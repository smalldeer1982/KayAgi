# And Reachability

## 题目描述

Toad Pimple 有一个整数数组 $a_1,\dots,a_n$。  
当 $x < y$ 且存在 $x = p_1 < \dots < p_k = y$ 的数列 $p$ 满足 $a_{p_i} \& a_{p_{i+1}} > 0$ 时，我们称 $y$ 是可从 $x$ 到达的。  
其中 $\&$ 表示按位与运算。

现在给出 $q$ 组下标，请检查它们可否到达。

## 说明/提示

第一个样例中，$a_3 = 0$，与其按位与结果总是 $0$，所以不可到达。  
$a_2 \& a_4 > 0$，所以 $4$ 可从 $2$ 到达。  
并且从 $1$ 到达 $4$ 中，$p = [1,2,4]$。

## 样例 #1

### 输入

```
5 3
1 3 0 2 1
1 3
2 4
1 4
```

### 输出

```
Fou
Shi
Shi
```

# 题解

## 作者：CYZZ (赞：7)

# [And Reachability](https://www.luogu.com.cn/problem/CF1168C)
## 推导
看到按位与操作马上想到按位考虑。

首先可以想到：如果 $a_i$ 和 $a_j$ 的 第 $k$ 位（二进制下）都为 $1$，则可以从 $a_i$ 到达 $a_j$，称 $a_i$ 可以通过 $k$ 到达 $a_j$。

设 $f_{i,j}$ 表示编号小于 $i$ 中最大的第 $j$ 位为 $1$ 的点，则 $f_{i,j}$ 可以通过 $f_{i-1,j}$ 求出。

那么如何处理两点能否到达呢？能到达不一定必须要有一位相同，还可以通过中间的某些点（中转站）中转一下。

设 $dp_{i,j}$ 为编号小于 $i$ 中最大的第 $j$ 位为 $1$ 且可以到达 $a_i$ 的点，分两种情况讨论：

- 需要中转站，设中转站为 $x$，设 $x$ 通过 $k$ 可以到达 $a_i$，从 $dp_{i,j}$ 可以到达 $x$。则 $x$ 和 $a_i$ 的第 $k$ 位都必须为 $1$。我们可以贪心地取 $x=f_{i,k}$，因为中转站离 $a_i$ 越近，中转站前面的点就会越多，选择也更多，所以一定更优（感性理解一下）。那么就有：
$$dp_{i,j}=\max(dp_{i,j},dp_{f_{i,k},j})$$
- 不需要中转站。也就是说，中转站本身第 $j$ 位就是 $1$。此时：
$$dp_{i,j}=\max(dp_{i,j},f_{i,k})$$

## 统计答案
对于输入的 $l$ 和 $r$，枚举 $a_l$ 和 $a_r$ 的每一位。

如果 $l$ 的第 $i$ 位为 $1$ 且 $dp_{r,i}\ge l$，那么把 $dp_{r,i}$ 作为中转站可行
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,q,a[300005],f[300005][20],dp[300005][20];
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        for(int j=0;j<20;j++)
        {
            if((a[i-1]>>j)&1)
                f[i][j]=i-1;//上一位
            else
                f[i][j]=f[i-1][j];
        }
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<20;j++)
        {
            for(int k=0;k<20;k++)
            {
                if(!((a[i]>>k)&1))//利用第k位连到i
                    continue;
                dp[i][j]=max(dp[i][j],dp[f[i][k]][j]);//中转
                if((a[f[i][k]]>>j)&1)
                    dp[i][j]=max(dp[i][j],f[i][k]);//不中转
            }
        }
    }
    while(q--)
    {
        int x,y,flag=0;
        scanf("%d%d",&x,&y);
        for(int i=0;i<20;i++)
        {
            if(((a[x]>>i)&1)&&dp[y][i]>=x)//符合要求
            {
                flag=1;
                break;
            }
        }
        if(flag)
            printf("Shi\n");
        else
            printf("Fou\n");
    }
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：wucstdio (赞：6)

比赛的时候只想到了线段树的解法。

