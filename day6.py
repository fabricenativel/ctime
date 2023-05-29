from collections import defaultdict
import fileinput
import re

# parse the lines into `(x, y)` tuples
points = [tuple(map(int, re.findall(r'\d+', x))) for x in fileinput.input()]

# find the min / max bounds of all points
x0, x1 = min(x for x, y in points), max(x for x, y in points)
y0, y1 = min(y for x, y in points), max(y for x, y in points)

# manhattan distance function
def dist(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)

# part 1
counts = defaultdict(int)
infinite = set()
# iterate over all cells in the bounding box
for y in range(y0, y1 + 1):
    for x in range(x0, x1 + 1):
        # at this cell, find the distance to every point
        # sort the result by distance
        ds = sorted((dist(x, y, px, py), i) for i, (px, py) in enumerate(points))
        # if the 1st and 2nd points are not the same distance
        # then we don't have a tie, and this cell will count
        if ds[0][0] != ds[1][0]:
            counts[ds[0][1]] += 1
            # assume points along the perimeter will extend infinitely
            if x == x0 or y == y0 or x == x1 or y == y1:
                infinite.add(ds[0][1])
# discard all infinite regions
print(infinite)
for k in infinite:
    counts.pop(k)
# print the maximal area
print(max(counts.values()))

# part 2
count = 0
# iterate over all cells in the bounding box
for y in range(y0, y1 + 1):
    for x in range(x0, x1 + 1):
        # sum up the distance to all points from this cell
        # increment our counter if the sum is less than 10000
        if sum(dist(x, y, px, py) for px, py in points) < 10000:
            count += 1
print(count)