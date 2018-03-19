.name "Tching tching(Intercepteur), Bouh!Bouh!(bruits d'anti-jeu)"
.comment ""


fork %:label_1
ld %-272,r3
live %0
fork %:label_2
ld %-272,r3
fork %:label_3
ld %0,r2
ld %0,r4
zjmp %:label_4

label_3:	ld %4,r2
ld %0,r4
zjmp %:label_4

label_2:	ld %-202,r3
fork %:label_5
ld %0,r2
ld %0,r4
label_2:
zjmp %:label_6

label_5:	ld %4,r2
ld %0,r4
zjmp %:label_6

label_1:	ld %144,r3
live %0
fork %:label_7
fork %:label_8
ld %0,r2
ld %0,r4
zjmp %:label_9

label_8:	ld %4,r2
ld %0,r4
zjmp %:label_9

label_7:	fork %13
ld %0,r4
zjmp %:label_10
ld %0,r4
zjmp %:label_11

label_4:	ldi r2,%18,r6
ld %0,r4
live %1
sti r6,r2,r3
zjmp %-277

label_9:	ldi r2,%18,r6
ld %0,r4
live %1
sti r6,r2,r3
zjmp %395

label_6:	ldi r2,%18,r6
ld %0,r4
live %1
sti r6,r2,r3
zjmp %-207

label_10:	live %1
fork %:label_10
zjmp %:label_10

label_11:	live %1
fork %:label_11
zjmp %:label_11
