# Light switches

## 题目描述

Nikola owns a large warehouse which is illuminated by $ N $ light bulbs, numbered $ 1 $ to $ N $ . At the exit of the warehouse, there are $ S $ light switches, numbered $ 1 $ to $ S $ . Each switch swaps the on/off state for some light bulbs, so if a light bulb is off, flipping the switch turns it on, and if the light bulb is on, flipping the switch turns it off.

At the end of the day, Nikola wants to turn all the lights off. To achieve this, he will flip some of the light switches at the exit of the warehouse, but since Nikola is lazy, he wants to flip the \_minimum\_ number of switches required to turn all the lights off. Since Nikola was not able to calculate the minimum number of switches, he asked you to help him. During a period of $ D $ days, Nikola noted which light bulbs were off and which were on at the end of each day. He wants you to tell him the minimum number of switches he needed to flip to turn all the lights off for each of the $ D $ days or tell him that it's impossible.

## 样例 #1

### 输入

```
4 3 4
2 1 2
2 2 3
1 2
1 1
2 1 3
3 1 2 3
3 1 2 4```

### 输出

```
2
2
3
-1```

# 题解

## 作者：Leap_Frog (赞：2)

### P.S.
Fun Fact : `bitset` 没有重定义大小于，却有哈希函数  
CF 恶评！！1

### Solution.
~~直接做，拿头做，用脚做，有手就行~~  

发现 $S\le 30$，一看就是指数复杂度。  
计算发现 $2^S$ 都过不去，那毛咕咕复杂度是 $\sqrt{2^S}$ 的。  
然后就直接想 `meet-in-middle`。  
暴力预处理 $1-B$ 的得到的答案，塞到 `Hash 表` 里，复杂度 $O(2^B)$。  
然后每次直接询问直接 $2^{S-B}$ 枚举状态，然后在 `Hash 表` 里查询状态。  
总复杂度是 $O(2^{S-B}\cdot D+2^{B})$，让 $B=\frac{S-\log_2D}2$ 最优。  
发现还有个 $n$ 没法搞，直接用个 `bitset` 暴力维护即可。  
复杂度懒得算了，反正能过。  

### Coding.
```cpp
//是啊，你就是那只鬼了，所以被你碰到以后，就轮到我变成鬼了{{{
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),bz=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) bz=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	bz?x=-x:x;
}/*}}}*/
typedef bitset<1005> Bt;int n,s,D;Bt c[35];unordered_map<Bt,int>mn;
int main()
{
	read(n),read(s),read(D);int m=min(s,20);
	for(int i=1,k,x;i<=s;i++) {read(k);while(k--) read(x),c[i][x]=1;}
	for(int S=0,ct=0;S<(1<<m);S++,ct=0)
	{
		Bt b;for(int j=0;j<m;j++) if((S>>j)&1) b^=c[j+1],ct++;
		if(!mn.count(b)||mn[b]>ct) mn[b]=ct;
	}
	for(int i=1,k,x;i<=D;i++)
	{
		Bt b;read(k);while(k--) read(x),b[x]=1;
		int rs=1e9;for(int S=0;S<(1<<(s-m));S++)
		{
			Bt bt;int tt=0;
			for(int j=0;j<s-m;j++) if((S>>j)&1) bt^=c[j+m+1],tt++;
			bt^=b;if(mn.count(bt)) rs=min(rs,mn[bt]+tt);
		}
		if(rs==1000000000) puts("-1");else printf("%d\n",rs);
	}
	return 0;
}
```

---

## 作者：ifffer_2137 (赞：1)

meet in the middle 好题。~~看了 tag 就会系列~~。
### 题意
$n$ 个灯泡，有 $s$ 个开关，每个开关可以改变若干个给定的不同的灯泡的状态，再给你 $q$ 次询问，每次给定初始状态，问关掉所有灯所用的最小开关数，或报告无解。
### 分析
~~tag~~ $s\le30$ 启发你考虑折半搜索。

