# Asya And Kittens

## 题目描述

Asya 非常喜欢动物。最近，她买了 $n$ 只小猫，并给它们编号为 $1$ 到 $n$，然后把它们放进了一个笼子里。这个笼子由一排 $n$ 个单元格组成，从左到右编号为 $1$ 到 $n$。相邻的单元格之间有半透明的隔板，因此最初有 $n-1$ 个隔板。最开始，每个单元格里正好有一只编号的小猫。

在观察小猫们时，Asya 发现它们非常友好，经常有一对相邻单元格的小猫想要一起玩。因此，Asya 开始移除相邻单元格之间的隔板。具体来说，在第 $i$ 天，Asya 会：

- 发现编号为 $x_i$ 和 $y_i$ 的小猫，位于相邻的单元格里，想要一起玩。
- 移除这两个单元格之间的隔板，将这两个单元格合并为一个单元格，里面包含原来两个单元格里的所有小猫。

由于 Asya 从未重新放回隔板，经过 $n-1$ 天后，笼子里只剩下一个单元格，里面有所有的小猫。

对于每一天，Asya 记得想要一起玩的小猫编号 $x_i$ 和 $y_i$，但她不记得最初是如何将小猫放进笼子的。请你帮她找出一种可能的小猫最初在 $n$ 个单元格中的排列方式。

## 说明/提示

样例的答案是多种可能初始排列中的一种。

下图展示了对于该初始排列，每一天是如何合并单元格的。注意，每一天想要一起玩的小猫，确实在相邻的单元格中。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1131F/0f66af3a5bf104383a10a56a67962cef2112dbf1.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 4
2 5
3 1
4 5
```

### 输出

```
3 1 4 2 5
```

# 题解

## 作者：SGColin (赞：10)

注意到合并两个块的时候，块内顺序是不可以改变的，但是两个块谁在左谁在右无所谓。

所以做法就很简单了，维护这 $n$ 个元素的并查集，在并查集的祖先节点维护一个 ```vector``` 代表对应的块的序列，每次合并的时候启发式合并，把小的 ```vector``` 暴力 ```push``` 进大的就好了，复杂度 $\mathcal O(n\log n)$

```C++
#include <bits/stdc++.h>
#define N 150005
#define gc getchar
using namespace std;

inline int rd() {
  int x = 0;
  char c = gc();
  while (!isdigit(c)) c = gc();
  while (isdigit(c)) {
    x = x * 10 + (c ^ 48); c = gc();
  }
  return x;
}

int n, f[N];

vector<int> s[N];

int find(int x) {return x == f[x] ? x : f[x] = find(f[x]);}

inline void merge(int x, int y) {
  x = find(x); y = find(y);
  if (s[x].size() < s[y].size()) swap(x, y);
  for (int i = 0, lim = s[y].size() - 1; i <= lim; ++i) s[x].push_back(s[y][i]);
  f[y] = x;
}

