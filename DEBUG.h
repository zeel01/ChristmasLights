#ifndef DEBUG_H
#define DEBUG_H

	#define DEBUG			// Comment out to disable debugging
	#define MEMORYFREE		// Comment out to disable MemoryFree
	
	#ifdef DEBUG
		#include <Arduino.h>
	
		namespace Debug {
			template<typename T>
			static void print(T&& msg) {
				Serial.print(msg);
			}
			
			template<typename T, typename... Ts>
			static void print(T&& msg, Ts&&... msgs) {
				print(msg);
				print(' ');
				print(msgs...);
			}
			
			template<typename T>
			static void println(T&& msg) {
				Serial.println(msg);
			}
			
			template<typename T, typename... Ts>
			static void println(T&& msg, Ts&&... msgs) {
				println(msg);
				println(' ');
				println(msgs...);
			}
		};
		
		
		#ifdef __cplusplus
		extern "C" {
		#endif

		int freeMemory();

		#ifdef  __cplusplus
		}
		#endif
		
		
		#define PRINT_BEGIN(baud) Serial.begin(baud)
		
		#define TRACE(...)		  DPRINT(__LINE__, F(": "), __PRETTY_FUNCTION__, F("\n    "), __VA_ARGS__)
		#define TRACELN(...)	  TRACE(__VA_ARGS__); Serial.println("")
		
		#define TRACEF(msg)		  TRACE(F(msg))
		#define TRACELNF(msg)	  TRACELN(F(msg))
		
		#define NV(var)           F(#var "="), var
		
		#define DPRINT(...)       Debug::print(__VA_ARGS__)   
		#define DPRINTF(msg)      Serial.print(F(msg))   
		#define DPRINTLN(...)     Debug::print(__VA_ARGS__); Serial.println("")   
		#define DPRINTLNF(msg)    Serial.println(F(msg))   
	#else
		#define PRINT_BEGIN(baud)
	    
	    #define TRACE(...)		 
	    #define TRACELN(...)	 
	    
	    #define TRACEF(msg)		 
	    #define TRACELNF(msg)	 
	    
	    #define NV(var)          
	    
	    #define DPRINT(...)      
	    #define DPRINTF(msg)     
		#define DPRINTLN(...)    
		#define DPRINTLNF(msg)   
	#endif
	
	#if defined(DEBUG) && defined(MEMORYFREE)
		#include "MemoryFree.h"
		
		#define FREEMEMORY()     freeMemory()
		#define TRACEMEM()       TRACELN(NVMEM)
		#define NVMEM            F("Memory: "), FREEMEMORY()
	#else		
		#define FREEMEMORY()
        #define TRACEMEM()  
	    #define NVMEM       
	#endif

#endif