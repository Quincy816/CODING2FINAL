# Coding 2 Final Procject
Name: Qian Xu

Student number: 22018776

E-mail:q.xu0320222@arts.ac.uk

# Video Link
Here is the link to my presentation video from Panopto:
https://ual.cloud.panopto.eu/Panopto/Pages/Viewer.aspx?id=f62e8113-6524-497c-80ee-afc6016c24a3&start=0


# Introduction

Hello mate, this is Readme file of my coding2 final project. I made an audio visualization program based on my favorite song using OpenFramework. The project uses the libraries included in OpenFramework and OfxOpenCV library.

I first created a 3D graphics stack with particles, then imported and processed audio using the ofSoundplayer function, and integrated the parsed data into a function that controls the size of a sphere group. Next, I created a frequency map based on the music data and converted it into columns arranged in a circle. After verifying that they all worked properly, I made a sphere, created its surface using a grid, and made it change with the music, merging the two pieces of code together. 

Then, I added the ofVideoGrabber function to capture images from the computer camera and used OfxOpenCV to analyse the changes in the images, linking them to the song's playback speed.

# Process Record

During the process of creating this project, I encountered many difficulties, but I learned a lot of new knowledge by solving them step by step. At first, I only had a rough idea of wanting to create a music visualization project, but inspired by my classmates, I decided to add the function of capturing camera images to enrich my project.

I watched many tutorials on creating 3D grids, but almost none of them had the effect I needed. After many attempts, I decided to start with something simple. I used the knowledge I learned last semester to create a cube that enlarges and shrinks with the rhythm of the music. Then, I turned it into a particle heap and replaced it with a noise-controlled mesh sphere I learned in the Perlin noise tutorial video. After ensuring that its appearance was the effect I wanted, I felt that its changes were still not intuitive enough. So, I searched the internet for some music visualization examples and found that the most commonly used approach was to create a dynamic 2D frequency map. To make it match my project, I converted the parameters of the 2D frequency map into some 3D pillars and placed them around the sphere I created, adjusting their size and position to make them look like a planet and a planetary belt.

After all of these tasks were completed, I decided to add camera capture and recognition functions. This is where I encountered my biggest difficulty. At first, everything went smoothly, but when I wanted to perform skeletal capture, I ran into difficulties. The functions of the OfxOpenCV library in OpenFramework were not enough to support this operation, and I needed to use the OpenCV library in Python for computation. So, I tried to write a computation program in Python and attempted to communicate between them through OSC, but I encountered difficulties with the computer configuration, rendering all my efforts in vain. Therefore, I asked for Adam's advice, and he told me to simplify the problem as much as possible and try to complete the computation using the simplest method, such as trying to run the entire program with OpenFramework.

So, I gave up on the idea of calculating the length of the skeleton and instead tried to calculate the coordinates of the centre point of the largest image using simple computation methods. This way, I could roughly transmit some information by detecting changes in camera movements, but I couldn't achieve the effect of controlling the image with finger movements that I had hoped for before. After some time and effort, I succeeded, and the program ran quite well, but it required some significant movements for the computer to recognize them, and the running speed was somewhat slow due to the many algorithms and image display codes in the program.

Furthermore, during the coding process, I encountered some small difficulties that I overcame. For example, the default libraries were unable to solve some problems, so I had to manually import some libraries and learn how to use them. Additionally, there were issues with image display because there were many parts in my draw function, and they had a certain order that needed to be arranged properly for the image to be displayed correctly. Initially, I didn't understand why the colour of each part was the same, but after questioning and reflection, I realized that I needed to reset the colour before drawing each part because the code compilation had a strict sequence.


# Project Summary

The changes in music are controlled by images in the camera, indirectly controlling the visualized grid of the song. This allows us to freely use our bodies to control everything. When we are still, the music and images play at a normal speed, but when we move, they begin to change. The faster our movements, the stronger the distortion in the music and images. Typically, we dance to the beat of the music, but in my project, the music changes with the beat of our dance, which is its highlight. The changes in the images also enhance the visual effects.


In conclusion, I combined the knowledge of creating a 3D world and controlling sound that I learned last year with the knowledge I gained this semester to create some new gameplay, such as using real-time images to control my work.

After solving one problem, encountering a new problem makes the previous difficulties seem insignificant. When the code successfully runs, my mood soars.

This assignment was a significant improvement for me because I almost independently solved all the problems and learned many extracurricular skills on the basis of mastering the in-class knowledge.

Last but not least, I would like to thank all the teachers and classmates who have helped me, as well as myself for persevering all the time.

