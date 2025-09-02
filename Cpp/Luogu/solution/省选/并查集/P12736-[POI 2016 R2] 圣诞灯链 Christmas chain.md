# [POI 2016 R2] 圣诞灯链 Christmas chain

## 题目背景

翻译来自于 [LibreOJ](https://loj.ac/p/5032)。

## 题目描述

**题目译自 [XXIII Olimpiada Informatyczna — II etap](https://sio2.mimuw.edu.pl/c/oi23-2/dashboard/) [Świąteczny łańcuch](https://szkopul.edu.pl/problemset/problem/cSa80AKpjHR8FlWE4BCpLGT3/statement/)**

每年圣诞节，Bajtazar 都会用五彩缤纷的灯链装点他的家。今年，他决定亲自挑选灯链的颜色，打造一串独一无二的装饰。他对灯链的美学有特定要求：某些灯链片段的颜色排列需与另一些片段完全相同。同时，他的妻子希望今年的灯链尽量丰富多彩，也就是说，灯链应包含尽可能多的不同颜色。请帮助 Bajtazar 计算，他需要购买多少种颜色的灯泡。

## 说明/提示

**样例 1 解释**

设 $a, b, c$ 表示三种不同颜色的灯泡。一个满足 Bajtazar 及其妻子要求的灯链为 $\texttt{abacbababa}$。

**附加样例**

1. $n=2000, m=2$，要求片段 $\{1, \ldots, 1000\}$ 与 $\{1001, \ldots, 2000\}$ 相同，$\{1, \ldots, 500\}$ 与 $\{501, \ldots, 1000\}$ 相同，最大颜色数为 $500$。
2. $n=500000, m=499900$，第 $i$ 个要求为 $a_i=i, b_i=i+100, l_i=1$，最大颜色数为 $100$。
3. $n=80000, m=79995$，第 $i$ 个要求为 $a_i=i, b_i=i+2, l_i=4$，最大颜色数为 $2$。
4. $n=50000, m=25000$，第 $i$ 个要求为 $a_i=1, b_i=i+1, l_i=9$，灯链只能使用单一颜色。

详细子任务附加限制及分值如下表所示。

| 子任务 | 附加限制 | 分值 |
| :---: | :--: | :---: |
| $1$    | $n, m \leq 2000$         | $30$ |
| $2$    | $n, m \leq 500000$，所有 $l_i = 1$ | $20$ |
| $3$    | $n, m \leq 80000$        | $30$ |
| $4$    | $n, m \leq 500000$       | $20$ |

## 样例 #1

### 输入

```
10 3
1 6 3
5 7 4
3 8 1```

### 输出

```
3```

## 样例 #2

### 输入

```
4 2
1 2 2
2 3 2```

### 输出

```
1```

# 题解

## 作者：wangjunyee (赞：3)

## 并查集 + 倍增

[助人为乐，顺便写个题解](https://www.luogu.com.cn/discuss/1091903)。

### 题目分析
题目要求在满足所有指定两个灯链片段颜色完全相同的前提下，求灯链中最大不同颜色数。

条件等同于 $a_i+j$ 与 $b_i+j$ 颜色相同（$0\le j<l_i$）。将灯泡视为节点，每个条件为节点间连边，则最终连通块内的节点颜色必须相同，不同连通块可赋予不同颜色。最大颜色数即为连通块数量。

但由于 $n,m≤500000$，直接建图显然不行。

考虑使用并查集和倍增优化。

将每个位置拆分为 $k=\log n$ 层，每层对应 $2^k$ 长度的区间。每层维护独立并查集,并按秩合并。

第 $0$ 层联通块的个数即为答案，时间复杂度约 $O((n+m)\log n⋅α(n))$（$α(n)$ 为并查集反阿克曼函数）。

完结撒花！
### 具体细节见代码


```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 500005;
const int LOG = 20;  // 2^20 > 500000

int fa[LOG][MAXN];
int rnk[LOG][MAXN];
int n, m;

//查找 
int find(int k, int x) {
    int root = x;
    while (fa[k][root] != root) {
        root = fa[k][root];
    }
    int temp = x;
    while (fa[k][temp] != root) {
        int nxt = fa[k][temp];
        fa[k][temp] = root;
        temp = nxt;
    }
    return root;
}

// 合并
void merge(int k, int x, int y) {
    int fx = find(k, x);
    int fy = find(k, y);
    if (fx == fy) return;
    if (rnk[k][fx] < rnk[k][fy]) {
        fa[k][fx] = fy;
    } else if (rnk[k][fx] > rnk[k][fy]) {
        fa[k][fy] = fx;
    } else {
        fa[k][fy] = fx;
        rnk[k][fx]++;
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int k = 0; k < LOG; k++) {
        for (int i = 1; i <= n; i++) {
            fa[k][i] = i;
            rnk[k][i] = 0;
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        int k = 0;
        while ((1 << (k+1)) <= l) {
            k++;
        }
        merge(k, a, b);
        int pos1 = a + l - (1 << k);
        int pos2 = b + l - (1 << k);
        merge(k, pos1, pos2);
    }

    for (int k = LOG-1; k >= 1; k--) {
        int mid = 1 << (k-1);
        for (int i = 1; i <= n; i++) {
            int root = find(k, i);
            merge(k-1, i, root);
            if (i + mid <= n && root + mid <= n) {
                merge(k-1, i + mid, root + mid);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (find(0, i) == i) {
            ans++;
        }
    }
    printf("%d\n", ans);

    return 0;
}
```

---

## 作者：kkxacj (赞：2)

十分有趣的题。

#### 思路

容易发现，每次操作就是让你将一些点连边，使其赋上一样的颜色。

这个很容易用并查集维护，不过每次是告知一段区间相同，考虑如何优化。

有一种比较无脑的方式，注意到有效合并最多 $n-1$ 次，然后考虑启发式合并，每次把连通块小的那些点颜色全部赋为连通块大的颜色，然后考虑哈希看区间是否相同，用树状数组维护即可，然后每次二分找到第一个不相同的地方，复杂度 $\operatorname{O}\left(n\log^2n\right)$。

我们并不满足这个复杂度，我们考虑 ST 表的思想，将区间表示为两个长度为 $2^k$ 的区间的并集，由于是看两边相等所以可以重复，我们只需要对于每一层维护一个并查集即可。

这样的话，我们又可以在最后把 $2^k$ 转成两个 $2^{k-1}$，复杂度 $\operatorname{O}\left(n\log n \times \alpha \left(n\right)\right)$，复杂度优化十分显著，从大于十秒到不到一秒。

[code](https://www.luogu.com.cn/paste/tkfbfi62)

---

## 作者：Comentropy (赞：0)

不用动脑子的简单数据结构做法，思考十分钟代码四十分钟就一发过了。但是时间复杂度稍劣。

题目的条件可以被拆成若干个两个位置相等的条件，暴力拆出来大概是 $\mathcal{O}(nm)$ 的，难以接受。考虑并查集维护的过程，你实际是在维护连通性，其有效合并其实只有 $\mathcal{O}(n)$ 次，暴力做法把多数时间花在了找可以合并的位置上，十分不优。以下称位置/数的颜色是其所属集合。

于是我们有一个基本的 idea：我们要让每次合并的尝试都是有效的，即要保证合并的两个位置的颜色不同。

我们维护位置的颜色序列。操作范围是区间，这就很简单，使用哈希就可以简单二分出两个区间第一个颜色不同的位置。使用树状数组可以简单维护修改和查询。每次找合并的位置，时间是 $\mathcal{O}(\log^2{n})$ 的。

但是你遇到一个问题：你的区间哈希需要有即时性，也就是你每次合并完集合之后需要把修改的颜色同步回序列上。使用启发式合并即可——启发式合并可以让“修改某个位置的颜色”的操作次数做到 $\mathcal{O}(n\log{n})$。使用上文的树状数组支持修改哈希即可。

最终时间复杂度是 $\mathcal{O}(n\log^2{n})$ 的，常数很小，而且数据貌似没把它卡满，比某些写法稍劣的倍增做法跑得快很多。**值得注意的是，尽管这道题没有卡单哈希，我仍然建议使用双哈希**，代码如下：

```cpp
// 注意他开了 4.5s 1G.
// 该思路使用 10min 完成思考。 40min coding.
// 不知道能不能过啊 而且我也不知道 hash 这个问题误报概率有多大。可能写得差不多了得加个双 hash
// feed back: 竟然过了！最慢点跑了 780ms 左右，也是独立切上紫题了。看看加个快读什么的跑得有多快吧。
// 这个空间不像是卡满的样子啊，不过想必确实有点难卡满吧。
#include<bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef long long LL;

const int N=5e5+10;
const int bas=131,mod=998244353;

inline int& addmod(int &x){ return x>=mod?x-=mod:x; }
inline int Mod(int x){return x>=mod?x-mod:x;}
struct IO{
    char buf[1<<21],*p1,*p2;
    #define gc() (p1==p2 && (p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
    inline int read(){
        register int x=0;
        register char c=gc();
        while(c<'0' || c>'9')   c=gc();
        while(c<='9' && c>='0') x=(x<<3)+(x<<1)+c-'0',c=gc();
        return x;
    }
}io;

int n,m,pw[N];
struct BIT{
    int t[N];
    #define lowbit(x) (x&(-x))

    inline void update(int x,int v){
        v=1ll*v*pw[x]%mod;
        for(int i=x;i<=n;i+=lowbit(i))
            addmod(t[i]+=v);
    }
    inline int query(int x){
        int ret=0;
        for(int i=x;i;i-=lowbit(i))
            addmod(ret+=t[i]);
        return ret;
    }
    inline int qrange(int l,int r){
        return Mod(query(r)+mod-query(l-1));
    }
}hsh;
inline bool comp(int l1,int r1,int l2,int r2){
    return 1ll*hsh.qrange(l1,r1)*pw[l2-l1]%mod==hsh.qrange(l2,r2);
}
struct DSU{ // 直接启发式合并
    int bel[N],tab[N];
    vector<int> e[N];
    inline void chg(int u,int fr){
        hsh.update(u,Mod(fr+mod-bel[u]));
        e[bel[u]=fr].push_back(u);
    }
    inline void init(){ for(int i=1;i<=n;i++) chg(i,i); }
    inline void merge(int u,int v){
        assert(bel[u]!=bel[v]); // 应该是不会有问题。
        if(bel[u]!=bel[v]){ // 这个地方写法其实有很多，所以 hash 还是很难卡的。
            u=bel[u],v=bel[v];
            if(e[u].size()<e[v].size())
                swap(u,v);
            for(int i:e[v])
                chg(i,u);
        }
    }
    inline int count(){
        int ans=0;
        for(int i=1;i<=n;i++)
            if(!(tab[bel[i]]++))
                ++ans;
        return ans;
    }
}dsu;
void init(){
    pw[0]=1;
    for(int i=1;i<=n;i++)
        pw[i]=1ll*bas*pw[i-1]%mod;
    dsu.init();
}
inline void update(int a,int b,int k){
    while(!comp(a,a+k-1,b,b+k-1)){
        int l=0,r=k-1,mid;
        while(l<r){
            mid=(l+r)>>1;
            if(!comp(a,a+mid,b,b+mid))
                r=mid;
            else
                l=mid+1;
        }
        dsu.merge(a+l,b+l);
    }
}
int main(){
    n=io.read(),m=io.read(),init();
    for(int i=1,a,b,k;i<=m;i++){
        a=io.read(),b=io.read(),k=io.read();
        if(a>b) swap(a,b);
        update(a,b,k);
    }
    printf("%d\n",dsu.count());
    return 0;
}
```

---

## 作者：XZhuRen (赞：0)

并查集区间对位的板子，不过这个 Trick 之前没见过。

考虑一次连边连区间，则区间对位连相当于不断地向下连。

直接类似 ST 表式倍增连边，则注意到每一层最后剩下的边数始终是 $\mathcal{O}(n)$，则找到 $fa_i$ 后拆成两个连边即可。

挺有趣的 Trick，复杂度线性对数。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m;
struct Dsu{
	int fa[N];
	void clear(){for(int i=1;i<=n;i++)fa[i]=i;}
	int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
	bool mer(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return 0;
		fa[y]=x;
		return 1;
	}
}dsu[20];
const int SK=19;
void init(){
	scanf("%d%d",&n,&m);
	for(int k=0;k<=SK;k++)dsu[k].clear();
	while(m--){
		int l1,l2,len=0;
		scanf("%d%d%d",&l1,&l2,&len);
		for(int k=SK;k>=0;k--){
			if((1<<k)<=len){
				dsu[k].mer(l1,l2);
				l1+=(1<<k),l2+=(1<<k);
				len-=(1<<k);
			}
		}
	}
}
vector<int>ops[N];
void work(){
	for(int k=SK;k>=1;k--){
		for(int i=1;i<=n;i++)ops[i].clear();
		for(int i=1;i<=n;i++){
			if(dsu[k].find(i)==i)continue;
			ops[dsu[k].find(i)].emplace_back(i);
		}
		for(int i=1;i<=n;i++){
			if(dsu[k].find(i)!=i)continue;
			for(auto x:ops[i]){
				int len1=(1<<(k-1));
				dsu[k-1].mer(i,x);
				dsu[k-1].mer(i+len1,x+len1);
			}
		}
	}
	int Ans=0;
	for(int i=1;i<=n;i++){
		if(dsu[0].find(i)==i)Ans++;
	}
	printf("%d\n",Ans);
}
int main(){
	init();
	work();
	return 0;
}
```

---

