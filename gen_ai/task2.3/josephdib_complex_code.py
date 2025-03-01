import numpy as np
import pandas as pd
import statistics as st

def KNN(kVal=9):
    for i in range(test_array.shape[0]):
        
        currEuclid = blankEuclid.copy()
        euclid = np.zeros(train_array.shape[0], dtype=int)
        dist(i, euclid)
        for j in range(euclid.shape[0]):
            currEuclid.iloc[j] = euclid[j]
        euclid_sorted=currEuclid.sort_values(ascending=True)
        indexes = np.empty(kVal, dtype=int)

        for k in range(kVal):
            indexes[k]=euclid_sorted.index[k]

        pred[i] = st.mode(indexes)

def dist(row, array):
    for a in range(train_array.shape[0]):
        array[a] = np.sqrt( np.sum( np.square( test_array[row] - train_array[a])))

train_data = pd.read_csv('MNIST_training.csv', index_col=0)
test_data = pd.read_csv('MNIST_test.csv', index_col=0)

train_array = train_data.to_numpy()
test_array = test_data.to_numpy()

train_array.astype(int)
test_array.astype(int)

groundTruth = np.empty(test_array.shape[0], dtype=int)

for i in range(test_array.shape[0]):
    groundTruth[i] = test_data.index[i]

blankEuclid = train_data.iloc[:, 0]

blankEuclid.astype(int)
for i in range(blankEuclid.shape[0]):
    blankEuclid.iloc[i]=0
print("Calculating KNN Accuracies...")
for kV in [1,3,5,9,11]:

    pred = np.empty(test_array.shape[0], dtype=int)
    KNN(kV)
    count = 0
    for c in range(test_array.shape[0]):
        if pred[c] == groundTruth[c]:
            count += 1
    acc = count / test_array.shape[0]
    print("K = ",kV,"   ACCURACY = ", acc)




    