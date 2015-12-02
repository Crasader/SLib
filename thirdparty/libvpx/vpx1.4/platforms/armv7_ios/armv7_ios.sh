as -arch armv7 -o asm/obj/bilinearfilter_v6.obj asm/bilinearfilter_v6.asm.s
as -arch armv7 -o asm/obj/copymem8x4_v6.obj asm/copymem8x4_v6.asm.s
as -arch armv7 -o asm/obj/copymem8x8_v6.obj asm/copymem8x8_v6.asm.s
as -arch armv7 -o asm/obj/copymem16x16_v6.obj asm/copymem16x16_v6.asm.s
as -arch armv7 -o asm/obj/dc_only_idct_add_v6.obj asm/dc_only_idct_add_v6.asm.s
as -arch armv7 -o asm/obj/dequant_idct_v6.obj asm/dequant_idct_v6.asm.s
as -arch armv7 -o asm/obj/dequantize_v6.obj asm/dequantize_v6.asm.s
as -arch armv7 -o asm/obj/filter_v6.obj asm/filter_v6.asm.s
as -arch armv7 -o asm/obj/idct_v6.obj asm/idct_v6.asm.s
as -arch armv7 -o asm/obj/intra4x4_predict_v6.obj asm/intra4x4_predict_v6.asm.s
as -arch armv7 -o asm/obj/iwalsh_v6.obj asm/iwalsh_v6.asm.s
as -arch armv7 -o asm/obj/loopfilter_v6.obj asm/loopfilter_v6.asm.s
as -arch armv7 -o asm/obj/simpleloopfilter_v6.obj asm/simpleloopfilter_v6.asm.s
as -arch armv7 -o asm/obj/sixtappredict8x4_v6.obj asm/sixtappredict8x4_v6.asm.s
as -arch armv7 -o asm/obj/vp8_mse16x16_armv6.obj asm/vp8_mse16x16_armv6.asm.s
as -arch armv7 -o asm/obj/vp8_sad16x16_armv6.obj asm/vp8_sad16x16_armv6.asm.s
as -arch armv7 -o asm/obj/vp8_short_fdct4x4_armv6.obj asm/vp8_short_fdct4x4_armv6.asm.s
as -arch armv7 -o asm/obj/vp8_variance_halfpixvar16x16_h_armv6.obj asm/vp8_variance_halfpixvar16x16_h_armv6.asm.s
as -arch armv7 -o asm/obj/vp8_variance_halfpixvar16x16_hv_armv6.obj asm/vp8_variance_halfpixvar16x16_hv_armv6.asm.s
as -arch armv7 -o asm/obj/vp8_variance_halfpixvar16x16_v_armv6.obj asm/vp8_variance_halfpixvar16x16_v_armv6.asm.s
as -arch armv7 -o asm/obj/vp8_variance8x8_armv6.obj asm/vp8_variance8x8_armv6.asm.s
as -arch armv7 -o asm/obj/vp8_variance16x16_armv6.obj asm/vp8_variance16x16_armv6.asm.s
as -arch armv7 -o asm/obj/walsh_v6.obj asm/walsh_v6.asm.s
ar rc libvpx_asm_armv7.a "asm/obj/bilinearfilter_v6.obj" "asm/obj/copymem8x4_v6.obj" "asm/obj/copymem8x8_v6.obj" "asm/obj/copymem16x16_v6.obj" "asm/obj/dc_only_idct_add_v6.obj" "asm/obj/dequant_idct_v6.obj" "asm/obj/dequantize_v6.obj" "asm/obj/filter_v6.obj" "asm/obj/idct_v6.obj" "asm/obj/intra4x4_predict_v6.obj" "asm/obj/iwalsh_v6.obj" "asm/obj/loopfilter_v6.obj" "asm/obj/simpleloopfilter_v6.obj" "asm/obj/sixtappredict8x4_v6.obj" "asm/obj/vp8_mse16x16_armv6.obj" "asm/obj/vp8_sad16x16_armv6.obj" "asm/obj/vp8_short_fdct4x4_armv6.obj" "asm/obj/vp8_variance_halfpixvar16x16_h_armv6.obj" "asm/obj/vp8_variance_halfpixvar16x16_hv_armv6.obj" "asm/obj/vp8_variance_halfpixvar16x16_v_armv6.obj" "asm/obj/vp8_variance8x8_armv6.obj" "asm/obj/vp8_variance16x16_armv6.obj" "asm/obj/walsh_v6.obj"