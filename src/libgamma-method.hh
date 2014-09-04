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
#ifndef LIBGAMMA_METHOD_HH
#define LIBGAMMA_METHOD_HH


#include <string>
#include <cstdlib>

#include "libgamma-native.hh"
#include "libgamma-error.hh"


#ifndef __GCC__
# define __attribute__(X) /* emtpy */
#endif



namespace libgamma
{
  /**
   * Cathode ray tube controller information data structure.
   */
  class CRTCInformation;
  
  /**
   * Capabilities of adjustment methods.
   */
  class MethodCapabilities;
  
  /**
   * Site state.
   * 
   * On operating systems that integrate a graphical environment
   * there is usually just one site. However, one systems with
   * pluggable graphics, like Unix-like systems such as GNU/Linux
   * and the BSD:s, there can usually be any (feasible) number of
   * sites. In X.org parlance they are called displays.
   */
  class Site;
  
  /**
   * Partition state.
   * 
   * Probably the majority of display server only one partition
   * per site. However, X.org can, and traditional used to have
   * on multi-headed environments, multiple partitions per site.
   * In X.org partitions are called 'screens'. It is not to be
   * confused with monitor. A screen is a collection of monitors,
   * and the mapping from monitors to screens is a surjection.
   * On hardware-level adjustment methods, such as Direct
   * Rendering Manager, a partition is a graphics card.
   */
  class Partition;
  
  /**
   * Cathode ray tube controller state.
   * 
   * The CRTC controls the gamma ramps for the
   * monitor that is plugged in to the connector
   * that the CRTC belongs to.
   */
  class CRTC;
  
  
  
  /**
   * Capabilities of adjustment methods.
   */
  class MethodCapabilities
  {
  public:
    /**
     * Constructor.
     */
    MethodCapabilities();
    
    /**
     * Constructor.
     * 
     * @param  caps  The information in the native structure.
     */
    MethodCapabilities(libgamma_method_capabilities_t* caps);
    
    /**
     * Copy constructor.
     * 
     * @param  other  The information to copy.
     */
    MethodCapabilities(const MethodCapabilities& other);
    
    /**
     * Destructor.
     */
    ~MethodCapabilities() __attribute__((const));
    
    /**
     * Copy operator.
     * 
     * @param  other  The information to copy.
     */
    MethodCapabilities& operator =(const MethodCapabilities& other);
    
    
    
    
    /**
     * OR of the CRTC information fields in `libgamma_crtc_information_t`
     * that may (but can fail) be read successfully.
     */
    int32_t crtc_information;
    
    /**
     * Whether the default site is known, if true the site is integrated
     * to the system or can be determined using environment variables.
     */
    bool default_site_known;
    
    /**
     * Whether the adjustment method supports multiple sites rather
     * than just the default site.
     */
    bool multiple_sites;
    
    /**
     * Whether the adjustment method supports multiple partitions
     * per site.
     */
    bool multiple_partitions;
    
    /**
     * Whether the adjustment method supports multiple CRTC:s
     * per partition per site.
     */
    bool multiple_crtcs;
    
    /**
     * Whether the partition to graphics card is a bijection.
     */
    bool partitions_are_graphics_cards;
    
    /**
     * Whether the adjustment method supports `libgamma_site_restore`.
     */
    bool site_restore;
    
    /**
     * Whether the adjustment method supports `libgamma_partition_restore`.
     */
    bool partition_restore;
    
    /**
     * Whether the adjustment method supports `libgamma_crtc_restore`.
     */
    bool crtc_restore;
    
    /**
     * Whether the `red_gamma_size`, `green_gamma_size` and `blue_gamma_size`
     * fields in `libgamma_crtc_information_t` will always have the same
     * values as each other for the adjustment method.
     */
    bool identical_gamma_sizes;
    
    /**
     * Whether the `red_gamma_size`, `green_gamma_size` and `blue_gamma_size`
     * fields in `libgamma_crtc_information_t` will always be filled with the
     * same value for the adjustment method.
     */
    bool fixed_gamma_size;
    
    /**
     * Whether the `gamma_depth` field in `libgamma_crtc_information_t`
     * will always be filled with the same value for the adjustment method.
     */
    bool fixed_gamma_depth;
    
    /**
     * Whether the adjustment method will actually perform adjustments.
     */
    bool real;
    
