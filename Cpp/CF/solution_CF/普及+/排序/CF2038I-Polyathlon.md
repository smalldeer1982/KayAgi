# Polyathlon

## 题目描述

伯兰（Berland）是今年国际大学生多项全能比赛的主办国！与双项全能是两个项目的比赛类似，多项全能是多个项目的比赛。今年有 $m$ 个项目。此外，还有 $n$ 名参赛者。项目编号从 $1$ 到 $m$ ，参赛者编号从 $1$ 到 $n$ 。

有些参赛者擅长多项运动。我们还知道，对于每一对参与者来说，至少存在一种运动，即其中一人擅长该运动，而另一人不擅长。

比赛项目的顺序在开幕式上决定。从历史上看，它是由万能的随机数生成器决定的。掷出一个从 $1$ 到 $m$ 的随机数 $x$ 。比赛从 $x$ 开始，然后是 $(x \bmod m + 1)$ ，接着是 $((x + 1) \bmod m + 1)$ ，以此类推。

每个项目的比赛规则如下。如果剩下的所有参赛者（所有尚未被淘汰的参赛者）都不擅长该项目，则所有人都进入下一个项目。否则，所有熟练的参赛者都进入下一个项目，所有不熟练的参赛者都被淘汰出局。一旦比赛只剩下一名参赛者，比赛即告结束，该参赛者即为获胜者。

作为比赛的组织者，您事先对比赛可能出现的结果很好奇。对于每个运动项目 $x$ ，如果比赛从运动项目 $x$ 开始，请打印获胜者的编号。

## 样例 #1

### 输入

```
3 5
10010
01100
10101```

### 输出

```
3 2 3 1 3```

# 题解

## 作者：Y2y7m (赞：3)

没道理紫啊。

我们先将每一行的字符串复制一遍放在这个字符串后面。

我们考虑这个从第 $i$ 个比赛开始进行比赛淘汰的过程实际上是将所有字符串从第 $i$ 个位置切开，然后取出字典序最大的那个字符串，这个字符串即为赢家。

所以我们每次都通过二分哈希求字典序最大的即可，复杂度 $O(mn\log{m})$。

---

## 作者：鳶一折纸 (赞：3)

不妨将举行第 $i$ 个项目时的选手看成从第 $i$ 列向后循环到第 $i-1$ 列组成的 $n$ 个长度 $m$ 的串。

不难发现，第 $i$ 列的获胜者即为这 $n$ 个串中字典序最大的一个。

将第 $n$ 位作为第 $n$ 个关键字，第一位作为第 $1$ 关键字，用 LSD 基数排序的思想计算出第 $1$ 列所有选手的排名，然后我们考虑动态维护这个排名来计算剩余列的答案。

从第 $i$ 列转移到第 $i-1$ 列，每次相当于将串的最后一位移动到第一位并成为新的第 $1$ 关键词，继续基数排序即可。

