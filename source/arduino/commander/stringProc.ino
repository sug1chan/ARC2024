//  Split string by delimiter
int split(String &data, char delimiter, String *dst, int dstNum)
{
    int index = 0; 
    int datalength = data.length();

    if (dstNum <= 0) return 0;
    for (int i = 0; i < dstNum; i++) dst[i] = "";
    
    for (int i = 0; i < datalength; i++)
    {
        char tmp = data.charAt(i);
        if ( tmp == delimiter )
        {
          if ((index+1) >= dstNum) break;
          index++;
        }
        else
        {
          dst[index] += tmp;
        }    
    }
    
    return (index+1);
}