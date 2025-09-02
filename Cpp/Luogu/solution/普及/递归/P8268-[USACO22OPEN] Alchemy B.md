# [USACO22OPEN] Alchemy B

## 题目描述

总是热衷于培养新的爱好的奶牛 Bessie 正在学习如何转化金属。对于 $1 \le i \le N \le 100$，她有 $a_i$（$0 \le a_i \le 10^4$）单位的金属 $i$。此外，她知道 $K$（$1\le K< N$）个配方，她可以融合若干种金属各一单位，制造一单位编号大于所有被融合金属的金属。另外保证，对于每种金属，Bessie 最多知道一种制造该金属的配方。

计算经过一系列转化后，Bessie 可能拥有的金属 $N$ 的最大单位数。

## 说明/提示

【样例解释】

在这个例子中，以下是一种最优的转化方式：

- 将一单位金属 1 转化为金属 2。
- 将一单位金属 2 转化为金属 3。
- 将一单位金属 3 和金属 4 转化为金属 5。

现在 Bessie 还有一单位金属 1 和一单位金属 5。她无法再制造更多的金属 5。

【测试点性质】

- 测试点 2 中，对于 $1\le i< N$，一单位金属 $i$ 可以被转化为一单位金属 $i+1$；

- 测试点 3-4 中，每个配方均将一单位的一种金属转化为另一种金属；

- 测试点 5-11 没有额外限制。

## 样例 #1

### 输入

```
5
2 0 0 1 0
3
5 2 3 4
2 1 1
3 1 2```

### 输出

```
1```

# 题解

## 作者：I_am_Accepted (赞：12)

### Preface

咱就是说，题目中 $n$ 良心地开小了……配方中的反应物数量总和（设为 $m$）应该可以开到 $10^5$ 级别。

### Analysis

从每个配方的生成物向反应物连有向边，发现是 DAG。因为每种材料用于生成不同材料的量不同，比较难办，我们采用**二分答案**。

假设当前我们二分到答案为 $A$。设 $b_i$ 为第 $i$ 种材料需要的量。初始化 $b_i=0\ (i<n)$ 而 $b_n=A$。

然后我们从 $n$ 到 $1$ 枚举材料 $x$：

* 若 $b_x\le a_x$，那直接跳过 $x$，因为已经够用了。

* 否则，枚举 $x$ 的出边到达的点 $y$，执行 $b_y\ +\!\!=b_x-a_x$（注意是 $+\!\!=$），表示 $y$ 节点还需要空出 $b_x-a_x$ 的量来生成材料 $x$。 

* 当然，如果 $x$ 没有出边（不能被制造），判断无解。

若无无解则为有解。

时间

$$O\left((n+m)\log\sum_{i=1}^{n}a_i\right)$$

### Detail

注意 $b$ 数组可能会爆 long long，所以当有 $b_i$ 过大直接判无解即可。

### Code

```cpp
//Said no more counting dollars. We'll be counting stars.
#include<bits/stdc++.h>
using namespace std;
#define pb emplace_back
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define For(i,j,k) for(int i=j;i<=k;i++)
#define Rof(i,j,k) for(int i=j;i>=k;i--)
#define int long long
#define N 102

int n,a[N],b[N],p[N];
vector<int> e[N];
priority_queue<int> q;
bool check(int x){
	For(i,1,n) b[i]=(i==n?x:0);
	Rof(i,n,1){
		if(b[i]>a[i] && e[i].empty()) return false;
		if(b[i]<=a[i]) continue;
		if(b[i]-a[i]>p[i-1]) return false;
		for(int j:e[i]){
			b[j]+=b[i]-a[i];
		}
	}
	return true;
}
signed main(){IOS;
	cin>>n;
	For(i,1,n) cin>>a[i];
	For(i,1,n) p[i]=p[i-1]+a[i];
	int q,x,y,z;
	cin>>q;
	while(q--){
		cin>>x>>y;
		while(y--){
			cin>>z;
			e[x].pb(z);
		}
	}
	int l=a[n]+1,r=0,mid,res=a[n];
	For(i,1,n) r+=a[i];
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid)) res=mid,l=mid+1; 
		else r=mid-1;
	}
	cout<<res<<endl;
return 0;}
```

---

## 作者：dts_std (赞：11)

### 更新日志

upd on 2022.5.18：规范 $LeTeX$ 公式。

upd on 2022.5.23：修改小错误，再次规范版面，丰富后记内容。

