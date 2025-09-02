# [POI 2010] CHO-Hamsters

## 题目描述

Byteasar 养了许多仓鼠。

每只仓鼠都有一个唯一的名字，由小写英文字母组成。

这些仓鼠有一个宽敞舒适的笼子。

Byteasar 打算在笼子下方放置一个显示器，以可视化显示他仓鼠的名字。

这个显示器只是一个字母序列，每个字母可以独立地亮起或不亮起。

同时只会显示一个名字。

亮起的字母必须相邻，即形成一个连续的子序列。

Byteasar 希望能够在至少 $m$ 个不同的位置显示这些仓鼠的名字。

然而，他允许在多个不同的位置显示相同的名字，并且不要求能够显示每一个仓鼠的名字。

注意，名字在显示器上的出现可以重叠。

可以假设没有任何仓鼠的名字会作为连续片段出现在其他仓鼠的名字中。

Byteasar 请求你帮助确定显示器需要的最小字母数。

换句话说，你需要确定一个字符串的最小长度（由非大写英文字母组成），使得仓鼠名字的总出现次数（计入重复）至少为 $m$。

（我们说字符串 $A$ 出现在字符串 $B$ 中，如果 $A$ 形成 $B$ 的一个连续片段。）

## 说明/提示

$1 \le n \le 200$，$1 \le m \le 10^9$，所有字符串的总长 $\le 10^5$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
4 5
monika
tomek
szymon
bernard```

### 输出

```
23```

# 题解

## 作者：wlzhouzhuan (赞：33)

讲一下自己的大致思路。

先说一下暴力分：

这是我看到此题的第一反应：`dp`，复杂度为$O(n^2m)$。


我们先定义两字符串间的距离值$dis[i][j]$，表示$j$号串拼接在$i$号串之后，需要在$i$号串末尾添加的字符数。

此时我们再用$dp[i][j]$ 表示这个串里应经有了$i$个字符串，并且最后出现在该串里的子串是$j$号串的答案，显然可以按下转移：

$dp[1][i]=len(i)$，表示取1个字符串，并且是第$i$个字符串结尾，那么它的代价显然是$len(i)$

$dp[i][j] = min\{ dp[i-1][k]+dis[k][j]\}$，我们在$k$号字符串
后面拼接上$j$号字符串，添加字符量即为$dis[k][j]$。

注意转移时的顺序，应该先枚举$i$，再枚举$j$和$k$。读者可以想想，为什么？

贴一下`dp`的核心部分：

```cpp
void DP() {
  memset(dp, 0x7f, sizeof(dp));
  for (int i = 1; i <= n; i++)
    dp[1][i] = len[i];
  for (int i = 2; i <= m; i++)
    for (int j = 1; j <= n; j++)
      for (int k = 1; k <= n; k++)
        dp[i][j] = min(dp[i][j], dp[i - 1][k] + dis[k][j]);
}
```

所以，我们分析想到了转移公式，那么答案即为$min\{ dp[m][i]\}$，其中$1\le i\le n$（因为一共有$n$种字符串）。

看到有$n$个字符串，并且是一个个字符串首尾拼接而成的，我们很自然的想到`AC自动机`。


在本人经过长达1小时的思考后，终于想出了正解。。。


本人比较擅长`KMP算法`，看到这题，果断想到是`KMP`，粗略计算一下，`KMP()`函数部分的复杂度为$O(\sum^{n}_{i=1}\sum^{n}_{j=1}(len(i)+len(j)))= O(\sum^{n}_{i=1}(n\times len[i]+\sum |S|))≈ O(n|S|)$，稍微带一点小常数。

下面是`KMP`部分的代码：

```cpp
void KMP() {
  // kmp1：单个字符串内匹配
  for (int p = 1; p <= n; p++) {
    int j = 0;
    for (int i = 2; i <= len[p]; i++) {
      while (j > 0 && str[p][j + 1] != str[p][i])
        j = nxt[p][j];
      if (str[p][j + 1] == str[p][i]) j++;
      nxt[p][i] = j;
    }
  }
  
  // kmp2：两两字符串间匹配
  for (int p1 = 1; p1 <= n; p1++) {
    for (int p2 = 1; p2 <= n; p2++) {
      int j = 0;
      for (int i = 2; i <= len[p1]; i++) {
        while (j > 0 && str[p2][j + 1] != str[p1][i])
          j = nxt[p2][j];
        if (str[p2][j + 1] == str[p1][i]) j++;
        if (i == len[p1]) {
          a.v[p1][p2] = len[p2] - j;
        }
      }
    }
  }
}
```

好，既然我们已经预处理`KMP`得到了两两字符串间的关系（末尾添加字符量），那么我们接下来考虑如何优化`dp`。

读者不妨再回头去看看`dp`的转移部分，有没有发现，这个转移方式似曾相识？

没错，这似乎与`floyd`的转移代码有异曲同工之妙。它的转移方式，跟`floyd`是一模一样的！那么这个转移方式等价于一个$O(n^3)$的`floyd`，我们从另一种角度去考虑如何优化这个伪的`floyd`。

在优化复杂度之前，请读者先考虑一些细节问题：

首先，将这个转换成`floyd`，是基于点操作的，我们可以将每一个字符串的每一个字符都视作是一个点，这下次就是彻彻底底的`floyd`了233。

其次，我们不知道该从第几号字符串作为整一个串的起点，所以我们考虑加一个`超级源`，设它为$0$号串，将$0$号串连接到第$i(1\le i\le n)$号串。从$0$到$i$的权值为$dis[0][i] = len(i)$，从$i$到$0$显然做不到，所以设置为无穷大，即：$dis[i][0] = inf$。

好了，接下来我们考虑如何去优化复杂度。

很显然，数据范围中$m$的范围特别大，已经到了$1e9$的地步，此时我们就数据范围倒推，显然不可能是$O(m)$线性扫，所以极大可能是$O(\sqrt{m})$或者$O(logm)$。

如果是$O(\sqrt{n})$，那么一定有关于开根号的东西，但`floyd`显然不可能与根号发生关系，所以暂时排除。

那么我们发现只可能是$O(logm)$的复杂度内运行`floyd`，此时我们果断想到：与$log$有关的，极大可能是`快速幂`，但这不是$a^p$的形式，而是一个二维的幂形式。

相信读者都已经猜到了，这就是`矩阵快速幂`！

综上，我们发现，这道题可以在$O(n|S|+n^2*log\space m)$的复杂度内跑出结果，常数较小，值得一试。

同时，作为前人，也提醒一下大家：这道题可能要开$-O2$才能$AC$,`数据#1`稍微有点卡常数！

献上代码，完美撒花：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef long long ll;

const int N = 202;
const int M = 100002;
string str[N];
int len[N], t;
int nxt[N][M];
//int dis[201][201];
int n, m;

struct MAT {
  ll v[N][N];
  void print() {
    for (int i = 0; i <= n; i++, puts(""))
      for (int j = 0; j <= n; j++)
        printf("%lld ", v[i][j]);
    putchar('\n');
  }
} ans, a;

