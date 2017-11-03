%% Problem 4
f0 = 1/2;
L = 3;

% create and save h[n]
x = zeros(200,1);
x(1) = 1; % Kronecker delta input
h = filter(L*Num,Den,x);
array_to_bin(h,'../data/h.bin')

% create and save x[n]
n = 512;
t = 0:1/100:10-1/100;
x = cos(2*pi*f0*t);
X = fftshift(fft(x,n));

f = (0:length(X)-1)/length(X)-0.5;
m = (20*log10(abs(X)));
m = abs(X);

plot(f,m)

array_to_bin(x,'../data/x.bin')


! ../build/sample_conv ../data/x.bin ../data/yhat.bin ../data/h.bin 3 2
y = bin_to_array('../data/yhat.bin');


n = 512;
Y = fftshift(fft(y,n));
% m = 20*log10(abs(Y));
m = abs(Y);
f = (0:length(Y)-1)/length(Y)-0.5;
plot(f,m)