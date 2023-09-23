package com.example.mphw4_2;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.graphics.drawable.ColorDrawable;

public class MainActivity extends AppCompatActivity {
    EditText edit1, edit2;
    Button BtnAdd, BtnSub, BtnMul, BtnDiv, BtnMod;
    TextView textResult;
    String num1, num2;
    Double resultDouble;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("초간단 계산기(수정)");
        getSupportActionBar().setDisplayShowHomeEnabled(true);
        getSupportActionBar().setIcon(R.drawable.s12);
        if (getSupportActionBar() != null) {
            getSupportActionBar().setBackgroundDrawable(new ColorDrawable(getResources().getColor(R.color.gblack)));
        }

        edit1 = findViewById(R.id.Edit1);
        edit2 = findViewById(R.id.Edit2);

        BtnAdd = findViewById(R.id.BtnAdd);
        BtnSub = findViewById(R.id.BtnSub); // Fix reference to BtnSub
        BtnMul = findViewById(R.id.BtnMul);
        BtnDiv = findViewById(R.id.BtnDiv);
        BtnMod = findViewById(R.id.BtnMod);

        textResult = findViewById(R.id.TextResult);

        BtnAdd.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                num1 = edit1.getText().toString();
                num2 = edit2.getText().toString();
                if (num1.isEmpty() || num2.isEmpty()) {
                    Toast.makeText(MainActivity.this, "값을 입력해주세요.", Toast.LENGTH_SHORT).show();
                    return;
                }
                resultDouble = Double.parseDouble(num1) + Double.parseDouble(num2);
                textResult.setText("계산 결과 : " + resultDouble);
            }
        });

        BtnSub.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                num1 = edit1.getText().toString();
                num2 = edit2.getText().toString();
                if (num1.isEmpty() || num2.isEmpty()) {
                    Toast.makeText(MainActivity.this, "값을 입력해주세요.", Toast.LENGTH_SHORT).show();
                    return;
                }
                resultDouble = Double.parseDouble(num1) - Double.parseDouble(num2);
                textResult.setText("계산 결과 : " + resultDouble);
            }
        });

        BtnMul.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                num1 = edit1.getText().toString();
                num2 = edit2.getText().toString();
                if (num1.isEmpty() || num2.isEmpty()) {
                    Toast.makeText(MainActivity.this, "값을 입력해주세요.", Toast.LENGTH_SHORT).show();
                    return;
                }
                resultDouble = Double.parseDouble(num1) * Double.parseDouble(num2);
                textResult.setText("계산 결과 : " + resultDouble);
            }
        });

        BtnDiv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                num1 = edit1.getText().toString();
                num2 = edit2.getText().toString();
                if (num1.isEmpty() || num2.isEmpty()) {
                    Toast.makeText(MainActivity.this, "값을 입력해주세요.", Toast.LENGTH_SHORT).show();
                    return;
                }

                double divisor = Double.parseDouble(num2);
                if (divisor == 0.0) {
                    Toast.makeText(MainActivity.this, "0으로 나눌 수 없습니다.", Toast.LENGTH_SHORT).show();
                    return;
                }
                resultDouble = Double.parseDouble(num1) / divisor;
                textResult.setText("계산 결과 : " + resultDouble);
            }
        });

        BtnMod.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                num1 = edit1.getText().toString();
                num2 = edit2.getText().toString();
                if (num1.isEmpty() || num2.isEmpty()) {
                    Toast.makeText(MainActivity.this, "값을 입력해주세요.", Toast.LENGTH_SHORT).show();
                    return;
                }

                double divisor = Double.parseDouble(num2);
                if (divisor == 0.0) {
                    Toast.makeText(MainActivity.this, "0으로 나눌 수 없습니다.", Toast.LENGTH_SHORT).show();
                    return;
                }
                resultDouble = Double.parseDouble(num1) % divisor;
                textResult.setText("계산 결과 : " + resultDouble);
            }
        });
    }
}
