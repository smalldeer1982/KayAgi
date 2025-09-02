# Rotate Columns (easy version)

## 题目描述

这是下一个问题的简化版，区别仅在于约束条件不同。

给定一个 $n \times m$ 的矩阵 $a$。每次操作你可以选择任意一列，并将该列中的元素循环移动一次。你可以对任意列进行任意多次（也可以不进行）这样的操作，同一列也可以多次操作。

完成所有循环移动后，对于每一行，计算该行的最大值。设第 $i$ 行的最大值为 $r_i$。请问 $r_1 + r_2 + \ldots + r_n$ 的最大可能值是多少？

## 说明/提示

在第一个测试用例中，你可以将第三列向下循环移动一次，这样可以得到 $r_1 = 5$，$r_2 = 7$。

在第二个测试用例中，你可以不进行任何旋转，此时 $r_1 = r_2 = 10$，$r_3 = 9$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
2
2 3
2 5 7
4 2 4
3 6
4 1 5 2 10 4
8 6 6 4 9 10
5 4 9 5 8 7
```

### 输出

```
12
29
```

# 题解

## 作者：Eibon (赞：5)

发现 $n \le 4$，但是 $m$ 很大，容易得出结论，我们只需要最大值前 $n$ 大的列。如果用到第 $n+1$ 大的列，那么前面的列一定能用本列的最大值去替换这一列。

$n$ 很小，不妨考虑暴搜。

从 $0$ 到 $n$ 枚举位移，保存状态，不断更新 $ans$ 即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=100;
int T,n,m,ans;
int num[8],x[8][8][8];
struct node
{
	int b[8],w;
	bool operator < (const node &x) const
	{
		return w>x.w;
	}
};
node a[maxn];
void dfs(int j)
{
	if(j>n){
		int res=0;
		for(int i=1;i<=n;i++){
			res+=num[i];
		}
		ans=max(ans,res);
		return;
	}
	for(int k=0;k<n;k++){
		for(int i=1;i<=n;i++){
			x[j][k][i]=num[i];
			int s=i+k;
			if(s>n){
				s=s%n;
			}
			num[i]=max(num[i],a[j].b[s]);
		}
		dfs(j+1);
		for(int i=1;i<=n;i++){
			num[i]=x[j][k][i];
		}
	}
}
signed main()
{
	scanf("%lld",&T);
	while(T--){
		ans=0;
		memset(num,0,sizeof num);
		memset(x,0,sizeof x);
		memset(a,0,sizeof a);
		scanf("%lld%lld",&n,&m);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%lld",&a[j].b[i]);
				a[j].w=max(a[j].w,a[j].b[i]);
			}
		}
		sort(a+1,a+m+1);
		dfs(1);
		printf("%lld\n",ans);
	}
	return 0;
}
//dyyyyds
```

---

## 作者：Qiiiiiii_ (赞：4)

题意描述：$T$ 次询问，每次给定一个 $n*m$ 的矩阵，每次可以将一列循环任意次。设 $r_i$ 表示第 $i$ 行的最大值，求所有可能的操作下 $\sum r_i$ 最大值。 $(T\le40,n\le12,m\le100)$

考虑到 $n$ 很小，显然就是状态压缩，但是 $m$ 很大，所以就思考这 $m$ 个必是唬人的。先猜一个结论，我们只用取每列最大值排名前 $n$ 的。考虑为什么。当我们取第 $n+1$ 大的那一列的时候，我们选前 $n$ 名取满一定不会更劣，而第 $n+1$ 大的那一列中不存在比那个列的最大值排名第 $n+1$ 的值更大的值了，所以必然不劣。然后就是对 $n*n$ 的矩阵求原值，这个用状态压缩 $dp$ 可以轻易通过。 设 $dp[i][j]$ 表示选到第 $i$ 列，强制选了状态为 $j$ 的行的最大值。时间复杂度$O(n3^n)$。  

