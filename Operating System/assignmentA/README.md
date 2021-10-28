# utual exclusion
## 자료구조 설명
##### Atomic_int와 peterson’s algorithm을 사용한 mutual exclusion
##### 동기화를 통해서 전역변수 critical_section_variable에 race condition 방지
## 동기화 방법 
##### Peterson’s algorithm을 사용해서 전역변수로 atomic_int turn과 atomic_int flag를 사용하고 flag의 값이 0과 1일 때는 구분하여 lock을 해주고 unlock을 해주는 방식으로 동기화
## 프로그램 설명
##### Critical_section_variable에 thread가 접근할 때 peterson’s algorithm을 사용한 lock을 걸어서 그 다음 접근하는 thread는 while문에 두고 처음 들어온 thread가 작업을 다 끝내면 unlock해주고 두번째 thread가 while문을 나와 lock을 해주는 과정을 통해 race condition을 관리해주는 프로그램
