# 「PFLOI R1」PFL 除法

## 题目背景

[有必要把所有比赛题的背景连在一起](https://www.luogu.com.cn/paste/enzfvjum)。

就这样，新世界的大门向它们敞开了……  

“喵！”一只可爱的花猫向它们问好。  

“你们刚来到这？”  

“嗯。”  

“我带你们去转转吧，谁叫我这么可爱呢！”  

“……” 花猫突然止住，打量一番手中的序列，俶尔又微笑着说：  

“但你们要先答出我的问题哦。”

## 题目描述

花猫有一个长度为 $n$ 的序列 $A$ 和另一个长度为 $m$ 的序列 $B$。你可以进行若干次以下操作：

+ 选择两个整数 $i$ 和 $j$，满足 $1\le i\le n$，$1\le j\le m$ 且 $B_j \mid A_i$，然后将 $A_i$ 变为 $\frac{A_i}{B_j}$。

**注意**：$A$ 和 $B$ 中的每个元素都可以选择并被**操作多次**。

最终要使得 $A$ 中的元素都相等，请求出最少的操作次数；若无解，输出 `-1`。

## 说明/提示

**本题采用捆绑测试**。

| 子任务编号 | 特殊性质 | 分值 | 
| :----------: | :----------: | :-----:| 
| $1$ | $A$ 中所有元素相等 | $5$ |
| $2$ | $n=2$ | $15$ |
| $3$ | $n,m\le10^3$ | $20$ | 
| $4$ | $n,m\le10^4$ | $20$ | 
| $5$ | 无 | $40$ |

对于所有数据，$1\le n,m\le5\times10^5$，$1\le A_i,B_i\le5\times10^5$。

## 样例 #1

### 输入

```
4 5
16 24 28 36
11 4 7 3 2```

### 输出

```
6```

## 样例 #2

### 输入

```
2 3
11 13
13 1 11```

### 输出

```
2```

## 样例 #3

### 输入

```
2 2
2 3
4 5```

### 输出

```
-1```

# 题解

## 作者：qwq___qaq (赞：13)

验题人题解。

讲个笑话，出题人最早打的是 $O(nm)$，还被 ddxrS 叉了。

然后在一阵口胡之下成了第一发正解。

如果正向求所有情况的最小次数，很难处理，于是考虑枚举每一种情况然后求这一种情况的最小次数。

考虑枚举最后所有数都变成的数 $D$，那么就会有 $D\mid \min\{A\}$，当然如果存在 $i$ 使得 $D\nmid A_i$ 的情况除外。

那么现在就是求 $\sum\limits_{i=1}^n step(A_i\to D)$。

那么对于 $A_i$，我们相当于要除以一个 $x=\dfrac{a_i}{D}$，问题就转化为了 $B$ 中子序列乘积为 $x$ 的最短长度。

那么问题就转化为了一个背包，如果直接背包，复杂度是 $O(n^2)$ 级别的，考虑优化。

若存在 $i,j$ 使得 $B_i=B_j$，那么 $i,j$ 就是等价的，于是对 $B$ 去个重。

那么这个时候时间复杂度就是 $O(n+\dfrac{n}{2}+\cdots+\dfrac{n}{m})$，是一个调和级数，那么整体的时间复杂度就是 $O(n\log n)$。

讲个笑话，这个题原数据甚至不去重或者不 `sort` 直接 `unique` 都能过。

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int N=5e5+5;
int n,m,ans=inf,a[N],b[N],V,dp[N];
inline int get(int x){
	int s=0;
	for(int i=1;i<=n;++i){
		if(a[i]%x)
			return inf;
		if(dp[a[i]/x]==inf)
			return inf;
		s+=dp[a[i]/x];
	}
	return s;
}
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;++i)
    	cin>>a[i],V=max(V,a[i]);
    for(int i=1;i<=m;++i)
    	cin>>b[i],V=max(V,b[i]);
    sort(a+1,a+n+1);
     sort(b+1,b+m+1);
     m=unique(b+1,b+m+1)-b-1;
    memset(dp,inf,sizeof(dp)),dp[1]=0;
    for(int i=1;i<=m;++i)
    	for(int s=b[i];s<=V;s+=b[i])
    		dp[s]=min(dp[s],dp[s/b[i]]+1);
	for(int i=1;i<=a[1]/i;++i)
		if(a[1]%i==0)
			ans=min({ans,get(i),get(a[1]/i)});
	if(ans==inf)
		ans=-1;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：哈哈人生 (赞：9)

