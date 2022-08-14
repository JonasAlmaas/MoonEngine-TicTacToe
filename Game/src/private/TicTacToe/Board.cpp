#include "pch.h"
#include "TicTacToe/Board.h"


namespace TicTacToe {

	void Board::Reset()
	{
		m_BitMap = 0;
	}

	bool Board::Evaluate(Team team)
	{
		// Check -
		for (unsigned int y = 0; y < 3; y++)
		{
			unsigned int fullRowMask = 0b111111 << (y * 6);
			unsigned int compMask = (bool)team ? 0b111111 << (y * 6) : 0b010101 << (y * 6);

			if ((m_BitMap & fullRowMask) == compMask)
				return true;
		}

		// Check |
		for (unsigned int x = 0; x < 3; x++)
		{
			unsigned int fullColMask = 0b11000011000011 << (x * 2);
			unsigned int compMask = (bool)team ? 0b11000011000011 << (x * 2) : 0b01000001000001 << (x * 2);

			if ((m_BitMap & fullColMask) == compMask)
				return true;
		}

		// Check \ 
		{
			unsigned int fulldidMask = 0b110000001100000011;
			unsigned int compMask = (bool)team ? 0b110000001100000011 : 0b010000000100000001;

			if ((m_BitMap & fulldidMask) == compMask)
				return true;
		}

		// Check /
		{
			unsigned int fulldiuMask = 0b11001100110000;
			unsigned int compMask = (bool)team ? 0b11001100110000 : 0b01000100010000;

			if ((m_BitMap & fulldiuMask) == compMask)
				return true;
		}

		return false;
	}

	bool Board::IsFull()
	{
		return (m_BitMap & 0b010101010101010101) == 0b010101010101010101;
	}

	bool Board::IsCellEmpty(uint8_t x, uint8_t y)
	{
		uint32_t index = y * 3 + x;
		return BIT_VALUE(m_BitMap, index * 2) == 0;
	}

	bool Board::IsCellEmpty(uint32_t index)
	{
		return BIT_VALUE(m_BitMap, index * 2) == 0;
	}

	void Board::SetCell(uint8_t x, uint8_t y, Team team)
	{
		uint32_t index = y * 3 + x;
		m_BitMap |= BIT_MASK(index * 2);
		if (team == Team::O)
			m_BitMap |= BIT_MASK(index * 2 + 1);
	}

	void Board::SetCell(uint32_t index, Team team)
	{
		m_BitMap |= BIT_MASK(index * 2);
		if (team == Team::O)
			m_BitMap |= BIT_MASK(index * 2 + 1);
	}

	Team Board::GetTeam(uint8_t x, uint8_t y)
	{
		uint32_t index = y * 3 + x;
		return (Team)(BIT_VALUE(m_BitMap, index * 2 + 1) != 0);
	}

	Team Board::GetTeam(uint32_t index)
	{
		return (Team)(BIT_VALUE(m_BitMap, index * 2 + 1) != 0);
	}

}
