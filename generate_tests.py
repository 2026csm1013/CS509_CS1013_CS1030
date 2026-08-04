import random

def generate_graph(num_vertices, avg_degree, is_weighted, filename):
    with open(filename, 'w') as f:
        # Estimate total edges
        total_edges = num_vertices * avg_degree
        f.write(f"{num_vertices} {total_edges}\n")
        
        for u in range(num_vertices):
            num_neighbors = max(1, random.randint(avg_degree - 1, avg_degree + 1))
            neighbors = set()
            while len(neighbors) < num_neighbors:
                v = random.randint(0, num_vertices - 1)
                if v != u:
                    neighbors.add(v)
            
            line = [str(u), str(len(neighbors))]
            for v in sorted(neighbors):
                line.append(str(v))
                if is_weighted:
                    weight = random.randint(1, 20)
                    line.append(str(weight))
            
            f.write(" ".join(line) + "\n")
        
        f.write("SOURCE 0\n")

# Target sizes required by Section 4.2
scales = [10, 100, 10000, 50000, 100000]

print("Generating Graph Test Inputs...")
for V in scales:
    # 1. Unweighted graphs for BFS & DFS (Section 6.1)
    generate_graph(V, avg_degree=3, is_weighted=False, filename=f"tests/bfs_{V}.txt")
    generate_graph(V, avg_degree=3, is_weighted=False, filename=f"tests/dfs_{V}.txt")
    
    # 2. Positive-weighted graphs for SSSP (Section 7.1)
    generate_graph(V, avg_degree=3, is_weighted=True, filename=f"tests/sssp_{V}.txt")
    print(f"  [+] Generated inputs for V = {V}")

print("All test files successfully generated in tests/ folder!")