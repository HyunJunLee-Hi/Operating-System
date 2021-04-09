#include "sched.h"
void init_mysched_rq(struct mysched_rq *mysched_rq)
{
	printk(KERN_INFO "***[MYSCHED] Myschedclass is online \n");
	mysched_rq->nr_running=0;
	INIT_LIST_HEAD(&mysched_rq->queue);
}

static void update_curr_mysched(struct rq *rq)
{
}
static void enqueue_task_mysched(struct rq *rq, struct task_struct *p, int flags) 
{

	struct mysched_rq *mysched_rq = &rq->mysched;
	struct sched_mysched_entity *mysched_se=&p->mysched;





	list_add_tail(&p->mysched.run_list, &rq->mysched.queue);
	rq->mysched.nr_running++;



	/* osdc lab - print mysched enqueue - CPU num, nr_running, state, pid,*/
	//write printk func here
	printk()

	}
static void dequeue_task_mysched(struct rq *rq, struct task_struct *p, int flags)
{

	struct mysched_rq *mysched_rq = &rq->mysched;
	struct sched_mysched_entity *mysched_se=&p->mysched;   	



	printk(KERN_INFO "***[MYSCHED] dequeue: start\n");
	if( (int) rq->mysched.nr_running > 0 )
	{
		list_del_init(&p->mysched.run_list);
		rq->mysched.nr_running--;

		/* osdc lab - print mysched dequeue - cpu num, state, pid, curr task pid */
		//write printk func here

	}
	else
	{
	}
	printk(KERN_INFO "***[MYSCHED] dequeue: end\n");
	
}
static void check_preempt_curr_mysched(struct rq *rq, struct task_struct *p, int flags) 
{ 
}
struct task_struct *pick_next_task_mysched(struct rq *rq, struct task_struct *prev)
{
	struct mysched_rq *mysched_rq = &rq->mysched;
	
	struct task_struct *p;
	struct sched_mysched_entity *mysched_se = NULL;

	if( list_empty(rq->mysched.queue.next) )
	{
		return NULL;
	}
	else
	{
		//put_prev_task(rq,prev);
		mysched_se = list_entry(rq->mysched.queue.next, struct sched_mysched_entity, run_list);
		p = container_of(mysched_se, struct task_struct, mysched);
		
		/* osdc lab - print mysched pick_next_task - cpu, prev task pid, next task pid, nr_running */
		//write printk func here

		printk(KERN_INFO "***[MYSCHED] pick_next_task: end\n");


		return p;
	}
	
	//put_prev_task(rq, prev);
	//return NULL;
}
static void put_prev_task_mysched(struct rq *rq, struct task_struct *p) 
{
	printk(KERN_INFO "\t***[MYSCHED] put_prev_task: do nothing, p->pid=%d\n", p->pid);
	//list_add(&p->mysched.run_list, &rq->mysched.queue); 
}
static int select_task_rq_mysched(struct task_struct *p, int cpu, int sd_flag, int flags)
{
	return task_cpu(p);
}
static void set_curr_task_mysched(struct rq *rq) 
{ 
}
static void task_tick_mysched(struct rq *rq, struct task_struct *p, int queued) 
{ 
}
static void prio_changed_mysched(struct rq *rq, struct task_struct *p, int oldprio) 
{ 
}
/* This routine is called when a task migrates between classes */
static void switched_to_mysched(struct rq *rq, struct task_struct *p)
{
	resched_curr(rq);
}
const struct sched_class mysched_sched_class = {
	.next			= &idle_sched_class,
	.enqueue_task		= enqueue_task_mysched,
	.dequeue_task		= dequeue_task_mysched,
	.check_preempt_curr	= check_preempt_curr_mysched,
	.pick_next_task		= pick_next_task_mysched,
	.put_prev_task		= put_prev_task_mysched,

#ifdef CONFIG_SMP
	.select_task_rq		= select_task_rq_mysched,
#endif
	.set_curr_task		= set_curr_task_mysched,
	.task_tick		= task_tick_mysched,
	.prio_changed		= prio_changed_mysched,
	.switched_to		= switched_to_mysched,
	.update_curr		= update_curr_mysched,
};
