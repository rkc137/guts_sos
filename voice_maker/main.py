from pydub import AudioSegment
import random

# Функция для нарезки, перемешивания и разворачивания
def process_audio(input_file, output_file, segment_duration=300):
    # Загружаем аудиофайл
    audio = AudioSegment.from_file(input_file)
    segment_duration_ms = segment_duration  # Длина отрезка в миллисекундах
    
    # Разбиваем на фрагменты
    segments = [audio[i:i + segment_duration_ms] for i in range(0, len(audio), segment_duration_ms)]
    
    # Перемешиваем фрагменты
    random.shuffle(segments)
    
    # Разворачиваем половину фрагментов
    for i in range(len(segments) // 2):
        segments[i] = segments[i].reverse()
    
    # Объединяем фрагменты в один аудиотрек
    processed_audio = sum(segments)
    
    # Сохраняем результат
    processed_audio.export(output_file, format="mp3")
    print(f"Обработанный файл сохранён как {output_file}")

# Укажите путь к исходному файлу и результату
input_file = "input.mp3"  # Исходный MP3-файл
output_file = "output.mp3"  # Файл с результатом

# Запускаем обработку
process_audio(input_file, output_file)
