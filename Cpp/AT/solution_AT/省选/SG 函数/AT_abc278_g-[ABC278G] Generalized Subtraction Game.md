# [ABC278G] Generalized Subtraction Game

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc278/tasks/abc278_g

本题为**交互题**（你的程序将与评测程序通过标准输入输出进行交互）。

给定整数 $N, L, R$。  
你将与评测系统进行如下游戏：

> 有 $N$ 张编号为 $1$ 到 $N$ 的卡片放在场上。  
>  先手和后手轮流进行如下操作：
> 
> - 选择一组整数 $(x, y)$，满足 $1 \leq x \leq N$，$L \leq y \leq R$，并且编号为 $x, x+1, \dots, x+y-1$ 的 $y$ 张卡片都还在场上，然后将这些卡片从场上移除。
>  
> 不能进行操作的一方判负，另一方获胜。

你需要选择先手或后手。然后，在你选择的回合与评测系统进行游戏，并取得胜利。

## 说明/提示

## 限制条件

- $1 \leq N \leq 2000$
- $1 \leq L \leq R \leq N$
- $N, L, R$ 均为整数

## 注意事项

- **每次输出后，请在行末加上换行并刷新标准输出。否则可能会导致评测结果为 TLE。**
- **如果在交互过程中输出了非法内容，或者程序中途退出，评测结果不确定。** 特别注意，如果程序运行时发生运行时错误，评测结果可能不是 RE，而是 WA 或 TLE。
- 游戏结束后请立即终止程序，否则评测结果不确定。

## 输入输出样例

以下为 $N = 6, L = 1, R = 2$ 时的输入输出示例。

    输入 输出 说明
    6 1 2  首先输入整数 $N, L, R$。
    First  选择先手，开始游戏。
    2 1  选择 $(x, y) = (2, 1)$，移除卡片 $2$。
    3 2  选择 $(x, y) = (3, 2)$，移除卡片 $3, 4$。
    6 1  选择 $(x, y) = (6, 1)$，移除卡片 $6$。
    5 1  选择 $(x, y) = (5, 1)$，移除卡片 $5$。
    1 1  选择 $(x, y) = (1, 1)$，移除卡片 $1$。
    0 0  评测系统无法操作，你获胜。

由 ChatGPT 4.1 翻译

# 题解

## 作者：cwfxlh (赞：12)

# [AT_abc278_g](https://www.luogu.com.cn/problem/AT_abc278_g)    
萌新接触 SG 函数的第一道题。     

首先考虑如果我们先手把区间砍成左右对称的两段，那么接下来机器的每一次操作都可以被我们镜像模仿，于是就赢了。剩下的情况就是 $l=r$ 且 $l$ 和 $n$ 奇偶性不同的情况。    

对于这种情况我们直接上 SG 函数，因为 $l=r$，所以这时的 SG 函数就可以 $O(n^2)$ 计算了，于是我们根据 $SG(n)$ 是否为零确定先后手，接下来按 Nim 的套路走就可以了。    

