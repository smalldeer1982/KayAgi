# Woodcutters

## 题目描述

Little Susie listens to fairy tales before bed every day. Today's fairy tale was about wood cutters and the little girl immediately started imagining the choppers cutting wood. She imagined the situation that is described below.

There are $ n $ trees located along the road at points with coordinates $ x_{1},x_{2},...,x_{n} $ . Each tree has its height $ h_{i} $ . Woodcutters can cut down a tree and fell it to the left or to the right. After that it occupies one of the segments $ [x_{i}-h_{i},x_{i}] $ or $ [x_{i};x_{i}+h_{i}] $ . The tree that is not cut down occupies a single point with coordinate $ x_{i} $ . Woodcutters can fell a tree if the segment to be occupied by the fallen tree doesn't contain any occupied point. The woodcutters want to process as many trees as possible, so Susie wonders, what is the maximum number of trees to fell.

## 说明/提示

In the first sample you can fell the trees like that:

- fell the $ 1 $ -st tree to the left — now it occupies segment $ [-1;1] $
- fell the $ 2 $ -nd tree to the right — now it occupies segment $ [2;3] $
- leave the $ 3 $ -rd tree — it occupies point $ 5 $
- leave the $ 4 $ -th tree — it occupies point $ 10 $
- fell the $ 5 $ -th tree to the right — now it occupies segment $ [19;20] $

In the second sample you can also fell $ 4 $ -th tree to the right, after that it will occupy segment $ [10;19] $ .

## 样例 #1

### 输入

```
5
1 2
2 1
5 10
10 9
19 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
5
1 2
2 1
5 10
10 9
20 1
```

### 输出

```
4
```

# 题解

## 作者：yzx72424 (赞：24)

看到楼下dalao的dp，本蒟蒻瑟瑟发抖.....

我用的是贪心，对没错，直接贪心就好了

第一棵树向左，最后一棵树向右，不用管

中间的能往左就往左，否则能向右就向右，再否则就砍不了 。

从左向右扫，如果向右倒就把x+=h

```
#include<bits/stdc++.h>
using namespace std;
int xx[200000],h[200000];
int main() {
	int a,t=0;
	scanf("%d",&a);
	for(int i=1;i<=a;i++){
       scanf("%d%d",&xx[i],&h [i]);
	}
	for(int i=2;i<=a-1;i++){
		if(xx[i]-h[i]>xx[i-1])t++;
		else if(xx[i]+h[i]<xx[i+1]){
			t++;xx[i]+=h[i];
		}
	}
	 if(a==1)printf("1");
     else printf("%d",t+2);
}
```

---

## 作者：ddmd (赞：7)

## 这个题目明显就是贪心

贪心策略就是尽可能往同一个方向倒，无法向倒，则尽量往另一个倒。  

为什么这样是最优的呢？   

其实可以考虑：   

能往同一个方向倒就往同一个方向倒，比如都往左倒。如果这个能往左倒，但是我偏要让它向右到，那么就会影响到下一棵树，即影响结果。   
但是这个不能向左倒，就要进行讨论：   
1. 如果这个树向右倒后，下一棵树就仍然可以向左倒，那么就这棵树就向右倒，这个显然是优的
2. 如果这个树向右倒后，下一棵树就不能向左倒，那么这两棵树就只能选一棵   

综上，即尽可能往同一个方向倒，无法向倒，则尽量往另一个倒   

Code   


------------
```cpp

// Dong_Dong出品 必是精品
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
inline void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
inline void writesp(int x)
{
	write(x);
	putchar(' ');
}
inline void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int maxn=1e5+5;
int n,ans,h[maxn],x[maxn];
signed main()
{
	ios::sync_with_stdio(0);
	n=read();
    for(int i=1;i<=n;i++) 
	x[i]=read(),h[i]=read();
    ans=2;
    for(int i=2;i<n;i++){
        if(x[i]-x[i-1]>h[i]) ans++;
        else if(x[i+1]-x[i]>h[i]) ans++,x[i]+=h[i];
    } 
    if (n==1)putchar('1');
		else writeln(ans); 
	return 0;
}

```


---

## 作者：wenjing233 (赞：7)

