# [ARC053C] 魔法使い高橋君

## 题目描述

高桥君会 $N$ 个魔法。将这些魔法分别编号为 $1$ 到 $N$ 。

开始时，气温为 $0$ 度。高桥君咏唱第 $i$ 个魔法后，气温会先上升 $a_i$ 度再下降 $b_i$ 度。

高桥君会将所有魔法都咏唱一遍。这期间气温的最大值为 $X$ 度。高桥君可以自己决定咏唱魔法的顺序，来使 $X$ 的值尽量小。

求最小的 $X$ 值。

## 说明/提示

- $1 \le N \le 10^5$
- $a_i,b_i$ 都是整数。
- $1 \le a_i,b_i \le 10^9$

# 题解

## 作者：CN_how (赞：1)

把魔法分为三类，第一类是放完会降温的，第二类放完温度不变，第三类放完温度上升

感性理解一下，应该先放完第一类，再放第二类，再放第三类。

内部怎么排序呢，第一类按放魔法过程中的温度上升值（即ai）升序排列，第二类随意，第三类按放魔法后下降值（即bi）降序排列

（感性理解一下或者对照样例画图理解更佳）

排完序后模拟一下。。代码看看咯，cmp函数是核心。
# 注意开long long！！我就直接define了

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define maxn 100050
#define int ll
inline int read()
{
	int x = 0,f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-')f = -1;ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}
struct type{
	int x,y,i;
}l[maxn];
ll maxx(ll a,ll b){return a > b ? a : b;}
bool cmp(type a,type b)
{
	if(a.i != b.i)return a.i < b.i;
	if(a.i == 1)return a.x < b.x;
	if(a.i == 3)return a.y > b.y;
	if(a.i == 2)return a.x < b.x;
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	int n = read();
	for(int i = 1;i <= n;i++)
	{
		l[i].x = read();
		l[i].y = read();
		if(l[i].x < l[i].y)l[i].i = 1;
		else if(l[i].x > l[i].y)l[i].i = 3;
		else				l[i].i = 2;
	}
	sort(l + 1,l + n + 1,cmp);
	ll ans = -10000,t = 0;
	for(int i = 1;i <= n;++i)
	{
		t += l[i].x;
		ans = maxx(ans,t);
		t -= l[i].y;
		ans = maxx(ans,t);
	}
	cout << ans;
	return 0;
}

```


---

