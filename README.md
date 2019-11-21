# Box2D 

## How to use Box2D Testbed?

```
$ ./premake5 gmake
```

Run "build.sh"

## How to add your own test?

* In "Testbed/Tests" add your new file .h, e.g "FooTest.h"

* Your file must look like this 

```
#ifndef FOOTEST_H
#define FOOTEST_H

class FooTest : public Test {

public:

FooTest() {
    //your code
  }

void Step(Settings* settings) {
    Test::Step(settings);

    //show some text in the main screen
    g_debugDraw.DrawString(5, m_textLine, "My test");
    m_textLine += 15;
  }
    
static Test* Create() {
    return new FooTest;
  }
  
};

#endif
```
* Then go TestEntries.cpp

First, in the header add:

`#include "FooTest.h`

Then, 
```
TestEntry g_testEntries[] =
{{"Foo test" , FooTest::Create}, //your file
{"Shape Cast", ShapeCast::Create }, //default tests...
```

Build again and success!


## License

Box2D is developed by Erin Catto, and has the [zlib license](http://en.wikipedia.org/wiki/Zlib_License). While the zlib license does not require acknowledgement, we encourage you to give credit to Box2D in your product.
