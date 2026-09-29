import csv
import os
import matplotlib.pyplot as plt


# 그래프를 저장할 폴더
OUTPUT_DIR = "graphs"
os.makedirs(OUTPUT_DIR, exist_ok=True)


# CSV 파일 읽기
data = []

with open("results.csv", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        row["n"] = int(row["n"])
        row["avg_time_ms"] = float(row["avg_time_ms"])
        row["comparisons"] = int(row["comparisons"])
        row["moves"] = int(row["moves"])

        data.append(row)


algorithms = ["Insertion", "Merge", "Heap"]
sizes = [100, 1000, 5000, 10000]


# =========================================================
# Graph 1
# Random input: execution time
# =========================================================

plt.figure(figsize=(8, 5))

for algorithm in algorithms:

    rows = [
        row for row in data
        if row["algorithm"] == algorithm
        and row["input_type"] == "Random"
    ]

    rows.sort(key=lambda row: row["n"])

    x = [row["n"] for row in rows]
    y = [row["avg_time_ms"] for row in rows]

    plt.plot(
        x,
        y,
        marker="o",
        label=algorithm
    )


plt.xlabel("Input Size (n)")
plt.ylabel("Average Execution Time (ms)")
plt.title("Execution Time on Random Input")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig(
    os.path.join(
        OUTPUT_DIR,
        "random_execution_time.png"
    ),
    dpi=300
)

plt.close()


# =========================================================
# Graph 2
# Random input: comparisons
# =========================================================

plt.figure(figsize=(8, 5))

for algorithm in algorithms:

    rows = [
        row for row in data
        if row["algorithm"] == algorithm
        and row["input_type"] == "Random"
    ]

    rows.sort(key=lambda row: row["n"])

    x = [row["n"] for row in rows]
    y = [row["comparisons"] for row in rows]

    plt.plot(
        x,
        y,
        marker="o",
        label=algorithm
    )


plt.xlabel("Input Size (n)")
plt.ylabel("Number of Comparisons")
plt.title("Comparisons on Random Input")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig(
    os.path.join(
        OUTPUT_DIR,
        "random_comparisons.png"
    ),
    dpi=300
)

plt.close()


# =========================================================
# Graph 3
# n = 10000: execution time by input type
# =========================================================

input_types = ["Random", "Sorted", "Reverse"]

x_positions = range(len(input_types))

bar_width = 0.25


plt.figure(figsize=(8, 5))


for index, algorithm in enumerate(algorithms):

    times = []

    for input_type in input_types:

        row = next(
            row for row in data
            if row["algorithm"] == algorithm
            and row["input_type"] == input_type
            and row["n"] == 10000
        )

        times.append(row["avg_time_ms"])


    positions = [
        x + (index - 1) * bar_width
        for x in x_positions
    ]

    plt.bar(
        positions,
        times,
        width=bar_width,
        label=algorithm
    )


plt.xticks(
    list(x_positions),
    input_types
)

plt.xlabel("Input Type")
plt.ylabel("Average Execution Time (ms)")
plt.title("Execution Time by Input Type (n = 10000)")
plt.legend()
plt.tight_layout()

plt.savefig(
    os.path.join(
        OUTPUT_DIR,
        "input_type_execution_time.png"
    ),
    dpi=300
)

plt.close()

# =========================================================
# Graph 4
# Random input: execution time (log scale)
# =========================================================

plt.figure(figsize=(8, 5))

for algorithm in algorithms:

    rows = [
        row for row in data
        if row["algorithm"] == algorithm
        and row["input_type"] == "Random"
    ]

    rows.sort(key=lambda row: row["n"])

    x = [row["n"] for row in rows]
    y = [row["avg_time_ms"] for row in rows]

    plt.plot(
        x,
        y,
        marker="o",
        label=algorithm
    )

plt.xlabel("Input Size (n)")
plt.ylabel("Average Execution Time (ms, log scale)")
plt.title("Execution Time on Random Input (Log Scale)")
plt.yscale("log")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig(
    os.path.join(
        OUTPUT_DIR,
        "random_execution_time_log.png"
    ),
    dpi=300
)

plt.close()


# =========================================================
# Graph 5
# Random input: comparisons (log scale)
# =========================================================

plt.figure(figsize=(8, 5))

for algorithm in algorithms:

    rows = [
        row for row in data
        if row["algorithm"] == algorithm
        and row["input_type"] == "Random"
    ]

    rows.sort(key=lambda row: row["n"])

    x = [row["n"] for row in rows]
    y = [row["comparisons"] for row in rows]

    plt.plot(
        x,
        y,
        marker="o",
        label=algorithm
    )

plt.xlabel("Input Size (n)")
plt.ylabel("Number of Comparisons (log scale)")
plt.title("Comparisons on Random Input (Log Scale)")
plt.yscale("log")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig(
    os.path.join(
        OUTPUT_DIR,
        "random_comparisons_log.png"
    ),
    dpi=300
)

plt.close()

print("Graphs created successfully.")
print("Saved in the graphs/ directory.")
