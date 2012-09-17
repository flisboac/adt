#!/usr/bin/env python

APPNAME = 'adt'
VERSION = '0.1.0'

top = '.'
out = 'build'

sources = 'src/**.c'
includes = 'include/**.h'

def options(ctx):

    # Waf chore
	ctx.load("compiler_c")

	# Options
	ctx.add_option(
		'-c', '--c-compiler'
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
    ctx(
          sources = ctx.glob(sources)
        , target = APPNAME
        , defines = ['adt_STATIC', 'adt_BUILDING']
        , features = 'cc stlib'
    )
    ctx(
          sources = ctx.glob(sources)
        , target = APPNAME
        , defines = ['adt_BUILDING']
        , features = 'cc shlib'
    )
    
