import matplotlib.pyplot as pp
import numpy as np
from sys import argv

if len(argv) == 2:
	filename = argv[1]
else:
	filename = 'mess.txt'

N = []
vals = []

buff = open(filename)
line = buff.readline()
while line:
	SL_temp = line.split()
	SL = []
	for sl in SL_temp:
		SL.append(float(sl))
	N.append(SL[0])
	vals.append(SL[2:])
	line = buff.readline()

N = np.array(N)
vals = np.array(vals)

C = vals.shape[1]

leg = []

for i in range(C):
	pp.plot(N, vals[:,i],'.-')
	if(i == 0):
		leg.append('data')
	else:
		leg.append('theory'+str(i))

pp.legend(leg)
pp.grid()
pp.show()











