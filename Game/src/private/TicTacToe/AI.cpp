#include "pch.h"
#include "TicTacToe/AI.h"

#include "TicTacToe/Board.h"


namespace TicTacToe {

	Difficulty AI::s_Difficulty = Difficulty::Impossible;
	
	void AI::SetDifficulty(Difficulty difficulty)
	{
		s_Difficulty = difficulty;
	}

	Board AI::MakeMove(Board board, Team playingTeam)
	{
		switch (s_Difficulty)
		{
			case Difficulty::Easy:
			{
				board = MakeMove_Random(board, playingTeam);
				break;
			}
			case Difficulty::Medium:
			{
				if (Random::Float() <= 0.5f)
					board = MakeMove_Random(board, playingTeam);
				else
					board = MakeMove_MiniMax(board, playingTeam);

				break;
			}
			case Difficulty::Hard:
			{
				if (Random::Float() <= 0.1f)
					board = MakeMove_Random(board, playingTeam);
				else
					board = MakeMove_MiniMax(board, playingTeam);

				break;
			}
			case Difficulty::Impossible:
			{
				board = MakeMove_MiniMax(board, playingTeam);
				break;
			}
		}

		return board;
	}

	Board AI::MakeMove_Random(Board board, Team playingTeam)
	{
		while (true)
		{
			uint8_t cellIndex = (uint8_t)Random::UInt16(0, 8);

			// Is cell clear
			if (board.IsEmptyCell(cellIndex))
			{
				board.SetCell(cellIndex, playingTeam);
				break;
			}
		}

		return board;
	}

	Board AI::MakeMove_MiniMax(Board board, Team playingTeam)
	{
		float bestBoardValue = -2.0f;
		Board bestBoard;

		for (uint8_t cellIndex = 0; cellIndex < 9; cellIndex++)
		{
			// Skip moves that can not be made
			if (!board.IsEmptyCell(cellIndex))
				continue;

			Board tempBoard(board);
			tempBoard.SetCell(cellIndex, playingTeam);

			float boardValue = MiniMax(tempBoard, playingTeam, -1.0f, 1.0f, false);

			if (boardValue > bestBoardValue)
			{
				bestBoardValue = boardValue;
				bestBoard = tempBoard;
			}
		}

		return bestBoard;
	}

	float AI::MiniMax(Board board, Team playingTeam, float alpha, float beta, bool maximizingPlayer)
	{
		// Other player wins
		if (board.Evaluate((Team)!(bool)playingTeam))
			return -1.0f;

		// Active plater wins ( This is what we want )
		if (board.Evaluate(playingTeam))
			return 1.0f;

		if (board.IsFull())
			return 0;

		if (maximizingPlayer)
		{
			float maxValue = -1.0f;

			for (uint8_t cellIndex = 0; cellIndex < 9; cellIndex++)
			{
				// Skip moves that can not be made
				if (!board.IsEmptyCell(cellIndex))
					continue;

				Board tempBoard(board);
				tempBoard.SetCell(cellIndex, playingTeam);

				float value = MiniMax(tempBoard, playingTeam, alpha, beta, false);
				maxValue = glm::max(maxValue, value);

				alpha = glm::max(alpha, value);
				if (beta <= alpha)
					break;
			}

			return maxValue;
		}
		else
		{
			float minValue = 1.0f;

			for (uint8_t cellIndex = 0; cellIndex < 9; cellIndex++)
			{
				// Skip moves that can not be made
				if (!board.IsEmptyCell(cellIndex))
					continue;

				Board tempBoard(board);
				tempBoard.SetCell(cellIndex, (Team)!(bool)playingTeam);

				float value = MiniMax(tempBoard, playingTeam, alpha, beta, true);
				minValue = glm::min(minValue, value);

				beta = glm::min(beta, value);
				if (beta <= alpha)
					break;
			}

			return minValue;
		}
	}

}
