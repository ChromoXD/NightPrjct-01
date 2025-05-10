#include "NightPrjtHdr.hpp"


Vector3 Player_Rotation() {

    //X-Axis Rotation Magic
    RttX = Rtt_Speed * GetMouseDelta().x;

    //Y-Axis Rotation Magic
    RttY = Rtt_Speed * GetMouseDelta().y;
    
    //Final Magical Values
    return { RttX, RttY, RttZ };
}