首先让我们考虑答案可以怎么求。可以用如下的代码求出：

```cpp
void check(int x,int y)
{
    int ans=a[x];
    for(int i=x+1;i<=y;i++)
      if(a[i]&ans)ans|=a[i];
    return ans&y;
}
```

也就是说，我们可以从第$x+1$开始枚举到$y$，一路上遇到一个数按位与不是$0$就或起来。

容易发现这个是满足可加性的。这也就启示我们可以用线段树来求。

线段树中的每一个节点储存一个长度为19的数组，依次表示$2^k$从左边传进来，一路走完这个区间后到了右边会出来什么数字。

合并的话可以直接枚举左边进来的是哪个数，然后直接放到右边做一个按位或：

```cpp

void pushup(int o)
{
    for(int i=0;i<19;i++)
    {
        tree[o].res[i]=tree[lson].res[i];
        int v=tree[lson].res[i];
        for(int j=0;j<19;j++)
          if((1<<j)&v)tree[o].res[i]|=tree[rson].res[j];
        tree[o].res[i]|=tree[rson].res[i];
    }
}
```

同理可以用这个来求出答案。

注意的是pushup一次是$O(\log^2)$的，更新答案是$O(\log n)$的，这就导致这个算法初始化和查询的复杂度都是$O(n\log^2 n)$，不过CF机子那么快300000两个$log$3s时限还是能爆过去的。

