from random import randrange
from random import randint
import math
import struct
from scipy.spatial.distance import hamming
import sys

mutationRate = .75
crossoverRate = .75
populationSize = 10
numOfGenerations = 20

fMaxList = []
fMinList = []
fAverageList = []

def float_to_bin(num):
    return ''.join('{:0>8b}'.format(c) for c in struct.pack('!f', num))

def bin_to_float(binary):
    return struct.unpack('!f',struct.pack('!I', int(binary, 2)))[0]

def M1(x):
    return (math.sin(5*math.pi*x))**6

def GenerateRandomSolutions(variables, solutions):
    while len(solutions) < populationSize:
        newVar = randrange(1,101)/100
        variables.append(newVar)
        solutions.append(M1(newVar))
        
def DetermineBest(solutions):
    bestSolutions = []
    #something something Hamming distance
    
    maxHammingDistance = sys.float_info.min
    minSolution1 = 0.0
    minSolution2 = 0.0
    
    fitnessList = []
    
    for solution1 in solutions:
        for solution2 in solutions:
            tempHammingDistance = hamming(list(float_to_bin(solution1)), list(float_to_bin(solution2)))
            if(tempHammingDistance > maxHammingDistance and solution1 != solution2):
                maxHammingDistance = tempHammingDistance
                minSolution1 = solution1   
                minSolution2 = solution2
                fitnessList.append(tempHammingDistance)
    
    fAverageList.append(sum(fitnessList)/len(fitnessList))
    fMaxList.append(max(fitnessList))
    fMinList.append(min(fitnessList))
    
    fitnessList.clear()
    
    bestSolutions.append(minSolution1)
    bestSolutions.append(minSolution2)
    
    return bestSolutions


#Crossover is currently looking for max solutions
def Crossover(solution1, solution2):
    if(randint(1,100)/100 > crossoverRate):
        #Sets float solutions to 32 bit binary strings
        binSol1 = float_to_bin(solution1)
        binSol2 = float_to_bin(solution2)
    
        #Make new var out of the first half of the first solution and the second half of the second solution
        if(solution1 >= solution2):
            newBinSol = binSol1[:16] + binSol2[16:]
            newSolution = bin_to_float(newBinSol)
    
            return newSolution
    
        else:
            newBinSol = binSol2[:16] + binSol1[16:]
            newSolution = bin_to_float(newBinSol)
    
            return newSolution
    else:
        return solution1
    
def Mutate(solution):
    if(randint(1,100)/100 > mutationRate):
        solutionBin = float_to_bin(solution)
        
        solutionList = list(solutionBin)
        randomIndex = randint(16, 31)
        
        if(solutionList[randomIndex] == "1"):
            solutionList[randomIndex]  == "0"
            
        elif(solutionList[randomIndex] == "0"):
            solutionList[randomIndex]  == "1"
            
        return "".join(solutionList)
        
    else:
        return solution

#Clean population to start with new solutions
def CleanPopulation(variables, solutions):
    maxSolution = max(solutions)
    solutions.clear()
    solutions.append(maxSolution)
    variables.clear()
    GenerateRandomSolutions(variables, solutions)

def Sharing(variables, solutions):
    #Crossover event   
    bestSolutions = DetermineBest(solutions)
     
    newSolution = Crossover(bestSolutions[0], bestSolutions[1])
    
    solutions.append(newSolution)
    
    #Mutate event
    Mutate(newSolution)
    
    #Clean population event
    CleanPopulation(variables, solutions)
    bestSolutions.clear()

variables = []
solutions = []

#Initial population generation (size is 20)
GenerateRandomSolutions(variables, solutions)

originalSolutions = solutions.copy()

tempSolutions = DetermineBest(solutions)

count = 1

maxOriginalSolution = max(solutions)

while(count < (numOfGenerations-1)):
    
    Sharing(variables, solutions)    
    
    count = count + 1

tempSolutions = DetermineBest(solutions)

print("\nMax original solution: ", maxOriginalSolution)
print("\nMax final solution: ", max(solutions))

# print("\nAverage Fitness List: ", fAverageList[19])
# print("\nMax Fitness List: ", fMaxList[19])
# print("\nMin Fitness List: ", fMinList[19])

# print(fAverageList[19],"\t",fMaxList[19],"\t",fMinList[19])
# print(fMaxList[19])
# print(fMinList[19])

generationList = [x for x in range(1, numOfGenerations+1)]

import matplotlib.pyplot as plt
import numpy as np

plt.plot(list(range(len(fAverageList))), fAverageList, color='b', label='Average cost')
plt.plot(list(range(len(fMinList))), fMinList, color='g', label='Min cost')
plt.plot(list(range(len(fMaxList))), fMaxList, color='r', label='Max cost')
plt.title("M1 Generation vs Fitness")
plt.xlabel('Iteration')
plt.ylabel('Path cost')
plt.legend()
plt.show()

# plt.bar(generationList, fAverageList, color='green')
# plt.xlabel("Generation")
# plt.ylabel("Average Fitness")
# plt.title("M4 Sharing Generation vs Average Fitness")
# plt.show()

# plt.bar(generationList, fMaxList, color='green')
# plt.xlabel("Generation")
# plt.ylabel("Max Fitness")
# plt.title("M4 Sharing Generation vs Max Fitness")
# plt.show()

# plt.bar(generationList, fMinList, color='green')
# plt.xlabel("Generation")
# plt.ylabel("Min Fitness")
# plt.title("M4 Sharing Generation vs Min Fitness")
# plt.show()

populationList = [x for x in range(1, populationSize+1)]

plt.scatter(np.array(populationList), np.array(originalSolutions), color = "b")
plt.scatter(np.array(populationList), np.array(solutions), color = "r")
plt.title("M1 Generation vs Population")
plt.xlabel("Population")
plt.ylabel("Solution")

plt.show()