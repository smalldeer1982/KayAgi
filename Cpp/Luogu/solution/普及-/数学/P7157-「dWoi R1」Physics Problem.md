# 「dWoi R1」Physics Problem

## 题目背景

面对白板上的物理题，王马陷入了沉思 ……

## 题目描述

有 $n$ 个状态，编号为 $1$ 到 $n$。这 $n$ 个状态之间有 $k$ 种转换关系，第 $i$ 个转换关系描述为：第 $u_i$ 个状态和第 $v_i$ 个状态可以进行转换。当两个状态之间没有直接的转换关系但有间接的转换关系时，那么这两个状态之间有升降华关系。

求有多少个升降华关系。

**王马不会做很难的物理题，所以保证一个状态一定可以通过直接或间接的转换为另一个任意状态。**

## 说明/提示

#### 样例 1 解释

一共有 $3$ 个状态，编号为 $1,2,3$，第 $1$ 个状态和第 $2$ 个状态之间有转换关系，第 $2$ 个状态和第 $3$ 个状态之间有转换关系，第 $1$ 个状态和第 $3$ 个状态之间没有直接的转换关系，但可以用第 $2$ 个状态做桥梁进行转换，所以第 $1$ 个状态和第 $3$ 个状态之间有升降华关系。只有这一个升降华关系，输出 $1$。

#### 数据规模与约定

**本题采用捆绑测试。**

- Subtask 1（5 pts）：$n \le 2$。
- Subtask 2（10 pts）：$k=n-1$，$u_i+1=v_i$。
- Subtask 3（10 pts）：$k=n-1$，$u_i=1$。
- Subtask 4（25 pts）：$n,k \le 1000$。
- Subtask 5（50 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le n,k \le 10^7$，$1 \le u_i,v_i \le n$。

保证 $u_i \ne v_i$ 且不存在 $i \ne j ∧(u_i =u_j∧v_i=v_j)$ 和 $i \ne j∧(u_i=v_j∧u_j=v_i)$。

这句话也可以理解为无重边无自环。

#### 提示

注意，对于下面这种情况（`a - b` 代表 $a$ 能与 $b$ 互相转换）：

```cpp
1 - 2
2 - 3
1 - 3
```

第 $1$ 个状态和第 $3$ 个状态算有直接转换关系，即转换关系取“最短路”。

## 样例 #1

### 输入

```
3 2
1 2
2 3```

### 输出

```
1```

# 题解

## 作者：一只书虫仔 (赞：22)

