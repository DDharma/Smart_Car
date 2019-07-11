#!/usr/bin/env python
# coding: utf-8

# In[3]:


import numpy as np
from keras.models import model_from_json
import operator
import cv2
import sys, os

json_file = open("model-bw.json", "r") # Loading the model
model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(model_json)
loaded_model.load_weights("model-bw.h5")# load weights into new model
print("Loaded model from disk")

cap = cv2.VideoCapture(0)


categories = {0: 'FORWARD', 1: 'LEFT', 2: 'STOP', 3: 'RIGHT', 4: 'SLOW', 5: 'DANGER'} # Category dictionary

while True:
    _, frame = cap.read()
    # Simulating mirror image
    frame = cv2.flip(frame, 1)
    
    # Got this from collect-data.py
    # Coordinates of the ROI
    x1 = int(0.5*frame.shape[1])
    y1 = 10
    x2 = frame.shape[1]-10
    y2 = int(0.5*frame.shape[1])
    # Drawing the ROI
    # The increment/decrement by 1 is to compensate for the bounding box
    cv2.rectangle(frame, (x1-1, y1-1), (x2+1, y2+1), (255,0,0) ,1)
    # Extracting the ROI
    roi = frame[y1:y2, x1:x2]
    
    # Resizing the ROI so it can be fed to the model for prediction
    roi = cv2.resize(roi, (64, 64)) 
    roi = cv2.cvtColor(roi, cv2.COLOR_BGR2GRAY)
    _, test_image = cv2.threshold(roi, 120, 255, cv2.THRESH_BINARY)
    cv2.imshow("test", test_image)
    
    # Batch of 1
    result = loaded_model.predict(test_image.reshape(1, 64, 64, 1))
    prediction = {'FORWARD': result[0][0], 
                  'LEFT': result[0][1], 
                  'STOP': result[0][2],
                  'RIGHT': result[0][3],
                  'SLOW': result[0][4],
                  'DANGER': result[0][5]}
    
    
    prediction = sorted(prediction.items(), key=operator.itemgetter(1), reverse=True)# Sorting based on top prediction
    
    
    cv2.putText(frame, prediction[0][0], (10, 120), cv2.FONT_HERSHEY_PLAIN, 1, (0,255,255), 1)# Displaying the predictions   
    cv2.imshow("Frame", frame)
    
    interrupt = cv2.waitKey(10)
    if interrupt & 0xFF == 27: # esc key
        break
        
cap.release()
cv2.destroyAllWindows()

