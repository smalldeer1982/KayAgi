# Choosing The Commander

## 题目描述

As you might remember from the previous round, Vova is currently playing a strategic game known as Rage of Empires.

Vova managed to build a large army, but forgot about the main person in the army - the commander. So he tries to hire a commander, and he wants to choose the person who will be respected by warriors.

Each warrior is represented by his personality — an integer number $ p_{i} $ . Each commander has two characteristics — his personality $ p_{j} $ and leadership $ l_{j} $ (both are integer numbers). Warrior $ i $ respects commander $ j $ only if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817E/b16f95ca4b565c33ddcd184eb553a25fa59f1c3f.png) (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817E/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) is the bitwise excluding OR of $ x $ and $ y $ ).

Initially Vova's army is empty. There are three different types of events that can happen with the army:

- $ 1 p_{i} $ — one warrior with personality $ p_{i} $ joins Vova's army;
- $ 2 p_{i} $ — one warrior with personality $ p_{i} $ leaves Vova's army;
- $ 3 p_{i} l_{i} $ — Vova tries to hire a commander with personality $ p_{i} $ and leadership $ l_{i} $ .

For each event of the third type Vova wants to know how many warriors (counting only those who joined the army and haven't left yet) respect the commander he tries to hire.

## 说明/提示

In the example the army consists of two warriors with personalities $ 3 $ and $ 4 $ after first two events. Then Vova tries to hire a commander with personality $ 6 $ and leadership $ 3 $ , and only one warrior respects him (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817E/81a0cabf14dad3e87bbace6c754e37623e351c09.png), and $ 2&lt;3 $ , but ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF817E/9023c8bab139f08429005ae47d2d497f5795be9b.png), and $ 5>=3 $ ). Then warrior with personality $ 4 $ leaves, and when Vova tries to hire that commander again, there are no warriors who respect him.

## 样例 #1

### 输入

```
5
1 3
1 4
3 6 3
2 4
3 6 3
```

### 输出

```
1
0
```

# 题解

## 作者：Powerless233 (赞：14)

## 思路分析
### 01Trie
观察题意，跟异或的统计数字问题有关，不难想到 01Trie 。添加、删除的操作较为好像，关键看**查询**：

因为我们在遍历的时候，是从高位到低位，即从 $2^{31}$ 到 $2^{0}$ 。也就是说，对于一个查询 $(p,l)$ ，当我们在前面遍历的过程中，保证 **每位按 $p$ 异或后的结果**（下文中用 $k$ 表示） 都小于等于 $l$ 那一位的值，就可以保证整体小于等于 $l$ ，例如：

```
l 1110110
```
$k$ 在当前位 $l = 1$ 时位可以取 $0/1$ ，例如这里的前 $3$ 位：
```
l 1110110
k 111
```
```
l 1110110
k 101 (当然，你也可以这样取)
```
$k$ 在当前位 $l = 0$ 时，就只能取 $0$ ，这样才能保证 $k \leq l$ 。
```
l 1110110
k 1110 (第4位只能取0)
```

如此遍历，就可以一直保证 $k \leq l$。建立在这样的遍历基础上，我们来思考如何统计答案：

对于当前这一位，若 $l = 1$ ，那么在 $k = 0$ 子树上所有的值都可以取：
```
l 1110110
k ----010
  ----011
  ----001 (这些都可以取)
```
那么就直接统计答案，**不再遍历 $k = 0$ 的子树**。

对于当前这一位，若 $l = 0$ ，那么在 $k = 1$ 子树上一定无解。在 $k = 0$ 的子树上**可能**有解，继续向下遍历即可。

停，在这里先思考一个问题：在 $k = 1$ 子树上真的**一定无解吗**？（已经得出结论的可直接跳过）


------------
考虑这样一种情况：
```
l 1110110
k 110010? (?表示当前正在处理的这一位)
```
那么此时立刻就会发现，虽然这一位上的 $l = 0$ ，但 $k$ 在这一位上可以取 $0/1$ 。这样就产生了矛盾。

但是这种情况时不会出现的。在前面遍历的过程中，我们就保证了这种情况不会出现。例如：

```
l 1110110
k 110
```
在这一位的时候，$k = 0$ 的情况已经被讨论过了，不会再向下遍历，所以上述情况不会存在。 

------------

总结一下思路，对于当前讨论的这一位

- 若 $l = 1$ ，则统计 $k = 0$ 子树上的答案，并向 $k = 1$ 的子树继续遍历。
- 若 $l = 0$ ，则向 $k = 0$ 的子树继续遍历。


## 代码实现

插入和删除没什么好说的。

对于统计一颗子树上点的个数，固然可以把插入、删除的操作写成递归的方式，在修改的时候直接把节点个数上传（类似于线段树的 pushup 操作）。

但我们可以采取更聪明的方法，直接在路径上将路径上的节点标记+1，这样就可以直接求得子树上的节点个数。

几个实现的时候要注意的小点：

- 字典树空间大小：字符总数 $ \times $ 字符类型。
- 当前节点赋值 `t=x & (1<<i)` 时，要把 `t` 定义成 bool 类型。


