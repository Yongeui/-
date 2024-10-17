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