最终我们可以用 $\mathcal O(nm)$ 的复杂度计算出第 $1$ 列 的答案，再用 $\mathcal O(nm)$ 的复杂度计算出剩余 $m-1$ 列的答案。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, m, tot;
int a[N], b[N], ans[N];
vector<vector<int>> sq;
string s;
signed main()
{
	ios::sync_with_stdio(0);
	cin >> n >> m;
	sq.resize(n + 1);
	for (int i = 1; i <= n; ++i)
	{
		cin >> s, sq[i].resize(m + 1), a[i] = i;
		for (int j = 1; j <= m; ++j)
			sq[i][j] = s[j - 1] - '0';
	}
	for (int i = m; i >= 1; --i)
	{
		tot = 0;
		for (int j = 1; j <= n; ++j)
			if (sq[a[j]][i])
				b[++tot] = a[j];
		for (int j = 1; j <= n; ++j)
			if (!sq[a[j]][i])
				b[++tot] = a[j];
		for (int j = 1; j <= n; ++j)
			a[j] = b[j];
	}
	ans[1] = a[1];
	for (int i = m; i >= 2; --i)
	{
		tot = 0;
		for (int j = 1; j <= n; ++j)
			if (sq[a[j]][i])
				b[++tot] = a[j];
		for (int j = 1; j <= n; ++j)
			if (!sq[a[j]][i])
				b[++tot] = a[j];
		for (int j = 1; j <= n; ++j)
			a[j] = b[j];
		ans[i] = a[1];
	}
	for (int i = 1; i <= m; ++i)
		cout << ans[i] << " ";
	return 0;
}
```

---

## 作者：Reunite (赞：3)

这里是赛时非正解做法。话说这题是被榜带歪了吧。

考虑阈值分治，记 $V=nm=2\times 10^6$，设一个阈值 $B$。对于 $n\le B$ 的时候，考虑如下做法：枚举一对点 $(i,j)$，我们想知道在哪些位置开始一轮比赛才不会让 $i$ 被淘汰，也就是所有 $a_{i,x}=1,a_{j,x}=0$ 的位置 $x$，到环上之前第一个 $a_{i,x}=0,a_{j,x}=1$ 的位置是合法的。因为保证每个位置被扫描和覆盖最多一次，复杂度 $O(n^2m)=O(BV)$。

否则 $n>B$，直接模拟题意是 $O(nm^2)$ 的，但是可以 bitset 优化，但是它是静态定长的很烦。注意到此时 $m>\log B$，所以 bitset 只需要开到 $\frac{nm}{\log B}$，复杂度 $O(\frac{nm^2}{\omega \log B})=O(\frac{V^2}{B\omega\log B})$。

近似一下，平衡 $B$ 即可做到 $O(V\sqrt{\frac{V}{\omega \log V}})$。可以适当加一下诸如 $n\le B$ 的部分对枚举 $j$ 的顺序随机打乱，对 $n>B$ 的部分再次阈值分治优化一下 bitset 长度等等。

```cpp
#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <bitset>
#include <random>
#include <ctime>
using namespace std;

mt19937 rnd(time(NULL));
int n,m,B=400;
char c[1000005];
int ans[1000005];
vector <bool> a[1000005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
}

namespace sub1{
	int id[10005];
	bool ok[1000005];
	bool oo[1000005];
	inline void work(){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++) ok[j]=1;
			for(int j=1;j<=n;j++) id[j]=j;
			shuffle(id+1,id+1+n,rnd);
			for(int j=1;j<=n;j++){
				int x=id[j];
				if(i==x) continue;
				for(int k=1;k<=m;k++) oo[k]=0;
				for(int k=1;k<=m;k++){
					if(a[x][k]) continue;
					if(a[x][k]==a[i][k]) continue;
					int pos=k;
					while(1){
						if(a[x][pos]&&!a[i][pos]) break;
						oo[pos]=ok[pos];
						pos--;
						if(pos==0) pos=m;
						if(pos==k) break;
					}
				}
				bool ko=0;
				for(int k=1;k<=m;k++) ok[k]=oo[k],ko|=ok[k];
				if(!ko) break;
			}
			for(int j=1;j<=m;j++) if(ok[j]) ans[j]=i;
		}
		for(int i=1;i<=m;i++) printf("%d ",ans[i]);
		return ;
	}
}

namespace sub2{
	inline void work1(){
		bitset <100005> f,g;
		bitset <100005> aa[5005];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) aa[j][i]=a[i][j];
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++) f[j]=1;
			int x=i;
			while(1){
				g=f&aa[x];
				if(g.any()) f=g;
				x=x%m+1;
				if(x==i) break;
			}
			x=0;
			for(int j=1;j<=n;j++) if(f[j]) x=j;
			printf("%d ",x);
		}

		return ;
	}
	inline void work2(){
		bitset <5005> f,g;
		bitset <5005> aa[5005];
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) aa[j][i]=a[i][j];
		for(int i=1;i<=m;i++){
			for(int j=1;j<=n;j++) f[j]=1;
			int x=i;
			while(1){
				g=f&aa[x];
				if(g.any()) f=g;
				x=x%m+1;
				if(x==i) break;
			}
			x=0;
			for(int j=1;j<=n;j++) if(f[j]) x=j;
			printf("%d ",x);
		}

		return ;
	}
	inline void work(){
		if(n<=5000) work2();
		else work1();
		return ;
	}
}

