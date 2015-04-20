#include "simulator.h"


//Initialize structure that holds default memory parameters
const mem_params Default_params = {.L1.block_size = 32, .L1.cache_size = 8192, .L1.assoc = 1,
.L1.hit_time = 1, .L1.miss_time = 1, .L2.block_size = 64, .L2.cache_size = 32768,
.L2.assoc = 1, .L2.hit_time = 5, .L2.miss_time = 7, .L2.transfer_time = 5,
.L2.bus_width = 16, .mmem.sendAddr = 10, .mmem.ready = 30, .mmem.chunkTime = 15,
.mmem.chunkSize = 8};


mem_params Parameters;

int verbosity;

// printUsage - Print usage info
void printUsage( char *argv[] )
{
   printf( "Usage: %s [-f <file>] [-h]\n", argv[0] );
   printf( "Options:\n" );
   printf( "  -f <file>  Optional configuration file.\n" );
   printf( "  -h         Print this help message.\n" );
   exit( 0 );
}

void printSummary( int hit_count, int miss_count, int eviction_count )
{
   printf( "hits: %d   misses: %d   evictions: %d\n", hit_count, miss_count, eviction_count );
}


int main(int argc, char **argv)
{
    char *config_file;
    char c;
    bool config = false;
    Parameters = Default_params;
    while ( ( c = getopt( argc, argv, "f:h" ) ) != -1 )
        {
            switch ( c )
            {
            case 'f':
                config_file = optarg;
                config = true;
                printf("config file = %s\n", config_file);
                break;
            case 'h':
                printUsage(argv);
                exit(1);
                break;
            }
        }
    if (!config){
        Parameters = Default_params;
        printf("Parameters set to default\n");
        simulate(Default_params);
    }
    else{
//        int L1_Cache,L2_cache;
//        unsigned short L1_assoc, L2_assoc;
        FILE *configfile = fopen(config_file, "r");
        while (fscanf( configfile, "%d %hu %d %hu", &Parameters.L1.cache_size, &Parameters.L1.assoc, &Parameters.L2.cache_size, &Parameters.L2.assoc) == 4)
            {
                simulate(Parameters);
            }
    }

//    printUsage(argv);
    return 0;
}
