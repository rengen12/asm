.name           "Zork_reaper"
.comment        "gavgav_in_da_bocal"
	
	sti	r1,%:live,%1
live:	
	live	%1
	ld %57672193, r2

	st r2, 493
	st r2, 424
	st r2, 355
	st r2, 286

	st r2, 478
	st r2, 409
	st r2, 340
	st r2, 271

	st r2, 463
	st r2, 394
	st r2, 325
	st r2, 256

	st r2, 448
	st r2, 379
	st r2, 310
	st r2, 241

	st r2, 433
	st r2, 364
	st r2, 295
	st r2, 226

	st r2, 418
	st r2, 349
	st r2, 280
	st r2, 211

	st r2, 403
	st r2, 334
	st r2, 265
	st r2, 196

	st r2, 388
	st r2, 319
	st r2, 250
	st r2, 181

	st r2, 373
	st r2, 304
	st r2, 235
	st r2, 166

	st r2, 358
	st r2, 289
	st r2, 220
	st r2, 151

	st r2, 343
	st r2, 274
	st r2, 205
	st r2, 136

	st r2, 328
	st r2, 259
	st r2, 190
	st r2, 121

	xor		r5, r5, r5
	fork 	%50
	xor		r5, r5, r5
	zjmp	%:live

