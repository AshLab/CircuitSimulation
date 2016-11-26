% Modelling Diode and Solving using Newton-Raphson methods

clc;
close all;
clear all;


G=[1E-3 0 ;0 1E-3];
G=G;


index=[0 0 -1];

initialVal=[2 1]';

I1=[1 0]';
Inl=zeros(2,1);

Jnl=zeros(2,2);
J=zeros(2,2);
Voltage=initialVal;

for i=1:100

konst=1*10^-7;

  Idio=konst*((exp((Voltage(1)-Voltage(2))/(2*25.3*10^-3)))-1);

  Inl=[-Idio Idio]';

  Io=I1+Inl;

  g=(konst/(2*25.3*10^-3))*(exp((Voltage(1)-Voltage(2))/(2*25.3*10^-3)));

  Jnl=[-g g;g -g];
  
  J=G-Jnl;
  
  Voltage=J\((-Jnl*Voltage)+Io);
  
 endfor
 
 Voltage