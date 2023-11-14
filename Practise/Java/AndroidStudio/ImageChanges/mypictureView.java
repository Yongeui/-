package com.example.test01;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import androidx.annotation.Nullable;
import android.util.AttributeSet;
import android.view.View;

public class myPictureView extends View {
    @SuppressWarnings("FieldCanBeLocal")
    private String imagePath = null;
    private Bitmap bitmap = null;

    public myPictureView(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public void setImagePath(String path) {
        imagePath = path;
        // 기존에 로드된 비트맵이 있다면 메모리 해제
        if (bitmap != null) {
            bitmap.recycle();
            bitmap = null;
        }
        // 새 이미지 경로에 대한 비트맵 로드
        if (imagePath != null) {
            bitmap = BitmapFactory.decodeFile(imagePath);
        }
        // onDraw를 호출하기 위해 뷰를 무효화
        invalidate();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        // 로드된 비트맵이 있다면 캔버스에 그림
        if (bitmap != null && !bitmap.isRecycled()) {
            canvas.drawBitmap(bitmap, 0, 0, null);
        }
    }
}

