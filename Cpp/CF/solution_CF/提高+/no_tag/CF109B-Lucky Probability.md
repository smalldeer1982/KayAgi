# Lucky Probability

## 题目描述

Petya 喜欢幸运数。众所周知，幸运数是指其十进制表示中只包含幸运数字 $4$ 和 $7$ 的正整数。例如，$47$、$744$、$4$ 是幸运数，而 $5$、$17$、$467$ 不是。

Petya 和他的朋友 Vasya 玩一个有趣的游戏。Petya 从区间 $[p_{l}, p_{r}]$ 中随机选择一个整数 $p$，Vasya 从区间 $[v_{l}, v_{r}]$ 中随机选择一个整数 $v$（同样是随机选择）。两位玩家选择整数的概率均等。请你计算，区间 $[\min(v, p), \max(v, p)]$ 恰好包含 $k$ 个幸运数的概率。

## 说明/提示

设 $[a, b]$ 表示整数区间，该区间包含端点。也就是说，$[a, b] = \{x \mid a \leq x \leq b\}$。

在第一个样例中，共有 $32$ 对满足条件的 $(p, v)$：$(1,7),(1,8),(1,9),(1,10),(2,7),(2,8),(2,9),(2,10),(3,7),(3,8),(3,9),(3,10),(4,7),(4,8),(4,9),(4,10),(7,1),(7,2),(7,3),(7,4),(8,1),(8,2),(8,3),(8,4),(9,1),(9,2),(9,3),(9,4),(10,1),(10,2),(10,3),(10,4)$。所有可能的 $(p, v)$ 对共有 $10 \cdot 10 = 100$ 种，因此答案为 $32/100$。

在第二个样例中，Petya 总是选到比 Vasya 小的数，且唯一的幸运数 $7$ 总是在这两个数之间，因此总是恰好有 $1$ 个幸运数。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
1 10 1 10 2
```

### 输出

```
0.320000000000
```

## 样例 #2

### 输入

```
5 6 8 10 1
```

### 输出

```
1.000000000000
```

# 题解

## 作者：fighter (赞：5)



~~写这篇题解纯粹是为了水水社区贡献~~

## 题意

直接上[传送门](https://www.luogu.org/problemnew/show/CF109B)

## 分析

我们发现虽然题目中给的区间范围很大，但是实际上所包含的“幸运数”并不多，于是我们可以考虑枚举相邻的$k$个幸运数，并累计恰好包含这$k$个数的区间总数。最后用符合条件的区间数除以总区间数，就是要求的概率。

思路就是那么简单，但细节却比较复杂。首先假设我们枚举的$k$个数的左右端点编号为$i,j$，用$num[i]$表示第$i$个幸运数，那么有以下一些注意点:

首先符合条件的区间左端点所在区间为$[num[i-1]+1,num[i]] \cap [pl, pr]$，同理右端点范围为$[num[j], num[j+1]-1] \cap [vl, vr]$，同时也需要把$pl,pr$和$vl,vr$交换统计答案。用代码表示就是

```cpp
		ans += calc(num[i-1]+1, num[i], pl, pr)*calc(num[j], num[j+1]-1, vl, vr);
		ans += calc(num[j], num[j+1]-1, pl, pr)*calc(num[i-1]+1, num[i], vl, vr);
```

其中$calc(l, r, x, y)$用于计算区间$[l,r]$和$[x,y]$的交集。

~~于是你兴奋地写完了代码，却发现WA声一片~~

接着我们发现会有重复的情况：比如``6 8 6 8 1``这组数据，由于我们把$pl,pr$和$vl,vr$交换位置后又算了一遍，那么就相当于把$[7,7]$这个区间算了两遍，产生了重复。

那么我们怎么避免重复呢？不难发现，这种情况仅仅会在$k=1$时出现，并且区间中仅有的一个数就是一个幸运数。那么我们就在原来的代码下面加一句特判即可。（别忘了这个区间必须符合要求）

```cpp
    ans += calc(num[i-1]+1, num[i], pl, pr)*calc(num[j], num[j+1]-1, vl, vr);
    ans += calc(num[j], num[j+1]-1, pl, pr)*calc(num[i-1]+1, num[i], vl, vr);
    if(k == 1) {
        if(calc(pl,pr,num[i],num[i]) && calc(vl,vr,num[i],num[i]))	//必须符合条件，否则根本不会计算
            ans--;
    }
