function array_to_bin(file_in, file_out)
if(nargin == 1)
    file_out = [inputname(1),'.bin'];
end
fprintf('Input file = %s\n', inputname(1));
fprintf('Output file = %s\n', file_out);

  
x = file_in;                            % transpose 2 audio channels
fs = 0;

fid = fopen(file_out,'wb');         % write binary
fwrite(fid,[1 size(x) 1 1],'int'); % audio header
fwrite(fid, x(:), 'float');
fclose(fid);

return;