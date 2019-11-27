#include <Siv3D.hpp>
#include <cmath>

namespace Initial {
double theta1 = -90_deg;
double theta2 = 90_deg;
double theta_vel1 = 0.0;
double theta_vel2 = 0.0;
float Mass1 = 1.0;
float Mass2 = 1.54;
float length1 = 0.23;
float length1_ = length1*1000;
float length2 = 0.33;
float length2_ = length2*1000;
float width = 15;
float g = 9.8;
};

namespace Mat_elem {
using namespace Initial;
double A = (Mass1*4*Mass2)*length1;
double B = 2*Mass2*length2*cos(theta1-theta2);
double C = 2*length1*cos(theta1-theta2);
double D = length2;
double D1 = -2*Mass2*length2*theta_vel2*theta_vel2*sin(theta1-theta2)-(Mass1+2*Mass2)*g*sin(theta1);
double D2 = 2*length1*theta_vel1*theta_vel1*sin(theta1-theta2)-g*sin(theta2);
}

namespace Mat_elem2 {
using namespace Initial;
double A1 = (Mass1+Mass2)*length1*length1;
double A2 = Mass2*length2*length2;
double B = Mass2*length1*length2*cos(theta1-theta2);
double D1 = -Mass2*length1*length2*theta_vel2*theta_vel2*sin(theta1-theta2)-(Mass1*Mass2)*g*length1*sin(theta1);
double D2 = Mass2*length1*length2*theta_vel1*theta_vel1*sin(theta1-theta2)-Mass2*g*length2*sin(theta2);
}

using namespace Initial;
using namespace Mat_elem;

void Main()
{
    Scene::SetBackground(Palette::Skyblue);
    const Rect stick1(0,0,Initial::width,Initial::length1_);
    const Circle knot(0,0,10);
    const int a = knot.center.x;
    const int b = knot.center.y;
    const Rect stick2(Arg::topCenter(a,b),Initial::width,Initial::length2_);
    
    while(System::Update()){
        double t = 0.001;
        
        for(int i = 0;i<30;i++){
        A = (Mass1*4*Mass2)*length1;
        B = 2*Mass2*length2*cos(theta1-theta2);
        C = 2*length1*cos(theta1-theta2);
        D = length2;
        Mat_elem::D1 = -2*Mass2*length2*theta_vel2*theta_vel2*sin(theta1-theta2)-(Mass1+2*Mass2)*g*sin(theta1);
        Mat_elem::D2 = 2*length1*theta_vel1*theta_vel1*sin(theta1-theta2)-g*sin(theta2);
        
        double ADBC = 1.0/A*D-B*C;
        
        theta_vel1 = theta_vel1 + t*(ADBC*(D*Mat_elem::D1-B*Mat_elem::D2));
        
        theta_vel2 = theta_vel2 + t*(ADBC*(-A*Mat_elem::D1+C*Mat_elem::D1));
        
        theta1 = theta1 + t*theta_vel1;
        theta2 = theta2 + t*theta_vel2;
        }
        const Transformer2D t0(Mat3x2::Translate(Scene::Center()-Vec2(width/2.0,100)),true);
        stick1.rotatedAt(stick1.pos+Vec2(width/2.0,0),theta1).draw(Palette::Orange);

        const Vec2 point = OffsetCircular(Vec2(width/2.0,0),length1_,180_deg+theta1);
        const Transformer2D t1(Mat3x2::Translate(point));
        
        knot.draw(Palette::Black);
        stick2.rotatedAt(knot.center,theta2).draw(Palette::Green);
    }
}
