###########################
# 6.00.2x Problem Set 1: Space Cows

from ps1_partition import get_partitions
import time
from random import randint
import pylab

#================================
# Part A: Transporting Space Cows
#================================

def gen_cows(filename, weight = 10, words = 100):
    """
    Generates cows from a list of words attributing a weight to a word randomly.

    Parameters:
    filename - the name of datafile as string.
    weight - maximum weight of cows.
    words - number of words.

    Returns:
    a dictionary of cow name (string), weight (int) pairs
    """
    cow_dict = dict()

    f = open(filename, 'r')

    line = f.readline()
    line_data = line.split()
    for i in range(words):
        cow_dict[line_data[i]] = randint(1, weight)
    return cow_dict

def load_cows(filename):
    """
    Read the contents of the given file.  Assumes the file contents contain
    data in the form of comma-separated cow name, weight pairs, and return a
    dictionary containing cow names as keys and corresponding weights as values.

    Parameters:
    filename - the name of the data file as a string

    Returns:
    a dictionary of cow name (string), weight (int) pairs
    """

    cow_dict = dict()

    f = open(filename, 'r')

    for line in f:
        line_data = line.split(',')
        cow_dict[line_data[0]] = int(line_data[1])
    return cow_dict

class Cow(object):
    def __init__(self, name, weight):
        self.name = name
        self.weight = weight
    def getName(self):
        return self.name
    def getWeight(self):
        return self.weight
    def __str__(self):
        return self.name + ': ' + str(self.weight)

