import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import confusion_matrix, accuracy_score, precision_score, recall_score
df = pd.read_csv('/mnt/data/Iris.csv')
df.head()
# Drop Id column (not useful)
df = df.drop(columns='Id')

# Features and target
X = df.drop(columns='Species')  # input features
y = df['Species']               # target label
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)
model = GaussianNB()
model.fit(X_train, y_train)
y_pred = model.predict(X_test)

# Create confusion matrix
cm = confusion_matrix(y_test, y_pred, labels=model.classes_)
print("Confusion Matrix:\n", cm)
# Accuracy
acc = accuracy_score(y_test, y_pred)

# Precision, Recall (macro = average for multiclass)
prec = precision_score(y_test, y_pred, average='macro')
rec = recall_score(y_test, y_pred, average='macro')

# Error rate
error_rate = 1 - acc

print(f"\nAccuracy     : {acc:.2f}")
print(f"Error Rate   : {error_rate:.2f}")
print(f"Precision    : {prec:.2f}")
print(f"Recall       : {rec:.2f}")
