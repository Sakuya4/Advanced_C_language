#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "method.h"

int init_device_list(tDeviceNode **head, tDeviceNode **tail)
{
    *head = NULL;
    *tail = NULL;
    return 0;
}

int insert_device(tDeviceNode **head, tDeviceNode **tail, tDeviceNode *new_device)
{
    if (*head == NULL) {
        *head = new_device;
        *tail = new_device;
    } else {
        (*tail)->next = new_device;
        *tail = new_device;
    }
    return 0;
}

const char *device_type_to_string(DeviceType type)
{
    switch (type) {
    case TEMP_SENSOR:      return "TEMP_SENSOR";
    case HUMID_SENSOR:     return "HUMID_SENSOR";
    case BUTTON:           return "BUTTON";
    case MOTOR:            return "MOTOR";
    case WIRELESS_MODULE:  return "WIRELESS_MODULE";
    default:               return "UNKNOWN";
    }
}

/* 列出所有裝置 */
int list_all_devices(tDeviceNode *head)
{
    tDeviceNode *current = head;
    int count = 0;

    printf("--- Device List ---\n");
    while (current != NULL) {
        printf("Name: %s\n", current->name);
        printf("  Type: %s\n", device_type_to_string(current->type));

        if (current->type == TEMP_SENSOR || current->type == HUMID_SENSOR) {
            printf("  [Analog] ADC channel = %d, scale = %.2f\n",
                   current->conn.analog.adc_channel,
                   current->conn.analog.scale);
        } else if (current->type == BUTTON || current->type == MOTOR) {
            printf("  [Digital] GPIO port = %u, pin = %u\n",
                   current->conn.digital.port,
                   current->conn.digital.pin);
        } else if (current->type == WIRELESS_MODULE) {
            const char *wtype =
                (current->conn.wireless.type == BLE) ? "BLE" :
                (current->conn.wireless.type == WIFI) ? "WiFi" :
                (current->conn.wireless.type == LTE) ? "LTE" : "Unknown";
            printf("  [Wireless] type = %s, id = 0x%X\n",
                   wtype, current->conn.wireless.id);
        }

        printf("\n");
        count++;
        current = current->next;
    }
    printf("-------------------\n");
    printf("Total %d device(s).\n", count);

    return 0;
}


int find_device(tDeviceNode *head, const char *name, tDeviceNode **found_device)
{
    tDeviceNode *current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (found_device) {
                *found_device = current;
            }
            return 1;
        }
        current = current->next;
    }

    if (found_device) {
        *found_device = NULL;
    }
    return 0;
}


int remove_device(tDeviceNode **head, tDeviceNode **tail, const char *name)
{
    tDeviceNode *current = *head;
    tDeviceNode *prev = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }

            if (current->next == NULL) {
                *tail = prev;
            }

            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}
