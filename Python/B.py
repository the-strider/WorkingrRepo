#importing the module 
from pytube import YouTube 

#where to save 
SAVE_PATH = "/home/lowjack/Videos" #to_do 

#link of the video to be downloaded 
links = [
	"https://www.youtube.com/watch?v=Q1RHLErAWsk&list=PL-nbe4FPvDBElyW0Iww5suxJqqmuGBgIH&index=8",
	"https://www.youtube.com/watch?v=vl5Fi5mHK-Q&list=PL-nbe4FPvDBElyW0Iww5suxJqqmuGBgIH&index=9",
	"https://www.youtube.com/watch?v=eZakJqbPwnE&list=PL-nbe4FPvDBElyW0Iww5suxJqqmuGBgIH&index=10",
	"https://www.youtube.com/watch?v=fhIQZqDJkI4&list=PL-nbe4FPvDBElyW0Iww5suxJqqmuGBgIH&index=11",
	"https://www.youtube.com/watch?v=4yddWppPgOU&list=PL-nbe4FPvDBElyW0Iww5suxJqqmuGBgIH&index=12",
	"https://www.youtube.com/watch?v=zw2UxEXM79M&list=PL-nbe4FPvDBElyW0Iww5suxJqqmuGBgIH&index=13",
	"https://www.youtube.com/watch?v=trDdNMp57Xk&list=PL-nbe4FPvDBElyW0Iww5suxJqqmuGBgIH&index=14",
	"https://www.youtube.com/watch?v=GViXQj150nU&list=PL-nbe4FPvDBElyW0Iww5suxJqqmuGBgIH&index=15",
	"https://www.youtube.com/watch?v=wMJ9jNSMRPQ&list=PL-nbe4FPvDBElyW0Iww5suxJqqmuGBgIH&index=16",
	"https://www.youtube.com/watch?v=eBPZM9eyC3Q&list=PL-nbe4FPvDBElyW0Iww5suxJqqmuGBgIH&index=17"
]

for link in links:
	try: 
		#object creation using YouTube which was imported in the beginning 
		yt = YouTube(link) 
	except: 
		print("Connection Error") #to handle exception 

	#filters out all the files with "mp4" extension 
	stream = yt.streams.first()
	stream.download()