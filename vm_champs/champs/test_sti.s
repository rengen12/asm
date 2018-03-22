.name           "f"
.comment        "Just a basic Winner Program"

lab1:
	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1
	live %0
	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1
lab2:
	sti r1, %5000000000, %0