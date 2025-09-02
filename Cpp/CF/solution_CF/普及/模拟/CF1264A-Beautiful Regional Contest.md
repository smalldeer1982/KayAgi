# Beautiful Regional Contest

## 题目描述

### 题意简述

一场有 $n$ 名选手参加的比赛结束了。第 $i$ 位的参赛者解决了 $p_i$ 个问题。组委会已经将 $p_i$ 降序排序，也就是说，$p_1 \geq p_2 \geq ··· \geq p_n$。

您需要给选手颁发奖牌 —— $g$ 枚金牌、$s$ 枚银牌和$b$ 枚铜牌，但要满足如下条件：

- 三种奖牌必须至少颁发一枚。也就是说，$g>0,s>0,b>0$。
- 金牌的数量必须严格小于银牌和铜牌的数量，也就是说 $g<s,g<b$，但**并没有**要求 $s<b$。
- 获得金牌的选手解决的问题数量必须严格大于获得银牌的选手解决的问题数量。
- 获得银牌的选手解决的问题数量必须严格大于获得铜牌的选手解决的问题数量。
- 获得铜牌的选手解决的问题数量必须严格大于没有获奖的选手解决的问题数量。
- 奖牌总数 $g+s+b$ 不得超过选手数量的一半，也就是说应当满足 $g+s+b \leq \lfloor \frac n2\rfloor$。

在满足上述条件的情况下，最多能颁发多少枚奖牌呢？

## 样例 #1

### 输入

```
5
12
5 4 4 3 2 2 1 1 1 1 1 1
4
4 3 2 1
1
1000000
20
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
32
64 64 63 58 58 58 58 58 37 37 37 37 34 34 28 28 28 28 28 28 24 24 19 17 17 17 17 16 16 16 16 11
```

### 输出

```
1 2 3
0 0 0
0 0 0
2 5 3
2 6 6
```

# 题解

## 作者：览遍千秋 (赞：2)

这道题的意思是~~让你扮演CCF~~给选手发奖

显然，相同分数的人一定获得同样级别的奖项，所以把连续的一段分数相同的人缩为一个人，记录数量。

接着贪心地选取更多的“新人”，使得$\sum_{i=1}^{k}\le \frac{n}{2}$，记录这个 $k$ 。

因为要让金牌小于银牌和铜牌，所以直接只给最高分的那些人发金牌，然后找出最少的银牌数量，可以计算出铜牌的数量。

判断一下合不合法即可。

```cpp
//CF1264A Accepted
#include<bits/stdc++.h>
using namespace std;

const int maxn=400007;

int T;
int n,a[maxn];
int tot,sum,cnt;
int b[maxn],size[maxn];


void Init(void){
	scanf("%d",&T);
}

void clear(void){
	tot=0;sum=0;
	cnt=0;
}

void output(void){
	int gold=size[1],silver(0);
	for(int i=2;i<=tot;i++){
		silver+=size[i];if(silver>gold) break;
	}
	if(!gold||!silver||gold+silver==sum) puts("0 0 0");
	else if(gold>=silver||gold>=sum-gold-silver) puts("0 0 0");
	else printf("%d %d %d\n",gold,silver,sum-gold-silver);
}

void Work(void){
	while(T--){
		clear();scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			if(a[i]!=a[i-1]) b[++cnt]=a[i],size[cnt]=0;
			++size[cnt];
		}
		for(int i=1;i<=cnt;i++){
			if(sum+size[i]<=n/2) ++tot;
			else break;
			sum+=size[i];
		}
		if(tot<3) puts("0 0 0");
		if(tot>=3){
			if(size[1]>=sum-size[1]-size[2]&&size[1]>=size[2]) puts("0 0 0");
			else output();
		}
	}
}

signed main(){
	freopen("CF1264A.in","r",stdin);
	Init();
	Work();
	return 0;
}
```

---