MAT operator * (MAT a, MAT b) {
  MAT c;
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      c.v[i][j] = 1e15;
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      for (int k = 0; k <= n; k++)
        c.v[i][k] = min(c.v[i][k], a.v[i][j] + b.v[j][k]);  
  return c;
}

void KMP() {
  // init
  a.v[0][0] = 1e15;
  for (int p = 1; p <= n; p++)
    a.v[0][p] = len[p], a.v[p][0] = 1e15;
  
  // kmp1
  for (int p = 1; p <= n; p++) {
    int j = 0;
    for (int i = 2; i <= len[p]; i++) {
      while (j > 0 && str[p][j + 1] != str[p][i])
        j = nxt[p][j];
      if (str[p][j + 1] == str[p][i]) j++;
      nxt[p][i] = j;
    }
  }
  
  // kmp2
  for (int p1 = 1; p1 <= n; p1++) {
    for (int p2 = 1; p2 <= n; p2++) {
      int j = 0;
      for (int i = 2; i <= len[p1]; i++) {
        while (j > 0 && str[p2][j + 1] != str[p1][i])
          j = nxt[p2][j];
        if (str[p2][j + 1] == str[p1][i]) j++;
        if (i == len[p1]) {
          a.v[p1][p2] = len[p2] - j;
        }
      }
    }
  }
  
  /*
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
      printf("dis[%d][%d] = %d\n", i, j, dis[i][j]);
  */
}

void ksm() {
  //a.print();
  
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      ans.v[i][j] = a.v[i][j];
  
  // woc, m--!   
  m--;
  while (m > 0) { 
    //printf("in ksm %d\n", m);
    //ans.print(); a.print();
    //printf("----------\n");
    if (m & 1) ans = ans * a;
    a = a * a; m >>= 1;
  }
}

bool check() {
  for (int i = 1; i <= n; i++) {
    if (len[i] == 1) return 1;
  }
  return 0;
}

signed main() {
  scanf("%lld%lld", &n, &m);
  if (m == 0) {
    puts("0"); return 0;
  }
  
  for (int i = 1; i <= n; i++) {
    cin >> str[i];
    len[i] = str[i].size();
    str[i] = ' ' + str[i];
  }
  
  if (check()) {
    printf("%lld\n", m);
    return 0;
  }
  
  KMP();
  ksm();
  
  ll anss = 2e15;
  for (int i = 1; i <= n; i++)
    anss = min(anss, ans.v[0][i]);
  printf("%lld\n", anss);
  return 0;
}
```

附：如果有$WA$的网友，我在这里提供几组$hack$数据，您可以不妨一测。

$\color{red}hack1.in$
```cpp
5 100
a
b
c
d
e
```

$\color{red}hack1.out$
```cpp
100
```

$\color{red}hack2.in$
```
1 0
a

```
$\color{red}hack2.out$
```
0
```

$\color{red}hack3.in$
```
4 5
ab
bc
cd
de
```

$\color{red}hack3.out$
```
7
```


---

## 作者：租酥雨 (赞：11)

本来这题是联赛模拟的一道T3，然而在联赛前一天被我找到了原题...

话不多说讲做法

首先互不包含是一个很重要的前提，这说明n个字符串在答案串S中的m次出现一定会**依次出现**（指的是m次出现的首位置一定会不同，但m次出现可能会存在重叠）

那么我们预先处理出来每个串接在另一个串的后面所需要**新添加的字符数量**，记为dis[i][j]。这里涉及的的字符串匹配，官方正解给出的是**AC自动机**。然而我这个小蒟蒻不会呀，所以就用的是**KMP算法**，时间复杂度是$O(\sum\sum(len(i)+len(j)))$，把式子化一下会发现复杂度就是$O(n$**总串长**$)$，所以还是能过的。

如果有了dis[i][j]，那么应该不难想到一个$O(n^2m)$的DP式。我们设dp[t][i]表示总串中已经出现了t个字符串，且最后一个出现的串是i号串的最小代价，代码如下：

```cpp
for (int i=1;i<=n;i++)
        dp[1][i]=len[i];
for (int t=2;t<=m;t++)
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            dp[t][i]=min(dp[t][i],dp[t-1][j]+dis[j][i]);
            ```
最终的答案就是min{dp[m][i]}。

然而我们发现m很大，怎么办呢？

上面的那个式子是不是有点眼熟？有点像$Floyed$？

我们可以这样转化一下模型：把每个字符视为一个点，一次转移相当于从一个点走到另一个点，最终的答案就是问你总共走m次的最小距离。边界情况：第一个串的代价总是等于串长，所以我们新建一个0号点，另`dis[0][i]=len[i]，dis[i][0]=dis[0][0]=INF`，那么在经过m次转移之后，最终答案就是min{Ans[0][i]}。

这样，每一次转移就相当于跑一次$O(n^3)$的$Floyed$，m怎么办？矩阵加速优化！

至此这题应该就讲完了，具体代码实现应该还是不难的^-^

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define ll long long
const int _ = 205;
const ll INF = 1e18;
char s[_][100005];
int n,m,len[_],next[_][100005];
ll ans=INF;
struct matrix
{
    ll f[205][205];
    matrix operator * (matrix &b)
        {
            matrix c;
            memset(c.f,63,sizeof(c.f));
            for (int i=0;i<=n;i++)
                for (int j=0;j<=n;j++)
                    for (int k=0;k<=n;k++)
                        c.f[i][k]=min(c.f[i][k],f[i][j]+b.f[j][k]);//一遍Floyed,和矩阵乘法类似但有不同
            return c;
        }
}Tra,Ans;//状态矩阵Ans,转移矩阵Tra
int main()
{
    //freopen("hamsters.in","r",stdin);
    //freopen("hamsters.out","w",stdout);
    scanf("%d %d\n",&n,&m);
    for (int i=1;i<=n;i++)
        scanf("%s",s[i]+1),len[i]=strlen(s[i]+1);
    for (int t=1;t<=n;t++)
    {
        int j=0;
        for (int i=2;i<=len[t];i++)
        {
            while (j&&s[t][j+1]!=s[t][i]) j=next[t][j];//预处理next数组
            if (s[t][j+1]==s[t][i]) j++;
            next[t][i]=j;
        }
    }
    Tra.f[0][0]=INF;//边界情况
    for (int x=1;x<=n;x++)
    {
        Tra.f[0][x]=len[x];Tra.f[x][0]=INF;//边界情况
        for (int y=1;y<=n;y++)
        {
            int j=0;
            for (int i=2;i<=len[x];i++)
            {
                while (j&&s[y][j+1]!=s[x][i]) j=next[y][j];
                if (s[y][j+1]==s[x][i]) j++;
                if (i==len[x]) Tra.f[x][y]=len[y]-j;
            }
        }
    }
    for (int i=0;i<=n;i++)
        for (int j=0;j<=n;j++)
            Ans.f[i][j]=Tra.f[i][j];
    for (m--;m;m>>=1)//Ans的初始状态就已经有一次转移了，所以m--
    {
        if (m&1) Ans=Ans*Tra;
        Tra=Tra*Tra;
    }
    for (int i=1;i<=n;i++)
        ans=min(ans,Ans.f[0][i]);
    return printf("%lld\n",ans),0;
}
```

