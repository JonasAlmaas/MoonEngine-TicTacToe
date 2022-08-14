#include "pch.h"
#include "TicTacToe/GameLayer.h"


namespace TicTacToe {

	GameLayer::GameLayer()
		: Layer("GameLayer")
	{
		m_Style.BoardSize = 0.5f;
		m_Style.BoardLineWidth = 0.005f;
		m_Style.BoardLineRadius = m_Style.BoardLineWidth * 0.5f;

		m_Style.CellSize = m_Style.BoardSize / 3.0f;
		m_Style.HalfCellSize = m_Style.CellSize * 0.5f;
		m_Style.InnerCellSize = m_Style.CellSize * 0.8f;
		m_Style.HalfInnerCellSize = m_Style.InnerCellSize * 0.5f;

		m_Style.XLineWidth = 0.02f;
		m_Style.XLineRadius = m_Style.XLineWidth * 0.5f;
		m_Style.CircleThickness = m_Style.XLineWidth * 2.0f / m_Style.InnerCellSize;

		m_Style.BackgroundColor = Color("#533747");
		m_Style.WhiteColor = Color("#FFEEE2");
		m_Style.GreenColor = Color("#7B9E89");
		m_Style.RedColor = Color("#DA667B");
		m_Style.BlueColor = Color("#6DB1BF");
	}

	void GameLayer::OnAttach()
	{
		// TODO: REMOVE!
		m_GameMode = GameMode::TwoPlayer;

		// Set up camera
		m_Camera = CreateRef<OrthographicCamera>(1.0f);
		auto [width, height] = Application::Get().GetWindow().GetSize();
		m_Camera->SetViewportSize((float)width, (float)height);

		m_Turn = (Team)Random::Bool();


		// Set up renderer
		RenderCommand::SetDepthTest(false);
		RenderCommand::SetClearColor(m_Style.BackgroundColor);
	}

	void GameLayer::OnUpdate(Timestep ts)
	{
		m_FrameTime = ts;
		RenderCommand::Clear();

		DrawBoard();
		//DrawScoreboard();
	}

	void GameLayer::DrawBoard()
	{
		Renderer2D::BeginScene(m_Camera);

		// Draw vertical lines
		{
			glm::vec2 p0 = { -m_Style.HalfCellSize, m_Style.CellSize + m_Style.HalfCellSize - m_Style.BoardLineRadius };
			glm::vec2 p1 = { p0.x, -m_Style.CellSize - m_Style.HalfCellSize + m_Style.BoardLineRadius };

			Renderer2D::DrawSprite({ p0.x, 0.0f }, { m_Style.BoardLineWidth, m_Style.BoardSize - m_Style.BoardLineWidth}, m_Style.WhiteColor);
			Renderer2D::DrawCircle(p0, m_Style.BoardLineRadius, 1.0f, 0.01f, m_Style.WhiteColor);
			Renderer2D::DrawCircle(p1, m_Style.BoardLineRadius, 1.0f, 0.01f, m_Style.WhiteColor);
		}

		{
			glm::vec2 p0 = { m_Style.HalfCellSize, m_Style.CellSize + m_Style.HalfCellSize - m_Style.BoardLineRadius };
			glm::vec2 p1 = { p0.x, -m_Style.CellSize - m_Style.HalfCellSize + m_Style.BoardLineRadius };

			Renderer2D::DrawSprite({ p0.x, 0.0f }, { m_Style.BoardLineWidth, m_Style.BoardSize - m_Style.BoardLineWidth }, m_Style.WhiteColor);
			Renderer2D::DrawCircle(p0, m_Style.BoardLineRadius, 1.0f, 0.01f, m_Style.WhiteColor);
			Renderer2D::DrawCircle(p1, m_Style.BoardLineRadius, 1.0f, 0.01f, m_Style.WhiteColor);
		}

		// Draw horizontal lines
		{
			glm::vec2 p0 = { -m_Style.CellSize - m_Style.HalfCellSize + m_Style.BoardLineRadius, m_Style.HalfCellSize };
			glm::vec2 p1 = { m_Style.CellSize + m_Style.HalfCellSize - m_Style.BoardLineRadius, p0.y };

			Renderer2D::DrawSprite({ 0.0f, p0.y }, { m_Style.BoardSize - m_Style.BoardLineWidth, m_Style.BoardLineWidth }, m_Style.WhiteColor);
			Renderer2D::DrawCircle(p0, m_Style.BoardLineRadius, 1.0f, 0.01f, m_Style.WhiteColor);
			Renderer2D::DrawCircle(p1, m_Style.BoardLineRadius, 1.0f, 0.01f, m_Style.WhiteColor);
		}

		{
			glm::vec2 p0 = { -m_Style.CellSize - m_Style.HalfCellSize + m_Style.BoardLineRadius, -m_Style.HalfCellSize };
			glm::vec2 p1 = { m_Style.CellSize + m_Style.HalfCellSize - m_Style.BoardLineRadius, p0.y };

			Renderer2D::DrawSprite({ 0.0f, p0.y }, { m_Style.BoardSize - m_Style.BoardLineWidth, m_Style.BoardLineWidth }, m_Style.WhiteColor);
			Renderer2D::DrawCircle(p0, m_Style.BoardLineRadius, 1.0f, 0.01f, m_Style.WhiteColor);
			Renderer2D::DrawCircle(p1, m_Style.BoardLineRadius, 1.0f, 0.01f, m_Style.WhiteColor);
		}

		// -- Draw Players --
		for (uint32_t cellIndex = 0; cellIndex < 9; cellIndex++)
		{
			if (!m_Board.IsEmptyCell(cellIndex))
			{
				float x = (float)(cellIndex % 3) * m_Style.CellSize - m_Style.CellSize;
				float y = (float)(cellIndex / 3) * -m_Style.CellSize + m_Style.CellSize;

				if (m_Board.GetTeam(cellIndex) == Team::X)
				{
					glm::vec2 p0 = {
						x - m_Style.HalfInnerCellSize + m_Style.XLineRadius,
						y + m_Style.HalfInnerCellSize - m_Style.XLineRadius,
					};

					glm::vec2 p1 = {
						x + m_Style.HalfInnerCellSize - m_Style.XLineRadius,
						y - m_Style.HalfInnerCellSize + m_Style.XLineRadius,
					};

					glm::vec2 p2 = {
						x + m_Style.HalfInnerCellSize - m_Style.XLineRadius,
						y + m_Style.HalfInnerCellSize - m_Style.XLineRadius,
					};

					glm::vec2 p3 = {
						x - m_Style.HalfInnerCellSize + m_Style.XLineRadius,
						y - m_Style.HalfInnerCellSize + m_Style.XLineRadius,
					};

					glm::vec2 distance = p0 - p1;
					float xLineLength = glm::length(distance);

					Renderer2D::DrawRotatedSprite({ x, y }, 45.0f, { m_Style.XLineWidth, xLineLength }, m_Style.WhiteColor);
					Renderer2D::DrawRotatedSprite({ x, y }, -45.0f, { m_Style.XLineWidth, xLineLength }, m_Style.WhiteColor);

					Renderer2D::DrawCircle(p0, m_Style.XLineRadius, 1.0f, 0.005f, m_Style.WhiteColor);
					Renderer2D::DrawCircle(p1, m_Style.XLineRadius, 1.0f, 0.005f, m_Style.WhiteColor);
					Renderer2D::DrawCircle(p2, m_Style.XLineRadius, 1.0f, 0.005f, m_Style.WhiteColor);
					Renderer2D::DrawCircle(p3, m_Style.XLineRadius, 1.0f, 0.005f, m_Style.WhiteColor);
				}
				else
				{
					Renderer2D::DrawCircle({ x, y }, m_Style.HalfInnerCellSize, m_Style.CircleThickness, 0.005f, m_Style.WhiteColor);
				}
			}
		}

		Renderer2D::EndScene();
	}

