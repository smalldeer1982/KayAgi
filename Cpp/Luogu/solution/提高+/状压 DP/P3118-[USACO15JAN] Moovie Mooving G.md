# [USACO15JAN] Moovie Mooving G

## 题目描述

Bessie 正在外看电影。调皮的她想在 $L$（$1 \leq L \leq 100,000,000$）分钟内连续观看电影来躲避农夫 John。她有 $N$（$1 \leq N \leq 20$）部电影可选，每部电影有特定时长和多个放映场次。Bessie 可以在电影放映期间的任意时刻入场或离场，但不能重复观看同一部电影，也不能切换到同一部电影时间重叠的场次。

请判断 Bessie 是否能从时间 $0$ 到时间 $L$ 连续观看电影。若可行，求出达成目标所需观看的最小电影数量（过多电影会让 Bessie 混淆剧情）。

## 说明/提示

Bessie 可以观看第四部电影的首场（时间 $0$ 至 $20$），接着观看第一部电影的首场（时间 $20$ 至 $65$），最后观看第二部电影的末场（时间 $65$ 至 $100$）。

## 样例 #1

### 输入

```
4 100 
50 3 15 30 55 
40 2 0 65 
30 2 20 90 
20 1 0 
```

### 输出

```
3 
```

# 题解

## 作者：WZKQWQ (赞：24)

#### 这篇题解受大佬NewErAd的启发而出

~~其实我就是让大家更好的理解它的思路~~

看了记录是第2快的（因为我懒得用快读，第一用了快读快输）

和第一只差0.05s

------------
珂爱的分割线
------------
介绍思想：

dp[i]表示集合i能最多看几分钟电影，

转移呼之欲出

选一个不在集合的点j把它加入

当j最小的电影开始时间小于dp[i]时

dp[i |(1 << j)] = max(dp[i |(1 << j)],a[j][#] + d[j]);

（#是最好的电影开始时间，后面会求）

不然考虑继承状态:dp[i |(1 << j)] = dp[i];

当找到一个dp[i] > L时:ans = min(ans,cnt1(i));

```cpp
int cnt1(int x)
{
    int num = 0;
    while (x)
    {
        if (x & 1)
            num++;
        x = x >> 1;
    }
    return num;
}
```
这个数1函数不用我说了吧。

现在我们来看前面的#怎么求

upper_bound以a[j] + 1, a[j] + a[j][0] + 1, f[i]) - a[j];

这个函数是求以a[j] + 1开头，以a[j] + a[j][0] + 1结尾

(这里我用a[j][0]保存一部电影有几场)

的数组里不大于f[i]的第一个数的下标。

当它小于1时就不存在这个数。

伪代码来一波：
```cpp
for (int i = 0; i < DP; i++)
    {
        if(f[i] == -1) continue;
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
                continue;
            int p = upper_bound(a[j] + 1, a[j] + a[j][0] + 1, f[i]) - a[j];
            if (p > 1)
                f[i | (1 << j)] = max(f[i | (1 << j)], a[j][p - 1] + d[j]);
            else
                f[i | (1 << j)] = f[i];
        }
        if (f[i] >= m)
            ans = min(ans, cnt1(i));
    }
```
其他代码呼之欲出，都是细节：

~~看在写题解那么辛苦的份上点个赞再走吧~~

你们在等的:
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, d[25], a[25][1005], f[1 << 20];
int cnt1(int x)
{
    int num = 0;
    while (x)
    {
        if (x & 1)
            num++;
        x = x >> 1;
    }
    return num;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &d[i], &a[i][0]);
        for (int j = 1; j <= a[i][0]; j++)
            scanf("%d", &a[i][j]);
    }
    int DP = 1 << n, ans = 1e9;
    memset(f,-1,sizeof(f));
    f[0] = 0;
    for (int i = 0; i < DP; i++)
    {
        if(f[i] == -1) continue;
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
                continue;
            int p = upper_bound(a[j] + 1, a[j] + a[j][0] + 1, f[i]) - a[j];
            if (p > 1)
                f[i | (1 << j)] = max(f[i | (1 << j)], a[j][p - 1] + d[j]);
            else
                f[i | (1 << j)] = f[i];
        }
        if (f[i] >= m)
            ans = min(ans, cnt1(i));
    }
    if (ans == 1e9)
        printf("-1");
    else
        printf("%d", ans);
    return 0;
}
```


---

## 作者：ASSWECAN (赞：12)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;傻逼题，但是真的恶心。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看到$n\le20$，明显是状压，很容易想到$dp$状态：$dp_i$表示当前看过的电影集合为$i$的最晩结束时间，最后只要判断$dp_i$是否大于等于$l$就可更新答案了。转移很好想，我们枚举下一场电影看什么，很容易证明，下一场电影的合法的开始时间中最晚的值一定能使结果最优，因为如果我们选了前面一个开始时间，带来的影响肯定比后面小，导致转移时受限。所以我们直接二分出开始时间就行了。总的时间复杂度$\Theta(n$·$2^n$·$log_2c)$。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;看样子可以过了，等等，如果不加优化的话交上去只能得$65$分~~，当然也可能是因为我天生自带大常数~~。那怎么优化呢，其实我们会发现，$dp_i$最多也就$20001$个不同的值（所有开始时间加上结束时间，以及一开始的$0$）。那么，我们不妨把二分放在外面进行，先离散化一下，这样$dp_i$记录的就是离散化后的下标，一样转移就行了。时间复杂度$\Theta(n$·$2^n+n^2c$·$log_2c)$，可以轻松通过全部数据。

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;具体细节详见代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
//#define usacojudge
int n,l;
int dp[1<<21];
int d[21];
int c[21];
int s[21][1010];
int cnt[1<<21];
int p[1<<21];
int to[20010][21];
int nxt[21][1010];
int ans=-1;
vector<int>tot;
int main()
{
	#ifdef usacojudge
	freopen("movie.in","r",stdin);
	freopen("movie.out","w",stdout);
	#endif
	scanf("%d%d",&n,&l);
	tot.push_back(0);
	for(int i=0;i<n;i++)
	{
		scanf("%d",d+i);
		scanf("%d",c+i);
		for(int j=0;j<c[i];j++)scanf("%d",&s[i][j]),tot.push_back(s[i][j]+d[i]);
	}
	sort(tot.begin(),tot.end());
	tot.erase(unique(tot.begin(),tot.end()),tot.end());
	for(int i=0;i<tot.size();i++)for(int j=0;j<n;j++)to[i][j]=upper_bound(s[j],s[j]+c[j],tot[i])-s[j]-1;
	for(int i=0;i<n;i++)for(int j=0;j<c[i];j++)nxt[i][j]=lower_bound(tot.begin(),tot.end(),s[i][j]+d[i])-tot.begin();
	for(int i=0;i<n;i++)p[1<<i]=i;
	for(int i=1;i<(1<<n);i++)cnt[i]=cnt[i-(i&-i)]+1;
	for(int i=0;i+1<(1<<n);i++)
	{
		int j=((1<<n)-1)^i;
		for(;j;j-=j&-j)
		{
			int k=p[j&-j];
			int pos=to[dp[i]][k];
			if(pos<0)continue;
			dp[i|(1<<k)]=max(dp[i|(1<<k)],max(dp[i],nxt[k][pos]));
		}
	}
	for(int i=0;i<(1<<n);i++)
	{
		if(tot[dp[i]]>=l)
		{
			if(ans==-1 || cnt[i]<ans)ans=cnt[i];
		}
	}
	printf("%d",ans);
	return 0;
} 
```

