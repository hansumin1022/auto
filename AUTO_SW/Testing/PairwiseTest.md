# PICT 이용 페이와이즈 테스트 케이스 도출

### PairWise Test
> 모든 변수의 쌍이 최소 1번씩은 등장하도록 한다.

<br>

### PICT 설치
```
sudo apt install -y cmake g++
git clone https://github.com/microsoft/pict.git ~/pict
cd ~/pict
cmake .
make
sudo make install
```
### PICT 입력 파일
```
cat > ~/AUTOSAR_IN_ERIKA3/drone_pict.txt << 'EOF'
# CSWC_DroneSystem 페어와이즈 입력 변수 정의

drone_detected:     감지, 미감지
plate_temp:         저온, 정상, 고온
ambient_temp:       영하, 영상
battery_percent:    고, 저
EOF
```
### PICT 실행 
```
pict ~/AUTOSAR_IN_ERIKA3/drone_pict.txt
```

### PICT를 통해 도출한 페어와이즈 테스트케이스

|테스트케이스|drone_detected|plate_temp|ambient_temp|battery_percent|
|--|--|--|--|--|
|PW-01|감지|저온|영하|저|
|PW-02|감지|고온|영상|고|
|PW-03|미감지|고온|영상|저|
|PW-04|미감지|정상|영상|고|
|PW-05|미감지|고온|영하|고|
|PW-06|감지|정상|영하|저|
|PW-07|미감지|저온|영상|고|
