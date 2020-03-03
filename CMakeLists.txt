cmake_minimum_required(VERSION 3.15)
project(LexicalAnalyzer)

set(CMAKE_CXX_STANDARD 14)

add_executable(LexicalAnalyzer main.cpp include/Analyzer.h src/Analyzer.cpp include/Token.h include/TokenType.h include/DFA.h)