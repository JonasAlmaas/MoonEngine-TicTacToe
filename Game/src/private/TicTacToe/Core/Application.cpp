#include "pch.h"
#include "TicTacToe/Core/Application.h"

#include "TicTacToe/GameLayer.h"


namespace TicTacToe {

	Application::Application(const Moon::ApplicationSpecification& spec)
		: Moon::Application(spec)
	{
		PushLayer(new GameLayer());
	}

}
