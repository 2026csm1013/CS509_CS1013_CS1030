import random
import os

# generate test file for betweenness centrality
def genBCTest(fName, numNodes, deg=3):

    totalEdges = numNodes * deg
    edgesSet = set()

    # connect nodes in a line backbone
    for i in range(numNodes - 1):

        edgesSet.add((i, i + 1))

    # add random undirected edges
    while len(edgesSet) < totalEdges:

        uNode = random.randint(0, numNodes - 1)
        vNode = random.randint(0, numNodes - 1)

        if uNode != vNode:

            minU = min(uNode, vNode)
            maxV = max(uNode, vNode)
            edgesSet.add((minU, maxV))

    # build adjacency set
    adjMap = {}
    for i in range(numNodes):

        adjMap[i] = set()

    for uNode, vNode in edgesSet:

        adjMap[uNode].add(vNode)
        adjMap[vNode].add(uNode)

    # write to output file
    f = open(fName, "w")
    f.write(str(numNodes) + " " + str(len(edgesSet)) + "\n")

    for uNode in range(numNodes):

        nbrs = sorted(list(adjMap[uNode]))
        dCount = len(nbrs)

        lineStr = str(uNode) + " " + str(dCount)

        for vNode in nbrs:

            lineStr = lineStr + " " + str(vNode)

        f.write(lineStr + "\n")

    f.close()

    print("Generated " + fName + " successfully.")


if __name__ == "__main__":

    os.makedirs("assignment_02/tests", exist_ok=True)

    nodeSizes = [10, 100, 1000, 5000, 10000]

    for nVal in nodeSizes:

        outPath = "assignment_02/tests/bc_" + str(nVal) + ".txt"
        genBCTest(outPath, nVal, 3)