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

export module lys;

// Core
export import :file;
export import :timer;

// RHI
export import :rhi_error;
export import :rhi_types;
export import :rhi_device;
export import :rhi_buffer;
export import :rhi_texture;
export import :rhi_shader;
export import :rhi_pipeline_state;
export import :rhi_command_buffer;
export import :rhi_command_queue;

// Platform
export import :input_manager;
export import :input_map;
export import :window;

// Metal
#ifdef LYS_METAL
export import :metal_buffer;
export import :metal_command_buffer;
export import :metal_command_queue;
export import :metal_device;
#endif

// Vulkan
#ifdef LYS_VULKAN
export import :vulkan_context;
export import :vulkan_debug;
export import :vulkan_device;
#endif

// Other libraries
export import mag;
