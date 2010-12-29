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

void FaCTReasoner::setTopBottomRoleNames(const char* topORoleName, const char* botORoleName,
	const char* topDRoleName, const char* botDRoleName) {
	Kernel->setTopBottomRoleNames(topORoleName, botORoleName, topDRoleName, botDRoleName);
}

const char* FaCTReasoner::getReasonerVersion(void) {
	return ReasoningKernel::getVersion();
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

void FaCTReasoner::setVerboseOutput(bool value) {
	Kernel->setVerboseOutput(value);
}

bool FaCTReasoner::clearKB(void) {
	return Kernel->clearKB();
}

void FaCTReasoner::classify(void) {
	
}

void FaCTReasoner::setOperationTimeout(unsigned long timeout) {
	Kernel->setOperationTimeout(timeout);
}