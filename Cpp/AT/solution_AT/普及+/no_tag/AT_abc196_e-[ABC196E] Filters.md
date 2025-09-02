# [ABC196E] Filters

## 题目描述

给出整数数列 $A=(a_1,a_2,...,a_n)$，$T=(t_1,t_2,...,t_n)$，$X=(x_1,x_2,...,x_q)$。

定义 $n$ 个函数 $f_1(x),f_2(x),...,f_n(x)$：
$$
f_i(x)=\begin{cases}
x+a_i& t_i=1\\
\max(x,a_i)& t_i=2\\
\min(x,a_i)& t_i=3\\
\end{cases}
$$
对于 $i=1,2,...,q$，求出 $f_n(...f_2(f_1(x_i))...)$ 的值。

## 说明/提示

对于 $100\%$ 的数据所有输入的值均为整数，$1 \leqslant n,q \leqslant 2 \times 10^5$，$1 \leqslant t_i \leqslant 3$，$|a_i|,|x_i| \leqslant 10^9$。

## 样例 #1

### 输入

```
3
-10 2
10 1
10 3
5
-15 -10 -5 0 5```

### 输出

```
0
0
5
10
10```

# 题解

## 作者：liangbowen (赞：9)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc196_e)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/17531887.html)

很有趣的题，取决于思考方向。

## 思路

如果你一开始想着从 $x$ 开始，将某些操作进行某些合并，再用某个数据结构维护，那么你做不出来。

正确的思考方向：将 $x$ 认为是一个未知数，维护一个 $[\text{L}, \text{R}]$ 的范围。

+ $t_i = 1$，$[\text{L}, \text{R}] \to [\text{L}+a_i, \text{R}+a_i]$。
+ $t_i = 2$，$[\text{L}, \text{R}] \to [\max(\text{L},a_i), \max(\text{R},a_i)]$。
+ $t_i = 3$，$[\text{L}, \text{R}] \to [\min(\text{L},a_i), \min(\text{R},a_i)]$。

对于一个 $x$，先将 $t_i=1$ 所增加偏移量补上。然后再把它限制进去 $[\text L,\text R]$ 里，即：答案为 $\max(\text{L}, \min(\text{R}, x + \text{add})$。

## 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long min(long long x, int y) {return x < y ? x : y;}
long long max(long long x, int y) {return x > y ? x : y;}
int main()
{
	int n, q; long long minx = -1e18, maxx = 1e18, add = 0;
	scanf("%d", &n);
	while (n--)
	{
		int x, op;
		scanf("%d%d", &x, &op);
		if (op == 1) minx += x, maxx += x, add += x;
		else if (op == 2) minx = max(minx, x), maxx = max(maxx, x);
		else if (op == 3) minx = min(minx, x), maxx = min(maxx, x);
	}
	scanf("%d", &q);
	while (q--)
	{
		int x; scanf("%d", &x);
		printf("%lld\n", max(minx, min(maxx, x + add)));
	}
	return 0;
}
```

希望能帮助到大家！

---

## 作者：DengDuck (赞：1)

比较有意思的离线题。

我们把询问按照值的大小排序，不难发现这个单调性会一直保存下去，然后 $\max$ 和 $\min$ 操作相当于将开头和结尾的一些询问变成一样的，那你可以把一样的询问删掉，最后用并查集找到你和什么询问是一样的。

找 $\max$ 和 $\min$ 操作的操作范围二分即可。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pLL pair<LL,LL>
#define fir first
#define sec second
using namespace std;
const LL N=2e5+5;
LL n,q,t[N],a[N],L,R,ans[N],fa[N];
pLL Q[N];
LL find(LL x)
{
	if(x==fa[x])return  x;
	return fa[x]=find(fa[x]);
}
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a[i],&t[i]);
	}
	LL k=0;
	scanf("%lld",&q);
	for(int i=1;i<=q;i++)
	{
		LL x;
		scanf("%lld",&x);
		Q[i]={x,i};
	}
	for(int i=1;i<=q;i++)fa[i]=i;
	sort(Q+1,Q+q+1);
	L=1,R=q;
	for(int i=1;i<=n;i++)
	{
		if(t[i]==1)
		{
			k+=a[i];
			continue;
		}
		a[i]-=k;
		if(t[i]==2)
		{
			if(Q[L].fir>=a[i])continue;
			int pos=upper_bound(Q+L,Q+R+1,(pLL){a[i],0ll})-Q;
			for(int j=L;j<pos;j++)
			{
				fa[Q[j].sec]=Q[pos-1].sec;
			}
			Q[pos-1].fir=a[i];
			L=pos-1;
		}
		if(t[i]==3)
		{
			if(Q[R].fir<=a[i])continue;
			int pos=lower_bound(Q+L,Q+R+1,(pLL){a[i],n})-Q;
			for(int j=pos;j<=R;j++)
			{
				fa[Q[j].sec]=Q[pos].sec;
			}
			Q[pos].fir=a[i];
			R=pos;			
		}
	}
	for(int i=1;i<=q;i++)
	{
		ans[Q[i].sec]=Q[i].fir+k;
	}
	for(int i=1;i<=q;i++)
	{
		printf("%lld\n",ans[find(i)]);
	}
}
```

---

## 作者：_GW_ (赞：0)

## 思路

1. 首先把操作一分离出来。如何分离？从 $t_1$ 遍历到 $t_n$，可以记录一个 $sum$，为当前为止操作一所加的数的总和，然后操作二，三的 $x_i$ 各减一个 $sum$，最后输出时每个答案再加一个 $sum$，就可以只考虑操作二，三了。

2. 发现对于操作二，小于 $a_i$ 的 $x_j$ 会变成 $a_i$，对于操作三，大于 $a_i$ 的 $x_j$ 会变成 $a_i$，久而久之 $x$ 的范围会越来越小。

3. 那么就考虑处理出一个答案可能在的区间，遇到操作二就把左右端点同时与 $a_i$ 取 $\max$，操作三就取 $\min$。

4. 最后，对于每个 $x_i$，若不在答案区间内，就把它放到答案区间内，别忘了加上 $sum$。

## code

```
#include <bits/stdc++.h>
using namespace std;
#define int long long//因为操作一，所以要开long long 
const int N=2e5+5;
int a[N],res[N],t[N],n,m,k,x,y,z,sum,Mi=-1e18,Ma=1e18;//初始答案区间记得赋极值 
signed main()
{
  cin>>n;
  for(int i=1;i<=n;i++) 
  {
    cin>>a[i]>>t[i];
    if(t[i]==1) 
    {
      sum+=a[i];//提取出操作一 
    }
    else if(t[i]==2)
    {
      Ma=max(Ma,a[i]-sum);
      Mi=max(Mi,a[i]-sum);//更新答案所在区间，记得减去sum 
    }
    else
    {
      Mi=min(Mi,a[i]-sum);
      Ma=min(Ma,a[i]-sum);//同上 
    }
  }
  cin>>m;
  for(int i=1;i<=m;i++)
  {
    cin>>x;
    cout<<max(Mi,min(Ma,x))+sum<<'\n';//把X弄到答案区间内并加上操作一 
  }
  return 0;
 } 
```

---

## 作者：Ryan_Adam (赞：0)

## 题解：AT_abc196_e [ABC196E] Filters
### Solution
我们发现对于单个的 $x$ 求这个函数值是 $\mathcal O(n)$ 的，复杂度显然不对。

观察式子性质，发现 $t$ 相当于操作序列，操作 $1,2,3$ 分别是进行数值的偏移，限定最小值，限定最大值。那我们可以提前预处理跑出最终限定后的合法区间，再对于每个 $x_i$ 都把所有的偏移量加上，在合法区间内就是它本身，否则就是取左端点或右端点。
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5;
const int INF=0x7fffffff;
int t[N],a[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    int l=-INF,r=INF;
    int sumt=0;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i]>>t[i];
        if(t[i]==1)l+=a[i],r+=a[i],sumt+=a[i];
        else if(t[i]==2)l=max(l,a[i]),r=max(r,a[i]);
        else if(t[i]==3)r=min(r,a[i]),l=min(l,a[i]);
    }
    // cout<<l<<" "<<r<<" "<<sumt<<endl;
    int q;
    cin>>q;
    while(q--)
    {
        int x;
        cin>>x;
        x+=sumt;
        cout<<max(l,min(r,x))<<endl;
    }
    
    return 0;
}

