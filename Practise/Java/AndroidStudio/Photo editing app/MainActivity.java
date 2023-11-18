package com.example.test01;

import androidx.appcompat.app.AppCompatActivity;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BlurMaskFilter;
import android.graphics.Canvas;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.EmbossMaskFilter;
import android.graphics.Paint;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.LinearLayout;

public class MainActivity extends AppCompatActivity {

    ImageButton ibZoomin, ibZoomout, ibRotate, ibBright, ibDark, ibGray, ibBlur, ibEmboss;
    MyGraphicView graphicView;
    static float scaleX = 1, scaleY = 1;
    static float angle = 0;
    //static float color = 1;
    static float satur = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("미니 포토샵(개선)");

        if (getSupportActionBar() != null) {
            getSupportActionBar().setDisplayShowHomeEnabled(true);
            getSupportActionBar().setIcon(R.drawable.picture);
        }

        LinearLayout pictureLayout = findViewById(R.id.pictureLayout);
        graphicView = new MyGraphicView(this);
        pictureLayout.addView(graphicView);

        clickIcons();
    }

    private void clickIcons() {
        ibZoomin = findViewById(R.id.ibZoomin);
        ibZoomin.setOnClickListener(v -> {
            scaleX += 0.2f;
            scaleY += 0.2f;
            graphicView.invalidate();
        });

        ibZoomout = findViewById(R.id.ibZoomout);
        ibZoomout.setOnClickListener(v -> {
            scaleX -= 0.2f;
            scaleY -= 0.2f;
            graphicView.invalidate();
        });

        ibRotate = findViewById(R.id.ibRotate);
        ibRotate.setOnClickListener(v -> {
            angle += 20;
            graphicView.invalidate();
        });

        ibBright = findViewById(R.id.ibBright);
        ibBright.setContentDescription("채도 높게");
        ibBright.setOnClickListener(v -> {
            satur += 0.2f;
            graphicView.updateMatrix();
            graphicView.invalidate();
        });

        ibDark = findViewById(R.id.ibDark);
        ibDark.setContentDescription("채도 낮게");
        ibDark.setOnClickListener(v -> {
            satur -= 0.2f;
            graphicView.updateMatrix();
            graphicView.invalidate();
        });

        ibGray = findViewById(R.id.ibGray);
        ibGray.setContentDescription("회색으로 설정");
        ibGray.setOnClickListener(v -> {
            satur = (satur == 0) ? 1 : 0;
            graphicView.updateMatrix();
            graphicView.invalidate();
        });

        ibBlur = findViewById(R.id.ibBlur);
        ibBlur.setOnClickListener(v -> {
            graphicView.setBlur(!graphicView.isBlur());
            graphicView.invalidate();
        });

        ibEmboss = findViewById(R.id.ibEmboss);
        ibEmboss.setOnClickListener(v -> {
            graphicView.setEmboss(!graphicView.isEmboss());
            graphicView.invalidate();
        });
    }

    private static class MyGraphicView extends View {
        private final Bitmap picture;
        private final Paint paint, filterPaint;
        private final ColorMatrix cm;
        private BlurMaskFilter blurFilter;
        private EmbossMaskFilter embossFilter;
        private boolean isBlur = false, isEmboss = false;

        public MyGraphicView(Context context) {
            super(context);
            setLayerType(View.LAYER_TYPE_SOFTWARE, null); // Disable hardware acceleration

            picture = BitmapFactory.decodeResource(getResources(), R.drawable.lena256);
            paint = new Paint(Paint.ANTI_ALIAS_FLAG);
            filterPaint = new Paint(Paint.ANTI_ALIAS_FLAG | Paint.FILTER_BITMAP_FLAG);
            cm = new ColorMatrix();
            updateMatrix();
            createFilters();
        }

        private void createFilters() {
            blurFilter = new BlurMaskFilter(15, BlurMaskFilter.Blur.NORMAL);
            embossFilter = new EmbossMaskFilter(new float[]{1, 1, 1}, 0.2f, 8, 15f);
        }

        public void setBlur(boolean blur) {
            this.isBlur = blur;
        }

        public boolean isBlur() {
            return isBlur;
        }

        public void setEmboss(boolean emboss) {
            this.isEmboss = emboss;
        }

        public boolean isEmboss() {
            return isEmboss;
        }

        public void updateMatrix() {
            cm.setSaturation(satur);
            paint.setColorFilter(new ColorMatrixColorFilter(cm));
        }

        @Override
        protected void onDraw(Canvas canvas) {
            int cenX = this.getWidth() / 2;
            int cenY = this.getHeight() / 2;
            canvas.scale(scaleX, scaleY, cenX, cenY);
            canvas.rotate(angle, cenX, cenY);

            if (isBlur) {
                filterPaint.setMaskFilter(blurFilter);
            } else if (isEmboss) {
                filterPaint.setMaskFilter(embossFilter);
            } else {
                filterPaint.setMaskFilter(null);
            }

            canvas.drawBitmap(picture, (float) cenX - picture.getWidth() / 2.0f, (float) cenY - picture.getHeight() / 2.0f, isBlur || isEmboss ? filterPaint : paint);
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
