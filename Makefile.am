include $(top_srcdir)/Makefile.all.am
#include ../Makefile.tool.am

noinst_LIBRARIES = libcapstone-@VGCONF_ARCH_PRI@.a
if VGCONF_HAVE_PLATFORM_SEC
noinst_LIBRARIES += libcapstone-@VGCONF_ARCH_SEC@.a
endif

LIBCAPSTONE_SOURCES_COMMON = \
	cs.c utils.c SStream.c MCInstrDesc.c MCRegisterInfo.c \
	arch/X86/X86DisassemblerDecoder.c \
	arch/X86/X86Disassembler.c \
	arch/X86/X86IntelInstPrinter.c \
	arch/X86/X86ATTInstPrinter.c \
	arch/X86/X86Mapping.c \
	arch/X86/X86Module.c \
	arch/ARM/ARMDisassembler.c \
	arch/ARM/ARMInstPrinter.c \
	arch/ARM/ARMMapping.c \
	arch/ARM/ARMModule.c \
	arch/AArch64/AArch64BaseInfo.c \
	arch/AArch64/AArch64Disassembler.c \
	arch/AArch64/AArch64InstPrinter.c \
	arch/AArch64/AArch64Mapping.c \
	arch/AArch64/AArch64Module.c \
	arch/Mips/MipsDisassembler.c \
	arch/Mips/MipsInstPrinter.c \
	arch/Mips/MipsMapping.c \
	arch/Mips/MipsModule.c \
	arch/PowerPC/PPCDisassembler.c \
	arch/PowerPC/PPCInstPrinter.c \
	arch/PowerPC/PPCMapping.c \
	arch/PowerPC/PPCModule.c \
	arch/Sparc/SparcDisassembler.c \
	arch/Sparc/SparcInstPrinter.c \
	arch/Sparc/SparcMapping.c \
	arch/Sparc/SparcModule.c \
	arch/SystemZ/SystemZDisassembler.c \
	arch/SystemZ/SystemZInstPrinter.c \
	arch/SystemZ/SystemZMapping.c \
	arch/SystemZ/SystemZModule.c \
	arch/SystemZ/SystemZMCTargetDesc.c \
	arch/XCore/XCoreDisassembler.c \
	arch/XCore/XCoreInstPrinter.c \
	arch/XCore/XCoreMapping.c \
	arch/XCore/XCoreModule.c \
	MCInst.c

libcapstone_@VGCONF_ARCH_PRI@_a_SOURCES = $(LIBCAPSTONE_SOURCES_COMMON)
if VGCONF_HAVE_PLATFORM_SEC
libcapstone_@VGCONF_ARCH_SEC@_a_SOURCES = $(LIBCAPSTONE_SOURCES_COMMON)
endif

libcapstone_@VGCONF_ARCH_PRI@_a_CPPFLAGS     = \
        $(AM_CPPFLAGS_@VGCONF_PLATFORM_PRI_CAPS@)
libcapstone_@VGCONF_ARCH_PRI@_a_CFLAGS       = \
        $(AM_CFLAGS_@VGCONF_PLATFORM_PRI_CAPS@) -O2 -I./include -I../../include -I../../VEX/pub -DCAPSTONE_SECRETGRIND -DCAPSTONE_USE_SYS_DYN_MEM  -DCAPSTONE_HAS_ARM -DCAPSTONE_HAS_ARM64 -DCAPSTONE_HAS_MIPS -DCAPSTONE_HAS_POWERPC -DCAPSTONE_HAS_SPARC -DCAPSTONE_HAS_SYSZ -DCAPSTONE_HAS_X86 -DCAPSTONE_HAS_XCORE
libcapstone_@VGCONF_ARCH_PRI@_a_DEPENDENCIES = \
        $(TOOL_DEPENDENCIES_@VGCONF_PLATFORM_PRI_CAPS@)

if VGCONF_HAVE_PLATFORM_SEC
libcapstone_@VGCONF_ARCH_SEC@_a_CPPFLAGS     = \
	$(AM_CPPFLAGS_@VGCONF_PLATFORM_SEC_CAPS@)
libcapstone_@VGCONF_ARCH_SEC@_a_CFLAGS       = \
	$(AM_CFLAGS_@VGCONF_PLATFORM_SEC_CAPS@) -O2 -I./include -I../../include -I../../VEX/pub -DCAPSTONE_SECRETGRIND -DCAPSTONE_USE_SYS_DYN_MEM  -DCAPSTONE_HAS_ARM -DCAPSTONE_HAS_ARM64 -DCAPSTONE_HAS_MIPS -DCAPSTONE_HAS_POWERPC -DCAPSTONE_HAS_SPARC -DCAPSTONE_HAS_SYSZ -DCAPSTONE_HAS_X86 -DCAPSTONE_HAS_XCORE
libcapstone_@VGCONF_ARCH_SEC@_a_DEPENDENCIES = \
	$(TOOL_DEPENDENCIES_@VGCONF_PLATFORM_SEC_CAPS@)
endif
