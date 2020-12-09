cmake_minimum_required(VERSION 3.14)
project(search_engine)
set (EXE_NAME search_engine)

##########################################
# Students, edit the items below.  In the quotes,
# put the names of the input files as they should appear
# in the argv param to main.
# Example:
#   set (input01 "train_data.csv")
#   set (input02 "train_target.csv")
# etc....

#set (input01 "FlightData.txt")
#set (input02 "RequestedFlightPlans.txt")
#set (input03 "FlightPlans.txt")

set(CMAKE_CXX_FLAGS "-O3")

#
##########################################

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04)
    configure_file(${file} ${file} COPYONLY)
endforeach()

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS_DEBUG "-O3")
add_executable(${EXE_NAME} main.cpp DSHashTable.h catch.hpp DSHashTableTests.cpp Runner.cpp Runner.h
        TreeTest.cpp Word.cpp Word.h DSTree.h Title.cpp Title.h porter2_stemmer.h porter2_stemmer.cpp Index.cpp Index.h IndexHandler.cpp IndexHandler.h QueryHandler.cpp QueryHandler.h Metadata.cpp Metadata.h rapidcsv.h)
