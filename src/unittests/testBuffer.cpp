#define lest_FEATURE_AUTO_REGISTER 1
#include <Vm/Buffer.h>
#include "lest.hpp"

#undef CASE
#define CASE(name) lest_CASE( testlist, name )

#undef SCENARIO
#define SCENARIO(sketch) lest_SCENARIO(testlist, sketch )

static lest::tests testlist;

CASE("Creation") {
    Buffer s;
    EXPECT(s.size() == 0);
    EXPECT(s.empty());
}

CASE("Creation 2") {
    Buffer s;
    s.append('a');
    EXPECT(std::strcmp(s.c_str(), "a") == 0);
    EXPECT(s.size() == 1);
}

CASE("Creation 3") {
    Buffer s;
    s.append("abc", 3);
    EXPECT(std::strcmp(s.c_str(), "abc") == 0);
    EXPECT(s.size() == 3);
}

CASE("Creation 4") {
    Buffer s;
    s.append("abc", 3)
        .append("abc", 3);

    EXPECT(std::strcmp(s.c_str(), "abcabc") == 0);
    EXPECT(s.front() == 'a');
    EXPECT(s.back() == 'c');
    EXPECT(s.size() == 6);

    //clear
    s.clear();
    EXPECT(s.size() == 0);
    EXPECT(s.capacity() != 0);
}

CASE("Print") {
    Buffer s;
    s.vprint("%.2f", 9.0);
    EXPECT(std::strcmp(s.c_str(), "9.0") == 0);
}

int main(int argc, char *argv[]) {
    if (int failures = lest::run(testlist, argc, argv))
        return failures;

    std::cout << "All tests passed\n", EXIT_SUCCESS;
    return 0;
}