# Step 1: Import all necessary libraries
import pandas as pd
import numpy as np

# Step 2: Load the dataset into a pandas DataFrame
df = pd.read_csv("nba.csv")  # Ensure the file is in your current working directory
print("Dataset Loaded Successfully!\n")

# Step 3: Initial Data Preprocessing
print("----- Initial Statistics & Missing Values -----")
print(df.info())  # Structure of the DataFrame
print("\nMissing values in each column:")
print(df.isnull().sum())

print("\n----- Basic Descriptive Statistics -----")
print(df.describe())  # Summary statistics for numeric columns

print("\n----- Dataset Dimensions -----")
print("Rows:", df.shape[0])
print("Columns:", df.shape[1])

# Step 4: Data Formatting and Type Normalization
print("\n----- Variable Data Types -----")
print(df.dtypes)

# Convert object columns that should be categorical
categorical_columns = ['Name', 'Team', 'College', 'Position']
for col in categorical_columns:
    if df[col].dtype == 'object':
        df[col] = df[col].astype('category')

# Convert 'Age', 'Height', 'Weight' to appropriate numeric types
numeric_columns = ['Age', 'Height', 'Weight']
for col in numeric_columns:
    df[col] = pd.to_numeric(df[col], errors='coerce')  # Coerce non-numeric to NaN if needed

print("\n----- Updated Data Types -----")
print(df.dtypes)

# Step 5: Turn Categorical Variables into Quantitative Variables
print("\n----- Encoding Categorical Variables -----")
encoded_df = pd.get_dummies(df, columns=['Team', 'College', 'Position'], drop_first=True)

print("Categorical variables converted to dummy/indicator variables.")
print("New dataset shape after encoding:", encoded_df.shape)

# Optional: Save encoded data
encoded_df.to_csv("nba_encoded.csv", index=False)