    /**
     * Whether the adjustment method is implement using a translation layer.
     */
    bool fake;
    
  };
  
  
  /**
   * Types for connectors.
   */
  typedef libgamma_connector_type_t ConnectorType;
  
  /**
   * Orders for subpixels. Currently the possible values are
   * very biased to LCD, Plasma and monochrome monitors.
   */
  typedef libgamma_subpixel_order_t SubpixelOrder;
  
  
  /**
   * Cathode ray tube controller information data structure.
   */
  class CRTCInformation
  {
  public:
    /**
     * Constructor.
     */
    CRTCInformation();
    
    /**
     * Constructor.
     * 
     * @param  info  The information in the native structure.
     */
    CRTCInformation(libgamma_crtc_information_t* info);
    
    /**
     * Copy constructor.
     * 
     * @param  other  The information to copy.
     */
    CRTCInformation(const CRTCInformation& other);
    
    /**
     * Destructor.
     */
    ~CRTCInformation();
    
    /**
     * Copy operator.
     * 
     * @param  other  The information to copy.
     */
    CRTCInformation& operator =(const CRTCInformation& other);
    
    
    
    /**
     * The Extended Display Identification Data associated with
     * the attached monitor. This is raw byte array that is usually
     * 128 bytes long. It is not NUL-terminate, rather its length
     * is stored in `edid_length`.
     */
    unsigned char* edid;
    
    /**
     * The length of `edid`.
     */
    size_t edid_length;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int edid_error;
    
    
    /**
     * The phyical width, in millimetres, of the viewport of the
     * attached monitor, as reported by the adjustment method. This
     * value may be incorrect, which is a known issue with the X
     * server where it is the result of the X server attempting
     * the estimate the size on its own.
     * Zero means that its is not applicable, which is the case
     * for projectors.
     */
    size_t width_mm;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int width_mm_error;
    
    
    /**
     * The phyical height, in millimetres, of the viewport of the
     * attached monitor, as reported by the adjustment method. This
     * value may be incorrect, which is a known issue with the X
     * server where it is the result of the X server attempting
     * the estimate the size on its own.
     * Zero means that its is not applicable, which is the case
     * for projectors.
     */
    size_t height_mm;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int height_mm_error;
    
    
    /**
     * The phyical width, in millimetres, of the viewport of the
     * attached monitor, as reported by it the monitor's Extended
     * Display Information Data. This value can only contain whole
     * centimetres, which means that the result is always zero
     * modulus ten. However, this could change with revisions of
     * the EDID structure.
     * Zero means that its is not applicable, which is the case
     * for projectors.
     */
    size_t width_mm_edid;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int width_mm_edid_error;
    
    
    /**
     * The phyical height, in millimetres, of the viewport of the
     * attached monitor, as reported by it the monitor's Extended
     * Display Information Data. This value can only contain whole
     * centimetres, which means that the result is always zero
     * modulus ten. However, this could change with revisions of
     * the EDID structure.
     * Zero means that its is not applicable, which is the case
     * for projectors.
     */
    size_t height_mm_edid;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int height_mm_edid_error;
    
    
    /**
     * The size of the encoding axis of the red gamma ramp.
     */
    size_t red_gamma_size;
    
    /**
     * The size of the encoding axis of the green gamma ramp.
     */
    size_t green_gamma_size;
    
    /**
     * The size of the encoding axis of the blue gamma ramp.
     */
    size_t blue_gamma_size;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int gamma_size_error;
    
    
    /**
     * The bit-depth of the value axes of gamma ramps,
     * -1 for single precision floating point, and -2 for
     * double precision floating point.
     */
    signed gamma_depth;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int gamma_depth_error;
    
    
    /**
     * Non-zero gamma ramp adjustments are supported.
     */
    int gamma_support;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int gamma_support_error;
    
    
    /**
     * The layout of the subpixels.
     * You cannot count on this value --- especially for CRT:s ---
     * but it is provided anyway as a means of distinguishing monitors.
     */
    SubpixelOrder subpixel_order;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int subpixel_order_error;
    
    
    /**
     * Whether there is a monitors connected to the CRTC.
     */
    int active;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int active_error;
    
    
    /**
     * The name of the connector as designated by the display
     * server or as give by this library in case the display
     * server lacks this feature.
     */
    std::string* connector_name;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int connector_name_error;
    
    
    /**
     * The type of the connector that is associated with the CRTC.
     */
    ConnectorType connector_type;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int connector_type_error;
    
    
    /**
     * The gamma characteristics of the monitor as reported
     * in its Extended Display Information Data. The value
     * holds the value for the red channel. If you do not have
     * and more accurate measurement of the gamma for the
     * monitor this could be used to give a rought gamma
     * correction; simply divide the value with 2.2 and use
     * the result for the red channel in the gamma correction.
     */
    float gamma_red;
    
