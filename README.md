# Miscellaneous-Projects
A repository for various smaller projects or unrelated files that don't warrant a repository of their own

# Assignment2
A small selection of problems from a computer science class to showcase a basic understanding of C++ programming, nothing more.

# Pendulum-Pulley-Analysis.ipynb
A numerical compution of a differential equation related to a physics problem that has no closed analytical solution.
The equation itself is derived on paper and then implemented inside the code, initial parameters are chosen and then the solution is run.
The various physical quantities of interest are graphed over time to show how the system evolves and any interesting features of the system.

# TempControllerAnalysis.ipynb

This is a file showcasing the analysis of data collected from our Temperature control circuit.

A project focused on an embedded temperature control system which uses a PID Controller (Proportional-Integral-derivative) to adjust the
temperature of the resistor to a certain target. The circuit consists of a capacitor, thermister, and resistor. The resistor is the main
heating element while the thermistor changes its resistance based on temperature and the capacitor changes its capacitance based on the
subsequent change in current. 

Analysing the data from the capacitor after precisely adjusting for the qualities of the thermistor lets one determine the current temperature,
how the system will behave in the near future, and therefore allow the PID control software to adjust for the target temperature in real-time.
The PID minimizes the error between the target value and current value allowing for highly precise temperature targetting.

Unfortunately the pertinent and advanced control system files and data structure are located on a computer on the SFU campus which currently
cannot be accessed. 
