class Ray {
public:
  float hx, hy, vx, vy, angle;
  Ray(float hx, float hy, float vx, float vy, float angle) {
    this->hx = hx;
    this->hy = hy;
    this->vx = vx;
    this->vy = vy;
    this->angle = angle;
  };
};