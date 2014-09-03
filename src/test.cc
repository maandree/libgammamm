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
#include <cstdlib>
#include <unistd.h>


int main(void)
{
  libgamma::Site* site;
  libgamma::Partition* partition;
  libgamma::CRTC* crtc;
  libgamma::CRTCInformation info;
  libgamma::MethodCapabilities caps;
  libgamma::GammaRamps<uint16_t>* ramps;
  int method;
  size_t i;
  
  uint16_t* saved_red;
  uint16_t* saved_green;
  uint16_t* saved_blue;
  
  std::string* str;
  char* cstr;
  unsigned char* edid;
  
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
  
  for (int m : libgamma::list_methods(0))
    std::cout << m << " ";
  std::cout << std::endl;
  for (int m : libgamma::list_methods(1))
    std::cout << m << " ";
  std::cout << std::endl;
  for (int m : libgamma::list_methods(2))
    std::cout << m << " ";
  std::cout << std::endl;
  for (int m : libgamma::list_methods(3))
    std::cout << m << " ";
  std::cout << std::endl;
  for (int m : libgamma::list_methods(4))
    std::cout << m << " ";
  std::cout << std::endl;
  std::cout << std::endl;
  method = libgamma::list_methods(0)[0];
  
  std::cout << libgamma::is_method_available(LIBGAMMA_METHOD_X_RANDR) << std::endl;
  str = libgamma::method_default_site(LIBGAMMA_METHOD_X_RANDR);
  if (str == nullptr)
    std::cout << "(nullptr)" << std::endl;
  else
    std::cout << *str << std::endl;
  delete str;
  str = libgamma::method_default_site_variable(LIBGAMMA_METHOD_X_RANDR);
  if (str == nullptr)
    std::cout << "(nullptr)" << std::endl;
  else
    std::cout << *str << std::endl;
  delete str;
  std::cout << std::endl;
  
  edid = libgamma::unhex_edid("0123456789abcdef");
  cstr = libgamma_behex_edid(edid, 8);
  std::cout << cstr << std::endl;
  free(cstr);
  std::cout << libgamma::behex_edid(edid, 8) << std::endl;
  std::cout << libgamma::behex_edid_lowercase(edid, 8) << std::endl;
  std::cout << libgamma::behex_edid_uppercase(edid, 8) << std::endl;
  free(edid);
  std::cout << std::endl;
  
  site = new libgamma::Site(method, new std::string(":0"));
  std::cout << site->partitions_available << std::endl;
  partition = new libgamma::Partition(site, 0);
  std::cout << partition->crtcs_available << std::endl;
  crtc = new libgamma::CRTC(partition, 0);
  std::cout << crtc->information(&info, ~0) << std::endl;
  std::cout << std::endl;
  
  cstr = libgamma_behex_edid(info.edid, info.edid_length);
  std::cout << "edid: " << cstr << std::endl;
  free(cstr);
  std::cout << "edid_length: " << info.edid_length << std::endl;
  std::cout << "edid_error: " << info.edid_error << std::endl;
  std::cout << "width_mm: " << info.width_mm << std::endl;
  std::cout << "width_mm_error: " << info.width_mm_error << std::endl;
  std::cout << "height_mm: " << info.height_mm << std::endl;
  std::cout << "height_mm_error: " << info.height_mm_error << std::endl;
  std::cout << "width_mm_edid: " << info.width_mm_edid << std::endl;
  std::cout << "width_mm_edid_error: " << info.width_mm_edid_error << std::endl;
  std::cout << "height_mm_edid: " << info.height_mm_edid << std::endl;
  std::cout << "height_mm_edid_error: " << info.height_mm_edid_error << std::endl;
  std::cout << "red_gamma_size: " << info.red_gamma_size << std::endl;
  std::cout << "green_gamma_size: " << info.green_gamma_size << std::endl;
  std::cout << "blue_gamma_size: " << info.blue_gamma_size << std::endl;
  std::cout << "gamma_size_error: " << info.gamma_size_error << std::endl;
  std::cout << "gamma_depth: " << info.gamma_depth << std::endl;
  std::cout << "gamma_depth_error: " << info.gamma_depth_error << std::endl;
  std::cout << "gamma_support: " << info.gamma_support << std::endl;
  std::cout << "gamma_support_error: " << info.gamma_support_error << std::endl;
  std::cout << "subpixel_order: " << info.subpixel_order << std::endl;
  std::cout << "subpixel_order_error: " << info.subpixel_order_error << std::endl;
  std::cout << "active: " << info.active << std::endl;
  std::cout << "active_error: " << info.active_error << std::endl;
  if (info.connector_name == nullptr)
    std::cout << "connector_name: " << "(nullptr)" << std::endl;
  else
    std::cout << "connector_name: " << *(info.connector_name) << std::endl;
  std::cout << "connector_name_error: " << info.connector_name_error << std::endl;
  std::cout << "connector_type: " << info.connector_type << std::endl;
  std::cout << "connector_type_error: " << info.connector_type_error << std::endl;
  std::cout << "gamma_red: " << info.gamma_red << std::endl;
  std::cout << "gamma_green: " << info.gamma_green << std::endl;
  std::cout << "gamma_blue: " << info.gamma_blue << std::endl;
  std::cout << "gamma_error: " << info.gamma_error << std::endl;
  std::cout << std::endl;
  
  libgamma::method_capabilities(&caps, method);
  std::cout << "crtc_information: " << caps.crtc_information << std::endl;
  std::cout << "default_site_known: " << caps.default_site_known << std::endl;
  std::cout << "multiple_sites: " << caps.multiple_sites << std::endl;
  std::cout << "multiple_partitions: " << caps.multiple_partitions << std::endl;
  std::cout << "multiple_crtcs: " << caps.multiple_crtcs << std::endl;
  std::cout << "partitions_are_graphics_cards: " << caps.partitions_are_graphics_cards << std::endl;
  std::cout << "site_restore: " << caps.site_restore << std::endl;
  std::cout << "partition_restore: " << caps.partition_restore << std::endl;
  std::cout << "crtc_restore: " << caps.crtc_restore << std::endl;
  std::cout << "identical_gamma_sizes: " << caps.identical_gamma_sizes << std::endl;
  std::cout << "fixed_gamma_size: " << caps.fixed_gamma_size << std::endl;
  std::cout << "fixed_gamma_depth: " << caps.fixed_gamma_depth << std::endl;
  std::cout << "real: " << caps.real << std::endl;
  std::cout << "fake: " << caps.fake << std::endl;
  std::cout << std::endl;
  
  std::cout << libgamma::group_gid << std::endl;
  libgamma::group_gid = 10;
  std::cout << libgamma::group_gid << std::endl;
  std::cout << std::endl;
  
  if (libgamma::group_name == nullptr)
    std::cout << "(nullptr)" << std::endl;
  else
    std::cout << libgamma::group_name << std::endl;
  libgamma::group_name = "test-group";
  if (libgamma::group_name == nullptr)
    std::cout << "(nullptr)" << std::endl;
  else
    std::cout << libgamma::group_name << std::endl;
  std::cout << std::endl;
  
  ramps = libgamma::gamma_ramps16_create(info.red_gamma_size, info.green_gamma_size, info.blue_gamma_size);
  std::cout << ramps->red.size << " "
	    << ramps->green.size << " "
	    << ramps->blue.size << std::endl;
  std::cout << ramps->depth << std::endl;
  std::cout << std::endl;
  
  saved_red = new uint16_t[ramps->red.size];
  saved_green = new uint16_t[ramps->green.size];
  saved_blue = new uint16_t[ramps->blue.size];
  
  crtc->get_gamma(ramps);
  
  for (i = 0; i < ramps->red.size; i++)
    {
      std::cout << ramps->red[i] << " ";
      saved_red[i] = ramps->red[i];
      ramps->red[i] /= 2;
    }
  std::cout << std::endl;
  std::cout << std::endl;
  
  for (i = 0; i < ramps->green.size; i++)
    {
      std::cout << ramps->green[i] << " ";
      saved_green[i] = ramps->green[i];
      ramps->green[i] /= 2;
    }
  std::cout << std::endl;
  std::cout << std::endl;
  
  for (i = 0; i < ramps->blue.size; i++)
    {
      std::cout << ramps->blue[i] << " ";
      saved_blue[i] = ramps->blue[i];
      ramps->blue[i] /= 2;
    }
  std::cout << std::endl;
  std::cout << std::endl;
  
  crtc->set_gamma(ramps);
  
  sleep(1);
  
  for (i = 0; i < ramps->red.size; i++)
    ramps->red[i] = saved_red[i];
  for (i = 0; i < ramps->green.size; i++)
    ramps->green[i] = saved_green[i];
  for (i = 0; i < ramps->blue.size; i++)
    ramps->blue[i] = saved_blue[i];
  
  crtc->set_gamma(ramps);
  
  delete [] saved_red;
  delete [] saved_green;
  delete [] saved_blue;
  delete ramps;
  
  sleep(1);
  
  ramps = new libgamma::GammaRamps<uint16_t>();
  libgamma::gamma_ramps16_initialise(ramps, info.red_gamma_size, info.green_gamma_size, info.blue_gamma_size);
  std::cout << ramps->red.size << " "
	    << ramps->green.size << " "
	    << ramps->blue.size << std::endl;
  std::cout << ramps->depth << std::endl;
  std::cout << std::endl;
  
  saved_red = new uint16_t[ramps->red.size];
  saved_green = new uint16_t[ramps->green.size];
  saved_blue = new uint16_t[ramps->blue.size];
  
  crtc->get_gamma(ramps);
  
  for (i = 0; i < ramps->red.size; i++)
    {
      std::cout << ramps->red[i] << " ";
      saved_red[i] = ramps->red[i];
      ramps->red[i] /= 2;
    }
  std::cout << std::endl;
  std::cout << std::endl;
  
  for (i = 0; i < ramps->green.size; i++)
    {
      std::cout << ramps->green[i] << " ";
      saved_green[i] = ramps->green[i];
      ramps->green[i] /= 2;
    }
  std::cout << std::endl;
  std::cout << std::endl;
  
  for (i = 0; i < ramps->blue.size; i++)
    {
      std::cout << ramps->blue[i] << " ";
      saved_blue[i] = ramps->blue[i];
      ramps->blue[i] /= 2;
    }
  std::cout << std::endl;
  std::cout << std::endl;
  
  crtc->set_gamma(ramps);
  
  sleep(1);
  
  for (i = 0; i < ramps->red.size; i++)
    ramps->red[i] = saved_red[i];
  for (i = 0; i < ramps->green.size; i++)
    ramps->green[i] = saved_green[i];
  for (i = 0; i < ramps->blue.size; i++)
    ramps->blue[i] = saved_blue[i];
  
  crtc->set_gamma(ramps);
  
  delete [] saved_red;
  delete [] saved_green;
  delete [] saved_blue;
  delete ramps;
  
  delete crtc;
  delete partition;
  delete site;
  
  try
    {
      throw libgamma::create_error(EIO);
    }
  catch (const libgamma::LibgammaException& err)
    {
      std::cout << err.what() << std::endl;
    }
  try
    {
      throw libgamma::create_error(LIBGAMMA_NO_SUCH_ADJUSTMENT_METHOD);
    }
  catch (const libgamma::LibgammaException& err)
    {
      std::cout << err.what() << std::endl;
    }
  
  return 0;
}

