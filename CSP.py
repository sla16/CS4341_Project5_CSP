# Python version: 2.7

from collections import defaultdict
from operator import itemgetter
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

# Global
information = defaultdict(list)

# Counts how many constraints each variable has
def CountConstraints(information):
	varConstraints = defaultdict(list)
	
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

		varConstraints[variable[0]]

	return varConstraints

# Helper function to check if we have a solution
def CheckSolution(solution, numVar, minFit):
	# TODO: check if solution has ALL variables + constraints met + bags are okay and stuff
	countOfVar = 0
	# Count number of variables (to make sure all variables are used)
	for bag in solution:
		countOfVar += (len(bag) - 2)
	if numVar != countOfVar:
		return False



	return True

# Checks the variable and see if it satisfies the constraints
def CheckConstraints(var, var_weight, bag, maxFit, solution):
	tempBag = list(bag)
	tempBag.append(var)
	tempBag[1] = (int(tempBag[1]) - var_weight)

	# If number of items in bag violates max fit, wrong bag
	if (2 - len(tempBag)) > maxFit:
		return False
	# If capacity exceeded, wrong bag
	if tempBag[1] < 0:
		return False
	# Check what bag the variable MUST belong to, if it has this constraint
	for constraints in information[UNARY_INCLUSIVE]:
		if var in constraints and bag[0] not in constraints:
			return False
	# Check what bag the variable MUST NOT belong to, if it has this constraint
	for constraints in information[UNARY_EXCLUSIVE]:
		if var in constraints and bag[0] in constraints:
			return False
	# Check binary equals constraint
	for constraints in information[BINARY_EQUALS]:
		if var in constraints and ConstraintInSolution(constraints, solution):
			if bag[0] != ConstraintBag(constraints, solution):
				return False
	# Check binary not equals constraint
	for constraints in information[BINARY_NOT_EQUALS]:
		if var in constraints and ConstraintInSolution(constraints, solution):
			if bag[0] == ConstraintBag(constraints, solution):
				return False
	# TODO: binary simultaneous/mutual inclusive
	return True

# Helper function to check if variable solved already
def InSolution(var, solution):
	for data in solution:
		if var in data:
			return True
	return False

def SolutionBag(var, solution):
	for data in solution:
		if var in data:
			return data[0]
	return None

def ConstraintBag(constraints, solution):
	for var in constraints:
		if InSolution(var, solution):
			return SolutionBag(var, solution)
	return None

def ConstraintInSolution(constraints, solution):
	for var in constraints:
		if InSolution(var, solution):
			return True
	return False

# Helper function to map a variable to its value
def GetVarWeight(var, var_info):
	return int(var_info[1][var_info[0].index(var)])

# Helper function to map a bag to its capacity
def GetBagCapacity(bag, bag_info):
	return int(bag_info[1][bag_info[0].index(bag)])

# Back tracking search algorithm
def BacktrackingSearch(variables, var_info, solution, minFit, maxFit):
	# print variables
	# print var_info
	# print solution

	if(CheckSolution(solution, len(variables), minFit)):
		return solution
	else:
		for var in variables:
			if not InSolution(var, solution):
				for bag in solution:
					var_weight = GetVarWeight(var, var_info)
					if(CheckConstraints(var, var_weight, bag, maxFit, solution)):
						# Variable fits the constraints, put it into the bag
						bag.append(var)
						bag[1] = (int(bag[1]) - var_weight)
						updatedSolution = BacktrackingSearch(variables, var_info, solution, minFit, maxFit)
						if updatedSolution is not None:
							return updatedSolution
						else:
							del bag[-1]
				return None

def CSP(filename):
	global information
	fp = open(filename, "r")

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
	varWeights = variables[1]
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
	varConstraints = sorted(varConstraints.items(), key = itemgetter(1))[::-1]
	varConstraints = zip(*varConstraints)

	# print (information[VALUE])
	# print (information)
	solution = BacktrackingSearch(varConstraints[0], variables, information[VALUE], minFit, maxFit)
	for bag in solution:
		totalWeight = 0
		bagCapacity = 0
		for item in bag:
			if type(item) is not int:
				if item.isupper():
					totalWeight += GetVarWeight(item, variables)
				if item.islower():
					bagCapacity = GetBagCapacity(item, bags)
				print item,
		wastedCapacity = bagCapacity - totalWeight
		print "\nnumber of items: ", len(bag)-2
		print "total weight: ", totalWeight, "/", bagCapacity
		print "wasted capacity: ", wastedCapacity, "\n"
	print solution

if __name__ == '__main__':
	if len(sys.argv) == 2:
		filename = sys.argv[1]
	else:
		print("Usage is: py CSP.py filename")
		sys.exit(0)
	
	CSP(filename)