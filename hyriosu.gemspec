# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'hyriosu/version'

Gem::Specification.new do |spec|
  spec.name          = "hyriosu"
  spec.version       = Hyriosu::VERSION
  spec.authors       = ["RGSS3"]
  spec.email         = ["RGSS3"]

  spec.summary       = %q{a ruby based but language neutral game framework}
  spec.description   = %q{a ruby based but language neutral game framework}
  spec.homepage      = "http://github.com/RGSS3/hyriosu"
  spec.license       = "MIT"

  
  spec.files         = `git ls-files -z`.split("\x0").reject do |f|
    f.match(%r{^(test|spec|features)/})
  end
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler", "~> 1.14"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rspec", "~> 3.0"
end
