from collections import defaultdict

class Vertex:
    def __init__(self, node):
        self.id = node
        self.children = {}

    def addNeighbor(self, neighbor, weight=0):
        self.children[neighbor] = weight

    def getConnection(self):
        return self.children.keys()

    def getID(self):
        return self.id

    def getWeight(self, neighbor):
        return int(self.children[neighbor])
        
    def getActions(self):
        options = []
        for x in self.children:
            options.append(x.getID())
        return options

class Graph:
    
    # Constructor
    def __init__ (self):
        self.vertices = {}
        self.numVertices = 0
    
    def __iter__(self):
        return iter(self.vertices.values())

    def addVertex(self, node):
        self.numVertices = self.numVertices + 1
        newVertex = Vertex(node)
        self.vertices[node] = newVertex
        return newVertex

    def getVertex(self, n):
        if n in self.vertices:
            return self.vertices[n]
        else:
            return None

    def addEdge(self, source, to, cost = 0):
        if source not in self.vertices:
            self.addVertex(source)
        if to not in self.vertices:
            self.addVertex(to)

        self.vertices[source].addNeighbor(self.vertices[to], cost)

    def getVertices(self):
        return self.vertices.keys()
        
    def getSolution(self, aDict, solution):
        count = 0
        for x in aDict:
            if count == 0:
                solution.append(x)
                count = count + 1
            else:
                self.getSolution(x, solution)
                
    def getPathWeight(self, myList):
        for i in range(0, len(myList)):
            myList[i] = int(myList[i])
        return myList       

	#**************************************************************************************

    def BFS(self, start, dest):
        node = start
        
        # FIFO queue
        bfs_frontier = []
        bfs_frontier.append(node)
        explored = []
        
        solutionPath = defaultdict(list)
        solutionPath[node].append(node)
        mySolution = []
        solutionWeights = defaultdict(list)
        
        pathWeight = [0]
        newPathWeight = 0
        solutionWeights[node] = pathWeight
        
        loop = True
        
        while(loop and bfs_frontier):
            # Print Current Status
            
            if bfs_frontier == []:
                print("Error")
                break
            # endIf
            node = bfs_frontier.pop(0)
            node = node.rstrip("\n")
            pathWeight = solutionWeights[node]
            if node == dest:
                g.getSolution(solutionPath[node], mySolution)
                outFile = open("output.txt", "w")
                for x in reversed(mySolution):
                    outFile.write("{} {}\n".format(x, solutionWeights[x]))
                # endFor
                outFile.close()
                loop = False
                break
            # endIf
            explored.append(node)
            actions = []
            for v in g:
                if v.getID() == node:
                    actions = v.getActions()
                    break
                # endIf
            # endFor
            for x in actions:
                if x not in explored:
                    if x not in bfs_frontier:
                        bfs_frontier.append(x)
                        if x not in solutionPath:
                            solutionPath[x].append(x)
                            solutionPath[x].append(solutionPath[node])
                        # endIf
                        for v in g:
                            for w in v.getConnection():
                                if ((v.getID() == node) and (w.getID() == x)):
                                    newPathWeight = v.getWeight(w)
                                    newPathWeight = newPathWeight + pathWeight[0]
                                    solutionWeights[x].append(newPathWeight)
                                    
                                    newPathWeight = 0
                                # endIf
                            # endFor
                        # endFor
                    # endIf
                # endIf
            # endFor
        # endWhile
    # endBFS
        
                        
	#**************************************************************************************

    def DFS(self, start, dest):
        node = start

        # FIFO queue
        frontier = []
        frontier.append(node)
        explored = []

        solutionPath = defaultdict(list)
        solutionPath[node].append(node)
        mySolution = []
        solutionWeights = defaultdict(list)

        pathWeight = [0]
        newPathWeight = 0
        solutionWeights[node] = pathWeight

        while(frontier):
            if frontier == []:
                print("Error")
                break
            # endIf
            node = frontier.pop()
            node = node.rstrip("\n")
            pathWeight = solutionWeights[node]
            if node == dest:
                #print("Dest node found!")
                g.getSolution(solutionPath[node], mySolution)
                outFile = open("output.txt", "w")
                for x in reversed(mySolution):
                    outFile.write("{} {}\n".format(x, solutionWeights[x]))
                # endFor
                outFile.close()
                break
            # endIf
            explored.append(node)
            actions = []
            for v in g:
                if v.getID() == node:
                    actions = v.getActions()
                    #print("Possible Actions: {}\n".format(actions))
                    break
                # endIf
            # endFor
            for x in actions:
                if x not in explored:
                    if x not in frontier:
                        frontier.append(x)
                        if x not in solutionPath:
                            solutionPath[x].append(x)
                            solutionPath[x].append(solutionPath[node])
                        # endIf
                        for v in g:
                            for w in v.getConnection():
                                if ((v.getID() == node) and (w.getID() == x)):
                                    newPathWeight = v.getWeight(w)
                                    print("new weight: {}\npath weight:{}\n".format(newPathWeight, pathWeight))
                                    newPathWeight = newPathWeight + pathWeight[0]
                                    solutionWeights[x].append(newPathWeight)

                                    newPathWeight = 0
                                # endIf
                            # endFor
                        # endFor
                    # endIf
                # endIf
            # endFor
        # endWhile
    # endDFS
	#**************************************************************************************


    def UCS(self, start, dest):
        node = start

        # FIFO priority queue
        frontier = []
        frontier.append(node)
        explored = []

        solutionPath = defaultdict(list)
        solutionPath[node].append(node)
        mySolution = []
        solutionWeights = defaultdict(list)

        pathWeight = [0]
        newPathWeight = 0
        solutionWeights[node] = pathWeight

        while(True):
            # Print Current Status
            print("Current Node: {}\nFrontier: {}\nExplored: {}\n".format(node, frontier, explored))

            if frontier == []:
                print("Error")
                break
            # endIf
            node = frontier.pop(0)
            node = node.rstrip("\n")
            pathWeight = solutionWeights[node]
            if node == dest:
                print("Dest node found!")
                g.getSolution(solutionPath[node], mySolution)
                outFile = open("output.txt", "w")
                for x in reversed(mySolution):
                    outFile.write("{} {}\n".format(x, solutionWeights[x]))
                # endFor
                outFile.close()
                break
            # endIf
            explored.append(node)
            actions = []
            for v in g:
                if v.getID() == node:
                    actions = v.getActions()
                    print("Possible Actions: {}\n".format(actions))
                    break
                # endIf
            # endFor
            for x in actions:
                if x not in explored:
                    if x not in frontier:
                        for i in frontier:
                            pathcost = solutionWeights[i]
                            for v in g:
                            	for w in v.getConnection():
                                    if ((v.getID() == node) and (w.getID() == x)):
                                        newPathWeight = v.getWeight(w)
                                        if pathWeight != []:
                                            newPathWeight = newPathWeight + pathWeight[0]
                                        # endIf
                                        print("pathcost: {}newPathWeight: {}".format(pathcost, newPathWeight))
                                        if pathcost != []:
                                            if newPathWeight < pathcost[0]:
                                                print("Index: {}".format(frontier.index(i)))
                                                indexValue = frontier.index(i)
                                                frontier.insert(indexValue, x)
                                                if x not in solutionPath:
                                                    solutionPath[x].append(x)
                                                    solutionPath[x].append(solutionPath[node])
                                                break
                                            # endIf
                                        # endIf
                                        else:
                                            break
                                        # endElse
                                    # endIf
                                # endFor
                            # endFor
                            break
                        # endFor
                    # endIf
                    if x not in frontier:
                        frontier.append(x)
                    
                        if x not in solutionPath:
                            solutionPath[x].append(x)
                            solutionPath[x].append(solutionPath[node])
                        # endIf
                    for v in g:
                        for w in v.getConnection():
                            if x not in solutionWeights:
                                if ((v.getID() == node) and (w.getID() == x)):
                                    newPathWeight = v.getWeight(w)
                                    print("new weight: {}\npath weight: {}\n".format(newPathWeight, pathWeight))
                                    newPathWeight = newPathWeight + pathWeight[0]
                                    solutionWeights[x].append(newPathWeight)

                                    newPathWeight = 0
                                # endIf
                            # endFor
                        # endFor
                    # endIf
                # endIf
            # endFor
        # endWhile
    # endUCS
	#**************************************************************************************

    def A_star(self, start, dest, heuristic):
        node = start

        # FIFO priority queue
        frontier = []
        frontier.append(node)
        explored = []

        solutionPath = defaultdict(list)
        solutionPath[node].append(node)
        mySolution = []
        solutionWeights = defaultdict(list)

        pathWeight = [0]
        newPathWeight = 0
        solutionWeights[node] = pathWeight
        
        frontierWeight = {}
        frontierWeight[node] = heuristic.get(node)

        while(True):
            # Print Current Status

            if frontier == []:
                print("Error")
                break
            # endIf
            node = frontier.pop(0)
            node = node.rstrip("\n")
            pathWeight = solutionWeights[node]
            if node == dest:
                g.getSolution(solutionPath[node], mySolution)
                outFile = open("output.txt", "w")
                for x in reversed(mySolution):
                    outFile.write("{} {}\n".format(x, solutionWeights[x]))
                outFile.close()
                # endFor
                break
            # endIf
            explored.append(node)
            actions = []
            for v in g:
                if v.getID() == node:
                    actions = v.getActions()
                    break
                # endIf
            # endFor
            for x in actions:
                if x not in explored:
                    if x not in frontier:
                        for i in frontier:
                            pathcost = solutionWeights[i]
                            for v in g:
                            	for w in v.getConnection():
                                    if ((v.getID() == node) and (w.getID() == x)):
                                        newPathWeight = v.getWeight(w)
                                        if pathWeight != []:
                                            newPathWeight = newPathWeight + pathWeight[0] + heuristic.get(x)
                                        # endIf
                                        if pathcost != []:
                                            if newPathWeight < (pathcost[0] + heuristic.get(i)):
                                                indexValue = frontier.index(i)
                                                frontier.insert(indexValue, x)
                                                if x not in solutionPath:
                                                    solutionPath[x].append(x)
                                                    solutionPath[x].append(solutionPath[node])
                                                break
                                            # endIf
                                        # endIf
                                        else:
                                            break
                                        # endElse
                                    # endIf
                                # endFor
                            # endFor
                            break
                        # endFor
                    # endIf
                    if x not in frontier:
                        frontier.append(x)
                            
                        if x not in solutionPath:
                            solutionPath[x].append(x)
                            solutionPath[x].append(solutionPath[node])
                        # endIf
                    for v in g:
                        for w in v.getConnection():
                            if x not in solutionWeights:
                                if ((v.getID() == node) and (w.getID() == x)):
                                    newPathWeight = v.getWeight(w)
                                    newPathWeight = newPathWeight + pathWeight[0]
                                    solutionWeights[x].append(newPathWeight)
                                    frontierWeight[x] = heuristic.get(x) + newPathWeight

                                    newPathWeight = 0
                                # endIf
                            # endFor
                        # endFor
                    # endIf
                # endIf
            # endFor
        # endWhile
    # endA_star


