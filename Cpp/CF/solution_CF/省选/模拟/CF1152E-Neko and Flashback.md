# Neko and Flashback

## 题目描述

长度为 $k$ 的排列是指从 $1$ 到 $k$ 的整数中，每个整数恰好出现一次的一个序列。例如，序列 $[3, 1, 2]$ 是长度为 $3$ 的一个排列。

当 Neko 五岁时，他想出了一个长度为 $n$ 的正整数数组 $a$ 和一个长度为 $n-1$ 的排列 $p$。然后，他进行了如下操作：

- 构造长度为 $n-1$ 的数组 $b$，其中 $b_i = \min(a_i, a_{i+1})$。
- 构造长度为 $n-1$ 的数组 $c$，其中 $c_i = \max(a_i, a_{i+1})$。
- 构造长度为 $n-1$ 的数组 $b'$，其中 $b'_i = b_{p_i}$。
- 构造长度为 $n-1$ 的数组 $c'$，其中 $c'_i = c_{p_i}$。

例如，如果数组 $a$ 为 $[3, 4, 6, 5, 7]$，排列 $p$ 为 $[2, 4, 1, 3]$，那么 Neko 会构造出如下数组：

- $b = [3, 4, 5, 5]$
- $c = [4, 6, 6, 7]$
- $b' = [4, 5, 3, 5]$
- $c' = [6, 7, 4, 6]$

然后，他把 $b'$ 和 $c'$ 两个数组写在了一张纸上，之后就忘记了。14 年后，当他在打扫房间时，发现了这张写有 $b'$ 和 $c'$ 的旧纸条。然而，他已经不记得当初的数组 $a$ 和排列 $p$ 了。

如果 Neko 当时算错了，导致不存在数组 $a$ 和排列 $p$ 能够得到这样的 $b'$ 和 $c'$，请输出 $-1$。否则，请帮他还原出任意一个可能的数组 $a$。

## 说明/提示

第一个样例的解释见题面。

在第三个样例中，对于 $a = [3, 4, 5, 2, 1, 4, 3, 2]$，一种可能的排列 $p$ 为 $[7, 1, 5, 4, 3, 2, 6]$。此时，Neko 会构造出如下数组：

