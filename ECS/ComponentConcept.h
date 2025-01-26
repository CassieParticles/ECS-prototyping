#pragma once
#include <type_traits>

class BaseComponent;

template<typename T>
concept Component = std::is_base_of<BaseComponent, T>::value;