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
    bool isBusy() const;
    void waitUntilNotBusy() const;

    /**
     * Write a byte of data to CGRAM/DDRAM
    */
    void write(uint8_t);

    uint8_t read();

protected:

    void _writeDR(uint8_t d);
    void _writeIR(uint8_t d);
    uint8_t _readDR();
    uint8_t _readIR() const;

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
    virtual uint8_t _readIR8() const = 0;
    
    virtual void _waitUs(uint16_t ms) const = 0;

private:

    const bool _isFourBit;
    const uint8_t _displayLines;
    const bool _fontMode;
};

#endif
