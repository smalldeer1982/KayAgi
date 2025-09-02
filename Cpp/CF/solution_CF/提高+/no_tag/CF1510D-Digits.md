# Digits

## 题目描述

现有一个长度为 $n$ 的数组 $a$ 。你要从中选择 $k$个不同的数（“不同”指在数组中的位置不同，而数值可以相同），使它们的乘积个位数字是 $d$。如果有多组解，输出乘积最大的一组。

## 说明/提示

$1\leq k\leq n\leq 10^5$

$0\leq d\leq 9$

$1\leq a_i\leq 1000$

## 样例 #1

### 输入

```
6 4
4 11 8 2 1 13```

### 输出

```
5
1 2 4 11 13```

## 样例 #2

### 输入

```
3 1
2 4 6```

### 输出

```
-1```

## 样例 #3

### 输入

```
5 7
1 3 1 5 3```

### 输出

```
-1```

## 样例 #4

### 输入

```
6 3
8 9 4 17 11 5```

### 输出

```
3
9 11 17```

## 样例 #5

### 输入

```
5 6
2 2 2 2 2```

### 输出

```
4
2 2 2 2```

# 题解

## 作者：Cry_For_theMoon (赞：5)

[传送门](https://codeforces.ml/problemset/problem/1510/D)

这场NERC最水的三题之一，我就专门负责开这个（）

考虑设 $f(i,j)$ 是前 $i$ 个数模 $10$ 为 $j$ 所得的最大值，我们很容易用刷表法去实现一个 $O(10n)$ 的 $dp$ 做法。但是本题是**乘积**，显然就算用高精度也存不下这个数值。

如果是加法，那么非常可做。我们有没有化乘为加的方法呢，众所周知有一个经典套路：$i \times j=2^{\log i+\log j}$，即转成指数。

这样我们就可以化乘为加了。

彩蛋：赛场上我一直 WA on 1，通过数十次用 cf 输出调试信息（浪费评测资源）后我才意识到**浮点比较不能直接用==**.

[AC代码](https://codeforces.ml/contest/1510/submission/111985033)

---

## 作者：王熙文 (赞：1)

这题我做了好久，因为一直不会比大数的大小，也就没想到 dp。因此这篇题解提供一个不同的思路。

## 思路

首先可以发现，$0 \sim 9$ 每一个数的幂模 $10$ 下都会产生循环节。这意味着，如果有很多个模 $10$ 相等的数，那么为了使乘积最大，只需要选删除最小的 $\le$ 循环节长度个数了。因为如果删了更多的数，那么肯定可以删更少的数使得模 $10$ 相等且乘积更大。

还有一种情况是模 $10$ 相等的这些数全都删掉，此时模 $10$ 为 $1$，因为在循环节中有可能全都不为 $1$，所以需要特判。

考虑列出每一个数的循环节长度 $+1$（加上特判的）。

$$0:2(1|0)$$

$$1:2(1|1)$$

$$2:5(1|2,4,8,6)$$

$$3:5(1|3,9,7,1)$$

$$4:3(1|4,6)$$

$$5:2(1|5)$$

$$6:2(1|6)$$

$$7:5(1|7,9,3,1)$$

$$8:5(1|8,4,2,6)$$

$$9:3(1|9,1)$$

可以发现所有方案乘起来 $2 \cdot 2 \cdot 5 \cdot 5 \cdot 3 \cdot 2 \cdot 2 \cdot 5 \cdot 5\cdot 5\cdot 3=90000$，因此可以暴力枚举这样的方案。

对于每一种方案，只需要计算删除最小的若干个之后的乘积即可。

如果值域比较小，可以直接预处理前缀积求。但是此时值域比较大。注意到 $ i \cdot j = 2 ^ { \log_2 i + \log_2 j}$，而且幂函数单调递增，所以可以直接把每一个数取对数，这样乘法就变成加法，直接求即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define double long double
int cnt[]={2,2,5,5,3,2,2,5,5,3};
int n,d; int a[100010];
vector<int> wz[10];
vector<int> qzh1[10];
vector<double> qzh2[10];
bool cmp(int x,int y) { return a[x]>a[y]; }
int nch[10];
double ans=0;
int ansnch[10]; 
void dfs(int now)
{
	if(now==10)
	{
		int cj=1; bool flag=0;
		for(int i=0; i<10; ++i)
		{
			if(nch[i]!=cnt[i]-1)
			{
				if(nch[i]>=wz[i].size()) return;
				flag=1,cj=cj*qzh1[i][wz[i].size()-nch[i]-1]%10;
			}
		}
		if(!flag) return;
		if(cj==d)
		{
			double nowans=0;
			for(int i=0; i<10; ++i)
			{
				if(nch[i]!=cnt[i]-1) nowans+=qzh2[i][wz[i].size()-nch[i]-1];
			}
			if(ans<nowans)
			{
				ans=nowans;
				for(int i=0; i<10; ++i) ansnch[i]=nch[i];
			}
		}
		return;
	}
	for(int i=0; i<=cnt[now]-1; ++i) nch[now]=i,dfs(now+1);
}
bool vis[100010];
int main()
{
	cin>>n>>d;
	for(int i=1; i<=n; ++i) cin>>a[i],wz[a[i]%10].push_back(i);
	for(int i=0; i<10; ++i)
	{
		if(wz[i].empty()) continue;
		sort(wz[i].begin(),wz[i].end(),cmp);
		qzh1[i].push_back(a[wz[i][0]]%10);
		qzh2[i].push_back(log2l(a[wz[i][0]]));
		for(int j=1; j<wz[i].size(); ++j)
		{
			int bk1=qzh1[i].back();
			qzh1[i].push_back(bk1*a[wz[i][j]]%10);
			double bk2=qzh2[i].back();
			qzh2[i].push_back(bk2+log2l(a[wz[i][j]]));
		}
	}
	dfs(0);
	if(ans==0) return cout<<-1,0;
	int anscnt=0;
	for(int i=0; i<10; ++i)
	{
		if(ansnch[i]!=cnt[i]-1) anscnt+=wz[i].size()-ansnch[i];
	}
	cout<<anscnt<<'\n';
	for(int i=0; i<10; ++i)
	{
		if(ansnch[i]!=cnt[i]-1)
		{
			for(int j=0; j<wz[i].size()-ansnch[i]; ++j) cout<<a[wz[i][j]]<<' ';
		}
	}
	return 0;
}
```

---

## 作者：Argon_Cube (赞：1)

* **【题目链接】**

[Link:CF1510D](https://www.luogu.com.cn/problem/CF1510D)

* **【解题思路】**

设 $f_{i,j}$ 为前 $i$ 个数中选一些数，乘积结尾为 $j$ 的乘积的最大值。

显然不能直接存乘积，那么非常套路的取对数。

然后值得注意的一点是，$k>0$，意味着 $d=1$ 时你不可以什么都不取。于是把 $1$ 全都取上，最后看取的数的个数。如果没取数同样不合法。

* **【代码实现】**

```cpp
#include <iostream>
#include <vector>
#include <array>
#include <cmath>

using namespace std;

array<array<pair<int,bool>,10>,100001>	DPpath;
array<array<long double,10>,100001>		DParr;
array<int,100001>						nums;
vector<int>								answer;

int main(int argc,char* argv[],char* envp[])
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int cnt,target;
	cin>>cnt>>target;
	DParr[0].fill(-16777216);
	DParr[0][1]=0;
	for(int i=1;i<=cnt;i++)
	{
		cin>>nums[i];
		DParr[i]=DParr[i-1];
		for(int j=0;j<10;j++)
			DPpath[i][j]=make_pair(j,false);
		for(int j=0;j<10;j++)
			if(DParr[i-1][j]+log(nums[i])>DParr[i][j*nums[i]%10]-1e-9)
				DParr[i][j*nums[i]%10]=DParr[i-1][j]+log(nums[i]),DPpath[i][j*nums[i]%10]=make_pair(j,true);
	}
	if(DParr[cnt][target]<0)
		return cout<<-1,0;
	int ptr=target;
	for(int i=cnt;i;i--)
		DPpath[i][ptr].second&&(answer.push_back(nums[i]),false),ptr=DPpath[i][ptr].first;
	if(answer.empty())
		return cout<<-1,0;
	cout<<answer.size()<<'\n';
	for(int i:answer)
		cout<<i<<' ';
	return 0;
}

```

---

## 作者：咸大猫 (赞：1)

题意：

- 有一个长度为 $n$ 的数组 $a$ ，你要从中选择一些数，每个数只能用一次，使它们的乘积的个位数字是 $d$ 。
- 如果有多组解，输出乘积最大的一组。
- 输出选择数的数量和所有选择的数（顺序不限），如果没有解则输出 $-1$。
- 数据范围是  $1\le n\le 10^5$ 

看到这个题目和数据范围我们考虑 dp，$dp_{i,j}$ 表示目前处理到了第 $i$ 个数时候个位数是 $j$ 的最大值。相信这个简单的 dp 大部分读者都能够想到，复杂度为 $O(10n)$  。

但是考虑到数有 $10^5$ 个，这些数如果直接乘的话就算使用高精度也不可能存下，于是这里要介绍一个技巧，我们可以把这些数转成指数，然后将指数求和就相当于我们把这些数相乘，这样直接用 int 都可以存的下。

但是很明显这道题到这里并没有完，题目要求输出选择数的数量和数。

对于这种情况，我们考虑在 dp 的过程中建立 $lst$ 数组，其中 $lst_{i,j}$ 保存了 $dp_{i,j}$ 转移过来的位置。然后可以在 dp      完成之后由 $dp_{n,m}$ 进行一次倒推，这里代码中采用了递归的方式进行，每次由 $dp_{i,j}$ 找到由 $dp_{i-1}$ 行转移过来时候的位置。当 $lst_{i,j}$ 为 $0$ 时候代表找完了所有的值。当然，这里还要再注意一点，有的情况转移是直接从上一行转移下来的，这个时候相当于没有选数，所以在递归的时候注意一下 dp 数组的值有没有变化，如果没有变化就不用统计。然后记录搜到的数的总数并输出即可。

代码：

```c++
#include<bits/stdc++.h>
#define mp make_pair
#define fi first
#define se second
#define ls p<<1
#define rs p<<1|1
//#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector <int> vi;
typedef pair<int,int> pii;
const int N=1e5+5,M=1e3+5;
const int Ox3f=1061109567;
const int INF=2147483647;
const ll Lx3f=4557430888798830399;
const ll LNF=9223372036854775807;
int mod=1e9+7;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int n,m,a[N],s[N],cnt=0;
pii lst[N][10];
double dp[N][10];
void dfs(int x,int y)
{
	int xx=lst[x][y].fi,yy=lst[x][y].se;
	if(dp[x][y]!=dp[xx][yy]||a[x]%10==1) s[++cnt]=a[x];//这里顺便把1算了进去，其实没有必要
	if(xx==0&&yy==0) return;
	dfs(xx,yy);
}
signed main()
{
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++)
	{
		dp[i][a[i]%10]=log2(a[i]);
		for(int j=0;j<=9;j++)
		{
			if(dp[i-1][j]&&dp[i-1][j]+log2(a[i])>dp[i][(j*a[i])%10])
			{
				dp[i][(j*a[i])%10]=dp[i-1][j]+log2(a[i]);
				lst[i][(j*a[i])%10]=mp(i-1,j);
			}
			if(dp[i-1][j]>dp[i][j])
			{
				dp[i][j]=dp[i-1][j];
				lst[i][j]=mp(i-1,j);
			}
		}
	}
	if(!dp[n][m])
	{
		printf("-1");
		return 0;
	}
	dfs(n,m);
	printf("%d\n",cnt);
	for(int i=1;i<=cnt;i++) printf("%d ",s[i]);
	return 0;
}
```



---

## 作者：123zbk (赞：1)

首先想到 dp，设 $dp_{i,j}$ 表示前 $i$ 个数乘积个位数为 $j$ 的最大乘积。

但是 $n \le 10^5,a_i \le1000$，如果直接乘起来的话肯定会爆。根据 $x\times y=2^{\log x+\log y}$ 可知，我们可以用指数算，化乘法为加法，然后分选不选第 $i$ 个数转移就行了。

但是这道题要输出方案，所以我们在转移时维护一个 $pre$ 数组，记录下每组数是由哪些数转移过来的，最后 dfs 一遍输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,a[maxn];
double dp[maxn][10];
vector <int> ans;
pair <int,int> pre[maxn][10];
void dfs(int x,int y)
{
	int xx=pre[x][y].first;
	int yy=pre[x][y].second;
	if(dp[x][y]!=dp[xx][yy])
	{
		ans.push_back(a[x]);
	}
	if(xx==0 and yy==0)
	{
		return;
	}
	dfs(xx,yy);
}
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) 
	{
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++)
	{
		dp[i][a[i]%10]=log2(a[i]);
		for(int j=0;j<=9;j++)
		{
			if(dp[i-1][j] and dp[i-1][j]+log2(a[i])>dp[i][(j*a[i])%10])//选 
			{
				dp[i][(j*a[i])%10]=dp[i-1][j]+log2(a[i]);
				pre[i][(j*a[i])%10]=make_pair(i-1,j);
			}
			if(dp[i-1][j] and dp[i-1][j]>dp[i][j])//不选 
			{
				dp[i][j]=dp[i-1][j];
				pre[i][j]=make_pair(i-1,j);
			}
		}
	}
	if(!dp[n][m])
	{
		puts("-1");
		exit(0);
	}
	dfs(n,m);
	cout<<ans.size()<<"\n";
	for(auto it:ans)
	{
		printf("%d ",it);
	}
	return 0;
}
```

