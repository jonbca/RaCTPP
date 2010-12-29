RaCTPP
======

What is it?
-----------
RaCTPP is a Ruby wrapper for [FaCT++](http://code.google.com/p/factplusplus/), a SHOIQ(D) description logic reasoner, with support for OWL DL and partial support for OWL 2.0. RaCTPP is intended to be used as a reasoner for the Web Ontology Language (OWL) in Semantic Web and [Linked Data](http://linkeddata.org) applications.

What is it not?
---------------
First of all, **it's not 100% Ruby**. It's a Ruby extension built in C++ that links in to the FaCT++ library, which itself is C++. One day, I'd like to build a 100% pure Ruby OWL reasoner, but that's significantly more effort and just not in the cards at the moment.

It's also **not a parser**. Although, it could easily work with a parser and probably should. There's a great 100% pure Ruby [parser](/bendiken/rdf) for the many RDF syntaxes (RDF/XML, Turtle, N3, etc.), which could certainly be adapted to work with this tool, and that's my next project. I don't have a plan to implement a parser for the [OWL abstract syntax](http://www.w3.org/TR/owl-semantics/syntax.html) or [Manchester syntax](http://www.w3.org/TR/owl2-manchester-syntax/) at the moment.

How is it licenced?
--------------------
RaCTPP is licenced under the Lesser GNU Public Licence. For more information, see the [COPYING](/jonbca/ractpp/blob/master/COPYING) and [COPYING.LESSER](/jonbca/ractpp/blob/master/COPYING.LESSER) files. RactPP is written and maintained by Jonathan Abourbih (jon.abourbih+github@gmail.com).

What else do I need?
--------------------
You'll need:

  *  Ruby 1.9.2
  *  bundler
  *  gcc, g++, and make. I've tested this with gcc 4.2.1 on the Mac, with the latest version of XCode.

Now, to build the project:

  * Download the [FaCT++ source code](http://code.google.com/p/factplusplus/) (tested with version 1.5.0)
  * Modify the FaCT++ Makefile according to their instructions for your platform
  * Build the Kernel using `make kernel`, making a note of the location of the `src/Kernel` directory. You don't need to build any of the other stuff, and it's probably best you don't if you have a Mac, as the JNI stuff is totally broken now.

Now, back to this project. Install the required rubygems with:

    $ bundle install

Then, go into the `src` directory and run the build process:

    $ ruby extconf.rb --with-ractpp-include=/path/to/FaCT++-1.5.0/src/Kernel --with-ractpp-lib=/path/to/FaCT++-1.5.0/src/Kernel/obj

You should see the output:

    checking for main() in -lKernel... yes
    creating Makefile

Then:

    $ make

You can run the tests in the `test` directory with `rspec ractpp.rb`.

Tell me more...
---------------
### About Description Logics
According to [Wikipedia](http://en.wikipedia.org/wiki/Description_logics), a description logic is a member of a logic family that can be used to describe a knowledge domain. Description logics are typically subsets of first-order predicate logic, but are more efficient for reasoning and more expressive than propositional logic. Description logics may be used to build ontologies, which computers can use to reason and make inferences over a domain.

### About OWL (The Web Ontology Language)
[OWL](http://en.wikipedia.org/wiki/Web_Ontology_Language) is a [W3C standard](http://www.w3.org/TR/owl2-overview/) language for the Semantic Web. OWL is compatible with [RDF](http://www.w3.org/TR/rdf-primer/), the Resource Description Framework, which is frequently used as a serialisation.

### Semantic Web and Linked Data
> The Semantic Web is an extension of the current one, in which information is given well-defined meaning, better enabling computers and people to work in cooperation. [_The Semantic Web_](http://www.sciam.com/article.cfm?articleID=00048144-10D2-1C70-84A9809EC588EF21), Berners-Lee et. al., 2001

The Semantic Web has seen explosive growth over the past few years, especially since the start of the [Linked Data](http://linkeddata.org) project. Linked Data semantically relates data from different, disparate data sources using shared vocabulary. Rather than being a standard, it's more of a best practice for sharing data.