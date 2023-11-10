from PIL import Image
import os

def convert_png_to_bmp(input_folder, output_folder):
    files = os.listdir(input_folder)
    for file in files:
        if file.lower().endswith('.png'):
            png_image = Image.open(os.path.join(input_folder, file))
            output_path = os.path.join(output_folder, os.path.splitext(file)[0] + ".bmp")
            png_image.save(output_path)

            print(f"Converted: {file} to BMP")
            
            
input_folder_path = 'C:/Users/Namo/Documents/Python/Gif Shit/pngs'
output_folder_path = 'C:/Users/Namo/Documents/Python/Gif Shit/bmps'
convert_png_to_bmp(input_folder_path, output_folder_path)
