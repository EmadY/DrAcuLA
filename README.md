# Core files for `DrAcuLA` project RPC

The `DrAcuLA` (Drone Accurate Localization Algorithm) project seeks to create a new way to produce accurate campus-level
localisation, by relying only on the propagation of a WiFi-Direct signal. As a proof of concept, we will have a drone
utilize this signal to fly towards a certain person. We will use only the signal created by us to guide us. 

This code will be placed on a Raspberry Pi that will control the drone. It has the ability to read the signals,
determine the correct one to pursue, and determine the direction in which to move. It also controls the drone (Bebop-3)
via ROS and guides it towards the destination.

For more information about how the signal is used to determine the location, or some specifics of our implementation,
feel free to email any of the authors.

### Acknowledgements 

The `DrAcuLA` project is an FYP project authored by **Emad Yehya** (`emad.yehya@gmail.com`), **Ebrahim Karam**
(`ebrahim.karam@gmail.com`), and **Mohammad-Ghazi Raad** for
the American University Of Beirut.

We would also like **Dr. Louay Bazzi** being our advisor on this project, and **Dr. Joseph Constantine** for his
assistance and recommendations. 
