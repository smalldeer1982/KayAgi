# Journey Planning

## 题目描述

Tanya wants to go on a journey across the cities of Berland. There are $ n $ cities situated along the main railroad line of Berland, and these cities are numbered from $ 1 $ to $ n $ .

Tanya plans her journey as follows. First of all, she will choose some city $ c_1 $ to start her journey. She will visit it, and after that go to some other city $ c_2 > c_1 $ , then to some other city $ c_3 > c_2 $ , and so on, until she chooses to end her journey in some city $ c_k > c_{k - 1} $ . So, the sequence of visited cities $ [c_1, c_2, \dots, c_k] $ should be strictly increasing.

There are some additional constraints on the sequence of cities Tanya visits. Each city $ i $ has a beauty value $ b_i $ associated with it. If there is only one city in Tanya's journey, these beauty values imply no additional constraints. But if there are multiple cities in the sequence, then for any pair of adjacent cities $ c_i $ and $ c_{i + 1} $ , the condition $ c_{i + 1} - c_i = b_{c_{i + 1}} - b_{c_i} $ must hold.

For example, if $ n = 8 $ and $ b = [3, 4, 4, 6, 6, 7, 8, 9] $ , there are several three possible ways to plan a journey:

- $ c = [1, 2, 4] $ ;
- $ c = [3, 5, 6, 8] $ ;
- $ c = [7] $ (a journey consisting of one city is also valid).

There are some additional ways to plan a journey that are not listed above.

Tanya wants her journey to be as beautiful as possible. The beauty value of the whole journey is the sum of beauty values over all visited cities. Can you help her to choose the optimal plan, that is, to maximize the beauty value of the journey?

## 说明/提示

The optimal journey plan in the first example is $ c = [2, 4, 5] $ .

The optimal journey plan in the second example is $ c = [1] $ .

The optimal journey plan in the third example is $ c = [3, 6] $ .

## 样例 #1

### 输入

```
6
10 7 1 9 10 15```

### 输出

```
26```

## 样例 #2

### 输入

```
1
400000```

### 输出

```
400000```

## 样例 #3

### 输入

```
7
8 9 26 11 12 29 14```

### 输出

```
55```

# 题解

## 作者：dblark (赞：5)

第一眼 DP。

这个 DP 的转移重点在一个式子上：$ c_{i + 1} - c_i = b_{c_{i + 1}} - b_{c_i} $

对其变换形式，可以得到：$ b_{c_{i + 1}} - c_{i + 1} = b_{c_i} - c_i $

那么我们拿个数组记录一下相同值的答案（全部加起来），然后取最大值就好了。

注意到下标可能出现负数，加个 $ n $ 就好了。

代码：

```cpp
#include <cstdio>
#include <algorithm>

int n;
int a[200005];
long long ans;
long long f[600005];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", a + i);
    for (int i = 1; i <= n; ++i) ans = std::max(ans, f[a[i] - i + n] += a[i]);
    printf("%lld\n", ans);
    return 0;
}
```

吐槽：感觉比 2A 题水多了

---

## 作者：xht (赞：2)

两个数可以同时选当且仅当**下标差等于值的差**，也就是**值减下标**要相等。

那么把值减下标相同的值加起来即可，由于值减下标可能为负，为了方便，使用 map 即可。

```cpp
const int N = 2e5 + 7;
int n;
ll a[N], ans;

int main() {
	rd(n), rda(a, n);
	map<ll, ll> f;
	for (int i = 1; i <= n; i++) f[a[i]-i] += a[i];
	for (auto o : f) ans = max(ans, o.se);
	print(ans);
	return 0;
}
```

---

## 作者：formkiller (赞：1)

### Problem:
给出一个长度为 $n$ 的序列 $\{b\}$。

若序列 $\{c\}$ 是序列 $\{b\}$ 的子序列且满足 ${\forall} i:c_{i+1} - c_i = b_{c_{i+1}} - b_{c_i}$，则称序列 $\{c\}$ 为一个合法子序列。

一个合法子序列 $\{c\}$ 的贡献为 $\sum\limits^{m}_{i=1}b_{ci}$ ，其中 $m$ 为序列 $\{c\}$ 的长度。

求出所有合法的子序列的贡献中最大的贡献。


------------
### Solution:
由于等式两边均出现了两个不同的下标 $i$ 和 $i+1$，不容易维护信息，所以我们考虑转换这个等式。

$c_{i+1} - c_i = b_{c_{i+1}} - b_{c_i} \Leftrightarrow c_{i+1} - b_{c_{i+1}}= c_i  - b_{c_i}$

