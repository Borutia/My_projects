a = -10.0;
b = 17.0;
h = 0.6;

x=a:h:b;

plot(sin((x/2)+7)+3);
hold on

plot(sqrt(abs(x+6)));
hold on