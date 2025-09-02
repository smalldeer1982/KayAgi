# [CERC2014] Can't stop playing

## 题目描述

有些计算机游戏非常有趣，这个问题可能就是关于其中之一。你得到了一系列一维的方块，每个方块的长度都是 2 的幂。游戏的目标是将所有方块合并成一个大方块。方块一个接一个地呈现，对于每一个方块，你必须决定是立即粘在前一个方块的左边还是右边。

每当两个相同大小的方块相邻时，它们会合并成一个长度是它们各自两倍的方块。注意，只要可能，生成的方块会立即与相邻的方块合并。例如，如果当前的方块序列是 $2, 4, 16$，那么将 $2$ 粘在左边会导致 $8, 16$，而粘在右边则会得到 $2, 4, 16, 2$。注意，在任何时刻最多只有一对可合并的方块。

你又一次输了游戏，并且想知道是否有任何方法可以赢。分析序列以找出答案。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3
9
2 8 4 1 1 4 4 4 4
5
2 16 4 8 2
3
2 2 2```

### 输出

```
rrrlllrrr
no
no```

# 题解

## 作者：DeepSeaSpray (赞：3)

原题目资料连接：[Link](https://cerc.tcs.uj.edu.pl/2014/data.html)。

首先合并肯定是越合越大的，又我们在两头加数，所以一个可行的队列总是单峰的。

> 形式话的说：
> 
> $a_1 < a_2 < \dots < a_K$
> 
> $a_K > a_{K-1} > \dots > a_n$

那么我们考虑如何表示它。

对于序列的左边，注意到它是递增的，再根据相同项合并的规则，以及 $a_i = 2^p$，我们会发现它是序列总和的二进制拆分。

> 更具体的，其类似于 `2 8 16 32` 的形式。

对于序列的右边也是这样的。

而总和是我们知道的，所以我们只需要左边序列的和即可表示这样一个单峰的合法序列。

故可以动态规划，设 $f(i,s)$ 表示考虑到第 $i$ 位，左侧序列为 $s$ 是否可以被操作构造出来。

那么我们每次加入一个数 $a_i$，其能加入左侧序列 $s$ 当且仅当满足下列两个条件之一（$\operatorname{lowbit}$ 表示二进制最低位）：

- $s = 0$
- $a_i \leq \operatorname{lowbit}(s)$

对于右侧序列 $(\sum_{j=1}^i a_i) - s$ 同理。

通过上述方式转移完之后，我们还需要判断一些情况。

首先对于“峰”即上文所说 $a_K$ 其可以属于左或右两边，需要处理。

同时两边序列的最高点有可能相同，我们需要判断然后合并。

答案 $f(n,\sum a)$。

对于”峰“，实现中我们可以预处理一个数的二进制最高位来解决。

同时还需要记录转移点和插入在左还是右两个信息，方便最后用递归找答案。

记得判断 $\sum a_i$ 是否是 $2$ 的幂。

时间复杂度 $O(n \sum a_i)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3;
const int maxs=1<<13;
int n;
int a[maxn+5],sum;
bool f[maxn+5][maxs+5];
char g[maxn+5][maxs+5];
int to[maxn+5][maxs+5];
int h[maxs+5];
char str[maxn+5];
inline int Lowbit(int x){return x&(-x);}
inline bool Check(int x,int s){
    return (s==0)||(x<=Lowbit(s));
}
void Print(int i,int s){
    if(i){
        if(g[i][s]) str[i]=g[i][s],Print(i-1,to[i][s]);
        else str[i]=g[i][s],Print(i-1,to[i][s]);
    }
}
inline void Solve(){
    scanf("%d",&n);
    sum=0;
    f[0][0]=1;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum+=a[i];
        for(int s=0;s<=sum;s++) f[i][s]=0;
    }
    sum=0;
    for(int i=1;i<=n;i++){
        for(int s=0;s<=sum;s++){
            if(!f[i-1][s]) continue;
            if(Check(a[i],s)){
                f[i][s+a[i]]=1;
                g[i][s+a[i]]='l';
                to[i][s+a[i]]=s;
            }
            if(Check(a[i],sum-s)){
                f[i][s]=1;
                g[i][s]='r';
                to[i][s]=s;
            }
        }
        sum+=a[i];
        for(int s=0;s<=sum;s++){
            if(!f[i][s]) continue;
            if(h[s]<h[sum-s]){
                f[i][s+h[sum-s]]=1;
                g[i][s+h[sum-s]]=g[i][s];
                to[i][s+h[sum-s]]=to[i][s];
            }
            if(h[s]>h[sum-s]){
                f[i][s-h[s]]=1;
                g[i][s-h[s]]=g[i][s];
                to[i][s-h[s]]=to[i][s];
            }
            if(h[s]==h[sum-s]){
                f[i][s]=0;
                f[i][s+h[s]]=1;
                f[i][s-h[s]]=1;
                g[i][s+h[s]]=g[i][s];
                g[i][s-h[s]]=g[i][s];
                to[i][s+h[s]]=to[i][s];
                to[i][s-h[s]]=to[i][s];
            }
        }
    }
    int tmp;for(tmp=sum;!(tmp&1);tmp>>=1);
    if(tmp==1&&f[n][sum]){
        Print(n,sum);
        for(int i=1;i<=n;i++) putchar(str[i]);
        putchar('\n');
    }
    else puts("no");
}
inline void Init(){
    for(int s=0;s<=maxs;s++){
        if(Lowbit(s)==s) h[s]=s;
        else h[s]=h[s>>1]<<1;
    }
}
signed main(){
    Init();
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
```

