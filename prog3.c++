import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Step 1: Load the dataset
df = pd.read_csv("Iris.csv")

# Step 2: Drop non-numeric/unnecessary columns (like ID if exists)
df = df.drop(columns=["Id"]) if "Id" in df.columns else df

# Step 3: Filter by species
species = df['Species'].unique()
for s in species:
    print(f"\n--- Statistics for {s} ---")
    subset = df[df['Species'] == s]
    print(subset.describe(percentiles=[.25, .5, .75]))

# Step 4: Measures of variability function
def variability_measures(data):
    stats = {
        'Range': data.max() - data.min(),
        'IQR': data.quantile(0.75) - data.quantile(0.25),
        'Variance': data.var(),
        'Standard Deviation': data.std()
    }
    return pd.DataFrame(stats)

print("\n--- Measures of Variability for Each Numeric Column ---")
numeric_cols = df.select_dtypes(include='float64')
print(variability_measures(numeric_cols))

# Step 5: Correlation matrix
corr = numeric_cols.corr()

# Step 6: Visualization of correlation matrix
plt.figure(figsize=(8, 6))
sns.heatmap(corr, annot=True, cmap='coolwarm', fmt='.2f')
plt.title("Correlation Heatmap of Iris Dataset Features")
plt.show()
