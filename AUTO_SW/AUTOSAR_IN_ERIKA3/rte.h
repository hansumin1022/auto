/* rte.h
 * Runtime Environment (RTE) - Sender/Receiver 인터페이스 */

#ifndef RTE_H
#define RTE_H

/* --------------------------------------------------------
 * RTE 데이터 구조체 (센서 데이터 모음)
 * -------------------------------------------------------- */
typedef struct {

    // [HC-SR04 초음파 센서]
    unsigned char drone_detected;    // 드론 감지 여부 (1 또는 0)
    unsigned int  distance_cm;       // 측정 거리 (cm)

    // [INA219 배터리 센서 - I2C]
    float         battery_voltage;   // 현재 배터리 전압 (V)
    float         battery_current;   // 현재 소비 전류 (mA)
    float         battery_remaining; // 남은 용량 (mAh) (전체용량 - 소비된용량)
    unsigned char battery_percent;   // 잔량 % (남은용량/전체용량 × 100)

    // [DS18B20 #2 - 외부 기온 전용]
    float         ambient_temp;      // 외부 온도 (°C)

    // 데이터 유효 여부 (Rte_Write() 호출 시 1로 설정, Rte_Read() 호출 후 0으로 초기화.)
    unsigned char data_valid;        // 1: 갱신 ㅇㅇ, 0: 갱신 ㄴㄴ

} } Rte_DataType_LandingStatus;


void Rte_Init(void); // 버퍼 초기화.

void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus *data);
// Sender가 호출, 데이터를 버퍼에 저장, SetEvent()로 OsTask 활성화

void Rte_Read_LandingStatus(Rte_DataType_LandingStatus *data);
// Receiver가 호출, 버퍼에서 데이터 꺼내 사용.

#endif
EOF