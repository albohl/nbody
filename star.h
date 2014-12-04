
struct star{
  float xpos, ypos;     //Coordinates for the body
  float xspeed, yspeed; //Speed in x- and y-direction
  float mass;
  float xforce, yforce; //The force that affect the body in x- and y-direction
};

struct star makeStar();

float readXForce(struct star *s);

float readYForce(struct star *s);

void newForce(struct star *s, float newxforce, float newyforce);

float readXPos(struct star *s);

float readYPos(struct star *s);

void newPos(struct star *s, float newxpos, float newypos);

float readMass(struct star *s);

void newMass(struct star *s, float newmass);

float readXSpeed(struct star *s);

float readYSpeed(struct star *s);

void newSpeed(struct star *s, float newxspeed, float newyspeed);

