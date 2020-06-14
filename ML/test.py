import tensorflow as tf
import copy
import numpy as np
from Sudoku import Sudoku, read

model = tf.keras.models.load_model('./model')

def norm(a):
    return (a/9)-.5

def denorm(a):
    return (a+.5)*9

def inference_sudoku(sample):
    
    feat = copy.copy(sample)
    
    while(1):
    
        out = model.predict(feat.reshape((1,9,9,1)))  
        out = out.squeeze()

        pred = np.argmax(out, axis=1).reshape((9,9))+1 
        prob = np.around(np.max(out, axis=1).reshape((9,9)), 2) 
        
        feat = denorm(feat).reshape((9,9))
        mask = feat == 0
     
        if mask.sum() == 0:
            break
            
        prob_new = prob*mask
    
        ind = np.argmax(prob_new)
        x, y = (ind//9), (ind%9)

        val = pred[x][y]
        feat[x][y] = val
        feat = norm(feat)
    
    return pred

if __name__ == '__main__':
    sudoku = read('../data/easy-1.txt')
    result = inference_sudoku(sudoku.get_values().reshape((9,9,1)))
    print(result)