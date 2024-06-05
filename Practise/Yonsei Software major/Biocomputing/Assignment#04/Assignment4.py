import sys
import time

def Fasta_format(fasta_file):
    sequences = []
    try:
        with open(fasta_file, 'r') as file:
            lines = file.readlines()
            if not lines:
                print("DNA 서열이 없습니다.")
                sys.exit()

            if not lines[0].startswith('>'):
                print("형식이 잘못되었습니다.")
                sys.exit()

            content = ''.join(lines).strip().upper()
            seq_blocks = content.split('>')
            for block in seq_blocks[1:]:
                parts = block.split('\n', 1)
                if len(parts) != 2 or not parts[1].replace('\n', ''):
                    print("형식이 잘못되었습니다.")
                    sys.exit()
                seq = ''.join(parts[1].split())
                if seq:
                    sequences.append(seq)
                    if len(sequences) >= 2:
                        break
    except Exception as e:
        print(f"파일을 읽는 중 오류 발생: {e}")
        sys.exit("DNA 서열이 없습니다.")

    return sequences

def Inspection_ATCG(sequence):
    valid_chars = set("ATCG")
    for char in sequence:
        if char not in valid_chars:
            return False
    return True

def Find_edit_distance(seq1, seq2):
    m, n = len(seq1), len(seq2)
    if n > m:
        seq1, seq2 = seq2, seq1
        n, m = m, n

    current_row = list(range(n+1))
    for i in range(1, m+1):
        previous_row, current_row = current_row, [i] + [0] * n
        for j in range(1, n+1):
            add, delete, change = previous_row[j] + 1, current_row[j-1] + 1, previous_row[j-1]
            if seq1[i-1] != seq2[j-1]:
                change += 1
            current_row[j] = min(add, delete, change)

    return current_row[n]

def Validate_DNA(sequence):
    if not sequence or not Inspection_ATCG(sequence):
        return False
    if any(char.isspace() for char in sequence):
        return False
    return True

if __name__ == "__main__":
    start_time = time.time()

    if len(sys.argv) != 2:
        print("입력 파일을 확인하세요.")
        sys.exit()

    inputFileName = sys.argv[1]
    sequences = Fasta_format(inputFileName)

    if len(sequences) < 2:
        message = "서열이 더 필요합니다." if sequences else "DNA 서열이 없습니다."
        print(message)
        sys.exit()

    for seq in sequences:
        if not Validate_DNA(seq):
            print("No DNA sequence")
            sys.exit()

    seq1, seq2 = sequences[0], sequences[1]
    edit_distance = Find_edit_distance(seq1, seq2)
    elapsed_time_in_microsecond = (time.time() - start_time) * 1e6
    elapsed_time_in_second = elapsed_time_in_microsecond / 1e6

    print(f"편집 거리: {edit_distance}")
    print(f"실행 시간: {elapsed_time_in_microsecond:.0f} microsecond ({elapsed_time_in_second:.6f} 초)")
