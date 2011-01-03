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
#include <string>
#include <sstream>
#include <stdexcept>

#ifdef NEED_KERNEL_H
#include "Kernel.h"
#else
/* Deal with the implementation later */
class ReasoningKernel;
/* Include the exceptions from FaCT++ */
#include "eFaCTPlusPlus.h"
#include "eFPPAxiomLoadFailure.h"
#include "eFPPCantRegName.h"
#include "eFPPCycleInRIA.h"
#include "eFPPInconsistentKB.h"
#include "eFPPNonSimpleRole.h"
#include "eFPPSaveLoad.h"
#include "eFPPTimeout.h"
#endif

struct Entity;

enum EntityType {
	ClassType,
	IndividualType,
	ObjectPropertyType,
	DataPropertyType,
	DataTypeType
};

static std::string EntityTypes[] = {
		"class",
		"individual",
		"object_property",
		"data_property",
		"data_type"
	};

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
	
	// Information about the knowledge base
	bool isKBPreprocessed(void) const;
	bool isKBClassified(void) const;
	bool isKBRealised(void) const;
	
	bool clearKB(void);
	
	// Setup functions
	void setTopBottomPropertyNames(const char* topORoleName, const char* botORoleName,
		const char* topDRoleName, const char* botDRoleName);
	
	// Classification
	void classify(void);
	void realise(void);
	
	// Concepts
	Entity* getTop(void);
	Entity* getBottom(void);
	Entity* getClassByName(std::string className);
	
	Entity* getTopObjectProperty(void);
	Entity* getBottomObjectProperty(void);
	
	Entity* getObjectProperty(std::string name);
	
	Entity* getTopDataProperty(void);
	Entity* getBottomDataProperty(void);
	Entity* getDataProperty(std::string name);
		
	Entity* getIndividual(std::string name);
	
	Entity* getBuiltInDataType(std::string name);
};

struct Entity {
	friend class FaCTReasoner;
private:
	const void * entityPointer;
	std::string name;
	EntityType type;
	Entity(const Entity &);
	Entity& operator=(Entity);
public:
	Entity(){}
	~Entity(){}
	Entity(const void *ep, std::string nm, EntityType t)
		: entityPointer(ep), name(nm), type(t) {}
		
	std::string getName() const {
		return name;
	}
	
	EntityType getType() const {
		return type;
	}
	
	const void * const getEntityPointer() const {
		return entityPointer;
	}
	
	std::string const to_s() const {
		std::stringstream sstr;
		char epstr[16];
		
		snprintf(epstr, 16, "%p", entityPointer);
		
		sstr << name << " " << EntityTypes[type] << "<" << epstr << ">";
		return sstr.str();
	}
};

class RaCTPPException : public std::runtime_error {
public:
	explicit RaCTPPException(const std::string& reason)
		: std::runtime_error(reason) {}
};
#endif