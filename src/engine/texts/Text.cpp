#include "Text.h"
#include "TextManager.h"

Text::Text(string txt) : wBox(0), hBox(0), text(txt), inBox(""), outBox("")
{
    computeLength();
    lengthInBox = 0;
}

Text::~Text()
{
}

void Text::display(int x, int y, int l)
{
    displayInternal(x, y, l);
}

void Text::displayInternal(int x, int y, int l)
{
    int space = TextManager::getInstance()->getWSpace();

    if (l < 0)
    {
        l = length;
    }

    int style = 0;
    int count = 0;
    int begin = 0;
    bool in = false;
    for (unsigned int i = 0; i < text.length() && count < l; i++)
    {
        if (in)
        {
            if (text[i] == ']')
            {
                if (text[begin + 1] == 'c' && text[i - 1] == 'r')
                {
                    // center, do nothing
                }
                else if (text[begin + 1] == '/' && text[i - 1] == 'r')
                {
                    // /center, do nothing
                }
                else if (text[begin + 1] == 'b' && text[i - 1] == 'r')
                {
                    // br, do nothing
                }
                else
                {
                    // retrieve the new style
                    string value = text.substr(begin + 3, i - begin - 1);
                    int number;
                    istringstream ss(value);
                    ss >> number;
                    style = number;
                }
                in = false;
            }
        }
        else
        {
            if (text[i] == '[')
            {
                begin = i;
                in = true;
            }
            else
            {
                TextManager::getInstance()->drawLetter(text[i], x, y, style);
                x += space;
                count++;
            }
        }
    }
}

void Text::displayBox(int x, int y, int l)
{

    if (l == -1)
    {
        l = lengthInBox;
    }

    int wSpace = TextManager::getInstance()->getWSpace();
    // int wSize = TextManager::getInstance()->getWSize();
    int hSize = TextManager::getInstance()->getHSize();

    int nbRows = wBox / wSpace;

    int style = 0;
    int count = 0;
    int begin = 0;
    int countRow = 0;
    int countLine = 0;
    int center = 0;
    bool in = false;
    bool newWord = true;
    for (unsigned int i = 0; i < inBox.length() && count < l; i++)
    {
        if (in)
        {
            if (inBox[i] == ']')
            {
                if (text[begin + 1] == 'c' && text[i - 1] == 'r')
                {
                    // center -> add space until the end of the line and center text
                    if (countRow > 0)
                    {
                        countRow = 0;
                        countLine++;
                    }
                    center = sizeToCenter(inBox, i + 1);
                    countRow += (nbRows - center) / 2;
                }
                else if ((text[begin + 1] == '/' && text[i - 1] == 'r') ||
                         (text[begin + 1] == 'b' && text[i - 1] == 'r'))
                {
                    // /center -> go to the next line or
                    // br -> go to the next line
                    countRow = 0;
                    countLine++;
                }
                else
                {
                    // retrieve the new style
                    string value = inBox.substr(begin + 3, i - begin - 1);
                    int number;
                    istringstream ss(value);
                    ss >> number;
                    style = number;
                }
                in = false;
            }
        }
        else
        {
            if (inBox[i] == '[')
            {
                begin = i;
                in = true;
            }
            else
            {

                // we check if the current word can be displayed on the current line
                if (inBox[i] == ' ')
                {
                    if (countRow + 1 > nbRows)
                    {
                        countRow = 0;
                        countLine++;
                    }
                    newWord = true;
                }
                else
                {
                    if (newWord)
                    {
                        int tmp = wordSize(inBox, i);
                        if (tmp == 0)
                        {
                            tmp = 1;
                        }

                        if (countRow + tmp > nbRows)
                        {
                            countRow = 0;
                            countLine++;
                        }
                        newWord = false;
                    }
                }

                if (countRow == 0 && inBox[i] == ' ' && i + 1 < inBox.length() && inBox[i + 1] != ' ')
                {
                    countRow--;
                }
                else
                {
                    TextManager::getInstance()->drawLetter(inBox[i],
                                                           x + countRow * wSpace,
                                                           y + countLine * hSize,
                                                           style);
                }
                count++;
                countRow++;
            }
        }
    }
}

void Text::setBox(int w, int h)
{
    wBox = w;
    hBox = h;
    cutBox();
}

bool Text::hasNext()
{
    return (outBox.length() > 0);
}

void Text::next()
{
    text = outBox;
    computeLength();
    cutBox();
}

int Text::getWBox()
{
    return wBox;
}

