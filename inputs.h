#include "mbed.h"
   
    DigitalIn knop(BUTTON1);

    DigitalOut motor1pin1(PC_9);
    DigitalOut motor1pin2(PB_8);
    DigitalOut motor2pin1(PC_8);
    DigitalOut motor2pin2(PC_6);
    DigitalOut motor3pin1(PB_13);
    DigitalOut motor3pin2(PB_14);
    DigitalOut motor4pin1(PB_15);
    DigitalOut motor4pin2(PB_1);
    PwmOut En1(PA_7);
    PwmOut En2(PB_6);
    PwmOut En3(PB_10);
    PwmOut En4(PB_4);

    int afstant_u =0;
    int correction = 0;
    Timer sonar;
    DigitalOut trigger(PA_13);
    DigitalIn echo (PA_14);

    float afstant_i =0;
    #define MAXIMALE_SPANNING 5.0f
    float spanning=0;
    AnalogIn analog_in(A0);

    PwmOut buzzer(PB_0);

    DigitalOut led1(PA_10);
    DigitalOut led2(PB_3);

    enum richting{links,rechts,non,both};



void vooruit(bool aan_uit){
    En1.write(0.25);
    En2.write(0.25);
    En3.write(0.25);
    En4.write(0.25); 

    if(aan_uit==true){
        //ra
        motor1pin1=1;
        motor1pin2=0;
        //la
        motor2pin1=0;
        motor2pin2=1;
        //rv
        motor3pin1=0;
        motor3pin2=1;
        //lv
        motor4pin1=1;
        motor4pin2=0;
    }
    else{
        motor1pin1=0;
        motor1pin2=0;
        motor2pin1=0;
        motor2pin2=0;

        motor3pin1=0;
        motor3pin2=0;
        motor4pin1=0;
        motor4pin2=0;  
    }
}

void achteruit(bool aan_uit){
    En1.write(0.25);
    En2.write(0.25);
    En3.write(0.25);
    En4.write(0.25);  

    if(aan_uit==true){
        motor1pin1=0;
        motor1pin2=1;
        motor2pin1=1;
        motor2pin2=0;

        motor3pin1=1;
        motor3pin2=0;
        motor4pin1=0;
        motor4pin2=1;
    }
    else{
        motor1pin1=0;
        motor1pin2=0;
        motor2pin1=0;
        motor2pin2=0;

        motor3pin1=0;
        motor3pin2=0;
        motor4pin1=0;
        motor4pin2=0;  
    }
}

int ultrasensor(){
    sonar.reset();
    sonar.start();
    while (echo==2) {};
    sonar.stop();
    correction = sonar.elapsed_time().count();
    
    trigger = 1;
    sonar.reset();        
    wait_us(10.0);
    trigger =0;
    while (echo==0) {};
    sonar.start();
    while (echo==1) {};
    sonar.stop();
    afstant_u = (sonar.elapsed_time().count()-correction)/58.0;

    return afstant_u;
}

float infrasensor(){
    spanning = analog_in.read() * MAXIMALE_SPANNING;
    afstant_i = 1/(0.0897*spanning - 0.0064) ;
    return afstant_i; 
}

richting scan(){
    richting vrij=non;
        buzzer.period_ms(20);
        buzzer.pulsewidth_us(1000);
        if (ultrasensor()>=30){
            vrij = links;
        }
        else{vrij=non;}
wait_us(1000000);
        buzzer.period_ms(20);
        buzzer.pulsewidth_us(2000);

        if (ultrasensor()>=30&&vrij==links){
            vrij = both;
        }
        else if(ultrasensor()>=30){
            vrij = links;
        }
        else{vrij=non;}
wait_us(1000000);
        buzzer.period_ms(20);
        buzzer.pulsewidth_us(1500);
wait_us(1000000);
        buzzer=0;

vrij=links;

return vrij;
}


void draai_90_rechts(){
    En1.write(0.25);
    En2.write(0.25);
    En3.write(0.25);
    En4.write(0.25); 
    //ra
    motor1pin1=0;
    motor1pin2=1;
    //la
    motor2pin1=0;
    motor2pin2=1;
    //rv
    motor3pin1=1;
    motor3pin2=0;
    //lv
    motor4pin1=1;
    motor4pin2=0;

wait_us(500);

    motor1pin1=0;
    motor1pin2=0;
    motor2pin1=0;
    motor2pin2=0;
    motor3pin1=0;
    motor3pin2=0;
    motor4pin1=0;
    motor4pin2=0; 
}

void draai_90_links(){
    En1.write(0.25);
    En2.write(0.25);
    En3.write(0.25);
    En4.write(0.25); 
    //ra
    motor1pin1=0;
    motor1pin2=1;
    //la
    motor2pin1=0;
    motor2pin2=1;
    //rv
    motor3pin1=1;
    motor3pin2=0;
    //lv
    motor4pin1=1;
    motor4pin2=0;

wait_us(500);

    motor1pin1=0;
    motor1pin2=0;
    motor2pin1=0;
    motor2pin2=0;
    motor3pin1=0;
    motor3pin2=0;
    motor4pin1=0;
    motor4pin2=0; 
}

void done(){
    while(knop==1){
        led1=!led1;
        led2=!led2;
        wait_us(500);
    }

}
void turn(richting vrij){
    if(vrij==links){
        draai_90_links();
        vooruit(true);
        wait_us(500);
        vooruit(false);
        draai_90_links();
    }
    /*if(vrij==rechts){
        draai_90_rechts();
        vooruit(true);
        wait_us(500);
        vooruit(false);
        draai_90_rechts();
    }*/
}