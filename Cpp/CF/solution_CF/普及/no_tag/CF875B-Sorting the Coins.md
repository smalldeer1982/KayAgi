# Sorting the Coins

## 题目描述

Recently, Dima met with Sasha in a philatelic store, and since then they are collecting coins together. Their favorite occupation is to sort collections of coins. Sasha likes having things in order, that is why he wants his coins to be arranged in a row in such a way that firstly come coins out of circulation, and then come coins still in circulation.

For arranging coins Dima uses the following algorithm. One step of his algorithm looks like the following:

1. He looks through all the coins from left to right;
2. If he sees that the $ i $ -th coin is still in circulation, and $ (i+1) $ -th coin is already out of circulation, he exchanges these two coins and continues watching coins from $ (i+1) $ -th.

Dima repeats the procedure above until it happens that no two coins were exchanged during this procedure. Dima calls hardness of ordering the number of steps required for him according to the algorithm above to sort the sequence, e.g. the number of times he looks through the coins from the very beginning. For example, for the ordered sequence hardness of ordering equals one.

Today Sasha invited Dima and proposed him a game. First he puts $ n $ coins in a row, all of them are out of circulation. Then Sasha chooses one of the coins out of circulation and replaces it with a coin in circulation for $ n $ times. During this process Sasha constantly asks Dima what is the hardness of ordering of the sequence.

The task is more complicated because Dima should not touch the coins and he should determine hardness of ordering in his mind. Help Dima with this task.

## 说明/提示

Let's denote as O coin out of circulation, and as X — coin is circulation.

At the first sample, initially in row there are coins that are not in circulation, so Dima will look through them from left to right and won't make any exchanges.

After replacement of the first coin with a coin in circulation, Dima will exchange this coin with next three times and after that he will finally look through the coins and finish the process.

XOOO $ → $ OOOX

After replacement of the third coin, Dima's actions look this way:

XOXO $ → $ OXOX $ → $ OOXX

After replacement of the fourth coin, Dima's actions look this way:

XOXX $ → $ OXXX

Finally, after replacement of the second coin, row becomes consisting of coins that are in circulation and Dima will look through coins from left to right without any exchanges.

## 样例 #1

### 输入

```
4
1 3 4 2
```

### 输出

```
1 2 3 2 1
```

## 样例 #2

### 输入

```
8
6 8 3 4 7 2 1 5
```

### 输出

```
1 2 2 3 4 3 4 5 1
```

# 题解

## 作者：Withershine (赞：3)

算是比较简单的题目了，自己多手出几个样例就可以发现规律了。

**强烈建议多读几遍题目！！！！**

## 思路
设 0 表示硬币朝上，1 表示硬币朝下，则第 $0$ 次与第 $n$ 操作一定输出 $1$。因为没有可以操作的对象，前者是由于全部硬币朝上，后者是由于全部硬币朝下，即使没有操作也要遍历一遍。**注意这里输出有 $n + 1$ 个数**。

以样例 $2$ 为例子，最开始的序列是这样的：

00000000

第一次修改第 $6$ 枚硬币，序列变为：

00000100

此时按照题目中的操作，第一次修改最后序列变为：

00000001

可以想到一共遍历了 $2$ 次序列。

第二次操作修改第 $8$ 枚硬币：

00000101

操作后：

00000011

明显这里只遍历了一次，但输出却是 $2$，因为修改完后再遍历了一遍，所以输出是 $1 + 1 = 2$。

第三次操作修改第三枚硬币：

00100101

操作：
 
00000111
 
输出 $3$。
 
 第四次修改第四枚硬币：
 
 00110101
 
 这里给出详细操作：
 
 00110101
 
 $→$  00101011
  
 $→$  00010111
  
 $→$  00001111
  
  输出为 $3 + 1 = 4$。
  
通过第三，四次操作可以发现，对于没有被硬币阻挡的硬币，第一次遍历就可以一换到底。而部分硬币由于后面的硬币的阻挡，并没有一换到底，最终的操作次数也因为这些硬币而增加。

因此可以的出结论：最终操作数就是当前处于反面状态的总硬币数 $i$，减去处于末尾的**连续的**反面状态的硬币数 $j$，最后要再检查一遍，故输出为 $i-j+1$。