## 题外话
赛事差一点通过，主要是数据的一个点很毒瘤，搞点~~奇技淫巧~~才能过。

## 思路
我们应该这么想，既然最后所有的数都要转换为同一个数，而且过程中还不能除以不能被整除的数，很显然那么最后所有数转换成的这同一个数一定是所有数的最大公因数，我们把它设成 $g$。

那么每个数如何变成这个数次数是最小的呢，很容易推出结论，就是：$\frac{a_i}{g}$ 被 $b$ 数组中的数乘得，最小化数的个数。

为了求出这个值，容易想到动态规划，不过我爱写递归式的，这题数据水，也不用记忆化。

可以这么想：要求一个整数 $x$ 的最小分解，其实就是求它的每两个相配（相乘得 $x$）的因数中最小分解和（因为只有相乘得 $x$ 能分解 $x$），那么求它的因数的最小分解就有能按照如上所说的方法分。那方法就简单了，我们把 $b$ 数组每一个数标记出现，再把 $\frac{a_i}{g}$ 无线分解，如果 $b$ 数组标记过分解的这个数就返回 $1$，否则接着分解，注意到 $1$ 返回是 $0$，无则返回 $-1$。以上均使用递归函数即可。

如果你真这么写了，恭喜你，获得了~~接近满分的~~好成绩。

我们可以发现，在某些有解的情况下 $g$ 取最大公因数就变成无解了，也就是说 $g$ 不一定是最大公因数。所以无解时，如果 $g$ 还不是 $1$，还得接着往次大公因数、次次大公因数等取值，具体做法就可以看我的~~奇技淫巧的~~代码。

由于没有记忆化~~而且数据很水~~，这种做法的时间复杂度是标准的 $O(n\log a_i)$，其实能过我也很诧异。

