#include <ipst.h>                                // เรียกใช้งานไลบรารีสำหรับ IPST-SE
#include <PS2X_lib.h>                            // เรียกใช้งานไลบรารีสำหรับ PS2 Controller

#define PS2_DAT        29                        // กำหนดขา Data    เป็นขา 16
#define PS2_CMD        27                        // กำหนดขา Command เป็นขา 17
#define PS2_SEL        28                        // กำหนดขา Select  เป็นขา 18
#define PS2_CLK        30                        // กำหนดขา Clock   เป็นขา 19

PS2X ps2x;                                       // ประกาศตัวแปรสำหรับ PS2 Controller

int servoGrab = 0;                              // ตัวแปรสำหรับเก็บองศาของเซอร์โวที่ใช้หนีบวัตถุ
int servoLift = 0;                              // ตัวแปรสำหรับเก็บองศาของเซอร์โวที่ใช้ยกแขนจับ

boolean isR1 = false;                            // สภานะของปุ่ม R1
boolean isR2 = false;                            // สภานะของปุ่ม R2

boolean isL1 = false;                            // สภานะของปุ่ม L1
boolean isL2 = false;                            // สภานะของปุ่ม L2

void setup()
{
  delay(1000);                                   // หน่วงเวลา 1 วินาทีเพื่อรอให้บอร์ดพร้อมทำงาน
  glcdClear();                                   // เคลียร์ภาพทั้งหมดบนหน้าจอแสดงผล
  glcdMode(1);                                   // กำหนดให้หน้าจอแสดงผลเป็นแนวนอน
  
  servo(1, servoGrab);                           // กำหนดองศาเริ่มต้นให้กับเซอร์โวที่ใช้หนีบวัตถุ
  servo(2, servoLift);                           // กำหนดองศาเริ่มต้นให้กับเซอร์โวที่ใชยกแขนจับ
  delay(200);                                    // หน่วงเวลา 200 มิลลิวินาที
  
  glcd(0, 0, "Connecting");                      // แสดงข้อความเพื่อให้รู้ว่ากำลังทำการเชื่อมต่อกับ PS2 Controller
      
  while(true)                                    // วนการทำงานเพื่อรอการเชื่อมต่อกับ PS2 Controller
  {
    // กำหนดขาที่จะเชื่อมต่กับ PS2 Controller โดยมีการเก็บค่าที่ส่งกลับมาเป็น Integer เพื่อรู้ได้ว่าเชื่อมต่อได้หรือไม่
    int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);
  
    if(error == 0)                               // กรณีที่เชื่อมต่อได้ ไม่มีปัญหาอะไร (Error = 0)
    {
      glcd(0, 0, "OK           ");               // แสดงข้อความว่าเชื่อมต่อกับ PS2 Controller เรียบร้อยแล้ว
      delay(1000);                               // หน่วงเวลา 1 วินาที
      glcdClear();                               // เคลียร์ภาพทั้งหมดบนหน้าจอแสดงผล
      break;                                     // ออกจาก while(true)
    } 
    delay(500);                                  // หน่วงเวลา 500 มิลลิวินาทีเพื่อรอการเชื่อมต่อครั้งต่อไปในกรณีที่เชื่อมต่อไม่สำเร็จ
  }
}

