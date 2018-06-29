#ifndef REVERSE_H_
#define REVERSE_H_
#include <type_traits>
#include <initializer_list>
#include <utility>
#include <iterator>

namespace adapter{

template<typename Cont>
struct reverse{
	explicit constexpr
	reverse(Cont & c)
	:container(c){}

	explicit constexpr
	reverse(std::remove_reference_t<Cont> &&c)
	:container(std::move(c)){}

	Cont container;
	constexpr auto begin() { return std::rbegin(container);}
	constexpr auto begin() const { return std::rbegin(container);}
	constexpr auto end() { return std::rend(container);}
	constexpr auto end() const { return std::rend(container);}
};
template<typename Cont>
reverse(Cont &) -> reverse<Cont &>;
template<typename Cont>
reverse(Cont  &&) -> reverse<Cont>;
template<typename T>
reverse(std::initializer_list<T>)-> reverse<std::initializer_list<T>>;

}


#endif /* REVERSE_H_ */
