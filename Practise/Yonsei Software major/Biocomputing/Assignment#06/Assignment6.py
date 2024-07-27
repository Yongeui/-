import re
import sys
import time
import os

def protein_inspection(sequence):
    for char in sequence:
        if char not in 'CSTPAGNDEQHRKMILVFYW' or char in ' ':
            return False
    return True

def get_protein_sequences(path: str) -> list[str]:
    if not os.path.isfile(path):
        print("입력 파일이 존재하지 않습니다.")
        sys.exit()
    
    sequences = []
    with open(path, 'r') as file:
        content = file.read()
        if '>' not in content:
            print("No correct format")
            sys.exit()
        sequence = ""
        for line in content.split('\n'):
            line = line.strip()
            if line.startswith('>'):
                if sequence:
                    sequences.append(sequence.upper())
                    sequence = ""
            else:
                if not protein_inspection(line):
                    print("No protein sequence")
                    sys.exit()
                sequence += line
        if sequence:
            sequences.append(sequence.upper())
    
    if len(sequences) < 2:
        print("Need more sequences")
        sys.exit()
    
    return sequences

def blosum62_matrix():
    proteins = "CSTPAGNDEQHRKMILVFYW"
    blosum62_scores = [
        [9, -1, -1, -3, 0, -3, -3, -3, -4, -3, -3, -3, -3, -1, -1, -1, -1, -2, -2, -2],
        [-1, 4, 1, -1, 1, 0, 1, 0, 0, 0, -1, -1, 0, -1, -2, -2, -2, -2, -2, -3],
        [-1, 1, 4, -1, 0, -2, 0, -1, -1, -1, -2, -1, -1, -1, -1, -1, 0, -2, -2, -2],
        [-3, -1, -1, 7, -1, -2, -2, -1, -1, -1, -2, -2, -1, -2, -3, -3, -2, -4, -3, -4],
        [0, 1, 0, -1, 4, 0, -2, -2, -1, -1, -2, -1, -1, -1, -1, -1, 0, -2, -2, -3],
        [-3, 0, -2, -2, 0, 6, 0, -1, -2, -2, -2, -2, -2, -3, -4, -4, -3, -3, -3, -2],
        [-3, 1, 0, -2, -2, 0, 6, 1, 0, 0, 1, 0, 0, -2, -3, -3, -3, -3, -2, -4],
        [-3, 0, -1, -1, -2, -1, 1, 6, 2, 0, -1, -2, -1, -3, -3, -4, -3, -3, -3, -4],
        [-4, 0, -1, -1, -1, -2, 0, 2, 5, 2, 0, 0, 1, -2, -3, -3, -2, -3, -2, -3],
        [-3, 0, -1, -1, -1, -2, 0, 0, 2, 5, 0, 1, 1, 0, -3, -2, -2, -3, -1, -2],
        [-3, -1, -2, -2, -2, -2, 1, -1, 0, 0, 8, 0, -1, -2, -3, -3, -3, -1, 2, -2],
        [-3, -1, -1, -2, -1, -2, 0, -2, 0, 1, 0, 5, 2, -1, -3, -2, -3, -3, -2, -3],
        [-3, 0, -1, -1, -1, -2, 0, -1, 1, 1, -1, 2, 5, -1, -3, -2, -2, -3, -2, -3],
        [-1, -1, -1, -2, -1, -3, -2, -3, -2, 0, -2, -1, -1, 5, 1, 2, 1, 0, -1, -1],
        [-1, -2, -1, -3, -1, -4, -3, -3, -3, -3, -3, -3, -3, 1, 4, 2, 3, 0, -1, -3],
        [-1, -2, -1, -3, -1, -4, -3, -4, -3, -2, -3, -2, -2, 2, 2, 4, 1, 0, -1, -2],
        [-1, -2, 0, -2, 0, -3, -3, -3, -2, -2, -3, -3, -2, 1, 3, 1, 4, -1, -1, -3],
        [-2, -2, -2, -4, -2, -3, -3, -3, -3, -3, -1, -3, -3, 0, 0, 0, -1, 6, 3, 1],
        [-2, -2, -2, -3, -2, -3, -2, -3, -2, -1, 2, -2, -2, -1, -1, -1, -1, 3, 7, 2],
        [-2, -3, -2, -4, -3, -2, -4, -4, -3, -2, -2, -3, -3, -1, -3, -2, -3, 1, 2, 11]
    ]
    protein_dict = {protein: index for index, protein in enumerate(proteins)}
    blosum_dict = {proteins[i]: {proteins[j]: blosum62_scores[i][j] for j in range(len(proteins))} for i in range(len(proteins))}
    return protein_dict, blosum_dict

