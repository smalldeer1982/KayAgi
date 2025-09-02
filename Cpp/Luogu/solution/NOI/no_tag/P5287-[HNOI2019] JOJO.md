# [HNOI2019] JOJO

## 题目背景

JOJO 的奇幻冒险是一部非常火的漫画。漫画中的男主角经常喜欢连续喊很多的 “欧拉” 或者 “木大”。

## 题目描述

为了防止字太多挡住漫画内容，现在打算在新的漫画中用 $x$ 欧拉或者 $x$ 木大表示有 $x$ 个欧拉或者木大。

为了简化内容我们现在用字母表示喊出的话。

我们用数字和字母来表示一个串，例如 `2 a 3 b` 表示的串就是 $aabbb$。

一开始漫画中什么话都没有，接下来你需要依次实现 $n$ 个操作，总共只有 $2$ 种操作：

- 第一种：`1 x c` 在当前漫画中加入 $x$ 个 $c$，表示在当前串末尾加入 $x$ 个 $c$ 字符。保证当前串是空串或者串尾字符不是 $c$。
- 第二种：`2 x` 觉得漫画没画好将漫画还原到第 $x$ 次操作以后的样子，表示将串复原到第 $x$ 次操作后的样子，如果 $x=0$ 则是将串变成空串。

如果当前串是 $bbaabbb$，第 $4$ 次操作后串是 $bb$，则 `2 4` 会使 $bbaabbb$ 变成 $bb$，保证 $x$ 小于当前操作数。

众所周知空条承太郎十分聪明，现在迪奥已经被打败了，他开始考虑自己的漫画中的一些问题：

对于一个串的每个前缀 $A$，都有一个最长的比它短的前缀 $B$ 与前缀 $A$ 的一个后缀匹配，设这个最长的前缀 $B$ 的长度为 $L$。$L$ 为 $0$ 时意味着 $B$ 是一个空串。

每一次操作后，你都需要将当前的串的所有前缀的 $L$ 求和并对 $998244353$ 取模输出告诉空条承太郎，好和他的白金之星算出的答案对比。

比如 $bbaaabba$ 的 $L$ 分别是 $0, 1, 0, 0, 0, 1, 2, 3$，所以对于这个串的答案就是 $7$。


## 说明/提示

#### 样例解释

| 操作 | 此时的串 | 答案 |
| :----------: | :----------: | :----------: |
| $1$ | `aa` | $0+1=1$ |
| $2$ | `aabbb` | $0+1+0+0+0=1$ |
| $3$ | `aabbbaa` | $0+1+0+0+0+1+2=4$ |
| $4$ | `aabbbaab` | $0+1+0+0+0+1+2+3=7$ |
| $5$ | `aabbb` | $0+1+0+0+0=1$ |
| $6$ | `aabbbaaa` | $0+1+0+0+0+1+2+2=6$ |
| $7$ | `aabbbaaabb` | $0+1+0+0+0+1+2+2+3+4=13$ |
| $8$ | `aabbbaaa` | $0+1+0+0+0+1+2+2=6$ |
| $9$ | `aabbb` | $0+1+0+0+0=1$ |
| $10$ | `aabbbaaaaaaa` | $0+1+0+0+0+1+2+2+2+2+2+2=14$ |
| $11$ | `aabbbaaaaaaaccccc` | $0+1+0+0+0+1+2+2+2+2+2+2+0+0+0+0+0=14$ |

#### 数据范围

$20\%$ 的数据满足 $n\leq 300$ 且每个 $1$ 操作中的 $x\leq 300$；

另有 $30\%$ 的数据满足 $n\leq 10 ^ 5$ 且每个 $1$ 操作中的 $x=1$；

另有 $30\%$ 的数据满足 $n\leq 10 ^ 5$ 且不含 $2$ 操作；

$100\%$ 的数据满足 $n\leq 10 ^ 5$ 且每个 $1$ 操作中的 $x\leq 10 ^ 4$。

## 样例 #1

### 输入

```
11
1 2 a
1 3 b
1 2 a
1 1 b
2 2
1 3 a
1 2 b
2 6
2 5
1 7 a
1 5 c
```

### 输出

```
1
1
4
7
1
6
13
6
1
14
14
```

# 题解

## 作者：Isonan (赞：28)

（此题考查了对KMP的理解以及~~乱搞能力~~有理有据的优化）

首先对于可持久化的操作，我们可以将其离线下来并在操作树上dfs。

题意显然可以转化为对一个字符串做KMP，并求$\sum nxt_i$。

现在我们考虑已经有了一些字段，现在要在后面加入一个新的字段，如何计算新字段的贡献。

我们可以从之前的最后一个字符开始跳$nxt$，如果跳到一个位置，它后面正好有一长串长度为$y$的$c$，我们就可以进行匹配。

由于保证了$c$不同于之前的最后一个字符，我们知道如果$nxt$跳到某个字段的中间，那么它是一定没有用的，可以自己yy一下。

所以我们定义$nxt'_i$为从当前的第$i$个字段的最后一个点开始，一直跳KMP的$nxt$所跳到的第一个点所在的字段，满足该点是其所在字段的最后一个字符。

以上算法大概是50分，由于数据过水，实际可以AC。

对于hack数据，我们考虑如何使其复杂度正确。（以下优化借鉴于@142857cs的代码orz）

每次跳$nxt'$时，我们考虑进行一些优化：

**如果当前字符串存在周期，我们直接跳到所有周期的第一个。**

否则就和原来一样跳$nxt$。

这样显然每次长度至少$/2$，复杂度就不需要均摊了，直接就是$O(nlogn)$

（如有错误请不吝赐教）

代码：

```cpp

// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using std::min;
std::map<std::pair<char,short>,int>ma[100001];
char get(){
    char ch=getchar();
    while(ch<'a'||ch>'z')ch=getchar();
    return ch;
}
int end[100010],pre[100010],cnt,n,length[100010],nxt[100010],ope[100010][2],len,P=998244353,f[100001];
int head[100010],Nxt[200010],b[200010],k,cn;
void push(int s,int t){
    Nxt[++k]=head[s];
    head[s]=k;
    b[k]=t;
}
long long ans[100010],fin[100010],val[100010][3];
inline long long getsum(register long long l,register long long r){
    if(l>r)return 0;
    return (l+r)*(r-l+1)/2;
}
void dfs(int x,int f){
    if(ope[x][0]){
        int tem=nxt[len];
        ++len;
        ans[len]=0;
        val[len][0]=ope[x][0];
        val[len][1]=ope[x][1];
        val[len][2]=val[len-1][2]+ope[x][1];
        nxt[len]=0;
        if(len==1){
            ans[len]=getsum(1,val[1][1]-1);
        }
        else{
        	int lastgap=len-tem;
            while(tem&&(val[tem+1][0]!=ope[x][0]||val[tem+1][1]!=ope[x][1])){
                if(tem-nxt[tem]==lastgap)tem=tem%lastgap+lastgap;
                lastgap=tem-nxt[tem];
                tem=nxt[tem];
            }
            if(tem||(val[1][0]==ope[x][0]&&val[1][1]<=ope[x][1]))nxt[len]=tem+1;
            else nxt[len]=tem;
            tem=nxt[len-1];
        	lastgap=len-1-tem;
            long long lastlength=0;
            while(lastlength<val[len][1]&&tem){
                if(val[tem+1][0]==ope[x][0]&&val[tem+1][1]>lastlength){
                    ans[len]+=getsum(val[tem][2]+lastlength+1,val[tem][2]+min(val[tem+1][1],val[len][1]));
                    lastlength=val[tem+1][1];
                }
                if(tem-nxt[tem]==lastgap)tem=tem%lastgap+lastgap;
                lastgap=tem-nxt[tem];
                tem=nxt[tem];
            }
            if(lastlength<val[len][1]&&val[1][0]==val[len][0]){
                ans[len]+=getsum(lastlength+1,min(val[len][1],val[1][1]));
                lastlength=std::max(lastlength,min(val[len][1],val[1][1]));
                ans[len]+=val[1][1]*(val[len][1]-lastlength);
            }
            ans[len]+=ans[len-1];
        }
    }
    fin[x]=ans[len];
    for(int i=head[x];i;i=Nxt[i]){
        dfs(b[i],x);
    }
    if(ope[x][0])--len;
}
int read(){
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x;
}
void write(long long x){
    if(x>9)write(x/10);
    putchar((x%10)+'0');
}
signed main(){
    scanf("%d",&n);
    for(int i=1,opt,x;i<=n;i++){
        opt=read(),x=read();
        if(opt==1){
            ope[i][0]=get();
            ope[i][1]=x;
            auto y=std::make_pair(ope[i][0],ope[i][1]);
            f[i]=ma[f[i-1]][y];
            if(!f[i]) ma[f[i-1]][y]=i,push(f[i-1],i),f[i]=i;
        }
        else{
            f[i]=f[x];
        }
    }
    dfs(0,-1);
    for(int i=1;i<=n;i++)write(fin[f[i]]%P),putchar('\n');
}

```

