import json
import matplotlib.pyplot as plt
import numpy as np
import sys

def parse_benchmarks(bms):
    data_list = []
    for bm in bms:
        bm_name, array_size, threads = bm["name"].split('/')[0:3]
        data_list.append([array_size,
                          threads,
                          bm["iterations"],
                          bm["real_time"],
                          bm["cpu_time"],
                          bm["bytes_per_second"],
                          bm["items_per_second"]])
    return np.array(data_list, dtype=float)

def plot_ips_vs_array_size_by_thread(bm_array, caches):
    # split by number of threads
    t1  = bm_array[bm_array[:,1] == 1,  :]
    t2  = bm_array[bm_array[:,1] == 2,  :]
    t4  = bm_array[bm_array[:,1] == 4,  :]
    t8  = bm_array[bm_array[:,1] == 8,  :]
    t16 = bm_array[bm_array[:,1] == 16, :]

    plt.loglog(t1[:,0],  t1[:,-1],  ".-", label="1 Thread")
    plt.loglog(t2[:,0],  t2[:,-1],  ".-", label="2 Threads")
    plt.loglog(t4[:,0],  t4[:,-1],  ".-", label="4 Threads")
    plt.loglog(t8[:,0],  t8[:,-1],  ".-", label="8 Threads")
    plt.loglog(t16[:,0], t16[:,-1], ".-", label="16 Threads")
    for cache in caches:
        plt.axvline(x=cache["size"]/4, linestyle="--", label=f"L{cache['level']} {cache['type']} cache")
    plt.xlabel("Array Size")
    plt.ylabel("Items per Second")
    plt.legend()
    plt.show()

def main():
    filename = sys.argv[1]
    with open(filename) as file:
        data = json.load(file)
        caches = data["context"]["caches"]
        benchmarks = data["benchmarks"]
        bm_array = parse_benchmarks(benchmarks)
        plot_ips_vs_array_size_by_thread(bm_array, caches)

if __name__ == "__main__":
    main()