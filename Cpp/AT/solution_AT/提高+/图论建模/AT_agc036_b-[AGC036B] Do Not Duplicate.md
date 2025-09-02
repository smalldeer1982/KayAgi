# [AGC036B] Do Not Duplicate

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc036/tasks/agc036_b

長さ $ N\ \times\ K $ の数列 $ X=(X_0,X_1,\cdots,X_{N\ \times\ K-1}) $ があります。 数列 $ X $ の要素は長さ $ N $ の数列 $ A=(A_0,A_1,\cdots,A_{N-1}) $ によって表され、全ての $ i,j $ ($ 0\ \leq\ i\ \leq\ K-1,\ 0\ \leq\ j\ \leq\ N-1 $) について、 $ X_{i\ \times\ N\ +\ j}=A_j $ です。

すぬけさんは、整数列 $ s $ を持っています。 最初、$ s $ は空です。 すぬけさんはこれから、すべての $ i=0,1,2,\cdots,N\ \times\ K-1 $ について、この順に、以下の操作を行います。

- $ s $ が $ X_i $ を含んでいない場合: $ s $ の末尾に $ X_i $ を追加する。
- $ s $ が $ X_i $ を含んでいる場合: $ s $ が $ X_i $ を含まなくなるまで、$ s $ の末尾の要素を削除し続ける。 このとき、$ X_i $ を末尾に**加えない**ことに注意せよ。

全ての操作が終わったあとの数列 $ s $ の状態を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ K\ \leq\ 10^{12} $
- $ 1\ \leq\ A_i\ \leq\ 2\ \times\ 10^5 $
- 入力される値はすべて整数である。

### Sample Explanation 1

$ X=(1,2,3,1,2,3) $ です。 操作は、以下のように行われます。 - $ i=0 $: $ s $ が $ 1 $ を含まないので、$ s $ の末尾に $ 1 $ を追加する。$ s=(1) $ となる。 - $ i=1 $: $ s $ が $ 2 $ を含まないので、$ s $ の末尾に $ 2 $ を追加する。$ s=(1,2) $ となる。 - $ i=2 $: $ s $ が $ 3 $ を含まないので、$ s $ の末尾に $ 3 $ を追加する。$ s=(1,2,3) $ となる。 - $ i=3 $: $ s $ が $ 1 $ を含むので、$ s $ が $ 1 $ を含む限り、末尾の要素を削除し続ける。$ s $ は $ (1,2,3)→(1,2)→(1)→() $ と変化する。 - $ i=4 $: $ s $ が $ 2 $ を含まないので、$ s $ の末尾に $ 2 $ を追加する。$ s=(2) $ となる。 - $ i=5 $: $ s $ が $ 3 $ を含まないので、$ s $ の末尾に $ 3 $ を追加する。$ s=(2,3) $ となる。

### Sample Explanation 3

数列 $ s $ が空のこともあります。

## 样例 #1

### 输入

```
3 2
1 2 3```

### 输出

```
2 3```

## 样例 #2

### 输入

```
5 10
1 2 3 2 3```

### 输出

```
3```

## 样例 #3

### 输入

```
6 1000000000000
1 1 2 2 3 3```

### 输出

```
```

## 样例 #4

### 输入

```
11 97
3 1 4 1 5 9 2 6 5 3 5```

### 输出

```
9 2 6```

# 题解

## 作者：feecle6418 (赞：4)

预处理出 $nxt_i$ 表示下一个等于 $a_i$ 的位置。

这东西的意义在于，当 $i$ 在栈空时被插入栈后，插入 $nxt_i$ 时栈会再次变空。

因此有一种稍微优秀一点的暴力：

> **暴力** 初始令 $p=1$。每次一直执行 $nxt_p\ \mathrm{mod}\ n+1\to p$，每跨过一次 $n$ 就令 $K$ 减一。假如 $K$ 小于 $5$ 就退出循环，从 $p$ 开始暴力。

假如我们建立有向图，从 $i$ 向 $nxt_i\ \mathrm{mod}\ n+1$ 连边，这个图一定由若干环构成（而不是基环树）。原因：每个点恰有一条入边，一条出边。

因此，设 $d$ 为跳完一次 $1$ 所在的环，跨过 $n$ 的次数，我们可以初始时把 $K$ 对 $d$ 取模，不影响答案。

模了之后，你会发现上面的暴力复杂度就对了，直接跑暴力即可。

