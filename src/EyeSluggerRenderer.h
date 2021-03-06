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

#ifndef _EYE_SLUGGER_RENDERER_H_
#define _EYE_SLUGGER_RENDERER_H_

#include "common.h"
#include "AbstractOpenGLRenderer.h"
#include "HenshinDetector.h"
#include <vector>

// TODO: renderer part and motion controller part should be separated
class EyeSluggerRenderer : public AbstractOpenGLRenderer
{
private:
	std::vector<GLBatch> m_batches;

	TimeTicker m_ticker;
	float m_shotLifeTime;
	float m_shotProgress;
	XV3 m_shotVector;
	float m_shotRotation;
	int m_shotTraceDencity;

	float m_brightness;

protected:
	HenshinDetector* m_henshinDetector;
	GLFrame m_objectFrame;
	XV3 m_origin;

private:
	void setupObjectModel();
	
	void drawSlugger(float velocity, float rotation);
	void drawHeld(float dt);
	void drawShot(float dt);

public:
	EyeSluggerRenderer(RenderingContext* rctx, HenshinDetector* henshinDetector);
	virtual ~EyeSluggerRenderer();

	virtual void draw();

	virtual void shoot(const XV3& v, float rotation, int traceDencity);

	XV3 getOrigin(); // TODO weird dependency direction; should this be give from outside?
	XV3 getForwardVector(); // TODO weird dependency direction; should this be give from outside?

	void setEnergy(float energy);

	bool isShot();

protected:
	virtual bool updateObjectFrame();
};

#endif