---

## 作者：cyffff (赞：10)

[$\text{Link}$](https://www.luogu.com.cn/problem/P3502)

$\text{Upd 2023.9.11}$：修改代码中的小错误。
## 题意
给出 $n$ 个互不包含的字符串 $a_{1,2,...,n}$，要求你求出一个最短的字符串 $S$，使得这 $n$ 个字符串在 $S$ 中总共至少出现 $m$ 次，问 $\min|S|$。

$\sum|a_i|\le10^5,1\le n\le 200,1\le m \le 10^9$.
## 思路
很是神仙！！

首先我们想到 $\text{dp}$。

设计状态 $dp_{i,j}$ 表示当前 $S$ 中字符串总出现次数为 $i$，其中最后出现的字符串为第 $j$ 个字符串。

我们先预处理 $dis_{i,j}$ 表示在第 $i$ 个字符串后最少添加多少个字符使得当前字符串中也含有 $j$。

则有边界条件 $dp_{1,j}=|a_j|$，转移方程 $dp_{i,j}=\min(dp_{i-1,k}+dis_{k,j})(1\le k\le n)$。

然后再想想怎么预处理 $dis_{i,j}$。

显然，我们将 $a_i,a_j$ 拉出来做 $\text{KMP}$，然后 $dis_{i,j}$ 就是 $|a_j|\,-$ 最后匹配到的位置。

答案为 $\min_{i=1}^ndp_{m,i}$。

这样就得到了一个 $O(n\sum|a_i|+n^2m)$ 的算法。

我们再看看这个转移方程，很容易想到和最短路相关的算法，然后我们~~啪的一下~~就知道了要矩阵优化了。

即经典广义矩阵乘法，若 $A\times B=C$，则 $C_{i,j}=\min(A_{i,k}+B_{k,j})$。

先设定 $dis_{0,i}=|a_i|,dis_{i,0}=\text{INF}$。

我们设定初始矩阵 $A$ 为：
$$\begin{bmatrix}
dis_{0,0}&dis_{0,1}&dis_{0,2}&...&dis_{0,n}\\
dis_{1,0}&dis_{1,1}&dis_{1,2}&...&dis_{1,n}\\
dis_{2,0}&dis_{2,1}&dis_{2,2}&...&dis_{2,n}\\
 &.\\
 & &.\\
 & & &.\\
dis_{n,0}&dis_{n,1}&dis_{n,2}&...&dis_{n,n}
\end{bmatrix}
$$

则目标矩阵 $C=A^{m}$，所求即为 $\min_{i=1}^n C_{0,i}$。这显然可以矩阵快速幂。

有一点小细节需要注意，即对于这种广义矩阵乘法我没有找到单位元，所以进行快速幂时我们需要计算 $C=A\times A^{m-1}$。

最终我们得到了一个 $O(n\sum|a_i|+n^3\log m)$ 的优秀算法！

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=200+10;
const ll INF=1e15;
char a[N][100010];
int nxt[N][100010],n,m,k,len[N];
ll dis[N][N];
struct Matrix{
	ll a[N][N];
	Matrix(){memset(a,0,sizeof(a));}
	inline ll* operator[](const int &x){
		return a[x];
	}
}bas,ans;
inline Matrix operator*(const Matrix &a,const Matrix &b){
	Matrix c;
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			ll s=INF;
			for(int k=0;k<=n;k++){
				s=min(s,a.a[i][k]+b.a[k][j]);
			}
			c[i][j]=s;
		}
	}
	return c;
}
int sum;
int main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		readstr(a[i]);
		sum+=len[i]=strlen(a[i]+1);
	}
	if(sum==n) return printf("%d",m),0;
	dis[0][0]=INF;
	for(int l=1;l<=n;l++){
		k=0;
		dis[0][l]=len[l];
		dis[l][0]=INF;
		for(int i=2;i<=len[l];i++){
			while(k&&a[l][i]!=a[l][k+1])k=nxt[l][k];
			if(a[l][i]==a[l][k+1]) k++;
			nxt[l][i]=k;
		}
	}
	for(int l1=1;l1<=n;l1++){
		for(int l2=1;l2<=n;l2++){
			k=0;
			dis[l1][l2]=len[l2];
			for(int i=2;i<=len[l1];i++){
				while(k&&a[l1][i]!=a[l2][k+1])k=nxt[l2][k];
				if(a[l1][i]==a[l2][k+1]) k++;
				if(i==len[l1]){
					dis[l1][l2]=len[l2]-k;
				}
			}
		}
	}
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			bas[i][j]=dis[i][j];
		}
	}
	ans=bas;
	m--;
	while(m){
		if(m&1) ans=ans*bas;
		bas=bas*bas;
		m>>=1;
	}
	ll sum=INF;
	for(int i=1;i<=n;i++){
		sum=min(sum,ans[0][i]);
	}
	write(sum);
	flush();
}
```
再见 qwq~

---

## 作者：是个汉子 (赞：8)

这个题的重点是转移方程的优化和匹配字符串的技巧，所以我们分开讲。

### Solution——字符串匹配

#### 1.KMP算法

因为是首尾拼接，所以拿KMP算法将nxt数组算出来。可以更简便的运算第 $j$ 种字符串接在第 $i$ 种结尾的最小增加量。

```c++
for(int k=1;k<=n;k++){
    int j=0;
    for(int i=2;i<=len[k];i++){
        while(j&&s[k][j+1]!=s[k][i]) j=nxt[k][j];
        if(s[k][j+1]==s[k][i]) j++;
        nxt[k][i]=j;
    }
}
```

#### 2.AC自动机

和KMP其实差不多（好像官方正解是这个），AC自动机就是算出fail数组而已，功能一样。

```c++
inline void insert(char *s,int id){
    int len=strlen(s+1),now=0;
    for(int i=1;i<=len;i++){
        int tmp=s[i]-'a';
        if(!ch[now][tmp]) ch[now][tmp]=++tot;
        now=ch[now][tmp];
    }
    ed[now]=id;pos[id]=now;
}

inline void get_fail()
{
	queue<int>q;q.push(0);
	while(q.size())
	{
        int x=q.front();q.pop();
        for(int i=0;i<26;i++){
            int y=ch[x][i];
            if(!y) continue;
            int k=fail[x];
            while(k&&(!ch[k][i])) k=fail[k];
            fail[y]=x?ch[k][i]:0;
            q.push(y);
        }
	}
}
```

#### 3.Hash

先拿的单Hash试了试 ，发现如果模数不太行的话，是会WA好几个点的。

~~也可能是我脸黑，一发入魂~~

```c++
inline bool check(int x,int y,int l){
	//第三个(ll) 不写会锅4个点 亲测
    return (ll)(Hash[x][len[x]-1]-Hash[x][len[x]-l-1]+mod)%mod
         ==(ll)((ll)Hash[y][l-1]*pow_26[len[x]-l]%mod);
}

