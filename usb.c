/**
 * @authors Nom Prenom Nom Prenom Groupe Ville
 */

#include "define.h"
#include "frame.h"
#include "ftd2xx.h"
#include "usb.h"


FT_HANDLE initUSB(){
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;

    ftStatus = FT_Open(0, &ftHandle);
    if(ftStatus != FT_OK) {
        fprintf(stderr, "Failed to open USB device\n");
        FT_Close(ftHandle);
        exit(1);
    }else{
        printf("USB Device open in InitUSB!\n");
    }
    ftStatus = FT_SetBaudRate(ftHandle, 9600);
    if (ftStatus != FT_OK) {
        fprintf(stderr, "Failed to set Baud Rate\n");
        FT_Close(ftHandle);

    }else {
        printf("Baud Rate is set\n");
    }

    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    if (ftStatus != FT_OK) {
        fprintf(stderr,"Failed to set Data characteristics\n");
        FT_Close(ftHandle);
    }
    else {
        printf("Data characteristics set\n");
    }

    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
    if (ftStatus != FT_OK) {
        fprintf(stderr,"Failed to set Flow Control\n");
        FT_Close(ftHandle);

    }
    else {
        printf("Flow Control set\n");
    }

    ftStatus = FT_SetTimeouts(ftHandle, 1000, 1000);
    if (ftStatus != FT_OK) {
        fprintf(stderr,"Failed to set Timeouts\n");
        FT_Close(ftHandle);

    }
    else {
        printf("Timeout set\n");
    }


    return ftHandle;

}
void closeUSB(FT_HANDLE ftHandle){

    FT_Close(ftHandle);
    printf("File closed\n");

}

void writeUSB(char* frame, FT_HANDLE ftHandle){

    FT_STATUS ftStatus;
    DWORD BytesWritten;

    ftStatus = FT_Write(ftHandle, frame, strlen(frame), &BytesWritten);
    if (ftStatus == FT_OK) {
        printf("Frame successfully written\n");
    }
    else {
        fprintf(stderr,"Frame not written");
    }
}