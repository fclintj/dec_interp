function bin_to_audio(infile,outfile)
if(nargin == 1)
    outfile = [infile(1:max(strfind(infile,'.'))),'wav'];
end
fprintf('Input file = %s\n', infile);
fprintf('Output file = %s\n', outfile);

fid = fopen(infile, 'rb');
ndim  = fread(fid, 1, 'int');
nchan = fread(fid, 1, 'int');
dim0  = fread(fid, 1, 'int');
dim1  = fread(fid, 1, 'int');
dim2  = fread(fid, 1, 'int');
[x, ~] = fread(fid, inf, 'double');
fclose(fid);
x = reshape(x, nchan, []).';
x = x./(max(abs(x)));
fs = dim1;

audiowrite(outfile, x, fs);
return