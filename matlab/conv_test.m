%% Convolution Test
x = [1,2,3,4,5,4,5,6,7];
array_to_bin(x,'../data/x.bin')

h = [1,2,3,2,1,2];
array_to_bin(h,'../data/h.bin')

! ../build/sample_conv ../data/x.bin ../data/y.bin ../data/h.bin 3 2
y = bin_to_array('../data/y.bin');
y'
