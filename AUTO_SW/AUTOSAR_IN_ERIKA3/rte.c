cat > ~/ AUTOSAR_IN_ERIKA3 / rte.c << 'EOF'

#include "rte.h" // 2026_03_15 업로드 완료
#include <string.h>
#include <stdio.h>

#ifdef SIMULATION_MODE // 시뮬레이션 모드 (Ubuntu VM gcc용)

  // 시뮬레이션용 SetEvent 스텁 (동작만 출력 예정)
    static void Sim_SetEvent(void)
{
    printf("[RTE] SetEvent(OsTask_DroneHeating, "
        "Ev_DataReceive) 호출\n");
    printf("[RTE] → OsTask_DroneHeating 활성화 완\n");
}

#else // 실제 ERIKA3 환경

#include "ee.h"
#endif

    static Rte_DataType_LandingStatus rte_buffer; // 내부 공유 버퍼 정의


void Rte_Init(void) // rte_buffer 초기화.
{
    memset(&rte_buffer, 0, sizeof(rte_buffer));
    printf("[RTE] 초기화 완\n");
}

void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus* data) //Sender API
{
    memcpy(&rte_buffer, data, sizeof(Rte_DataType_LandingStatus)); // 버퍼로 데이터 복사

    rte_buffer.data_valid = 1U; // Receiver에 데이터 감지 알림

    printf("[RTE] Rte_Write() 호출\n");
    printf("[RTE] 거리: %ucm | 감지: %s | "
        "전압: %.2fV | 잔량: %d%% | 외부기온: %.1f°C\n",
        rte_buffer.distance_cm,
        rte_buffer.drone_detected ? "드론 감지" : "드론 미감지",
        rte_buffer.battery_voltage,
        rte_buffer.battery_percent,
        rte_buffer.ambient_temp);

    if (data->drone_detected) { // 감지 시 RE 활성화
#ifdef SIMULATION_MODE
        Sim_SetEvent();
#else
        SetEvent(OsTask_DroneHeating, Ev_DataReceive);
#endif
    }
    else {
        printf("[RTE] 드론 미감지 → SetEvent 호출 X "
            "OsTask_DroneHeating 지속 대기.\n");
    }
}


void Rte_Read_LandingStatus(Rte_DataType_LandingStatus* data)
{
	memcpy(data, &rte_buffer, sizeof(Rte_DataType_LandingStatus)); // 버퍼에서 데이터 복사

    rte_buffer.data_valid = 0U; // Receiver에 데이터 감지 알림 초기화 (중복처리 방지)

    printf("[RTE] Rte_Read() 호출 "
        "data_valid 초기화.\n");
}
EOF