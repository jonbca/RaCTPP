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
require 'rake/gempackagetask'
require 'rake/extensiontask'
require 'rspec/core/rake_task'

spec = Gem::Specification.new do |s|
  s.platform      = Gem::Platform::RUBY
  s.summary       = 'Ruby wrapper for the FaCT++ SROIQ(D) reasoner'
  s.version       = "0.0.1"
  s.name          = "RaCTPP"
  s.author        = "Jonathan Abourbih"
  s.email         = "jon.abourbih+ractpp@gmail.com"
  s.required_ruby_version = ">=1.9"
  s.files         = Dir['**/**']
  s.test_files    = Dir['test/*.rb']
  s.has_rdoc      = false
  s.extensions    << 'ext/ractpp/extconf.rb'
  s.license       = 'LGPL-3'
  s.add_development_dependency('rspec')
end

Rake::GemPackageTask.new(spec).define

Rake::ExtensionTask.new('core', spec) do |t|
  t.config_options = ["--with-ractpp-include=#{ENV['FACT_KERNEL_DIR']}",
                      "--with-ractpp-lib=#{ENV['FACT_KERNEL_DIR']}/obj"]
  t.ext_dir = 'ext/ractpp'
  t.lib_dir = 'lib/ractpp'
end

desc "Run RSpec tests"
RSpec::Core::RakeTask.new(:spec) do |t|
  t.pattern = 'test/**/*_spec.rb'
end