fin = open('size.log', 'r')

cnt = {}
total = 0
total_s = 0
for row in fin:
   size = int(row)
   total += 1
   total_s += size
   if size in cnt:
      cnt[size] += 1
   else:
      cnt[size] = 1

for i, v in cnt.items():
   print(i, ':', v)

print(total_s)
print('avg gate:', str(float(total_s)/40320.0))



fin = open('ctrl.log', 'r')
cnt = {}
total = 0
total_s = 0
for row in fin:
   size = int(row)
   total += 1
   total_s += size
   if size in cnt:
      cnt[size] += 1
   else:
      cnt[size] = 1

for i, v in cnt.items():
   print(i, ':', v)

print(total_s)
print('avg ctrl:', str(float(total_s)/40320.0))
