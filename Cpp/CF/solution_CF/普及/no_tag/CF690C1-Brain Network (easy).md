# Brain Network (easy)

## 题目描述

One particularly well-known fact about zombies is that they move and think terribly slowly. While we still don't know why their movements are so sluggish, the problem of laggy thinking has been recently resolved. It turns out that the reason is not (as previously suspected) any kind of brain defect – it's the opposite! Independent researchers confirmed that the nervous system of a zombie is highly complicated – it consists of $ n $ brains (much like a cow has several stomachs). They are interconnected by brain connectors, which are veins capable of transmitting thoughts between brains. There are two important properties such a brain network should have to function properly:

1. It should be possible to exchange thoughts between any two pairs of brains (perhaps indirectly, through other brains).
2. There should be no redundant brain connectors, that is, removing any brain connector would make property 1 false.

If both properties are satisfied, we say that the nervous system is valid. Unfortunately (?), if the system is not valid, the zombie stops thinking and becomes (even more) dead. Your task is to analyze a given nervous system of a zombie and find out whether it is valid.

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 1
4 1
```

### 输出

```
no
```

## 样例 #2

### 输入

```
6 5
1 2
2 3
3 4
4 5
3 6
```

### 输出

```
yes
```

# 题解

## 作者：Larry76 (赞：0)

## 题目大意：

给定一张 $n$ 个点 $m$ 条边的无向图，判断这是不是一棵树。

## 题目分析：

两种思路：

思路一：

不需要建图，直接使用并查集判环即可

最后判断一下图联不联通就行，具体方法就是看并查集中是不是 $fa_x = x$ 的情况只存在一个，或者看边数是否等于 $n-1$。

时间复杂度 $O(n + m \log n)$

（PS：如果你要是带按秩合并的话时间复杂度可以进一步降低到 $O(n + m \alpha (n))$，其中 $\alpha(n)$ 为反阿克曼函数）

思路二：

建图，用 `dfs` 判环。

时间复杂度 $O(n + m)$

这里给出思路一的代码供大家参考。

## 代码实现：

```cpp
#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<": "<<x<<endl;
#define int long long
using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}

namespace Larry76{
    const int MAX_SIZE = 1.1e5;
    int fa[MAX_SIZE];
    int getfa(int x){
        if(fa[x]==x)
            return fa[x];
        return fa[x] = getfa(fa[x]);
    }
    void merge(int x,int y){
        int fx = getfa(x);
        int fy = getfa(y);
        fa[fy] = fx;
    }
    void main(){
        //Code Here;
        int n,m;
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            fa[i] = i;
        while(m--){
            int u,v;
            cin>>u>>v;
            if(getfa(u)==getfa(v)){
                cout<<"no"<<endl;
                return;
            }
            merge(u,v);
        }
        int same = 0;
        for(int i=1;i<=n;i++)
            if(fa[i] == i)
                same ++;
        if(same>1)
            cout<<"no"<<endl;
        else
            cout<<"yes"<<endl;
    }
}

signed main(){
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
    double c1 = clock();
#else
    ios::sync_with_stdio(false);
#endif
//============================================
    Larry76::main();
//============================================
#ifdef LOCAL
    double c2 = clock();
    cerr<<"Used Time: "<<c2-c1<<"ms"<<endl;
    if(c2-c1>1000)
        cerr<<"Warning!! Time Limit Exceeded!!"<<endl;
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}
```

---

## 作者：JWRuixi (赞：0)

~~为什么 Easy，Medium，hard 完全不一样啊！！~~

- 题意

给定以个 $n$ 个点，$m$ 条边的无向图，判断它是不是树。

- 分析

这就很简单了，~~只要英文过关就能过~~，首先如果 $m\ne n-1$，那就祭，然后跑一边 dfs 判断有没有环就行了！

- code

```cpp
// LUOGU_RID: 92683369
#include <bits/stdc++.h>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
using namespace std;

namespace IO{
	char ibuf[(1 << 20) + 1], *iS, *iT;
	#if ONLINE_JUDGE
	#define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
	#else
	#define gh() getchar()
	#endif
	#define reg register
	inline long long read () {
		reg char ch = gh();
		reg long long x = 0;
		reg char t = 0;
		while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
		while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
		return t ? -x : x;
	}
	inline void write(long long x) {
		if (x < 0) {
			x = ~(x - 1);
			putchar('-');
		}
		if (x > 9)
			write(x / 10);
		putchar(x % 10 + '0');
	}
}

using IO::read;
using IO::write;

const int maxn(2e5 + 500);
int n, m, head[maxn], tot;
bool vis[maxn];

struct edge {
	int v, nxt;
} e[maxn << 1];

inline void add (int u, int v) {
	e[++tot] = {v, head[u]};
	head[u] = tot;
}

inline void dfs (int u, int fa) {
	if (vis[u]) {
		puts("no");
		exit(0);
	}
	vis[u] = 1;
	for (int i = head[u]; i; i = e[i].nxt) {
		int v = e[i].v;
		if (v == fa) continue;
		dfs(v, u);
	}
}

int main () {
	n = read(), m = read();
	for (int i = 1, u, v; i <= m; i++) {
		u = read(), v = read();
		add(u, v);
		add(v, u);
	}
	if (m != n - 1) return puts("no"), 0;
	dfs(1, 0);
	puts("yes");
}
```

---

## 作者：loser_seele (赞：0)

题目大意是判断给定的无向图是否是一棵树。

于是判断这张图是否存在环且连通即可。

判断环和连通可以用并查集。

于是这题就做完了。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
//waiting qwq
//qwq qwq
bool ok=1;
const int maxn=2e5+10;
int fa[maxn];
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int a,int b)
{
	if(find(a)!=find(b))
	fa[find(b)]=find(a);
	else if(find(a)==find(b))
	ok=0;
}
int main()
{
int n,m;
cin>>n>>m;
if(m!=n-1)
{
cout<<"no";
return 0;
}
for(int i=1;i<=n;i++)
fa[i]=i;
for(int i=1;i<=m;i++)
{
int from,to;
cin>>from>>to;
merge(from,to);
}
if(ok)
cout<<"yes";
else
cout<<"no";
}
```


---

