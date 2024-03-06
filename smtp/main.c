#include <stdio.h>
#include <string.h>

int connect_smtp(const char* host, int port);
void send_smtp(int sock, const char* msg, char* resp, size_t len);
// Function to read the file into a buffer
void read_file(const char* filepath, char* buffer, size_t buffer_size);



/*
  Use the provided 'connect_smtp' and 'send_smtp' functions
  to connect to the "lunar.open.sice.indian.edu" smtp relay
  and send the commands to write emails as described in the
  assignment wiki.
 */
int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("Invalid arguments - %s <email-to> <email-filepath>", argv[0]);
    return -1;
  }

  char* rcpt = argv[1];
  char* filepath = argv[2];
  char response[4096];

  // Connect to the SMTP server
  int socket = connect_smtp("lunar.open.sice.indiana.edu", 25);

  send_smtp(socket, "HELO www.google.com\n", response, sizeof(response));
  printf("%s\n", response);

  char mailFromCommand[256];
  snprintf(mailFromCommand, sizeof(mailFromCommand), "MAIL FROM:<%s>\n", rcpt);
  send_smtp(socket, mailFromCommand, response, sizeof(response));
  printf("%s\n", response);

  char rcptToCommand[256];
  snprintf(rcptToCommand, sizeof(rcptToCommand), "RCPT TO:<%s>\n", rcpt);
  send_smtp(socket, rcptToCommand, response, sizeof(response));
  printf("%s\n", response);

  char emailMessage[4096];  // Assuming a maximum message size of 4096 characters
  read_file(filepath, emailMessage, sizeof(emailMessage));

  send_smtp(socket, "DATA\n", response, sizeof(response));
  printf("%s\n", response);

  char dataCommand[4096];
  snprintf(dataCommand, sizeof(dataCommand), "%s\r\n.\r\n", emailMessage);
  printf("%s\n", dataCommand);
  send_smtp(socket, dataCommand, response, sizeof(response));
  printf("%s\n", response);

  // Close the connection
  send_smtp(socket, "quit\n", response, sizeof(response));
  printf("%s\n", response);


  return 0;
}

void read_file(const char* filepath, char* buffer, size_t buffer_size) {
  FILE* file = fopen(filepath, "r");
  if (file != NULL) {
    size_t bytesRead = fread(buffer, 1, buffer_size, file);
    fclose(file);
    // Ensure the buffer is null-terminated
    buffer[bytesRead] = '\0';
  } else {
    printf("Error opening file: %s\n", filepath);
    // Handle the error appropriately
  }
}
