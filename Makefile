all:
# Compile object files
	g++ -c WiFi.cpp -o WiFi.o
	g++ -c WiFi4.cpp -o WiFi4.o
	g++ -c WiFi5.cpp -o WiFi5.o
	g++ -c WiFi6.cpp -o WiFi6.o
	g++ -c AccessPoint.cpp -o AccessPoint.o
	g++ -c Report.cpp -o Report.o
	g++ -c FrequencyChannel.cpp -o FrequencyChannel.o
	g++ -c Packet.cpp -o Packet.o
	g++ -c User.cpp -o User.o
# Create static library
	ar rcs libwifi_simulation.a  WiFi.o WiFi4.o WiFi5.o WiFi6.o AccessPoint.o Report.o FrequencyChannel.o Packet.o User.o
# Without optimization or debugging
	g++ simulation.cpp -L. -lwifi_simulation -o wifi_simulation
# Debug build
	g++ -g simulation.cpp -L. -lwifi_simulation -o wifi_simulation_debug
# Optimized build
	g++ -O3 simulation.cpp -L. -lwifi_simulation -o wifi_simulation_optimized

clean:
	rm -f *.o libwifi_simulation.a wifi_simulation wifi_simulation_debug wifi_simulation_optimized
