section .text
    global _start  ; 프로그램의 시작점을 _start로 설정

_start:
    ; 부트로더의 코드를 작성합니다.
    
    ; 부트로더는 메모리에 로드될 때, 16비트 실주소(segment offset pair) CS:IP를 0x7C00으로 설정합니다.
    xor ax, ax     ; AX 레지스터를 0으로 초기화
    mov ds, ax     ; DS 레지스터를 0으로 초기화
    mov es, ax     ; ES 레지스터를 0으로 초기화
    
    ; kernel.bin을 로드하기 위해 BIOS의 디스크 읽기 기능 호출
    mov ah, 0x02   ; 디스크 읽기 BIOS 인터럽트 번호
    mov al, 1      ; 읽을 섹터 수 (1개의 섹터만 읽음)
    mov ch, 0      ; 실린더 번호
    mov dh, 0      ; 헤드 번호
    mov cl, 2      ; 섹터 번호 (kernel.bin이 0x000200에 위치한다고 가정)
    mov bx, 0x8000 ; 읽을 위치 (0x8000 이후에 kernel.bin을 로드할 것으로 가정)
    int 0x13       ; BIOS 인터럽트를 호출하여 디스크에서 데이터를 읽음
    
    ; kernel.bin의 로드가 실패하면 여기서 프로그램을 멈춤
    jc halt
    
    ; kernel.bin을 메모리에 로드한 후에 실행
    mov si, 0x8000 ; kernel.bin이 로드된 메모리 위치
    call si        ; kernel.bin의 시작 지점을 호출
    
halt:
    hlt            ; 프로그램을 정지시킴
