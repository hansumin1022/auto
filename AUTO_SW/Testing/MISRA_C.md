# SW 코드의 MISRA C 준수 여부

| 규칙 | 내용 | 위반 파일 | 심각도 |
|---|---|---|---|
| Rule 21.6 | stdio.h 사용 금지 | rte.c, swc_landingswitch.c, swc_droneheating.c, main.c | 필수 |
| Rule 21.3 | memset/memcpy 금지 | rte.c | 필수 |
| Directive 4.6 | 기본 타입 직접 사용 | 전체 | 권고 |
| Rule 15.5 | 중간 return 사용 | swc_droneheating.c, main.c | 필수 |
| Rule 14.4 | float 직접 비교 | swc_landingswitch.c, swc_droneheating.c | 필수 |
| Rule 10.4 | 다른 타입 간 비교 | swc_droneheating.c | 필수 |
| Rule 10.1 | 매직 넘버 사용 | swc_droneheating.c | 권고 |
| Rule 8.4 | extern 전역변수 | main.c | 필수 |
| Rule 8.9 | 불필요한 파일 scope 변수 | rte.c | 권고 |
| Rule 12.1 | 연산자 우선순위 불명확 | swc_landingswitch.c | 권고 |
| Rule 14.4 | 비boolean 논리 연산 | swc_droneheating.c | 필수 |
| Rule 2.2 | // 주석 사용 | swc_droneheating.c | 권고 |


### Rule 2.2 | 주석 사용
