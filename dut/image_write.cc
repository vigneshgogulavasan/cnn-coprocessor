#include "Vimage_write.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

typedef Vimage_write TB;
#include "testbench.hh"

void prep(const std::string port, const std::vector<uint64_t> &value) {

  if ("rst" == port) {
    dut->rst = static_cast<uint8_t>(value[0]);
  } else if ("cfg_data" == port) {
    dut->cfg_data = static_cast<const uint32_t>(value[0]);
  } else if ("cfg_addr" == port) {
    dut->cfg_addr = static_cast<const uint8_t>(value[0]);
  } else if ("cfg_valid" == port) {
    dut->cfg_valid = static_cast<const uint8_t>(value[0]);
  } else if ("next" == port) {
    dut->next = static_cast<const uint8_t>(value[0]);
  } else if ("str_img_val" == port) {
    dut->str_img_val = static_cast<const uint8_t>(value[0]);
  } else if ("str_img_bus" == port) {
    for (std::size_t i = 0; i != value.size(); ++i) {
      dut->str_img_bus[i] = static_cast<const uint8_t>(value[i]);
    }
  } else {
    printf("WARNING: requested port \'%s\' not found.\n", port.c_str());
  }
}

py::dict update() {

  py::list str_img_bus;
  for (auto &item : dut->str_img_bus) {
    str_img_bus.append(item);
  }

  py::list wr_data;
  for (auto &item : dut->wr_data) {
    wr_data.append(item);
  }

  return py::dict (
    "rst"_a = dut->rst,
    "cfg_data"_a = dut->cfg_data,
    "cfg_addr"_a = dut->cfg_addr,
    "cfg_valid"_a = dut->cfg_valid,
    "next"_a = dut->next,
    "next_rdy"_a = dut->next_rdy,
    "str_img_bus"_a = str_img_bus,
    "str_img_val"_a = dut->str_img_val,
    "str_img_rdy"_a = dut->str_img_rdy,
    "wr_val"_a = dut->wr_val,
    "wr_addr"_a = dut->wr_addr,
    "wr_data"_a = wr_data
  );
}
