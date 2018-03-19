.name           "42"
.comment        "Just a basic Winner Program"

lab1:	
	live %0
	live %-5
	live %5
	live %:lab1
	live %:lab2
	live %5000000000
	live %-5000000000
	
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

lab2:
	live %:lab1
