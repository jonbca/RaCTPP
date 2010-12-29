# Copyright (C) 2010 Jonathan Abourbih
# 
# This file is part of RactPP, the Ruby-FaCT++ Bridge.
# 
# RactPP is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# RactPP is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License
# along with RactPP.  If not, see <http://www.gnu.org/licenses/>.

require 'mkmf'

extension_name = 'ractpp'

dir_config(extension_name)

# This warning is usually automatically included on MacOS but the
# FaCT++ files trip it a lot. It's not harmful but it's annoying, so remove it.
CONFIG['warnflags'].gsub!("-Wshorten-64-to-32", "")

# Add the FaCT++ library to the build path
find_library('Kernel', nil)

create_makefile(extension_name + "/core")