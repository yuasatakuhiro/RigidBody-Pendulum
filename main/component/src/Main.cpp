#include <Siv3D.hpp>
#include <cmath>

namespace Initial {
double theta = 60_deg;
double theta_vel = 0.1;
float Mass = 60;
float length = 2*100;
float width = 30;
float bind_length = length/2.0;
double Iz = Mass*(length/2.0)*(length/2.0)/3.0+Mass*bind_length*bind_length;
float g = 980;
};

void Main()
{
    Scene::SetBackground(Palette::Skyblue);
    
    const Rect stick(0,0,Initial::width,Initial::length);
    const Vec2 bind_point(stick.pos.x+Initial::width/2.0,stick.pos.y);
    
    float theta_vel = 0.1;
    float theta = 60_deg;
    
    while(System::Update()){
        if (Scene::DeltaTime()==0){
            continue;
        }
        const Transformer2D t0(Mat3x2::Translate(Scene::Center()-bind_point),true);
        const float theta_f = theta;
        const float theta_ff = theta_vel;
        
        theta_vel = theta_vel - Scene::DeltaTime()*Initial::g*sin(theta)/Scene::Center().y;
        theta = theta + Scene::DeltaTime()*theta_vel;
        
        const Vec2 pos = OffsetCircular(Vec2(bind_point.x,bind_point.y-Scene::Center().y),static_cast<double>(Scene::Center().y),180_deg+theta);
        
        const Vec2 pos_1 = OffsetCircular(Vec2(bind_point.x,bind_point.y-Scene::Center().y),static_cast<double>(Scene::Center().y),180_deg+theta_f);
        
        const Vec2 pos_2 = OffsetCircular(Vec2(bind_point.x,bind_point.y-Scene::Center().y),static_cast<double>(Scene::Center().y),180_deg+theta+(theta-theta_f));
        
        Vec2 pos_delta = (pos_2-pos_1);
        if(pos_delta.length() == 0){
            pos_delta = Vec2(0,0);
        }else{
            pos_delta = pos_delta/pos_delta.length();
        }
        const Vec2 theta_a = Scene::Center().y*abs((theta_vel - theta_ff)/Scene::DeltaTime())*pos_delta;
    
        Initial::theta_vel = Initial::theta_vel -  Scene::DeltaTime()*(Initial::Mass*Initial::g*Initial::length/2.0*sin(Initial::theta)/Initial::Iz) + (Initial::length/2.0)*cos(Initial::theta)*theta_a.y/Initial::Iz-(Initial::length/2.0)*sin(Initial::theta)*theta_a.x/Initial::Iz;
        
        Initial::theta = Initial::theta + Scene::DeltaTime()*Initial::theta_vel;
        
        Circle(bind_point.movedBy(pos),10).draw(Palette::White);
        Line(bind_point.movedBy(pos),Vec2(bind_point.x,-Scene::Center().y)).draw(Palette::Green);
        
        const Transformer2D t1(Mat3x2::Translate(pos));
        stick.rotatedAt(bind_point,Initial::theta).draw(Palette::Black);
    }
}
