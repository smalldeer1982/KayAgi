# [ABC355E] Guess the Sum

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc355/tasks/abc355_e

この問題は **インタラクティブな問題**（あなたの作成したプログラムとジャッジシステムが入出力を介して対話を行う形式の問題）です。

正整数 $ N $ および $ 0 $ 以上 $ 2^N $ 未満の整数 $ L,R(L\leq\ R) $ が与えられます。 ジャッジシステムは、$ 0 $ 以上 $ 99 $ 以下の整数からなる長さ $ 2^N $ の数列 $ A\ =\ (A_0,\ A_1,\ \dots,\ A_{2^N-1}) $ を隠し持っています。

あなたの目標は $ A_L+A_{L+1}+\dots+A_{R} $ を $ 100 $ で割った余りを求めることです。ただし、あなたは数列 $ A $ の要素の値を直接知ることはできません。 その代わりに、ジャッジシステムに対して以下の質問を行うことができます。

- $ 2^i(j+1)\leq\ 2^N $ を満たすように非負整数 $ i,j $ を選ぶ。$ l=2^ij,r=2^i(j+1)-1 $ として $ A_l+A_{l+1}+\dots+A_{r} $ を $ 100 $ で割った余りを聞く。
 
どのような $ A $ であっても $ A_L+A_{L+1}+\dots+A_{R} $ を $ 100 $ で割った余りを特定することができる質問回数の最小値を $ m $ とします。$ m $ 回以内の質問を行って $ A_L+A_{L+1}+\dots+A_{R} $ を $ 100 $ で割った余りを求めてください。

### Input &amp; Output Format

この問題はインタラクティブな問題（あなたの作成したプログラムとジャッジシステムが入出力を介して対話を行う形式の問題）です。

最初に、整数 $ N,L,R $ を標準入力から受け取ってください。

> $ N $ $ L $ $ R $

次に、$ A_L+A_{L+1}+\dots+A_{R} $ を $ 100 $ で割った余りを特定できるまで質問を繰り返してください。 質問は、以下の形式で標準出力に出力してください。

> $ ? $ $ i $ $ j $

ここで、$ i,j $ は以下を満たす必要があります。

- $ i,j $ は非負整数
- $ 2^i(j+1)\leq\ 2^N $
 
これに対する応答は、次の形式で標準入力から与えられます。

> $ T $

ここで、$ T $ は質問に対する答えで、$ l=2^ij,r=2^i(j+1)-1 $ としたとき $ A_l+A_{l+1}+\dots+A_{r} $ を $ 100 $ で割った余りです。

ただし、$ i,j $ が制約を満たしていないか、質問回数が $ m $ 回を超えた場合は $ T $ は `-1` となります。

ジャッジが `-1` を返した場合、プログラムはすでに不正解とみなされています。この場合、ただちにプログラムを終了してください。

$ A_L+A_{L+1}+\dots+A_{R} $ を $ 100 $ で割った余りが特定出来たら、$ S $ を $ A_L+A_{L+1}+\dots+A_{R} $ を $ 100 $ で割った余りとして以下の形式で出力してください。その後、ただちにプログラムを終了してください。

> $ ! $ $ S $

## 说明/提示

### 制約

- $ 1\leq\ N\leq\ 18 $
- $ 0\leq\ L\leq\ R\leq\ 2^N-1 $
- 入力は全て整数
 
### 注意点

- **出力を行うたびに、末尾に改行を入れて標準出力を flush してください。そうしなかった場合、ジャッジ結果が TLE となる可能性があります。**
- **対話の途中で誤った出力形式による出力を行った、あるいはプログラムが途中で終了した場合のジャッジ結果は不定です。**
- 解答を出力したらただちにプログラムを終了してください。そうしない場合、ジャッジ結果は不定です。
 
### 入出力例

以下は、$ N=3,L=1,R=5,A=(31,41,59,26,53,58,97,93) $ の場合の入出力例です。この場合 $ m=3 $ であるため、質問を $ 3 $ 回まで行うことができます。

    入力 出力 説明     `3 1 5`  まず整数 $ N,L,R $ が与えられます。    `? 0 1`  $ (i,j)=(0,1) $ として質問を行います。   `41`  $ l=1,r=1 $ であるため、質問の答えは $ A_1=41 $ を $ 100 $ で割った余りである $ 41 $ です。ジャッジはその値を返します。    `? 1 1` $ (i,j)\ =\ (1,1) $ として質問を行います。   `85`  $ l=2,r=3 $ であるため、質問の答えは $ A_2+A_3=85 $ を $ 100 $ で割った余りである $ 85 $ です。ジャッジはその値を返します。    `? 1 2` $ (i,j)\ =\ (1,2) $ として質問を行います。   `11`  $ l=4,r=5 $ であるため、質問の答えは $ A_4+A_5=111 $ を $ 100 $ で割った余りである $ 11 $ です。ジャッジはその値を返します。    `! 37` 答えは $ 37 $ であるとわかったので、それを出力します。

# 题解

## 作者：__ryp__ (赞：11)

本篇题解是赛后补的，参考学习了官方题解以及 jiangly dalao 的代码。

