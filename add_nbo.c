/*32 bit 숫자가 파일에 4바이트의 크기로 저장되어 있다(network byte order). 2개의 파일을 입력받아 숫자를 읽어 들여 그 합을 출력하는 프로그램을 작성하라.
ex) x000003e8, x000001f4 의 파일2개를 입력 받음 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>        // size_t를 사용하기 위한 전처리기  
#include <stdint.h>        // uint_류를 사용하기 위한 전처리기 
#include <netinet/in.h>    // ntohs를 사용하기 위한 전처리기
#include <stdlib.h>

int ascii_to_hex(char c) //ASCII 값을 HEX로 변경해주는 코드, 값의 범위를 제한함.
{
        int num = (int) c;
        if(num < 58 && num > 47)
        {
                return num - 48;
        }
        if(num < 103 && num > 96)
        {
                return num - 87;
        }
        return num;
}

int main(int argc, char *argv[]){
	printf("ARGC : %d\n", argc);
	if ( argc != 3 ) {                     // 2개의 파일만을 입력 받기 위한 조건
		printf("Usage : %s <filename1> <filename2>\n", argv[0]);
		return 0;
	}

	FILE *fd1, *fd2;
	char buf1[9];  
	char buf2[9];
	int i = 0;  //for문을 위한 3개 변수
	int j = 0;
	int k = 0;
	uint32_t n1 = 0;
	uint32_t n2 = 0;

	fd1 = fopen(argv[1], "r");
	if(fd1 == NULL){
		printf("first txt open error\n");
		return 1;
	}
	
	if(fread(buf1, sizeof(char), sizeof(buf1), fd1) != NULL){
		if(buf1[0] != 120){       //파일의 첫번째 인자가 x 인지 예외처리
			printf("첫번째 파일이 16진수 파일이 아닙니다.\n");
			exit(0);
		}
		if((sizeof(buf1)) != 9){    //size 를 이용한 예외처리
                        printf("첫번째 파일이 32비트 값이 입력되지 않았습니다.\n");
                        exit(0);
                }
		printf("첫번째 파일의 16진수 값 : ");
		for(i=0; i<4; i++){
			printf("x");
			for(j=0; j<2; j++){
				printf("%X", ascii_to_hex(buf1[k+1]));
				k++;
			}
		}
	}
        //16진수로 변환
	n1 = (ascii_to_hex(buf1[1])<<28)+(ascii_to_hex(buf1[2])<<24)+(ascii_to_hex(buf1[3])<<20)+(ascii_to_hex(buf1[4])<<16)+(ascii_to_hex(buf1[5])<<12)+(ascii_to_hex(buf1[6])<<8)+(ascii_to_hex(buf1[7])<<4)+(ascii_to_hex(buf1[8]));

	k=0;  //아래에서 써주기 위한 초기화

	printf("\n");

	fd2 = fopen(argv[2], "r");
	if(fd2 == NULL){
                printf("second txt open error\n");
                return 1;
        }

        if(fread(buf2, sizeof(char), sizeof(buf2), fd2) != NULL){
		if(buf2[0] != 120){
                        printf("두번째 파일이 16진수 파일이 아닙니다.\n");
			exit(0);
                }
		printf("%d",sizeof(buf2));
		if((sizeof(buf2)) != 9){
                        printf("두번째 파일이 32비트 값이 입력되지 않았습니다.\n");
                        exit(0);
                }
		printf("두번째 파일의 16진수 값 : ");
		for(i=0; i<4; i++){
                        printf("x");
                        for(j=0; j<2; j++){
                                printf("%X", ascii_to_hex(buf2[k+1]));
				k++;
                        }
		}
	}
	//16진수로 변환
	n2 = (ascii_to_hex(buf2[1])<<28)+(ascii_to_hex(buf2[2])<<24)+(ascii_to_hex(buf2[3])<<20)+(ascii_to_hex(buf2[4])<<16)+(ascii_to_hex(buf2[5])<<12)+(ascii_to_hex(buf2[6])<<8)+(ascii_to_hex(buf2[7])<<4)+(ascii_to_hex(buf2[8]));

	printf("\n 두파일 16진수 값의 합: 0x%X \n", n1+n2); 

	fclose(fd2);
	fclose(fd1);
}

