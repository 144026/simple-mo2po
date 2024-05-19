#!/bin/bash

exe=${1:-../build/mo2po}
mo=${2:-main.zh.mo}
po=${3:-main.zh.po}

"$exe" "$mo" _out.po && diff -u "$po" _out.po