```

于是你就可以非常愉快地过掉这道好~~冷门毒瘤~~题。

## 完整代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<ll> num;
int n;
ll pl, pr, vl, vr, k;
ll ans = 0;

void dfs(ll x) {		//无脑预处理
	if(x >= 1e9) return;
	num.push_back(x);
	dfs(x*10+4);
	dfs(x*10+7);
}

inline ll calc(ll l, ll r, ll x, ll y) {		//计算区间重复长度
	if(r < x || l > y) return 0;
	if(l>r || x>y) return 0;
	if(l >= x && l <= y) return min(r, y)-l+1;
	if(r >= x && r <= y) return r-max(l, x)+1;
	if(l < x && r > y) return y-x+1;
}

int main() {
	dfs(0);
	n = num.size();
	num.push_back(1e16);
	sort(num.begin(), num.end());
	cin >> pl >> pr >> vl >> vr >> k;
	for(int i = 1; i+k-1 <= n; i++) {
		if(num[i] > vr && num[i]>pr) break;		//（应该）可写可不写的特判break
		int j = i+k-1;
		ans += calc(num[i-1]+1, num[i], pl, pr)*calc(num[j], num[j+1]-1, vl, vr);
		ans += calc(num[j], num[j+1]-1, pl, pr)*calc(num[i-1]+1, num[i], vl, vr);
		if(k == 1) {
			if(calc(pl, pr, num[i], num[i]) && calc(vl, vr, num[i], num[i]))
				ans--;
		}
	}
	printf("%.12lf", ans*1.0/(vr-vl+1)/(pr-pl+1), 1.0);

	return 0;
}
```



---

## 作者：Jerry_heng (赞：0)

（一）

感觉蓝高了。

将所有符合条件的数列出来为 $a$ 序列。

那么选出其中连续 $k$ 个数以 $i$ 为开始的方案数为 $2\times (a_i-a_{i-1})\times (a_{i+k}-a_{i+k-1})$，注意特判边界即 $k=1$ 的重复计算即可。

（二）

记得开 long long。

AC 代码。

```cpp
//2025-01-24 19:41:51
#include<bits/stdc++.h>
#define db double
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define mkp make_pair
#define pii pair<int,int>
#define int long long
using namespace std;
bool MBE;
inline int read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f; 
}
const int inf=1e18;
int a[100010],cnt,ans;
queue<int>q;
int solve(int l,int r,int L,int R){
	if(l<0)l=L;if(r<0)r=R;
	l=max(l,L),r=min(r,R);
	return max(r-l+1,0ll);
}
signed main(){
    #ifndef ONLINE_JUDGE
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    int l1=read(),r1=read(),l2=read(),r2=read(),k=read();
    a[++cnt]=4,a[++cnt]=7;
    q.push(4),q.push(7);
    while(!q.empty()){
    	int u=q.front(),x;q.pop();
    	x=u*10+4;
    	if(x<=max(r1,r2))q.push(x),a[++cnt]=x;
    	x=u*10+7;
    	if(x<=max(r1,r2))q.push(x),a[++cnt]=x;
    }
    if(cnt<k){
    	puts("0");
    	return 0;
    }
    a[0]=-inf;
    a[cnt+1]=-inf;
    for(int i=1;i<=cnt-k+1;i++){
    	int l=a[i],r=a[i+k-1];
    	ans+=solve(a[i-1]+1,a[i],l1,r1)*solve(r,a[i+k]-1,l2,r2)+solve(a[i-1]+1,a[i],l2,r2)*solve(r,a[i+k]-1,l1,r1);
    	if(k==1&&max(l1,l2)<=a[i]&&a[i]<=min(r1,r2))ans--;
    }
    printf("%.10lf",ans*1.0/((r1-l1+1)*(r2-l2+1)));
    bool MED;
    cerr<<(&MED-&MBE)/1048576.0<<" MB, "<<1000*clock()/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}
```

---

## 作者：resftlmuttmotw (赞：0)


## 题目描述

