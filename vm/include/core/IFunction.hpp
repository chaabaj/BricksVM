#ifndef __BRICKSVM_CORE_IFUNCTION_HPP__
#define __BRICKSVM_CORE_IFUNCTION_HPP__

namespace bricksvm
{
	namespace core
	{
		class IFunction
		{
		public:
			virtual ~IFunction() {}

			virtual int getNbParameters() const = 0;
		};
	}
}

#endif