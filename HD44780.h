#ifndef _HD44780_h
#define _HD44780_h

#include <cstdint>

/**
 * IMPORTANT: This class should be "pure C++" and should 
 * not be making any assumptions about the hardward environment
 * that it is working in.  
*/
class HD44780 {
public:

    HD44780(bool isFourBit, uint8_t displayLines, bool fontMode);

    void init();
    void clearDisplay();
    void returnHome();
    void setEntryMode(bool increment, bool shift);
    void setDisplay(bool displayOn, bool cursorOn, bool blinkOn);
    void shift(bool displayShift, bool shiftRight);
    void setCGRAMAddr(uint8_t);
    void setDDRAMAddr(uint8_t);
    bool isBusy();
    void waitUntilNotBusy();

    /**
     * Write a byte of data to CGRAM/DDRAM at the currently
     * selected address.
     * 
     * IMPORTANT: This is a "raw" write, meaning that the 
     * display will not be filled linearly, depending on
     * the mapping of the addresses to the screen positions.
    */
    void write(uint8_t data);

    /**
     * Writes multiple data bytes. The assumption here is that 
     * the address is setup to increment. By default this 
     * just loops and calls single-byte write().
     * 
     * IMPORTANT: This is a "raw" write, meaning that the 
     * display will not be filled linearly, depending on
     * the mapping of the addresses to the screen positions.
    */
    virtual void write(uint8_t* data, uint16_t len);

    uint8_t read();

    uint16_t getBusyCount() const { return _busyCount; };

    enum Format { FMT_20x4 };

    /**
     * A utility function that will write all of the data into 
     * the display buffer in a "linear" fashion, meaing that the
     * quirks of the layout will be resolved automatically.
    */
    void writeLinear(Format format, 
        uint8_t* data, uint8_t len, uint8_t startPos);

protected:

    /**
     * A utility function that knows how to convert a linear 
     * position to an address in the LCD data memory.
    */
    static uint8_t _linearPosToAddr(Format format, uint8_t pos);

    void _writeDR(uint8_t d);
    void _writeIR(uint8_t d);
    uint8_t _readDR();
    uint8_t _readIR();

    /**
     * Used to write into the IR, regardless of the configuration.
     * If the interface is running in 4-bit mode then only
     * the 4 LSBs will be used.
    */
    virtual void _writeIR8(uint8_t d) = 0;

    /**
     * Used to write into the DR, regardless of the configuration.
     * If the interface is running in 4-bit mode then only
     * the 4 LSBs will be used.
    */
    virtual void _writeDR8(uint8_t d) = 0;

    virtual uint8_t _readDR8() = 0;
    virtual uint8_t _readIR8() = 0;

    virtual void _waitUs(uint16_t ms) const = 0;

private:

    const bool _isFourBit;
    const uint8_t _displayLines;
    const bool _fontMode;
    uint16_t _busyCount = 0;
};

#endif
