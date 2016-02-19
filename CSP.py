# Python version: 2.7

from collections import defaultdict
import sys

# Constants
CONST_DELIMITER = "##### - "
VARIABLES = "variables"
VALUE = "values"
FITTING_LIMITS = "fitting limits"
UNARY_INCLUSIVE = "unary inclusive"
UNARY_EXCLUSIVE = "unary exclusive"
BINARY_EQUALS = "binary equals"
BINARY_NOT_EQUALS = "binary not equals"
BINARY_SIMULTANEOUS = "binary simultaneous"

# Counts how many constraints each variable has
def CountConstraints(information):
	varConstraints = {}
	
	for variable in information[VARIABLES]:
		# Add value to dictionary
		if variable[0] not in varConstraints:
			varConstraints[variable[0]] = 0

		# Counts unary inclusive constraints
		varConstraints[variable[0]] += sum(var.count(variable[0]) for var in information[UNARY_INCLUSIVE])
		# Counts unary exclusive constraints
		varConstraints[variable[0]] += sum(var.count(variable[0]) for var in information[UNARY_EXCLUSIVE])
		# Counts binary equals constraints
		varConstraints[variable[0]] += sum(var.count(variable[0]) for var in information[BINARY_EQUALS])
		# Counts binary not equals constraints
		varConstraints[variable[0]] += sum(var.count(variable[0]) for var in information[BINARY_NOT_EQUALS])
		# Counts binary simultaneous constraints
		varConstraints[variable[0]] += sum(var.count(variable[0]) for var in information[BINARY_SIMULTANEOUS])

	return varConstraints

def CSP(filename):
	fp = open(filename, "r")
	information = defaultdict(list)

	# Parses through input file and splits data into different sections
	for data in fp:
		if CONST_DELIMITER in data:
			key = data.split(CONST_DELIMITER)[1].rstrip()
			information[key].append(" ")
		else:
			if information[key].count(" "):
				information[key].remove(" ")
			information[key].append(data.rstrip().split(" "))

	variables = zip(*information[VARIABLES])
	variables = list(variables)
	varNames = variables[0]
	varWieghts = variables[1]
	bags = zip(*information[VALUE])
	bags = list(bags)
	bagNames = bags[0]
	bagCapacity = bags[1]
	if(information[FITTING_LIMITS].count(" ")):
		minFit = 0
		maxFit = 100
	else:
		minFit = information[FITTING_LIMITS][0][0]
		maxFit = information[FITTING_LIMITS][0][1]
	
	varConstraints = CountConstraints(information)
	
	# print (information[VARIABLES])
	# print (information[VALUE])
	print (information)
	print varConstraints

if __name__ == '__main__':
	if len(sys.argv) == 2:
		filename = sys.argv[1]
	else:
		print("Usage is: py CSP.py filename")
		sys.exit(0)
	
	CSP(filename)