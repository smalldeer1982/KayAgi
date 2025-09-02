# 「HMOI R1」不知道是啥的垃圾题

## 题目背景

由于这是崩坏 3 round，所以这里应该有一个关于崩坏三的背景。然而 fz 不玩崩坏 3，而且他实在是太屑了，所以这题就变成了一道裸题。

## 题目描述

要求维护一个可重集，支持三种操作：
1. 插入一个自然数对；
1. 删除一个自然数对，保证这个数对之前在集合中；
1. 给定一个自然数对 $(x,y)$，问集合中有多少个数对 $(a,b)$ 满足 $x\operatorname{xor}a>y\operatorname{xor}b$，其中 $\operatorname{xor}$ 表示按位异或运算。

本题中所有“数对”均指有序数对。

## 说明/提示

对于样例，第一次查询时集合里没有任何数对，所以答案为 $0$。

第二次查询时，集合为 $\{(3,2),(4,5)\}$，$6\operatorname{xor}3=5>0=2\operatorname{xor}2$，$6\operatorname{xor}4=2<7=2\operatorname{xor}5$，故满足条件的数对只有 $(3,2)$ 一个，答案为 $1$。

第三次询问时，集合为 $\{(4,5)\}$，没有满足条件的数对，答案为 $0$。

------------
对于所有数据：
- $0 \le M \le 2 \times 10^5$；
- $0 \le x, y \le 10^{18}$。

--------

**本题采用捆绑测试。**

| No.  | Constraints                 | Score |
| ---- | --------------------------- | ----- |
| $1$  | $M \le 2000$ | $10$  |
| $2$  | $x, y < 8$          | $20$  |
| $3$  | $x, y \le M$          | $30$  |
| $4$  | No further constraints      | $40$  |

-------

- Idea: FZzzz
- Solution: FZzzz
- Code: FZzzz
- Data: FZzzz

## 样例 #1

### 输入

```
6
3 1 2
1 3 2
1 4 5
3 6 2
2 3 2
3 6 2
```

### 输出

```
0
1
0
```

# 题解

## 作者：Miko35 (赞：20)

验题人来水一水题解。

异或，比大小，很容易想到 Trie 树。但是这题插入的是二元组，很难用普通的 01trie 进行维护。

既然是二元组，有一个初步的想法是，将 Trie 开成四叉的，其中令 $ch_{x,i,j}(i,j \in \{ 0,1 \})$ 表示：节点 $x$ 内的二元组 $(x,y)$ 中，$x$ 二进制下一位为 $i$，$y$ 二进制下一位为 $j$ 的二元组集合。也就是说，插入的向量的第 $i$ 位是 $(x,y)$ 取第 $i$ 位形成的二元组。

比如从高到低插入插入二元组 $(1,3)$：

