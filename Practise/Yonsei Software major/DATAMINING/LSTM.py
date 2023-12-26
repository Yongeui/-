# 필요한 라이브러리 설치
!pip install tensorflow pandas numpy matplotlib mplfinance keras scikit-learn

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import mplfinance as mpf
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error
from sklearn.model_selection import KFold

# 데이터 로드 및 전처리
nasdaq_data = pd.read_csv('/content/drive/MyDrive/DM Project/Nasdaq.csv', index_col='Date', parse_dates=True)
bitcoin_data = pd.read_csv('/content/drive/MyDrive/DM Project/BTC-USD.csv', index_col='Date', parse_dates=True)

# 날짜 일치 및 더미값 처리 함수
def align_dates_and_fill(data, start_date, end_date):
    data = data.reindex(pd.date_range(start_date, end_date))
    # 주말 데이터 대체
    data.loc['2017-01-01'] = data.loc['2017-01-03']
    data.loc['2017-01-02'] = data.loc['2017-01-03']
    data.fillna(method='ffill', inplace=True)
    return data

# 나스닥 및 비트코인 데이터에 더미값 추가
nasdaq_data = align_dates_and_fill(nasdaq_data, '2017-01-01', '2023-11-23')
bitcoin_data = align_dates_and_fill(bitcoin_data, '2017-01-01', '2023-11-23')

# 데이터 정규화 함수
def normalize_data(data):
    scaler = MinMaxScaler(feature_range=(0, 1))
    scaled_data = scaler.fit_transform(data[['Open', 'High', 'Low', 'Close', 'Volume']])
    return scaled_data, scaler

# 나스닥 및 비트코인 데이터 정규화
nasdaq_scaled, nasdaq_scaler = normalize_data(nasdaq_data)
bitcoin_scaled, bitcoin_scaler = normalize_data(bitcoin_data)

# LSTM 시퀀스 생성 함수
def create_sequences(data, window_size=60):
    X, y = [], []
    for i in range(len(data) - window_size):
        X.append(data[i:(i + window_size), :])
        y.append(data[i + window_size, 3])  # Close price
    return np.array(X), np.array(y)

# 나스닥 및 비트코인 시퀀스 생성
nasdaq_X, nasdaq_y = create_sequences(nasdaq_scaled)
bitcoin_X, bitcoin_y = create_sequences(bitcoin_scaled)

# LSTM 모델 구축 함수
def build_lstm_model(input_shape=(60, 5)):
    model = Sequential()
    model.add(LSTM(50, return_sequences=True, input_shape=input_shape))
    model.add(LSTM(50, return_sequences=False))
    model.add(Dense(25))
    model.add(Dense(1))
    model.compile(optimizer='adam', loss='mean_squared_error')
    return model  # 모델 반환 추가

#롤링 함수
def rolling_forecast(model, data, window_size=60, correlation=None):
    predictions = []
    current_batch = data[-window_size:].copy()  # window_size를 60으로 조정

    for i in range(60):  # 60일 동안 예측 (window_size와 일치)
        current_batch_expanded = np.expand_dims(current_batch, axis=0)

        # 모델의 입력에 맞춰 형태 조정 (6개의 특성을 5개로 조정할 필요가 있음)
        # 여기에서 추가적인 조정이 필요할 수 있음
        current_batch_for_prediction = current_batch_expanded[:, :, :5]  # 상위 5개의 특성만 사용

        current_pred = model.predict(current_batch_for_prediction)
        predictions.append(current_pred[0, 0])
        current_batch = np.roll(current_batch, -1, axis=0)
        current_batch[-1, :-1] = current_pred

    return predictions


# 모델 구축 및 할당
nasdaq_model = build_lstm_model()
bitcoin_model = build_lstm_model()

# 모델 훈련
nasdaq_model.fit(nasdaq_X, nasdaq_y, epochs=10, batch_size=32)
bitcoin_model.fit(bitcoin_X, bitcoin_y, epochs=10, batch_size=32)

# 롤링 예측 수행
nasdaq_predictions = rolling_forecast(nasdaq_model, nasdaq_scaled)
bitcoin_predictions = rolling_forecast(bitcoin_model, bitcoin_scaled)

# 캔들차트로 시각화 함수
def plot_candlestick_chart(data, title="Stock Price"):
    mpf.plot(data, type='candle', mav=(3,6,9), volume=True, title=title)