[题目传送门](https://www.luogu.com.cn/problem/P8268)

### 题目大意

奶牛有 $n$ 种金属，第 $i$ 种金属有 $a_{i}$ 个。现在告诉你每种金属的数量和 $k$ 个合成表，问你最多合成多少个第 $n$ 种金属。

~~我怎么想到了MC中的工作台啊。。。~~

### 解法

话不多说，向上解法，再解释。

我用了递归解决本题。

先把原来就有的 $n$ 号金属拿去，然后考虑合成。遍历制作 $n$ 号金属的合成表，能做几个就做几个。如果哪个金属没有了，再看它的合成表，可以做的话就做**一个**（注意：只做一个！），能再做一个 $n$ 号就再做一个。如果还能再做一个，就继续做，以此类推。

那该如何判断能不能做呢？这就要用到深搜的思想了。如果 $n$ 号金属缺材料，那么就看缺的材料的合成表。如果还缺，就继续看；如果不缺，就做一个。如果缺的材料无法制作，那就做不下去了。这时就可以输出答案了。

### 对解法的解释（Q&A）

Q1：为什么要用递归？

A1：因为判断的时候类似（其实就是）深搜，用递归最方便。当然，用栈也可以。

Q2：为什么每次只做一个？一起做不香吗？

A2：~~因为不这样弄会WA。~~

我们来着重回答为什么会WA。

先看一个输入栗子：

```
3
2 0 0
2
3 2 1 2
2 1 1
```

简单解释一下：

奶牛有 $3$ 种金属，$1$ 金属有 $2$ 个，$2$ 金属有 $0$ 个，$3$ 金属有 $0$ 个

共 $2$ 个合成表，合成表为：

1. 一个 $1$ 金属和一个 $2$ 金属可以合成一个 $3$ 金属；

2. 一个 $1$ 金属可以合成一个$2$ 金属。

如果我们采用能做就全做的方式做金属的话，步骤是这样的：

1. 发现缺 $2$ 金属；

2. 把所有 $1$ 金属做成 $2$ 金属；

3. 误以为材料够做两个 $3$ ，于是输出了 $2$，~~高高兴兴地WA~~。

即使第三步加了个判断：

此时缺 $1$，而 $1$ 无法制作，误以为无法制作 $3$ ，于是输出 $0$，~~又高高兴兴地WA~~。

这下我们就可以知道这种方法的错误之处了。若采用一次做全部的策略，有可能把原来需要的材料全用掉，使其不满足条件，但少用一些可能可以制作，这就导致了误判。

若一个一个做金属，步骤就是这样的：

1. 发现缺 $2$ 金属；

2. 把一个 $1$ 金属做成 $2$ 金属；

3. 此时奶牛有 $1$ 个 $1$ 金属和 $1$ 个 $2$ 金属，把他们做成 $1$ 个 $3$ 金属；

4. 发现不能再做了，输出 $1$ 。

所以答案为 $1$。

我们可以从此看出，一个一个做金属，就可以少用原材料，把能做的情况全考虑到，若这时还不能做，那是真不能做了。

Q3：该算法时间复杂度多少？有更快的方法吗？

A3：举个最坏情况的栗子：

```
5
5 0 0 0 0
4
2 1 1
3 2 1 2
4 3 1 2 3
5 4 1 2 3 4
```

对于第 $i$ 种金属，最坏遍历它前面的 $i-1$ 块金属，又因为这是一个一个制作的，所以次数还和 $a_{i}$ 的最大值有关，时间复杂度为 $O \left (n^2 \cdot \max_{1\le i\le n} a_{i} \right )$。

若你们想要更快的方法，请看楼下的二分答案。

### 代码

~~我知道你们只看这个~~

其中 $a$ 数组表示现有金属数，$b$ 数组表示合成表，$dfs$ 函数的返回值表示是否能合成第 $k$ 个金属。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
long long a[110],b[110][110];
bool dfs(long long k){
	if(a[k]>0) return true;
	if(b[k][0]==0) return false;//当没有该种材料且无法合成它时，返回false
	long long i;
	for(i=b[k][0];i>=1;i--){/*这里一定要倒着扫，因为如果顺着扫，
后面dfs的过程中可能会用掉前面做好的材料，导致WA。若倒着扫，即使
后面的dfs用掉了前面的材料，前面还会再补上*/
		if(!dfs(b[k][i])) return false;//无法合成
	}
	for(i=1;i<=b[k][0];i++){//如果能合成，做一个
		a[b[k][i]]--;
	}
	a[k]++;
	return true;
}
int main(){
	long long n,k,i,j,t,ans=0;
	scanf("%lld",&n);
	for(i=1;i<=n;i++){
		scanf("%lld",&a[i]);
	}
	scanf("%lld",&k);
	for(i=1;i<=k;i++){
		scanf("%lld",&t);
		scanf("%lld",&b[t][0]);
		for(j=1;j<=b[t][0];j++){
			scanf("%lld",&b[t][j]);
		}
	}
	ans=a[n];a[n]=0;
	while(dfs(n)){
		ans++;
		a[n]=0;
	}
	printf("%lld",ans);
	return 0;
}
```


[AC记录](https://www.luogu.com.cn/record/75893019)

### 后记

尽管我觉得递归才是正解，但人家二分答案就是快。

引用一下我们老师说的名言：

空间复杂度是你竞争的底线，时间复杂度是你竞争的目标。

再引用一下洛谷上别人（忘了是谁）说的名言：

题解千万条，理解第一条。如果直接抄，棕名两行泪。

---

## 作者：lsj2009 (赞：9)

## 题目大意
<https://www.luogu.com.cn/problem/P8268>。
## 思路

在我看来，这是一道递归好题。

我们来考虑怎样查询 $x$ 金属是否能够生产（或者已经有 $x$ 金属）：

- 如果本身就有 $x$ 金属，将 $x$ 金属个数 $-1$，返回 ``true``；

- 如果本身没有 $x$ 金属且没有 $x$ 金属的生产配方，返回 ``false``；

- 如果本身没有 $x$ 金属且有 $x$ 金属的生产配方，则询问生产配方里的每个金属是否能够生产（或者已经有该金属），若均能生产，则返回 ``true``，反之返回 ``false``。


由于 $x$ 金属的配方 $\le 1$ 个且能制造 $x$ 金属的金属的编号全部 $< x$，则，我们可以将制造 $n$ 金属的****生产过程****构成一棵树。

当然，其中有一点点小小的问题：如果没有 $x$ 金属但有 $x$ 金属的生产配方，则我们之前对 $x$ 生产配方里的每个金属也进行了询问，其中极有可能会有能够生产的，则那些能够生产的金属的数量不是减去了一点吗？但是那些金属最终并没有被用于生产 $x$ 金属上，则那些金属不是被浪费了吗？

事实上，不需要担心此类事情的发生，因为在生产 $x$ 金属的过程中，一旦有其中一个金属无法生产，则 $x$ 金属也无法生产，递归也就没法继续进行，所以我们不需要担心那些被浪费的金属。

## Code:
```cpp
#include<bits/stdc++.h>
#define pd push_back
#define pb pop_back
#define mk make_pair
//#define int long long
#define PII pair<int,int>
#define _for(a,b,c) for(int a=b;a<=c;a++)
#define _rep(a,b,c) for(int a=b;a>=c;a--)
using namespace std;
template <typename T> inline void read(T& x) {
	x=0; T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { x=(x<<1)+(x<<3)+(ch&15); ch=getchar(); }
	x=x*f;
	return;
}
template <typename T,typename ...Arg> inline void read(T& x,Arg& ...arg){
	read(x); read(arg...);
}
int power(int a,int b) {
	int ans=1;
	do {
		if(b&1) ans*=a; a*=a;
	} while(b>>=1);
	return ans;
}
const int N=105;
int a[N],n,k;
vector<int> v[N];
bool Solve(int x) {
    if(a[x]) return a[x]--; //本身就有 x 金属（这里运用了非 0 值在 bool 中 =1 的特性）
	if(v[x].empty()&&!a[x]) return 0; //没有 x 金属且没有生产 x 金属的配方
	_for(i,0,v[x].size()-1) //没有 x 金属，但有 x 金属的配方
		if(!Solve(v[x][i]))
		    return 0;
	return 1;
}
signed main() {
	read(n);
	_for(i,1,n)
		read(a[i]);
	read(k);
	while(k--) {
		int l,m;
		read(l,m);
		while(m--) { //l 金属的配方
			int x; read(x); v[l].pd(x);
		}
	}
	int ans=0;
	while(Solve(n)) //当能生产 x 金属时一直生产
		ans++;
	printf("%d",ans);
	return 1;
}
```
接下来我们来谈一谈一下为什么不能直接查询能生产的 $x$ 金属的个数而是查询能否生产 $x$ 金属。

题目并没有规定一个金属只能出现在一个金属的生产配方中。

举个栗子，我们假定生产 $x$ 金属需要 $x_1$ 和 $x_2$ 金属，而生产 $x_1$ 金属需要 $x_3$ 和 $x_4$ 金属，生产 $x_2$ 需要 $x_3$ 和 $x_5$ 金属。

可以发现，生产 $x_1$ 和 $x_2$ 金属均需要使用 $x_3$ 金属，如果我们将 $x_3$ 全部用于生产 $x_1$ 金属上，则 $x_2$ 金属就无法生产，而没有 $x_2$ 金属就无法生产 $x$ 金属。

### Hack:
```
6
4 4 4 0 0 0
3
6 2 4 5
5 2 1 2
4 2 1 3
```

时间复杂度应为 $\Theta(\sum a_i)$。

---

## 作者：yzyjh (赞：4)

蒟蒻又来写题解了 $awa$

思路是这样的,每个金属只能被编号比他小的金属合成,从 $n$ 号金属开始搜索,先看看能合成出多少 $n$ 号金属,能合成多少合成多少，如果合成不了了,思考它的成分,如果缺的那个成分能合成出一份就合成一个,然后接着合成金属 $n$ ,直到不能合成,理论上最坏的复杂度就是 $n*n*max(ai)$


下面就是 $code$ 了：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105],leaf; 
vector<int>edge[105];
void dfs(int num)//dfs寻找最多可能数量
{
	if(edge[num].size()==0)return ;
	int mn=INT_MAX,i,j,to;
	while(1)
	{
		mn=INT_MAX;
		for(i=0;i<edge[num].size();i++)
		{
			to=edge[num][i];
			mn=min(a[to],mn);
		}
		if(mn==0)
		{
			for(i=edge[num].size()-1;i>=0;i--)
			{
				to=edge[num][i];
				if(a[to]==0)
					dfs(to);
				if(a[to]==0)
					return ;
			}
		}
		if(num==n)
		{
			a[num]+=mn;
			for(i=0;i<edge[num].size();i++)
			{
				to=edge[num][i];
				a[to]-=mn;
			}
		}
		else
		{
			a[num]++;
			for(i=0;i<edge[num].size();i++)
			{
				to=edge[num][i];
				a[to]-=1;
			}
			return ;
		}
	}
}
int main()
{
	int i,j,s,k,l,m;
	cin>>n;
	for(i=1;i<=n;i++)cin>>a[i];
	cin>>k;
	for(i=1;i<=k;i++)//读入配方
	{
		scanf("%d%d",&l,&m);
		for(j=1;j<=m;j++)
		{
			scanf("%d",&s);
			edge[l].push_back(s);
		} 
	}
	for(i=1;i<=n;i++)//将每个需要的数量进行排序
	{
		sort(edge[i].begin(),edge[i].end());
	}
	dfs(n); 
	cout<<a[n]<<endl;
	return 0;
}

```


---

## 作者：WorldHim (赞：1)

[在博客园阅读](https://www.cnblogs.com/WorldHim/p/solution-luogu-p8268.html) [在洛谷上阅读](https://www.luogu.com.cn/blog/worldhim/solution-p8268) 

## Part 0 题意简述

### [原题](https://www.luogu.com.cn/problem/P8268)

给出拥有的金属数量与金属配方，求金属 $N$ **最大能合成的数量**。

## Part 1 题目分析

首先，金属 $i$ 能配出的最大数量只和**它的原数量**和**它的配方中能合成的数量**有关。

所以我们应该能想到递归，可以使用一个 `bool` 类型的递归函数来返回合成是否可行：

1. 如果有金属 $i$，返回可行并减去一份金属 $i$；
2. 如果没有金属 $i$ 且没有配方，则返回不可行；
3. 如果没有金属 $i$ 有配方就递归配方所需金属 $r$；
   1. 有任一不可行，返回不可行；
   2. 所有可行，返回可行。

## Part 2 代码

根据上方分析，可以写出递归函数：

```cpp
// vector<int> recipe[100+20];
bool dfs(int metal){
	if(a[metal]){ //情况 1
		a[metal]--;
		return 1;
	}
	if(recipe[metal].empty()) //情况 2
		return 0;
	for(auto it:recipe[metal]) //情况 3
		if(!dfs(it))
			return 0; //情况 3-1
	return 1; //情况 3-2
}
```

结合其他部分，写出完整代码：

```cpp
#include<iostream>
#include<vector>
using namespace std;
const int MAXN=1e2+20;
vector<int> recipe[MAXN];
int n,k;
int l,m;
int a[MAXN],ans;
inline bool dfs(int metal){
	if(a[metal]){
		a[metal]--;
		return 1;
	}
	if(recipe[metal].empty())
		return 0;
	for(auto it:recipe[metal])
		if(!dfs(it))
			return 0;
	return 1;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	cin>>k;
	while(k--){
		cin>>l>>m;
		while(m--){
			int metal;
			cin>>metal;
			recipe[l].push_back(metal);
		}
	}
	ans=a[n],a[n]=0;
	while(dfs(n))
		ans++;
	cout<<ans;
	return 0;
}
```

## Part 3 对其他题解的 Hack

因为题目中没有保证配方金属按顺序排列，所以可以造出以下数据：
输入：

```
3
1 0 0
2
2 1 1
3 2 2 1
```

输出（正解）：
`0`

输出（错误）：
`1`

被 Hack 的题解：
[kbzcz 题解](https://www.luogu.com.cn/blog/kbzcz/solution-p8268)
[dts_std 题解](https://www.luogu.com.cn/blog/weilaibok/solution---p8268)

---

