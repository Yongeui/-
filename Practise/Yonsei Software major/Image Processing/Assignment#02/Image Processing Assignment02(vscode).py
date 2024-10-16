import os
from PIL import Image
import matplotlib.pyplot as plt
import numpy as np

class Histogram:
    def __init__(self, image_path):
        self.image_path = image_path
        if os.path.isfile(image_path):
            self.image = Image.open(image_path).convert("L")
            self.array_image = np.array(self.image)
            self.pixel_num = [0] * 256
            for pixel in self.array_image.flatten():
                self.pixel_num[pixel] += 1
        else:
            print(f"Error: Cannot find or open {image_path}.")
            exit()

    def display_original(self):
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))
        ax1.bar(range(256), self.pixel_num, color='black', width=1.0)
        ax1.set_title('Original Histogram')
        ax1.set_xlabel('Pixel value')
        ax1.set_ylabel('Frequency')
        ax1.set_xlim([0, 255])

        ax2.imshow(self.image, cmap='gray')
        ax2.set_title('Original Image')
        ax2.axis('off')
        plt.show()

    def perform_equalization(self):
        histogram = np.array(self.pixel_num)
        cdf = np.cumsum(histogram)
        cdf_normalized = ((cdf - cdf.min()) * 255) / (cdf.max() - cdf.min())
        equalized_image = cdf_normalized[self.array_image.flatten()].astype(np.uint8).reshape(self.array_image.shape)
        equalized_histogram = [0] * 256
        for pixel in equalized_image.flatten():
            equalized_histogram[pixel] += 1

        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))
        ax1.bar(range(256), equalized_histogram, color='black', width=1.0)
        ax1.set_title('Equalization Histogram')
        ax1.set_xlabel('Pixel value')
        ax1.set_ylabel('Frequency')
        ax1.set_xlim([0, 255])

        ax2.imshow(equalized_image, cmap='gray')
        ax2.set_title('Equalized Image')
        ax2.axis('off')
        plt.show()

    def perform_contrast_stretching(self):
        low, high = np.min(self.array_image), np.max(self.array_image)
        stretched_image = ((self.array_image - low) / (high - low) * 255).astype(np.uint8)
        stretched_histogram = [0] * 256
        for pixel in stretched_image.flatten():
            stretched_histogram[pixel] += 1

        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))
        ax1.bar(range(256), stretched_histogram, color='black', width=1.0)
        ax1.set_title('Basic Contrast Stretching Histogram')
        ax1.set_xlabel('Pixel value')
        ax1.set_ylabel('Frequency')
        ax1.set_xlim([0, 255])

        ax2.imshow(stretched_image, cmap='gray')
        ax2.set_title('Contrast Stretched Image')
        ax2.axis('off')
        plt.show()

    def perform_ends_in_stretching(self):
        low, high = 30, 200
        clipped_image = np.clip(self.array_image, low, high)
        stretched_image = ((clipped_image - low) / (high - low) * 255).astype(np.uint8)
        stretched_histogram = [0] * 256
        for pixel in stretched_image.flatten():
            stretched_histogram[pixel] += 1

        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))
        ax1.bar(range(256), stretched_histogram, color='black', width=1.0)
        ax1.set_title('End-in Contrast Stretching Histogram')
        ax1.set_xlabel('Pixel value')
        ax1.set_ylabel('Frequency')
        ax1.set_xlim([0, 255])

        ax2.imshow(stretched_image, cmap='gray')
        ax2.set_title('End-in Stretched Image')
        ax2.axis('off')
        plt.show()

    def menu(self):
        options = {
            '1': self.display_original,
            '2': self.perform_equalization,
            '3': self.perform_contrast_stretching,
            '4': self.perform_ends_in_stretching
        }
        while True:
            print("\nMenu:")
            print("1. Display Original")
            print("2. Perform Histogram Equalization")
            print("3. Perform Basic Contrast Stretching")
            print("4. Perform Ends-in Stretching")
            print("5. Exit")
            choice = input("Enter choice: ")
            if choice == '5':
                print("Exiting.")
                break
            elif choice in options:
                options[choice]()
            else:
                print("Invalid choice. Please choose again.")

if __name__ == "__main__": #image_path에서 lena.bmp가 있는 경로로 수정.
    image_path = r'C:\Users\82109\OneDrive\바탕 화면\영처과제\Assignment#02\Assignment#02\lena_bmp_512x512_new.bmp'
    histogram_processor = Histogram(image_path)
    histogram_processor.menu()
