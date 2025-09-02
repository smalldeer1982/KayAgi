# Connected Component on a Chessboard

## 题目描述

You are given two integers $ b $ and $ w $ . You have a chessboard of size $ 10^9 \times 10^9 $ with the top left cell at $ (1; 1) $ , the cell $ (1; 1) $ is painted white.

Your task is to find a connected component on this chessboard that contains exactly $ b $ black cells and exactly $ w $ white cells. Two cells are called connected if they share a side (i.e. for the cell $ (x, y) $ there are at most four connected cells: $ (x - 1, y), (x + 1, y), (x, y - 1), (x, y + 1) $ ). A set of cells is called a connected component if for every pair of cells $ C_1 $ and $ C_2 $ from this set, there exists a sequence of cells $ c_1 $ , $ c_2 $ , ..., $ c_k $ such that $ c_1 = C_1 $ , $ c_k = C_2 $ , all $ c_i $ from $ 1 $ to $ k $ are belong to this set of cells and for every $ i \in [1, k - 1] $ , cells $ c_i $ and $ c_{i + 1} $ are connected.

Obviously, it can be impossible to find such component. In this case print "NO". Otherwise, print "YES" and any suitable connected component.

You have to answer $ q $ independent queries.

## 样例 #1

### 输入

```
3
1 1
1 4
2 5
```

### 输出

```
YES
2 2
1 2
YES
2 3
1 3
3 3
2 2
2 4
YES
2 3
2 4
2 5
1 3
1 5
3 3
3 5
```

# 题解

## 作者：Bring (赞：3)

[更好的阅读体验请点这里](https://www.cnblogs.com/BrianPeng/p/12245908.html)

感觉这题还可以

**因为总空间比输入数量 _不知高到哪里去了_ ，所以完全不需要考虑放不下的问题**

从**贪心**的角度考虑，如果要使相差数量巨大的$b$和$w$能够成功放下来，应该使这些方块尽量分散（似乎有点抽象）

### 来一发图解

作者因为太懒于是决定直接以B表示黑色，W表示白色

假设有一组方块拼成了一个正方形，~~如图~~

```
BWB
WBW
BWB
```
那么在不改变白块数量的情况下，最多还能加$4$个黑块，分别连在四个白块旁边

但是如果拉成直线，~~如图~~
```
BWBWBWBWB
```
发现可以在两边总共加$8$个黑块了，因为每个白块都可以再接$2$个黑块

所以**拉成直线**是最优方法（~~我有一个绝妙的证明但是这里写不下~~）

### 现在回到题目

如果$b=w$，那么非常简单，直接画条直线

现在考虑$b\not=w$

不失一般性，直接假设$b>w$，反正如果$b<w$的话整体右移一格即可

**先画直线**

直线会包含所有白块

为了尽量消耗黑块，让直线的两个端点都是黑块

比如说如果$b>w=3$，那么直线应该长这个亚子

```
BWBWBWB
```
这样就先消耗掉$w+1$个黑块

对于剩下的$b-w-1$个黑块，就让它们分置在两边的总共$2w$个空间里面

所以如果$b-w-1\leqslant2w$那么就是可行的，否则不能

对于后面的具体处理方法就请大家自己思考吧，具体请见代码

Time complexity: $O(\sum b+\sum w)$

Memory complexity: $O(1)$

$288$ms / $8.00$KB / rank $2$，成绩还是不错的
```cpp
//This program is written by Brian Peng.
#pragma GCC optimize("Ofast","inline","no-stack-protector")
#include<bits/stdc++.h>
using namespace std;
#define Rd(a) (a=read())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int read(){
	register int x;register char c(getchar());register bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	if(c^'-')k=1,x=c&15;else k=x=0;
	while(isdigit(Gc(c)))x=(x<<1)+(x<<3)+(c&15);
	return k?x:-x;
}
void wr(register int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(register int i(a);i<(b);++i)
#define Frn1(i,a,b) for(register int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(register int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
int q,b,w,s;
signed main(){
	Rd(q);
	while(q--){
		Rd(b),Rd(w);
		if(b==w){
			puts("YES");
			Frn1(i,1,b<<1)Pc('1'),Ps,wr(i),Pe;
		}else{
			b<w?(swap(b,w),s=2):s=1;
			if((b-=w+1)>w<<1){puts("NO");continue;};
			puts("YES");
			Frn1(i,0,w<<1)Pc('2'),Ps,wr(s+i),Pe;
			if(b<=w)Frn0(i,0,b)Pc('1'),Ps,wr(s+(i<<1|1)),Pe;
			else{
				Frn0(i,0,w)Pc('1'),Ps,wr(s+(i<<1|1)),Pe;
				b-=w;
				Frn0(i,0,b)Pc('3'),Ps,wr(s+(i<<1|1)),Pe;
			}
		}
	}
	exit(0);
}
```

---

## 作者：FiraCode (赞：0)

## 思路：

首先有一个性质，就是我们选中一个颜色后，在选另一个颜色，最多能解锁 $3$ 个当前颜色，证明很简单，首先最多是四个，然后若是 $4$ 的的话那么说明那个颜色与当前块不连通，所以至多三个。

由于矩形很大，于是可以考虑横着构造，若不够则在两边再选即可。

复杂度 $O(Tn)$。

## Code：
```cpp
#include <bits/stdc++.h>

using namespace std;

int T;
int x, y;

int main() {
	scanf("%d", &T);

	while (T--) {
		scanf("%d%d", &x, &y);
		if (3 * x + 1 < y || 3 * y + 1 < x) puts("NO");
		else {
			puts("YES");
			if (x == y) {
				int X1 = 100000, Y1 = 100000;
				for (int i = 1; i <= y; ++i) {
					printf("%d %d\n", X1, Y1);
					printf("%d %d\n", X1, Y1 + 1);
					Y1 += 2;
				}
			} else if (x > y) {
				printf("%d %d\n", 100000, 100001);
				int X1 = 100000, Y1 = 100002;
				int tmp = max(0, x - y - 1);
				for (int i = 1; i <= y; ++i) {
					printf("%d %d\n", X1, Y1);
					printf("%d %d\n", X1, Y1 + 1);
					if (tmp) {
						printf("%d %d\n", X1 + 1, Y1);
						--tmp;
					}
					if (tmp) {
						printf("%d %d\n", X1 - 1, Y1);
						--tmp;
					}
					Y1 += 2;
				}
			} else {
				printf("%d %d\n", 100000, 100000);
				int X1 = 100000, Y1 = 100001;
				int tmp = max(0, y - x - 1);
				for (int i = 1; i <= x; ++i) {
					printf("%d %d\n", X1, Y1);
					printf("%d %d\n", X1, Y1 + 1);
					if (tmp) {
						printf("%d %d\n", X1 - 1, Y1);
						--tmp;
					}
					if (tmp) {
						printf("%d %d\n", X1 + 1, Y1);
						--tmp;
					}
					Y1 += 2;
				}
			}
		}
	}
	return 0;
}
```

---

