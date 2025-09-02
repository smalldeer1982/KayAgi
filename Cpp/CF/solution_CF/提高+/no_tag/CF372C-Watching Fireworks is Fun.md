# Watching Fireworks is Fun

## 题目描述

一个节日将在城镇的主街道上举行。主街道被划分为 $n$ 个区域，这些区域从左到右依次编号为 $1$ 到 $n$。相邻区域之间的距离为 $1$ 单位长度。

节日期间将发射 $m$ 个烟花。第 $i$ 次（$1 \leq i \leq m$）发射将在时间 $t_{i}$ 于区域 $a_{i}$ 进行。如果你在第 $i$ 次发射时位于区域 $x$（$1 \leq x \leq n$），你将获得幸福值 $b_{i} - |a_{i} - x|$（注意幸福值可能为负数）。

你可以在单位时间间隔内移动最多 $d$ 单位长度，但禁止移动到主街道之外。你可以在初始时刻（时间等于 $1$ 时）处于任意位置，目标是最大化观看烟花获得的总幸福值。求可能的最大总幸福值。

注意多个烟花可能在同一时间发射。

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
50 3 1
49 1 1
26 1 4
6 1 10
```

### 输出

```
-31
```

## 样例 #2

### 输入

```
10 2 1
1 1000 4
9 1000 4
```

### 输出

```
1992
```

# 题解

## 作者：Grussg (赞：60)

# $Problem:CF372C~ Watching~ Fireworks~Is ~Fun$ 
# $Description$


一个城镇有$n$个区域,从左到右编号为$1$到$n$,每个区域之间距离$1$个单位距离。
  
节日中有$m$个烟花要放，给定放的地点$a_i$​,时间$t_i$​,以及一个参数$b_i$。如果你当时在区域$x$,那么你可以获得$b_i - \vert a_i - x\vert$的开心值。  

你每个单位时间可以移动不超过$d$个单位距离。 你的初始位置是任意的(初始时刻为$1$),求你通过移动能获取到的最大的开心值。
数据范围：

$1\leq n\leq150000,1\leq m\leq 300,1\leq d\leq n$
$1\leq a_i\leq n,1\leq bi\leq10^9,1\leq t_i\leq10^9$
# $Solution$
先思考用什么算法。

如果是贪心，实际上是不好贪心的，因为它有多个参数。~~是蒟蒻的我也不会贪心~~

贪心不行，瞧上去又像是道~~乱搞题~~，那肯定是$DP$。

思考朴素$DP$

设$f[i][j]$为第$i$个烟❀的时候在第$j$个区间的最大开心值

推导方程

可见$f[i][j]=min(f[i][j],f[i-1][k]+b_i - \vert a_i - x\vert)$  $k\in[max(1,j-t\times d),min(n,j+t\times d)]~~t=t_i-t_{i-1}$

朴素$dp$方程还是很好推的

但是看时间复杂度最大$O(mn^2)$是无法通过的

同时的数组$f[300][150000]$也是无法开下来的

先解决空间问题

**优化1：**

容易想到滚动数组第一维$i$显然不需要存那么多，只需要存下当前$i$和$i-1$即可，滚掉一维即可。

**优化2：**

同时求$b_i - \vert a_i - x\vert$的最大值，同时$b_i$是一个固定的参数，
我们可以转换成求$- \vert a_i - x\vert$的最大值，即$\vert a_i - x\vert$的最小值，这样可以更加方便操作

再想如何解决时间问题

**优化3：**

我们枚举$i \to m$是无法优化的，同时枚举每个位置$j \to n$也是无法避免的，所以说我们想如何优化$k$的遍历，因为我们只需要通过在$k$的范围内最小值来更新现在的$f[i][j]$。既然需要最小值，用单调队列优化即可。我们跑两遍，从$1 \to n$和从$n \to 1$跑一遍，分别从右和从左更新$f[i][j]$。还有问题的可以结合代码看看

# $Code$
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MaxN=152000;
ll n,m,d,sum;
ll a[MaxN],b[MaxN],t[MaxN],f[2][152000],q[MaxN];
template <class G> inline void read(G&x){
	bool f;char ch=getchar();
	for(f=false;!isdigit(ch);ch=getchar())if(ch=='-')f=true;
	for(x=0;isdigit(ch);x=(x<<1)+(x<<3)+(ch^48),ch=getchar());
	x*=f==1?-1:1;
}
inline int abs(int x){
	if(x<0) return -x;
	return x;
}
signed main(){
	read(n),read(m),read(d);
	memset(f,0x3f3f3f,sizeof(f));
	for(register int i=1;i<=m;i++) read(a[i]),read(b[i]),read(t[i]),sum+=b[i];
	for(register int i=1;i<=n;i++) f[1][i]=abs(a[1]-i);
	for(register int i=2;i<=m;i++){
		int now=i&1,last=i&1^1,ti=t[i]-t[i-1];
		memset(f[now],0x3f3f3f,sizeof(f[now]));
		int head=1,tail=0;
		for(register int j=1;j<=n;j++){
			while (head<=tail&&q[head]<j-ti*d) ++head;
			while (head<=tail&&f[last][q[tail]]>f[last][j]) --tail;
			q[++tail]=j;
			f[now][j]=min(f[now][j],f[last][q[head]]+abs(a[i]-j));
		}
		head=1,tail=0;
		for(register int j=n;j>=1;j--){
			while (head<=tail&&q[head]>j+ti*d) ++head;
			while (head<=tail&&f[last][q[tail]]>f[last][j]) --tail;
			q[++tail]=j;
			f[now][j]=min(f[now][j],f[last][q[head]]+abs(a[i]-j));
		}		
	}
	ll ans=INT_MAX/2;
	for(register int i=1;i<=n;i++) ans=min(f[m&1][i],ans);
	cout<<sum-ans;
	return 0;
}
```
# $Postscript$
这只是一道很$naive$的题

