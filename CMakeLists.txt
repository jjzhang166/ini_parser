cmake_minimum_required(VERSION 3.6)
project(ini_parser)

set(SOURCE_FILES
        example.c
        ini_parser.c
        )

add_executable(ini_parser ${SOURCE_FILES})