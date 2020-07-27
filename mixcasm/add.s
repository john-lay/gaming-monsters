.globl _add
    _add:         ; WORD add(WORD a, WORD b)
                  ; There is no register to save:
                  ;  BC is not used
                  ;  DE is the return register
                  ;  HL needs never to be saved
    LDA  HL,2(SP)
    LD   E,(HL)   ; Get a in DE
    INC  HL
    LD   D,(HL)
    INC  HL
    LD   A,(HL)   ; Get b in HL
    INC  HL
    LD   H,(HL)
    LD   L,A
    ADD  HL,DE    ; Add DE to HL
    LD   D,H
    LD   E,L
                  ; There is no register to restore
    RET           ; Return result in DE