## Code
```cpp
#include<bits/stdc++.h>
#define MAXN 3200005
#define LL long long
using namespace std;
inline LL read(){
	LL res=0,fl=1;
	char ch=getchar();
	while(!(ch>='0' && ch<='9')){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0' && ch<='9')res=res*10+ch-'0',ch=getchar();
	return res*fl;
}
int tr[MAXN][2],sum[MAXN];
int n,tot=1;
inline void insert(int x,int z){
	int k=1;
	bool t;
	for(int i=31;i>=0;i--){
		t=x & (1<<i);
		if(!tr[k][t])tr[k][t]=++tot;
		k=tr[k][t];
		sum[k]+=z;
	}
}
inline int search(int p,int l){
	int k=1,res=0;
	bool x,y;
	for(int i=31;i>=0;i--){
		x=p & (1<<i),y=l & (1<<i);
		if(y)res+=sum[tr[k][x]],k=tr[k][x^1];
		else k=tr[k][x];
	}
	return res;
}
int main() {
	int opt,p,l;
	n=read();
	for(int i=1;i<=n;i++){
		opt=read(),p=read();
		if(opt==1)insert(p,1);
		if(opt==2)insert(p,-1);
		if(opt==3){
			l=read();
			cout<<search(p,l)<<'\n';
		}
	}
	return 0;
}


```


---

## 作者：lndjy (赞：7)

### 做法：trie树+分类讨论

因为这题是异或问题，所以考虑 01trie。

