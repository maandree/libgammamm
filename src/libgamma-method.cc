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
#include "libgamma-method.hh"

#include "libgamma-error.hh"

#include <cstdlib>
#include <cstring>
#include <cerrno>


namespace libgamma
{
  /**
   * Constructor.
   */
  MethodCapabilities::MethodCapabilities() :
    crtc_information(0),
    default_site_known(false),
    multiple_sites(false),
    multiple_partitions(false),
    multiple_crtcs(false),
    partitions_are_graphics_cards(false),
    site_restore(false),
    partition_restore(false),
    crtc_restore(false),
    identical_gamma_sizes(false),
    fixed_gamma_size(false),
    fixed_gamma_depth(false),
    real(false),
    fake(false)
  {
    /* Do nothing. */
  }
  
  
  /**
   * Constructor.
   * 
   * @param  caps  The information in the native structure.
   */
  MethodCapabilities::MethodCapabilities(libgamma_method_capabilities_t* caps) :
    crtc_information(caps->crtc_information),
    default_site_known(caps->default_site_known),
    multiple_sites(caps->multiple_sites),
    multiple_partitions(caps->multiple_partitions),
    multiple_crtcs(caps->multiple_crtcs),
    partitions_are_graphics_cards(caps->partitions_are_graphics_cards),
    site_restore(caps->site_restore),
    partition_restore(caps->partition_restore),
    crtc_restore(caps->crtc_restore),
    identical_gamma_sizes(caps->identical_gamma_sizes),
    fixed_gamma_size(caps->fixed_gamma_size),
    fixed_gamma_depth(caps->fixed_gamma_depth),
    real(caps->real),
    fake(caps->fake)
  {
    /* Do nothing. */
  }
  
  
  /**
   * Copy constructor.
   * 
   * @param  other  The information to copy.
   */
  MethodCapabilities::MethodCapabilities(const MethodCapabilities& other) :
    crtc_information(other.crtc_information),
    default_site_known(other.default_site_known),
    multiple_sites(other.multiple_sites),
    multiple_partitions(other.multiple_partitions),
    multiple_crtcs(other.multiple_crtcs),
    partitions_are_graphics_cards(other.partitions_are_graphics_cards),
    site_restore(other.site_restore),
    partition_restore(other.partition_restore),
    crtc_restore(other.crtc_restore),
    identical_gamma_sizes(other.identical_gamma_sizes),
    fixed_gamma_size(other.fixed_gamma_size),
    fixed_gamma_depth(other.fixed_gamma_depth),
    real(other.real),
    fake(other.fake)
  {
    /* Do nothing. */
  }
  
  
  /**
   * Destructor.
   */
  MethodCapabilities::~MethodCapabilities()
  {
    /* Do nothing. */
  }
  
  
  /**
   * Copy operator.
   * 
   * @param  other  The information to copy.
   */
  MethodCapabilities& MethodCapabilities::operator =(const MethodCapabilities& other)
  {
    this->crtc_information = other.crtc_information;
    this->default_site_known = other.default_site_known;
    this->multiple_sites = other.multiple_sites;
    this->multiple_partitions = other.multiple_partitions;
    this->multiple_crtcs = other.multiple_crtcs;
    this->partitions_are_graphics_cards = other.partitions_are_graphics_cards;
    this->site_restore = other.site_restore;
    this->partition_restore = other.partition_restore;
    this->crtc_restore = other.crtc_restore;
    this->identical_gamma_sizes = other.identical_gamma_sizes;
    this->fixed_gamma_size = other.fixed_gamma_size;
    this->fixed_gamma_depth = other.fixed_gamma_depth;
    this->real = other.real;
    this->fake = other.fake;
    
    return *this;
  }
  
  
  
  
  
