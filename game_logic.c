#include <stdio.h>
#include <stdlib.h>
#include "game_logic.h"


void drawBorders(int side, char vertical, char horizontal, char intersection) {
	
	int i, j, k;
	
	for(i = 0; i < side + 4; i++) {
		
		
		/* i use %4 so that it goes like ------- then 3 spaces then ------ etc */
		if(i % 4 == 0) {
			
			/* draw horizontal lines */
			for(j = 0; j < side/3; j++) {
				
				printf("%c", intersection);
				
				for(k = 0; k < side; k++) {
			
					printf("%c", horizontal);
				}	
			}
			
			printf("%c", intersection);
			
		} else {
			
			/* draw vertical lines */
			for(j = 0; j < side/3; j++) {
				
				printf("%c", vertical);
				
				for(k = 0; k < side; k++) {
			
					printf(" ");
				}	
			}
			
			printf("%c", vertical);			
		}
		
		printf("\n");
	}
}