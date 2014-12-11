/**
A star
 */
struct star{
  float xpos, ypos;     //Coordinates for the body
  float xspeed, yspeed; //Speed in x- and y-direction
  float mass;
  float xforce, yforce; //The force that affect the body in x- and y-direction
};

/**
Creates a star with all parameters set to 0.
 */
struct star makeStar();

/**
@param s The star
@return The force on s in the x-direction
 */
float readXForce(struct star *s);

/**
@param s The star
@return The force on s in the y-direction
 */
float readYForce(struct star *s);

/**
Sets the force affecting s in x-direction to newxforce and the force affectong s in y-direction to newyforce.
@param s The star
@param newxforce The wanted force in the x-direction
@param newyforce The wanted force in the y-direction
 */
void newForce(struct star *s, float newxforce, float newyforce);

/**
@param s The star
@return The x-coordinate of s
 */
float readXPos(struct star *s);

/**
@param s The star
@return The y-coordinate of s
 */
float readYPos(struct star *s);

/**
Sets the position of s to (newxpos, newypos)
@param s The star
@param newxpos The wanted new x-coordinate
@param newypos The wanted new y-coordinate
 */
void newPos(struct star *s, float newxpos, float newypos);

/**
@param s The star
@return The mass of s
 */
float readMass(struct star *s);

/**
Sets the mass of s to newmass
@param s The star
@param newmass The wanted mass
 */
void newMass(struct star *s, float newmass);

/**
@param s The star
@return The speed of s in x-direction
 */
float readXSpeed(struct star *s);

/**
@param s The star
@return The speed of s in y-direction
 */
float readYSpeed(struct star *s);

/**
Sets the speed of s in x direction to newxspeed and the speed of s in y-direction to newyspeed.
@param s The star
@param newxspeed The wanted speed of s in the x-direction
@param newyspeed The wanted speed of s in the y-direction
 */
void newSpeed(struct star *s, float newxspeed, float newyspeed);

