function [] = shift1(x_fft, w1, w2)
 
N = length(x_fft);
 x_fft = fftshift(x_fft);
 
 f=2*pi*[-N/2:N/2-1]/N; %вычисление значений, отображаемых по оси частот
 figure;
 hold on;
 stem(f,abs(x_fft))
 xlabel('Частота[-pi,pi]')
 ylabel('Значение ДПФ(x)')
 
 w=[-w2 -w1 w1 w2]; %вектор частот +-w1, +-w2
 w1_i = find (abs(f)==w1); %нахождение индексов частот +-w1
 w2_i = find (abs(f)==w2); %нахождение индексов частот +-w2
 yw=[abs(x_fft(w2_i(1))) abs(x_fft(w1_i(1)))
abs(x_fft(w1_i(2))) abs(x_fft(w2_i(2)))];
 
 stem(w,yw, 'r--')
 hold off;
 text(-w2,-1.5,'-w2'); %подписи частот +-w1, +-w2
 text(-w1,-1.5,'-w1');
 text(w1,-1.5,'w1');
 text(w2,-1.5,'w2');
 axis([min(f) max(f) 0 inf]); %границы частот
 grid 
end