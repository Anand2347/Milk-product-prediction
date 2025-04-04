import pandas as pd
from sklearn.tree import DecisionTreeClassifier
import joblib

# Load dataset
data = pd.read_csv("milk_data.csv")
data.columns = [col.strip().lower() for col in data.columns]

# Training
X = data[["temperature", "Fat", "ph"]]
y = data["product"]

model = DecisionTreeClassifier()
model.fit(X, y)

# Save model
joblib.dump(model, "milk_model.pkl")
print("✅ Model trained and saved")