```
#include<bits/stdc++.h>
#define re register
#define ll long long
#define LL inline ll
#define I inline int
#define V inline void
#define B inline bool 
#define FOR(i,a,b) for(re int i=(a),i##i=(b);i<=i##i;++i)
#define ROF(i,a,b) for(re int i=(a),i##i=(b);i>=i##i;--i)
//#define gc getchar()
#define gc (fs==ft&&(ft=(fs=buf)+fread(buf,1,1<<18,stdin),ft==fs))?0:*fs++
using namespace std;
char *fs,*ft,buf[1<<18];
const int N=1e4+10;
LL read(){
	ll p=0; bool w=0; char ch=gc;
	while(!isdigit(ch)) w=ch=='-'?1:0,ch=gc;
	while(isdigit(ch)) p=p*10+ch-'0',ch=gc;
	return w?-p:p;
}
int T,n,m,a[30][N],mx[N],ans;
int dp[2][N],f[20][N],sck[20],fl;
I get(int x,int zt){
	int res=0,as=0,tmp=zt;
	FOR(i,1,n){
		tmp=zt,as=0;
		FOR(j,i,i+n-1) (as+=(tmp&1)?a[j][x]:0),tmp>>=1;
		res=max(res,as);
	}
	return res;
}
V sol(){
	int tot=(1<<n)-1,tmp=0,bj=0;
	FOR(k,1,n) { 
		tmp=0,bj=0; 
		FOR(i,1,m) if(mx[i]>tmp) tmp=mx[i],bj=i;
		sck[k]=bj,mx[bj]=0;
	}
	FOR(k,1,n) FOR(j,0,tot) f[k][j]=get(sck[k],j);
	FOR(i,1,n){
		FOR(j,0,tot){
			int w=tot^j;
			dp[fl][j]=max(dp[fl][j],dp[fl^1][j]);
			for(re int k=w;k;k=(k-1)&w) 
				dp[fl][j|k]=max(dp[fl][j|k],dp[fl^1][j]+f[i][k]);
		}
		fl^=1;
		memset(dp[fl],0,sizeof(dp[fl]));
	}
	fl^=1;
	ans=dp[fl][tot];
	printf("%d\n",ans);
	return ;
}
V init(){
	memset(mx,0,sizeof(mx));
	memset(dp,0,sizeof(dp));
	return ;
}
int main(){
	T=read();
	while(T--){
		n=read(),m=read(),ans=0;
		init();
		FOR(i,1,n) FOR(j,1,m) a[i][j]=read(),mx[j]=max(mx[j],a[i][j]);
		FOR(i,n+1,2*n) FOR(j,1,m) a[i][j]=a[i-n][j];
		sol();
	}
	return 0;
}
```


---

## 作者：FjswYuzu (赞：3)

注意到整个 $n \times m$ 的矩阵中实际只有 $n^2$ 数是有用的，因为我们最坏的情况下，我们会选择 $n$ 列中的最大值对应我们的每一行。

于是矩阵被我们缩小到了 $4 \times 4$ 的范围，直接搜就行了。

---

## 作者：Foofish (赞：2)

相信题意大家已经都了解了，我们思考一下如何解决这道题目。

因为 $m$ 有 $100$，远比 $n$ 大，我们要尝试能不能把他弄掉。

> 我们只可能用到**列里最大值最大**的前 $n$ 个列

证明：

假设我们用到了最大值最第 $n+1$ 大的那个列。假如说他用到了这个列里的某些值，那么这些值肯定没有那些 $i,i\leq n$ 列的最大值大，那么我们大可以用那些前 $n$ 列的最大值替换现在这个列里用到的那些值，这样只会使答案更优。

我们已经将 $m$ 也降到了 $n$ 的级别了。

暴力枚举所有情况。直接令 $dp_{i,j}$ 表示现在选到了第 $i$ 行，已经确定选那些行的状态是 $j$ 的最大值。转移就枚举 $j$ 的子集 $k$ 表示上一行中已经确定的状态。那么就有状态转移方程 $dp_{i,j}=dp_{i,k}+w_{k\ xor \ j}$ 其中 $w_k$ 表示现在这一行中我已经确定的状态经过移位后的最大值。

有聪明的彦祖就会问了，如果我这一位最后明明不是行里的最大值，但是还是把他当做了最大值，这不是错误的么？

当然不是，因为就算这种选法是错误的，正是因为他不是行里的最大值，所以取最大的时候他肯定没正确的选法更大，所以不会对答案造成影响。

------------

然后我们计算一下时间复杂度。

枚举子集的复杂度是 $\mathcal{O}(3^n)$ 这里也稍微证明一下