for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        int l=Min(len[i],len[j]);
        for(int k(i==j?l-1:l);k;--k)
            if(check(i,j,k)){
                f[0][i][j]=len[j]-k;
                break;
            }
        if(f[0][i][j]>10000000) f[0][i][j]=len[j];
    }
//配合下面的倍增Floyd观看
```

我最后用的 mod=19280817

#### 4.双Hash

和单Hash不一样，对于双Hash来讲，只要你不zz，脸也不算太黑，出题人没有卡你双Hash，应该是没问题的。

但是，很不幸

这个题的内存是 $125MB$ ，双Hash是会MLE的 〒▽〒

```c++
inline int get_Hash(const int x,const int s,const int e){
    if(s>e) return 0;
    int t=(Hash[x][e+1]-1ll*Hash[x][s]*p26_1[e-s+1]%MOD)+MOD;
    return t>=MOD?t-MOD:t;
}

inline int get_HASH(const int x,const int s,const int e){
    if(s>e) return 0;
    int t=(HASH[x][e+1]-1ll*HASH[x][s]*p26_2[e-s+1]%mod)+mod;
    return t>=mod?t-mod:t;
}


inline int work(const int x,const int y){
    int m=min(len[x],len[y]);
    if(x==y) --m;
    for(int i=m;~i;--i){
        if((get_Hash(x,len[x]-i,len[x]-1)==get_Hash(y,0,i-1))&&(get_HASH(x,len[x]-i,len[x]-1)==get_HASH(y,0,i-1)))
            return len[y]-i;
    }
    return 0;
}
//借用大佬的部分代码

for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
    	dis[i][j]=work(i,j);
//这个dis[i][j]对应的是矩阵优化中的dis
```

### Solution——转移方程优化

#### 1.倍增Floyd

我们首先转化题意：

有 $n$ 个点，两个点 $i,j$ 之间的权值为将第 $j$ 种字符串接在第 $i$ 种结尾的最小增加量（注意此处 $i$ 可以和 $j$ 相等）。求一条经过 $m$ 个点的最短路径，起点和终点自己选择。

暴力求法很好想，因为 $n\leq 200$ ，所以考虑Floyd。设 $f_{k,i,j}$ 为 $i$ 到 $j$ 经过 $k$ 个点的最短路径，然后一层一层枚举，直到 $m$ ，就求出来了。

时间复杂度为 $O(n^3 m)$ 

~~这不直接满分？~~

所以考虑怎么优化——这时**倍增Floyd**出场了。

现在需要干啥呢？在 $f_{k,i,j}$ 的基础上将意义改为从 $i$ 到 $j$ 经过 $2^k$ 个点的最短路，这样转移的复杂度就从 $O(m)$ 变成了 $O(\log m)$ 。

```c++
for(int t=1;t<=30;t++)
    for(int k=1;k<=n;k++)
        for(int j=1;j<=n;j++)
            for(int i=1;i<=n;i++)
                f[t][i][j]=Min(f[t-1][i][k]+f[t-1][k][j],f[t][i][j]);
for(int i=0;i<=30;i++)
    if(m&(1<<i)){
        for(int j=1;j<=n;j++){
            tmp[j]=0x3f3f3f3f3f3f3f3fll;
            for(int k=1;k<=n;k++)
                tmp[j]=tmp[j]<dis[k]+f[i][k][j]?tmp[j]:dis[k]+f[i][k][j];
        }
        for(int j=1;j<=n;j++)
            dis[j]=tmp[j];
    }
```

现在时间复杂度为 $O(n^3\log m)$ 。

#### 2.矩阵优化

先考虑不加优化时的朴素做法，即暴力。

设 $dp_{i,j}$ 表示现在串里有 $i$ 个字符串，并以第 $j$ 种字符串结尾的最短长度， $dis_{i,j}$ 表示将第 $j$ 种字符串接在第 $i$ 种结尾的最小增加量。

那么转移方程也很好得到： $dp_{i,j}=\min\{dp_{i-1,k}+dis_{k,j}\}$ ，其中初始状态应为 $dp_{1,i}=len_i$ 

我们看一下这部分的代码：

```c++
for(int i=2;i=m;i++)
    for(int j=1;j<=n;j++)
        for(int k=1;k<=n;k++)
            dp[i][j]=min(dp[i][j],dp[i-1][k]+dis[k][j]);
```

等等，这一坨东西是不是似曾相识。

是不是在矩阵乘法中见过一个类似的，这启发我们用矩阵去优化这个转移。

```c++
for(int x=1;x<=n;x++){
    I.a[0][x]=len[x];I.a[x][0]=INF;
    for(int y=1;y<=n;y++){
        int j=0;
        for(inti i=2;i<=len[x];i++){
            whle(j&&s[y][j+1]!=s[x][i]) j=nxt[y][j];
            if(s[y][j+1]==s[x][i]) j++;
            if(i==len[x]) I.a[x][y]=len[y]-j;
        }
    }
}