由于要统计个数，考虑用 $tot_i$ 表示 01trie 中结尾在 $i$ 的子树中的数的个数。(也就是前缀相同的）

对于插入删除操作，套板子即可，和板子不同的是更新 $tot$ 数组。

麻烦的是查询。

考虑分类讨论。当这个位有贡献时一定是 $l_i$ 为 $1$.当 $p_i$ 为 $0$ 时，就加上 $1$ 的个数，当 $p_i$ 为 $1$ 时，就加上 $0$ 的个数，这样可以保证这一位异或后小于 $l_i$,也就是总体小于 $l_i$.

当 $p_i$ 为 $0$ 时，异或和也只能是 $0$ ,所以要走到 $l_i$，因为相同的数异或和为 $0$.当 $p_i$ 为 $1$ 时，$l_i$ 已经统计答案了，所以要走到 $l_i$ 相反的地方。

代码（自认为码风清新）
```cpp
#include<iostream>
using namespace std;
int son[3100005][2],tot[3100005],cnt=1;
void add(int x,int v)
{
	bool num;
	int now=1;
	for(int i=1<<30;i;i>>=1)
	{
		tot[now]+=v;
		num=x&i;
		if(!son[now][num]) son[now][num]=++cnt;
		now=son[now][num];
	}
	tot[now]+=v;
}
int ask(int x,int y)
{
	bool num,num2;
	int now=1,ans=0;
	for(int i=1<<30;i;i>>=1)
	{
		num=x&i;num2=y&i;
		if(num<num2)
		ans+=tot[son[now][0]];
		if(num&&num2)
		ans+=tot[son[now][1]];
		if(!num2)
		now=son[now][num];
		else
		now=son[now][num^1];
	}
	return ans;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int op,a,b;
		cin>>op>>a;
		if(op==1) add(a,1);
		if(op==2) add(a,-1);
		if(op==3)
		{
			cin>>b;
			cout<<ask(a,b)<<'\n';
		}
	}
	return 0;
}
```


---

## 作者：青鸟_Blue_Bird (赞：4)

此题其实为 $01Trie$ 模板题。

看到**加入**、**删除**、**求异或值**， 我们不禁也必须想到 $01Trie$ 树。（~~未学过的童鞋们除外~~）

#### 1、什么是 $01Trie$ ?

首先我们要先知道什么是 $Trie$ 树，这里推荐一篇个人认为还不错的[博客](https://blog.csdn.net/yuzhiqiang666/article/details/80711441)。

顾名思义，所谓 $01 Trie$, 是普通 $Trie$ 树的一种特殊应用。与 $Trie$ 树各个节点保存的都是字母类似，在 $01Trie$ 上我们每个节点保存的是数字在 $2$ 进制下的值所对应的 $01$ 位。 

比如，对于一个数 $4$, 其二进制下表示为 $1,0,0$。那么，我们就可以如下建树:

```cpp
1
|
0
|
0

```

如果，我们又有一个数 $5$, 其二进制表示为 $1,0,1$, 那么插入之后，$01Trie$ 就变为：

```cpp
1
|
0 
|\ 
0 1
```

#### 2、怎么应用？

考虑如下问题： 给定 $n$ 个数，求两两之间 $xor$ 的最大值。那我们就可以对 $n$ 个数建立一棵 $01Trie$, 然后固定一个值，遍历一遍 $Trie$ 树，在遍历时从高往低位贪心即可。

#### 3、关于此题

（以下的“每一位”之类的言语均指二进制状态下）

对于前两个操作，我们可以直接模仿普通的 $Trie$ 树，记录 $sum$ 为当前节点经过的数字数量，同时进行加减。在此不再赘述。

对于第三个操作，如下考虑：

1. 如果第 $i$ 位可以为答案造成贡献，那么我们的 $l$ 这一位一定要是 $1$。 
1. 如果 $l$ 这一位是 $1$, 那我们肯定优先往 $x$ 的 $xor$ 值那边跑，因为这样可以使得值更小。然后加上对应的值即可。
1. 如果 $l$ 的这一位是 $0$ 呢？ 那我们这一位肯定也只能是 $0$。所以 选择相等的那一边跑，一直到可以再次变小为止。


上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 1000010
#define ll long long

template <class T>
inline void read(T& a){
	T x = 0, s = 1;
	char c = getchar();
	while(!isdigit(c)){ if(c == '-') s = -1; c = getchar(); }
	while(isdigit(c)){ x = x * 10 + (c ^ '0'); c = getchar(); }
	a = x * s;
	return ;
}

struct tree{
	int ch[2]; 
	int sum;    // 经过这个节点的数的数量 
	
	tree(){
		for(int i = 0; i < 2; i++)
			ch[i] = 0;
		return ; 
	}
} t[N * 5];

int cnt = 1; 

void build(int now, int x){
	for(int i = (1 << 30); i; i >>= 1){
		bool c = i&x;   // 获取第 i 位 0, 1 
		t[now].sum++; 
		if(!t[now].ch[c]) t[now].ch[c] = ++cnt; 
		now = t[now].ch[c];
	}
	t[now].sum++; 
	return ; 
}

void del(int now, int x){
	for(int i = (1 << 30); i; i >>= 1){
		bool c = i&x;   // 获取第 i 位 0, 1 
		t[now].sum--; 
		if(!t[now].ch[c]) t[now].ch[c] = ++cnt; 
		now = t[now].ch[c]; 
	}
	t[now].sum--;
	return ;  
}

int query(int now, int x, int k){
	bool c1, c2; 
	int ans = 0;
	for(int i = 1 << 30; i; i >>= 1){
		c1 = x&i, c2 = k&i; 
		if(c1 < c2)
			ans += t[t[now].ch[0]].sum; 
		if(c1 && c2)
			ans += t[t[now].ch[1]].sum; 
		if(!c2)
			now = t[now].ch[c1];
		else now = t[now].ch[c1 ^ 1]; 
	}
	return ans; 
}

int main(){
	int q; read(q);
	while(q--){
		int opt, x, k;
		read(opt), read(x); 
		if(opt == 1){
			build(1, x); 
		}
		else if(opt == 2){
			del(1, x); 
		}
		else{
			read(k); 
			printf("%d\n", query(1, x, k)); 
		}
	}
	return 0; 
}

```



---

## 作者：快斗游鹿 (赞：2)

## 思路

看到与异或相关的查询操作，想到 01Trie。

插入时，我们可以将 $x$ 转化为一个二进制数。因为本题中 $x\le10^8$，所以 $30$ 位就够了。接下来从高位到低位插入 Trie 树，并记录每个节点被几个数经过。

删除时，将沿途每个节点的计数器减一就行了。

对于查询，假设当前在考虑第 $i$ 位，那么分类讨论：

$p$ 的第 $i$ 位为 $0$，$l$ 的第 $i$ 位为 $0$：因为不能够取等，所以不会产生贡献，继续。

$p$ 的第 $i$ 位为 $1$，$l$ 的第 $i$ 位为 $0$：同上。

$p$ 的第 $i$ 位为 $0$，$l$ 的第 $i$ 位为 $1$：显然所有第 $i$ 位为 $0$ 的数都一定小于 $l$，加入答案并查询第 $i$ 位为 $1$ 的数即可。

$p$ 的第 $i$ 位为 $1$，$l$ 的第 $i$ 位为 $1$：显然所有第 $i$ 位为 $1$ 的数都一定小于 $l$，加入答案并查询第 $i$ 位为 $0$ 的数即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int Q,t[N*30][5],tot=1,num[N*30],l,ans; 
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
void insert(int x){
	int u=1;
	for(int i=30;i>=0;i--){
		bool op=(x&(1<<i));
		if(!t[u][op])t[u][op]=++tot;
		u=t[u][op];
		num[u]++;
	}
}
void del(int x){
	int u=1;
	for(int i=30;i>=0;i--){
		bool op=(x&(1<<i));
		u=t[u][op];
		num[u]--;
	}
}
void ask(int x){
	int u=1;
	for(int i=30;i>=0;i--){
		bool op=(x&(1<<i));
		bool pp=(l&(1<<i));
		if(pp==1){
			ans+=num[t[u][op]];u=t[u][op^1]; 
		}
		else{
			u=t[u][op];
		}
	}
}
int main(){
	Q=read();
	while(Q--){
		int op,p;op=read();p=read();
		if(op==1){
			insert(p);
		}
		else if(op==2){
			del(p);
		}
		else{
			ans=0;
			l=read();ask(p);
			printf("%d\n",ans);
		}
	}
	return 0;
}
```



---

## 作者：Tx_Lcy (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF817E)
## 思路
字典树入门题。

所谓字典树，就是一颗像字典一样的树，常用来解决异或一类的问题，例如这题。

我们先把每个数按照二进制位分解，设 $u$ 为当前字典树上的节点，如果这个数的二进制位为 $0$，然而字典树上没有这条边，那么新建一条边，然后给这个数经过的每个点权值加 $1$。

至于删除则与插入一样，不再赘述。

而查询操作则有些不一样，首先我们计算 $p_i$ 的这一位与 $l_i$ 的这一位的异或值。若这个值为 $0$，显然我们只能往 $0$ 走。若这个值为 $1$，我们可以选择往 $0/1$ 走，往 $0$ 走就说明这一位异或 $p_i$ 已经小于 $l_i$ 了，所以我们后面填什么都没问题，不妨加上这个点的权值，然后往 $1$ 走。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=5e6+10;
int cnt=1;
struct Trie{
	int c[N][2],num[N];
	inline void insert(int x){
		int u=1;
		for (int i=35;~i;--i){
			bool nowp=(1LL<<i)&x;
			if (!c[u][nowp]) c[u][nowp]=++cnt;
			u=c[u][nowp];++num[u];
		}
	}
	inline void erase(int x){
		int u=1;
		for (int i=35;~i;--i){
			bool nowp=(1LL<<i)&x;
			u=c[u][nowp];--num[u];
		}
	}
	inline int query(int p,int l){
		int ans=0,u=1;
		for (int i=35;~i;--i){
			bool nowp=(1LL<<i)&p,nowl=(1LL<<i)&l;
			bool nowx=nowp^nowl;
			if (((!nowx)^nowp)<nowl) ans+=num[c[u][!nowx]],u=c[u][nowx];
		    else u=c[u][nowx];
		    if (!u) break;//如果这个节点没有了，显然不用继续走下去了
		}
		return ans;
	}
}T;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0); 
	int q;cin>>q;
	while (q--){
		int opt;cin>>opt;
		if (opt==1){int x;cin>>x;T.insert(x);}
		else if (opt==2){int x;cin>>x;T.erase(x);}
		else{int p,l;cin>>p>>l;cout<<T.query(p,l)<<'\n';}
	}
	return 0;
}
```


---

## 作者：Trimsteanima (赞：2)

## $\mathcal{Solution}$

[$\mathtt{blogs}$](https://www.cnblogs.com/wjnclln/p/11649648.html)

第三种操作询问异或后的值，于是自然而然可以想到用 $01trie$，所以可以把 $p_i$ 插入到字典树内，$1$ 操作是 $+1$，$2$ 操作就是 $-1$，$3$操作询问是，把 $p_i$ 的值遍历一遍，如果当前的位上是 $0$，把指针转到 $p_j$ 的位上，否则加上这个位上的数，把指针转到另一边。

## $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>
#define pow(x, i) (x >> i)
using namespace std;

const int N = 6e6 + 10, M = 30;

int cnt[N], trie[N][2], tot = 1, n;

inline int read() {
	int x = 0, k = 1; char c = getchar();
	for (; c < 48 || c > 57; c = getchar()) k ^= (c == '-');
	for (; c >= 48 && c <= 57; c = getchar()) x = x * 10 + (c ^ 48);
	return k ? x : -x;
}

inline void add(int x, int dg) {
    int p = 1;
    for (int i = M; i >= 0; --i) {
        if (dg == 1) trie[p][(pow(x, i) & 1)] = (trie[p][(pow(x, i) & 1)] != 0) ? trie[p][(pow(x, i) & 1)] : (++tot);
        p = trie[p][(pow(x, i) & 1)], cnt[p] += dg;
    }
}

inline int ask(int x, int y) {
    int p = 1;
    int sum = 0;
    for (int i = M; i >= 0; i--) {
        int t = (pow(y, i) & 1), t1 = (pow(x, i) & 1);
        if (t)
            sum += cnt[trie[p][t1]], p = trie[p][t1 ^ 1];
        else 
            p = trie[p][t1];
    }
    return sum;
}

int main() {
    n = read();
    while (n--) {
        int opt = read(), x = read();
        if (opt == 1)
            add(x, 1);
        else if (opt == 2)
            add(x, -1);
        else if (opt == 3) {
            int y = read();
            printf("%d\n", ask(x, y));
        }
    }
    return 0;
}
```

