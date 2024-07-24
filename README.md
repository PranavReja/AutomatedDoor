# AutomatedDoor
A personal home security project that uses Raspberry pi and Arduino to lock and unlock my door with facial recognition or custom linked keycards.  

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Facial Recognition
The facial recognition was done in two parts using a Raspberry Pi and a local computer. The raspberry pi is running an openCV based facial tracking algorithm and if any face is detected for a certain amount of time, then it takes a picture and uploads it to a locally runnning Flask web-server. Along with the image it uses socket communication to notify the local computer to check the webserver and download the new image uploaded for facial recognition and send the result back through socket communication. This portion was written in python. 

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Arduino Door Mechanism 
The Arduino accepts USB Serial Commands from the Raspberry Pi when a face is recognized and subsequently runs the stepper motor to open and close the door. It also is simultaneously running a keyscanner for non-recongized faces, a buzzer + light for audio-visual confirmations and a photoresistor that was rigged up to be a buttonless doorbell. If it scans a recognized keycard it will run the stepper motor to open the door the same. This portion was exclusively coded in C++ by way of the arduino IDE.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Visual Project Overview
![Project OverView drawio](https://github.com/user-attachments/assets/c1b49721-647d-4f05-8eab-c4d6f57d9451)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# Gallery
![9C811C72-5F50-4524-AE4C-AB94DF5333AE](https://github.com/user-attachments/assets/5ae30ee7-adcd-4f72-9b45-510be25b128b)
![DFF68456-9704-48B7-86C0-CB7B58F254FD](https://github.com/user-attachments/assets/715bcf76-030c-49bc-b31c-fd6c1edddb84)


