# Peterson’s algorithm을 통한 race condition 관리
## 프로그램 구조
##### Shared memory를 통해서 두 프로세스가 하나의 critical_section_variable에 접근하여 값을 1씩 더해주는 프로그램
##### Race condition을 관리해주기 위해 peterson’s algorithm을 통해 동기화
##### Processidassign을 통해 myorder을 받아오고 하나의 프로세스가 접근하면 processidassign을 1씩 올려주는 방식으로 프로세스를 구별
