# ERIKA3 를 이용한 OSEK/VDX 기반 SW 구성 시도
##### RT-Druid의 부재로 인해 SW 완성 실패 -> 함수로 로직만 구현해 테스트하는 용도로 사용하였음.

   > 실제 코드에서는 OSEK/VDX 기반 .oil 파일을 구성하는 등 파일 코드를 구성했지만 RT-Druid 부재로 인해 SW 상에서는 점검이 불가함.
   > 이를 반영해 기본 기능들을 일반 함수로 구현한 시뮬레이터 버전을 따로 개발해 로직만 테스트 할 수 있도록 하였음.
   > 실 구동 시 OSEK/VDX OS (ERIKA3) 를 사용할 수 있도록 버전을 분리하였음. (#ifdef SIMULATION_MODE 와 #else로 분기)

### ERIKA3 개발 단계
1. SW 요구사항 도출 (2026_03_27)
2. SW 구조도 도출 (2026_03_08)
3. SW 로직 테스트 (2026_03_27)

<img width="1920" height="1080" alt="7" src="https://github.com/user-attachments/assets/098ba995-601e-433c-baf8-2924bfec7f1f" />

<img width="1920" height="1080" alt="8" src="https://github.com/user-attachments/assets/a21f8189-03aa-42fc-8f9f-28311ecd2711" />