代码：     

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,r,k1,k2,k3,k4,k5,k6,k7,k8,k9,sg[5003],apr[50003],cs[5003],mxbit[500003];
int stk[50003][2],tot;
int lowbit(int X){return (X&(-X));}
int main(){
	scanf("%d%d%d",&n,&l,&r);
	for(int i=1;i<=500000;i++){
		if(i-lowbit(i)==0)mxbit[i]=lowbit(i);
		else mxbit[i]=mxbit[i-lowbit(i)];
	}
	if(l!=r||(l==r&&(n&1)==(l&1))){
		puts("First");
		fflush(stdout);
		for(int i=l;i<=r;i++){
			if((n&1)==(i&1)){
				printf("%d %d\n",((n-i)/2)+1,i);
				fflush(stdout);
				break;
			}
		}
		while(1){
			scanf("%d%d",&k1,&k2);
			if(k1==0&&k2==0)break;
			if(k1==-1&&k2==-1)return 0;
			printf("%d %d\n",n-(k1+k2-1)+1,k2);
			fflush(stdout);
		}
		return 0;
	}
	for(int i=0;i<l;i++)sg[i]=0;
	for(int i=l;i<=n;i++){
		for(int j=1,u=l;u<=i;j++,u++)apr[(sg[j-1]^sg[i-u])]=1;
		for(int j=0;;j++){
			if(apr[j]==0){
				sg[i]=j;
				break;
			}
		}
		for(int j=1,u=l;u<=i;j++,u++)apr[(sg[j-1]^sg[i-u])]=0;
	}
	if(sg[n]==0){
		puts("Second");
		fflush(stdout);
		scanf("%d%d",&k1,&k2);
		if(k1==-1&&k2==-1)return 0;
		if(k1==0&&k2==0)return 0;
		for(int i=k1;i<=k1+k2-1;i++)cs[i]=1;
	}
	else{
		puts("First");
		fflush(stdout);
	}
	while(1){
		tot=0;
		for(int i=1;i<=n;i++){
			if(cs[i]==0){
				if(i==1)stk[++tot][0]=1,stk[tot][1]=1;
				else{
					if(cs[i-1]==1)stk[++tot][0]=1,stk[tot][1]=i;
					else stk[tot][0]++;
				}
			}
		}
		k1=0;
		for(int i=1;i<=tot;i++)k1^=sg[stk[i][0]];
		for(int i=1;i<=tot;i++){
			if((sg[stk[i][0]]&mxbit[k1])!=0){
				k2=(sg[stk[i][0]]^k1);
				for(int j=1,u=l;u<=stk[i][0];j++,u++){
					if((sg[j-1]^sg[stk[i][0]-u])==k2){
						printf("%d %d\n",j+stk[i][1]-1,l);
						fflush(stdout);
						for(int p=j+stk[i][1]-1;p<=u+stk[i][1]-1;p++)cs[p]=1;
						break;
					}
				}
				break;
			}
		}
		scanf("%d%d",&k1,&k2);
		if(k1==-1&&k2==-1)return 0;
		if(k1==0&&k2==0)break;
		for(int i=k1;i<=k1+k2-1;i++)cs[i]=1;
	}
	return 0;
}
```


---

## 作者：jrxxx (赞：5)

[ABC278G](https://www.luogu.com.cn/problem/AT_abc278_g)

## 前置知识

$\text{nim}$ 游戏，$\text{sg}$ 函数。

## 思路

### $\text{Step 1}$

在博弈寻找必胜策略时有一种经典思路——将自己的操作和对手的操作一一对应，只要对手能够操作，自己就能够操作。

一个典例就是：轮流取石子，每次可以取 $1$ 个到 $3$ 个，取到最后一个石子的胜利。若石子总数为 $4$ 的倍数，有后手必胜策略：对手取 $x$ 个石子，自己就取 $4-x$ 个石子；否则有先手必胜策略：先一步取走除以 $4$ 的余数个石子，然后按照后手必胜策略做。

这道题，我们也希望能找到这样的一种“对应策略”。

具体地，我们先手将“正中心”取走一段 $[l,r]$ 。然后若对方选 $[1,l)$ 中的一段，我们就选 $(r,n]$ 中对应位置上的一段，反之亦然。

这种策略在绝大多数情况下都适用，但有一个 $\text{bug}$——当 $L=R$ 且与 $n$ 奇偶性相反时，无法取走“正中心”。

### $\text{Step 2}$

对这种情况，我们需要寻找另外的思路。

考虑一个游戏局面——由若干不交区间组成。这相当于一个 $\text{nim}$ 游戏：每一个区间都是一个独立的公平博弈游戏，每次操作只能选择且一定要选择一个区间进行游戏。

于是，预处理出 $sg_i$ 表示长度为 $i$ 的区间的 $sg$ 函数值后，就可以通过 $\text{xor}$ 表示出任意局面的 $sg$ 函数值。（$\text{nim}$ 游戏的结论）

从小到大枚举长度 $i$，求 $sg_i$ 时枚举进行一次取走操作能到的后继状态——枚举 $j$ 表示取走 $[j+1,j+L]$，则 $sg_i=\text{mex}\{sg_{j}\oplus sg_{i-j-L}\}$。复杂度 $O(n^2)$。

初始时的局面就是 $sg_n$，若 $sg_n>0$ 有先手必胜策略，否则有后手必胜策略。

如何构造方案呢？

已知当前局面是必胜态，要求找到一种当前状态的后继必败状态。

设当前共有 $k$ 条线段，长度分别为 $a_1$ 到 $a_k$。

则 $sg_{now}=sg_{a_1}\oplus sg_{a_2}\oplus\cdots\oplus sg_{a_k}$。

目标是找到一个区间 $i$，将其取走长为 $L$ 的一段，剩下两段长度分别为 $j$ 和 $a_i-j-L$，使得 $sg_{now}\oplus sg_{a_i}\oplus sg_{j}\oplus sg_{a_i-j-L}=0$。

即 $sg_{now}\oplus sg_{a_i}=sg_{j}\oplus sg_{a_i-j-L}$。

枚举 $i$，左半部分是好求的，右半部分在预处理 $sg$ 时在 $\text{xor}$ 的值域上开个桶顺便记录一下，直接查即可。单次操作复杂度 $O(n)$。

总复杂度 $O(n^2)$。

## 代码

[提交记录](https://atcoder.jp/contests/abc278/submissions/36702819)




---

## 作者：Qiaoqia (赞：3)

[可能更好的阅读体验](https://atcoder-for-chinese-developers.github.io/atcoder-for-chinese/index.html?page=Sabc278.abc278_g.mf25ic)


首先发现这个问题是一个公平组合游戏，那么考虑它一个状态的 SG 函数是怎么样的。

我们把这个游戏看成若干个满足卡牌连续的游戏的组合，这样我们只要处理出每个长度对应的游戏的 SG 函数就可以了。  

于是就有了一个朴素的做法，枚举一个长度，再枚举 $x, y$，最后对所有执行了 $(x, y)$ 操作剩下的两段的异或和求 $\operatorname{mex}$，这样就处理出来了我们需要的 SG 函数。进行游戏时只要枚举操作将当前状态变成 SG 函数值为 $0$ 的状态即可。  

但是这样复杂度太高了。可以发现，$L \le y \le R$ 的限制实际上是限制了操作后剩下的两段的和，那么对于每个长度，把它所有的分成两段和相同的作为一组。这样枚举 $(x, y)$ 显然浪费了，考虑直接枚举两段异或值 $x$，并判断否可以被达到。  

具体地，开一个 `std::map` 的数组，把异或和为 $x$，长度和为 $y$ 的两段长度放进 `map[x][y]` 里，查询的时候在相应的异或和对应的容器里 `lower_bound` 即可。同时对于一个长度记下要达成每个异或和的方案。注意到只加入了 $n$ 个 SG 函数值，所以可以单次加入的时候枚举它和前面每一个长度的组合，存到相应的 `std::map` 里。

这样处理出所有 `SG` 的复杂度降到了 $O(n^2 \log n)$。

然后考虑怎么去进行游戏。  

这一步其实很好做，用一个 `std::set` 存下每一段，对于我们的回合，枚举每一段可否通过改变使得所有段的 SG 函数为 $0$ 即可。由 SG 函数知识可以知道，这是一定有解的。得到任意一组答案后进行相应的修改并处理交互库的操作即可。  

这一段的复杂度也是 $O(n^2 \log n)$ 的。

```cpp
void doit(int x, int y) {
	auto c = *std::prev(s.upper_bound({x, n}));
	s.erase(c);
	cur ^= SG[c.second];
	if (x - c.first > 0) s.insert({c.first, x - c.first}), cur ^= SG[x - c.first];
	if (c.second - (x - c.first) - y > 0) {
	    s.insert({x + y, c.second - (x - c.first) - y});
	    cur ^= SG[c.second - (x - c.first) - y];
	}
}

