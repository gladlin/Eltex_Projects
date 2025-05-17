GCC = gcc
FLAGS = -Wall -Wextra  -Werror -lrt
OBJDIR = obj

all: $(OBJDIR)/ask_driver.o $(OBJDIR)/create_driver.o $(OBJDIR)/driver.o $(OBJDIR)/get_drivers.o $(OBJDIR)/get_status.o $(OBJDIR)/handle_input.o $(OBJDIR)/send_task.o $(OBJDIR)/CLI.o
	$(GCC) $(FLAGS) $(OBJDIR)/*.o -o taxi

$(OBJDIR)/ask_driver.o: taxi.h ask_driver.c
	$(GCC) $(FLAGS) ask_driver.c -c -o $(OBJDIR)/ask_driver.o

$(OBJDIR)/CLI.o: taxi.h CLI.c
	$(GCC) $(FLAGS) CLI.c -c -o $(OBJDIR)/CLI.o

$(OBJDIR)/create_driver.o: taxi.h create_driver.c
	$(GCC) $(FLAGS) create_driver.c -c -o $(OBJDIR)/create_driver.o

$(OBJDIR)/driver.o: taxi.h driver.c
	$(GCC) $(FLAGS) driver.c -c -o $(OBJDIR)/driver.o

$(OBJDIR)/get_drivers.o: taxi.h get_drivers.c
	$(GCC) $(FLAGS) get_drivers.c -c -o $(OBJDIR)/get_drivers.o

$(OBJDIR)/get_status.o: taxi.h get_status.c
	$(GCC) $(FLAGS) get_status.c -c -o $(OBJDIR)/get_status.o

$(OBJDIR)/handle_input.o: taxi.h handle_input.c
	$(GCC) $(FLAGS) handle_input.c -c -o $(OBJDIR)/handle_input.o

$(OBJDIR)/send_task.o: taxi.h send_task.c
	$(GCC) $(FLAGS) send_task.c -c -o $(OBJDIR)/send_task.o

clean:
	rm -f $(OBJDIR)/*.o taxi