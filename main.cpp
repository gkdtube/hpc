#include <iostream>
#include <tuple>
#include <map>
#include <any>

template<typename F, typename...Args>
    //requires std::invocable<F, Args...>
struct Input {
    using R = std::invoke_result_t<F, Args...>;

    F _f;
    std::tuple<Args...>_values;

    Input(F f, Args...args) :_f{ f }, _values{ args... } {}
    constexpr R operator()()const noexcept {
        return std::apply([&](Args...args) {return _f(args...); }, _values);
    }
};

enum class FunType
{
    InputType,
    OutputType
};

int main() {
    Input input([](int a, double b) {std::cout << a << ' ' << b << '\n'; }, 1, 2.);
    input();
    std::map<FunType, Input<typename F, typename...Args>> fun_map;
    std::cout << std::get<0>(input._values) << '\n';
}
