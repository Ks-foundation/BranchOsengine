ORG 0x7C00

MOV AX, 0x1000      ; 세그먼트 레지스터에 0x1000을 로드하여 kernel.bin을 로드할 메모리 위치를 지정
MOV DS, AX
MOV SI, 0           ; SI 레지스터에 0을 로드하여 로드할 위치를 지정

LOAD_KERNEL:
    MOV AH, 02h     ; 디스크에서 섹터를 읽기 위한 BIOS 서비스 호출
    MOV AL, 1       ; 읽을 섹터 수
    MOV CH, 0       ; 실린더 번호
    MOV CL, 2       ; 섹터 번호 (0-based, 1번 섹터)
    MOV DH, 0       ; 헤드 번호
    INT 13h         ; BIOS 호출
    JC LOAD_KERNEL  ; 에러 발생 시 재시도

MOV AX, 0x1000      ; 세그먼트 레지스터에 0x1000을 로드하여 shell.bin을 로드할 메모리 위치를 지정
MOV DS, AX
MOV SI, 0           ; SI 레지스터에 0을 로드하여 로드할 위치를 지정

LOAD_SHELL:
    MOV AH, 02h     ; 디스크에서 섹터를 읽기 위한 BIOS 서비스 호출
    MOV AL, 1       ; 읽을 섹터 수
    MOV CH, 0       ; 실린더 번호
    MOV CL, 3       ; 섹터 번호 (0-based, 2번 섹터)
    MOV DH, 0       ; 헤드 번호
    INT 13h         ; BIOS 호출
    JC LOAD_SHELL   ; 에러 발생 시 재시도

MOV AX, 0x1000      ; kernel.bin의 메모리 위치를 로드
MOV DS, AX
CALL 0x1000         ; kernel.bin 실행

MOV AX, 0x1000      ; shell.bin의 메모리 위치를 로드
MOV DS, AX
CALL 0x1000         ; shell.bin 실행

JMP $               ; 무한 루프
TIMES 510 - ($ - $$) DB 0 ; 부트로더를 512바이트로 채우기 위한 더미
DW 0xAA55               ; 부트로더 서명