---

## 作者：TheAutumnGlory (赞：6)

# 好恶心的一道题！！！

这道题是让我们求**最小观看电影个数**，那么题意就可以简化成：

每个电影只能看一次，且为了保持**观看电影个数最小**，所以除了最后到l的一场，其他的都不能中途离开---->即**她也不能在看一部电影的过程中，换到另一个正在播放相同电影的放映厅**。

### 然后看数据范围：
$n<=20$**一眼状压**

现在，我们定$f[S]$为看了S集合里的电影最多可以看多少分钟。

$S$集合中$1$的说明看过，$0$说明没有。

那么我们可以通过宽搜来枚举S的所有情况

用$S$表示当前状态，$i$表示当前讨论的点，$s$表示目标状态——>$s=S|(1<<i)$

然后我们就可以通过二分查找找到最接近$f[S]$的第$i$个电影的开场时间和电影$i$的长度来更新$f[S]$

最后扫一遍所有的状态，找到看了$T$分钟后的一种状态使$1$最少

### 优化：
**通过一个打表的思路，先算出每个$S$的二进制下的$1$的个数，最后遍历的时间复杂度为$O(1)$**

### 注：
- **$bfs$找到的第一个$f[S]$超过l就是正解了——因为宽搜保证看的电影数量递增**
- **下列代码要开$O2$，建议用手写二分，队列，读入优化**

#### code:
```
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;
queue<int> q;
const int N=22;
const int K=1005;
bool vis[1<<N];
const int inf=1e9;
//arr[i][j]:表示第i部电影的第j场的开始时间
int n,len,t[N],k[N],arr[N][K],f[1<<N],tot,cnt[1<<N],ans=inf;
int main(){
	scanf("%d %d",&n,&len);
	tot=(1<<n)-1;
	for(int i=1;i<=tot;i++){//初始化找1的个数 
		cnt[i]=cnt[i>>1];
		if(i&1)
			cnt[i]++;
	}
	for(int i=1;i<=n;i++){
		scanf("%d %d",&t[i],&k[i]);
		for(int j=1;j<=k[i];j++)
			scanf("%d",&arr[i][j]);
		if(!arr[i][1]){//初始化f数组
			int p=(1<<(i-1));
			f[p]=t[i];
			q.push(p);
			vis[p]=true;
		}
	}
	while(q.size()){
		int p=q.front();
		q.pop();
		vis[p]=false;//p状态标记为不在队列中 
		if(f[p]>=len)
			break;//第一个f[q]超过len分钟就是正解了 
		for(int i=1;i<=n;i++){
			if((p>>(i-1))&1)
				continue;
			int tt=p|(1<<(i-1));
			int l=upper_bound(arr[i]+1,arr[i]+1+k[i],f[p])-arr[i]-1;//找出最接近f[p]的开场时间来更新f[p]
			if(f[tt]<arr[i][l]+t[i] && f[tt]<len){
				f[tt]=arr[i][l]+t[i];
				if(!vis[tt]){
					vis[tt]=true;//标记进队 
					q.push(tt);
				}
			}
		}
	}
	for(int i=1;i<=tot;i++){
		if(f[i]<len)//已经超过时间的直接跳过 
			continue;
		ans=min(ans,cnt[i]);
	}
	if(ans<inf)
		printf("%d",ans);
	else
		puts("-1");
	return 0;
}
```


