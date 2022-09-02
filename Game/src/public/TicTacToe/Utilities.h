#pragma once

using namespace Moon;


namespace TicTacToe {

	enum class GameMode : bool
	{
		SinglePlayer,
		TwoPlayer,
		AIvAI,
	};

	enum class GameState : bool
	{
		Running,
		Over,
	};

	enum class Team : bool
	{
		X, O,
	};

	enum class Difficulty : uint8_t
	{
		Easy,			// Random
		Medium,			// Minimax with 50% randomness
		Hard,			// Minimax with 10% randomness
		Impossible,		// Minimax with 0% randomness
	};

	struct Score
	{
		uint32_t X = 0;
		uint32_t O = 0;
		uint32_t Tie = 0;
	};

	struct BoardStyle
	{
		float BoardSize;
		float BoardLineWidth;
		float BoardLineRadius;

		float CellSize;
		float HalfCellSize;
		float InnerCellSize;
		float HalfInnerCellSize;

		float XLineWidth;
		float XLineRadius;
		float CircleThickness;

		float TextSizeSmall;
		float TextSizeBig;
		float TextSizeTitle;

		Color BackgroundColor;
		Color WhiteColor;
		Color GreenColor;
		Color RedColor;
		Color BlueColor;
	};

}
