# [USACO25JAN] Table Recovery S

## 题目描述

Bessie 有一个 $N\times N$（$1\le N\le 1000$）的加法表，其中对于所有 $1\le r,c\le N$，第 $r$ 行第 $c$ 列的方格中的整数为 $r+c$。例如，对于 $N=3$，表格如下所示：

```
2 3 4
3 4 5
4 5 6
```

不幸的是，Elsie 得到了这张表格，并通过执行若干次以下三种类型的操作对表格进行了变换。

1. 交换两行；
2. 交换两列；
3. 选择两个同时存在于表格中的值 $a$ 和 $b$，然后同时将每一个 $a$ 更改为 $b$，每一个 $b$ 更改为 $a$。

Elsie 总是按类型顺序执行操作；也就是说，她首先执行任意数量（可能为零）的类型 $1$ 操作，然后是类型 $2$ 操作，最后是类型 $3$ 操作。

请帮助 Bessie 恢复 Elsie 在执行完所有类型 $1$ 和 $2$ 操作后，但在执行任意类型 $3$ 操作之前，表格的一种可能状态。可能存在多种可能的答案，在这种情况下你应当输出字典序最小的答案。

按字典序比较两个表格时，比较它们在自然顺序（行间从上到下，行内从左到右）下读取时第一个不同的项。

## 说明/提示

### 样例解释

#### 样例 #1

无论 Elsie 执行什么操作表格均不会改变。

#### 样例 #2

以下是 Elsie 可能执行的一种操作序列。

```text
2 3 4
3 4 5
4 5 6
-> （操作 2：交换列 2 和 3）
2 4 3
3 5 4
4 6 5
-> （操作 2：交换列 1 和 2）
4 2 3
5 3 4
6 4 5
-> （操作 3：交换值 2 和 3）
4 3 2
5 2 4
6 4 5
-> （操作 3：交换值 3 和 4）
3 4 2
5 2 3
6 3 5
```
注意：以下也是经过类型 1 和 2 操作后表格的一种可能状态，但它不是字典序最小的，因为第一行的第二项比正确答案中的要大。
```
4 6 5
3 5 4
2 4 3
```

### 子任务

- 测试点 4-5：$N\le 6$。
- 测试点 6-7：$N\le 8$。
- 测试点 8-11：$N\le 100$。
- 测试点 12-15：没有额外限制。

## 样例 #1

### 输入

```
1
2```

### 输出

```
2```

## 样例 #2

### 输入

```
3
3 4 2
5 2 3
6 3 5```

### 输出

```
4 2 3
5 3 4
6 4 5```

## 样例 #3

### 输入

```
6
8 10 5 6 7 4
12 11 10 4 8 2
5 4 6 7 9 8
10 2 4 8 5 12
6 8 7 9 3 5
4 12 8 5 6 10```

### 输出

```
7 5 8 9 10 6
4 2 5 6 7 3
8 6 9 10 11 7
5 3 6 7 8 4
9 7 10 11 12 8
6 4 7 8 9 5```

# 题解

## 作者：Lavaloon (赞：8)

由于笔者认为本题过于 Ad-hoc，故在此给出一种非官解的、硬分析的解法。笔者认为其更加系统且无脑。

**首先考察一个表格可以通过操作 1,2 变换成原始矩阵的充要条件。**

模拟这个过程，初始表格 $A_{i,j}=i+j$，经过一次行交换（不妨设交换了第 $s$ 行和第 $t$ 行），那么 $A_{s,j}=t+j$，而 $A_{t,j}=s+j$。

在这一部分，读者可以感觉到，将行重新排列后（不妨设新表格的第 $i$ 行为原表格的第 $p_i$ 行），$A_{i,j}=p_i+j$。

同理在此基础上模拟列交换（不妨设新表格的第 $i$ 列为原表格的第 $q_i$ 列），$A_{i,j}=p_i+q_j$。

这实际上是说，$p,q$ 两排列可以与一个进行完行列交换的表格一一对应。

于是我们仅需检查能否将给定表格进行操作 3 后是否存在这样的 $p,q$ 即可。

**其次考察一个表格可以通过操作 3 变换成给定矩阵的充要条件。**

那显然是，之前不同色的，后来仍不能同色；而之前同色的，后来必定同色。

这个条件第一眼好像没有提示我们任何东西。

你此时可以直接选择另一种思考角度，比如出现次数最小的数一定在原表格中是 $1$ 或 $2n+2$，出现次数最大的数一定在原表格中是 $n+1$（此时你也可以发现原值为 $n+1$ 的必定在每行每列均有恰好一个，故在确定 $p,q$ 之一后就可以推出另一个，这是依据 $A_{i,j}=p_i+q_j=n+1$ 的性质得到的。这实际上可以用于合法性检查）。

联系上面的那个结论，我们推广得：出现次数为 $k$ 次的数在原表格中一定是 $k+1$ 或 $2n+1-k$。

那么给定表格中的每个数有两种候选的原值，现在我们欲使其满足通过操作 1,2 变换成原始矩阵的充要条件的同时最小化字典序。

通过操作 1,2 变换成原始矩阵的充要条件仍然难以判定，那么我们考虑**弱化条件，去考虑满足该条件的表格具有的性质。**

感性理解层面，可以将这个充要条件理解为，两个一维数组搞出来了一个二维数组，且只与 $i,j$ 相关。这说明其势必具有更加优秀的性质。

通过观察样例或直接进行分析，可以得出：**位于同一列且位于相邻两行的数的差恒定，位于同一行且位于相邻两列的数的差恒定。**

证明非常容易：$A_{i,j}-A_{i-1,j}=p_i+q_j-p_{i-1}-q_j=p_i-p_{i-1}$，与 $j$ 完全无关。

在此基础上，结合“每个数有两种候选的原值”的推论，**一个约束可以把 $p_{i}-p_{i-1}$ 和 $q_i-q_{i-1}$ 的可取的值缩小到不多于 $4$ 个，其中有两对必为相反数。**

