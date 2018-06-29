#ifndef REVERSE_H_
#define REVERSE_H_
#include <type_traits>
#include <initializer_list>
#include <utility>
#include <iterator>

namespace adapter{

template<typename Cont>
struct reverse{
	static_assert(std::is_reference_v<Cont>||std::is_move_constructible_v<Cont>,"ref or move constructible");
	explicit constexpr reverse(Cont &&c)
	:container{std::forward<Cont>(c)}{}
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
reverse(std::initializer_list<T>)-> reverse<std::initializer_list<T>const&>;

}


#endif /* REVERSE_H_ */