## 代码
赛时被卡，赛后刷刷过，唉。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,a[500005],g=-1,s,ans=0;
bool b[500005];
int fc(int x) {
	if(x==1)return 0;//递归边界
	if(b[x]==1)return 1;//找到个数加一
	int minn=1<<30;
	for(int i=2; i*i<=x; i++) {//求最优（最小）值
		if(x%i==0){
			int xx=fc(i),yy=fc(x/i);//继续分解
			if(xx==-1||yy==-1)continue;
			minn=min(minn,xx+yy);
		}
	}
	if(minn!=1<<30)return minn;
	else return -1;//无解情况
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1; i<=n; i++) {
		cin>>a[i];
		if(g==-1)g=a[i];
		else g=__gcd(g,a[i]);
	}
	for(int i=1; i<=m; i++)cin>>s,b[s]=true;
	tz:;
	for(int i=1; i<=n; i++) {
		int j=fc(a[i]/g);
		if(j<0){
		    if(g==1)cout<<-1,exit(0);
		    else{
		        int g2=g-1;//奇技淫巧向下取值
		        while(g%g2)g2--;
		        g=g2;
		        ans=0;
		        goto tz;
		    }
		}
		else ans+=j;
	}
	cout<<ans;
	return 0;
}
```
站长曾经说过：不抄袭题解代码，只借鉴题解思路，但应该给题解点个赞（后半句话纯属娱乐哈）。

---

## 作者：LCat90 (赞：4)

首先考虑最终相等的那个值。它一定是 $\gcd _ {i=1}^n A_i$ 的因数。

所以我们枚举这个值 $x$，然后将 $A$ 里面的值都除以 $x$，问题就转变为了：运用序列 $B$，使新的序列 $A'$ 的所有元素都变为 $1$。

观察到值域并不大，可以预处理出将一个值 $V$ 操作至 $1$ 所需的最少方案数。具体地，设 $dp_j$ 表示数 $j$ 变为 $1$ 所需的最少操作次数。那么我们先枚举 $B_i$，有：

$$dp_{k\times B_i}=\min\{dp_{k\times B_i},dp_{k}+1\}$$

预处理完毕后，我们就可以枚举最终的值 $x$，然后把所有 $A_i$ 变成 $x$。这等价于将每个 $\dfrac{A_i}{x}$ 变为 $1$。那么我们只需要将所有 $dp_{\frac{A_i}{x}}$ 加起来，最后取最小值即可。



让我们来计算一下时间复杂度：设 $V$ 为值域。预处理是调和级数，时间为 $O(n\log V)$。枚举 $x$ 看似是 $O(\sqrt V)$，但实际上在 $5\times 10^5$ 范围内的数最多的因数只有 $I=200$ 个，在加上统计答案的 $O(n)$。所以总时间为 $O(In)$，在 $10^8$ 以内。

注意要给 $b$ 序列去重。不然预处理不满足调和级数，会炸时间。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5, M = 2e6, Mod = 1e9 + 7;
int n, m, a[N], b[N], ans = 1e9, x, V, mx, Gcd, dp[N];
signed main() {
	cin >> n >> m;
	for(int i = 1;i <= n; ++i) scanf("%d", &a[i]), V = max(V, a[i]), Gcd = __gcd(Gcd, a[i]);
	for(int i = 1, y;i <= m; ++i) {
		scanf("%d", &y);
		if(y != 1) b[++mx] = y, V = max(V, y);  
	} m = mx;
	sort(b + 1, b + m + 1);
	m = unique(b + 1, b + m + 1) - b - 1;
	memset(dp, 0x3f, sizeof dp);
	dp[1] = 0;
	for(int i = 1;i <= m; ++i)
		for(int j = 1;j * b[i] <= V;j ++) dp[j * b[i]] = min(dp[j * b[i]], dp[j] + 1);
	for(int i = 1;i * i <= Gcd; ++i)
		if(Gcd % i == 0) {
			int s = 0;
			for(int j = 1;j <= n; ++j) {
				if(dp[a[j] / i] == 0x3f3f3f3f) { s = 1e9; break ; }
				s += dp[a[j] / i];
			}
			ans = min(ans, s);
			s = 0;
			for(int j = 1;j <= n; ++j) {
				if(dp[a[j] / (Gcd / i)] == 0x3f3f3f3f) { s = 1e9; break ; }
				s += dp[a[j] / (Gcd / i)];
			}
			ans = min(ans, s);
		} 
	cout << (ans == 1e9 ? -1 : ans);
	return 0;
}
```

---

## 作者：yanhao40340 (赞：2)

场上只切了 A，B，C，结果只有 B 题加入了主题库……所以就来水题解了。

## 分析

观察到数据范围与 $n,m$ 同阶，可以想到这是一个依赖于值域的做法。

设 $x$ 为 $A_i$ 最后变成的数，显然有 $x \mid \gcd(A_1,A_2,\cdots.A_n)=k$。

考虑枚举 $x$ 的取值。

记 $f(a,b)$ 为 $a$ 变为 $b$ 的代价，则原题即求：

$$\min_{x|k}\sum^n_{i=1} f(A_i,x).$$

显然，我们需要快速处理出每一个 $f(A_i,x)$ 的值。

根据 $f$ 函数的定义可得：

**【结论 1】$f(A_i,x)=f(mA_i,mx),m \in \mathbb{N^+}$。**

证明：设 $A_i$ 变成 $x$ 需要依次除以 $B^\prime=\{
B_{a_1},B_{a_2},\cdots,B_{a_t}\}$ 中的每个元素，则有 $\prod_{i=1}^t a_i=\dfrac{A_i}{x}$。显然，$mA_i$ 也可以通过除以 $B^\prime$ 中的每个元素变成 $mx$。所以 $f(A_i,x) \ge f(mA_i,mx)$。 

同理可得，$f(A_i,x) \le f(mA_i,mx)$。所以 $f(A_i,x)=f(mA_i,mx)$。证毕。

因为 $x \mid A_i$，所以 $f(A_i,x)=f \left(\dfrac{A_i}{x},1 \right)$。

那么我们只用预处理出 $f(i,1),i \le \max\{A_i\}$ 即可。

与官方题解不同的是，我这里是用一种类似宽搜的方法解决的。由于每个数最多进队一次，且它每次只会搜索它的倍数，所以时间复杂度为 $\Theta(n+\dfrac n2+ \dfrac n3+ \cdots )$，即 $\Theta(n \log n)$。为保证每个数不会被重复搜，一开始需要对 $B$ 序列去重，否则会被卡成 $\Theta(n^2)$。注意特判掉 $1$ 的情况。

