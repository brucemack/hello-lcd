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
    void write(uint8_t);
    uint8_t read();

    bool isBusy() const;
    void waitUntilNotBusy() const;

protected:

    virtual void writeDR(uint8_t d) = 0;
    virtual void writeIR(uint8_t d) = 0;
    virtual uint8_t readDR() = 0;
    virtual uint8_t readIR() = 0;

private:

    const bool _isFourBit;
    const uint8_t _displayLines;
    const bool _fontMode;
};

#endif