举个例子：在第三组样例中，$10$ 的原值是 $5$ 或 $9$，而 $5$ 的原值是 $6$ 或 $8$，那么这给出，$q_3-q_2=5-6$ 或 $5-8$ 或 $9-6$ 或 $9-8$。

那么就容易想到把所有对应约束取交，求得完全可行的 $p_{i}-p_{i-1}$ 和 $q_i-q_{i-1}$ 的取值。

而对于一个确定的 $i$，对 $p_{i}-p_{i-1}$ 或 $q_i-q_{i-1}$ 的限制互不相同。这意味着，**所有约束可取的值取交后，真正可行的值恰为 $2$ 个且互为相反数**。如下图的橙色字体所示。

![](https://cdn.luogu.com.cn/upload/image_hosting/zr7idx3p.png)

**接下来你要做的就是，为这些橙色部分选择合适的正负号，使得生成的表格合法且字典序最小。**

上图中画出的黄绿色路径代表了所有可行的转移，其具有启发意义。**实际上就是走出一条合法的黄绿色路径且最小化字典序**。比如答案走出的路径为：$7\rightarrow 5\rightarrow 8\rightarrow 9\rightarrow 10\rightarrow 6$。

事实上黄绿色路径的形式是非常单一的，在两数之间，其往往是两条或者四条边，且对于两数之间恰有两条边的情况，这两条边一定由不同的数指向不同的数，而对于两数之间恰有四条边的情况，这种情况很少，在一行中不会出现超过两次。因为若出现这种路径，则边的一侧必然为 $n+1$，然而给定表格中每行必然不存在重复数字，否则一定无解。或者你也可以直接把上图中红色和蓝色的 $7$ 当成一个点，这样直接规避掉了两数之间恰有四条边的情况。

综上我们证明了，**合法路径数量是 $\mathcal{O}(1)$ 级别的**，因此可以直接爆搜出来检查合法性。找到字典序最小的路径同样是简单的。

总结算法流程：

- 求出每个位置的可能原值；
- 对相邻两列的可能差值求交；
- 爆搜找出所有黄绿色路径并判断合法性；
- 取字典序最小的合法路径，构造答案并输出之。

综上，时间复杂度 $\mathcal{O}(N^2)$。 

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<string>
#include<cmath>
#include<array>
#include<unordered_map>
#include<vector>
#include<bitset>
#include<queue>
#include<set>
#include<map>
#include<ctime>
#include<random>
#include<numeric>
using namespace std;
#define int long long
#define ll long long
#define ull unsigned long long
#define lc (x<<1)
#define rc (x<<1|1)
#define pii pair<int,int>
#define mkp make_pair
#define fi first
#define se second
const int Mx=2005;
int read(){
	char ch=getchar();
	int Alice=0,Aya=1;
	while(ch<'0'||ch>'9'){
		if(ch=='-') Aya=-Aya;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
		Alice=(Alice<<3)+(Alice<<1)+(ch^48),ch=getchar();
	return (Aya==1?Alice:-Alice);
}
int n;
int a[Mx][Mx],A[Mx][Mx];
int cnt[Mx];
int rev[Mx][2];
int d[Mx];
vector<pii>pos[Mx];
int D;
int p[Mx],q[Mx];
int vis[Mx];
int f[Mx][2];
void Check(){
	for(int i=1;i<=n+n+2;i++) vis[i]=0;
	int mn=1e9;
	for(int i=1;i<=n;i++){
		mn=min(mn,p[i]);
		if(vis[p[i]]) return;
		vis[p[i]]=1;
	}
	for(int i=1;i<=n;i++){
		p[i]-=mn-1;
	}
	for(pii _:pos[D]) q[_.fi]=n+1-p[_.se];
	for(int i=2;i<=n+n;i++){
		int v=q[pos[i][0].fi]+p[pos[i][0].se];
		for(pii _:pos[i]) if(q[_.fi]+p[_.se]!=v){
			for(int o=1;o<=n;o++) p[o]+=mn-1;
			return;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<n;j++){
			cout<<q[i]+p[j]<<" ";
		}
		cout<<q[i]+p[n]<<endl;
	}
	exit(0);
}
vector<int>now;
void dfs(int i,int op){
	int v=rev[a[1][i]][op];
	p[i]=v;
	if(i==n){
		Check();
		return;
	}
	for(int o=0;o<2;o++){
		int nxt=rev[a[1][i+1]][o];
		if(abs(nxt-v)==d[i]) dfs(i+1,o);
	}
}
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=A[i][j]=read();
			cnt[A[i][j]]++;
			pos[A[i][j]].push_back({i,j});
			if(cnt[A[i][j]]==n) D=A[i][j];
		}
	}
	for(int i=2;i<=n+n;i++){
		for(int j=2;j<=n+n;j++){
			if(cnt[i]==min(j-1,n+n-j+1)){
				rev[i][0]=j;
				rev[i][1]=n+n+2-j;
				break;
			}
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=n+n+2;j++) vis[j]=0;
		for(int j=1;j<=n;j++){
			int w[4]={0};
			for(int x:{0,1}){
				for(int y:{0,1}){
					int v=rev[a[j][i]][x]-rev[a[j][i+1]][y];
					w[x*2+y]=v;
				}
			}
			for(int o=0;o<4;o++){
				bool ok=1;
				for(int t=o+1;t<4;t++){
					if(w[o]==w[t]){
						ok=0;
						break;
					}
				}
				if(ok&&w[o]>0) vis[w[o]]++;
			}
		}
		for(int j=1;j<=n+n+2;j++) if(vis[j]==n){
			d[i]=j;
			break;
		}
	}
	dfs(1,0),dfs(1,1);
	return 0;
}
```

---

## 作者：shinzanmono (赞：6)

考虑如下三个结论：

> 1. 合法的矩阵不会有一行或者一列满足存在相同的数。
>
> 2. 操作 1 和操作 2 结束后将所有行拆出来，对每行都进行排序，然后将行之间排序，必定可以还原矩阵；列同理。所以 $2$ 所在的行列必存在 $3,4,\ldots n+1$，$2n$ 所在的行列必存在 $n+1,n+2,\ldots 2n$。
>
> 3. 出现次数相同的数最多只有两个。

所以我们直接找到两个出现次数只有 1 次的位置，然后分别讨论两种情况，根据数的出现次数构造，并输出字典序最小就好了。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
const int sz=1010;
int a[sz][sz],cnt[sz<<1],vis[sz<<1];
std::vector<int>f[sz];
std::vector<std::vector<int>>l,r;
std::ostream &operator<<(std::ostream &out,std::vector<std::vector<int>>x){
  for(int i=0;i<x.size();i++){
    for(int j=0;j<x[i].size();j++)out<<x[i][j]<<(j+1==x[i].size()?"":" ");
    out<<(i+1==x.size()?"":"\n");
  }
  return out;
}
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin>>n;
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)std::cin>>a[i][j],cnt[a[i][j]]++;
  for(int i=2;i<=n;i++)f[n-i+1].push_back(i+n);
  for(int i=1;i<=n;i++)f[i].push_back(i+1);
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      if(cnt[a[i][j]]==1){
        for(int x=1;x<=n;x++){
          if(vis[a[x][j]]!=0)continue;
          vis[a[x][j]]=f[cnt[a[x][j]]].back();
          f[cnt[a[x][j]]].pop_back();
        }
      }
    }
  }
  l.assign(n,std::vector<int>(n,0));
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++)l[i-1][j-1]=vis[a[i][j]];
  }
  std::fill(vis+1,vis+n*2+1,0);
  for(int i=1;i<=n;i++)f[i].push_back(i+1);
  for(int i=2;i<=n;i++)f[n-i+1].push_back(i+n);
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++){
      if(cnt[a[i][j]]==1){
        for(int x=1;x<=n;x++){
          if(vis[a[x][j]]!=0)continue;
          vis[a[x][j]]=f[cnt[a[x][j]]].back();
          f[cnt[a[x][j]]].pop_back();
        }
      }
    }
  }
  r.assign(n,std::vector<int>(n,0));
  for(int i=1;i<=n;i++){
    for(int j=1;j<=n;j++)r[i-1][j-1]=vis[a[i][j]];
  }
  std::fill(vis+1,vis+n*2+1,0);
  std::cout<<std::min(l,r)<<"\n";
  return 0;
}
```

