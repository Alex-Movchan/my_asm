.name "zork"    
.comment "I'M ALIIIIVE"
	sti r1,%:live, %0 #fdsafafds
	and r1,%0,r1
live:    live %1
	zjmp %:live
