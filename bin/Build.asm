;;
;; * Copyright (c) 2010 Saneyuki. All rights reserved.
;;


;;=====   Build Saneos   =========================================================


;;-----   Bootloader   -----------------------------------------------------------
;;--------------------------------------------------------------------------------

        incbin  "starter.sos"						; LBA No.~ (No.~)
        incbin  "bootloader.sos", 0x200				; LBA No.~ (No.~)
        
        times   16384 - ($-$$) db 0
        
        incbin  "system.sfn"						; LBA No.~ (No.~)

align   2048

        incbin  "test_data.sos"						; LBA No.~ (No.~)

;;-----   Database   ------------------------------------------------------------
;;--------------------------------------------------------------------------------

        incbin  "database.sos"						; LBA No.~ (No.~)


;;-----   Installer   ------------------------------------------------------------
;;--------------------------------------------------------------------------------


;;-----   Datas   ----------------------------------------------------------------
;;--------------------------------------------------------------------------------