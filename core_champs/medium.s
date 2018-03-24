.name           "Medium"
.comment        "gavgav_in_da_bocal"
	
	sti	r1,%:live,%1
live:	
	live	%1
	ld %57672193, r2

	st r2, 500
	st r2, 431
	st r2, 362
	st r2, 293

	st r2, 493
	st r2, 424
	st r2, 355
	st r2, 286

	st r2, 493
	st r2, 424
	st r2, 355
	st r2, 286

	xor		r5, r5, r5
	fork 	%150
	xor		r5, r5, r5
	zjmp	%:live

