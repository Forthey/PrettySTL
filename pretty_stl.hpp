#ifndef TEST_PRETTY_STL_HPP
#define TEST_PRETTY_STL_HPP
#include <string>
#include <iostream>


class PrettyStl {
    std::ostream *prettyOut = &std::cout;
public:
    explicit PrettyStl(std::ostream& out = std::cout) {
        setOutVariable(out);
    }

    void setOutVariable(std::ostream& newOut) {
        prettyOut = &newOut;
    }

    template<typename Container>
    std::ostream &operator<<(Container const &container) {
        print(container);

        return *prettyOut;
    }

    template<typename Container>
    void print(
            Container const &container,
            std::string const& separatingMask = ", ",
            std::string const& beginStr = "{",
            std::string const& endStr = "} ") {
        *prettyOut << beginStr;

        for (auto iter = container.begin(); iter != container.end();) {
            *prettyOut << *iter;
            if (++iter != container.end()) {
                *prettyOut << separatingMask;
            }
        }

        *prettyOut << endStr;
    }
};


#endif // TEST_PRETTY_STL_HPP