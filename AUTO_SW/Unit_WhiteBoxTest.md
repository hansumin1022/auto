# SW 테스팅
- 실제 구동을 위한 HW의 부재로 인한 이하 SW의 로직을 검증용 시뮬레이션의 테스트 기법은 아래와 같음.

* 테스트 레벨 관점: 단위 테스트 (Unit Test)
* 테스트 기법 관점: 화이트 박스 테스트


### SW 로직 검증 시뮬레이션 동작 결과
- SW 로직의 정상 작동을 검증하기 위해 실제 ERIKA3 환경임을 가정하고 각 함수로 역할을 모방해 테스트하였음.
```
suminhan@ubuntu:~/AUTOSAR_IN_ERIKA3$ make sim
gcc -Wall -Wextra -g -DSIMULATION_MODE main.c rte.c swc_landingswitch.c swc_droneheating.c -o drone_system_sim -lrt
./drone_system_sim

========================================
 CSWC_DroneSystem 시뮬레이션 시작
 AUTOSAR 구조 기반 ERIKA3 구현 By Sumin Han 
========================================

[RTE] 초기화 완
[SWC_LandingSwitch] 초기화 완 (Simulation Mode)
[SWC_LandingSwitch] HC-SR04 | INA219 | DS18B20#2 | LED 준비됨
[SWC_DroneHeating] 초기화 완료 (Simulation Mode)
[SWC_DroneHeating] MOSFET CH1~CH3 | DS18B20#1 준비됨

[StartOS] OS 시작. OsTask_DroneHeating 대기 상태 진입.
[OsTask_DroneHeating] WaitEvent() 대기 중...

[ 사이클 1 / 10 ]

========================================
 OsTask_LandingSwitch 실행 (1초 주기)
========================================

[RE_LandingSwitch] ===== 1초 주기 실행 =====
[HC-SR04 STUB] 거리 측정: 5.0cm
[RE_LandingSwitch] 드론 감지거리: 5.0cm < 7cm
[LED STUB] 드론 감지 LED: ON  ← 드론 감지
[INA219 STUB] 전압: 3.96V | 전류: 500.0mA | 잔량: 3999.9mAh (79%)
[DS18B20#2 STUB] 외부 기온: -5.0°C
[RTE] Rte_Write() 호출
[RTE] 거리: 5cm | 감지: 드론 감지 | 전압: 3.96V | 잔량: 79% | 외부기온: -5.0°C
[RTE] SetEvent(OsTask_DroneHeating, Ev_DataReceive) 호출
[RTE] → OsTask_DroneHeating 활성화 완
[RE_LandingSwitch] ===== 실행 완료 =====
[OsTask_LandingSwitch] TerminateTask()

========================================
 OsTask_DroneHeating 실행 (이벤트 수신)
========================================
[OsTask_DroneHeating] ClearEvent()
[RTE] Rte_Read() 호출 data_valid 초기화.

[RE_DroneHeating] 실행됨. drone_detected = 1
[DS18B20#1 STUB] 내부 온도: 14.5°C
[MOSFET STUB] CH1(발열#1): ON | CH2(발열#2): ON
[RE_DroneHeating] 14.5°C < 18°C → MOSFET CH1, CH2 ON (가열 시작)
[RE_DroneCharging] 실행됨. drone_detected = 1
[MOSFET STUB] CH3(무선충전 패드): ON  = 충전 시작
[RE_DroneCharging] MOSFET CH3 ON → 무선충전 패드 전원 공급 시작
[OsTask_DroneHeating] 처리 완료 → WaitEvent()로 복귀
[OsTask_DroneHeating] WaitEvent() 대기 중...

[ 사이클 2 / 10 ]

========================================
 OsTask_LandingSwitch 실행 (1초 주기)
========================================

[RE_LandingSwitch] ===== 1초 주기 실행 =====
[HC-SR04 STUB] 거리 측정: 5.0cm
[RE_LandingSwitch] 드론 감지거리: 5.0cm < 7cm
[INA219 STUB] 전압: 3.96V | 전류: 500.0mA | 잔량: 3999.7mAh (79%)
[DS18B20#2 STUB] 외부 기온: -5.0°C
[RTE] Rte_Write() 호출
[RTE] 거리: 5cm | 감지: 드론 감지 | 전압: 3.96V | 잔량: 79% | 외부기온: -5.0°C
[RTE] SetEvent(OsTask_DroneHeating, Ev_DataReceive) 호출
[RTE] → OsTask_DroneHeating 활성화 완
[RE_LandingSwitch] ===== 실행 완료 =====
[OsTask_LandingSwitch] TerminateTask()

========================================
 OsTask_DroneHeating 실행 (이벤트 수신)
========================================
[OsTask_DroneHeating] ClearEvent()
[RTE] Rte_Read() 호출 data_valid 초기화.

[RE_DroneHeating] 실행됨. drone_detected = 1
[DS18B20#1 STUB] 내부 온도: 16.0°C
[RE_DroneCharging] 실행됨. drone_detected = 1
[RE_DroneCharging] 무선충전 패드 이미 ON 상태 유지
[OsTask_DroneHeating] 처리 완료 → WaitEvent()로 복귀
[OsTask_DroneHeating] WaitEvent() 대기 중...

[ 사이클 3 / 10 ]

========================================
 OsTask_LandingSwitch 실행 (1초 주기)
========================================

[RE_LandingSwitch] ===== 1초 주기 실행 =====
[HC-SR04 STUB] 거리 측정: 5.0cm
[RE_LandingSwitch] 드론 감지거리: 5.0cm < 7cm
[INA219 STUB] 전압: 3.96V | 전류: 500.0mA | 잔량: 3999.6mAh (79%)
[DS18B20#2 STUB] 외부 기온: -5.0°C
[RTE] Rte_Write() 호출
[RTE] 거리: 5cm | 감지: 드론 감지 | 전압: 3.96V | 잔량: 79% | 외부기온: -5.0°C
[RTE] SetEvent(OsTask_DroneHeating, Ev_DataReceive) 호출
[RTE] → OsTask_DroneHeating 활성화 완
[RE_LandingSwitch] ===== 실행 완료 =====
[OsTask_LandingSwitch] TerminateTask()

========================================
 OsTask_DroneHeating 실행 (이벤트 수신)
========================================
[OsTask_DroneHeating] ClearEvent()
[RTE] Rte_Read() 호출 data_valid 초기화.

[RE_DroneHeating] 실행됨. drone_detected = 1
[DS18B20#1 STUB] 내부 온도: 17.5°C
[RE_DroneCharging] 실행됨. drone_detected = 1
[RE_DroneCharging] 무선충전 패드 이미 ON 상태 유지
[OsTask_DroneHeating] 처리 완료 → WaitEvent()로 복귀
[OsTask_DroneHeating] WaitEvent() 대기 중...

[ 사이클 4 / 10 ]

========================================
 OsTask_LandingSwitch 실행 (1초 주기)
========================================

[RE_LandingSwitch] ===== 1초 주기 실행 =====
[HC-SR04 STUB] 거리 측정: 5.0cm
[RE_LandingSwitch] 드론 감지거리: 5.0cm < 7cm
[INA219 STUB] 전압: 3.96V | 전류: 500.0mA | 잔량: 3999.4mAh (79%)
[DS18B20#2 STUB] 외부 기온: -5.0°C
[RTE] Rte_Write() 호출
[RTE] 거리: 5cm | 감지: 드론 감지 | 전압: 3.96V | 잔량: 79% | 외부기온: -5.0°C
[RTE] SetEvent(OsTask_DroneHeating, Ev_DataReceive) 호출
[RTE] → OsTask_DroneHeating 활성화 완
[RE_LandingSwitch] ===== 실행 완료 =====
[OsTask_LandingSwitch] TerminateTask()

========================================
 OsTask_DroneHeating 실행 (이벤트 수신)
========================================
[OsTask_DroneHeating] ClearEvent()
[RTE] Rte_Read() 호출 data_valid 초기화.

[RE_DroneHeating] 실행됨. drone_detected = 1
[DS18B20#1 STUB] 내부 온도: 19.0°C
[RE_DroneHeating] 19.0°C → 18~22°C 범위 유지 중 (상태 유지)
[RE_DroneCharging] 실행됨. drone_detected = 1
[RE_DroneCharging] 무선충전 패드 이미 ON 상태 유지
[OsTask_DroneHeating] 처리 완료 → WaitEvent()로 복귀
[OsTask_DroneHeating] WaitEvent() 대기 중...

[ 사이클 5 / 10 ]

========================================
 OsTask_LandingSwitch 실행 (1초 주기)
========================================

[RE_LandingSwitch] ===== 1초 주기 실행 =====
[HC-SR04 STUB] 거리 측정: 5.0cm
[RE_LandingSwitch] 드론 감지거리: 5.0cm < 7cm
[INA219 STUB] 전압: 3.96V | 전류: 500.0mA | 잔량: 3999.3mAh (79%)
[DS18B20#2 STUB] 외부 기온: -5.0°C
[RTE] Rte_Write() 호출
[RTE] 거리: 5cm | 감지: 드론 감지 | 전압: 3.96V | 잔량: 79% | 외부기온: -5.0°C
[RTE] SetEvent(OsTask_DroneHeating, Ev_DataReceive) 호출
[RTE] → OsTask_DroneHeating 활성화 완
[RE_LandingSwitch] ===== 실행 완료 =====
[OsTask_LandingSwitch] TerminateTask()

========================================
 OsTask_DroneHeating 실행 (이벤트 수신)
========================================
[OsTask_DroneHeating] ClearEvent()
[RTE] Rte_Read() 호출 data_valid 초기화.

[RE_DroneHeating] 실행됨. drone_detected = 1
[DS18B20#1 STUB] 내부 온도: 20.5°C
[RE_DroneHeating] 20.5°C → 18~22°C 범위 유지 중 (상태 유지)
[RE_DroneCharging] 실행됨. drone_detected = 1
[RE_DroneCharging] 무선충전 패드 이미 ON 상태 유지
[OsTask_DroneHeating] 처리 완료 → WaitEvent()로 복귀
[OsTask_DroneHeating] WaitEvent() 대기 중...

[ 사이클 6 / 10 ]

========================================
 OsTask_LandingSwitch 실행 (1초 주기)
========================================

[RE_LandingSwitch] ===== 1초 주기 실행 =====
[HC-SR04 STUB] 거리 측정: 5.0cm
[RE_LandingSwitch] 드론 감지거리: 5.0cm < 7cm
[INA219 STUB] 전압: 3.96V | 전류: 500.0mA | 잔량: 3999.2mAh (79%)
[DS18B20#2 STUB] 외부 기온: -5.0°C
[RTE] Rte_Write() 호출
[RTE] 거리: 5cm | 감지: 드론 감지 | 전압: 3.96V | 잔량: 79% | 외부기온: -5.0°C
[RTE] SetEvent(OsTask_DroneHeating, Ev_DataReceive) 호출
[RTE] → OsTask_DroneHeating 활성화 완
[RE_LandingSwitch] ===== 실행 완료 =====
[OsTask_LandingSwitch] TerminateTask()

========================================
 OsTask_DroneHeating 실행 (이벤트 수신)
========================================
[OsTask_DroneHeating] ClearEvent()
[RTE] Rte_Read() 호출 data_valid 초기화.

[RE_DroneHeating] 실행됨. drone_detected = 1
[DS18B20#1 STUB] 내부 온도: 22.0°C
[RE_DroneHeating] 22.0°C → 18~22°C 범위 유지 중 (상태 유지)
[RE_DroneCharging] 실행됨. drone_detected = 1
[RE_DroneCharging] 무선충전 패드 이미 ON 상태 유지
[OsTask_DroneHeating] 처리 완료 → WaitEvent()로 복귀
[OsTask_DroneHeating] WaitEvent() 대기 중...

[ 사이클 7 / 10 ]

========================================
 OsTask_LandingSwitch 실행 (1초 주기)
========================================

[RE_LandingSwitch] ===== 1초 주기 실행 =====
[HC-SR04 STUB] 거리 측정: 5.0cm
[RE_LandingSwitch] 드론 감지거리: 5.0cm < 7cm
[INA219 STUB] 전압: 3.96V | 전류: 500.0mA | 잔량: 3999.0mAh (79%)
[DS18B20#2 STUB] 외부 기온: -5.0°C
[RTE] Rte_Write() 호출
[RTE] 거리: 5cm | 감지: 드론 감지 | 전압: 3.96V | 잔량: 79% | 외부기온: -5.0°C
[RTE] SetEvent(OsTask_DroneHeating, Ev_DataReceive) 호출
[RTE] → OsTask_DroneHeating 활성화 완
[RE_LandingSwitch] ===== 실행 완료 =====
[OsTask_LandingSwitch] TerminateTask()

========================================
 OsTask_DroneHeating 실행 (이벤트 수신)
========================================
[OsTask_DroneHeating] ClearEvent()
[RTE] Rte_Read() 호출 data_valid 초기화.

[RE_DroneHeating] 실행됨. drone_detected = 1
[DS18B20#1 STUB] 내부 온도: 23.5°C
[MOSFET STUB] CH1(발열#1): OFF | CH2(발열#2): OFF
[RE_DroneHeating] 23.5°C > 22°C → MOSFET CH1, CH2 OFF (가열 중단)
[RE_DroneCharging] 실행됨. drone_detected = 1
[RE_DroneCharging] 무선충전 패드 이미 ON 상태 유지
[OsTask_DroneHeating] 처리 완료 → WaitEvent()로 복귀
[OsTask_DroneHeating] WaitEvent() 대기 중...

[ 사이클 8 / 10 ]

========================================
 OsTask_LandingSwitch 실행 (1초 주기)
========================================

[RE_LandingSwitch] ===== 1초 주기 실행 =====
[HC-SR04 STUB] 거리 측정: 5.0cm
[RE_LandingSwitch] 드론 감지거리: 5.0cm < 7cm
[INA219 STUB] 전압: 3.96V | 전류: 500.0mA | 잔량: 3998.9mAh (79%)
[DS18B20#2 STUB] 외부 기온: -5.0°C
[RTE] Rte_Write() 호출
[RTE] 거리: 5cm | 감지: 드론 감지 | 전압: 3.96V | 잔량: 79% | 외부기온: -5.0°C
[RTE] SetEvent(OsTask_DroneHeating, Ev_DataReceive) 호출
[RTE] → OsTask_DroneHeating 활성화 완
[RE_LandingSwitch] ===== 실행 완료 =====
[OsTask_LandingSwitch] TerminateTask()

========================================
 OsTask_DroneHeating 실행 (이벤트 수신)
========================================
[OsTask_DroneHeating] ClearEvent()
[RTE] Rte_Read() 호출 data_valid 초기화.

[RE_DroneHeating] 실행됨. drone_detected = 1
[DS18B20#1 STUB] 내부 온도: 23.0°C
[RE_DroneCharging] 실행됨. drone_detected = 1
[RE_DroneCharging] 무선충전 패드 이미 ON 상태 유지
[OsTask_DroneHeating] 처리 완료 → WaitEvent()로 복귀
[OsTask_DroneHeating] WaitEvent() 대기 중...

[ 사이클 9 / 10 ]

========================================
 OsTask_LandingSwitch 실행 (1초 주기)
========================================

[RE_LandingSwitch] ===== 1초 주기 실행 =====
[HC-SR04 STUB] 거리 측정: 5.0cm
[RE_LandingSwitch] 드론 감지거리: 5.0cm < 7cm
[INA219 STUB] 전압: 3.96V | 전류: 500.0mA | 잔량: 3998.7mAh (79%)
[DS18B20#2 STUB] 외부 기온: -5.0°C
[RTE] Rte_Write() 호출
[RTE] 거리: 5cm | 감지: 드론 감지 | 전압: 3.96V | 잔량: 79% | 외부기온: -5.0°C
[RTE] SetEvent(OsTask_DroneHeating, Ev_DataReceive) 호출
[RTE] → OsTask_DroneHeating 활성화 완
[RE_LandingSwitch] ===== 실행 완료 =====
[OsTask_LandingSwitch] TerminateTask()

========================================
 OsTask_DroneHeating 실행 (이벤트 수신)
========================================
[OsTask_DroneHeating] ClearEvent()
[RTE] Rte_Read() 호출 data_valid 초기화.

[RE_DroneHeating] 실행됨. drone_detected = 1
[DS18B20#1 STUB] 내부 온도: 22.5°C
[RE_DroneCharging] 실행됨. drone_detected = 1
[RE_DroneCharging] 무선충전 패드 이미 ON 상태 유지
[OsTask_DroneHeating] 처리 완료 → WaitEvent()로 복귀
[OsTask_DroneHeating] WaitEvent() 대기 중...

[ 사이클 10 / 10 ]

========================================
 OsTask_LandingSwitch 실행 (1초 주기)
========================================

[RE_LandingSwitch] ===== 1초 주기 실행 =====
[HC-SR04 STUB] 거리 측정: 5.0cm
[RE_LandingSwitch] 드론 감지거리: 5.0cm < 7cm
[INA219 STUB] 전압: 3.96V | 전류: 500.0mA | 잔량: 3998.6mAh (79%)
[DS18B20#2 STUB] 외부 기온: -5.0°C
[RTE] Rte_Write() 호출
[RTE] 거리: 5cm | 감지: 드론 감지 | 전압: 3.96V | 잔량: 79% | 외부기온: -5.0°C
[RTE] SetEvent(OsTask_DroneHeating, Ev_DataReceive) 호출
[RTE] → OsTask_DroneHeating 활성화 완
[RE_LandingSwitch] ===== 실행 완료 =====
[OsTask_LandingSwitch] TerminateTask()

========================================
 OsTask_DroneHeating 실행 (이벤트 수신)
========================================
[OsTask_DroneHeating] ClearEvent()
[RTE] Rte_Read() 호출 data_valid 초기화.

[RE_DroneHeating] 실행됨. drone_detected = 1
[DS18B20#1 STUB] 내부 온도: 22.0°C
[RE_DroneHeating] 22.0°C → 18~22°C 범위 유지 중 (상태 유지)
[RE_DroneCharging] 실행됨. drone_detected = 1
[RE_DroneCharging] 무선충전 패드 이미 ON 상태 유지
[OsTask_DroneHeating] 처리 완료 → WaitEvent()로 복귀
[OsTask_DroneHeating] WaitEvent() 대기 중...

========================================
 시뮬레이션 종료 (10 사이클 완료)
========================================
```
|사이클|온도|상태|
|---|---|--------|
|1~3|14.5 → 16.0 → 17.5°C|MOSFET CH1, CH2 ON (가열 중)<br>무선충전 패드 ON|
|4~6|19.0 → 20.5 → 22.0°C|18~22°C 범위 → 현재 상태 유지 (히스테리시스)<br>무선충전 패드 ON 유지|
|7|23.5°C|22°C 초과 → MOSFET CH1, CH2 OFF (가열 중단)|
|8~10|23.0 → 22.5 → 22.0°C|아직 22°C 이상 → OFF 상태 유지<br>무선충전 패드 ON 유지|

