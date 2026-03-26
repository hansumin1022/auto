
#include <stdio.h>
#include "rte.h"
#include "swc_landingswitch.h"
#include "swc_droneheating.h"

// 시뮬레이션 환경

#ifdef SIMULATION_MODE

// 시뮬레이션용 Task 실행 함수 (Task 관리 함수)

#include <unistd.h>  // sleep() 함수 사용

#define SIM_CYCLE_COUNT  10  // 시뮬레이션 반복 횟수

// 시뮬레이션용 드론 감지 Data Receive Event

int sim_event_flag = 0;

// OsTask_LandingSwitch 시뮬레이션 (OsAlarm 역할)

static void Sim_OsTask_LandingSwitch(void)
{
    printf("\n");
    printf("========================================\n");
    printf(" OsTask_LandingSwitch 실행 (1초 주기)\n");
    printf("========================================\n");

    // RE_LandingSwitch 호출
    RE_LandingSwitch();

    // TerminateTask() 역할
    printf("[OsTask_LandingSwitch] TerminateTask()\n");
}

// OsTask_DroneHeating 시뮬레이션 (sim_event_flag = 1일 때만 실행)

static void Sim_OsTask_DroneHeating(void)
{
    Rte_DataType_LandingStatus rx_data;

    if (!sim_event_flag) {
        printf("[OsTask_DroneHeating] "
               "WaitEvent() 대기 중...\n");
        return;
    }

    printf("\n");
    printf("========================================\n");
    printf(" OsTask_DroneHeating 실행 (이벤트 수신)\n");
    printf("========================================\n");

    sim_event_flag = 0;
    printf("[OsTask_DroneHeating] ClearEvent()\n");

    // 데이터 수신
    Rte_Read_LandingStatus(&rx_data);

    // RE_DroneHeating 호출
    RE_DroneHeating(rx_data.drone_detected);

    // RE_DroneCharging 호출
    RE_DroneCharging(rx_data.drone_detected);

    printf("[OsTask_DroneHeating] "
           "처리 완료 → WaitEvent()로 복귀\n");
}

int main(void)
{
    int cycle;

    printf("\n");
    printf("========================================\n");
    printf(" CSWC_DroneSystem 시뮬레이션 시작\n");
    printf(" AUTOSAR 구조 기반 ERIKA3 구현 By Sumin Han \n");
    printf("========================================\n\n");

    // SWC 초기화
    Rte_Init();
    SWC_LandingSwitch_Init();
    SWC_DroneHeating_Init();

    printf("\n[StartOS] OS 시작. "
           "OsTask_DroneHeating 대기 상태 진입.\n");
    printf("[OsTask_DroneHeating] WaitEvent() 대기 중...\n");

    //  실제 ERIKA3에서는 StartOS()가 Task 관리

    for (cycle = 1; cycle <= SIM_CYCLE_COUNT; cycle++) {
        printf("\n[ 사이클 %d / %d ]\n",
               cycle, SIM_CYCLE_COUNT);

        // 1초 주기 구현
        sleep(1);

        // OsTask_LandingSwitch 실행
        Sim_OsTask_LandingSwitch();

        // Data Receive Event 수신 시 비동기 Task 실행
        Sim_OsTask_DroneHeating();
        Sim_OsTask_DroneHeating();
    }

    printf("\n========================================\n");
    printf(" 시뮬레이션 종료 (%d 사이클 완료)\n",
           SIM_CYCLE_COUNT);
    printf("========================================\n");

    return 0;
}

#else// 실제 ERIKA3 환경

#include "ee.h"

TASK(OsTask_LandingSwitch)
{
    RE_LandingSwitch();
    TerminateTask();
}

// TASK: OsTask_DroneHeating (비주기 Extended Task)

TASK(OsTask_DroneHeating)
{
    Rte_DataType_LandingStatus rx_data;
    EventMaskType recv_event;

    for (;;) {
        /* Ev_DataReceive 이벤트 대기 */
        WaitEvent(Ev_DataReceive);
        GetEvent(OsTask_DroneHeating, &recv_event);
        ClearEvent(Ev_DataReceive);

        /* RTE Receiver: 데이터 수신 */
        Rte_Read_LandingStatus(&rx_data);

        if (rx_data.data_valid) {
            RE_DroneHeating(rx_data.drone_detected);
            RE_DroneCharging(rx_data.drone_detected);
        }
    }
    TerminateTask();
}

int main(void)
{
    Rte_Init();
    SWC_LandingSwitch_Init();
    SWC_DroneHeating_Init();

    /* ERIKA3 OS 시작 (이후 반환 안 함) */
    StartOS(OSDEFAULTAPPMODE);

    return 0;
}

#endif /* SIMULATION_MODE */
