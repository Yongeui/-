#Assignmnet#82021245151 정용의

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

def Distance_calculation(s1, s2):
    return sum(ch1 != ch2 for ch1, ch2 in zip(s1, s2))

def Combination_string(options, length):
    result = []
    def generate(current):
        if len(current) == length:
            result.append(current)
            return
        for option in options:
            generate(current + option)
    generate("")
    return result

def Find_pattern(sequences, m):
    if len(sequences) < 2:
        print("Need more sequence")
        sys.exit()

    all_patterns = Combination_string('ATCG', m)
    min_distance = float('inf')
    best_patterns = []

    for pattern in all_patterns:
        current_min_distance = float('inf')
        pattern_distances = []

        for seq in sequences:
            min_dist_for_seq = float('inf')

            for i in range(len(seq) - m + 1):
                dist = Distance_calculation(pattern, seq[i:i+m])
                if dist < min_dist_for_seq:
                    min_dist_for_seq = dist

            pattern_distances.append(min_dist_for_seq)

        total_distance = sum(pattern_distances)

        if total_distance < min_distance:
            min_distance = total_distance
            best_patterns = [pattern]
        elif total_distance == min_distance:
            best_patterns.append(pattern)

    return best_patterns

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print("입출력파일과 패턴길이를 확인해주세요.")
        sys.exit()

    inputFileName = sys.argv[1]
    outputFileName = sys.argv[2]
    patternLength = int(sys.argv[3])

    if patternLength < 1:
        print("패턴의 길이는 최소 1개 이상 입력하세요.")
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

    approximate_patterns = Find_pattern(sequences, patternLength)

    with open(outputFileName, 'w') as f:
        if approximate_patterns:
            for pattern in approximate_patterns:
                f.write(pattern + '\n')
        else:
            print("No pattern found")

    elapsed_time = time.time() - start_time
    elapsed_time_in_microsecond = elapsed_time * 1000000
    print(f"실행 시간: {elapsed_time_in_microsecond:.0f} microsecond ({elapsed_time:.6f} 초)")