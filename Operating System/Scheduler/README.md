# Linux scheduler
## mysched.c
##### CPU run queue안에 총 5개의 sub_run queue가 존재
##### mysched를 추가하여 CPU가 다음에 실행할 프로세스를 선택
##### stop_task scheduler class를 사용하는 프로세스가 있는지 확인하고 없다면 deadline scheduler class(ready 상태)를 사용하는 프로세스가 있는지 확인하고 이러한 방식을 따라서 RT->CFS(fair)->mysched->IDLE_TASK 순서로 동작
##### scheduler entity는 번호표 개념
##### Runqueue(rq)에는 running 상태인 task들 존재
##### rq->curr에는 실제 CPU에서 수행중인 task 존재
##### Fork 등으로 enqueue_task()를 통해 rq에 삽입되고 어떠한 주기 혹은 이벤트로 CPU에서 실행되겠다 결정되면 pick_next_task()통해서 rq->curr로 만듬
##### 실행 중 어떠한 이유로 빼앗기면 put_prev_task()로 rq로 돌아가 대기
##### sleep를 통해 dequeue_task()로 제거되기도 함
##### mysched.c는 기본적으로 FIFO run queue형태로 구성
##### Subrun queue는 double linked list로 구현

## myrr.c
##### 스케줄러 우선순위는 rt->mysched->myrr->cfs->idle 순서로 진행
##### myrr은 round robin 방식을 바탕으로 동작
##### 시간 대신 sched_myrr_entity 안에 있는 update_num의 값이 3이 넘어가면 Time Slice가 모두 소진 됐다고 생각하고 현재 실행되고 있는 task를 queue의 맨 뒤로 옮겨주는 정렬을 한 뒤 update num값을 초기화해주고 rescheduling
##### myrr 프로세스들이 newclass 코드에 의해 1초 간격으로 fork되며, fork된 각각의 프로세스는 1씩 200000000번 더하는 작업을 10번 반복
##### 모든 작업이 끝난 뒤 프로세스는 종료되며 update_num이 3보다 크면 reschedule 함수를 호출하여 스케줄링을 실행

## mypriority.c
##### mypriority_rq 안에 queue를 배열로 선언하여 index값을 기준으로 우선 순위를 구현(최대 크기를 10으로 제한)
##### Enqueue시 queue의 priority_num값 번째에 enqueue 시켜주었습니다. 
##### nr_running을 1씩 더해주고 check 배열의 priority_num 번째 값을 1씩 올려줬습니다. (task_next_pick에서 가장 우선 순위가 높은 task를 고르기 위한 배열)
##### Dequeue시 nr_running이 0보다 큰 경우 dequeue시켜주며 nr_running의 값과 check 배열의 priority_num번째 값을 1씩 차감

