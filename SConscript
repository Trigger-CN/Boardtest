from buildconfig import *

cwd  = GetCurrentDir()
objs = [
    "coremark/core_list_join.c",
    "coremark/core_matrix.c",
    "coremark/core_state.c",
    "coremark/core_util.c",
    "coremark/posix/core_portme.c",
    "coremark/core_main.c",
    "main.c"
    ]
list = os.listdir(cwd)
CPPPATH = [
    cwd,
    'coremark',
    'coremark/posix'
    ]

AppendCPPPATH(CPPPATH)

for d in list:
    path = os.path.join(cwd, d)
    if os.path.isfile(os.path.join(path, 'SConscript')):
        objs = objs + SConscript(os.path.join(d, 'SConscript'))

Return('objs')
