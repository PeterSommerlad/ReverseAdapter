#include <reversed.h>
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <array>

using std::array;
using adapter::reversed;

constexpr std::array<int,5> make_array(){
	return {1,2,3,4,5};
}
void testWithReturnedTemporary(){
	std::ostringstream out{};
	for(auto const &i:reversed(make_array())){
		out << i;
	}
	ASSERT_EQUAL("54321",out.str());

}

struct memorize_use_after_delete{
	static inline size_t deleted{};
	static inline size_t constructed{};
	memorize_use_after_delete(){
		++constructed;
	}
	memorize_use_after_delete(memorize_use_after_delete const &){
		++constructed;
	}
	memorize_use_after_delete(memorize_use_after_delete &&) noexcept {
		++constructed;
	}
	~memorize_use_after_delete(){
		++deleted;
	}
	bool check(){
		return deleted<constructed;
	}
};

std::vector<memorize_use_after_delete> factory(){
	return (std::vector<memorize_use_after_delete>(2));
}

void test_use_after_delete(){
	for(auto &i:reversed(factory())){
		ASSERT_GREATER(memorize_use_after_delete::constructed,memorize_use_after_delete::deleted);
		ASSERTM("fewer deleted than constructed assumed",i.check());
	}
}


void testReverseArray(){
	array a{1,2,3,4,5,6};
	std::ostringstream out{};
	for(auto const &i:reversed(a)){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());
}
void testReverseConstArray(){
	array const a{1,2,3,4,5,6};
	std::ostringstream out{};
	for(auto const &i:reversed(a)){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());
}
void testReverseLRefArray(){
	array a{0,1,2,3,4,5};
	std::ostringstream out{};
	for(auto  &i:reversed(a)){
		++i;
	}
	for(auto const &i:reversed(a)){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());
}
void testReverseTempArray(){
	std::ostringstream out{};
	for(auto  &i:reversed(array{1,2,3,4,5,6})){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());
}
void testReverseInitializerList(){
	std::ostringstream out{};
	for(auto const &i:reversed({1,2,3,4,5,6})){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());
}
void testReverseCArray(){
	int a[]={1,2,3,4,5,6};
	std::ostringstream out{};
	for(auto const &i:reversed(a)){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());

}
bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	//TODO add your test here
	s.push_back(CUTE(testReverseArray));
	s.push_back(CUTE(testReverseConstArray));
	s.push_back(CUTE(testReverseLRefArray));
	s.push_back(CUTE(testReverseTempArray));
	s.push_back(CUTE(testReverseCArray));
	s.push_back(CUTE(testReverseInitializerList));
	s.push_back(CUTE(testWithReturnedTemporary));
	s.push_back(CUTE(test_use_after_delete));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
