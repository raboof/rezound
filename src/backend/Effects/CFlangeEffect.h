/* 
 * Copyright (C) 2002 - David W. Durham
 * 
 * This file is part of ReZound, an audio editing application.
 * 
 * ReZound is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 * 
 * ReZound is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA
 */

#ifndef __CFlangeEffect_H__
#define __CFlangeEffect_H__

#include "../../../config/common.h"


#include "../AAction.h"
#include "../ALFO.h"

class CFlangeEffect : public AAction
{
public:
	CFlangeEffect(const AActionFactory *factory,const CActionSound *actionSound,float delayTime,float wetGain,float dryGain,const CLFODescription &flangeLFO,float feedback);
	virtual ~CFlangeEffect();

protected:
	bool doActionSizeSafe(CActionSound *actionSound,bool prepareForUndo);
	void undoActionSizeSafe(const CActionSound *actionSound);
	CanUndoResults canUndo(const CActionSound *actionSound) const;

private:
	const float delayTime;
	const float wetGain;
	const float dryGain;
	const CLFODescription flangeLFO;
	const float feedback;

};

class CFlangeEffectFactory : public AActionFactory
{
public:
	CFlangeEffectFactory(AActionDialog *channelSelectDialog,AActionDialog *dialog);
	virtual ~CFlangeEffectFactory();

	CFlangeEffect *manufactureAction(const CActionSound *actionSound,const CActionParameters *actionParameters) const;
};


#endif