int main() {
  n = rd();
  for (int i = 1; i <= n; ++i) {
    f[i] = i; s[i].push_back(i);
  }
  for (int i = 1, x, y; i < n; ++i) {
    x = rd(); y = rd();
    merge(x, y);
  }
  int rt = find(1);
  for (int i = 0, lim = s[rt].size() - 1; i <= lim; ++i) printf("%d ", s[rt][i]);
  return 0;
}
```

---

## 作者：Wuyanru (赞：2)

一道比较水的紫题。

首先，我们先直接考虑 $ \Theta\left(n^2\right) $ 的暴力。

我们使用一个数组 $ ans $ 来记录答案，其中 $ ans_{i,0} $ 表示 $ i $ 号数字左边的数字编号，用 $ ans_{i,1} $ 来表示 $ i $ 号数字右边的数字的编号。

然后，我们就可以写出一个函数，用来寻找 $ i $ 号数字所在连通块最左边数字的编号，就像下面这样：

```
int find(int num,int l) {
	if(ans[num][l]==0)
		return num;
	return find(ans[num][l],l);
}
```

非常明显，如果 $ ans_{num,l} $ 为 $ 0 $,则代表 $ num $ 就是最边上的数字，返回 $ num $,否则递归继续寻找。

我们再来考虑建立关系，若输入的两个数字分别是 $ a $ 和 $ b $,那么我们就让 $ a $ 所在的连通块处于 $ b $ 所在连通块的左边，这样，我们就只需要找到两个节点并改变他们邻居的编号就可以了，到时候输出就直接找到邻居然后输出。

代码如下：
```
#include<cstdio>
using namespace std;
int ans[150001][2];
int n;
int a,b;
int find(int num,int l) {
	if(ans[num][l]==0)
		return num;
	return find(ans[num][l],l);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<n; i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		int x=find(a,1);
		int y=find(b,0);
		ans[x][1]=y;
		ans[y][0]=x;
	}
	int left;
	for(int i=1; i<=n; i++)
		if(ans[i][0]==0) {
			left=i;
			break;
		}
	printf("%d",left);
	while(ans[left][1]!=0) {
		left=ans[left][1];
		printf(" %d",left);
	}
	return 0;
}
```
然后，我们就可以~~愉快地~~在第八个测试点超时。

下来我们来考虑正解，~~被优化过的暴力~~。

其实，程序超时的地方就在每次寻找连通块边界上，每一次寻找的时间复杂度都大约为 $ \Theta\left(n\right) $,所以我们就可以再使用一个数组来记录每个连通块的边界，并在寻找的过程中进行修改，于是函数就变成了这个样子：
```
int find(int num,int l) {
	if(lia[num][l]==num&&ans[num][l]==0)
		return num;
	if(lia[num][l]!=num&&ans[num][l]!=0)
		return lia[num][l]=find(lia[num][l],l);
	return lia[num][l]=find(ans[num][l],l);
}
```
由于这个地方不太好理解，所以我将进行一步一步的讲解。

首先我们来看前两行：
```
	if(lia[num][l]==num&&ans[num][l]==0)
		return num;
```
意思是说 $ num $ 旁边没有邻居且连通块数组已经更新到最新情况，返回 $ num $。

第二部分：
```
	if(lia[num][l]!=num&&ans[num][l]!=0)
		return lia[num][l]=find(lia[num][l],l);
```
这里的意思是说 $ num $ 并不是连通块的边界，寻找连通块边界并且更新数组。

最后一部分：
```
	return lia[num][l]=find(ans[num][l],l);
```
这里是说 $ num $ 并不是连通块的边界但是 $ lia $ 数组还未更新，仍然认为 $ num $ 是连通块边界的情况，这时通过 $ num $ 的邻居来寻找连通块边界并更新 $ lia $ 数组。

这样，虽然时间复杂度看起来并没有减少多少，但由于原来的方法是一个一个寻找，现在变为了跳跃式的寻找，所以会快很多。

AC代码：
```
#include<cstdio>
using namespace std;
int ans[150001][2];
int lia[150001][2];
int n;
int find(int num,int l) {
	if(lia[num][l]==num&&ans[num][l]==0)
		return num;
	if(lia[num][l]!=num&&ans[num][l]!=0)
		return lia[num][l]=find(lia[num][l],l);
	return lia[num][l]=find(ans[num][l],l);
}
int main() {
	scanf("%d",&n);
	for(int i=1; i<=n; i++)
		lia[i][0]=lia[i][1]=i;
	for(int i=1; i<n; i++) {
		int a,b;
		scanf("%d%d",&a,&b);
		int x=find(a,1);
		int y=find(b,0);
		ans[x][1]=y;
		ans[y][0]=x;
	}
	int left;
	for(int i=1; i<=n; i++)
		if(ans[i][0]==0) {
			left=i;
			break;
		}
	printf("%d",left);
	while(ans[left][1]!=0) {
		left=ans[left][1];
		printf(" %d",left);
	}
	return 0;
}
```
感谢观看！

---

## 作者：Infinity_Fantasy (赞：1)

看到题解区大部分都是维护链状数据结构，于是就写了一篇启发式合并的题解，~其实是随机跳的题发现还可以写题解~。

首先看到连通块合并，很容易想到用并查集，要求相邻的块才能合并，即用并查集模拟，然后依次输出同一个连通块内的点。

但是考虑到最开始各个顶点相互独立，最终的同一连通块内的点的合并顺序是重要的，则可以联想到启发式合并。所谓启发式合并通俗一点讲就是并查集按顺序合并，始终保持着块内元素的顺序，也就是题目中点的合并顺序。

于是就愉快地结束了。

---

## 作者：_JF_ (赞：1)

[Link](https://codeforces.com/problemset/problem/1131/F)

这个思路可能需要一点灵感？

首先你注意到合并两个块的时候一定要紧挨在一起，但是我们不知道他们的左右顺序。

为了让这两个块 $x,y$ 紧挨在一起，我们考虑 Kuskral 重构树的建树方式，新开一个节点，连向 $x,y$ ，表示这两个块我们希望它挨在一起。

那这样我们就表示出来了两个连通块的合并。

因为这是一个二叉树，建完树以后我们对于一个点直接找左右子树递归就是结果。这里没有顺序的要求。（因为你合并两个连通块谁左谁右没有关系。）

并且我们按照输入的顺序来进行这个操作的话，自上而下遍历输出，就符合了我们整个的合并过程。

时间复杂度 $O(n)$


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long
int n,root,fa[N],tot;
vector<int> g[N];
int Find(int x){
	return (x==fa[x])?x:fa[x]=Find(fa[x]);
}
void Slove(int u){
	if(g[u].size()==0&&u!=tot)	{cout<<u<<" ";return ;}
	Slove(g[u][0]),Slove(g[u][1]);
}
signed main(){
	cin>>n;
	tot=n;
	for(int i=1;i<=2*n;i++)	fa[i]=i;
	for(int i=1,u,v;i<n;i++){
		cin>>u>>v;
		u=Find(u),v=Find(v);
		if(v!=u)	tot++,g[tot].push_back(u),g[tot].push_back(v),fa[u]=fa[v]=tot;
	}
	Slove(tot);
	return 0;
}
```

