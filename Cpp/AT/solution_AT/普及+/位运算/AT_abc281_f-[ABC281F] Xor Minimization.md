# [ABC281F] Xor Minimization

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc281/tasks/abc281_f

非負整数列 $ A=(a_1,\ldots,a_N) $ が与えられます。

$ A $ に対して次の操作をちょうど $ 1 $ 回行います。

- 非負整数 $ x $ を選ぶ。そして、$ i=1,\ldots,N $ すべてに対し、$ a_i $ の値を「$ a_i $ と $ x $ のビット単位 xor」に置き換える。
 
操作後の $ A $ に含まれる値の最大値を $ M $ とします。$ M $ の最小値を求めてください。

 ビット単位 xor とは 非負整数 $ A,\ B $ のビット単位 xor 、$ A\ \oplus\ B $ は、以下のように定義されます。 - $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。

 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 1.5\ \times\ 10^5 $
- $ 0\ \leq\ a_i\ \lt\ 2^{30} $
- 入力はすべて整数
 
### Sample Explanation 1

$ x=2 $ として操作をすると、操作後の数列は $ (12\ \oplus\ 2,18\ \oplus\ 2,\ 11\ \oplus\ 2)\ =\ (14,16,9) $ となり、最大値 $ M $ は $ 16 $ となります。 $ M $ を $ 16 $ より小さくすることは出来ないため、この値が答えです。

## 样例 #1

### 输入

```
3
12 18 11```

### 输出

```
16```

## 样例 #2

### 输入

```
10
0 0 0 0 0 0 0 0 0 0```

### 输出

```
0```

## 样例 #3

### 输入

```
5
324097321 555675086 304655177 991244276 9980291```

### 输出

```
805306368```

# 题解

## 作者：Pengzt (赞：10)

