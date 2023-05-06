with open("input1.txt") as reader:
    data = reader.read().strip().split('\n')

seen = set()
idx = 0
somme = 0
while somme not in seen:
    seen.add(somme)
    somme += int(data[idx])
    idx = (idx+1) % len(data)
print(somme)