# endGraph


if __name__ == '__main__':

    inFile = open('input.txt', 'r')
    Lines = inFile.readlines()
    count = 0
    searchType = Lines[0]
    start = Lines[1]
    end = Lines[2]
    liveTrafficLines = int(Lines[3])
    sundayTrafficLines = int(Lines[4 + liveTrafficLines])

    heuristic = defaultdict()
        
    g = Graph()
    for line in Lines[4:4+liveTrafficLines]:
        words = line.split()
        g.addEdge(words[0], words[1], int(words[2]))

    for line in Lines[5+liveTrafficLines:6+liveTrafficLines + sundayTrafficLines]:
        words = line.split()
        heuristic[words[0]]= int(words[1])

    start = start.rstrip("\n")
    end = end.rstrip("\n")
    searchType = searchType.rstrip("\n")
    # Print Starting Point and Goal
    print("Starting Node: {}\nGoal Node: {}\n".format(repr(start), repr(end)))
    print("******************************")
    print("Starting {}\n".format(searchType))

    if searchType == "BFS":
        g.BFS(start, end)
        
    elif searchType == "UCS":
        g.UCS(start, end)
        
    elif searchType == "DFS":
        g.DFS(start, end)

    elif searchType == "A*":
        g.A_star(start, end, heuristic)
        
    print("{} Finished\nCheck \"output.txt\" for Results".format(searchType))
    print("******************************\n")






