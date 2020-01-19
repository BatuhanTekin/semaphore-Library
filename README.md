# deu-library-BatuhanTekin
deu-library-BatuhanTekin created by GitHub Classroom

Goal
In this assignment, you will solve synchronization problem using semaphores and mutex. You should suffer from deadlock and/or starvation. 
You are expected to simulate and solve "Library” synchronization problem, which its details are given.

Implementation Details & Requirements

On exam days at the DEU, you are waiting for a long time at the entrance of the working rooms in the

library. We are launching the DEU Library application to facilitate this. This will prevent both all
students to create long queues and to lock the working rooms before be full. Alsoit will provide an

efficient and fair sharing because rooms will contain students up toits capacity.

With your simulation and solution with mutex and semaphores students hopefully will no longer wait

so long for working.

● Each room has 4 students capacity.

● Students will come to library in continuously and random periods.

● The library has 10 working rooms and also 10 room keepers. So, each room contains one
room keeper.
● The states for each room:

○ Entry free state: Room keeper w

ll announce to the students his remaining places to

get in the room,
fit has one or more students
n the room. For example, each room
has 2 students and wait two more students, room keeper calls “The last two students,
let's get up!”

○ Idle (Empty) state: If there

is no student
n the room, the room keeper will cleanroom. Being idle is forbidden for the room keepers.
If any student came, they should open the working room. Don't forget to no student are
waiting.

○ Full and busy state: If there are 4 students

n the room, the room will be
n busy state.

● The states for each student:
○ Waiting
n room: When a student comes at room, she/he gets
n the nearly full
capacity room. If no student
n room, first student alerts keeper
if he is cleaning. And the students will study
n the room until the room’s full. After the room
s full, the students work
n the room more and together they empty the room.
○ Waiting at library: If there
is no empty room, she/he's gonna wait for a room at the
library.

● You should not do the same room work constantly so that others can work overt
me, so

consider the status of starvation.
