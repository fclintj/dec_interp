#include <iostream>
#include <vector>
#include <string.h>
#include <cmath>

const int IOBUFFSIZE = 10;

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

void print_arr(double arr[], int size){
     for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";    
     }
     std::cout << std::endl;
}
int main(int argc, char* argv[]){

     if (argc < 2) {
         std::cout << "file_in file_out file_h U D"  << std::endl;
     }

    // read in file
    char* file_in = argv[1];
    char* file_out = argv[2];
    char* file_h = argv[3];
    int U = atoi(argv[4])+1; //
    int D = atoi(argv[5]); //

    int Lh;  // size of buffer


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

    Lh = header_h.len;
    double *h = new double[Lh];
    fread(h,sizeof(double),Lh,fh);
    if(header_x.nchan > 1) { printf("Error: function only takes 1 channel audio"); return -1; }

    memcpy(&header_y, &header_x, sizeof(header_x));

    // header_y.len = ceil(header_x.len*double(U)/D);
    //     header_y.len = ceil(header_x.len*double(U)/D);
    //
    // header_y.fs = header_x.fs*U/D;

    fwrite(&header_y, sizeof(header_x), 1, fy);

    double t;          // Variable for accumulating convolution result
    int xlen, ylen=0; // Indexes for input and output buffers
    int i;            // Index for input data buffer
    int j;            // Index for up sampling loop
    int k=0;          // Index for circular data buffer
    int m;            // Convolution loop index for filter coefficients
    int n;            // Convolution loop index for circular data buffer
    int l=0;          // Down sampling counter

    double x[IOBUFFSIZE], y[IOBUFFSIZE];
    double *g = (double*)calloc(Lh, sizeof(double));

    xlen = fread(x,sizeof(double),IOBUFFSIZE,fx);// Read in first chunk of input samples

    while(xlen>0) {                             // keep sampling 
        for(i=0; i<xlen; i++) {                 
            k = (k+Lh-1) % Lh;                  // Update circular index of filter. Lh = length(h) 
            // l = (l+D) % D;                    // Update down-sample counter
            g[k] = x[i];                        // Put each sample into the filter circular data buffer
        
            // Convolution loop
            if(l==0) {                          
                for (j = 0; j<U; j++) {         // Loop over the up sampled outputs
                    // Convolution loop 
                    // print_arr(g,Lh);
                    // print_arr(h,Lh);

                    for (t=0.0, m=0, n=0; n<Lh; n++, m+=U) { 
                        t += h[m+j] * g[(n+k) % Lh]; // Multiply and accumulate into local variable
                    }                           

                    // Save result into output buffer
                    y[ylen] = t;                
                    ylen++;                     // Increment the index for the output buffer

                    // If output buffer is full, then save it to output file
                    if (ylen == IOBUFFSIZE) {   
                    fwrite(y, sizeof(double), ylen, fy);
                    ylen = 0;               // Reset the index for the output buffer
                    }
                }                               
            }
        }                                       
        xlen = fread(x,sizeof(double),IOBUFFSIZE,fx); // Read in next chunk of input samples
    }
    
    // Finish writing last output samples
    if(ylen>0) {                                // If output buffer is full, then save it to output file
        fwrite(y,sizeof(double),ylen,fy);        // Write the output buffer
        ylen = 0;                               // Reset the index for the output buffer
    }
    fclose(fx);
    fclose(fy);
    free(g);
    return 0;
}