![](https://cdn.luogu.com.cn/upload/image_hosting/zxxf3qro.png)

$$\color{Red}\sf dWoi\ Round\ 1\ A\ Physics\ Problem$$

#### Description

> 给定一个 $n$ 点 $k$ 边的连通无向图，求有多少组满足要求的点对使得这两个点之间的最短路长度大于 $1$。         
> $1 \le n,k \le 10^7$，$1 \le u_i,v_i \le n$，保证无重边无自环

#### Subtask 1

约束条件：$n \le 2$。

当 $n \le 2$ 时，不存在满足要求的点对使得最短路长度大于 $1$，因此输出 $0$。

#### Subtask 2

约束条件：该图是一条链。

每一个点 $p$ 都可以往他的右边找到 $n-p-1$ 个点，因此答案为：

$$\sum\limits_{i=1}^{n-2}n-i-1$$

#### Subtask 3

约束条件：该图是一个菊花图。

和链差不多，就不说了，~~其实是书虫太懒没写~~

#### Subtask 4

约束条件：$n,k \le 1000$。

有一个奇怪的 $\mathcal O(n^2)$ 做法，也就是枚举所有点对然后判断他们在不在同一条边（

应该能过，放的很水。

#### Subtask 5

这题把连通，无重边，无自环都限制了，题目就简单 1w 倍了。

首先我们先任意选择两个点形成的点对，应该有 $\textsf C_n^2$ 种选择方法，然后我们要把 $k$ 条边直接相连的点对个数减掉，也就是减掉 $k$，所以最终答案为：

$$\textsf C_n^2-k=\dfrac{n \times (n-1)}{2}-k$$

直接 $\mathcal O(1)$。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int main () {
	long long n, k;
	scanf("%lld%lld", &n, &k);
	printf("%lld", n *(n - 1) / 2 - k);
	return 0;
}

```

---

## 作者：zjrdmd (赞：6)

看几乎所有题解都是$O(1)$的啊/kk

这题$n$的范围只有$10^7$，所以很显然$O(n)$可过，我们考虑题目保证“保证一个状态一定可以通过直接或间接的转换为另一个任意状态”，所以只有与当前点**直接相连**的点和**自己本身**没有升降关系，剩下的所有点都有，所以我们可以统计每个点与他直接相连的点的个数，暴力统计即可。

```cpp
#include <iostream>
#include <cstdio>
#define ri register int
#define int long long

inline int read() {
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') {x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

const int N=1e7+5;
int a[N],ans=0;

signed main(void){
	int n=read(),k=read();
	for(ri i=1,u,v;i<=k;i++){
		u=read(),v=read();
		a[u]++;a[v]++;
	}
	for(ri i=1;i<=n;i++)ans+=(n-a[i]-1);
	printf("%lld",ans/2);
	return 0;
}

```


---

## 作者：WinterRain208 (赞：5)

【「dWoi R1」Physics Problem】

我记得这题好像是某比赛的第一题，但我没打。

这题简单来说就是$n$个元素，有$k$对可以互相转化，让你求不能互相转化的元素有几对。

不要被题里面物理题物理题什么的迷惑住（蒟蒻没学过物理）,这题就是一道简单的排列组合。

$n$个元素，也就是说有$n*(n-1)/2$对，小学乘法原理，这里考虑$a-b$和$b-a$重复。

再减去可以互相转换的$k$对即可，输入中只有前两个数是有用的，其他对答案没有影响，因为没有重复的。

解法：

$n*(n-1)/2-k$。

### 丑陋的代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long a,b;
    cin>>a>>b;
    cout<<a*(a-1)/2-b;
    return 0;
}
```

## wtrl


---

## 作者：VanHelsing (赞：3)

嗯，这个题吧，他很让我生气。

让我生气的原因主要是：我做这道题的时候，是用并查集的思路来做的，因为保证无重边，所以每次查一下两个点是否已经被连上了，然后连上。记录一下每个点所在的连通块中的点的个数 $siz$ 以及这个点和其他的点连了几条边 $deed$ ，答案就是所有点的 $siz-deed$ 在除以2。用一个并查集可以搞掉，也的确能过这道题。

代码如下(码风毒瘤，勿喷）：  
```cpp
#include<bits/stdc++.h>

using namespace std;

int read()
{
    int x=0,y=1;
    int ch=getchar();
    while(!isdigit(ch))
    {
        if(ch=='-')
        {
            y=-1;
        }
        ch=getchar();
    }
    
    while(isdigit(ch))
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    return x*y;
}

const int maxn=1e7+5;

int n,k;

int fa[maxn];

int deed[maxn],siz[maxn];

int find(int x)
{
	if(fa[x]==x)
	{
		return x;
	}
	
	else
	{
		return fa[x]=find(fa[x]);
	}
}

int main()
{
	n=read();
	
	k=read();
	
	for(int i=1;i<=n;i++)
	{
		fa[i]=i;
		
		siz[i]=1;
	}
	
	for(int i=1;i<=k;i++)
	{
		int x,y;
		
		x=read();
		
		y=read();
		
		int fx=find(x),fy=find(y);
		
		if(fx!=fy)
		{
			fa[fy]=fx;
			
			siz[fx]+=siz[fy];
		}
		
		deed[x]++;
		
		deed[y]++;
	}
	
	long long ans=0;
	
	for(int i=1;i<=n;i++)
	{
		siz[i]=siz[find(i)];
		
		ans+=siz[i]-1-deed[i];
	}
	
	printf("%lld\n",ans/2);
}
```

生气的原因是：在和别人说这道题的时候，知道了另一种傻逼做法。每次连一条边的时候都会使本来不连边的答案-1（因为最后一定一个状态能变成另一个状态）。那么答案就是 $C_n^2 - m $ 。

正解代码就这么短：  
```cpp
#include<bits/stdc++.h>

using namespace std;

const int maxn=1e7+5;

int n,m;

int main()
{
	scanf("%d%d",&n,&m);
	
	printf("%lld\n",1ll*n*(n-1)/2-m);
}
```

写一下这个题的第一个题解发泄一下愤怒（

---

## 作者：血色黄昏 (赞：1)

来一篇本题最短题解(

首先当我们把题目认真看完后就能注意到这句话

```
王马不会做很难的物理题，所以保证一个状态一定可以通过直接或间接的转换为另一个任意状态
......无重边无自环
```

那么说明这一定是个连通且正常的图

那么显然答案就是让你求有$n$个点的完全图边数减去连上的边数，即为$\frac{n(n-1)}2{}-k$

那么此题最短解就出来了(当然是用python啦)

```python
n, m = input().split()#读入
print(int(n) * (int(n) - 1) // 2 - int(m))#按意思输出
```

感谢审核+观看/qq

---

## 作者：Keep_RAD (赞：1)

这一题我这只小蒟蒻比赛时没有打出代码，

总以为这是一道和并查集有关的题，

所以套上了并查集的模板，

交上去一看：

稻花香里说丰年，**听取TLE声一片！**

由于比赛是OI赛制，我以为过了，结果竟然$TLE$！

比赛完，我思考了一下，发现了一句话：

**保证一个状态一定可以通过直接或间接的转换为另一个任意状态。**

每个点一定连通！

那么就可以直接用$O(1)$的公式套了。

$n$个元素，也就是说有$n*(n-1)/2$对，减去直接连通的$k$个关系，就有$n*(n-1)/2-k$个升降华关系了。

上代码！

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n,k,x,y;
    cin>>n>>k;
  	for(int i=0;i<k;i++)
    {
    	cin>>x>>y;
    }
                         
    cout<<(n*n-n)/2-k; //最好不要括号套括号，所以改成(n*n-n)
    return 0;
}
```

不要运行，

https://www.luogu.com.cn/record/44292460

还是会超时！

why?

让我们回到数据范围：

$10$的$7$次方，也就是说光输入就会超时！

再看我们的公式，只和$n$和$k$有关，就不用输入哪几个直接联通的点了。

AC代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    long long n,k,x,y;
    cin>>n>>k;                   
    cout<<(n*n-n)/2-k;
    return 0;
}
```

懂了吗？

管理员大大求过~~


---

## 作者：Cocoly1990 (赞：1)

## P7157 【「dWoi R1」Physics Problem】

看到 第 $u_i$ 个状态和第 $v_i$个状态可以进行转换 这句话，一眼就看出来和图相关

**王马不会做很难的物理题，所以保证一个状态一定可以通过直接或间接的转换为另一个任意状态。**

这句话非常重要，它限制了这是一个**连通图**。

那么有多少对可能的状态$(a,b)$？

也就是$\tbinom{n}{2}$种

但是还需要去除$k$条直接相连的$(a,b)$，因为他们不是升降华关系

最后的答案就是$\tbinom{n}{2}-k$

记得开$long$ $long$ ，不开见祖宗

代码丑死了，不贴

---

## 作者：REAL_曼巴 (赞：0)

此题只和 $n$ 与 $m$ 有关，仅需输入他们，否则会超时。有 $n$ 个节点，我们不难用乘法原理看出，随便哪两个点，我们都会有以下个联通的方案数量：

$n \times (n+1) \div 2$

然后我们要把 $k$ 条边直接相连的点对个数减掉，我们就可以得出最终公式，套公式输入输出即可。

注：要用长整型！

```
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,k,x,y;
    cin>>n>>k;                   
    cout<<(n*n-n)/2-k;
    return 0;
}
```



---

## 作者：Aw顿顿 (赞：0)

一共有 $n$ 个点，$k$ 条边，求有多少组满足要求的点对，使得两点之间的最短路长度大于 $1$。

注意到**连通，无重边，无自环**。

那么任意选择两个点，一共是 $\binom{2}{n}$ 中选择方法，再减去 $k$ 条相连的边即可。

那么，答案为：

$$\dfrac{n(n-1)}{2}-k$$

哦对了顺便，因为答案只和 $n,k$ 有关，就别全部数据都读入了，可能会 T。


代码易于书写：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,k;
int main(){
	cin>>n>>k;
	cout<<n*(n-1)/2-k;
}
```

---

