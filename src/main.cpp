#include "global_stuff.hpp"
#include "utms.hpp"

int main(int argc, char *argv[])
{
    UTMS *utms = new UTMS(argv[1], argv[2], argv[3], argv[4]);
    utms->run();
    delete utms;
}