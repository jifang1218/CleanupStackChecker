#ifndef CSOMECLASS_H_
#define CSOMECLASS_H_

#include "CBase.h"

namespace Fang {

/**
 a CBase derived class. Represents a regular C-class.
 It provides a regular method and two leave methods. 
 */
class CSomeClass : public CBase {
	public:
		CSomeClass();
		virtual ~CSomeClass();

	public:
		void DoSomeAction();
		void DoSomeActionL();
		void DoSomeActionLC();
};

} // Fang

#endif // CSOMECLASS_H

