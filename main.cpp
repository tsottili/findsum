#include <stdio.h>
#include <vector>
#include <iostream>
#include <list>
#include <stdlib.h>

std::list<int> current_sequence;
int best_number = 8;

// Print the sequence when found
// a sequence is printed only if it's better (shorter) than the previous one
void sequence_found()
{
	int tmp = current_sequence.size() -1;
	if (tmp < best_number)
		best_number = tmp;
		
	std::cout << "Sequence:"; 
	for (auto&& i: current_sequence)
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
}

// Examine all the sequence searching the best sequence.
// v = operands vector
// actual_value = current sequence actual sum
// target = target value.
// level = recursion level. (same as current_sequence.size()...)
// last_value = last examined value (to cut some branch and ddon't visit them twice).
bool search_sum_sequence(std::vector<int> v, int actual_value, int target, int level, int last_value)
{
	// It's longer than the previous one, stop.
	if (level >= best_number)
		return false;
			
	for(auto&& i: v)
	{				
		// current value is larger than the previous one, stop. We've checked this sequence some calls ago.
		if  (i > last_value)
			continue;
		
		// Add element to current sequence
		current_sequence.push_back(i);
		
		// Too big! stop-
		if (actual_value + i > target)
		{
			current_sequence.pop_back();
			return false;
		}
		
		if (actual_value + i == target)
		{
			sequence_found();
			current_sequence.pop_back();
			return true;
		}
				
		// Recurse the call.
		search_sum_sequence(v, actual_value + i, target, level + 1, i);
		
		// Remove actual element to the sequence
		current_sequence.pop_back();
	}	
	
	return false;
}



int main(int argc, char **argv)
{

	// No arguments, no game.
	if (argc == 1)	
	{
		std::cout << "Syntax: findsum targetvalue operands_list" << std::endl;
		std::cout << "Example: findsum 13 5 4 3" << std::endl;
		std::cout << "Output: Target value is: 13\nOperands are: 5 4 3\nSequence: 5 4 4" << std::endl;

		return -1;
	}	
	
	std::vector<int> vOperands;
	 
	// the first parameter after command is the target value
	int target = atoi(argv[1]);
	
	// No second parameters (use default: foe house population)
	if (argc == 2)
	{
		vOperands.push_back(1380);
		vOperands.push_back(1330);
		vOperands.push_back(1087);	
		vOperands.push_back(900);
		vOperands.push_back(680);
		vOperands.push_back(510);
		vOperands.push_back(474);
		vOperands.push_back(380);
		vOperands.push_back(285);
		vOperands.push_back(259);
		vOperands.push_back(207);
		vOperands.push_back(205);
		vOperands.push_back(156);
		vOperands.push_back(155);
		vOperands.push_back(123);
		vOperands.push_back(111);
		vOperands.push_back(94);
		vOperands.push_back(73);
		vOperands.push_back(67);
		vOperands.push_back(44);
		vOperands.push_back(32);
		vOperands.push_back(27);
		vOperands.push_back(22);
		vOperands.push_back(14);
	}
	else
	{
		// second and followinf arguments: list of operands.
		for (int i = 2; i < argc; i++ )
		{
			int iVal = atoi(argv[i]);
			vOperands.push_back(iVal);
		}
	}
	
	std::cout << "Target value is: " << target << std::endl;
	std::cout << "Operands are:";
	for (auto&& i: vOperands)
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
	
	// Search the sequence!
	for(auto&& i: vOperands)
	{
		current_sequence.push_back(i);
		search_sum_sequence(vOperands, i, target, 1, i);
		current_sequence.pop_back();
	}
	
	if (best_number == 0)
	{
		std::cout << "No sequence found." << std::endl;
	}
	
	return 0;
}
