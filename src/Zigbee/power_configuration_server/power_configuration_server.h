/***************************************************************************//**
 * @file
 * @brief Power Configuration Server Cluster
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Alexei Chetroi</b>
 *******************************************************************************
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#ifndef ZIGBEE_POWER_CONFIGURATION_SERVER_H
#define ZIGBEE_POWER_CONFIGURATION_SERVER_H

/**
 * @defgroup Power Configuration Server
 * @ingroup component cluster
 * @brief API and Callbacks Power Configuration Cluster implementation
 *
 */

/**
 * @addtogroup power-configuration-server
 * @{
 */
/**
 * @name Callbacks
 * @{
 */

/**
 * @defgroup power_configuration_server_cb Power Configuration
 * @ingroup af_callback
 * @brief Callbacks for Power Configuration Server cluster
 *
 */

/**
 * @addtogroup power_configuration_server_cb
 * @{
 */

/** @brief Power Configuration cluster server post init.
 *
 * Following the resolution of the current level at startup for this endpoint,
 * perform any additional initialization needed, e.g., synchronize hardware
 * state.
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 */
void emberAfPowerConfigurationClusterServerInitCallback(uint8_t endpoint);


/** @brief Power Configuration cluster measurement ready.
 *
 * after battery voltage is received and converted into battery % remaining
 * execute this callback.
 *
 * @param endpoint Endpoint that is being initialized  Ver.: always
 * @param battery_double_percent Battery Percent Remaining times 2
 * @param battery_milliV Battery voltage in milli Volts
 */
void emberAfPowerConfigurationClusterBatteryUpdated(uint8_t endpoint,
                                                    uint8_t battery_double_percent,
                                                    uint16_t battery_milliV);

/** @} */ // end of power_configuration_server_cb
/** @} */ // end of name Callbacks
/** @} */ // end of power-configuration-server

/**
 * @brief Called after the Power Configuration cluster is initialized.
 */
void emberAfPowerConfigurationClusterServerInitCallback(uint8_t endpoint);

#endif // ZIGBEE_POWER_CONFIGURATION_SERVER_H
