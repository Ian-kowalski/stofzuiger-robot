#include "mbed.h"
#include "inputs.h"

int main()
{
    buzzer.period_ms(20);
    buzzer.pulsewidth_us(1500);
    bool stop=false;
    bool back=false;
    bool running=false;
    Timer bewegen;
    richting last;
    richting vrij;

    led1=1;
    led2=1;

    while(true)
    {
        if(knop==0){
            printf("hoi");
            running=true;
        }

        while(running==true){
            if (stop==false)
            {
                vooruit(true);
            }

            while(ultrasensor()<=15||infrasensor()>=20||infrasensor()<=-1){
                stop=true;
                vooruit(false);
            
                if(infrasensor()>=20||infrasensor()<=-1){
                    back=true;
                    if(back==true){
                    bewegen.start();
                    achteruit(true);
                        if(stop==true&&bewegen.elapsed_time().count()>=200000){
                            achteruit(false);
                            back=false;
                        }
                    }
                }
            }
            while(stop==true&&back==false){
                vrij=scan();
                if(last==vrij||vrij==non){
                    done();
                    running=false;
                    }
                else if(vrij==both){
                    if(last==rechts){
                        last=links;
                        turn(links);
                        stop=false;
                    }
                    else{
                        last=rechts;
                        turn(rechts);
                        stop=false;
                    }
                }
                else{
                turn(vrij);
                vrij=last;
                stop=false;
                }
            }
        }
    
    }
}