---

## 作者：yinbe (赞：4)

## 题目描述

有一个 $N\times N$（$1\le N\le 1000$）的矩阵，其中第 $r$ 行第 $c$ 列的方格中的整数为 $r+c$。

有 $3$ 种操作。

1. 交换两行；
2. 交换两列；
3. 选择两个同时存在于表格中的值 $a$ 和 $b$，然后同时将每一个 $a$ 更改为 $b$，每一个 $b$ 更改为 $a$。

Elsie 总是按类型顺序执行操作；也就是说，她首先执行任意数量（可能为零）的类型 $1$ 操作，然后是类型 $2$ 操作，最后是类型 $3$ 操作。

请求出在执行完所有类型 $1$ 和 $2$ 操作后，在执行任意类型 $3$ 操作之前，矩阵的一种可能状态。可能存在多种可能的答案，在这种情况下你应当输出字典序最小的答案。

## 思路

首先有一个性质：**执行完 $1$、$2$ 操作后，每一行每一列的数字会变成原来的行、列的排列**，就是一开始与 $2$ 在同一行的是 $3$ 到 $2+n-1$，执行完 $1$、$2$ 操作后，与 $2$ 在同一行的还是 $3$ 到 $2+n-1$。

显然，$1$ 操作交换行，行内部的数字不会变，$2$ 操作交换列，行内部相当于交换 $2$ 个数的顺序，不会改变值，只会改变顺序。$1$ 操作交换行列内部相当于交换 $2$ 个数的数字，不会改变值，只会改变顺序，$2$ 操作交换列，列内部的数字不会变。所以执行完 $1$、$2$ 操作后，每一行每一列的数字只会变顺序，一开始与 $2$ 在同一行同一列的数字执行完 $1$、$2$ 操作后还是与 $2$ 在同一行同一列。

然后，只有一开始的第 $1$ 行有 $2$，一开始的最后 $1$ 行有 $n\times 2$，$2$ 和 $n\times 2$ 都只出现了一次，很好确定位置，与 $2$ 在同一行的是 $2$ 到 $n+1$，与 $n\times 2$ 在同一行的是 $n+1$ 到 $n\times 2$，通过出现次数刚好可以确定所有的数，因为出现次数是 $1$ 的有 $2$ 个数，我们不知道哪个是 $1$ 哪个是 $n\times 2$，所以答案有 $2$ 种，我们分两种情况算完后比较字典序即可。