[ABC281F](https://www.luogu.com.cn/problem/AT_abc281_f)

先将每一个 $a_i$ 二进制拆分。

因为每一位的 $\text{xor}$ 运算是互不影响的，于是可以考虑每一位。

从高位到低位考虑，因为 $a_i < 2^{30}$，所以二进制状态下的 $a_i$ 的长度是 $\le 29$ 的。

假设在考虑 $bit$ 位，则有 $2$ 种情况：

1. 当前考虑的所有数的第 $bit$ 位都是 $0$ 或 $1$。

2. 当前考虑的所有数的第 $bit$ 位 $0$ 和 $1$ 都有。

第 $1$ 种情况显然可以使最后答案第 $bit$ 位变为 $0$。

第 $2$ 种情况：数组 $c$ 存储第 $bit$ 位为 $0$ 的数，数组 $d$ 存储第 $bit$ 位为 $1$ 的数。

此时最后答案的第 $bit$ 位肯定为 $1$。

但是如果 $x$ 的第 $bit$ 位为 $0$，便只需考虑 $d$ 数组了。同理，若 $x$ 的第 $bit$ 位为 $1$，便只需考虑 $c$ 数组了。

分别搜索 $x$ 的 $bit$ 位为 $1$ 和 $0$ 即可。

但直接搜索参数需要传递数组，效率过低。

优化方法：排序后传递下标。

时间复杂度：$\mathcal{O}(2^{\log_2n}+n\log n)=\mathcal{O}(n\log n)$

[评测记录](https://www.luogu.com.cn/record/97087596)

---

## 作者：Zhaohongrui (赞：9)

第一眼看到很懵，感觉除了暴力枚举 $x$ 的值没什么好方法。但我仔细想了想，这不就是 trie 树吗？

设 $son_{x,0}$ 为节点 $x$ 的指向 $0$ 的节点，$son_{x,1}$ 为节点 $x$ 指向 $1$ 的节点，最小答案为 ```query(x, dep)```

设当前节点为 $x$ ，当前深度为 $dep$ 。

当 $son_{x,0}=0$ 且 $son_{x,1}=0$，最小答案为 $0$。

当 $son_{x,0}=0$ 且 $son_{x,1}\neq 0$，最小答案为 ```query(son[x][1], dep - 1)```。

当 $son_{x,0}\neq 0$ 且 $son_{x,1}=0$，最小答案为 ```query(son[x][0], dep - 1)```。

当 $son_{x,0}\neq 0$ 且 $son_{x,1}\neq 0$，最小答案为 ```min(query(son[x][0],dep - 1), query(son[y][0],dep - 1)) | 1 << dep```。


## 代码
```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int son[4500005][2],cnt = 1;
void insert(int x) {
	int u = 1;
	for (int i = 29; i >= 0; i--) {
		int v = x >> i & 1;
		if (!son[u][v]) son[u][v] = ++cnt;
		u = son[u][v];
	}
}
int query(int x, int dep) {
	if (!son[x][0] && !son[x][1]) return 0;
	if (!son[x][0]) return query(son[x][1], dep - 1);
	if (!son[x][1]) return query(son[x][0], dep - 1);
	return min(query(son[x][0], dep - 1),query(son[x][1], dep - 1)) | 1 << dep;
}
int main() {
	scanf("%d", &n);
	for (int _ = 1; _ <= n; _++) {
		int a;
		scanf("%d", &a);
		insert(a);
	}
	printf("%d\n",query(1, 29));
	return 0;
}
```
~~萌新的第一篇题解，求过~~

---

## 作者：EternalHeart1314 (赞：5)

### [题目传送门](https://www.luogu.com.cn/problem/AT_abc281_f)

### [双倍经验](https://www.luogu.com.cn/problem/CF1285D)

# 思路

看到位运算，我首先就想到了位之间相互独立。

因为 $a_i<2^{30}$，所以 $a_i$ 最多有 $30$ 位（二进制下），从高到低每一位考虑。

设当前位是 $bit$ 位，则：

+ 如果 $bit$ 位全为 $1$ 或 $0$，则可以使得当前位全部变成 $0$。

+ 如果 $bit$ 位有 $1$ 也有 $0$，那么可以选择异或 $1$ 和异或 $0$ 两种情况。

> + 异或 $1$：则 $bit$ 位 $0$ 变成 $1$，$1$ 变成 $0$，可以将**原来**为 $0$ 的放在一起，继续搜索。
>
> + 异或 $0$：则 $bit$ 位 $0$ 还是 $0$，$1$ 还是 $1$，可以将**原来**为 $1$ 的放在一起，继续搜索。
>
> 由于 $bit$ 位**肯定**有 $1$，所以要加上 $2^{bit}$。
>
> 最后取 $\min$。

# Code
```
#include<bits/stdc++.h>
#define VI vector<int>
using namespace std;

int n;

int dfs(VI a, int bit) {
	if(!bit) {
		return 0;
	}
	-- bit;
	VI b, c;
	for(auto i : a) {
		if(i >> bit & 1) {
			b.push_back(i);
		} else {
			c.push_back(i);
		}
	}	//1 和 0 分别考虑 
	if(b.empty()) {
		return dfs(c, bit);
	} else if(c.empty()) {
		return dfs(b, bit);
	}	//只有 1 或 只有 0 
	return min(dfs(b, bit), dfs(c, bit)) + (1 << bit);
		//有 1 也有 0 
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	VI a;
	for(int i(1), x; i <= n; ++ i) {
		cin >> x;
		a.push_back(x);
	}
	return cout << dfs(a, 30), 0;
}
```

### 珍惜生命，远离抄袭

---

## 作者：expecto__patronum (赞：2)

## 题目
$n$ 个数，第 $i$ 个数 $a_i$，

你可以选择一个非负的数 $x$，对每个数都异或 $x$，

使 $a_i$ 异或 $x$ 的最大值最小，输出此时的最大值。

## 题解
考虑按位分治。

1.当有一位全是 $0$ 或者全是 $1$ 时，一定可以置 $0$。

2.当不全是 $1$ 时，会把数分成两堆，其中一堆取 $0$，另一堆取 $1$。

因为有后效性，所以对低位，递归这两堆。

将其中较小的数挂在 $1$ 的后面，较大的数挂在 $0$ 的后面。

## Code：
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,v;
vector<int>now;
ll gao(int dep,vector<int>q)
{
	if(dep<0)return 0;
	int cnt[2]={0};
	for(int i=0;i<q.size();++i)
	cnt[q[i]>>dep&1]++;
	if(!cnt[0]||!cnt[1])return gao(dep-1,q);
	else
	{
		vector<int>nex[2];
		for(int i=0;i<q.size();++i)
		nex[q[i]>>dep&1].push_back(q[i]);
		return (1<<dep)|min(gao(dep-1,nex[0]),gao(dep-1,nex[1]));
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		scanf("%d",&v);
		now.push_back(v);
	}
	printf("%lld\n",gao(30,now));
	return 0;
}
```
[博客](https://blog.csdn.net/Code92007/article/details/128271109)

---

## 作者：Erica_N_Contina (赞：2)

# [ABC281F] Xor Minimization



## 大意

求一自然数 $i$ 使得 $A_k \oplus i\ (k=1\sim N)$ 中的最大值 $m$ 最小。

## 思路

我们从高位开始分情况讨论。

- $a_1\sim a_N$ 的第 $p$ 位均为 $1$ 或者 $0$。

这样我们就可以让 $i$ 的第 $p$ 位相应的为 $1$ 或者 $0$，那么 $m$ 的第 $p$ 位就为 $0$。

- $a_1\sim a_N$ 的第 $p$ 位有 $1$ 也有 $0$。

那么首先，$m$ 的第 $p$ 位（从第 $0$ 位开始计数）肯定是 $1$ 逃不了了，所以此时 $m$ 一定不小于 $2^p$。这时我们来讨论 $i$。

- 当 $i$ 的第 $p$ 位为 $1$ 时。

我们找到所有第 $p$ 位为 $0$ 的 $a_k$，递归下去，将返回值 $+2^p$ 作为 $m$ 的值 $m_1$。

- 当 $i$ 的第 $p$ 位为 $0$ 时。

我们找到所有第 $p$ 位为 $1$ 的 $a_k$，递归下去，将返回值 $+2^p$ 作为 $m$ 的值 $m_2$。

然后我们在 $m_1$ 和 $m_2$ 中取最小值作为返回值即可，类似回溯。

```C++
/*////////ACACACACACACAC///////////
       . Coding by Ntsc .
       . ToFind Chargcy .
       . Prove Yourself .
/*////////ACACACACACACAC///////////

//头文件
#include<bits/stdc++.h>

//数据类型
#define ll long long
#define ull unsigned long long
#define db double
#define endl '\n'
//命名空间
using namespace std;
//常量
const int N=1e6+5;
const int M=1e3;
const int MOD=903250223;
const int INF=1e9;
//变量
int n,b,c,a[N],y[N],ans=INF,tmp,k,cnt,mxr;

int dfs(int p,int l,int r){//p为第p位
	if(p==-1)return 0;
	int mid=INF;
	for(int i=l;i<=r;i++){
		if((a[i]>>p)&1){
			mid=i;break;// 找到第一个i满足a[i]的第p位为1
		}
	}
	//1~mid-1满足a[i]的第p位为0,mid~r满足a[i]的第p位为1
	if(mid==l || mid==INF)return dfs(p-1,l,r);//说明l~r中a[i]的第p位均相同
	return min(dfs(p-1,l,mid-1),dfs(p-1,mid,r))+(1<<p);
}

signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];

	}
	sort(a+1,a+n+1);
	cout<<dfs(29,1,n);//位数与a[i]最大值相同,即2^30(即0~29)
	return 0;
	
}