void insert(int x) {
	for (int i = 0; i <= x; i++)	
		map[SG[i] ^ SG[x]][i + x] = {i, x};
}

void main() {
	std::cin >> n >> L >> R;
	
	for (int i = 0; i <= n; i++) 
		for (int j = 0; j <= n; j++)    
			mtd[i][j] = {-1, -1};
	for (int i = 0; i < L; i++) SG[i] = 0, insert(i);
	for (int i = L; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			int l = std::max(i - R, 0), r = std::max(i - L, l);
			auto it = map[j].lower_bound(l);
			if (it == map[j].end() || it -> first > r) {
				SG[i] = j;
				break;
			} 
			mtd[i][j] = it -> second;
		}
		insert(i);
	}
	
	s.insert({1, n}), cur = SG[n];
	if (SG[n]) std::cout << "First" << std::endl;
	else { 
		std::cout << "Second" << std::endl;
		int x, y;
		std::cin >> x >> y;
		doit(x, y);
	}
	
	while ("2500!"[0]) {
		std::pair<int, int> res = {-1, -1};
		int b = 0, l = 0;
		for (auto c : s) 
			if (mtd[c.second][SG[c.second] ^ cur] != std::make_pair(-1, -1)) 
				res = mtd[c.second][SG[c.second] ^ cur], l = c.second, b = c.first;
		int x = res.first + b, y = l - res.second - res.first;
		std::cout << x << ' ' << y << std::endl;
		doit(x, y);
		std::cin >> x >> y;
		if (x == 0 && y == 0) return;
		doit(x, y);
	}
}
```

第一次在比赛中想出 AT 难度 2500 的题做法耶！

---

## 作者：fanypcd (赞：2)

如果开始的序列是两段中间隔开且长度一样的部分，显然后手必胜。

必胜策略就是在先手没操作的那一半部分模仿先手的操作。

但是现在的序列是连续的一段，所以我们考虑先手并将其分割开，需要满足 $L < R ~\lor ~ (n-L)=2k(k \in \mathbb{N})$，即如果可选的操作长度奇偶均有，或者只有一种但是和序列长度奇偶性相同，都可以做到在第一步将其分为相同长度的两段。

这个时候还剩下 $L=R~\land~(n-L)=2k+1(k \in\mathbb{N})$ 的情况没有解决。但是此时算出所有长度的 SG 函数的复杂度是 $O(n^2)$ 可以接受，所以就解决了。

如果 ${\rm SG}(n)=0$ 后手必胜，反之先手必胜，输出方案只需要保证当前局面的 ${\rm SG}$ 函数的异或和为零即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
template <class T> inline void read(T &x) {
	x = 0; int f = 0; char ch = getchar();
	while(!isdigit(ch))
		f |= ch == '-', ch = getchar();
	while(isdigit(ch))
		x = x * 10 + ch - 48, ch = getchar();
	x = f ? -x : x; return;
}
#define inf 0x3f3f3f3f
#define ll long long
#define fir first
#define sec second
#define N 2005
int n, L, R, a, b;
int f[N];
int dfs(int len) {
	if(~f[len]) return f[len];
	if(len < L) return f[len] = 0;
	int cnt[N] = {0};
	for(int i = 0; i + L <= len && i <= len - L - i; i++) {
		cnt[dfs(i) ^ dfs(len - L - i)]++;
	}
	int re = 0; while(cnt[re]) re++;
	return f[len] = re;
}
int st[N];
inline void modify(int p, int l) {
	for(int i = p; i <= p + l - 1; i++) st[i] = 0;
	return;
}
inline bool work() {
	int nv = 0;
	for(int i = 1; i <= n; i++) {
		if(st[i]) {
			int p = i; while(st[p]) p++; p--;
			nv ^= dfs(p - i + 1); i = p;
		}
	}
//	assert(nv);
	for(int i = 1; i <= n; i++) {
		if(st[i]) {
			int p = i; while(st[p]) p++; p--;
			if(p - i + 1 >= L) {
				for(int dv = 0; dv + L <= p - i + 1; dv++) {
					if((dfs(p - i + 1) ^ dfs(dv) ^ dfs(p - i + 1 - L - dv)) == nv) {
						cout << i + dv << " " << L << endl;
						modify(i + dv, L); return 1;
					}
				}
			}
			i = p;
		}
	}
	cout << "0 0" << endl;
//	assert(0);
	return 0;
}
signed main() {
	read(n), read(L), read(R);
	if(L < R || !((n - L) & 1)) {
		cout << "First" << endl;
		int v = L + ((n - L) & 1);
		cout << (n - v) / 2 + 1 << " " << v << endl;
		n -= v;
		while(1) {
			read(a), read(b);
			if(!a && !b) break;
			if(a <= n / 2) {
				cout << a + n / 2 + v << " " << b << endl;
			}
			else cout << a - n / 2 - v << " " << b << endl;
		}
		return 0;
	}
	memset(f, -1, sizeof(f));
	dfs(n); fill(st + 1, st + n + 1, 1);
	if(f[n]) {
		cout << "First" << endl;
		work();
	}
	else cout << "Second" << endl;
	while(1) {
		read(a), read(b);
		if(a <= 0 || b <= 0) break;
		modify(a, b); work();
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：1)

牛逼博弈题。

首先如果 $l<r$，先手必胜。先手可以取一个和 $n$ 奇偶性相同的长度 $x$，把中间 $x$ 个取走。然后可以对称地模仿对方的操作，最后肯定是先手取完。

如果 $l=r$，注意到每一个长度的 SG 值相等，暴力计算 SG 值：

$$sg_i=\operatorname{mex}\{sg_j\oplus sg_{i-j-l}\}$$

如果 $sg_n\ne0$ 先手必胜，否则后手必胜。

然后就找当前的一段没被取的区间 $[s,t]$，分成 $[s,i)$ 和 $[i+l,t]$。设当前所有区间 SG 值的 mex 为 $sm$，为保证必胜，要满足 $sm\oplus sg_{t-s+1}\oplus sg_{s-i}\oplus sg_{t-i-l-1}=0$。用 set 维护连续段即可。

```cpp
int n,s,t,L,R,sg[N],b[N];
set<int> ps; set<pii> st;
pii qry(int l,int r,int f=1) {
	if(f) wr(l," "),wr(r-l+1,"\n"),fflush(stdout); int x=rd(),y=rd();
	if(!x&&!y||!~x&&!~y) exit(0); y+=x-1;
	auto it=ps.lb(x); L=*prev(it)+1,R=*it-1;
	for(int i=x;i<=y;i++) ps.insert(i); return pii{x,y};
}
void QwQ() {
	n=rd(),s=rd(),t=rd(),ps={0,n+1};
	if(s<t) {
		puts("First"),fflush(stdout); pii p;
		if(n&1) {int x=t&1?t:t-1; p=qry((n+1>>1)-(x>>1),(n+1>>1)+(x>>1));}
		else {int x=t&1?t-1:t; p=qry((n>>1)-(x>>1)+1,(n>>1)+(x>>1));}
		while(1) p=qry(n+1-p.sec,n+1-p.fir);
	} else {
		for(int i=s;i<=n;i++) {
			mst(b,0);
			for(int j=0;j<=i-s;j++) b[sg[j]^sg[i-j-s]]=1;
			for(;b[sg[i]];sg[i]++);
		}
		#define I(l,r) l<=r&&(st.insert({l,r}),0)
		#define E(l,r) st.erase({l,r})
		if(sg[n]) puts("First"),fflush(stdout),I(1,n);
		else {puts("Second"),fflush(stdout); pii p=qry(1,n,0); I(1,p.fir-1),I(p.sec+1,n);}
		while(1) {
			int sm=0,f=0; for(auto [l,r]:st) sm^=sg[r-l+1];
//			wr(sm,"\n");
//			for(auto [l,r]:st) wr(l," "),wr(r,"\n"); puts("");
//			for(int x:ps) wr(x," "); puts("");
			for(auto [l,r]:st) {
				for(int i=l;i<=r-s+1;i++) {
//					wr(l," "),wr(r," "),wr(i,"\n"),wr(sm^sg[r-l+1]^sg[i-l]^sg[r-s-i+1],"\n");
					if(!(sm^sg[r-l+1]^sg[i-l]^sg[r-s-i+1])) {
						for(int j=i;j<=i+s-1;j++) ps.insert(j);
						E(l,r),I(l,i-1),I(i+s,r); pii p=qry(i,i+s-1);
						E(L,R),I(L,p.fir-1),I(p.sec+1,R),f=1; break;
					}
				}
				if(f) break;
			}
		}
	}
}
```

---

## 作者：AC_love (赞：1)

显然，如果 $l \ne r$ 或 $l = r$ 且 $l$ 与 $n$ 奇偶性相同，那么你只需要先占据中间，然后和交互库下模仿棋，你就赢定了。

考虑 $l = r$ 且 $l$ 与 $n$ 奇偶性不同时应该怎么做。

不难发现，对于一个长度为 $len$ 的块，其 SG 值是固定的。

那么我们就可以直接记忆化搜索求出 $len = 1$ 到 $len = n$ 时所有的块的 SG 函数。如果发现 `sg[n]` 不是 $0$ 你就选先手，如果是 $0$ 你就选后手。

与人机对弈时记得时刻保证你下完之后当前每个块的 SG 值异或和为 $0$ j即可。

核心代码：

```cpp
void solve()
{
	int now = 0, lent = 0;
	for(int i = 1; i <= n + 1; i = i + 1)
	{
		if(seg[i])
			now ^= SG(lent),
			lent = 0;
		else
			lent ++;
	}
	for(int i = 1; i <= n; i = i + 1)
	{
		if(seg[i])
			continue;
		int j = i;
		while(!seg[j])
			j ++;
		j --;
		int len = j - i + 1;
		if(j - i + 1 >= l)
		{
			for(int lef = i; lef + l - 1 <= j; lef = lef + 1)
			{
				if((now ^ sg[len] ^ sg[lef - i] ^ sg[j - (lef + l - 1)]) == 0)
				{
					cout << lef << " " << l << endl;
					clear(lef, l);
					return;
				}
			}
		}
		i = j;
	}
}
```

---

## 作者：james1BadCreeper (赞：1)

如果可以先手第一步下在中间，然后我们就下模仿棋就行了。

否则，此时选择的区间长度固定，考虑计算 SG 函数，令 $\operatorname{SG}_i$ 代表长度为 $i$ 的游戏的 SG 值。

对于 $i<l$，有 $\operatorname{SG}_i=0$，否则枚举选择的长度，有 $\operatorname{SG}_i=\operatorname{mex}_{j=0}^{i-l}\{\operatorname{SG}_{j} \operatorname{xor} \operatorname{SG}_{i-j-l}\}$。

输出方案时采用 `set` 维护连续段，不断选择后手必败的区间即可。[代码](https://atcoder.jp/contests/abc278/submissions/49015405)。

---

## 作者：bulijoijiodibuliduo (赞：1)

## 题目大意
 - 给定 $n$，$l$，$r$ 三个数，你需要和交互器博弈。
 - 有一个长度为 $n$ 的区间，你和交互器轮流操作。
 - 每次操作，操作的一方选择一个没有被染黑并且长度在 $l$ 和 $r$ 之间的区间，把它染黑。
 - 无法操作的一方寄了，另一方获胜。
 - 每次你操作要输出两个数 $a$ 和 $b$，表示你选择了区间 $[a,a+b-1]$。
 - 每次交互器操作会给你两个数 $a$ 和 $b$，表示交互器选择了 $[a,a+b-1]$，若  $a=b=0$ 则表示你获胜，如果 $a=b=-1$ 则表示你寄了。

## 解题思路
### 情况1
 - 先考虑能否模仿对方，发现唯一的问题就是如果他把区间放在，中间你模仿不了。
 - 所以你考虑先手，先把中间的占了，让左右的长度相同。
 - 此时只要满足 $l\neq r$ 或者 $l \equiv n \pmod 2$ 即可。

### 情况2
 - $l = r$，这个时候你只能涂黑固定长度的区间。
 - 考虑计算 $\text{SG}$ 函数，不知道什么是 $\text{SG}$ 函数的可以看[这里](https://oi-wiki.org/math/game-theory/impartial-game/)。 
 - 令 $SG_i$ 表示长度为 $i$ 的 $\text{SG}$ 函数值。
 - 那么当 $i<l$ 时，$SG_i=0$。
 - 那么我们要计算对于 $i\ge l$ 的 $SG_i$，就要枚举你这个区间放在哪里。
 - 所以 $SG_i=\operatorname{mex}_{j=1}^{i-l+1}\{SG_{j-1} \operatorname{xor} SG_{i-j-l+1}\}$。
 - 如果 $SG_n = 0$ 那么先手必败，你要选择后手，否则选择先手。
 - 你可以用 `set` 维护现在还剩哪些连续的空白段。
 - 每次轮到你操作的时候就枚举你选择哪个区间，使得删去这个区间时剩下的局面先手必败，也就是剩下的 $\text{SG}$ 函数值异或为 $0$。

## 代码示例
场上没过，后来才调出来。

```cpp
/*
* @Author: ftt2333
* @Email: ftt2333@126.com
* @LastEditTime: 2022-11-19 23:41:43
*/

