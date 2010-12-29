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
#ifndef KERNEL_REASONER_SEEN
#define KERNEL_REASONER_SEEN
#include <sstream>

#ifdef NEED_KERNEL_H
#include "Kernel.h"
#else
class ReasoningKernel;
#endif

class FaCTReasoner {
private:
	ReasoningKernel *Kernel;
	FaCTReasoner(const FaCTReasoner&);      // No copy constructor
	FaCTReasoner& operator=(FaCTReasoner);  // No assignment
	
public:
	FaCTReasoner();
	~FaCTReasoner();
		
	// About the reasoner
	static const char* getReasonerVersion(void);
	
	bool isKBPreprocessed(void) const;
	bool isKBClassified(void) const;
	bool isKBRealised(void) const;
	
	// Setup functions
	void setVerboseOutput(bool value);
	void setTopBottomRoleNames(const char* topORoleName, const char* botORoleName,
		const char* topDRoleName, const char* botDRoleName);
	void writeReasoningResult( std::ostream& o, float time) const;
	void setOperationTimeout(unsigned long timeout);
};
#endif