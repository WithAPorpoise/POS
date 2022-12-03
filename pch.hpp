//
// Akanya, Engine
// includes/pch
// g++ -x c++-header -Wpedantic -Wall -Wextra -Wno-volatile -Wno-address -Wno-nonnull-compare -std=c++20 -Ofast -pipe -o includes/pch.hpp.gch -Iincludes -Isources -Ilibraries -Iexterns includes/pch.hpp
//

#ifndef ___INCLUDE_GUARD_INCLUDES_PCH_HPP___
#define ___INCLUDE_GUARD_INCLUDES_PCH_HPP___

#include <concepts>
// #include <coroutine> // requires -fcoroutines
#include <any>
#include <bitset>
#include <chrono>
#include <compare>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <initializer_list>
#include <optional>
#include <source_location>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <variant>
#include <version>
#include <memory>
#include <memory_resource>
#include <new>
#include <scoped_allocator>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <cstdint>
#include <limits>
#include <cassert>
#include <cerrno>
#include <exception>
#include <stdexcept>
#include <system_error>
// #include <stacktrace> // c++23
#include <cctype>
#include <charconv>
#include <cstring>
#include <cuchar>
#include <cwchar>
#include <cwctype>
// #include <format> // c++23
#include <string>
#include <string_view>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <span>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iterator>
#include <ranges>
#include <algorithm>
// #include <execution> // linkage errors
#include <bit>
#include <cfenv>
#include <cmath>
#include <complex>
#include <numbers>
#include <numeric>
#include <random>
#include <ratio>
#include <valarray>
#include <clocale>
#include <codecvt>
#include <locale>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <ostream>
// #include <spanstream> // c++23
#include <sstream>
#include <streambuf>
#include <syncstream>
#include <filesystem>
#include <regex>
#include <atomic>
#include <barrier>
#include <condition_variable>
#include <future>
#include <latch>
#include <mutex>
#include <semaphore>
#include <shared_mutex>
#include <stop_token>
#include <thread>
#include <cstdio>

using ::std::string_literals::operator""s;
using ::std::literals::string_view_literals::operator""sv;
using ::std::chrono_literals::operator""ms;

#define PRINT_DEBUG
//#include <xrn/Log.hpp>
// #include <xrn/Meta>

#include <QtWidgets>
#include <QLineEdit>

#include <sqlite3.h>

#endif // ___INCLUDE_GUARD_INCLUDES_PCH_HPP___
