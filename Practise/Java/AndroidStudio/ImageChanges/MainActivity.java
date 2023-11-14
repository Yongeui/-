package com.example.test01;

import android.os.Bundle;
import androidx.appcompat.app.AppCompatActivity;
import android.widget.Button;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private myPictureView myPicture;
    private TextView tvNumber;
    private int curNum = 0;
    private File[] imageFiles;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle(R.string.image_viewer_title); // Using string resource for title

        if (getSupportActionBar() != null) {
            getSupportActionBar().setDisplayShowHomeEnabled(true);
            getSupportActionBar().setIcon(R.drawable.s12); // Assuming you have an icon named s12 in drawable
        }

        Button btnPrev = findViewById(R.id.btnPrev);
        Button btnNext = findViewById(R.id.btnNext);
        myPicture = findViewById(R.id.myPictureView1);
        tvNumber = findViewById(R.id.tvNumber);

        File imagesDir = getFilesDir(); // Using the internal storage directory
        imageFiles = imagesDir.listFiles(file -> file.isFile() && file.getName().endsWith(".png"));

        if (imageFiles != null && imageFiles.length > 0) {
            displayImage(curNum); // Display the first image
        } else {
            tvNumber.setText(R.string.no_images); // Using string resource for no images text
        }

        btnPrev.setOnClickListener(v -> {
            if (isImagesAvailable()) {
                curNum = (curNum - 1 + imageFiles.length) % imageFiles.length;
                displayImage(curNum);
            }
        });

        btnNext.setOnClickListener(v -> {
            if (isImagesAvailable()) {
                curNum = (curNum + 1) % imageFiles.length;
                displayImage(curNum);
            }
        });
    }

    private void displayImage(int imageIndex) {
        if (isImagesAvailable()) {
            String imageFname = imageFiles[imageIndex].getAbsolutePath();
            myPicture.setImagePath(imageFname);
            String imageInfo = getString(R.string.image_info, imageIndex + 1, imageFiles.length);
            tvNumber.setText(imageInfo);
        }
    }

    private boolean isImagesAvailable() {
        return imageFiles != null && imageFiles.length > 0;
    }
}