复杂度 $O(n)$。代码超好写。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,a[200005],lst[200005],nxt[200005],st[200005],top,is[200005];
ll K;
void Push(int x){
	if(!is[x])st[++top]=x,is[x]=1;
	else {
		while(st[top]!=x)is[st[top--]]=0;
		is[st[top--]]=0;
	}
}
int main(){
	cin>>n>>K;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n;i>=1;i--)lst[a[i]]=i;
	for(int i=n;i>=1;i--)nxt[i]=lst[a[i]],lst[a[i]]=i;
	int p=1,d=0;
	do {
		int q=nxt[p];
		if(q==n)d++;
		if(q<=p)d++;
		p=q%n+1;
	} while(p!=1);
	K%=d;
	while(K>5){
		int q=nxt[p],w=0;
		if(q==n)w++;
		if(q<=p)w++;
		p=q%n+1,K-=w;
	}
	for(int i=p;i<=n;i++)Push(a[i]);
	for(int j=1;j<K;j++)for(int i=1;i<=n;i++)Push(a[i]);
	for(int i=1;i<=top;i++)cout<<st[i]<<' ';
}
```

---

## 作者：Augen_stern (赞：2)

## Part 1：题目大意

原题的大概意思是将一个长度为 $n$ 的序列重复 $k$ 次，构成一个大序列，对于每一个数，若之前存在，则删除第一个存在的数的位置至当前位置，否则它当前存在。

## Part 2：分析求解

考虑模拟，但必定超时。

故考虑优化，我们发现，在不超过 $n$ 次内，会会出现空串，我们可将其称作循环节。

#### 所以第一个子问题：求循环节。
我们记原序列为 ${a}$，当前大序列中储存的元素下标为 ${b}$。

我们可以发现，若要删空序列，即当 $a_{b_{start}}=a_{b_{end}}$，所以我们可以找出每一个元素位置的 $next$，表示若 $i$ 为 $i=b_{start}$，则当 $next_{i}=b_{end}$ 时原序列为空。

代码表示为：

```cpp
	for(int i=0;i<n;i++) {
		maxx=max(maxx,a[i]);
		vst[a[i]].push_back(i);
	}
	for(int i=1;i<=maxx;i++) {
		if(vst[i].size()) {
			for(int j=0;j<vst[i].size()-1;j++) {
				next[vst[i][j]]=vst[i][j+1];
			}
			next[vst[i][vst[i].size()-1]]=vst[i][0];
		}
	}
```

然后从 $1$ 开始模拟，以 $\mathcal{O}(n)$ 的速度，计算出循环节，及当每次 $next_{now}\le now$ 时循环节 $+1$。

具体细节如下：

```cpp
	int u=0,num=0,ci=1;
	vis[0]=1;
	while(1) {
		if(next[u]<=u) ci++;
		u=next[u]+1;
		u%=n;
		if(vis[u]) break;
		vis[u]=1;
	} 
```

#### 第二个子问题：暴力求答案

而解决完循环节后，为了使剩下长度不超过 $n$，对于剩下 $max(0,k-1)$ 个复制序列，我们可以直接 $next$ 跳，值得注意的是最后一个原序列的复制序列不能使用 $next$ ，万一跳过了就悲剧了，所以剩下的还是 $\mathcal{O}(n)$ 。

具体代码如下：

```cpp
	if(ci!=0) k%=ci;
	while(1) {
		if(k==0) break;
		if(k==1) {
			//u
			for(int i=u;i<n;i++) {
				if(vs[a[i]]==0) q[++q[0]]=a[i],vs[a[i]]++;
				else {
					while(vs[a[i]]) {
						vs[q[q[0]]]--;
						q[0]--;
					}
				}
			}
			break;
		}
		if(next[u]<=u&&k>1) k--,u=next[u]+1,u%=n;
		else if(k>1) u=next[u]+1;
	}
```
## Part 3：CODE

话说有两的地方还需要注意：
1. ```long long``` 这玩意儿不加，就会像我一样，对着一个 TLE 且 WA ，有时还 RE 的代码疯狂 DEBUG。
2. next 是个神奇的东西，用了要 CE，这边建议直接 ```#define next Next```。

所以：

