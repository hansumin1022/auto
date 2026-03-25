# Project AUTO _ SW 부문

<img width="1027" height="573" alt="image" src="https://github.com/user-attachments/assets/5695f2e6-18a9-4b89-801e-81660b129723" />


> ## Project Status
- 2023-2학기 한국공학대학교 산업 AI마이크로디그리 미래차 실무 과정 중 국민대 현대오토사센터에서 주관한 AUTOSAR 실습 당시 프로젝트 구성 발표

- 2026_02_16 위를 고도화하여 OSEK/VDX 기반 운영체제에서의 기능 구현을 목표로 <b>Project AUTO SW 부문</b> 계획
  
- 2026_02_17 SW 분과 개발 도구인 ERIKA3는 GitHub 미러 저장소를 찾아 확보했지만, RT-Druid는 아카이브 파일 탐색 불가. (~함께 찾아준 GPT와 Claude에게 이 영광을..~)
  - 2025년 부로 ERIKA 사의 오픈소스 배포 및 개발이 중단된 것으로 보여짐.. (~군대 가지 말걸~)
  - RT-Druid 없이 OIL 파일 직접 구성하는 방식으로 기능 구현 예정.
  - Ubuntu 20.04를 VMWare 상에서 구동하는데, RTOS의 빌드 및 실행화면 표시를 위해 KVM activate 하였음.

- 2026_02_25 한국공대 프로젝트 리뷰 과정에서 OSTask 누락 발견 (data receive event 또한 비동기 Task로 OS 관리 필요)
  
-2026_03_08 SW 구조도 완성
  <img width="1007" height="545" alt="image" src="https://github.com/user-attachments/assets/e3ad9c6f-111b-4513-9f2f-533212f7fa63" />

- 2026_03_10 Linux 20.04 내 suminhan@ubunto/AUTOSAR_IN_ERIKA3/ 폴더 개설
  (Linux 내 구축한 VS code 이용 C 기반 소스/헤더 파일 순차 업로드 예정)
  
- 2026_03_10 ~/AUTOSAR_IN_ERIKA3$ 폴더 내 Project SW file Tree 완성
   ~/AUTOSAR_IN_ERIKA3$
    - conf.oil
    - main.c
    - rte.c
    - rte.h
    - swc_droneheating.c
    - swc_droneheating.h
    - swc_landingswitch.c
    - swc_landingswitch.h
    - makefile </br>
      이상 9개 파일로 업로드 예정.

  - 2026_03_15 rte.h 및 rte.c 파일 개발 및 주석 처리 후 깃허브 업로드 완료
  - 2026_03_21 swc_droneheating.h 및 swc_droneheating.c 파일 개발 및 주석 처리 후 깃허브 업로드 완료
  - 2026_03_23 swc_landingswitch.h 및 swc_landingswitch.c 파일 개발 및 주석 처리 후 깃허브 업로드 완료
    <img width="791" height="55" alt="image" src="https://github.com/user-attachments/assets/04fbbf67-6926-425c-864e-f296b7848947" />
  * 현재는 SW 테스트를 위해 스텁을 통한 시뮬레이션이 가능하도록 설정된 상태임. HAL 활용해 실제 HW 동작 가능

