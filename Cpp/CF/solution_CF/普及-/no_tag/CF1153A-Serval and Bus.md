# Serval and Bus

## 题目描述

It is raining heavily. But this is the first day for Serval, who just became 3 years old, to go to the kindergarten. Unfortunately, he lives far from kindergarten, and his father is too busy to drive him there. The only choice for this poor little boy is to wait for a bus on this rainy day. Under such circumstances, the poor boy will use the first bus he sees no matter where it goes. If several buses come at the same time, he will choose one randomly.

Serval will go to the bus station at time $ t $ , and there are $ n $ bus routes which stop at this station. For the $ i $ -th bus route, the first bus arrives at time $ s_i $ minutes, and each bus of this route comes $ d_i $ minutes later than the previous one.

As Serval's best friend, you wonder which bus route will he get on. If several buses arrive at the same time, you can print any of them.

## 说明/提示

In the first example, the first bus of the first route arrives at time $ 6 $ , and the first bus of the second route arrives at time $ 9 $ , so the first route is the answer.

In the second example, a bus of the third route arrives at time $ 5 $ , so it is the answer.

In the third example, buses of the first route come at times $ 2 $ , $ 4 $ , $ 6 $ , $ 8 $ , and so fourth, buses of the second route come at times $ 2 $ , $ 5 $ , $ 8 $ , and so fourth and buses of the third route come at times $ 2 $ , $ 6 $ , $ 10 $ , and so on, so $ 1 $ and $ 2 $ are both acceptable answers while $ 3 $ is not.

## 样例 #1

### 输入

```
2 2
6 4
9 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
5 5
3 3
2 5
5 6
4 9
6 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
3 7
2 2
2 3
2 4
```

### 输出

```
1
```

# 题解

## 作者：hsfzLZH1 (赞：4)

## 题目大意

有 $n$ 列公交车，第 $i$ 列公交车有一个始发时间 $s_i$ 和发车间隔 $d_i$ ，即该公交车会在时刻 $s_i+k\times d_i(k\in \mathbb{N})$ 到达 Serval 所在的车站。

Serval 会在时刻 $t$ 到达车站，并会选择最早到达的那辆公交车，请你输出该公交车的编号。如果有多辆公交车同时到达，输出其中任意一个。

$1\le n\le 100,1\le t,s_i,d_i\le 10^5$

## 解题思路

这题考察了数组的简单应用。

观察到公交车的数量比较少，我们考虑计算出一辆公交车会在哪些时刻到达车站，并用数组存起来，时间复杂度 $O(nt)$ 。

由于可怜的 Serval 等到公交车的最晚时间为 $2\times 10^5$ ，我们的数组同样也要计算到 $2\times 10^5$ 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=200010;
int n,t,s,d,tf[maxn]; 
int main()
{
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&s,&d);
        for(int j=s;j<=200000;j+=d)tf[j]=i;
    }
    for(int i=t;;i++)if(tf[i]){printf("%d\n",tf[i]);return 0;}
    return 0;
}
```

---

## 作者：hgoicjl (赞：1)

### 题意

NaCly_Fish 要去机房，但他只能乘公交去。

公交站有$n$个线路，第$i$个线路在$s_i$时会来第一辆，然后每隔$d_i$秒来一辆。

NaCly_Fish 在第$t$秒会到公交站，请告诉他他最先能到哪辆公交车上。

如果有多种可能，输出任意一种。

---

### 算法
~~div2A要什么算法~~

模拟/思维？

---

模拟不过多赘述，可移步他人题解

以下算法为$O(1)$

我们考虑NaCly_Fish上车的时间$r$与$s_i$、$d_i$、$t$的关系

显然当$s_i>=t$时

NaCly_Fish只能坐上首班车，此时坐上车的时间为$r=s_i$

对于$s_i<t$

我们可以考虑NaCly_Fish最早能坐上第$k$班车

满足$s_i+k*d_i>=t$

通过 ~~初中数学~~ 移项，同除我们可以得到

$k=\lceil\frac{t-s_i}{d_i}\rceil$

即

$r=\lceil\frac{t-s_i}{d_i}\rceil d_i+s_i$

---
### Code
```
#include<bits/stdc++.h>
using namespace std;
int s(int a,int b,int c)//求文中t的函数，这里a,b,c对应了t,si,bi
{
	if(b>=a)
		return b;
	else if((a-b)%c==0)
		return a;
	else 
		return b+((a-b)/c+1)*c;
}
int main()
{
	int n,t,a1,a2,mi=1000000,x;
	cin>>n>>t;
	for(int i=1;i<=n;i++)
	{
		cin>>a1>>a2;
		if(mi>=s(t,a1,a2))//求最早上车的情况
		{
			mi=s(t,a1,a2);
			x=i;
		}
	}
	cout<<x;
	return 0;
} 
```

---

## 作者：1saunoya (赞：1)

看大佬的代码都好复杂（不愧是大佬$orz$

蒟蒻提供一种思路

因为求的是最近的车对吧$qwq$

所以我们可以用一个$while$循环所以没必要去用什么 $for...$

至于这是$div2$的第一题还是比较水的


```cpp
#include <bits/stdc++.h>
#define rep(i,j,n) for(register int i=j;i<=n;i++)
#define Rep(i,j,n) for(register int i=j;i>=n;i--)
#define low(x) x&(-x)
using namespace std ;
typedef long long LL ;
const int inf = INT_MAX >> 1 ;
inline LL In() { LL res(0) , f(1) ; register char c ;
#define gc c = getchar()
    while(isspace(gc)) ; c == '-' ? f = - 1 , gc : 0 ;
    while(res = (res << 1) + (res << 3) + (c & 15) , isdigit(gc)) ;
    return res * f ;
#undef gc
}

int n , t ;
const int N = 100 + 5 ;
struct node {
	int s , d ;
}a[N] ;
inline void Ot() {
	n = In() , t = In() ;
	rep(i,1,n) a[i].s = In() , a[i].d = In() ;
	int tmp = inf ;
	int ans = 0 ;
	rep(i,1,n) {
		int s = a[i].s ;
		while(s < t) s += a[i].d ;
		if(tmp > (s-t)) tmp = (s-t) , ans = i ;
	}
	cout << ans << endl ;
}
signed main() {
//  freopen("test.in","r",stdin) ;
    return Ot() , 0 ;
}
```

---

## 作者：世末OIer (赞：0)

~~先吐槽一句:这是我见过的代码量最大的正常的div2A~~

---

题目大意：

给你两个数n和k

然后还有n行

每行2个数$a_i$和$b_i$

对于每一个i,$c_i$=以$a_i$为首项，$b_i$为公差的等差数列中第一个大于等于n的数。

求$c_i$中的最小值。

---

题解:

暴力。

```cpp
#include<bits/stdc++.h>
#pragma GCC diagnostic error "-std=c++11"
using namespace std;
int n,m;
int a[111],b[111];
int main(){
	int i,j;
	cin>>n>>m;                    //读入
	for(i=1;i<=n;++i) cin>>a[i]>>b[i];
	int mn=123456789,wz=0;
	for(i=1;i<=n;++i){               //枚举
		if(a[i]>=m){               //如果大于首项就为首相
			if(a[i]<=mn){
				mn=a[i];
				wz=i;
			}
		}else{
			int t=m-a[i];
			t=(t+b[i]-1)/b[i];
			t=t*b[i];
			t+=a[i];               //```计算出c[i]
				mn=t;
				wz=i;
			}
		}
	}
	cout<<wz<<endl;                //输出答案
	return 0;
}
```

---

