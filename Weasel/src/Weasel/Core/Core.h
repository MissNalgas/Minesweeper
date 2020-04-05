#pragma once

#include <memory>

#ifdef WS_PLATFORM_WINDOWS
#if WS_DYNAMIC_LINK
#ifdef WS_BUILD_DLL
#define WS_API __declspec(dllexport)
#else
#define WS_API __declspec(dllimport)
#endif
#else
#define WS_API 
#endif
#else 
#error Not Supported
#endif

#ifdef WS_ENABLE_ASSERTS
#define WS_ASSERT(x, ...) {if(!(x)) {WS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define WS_CORE_ASSERT(x, ...) {if(!(x)) { WS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
#define WS_ASSERT(x, ...)
#define WS_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define WS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Weasel {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}