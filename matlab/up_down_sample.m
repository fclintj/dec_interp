%% up/down sample
% create and save h[n]
x = zeros(200,1);
x(1) = 1; % Kronecker delta input
% h = filter(Num,Den,x);
h = Num;
array_to_bin(h,'../data/h.bin')

! ../build/sample_conv ../data/ghostbustersray.bin ../data/ghostbustersray_edited.bin ../data/h.bin 4 2
bin_to_audio('../data/ghostbustersray_edited.bin','../data/ghostbustersray_edited.wav');
[y,Fs] = audioread('../data/ghostbustersray_edited.wav');
sound(y,Fs);