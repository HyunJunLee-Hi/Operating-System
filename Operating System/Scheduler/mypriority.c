#include "sched.h"
static void put_prev_task_mypriority(struct rq *rq, struct task_struct *p);
static int select_task_rq_mypriority(struct task_struct *p, int cpu, int sd_flag, int flags);
static void set_curr_task_mypriority(struct rq *rq);
static void task_tick_mypriority(struct rq *rq,struct task_struct *p, int oldprio);
static void switched_to_mypriority(struct rq *rq, struct task_struct *p);
void init_mypriority_rq(struct mypriority_rq *mypriority_rq);
static void update_curr_mypriority(struct rq *rq);
static void enqueue_task_mypriority(struct rq *rq, struct task_struct *p, int flags);
static void dequeue_task_mypriority(struct rq *rq, struct task_struct *p, int flags);
static void check_preempt_curr_mypriority(struct rq *rq, struct task_struct *p,int flags);
struct task_struct *pick_next_task_mypriority(struct rq *rq, struct task_struct *prev);
static void prio_changed_mypriority(struct rq *rq, struct task_struct *p, int oldprio);

#define MYPRIORITY_TIME_SLICE 3
const struct sched_class mypriority_sched_class={
	.next=&fair_sched_class,
	.enqueue_task=&enqueue_task_mypriority,
	.dequeue_task=dequeue_task_mypriority,
	.check_preempt_curr=check_preempt_curr_mypriority,
	.pick_next_task=pick_next_task_mypriority,
	.put_prev_task=put_prev_task_mypriority,
#ifdef CONFIG_SMP
	.select_task_rq=select_task_rq_mypriority,
#endif
	.set_curr_task=set_curr_task_mypriority,
	.task_tick=task_tick_mypriority,
	.prio_changed=prio_changed_mypriority,
	.switched_to=switched_to_mypriority,
	.update_curr=update_curr_mypriority,
};

void init_task_mypriority(struct task_struct *p) 
{
	struct sched_mypriority_entity *se = &p -> mypriority;

	p->sched_class = &mypriority_sched_class;
}

void init_mypriority_rq (struct mypriority_rq *mypriority_rq)
{
	int i;
	printk(KERN_INFO "***[MYPRIORITY] Mysched class is online \n");
	mypriority_rq->nr_running=0;
	for (i = 0; i<10; i++) {

		INIT_LIST_HEAD(&mypriority_rq->queue[i]);
	}
}
static void update_curr_mypriority(struct rq *rq){
	
	struct task_struct* curr = rq->curr;
	struct sched_mypriority_entity* mypriority_se = &curr->mypriority;

	mypriority_se->aging_num++;
	printk(KERN_INFO "***[MYPRIORITY] update_curr_mypriority\tpid=%d update_num=%d, -------------- prio_num=%d\n", curr->pid, mypriority_se->aging_num, mypriority_se->priority_num);
	if (mypriority_se->aging_num > 3){
		list_del_init(&curr->mypriority.run_list);
		list_add_tail(&curr->mypriority.run_list, &rq->mypriority.queue[mypriority_se->priority_num]);
		mypriority_se->aging_num = 0;
		resched_curr(rq);
	}

}

static void enqueue_task_mypriority(struct rq *rq, struct task_struct *p, int flags) {

	struct mypriority_rq* mypriority_rq = &rq->mypriority;
	struct sched_mypriority_entity* mypriority_se = &p->mypriority;
	
	
	list_add_tail(&p->mypriority.run_list, &rq->mypriority.queue[mypriority_se->priority_num]);
	rq->mypriority.nr_running++;
	rq->mypriority.check[mypriority_se->priority_num]++;

	printk(KERN_INFO"***[MYPRIORITY] enqueue: success cpu=%d, nr_running=%d, pid=%d\n",cpu_of(rq), rq->mypriority.nr_running,p->pid);
}
static void dequeue_task_mypriority(struct rq *rq, struct task_struct *p, int flags) 
{
	struct mypriority_rq* mypriority_rq = &rq->mypriority;
	struct sched_mypriority_entity* mypriority_se = &p->mypriority;

	if(rq->mypriority.nr_running>0)
	{
		
		list_del_init(&p->mypriority.run_list);
		rq->mypriority.nr_running--;
		rq->mypriority.check[mypriority_se->priority_num]--;

		printk(KERN_INFO"\t***[MYPRIORITY] dequeue: success cpu=%d, nr_running=%d, pid=%d\n",cpu_of(rq), rq->mypriority.nr_running,p->pid);
	}
	else{
	}
	
}
void check_preempt_curr_mypriority(struct rq *rq, struct task_struct *p, int flags) {
	printk("***[MYPRIORITY] check_preempt_curr_mypriority\n");
}
struct task_struct *pick_next_task_mypriority(struct rq *rq, struct task_struct *prev)
{
	struct mypriority_rq* mypriority_rq = &rq->mypriority;


	struct task_struct* p;
	struct sched_mypriority_entity* mypriority_se = NULL;
	int i;

	if(rq->mypriority.nr_running == 0 ){
		return NULL;
	}
	
	else {
		for(i = 0 ; i<10; i++) {
			if(rq->mypriority.check[i] > 0) {
				mypriority_se = list_entry(rq->mypriority.queue[i].next, struct sched_mypriority_entity, run_list);
				p = container_of(mypriority_se, struct task_struct, mypriority);
				printk(KERN_INFO "\t***[MYPRIORITY] pick_next_task: cpu=%d, prev->pid=%d,next_p->pid=%d,nr_running=%d\n", cpu_of(rq), prev->pid, p->pid, rq->mypriority.nr_running);
				return p;
			}
		}
		return NULL;
	}

}
void put_prev_task_mypriority(struct rq *rq, struct task_struct *p) {
	printk(KERN_INFO "\t***[MYPRIORITY] put_prev_task: do_nothing, p->pid=%d\n",p->pid);
}
int select_task_rq_mypriority(struct task_struct *p, int cpu, int sd_flag, int flags){return task_cpu(p);}
void set_curr_task_mypriority(struct rq *rq){
	printk(KERN_INFO"***[MYPRIORITY] set_curr_task_mypriority\n");
}
void task_tick_mypriority(struct rq *rq, struct task_struct *p, int queued) {
	update_curr_mypriority(rq);
}
void prio_changed_mypriority(struct rq *rq, struct task_struct *p, int oldprio) { }
/*This routine is called when a task migrates between classes*/
void switched_to_mypriority(struct rq *rq, struct task_struct *p)
{
	resched_curr(rq);
}