- $b = [3, 4, 2, 1, 1, 3, 2]$
- $c = [4, 5, 5, 2, 4, 4, 3]$
- $b' = [2, 3, 1, 1, 2, 4, 3]$
- $c' = [3, 4, 4, 2, 5, 5, 4]$

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
4 5 3 5
6 7 4 6
```

### 输出

```
3 4 6 5 7 
```

## 样例 #2

### 输入

```
3
2 4
3 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
8
2 3 1 1 2 4 3
3 4 4 2 5 5 4
```

### 输出

```
3 4 5 2 1 4 3 2 
```

# 题解

## 作者：Suzt_ilymtics (赞：8)

[更好的阅读体验？](https://www.cnblogs.com/Silymtics/p/solution-CF1152E.html)

### Description

[题目传送](https://www.luogu.com.cn/problem/CF1152E)

题目翻译好像有点问题，应该改为，

$$b_i = \min \{a_i, a_{i+1} \}$$

$$c_i = \max \{a_i, a_{i+1} \}$$

### Solution

先说做法，欧拉路径。

如果不知道什么是欧拉路径，可以去看一下这个[模板题](https://www.luogu.com.cn/problem/P7771)。

其实这个做法通过观察样例就能看出来。

其实 $p$ 序列没啥用，唯一的用处就是让你可以打乱这个 $b,c$ 序列，实现过程中不需要考虑它。

考虑欧拉回路正确性，对于一对 $b_i, c_i$，一定分别对应着 $a_i,a_{i+1}$ 的两个值，可以看做是两个点连边，而 $b_{i+1}$ 和 $c_{i+1}$ 又能将 $a_{i+1}$ 和 $a_{i+2}$ 连接。最后整个 $a$ 序列就是一条由每一对 $b_i,c_i$ 连起来的合法的欧拉路径。

对了，虽然 $b,c$ 序列的值域是 $10^9$，但离散化一下就好了。

剩下的就是判断不合法（无解）情况：

- $b_i > c_i$，这个通过样例二就能看出来，并且 $\min \{a_i, a_{i+1} \} > \max \{a_i, a_{i+1} \}$ 这本来就是不合法的。
- 还有就是 $b,c$ 序列没有构成欧拉路径，这个可以根据度数为奇数的点的数量来判断，只有 $0$ 和 $2$ 的情况是合法的。
- 当然图可能不连通，所以我们只 `dfs` 一遍，如果栈中的元素不等于 $n$，也是无解的。

这里建议用 `vector` 存边，并且用数组 $now$ 来记录当前点遍历到了那条边，下次经过的时候可以跳过前面已经遍历过的边，达到优化复杂度的效果，以防被卡到 $O(m^2)$。

注意一对 $b_i,c_i$ 所连的边是双向边，`vector` 本身是不方便同时对一对边标记的，不过我们可以对每条边多存一个信息 $id$ （表示它是第几条边）来解决。

### Code

```cpp
/*
Work by: Suzt_ilymics
Problem: 不知名屑题
Knowledge: 垃圾算法
Time: O(能过)
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define LL long long
#define orz cout<<"lkp AK IOI!"<<endl

using namespace std;
const int MAXN = 3e5+5;
const int INF = 1e9+7;
const int mod = 1e9+7;

struct node {
    int v, id;
};

int n;
int b[MAXN], c[MAXN];
int date[MAXN], date_num = 0, Cnt = 0;
vector<node> e[MAXN];
int now[MAXN], du[MAXN];
int stc[MAXN], sc = 0;
bool vis[MAXN];

int read(){
    int s = 0, f = 0;
    char ch = getchar();
    while(!isdigit(ch))  f |= (ch == '-'), ch = getchar();
    while(isdigit(ch)) s = (s << 1) + (s << 3) + ch - '0' , ch = getchar();
    return f ? -s : s;
}

void dfs(int u) {
    for(int M = e[u].size(); now[u] < M; ) {
        node v = e[u][now[u]++];
        if(vis[v.id]) continue;
        vis[v.id] = true;
        dfs(v.v);
    }
    stc[++sc] = u;
}

int main()
{
    n = read();
    for(int i = 1; i < n; ++i) date[++date_num] = b[i] = read();
    for(int i = 1; i < n; ++i) date[++date_num] = c[i] = read();
    for(int i = 1; i < n; ++i) {
        if(b[i] > c[i]) {
            puts("-1");
            return 0;
        }
    }
    sort(date + 1, date + date_num + 1), date[0] = -INF;
    for(int i = 1; i <= date_num; ++i) if(date[i] != date[i - 1]) date[++Cnt] = date[i];
    for(int i = 1; i < n; ++i) {
        b[i] = lower_bound(date + 1, date + Cnt + 1, b[i]) - date;
        c[i] = lower_bound(date + 1, date + Cnt + 1, c[i]) - date;
        e[b[i]].push_back((node){c[i],i}), du[c[i]]++;
        e[c[i]].push_back((node){b[i],i}), du[b[i]]++;
    }
    int js = 0;
    for(int i = 1; i <= Cnt; ++i) if(du[i]&1) js++;
    if(js != 0 && js != 2) {
        puts("-1");
        return 0;
    }
    bool flag = false;
    for(int i = 1; i <= Cnt; ++i) {
        if(du[i] & 1) {
            dfs(i);
            flag = true;
            break;
        }
    }
    if(!flag) dfs(1);
    if(sc != n) puts("-1");
    else while(sc) printf("%d ", date[stc[sc--]]);
    return 0;
}
```

---

## 作者：KEBrantily (赞：4)

这题题目有点问题，应该是 $b_i=\min\{a_i,a_{i+1}\}$，$c_i$ 同理。  
不过没什么影响。
- - -

根据题目可以发现，$b_i$ 是 $a_i,a_{i+1}$ 中较小的那个，而 $c_i$ 是较大的。

所以 $b_i>c_i$ 时无解。

观察一下样例，可以发现答案就是从某个数开始取，再取另一个序列中的同位置的数，然后转到这个同位置数的另一个出现位置，重复上述操作。

所以我们要找从哪个数开始取。

我们要保证每个数都被取一次，而且是按上述方式不间断地取。  

可以发现这个过程类似于找欧拉路径的过程。

那我们对于每一对 $(b_i,c_i)(i\in[1,n-1])$ 连无向边，然后按找欧拉路径的方法判断一下有无解以及起点，最后输出即可。

```cpp
bool flag,vis[maxn];
int n,cnt,m,top,st,_js;
int du[maxn],base[maxn],c[maxn];
int zhan[maxn],d[maxn],a[maxn],b[maxn];
struct node{int pos,num;};
vector<node> g[maxn];

void dfs(int u){
  for(int i=d[u];i<g[u].size();i=d[u]){
    d[u]++;node to=g[u][i];
    if(vis[to.num]) continue;
    vis[to.num]=1;dfs(to.pos);
  }
  zhan[++top]=u;
}

int main(){
  n=read();
  for(int i=1;i<n;i++) base[++cnt]=b[i]=read();
  for(int i=1;i<n;i++) base[++cnt]=c[i]=read();
  sort(base+1,base+cnt+1);
  int tot=unique(base+1,base+cnt+1)-base-1;
  for(int i=1;i<n;i++){
    b[i]=lower_bound(base+1,base+tot+1,b[i])-base;
    c[i]=lower_bound(base+1,base+tot+1,c[i])-base;
    if(b[i]>c[i]) return puts("-1"),0;
    int u=b[i],v=c[i];du[u]++;du[v]++;
    g[u].push_back((node){v,i});
    g[v].push_back((node){u,i});
  }
  for(int i=1;i<=tot;i++) _js+=(du[i]&1);
  if(_js&&_js!=2) return puts("-1"),0;
  if(!_js) dfs(1);
  else for(int i=1;i<=tot;i++) 
    if(du[i]&1){dfs(i);break;}
  if(top^n)return puts("-1"),0;
    for(int i=top;i>=1;i--)
      printf("%d ",base[zhan[i]]);
  return 0;
}
```

---

## 作者：ljc20020730 (赞：3)

显然对于$b,c$两个数组所描述的数一定是相邻两个数。

也就是说给出这两个数组的目的是告诉选手那两个数是被放在相邻位置的。

对于第$i$组要求,表示数$b_i$和数$c_i$出于相邻位置，于是我们将其建一条无向边。

显然如果构成一组合法的序列，那么这些限制都需要满足，自然想到了欧拉路径（不重复经过所有边）

现在，这条路径上点表示的数就是所求的序列。

于是，我们只需要将点权离散化Fleury跑欧拉路径即可，复杂度大概是O(E)

这里只有$n-1$条边，所以总复杂度是$O(n)$

注意，图可能不是欧拉图，甚至不连通，甚至输入就不合法($a_i > b_i$)在这些情况下直接输出-1即可。

```
# include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int du[N],a[N],b[N],t[N],Path[N],T,n;
vector<int>V[N];
int Ls(int x){return lower_bound(t+1,t+1+T,x)-t;}
int Rl(int x){return t[x];}
void adde(int u,int v)
{
    //printf("adde : %d %d\n",u,v);
    V[u].push_back(v);
    V[v].push_back(u);
    du[u]++; du[v]++;
}
void del(int u,int v)
{
    //printf("del %d %d\n",u,v);
    for (int i=0;i<V[u].size();++i)
     if (V[u][i]==v) {
         V[u].erase(V[u].begin()+i);
         break;
     }
    for (int i=0;i<V[v].size();++i)
     if (V[v][i]==u) {
         V[v].erase(V[v].begin()+i);
         break;
     }
}
void dfs(int u)
{
    //printf("u = %d \n",u);
    for (int i=0;i<V[u].size();++i) {
        int v=V[u][i]; del(u,v); dfs(v);
    } 
    Path[++Path[0]]=u;
}
int main()
{
    scanf("%d",&n); 
    for (int i=1;i<=n-1;i++) scanf("%d",&a[i]),t[++t[0]]=a[i];
    for (int i=1;i<=n-1;i++) scanf("%d",&b[i]),t[++t[0]]=b[i];
    for (int i=1;i<=n-1;i++) 
        if (a[i]>b[i])  { puts("-1"); return 0;}    
    sort(t+1,t+1+t[0]);
    T=unique(t+1,t+1+t[0])-t-1;
    for (int i=1;i<=n-1;i++)
     adde(Ls(a[i]),Ls(b[i]));
    bool flag=false; int cnt=0;
    for (int i=1;i<=n;i++)
     if (du[i]%2==1) cnt++;
    if (cnt!=0&&cnt!=2) { puts("-1"); return 0;}
    for (int i=1;i<=n;i++)
     if (du[i]%2==1) { flag=true; dfs(i); break;}
    if (flag==false) dfs(1);
    if (Path[0]!=n) { puts("-1"); return 0;    }  
    for (int i=1;i<=Path[0];i++) 
     printf("%d ",Rl(Path[i]));
    puts("");  
    return 0;
}
```

---

## 作者：phil071128 (赞：1)

**Neko and Flashback**

欧拉路径，duel 的时候做的题，因为双方都忘了板子故平局。

问题可以转换为，将每个 $b,c$ 看作一个二元组后重排。观察样例，不难发现重排后合法，当且仅当对于对于每一步 $i\to i+1$，$c_i=c_{i+1},c_{i}=b_{i+1},b_{i}=b_{i+1},b_{i}=c_{i+1}$ 四者至少成立一个。

转换一下条件，我们对于每一组 $(b,c)$ 之间连无向边，那么这样的一条路径合法，当且仅当这 $n$ 条边都被经过，因此转换为欧拉路径问题。

对于 $b>c$ 的情况特判一下无解。
注意当前弧优化， 复杂度容易写假。

```cpp
for(int i=head[x];i<s[x].size();i++) 
    head[x]=i;
for(int i=head[x];i<s[x].size();i=head[x]) {
	head[x]=i+1;
```

前者复杂度会退化到 $O(m^2)$。



```cpp
#include <bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int read(){
	char c=getchar();int h=0,tag=1;
	while(!isdigit(c)) tag=(c=='-'?-1:1),c=getchar();
	while(isdigit(c)) h=(h<<1)+(h<<3)+(c^48),c=getchar();
	return h*tag;
}
void fil(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
}
stack<int>q; 
const int N=5e5+50;
int low[N],b[N],deg[N];
pii a[N];
map<pii,int>mp;
vector<int>s[N];
void dfs(int x) {
//	cout<<x<<endl;
	for(int i=low[x];i<s[x].size();i=low[x]) {
		low[x]=i+1;
		int y=s[x][i];
//		cout<<mp[pii(x,y)]<<" "<<q.size()<<endl; 
		if(mp[pii(x,y)]>0) {
			mp[pii(x,y)]--,mp[pii(y,x)]--;
			dfs(y);
		}
	}
	q.push(x);
//	for(int i=low[x];i<s[x].size();i=low[x]) {
//		low[x]=i+1;
//		if(mp[pii(u,v)])
//		dfs(s[x][i]);
//	}
//	q.push(x);
}
void work() {
	int n=read(),cnt=0;
	for(int i=1;i<n;i++) a[i].fi=read();
	for(int i=1;i<n;i++) a[i].se=read();
	
	for(int i=1;i<n;i++) {
		b[++cnt]=a[i].fi,b[++cnt]=a[i].se;	
	}
	sort(b+1,b+1+cnt);
	int tot=unique(b+1,b+1+cnt)-b-1;
	for(int i=1;i<=tot;i++) low[i]=deg[i]=0;
	for(int i=1;i<n;i++) {
		a[i].fi=lower_bound(b+1,b+1+tot,a[i].fi)-b;
		a[i].se=lower_bound(b+1,b+1+tot,a[i].se)-b;
	}
	for(int i=1;i<n;i++) {
		if(a[i].fi>a[i].se) {
			puts("-1");return ;
		}
		s[a[i].fi].push_back(a[i].se);
		s[a[i].se].push_back(a[i].fi);
		deg[a[i].fi]++;deg[a[i].se]++; 
		mp[pii(a[i].fi,a[i].se)]++;
		mp[pii(a[i].se,a[i].fi)]++;
	}
	int st=0,ed=0;
	for(int i=1;i<=tot;i++) {
		if(deg[i]%2==1) {
			if(!st) st=i;
			else if(!ed) ed=i;
			else {
				puts("-1");return ;
			}
		}
	}
	if(st==0) st=1;
	dfs(st);
	if(q.size()!=n) {
		puts("-1");return ;
	}
	while(!q.empty()) {
		cout<<b[q.top()]<<" ";q.pop();
	}
	cout<<"\n";
	
}
int main(){
//	fil();
	int T=1;while(T--) work();
	return 0;
}

```

---

## 作者：mulberror (赞：1)

# 自己写的所有题解
[【传送门】](https://www.cnblogs.com/chhokmah/p/10768012.html)  
# 题解
其实还是一道水题。。。
比较容易就可以得出题目中给出$P$数组是没有用的。  
输入中给出的$b'$和$c'$一定是相邻的两个数。  
也就是${b'}_i$和${c'}_i$是相邻的。  

我们需要还原$a$数组，也就是需要符合以上所有$b'$和$c'$的限制。  
容易想到就是用欧拉路径实现。  

坑点盘点：  
* 建出的图可能不连通。
* 可能存在环中路径。
* 需要离散化。

# 代码
```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 2e5 + 5;
int a[N], b[N], c[N], d[N], disc[N], de[N], point[N], ans[N];
int n, dcnt = 0, acnt = 0, pcnt = 0; 
multiset<int> g[N];
template <typename T> void read(T &x) {
    x = 0; T fl = 1; char ch = 0;
    for (; ch < '0' || ch > '9'; ch = getchar()) if (ch == '-') fl = -1;
    for (; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
    x *= fl;
}
void dfs(int u) {
	if (de[u] == 0) { ans[++ acnt] = u; return; }
	for (auto i = g[u].begin(); i != g[u].end(); i = g[u].begin()) {
		int v = *i;
		g[u].erase(i); 
		g[v].erase(g[v].find(u)); de[u] --, de[v] --; 
		dfs(v); 
	}
	ans[++ acnt] = u;
}
signed main() {
	read(n);
	for (int i = 1; i <= n; i ++) g[i].clear();
	for (int i = 1; i < n; i ++) read(a[i]), disc[++ dcnt] = a[i];
	for (int i = 1; i < n; i ++) read(b[i]), disc[++ dcnt] = b[i];
	for (int i = 1; i < n; i ++) if (a[i] > b[i]) { cout << -1 << endl; return 0; }
	sort(disc + 1, disc + 1 + dcnt);
	dcnt = unique(disc + 1, disc + 1 + dcnt) - disc - 1;
	for (int i = 1; i < n; i ++) {
		c[i] = lower_bound(disc + 1, disc + 1 + dcnt, a[i]) - disc;
		d[i] = lower_bound(disc + 1, disc + 1 + dcnt, b[i]) - disc;
	}
	for (int i = 1; i < n; i ++) {
		g[c[i]].insert(d[i]); g[d[i]].insert(c[i]);
		de[c[i]] ++; de[d[i]] ++;
	}
	for (int i = 1; i <= n; i ++) 
		if (de[i] & 1) point[++ pcnt] = i;
	if (pcnt != 0 && pcnt != 2) { cout << -1 << endl; return 0; }
	acnt = 0; 
	if (pcnt == 0) dfs(1); else dfs(point[1]);
	if (acnt != n) { cout << -1 << endl; return 0; }
	for (int i = 1; i <= acnt; i ++) printf("%d ", disc[ans[i]]); 
	return 0;
}
```

---

## 作者：GJX_Algorithm (赞：0)

# CF1152E 题解
## 前置知识
- 离散化。

- 欧拉路径和欧拉回路。

## 解题思路
### 有解情况
- 首先代入题面公式：

$$
b_i' = b_{p_i} = \min(a_{p_i}, a_{p_{i+1}})
$$

$$
c_i' = c_{p_i} = \max(a_{p_i}, a_{p_{i+1}})
$$

- 我们可以发现，如果 $b_i' = a_{p_i}$，那么一定有 $c_i' = a_{p_{i+1}}$，反之亦然。

- 这时我们就可以把 $b_i'$ 和 $c_i'$ 看作 $a_{p_i}$ 和 $a_{p_{i+1}}$ 连边，且因为我们不能确定 $b_i'$ 和 $c_i'$ 是 $a_{p_i}$ 和 $a_{p_{i+1}}$ 其中的哪一个，所以建的图是无向图。

- 建完图后就能发现，这张图的欧拉路径（欧拉回路）就是数组 $a$ 啦！

- 最后由于 $2 \le n \le 10^5, 1\le b_i' , c_i' \le 10^9$，需要把数列 $b, c$ 离散化。

### 无解情况
#### 无向图欧拉路径本身就有的两种无解情况：
- 度数为奇数的点既不是 0 个，也不是 2 个。

- 该图不连通。

#### 由题意得出的无解情况：
- $b_i' > c_i'$，即 $\min(a_{p_i}, a_{p_{i+1}}) > \max(a_{p_i}, a_{p_{i+1}})$。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
int n, m;
int b[N], b1[N], c[N];
int cnt, du[N], stk[N], head[N];
bool vis[N];
struct node
{
    int e, to;
};
vector<node> nbr[N];
void dfs(int cur) //优化过的无向图欧拉路径，时间复杂度：O(m)
{
	for (int i = head[cur]; i < nbr[cur].size(); i = head[cur])
	{
		int nxt = nbr[cur][i].to, id = nbr[cur][i].e;
        head[cur] = i + 1; //枚举过就不用再枚举了，下次如果再次搜到这个点循环就直接从下一个开始，确保严格O(m)
        if (vis[id] == 0) //vis标记边，每条边只去一次
        {
            vis[id] = 1;
            dfs(nxt);
        }
	}
	stk[++cnt] = cur;
	return ;
}
void discrete() //离散化
{
    sort(b1 + 1, b1 + (2 * m) + 1);
    int len = unique(b1 + 1, b1 + (2 * m) + 1) - (b1 + 1);
    for (int i = 1; i <= m; i++)
    {
        b[i] = lower_bound(b1 + 1, b1 + len + 1, b[i]) - b1;
        c[i] = lower_bound(b1 + 1, b1 + len + 1, c[i]) - b1;
    }
    return ;
}
int main()
{
    int start = 1;
    cin >> n;
    m = n - 1;
    for (int i = 1; i <= m; i++) cin >> b[i], b1[i] = b[i];
    for (int i = 1; i <= m; i++) cin >> c[i], b1[i + m] = c[i];
    discrete();
    for (int i = 1; i <= m; i++)
    {
        if (b[i] > c[i]) //第三种无解情况
        {
            cout << -1;
            return 0;
        }
        nbr[b[i]].push_back({i, c[i]});
        nbr[c[i]].push_back({i, b[i]});
        du[b[i]]++, du[c[i]]++;
    }
    int flag = 0;
	for (int i = 1; i <= n; i++)
        if (du[i] % 2 == 1)
            start = i, flag++;
    if (flag != 0 && flag != 2) //第一种无解情况
    {
        cout << -1;
        return 0;
    }
	dfs(start);
    if (cnt != n) //第二种无解情况
    {
        cout << -1;
        return 0;
    }
	for (int i = cnt; i >= 1; i--) cout << b1[stk[i]] << " ";
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)

对于一个 $i$，有 $b_i=\min\{a_i,a_{i+1}\},c_i=\max\{a_i,a_{i+1}\}$，也就是说 $b_i,c_i$ 各是 $a_i,a_{i+1}$ 其中的一个（当然需要 $b_i\le c_i$，否则无解）。 注意这个输出方式，$p$ 的作用是将 $a$ 排列，也就是说我们只需要求出 $a$ 有哪些数组成即可。将给定的 $a_i,a_{i+1}$ 的关系看成一条无向边，走过这个路径就相当于满足了一个限制条件。那么在图上找出欧拉路，就可以得到一个满足所有的限制条件的序列 $a$（需要先离散化后再建图）。时间复杂度 $O((n+m)\log m)$。

```cpp

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int n, tot, cur[100005], deg[200005], st[200005];
int b[100005], c[100005], B[200005];
vector<int> edges;
vector<int> G[200005];
inline void addedge(int u, int v) {
    edges.emplace_back(v); G[u].emplace_back(edges.size() - 1);
    ++deg[v];
}

void dfs(int x) {
    for (; cur[x] < G[x].size(); ++cur[x]) {
        int y = edges[G[x][cur[x]]];
        if (y) {
            edges[G[x][cur[x]]] = 0, edges[G[x][cur[x]] ^ 1] = 0;
            dfs(y);
        }
    }
    st[++tot] = x; 
}

int main(void) {
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) scanf("%d", b + i), B[++tot] = b[i];
    for (int i = 1; i < n; ++i) scanf("%d", c + i), B[++tot] = c[i];
    sort(B + 1, B + tot + 1); tot = unique(B + 1, B + tot + 1) - (B + 1);
    for (int i = 1; i < n; ++i) {
        b[i] = lower_bound(B + 1, B + tot + 1, b[i]) - B;
        c[i] = lower_bound(B + 1, B + tot + 1, c[i]) - B; 
        if (b[i] > c[i]) return puts("-1"), 0;
        addedge(b[i], c[i]); addedge(c[i], b[i]);
    }
    int cnt = 0, h = 0;
    for (int i = 1; i <= tot; ++i) if (deg[i] & 1) {
        ++cnt;
        if (!h) h = i;
    }
    if (cnt == 1 || cnt > 2) return puts("-1"), 0;
    tot = 0; dfs(h ? h : 1);
    if (tot != n) return puts("-1"), 0;
    for (int i = tot; i >= 1; --i) printf("%d ", B[st[i]]);
    putchar('\n');
    return 0;
}
```

---

## 作者：little_cindy (赞：0)

这是蒟蒻的第一篇黑题题解，望管理员通过qwq。

## 思路

### （奇妙的）思路

其实从样例看得出来，这就是一道欧拉路径的题，不过还需要离散化。

然后就做完了。

### （正经的）思路
简单的推一下柿子就可以知道，$p$ 数组没有一点用，纯粹是能够让你打乱每组 $(b_i,c_i)$ 的顺序，你可以看做一条边。

由于 $b_i=\min(a_i,a_{i+1}),c_i=\max(a_i,a_{i+1})$，若 $a$ 数组从小到大排列，所以 $c_i=b_{i+1}$，就可以理解为从 $b_i$ 到 $c_i$（也就是 $b_{i+1}$）再到 $c_{i+1}$。

由于题目只要求我们构造一组可行解，我们就可以假定 $a$ 数组从小到大排列。那么，我们就把 $b$ 数组和 $c$ 数组的每一项的权值看做点的编号。

但是注意题目数据范围：$1\le b_i,c_i\le10^9$，所以我们需要离散化一下。

## code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
template <typename T> inline void read(T& x) {
	x=0;T f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x=x*f;
	return;
}
template <typename T,typename ...Arg>void read(T& x,Arg& ...arg){
	read(x);
	read(arg...);
}
template <typename T>inline void write(T x) {
	if(x<0)putchar('-'),x=-x;
	if(x<10)putchar(x+'0');
	else write(x/10),putchar(x%10+'0');
}
template <typename T,typename ...Arg>void write(T& x,Arg& ...arg){
	write(x);
	putchar(' ');
	write(arg...);
}
const int maxn=3e5+5;
int n;
int ans[maxn],cnt,d[maxn],a[maxn],b[maxn];
struct node{
	int val,id;
};
vector<node> nbr[maxn];
int head[maxn];
bool vis[maxn];
void dfs(int i){
	for(int j=head[i];j<nbr[i].size();j=head[i]){
		head[i]++;
		if(!vis[nbr[i][j].id]){
			vis[nbr[i][j].id]=1;
			dfs(nbr[i][j].val);
		}
	}
	ans[++cnt]=i;
	return;
}
int LSH[maxn<<1];
int main(){	
	read(n);
	int CNT=0;
	for(int i=1;i<n;i++){
		cin>>a[i];
		LSH[++CNT]=a[i];
	}
	for(int i=1;i<n;i++){
		cin>>b[i];
		LSH[++CNT]=b[i];
		if(a[i]>b[i]){
			cout<<"-1";
			return 0;
		}
	} 
    //离散化开始
	sort(LSH+1,LSH+CNT+1);
	LSH[0]=-1e9-7;
	int num=0;
	for(int i=1;i<=CNT;i++){
		if(LSH[i]!=LSH[i-1]){
			LSH[++num]=LSH[i];
		}
	}
	for(int i=1;i<n;i++){
		a[i]=lower_bound(LSH+1,LSH+1+num,a[i])-LSH;
		b[i]=lower_bound(LSH+1,LSH+1+num,b[i])-LSH;
		nbr[a[i]].push_back({b[i],i});//建边
		nbr[b[i]].push_back({a[i],i});
		d[a[i]]++;//统计度数
		d[b[i]]++;
	}
    //离散化结束
	int sum=0;
	for(int i=1;i<=num;i++){
		if(d[i]&1){
			sum++;
		}
	}
	if(sum!=0&&sum!=2){//无解
		cout<<"-1";
		return 0;
	}
	bool flag=0;
	for(int i=1;i<=num;i++){
		if(d[i]&1){
			dfs(i);
			flag=1;
			break;
		}
	}
	if(!flag)dfs(1);
	if(cnt!=n){
		cout<<"-1";
		return 0;
	}
	for(int i=cnt;i>=1;i--){//输出答案
		cout<<LSH[ans[i]]<<' ';
	}
	return 0;
}

```

---