for(m--;m;m>>=1){
    if(m&1) Ans=Ans*I;
    I=I*I;
}
//搭配上面的KMP观看
```

时间复杂度也是 $O(n^3\log m)$ 。



注意：我将上面的几乎每个组合都试了一遍，除了双Hash在不管无论开不开O2的情况下都是第一个点MLE，别的方法在不开O2的情况是第一个点TLE。（咱也不知道为什么时间复杂度对了还会T，这也卡常？）

### 代码

刚刚每个都放了部分代码，这里就~~咕咕咕~~

还是放一个倍增Floyd的完整代码吧

~(￣▽￣)~*

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=210,L=100010,mod=19260817;
char s[N][L];
ll f[35][N][N],dis[N],tmp[N],n,m,ans;
int len[N],Hash[N][L],pow_26[L];

ll Min(ll x,ll y){
    return x<y?x:y;
}

inline bool check(int x,int y,int l){
    //第三个(ll) 不写会锅4个点 亲测
    return (ll)(Hash[x][len[x]-1]-Hash[x][len[x]-l-1]+mod)%mod==(ll)((ll)Hash[y][l-1]*pow_26[len[x]-l]%mod);
}

inline void init(){
    pow_26[0]=1;
    for(int i=1;i<=100000;i++)
        pow_26[i]=pow_26[i-1]*26%mod;
    memset(f,0x3f,sizeof(f));
}

int main(){
    init();
    scanf("%lld%lld",&n,&m); m--;
    for(int i=1;i<=n;i++){
        scanf("%s",s[i]);
        len[i]=strlen(s[i]);
        dis[i]=len[i];
        for(int j=0;j<len[i];j++)
            if(j) Hash[i][j]=(Hash[i][j-1]+pow_26[j]*(s[i][j]-'a'+1))%mod;
            else Hash[i][j]=s[i][j]-'a'+1;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            int l=Min(len[i],len[j]);
            for(int k(i==j?l-1:l);k;--k)
                if(check(i,j,k)){
                    f[0][i][j]=len[j]-k;
                    break;
                }
            if(f[0][i][j]>10000000) f[0][i][j]=len[j];
        }
    for(int t=1;t<=30;t++)
        for(int k=1;k<=n;k++)
            for(int j=1;j<=n;j++)
                for(int i=1;i<=n;i++)
                    f[t][i][j]=Min(f[t-1][i][k]+f[t-1][k][j],f[t][i][j]);
    for(int i=0;i<=30;i++)
        if(m&(1<<i)){
            for(int j=1;j<=n;j++){
                tmp[j]=0x3f3f3f3f3f3f3f3fll;
                for(int k=1;k<=n;k++)
                    tmp[j]=tmp[j]<dis[k]+f[i][k][j]?tmp[j]:dis[k]+f[i][k][j];
            }
            for(int j=1;j<=n;j++)
                dis[j]=tmp[j];
        }
    ans=0x3f3f3f3f3f3f3f3fll;
    for(int i=1;i<=n;i++)
        ans=Min(ans,dis[i]);
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：梧桐灯 (赞：3)

我写的hash+矩阵加速Floyd。

##### ~~前方高能预警~~

盘点一下这一题的几个坑点：

- 十年OI一场空，不开longlong……（其实只是我太菜忘了QAQ）

- 不要用string类！！不然不开O2 T掉第一个点（虽然开只要266ms）

- 对于相同的串不能算两次，单也要考虑一下：

比如aba相接两次就是ababa对答案的贡献为5而不是6（我一开始以为同一个串对答案贡献必定是原长而Wa了一个点）

- 为了保险，我用了双hash值（但不用似乎也可以）

- 据说m可能为0，但亲测不会（如果T了并不是这个锅）

接下来一些细节在代码中呈现

```cpp
#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;
const int N = 203, M = 100003, MOD = 299999973, mod = 399999977; //双hash值保险防冲突
string a[N];
int n, m;
int c[N][N], l[N];
int Hash[N][M];
int HASH[N][M];

int p261[M], p262[M];

inline int Get (const int x, const int s, const int e) {
	if (s > e) return 0;
    int t = (Hash[x][e + 1] - 1ll * Hash[x][s] * p261[e - s + 1] % MOD) + MOD;
    return t >= MOD ? t - MOD : t;
} //算hash值

inline int GET (const int x, const int s, const int e) {
	if (s > e) return 0;
    int t = (HASH[x][e + 1] - 1ll * HASH[x][s] * p262[e - s + 1] % mod) + mod;
    return t >= mod ? t - mod : t;
}


inline int work (const int x, const int y) {
    int i, m = min (l[x], l[y]);
	if (x == y) --m;
    for (i = m; ~i; --i) {
		if (Get (x, l[x] - i, l[x] - 1) == Get (y, 0, i - 1)) {
			if (GET (x, l[x] - i, l[x] - 1) == GET (y, 0, i - 1)) return l[y] - i;
		}
	}
	return 0;
}//判断如果串x后接y的长度为len[y] - 最长公共x前缀与y后缀

struct stu {
    ll x[N][N];
};

inline stu mult (const stu& p, const stu& q) {
    stu r; memset (r.x, 0x3f, sizeof (r.x));
    register int i, j, k;
    for (k = 0; k <= n; ++k) {
        for (i = 0; i <= n; ++i) {
            for (j = 0; j <= n; ++j) 
				r.x[i][j] = min (r.x[i][j], p.x[i][k] + q.x[k][j]);
        }
    }
    return r;
}

/*
建立一个超级原点为0到每个串权值为串长
然后用Floyed进行
记得开longlong ！！
*/

inline ll ksm (int x) {
    stu s, p;
    int i, j; for (i = 0; i <= n; ++i) {
        for (j = 0; j <= n; ++j) p.x[i][j] = s.x[i][j] = c[i][j];
    }
	for (i = 0; i <= n; ++i) p.x[i][0] = s.x[i][0] = 0x3f3f3f3f3f3f3f3fll;
	while (x) {
        if (x & 1) s = mult (s, p);
        p = mult (p, p);
        x >>= 1;
    }
    ll ans = 1ll << 60;
    for (i = 1; i <= n; ++i) if (s.x[0][i]) ans = min (ans, s.x[0][i]);
    return ans;
}

int main () {
    cin >> n >> m;
	if (!m) {
		puts ("0");
		return 0;
	}
    int i, j; for (i = 1; i <= n; ++i) {
        cin >> a[i];
        l[i] = a[i].size ();
        c[0][i] = l[i];
    }
    p261[0] = p262[0] = 1;
    for (i = 1; i <= 100000; ++i) {
		p261[i] = 1ll * p261[i - 1] * 26 % MOD;
		p262[i] = 1ll * p262[i - 1] * 26 % mod;
	}
    for (i = 1; i <= n; ++i) {
		Hash[i][1] = a[i][0] - 'a';
		HASH[i][1] = a[i][0] - 'a';
        for (j = 1; j < l[i]; ++j) {
            Hash[i][j + 1] = (1ll * Hash[i][j] * 26 + (a[i][j] - 'a')) % MOD;
			HASH[i][j + 1] = (1ll * HASH[i][j] * 26 + (a[i][j] - 'a')) % mod;
        }
    }
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j)
            c[i][j] = work (i, j);
    }
    cout << ksm (m - 1) << '\n';
    return 0;
}