---

## 作者：RuntimeErr (赞：1)

很典的 01Trie，有一道类似的题 [CF665E Beautiful Subarrays](https://www.luogu.com.cn/problem/CF665E)。

插入和删除不必废话，咱讲一讲查询操作的分类讨论：

设 $p_i$ 当前位为 $a$，$l_i$ 当前位为 $b$。

若 $b=1$，则当前位为 $a\oplus0=a$ 的数都可以取，继续查询 $a\oplus1$ 的子树。

若 $b=0$，由于不确定是否都符合，只能继续去查询 $a\oplus0=a$ 的子树。

```cpp
const int N=1e5+10;

int q;
int tre[N<<7][2],siz[N<<7],rt=0,tot=0;

void ins(int &cur,int val,int bit=27){
    if(!cur)cur=++tot;++siz[cur];
    if(bit==-1)return;
    int id=val>>bit&1;
    ins(tre[cur][id],val,bit-1);
}
void del(int cur,int val,int bit=27){
    --siz[cur];
    if(bit==-1)return;
    int id=val>>bit&1;
    del(tre[cur][id],val,bit-1);
}
int query(int cur,int val,int k,int bit=27){
    if(bit==-1||!siz[cur])return 0;
    int id=val>>bit&1,idk=k>>bit&1;
    if(idk==1)return siz[tre[cur][id]]+query(tre[cur][id^1],val,k,bit-1);
    else return query(tre[cur][id],val,k,bit-1);
}

int main(){
    read(q);
    for(int i=1,op,p,l;i<=q;++i){
        read(op),read(p);
        if(op==1)ins(rt,p);
        else if(op==2)del(rt,p);
        else read(l),printf("%d\n",query(rt,p,l));
    }
    return 0;
}
```


---

## 作者：OrezTsim (赞：1)

首先，对于 $1,2$ 操作显然可以对于当前 Trie 上的编号开一个数组记录出现次数。

考虑 $3$ 操作。可以树上前缀和在 $1,2$ 操作的时候把根节点到当前编号路径上全体 $+1$ 或 $-1$。

那么一个节点上的答案就记录了以其为根的子树内的答案总和。

考虑如何统计严格小于。设当前枚举到第 $k$ 位。设 $a_k$ 表示其在二进制下的从高到低第 $k$ 位。

1. $p_k=0,\space l_k=0$。

此时无法判断答案，因为 $0 \text{ xor } 0=0$，目前无法确定后面的位，所以无法确定是否严格小于。

2. $p_k=0,\space l_k=1$。

此时发现符合条件的数的第 $k$ 位一定为 $1$，那么这一位为 $0$ 的全都可以统计答案。

3. $p_k=1,\space l_k=0$。

发现符合条件的数的第 $k$ 位一定为 $1$，无法统计答案，理由同 1。

4. $p_k=1,\space l_k=1$。

发现符合条件的数的第 $k$ 位一定为 $0$。否则为 $1$ 时这一位异或值就会等于 $0$，统计 $1$ 的答案。

没了。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int n, cnt = 1, val[N << 5], ch[N << 5][2];

inline void ins(int x, int v) {
    int cur; val[cur = 1] += v;
    for (int i = 30; ~i; --i) {
        int to = (x >> i) & 1;
        if (!ch[cur][to]) ch[cur][to] = ++cnt;
        cur = ch[cur][to]; val[cur] += v;
    }
    return ;
}

inline int query(int x, int lim) {
    int cur = 1, res = 0;
    for (int i = 30; ~i; --i) {
        int tox = (x >> i) & 1, tolim = (lim >> i) & 1;
        if (tox < tolim) res += val[ch[cur][0]];
        if (tox && tolim) res += val[ch[cur][1]];
        if (!tox) cur = ch[cur][tolim];
        else cur = ch[cur][!tolim];
    }
    return res;
}

inline void solve() {
    int op, x, y; cin >> op >> x;
    if (op < 3) ins(x, op & 1? 1 : -1);
    else cin >> y, cout << query(x, y) << endl; return ;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0), cout.tie(0);
    cin >> n; while (n--) solve(); return 0;
}
```

---

## 作者：_JF_ (赞：0)

[CF817E Choosing The Commander ](https://www.luogu.com.cn/problem/CF817E)

数据结构的题面，看到异或，拍到 01trie 上，全对了！

插入，删除操作其实就是在对应节点上加上对应标记就能表示当前数的出现了。

就算我们根据某个数建立出的节点，然后这个数被删掉了，但是对应节点没必要删掉，把节点数值设成 $0$ 其实是等效的，我们保留节点。

看看操作 $3$，大力对每一个位进行分类讨论，$p_i$ 表示 $p$ 的第 $i$ 位，我们需要快速做出决策：

- $p_i=0，l_i=0$，只可能走 $0$。
- $p_i=0，l_i=1$，$0$ 的贡献全部拿下，走 $1$。
- $p_i=1，l_i=0$，只可以走 $1$。
- $p_i=1，l_i=1$，$1$ 的贡献全部拿下，走 $0$。

下班。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e5+10;
#define int long long
int ch[N*27+1][3],ans,sum[N*27+1],l,t,tot,op,P;
void Build(int x){
	int p=0;
	for(int i=27;i>=0;i--){
		int now=(x>>i&1);
		if(ch[p][now]==0)	ch[p][now]=++tot;
		p=ch[p][now],sum[p]++;	
	}
}
void Clean(int x){
	int p=0;
	for(int i=27;i>=0;i--){
		int now=(x>>i&1);
		p=ch[p][now],sum[p]--;
	}
}
void Slove(int x,int p,int num,bool Op){
	if(Op==0&&p==0)	return ;	
	int now=(x>>num&1),now1=(l>>num&1);
	if(num==0){
		if(now==0&&now1==0)	return ;
		else if(now==0&&now1==1)	ans+=sum[ch[p][0]];
		else if(now==1&&now1==0)	return ;
		else	ans+=sum[ch[p][1]];
		return ;
	}
	if(now==0&&now1==0)	Slove(x,ch[p][0],num-1,0);
	else if(now==0&&now1==1)	ans+=sum[ch[p][0]],Slove(x,ch[p][1],num-1,0);
	else if(now==1&&now1==0)	Slove(x,ch[p][1],num-1,0);
	else	ans+=sum[ch[p][1]],Slove(x,ch[p][0],num-1,0);
}
signed main(){
	cin>>t;
	while(t--){
		cin>>op;
		if(op==1)	cin>>P,Build(P);
		else if(op==2)	cin>>P,Clean(P);
		else	ans=0,cin>>P>>l,Slove(P,0,27,1),cout<<ans<<endl;
	} 
	return 0;
}

```