int main(){
	in(n),in(m);
	for(int i=1;i<=n;i++){
		a[i].resize(m+1);
		// for(int j=1;j<=m;j++) a[i][j]=(i+j)&1;
		// for(int j=1;j<=m;j++) a[i][j]=1;
		// a[i][i]=0;
		scanf("%s",c+1);
		for(int j=1;j<=m;j++) a[i][j]=c[j]-'0';
	}
	if(n<=B){sub1::work();return 0;}
	sub2::work();

	return 0;
}
```

---

## 作者：Register_int (赞：2)

黄题。

题目描述可以表示为字典序最大的一个人赢。而对于 0/1 串来说，字典序等价于两个二进制数的大小关系。考虑断环为链，直接对于每个长度，比较所有 0/1 串对应长度的后缀即可。

你发现二进制帮你拆好了，枚举顺序甚至从低往高，那你直接基数排序是不是做完了？具体的，用一个数组从大到小存所有串，新加一位把 1 往前放、0 往后放即可。

复杂度 $O(nm)$。很难理解怎么带上 $\log$ 的。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e6 + 10;

int n, m, ans[MAXN << 1];

char s[MAXN]; vector<int> a[MAXN], f, g;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s), a[i].resize(m * 2);
		for (int j = 0; j < m; j++) a[i][j] = a[i][m + j] = s[j] - '0';
	}
	for (int i = 1; i <= n; i++) f.emplace_back(i);
	for (int j = m * 2 - 1; ~j; j--) {
		for (int x : f) if (a[x][j]) g.emplace_back(x);
		for (int x : f) if (!a[x][j]) g.emplace_back(x);
		f = g, g.clear(), ans[j] = f[0];
	}
	for (int j = 0; j < m; j++) printf("%d ", ans[j]);
}
```

---

## 作者：IdnadRev (赞：1)

感觉这个"不难发现"对于我来说还是太难发现了，讲一个不需要这个观察的做法。

断环为链是显然的，我们只需在序列上，考虑求出以每个起点 $s$ 向后走的答案。

我们的目标是设计一个复杂度只与 $n$ 有关的做法（先前已经枚举 $O(m)$ 的内容），于是可以考虑每次删去至少一个候选者。为达成这一目标，我们知道所有的全零、全一运动是没有用的，我们需要快速跳到下一个零一皆有的运动，也就是找到第一个时刻，每个候选者的字符串开始不同。

对于“不同”，一个比较常见的设计方法是对于所有相邻候选者算第一个不同的时刻，其最小值也就是我们所需的下一个时刻。这也是我们做法的核心思路——用链表维护所有剩余候选者，对于每对相邻候选者，计算其第一个不同的时刻（可以通过二分+哈希算出）。接下来我们用堆维护这些时刻，每次从堆中取出所有对应最小时刻的候选者，并将不符合的候选者删去。

