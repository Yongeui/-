#2021245151 정용의

import sys

def reverse_compensation(seq):
    seq = seq.upper()[::-1]
    new_seq = ''
    for char in seq:
        if char == 'A':
            new_seq += 'T'
        elif char == 'T':
            new_seq += 'A'
        elif char == 'C':
            new_seq += 'G'
        elif char == 'G':
            new_seq += 'C'
    return new_seq

def Inspection_ATCG(dna):
    inspection_chars = {'A', 'T', 'C', 'G'}
    for char in dna:
        if char not in inspection_chars:
            return False
    return True

def switch_files(input_file_name, output_file_name):
    try:
        with open(input_file_name, 'r',  encoding='utf-8') as file:
            dna_sequences = file.read().split('>')
            dna=''
            for seq in dna_sequences:
                if seq.strip():
                    lines = seq.split('\n')
                    if len(lines) > 1:
                        dna += ''.join(lines[1:])
                    else:
                        dna += ''.join(lines)

        dna = dna.replace('\n', '').upper()
        
        
        if not dna:
            result = "DNA염기서열이 없습니다."
        elif not Inspection_ATCG(dna):
            result = "오류 발생: 유효하지 않은 문자가 포함되어 있습니다."
        else:
            result = reverse_compensation(dna)

        with open(output_file_name, 'w',  encoding='utf-8') as outFile:
            outFile.write(result)

    except Exception as e:
        print(f"파일을 처리 도중 오류 발생: {e}")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("입출력파일을 준비해주세요")
    else:
        inputFileName = sys.argv[1]
        outputFileName = sys.argv[2]
        switch_files(inputFileName, outputFileName)
