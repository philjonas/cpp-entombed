#include "Entombed.h"

Entombed::Entombed()
{
}


Entombed::~Entombed()
{
}

unsigned int Entombed::getRandomBit() {
	return rand() % 2;
}

void Entombed::rowGen(std::vector<unsigned int> &lastrows) {
	size_t last_index = lastrows.size() - 1;
	// prepend and  append randombits  to last   row
	unsigned int lastrowpadded = getRandomBit();
	lastrowpadded <<= 8;
	lastrowpadded |= lastrows[last_index];
	lastrowpadded <<= 1;
	lastrowpadded |= getRandomBit();
	// last   two  bits  generatedin currentrow, initialvalue = 10
	unsigned int lasttwo = 0b10;
	unsigned int newrow = 0;
	// iteratefrom  7...0, inclusive
	for (int i = 7; i > -1; i--)
	{
		unsigned int threeabove = (lastrowpadded >> i) & 0b111;
		int newbit = MAGIC(lasttwo, threeabove);
		if (newbit == RANDOM_WALL) {
			newbit = getRandomBit();
		}
		newrow = (newrow << 1) | (unsigned int)newbit;
		lasttwo = ((lasttwo << 1) | (unsigned int)newbit) & 0b11;
	}

	// now  do postprocessing
	// add last row
	lastrows.push_back(newrow);
	// keep array 12 units long
	if (lastrows.size() > 12) { 
		lastrows.erase(lastrows.begin()); 
	}
	last_index = lastrows.size() - 1;

	// postprocessing condition 1
	std::vector<unsigned int> history;
	for (auto b : lastrows) {
		history.push_back(b & 0xf0);
	}
	if (!isZeroPresent(history)) {
		unsigned int hsum = 0;
		for (auto b : history) {
			hsum += b & 0x80;
		}
		if (hsum == 0) {
			lastrows.at(last_index) = 0;
		}
	}

	// postprocessing condition2
	// instead of all 12 rows, get only the last 7
	std::vector<unsigned int> history2;
	int first = ((int)last_index) - 6;
	if (first < 0) first = 0;
	for (size_t i = first; i <= last_index; i++)
	{
		history2.push_back(lastrows.at(i) & 0xf);
	}
	if (!isZeroPresent(history2)) {
		unsigned int comparator = 0;
		if (lastrows.size() >= 9) {
			comparator = lastrows.at(last_index - 8);
		}
		unsigned int csum = 0;
		for (auto b : history2) {
			csum += (b & 1);
		}
		unsigned int cmult = (comparator & 1) * 7;
		if (csum == cmult) {
			lastrows.at(last_index) &= 0xf0;
		}
	}
}

std::string Entombed::render_line(unsigned int row) {
	std::string PF12 = "";

	for (size_t i = 0; i < 8; i++)
	{
		if (row & 1) {
			PF12 = "X" + PF12;
		}
		else {
			PF12 = " " + PF12;
		}
		row >>= 1;
	}
	std::string PF012 = "X" + PF12;
	std::string mirrorPF012 = "";
	for (int n = ((int) PF012.length()) - 1; n >= 0; n--) {
		mirrorPF012.push_back(PF012[n]);
	}
	return PF012 + mirrorPF012;
}

bool Entombed::isZeroPresent(std::vector<unsigned int> lastrows) {
	for (auto b : lastrows) {
		if (b == 0) return true;
	}
	return false;
}

int Entombed::MAGIC(unsigned int lasttwo, unsigned int threeabove) {
	int response;
	lasttwo = lasttwo << 3;
	switch (lasttwo | threeabove)
	{
	case 0b00000:
		response = IS_WALL;
		break;
	case 0b00001:
		response = IS_WALL;
		break;
	case 0b00010:
		response = IS_WALL;
		break;
	case 0b00011:
		response = RANDOM_WALL;
		break;
	case 0b00100:
		response = NO_WALL;
		break;
	case 0b00101:
		response = NO_WALL;
		break;
	case 0b00110:
		response = RANDOM_WALL;
		break;
	case 0b00111:
		response = RANDOM_WALL;
		break;
	case 0b01000:
		response = IS_WALL;
		break;
	case 0b01001:
		response = IS_WALL;
		break;
	case 0b01010:
		response = IS_WALL;
		break;
	case 0b01011:
		response = IS_WALL;
		break;
	case 0b01100:
		response = RANDOM_WALL;
		break;
	case 0b01101:
		response = NO_WALL;
		break;
	case 0b01110:
		response = NO_WALL;
		break;
	case 0b01111:
		response = NO_WALL;
		break;
	case 0b10000:
		response = IS_WALL;
		break;
	case 0b10001:
		response = IS_WALL;
		break;
	case 0b10010:
		response = IS_WALL;
		break;
	case 0b10011:
		response = RANDOM_WALL;
		break;
	case 0b10100:
		response = NO_WALL;
		break;
	case 0b10101:
		response = NO_WALL;
		break;
	case 0b10110:
		response = NO_WALL;
		break;
	case 0b10111:
		response = NO_WALL;
		break;
	case 0b11000:
		response = RANDOM_WALL;
		break;
	case 0b11001:
		response = NO_WALL;
		break;
	case 0b11010:
		response = IS_WALL;
		break;
	case 0b11011:
		response = RANDOM_WALL;
		break;
	case 0b11100:
		response = RANDOM_WALL;
		break;
	case 0b11101:
		response = NO_WALL;
		break;
	case 0b11110:
		response = NO_WALL;
		break;
	case 0b11111:
		response = NO_WALL;
		break;
	default:
		break;
	}

	return response;
}
