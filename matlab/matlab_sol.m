%% matlab test
% U=3;
% D=1;
% 
% [x,Fs] = audioread('../data/ghostbustersray.wav');
% Fs = Fs*U-1/D;
% 
% x_u = reshape(vertcat(x',zeros(size(x,1),U-1)'),1,[]);
% y_u = conv(x_u,Num);
% y = y_u(1:D:size(y_u,D));
% Fs
% sound(up_sampled,Fs);
h = Num;
% num = 1317
% 1317+

U=3;
D=2;
[x,Fs] = audioread('../data/ghostbustersray.wav');

x_u = reshape(vertcat(x',zeros(size(x,1),U)'),1,[]);
x_filt = conv(x_u,h);
size(x_filt)
y = x_filt(1:D+1:size(x_filt,2));

sound(y,Fs/size(x,1)*size(x_filt,2)/(D+1));