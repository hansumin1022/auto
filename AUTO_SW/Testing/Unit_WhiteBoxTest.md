# SW 테스팅
- 실제 구동을 위한 HW의 부재로 인한 이하 SW의 로직을 검증용 시뮬레이션의 테스트 환경은 아래와 같음.

|항목| 내용|
|--|----|
|테스트 방법| SIL (Software In the Loop) |
|실행환경| Ubuntu 20.04 LTS (VMware) |
|빌드 도구| gcc 9.4.0, make | 
|빌드 옵션| -Wall -Wextra -g -DSIMULATION_MODE |
|시뮬레이션 사이클 주기| 1 sec |
|HW 대체 방법| 스텁(Stub) 함수로 센서 및 GPIO 대체 |
|테스트 케이스 수| 18개 |
|테스트 결과| 100% PASS |

<br>

### 테스트 케이스
* 기능 관련
|순번|내용|입력|확인|
|--|--|--|--|
|TC-01|1초 주기 거리 측정|HC-SR04 스텁 5.0cm 반환|1초마다 거리 측정 로그 출력|
|TC-02|드론 감지 판단|distance_cm = 5 (< 7cm)|drone_detected = 1 설정|
|TC-03|드론 미감지 판단|distance_cm = 10 (≥ 7cm)|drone_detected = 0 설정|
|TC-04|LED 점등 (감지)|drone_detected = 1|LED ON 로그 출력|
|TC-05|LED 소등 (미감지)|drone_detected = 0|LED OFF 로그 출력|
|TC-06|MOSFET ON (저온)|금속판 온도 14.5°C < 18°C|MOSFET CH1, CH2 ON|
|TC-07|MOSFET 상태 유지 (범위 내)|금속판 온도 19.0~22.0°C|현재 상태 유지 (히스테리시스)|
|TC-08|MOSFET OFF (고온)|금속판 온도 23.5°C > 22°C|MOSFET CH1, CH2 OFF|
|TC-09|MOSFET OFF (미감지)|drone_detected = 0|MOSFET CH1, CH2 즉시 OFF|
|TC-10|무선충전 패드 ON|drone_detected = 1|MOSFET CH3 ON|
|TC-11|무선충전 패드 OFF|입력: drone_detected = 0|MOSFET CH3 OFF|
|TC-12|배터리 전압 측정|INA219 스텁 3.96V 반환|battery_voltage = 3.96V|
|TC-13|배터리 잔량 계산|전류 500mA, 주기 1초|잔량 mAh 감소 계산 정상|
|TC-14|외부 기온 측정|DS18B20#2 스텁 -5.0°C 반환|ambient_temp = -5.0°C|

<br>

* RTE/OS 관련
|순번|내용|입력|확인|
|--|--|--|--|
|TC-15|RTE Write/Read|Rte_Write() 후 Rte_Read() 호출|data_valid 플래그 정상 동작|
|TC-16|SetEvent 트리거|drone_detected = 1 시 SetEvent 호출|OsTask_DroneHeating 활성화|
|TC-17|WaitEvent 대기|이벤트 미수신 상태|Task 대기 상태 유지|
|TC-18|10사이클 연속 동작|10회 반복 실행|오류 없이 정상 완료

### 요구사항 검증 결과


### SW 로직 검증 시뮬레이션 동작 결과 (Software In the Loop) 전문

|사이클|온도|상태|
|---|---|--------|
|1~3|14.5 → 16.0 → 17.5°C|MOSFET CH1, CH2 ON (가열 중)<br>무선충전 패드 ON|
|4~6|19.0 → 20.5 → 22.0°C|18~22°C 범위 → 현재 상태 유지 (히스테리시스)<br>무선충전 패드 ON 유지|
|7|23.5°C|22°C 초과 → MOSFET CH1, CH2 OFF (가열 중단)|
|8~10|23.0 → 22.5 → 22.0°C|아직 22°C 이상 → OFF 상태 유지<br>무선충전 패드 ON 유지|


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