```

---

## 作者：expecto__patronum (赞：0)

## 思路：
图象是分段函数，自变量从负无穷到 $x=a[i]$ 时图象是一三象限角平分线的一部分，其余部分函数值等于 $a[i]$。

然后我们发现经过这些函数的加工后它有最小值（下界）和最大值（上界），遇到 $t[i]=1$ 时，下界和上界都加上 $a[i]$，并记录$t[i]=1$ 时 $a[i]$ 的和。

遇到 $t[i]=2$ 或 $t[i]=3$ 时，下界和上界都分别 $min/max$ 上这个值。（里层 $min$，$max$ 函数的值域作外层函数的定义域，这个可以自己画图模拟一下过程)
## Code:
```
#include<bits/stdc++.h>
#define re register 
#define N 200010
#define int long long
#define inf 2e18
using namespace std;
int n,tmp,l,h,q;
int a[N],t[N];
template <class T> inline void read(T &x)
{
	x=0;int g=1;char ss=getchar();
	for (;ss>'9'||ss<'0';ss=getchar()) if (ss=='-') g=-1;
	for (;ss<='9'&&ss>='0';ss=getchar()) x=(x<<1)+(x<<3)+(ss^48);	
	x*=g;
}
inline int doit(int x)
{
	if (x<l) return l;if (x>h) return h;return x;
}
signed main()
{
	re int i,j,op,x;
	read(n);
	for (i=1;i<=n;i++)
		read(a[i]),read(t[i]);
	l=-inf,h=inf;
	for (i=1;i<=n;i++)
	{
		if (t[i]==1)	tmp+=a[i],l+=a[i],h+=a[i];
		else if (t[i]==2) l=max(l,a[i]),h=max(h,a[i]);
		else l=min(l,a[i]),h=min(h,a[i]);
	}
	read(q);
	while(q--)
	{
		read(x);
		printf("%lld\n",doit(x+tmp));
	}
	return 0;
}
```
[更好阅读体验](https://www.cnblogs.com/Ritalc/p/14574950.html)

---

