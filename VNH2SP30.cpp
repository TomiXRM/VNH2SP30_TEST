#include "mbed.h"

Serial pc(USBTX,USBRX);

PwmOut PWM(D15);
DigitalOut INA(D14);
DigitalOut INB(D12);


void turnMotor(float power){
        //power:-100 to 100
        if(power > 100) {
                power = 100;
        }else if(power < -100) {
                power = -100;
        }
        if(abs(power) > 0) {
                if(power > 0) {
                        INA.write(1);
                        INB.write(0);
                }else{
                        INA.write(0);
                        INB.write(1);
                }
        }else{
                INA = 1;
                INB = 1;
        }
        PWM.write(abs(power)/100);
}
int main(){
        pc.baud(230400);
        PWM.period_us(50);
        while (1) {
                for (int i = -100; i < 100; i++) {
                        turnMotor(i);
                        wait_ms(8);
                }
                for (int i = 100; i > -100; i--) {
                        turnMotor(i);
                        wait_ms(8);
                }
        }
}
