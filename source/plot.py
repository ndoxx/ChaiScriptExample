#!/usr/bin/python3

import sys, json
from matplotlib import cm
import matplotlib.pyplot as plt
import numpy as np

def get_data(filepath):
	# Read json file and parse it
	with open(filepath, 'r') as file:
		data = json.loads(file.read())

	dt = float(data['dt'])

	Ents = []
	for ii, entity in enumerate(data['entities']):
		X = []
		Y = []
		for pos in entity['position']:
			X.append(pos[0])
			Y.append(pos[1])

		Ents.append([np.array(X),np.array(Y)])

	return (dt, Ents)

def main(argv):
	dt, data = get_data("data.json")
	numpoints = len(data[0][0])
	numents = len(data)

	time = np.arange(0, numpoints*dt, dt)

	print("dt: " + str(dt))
	print("np: " + str(numpoints))
	print("ne: " + str(numents))

	fig = plt.figure()
	ax = fig.add_subplot(1, 1, 1)
	ax.grid(True, which='both')

	for ii, pos in enumerate(data):
		ax.plot(pos[0], pos[1], marker='o', markersize=3, c=cm.Spectral(ii/(numents-1)))

	plt.show()

if __name__ == '__main__':
    main(sys.argv[1:])