---

## 作者：LJC00118 (赞：1)

两个被合并的点的联通块一定在序列里是挨着的，直接链表合并，最后遍历一下链表即可

```cpp
#include <bits/stdc++.h>
#define Fast_cin ios::sync_with_stdio(false), cin.tie(0);
#define rep(i, a, b) for(register int i = a; i <= b; i++)
#define per(i, a, b) for(register int i = a; i >= b; i--)
#define DEBUG(x) cerr << "DEBUG" << x << " >>> " << endl;
using namespace std;

typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef long long ll;

template <typename _T>
inline void read(_T &f) {
    f = 0; _T fu = 1; char c = getchar();
    while(c < '0' || c > '9') { if(c == '-') fu = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { f = (f << 3) + (f << 1) + (c & 15); c = getchar(); }
    f *= fu;
}

template <typename T>
void print(T x) {
    if(x < 0) putchar('-'), x = -x;
    if(x < 10) putchar(x + 48);
    else print(x / 10), putchar(x % 10 + 48);
}

template <typename T>
void print(T x, char t) {
    print(x); putchar(t);
}

template <typename T>
struct hash_map_t {
    vector <T> v, val, nxt;
    vector <int> head;
    int mod, tot, lastv;
    T lastans;
    bool have_ans;

    hash_map_t (int md = 0) {
        head.clear(); v.clear(); val.clear(); nxt.clear(); tot = 0; mod = md;
        nxt.resize(1); v.resize(1); val.resize(1); head.resize(mod);
        have_ans = 0;
    }

    bool count(int x) {
        int u = x % mod;
        for(register int i = head[u]; i; i = nxt[i]) {
            if(v[i] == x) {
                have_ans = 1;
                lastv = x;
                lastans = val[i];
                return 1;
            }
        }
        return 0;
    }

    void ins(int x, int y) {
        int u = x % mod;
        nxt.push_back(head[u]); head[u] = ++tot;
        v.push_back(x); val.push_back(y);
    }

    int qry(int x) {
        if(have_ans && lastv == x) return lastans;
        count(x);
        return lastans;
    }
};

const int N = 150005;

int f[N], head[N], tail[N], nxt[N];
int n;

int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }

int main() {
    read(n);
    for(register int i = 1; i <= n; i++) {
        f[i] = i;
        head[i] = tail[i] = i;
    }
    for(register int i = 1; i < n; i++) {
        int a, b; read(a); read(b);
        int x = find(a), y = find(b); f[y] = x;
        nxt[tail[x]] = head[y];
        tail[x] = tail[y];
    }
    int u = find(1);
    for(int i = head[u]; ; i = nxt[i]) {
        printf("%d ", i);
        if(i == tail[u]) break;
    }
    putchar('\n');
    return 0;
}
```

---

## 作者：Merge_all (赞：0)

