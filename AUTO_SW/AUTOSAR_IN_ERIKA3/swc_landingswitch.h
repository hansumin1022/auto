cat > ~/AUTOSAR_IN_ERIKA3/swc_landingswitch.h << 'EOF'

#ifndef SWC_LANDINGSWITCH_H
#define SWC_LANDINGSWITCH_H

// 핀 정의

// HC-SR04
#define HCSR04_TRIG_PIN        // P02.3 - GPIO OUT - 초음파 발사\
#define HCSR04_ECHO_PIN        // P02.4 - GPIO IN  - 초음파 수신\

// DS18B20
#define DS18B20_AMBIENT_PIN    // P00.2 - OneWire

// INA219 배터리 잔량감지
#define INA219_SDA_PIN         // I2C SDA - 전압+전류 측정
#define INA219_SCL_PIN         // I2C SCL

// LED
#define LED_DETECT_PIN         // P10.4 - GPIO OUT

// 관련 상수 정의

// 드론 감지 거리 기준
#define DRONE_DETECT_THRESHOLD_CM   7U

// INA219 배터리 전체 용량
#define BATTERY_TOTAL_MAH           5000.0f

// 배터리 최대/최소 전압 (잔량 % 계산용)
#define BATTERY_MAX_VOLTAGE         4.2f    // 만충 전압 (V) 
#define BATTERY_MIN_VOLTAGE         3.0f    // 방전 전압 (V) 

// 함수 선언

// 초기화
void SWC_LandingSwitch_Init(void);

// RE_LandingSwitch Runnable

void RE_LandingSwitch(void);

#endif
EOF
