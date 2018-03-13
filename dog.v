0:	.name "Tching tching(Intercepteur), Bouh!Bouh!(bruits d'anti-jeu)"
0:	.comment "abcdefgh"

0:	
label_1:	ld %4,r2
7:	ld %0,r4
14:	zjmp %:label_1
17:	ld %-202,r3
24:	ld %-272,r3
31:	fork %:label_2
34:	live %0
39:	fork %:label_3
42:	ld %-272,r3
49:	fork %:label_1
52:	ld %0,r2
59:	ld %0,r4
66:	zjmp %:label_4
69:	
label_3:	ld %-202,r3
76:	fork %:label_5
79:	ld %0,r2
86:	ld %0,r4
93:	zjmp %:label_6
96:	
label_5:	ld %4,r2
103:	ld %0,r4
110:	zjmp %:label_6
113:	
label_2:	ld %-112,r3
120:	live %0
125:	fork %:label_7
128:	fork %:label_8
131:	ld %0,r2
138:	ld %0,r4
145:	zjmp %:label_9
148:	
label_8:	ld %4,r2
155:	ld %0,r4
162:	zjmp %:label_9
165:	
label_7:	fork %13
168:	ld %0,r4
175:	zjmp %:label_10
178:	ld %0,r4
185:	zjmp %:label_11
188:	
label_4:	ldi r2,%18,r6
194:	ld %0,r4
201:	live %1
206:	sti r6,r2,r3
211:	zjmp %-277
214:	
label_9:	ldi r2,%18,r6
220:	ld %0,r4
227:	live %1
232:	sti r6,r2,r3
237:	zjmp %395
240:	
label_6:	ldi r2,%18,r6
246:	ld %0,r4
253:	live %1
258:	sti r6,r2,r3
263:	zjmp %-207
266:	
label_10:	live %1
271:	fork %:label_10
274:	zjmp %:label_10
277:	
label_11:	live %1
282:	fork %:label_11
285:	zjmp %:label_11
