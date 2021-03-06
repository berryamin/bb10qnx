$NetBSD: patch-gcc-gcc_config_h8300_h8300.c,v 1.1 2013/04/30 13:26:35 ryoon Exp $

* Fix build on 64bit platform.
  From http://gcc.gnu.org/ml/gcc-patches/2006-10/msg00337.html

--- gcc/config/h8300/h8300.c.orig	2004-02-09 17:25:35.000000000 +0000
+++ gcc/config/h8300/h8300.c
@@ -52,8 +52,8 @@ static int h8300_interrupt_function_p (t
 static int h8300_saveall_function_p (tree);
 static int h8300_monitor_function_p (tree);
 static int h8300_os_task_function_p (tree);
-static void h8300_emit_stack_adjustment (int, unsigned int);
-static int round_frame_size (int);
+static void h8300_emit_stack_adjustment (int, HOST_WIDE_INT);
+static HOST_WIDE_INT round_frame_size (HOST_WIDE_INT);
 static unsigned int compute_saved_regs (void);
 static void push (int);
 static void pop (int);
@@ -368,7 +368,7 @@ byte_reg (rtx x, int b)
    SIZE to adjust the stack pointer.  */
 
 static void
-h8300_emit_stack_adjustment (int sign, unsigned int size)
+h8300_emit_stack_adjustment (int sign, HOST_WIDE_INT size)
 {
   /* H8/300 cannot add/subtract a large constant with a single
      instruction.  If a temporary register is available, load the
@@ -397,8 +397,8 @@ h8300_emit_stack_adjustment (int sign, u
 
 /* Round up frame size SIZE.  */
 
-static int
-round_frame_size (int size)
+static HOST_WIDE_INT
+round_frame_size (HOST_WIDE_INT size)
 {
   return ((size + STACK_BOUNDARY / BITS_PER_UNIT - 1)
 	  & -STACK_BOUNDARY / BITS_PER_UNIT);
