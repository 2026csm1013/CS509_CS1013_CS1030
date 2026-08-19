import random

# generate directed flow network
def genFlowNet(fileLoc, numNod, targetEdg, srcNod=0, snkNod=None):

    if snkNod is None:
        snkNod = numNod - 1

    adjList = {i: {} for i in range(numNod)}
    totEdg = 0

    # make sure path exists from src to snk
    midNods = list(range(1, numNod - 1))
    random.shuffle(midNods)
    mainPath = [srcNod] + midNods[:min(5, len(midNods))] + [snkNod]

    for i in range(len(mainPath) - 1):
        u = mainPath[i]
        v = mainPath[i + 1]
        cVal = random.randint(10, 50)
        adjList[u][v] = cVal
        totEdg += 1

    # add random sparse edges
    for u in range(numNod):
        if u == snkNod:
            continue

        degCount = random.randint(2, 4)

        for _ in range(degCount):
            if u + 1 < numNod:
                v = random.randint(u + 1, min(numNod - 1, u + 20))
            else:
                v = snkNod

            if v != u and v not in adjList[u]:
                adjList[u][v] = random.randint(1, 100)
                totEdg += 1

    # write to txt file
    with open(fileLoc, "w") as outF:
        outF.write(f"{numNod} {totEdg}\n")

        for u in range(numNod):
            nbrs = adjList[u]
            rowVals = [str(u), str(len(nbrs))]

            for v, cVal in nbrs.items():
                rowVals.extend([str(v), str(cVal)])

            outF.write(" ".join(rowVals) + "\n")

        outF.write(f"SOURCE {srcNod}\n")
        outF.write(f"SINK {snkNod}\n")


# make test files for maxflow
genFlowNet("assignment_03/tests/maxflow_10.txt", 10, 25)
genFlowNet("assignment_03/tests/maxflow_100.txt", 100, 300)
genFlowNet("assignment_03/tests/maxflow_1000.txt", 1000, 3000)
genFlowNet("assignment_03/tests/maxflow_10000.txt", 10000, 30000)
genFlowNet("assignment_03/tests/maxflow_50000.txt", 50000, 150000)

print("done generating test files")