令二元组 $(S,T),T\subseteq S$ 这就表示我们枚举的集合 $S$ 和子集 $T$ 。我们思考一下每一个元素可能的情况


$k\in S,k\notin Tk∈S,k∉T$
1. $k\in S,k\notin T$
2. $k\in S,k\in T$
3. $k\notin S,k\notin T$

所以对于每一种元素有 $3$ 种情况，那么总时间复杂度就是 $\mathcal{O}(3^n)$

话说上文，枚举了子集之后，我们还要计算 $w_{k\ xor\ j}$ 的值，因为还要移位所以计算 $w_{k\ xor\ j}$ 的复杂度是 $\mathcal{O}(n^2)$ 总时间复杂度就是 $\mathcal{O}(n^33^n)$ 

因为 $n$ 只有 $4$，完全可以通过本题。这种做法也已经距离 E2 很接近了。

---

## 作者：liu_yi (赞：2)

## 题目大意

给定一个 $n\times m$ 的矩阵，可以对每一列进行若干次循环位移，求经过若干次操作后每一行的最大值之和的最大值。

## 解题思路

注意到 $n$ 较小，$m$ 较大，所以这个 $m$ 肯定是要缩小的，考虑每列按最大值排序，只取前 $n$ 列，这样就变成了 $n\times n$ 的矩阵了，这样为什么是对的呢？

证明：如果现在取到是第 $n + 1$ 列，那么是没有让前 $n$ 列的最大值换到每一行更优的。

所以现在 $n,m \leq 4$ 了，考虑暴搜，对于每一列，枚举循环位移几位，在统计答案即可。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int T,n,m,M,ans,sum,Max[5];
struct node{
    int b[5],maxn;
}a[110];
inline int read(){
	register int step=1,s=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
	    if(ch=='-')step=-1;
	    ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
	    s=(s<<1)+(s<<3)+(ch^48);
	    ch=getchar();
	}
	return step*s;
}
bool cmp(node x,node y){
    return x.maxn>y.maxn;
}
inline void get(){
    sum=0;
    for(int i=0;i<M;i++)for(int j=0;j<n;j++)Max[j]=max(Max[j],a[i].b[j]);
    for(int i=0;i<n;i++){
        sum+=Max[i];
        Max[i]=0;
    }
}
inline void dfs(){
    get();
    if(sum<=ans)return ;
    ans=sum;
    for(int i=0;i<M;i++){
        int c[5];
        for(int j=0;j<n;j++)c[j]=a[i].b[j];
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++)a[i].b[(k+j)%n]=c[k];
            dfs();
        }
        for(int j=0;j<n;j++)a[i].b[j]=c[j];
    }
}
int main(){
    T=read();
    while(T--){
        ans=0;
        n=read(),m=read();
        M=min(n,m);
        for(int i=0;i<m;i++)a[i].maxn=0;
        for(int i=0;i<n;i++)for(int j=0;j<m;j++)a[j].b[i]=read(),a[j].maxn=max(a[j].maxn,a[j].b[i]);
        sort(a,a+m,cmp);
        dfs();
        cout<<ans<<endl;
    }  
    return 0;
}
```

---

## 作者：QQzhi (赞：1)

# 状压动规（逐步详解）

先贴个链接~（双倍经验题单碎片）

- [Codeforces 青春版原题面](https://codeforces.com/problemset/problem/1209/E1) 

- [Codeforces 标准版原题面](https://codeforces.com/problemset/problem/1209/E2)

- [洛谷 青春版题面](https://www.luogu.com.cn/problem/CF1209E1)

- [洛谷 标准版题面](https://www.luogu.com.cn/problem/CF1209E2)

## 逐步分析

这道题要求在任意滚动原矩阵的任意列后求每行的最大值之和的最大值。

状态压缩的题非常好判断，扫一眼数据范围，发现本题就可作为状压动规的练手题。

**初始化**

观察容易发现，最后对答案有贡献的数据每行有且只有一个。进一步可知，只有列内最大值为前 $n$ 大的列才会对答案有贡献，可以自行反证一下当引入其他列后答案是否最优。

故读入后，分别计出每列最大值后降序排序，切去矩阵多余部分。

```cpp
constexpr int N=12,M=2000;
int n,m,dp[N+1][1<<N],sum[1<<N];
std::vector<int> col[M];
int w;
void init(){
	cin>>n>>m;
	w=1<<n; // 状态总数共有 2^n 种
	for (int i=0;i<m;i++)
		col[i].resize(n+1);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			cin>>col[j][i];
	for (int i=0;i<m;i++)
		col[i][n]=*std::max_element(col[i].begin(),col[i].begin()+n); // 计算列内最大值
	std::sort(col,col+m,[=](const auto &a,const auto &b){
		return a[n]>b[n]; // 按列内最大值降序排序
	});
	m=min(n,m); // 裁取有效列
}
```

**选定状态**

答案最终要每行都有数据贡献，这里令状态表示贡献集合， $s$ 的第 $i$ 位表示第 $i+1$ 行有无数据贡献。

**计算滚动前贡献**

遍历状态，计算未滚动时该列对各种状态的贡献。

```cpp
for (int j=0;j<w;j++){
  sum[j]=0;
  for (int k=0;k<n;k++)
    if (j&(1<<k))
      sum[j]+=col[i][k];
}
```

**计算滚动后贡献**

状态滚动起来可比原数据滚动省心，对各个状态进行滚动以计算滚动后该列对每种状态的最大贡献。

```cpp
for (int j=0;j<w;j++)
  for (int k=0;k<n;k++)
    sum[j]=max(sum[j],sum[((j<<k)|(j>>(n-k)))&(w-1)]);