## 代码

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n,a[1005][1005],cnt[2005],fa[2005],s1,s2,ans1[1005][1005],ans2[1005][1005];
int check()
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(ans1[i][j]<ans2[i][j])
				return true;
			if(ans1[i][j]>ans2[i][j])
				return false;
		}
	}
	return 924;
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&a[i][j]);
			cnt[a[i][j]]++;
		}
	}
	for(int i=1;i<=n;i++)
	{
		bool flag=false;
		for(int j=1;j<=n;j++)
		{
			if(cnt[a[i][j]]==1)
			{
				if(!s1)
					s1=i;
				else
				{
					s2=i;
					flag=true;
					break;
				}
			}	
		}
		if(flag)
			break;
	}
	for(int i=1;i<=n;i++)
	{
		fa[a[s1][i]]=cnt[a[s1][i]]+1;
		fa[a[s2][i]]=n*2-cnt[a[s2][i]]+1;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			ans1[i][j]=fa[a[i][j]]; 
	}
	for(int i=1;i<=n;i++)
	{
		fa[a[s1][i]]=n*2-cnt[a[s1][i]]+1;
		fa[a[s2][i]]=cnt[a[s2][i]]+1;
	}	
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
			ans2[i][j]=fa[a[i][j]]; 
	}
	if(check())
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				printf("%d ",ans1[i][j]);
			printf("\n");
		}
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
				printf("%d ",ans2[i][j]);
			printf("\n");
		}		
	}
}
```

---

## 作者：XGTD (赞：4)

# 题解：P11672 [USACO25JAN] Table Recovery S

## Preface

~~这场太我难了~~。前两题做出来之后本来以为进金稳了，结果剩 45 分钟第三题愣是第一个点都没拿到。痛失 Au。

赛后发现第三题好简单，比前两题既更好想也更好写。

## Problem statement

[P11672](https://www.luogu.com.cn/problem/P11672)

## Solution

这道题突破点就是每个数出现的频率。

只要把初始状态，未被打乱的格子真正画出来~~我在考场上居然没画~~就会发现只有两个数只出现一次，也就是 $2$ 和 $2n$。

这时候还需要发现一个还算挺明显的性质，也就是每行和每列的数在进行完前两种操作后是不会被打乱的，也就是说原来在 $2$ 所在的行里的数在进行完前两种操作后还和 $2$ 在一行。$2n$ 也同理。

最后还需要在观察一下画出来的表格，发现所有和 $2$ 在同一行的数出现次数都不同，所有和 $2n$ 在同一行的数出现次数也各不相同。而且每个数要么在 $2$ 的行里出现过，要么在 $2n$ 的行里出现过。因此我们可以直接通过出现次数确定出每一个数在第三种操作前是什么，也就是确定了答案。

不过还有一点，因为一共有两个数都只出现了一次，我们不知道哪个是 $2$ 哪个是 $2n$，所以需要把两种可能性的最后结果都算出来，比较字典序，小的那个就是答案。

同时注意这也顺便证明了其实一共只有两种可能的答案。

细节看代码，有大量注释解释。


```cpp
/*
the forever pain


the key key point to this problem is = 
the frequencies the numbers appear

if you draw the grid out, you'll see that only 2 and 2n appear
exactly once, and another observation that can be made really
easily(as in so easy that I was able to make it incontest) is
that after operations 1 and 2, the elements in a certain row or 
colume won't get mixed up, meaning the numbers that are in the
row 2 was in are still 2, 3, ... n + 1, and same with the colume.

now we've gotta utilize the "frequency" observations again.
this time realizing that each element within the row 2 was
originally in appeared different number of times, for example 3
appear twice, 4, three times, and n + 1 exactly n times.

and we can do the same with elements in the row of 2n(which we can
easily identify because it's one of the only two elements that
appear only once), which include elements n + 1 to 2 * n

and guess what? now we have the whole grid! because now we know
exactly what each elements got switched to what other elements
after operation 3! now there's just one more thing that I haven't
mentioned, it's that we don't know who's 2 and who's 2n, cuz
they both appear once. well we can just construct both
possibilities, and compare the lexicographical order!!!!

一遍过

比t2简单多了, 其实比t1也简单多了 

唉，与 au 失之交臂 
*/
#include<bits/stdc++.h>
using namespace std;
//#pragma GCC optimize("O3,unroll-loops")
#define int long long
int n, a[1005][1005], cnt[2005], orig[2005], ans1[1005][1005];
//cnt[i] = how many times i appeared in final table
//orig[i] = what i is originally
int s1, s2;
//only record the row number
signed main(){
	cin>>n;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin>>a[i][j];
			cnt[a[i][j]]++;
			//count how many times each element appeared
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(cnt[a[i][j]] == 1){
				if(!s1)s1 = i;
				else s2 = i;
				//find where 2 and 2n are located
			}
		}
	}
	for(int i = 1; i <= n; i++){
		//those are the ones on the same row as 2
		orig[a[s1][i]] = cnt[a[s1][i]] + 1;
		//what it was is just the number of times it appeared + 1		
		
		//on the same row as 2n
		orig[a[s2][i]] = n * 2 - cnt[a[s2][i]] + 1;
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			ans1[i][j] = orig[a[i][j]];
			//record the answer grid if 2 is s1, so we can
			//compare lexicographical order
		}
	}
	for(int i = 1; i <= n; i++){
		orig[a[s1][i]] = 2 * n - cnt[a[s1][i]] + 1;
		orig[a[s2][i]] = cnt[a[s2][i]] + 1;
		//this time s1 and s2 are reversed
	}
	int opt = 0;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(!opt && orig[a[i][j]] != ans1[i][j]){
				if(orig[a[i][j]] < ans1[i][j])opt = 2;
				else opt = 1;
				//find optimal assignment, whether it's the
				//first one(opt = 1) or second one
			}
			if(!opt || opt == 1)cout<<ans1[i][j];
			else cout<<orig[a[i][j]];
			
			if(j != n)cout<<" ";
			//bruh, usaco!!!
		}
		cout<<endl;
	}
	return 0;
}

