# GraphWidget

This is a C++ Qt static library which adds a widget to display graphs in Qt.

1. [Installation](#installation)
2. [Minimum Working Example](#example1)
3. [Updating Graph Periodically](#example2)
4. [Function List](#functions)
5. [Themes](#themes)

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
<a name="example1"></a>
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

Now we can begin to add data to the plot with the `addData(double xData, double yData)` function. We can add
```c++
#include <QRandomGenerator>
```
to the top of our `mainwindow.cpp` file and append the following code to the end of `MainWindow`s constructor:
```c++
for (int x = 0; x < 50; x++) {
    double y = QRandomGenerator::global()->generate() % 100;
    graph->addData(x, y);
}
```
This should add 50 data points with randomly generated values in the range 0 - 99:

![alt text](https://user-images.githubusercontent.com/17698478/61420500-1727ef80-a903-11e9-97e7-5dd01b201e13.png)

<a name="example2"></a>
## 3. Updating Graph Periodically
In this example we use a `QTimer` to add values periodically to the graph by connecting the `QTimer`s `timeout` signal to a lambda function. In the lambda we update a static variable to keep track of time, and use the `qSin()` function (found in `<QtMath>`) to construct a 1 Hz sine wave.
```c++
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGridLayout>
#include <QTimer>
#include <QtMath>

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

    // Create a new timer object
    QTimer* timer = new QTimer(this);

    // Set the timers update interval
    int interval = 50;
    timer->setInterval(interval);

    // Set the frequency to 1 Hz
    double frequency = 1.0;
    double angularFrequency = frequency*2.0*M_PI;

    // Update the graph with new data when the timer timeouts
    connect(timer, &QTimer::timeout,
            this, [graph, interval, angularFrequency] ()
    {
        static double xData = 0;
        double yData = qSin(angularFrequency*xData);

        graph->addData(xData, yData);

        xData += static_cast<double>(interval)/1000.0;
    });

    // Start the timer
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
```

![alt text](https://user-images.githubusercontent.com/17698478/61421609-19407d00-a908-11e9-9f82-65e746397725.gif)

The graph continuously adds data to the graph, but after the number of data points reach a certain value, old data will be pushed out. This is to prevent the graph from cluttering when data is plotted continuously for a long time. The default maximum number of samples is 100. This can be changed by calling
```c++
setSampleBufferSize(const int size)
```
<a name="functions"></a>
## 4. Function List
 | Function | Description |
 | ---------- | ------------- |
 | `GraphWidget(int width = 400, int height = 200, QWidget* parent = nullptr)` | Constructor for the GraphWidget. `width` and `height` specifies the width and height of the active graph area, not the widget. The widget itself will be slightly larger to fit the axis and lables. |
 | `void addData(double xData, double yData)` | Adds a new pair of data to the graph. |
 | `void setSampleBufferSize(const int size)` | Sets the maximum number of samples stored on the graph. If `size` is set to a number smaller than the number of samples already plotted, the graph will be resized. |
 | `void setTheme(const GraphStyler::GraphThemeSelection theme)` | Changes the theme of the graph. Two themes are currently supported, `GraphStyler::BasicTheme` and `GraphStyler::DarkTheme` (see [themes](#themes)).|
 | `void setXTicks(const int ticks)` | Sets number of ticks on the x-axis. |
 | `void setYTicks(const int ticks)` | Sets number of ticks on the y-axis. |
 | `void setTicksToMatchData(const bool match = true);` | Sets the number of ticks on the x-axis to match the number of samples (assumes data on x-axis is linear). |

<a name="themes"></a>
## 5. Themes
### Basic Theme
![alt text](https://user-images.githubusercontent.com/17698478/61422580-9e2d9580-a90c-11e9-9ebe-1a9ff9e1592f.png)

### Dark Theme
![alt text](https://user-images.githubusercontent.com/17698478/61422606-aede0b80-a90c-11e9-99df-d69d7fcb9370.png)


