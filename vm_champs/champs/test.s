.name           "f"
.comment        "Just a basic Winner Program"

lab1:	
	live %0
	live %-5
	live %5
	live %:lab1
	live %:lab2
	live %5000000000
	live %-5000000000
	
	zjmp %0
	zjmp %-5
	zjmp %5
	zjmp %:lab1
	zjmp %:lab2
	zjmp %5000000000
	zjmp %-5000000000

	ld %0, r1
	ld %-5, r1
	ld %5, r1
	ld %:lab1, r1
	ld %:lab2, r1
	ld %5000000000, r1
	ld %-5000000000, r1

	ld 0, r1
	ld -5, r1
	ld 5, r1
	ld :lab1, r1
	ld :lab2, r1
	ld 5000000000, r1
	ld -5000000000, r1

	st r1, 0
	st r1, 5
	st r1, -5
	st r1, :lab1
	st r1, :lab2
	st r1, 5000000000
	st r1, -5000000000
	st r1, r16

	add r1, r2, r16
	sub r1, r2, r16

	and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0
		and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0

		and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0

		and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0

		and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0

		and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0

		and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0

		and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0

		and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0

		and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0
	and %0, %0,r1
	and %-5, %-5,r1
	and %5, %5,r1
	and %:lab1, %:lab1,r1
	and %:lab2, %:lab2,r1
	and %5000000000, %5000000000,r1
	and %-5000000000, %-5000000000,r1

	and 0, 0,r1
	and -5, -5,r1
	and 5, 5,r1
	and :lab1, :lab1,r1
	and :lab2, :lab2,r1
	and 5000000000, 5000000000,r1
	and -5000000000, -5000000000,r1	

	and %0, 0,r1
	and %-5, -5,r1
	and %5, 5,r1
	and %:lab1, :lab1,r1
	and %:lab2, :lab2,r1
	and %5000000000, 5000000000,r1
	and %-5000000000, -5000000000,r1

	and 0, %0,r1
	and -5, %-5,r1
	and 5, %5,r1
	and :lab1, :lab1,r1
	and :lab2, %:lab2,r1
	and 5000000000, %5000000000,r1
	and -5000000000, %-5000000000,r1

	ldi %0, %0,r1
	ldi %-5, %0,r1
	ldi %5, %0,r1
	ldi %:lab1, %0,r1
	ldi %:lab2, %0,r1
	ldi %5000000000, %0,r1
	ldi %-5000000000, %0,r1

	ldi 0, %0,r1
	ldi -5, %0,r1
	ldi 5, %0,r1
	ldi :lab1, %0,r1
	ldi :lab2, %0,r1
	ldi 5000000000, %0,r1
	ldi -5000000000, %0,r1

	sti r1, 0, %0
	sti r1, -5, %0
	sti r1, 5, %0
	sti r1, :lab1, %0
	sti r1, :lab2, %0
	sti r1, 5000000000, %0
	sti r1, -5000000000, %0

	sti r1, %0, %0
	sti r1, %-5, %0
	sti r1, %5, %0
	sti r1, %:lab1, %0
	sti r1, %:lab2, %0
	sti r1, %5000000000, %0
	sti r1, %-5000000000, %0

	aff r1

lab2:
	live %:lab1
