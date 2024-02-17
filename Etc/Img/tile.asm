; Tile.asm

; 이 함수는 메모리에 타일 형식의 이미지를 출력합니다.
; 인자:
;   - source: 이미지 데이터가 저장된 위치
;   - destination: 출력할 메모리 위치
;   - width: 이미지의 너비
;   - height: 이미지의 높이
;   - tileWidth: 타일의 너비
;   - tileHeight: 타일의 높이
PrintTileImage:
    PUSH    BP             ; BP 레지스터를 스택에 저장
    MOV     BP, SP         ; 스택 포인터를 BP 레지스터에 복사

    PUSH    SI             ; SI 레지스터를 스택에 저장
    PUSH    DI             ; DI 레지스터를 스택에 저장

    MOV     SI, [BP+4]     ; 소스 위치를 SI 레지스터에 로드
    MOV     DI, [BP+6]     ; 대상 위치를 DI 레지스터에 로드
    MOV     CX, [BP+8]     ; 이미지의 너비를 CX 레지스터에 로드
    MOV     DX, [BP+10]    ; 이미지의 높이를 DX 레지스터에 로드
    MOV     BX, [BP+12]    ; 타일의 너비를 BX 레지스터에 로드
    MOV     AX, [BP+14]    ; 타일의 높이를 AX 레지스터에 로드

    MOV     BP, 0          ; BP 레지스터를 0으로 초기화

PrintTileLoop:
    PUSH    CX             ; 레지스터 값을 스택에 저장
    PUSH    DX             ; 레지스터 값을 스택에 저장

    MOV     CX, BX         ; 타일의 너비를 CX 레지스터에 로드
    MOV     DX, AX         ; 타일의 높이를 DX 레지스터에 로드

    REP     MOVSB          ; 타일 복사

    POP     DX             ; 스택에서 레지스터 값을 복원
    POP     CX             ; 스택에서 레지스터 값을 복원

    ADD     DI, BX         ; 다음 타일로 이동
    ADD     BP, BX         ; 다음 타일로 이동

    CMP     BP, CX         ; 이미지의 한 줄이 끝났는지 확인
    JL      PrintTileLoop  ; 만약 더 출력할 줄이 있다면 반복

    POP     DI             ; DI 레지스터 값을 스택에서 복원
    POP     SI             ; SI 레지스터 값을 스택에서 복원

    POP     BP             ; BP 레지스터 값을 스택에서 복원
    RET                    ; 함수 종료