---

## 作者：Cute__yhb (赞：0)

## 思路

看到异或，想到 01trie。

对于统计数的个数，可以记录每个节点被经过的次数。

添加时，次数加 $1$，删除时，次数减 $1$。

然后是第三种操作。

对于二进制上的第 $i$ 位，设 $p$ 这一位是 $x$，$l$ 这一位是 $y$。

分情况讨论。

- 如果 $y$ 为 $1$，那么这一位一定可以取 $x$，所以，答案加上经过 $x$ 的节点数，往相反方向跳。

- 反之，这一位只有可能取到 $x$，所以，往 $x$ 的方向跳。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
#define re register
#define ri register int
#define rll register long long
#define ld long double
#define endl '\n'
#define fi first
#define se second
#define pii pair<int,int>
#define p_q priority_queue
#define iter iterator
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define nep(i,a,b) for(int i=(a);i>=(b);i--)
#define popcount __builtin_popcount
#define pb push_back
#define mem(a,x) memset((a),x,sizeof(a))
#define eps 1e-8
#define oper operator
#define mk make_pair
int trie[3200005][2],tot=1,sum[6200005];//sum为每个节点被经过的次数
void insert(int s){//增加
	int p=1;
	for(int i=31;i>=0;i--){
		int ch=(s>>i)&1;
		if(!trie[p][ch]){//空节点
			trie[p][ch]=++tot;//新建
		}
		p=trie[p][ch];
		sum[p]++;//多经过一次
	}
}
void del(int s){//删除
	int p=1;
	for(int i=31;i>=0;i--){
		int ch=(s>>i)&1;
		p=trie[p][ch];
		sum[p]--;//减少一次
	}
}
int query(int s,int q){//查询
	int p=1,ans=0;
	for(int i=31;i>=0;i--){
		int ch=(s>>i)&1,k=ch^1,ch1=(q>>i)&1;
		if(ch1){//l这一位为1
			ans+=sum[trie[p][ch]];//一定可以取ch	
			p=trie[p][k];//往相反方向跳
		}else{
			p=trie[p][ch];//只能取ch
		}
	}
	return ans;
}
int main(){
	int t;
	cin>>t;
	while(t--){
		int opt;
		cin>>opt;
		if(opt==1){
			int x;
			cin>>x;
			insert(x);
		}else if(opt==2){
			int x;
			cin>>x;
			del(x);
		}else{
			int p,l;
			cin>>p>>l;
			cout<<query(p,l)<<endl;
		}
	}
    return 0;
}
```

---

## 作者：_HCl_ (赞：0)

01Trie 练手好题。

# CF817E 题解

**题意简述**

维护可重集 $S$，支持插入、删除、和查询有多少个 $x\in S$ 满足 $x\ \text{xor}\ p<l$。

**思路引导**

考虑用 01Trie 来维护。

对于插入和删除的操作，我们用 $sum_x$ 记录 $x$ 节点有多少个数，或者说 $x$ 代表的这个数出现过几次。那么对于插入 $p$ 操作，就是新建 $p$ 所对应的节点，或者在 $p$ 所对应是节点上 $+1$。删除操作同理，就是 $-1$。

接下来讲查询操作的处理。

我们从高位向低位遍历。不难发现：

- 如果 $a$ 的当前位比 $l$ 的当前位大，那么 $a$ 一定比 $l$ 大。我们就结束遍历。
- 如果 $a$ 的当前位比 $l$ 的当前位小，那么 $a$ 一定比 $l$ 小。我们也结束遍历。
- 如果 $a$ 的当前位和 $l$ 的当前位一样大，那么 $a$ 有可能比 $l$ 小。我们继续遍历。

我们再把这个东西放到本题中，我们这么处理。在当前位下：

- 如果 $l$ 的当前位是 $1$

先把字典树上这一位和 $p$ 相同的所有数统计进答案，因为这些数异或后该为是$0$，是一定 $<l$ 的。然后跳转到字典树上这一位是 $\lnot p$ 的这一位，因为异或后是 $1$，也是有机会 $<l$ 的。

- 如果 $l$ 的当前位是 $0$

直接跳转到字典树上这一位是 $p$ 的这一位，因为只有这样，才能使异或后是 $0$，才有希望 $<l$。

这样就可以完成题目要求的查询操作了。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,tot=1;
int t[10000001][2],sum[10000001];
void insert(int p,int k){
	int x=1;
	for(int i=(1<<30);i;i>>=1){
		bool tmp=p&i;
		if(!t[x][tmp])t[x][tmp]=++tot;
		x=t[x][tmp];
		sum[x]+=k;
	}
}
int query(int p,int l){
	int x=1,ans=0;
	for(int i=(1<<30);i;i>>=1){
		bool tmp=p&i,tmp2=l&i;\\一定要用 bool 去存
		if(tmp2)ans+=sum[t[x][tmp]],x=t[x][!tmp];
		else x=t[x][tmp];
	}
	return ans;
}
int main(){
	cin>>n;
	while(n--){
		int op,p,l;
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&p);
			insert(p,1);
		}
		else if(op==2){
			scanf("%d",&p);
			insert(p,-1);
		}
		else{
			scanf("%d%d",&p,&l);
			cout<<query(p,l)<<"\n";
		}
	}
}
```