int Text::getHBox()
{
    return hBox;
}

int Text::getLength()
{
    return length;
}

int Text::getLengthInBox()
{
    return lengthInBox;
}

string Text::getText()
{
    return text;
}

char Text::charAtInBox(int i)
{
    bool in = false;
    int count = 0;
    for (unsigned int j = 0; j < inBox.length(); j++)
    {
        if (in)
        {
            if (inBox[j] == ']')
            {
                in = false;
            }
        }
        else
        {
            if (inBox[j] == '[')
            {
                in = true;
            }
            else
            {
                if (count == i)
                {
                    return inBox[j];
                }
                count++;
            }
        }
    }
    return 0;
}

void Text::computeLength()
{
    length = 0;
    bool in = false;
    for (unsigned int i = 0; i < text.length(); i++)
    {
        if (in)
        {
            if (text[i] == ']')
            {
                in = false;
            }
        }
        else
        {
            if (text[i] == '[')
            {
                in = true;
            }
            else
            {
                length++;
            }
        }
    }
}

void Text::cutBox()
{
    lengthInBox = 0;

    int wSpace = TextManager::getInstance()->getWSpace();
    // int wSize = TextManager::getInstance()->getWSize();
    int hSize = TextManager::getInstance()->getHSize();

    int nbRows = wBox / wSpace;
    int nbLines = hBox / hSize;

    int countRow = 0;
    int countLine = 0;
    int begin = 0;
    int center = 0;
    bool in = false;
    for (unsigned int i = 0; i < text.length(); i++)
    {
        if (in)
        {
            if (text[i] == ']')
            {
                if (text[begin + 1] == 'c' && text[i - 1] == 'r')
                {
                    // center -> add space until the end of the line and center text
                    if (countRow > 0)
                    {
                        countRow = 0;
                        countLine++;
                        if (countLine >= nbLines)
                        {
                            inBox = text.substr(0, begin);
                            outBox = text.substr(begin, text.length() - begin);
                            return;
                        }
                    }
                    center = sizeToCenter(inBox, i + 1);
                    countRow += (nbRows - center) / 2;
                }
                else if ((text[begin + 1] == '/' && text[i - 1] == 'r') ||
                         (text[begin + 1] == 'b' && text[i - 1] == 'r'))
                {
                    // /center -> go to the next line or
                    // br -> go to the next line
                    countRow = 0;
                    countLine++;
                    if (countLine >= nbLines && i + 1 < text.length())
                    {
                        inBox = text.substr(0, i + 1);
                        outBox = text.substr(i + 1, text.length() - (i + 1));
                        return;
                    }
                }

                in = false;
            }
        }
        else
        {
            if (text[i] == '[')
            {
                begin = i;
                in = true;
            }
            else
            {

                lengthInBox++;

                if (countRow == 0 && text[i] == ' ' && i + 1 < text.length() && text[i + 1] != ' ')
                {
                    continue;
                }

                countRow++;

                // we check if the current word can be displayed on the current line
                int tmp = wordSize(text, i);
                if (tmp == 0)
                {
                    tmp = 1;
                }
                if (countRow + tmp - 1 > nbRows)
                {
                    countRow = tmp;
                    countLine++;

                    if (countLine >= nbLines)
                    {
                        inBox = text.substr(0, i);
                        outBox = text.substr(i, text.length() - i);
                        return;
                    }
                    i += (tmp - 1);
                    lengthInBox += (tmp - 1);
                }
            }
        }
    }
    inBox = text;
    outBox.clear();
}

int Text::wordSize(string txt, unsigned int i)
{
    int size = 0;
    bool in = false;
    for (; i < text.length(); i++)
    {
        if (in)
        {
            if (text[i] == ']')
            {
                in = false;
            }
        }
        else
        {
            if (text[i] == '[')
            {
                in = true;
            }
            else
            {
                if (text[i] == ' ')
                {
                    return size;
                }
                size++;
            }
        }
    }
    return size;
}

int Text::sizeToCenter(string txt, unsigned int i)
{
    int size = 0;
    bool in = false;
    for (; i < text.length(); i++)
    {
        if (in)
        {
            if (text[i] == '/' && text[i + 1] == 'c')
            {
                // /center
                return size;
            }
            else if (text[i] == ']')
            {
                in = false;
            }
        }
        else
        {
            if (text[i] == '[')
            {
                in = true;
            }
            else
            {
                size++;
            }
        }
    }
    return size;
}

int Text::getSize()
{
    return length * TextManager::getInstance()->getWSpace();
}
