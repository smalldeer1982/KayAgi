# Ancient Language

## 题目描述

在探险一个古老的洞穴时，研究人员发现了一堆来自一本书的杂乱的书页。幸运的是，所有的书页都是完整的并且有着自己的页码。所以，研究人员可以将它复原。

在仔细地研究了一遍这些书页后，语言学家认为这可能是一种字典。有趣的是这个古典文明所使用的字母表是英文字母表的一部分，但不是按英文的顺序来的。

给出研究人员已经找到的书页的有关内容，你的任务是用给出的字典上的有关内容还原这个字母表。

## 样例 #1

### 输入

```
3 3
2
b
b
bbac
0
a
aca
acba
1
ab
c
ccb```

### 输出

```
acb```

# 题解

## 作者：__Aaaaaaaa (赞：1)

人话版题面：给定一本书的 $n$ 页，每页 $k$ 个单词，判定它是否是字典，如果是则给出其字典序。

处理这个问题的第一步是把这 $n$ 页展开变成一页，然后再做后面的推理。

我们不妨先想一想给定一个字典序如何比较两个不同的单词（题目原因无需考虑相等）：  
1.比较第 $1$ 个字符，如果不同，谁的第 $1$ 个字符在字典序更靠前谁更小，否则比较第 $2$ 个；  
2.比较第 $2$ 个字符，如果不同，谁的第 $2$ 个字符在字典序更靠前谁更小，否则比较第 $3$ 个；  
3.比较第 $3$ 个字符，如果不同，谁的第 $3$ 个字符在字典序更靠前谁更小，否则比较第 $4$ 个；  
……

既然如此，我们不难发现，如果两个单词前缀相同，而下一个字符不一样，那么就可以进行比较。反过来，也可以根据他们在字典里的相对位置从而判定这对不相同的字母在字典序的相对位置。  
很明显了，如果我确定好了字母在字典序里的相对位置，那么就可以拓扑排序得到结果。

如何确定呢？直接 DFS，DFS 中带三个参数：  
$p$：当前考虑第几个字符；  
$l/r$：在比较第 $p$ 个字符，需保证前提是从第 $l$ 到第 $r$ 个单词的前 $p-1$ 的字符都相等。

这样一来，就可以直接通过 $ [l,r] $ 的单词的第 $p$ 个字母进行确定先后关系然后建图。

由于单词只含小写字母，所以最多只需要 $ 26 \times 26=676 $ 条边即可，处理是否有闭环的情况稍微暴力一点也不会出事，最重要的是建图的 DFS 不能超过时限，还有代码中的亿些细节。

