/*
 * Copyright 2026 Marcus Gigandet
 *
 * All rights reserved.
 */

module;
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_raii.hpp>
export module lys:vulkan_debug;

import :log;
import mag;
import std;
import vulkan;

namespace lys
{

#ifdef NDEBUG
	constexpr bool enableValidationLayers = false;
#else
	constexpr bool enableValidationLayers = true;
#endif

	const std::vector<char const*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

	VKAPI_ATTR vk::Bool32 VKAPI_CALL
	debugCallback(const vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
				  const vk::DebugUtilsMessageTypeFlagsEXT type,
				  const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
				  void* pUserData)
	{
		switch (severity)
		{
		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
			logger().error("Validation layer: {} - {}",
						   to_string(type),
						   std::string(pCallbackData->pMessage));
			break;
		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
			logger().warning("Validation layer: {} - {}",
							 to_string(type),
							 std::string(pCallbackData->pMessage));
			break;
		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
			logger().info("Validation layer: {} - {}",
						  to_string(type),
						  std::string(pCallbackData->pMessage));
			break;
		case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
		default:
			logger().debug("Validation layer: {} - {}",
						   to_string(type),
						   std::string(pCallbackData->pMessage));
			break;
		}

		return vk::False;
	}

	std::optional<vk::raii::DebugUtilsMessengerEXT>
	setupDebugMessenger(const vk::raii::Instance& instance)
	{
		if constexpr (!enableValidationLayers)
			return std::nullopt;

		vk::DebugUtilsMessageSeverityFlagsEXT severityFlags{
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
				vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
		};
		vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags{
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
				vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
				vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
		};
		const vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfoEXT{
			.messageSeverity = severityFlags,
			.messageType = messageTypeFlags,
			.pfnUserCallback = &debugCallback,
		};
		auto debugMessenger =
			instance.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfoEXT);
		return debugMessenger;
	}
} // namespace lys
