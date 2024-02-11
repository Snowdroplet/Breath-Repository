#include "camera.h"

//ALLEGRO_BITMAP* Camera::cameraBuffer;

ALLEGRO_TRANSFORM Camera::noTransform; // identity transform
ALLEGRO_TRANSFORM Camera::zoomTransform;

float Camera::zoomScale;
float Camera::zoomTranslateX;
float Camera::zoomTranslateY;

float Camera::mouseTransformedX;
float Camera::mouseTransformedY;

bool Camera::atDestination;
bool Camera::approachingDestination;

int Camera::xCell;
int Camera::yCell;
float Camera::xPosition;
float Camera::yPosition;
float Camera::xDestination;
float Camera::yDestination;



void Camera::ApproachDestination()
{
    ///if(!atDestination)
    ///{

        if(xPosition != xDestination)
            xPosition += (xDestination - xPosition)/2;

        if(yPosition != yDestination)
            yPosition += (yDestination - yPosition)/2;

        ///if(std::abs(xDestination - xPosition) <= 4.0 && std::abs(yDestination - yPosition) <= 4.0)
        ///{
           /// WarpToDestination();
        ///}
    ///}
}

void Camera::WarpToDestination()
{
    atDestination = true;
    approachingDestination = false;
    xPosition = xDestination;
    yPosition = yDestination;
}
