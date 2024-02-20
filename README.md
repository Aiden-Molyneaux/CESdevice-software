## CES Device Prototype Software
### OVERVIEW
This software was developed as a submission for a term project in a university-level 'Objected-Oriented Software Engineering' course. The project is a software-based prototype mimicking the functionality of a medical device called a Cranio-Electric Stimulation (CES) device.

Here is a brief snippet of the project goals:\
" Raven Microcurrent Biofeedback Inc. (RMB), a manufacturer of a variety of microcurrent
biofeedback devices, has hired you to build them a software-based prototype of a device they
are planning to add to their product line. RMB intends to use this prototype to explore different
capabilities before deciding on the design of the physical product. Your team happily accepts
the task, eager to impress your new employer with your development skills. RMB would like
their device to have the same features as Oasis Pro from Mind Alive Inc. with the a few
additional capabilities related to recording and replay of treatments. The implementation and
testing are to be in C++ using the Qt framework.

Oasis Pro is an example of a CES device which is a non-invasive neuro-stimulation medical
device that delivers microcurrent via an electrode through the earlobes to stimulate the brain for
the purpose of therapeutic intervention. "

More information on the project specification, as well as what a CES device can be found in the file labeled 'Team Project Specification'. 

### MEET THE TEAM
Team 38:
- Aiden Molyneaux
- Patrick Kye Foley
- Joshua Di Lello
- Bret Tellier

TA:
- Ming Lei

### CONTRIBUTIONS
Aiden's contributions:
- Created GitHub repository for team.
- Created Github commit and pull request workflow for team.
- Programmed about half of the Oasis Pro implementation.
  - Specifically the main therapy() and connectionTest() functions as well as many other support functions.
- Contributed to QT UI development and implementation.
- Wrote about half of the testing documentation.

Patrick's contributions:
- Programmed about half of the Oasis Pro implementation.
  - Specifically functionality regarding adding users, creating treatment history & replaying sessions, testing scripts.
- Contributed to QT UI development and implementation.
- Contributed to written testing documentation.

Joshua's contributions:
- Use cases 1-4
- Traceability matrix
- Use case diagram
- Sequence diagrams 1-4

Bret's contributions:
- Use cases 5-8
- UML diagram
- Sequence diagrams 5-8

### DELIVERABLES
Files included in this project:
- Folder '3004F22' contains all .h, .cpp, and .pro files for the QT Project
  - 3004F22.pro
  - 3004F22.pro.user
  - mainwindow.cpp
  - mainwindow.h
  - mainwindow.ui
  - main.cpp
  - DeviceMediator.cpp
  - DeviceMediator.h
  - Device.cpp
  - Device.h
  - Widget.cpp
  - Widget.h
  - Group.cpp
  - Group.h
  - Session.cpp
  - Session.h
  - User.cpp
  - User.h
  - Recording.cpp
  - Recording.h
  - Battery.cpp
  - Battery.h
  - Button.cpp
  - Button.h
  - Light.cpp
  - Light.h
  - res.qrc
  - .gitignore
- Folder 'icons' contains all .png files required for UI implementation
- Folder 'Documentation' contains all documentation for the Project - Use cases, UML class diagrams, sequence diagrams, traceability matrix, testing
  - UML & Sequence Diagrams.pdf
  - Use Case - UC Diagram - Traceability Matrix.pdf
  - Team Project - Tests
- README.md
 
### TEST SCENARIOS
Fully-tested scenarios:
- Power On Scenario
- Power Off Scenario
- Low Battery Scenario
- Select a Session Scenario
- Connection Test Scenario
- Change Intensity Scenario
- Record a Session Scenario
- Replay a Session Scenario