令 $x = c_i$ ， $ y = c_{i+1}$，得 $y - b_{y}= x  - b_{x}$

维护这个等式成立，只需要在序列 $\{b\}$ 中维护 $ i - b_i$ 这个数即可。我们可以考虑将其作为数组下标，每次更新答案。考虑到 $ i - b_i$ 有可能出现负数，但由于数据范围不大，我们可以加上一个恒定值做数组偏移。比赛的时候脑子一抽，强行写了发单点查询单点修改线段树，贴出来让大家参考~~看笑话~~。


------------
### Code:

```cpp
//good luck
# include <iostream>
# include <cstdio>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <string>
# include <algorithm>

#define LL long long
#define maxn int(1e6+5)
#define is(a) (a>='0'&&a<='9')

using namespace std;

struct data{LL x;}t[maxn<<2];

int N;
LL ma,f[maxn];

inline void read(int &x)
{
  x=0;bool f=0;char ch=getchar();
  for (;!is(ch);ch=getchar()) f|=ch=='-';
  for (;is(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
  x=f?-x:x;
}

inline void update(int ro,int L,int R,int x,LL val)
{
	if (L==R) 
	{
		t[ro].x=max(val,t[ro].x);
		return;
	}
	int Mid=(L+R)>>1;
	if (x<=Mid) update(ro<<1,L,Mid,x,val);
	else		update(ro<<1|1,Mid+1,R,x,val);
}

inline LL query(int ro,int L,int R,int x)
{
	if (L==R) return t[ro].x;
	int Mid=(L+R)>>1;
	if (x<=Mid) return query(ro<<1,L,Mid,x);
	else		return query(ro<<1|1,Mid+1,R,x);
}

int main()
{
//	freopen("a.in","r",stdin);
	read(N);
	for (int i = 1; i <= N; ++i)
	{
		int x,y;
		read(x);
		y=x-i;
		f[i]=query(1,1,maxn*2,y+maxn)+x;
		update(1,1,maxn*2,y+maxn,f[i]);
	}
	for (int i = 1; i <= N; ++i) ma=max(ma,f[i]);
	cout << ma << endl;
    return 0;
}
```

---

## 作者：Reanap (赞：1)

这道题第一眼看过去可能会有点懵，但第二次读题就会发现这道题不难。

本题的体验在于下面这个式子:

$c_{i+1} - c_i = b_{c_{i+1}} - b_{c_{i}}$

看上去有一些怪异，因为在每一次比较的对象都不一样，所以我们可以把式子转化成每次比较的对象都一样的情况。

移项得下式:

$b_{c_{i+1}} - c_{i+1} = b_{c_i} - c_i$

这样子等式两边的东西都是可以预处理比较的。

可以定义$dp_i$为选择第$i$个位置的最大值。

所以得：

$dp_i = \max(dp_k)+b_i$ 其中$b_i - i = b_k - k$

这是一个$n^2$的算法，我们考虑优化。

我们可以维护出当前同种$b_j - j$的值的最大$dp$值，这样就可以$O (1)$转移了。

本人考试时没有看数据范围，所以维护的时候就开的是map，不过没有什么影响啦。

代码很简单

```cpp
#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int MAXN = 2e5 + 5;
map <int , LL> M;
LL dp[MAXN] , n , b[MAXN] , ans;
int main() {
	scanf("%lld" , &n);
	for (int i = 1; i <= n; ++i) scanf("%lld" , &b[i]);
	for (int i = 1; i <= n; ++i) {
		dp[i] = M[b[i] - i] + b[i];
		M[b[i] - i] = max(M[b[i] - i] , dp[i]);
		ans = max(ans , dp[i]);
	}
	printf("%lld" , ans);
	return 0;
}

```

---

## 作者：123456zmy (赞：1)

题意：  
给你一个数列 $b$，你需要选出一些数，记你选的数的下标为 $c_1,c_2,…,c_k$，输出在满足 $c_{i+1}-c=b_{c_{i+1}}-b_{c_i}$ 的情况下最大的选的数的和（$\max(\sum_{i=1}^{k}b_{c_i})$）。
___
题目要求在数之差和下标之差相同的数，移一下项就可以转化为求数与下标之差相同的数，用一个桶记录值与下标的差并维护最大值输出即可。

