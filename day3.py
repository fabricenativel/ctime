from collections import defaultdict
import fileinput
import re

# `ids` will map (x, y) tuples to the set of claim IDs that overlap that cell
ids = defaultdict(set)
for line in open("input3.txt"):
    # find, parse, and unpack every number in the string
    id, x, y, w, h = map(int, re.findall(r'\d+', line))
    # update `ids` for each cell in this claim
    for j in range(y, y + h):
        for i in range(x, x + w):
            ids[(i, j)].add(id)

# part 1
print(sum(len(x) > 1 for x in ids.values()))