## CF545C Woodcutters
贪心就是尽可能往左倒  
无法向左倒，则尽量往右倒  
第一个准则很好理解，但另一个则让人费解  
如果向右倒的话，则再右边的那颗树则也可能会向右倒，这样可能会有人会想这样会不会让答案不优  
那么我们假设这样之后，我们让一颗树既不能向左也不能向右，也就是造成了负面影响，因为一棵树无论倒不倒，都会让他所在的点无法被接触到，所以说这棵树停在原地等价于向左倒，也就是我们只是面对二择，要么左边，要么右边，对于答案而言是等价的。  
故此贪心策略是正确的  
Q·E·D
代码懒得去黏贴了，我记得没有代码也没关系的吧

---

## 作者：一只书虫仔 (赞：4)

#### Description

> 有 $n$ 棵树，第 $i$ 棵树在数轴 $x_i$ 的位置上，倒下会占 $h_i$ 个单位长度，两棵树倒下的树木长度不能重合，某一倒下的树木也不能覆盖另一个没有砍倒的树木，求最多可以砍倒多少棵树。

#### Solution

~~solve by tag~~

**做法一**

考虑 dp，设 $f_{i,0/1/2}$ 为第 $i$ 棵树不倒 / 往左边倒 / 往右边倒能最多砍倒多少棵树，转移：

- $f_{i,0}=\max\limits_{j \in [0,2]}\{f_{i-1,j}\}$；
- $f_{i,1}$ 能够从若干种状态转移过来：
	- $f_{i-1,0}$ 与 $f_{i-1,1}$，前提是第 $i$ 棵树挡不住第 $i-1$ 棵树；
    - $f_{i-1,2}$，前提是第 $i$ 棵树与第 $i-1$ 棵树不重叠；
- $f_{i,2}$ 能够从 $f_{i-1,0},f_{i-1,1},f_{i-1,2}$ 转移过来，前提是挡不住第 $i+1$ 棵树。

答案即为 $\max\limits_{j \in [0,2]}\{f_{n,j}\}$。

**做法二**

考虑贪心，能往一边倒就往一边倒。

我们假设都往左边倒，如果左边倒不行，就分别考虑：

- 往右边倒不会挡住下一棵树往左边倒，就直接跳过；
- 往右边倒会挡住下一棵树往左边倒，就选择长度大的（实际上并不需要再考虑，因为答案为最多能砍倒多少棵树，随便选择一棵答案是不变的）。

易得第 $1$ 棵与第 $n$ 棵不用管。

---

## 作者：When (赞：4)

#### 主要是对楼下大佬们贪心算法的补充说明

对于第一句话：

>  “能往左倒就往左倒。”

如同数学中“我们不妨设”一样，相信很好理解。这里只对第二句话稍作解释：

> “不能往左倒的尽量往右倒。”

这样为什么是对的呢？

我们可以分类讨论一下：

+ 假设当前已经处理到第$i$个，且它不能往左倒，$h_i$表示树高，$x_i$表示位置。

+ 若$x_{i + 1} - x_i > h_i$，也就是说i可以往右倒，那么它有两种选择：

  1. 往右倒。如果倒完以后$i+1$还能向左倒，那么显然最优；如果倒完之后$i+1$不能往左倒了，

     那么在处理$i+1$时会考虑它能否往右，但我们发现$[i-i + 1]$这段区间内的贡献已达到了最大值（因为就算让$i + 1$往左倒这段区间对答案贡献也为$1$），因此不会使答案变差。

  2. 不往右倒。假如$i + 1$既能往左倒又能往右倒，那么如果$i$不往右倒就会影响答案，所以不能选。

+ 若$x_{i + 1} - x_i \leq h_i$，也就是说不能往右倒，这时它根本没得选。

综上，我们证明了该贪心算法的正确性，希望这对你有所帮助。

#### 贴一波代码

```cpp
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 10;
int n,ans;
struct Tree{
    int h,x;
}t[maxn];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++ i) scanf("%d%d", &t[i].x, &t[i].h);
    ans = 2;
    for(int i = 2; i < n; ++ i){
        if(t[i].x - t[i - 1].x > t[i].h) ans ++;
        else if(t[i + 1].x - t[i].x > t[i].h) ans ++, t[i].x += t[i].h;
    } printf("%d\n", ans);
    return 0;
}
```



---

## 作者：LSG_waterlyf (赞：3)