下面是代码，注意空间：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define lson o<<1
#define rson o<<1|1
#define mid (l+r)/2
using namespace std;
int n,m,a[300005];
struct Tree
{
    int res[19];
}tree[1200005];
void pushup(int o)
{
    for(int i=0;i<19;i++)
    {
        tree[o].res[i]=tree[lson].res[i];
        int v=tree[lson].res[i];
        for(int j=0;j<19;j++)
          if((1<<j)&v)tree[o].res[i]|=tree[rson].res[j];
        tree[o].res[i]|=tree[rson].res[i];
    }
}
void build(int o,int l,int r)
{
    if(l==r)
    {
        for(int i=0;i<19;i++)
          if((1<<i)&a[l])tree[o].res[i]=a[l];
        return;
    }
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(o);
}
int val;
bool ask(int o,int l,int r,int from,int to,int y)
{
    if(val&y)return 1;
    if(l>=from&&r<=to)
    {
        int x=0;
        for(int i=0;i<19;i++)
          if((1<<i)&val)x|=tree[o].res[i];
        val|=x;
        return val&y;
    }
    bool f=0;
    if(from<=mid)f|=ask(lson,l,mid,from,to,y);
    if(f)return 1;
    if(to>mid)f|=ask(rson,mid+1,r,from,to,y);
    return f;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    build(1,1,n);
    while(m--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        val=a[x];
        if(ask(1,1,n,x+1,y-1,a[y]))printf("Shi\n");
        else printf("Fou\n");
    }
    return 0;
}
```

---

## 作者：81179332_ (赞：3)

按位考虑

定义 $g_{i,j}$ 表示位置小于 $i$ 中第 $j$ 为为 $1$ 的最靠近 $i$ 的数的位置

若 $p_k$ 为 $i$，则显然我们可以贪心选 $p_{k-1}=g_{i,j}$

设 $f_{i,j}$ 为 $i$ 前面离 $i$ 最近的点的位置，使得这个数的第 $j$ 位是 $1$ 且这个数能转移到点 $i$

询问的时候，我们枚举 $x$ 的每一个为 $1$ 的第 $j$ 位，若 $f_{y,j}\ge x$，则可达，否则不可达

```cpp
const int N = 300010;
int n,q;
bool c[N][22];
int g[N][22],f[N][22];
int main()
{
	n = read(),q = read();
	for(int i = 1;i <= n;i++)
	{
		int x = read();
		for(int j = 1;j <= 20;j++)
			c[i][j] = (x & 1),x >>= 1;
	}
	for(int j = 1;j <= 20;j++)
		for(int i = 1;i <= n;i++)
			if(c[i - 1][j]) g[i][j] = i - 1;
			else g[i][j] = g[i - 1][j];
	for(int i = 1;i <= n;i++)
		for(int j = 1;j <= 20;j++)
			for(int k = 1;k <= 20;k++) if(c[i][k])
			{
				int pre = g[i][k];
				f[i][j] = max(f[i][j],f[pre][j]);
				if(c[pre][j]) f[i][j] = max(f[i][j],pre);
			}
	while(q--)
	{
		int x = read(),y = read();
		bool fl = 0;
		for(int i = 1;i <= 20;i++) if(c[x][i] && f[y][i] >= x) fl = 1;
		puts(fl ? "Shi" : "Fou");
	}
	return 0;
}
```

---

## 作者：Ynoi (赞：3)

既然是有and操作，肯定要按位考虑

定义 $g_{i,j}$为小于等于$i$中最大的数，且$a_{g_{i,j}}$二进制第$j$位是1。

然后贪心可得每次可以这么操作 若$p_k = i$则$p_{k-1} = g_{i,j}$

下一步，dp处理 $f_{i,j}$为$i$前面离$i$最近的点的编号使得这个点二进制第j位是1且这个点能够到达点i

最后是统计

对于询问l,r

对于每一个l的为1的二进制(设为第j位)，如果$f_{r,j} >= l$

则可以走 l -> $f_{r,j}$ -> r,则可达

如果每一位都不符，则不可达

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 300005
int n,m;
int f[MAXN][22];
int g[MAXN][22];
bool c[MAXN][22];

void suan(int k,int x) {
	for(int i = 1; i <= 20; i ++) {
		if(x&1) c[k][i] = 1;
		x >>= 1;
	}
}

void rd()
{
	scanf("%d",&n);
	cin >> m;
	for(int i = 1; i <= n; i ++)
	{
		int x;
		scanf("%d",&x);
		suan(i,x);	
	}
}

signed main() {
	rd();
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= 20; j ++) {
			if(c[i-1][j]) g[i][j] = i-1;
			else g[i][j] = g[i-1][j];
		} 
	} 
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= 20; j ++)  
		{
			for(int k = 1; k <= 20; k ++)
			if(c[i][k]){
				int x = g[i][k];
				f[i][j] = max(f[i][j],f[x][j]);
				if(c[x][j]) f[i][j] = max(f[i][j],x);
			}
		}
	}
	while(m --)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		int ans = 0;
		for(int i = 1; i <= 20; i ++)
		if(c[l][i] && f[r][i] >= l) ans = 1;
		if(ans) printf("Shi\n");
		else printf("Fou\n");
	}
	return 0;
}
```

---

## 作者：binbin_200811 (赞：1)

# CF1168C

