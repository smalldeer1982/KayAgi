# [AGC044C] Strange Dance

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc044/tasks/agc044_c

$ 3^N $ 人の人が輪になって踊っています。 輪の中の人がいる位置に、$ 0,1,\dots,\ 3^{N}-1 $ の番号を、適当な場所から始めて時計回りに付けます。はじめ、これらの位置それぞれに一人の人が立っています。

これから二種類の曲、サルサとルンバが流れ、人々はそれに合わせて踊ります。

- サルサが流れたら、位置 $ i $ にいる人は以下で述べるような位置 $ j $ に移動します。$ j $ は、$ i $ を $ 3 $ 進法で表記し、$ 1 $ という桁をそれぞれ $ 2 $ に、$ 2 $ という桁をそれぞれ $ 1 $ に置き換えて得られる数です (例えば、位置 $ 46 $ の人は位置 $ 65 $ に移動します)。
- ルンバが流れたら、位置 $ i $ にいる人は位置 $ i+1 $ に移動します。ここで、位置 $ 3^N $ は位置 $ 0 $ とみなします。

文字列 $ T=T_1T_2\cdots\ T_{|T|} $ が与えられます。これは、$ T_i= $`S` なら $ i $ 番目に流れる曲がサルサであり、$ T_i= $`R` ならルンバであることを表します。 はじめ位置 $ i $ に立っていた人が、すべての曲が流れたあとに位置 $ P_i $ に立っているとします。 列 $ P_0,P_1,\dots,\ P_{3^N-1} $ を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N\ \le\ 12 $
- $ 1\ \le\ |T|\ \le\ 200,000 $
- $ T $ は `S`、`R` からなる。

### Sample Explanation 1

最初の曲が流れる前に位置 $ i $ に立っていた人を人 $ i $ とします。 1. サルサが一度目に流れたあと、人 $ 0,\ 1,\ 2 $ はそれぞれ位置 $ 0,\ 2,\ 1 $ に立っています。 2. ルンバが流れたあと、人 $ 0,\ 1,\ 2 $ はそれぞれ位置 $ 1,\ 0,\ 2 $ に立っています。 3. サルサが二度目に流れたあと、人 $ 0,\ 1,\ 2 $ はそれぞれ位置 $ 2,\ 0,\ 1 $ に立っています。

## 样例 #1

### 输入

```
1
SRS```

### 输出

```
2 0 1```

## 样例 #2

### 输入

```
2
RRSRSSSSR```

### 输出

```
3 8 1 0 5 7 6 2 4```

## 样例 #3

### 输入

```
3
SRSRRSRRRSRRRR```

### 输出

```
23 9 22 8 3 7 20 24 19 5 18 4 17 12 16 2 6 1 14 0 13 26 21 25 11 15 10```

# 题解

## 作者：rui_er (赞：13)

这道题启示我们 Trie 树是可以支持全局下标加 $1$ 的。

首先把 $3^n$ 个人**从低位到高位**建到三进制 Trie 树上。类似二叉树的左右儿子，我们称由 $0,1,2$ 边连接的儿子为 $0,1,2$ 儿子。

分析两种操作意味着什么：

- Salasa 舞：交换每一个节点的 $1$ 儿子和 $2$ 儿子，打懒标记即可。
- Rumba 舞：这个比较复杂。从最低位开始分析，最低位的变化是 $+1\pmod{3}$，容易想到轮换一下 $0,1,2$ 儿子。但是我们还需要处理进位。发现新的 $1,2$ 儿子轮换后不会有进位，因此不需要管，只有新的 $0$ 儿子会进位。进位后相当于在新的 $0$ 儿子的子树内部进行一个 Rumba 舞的操作，沿着 $0$ 儿子这条链递归下去即可。

于是我们可以 $\mathcal O(n)$ 地进行单次操作。

统计答案类似于建树，dfs 时根据路径上的数计算位置即可。

时间复杂度 $\mathcal O(3^n+|T|\cdot n)$。

