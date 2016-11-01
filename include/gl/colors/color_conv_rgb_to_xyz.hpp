/*

PICCANTE
The hottest HDR imaging library!
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/

#ifndef PIC_GL_COLORS_COLOR_CONV_RGB_TO_XYZ_HPP
#define PIC_GL_COLORS_COLOR_CONV_RGB_TO_XYZ_HPP

#include "colors/color_conv_rgb_to_xyz.hpp"

#include "gl/colors/color_conv.hpp"

namespace pic {

/**
 * @brief The ColorConvGLRGBtoXYZ class
 */
class ColorConvGLRGBtoXYZ: public ColorConvGL
{
public:

    /**
     * @brief ColorConvGLRGBtoXYZ
     */
    ColorConvGLRGBtoXYZ(bool direct = true) : ColorConvGL(direct)
    {
    }

    /**
     * @brief getDirectFunction
     * @return
     */
    std::string getDirectFunction()
    {
        std::string fragment_source = MAKE_STRING
                          (
        uniform sampler2D u_tex; \n
        uniform mat3 mtx; \n
        out     vec4 f_color; \n
        \n
        void main(void) {
            \n
            ivec2 coords = ivec2(gl_FragCoord.xy); \n
            vec3 color = texelFetch(u_tex, coords, 0).xyz; \n
            f_color = vec4(mtx * color, 1.0); \n
            \n
        }
                          );
        return fragment_source;
    }

    /**
     * @brief getInverseFunction
     * @return
     */
    std::string getInverseFunction()
    {
        return getDirectFunction();
    }

    /**
     * @brief setUniforms
     */
    void setUniforms()
    {
        if(direct) {
            glw::bind_program(programs[0]);
            programs[0].uniform3x3("mtx", mtxRGBtoXYZ, true);
        } else {
            glw::bind_program(programs[1]);
            programs[1].uniform3x3("mtx", mtxXYZtoRGB, true);
        }

        glw::bind_program(0);
    }

};

} // end namespace pic

#endif /* PIC_GL_COLORS_COLOR_CONV_RGB_TO_XYZ_HPP */