[题面及数据范围](https://www.luogu.com.cn/problem/CF1168C)

Ps：链接为洛谷 OJ。

发现对于每一个 $i$ 只需求经过若干次转移使转移后第 $j$ 个二进制位为 $1$ 的最近位置 $k$。

查询时，当 $k \leq y$（$y$ 第 $j$ 位为 $1$）时便可以到达。（存在路径从 $x$ 到 $k$，只需要从 $k$ 到 $y$ 走一次即可）

下文的位无特殊说明位均指二进制位。

设 $f[i][j]$ 为 $i$ 经过转移使第 $j$ 位为 $1$ 的最近点，易得有如下转移方程：
$$
f[i][j]=\min(f[i][j],f[k][j])
$$

要求 $i \leq k$ 且 $a_i\&a_k>0$。

方程需要逆序转移即从 $n$ 到 $1$ 转移。

时间复杂度 $O(n^2\log_2n)$。

考虑优化，发现 $i$ 的某一位到达的点可能有多个，但只需通过最近的一个进行转移。（最近的点已经转移到更远的点了）

可以维护一个 $\log_2n$ 的数组 $g$，$g[j]$ 表示当前第 $j$ 位相同，离 $i$ 最近的点。

每次把 $a_i$ 中位为 $1$ 的第 $j$ 的 $g[j]$ 赋为 $i$ 即可。

时间复杂度 $O(n\log^2_2n)$。

具体实现看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=3e5+5;

int n,q;
int f[maxn][30],a[maxn],top[30];//top 为维护某位最近点的数组

bool vis[maxn][30];//标记  i的第 j 位是否为 1

int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        int tmp=a[i],ct=0;
        while(tmp)
        {
            vis[i][ct]=tmp%2;
            tmp/=2;
            ct++;
        }
    }

    memset(f,0x7f,sizeof(f));
    for(int i=0;i<=20;i++) top[i]=n+1,f[n+1][i]=n+1;
    for(int i=n;i;i--)
    {
        for(int j=20;j>=0;j--)
        {
            if(!vis[i][j]) continue;
            f[i][j]=i;
            int u=top[j];
            for(int k=20;k>=0;k--) f[i][k]=min(f[i][k],f[u][k]);
            top[j]=i;
        }
    }

    while(q--)
    {
        int x,y;
        bool flg=0;
        scanf("%d%d",&x,&y);
        for(int i=0;i<=20;i++)
        {
            if(vis[y][i]&&f[x][i]<=y)
            {
                flg=1;
                break;
            }
        }
        if(flg) printf("Shi\n");
        else printf("Fou\n");
    }
}
```

---

## 作者：DengDuck (赞：1)

还是挺简单的。

一次预处理记录第 $i$ 个数前面离其最近的第 $j$ 位为 $1$ 的数字的位置 $f_{i,j}$，这个是很好维护的，同时需要维护上一个。

对于 $A_i$ 的第 $j$ 位为 $1$ 的情况，显然有 $f_{i,j}=i$。

但是对于第 $j$ 位为 $0$ 的情况，我们显然要走多步，我们注意到走所有能走到的点，都可以由 $A_i$ 所有为 $1$ 的位 $j$ 的 $lst_{j}$ 走到，所以我们用所有的 $lst_j$ 尝试更新 $f_{i,j}$。

之后就可以 $\mathcal O(\log n)$ 解决询问了，枚举 $x\to y$ 的途径，如果存在 $x\leq f_{y,i}$ 且 $x$ 的第 $i$ 位为 $1$，那么就说明有解。

时间复杂度为 $\mathcal O(n\log^2n)$，可以进一步优化。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=3e5+5;
const LL M=20;
LL n,q,x,y,a[N],lst[M+5],f[N][M+5];
int main()
{
	scanf("%lld%lld",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		for(int j=0;j<=M;j++)
		{
			if((a[i]>>j)&1)
			{
				if(lst[j])for(int k=0;k<=M;k++)f[i][k]=max(f[i][k],f[lst[j]][k]);						
				f[i][j]=i,lst[j]=i;
			}
		}
	}
	while(q--)
	{
		scanf("%lld%lld",&x,&y);
		LL pd=0;
		for(int i=0;i<=M;i++)
		{
			if((a[x]>>i)&1)
			{
				if(f[y][i]>=x)
				{
					pd=1;
					break;
				}
			}
		}
		if(pd)puts("Shi");
		else puts("Fou");
	}
}
```

---

## 作者：jamesharden666 (赞：1)

考虑从 $y$ 跳到 $x$，可能会有多个中转站使 $x$ 到达 $y$，但肯定是取最右边的那个，因为这样可以让更多的 $x$ 可行。

所以设 $f_{i,j}$ 代表能到达 $i$ 且离 $i$ 最近，第 $j$ 位为 $1$ 的点。

$lst_j$ 代表最近的第 $j$ 位为 $1$ 的点。

每次读入 $a_i$ 时，都更新一下 $f$ 和 $lst$ 数组，考虑到枚举前面的 $a_i$ 会超时，

所以枚举位数 $j$。

$lst_j$ 相当于中转站，$f_{i,k}=\max(f_{i,k},f_{lst_j,k})$。

判断答案时，只要有一个位数 $i$，使得 $a_l$ 的第 $i$ 位为 $1$ 并且 $f_{r,i}\ge l$，便可以到达。

