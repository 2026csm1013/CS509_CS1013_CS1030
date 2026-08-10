import random
import os

# generate test file for triangle counting
def genTCTest(fName, numNodes, deg=4):

    totalEdges = (numNodes * deg) // 2
    edgesSet = set()

    # connect nodes in a line backbone
    for i in range(numNodes - 1):

        edgesSet.add((min(i, i + 1), max(i, i + 1)))

    # add random undirected edges
    while len(edgesSet) < totalEdges:

        uNode = random.randint(0, numNodes - 1)
        vNode = random.randint(0, numNodes - 1)

        if uNode != vNode:

            edgesSet.add((min(uNode, vNode), max(uNode, vNode)))

    # build adjacency list
    adjList = {}
    for i in range(numNodes):

        adjList[i] = []

    for uNode, vNode in edgesSet:

        adjList[uNode].append(vNode)
        adjList[vNode].append(uNode)

    # write to file
    f = open(fName, "w")
    f.write(str(numNodes) + " " + str(len(edgesSet)) + "\n")

    for uNode in range(numNodes):

        curEdges = adjList[uNode]
        dCount = len(curEdges)

        if dCount > 0:

            lineStr = str(uNode) + " " + str(dCount)

            for vNode in curEdges:

                lineStr = lineStr + " " + str(vNode)

            f.write(lineStr + "\n")
        else:

            f.write(str(uNode) + " 0\n")

    f.close()

    print("Generated " + fName + " successfully.")


if __name__ == "__main__":

    os.makedirs("assignment_02/tests", exist_ok=True)

    nodeSizes = [10, 100, 10000, 50000, 100000]

    for nVal in nodeSizes:

        outPath = "assignment_02/tests/tc_" + str(nVal) + ".txt"
        genTCTest(outPath, nVal, 4)