### 思路：
- 发现是合并操作，因此用并查集做起来**方便又快捷**。
- 用一个 vector 记录节点 $i$ 的所有子孙。
- 初始先加入自己，在每次合并时，用**启发式优化**的同时，进行合并操作，并且将一个**集合的所有元素都放入** $v_{i}$ 这个 vector 中，表示它们都是 $i$ 的子孙。
- 接下来就是并查集的板子了。
### 代码：
```
#include <bits/stdc++.h>

using namespace std;

const int N=200100;

int n, f[N];
vector<int> s[N];

int find(int x) {
	return x == f[x] ? x : f[x] = find(f[x]);
}

inline void merge_set(int x, int y) {
	x = find(x);
	y = find(y);
	if (s[x].size() < s[y].size()) swap(x, y);
	int len=s[y].size();
	for (int i = 0 ; i < len; i++) s[x].push_back(s[y][i]);
	f[y] = x;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for (int i = 1; i <= n; i++) {
		f[i] = i;
		s[i].push_back(i);
	}
	for (int i = 1, x, y; i < n; i++) {
		cin>>x>>y;
		merge_set(x, y);
	}
	int root = find(1);
	int len = s[root].size();
	for (int i = 0; i < len; i++) cout<<s[root][i]<<" ";
	return 0;
}
```

---

## 作者：Lamb_Carp (赞：0)

## advertisement

