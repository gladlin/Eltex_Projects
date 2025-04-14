CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
LDFLAGS = -lncurses
BUILD_DIR = build

all: $(BUILD_DIR)/server $(BUILD_DIR)/client

$(BUILD_DIR)/server: $(BUILD_DIR)/server.o $(BUILD_DIR)/server_threads.o $(BUILD_DIR)/common.o $(BUILD_DIR)/server_functional.o $(BUILD_DIR)/ui.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/client: $(BUILD_DIR)/client.o $(BUILD_DIR)/client_threads.o $(BUILD_DIR)/common.o $(BUILD_DIR)/client_functional.o $(BUILD_DIR)/ui.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/server.o: server/server.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/server_threads.o: server/server_threads.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/server_functional.o: server/server_functional.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/client.o: chat/client.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/client_threads.o: chat/client_threads.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/client_functional.o: chat/client_functional.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/common.o: common/common.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/ui.o: ncurses/ui.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/server $(BUILD_DIR)/client