#include <bits/stdc++.h>
using namespace std;
#define off ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define fin(s) freopen(s, "r", stdin)
#define fout(s) freopen(s, "w", stdout)
#define fio(s) fin(s".in"), fout(s".out")
using ll = long long; using ull = uint64_t;
using db = double; using ldb = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
using vi = vector<int>; using vl = vector<ll>;
template <class T> using uid = uniform_int_distribution<T>;
template <class T> using urd = uniform_real_distribution<T>;
#define rep(i, a, b) for(auto i = (a); i <= (b); ++i)
#define per(i, a, b) for(auto i = (a); i >= (b); --i)
#define go(i, h, e, x) for(int i = h[x]; i; i = e[i].nxt)
#define pb push_back
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define szof(a) int((a).size())
#define mem(a, b) memset(a, b, sizeof(a))
#define mcpy(a, b) memcpy(a, b, sizeof(a))
#define int ll

mt19937 rnd(random_device{}());
const int mod = 998244353, N = 2114;

int n, l, r;
int f[N], tax[N];

void solve1() {
  cout << "First\n";
  int e = l + (l % 2 != n % 2);
  int pos = (n - e) / 2 + 1;
  cout << pos << ' ' << e << '\n';
  cout.flush();
  int x, y;
  for (; ; ) {
    cin >> x >> y;
    if (!x && !y) break;
    y = x + y - 1;
    swap(x, y);
    x = n + 1 - x, y = n + 1 - y;
    cout << x << ' ' << y - x + 1 << '\n';
    cout.flush();
  }
}