也感谢其他奆佬写的题解对我的帮助

更多的单调队列优化$DP$好题
                  
1.[ [POI2014]PTA-Little Bird（板子）](https://www.luogu.org/problem/P3572).
                  
2.[ [NOI2011]Noi嘉年华](https://www.luogu.org/problem/P1973)

希望大家对单调队列优化的$DP$有更深的理解

# $C_{s_p}~_20^{1^9}~P_{l^us}~P^{l_{u_s}}$

>希望各位考完联赛能和最爱的人好好看一场烟花





---

## 作者：RedLycoris (赞：33)

[CF372C Watching Fireworks is Fun](https://www.luogu.com.cn/problem/CF372C)

我们可以换种思考方式来解决这个问题。

显然 $b_i$ 是一个很无关紧要的东西，我们可以把它们先全部累加到 $ans$ 里。然后题目就变成了要让 $\sum -|a_i-x|$ 最大，所以就可以看为要使得 $\sum |a_i-x|$ 最小。

令 $f(x)$ 表示考虑到某个时间点，此时你的坐标为 $x$ 的最小的 $\sum |a_i-x|$。

假设我们已经考虑了前 $i$ 场烟花，此时我们要考虑加入第 $i+1$ 场烟花带来的影响。

令 $\Delta t=t_{i+1}-t_i, s=\Delta t\times d$，则我们就相当于执行 $f(x)=\min(f(x-d)\dots f(x+d))$。

然后每燃放一场烟花，我们就相当于对 $f(x)$ 加上一个 $|a_i-x|$ 的函数。

综上，可以发现，这个 $f(x)$ 是一个折线函数，且段数是 $O(m)$ 的，计算相邻时间和加入新烟花秀都可以在 $O(m)$ 的时间内解决，故我们得到了一个时间复杂度为 $O(m^2)$ 的做法。

考虑继续优化。

发现这个 $f(x)$ 的每条折线的斜率从左往右可以看作依次为 $-i,-i+1,\dots,0,\dots i-1,i$。

这启发我们可以维护两个优先队列一样的东西，一个维护左半段斜率小于 $0$ 的部分的转折点的 $x$ 坐标，另一个维护右半段的东西。

我们考虑在这种维护方式下，等待时间和加入烟花秀各有什么影响。

由于这个 $f(x)$ 是先降后增的，所以这个等待一段时间就变得非常好处理。就是让 $L$ 中的所有元素减去 $s$，$R$ 中的所有元素加上 $s$，中间多出一段斜率为 $0$ 的段。

当然，我们没有必要真的去减一遍，我们只需要维护两个全局减去/加上的 $sL$ 和 $sR$，每次就让 $sL-s,sR+s$，然后再 $L,R$ 中加入新元素的时候就加入 $l+sL,r-sR$。

再考虑这个加入烟花的操作。

令左半段最右边的转折点横坐标为 $l$，右半段最左边的转折点横坐标为 $r$。

+ $l<a_i<r$

此时就相当于 $L,R$ 都多了一个转折点 $a_i$，都push。

+ $a_i \le l$

此时 $L$ 的最右边的转折点就成为了 $a$，且斜率为 $-1$ 的转折点消失了，但不妨碍我们维护，因为我们可以想象它和斜率为 $0$ 的转折点重合了。

所以我们加入两边 $a$ 至 $L$，然后把 $l$ 加到 $R$ 即可。

+ $a_i \ge r$

和上一种情况同理。

综上，时间复杂度 $O(m\log m)$，可以加强到 $n=10^9,m=2\times10^5$，甚至比原题的单调队列优化dp好写的多。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,d,ans,tag,pre;
priority_queue<int>L;
priority_queue<int,vector<int>,greater<int> >R;
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m>>d;
	for(int i=1;i<=m;++i){
		int a,b,t;cin>>a>>b>>t;
		ans+=b;
		if(i==1)L.push(a),R.push(a),pre=t;
		else{
			tag+=d*(t-pre);
			int l=L.top()-tag,r=R.top()+tag;
			if(a<l)L.pop(),L.push(a+tag),L.push(a+tag),R.push(l-tag),ans-=l-a;
			else if(a>r)R.pop(),R.push(a-tag),R.push(a-tag),L.push(r+tag),ans-=a-r;
			else L.push(a+tag),R.push(a-tag);
		}
		pre=t;
	}
	cout<<ans<<'\n';
}
```

---

## 作者：LevenKoko (赞：13)

$$\Large\href{https://www.cnblogs.com/zhenglw/p/11740954.html}{\textcolor{red}{My Blog}}$$


突然发现我可能单调队列都打不来了...我太菜了...

 

------------
有一个显然的转移方程：
$$f[i][j]=max\{f[i-1][k]+b[i]-\vert j-a[i] \vert\}$$

而$ans=max_{i=1}^{n}\{f[m][i]\}$

观察到有个$b[]$其实是没有什么用的，所以对式子进行一些魔改


如果设


$$f[i][j]=min\{f[i-1][k]+\vert j-a[i] \vert\}$$

 

则$ans=\sum_{i=1}^{m} b_i - min_{j=1}^{n}\{f[m][j]\}$

 

令$len=(t[i]-t[i-1])*d$则其中k满足
$$k∈[j-len,j+len]$$

 

$f[i][]$只与$f[i-1][]$有关，所以可以把第一维压掉

 

不难弄出一个$O(n^2m)$的代码：
```cpp
#include<bits/stdc++.h>
#define int long long 
#define writeln(x)  write(x),puts("")
#define writep(x)   write(x),putchar(' ')
using namespace std;
inline int read(){
	int ans=0,f=1;char chr=getchar();
	while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
	while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
	return ans*f;
}void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}const int M = 150005;
int f[2][M],n,m,d,ans=0x3f3f3f3f,sum;
struct P{int a,b,t;}a[M];
signed main(){
	n=read(),m=read(),d=read(),sum=0;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		sum+=y;a[i]=(P){x,y,z};
	}for(int i(1);i<=n;i++)f[1][i]=abs(a[1].a-i);
	for(int i(2);i<=m;i++){	
		memset(f[i&1],0x3f,sizeof(f[i&1]));
		int len=(a[i].t-a[i-1].t)*d;
		for(int j=1;j<=n;j++){
			for(int k=max(1ll,j-len);k<=min(j+len,n);k++)
				f[i&1][j]=min(f[i&1][j],f[i&1^1][k]+abs(a[i].a-j));
			if(i==m)ans=min(ans,f[i&1][j]);
		}
	}cout<<sum-ans<<endl;
	return 0;
}
```
 

------------


------------


但是显然会T，注意到上面k的范围，可以考虑单调队列优化，对于每一次的$i,j$，对$[j-len,j]$跑一次滑动窗口，对$[j,j+len]$跑一次滑动窗口取最小值即可

 
```cpp
#include<bits/stdc++.h>
#define int long long
#define writeln(x)  write(x),puts("")
#define writep(x)   write(x),putchar(' ')
using namespace std;
inline int read(){
	int ans=0,f=1;char chr=getchar();
	while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
	while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
	return ans*f;
}void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}const int M = 150005;
int f[2][M],n,m,d,ans=0x3f3f3f3f,sum,q[M];
struct P{int a,b,t;}a[M];
signed main(){
	n=read(),m=read(),d=read(),sum=0;
	for(int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		sum+=y;a[i]=(P){x,y,z};
	}for(int i(1);i<=n;i++)f[1][i]=abs(a[1].a-i);
	for(int i(2);i<=m;i++){
		int len=(a[i].t-a[i-1].t)*d,l=1,r=0;
		for(int j=1;j<=n;j++){
			while(l<=r&&q[l]<j-len)++l;
			while(l<=r&&f[i&1^1][q[r]]>f[i&1^1][j])--r;
			q[++r]=j;
			f[i&1][j]=f[i&1^1][q[l]]+abs(j-a[i].a);
			if(i==m)ans=min(ans,f[i&1][j]);
		}l=1,r=0;
		for(int j=n;j>=1;j--){
			while(l<=r&&q[l]-len>j)++l;
			while(l<=r&&f[i&1^1][q[r]]>f[i&1^1][j])--r;
			q[++r]=j;
			f[i&1][j]=min(f[i&1][j],f[i&1^1][q[l]]+abs(j-a[i].a));
			if(i==m)ans=min(ans,f[i&1][j]);
		}		
	}cout<<sum-ans<<endl;
	return 0;
}
```

打完收工qwq

---

## 作者：He_Ren (赞：6)

动态规划

不难想到，用$dp[i][j]$表示到第$i$个烟花，位置为$j$的答案

$dp[i][j]=max\{dp[i-1][k]\}+\text{欢乐度}$

即：$dp[i][j]=max\{dp[i-1][k]\} + (b[i]-|a[i]-j|)$

复杂度$O(n^2 m)$，太慢

**优化dp时要观察dp中不变的量**

发现对于每个$i$，$k$的值都是一个固定的范围（$\pm d(t[i]-t[i-1])$）

**用单调队列优化**

这样转移复杂度均摊$O(1)$

总复杂度$O(nm)$，可过

---

在实现上，发现b很烦，所以我用$dp[i][j]$表示到第$i$个烟花，位置为$j$的距离之和的最小值

$dp[i][j]=min\{dp[i-1][k]\} + |a[i]-j|$

然后答案就是

$\sum_{i=1}^m b[i] - min\{dp[m][i]\}$

注意$O(nm)$的空间会炸，需用滚动数组优化

```cpp
#include<cstdio>
typedef long long ll;
const int MAXN = 150000 + 5;
const int MAXM = 300 + 5;
const ll inf = 0x3fffffffffffffff;

