# Restructuring Company

## 题目描述

Even the most successful company can go through a crisis period when you have to make a hard decision — to restructure, discard and merge departments, fire employees and do other unpleasant stuff. Let's consider the following model of a company.

There are $ n $ people working for the Large Software Company. Each person belongs to some department. Initially, each person works on his own project in his own department (thus, each company initially consists of $ n $ departments, one person in each).

However, harsh times have come to the company and the management had to hire a crisis manager who would rebuild the working process in order to boost efficiency. Let's use $ team(person) $ to represent a team where person $ person $ works. A crisis manager can make decisions of two types:

1. Merge departments $ team(x) $ and $ team(y) $ into one large department containing all the employees of $ team(x) $ and $ team(y) $ , where $ x $ and $ y $ ( $ 1<=x,y<=n $ ) — are numbers of two of some company employees. If $ team(x) $ matches $ team(y) $ , then nothing happens.
2. Merge departments $ team(x),team(x+1),...,team(y) $ , where $ x $ and $ y $ ( $ 1<=x<=y<=n $ ) — the numbers of some two employees of the company.

At that the crisis manager can sometimes wonder whether employees $ x $ and $ y $ ( $ 1<=x,y<=n $ ) work at the same department.

Help the crisis manager and answer all of his queries.

## 样例 #1

### 输入

```
8 6
3 2 5
1 2 5
3 2 5
2 4 7
2 1 2
3 1 7
```

### 输出

```
NO
YES
YES
```

# 题解

## 作者：Saliеri (赞：8)

### 简要题目描述：

给你一个数列，让你支持三种操作：

1. 将两个元素合并为同类；

1. 将一段元素合并为同类；

1. 查询两个元素是否为同一类。

___

### 分析：

首先，如果只有 1,3 操作，直接并查集暴力即可。

而 2 操作，如果直接铁头硬上的话，复杂度将会高达 $O(nq)$。

所以我们来分析如何减少 2 操作的代价。

我们发现，在多次操作后，序列基本上都被合成为了**一些的连续段**，而我们如果每次都遍历一遍连续段的话，是对时间的一种浪费。

所以我们要来试着 **跳过一些连续的段**。

如何跳过？

记录 $next_i$ 表示在第 $i$ 个元素后，第一个**不属于** $i$ 的集合的元素编号。

所以当我们遍历的时候，可以通过 next 数组来跳过连续段，以减少便利代价。

Tips ： 

- 关于 next 数组 : 在初始化时将 $next_i \gets i+1$，而后在区间修改时，（设 y 为区间右端点），将所有区间内的 $next_i \gets next_y$ 即可。

___

### 代码

还不懂就只好看代码了……

```cpp
#include <cstdio>
const int maxn = 3e5+5;
int n,q,fa[maxn],nex[maxn];
inline int getfa(int x){return fa[x] == x ? x : fa[x] = getfa(fa[x]);}//并查集基础操作 
int main(){
	scanf("%d %d",&n,&q);
	for(int i=1;i<=n;++i)fa[i] = i,nex[i] = i+1;//初始化 
	for(int i=1,ty,x,y;i<=q;++i){
		scanf("%d %d %d",&ty,&x,&y);
		if(ty == 1)fa[getfa(x)] = getfa(y);//合并 
		if(ty == 2){
			int to;
			for(int i=x+1;i<=y;i=to){
				fa[getfa(i-1)] = getfa(i);//合并 
				to = nex[i],nex[i] = nex[y];//跳区间，更新 
			}
		}
		if(ty == 3)getfa(x)==getfa(y)?printf("YES\n"):printf("NO\n");
	} 
	return 0;
}
```

---

## 作者：localhost (赞：6)

并查集技巧：记录每个点后面和它不属于同一个集合的第一个点

