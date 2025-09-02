# k-Multiple Free Set

## 题目描述

A $ k $ -multiple free set is a set of integers where there is no pair of integers where one is equal to another integer multiplied by $ k $ . That is, there are no two integers $ x $ and $ y $ $ (x<y) $ from the set, such that $ y=x·k $ .

You're given a set of $ n $ distinct positive integers. Your task is to find the size of it's largest $ k $ -multiple free subset.

## 说明/提示

In the sample input one of the possible maximum 2-multiple free subsets is {4, 5, 6}.

## 样例 #1

### 输入

```
6 2
2 3 6 5 4 10
```

### 输出

```
3
```

# 题解

## 作者：XL4453 (赞：7)

这么点大的数据范围不是瞎玩？

---
### 解题思路：

这个题第一个想到的应该是图论，对于每一个不能同时取的连一条边，然后求一个最大独立集，大小就是答案。

不太好写，考虑再抠一点性质出来，优化一下。

发现这个图其实是若干链组成的（如果一个点也可以看成一条长度为 $1$ 的链的话），那么可以直接贪心选择，就是从一个端点开始选择，每隔一个选择一个。

可是这样还要建图，还是麻烦，能不能直接做呢？

考虑用将所有的数排序，假装建立了一个图，然后每一次将这一个点链接的下一个点（可能不存在）打上标记，表示不取。

具体实现上用一个 map 打标记就行了。

---
### 代码：

```cpp
#include<map>
#include<cstdio>
#include<algorithm>
#define int long long
using namespace std;
int n,k,a[100005],ans;
map <int,bool> del;
signed main(){
	scanf("%I64d%I64d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%I64d",&a[i]);
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++){
		if(del[a[i]]==0){
			del[a[i]*k]=1;
			ans++;
		}
	}
	printf("%I64d",ans);
	return 0;
}
```

---

## 作者：素质玩家孙1超 (赞：3)

把每一个 $K$ 倍关系都看成一条边，那么原题就变成求最大独立集。

然后我们稍微分析一下我们建出来的图。

由于题目中给的是一个没有重复元素的集合，那么每个数最多只出现一次。

同样的，每个元素的 $K$ 倍也最多出现一次。

所以这个建造出来的图就是很多条链。

链上的最大独立集就是链长除以二向下取整，相当于贪心的从端点开始取数。

所以只要总小到大取数并且纪录不能取的数就好了。（由于$K*a_i$会爆int，所以我直接用了long long ）

---

