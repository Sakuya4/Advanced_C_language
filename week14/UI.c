#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "method.h"
#include "UI.h"

void run_device_manager(void)
{
    tDeviceNode *device_list_head = NULL;
    tDeviceNode *device_list_tail = NULL;
    int user_choice = 0;

    init_device_list(&device_list_head, &device_list_tail);

    while (1) {
        printf("===== Device Manager =====\n");
        printf("1) Add device\n");
        printf("2) List all devices\n");
        printf("3) Find device\n");
        printf("4) Remove device\n");
        printf("0) Quit\n");
        printf("Select: ");

        if (scanf("%d", &user_choice) != 1) {
            break;  /* 異常輸入就退出 */
        }

        if (user_choice == 0) {
            break;  /* Quit */
        }

        if (user_choice == 1) {
            /* Add device */
            tDeviceNode *new_device = (tDeviceNode *)malloc(sizeof(tDeviceNode));
            if (!new_device) {
                fprintf(stderr, "Memory allocation failed\n");
                return;  /* 直接離開 run_device_manager */
            }
            memset(new_device, 0, sizeof(tDeviceNode));

            printf("\nEnter device name: ");
            scanf("%15s", new_device->name);

            printf("Select device type:\n");
            printf("  0) TEMP_SENSOR\n");
            printf("  1) HUMID_SENSOR\n");
            printf("  2) BUTTON\n");
            printf("  3) MOTOR\n");
            printf("  4) WIRELESS_MODULE\n");
            printf("Type: ");
            int type_input = 0;
            scanf("%d", &type_input);
            if (type_input < 0) type_input = 0;
            if (type_input > 4) type_input = 4;
            new_device->type = (DeviceType)type_input;

            if (new_device->type == TEMP_SENSOR || new_device->type == HUMID_SENSOR) {
                /* Analog sensor settings */
                printf("\n[Analog sensor settings]\n");
                printf("ADC channel: ");
                scanf("%d", &new_device->conn.analog.adc_channel);
                printf("Scale (°C per unit): ");
                scanf("%f", &new_device->conn.analog.scale);
            } else if (new_device->type == BUTTON || new_device->type == MOTOR) {
                /* Digital I/O settings */
                unsigned int port = 0, pin = 0;
                printf("\n[Digital I/O settings]\n");
                printf("GPIO port (0~255): ");
                scanf("%u", &port);
                printf("GPIO pin (0~255): ");
                scanf("%u", &pin);
                new_device->conn.digital.port = (unsigned char)port;
                new_device->conn.digital.pin  = (unsigned char)pin;
            } else if (new_device->type == WIRELESS_MODULE) {
                /* Wireless module settings */
                int wt = 0;
                unsigned int id = 0;
                printf("\n[Wireless module settings]\n");
                printf("Wireless type:\n");
                printf("  0) BLE\n");
                printf("  1) WiFi\n");
                printf("  2) LTE\n");
                printf("Type: ");
                scanf("%d", &wt);
                if (wt < 0) wt = 0;
                if (wt > 2) wt = 2;
                new_device->conn.wireless.type = (WirelessType)wt;
                printf("Module ID (hex allowed): ");
                scanf("%x", &id);           /* 0x1234 這種輸入 OK */
                new_device->conn.wireless.id = id;
            }

            new_device->next = NULL;
            insert_device(&device_list_head, &device_list_tail, new_device);
            printf("\nDevice \"%s\" added.\n\n", new_device->name);

        } else if (user_choice == 2) {
            /* List all devices */
            printf("\n");
            list_all_devices(device_list_head);
            printf("\n");

        } else if (user_choice == 3) {
            /* Find device */
            char search_name[16];
            printf("\nEnter device name to find: ");
            scanf("%15s", search_name);
            tDeviceNode *found = NULL;
            if (find_device(device_list_head, search_name, &found)) {
                printf("\n[Device Found]\n");
                printf("Name: %s\n", found->name);
                printf("Type: %s\n", device_type_to_string(found->type));

                if (found->type == TEMP_SENSOR || found->type == HUMID_SENSOR) {
                    printf("[Analog] ADC channel = %d, scale = %.2f\n",
                           found->conn.analog.adc_channel,
                           found->conn.analog.scale);
                } else if (found->type == BUTTON || found->type == MOTOR) {
                    printf("[Digital] GPIO port = %u, pin = %u\n",
                           found->conn.digital.port,
                           found->conn.digital.pin);
                } else if (found->type == WIRELESS_MODULE) {
                    const char *wtype =
                        (found->conn.wireless.type == BLE) ? "BLE" :
                        (found->conn.wireless.type == WIFI) ? "WiFi" :
                        (found->conn.wireless.type == LTE) ? "LTE" : "Unknown";
                    printf("[Wireless] type = %s, id = 0x%X\n",
                           wtype, found->conn.wireless.id);
                }
                printf("\n");
            } else {
                printf("\nDevice \"%s\" not found.\n\n", search_name);
            }

        } else if (user_choice == 4) {
            /* Remove device */
            char remove_name[16];
            printf("\nEnter device name to remove: ");
            scanf("%15s", remove_name);
            if (remove_device(&device_list_head, &device_list_tail, remove_name)) {
                printf("\nDevice \"%s\" removed.\n\n", remove_name);
            } else {
                printf("\nDevice \"%s\" not found.\n\n", remove_name);
            }
        }
    }

    /* 離開前把 list 清掉，避免 memory leak */
    tDeviceNode *cur = device_list_head;
    while (cur) {
        tDeviceNode *next = cur->next;
        free(cur);
        cur = next;
    }
}
