#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>

const int IOBUFFSIZE = 1024;

typedef struct {
    int ndim;		// number of dimensions
    int nchan;		// number of channels
    int len;    	// length of first dimension
    int fs;			// length of second dimension or sample rate
    int empty;		// length of third dimension
} sound_header;

typedef struct {
    int ndim;		// number of dimensions
    int nchan;		// number of channels
    int len;    	// length of first dimension
    int empty1;		// length of second dimension or sample rate
    int empty2;		// length of third dimension
} transfer_function;

int main(int argc, char* argv[]){

     if (argc < 2) {
         std::cout << "file_in file_out file_h U D"  << std::endl;
     }

    // read in file
    char* file_in = argv[1];
    char* file_out = argv[2];
    char* file_h = argv[3];
    int U = atoi(argv[4]); //
    int D = atoi(argv[5]); //

    int M;  // size of buffer


    sound_header header_x, header_y;
    transfer_function header_h;

    FILE *fx, *fy, *fh;
    if (NULL == (fx = fopen(file_in, "rb"))) {
        printf("Error: Cannot find file for input.\n");
        return -1;
    }
    if (NULL == (fh = fopen(file_h, "rb"))) {
        printf("Error: Cannot open transfer function file for processing.\n");
        return -1;
    }
    if (NULL == (fy = fopen(file_out, "wb"))) {
        printf("Error: Cannot open file for ouput.\n");
        return -1;
    }

    // read in header
    fread(&header_x, sizeof(header_x), 1, fx);
    fread(&header_h, sizeof(header_h), 1, fh);

    M = header_h.len;
    float *h = new float[M];
    fread(h,sizeof(float),M,fh);
    if(header_x.nchan > 1) { printf("Error: function only takes 1 channel audio"); return -1; }

    memcpy(&header_y, &header_x, sizeof(header_x));

    header_y.len = ceil(header_x.len*double(U)/D);
    std::cout << header_x.len*double(U)/D+1 <<std::endl;
    if(U==1 || U==0){
        header_y.len -= 1;
        U = 1;
    }
    if(D==1 || D==0){
        D = 1;
        header_y.len -= 1;
    }
    header_y.fs = header_x.fs*U/D;

    fwrite(&header_y, sizeof(header_x), 1, fy);

    float t;          // Variable for accumulating convolution result
    int xlen, ylen=0; // Indexes for input and output buffers
    int i;            // Index for input data buffer
    int j;            // Index for up sampling loop
    int k=0;          // Index for circular data buffer
    int m;            // Convolution loop index for filter coefficients
    int n;            // Convolution loop index for circular data buffer
    int l=1;          // Down sampling counter

    int written_sum = 0;
    float x[IOBUFFSIZE], y[IOBUFFSIZE];
    float *g = (float*)calloc(M, sizeof(float));

    xlen = fread(x,sizeof(float),IOBUFFSIZE,fx);// Read in first chunk of input samples

    while(xlen>0) {                             // keep sampling 
        for(i=0; i<xlen; i++) {                 
            k = (k+M-1) % M;                    // Update circular index of filter. M = length(h) 
            l = (l+D-1) % D;                    // Update down-sample counter
            g[k] = x[i];                        // Put each sample into the filter circular data buffer

            // Down sampling condition: Compute convolution result 
            if(l==0) {                          
                for (j = 0; j<U; j++) {         // Loop over the up sampled outputs
                    // Convolution loop
                    for (t=0.0, m=0, n=0; n<M; n++, m+=U) { 
                        t += h[m+j] * g[(n+k) % M];            // Multiply and accumulate into local variable
                    }                           

                    // Save result into output buffer
                    y[ylen] = t;                
                    ylen++;                     // Increment the index for the output buffer

                    // If output buffer is full, then save it to output file
                    if (ylen == IOBUFFSIZE) {   
                    fwrite(y, sizeof(float), ylen, fy);
                    written_sum += ylen;    // verify the total output samples with predicted
                    ylen = 0;               // Reset the index for the output buffer
                    }
                }                               
            }
        }                                       
        xlen = fread(x,sizeof(float),IOBUFFSIZE,fx); // Read in next chunk of input samples
    }
    
    // Finish writing last output samples
    if(ylen>0) {                                // If output buffer is full, then save it to output file
        fwrite(y,sizeof(float),ylen,fy);        // Write the output buffer
        written_sum += ylen;
        ylen = 0;                               // Reset the index for the output buffer
    }
    fclose(fx);
    fclose(fy);
    free(g);
    std::cout << "header: " << header_y.len << std::endl;
    std::cout << "actual written: " << written_sum << std::endl;
    return 0;
}
