#!/usr/bin/env python
import sys, os

def options(opt):
    opt.load('compiler_cxx')
    opt.load('gtest')

def configure(cfg):
    cfg.load('compiler_cxx')
    cfg.load('gtest')

def build(bld):
    bld(target          = 'bitter',
        export_includes = '.')

    # install headers
    for header in bld.path.ant_glob('bitter/**/*.(h|hpp|ipp)'):
        bld.install_as('${PREFIX}/include/%s' % header.path_from(bld.path), header)

    bld.program(
        features     = 'gtest',
        source       = bld.path.ant_glob('test/*.cc'),
        target       = 'bitter_test',
        includes     = '.',
        install_path = 'bin',
        use          = ['bitter'],
    )
