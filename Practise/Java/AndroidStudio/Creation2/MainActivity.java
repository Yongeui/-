package com.example.test;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;

public class MainActivity extends AppCompatActivity {

    EditText editText;
    Button change;
    RadioButton rdoCel, rdoFah;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        editText = findViewById(R.id.edtText);
        rdoCel = findViewById(R.id.celsius);
        rdoFah = findViewById(R.id.fahrenheit);
        change = findViewById(R.id.change);

        change.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String input = editText.getText().toString();

                if (rdoCel.isChecked()) {
                    float celsiusValue = Float.parseFloat(input);
                    float fahrenheitConverted = convertCTF(celsiusValue);
                    editText.setText(String.valueOf(fahrenheitConverted));

                    rdoCel.setChecked(false);
                    rdoFah.setChecked(true);
                } else if (rdoFah.isChecked()) {
                    float fahrenheitValue = Float.parseFloat(input);
                    float celsiusConverted = convertFTC(fahrenheitValue);
                    editText.setText(String.valueOf(celsiusConverted));

                    rdoCel.setChecked(true);
                    rdoFah.setChecked(false);
                }
            }
        });
    }

    private float convertFTC(float f) {
        return ((f-32) * 5 / 9);
    }

    private float convertCTF(float c) {
        return ((c * 9) / 5) + 32;
    }
}
