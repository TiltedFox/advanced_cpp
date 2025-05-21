#ifndef TYPEPTRMAP_H
#define TYPEPTRMAP_H

#include <any>
#include <array>
#include <initializer_list>
#include <ranges>
#include <iostream>
#include <variant>
#include <memory>
#include "../task2/TypeList.hpp"

template <typename... Ts>
class TypeMap
{
public:
    template <class T, class... Args>
    void AddValue(Args &&...args)
    {
        if (TypeList<Ts...>::template contains<T>)
        {
            constexpr std::size_t index = TypeList<Ts...>::template get_index<T>;
            values_ptrs_[index] = std::make_unique<T>(std::forward<Args>(args)...);
        }
        else
        {
            throw std::logic_error("TypeMap does not contains such type");
        }
    }

    template <class T>
    T &GetValue()
    {
        if (!Contains<T>())
        {
            std::string error = "Cant get this type; TypeMap does not contain such value or type";
            throw std::logic_error(error);
        }

        constexpr std::size_t index = TypeList<Ts...>::template get_index<T>;
        auto &slot = values_ptrs_[index];
        auto &ptr = std::get<std::unique_ptr<T>>(slot);

        return *ptr;
    }

    template <class T>
    bool Contains()
    {
        if (!TypeList<Ts...>::template contains<T>)
            return false;

        constexpr std::size_t index = TypeList<Ts...>::template get_index<T>;
        auto &slot = values_ptrs_[index];

        if (auto ptr_to_up = std::get_if<std::unique_ptr<T>>(&slot))
        {
            // ptr_to_up — указатель на std::unique_ptr<T>
            return *ptr_to_up != nullptr;
        }

        return false;
    }

    template <class T>
    void RemoveValue()
    {
        if (!Contains<T>())
        {
            std::string text = "Cant remove this type; TypeMap does not contain such value or type";
            throw std::logic_error(text);
        }
        constexpr auto index = TypeList<Ts...>::template get_index<T>;
        auto &var = values_ptrs_[index];

        // получаем ссылку на unique_ptr внутри variant
        auto &up = std::get<std::unique_ptr<T>>(var);

        up.reset();
    }

private:
    std::array<std::variant<std::unique_ptr<Ts>...>, TypeList<Ts...>::size> values_ptrs_{};
};

#endif // TYPEPTRMAP_H
