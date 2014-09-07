#ifndef __BRICKSVM_CORE_FUNCTION_HPP__
#define __BRICKSVM_CORE_FUNCTION_HPP__

# include <functional>
# include "core/IFunction.hpp"
# include "core/Utils.hpp"

namespace bricksvm
{
	namespace core
	{
		template<typename Signature>
		class Function : public IFunction
		{
		public:
			Function(std::function<Signature> const &&fn) : _fn(fn)
			{

			}

			Function(std::function<Signature> const &fn) : _fn(fn)
			{

			}

			~Function()
			{

			}

			template<typename ResultType = void, typename ... Args>
			ResultType call(Args ... args)
			{
				return _fn(args...);
			}

			template<typename ResultType = void, typename ... Args>
			ResultType call(Args ... args) const
			{
				return _fn(args...);
			}

			int getNbParameters() const
			{
				return CountArgs<Signature>::value;
			}


		private:
			std::function<Signature>	_fn;
		};

		template<typename ResultType = void, typename ... Args>
		ResultType call(IFunction &fn, Args ... args)
		{
			if (sizeof...(args) == fn.getNbParameters())
			{
				return static_cast<Function<ResultType (Args...)>&>(fn).call<ResultType>(args...);
			}
			throw std::runtime_error("Try to call a function with invalid arguments number");
		}

		template<typename ResultType, typename ... Args>
		IFunction *makeFunction(ResultType (*ptrFn)(Args...))
		{
			std::function<ResultType(Args...)> fn = ptrFn;

			return new Function<ResultType (Args...)>(fn);
		}

		template<typename ObjectType, typename ResultType, typename ... Args>
		IFunction *makeFunction(ObjectType &instance, ResultType(ObjectType::*method)(Args...))
		{
			std::function<ResultType(Args...)> fn = std::bind(method, instance);

			return new Function<ResultType(Args...)>(fn);
		}

		template<typename ResultType, typename ... Args>
		IFunction *makeFunction(std::function<ResultType(Args...)> const &fn)
		{
			return new Function<ResultType(Args...)>(fn);
		}
	}


}

#endif