```

## After thoughts

[Result](https://www.luogu.com.cn/record/202107156)

其实现在来看这道题其实比这场前两道简单多了，应该只有十二月份 t1 的难度，考场上 45 分钟连想加写完全够了，看来当时应该是被前两题难度给吓到了。

---

## 作者：fire_and_sweets (赞：2)

给出题人下跪了，思维性很强。

这题我们需要发现很多性质。

首先一个性质：对于一个数，如果他在 Elsie 进行操作 $1,2,3$ 后在矩阵中出现了 $n$ 次，则可以确定这个数一定双射到了 $(n+1)$。

推广：对于一个数，如果他在最后的矩阵中出现了 $k(k\neq n)$ 次，则他有两种可能的取值，$(k+1)$ 或 $(2\times n+2-(k+1))$。

这两个性质很容易证明。

这个时候我们考虑字典序最小的情况。首先先把确定的对角线 $n+1$ 这一部分进行赋值。

显然按照自然顺序遍历整个矩阵，假如说当前遇到了 $(i,j)$，我们希望 $(i,j)$ 尽可能是 $k+1$ 而非 $(2\times n+2-(k+1))$。

于是我们考虑判断，如果 $(i,j)$ 是 $k+1$，那么是否存在一种解？

这边我们再发现一个性质：在顺次进行前两个操作后的矩阵满足：在任意两行中，元素大小关系完全相同；在任意两列中，元素大小关系完全相同。

于是我们考虑对所有的行维护一个带权并查集表示其大小关系；对于所有的列维护一个带权并查集表示其大小关系。

每次建立新的双射的时候，考虑直接把这个点和当前这一行/列的 $(n+1)$ 这个对角线元素进行 `merge` 操作。注意这边需要预处理一下 $n+1$ 在每一行和每一列中出现的位置，方便连边。

具体细节可以见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2010;

int n, a[N][N], ha[N], pei[N], r[N][N], ok[N];
int mp[N], diag;
int t1[N], t2[N], t3[N], t4[N];
int fah[N], wh[N], fal[N], wl[N];
int label[N], halabel[N];
int plach[N], placl[N];
vector<pair<int, int> > v[N]; 

int findh(int x)
{
	if (x == fah[x]) return x;
	int f = fah[x];
	fah[x] = findh(fah[x]);
	wh[x] += wh[f];
	return fah[x]; 
}

int findl(int x)
{
	if (x == fal[x]) return x;
	int f = fal[x];
	fal[x] = findl(fal[x]);
	wl[x] += wl[f];
	return fal[x];
}

int flag = 1;

void mergeh(int x, int y, int d)
{
	int px = findh(x), py = findh(y);
	if (px == py)
	{
		if (wh[y] - wh[x] != d) 
		{
//			cout<<"error on H:" <<x<<" "<<y<<" "<<d<<endl;
			flag = -1;
		}
		return;
	}	
	fah[py] = px;
	wh[py] = -wh[y] + d + wh[x];
}

void mergel(int x, int y, int d)
{
	int px = findl(x), py = findl(y);
	if (px == py)
	{
		if (wl[y] - wl[x] != d)
		{
//			cout<<"EL: "<<x<<" "<<y<<" "<<d<<endl;
			flag = -1;
		}
		return; 
	}
	fal[py] = px;
	wl[py] = -wl[y] + d + wl[x];
}

void fill_colors(int aa, int bb, bool f)
{
	for (auto ppair : v[aa])
	{
		int x = ppair.first, y = ppair.second;
		if (f) r[x][y] = bb;
		mergeh(y, plach[x], bb - (n + 1)); // 注意这边是值-值 
		mergel(x, placl[y], bb - (n + 1));
	}
}

signed main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ ) cin >> a[i][j], ha[a[i][j]] ++ ;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ ) v[a[i][j]].push_back({i, j});
	for (int i = 2; i <= 2 * n; i ++ )
	{
		if (mp[ha[i]])
		{
			pei[i] = mp[ha[i]];
			pei[mp[ha[i]]] = i;
		}
		else mp[ha[i]] = i;
	} 
	int cnt = 0;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ )
		{
			if (!halabel[a[i][j]]) label[ ++ cnt] = a[i][j], halabel[a[i][j]] = 1;
		}
	assert(cnt == 2 * n - 1);
	for (int i = 2; i <= 2 * n; i ++ ) fah[i] = fal[i] = i;
	for (int i = 2; i <= 2 * n; i ++ )
		if (ha[i] == n) diag = i;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ )
			if (a[i][j] == diag) plach[i] = j;
	for (int j = 1; j <= n; j ++ )
		for (int i = 1; i <= n; i ++ )
			if (a[i][j] == diag) placl[j] = i;
	ok[diag] = 1;
	for (int i = 1; i <= n; i ++ )
		for (int j = 1; j <= n; j ++ )
			if (a[i][j] == diag) r[i][j] = n + 1;
	for (int id = 1; id <= cnt; id ++ )
	{
		if (ok[label[id]]) continue; // 重点细节：已经放过的不能再放了。 
		
		for (int i = 0; i <= 2 * n; i ++ )
		{
			t1[i] = fah[i];
			t2[i] = wh[i];
			t3[i] = fal[i];
			t4[i] = wl[i];
		} 
		int tmp1 = label[id], tmp2 = pei[tmp1];
		ok[tmp1] = ok[tmp2] = 1;
		int ls = ha[tmp1] + 1, rs = 2 * n + 2 - ls;
//		cout << "now, tmp1, tmp2, ls, rs are: " << tmp1 << ", " << tmp2 << ", " << ls << ", " << rs << endl; 
		flag = 1;
		fill_colors(tmp1, ls, 0);
		fill_colors(tmp2, rs, 0);
		if (flag == -1) swap(ls, rs);
//		cout << "RETEST_________________________________________________________" << endl;
		flag = 1;
		for (int i = 0; i <= 2 * n; i ++ )
		{
			fah[i] = t1[i];
			wh[i] = t2[i];
			fal[i] = t3[i];
			wl[i] = t4[i];
		}
		fill_colors(tmp1, ls, 0); // 这一部分是用于调试的，没有什么用。 
		fill_colors(tmp2, rs, 0);
	//	assert(flag != -1);
		
		for (int i = 0; i <= 2 * n; i ++ )
		{
			fah[i] = t1[i];
			wh[i] = t2[i];
			fal[i] = t3[i];
			wl[i] = t4[i];
		}
		fill_colors(tmp1, ls, 1);
		fill_colors(tmp2, rs, 1);
//	for (int i = 1; i <= n; i ++ , cout << endl)
//		for (int j = 1; j <= n; j ++ ) {
//			cout << r[i][j]; if (j != n) cout << ' '; }
//			system("pause");
	}
	for (int i = 1; i <= n; i ++ , cout << endl)
		for (int j = 1; j <= n; j ++ ) {
			cout << r[i][j]; if (j != n) cout << ' '; }
	return 0;
}

```

---

## 作者：buowen123 (赞：2)

下文中 $n$ 指代 $N$，原矩阵指代输入，答案矩阵指代的输出。

