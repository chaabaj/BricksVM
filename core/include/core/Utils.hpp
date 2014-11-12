#ifndef __BRICKSVM_CORE_UTILS_HPP__
#define __BRICKSVM_CORE_UTILS_HPP__

#include <sstream>
#include <cctype>

namespace bricksvm
{
    namespace core
    {
        template<typename ExceptionType>
        inline void throwIf(bool val, std::string const &msg)
        {
            if (val)
            {
                throw ExceptionType(msg);
            }
        }

        template<typename Signature>
        struct CountArgs;

        template<typename ResultType, typename ... Args>
        struct CountArgs < ResultType(Args...) >
        {
            static const int value = sizeof...(Args);
        };

        template<typename T>
        class TypeTraits
        {
            template<typename U>
            struct isRefWrapper
            {
                static const bool value = false;
            };

            template<typename U>
            struct isRefWrapper < std::reference_wrapper<U> >
            {
                static const bool value = true;
            };

        public:
            static const bool is_ref_wrapper = isRefWrapper<T>::value;
        };

		template<typename T>
		T convert(std::string const &value)
		{
			std::stringstream stream;
			T convertedValue;

			stream << value;
			stream >> convertedValue;
			return (convertedValue);
		}

		template<typename... T>
		std::string stringBuilder(T ...args)
		{
			std::stringstream stream;
			std::string  newString;

			append(stream, args...);
			return (stream.str());
		}

		template<typename T, typename ... U>
		void append(std::stringstream &stream, T const &val, U &...others)
		{
			stream << val;
			append(stream, others...);
		}

		template<typename T>
		void append(std::stringstream &stream, T const &val)
		{
			stream << val;
		}

		inline bool isInteger(const std::string& s)
		{
			std::string::const_iterator it = s.begin();
			while (it != s.end() && std::isdigit(*it)) ++it;
			return !s.empty() && it == s.end();
		}

		inline bool isLabel(const std::string &s)
		{
			const std::string availablesCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_-";

			std::string::const_iterator it;
			for (it = s.begin(); it != s.end(); ++it)
			{
				if (availablesCharacters.find(*it) == std::string::npos)
					return (false);
			}
			return (true);
		}

		inline bool isDecimal(const std::string& s, char decimalSeparator = '.')
		{
			/*bool hasDecimalSeparator = false;

			std::string::const_iterator it = s.begin();
			while ( && std::isdigit(*it)) ++it;
			return !s.empty() && it == s.end();*/

			std::string::const_iterator it;
			for (it = s.begin(); it != s.end(); ++it)
			{
				if (!std::isdigit(*it) && *it != decimalSeparator)
					return (false);
				else if (*it == decimalSeparator && it != s.begin())
					return (false);
			}
			return (it == s.end());
		}

		/*bool isValidNumber(std::string t)
		{
			return (true);
		}*/

    }
}

#endif
