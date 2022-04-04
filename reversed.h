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
	constexpr auto begin() & { using std::rbegin; return rbegin(container);}
	constexpr auto begin() const & { using std::rbegin; return rbegin(container);}
	constexpr auto end() & { using std::rend; return rend(container);}
	constexpr auto end() const & { using std::rend; return rend(container);}
};
template<typename Cont>
reversed(Cont &) -> reversed<Cont &>;
template<typename Cont>
reversed(Cont  &&) -> reversed<Cont>;
template<typename T>
reversed(std::initializer_list<T>)-> reversed<std::initializer_list<T>>;
}

#endif /* REVERSED_H_ */