void loop()
{
  ps2x.read_gamepad(false, false);               // อ่านข้อมูลจาก PS2 Controller
  
  if(ps2x.Button(PSB_R1))                        // ถ้าปุ่ม R1 ถูกกด
    isR1 = true;                                 // กำหนดสถานะของ isR1 เป็น True
  else                                           // ถ้าปุ่ม R1 ไม่ถูกกด
    isR1 = false;                                // กำหนดสถานะของ isR1 เป็น False
    
  if(ps2x.Button(PSB_R2))                        // ถ้าปุ่ม R2 ถูกกด 
    isR2 = true;                                 // กำหนดสถานะของ isR2 เป็น True
  else                                           // ถ้าปุ่ม R2 ไม่ถูกกด
    isR2 = false;                                // กำหนดสถานะของ isR2 เป็น False
    
  if(ps2x.Button(PSB_L1))                        // ถ้าปุ่ม L1 ถูกกด 
    isL1 = true;                                 // กำหนดสถานะของ isL1 เป็น True
  else                                           // ถ้าปุ่ม L1 ไม่ถูกกด
    isL1 = false;                                // กำหนดสถานะของ isL1 เป็น False
    
  if(ps2x.Button(PSB_L2))                        // ถ้าปุ่ม L2 ถูกกด 
    isL2 = true;                                 // กำหนดสถานะของ isL2 เป็น True
  else                                           // ถ้าปุ่ม L2 ไม่ถูกกด
    isL2 = false;                                // กำหนดสถานะของ isL2 เป็น False
    
  if(ps2x.Button(PSB_TRIANGLE))                  // เมื่อปุ่มสามเหลี่ยมถูกกด
  {
    servo(1, -1);                                // ผ่อนเซอร์โวทั้งสองตัว
    servo(2, -1);
  } 
  
  if(ps2x.Button(PSB_PAD_UP))                    // ถ้าปุ่มขึ้นถูกกด
    fd(90);                                      // สั่งงานให้หุ่นยนต์เดินหน้า
  else if(ps2x.Button(PSB_PAD_DOWN))             // ถ้าปุ่มลงถูกกด
    bk(90);                                      // สั่งงานให้หุ่นยนต์ถอยหลัง
  else if(ps2x.Button(PSB_PAD_LEFT))             // ถ้าปุ่มซ้ายถูกกด
    sl(80);                                      // สั่งงานให้หุ่นยนต์เลี้ยวซ้าย
  else if(ps2x.Button(PSB_PAD_RIGHT))            // ถ้าปุ่มขวาถูกกด
    sr(80);                                      // สั่งงานให้หุ่นยนต์เลี้ยวขวา
  else                                           // ถ้าไม่มีปุ่มทิศทางใดๆถูกกด
    ao();                                        // หุ่นยนต์หยุดเคลื่อนที่
  
  if(isR2)                                       // เมื่อสถานะของ isR1 เป็น True (ถูกกด) : หนีบวัตถุ
  {  
    servoGrab += 1;                              // องศาของเซอร์โวเพิ่มขึ้น 2 องศา
    servoGrab = (servoGrab > 180) ? 180 : servoGrab; // ให้ค่าองศาของเซอร์โวสูงสุดแค่ 140 องศา
    servo(1, servoGrab);                         // กำหนดองศาของเซอร์โวที่เก็บไว้ในตัวแปร servoGrab
  } 
  else if(isR1)                                  // เมื่อสถานะของ isR2 เป็น True (ถูกกด) : ปล่อยวัตถุ
  {
    servoGrab -= 1;                              // องศาของเซอร์โวลดลง 2 องศา
    servoGrab = (servoGrab < 0) ? 0 : servoGrab;   // ให้ค่าองศาของเซอร์โวต่ำสุดแค่ 40 องศา
    servo(1, servoGrab);                         // กำหนดองศาของเซอร์โวสำหรับหนีบของที่เก็บไว้ในตัวแปร servoGrab
  } 
  else if(isL2)                                  // เมื่อสถานะของ isL1 เป็น True (ถูกกด) : ปล่อยแขนจับให้ต่ำลง
  {
    servoLift += 1;                              // องศ่าของเซอร์โวเพิ่มขึ้น 2 องศา
    servoLift = (servoLift > 90) ? 90 : servoLift; // ให้ค่าองศาของเซอร์โวสูงสุดแค่ 135 องศา
    servo(2, servoLift);                         // กำหนดองศาของเซอร์โวสำหรับยกแขนจับที่เก็บไว้ในตัวแปร servoLift
  } 
  else if(isL1)                                  // เมื่อสถานะของ isL2 เป็น True (ถูกกด) : ยกแขนจับขึ้น
  {
    servoLift -= 1;                              // องศาของเซอร์โวลดลง 2 องศา
    servoLift = (servoLift < 0) ? 0 : servoLift;   // ให้ค่าองศาของเซอร์โวต่ำสุดแค่ 35 องศา
    servo(2, servoLift);                         // กำหนดองศาของเซอร์โวสำหรับยกแขนจับที่เก็บไว้ในตัวแปร servoLift
  }
  
  delay(10);                                     // หน่วงเวลา 50 มิลลิวินาที
}
