#include <Siv3D.hpp>
#include <vector>
#include <cmath>

const int num = 10;
namespace Initial {
std::vector<double> theta1 = {90_deg,90.001_deg,90.002_deg,90.003_deg,90.004_deg,90.005_deg,90.006_deg,90.007_deg,90.008_deg,90.009_deg};
std::vector<double> theta2(num,90_deg);
std::vector<double> theta_vel1(num,0.0);
std::vector<double> theta_vel2(num,0.0);
std::vector<float> Mass1(num,0.40);
std::vector<float> Mass2(num,1.0);
std::vector<float> length1(num,0.23);
std::vector<float> length1_(num,length1[0]*1000);
std::vector<float> length2(num,0.13);
std::vector<float> length2_(num,length2[0]*1000);
std::vector<float> width(num,15);
float g = 9.8;
};

namespace Mat_elem {
using namespace Initial;
double A[num];
double B[num];
double C[num];
double D[num];
double D1[num];
double D2[num];
}

/*namespace Mat_elem2 {
using namespace Initial;
double A1 = (Mass1+Mass2)*length1*length1;
double A2 = Mass2*length2*length2;
double B = Mass2*length1*length2*cos(theta1-theta2);
double D1 = -Mass2*length1*length2*theta_vel2*theta_vel2*sin(theta1-theta2)-(Mass1*Mass2)*g*length1*sin(theta1);
double D2 = Mass2*length1*length2*theta_vel1*theta_vel1*sin(theta1-theta2)-Mass2*g*length2*sin(theta2);
}*/

using namespace Initial;
using namespace Mat_elem;

void Main()
{
    Scene::SetBackground(Palette::Skyblue);
    RectF stick1[num]; Circle knot[num]; RectF stick2[num];
    for(auto n:step(num)){
        stick1[n] = RectF(0,0,Initial::width[n],Initial::length1_[n]);
        knot[n] = Circle(0,0,10);
        stick2[n] = RectF(Arg::topCenter(knot[n].center.x,knot[n].center.y),Initial::width[n],Initial::length2_[n]);
    }
    
    Window::SetStyle(WindowStyle::Sizable);
    Scene::SetScaleMode(ScaleMode::ResizeFill);
    Window::Maximize();
    Scene::SetLetterbox(Palette::Black);
    Window::SetStyle(WindowStyle::Sizable);
    //Scene::SetScaleMode(ScaleMode::ResizeFill);
    Window::Maximize();
    Scene::SetLetterbox(Palette::Black);
    
    while(System::Update()){
        double t = 0.001;
        
        for(auto _:step(30)){
            for (auto j:step(num)){
        A[j] = (Mass1[j]*4*Mass2[j])*length1[j];
        B[j] = 2*Mass2[j]*length2[j]*cos(theta1[j]-theta2[j]);
        C[j] = 2*length1[j]*cos(theta1[j]-theta2[j]);
        D[j] = length2[j];
        Mat_elem::D1[j] = -2*Mass2[j]*length2[j]*theta_vel2[j]*theta_vel2[j]*sin(theta1[j]-theta2[j])-(Mass1[j]+2*Mass2[j])*g*sin(theta1[j]);
        Mat_elem::D2[j] = 2*length1[j]*theta_vel1[j]*theta_vel1[j]*sin(theta1[j]-theta2[j])-g*sin(theta2[j]);
            
        double ADBC = 1.0/A[j]*D[j]-B[j]*C[j];
        
        theta_vel1[j] = theta_vel1[j] + t*(ADBC*(D[j]*Mat_elem::D1[j]-B[j]*Mat_elem::D2[j]));
        
        theta_vel2[j] = theta_vel2[j] + t*(ADBC*(-A[j]*Mat_elem::D1[j]+C[j]*Mat_elem::D1[j]));
        
        theta1[j] = theta1[j] + t*theta_vel1[j];
        theta2[j] = theta2[j] + t*theta_vel2[j];
            }}
        
        for(auto i:step(num)){
            
        
            }
        }
}
