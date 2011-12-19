;;
;; * Copyright (c) 2010 Saneyuki. All rights reserved.
;;


;;=====   Global functions   =====================================================

[bits   32]

global _LGDT
global _LIDT
global _WriteDataNML
global _WriteDataAND
global _WriteDataOR
global _WriteDataXOR
global _WriteDataNOT
global _GetDataNML
global _InputB
global _InputW
global _InputD
global _OutputB
global _OutputW
global _OutputD
global _HaltProcessor
global _SetIntFlug
global _ClearIntFlug
global _NoOperation
global _ISR
global _Int20Handler

_LGDT:
        mov    edi, [esp+4]
        lgdt   [edi]
        mov    eax, 0xF0F0
        ret
        
_LIDT:
        mov    edi, [esp+4]
        lidt   [edi]
        mov    eax, 0xF0F0
        ret

_WriteDataNML:
        mov    edi, [esp+4]
        mov    edx, [esp+8]
        mov    ebx, [esp+12]
        or     dword [edi], ebx
        xor    dword [edi], ebx
        or     dword [edi], edx
        ret
        
_WriteDataAND:
        mov    edi, [esp+4]
        mov    edx, [esp+8]
        mov    ebx, [esp+12]
        mov    eax, [edi]
        and    eax, ebx
        and    eax, edx
        or     dword [edi], ebx
        xor    dword [edi], ebx
        or     dword [edi], eax
        ret

_WriteDataOR:
        mov    edi, [esp+4]
        mov    edx, [esp+8]
        or     byte [edi], dl
        ret
        
_WriteDataXOR:
        mov    edi, [esp+4]
        mov    edx, [esp+8]
        xor    dword [edi], edx
        ret
        
_WriteDataNOT:
        mov    edi, [esp+4]
        mov    ebx, [esp+8]
        mov    eax, [edi]
        and    eax, ebx
        xor    eax, ebx
        or     dword [edi], ebx
        xor    dword [edi], ebx
        or     dword [edi], eax
        ret
        
_GetDataNML:
        mov    edi, [esp+4]
        mov    ebx, [esp+8]
        mov    eax, [edi]
        and    eax, ebx
        ret

_InputB:
        mov    dx, [esp+4]
        xor    ax, ax
        in     al, dx
        ret
        
_InputW:
        mov    dx, [esp+4]
        xor    ax, ax
        in     ax, dx
        ret
        
_InputD:
        mov    dx, [esp+4]
        xor    eax, eax
        in     eax, dx
        ret

_OutputB:
        mov    dx, [esp+4]
        mov    al, [esp+8]
        out    dx, al
        ret

_OutputW:
        mov    dx, [esp+4]
        mov    ax, [esp+8]
        out    dx, ax
        ret

_OutputD:
        mov    dx, [esp+4]
        mov    eax, [esp+8]
        out    dx, eax
        ret

_HaltProcessor:
        hlt
        ret
        
_SetIntFlug:
        sti
        ret
        
_ClearIntFlug:
        cli
        ret
        
_NoOperation:
        nop
        ret
        
_ISR:
        mov     al, 0x20
        out     0x20, al
        iret
        
_Int20Handler:
        pusha
        push    ds
        push    es
        mov     al, 0x60
        out     0x20, al
        mov     edi, 0x000A0000
        mov     byte [edi], 0xFF
        pop     es
        pop     ds
        popa
        iret