```cpp
//#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<math.h>
#include<algorithm>
#include<queue>
#include<map>
#include<vector>
#define INF 0x7fffffff
#define int long long
#define next Next
using namespace std;
vector<int> vst[2000005];
int n,k,maxx;
int a[2000005],next[2000005],vis[2000005],vs[2000005],q[2000005];
signed main() {
	scanf("%lld%lld",&n,&k);
	for(int i=0;i<n;i++) {
		scanf("%lld",&a[i]);
		maxx=max(maxx,a[i]);
		vst[a[i]].push_back(i);
	}
	for(int i=1;i<=maxx;i++) {
		if(vst[i].size()) {
			for(int j=0;j<vst[i].size()-1;j++) {
				next[vst[i][j]]=vst[i][j+1];
			}
			next[vst[i][vst[i].size()-1]]=vst[i][0];
		}
	}// 计算 next 
	int u=0,num=0,ci=1;
	vis[0]=1;
	while(1) {
		if(next[u]<=u) ci++;
		u=next[u]+1;
		u%=n;
		if(vis[u]) break;
		vis[u]=1;
	}// 循环节 
	if(ci!=0) k%=ci;
	while(1) {
		if(k==0) break;
		if(k==1) {
			//u
			for(int i=u;i<n;i++) {
				if(vs[a[i]]==0) q[++q[0]]=a[i],vs[a[i]]++;
				else {
					while(vs[a[i]]) {
						vs[q[q[0]]]--;
						q[0]--;
					}
				}
			}
			break;
		}// 最后一个不能跳 
		if(next[u]<=u&&k>1) k--,u=next[u]+1,u%=n;
		else if(k>1) u=next[u]+1;
	}
	for(int i=1;i<=q[0];i++) {
		printf("%lld ",q[i]);
	}
	return 0;
}
```



---

## 作者：StrSeeker (赞：0)

原题的大概意思是将一个长度为 $n$ 的序列重复 $k$ 次，构成一个大序列，对于每一个数，若之前存在，则删除第一个存在的数的位置至当前位置，否则将它加入序列尾端。

模拟必定超时，故考虑优化，发现在不超过 $n+1$ 次操作内，一定会出现重复，我们可将其称作循环节。

开栈存序列，如果当前栈内第一个元素为 $x$，则下一次栈空即为下一次遇到 $x$。所以预处理出每个 $a_i$ 下一个和它相同的位置，假设为 $j$，那么可将 $i$ 向 $j+1$ 连边，即下次栈首元素为 $a_{j+1}$。

### 题解 1

倍增从每个元素出发跳了 $2^i$ 步之后所在位置，直至超过 $n \times k$。从 $a_1$ 开始考虑每个元素，跳若干步直到还差一步超过 $n \times k$。记当前位置为 $a_i$，若 $i\lt nk$，输出这个元素，然后考虑 $a_{i+1}$，重复上述过程。

复杂度：$O(n\log(nk))$。

### 题解 2

可以证明最后连出的一定是若干个环而不是基环内向树，因为每个点有唯一出边且有唯一入边。

也就是说 $1$ 一定可以走回 $1$，一定存在循环节，环长度最大是 $n$，而对于 $k$ 来说，循环节长度最大为 $n+1$。

所以在环上暴力跑出循环节，将 $k$ 对循环节长度取模后，剩下的在环上暴力跑，多出来的一点也暴力跑就好。

复杂度：$O(n)$。