# 실제 데이터와 예측 데이터 결합 및 시각화
nasdaq_combined = nasdaq_data.copy()
nasdaq_combined['Predictions'] = np.nan
nasdaq_combined.loc[nasdaq_combined.index[-len(nasdaq_predictions):], 'Predictions'] = nasdaq_predictions
plot_candlestick_chart(nasdaq_combined, "NASDAQ Stock Price")

bitcoin_combined = bitcoin_data.copy()
bitcoin_combined['Predictions'] = np.nan
bitcoin_combined.loc[bitcoin_combined.index[-len(bitcoin_predictions):], 'Predictions'] = bitcoin_predictions
plot_candlestick_chart(bitcoin_combined, "Bitcoin Price")

# 교차 검증을 위한 함수
def cross_validation(model, X, y, n_splits=5):
    kf = KFold(n_splits=n_splits)
    mse_scores = []
    for train_index, test_index in kf.split(X):
        X_train, X_test = X[train_index], X[test_index]
        y_train, y_test = y[train_index], y[test_index]
        model.fit(X_train, y_train, epochs=1, batch_size=32, verbose=0)
        predictions = model.predict(X_test)
        mse_scores.append(mean_squared_error(y_test, predictions))
    return np.mean(mse_scores)

# 교차 검증 및 오차 범위 계산
nasdaq_model = build_lstm_model()
bitcoin_model = build_lstm_model()

nasdaq_mse = cross_validation(nasdaq_model, nasdaq_X, nasdaq_y)
bitcoin_mse = cross_validation(bitcoin_model, bitcoin_X, bitcoin_y)

# 교차 검증 결과를 반영하여 모델 재조정
def retrain_model(model, X, y, mse):
    new_learning_rate = 0.001 / mse
    model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=new_learning_rate), loss='mean_squared_error')
    model.fit(X, y, epochs=5, batch_size=32, verbose=0)
    return model

nasdaq_model = retrain_model(nasdaq_model, nasdaq_X, nasdaq_y, nasdaq_mse)
bitcoin_model = retrain_model(bitcoin_model, bitcoin_X, bitcoin_y, bitcoin_mse)

# 모델 구축 및 훈련
nasdaq_model = build_lstm_model()
bitcoin_model = build_lstm_model()

nasdaq_model.fit(nasdaq_X, nasdaq_y, epochs=10, batch_size=32)
bitcoin_model.fit(bitcoin_X, bitcoin_y, epochs=10, batch_size=32)

# 비트코인의 미래 예측 (2023년 11월 24일부터 2024년 12월 31일까지)
future_start_date = '2023-11-24'
future_end_date = '2024-12-31'
future_dates = pd.date_range(start=future_start_date, end=future_end_date)

# 예측을 위한 데이터 생성 (기존 데이터의 마지막 부분을 사용)
last_data_point = bitcoin_scaled[-1:]
future_bitcoin_predictions = []

for _ in range(len(future_dates)):
    current_batch_expanded = np.expand_dims(last_data_point, axis=0)
    current_pred = bitcoin_model.predict(current_batch_expanded)
    future_bitcoin_predictions.append(current_pred[0, 0])
    last_data_point = np.roll(last_data_point, -1, axis=0)
    last_data_point[-1, -1] = current_pred[0, 0]  # 수정: 2D 배열에서 특정 위치에 값을 할당

# 예측 결과를 포함하는 새로운 Series 생성
future_bitcoin_series = pd.Series(index=future_dates, data=future_bitcoin_predictions)

# 실제 비트코인 데이터와 예측 데이터 결합 및 시각화
bitcoin_combined = bitcoin_data.copy()
bitcoin_combined['Predictions'] = np.nan
bitcoin_combined.loc[bitcoin_combined.index[-len(bitcoin_predictions):], 'Predictions'] = bitcoin_predictions

# 예측값을 데이터프레임에 할당할 때 인덱스를 일치시킵니다.
bitcoin_future_combined = bitcoin_future_combined.reindex(future_dates)

# 예측값을 데이터프레임에 할당
bitcoin_future_combined['Predictions'] = future_bitcoin_predictions

# 결측값을 제외하고 캔들차트를 그립니다.
bitcoin_combined_without_nan = bitcoin_combined.dropna()
plot_candlestick_chart(bitcoin_combined_without_nan, "Bitcoin Future Price Prediction")



