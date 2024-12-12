# Import required libraries
import os
import pandas as pd  # For data manipulation and analysis
import matplotlib.pyplot as plt  # For data visualization

def analyse(file_path: str):

    # Read the CSV file
    df = pd.read_csv(file_path)

    # Extract the first row as reference
    reference_row = df.iloc[0]

    # Remove the first row from the DataFrame
    df = df.drop(df.index[0])

    # Sort the DataFrame by 'Pool Size' and 'Nb Threads'
    df_sorted = df.sort_values(by=['Pool Size', 'Nb Threads'])

    # Print the first few rows to verify sorting
    print(df_sorted.head())

    # Create a plot
    plt.figure(figsize=(12, 8))

    # Plot the reference line
    plt.axhline(
        y=reference_row['Execution Time (ms)'],
        color='r', linestyle='--', label='Reference'
    )

    # Loop through unique pool sizes and plot execution times
    for pool_size in df_sorted["Pool Size"].unique():
        # Filter the DataFrame by current pool size
        subset = df_sorted[df_sorted["Pool Size"] == pool_size]

        # Plot the number of threads vs execution time
        plt.plot(
            subset["Nb Threads"],
            subset["Execution Time (ms)"],
            marker='o',
            label=f"Pool Size {pool_size}"
        )

    # Customize the plot
    #plt.title("Execution Time vs Number of Threads by Pool Size (Sorted)")
    plt.title(os.path.splitext(os.path.basename(file_path))[0])
    plt.xlabel("Number of Threads")
    plt.ylabel("Execution Time (ms)")
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.legend(title="Pool Size")

    # Save the plot as an image in the current directory
    output_file = file_path.replace('.csv', '.png')
    plt.savefig(output_file, dpi=300, bbox_inches='tight')

    # Inform the user and display the plot
    print(f"Plot saved as {output_file} in the current directory.")
    plt.show()

# Ensure the main function runs only when this script is executed directly
if __name__ == "__main__":
    csv_directory = "./analyse"

    for file in os.listdir(csv_directory):
        if file.endswith(".csv"):
            file_path = os.path.join(csv_directory, file)
            analyse(file_path)