inline ll abs(ll x){ return x<0? -x: x;}
inline void chk_min(ll &a,ll b){ if(a>b) a=b;}

int a[MAXM],b[MAXM],t[MAXM];
ll dp[3][MAXN];

int q[MAXN],hd=0,tl=0;
inline void init(void){ hd=tl=0;}
inline void push(int i,int x)
{
	while(tl>hd && dp[i][q[tl]]>dp[i][x]) --tl;
	q[++tl]=x;
}
inline void pop(void)
{
	if(hd < tl) ++hd;
}

int main(void)
{
	int n,m,d;
	scanf("%d%d%d",&n,&m,&d);
	for(int i=1; i<=m; ++i) scanf("%d%d%d",&a[i],&b[i],&t[i]);
	
	for(int i=1; i<=m; ++i)
	{
		int now = i&1, last = now^1;
		
		ll nd = (ll)d*(t[i]-t[i-1]);
		
		init();
		for(int j=1; j<=nd && j<=n; ++j)
			push(last,j);
		
		for(int j=1; j<=n; ++j)
		{
			if(q[hd+1] < j-nd) pop();
			if(j+nd <= n) push(last,j+nd);
			dp[now][j] = dp[last][q[hd+1]] + abs((ll)a[i]-j);
		}
	}
	
	ll ans=inf;
	for(int i=1; i<=n; ++i)
		chk_min(ans, dp[m&1][i]);
	ll sum=0;
	for(int i=1; i<=m; ++i) sum+=b[i];
	printf("%lld",sum-ans);
	return 0;
}
```


---

## 作者：Plozia (赞：4)

宣传博客：[link](https://blog.csdn.net/BWzhuzehao/article/details/109687742)

题目链接：[link](https://www.luogu.com.cn/problem/CF372C)

## 初步分析：

这道题首先不会是贪心 ~~（其实是我不会）~~ ，看到“最大”二字，又看了眼数据范围，基本上可以定下来是 dp 题了。

首先设状态： $f[i][j]$ 表示第 $i$ 个烟花放出时当前人在 $j$ 位置可以得到的最大开心值。

然后推方程：$f[i][j]=\max(f[i-1][k]+b[i]-|a[i]-j|),k \in [j-d*(t[i]-t[i-1]),j+d*(t[i]-t[i-1])]$，应该不难想吧。

根据转移方程，我们要开 $f[300][150000]$ 的数组，时间复杂度 $O(mn^2)$，并且：

```cpp
int 一时爽，溢出火葬场！
```

TLE&MLE 警告。。。。。。

所以，我们要优化时空。

## 进一步优化：

1. 想想学背包时，我们将方程从 $f[i][j]$ 压为 $f[j]$ 是因为不需要存下那么多的 $f[i][j]$ 。同理，这里我们只需要开 $f[2][150000]$ ，然后滚动压缩即可。MLE 解决。
2. 这里是一个小技巧：观察到无论怎么算，总是要求出 $b_i$ 的和，那么不如让 $f[0/1][j]$ 计算 $|a_i-x|$ 的最小值，将方程变成 $f[fir][j]=\min(f[sec][k])+|a[i]-j|$，其中 $fir=i\&1,sec=fir \oplus 1$
3. 再一次观察上面的方程，发现 $k \in [j-d*(t[i]-t[i-1]),j+d*(t[i]-t[i-1])]$ ,**是一个固定区间！** 固定区间求最小值，各位能想到什么？单调队列。因此，我们使用单调队列从 1 到 $n$ 维护一遍区间长度为 $d*(t[i]-t[i-1])$ 的最小值，再使用单调队列从 $n$ 到 1 维护一遍区间长度为 $d*(t[i]-t[i-1])$ 的最小值，一边维护一遍更新即可。时间复杂度优化到 $O(nm)$ ，TLE 解决。

## 代码：

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN=150000+10,MAXM=300+10;
int n,m,d,a[MAXM],b[MAXM],t[MAXM],q[MAXN],l,r;
typedef long long LL;
LL f[2][MAXN],sum=0;

int read()
{
	int sum=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') {sum=(sum<<3)+(sum<<1)+ch-'0';ch=getchar();}
	return sum;
}

int main()
{
	n=read();m=read();d=read();
	for(int i=1;i<=m;i++)
	{
		a[i]=read();b[i]=read();t[i]=read();
		sum+=(LL)b[i];
	}
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++) f[1][i]=(LL)abs(a[1]-i);
	for(int i=2;i<=m;i++)
	{
		int fir=i&1,sec=i&1^1;
		LL delta_d=(LL)(t[i]-t[i-1])*d;
		l=1,r=0;
		memset(f[fir],0x3f,sizeof(f[fir]));
		for(int j=1;j<=n;j++)
		{
			while(l<=r&&(LL)j-q[l]>delta_d) l++;
			while(l<=r&&f[sec][q[r]]>=f[sec][j]) r--;
			q[++r]=j;
			f[fir][j]=min(f[fir][j],f[sec][q[l]]+(LL)abs(a[i]-j));
		}
		l=1,r=0;
		for(int j=n;j>=1;j--)
		{
			while(l<=r&&(LL)q[l]-j>delta_d) l++;
			while(l<=r&&f[sec][q[r]]>=f[sec][j]) r--;
			q[++r]=j;
			f[fir][j]=min(f[fir][j],f[sec][q[l]]+(LL)abs(a[i]-j));
		}
	}
	int fir=m&1;
	LL ans=0x7f7f7f7f7f7f7f7f;
	for(int i=1;i<=n;i++) ans=min(ans,f[fir][i]);
	cout<<sum-ans<<"\n";
	return 0;
}
```

