# Anton and Ira

## 题目描述

Anton loves transforming one permutation into another one by swapping elements for money, and Ira doesn't like paying for stupid games. Help them obtain the required permutation by paying as little money as possible.

More formally, we have two permutations, $ p $ and $ s $ of numbers from $ 1 $ to $ n $ . We can swap $ p_{i} $ and $ p_{j} $ , by paying $ |i-j| $ coins for it. Find and print the smallest number of coins required to obtain permutation $ s $ from permutation $ p $ . Also print the sequence of swap operations at which we obtain a solution.

## 说明/提示

In the first sample test we swap numbers on positions 3 and 4 and permutation $ p $ becomes 4 2 3 1. We pay $ |3-4|=1 $ coins for that. On second turn we swap numbers on positions 1 and 3 and get permutation $ 3241 $ equal to $ s $ . We pay $ |3-1|=2 $ coins for that. In total we pay three coins.

## 样例 #1

### 输入

```
4
4 2 1 3
3 2 4 1
```

### 输出

```
3
2
4 3
3 1
```

# 题解

## 作者：stansxt (赞：4)

# 思路
- 这题也不难，随便说点思路吧，与一楼大佬稍有不同。
- 最开始要把$s$数组化成升序，然后对$p$做一下变换。相信这个大家都会$QwQ$
- 然后我是先做的第一问。第一问呢，我们先看看下限。由于每一个数$p[i]$,它应该在$p[i]$这个位置上而不是$i$位置。因此每个数交换过程中移动的距离的总和是$\sum_{i=1}^n|p[i]-i|$。又由于每次交换的代价就是这两个数分别移动的距离，因此答案下限就是$\frac{\sum_{i=1}^n|p[i]-i|}{2}$。
- 我们观察一下答案的下限能否取到，以及怎么取到。对于$p$数组，我们从大到小调整（从小到大其实同理）。当做到$i$时，由于比$i$更大的数都已经在正确的位置上了，因此我们的$i$只会向右移动。而移动时，我们只与$j$满足$p[j]<i$的位置进行交换。因此，移动时我们保证了对于$p[i]>i$的$p[i]$不向左移动，$p[i]<i$的$p[i]$不向右移动。而因为$\sum_{i=1}^np[i]-i=0$，所以$\sum_{i=1,p[i]>i}^np[i]-i$必然等于$\sum_{i=1,p[i]<i}^ni-p[i]$，且都等于答案的下限$\frac{\sum_{i=1}^n|p[i]-i|}{2}$。我们做的时候是没有浪费的，移动步数为$\sum_{i=1,p[i]>i}^np[i]-i$，所以这就是答案。
- 第二问，直接按我上面说的模拟即可。话不多说，直接上代码~
---
# 代码
```
//CF584E Anton and Ira
//submit 1 
//By sxt on 2020.8.26 
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
#define rg register int
#define il inline
#define is_(x) (x<='9'&&x>='0')
#define mid (l + r >> 1)
#define el else if
#define lowbit(x) (x&(-x))
#define Mem(x) memset(x, 0, sizeof(x))
#define in read()
#define _num (ch<='9'&&ch>='0')
using namespace std;
const int N = 2007;
const int M = 2e6+7;
il int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!_num){
		if(ch=='-')
			f=-1;
		ch=getchar();
	}
	while(_num){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
char f[11];
int pcnt;
il void pint(int x){
	pcnt = 0;
	if(x == 0) putchar('0');
	if(x < 0){
		x = -x;
		putchar('-');
	}
	while(x){
		f[++pcnt] = x % 10 + '0';
		x /= 10;
	}
	while(pcnt) putchar(f[pcnt--]);
	putchar('\n');
}
int n, a[N], b[N], to[N], ans;
struct node{
	int x, y;
}x[M];
signed main()
{
//	freopen("1.txt", "r", stdin);
	n = in;
	for(rg i = 1; i <= n; ++ i)a[i] = in;
	for(rg i = 1; i <= n; ++ i)b[i] = in, to[b[i]] = i;
	for(rg i = 1; i <= n; ++ i){
		a[i] = to[a[i]];
		ans += abs(a[i] - i);
	}
	ans >>= 1;
	pint(ans);
	ans = 0;
	for(rg i = 1; i <= n; ++ i)to[a[i]] = i;
	for(rg i = n, now = to[n]; i; -- i, now = to[i])for(rg j = to[i]+1; j <= n; ++ j)
		if(a[j] <= now){
			x[++ans] = (node){j, now};
			swap(a[now], a[j]);
			now = j;
		}
	pint(ans);
	for(rg i = 1; i <= ans; ++ i)printf("%d %d\n", x[i].x, x[i].y);
    return 0;
}



```



PS:1.21s那个大佬怎么做的呀@_@太强了吧T_T

---

## 作者：素质玩家孙1超 (赞：3)

考虑贪心，可以$O(n^2)$扫描，贪心判断是否交换

首先把第一个序列和第二个序列搞成一个$[1,n]$序列

就是这么干

```cpp
//其中R();是读入
n=R();
for(int i=1;i<=n;i++) a[i]=R();
for(int i=1;i<=n;i++) b[R()]=i;
for(int i=1;i<=n;i++) tmp[i]=b[a[i]];
for(int i=1;i<=n;i++) b[i]=tmp[i];

```
比如
```
7
7 4 6 2 5 1 3
7 5 6 1 3 2 4
可以变换为
1 5 3 6 7 4 2
```
这样题目就转换为对一个序列交换，使其升序

然后扫描对于

$ b[i]>i$且$b[j]<=i$且$j<=b[i]$ ($i < j$)

的交换$b[i]$,$b[j]$计算贡献就好了

