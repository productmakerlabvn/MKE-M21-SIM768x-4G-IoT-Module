//Chương trình test MKE-M21 SIM768x 4G SMS/CALL IoT Module
//Link SP: https://www.makerlab.vn/mkem21
//Lưu ý quan trọng: SIM phải được đăng ký 4G và dịch vụ VoLTE (HD Voice) trước khi sử dụng

//Khởi tạo các biến
String SDT="0934xxxxxx"; // Biến lưu trữ số điện thoại
String feedback; // Biến lưu giá trị phan hồi từ SIM

void setup() {
  Serial.begin(9600);  // Khởi động serial với baudrate mặc định được thiết lập là 9600 (MKE-M21 SIM768x)
  //Lưu ý: Thừ nghiệm thực tế với Arduino Baudtrate cao 115200 module hoạt động kém ổn định!!!
  Serial.println("Waiting for 4G Signal on 20s"); //Chờ SIM nhận sóng 15s
  delay(15000);
  SIMsetup();
  delay(10000);
  SMSTest(); // Test gửi tin nhắn SMS
  delay(20000); // Chờ 20s
  CallTest(); // Test gọi điện đổ chuông
  //Lưu ý quan trọng, giữa các lần gọi / nhắn tin nên cách nhau tối thiểu 20s
}

void loop() {
  SIMfeedback();//Hàm đọc các giá trị phản hồi từ SIM768x`
}

void SIMfeedback() {
  for (int b = 0; b < 1000; b++) {
    feedback = "";
    delay(1); // Chờ phản hồi trong 1000ms
    if (Serial.available() > 0) {
      delay(500);  // Chờ giá trị gửi qua Serial
      feedback = "";
      while (Serial.available()) {
        char inChar = (char)Serial.read();
        feedback += inChar; // Lưu giá trị gửi qua Serial vào biến feedback
      }
      delay(100);
      b=1000;
      Serial.println(">>");
      Serial.println(feedback);// Gửi giá trị phản hồi lên máy tính
    }
  }
}

void SIMsetup() {
//Hàm thiết lập các thông số của SIM768x trước khi hoạt động
  Serial.print("AT\r\n");
  delay(1000);
  SIMfeedback();

  Serial.print("ATE0\r\n");
  delay(1000);
  SIMfeedback();

  Serial.print("AT+CSCS=\"GSM\"\r\n");
  delay(1000);
  SIMfeedback();

  Serial.print("AT+CMGF=1\r\n");
  delay(1000);
  SIMfeedback();

  Serial.print("AT+CNMI=2,2,0,0,0\r\n");
  delay(1000);
  SIMfeedback();

  Serial.print("AT+CMGD=1\r\n");
  delay(1000);
  SIMfeedback();

  Serial.print("AT+CLIP=1\r\n");
  delay(1000);
  SIMfeedback();

  Serial.print("AT&W\r\n");
  delay(1000);
  SIMfeedback();

  Serial.print("AT+CSQ\r\n");
  delay(1000);
  SIMfeedback();
}

void CallTest() {
  Serial.print("ATD"); // Quay số
  Serial.print(SDT); // Số điện thoại cần gọi
  Serial.println(";");
  delay(200);
  SIMfeedback();
  delay(10000);// Thời gian chờ đổ chuông 10s
  Serial.println("AT+CHUP");// Cúp máy
  delay(200);
}

void SMSTest() {

  Serial.print("AT+CMGS=\"" + SDT + "\"\r");  // Gửi tin nhắn đền SDT
  delay(100);
  Serial.print("Test SMS SIM768x");  // Nội dung tin nhắn
  delay(100);
  Serial.println((char)26);  // Kết thúc gửi tin nhắn
  delay(1000);
}