```




---

## 作者：honglan0301 (赞：2)

## 题意简述
给定 $n\ (n\leq 1.5\times10^5)$ 个数的数列，可以任选一个正整数 $x$，让数列中每个数都与它按位异或。求经过这样的操作后数列中的最大值最小是多少。

## 题目分析
容易想到按位（从高位向低位）考虑，发现对于当前可能成为最大值的数来说，若 $x$ 的第 $i$ 位为 $1$, 则不需要再考虑第 $i$ 位为 $1$ 的数；反之不需要考虑第 $i$ 位为 $0$ 的数。

于是从高位向低位 dfs，用 vector 装目前还需要考虑的数，若当前不存在这一位（第 $i$ 位）为 $0$ 或不存在这一位为 $1$ 的数，则显然当前情况这一位选 $0/1$ 是优的，直接向下 dfs。否则当前情况这一位必然不可能都消成 $0$，根据向下 dfs 的返回值取更优情况，并加上 $2^{i-1}$ 即可。

## 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <vector>
#define int long long
using namespace std;

int n,a[150005],ans;
vector <int> v;

int dfs(vector <int> aa,int dep)
{
	if(dep<0)
	{
		return 0;
	}
	vector <int> bb,cc;
	for(auto i:aa)
	{
		if(i&(1<<dep))
		{
			bb.push_back(i);
		}
		else
		{
			cc.push_back(i);
		}
	}
	if(!bb.size())
	{
		return dfs(cc,dep-1);
	}
	else if(!cc.size())
	{
		return dfs(bb,dep-1);
	}
	return min(dfs(bb,dep-1),dfs(cc,dep-1))+(1<<dep);
}
signed main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		v.push_back(a[i]);
	}
	ans=dfs(v,30);
	cout<<ans<<endl;
}
```



