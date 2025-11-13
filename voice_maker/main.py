from pydub import AudioSegment
import random

input_file = input('input file: ')
output_file = input('output file: ')
segment_duration = 300
    
audio = AudioSegment.from_file(input_file)

segments = [audio[i:i + segment_duration] for i in range(0, len(audio), segment_duration)]

random.shuffle(segments)

for i in range(len(segments) // 2):
    segments[i] = segments[i].reverse()

processed_audio = sum(segments)

processed_audio.export(output_file, format = "mp3")
print(f"{output_file} saved")