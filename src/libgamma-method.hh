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

#include "libgamma-native.hh"


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
     * @param  caps  The information in the native structure
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
    ~MethodCapabilities();
    
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
     * @param  info  The information in the native structure
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

  
}


#endif

