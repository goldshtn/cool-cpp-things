# Five Cool Things You Never Thought C++ Could Do

This repository contains the code samples for my talk on cool things you can do in C++. There are five such things right now:

1. Safe printf -- a foundation for compile-time safe ```printf``` when the format string is a compile-time literal. The code determines the number of placeholders in the format string and verifies that the arguments passed match the number of placeholders.
 
2. Container dumper -- a basic library for printing out containers, recursively, by recognizin that an object is indeed a container.
 
3. Parallelism -- a very simple parallelism library based on C++11 threading support. Includes three algorithms: ```parallel_for```, ```parallel_invoke```, and ```parallel_transform```.

4. Units -- a simple example of dimensional analysis. A ```unit``` template type represents scalar values associated with a physical unit, such as m/s or kg/m^2. Operations on units are compile-time safe, so you can't (for example) add meters to seconds or assign speed to an acceleration variable.

5. Expression templates -- a simple example of using proxy classes to defer expression evaluation on mathematical vectors.

This talk was first delivered at the [Sela Developer Practice](http://www.seladeveloperpractice.com) in 2015. Some of the ideas for this talk were influenced by the C++ MVP community.