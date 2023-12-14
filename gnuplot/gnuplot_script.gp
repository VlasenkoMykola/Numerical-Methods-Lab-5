set terminal pngcairo enhanced font 'arial,12' size 800,600

# Set axis labels and title
set xlabel 'x'
set ylabel 'y'
set title 'Function Graphs'

set output 'func1.png'
# Plot the data using lines
plot 'func1.data' using 1:2 with lines title 'f(x)', \
     'func1.data' using 1:3 with lines title 'N(x)', \
     'func1.data' using 1:4 with lines title 'G(x)'

set output 'func2.png'
# Plot the data using lines
plot 'func2.data' using 1:2 with lines title 'f(x)', \
     'func2.data' using 1:3 with lines title 'N(x)', \
     'func2.data' using 1:4 with lines title 'G(x)'


set output 'func3.png'
# Plot the data using lines
plot 'func3.data' using 1:2 with lines title 'f(x)', \
     'func3.data' using 1:3 with lines title 'N(x)', \
     'func3.data' using 1:4 with lines title 'G(x)'