可以发现删去每个候选者仅需 $O(\log n+\log m)$ 的复杂度，因此总复杂度 $O(nm(\log n+\log m))$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2000005;
int n,m;
int pre[maxn],suc[maxn],del[maxn];
vector<int>g[maxn];
vector<unsigned long long>sum[maxn];
priority_queue< pair<int,pair<int,int>> >q;
unsigned long long ps[maxn];
mt19937_64 rnd(time(0));
string s;
int findlcp(int a,int b,int st) {
	int L=st-1,R=m+m+1;
	while(L+1<R) {
		int mid=(L+R>>1);
		if(sum[a][mid]-sum[a][st-1]!=sum[b][mid]-sum[b][st-1])
			R=mid;
		else L=mid;
	}
	return R;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m+m; i++)
		ps[i]=rnd();
	for(int i=1; i<=n; i++) {
		cin>>s;
		sum[i].resize(m+m+1),g[i].resize(m+m+1);
		for(int j=0; j<m; j++) {
			g[i][j+1]=g[i][j+m+1]=s[j]-48;
			if(s[j]=='1')
				sum[i][j+1]=ps[j+1],sum[i][j+m+1]=ps[j+m+1];
		}
		for(int j=1; j<=m+m; j++)
			sum[i][j]+=sum[i][j-1];
	}
	for(int X=1; X<=m; X++) {
		for(int i=1; i<=n; i++)
			pre[i]=i-1,suc[i]=i+1,del[i]=0;
		suc[0]=1,pre[n+1]=n;
		for(int i=1; i<n; i++)
			q.push(make_pair(-findlcp(i,i+1,X),make_pair(i,i+1)));
		while(!q.empty()) {
			int tm=-q.top().first,p1=q.top().second.first,p2=q.top().second.second;
			while(del[p1]||del[p2]) {
				q.pop();
				if(q.empty())
					break;
				tm=-q.top().first,p1=q.top().second.first,p2=q.top().second.second;
			}
			if(q.empty())
				break;
//			printf("tm=%d\n",tm);
			vector<int>W;
			W.emplace_back(p1),W.emplace_back(p2);
			q.pop();
			while(!q.empty()&&-q.top().first==tm) {
				p1=q.top().second.first,p2=q.top().second.second;
				while(del[p1]||del[p2]) {
					q.pop();
					if(q.empty()||-q.top().first!=tm)
						break;
					p1=q.top().second.first,p2=q.top().second.second;
				}
				if(q.empty()||-q.top().first!=tm)
					break;
				W.emplace_back(p1),W.emplace_back(p2);
				q.pop();
			}
			for(int i=0; i<W.size(); i++)
				if(del[W[i]]==0&&g[W[i]][tm]==0) {
					int x=W[i];
					pre[suc[x]]=pre[x],suc[pre[x]]=suc[x],del[x]=1;
					if(pre[x]>=1&&suc[x]<=n)
						q.push(make_pair(-findlcp(pre[x],suc[x],X),make_pair(pre[x],suc[x])));
				}
		}
		printf("%d%c",suc[0],X==m? '\n':' ');
	}
	return 0;
}
```

---

## 作者：madfallen (赞：0)

模拟赛被全班爆切，建议降绿。

破环为链。很明显胜出者就是字典序最大的那一个。开一个 set 给编号赋值，从后往前枚举后缀，该位是 1 就往前放，该位是 0 就往后放。怎么做到这一点呢？每次扫完把各个编号按大小赋值 $1 \sim n$，如果该位是 1 就加上一个极大值。扫到 $\leq m$ 的时候把 set 里第一个的编号作为答案就好了。

记得使用较快的读入，吃了一发。

```c++
#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdio>
#include<vector>
#include<string>
#include<set>
using namespace std;
const int inf=2e7;
const int N=2e5;
const int M=2e6;
string s[N+5];
int n,m;
struct node{
	int id,val;
	node(){};
	node(int id,int val){
		this->id=id;
		this->val=val;
	}
	bool operator<(const node &x)const{
		return val==x.val?id<x.id:val>x.val;
	}
};
set<node>p,q;
int ans[M+5];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>s[i],s[i]+=s[i];
	for(int i=1;i<=n;i++)p.insert(node(i,0));
	for(int i=2*m-1;~i;i--){
		while(p.size()){
			node now=*p.begin();p.erase(p.begin());
			if(s[now.id][i]=='1')now.val+=inf;
			q.insert(now);
		}
		int u=n;
		while(q.size()){
			node now=*q.begin();q.erase(q.begin());
			now.val=u--;
			p.insert(now);
		}
		node an=*p.begin();
		if(i<m)ans[i]=an.id;
	}
	for(int i=0;i<m;i++)cout<<ans[i]<<" ";
}

