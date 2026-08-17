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

#include <metal_stdlib>
using namespace metal;

struct VertexOut
{
	float4 position [[position]];
	float2 texCoord;
};

struct Vertex
{
	float3 position;
	float2 texCoord;
};

vertex VertexOut
vertexMain(const device Vertex* vertices [[buffer(0)]], uint vertexID [[vertex_id]])
{
	VertexOut out;
	out.position = float4(vertices[vertexID].position, 1.0);
	out.texCoord = vertices[vertexID].texCoord;
	return out;
}

fragment float4 fragmentMain(
	VertexOut in [[stage_in]], texture2d<float> tex [[texture(0)]], sampler smp [[sampler(0)]])
{
	return tex.sample(smp, in.texCoord);
}