首先发现本题和最近的 [ABC349D](https://www.luogu.com.cn/problem/AT_abc349_d) 很像。但是注意到那个题里没法将两个区间相减，但是本题可以，于是那个题的策略没法照搬。

那么怎么样才能得到最优解呢？（题目要求我们必须用最优策略）

换句话说，我们需要求出从 $r$ 走到 $l$ 的最少步数。注意到值域相比上一个题小了很多，那么可以尝试最短路。

不难发现，对于一个数 $u$，我们能够转移到的数是 $v = u \pm 2^j, 0\le j \le \mathrm
{lowbit}(u)$，其中 $\mathrm{lowbit}(x)$ 是 $x$ 的最低非零位。因为对于 $j \gt\mathrm{lowbit}(u)$，$2^j \nmid u$，无法转移。

由于边权都是 $1$，我们就可以直接 BFS 跑出最短路，然后一边跳一边计算即可。

[赛后的 submission](https://atcoder.jp/contests/abc355/submissions/53901382)

---

## 作者：Iceturky (赞：6)

[Link](https://atcoder.jp/contests/abc355/tasks/abc355_e) 

注意到要求使用区间数量最小，且区间端点范围较小。

可以把所有可以使用的区间全都拿出来，找一个能拼成 $[l,r]$ 的使用区间数量最少的方案。

这个可以通过把区间变成左闭右开（好处理一些）跑最短路。

因为边权为 $1$ 所以直接 bfs 。

赛时没想出来，想了个分治，感觉不好写就弃了。

code

```cpp
struct edge{
	int v,nxt;
}e[N<<2];//区间数量最多 2^{n+1} 级别
int head[N],tott;
void add(int u,int v){e[++tott]={v,head[u]},head[u]=tott;}

int frm[N];

void bfs(int st,int ed){
	queue<int>q;
	q.push(st);
	frm[st]=st;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		if(u==ed)
			return;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(frm[v]>=0)
				continue;
			frm[v]=u;
			q.push(v);
		}
	}
}

signed main()
{
	int n,l,r;
	cin>>n>>l>>r;r++;
	for(int k=0;k<=n;k++)
		for(int i=0;((i+1)<<k)<=(1<<n);i++)
			add(i<<k,(i+1)<<k),add((i+1)<<k,i<<k);
	for(int i=0;i<=(1<<n);i++)
		frm[i]=-1;
	bfs(l,r);
	int ans=0;
	for(int i=frm[r];i!=r;r=i,i=frm[i]){
//		cout<<r<<" "<<i<<endl;
		if(i<r)
			cout<<"? "<<__lg(r-i)<<" "<<(i>>__lg(r-i))<<endl,ans+=read();
		else
			cout<<"? "<<__lg(i-r)<<" "<<(r>>__lg(i-r))<<endl,ans-=read();
	}
	cout<<"! "<<(ans%100+100)%100<<endl;
	return 0;
}
```

---

## 作者：ran_qwq (赞：5)

用尽量少的长度为 $2^i$，左端点能被长度整除的区间表示出 $L,R$。

首先这题与大多数交互题不同，贪心是错误的。不一定要拆分区间，可以用大区间和减去小区间和。而贪心只会往一个方向走不会往另一个方向走。

所以可以抽象成一个图论模型，从已知点搜索，可以通过 $1$ 的花费互相转化的两个点之间建边权为 $1$ 的边。

这里从 $L$ 开始，bfs 走到 $R+1$（如果是 $L-1$ 和 $R$ 就会数组越界），设当前是 $u$。对于一个 $l$，区间长度为 $2^l$，如果 $l=0$ 或者 $2^{l-1}\mid u$ 就可以走。
- 如果 $u+2^l\le N$，就可以从 $u$ 走到 $u+2^l$。
- 如果 $u\ge 2^l$，就可以从 $u$ 走到 $u-2^l$。

走的同时记录前驱和询问的 $i,j$。当走到 $R+1$ 时，就找到了最小询问次数的方案。输出方案时不停往前跳，直到跳到 $L$。

现在的问题就是知道了方案，怎么求和。这个其实不难，bfs 的过程可以理解为不停地拓展当前区间 $[L,u]$，直到与目标区间重合（我们定义这里的闭区间可以左端点大于等于右端点）。所以 $u$ 往左走对答案有负贡献，往右走有正贡献。输出方案是倒着输出的，所以要反过来。

```cpp
int n,L,R,l,r,ans,q[N],dp[N],pre[N],I[N],J[N];
void QwQ() {
	n=rd(),L=rd(),R=rd(),q[l=r=1]=L,mst(dp,0x3f),mst(pre,-1),dp[L]=0;
	while(l<=r) {
		int u=q[l++],v;
		if(u==R+1) {
			int t=u;
			while(~pre[t]) {
				int x=t-1,y=pre[t]-1; if(x>y) swap(x,y); x++;
				printf("? "),wr(I[t]," "),wr(J[t],"\n"),fflush(stdout);
				int res=rd(); if(t>pre[t]) ans=(ans+res)%100; else ans=(ans-res+100)%100;
				t=pre[t];
			}
			printf("! "),wr(ans,"\n"),exit(0);
		}
		for(int i=0;i<=n&&(!i||!(u>>i-1&1))&&u>=1<<i;i++) {
			v=u-(1<<i); if(dp[v]!=INF) continue;
			dp[v]=dp[u]+1,pre[v]=u,I[v]=i,J[v]=min(u,v)>>i,q[++r]=v;
		}
		for(int i=0;i<=n&&(!i||!(u>>i-1&1))&&u+(1<<i)<=1<<n;i++) {
			v=u+(1<<i); if(dp[v]!=INF) continue;
			dp[v]=dp[u]+1,pre[v]=u,I[v]=i,J[v]=min(u,v)>>i,q[++r]=v;
		}
	}
}
```

---

## 作者：Arghariza (赞：4)

根据[这题](https://www.luogu.com.cn/problem/P10145)，将区间变成左闭右开 $[L,R)$，询问 $[L,R)$ 就给 $L$ 和 $R$ 之间连边，那么最后区间 $[L',R')$ 可以得出的充要条件为 $L'$，$R'$ 联通。

于是相当于对所有 $i,j$，给 $2^ij$ 和 $2^i(j+1)$ 连边，求 $L,R+1$ 的最短路。

注意到边权为 $1$，总边数为 $2^N+2^{N-1}+\cdots +2^0=2^{N+1}-1$，于是直接建图 bfs 即可。

假设最短路为 $L\to p_1\to p_2\to \cdots \to p_m\to R+1$，那么每次查询时往左跳就减去查询的和，往右跳就加上即可。如果是从 $R+1$ 跳到 $L$ 就反过来。

```cpp
#include <bits/stdc++.h>
#define eb emplace_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

const int M = (1 << 18) + 100;

int n, S, L, R, to[M], vs[M];
vector<int> g[M];

void solve() {
    scanf("%d%d%d", &n, &L, &R), R++;
    S = (1 << n);
    queue<int> q; q.push(L);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j + (1 << i) <= S; j += (1 << i))
            g[j].eb(j + (1 << i)), g[j + (1 << i)].eb(j);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vs[u] = 1;
        for (int v : g[u]) {
            if (vs[v]) continue;
            to[v] = u, vs[v] = 1, q.push(v);
        }
    }
    int cur = R, res = 0;
    while (cur != L) {
        int lst = to[cur];
        int l = min(lst, cur), r = max(lst, cur), len = __lg(r - l);
        printf("? %d %d\n", len, l / (1 << len)), fflush(stdout);
        int c; scanf("%d", &c);
        if (lst >= cur) (res += 100 - c) %= 100;
        else (res += c) %= 100;
        cur = lst;
    }
    printf("! %d\n", res); fflush(stdout);
}

bool Med;
int main() {
	// ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	// cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen(".in", "r", stdin);
		freopen(".out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	// cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：OtterZ (赞：4)

~~没有场切，蒟蒻吃枣药丸~~
# 题意
给定二进制位数 $N$ 与要查询的区间 $[L,R]$，以最小的查询次数查 $[2^ij,2^i(j + 1) - 1]$，得到 $[L,R]$。
# 两种情况

1. 查询 $[2^ij,2^i(j + 1) - 1]$，作为有效区间加入。
2. 查询 $[2^ij,2^i(j + 1) - 1]$，作为赘余区间排除。

这个蒟蒻试图贪心，但贪心只处理 $1$ 可以，加入 $2$ 后一言难尽，欢迎嘲讽。
# 差分与最短路
我们根据差分思想，转化为求 $s_r - s_{l - 1}$。
这样区间 $[2^ij,2^i(j + 1) - 1]$ 变为 $s_{2^i(j + 1) - 1} - s_{2^ij}$。
设 $i$ 号点对应 $s_i$，边或路径 $(i,j)$ 对应 $s_j - s_i$，边权为 $1$，则我们要求 $l - 1$ 到 $r$ 的最短路径。

考虑到存在 $s_{-1}$，我们将编号总体加 $1$。
# 正解
对于 $2^j | i$，在 $i$ 和 $i + 2 ^ j$ 之间连双向边，用 `bfs` 求最短路，最终还原最短路时询问。时间复杂度 $\operatorname{O}(|V| + |E|) = \operatorname{O}(n2^n)$。
# 代码

```cpp
#include<cstdio>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;
int n,m,l,r;
int las[(1 << 18) + 9];
bool vis[(1 << 18) + 9];
vector<int>e[(1 << 18) + 9];
queue<int>q;
void bfs(){
	q.push(l);
	vis[l] = true;
	while(!q.empty()){
		int d = q.front();
		q.pop();
		for(int i = 0; i < e[d].size(); i ++){
			if(!vis[e[d][i]]){
				vis[e[d][i]] = true;
				q.push(e[d][i]);
				las[e[d][i]] = d;
			}
		}
	}
}
int main(){
	scanf("%d %d %d",&n,&l,&r);
	for(int i = 0; i < (1 << n); i ++){
		for(int j = 1; i + j <= (1 << n) && i % j == 0; j *= 2){
			e[i].push_back(i + j);
			e[i + j].push_back(i);
		}
	}
	bfs();
	int nw = r + 1;
	int sum = 0;
	while(nw != l){
		int o = las[nw];
		//printf(" %d %d\n",nw,o);
		if(nw > o){
			int sp = log2(nw - o),tp = o / (1 << sp);
			printf("? %d %d\n",sp,tp);
			fflush(stdout);
			int p;
			scanf("%d",&p);
			sum = (sum + p) % 100;
		}
		else{
			int sp = log2(o - nw),tp = nw / (1 << sp);
			printf("? %d %d\n",sp,tp);
			fflush(stdout);
			int p;
			scanf("%d",&p);
			sum = (sum - p + 100) % 100;
		}
		nw = o;
	}
	printf("! %d\n",sum);
	return 0;
}
```
~~没有场切，蒟蒻吃枣药丸~~

---

## 作者：songhongyi (赞：2)

经典套路：考虑前缀和 $s_i = a_1+\cdots+a_{i-1}$，则 $a_l+\cdots+a_{r-1} = s_{r}-s_{l}$。考虑对于每个这样的询问，连一条边 $(l,r)$，则 $[L,R)$ 的区间和可知当且仅当 $L,R$ 连通。

因此我们要找的就是一条 $L$ 到 $R+1$ 的最短路。由于这张图只有 $O(2^N\cdot N)$ 条边，因此直接在此图上 bfs 的时间复杂度是可以接受的。

---

## 作者：zrl123456 (赞：1)

**注：此题为 IO 交互题。**

题目考察：交互，最短路。  
题目简述：  
给你三个整数 $n,l,r$，指评测机随机生成了一个长度为 $2^n$ 的序列 $\{a_{2^n}\}$（题目从 $0$ 开始计数），让你求区间 $[l,r]$ 的和对 $100$ 取模的结果 $\displaystyle(\sum_{i=l}^ra_i)\bmod 100$。  
你可以问评测机若干个问题，每次以 ``` ? l r ``` 的形式给出，意为询问区间 $[2^ij,2^i(j+1)-1]$ 的和对 $100$ 取模的结果，若得到了答案，以 ```! ans``` 的形式给出答案，并立即终止程序。  
要求在能确定答案的情况下，问题数最少，你要按照以上描述给出答案。  
数据范围：
- $n\in[1,18]\cap\mathbb N$
- $l,r\in[0,2^n-1]\cap\mathbb N$
- $l\le r$

------------
为了方便，我们将 $[l,r+1)$ 当作题目的 $[l,r]$。  
我们将这道题建模为由 $r+1$ 走到 $l$ 的最短路，我们可以由 $x$ 转移到 $x-2^i$ 和 $x+2^i$（$i\in\mathbb Z,2^i|x$），由于边权都为 $1$，所以使用 BFS 即可。  
记录路径时我们记录其前驱结点即可。  

这样我们就得到了路径，然后我们对其进行询问，最后输出答案即可。  

代码：  
```cpp
#include<bits/stdc++.h>
#define int long long
#define reg register
#define inl inline
#define INF LLONG_MAX
#define rep(i,x,y) for(reg int i=x;i<=y;++i)
#define rer(i,x,y,cmp) for(reg int i=x;i<=y&&cmp;++i)
#define per(i,x,y) for(reg int i=x;i>=y;--i)
#define gc getchar
#define pc putchar
#define endl '\n'
#define fi first
#define se second
using namespace std;
inl int read(){
	reg int f=1,x=0;
	reg char ch;
	while(!isdigit(ch=gc()))
		if(!(ch^'-')) f=-1;
	x=ch^48;
	while(isdigit(ch=gc())) x=(x<<1)+(x<<3)+(ch^48);
	return f*x;
}
inl void write(int x,char ch){
	if(x<0){
		pc('-');
		x=-x;
	}
	if(x>=10) write(x/10,0);
	pc(x%10^48);
	if(ch) pc(ch);
}
inl string get(){
	char ch;
	string s="";
	while((ch=gc())=='\r'||ch=='\n'||ch==' ');
	s+=ch;
	while((ch=gc())!='\r'&&ch!='\n'&&ch!=' ') s+=ch;
	return s;
}
inl char gett(){
	char ch;
	while((ch=gc())=='\r'||ch=='\n'||ch==' ');
	return ch;
}
inl int maxx(int a,int b,int c){
	return max(a,max(b,c));
}
inl int minn(int a,int b,int c){
	return min(a,min(b,c));
}
const int N=(1<<18)+10,MOD=100;
int n,l,r,lst[N],ans,now,res;
queue<int>q;
inl void bfs(){
	q.push(l);
	while(!q.empty()){
		reg int x=q.front();
		q.pop();
		rep(i,0,__lg(n)){
			rep(j,-1,1)
				if(j){
					reg int tx=x+(1<<i)*j;
					if(tx>=0&&tx<=n&&!(~lst[tx])){
						lst[tx]=x;
						q.push(tx);
					}
				}
			if(x&(1<<i)) break;
		}
	}
}
signed main(){
	memset(lst,-1,sizeof(lst));
	n=(1<<read());
	l=read();
	r=read()+1;
	bfs();
	now=r;
	while(now!=l){
		reg int f=1,a=lst[now],b=now;
		if(a>b){
			swap(a,b);
			f=-1;
		}
		putchar('?');
		putchar(' ');
		write(__lg(b-a),' ');
		write(a/(b-a),endl);
		fflush(stdout);
		res=read();
		(ans+=f*res+MOD)%=MOD;
		now=lst[now];
	}
	putchar('!');
	putchar(' ');
	write(ans,endl);
	return 0;
}
```

---

## 作者：M1saka16I72 (赞：1)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-abc355-e.html)

非常好交互题，使我的思维旋转。大概是最近几场 abc 里唯一一道比较值得带脑子做的 E 题。

## 思路

按照题意模拟后，可以画出一张允许被查询的区间的示意图：

![](https://pic.imgdb.cn/item/66532b6ed9c307b7e947cc70.png)

你会发现这个东西长得跟线段树很像，但如果把线段树的递归查询函数照葫芦画瓢写上就会发现 WA 了三分之二的测试点，原因则是交互次数不能保证最优，比如说图里的 $[1,7]$ 实际上只用查 $[0,7],[0,0]$ 两次，用这种方法需要查 $[1,1],[2,3],[4,7]$ 三次。

上面的乱搞给了我们一个启示，那就是最优的询问次数很可能小于  $\log n$，从而我们可以推断，我们需要使用的询问方式并不是一种基于复杂度分析的通用策略（因为不管什么固定策略都不会比 $\log$ 的询问复杂度更优秀了），而是会根据输入动态调整的。此时可以开始考虑如何转化题意，使问题更加可做。

## 转化

看了官方题解的应该都知道是把询问转化成图上的边然后跑最短路，这里解释一下这样做的实际意义，便于理解。

我们可以利用一个比较经典的 trick，在差分约束算法的经典例题 [Intervals](https://www.luogu.com.cn/problem/UVA1723) 中就能见到，简单来讲就是把区间问题转化成前缀和上的问题。

假装我们已经知道了序列里下标为 $l-1$ 的前缀和，并且 $[l,r]$ 是一个可询问的区间，那么通过一次询问，我们就能知道 $r$ 的前缀和，反之亦然。于是可以把这种关系干到图上，对每个可询问区间 $[l,r]$ 都从 $l-1$ 向 $r$ 连双向边。由于每次询问的代价为 $1$，因此边权也全为 $1$，直接跑 bfs 求 $L-1$ 到 $R$ 的最短路即可。

## 实现

实现方面，我们可以用一个 from 数组记录使每个点到达最短路的边，这样方便我们求完最短路之后进行询问。同时对于每条边可以加上一个 id 值代表这条边是正边还是反边，如果是反边就在询问时减掉这次询问的结果，否则加上询问结果。同时因为本题下标从 $0$ 开始，可以直接改为从 $l$ 向 $r+1$ 连边再求 $L$ 到 $R+1$ 的最短路，否则 $l=0$ 时会访问到负下标。至于对区间 $[l,r]$ 的询问格式，推一个比较简单的式子即可，这里不再赘述，参见代码：[link](https://atcoder.jp/contests/abc355/submissions/53927126)。

---

## 作者：Otue (赞：1)

简单交互题。

注意到我们求最终答案的方式：由你询问的区间拼凑而成。

但不一定只有加法，可以询问一个大区间然后减去一些小区间。这可能比一堆小区间拼凑起来用的区间数量更少。

观察到 $0\leq L\leq R\leq 2^{18}-1$，这是一个很小的数。说明这道题并不需要数学方式求解，考虑建图再跑最短路。对于一个数 $x$，找出以 $x$ 为端点的所有区间，将 $x$ 连向区间的另一个端点，边权为 $1$。 

```cpp
// 从x开始连边 
for (int i = 1; i <= (1ll << n); i *= 2) {
	for (auto j : {x - i, x + i}) {
		if (j < 0 || j > (1ll << n)) continue;
		add_edge(x, j, 1);
	}
	if (x & i) break;
}
```

这是连边方式的代码，请意会。

于是从 $L$ 开始跑最短路，记录最短路前驱。从 $R$ 开始倒推，若当前点为 $a$，倒推至上一个点 $b$，则有：

* 若 $b\leq a$，则将答案加上 judge 返回的答案。
* 否则，将答案减去 judge 返回的答案。

注意到此题边权都为 1，则直接 bfs 即可，且可直接记录前驱。 

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define _for(i, a, b) for (int i = (a); i <= (b); i++)
#define _pfor(i, a, b) for (int i = (a); i >= (b); i--)
#define int long long
const int N = 19;

int n, L, R, vis[1 << N], lst[1 << N];

signed main() {
	cin >> n >> L >> R;
	R++;
	queue<int> q;
	q.push(L);
	memset(lst, -1, sizeof lst);
	lst[L] = L;
	while (q.size()) {
		int u = q.front(); q.pop();
		for (int i = 1; i <= (1ll << n); i *= 2) {
			for (auto j : {u - i, u + i}) {
				if (j < 0 || j > (1ll << n)) continue;
				if (lst[j] == -1) {
					lst[j] = u;
					q.push(j);
				}
			}
			if (u & i) break;
		}
	}
	int res = 0;
	int t = R;
	while (t != L) {
		int a = lst[t], b = t, f = 1;
		if (a > b) {
			swap(a, b);
			f = -1;
		}
		cout << "? " << __lg(b - a) << ' ' << a / (b - a) << endl;
		int x;
		cin >> x;
		res = (res + x * f + 100) % 100;
		t = lst[t];
	}
	cout << "! " << res << endl;
}
```

复杂度 $O(2^nn)$。本题复杂度可以做到 $O(n^3)$ 左右的级别，为 dp 做法。

---

## 作者：huhaoming2011 (赞：0)

## 题目大意
在一个 $2^N$ 的区间里,通过题目所给的操作，在不超过操作次数下，查询出 $l$ 到 $r$ 区间内的和模 $100$ 的值。

题目要求操作：
每次可选择非负整数 $i,j$，使得 $2^i(j+1) \leq 2^N$，给你区间 $2^ij$ 到 $2^i(j+1)$ 的值。
## 分析
第一情况下肯定能想到跳区间求和，十分贪心，但就因为是贪心，操作次数不一定是最小的，肯能会超出限制，所以，我们要换个思路：题目里其实可以通过加区间和、删区间和来求某区间和，此时操作数最小，这时发现可以对每一个点所能去到的其他点（左边右边都可以）连边，然后从点 $l$ 开始跳，跳到输入的 $r$ 为止，途中记录点所对应要跳到的点，最后询问并输出（为了方便，$r$ 在输入后加 $1$）
## 代码
```cpp
// LUOGU_RID: 161197907
#include<bits/stdc++.h>
using namespace std;
const int N=20;
int hd[N<<N],nxt[2<<N],to[2<<N],n,l,r,cnt,pp[2<<N],q[2<<N],ans;
void add(int u,int v){
	cnt++;
	to[cnt]=v;
	nxt[cnt]=hd[u];
	hd[u]=cnt;
}
void bfs(){
	int had=1,tal=1;
	q[had]=l;
	pp[l]=l;
	while(tal-had>=0){
		int u=q[had];
		had++;
		if(u==r) return;
		for(int i=hd[u];i;i=nxt[i]){
			int v=to[i];
			if(pp[v]<0){
				pp[v]=u;
				q[++tal]=v;
			}
		}
	}
}
signed main()
{
	memset(pp,-1,sizeof(pp));
	scanf("%d%d%d",&n,&l,&r);
	r++;
	for(int j=0;j<=n;j++){
		for(int i=0;((i+1)<<j)<=(1<<n);i++){
			add(i<<j,(i+1)<<j);
			add((i+1)<<j,i<<j);
		}
	}
	bfs();
	int k=pp[r];
	while(k!=r){
		if(k<r){
			printf("? %d %d\n",__lg(r-k),(k>>__lg(r-k)));
			fflush(stdout);
			int op;
			scanf("%d",&op);
			if(op==-1) return 0;
			ans+=op;
		}
		else{
			printf("? %d %d\n",__lg(k-r),(r>>__lg(k-r)));
			fflush(stdout);
			int op;
			scanf("%d",&op);
			if(op==-1) return 0;
			ans-=op;
		}
		ans=((ans%100)+100)%100;
		r=k,k=pp[k];
	}
	printf("! %d",((ans%100)+100)%100);
	return 0;
}
```
### 感谢观看

---

## 作者：cike_bilibili (赞：0)

# 思路
注意到每个点最多可以有 $O(N)$ 个可达点以及 $N$ 的数据范围，不难想到对于每个点到它的所有可达点建边跑最短路，时间复杂度似乎是 $2^N \times N^2$。

注意：每次询问后清空缓存。
```cpp
cout<<endl;
```
这行代码可以自动清理缓存。

# AC CODE
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
	int ans=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-')w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+ch-'0';
		ch=getchar();
	}
	return w*ans;
}
int n,L,R;
struct edge{
	int to;
	int next;
}ed[20000005];
int cnt;
int h[500005];
void add(int x,int y){
	ed[++cnt]={y,h[x]};
	h[x]=cnt;
}
struct node{
	int x;
	int id;
};
bool operator<(node a,node b){
	return a.x>b.x;
}
priority_queue<node>q;
int dij[500005],st[500005];
int pre[500005];
void dijkstra(int x){
	memset(dij,0x3f,sizeof dij);
	q.push({0,x});
	dij[x]=0;
	while(q.size()){
		node now=q.top();
		q.pop();
		int x=now.id;
		if(st[x])continue;
		st[x]=1;
		for(int i=h[x];i;i=ed[i].next){
			int v=ed[i].to;
			if(dij[v]>dij[x]+1){
				dij[v]=dij[x]+1;
				pre[v]=x;;
				q.push({dij[x],v});
			}
		}
	}
}
int ans;
void print(int x){
	int p=pre[x];
	if(x==L)return;
	if(p<x){
		x--;
		int k=log2(x-p+1);
		int q=p/(1<<k);
		cout<<"? "<<k<<' '<<q<<endl;
		int x=read();
		if(x==-1)exit(0);
		ans+=x;
		print(p);
	}else{
		p--;
		int k=log2(p-x+1);
		int q=x/(1<<k);
		cout<<"? "<<k<<' '<<q<<endl;
		int x=read();
		if(x==-1)exit(0);
		ans-=x;
		print(p+1);
	}
}
signed main(){
	n=(1<<read());
	L=read(),R=read();
	for(int i=0;i<=n;i++){
		for(int j=0;j<=18;j++){
			if(i%(1<<j)==0&&i+(1<<j)<=n+1)add(i,i+(1<<j));
			else break;
		}
		for(int j=0;j<=18;j++){
			if(i%(1<<j)==0&&i-(1<<j)>=0)add(i,i-(1<<j));
			else break;
		}
	}
	dijkstra(L);
	print(R+1);
	cout<<"! "<<(ans%100+100)%100<<endl;
	return 0;
} 
```

---

## 作者：Milthm (赞：0)

考虑从 $l$ 开始进行广搜，在广搜过程中记录每个位置上一个是从哪里转移过来的。这样步数一定最小。

然后从 $r$ 开始往前跳，每次看一下这段区间左端点和右端点的位置，就可以判断这段提供的权值是正的还是负的。然后把所有权值加起来就是答案。

当然因为这个询问的区间最后少一个的问题，我们实现的时候把 $r$ 加一更好实现。

[AC code](https://atcoder.jp/contests/abc355/submissions/53935501)。

---

## 作者：Sorato_ (赞：0)

# ABC355E Guess the Sum

## 题目大意

给定一个长度为 $2^n$ 的序列 $(A_0,A_1,\dots,A_{2^n-1})$，每次可以询问一个长度为 $2^i$ 的区间 $[l,r]$，满足 $l$ 是 $2^i$ 的倍数，标准输入会返回 $[l,r]$ 的区间和 $\bmod 10$ 的结果，要求以最少的次数计算出给定区间 $[L,R]$ 的区间和。

## Solve

令 $sum$ 为原序列的前缀和数组，询问区间 $[l,r]$ 的区间和相当于询问 $sum_r-sum_{l-1}$。

考虑在前缀和上建图，如果可以询问区间 $[l,r]$，那么就在 $l-1$ 和 $r$ 间连一条无向边。建边后从 $L-1$ 跑单源最短路即可，可以用 BFS 跑，因为边权都是 $1$。

至于输出询问，我们可以对于每个点 $i$，用 $fa_i$ 记录它是从哪个点转移过来的，最后从 $R$ 跑一遍 DFS 即可。

注意，原序列的下标从 $0$ 开始，所以访问 $sum_{0-1}$ 时会出问题，应将原序列下标整体加一。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
int n,a,b,ans,res,fa[1<<19];
vector<int>e[1<<19];
bool vis[1<<19];
void bfs()
{
	queue<int>q;
	q.push(a);vis[a]=1;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(auto i:e[u])
			if(!vis[i])
			{
				fa[i]=u;vis[i]=1;
				if(i==-~b)	return;
				q.push(i);
			}
	}
}
void dfs(int u)
{
	int len=log2(abs(fa[u]-u));
	if(fa[u]>u)//若转移点在当前点右侧，说明是走回头路，应减去这一段区间和。
		printf("? %lld %lld\n",len,u/(1<<len)),
		fflush(stdout)/*清空缓冲区*/,ans-=(res=read());
	else//否则应加上区间和
		printf("? %lld %lld\n",len,(fa[u])/(1<<len)),
		fflush(stdout),ans+=(res=read());
	if(res==-1)	exit(0);//依题意，若询问不合法或询问次数多于最小次数标准输出会返回-1，此时退出。
	if(fa[u]!=a)	dfs(fa[u]);//若是从起点a-1转移过来，则说明已询问完，此时不再继续询问。
}
signed main()
{
	n=read();a=read();b=read();
	for(int len=(1<<n);len;len>>=1)
		for(int i=1;i+len-1<=(1<<n);i=-~i)
			if((i-1)%len==0)//建图
				e[i-1].push_back(i+len-1),e[i+len-1].push_back(i-1);
	bfs();dfs(-~b);
	printf("! %lld",(ans%100+100)%100);
	fflush(stdout);
	return 0;
}
```

---

## 作者：Composite_Function (赞：0)

发现我跟题解区里的所有其他题解都不一样，于是就发一篇题解。

首先我们知道，$[l,r]$ 如果能被表示出来，一定是通过一两个区间加起来，或者用一个大区间表示出来。

然后考虑一个区间，这一段是在一个一个端点在区间端点上的可询问区间上。称这个区间为单边区间。

于是就可以分开成若干区间，然后考虑一个固定长度的单边区间，可以计算出这个单边区间的最优查询策略。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
int n, L, R;
inline int query(int l, int r) {
	int i = round(log2(r - l + 1));
	int j = (l - 1) / (1 << i);
	cout << "? " << i << " " << j << endl;
	fflush(stdout);
	int x;
	cin >> x;
	return x;
}
int num[N];
bool opt[N];
inline int Q(int L, int R, int x, bool lr) {
	if (L > x || R < x) return 0;
	if (L == R) {
		int ret = query(L, R);
		return ret;
	}
	if (x == R && lr == 0) {
		int ret = query(L, R);
		return ret;
	}
	if (x == L && lr == 1) {
		int ret = query(L, R);
		return ret;
	}
	int mid = (L + R) >> 1;
	if (x <= mid && lr == false) {
		return Q(L, mid, x, lr);
	}
	if (x > mid && lr == true) {
		return Q(mid + 1, R, x, lr);
	}
	if (lr == false) {
		if (!opt[x - L + 1]) return (query(L, mid) + Q(mid + 1, R, x, false)) % 100;
		else return (query(L, R) - Q(mid + 1, R, x + 1, true) + 100) % 100;
	}
	else {
		if (!opt[R - x + 1]) return (query(mid + 1, R) + Q(L, mid, x, true)) % 100;
		else return (query(L, R) - Q(L, mid, x - 1, false) + 100) % 100;
	}
}
inline int solve(int l, int r, int L, int R) {
	int mid = (l + r) >> 1;
	if (R <= mid) {
		return solve(l, mid, L, R);
	}
	if (L > mid) {
		return solve(mid + 1, r, L, R);
	}
//	cout << l << " " << r << " " << L << " " << R << endl;
	if (num[mid - L + 1] + num[R - mid] < num[L - l] + num[r - R] + 1) {
//		cout << "+" << endl;
		return (Q(l, mid, L, true) + Q(mid + 1, r, R, false)) % 100;
	}
	else {
		return (query(l, r) - Q(l, mid, L - 1, false) - Q(mid + 1, r, R + 1, true) + 200) % 100;
	}
}
signed main() {
	cin >> n >> L >> R, ++L, ++R;
	if (L == R) {
		int ret = query(L, R);
		cout << "! " << ret << endl;
		fflush(stdout);
		return 0;
	}
	int x = 1;
	for (int i = 1; i <= (1 << n); ++i) {
		if ((i & (i - 1)) == 0 && i != 1) {
			x <<= 1;
			num[i] = 1;
			continue;
		}
		if (num[i - x] + 1 < num[(x << 1) - i] + 1) {
			opt[i] = false;
			num[i] = num[i - x] + 1;
		}
		else {
			opt[i] = true;
			num[i] = num[(x << 1) - i] + 1;
		}
	}
	int ret = solve(1, (1 << n), L, R);
	cout << "! " << (ret % 100 + 100) % 100 << endl;
	fflush(stdout);
	return 0;
}
```

---

## 作者：ttq012 (赞：0)

发现 $2^n$ 很小，所以考虑暴力建图跑最短路。

具体的，考虑参见 WC2024 的第三题的做法，对于每一条可以询问的区间 $[u,v]$，从 $u$ 向 $v+1$ 连一条边。

然后考虑从 $L$ 向 $R+1$ 跑最短路，这样可以恰好覆盖 $[L,R]$ 的全部区间。

在跑最短路的时候记录一下路径，输出答案的时候计算一下即可。具体的细节见代码。

```cpp
#define F(i,x,y) for(int i=x;i<=y;i++)
#define G(i,x,y) for(int i=x;i>=y;i--)
#define W(G,i,x) for(auto&i:G[x])
#define W_(G,i,j,x) for(auto&[i,j]:G[x])
#define add(x,y) z[x].em(y)
#define add_(x,y) add(x,y),add(y,x)
#define Add(x,y,d) z[x].em(y,d)
#define Add_(x,y,z) Add(x,y,z),Add(y,x,z);
using namespace std;
const int N = 550010;
vector<int> z[N];
int dis[N], frt[N];
bool vis[N];
int ask(int x, int y) {
    int t, p1 = log2(abs(y - x)), p2 = min(x, y) / abs(y - x);
    if (x < y) {
        cout << "? " << p1 << ' ' << p2 << endl;
        cin >> t;
    } else {
        cout << "? " << p1 << ' ' << p2 << endl;
        cin >> t;
        t = -t;
    }
    // int len = y - x + 1, lgcnt = 0;
    // while (len > 1) len /= 2, lgcnt++;
    // int j = x / (y - x + 1);
    // cout << "? " << lgcnt << ' ' << j << endl;
    return t;
}
auto main() [[O3]] -> signed {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // freopen("gr.out", "w", stdout);
    int n, l, r;
    cin >> n >> l >> r;
    l++, r++;
    F(i, 0, 24) {
        int pw = 1;
        F(j, 1, i) pw = pw * 2;
        for (int L = 1, R = pw + 1; R - 1 <= (1ll << n); ) {
            add_(L, R);
            L = R;
            R += pw;
        }
    }
    queue<int> q;
    q.push(l);
    memset(dis, 0x3f, sizeof dis);
    dis[l] = 0;
    vis[l] = true;
    while (q.size()) {
        int f = q.front();
        q.pop();
        vis[f] = false;
        W(z, g, f) {
            if (dis[g] > dis[f] + 1) {
                dis[g] = dis[f] + 1, frt[g] = f;
                if (!vis[g]) q.push(g), vis[g] = true;
            }
        }
    }
    vector<int> lz;
    int t = r + 1, s = 0;
    while (t != l) lz.pb(t), t = frt[t];
    lz.pb(t);
    reverse(lz.begin(), lz.end());
    for (auto &x : lz) x--;
    F(i, 1, (int)lz.size() - 1) s = (s + ask(lz[i - 1], lz[i])) % 100;
    cout << "! " << (s % 100 + 100) % 100 << endl;
}
```

---

## 作者：Pentiment (赞：0)

还是我太弱了 qwq

首先，直接上线段树或树状数组这样的结构并不是最优的，只能过一小部分的点。

因此我们要舍弃一部分效率，使得查询次数最小。

考虑一个很暴力的方法：建立一张图，对于每个 $x$，向它能跳到的数 $y$ 连边。具体地说，向 $x+2^z$ 连边，其中 $z$ 不大于 $\text{lowbit}(x)$。

然后我们要求 $L$ 到 $R+1$ 的最短路。边权都是 $1$，直接广搜即可。这样的时间复杂度为 $O(n2^n)$ 的，足以通过。

---

## 作者：gdf_yhm (赞：0)

[abc355e](https://www.luogu.com.cn/problem/AT_abc355_e)

### 思路

[WC2024T3](https://www.luogu.com.cn/problem/P10145) 中知道一个技巧：如果知道区间 $[l,r]$ 的和就连边 $l\to r+1$，那么想推出 $[L,R]$ 的区间和就要求 $L$ 和 $R+1$ 联通。

按题意把符合要求的边连上，设边权为 $1$ 跑 bfs，求出 $L$ 到 $R+1$ 的最短路并记录路径上的点，就可以得到要询问的区间。

因为是从小往大推，对于最短路上的边 $u\to v$，如果 $u<v$ 就把区间和加上，否则减去。

### code

```cpp
int n,a,b;
int dis[maxn],pre[maxn];
vector<pii> ans;int res;
queue<int> q;
signed main(){
	n=read();a=read();b=read();
	mems(dis,0x3f);dis[a]=0;q.push(a);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=1;i<=(1<<n);i<<=1){
			int v=u+i;
			if(u%i==0&&v<=(1<<n)){
				if(dis[v]>dis[u]+1)dis[v]=dis[u]+1,pre[v]=u,q.push(v);
			}
			v=u-i;
			if(v%i==0&&v>=0){
				if(dis[v]>dis[u]+1)dis[v]=dis[u]+1,pre[v]=u,q.push(v);
			}
		}
	}
	// cout<<dis[0]<<" "<<dis[8]<<"\n";
	int u=b+1;
	while(u!=a){
		ans.push_back({pre[u],u});
		u=pre[u];
	}
	for(auto [l,r]:ans){
		int i=log2(abs(l-r)),j=min(l,r)/abs(l-r);
		if(l<r){
			printf("? %lld %lld\n",i,j);fflush(stdout);
			res+=read();
		}
		else{
			printf("? %lld %lld\n",i,j);fflush(stdout);
			res-=read();
		}
	}
	res%=100,res+=100,res%=100;
	printf("! %lld\n",res);fflush(stdout);	
}
```

---

## 作者：yanqijin (赞：0)

# 题目大意
在 $2^n$ 长的区间中，查询 $l$ 到 $r$ 的和在模 $100$ 意义下为多少。
操作：询问机器 $i$，$j$，机器会返回 $2^ij$ 到 $2^i(j+1)$ 的和在模 $100$ 意义下为多少。
# 思路
我们发现需要用最小操作次数询问，而每次操作相当于从 $2^ij$ 向 $2^i(j+1)$ 连一条边权为 $1$ 的边，所以考虑 `bfs`。
# code
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,l,r,ans=0,nxt[4718592],cnt,head[9048576],to[4718592],dis[9048576][2],sum,o,c;
long long b[9048576][2],headd=0,taill=1;
bool vis[9048576];
void read(long long &x)
{
	x=0;
	int w=1;
	char ch=0;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') w=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+ch-48;
		ch=getchar();
	}
	x*=w;
}
void write(long long x)
{
	if(x<0) putchar('-'),x=-x;
	int sta[100];
	int top=0;
	do
	{
		sta[top++]=x%10,x/=10;
	}while(x);
	while(top) putchar(sta[--top]+48);
	putchar(' ');
}
void add(long long u,long long v)
{
	nxt[++cnt]=head[u];
	head[u]=cnt;
	to[cnt]=v;
}
void bfs()
{
	b[1][0]=l;
	b[1][1]=0;
	vis[l]=1;
	while(headd<=taill)
	{
		headd++;
		for(int i=head[b[headd][0]];i;i=nxt[i])
		{
			if(vis[to[i]]) continue;
			vis[to[i]]=1;
			dis[to[i]][0]=headd;
			dis[to[i]][1]=to[i]-b[headd][0];
			if(dis[to[i]][1]<0) dis[to[i]][1]=-dis[to[i]][1];
			b[++taill][0]=to[i];
			b[taill][1]=b[headd][1]+1;
			if(b[taill][0]==r+1)
			{
				o=taill;
				ans=b[taill][1];
				return ;
			}
		}
	}
}
int main()
{
	read(n);read(l);read(r);
	for(int i=0;i<=(1<<n)-1;i++)
	{
		long long h=1;
		for(int j=0;j<=n;j++)
		{
			if(i%h==0)
			{
				if(i+h<=(1<<n))
				{
					add(i+h,i);
					add(i,i+h);
				}
			}
			h<<=1;
		}
	}
	bfs();
	for(int i=1;i<=ans;i++)
	{
		long long u=b[dis[b[o][0]][0]][0];
		if(u>b[o][0]) u=b[o][0];
		long long w=log2(dis[b[o][0]][1]),w1=u/dis[b[o][0]][1];
		printf("? ");write(w);write(w1);putchar('\n');
		fflush(stdout);
		read(c);
		if(c==-1) return 0;
		if(b[o][0]>b[dis[b[o][0]][0]][0])sum=(sum+100+c)%100;
		else sum=(sum+100-c)%100;
		o=dis[b[o][0]][0];
	}
	printf("! ");write(sum);
	fflush(stdout);
	return 0;
}
```

---

