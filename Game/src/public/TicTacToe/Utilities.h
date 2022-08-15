#pragma once

using namespace Moon;


namespace TicTacToe {

	enum class GameMode : bool
	{
		SinglePlayer,
		TwoPlayer,
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
