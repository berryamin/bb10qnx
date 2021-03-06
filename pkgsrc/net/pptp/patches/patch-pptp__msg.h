$NetBSD$

--- pptp_msg.h.orig	2006-02-13 03:07:43.000000000 +0000
+++ pptp_msg.h
@@ -9,6 +9,24 @@
 
 /* Grab definitions of int16, int32, etc. */
 #include <sys/types.h>
+#ifdef __QNXNTO__
+#ifndef _U_INT8_T_DEFINED
+#define _U_INT8_T_DEFINED
+typedef _Uint8t         u_int8_t;
+#endif
+#ifndef _U_INT16_T_DEFINED
+#define _U_INT16_T_DEFINED
+typedef _Uint16t        u_int16_t;
+#endif
+#ifndef _U_INT32_T_DEFINED
+#define _U_INT32_T_DEFINED
+typedef _Uint32t        u_int32_t;
+#endif
+#ifndef _U_INT64_T_DEFINED
+#define _U_INT64_T_DEFINED
+typedef _Uint64t        u_int64_t;
+#endif
+#endif
 /* define "portable" htons, etc. */
 #define hton8(x)  (x)
 #define ntoh8(x)  (x)