---

## 作者：Sol1 (赞：5)

很容易的一道状压。

题目要求“相同的电影看一遍”，同时 $n\leq 20$，所以考虑状压。

先设状态为 $s$，$s$ 的二进制表示中从后往前数第 $i$ 位如果是 $1$ 则代表此时第 $i+1$ 个电影已经看过；反之亦然。

然后可以发现答案（即最小的观影数量）已经被包含在状态中了，所以可以调整一下最优化目标。由于题目中还涉及一个时间，所以考虑最优化时间 $t$。

不难发现，如果我们对这个状态设计的方案可以在 $[0,t]$ 内不间断观影，那么 $t$ 应该尽量大。

于是设 $f_s=t$，考虑转移。

显然转移就是加入一个新的电影，那么由于 $d$ 是固定的，就要让开始时间尽量大，又不造成间断。显然可以二分找到不超过当前 $f$ 值的最大的开始时间并进行转移。

那么这题就做完了~

时间复杂度 $O(2^nn\log c)$，空间复杂度 $O(2^n)$。

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1 << 21], *p1 = buf, *p2 = buf;

inline int qread() {
	register char c = getchar();
	register int x = 0, f = 1;
	while (c < '0' || c > '9') {
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
	return x * f;
}

inline int Abs(const int& x) {return (x > 0 ? x : -x);}
inline int Max(const int& x, const int& y) {return (x > y ? x : y);}
inline int Min(const int& x, const int& y) {return (x < y ? x : y);}

const int N = 25;
int n, l, d[N], c[N][1005], dp[(1 << 20) + 5], popcnt[(1 << 20) + 5];

inline void Read() {
	n = qread(); l = qread();
	for (int i = 1;i <= n;i++) {
		d[i] = qread();
		c[i][0] = qread();
		for (int j = 1;j <= c[i][0];j++) c[i][j] = qread();
	}
}

inline void Solve() {
	memset(dp, 0xcf, sizeof(dp));
	dp[0] = 0;
	for (int i = 1;i < (1 << n);i++) popcnt[i] = popcnt[i >> 1] + (i & 1);
	for (int i = 0;i < (1 << n);i++) {
		if (dp[i] < 0) continue;
		for (int j = 1;j <= n;j++) {
			if (!(i & (1 << j - 1))) {
				int lst = upper_bound(c[j] + 1, c[j] + c[j][0] + 1, dp[i]) - c[j] - 1;
				if (lst != 0 && c[j][lst] + d[j] > dp[i]) dp[i | (1 << j - 1)] = Max(dp[i | (1 << j - 1)], c[j][lst] + d[j]);
			}
		}
	}
	int ans = 0x3f3f3f3f;
	for (int i = 0;i < (1 << n);i++) {
		if (dp[i] >= l) {
			//printf("%d %d\n", i, dp[i]);
			ans = Min(ans, popcnt[i]);
		}
	}
	if (ans > n) puts("-1");
	else printf("%d", ans);
}

int main() {
	Read();
	Solve();
	#ifndef ONLINE_JUDGE
	while (1);
	#endif
	return 0;
}
```

---

## 作者：NewErA (赞：4)

一道比较典型的状态压缩DP题

不过好像测评慢了或是数据改强了导致现在什么代码也AC不了了？

以前能AC的代码现在也TLE？？？


不管了

由于n仅为20，因此可以用一个10进制数来表示所有电影观看与否这个状态

\_\_builtin\_popcount这个函数让我长见识了（一开始是 两个 下划线！！）


附上代码

```cpp
/*
    诡异卡常数题，至今未AC 
*/

#include<bits/stdc++.h>

using namespace std;
int n,l,dur[30],dp[1<<22];
int a[30][1005];

inline int read() //用read读取快 
{
    int x=0;
    char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x;
}

int main()
{
    n=read();l=read();
    for(int i=1;i<=n;i++)
    {
        cin >> dur[i] >> a[i][0];  //这里使用了一个小技巧，用a[i][0]存储数据个数，从而不用vector，提高速度！！！ 
        for(int j=1;j<=a[i][0];j++)
        {
            cin >> a[i][j];
        }
    }
    
    memset(dp,-1,sizeof(dp));
    dp[0]=0;
    int res=100;
    for(int i=0;i<(1 << n);i++)
    {
        if(dp[i]==-1) continue;
        
        for(int j=0;j<=n-1;j++)  //核心算法，由于n仅为20，使用状态压缩DP,对每个节目是否选取进行动归!!!
        {
            int k=1 << j;
            
            if((i & k)>0) continue;  //值得注意的地方，位运算优先级低，要打括号 要打括号 要打括号
            
            int pos=upper_bound(a[j+1]+1,a[j+1]+a[j+1][0]+1,dp[i])-a[j+1]; //直接用upper_bound查找第一个比dp[i]大的数 
            if(pos>1) dp[i | k]=max(dp[i | k],a[j+1][pos-1]+dur[j+1]);     //考虑应用lower还是upper!!! 
            else dp[i | k]=dp[i];
        }
        
        if (dp[i]>=l)
        {
            int cnt=__builtin_popcount(i);  //值得学习的函数，_builtin_popcount显示一个10进制数的二进制有多少个1 
            res=min(res,cnt);        
        }
    }
    
    if (res==100) cout << -1;
    else cout << res;
    return 0;
}
```

---

## 作者：Tmbcan (赞：3)

## [P3118 [USACO15JAN] Moovie Mooving G](https://www.luogu.com.cn/problem/P3118)
### 题目描述
有 $N$ 部电影，每部时长为 $val_i$ 共放映 $num_i$ 场，且第 $i$ 部电影第 $j$ 场的开场时间为 $tim_{i,j}$。  
每部电影只能看一次，看电影的中途可以换电影，求连续看满时长 $L$ 最少要看几部电影。
### 思路
数据范围 $1\le N\le 20$，考虑状压 DP。  
设 $dp_s$ 表示在状态 $s$ 时，可以连续看多久电影。  
对于每个状态 $s$，暴力枚举接下来我们要看的电影。

因为要求看的电影数量尽可能少，所以每次应该选择**最后一个不大于**当前时间的电影场次。这个操作可以用 `upper_bound` 解决。  

然后做正常的状压 DP 就可以了，设当前选到了电影 $i$，只有 $i$ **存在**不大于当前时间的场次，才进行转移。当前状态应当与电影结束时间取最大值，即 $\max(dp_{s|(1<<(i-1))} , tim_{i,idx}+ val_i)$。

### 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;
template <typename T>
inline void read(T&x){//快读
	int w=0;x=0;
	char ch = getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') w = 1;
		ch = getchar();
	}
	while(ch>='0' && ch<='9'){
		x = (x<<1)+(x<<3)+(ch^48);
		ch = getchar();
	}
	if(w) x=-x;
}
template <typename T,typename...Args>
inline void read(T&t,Args&...args){
	read(t);read(args...);
}
const int N = 25,INF = 0x3f3f3f3f;
int n,L;
int val[N],num[N],tim[N][1100];
int ans=INF,dp[(1<<20)+10];
int main(){
	read(n,L);
	for(int i=1;i<=n;++i){
		read(val[i],num[i]);//电影时长、场次数量
		for(int j=1;j<=num[i];++j){
			read(tim[i][j]);//每场的开始时间
		}
	}
	for(int s=0;s<1<<n;++s){
		for(int i=1;i<=n;++i){
			if((1<<(i-1))&s) continue;//电影已经选过
			int idx = upper_bound(tim[i]+1,tim[i]+num[i]+1,dp[s])-(tim[i]+1);
			if(idx>0) dp[s|(1<<(i-1))] = max(dp[s|(1<<(i-1))],tim[i][idx]+val[i]); //存在场次
		}
		if(dp[s]>=L) ans = min(ans,__builtin_popcount(s));//popcount非常快
	}
	printf("%d",ans==INF? -1 : ans);
	return 0;
}
```

---

## 作者：WZWZWZWY (赞：3)

~~啊吧啊吧，被打回了，死因没加句号，并且左移符号要用 `\ll`~~。

~~啊吧啊吧，又被打回了，死因没有在状压和 DP 中间加空格，还有 `LaTeX` 应写成 `\LaTeX`。~~

啊吧啊吧，再提交一次。

------------


在观摩了各位大佬的题解后，我来地讲讲。

本质上是：**状压 DP**。

没接触过的也不一定看不懂。

------------

### 什么是状态压缩

二进制都知道吧？都由 $0$ 或 $1$ 组成。

那么设一个二进制数 $S$。

如果它二进制下的（从低位向高位）第 $i$ 位为 $1$，表示第 $i$ 种电影被选择；为 $0$ 就是没有被选择。

比如 $S=1010$，说明总共有 $4$ 种电影，$1$、$3$ 种已经被选择。

嗯，那么你已经学会了设计状态。压缩？二进制数就是所谓“压缩”了。


------------

### 思路

设 $f[S]$，表示状态 $S$ 下，最大的观看结束的时间。也就是看完 $S$ 中的每种电影（也就是 $1$）后，最大的时间。

对于每种电影 $i$：

+ 如果 $S$ 的（从低位向高位）第 $i$ 位为 $1$，说明看过了，一个电影不能看两遍，跳过。

+ 如果为 $0$，那么将其设为 $1$（也就是 $S|(1\ll (i-1))$）。并寻找小于等于 $f_S$ 的 $i$ 种电影最大的开始时间。尝试更新 $f_{S|(1\ll (i-1))}$ 的值。

$\ll$ 是将二进制数整体左移的意思，$1$ 左移 $2$ 位就变成了 $100$。

显然，

$$
f_{s|(1\ll(j-1))} = \max(f_{i | (1\ll(j-1))}, k + last_j)
$$

$k$ 是小于等于 $f_S$ 的 $i$ 种电影最大的开始时间，$last_j$ 是 $j$ 种电影的持续时间。

（这种反直观的 $\LaTeX$ 真的不是我故意的啊喂！否则过不了题解……看得迷糊就看代码吧 QWQ。）


------------

### 代码

```
#include <bits/stdc++.h>
using namespace std;

int a[25][1005], c[25], f[1<<20], last[25], n, l;

int find(int x, int y) { // 题目保证同种电影的开始时间单调上升，可以二分（就算没有保证，也可以先排个序） 
	int l = 1, r = c[x], ans = -1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (a[x][mid] <= y) {
			ans = a[x][mid];
			l = mid + 1;
		} else r = mid - 1;
	}
	return ans;
}

int cnt(int x) { // 找二进制下的1的个数 
	int sum = 0;
	while (x > 0) {
		sum += (x & 1);
		x >>= 1;
	}
	return sum;
}

int main() {
	cin >> n >> l;
	for (int i = 1; i <= n; i++) {
		cin >> last[i] >> c[i];
		for (int j = 1; j <= c[i]; j++) cin >> a[i][j];
	} 
	
	int ans = 0x3f3f3f3f;
	for (int i = 0; i < (1 << n); i++) { //这里的 i 就是题解中的 S，也就是状态 
		if (f[i] >= l) ans = min(ans, cnt(i)); // 最长时间大于L，有解 
		for (int j = 1; j <= n; j++) { // 这里的 j 表示每一种电影 
			if ((i >> (j-1)) & 1) continue; // 第一种情况：这个电影看过了 
			int k = find(j, f[i]); // 找小于等于f[s]的最后一场 j 种电影的开始时间 
			if (k != -1) f[i | (1 << (j-1))] = max(f[i | (1 << (j-1))], k + last[j]); // 啊吧啊吧，最重要的转移（文章中心） 
		}
	}
	if (ans == 0x3f3f3f3f) cout << -1; // 无解
	else cout << ans;
}
```


[还是很轻松地 A 掉的](https://www.luogu.com.cn/record/list?pid=P3118&user=704668&page=1)。



------------

还有什么不懂的可以问我哦！

---

## 作者：xuantianhao (赞：3)

# [Moovie Mooving G](https://www.luogu.com.cn/problem/P3118)

设 $f[i][S]$ 表示在第 $i$ 场（注意是场，不是部）电影时，已经看了 $S$ 里面的电影是否合法。

然后贪心地取 $|S|$ 最小的状态保存。光荣 MLE 了， $21\%$。

发现当一场电影结束后，无论这一场是在哪里看的都没关系。

因此我们设 $f[S]$ 表示只看集合 $S$ 里面的电影，最多能够看多久。

转移就枚举下一场看什么，二分一下小于等于 $f[S]$ 的第一场比赛并观看即可。

复杂度 $O(n2^n\log C)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int INF=0x3f3f3f3f;
const int N=20;
int n,m,res=INF,x,y;
int f[1<<N],len[N];
vector<int> v[N];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        scanf("%d%d",&len[i],&x);
        while(x--){
			scanf("%d",&y);
			v[i].push_back(y);
		}
    }
    for(int x=0;x<(1<<n);x++){
        if(f[x]>=m){
			res=min(res,__builtin_popcount(x));
			continue;
		}
        for(int i=0;i<n;i++){
            if(x&(1<<i)) continue;
            vector<int>::iterator it=upper_bound(v[i].begin(),v[i].end(),f[x]);
            if(it==v[i].begin()) continue;
            it--;
            f[x|(1<<i)]=max(f[x|(1<<i)],*it+len[i]);
        }
    }
    printf("%d\n",res==INF?-1:res);
    return 0;
} 
```


---

## 作者：zach0914 (赞：2)

# [[USACO15JAN]Moovie Mooving G](https://www.luogu.com.cn/problem/P3118)

---

状压难题。不过也好理解。

---

首先我们根据题意：

> she does not want to ever visit the same movie twice.

这句话以及$n$的取值范围给了我们足够多的提醒：可能是**状态压缩**。

那么，当我们真正尝试用集合表示每个电影是否已看过的时候，我们却不容易给出能够转移的状态。

举个例子，当我们定义的状态中集合表示成为该状态的元素，那么这将会与最终求该集合的最小值冲突——状态中没法记录集合的最小值。

我们不妨换一种思路：$dp(i,S)$表示的是以$i$为结尾、已经看过的集合为$S$的**最长时间**。这种状态在转移的时候能够避免计算到不合法的状态，我们接下来具体分析：

容易得到：
$$
dp(i,S)=max(dp(j,S\setminus\{i\}),query(dp(j,S\setminus\{i\}))+d_i)
$$
其中，$query(dp(j,S\setminus\{i\}))$代表的是电影$i$中时间节点不超过$dp(j,S\setminus\{i\})$的最大值。而该状态下**允许**不存在这样的时间节点，转移的时候特殊处理即可。

这是由于计算的时候避免出现**间隔**——即看电影时间处处连续。

最后，统计最终答案的时候对于所有的大于等于限制$L$的状态计算它们的集合大小，更新。

这样做的时间复杂度为$O(n^22^nlogn)$。实际测试的时候会更快。

```c++
…… 
int n, L, t, c[N], d[N], st[N][C], siz[S] = {}, ttt[S];
int ans = INF, dp[N][S];
int query(int cur, int x)
{
	int L = 0, R = c[cur], mid, tmp; 
	while(L < R)
	{
		mid = L + ((R - L) >> 1);
		tmp = st[cur][mid];		
		if(tmp == x) return x;
		if(tmp < x) L = mid + 1;
		else R = mid;
	}
	if(!R) return -1;
	return st[cur][R - 1];
}
int main()
{
	scanf("%d %d", &n, &L);
	for(int i = 0; i < n; ++ i) 
	{
		scanf("%d %d", &d[i], &c[i]);
		for(int j = 0; j < c[i]; ++ j) scanf("%d", &st[i][j]);
	}
	t = (1 << n) - 1;
	for(int i = 1; i <= t; ++ i) siz[i] = siz[i ^ (i & (-i))] + 1;
	for(int i = 0; i < n; ++ i) ttt[1 << i] = i;
	for(int i = 1; i <= t; ++ i) ttt[i] = ttt[i & (-i)];
	memset(dp, 0, sizeof(dp));
	for(int s = 1; s <= t; ++ s)
	{
		for(int s0 = s, i = ttt[s]; s0; s0 &= ~(1 << i), i = ttt[s0])
		{
			if(siz[s] == 1 && st[i][0] == 0) dp[i][s] = d[i];
			else
			{
				for(int s1 = s ^ (1 << i), j = ttt[s1]; s1; s1 &= ~(1 << j), j = ttt[s1])
				{
					int tmp = query(i, dp[j][s ^ (1 << i)]);
					dp[i][s] = max(dp[i][s], dp[j][s ^ (1 << i)]);
					if(tmp != -1) dp[i][s] = max(dp[i][s], tmp + d[i]);
				}
			}
//			printf("dp[%d][%d] = %d\n", i, s, dp[i][s]);
			if(dp[i][s] >= L) ans = min(ans, siz[s]);
		} 
	}
	if(ans == INF) puts("-1");
	else printf("%d\n", ans);
	return 0;
} 
```

---

其实，我们发现，在我们转移的时候，我们完全可以仅记录一个集合代表该集合下所能达到的最长时间结点。这样一来，我们只需要枚举集合中的每一个元素，直接转移即可。

这是因为第一维状态是无用的，因为**转移只和DP出的值有关，与元素无关。**

时间复杂度：$O(n2^nlogn)$。空间也可以承受的了。

```c++
……
int n, L, t, c[N], d[N], st[N][C], siz[S] = {}, ttt[S];
int ans = INF, dp[S];
int query(int cur, int x)
{
	int L = 0, R = c[cur], mid, tmp; 
	while(L < R)
	{
		mid = L + ((R - L) >> 1);
		tmp = st[cur][mid];		
		if(tmp == x) return x;
		if(tmp < x) L = mid + 1;
		else R = mid;
	}
	if(!R) return -1;
	return st[cur][R - 1];
}
int main()
{
	scanf("%d %d", &n, &L);
	for(int i = 0; i < n; ++ i) 
	{
		scanf("%d %d", &d[i], &c[i]);
		for(int j = 0; j < c[i]; ++ j) scanf("%d", &st[i][j]);
	}
	t = (1 << n) - 1;
	for(int i = 1; i <= t; ++ i) siz[i] = siz[i ^ (i & (-i))] + 1;
	for(int i = 0; i < n; ++ i) ttt[1 << i] = i;
	for(int i = 1; i <= t; ++ i) ttt[i] = ttt[i & (-i)];
	memset(dp, 0, sizeof(dp));
	for(int s = 1; s <= t; ++ s)
	{
		for(int s0 = s, i = ttt[s]; s0; s0 &= ~(1 << i), i = ttt[s0])
		{
			int tmp = query(i, dp[s ^ (1 << i)]);
			dp[s] = max(dp[s], dp[s ^ (1 << i)]);
			if(tmp != -1) dp[s] = max(dp[s], tmp + d[i]);
			if(dp[s] >= L) ans = min(ans, siz[s]);
		} 
	}
	if(ans == INF) puts("-1");
	else printf("%d\n", ans);
	return 0;
} 
```

---

总结：

1. 这道题敢于在转移的过程中进行非$O(1)$做法的计算；
2. 当转移与状态中集合元素本身**无关联**，与状态值有关时应去除冗杂信息。

---

## 作者：Melo_DDD (赞：1)

虽然我是 dp 低手，但是我还是很喜欢这道的，不错不错。

一定要注意一部电影只能看一次啊。

~~通过观察数据范围我们发现~~，这是一道可以用状压 dp 求解的问题，那么应该把 dp 状态设成一个数，如果当前数在二进制下从低位开始第 $i$ 位是 $1$，表示我们已经选过了第 $i+1$ 部电影。

考虑如何转移，第 $j$ 部电影可以从 $i$ 状态转移过来的充要条件是 $i$ 在二进制下的第 $j-1$ 位不为 $1$。

转移方程怎么设定？发现值域很大，再放一维已经爆了啊，所以考虑把所用的时间设成 dp 值，即 $dp_i=k$ 表示状态为 $i$ 的时候最多可以从 $0$ 时刻看到 $k$ 时刻。

接下来考虑转移方程，如果第 $j$ 部电影可以从 $i$ 状态转移过来，即 $i$ 可以转移到 $i|(1\ll j-1)$，由于一部电影仅可以选择一次，所以可以贪心地考虑。具体地，我们应选择电影 $j$ 所有开始时间中小于等于 $dp_i$ 的最大的数，既可以满足合法性，也可以让结束时间尽量晚，一定是不劣的。

如何统计答案？考虑暴力枚举所有的 $i$，如果 $dp_i\ge l$，说明这个状态是合法的。而我们选择的电影的数量就是 $(i)_2$ 的 $1$ 的个数，对所有这样的 $i$ 的 $1$ 的个数取最小值即可。

不要忘记判断无解的情况。


```cpp
#include <bits/stdc++.h>
#define f(i ,m ,n ,x) for (int i = (m) ;i <= (n) ;i += (x))
using std :: cout ;
using std :: lower_bound ;
using std :: max ;
using std :: min ;
template < typename T > inline void read ( T &x ) {
	x = 0 ;
	bool flag (0) ;
	register char ch = getchar () ;
	while (! isdigit (ch)) {
		flag = ch == '-' ;
		ch = getchar () ;
	}
	while (isdigit (ch)) {
		x = (x << 1) + (x << 3) + (ch ^ 48) ;
		ch = getchar () ;
	}
	flag ? x = - x : 0 ;
}
template < typename T ,typename ...Args > 
inline void read ( T &x ,Args &...tmp ) {
	read (x) ,read (tmp...) ;
}
const int N = 21 ;
using ll = long long ;
int n ,siz[N] ;
ll l ,dp[1 << N] ,c[N][N * 100] ,d[N] ,sta ;
int main () {
	read (n ,l) ;
	f (i ,1 ,n ,1) {
		read (d[i] ,siz[i]) ;
		f (j ,1 ,siz[i] ,1) 
			read (c[i][j]) ;
	}
	sta = (1 << n) - 1 ;
	f (i ,0 ,sta ,1) {
		f (j ,1 ,n ,1) {
			if (i & (1 << j - 1)) continue ;
			if (c[j][1] > dp[i]) continue ;
			auto it = lower_bound (c[j] + 1 ,c[j] + siz[j] + 1 ,dp[i]) ;
			if (*it != dp[i]) it -- ; // 注意不能让 it 指向的值大于 dp[i]
			dp[i | (1 << j - 1)] = max ({dp[i | (1 << j - 1)] ,dp[i] ,*it + d[j]}) ; 
		} 
	}
	int ans = 0x7f7f7f7f ;
	f (i ,0 ,sta ,1) {
		if (dp[i] >= l) 
			ans = min (ans ,__builtin_popcount (i)) ; // 一个好用的函数
	}
	if (ans == 0x7f7f7f7f) 
		return puts ("-1") ,0 ;
	cout << ans << '\n' ;
	return 0 ;
}
```

---

## 作者：Kexi_ (赞：0)

思路很自然的可爱题！

首先看数据范围发现是状压，重新读题发现每种只能选一次。因此直接设 dp 数组表示不同选择情况时的最大观影时长，最后判断一下是否大于等于 $l$ 就好了！

对于每一种情况，你可以扣掉其中已经选择的一个电影然后转移。容易发现在确定电影开场时间比你扣掉这个情况的 dp 值小的情况下，你越往后的场次多出来的时长会更多，因此二分找第一个小于等于扣掉这个情况后的 dp 值的电影场次的开始时间就行。


```cpp
#include <bits/stdc++.h>
constexpr int N = 22;
int ans , n , l , m , x , d[N];
using namespace std;
vector<int> Time[N];
int dp[1 << N];
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main() {
	ans = 0x3f3f3f3f;
	n = read() , l = read();
	for(register int i = 1; i <= n; ++i) {
		d[i] = read() , m = read();
		Time[i].clear();
		for(register int j = 1; j <= m; ++j) {
			Time[i].push_back(read());
		}
		if(!Time[i][0]) {
			dp[1 << (i - 1)] = d[i];
		}
	}
	for(register int i = 1; i < (1 << n) ; ++i) {
		for(register int j = 1; j <= n; ++j) {
			if(i & (1 << (j - 1))) {
				if(dp[i ^ (1 << (j - 1))] < Time[j][0]) {
					continue; //如果你扣掉这个情况后最大的观影时长都没到开始时间，那就无法转移
				}
				int value = *--upper_bound(Time[j].begin() , Time[j].end() , dp[i ^ (1 << (j - 1))]);
        //找第一个小于等于扣掉后的情况的最大观影时长的开始时间
				if(value + d[j] > dp[i ^ (1 << (j - 1))]) {
					dp[i] = max(dp[i] , value + d[j]);	
				}	
			}
		}
	}
	for(register int i = 1; i < (1 << n); ++i) {
		if(dp[i] >= l) {
			ans = min(ans , __builtin_popcount(i));
		}
	}
	cout << (ans == 0x3f3f3f3f ? -1 : ans);
	return 0;
}
```

---

## 作者：_EternalRegrets_ (赞：0)

### 题意描述：
> 奶牛想要连续看 $l$ 分钟的电影。有 $n$ 种电影可以看，且奶牛可以从一个正在放映的电影转移到另一个正在放映的电影。特殊地，奶牛不能多次看同一种电影。

### 前置知识：状压动规

当情况比较少的时候，可以用一个 $01$ 序列来表示每一种状态。

以本题为例，序列 ```01001``` 可以表示在 $n=5$ 种电影种，奶牛已经看过了第一种和第四种电影。（从后向前）

转移方程具体题目具体分析，通常使用主动转移，即考虑当前状态可以转移到哪里。

### Solution:

一看数据范围：$n \leq 20$，容易想到状压动规。

$f_i$ 表示对于 $i$ 状态，看电影看到的最晚时间。

转移方式就很显然：枚举下一次看哪个电影，二分时间之后计算即可。

初始化：所有有在 $0$ 时刻开场的电影的单个电影状态的 $f_i$ 是电影的总时间。

计算答案：根据电影个数从小到大枚举情况，如果有情况 $i$ 使得 $f_i \geq l$，则可以直接输出答案。

### code:
```
#include<bits/stdc++.h>
#define int long long
using namespace std;

