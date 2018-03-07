#deassembler par msa 1.8, made by joe
.name "Tching tching(Intercepteur), Bouh!Bouh!(bruits d'anti-jeu)"
.comment ""

	 fork  %:label00          		# 3,0,281
	 ld    %-272,r3           		
	 live  %0                 		
	 fork  %:label01       #test  
	 ld    %-272,r3         #test
	 fork  %:label02          #test
	 ld    %0,r2              #test
	 ld    %0,r4              	#test
	 zjmp  %:label03          		#test
			
label02: ld    %4,r2              	#test
	 ld    %0,r4              		#test
	 zjmp  %:label03          	#test

label01: ld    %-202,r3           #test
	 fork  %:label04          		#test
	 ld    %0,r2              	#test
	 ld    %0,r4              	#test
	 zjmp  %:label05          		#test

label04: ld    %4,r2              	#test
	 ld    %0,r4              		#test
	 zjmp  %:label05          		#test

label00: ld    %400,r3            	#test
	 live  %0                 	#test
	 fork  %:label06          	#test
	 fork  %:label07          #test
	 ld    %0,r2              		#test
	 ld    %0,r4              	#test
	 zjmp  %:label08          	#test

label07: ld    %4,r2              	#test	
	 ld    %0,r4              	#test
	 zjmp  %:label08          		#test

label06: fork  %:label09          #test
	 ld    %0,r4              		#test
	 zjmp  %:label10          		#test

label09: ld    %0,r4              #test
	 zjmp  %:label11          	#test

label03: ldi   r2,%:label12,r6    		#test
	 ld    %0,r4              	#test
	 live  %1             #test

label12: sti   r6,r2,r3         #test
	 zjmp  %-277              	#test

label08: ldi   r2,%:label13,r6    	#test
	 ld    %0,r4              	#test
	 live  %1                 	#test

label13: sti   r6,r2,r3           #test
	 zjmp  %395               	#test

label05: ldi   r2,%:label14,r6    	#test	
	 ld    %0,r4              		#test
	 live  %1                 	#test

label14: sti   r6,r2,r3           	#test
	 zjmp  %-207             #test

label10: live  %1                 #test
	 fork  %:label10          	#test
	 zjmp  %:label10          	#test

label11: live  %1                 	#test
	 fork  %:label11          #test
	 zjmp  %:label11       #test
