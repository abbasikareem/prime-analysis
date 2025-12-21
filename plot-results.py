import pandas as pd
import matplotlib.pyplot as plt

# read benchmark data
td_df = pd.read_csv("csvs/trial-division.csv")
s_df = pd.read_csv("csvs/sieve.csv")

# make trial by division plot
plt.scatter(td_df["n"], td_df["ms"], marker="o")
plt.xlabel("N")
plt.ylabel("Time (milliseconds)")
plt.title("Trial Division Runtime")
plt.savefig("plots/trial-division-runtime.png")

# clear plot
plt.clf()

# make sieve of eratosthenes plot
plt.scatter(s_df["n"], s_df["ms"], marker="o")
plt.xlabel("N")
plt.ylabel("Time (milliseconds)")
plt.title("Sieve of Eratosthenes Runtime")
plt.savefig("plots/sieve-runtime.png")