代码仅供参考。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define N 1050500
int lst[N],nxt[N],a[N],top,sta[N],cnt[N],n,k;
void insert(int x){
    if(cnt[x]){
        while(cnt[x])cnt[sta[top--]]--;
    }
    else cnt[sta[++top]=x]++;
}
signed main(){
    ios::sync_with_stdio(false);
    cin>>n>>k;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=n;i;--i)lst[a[i]]=i;
    for(int i=n;i;--i)nxt[i]=lst[a[i]],lst[a[i]]=i;
    int now=1,cnt=0;
    do{
        int ver=nxt[now];
        if(ver==n)++cnt;
        if(now>=ver)++cnt;
        now=ver%n+1;
    }while(now!=1);
    k%=cnt;
    while(k>2)
    {
        int ver=nxt[now];
        if(ver==n)--k;
        if(now>=ver)--k;
        now=ver%n+1;
    }
    for(int i=now;i<=n;i++)insert(a[i]); 
    for(int c=1;c<k;c++)for(int i=1;i<=n;i++)insert(a[i]);
    for(int i=1;i<=top;i++)cout<<sta[i]<<" ";
} 
```

---

## 作者：Lnsk (赞：0)

- 预处理：$nxt_i$ 表示 $a_i$ 之后的第一个等于 $a_i$ 的值的位置。
- 找环：先定义 $x=1$，循环 $y=nxt_i$，当 $y$ 大于 $n$ 或小于等于 $x$ 时，就说明跳到了下一次发送的沝沝，$d$ 加一，然后更新 $x$ 为 $y\bmod n+1$，直到 $x$ 回到 $1$，退出循环，$d$ 就是循环节的长度。
- 模拟：将 $k$ 模掉 $d$，剩下的接着 $x$ 模拟就行了。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 200005
int n,a[MAXN],nxt[MAXN],last[MAXN];
long long m;
bool f[MAXN];
stack<int> st,sta;
vector<vector<int> > v;
vector<int> x,ans;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=n;i>=1;i--)last[a[i]]=i;
	for(int i=n;i>=1;i--)nxt[i]=last[a[i]],last[a[i]]=i;
	int x=1,y,d=0;
	while(1){
		y=nxt[x];
		if(y==n)d++;
		if(y<=x)d++;
		x=y%n+1;
		if(x==1)break;
	}
	m%=d;
	while(m>5){
		d=0,y=nxt[x];
		if(y==n)d++;
		if(y<=x)d++;
		x=y%n+1;
		m-=d;
	}
	for(int i=x;i<=n&&m;i++){
		if(f[a[i]]){
			f[a[i]]=0;
			while(!st.empty()&&st.top()!=a[i])f[st.top()]=0,st.pop();
			st.pop();
		}else{
			f[a[i]]=1;
			st.push(a[i]);
		}
	}
	while(m&&--m){
		for(int i=1;i<=n;i++){
			if(f[a[i]]){
				f[a[i]]=0;
				while(!st.empty()&&st.top()!=a[i])f[st.top()]=0,st.pop();
				st.pop();
			}else{
				f[a[i]]=1;
				st.push(a[i]);
			}
		}
	}
	while(!st.empty())sta.push(st.top()),st.pop();
	while(!sta.empty())cout<<sta.top()<<' ',sta.pop();
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

### 题目大意
将一个长度为 $n$ 的序列重复 $k$ 次，构成一个大序列，对于每一个数，若之前存在，则删除第一个存在的数的位置至当前位置，否则将它加入序列尾端。

### 题解
我们发现：在不超过 $n+1$ 次操作内，一定会出现重复，我们可将其称作循环节。

如果当前栈内第一个元素为 $x$，则下一次栈空即为下一次遇到 $x$。所以预处理出每个 $a_i$ 下一个和它相同的位置，假设为 $j$，那么可将 $i$ 向 $j+1$ 连边，即下次栈首元素为 $a_j+1$。

可以证明最后连出的一定是若干个环而不是基环内向树，因为每个点有唯一出边且有唯一入边。

也就是说 $1$ 一定可以走回 $1$，一定存在循环节，环长度最大是 $n$，而对于 $k$ 来说，循环节长度最大为 $n+1$。

所以在环上暴力跑出循环节，将 $k$ 对于循环节长度取余后，剩下的在环上暴力跑，多出来的一点也暴力跑就好。

复杂度： $O(n)$。

### AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<long long> v[2000005];
long long n,k,maxn;
long long a[2000005],b[2000005],c[2000005],p[2000005],q[2000005];
void check(long long x){
	for(long long i=x;i<n;i++){
		if(p[a[i]]==0){
			q[++q[0]]=a[i];
			p[a[i]]++;
		}
		else{
			while(p[a[i]]){      
				p[q[q[0]]]--;
				q[0]--;
			}
		}
	}
} 
int main(){
	cin>>n>>k;
	for(long long i=0;i<n;i++){
		cin>>a[i];
		maxn=max(maxn,a[i]);
		v[a[i]].push_back(i);
	}
	for(long long i=1;i<=maxn;i++){
		if(v[i].size()){
			for(long long j=0;j<v[i].size()-1;j++){
				b[v[i][j]]=v[i][j+1];
			}
			b[v[i][v[i].size()-1]]=v[i][0];
		}
	}
	long long u=0,s=1;
	c[0]=1;
	while(1){
		if(b[u]<=u)s++;
		u=(b[u]+1)%n;
		if(c[u])break;
		c[u]=1;
	}
	if(s!=0)k%=s;
	while(1){
		if(!k)break;
		if(k==1){
			check(u);
			break;
		}
		if(b[u]<=u&&k>1){
			k--;
			u=(b[u]+1)%n;
		}
		else if(k>1)u=b[u]+1;
	}
	for(long long i=1;i<=q[0];i++)cout<<q[i]<<" ";
	return 0;
}
```


---

