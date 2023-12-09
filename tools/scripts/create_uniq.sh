#!/usr/bin/env sh

# This script creates a single file with all the code in it, so that it can be

utils="submodules/data_structures/include/utils.h submodules/data_structures/src/utils.cc"
vector="submodules/data_structures/include/vector.h submodules/data_structures/src/vector.cc"
trick="include/trick.h src/trick.cc"
section="include/section.h src/section.cc"
skatepark="include/skatepark.h src/skatepark.cc"
main="src/main.cc"

cat $utils $vector $trick $section $skatepark $main | sed '/#include "/d' > allin.cc