具体参考代码实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q,a[300000+10],lst[20+10],f[300000+10][20+10];
int read()
{
    int s=0,w=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
        s=s*10+(ch-'0'),ch=getchar();
    return s*w;
}
int main()
{
    n=read(),q=read();
    for(int i=1;i<=n;++i)
    {
        a[i]=read();
        for(int j=0;j<=20;++j)
            if((a[i]>>j)&1)
            {
                if(lst[j])
                    for(int k=0;k<=20;++k)
                        f[i][k]=max(f[i][k],f[lst[j]][k]);
                f[i][j]=i;
                lst[j]=i;
            }
    }
    while(q--)
    {
        int l=read(),r=read();
        bool flag=false;
        for(int i=0;i<=20;++i)
            if((a[l]>>i)&1)
                if(f[r][i]>=l)
                {
                    flag=true;
                    break;
                }
        if(flag)
            puts("Shi");
        else
            puts("Fou");
    }
    return 0;
}
```

---

## 作者：_edge_ (赞：1)

比较显然的想法，如果我们可以找到一个 $a_i$ 的位是 $1$ 同时 $a_l$ 这一位也为 $1$，并且能从 $a_r$ 跳到这个位置上，那就是可以到达。

设 $f_{i,j}$ 表示从 $i$ 这个位置，跳到第 $j$ 位为 $1$ 的最近的点，因为远的肯定没有近的贡献多。

然后我们思考如何转移，可行的转移方法是 $f_{i,j}=f_{k,j}$ 并且满足 $a_i \& a_k>0$，但是这样会 TLE，如何优化？

可以发现，我们所需要的决策点，是 $a_i$ 为 $1$ 位，并且离他最近的这一位为 $1$ 的点，这样能保证他们两个按位与起来不会是 $0$。

同时，需要知道的是这样做为什么是比较优的，考虑枚举前面的点，如果他和当前点按位与是不为 $0$，那么他一定会被另外的点转移，因为他没有哪一位比其他点有优势。

所谓的有优势，就是他在其他点后面，并且他有着自己独特的一位。

因此总时间复杂度是 $O(n \log^2 n)$。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=3e5+5;
int n,m,f[INF][25],a[INF],pre[INF];
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;for (int i=1;i<=n;i++) cin>>a[i];
	for (int i=1;i<=n;i++) {
		for (int j=0;j<20;j++) {
			for (int k=0;k<20;k++) {
				if ((a[i]>>k)&1) {
					if (f[pre[k]][j]) 
						f[i][j]=max(f[i][j],f[pre[k]][j]);
				}
			}
		}
		for (int j=0;j<20;j++) {
			if ((a[i]>>j)&1) {
				pre[j]=i;
				f[i][j]=max(f[i][j],i);
			}
		}
//		cout<<pre[1]<<" ???\n";
	} 
//	cout<<f[4][0]<<" "<<f[2][0]<<" ?\n";
	for (int i=1;i<=m;i++) {
		int l=0,r=0,fl=0;cin>>l>>r;
		for (int j=0;j<20;j++) {
			if ((a[l]>>j)&1) {
//				cout<<r<<" "<<j<<" "<<a[l]<<" "<<f[r][j]<<" ??\n";
				if (f[r][j]>=l && f[r][j]) fl=1;
			}
		}
		if (fl) cout<<"Shi\n";
		else cout<<"Fou\n";
	}
	return 0;
}
```


---

## 作者：Tastoya (赞：0)

#### 题目大意

给定一个数列 $a$，我们称 $x$ 可以到达 $y$ 当且仅当：

1. $x < y$；
2. 存在一个数组 $p$，其中 $x=p_1 < p_2 \dots < p_k = y$，并且对于任意 $1 \leq i < k$，满足 $a_{p_i} \operatorname{AND} a_{p_{i+1}} > 0$。

现给出 $q$ 组下标，输出它们是否可以到达。

#### 思路