---

## 作者：linch (赞：0)

题面比较简短，不再赘述。讲解部分的变量名与题面保持一致。
## Solution
考虑贪心，从高位开始考虑。

如果所有数的某一位（指二进制位，下同）都是 $0$，那么我们可以让 $i$ 的这一位为 $0$，此时该位异或值为 $0$。

同理，当所有数该位都是 $1$，$i$ 的这一位也要取 $1$，此时该位异或值为 $0$。

如果一部分数这一位上为 $1$，一部分为 $0$，则 $i$ 的这一位上无论取 $1$ 还是 $0$，最大异或值一定为 $1$。后面更低位部分就贪心地取两种情况的较小值。

这样就能做到答案最小。

但是直接枚举复杂度过高，可以使用 01-Trie 维护每个位上是否有数该位为 $1$ 和 $0$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,a[maxn];
namespace Trie{
	const int siz=6e6+10;
	int son[siz][2],sz=1;
	void push(int x){
		int p=1;
		for(int i=29;i>=0;i--){
			bool e=x&(1<<i);
			if(son[p][e]) p=son[p][e];
			else p=son[p][e]=++sz;
		}
	}
	int query(int x,int dep){
		if(son[x][0] && son[x][1]){
			return min(query(son[x][0],dep-1),query(son[x][1],dep-1)) + (1<<dep);
		}
		else if(son[x][0]){
			return query(son[x][0],dep-1);
		}
		else if(son[x][1]){
			return query(son[x][1],dep-1);
		}
		else return 0;
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		Trie::push(a[i]);
	}
	cout<<Trie::query(1,29)<<"\n";
	return 0;
}
```
[AC record](https://www.luogu.com.cn/record/196610941)

---

## 作者：Claire0918 (赞：0)

我们注意到对一个数 $a$ 异或上一个数 $x$，实际上相当于将 $a$ 和 $x$ 写作二进制，如果 $x$ 在某一位上的值为 $1$，则将 $a$ 的该位取反，否则不改变该位。

我们又注意到一个显然的性质：$a < b$，当且仅当存在极高的一位，使得在该位上 $a$ 为 $0$ 且 $b$ 为 $1$，且在该位之前 $a$ 和 $b$ 在每一位上都相同，所以我们只需要贪心地优先考虑高位尽量小即可。

结合上述两条性质，我们想到将 $a_i$ 写作二进制。如果在某一位上所有 $a_i$ 的值都相同，则我们可以将该位全部变为 $0$，且这样一定是不劣的。否则，在这一位无法确定是否取反更优，但可以确定该位一定为 $1$，随后分别按照取反和不取反递归到更低一位使后面取得最小值即可。

时间复杂度 $\mathcal{O}(n\log a)$。

Code：
```cpp
#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a));

using namespace std;

const int maxloga = 30;

int n;
vector<int> a;

inline int dfs(int mov, vector<int> a){
    if (mov < 0){
        return 0;
    }
    vector<int> nex[2];
    for (auto x: a){
        nex[x >> mov & 1].push_back(x);
    }
    if (nex[0].empty()){
        return dfs(mov - 1, nex[1]);
    }
    if (nex[1].empty()){
        return dfs(mov - 1, nex[0]);
    }
    return min(dfs(mov - 1, nex[0]), dfs(mov - 1, nex[1])) + (1 << mov);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        int a;
        scanf("%d", &a);
        ::a.push_back(a);
    }
    printf("%d", dfs(maxloga, a));

