function [] = shift2(x_fft, fs)
N = length(x_fft);
 
%Определение значений оси частот
f = -fs/2 : (fs/N) : (fs/2 - fs/N);
 
%Построение спектра на частотной оси с нулем в центре
x_f_shift = fftshift(x_fft);
figure()
stem(f, abs(x_f_shift))
xlabel('Частота [-Fs/2, F/2]')
ylabel('Значение ДПФ(х)')
axis ([-fs/2 fs/2 -inf inf]);
grid
end
