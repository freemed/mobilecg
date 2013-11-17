#ifndef INT24_H
#define INT24_H

const int INT24_MAX = 8388607;

class __attribute__((packed)) int24
{
protected:
    unsigned char m_Internal[3];
public:
    int24()
    {
    }

    int24( const int val )
    {
        *this   = val;
    }

    int24( const int24& val )
    {
        *this   = val;
    }

    operator int() const
    {
        if ( m_Internal[2] & 0x80 ) // Is it negative? 
        {
            return (0xff << 24) | (m_Internal[2] << 16) | (m_Internal[1] << 8) | (m_Internal[0] << 0);
        }
        else
        {
            return (m_Internal[2] << 16) | (m_Internal[1] << 8) | (m_Internal[0] << 0);
        }
    }

    operator float() const
    {
        return (float)this->operator int();
    }

    int24& operator =( const int24& input )
    {
        m_Internal[0]   = input.m_Internal[0];
        m_Internal[1]   = input.m_Internal[1];
        m_Internal[2]   = input.m_Internal[2];

        return *this;
    }

    int24& operator =( const int input )
    {
        m_Internal[0]   = input & 0xff;
        m_Internal[1]   = (input >> 8) & 0xff;
        m_Internal[2]   = (input >> 16) & 0xff;

        return *this;
    }
};

#endif