---

## 作者：wgyhm (赞：3)

## Description

https://www.luogu.com.cn/problem/P7093

## Solution

什么题目都要调一年了。

发现每个数只会变大不能变小，所以如果一个数两边都比自己大，就不行了。

有了这个结论以后，也就是序列时刻会保持一个先增后减的单峰型。如果我们要全维护要 $2^{26}$ 个状态。

但是发现对于其中的一边，每个数各不相同，两边的数之和又是序列的前缀和。考虑只维护一边，把当前序列的最大值钦定在左边即可。

状态 $2^{13}$，复杂度 $O(T\sum n2^{13})$，使用记忆化搜索，记录转移点输出方案。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define maxn 1005
#define put() putchar('\n')
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;
Tp void read(T &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod=1e9+7;
int power(int x,int y=mod-2) {
	int sum=1;
	while (y) {
		if (y&1) sum=sum*x%mod;
		x=x*x%mod;y>>=1;
	}
	return sum;
}
----------------template------------------
#define lowbit(x) ((x)&(-(x)))
int n,a[maxn],suf[maxn],b[maxn];
int f[1005][(1<<14)+5],nex[1005][(1<<14)+5],h[(1<<14)+5];
bool dfs(int now,int stat) {
	int i,tmp1=-1,tmp2=-1,s=suf[now-1]-stat;
	tmp1=h[stat],tmp2=h[s];
	if (tmp1==tmp2&&tmp1>=0) stat+=(1<<tmp1);
	else if (tmp1<tmp2) stat+=(1<<tmp2);
	if (now==n+1) {
		if ((stat==0)||(stat==suf[n])||stat==suf[n]-stat) return 1;
		else return 0;
	}
	if (f[now][stat]!=-1) return f[now][stat];
	int res=0;f[now][stat]=0;
	if (a[now]<=lowbit(stat)||stat==0) {
		res=dfs(now+1,stat+a[now]);
		if (res) f[now][stat]=1,nex[now][stat]=0;
	}
	s=suf[now-1]-stat;
	if (a[now]<=lowbit(s)||s==0) {
		res=dfs(now+1,stat);
		if (res&&!f[now][stat]) f[now][stat]=1,nex[now][stat]=1;
	}
	return f[now][stat];
}
void print(int now,int stat) {
	int i,tmp1=-1,tmp2=-1,s=suf[now-1]-stat;
	tmp1=h[stat],tmp2=h[s];
	if (tmp1==tmp2&&tmp1>=0) stat+=(1<<tmp1);
	else if (tmp1<tmp2) stat+=(1<<tmp2);
	if (now==n+1) return ;
	putchar(nex[now][stat]?'r':'l');
	print(now+1,nex[now][stat]?stat:stat+a[now]);
}
void solve(void) {
	int i,j;
	read(n);
	for (i=1;i<=n;i++) read(a[i]),suf[i]=suf[i-1]+a[i],b[i]=__builtin_popcount(a[i]);
	if (suf[n]!=lowbit(suf[n])) return puts("no"),void();
	for (i=0;i<=n;i++) for (j=0;j<=suf[n];j++) f[i][j]=-1;
	if (!dfs(1,0)) return puts("no"),void();
	else {
		print(1,0);put();
	}
}
signed main(void){
	int T,i,j;
	h[0]=-1;
	for (i=1;i<=(1<<14);i++) {
		for (j=0;j<=14;j++) if ((i>>j)&1) h[i]=j;
	}
	read(T);
	while (T--) solve();
	return 0;
}
```



---

## 作者：Youth518 (赞：3)

### 分析：

DP

来贡献一发最劣解的做法

* 暴力

我们发现由于**长度之和不超过$2^{13}$** ，所以放进去的块可以用一个不超过 $2^{14}$ 的数字状压出来，其次我们手玩样例会发现一个性质，就是过程中拼出来的序列满足大小形状类似倒放的 **V**

证明：若存在 $a>b<c$ ，那么 $b$ 没有办法和任何一个块消掉

所以我们把序列拆成左右两个单调的序列，然后每次判断一下能不能并到左边或者右边，只要满足以下任何一个条件即可：

1. 左序列或者右序列为空
2. 小于左序列或者右序列的最小值

然后我们就得到了一个 $O(tn2^{26}\times13)$ 的做法

* 优化

我们发现左右序列的和值固定，所以只需要枚举左序列的状态就可以了，复杂度降低为 $O(tn2^{13}\times 13)$ ,但是由于直接枚举是跑满的，所以会 **TLE** 的

* 正解

我们发现状态转移是固定的，所以不需要枚举状态，直接 DFS 就可以了，并且预处理一下 **highbit** ，复杂度就变成了常数极小的 $O(tn2^{13})$

**tip:**

1. 可能存在一种情况就是，左右序列都单调递增，所以转移的时候每次记得把左右序列相连的部分能合并就合并，不然会像我一样直接白给好多发

    比如 2|2 的情况添加一个 4，原本是添加不进去的，但先合并之后变成 4|0，然后就可以添加进去了

2. 记忆化一下，保证复杂度正确

### 代码：

~~~cpp
#include<bits/stdc++.h>
#define inl inline
#define reg register
#define mk(x,y) make_pair(x,y)
#define fir first
#define sec second

using namespace std;

namespace zzc
{
    typedef long long ll;
    inl ll read()
    {
        ll x=0,f=1;char ch=getchar();
        while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
        while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
        return x*f;
    }

    const ll maxn = 1005;
    const ll maxm = (1<<14);
    ll n,t;
    bool vis[maxn][maxm],ans[maxn];
    ll sum[maxn],a[maxn],hig[maxm];

    inl ll merge(ll x,ll y,ll k)//表示将 k 加到 x 序列上 
    {
        if(hig[x]>hig[y])//先将x序列最大值并到y序列上， 参考 tip:1 
        {
        	ll tmp=hig[x];
        	x-=tmp;
        	y+=tmp;
        }
        if(x&&(x&(-x))<k) return -1;x+=k;
        if(hig[x]==hig[y])//合并两个序列相连的部分 
        {
        	ll tmp=hig[x];
        	x+=tmp;
        	y-=tmp;
        }
        return x;
    }
    
	bool dfs(ll pos,ll lef)
	{
		ll rig,now;
		rig=sum[pos]-lef;
        if(pos==n)
        {
        	//将左右序列合并化到最简 
        	lef=merge(lef,rig,0);
        	rig=sum[pos]-lef;
        	if(lef==sum[n]&&(lef&(lef&(-lef)))==lef) return true;
        	if(rig==sum[n]&&(rig&(rig&(-rig)))==rig) return true;
        	return false;
        }
        if(vis[pos][lef]) return false;
        vis[pos][lef]=true;
        
        now=merge(lef,rig,a[pos+1]);
        if(now!=-1&&dfs(pos+1,now)) 
        {
            ans[pos+1]=true;
            return true;
        }
        
        now=merge(rig,lef,a[pos+1]);
        if(now!=-1&&dfs(pos+1,sum[pos+1]-now))
        {
            ans[pos+1]=false;
           	return true;
        }
        
        return false;
	}
	
	void init()
	{
		for(reg ll i=1;i<(1<<14);i++)// 预处理 highbit 
		{
			if((i&(-i))==i) hig[i]=i;
			else hig[i]=hig[i-1];
		}
	}
	
    void work()
    {
    	init();
        t=read();
        while(t--)
        {
    	     memset(vis,false,sizeof(vis));
             memset(ans,false,sizeof(ans));
             n=read();
             for(reg ll i=1;i<=n;i++) a[i]=read(),sum[i]=sum[i-1]+a[i];
             if(!dfs(0,0)) printf("no");
             else for(reg ll i=1;i<=n;i++) printf("%c",(ans[i]?'l':'r'));
             puts("");
        }
    }

}

int main()
{
    zzc::work();
    return 0;
}
~~~



---

## 作者：Planetary_system (赞：2)

## 题面解释：
$n$ 个数依次加入 $1$ 个双端队列，相同数可以合并变为原来的两倍，求使双端队列中最后只有 $1$ 个数的方案。

## 思路分析：
首先有 $1$ 个显然的性质：数加进去之后只能变大不能变小，我们需要达到 $1$ 个状态使所有数合并，所以双端队列中必须保持先递增后递减。

一开始我想要倒着做，但是失败了，似乎很困难（可能只是我太菜了）。

考虑进行 `dp`。状态最开始有可能会想成记录双端队列的端点，即最小值，但这样似乎不可取，因为你无法知道合并后的情况。那我们重新设计，由于全为 $2$ 的幂，不难想到二进制，类似状压的思想吧。我们定义 $dp_{i,j}$ 为第 $i$ 个数加进去之后左半边和为 $j$ 是否可能，那么右半边的和用总和减一下就好了，这样设计的前提是转移时始终保证队列中的最大值为左半边的结尾。

特殊情况：若总和不为 $2$ 的幂，一定无解。

那么端点显然就是 `lowbit`。转移是显然的，注意不要忘记如果往右边加要保证峰值在左边。关于答案，记录转移路径即可。

这里讲一下卡了我很久的一个点QWQ，就是 `memset` 不要全局进行，用到哪就覆盖到哪即可（不然可能会 `TLE` 哦）。
## AC Code:
当前最优解代码，这里只展示核心代码了（代码中 `lbt` 表示 `lowbit`，$h_i$ 表示 `highbit`）。
```cpp
inline void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i],s[i]=s[i-1]+a[i];
	if(s[n]!=lbt(s[n])){cout<<"no\n";return;}
	for(int i=1;i<=n;i++){
		memset(dp[i],0,s[i]+10);
		for(int j=0;j<=s[i-1];j++){
			if(!dp[i-1][j])continue;
			if(j==0||a[i]<=lbt(j))
				dp[i][j+a[i]]=1,
				from[i][j+a[i]]={j,'l'};
			int delt=(h[j]<=h[s[i-1]-j+a[i]])*h[s[i-1]-j+a[i]];
			if(j==s[i-1]||a[i]<=lbt(s[i-1]-j))
				dp[i][j+delt]=1,
				from[i][j+delt]={j,'r'};
		}
	}
	if(!dp[n][s[n]])cout<<"no";
	else{
		int p=s[n];
		for(int i=n;i;i--)
			ans[i]=from[i][p].ch,
			p=from[i][p].to;
		for(int i=1;i<=n;i++)
			cout<<ans[i];
	}
	cout<<'\n';
}
```
完结撒花！！！

---

## 作者：__xxy_free_ioi__ (赞：1)

一道非常鬼畜的动态规划题。

为方便表达，做出以下约定：

1. 我们称能够合并成一块的序列为答案序列。
2. $\operatorname{lowbit}(i)$ 表示 $i$ 在二进制下的最低位一的值。

首先，我们发现，合并一定是越合越大的，那么，一个答案序列肯定是先单调递增，再单调递减的。也就是说，答案序列 $a$ 必然满足：

1. $a_1 < a_2 < a_3 < \dots < a_i$
2. $a_i > a_{i+1}> \dots > a_{n-1} > a_n$

所以，我们约定 $a_1,a_2,\dots,a_i$ 为左堆，$a_{i+1},a_{i+2},\dots,a_n$ 为右堆（为啥要将最大的放在左堆，我以后会解释）。

同时，因为所有的数都可以被表示成 $2^p$ 的形式，所以，设左堆的和为 $SL$，右堆的和为 $SR$，那么这个序列的两端就是 $\operatorname{lowbit}(SL)$ 与 $\operatorname{lowbit}(SR)$。而变化只会发生在两端，所以，我们只需要记录两个数：

1. 总和 $SA$。
2. 右堆和 $SR$（因为 $SL=SA-SR$）。

这也是我们使用动态规划的核心思路。

由上文，我们还可以得出三个结论：

1. 若 $a_{n+1}$ 要插入序列 $a$ 的左堆，那么 $SL = 0$ 或者 $a_{n+1} \le \operatorname{lowbit}(SL)$。
2. 若 $a_{n+1}$ 要插入序列 $a$ 的右堆，那么 $SR = 0$ 或者 $a_{n + 1} \le \operatorname{lowbit}(SR)$。
3. 若 $SR + a_{n+1}$ 为 $2^p$ 并且大于左堆最大的那一块，那么将其移至左堆，清空右堆（这样，我们就最后就可以只计算左堆了，会方便很多，这也就是我将最大的那一个块放在左堆的原因）。

综上，令 $f_{i,s}$ 表示当处理到第 $i$ 个块，右堆和为 $s$ 时上一步的右堆的和，$C_{i,s}$ 表示当处理到第 $i$ 个块，右堆和为 $s$ 时第 $i$ 个块是去左堆还是去右堆，然后根据题意一步步模拟即可。

具体看代码吧！


```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define VI vector<int>
#define PII pair<int, int>
#define up(i, s, t) for (int i = s; i <= t; i++)
#define dw(i, s, t) for (int i = s; i >= t; i--)

