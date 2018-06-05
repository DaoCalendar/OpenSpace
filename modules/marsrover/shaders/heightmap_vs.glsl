/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2018                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#version __CONTEXT__

#include "PowerScaling/powerScaling_vs.hglsl"

layout(location = 0) in vec4 in_position;
layout(location = 1) in vec2 in_st;
//layout(location = 2) in vec3 in_normal;
layout(location = 2) in vec2 textureCoords;


out vec2 vs_st;
out vec4 vs_position;
//out vec3 vs_normalViewSpace;
//out float vs_screenSpaceDeph;

//out vec2 UV;
out vec2 pass_textureCoords;
out vec4 vs_positionScreenSpace;

//uniform mat4 cameraFrustumSize;
//uniform mat4 directionToSurfaceViewSpace;
uniform mat4 modelViewProjectionTransform;
uniform mat4 projectionTransform;


void main() {

	vs_st = in_st;
	vec4 positionCameraSpace = vec4(modelViewProjectionTransform * in_position);

	//in_position should be the frustum size??? ie. ModelPath
	//guessing this 0.0 should be the height
	vs_position = z_normalization(
		modelViewProjectionTransform * vec4(in_position.xy, 0.0, 1.0) * vec4(textureCoords.xy, 0.0, 1.0) //* cameraFrustumSize
	);

	vec4 positionClipSpace = projectionTransform * positionCameraSpace;
    vs_positionScreenSpace = z_normalization(positionClipSpace);

	gl_Position = vs_position;
	pass_textureCoords = textureCoords;

	//vs_normalViewSpace = normalize(mat3(ViewProjection) * in_normal);
}