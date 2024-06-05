import sys
import time

def Fasta_format(fasta_file):
    sequences = []
    try:
        with open(fasta_file, 'r') as file:
            content = file.read().strip().upper()
            if not content:
                print("No DNA sequence")
                sys.exit()
            if '>' not in content:
                print("No correct format")
                sys.exit()
            seq_blocks = content.split('>')
            if len(seq_blocks) < 2 or seq_blocks[0]:
                print("No correct format")
                sys.exit()
            for block in seq_blocks[1:]:
                parts = block.split('\n', 1)
                if len(parts) != 2:
                    print("No correct format")
                    sys.exit()
                header, sequence = parts[0], parts[1].strip()
                if not sequence:
                    print("No DNA sequence")
                    sys.exit()
                cleaned_sequence = ''.join(sequence.split())
                if not cleaned_sequence or any(char not in 'ATCG' for char in cleaned_sequence):
                    print("No DNA sequence")
                    sys.exit()
                sequences.append(cleaned_sequence)
                if len(sequences) >= 2:
                    break
    except IOError as e:
        print(f"파일을 읽는 중 오류 발생: {e}")
        sys.exit()
    return sequences

def Inspection_ATCG(sequence):
    for char in sequence:
        if char not in 'ATCG' or char in ' ':
            return False
    return True

def Dynamic_program(seq1, seq2, match=2, mismatch=-2, gap=-1):
    m, n = len(seq1), len(seq2)
    score = [[0] * (n + 1) for _ in range(m + 1)]
    max_score = 0
    max_pos = None

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            diag = score[i-1][j-1] + (match if seq1[i-1] == seq2[j-1] else mismatch)
            delete = score[i-1][j] + gap
            insert = score[i][j-1] + gap
            max_value = max(0, diag, delete, insert)
            score[i][j] = max_value
            if max_value > max_score:
                max_score = max_value
                max_pos = (i, j)

    aligned1, aligned2 = '', ''
    i, j = max_pos
    while i > 0 and j > 0 and score[i][j] > 0:
        if score[i][j] == score[i-1][j-1] + (match if seq1[i-1] == seq2[j-1] else mismatch):
            aligned1 = seq1[i-1] + aligned1
            aligned2 = seq2[j-1] + aligned2
            i -= 1
            j -= 1
        elif score[i-1][j] > score[i][j-1]:
            aligned1 = seq1[i-1] + aligned1
            aligned2 = '-' + aligned2
            i -= 1
        else:
            aligned1 = '-' + aligned1
            aligned2 = seq2[j-1] + aligned2
            j -= 1

    return aligned1, aligned2, max_score

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("입출력 파일을 확인하세요.")
        sys.exit()

    start_time = time.time()

    inputFileName = sys.argv[1]
    outputFileName = sys.argv[2]

    sequences = Fasta_format(inputFileName)
    
    if len(sequences) < 2:
        print("Need more sequences")
        sys.exit()

    if not all(Inspection_ATCG(seq) for seq in sequences[:2]):
        print("No DNA sequence")
        sys.exit()

    seq1, seq2 = sequences[0], sequences[1]
    aligned_seq1, aligned_seq2, score = Dynamic_program(seq1, seq2)

    with open(outputFileName, 'w') as file:
        file.write(f"{aligned_seq1}\n{aligned_seq2}\n")

    elapsed_time_in_microsecond = (time.time() - start_time) * 1e6
    elapsed_time_in_second = elapsed_time_in_microsecond / 1e6

    print(f" A 스코어: {score}")
    print(f"실행 시간: {elapsed_time_in_microsecond:.0f} microsecond ({elapsed_time_in_second:.6f} 초)")