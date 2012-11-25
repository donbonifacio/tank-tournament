#include "../include/Direction.h"

using namespace Tank;

UpDirection __up;
DownDirection __down;
LeftDirection __left;
RigthDirection __rigth;

const Point UpDirection::dirVector(0,-1);
const Point DownDirection::dirVector(0,1);
const Point LeftDirection::dirVector(-1,0);
const Point RigthDirection::dirVector(1,0);

//---------------------------------------------------------------------------------------------------------
Direction* Direction::up()		{ return &__up; 	}
Direction* Direction::down()	{ return &__down; 	}
Direction* Direction::left()	{ return &__left; 	}
Direction* Direction::rigth()	{ return &__rigth; 	}

Direction* Direction::getDirection( Type _type )
{
	switch(_type) {
		case UP:	return up();	break;
		case DOWN:	return down();	break;
		case LEFT:	return left();	break;
		case RIGTH:	return rigth();	break;
	}
	return 0;
}
	
//---------------------------------------------------------------------------------------------------------
Direction* UpDirection::getOpositeDirection() const { return &__down; }
Direction* DownDirection::getOpositeDirection() const { return &__up; }
Direction* LeftDirection::getOpositeDirection() const { return &__rigth; }
Direction* RigthDirection::getOpositeDirection() const { return &__left; }

//---------------------------------------------------------------------------------------------------------

Direction* UpDirection::getCWDirection() const	{ return &__rigth; 	}
Direction* UpDirection::getCCWDirection() const	{ return &__left; 	}

Direction* DownDirection::getCWDirection() const	{ return &__left; 	}
Direction* DownDirection::getCCWDirection() const	{ return &__rigth; 	}

Direction* LeftDirection::getCWDirection() const	{ return &__up; 	}
Direction* LeftDirection::getCCWDirection() const	{ return &__down; 	}

Direction* RigthDirection::getCWDirection() const	{ return &__down; 	}
Direction* RigthDirection::getCCWDirection() const	{ return &__up; 	}

//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
