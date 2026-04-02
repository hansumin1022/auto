# SW 코드의 MISRA C 준수 여부

| 규칙 번호         | 위반 내용                                                       | 위반 예시 / 함수                                                       | 위반 파일                                                  | 심각도 |
| ------------- | ----------------------------------------------------------- | ---------------------------------------------------------------- | ------------------------------------------------------ | --- |
| Rule 21.6     | 표준 입출력 함수(<stdio.h>)는 사용하지 않아야 한다                           | #include <stdio.h>, printf()                                     | rte.c, swc_landingswitch.c, swc_droneheating.c, main.c | 필수  |
| Rule 21.3     | 동적 메모리 할당 및 해제 함수(<string.h> memset/memcpy 포함)는 사용하지 않아야 한다 | memset(), memcpy()                                               | rte.c                                                  | 필수  |
| Rule 15.5     | 함수는 단일 출구(return)만 가져야 한다                                   | 함수 중간 return 사용                                                  | swc_droneheating.c, main.c                             | 필수  |
| Rule 14.4     | if/while/for 조건식은 반드시 boolean 타입이어야 한다                      | if(sim_mosfet_ch1 && sim_mosfet_ch2)                             | swc_droneheating.c                                     | 필수  |
| Rule 10.4     | 복합 표현식에서 양쪽 피연산자는 동일한 타입이어야 한다                              | float ↔ unsigned int 비교                                          | swc_droneheating.c, swc_landingswitch.c                | 필수  |
| Rule 8.4      | 외부 연결을 가진 객체 및 함수는 호환되는 선언이 있어야 한다                          | extern int sim_event_flag 헤더 선언 없음                               | main.c                                                 | 필수  |
| Rule 14.4     | 부동소수점 변수는 == 또는 != 로 직접 비교하지 않아야 한다                         | if(distance_cm < (float)DRONE_DETECT_THRESHOLD_CM)               | swc_landingswitch.c                                    | 필수  |
| Directive 4.6 | 기본 숫자 타입(int, char, float 등) 대신 typedef로 정의된 타입을 사용해야 한다    | float, int, unsigned char 직접 사용                                  | 전체 파일                                                  | 권고  |
| Rule 10.1     | 피연산자는 적절한 타입이어야 한다 (매직 넘버 사용 금지)                            | sim_plate_temp += 1.5f, -= 0.5f                                  | swc_droneheating.c                                     | 권고  |
| Rule 8.9      | 하나의 함수에서만 사용되는 객체는 블록 scope로 선언해야 한다                        | static Rte_DataType_LandingStatus rte_buffer                     | rte.c                                                  | 권고  |
| Rule 12.1     | 표현식에서 연산자 우선순위를 괄호로 명확히 표현해야 한다                             | sim_remaining -= sim_current * (get_elapsed_seconds() / 3600.0f) | swc_landingswitch.c                                    | 권고  |
| Rule 2.2      | C++ 스타일 주석(//)을 사용하지 않아야 한다                                 | // 주석 사용                                                         | swc_droneheating.c                                     | 권고  |
| Rule 16.6     | 비표준 라이브러리 함수는 사용하지 않아야 한다                                   | sleep() (POSIX 함수 사용)                                            | main.c                                                 | 필수  |
| Rule 2.1      | 루프 제어 변수는 루프 내부에서 선언해야 한다                                   | int cycle을 for문 외부에 선언                                           | main.c                                                 | 권고  |
