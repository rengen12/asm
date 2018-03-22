#debut du mega truc qu'il est trop dur a faire

.name "Jumper !"
.comment "en fait C forker !"

gobepc:	st r1,:buff
	st r6,-4
	ld :buff,r1
debut:	ld %0,r7
	zjmp %:suite

goboucle0:	live %66
		ldi %-5,r3,r1
		sti r1,%-173,r3
		add r3,r4,r3
		xor r5,r3,r6
		zjmp %:finboucle0
		ld %0,r7
		zjmp %:goboucle0
finboucle0:	xor r3,r3,r3
		zjmp %-207

buff:	st r1,r1	
		
suite:	sti r1,%:livel,%1
livel:	live %66
	sti r2,%:debut,%-60
	ld %4,r4
	st r2,512
go:	ld %48,r5
	sti r1,%:goboucle0,%1
	sti r1,%:goboucle1,%1
	sti r1,%:live0,%1
	sti r1,%:live1,%1
	sti r1,%:live2,%1
	sti r1,%:live3,%1
	sti r1,%:live4,%1
live0:	live %66
live1:	live %66
live2:	live %66
live3:	live %66
live4:	live %66
	zjmp %:live0
	xor r3,r3,r3
	sti r1,%:livex,%1
livex:	live %66
	fork %:live0
	sti r1,%:boucle,%1
	sti r1,%:boucle,%9
	sti r1,%:boucle,%17
	sti r1,%:boucle,%25
	
boucle:	live %66
	fork %:goboucle0
	live %66
	fork %:boucle
	live %66
	fork %:goboucle1
	live %66
	zjmp %:goboucle0
goboucle1:	live %66
		ldi %-5,r3,r1
		sti r1,%17,r3
		add r3,r4,r3
		xor r5,r3,r6
		zjmp %:finboucle1
		ld %0,r7
		zjmp %:goboucle1
finboucle1:	xor r3,r3,r3
		zjmp %1
  		# 7,124,157
	 ld    %0,r4              		# 7,131,150
	 zjmp  %:label08          		# 3,138,143

label07: ld    %4,r2              		# 7,141,140
	 ld    %0,r4              		# 7,148,133
	 zjmp  %:label08          		# 3,155,126

label06: fork  %:label09          		# 3,158,123
	 ld    %0,r4              		# 7,161,120
	 zjmp  %:label10          		# 3,168,113

label09: ld    %0,r4              		# 7,171,110
	 zjmp  %:label11          		# 3,178,103

label03: ldi   r2,%:label12,r6    		# 6,181,100
	 ld    %0,r4              		# 7,187,94
	 live  %1                 		# 5,194,87

label12: sti   r6,r2,r3           		# 5,199,82
	 zjmp  %-277              		# 3,204,77

label08: ldi   r2,%:label13,r6    		# 6,207,74
	 ld    %0,r4              		# 7,213,68
	 live  %1                 		# 5,220,61

label13: sti   r6,r2,r3           		# 5,225,56
	 zjmp  %395               		# 3,230,51

label05: ldi   r2,%:label14,r6    		# 6,233,48
	 ld    %0,r4              		# 7,239,42
	 live  %1                 		# 5,246,35

label14: sti   r6,r2,r3           		# 5,251,30
	 zjmp  %-207              		# 3,256,25

label10: live  %1                 		# 5,259,22
	 fork  %:label10          		# 3,264,17
	 zjmp  %:label10          		# 3,267,14

label11: live  %1                 		# 5,270,11
	 fork  %:label11          		# 3,275,6
	 zjmp  %:label11          		# 3,278,3
