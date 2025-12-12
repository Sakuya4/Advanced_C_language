#ifndef _METHOD_H_
#define _METHOD_H_

#include <stdio.h>

/* 裝置類型定義：配合 demo.txt 顯示的 0~4 類別 */
typedef enum {
    TEMP_SENSOR = 0,
    HUMID_SENSOR,
    BUTTON,
    MOTOR,
    WIRELESS_MODULE
} DeviceType;

#include "struct.h"   /* struct.h 裡的 tDeviceNode 會用到 DeviceType */

/* 連結串列 / 查詢相關函式 */
int init_device_list(tDeviceNode **head, tDeviceNode **tail);
int insert_device(tDeviceNode **head, tDeviceNode **tail, tDeviceNode *new_device);
int list_all_devices(tDeviceNode *head);
int find_device(tDeviceNode *head, const char *name, tDeviceNode **found_device);
int remove_device(tDeviceNode **head, tDeviceNode **tail, const char *name);

/* 讓 main 可以把 DeviceType 轉成字串印出 */
const char *device_type_to_string(DeviceType type);

#endif /* _METHOD_H_ */