## 一种有点暴力的dp
首先$f[i][0]$表示第i棵树不砍，$f[i][1]$表示第$i$棵树向左倒，$f[i][2]$表示第$i$棵树向右倒。对于每棵树$i$，考虑在合法情况下的转移，即题目的要求。不懂的可以看代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,f[100010][3];
struct tree
{
	int x,h;
}t[100010];
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	scanf("%d%d",&t[i].x,&t[i].h);
	f[1][0]=1;if(t[2].x-t[1].x>t[1].h) f[1][1]=1;
	for(int i=2;i<=n;i++)
	{
		f[i][0]=max(f[i-1][0],f[i-1][1]);
		if(t[i].x-t[i-1].x>t[i-1].h) f[i][0]=max(f[i][0],f[i-1][2]);
		if(t[i].x-t[i-1].x>t[i].h) f[i][1]=max(f[i-1][1]+1,f[i-1][0]+1);
		if(t[i].x-t[i-1].x>t[i].h+t[i-1].h) f[i][1]=max(f[i][1],f[i-1][2]+1);
		f[i][2]=max(f[i-1][0],f[i-1][1])+1;
		if(t[i].x-t[i-1].x>t[i-1].h) f[i][2]=max(f[i][2],f[i-1][2]+1);
	}
	cout<<max(max(f[n][0],f[n][1]),f[n][2]);
	return 0;
}
```


---

## 作者：XL4453 (赞：2)

题目分析：

考虑贪心。

结论是从左向右考虑每一棵树，对于当前树如果能向左倒那就尽量向左倒，否则若能向右倒那就向右倒。

------------
这样的正确性是可以保证的。

每一棵树所能提供的价值仅为一，那么即使倒了一颗更高的树到右边（相对右边的树倒向左边），所能够产生的价值也不会下降。

因为最坏情况也是那颗树没有办法倒，损失的一点价值则由之前占了他的位置的树填补。

------------

需要注意树是否可以倒下的判断条件，容易写错。

------------
代码：

```cpp
#include<cstdio>
using namespace std;
int p[100005],len[100005],n,ans,last;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&p[i],&len[i]);
	}
	p[0]=-2147483647;
	p[n+1]=2147483647;
	for(int i=1;i<=n;i++){
		if(last==0){
			if((long long)p[i]-(long long)p[i-1]>(long long)len[i])ans++,last=0;
			else if((long long)p[i+1]-(long long)p[i]>(long long)len[i])ans++,last=1;
			else last=0;
		}
		else{
			if((long long)p[i]-(long long)p[i-1]-(long long)len[i-1]>len[i])ans++,last=0;
			else if((long long)p[i+1]-(long long)p[i]>(long long)len[i])ans++,last=1;
			else last=0;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：D2T1 (赞：2)

### 思路：

简单贪心，不知道为什么评蓝。

思路很简单，让每棵树尽量往一个方向倒。

有两个注意点：

- 1. 不用 sort。

- 2. 如果一棵树倒了刚好砸到另一棵树的边，这不算。

### 代码：

```cpp
//CF545C
#include <cstdio>

const int maxn=100010;
int a[maxn],b[maxn];

int main(){
	int n,sum=2;
	scanf("%d",&n);
	if(n==1) return putchar('1')&0;
	for(int i=0; i<n; ++i)
		scanf("%d%d",&a[i],&b[i]);
	for(int i=1; i<n-1; ++i){
		if(a[i]-a[i-1]>b[i]) ++sum;
		else if(a[i+1]-a[i]>b[i]) ++sum,a[i]+=b[i];
	}
	printf("%d",sum);
	return 0;
}
```

### 推荐习题：

[P2887 [USACO07NOV]Sunscreen G](https://www.luogu.com.cn/problem/P2887)

[P2859 [USACO06FEB]Stall Reservations S](https://www.luogu.com.cn/problem/P2859)

---

## 作者：NSOI (赞：1)

本题纯贪心

[题目传送门](https://www.luogu.com.cn/problem/CF545C)

# 分析

这题先判断是否一棵树，如果是一棵树就输出一（WA了两遍！！！）。

```c
if(n==1){
	printf("1");
	return 0;
}
```
然后，最左边的树让它倒向左边，最右边的树让它倒向右边，这样可以保证这两棵树不干涉其他的树。所以输出时答案加二。
```c
printf("%d",ans+2);
```
最后，贪心的过程：尽量都往左边倒。

### 证明如下：

**反证法**：若一棵树往左倒之后比往右倒的树木少，那么他的最优解一定是往右倒。此时有两种情况：

(1)右边的树比左边的矮，那么他们都往左倒比向右倒更优，矛盾。

(2)右边的树比左边的树高，那么左边的树往左不比往右差，矛盾。

证毕。

按照往左倒优先的顺序做完贪心即可。

```c
for(int i=2;i<=n-1;i++){
	if(num[i]-h[i]>num[i-1])ans++;
	else if(num[i]+h[i]<num[i+1]){
		ans++;
		num[i]+=h[i];
	}
}
```

---

## 作者：linaonao (赞：1)

###### 注：本篇题解较细致讲解，新手向

从某贪心题单来到这，感觉这是一道$dp$ ，但还是忍住打了贪心。

讲一下贪心的思路：

每棵树都有两种情况，向左或向右，显然这是对称的，所以我们从一边过去考虑即可。这里我从左边开始考虑（显然这符合一般人的逻辑）。若从左边考虑，分两种情况：

- 向左倒可行，那么往左倒一定是最优的，不会干扰后续树的选择。

- 向左不可行，此时看看向右是否可行，若可行，又分两种

 	
    - 自己向右倒	
   - 自己右边那棵向左倒
 	- 这两种若不冲突，那是最好，若冲突，两者取一对后续选择还是没有干扰，所以随便选一个（这里为了方便选自己向右倒），之后再移到下一棵树进行判断。
 
注意点：

- 第一棵和最后一棵显然向两边倒

- 为了后续操作的的连贯性，向右倒时可以将树的坐标向右移，向左倒就不用管他。

代码：

~~~cpp
#include<bits/stdc++.h>
using namespace std;
int loc[100005],tree[100005];
int main(){
	int n;cin>>n;
	for(int i=1;i<=n;++i){	
		scanf("%d%d",&loc[i],&tree[i]);
	}
	int sum=2;
	for(int i=2;i<n;++i){
		if(loc[i]-tree[i]>loc[i-1]) ++sum;
		else if(loc[i]+tree[i]<loc[i+1]) ++sum,loc[i]+=tree[i];
	}
	int ans=n==1?1:sum;
	printf("%d",ans);
} 
~~~



---

## 作者：lukelin (赞：1)

贪心  
先排序  
然后能往左倒就往左倒，不能往左倒就看可不可以往右倒  
解释:  
	该树本身就占一格，如果不往左倒就是浪费  
   如果能往右倒，意味着对于后面的树来说，比下一颗树往左倒更优  
   解决  
  
  
放个代码：
```cpp
#include <cstdio>
#include <algorithm>
#define ll long long

using namespace std;

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

struct Tree{
    int pos, hei;
} trees[100005];

int cut[100005];

bool Comp(const Tree &a, const Tree &b){
    if (a.pos < b.pos)
        return true;
    else if (a.pos == b.pos){
        if (a.hei < b.hei)
            return true;
        else
            return false;
    }
    else
        return false;
}

int main(){
    int n = read();
    for (int i = 0; i < n; ++i){
        trees[i].pos = read(), trees[i].hei = read();
    }
    sort(trees, trees + n, Comp);
    int ans = 1, flg = 0;
    for (int i = 1; i < n; ++i){
        if (trees[i].pos - trees[i - 1].pos > trees[i].hei + (cut[i - 1] ? trees[i - 1].hei : 0)){
            ++ans;
        } else if (((i == n - 1) ? 2147483647 : trees[i + 1].pos) - trees[i].pos > trees[i].hei){
            cut[i] = 1;
            ++ans;
        }
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：这有一只匿 (赞：1)

简单DP题。记f[0][i]为第i棵树向左倒的最多能砍掉的树，记f[1][i]为第i棵树向右倒的最多能砍掉的树，那么可分3类讨论。

```cpp
f[1][i]=f[0][i]=max(f[1][i-1],f[0][i-1]);
//这个代表将上一棵树的最优状态转移到这一棵，所以这棵树不砍也能用f数组表示最优
if(x[i]-h[i]>x[i-1])
f[0][i]=max(f[0][i],f[0][i-1]+1);
//这棵树向左倒，上一棵树也向左倒
if(x[i]-h[i]>x[i-1]+h[i-1])
f[0][i]=max(f[1][i-1]+1,f[0][i]);
//这棵树向左倒，上一棵树向右倒
if(x[i]+h[i]<x[i+1])f[1][i]++;
//这棵树向右倒
```

最后输出MAX（f[1][n],f[0][n]）即可。（注意处理左边界和右边界）。


```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int MAX=1e5+5;
int f[2][MAX],x[MAX],h[MAX],n;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	scanf("%d%d",&x[i],&h[i]);
	x[n+1]=2147483647;x[0]=-2147483647;
	for(int i=1;i<=n;i++)
	{
		f[1][i]=f[0][i]=max(f[1][i-1],f[0][i-1]);
		if(x[i]-h[i]>x[i-1])
        f[0][i]=max(f[0][i],f[0][i-1]+1);
		if(x[i]-h[i]>x[i-1]+h[i-1])
        f[0][i]=max(f[1][i-1]+1,f[0][i]);
		if(x[i]+h[i]<x[i+1])f[1][i]++;
	}
	cout<<max(f[0][n],f[1][n]);
	return 0;
}
```

---

## 作者：BotDand (赞：0)

# $\text{Problems}$

给 $n$ 棵树在一维数轴上的坐标，以及它们的长度。

现在要你砍倒这些树，树可以向左倒也可以向右倒，砍倒的树不能重合，当然，也不能覆盖其他的树原来的位置。

求最大可以砍倒的树的数目。

# $\text{Answer}$

贪心。

先让最左边的树往左倒，最右边的树往右倒，然后考虑第 $i\,\,\,\,\,(i\in [2,n-1])$ 棵树。

如果第 $i$ 棵树能往右倒，则往右倒，否则就往左倒，如果都不行，就不砍到。

向右倒的话还要将坐标右移 $x$ 位，$x$ 为这棵树的高度。

最后特判一下 $n$ 为 $1$ 的情况即可。

# $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int s;
struct arr
{
    int x,h;
}a[100002];
inline int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
inline void write(int x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline void print(int x)
{
    write(x);
    putchar('\n');
}
bool cmp(arr x,arr y)
{
    return x.x<y.x;
}
int main()
{
    n=read();
    if(n==1) return puts("1"),0;
    for(int i=1;i<=n;++i) a[i].x=read(),a[i].h=read();
    sort(a+1,a+n+1,cmp);
    s=2;
    for(int i=2;i<n;++i)
        if(a[i].h<a[i].x-a[i-1].x) s++;
            else
                if(a[i].h<a[i+1].x-a[i].x)
                {
                    a[i].x+=a[i].h;
                    s++;
                }
    print(s);
    return 0;
}
```


---

## 作者：傅思维666 (赞：0)

## 题解：

一眼切的DP。

看到很多大佬都是用的贪心解法。所以来介绍一下DP。

DP的精髓在于转移。所以状态的设置要为转移服务。转移要保证无后效性和最优子结构。DP就是这些东西，再也没有什么其他的了。什么答案的统计都是细节问题。

那么这道题显然，针对于两棵树之间的转移，一定有第$i$棵树不砍、往左砍、往右砍这三种状态，每种状态都会对应一个最优决策，所以就直接按这个设状态：$dp[i][0/1/2]$。

然后按题意转移就行。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,dp[maxn][3];
struct tree
{
	int x,h;
}t[maxn];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	    scanf("%d%d",&t[i].x,&t[i].h);
	dp[1][0]=1;
    if(t[2].x-t[1].x>t[1].h) 
        dp[1][1]=1;
	for(int i=2;i<=n;i++)
	{
		dp[i][0]=max(dp[i-1][0],dp[i-1][1]);
		if(t[i].x-t[i-1].x>t[i-1].h) 
            dp[i][0]=max(dp[i][0],dp[i-1][2]);
		if(t[i].x-t[i-1].x>t[i].h) 
            dp[i][1]=max(dp[i-1][1]+1,dp[i-1][0]+1);
		if(t[i].x-t[i-1].x>t[i].h+t[i-1].h) 
            dp[i][1]=max(dp[i][1],dp[i-1][2]+1);
		dp[i][2]=max(dp[i-1][0],dp[i-1][1])+1;
		if(t[i].x-t[i-1].x>t[i-1].h) 
            dp[i][2]=max(dp[i][2],dp[i-1][2]+1);
	}
	cout<<max(max(dp[n][0],dp[n][1]),dp[n][2]);
	return 0;
}
```



---

## 作者：李若谷 (赞：0)

### 贪心

对于第一棵树，砍了倒左边。其他的尽量倒左边，否则倒右边。

两边都不行再不砍。

证明：

对于第一棵树，很显然要倒左边。因为如果倒右边可能会对第二棵树有负面影响，如果不砍，那么对于第二棵树的影响和砍一样，但是不会的砍树总数。

对于第$i$颗数，如果能够倒左边（和第$i-1$颗砍倒后不会冲突），肯定倒左边，因为如果倒右边可能会对第$i+1$课带来负面影响，如果不砍不会增加总数。

如果不能倒左边，那么看是否能倒右边。如果能倒右边就倒右边。

因为如果能倒右边，不外两种情况。

1）倒右边后和下一颗倒左边不冲突。

这样很显然要倒右边，因为如果倒右边不会对下一颗造成负面影响。

2）倒右边后和下一颗倒左边会冲突。

这种情况依然要倒右边。因为我们现在讨论的只是不能倒左边的情况。那么如果倒右边，总数会加$1$，但是下一颗不能倒左边。如果这颗不砍，下一颗倒左边的话，总数仍然会加$1$，所以是一样的。但是为了程序简便，所以倒右边。

AC $1.26s$，暂居rk2。


代码：
```cpp

#include <stdio.h>
int x[100005],h[100005];
inline int read()
{
	int ans = 0;
	char ch = getchar();
	while(ch<'0'||ch>'9') ch = getchar();
	while(ch>='0'&&ch<='9')
	{
		// ans = ans * 10 + ch - '0';
		ans = (ans<<1) + (ans<<3) + (ch^48);
		ch = getchar();
	}
	return ans;
}
void write(int x)
{
	if(x>9)
	{
		write(x/10);
	}
	putchar(x%10 + '0');
}	
int main()
{
	int n = read();
	int tot = 1; //第一棵树向左、
	for(register int i=1;i<=n;i++) x[i]=read(),h[i]=read();
	int pre = 0; //记录上一棵树向右的高度。
	x[n+1] = 2e9+10;
	for(register int i=2;i<=n;i++)
	{
		if(x[i-1]+pre < x[i]-h[i]) //当前树向左
		{
			pre=0,++tot;
		}
		else if(x[i]+h[i]<x[i+1]) //当前树向右
		{
			pre = h[i],++tot;
		}
		else	//不砍
			pre = 0;
	}
	write(tot);
}

```

---

## 作者：xun薰 (赞：0)

我来写一个不一样的方法。

首先我们肯定知道，最左边和最右边的树一定可以砍倒，最左边的往左倒，最右边的向右倒就可以了。

Lp,Rp均为树的编号，初始值Lp=1,Rp=n;
L为左边被占位置，R为右边被占位置。

[Lp,Rp]左边向左倒，右边向右倒，则剩下需要解决的区间为[Lp+1,Rp-1]。
再对[Lp+1,Rp-1]，Lp+1能向左倒向左倒，不能左倒向右倒，Rp-1能向右倒向右倒，不能右倒向左倒，同时用L，R标记能倒的范围。

即最头上的树尽量向两侧倒，这样我们需要解决的区间范围越来越小。


```c
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100009
using namespace std;

int ans;

int n,L,R,Lp,Rp;

int x[N],h[N];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&h[i]);
	if(n==1) {cout<<"1";return 0;}
	if(n==2) {cout<<"2";return 0;}
	ans=2;L=x[1];R=x[n];Lp=2;Rp=n-1;
	while(Lp<=Rp)
	{
		if(Lp==Rp)
		{
			if(x[Lp]-h[Lp]>L||x[Lp]+h[Lp]<R) ans++;
			break;
		}
		bool flag1=0,flag2=0;
		if(x[Lp]-h[Lp]>L) 
		{
			flag1=true;
			ans++;
			L=x[Lp];
		}else
		if(x[Lp]+h[Lp]<x[Lp+1])
		{
			flag1=true;
			ans++;
			L=x[Lp]+h[Lp];
		}
		if(!flag1) L=x[Lp];
		Lp++;
	//	if(Lp>Rp) break;
		if(x[Rp]+h[Rp]<R)
		{
			flag2=true;
			ans++;
			R=x[Rp];
		}else
		if(x[Rp]-h[Rp]>x[Rp-1])
		{
			flag2=true;
			ans++;
			R=x[Rp]-h[Rp];
		}
		if(!flag2)R=x[Rp];
		Rp--;
	}
	cout<<ans<<endl;
	return 0;
} 
```



---

## 作者：Bosun (赞：0)

这道题目首先看到数据范围就知道是贪心
显然第一棵树往左倒，第n棵往右倒，中间的树怎么办呢？
考虑到实现简单，我们先按照x坐标从小到大排序，中间的树优先往左倒，倒不了就往右倒，然后记录一个f,表示这棵树是往哪个方向倒，到下一棵树就知道上一棵树的f了，如果这棵树往左倒，那么上一棵树倒下后树根的x坐标必须小于我的坐标-我的长度。如果往右倒，由于不知道下一棵树往哪个方向倒，所以贪心满足自己，直接向右倒就行了

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,h,f;
}a[100001];
int n;
int cmp(node x,node y){
	return x.x<y.x;
}
int main(){
	int i;
	cin>>n;
	for(i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].h);
	sort(a+1,a+n+1,cmp);
	int ans=2;
	for(i=2;i<n;i++){
		if(a[i].x-a[i].h>a[i-1].x+max(a[i-1].f,0)*a[i-1].h)a[i].f=-1,ans++;
		else if(a[i].x+a[i].h<a[i+1].x)a[i].f=1,ans++;
	}
	if(n==1)cout<<1<<endl;
	else cout<<ans<<endl;
	return 0;
}
```


---

## 作者：yangwenbin (赞：0)

# 题解 CF545C 【Woodcutters】

没看过题目的同学请走这（[传送门](https://www.luogu.com.cn/problem/CF545C#submit)）

首先发现这道题，一看见就觉得是一道dp的题目。

因为每一次操作大概是与前面的一棵树（或几棵树继承下来）

首先分为三类，第一类即当前的棵树被砍且向左倒：

这一类只要这一棵树砍倒后不与前面的树相交即可，即：

```
input[i-1].x < input[i].x - input[i].height
```

第二类是当前的棵树向右倒，这样只要不与后面的树相交即可，即：

```
input[i].x + input[i].height < input[i+1].x
```

第三类就是不砍。

但是推着发现向右砍对后面的操作有影响，即有后效性。所以我排除了dp。

同时也发现了如果向右倒极有可能是会使后面的树不能砍倒，所以是下策，而不砍是下下策。

此时，贪心的思路逐渐浮出水面，事实上只要按照之前的三种分类逐一判断。

优先向左，其次向右，不到万不得已必须砍。

所以本道题的核心代码就出来了，即：

```
for (int i = 1; i <= n; ++i){
	if(rs < input[i].x - input[i].height){
		rs = input[i].x;
		++ans;
	}else if(input[i].x + input[i].height < input[i+1].x){
		rs = input[i+1].x;
		++ans;
	}else{
		rs = input[i].x;
	}
}
```

解释一下：

 rs 是指目前为止砍倒树不能越过的位置。rs记录为树最右边的的位置上
 
#  code

```
#include <bits/stdc++.h>
using namespace std;
inline int read(){
	int x = 0;char ch = getchar();
	while (ch < '0' || ch > '9') ch = getchar();
	while (ch >= '0' && ch <= '9'){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}return x;
}
int n,rs;
struct tree{
	int x,height;
}input[100050];
int main(){
	n = read();
	for (int i = 1; i <= n; ++i){
		input[i].x = read();input[i].height = read();
	}
	int ans = 0;
	input[n+1].x = 2147483640;
	rs = -2147483640;
	for (int i = 1; i <= n; ++i){
		if(rs < input[i].x - input[i].height){
			rs = input[i].x;
			++ans;
		}else if(input[i].x + input[i].height < input[i+1].x){
			rs = input[i+1].x;
			++ans;
		}else{
			rs = input[i].x;
		}
	}
	printf("%d\n",ans);
}

```



---