    /**
     * The gamma characteristics of the monitor as reported
     * in its Extended Display Information Data. The value
     * holds the value for the green channel. If you do not have
     * and more accurate measurement of the gamma for the
     * monitor this could be used to give a rought gamma
     * correction; simply divide the value with 2.2 and use
     * the result for the green channel in the gamma correction.
     */
    float gamma_green;
    
    /**
     * The gamma characteristics of the monitor as reported
     * in its Extended Display Information Data. The value
     * holds the value for the blue channel. If you do not have
     * and more accurate measurement of the gamma for the
     * monitor this could be used to give a rought gamma
     * correction; simply divide the value with 2.2 and use
     * the result for the blue channel in the gamma correction.
     */
    float gamma_blue;
    
    /**
     * Zero on success, positive it holds the value `errno` had
     * when the reading failed, otherwise (negative) the value
     * of an error identifier provided by this library.
     */
    int gamma_error;
    
  };
  
  
  
#ifdef __GCC__
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Weffc++"
  /* Lets ignore that we do not override the copy constructor
   * and the copy operator. */
#endif
  
  /**
   * One single Gamma ramp.
   */
  template <typename T>
  class Ramp
  {
  public:
    /**
     * Constructor.
     * 
     * @param  native_ramp  The ramp.
     * @param  ramp_size    The size of the ramp.
     */
    Ramp(T* native_ramp, size_t ramp_size)
    {
      this->ramp = native_ramp;
      this->size = ramp_size;
    }
    
    /**
     * Destructor.
     */
    ~Ramp()
    {
      /* Do nothing */
    }
    
    /**
     * Subscript operator.
     * 
     * @param   index  The index of the stop to set or get.
     * @return         A reference to the stop's value.
     */
    T& operator [](size_t index)
    {
      return this->ramp[index];
    }
    
    /**
     * Subscript operator.
     * 
     * @param   index  The index of the stop to get.
     * @return         The value of the stop.
     */
    const T& operator [](size_t index) const
    {
      return this->ramp[index];
    }
    
    
    
    /**
     * The size of the ramp.
     */
    size_t size;
    
    /**
     * The ramp (internal data).
     */
    T* ramp;
    
  };
  
  
  /**
   * Gamma ramp structure.
   */
  template <typename T>
  class GammaRamps
  {
  public:
    /**
     * Constructor.
     */
    GammaRamps() :
      red(Ramp<T>(nullptr, 0)),
      green(Ramp<T>(nullptr, 0)),
      blue(Ramp<T>(nullptr, 0)),
      depth(0)
    {
      /* Do nothing. */
    }
    
    /**
     * Constructor.
     * 
     * @param  red_ramp     The red gamma ramp.
     * @param  green_ramp   The green gamma ramp.
     * @param  blue_ramp    The blue gamma ramp.
     * @param  red_size     The size of the gamma ramp for the red channel.
     * @param  green_size   The size of the gamma ramp for the green channel.
     * @param  blue_size    The size of the gamma ramp for the blue channel.
     * @param  gamma_depth  The bit-depth of the gamma ramps, -1 for single precision
     *                      floating point, and -2 for double precision floating point.
     */
    GammaRamps(T* red_ramp, T* green_ramp, T* blue_ramp,
	       size_t red_size, size_t green_size, size_t blue_size, signed gamma_depth) :
      red(Ramp<T>(red_ramp, red_size)),
      green(Ramp<T>(green_ramp, green_size)),
      blue(Ramp<T>(blue_ramp, blue_size)),
      depth(gamma_depth)
    {
      /* Do nothing. */
    }
    
    /**
     * Destructor.
     */
    ~GammaRamps()
    {
      free(this->red.ramp);
    }
    
    
    
    /**
     * The red gamma ramp.
     */
    Ramp<T> red;
    
