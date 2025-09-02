# Hyperspace Jump (hard)

## 题目描述

现在已经是 $125$ 年过后了，但人类仍在逃离一个企图灭绝人类的机器人种族。或许我们在这里混淆了一些故事...无论如何，舰队在现在的规模更小了。然而，在最近的升级中，所有的导航系统都配备了高维线性代数跳跃处理器。

现在，为了进行迁跃，船长需要指定一个 $d$ 维空间的子空间，其中正在发生事情。她通过提供该子空间的向量生成集来实现这一点。

公主 Heidi 从 $m$ 艘船的船长那里收到了这样的一组信息。同样，她想将那些超空间迁跃子空间相等的船只分为同一组。为此，她想给每艘船分配一个 $1$ 到 $m$ 之间的组号。对于两艘船，当且仅当它们对应的子空间相等时，两艘船具有相同的组号（即使它们可能使用不同的向量集给出）。

帮帮 Heidi！

### **简明题意**

对 $m$ 艘船每艘给出一个 $d$ 维向量集，请将目的地相同的船分在同一组。

## 样例 #1

### 输入

```
8 2
1
5 0
1
0 1
1
0 1
2
0 6
0 1
2
0 1
1 0
2
-5 -5
4 3
2
1 1
0 1
2
1 0
1 0
```

### 输出

```
1 2 2 2 3 3 3 1 ```

# 题解

## 作者：DiDi123 (赞：0)

# 一、题意

给你 $m$ 个 $d$ 维的子空间，第 $i$ 个子空间包含 $k_i$ 个向量。你需要给出一个字典序最小的正整数序列 $g$，满足 $g_i=g_j$ 当且仅当第 $i$ 个子空间与第 $j$ 个子空间相等。

# 二、分析

由于**线性基**能表示出这个子空间所属线性空间内的所有的向量，所以线性基能很好的代表这个子空间。注意到我们用高斯消元法按照从高到底遍历每个维度的顺序求线性基，**两组线性基相同当且仅当两个子空间相等**。证明就考虑把每个子空间的线性空间表示出来，那么可以发现线性基包含的向量个数应该是相同的。由于高斯消元求解后会得出来一个上三角矩阵，所以个子空间等价的话必然有两个线性基中包含最高非 $0$ 维度的向量在第一行，次高非 $0$ 维度如果不在第一行的向量中必在第二行，以此类推。所以此时能发现两个线性基是相同的。

这样的话我们就每个子空间求一下线性基，然后对线性基 hash 一下，再用 map 维护是否有相同的线性基即可。

我一开始想直接用小数的高斯消元，但是精度会炸，所以最好用取模意义下的高斯消元。

时间复杂度 $\mathcal{O}(md^3+m\log m)$。

# 三、代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
#define MAXN 30010
#define base 133
#define mp make_pair
#define fi first
#define se second
typedef pair<int,int> pa;
int qp(int x,int p)
{
	int res=1;
	while(p)
	{
		if(p&1) res=res*x%mod;
		x=x*x%mod;
		p>>=1;
	}
	return res;
}
int inv(int x)
{
	return qp(x,mod-2);
}
int m,d,ss[MAXN],cnt;
struct node
{
	int n,k=1,a[6][6];
	pa h;
	void gs() //高斯消元
	{
		for(int i=d;i>=1;i--)
		{
			for(int j=k;j<=n;j++)
				if(abs(a[j][i])>abs(a[k][i]))
				{
					swap(a[j],a[k]);
					break;
				}
			if(!a[k][i]) continue;
			int tp=inv(a[k][i]);
			for(int j=1;j<=d;j++) a[k][j]=a[k][j]*tp%mod;
			for(int j=1;j<=n;j++)
				if(j!=k && a[j][i])
					for(int p=1;p<=d;p++)
						a[j][p]=(a[j][p]-a[j][i]*a[k][p]%mod+mod)%mod;
			k++;		
			if(k>n) break;			
		}
		k--;
	}
	int hs1() //用双哈希可能精度更高？
	{
		int tp=0;
		for(int i=1;i<=k;i++)
			for(int j=1;j<=d;j++)
				tp=(tp*base+a[i][j])%mod;
		return tp;
	}
	int hs2()
	{
		int tp=1;
		for(int i=1;i<=k;i++)
			for(int j=1;j<=d;j++)
				if(a[i][j]) tp=tp*a[i][j]%mod;
		return tp;
	}
}t[MAXN];
map <pa,int> st;
signed main()
{
	cin>>m>>d;
	for(int i=1;i<=m;i++)
	{
		cin>>t[i].n;
		for(int j=1;j<=t[i].n;j++)
			for(int k=1;k<=d;k++)
				cin>>t[i].a[j][k],t[i].a[j][k]=(t[i].a[j][k]+mod)%mod;
		t[i].gs();
		t[i].h=mp(t[i].hs1(),t[i].hs2());
	//	cout<<t[i].h.fi<<' '<<t[i].h.se<<endl;
		if(!st[t[i].h]) st[t[i].h]=++cnt;
		ss[i]=st[t[i].h];
	}
	for(int i=1;i<=m;i++)
		cout<<ss[i]<<' ';
}
```


---