---

## 作者：LinuF (赞：0)

~~一道板子。~~

### 思路

考虑采用 $01$ 维护信息，加入的时候直接加，删除的时候把一路上前缀和数组 $cnt$ 删掉即可。这道题重点在于怎么统计怎么异或 $p_i$ 小于 $l_i$ 我们考虑走使得异或为 $l_i$ 的路径，每次加上使其更小的位置的前缀和即可。

具体看代码

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename types>
inline void read(types &x){
    x = 0; char c = getchar(); int f = 1;
    while (!isdigit(c)){ if (c == '-') f = -1; c = getchar(); }
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    x *= f; return;
}
inline void read(){}
template<typename types, typename... Args>
void read(types &x, Args&... args){
    read(x), read(args...);
    return;
}
template<typename types>
void write(types x){
    if (x < 0) putchar('-'), x = -x;
    types k = x / 10;
    if (k) write(k);
    putchar(x - k * 10 + '0');
    return;
}
const int N=2e6+5;
int q,son[N][2],cnt[N],idx;
void add(int x){
    int p=0;
    for(int i=30;i>=0;i--){
        int dir=(x>>i)&1;
        if(!son[p][dir]){
            son[p][dir]=++idx;
        }
        p=son[p][dir];
        cnt[p]++;
    }
    return;
}
void del(int x){
    int p=0;
    for(int i=30;i>=0;i--){
        int dir=(x>>i)&1;
        p=son[p][dir];
        cnt[p]--;
    }
}
int ask(int x,int y){// ^x==y
    int res=0,flag=false,p=0;
    for(int i=30;i>=0;i--){
        int dir1=(x>>i)&1,dir2=(y>>i)&1;
        int dir=dir1^dir2;
        if(dir2==1) flag=true;
        if(flag&&dir2==1) res+=cnt[son[p][dir^1]];
        if(!son[p][dir]) break;
        else{
            p=son[p][dir];
        }
    }
    return res;
}
void solve(){
    int q;
    read(q);
    while(q--){
        int type,p,l;
        read(type,p);
        if(type==1){
            add(p);
        }
        if(type==2){
            del(p);
        }
        if(type==3){
            read(l);
            write(ask(p,l));puts("");
        }
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen(".in","r",stdin);
#endif
    solve();
    return 0;
}
```


---

## 作者：daniEl_lElE (赞：0)

01trie。

## 思路

考虑建立 [01trie](https://oi-wiki.org/string/trie/#%E7%BB%B4%E6%8A%A4%E5%BC%82%E6%88%96%E5%92%8C)。插入和删除都是很平凡的，这里不讲。主要想一下询问如何解决。

依然按位枚举。

如果这一位要求小于的异或和 $l$ 上为 $1$，实际异或和可以选择 $0/1$。选择 $0$ 则其他位都不需要考虑了，故直接将该子树内的数加入答案。然后向 $1$ 的方向走。

如果这一位要求小于的异或和 $l$ 上为 $0$，考虑前面都是顶满计算的，这一位只能选 $0$ 且选完并不是所有情况都能选择，故只需向 $0$ 方向走即可。

复杂度的话，$O(q\log p_i)$。不需要任何卡常。

然后循环的时候开 $29$ 足够，我开的 $30$。

比较经典的 01trie 题，非常适合刚学选手练手。

个人觉得话，按照异或和 $0/1$ 去筛选算是一个比较常用的套路了。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define lowbit(x) (x&(-x))
#define mid ((l+r)>>1)
using namespace std;
int trie[4000005][2],num[4000005],cnt=1;
void add(int n){
	int now=1;
	num[now]++;
	for(int i=30;i>=0;i--){
		if(!trie[now][(n>>i)&1]) trie[now][(n>>i)&1]=++cnt;
		now=trie[now][(n>>i)&1];
		num[now]++;
	} 
}
void del(int n){
	int now=1;
	num[now]--;
	for(int i=30;i>=0;i--){
		if(!trie[now][(n>>i)&1]) trie[now][(n>>i)&1]=++cnt;
		now=trie[now][(n>>i)&1];
		num[now]--;
	} 
}
int qry(int n,int m){
	int now=1,ans=0;
	for(int i=30;i>=0;i--){
		if((m>>i)&1){
			ans+=num[trie[now][(n>>i)&1]];
			now=trie[now][((n>>i)&1)^1];
		}
		else{
			now=trie[now][((n>>i)&1)];
		}
	}
	return ans;
}
signed main(){
	int n;
	cin>>n;
	while(n--){
		int opt;
		cin>>opt;
		if(opt==1){
			int x;
			cin>>x;
			add(x);
		}
		if(opt==2){
			int x;
			cin>>x;
			del(x); 
		}
		if(opt==3){
			int x,y;
			cin>>x>>y;
			cout<<qry(x,y)<<endl;
		}
	}
	return 0;
}
```

---

## 作者：万弘 (赞：0)

首先可以做一下[最大异或对](https://www.acwing.com/problem/content/145/) 这题,可能有帮助

考虑查询.假设现在剩下的数$x\in S$都满足对于前高$i-1$位都有$x_j\ xor\ p_j\le l_j(j<i)$.  
显然有:  
- $\forall x\in S,$若$x_i\ xor\ p_i<l_i$,则$x\ xor\ p<l$;若$x_i\ xor\ p_i>l_i$,则$x\ xor\ p>l$;

统计一下这两种情况的数量,对于剩下的$x_i\ xor\ p_i=l_i$的情况,继续处理低位即可.统计情况的数量用01-Trie就好(情况数量就是Trie上的子树和)

时空复杂度$\mathcal O(n \log v)$
```cpp
#define MAXN 100011
struct Trie
{
    ll t[MAXN*40][2],val[MAXN*40],cnt=1;
    void insert(ll x)
    {
        ll u=1;
        for(ll i=30;i>=0;--i)
        {
            ++val[u];
            ll &v=t[u][(x>>i)&1];
            if(!v)v=++cnt;
            u=v;
        }
        ++val[u];
    }
    void erase(ll x)
    {
        ll u=1;
        for(ll i=30;i>=0;--i)
        {
            --val[u];
            u=t[u][(x>>i)&1];
        }
        --val[u];
    }
    ll Query(ll p,ll l)
    {
        ll u=1,res=0;
        for(ll i=30;i>=0;--i)
        {
        	ll v=0;
            for(ll j=0;j<=1;++j)//枚举这一位0还是1
                if((j^((p>>i)&1))<((l>>i)&1))res+=val[t[u][j]];//小于则加上情况数量
                else if((j^((p>>i)&1))==((l>>i)&1))v=t[u][j];//否则继续往下做
            if(!v)break;
            u=v;
        }
        return res;
    }
}t;
int main()
{
    ll n=read();
    while(n--)
    {
        ll op=read(),p=read();
        if(op==1)t.insert(p);
        else if(op==2)t.erase(p);
        else printf("%d\n",t.Query(p,read()));
    }
    return 0;
}
```

---

## 作者：zhmshitiancai (赞：0)

[门](https://www.luogu.com.cn/problem/CF817F)
题意：n个操作，每次加入一个数或者删除已有的一个数，或者询问已有的数中异或x小于y的有多少个。

题解：
### trie树

对于加入和删除操作，在trie树路径上+1或-1即可。trie树中每个点，表示前缀为这个的数的个数。

对于询问操作，一位位扫描，并统计答案即可

### tips
trie树的空间要开够(每个元素的长度*个数)

**code**
```cpp
//love yjl forever
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int INF=0x3f3f3f3f,N=1e5+5,M=27;
int n;
int trie[N*30][2],num[N*30],tot=1;
void add(int x,int y)
{
	int u=1;
	for(int i=M;i>=0;i--)
	{
		int z=(x>>i)&1;
		if(!trie[u][z])
			trie[u][z]=++tot;
		u=trie[u][z];
		num[u]+=y;
	}
}
int query(int x,int y)
{
	int u=1,ans=0;
	for(int i=M;i>=0;i--)
	{
		if((y>>i)&1)
		{
			if((x>>i)&1)
			{
//				cout<<x<<" "<<y<<endl;
				ans+=num[trie[u][1]];
				u=trie[u][0];
			}
			else
			{
//				cout<<x<<" "<<y<<" "<<i<<trie[u][0]<<endl;
				ans+=num[trie[u][0]];
				u=trie[u][1];
			}
		}
		else 
		{
			if((x>>i)&1)
			{
				u=trie[u][1];
			}
			else
			{
				u=trie[u][0];
			}			
		}
		if(u==0) break;
	}
	return ans;
}
int main()
{
/*	freopen("","r",stdin);
	freopen("","w",stdout);*/
	int i;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		int x,y,z;
		scanf("%d",&x);
		if(x==1)
		{
			scanf("%d",&y);
			add(y,1);
		}
		if(x==2)
		{
			scanf("%d",&y);
			add(y,-1);
		}
		if(x==3)
		{
			scanf("%d%d",&y,&z);
			cout<<query(y,z)<<endl;
		}
//		for(int j=1;j<=tot;j++)
//			cout<<num[j]<<" ";
//		cout<<endl;
	}
}

---

