%% Matlab Convolution Test
x = [1,2,3,4,5,4,5,6,7];
h = [1,2,3,2,1,2];

U=0;
D=0;
Fs = Fs*U-1/D;

x = reshape(vertcat(x,zeros(size(x,2),U)'),1,[]);
x_filt = conv(x,h);
y = x_filt(1:D+1:size(x_filt,2));