注意：直接相减可能会出现负数，可以加上一个数~~或者用`map<int,int>`~~。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int n;
long long b,ansm;
map<int,long long>ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&b);
		ansm=max(ans[b-i]+=b,ansm);
	}
	printf("%lld",ansm);
	return 0;
}
```

---

## 作者：NaOH_Frog (赞：0)

直接转化式子

题目已知 $c_{i + 1} - c_{i} = b_{c_{i + 1}} - b_{c_i}$

移项后得到 $b_{c_{i + 1}} - c_{i + 1} = b_{c_i} - c_i$

对于路程经过的每一项，它的 $b$ 值和 $c$ 值的差为定值

只要把所有 $b_i$ 减去 $i$ 然后把相同的值加在一起就行了

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct nod{
	int bt, cn;
}a[200007];
bool cmp(nod a, nod b){
	return a.cn > b.cn;
}
int main(){
	int n;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i].bt;
		a[i].cn = a[i].bt - i;
	}
	sort(a, a + n, cmp); //按照差值排序，直接把相等的值排到一起
	long long ans = 0, mans = 0;
	for(int i = 0; i < n; i++){
		if(i != 0){
			if(a[i].cn != a[i - 1].cn){
				mans = max(ans, mans);
				ans = a[i].bt;
			}else ans += a[i].bt;
		}else ans = a[i].bt;
	}
	mans = max(ans, mans);
	cout << mans << endl;
	return 0;
}
```


---

## 作者：流绪 (赞：0)

比赛时没打出来,一直以为要打一个 nlog(n) 的,甚至一度以为我误入 div1,第二天再一看题目才发现是自己憨批...

题目给的式子：Ci+1 - Ci = Bi+1 - Bi

移项得：Ci+1 - Bi+1 = Ci - Bi

然后就很显然了，每一条路线能走的城市必定美丽值和其下标差相等。之于另一个条件严格递增，我们只要从前往后做，然后因为下标是严格递增的，若差相等，则美丽值也是严格递增的。

所以我们算出每一个城市美丽值和下标的差，然后用另一个数组，下标为这个差值的地方存上美丽值，最后取最大值即可。

一个细节，因为美丽值可能小于下标，导致其差为负数，那么我们给他们的差都加上 400000，这样就让他们都为正可以存了（好像200000就可以了？）。

下面是 AC 代码。
```
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
#define mod 1000000009
using namespace std;
int a[maxn],b[maxn]={0};
signed main()
{
	ios::sync_with_stdio(0);
	int n; 
	cin >> n;
	int maxx = 0;
	for(int i=1;i<=n;i++)
	{
		cin >> a[i];
		b[a[i]-i+400000] += a[i]; 
	}
	for(int i=0;i<=800000;i++)
		maxx = max(maxx,b[i]);
	cout << maxx;
  	return 0;
}
```


---

## 作者：Fairicle (赞：0)

对于这题，我们把式子转化一下，问题就迎刃而解了。

把 $c_{i+1}-c_i$ $=$ $b_{i+1}-b_i$ 转化成 $c_{i+1}-b_{i+1}$ $=$ $c_i-b_i$ 即可，对于 $c_j-b_j$ 这个量开一个 map 存储，相同的放一起。

code：
```
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ul unsigned long long
#define ui unsigned int
#define ri register int
int n;
map<int,ll> mp;
ll ans;
int b[200010];
int main()
{
	n=read();
	for(ri i=1;i<=n;++i)
	{
		b[i]=read();
		mp[b[i]-i]+=b[i];
		ans=max(ans,mp[b[i]-i]);
	}
	cout<<ans;
    return 0;
}
```


---

## 作者：dead_X (赞：0)

## 1 题意简述
给出长度为 $n(n\leq2\times 10^5)$ 的数列 $a$ ，求出数列中最长的子序列 $b$ ，使得 $b_i$ 递增且任意两项数值之差等于在 $a$ 中的位置的距离差。
## 2 思路简述
题意简述中的任意两项显然可以化为所有的相邻两项

如果 $A$ 能到 $B$ ，$B$ 能到 $C$ ， 那么 $A$ 能到 $C$

记录一下最近关系即可， ``map`` 解决
## 3 代码
```
#include<bits/stdc++.h>
#include<map>
using namespace std;
int a[500003],b[500003];
bool f[500003];
using namespace std;
map<int,int> M;
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	for(int i=1; i<=n; i++) 
	{
		map<int,int>::iterator m;
    	m=M.find(a[i]-i);
    	if(m!=M.end()) b[m->second]=i,f[i]=1,M.erase(m);
		M[a[i]-i]=i;
	}
	long long ans=0,now;
	int pos;
	for(int i=1; i<=n; i++) if(!f[i]) 
	{
		now=a[i],pos=i;
		while(b[pos]) pos=b[pos],now+=a[pos];
		if(now>ans) ans=now;
	}
	cout<<ans;
	return 0;
}
```
## 4 评价
赛时想出做法所用时间:9min

比赛A掉所用时间:21min

建议难度:橙/黄

---