![](https://cdn.luogu.com.cn/upload/image_hosting/5y4yj3up.png)

这样就可以像 01trie 一样实现异或比大小，也就是：将 $x \operatorname{xor} a=1,y \operatorname{xor} b=0$ 的节点计入答案，然后分别递归 $x \operatorname{xor} a=y \operatorname{xor} b=0/1$ 的点。

显然这样不是很对，因为每一层要递归两个节点，一次操作总共涉及的节点数到了 $O(M)$ 级别。

观察可知，一个点能被递归下去，当且仅当在这一位 $x \operatorname{xor} a=y \operatorname{xor} b$，而这个可以写成 $x \operatorname{xor} y=a \operatorname{xor} b$，左边只跟 $x,y$ 有关。这样插入时只需要保留两个儿子：下一位 $x \operatorname{xor} y=1$ 和 $=0$ 的，查询时只需要根据 $a \operatorname{xor} b$ 的取值决定往哪边走即可。

依然要在每个节点处记录下一位 $(x,y)=(0/1,0/1)$ 的二元组个数，这样才可以在递归时统计答案。

良心题，代码真心不长。

```cpp
#include<bits/stdc++.h>
#define g(a) ((a)>>d&1)
long long x,y;
int m,o,c,S[1<<23][2][2],r,h[1<<23][2];
void s(int& r,int d){
	if(~d)S[r?r:r=++c][g(x)][g(y)]+=3-o*2,s(h[r][g(x^y)],d-1);
}
int q(int r,int d){
	return r&&~d?S[r][!g(x)][g(y)]+q(h[r][g(x^y)],d-1):0;
}
int main(){
	std::cin>>m;
	while(m--)std::cin>>o>>x>>y,o^3?s(r,60):void(printf("%d\n",q(r,60)));
}
```





---

## 作者：Masterwei (赞：4)

模拟赛弱化版，赛时场切了，来写篇题解。

$x\oplus a>y\oplus b$，考虑什么时候 $x\oplus a$ 会大于 $y\oplus b$，转成二进制后就是一段相同的前缀，然后遇到一位不同的。

设这两个数相同的前缀长度为 $w$，那么考虑枚举 $w$，那么我们可以发现 $x\oplus y$ 和 $a\oplus b$ 的前 $w$ 位是相同的，那么我们就可以用 trie 树把这东西存起来，询问的时候直接在 trie 树上跑即可。


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
  ll x=0;bool f=0;char ch=getchar();
  while(ch<'0'||ch>'9')f^=(ch=='-'),ch=getchar();
  while('0'<=ch&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
  return f?-x:x;
}
bool st;
const int Maxn=2e5+5,V=59;
int opp,n;
ll ans;
ll a[Maxn],b[Maxn];
int root,cnt;
struct trie{
	int ls,rs,val[2][2];
}t[Maxn*61];
void insert(int&x,ll a,ll b,int w,int p){
	if(!x)x=++cnt;
	if(w<0)return;t[x].val[(a>>w)&1][(b>>w)&1]+=p;
	if(((a>>w)&1)==((b>>w)&1))insert(t[x].ls,a,b,w-1,p);
	else insert(t[x].rs,a,b,w-1,p);
}
int query(int x,ll a,ll b,int w){
	if(w<0)return 0;
	if(((a>>w)&1)==((b>>w)&1))return t[x].val[(a>>w)&1^1][(b>>w)&1]+query(t[x].ls,a,b,w-1);
	return t[x].val[(a>>w)&1^1][(b>>w)&1]+query(t[x].rs,a,b,w-1);
}
bool en;
signed main(){cerr<<(&st-&en)/1024.0/1024.0<<'\n';
//	freopen("poison.in","r",stdin);
//	freopen("poison.out","w",stdout);
	n=read();
	while(n--){
		int op=read();ll a=read(),b=read();
		if(op==1)insert(root,a,b,V,1);
		if(op==2)insert(root,a,b,V,-1);
		if(op==3)printf("%d\n",query(root,a,b,V));
	}
	return 0;
}

```

---

## 作者：Ivan422 (赞：2)

今天随机跳题跳到的。

我们发现，这个东西可以通过**维护一个两位的字典树**得到。

但是显然的，我们并不能通过开一个四叉的字典树得到。

容易发现不这么做的原因是每一次**要往下找两个节点**，在题目的数据范围内无法被接受。

又因为我们在这个题中要求异或，考虑使用 01-Trie。

因为 $x\otimes a=y\otimes b$，可得 $x\otimes y=a\otimes b$，就可以通过异或判定方向。

我们在每一次插入时异或的每一位，然后再通过对二元组的统计使得异或相同但是位不同的二元组得到不同的统计。

接下来查询就跟正常的没有什么区别了，我们只需要把 $x$ 的一位二进制取反，就能对异或产生贡献，即可统计。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+10;
ll x,y;
int opt,m,cnt,v[N<<6][4],nxt[N<<6][4];
void insert(ll x,ll y,int val){
    int p=0;
    for(int i=60;i>=0;i--){
        int pa=(x>>i)&1,pb=(y>>i)&1,pc=((x^y)>>i)&1;
        if(!nxt[p][pc])nxt[p][pc]=++cnt;
        v[p][pa+pb*2]+=val;p=nxt[p][pc];
    }
}
int query(ll x,ll y){
    int p=0,ans=0;
    for(int i=60;i>=0;i--){
        int pa=(x>>i)&1,pb=(y>>i)&1,pc=((x^y)>>i)&1;
        ans+=v[p][(!pa)+pb*2];
        if(!nxt[p][pc])break;
        p=nxt[p][pc];
    } 
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    cin>>m;
    while(m--){
        cin>>opt>>x>>y;
        if(opt==1)insert(x,y,1);
        if(opt==2)insert(x,y,-1);
        if(opt==3)cout<<query(x,y)<<"\n";
    }
    return 0;
}
```

---

## 作者：OrinLoong (赞：1)

验题人的学弟来水一水题解。  
验题人的题解写的已经解释得很清楚了。我来水题解的理由是[他的代码](https://www.luogu.com.cn/article/guybsapb)压行过于厉害，我不妨留一份更清晰的代码给后人。然而因为只有代码被打回了。。。所以讲一下思路。  
看到异或显然考虑 01Trie，发现这道题插入删除询问全部都是数对，因此我们要把整个数对都压入 01Trie 中。$(a,b)$ 的取值在每一位都有四种，因此我们的 `cnt` 数组第二维大小为四。但是我们的 `nxt` 数组第二维绝对不能是四，否则询问的时候就要递归下去两个儿子，造成运算量指数级增长，这是绝对不可行的。考虑到询问时我们要继续递归的情形当且仅当 $x\oplus a=y\oplus b$，不好归纳，但是我们只要把它移项为 $x\oplus y=a\oplus b$，问题就迎刃而解。插入、删除时我们根据 $a\oplus b$ 在这一位上的取值决定递归方向就行。其它的都是 01Trie 基本套路了，具体实现看代码吧。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long lolo;
const int MaxN=2e5+5;
int M,Opt;lolo X,Y;
struct BinaryTrie{
    int ncnt,nxt[MaxN<<6][2],cnt[MaxN<<6][4];
    void init(){ncnt=1;memset(nxt,0,sizeof(nxt));}
    int isbit(lolo x,int p){return (x>>p)&1;}
    void inse(lolo x,lolo y){
        int p=1;
        for(int i = 59;i >= 0;i--){
            int id1=isbit(x^y,i),id2=isbit(x,i)+(isbit(y,i)<<1);
            if(!nxt[p][id1])nxt[p][id1]=++ncnt;
            cnt[p][id2]++,p=nxt[p][id1];            
        }
    }
    void dele(lolo x,lolo y){
        int p=1;
        for(int i = 59;i >= 0;i--){
            int id1=isbit(x^y,i),id2=isbit(x,i)+(isbit(y,i)<<1);
            cnt[p][id2]--,p=nxt[p][id1];
        }
    }
    int srch(lolo x,lolo y){
        int p=1,ans=0;
        for(int i = 59;i >= 0;i--){
            if(!p)break;
            int id1=isbit(x^y,i),id2=(!isbit(x,i))+(isbit(y,i)<<1);
            ans+=cnt[p][id2],p=nxt[p][id1];            
        }
        return ans;
    }
}BnTre;
int main(){
    scanf("%d",&M);BnTre.init();
    for(int i = 1;i <= M;i++){
        scanf("%d%lld%lld",&Opt,&X,&Y);
        if(Opt==1)BnTre.inse(X,Y);
        if(Opt==2)BnTre.dele(X,Y);
        if(Opt==3)printf("%d\n",BnTre.srch(X,Y));
    }
    return 0;
}
```

---

## 作者：Tomle (赞：0)

我们考虑比大小的本质，在二进制下，两数的大小是由第一个不同位决定的。

考虑 $x\operatorname{xor}a$ 和 $y\operatorname{xor}b$ 前 $k$ 位相等，$a_1,b_1,x_1,y_1$ 分别是 $a,b,x,y$ 前 $k$ 位，$a_2,b_2,x_2,y_2$ 分别是 $a,b,x,y$ 第 $(k+1)$ 位。

合法的 $(a,b)$ 满足：

- $x_1\operatorname{xor}a_1=y_1\operatorname{xor}b_1$ 即 $a_1\operatorname{xor}b_1=x_1\operatorname{xor}y_1$。
- $x_2\operatorname{xor}a_2>y_2\operatorname{xor}b_2$。

这启示我们在 trie 上记录 $a\operatorname{xor}b$，查询时顺着 $x\operatorname{xor}y$ 往下走，找到第一个不同位。

注意我们的 trie 的路径虽然是 $a\operatorname{xor}b$，但也要记录一下 $a,b$ 的每一位，便于在第一不同位进行比较。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;

typedef long long ll;

int q, op, tr[N * 70][2], ct[N * 70][2], tot;
ll x, y;

template <class T> inline void rd(T &a, int ch = 0) {
    while (ch = getchar(), ch < 48 || ch > 57);
    for (a = 0; ch >= 48 && ch <= 57; ch = getchar()) a = (a << 3) + (a << 1) + (ch ^ 48);
}
void wrt(int x) {
    if (x > 9) wrt(x / 10);
    putchar(x % 10 ^ 48);
}
void ins(ll pt, ll x, ll y, int k) {
    int p = 0;
    for (int i = 62; ~i; i--) {
        if (!tr[p][pt >> i & 1]) tr[p][pt >> i & 1] = ++tot;
        p = tr[p][pt >> i & 1];
        ct[p][x >> i & 1] += k;
    }
}
int qry(ll pt, ll x, ll y) {
    int R = 0, p = 0;
    for (int i = 62; ~i; i--) {
        int z = pt >> i & 1;
        R += ct[tr[p][z ^ 1]][x >> i & 1 ^ 1];
        if (tr[p][z]) p = tr[p][z];
        else break;
    }
    return R;
}
int main() {
    rd(q);
    while (q--) {
        rd(op), rd(x), rd(y);
        if (op == 1) ins(x ^ y, x, y, 1);
        else if (op == 2) ins(x ^ y, x, y, -1);
        else wrt(qry(x ^ y, x, y)), putchar(10);
    }
}
```

---

