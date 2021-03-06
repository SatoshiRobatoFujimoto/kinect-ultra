//@COPYRIGHT@//
//
// Copyright (c) 2011, Tomoto S. Washio
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//   * Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   * Neither the name of the Tomoto S. Washio nor the names of his
//     contributors may be used to endorse or promote products derived from
//     this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL TOMOTO S. WASHIO BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//@COPYRIGHT@//

#ifndef _DEPTH_IMAGE_RENDERER_H_
#define _DEPTH_IMAGE_RENDERER_H_

#include "common.h"
#include "Configurable.h"
#include "AbstractOpenGLRenderer.h"
#include "HenshinDetector.h"
#include "TimeTicker.h"
#include "ImageProvider.h"
#include "DepthProvider.h"

class WorldRenderer : public AbstractOpenGLRenderer, protected Configurable
{
private:
	// This should be GLBatch's job, but GLBatch has memory leak!
	class Batch {
	private:
		GLuint m_numPoints;
		GLuint m_vertexArrayID;
		GLuint m_vertexBufID;
		GLuint m_colorBufID;

	public:
		Batch();
		~Batch();
		void init(GLuint numPoints);
		void draw(M3DVector3f* vertexBuf, M3DVector4f* colorBuf);
	};

protected:
	DepthProvider* m_depthProvider;
	ImageProvider* m_imageProvider;
	HenshinDetector* m_henshinDetector;

	Batch m_batch; 

	int m_width;
	int m_height;
	M3DVector3f* m_vertexBuf;
	M3DVector4f* m_colorBuf;

	GLuint m_henshinGlowTextureID;

	float m_depthAdjustment;

public:
	WorldRenderer(RenderingContext* rctx, DepthProvider* depthProvider, ImageProvider* imageProvider, HenshinDetector* henshinDetector);
	virtual ~WorldRenderer();
	
	void draw();

	void addDepthAdjustment(float value) { m_depthAdjustment += value; }
private:
	DWORD getNumPoints() { return m_width * m_height; }

	void getHenshinData(XuUserID* pUserID, XV3* pHeadPoint, XV3* pNeckPoint, int* pHenshinBottom, float* pFlyingOffset);

	void drawBackground();
	void drawHenshiningGlow();
};

#endif
