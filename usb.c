/**
 * @authors Lelievre Tom Bellenger Maxime GroupePJ2 Caen
 */

#include "define.h"
#include "frame.h"
#include "ftd2xx.h"
#include "usb.h"

/**Init the usb device with our spec
 *
 * @return
 */
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

    // set the baud rate 9600 bps
    ftStatus = FT_SetBaudRate(ftHandle, 9600);
    if (ftStatus != FT_OK) {
        fprintf(stderr, "Failed to set Baud Rate\n");
        FT_Close(ftHandle);

    }else {
        printf("Baud Rate is set\n");
    }

    // Set a 8 bit frame with 1 stop bit and no parity bit
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
    if (ftStatus != FT_OK) {
        fprintf(stderr,"Failed to set Data characteristics\n");
        FT_Close(ftHandle);
    }
    else {
        printf("Data characteristics set\n");
    }

    // No flux control use to avoid to sent to much packet
    ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
    if (ftStatus != FT_OK) {
        fprintf(stderr,"Failed to set Flow Control\n");
        FT_Close(ftHandle);

    }
    else {
        printf("Flow Control set\n");
    }
    // set the read operations waiting time same for writing
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
/**Stop the communication with the usb device
 *
 * @param ftHandle
 */
void closeUSB(FT_HANDLE ftHandle){

    FT_Close(ftHandle);
    printf("File closed\n");

}

/**Write a frame in our usb device
 *
 * @param frame
 * @param ftHandle
 */
void writeUSB(char* frame, FT_HANDLE ftHandle){

    FT_STATUS ftStatus;
    DWORD BytesWritten; // will stock the frame when it is written

    ftStatus = FT_Write(ftHandle, frame, strlen(frame), &BytesWritten);
    if (ftStatus == FT_OK) {
        printf("Frame successfully written\n");
    }
    else {
        fprintf(stderr,"Frame not written");
    }
}