!pip install pandas numpy scikit-learn torch joblib matplotlib seaborn

위 라이브러리 중 설치되어있지 않는 것은 별도로 설치해야합니다 귀찮으시면 그냥 위에꺼

복사하셔서 실행시키시면 됩니다.

압축파일 위치

테스트 코드
	┗colums.pkl , label_encoder.pkl, scaler.pkl, train_model.pth,
	   Test_model.ipynb, test-set.csv, submission_sampel.csv

학습 코드 및 모델
	┗Train_model.ipynb, training-set

==========================================================
※※※※※※※※※※※※※※※※※※Colab 실행 과정※※※※※※※※※※※※※※※※※※※※※※※
==========================================================
(1) 드라이브 마운트 후에 코랩 Drive에 MyDrive 에 Colab NoteBooks
    들어가셔서 Test, Train모델 파일 붙여 넣어주시면 됩니다. 

(2) MyDrive에 "실습"이라는 이름의 파일 하나만들어주시고 training-set.csv
     와 test-set.csv 데이터셋 붙여 넣어주시면 됩니다.

(3) MyDrive에 "result"이라는 이름의 파일 하나 만들어주시고 columns.pkl
     label_encoder.pkl, scaler.pkl, train_model.pth 붙여 넣어주시면 됩니다.

(4) 실행 시키면 됩니다. 예측값이 저장되는 위치는 "result"입니다.

Drive 
     ┗MyDrive
          │	   ┗Colab Notebooks
          │			├Test_model.ipynb
          │			┗Train_model.ipynb
          ├──실습
          │	        ├training-set.csv
          │         ┗test-set.csv
          │          
          ┗─────result
		     ├columns.pkl
		     ├label_encoder.pkl
		     ├scaler.pkl
		     ┗train_model.pth
==========================================================
==========================================================
==========================================================