def table_initialization(n, m, gap_penalty):
    dp = [[0] * m for _ in range(n)]
    for i in range(1, n):
        dp[i][0] = dp[i-1][0] + gap_penalty
    for j in range(1, m):
        dp[0][j] = dp[0][j-1] + gap_penalty
    return dp

def PSA(seq1, seq2, protein_dict, blosum_dict, gap_penalty):
    n, m = len(seq1), len(seq2)
    dp = table_initialization(n + 1, m + 1, gap_penalty)
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            match = dp[i-1][j-1] + blosum_dict[seq1[i-1]][seq2[j-1]]
            delete = dp[i-1][j] + gap_penalty
            insert = dp[i][j-1] + gap_penalty
            dp[i][j] = max(match, delete, insert)
    align1, align2 = '', ''
    i, j = n, m
    while i > 0 and j > 0:
        if dp[i][j] == dp[i-1][j-1] + blosum_dict[seq1[i-1]][seq2[j-1]]:
            align1 = seq1[i-1] + align1
            align2 = seq2[j-1] + align2
            i -= 1
            j -= 1
        elif dp[i][j] == dp[i-1][j] + gap_penalty:
            align1 = seq1[i-1] + align1
            align2 = '-' + align2
            i -= 1
        else:
            align1 = '-' + align1
            align2 = seq2[j-1] + align2
            j -= 1
    while i > 0:
        align1 = seq1[i-1] + align1
        align2 = '-' + align2
        i -= 1
    while j > 0:
        align1 = '-' + align1
        align2 = seq2[j-1] + align2
        j -= 1
    return align1, align2

def star_alignment(sequences, protein_dict, blosum_dict, gap_penalty):
    n = len(sequences)
    scores = [0] * n
    alignments = []
    for i in range(n):
        for j in range(i + 1, n):
            align1, align2 = PSA(sequences[i], sequences[j], protein_dict, blosum_dict, gap_penalty)
            score = sum(blosum_dict[align1[k]][align2[k]] for k in range(len(align1)) if align1[k] != '-' and align2[k] != '-')
            scores[i] += score
            scores[j] += score
    center_index = scores.index(max(scores))
    center_seq = sequences[center_index]
    center_align = ['', []]
    for i, char in enumerate(center_seq):
        if char == '-':
            center_align[1].append(i)
        center_align[0] += char
    alignments.append(center_align)
    for i in range(n):
        if i != center_index:
            align1, align2 = PSA(center_seq, sequences[i], protein_dict, blosum_dict, gap_penalty)
            for gap_index in reversed(center_align[1]):
                align2 = align2[:gap_index] + '-' + align2[gap_index:]
            alignments.append([align2, []])
    msa = [align[0] for align in alignments]
    return msa

def write_output(msa, output_path):
    with open(output_path, 'w') as file:
        for sequence in msa:
            for i in range(0, len(sequence), 50):
                file.write(sequence[i:i+50] + '\n')
            file.write('\n')

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("입출력 파일을 확인하세요!")
        sys.exit()

    inputFileName = sys.argv[1]
    outputFileName = sys.argv[2]

    start_time = time.time()

    sequences = get_protein_sequences(inputFileName)
    protein_dict, blosum_dict = blosum62_matrix()
    gap_penalty = -5
    msa = star_alignment(sequences, protein_dict, blosum_dict, gap_penalty)
    write_output(msa, outputFileName)

    elapsed_time_in_microsecond = (time.time() - start_time) * 1e6
    elapsed_time_in_second = elapsed_time_in_microsecond / 1e6

    print("출력을 완료하였습니다.")
    print(f"실행 시간: {elapsed_time_in_microsecond:.0f} microsecond ({elapsed_time_in_second:.6f} 초)")
