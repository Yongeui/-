import sys

def GC_ratio_calculation(sequence):
    g_count = 0
    c_count = 0
    for nucleotide in sequence:
        if nucleotide == 'G':
            g_count += 1
        elif nucleotide == 'C':
            c_count += 1
    total_length = len(sequence)
    if total_length > 0:
        return ((g_count + c_count) / total_length) * 100
    else:
        return 0

def Fasta_format(fasta_file):
    sequences = {}
    current_id = ""
    content_exists = False
    try:
        with open(fasta_file, 'r') as file:
            for line in file:
                line = line.strip()
                if line:
                    content_exists = True
                    if line.startswith('>'):
                        current_id = line
                        sequences[current_id] = ""
                    elif current_id:
                        sequences[current_id] += line.upper()
    except Exception:
        print("파일을 읽는 중 오류 발생")
        sys.exit(1)
    
    if not content_exists:
        print("입력파일을 확인하세요.")
        sys.exit(1)
    
    return sequences

def Inspection_ATCG(sequence):
    for char in sequence:
        if char not in ['A', 'T', 'C', 'G']:
            return False
    return True

def find_high_GC_content(sequences):
    find_valid_sequence = True
    for seq_id, sequence in sequences.items():
        if not Inspection_ATCG(sequence):
            find_valid_sequence = False
            break
    
    if not find_valid_sequence:
        print("No DNA sequence.")
        sys.exit(1)
    
    high_GC_content = 0
    high_GC_name = ""
    for seq_id, sequence in sequences.items():
        gc_content = GC_ratio_calculation(sequence)
        if gc_content > high_GC_content:
            high_GC_content = gc_content
            high_GC_name = seq_id
            
    if not high_GC_name:
        print("No DNA sequence.")
        sys.exit(1)
    
    return high_GC_name, high_GC_content

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("입출력 파일을 확인하세요.")
        sys.exit(1)

    inputFileName = sys.argv[1]
    outputFileName = sys.argv[2]

    sequences = Fasta_format(inputFileName)
    if not sequences:
        print("No DNA sequence.")
        sys.exit(1)
    
    high_GC_name, high_GC_content = find_high_GC_content(sequences)
    if high_GC_name:
        print(f"GC비율이 가장 높은 시퀀스는? : {high_GC_content}%")
        with open(outputFileName, 'w') as output_file:
            output_file.write(f"{high_GC_name}\n{sequences[high_GC_name]}")
    else:
        print("No DNA sequencee. ")