return 0;
}
```

---

## 作者：_JF_ (赞：0)

[[ABC281F] Xor Minimization](https://www.luogu.com.cn/problem/AT_abc281_f)

诶，原来我也可以切 dp 题。

看到位运算，很自然的想到按位考虑。

我期望最后的值最小，那么我们对于原序列里面的数，如果对于当前位置，序列里边该位都是 $0$ 或者 $1$ 的话，我们可以钦定 $X$ 该位让这一位不产生贡献。

但是如果原序列对应的数里面该位有 $0$ 又有 $1$，那么无论我怎么钦定 $X$ 的当前位，这一位都必然会对答案产生贡献。

这时候开始考虑考虑选 $0$ 还是选 $1$。

我开始还是考虑贪心，就不妨对当前剩余的数中位是 $0$ 或 $1$ 的分组，我们看那个组的数会在后续的位中第一次出现有 $0$ 和 $1$ 更后的那组即可。

但是这么贪心有缺陷。因为如果找到的那个位置还是一样，那就很难处理了。

于是转换一个思路，因为问道最值，所以我们可以考虑 dp。

可能把他拍到 trie 上会形象些，虽然你不拍也行。

设 $dp_{u,0}$ 表示当前点开始边权为 $0$ 的最小代价，以及 $dp_{u,1}$ 表示走边权为 $1$ 的最小代价。

如果当前有两个儿子，那就必然会产生分叉，贡献就是
$2^{30-dep[u]}$。

转移情况如下：

- 如果当前有边权为 $0$ 的儿子，那么有：$dp_{u,0}+=\min({dp_{v0,0},dp_{v0,1}})$。

- 如果当前没有边权为 $0$ 的儿子，必然没有选边权为 $1$ 的优秀，给他赋 $dp_{u,0}=2^{30-dep[u]}$。

- 如果当前有边权为 $1$ 的儿子，那么有：$dp_{u,1}+=\min({dp_{v1,0},dp_{v1,1}})$

- 如果当前没有边权为 $1$ 的儿子，同理，有 $dp_{u,0}=2^{30-dep[u]}$。

还有双倍经验，[CF1285D](https://www.luogu.com.cn/problem/CF1285D)。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =7e6+10;
// #define int long long
int dp[N][2],ch[N][3],a[N],dep[N],pre,n,ans;
void build(int x){
	int p=0;
	for(int i=29;i>=0;i--){
		int now=(a[x]>>i&1);
		if(!ch[p][now])	ch[p][now]=++pre;
		p=ch[p][now];
	}
}
void init(int u,int fath){
	int v1=ch[u][0],v2=ch[u][1]; dep[u]=dep[fath]+1;
	if(v1==0&&v2==0)	return ;
	else if(v1==0)	init(v2,u),dp[u][0]=(1<<(30-dep[u])),dp[u][1]=min(dp[v2][1],dp[v2][0]);
	else if(v2==0)	init(v1,u),dp[u][0]=min(dp[v1][1],dp[v1][0]),dp[u][1]=(1<<(30-dep[u]));
	else dp[u][0]+=(1<<(30-dep[u])),dp[u][1]=dp[u][0],init(v1,u),init(v2,u),dp[u][0]+=min(dp[v1][0],dp[v1][1]),dp[u][1]+=min(dp[v2][0],dp[v2][1]);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)	cin>>a[i],build(i);
	init(0,0),cout<<min(dp[0][0],dp[0][1])<<endl;
	return 0;
}
```

---

## 作者：_shine_ (赞：0)

考虑对每一个进行二进制拆分。

因为异或 $x$ 后整个的最大值最小，所以根据这个条件和异或后只会影响到每一位（二进制下异或特定一位不会造成其他变更），所以说对于每一个都要拆分出来单独考虑。

设当前数为 $x$，且到了 $x$ 二进制下的第 $y$ 位 $j$，则可以发现最优的方案就是异或 $j$（异或又称作不进位加法，所以说当 $j$ 为 $0$ 和 $1$ 时分别异或 $0,1$ 时就能得到最小值），那么对于这里所有的 $a_i$ 中的第 $y$ 位组合起来就只有三种情况（这里现设所有 $a_i$ 中的第 $y$ 位拼起来排序后的零一串为 $st$）：

1. 当 $st$ 为 $000\dots 00$ 时，$x$ 的第 $y$ 位为 $0$。

1. 当 $st$ 为 $111\dots 11$ 时，$x$ 的第 $y$ 位为 $1$。

1. 当 $st$ 为 $000\dots 00111\dots11$ 时，这种情况无论如何最后都肯定有数的第 $y$ 位会有 $1$，所以要两种情况都进行讨论，可以分别枚举为 $0$ 和 $1$ 的情况进行处理即可。

---

## 作者：taojinchen (赞：0)

# 思路
首先看见异或，考虑零一字典树。

