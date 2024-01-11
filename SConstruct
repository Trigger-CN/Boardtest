import os
import sys
import buildconfig

TARGET = 'boardtest.' + buildconfig.TARGET_EXT

DefaultEnvironment(tools=[])
env = Environment(tools = ['mingw'],
	AS = buildconfig.AS, ASFLAGS = buildconfig.AFLAGS,
	CC = buildconfig.CC, CCFLAGS = buildconfig.CFLAGS,
	AR = buildconfig.AR, ARFLAGS = '-rc',
	LINK = buildconfig.LINK, LINKFLAGS = buildconfig.LFLAGS)

# make a building
from buildconfig import *
main_vdir = ''
# 定义源文件
PrepareBuilding(env)
objs = SConscript('SConscript', variant_dir=main_vdir, duplicate=0)
# 生成可执行文件
DoBuilding(TARGET, objs)
