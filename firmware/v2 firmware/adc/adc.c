//!
//! \file       adc.c
//! \author     Abdelrahman Ali
//! \date       2024-09-08
//!
//! \brief      adc dac pio.
//!

//---------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------

#include "adc.h"

#include "adc.pio.h"

//---------------------------------------------------------------------------
// GLOBAL VARIABLES
//---------------------------------------------------------------------------

PIO pio_adc;
uint sm;
uint offset;
// uint sm2;
// uint offset2;
uint dma_chan;
dma_channel_config dma_chan_cfg;
uint16_t buffer[SAMPLE_COUNT];
uint8_t trigger;

//---------------------------------------------------------------------------
// ADC INIT FUNCTION
//---------------------------------------------------------------------------

void pio_adc_init()
{
    pio_adc = pio0;
    sm = pio_claim_unused_sm(pio_adc, true);
    offset = pio_add_program(pio_adc, &adc_program);
    adc_program_init(pio_adc, sm, offset, PIN_BASE, ADC_CLK);
    dma_chan = dma_claim_unused_channel(true);
    dma_chan_cfg = dma_channel_get_default_config(dma_chan);
    channel_config_set_transfer_data_size(&dma_chan_cfg, DMA_SIZE_16);
    channel_config_set_read_increment(&dma_chan_cfg, false);
    channel_config_set_write_increment(&dma_chan_cfg, true);
    channel_config_set_dreq(&dma_chan_cfg, pio_get_dreq(pio_adc, sm, false));
}

//---------------------------------------------------------------------------
// ADC DMA FUNCTION
//---------------------------------------------------------------------------

void pio_adc_dma()
{
    dma_channel_configure(dma_chan, &dma_chan_cfg, buffer, &pio_adc->rxf[sm], SAMPLE_COUNT, true);

    dma_channel_wait_for_finish_blocking(dma_chan);
}

//---------------------------------------------------------------------------
// ADC PREPARE SAMPLES FUNCTION
//---------------------------------------------------------------------------

void pio_adc_prepare_samples(uint16_t *samples)
{
    for (uint16_t i = 0; i < SAMPLE_COUNT; ++i)
    {
        samples[i] = samples[i] & 0x03FF;
    }
}

//---------------------------------------------------------------------------
// ADC CLEAN FIFO FUNCTION
//---------------------------------------------------------------------------

void pio_adc_clear_fifos()
{
    pio_sm_clear_fifos(pio_adc, sm);
}

//---------------------------------------------------------------------------
// ADC MAIN FUNCTION
//---------------------------------------------------------------------------

void adc_trigger()
{

    while (1)
    {
        printf("Enter a triggering number: ");
        trigger = getchar();
        printf("%d\n", trigger - '0');
        if (trigger == '1')
        {
            break;
        }
    }
    pio_adc_clear_fifos();
    pio_adc_dma();
    // pio_adc_prepare_samples(buffer);

    printf("----------Start of ACQ----------\n");

    for (uint16_t i = 0; i < SAMPLE_COUNT; ++i)
    {
        printf("%X,", buffer[i]);
    }

    printf("\n-----------End of ACQ-----------\n");
}

//---------------------------------------------------------------------------
// END OF FILE
//---------------------------------------------------------------------------