    /**
     * The green gamma ramp.
     */
    Ramp<T> green;
    
    /**
     * The blue gamma ramp.
     */
    Ramp<T> blue;
    
    /**
     * The bit-depth of the gamma ramps, -1 for single precision
     * floating point, and -2 for double precision floating point.
     */
    signed depth;
    
  };
  
  
  
  /**
   * Site state.
   * 
   * On operating systems that integrate a graphical environment
   * there is usually just one site. However, one systems with
   * pluggable graphics, like Unix-like systems such as GNU/Linux
   * and the BSD:s, there can usually be any (feasible) number of
   * sites. In X.org parlance they are called displays.
   */
  class Site
  {
  public:
    /**
     * Constructor.
     */
    Site();
    
    /**
     * Constructor.
     * 
     * @param  method  The adjustment method of the site.
     * @param  site    The site identifier, will be moved into
     *                 the structure, must be `delete`:able.
     */
    Site(int method, std::string* site = nullptr);
    
    /**
     * Destructor.
     */
    ~Site();
    
    /**
     * Restore the gamma ramps all CRTC:s with a site to
     * the system settings.
     */
    void restore();
    
    
    
    /**
     * This field specifies, for the methods if this library,
     * which adjustment method (display server and protocol)
     * is used to adjust the gamma ramps.
     */
    int method;
    
    /**
     * The site identifier. It can either be `nullptr` or a string.
     * `nullptr` indicates the default site. On systems like the
     * Unix-like systems, where the graphics are pluggable, this
     * is usually resolved by an environment variable, such as
     * "DISPLAY" for X.org.
     */
    std::string* site;
    
    /**
     * The number of partitions that is available on this site.
     * Probably the majority of display server only one partition
     * per site. However, X.org can, and traditional used to have
     * on multi-headed environments, multiple partitions per site.
     * In X.org partitions are called 'screens'. It is not to be
     * confused with monitor. A screen is a collection of monitors,
     * and the mapping from monitors to screens is a surjection.
     * On hardware-level adjustment methods, such as Direct
     * Rendering Manager, a partition is a graphics card.
     */
    size_t partitions_available;
    
    /**
     * The state in the native structure.
     */
    libgamma_site_state_t* native;
    
  };
  
  
  
  /**
   * Partition state.
   * 
   * Probably the majority of display server only one partition
   * per site. However, X.org can, and traditional used to have
   * on multi-headed environments, multiple partitions per site.
   * In X.org partitions are called 'screens'. It is not to be
   * confused with monitor. A screen is a collection of monitors,
   * and the mapping from monitors to screens is a surjection.
   * On hardware-level adjustment methods, such as Direct
   * Rendering Manager, a partition is a graphics card.
   */
  class Partition
  {
  public:
    /**
     * Constructor.
     */
    Partition();
    
    /**
     * Constructor.
     * 
     * @param  site       The site of the partition.
     * @param  partition  The index of the partition.
     */
    Partition(Site* site, size_t partition);
    
    /**
     * Destructor.
     */
    ~Partition();
    
    /**
     * Restore the gamma ramps all CRTC:s with a partition
     * to the system settings.
     */
    void restore();
    
    
    
    /**
     * The site this partition belongs to.
     */
    Site* site;
    
    /**
     * The index of the partition.
     */
    size_t partition;
    
    /**
     * The number of CRTC:s that are available under this
     * partition. Note that the CRTC:s are not necessarily
     * online.
     */
    size_t crtcs_available;
    
    /**
     * The state in the native structure.
     */
    libgamma_partition_state_t* native;
    
  };
  
  
  
  /**
   * Cathode ray tube controller state.
   * 
   * The CRTC controls the gamma ramps for the
   * monitor that is plugged in to the connector
   * that the CRTC belongs to.
   */
  class CRTC
  {
  public:
    /**
     * Constructor.
     */
    CRTC();
    
    /**
     * Constructor.
     * 
     * @param  partition  The partition of the CRTC.
     * @param  crtc       The index of the CRTC.
     */
    CRTC(Partition* partition, size_t crtc);
    
    /**
     * Destructor.
     */
    ~CRTC();
    
    /**
     * Restore the gamma ramps for a CRTC to the system
     * settings for that CRTC.
     */
    void restore();
    
