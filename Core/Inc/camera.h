#ifndef CAMERA_H
#define CAMERA_H


int CAMERA_Initialization_sequence();

void CAMERA_Start_Crop_Capture_To_Video_Buffer();

void CAMERA_Start_Capture(uint16_t *buf, size_t bufsize);

#endif