```cpp
#include<bits/stdc++.h>
namespace ZDY{
    #pragma GCC optimize(3)
    #define il __inline__ __attribute__ ((always_inline))
    #define rg register
    #define ll long long
    #define ull unsigned long long
    #define db double
    #define sht short
    #define MB template <class T>il
    #define Fur(i,x,y) for(int i=x;i<=y;++i)
    #define Fdr(i,x,y) for(int i=x;i>=y;--i)
    #define fl(i,x) for(int i=head[x],to;to=e[i].to,i;i=e[i].nxt)
    #define clr(x,y) memset(x,y,sizeof(x))
    #define cpy(x,y) memcpy(x,y,sizeof(x))
    #define fin(s) freopen(s".in","r",stdin)
    #define fout(s) freopen(s".out","w",stdout)
    #define fcin ios::sync_with_stdio(false)
    #define l2(n) ((int)(log2(n)))
    #define inf 0x3f3f3f3f
    MB T ABS(T x){return x>0?x:-x;}
    MB T MAX(T x,T y){return x>y?x:y;}
    MB T MIN(T x,T y){return x<y?x:y;}
    MB T GCD(T x,T y){return y?GCD(y,x%y):x;}
    MB void SWAP(T &x,T &y){T t=x;x=y;y=t;}
}using namespace ZDY;using namespace std;
namespace IO{const char* ln="\n";const int str=1<<20;struct IN{char buf[str],*s,*t;bool _;IN():s(buf),t(buf),_(0){}il char gc(){return s==t&&((t=(s=buf)+fread(buf,1,str,stdin))==s)?EOF:(*s++);}IN&operator>>(char&ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)_=1;else ch=c;return *this;}IN& operator>>(char* ch){clr(ch,0);if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;*ch=c;ch++;while((c=gc())!=EOF&&!isspace(c))*ch=c,ch++;if(c==EOF)_=1;return *this;}IN& operator>>(string& ch){if(_)return *this;char c;while((c=gc())!=EOF&&isspace(c));if(c==EOF)return _=1,*this;ch+=c;while((c=gc())!=EOF&&!isspace(c))ch+=c;if(c==EOF)_=1;return *this;}template<typename T>IN&operator>>(T&x){if(_)return *this;char c=gc();bool ff=0;while(c!=EOF&&(c<'0'||c>'9'))ff^=(c=='-'),c=gc();if(c==EOF){_=1;return *this;}x=0;while(c!=EOF&&'0'<=c&&c<='9')x=(x<<3)+(x<<1)+c-48,c=gc();if(c==EOF)_=1;if(ff)x=-x;return *this;}}in;struct OUT{char buf[str],*s,*t;OUT():s(buf),t(buf+str){}~OUT(){fwrite(buf,1,s-buf,stdout);}void pt(char c){(s==t)?(fwrite(s=buf,1,str,stdout),*s++=c):(*s++=c);}OUT&operator<<(const char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(char*s){while(*s)pt(*s++);return *this;}OUT&operator<<(string s){for(int i=0;s[i];i++)pt(s[i]);return *this;}template<typename T>OUT&operator<<(T x){if(!x)return pt('0'),*this;if(x<0)pt('-'),x=-x;char a[30],t=0;while(x)a[t++]=x%10,x/=10;while(t--)pt(a[t]+'0');return *this;}}out;}using namespace IO;
#define N 200011
int f[N],n,q,nxt[N];
int gf(int x){
    return (x==f[x])?x:(f[x]=gf(f[x]));
}
il void mg(int x,int y){
    if(gf(x)!=gf(y))f[f[y]]=f[x];
}//合并
int main(){
    in>>n>>q;
    Fur(i,1,n)f[i]=i,nxt[i]=i+1;//初始化
    int opt,x,y;
    while(q--){
        in>>opt>>x>>y;
        if(opt==3)out<<(gf(x)==gf(y)?"YES":"NO")<<ln;
        if(opt==2)
            for(int i=x+1;i<=y;)mg(i-1,i),x=nxt[i],nxt[i]=nxt[y],i=x;//合并的时候更新nxt数组
        if(opt==1)mg(x,y);
    }
}
```

---

## 作者：rui_er (赞：3)

区间合并的并查集。

区间合并操作显然不能硬上，考虑如何优化这一段的合并。

例如，假设目前并查集长这样（如下图），此时希望合并 $2\sim 7$，你会怎么做呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/cuej1069.png)

相信我们的第一反应都是：直接把左侧三个集合合并就好了，而不是去合并 $(2,3)(3,4)\cdots(6,7)$。

这确实就是我们的做法，那么我们就需要知道每个集合管辖的范围是哪段区间，或者说需要知道在这一集合后方不属于这一集合的第一个点是多少。我们维护一个数组 $nxt_i$ 表示以 $i$ 为根的那个集合后面不属于这一集合的第一个点，例如 $nxt_3=6$。

然后我们在区间内找到每个集合的第一个点并与前一个集合合并即可。时间复杂度易证（共合并不超过 $n-1$ 次）。

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int n, m, nxt[N]; 
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
struct Dsu {
	int fa[N];
	void init(int x) {rep(i, 1, x) fa[i] = i;}
	int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}
	bool merge(int x, int y) {
		int u = find(x), v = find(y);
		if(u == v) return 0;
		fa[v] = u;
		return 1;
	}
}dsu;

