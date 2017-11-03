function x = bin_to_array(infile)
fprintf('Input file = %s\n', infile);

fid = fopen(infile, 'rb');
ndim  = fread(fid, 1, 'int');
nchan = fread(fid, 1, 'int');
dim0  = fread(fid, 1, 'int');
dim1  = fread(fid, 1, 'int');
dim2  = fread(fid, 1, 'int');
[x, ~] = fread(fid, inf, 'float');
fclose(fid);
x = reshape(x, nchan, size(x,1)).';
return