int f[1100000];

struct node{
    int t;
    int x;
    int a[1005];
};

node a[25];

int n;
bool cmp(int a,int b){ //主要用于排序转移顺序（按收看电影个数排序）
    int tmp1,tmp2; tmp1=a,tmp2=b;
    int x1,x2; x1=x2=0;

    for(int i=0;i<n;i++){
        int p; p=1<<i;

        if(a&p){
            x1++;
        }

        if(b&p){
            x2++;
        }
    }

    if(x1==x2){
        return a>b;
    }
    else{
        return x1<x2;
    }
}

int c[1100000]; //转移顺序
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    //freopen("movie.in","r",stdin);
    //freopen("movie.out","w",stdout);

    int l; cin>>n>>l;

    for(int i=1;i<=n;i++){
        cin>>a[i].t>>a[i].x;

        for(int j=1;j<=a[i].x;j++){
            cin>>a[i].a[j];
        }
    }

    for(int i=1;i<(1<<n);i++){
        c[i]=i;
    }

    sort(c+1,c+(1<<n),cmp);

    for(int i=1;i<(1<<n);i++){
        f[i]=-1;
    }

    for(int i=1;i<=n;i++){
        if(a[i].a[1]==0){
            f[(1<<(i-1))]=a[i].t;
            //cout<<f[(1<<(i-1))]<<endl;
        }
        else{
            f[(1<<(i-1))]=-1;
        }
    }

    for(int i=1;i<(1<<n);i++){
        if(f[c[i]]==-1){
            continue;
        }

        for(int j=1;j<=n;j++){
            if(!(c[i]&(1<<(j-1)))){
                int l,r; l=1,r=a[j].x;

                while(l<=r){
                    int mid; mid=(l+r)>>1;
                    if(a[j].a[mid]>f[c[i]]){
                        r=mid-1;
                    }
                    else{
                        l=mid+1;
                    }

                    //cout<<l<<" "<<r<<endl;
                }

                //cout<<r<<endl;
                //cout<<"*"<<endl;
                f[c[i]+(1<<(j-1))]=max(f[c[i]+(1<<(j-1))],a[j].a[r]+a[j].t);
                //cout<<"-"<<endl;
            }

            //cout<<"j:"<<j<<endl;
        }

        //cout<<"i:"<<i<<endl;
    }

    int ans; ans=0;
    for(int i=1;i<(1<<n);i++){
        if(f[c[i]]>=l){
            int x; x=c[i];
            for(int j=0;j<n;j++){
                if(x&(1<<j)){
                    ans++;
                }
            }

            cout<<ans;
            //cout<<" "<<f[c[i]]<<endl;
            return 0;
        }
    }

    cout<<-1;
    return 0;
}
```

---

## 作者：AK_heaven (赞：0)

[题目链接](https://www.luogu.com.cn/problem/P3118)

本人题解重在简洁，不懂可以私信我。

这是一道状压 DP，设 $F_s$ 为状态 $s$ 下，最多可以看多久电影。

则，有转移方程如下

$ F_{s|(1<<j)} = \max{( x + time_j )}$

其中，$x$ 需要满足存在一场 $x$ 时刻开始的 $j$ 电影。$s$ 需要满足第 $j$ 位为 $0$，并且 $x \le F_s$，$time_j$ 表示电影 $j$ 的时长。

准确来讲，这个转移的意义就是，在还没有看 $j$ 电影的情况下，在 $x$ 时刻或者在 $x$ 时刻到电影结束之前看 $j$ 电影。

- $O(2^n\times\sum c)$ 做法

枚举每个状态，找到该状态下还未看过的电影集合 $S$。对于每个 $j \in S$，都尝试进行转移。

期望得分 $57$ pts。

- $O(2^n\times \log \sum c) $ 做法

我们发现，$x \le F_s$ 和 $val_{x_i} < val_{x_{i+1}}$ 告诉我们转移点与价值具有单调性，且限制条件明确，所以可以二分查找答案，直接在 $\log \sum c$ 的时间内找到所有电影的最佳转移点。

期望得分 $100$ pts。

**银鞍照白马，飒沓如流星**

- the code


```cpp
#include <bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define pii pair<int, int>
#define ll long long
#define vi vector<int>
#define P 1e9+7917120411

using namespace std;

const int N = 21;

int f[(1<<N)], n, m, tot, w[N]; 

vector<int> vec[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	L(i, 1, n) {
		int k, s; cin >> w[i-1] >> s;
		while(s--) cin >> k, vec[i-1].push_back(k);
	}
	L(i, 0, (1<<n)-1) {
		for(int j = 0; j < n; j++)
		  if(!((i >> j)&1)) {
		  	int l = 0, r = vec[j].size()-1, x = -1;
		  	while(l <= r) {
		  		int mid = (l + r) >> 1;
		  		if(vec[j][mid] <= f[i]) l = mid+1, x = mid;
		  		else r = mid-1;
			}
		  	  if(x != -1)
		        f[i|(1<<j)] = max(f[i|(1<<j)], vec[j][x]+w[j]);
		  }
	}
	ll ans = 1e9;
	L(i, 0, (1<<n)-1) if(f[i] >= m) ans = min(ans, (ll)__builtin_popcount(i));
	if(ans == 1e9) cout << -1;
	else cout << ans;
	return 0;
}

```

---

