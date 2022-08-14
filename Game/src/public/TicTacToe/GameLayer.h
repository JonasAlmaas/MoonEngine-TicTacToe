#pragma once

using namespace Moon;

#include "TicTacToe/Board.h"
#include "TicTacToe/Utilities.h"


namespace TicTacToe {

	class GameLayer : public Layer
	{
	public:
		GameLayer();
		virtual ~GameLayer() = default;

		virtual void OnAttach() override;
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& e) override;

	private:
		void DrawBoard();
		void DrawScoreboard();

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		Ref<OrthographicCamera> m_Camera;

		GameMode m_GameMode = GameMode::SinglePlayer;
		GameState m_GameState = GameState::Running;

		BoardStyle m_Style;
		Board m_Board;

		Team m_Turn = Team::X;
		Score m_Score;

		Ref<Font> m_FontSegoeUIBold, m_FontSegoeUISemiBold;

		float m_FrameTime = 0.0f;

	};

}