然后就每次询问先暴力搜前一半的动作，同时维护出当前的局面，后面一半的提前预处理好，直接拿过来调用取 $\min$。这里暴搜时维护状态的方式可能会没有什么想法，本来是想 `bitset` 的但是复杂度爆炸。然后因为是灯泡控制所以可以想到随机权值 xor hash，于是就好做了，直接把当前的灯泡状态 xor hash 掉然后暴搜的时候直接在 `map` 里修改 `map` 里查就可以了。

然后你考虑平衡一下复杂度，前 $10$ 个暴搜后 $20$ 个预处理就比较平衡，时间复杂度 $O(2^{\frac{2}{3}s}+q2^{\frac{1}{3}s}\log)$
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
mt19937_64 rnd(time(NULL));
const int maxn=(1<<10)+5;
int n,s,q;
int B;
ull v[maxn];
ull t[maxn];
map<ull,int> mn; 
void dfs(int x,ull hs,int k){
	if(x==B){
		if(!mn.count(hs)) mn[hs]=k;
		else mn[hs]=min(mn[hs],k);
		return;
	}
	dfs(x-1,hs^t[x],k+1);
	dfs(x-1,hs,k);
}
int solve(int x,ull hs,int k){
	if(x==B+1){
		if(!mn.count(hs)) return inf;
		else return k+mn[hs];
	}
	return min(solve(x+1,hs^t[x],k+1),solve(x+1,hs,k));
}
signed main(){
	#ifndef ONLINE_JUDGE
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	n=read(),s=read(),q=read();B=s/3;
	for(int i=1;i<=n;i++) v[i]=rnd();
	for(int i=1;i<=s;i++){
		int k=read();
		for(int j=1;j<=k;j++){
			int x=read();
			t[i]^=v[x];
		}
	}
	dfs(s,0,0);
	while(q--){
		int k=read();ull p=0;
		for(int j=1;j<=k;j++){
			int x=read();
			p^=v[x];
		}
		int ans=solve(1,p,0);
		if(ans<inf) cout<<ans<<'\n';
		else cout<<-1<<'\n';
	}
	return 0;
}
```

---

## 作者：Masterwei (赞：1)

#### 前言

一眼秒了，常数写的太烂了，导致跑得很慢。

### 思路

发现一共只有 $30$ 个开关，直接状压肯定不行，考虑折半搜索，对于一个询问，我们枚举后半部分的状态，通过异或算出相应匹配的上半部分的状态，再算最小贡献。

具体的，状态我们用 bitset 装，因为要异或，再用一个 map 存上半部分的状态，就行了。算贡献的时候用两个状态的最小次数相加就行了。但此题如果纯折半（上半、下半状态数一致）过不了，时间复杂度炸了，但发现时间复杂度瓶颈在于询问的时候，下半状态数太多了，如果下半开小一点儿，上半开大一点儿，就可以过了。我上半的点的数量开的 $20$，跑了 $2.8$ 秒。

```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(3)
using namespace std;
inline int read(){
	int x=0;bool f=0;char ch=getchar();
	while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
const int Maxn=1e3+5,N=40;
int n,m,q;
bitset<1005>d[N];
bitset<1005>b;
int g[1<<15];
bitset<1005>gg[1<<15];
unordered_map<bitset<1005>,int>f,vis;
int main(){
	n=read();m=read();q=read();
	for(int i=1;i<=m;i++){
		int k=read();
		while(k--)d[i][read()]=1;
	}
	int cnt=m-m/3;
	for(int s=0;s<(1<<cnt);s++){
		bitset<1005>c;
		int popcnt=0;
		for(long i=1;i<=cnt;i++){
			if((s>>i-1)&1){
				c^=d[i];
				popcnt++;
			}
		}
		if(!vis[c])vis[c]=1,f[c]=popcnt;
		else f[c]=min(f[c],popcnt);
	}
	cnt=m/3;
	for(int s=0;s<(1<<cnt);s++){
		int popcnt=0;
		for(int i=1;i<=cnt;i++){
			if((s>>i-1)&1){
				gg[s]^=d[m-m/3+i];
				popcnt++;
			}
		}g[s]=popcnt;
	}
	while(q--){
		for(int i=1;i<=n;i++)b[i]=0;
		int k=read();
		while(k--)b[read()]=1;
		int ans=1e9+7;
		bitset<1005>tmp;
		for(int s=0;s<(1<<cnt);s++){
			tmp=b^gg[s];
			if(vis[tmp])ans=min(ans,f[tmp]+g[s]);
		}
		if(ans==1e9+7)puts("-1");
		else printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：lcfollower (赞：0)

考虑暴力，但是 $1\leq S\leq 30$，时间不允许。

但是我们可以考虑折半搜索。

尽管起点不一定，但是终点是一定的。

我们可以先暴力得出 $1\sim b$（一个自己定的值）可以得到的每一个状态的最小步数，丢进 `unordered_map` 里。而对于状态的更新，我们可以用 `bitset`。

更新完状态后，对于每一次次询问，从给定的状态开始 dfs，若状态出现在 `unordered_map` 里则直接返回**存储的步数**加上从**给定状态到此状态的步数**，对计算出来的答案打擂台即可。

代码如下：

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define infi 0x3f3f3f3f3f3f3f3fll
#define up(i,x,y) for(register int i=x;i<=y;++i)
#define dn(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();return x*f;}
inline void write(int x){if(x<0)putchar('-'),x=-x;if(x>9)write(x/10);putchar(x%10|48);}
inline void writeln(int x){write(x),putchar('\n');}
inline void writesp(int x){write(x),putchar(' ');}
namespace LC{
	int n=read(),s=read(),T=read(),b=19;
	bitset<1001>lig,swi[31];
	unordered_map<bitset<1001>,int>Mp;
	void dfs1(int step,int now,bitset<1001>sta){
		if(now>b){
			if(Mp.count(sta))Mp[sta]=min(Mp[sta],step);//存在则打擂台。
			else Mp[sta]=step;//不存在直接赋值。
			return ;
		}dfs1(step,now+1,sta),dfs1(step+1,now+1,sta^swi[now]);//搜索两种状态。
	}int dfs2(int step,int now,bitset<1001>sta){
		if(now>s){
			if(Mp.count(sta))return Mp[sta]+step;//存在则返回步数。
			else return inf;//到达不了就返回无解。
		}return min(dfs2(step,now+1,sta),dfs2(step+1,now+1,sta^swi[now]));//对于两种状态比最小值。
	}inline signed main(){
		up(i,1,s){
			int num=read(),x;
			up(j,1,num)x=read(),swi[i][x]=1;
		}dfs1(0,1,0);//折半搜索。
		while(T--){
			int num=read(),x;lig=0;
			up(i,1,num)x=read(),lig[x]=1;
			int ans=dfs2(0,b+1,lig);//搜索答案。
			writeln(ans==inf?-1:ans);
		}exit(0);
	}
}signed main(){
	LC::main();
}
```

---

## 作者：daniEl_lElE (赞：0)

XOR Hash+折半搜索。

对于前 $B$ 个开关，暴搜出其所有状态，并将所有翻转的开关的状态记入一个 map。直接做不好做，考虑给每个开关一个随机权值，XOR Hash 后将值加入 map。

对于后 $s-B$ 个开关，每次询问的时候枚举这些的状态，在 map 中查询是否有翻转且仅翻转剩余开关的方案即可。

总复杂度 $O(2^BB\log(2^B)+D2^{s-B}(s-B)\log D2^{s-B})$，取 $B=20$ 时最优。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
mt19937_64 rng(0x12f81ac);
int val[1005],num[35];
unordered_map<int,int> mp;
signed main(){
	int n,s,d; cin>>n>>s>>d;
	for(int i=1;i<=n;i++) val[i]=rng();
	for(int i=1;i<=s;i++){
		int c; cin>>c;
		while(c--){
			int x; cin>>x; num[i]^=val[x];
		}
	}
	for(int i=0;i<(1<<min(s,20ll));i++){
		int rval=0;
		for(int j=1;j<=s;j++){
			if((i>>(j-1))&1) rval^=num[j];
		}
		if(mp[rval]==0) mp[rval]=__builtin_popcount(i)+1;
		else mp[rval]=min(mp[rval],(int)__builtin_popcount(i)+1);
	}
	while(d--){
		int c; cin>>c;
		int qval=0;
		while(c--){
			int x; cin>>x; qval^=val[x];
		}
		if(s<=20){
			if(mp[qval]) cout<<mp[qval]-1;
			else cout<<-1;
		}
		else{
			int minv=1e9;
			for(int i=0;i<(1<<(s-20));i++){
				int rval=0;
				for(int j=1;j<=s-20;j++){
					if((i>>(j-1))&1) rval^=num[j+20];
				}
				if(mp[qval^rval]!=0) minv=min(minv,mp[qval^rval]-1+__builtin_popcount(i));
			}
			if(minv==1e9) cout<<-1;
			else cout<<minv;
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：紊莫 (赞：0)

$m$ 很小考虑暴力，但是 $\mathcal{O(n2^m)}$ 不能过，考虑 meet-in-middle。  

因为起点是不确定的，终点是唯一的，所以从全 $0$ 开始，对前 $K$ 个开关暴力枚举开或者关，记录下所有状态下的步数。这里因为 $n\le 1000$，所以改用 ``bitset`` 存储灯的状态。

然后对于每次询问，只需要把剩下一点再次暴力枚举，然后去前面找找有没有答案即可。

几个问题：

首先，$K=19$ 左右最佳，而不是 $K=\dfrac{m}{2}$，因为考虑到询问是有 $q$ 的常数（假设看做一个大常数），那么就有约 $2^{10}$ 的差距，折中一下，本地测试为 $K=19$ 最佳。

其次，因为 ``bitset`` 不支持比较，但是支持哈希，所以要用 ``unordered_map`` 存储，常数略大。

```cpp
const int N=1005,M=2000005,inf=0x3f3f3f3f,mod=1e9+7;
int n,m,q;
bitset<N> a[35],x,y;
unordered_map<bitset<N>,int> c;
void solve(){
	n = rd();m = rd();q = rd();
	F(i,0,m - 1){
		int k=rd();
		while(k--)a[i].set(rd());
	}
	int K = min(m,19),Li=(1<<K)-1;
	F(i,0,Li){
		x.reset(); int cnt = 0;
		F(j,0,K-1) if(i&(1<<j))x ^= a[j],cnt ++;
		if(!c.count(x)||c[x] > cnt) c[x] = cnt;
	}
	K = m - K;Li=(1<<K)-1;
	while(q--){
		int k = rd(),ans = inf; x.reset();
		while(k--) x.set(rd());
		if(m<=19){
			if(c.count(x)) write(c[x]),puts("");
			else puts("-1"); continue;
		}
		F(i,0,Li){
			int cnt = 0; y = x;
			F(j,0,K-1) if(i&(1<<j))y ^= a[j+19],cnt ++;
			if(c.count(y)) ans = min(ans,cnt+c[y]);
		}
		if(ans>=inf) puts("-1");
		else write(ans),puts("");
	}
}
```

---

## 作者：Cure_Wing (赞：0)

[CF1423L Light switches](https://www.luogu.com.cn/problem/CF1423L)

保持平衡，才能越走越远。

### 思路

考虑一个开关做两次是没有意义的，因为这样相当于没操作。

所以我们可以写出一个很暴力的做法，枚举每个开关是否按下，然后判断一下是否全部关闭即可。时间复杂度 $O(N\times2^S\times D)$，直接起飞。

观察一下发现 $1\le S\le30$，于是我们用折半搜索优化，每次从终点状态、初始状态开始搜索，以一半的操作为界。时间复杂度优化为 $O((N+2^{\frac{S}{2}+1})\times D)$，还是爆炸。

发现从终点状态出发搜出来的结果始终不会改变，所以这一部分可以预处理。时间复杂度优化为 $O(2^{\frac{S}{2}}+(N+2^{\frac{S}{2}})\times D)$，依旧不能满足要求。

此时我们会发现，预处理部分和询问部分的时间复杂度是不平衡的，因为后者跟着巨大的 $N$ 和 $D$。于是我们考虑平衡这两者。而事实上折半搜索的分界是我们自己定的，于是我们可以让预处理部分搜的多一点，询问部分搜的少一点，实现平衡规划。设前半部分搜索前 $l$ 个的状态，那么时间复杂度是 $O(2^l+(N+2^{S-l})\times D)$。当 $l=\frac{2S}{3}$ 时，时间复杂度为 $O(2^{\frac{2S}{3}}+(N+2^\frac{S}{3})\times D)$，可以通过。

接下来一个问题就是状态的存储。因为 $1\le N\le10^3$，显然不能用一个整数来表示。这个时候就要用到 [`bitset`](http://oi-wiki.com/lang/csl/bitset/)。`std::bitset` 是标准库中的一个存储 `0/1` 的大小不可变容器。我们把按开关的操作可以理解为两个二进制串的异或，灯泡的 $0/1$ 表示亮暗状态，开关的 $0/1$ 表示是否使灯的亮暗发生变化。而 `bitset` 可以快速的实现这个功能。比如有两个 `bitset` 变量 `a` 和 `b`，那么我们可以用 `a=a^b;` 来实现在 `a` 状态下按下了 `b` 状态的开关。

而且 `bitset` 的时间和空间也很优秀。对于一个 $4$ 字节的 `int` 变量，在只存 `0/1` 的意义下，`bitset` 占用空间只是其 $\frac{1}{32}$，计算一些信息时，所需时间也是其 $\frac{1}{32}$。

美中不足的是，`bitset` 没有自定义比较符号，而如果用红黑树实现的 [`map`](http://oi-wiki.com/lang/csl/associative-container/#map) 记录状态的话会编译失败，因为 `map` 是有序键值对容器。这个时候只能使用无序关联式容器 [`unordered_map`](http://oi-wiki.com/lang/csl/unordered-container/) 存了，因为 `unordered_map` 是基于哈希实现的。

于是我们最终的时间复杂度为 $O(\frac{1}{w}(2^{\frac{2S}{3}}+(N+2^\frac{S}{3})\times D))$。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<bitset>
#include<unordered_map>
using std::cin;using std::cout;
constexpr int N=1005,M=35,inf=1e9;
int n,m,q,k,b,ans,l;
std::bitset<N>a[M],c,d;
std::unordered_map<std::bitset<N>,int>p,v;
inline void dfs(int u,int w,int s){
    if(p.count(d)&&p[d]<=s) return ;p[d]=s;//记录最优状态
    if(u==w+1) return ;
    for(int i=u;i<=w;++i){d^=a[i];dfs(i+1,w,s+1);d^=a[i];}//继续搜索
}
inline void dfs2(int u,int w,int s){
    if(v.count(c)&&v[c]<=s) return ;v[c]=s;
    if(p.count(c)) ans=std::min(ans,s+p[c]);//发现存在对应的情况，计算答案，取最小值
    if(u==w-1) return ;
    for(int i=u;i>=w;--i){c^=a[i];dfs2(i-1,w,s+1);c^=a[i];}
}
signed main(){
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
    cin>>n>>m>>q;
    for(int i=1;i<=m;++i){
        cin>>k;
        for(int j=1;j<=k;++j){cin>>b;a[i][b]=1;}
    }
    dfs(1,m/1.5,0);//折半搜索预处理
    for(int i=1;i<=q;++i){
        cin>>k;v.clear();ans=inf;
        for(int j=1;j<=n;++j) c[j]=0;
        for(int j=1;j<=k;++j){cin>>b;c[b]=1;}
        dfs2(m,m/1.5+1,0);
        cout<<(ans==inf?-1:ans)<<'\n';
    }
    return 0;
}
```

---

## 作者：cryozwq (赞：0)

~~话说我代码常数怎么又这么大。~~

喜闻乐见的开关灯问题，发现数据范围有点大，不太能高斯消元，怎么办呢？

最暴力的做法是直接枚举每个开关的状态，记录下得到的结果。

怎么优化呢？可以考虑 Meet in the middle。

首先枚举前 $\frac{m}{2}$ 个开关，得到每个最终状态所需最小步数。再对后 $\frac{m}{2}$ 个开关来一遍。

每次询问就枚举后 $\frac{m}{2}$ 的开关的状态，异或最终状态得到前 $\frac{m}{2}$ 个开关的状态，步数取最小值即可。

但是这样单次查询 $O(2^{15})$ ，肯定过不了。我们需要让前面枚举的多一些，经过本地测试，前面 $20$ 个，后面 $10$ 个的效率是最高的。

代码见[此处](https://www.luogu.com.cn/paste/ogx8suy5)。

---

## 作者：yangchenxiao (赞：0)

首先，每个灯只有开启和关闭两种状态，可以想到状态压缩。

但是 $n$ 的范围比较大，可以用 $\mathrm{bitset}$ 来记录，如果一个人选择相当于异或其控制的灯。

如果暴力搜索时间复杂度是 $O(\displaystyle D2^S\frac{n}{32})$ 的，显然过不去。

但是由于维护信息的可合并性，可以采用折半搜索的思想，先处理一半，另一半的信息与其进行匹配。

考虑到每次询问对人的状态是不影响的，所以两部分都可以预处理。

设第一部分大小为 $size$，时间复杂为 $O(2^{size}+D2^{n-size})$。

为了进行复杂度的均衡，$size$ 选 $20$ 比较合适。

附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int len=1e3+100;
const int maxn=35,maxm=2e6+5;
const int inf=0x3f3f3f3f;
int n,m,t,num,x,cnt[maxm],ans;
bitset<len>S[maxn],a[len],ask,all,req;
unordered_map<bitset<len>,int>mp;
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
int main(){
	m=read();
	n=read();
	t=read();
	for(int i=1;i<=n;i++){
		num=read();
		for(int j=1;j<=num;j++){
			x=read();
			S[i][x]=1;
		}
	}
	int limit=n*2/3;
	bitset<len>SS;
	for(int i=0;i<(1<<limit);i++){
		SS.reset();
		num=0;
		for(int j=1;j<=limit;j++){
			if((1<<(j-1))&i)SS^=S[j],num++;
		}
//		cout<<"ppp "<<num<<endl;
		if(mp.find(SS)==mp.end())mp[SS]=num;
		else mp[SS]=min(mp[SS],num);
	}
	int limit1=n-limit;
	for(int i=1;i<(1<<limit1);i++){
		num=0;
		for(int j=1;j<=limit1;j++){
			if((1<<(j-1))&i)a[i]^=S[j+limit],num++;
		}
		cnt[i]=num;
	}
	while(t--){
		num=read();
		ask.reset();
		for(int i=1;i<=num;i++){
			x=read();
			ask[x]=1;
		}
		req.reset();
		ans=inf;
		for(int i=0;i<(1<<limit1);i++){
			req=a[i]^ask;
			if(mp.find(req)!=mp.end())ans=min(ans,mp[req]+cnt[i]);//,cout<<"hhh "<<cnt[i]<<" "<<mp[req]<<endl;
		}
		if(ans==inf)puts("-1");
		else printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：happybob (赞：0)

题意：

你有 $n$ 个灯泡和 $m$ 个开关，以及 $D$ 次询问，每次询问给定初始时亮着的灯泡，求按至少多少次开关，可以使得所有灯熄灭。

范围：$1 \leq n,D \leq 10^3$，$1 \leq m \leq 30$。

解法：

考虑先预处理 $f_i$ 表示从全部灯熄灭到有 $i$ 这个状态，只通过前 $B$ 个开关至少需要多少次。其中 $i$ 是一个 `bitset`，使用 `unordered_map` 维护即可。

询问时从 $B+1$ 开始 DFS 到 $n$，每次更新答案。为了减少常数取 $B=20$ 即可通过。

[Submission Link](https://codeforces.com/problemset/submission/1423/256660782)。

---