部分代码如下：

```cpp
#define int long long

sort(b+1,b+m+1);
m=unique(b+1,b+m+1)-b-1; //去重
for (int i=1;i<=m;++i) if (b[i]^1) //特判 1 的情况
	q.push(b[i]),cnt[b[i]]=1;
while (!q.empty()){
	int fr=q.front();q.pop();
	for (int i=1;i<=m;++i){
		if (b[i]==1) continue; //剪枝
		int tmp=fr*b[i]; //这里会爆 int
		if (tmp>=maxn) break; //剪枝
		else if (cnt[tmp]==inf) q.push(tmp),cnt[tmp]=cnt[fr]+1;
	}
}
```

这样我们就快速的预处理完了 $f(i,1),i \le \max\{A_i\}$ 的部分。

接下来枚举 $k$ 的正因子 $x_1,x_2,\cdots,x_r$，依次代入公式计算即可。

### 时间复杂度分析

显然时间复杂度为 $\Theta(n \log n + n\operatorname{d}(k))$，其中 $\operatorname{d}(i)$ 表示 $i$ 的正因子个数。

打表发现 $\max_{i=1}^{5 \times 10^5}\operatorname{d}(i)=200$，所以 $n \log n + n\operatorname{d}(k) \le 5 \times 10^5  \times 14 + 5 \times 10^5 \times 200=1.07 \times 10^8$。可以通过本题。

## 代码

**代码仅供参考。**已省略快读快输模板。

```cpp
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <vector>
#define int long long
using namespace std;
const int maxn=5e5+5,inf=0x3f3f3f3f3f3f3f3f;
queue<int> q;
int cnt[maxn],a[maxn],b[maxn]; 
vector<int> factors; //存储 k 的所有正因子，即 x 的所有可能取值
signed main(){
	memset(cnt,0x3f,sizeof cnt);
	cnt[1]=0; //初始条件
	int n=read(),m=read();
	for (int i=1;i<=n;++i) a[i]=read();
	for (int i=1;i<=m;++i) b[i]=read();
	sort(b+1,b+m+1);
	m=unique(b+1,b+m+1)-b-1;
	for (int i=1;i<=m;++i) if (b[i]^1)
		q.push(b[i]),cnt[b[i]]=1;
	while (!q.empty()){
		int fr=q.front();q.pop();
		for (int i=1;i<=m;++i){
			if (b[i]==1) continue;
			int tmp=fr*b[i];
			if (tmp>=maxn) break;
			else if (cnt[tmp]==inf) q.push(tmp),cnt[tmp]=cnt[fr]+1;
		}
	}
	int k=a[1];
	for (int i=2;i<=n;++i)
		if (k^1) k=__gcd(k,a[i]);
		else break;
	for (int i=1;i*i<=k;++i) //枚举出 k 的所有正因子
		if (!(k%i)) factors.push_back(i),factors.push_back(k/i);
	int ans=inf;
	for (int i:factors){
		if (!(k%i)){
			int tot=0;
			for (int j=1;j<=n;++j)
				if (cnt[a[j]/i]^inf) tot+=cnt[a[j]/i]; //按公式模拟
				else goto skip;
			ans=min(ans,tot);
		}
		skip:;
	}
	write(ans^inf?ans:-1);
	return 0;
}
```

---

## 作者：sbno333 (赞：0)

这道题很好想到，枚举 $A$ 数组的公因数，即最大公因数的因数。

```cpp
	__int128 gc;
	gc=0;
	for(__int128 i=1;i<=n;i++)gc=__gcd(gc,(__int128)a[i]);//计算最大公因数
	__int128 ans;
	ans=1e12;
	for(long long i=1;i*i<=gc;i++)
		if(gc%i==0)
			ans=min(ans,min(an(i),an(gc/i)));//计算最后变为i或gc/i的话的结果
	if(ans>1e9)
		ans=-1;
	cout<<(long long)ans;
```
然而，我们还需要计算结果，我们考虑枚举 $A$ 数组，每次枚举计算需要除以的数。

