# Simulator Particle

First I created a particle that works alone (gravity, mass, collision):

![image](image/Particule1.jpg)

Then make groups of these particles connected by springs:

![image](image/Particule2.jpg)
![image](image/Particule3.jpg)

# Subject

```
PARTICLE ALONE:

We will denote pt the position at time t, vt the speed at time t and at the acceleration at time
t. Acceleration is the change in speed. Let dt be a small time interval, for example
10-3seconds (0.001 seconds). Acceleration is the change in speed:

dv(t)/dt = (v(t)-v(t-dt)) / dt = a(t)

We can do the same for the speed which is the variation of position:

(p(t)-p(t-dt)) / dt = v(t) 

1. Calculate the new position based on the speed and position at the time step
previous.

2. Calculate the speed update based on the speed at the previous time step
and acceleration.

3. From these two expressions and the fundamental principle of dynamics, calculate
the position of a particle as a function of the forces experienced at time t.

The position of a particle at point P can be written as the vector OP, a
2-dimensional vector in the case of the plane that we will deal with here. The speed of the particle
is also a vector.

1. Write in C++ the Vec2 structure which stores a 2-dimensional vector. You can
take the Complex structure and rename it. Also take the operators +, -, *,
And /.

2. Write in C++ the Particle structure which stores the information necessary for a
simulation by the second law of dynamics (Newton's 2nd law). A particle is
represented by a position, a speed, a force and a mass. If the particle undergoes
several forces, the force vectors will be summed.

3. Write the partInit function that initializes a particle with the following parameters:
a position p, a speed v, and a mass m.

4. Write the procedure void partAddForce(Particles& p, Vec2 force) which adds a force
to the particle p.

5. Write the void partUpdatePV procedure that updates the speed and position of a
particle.

6. Write the main program simulating and displaying a particle.
Note: forces must be provided, otherwise the particle will remain immobile.

7. Define the MAX_PART constant, as well as the World structure which contains a
set of particles. The World structure will contain an array of MAX_PART
particles, as well as the number of particles actually simulated in the table.

8. Write the init procedure which takes as parameters a world World and a number of
particles to be initialized in this world. Initialize the particle velocity vector of
way to have a fountain.

At the same time write an addParticle function which takes a world as parameter
World, a particle and which returns the index of the particle added in the table.

void addParticle(World& w , Particle p)

SPRING:

We are going to go a little further with the manipulation of moving particles by
connecting two particles together with a spring.
The elastic restoring force exerted by the spring on the mass m is

T = −k . Δl . er

where:

- is a unit vector directed along the axis of the spring, oriented outwards.

- Δl=l−l0 is the elongation of the spring, noting l the length of the spring, and l0 its length at
empty.

- k is the stiffness of the spring, intrinsic to the spring considered, it characterizes the capacity of the
spring to resist the movement of mass m, and consequently to return to its position
balance

1. Define a Spring structure based on the World structure containing
all the particles in the world. You can use the index of a particle in
the table as identifier.

2. Add a spring array to the World structure.

3. Modify the init procedure that initializes the world so that it also creates the
springs. We advise you to write an addParticle structure that returns the index
of the added particle. You can start by creating 2 particles connected by a
spring, then make a triangle, then a square, etc.
procedure addParticle(w: data/Result World)

4. Modify the draw procedure so that it displays springs represented by lines.

5. Write the procedure computeParticleForceSpring which calculates the forces exerted by the
springs on all the particles in the world.

COLLISION:

On Earth, an approximation of the force experienced by a particle subjected to Earth's attraction
is the weight, with m the mass and G is the universal gravitational constant G=9.81:
P = m.G

1. Add a World structure that will store several particles in an array. In
complement the structure, program an init function.

2. Add this force of gravity to your program so that your particles “fall”.
For collision management we will only consider horizontal walls or
vertical: x=0, y=0, x=Xmax, y=Ymax

3. Modify the update function code to include these collisions. You should get
particles bouncing around in the screen box. The crash test is quite
simple: if (x<0) { … }

The reaction to a collision can be done by artificially putting the particle back into the
simulation rectangle: x = -x;

It is also necessary to reorient the speed vector symmetrically: vx = -vx

4. After a shock a particle loses a little speed (energy) absorbed by the wall. This
is done by reducing the speed vector: v = -FRICTION * v where FRICTION is a
constant less than 1, for example 0.6.

```

# GrAPiC 

## Starting

Linux, Windows and Mac instruction :

http://licence-info.univ-lyon1.fr/grapic

## Introduction

GrAPiC is a small, easy-to-use framework to add graphical functionalities to your C/C++ code. 
Its main goal is to provide easy graphical functions to be used in introduction courses of algorithm and programming in C/C++. 
It is based on SDL2 but to use it you need to know only few very simples functions. 
The Grapic archive comes with the needed SDL part, you do not have to install SDL. Just unzip and enjoy ! 

## Starting

Compiling from the github (which is not the standard way).

* On Linux you need to install:
- g++
- doxygen
- zip
- lib-sdl2-dev lib-sdl2 sd2_image... sdl2_ttf...

1. sudo apt install g++ premake4 zip doxygen libsdl2-dev libsdl2-mixer-dev libsdl2-image-dev
2. make premake
3. make
(4. script/make_linux_test.sh): to test the archive doc/download/grapic-linux.tgz
(5. script/make_web.sh): to create the zip files in doc/download or to sync everything to the webpage (need passwd).


* On windows
0. Install CB 20
1. run premake-cb20.bat to generate the projects files    or     run premake-lifami.bat to generate lifami projects 
2. open build/windows-cb20/grapic.workspace

## Best way to make a projet in windows

(windows): 
 - Open build/windows-cb20/grapic.workspace in CodeBlocks
 - In the left part (Management) of the logiciel, double clic in the projet of yours choice (it's those in /apps)
 - Finally clic in the green arrow in the top of the screen

![OpenFolder](image/OpenFolder.jpg)
![OpenFile](image/OpenFile.jpg)

## Put your new project in GraPic

Add your directory with your cpp files in "apps" and add the path in "premake4".

