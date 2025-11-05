MID TERME EXAM
Added 4th Worker:
- Old code: 3 BlinkWorker for 3 LEDs.
- New code: 4 BlinkWorker for 4 LEDs.

Semaphore:
- Old code: 3 tokens max, but only 2 available initially.
- New code: 4 tokens max, still only 2 available at first.

Personal Info Display:
- New code: Prints your name and student ID every 3 seconds.

Behavior:
With 4 workers and only 2 tokens, only 2 can blink at a time, others wait their turn. It tests resource management under contention.
