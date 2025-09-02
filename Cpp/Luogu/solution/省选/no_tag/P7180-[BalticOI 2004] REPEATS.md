# [BalticOI 2004] REPEATS

## 题目描述

如果字符串 $s$ 满足：

- 对于一个数对 $(k,l)~(k\ge 1,l\ge 1)$。
- $s$ 是由 $k$ 个长度为 $l$ 的字符串 $t$ 拼接成的。

那么 $s$ 就被称作是一个 $(k,l)\text{ - repeat}$ 串。

如 $s=\tt abaabaabaaba$ 就是一个 $t=\tt aba$ 的 $(4,3)\text{ - repeat}$ 串。

对于一个字符串 $u$（仅含字符 $\texttt a$ 和 $\texttt b$），你需要找出其中的一段是 $(k,l)\text{ - repeat}$ 串的**连续的**字符串，使 $k$ 尽可能大。

例如 $u=\tt babb\underline{abaabaabaaba}b$，其中划线部分就是一个 $(4,3)\text{ - repeat}$ 串，这时 $k$ 的值最大。

## 说明/提示

#### 数据规模与约定

对于 $100\%$ 的数据，有 $1\le n\le 5\times 10^{4}$，$u_i\in\{\tt a,b\}$。

#### 说明

译自 [BalticOI 2004 Day2 A REPEATS](https://boi.cses.fi/files/boi2004_day2.pdf)

特别感谢 @[Sprague_Garundy](https://www.luogu.com.cn/user/764746) 提供的 SPJ！

## 样例 #1

### 输入

```
17
b
a
b
b
a
b
a
a
b
a
a
b
a
a
b
a
b ```

### 输出

```
4
3
5```

# 题解

## 作者：D2T1 (赞：3)

## P7180 [BOI2004] REPEATS

题意：给定字符串，求重复次数最多的连续重复子串。

考虑枚举这个子串的长度 $k$。如果 $lcp(suf(i), suf(i+k))=x$，那么则 $s_{[i,i+k-1]}$ 重复了 $\lfloor \dfrac{x}{k}\rfloor$ 次。那么我们就得到了一个 $O(n^2)$ 的做法，即先枚举 $k$，再枚举 $i$。

考虑优化，其实我们并不需要枚举所有的 $i$。容易发现如果 $[i,i+k-1]$ 与 $[j,j+k-1]$ 有交的话，计算一个向两侧的 lcp 即可。具体地，若计算 $i$，令 $l=i-1-lcs(pre(i+k-1), pre(i-1))+1$，$r=i+k+lcp(suf(i), suf(i+k))-1$，答案用 $\lfloor \dfrac{r-l+1}{k}\rfloor$ 更新。这样我们只用枚举 $i=1,1+k,1+k*2,...$。

lcp 和 lcs（反串 lcp）可使用后缀数组求解。

复杂度为 $O(n\log n+\dfrac n1 +\dfrac n2+...+\dfrac nn)=O(n\log n)$。

```cpp
//P7180
#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 10;
int t, n, a[N], lg2[N];
int sa[N], rk[N], cn[N], pr[N], he[N];
int st[N][20], stt[N][20];
int saa[N], rkk[N], hee[N];

void initial(){
	memset(sa, 0, sizeof(sa));
	memset(rk, 0, sizeof(rk));
	memset(cn, 0, sizeof(cn));
	memset(pr, 0, sizeof(pr));
	memset(he, 0, sizeof(he));
}
void suftech(){
	int m = 26;
	for(int i = 1; i <= n; ++ i){
		rk[i] = a[i];
		++ cn[rk[i]];
	}
	for(int i = 2; i <= m; ++ i){
		cn[i] += cn[i-1];
	}
	for(int i = n; i >= 1; -- i){
		sa[cn[rk[i]]--] = i;
	}
	for(int k = 1; k <= n; k <<= 1){
		int tot = 0;
		for(int i = n - k + 1; i <= n; ++ i){
			pr[++tot] = i;
		}
		for(int i = 1; i <= n; ++ i){
			if(sa[i] > k){
				pr[++tot] = sa[i] - k;
			}
		}
		for(int i = 1; i <= m; ++ i){
			cn[i] = 0;
		}
		for(int i = 1; i <= n; ++ i){
			++ cn[rk[i]];
		}
		for(int i = 2; i <= m; ++ i){
			cn[i] += cn[i-1];
		}
		for(int i = n; i >= 1; -- i){
			sa[cn[rk[pr[i]]]--] = pr[i];
			pr[i] = 0;
		}
		swap(rk, pr);
		tot = 1;
		rk[sa[1]] = 1;
		for(int i = 2; i <= n; ++ i){
			if(pr[sa[i]] == pr[sa[i-1]] && pr[sa[i]+k] == pr[sa[i-1]+k]){
				rk[sa[i]] = tot;
			} else {
				rk[sa[i]] = ++ tot;
			}
		}
		if(tot == n){
			break;
		}
		m = tot;
	}
	int k = 0;
	for(int i = 1; i <= n; ++ i){
		if(rk[i] == 1){
			he[rk[i]] = 0;
		}
		if(k){
			-- k;
		}
		int j = sa[rk[i]-1];
		while(i+k <= n && j+k <= n && a[i+k] == a[j+k]){
			++ k;
		}
		he[rk[i]] = k;
	}
	
	for(int i = 1; i <= n; ++ i){
		st[i][0] = he[i];
	}
	for(int i = 1; i <= lg2[n]; ++ i){
		for(int j = 1; j + (1<<i) - 1 <= n; ++ j){
			st[j][i] = min(st[j][i-1], st[j+(1<<(i-1))][i-1]);
		}
	}
}

int ask(int l, int r){
	if(l > r){
		swap(l, r);
	}
	++ l;
	int k = lg2[r - l + 1];
	return min(st[l][k], st[r-(1<<k)+1][k]);
}
int askk(int l, int r){
	if(l > r){
		swap(l, r);
	}
	++ l;
	int k = lg2[r - l + 1];
	return min(stt[l][k], stt[r-(1<<k)+1][k]);
}

int main(){
	lg2[0] = -1;
	for(int i = 1; i <= 50000; ++ i){
		lg2[i] = lg2[i>>1] + 1;
	}
	scanf("%d", &n);
	int ans = 0, lee, stp;
	for(int i = 1; i <= n; ++ i){
		static char ch[5];
		scanf("%s", ch);
		a[i] = ch[0] - 'a' + 1;
	}
	initial();
	suftech();
	reverse(a + 1, a + n + 1);
	memcpy(stt, st, sizeof(st));
	memcpy(saa, sa, sizeof(sa));
	memcpy(rkk, rk, sizeof(rk));
	memcpy(hee, he, sizeof(he));
	initial();
	suftech();
	for(int len = 1; len <= n; ++ len){
		for(int st = 1; st + len - 1 <= n; st += len){
			int r = st + len + askk(rkk[st], rkk[st+len]) - 1;
			int l = st - 1 - ask(rk[n-(st+len-1)+1], rk[n-(st-1)+1]) + 1;
			if(ans < (r-l+1) / len){
				ans = (r-l+1) / len;
				lee = len;
				stp = l;
			}
		}
	}
	printf("%d\n%d\n%d\n", ans, lee, stp);
	return 0;
}
```

---

## 作者：Reunite (赞：3)

简单题。

考虑固定 $k$，考察 $\text{lcp}(i,i+k)=x$，则 $s_{[i,i+x-1]}$ 为 $s_{[i,i+k+x-1]}$ 的 $\text{border}$，该串有长度为 $k$ 的周期，也即存在 $\lfloor \frac{k}{x}\rfloor+1$ 的重复。暴力枚举 $k,i$ 复杂度 $O(n^2)$，考虑优化。

字符串非字典序题，无脑上 $\text{SAM}$，现在只需要考虑一个节点上所有等价类之间的贡献，显然 $x$ 直接取节点的 $len_u$，显然需要最小化 $k$，而这样的 $k$ 只会在相邻的 $\text{endpos}$ 中取得。

因此暴力一点，直接 $\text{set}$ 启发式合并维护 $\text{endpos}$，每次在插入的时候检查相邻元素即可，复杂度 $O(n\log^2 n)$。

还可以更优秀一点，注意到瓶颈在于快速提取所有 $\text{endpos}$ 的本质不同相邻元素，可以使用我在 [P7361 「JZOI-1」拜神](https://www.luogu.com.cn/problem/P7361) 中 [题解](https://www.luogu.com.cn/article/bnnnevki) 提到的爆标做法，使用点分治和离线桶排做到 $O(n\log n)$。笔者实现的是较为简单的 $2\log n$ 做法。

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int n,tot=1,K,L,P;
char c[50005];
int fa[100005];
int len[100005];
int mp[100005][2];
set <int> st[100005];
vector <int> g[100005];

inline int ins(int c,int las){
	if(mp[las][c]){
		int p=las,v=mp[p][c];
		if(len[p]+1==len[v]) return v;
		int x=++tot;
		len[x]=len[p]+1;
		for(int i:{0,1}) mp[x][i]=mp[v][i];
		while(mp[p][c]==v) mp[p][c]=x,p=fa[p];
		fa[x]=fa[v],fa[v]=x;
		return x;
	}
	int x=++tot,p=las;
	len[x]=len[p]+1;
	while(p&&!mp[p][c]) mp[p][c]=x,p=fa[p];
	if(!p) fa[x]=1;
	else{
		int v=mp[p][c];
		if(len[p]+1==len[v]) fa[x]=v;
		else{
			int y=++tot;
			len[y]=len[p]+1;
			for(int i:{0,1}) mp[y][i]=mp[v][i];
			while(mp[p][c]==v) mp[p][c]=y,p=fa[p];
			fa[y]=fa[v],fa[x]=fa[v]=y;
		}
	}
	return x;
}

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

inline void solve(int u){
	int mn=1e9,pos=0;
	for(int v:g[u]){
		solve(v);
		if(st[u].size()>st[v].size()) swap(st[u],st[v]);
		for(int v:st[v]) st[u].insert(v);
		for(int v:st[v]){
			auto it=st[u].find(v);
			if(it!=st[u].begin()){
				int x=*it-*prev(it);
				if(x<mn) mn=x,pos=*prev(it);
			}
			if(next(it)!=st[u].end()){
				int x=*next(it)-*it;
				if(x<mn) mn=x,pos=*it;
			}
		}
	}
	if(K<len[u]/mn+1){
		K=len[u]/mn+1;
		L=mn;
		P=pos-len[u]+1;
	}
	return ;
}

int main(){
	in(n);
	for(int i=1;i<=n;i++){
		char ch[3];
		scanf("%s",ch+1);
		c[i]=ch[1];
	}
	int las=1;
	for(int i=1;i<=n;i++) las=ins(c[i]-'a',las),st[las].insert(i);
	for(int i=2;i<=tot;i++) g[fa[i]].emplace_back(i);
	solve(1);
	printf("%d\n%d\n%d\n",K,L,P);

	return 0;
}
```

---

