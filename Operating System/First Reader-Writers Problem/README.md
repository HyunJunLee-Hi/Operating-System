# First Reader-Writers Problem
## 프로그램 구조
##### 2명의 reader와 5명의 writer가 접근을 할 때 reader에게 우선순위를 줘서 readcount가 0이 되기 전까지는 writer에게 권한을 주지 않는 방식으로 race를 방지
## 함수
##### Writer함수는 cur_count 전역변수를 0부터 99까지 1씩 증가하는 i로 덮어써주고 출력
##### Semaphore를 이용해서 다른 thread의 접근을 차단
##### Reader함수는 S semaphore를 이용해서 readcount의 race를 방지해주고, reader thread가 들어오면 readcount를 1씩 증가시켜주고 reader가 0이 되기 전까지 writer thread의 접근을 불허
## First Reader-Writers Problem 해결 과정
##### First Reader-writers Problem을 해결하는 방식은 Reader에게 우선순위를 줘서 더 이상의 reader가 없을 때까지 writer을 wait시키는 방식으로 문제를 해결
##### S와 wrt 두개의 semaphore를 이용해서 S로는 readcount에 대한 race를 방지하고 wrt를 이용해서 reader가 없을 때까지 writer를 unbounded waiting
##### 모든 reader가 작업을 마치면 writer의 접근을 허용하는 방식으로 해결