代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
inline int R()
{
	char c;int sign=1,res=0;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1;res+=c-'0';
	while((c=getchar())>='0'&&c<='9') res=res*10+c-'0';
	return res*sign;	
}
const int Maxn=2e6+6;
int n;
int a[Maxn],b[Maxn],tmp[Maxn]; 
int Ans[Maxn][2],top;
int main()
{
	n=R();
	for(int i=1;i<=n;i++) a[i]=R();
	for(int i=1;i<=n;i++) b[R()]=i;
	for(int i=1;i<=n;i++) tmp[i]=b[a[i]];
	for(int i=1;i<=n;i++) b[i]=tmp[i];//读入
	int ans=0,st=1;
	bool f=0;
	LXY:;
	while(b[st]==st) ++st;//小优化
	for(int i=st;i<=n;i++)
	{
		if(b[i]>i)
		{
			for(int j=i+1;j<=n;j++)
			{
				if(b[j]<=i&&j<=b[i])
				{
					ans+=(j-i);
					Ans[++top][0]=i;
					Ans[  top][1]=j;
					swap(b[i],b[j]);
					goto LXY;
				}
			}
		}
	}
	printf("%d\n",ans);
	printf("%d\n",top);
	for(int i=1;i<=top;i++)
	printf("%d %d\n",Ans[i][0],Ans[i][1]);
}
```

---

## 作者：Imiya (赞：1)

考虑每次一单位代价都会使两点离各自目标近一格，显然代价的下界是 $\frac 12\sum\vert p_i-i\vert$。

证明可以取到下界。

已知 $p$ 为长度为 $n$ 的排列，$\forall i,p_i\not=i$。

证明： $\exist i,j$，满足 $p_j\le i<j\le p_i$。

考虑反证：若 $\forall i<p_i,\forall j\in(i,p_i],p_j>i$。  
则有  
$\because p_1>1\lrArr p_1\ge 2,\therefore p_2>1$  
又 $\because p_2\not=2,\therefore p_2\ge2,\therefore p_3>2$。

即数学归纳法。易知 $p_1>1$。  
若 $p_k>k$,  
则 $p_k\ge k+1$  
$\therefore p_{k+1}>k$  
又 $\because p_{k+1}\not=k+1$  
$\therefore p_{k+1}>k+1$

即若原命题为假，则 $\forall i,p_i>i$，显然与 $p$ 为排列的条件矛盾。所以原命题为真。

也就是一定存在 $i,j$，使得 $p_j\le i<j\le p_i$，此时交换 $i,j$ 一定不劣。又考虑到交换之后剩下的还是排列，因为自环没有入度，所以缩去自环影响不大，可以继续找这样一对点交换。一直交换直到只剩下自环结束，此时代价取到下界 $\frac 12\sum\vert p_i-i\vert$。

考虑如何找到这样一对点，类似上面的数学归纳法，找到第一个 $p_i<i$，此时 $i-1,i$ 是一对符合条件的点，交换后 $i-1$ 可能是第一个 $p_{i-1}<i-1$，也就是不断和左边第一个非自环交换，交换到头再找下一个 $p_i<i$ 即可。交换次数 $O(n^2)$。

```cpp
#include<iostream>
using namespace std;
const int N=2000100;
int pos[N],n,a[N],b[N];
void init(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++)cin>>a[i],pos[a[i]]=i;
}
pair<int,int> ans[N];
int cnt;
inline void opt(int x,int y){
    ans[++cnt]=make_pair(x,y);
    swap(b[x],b[y]);
}
int main(){
    // freopen("read.in","r",stdin);
    init();
    int tot=0;
    for(int i=1;i<=n;i++)tot+=abs(pos[b[i]]-i);
    cout<<tot/2<<endl;
    for(int i=1;i<=n;i++){
        if(pos[b[i]]<i){
            int lst=i;
            int target=pos[b[i]];
            for(int j=i-1;j>=target;j--)if(pos[b[j]]>j){
                opt(j,lst);
                lst=j;
            }
        }
    }
    cout<<cnt<<endl;
    for(int i=1;i<=cnt;i++)printf("%d %d\n",ans[i].first,ans[i].second);
    return 0;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

我们转换一下题面，对 $p$ 建立以 $s$ 为基底的映射，因此 $s$ 变成了 $1\sim n$ 的有序排列，$p$ 变成 $1\sim n $ 的乱序排列，以便于我们进行讨论。

那么现在我们要找到一个普适化的策略来调整 $p$ 使得 $p$ 最终变得升序。

我们可以证明，一定存在 $(i,j),i<j$ 有 $p_j≤i,j≤p_i$。我们可以尝试构造反例来证明，可以发现即使是设计的构造最终也定会存在上面的情况。这也可以说明在 $p$ 变得有序之前，一定会有以上满足条件的二元组存在。

然后当我们每次发现这种二元组，就交换其即可。

事实证明暴力出奇迹。

---
```c++
	for(int i=1;i<=n;i++)a[i]=rd;
	for(int i=1;i<=n;i++)p[rd]=i;
	for(int i=1;i<=n;i++)t[i]=p[a[i]];
	for(int i=1;i<=n;i++)p[i]=t[i];
    
	while(1){
		int f=0;
		int t=0;
		while(p[t]==t)t++;
		for(int i=t;i<=n;i++){
			if(p[i]<=i)continue;
			for(int j=i+1;j<=n;j++){
				if(p[j]<=i&&j<=p[i]){
					cnt+=(j-i);
					ans[++top][0]=i,ans[top][1]=j;
					swap(p[i],p[j]);
					f=1;break;
				}
			}
			if(f)break;	
		}
		if(!f)break;
	}
    
```




---