### Don't talk much:
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1010,M=N*N,S=110,C=30;
int h[C],e[C*C],ne[C*C],idx=1;
bool mp[C][C];
int flag;
int ind[C];
void add(int x,int y){//建图
	if(x>=0&&x<26&&y>=0&&y<26&&x!=y){
		if(mp[x][y])return;
		if(mp[y][x])flag=true;
		mp[x][y]=1,ind[y]++;
		e[idx]=y,ne[idx]=h[x],h[x]=idx++;
	}
}
char a[M][S];
int n,k;
void dfs(int p,int l,int r){
	if(flag||l>=r)return;
	bool st[C];
	for(int i=0;i<26;i++)
		st[i]=0;
	char now=a[l][p];
	int tl=l,tr=l;
	for(int i=l+1;i<=r;i++){
		if(a[i][p]==now)
			tr++;
		else{
			dfs(p+1,tl,tr);
			tl=tr=i,now=a[i][p];
			if(st[now-'a']){
				flag=true;
				break;
			}
			add(a[i-1][p]-'a',a[i][p]-'a');//尝试加边
		}
	}
	dfs(p+1,tl,tr);
}
int dis[C];
int q[M],hh,tt;
struct ans{
	int id,dis;
	bool operator<(const ans &tp)const{
		return dis<tp.dis;
	}
}A[C];
int vis[C];
bool live[C];
int id=0;
char ANS[C];
int main(){
	scanf("%d%d",&n,&k);
	for(int i=1,p;i<=n;i++){
		scanf("%d",&p);
		for(int j=p*k+1;j<=p*k+k;j++){//n页展开变成一页
			scanf("%s",a[j]+1);
			for(int k=1;a[j][k];k++)
				live[a[j][k]-'a']=1;//标记哪些是存在的字符，后面要用
		}
	}
	dfs(1,1,n*k);
	if(flag){//在加边的过程中就出现错误，不可能
		puts("IMPOSSIBLE");
		return 0;
	}
	hh=0,tt=-1;
	int ch1=0;
	for(int i=0;i<26;i++){
		if(ind[i]==0){
			q[++tt]=i;
			dis[i]=1;
			vis[i]=1;
		}
		if(live[i])
			ch1++;
	}
	while(hh<=tt){
		int x=q[hh++];
		for(int i=h[x];i;i=ne[i]){
			int j=e[i];
			if(!vis[j]){
				dis[j]=dis[x]+1;
				q[++tt]=j;
				vis[j]=1;
			}
			else if(dis[x]+1>dis[j]){
				dis[j]=dis[x]+1;
				if(dis[j]>=100){//出现环了，不可能
					puts("IMPOSSIBLE");
					return 0;
				}
				q[++tt]=j;
			}
		}
	}
	for(int i=0;i<26;i++)
		A[i]=(ans){i,dis[i]};
	sort(A,A+26);
	for(int i=0;i<26;i++)
		if(live[A[i].id]&&dis[A[i].id]>0)
			ANS[++id]=A[i].id+'a';
	if(id==ch1)//如果不存在闭环，输出答案
		printf("%s\n",ANS+1);
	else
		puts("IMPOSSIBLE");
	return 0;
}
```

---

## 作者：teylnol_evteyl (赞：1)

## 1. 题意描述

一本字典中有 $r$ $(1 \leq r \leq 10^6)$ 个单词，单词长度不超过 $10^3 $，所有字母都是小写英文字母，但字母排序不是按英文字母排序，求所有出现字母的一种排序，如果不存在，输出 "IMPOSSIBLE"。

## 2. 题目分析

由排序规则可知，对于字符串 $s$ 和 $t$，$s$ 排在 $t$ 前面，必是一下两种情况之一：

- $s$ 是 $t$ 前缀。
- 设 $s$ 和 $t$ 第一个不同字符位置为 $i$，则 $s_i$ 的顺序在 $t_i$ 之前。

所以，如果存在字符串 $s$ 和 $t$，$s$ 排在 $t$ 前面但 $t$ 是 $s$ 前缀，则无解；然后可以记录每个导致 $s$ 排在 $t$ 前面的每对字母，判断是否矛盾并求解。

但是这个的时间复杂度是极高的，于是想办法优化。实际上，只需要对比相邻两个字符串即可保证正确性。证明如下：

如果存在字符串 $s$ 和 $t$，$s$ 排在 $t$ 前面但 $t$ 是 $s$ 前缀，且 $s$ 和 $t$ 不相邻，可能会有：

1. $s$ 后一个字符串是 $s$ 前缀，且 $t$ 是这个字符串前缀，可以判断无解。
2. $s$ 后一个字符串不是 $s$ 前缀，且 $t$ 是这个字符串前缀，用归纳法可以证明这种情况会出现矛盾。
3. $t$ 不是 $s$ 后一个字符串的前缀，则在 $s$ 后一个字符串和 $t$ 必然存在一个位置，使两个字符串这个位置上的字符不同，但此时 $s$ 后一个字符串这个位置的字符同时在 $s$ 这个位置的字符之前和之后，就能推出无解。

如果存在字符串 $s$ 和 $t$，$s$ 排在 $t$ 前面，$t$ 不是 $s$ 前缀，可能会有：

1. $s$ 和 $t$ 相邻，直接得到关系。
2. $s$ 后一个字符串是 $s$ 前缀，可推出无解。
3. $s$ 是 $s$ 后一个字符串前缀，可归纳证明可有其它信息得到 $s$ 和 $t$ 能得到的信息。
4. $s$ 后一个字符串和 $s$ 不互相为前缀，且 $s$ 后一个字符串和 $s$ 第一个不相同的位置不在 $s$ 和 $t$ 第一个不相同的位置之前，可归纳证明可有其它信息得到 $s$ 和 $t$ 能得到的信息。
5. $s$ 后一个字符串和 $s$ 不互相为前缀，且 $s$ 后一个字符串和 $s$ 第一个不相同的位置在 $s$ 和 $t$ 第一个不相同的位置之前，归纳法可推出能得到 $s$ 后一个字符串和 $s$ 第一个不相同位置上的字符同时在 $s$ 这个位置上的字符之前和之后，则能推出无解。

综上，所有不相邻的两个字符串，要么可以用其它条件推出无解，要么可以用其它条件推出这两个字符串看获得的信息。

对这些条件分析，只需要用 Floyd 算法求传递闭包，然后如果存在字符 $i$ 在 $i$ 前，则无解；否则每次选出一个不在所有未选择字符之前的数作为插入当前得到顺序开头，则最终可以得到正确顺序。

## 3. 示例代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1005, T = N * N, M = 105, C = 30;

int n, k;
char s[T][M];
bool f[C][C], st[C], ins[C];
char res[C];

int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++ )
	{
		int p;
		scanf("%d", &p);
		for(int j = 1; j <= k; j ++ ) scanf("%s", s[p * k + j] + 1);
	}
	
	for(int i = 1; i <= n * k; i ++ )
	{
		if(i < n * k)
			for(int j = 1; j < M; j ++ )
			{
				if(!s[i][j]) break; // s[i] 是 s[i + 1] 前缀 
				if(!s[i + 1][j]) // s[i + 1] 是 s[i] 前缀 
				{
					puts("IMPOSSIBLE");
					return 0;
				}
				if(s[i][j] != s[i + 1][j]) // s[i + 1] 和 s[i] 第一个不相同字符的位置是 j   
				{
					f[s[i][j] - 'a' + 1][s[i + 1][j] - 'a' + 1] = true; // s[i][j] 在 s[i + 1][j] 之前 
					break;
				}
			}
		for(int j = 1; s[i][j]; j ++ ) ins[s[i][j] - 'a' + 1] = true; // 找到出现的字符  
	}
	
	for(int k = 1; k <= 26; k ++ ) // Floyd 求传递闭包 
		for(int i = 1; i <= 26; i ++ )
			for(int j = 1; j <= 26; j ++ )
				f[i][j] |= f[i][k] & f[k][j];
	
	for(int i = 1; i <= 26; i ++ )
		if(f[i][i]) // i 在 i 之前，无解  
		{
			puts("IMPOSSIBLE");
			return 0;
		}
	
	int cnt = 0;
	for(int i = 1; i <= 26; i ++ ) cnt += ins[i];
	for(int i = 1; i <= cnt; i ++ )
	{
		int c;
		for(int j = 1; j <= 26; j ++ )
			if(ins[j] && !st[j])
			{
				int p = 0;
				for(int k = 1; k <= 26; k ++ )
					p += !st[k] && f[j][k];
				if(!p) // j 不在所有未选出的字符前面 
				{
					c = j;
					break;
				}
			}
		st[c] = true;
		res[cnt - i] = c + 'a' - 1;
	}
	
	puts(res);
	return 0;
}
```

