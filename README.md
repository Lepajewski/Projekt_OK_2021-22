# Projekt_OK_2021-22

*sources* - contains all sources used in the project.
* test_generator.cpp - generates random graphs, arguments: \#vertices, \#instances
* triangle_histogram.cpp - counts \#triangles in graphs in given files and saves the results
* find_holes.cpp - finds all holes in triangles occurrences and saves them
* choose_models.cpp - finds all complete graphs that are complement to those given in files. Given graphs must also contain zero triangles and must be considered as a hole. Saves chosen models.
* format_csv.cpp - reads models and saves them in *.csv* file that can be easily read by *pandas* and interpreted as a graph by *networkx* (for drawing the graphs).

*results* - histogram of all triangles in graphs. The order in files is: \#triangles \(t\), \#graphs_with_t_triangles, \#edges. Results are both for 10M and 100K test sizes.<br>
*holes* - contains files with all holes found in triangles occurrences.<br>
*Plots2D* - pictures and animated gifs with histograms and times.<br>
*Plots3D* - visualisation of histograms; both sscatter and mesh.<br>

### Tools used:

I wrote sources in C++ and Python.<br>
Python: numpy, plotly, matplotlib, mpl_toolkits, pandas, networkx<br>
I used GIMP for making gifs.
