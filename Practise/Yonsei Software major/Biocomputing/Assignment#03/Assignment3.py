#2021245151 정용의

"""
DNA sequence에서 특정 segment가 연속하여 반복되는 것을 "repeat"이라하는데 이것을 찾는 것을 목표로한다.
segment의 사이즈는 길이2~4인 세그먼트가 최소 2번 이상 반복되는 경우를 repeat segment라 정의.
ex: AGCATCGATCGAGGC라면 ATCG라는 길이4의 세그먼트가 총 2번 ATCGATCG 반복된 것이다. 그렇다면 이 ATCGATCG가 하나의 Repeat segment인 것. 이 segment가
가장 길다면 해당 segment를 outputFile에 출력하도록 한다. 만약 동일한 길이 ATAT 혹은 TATA라는 repeat segment가 나왔다면 둘 중에 먼저 나온 repeat segment를
outputFile에 출력하도록 한다. 
★ Reapeat segment를 찾는데 걸리는 시간을 >elapsed time microsecnd<로 축정하여 CMD창에 출력할 것. + Time.Time()
★ ATCG라는 DNA sequence를 제외한 화이트스페이스, 기호가 sequence에 껴있다면 "No correct foramt"을 출력 (추가)
"""

import sys
import time

def Fasta_format(fasta_file):
    sequence = ""
    reading_sequence = False
    try:
        with open(fasta_file, 'r') as file:
            for line in file:
                line = line.strip()
                if line.startswith('>'):
                    if reading_sequence: 
                        break
                    else:
                        reading_sequence = True
                elif reading_sequence and not line:
                    continue
                elif reading_sequence:
                    sequence += line.upper()
    except Exception as e:
        print(f"파일을 읽는 중 오류 발생: {e}")
        sys.exit("No DNA sequence")
    
    if not sequence:
        print("No correct format")
        sys.exit(1)
    
    return sequence

def Inspection_ATCG(sequence):
    for char in sequence:
        if char not in ['A', 'T', 'C', 'G']:
            return False
    return True

def Find_repeat_segment(sequence):
    repeat_segment = ""
    for size in range(2, 5):
        for start in range(len(sequence)):
            segment = sequence[start:start+size]
            repeat = segment
            count = 1
            for check_start in range(start + size, len(sequence), size):
                next_segment = sequence[check_start:check_start+size]
                if next_segment == segment:
                    repeat += next_segment
                    count += 1
                else:
                    if count > 1 and len(repeat) > len(repeat_segment):
                        repeat_segment = repeat
                    break
            if count > 1 and len(repeat) > len(repeat_segment):
                repeat_segment = repeat

    return repeat_segment if repeat_segment else "No repeat"

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("입출력 파일을 확인하세요.")
        sys.exit(1)
    
    start_time = time.time()
    
    inputFileName = sys.argv[1]
    outputFileName = sys.argv[2]
    
    sequence = Fasta_format(inputFileName)
    if not Inspection_ATCG(sequence):
        print("No correct format")
        sys.exit(1)
    
    repeat_segment = Find_repeat_segment(sequence)
        
    with open(outputFileName, 'w') as file:
        file.write(repeat_segment)
    
    elapsed_time_in_second = time.time() - start_time
    elapsed_time_in_microsecond = elapsed_time_in_second * 1e6

    print(f"Repeat segment를 찾는데 걸린 시간: {elapsed_time_in_microsecond:.0f} microsecond ({elapsed_time_in_second:.6f} 초)")
