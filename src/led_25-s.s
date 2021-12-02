	.arch msp430g2553
	.p2align 1,0
	
	.text
jt:
	.word default		;jt[0]
	.word case0		;jt[1]
	.word case1		;jt[2]
	.word case2		;jt[3]
	.word case3		;jt[4]

	.global light_25
	.extern P1OUT

light_25:			; s (the selector) is in r12
	cmp #5, r12		; r12 - 5 >= 0 then go to default
	jhs default		; jmp if s > 4
	add r12, r12		; 2*r12 (means 2*selector)
	mov jt(r12), r0		; jmp jt[s]


	;; switch table options
	;; same order as in source code
	
case0:
case1:
case2:
	and.b #~1, &P1OUT	; turn off green LED
	jmp exit		; break
case3:
	bis.b #1, &P1OUT	; turn on green LED

default:
exit:
	pop r0
	
