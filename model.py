import pandas as pd
from sklearn.tree import DecisionTreeClassifier
import pickle

# Load dataset
data = pd.read_csv('milk_data.csv')
X = data[['temperature', 'ph', 'fat_percentage']]
y = data['product']

# Train model
model = DecisionTreeClassifier()
model.fit(X, y)

# Save model
with open('milk_model.pkl', 'wb') as f:
    pickle.dump(model, f)