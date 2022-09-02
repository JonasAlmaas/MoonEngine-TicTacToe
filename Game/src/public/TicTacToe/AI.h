#pragma once

#include "TicTacToe/Utilities.h"


namespace TicTacToe {

	class Board;

	/**
	 * This ai is only designed to have one computer player.
	 */
	class AI
	{
	public:
		static void SetDifficulty(Difficulty difficulty);
		static Difficulty GetDifficulty() { return s_Difficulty; };

		static Board MakeMove(Board board, Team playingTeam);

	private:
		static Board MakeMove_Random(Board board, Team playingTeam);
		static Board MakeMove_MiniMax(Board board, Team playingTeam);

		static float MiniMax(Board board, Team playingTeam, float alpha, float beta, bool maximizingPlayer);

	private:
		static Difficulty s_Difficulty;
	};

}
