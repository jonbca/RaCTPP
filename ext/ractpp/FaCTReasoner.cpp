/*
Copyright (C) 2010 Jonathan Abourbih

This file is part of RactPP, the Ruby-FaCT++ Bridge.

RactPP is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RactPP is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RactPP.  If not, see <http://www.gnu.org/licenses/>.
*/

#define NEED_KERNEL_H
#include "FaCTReasoner.h"

FaCTReasoner::FaCTReasoner()
	: Kernel(new ReasoningKernel)
{
	// Do Nothing
}

FaCTReasoner::~FaCTReasoner() {
	delete Kernel;
}

const char* FaCTReasoner::getReasonerVersion(void) {
	return ReasoningKernel::getVersion();
}

void FaCTReasoner::setTopBottomPropertyNames(const char* topORoleName, const char* botORoleName,
	const char* topDRoleName, const char* botDRoleName) {
	Kernel->setTopBottomRoleNames(topORoleName, botORoleName, topDRoleName, botDRoleName);
}

bool FaCTReasoner::isKBPreprocessed(void) const {
	return Kernel->isKBPreprocessed();
}

bool FaCTReasoner::isKBClassified(void) const {
	return Kernel->isKBClassified();
}

bool FaCTReasoner::isKBRealised(void) const {
	return Kernel->isKBRealised();
}

bool FaCTReasoner::clearKB(void) {
	return Kernel->clearKB();
}

void FaCTReasoner::classify(void) {
	Kernel->classifyKB();
}

void FaCTReasoner::realise(void) {
	Kernel->realiseKB();
}

Entity* FaCTReasoner::getTop(void) const {
	TExpressionManager* em = Kernel->getExpressionManager();
	
	ReasoningKernel::TConceptExpr* top = em->Top();
	
	Entity *entity = new Entity;
	entity->entityPointer = top;
	entity->type = ClassType;
	entity->name = "Top Concept";
	
	return entity;
}

Entity* FaCTReasoner::getBottom(void) const {
	TExpressionManager* em = Kernel->getExpressionManager();
	
	ReasoningKernel::TConceptExpr* bottom = em->Bottom();
	
	Entity *entity = new Entity;
	entity->entityPointer = bottom;
	entity->type = ClassType;
	entity->name = "Bottom Concept";
	
	return entity;
}

Entity* FaCTReasoner::getClassByName(std::string name) const {
	TExpressionManager* em = Kernel->getExpressionManager();
	
	ReasoningKernel::TConceptExpr* clazz = em->Concept(name);
	
	Entity *entity = new Entity;
	entity->entityPointer = clazz;
	entity->type = ClassType;
	entity->name = name;
	
	return entity;
}