// 两向位移后合并后裁取有效位实现滚动
```

**进行状压动规**

枚举目标贡献集合状态，然后再枚举其非空子集作为本列对该状态的贡献情况，进行转移。$dp_{i,j}$ 为前 $i$ 列对状态 $j$ 的最大贡献。

小技巧：观察二进制减法，可知减一操作是将最低位的 $1$ 消去，在其后全补上 $1$，然后取有效位，即可构成下一个原状态的子集。另外不要忘记转移空集时的情况。

```cpp
for (int j=0;j<w;j++){
  dp[i+1][j]=dp[i][j]; // 本列贡献为空集
  for (int k=j;k;k=(k-1)&j) // 枚举非空子集
    dp[i+1][j]=max(dp[i+1][j],dp[i][j^k]+sum[k]);
}
```

循环处理所有有效列即可。

**多测提醒**

$\color{red}{\texttt{多测不清空，白费十年功。}}$

## 整体代码

拿 502 ~~一种响应状态码~~ 胶水粘起来即可得到：

```cpp
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using std::cin;using std::cout;using std::min;using std::max;
constexpr int N=12,M=2000;
int n,m,dp[N+1][1<<N],sum[1<<N];
std::vector<int> col[M];
int w;
void init(){
	cin>>n>>m;
	w=1<<n;
	for (int i=0;i<m;i++)
		col[i].resize(n+1);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			cin>>col[j][i];
	for (int i=0;i<m;i++)
		col[i][n]=*std::max_element(col[i].begin(),col[i].begin()+n);
	std::sort(col,col+m,[=](const auto &a,const auto &b){
		return a[n]>b[n];
	});
	m=min(n,m);
}
void solve(){
	memset(dp,0,sizeof(dp));
	for (int i=0;i<m;i++){
		for (int j=0;j<w;j++){
			sum[j]=0;
			for (int k=0;k<n;k++)
				if (j&(1<<k))
					sum[j]+=col[i][k];
		}
		for (int j=0;j<w;j++)
			for (int k=0;k<n;k++)
				sum[j]=max(sum[j],sum[((j<<k)|(j>>(n-k)))&(w-1)]);
		for (int j=0;j<w;j++){
			dp[i+1][j]=dp[i][j];
			for (int k=j;k;k=(k-1)&j)
				dp[i+1][j]=max(dp[i+1][j],dp[i][j^k]+sum[k]);
		}
	}
	cout<<dp[m][w-1]<<'\n';
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	int t;
	cin>>t;
	while (t--){
		init();
		solve();		
	}
}