题目等价于把每个值重新标号为 $2\sim 2n$，使得可以通过若干次 $1,2$ 操作将矩阵复原为最初态。设 $i$ 被重新标号为 $to_i$，$pre_i$ 是 $to_i$ 的逆排列（$pre_{to_i}=i$）。

设 $buk_i$ 为原矩阵中 $i$ 的出现次数。对比最初态可知，若 $buk_i=x$，则 $to_i=x+1$ 或 $2n+1-x$ 有两种取值，进而 $pre_i$ 有两种取值。

为了构造答案矩阵，取 $st$ 满足 $buk_{st}=1$，令 $pre_2=st$ 并依次求出 $pre_3\sim pre_{n-1}$。考虑已知 $pre_i$ 怎么确定 $pre_{i+1}$。

-----
观察最初态的矩阵的左上角：
$\\
2\quad3\quad4\quad{\color{green}5}\quad{\color{orange}6}\dots\\
3\quad4\quad{\color{green}5}\quad{\color{red}6}\dots\\
4\quad{\color{green}5}\quad{\color{red}6}\dots\quad\\
{\color{green}5}\quad{\color{red}6}\dots\quad\\
{\color{orange}6}\dots\quad\\
$
发现对于 $2\le x<n$，可以把矩阵中 $x+1$ 分为 $3$ 类：
- 存在 $x-2$ 个 $x+1$，满足、存在某个 $x$ 的横坐标与之相等，也存在某个 $x$ 的纵坐标与之相等。这些属于第 $1$ 类；
- 而剩下的 $2$ 个 $x+1$，$1$ 个只有横坐标存在，$1$ 个只有纵坐标存在。这两个分别属于第 $2,3$ 类。

例如取 $x=5$，标为红色的三个 $6$，上方的 $5$ 与其纵坐标相等，左方的 $5$ 与其横坐标相等，而标为橙色的两个 $6$，一个只有上方的 $5$，一个只有左方的 $5$。

发现“第 $2,3$ 类数各只有一个”这一特性，将 $x+1$ 换为 $2n+1-x$ 则不满足。且此特性的存在与 $1,2$ 操作无关（初始在同行/列的数，$1$ 或 $2$ 操作后仍在同行/列）。

------
回到原题，由于 $pre_{i+1}$ 的待选取值只有两个，令 $pre_i$ 为上文的 $x$，$pre_{i+1}$ 为上文的 $x+1$，对上述 $3$ 类数进行计数，判断是否满足上述“特性”即可，每一次是 $O(n)$ 的。

确定了 $pre_2\sim pre_{n-1}$，答案矩阵就出来了。注意这只是其中一个解，另一个解可以通过 $v\leftarrow 2n+2-v$ 得到，比较即得答案。时间复杂度 $O(n^2)$。

下面是代码实现（本人的实现多一个 $\log n$）。~~另外，常改马蜂是我个人的神秘习惯，大家不要在意。~~
```cpp
#include<bits/stdc++.h>
#define eb emplace_back
#define mp make_pair
using namespace std;
typedef unsigned long long ull;
const int N=1e3+5;
int n,st,ret,a[N][N],a1[N][N],a2[N][N],buk[N<<1],to[N<<1];
mt19937_64 rng(time(0));
vector<int>v[N<<1],p1[N<<1],p2[N<<1];
vector<pair<int,int>>p[N<<1];
int tmp[N<<1][2];
bool fd(vector<int>x,int y){
	auto it=lower_bound(x.begin(),x.end(),y);
	return (it!=x.end())&&(*it==y);
}
bool check(int x,int y){int i=0;memset(tmp,0,sizeof(tmp));
//设pre[i]=y，返回pre[i+1]=x是否可能（x是否拥有那个“特性”）
	for(auto w:p[x]){i++;int s=w.first,t=w.second;
		if(fd(p1[y],s))tmp[i][0]++;if(fd(p2[y],t))tmp[i][1]++;
	}//tmp[i][0]:横坐标是否存在 tmp[i][1]:纵坐标是否存在
	int c[4]={0,0,0,0};//c[0]表示不属于任何一类
	for(int j=1;j<=i;j++)c[tmp[j][0]+2*tmp[j][1]]++;
	if(c[0]||c[1]!=1||c[2]!=1)return false;return true;
}
int main(){scanf("%d",&n);if(n==1){puts("2");return 0;}//特判
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
		scanf("%d",&a[i][j]),buk[a[i][j]]++;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
		p1[a[i][j]].eb(i),p2[a[i][j]].eb(j),p[a[i][j]].eb(mp(i,j));//预处理每个值的坐标
	for(int i=2;i<=2*n;i++)sort(p1[i].begin(),p1[i].end());
	for(int i=2;i<=2*n;i++)sort(p2[i].begin(),p2[i].end());
	for(int i=2;i<=2*n;i++)if(buk[i]==1)st=i,to[i]=2;
	for(int i=2;i<=2*n;i++)if(buk[i]==1&&st!=i)to[i]=2*n;
	for(int i=2;i<=2*n;i++)if(buk[i]==n)to[i]=n+1;//预处理其中3个to值
	for(int i=2;i<=2*n;i++)v[buk[i]].eb(i);//v[i][0/1]表示pre[i]两种取值
	
	int cur=st;for(int i=2;i<n;i++){int o;
		if(check(v[i][0],cur))cur=v[i][0],o=0;
		else cur=v[i][1],o=1;
		to[cur]=i+1,to[v[i][1-o]]=2*n+1-i;
		//通过to[cur]的值反推另一个to值（v[i][0/1]的buk值都是i）
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){
		a1[i][j]=to[a[i][j]],a2[i][j]=2*n+2-to[a[i][j]];
		if(a1[i][j]<a2[i][j]&&!ret)ret=1;if(a1[i][j]>a2[i][j]&&!ret)ret=2;
	}//求答案，比较字典序
	for(int i=1;i<=n;i++,putchar(10))for(int j=1;j<=n;j++)
		printf("%d ",ret==1?a1[i][j]:a2[i][j]);
}
```
（如果这题升了难度，记得喊我把这篇题解精简一下。）