这位靓仔，你都来看我的题解了，为什么不来[我的博客](https://www.cnblogs.com/carp-oier/p/CF1131F.html)看一看呢。

## prologue

大水题

## analysis

我们要维护连通块，题目给的样例解释也很清楚，就是让我们将两个连通块合并。

我们之后只需要用一个链表来维护头尾就好了。

这个过程直接用**并查集**维护就好了。

## code time

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fom(i, a) for(int i=a; i; -- i)
#define foa(i, a, b) for(int i=a; i < b; ++ i)
#define fos(i, a, b) for(int i=a; i <= b; ++ i)
#define fop(i, a, b) for(int i=a; i >= b; -- i)
#define ws putchar(' ')
#define wl putchar('\n')

template <class T> void waw(T x)
{
    if(x > 9) waw(x / 10);
    putchar(x % 10 ^ 48);
}

template <class T> inline void ww(T x)
{
    if(x < 0) x = ~x + 1, putchar('-');
    waw(x);
}

template <class T> inline void read(T &res)
{
    char ch = getchar(); bool f = 0; res = 0;
    for(; !isdigit(ch); ch = getchar()) f |= ch == '-';
    for(; isdigit(ch); ch = getchar()) res = (res << 1) + (res << 3) + (ch ^ 48);
    res = f ? ~res + 1 : res;
}

const int N = 2e5 + 10;

ll n;

ll p[N], h[N], ne[N], t[N];

inline ll find(ll x) { return (p[x] == x) ? x : p[x] = find(p[x]); }

inline void merge(ll x, ll y)
{
    ll a = find(x), b = find(y);
    ne[t[a]] = h[b], t[a] = t[b];
    p[b] = a;
}

int main()
{
    read(n);
    fos(i, 1, n) p[i] = h[i] = t[i] = i;

    foa(i, 1, n)
    {
        ll x, y; read(x), read(y);  
        merge(x, y);
    }

    ll s = h[find(1)];

    fos(i, 1, n) ww(s), ws, s = ne[s];
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

迷惑。

考虑直接模拟，如果有 `x y` 的要求，直接把 $x$ 所在块和 $y$ 所在块拼在一起。很显然，无论谁在前谁在后都不会对后面产生影响。

因此你在并查集的每个父亲节点记一下链表的首尾即可。

代码：

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,nxt[MAXN],fa[MAXN],hd[MAXN],tl[MAXN];
int find(int k) {
	if(fa[k]==k) return k;
	return fa[k]=find(fa[k]);	
}
void merge(int u,int v) {
	u=find(u),v=find(v);
	nxt[tl[u]]=hd[v],tl[u]=tl[v],fa[v]=u;
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n; ffor(i,1,n) fa[i]=i,hd[i]=tl[i]=i;
	ffor(i,1,n-1) {
		int x,y;
		cin>>x>>y;
		merge(x,y);	
	}
	int st=hd[find(1)];
	ffor(i,1,n) {
		cout<<st<<' ';
		st=nxt[st];	
	}
	return 0;
}
```

所以这是紫题。不会有人用块状链表或平衡树吧 /jy

---

## 作者：Unnamed114514 (赞：0)

对于集合的合并关系，容易想到并查集。

如果直接硬性合并两个集合的元素，时间复杂度就是 $O(n)$。

考虑到本题只需要两个集合挨在一起，也就是说，它们是无序的。

于是可以使用启发式合并，每次将元素数量少的合并到元素数量多的，时间复杂度 $O(n\log n)$。

---

## 作者：fzj2007 (赞：0)

维护联通块的好题。

可以发现，对于合并操作，只是要求两个块相邻，并没有对块的绝对位置的要求。

由于只会合并 $n-1$ 次，可以考虑每次记录下来合并的两个联通块。由于直接记录时间和空间都无法承受，考虑到解决联通块问题的利器-并查集。

与普通的并查集不同的是，当前每次合并操作都新建一个节点以保留原有的信息。

假如原来的并查集是这样的：(这里只展示要合并的两个联通块）

![](https://cdn.luogu.com.cn/upload/image_hosting/4v9sx84r.png)

现在合并之后是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/77qqkl9s.png)

容易发现，这样操作后应该形成一棵节点为 $2\times n-1$ 的二叉树，节点数并不多。由于输出答案需要从根节点开始，故可以再每次新建节点的时候从新节点向要合并的两个联通块分别连一条边。

最后直接从根节点 $\text{dfs}$ 输出答案即可。

```
#include<bits/stdc++.h>
using namespace std;
namespace IO{
    template<typename T>inline void read(T &x){
        x=0;
        char ch=getchar();
        bool flag=0;
        while(ch<'0'||ch>'9') flag=flag||(ch=='-'),ch=getchar();
        while(ch>='0'&&ch<='9') x=x*10+(ch^'0'),ch=getchar();
        if(ch!='.'){
            x=flag?-x:x;
            return;
        }
        double Base=0.1;
        while(ch<'0'||ch>'9') ch=getchar();
        while(ch>='0'&&ch<='9') x=x+Base*(ch^'0'),Base/=10.0,ch=getchar();
        x=flag?-x:x;
    }
    template<typename T>void prt(T x){
        if(x>9) prt(x/10);
        putchar(x%10+'0');
    }
    template<typename T>inline void put(char ch,T x){
        if(x<0) putchar('-'),x=-x;
        prt(x);
        putchar(ch);
    }
    const int DM[10]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
    inline void putd(char ch,double x,int w){
        if(x<0) putchar('-'),x=-x;
        if(!w){
            put(ch,(int)(x+0.5));
            return;
        }
        int prex=(int)x;
        x-=(int)x;
        x*=DM[w];
        x+=0.5;
        int nowx=(int)x,now=0;
        if(nowx>=DM[w]) nowx=0,prex++;
        put('.',prex);
        int xx=nowx;
        if(!xx) now=1;
        else while(xx) xx/=10,now++;
        now=w-now;
        while(now--) putchar('0');
        put(ch,nowx);
    }
    inline void putstr(string s){
        for(int i=0;i<s.length();i++) putchar(s[i]);
    }
}
using namespace IO;
#define N 300005
int n,fa[N];
int idx,ch[N][2];
int getf(int x){//可以路径压缩
	return fa[x]==x?x:fa[x]=getf(fa[x]);
}
inline void merge(int x,int y){
	x=getf(x),y=getf(y);
	ch[++idx][0]=x,ch[idx][1]=y;//一个点只可能有两个子节点
	fa[x]=fa[y]=fa[idx]=idx;//重新赋值父节点
}
void solve(int x){
	if(x<=n) return put(' ',x),void();
	if(ch[x][0]) solve(ch[x][0]);//如果有节点有dfs
	if(ch[x][1]) solve(ch[x][1]);
}
int main(){
	read(n);
	idx=n;
	for(int i=1;i<=n<<1;i++) fa[i]=i;
	for(int i=1,a,b;i<n;i++)
		read(a),read(b),merge(a,b);
	solve(idx);
	return 0;
}

```

---

## 作者：Night_Bringer (赞：0)

# 前言
[博客园食用更佳](https://www.cnblogs.com/C202202chenkelin/p/14987738.html)

[Codeforces](https://codeforces.com/problemset/problem/1131/F)
# 题意
有一个长为 $n$ 的排列，一开始每个数都是一个独立的联通块。有 $n-1$ 次操作，每次要求 $x_i$ 和 $y_i$ 所在的联通块相邻，然后把这两个联通块合并。求一个合法的排列使得所有操作合法。保证有解。
# 思路
先说这道题的坑点，合并时 $x_i$ 必须放在左边，合并时 $y_i$ 必须放在右边。

首先将每一个块看成一个独立的连通块。对于每一个连通块，可以看做是一条链。

于是可以使用链来维护，手写。重要的是链首和链尾。

显然初始化时，应该把每一个链的链首与链尾初始化成自己。

而对于查找每一个点属于哪一个连通块可以使用并查集进行维护。

并查集合并时，将左边的链连接至右边的链的头部，让后将左边的链尾设置尾右边的链尾。

由于右连通块的父亲将置为左连通块，所以右连通块的信息已经没有用处了，就不需要更新。

最后从整条链的链首开始，一直输出到链尾。
# Code
时间复杂度尾 $O(α(n)n)$ 。
```cpp
#include <cstdio>
namespace Quick_Function {
	template <typename Temp> void Read(Temp &x) {
		x = 0; char ch = getchar(); bool op = 0;
		while(ch < '0' || ch > '9') { if(ch == '-') op = 1; ch = getchar(); }
		while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
		if(op) x = -x;
	}
	template <typename T, typename... Args> void Read(T &t, Args &... args) { Read(t); Read(args...); }
	template <typename Temp> Temp Max(Temp x, Temp y) { return x > y ? x : y; }
	template <typename Temp> Temp Min(Temp x, Temp y) { return x < y ? x : y; }
	template <typename Temp> Temp Abs(Temp x) { return x < 0 ? (-x) : x; }
	template <typename Temp> void Swap(Temp &x, Temp &y) { x ^= y ^= x ^= y; }
}
using namespace Quick_Function;
const int MAXN = 15e4 + 5;
int fa[MAXN], head[MAXN], tail[MAXN];
int nxt[MAXN], a[MAXN], n;
struct DSU {	
	int Find(int x) { return fa[x] == x ? x : (fa[x] = Find(fa[x])); }
	void Union(int x, int y) {
		int fax = Find(x), fay = Find(y);
		if(fax == fay) return;
		fa[fay] = fax;
		nxt[tail[fax]] = head[fay];
		tail[fax] = tail[fay];
	}
	void Init() { for(int i = 1; i <= n; i++) fa[i] = head[i] = tail[i] = i, nxt[i] = 0; }
	void Print(int x) {
		if(!x) return;
		printf("%d ", x);
		Print(nxt[x]);
	}
};
DSU dsu;
int main() {
	Read(n); dsu.Init();
	for(int i = 1, x, y; i < n; i++) Read(x, y), dsu.Union(x, y);
	dsu.Print(head[dsu.Find(1)]);
	return 0;
}
```

---

## 作者：yaaaaaan (赞：0)

## 一、原题链接
[点我传送](https://codeforces.com/contest/1131/problem/F)

## 二、题目大意
有 $n$ 个单元格，$n-1$ 个隔板，每次打开相邻两个之间的隔板，求最初 $n$ 个数的排列顺序（**任意**打印一种答案）。

## 三、思路
用一个 vector 数组记录以 $i$ 为祖先的所有儿子，最初初始化加入自己，每拆开一个隔板就把那两个集合用并查集合并，然后把其中一个的所有元素都加进另一个元素的序列。最后随机打印**任意一个 $i$ 祖先的 vector 数组**就是可能的放置顺序了。

如果这么写有一个小错误会爆空间，需要用到**启发式优化**。

启发式优化 即将**数量小的集合合并到数量大**的集合，所以定义一个数组记录集合内部个数，初始化为 $1$，合并的时候更新数组即可。

## 四、核心代码
```cpp
for(int i=1;i<n;i++)
{
	int x,y;
	cin>>x>>y;
	int xx=find(x),yy=find(y);
	if(s[xx]<s[yy]) swap(xx,yy);
	fa[yy]=xx;
	s[xx]+=s[yy];
 	for(auto it：v[yy])
	{
		v[xx].push_back(it);
	}
}
int ans=find(1);
for(auto it:v[ans])
{
	cout<<it<<" ";
}
```

---

