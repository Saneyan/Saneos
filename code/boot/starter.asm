;;
;; * Copyright (c) 2010 Saneyuki. All rights reserved.
;;


;;=====   Bootstrap loader   =====================================================


[bits   16]
[org    0x7C00]


;;
;; struct Drive[256]{
;;     char BootableDrive;
;; };
;;
;; struct VideoMode{
;;     unsigned char VBEControllerInformation[128];
;;     char NumberVBEMode;
;;     unsigned short SupportVBEMode[31];
;;     char SupportVGAMode;
;; };
;;
;; char ErrorFlug;
;;
;; unsigned char VBEModeInformation[7936];
;;

DESegment                   EQU  0x1000

BootableDrive               EQU  0x03EC

VBEControllerInformation    EQU  0x05EC

NumberVBEMode               EQU  0x06EC

SupportVBEMode              EQU  0x06ED

SupportVGAMode              EQU  0x070C

ErrorFlug                   EQU  0x070D

VGAVRAM						EQU  0x07A0

VBEModeInformation          EQU  0x0800


        jmp     0x0000:0x7C05

Start:
        mov     eax, cr0
        cmp     eax, 0x00000001
        je      ProtectModeALRDY
        
        cli
        mov     ax, cs
        mov     ss, ax
        mov     sp, 0x7C00
        mov     ax, DESegment
        mov     ds, ax
        mov     es, ax
        sti
        
        mov     byte [ds:BootableDrive], dl
        
        mov     ax, 0x4F00
        mov     di, VBEControllerInformation
        int     0x10
        
        cmp     ax, 0x004F
        je      NotSupportedVBEMode
        
        mov     bx, 0x0100
        mov     cx, 0x001F
        xor     dx, dx
        mov     di, VBEModeInformation
        mov     si, SupportVBEMode
        
ScanVBEMode_1:
        push    cx
        mov     ax, 0x4F01
        mov     cx, bx
        int     0x10
        
        cmp     ax, 0x004F
        jne     ScanVBEMode_2
        
        inc     dl
        add     di, 0x0100
        
        mov     word [ds:si], bx
        add     si, 0x0002
        
ScanVBEMode_2:
        inc     bx
        pop     cx
        loop    ScanVBEMode_1
        
        cmp     dl, 0x00
        je      NotSupportedVBEMode
        
        mov     byte [ds:NumberVBEMode], dl
        
        jmp     VGAMode
        
NotSupportedVBEMode:
        mov     byte [ds:SupportVGAMode], 0x01
        
VGAMode:
        mov     ax, 0x0012
        int     0x10
        
        mov     dword [ds:VGAVRAM], 0x000A0000

ChangeProtectMode:
        mov     ax, 0x2401
        int     0x15

        cli
        mov     al, 0xFF
        out     0x21, al
        out     0xA1, al
        
        mov     al, 0x11
        out     0x20, al
        out     0xA0, al
        
        mov     al, 0x20
        out     0x21, al
        mov     al, 0x28
        out     0xA1, al
        
        mov     al, 0x04
        out     0x21, al
        mov     al, 0x02
        out     0xA1, al
        
        mov     al, 0x01
        out     0x21, al
        mov     al, 0x01
        out     0xA1, al
        
        mov     al, 0xFB
        out     0x21, al
        mov     al, 0xFF
        out     0xA1, al
        
        mov     ax, cs
        mov     ds, ax
        
        lgdt    [GDTR]
        
        mov     eax, cr0
        or      eax, 0x00000001
        mov     cr0, eax
        
        jmp     ProtectMode

ProtectModeALRDY:
        lgdt    [GDTR]
        
ProtectMode:
        mov     ax, 0x0010
        mov     ds, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax
        mov     ss, ax
        mov     esp, 0x00007C00
        
        jmp     dword  0x0008:0x00008400
        
        
;;-----   GDT (GDTR)   -----------------------------------------------------------
;;--------------------------------------------------------------------------------

align   8

GDTR:											;; Set GDTR
        dw      GDTEnd - GDT - 1				; GDT limit
        dd      GDT								; GDT address

align   8

GDT:											;; Set GDT
NullSelector:									;; Null selector
        dw      0x0000							; Low limit
        dw      0x0000							; Low base
        db      0x00							; Middle base
        db      0x00							; 0-00-0-000-0 (P-DPL-S-Type-A)
        db      0x00							; 0-0-0-0-0000 (G-D-RES-AVL-HLimit)
        db      0x00							; High base
        
CodeSegment:									;; Set up code segment
        dw      0xFFFF							; 1111 1111 1111 1111
        dw      0x0000							; 0000 0000 0000 0000
        db      0x00							; 0000 0000
        db      0x9A							; 1001 1010 (1-00-1-101-0)
        db      0xDF							; 1101 1111 (1-1-0-1-1111)
        db      0x00							; 0000 0000

DataSegment:									;; Set up data segment
        dw      0xFFFF							; 1111 1111 1111 1111
        dw      0x0000							; 0000 0000 0000 0000
        db      0x00							; 0000 0000
        db      0x92							; 1001 0010 (1-00-1-001-0)
        db      0xDF							; 1101 1111 (1-1-0-1-1111)
        db      0x00							; 0000 0000
GDTEnd:											;; GDT end

        times   2048 - ($-$$) db 0