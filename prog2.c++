import csv  # for reading CSV files
import math  # for mathematical operations

# ---------- Step 1: Load the dataset manually ----------
age = []
income = []

with open('Age-Income-Dataset.csv', 'r') as file:
    reader = csv.DictReader(file)
    for row in reader:
        age.append(float(row['Age']))
        income.append(float(row['Income']))

# ---------- Step 2: Define custom functions for summary statistics ----------
def calculate_mean(data):
    return sum(data) / len(data)

def calculate_median(data):
    sorted_data = sorted(data)
    n = len(sorted_data)
    mid = n // 2
    if n % 2 == 0:
        return (sorted_data[mid - 1] + sorted_data[mid]) / 2
    else:
        return sorted_data[mid]

def calculate_min(data):
    return min(data)

def calculate_max(data):
    return max(data)

def calculate_std(data):
    mean = calculate_mean(data)
    variance = sum((x - mean) ** 2 for x in data) / len(data)
    return math.sqrt(variance)

# ---------- Step 3: Calculate and print statistics manually ----------
print("=== Summary Statistics (Manual) ===")
print("Age - Mean:", calculate_mean(age))
print("Age - Median:", calculate_median(age))
print("Age - Min:", calculate_min(age))
print("Age - Max:", calculate_max(age))
print("Age - Std Dev:", calculate_std(age))

print("Income - Mean:", calculate_mean(income))
print("Income - Median:", calculate_median(income))
print("Income - Min:", calculate_min(income))
print("Income - Max:", calculate_max(income))
print("Income - Std Dev:", calculate_std(income))

# ---------- Step 4: Summary statistics using library (optional) ----------
import pandas as pd

df = pd.read_csv('Age-Income-Dataset.csv')
print("\n=== Summary Statistics using Pandas ===")
print(df.describe())

# ---------- Step 5: Grouped statistics ----------
print("\n=== Grouped Summary of Income by Age Groups ===")
df['Age_Group'] = pd.cut(df['Age'], bins=[0, 20, 40, 60, 80, 100],
                         labels=["0-20", "21-40", "41-60", "61-80", "81-100"])
print(df.groupby('Age_Group')['Income'].describe())

# ---------- Step 6: Convert categorical to numeric (if any) ----------
# Assuming there’s a categorical column like "Job Type"
# Convert it to numeric codes
if 'Job Type' in df.columns:
    df['Job Type Code'] = df['Job Type'].astype('category').cat.codes
    print("\nCategorical to Numeric Mapping:")
    print(dict(enumerate(df['Job Type'].astype('category').cat.categories)))