---

## 作者：ywy_c_asm (赞：21)

~~数组不清空，爆0两行泪~~

首先你发现这个串是由一堆二元组$(x_i,c_i)$构成的，然而这个匹配是基于一个个字符匹配的，看上去似乎和这些$O(n)$个二元组没啥关系。但是这题的最重要的性质就是如果一个前缀和一个后缀能够匹配，那么他们的除去开头的和结尾的剩下中间的所有二元组一定能匹配。举个例子：

$aaa|bb|ccc|a|c|bbbb……aaaaa|bb|ccc|a|c|bbb$

这个显然可以有一个$Border$是$aaabbcccacbbb$，这中间的$bbcccac$的部分是完全匹配的二元组序列$(2,b)(3,c)(1,a)(1,c)$，但是开头和结尾的二元组可能长度有所不同，具体来说，**后缀的开头长度不小于前缀，结尾长度不超过前缀**，我们需要让他同时满足这两个条件才能够匹配。

很显然那个2的可持久化操作我们需要离线建棵树然后dfs（其实在线在这棵树上做做应该也是可以的……），我们就考虑当前点到根的串就行了。

既然那中间的二元组需要严格的匹配，那我们不妨把这个求一个$next$，而且既然我的第一个二元组可以在长度上不严格的匹配，干脆就在构建$next$数组的时候特判一下与第一个二元组的匹配不就行了？这样我们就只需考虑结尾的二元组了，而我们也正是要考虑结尾添加一个二元组会增加多少答案，这样好。

这里要特别注意的是，由于我们现在是在树上跑$next$，然而普通串上的复杂度是**均摊**$O(n)$的，放到树上复杂度就不对了……（这显然可以造一条链，底下挂个菊花来卡），因此我们需要像自动机一样令$nxt[i][c][x]$为在与$i$号点这个前缀一样的后缀后面加个二元组$(x,c)$，$next$应该到哪，这个$nxt[i][c]$可以套路的用主席树存，它可以直接从$next[i]$转移过来，然后单点修改。

（接下来为了方便描述，我们就称这个串的**fail树**为每个二元组的位置以$next$为父亲构建的树，要注意与这棵询问的树区分开）

然后我们考虑添加一个二元组$(x,c)$，我们肯定要考虑它的上一个位置$u$的$fail$树上到根的一条祖先链，新加的这$x$个字符可能就会把$next$继承自这条链上的某个后继字符为$c$的祖先，然而，这样的祖先会有很多，但是我们希望找到的$next$尽量长（毕竟是最长的$Border$），我们以这张图为例：