const int S = 1 << 13, N = 1e3;

int n;
int f[N + 1][S + 1], lp[S + 1], C[N + 1][S + 1]; 
// f[i][s] 处理完i，右堆重s时上一步右堆的重量/lp不超过i的最大2的幂/C记录路径 
// f[i][s] 这样设计是为了方便输出路径 

int LB(int x) { return x & -x; } // low_bit
void init() { up(i, 1, S) lp[i] = (LB(i) == i) ? i : lp[i - LB(i)]; }
void print(int i, int j) { if (i) print(i - 1, f[i][j]), putchar("lr"[C[i][j]]); }
// 向前找路径，一步步递归即可，这里的putchar("lr"[C[i][j]])就相当于s="lr",cout << s[C[i][j]]; 
void solve() {
	f[0][0] = 0;
	int sa = 0; // 总重 s_all 左堆重 sl 右堆重 sr 
	for (int i = 0, a; i < n && cin >> a; i++, sa += a) { // sa 在结束时别忘了加上 a 
		fill(f[i + 1], f[i + 1] + sa + a + 1, -1); // 全部设为不可达
		// 我这里的 DP 写的是扩散型，只不过我太蒟了，不会写收集型。 
		up(sr, 0, sa) if (f[i][sr] != -1) { // 可达，则用 f[i][sr] 向后转移
			int sl = sa - sr;
			if (sl == 0 || a <= LB(sl)) // 可以放左堆 
				f[i + 1][sr] = sr, C[i + 1][sr] = 0; // 放左堆右堆和自然不变，C记录一下 
			if (sr == 0 || a <= LB(sr)) { // 可以放右堆
				int nws = sr + a; // 新的和 
				// 若右堆重量可以合并成2^p且大于左堆的所有块，则一至左堆 
				// 这样，最后直接计算左堆重量即可 
				if (nws == LB(nws) && nws >= lp[sl]) nws = 0; // 特殊处理
				f[i + 1][nws] = sr, C[i + 1][nws] = 1;  // 放右堆和要加上 a，但注意特殊处理 
			}
		} 
	}
	// 根据设计，右堆必然要合并成一块然后转移左堆，否则无解
	// 同样的，若左堆无法表示成2的幂的形式，也无解 
	if (f[n][0] != -1 && sa == LB(sa)) print(n, 0), puts("");
	else puts("no");
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int T;
	cin >> T, init();
	while (T-- && cin >> n) solve();
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

如果当前队列中出现了 $a_{i-1}>a_i<a_{i+1}$，那么 $a_i$ 永远无法合并，不合法。

因此两边都是单增的，可以用二进制数维护他们。

他们和是定值（可以把最大值分派给一个方向），因此只有 $O(\sum a_i)$ 种方案。暴力 $\rm DP$ 即可。

哥们清空清错了，成为了小丑。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1000+10,MAXM=10000+10;
int T,n,c,a[MAXN],pre[MAXN],lst[MAXN][MAXM],hb[MAXM];
bool dp[MAXN][MAXM],frm[MAXN][MAXM];
void output(int n,int s) {
	if(!n) return ;
	output(n-1,lst[n][s]);
	if(frm[n][s]==0) cout<<"l";
	else cout<<"r";
	return ;	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	ffor(i,0,13) hb[1<<i]=(1<<i);
	ffor(i,1,10000) if(!hb[i]) hb[i]=hb[i-1]; 
	while(T--) {
		c++;
		cin>>n;
		ffor(i,1,n) cin>>a[i],pre[i]=pre[i-1]+a[i];
		int tot=pre[n];
		if(tot!=(tot&-tot)) {
			cout<<"no\n";
			continue ;
		}
		ffor(i,1,n) ffor(j,0,tot) dp[i][j]=0;
		dp[0][0]=1;
		ffor(i,0,n-1) {
			if(i) ffor(j,0,pre[i]) if(dp[i][j]) {
				int l=j,r=pre[i]-j;
				assert(hb[l&r]!=hb[l|r]);
				if(l<r) {
					int ll=l+hb[r],rr=r-hb[r];
					dp[i][ll]=1,frm[i][ll]=frm[i][j],lst[i][ll]=lst[i][j];	
				}
				else {
					int ll=l-hb[l],rr=r+hb[l];
					dp[i][ll]=1,frm[i][ll]=frm[i][j],lst[i][ll]=lst[i][j];	
				}
			}
			ffor(j,0,pre[i]) if(dp[i][j]) {
				int l=j,r=pre[i]-j,v=a[i+1];
				if(!l||v<=(l&(-l))) {
					int nl=l+v;
					int h=hb[nl&r];
					if(hb[nl|r]==h) nl+=h;
					dp[i+1][nl]=1,frm[i+1][nl]=0,lst[i+1][nl]=j;
				}
				if(!r||v<=(r&(-r))) {
					int nr=r+v;
					int h=hb[l&nr];
					if(hb[l|nr]==h) l+=h;
					dp[i+1][l]=1,frm[i+1][l]=1,lst[i+1][l]=j;
				}
			}
		}
		if(dp[n][tot]) output(n,tot);
		else if(dp[n][0]) output(n,0);
		else cout<<"no";
		cout<<'\n';
	}
	return 0;
}
```

---

