
import sys
import time
import re

def Fasta_format(input_file):
    sequences = []
    try:
        with open(input_file, 'r') as file:
            sequence = ''
            header_present = False
            for line in file:
                line = line.strip()
                if line.startswith('>'):
                    header_present = True
                    if sequence:
                        sequences.append(sequence.upper())
                        sequence = ''
                elif line:
                    if not header_present:
                        print("No correct format")
                        sys.exit()
                    sequence += line
            if sequence:
                sequences.append(sequence.upper())
    except FileNotFoundError:
        print("No input file")
        sys.exit()
    if not header_present:
        print("No correct format")
        sys.exit()
    if not sequences:
        print("No DNA sequence")
        sys.exit()
    return sequences

def Inspection_ATCG(sequences):
    if any(not re.fullmatch('[ACGT]+', seq, re.IGNORECASE) for seq in sequences):
        print("No DNA sequence")
        sys.exit()
    seq_length = len(sequences[0])
    if any(len(seq) != seq_length for seq in sequences):
        print("Incorrect length of sequence")
        sys.exit()
    if len(sequences) & (len(sequences) - 1) != 0:
        print("Incorrect number of sequence")
        sys.exit()

def Create_tree(sequences):
    nodes = [[seq, []] for seq in sequences]
    while len(nodes) > 1:
        new_nodes = []
        for i in range(0, len(nodes), 2):
            left, right = nodes[i], nodes[i+1]
            parent = ['', [left, right]]
            new_nodes.append(parent)
        nodes = new_nodes
    return nodes[0]

def Fitch_alg(node):
    if not node[1]:
        return {node[0]}, 0
    left_set, left_cost = Fitch_alg(node[1][0])
    right_set, right_cost = Fitch_alg(node[1][1])
    intersection = left_set.intersection(right_set)
    if intersection:
        node[0] = min(intersection)
        return intersection, left_cost + right_cost
    union = left_set.union(right_set)
    node[0] = min(union)
    return union, left_cost + right_cost + 1

def Parsimony_score(root, outputFileName):
    result = []
    def traverse(node):
        if node:
            result.append(node[0])
            if node[1]:
                traverse(node[1][0])
                traverse(node[1][1])

    traverse(root)
    with open(outputFileName, 'w') as f:
        for res in result:
            f.write(res + '\n')

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("입출력 파일을 확인하세요.")
        sys.exit(1)

    start_time = time.time()
    inputFileName = sys.argv[1]
    outputFileName = sys.argv[2]

    sequences = Fasta_format(inputFileName)
    Inspection_ATCG(sequences)
    root = Create_tree(sequences)
    _, parsimony_score = Fitch_alg(root)
    Parsimony_score(root, outputFileName)
    end_time = time.time()

    elapsed_time = end_time - start_time
    elapsed_time_in_microsecond = elapsed_time * 1000000
    elapsed_time_in_second = elapsed_time

    print(f"Parsimony score : {parsimony_score}")
    print(f"실행시간 : {elapsed_time_in_microsecond:.0f} microsecond ({elapsed_time_in_second:.6f} 초)")
