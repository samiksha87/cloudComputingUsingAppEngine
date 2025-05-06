import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score

# Step a) Load dataset and handle null values
df = pd.read_csv("Banglore Housing Prices - Banglore Housing Prices.csv")
df.fillna(method='ffill', inplace=True)  # Forward fill for simplicity

# Step b) Transform 'size' column (e.g., '2 BHK' to 2)
df['BHK'] = df['size'].apply(lambda x: int(str(x).split()[0]) if pd.notnull(x) else None)

# Step c) Convert 'total_sqft' to numerical values
def convert_sqft(x):
    try:
        if '-' in str(x):
            nums = x.split('-')
            return (float(nums[0]) + float(nums[1])) / 2
        return float(x)
    except:
        return None

df['total_sqft'] = df['total_sqft'].apply(convert_sqft)

# Drop rows with missing or invalid sqft or BHK values
df = df.dropna(subset=['total_sqft', 'BHK'])

# Step d) Add 'price_per_sqft' column
df['price_per_sqft'] = (df['price'] * 100000) / df['total_sqft']

# Step e) Remove outliers in 'price_per_sqft' and 'BHK'
def remove_outliers(df):
    df_out = pd.DataFrame()
    for location, subdf in df.groupby('location'):
        m = np.mean(subdf['price_per_sqft'])
        st = np.std(subdf['price_per_sqft'])
        reduced_df = subdf[(subdf['price_per_sqft'] > (m - st)) & (subdf['price_per_sqft'] <= (m + st))]
        df_out = pd.concat([df_out, reduced_df], ignore_index=True)
    return df_out

df = df.dropna(subset=['location'])
df['location'] = df['location'].apply(lambda x: x.strip())
location_counts = df['location'].value_counts()
df['location'] = df['location'].apply(lambda x: x if location_counts[x] > 10 else 'other')

df = remove_outliers(df)

# Step f) Linear Regression Model
X = df[['total_sqft', 'BHK']]
y = df['price']

# Split the dataset
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=1)

# Train model
model = LinearRegression()
model.fit(X_train, y_train)

# Predict and evaluate
y_pred = model.predict(X_test)

mse = mean_squared_error(y_test, y_pred)
accuracy = r2_score(y_test, y_pred)

print("Mean Squared Error:", mse)
print("R² Score (Accuracy):", accuracy)