---

## 作者：littlebug (赞：2)

就这题使我差 6pts 升金。/fn

不过赛后再看，这道题还是挺简单的，反正比 A 简单，纯粹是因为位置问题导致我以为这个题得很难。

## Solution

显然在操作 1、2 中，不会改变某一个数所在的行或列的数组成的集合，只是顺序不同。

所以考虑拿几个特殊值来确定操作 3 前的矩阵，发现 $2$ 和 $2n$ 都一定出现了一次，于是先把这两个确定下来。然后跟 $2$ 在同一行的用手打表可知一定是 $3,4,5,\dots,n+1$，跟 $2n$ 在同一行的是 $n+1,n+2,\dots,2n$，又因为每个数的出现次数是一定的，所以每个数的位置就都能确定出来了。

分讨 $2$ 和 $2n$ 的位置（一共就这两个数出现一次），比较一下谁小答案就是谁。

而且不用判无解，因为「输入保证答案存在」，而可以证明如果 $2$ 和 $2n$ 当前确定的位置合法，那么互换也是合法的，因为整个矩阵每一对 $2+x$ 与 $2n-x$ 的出现次数是对称的。

时间复杂度 $O(n^2)$。

## Code

```cpp
int n,a[MAXN][MAXN],c[MAXN<<1],b[MAXN][MAXN],to[MAXN<<1],ans1[MAXN][MAXN],ans2[MAXN][MAXN];

il void solve(pii d1,pii d2,int ans[MAXN][MAXN])
{
    memset(to,0,sizeof(to));
    to[a[d1.st][d1.nd]]=2,to[a[d2.st][d2.nd]]=n<<1;
    rep(j,1,n) if(j!=d1.nd) to[a[d1.st][j]]=c[a[d1.st][j]]+1;
    rep(j,1,n) if(j!=d2.nd) to[a[d2.st][j]]=(n<<1)-c[a[d2.st][j]]+1;

    rep(i,1,n) rep(j,1,n) ans[i][j]=to[a[i][j]];
}

signed main()
{
    read(n),_::r(a,n,n);
    rep(i,1,n) rep(j,1,n) ++c[a[i][j]];

    int x1=-1,x2=-1; pii d1,d2;
    rep(i,2,n<<1) c[i]==1 && (x1==-1 ? (x1=i) : (x2=i));
    rep(i,1,n) rep(j,1,n) a[i][j]==x1 && (d1={i,j},1),a[i][j]==x2 && (d2={i,j},1);

    solve(d1,d2,ans1),solve(d2,d1,ans2);
    int f=0;
    rep(i,1,n) rep(j,1,n) if(ans1[i][j]!=ans2[i][j]) {f=(ans1[i][j]<ans2[i][j]); goto out;}
    out:;
    _::w(f?ans1:ans2,n,n);

    return 0;
}
```

---

华风夏韵，洛水天依！

---

## 作者：Inv_day_in_R (赞：1)

首先观察性质：
1. 将每一行视为一组，经过若干次操作一和操作二后，这一组所在行和组内顺序可能改变，但这一组内的数不可能跑到其他组里去。每一列也有相同的性质。
2. 经过若干次操作三后，每一个位置上的数出现次数不变。

很显然，那个只出现了两次的数它原来要么是 $2$ 要么是 $2n$。那么设两个点坐标分别为 $(x_0,y_0)$ 与 $(x_1,y_1)$，不妨先算 $ans_{x_0,y_0}=2$ 的情况。先算出每一个数的出现次数，这时使用第一条性质，第 $x_0$ 行内原来必然为 $[2,n+1]$，观察到这些数的出现次数各不相同，可以直接找出对应数。同理，计算第 $x_1$ 行可找到 $[n+1,2n]$ 的对应数。这时已经覆盖了整个区间 $[2,2n]$，找出了所有数的对应数，可以还原出答案。

然后再算出 $ans_{x_0,y_0}=2n$ 的情况，求出另一种答案，暴力比较字典序，输出较小者即可。

代码：

```cpp
void solve(){
	int n;
	cin>>n;
	vector<vector<int>>v(n,vector<int>(n));
	cin>>v;
	vector<int>cnt(2*n+1),ans(2*n+1),ans2(2*n+1);
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)cnt[v[i][j]]++;
	int x0,x1;
	for(int i=0;i<n;i++){
		bool bl=0;
		for(int j=0;j<n;j++)if(cnt[v[i][j]]==1){
			x0=i;
			bl=1;
			break;
		}
		if(bl)break;
	}
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(cnt[v[i][j]]==1)x1=i;
	for(int i=0;i<n;i++){
		int num=v[x0][i];
		ans[num]=cnt[num]+1;
		ans2[num]=2*n+1-cnt[num];
	}
	for(int i=0;i<n;i++){
		int num=v[x1][i];
		ans[num]=2*n+1-cnt[num];
		ans2[num]=cnt[num]+1;
	}
	for(int i=0;i<n;i++){
		bool bl=0;
		for(int j=0;j<n;j++)if(ans2[v[i][j]]<ans[v[i][j]]){
			bl=1;
			swap(ans,ans2);
			break;
		}
		else if(ans2[v[i][j]]>ans[v[i][j]]){
			bl=1;
			break;
		}
		if(bl)break;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)cout<<ans[v[i][j]]<<(j==n-1?"":" ");
		if(i!=n-1)cout<<endl;
	}
}
```
题外话：

我在函数外重载了运算符 `>>`，可以直接输入 `vector`，不可能直接编译通过。

---

## 作者：zxh923 (赞：1)

# Table Recovery 题解

