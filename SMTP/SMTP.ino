#include <Arduino.h>
#include <WiFi.h>
#include <ESP_Mail_Client.h>

// SMTP Server Configuration
#define SMTP_HOST "smtp.gmail.com"   // Corrected from "smtp_gmail.com"
#define SMTP_PORT 587

// Email Account Credentials
#define AUTHOR_MAIL "datasender59@gmail.com"
#define AUTHOR_PASSWORD "rbra gaud yzup pouf"
#define RECIPIENT_EMAIL "ashishdhakne77@gmail.com"


// SMTP Session Object
SMTPSession smtp;

// WiFi Credentials
const char* ssid = "123";  // YOUR WIFI NAME.
const char* password = ""; // YOUR WIFI PASSWORD


// SMTP Callback Function Declaration
void smtpCallback(SMTP_Status status);

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

 smtp.debug(1);
 smtp.callback(smtpCallback);

  // Configure SMTP Session
  Session_Config config;
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_MAIL;
  config.login.password = AUTHOR_PASSWORD;
  config.login.user_domain = "";

  // Set the callback function
  smtp.callback(smtpCallback);

  config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 3;
  config.time.day_light_offset = 0;

  // Prepare Email Message
  SMTP_Message message;
  message.sender.name = F("ESP");
  message.sender.email = AUTHOR_MAIL;
  message.subject = F("ESP Check (test mail)");
  message.addRecipient(F("Recipient"), RECIPIENT_EMAIL);

  // Optional: Add message content
  message.text.content = "Hello pagal !";
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  // Connect and Send Mail
  if (!smtp.connect(&config)) {
    Serial.printf("Connection Error: %d, Error: %d, Reason: %s\n", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
    return;
  }

  if (!MailClient.sendMail(&smtp, &message)) {
    Serial.printf("Send Error: %d, Error: %d, Reason: %s\n", smtp.statusCode(), smtp.errorCode(), smtp.errorReason().c_str());
  }
}

void loop() {
  // Empty loop
}

// SMTP Callback
void smtpCallback(SMTP_Status status) {
  Serial.println("\nSMTP Status Callback:");
  
  if (status.success()) {
    Serial.println("Mail sent successfully!");
    Serial.printf("Messages Sent: %d\n", status.completedCount());
    Serial.printf("Messages Failed: %d\n", status.failedCount());

    for (size_t i = 0; i < smtp.sendingResult.size(); i++) {
      SMTP_Result result = smtp.sendingResult.getItem(i);
      Serial.printf("Message #%d\n", i + 1);
      Serial.printf("Status: %s\n", result.completed ? "Success" : "Failed");
      Serial.printf("Date/Time: %s\n", MailClient.Time.getDateTimeString(result.timestamp, "%B %d, %Y %H:%M:%S").c_str());
      Serial.printf("Recipient: %s\n", result.recipients.c_str());
      Serial.printf("Subject: %s\n", result.subject.c_str());
      Serial.println("------------------------");
    }

    smtp.sendingResult.clear(); // Clean up
  } else {
    Serial.println("Mail send failed.");
  }
}