![](https://cdn.luogu.com.cn/upload/pic/58634.png)

（其中黑色部分是这条fail链，红色的是一个长度为$x$的二元组$(x,c)$，这是我们当前在添加的新二元组，上面3个蓝色的是后继字符为$c$的3个祖先的二元组）

我们对$[1,x]$所有的新添加的$c$字符进行分段考虑，$[1,x_3]$这个部分显然就要找$(x3,c)$这个祖先进行匹配，对于任意的$i\in[1,x_3]$，$next_i=deep_{(x_3,c)}+i$，同理对于任意的$i\in[x_3+1,x_2]$，$next_i=deep_{(x_2,c)}+i$，对于$i>x2$，$next_i$显然就是0了。那么我们可以把这个拆成两部分，我们设$mx[i][c]$为$i$的所有fail祖先中，后继字符为$c$的最长的$x$，那么显然在$[1,\min(mx[u][c],x)]$这个部分里的$next$是有值的，它们肯定要加$i$，那么可以先把$\sum_{i=1}^{\min(mx[u][c],x)}i$这个等差数列的和加到答案里，然后就是考虑能够匹配的祖先的深度之和了。注意到我们在$dfs$的时候，深度显然是递增的，那么我们可以用区间强行赋值！令$f[i][c][x]$为$i$的$fail$祖先对一个在后面$x$位置的$c$字符的最大的贡献，这个仍然用主席树存，我们每遇到一个$(x,c)$，都把$[1,x]$这个区间强行赋为当前点的深度因为这一定是最优的，这样在主席树上区间求和就行了。

另外我们需要特判像下面这样的这种情况：

$aaaa|bbbb|aaaaaa$

考虑最后一段$(6,a)$的$next$数组依次为$1,2,3,4,4,4$，而不是$1,2,3,4,0,0$，这是因为匹配的是第一个二元组，这个特判一下就好了。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define ll long long
#define p 998244353
#define up(_o) data[_o] = (data[lef[_o]] + data[rgh[_o]]) % p
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	inline char cget() {
	    char c;
	    while ((c = getchar()) || 23333)
	        if (c >= 'a' && c <= 'z')
	            return (c);
	}
	typedef struct _b {
	    int dest;
	    int nxt;
	    int x;
	    int c;
	} bian;
	bian memchi[1000001], stk[100011];
	int gn = 1, heads[200001], f[200011][26], nxt[200011][26];
	inline void add(int s, int t, int x, int c) {
	    memchi[gn].dest = t;
	    memchi[gn].nxt = heads[s];
	    memchi[gn].x = x;
	    memchi[gn].c = c;
	    heads[s] = gn;
	    gn++;
	}
	int lef[20000001], rgh[20000001];
	int data[20000001], anss[200001], changes[20000001];
	int id[200001], gseg = 1;
	int set(int rl, int rr, int l, int r, int tree, int x, int chg) {
	    int me = gseg;
	    gseg++;
	    if (rl == l && rr == r) {
	        changes[me] = x;
	        data[me] = (x * (ll)(r - l + 1)) % p;
	        return (me);
	    }
	    int mid = (l + r) >> 1;
	    if (changes[tree])
	        chg = changes[tree];
	    if (rl > mid) {
	        if (chg) {
	            lef[me] = gseg;
	            gseg++;
	            changes[lef[me]] = chg;
	            data[lef[me]] = (chg * (mid - l + 1)) % p;
	            rgh[me] = set(rl, rr, mid + 1, r, rgh[tree], x, chg);
	        } else
	            lef[me] = lef[tree], rgh[me] = set(rl, rr, mid + 1, r, rgh[tree], x, 0);
	    } else {
	        if (rr <= mid) {
	            if (chg) {
	                rgh[me] = gseg;
	                gseg++;
	                changes[rgh[me]] = chg;
	                data[rgh[me]] = (chg * (ll)(r - mid)) % p;
	                lef[me] = set(rl, rr, l, mid, lef[tree], x, chg);
	            } else
	                rgh[me] = rgh[tree], lef[me] = set(rl, rr, l, mid, lef[tree], x, 0);
	        } else {
	            lef[me] = set(rl, mid, l, mid, lef[tree], x, chg);
	            rgh[me] = set(mid + 1, rr, mid + 1, r, rgh[tree], x, chg);
	        }
	    }
	    up(me);
	    return (me);
	}
	int query(int rl, int rr, int l, int r, int tree) {
	    if (!tree)
	        return (0);
	    int mid = (l + r) >> 1;
	    if (changes[tree])
	        return ((changes[tree] * (ll)(rr - rl + 1)) % p);
	    if (rl == l && rr == r)
	        return (data[tree]);
	    if (rl > mid)
	        return (query(rl, rr, mid + 1, r, rgh[tree]));
	    if (rr <= mid)
	        return (query(rl, rr, l, mid, lef[tree]));
	    return ((query(rl, mid, l, mid, lef[tree]) + query(mid + 1, rr, mid + 1, r, rgh[tree])) % p);
	}
	int sp = 1, fail[200001], mx[200001][26];
	inline ll dft(ll n) { return (((n * (n + 1)) >> 1) % p); }
	void dfs(int pt, int deep) {
	    for (register int i = heads[pt]; i; i = memchi[i].nxt) {
	        if (pt) {
	            for (register int j = 0; j < 26; j++)
	                mx[pt][j] = mx[fail[pt]][j], f[pt][j] = f[fail[pt]][j], nxt[pt][j] = nxt[fail[pt]][j];
	        } else {
	            for (register int j = 0; j < 26; j++) mx[pt][j] = 0, f[pt][j] = 0, nxt[pt][j] = 0;
	        }
	        if (pt == 0)
	            stk[1] = memchi[i];
	        fail[memchi[i].dest] = query(memchi[i].x, memchi[i].x, 1, 10000, nxt[pt][memchi[i].c]);
	        if (pt == 0) {
	            anss[memchi[i].dest] = dft(memchi[i].x - 1);
	        } else {
	            if (!fail[pt]) {
	                if (memchi[i].c != stk[1].c)
	                    anss[memchi[i].dest] = anss[pt];
	                else
	                    anss[memchi[i].dest] =
	                        (anss[pt] + dft(min(memchi[i].x, mx[pt][memchi[i].c])) +
	                         (ll)(memchi[i].x - min(memchi[i].x, mx[pt][memchi[i].c])) * mx[pt][memchi[i].c]) %
	                        p;
	            } else {
	                anss[memchi[i].dest] = (anss[pt] + dft(min(memchi[i].x, mx[pt][memchi[i].c])) +
	                                        (ll)query(1, memchi[i].x, 1, 10000, f[pt][memchi[i].c])) %
	                                       p;
	                if (memchi[i].x > mx[pt][memchi[i].c] && memchi[i].c == stk[1].c) {
	                    anss[memchi[i].dest] =
	                        (anss[memchi[i].dest] + stk[1].x * (ll)(memchi[i].x - mx[pt][memchi[i].c])) % p;
	                }
	            }
	        }
	        f[pt][memchi[i].c] = set(1, memchi[i].x, 1, 10000, f[fail[pt]][memchi[i].c], deep, 0);
	        if (pt == 0) {
	            nxt[pt][memchi[i].c] =
	                set(memchi[i].x, 10000, 1, 10000, nxt[fail[pt]][memchi[i].c], memchi[i].dest, 0);
	        } else
	            nxt[pt][memchi[i].c] =
	                set(memchi[i].x, memchi[i].x, 1, 10000, nxt[fail[pt]][memchi[i].c], memchi[i].dest, 0);
	        mx[pt][memchi[i].c] = max(mx[fail[pt]][memchi[i].c], memchi[i].x);
	        dfs(memchi[i].dest, deep + memchi[i].x);
	    }
	}
	void ywymain() {
	    int n = get();
	    int cur = 0, gpt = 1;
	    for (register int i = 1; i <= n; i++) {
	        int op = get();
	        if (op == 2)
	            cur = id[get()];
	        else {
	            int x = get();
	            char c = cget();
	            add(cur, gpt, x, c - 'a');
	            cur = gpt;
	            gpt++;
	        }
	        id[i] = cur;
	    }
	    dfs(0, 0);
	    for (register int i = 1; i <= n; i++) printf("%d\n", anss[id[i]]);
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：dsidsi (赞：17)

# Description

两种操作

 - `1 x c` 在当前字符串末尾添加$x$个$c$字符。
 - `2 x` 把当前字符串变为第$x$次操作之后的状态。

每次操作后，输出当前字符串的$next$数组只和。

操作数$\leq 10^5$，$c \leq 10^4$。

# Solution

`2`操作显然可以用离线建树解决。

考虑如果一段前缀匹配一段后缀，那么除了第一段的字符，其他段的二元组$(x,c)$需要满足完全相等。这本质上可以将$(x,c)$视为一种特殊的字符进行匹配。

先考虑在当前串的末尾新加入一个二元组$(x,c)$怎么计算答案，显然是不断跳$next$，如果当前前缀后接的字符为$c$，那么可以增加一段首项为当前前缀长度，公差为$1$的等差数列的贡献（要与之前的贡献取$max$，也就是只能覆盖之前没覆盖的位置）。

而如果在$next$链上有恰好等于$(x,c)$的二元组，那么当前串结尾的$next$指向最靠后的二元组，否则指向$0$。因为如果存在一个二元组$(x',c)$满足$x'>x$，那么由于下次添加的字符一定与当前字符不同，所以一定无法匹配。

但是由于$kmp$的复杂度是均摊的，所以直接把上述算法套进树上`dfs`是行不通的。

考虑一个叫$kmp$自动机的东西，它的本质是把$kmp$跳$next$的过程预处理，由于本题字符集大小很大，用主席树维护。

设$f_{i,j,k}$表示在串的$s_{i-1}$位置添加一个字符$(j,k)next$所到达的位置，同理设$g_{i,j,k}$表示增加的答案。在`dfs`的时候，修改$f_{i,x,c}$的值，并将$g_{i,x,1..c}$设置为首项为当前串长度，公差为$1$的等差数列。`dfs`下一层前把$f_{i+1}$的状态由$f_{next[i]+1}$继承过来。

由于每次操作都是把数列设为一个公差为$1$的等差数列，所以只用维护首项所覆盖的位置，剩下的用高斯求和单独算即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int gi()
{
	char c = getchar();
	while (c < '0' || c > '9') c = getchar();
	int sum = 0;
	while ('0' <= c && c <= '9') sum = sum * 10 + c - 48, c = getchar();
	return sum;
}

inline char gc()
{
	char c = getchar();
	while (c < 'a' || c > 'z') c = getchar();
	return c;
}

typedef long long ll;
const int maxn = 100005, M = 1e4 + 7, mod = 998244353;

int n;
int val[maxn], pos[maxn], ans[maxn], a[maxn], b[maxn], top;
vector<int> to[maxn];

int rt[maxn][26], mx[maxn][26], tot;
struct seg
{
	int l, r, lch, rch, sum, lzy, nxt;
} t[maxn * 60];

#define mid ((l + r) >> 1)

inline void new_node(int &s) {t[++tot] = t[s]; s = tot;}
inline void add(int s, int v, int len) {t[s].sum = (ll)v * len % mod; t[s].lzy = v;}
inline void push_down(int s, int l, int r)
{
	if (!t[s].lzy) return ;
	new_node(t[s].lch); add(t[s].lch, t[s].lzy, mid - l + 1);
	new_node(t[s].rch); add(t[s].rch, t[s].lzy, r - mid);
	t[s].lzy = 0;
}

void modify(int &s, int l, int r, int x, int v, int p)
{
	new_node(s);
	if (r < x) return add(s, v, r - l + 1);
	if (l == r) return t[s].nxt = p, add(s, v, 1);
	push_down(s, l, r);
	modify(t[s].lch, l, mid, x, v, p);
	if (x > mid) modify(t[s].rch, mid + 1, r, x, v, p);
	t[s].sum = (t[t[s].lch].sum + t[t[s].rch].sum) % mod;
}

void query(int &s, int l, int r, int x, int &ans, int &nxt)
{
	if (r < x) return ans = (ans + t[s].sum) % mod, void();
	if (l == r) return ans = (ans + t[s].sum) % mod, nxt = t[s].nxt, void();
	push_down(s, l, r);
	query(t[s].lch, l, mid, x, ans, nxt);
	if (x > mid) query(t[s].rch, mid + 1, r, x, ans, nxt);
}

inline int getsum(int x) {return ((ll)x * (x + 1) >> 1) % mod;}

void dfs(int u)
{
	++top;
	int x = val[u] / M, y = val[u] % M, nxt = 0;
	a[top] = val[u]; b[top] = b[top - 1] + y;
	if (top == 1) ans[u] = getsum(y - 1);
	else {
		ans[u] = (ans[u] + getsum(min(mx[top][x], y))) % mod;
		query(rt[top][x], 1, M, y, ans[u], nxt);
		if (!nxt && a[1] / M == x && b[1] < y) nxt = 1, ans[u] = (ans[u] + (ll)b[1] * max(0, y - mx[top][x])) % mod;
	}
	mx[top][x] = max(mx[top][x], y);
	modify(rt[top][x], 1, M, y, b[top - 1], top);
	for (int v : to[u]) {
		memcpy(mx[top + 1], mx[nxt + 1], sizeof(mx[top + 1]));
		memcpy(rt[top + 1], rt[nxt + 1], sizeof(rt[top + 1]));
		ans[v] = ans[u]; dfs(v);
	}
	--top;
}

int main()
{
	n = gi();
	for (int op, x, i = 1; i <= n; ++i) {
		op = gi(); x = gi();
		if (op == 1) val[++tot] = (gc() - 'a') * M + x, pos[i] = tot, to[pos[i - 1]].push_back(pos[i]);
		else pos[i] = pos[x];
	}

	for (int i : to[0]) {
		tot = 0;
		memset(rt[1], 0, sizeof(rt[1]));
		memset(mx[1], 0, sizeof(mx[1]));
		dfs(i);
	}

	for (int i = 1; i <= n; ++i) printf("%d\n", ans[pos[i]]);
	
	return 0;
}
```

---

## 作者：dspr (赞：15)

# HNOI2019 JOJO

**upd:突然发现这个做法是可以强制在线的，下面的描述有所改动**

被鱼那题送退役了，很生气。

然后我Day1快下考的时候口胡了一个做法

今天想起来之后就写了一下，发现它过了，它过了，它过了。

woc要是不写鱼，我可以多出3个小时写T2,T3,随便打也能进队啊啊啊啊啊啊

好了，不扯了，我们言归正传。



我们发现，若两个串匹配，那么他们中间的每一段的长度也必须相同，只有第一段和最后一段可能不是完整的一段，因此我们可以直接将每一段相同的字符看成一个新的字符(**我们暂且把新的字符叫做字段**)，求next数组。

由于其中一个匹配串必须是整个串的前缀，因此，第一字段的处理几乎与一般的KMP相同，只有一种特殊情况**:若某个字段与第一字段的字符相同，并且长度大于第一字段**，也是可以匹配的，因为你可以用这一段的后面一段字符去匹配第一段字符

比如说 对于串aabbbaabbaaabbb，我们可以把它看成 a2 b3 a2 b2 a3 b3 共6个字段的串

这个新串的next数组为 0 0 1 0 1 2 

此时$next[4]=0$而不是$1$，因为后一个字符一定与$b$不同，一定匹配不上下一个字符，这个next对于后面的匹配来说是无意义的，所以我们可以近似的认为，b2与b3不能匹配，但是在统计b2这段字符的答案会出现问题，因为实际上这一段是可以与前面的匹配的，所以我们需要在跳next的过程中，顺便将每个字符的next求出来计入答案。

以上是我的考场做法，可以获得50分，但由于一些奇怪的错误我只获得了20分。

贴下50分代码

```
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int _=1e5+5,M=2e4,yl=998244353;
void inc(int &x,int y){x+=y;if(x>=yl)x-=yl;}
int n;
namespace task1{
    struct Node{
        int a[305],b[305],f[305],len,ans;
        int js(ll l,ll r){
            if(l>r)return 0;
            return (l+r)*(r-l+1)/2%yl;
        }
        void insert(int x){
            if(len==0)return ans=js(1,x%M-1),b[1]=x%M,f[1]=0,a[++len]=x,void();
            ll k=f[len],mx=0; a[++len]=x;
            while(1){
                if(a[k+1]/M==x/M){
                    ll l=min(x%M,a[k+1]%M);
                    inc(ans,js(b[k]+mx+1,b[k]+l));
                    mx=l;
                }
                if(a[k+1]==x||!k)break; k=f[k];
            }
            if(a[k+1]==x)f[len]=k+1,b[len]=b[k]+x%M;
            else if(a[1]/M==x/M&&a[1]%M<x%M)
                f[len]=1,inc(ans,max(0ll,(x%M-mx))*b[1]%yl);
            b[len]=b[len-1]+x%M;
        }
    }T[305];
    void main(){
        for(int i=1;i<=n;++i){
            int opt,x;cin>>opt;
            if(opt==1){
                char c;cin>>x>>c;
                T[i]=T[i-1];
                T[i].insert(c*M+x);
                cout<<T[i].ans<<endl;
            }
            else cin>>x,T[i]=T[x],cout<<T[i].ans<<endl;
        }
    }
}
namespace task2{
    int a[_],b[_],f[_],len,ans;
    ll js(ll l,ll r){
        if(l>r)return 0;
        return (l+r)*(r-l+1)/2%yl;
    }
    void insert(int x){
        if(len==0)return ans=js(1,x%M-1),b[1]=x%M,f[1]=0,a[++len]=x,void();
        ll k=f[len],mx=0; a[++len]=x;
        while(1){
            if(a[k+1]/M==x/M){
                ll l=min(x%M,a[k+1]%M);
                inc(ans,js(b[k]+mx+1,b[k]+l));
                mx=l;
            }
            if(a[k+1]==x||!k)break; k=f[k];
        }
        if(a[k+1]==x)f[len]=k+1,b[len]=b[k]+x%M;
        else if(a[1]/M==x/M&&a[1]%M<x%M)
            f[len]=1,inc(ans,max(0ll,(x%M-mx))*b[1]%yl);
            //我考场上把b[1]写成了a[1]丢了30分
        b[len]=b[len-1]+x%M;
    }
    void main(){
        for(int i=1;i<=n;++i){
            int opt,x;cin>>opt;
            char c;cin>>x>>c;
            insert(c*M+x);
            cout<<ans<<endl;
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n;
    if(n<=300)task1::main();
    else task2::main();
}

```

至于扩展到100分。

但是暴力跳next的复杂度是均摊的，我们还是不能接受。

因此我们考虑建立一个大概可以叫做KMP自动机的东西，由于经过转化后字符集很大，我们考虑通过可持久化线段树，来维护这个KMP自动机的转移，每次只需要将一个字符的next的转移拷贝过来，并把后一个字段加进转移即可。

再考虑如何统计答案，我们发现，假设有一个字段是长度为L，那么每次匹配到它的另一个字段的前L个字符会被它匹配掉，而我们要求匹配最长，所以我们只需要找到最后一段可以匹配的，依然考虑通过可持久化线段树维护一类字段的第$i$个能匹配多长的字符。每次需要进行的操作就变成了前缀赋值与前缀求和。

因此我们就可以通过可持久化线段树的，单点修改，前缀赋值，前缀求和来完成所有1操作。

而这样做可以顺便解决2操作带来的对历史版本进行操作的问题

时空复杂度均为$O(nlog n)$

鉴于洛谷上抄题解太多了，防不胜防，所以代码就不贴了，有需要的可以私信我。

---

## 作者：云浅知处 (赞：8)

我们来刻画本题这样的字符串的 border：可以发现，一些后缀段能和一些前缀段构成 border，需要他们除了开头和结尾之外的二元组 $(x,c)$ 都完全相同。对于首尾两个二元组，需要后缀的开头段比前缀长，前缀的结尾段比后缀长。

考虑直接把二元组 $(x,c)$ 当作字符来进行字符串匹配。我们考虑加入一个 $(x,c)$ 对答案的贡献。如果没有撤销操作，我们可以直接暴力跳 fail link 并记录当前遇到的所有节点中 $c$ 这条出边长度的前缀最大值 $w_1$，每遇到一个更大的 $w_2$，设这里前面的总长度为 $L$，我们就给答案加上 $\sum_{i=w_1+1}^{w_2}L+i$；当遇到和 $(x,c)$ 完全相同的二元组时停下。时间复杂度和 kmp 相同。

注意 kmp 的复杂度是均摊的，即使我们能够存下所有的版本，也不能在扩展新版本时直接由原版本暴力跳 fail link 扩展而来此时有两种做法。

注意到一个字符串 $s$ 的所有 border 构成 $O(\log|s|)$ 段等差数列，我们考虑利用这一性质优化跳 fail link 的过程。具体来说，我们对当前的 $s[1\cdots k]$ 考虑其最长 border，设其为 $k-d$，那么 $d$ 是 $s[1\cdots k]$ 的周期。由弱周期引理，所有 $\le k-d$ 的数中只有 $d$ 的倍数是周期（因为弱周期引理需要 $p+q\le |s|$，所以是 $\le k-d$ 而非 $\le k$），这对应着所有长度 $\ge d$ 的位置只有形如 $k-xd$ 的位置是 border（并且进一步由于 $d$ 是周期，这些 border 的下一个字符总是相同的）。

因此我们只需要令 $k\leftarrow k\bmod d+d$，即最小的一个 $\ge d$ 的形如 $k-xd$ 的位置，即可。这里很多题解想要解释 $+d$ 的原因，但实际上注意上面我们的论断都需要弱周期引理那个 $p+q\le |s|$ 的条件，因此只能说明长度 $\ge d$ 的位置中有且仅有 $k-xd$ 这些 border，如果贸然跳到 $k\bmod d$ 就可能会错误地漏掉若干 border。

回到本题。我们上面说过，所有 $\ge d$ 的长度形如 $k-xd$ 的位置均为 border，且**这些 border（除了最后一个）后面的字符相同**，由于我们需要维护的是前缀最大值，因此这些字符的贡献都被 $k$ 这一位置覆盖，可以直接忽略他们。注意由于最后一个 border 的字符不同，我们需要先小跳一步计算贡献，然后再跳等差数列。因此就可以在不均摊的 $O(\log n)$ 时间内完成跳 fail link 的过程了。只需要把操作离线并建立操作树即可。

```cpp
#include<bits/stdc++.h>

#define ll long long
#define int long long

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,int y,int p=mod){
	int ans=1;
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
mt19937 rnd(time(0));
int randint(int l,int r){return rnd()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}

const int N=5e5+5;

struct Edge{
	pair<int,int>cost;
	int to;
	Edge(int T,pair<int,int>C):to(T),cost(C){}
	Edge(){}
};

int col[N],len[N],id[N],n,fail[N],ans[N],top=0,pre[N],tot,pos[N];
vector<Edge>G[N];

#define fi first
#define se second
#define mk make_pair

int Ans[N];
vector<int>qs[N];

bool chk(int p,int x,int c){
	if(p==0)return col[pos[p]+1]==c&&len[pos[p]+1]<=x;
	return col[pos[p]+1]==c&&len[pos[p]+1]==x;
}
int sum(int l,int r){
	if(l>r)return 0;
	return (1ll*(r-l+1)*(l+r)/2)%mod;
}
int ins(int lst,int x,int c){
	if(lst==0){
		int q=++tot;ans[q]=sum(1,x-1);fail[q]=0;
		++top,len[top]=x,col[top]=c,pos[q]=top,pre[q]=x,id[top]=q;
		return q;
	}
	int p=fail[lst],D=0,curmx=0,ls=lst;
	while(p&&(!chk(p,x,c))){
		int cc=col[pos[p]+1],xx=len[pos[p]+1];
		if(cc==c&&xx>curmx)add(D,sum(pre[p]+curmx+1,pre[p]+min(xx,x))),curmx=min(xx,x);
		if(ls-p==p-fail[p]){//small jump 
			int d=p-fail[p];
			ls=p,p=p%d+d;
		}
		else ls=p,p=fail[p];
	}
	int q=++tot;
	if(chk(p,x,c))fail[q]=id[pos[p]+1],add(D,sum(pre[p]+curmx+1,pre[p]+len[pos[p]+1])),add(D,1ll*(pre[p]+len[pos[p]+1])*(x-max(len[pos[p]+1],curmx))%mod);//注意这里有细节
	else{
		fail[q]=0;
		int cc=col[pos[p]+1],xx=len[pos[p]+1];
		if(cc==c&&xx>curmx)add(D,sum(pre[p]+curmx+1,pre[p]+min(xx,x))),curmx=min(xx,x);
	}
	++top,len[top]=x,col[top]=c,pos[q]=top,pre[q]=pre[lst]+x,id[top]=q;
	Mod(ans[q]=ans[lst]+D);
	return q;
}

void dfs(int u,int p){
	for(auto e:G[u]){
		int x=e.cost.fi,c=e.cost.se,v=e.to;
		int q=ins(p,x,c);
		dfs(v,q);
	}
	for(auto i:qs[u])Ans[i]=ans[p];
	len[top]=col[top]=id[top]=0,top--,pre[p]=ans[p]=fail[p]=pos[p]=0;
}

int nodes[N];

signed main(void){

#ifdef YUNQIAN
	freopen("jojo6.in","r",stdin);
	freopen("jojo6.out","w",stdout);
#endif

	n=read();
	int now=0;
	for(int i=1;i<=n;i++){
		int op=read();
		if(op==1){
			int x=read();char c=getchar();
			while(c<'a'||c>'z')c=getchar();
			++tot;
			G[now].emplace_back(Edge(tot,mk(x,c-'a')));
			now=tot;
		}
		else now=nodes[read()];
		qs[now].emplace_back(i),nodes[i]=now;
	}
	tot=0;dfs(0,0);
	for(int i=1;i<=n;i++)cout<<Ans[i]%mod<<'\n';

	return 0;
}
```

---

## 作者：FjswYuzu (赞：5)

不难发现是求字符串做 KMP 之后的 $\sum next(i)$。众所周知 $next(i)$ 表示字符串长度为 $i$ 的前缀的最长真 $\operatorname{Border}$ 长度，于是答案显而易见……但是字符串很长，还有回溯操作，怎么办？

首先想没有回溯操作的怎么做。容易发现这是仅有的一个字符串，然后总共有 $n$ 段，不难发现我们的复杂度应该只跟段数挂上关系。用 $s_{c_i}$ 表示字符串 $s$ 第个极长 $i$ 段的字符是 $s_{c_i}$，$s_{l_i}$ 表示字符串 $s$ 第 $i$ 个极长段长度，那么定义两个字符串 $s,t$ 近似相等为：

1. 字符串上面的极长相同字符的段数相同，记为 $p$；   
2. $\forall i,1 \leq i \leq p,s_{c_i} = t_{c_i}$；   
3. $\forall i,2 \leq i \leq p,s_{l_i} = t_{l_i}$ 且 $s_{l_1} \leq t_{l_1}$。

又定义类 $\operatorname{Border}$ 表示将 $\operatorname{Border}$ 定义中的两个字符串相等改为近似相等。采用这种新的比较方式来进行 KMP 值得尝试。显然采取增量法计算，我们新加入一段字符，遍历没加入之前的这个字符串的所有类 $\operatorname{Border}$。如果类 $\operatorname{Border}$ 后的字符与新加入的字符相同，那么就会造成贡献。容易发现我们加入的前缀其实是一段一段造成贡献（因为类 $\operatorname{Border}$ 后面的字符段长度可能不足让所有字符造成贡献），这个贡献类似于一个等差数列（特殊的，如果第一段的字符和新加入的字符相同，造成的贡献会有些许不同，但不难处理，可以自己思考），直接计算即可。

于是可以直接用改变匹配方式的 KMP $O(n)$ 解决没有回溯操作的情况。

然后出现了回溯操作。建出状态树可以直接解决这个问题，但是出现的另一个问题是 KMP 的复杂度是均摊的，显然不可能支持这样一个类似于「持久化」的操作，能不能采取一些方法优化呢？根据 Border 那套理论，有一个性质是，一个字符串 $s$ 长度大于 $\frac{|s|}{2}$ 的 $\operatorname{Border}$ 构成一个等差数列，我们能否用这个性质优化呢？答案是，可以但不完全可以，手推导之后发现如果直接跳到小于 $\frac{|s|}{2}$ 的地方会出现问题，因为无法证明一个不是原串的 $\operatorname{Border}$ 的字符串不是一个原串的类 $\operatorname{Border}$（实际上这个题你直接模公差都不会出问题，因为数据太水了……）。那么就跳到比较接近 $\frac{|s|}{2}$ 的类 $\operatorname{Border}$ 就行，正确性和复杂度都能保证。

这样每次计算和求 $next(i)$ 的复杂度都变成单次 $O(\log n)$ 了，复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL MOD=998244353;
vector<LL> G[100005];
LL n,pos[100005],ans[100005],l[100005];
char c[100005];
LL cnt;
LL getSum(LL L,LL R){return (L<=R)?(R-L+1)%MOD*(MOD+1)/2%MOD*(L+R)%MOD:0;}
LL nxt[100005],seql[100005],len[100005],sum[100005];
char seqc[100005];
void dfs(LL now)
{
	for(auto st:G[now])
	{
		char stc=c[st];
		LL stl=l[st];
		++cnt;
		sum[cnt]=0,len[cnt]=len[cnt-1]+stl,seql[cnt]=stl,seqc[cnt]=stc;
		if(cnt==1)	sum[cnt]=getSum(0,stl-1);
		else
		{
			LL j,lst;
			j=nxt[lst=cnt-1];
			while(j && (seqc[j+1]!=seqc[cnt] || seql[j+1]!=seql[cnt]))
			{
			    if(nxt[j]<=lst/2)   lst=j,j=nxt[j];
			    else
			    {
					int d=j-nxt[j];
					int tmp=lst/2;
					j=j%d;
					j+=((tmp-j)/d+1)*d;
					lst=j+d;
			    }
			}
			if(j || (seqc[j+1]==seqc[cnt] && seql[j+1]==seql[cnt]))	nxt[cnt]=j+1;
			else if(seqc[1]==seqc[cnt] && seql[1]<=seql[cnt])	nxt[cnt]=1;
			else	nxt[cnt]=0;
			j=nxt[lst=cnt-1];
			LL maxn=0;
			while(j && maxn<seql[cnt])
			{
				if(seqc[j+1]==seqc[cnt] && seql[j+1]>maxn)
				{
					sum[cnt]=(sum[cnt]+getSum(len[j]+maxn+1,len[j]+min(seql[j+1],seql[cnt])));
					maxn=seql[j+1];
				}
			    if(nxt[j]<=lst/2)   lst=j,j=nxt[j];
			    else
			    {
					int d=j-nxt[j];
					int tmp=lst/2;
					j=j%d;
					j+=((tmp-j)/d+1)*d;
					lst=j+d;
			    }
			}
			if(maxn<seql[cnt])
			{
				if(seqc[1]==seqc[cnt])
				{
					LL x=min(seql[1],seql[cnt]);
					sum[cnt]=(sum[cnt]+getSum(maxn+1,x))%MOD;
					sum[cnt]=(sum[cnt]+(seql[cnt]-max(maxn,x))*seql[1]%MOD)%MOD;
				}
			}
		}
		ans[st]=sum[cnt]=(sum[cnt]+sum[cnt-1])%MOD;
		dfs(st);
		--cnt;
	}
}
int main(){
	scanf("%lld",&n);
	for(LL i=1;i<=n;++i)
	{
		LL op;
		scanf("%lld",&op);
		if(op==1)
		{
			LL t;
			char s[2];
			scanf("%lld %s",&t,s);
			pos[i]=++cnt;
			G[pos[i-1]].push_back(pos[i]);
			l[pos[i]]=t,c[pos[i]]=*s;
		}
		else
		{
			LL x;
			scanf("%lld",&x);
			pos[i]=pos[x];
		}
	}
	cnt=0;
	dfs(0);
	for(LL i=1;i<=n;++i)	printf("%lld\n",ans[pos[i]]);
	return 0;
}
```

---

## 作者：NOI_Winner (赞：1)

本题需要进行可持久化的操作，我们可以考虑先将所有操作离线并将所有第一种操作建成一棵树。

为简化问题，我们先考虑无还原操作。我们可以考虑将一段同一次插入的字符看成一个字符求出 $nxt$ 数组。这样的做法之所以正确，是因为题目保证每一次插入时当前末尾字符与待插入字符不同。考虑原字符串的 $nxt$ 数组，如果最后一个字符的 $nxt$ 值正好跳到一段同一次插入的字符中间，那新插入的字符一定无法在该位置匹配。我们不断往前跳 $nxt$，记录新插入字符中已经匹配的个数，并统计答案。如果当前位置后有一段与新插入字符**长度和字符都相等**的一段字符，则新插入字符的 $nxt$ 就等于它，否则为 $0$。

再考虑树上操作，发现 KMP 算法的均摊复杂度在树上并不适用，因为可以构造出上面是一条链、底下是菊花状的树。考虑优化，设当前跳到的位置为 $p$，$p$ 和前面所有字符的总长度为 $s_p$，如果 $2 \times s_{nxt_p}\ge s_p$，则说明当前串存在周期，接下来一段 $nxt$ 对答案都没有贡献，也不会成为新字符的 $nxt$，我们直接跳到周期中最前面的位置就行了，此时长度必然减少一半。如果 $2 \times s_{nxt_p}\lt s_p$，直接跳 $nxt$ 就行了。时间复杂度 $O(nlogn)$。

代码示例：
```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
constexpr int maxn = 100000, mod = 998244353, inv2 = 499122177;
int head[maxn + 5], vert[2 * maxn + 5], nt[2 * maxn + 5], tot;
int len[maxn + 5], ans[maxn + 5], pos[maxn + 5], id[maxn + 5], nxt[maxn + 5], last[maxn + 5];
ll sum[maxn + 5];
char c[maxn + 5];

inline void add(int x, int y)
{
    vert[++tot] = y;
    nt[tot] = head[x];
    head[x] = tot;
}

inline int get_sum(ll l, ll r)     //   求 l + (l + 1) + (l + 2) + ... + (r - 1) + r
{
    if (l > r) return 0;
    l %= mod; r %= mod;
    return (l + r) % mod * ((r - l + 1) % mod) % mod * inv2 % mod;
}

void dfs(int x, int f, int dep)    //   dfs 求解答案
{
    id[dep] = x; pos[x] = dep; sum[x] = sum[f] + len[x];    //  id 记录当前字符串，pos 记录深度，sum 记录原字符串总长度
    int cur = f, cnt = 0; ans[x] = ans[f]; last[x] = x;     //  ans 记录答案， last 记录周期的开头
    if (0 == f)
        ans[x] = get_sum(1, len[x] - 1);
    else if (f > 0)
    {
        while (cur >= 0)
        {
            int y = id[pos[nxt[cur]] + 1];
            if (c[y] == c[x])
            {
                ans[x] = (ans[x] + get_sum(sum[nxt[cur]] + cnt + 1, sum[nxt[cur]] + min(len[y], len[x]))) % mod;
                if (len[y] == len[x])
                { cur = y; break; }
                else
                    cnt = max(cnt, min(len[x], len[y]));
            }
            if (last[cur] != cur) cur = last[cur];
            else cur = nxt[cur];
        }
        if (cur >= 0)
        {
            nxt[x] = cur;
            if (pos[cur] << 1 >= pos[x])
                last[x] = last[cur];
        }
        if (-1 == cur && cnt < len[x] && c[id[1]] == c[x])
        {
            ans[x] = (ans[x] + 1ll * (len[x] - cnt) * len[id[1]] % mod) % mod;
            nxt[x] = id[1];
        }
    }

    for (int i = head[x]; i; i = nt[i])
    {
        int y = vert[i];
        dfs(y, x, dep + 1);
    }
}

int main()
{
    int n; scanf("%d", &n);
    for (int i = 1, cur = 0; i <= n; i++)
    {
        int op; scanf("%d", &op);
        if (1 == op)
        {
            scanf("%d %s", &len[i], &c[i]);
            add(cur, i); cur = i; pos[i] = i;
        }
        else
        {
            int last; scanf("%d", &last);
            ans[i] = -1; cur = pos[last];
            pos[i] = cur;
        }
    }
    nxt[0] = -1;
    dfs(0, -1, 0);

    for (int i = 1; i <= n; i++)
        if (ans[i] >= 0)
            printf("%d\n", (ans[i] + mod) % mod);
        else
            printf("%d\n", (ans[pos[i]] + mod) % mod);
    
    return 0;
}
```

---

## 作者：Felix72 (赞：1)

节选自我的 [[字符串] Border 和回文前后缀的性质、维护和运用](https://www.luogu.com.cn/article/96hy0bja)。

#### Part A

因为不要求可持久化，所以回退版本并不是什么难点，建出操作树或者直接暴力删都是可以的。问题在于如何维护加字符操作。我们知道若两串字符相等，除了首尾两部分，把剩下的二元组 $(x, c)$ 看成单个**压缩字符**，它们组成的字符串应该也是完全相等的。不妨对压缩字符做 KMP。边跳 $nxt$ 边计算贡献。

计算贡献的部分可以参考我的代码，

#### Part B

回滚 ban 掉了均摊复杂度，算贡献 ban 掉了 KMP 自动机，但是我们还有一条路，即运用 $O(\log)$ 段等差数列性质。

这个性质的由来是字符串的周期，那么一段等差 $border$ 对应的前缀后面接的字符串都有一段 LCP，即这个周期。周期至少有一个压缩字符，则它们对答案的贡献一致，可以直接跳过，跳到大于周期 $t$ 的最小 $border$。

这样暴力跳 $nxt$ 的复杂度变为严格 $O(\log n)$，可以通过。

#### Part C

加了注释。

```cpp
/* Good Game, Well Play. */
#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 100010, mod = 998244353;
int n, ver[N]; long long res[N];
struct Edge {int to, x; char c;}; vector < Edge > tr[N]; int idx = 1;

struct Char {int x, c;} s[N]; int len, prx[N], nxt[N];
inline bool find_son(int p, int x, int c)
{
	if(!p) return (s[p + 1].c == c && s[p + 1].x <= x); // 如果在字符串的开头，那么开头少几个字符也是可以匹配上的，只要 x 个字符不全用完就行了
	else return (s[p + 1].c == c && s[p + 1].x == x); // 不然必须要求 (x, c) 二元组相等
}
inline int get_sum(int l, int r)
{if(l > r) return 0; return 1ll * (l + r) * (r - l + 1) / 2 % mod;}
inline int insert(int x, char c)
{
	s[++len] = {x, c}; prx[len] = prx[len - 1] + s[len].x;
	if(len == 1) return get_sum(1, x - 1); // 同 KMP 和 Z 函数理，len = 1 需要特判
	int p = nxt[len - 1], lst = len, maxlen = 0; long long delt = 0;
  // 这里记录 maxlen 的意思是，当前有 x 个字符等着算贡献，因为要找最大 border，所以贪心把前面能找的都找了，后面的以后再去找
	while(p && !find_son(p, x, c))
	{
		if(s[p + 1].c == c && min(x, s[p + 1].x) > maxlen)
		{
			delt = (delt + get_sum(prx[p] + maxlen + 1, prx[p] + min(x, s[p + 1].x)));
			maxlen = s[p + 1].x;
		}
		if(lst - p == p - nxt[p])
		{
			int t = p - nxt[p];
			lst = p; p = p % t + t;
		}
		else lst = p, p = nxt[p];
	}
	if(find_son(p, x, c))
	{
		nxt[len] = p + 1;
		delt = (delt + get_sum(prx[p] + maxlen + 1, prx[p] + s[p + 1].x));
		delt = (delt + 1ll * s[p + 1].x * (x - max(maxlen, s[p + 1].x))); // 这是针对匹配到开头，x 个字符不全用完所补加的贡献
	}
	else
	{
		nxt[len] = p;
		if(s[p + 1].c == c && min(s[p + 1].x, x) > maxlen)
			delt = (delt + get_sum(maxlen + 1, maxlen + min(s[p + 1].x, x)));
	}
	return delt;
}
inline void roll()
{
	s[len] = {0, 0}; prx[len] = nxt[len] = 0;
	--len;
}
inline void solve(int now)
{
	for(Edge li : tr[now])
	{
		res[li.to] = (res[now] + insert(li.x, li.c)) % mod;
		solve(li.to); roll();
	}
}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n; ver[0] = 1;
	for(int i = 1, p = 1; i <= n; ++i)
	{
		int op, x; char c; cin >> op;
		if(op == 1)
		{
			cin >> x >> c;
			++idx; tr[p].push_back({idx, x, c});
			p = idx; ver[i] = p;
		}
		else
		{
			cin >> x;
			ver[i] = p = ver[x];
		}
	}
	solve(1);
	for(int i = 1; i <= n; ++i) cout << res[ver[i]] << '\n';
	return 0;
}
/*

*/
```

---

## 作者：Hoks (赞：0)

## 前言
好题，但是感觉好像还不算很难做。

广告：[『从入门到入土』串串学习笔记](https://www.luogu.com.cn/article/dv6dig1o)。
## 思路分析
看到可持久化，又没有强制在线，果断离线建树。

发现题目求的是所有前缀的最长 border 长度之和。

其实也就是 $\sum nxt_i$。

看眼数据范围发现字符串长度可能很长，但是总共的连续段最多只会有 $10^5$ 个。

这启发我们把一个连续段合并起来一起计算答案。

其实可以发现如果答案比目前的最底段长度长的话，中间部分都是整段整段的，可以直接快速计算。

那么我们先考虑下最底这段的增加如何计算。

用 KMP 匹配的知识，我们知道是不断的跳 $nxt_i$ 计算，但是由于长度原因所以要记得取 $\max$ 计算。

每次增加的一段也就是一段新的等差数列，其公差为 $1$，可以用小学数学快速计算。

特殊的，如果整段成功匹配上了，就可以更新 $nxt$，否则就不行。

因为正如前面所言，只有完全匹配才可以继续拓展。

所以每一种整段都可以看做是一个字符。

现在我们就解决了链的情况，但是题目是一颗树。

由于 KMP 的复杂度是均摊的，所以只需要链套菊花就可以卡爆了。

我们考虑如何优化这个过程。

**多使用一些空间多记录点东西！**

具体的，我们考虑使用 KMP 自动机。

预处理 KMP 跳 $nxt$ 的过程。

考虑 $f_{i,j,k}$ 表示从 $i-1$ 这个点加上 $j$ 个 $k$ 后的 $nxt$ 位置。

那么我们进入这个点时修改添加上字符的值并增加答案为等差数列。

在进入下一层时令 $f_{i+1}=f_{nxt_i+1}$ 即可。

因为字符集拓展后很大，所以使用主席树维护。

本质而言，我们就是在维护 nxt 链，返回的时候把链的下面部分扔掉。

**Tips：复制节点别复制错了，修改前记得复制，宏定义语句多加括号。**
## 代码

```cpp
#include<bits/stdc++.h>
#define ls (lc[p])
#define rs (rc[p])
#define mid ((l+r)>>1)
#define calc(x) ((((x+1)*(x))>>1)%mod)
#define int long long
using namespace std;
const int N=1e5+10,V=1e4+10,M=27,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,m,tot,d,w[N],a[N],g[N],ans[N];vector<int>e[N];
int mx[N][M],rt[N][M],lc[N<<6],rc[N<<6],nxt[N<<6],s[N<<6],lz[N<<6];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
	#define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
	inline int read()
	{
		int x(0),t(1);char fc(getchar());
		while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
		while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
		return x*t;
	}
	inline void flush(){fwrite(out,1,length,stdout);length=0;}
	inline void put(char c){if(length==9999999) flush();out[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
	inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
	inline void rd(char s[],int&n)
	{
		s[++n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();
		n--;
	}
}
using namespace Fast_IO;
inline void get(int&p){lc[++tot]=lc[p];rc[tot]=lc[p];nxt[tot]=nxt[p],s[tot]=s[p],lz[tot]=lz[p];p=tot;}
inline void pushson(int&p,int w,int le){get(p);s[p]=w*le%mod,lz[p]=w;}
inline void pushdown(int p,int l,int r){if(lz[p]) pushson(ls,lz[p],mid-l+1),pushson(rs,lz[p],r-mid),lz[p]=0;}
inline void modify(int&p,int l,int r,int x,int w,int f)
{
	get(p);if(r<x) return pushson(p,w,r-l+1);
	if(l==r) return nxt[p]=f,pushson(p,w,1);
	pushdown(p,l,r);modify(ls,l,mid,x,w,f);
	if(x>mid) modify(rs,mid+1,r,x,w,f);
	s[p]=(s[ls]+s[rs])%mod;
}
inline void query(int&p,int l,int r,int x,int&ans,int&w)
{
	if(r<x) return ans=(ans+s[p])%mod,void();
	if(l==r) return ans=(ans+s[p])%mod,w=nxt[p],void();
	pushdown(p,l,r);query(ls,l,mid,x,ans,w);
	if(x>mid) query(rs,mid+1,r,x,ans,w);
}
inline void dfs(int u,int d,int f)
{
	int x=w[u]/V,y=w[u]%V,nxt=0;g[d]=g[d-1]+y;
	if(d==1) ans[u]=calc(y-1);
	else
	{
		ans[u]=(ans[u]+calc(min(mx[d][x],y)))%mod;query(rt[d][x],1,V,y,ans[u],nxt);
		if(!nxt&&f/V==x&&g[1]<y) nxt=1,ans[u]=(ans[u]+g[1]*max(0ll,y-mx[d][x]))%mod;
	}mx[d][x]=max(mx[d][x],y);modify(rt[d][x],1,V,y,g[d-1],d);
	for(auto v:e[u])
	{
		memcpy(mx[d+1],mx[nxt+1],sizeof(mx[d+1]));
		memcpy(rt[d+1],rt[nxt+1],sizeof(rt[d+1]));
		ans[v]=ans[u];dfs(v,d+1,f);
	}
}
inline void solve()
{
	m=read();for(int i=1,op,x;i<=m;i++)
	{
		op=read(),x=read();
		if(op==1)
		{
			w[++n]=(getchar()-'a')*V+x;
			a[i]=n,e[a[i-1]].emplace_back(a[i]);
		}else a[i]=a[x];
	}for(int i:e[0])
	{
		tot=0;memset(rt[1],0,sizeof(rt[1]));
		memset(mx[1],0,sizeof(mx[1]));dfs(i,1,w[i]);
	}for(int i=1;i<=m;i++) print(ans[a[i]]),put('\n');
}
signed main()
{
	int T=1;while(T--) solve();
	genshin:;flush();return 0;
}
```

---