[题目传送门](https://www.luogu.com.cn/problem/P11672)

### 思路

简单注意到几个性质，这题就是好做的了。

首先注意到前 $2$ 个操作进行若干次后，同一行的数还在同一行，同一列的数还在同一列。

然后发现，这道题还是没法做。但是我们漏了一个性质，就是初始矩阵有 $a_{i,j}=i+j$。

注意到初始矩阵中，第一行和最后一行包含了所有的数。那么变换完之后，也一定有两个这样的行。

显然这两行有一个特征，有一个仅出现一次的数。我们设这两行为 $l_1,l_2$。

不妨设 $l_1$ 是初始矩阵的第一行，$l_2$ 是初始矩阵的最后一行（$l_1$ 是最后一行的话交换 $l_1,l_2$ 再做一遍就好了）。

那么 $l_1$ 这一行中，有出现 $1$ 次的数是 $2$，出现 $2$ 次的数是 $3$，以此类推。$l_2$ 这一行中，有出现 $1$ 次的数是 $n+n$，出现 $2$ 次的数是 $n+n-1$，以此类推。

也就是说，我们找出 $l_1,l_2$，然后枚举哪一行是答案矩阵的第一行，这样就可以通过每个数的出现次数确定是答案矩阵的哪个数变为了最终矩阵的这个数，进而唯一确定了两个可能的答案矩阵，输出字典序更小的那个即可。

### 代码


```cpp
#include<bits/stdc++.h> 
#define int long long
#define N 2005
#define pii pair<int,int>
#define x first
#define y second
#define pct __builtin_popcount
#define mod 1000000007
#define inf 1e18
#define pi acos(-1)
#define eps 1e-8
using namespace std;
int T=1,n,l1,l2,a[N][N],cnt[N],oth[N],res[2][N][N];
void print(int t){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout<<res[t][i][j];
			if(j!=n)cout<<' ';
		}
		cout<<'\n';
	}
}
void check(){
	for(int j=1;j<=n;j++){
		oth[a[l1][j]]=2+cnt[a[l1][j]]-1;
		oth[a[l2][j]]=n+n-(cnt[a[l2][j]]-1);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			res[0][i][j]=oth[a[i][j]];
		}
	}
	swap(l1,l2);
	for(int j=1;j<=n;j++){
		oth[a[l1][j]]=2+cnt[a[l1][j]]-1;
		oth[a[l2][j]]=n+n-(cnt[a[l2][j]]-1);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			res[1][i][j]=oth[a[i][j]];
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(res[0][i][j]<res[1][i][j]){
				print(0);
				return;
			}
			else if(res[1][i][j]<res[0][i][j]){
				print(1);
				return;
			}
		}
	}
	print(0);
}
void solve(int cs){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
			cnt[a[i][j]]++;
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(cnt[a[i][j]]==1){
				if(!l1)l1=i;
				else l2=i;
			}
		}
	}
	check();
}
void solution(){
    /*
    nothing here
    */
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
//	init();
//	cin>>T;
    for(int cs=1;cs<=T;cs++){
        solve(cs);
    }
    return 0; 
}
```

---

## 作者：_ayaka_ (赞：1)

结论题。

### 思路

考虑以下几点。

1. 对一行/一列进行排序，此行/列排序的结果一定为 $x,x+1,\dots,x+n$。
2. 出现 $n$ 次的数字只有一种，其余次数的也只有两种。
3. 对于一种成立的情况，将所有出现次数相等的数字互换，此情况依然成立。

而我们也知道，出现次数为 $1,2,3,\dots,n-1,n,n-1,\dots,2,1$ 的数也就是 $2,3,4,\dots,n,n+1,n+2,\dots,2n-1,2n$，综上，我们可以利用每个数字出现的次数来构造出两种可行的原情况，这两种情况出现次数相等的数字正好互换。然后比较出字典序较小的那一种输出即可。

时间复杂度 $O(n^2)$。

### 代码流程
代码并不好理解，遂附之。

- 读入并保存每个数出现的次数。
- 特判 $n=1$。
- 将两个包含有只出现了一次的数字的行保存下来，并将保存的两行按出现次数来排序。按照推论，这两行也就是 $2,3,\dots,n,n+1$ 与 $n+1,n+2,\dots,2n-1,2n$。
- 进行替换并比较字典序，最后输出。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, a[1005][1005], num[5005], ans1[5005], ans2[5005];
struct que {
	int id, num;
} d1[5005], d2[5005];
bool cmp(que x, que y) {
	return x.num < y.num;
}
bool check() {
	int bj = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (ans1[a[i][j]] < ans2[a[i][j]]) {
				bj = 1;
				break;
			} else if (ans1[a[i][j]] > ans2[a[i][j]]) {
				bj = 2;
				break;
			}
		}
		if (bj) break;
	}
	if (bj == 1) return true;
	return false;
}
signed main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> a[i][j];
			num[a[i][j]]++;
		}
	}
	if(n==1){
		cout<<"2";
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		int bj = 0;
		for (int j = 1; j <= n; j++) {
			if (num[a[i][j]] == 1) {
				bj = 1;
				break;
			}
		}
		if (bj == 1) {
			if (d1[1].num) {
				for (int j = 1; j <= n; j++) d2[j] = {a[i][j], num[a[i][j]]};
			} else {
				for (int j = 1; j <= n; j++) d1[j] = {a[i][j], num[a[i][j]]};
			}
		}
	}
	sort(d1 + 1, d1 + n + 1, cmp);
	sort(d2 + 1, d2 + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		ans1[d1[i].id] = i + 1;
	}
	for (int i = n - 1; i >= 1; i--) {
		ans1[d2[i].id] = n - i + n + 1;
	}
	for (int i = 1; i <= n; i++) {
		ans2[d2[i].id] = i + 1;
	}
	for (int i = n - 1; i >= 1; i--) {
		ans2[d1[i].id] = n - i + n + 1;
	}//此处我替换的是下标，即ans的下标代表操作3后的数字，ans的值代表操作3前的数字。
	if (check()) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) cout << ans1[a[i][j]] << " ";
			cout << "\n";
		}
	} else {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) cout << ans2[a[i][j]] << " ";
			cout << "\n";
		}
	}//比较并输出
	return 0;
}

```

---

