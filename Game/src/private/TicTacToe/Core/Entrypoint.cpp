#include "pch.h"
#include <Moon/Core/Entrypoint.h>

#include "TicTacToe/Core/Application.h"


namespace Moon {

	Application* Application::Create(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.CommandLineArgs = args;
		spec.Name = "TicTacToe";
		spec.WorkingDirectory = "../Game";
		spec.WindowWidth = 1920;
		spec.WindowHeight = 1080;

		return new TicTacToe::Application(spec);
	}

}
