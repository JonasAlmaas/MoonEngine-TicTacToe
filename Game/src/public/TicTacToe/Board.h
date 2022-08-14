#pragma once

#include "TicTacToe/Utilities.h"


namespace TicTacToe {

	class Board
	{
	public:
		Board() = default;

		void Reset();

		// Returns true if the last move was a winning move.
		bool Evaluate(Team team);
		bool IsFull();

		bool IsEmptyCell(uint8_t x, uint8_t y);
		bool IsEmptyCell(uint32_t index);

		void SetCell(uint8_t x, uint8_t y, Team team);
		void SetCell(uint32_t index, Team team);

		Team GetTeam(uint8_t x, uint8_t y);
		Team GetTeam(uint32_t index);

	private:
		uint32_t m_BitMap = 0;

	};

}