```


---

## 作者：nofind (赞：2)

题意：https://www.luogu.org/problem/P3502

没有AC自动机的题解吗~~ 

思路跟其他题解一样,不过将KMP换成了AC自动机

首先n个串互不包含,因此最终答案一定是m个串前后拼接而成

因此考虑f[i][j]->拼成了i个串,最后一个串为第j个串的最小长度

可以预处理dis[i][j]表示在i后面拼接几个字符能出现j:

如 i:aab j:ba dis[i][j]=1(aab+'a')

dis数组显然可以用AC自动机暴力跳fail求(不知道为什么不开02会T第一个点,希望dalao们看看)

f[i][j]=min(f[i-1][k]+dis[k][j])

但是i[0,m],m<=1e9,显然会T

考虑上面的DP式子其实是一个取min的矩乘,因此用矩乘优化

复杂度:O(N^3logM)

**千万注意****千万注意****千万注意**：单位矩阵为全inf矩阵,不要像傻乎乎的nofind弄成对角线全为1的矩阵

code:
```
#include<bits/stdc++.h>
using namespace std;
#define re register
typedef long long ll;
const int maxn=210;
const int maxl=100010;
ll n,m,tot,ans=1LL<<60;
int end[maxl],pos[maxl],len[maxn],fail[maxl],dep[maxl];
int ac[maxl][26];
char s[maxl];
struct Mat
{
	ll a[maxn][maxn];
	ll* operator[](int i){return a[i];}
	Mat(){memset(a,0x3f,sizeof(a));}
	inline void idx(){for(re int i=1;i<=n;i++)a[i][i]=1;}
}A;
Mat operator*(Mat &x,Mat &y)
{
	Mat res;
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++)
			for(re int k=1;k<=n;k++)
				res[i][j]=min(res[i][j],x[i][k]+y[k][j]);
	return res;
}
Mat operator ^(Mat &a,ll k)
{
    Mat res;
    for(re int i=1;i<=n;i++)res[i][i]=0;
    while(k)
    {
        if(k&1)res=res*a;
        a=a*a;k>>=1;
    }
    return res;
}
inline void insert(char* s,int id)
{
	int len=strlen(s+1),now=0;
	for(re int i=1;i<=len;i++)
	{
		int c=s[i]-'a';
		if(!ac[now][c])ac[now][c]=++tot;
		now=ac[now][c];
	}
	end[now]=id;pos[id]=now;
}
inline void getfail()
{
	queue<int>q;q.push(0);
	while(!q.empty())
	{
		int x=q.front();q.pop();
		for(re int i=0;i<26;i++)
		{
			int y=ac[x][i];
			if(!y)continue;
			int k=fail[x];
			while(k&&(!ac[k][i]))k=fail[k];
			fail[y]=x?ac[k][i]:0;
			q.push(y);
		}
	}
}
inline void build()
{
	for(re int i=1;i<=n;i++)
		for(re int j=pos[i];fail[j];j=fail[j])
		{
			dep[fail[j]]=0;
			queue<int>q;q.push(fail[j]);
			while(!q.empty())
			{
				int x=q.front();q.pop();
				for(int k=0;k<26;k++)
				{
					int y=ac[x][k];
					if(!y)continue;
					A[i][end[y]]=dep[y]=dep[x]+1;q.push(y);
				}
			}	
		}		
}
int main()
{
	scanf("%lld%lld",&n,&m);
	if(!m){puts("0");return 0;}
	for(re int i=1;i<=n;i++)
	{
		scanf("%s",s+1);len[i]=strlen(s+1);
		insert(s,i);
		for(re int j=1;j<=n;j++)A[j][i]=len[i];
	}
	getfail();build();
	A=A^(m-1);
	/*for(int i=1;i<=n;i++,puts(""))
		for(int j=1;j<=n;j++)
			printf("%lld ",A[i][j]);
	puts("");*/
	for(re int i=1;i<=n;i++)
		for(re int j=1;j<=n;j++)
			ans=min(ans,len[i]+A[i][j]);
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Bosun (赞：2)

这道题目很妙，当时只有@wlzhouzhuan 巨佬一个做出来。

现在想要是那个时候A这道题该有多爽啊（~~好吧2010年我才3岁。。。~~）

首先看到题面，我第一想法是dp不可做，为何？我想：有可能不是所有的串首尾相接呀，可能一个串含在另外两个合并起来的大串里呀！。

其实不是的，比如说aaab abc bcc
答案是6

既然都是首尾相接，那就好办了，我们用string_hash求出任意两个字符串要连接起来的最少长度(记为dis[i][j])，用这个跑dp就行了

dp式子为：f[i][j]：串中已经有了i个字符串，最后一个为j的最小长度。
f[i][j]=min（f[i][j],f[i-1][k]+dis[k][j]）；

到这里就有60分了（~~够了够了~~），可是与AK的bmh201708巨佬差距还是不小。

所以我们要进行优化，算法的瓶颈在m上。

但是您有没有发现，这个式子相当于每次**只转移一条边**的floyd???

没错哦，先改写成floyd的式子：f[i][j]=min(f[i][j],f[i][k]+f[k][j])

机房里大多数人放弃在这里，她们想不到了。其实这就相当于把字符串看成点，只经过k条边的最短路，这有个东西叫倍增floyd，请读者自行百度

然后还要连一个超级源，不然不知到从哪个串开始，枚举浪费时间。对于超级源来说，出边连的是对应点的字符串长度，入边连inf（相当于不能走，为何不能走？因为走一步就相当于浪费了一条边（走到了空点上），可是必须得走满呀！！！）

还有一个细节：m在矩乘时要减一，因为快速幂res的“1”不知道（是邻接矩阵吗？不是，应为邻接矩阵自己对自己连边是不花费的，可是这里一个点重复两次要花费呀！！！所以“1”就变成底数，然后m--，保证是m次方）

详细实现见代码：
```c
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;//自然溢出法
const int N=1005;//不给数据范围。。。
const ll d=1003;
const ll inf=1e15;//不要太小，其实1e15就够了
int n; 
ll m;
char s[N][10001];//不给数据范围。。。
ll dis[N][N];
ull po[10001];
ull hasa[10001],hasb[10001];
struct ju{
	ll a[N][N];
};
ju mul(ju a,ju b){//矩阵乘法，见倍增floyd
	ju x;
	int i,j,k;
	for(i=0;i<=n;i++)for(j=0;j<=n;j++)x.a[i][j]=inf;
	for(k=0;k<=n;k++){//做floyd
		for(i=0;i<=n;i++){
			for(j=0;j<=n;j++){
				x.a[i][j]=min(x.a[i][j],a.a[i][k]+b.a[k][j]);
			}
		}	
	}
	return x;
}
int len[N];
ull chsuc(int x,int p){//后缀哈希值
	return hasa[len[x]]-hasa[p-1]*po[len[x]-p+1]; 
}
ll did(int x,int y,int same){//算dis
	int i,j;
	memset(hasa,0,sizeof(hasa));
	memset(hasb,0,sizeof(hasb));
	for(i=1;i<=len[x];i++)hasa[i]=hasa[i-1]*d+s[x][i];
	for(i=1;i<=len[y];i++)hasb[i]=hasb[i-1]*d+s[y][i];
	for(i=len[y]-same;i>=1;i--){//注意，当两串相同时不可以一个当两个用，最多匹配到倒数第二位
		if(len[x]<i)continue;//i枚举的是b的前缀与a的后缀的重复字符数，显然不能超过len[x]
		ull h1=hasb[i],h2=chsuc(x,len[x]-i+1); 
		if(h1==h2){
			return len[y]-i;
		}
	}
	return len[y];
} 
int main(){
	cin>>n>>m;
	int i,j;
	for(i=1;i<=n;i++)scanf("%s",s[i]+1),len[i]=strlen(s[i]+1);
	po[0]=1;
	for(i=1;i<=10000;i++)po[i]=po[i-1]*d;//奇怪吗？多写string_hash
	for(i=0;i<=n;i++){//超级源为0点
		for(j=0;j<=n;j++){
			if(j==0)dis[i][j]=inf;
			else if(i==0)dis[i][j]=len[j];//build a super start 
			else dis[i][j]=did(i,j,i==j);
		}
	}
	ju hhh,res;
	for(i=0;i<=n;i++)for(j=0;j<=n;j++)hhh.a[i][j]=dis[i][j];			
	res=hhh;
    m--;//m可以为0哦！
	if(m==-1){
		puts("0");
		return 0;
	}
	while(m){//快速幂
		if(m&1)res=mul(res,hhh);
		hhh=mul(hhh,hhh);
		m>>=1;
	}
	ll ans=inf;
	for(i=1;i<=n;i++)ans=min(ans,res.a[0][i]);
	cout<<ans<<endl;
	return 0;
}
```



---

## 作者：Engulf (赞：1)

考虑 dp，设 $f_{i, j}$ 表示拼到 $i$ 个名字，最后一个名字的编号为 $j$ 的方案数，转移显然：

$$f_{i, j} = \min(f_{i, j}, f_{i - 1, k} + dis_{k, j})$$

$$f_{1, i} = |s_i|$$

$s_i$ 表示第 $i$ 个名字。

此处的 $dis_{i, j}$ 表示把第 $j$ 个字符串接在第 $i$ 个字符串后需要添加的字符个数。

考虑怎么求 $dis$。设我们现在要计算字符串 $t$ 接在字符串 $s$ 后面需要添加的字符个数，显然 $s$ 和 $t$ 可以有一段最长的相同的部分，即我们要得到最大的 $k$ 使得 $s$ 的后 $k$ 个字符和 $t$ 的前 $k$ 个字符相等。这 $k$ 个字符显然可以共用，最终的答案就是 $|t| - k$。我们记 $p = t + s$ 即 $t$ 和 $s$ 相接。易发现 $k$ 就是 $p$ 的最长 border 长度，这个可以用 kmp 求出来。

有一个问题，如果按照上面的方法求两个一样的字符串接在一起的话，求出的 border 就是原字符串的长度，算出来的答案仍是原字符串的长度，所以这里就不能减去最长的 border，得减去次长的 border。

记 $\sum|s_i| = S$，现在我们可以大概 $\mathcal{O}(nS)$ 的时间求出 $dis$。

给个证明：一次 kmp 的时间复杂度是 $\mathcal{O}(|s|)$ 的，$s$ 是跑 kmp 的那个字符串，那么处理 $dis$ 的时间复杂度为

$$\sum\limits_{i = 1}^n\sum\limits_{j = 1}^n |s_i| + |s_j|$$

$|s_i|$ 与 $j$ 无关，提出来

$$\sum\limits_{i = 1}^n \left( n|s_i| + \sum\limits_{j = 1}^n|s_j|\right)$$

后面那个正好是 $S$

$$\sum\limits_{i=1}^nn|s_i| + S$$

拆成两部分

$$n\sum\limits_{i=1}^n|s_i| + nS$$

左边那个还是 $S$，所以最终结果就是

$$2nS$$

即

$$\mathcal{O}(nS)$$

回到 dp，现在的 dp 是 $\mathcal{O}(n^2m)$ 的，看到 dp 的式子，发现可以矩阵加速。

$$\begin{bmatrix}
f_{i, 1}  & f_{i, 2} & \cdots  & f_{i, n}
\end{bmatrix} \times \begin{bmatrix}
dis_{1, 1}  & dis_{1, 2} & \cdots  & dis_{1, n} \\
dis_{2, 1} & \ddots \\
\cdots \\
dis_{n, 1} & \cdots &  & dis_{n, n}
\end{bmatrix} = \begin{bmatrix}
f_{i+1, 1}  & f_{i+1, 2} & \cdots  & f_{i+1, n}
\end{bmatrix}$$

注意这里的 $\times$ 是广义的，这是广义矩阵乘法。

初始矩阵为 $f$，则最终矩阵为 $f \times A^{m-1}$，答案为 $\min\limits_{i=1}^n f_i$。

时间复杂度 $\mathcal{O}(n^3\log m)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 205, LEN = 1e5 + 5;

int n, m;

char str[N][LEN];

ll dis[N][N];

int ne[LEN << 1];

int getdis(char *s, char *t) {
    int n = strlen(s + 1), m = strlen(t + 1);
    auto getch = [=](int i) {return i <= m ? t[i] : s[i - m];};
    for (int i = 2, j = 0; i <= n + m; i++) {
        while (j && getch(j + 1) != getch(i)) j = ne[j];
        if (getch(j + 1) == getch(i)) j++;
        ne[i] = j;
    }
    return m - (ne[n + m] != m ? ne[n + m] : ne[ne[n + m]]);
}

ll f[N][N];

void mul(ll c[][N], ll a[][N], ll b[][N]) {
    static ll t[N][N];
    memset(t, 0x3f, sizeof t);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
                t[i][j] = min(t[i][j], a[i][k] + b[k][j]);
    memcpy(c, t, sizeof t);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> str[i] + 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            dis[i][j] = getdis(str[i], str[j]);
    for (int i = 1; i <= n; i++) f[1][i] = strlen(str[i] + 1);
    m--;
    while (m) {
        if (m & 1) mul(f, f, dis);
        mul(dis, dis, dis);
        m >>= 1;
    }
    ll ans = 1e18;
    for (int i = 1; i <= n; i++) ans = min(ans, f[1][i]);
    cout << ans << "\n";
    return 0;
}
```

---

## 作者：5k_sync_closer (赞：1)

设 $f_{i,j}$ 表示填了 $i$ 个串，最后一个串为 $j$ 的最短长度，

考虑往后接一个串，则有 $f_{i+1,j}=\min\limits_{k=1}^n\{f_{i,k}+|s_j|-B(j,k)\}$，

其中 $B(j,k)$ 表示既是 $s_j$ 的前缀，又是 $s_k$ 的后缀的串的最大长度，即 $s_j,s_k$ 重叠的部分，

可以 KMP 求出 $B$ 的所有点值。

发现转移是广义矩乘的形式，于是矩阵加速即可。

```cpp
#include <string>
#include <iostream>
#include <cstring>
#define int long long
using namespace std;
int n, m, Q = 1e18, k[1000050];
string a, s[250];
struct S
{
    int a[250][250];
    S() { memset(a, 0x3f, sizeof a); }
    S operator*(S b)
    {
        S c;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
            {
                int q = 1e18;
                for (int k = 0; k < n; ++k)
                    q = min(q, a[i][k] + b.a[k][j]);
                c.a[i][j] = q;
            }
        return c;
    }
} b, q;
signed main()
{
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> s[i], q.a[0][i] = s[i].length();
    for (int x = 0; x < n; ++x)
        for (int y = 0, z; y < n; ++y)
        {
            a = ' ' + s[x] + s[y];
            for (int i = 2, j = 0; i < a.length(); ++i)
            {
                while (j && a[i] != a[j + 1])
                    j = k[j];
                k[i] = j += a[i] == a[j + 1];
            }
            for (z = k[a.length() - 1]; z >= s[x].length(); z = k[z])
                ;
            b.a[y][x] = s[x].length() - z;
            for (int i = 1; i < a.length(); ++i)
                k[i] = 0;
        }
    for (--m; m; m >>= 1, b = b * b)
        if (m & 1)
            q = q * b;
    for (int i = 0; i < n; ++i)
        Q = min(Q, q.a[0][i]);
    cout << Q;
    return 0;
}
```


---

## 作者：wmy_goes_to_thu (赞：1)

水题，感觉评紫有点过分。

和是 $m$ 次，那么我们考虑把一个字符串接到大字符串的后边。

例如，我现在拼成了 abcdefgabc，然后想加入 abcdefg（字符串 $s$），那么就可以变成 abcdefgabcdefg，加入的长度是 $|s|-C$，其中 $C$ 是大字符串末尾和 $s$ 的前部最大交集。

可能还是说的有些抽象，如果设大字符串为 $t$ 就有 $C=\max\limits_{k \in [0,min(|s|,|t|))}k(t_{|t|-k+1\sim|t|}=s_{1 \sim k})$。

这个东西 KMP 可以做，但是 KMP 毕竟需要脑子，于是果断字符串 hash。

因为没有包含关系，所以大字符串可以变成这个大字符串最后接入的字符串。这样就有了一个矩阵 $f_{i,j}$。最开始大字符串是空，所以还要引入 $f_{0,i}$。

发现问题可以转化成从 $0$ 到任意节点恰好经过 $m$ 条边的最短路！那这玩意儿可以用矩阵乘法去做，如果不会去看魔法值（NOI Online 3 提高组）的题解。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
unsigned long long mo=111339248186143ull,bs[100005];
char s[205][100005];
vector<unsigned long long>g[205];
int l[205];
long long f[31][205][205],ff[205][205],f3[205][205];
int main()
{
	bs[0]=1;
	for(int i=1;i<=100000;i++)bs[i]=bs[i-1]*mo;
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)scanf("%s",s[i]+1),l[i]=strlen(s[i]+1);
	for(int i=1;i<=n;i++)
	{
		g[i].push_back(0);
		for(int j=1;j<=l[i];j++)
		{
			unsigned long long mm=g[i][j-1];
			g[i].push_back(mm*mo+s[i][j]);
		}
	}
	memset(f,63,sizeof(f));
	for(int i=1;i<=n;i++)f[0][0][i]=l[i];
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
	{
		int wz=0;
		for(int k=1;k<min(l[i],l[j]);k++)
			if(g[i][l[i]]-g[i][l[i]-k]*bs[k]==g[j][k])wz=k;
		f[0][i][j]=l[j]-wz;
	}
	for(int i=1;i<=30;i++)for(int j=0;j<=n;j++)for(int k=1;k<=n;k++)
		for(int t=1;t<=n;t++)f[i][j][k]=min(f[i][j][k],f[i-1][j][t]+f[i-1][t][k]);
	int nnn=0;
	for(int i=30;i>=0;i--)if(m>=(1<<i))
	{
		m-=1<<i;
		if(!nnn)
		{
			for(int j=0;j<=n;j++)for(int k=1;k<=n;k++)ff[j][k]=f[i][j][k];
			nnn=1;
		}else
		{
			memset(f3,63,sizeof(f3));
			for(int j=0;j<=n;j++)for(int k=1;k<=n;k++)for(int t=1;t<=n;t++)
				f3[j][k]=min(f3[j][k],f[i][j][t]+ff[t][k]);
			for(int j=0;j<=n;j++)for(int k=1;k<=n;k++)ff[j][k]=f3[j][k];
		}
	}
	long long ans=LLONG_MAX;
	for(int i=1;i<=n;i++)ans=min(ans,ff[0][i]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Fzrcy (赞：0)

设 $T_{i,j}$ 表示至少要在 $s_i$ 后添加 $T_{i,j}$ 个字符才能使 $s_j$ 是 $s_i$ 的后缀，$f_{i,j}$ 表示 $n$ 个字符串共出现 $i$ 次且最后一个字符串是 $s_j$ 的字符串的最短长度，显然 $f_{i,j}=\min\{f_{i-1,k}+T_{k,j}\}$，这个式子可以用矩阵乘法优化。

对于预处理 $T_{i,j}$，直接字符串哈希、暴力查询即可，预处理的复杂度为 $O(n\sum|s_i|)$。

总的复杂度为 $O(n\sum|s_i|+n^3\log m)$。

```cpp
// qwq
#include <bits/stdc++.h>
using namespace std;
namespace Work{
    typedef unsigned long long ull;
    constexpr int N=203,M=1.3e5+2;
    constexpr ull Base=233;
    char s[M]; ull P[M],H[M];
    int len[M],n,m,r[M],now;
    ull Hash(int x,int y){
        return H[y]-H[x-1]*P[y-x+1];
    }
    int get(int x,int y){
        int xl=r[x],xr=r[x]+len[x]-1;
        int yl=r[y],yr=r[y]+len[y]-1;
        int mx=0,mn=min(len[x],len[y]);
        for(int i=1;i<mn;i++)
            if(Hash(xr-i+1,xr)==Hash(yl,yl+i-1))
                mx=i;
        return len[y]-mx;
    }
    typedef long long ll;
    struct mat{
        ll a[N][N];mat(){memset(a,0x3f,sizeof a);}
        mat operator * (mat b){
            mat ret;
            for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) for(int k=1;k<=n;k++)
                ret.a[i][j]=min(ret.a[i][j],a[i][k]+b.a[k][j]);
            return ret;
        }
    };
    mat ksm(mat x,ll y){
        mat r;for(int i=1;i<=n;i++)r.a[i][i]=0;
        for(;y;y>>=1,x=x*x)if(y&1)r=r*x;return r;
    }
    int Main(){
        scanf("%d %d",&n,&m),P[0]=1;
        for(int i=1;i<=n;i++){
            r[i]=r[i-1]+len[i-1]+1;
            scanf(" %s",s+r[i]);
            len[i]=strlen(s+r[i]);
            now=r[i]+len[i];
        }
        for(int i=1;i<=now;i++)
            P[i]=P[i-1]*Base,
            H[i]=H[i-1]*Base+s[i];
        mat S;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                S.a[i][j]=get(i,j);
        mat rr;
        for(int i=1;i<=n;i++)
            rr.a[1][i]=len[i];
        S=ksm(S,m-1);
        rr=rr*S;
        ll ans=1e18;
        for(int i=1;i<=n;i++)
            ans=min(ans,rr.a[1][i]);
        cout<<ans<<'\n';
        return 0;
    }
}
int main(){
    Work::Main();
    return 0;
}
```



---

## 作者：InoueTakina (赞：0)

字符串互不包含的性质尤为重要。这意味着最终字符串的每个字符最多被贡献两次，并且贡献形式是一个串的后缀和另一个串的前缀共用。

这无疑是很好的性质，这意味着我们只关心 $S$ 的末尾究竟是哪个串，所需记录的信息大大减少。

我们不妨先预处理出任意两个串按上述贡献形式最大能共用的字符数量，可以用 kmp 处理。



不妨记 $g(i,j)$ 为串 $i$ 的后缀和串 $j$ 的前缀所能共用的最大字符数量，$f(i,j)$ 为当前以串 $i$ 结尾，所有串总共出现了 $j$ 次的最小长度，转移：

$$f(i,j)=\min_k\{f(k,j-1)+g(k,i)\}$$

注意到转移方程是关于第二维的线性递推，广义矩阵乘法加速递推即可。


---

