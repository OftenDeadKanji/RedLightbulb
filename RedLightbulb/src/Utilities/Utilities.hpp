#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__

#define sCast(type, value)      static_cast<type>(value)
#define dCast(type, value)     dynamic_cast<type>(value)
#define cCast(type, value)       const_cast<type>(value)
#define rCast(type, value) reinterpret_cast<type>(value)

template<typename T>
using rPtr = T*;

template<typename T>
using uPtr = std::unique_ptr<T>;

template<typename T>
using sPtr = std::shared_ptr<T>;

namespace Utilities
{
	class NonCopyable
	{
	public:
		NonCopyable() = default;
		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;
	};

	void readFile(const std::string& fileName, std::string& fileContent);
}

#endif
