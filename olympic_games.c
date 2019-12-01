#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct INFO {
	char n[50];  // name;
	int g;    	 // gold;
	int s;    	 // silver;
	int b;    	 // bronze;
	int t;    	 // total
};

bool infoCmp(struct INFO lhs, struct INFO rhs) {
	
	if(lhs.g > rhs.g) { return true;}
	else if(lhs.g < rhs.g) {return false;}
	
	else if(lhs.s > rhs.s) {return true;}
	else if(lhs.s < rhs.s) {return false;}
	
	else if(lhs.b > rhs.b) {return true;}
	else if(lhs.b < rhs.b) {return false;}
	
	else if(strcmp(lhs.n, rhs.n) > 0) { return false;}		// 分数从大到小，字母从小到大
	else return true;
	
}

void bubbleSort(struct INFO info[], int len) {				// 从大到小
	for(int i = 0; i < len-1; i++) {
		for(int j= 0; j < len - i - 1; j++) {
			if(!infoCmp(info[j],info[j+1])) {			
				struct INFO tmp = {'\0', 0, 0, 0};
				tmp = info[j];
				info[j] = info[j+1];
				info[j+1] = tmp;
			}
		}
	} 
}

void printResult(struct INFO info[], int len) {
	printf("..........index..........\n");
	bubbleSort(info, len);
	for(int i = 0; i < len; i++) { 
		printf("%s\n",info[i].n);
	}	
}

void infoClear(struct INFO info[], int len) {
	for(int i = 0; i < len; i++) { 
		info[i].g = 0;
		info[i].s = 0;
		info[i].b = 0;
		info[i].t = 0;
	}
}

int main() {
	
	struct INFO info[20];
	infoClear(info, 20);  //
	char name[50];
   	memset(name, '\0', sizeof(name));
	
	int num, gold, silver, bronze;
	scanf("%d",&num);
	if(num < 1 || num > 20) 
		return 0;
	for(int i = 0; i < num; i++) {
		scanf("%s%d%d%d", name, &gold, &silver, &bronze);
		if(strlen(name)> 48)
		 	return 0;
		if(gold < 0 || gold > 100)
			return 0;
		if(silver < 0 || silver > 100)
			return 0;
		if(bronze < 0 || bronze > 100)
			return 0;		
		strcpy(info[i].n, name); 	// 使用strcpy!!!!
		info[i].g = gold;
		info[i].s = silver;
		info[i].b = bronze;
		info[i].t = gold + silver + bronze;	
	}
	
	printResult(info, num);
	
	return 0;
}
