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
    current_batch = data[-window_size:].copy()

    for i in range(365):
        # 차원 확장
        current_batch_expanded = np.expand_dims(current_batch, axis=0)

        if correlation is not None:
            additional_feature = np.full((1, current_batch_expanded.shape[1], 1), correlation)
            current_batch_with_corr = np.append(current_batch_expanded, additional_feature, axis=2)
            current_pred = model.predict(current_batch_with_corr)
        else:
            current_pred = model.predict(current_batch_expanded)

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

# 실제 데이터와 예측 데이터의 오차 계산 함수
def calculate_prediction_error(real_data, predicted_data):
    return mean_squared_error(real_data, predicted_data)

# 실제 데이터와 예측 데이터를 비교하여 오차를 계산하고 모델 재훈련
def refine_model_with_real_data(model, real_data, predicted_data, X, y):
    error = calculate_prediction_error(real_data, predicted_data)
    new_learning_rate = 0.001 / error
    model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=new_learning_rate), loss='mean_squared_error')
    model.fit(X, y, epochs=5, batch_size=32, verbose=0)
    return model

# 실제 데이터와 예측 데이터 비교 및 모델 재조정
real_nasdaq_data = nasdaq_data['Close'][-len(nasdaq_predictions):]
real_bitcoin_data = bitcoin_data['Close'][-len(bitcoin_predictions):]

nasdaq_model = refine_model_with_real_data(nasdaq_model, real_nasdaq_data, nasdaq_predictions, nasdaq_X, nasdaq_y)
bitcoin_model = refine_model_with_real_data(bitcoin_model, real_bitcoin_data, bitcoin_predictions, bitcoin_X, bitcoin_y)

# 모델 구축 및 훈련
nasdaq_model = build_lstm_model()
bitcoin_model = build_lstm_model()

nasdaq_model.fit(nasdaq_X, nasdaq_y, epochs=10, batch_size=32)
bitcoin_model.fit(bitcoin_X, bitcoin_y, epochs=10, batch_size=32)

# 비트코인의 미래 예측
future_bitcoin_predictions = rolling_forecast(bitcoin_model, bitcoin_scaled, window_size=365, correlation=correlation)

# 예측 결과를 포함하는 새로운 DataFrame 생성
bitcoin_future_df = pd.DataFrame(index=future_dates, data={'Predictions': future_bitcoin_predictions})

# 실제 비트코인 데이터와 예측 데이터 결합 및 시각화
bitcoin_future_combined = pd.concat([bitcoin_combined, bitcoin_future_df])
plot_candlestick_chart(bitcoin_future_combined, "Bitcoin Future Price Prediction")
