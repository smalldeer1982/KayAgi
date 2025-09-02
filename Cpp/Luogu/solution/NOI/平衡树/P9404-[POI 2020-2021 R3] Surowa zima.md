# [POI 2020/2021 R3] Surowa zima

## 题目背景

译自 [XXVIII Olimpiada Informatyczna - III etap](https://sio2.mimuw.edu.pl/c/oi28-3/dashboard/) [Surowa zima](https://szkopul.edu.pl/problemset/problem/QCCQf92wAoWAOoJ3tHoypvp3/statement/)。

d1t3。

## 题目描述

有一条长 $l$ 米的道路（数轴）。路上有 $n$ 个充电站。每天整条路上（坐标 $[0,l]$）都会落满雪。

有一台机器能扫雪。充一次电可以扫至多 $k$ 米的雪。扫雪是和移动同时进行的，详见样例解释。机器一秒能移动一米，充电不消耗时间。

简单来说，**移动不扫雪不消耗电，需要一秒；移动并扫雪消耗最大电量的 $\bold{\frac1k}$，需要一秒；扫雪必须移动。**

给出每天机器的初始位置，机器初始没电，问每天清除所有雪的最少时间。终点任意。

带修，即充电站可能损坏或修好（第一天之前都是好的），但保证每天都至少有一个好的充电站（所以不会无解）。

## 说明/提示

样例解释：$3\rightarrow2_{充电}\Rightarrow0\rightarrow2_{充电}\Rightarrow4\rightarrow5_{充电}\Rightarrow4$。$\rightarrow$ 表示移动，$\Rightarrow$ 表示移动并扫雪。

对于所有数据，$1\leq n\leq 250000$，$1\leq l\leq 10^9$，$1\leq k\leq l$，$1\leq d\leq 250000$，$\sum z,\sum u\leq 500000$。

| 子任务编号 | 附加限制 | 分数 |
| :----------: | :----------: | :----------: |
| 1 | $l\leq 12$，$d\leq 50$ | 10 |
| 2 | $l\leq 500$，$d\leq 50$，$k=1$ | 12 |
| 3 | $l\leq 5000000$，$d\leq 20$ | 8 |
| 4 | $z=u=0$ | 8 |
| 5 | $z,u\leq 100$，$k\leq 50$ | 20 |
| 6 | $k=1$ | 18 |
| 7 |  | 24 |


## 样例 #1

### 输入

```
3 5 2 1
2 3 5
0 1 3

2
```

### 输出

```
9
```

## 样例 #2

### 输入

```
5 12 1 5
1 3 6 9 11
0 1 1

1
1 1 3
1
2
1 1 6
2
3
1 1 9
3
4
1 1 11
4
5
```

### 输出

```
33
33
36
33
33
```

## 样例 #3

### 输入

```
11 100 1 26
0 10 20 30 40 50 60 70 80 90 100
0 5 0

2 4 6 8 10
5 6 4
2 4 6 8 10
1 3 5 7 9 11
6 5 8
1 3 5 7 9 11
2 4 6 8 10
5 6 12
2 4 6 8 10
1 3 5 7 9 11
6 5 16
1 3 5 7 9 11
2 4 6 8 10
5 6 20
2 4 6 8 10
1 3 5 7 9 11
6 5 24
1 3 5 7 9 11
2 4 6 8 10
5 6 28
2 4 6 8 10
1 3 5 7 9 11
6 5 32
1 3 5 7 9 11
2 4 6 8 10
5 6 36
2 4 6 8 10
1 3 5 7 9 11
6 5 40
1 3 5 7 9 11
2 4 6 8 10
5 6 44
2 4 6 8 10
1 3 5 7 9 11
6 5 48
1 3 5 7 9 11
2 4 6 8 10
5 6 52
2 4 6 8 10
1 3 5 7 9 11
6 5 56
1 3 5 7 9 11
2 4 6 8 10
5 6 60
2 4 6 8 10
1 3 5 7 9 11
6 5 64
1 3 5 7 9 11
2 4 6 8 10
5 6 68
2 4 6 8 10
1 3 5 7 9 11
6 5 72
1 3 5 7 9 11
2 4 6 8 10
5 6 76
2 4 6 8 10
1 3 5 7 9 11
6 5 80
1 3 5 7 9 11
2 4 6 8 10
5 6 84
2 4 6 8 10
1 3 5 7 9 11
6 5 88
1 3 5 7 9 11
2 4 6 8 10
5 6 92
2 4 6 8 10
1 3 5 7 9 11
6 5 96
1 3 5 7 9 11
2 4 6 8 10
5 6 100
2 4 6 8 10
1 3 5 7 9 11
```

### 输出

```
1090
1096
1098
1092
1094
1100
1094
1092
1098
1096
1090
1096
1098
1092
1094
1100
1094
1092
1098
1096
1090
1096
1098
1092
1094
1100
```

## 样例 #4

### 输入

```
见附件```

### 输出

```
见附件```

## 样例 #5

### 输入

```
见附件```

### 输出

```
1000000000000000000
2001007996000
```

# 题解

## 作者：_•́へ•́╬_ (赞：17)

青蛙。毒瘤。赛时最高 12 分。

吐槽：前两个包数据好水。调试可以试试这些数据：

```plain
2 9 2 1
0 9
0 0 0
```

`25`

```plain
3 22 2 1
1 10 21
0 0 1
```

`69`

```plain
5 12 1 1
0 5 7 9 11
0 0 1
```

`30`

## 思路

我们首先介绍一下 30 分的做法。

考虑路径大概长啥样。

第一步是从出发点走到第一个充电站。

第二步是走到某一个端点。

第三步是走到另一个端点。

第四步是往回走一点点。也可能不往回走，这一步可能不存在。

详细分析一下：

第一步可能走到左边第一个，也可能走到右边第一个。第二步也有两个方向。所以是有四种情况的。

下文默认是向左走（与样例的方向一致）。下文称第一个充电站为出发点，称相邻两个充电站之间为段。

在出发点左侧的段：

要走过去再走回来，就顺带搞掉了 $2k$ 的长度。这 $2k$ 应当安排在中央。两边的就来回走。

在出发点右侧的段：

直接走过去，不回来，就顺带搞掉了 $k$ 的长度。这 $k$ 就安排在中央。两边来回走，跟上面一样。

往回走一点点时经过的段（这些段一定是所有段的一个后缀，且都在出发点右侧）：

考虑把这些段的贡献记做新贡献减原贡献，就能直接与上面的和相加了。

新贡献计算方法与出发点左侧的段完全一样。

往回走一点点的终点：

终点会在一段的中间。处理一下即可。

- `e0` 为走到端点并停在端点的代价，适用最右段。
- `e1` 为走到端点再走回来的代价，适用最左段。
- `m0` 为走完一段并走到另一端的代价，适用出发点右侧的段。
- `m1` 为走完一段并回到原端的代价，适用出发点左侧的段。
- `m2` 为走完一段并停在中间某处的代价，适用第四步的终点段。

## code

```cpp
#include<stdio.h>
#include<algorithm>
#include<vector>
#define N 250009
#define int long long
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,l,k,d,a[N];bool down[N];
inline int e0(int x)
{
	int ans=-x;
	for(int o=(x%k?x%k:k);x>0;x-=k)ans+=o<<1,o+=k;
	return ans;
}
inline int e1(int x)
{
	int ans=0;
	for(int o=(x%k?x%k:k);x>0;x-=k)ans+=o<<1,o+=k;
	return ans;
}
inline int m0(int x)
{
	int ans=x;x-=k;
	for(int o=(x%k?x%k:k),oo=k;x>0;x-=k)
		if(o<oo)ans+=o<<1,o+=k;
		else ans+=oo<<1,oo+=k;
	return ans;
}
inline int m1(int x)
{
	int ans=x<<1;x-=k+k;
	for(int o=(x%k?x%k:k),oo=k;x>0;x-=k)
		if(o<oo)ans+=o<<1,o+=k;
		else ans+=oo<<1,oo+=k;
	return ans;
}
inline int m2(int x)
{
	if(x<=k)return x;
	if(x<=k<<1)return x+x-k;
	int ans=x;x-=k+k;
	for(int o=(x%k?x%k:k),oo=k;x>0?1:(ans+=min(o,oo),0);x-=k)
		if(o<oo)ans+=o<<1,o+=k;
		else ans+=oo<<1,oo+=k;
	return ans;
}
inline int lft(const int&x)
{
	int ans=0;
	for(int i=x,j;;i=j)
	{
		for(j=i-1;j>=0&&down[j];--j);
		if(j>>63){ans+=e1(a[i]);break;}
		ans+=m1(a[i]-a[j]);
	}
	vector<int>b,c;
	for(int i=x,j;;i=j)
	{
		for(j=i+1;j<n&&down[j];++j);
		if(j==n)
		{
			ans+=e0(l-a[i]);
			b.emplace_back(e1(l-a[i])-e0(l-a[i]));c.emplace_back(0);
			break;
		}
		ans+=m0(a[j]-a[i]);
		b.emplace_back(m1(a[j]-a[i])-m0(a[j]-a[i]));
		c.emplace_back(m2(a[j]-a[i])-m0(a[j]-a[i]));
	}
	int bns=0;
	for(int i=b.size()-1,s=0;i>=0;--i)
		bns=min(bns,s+c[i]),s+=b[i];
	return ans+bns;
}
inline int rgt(const int&x)
{
	int ans=0;
	for(int i=x,j;;i=j)
	{
		for(j=i+1;j<n&&down[j];++j);
		if(j==n){ans+=e1(l-a[i]);break;}
		ans+=m1(a[j]-a[i]);
	}
	vector<int>b,c;
	for(int i=x,j;;i=j)
	{
		for(j=i-1;j>=0&&down[j];--j);
		if(j>>63)
		{
			ans+=e0(a[i]);
			b.emplace_back(e1(a[i])-e0(a[i]));c.emplace_back(0);
			break;
		}
		ans+=m0(a[i]-a[j]);
		b.emplace_back(m1(a[i]-a[j])-m0(a[i]-a[j]));
		c.emplace_back(m2(a[i]-a[j])-m0(a[i]-a[j]));
	}
	int bns=0;
	for(int i=b.size()-1,s=0;i>=0;--i)
		bns=min(bns,s+c[i]),s+=b[i];
	return ans+bns;
}
main()
{
	read(n);read(l);read(k);read(d);
	for(int i=0;i<n;read(a[i++]));
	for(int z,u,p;d--;)
	{
		read(z);read(u);read(p);
		for(int x;z--;read(x),down[--x]=0);
		for(int x;u--;read(x),down[--x]=1);
		z=1ll<<60;u=lower_bound(a,a+n,p)-a;
		for(;u<n&&down[u];++u);
		if(u<n)z=min(z,a[u]-p+min(lft(u),rgt(u)));
		for(--u;u>=0&&down[u];--u);
		if(u>=0)z=min(z,p-a[u]+min(lft(u),rgt(u)));
		printf("%lld\n",z);
	}
}
```

## 思路

~~上面那个代码是依托答辩。但是可以吊打（波兰的）国家队。~~

容易发现 `e0`、`e1`、`m0`、`m1`、`m2` 都是可以 $\mathcal O(1)$ 计算的。

容易发现统计到达反方向的端点之前的答案是直接加和的形式，而统计往回走一点点对答案的贡献差是后缀和最小值的形式。

直接上数据结构维护即可。可以使用线段树。时限很够平衡树也行，但是难写一点。封装一下会舒服很多。

## code

```cpp
#include<stdio.h>
#include<set>
#define N 250009
#define ll long long
#define lc ((i)<<1|1)
#define rc ((i)+1<<1)
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
int n,l,k,q,a[N];set<int>qwq;
inline ll e1(int x){return(x%k+x)*(x/k+1ll);}
inline ll e0(int x){return e1(x)-x;}
inline ll m_(int x)
{
	ll l1=x%k?x%k:k,cnt1=(x-1)/k+1+1>>1,l2=k,cnt2=(x-1)/k+1>>1;
	return(l1+l1+(cnt1-1)*k)*cnt1+(l2+l2+(cnt2-1)*k)*cnt2;
}
inline ll m0(int x){return x<=k?x:m_(x-k)+x;}
inline ll m1(int x){return x<=k+k?x+x:m_(x-k-k)+x+x;}
inline ll m2(int x)
{
	if(x<=k)return x;
	if(x<=k<<1)return x+x-k;
	x-=k<<1;ll l1=x%k?x%k:k,cnt1=(x-1)/k+1+1>>1,l2=k,cnt2=(x-1)/k+1>>1;
	return(l1+l1+(cnt1-1)*k)*cnt1+(l2+l2+(cnt2-1)*k)*cnt2+(x+k+k)+
		min(l1+cnt1*k,l2+cnt2*k);
}
inline ll d(int x){return e1(x)-e0(x);}
struct _
{
	ll s0,s1,pfx,pfxmn,sfx,sfxmn;
	inline _ operator+(const _&kkk)const
	{
		return(_){s0+kkk.s0,s1+kkk.s1,pfx+kkk.pfx,min(pfxmn,pfx+kkk.pfxmn)
			,sfx+kkk.sfx,min(kkk.sfxmn,kkk.sfx+sfxmn)};
	}
}tre[524288];
inline _ g(const int&x)
	{ll u=m0(x),v=m1(x),w=m2(x);return(_){u,v,v-u,w-u,v-u,w-u};}
inline void upd(int i,int l,int r,int p,int x)
{
	if(l==r){tre[i]=g(x);return;}
	int mid=l+r>>1;
	if(p<=mid)upd(lc,l,mid,p,x);
	else upd(rc,mid+1,r,p,x);
	tre[i]=tre[lc]+tre[rc];
}
inline pair<_,_>operator+(const pair<_,_>&x,const _&y)
	{return{x.first,x.second+y};}
inline pair<_,_>operator+(const _&x,const pair<_,_>&y)
	{return{x+y.first,y.second};}
inline pair<_,_>qry(int i,int l,int r,int p)
{
	if(l==r)return{_(),tre[i]};
	int mid=l+r>>1;
	if(p<=mid)return qry(lc,l,mid,p)+tre[rc];
	else return tre[lc]+qry(rc,mid+1,r,p);
}
inline ll qry(const int&x)
{
	if(qwq.size()==1)return min(e1(x)+min(e0(l-x),e1(l-x)),
		e1(l-x)+min(e0(x),e1(x)));
	pair<_,_>tmp=qry(0,0,n-1,lower_bound(a,a+n,x)-a);
	_ lft=tmp.first,rgt=tmp.second;
	return min(e1(*qwq.begin())+e0(l-*--qwq.end())+lft.s1+rgt.s0+
		min(0ll,rgt.sfxmn+d(l-*--qwq.end())),
		e1(l-*--qwq.end())+e0(*qwq.begin())+rgt.s1+lft.s0+
		min(0ll,lft.pfxmn+d(*qwq.begin())));
}
main()
{
	read(n);read(l);read(k);read(q);
	for(int i=0;i<n;read(a[i]),qwq.emplace(a[i++]));
	for(int i=0;i<n-1;++i)upd(0,0,n-1,i,a[i+1]-a[i]);
	for(int z,u,p;q--;)
	{
		read(z);read(u);read(p);
		for(int x,pos;z--;qwq.emplace(x))
		{
			read(x);pos=--x;x=a[x];
			if(x<*qwq.begin()){upd(0,0,n-1,pos,*qwq.begin()-x);continue;}
			if(x>*--qwq.end())
			{
				upd(0,0,n-1,lower_bound(a,a+n,*--qwq.end())-a,
					x-*--qwq.end());continue;
			}
			set<int>::iterator y=qwq.lower_bound(x),z=y;--y;
			upd(0,0,n-1,lower_bound(a,a+n,*y)-a,x-*y);
			upd(0,0,n-1,pos,*z-x);
		}
		for(int x,pos;u--;qwq.erase(x))
		{
			read(x);pos=--x;x=a[x];
			set<int>::iterator y=qwq.lower_bound(x),z=y;++z;
			upd(0,0,n-1,pos,0);
			if(y==qwq.begin())continue;--y;
			if(z==qwq.end())upd(0,0,n-1,lower_bound(a,a+n,*y)-a,0);
			else upd(0,0,n-1,lower_bound(a,a+n,*y)-a,*z-*y);
		}
		ll ans=1ll<<60;set<int>::iterator it=qwq.lower_bound(p);
		if(it!=qwq.end())ans=min(ans,*it-p+qry(*it));
		if(it!=qwq.begin())--it,ans=min(ans,p-*it+qry(*it));
		printf("%lld\n",ans);
	}
}
```

---

## 作者：ningago (赞：6)



对 `_•́へ•́╬_` 题解进行亿点详细（冗长）解释 Orz。

---

由于没有电啥也干不了，所以可以默认先走到最近的一个充电桩（枚举左右），下文默认起点是充电桩。

---

考虑简单一点的情况： $n=1$ 并且唯一的充电桩坐标在 $0$ 时怎么做，令 $len=L$。

此时最少需要 $t=\left\lceil\dfrac{len}{K}\right\rceil$ 轮往返（最后一次不用返）。

显然如果电用完了就必定返，其中有 $p=\left\lfloor\dfrac{len}{K}\right\rfloor$ 次扫雪是扫了完整的 $K$ 单位，有一次是扫了 $r=len\bmod K$ 单位。现在问题是决策多出来的 $r$ 什么时候扫。画画图：

```
   K     K     K   r
|-----|-----|-----|-|
|-----|-----|-|-----|
|-|-----|-----|-----|
```

发现把 $r$ 从后往前挪的过程中，其以后的往返距离都会变短，把 $r$ 放在第一次往返是最优的。

即这个过程对于 $len$ 的答案为 $val(len)$，不难用等差数列 $O(1)$ 计算。

---

考虑简单两点的情况：$n=1$ 怎么做。由于经过充电桩时必然充电，所以左右两边是独立的，即答案为 $val(l)+val(r)+\min(l,r)$。因为其中有一段需要返回。

---

考虑简单三点的情况：$n=2$ 怎么做。此时充电桩 $x,y$ 和端点把 $L$ 分成了三段，长度为 $a,b,c$，假设起点是第一个充电桩。不妨假设先把起点左/右的雪全扫完，然后回到起点扫另一边（其它左右横跳的方案都可以等价调整为此）。考虑 $b$ 这一段上的雪：

- 如果先向左走。

假设 $b$ 只被经过一次，每一单位的雪一定属于一段“往返”，只不过“往返”可以以 $x$ 为起点或以 $y$ 为起点。

此时不难贪心看出，肯定存在一个长度为 $K$ 的区间（$b\leq K$ 的情况是平凡的），满足在其左边的雪都属于以 $x$ 起点，右边都属于以 $y$ 起点，其内部则是在从 $x$ 走到 $y$ 的过程中顺带扫掉了。

于是令该区间的左端点到 $x$ 的距离为 $d$，$len=b$，则该段的花费为：$val(d+K)+val(len-d)-K$。根据一些二次函数的小技巧不难看出 $d$ 需要尽可能地靠近中点，且根据上面的贪心，$d$ 应当是 $K$ 的倍数（让 $r$ 完全处于一边）。代价不难计算。记其为 $v_1(len)$。

总共的代价为 $val(a)+a+v_1(b)+val(c)$。

然而 $b$ 不一定只被 $x\to y$ 经过一次，这个后面再说。

- 如果先向右走。

此时 $b$ 段会被经过正反两次。不妨把所有“往返”都在第一次经过时扫掉。在 $v_1$ 中，会有 $K$ 单位雪在 $x\to y$ 时顺带扫掉，而此时也可以预留出 $K$ 单位雪等到 $y\to x$ 时扫掉。也就是说，会有长度为 $2K$ 的区间不在“往返”当中。则 $b$ 的代价为 $val(d+K)+val(len-d-K)+len$（加上 $y$ 往 $x$ 走的代价）。同样地规划 $d$ 的取值，记其最终代价为 $v_2(len)$。

总共的代价为 $v_2(b)+val(c)+c+val(a)$。

- 如果先向左走。

在刚才的分析中，默认了 $b$ 段只经过一次，而实际上可以像 $v_2$ 一样预留出 $2K$ 单位雪，最后从 $y$ 返回 $x$ 扫掉，此时代价为 $v_3(len)=\min_d\{val(d+K)+val(len-d-K)+\min(d+K,len-d-K)\}$（从 $y$ 回来时不用走到头）。

总共的代价为 $val(a)+a+v_3(b)+val(c)+c$。

不难发现 $b$ 段经过 $\geq 3$ 次都是不优或等价的。

---

考虑简单四点的情况：没有修改操作。

首先可以枚举先往左走还是往右走，这是相似的，考虑先向左走。记最左边的充电桩距 $0$ 的距离为 $t_L$，最右边的距 $L$ 的距离为 $t_R$。

对于左边，因为必然要返回，则记 $d$ 表示相邻两个充电桩的距离，代价为 $val(t_L)+t_L+\sum_{d}v_2(d)$。

而对于右边，最朴素的情况是直接使用 $v_1$，代价为 $val(t_R)+\sum_{d}v_1(d)$。

另一种情况，是找到一个 $d_*$，把 $d_*$ 设置成 $v_3$，其左边的只经过一次，为 $v_1$，其右边的经过正反两次，为 $v_2$（包括 $t_R$）。

此时代价为 $val(t_R)+t_R+\sum_{d<d_*}v_1(d)+v_3(d_*)+\sum_{d>d_*}v_2(d)$。

此时从后往前扫一遍枚举 $d_*$ 即可求出最优答案。

--- 

总而言之，代价形如：

```
                S
---|---|---|---||---|---|---|---|---|---
往返 v2  v2  v2   v1  v1  v1  v1  v1  往
```

或者：

```
                S
---|---|---|---||---|---|---|---|---|---
往返 v2  v2  v2   v1  v1  v3  v2  v2  往返
```

--- 

考虑简单五点的情况：无特殊限制。

设计 $v_3(x)'=v_3(x)-v_1(x)$，$v_2'$ 同理。现在只需要维护：区间（前缀）加、区间（后缀）查询最小值、动态插入删除。

用平衡树维护即可。复杂度 $O(n\log n)$，常数有亿点大。

```cpp
#define N 250010
int n, L, K, Q;
int val(int len) 
{
	if(len <= K) return len;
	int r = len % K, p = (len - r) / K;
	return 2 * r * (p + 1) + K * p * (p + 1) - len;
}

int e0(int len) { return val(len); }
int e1(int len) { return val(len) + len; }
int m0(int len) 
{ 
	if(len <= K) return len;
	int p = (len - len % K) / K, res = inf, mid;
	mid = (p / 2) * K    , ckmin(res, val(mid) + val(len - mid + K) - K);
	mid = (p / 2 + 1) * K, ckmin(res, val(mid) + val(len - mid + K) - K);
	return res;
}
int m1(int len)
{
	if(len <= 2 * K) return 2 * len;
	int p = (len - len % K) / K, res = inf, mid;
	mid = (p / 2) * K    , ckmin(res, val(mid) + val(len - mid) + len);
	mid = (p / 2 + 1) * K, ckmin(res, val(mid) + val(len - mid) + len);
	return res;
}
int m2(int len)
{
	if(len <= K) return len;
	if(len <= 2 * K) return 2 * len - K;
	int p = (len - len % K) / K, res = inf, mid;
	mid = (p / 2) * K    , ckmin(res, val(mid) + val(len - mid) + std::min(mid, len - mid));
	mid = (p / 2 + 1) * K, ckmin(res, val(mid) + val(len - mid) + std::min(mid, len - mid));
	return res;
}
#define ui unsigned int
ui sd = 114514;
ui rnd() { sd ^= sd << 11; sd ^= sd >> 7; sd ^= sd << 13; return sd; }
struct Tree
{
	int m1val, m0val, m2val;
	int m1sum, m0sum, m2min;
	int r, ls, rs, lazy;
	ui key;
	void push(int z) { m2min += z, m2val += z, lazy += z; }
};

struct ANS
{
char ID;
std::set <int> s;
#define sit std::set<int>::iterator
int sta[N], top = 0, pre[N];
int brute(sit t)
{
	int left = e1(*s.begin()), right = 0, ed = (L - *s.rbegin());
	for(sit it = s.begin(), nxt; it != t; it++)
	{
		nxt = next(it);
		left += m1(*nxt - *it);
	}
	top = 0;
	for(sit it = t, nxt = next(t); nxt != s.end(); it = nxt, nxt++)
		sta[++top] = (*nxt - *it);
	for(int i = 1; i <= top; i++) right += m0(sta[i]), pre[i] = right; right += e0(ed);
	for(int i = top, suf = e1(ed); i; i--)
	{
		ckmin(right, suf + m2(sta[i]) + pre[i - 1]);
		suf += m1(sta[i]);
	}
	printf("%c, p = %d [%d %d] brute\n", ID, *t, left, right);
	return left + right;
}
Tree tr[N * 6]; int idx, root;
#define lson(k) tr[k].ls
#define rson(k) tr[k].rs
int newnode(int l, int r, int v)
{
	int k = ++idx; tr[k].r = r; tr[k].key = rnd();
	tr[k].m0sum = tr[k].m0val = m0(r - l);
	tr[k].m1sum = tr[k].m1val = m1(r - l);
	tr[k].m2min = tr[k].m2val = m2(r - l) - m0(r - l) + v; tr[k].ls = tr[k].rs = tr[k].lazy = 0;
	return k;
}
void pushup(int k)
{
	tr[k].m0sum = tr[k].m0val + tr[lson(k)].m0sum + tr[rson(k)].m0sum;
	tr[k].m1sum = tr[k].m1val + tr[lson(k)].m1sum + tr[rson(k)].m1sum;
	tr[k].m2min = std::min({tr[k].m2val, tr[lson(k)].m2min, tr[rson(k)].m2min});
}
void pushdown(int k)
{
	if(tr[k].lazy)
	{
		if(lson(k)) tr[lson(k)].push(tr[k].lazy);
		if(rson(k)) tr[rson(k)].push(tr[k].lazy);
		tr[k].lazy = 0;
	}
}
void split(int k, int r, int &x, int &y)
{
	if(!k) { x = y = 0; return; }
	pushdown(k);
	if(tr[k].r <= r) { x = k; split(rson(k), r, rson(k), y); }
	else             { y = k; split(lson(k), r, x, lson(k)); }
	pushup(k);
}
int merge(int x, int y)
{
	if(!x || !y) { return x | y; }
	if(tr[x].key <= tr[y].key) { pushdown(x); rson(x) = merge(rson(x), y); pushup(x); return x; }
	else { pushdown(y); lson(y) = merge(x, lson(y)); pushup(y); return y; }
}
int t1, t2, t3;
int calc(sit it)
{
	int p = *it;
	split(root, p, t1, t2);
	int left, right, ed = (L - *s.rbegin());
	left = tr[t1].m1sum + e1(*s.begin());
	right = tr[t2].m0sum + e0(ed);
	ckmin(right, tr[t2].m0sum + tr[t2].m2min + e1(ed));
	root = merge(t1, t2);
	return left + right;
}
int Abs(int x) { return x > 0 ? x : -x; }
int solve(int z)
{
	// printf("%c solve %d\n", ID, z);
	int ans = inf, ds; sit it;
	if((it = s.lower_bound(z)) != s.begin()) it = prev(it), ds = Abs(z - *it), ckmin(ans, ds + calc(it));//, brute(it);
	if((it = s.lower_bound(z)) != s.end()) ds = Abs(z - *it), ckmin(ans, ds + calc(it));//, brute(it);
	return ans;
}
void inslr(int l, int r)
{
	split(root, r, t1, t2);
	int p = newnode(l, r, tr[t2].m1sum - tr[t2].m0sum);
	if(t1) tr[t1].push(tr[p].m1sum - tr[p].m0sum);
	root = merge(merge(t1, p), t2);
}
void dellr(int l, int r)
{
	split(root, r, t1, t3);
	split(t1, r - 1, t1, t2);
	if(t1) tr[t1].push(-(tr[t2].m1sum - tr[t2].m0sum));
	root = merge(t1, t3);
}
void ins(int z)
{
	sit it = s.insert(z).fi;
	if(s.size() != 1)
	{
		if(next(it) == s.end()) { int p = *prev(it); inslr(p, z); }
		else if(it == s.begin()) { int p = *next(it); inslr(z, p); }
		else
		{
			int lst = *prev(it), nxt = *next(it);
			dellr(lst, nxt); inslr(lst, z); inslr(z, nxt);
		}
	}
}
void del(int z)
{
	sit it = s.lower_bound(z);
	if(s.size() != 1)
	{
		if(next(it) == s.end()) { int p = *prev(it); dellr(p, z); }
		else if(it == s.begin()) { int p = *next(it); dellr(z, p); }
		else
		{
			int lst = *prev(it), nxt = *next(it);
			dellr(lst, z); dellr(z, nxt);
			inslr(lst, nxt);
		}
	}
	s.erase(z);
}
void init(char c)
{
	ID = c;
	tr[0].m2min = inf;
}
}A, B;
void ins(int z) { A.ins(z); B.ins(L - z); }
void del(int z) { A.del(z); B.del(L - z); }
int id[N];

void solve()
{
	A.init('A'); B.init('B'); n = read(), L = read(), K = read(), Q = read();
	for(int i = 1; i <= n; i++) ins(id[i] = read());
	for(int i = 1, x, y, z; i <= Q; i++)
	{
		x = read(); y = read(); z = read();
		for(int j = 1; j <= x; j++) ins(id[read()]);
		for(int j = 1; j <= y; j++) del(id[read()]);
		int ans = std::min(A.solve(z), B.solve(L - z));
		print(ans, '\n');
	}
}
```

---

