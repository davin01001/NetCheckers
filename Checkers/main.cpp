#include "../Core/framework.h"

#include <cstdlib>

#include <iostream>
#include <string>
#include <exception>
using namespace std;

int main(int argc, char * argv[])
{
	string ip;
	if (argc > 1) {
		ip = argv[1];
	}

	try
	{
		auto controller = make_unique<BoardController>(ip);
		if (!controller->Created())
			return EXIT_FAILURE;

		while (controller->IsAlive())
		{
			controller->ProcessEvents();
			controller->Update();
			controller->Render();
			controller->Idle();
		}
	}
	catch (runtime_error & re)
	{
		cerr << "Runtime error: " << re.what() << endl;
	}
	catch (exception & ex)
	{
		cerr << "Error occurred: " << ex.what() << endl;
	}
	catch (...)
	{
		cerr << "Unknown exception. Possibly memory corruption." << endl;
	}

	return EXIT_SUCCESS;
}