	void GameLayer::DrawScoreboard()
	{
	}

	// -- Event hanling --

	void GameLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(ME_BIND_EVENT_FN(GameLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(ME_BIND_EVENT_FN(GameLayer::OnWindowResizeEvent));
	}

	bool GameLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		switch (e.GetMouseButton())
		{
			case Mouse::Button0:
			{
				if (m_GameState == GameState::Over)
				{
					m_Board.Reset();
					m_GameState = GameState::Running;
					break;
				}

				uint32_t x = (uint32_t)Input::GetMouseX();
				uint32_t y = (uint32_t)Input::GetMouseY();

				uint32_t windowWidthPx = Application::Get().GetWindow().GetWidth();
				uint32_t windowHeightPx = Application::Get().GetWindow().GetHeight();

				uint32_t boardSizePx = (uint32_t)((float)windowHeightPx * m_Style.BoardSize);

				// Get board bounds
				uint32_t boardLeftPx = (windowWidthPx - boardSizePx) / 2;
				uint32_t boardRightPx = windowWidthPx - boardLeftPx;
				uint32_t boardTopPx = (windowHeightPx - boardSizePx) / 2;
				uint32_t boardBottomPx = windowHeightPx - boardTopPx;

				// Check if mouse click was withing the bounds on the board
				if (x > boardLeftPx && y > boardTopPx && x < boardRightPx && y < boardBottomPx)
				{
					// Ignore some clicks on the board
					if ((m_GameMode == GameMode::SinglePlayer && m_Turn != Team::X) || m_GameMode == GameMode::AIvsAI)
						break;

					float pixelsPerCell = (float)boardSizePx / 3.0f;

					uint32_t relX = x - boardLeftPx;
					uint32_t relY = y - boardTopPx;

					uint32_t cellX = (uint32_t)((float)relX / pixelsPerCell);
					uint32_t cellY = (uint32_t)((float)relY / pixelsPerCell);

					if (m_Board.IsEmptyCell(cellX, cellY))
					{
						m_Board.SetCell(cellX, cellY, m_Turn);

						// Checks if the last move was a winning move.
						if (m_Board.Evaluate(m_Turn))
						{
							if (m_Turn == Team::X)
								m_Score.X++;
							else
								m_Score.O++;

							ME_LOG("Player {} won!", (bool)m_Turn ? "O" : "X");
							m_GameState = GameState::Over;
						}
						else if (m_Board.IsFull())
						{
							ME_LOG("Stale mate, noone wins!");
							m_GameState = GameState::Over;
						}

						m_Turn = (Team)!(bool)m_Turn;
					}
				}

				break;
			}

		}

		return false;
	}

	bool GameLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		m_Camera->SetViewportSize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}
