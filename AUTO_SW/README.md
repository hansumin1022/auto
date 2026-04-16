# Project AUTO _ SW 부문

### 개발 단계
1. SW 요구사항 도출 (2026_03_27)
2. SW 구조도 도출 (2026_03_08)
3. SW 로직 테스트 (2026_03_27)

<br>

   > 실제 코드에서는 OSEK/VDX 기반 .oil 파일을 구성하는 등 파일 코드를 구성했지만 RT-Druid 부재로 인해 SW 상에서는 점검이 불가함.
   > 이를 반영해 기본 기능들을 일반 함수로 구현한 시뮬레이터 버전을 따로 개발해 로직만 테스트 할 수 있도록 하였음.
   > 실 구동 시 OSEK/VDX OS (ERIKA3) 를 사용할 수 있도록 버전을 분리하였음. (#ifdef SIMULATION_MODE 와 #else로 분기)

---

> ## Project Status
- 2023-2학기 한국공학대학교 산업 AI마이크로디그리 미래차 실무 과정 중 국민대 현대오토사센터에서 주관한 AUTOSAR 실습 당시 프로젝트 구성 발표

- 2026_02_16 위를 고도화하여 OSEK/VDX 기반 운영체제에서의 기능 구현을 목표로 <b>Project AUTO SW 부문</b> 계획
  
- 2026_02_17 SW 분과 개발 도구인 ERIKA3는 GitHub 미러 저장소를 찾아 확보했지만, RT-Druid는 아카이브 파일 탐색 불가. (~함께 찾아준 GPT와 Claude에게 이 영광을..~)
  - 2025년 부로 ERIKA 사의 오픈소스 배포 및 개발이 중단된 것으로 보여짐.. (~군대 가지 말걸~)
  - RT-Druid 없이 OIL 파일 직접 구성하는 방식으로 기능 구현 예정.
  - Ubuntu 20.04를 VMWare 상에서 구동하는데, RTOS의 빌드 및 실행화면 표시를 위해 KVM activate 하였음.

- 2026_02_25 한국공대 프로젝트 리뷰 과정에서 OSTask 누락 발견 (data receive event 또한 비동기 Task로 OS 관리 필요)
  
-2026_03_08 SW 구조도 완성

- 2026_03_10 Linux 20.04 내 suminhan@ubunto/AUTOSAR_IN_ERIKA3/ 폴더 개설
  (Linux 내 구축한 VS code 이용 C 기반 소스/헤더 파일 순차 업로드 예정)
  
- 2026_03_10 ~/AUTOSAR_IN_ERIKA3$ 폴더 내 Project SW Logic Simulation file Tree 완성
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
  - 2026_03_26 conf.oil 파일 개발 및 주석 처리 후 깃허브 업로드 완료, makefile은 claude로 제작 및 업로드 완료 (makefile 탭 오류로 수정)
  - 2026_03_27 main.c 파일 개발 및 주석 처리 후 깃허브 업로드 완료. 시뮬레이션 실행 에러...
### 2026_03_30 모든 시뮬레이션 코드 개발 완료, 시뮬레이션 테스트 정상 작동 확인
- 정상 작동된 시뮬레이션 결과 화면은 requirements.md 파일에 요구사항 및 테스트 결과와 함께 정리할 예정 (~26/04)
  
### RT-Druid 설치 불가, ERIKA3 공식 파일 지원 중단으로 인한 OSEK/VDX SW 단독 동작 불가

- 2026_04_16 명지대학교 스마트자동차 실험실 내에 설치된 MATLAB Simulink를 이용해 위 다이어그램 코드를 생성해보고 싶었지만 R2016a 버전은 AUTOSAR도, Embedded Coder도 지원하지 않는다..
- 한국공대는 학번을 넣으면 자동으로 개인 라이선스가 지급되던데 우리는 학교에서만 쓸 수 있으면서 버전도 2016이다.. 나도 시뮬링크 써보고 싶다아아아아!

