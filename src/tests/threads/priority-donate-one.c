/* The main thread acquires a lock.  Then it creates two
   higher-priority threads that block acquiring the lock, causing
   them to donate their priorities to the main thread.  When the
   main thread releases the lock, the other threads should
   acquire it in priority order.

   Based on a test originally submitted for Stanford's CS 140 in
   winter 1999 by Matt Franklin <startled@leland.stanford.edu>,
   Greg Hutchins <gmh@leland.stanford.edu>, Yu Ping Hu
   <yph@cs.stanford.edu>.  Modified by arens. */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/synch.h"
#include "threads/thread.h"

static thread_func acquire1_thread_func;
static thread_func acquire2_thread_func;

void
test_priority_donate_one (void) 
{
  struct lock lock;

  /* This test does not work with the MLFQS. */
  ASSERT (!thread_mlfqs);
  //msg("tetsgjdhjrjf");
  /* Make sure our priority is the default. */
  ASSERT (thread_get_priority () == PRI_DEFAULT);
  //msg("assert done");
  lock_init (&lock);
  lock_acquire (&lock);
 // msg("In test %p\n",(&lock.semaphore));
  //msg("test case thread create befor");
  thread_create ("acquire1", PRI_DEFAULT + 1, acquire1_thread_func, &lock);
  //msg("acquire 1 thread created");
  msg ("This thread should have priority %d.  Actual priority: %d.",
       PRI_DEFAULT + 1, thread_get_priority ());
  //msg("first  msg printed");
  thread_create ("acquire2", PRI_DEFAULT + 2, acquire2_thread_func, &lock);
  //msg("acquire2 thread created");
  msg ("This thread should have priority %d.  Actual priority: %d.",
       PRI_DEFAULT + 2, thread_get_priority ());
 // msg("second msg printed");
  lock_release (&lock);
  msg("locked released by %s\n",thread_current ()->name);
  msg ("acquire2, acquire1 must already have finished, in that order.");
  msg ("This should be the last line before finishing this test.");
}

static void
acquire1_thread_func (void *lock_) 
{
  struct lock *lock = lock_;
 // printf("in acquire1 func\n");
  lock_acquire (lock);
  msg ("acquire1: got the lock");
  lock_release (lock);
  msg ("acquire1: done");
}

static void
acquire2_thread_func (void *lock_) 
{
  struct lock *lock = lock_;
  //msg("In test %p\n",(lock_.semaphore));
  lock_acquire (lock);
  //msg("%s\n",&lock->holder->name);
  msg ("acquire2: got the lock");
  lock_release (lock);
  //ssmsg("dcvw");
  msg ("acquire2: done");
}
