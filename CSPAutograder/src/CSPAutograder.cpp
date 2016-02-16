
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <math.h>

struct Item {
	char name;
	int weight;
	char stored;
	std::set<char> allowed;
	std::set<char> forbidden;
	std::list<Item*> friends;
	std::list<Item*> enemies;
	std::vector<Item*> mutualFriends;
	std::vector<char> mutualA;
	std::vector<char> mutualB;
};

struct Bag {
	char name;
	int capacity;
	int max;
	int stored;
};

std::map<int,Item*> itemMap;
std::map<char,Item*> itemNames;
std::map<int,Bag*> bagMap;
std::map<char,Bag*> bagNames;
int low;
int high;

int main() {

	std::ifstream myReadFile;

	std::cout << "Put the name of the input file here, and make sure its within this project's directory."<< std::endl;
	std::cout << "For our given example, type in 'exampleInput.txt', which should be included."<< std::endl;
	std::string readFile;
	std::cin >> readFile;
	myReadFile.open(readFile.c_str());
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!                  Uncomment below and comment to manually enter your file location / name
	//myReadFile.open("exampleInput.txt");


	std::cout << " " << std::endl;

	// Input reader below
	if(myReadFile.is_open())
	{
		std::string input;
		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;

		int current=0;
		while(input!="#####") // Item (variables) loop
		{
			char myName;
			myName=input[0];
			int myWeight;
			myReadFile >> myWeight;

			itemMap[current]=new Item();
			itemMap[current]->name=myName;
			itemMap[current]->weight=myWeight;
			itemMap[current]->stored='-';
			itemNames[myName]=itemMap[current];

			current++;
			myReadFile >> input;
		}

		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;

		current=0;
		while(input!="#####") // Bags (values) loop
		{
			char myName;
			myName=input[0];
			int mySize;
			myReadFile >> mySize;

			bagMap[current]=new Bag();
			bagMap[current]->name=myName;
			bagMap[current]->capacity=mySize;
			bagMap[current]->max=mySize;
			bagMap[current]->stored=0;
			bagNames[myName]=bagMap[current];

			current++;
			myReadFile >> input;
		}

		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;

		low=0;
		high=999;
		if(input!="#####") // Low / high (fitting limits) check
		{
			low=atoi(input.c_str());
			myReadFile >> input;
			high=atoi(input.c_str());

			myReadFile >> input;
		}

		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;

		while(input!="#####") // Allowed (unary inclusive) loop
		{
			char myName;
			myName=input[0];

			char bagName;
			myReadFile >> input;
			bagName=input[0];

			while(input[0]!='#' && !isupper(input[0]))
			{
				itemNames[myName]->allowed.insert(bagName);
				myReadFile >> input;
				bagName=input[0];
			}
		}

		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;

		while(input!="#####") // Forbidden (unary exclusive) loop
		{
			char myName;
			myName=input[0];

			char bagName;
			myReadFile >> input;
			bagName=input[0];

			while(input[0]!='#' && !isupper(input[0]))
			{
				itemNames[myName]->forbidden.insert(bagName);
				myReadFile >> input;
				bagName=input[0];
			}
		}

		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;

		while(input!="#####") // friends (binary inclusive) loop
		{
			char myName;
			myName=input[0];

			char hisName;
			myReadFile >> input;
			hisName=input[0];

			itemNames[myName]->friends.push_back(itemNames[hisName]);
			itemNames[hisName]->friends.push_back(itemNames[myName]);

			myReadFile >> input;
		}

		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;

		while(input!="#####") // Enemies (binary exclusive) loop
		{
			char myName;
			myName=input[0];

			char hisName;
			myReadFile >> input;
			hisName=input[0];

			itemNames[myName]->enemies.push_back(itemNames[hisName]);
			itemNames[hisName]->enemies.push_back(itemNames[myName]);

			myReadFile >> input;
		}

		myReadFile >> input;
		myReadFile >> input;
		myReadFile >> input;
		std::string lastInput=input;
		myReadFile >> input;

		while(input!=lastInput) // Mutual friends (mutual exclusive) loop
		{
			char myName;
			myName=input[0];

			char hisName;
			myReadFile >> input;
			hisName=input[0];

			char bagOne;
			myReadFile >> input;
			bagOne=input[0];

			char bagTwo;
			myReadFile >> input;
			bagTwo=input[0];

			itemNames[myName]->mutualFriends.push_back(itemNames[hisName]);
			itemNames[myName]->mutualA.push_back(bagOne);
			itemNames[myName]->mutualB.push_back(bagTwo);
			itemNames[myName]->mutualFriends.push_back(itemNames[hisName]);
			itemNames[myName]->mutualA.push_back(bagTwo);
			itemNames[myName]->mutualB.push_back(bagOne);

			itemNames[hisName]->mutualFriends.push_back(itemNames[myName]);
			itemNames[hisName]->mutualA.push_back(bagOne);
			itemNames[hisName]->mutualB.push_back(bagTwo);
			itemNames[hisName]->mutualFriends.push_back(itemNames[myName]);
			itemNames[hisName]->mutualA.push_back(bagTwo);
			itemNames[hisName]->mutualB.push_back(bagOne);

			lastInput=input;
			myReadFile >> input;
		}

		myReadFile.close();
	}
	else
	{
		std::cout << "Couldn't read the input file?" << std::endl;
		return 0;
	}









	std::cout << "Put the name of your program's output file here, and make sure its within this project's directory as well."<< std::endl;
	std::cout << "For our given example, type in 'exampleOutput.txt', which should be included."<< std::endl;
	std::cin >> readFile;
	myReadFile.open(readFile.c_str());

	std::cout << " " << std::endl;

	//myReadFile.open("exampleOutput.txt");

	if(myReadFile.is_open())
	{
		std::string input;
		myReadFile >> input;

		unsigned int current=0;
		while(current<bagMap.size())
		{
			char bagName;
			bagName=input[0];

			if(bagNames.count(bagName)==0 || bagNames.find(bagName)==bagNames.end())
			{
				std::cout << "Output failed: Bag " << bagName << " isn't recognized from the inputs? Are you sure the output is formatted correctly?" << std::endl;
				return 0;
			}

			char itemName;
			myReadFile >> input;

			while(input!="number")
			{
				itemName=input[0];

				if(itemNames.count(itemName)==0 || itemNames.find(itemName)==itemNames.end())
				{
					std::cout << "Output failed: Item " << itemName << " isn't recognized from the inputs? Its supposedly in bag " << bagName << "!" << std::endl;
					return 0;
				}

				if(itemNames[itemName]->stored=='-')
				{
					itemNames[itemName]->stored=bagName;
				}
				else
				{
					std::cout << "Output failed: Item " << itemName << " is stored in multiple bags? Stored in " << itemNames[itemName]->stored << " and " << bagName << "!" << std::endl;
					return 0;
				}

				bagNames[bagName]->capacity-=itemNames[itemName]->weight;

				bagNames[bagName]->stored++;

				myReadFile >> input;
			}

			myReadFile >> input;
			myReadFile >> input;
			myReadFile >> input;
			myReadFile >> input;
			myReadFile >> input;
			myReadFile >> input;
			myReadFile >> input;
			myReadFile >> input;
			myReadFile >> input;
			myReadFile >> input;
			current++;
		}

		while(!myReadFile.eof())
		{
			myReadFile >> input;
		}
	}
	else
	{
		std::cout << "Couldn't read the output file?" << std::endl;
		return 0;
	}



























	unsigned int current=0;
	while(current < itemMap.size())
	{
		std::cout << "Item Name: " << itemMap[current]->name << std::endl;
		std::cout << "Weight: " << itemMap[current]->weight << std::endl;

		std::cout << "Stored in bag : " << itemMap[current]->stored << std::endl;
		if(itemMap[current]->stored=='-')
		{
			std::cout << "Output failed: Item " << itemMap[current]->name << " is not in a bag!" << std::endl;
			return 0;
		}

		if(!itemMap[current]->allowed.empty())
		{
			bool correct=false;
			for (std::set<char>::iterator it=itemMap[current]->allowed.begin(); it!=itemMap[current]->allowed.end(); ++it)
			{
				if((*it)==itemMap[current]->stored)
				{
					correct=true;
					break;
				}
			}
			if(!correct)
			{
				std::cout << "Output failed: Item " << itemMap[current]->name << " has unary inclusive values, but is stored in bag " << itemMap[current]->stored << " instead!" << std::endl;
				return 0;
			}
		}

		if(!itemMap[current]->forbidden.empty())
		{
			for (std::set<char>::iterator it=itemMap[current]->forbidden.begin(); it!=itemMap[current]->forbidden.end(); ++it)
			{
				if((*it)==itemMap[current]->stored)
				{
					std::cout << "Output failed: Item " << itemMap[current]->name << " has unary exclusive values, but is stored in bag " << itemMap[current]->stored << "!" << std::endl;
					return 0;
				}
			}
		}

		if(!itemMap[current]->friends.empty())
		{
			for (std::list<Item*>::iterator it=itemMap[current]->friends.begin(); it!=itemMap[current]->friends.end(); ++it)
			{
				if((*it)->stored!=itemMap[current]->stored)
				{
					std::cout << "Output failed: Item " << itemMap[current]->name << " is binary equals with " << (*it)->name << ", but " << itemMap[current]->name << " is stored in bag " << itemMap[current]->stored << " while " << (*it)->name << " is stored in bag " << (*it)->stored << "!" << std::endl;
					return 0;
				}
			}
		}

		if(!itemMap[current]->enemies.empty())
		{
			for (std::list<Item*>::iterator it=itemMap[current]->enemies.begin(); it!=itemMap[current]->enemies.end(); ++it)
			{
				if((*it)->stored==itemMap[current]->stored)
				{
					std::cout << "Output failed: Item " << itemMap[current]->name << " is binary not equals with " << (*it)->name << ", but they share the same bag " << itemMap[current]->stored << "!" << std::endl;
					return 0;
				}
			}
		}

		if(!itemMap[current]->mutualFriends.empty())
		{
			for(unsigned int i=0; i<itemMap[current]->mutualFriends.size(); ++i)
			{
				if(itemMap[current]->mutualFriends[i]->stored==itemMap[current]->mutualA[i] && itemMap[current]->stored!=itemMap[current]->mutualB[i])
				{
					std::cout << "Output failed: Item " << itemMap[current]->name << " is mutually inclusive with " << itemMap[current]->mutualFriends[i]->name << ", but " << itemMap[current]->name << " is in bag " << itemMap[current]->stored << " and " << itemMap[current]->mutualFriends[i]->name << " is in bag " << itemMap[current]->mutualFriends[i]->stored << "!" << std::endl;
					return 0;
				}
			}
		}

		std::cout << " " << std::endl;
		current++;
	}



	std::cout << "-------" << std::endl;

	current=0;
	while(current < bagMap.size())
	{
		std::cout << "Bag Name: " << bagMap[current]->name << std::endl;

		std::cout << "Capacity left: " << bagMap[current]->capacity << std::endl;
		if(bagMap[current]->capacity<0)
		{
			std::cout << "Output failed: Bag " << bagMap[current]->name << " is filled beyond capacity. Its overflowing by " << -bagMap[current]->capacity << " kg!" << std::endl;
			return 0;
		}

		if((bagMap[current]->max-bagMap[current]->capacity) < floor(bagMap[current]->max-(bagMap[current]->max*0.1)))
		{
			std::cout << "Output failed: Bag " << bagMap[current]->name << " is filled less than 90% capacity. Its currently holding " << bagMap[current]->max-bagMap[current]->capacity << " kg, but must be holding at least " << floor(bagMap[current]->max-(bagMap[current]->max*0.1)) << " kg!" << std::endl;
			return 0;
		}

		std::cout << "Total Items: " << bagMap[current]->stored << std::endl;
		if(bagMap[current]->stored < low)
		{
			std::cout << "Output failed: Minimum number of items per bag is " << low << ", but bag " << bagMap[current]->name << " only has " << bagMap[current]->stored << "!" << std::endl;
			return 0;
		}
		if(bagMap[current]->stored > high)
		{
			std::cout << "Output failed: Maximum number of items per bag is " << high << ", but bag " << bagMap[current]->name << " has " << bagMap[current]->stored << "!" << std::endl;
			return 0;
		}


		std::cout << " "<< std::endl;
		current++;
	}


	std::cout << "No problems! This works! The output is a correct solution."<< std::endl;

	return 0;
}