```

上面直接贴了 hard version 的代码，easy version 改动下数组大小常量即可。

---

## 作者：2huk (赞：1)

首先每一行的最大值之和的最大值，等价于在每一行都任意选一个数，这些数的和的最大值。

考虑状压 DP。设 $f(i, S)$ 表示若考虑前 $i$ 列，已经确定的行组成的集合为 $S$，选出的数的最大和。

转移首先让第 $i$ 列循环移位。然后枚举第 $i$ 列选了哪些行。令这些行的集合为 $T$。那么：

$$
f(i, S) = \max_{T \subseteq S}\left(\sum_{u \in T}a_u + f(i - 1, S/T)\right)
$$

答案为 $f(m, \{1,2,\dots,n\})$。把上面说的集合改成状态压缩实现即可。

<https://codeforces.com/contest/1209/submission/275189194>

E2 题解交不了了，在 E1 题解里一块写了。

$m$ 很大。但是由于每行都恰选一个点，所以有用的列一定 $\le n$。可以证明有用的列是最大值前 $n$ 大的列。

> 反证法。如果某一列的最大值不是前 $n$ 大，且我们在某些行我们选的数是这一列的。我们知道「这一列的数」$\le $「这一列的最大值」，而「这一列的最大值」$\le$「前 $n$ 大的列中，把最大放在这些行上的列的最大值」。所以不优。

所以我们将列数降到了 $n$。这是第一个优化。

第二个优化是，预处理 $w(i, j, S)$ 表示将第 $i$ 列循环移位 $j$ 次后，$\sum_{u \in S} a_{u,i}$ 的值。再维护 ${w_{\max}}_{i, S} = \max_{j=0}^{n-1} w(i, j, S)$。转移时直接查表即可。

<https://codeforces.com/contest/1209/submission/275196043>

---

## 作者：初雪_matt (赞：1)

可以发现，当 $m \geq n$ 时，按列中最大值从大到小排序，取前 $n$ 列必定更优。

因为当你去到第 $n+1$ 列以及更后面的列时，一定可以将前 $n$ 列的某一列替换这后面的列，答案一定更优（因为行数一定，答案和行数相关）。

由于 $n,m$ 同级，考虑爆搜，枚举每一列要循环移位多少次。

```cpp
#include<bits/stdc++.h>
#define N 2005
using namespace std;
int T,n,m,f[N],sum,d[N],res;
struct node{
    int b[20],maxi;
    bool operator<(const node&t)const{  
        return maxi>t.maxi;
    }
}a[N],c[N];
void dfs(int u){
    if(u==min(n,m)+1){
        memcpy(c,a,sizeof(c));
        for(int i=1;i<=min(n,m);i++){
            int tmp[6];
            for(int j=1;j<=n;j++) tmp[j]=c[i].b[j];
            for(int j=1;j<=n;j++) c[i].b[(j+d[i])%n+1]=tmp[j];
        }
        int sum=0;
        for(int i=1;i<=n;i++){
            int maxi=0;
            for(int j=1;j<=min(n,m);j++) maxi=max(maxi,c[j].b[i]);
            sum+=maxi;
        }
        res=max(sum,res);
        return ;
    }
    for(int i=0;i<n;i++){
        d[u]=i;
        dfs(u+1);
    }
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>T;
    while(T--){ 
        memset(a,0,sizeof(a));
        memset(d,0,sizeof(d));
        res=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) cin>>a[j].b[i],a[j].maxi=max(a[j].maxi,a[j].b[i]);
        sort(a+1,a+m+1);
        dfs(1);
        cout<<res<<endl;
    }
}
```

---

## 作者：Ghosty_Neutrino (赞：0)

这是 easy version 哇。
## 题意
给你一个 $n \times m$ 的矩阵，你可以对任意列进行任意次操作，即将该列进行上下循环移位，然后从每行挑出来一个数，使得这 $n$ 个数的和最大。
## 思路
首先脑海里蹦出了个 DP，因为是**和最大**。

方法就是用状压 DP，$dp_{i,k}$ 表示前 $i$ 列，状态为 $k$ 时的最大和。

一边枚举一边考虑更新以后的状态，于是我们枚举另一个可以转移的状态，但需要满足条件为：**两个状态不能有交集**，因为数字不能被重复选择。

当前状态 $k$，枚举可以转移的状态 $p$，中间加个或运算，那么状态转移方程就出现了：
```cpp
dp[i][k|p]=max(dp[i][k|p],dp[i-1][p]+val);
```
$val$ 是状态 $k$ 包含的值的和，目标状态为就是下面的代码，最后输出它就行了：

```cpp
dp[m][(1<<n)-1];
```
## 提示一些低级错误：
* 由于有多组数据，$dp$ 数组一定要清零，不然输出怪怪的。
* $val$ 在每次循环移位时都要清零。
* 变量过多不要弄混，劝你别用 $a$，$b$，$c$，$d$，真的眼花，循环变量 $i$，$j$ 不要搞错关系。
## 核心代码

```cpp
memset(dp,0,sizeof(dp));
//都给我清！零！
//输入用不着讲
for(int i=1;i<=m;i++){
    for(int k=0;k<(1<<n);k++){
        for(int o=1;o<=n;o++){//循环移位
            int val=0;
            //也给我清！零！
            for(int j=1;j<=n;j++)
                if(k&(1<<j-1)) val+=a[j][i];
            for(int p=0;p<(1<<n);p++)
                if(!(k&p)) dp[i][k|p]=max(dp[i][k|p],dp[i-1][p]+val);//没有交集，转移！
                //直接套状态转移方程
            for(int j=1;j<=n;j++) a[j-1][i]=a[j][i];
            a[n][i]=a[0][i];
        }
    }
}//最后再输出就OK
```

---

## 作者：RainWorld_XIV (赞：0)

[更好的阅读体验](https://www.cnblogs.com/MithrilSwordXIV/p/18351402)

[题目传送门](https://www.luogu.com.cn/problem/CF1209E1)


## 题意

给出一个 $n\times m$ 的矩阵，我们可以对每一列进行循环位移，不限次数，最后求每一行的最大值之和。

$1 \leq n \leq 4 , 1 \leq m \leq 100$

## 思路

注意到 $n$ 的范围很小，那么我们也可以缩小 $m$ 的范围。

正确的方案显然是取整个矩阵的前 $n$ 大值，并且将它们换到每一行。即便这 $n$ 大值分布在不同的列，也一共只有 $n$ 列，因此整个矩阵的有效范围只有 $n \times n$。

现在就可以随意的爆搜了，对于每一列，循环枚举位移的行数，最后统计答案即可，注意多测要清空。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long 
#define inf 0x7f7f7f7f
using namespace std;
int lst[105][105][105],T,n,m;
int maxx[105],ans=-inf;
struct MRS{
	int sr[105],maxn;//sr存行 
	bool operator<(const MRS &x){return maxn>x.maxn;}
}mp[105];//存列 
bool cmp(int a,int b){return a>b;}
void dfs(int x){
	if(x>n){//搜索结束 
		int sum=0;
		for(int i=1;i<=n;i++)sum+=maxx[i];
		ans=max(ans,sum);
		return;
	}
	for(int i=0;i<=n-1;i++){
		for(int j=1;j<=n;j++){
			int tmp=((i+j)==n)?(i+j):(i+j)%n;//注意当下标等于n时不取余 
			lst[x][i][tmp]=maxx[tmp];//记录当前情况 
			maxx[tmp]=max(maxx[tmp],mp[x].sr[j]);//更新 
		}
		dfs(x+1);
		for(int j=1;j<=n;j++)maxx[j]=lst[x][i][j];//回溯 
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--){
		ans=0;
		memset(mp,0,sizeof(mp));
		memset(lst,0,sizeof(lst));
		memset(maxx,0,sizeof(maxx));
		cin>>n>>m;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)cin>>mp[j].sr[i],mp[j].maxn=max(mp[j].maxn,mp[j].sr[i]);//存储每一列的的最大值，之后按此排序 
		sort(mp+1,mp+1+m);
		dfs(1);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：FRZ_29 (赞：0)

# codeforces 1209E1 Rotate Columns (easy version)
题目传送门：[codeforcces](https://codeforces.com/contest/1209/problem/E1) ， [luogu](https://www.luogu.com.cn/problem/CF1209E1)
   
[也许更好的阅读体验](https://www.cnblogs.com/FRZ29/p/18328329)

## 思路
贪心，暴力搜索

### 贪心
对于所有列，只有列中最大值在所有列的最大值中前 $n$ 大才可能对答案有贡献。  
证明：若有非前 $n$ 大的列对某行最大值产生了贡献，则用没有被取的前 $n$ 大的列代替该行一定更优。所以只有列中最大值在所有列的最大值中前 $n$ 大才可能对答案有贡献。  

### 暴力搜索
将所有列按列的最大值从大到小排序。根据贪心，答案一定由前 $n$ 列产生，而 $n \leq 4$ ，所以直接爆搜就行了。

## 细节
更新的时候要先保存，不然回溯会出错。

## 代码
单次时间复杂度$O(n^{2 \times n - 2})$
~~~cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 6, M = 105;

#define LF(i, __l, __r) for (int i = __l; i <= __r; i++)
#define RF(i, __r, __l) for (int i = __r; i >= __l; i--)

struct col { int a[N], mx; } a[M];
int t, n, m, ans, mx[N];
int back[N][N][N];

bool cmp(col a, col b) { return a.mx > b.mx; }

void Init() {
    ans = 0;
    memset(mx, 0, sizeof(mx));
    memset(back, 0, sizeof(back));
    memset(a, 0, sizeof(a));
}

void dfs(int u) {
    if (u == n + 2) {
        int res = 0;
        LF(i, 1, n) res += mx[i];
        ans = max(ans, res);
        return;
    }

    LF(i, 0, n - 1) {
        LF(j, 1, n) {
            int s = i + j;
            if (s > n) s %= n;
            back[u][i][s] = mx[s];
            mx[s] = max(mx[s], a[u].a[j]);
        }
        dfs(u + 1);
        LF(j, 1, n) mx[j] = back[u][i][j];
    }
}

int main() {
    scanf("%d", &t);

    while (t--) {
        Init();
        scanf("%d%d", &n, &m);
        LF(i, 1, n) LF(j, 1, m) {
            scanf("%d", &a[j].a[i]);
            a[j].mx = max(a[j].mx, a[j].a[i]);
        }

        sort(a + 1, a + m + 1, cmp);
        
        dfs(1);
        printf("%d\n", ans);
    }
    return 0;
}
~~~

---

## 作者：detect (赞：0)

### [T5-1](https://codeforces.com/contest/1209/problem/E1)


题意：给你一个n*m表格，你可以把每一列向上或向下移动（边界自动跳），现在你要移动表格，使每一行最大数的和最大。



------------


然而似乎朴素贪心都不对。

因为是弱版嘛，自然可以考虑稍微暴力点的做法---状压dp

强行枚举每一列的状态，然后再在状态中枚举子状态，再更新：

```cpp
dp[i][j]=max(dp[i][j],dp[i-1][k]+solve(i,j-k));//想多久加上就多久加上
```



------------

code

```cpp
#include<bits/stdc++.h>
using namespace std;
int getint()
{
    int summ=0,f=1;
    char ch;
    for(ch=getchar();!isdigit(ch)&&ch!='-';ch=getchar());
    if(ch=='-')
    {
        f=-1;
        ch=getchar();
    }
    for(;isdigit(ch);ch=getchar())
        summ=(summ<<3)+(summ<<1)+ch-48;
    return summ*f;
}
bool cmp(int x,int y)
{
	return x>y;
}
int n,m,maxx=0,ans,num[15][2010],dp[2010][4500];
int solve(int x,int s)
{
	ans=0;
	for(int i=1;i<=n;i++)
	{
		int sum=0,k=1;
		for(int j=1;j<=n;j++)
		{
			if(k&s) sum+=num[j][x];//加上对应值
			k<<=1;
		}
		ans=max(ans,sum);
		for(int j=n;j>=1;j--)
		num[j+1][x]=num[j][x];
		num[1][x]=num[n+1][x];//按顺序旋转
	}
	return ans;
}
int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		  for(int j=1;j<=m;j++)
		    num[i][j]=getint();
		int maxn=(1<<n)-1;
		for(int i=1;i<=m;i++)
		{
			memset(dp[i],0,sizeof(dp[i]));
			for(int j=0;j<(1<<n);j++)//枚举状态
			{
				for(int k=j;;k=(k-1)&j)//枚举子集
				{
					dp[i][j]=max(dp[i][j],dp[i-1][k]+solve(i,j-k));
					if(k==0) break;
				}
			}
		}cout<<dp[m][(1<<n)-1]<<endl;
	}	 
	return 0;
} 
```



---