  /**
   * Constructor.
   */
  CRTCInformation::CRTCInformation() :
    edid(nullptr),
    edid_length(0),
    edid_error(0),
    width_mm(0),
    width_mm_error(0),
    height_mm(0),
    height_mm_error(0),
    width_mm_edid(0),
    width_mm_edid_error(0),
    height_mm_edid(0),
    height_mm_edid_error(0),
    red_gamma_size(0),
    green_gamma_size(0),
    blue_gamma_size(0),
    gamma_size_error(0),
    gamma_depth(0),
    gamma_depth_error(0),
    gamma_support(0),
    gamma_support_error(0),
    subpixel_order((SubpixelOrder)0),
    subpixel_order_error(0),
    active(0),
    active_error(0),
    connector_name(nullptr),
    connector_name_error(0),
    connector_type((ConnectorType)0),
    connector_type_error(0),
    gamma_red(0),
    gamma_green(0),
    gamma_blue(0),
    gamma_error(0)
  {
    /* Do nothing. */
  }
  
  
  /**
   * Constructor.
   * 
   * @param  info  The information in the native structure.
   */
  CRTCInformation::CRTCInformation(libgamma_crtc_information_t* info) :
    edid(info->edid),
    edid_length(info->edid_length),
    edid_error(info->edid_error),
    width_mm(info->width_mm),
    width_mm_error(info->width_mm_error),
    height_mm(info->height_mm),
    height_mm_error(info->height_mm_error),
    width_mm_edid(info->width_mm_edid),
    width_mm_edid_error(info->width_mm_edid_error),
    height_mm_edid(info->height_mm_edid),
    height_mm_edid_error(info->height_mm_edid_error),
    red_gamma_size(info->red_gamma_size),
    green_gamma_size(info->green_gamma_size),
    blue_gamma_size(info->blue_gamma_size),
    gamma_size_error(info->gamma_size_error),
    gamma_depth(info->gamma_depth),
    gamma_depth_error(info->gamma_depth_error),
    gamma_support(info->gamma_support),
    gamma_support_error(info->gamma_support_error),
    subpixel_order(info->subpixel_order),
    subpixel_order_error(info->subpixel_order_error),
    active(info->active),
    active_error(info->active_error),
    connector_name(nullptr),
    connector_name_error(info->connector_name_error),
    connector_type(info->connector_type),
    connector_type_error(info->connector_type_error),
    gamma_red(info->gamma_red),
    gamma_green(info->gamma_green),
    gamma_blue(info->gamma_blue),
    gamma_error(info->gamma_error)
  {
    if (info->connector_name != nullptr)
      {
	this->connector_name = new std::string(info->connector_name);
	free(info->connector_name);
      }
  }
  
  
  /**
   * Copy constructor.
   * 
   * @param  other  The information to copy.
   */
  CRTCInformation::CRTCInformation(const CRTCInformation& other) :
    edid(nullptr),
    edid_length(other.edid_length),
    edid_error(other.edid_error),
    width_mm(other.width_mm),
    width_mm_error(other.width_mm_error),
    height_mm(other.height_mm),
    height_mm_error(other.height_mm_error),
    width_mm_edid(other.width_mm_edid),
    width_mm_edid_error(other.width_mm_edid_error),
    height_mm_edid(other.height_mm_edid),
    height_mm_edid_error(other.height_mm_edid_error),
    red_gamma_size(other.red_gamma_size),
    green_gamma_size(other.green_gamma_size),
    blue_gamma_size(other.blue_gamma_size),
    gamma_size_error(other.gamma_size_error),
    gamma_depth(other.gamma_depth),
    gamma_depth_error(other.gamma_depth_error),
    gamma_support(other.gamma_support),
    gamma_support_error(other.gamma_support_error),
    subpixel_order(other.subpixel_order),
    subpixel_order_error(other.subpixel_order_error),
    active(other.active),
    active_error(other.active_error),
    connector_name(nullptr),
    connector_name_error(other.connector_name_error),
    connector_type(other.connector_type),
    connector_type_error(other.connector_type_error),
    gamma_red(other.gamma_red),
    gamma_green(other.gamma_green),
    gamma_blue(other.gamma_blue),
    gamma_error(other.gamma_error)
  {
    if (other.edid != nullptr)
      {
	this->edid = (unsigned char*)malloc(this->edid_length * sizeof(unsigned char));
	memcpy(this->edid, other.edid, this->edid_length * sizeof(unsigned char));
      }
    if (other.connector_name != nullptr)
      this->connector_name = new std::string(*(other.connector_name));
  }
  
  
  /**
   * Destructor.
   */
  CRTCInformation::~CRTCInformation()
  {
    if (this->connector_name != nullptr)
      delete this->connector_name;
    free(this->edid);
  }
  
  
  /**
   * Copy operator.
   * 
   * @param  other  The information to copy.
   */
  CRTCInformation& CRTCInformation::operator =(const CRTCInformation& other)
  {
    this->edid = nullptr;
    this->edid_length = other.edid_length;
    this->edid_error = other.edid_error;
    this->width_mm = other.width_mm;
    this->width_mm_error = other.width_mm_error;
    this->height_mm = other.height_mm;
    this->height_mm_error = other.height_mm_error;
    this->width_mm_edid = other.width_mm_edid;
    this->width_mm_edid_error = other.width_mm_edid_error;
    this->height_mm_edid = other.height_mm_edid;
    this->height_mm_edid_error = other.height_mm_edid_error;
    this->red_gamma_size = other.red_gamma_size;
    this->green_gamma_size = other.green_gamma_size;
    this->blue_gamma_size = other.blue_gamma_size;
    this->gamma_size_error = other.gamma_size_error;
    this->gamma_depth = other.gamma_depth;
    this->gamma_depth_error = other.gamma_depth_error;
    this->gamma_support = other.gamma_support;
    this->gamma_support_error = other.gamma_support_error;
    this->subpixel_order = other.subpixel_order;
    this->subpixel_order_error = other.subpixel_order_error;
    this->active = other.active;
    this->active_error = other.active_error;
    this->connector_name = nullptr;
    this->connector_name_error = other.connector_name_error;
    this->connector_type = other.connector_type;
    this->connector_type_error = other.connector_type_error;
    this->gamma_red = other.gamma_red;
    this->gamma_green = other.gamma_green;
    this->gamma_blue = other.gamma_blue;
    this->gamma_error = other.gamma_error;
    
    if (other.edid != nullptr)
      {
	this->edid = (unsigned char*)malloc(this->edid_length * sizeof(unsigned char));
	memcpy(this->edid, other.edid, this->edid_length * sizeof(unsigned char));
      }
    if (other.connector_name != nullptr)
      this->connector_name = new std::string(*(other.connector_name));
    
    return *this;
  }
  
#ifdef __GCC__
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wshadow"
#endif
  
