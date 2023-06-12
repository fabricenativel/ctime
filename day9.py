from collections import deque
import fileinput
import re

num_players, num_marbles = 459, 72103

def solve(num_players, num_marbles):
    # initialize a double-ended queue with zero
    d = deque([0])
    # track score for each player
    scores = [0] * num_players
    for m in range(1, num_marbles + 1):
        if m % 23 == 0:
            d.rotate(7)
            scores[m % num_players] += m + d.pop()
            d.rotate(-1)
        else:
            d.rotate(-1)
            d.append(m)
    return max(scores)

print(solve(num_players, num_marbles))
print(solve(num_players, num_marbles * 100))