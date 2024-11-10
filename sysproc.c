#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
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
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
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

int sys_nice(void) {
    int pid, new_nice;
    // Get the process ID and new nice value from arguments
    if (argint(0, &pid) < 0 || argint(1, &new_nice) < 0) {
        return -1;  // Return error if arguments are invalid
    } 

    // Check the range of the new nice value
    if (new_nice < 1 || new_nice > 5) {
        return -1;  // Return error if new_nice is out of bounds
    }

    // Find the process by PID
    struct proc *p = find_proc_by_pid(pid);
    if (!p) {
        return -1;  // Return error if process with given PID is not found
    }

    // Store old nice value, update to new value
    int old_nice = p->nice;
    p->nice = new_nice;
    return old_nice;  // Return old nice value
}

int sys_sched(void) {
  scheduler();
  return 0;
}
