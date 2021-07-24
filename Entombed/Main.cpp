#include "stdafx.h"
#include "Entombed.h"

int main()
{
	std::srand((unsigned int)std::time(0));
	std::vector<unsigned int> rows = { 128, 128, 128, 128 };
	Entombed m = Entombed();
	while (true)
	{
		m.rowGen(rows);
		for (auto r : rows) {
			std::cout << m.render_line(r) << std::endl;
		}
		system("pause");
	}

	return 0;
}