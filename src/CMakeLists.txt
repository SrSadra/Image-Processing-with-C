#cmake_minimum_required(VERSION 3.26)
#project(src)
#
#set(CMAKE_CXX_STANDARD 14)
#
#set(GCC_COVERAGE_COMPILE_FLAGS "-lws2_32")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
#
#include_directories(.)
#include_directories(Effects)
#include_directories(lib)
#include_directories(lib/jpeg-6b)
#include_directories(lib/jpeg-9e-h2bbff1b_1)
#include_directories(lib/jpeg-9e-h2bbff1b_1/Library)
#include_directories(lib/jpeg-9e-h2bbff1b_1/Library/include)
#include_directories(lib/lpng1639)
#include_directories(lib/lpng1639/contrib/pngminim/decoder)
#include_directories(lib/lpng1639/contrib/pngminim/encoder)
#include_directories(lib/lpng1639/contrib/pngminim/preader)
#include_directories(lib/write)
#
#add_executable(src
#        Effects/Color.c
#        Effects/Color.h
#        Effects/Noise.c
#        Effects/Noise.h
#        Effects/Redeye.c
#        lib/jpeg-6b/ansi2knr.c
#        lib/jpeg-6b/cderror.h
#        lib/jpeg-6b/cdjpeg.c
#        lib/jpeg-6b/cdjpeg.h
#        lib/jpeg-6b/cjpeg.c
#        lib/jpeg-6b/ckconfig.c
#        lib/jpeg-6b/djpeg.c
#        lib/jpeg-6b/example.c
#        lib/jpeg-6b/jcapimin.c
#        lib/jpeg-6b/jcapistd.c
#        lib/jpeg-6b/jccoefct.c
#        lib/jpeg-6b/jccolor.c
#        lib/jpeg-6b/jcdctmgr.c
#        lib/jpeg-6b/jchuff.c
#        lib/jpeg-6b/jchuff.h
#        lib/jpeg-6b/jcinit.c
#        lib/jpeg-6b/jcmainct.c
#        lib/jpeg-6b/jcmarker.c
#        lib/jpeg-6b/jcmaster.c
#        lib/jpeg-6b/jcomapi.c
#        lib/jpeg-6b/jcparam.c
#        lib/jpeg-6b/jcphuff.c
#        lib/jpeg-6b/jcprepct.c
#        lib/jpeg-6b/jcsample.c
#        lib/jpeg-6b/jctrans.c
#        lib/jpeg-6b/jdapimin.c
#        lib/jpeg-6b/jdapistd.c
#        lib/jpeg-6b/jdatadst.c
#        lib/jpeg-6b/jdatasrc.c
#        lib/jpeg-6b/jdcoefct.c
#        lib/jpeg-6b/jdcolor.c
#        lib/jpeg-6b/jdct.h
#        lib/jpeg-6b/jddctmgr.c
#        lib/jpeg-6b/jdhuff.c
#        lib/jpeg-6b/jdhuff.h
#        lib/jpeg-6b/jdinput.c
#        lib/jpeg-6b/jdmainct.c
#        lib/jpeg-6b/jdmarker.c
#        lib/jpeg-6b/jdmaster.c
#        lib/jpeg-6b/jdmerge.c
#        lib/jpeg-6b/jdphuff.c
#        lib/jpeg-6b/jdpostct.c
#        lib/jpeg-6b/jdsample.c
#        lib/jpeg-6b/jdtrans.c
#        lib/jpeg-6b/jerror.c
#        lib/jpeg-6b/jerror.h
#        lib/jpeg-6b/jfdctflt.c
#        lib/jpeg-6b/jfdctfst.c
#        lib/jpeg-6b/jfdctint.c
#        lib/jpeg-6b/jidctflt.c
#        lib/jpeg-6b/jidctfst.c
#        lib/jpeg-6b/jidctint.c
#        lib/jpeg-6b/jidctred.c
#        lib/jpeg-6b/jinclude.h
#        lib/jpeg-6b/jmemansi.c
#        lib/jpeg-6b/jmemdos.c
#        lib/jpeg-6b/jmemmac.c
#        lib/jpeg-6b/jmemmgr.c
#        lib/jpeg-6b/jmemname.c
#        lib/jpeg-6b/jmemnobs.c
#        lib/jpeg-6b/jmemsys.h
#        lib/jpeg-6b/jmorecfg.h
#        lib/jpeg-6b/jpegint.h
#        lib/jpeg-6b/jpeglib.h
#        lib/jpeg-6b/jpegtran.c
#        lib/jpeg-6b/jquant1.c
#        lib/jpeg-6b/jquant2.c
#        lib/jpeg-6b/jutils.c
#        lib/jpeg-6b/jversion.h
#        lib/jpeg-6b/rdbmp.c
#        lib/jpeg-6b/rdcolmap.c
#        lib/jpeg-6b/rdgif.c
#        lib/jpeg-6b/rdjpgcom.c
#        lib/jpeg-6b/rdppm.c
#        lib/jpeg-6b/rdrle.c
#        lib/jpeg-6b/rdswitch.c
#        lib/jpeg-6b/rdtarga.c
#        lib/jpeg-6b/transupp.c
#        lib/jpeg-6b/transupp.h
#        lib/jpeg-6b/wrbmp.c
#        lib/jpeg-6b/wrgif.c
#        lib/jpeg-6b/wrjpgcom.c
#        lib/jpeg-6b/wrppm.c
#        lib/jpeg-6b/wrrle.c
#        lib/jpeg-6b/wrtarga.c
#        lib/jpeg-9e-h2bbff1b_1/Library/include/jconfig.h
#        lib/jpeg-9e-h2bbff1b_1/Library/include/jerror.h
#        lib/jpeg-9e-h2bbff1b_1/Library/include/jmorecfg.h
#        lib/jpeg-9e-h2bbff1b_1/Library/include/jpegint.h
#        lib/jpeg-9e-h2bbff1b_1/Library/include/jpeglib.h
#        lib/lpng1639/arm/arm_init.c
#        lib/lpng1639/arm/filter_neon_intrinsics.c
#        lib/lpng1639/arm/palette_neon_intrinsics.c
#        lib/lpng1639/contrib/arm-neon/android-ndk.c
#        lib/lpng1639/contrib/arm-neon/linux-auxv.c
#        lib/lpng1639/contrib/arm-neon/linux.c
#        lib/lpng1639/contrib/examples/iccfrompng.c
#        lib/lpng1639/contrib/examples/pngpixel.c
#        lib/lpng1639/contrib/examples/pngtopng.c
#        lib/lpng1639/contrib/examples/simpleover.c
#        lib/lpng1639/contrib/gregbook/readpng.c
#        lib/lpng1639/contrib/gregbook/readpng.h
#        lib/lpng1639/contrib/gregbook/readpng2.c
#        lib/lpng1639/contrib/gregbook/readpng2.h
#        lib/lpng1639/contrib/gregbook/readppm.c
#        lib/lpng1639/contrib/gregbook/rpng-win.c
#        lib/lpng1639/contrib/gregbook/rpng-x.c
#        lib/lpng1639/contrib/gregbook/rpng2-win.c
#        lib/lpng1639/contrib/gregbook/rpng2-x.c
#        lib/lpng1639/contrib/gregbook/wpng.c
#        lib/lpng1639/contrib/gregbook/writepng.c
#        lib/lpng1639/contrib/gregbook/writepng.h
#        lib/lpng1639/contrib/libtests/fakepng.c
#        lib/lpng1639/contrib/libtests/makepng.c
#        lib/lpng1639/contrib/libtests/pngimage.c
#        lib/lpng1639/contrib/libtests/pngstest-errors.h
#        lib/lpng1639/contrib/libtests/pngstest.c
#        lib/lpng1639/contrib/libtests/pngunknown.c
#        lib/lpng1639/contrib/libtests/pngvalid.c
#        lib/lpng1639/contrib/libtests/readpng.c
#        lib/lpng1639/contrib/libtests/tarith.c
#        lib/lpng1639/contrib/libtests/timepng.c
#        lib/lpng1639/contrib/mips-msa/linux.c
#        lib/lpng1639/contrib/oss-fuzz/libpng_read_fuzzer.cc
#        lib/lpng1639/contrib/pngminim/decoder/pngusr.h
#        lib/lpng1639/contrib/pngminim/encoder/pngusr.h
#        lib/lpng1639/contrib/pngminim/preader/pngusr.h
#        lib/lpng1639/contrib/pngminus/png2pnm.c
#        lib/lpng1639/contrib/pngminus/pnm2png.c
#        lib/lpng1639/contrib/powerpc-vsx/linux.c
#        lib/lpng1639/contrib/powerpc-vsx/linux_aux.c
#        lib/lpng1639/contrib/tools/checksum-icc.c
#        lib/lpng1639/contrib/tools/cvtcolor.c
#        lib/lpng1639/contrib/tools/genpng.c
#        lib/lpng1639/contrib/tools/makesRGB.c
#        lib/lpng1639/contrib/tools/png-fix-itxt.c
#        lib/lpng1639/contrib/tools/pngcp.c
#        lib/lpng1639/contrib/tools/pngfix.c
#        lib/lpng1639/contrib/tools/sRGB.h
#        lib/lpng1639/contrib/visupng/cexcept.h
#        lib/lpng1639/contrib/visupng/PngFile.c
#        lib/lpng1639/contrib/visupng/PngFile.h
#        lib/lpng1639/contrib/visupng/resource.h
#        lib/lpng1639/contrib/visupng/VisualPng.c
#        lib/lpng1639/intel/filter_sse2_intrinsics.c
#        lib/lpng1639/intel/intel_init.c
#        lib/lpng1639/mips/filter_msa_intrinsics.c
#        lib/lpng1639/mips/mips_init.c
#        lib/lpng1639/powerpc/filter_vsx_intrinsics.c
#        lib/lpng1639/powerpc/powerpc_init.c
#        lib/lpng1639/scripts/intprefix.c
#        lib/lpng1639/scripts/prefix.c
#        lib/lpng1639/scripts/sym.c
#        lib/lpng1639/scripts/symbols.c
#        lib/lpng1639/scripts/vers.c
#        lib/lpng1639/example.c
#        lib/lpng1639/png.c
#        lib/lpng1639/png.h
#        lib/lpng1639/pngconf.h
#        lib/lpng1639/pngdebug.h
#        lib/lpng1639/pngerror.c
#        lib/lpng1639/pngget.c
#        lib/lpng1639/pnginfo.h
#        lib/lpng1639/pnglibconf.h
#        lib/lpng1639/pngmem.c
#        lib/lpng1639/pngpread.c
#        lib/lpng1639/pngpriv.h
#        lib/lpng1639/pngread.c
#        lib/lpng1639/pngrio.c
#        lib/lpng1639/pngrtran.c
#        lib/lpng1639/pngrutil.c
#        lib/lpng1639/pngset.c
#        lib/lpng1639/pngstruct.h
#        lib/lpng1639/pngtest.c
#        lib/lpng1639/pngtrans.c
#        lib/lpng1639/pngwio.c
#        lib/lpng1639/pngwrite.c
#        lib/lpng1639/pngwtran.c
#        lib/lpng1639/pngwutil.c
#        lib/write/stb_image.h
#        lib/write/stb_image_resize.h
#        lib/write/stb_image_write.h
#        File.c
#        File.h
#        Image.c
#        Image.h
#        Input.c
#        Main.c
#        Save.c
#        Save.h
#        UserHandler.c
#        UserHandler.h)
#
#target_link_libraries(src ws2_32)
cmake_minimum_required(VERSION 3.21)
project(src)

