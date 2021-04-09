#include "sched.h"
/// OUTSIDE, WE TOOK TICKET AS ATTRIBUTE, SO TICKET = Priority  FOR
void init_mystride_rq(struct mystride_rq* mystride_rq)
{
	printk(KERN_INFO "***[Priority] Mystrideclass is online \n");
	INIT_LIST_HEAD(&mystride_rq->queue);
}
void init_task_mystride(struct task_struct* p)
{
	struct sched_mystride_entity* se = &p->mystride;

	p->sched_class = &mystride_sched_class;
	se->stride = 1000 / (se->ticket);
	se->pass = se->stride;
}

static void update_task_againg(struct rq* rq)
{
	// START AGAING IN HERE!
	struct list_head* ptr;
	struct sched_mystride_entity* node;
	struct task_struct* current_p;


	printk(KERN_INFO "***[MY_PRO] 21\n");


	list_for_each(ptr, &rq->mystride.queue) {
		node = list_entry(ptr, struct sched_mystride_entity, run_list);

		current_p = container_of(node, struct task_struct, mystride);
		printk(KERN_INFO "***[MY_PRO] aging iterate, p->pid:%d, node->priority->%d\n", current_p->pid, node->ticket);

		if (node->ticket == 0) {
			printk(KERN_INFO "***[MY_PRO] aging already max, p->pid:%d, node->priority->%d\n", current_p->pid, node->ticket);
		}
		else {
			node->ticket = node->ticket - 1;
			printk(KERN_INFO "***[MY_PRO] aging downsize, p->pid:%d, node->priority->%d\n", current_p->pid, node->ticket);
		}
	}
}
static void update_curr_mystride(struct rq* rq)
{
}

static void enqueue_task_mystride(struct rq* rq, struct task_struct* p, int flags)
{
	list_add_tail(&p->mystride.run_list, &rq->mystride.queue);
	rq->mystride.nr_running++;
	printk(KERN_INFO "***[Priority] Dequeue: nr_running = %d, pid = %d\n", rq->mystride.nr_running, p->pid);

}


static void dequeue_task_mystride(struct rq* rq, struct task_struct* p, int flags)
{

	struct mystride_rq* mystride_rq = &rq->mystride;


	printk(KERN_INFO "***[MY_PRO] 53\n");

	update_task_againg(rq);


	printk(KERN_INFO "***[Priority] dequeue: start\n");
	if ((int)rq->mystride.nr_running > 0)
	{
		list_del_init(&p->mystride.run_list);
		rq->mystride.nr_running--;

	}
	else
	{
	}
	printk(KERN_INFO "***[Priority] dequeue: end\n");

}
static void check_preempt_curr_mystride(struct rq* rq, struct task_struct* p, int flags)
{
}
//struct task_struct *pick_next_task_mystride(struct rq *rq, struct task_struct *prev)
//{
//
//    struct list_head *ptr;
//    struct task_struct *p;
//    struct sched_mystride_entity *node;
//    unsigned int max_priority = 100;
//    struct task_struct *current_p;
//
//    printk(KERN_INFO "***[MY_PRO] 80\n");
//
//
//    if( list_empty(rq->mystride.queue.next) )
//    {
//        return NULL;
//    }
//
//    printk(KERN_INFO "***[MY_PRO] 86\n");
//
//
//    list_for_each(ptr, &rq->mystride.queue) {
//        node = list_entry(ptr, struct sched_mystride_entity, run_list);
//        current_p = container_of(node, struct task_struct, mystride);
//        printk(KERN_INFO "***[MY_PRO] pick_next_task iterate, p->pid:%d, node->priority->%d\n", current_p->pid, node->ticket);
//        if (node->ticket < max_priority) {
//            max_priority = node->ticket;
//            p = current_p;
//        }
//    }
//
//    if (p == NULL) {
//        printk(KERN_INFO "***[MY_PRO] pick_next_task failure, you should debug!!\n");
//        return NULL;
//    } else {
//        return p;
//    }
//
//}
struct task_struct* pick_next_task_mystride(struct rq* rq, struct task_struct* prev)
{

	struct task_struct* p;
	struct sched_mystride_entity* mystride_se = NULL;

	if (list_empty(rq->mystride.queue.next))
	{
		return NULL;
	}
	else
	{
		put_prev_task(rq, prev);
		mystride_se = list_entry(rq->mystride.queue.next, struct sched_mystride_entity, run_list);
		p = container_of(mystride_se, struct task_struct, mystride);
		p->se.exec_start = rq_clock_task(rq);

		printk(KERN_INFO "***[MYSTRIDE] pick_next_task: cpu=%d,prev->pid=%d,next_p->pid=%d,nu_running=%d\n", rq->cpu, prev->pid, p->pid, rq->mystride.nr_running);

		printk(KERN_INFO "***[MYSTRIDE] pick_next_task: end\n");


		return p;
	}

	//put_prev_task(rq, prev);
	//return NULL;
}

static void put_prev_task_mystride(struct rq* rq, struct task_struct* p)
{
	printk(KERN_INFO "\t***[Priority] put_prev_task: do nothing, p->pid=%d\n", p->pid);
	list_add(&p->mystride.run_list, &rq->mystride.queue);
}
static int select_task_rq_mystride(struct task_struct* p, int cpu, int sd_flag, int flags)
{
	return task_cpu(p);
}
static void set_curr_task_mystride(struct rq* rq)
{
}
static void task_tick_mystride(struct rq* rq, struct task_struct* p, int queued)
{
}
static void prio_changed_mystride(struct rq* rq, struct task_struct* p, int oldprio)
{
}
/* This routine is called when a task migrates between classes */
static void switched_to_mystride(struct rq* rq, struct task_struct* p)
{
	resched_curr(rq);
}
const struct sched_class mystride_sched_class = {
		.next = &fair_sched_class,
		.enqueue_task = enqueue_task_mystride,
		.dequeue_task = dequeue_task_mystride,
		.check_preempt_curr = check_preempt_curr_mystride,
		.pick_next_task = pick_next_task_mystride,
		.put_prev_task = put_prev_task_mystride,

#ifdef CONFIG_SMP
		.select_task_rq = select_task_rq_mystride,
#endif
		.set_curr_task = set_curr_task_mystride,
		.task_tick = task_tick_mystride,
		.prio_changed = prio_changed_mystride,
		.switched_to = switched_to_mystride,
		.update_curr = update_curr_mystride,
};