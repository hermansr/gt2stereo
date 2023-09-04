cmake_minimum_required(VERSION 3.5)

add_library(resid OBJECT
  dac.cc
  envelope.cc
  extfilt.cc
  filter8580new.cc
  # filter.cc
  pot.cc
  sid.cc
  # version.cc
  voice.cc
  wave.cc
)
