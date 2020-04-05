#pragma once

#ifdef WS_PLATFORM_WINDOWS

extern Weasel::Application* Weasel::CreateApplication();

int main(int argc, char** argv) {

	Weasel::Log::Init();
	
	WS_PROFILE_BEGIN_SESSION("Startup", "WeaselProfile-Startup.json");
	auto app = Weasel::CreateApplication();
	WS_PROFILE_END_SESSION();

	WS_PROFILE_BEGIN_SESSION("Startup", "WeaselProfile-Runtime.json");
	app->Run();
	WS_PROFILE_END_SESSION();

	WS_PROFILE_BEGIN_SESSION("Startup", "WeaselProfile-Shutdown.json");
	delete app;
	WS_PROFILE_END_SESSION();

	return 0;

}

#endif
