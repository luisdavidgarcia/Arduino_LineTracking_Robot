# 🚗 Arduino_LineTracking_Robot 🤖

I assembled my first robot and learned how to program it to move, process data, detect objects, and follow functions I built using both IR sensors and bluetooth.

To learn how to program a robot from scratch, I followed along with Paul McWhorter's [Robotics Tutorial Series] (https://www.youtube.com/c/mcwhorpj), where I finally got apply my concepts I learned in my physics and calculus courses, such as circular motion, linear motion, linear regression, point-slope form, and measuring distances between objects using sound waves.

I even learned how to make various calibrations to ensure my robot went the accurate and precise distances in feet, speed in ft/s, and turns in degrees.

From my calibrations I learned how to think as engineer by creating formulas and equations using my mathematics and physics knowledge to simplify the code and processing that must be done in the logic I create. 

For instance, I could have simply used the trial and error method to find the speeds at which the car will move at specific distances, but why do that when I could just perform a few trials and model it using linear equations on MATLAB or even spreadsheets, which reduces the amount of work I must do and makes my project simpler to replicate. 

However, I knew from watching this series Dr. McWhorter was not necessarily focused too much on organizing the code and making it as effective as possible since his aim was to teach the students about robotics in general from learning the math, physics, electronics, and programming. 

With this in mind, I used my programming knowledge from my courses and projects to turn the my robotic car into a C++ class since all the pins were already defined all I needed to do was make them constant private members, analyze the runtime of my functions, and create the functions as public members to my robotic car class. That way I turned my main.cpp file from 328 lines of code to only 30 lines of code. 

I faced issues in just having the program compile at first since I thought I should make the setup commands individually, but I needed to incoprate them in the class and run the setup before the setup function in the Arduino IDE to successfully upload the code to my robot. 

I made the setup evident in my robotCar.cpp file with the setUp() function. 

I still have more to improve on such as analyzing the runtime of my code and gathering more calibrations to handle movements in various terrains, such as carpets, hardwood, rocky terrain, and grass if desired. 

Please feel free to contribute to the code and add to the conversation. Thak you.