代码:

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int Maxn=1e5+5;
inline int R()
{
	char ch=getchar();int x=0;bool f=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
int a[Maxn],k,n;
map<int,bool>vis;
signed main()
{
	n=R();k=R();
	for(int i=1;i<=n;i++) a[i]=R();
	sort(a+1,a+1+n);
	int ans=0;
	for(int i=1;i<=n;i++) 
		if(!vis[a[i]])
		{
			++ans;
			vis[a[i]*k]=1;
		}
	printf("%lld\n",ans);
}
```

---

## 作者：llzzxx712 (赞：2)

## CF274A

**看前提示：本题翻译有些小问题，这 n 个数是一个集合而不是序列，集合保证了 n 个数中没有相同的数。可以再尝试自己做一下。**

### 题目分析
本题中要我们找出最多的数，保证其中不存在一对数，满足一个数是另一个数的 k 倍。

那么对于一个数 $a_i$ ，如果 $a_i * k$ 也在集合中，那么我们肯定不能将它们都选上，肯定要去掉一个。

**应该去掉哪一个呢？** 题目保证了每个数都不同，如果留下 $a_i$ 那么它不会和其它数冲突（因为只有一个 $a_i * k$）。但如果留下 $a_i * k$ ，它就有可能和 $a_i * k * k$ 冲突。所以应该保留 $a_i $。

那么本题的思路就很明显了，将序列排序，从小到大扫描每一个数 $a_i$ ，用它来删去其中的$a_i * k$,并将 ans-1 （ans 初始为 n）。

### 易错点
- 给的数据不是从小到大的，二分前先要排序
- 记得开 long long

### AC代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
void read(ll &x){
	int f=1;x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0'; ch=getchar();}
	x*=f;
}
#define N 100010
int n,k,ans;
ll a[N];
bool v[N];//为 1 表示删去 
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++) read(a[i]);
	sort(a+1,a+1+n);
	ans=n;
	for(int i=1;i<=n;i++){
		if(v[i]) continue;
		int le=i+1,r=n;
		while(le<=r){
			ll d=a[i]*k;
			int mid=(le+r)>>1;
			if(a[mid]<d){
				le=mid+1;
			}
			else if(a[mid]>d){
				r=mid-1;
			}
			else{
			 	v[mid]=1;
			 	ans--;
			 	break;
			} 
		}
	}
	cout<<ans;
	return 0;
}

```

如果这篇题解对你有帮助，给个赞呗

---

## 作者：Quirrel_dog (赞：1)

# CF274A 题解
### [题目链接](https://www.luogu.com.cn/problem/CF274A)  
题目要求：找已经给出的序列中最长的集合使得集合中没有两个数成 $ k $ 倍关系，且保证没有相同的数。

分析：对于一个数 $ x $，如果 $ k \times x $ 在原序列中，则若取 $ x $ 与取 $ k \times x $ 对答案产生的贡献相同，但是取 $ k \times x $ 会对 $ k \times x \times x$ 造成影响，所以取 $ x $ 显然优于 $ k \times x $，故我们可以对原序列按从小到大排序，取未取过的数并将它的 $ k $ 倍删去(即打标记)，但是由于开 ` bool ` 数组空间不够，所以用 ` map ` 来打标记，然后统计取出的数的数量，输出即可。

AC  CODE
```cpp
#include <bits/stdc++.h>
#define int long long
const int N = 1000010;
using namespace std;
int n,k,ans;
int a[N];
unordered_map <int,bool> mp;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie();cout.tie();
	cin>>n>>k;
	for(int i = 1;i<=n;i++) cin>>a[i];
	sort(a+1,a+n+1);
	for(int i = 1;i<=n;i++) if(!mp[a[i]]) mp[a[i]*k]=1,ans++;
	cout<<ans;
	return 0;
}
```
###### ~~经典 CF 恶评，感觉差不多绿/黄。~~

---

## 作者：tallnut (赞：0)

# 吐槽
就这都能到蓝，真的服了。
# 思路
直接模拟一遍。开一个 `map<long long,bool>` 表示一个数是否取过，如果没取过就更新答案，然后把该数自己和该数 $\times k$ 打上取过的标记。当然，得先排序一遍再计算。
# 双倍经验
P1978 是这题的双倍经验。~~但那题的数据范围比这题大，而评级却比这题低，真的服了。~~

如果你想用和本题一样的思路 $\color{#52C41A}\text{AC}$ 这题的话，你需要开 `__int128_t`。
# AC 代码
[AC 记录](https://www.luogu.com.cn/record/137819059)。
```
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
const int N = 1e5 + 1;
long long n,k,ans;
long long a[N];
map<long long,bool> vis;
int main()
{
	cin >> n >> k;
	for (int i = 1;i <= n;i++)
		cin >> a[i];
	sort(a + 1,a + n + 1);
	for (int i = 1;i <= n;i++)
		if (vis[a[i]] == false)
		{
			ans++;
			vis[a[i]] = true;
			vis[a[i] * k] = true;
		}
	cout << ans;
}
```

---

## 作者：黑影洞人 (赞：0)

我一开始没看到数字可以不同，于是我想的是建一个图跑一个树形 DP。

具体操作也很模板，就是先排序，建边。

可以发现，这是一个森林（其实是一堆链）。

然后对于每条链，跑一个没有上司的舞会，就是选出最大独立集。

```cpp
void dfs(int x){
	vis[x]=1; 
	dp[x][0]=0;
	dp[x][1]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(vis[y])continue;
		dfs(y);
		dp[x][0]+=max(dp[y][0],dp[y][1]);
		dp[x][1]+=dp[y][0];
	}
}
```

然后细节就是建边的时候一定要排序，不排序会建少边，然后会寄。

完整代码：
```cpp
#include<cstdio>
#include<algorithm>
#include<map>
#define int long long
#define N 114514
using namespace std;
int n,k,ans;
bool vis[N];
map<int,int>mp;
//lz love ohq
struct node{
	int a,id;
	bool operator<(const node &aa)const{return a<aa.a;}
}a[N];
int head[N],to[N],nxt[N],dp[N][2],tot;
void add(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
void dfs(int x){
	vis[x]=1; 
	dp[x][0]=0;
	dp[x][1]=1;
	for(int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(vis[y])continue;
		dfs(y);
		dp[x][0]+=max(dp[y][0],dp[y][1]);
		dp[x][1]+=dp[y][0];
	}
}
signed main(){
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i].a),a[i].id=i,mp[a[i].a]=i;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++)if(mp[a[i].a*k])add(a[i].id,mp[a[i].a*k]);
	for(int i=1;i<=n;i++)if(!vis[a[i].id])dfs(a[i].id),ans+=max(dp[a[i].id][0],dp[a[i].id][1]);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Arghariza (赞：0)

> 要求从中挑出尽可能多的数，保证其中不存在一对数，满足一个数是另一个数的k倍。

我们可以考虑构造几组数，每一组内的数相邻 $2$ 个都成 $k$ 倍关系，例如：

$1\;, 1\;, 2\;, 2\;, 4\qquad k=2$

可以分成：

$\begin{cases}(1\;,2\;,4)\\(1,\; 2)\end{cases}$

于是我们可以取（标红的数）：

$\begin{cases}(\color{red}1\color{black}\;,2\;,\color{red}4\color{black})\\(\color{red}1\color{black},\; 2)\end{cases}$

换句话说，其实就是隔一个取一个，如果你取了 $a_n$ ，就不能取 $a_n\cdot\;k$ ， 但是 $a_n \cdot\;k^2$ 可以取（如果有的话）。因此，当我们取 $a_n$ ，只用把 $a_n\cdot\; k$ 打上标记表示不能再取（然而前提是 $a_n$ 没有打上标记）。

当然大前提是 $a$ 是按照从小到大排序的，至于具体的细节就看注释了（别忘了开$long\;long$）：

```
#include <bits/stdc++.h>
#define int long long// 不开long long见祖宗
using namespace std;

int n, k, ans, s[100001];
map<int, bool> vis;// 因为s太大了所以使用map

signed main() {
	cin >> n >> k;// 输入
	for (int i = 1; i <= n; i++) {// 输入
		cin >> s[i];
	}
	sort(s + 1, s + n + 1, less<int> ());// 从小到大排序
	for (int i = 1; i <= n; i++) {// 遍历每个数
		if (!vis[s[i]]) {// 如果可以取这个数
			vis[s[i] * k] = true;// 把这个数的k倍打上标记
			ans++;// ans递加
		}
	}
	cout << ans;// 输出
	return 0;
}
```

---

## 作者：espionage (赞：0)

### 题目链接: [k-Multiple Free Set](https://www.luogu.com.cn/problem/CF274A)

题意：给定正整数 $n$，$k$ 和 $n$ 个互不相同的正整数。求最多能在 $a_1,\cdots,a_n$ 中选出几个正整数，使得其任意两个都不满足 $k$ 倍关系。

---

想一个朴素的贪心，先对整个数组进行排序，然后从小到大遍历一遍，如果 $a_i$ 没有被遍历过，那么计入答案。并把 $a_i \times k$ 改为 $1$，使得 $a_i \times k$ 不会再次被遍历到。


#### 正确性？

由于是否取 $a_i$ 只会影响到 $a_i \times k$，所以在 $a_i \times k ^ p$（$p \ge 0$）这 $p$ 个数中最多只能选出 $\lceil \frac{p}{2} \rceil$ 个数，故从第一个数开始取是最优的。

#### 实现？

可以用 `map` 存是否便利过或可以遍历，记得开 `long long`。

以下是代码。

```cpp
#include <bits/stdc++.h>
#define y1 y114514
#define endl '\n'
#define int long long

using namespace std;

const int N = 1e5 + 10;

int n, k, ans;
int a[N];
map<int, int> vis;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    
    cin >> n >> k;
    for(int i = 1;i <= n;i++)
    	cin >> a[i];
    sort(a + 1, a + n + 1);
    for(int i = 1;i <= n;i++)
    	if(vis[a[i]] == 0)
    	{
    		vis[a[i] * k] = 1;
    		ans++;
    	}
    cout << ans;
    
	return 0;
}
```

---

## 作者：DepContain (赞：0)

#### 题目链接 : [Link](https://www.luogu.com.cn/problem/CF274A)

## Description

给定正整数 $n,k$ 和 $n$ 个互不相同的正整数 $a_1,\cdots,a_n$，求最多能在 $a_1,\cdots,a_n$ 中选出多少个正整数，使得其中没有两个不同的正整数成 $k$ 倍关系。


## Solution

众所周知, 水的颜色是蓝色的。

对于序列中的每一个数 $a_i$，有且只有一个数满足是它的 $k$ 倍。

由于 $k \in [1, 10^9]$，$ka_i \ge a_i$，我们从小到大对原数组排序。

遍历 {$a_n$}  每次 `vis[k * a[i] = 1` 记录即可。

但考虑到 $n \in [1, 10^5]$ 且 $k \in [1, 10^9]$ 容易爆下标，故用 `map` 存。

## AC Code
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int maxn = 1e5 + 5;

int a[maxn], k, n;
map<int, bool> vis;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n >> k;
	for(int i = 0; i < n; ++i) cin >> a[i];

	sort(a, a + n);

	int ans = 0;
	for(int i = 0; i < n; ++i)
		if(!vis[a[i]]) {
			++ans;
			vis[a[i] * k] = 1;
		}

	cout << ans;

	return 0;
}

```


---

