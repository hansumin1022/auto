suminhan@ubuntu:~/AUTOSAR_IN_ERIKA3$ make sim
gcc -Wall -Wextra -g -DSIMULATION_MODE main.c rte.c swc_landingswitch.c swc_droneheating.c -o drone_system_sim -lrt
In file included from main.c:3:
rte.h:23:3: error: expected identifier or ‘(’ before ‘}’ token
   23 | } } Rte_DataType_LandingStatus;
      |   ^
rte.h:23:5: warning: data definition has no type or storage class
   23 | } } Rte_DataType_LandingStatus;
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.h:23:5: warning: type defaults to ‘int’ in declaration of ‘Rte_DataType_LandingStatus’ [-Wimplicit-int]
rte.h:28:36: warning: type defaults to ‘int’ in declaration of ‘Rte_DataType_LandingStatus’ [-Wimplicit-int]
   28 | void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus *data);
      |                                    ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.h:28:63: error: expected ‘;’, ‘,’ or ‘)’ before ‘*’ token
   28 | void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus *data);
      |                                                               ^
rte.h:31:29: error: expected declaration specifiers or ‘...’ before ‘Rte_DataType_LandingStatus’
   31 | void Rte_Read_LandingStatus(Rte_DataType_LandingStatus *data);
      |                             ^~~~~~~~~~~~~~~~~~~~~~~~~~
In file included from main.c:4:
swc_landingswitch.h:8:32: warning: multi-line comment [-Wcomment]
    8 | #define HCSR04_TRIG_PIN        // P02.3 - GPIO OUT - 초음파 발사\
      |                                ^
