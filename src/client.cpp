#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "common.hpp"

int main() {
    stdio_init_all();
    sleep_ms(3000);
    printf("Client starting up...\n");

    // Initialize the Wi-Fi module
    if (cyw43_arch_init()) {
        printf("Wi-Fi initialization failed.\n");
        return -1;
    }

    // Enable station mode
    cyw43_arch_enable_sta_mode();

    printf("Connecting to network: %s\n", WIFI_SSID);
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Failed to connect to the Wi-Fi network.\n");
        return -1;
    } else {
        printf("Connected to Wi-Fi network.\n");

        // Retrieve and print the IP address
        uint8_t *ip_addr = (uint8_t *)&cyw43_state.netif[0].ip_addr.addr;
        printf("Client IP Address: %d.%d.%d.%d\n", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    }

    // Main loop: Send periodic messages to the shotclock (this part assumes a socket-based connection)
    while (true) {
        printf("Client is connected to the network.\n");
        sleep_ms(5000); // Keep alive, placeholder for communication
    }

    // Disconnect Wi-Fi (cleanup, rarely needed in embedded environments)
    cyw43_arch_deinit();
    return 0;
}