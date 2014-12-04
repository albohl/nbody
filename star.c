struct star{
  float xpos, ypos;     //Coordinates for the body
  float xspeed, yspeed; //Speed in x- and y-direction
  float mass;
  float xforce, yforce; //The force that affect the body in x- and y-direction
};

struct star makeStar(){
  struct star s;
  s.xpos = 0;
  s.ypos = 0;
  s.xspeed = 0;
  s.yspeed = 0;
  s.mass = 0;
  s.xforce = 0;
  s.yforce = 0;
  return s;
}

float readXForce(struct star *s){
  return s -> xforce;
}

float readYForce(struct star *s){
  return s -> yforce;
}

void newForce(struct star *s, float newxforce, float newyforce){
  s -> xforce = newxforce;
  s -> yforce = newyforce;
}

float readXPos(struct star *s){
  return s -> xpos;
}

float readYPos(struct star *s){
  return s -> ypos;
}

void newPos(struct star *s, float newxpos, float newypos){
  s -> xpos = newxpos;
  s -> ypos = newypos;
}

float readMass(struct star *s){
  return s -> mass;
}

void newMass(struct star *s, float newmass){
  s -> mass = newmass;
}

float readXSpeed(struct star *s){
  return s -> xspeed;
}

float readYSpeed(struct star *s){
  return s -> yspeed;
}

void newSpeed(struct star *s, float newxspeed, float newyspeed){
  s -> xspeed = newxspeed;
  s -> yspeed = newyspeed;
}