In file included from main.c:5:
swc_droneheating.h:15:1: error: unterminated comment
   15 | /* 온도 상수
      | ^
swc_droneheating.h:2: error: unterminated #ifndef
    2 | #ifndef SWC_DRONEHEATING_H
      | 
main.c: In function ‘Sim_OsTask_DroneHeating’:
main.c:41:5: warning: statement with no effect [-Wunused-value]
   41 |     Rte_DataType_LandingStatus rx_data;
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~
main.c:41:31: error: expected ‘;’ before ‘rx_data’
   41 |     Rte_DataType_LandingStatus rx_data;
      |                               ^~~~~~~~
      |                               ;
main.c:58:5: warning: implicit declaration of function ‘Rte_Read_LandingStatus’ [-Wimplicit-function-declaration]
   58 |     Rte_Read_LandingStatus(&rx_data);
      |     ^~~~~~~~~~~~~~~~~~~~~~
main.c:58:29: error: ‘rx_data’ undeclared (first use in this function)
   58 |     Rte_Read_LandingStatus(&rx_data);
      |                             ^~~~~~~
main.c:58:29: note: each undeclared identifier is reported only once for each function it appears in
main.c:61:5: warning: implicit declaration of function ‘RE_DroneHeating’ [-Wimplicit-function-declaration]
   61 |     RE_DroneHeating(rx_data.drone_detected);
      |     ^~~~~~~~~~~~~~~
main.c:64:5: warning: implicit declaration of function ‘RE_DroneCharging’ [-Wimplicit-function-declaration]
   64 |     RE_DroneCharging(rx_data.drone_detected);
      |     ^~~~~~~~~~~~~~~~
main.c: In function ‘main’:
main.c:83:5: warning: implicit declaration of function ‘SWC_DroneHeating_Init’ [-Wimplicit-function-declaration]
   83 |     SWC_DroneHeating_Init();
      |     ^~~~~~~~~~~~~~~~~~~~~
In file included from rte.c:2:
rte.h:23:3: error: expected identifier or ‘(’ before ‘}’ token
   23 | } } Rte_DataType_LandingStatus;
      |   ^
rte.h:23:5: warning: data definition has no type or storage class
   23 | } } Rte_DataType_LandingStatus;
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.h:23:5: warning: type defaults to ‘int’ in declaration of ‘Rte_DataType_LandingStatus’ [-Wimplicit-int]
rte.h:28:36: warning: type defaults to ‘int’ in declaration of ‘Rte_DataType_LandingStatus’ [-Wimplicit-int]
   28 | void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus *data);
      |                                    ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.h:28:63: error: expected ‘;’, ‘,’ or ‘)’ before ‘*’ token
   28 | void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus *data);
      |                                                               ^
rte.h:31:29: error: expected declaration specifiers or ‘...’ before ‘Rte_DataType_LandingStatus’
   31 | void Rte_Read_LandingStatus(Rte_DataType_LandingStatus *data);
      |                             ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.c:21:39: error: expected ‘=’, ‘,’, ‘;’, ‘asm’ or ‘__attribute__’ before ‘rte_buffer’
   21 |     static Rte_DataType_LandingStatus rte_buffer; // 내부 공유 버퍼 정의
      |                                       ^~~~~~~~~~
rte.c: In function ‘Rte_Init’:
rte.c:26:13: error: ‘rte_buffer’ undeclared (first use in this function); did you mean ‘setbuffer’?
   26 |     memset(&rte_buffer, 0, sizeof(rte_buffer));
      |             ^~~~~~~~~~
      |             setbuffer
rte.c:26:13: note: each undeclared identifier is reported only once for each function it appears in
rte.c: At top level:
rte.c:30:36: warning: type defaults to ‘int’ in declaration of ‘Rte_DataType_LandingStatus’ [-Wimplicit-int]
   30 | void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus* data) //Sender API
      |                                    ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.c:30:62: error: expected ‘;’, ‘,’ or ‘)’ before ‘*’ token
   30 | void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus* data) //Sender API
      |                                                              ^
rte.c:59:29: error: expected declaration specifiers or ‘...’ before ‘Rte_DataType_LandingStatus’
   59 | void Rte_Read_LandingStatus(Rte_DataType_LandingStatus* data)
      |                             ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.c:9:17: warning: ‘Sim_SetEvent’ defined but not used [-Wunused-function]
    9 |     static void Sim_SetEvent(void)
      |                 ^~~~~~~~~~~~
In file included from swc_landingswitch.c:2:
swc_landingswitch.h:8:32: warning: multi-line comment [-Wcomment]
    8 | #define HCSR04_TRIG_PIN        // P02.3 - GPIO OUT - 초음파 발사\
      |                                ^
In file included from swc_landingswitch.c:3:
rte.h:23:3: error: expected identifier or ‘(’ before ‘}’ token
   23 | } } Rte_DataType_LandingStatus;
      |   ^
rte.h:23:5: warning: data definition has no type or storage class
   23 | } } Rte_DataType_LandingStatus;
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.h:23:5: warning: type defaults to ‘int’ in declaration of ‘Rte_DataType_LandingStatus’ [-Wimplicit-int]
rte.h:28:36: warning: type defaults to ‘int’ in declaration of ‘Rte_DataType_LandingStatus’ [-Wimplicit-int]
   28 | void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus *data);
      |                                    ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.h:28:63: error: expected ‘;’, ‘,’ or ‘)’ before ‘*’ token
   28 | void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus *data);
      |                                                               ^
rte.h:31:29: error: expected declaration specifiers or ‘...’ before ‘Rte_DataType_LandingStatus’
   31 | void Rte_Read_LandingStatus(Rte_DataType_LandingStatus *data);
      |                             ^~~~~~~~~~~~~~~~~~~~~~~~~~
swc_landingswitch.c: In function ‘RE_LandingSwitch’:
swc_landingswitch.c:112:5: warning: statement with no effect [-Wunused-value]
  112 |     Rte_DataType_LandingStatus tx_data;
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~
swc_landingswitch.c:112:31: error: expected ‘;’ before ‘tx_data’
  112 |     Rte_DataType_LandingStatus tx_data;
      |                               ^~~~~~~~
      |                               ;
swc_landingswitch.c:134:9: error: ‘tx_data’ undeclared (first use in this function)
  134 |         tx_data.drone_detected = 1U;
      |         ^~~~~~~
swc_landingswitch.c:134:9: note: each undeclared identifier is reported only once for each function it appears in
swc_landingswitch.c:186:5: warning: implicit declaration of function ‘Rte_Write_LandingStatus’ [-Wimplicit-function-declaration]
  186 |     Rte_Write_LandingStatus(&tx_data);
      |     ^~~~~~~~~~~~~~~~~~~~~~~
In file included from swc_droneheating.c:2:
swc_droneheating.h:15:1: error: unterminated comment
   15 | /* 온도 상수
      | ^
swc_droneheating.h:2: error: unterminated #ifndef
    2 | #ifndef SWC_DRONEHEATING_H
      | 
In file included from swc_droneheating.c:3:
rte.h:23:3: error: expected identifier or ‘(’ before ‘}’ token
   23 | } } Rte_DataType_LandingStatus;
      |   ^
rte.h:23:5: warning: data definition has no type or storage class
   23 | } } Rte_DataType_LandingStatus;
      |     ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.h:23:5: warning: type defaults to ‘int’ in declaration of ‘Rte_DataType_LandingStatus’ [-Wimplicit-int]
rte.h:28:36: warning: type defaults to ‘int’ in declaration of ‘Rte_DataType_LandingStatus’ [-Wimplicit-int]
   28 | void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus *data);
      |                                    ^~~~~~~~~~~~~~~~~~~~~~~~~~
rte.h:28:63: error: expected ‘;’, ‘,’ or ‘)’ before ‘*’ token
   28 | void Rte_Write_LandingStatus(const Rte_DataType_LandingStatus *data);
      |                                                               ^
rte.h:31:29: error: expected declaration specifiers or ‘...’ before ‘Rte_DataType_LandingStatus’
   31 | void Rte_Read_LandingStatus(Rte_DataType_LandingStatus *data);
      |                             ^~~~~~~~~~~~~~~~~~~~~~~~~~
swc_droneheating.c: In function ‘RE_DroneHeating’:
swc_droneheating.c:117:29: error: ‘TEMP_MIN_CELSIUS’ undeclared (first use in this function)
  117 |     if (plate_temp < (float)TEMP_MIN_CELSIUS) {
      |                             ^~~~~~~~~~~~~~~~
swc_droneheating.c:117:29: note: each undeclared identifier is reported only once for each function it appears in
swc_droneheating.c:131:36: error: ‘TEMP_MAX_CELSIUS’ undeclared (first use in this function)
  131 |     } else if (plate_temp > (float)TEMP_MAX_CELSIUS) {
      |                                    ^~~~~~~~~~~~~~~~
make: *** [Makefile:8: sim] Error 1
