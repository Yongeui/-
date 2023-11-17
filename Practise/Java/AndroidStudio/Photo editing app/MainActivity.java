package com.example.test01;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.Paint;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.LinearLayout;

public class MainActivity extends AppCompatActivity {

    ImageButton ibZoomin, ibZoomout, ibRotate, ibBright, ibDark, ibGray;
    MyGraphicView graphicView;

    static float scaleX = 1, scaleY = 1;
    static float angle = 0;
    static float color = 1;
    static float satur = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("미니 포토샵 앱 만들기");

        LinearLayout pictureLayout = findViewById(R.id.pictureLayout);
        graphicView = new MyGraphicView(this);
        pictureLayout.addView(graphicView);

        clickIcons();
    }

    private void clickIcons() {
        ibZoomin = findViewById(R.id.ibZoomin);
        ibZoomin.setContentDescription("Zoom In");
        ibZoomin.setOnClickListener(v -> {
            scaleX += 0.2f;
            scaleY += 0.2f;
            graphicView.invalidate();
        });

        ibZoomout = findViewById(R.id.ibZoomout);
        ibZoomout.setContentDescription("Zoom Out");
        ibZoomout.setOnClickListener(v -> {
            scaleX -= 0.2f;
            scaleY -= 0.2f;
            graphicView.invalidate();
        });

        ibRotate = findViewById(R.id.ibRotate);
        ibRotate.setContentDescription("Rotate");
        ibRotate.setOnClickListener(v -> {
            angle += 20;
            graphicView.updateMatrix();
            graphicView.invalidate();
        });

        ibBright = findViewById(R.id.ibBright);
        ibBright.setContentDescription("Bright");
        ibBright.setOnClickListener(v -> {
            color += 0.2f;
            graphicView.updateMatrix();
            graphicView.invalidate();
        });

        ibDark = findViewById(R.id.ibDark);
        ibDark.setContentDescription("Dark");
        ibDark.setOnClickListener(v -> {
            color -= 0.2f;
            graphicView.updateMatrix();
            graphicView.invalidate();
        });

        ibGray = findViewById(R.id.ibGray);
        ibGray.setContentDescription("Gray");
        ibGray.setOnClickListener(v -> {
            satur = (satur == 0) ? 1 : 0;
            graphicView.updateMatrix();
            graphicView.invalidate();
        });
    }

    private static class MyGraphicView extends View {
        private final Bitmap picture;
        private final Paint paint;
        private final ColorMatrix cm;

        public MyGraphicView(Context context) {
            super(context);
            picture = BitmapFactory.decodeResource(getResources(), R.drawable.lena256);
            paint = new Paint();
            paint.setAntiAlias(true);
            cm = new ColorMatrix();
            updateMatrix();
        }

        public void updateMatrix() {
            cm.set(new float[]{
                    color, 0, 0, 0, 0,
                    0, color, 0, 0, 0,
                    0, 0, color, 0, 0,
                    0, 0, 0, 1, 0
            });

            if (satur == 0) {
                cm.setSaturation(satur);
            }

            paint.setColorFilter(new ColorMatrixColorFilter(cm));
        }

        @Override
        protected void onDraw(Canvas canvas) {
            super.onDraw(canvas);

            int cenX = this.getWidth() / 2;
            int cenY = this.getHeight() / 2;
            canvas.scale(scaleX, scaleY, cenX, cenY);
            canvas.rotate(angle, cenX, cenY);

            int picX = (this.getWidth() - picture.getWidth()) / 2;
            int picY = (this.getHeight() - picture.getHeight()) / 2;
            canvas.drawBitmap(picture, picX, picY, paint);
        }

        @Override
        protected void onDetachedFromWindow() {
            super.onDetachedFromWindow();
            if (picture != null) {
                picture.recycle();
            }
        }
    }
}
