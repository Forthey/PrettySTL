#ifndef TEST_PRETTY_STL_HPP
#define TEST_PRETTY_STL_HPP
#include <string>
#include <iostream>


template<class ContainerElement>
class PrettyStl {
    std::ostream *prettyOut = &std::cout;
    std::string (*prettyOutput)(ContainerElement const& element) = nullptr;
public:
    explicit PrettyStl(std::ostream& out = std::cout) {
        setOutVariable(out);
    }

    void setOutVariable(std::ostream& newOut) {
        prettyOut = &newOut;
    }

    void setElementOutput(std::string (*outputFunc)(ContainerElement const& element)) {
#define CUSTOM_OUTPUT
        prettyOutput = outputFunc;
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
#ifdef CUSTOM_OUTPUT
        *prettyOut << beginStr;
#else
        *prettyOut << beginStr;
#endif

        for (auto iter = container.begin(); iter != container.end();) {
            *prettyOut << prettyOutput(*iter);
            if (++iter != container.end()) {
                *prettyOut << separatingMask;
            }
        }

        *prettyOut << endStr;
    }
};

#endif // TEST_PRETTY_STL_HPP