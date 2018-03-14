32767:	.name "Tching tching(Intercepteur), Bouh!Bouh!(bruits d'anti-jeu)"
0:	.comment ""

0:	fork %:label_1
3:	ld %-272,r3
10:	live %0
15:	fork %:label_2
18:	ld %-272,r3
25:	fork %:label_3
28:	ld %0,r2
35:	ld %0,r4
42:	zjmp %:label_4
45:	
label_3:	ld %4,r2
52:	ld %0,r4
59:	zjmp %:label_4
62:	
label_2:	ld %-202,r3
69:	fork %:label_5
72:	ld %0,r2
79:	ld %0,r4
86:	zjmp %:label_6
89:	
label_5:	ld %4,r2
96:	ld %0,r4
103:	zjmp %:label_6
106:	
label_1:	ld %144,r3
113:	live %0
118:	fork %:label_7
121:	fork %:label_8
124:	ld %0,r2
131:	ld %0,r4
138:	zjmp %:label_9
141:	
label_8:	ld %4,r2
148:	ld %0,r4
155:	zjmp %:label_9
158:	
label_7:	fork %13
161:	ld %0,r4
168:	zjmp %:label_10
171:	ld %0,r4
178:	zjmp %:label_11
181:	
label_4:	ldi r2,%18,r6
187:	ld %0,r4
194:	live %1
199:	sti r6,r2,r3
204:	zjmp %-277
207:	
label_9:	ldi r2,%18,r6
213:	ld %0,r4
220:	live %1
225:	sti r6,r2,r3
230:	zjmp %395
233:	
label_6:	ldi r2,%18,r6
239:	ld %0,r4
246:	live %1
251:	sti r6,r2,r3
256:	zjmp %-207
259:	
label_10:	live %1
264:	fork %:label_10
267:	zjmp %:label_10
270:	
label_11:	live %1
275:	fork %:label_11
278:	zjmp %:label_11
