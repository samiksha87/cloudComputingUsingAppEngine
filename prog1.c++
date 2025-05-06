import pandas as pd
import numpy as np
from sklearn.preprocessing import LabelEncoder
import seaborn as sns
import matplotlib.pyplot as plt

# Load the dataset
df = pd.read_csv("AcadmicPerformance.csv")

# -----------------------
# a) Handle Missing Values
# -----------------------
print("\n🔍 Missing Values Before:")
print(df.isnull().sum())

# Fill numeric columns with mean
numeric_cols = df.select_dtypes(include=[np.number]).columns
df[numeric_cols] = df[numeric_cols].fillna(df[numeric_cols].mean())

# Fill categorical columns with mode
categorical_cols = df.select_dtypes(include=['object']).columns
df[categorical_cols] = df[categorical_cols].fillna(df[categorical_cols].mode().iloc[0])

print("\n✅ Missing Values After Handling:")
print(df.isnull().sum())

# -----------------------
# b) Detect and Handle Outliers (Using IQR Method)
# -----------------------
for col in numeric_cols:
    Q1 = df[col].quantile(0.25)
    Q3 = df[col].quantile(0.75)
    IQR = Q3 - Q1
    lower = Q1 - 1.5 * IQR
    upper = Q3 + 1.5 * IQR
    outliers = df[(df[col] < lower) | (df[col] > upper)]
    if not outliers.empty:
        print(f"\n📌 Outliers detected in {col}")
        # Cap the outliers to upper and lower bounds
        df[col] = np.where(df[col] < lower, lower, df[col])
        df[col] = np.where(df[col] > upper, upper, df[col])

# -----------------------
# c) Encode Categorical Columns
# -----------------------
le = LabelEncoder()

for col in categorical_cols:
    if col != "STUDENT_ID":  # Skip ID
        df[col] = le.fit_transform(df[col])

# Show cleaned dataset
print("\n📄 Cleaned Data (first 5 rows):")
print(df.head())