int mex(vi v) {
  for (int x : v) tax[x]++;
  int res = 0;
  rep(i, 0, N - 1) if (!tax[i]) {
    res = i;
    break;
  }
  for (int x : v) tax[x]--;
  return res;
}

set<pii> rng;

void split(int l, int r) {
  auto it = prev(rng.upper_bound({l, n}));
  auto e = *it;
  rng.erase(it);
  if (e.fi < l) rng.insert({e.fi, l - 1});
  if (e.se > r) rng.insert({r + 1, e.se});
}

int base = 0;
bool check(int l, int r) {
  auto it = rng.upper_bound({l, n});
  if (it == rng.begin()) return 0;
  it--; auto e = *it;
  if (e.fi > l || e.se < r) return 0;
  if (base ^ f[e.se - e.fi + 1] ^ f[l - e.fi] ^ f[e.se - r]) return 0;
  return 1;
}

void getnext() {
  base = 0;
  for (auto e : rng) base ^= f[e.se - e.fi + 1];
  rep(i, 1, n - l + 1) if (check(i, i + l - 1)) {
    cout << i << ' ' << l << '\n';
    cout.flush();
    split(i, i + l - 1);
    break;
  }
}

void solve2() {
  rep(i, l, n) {
    vi v;
    rep(j, 1, i - l + 1) {
      v.pb(f[j - 1] ^ f[i - j - l + 1]);
    }
    f[i] = mex(v);
  }
  rng.insert({1, n});
  if (f[n]) {
    cout << "First\n";
    getnext();
  }
  else cout << "Second\n";
  int x, y;
  for (; ; ) {
    cin >> x >> y;
    if (!x && !y) return;
    y = x + y - 1;
    split(x, y);
    getnext();
  }
}

