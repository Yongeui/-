#2021245151 정용의

"""
☆질문 2024/05/13
1. 여러개의 패턴이 나올 경우 어떤 패턴을 출력해야하는가? => 제일 처음 나온 패턴을 선택하여 출력
2. 같은 패턴이 오버래핑될 때 고려해야하는 부분은 무엇인가? => 시퀀스에 ABCDF가 있다면 길이를 4로 줬을 때 ABCD 그리고 BCDF로 출력되도록.
----------------------------------------------------------------------------------------------------------------------------

*sub string은 하나만 있을 수도 있고 여러 개 있을 수도 있다. 각 패턴을 한 줄씩 출력하도록 수정
동일한 패턴을 시퀀스에 존재하는만큼 출력하는 것이 아니라 중복되는 것은 제외하여 동일한 패턴만 출력.

☆제출마감 : 2024/05/15
"""

import sys
import time

def Fasta_format(input_file):
    with open(input_file, 'r') as file:
        sequences = []
        buffer = ''
        header = None
        for line in file:
            line = line.strip()
            if line.startswith('>'):
                if header and buffer:
                    if not Inspection_ATCG(buffer):
                        print("No DNA sequence")
                        sys.exit()
                    sequences.append(buffer.upper())
                    buffer = ''
                header = line[1:]
            else:
                if not header:
                    print("No correct format")
                    sys.exit()
                buffer += line
        if buffer:
            if not Inspection_ATCG(buffer):
                print("No DNA sequence")
                sys.exit()
            sequences.append(buffer.upper())

    return sequences

def Inspection_ATCG(sequence):
    return all(char in 'ATCG' for char in sequence.upper())

def Find_pattern(sequences, m):
    if len(sequences) < 2:
        print("Need more sequence")
        sys.exit()

    exact_pattern = set(sequences[0][i:i+m] for i in range(len(sequences[0]) - m + 1))
    for seq in sequences[1:]:
        Save_string = set(seq[i:i+m] for i in range(len(seq) - m + 1))
        exact_pattern.intersection_update(Save_string)
        if not exact_pattern:
            break

    return list(exact_pattern)

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("입출력파일과 패턴길이를 확인해주세요.")
        sys.exit()

    inputFileName = sys.argv[1]
    outputFileName = sys.argv[2]
    patternLength = int(sys.argv[3])

    if patternLength < 1:
        print("패턴의 길이는 최소 '1' 이상 입력하세요.")
        sys.exit()

    start_time = time.time()

    try:
        sequences = Fasta_format(inputFileName)
    except FileNotFoundError:
        print("No input file")
        sys.exit()
    except Exception as e:
        print("입력파일을 확인해주세요.", e)
        sys.exit()

    if not sequences:
        print("No DNA sequence")
        sys.exit()

    exact_pattern = Find_pattern(sequences, patternLength)

    with open(outputFileName, 'w') as f:
        if exact_pattern:
            for pattern in exact_pattern:
                f.write(pattern + '\n')
        else:
            print("No pattern found")

    elapsed_time = time.time() - start_time
    elapsed_time_in_microsecond = elapsed_time * 1000000
    elapsed_time_in_second = elapsed_time
    print(f"실행 시간: {elapsed_time_in_microsecond:.0f} microsecond ({elapsed_time_in_second:.6f} 초)")