## 代码
内涵部分注释，可以更好地理解题解。
```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<climits>
#include<queue>
#include<map>
#include<set>
#include<sstream>
#include<cassert>
#define ll long long
#define inf 0x3f3f3f3f
#define fr(i , a , b) for(ll i = a ; i <= b ; ++i)
#define fo(i , a , b) for(ll i = a ; i >= b ; --i)
#pragma comment(linker , "/stack : 200000000")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
inline char gchar()
{
    static char buf[1000000] , *p1 = buf , *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf , 1 , 1000000 , stdin) , p1 == p2) ? EOF : *p1++;
}
inline ll read()
{
    ll x = 0 , f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
	  {
        if(ch == '-')
        {
        	f = -1;
		}
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
	  {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
ll n , ex , coin[300005];
ll ans;
ll r;
signed main()
{
    r = n = read();
    printf("1 ");//单独处理第0次
    n--;
    while(n >= 1)
    {
        ans++;
        ex = read();
        coin[ex] = 1;
        //对r进行优化，不需要每次都从最后一枚硬币开始
        while(coin[r--] != 0)
        {
            ans--;
        }
        r++;//在遍历时r多减了1，加回来
        printf("%lld " , ans + 1);
        n--;
    }
    printf("1");//单独处理第n次
    system("pause");
    return 0;
}
/*
0朝上
1朝下
*/
```

---

## 作者：__AFO__ (赞：1)

## 题解
[题目传送门](https://www.luogu.com.cn/problem/CF875B)

这道题其实真的就是一个小模拟，如果你可以写一个暴力代码出来，多自己出几个样例（有能力的也可以对拍），不难发现这道题的规律。

其实测试一下发现，一个反面朝上的硬币每遍历一次序列，他的位置就会移到下一个反面朝上的前面。

经过多次测验我们得出了一个结论，操作次数大概率是有多少个反面朝上的硬币数量加一，而为什么是大概率，因为如果有一个反面朝上的硬币在没排序时就已经在边缘了，这个时候，我们就要把他减掉，这样就得出了总操作次数，理解之后，代码也很好写了。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[300010],x,minn=0x3f3f3f,maxx,c;
int main(){
	scanf("%lld",&n);	
	maxx=n;
	for(long long i=1;i<=n;i++){
	   if(i==1) printf("1 ");//第一个永远是一所以先输出 
	   if(i==n){
	   	printf("1");//最后一个也永远是一所以直接特判即可 
	   	return 0;
	   }
	   scanf("%lld",&x);  
	   a[x]=1;
	   while(a[maxx]==1) maxx--,c++;//判断有多少个棋子到了边界 
	   printf("%lld ",i-c+1);//i是棋子总数，c是已经到了边界的棋子 
	}
	
	
	return 0;
}
```

~~交了很久才过，一直给我 UKE 服了~~。

### END

---

## 作者：_LighT_ (赞：1)

题目传送门：[CF875B](https://www.luogu.com.cn/problem/CF875B)

## 思路

先来简单地模拟一下题意，用 `X` 代表反面朝上：

​	XOXXOOXX

$\to$OXXOOXXX

$\to$OXOOXXXX

$\to$OOOXXXXX

不难发现，处于末尾的 `X` 由于已经不会被交换，所以操作前可以直接无视之：

​	XOXXOO(XX)

$\to$OXXOO(XXX)

$\to$OXOO(XXXX)

$\to$OOO(XXXXX)

由此，规律明了：操作次数 $=$ `X`总个数 $-$ 末尾 `X` 个数 $+\ 1$.

感性地去理解一下，第 $1$ 个 `X` 跟着第 $2$ 个的足迹走，第 $2$ 个跟着第 $3$ 个走······最后的被跟随者是末尾 `X` 的最左一个。

由于不会重复修改已修改的硬币，那末尾 `X` 个数必定单调不减。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ri register int
typedef long long ll;
const int MAXN=3E5+5;
inline int read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x;
}
int n;
int a[MAXN],num=0;//a[]用于记录当前状态，num用于记录末尾X个数
inline void solve(int xxx){
	a[n-read()+1]=1;
	for(ri i=num+1;i<=n+1;++i)
		if(a[i]==0){
			num=i-1;
			break;
		}//这里我是反存正搜
	printf(" %d",xxx-num+1);
    //+1是指最后X都靠右后还要再扫一遍
}
int main(){
	n=read();
	printf("1");
	for(ri i=1;i<=n;++i)
		solve(i);
	return 0;
}
```

时间复杂度：$O(n)$（~~这一点是 @伞兵二号zja 说的，假了请找他~~）.

---

## 作者：Crazyouth (赞：0)

## 分析

又是性质题。注意到每次操作都会把恰好一枚反面朝上的硬币归位，因此第 $i$ 次答案至多是 $i+1$，但是有些硬币开始时就归位了，要减去这些硬币的数量，用一个只减不增的指针来维护当前初始时已归位的硬币中最小下标在哪里，同时根据这个指针求出有多少在初始时就归位的硬币，答案就是 $i+1$ 减去归位硬币数。

## AC Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int ed=0,ned=0,a[300010];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	cout<<1<<' ';
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		if(i==n)
		{
			cout<<1;
			return 0;
		}
		a[x]=1;
		for(int j=n-ned;a[j];j--) ned++,ed++;
		cout<<i-ed+1<<' ';
	}
}

---

## 作者：Lizj (赞：0)

