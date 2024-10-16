import os
from PIL import Image
import matplotlib.pyplot as plt
import numpy as np
import ipywidgets as widgets
from IPython.display import display

from google.colab import drive
drive.mount('/content/drive')

class Histogram:
    def __init__(self, root_dir):
        super().__init__()
        print('Image Processing Assignment02 \n')

        self.image_name = 'lena_bmp_512x512_new.bmp'
        self.image_path = os.path.join(root_dir, self.image_name)

        if os.path.isfile(self.image_path):
            self.lena = Image.open(self.image_path).convert("L")
            self.array_lena = np.array(self.lena)
            self.bright_hist = list(range(256))
            self.pixel_num = [0] * 256
            for pixel in self.array_lena.flatten():
                self.pixel_num[pixel] += 1
        else:
            print(f"Error: Cannot find or open {self.image_path}.")
            return

    def plot_histogram(self, data, title, ax):
        ax.bar(self.bright_hist, data, color='black', width=1.0)
        ax.set_title(title)
        ax.set_xlabel('Pixel value')
        ax.set_ylabel('Frequency')
        ax.set_xlim([0, 255])


    def show_image(self, image, title, ax):
        ax.imshow(image, cmap='gray')
        ax.set_title(title)
        ax.axis('off')

    def histo_1(self):
        fig, ax = plt.subplots(1, 2, figsize=(12, 6))
        self.plot_histogram(self.pixel_num, 'Original Histogram', ax[0])
        self.show_image(self.array_lena, 'Original Image', ax[1])
        plt.show()

    def histo_2(self):
        histogram = np.array(self.pixel_num)
        cdf = np.cumsum(histogram)
        sk = np.round(cdf / cdf[-1] * 255).astype(np.uint8)
        equalized_image = sk[self.array_lena]
        equalized_histogram = [0] * 256
        for pixel in equalized_image.flatten():
            equalized_histogram[pixel] += 1
        fig, ax = plt.subplots(1, 2, figsize=(12, 6))
        self.plot_histogram(equalized_histogram, 'Equalization Histogram', ax[0])
        self.show_image(equalized_image, 'Equalization Image', ax[1])
        plt.show()

    def histo_3(self):
        low = np.min(self.array_lena)
        high = np.max(self.array_lena)
        stretched_image = ((self.array_lena - low) / (high - low) * 255).astype(np.uint8)
        stretched_histogram = [0] * 256
        for pixel in stretched_image.flatten():
            stretched_histogram[pixel] += 1
        fig, ax = plt.subplots(1, 2, figsize=(12, 6))
        self.plot_histogram(stretched_histogram, 'Basic Contrast Stretching', ax[0])
        self.show_image(stretched_image, 'Basic Contrast Stretching Image', ax[1])
        plt.show()

    def histo_4(self):
        low, high = 30, 200
        clipped_image = np.clip(self.array_lena, low, high)
        stretched_image = ((clipped_image - low) / (high - low) * 255).astype(np.uint8)
        stretched_histogram = [0] * 256
        for pixel in stretched_image.flatten():
            stretched_histogram[pixel] += 1
        fig, ax = plt.subplots(1, 2, figsize=(12, 6))
        self.plot_histogram(stretched_histogram, 'End-in Contrast Stretching Histogram', ax[0])
        self.show_image(stretched_image, 'End-in Contrast Stretching Image', ax[1])
        plt.show()

    def display_options(self):
        options = {
            'Original Histogram': self.histo_1,
            'Equalization Histogram': self.histo_2,
            'Basic Contrast Stretching': self.histo_3,
            'End-in Contrast Stretching': self.histo_4,
            'Terminate': self.exit_program
        }
        dropdown = widgets.Dropdown(options=['Original Histogram', 'Equalization Histogram',
                                             'Basic Contrast Stretching', 'End-in Contrast Stretching',
                                             'Terminate'], description='Select Task:')
        
        button = widgets.Button(description="버튼")
        output = widgets.Output()

        display(dropdown, button, output)

        def on_button_clicked(b):
            with output:
                plt.close('all')
                options[dropdown.value]()

        button.on_click(on_button_clicked)

    def exit_program(self):
        print("프로그램이 성공적으로 종료되었습니다.")

root_dir = '/content/drive/MyDrive/Imagecreateive'
histogram_processor = Histogram(root_dir)
histogram_processor.display_options()