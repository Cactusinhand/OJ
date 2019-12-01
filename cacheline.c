#include <stdio.h>

struct CacheLine {
	int timer;
	int count;
	int block;
};

void CacheLineClear(struct CacheLine* line) {
	for(int i = 0; i < 8; i++) {
		line[i].timer = -1;
		line[i].count = -1;
		line[i].block = -1;
	}
}

void CacheLineTargetSet(struct CacheLine* line, int target, int block) {
	// set the targeted line
	line[target].timer = 0;
	line[target].count = line[target].count + 1;
	line[target].block = block;
	// un-targetd
	for(int i = 0; i < 8; i++) {
		if(i != target) {
			line[i].timer = line[i].timer + 1;
		}
	}
}

void CacheLineUnTargetSet(struct CacheLine* line, int oldest, int block) {
	// this target is the oldest
	line[oldest].timer = 0;
	line[oldest].count = 0;
	line[oldest].block = block;
	// for the rest of others
	for(int i = 0; i < 8; i++) {
		if(i != oldest) {
			line[i].timer = line[i].timer + 1;

		}
	}
}
int CacheLineQuery(struct CacheLine* line, int block) {
	int flag = 0;
	for(int i = 0; i < 8; i++) {
		if(block == line[i].block)
			return i;
		flag++;
	}	
	if(flag == 8)
		return -1;

	return 0;
}

int FindTheOldest(struct CacheLine* line) {
	int index = 0;
	int oldest = line[0].timer;
	for(int i = 0; i < 8; i++) {
		if(line[i].timer > oldest) {
			oldest = line[i].timer;
			index = i;
		}
	}
	return index;
}

int DataCollect(struct CacheLine* line) {
	int max = line[0].count;
	for(int i = 0; i < 8; i++) {
		if( line[i].count > max) {
			max = line[i].count;

		}
	}
	return max;
}

void printResult(int array[], int len) {
	for(int i = 0; i < len; i++) {
		printf("%d\n",array[i]);
	}
}

int main() {

	struct CacheLine line[8];
	CacheLineClear(line);
	int array[1024];

	int num, addr, block, new;
	int count = 0;

	while(scanf("%d", &num) != EOF) {
		if(num == 0) {  // clear
			CacheLineClear(line);
			continue;
		}
		if(num <= -1) { // print and exit
			printResult(array,count);
			return 0;
		} 
		while(num) {
			scanf("%d", &addr);
			if(addr > 65535 || addr < 0) {
				printf("error input\n");
				break;
			}
			block = addr/64;
			int target = CacheLineQuery(line, block);
			if(target >= 0) {  // target
				CacheLineTargetSet(line, target, block);
			}
			else {   // un-target
				new = FindTheOldest(line);
				CacheLineUnTargetSet(line, new, block);
			}
			num--;
		}
		array[count] = DataCollect(line);
		count++;
	}
	return 0;
}
