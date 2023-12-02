pip install pandas numpy matplotlib mplfinance keras scikit-learn

import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from keras.models import Sequential
from keras.layers import LSTM, Dense
import mplfinance as mpf
import matplotlib.pyplot as plt

# 데이터 로드 및 전처리 함수
def preprocess_data(file_name):
    stock_data = pd.read_csv(file_name, index_col='Date', parse_dates=True)
    stock_data.drop(['Adj Close'], axis=1, inplace=True)
    scaler = MinMaxScaler()
    stock_data_scaled = scaler.fit_transform(stock_data)
    return stock_data_scaled, scaler, stock_data

  # 데이터셋 생성 함수
  def create_lstm_dataset(data_scaled, seq_len=60):
      X, Y = [], []
      for i in range(seq_len, len(data_scaled)):
          X.append(data_scaled[i - seq_len:i])
          Y.append(data_scaled[i, :])
      return np.array(X), np.array(Y)

    # LSTM 모델 구축 함수
    def build_lstm_model(input_shape):
        model = Sequential()
        model.add(LSTM(50, return_sequences=True, input_shape=input_shape))
        model.add(LSTM(50, return_sequences=False))
        model.add(Dense(25))
        model.add(Dense(5))  # 예측하려는 특성의 수 (Open, High, Low, Close, Volume)
        model.compile(optimizer='adam', loss='mean_squared_error')
        return model

      # 파일 경로 설정
      nasdaq_file = '/content/drive/MyDrive/DM Project/Nasdaq.csv'
      btc_file = '/content/drive/MyDrive/DM Project/BTC-USD.csv'

# 나스닥 데이터 전처리
nasdaq_data_scaled, nasdaq_scaler, nasdaq_data = preprocess_data(nasdaq_file)
nasdaq_X, nasdaq_Y = create_lstm_dataset(nasdaq_data_scaled)

# 비트코인 데이터 전처리
btc_data_scaled, btc_scaler, btc_data = preprocess_data(btc_file)
btc_X, btc_Y = create_lstm_dataset(btc_data_scaled)

# 나스닥 모델 학습
nasdaq_model = build_lstm_model(nasdaq_X.shape[1:])
nasdaq_model.fit(nasdaq_X, nasdaq_Y, epochs=10, batch_size=32, validation_split=0.1)

# 비트코인 모델 학습
btc_model = build_lstm_model(btc_X.shape[1:])
btc_model.fit(btc_X, btc_Y, epochs=10, batch_size=32, validation_split=0.1)

# 예측 및 시각화 함수
def predict_and_plot(model, data_X, scaler, original_data, title):
    predicted = model.predict(data_X)
    predicted = scaler.inverse_transform(predicted)

    # 예측된 'Close' 값을 저장하기 위한 열을 생성합니다.
    original_data['Predicted Close'] = np.nan
    # 예측값을 적절한 위치에 할당합니다.
    original_data['Predicted Close'].iloc[-len(predicted):] = predicted[:, 3]

    # 예측된 'Close' 값을 빨간 점선으로 시각화합니다.
    predicted_plot = mpf.make_addplot(original_data['Predicted Close'], type='line', color='red', linestyle='dashdot', width=1.5)

    # 실제 데이터 캔들차트 시각화 설정
    mc = mpf.make_marketcolors(up='blue', down='blue', inherit=True)
    s = mpf.make_mpf_style(marketcolors=mc)

    # 시각화 설정 및 플롯
    fig, axes = mpf.plot(original_data, type='candle', volume=True, addplot=predicted_plot, title=title, style=s, returnfig=True)

    # 색상 설명을 위한 텍스트 추가
    textstr = 'Blue: Actual Data\nRed dash-dot: Predicted Data'
    props = dict(boxstyle='round', facecolor='wheat', alpha=0.5)

    # 텍스트를 메인 차트에 추가합니다.
    axes[0].text(0.01, 0.97, textstr, transform=axes[0].transAxes, fontsize=9, verticalalignment='top', bbox=props)

    # 차트를 표시합니다.
    plt.show()

  # 나스닥 데이터에 대한 예측 및 시각화
  predict_and_plot(nasdaq_model, nasdaq_X, nasdaq_scaler, nasdaq_data, 'NASDAQ Predictions')

# 비트코인 데이터에 대한 예측 및 시각화
predict_and_plot(btc_model, btc_X, btc_scaler, btc_data, 'BTC Predictions')

#나스닥과 비트코인에 대한 60일간의 예측으로 모델을 학습 -> 학습한 모델로 다음날 즉 2014년 9월 17일부터 60일에 대한
모델 훈련을 진행하였다면, 두달 뒤 그 다음날의 시가 및 종가를 예측한다. 그렇게 예측한 시가와 종가를 실데이터와 비교하고
훈련하여 오차범위를 좁힌다. 그렇게 계속 진행하여 2014년9월17일부터 2023년11월23일 실데이터의 끝까지 진행하도록 한다.
이후 나스닥과 비트코인과의 상관관계를 분석하고, 훈련한 모델을 통해 2023년11월24일부터 2024년 12월 31일까지의 비트코이
추세와 가격을 예측한다. 다음으로 아까 구한 나스닥과 비트코인과 비교하여 분석한 상관관계를 적용하여 비트코인의 추세와
가격을 예측한다. 이후 상관관계를 적용하여 예측한 비트코인의 추세 및 가격과 상관관계를 통해 훈련하지 않고 일반적으로
예측한 모델의 데이터셋 즉 도출결과를 서로 비교하여 훈련시킨 다음 다시 2024년12월31일까지의 예측 결과를 도출한다.

#100일 이상은 과적합의 위험성이 있음 고로 seq_lens = 60으로 설정 -> 이후 60일의 실데이터를 통해 61일의 데이터를
예측하고 반복적으로 61D~120D까지의 예측데이터를 분석하고, 예측데이터와 실데이터의 차이를 분석한다. 이렇게 계속
반복적으로 모델을 학습하여 2023년11월23일까지의 데이터이 즉 2014년9월17일부터 2023년11월23일까지 진행한 후
해당 기간의 데이터를 토대로 2023년11월24일부터 2024년12월31일까지의 비트코인 추세와 가격을 예측한다. 이 후
같은 모델의 반복을 통해서 나스닥의 추세와 가격을 예측한다 23년11월23일까지 이 후 비트코인과 나스닥의 상관관계를
분석하여 2023년11월24일부터~2024년12월31일까지의 가격과 추세를 예측한 후 그냥 예측한 데이터와 나스닥과 비교하여
분석 예측한 비트코인 데이터와의 가격을 비교한다.싸이클이 도는 주기를 과적하븨 의미로 해석, 왜 60일로 하였는가?
목적성 예측 프레딕트 벨류 , 리얼 벨류 실데이터 vs 예측데이터 / 조정 전과 조정 후의 레인지 1,0간이라던가 조정전과
조정 후의 수익률의 차이 
