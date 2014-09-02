/**
 * libgammamm -- C++ wrapper for libgamma
 * Copyright (C) 2014  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "libgamma.hh"

#include <iostream>


int main(void)
{
  std::string* str;
  
  libgamma::perror("test", 0);
  libgamma::perror("test", 2);
  libgamma::perror("test", -2);
  libgamma::perror("test", LIBGAMMA_ERRNO_SET);
  std::cout << std::endl;
  
  str = libgamma::name_of_error(-2);
  std::cout << *str << std::endl;
  std::cout << libgamma::value_of_error(str) << std::endl;
  delete str;
  str = new std::string("LIBGAMMA_NO_SUCH_ADJUSTMENT_METHOD");
  std::cout << libgamma::value_of_error(str) << std::endl;
  delete str;
  std::cout << std::endl;
  
  return 0;
}