按位与操作可以按位考虑，$x$ 可以到达 $y$ 当且仅当 $x$ 与 $y$ 在二进制下某一位同时为 $1$ 或者 $x$ 与 $y$ 可以通过一些数中转到达。

那么设 $f_{i,j}$ 表示 $1 \sim i -1$ 位置第 $j$ 位上为 $1$ 的最靠后的位置，处理出这个用于后面的转移。

设 $dp_{i,j}$ 表示第 $1 \sim i-1$ 位置第 $j$ 位上为 $1$ 且能转移到 $a_i$ 的最靠后的位置，如果需要中转站，那么可以直接以 $f_{i,j}$ 为中转站转移，否则可以直接转移。

#### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 300500;

int n,q;

int a[N];

int f[N][20],dp[N][20];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> q;
	for(int i = 1;i <= n; i++) {
        cin >> a[i];

        for(int j = 0;j < 20; j++) {
            if((a[i - 1] >> j) & 1)
                f[i][j] = i - 1;
            else
                f[i][j] = f[i - 1][j];
        }
    }

    for(int i = 1;i <= n; i++) {
        for(int j = 0;j < 20; j++) {
            for(int k = 0;k < 20; k++) {
                if(!((a[i] >> k) & 1)) 
                    continue;

                dp[i][j] = max(dp[i][j],dp[f[i][k]][j]);

                if((a[f[i][k]] >> j) & 1)
                    dp[i][j] = max(dp[i][j],f[i][k]);
            }
        }
    }

	for(int i = 1,x,y;i <= q; i++) {
		cin >> x >> y;

        bool flag = 0;

        for(int j = 0;j < 20; j++) {
            if(((a[x] >> j) & 1) && dp[y][j] >= x) {
                flag = 1;
                break;
            }
        }

		if(flag)
			cout << "Shi\n";
		else
			cout << "Fou\n";
	}
	return 0;
}
```

---

## 作者：CyberPrisoner (赞：0)

~~考试时做的，但是当时思路假飞了。~~

看到这个题我第一反应是建图，对于所有 $i<j$，$a_i\land a_j>0$，我们就建一条从 $i$ 到 $j$ 的边。最后会建出来一个 DAG，那么问题就转化成一个 DAG 上一个点能不能到另一个点，然而这个操作单次时间复杂度是 $O(n)$，然后就~~破防了~~换了个做法。

对于每对 $x,y$，我们可以枚举 $a_y$ 在二进制下哪些位是 $1$ ，然后看一组合法的 $p$ 中 $x$ 后续中第一次出现这一位是哪个位置，比较它与 $y$ 的大小。
具体的，我们令 $f_{i,j}$ 表示 $i$ 位置的后续（包括自己）第一次出现第 $j$ 位是在哪。然后就有转移式 
$$f_{i,j}=\min(f_{pos_k,j},f_{i,j})$$ 
其中 $pos_k$ 代表下一个第 $ k $ 位出现在哪里。

 _code_ 
 ```
#include<bits/stdc++.h>
using namespace std;
const int N=3e5+1000;
int n,a[N];
int f[N][30],q;
int pos[30],b[N][30];
int main(){
//	freopen("and.in","r",stdin);
//	freopen("and.out","w",stdout);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		for(int j=1;j<=30;j++){
			if(((1<<(j-1))&a[i])){
				b[i][j]=1;
				f[i][j]=i;
			}else f[i][j]=n+1;
			
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=1;j<=30;j++){
			if(!b[i][j])continue;
			if(pos[j]){
				for(int k=1;k<=30;k++){//找没有的  
					f[i][k]=min(f[i][k],f[pos[j]][k]);
				}
			}
			pos[j]=i;
		}
	}
	for(int i=1,x,y;i<=q;i++){
		cin>>x>>y;
		bool flag=0;
		for(int j=1;j<=30;j++){
			if(b[y][j]&&y>=f[x][j])flag=1; 
		}
		if(flag==1)cout<<"Shi"<<endl;
		else cout<<"Fou"<<endl;
	}
	//if(system("fc and.ans and.out")==1)cout<<"WA"<<endl;
}

```


---

