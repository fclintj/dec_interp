% coefficients for filter
Num = [0.00585700211848685,-0.0101050645904296,0.0248390445383391,-0.0228929830964889,0.0346732733671082,-0.0238512859600107,0.0346732733671082,-0.0228929830964889,0.0248390445383391,-0.0101050645904296,0.00585700211848685];
Den = [1,-5.81770676287660,17.4269969697500,-33.9484051722572,47.0576123759448,-48.0956541934415,36.5797794473643,-20.4099537116018,8.00548424863840,-2.00036903049939,0.244059567466600];


% plot filter in time domain
x = zeros(100,1);
x(1) = 1; % Kronecker delta input
y = filter(Num,1,x);
plot(y)
% save_fig('h-impulse-response.pdf',gcf)
% 
% % plot magnitude response of filter (frequency domain)
% [H,W] = freqz(Num,Den);
% plot(W/(2*pi),20*log10(abs(H)));
% ylim([-85 5]);
% xlim([0 0.5]);
% title("Magnitude Response (dB)")
% xlabel("Frequency")
% ylabel("Magnitude (dB)")
% save_fig('H-mag-response.pdf',gcf)
% 
% 
% % plot frequency response of filter
% [H,W] = freqz(Num,Den);
% plot(W/(2*pi),unwrap(angle(H)));
% title("Phase Response")
% xlabel("Frequency")
% ylabel("Phase (radians)")
% save_fig('H-phse-response.pdf',gcf)