---

## 作者：lovely_qiqi (赞：0)

## 思路

显然的 trick 题目。如果不会背包左转 [这里](https://oi-wiki.org/dp/knapsack/#0-1-%E8%83%8C%E5%8C%85) 以及方案的转移。

发现可以转换成一个背包问题，体积就是选中的物体乘起来再取模 $10$，而价值就是它本身的乘积。显然价值使用高精度会 MLE。于是考虑一个经典的 trick：**化乘为加**，（所有 $\log$ 都是以 $2$ 为底）也就是 $x\times y=2^{\log{x}}\times2^{\log{y}}=2^{\log{x}+\log{y}}$。

那么直接把原本的价值 $x$ 改成 $\log{x}$ 就可以了，容易证明原本的相对大小是不会改变的。

### 扩展
HDU 3666
>给你一个的 $n\times m$ 的整数矩阵 H，矩阵的每个格子都有数字，位于格子 $(i,j)$ 的数字为 $H_{i,j}$。
$\\$希望你能帮忙构造两个整数数列 A 和 B,
让 A 数列有 $n$ 个元素编号 $1$ 到 $n$，B 数列有 $m$ 个元素编号 $1$ 到 $m$。
$\\$将按照如下公式对矩阵中的每个数字进行估价:
$V_{i,j}=h_{i,j}*A_i/B_j$
$\\$要求矩阵每个数字的估价值都在 $x$ 和 $y$ 之间。
$\\$即 $x \le V_{i,j} \le y$，$1\le i \le n$，$1 \le j \le m$。
能否构造出满足条件的数列 A，B，能输出 YES，不能输出 NO。

那这个题也是一样的，$x \le V_{i,j} \le y$ 直接移项两边同时除以 $V_{i,j}$ 再取 $\log$ 就变成了差分约束板子题。代码网上搜一下就有了。 
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,d,t1,t2,inv,a[100010];
double dp[100010][12];
stack<int> s;
pair<int,int> path[100010][12],now;
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>n>>d;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		dp[i][a[i]%10]=log2(a[i]);
		for(int j=0;j<=9;j++){
			if(dp[i-1][j]&&dp[i-1][j]+log2(a[i])>dp[i][j*a[i]%10]){
				dp[i][j*a[i]%10]=dp[i-1][j]+log2(a[i]);
				path[i][j*a[i]%10].first=i-1;
				path[i][j*a[i]%10].second=j;
			}
			if(dp[i-1][j]&&dp[i-1][j]>dp[i][j]){
				dp[i][j]=dp[i-1][j];
				path[i][j].first=i-1;
				path[i][j].second=j;
			}
		}
 	}
 	if(dp[n][d]==0){
 		cout<<"-1";
 		return 0;
 	}	
 	now={n,d};
 	while(true){
 		if(now.first==0&&now.second==0) break;
		t1=now.first;t2=now.second;
 		if(dp[t1][t2]!=dp[path[t1][t2].first][path[t1][t2].second]) s.push(a[t1]);	
		now=path[t1][t2];
	}
	cout<<s.size()<<"\n";
	while(!s.empty()){
		cout<<s.top()<<" ";
		s.pop();
	}
	return 0;
}
```

---

## 作者：ziyistudy (赞：0)

第一眼肯定能想到 dp。及 $dp_{i,j}$ 表示选到第 $i$ 个数，乘积个位为 $j$。

可是发现数太多了，肯定会爆。这时就要用到一个很常用的套路，及 $\log_{}{A}\times \log_{}{AB}=\log_{}{AB}$。那这样我们就可以成功将乘法转为加法，肯定不会爆。

最后只需要用一个 $pre$ 记录上一个是由什么转过来的，注意：浮点数不能使用等于比大小。

[code](https://codeforces.com/contest/1510/submission/257050266)

---

