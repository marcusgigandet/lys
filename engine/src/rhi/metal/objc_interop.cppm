/*
 * Copyright 2026 Marcus Gigandet
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

module;
#include <objc/message.h>
#include <objc/runtime.h>
#ifdef LYS_DEBUG
#	include <spdlog/spdlog.h>
#endif
export module lys:metal_objc_interop;

namespace lys
{
	/**
	 * @brief Calls an Objective-C method on a specified object with the given selector and
	 * arguments.
	 *
	 * This function template is used to invoke an Objective-C method on an object. In debug mode,
	 * it performs additional checks to ensure the object, selector, and method are valid.
	 *
	 * Example usage:
	 * @code
	 * 		objcCall<void>(nsView, "wantsLayer", YES);
	 * @endcode
	 *
	 * @param obj The Objective-C object on which to call the method.
	 * @param selector The name of the selector (method) to call.
	 * @param args The arguments to pass to the method.
	 * @return Ret The return value of the called Objective-C method.
	 */
	export template <typename Ret, typename... Args>
	Ret objcCall(id obj, const char* selector, Args... args)
	{
		SEL sel{sel_registerName(selector)};

#ifdef LYS_DEBUG
		if (!obj)
		{
			spdlog::warn("objcCall: called with null object for selector '{}'", selector);
			return Ret{};
		}

		if (!selector)
		{
			spdlog::warn("objcCall: null selector passed");
			return Ret{};
		}

		if (!sel)
		{
			spdlog::warn("objcCall: failed to register selector '{}'", selector);
			return Ret{};
		}

		const char* className{class_getName(object_getClass(obj))};
		if (!class_respondsToSelector(object_getClass(obj), sel))
		{
			spdlog::warn(
				"objcCall: object of class '{}' does not respond to selector '{}'",
				className,
				selector);
			return Ret{};
		}
#endif

		using FnType = Ret (*)(id, SEL, Args...);
		auto fn{reinterpret_cast<FnType>(objc_msgSend)};
		return fn(obj, sel, args...);
	}
} // namespace lys
