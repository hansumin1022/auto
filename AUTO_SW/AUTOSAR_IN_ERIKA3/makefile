cat > ~/AUTOSAR_IN_ERIKA3/Makefile << 'EOF'

# ============================================================
# Makefile - CSWC_DroneSystem
#
# [사용법]
#   make sim    : Ubuntu VM에서 시뮬레이션 빌드 & 실행
#   make clean  : 빌드 산출물 삭제
#   make erika  : 실제 ERIKA3 빌드 (TC277 타겟)
# ============================================================

# 컴파일러 설정
CC      = gcc

# 컴파일 옵션
# -Wall    : 모든 경고 출력
# -Wextra  : 추가 경고 출력
# -g       : 디버그 정보 포함
# -DSIMULATION_MODE : 시뮬레이션 모드 활성화
CFLAGS  = -Wall -Wextra -g -DSIMULATION_MODE

# 소스 파일 목록
SRCS    = main.c \
          rte.c \
          swc_landingswitch.c \
          swc_droneheating.c

# 실행 파일 이름
TARGET  = drone_system_sim

# ERIKA3 소스 경로
ERIKA3_DIR = $(HOME)/Downloads/erika3

# ============================================================
# sim: 시뮬레이션 빌드 & 실행
# Ubuntu VM에서 SIMULATION_MODE로 동작 검증
# ============================================================
.PHONY: sim
sim:
	@echo "============================================"
	@echo " 시뮬레이션 빌드 시작 (SIMULATION_MODE)"
	@echo "============================================"
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) -lrt
	@echo "============================================"
	@echo " 빌드 완료! 실행 시작"
	@echo "============================================"
	./$(TARGET)

# ============================================================
# build: 빌드만 (실행 없이)
# ============================================================
.PHONY: build
build:
	@echo "빌드 중..."
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) -lrt
	@echo "빌드 완료: ./$(TARGET)"

# ============================================================
# run: 빌드된 파일 실행
# ============================================================
.PHONY: run
run:
	./$(TARGET)

# ============================================================
# clean: 빌드 산출물 삭제
# ============================================================
.PHONY: clean
clean:
	@echo "빌드 산출물 삭제 중..."
	rm -f $(TARGET) *.o
	@echo "삭제 완료"

# ============================================================
# erika: 실제 ERIKA3 빌드 (TC277 타겟)
# SW 완성 후 TC277 PCB에 올릴 때 사용
# ============================================================
.PHONY: erika
erika:
	@echo "ERIKA3 빌드 시작..."
	@mkdir -p build
	@cp conf.oil build/
	@cp *.c *.h build/
	@cd build && cmake $(ERIKA3_DIR) \
	    -DERIKA3_OIL_FILES=$(PWD)/build/conf.oil \
	    -DCMAKE_BUILD_TYPE=Debug
	@cd build && make
EOF
