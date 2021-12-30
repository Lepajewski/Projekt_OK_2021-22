import pandas as pd
import networkx as nx
import matplotlib.pyplot as plt
import os

for model in os.listdir('models_ready'):
    dir_name = model.split('_')[0]
    if dir_name in ['15', '16','17','18','19','20']:
        print("Current: ", model)
        if not os.path.isdir('{}/{}'.format('models_visu', dir_name)):
            os.mkdir('{}/{}'.format('models_visu', dir_name))
        input_data = pd.read_csv('{}/{}'.format('models_ready', model), index_col=0)
        G = nx.Graph(input_data.values)
        if 'd' in model:
            plt.title('V={} E={} dopełnienie'.format(model.split('_')[0], G.number_of_edges()))
        else:
            plt.title('V={} E={}'.format(model.split('_')[0], G.number_of_edges()))

        nx.draw(G, with_labels=True)


        plt.savefig("{}/{}/{}.png".format('models_visu', dir_name, model[0:model.find('.')]))
        plt.clf()
