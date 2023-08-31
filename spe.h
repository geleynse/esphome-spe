#include "SparkFun_SinglePairEthernet.h"
#include "esphome/core/application.h"

class Spe : public PollingComponent, public Sensor {
 public:
  Spe() : PollingComponent(15000) {}

  float get_setup_priority() const override {
    return esphome::setup_priority::DATA;
  }

  static bool macsEqual(const uint8_t * mac1, const uint8_t * mac2)
{
    if(!mac1 || !mac2)
    {
        return false;
    }
    return( (mac1[0] == mac2[0]) &&
            (mac1[1] == mac2[1]) &&
            (mac1[2] == mac2[2]) &&
            (mac1[3] == mac2[3]) &&
            (mac1[4] == mac2[4]) &&
            (mac1[5] == mac2[5]) );
}

  static void rxCallback(byte* data, int dataLen, byte* senderMac) {
    if (macsEqual(senderMac, Spe::remoteMAC)) {
      // Process received data here.
    }
  }

  void setup() override {
    ESP_LOGD("SPE", "Single Pair Ethernet");
    uint8_t mac = *deviceMAC; // make a mutable copy which begin expects
    if (!adin1110.begin(&mac)) {
      ESP_LOGD("SPE", "Failed to connect Single Pair Ethernet");
      return;
    }

    ESP_LOGD("SPE", "Configured SPE");
  }
  void update() override {
    if (adin1110.getLinkStatus() != true) {
      ESP_LOGD("SPE", "No link");
    } else {
      ESP_LOGD("SPE", "Link");
    }
  }

 private:
  SinglePairEthernet adin1110;

  static constexpr byte deviceMAC[6] = {0x00, 0xE0, 0x22, 0xFE, 0xDA, 0xCA};
  static constexpr byte remoteMAC[6] = {0x00, 0xE0, 0x22, 0xFE, 0xDA, 0xC9};
};
