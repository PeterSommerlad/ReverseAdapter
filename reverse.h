#ifndef REVERSE_H_
#define REVERSE_H_
#include <type_traits>
#include <utility>
#include <iterator>

namespace adapter{

template<typename Cont>
struct reverse{
	explicit constexpr reverse(Cont &&c,std::enable_if_t<!std::is_reference_v<Cont>>* = nullptr):container{std::move(c)}{}
	explicit constexpr reverse(Cont c,std::enable_if_t<std::is_reference_v<Cont>>* = nullptr):container{c}{}
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