[洛谷题目](https://www.luogu.org/problemnew/show/CF109B)

[CF题目](http://codeforces.com/contest/109/problem/B)

# 思路

先算出在范围内（num[q - 1] < max(qr,vr)）所有的只包含4和7的数

但要多算一个
```cpp
bool able = 1;
inline void dfs(int li)
{
	li为边界
    int i,it = q;
    记录该点的在num的位置
    num[i]表示第i大的只含4,7的数
    for(i = 0;i < 2;i++)
    {
        if(1ll * num[it] * 10 + x[i] > li)
        {
            if(able) num[++q] = 1ll * num[it] * 10 + x[i],able = 0;
            多算的那一个
            return;
        }
        num[++q] = num[it] * 10 + x[i]; 
        dfs(li);
    }
}

```
然后就分类讨论

```cpp
#include <cstdio>
#include <string>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long lol;
const int MAXN = 60000;
int x[2] = {4,7},q;
lol ans,num[MAXN];
bool able = 1;
inline void dfs(int li)
{
    int i,it = q;
    for(i = 0;i < 2;i++)
    {
        if(1ll * num[it] * 10 + x[i] > li)
        {
            if(able) num[++q] = 1ll * num[it] * 10 + x[i],able = 0;
            return;
        }
        num[++q] = num[it] * 10 + x[i]; 
        dfs(li);
    }
}
inline void EX(lol &x,lol &y) {lol z = y; y = x;x = z;}
int main()
{
    lol pl,pr,vl,vr;
    int i,j,k;
    cin >> pl >> pr >> vl >> vr >> k;
    if(pl > vl) EX(pl,vl),EX(pr,vr);
    保证一区间的左边界<=右区间的左边界
    dfs(max(pr,vr));
    求<=max(pr,vr)所有的只包含4和7的数和第一个大于max(pr,vr)且只包含4和7的数
    sort(num + 1,num + 1 + q);
    求出来的是乱序 排下序
    for(i = 1;i + k - 1 < q;i++)
    {
    	int j = i + k - 1;
    	题目要求 求恰好包含k个幸运数的概率
    	分成子问题 此时有num[i]~num[j] 共k个幸运数
       	有多少种取法
       	从pl pr中选出x
       	从vl vr中选出y
       	满足num[i-1]<x<=num[i]&&num[j]<=y<num[j+1]  (所以要多算一位)
       	或则num[i-1]<y<=num[i]&&num[j]<=x<num[j+1]
        if(num[i] < min(pl,vl)) continue;
        不可能的情况
        if(num[j] > max(pr,vr)) break;
        此时的num[j]大于了max(pr,vr)，num为递增序列，那接下来的若干num[j]也必大于max(pr,vr)
        if(pr < vl)
        { 
        Case1
        当
        pl              pr
        |      x         |
        				    vl     vr
        				 	|   y   |
       pl              pr
        |      x         |
        				    vl     vr
        				 y	|     |这种情况也是有可能的只要num[j+1]>vl&&num[i - 1] < pr
            if(num[i] >= pl&&num[j] <= vr&&num[j + 1] > vl&&num[i - 1] < pr)
                ans += (min(num[i],pr) - max(pl - 1,num[i - 1])) * (min(vr + 1,num[j + 1]) - max(num[j],vl));
              这些min,max都是必要的
            continue;
        }
        if(pr <= vr)
        { 
        |       |
        	|       |
        	但要考虑刚好衔接即vr==pl的情况和两区间重合的情况
        	if(num[i - 1] < pr&&num[j + 1] > vl)
            	ans += (min(num[i],pr) - max(pl - 1,num[i - 1])) * (min(vr + 1,num[j + 1]) - max(num[j],vl));
            if(num[i] >= vl&&num[j] <= pr)
                ans += (num[i] - max(vl - 1,num[i - 1])) * (min(pr + 1,num[j + 1]) - num[j]) - ((k == 1)? 1:0);
        } else {
        这种是算包含的情况
        |          |
        	|   |
            if(num[i] >= vl&&num[j] <= pr&&num[i - 1] < vr)
                ans += (min(num[i],vr) - max(vl - 1,num[i - 1])) * (min(pr + 1,num[j + 1]) - num[j]);
            if(num[j] <= vr&&num[i] >= pl&&num[j + 1] > vl)
                ans += (num[i] - max(pl - 1,num[i - 1])) * (min(vr + 1,num[j + 1]) - max(num[j],vl));
            if(num[i] >= vl&&num[j] <= vr&&k == 1) ans--;
            也要考虑算重的情况
        }
    }
    cout.setf(ios::fixed);
    cout的自动补全0
    cout << fixed << setprecision(12) << ans * 1.0 / (1ll * (pr - pl + 1) * (vr - vl + 1));
    cout的保留位数函数
    return 0;
}
```

---

