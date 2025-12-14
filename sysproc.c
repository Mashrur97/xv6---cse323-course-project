#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h" 

extern struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;


int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

int
sys_hello(void)
{
    cprintf("Hello from kernel!\n");
    return 0;
}

char*
statename(int state)
{
    switch(state){
    case UNUSED:   return "UNUSED";
    case EMBRYO:   return "EMBRYO";
    case SLEEPING: return "SLEEP";
    case RUNNABLE: return "RUNNABLE";
    case RUNNING:  return "RUNNING";
    case ZOMBIE:   return "ZOMBIE";
    default:       return "UNKNOWN";
    }
}


int sys_meminfo(void) {
    struct proc *p;

    cprintf("PID    NAME     MEMORY(bytes)  CREATED(ticks)    STATE   PRIORITY\n");

    acquire(&ptable.lock);

    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
        if(p->state == UNUSED)
            continue;

      
        cprintf(" %d", p->pid);
        int pid_len = 0, temp = p->pid;
        if(temp == 0) pid_len = 1;
        else while(temp > 0){ pid_len++; temp /= 10; }
        for(int i = pid_len; i < 6; i++) cprintf(" ");

      
        cprintf("%s", p->name);
        int name_len = strlen(p->name);
        for(int i = name_len; i < 12; i++) cprintf(" ");

      
        cprintf("%d", p->sz);
        int mem_len = 0;
        temp = p->sz;
        if(temp == 0) mem_len = 1;
        else while(temp > 0){ mem_len++; temp /= 10; }
        for(int i = mem_len; i < 14; i++) cprintf(" ");

       
        cprintf("%d", p->ctime);
        int time_len = 0;
        temp = p->ctime;
        if(temp == 0) time_len = 1;
        else while(temp > 0){ time_len++; temp /= 10; }
        for(int i = time_len; i < 16; i++) cprintf(" ");

        char *st = statename(p->state);
        cprintf("%s", st);
        int state_len = strlen(st);
        for(int i = state_len; i < 10; i++) cprintf(" ");

        cprintf("%d\n", p->priority);
    }

    release(&ptable.lock);
    return 0;
}



int
sys_chpr(void)
{
  int pid, pr;
  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &pr) < 0)
    return -1;

  return chpr(pid, pr);
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
