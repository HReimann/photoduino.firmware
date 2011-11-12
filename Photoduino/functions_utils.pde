/**
 *
 * - Photoduino
 * - http://www.photoduino.com/
 *
 * This file is part of Photoduino.
 *
 * Photoduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Photoduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Photoduino.  If not, see <http://www.gnu.org/licenses/>.
 */
 

// Write a unsigned int (two bytes) value to eeprom
void eeprom_writeInt(int address, unsigned int value){
    
  EEPROM.write(address, value/256);
  EEPROM.write(address+1, value % 256);

}

// read a unsigned int (two bytes) value from eeprom
unsigned int eeprom_readInt(int address){
  
  return EEPROM.read(address)*256+EEPROM.read(address+1);
}


// increment the value of a variable using minimun and maximun limits (byte version)
void circularList_incrementBy(byte *value, byte minimun, byte maximun, int incrementBy) {
  
  if (incrementBy>0) {
    
    if (*value+incrementBy > maximun) *value = minimun; 
    else *value = *value+incrementBy;
    
  } else {
    
    if ( (*value < minimun) || (*value < (incrementBy*(-1)) )) *value = maximun;
    else *value = *value+incrementBy;
    
  }
    
}

// increment the value of a variable using minimun and maximun limits (unsigned int version)
void circularList_incrementBy(unsigned int *value, unsigned int minimun, unsigned int maximun, int incrementBy) {
  
  if (incrementBy>0) {
    
    if (*value+incrementBy > maximun) *value = minimun; 
    else *value = *value+incrementBy;
    
  } else {
    
    if ( (*value < minimun) || (*value < (incrementBy*(-1)) )) *value = maximun;
    else *value = *value+incrementBy;
    
  }
}

// increment the value of a variable using minimun and maximun limits (unsigned int version)
void circularList_matchBy(unsigned int *value, unsigned int targetValue, unsigned int minimun, unsigned int maximun, int offset) {
  
  if (offset>0) {
    
    if (targetValue+offset > maximun) *value = maximun; 
    else *value = targetValue+offset;
    
    
  } else {
    
    if ( targetValue < (offset*(-1)) ) *value = minimun;
    else *value = targetValue+offset;
        
  }  
}

// Code to print out the free memory form aJSON library example

struct __freelist {
  size_t sz;
  struct __freelist *nx;
};

extern char * const __brkval;
extern struct __freelist *__flp;

uint16_t freeMem(uint16_t *biggest)
{
  char *brkval;
  char *cp;
  unsigned freeSpace;
  struct __freelist *fp1, *fp2;

  brkval = __brkval;
  if (brkval == 0) {
    brkval = __malloc_heap_start;
  }
  cp = __malloc_heap_end;
  if (cp == 0) {
    cp = ((char *)AVR_STACK_POINTER_REG) - __malloc_margin;
  }
  if (cp <= brkval) return 0;

  freeSpace = cp - brkval;

  for (*biggest = 0, fp1 = __flp, fp2 = 0;
     fp1;
     fp2 = fp1, fp1 = fp1->nx) {
      if (fp1->sz > *biggest) *biggest = fp1->sz;
    freeSpace += fp1->sz;
  }

  return freeSpace;
}

uint16_t biggest;

void freeMem(char* message) {
  Serial.print(message);
  Serial.print(":\t");
  Serial.println(freeMem(&biggest));
}





