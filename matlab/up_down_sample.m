%% up/down sample
% create and save h[n]
% x = zeros(20,1);
% x(1) = 1; % Kronecker delta input
% y = filter(Num,1,x);
array_to_bin(Num,'../data/h.bin')

audio_to_bin('../data/ghostbustersray.wav','../data/ghostbustersray.bin');

! ../build/sample_conv ../data/ghostbustersray.bin ../data/ghostbustersray_edited.bin ../data/h.bin 1 0
bin_to_audio('../data/ghostbustersray_edited.bin','../data/ghostbustersray_edited.wav');
[y,Fs] = audioread('../data/ghostbustersray_edited.wav');
Fs
sound(y,Fs);