```

---

## 作者：xyz105 (赞：0)

$$\begin{Bmatrix}\color{red}\LARGE\bold{Solution}\\\normalsize\texttt{No.016 }\bold{CF2038I}\end{Bmatrix}\times\footnotesize\texttt{ By Xyz105}$$


### 前言

**短代码**预警！这是代码长度 **小于 1 KB** 的极简做法。

是的你没有看错。我都很怀疑这题真的有没有 *2500，并且~~本人发现怎么题解区代码都这么长啊？~~


### 题目描述

以下描述相较于现有翻译更偏形式化。

给定 $n$ 个长度为 $m$ 的 $\texttt{01}$ 串，这些字符串两两不同，不妨将其编号为 $s_1,s_2,\ldots,s_n$。

现在你可以通过以下规则，淘汰掉 $n-1$ 个字符串，选出最终获胜的那个字符串：
- 选定一个位置 $p$（$1\le p\le m$）。如果在所有未被淘汰的字符串中，存在至少一个字符串，它的第 $p$ 位为 $\texttt{1}$，则将剩下的第 $p$ 位为 $\texttt{0}$ 的字符串全部淘汰；否则不进行淘汰操作。  
  之后如果幸存的字符串仍多于一个，则令 $p\gets (p \bmod m)+1$，重复执行上述操作。

试求出将 $p$ 的初始值定为 $1,2,\ldots,m$ 时，获胜的字符串编号。


### 解题思路

设 $s_{i,j}$ 表示 $s_i$ 向左循环移位 $(j-1)$ 次后得到的新字符串。

于是就有了较显然的转化：如果确定了 $p$ 的初始值，那么第 $i$ 个字符串能获胜，当且仅当 $s_{i,p}$ 在所有 $s_{1,p},s_{2,p},\ldots,s_{n,p}$ 中字典序最大。感性理解，字典序越大意味着字符 $\texttt{1}$ 越有可能出现在偏左的位置，该字符串更容易幸存。

于是 $p$ 初始值为 $1$ 的做法就很显然了：给所有 $s_i$ 排序，字典序最大的字符串的编号就是答案。考虑直接**暴力上 `sort`**，时间复杂度是 $O(nm\log m)$ 的，完全可以接受。代码片段如下：

```cpp
pair<string, int> a[MAXN]; string s[MAXN];

for (int i = 1; i <= n; i++) cin >> s[i], a[i].first = s[i], a[i].second = i;
sort(a + 1, a + n + 1), ans[1] = a[n].second;
```

是的，就是这么简单粗暴。

考虑求出 $p$ 初始值为 $m,m-1,\ldots,2$ 时的答案。这个时候对于每个 $p$ 都做一遍上述求法显然是会 TLE 的。

但是好消息是，咱们可以通过 $p=j+1$ 时的排序结果，用 $O(n)$ 的时间推出 $p=j$ 时的排序结果。（准确来说，先从 $p=1$ 推到 $p=m$，再从 $p=m$ 推到 $p=m-1,m-2$ 等等）

当 $s_{i,j}$ 从 $s_{i,j+1}$ 变过来时，发现它只是将最后一个字符向前提到了第一个的位置。  
将所有的 $s_{i,j+1}$ 都删去最后一个字符，它们的大小关系不变；但为了变成 $s_{i,j}$，有些串要在最前面添加 $\texttt{0}$，有些串则是添加 $\texttt{1}$。  
但你会发现，如果只考虑最前面添加 $\texttt{0}$ 的字符串，它们的相对大小关系不变；最前面添加 $\texttt{1}$ 的同理；另外，添加 $\texttt{0}$ 的字符串的字典序必然小于添加 $\texttt{1}$ 的。于是有如下代码：

```cpp
for (int i = 1; i <= n; i++) b[i] = a[i].second;
for (int i = m; i > 1; i--)
{
	int cnt = 0;
	for (int j = 1; j <= n; j++) if (s[b[j]][i - 1] == '0') tmp[++cnt] = b[j];
	for (int j = 1; j <= n; j++) if (s[b[j]][i - 1] == '1') tmp[++cnt] = b[j];
	for (int j = 1; j <= n; j++) b[j] = tmp[j];
	ans[i] = b[n];
}
```

其中 `b[]` 记录将 $s_{1,i},s_{2,i},\ldots,s_{n,i}$ 从小到大排序后，它们相应的编号（$s_{j,i}$ 中的 $j$ 这一维）。

于是就做完了，就这么简单。总复杂度 $O(nm\log n)$。


### 参考代码

[Submission on Codeforces](https://codeforces.com/contest/2038/submission/293640492)。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;

int n, m, ans[MAXN], b[MAXN], tmp[MAXN];

pair<string, int> a[MAXN]; string s[MAXN];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) cin >> s[i], a[i].first = s[i], a[i].second = i;
	sort(a + 1, a + n + 1), ans[1] = a[n].second;
	
	for (int i = 1; i <= n; i++) b[i] = a[i].second;
	for (int i = m; i > 1; i--)
	{
		int cnt = 0;
		for (int j = 1; j <= n; j++) if (s[b[j]][i - 1] == '0') tmp[++cnt] = b[j];
		for (int j = 1; j <= n; j++) if (s[b[j]][i - 1] == '1') tmp[++cnt] = b[j];
		for (int j = 1; j <= n; j++) b[j] = tmp[j];
		ans[i] = b[n];
	}
	for (int i = 1; i <= m; i++) printf("%d ", ans[i]);
	
	return 0;
}
```