我们先把每一个新节点插入零一字典树，没有很多特殊处理。插入完了以后从根开始分类讨论，如果这个节点只有一个子节点，很明显这一位的异或值等于零。
如果有两个，直接两边各跑一遍，取最小加上一个值，这一个值是这一个二进制位的计数单位。如果是叶子节点，直接返回零。
# 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int kM=5e6+5;//≈30×(1.5×10^5)+一点点
ll n,i,j,x,ret,cnt[kM],dis[kM],tr[kM][2];
void ins(ll x){//插入新元素
  ll s=0;
  for(j=30;~j;j--){
    bool t=(1<<j)&x;//判断是走0还是1
    if(tr[s][t]==0){
      dis[++ret]=(1<<(j-1));//如果异或不等于0，加上这个数（只有这里是特殊处理）
      tr[s][t]=ret,s=ret;//移动到子节点
    }
    else s=tr[s][t];//移动到子节点
    cnt[s]++;//记录
  }
  return;
}
ll dfs(ll rt){
  if(tr[rt][0]){
    if(tr[rt][1]){
      return min(dfs(tr[rt][1]),dfs(tr[rt][0]))+dis[rt];//异或值不等于0
    }
    else return dfs(tr[rt][0]);//这一位的异或值可以等于0
  }
  else if(tr[rt][1]){
    return dfs(tr[rt][1]);//这一位的异或值可以等于0
  }
  return 0;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(i=1;i<=n;i++){
    cin>>x;
    ins(x);
  }
  cout<<dfs(0);
  return 0;
}
```


---

## 作者：cwfxlh (赞：0)

## [题面传送门](https://www.luogu.com.cn/problem/AT_abc281_f)
题意不多赘述。  

我们首先将每一个数都拆分成若干个二进制为来看（不够的补零），因为每一位之间互不影响，所以可以一位一位处理。  

题面要使异或后最大值最小，那我们只用考虑最大值。从高位向低位考虑，每一位的数要么都反转，要么都不变，反转后 0 变 1，1 变 0。可以看出一点，选择反转，那么最大值一定会集中到当前位是 0 的那一边，否则集中在当前位是 1 的那一边。这里已经可以看出来分治了。那么我们两种情况都进行考虑：如果不反转，找到 1 侧的数去掉当前位后异或的最大值的最小情况；否则找到 0 侧的数去掉当前位后最大值的最小值。两种情况取小即可。    


写一个分治就完事啦，很有意思的一道题。       

另外在分治前要排一边序，这样处理当前区间更方便。      

上代码：     
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
long long a[400003];
int finf(long long w,int l,int r)
{
	int lft=l,rgt=r,mid;
	while(lft<rgt)
	{
		mid=((lft+rgt)>>1)+1;
		if((a[mid]&(1<<w))==0)lft=mid;
		else rgt=mid-1;
	}
	return lft;
}
long long dfs(long long w,int l,int r)
{
	if((a[l]&((1<<(w+1))-1))==(a[r]&((1<<(w+1))-1)))return 0;
	int k1=w;
	while(k1>0&&((a[l]&(1<<k1))==(a[r]&(1<<k1))))
	{
		k1--;
	}
	int k2=finf(k1,l,r);
	return (1<<k1)+min(dfs(k1,l,k2),dfs(k1,k2+1,r));
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
	sort(a+1,a+n+1);
	printf("%lld",dfs(30,1,n));
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

此题可以贪心地从 `M`  的二进制表示下的最高位开始考虑。

若序列中每个 $a_k$ 的第 $i$ 位都是 $1$ 或 $0$，那么我们可以直接将 `M` 的第 $i$ 位置为 $0$。

否则，`x` 的第 $i$ 位可以分为 $0$ 或 $1$ ，显然此时 `M` 的最小值一定 $⩾2^i$ 。当 `x` 的第 $i$ 位为 $0$ 时，只考虑 $a_k$ 的第 $i$ 位为 $11$ 时的 `M` 的**最小值** $+2^i$；当 `x` 的第 $i$ 位为 $1$ 时，只考虑 $a_k$ 的第 $i$ 位为 $0$ 时的 `M` 的最小值 $+2^i$，然后取这两者中**较小**的那个即可。

先对原序列进行升序排序，然后递归地从高位开始用 `x` 是 $0$ 还是 $1$ 进行分治，从而求得 `M` 的最小值。

时间复杂度 $O(N(\log N+30))$。

### 代码
```
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); ++i)
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    rep(i, n) cin >> a[i];
    sort(a.begin(), a.end());
    function<int(int, int, int)> f = [&](int k, int l, int r) {
        if (k == -1) return 0;
        int mid = r;
        for (int i = l; i < r; ++i) {
            if (a[i]>>k&1) {
                mid = i;
                break;
            }
        }
        if (mid == l or mid == r) return f(k-1, l, r);
        int x = f(k-1, l, mid);
        int y = f(k-1, mid, r);
        return min(x, y) + (1<<k);
    };
    int ans = f(29, 0, n);
    cout << ans << '\n';

    return 0;
}
```

$\operatorname{log}$已修正，求过。

---

