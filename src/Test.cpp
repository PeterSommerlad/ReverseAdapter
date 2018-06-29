#include "reverse.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include <array>

using std::array;
using adapter::reverse;

void testReverseArray(){
	array a{1,2,3,4,5,6};
	std::ostringstream out{};
	for(auto const &i:reverse(a)){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());
}
void testReverseConstArray(){
	array const a{1,2,3,4,5,6};
	std::ostringstream out{};
	for(auto const &i:reverse(a)){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());
}
void testReverseLRefArray(){
	array a{0,1,2,3,4,5};
	std::ostringstream out{};
	for(auto  &i:reverse(a)){
		++i;
	}
	for(auto const &i:reverse(a)){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());
}
void testReverseTempArray(){
	std::ostringstream out{};
	for(auto  &i:reverse(array{1,2,3,4,5,6})){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());
}
void testReverseInitializerList(){
	std::ostringstream out{};
	for(auto const &i:reverse({1,2,3,4,5,6})){
		out << i;
	}
	ASSERT_EQUAL("654321",out.str());
}
void testReverseCArray(){
	int a[]={1,2,3,4,5,6};
	std::ostringstream out{};
	for(auto const &i:reverse(a)){
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
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
