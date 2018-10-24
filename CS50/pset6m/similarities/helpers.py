from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    cost = [[(0, None) for x in range(len(b) + 1)] for y in range(len(a) + 1)]
    for i in range(1, len(a) + 1):
        cost[i][0] = (i, Operation.DELETED)
    for j in range(1, len(b) + 1):
        cost[0][j] = (j, Operation.INSERTED)
    for i in range(1, len(a) + 1):
        for j in range(1, len(b) + 1):
            delcost, t = cost[i - 1][j]
            inscost, t = cost[i][j - 1]
            subcost, t = cost[i - 1][j - 1]
            delcost += 1
            inscost += 1
            if a[i - 1] != b[j - 1]:
                subcost += 1
            if (delcost, ) <= (inscost, ) and (delcost, ) <= (subcost, ):
                cost[i][j] = (delcost, Operation.DELETED)
            elif (inscost, ) <= (delcost, ) and (inscost, ) <= (subcost, ):
                cost[i][j] = (inscost, Operation.INSERTED)
            elif (subcost, ) == cost[i - 1][j - 1]:
                cost[i][j] = (subcost, None)
            else:
                cost[i][j] = (subcost, None)
    return cost