  /**
   * Constructor.
   */
  Site::Site() :
    method(0),
    site(nullptr),
    partitions_available(0),
    native(nullptr)
  {
    /* Do nothing. */
  }
  
  /**
   * Constructor.
   * 
   * @param  method  The adjustment method of the site.
   * @param  site    The site identifier, will be moved into
   *                 the structure, must be `delete`:able.
   */
  Site::Site(int method, std::string* site) :
    method(method),
    site(site),
    partitions_available(0),
    native(nullptr)
  {
    char* cstr = nullptr;
    int r;
    
    if (site != nullptr)
      {
	const char* cstr_ = site->c_str();
	cstr = (char*)malloc((strlen(cstr_) + 1) * sizeof(char));
	memcpy(cstr, cstr_, (strlen(cstr_) + 1) * sizeof(char));
      }
    this->native = (libgamma_site_state_t*)malloc(sizeof(libgamma_site_state_t));
    r = libgamma_site_initialise(this->native, method, cstr);
    if (r < 0)
      {
	int saved_errno = errno;
	free(this->native);
	this->native = nullptr;
	errno = saved_errno;
	throw create_error(r);
      }
    this->partitions_available = this->native->partitions_available;
  }
  
  /**
   * Destructor.
   */
  Site::~Site()
  {
    if (this->site != nullptr)
      delete this->site;
    if (this->native != nullptr)
      libgamma_site_free(this->native);
  }
  
