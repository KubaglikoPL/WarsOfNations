#pragma once

#ifdef _WIN32
	#ifdef DLL_EXPORT
		#define API __declspec(dllexport)
	#else
		#define API __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
	#ifdef GEN_EXPORT
		#define API __attribute__((visibility("default")))
	#else
		#define API
	#endif
#else
	#define API
#endif