## 总结：

对于此类动态规划，一种方法就是：

1. 写出最初始的转移方程
2. 一步一步优化，联系平时所学。
3. 最后写出最后的转移方程。

---

## 作者：lotus_grow (赞：4)

[![image.png](https://s22.postimg.cc/muff0orox/image.png)](https://postimg.cc/image/7ygvt3ga5/)

设 $f[i][j]$ 表示在位置 $j$ ，正在放第 $i$ 个烟花的 $happiness$ 的最大值。

根据题意，容易写出 dp 方程：

$f [ i ][ j ] = max$ { $f [ i ][ j ] , f [ i - 1 ][ k ] + b [ i ] - | a [ i ] - j |$ }$

如果 $ k <= j $,则$ j - ( t [ i ] - t [ i - 1 ] ) * d <= k <= j$;

如果 $ k >= j $ ,则$ j  <= k <= j + ( t [ i ] - t [ i - 1 ] ) * d$;

进一步观察式子得到

1. dp 方程中的 $b [ i ]$ 可以放到大括号外，即 $f [ i ][ j ]$ 维护在位置 $j$ ，正在放第 $i$ 个烟花的 $happiness$ 的最大值减去 $b [ i ]$。又因为 $f [ 0 ][ j ]$ 全部等于 $0$ ，$f [ i ][ j ]$ 维护所有 $- | a [ i ] - j |$ 的最大值，即 $| a [ i ] - j |$ 的最小值

1.  如果做过**滑动窗口 ( sliding windows )** 这道题，那么看到 k 的取值范围，马上会想到**滑动窗口**的做法——用单调队列维护 $f [ i - 1 ][ k ]$ 在取值范围内的最小值。

1. 因为 dp 方程中 $i$ 这一维只与 $i-1$ 有关，所以可以用滚动数组**（不用会 $MLE$ ）**

最后 $ans=Σb[i]-min${$f[m][j]$} $(i=1$  $to$  $m,j=1$  $to$  $n)$


代码
```cpp
#include<cstdio>
#include<algorithm>

using namespace std;
typedef long long ll;

ll f[2][150001],ans,s;
int n,m,d,p;
int a,b,t[2],q[150001];

int main()
{
	scanf("%d%d%d",&n,&m,&d);
	p=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&t[p^1]);
		s+=b;
		ll time=(ll)(t[p^1]-t[p])*d;
		int l=1,r=0;
		for(int j=1;j<=n;j++)
		{
			while(l<=r && q[l]<j-time) l++;
			while(l<=r && f[p][q[r]]>f[p][j]) r--;
			q[++r]=j;
			f[p^1][j]=f[p][q[l]]+abs(a-j);
		}
		l=1,r=0;
		for(int j=n;j>0;j--)
		{
			while(l<=r && q[l]>j+time) l++;
			while(l<=r && f[p][q[r]]>f[p][j]) r--;
			q[++r]=j;
			f[p^1][j]=min(f[p^1][j],f[p][q[l]]+abs(a-j));
		}
		p^=1;
	}
	ans=1e18;
	for(int i=1;i<=n;i++)
	ans=min(ans,f[p][i]);
	printf("%lld\n",s-ans);
	return 0;
}

```

---

## 作者：Leap_Frog (赞：3)

### P.S.
数据结构学傻人前来写题解。  
要是没场的 div1C 都有这么简单就好了！
### Description.
每单位时间，可以从 $i$ 到 $[i-d,i+d]$。  
第 $i$ 次烟花在 $t_i$ 时发生。  
如果你在位置 $x$ 那么你会获得 $b_i-|a_i-x|$ 的价值。  
最大化价值。  
### Solution.
设 $dp_{i,j}$ 表示当前在第 $i$ 时刻，位置在 $j$ 的最大收益。  
那么显然有 $dp_{i,j}\leftarrow dp_{i-1,k}\quad (k\in[j-(t_i-t_{i-1})\times d,j+(t_i-t_{i-1})\times d])$。  
那么我们只需要暴力 dp，每次加上 当前这次烟花的价值就好了。  
转移直接用一棵区间求最值的线段树就可以计算了。  

Q : MLE 了怎么办？  
A : 第一维可以滚动数组优化，$O(n\times m)\rightarrow O(n)$

~~然后就做完了，完结撒花~~  

桥豆麻袋！$O(n\times m\times\log n)$ 会 TLE on test 33。  
主要我们需要优化掉那一只 $\log$。  
我们观察，同一层每次转移所属区间长度都是一样的。  
相当于左端点和右端点每次右移一格。  
我们想到了什么，滑动窗口，好，完结撒花。  
直接套上一个单调队列就 $O(n\times m\times\log n)\rightarrow O(n\times m)$。  
### Coding.
[代码链接](https://codeforces.com/contest/372/submission/111425899)

---

## 作者：EricQian (赞：3)

[$\leftarrow$ 我的单调队列优化 DP 专题](https://www.luogu.com.cn/blog/EricQian/dan-diao-dui-lie-you-hua-dp)

[CF372C Watching Fireworks is Fun](https://www.luogu.com.cn/problem/CF372C)

状态：设 $dp[i][j]$ 表示在放第 $i$ 个烟花的时候，在第 $j$ 个位置的最大快乐值 。

转移方程：

$$j-(t[i]-t[i-1])\times d\le k\le j+(t[i]-t[i-1])\times d$$

$$dp[i][j]=\max{\{dp[i-1][k]+b[i]-\operatorname{abs}(a[i]-j)\}}$$

将转移方程变形：

$$dp[i][j]=b[i]-\operatorname{abs}(a[i]-j)+\max{\{dp[i-1][k]\}}$$

一看到上面这个方程，一眼就会想到 **单调队列优化$\operatorname{DP}$** ！

可以用一个单调队列维护 $dp[i-1][j-(t[i]-t[i-1]),j+(t[i]-t[i-1])]$ 的最大值，转移到 $dp[i][j]$ ，转移均摊 $O(1)$ 。

复杂度：$O(nm)$ 。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define infll 0x7f7f7f7f7f7f7f7f
#define inf 0x7f7f7f7f
#define Maxn 150005
#define Maxm 305 
typedef long long ll;
inline ll rd()
{
	 ll x=0;
     char ch,t=0;
     while(!isdigit(ch = getchar())) t|=ch=='-';
     while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
     return x=t?-x:x;
}
ll maxll(ll x,ll y){ return x>y?x:y; }
ll minll(ll x,ll y){ return x<y?x:y; }
ll absll(ll x){ return x>0ll?x:-x; }
ll n,m,d,l,r,pos,que[Maxn];
ll p,ans=-infll,a[Maxm],b[Maxm],t[Maxm],f[Maxn],g[Maxn];
int main()
{
     //freopen(".in","r",stdin);
     //freopen(".out","w",stdout);
	 n=rd(),m=rd(),d=rd();
	 for(ll i=1;i<=m;i++) a[i]=rd(),b[i]=rd(),t[i]=rd();
	 for(ll i=1;i<=m;i++)
	 {
	 	 l=1,r=0,pos=1,p=(t[i]-t[i-1])*d;
	 	 for(ll j=1;j<=n;j++)
	 	 {
	 	 	 for(;pos<=minll(n,j+p);pos++)
	 	 	 {
	 	 	 	 while(l<=r && g[que[r]]<=g[pos]) r--;
	 	 	 	 que[++r]=pos;
			 }
			 while(l<=r && que[l]<j-p) l++;
			 f[j]=g[que[l]]+b[i]-absll(a[i]-j);
		 }
		 memcpy(g,f,sizeof(f));
	 }
	 for(ll i=1;i<=n;i++) ans=maxll(ans,f[i]);
	 printf("%lld\n",ans);
     //fclose(stdin);
     //fclose(stdout);
     return 0;
}
```

---

## 作者：Rossie65536 (赞：3)

[更好的阅读方式](https://www.cnblogs.com/ASTiKi/p/12285911.html)
## 题目大意
城镇中有$n$个位置，有$m$个烟花要放。第$i$个烟花放出的时间记为$t_{i}$，放出的位置记为$a_{i}$。如果烟花放出的时候，你处在位置$x$，那么你将收获$b_{i}- \left | a_{i}-x \right |$点快乐值。 

初始你可在任意位置，你每个单位时间可以移动不大于$d$个单位距离。现在你需要最大化你能获得的快乐值。 

## 思路：DP+单调队列+滚动数组
有一个显然的动态转移方程：

$f_{i,j}=max \left (f_{i,j},f_{i-1,k}+b_{i}- \left |a_{i}-j \right | \right )$

$f_{i,j}$表示在位置$j$放第$i$个烟花获得的最大值。

则$ans=max_{i=1}^{n}f_{m, i}$。

观察方程，可以看出$b_{i}$可以提出来，而$- \left |a_{i}-j \right |$的值在计算的过程中也是确定的，也可提出来。

最后的式子长这个样子

$f_{i,j}=min \left (f_{i,j},f_{i-1,k} \right )$

$ans=sum_{i=1}^{m}b_{i}-min_{i=1}^{n}f_{m, i}$

感觉可以，一看复杂度$O \left ( n^{2}m \right )$，T到飞起。

从上式中，可以看出$k$的范围是

$j- \left ( t_{i}-t_{i-1} \right ) *d \leq k \leq j+ \left ( t_{i}-t_{i-1} \right ) *d$

如何维护$k$的值？很明显，用单调队列维护，使得其能在均摊$0 \left (1 \right )$的时间复杂度内计算出$min \left (f_{i,j},f_{i-1,k} \right )$。

于是复杂度从$O \left ( n^{2}m \right )$降到了$O \left ( nm \right )$。

一看范围，150000。。。直接爆炸。

仔细观察，发现可以用滚动数组优化空间，能过。

## 代码
```cpp
#include <iostream>

#define RI register int
typedef long long ll;
const int N = 150001;

using namespace std;

template <class T>
inline void read(T &x) {
    T f = 1; x = 0; char c = getchar();
    while(c > '9' || c < '0') {
        if(c == '-')
            f = -f;
        c = getchar();
    }
    while(c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    x *= f;
}

int n, m, d, t[2];
ll f[2][N], ans = 1e18 + 7, sum;
int l, r, q[N];
int p;

inline int abs(int x) {
    return x > 0 ? x : -x;
}

inline ll min(ll x, ll y) {
    return x > y ? y : x;
}

int main() {
    read(n), read(m), read(d);
    for(RI i = 1; i <= m; i++) {
        int a, b;
        read(a), read(b), read(t[p ^ 1]);
        sum += b;
        ll len = ll(t[p ^ 1] - t[p]) * d;
        l = 1, r = 0;
        for(RI j = 1; j <= n; j++) {
            while(l <= r && q[l] < j - len)
                l++;
            while(l <= r && f[p][q[r]] > f[p][j])
                r--;
            q[++r] = j;
            f[p ^ 1][j] = f[p][q[l]] + abs(a - j);
        }
        l = 1, r = 0;
        for(RI j = n; j >= 1; j--) {
            while(l <= r && q[l] > j + len)
                l++;
            while(l <= r && f[p][q[r]] > f[p][j])
                r--;
            q[++r] = j;
            f[p ^ 1][j] = min(f[p][q[l]] + abs(a - j), f[p ^ 1][j]);
        }
        p ^= 1;
    }
    for(RI i = 1; i <= n; i++)
        ans = min(ans, f[p][i]);
    printf("%lld\n", sum - ans);
    return 0;
}
```

---

## 作者：Jayun (赞：1)

# Watching Fireworks is Fun

## 链接：

[洛谷](https://www.luogu.com.cn/problem/CF372C)

[博客园](https://www.cnblogs.com/GJY-JURUO/p/15114916.html)

## 题目大意：

一个城镇有 $n$ 个区域，从左到右 $1$ 编号为 $n$，每个区域之间距离 $1$ 个单位距离。节日中有 $m$ 个烟火要放，给定放的地点 $a_i$，时间 $t_i$，如果你当时在区域 $x$，那么你可以获得 $b_i - \vert a_i - x\vert$ 的开心值。你每个单位时间可以移动不超过 $d$ 个单位距离。你的初始位置是任意的（初始时刻为 $1$），求你通过移动能获取到的最大的开心值。

## 正文：

考虑 DP，设 $f_{i,j}$ 表示当前放第 $i$ 个烟花且在位置 $j$ 时的最大开心值。则有：

$$f_{i,j}=\max_{k,|j-k|\leq(t_i-t_{i-1})d}\left\{f_{i-1,k}+b_i-|a_i-j|\right\}$$

考虑到可以将 $b_i$ 提出，得到：

$$f_{i,j}=\max_{k,|j-k|\leq(t_i-t_{i-1})d}\left\{f_{i-1,k}-|a_i-j|\right\}$$

我们可以用单调队列优化上面的式子。

最后答案为：

$$\sum_{i=1}^m b_i + \max_{i=1}^n\{f_{m,i}\}$$

但是空间复杂度 $\mathcal{O}(nm)$，用滚动数组优化至 $\mathcal{O}(n)$ 即可。

## 代码：

```
const int N = 150010, M = 310;

inline ll Read()
{
	ll x = 0, f = 1;
	char c = getchar();
	while (c != '-' && (c < '0' || c > '9')) c = getchar();
	if (c == '-') f = -f, c = getchar();
	while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
	return x * f;
}

int n, m, d; 
ll f[2][N];
struct node
{
	int a, t;
}a[M];
deque <int> q;
ll sum, ans = -(1ll << 60);

int main()
{
	n = Read(), m = Read(), d = Read();
	for (int i = 1; i <= m; i++)
		a[i].a = Read(), sum += Read(), a[i].t = Read();
	for (int i = 1; i <= m; i++)
	{
		ll len = (ll)(a[i].t - a[i - 1].t) * d;
		for (; !q.empty(); q.pop_back());
		for (int j = 1; j <= n; j++)
		{
			for (; !q.empty() && q.front() < j - len; q.pop_front());
			for (; !q.empty() && f[i & 1 ^ 1][j] > f[i & 1 ^ 1][q.back()]; q.pop_back());
			q.push_back(j);
			f[i & 1][j] = f[i & 1 ^ 1][q.front()] - abs(a[i].a - j);
		}
		
		for (; !q.empty(); q.pop_back());
		for (int j = n; j >= 1; j--)
		{
			for (; !q.empty() && q.front() > j + len; q.pop_front());
			for (; !q.empty() && f[i & 1 ^ 1][j] > f[i & 1 ^ 1][q.back()]; q.pop_back());
			q.push_back(j);
			f[i & 1][j] = max(f[i & 1][j], f[i & 1 ^ 1][q.front()] - abs(a[i].a - j));
		}
	}
	
	for (int i = 1; i <= n; i++)
		ans = max(ans, f[m & 1][i]);
	ans = sum + ans;
	printf ("%lld", ans);
	return 0;
}
```

---

## 作者：破忆 (赞：1)

## 【题意】
$m$个烟火将在在$n$个区域依次释放

当烟火$i$释放时，若你在位置$j$，你将得到$b[i]-|a[i]-j|$的收益

你每个时刻可以移动$d$的距离

求最大的收益
## 【分析】
很显然这是一道**DP**题

$f[i][j]$表示第$i$个烟花释放时你在位置$j$的最大收益

$f[i][j]=\min(f[i-1][k])+b[i]-|a[i]-j|$

复杂度$m * n^2$

考虑把$k$这层循环优化下来

由于是在静态区间多次询问最小值，可以使用**单调序列**优化

$f$数组有两维，空间达到了343M，需要滚动优化空间

另外还有一些细节需要注意，在代码中进行补充

## 【算法】

DP+单调序列
## 【代码】
```cpp
#include<bits/stdc++.h>
#define LL long long//都开longlong
using namespace std;
const int maxn=1.5e5+5,maxm=305;
const LL INF=1ll<<62;
int n,m;
LL f[2][maxn],ans=-INF;
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
LL a[maxn],b[maxn],t[maxn],d;
int que[maxn];
int main(){
	freopen("CF372C.in","r",stdin);
	freopen("CF372C.out","w",stdout);
	n=read(),m=read(),d=read();
	for(int i=1;i<=m;i++) a[i]=read(),b[i]=read(),t[i]=read();
	f[0][0]=f[1][0]=-INF;//初始时til指针是0，会调用到这两个元素，设为无穷小以避免影响
	for(int i=1;i<=m;i++){
		int hed=1,til=0;
		if(t[i]==t[i-1]){
			for(int j=1;j<=n;j++) f[i&1][j]=f[1-i&1][j]+b[i]-abs(a[i]-j);//相同时间直接更新
			continue;
		}
		LL r=1;
		for(int j=1;j<=n;j++){
			while(r<=n&&r<=d*(t[i]-t[i-1])+j){//两数相乘要开longlong
				while(f[1-i&1][que[til]]<=f[1-i&1][r]&&til>=hed) til--;
				que[++til]=r;
				r++;
			}
			while(que[hed]+d*(t[i]-t[i-1])<j&&hed<=til) hed++;
			f[i&1][j]=f[1-i&1][que[hed]];
		}
		for(int j=1;j<=n;j++) f[i&1][j]+=b[i]-abs(a[i]-j);
	}
	
	for(int i=1;i<=n;i++) ans=max(ans,f[m&1][i]); 
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：piao_A_piao (赞：1)

## dp（单调队列+滚动数组优化）

------------
很明显是一道dp题，很容易得出状态转移方程：dp[i][j]=max(dp[i-1][k]+b[i]-|a[i]-j|)

dp第一维表示当前放到第几个烟花了，第二维表示当前位置在哪里，所以j的取值范围为
两次烟花时间之差乘上单位时间的路程，即：

l<=k<=r (1<=l<=j-(t[i]-t[i-1])·d&&j+(t[i]-t[i-1])·d<=k<=n)

由于这样算会超时（m·n ^ 2），所以考虑优化

由于每个i所对应的b都会累加到答案中，所以可以先累加入答案中

方程便剩下：dp[i][j]=max(dp[i-1][k]-|a[i]-j|)

将绝对值前的负号取正：dp[i][j]=min(dp[i-1][k]+|a[i]-j|)

于是可以利用单调队列对j对应的所有k快速算最值：维护一个递增序列，对于每一个j先筛除不在范围内的head，再加入当前新的dp[...][r]（与滑动窗口原理相似）

外加滚动数组优化


------------
```
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define ll long long
#define N 150100
using namespace std;

int n,m,d,head,tail;
ll ans1,ans2;
ll dp[2][N];

struct node
{
	int num;
	int val;
}q[N];

struct fire
{
	int a;
	int b;
	int t;
}fi[N];

int main()
{
	while(~scanf("%d%d%d",&n,&m,&d))
	{
		ans1=0;
		for(int i=1;i<=m;i++) scanf("%d%d%d",&fi[i].a,&fi[i].b,&fi[i].t),ans1+=fi[i].b;
		for(int i=1;i<=n;i++) dp[0][i]=abs(fi[1].a-i);
		ll k;
		int now=0;
		for(int j=2;j<=m;j++)
		{
			k=1ll*(fi[j].t-fi[j-1].t)*d;
			if(k>n) k=n;
			head=tail=0;
			for(int i=1;i<=k;i++)//初始化位置为1时可选位置
			{
				while(head<tail&&dp[now][i]<q[tail-1].val) tail--;
				q[tail].val=dp[now][i],q[tail++].num=i;
			}
			for(int i=1;i<=n;i++)
			{
				int l,r;
				l=i-k,r=i+k;
				if(l<=0) l=1;
				while(head<tail&&q[head].num<l) head++;
				if(r<=n)
				{
					while(head<tail&&dp[now][r]<q[tail-1].val) tail--;
					q[tail].val=dp[now][r],q[tail++].num=r;
				}
				dp[1-now][i]=q[head].val+abs(fi[j].a-i);
			}
			now=1-now;
		}
		ans2=1e15;
		for(int i=1;i<=n;i++) ans2=min(ans2,dp[now][i]);
		cout<<ans1-ans2<<endl;
	}
	return 0;
}
```


---

