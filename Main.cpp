#include "stdafx.h"
#include "Entombed.h"

int main()
{
	std::srand((unsigned int)std::time(0));
	unsigned int init_data[] = { 128, 128, 128, 128 };
	std::vector<unsigned int> rows;
	for (size_t i = 0; i < 4; i++)
	{
		rows.push_back(init_data[i]);
	}
	
	Entombed m = Entombed();
	while (true)
	{
		m.rowGen(rows);
		for (size_t i = 0; i < rows.size(); i++)
		{
			std::cout << m.render_line(rows.at(i)) << std::endl;
		}
		system("pause");
	}

	return 0;
}