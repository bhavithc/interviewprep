# POSIX MQ
- Allow processes to exchange data in the form of messages
- Posix mq are reference counted. A queue that is marked for deletion is removed only after it is closed by all processes that are currenly using it
- Posix mq has an associated priority, and message are always striclty queued(and thus received) in priority order
- Posix mq provide feature that allows a process to be asynchornously notified when a message is available on a queue

Refer:
1. https://users.pja.edu.pl/~jms/qnx/help/watcom/clibref/mq_overview.html
2. https://www.softprayog.in/programming/interprocess-communication-using-posix-message-queues-in-linux (With server and client sample)

### Summary 
- Allow processes to exchange data in the form of messages
- Each message is associated with interger priority, and message are queued(and thus received) in order of priority
- They are reference counted and that a process can be asynchornously notifed of the arrival of message on an empty queue
- less portable than System V message queues