signed main() {
  cin >> n >> l >> r;
  if (l != r) solve1();
  else solve2();
}
```

---

## 作者：Aigony (赞：0)

> 我们有时候要把正经做法和人类智慧结合起来。—— KH

试试直接 dp？设 $sg(i)$ 表示一个长度为 $i$ 的区间的 $\text{SG}$ 值，总复杂度是 $\mathcal{O}(n^3)$ 的，且看起来不可优化。

找性质，如果在第一步能把区间划分成恰好相等的两段，此后不论后手做什么，我们都在另一段做对称的操作，就赢了。

而做不到这种情况时，必然有 $l=r$ 且 $l\bmod 2\neq n\bmod 2$。  
进一步地，重新考虑上面的 dp，因为这时候有 $l=r$ 的保证，转移复杂度就变成了 $\mathcal{O}(n^2)$。可以写出方程：
$$
sg(i)=\text{mex}_{j+k=i-l} \{sg(j)\oplus sg(k)\}
$$

求出先后手必胜后，选择对应的一方即可。

至于构造方案，类比 Nim 游戏的证明，对每个 $i$ 开一个桶存放哪些位置能被谁异或到，每次枚举连续段，找到任意一个使 $\text{SG}$ 值变为 $0$ 的方案并操作。
因为这里可以接受平方的复杂度，每次重新统计所有连续段情况是完全可行的。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
int n,l,r;
il void Solve()
{
    cout<<"First"<<endl;
    int len=((n-l)&1)?l+1:l,st=((n-len)>>1)+1;
    cout<<st<<" "<<len<<endl;
    while("qwq")
    {
        int a,b; cin>>a>>b; 
        if(a<=0) return;
        int l=a,r=a+b-1; l=n-l+1,r=n-r+1;
        cout<<r<<" "<<l-r+1<<endl;
    }
}
const int N=2005;
int sg[N],t[N][N];
int nw[N];
il bool dopt()
{
    int a,b; cin>>a>>b;
    if(a<=0) return 0;
    for(int i=a;i<=a+b-1;i++) nw[i]=1;
    return 1;
}
struct node{int l,r;};
vector<node> v;
il void wopt()
{
    int st=-1;
    v.clear(); nw[n+1]=1;
    for(int i=1;i<=n+1;i++)
    {
        if(!nw[i]&&st==-1) st=i;
        else if(nw[i]&&st!=-1) v.push_back({st,i-1}),st=-1;
    }
    int now=0;
    for(auto x:v) now^=sg[x.r-x.l+1];
    for(auto x:v)
    {
        int len=x.r-x.l+1,qwq=now^sg[len];
        if(t[len][qwq]!=-1) 
        {
            int st=t[len][qwq]+x.l;
            cout<<st<<" "<<l<<endl;
            for(int i=st;i<=st+l-1;i++) nw[i]=1;
            break;
        }
    }
}
int main()
{
    cin>>n>>l>>r;
    if(l!=r||(n-l)%2==0) {Solve();return 0;}
    memset(t,-1,sizeof(t));
    for(int i=l;i<=n;i++)
    {
        for(int j=0;i-l-j>=0;j++) t[i][sg[j]^sg[i-l-j]]=j;
        while(t[i][sg[i]]!=-1) sg[i]++;
    }
    if(sg[n]) printf("First\n");
    else 
    {
        printf("Second\n");
        dopt();
    }
    while("qwq") 
    {
        wopt();
        if(!dopt()) return 0;
    }
}
```