int main() {
	scanf("%d%d", &n, &m);
	rep(i, 1, n) nxt[i] = i + 1; 
	dsu.init(n);
	rep(i, 1, m) {
		int op, x, y;
		scanf("%d%d%d", &op, &x, &y);
		if(op == 1) dsu.merge(x, y);
		else if(op == 2) {
			int lst = 0;
			for(int i=x+1;i<=y;i=nxt[i]) {
				dsu.merge(i-1, i);
				if(lst) nxt[lst] = nxt[y];
				lst = i;
			}
			nxt[lst] = nxt[y];
		}
		else puts(dsu.find(x)==dsu.find(y)?"YES":"NO");
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：2)

## 思路

这道题的 $1,3$ 操作用并查集直接查询即可。关键就在于 $2$ 操作怎么用 $O(\log n)$ 或均摊 $O(\log n)$ 的复杂度进行解决。

首先，我们在合并 $[l,r]$ 这一段数的时候，其实有很多数本来就在一个并查集里。我们只需要合并若干个还没有合并的并查集，而不需要从 $l$ 到 $r$ 一个一个合并。因为只要合并了这几个并查集，效果**等价于**把 $[l,r]$ 直接合并了。

那么我们怎么做呢？每次记录一个 `nxt[i]` 表示第 $i$ 个点后面第一个没有和 $i$ 合并的点。每次合并的时候直接 `i=nxt[i]` 处理即可，最后把 $[l,r]$ 中所有的 `nxt[i]` 都赋值为 `nxt[r]`。这样的话，两个不同的并查集在这一操作中至多合并一次，总共的复杂度不超过 $O(n \log n)$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int fa[500005],nxt[500005];
int find(int k){return (fa[k]==k)?k:fa[k]=find(fa[k]);}
int main()
{
	int n,q; scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++) fa[i]=i,nxt[i]=i+1; // 预处理
	while(q--)
	{
		int op,x,y; scanf("%d%d%d",&op,&x,&y);
		if(op==1) fa[find(y)]=find(x);
		else if(op==2)
		{
			int lst=x;
			for(int i=nxt[x];i<=y;i=nxt[i])
			{
				int tx=find(lst),ty=find(i);
				if(tx!=ty) fa[tx]=ty;
				nxt[lst]=nxt[y]; //因为 [l,r] 都被合并了，所以 [l,r] 之间每个数都在同一个并查集里，nxt 一定是 nxt[y]。
				lst=i;
			}
			nxt[lst]=nxt[y];
		}
		else
		{
			if(find(x)==find(y)) puts("YES");
			else puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：silly_mouse (赞：1)

## 题目描述

有 $n$ 个点，三种操作。

操作 1：将 $x$ 和 $y$ 所在的集合 合并成一个集合。

操作 2：将 $x-y$ 这些点所在的集合 合并成一个集合。

操作 3：查询 $x$ 和 $y$ 是否在同一集合。

## 思路

### 思路一：暴力

容易想到直接用并查集合并，很显然操作 2 多一点导致时间复杂度为 $O(nq)$。

### 思路二：优化暴力

可以看出操作 2 将 $x-y$ 合并后，之后再遇到 $x-y$ 就可以直接跳过。所以使用 $nxt$ 数组记录跳到下一个数是什么数。之后再使用并查集路径压缩即可快速跳过遍历过程。

最后附上我丑陋的代码。

## AC code

```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=1000005;
int n,q,op,x,y,fa[N],nxt[N];
int find(int x){return (x==fa[x])?x:fa[x]=find(fa[x]);}
int find_nxt(int x){return (x==nxt[x])?x:nxt[x]=find_nxt(nxt[x]);}
void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx!=fy)fa[fy]=fx;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<=n+1;i++)fa[i]=nxt[i]=i;
	while(q--){
		cin>>op>>x>>y;
		if(op==1)merge(x,y);
		else if(op==3){
			if(find(x)==find(y))cout<<"YES\n";
			else cout<<"NO\n";
		}else{
			int a=find(x);
			for(int j=x+1;j<=y;j=find_nxt(j)){
				int b=find(j);
				merge(a,b);
				if(j==nxt[j])nxt[j]++;
				a=b;
			}
		}
	}
	return 0;
}
```

---

## 作者：Heavenly_meteorite (赞：1)

这里可以看到算法标签有并查集，所以以下思路都是直接用并查集维护。

这道题先打暴力，会发现：时间复杂度都花在第二种合并上的。那么我们是否可以优化呢？

答案肯定为是~~不然题都做不了~~。那么怎么优化呢？先问一个问题：我合并一大堆循环合并跟先把分成几小堆内部合并再堆堆之间合并有区别吗？显然没有。而这道题的时间很多花在了重复计算即以上内容的“一小堆”内部的合并。于是我们便可以完成以下操作。

这是暴力：


```cpp
    int type,x,y;
	cin>>type>>x>>y;
	if(type==1) {
		follow(x,y);
	} else if(type==2) {
		for(int i=x+1; i<=y; i++) {
			follow(i,x);
		}
	} else {
		if(get_father(x)==get_father(y)) {
			cout<<"YES\n";
		} else {
			cout<<"NO\n";
		}
	}
```
其中,两个函数分别为寻找最“老”的祖先和合并两个并查集，代码如下：

```cpp
int get_father(int i){//最“老”祖先 
	return i==fath[i]?i:fath[i]=get_father(fath[i]);
}
void follow(int i,int j){//合并 
	i=get_father(i);
	j=get_father(j);
	if(i!=j){
		fath[i]=j;
	}
}
```
优化后的代码跟原本的暴力相似但多了一个跳跃，比如有一区间 $[i,j]$ 内的所有的元素都合并过一遍，那么当我们遍历一个大区间的时候，遍历完 $i$ 就遍历 $j+1$。代码实现：

```cpp
int type;
cin>>type;
if(type==1) {
	int x,y;
	cin>>x>>y;
	follow(x,y);
	if(x==y) {
		continue;
	}
} else if(type==2) {
	int x,y;
	cin>>x>>y;
	if(x==y) {
		continue;
	}
	int last=0;
	for(int i=ne[x]+1; i<=y; i=last+1) {
		follow(i,x);
		last=ne[i];
		ne[i]=max(ne[i],ne[y]);
	}
	ne[x]=max(ne[x],ne[y]);
} else {
	int x,y;
	cin>>x>>y;
	if(get_father(x)==get_father(y)) {
		cout<<"YES\n";
	} else {
		cout<<"NO\n";
	}
}
```
其中 $ne[i]$ 数组表示遍历完 $i$ 该遍历的元素下标减一。注意数组要赋初值。

完整代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,q;
const int N=2e5+10;
int ne[N];
int fath[N];
int get_father(int i){
	return i==fath[i]?i:fath[i]=get_father(fath[i]);
}
void follow(int i,int j){
	i=get_father(i);
	j=get_father(j);
	if(i!=j){
		fath[i]=j;
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		fath[i]=i;
		ne[i]=i;
	} 
	while(q--){
		int type;
		cin>>type;
		if(type==1){
			int x,y;
			cin>>x>>y;
			follow(x,y);
			if(x==y){
				continue;
			}
		}
		else if(type==2){
			int x,y;
			cin>>x>>y;
			if(x==y){
				continue;
			}
			int last=0;
			for(int i=ne[x]+1;i<=y;i=last+1){
				follow(i,x);
				last=ne[i];
				ne[i]=max(ne[i],ne[y]);
			}
			ne[x]=max(ne[x],ne[y]);
		}
		else{
			int x,y;
			cin>>x>>y;
			if(get_father(x)==get_father(y)){
				cout<<"YES\n";
			}
			else{
				cout<<"NO\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：ZPB2011 (赞：1)

# Restructuring Company

## 前言

~~老师不知道什么原因把这题丢到了链表专题里。~~

## 思路

第 1，3 操作可以直接用并查集搞定。

2 操作如果暴力合并会让时间复杂度飙升到 $O(nq)$ 导致 TLE，我们考虑优化。

经过观察可以发现把一段区间合并后会让让序列产生一些连续的段，于是我们可以用链表的思想给每个点一个下一个点，这样在进行二操作时就可以每次往右跳而不是一个一个找。

## AC code

[CF AC 记录](https://codeforces.com/contest/566/submission/298135041)。

```cpp
#include <iostream>
#define endl '\n'
using namespace std;

const int N = 2e5 + 5;

int fa[N], r[N];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, q;
	cin >> n >> q;
	for(int i = 1; i <= n; i++) {
		fa[i] = i;
		r[i] = i + 1;
	}
	while(q--) {
		int op, x, y;
		cin >> op >> x >> y;
		if(op == 1) {
			int u = find(x), v = find(y);
			fa[u] = v;
		}
		else if(op == 2) {
			for(int i = x + 1; i <= y;) {
				int u = find(i - 1), v = find(i);
				fa[u] = v;
				int i2 = r[i];
				r[i] = r[y];
				i = i2;
			}
		}
		else {
			int u = find(x), v = find(y);
			if(u == v) cout << "YES" << endl;
			else cout << "NO" << endl;
		}
	}
	return 0;
}
```

---

## 作者：jch123 (赞：0)

## 思路：

有点像[这道题](https://www.luogu.com.cn/problem/P2391)，发现合并区间时有很多的重复（即合并的数已经在一个集合）。记录每个数右边第一个和它不在一个集合的位置 $p_i$，合并一段区间时直接跳 $p_i$ 即可，跳过的部分都和 $i$ 在一个集合内，所以不用在合并了。

初始化将 $p_i$ 设为 $i+1$ 即可。

## 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int p[N],fa[N];
int find(int u)
{
	if(fa[u]==u) return u;
	return fa[u]=find(fa[u]);
}
void merge(int u,int v)
{
	int fx=find(u),fy=find(v);
	fa[fx]=fy;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++)
		fa[i]=i,p[i]=i+1;
	while(q--)
	{
		int op,l,r;
		cin>>op>>l>>r;
		if(op==1) merge(l,r);
		else if(op==2)
		{
			int j;
			for(int i=l+1;i<=r;i=j)
			{
				merge(i,i-1);
				j=p[i],p[i]=p[r];
			}
			p[l]=p[r];
		}
		else
		{
			if(find(l)!=find(r)) cout<<"NO\n";
			else cout<<"YES\n";
		}
	}
	return 0;
}

```

#

---

## 作者：YoungCyrus (赞：0)

## 审题

对一个数列进行 3 种操作：

1. 将两个元素合并为同类
   
2. 将一段元素合并为同类
   
3. 查询两个元素是否同类

可以发现如果只有 1 和 3 这是一道十分板的模板 dsu。

但如果暴力执行 2 的时间复杂度为 $O(nq)$ 显然超时。

## 正解

其实我们可以轻松想到这个区间中，有的元素**已经是同类**了，**没必要合并**了。

那如果我们**跳过这些子段**，就可以节省时间复杂度。

那我们只需要一个数组 $pre_i$ 来记录在第 $i$ 个元素后第一个 $\notin i$ 的集合的元素的编号。

所以当我们遍历的时候，可以通过 $pre$ 数组来跳过连续段，以减少遍历代价。

而 $pre$ 数组初始化为 $i+1$，在区间修改 $[x,y]$ 时就直接将 $pre_i ← pre_y$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 4;
typedef long long ll;
int n, p[N], pre[N], q, type, x, y;
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
    {
        p[i] = i;
        pre[i] = i + 1;
    }
    while (q--)
    {
        scanf("%d%d%d", &type, &x, &y);
        if (type == 3)
        {
            if (find(x) == find(y)) printf("YES\n");
            else printf("NO\n");
        }
        else if (type == 1)
        {
            int fx = find(x), fy = find(y);
            p[fx] = fy;
        }
        else
        {
            int r;
            for (int i = y; i >= x; i = r)
            {
                r = pre[i];
                if (r < x) break;
                p[find(r)] = p[find(i)];
                pre[i] = pre[r];
            }
        }
    }
    return 0;
}
```

---

## 作者：114514xxx (赞：0)

## 思路
### 暴力
用并查集将给定区间的合并起来，时间复杂度 $O(qn)$，显然会超时。
### 正解
暴力思路的时间瓶颈就在对给定区间合并起来。在将已合并区间再次全部重新合并是一笔很大的时间开销。因此我们要尽量让所有的元素都只被合并一次。

我们可以用数组 ${nxt}_i$ 表示元素 $i$ 后面第一个没有被合并的元素。在对一个未进行合并的区间 $[x,y]$ 进行合并时，将 ${nxt}_i$ 设为 ${nxt}_y$，这样就可以尽量跳过已合并区间。 

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=3e5+5;
int n,q,f[N],nxt[N];
inline int read() {
	register int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-')f-=2;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}
inline int find(int x) {
	return f[x]==x?x:f[x]=find(f[x]);
}
int main() {
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	for (int i=1;i<=n;++i)
        f[i]=i,nxt[i]=i+1;//记得初始化
	int opt,x,y,v;
	for (int i=1;i<=q;++i){
		opt=read(),x=read(),y=read();
		if(opt==1)
            f[find(x)]=find(y);
		if(opt==2)
			for (int j=x+1;j<=y;j=v) {
				f[find(j-1)]=find(j);
				v=nxt[j],nxt[j]=nxt[y];
			}
		if(opt==3){
            if(find(x)==find(y))
            puts("YES");
            else puts("NO");
        }
	}
	return 0;
}
```

---

