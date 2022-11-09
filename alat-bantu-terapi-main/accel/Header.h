#include <MegunoLink.h>
#include <CommandHandler.h>
#include <ArduinoTimer.h>
#include <AccelStepper.h>
#include <vector_type.h>
#include <Math.h>
#include <ListLib.h>

#define KANAN 1
#define KIRI 0
#define BELAKANG -1
#define DEPAN 1

#define MOTOR_LIST {'RT','RM','RB','LT','LM','LB'}

#define STEPS_PER_ROTATION 800

#define TINGGI_SELURUH 92.5
#define PANJANG_PAHA 41
#define PANJANG_BETIS 41
#define PANJANG_TELAPAK 24.7
#define TINGGI_MATAKAKI 10.5

int kakiPilihan = KANAN;
int paha_rotation = DEPAN;
int betis_rotation = BELAKANG;
int telapak_rotation = BELAKANG;
int motor_speed = 200;
int motor_accel = 50;
int button = A5;
