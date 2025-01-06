/*******************************************************************************
 * @file
 * @brief Power Configuration Server Cluster
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ******************************************************************************/

#include "app/framework/include/af.h"
#include "power_configuration_server_config.h"

#if SL_POWER_CONFIGURATION_BATTERY_TYPE == SL_POWER_CONFIGURATION_BATTERY_TYPE_CR2032
#define SL_POWER_CONFIGURATION_BATTERY_VOLTAGE_CAPACITY \
   { { 3.0, 100 }, { 2.9, 80 }, { 2.8, 60 }, { 2.7, 40 }, { 2.6, 30 }, \
     { 2.5, 20 }, { 2.4, 10 }, { 2.0, 0 } };
#elif SL_POWER_CONFIGURATION_BATTERY_TYPE == SL_POWER_CONFIGURATION_BATTERY_TYPE_18650
#define SL_POWER_CONFIGURATION_BATTERY_VOLTAGE_CAPACITY \
   { { 4.2, 100 }, { 4.06, 90 }, { 3.98, 80 }, { 3.92, 70 }, { 3.87, 60 }, \
     { 3.82, 50 }, { 3.79, 40 }, { 3.77, 30 }, { 3.74, 20 }, { 3.68, 10 }, \
     { 3.60, 5 }, { 3.20, 0 } }
#endif


// -----------------------------------------------------------------------------
// Private type definitions

typedef struct {
  float volts;
  uint8_t capacity;
} batt_cap_entry_t;

typedef struct {
  uint16_t milliV;
} battery_update_t;

static volatile battery_update_t _lastUpdateValues;
static sl_zigbee_event_t batteryUpdatedEvent;

// -----------------------------------------------------------------------------
// Private variables
static batt_cap_entry_t batt_volt_to_cap[] = SL_POWER_CONFIGURATION_BATTERY_VOLTAGE_CAPACITY;

// -----------------------------------------------------------------------------
// Forward declarations
static uint8_t convert_voltage_to_capacity(uint16_t milliV);
static void battery_update_handler(sl_zigbee_event_t *event);

// ------------------------------------------------------------------------------
// Component call backs
void emberAfPowerConfigurationClusterServerInitCallback(uint8_t endpoint)
{
  sl_zigbee_af_isr_event_init(&batteryUpdatedEvent, battery_update_handler);
  emberAfPowerConfigClusterPrintln("Power Configuration Cluster: initialized");
}

SL_WEAK void emberAfPowerConfigurationClusterServerPostInitCallback(uint8_t endpoint)
{
}

SL_WEAK void emberAfPowerConfigurationClusterBatteryUpdated(uint8_t endpoint,
                                                         uint8_t battery_double_percent,
                                                         uint16_t battery_milliV)
{
}

// ------------------------------------------------------------------------------
// callbacks implementations
void sl_battery_monitor_measurement_ready_cb(uint16_t milliV)
{
  _lastUpdateValues.milliV = milliV;
  sl_zigbee_event_set_active(&batteryUpdatedEvent);
}

void battery_update_handler(sl_zigbee_event_t *event)
{
  EmberAfStatus afStatus;
  uint8_t deciV = _lastUpdateValues.milliV / 100;
  uint8_t capacity = convert_voltage_to_capacity(_lastUpdateValues.milliV);

  sl_zigbee_app_debug_print("Power configuration cluster: reported voltage: %d dV", deciV);
  sl_zigbee_app_debug_println(", reported double battery %% remaining: %d%%", capacity);

  uint8_t endpoint;
  for (uint8_t i = 0; i < emberAfEndpointCount(); i++) {
    endpoint = emberAfEndpointFromIndex(i);
    // Update battery voltage
    if (emberAfContainsServer(endpoint, ZCL_POWER_CONFIG_CLUSTER_ID)) {
      afStatus = emberAfWriteServerAttribute(endpoint,
                                             ZCL_POWER_CONFIG_CLUSTER_ID,
                                             ZCL_BATTERY_VOLTAGE_ATTRIBUTE_ID,
                                             &deciV,
                                             ZCL_INT8U_ATTRIBUTE_TYPE);

      if (EMBER_ZCL_STATUS_SUCCESS != afStatus) {
        emberAfAppPrintln("Power Configuration Server: failed to write value "
                          "0x%x to cluster 0x%x attribute ID 0x%x: error 0x%x",
                          deciV,
                          ZCL_POWER_CONFIG_CLUSTER_ID,
                          ZCL_BATTERY_VOLTAGE_ATTRIBUTE_ID,
                          afStatus);
      }
    }
    // update battery capacity
    if (emberAfContainsServer(endpoint, ZCL_POWER_CONFIG_CLUSTER_ID)) {
      afStatus = emberAfWriteServerAttribute(endpoint,
                                             ZCL_POWER_CONFIG_CLUSTER_ID,
                                             ZCL_BATTERY_PERCENTAGE_REMAINING_ATTRIBUTE_ID,
                                             &capacity,
                                             ZCL_INT8U_ATTRIBUTE_TYPE);

      if (EMBER_ZCL_STATUS_SUCCESS != afStatus) {
        emberAfAppPrintln("Power Configuration Server: failed to write value "
                          "0x%x to cluster 0x%x attribute ID 0x%x: error 0x%x",
                          capacity,
                          ZCL_POWER_CONFIG_CLUSTER_ID,
                          ZCL_BATTERY_PERCENTAGE_REMAINING_ATTRIBUTE_ID,
                          afStatus);
      }
    }
    emberAfPowerConfigurationClusterBatteryUpdated(endpoint, capacity, _lastUpdateValues.milliV);
  }
}


// ------------------------------------------------------------------------------
// private functions

/*
 * Calculate battery capacity
 */
static uint8_t convert_voltage_to_capacity(uint16_t milliV)
{
  float volts = milliV / 1000.0F;
  uint8_t res = 0;
  uint8_t count = sizeof(batt_volt_to_cap) / sizeof(batt_cap_entry_t);

  if (volts >= batt_volt_to_cap[0].volts) {
    // Return with max capacity if voltage is greater than the max voltage in the model.
    res = batt_volt_to_cap[0].capacity;
  } else if (volts <= batt_volt_to_cap[count - 1].volts) {
    // Return with min capacity if voltage is smaller than the min voltage in the model.
    res = batt_volt_to_cap[count - 1].capacity;
  } else {
    uint8_t i;
    // Otherwise find the 2 points in the model where the voltage level fits in between,
    // and do linear interpolation to get the estimated capacity value.
    for (i = 0; i < (count - 1); i++) {
      if ((volts < batt_volt_to_cap[i].volts) && (volts >= batt_volt_to_cap[i + 1].volts)) {
        res = (uint8_t)((volts - batt_volt_to_cap[i + 1].volts)
                        * (batt_volt_to_cap[i].capacity - batt_volt_to_cap[i + 1].capacity)
                        / (batt_volt_to_cap[i].volts - batt_volt_to_cap[i + 1].volts));
        res += batt_volt_to_cap[i + 1].capacity;
        break;
      }
    }
  }

  return res << 1;
}