# Add the include directories for the PNG library
include_directories(C:/msys64/mingw64/include)

# Add your source files to the project
add_executable(src Main.c Save.c File.c Effects/Color.h Effects/Color.c Main.c Effects/Noise.c Effects/Noise.h Effects/Noise.c UserHandler.c Effects/Noise.c Image.c UserHandler.c Effects/Redeye.c Effects/Redeye.c Effects/Redeye.c Effects/Redeye.h Effects/Stylize.c Effects/Stylize.h Effects/Stylize.c Effects/Stylize.h Effects/Redeye.h Effects/Color.c Effects/Redeye.c Effects/Redeye.c Effects/Stylize.c C:/msys64/mingw64/include/ws2tcpip.h File.c Effects/Stylize.c Effects/Pixelate.c Effects/Pixelate.h Effects/CartoonDrawing.c Effects/CartoonDrawing.h Effects/Blur.c Effects/Blur.h Effects/Solarize.c Effects/Solarize.h Effects/Border.c Effects/Border.h email.c Menu.c Menu.h popupImage.c popupImage.h Effects/Stylize.c Effects/Color.c popupImage.c lib/lpng1639/pngmem.c /stdlib.h)

# Link against the PNG and Winsock libraries
target_link_libraries(src C:/msys64/mingw64/lib/libpng.a)

#target_compile_options(src -lpng)
# Specify the C standard
set_target_properties(src PROPERTIES C_STANDARD 11)
target_link_libraries(src ws2_32)