---

## 作者：TTpandaS (赞：0)

首先破环成链，然后对于 $x=i$ 的答案，就是寻找以 $i$ 作为起点，长度为 $m$ 的字典序最大的串的编号。

考虑用哈希判断字典序，首先二分出最长公共前缀，然后判断下一位大小即可。这样就是 $O(n \log^2 n)$ 的。但是二分最长公共前缀时可以先手动比较前 $k$ 位大小，再卡卡常，实测 $k=25$ [可过](https://codeforces.com/contest/2038/submission/293216648)。

---

## 作者：_jimmywang_ (赞：0)

这 *2500？

观察条件，比如从第一个运动开始比，胜者即字典序最大者。那么从第 $x$ 个位置开始，胜者就是左轮换 $x-1$ 次后的字典序最大者。

考虑动态维护这个次序。假设我们已经做完了 **从第 $i$ 位开始的结果**，思考如何将他变为**从第 $i+1$ 位开始结果**。

这个过程中每个串的变化就是把第一个字符挪到最后去了。观察到第 $i$ 位上是 1 的串之间已经有序，第 $i$ 位上是 $0$ 的串之间也已经有序。于是我们归并排序即可。单轮比较次数 $O(n)$。那么总比较次数就是 $O(nm)$。

然而我比较蠢，使用初级的 hash+ 二分进行比较，那么算上第一轮要快排一遍，总复杂度是 $O(nm\log n)$，能过。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define f(i,a,b) for(ll i=a;i<=b;i++)
#define wt int tt=d;while(tt--)
#define py puts("Yes")
#define pn puts("No")
#define pritnf printf
#define edfl endl
#define fe(i,e) for(int i=0;i<e.size();i++)
#define vi vector<ll>
inline ll rd() {
	ll x=0,f=1;
	char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x*f;
}
namespace binom{
	const ll Lim=300010,mod=998244353;
	ll jc[Lim],inv[Lim],inc[Lim];
	void pre(){
		jc[0]=jc[1]=inc[0]=inc[1]=inv[0]=inv[1]=1;
		f(i,2,Lim-1)jc[i]=jc[i-1]*i%mod,inv[i]=(mod-mod/i)*inv[mod%i]%mod,
		inc[i]=inc[i-1]*inv[i]%mod;
	}ll C(ll n,ll m){if(n<0||m<0||n<m)return 0;return jc[n]*inc[m]%mod*inc[n-m]%mod;}
}
// using namespace binom;
ll dx[4]={0,1,0,-1};
ll dy[4]={1,0,-1,0};
#define d rd()
#define pb push_back
const ll N=300010;
struct edge{ll v,w,nx;}e[N<<1];
ll hd[N],cnt;
void add(ll u,ll v,ll w){e[++cnt]=(edge){v,w,hd[u]};hd[u]=cnt;}
ll qp(ll a,ll b,ll p){
	ll ans=1;while(b){
		if(b&1)ans=ans*a%p;
		a=a*a%p;b>>=1;
	}return ans;
}ll n,m;
string s[2000010];
vector<ll>h[2000010];
const ll mod=1000000009;
ll pw[2000010];
ll get(ll id,ll l,ll r){
    return (h[id][r]-pw[r-l+1]*h[id][l-1]%mod+mod)%mod;
}
bool cmp(ll x,ll y,ll st){
	if(get(x,st,m)==get(y,st,m))return cmp(x,y,1);
	ll l=st,r=m;
	while(l<r){
		ll mid=l+r>>1;
		if(get(x,st,mid)==get(y,st,mid))l=mid+1;
		else r=mid;
	}
	return s[x][l-1]=='1';
}
ll rk[2000010];
bool Cmp(const ll &x,const ll &y){
	return cmp(x,y,1);
}
ll x[2000010],y[2000010];
ll lx,ly;
int main(){
	n=d,m=d;
	pw[0]=1;f(i,1,2000000)pw[i]=pw[i-1]*3%mod;
	f(i,1,n){h[i].resize(m+1);
		cin>>s[i];rk[i]=i;
		f(j,1,m)h[i][j]=(h[i][j-1]*3+s[i][j-1]-'0'+1)%mod;
	}
	sort(rk+1,rk+n+1,Cmp);
	cout<<rk[1]<<" ";
	f(i,2,m){
		lx=0,ly=0;
		f(j,1,n)if(s[rk[j]][i-2]=='1')x[++lx]=rk[j];else y[++ly]=rk[j];
		ll qwq=0,ix=1,iy=1;
		while(ix<=lx&&iy<=ly){
			if(cmp(x[ix],y[iy],i))rk[++qwq]=x[ix++];
			else rk[++qwq]=y[iy++];
		}
		while(ix<=lx)rk[++qwq]=x[ix++];
		while(iy<=ly)rk[++qwq]=y[iy++];
		cout<<rk[1]<<" ";
	}
	return 0;
}
```

---

## 作者：Jelly_prx (赞：0)

# I. Polyathlon

来自[2024-2025 ICPC, NERC, Southern and Volga Russian Regional Contest](https://codeforces.com/contest/2038)

将题意快进到对每个后缀，求出字典序最大的串的编号。（证明显然）。

>假设某个人 $i$ 在第 $k$ 轮淘汰了人 $j$，那么在有 $\forall x\in[1,k-1],s_{i,x}=s_{j,x}\& s_{i,k}>s_{j,k}$，相当于 $i$ 的字典序大于 $j$，然后 $j$ 就没用了。
>
>那么对于字典序最大的那个人，肯定不存在某个人能够淘汰它。
>
>事实上在断环成链后你并不需要严格截断 $m$ 个位置，因为保证有解，直接取整个后缀比较即可。

### sol1

首先第一反应是 hash+二分，这样复杂度就是 $O(nm\log m)$ 的。但是发现你被卡麻了，于是你需要放弃断环成链，人工特判，使用冷门质数做到只用单 hash，然后就可卡过。

### sol2

于是就想，这题可能是线性吗？事实上快速求两个后缀的排名我们有后缀排序，这样我们将所有串拼起来，然后做一遍 SA，比较直接拎出它们的排名即可。但是这样你发现有个问题：你不会 $O(n)$ 求 SA！

一个想法是你可以从 LOJ 上地一个跑得快一点的板子，另一个想法是你可以看看这个：[《如何优雅的用SAM构造SA数组 - 洛谷专栏》](https://www.luogu.com.cn/article/e3li2g9u)（里面的图是贺的），并将其中的 dfs 换成人工栈（因为它甚至卡栈空间）。

### sol3

感觉太不巧妙了！

思考一下，你要对每个后缀都求一遍排名，是不是得到了许多大量的排名信息，但这些信息你并没有加以利用。

我们考虑倒着做！

具体地，我们假设现在要比较 $i,j$ 两个串后缀 $[k,m]$ 的大小，我们先比较 $s_{i,k},s_{j,k}$ 的大小，若相同那么问题就变成了比较 $s_{i,[k+1,m]},s_{j,[k+1,m]}$ 的大小，但这个问题我们已经做过了！

直接使用 sort 虽然还是 $O(nm\log n)$ 的，但是因为常数小可以轻松跑过。

但是我们不妨直接使用基数排序，这样复杂度就简单地变为了 $O(nm)$ 的了。其实这个本质上就是对 $n$ 个大整数进行排序，而基数排序天然支持得到从低位往高位排序时，排到某一位的排名情况。

---

## 作者：wangif424 (赞：0)

比 D 简单。

考虑 $m$ 个人的能力构成的 `01` 串，不难发现胜者一定是字典序最大的那个，证明如下：

- 若都为零或都为一，则都进入下一轮。即字符串的一位相同比较下一位。

- 否则，为一的胜出，为零的出局。即 $0\lt1$。

于是用哈希维护 `01` 串，二分比较即可，时间复杂度 $O(nm\log n)$。

## AC 代码

[赛时提交纪录](https://codeforces.com/contest/2038/submission/292194973)

```cpp
#include <bits/stdc++.h>
#define R(x) x = read()
#define int long long
#define double long double
#define pii pair<int,int>
#define sqrt sqrtl
using namespace std;
using strint=basic_string<int>;
char pbuf[1<<20], *pp=pbuf;
inline void push(const char &c){(pp-pbuf==1<<20)?fwrite(pbuf,1,1<<20,stdout),pp=pbuf,*pp++=c:*pp++=c;}
class io {public:~io() {fwrite(pbuf, 1, pp - pbuf, stdout);}} _;
inline void write(int x) {
    x<0&&(push('-'),x=-x);
    static int sta[60]={},top=0;
    do{sta[top++]=x%10,x/=10;}while(x);
    while(top)push(sta[--top]^'0');
}
inline int read() {
    int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){ch=='-'&&(f=-1);ch=getchar();}
    while(isdigit(ch)) x=x*10+(ch^48),ch=getchar();
    return x*f;
}
constexpr int N=2e6+100,mod=1e9+9;
int base;
mt19937 rd(time(0));
int n,m;
string a[N];
vector<int>h[N];
int p[N];
int hsh(int x,int l,int r){
    return (h[x][r]-(h[x][l-1]*p[r-l+1])%mod+mod)%mod;
}
int getans(int be){
    int x=1;
    for(int j=2;j<=n;j++){
        if(a[x].at(be)!=a[j].at(be)){
            if(a[x].at(be)=='0')x=j;
            continue;
        }
        int l=be,r=a[j].size()-2;
        while(l<r){
            int mid=(l+r+1)>>1;
            if(hsh(x,be,mid)==hsh(j,be,mid))l=mid;
            else r=mid-1;
        }
        if(a[x].at(l+1)=='0')x=j;
    }
    return x;
}
void solve(){
    base=rd()%911+1;
    p[0]=1;
    for(int i=1;i<N;i++)p[i]=p[i-1]*base%mod;
    R(n);R(m);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]+=a[i];
        a[i]=' '+a[i];
    }
    for(int i=1;i<=n;i++){
        h[i].emplace_back(0);
        for(int j=1,s=a[i].size();j<s;j++){
            int hi=h[i].back();
            h[i].emplace_back((hi*base+(a[i].at(j)))%mod);
        }
    }
    for(int i=1;i<=m;i++){
        write(getans(i));push(' ');
    }
}
signed main(){
    int T;
    T=1;
    while(T--)solve();    
    return 0;
}
```

---

