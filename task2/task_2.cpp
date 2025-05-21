#include "TypeList.hpp"
#include <iostream>
#include <string>

int main()
{
   constexpr TypeList<int, double, std::string, float, int> type_list;

   std::cout << type_list.size << std::endl;

   std::cout << type_list.contains<std::string> << std::endl;

   // queals type_list.size if no such type exists
   std::cout << "index: " << type_list.get_index<int, 2> << std::endl;

   using type_list_type = TypeList<int, double, std::string, float, int>;
   std::cout << std::is_same_v<type_list_type::type_by_index<3>, int> << std::endl;

   auto excep1 = type_list.push_back<std::exception>;
   std::cout << type_list.contains<std::exception> << std::endl;
   std::cout << excep1.contains<std::exception> << " " << excep1.get_index<std::exception> << std::endl;

   auto excep2 = type_list.push_front<std::exception>;
   std::cout << type_list.contains<std::exception> << std::endl;
   std::cout << excep2.contains<std::exception> << " " << excep2.get_index<std::exception> << std::endl;
}