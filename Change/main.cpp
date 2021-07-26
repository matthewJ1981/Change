#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

//Check every value from 1 to 99 can be made by combining the coins
inline bool allAmounts(std::vector<int> coins_in)
{
	//Loop through every desired amount to the be made and verify it can be made with the available coins
	for (int i = 1; i < 100; ++i)
	{
		std::vector<int> coins = coins_in;
		bool made = false;
		int total = 0;
		int amount = 0;
		int current = 0;
		while (coins[0] + coins[1] + coins[2] + coins[3] > 0)
		{
			//Get coin amount;
			switch (current)
			{
			case 0:
				amount = 25;
				break;
			case 1:
				amount = 10;
				break;
			case 2:
				amount = 5;
				break;
			case 3:
				amount = 1;
				break;
			default:
				current = 0;
				amount = 0;
				break;
			}

			//If there is a coin remove it otherwise move to the next denomination
			//The while loop will exit when all coins have been removed
			if (coins[current] > 0)
			{
				coins[current]--;
			}
			else
			{
				current++;
				continue;
			}

			//Add the coin to the desired total 
			if (amount > 0 && amount + total <= i)
			{
				total += amount;
			}
			else
			{
				current++;
			}

			//Made the amount with the coins available
			if (total == i)
			{
				made = true;
				break;
			}


		}

		//Didnt make the amount 
		if (made == false)
			return false;
	}

	return true;
}

int main()
{
	//Find every combination of up to 10 of each coin
	std::vector<int> coins{ 0, 0, 0, 0 };
	std::vector<std::pair<std::vector<int>, int>> result;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			for (int k = 0; k < 10; ++k)
			{
				for (int l = 0; l < 9; ++l)
				{
					coins[3]++;
					//check if coin combination can make every amount from 1 to 99
					if (allAmounts(coins))
					{
						result.push_back({ coins, coins[0] + coins[1] + coins[2] + coins[3] });
					}
				}
				coins[3] = 0;
				coins[2]++;
			}
			coins[2] = 0;
			coins[1]++;
		}
		coins[1] = 0;
		coins[0]++;
	}

	//sort all coin combinations that make every amount by number of coins
	std::sort(result.begin(), result.end(), [](const auto& l, const auto& r) {
		return l.second < r.second;
		});

	std::cout << "The least amount of coins to always have correct change is " << result[0].second << "...\n";
	std::cout << result[0].first[0] << " Quarters\n";
	std::cout << result[0].first[1] << " Dimes\n";
	std::cout << result[0].first[2] << " Nickels\n";
	std::cout << result[0].first[3] << " Pennies\n";

	return 0;
}