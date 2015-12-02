"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/temporal_filter_apply_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/emms.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/dequantize_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/idctllm_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/iwalsh_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/loopfilter_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/recon_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/sad_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/subpixel_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/variance_impl_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/idctllm_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/recon_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/sad_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/subpixel_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/loopfilter_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/iwalsh_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/variance_impl_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/sad_sse3.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/sad_ssse3.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/subpixel_ssse3.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/variance_impl_ssse3.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/sad_sse4.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/postproc_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/mfqe_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/postproc_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/dct_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/subtract_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/dct_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/fwalsh_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/subtract_sse2.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/quantize_mmx.asm" -o "./asm/obj/"
"./asm/yasm/vsyasm.exe" -Xvc -f win32  -I"." "./asm/encodeopt.asm" -o "./asm/obj/"
lib /OUT:"libvpx_asm_x86.lib" /machine:x86 "asm/obj/*.obj"