```cpp
__int128 an(__int128 x){
	__int128 ans;
	ans=0;
	for(__int128 i=1;i<=n;i++)
		ans+=f[a[i]/x];//f存储除以这个数需要几次操作
	return ans;
}
```

然后就是难点：计算 $f$ 数组。

我们可以参考欧式筛，可以将 $B$ 数组中的数假设为欧式筛中的质数，每次找到的数为当前数乘 $B$ 数组某个数，其 $f$ 的值为当前的值加一和原来的值的最小值，即动态规划，特别的，如果遇到当前数的因数，**不退出**。

```cpp
	for(__int128 i=0;i<1000009;i++)
		f[i]=1e12;//初始为无穷
	cin>>n>>m;
	for(__int128 i=1;i<=n;i++)
		cin>>a[i];
	for(__int128 i=1;i<=m;i++)
		cin>>a[0],vis[a[0]]=1;//输入B数组
	vis[1]=1;
	f[1]=0;//必要的初始化
	for(__int128 i=2;i<=500009;i++){
		if(vis[i]){//如果在B数组
			zzz[++inn]=i;
			f[i]=1;
		}
		for(__int128 j=1;j<=inn&&zzz[j]*i<=500009;j++){//模仿欧式筛
			f[zzz[j]*i]=min(f[zzz[j]*i],f[i]+1);//DP
			if(i%zzz[j]==0){//由于不是质数，而且是取最小值，所以不退出，好吧，其实是亲身试验，呜呜呜
			//	break;//不退出
			}
		}
	}
```

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[1000009];
__int128 f[1000009];
long long a[1000009];
__int128 zzz[1000009];
__int128 inn;
long long n,m;
__int128 an(__int128 x){
	__int128 ans;
	ans=0;
	for(__int128 i=1;i<=n;i++)
		ans+=f[a[i]/x];
	return ans;
}
int main(){
	for(__int128 i=0;i<1000009;i++)
		f[i]=1e12;
	cin>>n>>m;
	for(__int128 i=1;i<=n;i++)
		cin>>a[i];
	for(__int128 i=1;i<=m;i++)
		cin>>a[0],vis[a[0]]=1;
	vis[1]=1;
	f[1]=0;
	for(__int128 i=2;i<=500009;i++){
		if(vis[i]){
			zzz[++inn]=i;
			f[i]=1;
		}
		for(__int128 j=1;j<=inn&&zzz[j]*i<=500009;j++){
			f[zzz[j]*i]=min(f[zzz[j]*i],f[i]+1);
			if(i%zzz[j]==0){
			//	break;
			}
		}
	}
	__int128 gc;
	gc=0;
	for(__int128 i=1;i<=n;i++)gc=__gcd(gc,(__int128)a[i]);
	__int128 ans;
	ans=1e12;
	for(long long i=1;i*i<=gc;i++)
		if(gc%i==0)
			ans=min(ans,min(an(i),an(gc/i)));
	if(ans>1e9)
		ans=-1;
	cout<<(long long)ans;
	return 0;
} 
```

---

## 作者：caohan (赞：0)

# 思路

这道题不难让人发现，分这几部分：

- 先将 $a$ 和 $b$ 最大值统计出来，用一个简单的滚动无尽背包算出最大值以下每一个数用 $b$ 中的数表示的最小个数。结果存于 $dp$ 即可。

- 而后像 $x \in [1,a_1]$ 枚举，计算最后 $a$ 全部化成该数的总步数，其实就是 $\sum_{i=1}^{n} dp_{a_i/x}$ 这个值。

这时发现，总的时间复杂度为 $\operatorname{O}(n^2)$ 的量级。试图通过将 $b$ 去重的方式优化为一个调和级数，即 $\operatorname{O}(n \log n)$ 即可。

这道题真~~简单~~。

# 代码

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
int a[500005];
int b[500005];
int n,m;
int dp[500005];
int get(int x)
{
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(a[i]%x)
		{
			return inf;
		}
		if(dp[a[i]/x]==inf)
		{
			return inf;
		}
		ans+=dp[a[i]/x];
	}
	return ans;
}//计算当把全部的数化为x时用的最小总次数（加和就行）
int maxx;
int main()
{
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		maxx=max(maxx,a[i]);
	}
	for(int i=1;i<=m;i++)
	{
		cin>>b[i];
		maxx=max(maxx,b[i]);
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);
	m=unique(b+1,b+m+1)-b-1;
	memset(dp,inf,sizeof(dp));
	dp[1]=0;
   //输入+排序+去重+初始化
	for(int i=1;i<=m;i++)
	{
		for(int j=b[i];j<=maxx;j+=b[i])
		{
			dp[j]=min(dp[j],dp[j/b[i]]+1);
		}
	}//滚动背包dp
	int ans=inf;
	for(int i=1;i*i<=a[1];i++)
	{
		if(a[1]%i==0)
		{
			ans=min(ans,min(get(i),get(a[1]/i)));
		}
	}//枚举因数
	if(ans==inf)
	{
		ans=-1;
	}
	cout<<ans;
	return 0; 
}
```