---

## 作者：不知名用户 (赞：0)

题意：给定一个长度为 $N$ 的序列，每次可以删去长度为 $[L,R]$ 的区间，无法操作者败。现在你要选择先手或后手使得你能获胜。（与交互机 PK）

如果 $[L,R]$ 中有与 $N$ 奇偶相同的数，则在中间取一段使得左右长度相等然后镜像操作（$\Theta(n)$）。

否则 $L=R$，考虑 $\text{SG}$。易知 $\text{SG}(x)=\text{mex}^{x-L+1}_{i=1}\text{SG}(i-1)\oplus\text{SG}(x+1-i-L)$。然后我们可以选择先后手，对于每一步我们知道剩下区间的长度，即可得到当前的 $\text{SG}$。然后依次与每个长度的 $\text{SG}$ 值分别异或看有没有比原来小的，如果有就对这个区间拆分成两个线段使得两个线段的 $\text{SG}$ 异或之后是你想要的即可。

~~注意到某个 ** 忘记在输出之后对区间标记，警钟长鸣。~~

```cpp
#include<bits/stdc++.h>
#define end ((a==0&&b==-1)||(a==-1||b==-3))
using namespace std;

const int N = 2010;

int sg[N], mk[N], col[N];

void put(int l, int r){cout<<l<<' '<<r-l+1<<'\n';for(int i=l;i<=r;i++) col[i] = 1;fflush(stdout);}

int main()
{
	int n, l, r, i, j, k;
	cin>>n>>l>>r;
	if(l<r||(n-l)%2==0)
	{
		int L, R;
		if((n-l)%2) l++;
		L = (n - l) / 2 + 1, R = n - (n - l) / 2;
		cout<<"First\n";
		put(L,R);
		for(;;)
		{
			int a, b;cin>>a>>b;b = a + b - 1;
			if(end) break;
			put(L+R-b,L+R-a);
		}
		return 0;
	}
	for(i=l;i<=n;i++)
	{
		for(j=1,k=l;k<=i;j++,k++) mk[sg[j-1]^sg[i-k]] = 1;
		for(j=0;mk[j];j++);
		sg[i] = j;
		for(j=1,k=l;k<=i;j++,k++) mk[sg[j-1]^sg[i-k]] = 0;
	}
	if(sg[n]) cout<<"First\n", fflush(stdout);
	else
	{
		cout<<"Second\n", fflush(stdout);
		int a, b;cin>>a>>b;b = a + b - 1;
		if(end) return 0;
		for(i=a;i<=b;i++) col[i] = 1;
	}
	while(1)
	{
		int s = 0, found = 0;
		for(i=1;i<=n;i++)
			if(!col[i])
			{
				for(j=i;j<=n&&!col[j];j++);
				int len = j - i;
				s ^= sg[len];
				i = j - 1;
			}
		//assert(s);
		for(i=1;i<=n;i++)
			if(!col[i])
			{
				for(j=i;j<=n&&!col[j];j++);
				int len = j - i, L = i, R = j - 1;
				if(len>=l&&(s^sg[len])<sg[len])
				{
					for(j=L,k=i+l-1;k<=R;j++,k++)
						if((s^sg[len])==(sg[j-L]^sg[R-k]))
						{
							put(j,k);found = 1;
							break;
						}
				}
				if(found) break;
				i = R;
			}
		int a, b;cin>>a>>b;b = a + b - 1;
		if(end) break;
		for(i=a;i<=b;i++) col[i] = 1;
	}
	return 0;
}

```

---

## 作者：zesqwq (赞：0)

# [ABC278G] Generalized Subtraction Game 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc278_g)

$\text{sto}\ \text{lg\_choumingzhaozhu}$ 一眼秒了这道题。

我们发现这个博弈如果直接 $\text{SG}$ 函数是 $O(n^3)$ 的。但是我们发现博弈游戏有一个很好的方案，叫做模仿对手，因此我们把问题分为两类：

----

第一类，$l \not = r$。

我们发现这类问题可以选择先手，然后直接取正中间的一段（因为 $l,l+1$ 之中一定有一个和 $n$ 同奇偶），这样序列就划分成了完全相同的 $2$ 段，可以对对方的操作进行 **模仿** 来获取胜利。

简要代码如下：

```cpp
puts("First");
printf("%d %d\n", (n >> 1) - (l >> 1) + 1, l);
fflush(stdout);
int l = (n >> 1) - (l >> 1) + 1, k = l + l;
int L, R;
while (scanf("%d %d", &L, &R), L && L != -1) {
    if (L < l)
        printf("%d %d\n", L + k - 1, R);
    else
        printf("%d %d\n", L - k + 1, R);
    fflush(stdout);
}
```

-----

第二类，$l=r$。

