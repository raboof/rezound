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

#include "CAddCuesAction.h"

#include "../CActionParameters.h"

CAddCuesAction::CAddCuesAction(const CActionSound &actionSound,const string _cueName,const unsigned _cueCount) :
	AAction(actionSound),
	cueName(_cueName),
	cueCount(_cueCount)
{
}

CAddCuesAction::~CAddCuesAction()
{
}

bool CAddCuesAction::doActionSizeSafe(CActionSound &actionSound,bool prepareForUndo)
{
	const sample_pos_t start=actionSound.start;
	const sample_pos_t selectionLength=actionSound.selectionLength();

	sample_fpos_t interval=(sample_fpos_t)selectionLength/cueCount;
	sample_fpos_t position=start;
	for(size_t t=0;t<cueCount;t++)
	{
		actionSound.sound->addCue(cueName,(sample_pos_t)sample_fpos_round(position),false);
		position+=interval;
	}

	return true;
}

AAction::CanUndoResults CAddCuesAction::canUndo(const CActionSound &actionSound) const
{
	return curYes;
}

void CAddCuesAction::undoActionSizeSafe(const CActionSound &actionSound)
{
	// it is not necessary to do anything here because AAction handles restoring all the cues
}


// --------------------------------------------------
//
CAddCuesActionFactory::CAddCuesActionFactory(AActionDialog *normalDialog) :
	AActionFactory("Add Cues","Add Cues at Evenly Spaced Intervals",false,NULL,normalDialog,NULL)
{
}

CAddCuesActionFactory::~CAddCuesActionFactory()
{
}

CAddCuesAction *CAddCuesActionFactory::manufactureAction(const CActionSound &actionSound,const CActionParameters *actionParameters,bool advancedMode) const
{
	return new CAddCuesAction(
		actionSound,
		actionParameters->getStringParameter("Cue Name"),
		actionParameters->getUnsignedParameter("Cue Count")
		);
}