def cowSearch(cowList, weight):
    """
    Searches through a sorted list to give the cow with maximum wright within a constraint.

    Parameters:
    cowList - a list os cows (Cow)
    weight - weight limit (an int)

    Returns:
    A Cow.
    """
    if len(cowList) == 1 and cowList[0].getWeight() < weight:
        return cowList[0]
    elif cowList[len(cowList) // 2].getWeight() == weight:
        return cowList[len(cowList) // 2]
    elif cowList[len(cowList) // 2].getWeight() > weight:
        return cowSearch(cowList[:(len(cowList) // 2)], weight)
    elif cowList[len(cowList) // 2].getWeight() < weight:
        return cowSearch(cowList[(len(cowList) // 2):], weight)

def greedy_cow_transport(cows,limit=10):
    """
    Uses a greedy heuristic to determine an allocation of cows that attempts to
    minimize the number of spaceship trips needed to transport all the cows. The
    returned allocation of cows may or may not be optimal.
    The greedy heuristic should follow the following method:

    1. As long as the current trip can fit another cow, add the largest cow that will fit
        to the trip
    2. Once the trip is full, begin a new trip to transport the remaining cows

    Does not mutate the given dictionary of cows.

    Parameters:
    cows - a dictionary of name (string), weight (int) pairs
    limit - weight limit of the spaceship (an int)

    Returns:
    A list of lists, with each inner list containing the names of cows
    transported on a particular trip and the overall list containing all the
    trips
    """
    cowList = []
    for cow in cows:
        cowList.append(Cow(cow, cows[cow]))
    cowList.sort(key = Cow.getWeight)
    travel = []
    # Runs the ship until ther is no cow left
    while cowList != []:
        weight = 0
        trip =[]
        #Book trips while ther is still space
        while weight < limit:
            try:
                cow = cowSearch(cowList, limit - weight)
                weight += cow.getWeight()
                cowList.remove(cow)
                trip.append(cow.getName())
            except:
                break
        travel.append(trip)
    return travel

def brute_force_cow_transport(cows,limit=10):
    """
    Finds the allocation of cows that minimizes the number of spaceship trips
    via brute force.  The brute force algorithm should follow the following method:

    1. Enumerate all possible ways that the cows can be divided into separate trips
    2. Select the allocation that minimizes the number of trips without making any trip
        that does not obey the weight limitation

    Does not mutate the given dictionary of cows.

    Parameters:
    cows - a dictionary of name (string), weight (int) pairs
    limit - weight limit of the spaceship (an int)

    Returns:
    A list of lists, with each inner list containing the names of cows
    transported on a particular trip and the overall list containing all the
    trips
    """
    score = len(cows) + 1
    blist = []
    for i in get_partitions(cows): # parse all partitions
        bool = True
        for trip in i:                 # weight check
            weight = 0
            for cow in trip:
                weight += cows[cow]
            if weight > limit: #checks validity
                bool = False
                break
        if bool == True:
            if len(i) < score:
                score = len(i)
                blist = i
    return blist

def wgreedy_cow_transport(cows,limit=10):
    """
    Uses a greedy heuristic to determine an allocation of cows that attempts to
    minimize the number of spaceship trips needed to transport all the cows. The
    returned allocation of cows may or may not be optimal.
    The greedy heuristic should follow the following method:

    1. As long as the current trip can fit another cow, add the largest cow that will fit
        to the trip
    2. Once the trip is full, begin a new trip to transport the remaining cows

    Does not mutate the given dictionary of cows.

    Parameters:
    cows - a dictionary of name (string), weight (int) pairs
    limit - weight limit of the spaceship (an int)

    Returns:
    A list of lists, with each inner list containing the names of cows
    transported on a particular trip and the overall list containing all the
    trips
    """
    cowDict = cows.copy()
    travel = []
    # Runs the ship until ther is no cow left
    while cowDict != {}:
        weight = 0
        trip =[]
        #Book trips while ther is still space
        while weight < limit:
            bestCow = 0
            score = 0
            for cow in cowDict:
                if cowDict[cow] <= limit - weight and cowDict[cow] > score:
                    score = cowDict[cow]
                    bestCow = cow
            try:
                weight += cowDict[bestCow]
                cowDict.pop(bestCow)
                trip.append(bestCow)
            except:
                break
        travel.append(trip)
    return travel

def compare_cow_transport_algorithms():
    """
    Using the data from ps1_cow_data.txt and the specified weight limit, run your
    greedy_cow_transport and brute_force_cow_transport functions here. Use the
    default weight limits of 10 for both greedy_cow_transport and
    brute_force_cow_transport.

    Print out the number of trips returned by each method, and how long each
    method takes to run in seconds.

    Returns:
    Does not return anything.
    """
    numCows = []
    gtimes = []
    wgtimes = []
    for i in range(50, 300, 50):
        cows = gen_cows("randcow.txt", 10, i)
        numCows.append(i)
        x = time.time()
        wgreedy_cow_transport(cows)
        wg = time.time() - x
        wgtimes.append(wg)
        x = time.time()
        greedy_cow_transport(cows)
        gt = time.time() - x
        gtimes.append(gt)
    pylab.figure()
    pylab.plot(numCows, wgtimes)
    pylab.plot(numCows, gtimes)
    pylab.title("Algorithms vs. Time")
    pylab.legend(('Dumb Greedy', 'Greedy'))
    pylab.xlabel("Cows")
    pylab.ylabel("Seconds")
    pylab.show()

"""
Here is some test data for you to see the results of your algorithms with.
Do not submit this along with any of your answers. Uncomment the last two
lines to print the result of your problem.
"""

# cows = load_cows("ps1_cow_data.txt")
# t = time.time()
# inp = int(input("How many cows? "))
# cows = gen_cows("randcow.txt", 10, inp)
# tgen = time.time() - t
# print('It took ' + str(tgen) + ' seconds to generate cows.\nLoaded: ' + str(len(cows)))
# limit=10
# x = time.time()
# greedy_cow_transport(cows)
# gt = time.time() - x
# print(str(len(greedy_cow_transport(cows))) + ': ' + str(gt))
# x = time.time()
# wgreedy_cow_transport(cows)
# gt = time.time() - x
# print(str(len(wgreedy_cow_transport(cows))) + ': ' + str(gt))

# idea
# run algorithms when they do best e.g.
# if len(cows) < 100:
#     wgreedy_cow_transport(cows)
# else:
#     greedy_cow_transport(cows)

compare_cow_transport_algorithms()