  /**
   * Restore the gamma ramps all CRTC:s with a site to
   * the system settings.
   */
  void Site::restore()
  {
    int r;
    r = libgamma_site_restore(this->native);
    if (r != 0)
      throw create_error(r);
  }
  
  
  
  /**
   * Constructor.
   */
  Partition::Partition() :
    site(nullptr),
    partition(0),
    crtcs_available(0),
    native(nullptr)
  {
    /* Do nothing. */
  }
  
  /**
   * Constructor.
   * 
   * @param  site       The site of the partition.
   * @param  partition  The index of the partition.
   */
  Partition::Partition(Site* site, size_t partition) :
    site(site),
    partition(partition),
    crtcs_available(0),
    native(nullptr)
  {
    int r;
    this->native = (libgamma_partition_state_t*)malloc(sizeof(libgamma_partition_state_t));
    r = libgamma_partition_initialise(this->native, site->native, partition);
    if (r < 0)
      {
	int saved_errno = errno;
	free(this->native);
	this->native = nullptr;
	errno = saved_errno;
	throw create_error(r);
      }
    this->crtcs_available = this->native->crtcs_available;
  }
  
  /**
   * Destructor.
   */
  Partition::~Partition()
  {
    if (this->native != nullptr)
      libgamma_partition_free(this->native);
  }
  
  /**
   * Restore the gamma ramps all CRTC:s with a partition
   * to the system settings.
   */
  void Partition::restore()
  {
    int r;
    r = libgamma_partition_restore(this->native);
    if (r != 0)
      throw create_error(r);
  }
  
  
  
  /**
   * Constructor.
   */
  CRTC::CRTC() :
    partition(nullptr),
    crtc(0),
    native(nullptr)
  {
    /* Do nothing. */
  }
  
  /**
   * Constructor.
   * 
   * @param  partition  The partition of the CRTC.
   * @param  crtc       The index of the CRTC.
   */
  CRTC::CRTC(Partition* partition, size_t crtc) :
    partition(partition),
    crtc(crtc),
    native(nullptr)
  {
    int r;
    this->native = (libgamma_crtc_state_t*)malloc(sizeof(libgamma_crtc_state_t));
    r = libgamma_crtc_initialise(this->native, partition->native, crtc);
    if (r < 0)
      {
	int saved_errno = errno;
	free(this->native);
	this->native = nullptr;
	errno = saved_errno;
	throw create_error(r);
      }
  }
  
  /**
   * Destructor.
   */
  CRTC::~CRTC()
  {
    if (this->native != nullptr)
      libgamma_crtc_free(this->native);
  }
  
  /**
   * Restore the gamma ramps for a CRTC to the system
   * settings for that CRTC.
   */
  void CRTC::restore()
  {
    int r;
    r = libgamma_crtc_restore(this->native);
    if (r != 0)
      throw create_error(r);
  }
  
  /**
   * Read information about a CRTC.
   * 
   * @param   output  Instance of a data structure to fill with the information about the CRTC.
   * @param   fields  OR:ed identifiers for the information about the CRTC that should be read.
   * @return          Whether an error has occurred and is stored in a `*_error` field.
   */
  bool CRTC::information(CRTCInformation* output, int32_t fields)
  {
    libgamma_crtc_information_t info;
    int r;
    
    r = libgamma_get_crtc_information(&info, this->native, fields);
    *output = CRTCInformation(&info);
    return r != 0;
  }
  
#ifdef __GCC__
# pragma GCC diagnostic pop
#endif
  
}

