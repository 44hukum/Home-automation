/**
 * HOME AUTOMATION, HOME LIGHT CONTROL WITH ARDUINO, 4CHANNEL RELAY   
 * */


int IN1 = 3;
int IN2 = 4;
int IN3 = 5;
int IN4 = 6;

#define ON 0
#define OFF 1

char val;        // variable to receive data from the serial port
int ledpin = 13; // LED connected to pin 2 (on-board LED)

void setup()
{

  Serial.begin(9600); // start serial communication at 115200bps
  relay_init();       //initialize the relay
}

void loop()
{
  if (Serial.available())
  {
    val = Serial.read(); // read it and store it in 'val'

    if (val == '1')
    {
      relay_SetStatus(IN1, ON); //turn on RELAY_1
    }

    if (val == '2')
    {
      relay_SetStatus(IN2, ON); //turn on RELAY_2
    }
    if (val == '3')
    {
      relay_SetStatus(IN3, ON); //turn on RELAY_3
    }

    if (val == '4')
    {
      relay_SetStatus(IN4, ON); //turn on RELAY_4
    }

    // turn them off
    if (val == '5')
    {
      relay_SetStatus(IN1, OFF); //turn off RELAY_1
    }

    if (val == '6')
    {
      relay_SetStatus(IN2, OFF); //turn off RELAY_2
    }

    if (val == '7')
    {
      relay_SetStatus(IN3, OFF); //turn off RELAY_3
    }
    if (val == '8')
    {
      relay_SetStatus(IN4, OFF); //turn off RELAY_4
    }
  }
}

void relay_init(void) //initialize the relay
{
  //set all the relays OUTPUT
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  relay_SetStatus(IN1, OFF); //turn off all the relay
  relay_SetStatus(IN2, OFF); //turn off all the relay
  relay_SetStatus(IN3, OFF); //turn off all the relay
  relay_SetStatus(IN4, OFF); //turn off all the relay
}
//set the status of relays
void relay_SetStatus(int channel, unsigned char status)
{
  digitalWrite(channel, status);
}
