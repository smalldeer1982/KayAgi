#include <cstdio>
#include <algorithm>
using namespace std;

bool prime[100007];
int l;

void ai() {
	for(int i = 2; i <= 100000; ++i)	prime[i] = 1;
	for(int i = 2; i <= 100000; ++i)
		if(prime[i])
			for(int j = i * 2; j <= 100000; j += i)
				prime[j] = 0;	
}

int main() {
	scanf("%d", &l);
	int p = l, sum = 0;
	ai();
	for(int i = 1; i <= p; ++i) {
		if(prime[i]) {
			printf("%d\n", i);
			p -= i;
			sum++;
		}
		if(p <= 0)	break;
	} 
	printf("%d", sum);
	return 0;
}