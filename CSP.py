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
BINARY_NOT_EQUALS = "binary nont equals"
BINARY_SIMULTANEOUS = "binary simultaneous"

def CSP(filename):
	fp = open(filename, "r")
	information = defaultdict(list)

	# Parses through input file and splits data into different sections
	for data in fp:
		if CONST_DELIMITER in data:
			key = data.split(CONST_DELIMITER)[1].rstrip()
		else:
			information[key].append(data.rstrip().split(" "))
	# print information

if __name__ == '__main__':
	if len(sys.argv) == 2:
		filename = sys.argv[1]
	else:
		print("Usage is: py CSP.py filename")
		sys.exit(0)
	
	CSP(filename)