## 题面简述

可能大部分人看不懂题只是因为题面翻译比较模糊，在这里给出题面简述：

给出 $n$ 枚硬币，硬币分为两种类型，流通中和停止流通的。要将这 $n$ 枚硬币排序成流通中的在前，停止流通的在后的形式，排序按以下顺序进行：

1. 从第 $1$ 枚硬币向第 $n$ 枚顺次遍历。

1. 若第 $i$ 枚硬币反面朝上且第 $i+1$ 枚正面朝上，交换这两枚硬币的位置后，从第 $i+1$ 枚硬币继续排序。

开始时，所有硬币都正面朝上。给出 $n$ 次修改，第 $i$ 次修改是在第 $i−1$ 次修改的初状态（即操作前）的基础上将第 $p_i(\{p_1,p_2,\dots,p_n\}=\{1,2,\dots,n\})$ 枚硬币从正面朝上翻转为反面朝上，每次修改（包括第 $0$ 次）后请求出当前序列的排序难度，可以理解为当前序列到有序的过程中不同的状态数目。

## 分析

对于“状态数目”，以下进行具体说明并分析解题思路，以样例一为例，用 $\text{O}$ 代替流通中的硬币，用 $\text{X}$ 代替停止流通的硬币：

在第一次修改前，序列有序，距离有序序列只有一种状态:

$\text{OOOO}$

该序列已有序。

第一次修改过程：

$\text{XOOO}\to \text{OOOX}$

第一次修改后，硬币交换了 $3$ 次，可答案却是 $2$，因为交换三次硬币是一个连贯的排序过程，动作后才需采取另一次操作，所以答案为 $2$。

第二次修改：

$\text{XOXO}\to \text{OXOX}\to \text{OOXX}$

同理，在第二步后，原本的两枚硬币一同移动变为了只移动一枚硬币，另算作一种状态，答案为三。

第三次修改：

$\text{XOXX}\to \text{OXXX}$

同上。至此，可以看出，每次操作都针对于无硬币遮挡的硬币，且排序难度的增大取决于被遮挡的硬币。

得出答案为：

反面状态的总硬币数 $-$ 末尾的连续的反面状态的硬币数 $+1$，由此，本题得出解。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1,ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48),ch=getchar();}  //位运算优化快读
	return x*f;
}
int n,a[300010],ans;
void solve(int i){
    int x=read();
    a[n-x+1]=1;
    for(int i=ans+1;i<=n+1;i++){    //从上次结束的地方开始搜，节省时间
        if(a[i]==0){
            ans=i-1;    //储存答案
            break;
        }
    }
    printf("%d ",i-ans+1);
}
int main(){
    n=read();
    printf("1 ");   //提前处理第一次
    for(int i=1;i<=n;i++){
        solve(i);
    }
    return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
比较有意思的一道题目。这个其实和之前的序列翻转和取反的那类题有异曲同工之妙，比较显然需要找规律。
## 分析。
可以发现扫描一次后进行交换，第一次操作的被改变成 ```X``` 的位置一定会被移到最后面，即第 $n$ 位上，同理，每一次的扫描都会把一个 ```X``` 交换到最后面（注意这个最后面不一定是第 $n$ 位）。所以有一个很巧妙的思路。我们事实上只需要知道下标最大的 ```O``` 前面有几个 ```X``` 即可。

这个算法的原理是：首先在第 $0$ 次操作时，必然最大的下标在 $n$ 处，此后被替换，那么显然下标要减少一个，此后再次进行交换，因为每一次的操作都是在上一个操作的基础上进行操作的，所以在原位置上又可以被替换，此时如果现在所处的最大坐标的位置被占领了，那么就继续将下标递减。同时因为后面的已经确定位置的 ```X``` 没有动，所以需要减去它们已经占领的个数。

那么答案就是总的 ```X``` 的个数减去已经占领的 ```X``` 个数再加上一个，这个加上一个的原因是即便不再交换，也必定要扫一遍。如果还是不甚理解，那么代码如下，仅供参考：
```
#include<iostream>
#include<cstdio>
using namespace std;
int n,p;
int sum,n2,a[300005];
template <typename T> void read(T &x){
	x = 0;
	bool f = 0;
	char c = getchar();
	while (c < '0' || c > '9') f |= c == '-', c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	if (f) x = -x;
}
template <typename T> void write(T x){
	if (x < 0) putchar('-'), x = -x;
	if (x < 10) putchar(x + '0');
	else write(x / 10), putchar(x % 10 + '0');
}
int main(){
    read(n);
    n2=n;
    cout<<"1 ";//第0次没有改变，但是需要扫描一遍。
    for(int i=1;i<=n;i++){
        read(p);
        a[p]=1;
        sum++;
        while(a[n2]){
        	sum--;
            n2--;
        }
        write(sum+1);
        printf(" ");
    }
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