    /**
     * Read information about a CRTC.
     * 
     * @param   output  Instance of a data structure to fill with the information about the CRTC.
     * @param   fields  OR:ed identifiers for the information about the CRTC that should be read.
     * @return          Whether an error has occurred and is stored in a `*_error` field.
     */
    bool information(CRTCInformation* output, int32_t fields);
    
#define __LIBGAMMA_GET_GAMMA(AFFIX)						\
    libgamma_gamma_ramps ## AFFIX ## _t ramps_;					\
    int r;									\
    ramps_.red = ramps->red.ramp;						\
    ramps_.green = ramps->green.ramp;						\
    ramps_.blue = ramps->blue.ramp;						\
    ramps_.red_size = ramps->red.size;						\
    ramps_.green_size = ramps->green.size;					\
    ramps_.blue_size = ramps->blue.size;					\
    r = libgamma_crtc_get_gamma_ramps ## AFFIX(this->native, &ramps_);		\
    if (r != 0)									\
      throw create_error(r)
    
    /**
     * Get the current gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void get_gamma(GammaRamps<uint8_t>* ramps)
    {
      __LIBGAMMA_GET_GAMMA(8);
    }
    
    /**
     * Get the current gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void get_gamma(GammaRamps<uint16_t>* ramps)
    {
      __LIBGAMMA_GET_GAMMA(16);
    }
    
    /**
     * Get the current gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void get_gamma(GammaRamps<uint32_t>* ramps)
    {
      __LIBGAMMA_GET_GAMMA(32);
    }
    
    /**
     * Get the current gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void get_gamma(GammaRamps<uint64_t>* ramps)
    {
      __LIBGAMMA_GET_GAMMA(64);
    }
    
    /**
     * Get the current gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void get_gamma(GammaRamps<float>* ramps)
    {
      __LIBGAMMA_GET_GAMMA(f);
    }
    
    /**
     * Get the current gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void get_gamma(GammaRamps<double>* ramps)
    {
      __LIBGAMMA_GET_GAMMA(d);
    }
    
#undef __LIBGAMMA_GET_GAMMA
    
#define __LIBGAMMA_SET_GAMMA(AFFIX)						\
    libgamma_gamma_ramps ## AFFIX ## _t ramps_;					\
    int r;									\
    ramps_.red = ramps->red.ramp;						\
    ramps_.green = ramps->green.ramp;						\
    ramps_.blue = ramps->blue.ramp;						\
    ramps_.red_size = ramps->red.size;						\
    ramps_.green_size = ramps->green.size;					\
    ramps_.blue_size = ramps->blue.size;					\
    r = libgamma_crtc_set_gamma_ramps ## AFFIX(this->native, ramps_);		\
    if (r != 0)									\
      throw create_error(r)
    
    /**
     * Set gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void set_gamma(GammaRamps<uint8_t>* ramps)
    {
      __LIBGAMMA_SET_GAMMA(8);
    }
    
    /**
     * Set gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void set_gamma(GammaRamps<uint16_t>* ramps)
    {
      __LIBGAMMA_SET_GAMMA(16);
    }
    
    /**
     * Set gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void set_gamma(GammaRamps<uint32_t>* ramps)
    {
      __LIBGAMMA_SET_GAMMA(32);
    }
    
    /**
     * Set gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void set_gamma(GammaRamps<uint64_t>* ramps)
    {
      __LIBGAMMA_SET_GAMMA(64);
    }
    
    /**
     * Set gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void set_gamma(GammaRamps<float>* ramps)
    {
      __LIBGAMMA_SET_GAMMA(f);
    }
    
    /**
     * Set gamma ramps for the CRTC.
     * 
     * @param  ramps  The gamma ramps to fill with the current values.
     */
    void set_gamma(GammaRamps<double>* ramps)
    {
      __LIBGAMMA_SET_GAMMA(d);
    }
    
#undef __LIBGAMMA_SET_GAMMA
    
    
    
    /**
     * The partition this CRTC belongs to.
     */
    Partition* partition;
    
    /**
     * The index of the CRTC within its partition.
     */
    size_t crtc;
    
    /**
     * The state in the native structure.
     */
    libgamma_crtc_state_t* native;
    
  };
  
#ifdef __GCC__
# pragma GCC diagnostic pop
#endif
  
}


#ifndef __GCC__
# undef __attribute__
#endif

#endif