---

## 作者：lgx57 (赞：0)

一眼题。

首先把 $n$ 页书排到一个 vector 里面。

考虑两个字符串的比较过程：

1. 逐位比较字符。如果相等，那么继续比较，否则按照字典的顺序排。
2. 如果一直比较到了其中一个字符串的结尾，那么短的字符串排在前面。

按照这样的方法，我们可以得出一些字符之间的大小关系。

考虑建图。假设字符 $x$ 比 $y$ 小，那么连一条 $x\to y$ 的边。容易知道这肯定是一个 DAG。那么就可以用拓扑排序判断这个图是否为 DAG。

代码中需要注意的细节：

1. 字符串的长度也要判断。
2. 在字典中没有出现的字符不需要在结果中输出。
3. 如果最后有字典中的字符在答案中没有出现，那么也是不可能的。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define pii pair<int,int>
#define endl '\n'
#define pb push_back
#define ls(p) ((p)<<1)
#define rs(p) ((p)<<1|1)
#define lowbit(x) ((x)&(-(x)))
#define abs(x) ((x)>0?(x):(-(x)))
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#define gc getchar
#define pc putchar
#define sz(v) ((int)(v.size()))
using namespace std;
mt19937_64 Rand(chrono::steady_clock::now().time_since_epoch().count());
inline int read(){
	int x=0,f=1;
	char ch=gc();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=gc();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=gc();}
	return x*f;
}
inline void print(int x){
	if (x<0) pc('-'),x*=-1;
	if (x<10) pc(x+'0');
    else print(x/10),pc(x%10+'0');
}
const int N=1005;
vector<string> v[N];
vector<int> p[27];
int deg[N];
bool f[N];
void sol(){
	int n,k;
	cin>>n>>k;
	for (int i=1;i<=n;i++){
		int x;
		cin>>x;
		x++;
		for (int j=1;j<=k;j++){
			string s;
			cin>>s;
			v[x].pb(s);
			for (int _=0;_<sz(s);_++) f[s[_]-'a']=1;
		}
	}
	vector<string> vv;
	for (int i=1;i<=n;i++) for (auto kk:v[i]) vv.pb(kk);
	for (int i=0;i+1<sz(vv);i++){
		string x=vv[i];
		string y=vv[i+1];
		bool ff=0;
		for (int j=0;j<min(sz(x),sz(y));j++){
			if (x[j]!=y[j]){
				p[x[j]-'a'].pb(y[j]-'a');
				deg[y[j]-'a']++;
				ff=1;
				break;
			}
		}
		if (!ff){
			if (sz(x)>sz(y)) return cout<<"IMPOSSIBLE",void();
		}
	}
	vector<int> Ans;
	queue<int> q;
	for (int i=0;i<26;i++){
		if (!f[i]) continue;
		if (!deg[i]) q.push(i);
	}
	int cnt=0;
	for (int i=0;i<26;i++) cnt+=f[i];
	while (!q.empty()){
		int u=q.front();
		q.pop();
		Ans.pb(u);
		for (int v:p[u]){
			if (!(--deg[v])) q.push(v);
		}
	}
	set<int> ss;
	for (int x:Ans){
		ss.insert(x);
	} 
	if (sz(ss)!=sz(Ans)||sz(Ans)!=cnt) return cout<<"IMPOSSIBLE",void();
	else for (int x:Ans) cout<<(char)(x+'a');
}
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t=1;
	while (t--) sol();
	return 0;
}
```

---

