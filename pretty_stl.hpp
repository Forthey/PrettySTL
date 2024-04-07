#ifndef PRETTY_STL_HPP
#define PRETTY_STL_HPP

#include <string>
#include <iostream>
#include <unordered_map>


/// \namespace PrettySTL namespace
namespace Pretty {
    using ElementConvertFunction = std::string (*)(void const *);

    /// \brief Print parameters
    enum Params {
        /// separator between container elements
        separator = 0,
        /// beginning of output
        begin,
        /// ending of output
        end
    };

    /// \class STL pretty output class
    class Stl {
        static std::string const
                defaultSeparator,
                defaultBegin,
                defaultEnd;

        std::ostream *out = &std::cout;

        ElementConvertFunction elementConvertFunction = nullptr;
    public:

        /// \brief Constructor allows to set custom output
        /// \param out a custom output (file, for example)
        explicit Stl(std::ostream &out = std::cout) : out(&out) {
        }

        /// \brief Constructor allows to set custom output of elements
        /// \param convertFunction a function of the form std::string (*)(void const* element),
        /// which takes an element as param and returns it as a string
        explicit Stl(ElementConvertFunction convertFunction) : elementConvertFunction(convertFunction) {
        }

        /// \brief Constructor allows to set both custom output of elements and custom output
        /// \param out a custom output (file, for example)
        /// \param convertFunction a function of the form std::string (*)(void const* element),
        /// which takes an element as param and returns it as a string
        explicit Stl(std::ostream &out, ElementConvertFunction convertFunction) : out(&out),
                                                                                  elementConvertFunction(
                                                                                          convertFunction) {
        }

        /// \brief Functions allows to set custom output
        /// \param out_ a custom output (file, for example)
        void setOutVariable(std::ostream &out_) {
            out = &out_;
        }

        /// \brief Function allows to set custom output of elements
        /// \param convertFunction a function of the form std::string (*)(void const* element),
        /// which takes an element as param and returns it as a string
        void setElementConvertFunction(std::string (*outputFunc)(void const *element)) {
            elementConvertFunction = outputFunc;
        }

        /// \brief Shortened setElementConvertFunction
        void f(std::string (*outputFunc)(void const *element)) {
            elementConvertFunction = outputFunc;
        }

        /// \brief Overloading the output operator. Doesn't work for built-in types
        /// \param container container to print
        /// \return out variable for chain output
        template<class Container>
        std::ostream &operator<<(Container const &container) {
            print(container);

            return *out;
        }

        /// \brief Function that prints the container. For built-in types please use printBuiltIn
        /// \param container container itself
        /// \param separatorStr string that will be used as a separator between elements
        /// \param beginStr string that will be printed at the beginning
        /// \param endStr string that will be printed at the end
        template<class Container>
        void print(
                Container const &container,
                std::string const &separatorStr = defaultSeparator,
                std::string const &beginStr = defaultBegin,
                std::string const &endStr = defaultEnd) {
            *out << beginStr;

            for (auto iter = container.begin(); iter != container.end();) {
                *out << elementConvertFunction(&(*iter));
                if (++iter != container.end()) {
                    *out << separatorStr;
                }
            }

            *out << endStr;
        }

        /// \brief Function that prints the container. For built-in types please use printBuiltIn
        /// \param container container itself
        /// \param params input parameters -- you can look them in Pretty::Params enum
        /// \example print(container, {{Pretty::separator, "\n"}});
        template<class Container>
        void print(Container const &container, std::unordered_map<Params, std::string> const &params) {
            print(
                    container,
                    params.contains(separator) ? params.at(separator) : defaultSeparator,
                    params.contains(begin) ? params.at(begin) : defaultBegin,
                    params.contains(end) ? params.at(end) : defaultEnd
            );
        }

        /// \brief Function that prints the container. Use this func for built-in types
        /// \param container container itself
        /// \param separatingMask string that will be used as a separator between elements
        /// \param beginStr string that will be printed at the beginning
        /// \param endStr string that will be printed at the end
        template<class Container>
        void printBuiltIn(
                Container const &container,
                std::string const &separatingMask = defaultSeparator,
                std::string const &beginStr = defaultBegin,
                std::string const &endStr = defaultEnd) {
            *out << beginStr;

            for (auto iter = container.begin(); iter != container.end();) {
                *out << *iter;
                if (++iter != container.end()) {
                    *out << separatingMask;
                }
            }

            *out << endStr;
        }

        /// \brief Function that prints the container. Use this func for built-in types
        /// \param container container itself
        /// \param params input parameters -- you can look them in Pretty::Params enum
        /// \example print(container, {{Pretty::separator, "\n"}});
        template<class Container>
        void printBuiltIn(Container const &container, std::unordered_map<Params, std::string> const &params) {
            printBuiltIn(
                    container,
                    params.contains(separator) ? params.at(separator) : defaultSeparator,
                    params.contains(begin) ? params.at(begin) : defaultBegin,
                    params.contains(end) ? params.at(end) : defaultEnd
            );
        }
    };

    std::string const
            Stl::defaultSeparator = ", ",
            Stl::defaultBegin = "{",
            Stl::defaultEnd = "}\n";
}

#endif // PRETTY_STL_HPP