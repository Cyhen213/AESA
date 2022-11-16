import pandas as pd
from pandas import DataFrame

# pd_reader = pd.read_csv("CFAR_input.csv")
# test0=pd_reader.iloc[0].values
# split_array=str(test0[0]).split()
# result=[]
# for value in split_array:
#     result.append(float(value))
# print(len(result))

import pandas as pd
import numpy as np
df = pd.read_csv("CFAR_input.csv", sep=' ', header=None)
df=df.drop(columns=[0])
print(np.array(df).shape)

df.to_csv("processed_Cfar.csv",header=False,index=False)
