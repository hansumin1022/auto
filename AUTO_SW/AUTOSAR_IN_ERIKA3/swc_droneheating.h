cat > ~/AUTOSAR_IN_ERIKA3/swc_droneheating.h << 'EOF'

#ifndef SWC_DRONEHEATING_H
#define SWC_DRONEHEATING_H

// 핀 정의
// MOSFET 
#define MOSFET_CH1_PIN    // P10.0 - GPIO OUT - 금속판 발열 #1
#define MOSFET_CH2_PIN    // P10.1 - GPIO OUT - 금속판 발열 #2
#define MOSFET_CH3_PIN    // P10.2 - GPIO OUT - 무선충전 패드
#define MOSFET_CH4_PIN    // P10.3 - GPIO OUT - 여분

// DS18B20
#define DS18B20_PLATE_PIN  // P00.1 - OneWire  - 금속판 온도

/* 온도 상수
#define TEMP_MIN_CELSIUS    18U   // 이하면 MOSFET ON
#define TEMP_MAX_CELSIUS    22U   // 이상이면 MOSFET OFF

// SWC 초기화
void SWC_DroneHeating_Init(void);

// RE_DroneHeating (Runnable) : 금속판 온도 읽고, MOSFET 제어.
// drone_detected = 0이면 즉시 OFF
void RE_DroneHeating(unsigned char drone_detected);

// RE_DroneCharging Runnable : 무선충전 패드 전원 제어
void RE_DroneCharging(unsigned char drone_detected);

#endif
EOF
