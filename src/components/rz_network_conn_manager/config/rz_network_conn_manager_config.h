/***************************************************************************//**
 * @file
 * @brief rz_network_connection_manager_config Config
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Alexei Chetroi</b>
 *******************************************************************************
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 ******************************************************************************/

#ifndef RZ_NETWORK_CONN_MANAGER_CONFIG_H
#define RZ_NETWORK_CONN_MANAGER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu

// <h> Network connection manager LED configuration

// <o RZ_NETWORK_CONN_MANAGER_COMMISSIONING_LED> Commissioning LED index
// <0..5:1>
// <i> Default: 0
// <i> Identifying LED number
#define RZ_NETWORK_CONN_MANAGER_COMMISSIONING_LED 0

// <o RZ_NETWORK_CONN_MANAGER_LED_BLINK_SHORT_MS> Duration of a short led blink in MS
// <50..2000:25>
// <i> Default: 100
// <i> Led short blink duration
#define RZ_NETWORK_CONN_MANAGER_LED_BLINK_SHORT_MS 200

// <o RZ_NETWORK_CONN_MANAGER_LED_BLINK_LONG_MS> Duration of a long led blink in MS
// <500..3000:100>
// <i> Default: 750
// <i> Led long blink duration
#define RZ_NETWORK_CONN_MANAGER_LED_BLINK_LONG_MS 750

// <o RZ_NETWORK_CONN_MANAGER_LED_BLINK_IDENTIFY_MS> Duration of a long led blink in MS
// <200..1000:100>
// <i> Default: 500
// <i> Identifying led blink duration
#define RZ_NETWORK_CONN_MANAGER_LED_BLINK_IDENTIFY_MS 500

// <o RZ_NETWORK_CONN_MANAGER_NETWORK_UP_BLINK_COUNT> number of blinks when network is up
// <1..20:1>
// <i> Default: 3
// <i> Network up count of led blinks
#define RZ_NETWORK_CONN_MANAGER_NETWORK_UP_BLINK_COUNT 3

// </h> end Network connection manager config

// <h> Network Joining configuration
// <o RZ_NETWORK_CONN_MANAGER_MAX_REJOIN_ATTEMPTS> Max number of join attempts
// <1..100:1>
// <i> Default: 15
// <i> MAX rejoin attempts
#define RZ_NETWORK_CONN_MANAGER_MAX_REJOIN_ATTEMPTS 1

// <o RZ_NETWORK_CONN_MANAGER_REJOIN_BACKOFF_S> number of seconds to back off after unsuccessful rejoin
// <1..20:1>
// <i> Default: 5
// <i> number of seconds to back off after unsuccessful rejoin
#define RZ_NETWORK_CONN_MANAGER_REJOIN_BACKOFF_S 5

// <o RZ_NETWORK_CONN_MANAGER_MAX_REJOIN_BACKOFF_S> number of seconds to back off after unsuccessful rejoin
// <100..3600:120>
// <i> Default: 1800
// <i> maximum number of seconds to back off after unsuccessful rejoin
#define RZ_NETWORK_CONN_MANAGER_MAX_REJOIN_BACKOFF_S 1800

// </h> Network Joining configuration
// <<< end of configuration section >>>

#endif // RZ_NETWORK_CONN_MANAGER_CONFIG_H