//----------------------------------------------------------------------------
// Copyright [2014] [Ztachip Technologies Inc]
//
// Author: Vuong Nguyen
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except IN compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to IN writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//------------------------------------------------------------------------------

#ifndef _SOC_H_
#define _SOC_H_

#include <stdint.h>
#include "../base/types.h"
#include "../base/zta.h"

#define DISPLAY_WIDTH       640

#define DISPLAY_HEIGHT      480

#define WEBCAM_WIDTH        640

#define WEBCAM_HEIGHT       480

// Memory mapped of APB bus

#define APB ((volatile unsigned int *)0xC0000000)

//--------------- APB register map -------------------------

// GPIO memory map

#define APB_LED_BASE          (0/4)

#define APB_LED               (APB_LED_BASE+0)

#define APB_PB                (APB_LED_BASE+1)

// Camera memory map (axi_rstream)

#define APB_CAMERA_BASE       (0x10000/4)

#define APB_CAMERA_ENABLE     (APB_CAMERA_BASE+0)

#define APB_CAMERA_CURR_FRAME (APB_CAMERA_BASE+1)

#define APB_CAMERA_BUFFER     (APB_CAMERA_BASE+2)

// Video memory map (axi_wstream)

#define APB_VIDEO_BASE        (0x20000/4)

#define APB_VIDEO_ENABLE      (APB_VIDEO_BASE+0)

#define APB_VIDEO_CURR        (APB_VIDEO_BASE+1)

#define APB_VIDEO_BUFFER      (APB_VIDEO_BASE+2)

// UART memory map

#define APB_UART_BASE         (0x30000/4)

#define APB_UART_READ         (APB_UART_BASE+0) 

#define APB_UART_WRITE        (APB_UART_BASE+1) 

#define APB_UART_READ_AVAIL   (APB_UART_BASE+2) 

#define APB_UART_WRITE_AVAIL  (APB_UART_BASE+3) 

// Timer memory map

#define APB_TIME_BASE         (0x40000/4)

#define APB_TIME_GET          (APB_TIME_BASE+0) 

#define APB_TIME2_GET         (APB_TIME_BASE+1)

// Ethernet memory map

#define APB_ETH_BASE          (0x60000/4)

#define APB_ETH_TXPINGBUF     (APB_ETH_BASE+0/4)

#define APB_ETH_TXPONGBUF     (APB_ETH_BASE+0x800/4)

#define APB_ETH_RXPINGBUF     (APB_ETH_BASE+0x1000/4)

#define APB_ETH_RXPONGBUF     (APB_ETH_BASE+0x1800/4)

#define APB_ETH_GIE           (APB_ETH_BASE+0x7F8/4)

#define APB_ETH_MDIOADDR      (APB_ETH_BASE+0x7E4/4)

#define APB_ETH_MDIOWR        (APB_ETH_BASE+0x7E8/4)

#define APB_ETH_MDIORD        (APB_ETH_BASE+0x7EC/4)

#define APB_ETH_MDIOCTRL      (APB_ETH_BASE+0x7F0/4)

#define APB_ETH_TXPINGLEN     (APB_ETH_BASE+0x7F4/4)

#define APB_ETH_TXPINGCTRL    (APB_ETH_BASE+0x7FC/4)

#define APB_ETH_TXPONGLEN     (APB_ETH_BASE+0xFF4/4)

#define APB_ETH_TXPONGCTRL    (APB_ETH_BASE+0xFFC/4)

#define APB_ETH_RXPINGCTRL    (APB_ETH_BASE+0x17FC/4)

#define APB_ETH_RXPONGCTRL    (APB_ETH_BASE+0x1FFC/4)

// Flush data cache with VexRiscv
// This is dependent on the Riscv implementation since flushing datacache
// is not defined in official Riscv specs

#ifdef __WIN32__
#define FLUSH_DATA_CACHE() {}
#else
#define FLUSH_DATA_CACHE()  {asm(".word 0x500F");}
#endif

extern uint8_t *DisplayCanvas;

#ifdef __cplusplus
extern "C" {
#endif
ZtaStatus DisplayInit(int w,int h);

inline uint8_t *DisplayGetBuffer(void) {return DisplayCanvas;}

ZtaStatus DisplayUpdateBuffer(void);

ZtaStatus CameraInit(int w,int h);

bool CameraCaptureReady();

uint8_t *CameraGetCapture(void);

void LedSetState(uint32_t ledState);

uint32_t PushButtonGetState();

uint8_t UartRead();

void UartWrite(uint8_t ch);

int UartReadAvailable();

int UartWriteAvailable();

ZtaStatus EthernetLiteInit(uint8_t *macAddr);

int EthernetLiteSend(uint8_t *pkt,int pktLen);

int EthernetLiteReceive(uint8_t *pkt,int pktLen);

#ifdef __cplusplus
}
#endif

#define TimeGet() (APB[APB_TIME_GET])

#define Time2Get() (APB[APB_TIME2_GET])

#endif