---

## 作者：smyoking (赞：0)

## 题目简述

有两个序列 $A$ 和 $B$，经过若干次操作，得到 $A$ 序列中全部元素相同，求出最少的操作数。

## 思路

最终的序列通过~~做法~~操作之后元素相同，而操作是 $\frac{A_i}{B_j}$，很容易看出来最终的元素一定是序列 $A$ 的最大公约数的因数。

首先，我们将 $B$ 序列可以不限次数相乘得到的数字求出，这个可以用完全背包进行。通过一系列操作，我们就可以得到一个已经处理好的数组 $dp[]$。

对于 $dp[]$ 这个数组，初始化值为 $\infty$，经过完全背包之后，如果 $i$ 这个数可以通过 $B$ 序列得到。 

我们令 $g$ 为序列 $A$ 的最大公约数，令 $e$ 为 $g$ 的因数，对于满足条件的 $e$，必须是可以得到的，也就是 $dp[A_i/e]$ 不能等于 $\infty$。

然后，就可以美美的暴力求 $e$ 和总次数 $tot$，最终答案取最小的 $tot$ 即可。

注意，**序列 $B$ 需要进行去重。**

## Code

```cpp
#include<bits/stdc++.h>
#include<string>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<set>

using namespace std;

inline int read() {
	int x=0,f=1;char s=getchar();
	while (s>'9'||s<'0') {
		if (s=='-') f=-f;
		s=getchar();
	}
	while (s>='0'&&s<='9') {
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return x*f;
}

const int N = 5e5+10;
const int INF = 1e9;

int n,m,a[N],b[N],g,amax,ans,tot,dp[N];
vector<int>y;

int gcd(int xx,int yy) {  //辗转相除法求最大公约数 
	if (!yy) return xx;
	else return gcd(yy,xx%yy);
}

int main() {
	n=read();m=read();
	for (int i=1;i<=n;++i) a[i]=read(),g=gcd(a[i],g),amax=max(amax,a[i]);
	for (int i=1;i<=m;++i) b[i]=read();
	for (int i=1;i<=amax;++i) dp[i]=INF;  //初始化 
	dp[1]=0;  
	sort(b+1,b+1+m);
	for (int i=1;i<=m;++i) {
		if (b[i]==b[i-1]) continue;  //去重 
		for (int j=1;j*b[i]<=amax;++j) 
			if (dp[j]!=INF) dp[j*b[i]]=min(dp[j*b[i]],dp[j]+1);
			// 如果上一个数j已经得到的话，那么j*b[i]也就自然可以得到 
	}
	for (int i=1;i*i<=g;++i) {//暴力求出序列A的 g 的因子 e 
		if (g%i==0) {
			y.push_back(i);  
			if (g!=i*i) y.push_back(g/i);
		}
	}
	int len=y.size();
	ans=INF;
	for (int i=0;i<len;++i) {
		bool t=true;tot=0;
		for (int j=1;j<=n;++j) {
			if (dp[a[j]/y[i]]==INF) {
				//此时这个因子e显然不满足条件，无法得到，所以直接跳过它 
				t=false;break;
			}
			tot+=dp[a[j]/y[i]];
		}
		if (t) ans=min(ans,tot); //当前这个因子e满足条件，ans取最小值 
	}
	if (ans==INF) printf("-1\n"); //ans没动过，说明没有满足条件的e，则输出-1 
	else printf("%d\n",ans);
	return 0;
} 
```


---