我们发现这样情况下 $\text{SG}$ 的时间复杂度是 $O(n^2)$ 预处理 $O(n^2\log n)$ 查询的。具体来说，首先，一个长度为 $n$ 的区间可以分裂成长度为 $x$ 和 $n - x - l$ 这样 $2$ 个区间，那么我们就可以得出 $SG(x) = \operatorname{mex}_{i=1}^{n-l+1}\{SG(i - 1) \operatorname{xor} SG(n - i - l - 1)\}$，即可 $O(n^2)$ 计算 $\text{SG}$ 函数。

然后考虑如何输出操作。起初，你要按照 $\text{SG}$ 函数是否为 $0$ 来判断先后手，然后用一个类似 `old driver tree` 的方法，用一个 `set` 来维护，`set` 中存的是许多二元组 $(l,r)$。

处理对手的输入的方法就是每次找到对手输入的区间在 `set` 中的位置，然后分裂这个区间，例如对手输入了 $[l,r]$，你找到了 $[L,R]$，那么你就分裂成 $[L,l-1],[r + 1,R]$，注意判断分裂后区间大小是否大于 $0$。

自己操作就暴力枚举从哪个位置开始操作，然后用 `set` 验证操作是否合法， $\text{SG}$ 函数验证这样操作是否正确，最后再用处理对手输入的方法来删除区间即可。

实际上你这个 `set` 可以用 `list` 优化到 $O(n^2)$，但是没有必要。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
int n, l, r;
const int N = 2222;
int mp[N];
void wudaoshi_idea(int x) {
    puts("First");
    printf("%d %d\n", (n >> 1) - (x >> 1) + 1, x);
    fflush(stdout);
    int l = (n >> 1) - (x >> 1) + 1, k = l + x;
    int L, R;
    while (scanf("%d %d", &L, &R), L && L != -1) {
        if (L < l)
            printf("%d %d\n", L + k - 1, R);
        else
            printf("%d %d\n", L - k + 1, R);
        fflush(stdout);
    }
    exit(0);
}
set<pair<int, int> > odt;
int base;
inline bool check(int l, int r) {
    set<pair<int, int> >::iterator it = odt.upper_bound({l, n});
    if (it == odt.begin()) return 0;
    --it;
    if (it->first > l || it->second < r) return 0;
    return !(base ^ mp[it->second - it->first + 1] ^ mp[l - it->first] ^ mp[it->second - r]);
}
inline void split(int l, int r) {
    set<pair<int, int> >::iterator it = odt.upper_bound({l, n});
    --it;
    int L = it->first, R = it->second;
    odt.erase(it);
    if (R > r) odt.insert({r + 1, R});
    if (L < l) odt.insert({L, l - 1});
}
inline void solve() {
    base = 0;
    for (set<pair<int, int> >::iterator it = odt.begin(); it != odt.end(); it++) base ^= mp[it->second - it->first + 1];
    for (int i = 1; i <= n - l + 1; i++)
        if (check(i, i + l - 1)) {
            printf("%d %d\n", i, l), fflush(stdout);
            split(i, i + l - 1);
            return;
        }
}
bool vis[N];
inline int mex(vector<int> &vec) {
    memset(vis, 0, sizeof(vis));
    for (int v : vec) vis[v] = 1;
    int ans = 0;
    while (vis[ans]) ++ans;
    return ans;
}
int main() {
    cin >> n >> l >> r;
    if (l != r) wudaoshi_idea(((l ^ n) & 1) + l);
    if (!((l ^ n) & 1)) wudaoshi_idea(l);
    vector<int> s;
    for (int x = 1; x <= n; x++) {
        int ans = 0;
        for (int i = 1; i <= x - l + 1; i++) s.push_back(mp[i - 1] ^ mp[x - i - l + 1]);
        mp[x] = mex(s);
        s.clear();
    }
    odt.insert({1, n});
    if (mp[n])
        puts("First"), solve();
    else
        puts("Second");
    fflush(stdout);
    int L, R;
    while (scanf("%d %d", &L, &R), L && L != -1) {
        split(L, L + R - 1);
        solve();
    }
    return 0;
}
```

---

## 作者：Iam1789 (赞：0)

萌萌博弈捏。

考虑暴力 `dp` 出 `SG` 函数，有 $\text{SG}_n=\text{mex}_{1\leq i \leq j \leq n,l\leq j-i+1 \leq r}\text{SG}_{i-1}\oplus\text{SG}_{n-j}$。转移时间复杂度为 $\Theta(n^2(r-l))$，无法通过。

但考虑如果 $\exists l\leq i \leq r$，满足 $n-i$ 为偶数，则我们可以选择中间长度为 $i$ 的一段，将左右分成均匀的两段，与对手下模仿棋。具体的，我们第一步选择了 $l,r$，如果对手下 $l_1,r_1 < l$，则我们下 $r+(l-r_1),r+(l-l_1)$，反之亦然。此时是先手必胜的。

特判掉 $n < l$ 和 $l \leq n \leq r$ 后，由于奇偶性的原因，对于所有的 $l <r$，均可找到 $i$ 满足上面的条件，可以使用上面的做法。否则使用暴力 `dp`。因为 $l=r$，`dp` 的时间复杂度为 $\Theta(n^2)$，可以通过。

---

