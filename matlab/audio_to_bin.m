function audio2bin(file_in, file_out)
if(nargin == 1)
    file_out = [file_in(1:max(strfind(file_in,'.'))),'bin'];
end
fprintf('Input file = %s\n', file_in);
fprintf('Output file = %s\n', file_out);

[x,fs] = audioread(file_in);

x = x.';                            % transpose 2 audio channels

fid = fopen(file_out,'wb');         % write binary
fwrite(fid,[1 size(x) fs 0],'int'); % audio header
fwrite(fid, x(:), 'float');
fclose(fid);

return;