```cpp
// Problem: AT_agc044_c [AGC044C] Strange Dance
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/AT_agc044_c
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int K = 13, N = 3e6+5;

int k, n, m, bas[K], ans[N];
char s[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
struct Trie {
	int son[N][3], val[N], tag[N], sz;
	void build(int u, int d, int now) {
		if(d == k) {
			val[u] = now;
			return;
		}
		rep(i, 0, 2) {
			son[u][i] = ++sz;
			build(son[u][i], d+1, now+i*bas[d]);
		}
	}
	void pushdown(int u) {
		if(!tag[u]) return;
		swap(son[u][1], son[u][2]);
		rep(i, 0, 2) tag[son[u][i]] ^= 1;
		tag[u] = 0;
	}
	void add(int u) {
		if(!son[u][0]) return;
		pushdown(u);
		int qwq = son[u][0];
		son[u][0] = son[u][2];
		son[u][2] = son[u][1];
		son[u][1] = qwq;
		add(son[u][0]);
	}
	void dfs(int u, int d, int now) {
		if(d == k) {
			ans[val[u]] = now;
			return;
		}
		pushdown(u);
		rep(i, 0, 2) dfs(son[u][i], d+1, now+i*bas[d]);
	}
}trie;

int main() {
	scanf("%d", &k);
	bas[0] = 1;
	rep(i, 1, k) bas[i] = bas[i-1] * 3;
	n = bas[k];
	trie.build(0, 0, 0);
	scanf("%s", s+1);
	m = strlen(s+1);
	rep(i, 1, m) {
		if(s[i] == 'S') trie.tag[0] ^= 1;
		else trie.add(0);
	}
	trie.dfs(0, 0, 0);
	rep(i, 0, n-1) printf("%d%c", ans[i], " \n"[i==n]);
	return 0;
}
```

---

## 作者：Arghariza (赞：4)

DS 好闪，拜谢 DS。

考虑二进制的情况怎么做，那这两个操作就变成了取反和全局加 $1$。

建 `01-trie`，如果是 $01$ 反转的话打交换儿子的标记即可。考虑全局加 $1$，最后一位 $01$ 状态反转，并且反转后为 $0$ 的位置会对前面的位有进位。递归 $0$ 链并顺路交换左右儿子即可。

然后考虑三进制，其实是相同的：

建三进制 `trie`，$1$ 操作相当于交换 $1,2$ 两个儿子；全局加 $1$ 就是原本的 $0$ 儿子变成 $1$ 儿子、$1$ 儿子变成 $2$ 儿子，以此类推。同样顺着 $0$ 链递归交换即可，单次修改 $O(n)$。

所以每个点上维护其 $3$ 个儿子的编号、反转标记以及当前值对应的下标即可。

总复杂度 $O(3^n+Tn)$，太厉害了。

