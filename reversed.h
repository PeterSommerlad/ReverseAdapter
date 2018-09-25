#ifndef REVERSED_H_
#define REVERSED_H_
#include <type_traits>
#include <initializer_list>
#include <utility>
#include <iterator>

namespace adapter{

template<typename Cont>
struct reversed{
	explicit constexpr
	reversed(Cont & c)
	:container(c){}

	explicit constexpr
	reversed(std::remove_reference_t<Cont> &&c)
	:container(std::move(c)){}

	Cont container;
	constexpr auto begin() { return std::rbegin(container);}
	constexpr auto begin() const { return std::rbegin(container);}
	constexpr auto end() { return std::rend(container);}
	constexpr auto end() const { return std::rend(container);}
};
template<typename Cont>
reversed(Cont &) -> reversed<Cont &>;
template<typename Cont>
reversed(Cont  &&) -> reversed<Cont>;
template<typename T>
reversed(std::initializer_list<T>)-> reversed<std::initializer_list<T>>;
}

#endif /* REVERSED_H_ */
