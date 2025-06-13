# BabySense

<img src="readme_assets/1.jpeg" width="500"/>
<img src="readme_assets/2.jpeg" width="500"/>

This is the unofficial repository of BabySense, a project that was created during the Neapolis Innovation Summer Campus 2024 (NISC) in collaboration with STMicroelectronics. It was an Hackathon that took place  in the STMicroelectronics Naples branch in which each team had about 5 days to learn how to work with embedded systems and create a project from scratch.

The aim of this prototype was to create a Baby Monitor that could be useful both for the parents and for the baby. The monitor on the parent side provides useful information like temperature and noise recognition. The parent can set a decibel threshold that plays an alarm after being met. On the kid's side, the monitor keeps the baby entertained with simple games such as Rock Paper Scissor, recognising Animals and Geometrical Shapes. The baby can also interact with the monitor by petting its head, which will make it look happier for a while, in a basic attempt to teach empathy.

You can see [a short demo here](https://youtu.be/uJ5wRD_ZAyA).

## Technologies

The project was created in about a week using a NucleoG4 board. We used the ChibiStudio toolchain that included an IDE and ChibiOS, a free embedded real time operating system.

We employed many sensors provided by the hackathon: the two devices communicate through an IR Sensor, the monitor has a Temperature and Humidity Sensor, a Proximity Sensor, two 48x84 LCDs, a mic and 4 buttons. The parents set the threshold using buttons and a speaker is used for the alarm.

The boxes were created using recycled materials such as cardboard, tape and markers. The monitor was decorated to give a playful vibe while the parent's side is more minimalistic. 

The code was originally uploaded on a TortoiseSVN instance provided by STMicroelectronics.

<img src="readme_assets/3.jpeg" width="500"/>
<img src="readme_assets/4.png" width="500"/>

## Team

The app was created by a team of 8 people from various backgrounds:

| Name  |  Course |
|---|---|
Luigi Inquieto     | Computer Engineering  |
Fabrizio Bonomo    | Computer Engineering  |
Lorenzo Cavaliere  | Computer Engineering  |
Teresa Di Dona     | Computer Engineering  |
Manuel Loffredo    | Computer Engineering  |
Carmine Sorrentino | Computer Engineering  |
Simone Boscaglia   | Computer Science      |
Luca Criscuolo     | Cybersecurity         |




