package com.example.mphw4_2;

//안드로이드 프레임워크에서 필요한 패키지들을 가져온다.
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;
import android.graphics.drawable.ColorDrawable;
import java.util.Locale;

// MainActivity 클래스는 앱의 주 화면을 담당하는 액티비티입니다.
public class MainActivity extends AppCompatActivity {
    // 사용자의 입력과 결과를 표시하는 위젯 변수들을 선언합니다.
    EditText edit1, edit2;
    Button BtnAdd, BtnSub, BtnMul, BtnDiv, BtnMod;
    TextView textResult;

    // 결과값 포맷팅. 소수점 밑 10자리까지 표현하거나, 2자리로 줄이거나 정수로 표현하는 로직
    private String formatResult(double result) {
        // 여기서는 연산 결과가 소수점 아래에만 있고, 소수점 아래가 10자리 이상일 때 포맷팅하는 코드가 필요하다.
        // 예를 들어, 0.00000000001는 0으로 출력되어야하며, 1.234567891011은 1.23로 출력되어야 한다.
        if (result == (int) result) {
            return String.valueOf((int) result);
        } else {
            String formattedResult = String.format(Locale.US, "%.10f", result);
            String decimals = formattedResult.split("\\.")[1];
            boolean isPatternRepeated = false;
            for (int i = 0; i < decimals.length() - 1; i++) {
                if (decimals.charAt(i) == decimals.charAt(i + 1)) {
                    isPatternRepeated = true;
                    break;
                }
            }

            if (!isPatternRepeated) {
                formattedResult = String.format(Locale.US, "%.2f", result);
            }

            while (formattedResult.charAt(formattedResult.length() - 1) == '0') {
                formattedResult = formattedResult.substring(0, formattedResult.length() - 1);
            }

            if (formattedResult.endsWith(".")) {
                return formattedResult.substring(0, formattedResult.length() - 1);
            }

            return formattedResult;
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("초간단 계산기(수정)");

        if (getSupportActionBar() != null) {
            getSupportActionBar().setDisplayShowHomeEnabled(true);
            getSupportActionBar().setIcon(R.drawable.s12);
            getSupportActionBar().setBackgroundDrawable(new ColorDrawable(getResources().getColor(R.color.gblack)));
        }

        edit1 = findViewById(R.id.Edit1);
        edit2 = findViewById(R.id.Edit2);
        BtnAdd = findViewById(R.id.BtnAdd);
        BtnSub = findViewById(R.id.BtnSub);
        BtnMul = findViewById(R.id.BtnMul);
        BtnDiv = findViewById(R.id.BtnDiv);
        BtnMod = findViewById(R.id.BtnMod);
        textResult = findViewById(R.id.TextResult);

        BtnAdd.setOnClickListener(this::add);
        BtnSub.setOnClickListener(this::subtract);
        BtnMul.setOnClickListener(this::multiply);
        BtnDiv.setOnClickListener(this::divide);
        BtnMod.setOnClickListener(this::modulo);
    }

    @SuppressWarnings("Convert2MethodRef")
    private void add(View view) {
         /*덧셈의 패턴 add 메서드의 람다 표현식은 Double::sum 메서드 참조와 유사하기
        때문에 Lambda can be replaced with method reference 발생, 다른 연산은
        자바의 Double 클래스에 해당하는 메서드 참조가 없기 때문에 경고가 발생하지 않는다.*/
        performCalculation((n1, n2) -> n1 + n2);
    }

    private void subtract(View view) {
        performCalculation((n1, n2) -> n1 - n2);
    }

    private void multiply(View view) {
        performCalculation((n1, n2) -> n1 * n2);
    }

    private void divide(View view) {
        if (areInputsInvalid()) {
            return;
        }
        String num2 = edit2.getText().toString();
        if (Double.parseDouble(num2) == 0.0) {
            Toast.makeText(MainActivity.this, R.string.divide_by_zero_error, Toast.LENGTH_SHORT).show();
            return;
        }
        performCalculation((n1, n2) -> n1 / n2);
    }

    private void modulo(View view) {
        performModuloOperation();
    }

    @FunctionalInterface
    private interface Calculation {
        double perform(double n1, double n2);
        // 이 함수형 인터페이스는 두 숫자를 받아 연산한 후 결과를 반환한다.
    }

    // 입력값 유효성 검사: 두 EditText 필드가 비어있지 않은지 검사
    private boolean areInputsInvalid() {
        String num1 = edit1.getText().toString();
        String num2 = edit2.getText().toString();
        if (num1.isEmpty() || num2.isEmpty()) {
            Toast.makeText(MainActivity.this, R.string.enter_values_error, Toast.LENGTH_SHORT).show();
            return true;
        }
        return false;
    }

    private void displayResult(double result) {
        textResult.setText(getString(R.string.calculation_output, formatResult(result)));
    }

    // performCalculation 메서드는 특정 연산을 수행한 후 그 결과를 화면에 표시한다.
    private void performCalculation(Calculation calculation) {
        if (areInputsInvalid()) {
            return;
        }
        double num1 = Double.parseDouble(edit1.getText().toString());
        double num2 = Double.parseDouble(edit2.getText().toString());
        double result = calculation.perform(num1, num2);
        displayResult(result);
    }

    private void performModuloOperation() {
        if (areInputsInvalid()) {
            return;
        }

        double dblNum1 = Double.parseDouble(edit1.getText().toString());
        double dblNum2 = Double.parseDouble(edit2.getText().toString());

        if (dblNum2 == 0.0) {
            Toast.makeText(MainActivity.this, R.string.divide_by_zero_error, Toast.LENGTH_SHORT).show();
            return;
        }

        if (dblNum1 == (int)dblNum1 && dblNum2 == (int)dblNum2) {
            int intNum1 = (int) dblNum1;
            int intNum2 = (int) dblNum2;
            int resultInt = intNum1 % intNum2;
            textResult.setText(getString(R.string.calculation_output, String.valueOf(resultInt)));
        } else {
            double result = dblNum1 % dblNum2;
            displayResult(result);
        }
    }
}
