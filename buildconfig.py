import os
import sys
import string
import operator
import platform

# toolchains options
ARCH='arch_tricore'
CPU='arch_tc3'

CROSS_TOOL='gcc'
PLATFORM   = 'linux'
EXEC_PATH = r" "

BUILD = 'release'

PREFIX = ''
CC = PREFIX + 'gcc'
AS = PREFIX + 'as'
AR = PREFIX + 'ar'
LINK = PREFIX + 'gcc'
TARGET_EXT = 'elf'
SIZE = PREFIX + 'size'
OBJDUMP = PREFIX + 'objdump'
OBJCOPY = PREFIX + 'objcopy'
STRIP = PREFIX + 'strip'

DEVICE = ''
CFLAGS = DEVICE + ' -Os -g3 -W -Wall -std=gnu99'
AFLAGS = DEVICE
LFLAGS = DEVICE + '-fopenmp -o "boardtest.elf" '
LFLAGS += ' -Wl,-Map="boardtest.map" '

if BUILD == 'release':
    CFLAGS += ' -O2 -Os'

POST_ACTION = OBJCOPY + ' -O ihex $TARGET boardtest.hex\n'
POST_ACTION += SIZE + ' $TARGET \n'

Env = None

def PrepareBuilding(env):
    global Env
    Env = env

def DoBuilding(target, objects):
    global Env
    Env.Program(target, objects)
    Env.AddPostAction(target, POST_ACTION)

def AppendCPPPATH(target):
    global Env
    Env.AppendUnique(CPPPATH = target)

def GetCurrentDir():
    path = os.path.dirname(os.path.abspath('SConscript'))
    return path

