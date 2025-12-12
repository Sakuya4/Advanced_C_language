#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <stdio.h>

typedef struct {int adc_channel; float scale; } AnalogInfo;
typedef struct {unsigned char port, pin;} DigitalInfo;

typedef enum {BLE, WIFI, LTE} WirelessType;
typedef struct {WirelessType type; unsigned int id;} WirelessInfo;

typedef union {
    AnalogInfo   analog;   // 類比感測器
    DigitalInfo  digital;  // 按鍵 
    WirelessInfo wireless; // 無線模組
} DeviceConnInfo;

typedef struct device_node {
    char          name[16];     // 裝置名稱，例如 "TEMP1"
    DeviceType    type;         // 裝置類型 (自己定)
    DeviceConnInfo conn;        // 連接資訊
    struct device_node *next;    // 指向下一個節點
} tDeviceNode;

#endif //_STRUCT_H_