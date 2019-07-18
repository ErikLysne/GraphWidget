# GraphWidget

This is a C++ Qt static library which adds a widget to display graphs in Qt.

1 [Installation](#installation)

<a name="installation"></a>
## 1. Installation and Usage
1. Clone/download this repository
2. Open Qt Creator and open `GraphWidget.pro`
3. Build the project - this should generate a build folder with a library file (`libGraphWidget.a` on macOS)
4. Create a new Qt Widget Application called `GraphWidgetTest`
5. Right click on the project folder and click `Add Library...`
6. Choose `External Library`  and click `Next`
7. In `Library file:`, press `Choose...` and navigate to the `GraphWidget` **build** folder and select the static library file generated in step 3
8. Click `Next` and `Finish`
9. Somewhere in your project (e.g. in `mainwindow.h`) you need to include the file `graphwidget.h` with the correct path - this can be done in one of two ways:
    1. By including the file with its relative path:
        ```c++
        #include <PATH_TO_SOURCE_CODE/GraphWidget/graphwidget.h>
        ```
    2. By copy-pasting the source code directory into your project:
        1. Copy-paste the `GraphWidget` directory into the same directory as your `.pro` file
        2. In Qt Creator, right click on the project folder and click `Add Existing Directory...`
        3. Make sure the `GraphWidget` folder is checked
        4. Click `Ok`
        5. You can now include the headerfile like this:
        ```c++
        #include <GraphWidget/graphwidget.h>
        ```
        
## 2. Minimum Working Example
The following example shows how to create a new `GraphWidget` object and add it to a layout in `mainwindow.cpp`:
```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>

#include <GraphWidget/graphwidget.h>

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
ui->setupUi(this);
setWindowTitle("Simple Graph Example");

// Create a new layout
QGridLayout* layout = new QGridLayout;

// Create a new graph widget object with width = 400 and height = 200
GraphWidget* graph = new GraphWidget(400, 200, this);

// Add the graph to the layout
layout->addWidget(graph);

// Create a new widget to bind the layout
QWidget* widget = new QWidget(this);
widget->setLayout(layout);

// Make the widget the central widget
setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
delete ui;
}
```
This should generate something like this:
![alt text](https://user-images.githubusercontent.com/17698478/61420206-c4016d00-a901-11e9-9189-d81414aca1d2.png)
