#!/usr/bin/env python

APPNAME = 'dt'
MAJOR = 0
MINOR = 1
PATCH = 0
RELEASE = 'beta'

VERSION = '%d.%d.%d-%s' % (MAJOR, MINOR, PATCH, RELEASE)
APPPREFIX = APPNAME + '_'

top = '.'
out = 'build'

sources = 'src/**.c'
includes = 'include/**.h'
doxyfile = "Doxyfile"

def options(ctx):

    # Waf chore
    ctx.load("compiler_c")
    
    # Options
    ctx.add_option(
        '-C', '--c-compiler'
        , dest = 'c_compiler'
        , default = ''
        , action = 'store'
        , help = "Chooses the exact compiler to use in the build process."
    )


def configure(ctx):
    # Load compiler
    if ctx.options.c_compiler:
        ctx.load(ctx.options.c_compiler)
    else:
        ctx.load("compiler_c")


def build(ctx):
    ctx.stlib(
          source = ctx.path.ant_glob(sources)
        , target = APPNAME
        , defines = [APPPREFIX + 'STATIC', APPPREFIX + 'BUILDING']
        , includes = ['include']
        #, cflags = ['-E']
    )
    ctx.shlib(
          source = ctx.path.ant_glob(sources)
        , target = APPNAME
        , includes = ['include']
        , defines = [APPPREFIX + 'BUILDING']
    )
    
    
def docs(ctx):
    from subprocess import call
    node = ctx.path.make_node("build/docs")
    try: node.mkdir()
    except: pass
    call(["doxygen", doxyfile])


def setup_site(ctx):
    from subprocess import call
    print("Todo...")


