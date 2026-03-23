cat > ~/AUTOSAR_IN_ERIKA3/swc_landingswitch.c << 'EOF'

#include "swc_landingswitch.h"
#include "rte.h"
#include <stdio.h>
#include <time.h>

// 시뮬레이션 스텁
#ifdef SIMULATION_MODE

// 스텁 변수값

// HC-SR04 스텁
static float sim_distance_cm = 5.0f;

// INA219 스텁
static float sim_voltage      = 4.0f;         // 현재 전압 (V)
static float sim_current      = 500.0f;      // 전류 (mA)
static float sim_remaining    = 4000.0f;   // 남은 용량 (mAh)

// DS18B20 #2 스텁
static float sim_ambient_temp = -5.0f;   // 외부 기온 (°C)

// LED 스텁
static int sim_led_state = 0; 

// 시간 측정

static float get_elapsed_seconds(void)
{
    // OSTask 의해 1초 주기로 호출 -> 고정값 1.0f 반환
    return 1.0f;
}

// HC-SR04 스텁 함수

static float Stub_HCSR04_Measure(void)
{
    printf("[HC-SR04 STUB] 거리 측정: %.1fcm\n",
           sim_distance_cm);
    return sim_distance_cm;
}

// INA219 스텁 함수

static void Stub_INA219_Read(float *voltage,
                              float *current,
                              float *remaining,
                              unsigned char *percent)
{
    // 배터리 잔량 감소 시뮬레이션
    sim_remaining -= sim_current * (get_elapsed_seconds() / 3600.0f);
    if (sim_remaining < 0.0f) sim_remaining = 0.0f;

    // 전압 감소 시뮬레이션
    sim_voltage = BATTERY_MIN_VOLTAGE +
                  (sim_remaining / BATTERY_TOTAL_MAH) *
                  (BATTERY_MAX_VOLTAGE - BATTERY_MIN_VOLTAGE);

    *voltage   = sim_voltage;
    *current   = sim_current;
    *remaining = sim_remaining;
    *percent   = (unsigned char)
                 ((sim_remaining / BATTERY_TOTAL_MAH) * 100.0f);

    printf("[INA219 STUB] 전압: %.2fV | 전류: %.1fmA | "
           "잔량: %.1fmAh (%d%%)\n",
           *voltage, *current, *remaining, *percent);
}

// DS18B20 #2 스텁

static float Stub_DS18B20_Ambient(void)
{
    printf("[DS18B20#2 STUB] 외부 기온: %.1f°C\n",
           sim_ambient_temp);
    return sim_ambient_temp;
}

// LED 스텁

static void Stub_LED_Set(int state)
{
    if (sim_led_state != state) {
        sim_led_state = state;
        printf("[LED STUB] 드론 감지 LED: %s\n",
               state ? "ON  ← 드론 감지" : "OFF ← 드론 없음");
    }
}

#endif /* SIMULATION_MODE */


void SWC_LandingSwitch_Init(void)
{
#ifdef SIMULATION_MODE
    printf("[SWC_LandingSwitch] 초기화 완 "
           "(Simulation Mode)\n");
    printf("[SWC_LandingSwitch] HC-SR04 | INA219 | "
           "DS18B20#2 | LED 준비됨\n");
#else
    /* GPIO 초기화
     * HAL_GPIO_SetMode(HCSR04_TRIG_PIN, OUTPUT);
     * HAL_GPIO_SetMode(HCSR04_ECHO_PIN, INPUT);
     * HAL_GPIO_SetMode(LED_DETECT_PIN,  OUTPUT);
     * HAL_I2C_Init();       // INA219
     * HAL_OneWire_Init();   // DS18B20 #2           */
#endif
}

void RE_LandingSwitch(void)
{
    Rte_DataType_LandingStatus tx_data;
    float distance_cm;

    printf("\n[RE_LandingSwitch] ===== 1초 주기 실행 =====\n");

// HC-SR04 거리 측정

#ifdef SIMULATION_MODE
    distance_cm = Stub_HCSR04_Measure();
#else
    /* 실제 TC277:
     * HAL_GPIO_Write(HCSR04_TRIG_PIN, LOW);
     * HAL_DelayUs(2);
     * HAL_GPIO_Write(HCSR04_TRIG_PIN, HIGH);
     * HAL_DelayUs(10);
     * HAL_GPIO_Write(HCSR04_TRIG_PIN, LOW);
     * unsigned long duration = HAL_PulseIn(HCSR04_ECHO_PIN);
     * distance_cm = duration * 0.0343f / 2.0f;             */
#endif

    // 드론 감지
    if (distance_cm < (float)DRONE_DETECT_THRESHOLD_CM) {
        tx_data.drone_detected = 1U;
        printf("[RE_LandingSwitch] 드론 감지"
               "거리: %.1fcm < %ucm\n",
               distance_cm, DRONE_DETECT_THRESHOLD_CM);
    } else {
        tx_data.drone_detected = 0U;
        printf("[RE_LandingSwitch] 드론 없음."
               "거리: %.1fcm\n", distance_cm);
    }
    tx_data.distance_cm = (unsigned int)distance_cm;

// LED

#ifdef SIMULATION_MODE
    Stub_LED_Set(tx_data.drone_detected);
#else
    /* HAL_GPIO_Write(LED_DETECT_PIN,
     * tx_data.drone_detected ? HIGH : LOW); */
#endif

    // INA219 배터리 측정

#ifdef SIMULATION_MODE
    Stub_INA219_Read(&tx_data.battery_voltage,
                     &tx_data.battery_current,
                     &tx_data.battery_remaining,
                     &tx_data.battery_percent);
#else
    /* 실제 TC277:
     * HAL_INA219_Read(INA219_SDA_PIN,
     *                 &tx_data.battery_voltage,
     *                 &tx_data.battery_current);
     * tx_data.battery_remaining -= tx_data.battery_current
     *                              * (1.0f / 3600.0f);
     * tx_data.battery_percent =
     *   (unsigned char)((tx_data.battery_remaining
     *                    / BATTERY_TOTAL_MAH) * 100.0f);  */
#endif

    // DS18B20 #2 외부 기온 측정

#ifdef SIMULATION_MODE
    tx_data.ambient_temp = Stub_DS18B20_Ambient();
#else
    /* 실제 TC277:
     * tx_data.ambient_temp =
     *   HAL_DS18B20_Read(DS18B20_AMBIENT_PIN);            */
#endif

    // RTE Write

    tx_data.data_valid = 1U;
    Rte_Write_LandingStatus(&tx_data);

    printf("[RE_LandingSwitch] ===== 실행 완료 =====\n");
}
EOF
