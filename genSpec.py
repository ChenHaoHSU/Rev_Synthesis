import itertools

perms = list(map(",".join, itertools.permutations('01234567')))

for i in range(len(perms)):
   fout = open('allcase/'+str(i)+'.spec', 'w')
   fout.write(perms[i])
   fout.close()
