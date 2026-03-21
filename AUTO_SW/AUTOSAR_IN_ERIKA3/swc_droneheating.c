cat > ~/AUTOSAR_IN_ERIKA3/swc_droneheating.c << 'EOF'

#include "swc_droneheating.h"
#include "rte.h"
#include <stdio.h>

#ifdef SIMULATION_MODE // 테스트용 스텁 정의

// DS18B20
static float sim_plate_temp = 15.0f;  // 초기 온도값 (예상)

// MOSFET
static int sim_mosfet_ch1 = 0;   // 0이 off
static int sim_mosfet_ch2 = 0;
static int sim_mosfet_ch3 = 0;

// DS18B20 시뮬용 스텁
static float Stub_DS18B20_Plate(void)
{
    // MOSFET ON
    if (sim_mosfet_ch1 && sim_mosfet_ch2) {
        sim_plate_temp += 1.5f;  // 1.5도씩 상승
    } else {
        if (sim_plate_temp > 10.0f) {
            sim_plate_temp -= 0.5f; // 0.5도씩 하강
        }
    }
    printf("[DS18B20#1 STUB] 내부 온도: %.1f°C\n",
           sim_plate_temp);
    return sim_plate_temp;
}

// MOSFET 시뮬용 스텁
static void Stub_MOSFET_Set(int ch1, int ch2)
{
    int changed = 0;
    if (sim_mosfet_ch1 != ch1) {
        sim_mosfet_ch1 = ch1;
        changed = 1;
    }
    if (sim_mosfet_ch2 != ch2) {
        sim_mosfet_ch2 = ch2;
        changed = 1;
    }
    if (changed) {
        printf("[MOSFET STUB] CH1(발열#1): %s | "
               "CH2(발열#2): %s\n",
               ch1 ? "ON" : "OFF",
               ch2 ? "ON" : "OFF");
    }
}

static void Stub_MOSFET_CH3_Set(int state)
{
    if (sim_mosfet_ch3 != state) {
        sim_mosfet_ch3 = state;
        printf("[MOSFET STUB] CH3(무선충전 패드): %s\n",
               state ? "ON  = 충전 시작" : "OFF = 충전 중단");
    }
}

#endif // 시뮬레이션 모드

// 현재 상태 기억
static unsigned char heater_state  = 0U; 
static unsigned char charger_state = 0U;

void SWC_DroneHeating_Init(void)
{
#ifdef SIMULATION_MODE
    printf("[SWC_DroneHeating] 초기화 완료 "
           "(Simulation Mode)\n");
    printf("[SWC_DroneHeating] MOSFET CH1~CH3 | "
           "DS18B20#1 준비됨\n");
#else	// TC277 HAL 초기화
    /* GPIO 현황
     * HAL_GPIO_SetMode(HCSR04_TRIG_PIN, OUTPUT);
     * HAL_GPIO_SetMode(HCSR04_ECHO_PIN, INPUT);
     * HAL_GPIO_SetMode(LED_DETECT_PIN,  OUTPUT);
     * HAL_I2C_Init();       (INA219)
     * HAL_OneWire_Init();    (DS18B20 #2)*/

#endif
}

// RE_DroneHeating  (Runnable)

void RE_DroneHeating(unsigned char drone_detected)
{
    float plate_temp;

    printf("\n[RE_DroneHeating] 실행됨. "
           "drone_detected = %d\n", drone_detected);

// 드론 감지 X
    if (!drone_detected) {
        if (heater_state == 1U) {
#ifdef SIMULATION_MODE
            Stub_MOSFET_Set(0, 0);
#else
            /* HAL_GPIO_Write(MOSFET_CH1_PIN, LOW);
             * HAL_GPIO_Write(MOSFET_CH2_PIN, LOW); */
#endif
            heater_state = 0U;
            printf("[RE_DroneHeating] 드론 없음 → "
                   "MOSFET CH1, CH2 OFF\n");
        }
        return;
    }

// 금속판 온도 읽기
#ifdef SIMULATION_MODE
    plate_temp = Stub_DS18B20_Plate();
#else
    /* plate_temp = HAL_DS18B20_Read(DS18B20_PLATE_PIN); */
#endif

    if (plate_temp < (float)TEMP_MIN_CELSIUS) {
        /* 온도 낮음 → 가열 시작 */
        if (heater_state == 0U) {
#ifdef SIMULATION_MODE
            Stub_MOSFET_Set(1, 1);
#else
            /* HAL_GPIO_Write(MOSFET_CH1_PIN, HIGH);
             * HAL_GPIO_Write(MOSFET_CH2_PIN, HIGH); */
#endif
            heater_state = 1U;
            printf("[RE_DroneHeating] %.1f°C < %d°C → "
                   "MOSFET CH1, CH2 ON (가열 시작)\n",
                   plate_temp, TEMP_MIN_CELSIUS);
        }
    } else if (plate_temp > (float)TEMP_MAX_CELSIUS) {
        /* 온도 높음 → 가열 중단 */
        if (heater_state == 1U) {
#ifdef SIMULATION_MODE
            Stub_MOSFET_Set(0, 0);
#else
            /* HAL_GPIO_Write(MOSFET_CH1_PIN, LOW);
             * HAL_GPIO_Write(MOSFET_CH2_PIN, LOW); */
#endif
            heater_state = 0U;
            printf("[RE_DroneHeating] %.1f°C > %d°C → "
                   "MOSFET CH1, CH2 OFF (가열 중단)\n",
                   plate_temp, TEMP_MAX_CELSIUS);
        }
    } else {
        /* 18~22°C → 현재 상태 유지 */
        printf("[RE_DroneHeating] %.1f°C → "
               "18~22°C 범위 유지 중 (상태 유지)\n",
               plate_temp);
    }
}

// RE_DroneCharging  (Runnable)

void RE_DroneCharging(unsigned char drone_detected)
{
    printf("[RE_DroneCharging] 실행됨. "
           "drone_detected = %d\n", drone_detected);

    if (drone_detected) {
        if (charger_state == 0U) {
#ifdef SIMULATION_MODE
            Stub_MOSFET_CH3_Set(1);
#else
            /* HAL_GPIO_Write(MOSFET_CH3_PIN, HIGH); */
#endif
            charger_state = 1U;
            printf("[RE_DroneCharging] MOSFET CH3 ON → "
                   "무선충전 패드 전원 공급 시작\n");
        } else {
            printf("[RE_DroneCharging] 무선충전 패드 "
                   "이미 ON 상태 유지\n");
        }
    } else {
        if (charger_state == 1U) {
#ifdef SIMULATION_MODE
            Stub_MOSFET_CH3_Set(0);
#else
            /* HAL_GPIO_Write(MOSFET_CH3_PIN, LOW); */
#endif
            charger_state = 0U;
            printf("[RE_DroneCharging] MOSFET CH3 OFF → "
                   "무선충전 패드 전원 차단\n");
        }
    }
}
EOF
