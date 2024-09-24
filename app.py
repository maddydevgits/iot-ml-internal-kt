from flask import Flask,request
import pickle

with open('model.pkl','rb') as model:
    classifier=pickle.load(model)

app=Flask(__name__)

@app.route('/')
def home():
    return 'API Server Online'

@app.route('/predict',methods=['GET','POST'])
def predict():
    m=request.args.get('m')
    m=int(m)
    result=classifier.predict([[m]])[0]
    if result==1:
        return 'off'
    else:
        return 'on'
    
if __name__=="__main__":
    app.run(host="0.0.0.0",port=2000)
