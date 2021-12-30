from mpl_toolkits import mplot3d
import numpy as np
import matplotlib.pyplot as plt
import os
import plotly
import plotly.graph_objs as go

def max_edges(n):
    return (n-1)*n // 2
def max_triangles(n):
    return n*(n-1)*(n-2) // 6

def read_data(f_name):
    f = open('{}/{}'.format('results', f_name), 'r')
    time = []
    n_of_line = 0
    ver = 0
    tests = 0
    max_e = 0
    max_t = 0
    plot = [[],[],[]]

    for line in f:
        if n_of_line == 0:
            ver, tests = line.split(' ')
            ver = int(ver)
            tests = int(tests)
            max_e = max_edges(ver)
            max_t = max_triangles(ver)
        if n_of_line == 1:
            time.append(float(line))
        if n_of_line > 1 and line != '\n':
            line = line[0:len(line)-1]
            x, y, z = line.split(' ')
            x = int(x)
            y = int(y)
            z = int(z)
            plot[0].append(x)
            plot[1].append(y)
            plot[2].append(z)
        if n_of_line == max_t + 3:
            n_of_line = 0

        n_of_line += 1

    f.close()
    return ver, tests, plot, time

def make_plots(ver, tests, plot):
    data = [go.Scatter3d(z=plot[1], x=plot[0], y=plot[2], mode='markers',
                         marker={'size':4, 'opacity':0.9, 'color':plot[1]})]
    layout = go.Layout(scene = dict(
                    xaxis_title='Liczba trójkątów',
                    yaxis_title='Liczba krawędzi',
                    zaxis_title='Liczba grafów'), margin={'l': 0, 'r': 0, 'b': 0, 't': 0})
    fig = go.Figure(data=data, layout=layout)
    fig.write_html("{}_{}.html".format(ver, tests))

def surface_plots(ver, tests, plot):
    plot[0] = plot[0][0:len(plot[0])-1]
    plot[1] = plot[1][0:len(plot[1])-1]
    plot[2] = plot[2][0:len(plot[2])-1]

    data = [go.Mesh3d(
        z=plot[1],
        x=plot[0],
        y=plot[2],
        opacity=1,
        colorscale= [[0, 'white'],
                    [0.01, 'darkviolet'],
                    [0.5, 'green'],
                    [1, 'yellow']],
        intensity=plot[1],
        contour_width=6, contour_color='black', contour_show=True,
        showlegend=True
        )]
    layout = go.Layout(scene = dict(
                    xaxis_title='Liczba trójkątów',
                    yaxis_title='Liczba krawędzi',
                    zaxis_title='Liczba grafów'), margin={'l': 0, 'r': 0, 'b': 0, 't': 0})
    fig = go.Figure(data=data, layout=layout)
    fig.write_html("{}_{}_surf.html".format(ver, tests))

def plots2d(ver, tests, plot):
    if not os.path.isdir('{}/{}'.format('plots2D', ver)):
        os.mkdir('{}/{}'.format('plots2D', ver))
    max_e = max_edges(ver)
    max_t = max_triangles(ver)

    curr = 0

    for e in range(3, max_e + 1):
        plot_dpi=200
        plt.figure(figsize=(2000/plot_dpi, 2000/plot_dpi), dpi=plot_dpi)

        plt.figure()
        plt.plot(plot[0][curr:curr+max_t+1]+[0], plot[1][curr:curr+max_t+1]+[1e6], '.')

        plt.ylim(0, 1e5)


        plt.title('V={}, E={}'.format(ver, e))
        plt.xlabel('Liczba trójkątów')
        plt.ylabel('Liczba grafów')
        plt.savefig('{}/{}/100k_{}.png'.format('plots2D', ver, e), dpi=plot_dpi, bbox_inches="tight")
        plt.clf()
        curr += max_t

def plot_time(ver, time):
    if not os.path.isdir('{}'.format('time_plots_100k')):
        os.mkdir('{}'.format('time_plots_100k'))
    max_e = max_edges(ver)
    total_time = sum(time)
    x = [i for i in range(3, max_e + 1)]
    plot_dpi=200
    plt.figure(figsize=(2000/plot_dpi, 2000/plot_dpi), dpi=plot_dpi)

    plt.figure()
    plt.plot(x, time, '.')
    plt.ylim(0, 1)
    plt.xlim(0,192)

    plt.title('V={}, Całkowity czas={:.3f}s'.format(ver, total_time))
    plt.xlabel('Liczba krawędzi')
    plt.ylabel('Czas [s]')
    plt.savefig('{}/{}.png'.format('time_plots_100k', ver), dpi=plot_dpi)
    plt.clf()

def plot_max_time(max_time, name):
    total_time = sum(max_time[1])
    plot_dpi=200
    plt.figure(figsize=(2000/plot_dpi, 2000/plot_dpi), dpi=plot_dpi)

    plt.figure()
    plt.plot(max_time[0], max_time[1], '.')
    plt.ylim(0, 1)
    plt.xlim(2, 21)

    plt.title('Całkowity czas={:.3f}s'.format(total_time))
    plt.xlabel('Liczba wierzchołków')
    plt.ylabel('Czas [s]')
    plt.savefig('{}/{}.png'.format('time_plots_100k', name), dpi=plot_dpi)
    plt.clf()

if __name__ == '__main__':
    max_times = [[],[]]
    avg_times = [[],[]]
    min_times = [[],[]]
    for res in os.listdir('{}'.format('results')):
        if '.' in res:
            ver, tests, plot, time = read_data(res)
            print("Current file: ", res)
            make_plots(ver, tests, plot)
            surface_plots(ver, tests, plot)
            plots2d(ver, tests, plot)
            max_times[0].append(ver)
            max_times[1].append(max(time))
            avg_times[0].append(ver)
            avg_times[1].append(sum(time)/len(time))
            min_times[0].append(ver)
            min_times[1].append(min(time))
            plot_time(ver, time)
    plot_max_time(max_times, 'max_times')
    plot_max_time(avg_times, 'avg_times')
    plot_max_time(min_times, 'min_times')