[提交记录。](https://atcoder.jp/contests/agc044/submissions/38687171)

---

## 作者：GIFBMP (赞：3)

Trie 好题。

首先我们对于 $[0,3^n-1]$ 中的整数按三进制从低位到高位建立 Trie 树，容易看出这是一棵满三叉树，记节点 $x$ 的三个儿子分别为 $ch_{x,0}$，$ch_{x,1}$，$ch_{x,2}$，则 `S` 操作相当于对于树上的每个节点 $x$，交换 $ch_{x,1}$ 和 $ch_{x,2}$。这可以通过基础的打懒标记实现，这里就不多讲了。

那么对于 `R` 操作，我们应该怎么实现呢？注意到 `R` 操作相当于 $x\leftarrow (x+1)\bmod 3^n$，考虑模拟这个加法的过程。由于加法从低位到高位进位，因此要从低位到高位建树。考虑当前这一位上加了 $1$ 之后三个儿子会发生什么变化：容易发现 $ch'_{x,0}=ch_{x,2}$，$ch'_{x,1}=ch_{x,0}$，$ch'_{x,2}=ch_{x,1}$。此时 $ch'_{x,1}$，$ch'_{x,2}$ 都不会发生进位，而 $ch'_{x,0}$ 从 $ch_{x,2}$ 加一得来，会发生进位，需要在 $ch'_{x,0}$ 执行同样的操作。因此我们把原问题转化成了一个子问题，递归处理即可。

时间复杂度 $\Theta(n|S|)$。

Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std ;
const int MAXN = 2e6 + 10 ;
int n , ch[MAXN][3] , pw[15] , cnt = 1 , a[MAXN] , ans[MAXN] ;
int lz[MAXN] ;
void ins (int x) {
	int nw = 1 , y = x ;
	for (int i = 0 ; i < n ; i++ , y /= 3) {
		if (!ch[nw][y % 3]) ch[nw][y % 3] = ++cnt ;
		nw = ch[nw][y % 3] ;
	}
	a[nw] = x ;
}
void chg (int x) {lz[x] ^= 1 , swap (ch[x][1] , ch[x][2]) ;}
void chg2 (int x) {int tmp = ch[x][0] ; ch[x][0] = ch[x][2] , ch[x][2] = ch[x][1] , ch[x][1] = tmp ;}
void pushdown (int x) {if (lz[x]) chg (ch[x][0]) , chg (ch[x][1]) , chg (ch[x][2]) , lz[x] = 0 ;}
void dfs (int x) {
	if (!x) return ;
	pushdown (x) ;
	dfs (ch[x][0]) , dfs (ch[x][1]) , dfs (ch[x][2]) ;
}
char s[MAXN] ;
void upd (int x) {
	if (!x) return ;
	pushdown (x) ; chg2 (x) , upd (ch[x][0]) ;
}
int main () {
	memset (a , -1 , sizeof (a)) ;
	scanf ("%d" , &n) ; pw[0] = 1 ;
	for (int i = 1 ; i <= n ; i++) pw[i] = pw[i - 1] * 3 ;
	for (int i = 0 ; i < pw[n] ; i++) ins (i) ;
	scanf ("%s" , s + 1) ; int len = strlen (s + 1) ;
	for (int i = 1 ; i <= len ; i++) {
		if (s[i] == 'S') chg (1) ;
		else upd (1) ;
	}
	dfs (1) ;
	for (int i = 0 ; i < pw[n] ; i++) {
		int nw = 1 ;
		for (int j = 0 , k = i ; j < n ; j++ , k /= 3)
			nw = ch[nw][k % 3] ;
		ans[a[nw]] = i ;
	}
	for (int i = 0 ; i < pw[n] ; i++) printf ("%d " , ans[i]) ; 
	return 0 ;
}
```

---

## 作者：_HCl_ (赞：1)

写一篇题解加深一下对 Trie 的理解。

# AGC044C 题解

**题意简述**

有 $3^n-1$ 个人围成一个圈，现在有两种操作：

- S 操作：在 $i$ 位置的人前往 $j$ 位置，$j$ 为在三进制下把 $i$ 的 $1$ 换成 $2$，把 $2$ 换成 $1$。
- R 操作：在 $i$ 位置的人前往 $i+1$ 位置。特别地，$3^n-1$ 的人前往 $0$ 位置。

给定操作序列，求最后一开始在 $i$ 位置的人最后在什么位置。

**思路引导**

我们考虑构建一棵从低位到高位的三叉 Trie 树，字典树的叶子节点存初始位置。最后询问的时候就可以通过节点将初始位置映射到最终位置了。

接下来考虑怎么处理操作。

对于 S 操作，考虑直接交换每一个节点的 $1$ 儿子和 $2$ 儿子。然而这样的效率太低了，所以我们考虑打上懒标记，再访问到的时候再进行处理和下放。

对于 R 操作，如果只考虑当前位的变化情况，不难发现，其实就是 $0\rightarrow 1\rightarrow 2\rightarrow 0$ 的轮换。

接下来我们考虑怎么处理进位。不难发现，只有 $2$ 轮换后（也就是新的 $0$ 儿子）会发生进位。而这个进位也是 $+1$ 的，所以就相当于在 $0$ 子树内进行 R 操作。所以我们可以递归地处理该操作。

查询时跟建树相同，把整棵 Trie 遍历一遍，遍历到子节点的时候把答案记下来。

**代码**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
string str;
int tot=1;
int t[10000001][3],tag[10000001],num[10000001],bas3[50],ans[10000001];
void init(){
	bas3[0]=1;
	for(int i=1;i<=n;++i)bas3[i]=bas3[i-1]*3;
}
void build(int x,int k,int p){//x存当前节点，k是层数，p是当前节点对应的值
	if(k==n){
		num[x]=p;//到叶子节点了
		return;
	}
	for(int i=0;i<=2;++i){
		t[x][i]=++tot;//建新节点
		build(tot,k+1,p+i*bas3[k]);
	}
}
void pushdown(int x){//下放标记
	if(tag[x]){
		swap(t[x][1],t[x][2]);
		for(int i=0;i<=2;++i)tag[t[x][i]]^=1;
		tag[x]=0;
	}
}
void add(int x){
	if(t[x][0]==-1)return;
	pushdown(x);//记得下放
	int tmp=t[x][2];
	t[x][2]=t[x][1],t[x][1]=t[x][0],t[x][0]=tmp;//轮换
	add(t[x][0]);//对 0 子树进行相同操作
}
void getans(int x,int k,int p){
	if(k==n){
		ans[num[x]]=p;//记录答案
		return;
	}
	pushdown(x);
	for(int i=0;i<=2;++i)
		getans(t[x][i],k+1,p+i*bas3[k]);
}
int main(){
	memset(t,0xff,sizeof(t));
	cin>>n;
	cin>>str;
	init();//预处理出3的i次
	build(1,0,0);//建树
	for(int i=0;i<str.length();++i){
		if(str[i]=='S')tag[1]^=1;//打上交换标记
		else add(1);//+1操作
	} 
	getans(1,0,0);//查询
	for(int i=0;i<bas3[n];++i)
		cout<<ans[i]<<" ";
	cout<<"\n";//AtCoder特有的答案末尾回车
}
```

---

## 作者：Yu_Chengxuan (赞：0)

trie 对于 lazy tag 的应用，好题。

我们考虑维护 0-2trie , 分别考虑两个操作。

Rumba 舞: 

实际上是让每一个节点 $ x←(x+1) \bmod 3^n$ ， 即全局加一。

对于全局加一是简单的，从低位到高位找第一个出现的 0 , 
随后将这个位置后面的 1 都变成 0 , 我们由低位到高位
建树即可解决。

Salasa 舞：

这个时候就要引入 lazy tag 思想了:
我们发现只需交换每一个节点的 1 儿子和 2 儿子, 所以我们可以直接对根节点打标记, 在全局加一时就下放标记, 这样就可以保证 log 的复杂度了。

时间复杂度显然是 $O(|T|\cdot n + 3^n)$。

## code


```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 3e6 + 10;
int n, m, rt;
int tot, t[N][3], w[N], tag[N], power[N], ans[N];
void build(int &u, int dep, int sum) {
    if (!u)
        u = ++tot;
    if (dep == n) {
        w[u] = sum;
        return;
    }
    for (int i = 0; i <= 2; i++) {
        t[u][i] = ++tot;
        build(t[u][i], dep + 1, sum + i * power[dep]);
    }
}
void addone(int u) {
    if (!t[u][0])
        return;
    if (tag[u]) {
        for (int i = 0; i <= 2; i++) tag[t[u][i]] ^= 1;
        swap(t[u][1], t[u][2]);
        tag[u] = 0;
    }
    int tmp = t[u][0];
    t[u][0] = t[u][2];
    t[u][2] = t[u][1];
    t[u][1] = tmp;
    addone(t[u][0]);
}
void dfs(int u, int dep, int sum) {
    if (dep == n) {
        ans[w[u]] = sum;
        return;
    }
    if (tag[u]) {
        for (int i = 0; i <= 2; i++) tag[t[u][i]] ^= 1;
        swap(t[u][1], t[u][2]);
        tag[u] = 0;
    }
    for (int i = 0; i <= 2; i++) {
        dfs(t[u][i], dep + 1, sum + i * power[dep]);
    }
}
char s[N];
signed main() {
    scanf("%lld %s", &n, s + 1);
    m = strlen(s + 1);
    power[0] = 1;
    for (int i = 1; i <= n; i++) {
        power[i] = power[i - 1] * 3;
    }
    build(rt, 0, 0);
    for (int i = 1; i <= m; i++) {
        if (s[i] == 'S') {
            tag[rt] ^= 1;
        } else {
            addone(rt);
        }
    }
    dfs(rt, 0, 0);
    for (int i = 0; i <= power[n] - 1; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
```

做完这道题后也可以去做: P6018，学习更多样的 trie  trick。

---

## 作者：freoepn (赞：0)

看到三进制先建出一颗 Trie 树，叶子节点表示位置，叶子上记录该位置上站着的人，考虑如何进行修改，第一种修改需要交换所有节点的 $1$ 和 $2$ 儿子，再根节点打上懒标记向下传递即可，第二种修改相当于把最后一位为 $0$ 的变为 $1$，为 $1$ 的变为 $2$，为 $2$ 的变为 $0$ 并对倒数第二位产生进位，可以从上往下递归实现，最后搜索维护最终序列即可。


```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
string s;
int siz;
int tr[2000005][3];
int tag[2000005];
int a[2000005],b[2000005];
void pushdown(int x) {
  for (int i = 0; i <= 2; i++) {
    tag[tr[x][i]] ^= tag[x];
  }
  if (tag[x]) swap(tr[x][1], tr[x][2]);
  tag[x] = 0;
}
void build(int x, int y, int z) {
  if (y == n) {
    a[x] = z;
    return;
  }
  for (int i = 0; i <= 2; i++) {
    tr[x][i] = ++siz;
    build(siz, y + 1, z + i * pow(3, y));
  }
}
void change(int x, int y) {
  if (y == n) {
    return;
  }
  pushdown(x);
  swap(tr[x][1], tr[x][2]);
  swap(tr[x][1], tr[x][0]);
  change(tr[x][0], y + 1);
}
void dfs(int x, int y, int z) {
  if (y == n) {
    b[a[x]] = z; 
    return;
  }
  pushdown(x);
  for (int i = 0; i <= 2; i++) {
    dfs(tr[x][i], y + 1, z + i * pow(3, y));
  }
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> s;
  build(0, 0, 0);
  for(int i = 0;i < s.size();i++){
    if(s[i] == 'S'){
      tag[0] ^= 1;
    }else{
      change(0,0);
    }
  }
  dfs(0,0,0);
  for(int i = 0;i < pow(3,n);i++){
    cout << b[i]<< " ";
  }
  return 0;
}
```

---

## 作者：WRuperD (赞：0)

sto nantf orz

## 正文

算得上相当有意思以及启发性的数据结构题了。

三进制表示联想到我们可以建立一个三叉树。类似于 Trie 一样的，按三进制从低位到高位建立一个 Trie 树。一个非常好的性质这是一个完美三叉树。

接下来我们可以考虑怎么维护每一种操作。

#### Salasa 舞
对于这种操作，相当于对于树上每一个点都交换他们的 1,2 两个儿子。打个标记即可支持。

#### Rumba 舞
这相当于什么呢？我们发现，相当于把原来的 0 号儿子给到 1 号儿子，把原来的 1 号儿子给到 2 号儿子，把原来的 2 号儿子给到 0 号儿子。前两者没有进位，所以不用管，发现原来 2 号儿子会产生一个进位操作。这相当于什么呢？这相当于在这个儿子子树内再进行一次 Rumba 舞操作。递归求解即可。

总复杂度 $O(3^n+Tn)$

[code](https://atcoder.jp/contests/agc044/submissions/49335959)

---

## 作者：AK_heaven (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_agc044_c)

考虑用 012 Trie 来做。

考虑建树，为了维护 +1 操作，我们只有从低位往高位建树，因为进位是从低位往高位进位。

考虑 S 舞蹈，我们发现实际上就是对于所有非叶子节点，子树 1 和 子树 2 进行交换操作，懒标记维护即可，时间复杂度均摊。

考虑 R 舞蹈，我们从根节点开始进行树的遍历，每次都有 0 $\to$ 1，1 $\to$ 2，2 需要进位操作，所以 2 $\to$ 0，并且在该子树中仍然需要进行相同操作，其中数字代表该节点三个子树的编号，时间复杂度 $O(\log n)$，可以过。

最后因为进位我们是直接进位，并没有取模，所以最后答案里面记得取一下模。


```cpp
#include <bits/stdc++.h>

#define L(i, a, b) for(int i = (a); i <= (b); i++)
#define R(i, a, b) for(int i = (a); i >= (b); i--)
#define pii pair<int, int>
#define ll long long
#define vi vector<int>
using namespace std;

const int N = 5e6 + 10;

#define l1 tr[p].ch[1]
#define l2 tr[p].ch[2]
#define l0 tr[p].ch[0]

struct Trie {
	int ch[3], val, tag; 
}tr[N];

int n, idx = 1, a[N];

void insert(int x, int id) {
	int p = 1;
	L(i, 0, 12) {
		int &to = tr[p].ch[x % 3];
		x /= 3;
		if(!to) to = ++idx;
		p = to;
	}
	tr[p].val = a[p] = id;
}

void pushdown(int p) {
	if(!tr[p].tag) return ;
	swap(tr[p].ch[1], tr[p].ch[2]);
	tr[tr[p].ch[0]].tag ^= 1;
	tr[tr[p].ch[1]].tag ^= 1;
	tr[tr[p].ch[2]].tag ^= 1;
	tr[p].tag = 0;
}

void dfs(int p) {
	if(!p) return ;
	pushdown(p);
	swap(tr[p].ch[0], tr[p].ch[1]);
	swap(tr[p].ch[0], tr[p].ch[2]);
	dfs(tr[p].ch[0]);
}

int ans[N];

void out(int p, int now, int i) {
	if(!p) return ;
	pushdown(p);
	if(tr[p].val) ans[tr[p].val-1] = now;
	out(tr[p].ch[0], now, i*3); out(tr[p].ch[1], now+i, i*3); out(tr[p].ch[2], now+2*i, i*3);
}

char op[N]; int m;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> op+1;
	m = 1;
	L(i, 1, n) m *= 3;
	L(i, 0, m-1) insert(i, i+1);
	n = strlen(op+1);
	L(i, 1, n) {
		if(op[i] == 'S') tr[1].tag ^= 1;
		else dfs(1);
	}
	out(1, 0, 1);
	L(i, 0, m-1) cout << ans[i] % m << ' ';
	return 0;
}

```

---

