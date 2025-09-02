# Jewel Magic

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=229&page=show_problem&problem=3147

[PDF](https://uva.onlinejudge.org/external/119/p11996.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11996/2bab589816720983ab635f9484728b78d4993b0f.png)

## 样例 #1

### 输入

```
12 9
000100001100
1 0 1
4 2 6
3 7 10
4 1 7
2 9
4 3 11
4 1 9
4 1 7
4 2 3```

### 输出

```
3
6
2
0
3
2```

# 题解

## 作者：hl666 (赞：3)

这题貌似全网都是**Splay**的题解，其实**FHQ_Treap**当然也是可以做的，这里为暴力非旋Treap党上一份代码。

题目大意就是先给你一个字符串，然后让你维护一些操作：

1. $p\ c$：在第$p$个位置后插入字符$c$
2. $p$ ：删除第$p$个字符
3. $p1\ p2$：**翻转**第$p1$个字符到第$p2$个字符
4. $p1\ p2$：询问从第$p1$个字符开始的后缀和从第$p2$个字符开始的后缀的**LCP**

看到LCP，第一眼想到什么？**SA,SAM**？

但是这两个算法都有一个致命伤——不支持修改，况且这里还有鬼畜的**翻转**操作。

但是如果只看$1,2,3$操作我们发现其实就是一个序列维护，我们可以用**平衡树**来维护。

所以大致思路有了，但是有什么东西可以维护序列的值还支持快速修改呢？

很简单，就是**Hash**！而且Hash求LCP在静态问题不想写SA,SAM时（一般都是写挂了吧）也常常用来得到比暴力优秀的$O(n\log n)$复杂度（一般出题人不卡的话都可以过）

所以我们对于平衡树的每一个节点维护左右儿子的$size$和正（从前往后）的$hash$值以及反（**从后往前**）的$hash$值，然后```pushup```的时候合并一下即可。

至于为什么要维护反的，这样就可以$O(1)$翻转了啊！

询问的时候**二分**LCP的长度，用Hash值判断即可。复杂度$O(n\log^2 n)$

CODE

```cpp
#include<cstdio>
#include<cctype>
#define RI register int
using namespace std;
typedef unsigned long long ull;
const int N=400005;
const ull seed=233;
int n,m,opt,x,y; ull pw[N];
class FileInputOutput
{
    private:
        #define S 1<<21
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
        #define pc(ch) (Ftop<S?Fout[Ftop++]=ch:(fwrite(Fout,1,S,stdout),Fout[(Ftop=0)++]=ch))
        char Fin[S],Fout[S],*A,*B; int Ftop,pt[15];
    public:
        inline void gd(int &x)
        {
            char ch; while (!isdigit(ch=tc())); x=ch&15;
        }
        inline bool read(int &x)
        {
            x=0; char ch; while (!isdigit(ch=tc())) if (ch==EOF) return 0;
            while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc())); return 1;
        }
        inline void write(int x)
        {
            if (!x) return (void)(pc('0'),pc('\n')); RI ptop=0;
            while (x) pt[++ptop]=x%10,x/=10; while (ptop) pc(pt[ptop--]+48); pc('\n');
        }
        inline void Fend(void)
        {
            fwrite(Fout,1,Ftop,stdout);
        }
        #undef S
        #undef tc
        #undef pc
}F;
class FHQ_Treap
{
    private:
        struct treap
        {
            int ch[2],size,rev,dat,val; ull h,rh;
            treap(int Lc=0,int Rc=0,int Size=0,int Val=0,int Dat=0)
            {
                ch[0]=Lc; ch[1]=Rc; size=Size; h=rh=val=Val; dat=Dat;
            }
        }node[N]; int tot,seed;
        #define lc(x) node[x].ch[0]
        #define rc(x) node[x].ch[1]
    public:
        int rt;
        inline int rand(void)
        {
            return seed=(int)seed*482711LL%2147483647;
        }
        inline int create(int val)
        {
            node[++tot]=treap(0,0,1,val,rand()); return tot;
        }
        inline void swap(int &x,int &y)
        {
            int t=x; x=y; y=t;
        }
        inline void swap(ull &x,ull &y)
        {
            ull t=x; x=y; y=t;
        }
        inline void pushup(int now)
        {
            treap lson=node[lc(now)],rson=node[rc(now)]; node[now].size=lson.size+rson.size+1;
            node[now].h=1ull*rson.h*pw[lson.size+1]+1ull*node[now].val*pw[lson.size]+lson.h;
            node[now].rh=1ull*lson.rh*pw[rson.size+1]+1ull*node[now].val*pw[rson.size]+rson.rh;
        }
        inline void pushdown(int now)
        {
            if (!now||!node[now].rev) return; if (lc(now)) flip(lc(now)); if (rc(now)) flip(rc(now)); node[now].rev=0;
        }
        inline void flip(int now)
        {
            if (!now) return; node[now].rev^=1; swap(node[now].h,node[now].rh); swap(lc(now),rc(now));
        }
        inline void merge(int &now,int x,int y)
        {
            if (!x||!y) return (void)(now=x+y); if (node[x].dat>node[y].dat)
            pushdown(x),now=x,merge(rc(now),rc(x),y),pushup(x); else
            pushdown(y),now=y,merge(lc(now),x,lc(y)),pushup(y);
        }
        inline void split(int now,int &x,int &y,int rk)
        {
            if (!now) return (void)(x=y=0); pushdown(now); if (node[lc(now)].size<rk)
            x=now,split(rc(now),rc(x),y,rk-node[lc(now)].size-1); else
            y=now,split(lc(now),x,lc(y),rk); pushup(now);
        }
    public:
        inline void clear(void)
        {
            rt=tot=0; seed=233;
        }
        inline void insert(int rk,int val)
        {
            int x=0,y=0,z=create(val);
            split(rt,x,y,rk-1);
            merge(x,x,z); merge(rt,x,y);
        }
        inline void remove(int rk)
        {
            int x=0,y=0,z=0; split(rt,x,y,rk-1);
            split(y,y,z,1); merge(rt,x,z);
        }
        inline void reverse(int l,int r)
        {
            int x=0,y=0,z=0; split(rt,x,y,l-1); split(y,y,z,r-l+1);
            flip(y); merge(y,y,z); merge(rt,x,y);
        }
        inline ull gethash(int x)
        {
            return node[x].rev?node[x].rh:node[x].h;
        }
        inline int getsize(int x)
        {
            return node[x].size;
        }
        #undef lc
        #undef rc
}T;
inline bool check(int a,int b,int com)
{
    int x=0,y=0,z=0; ull h1,h2;
    T.split(T.rt,x,y,a-1); if (T.getsize(y)<com) return T.merge(T.rt,x,y),0;
    T.split(y,y,z,com);	h1=T.gethash(y); T.merge(y,y,z); T.merge(T.rt,x,y);
    T.split(T.rt,x,y,b-1); if (T.getsize(y)<com) return T.merge(T.rt,x,y),0;
    T.split(y,y,z,com);	h2=T.gethash(y); T.merge(y,y,z); T.merge(T.rt,x,y);
    return h1==h2;
}
inline int LCP(int x,int y)
{
    int l=1,r=T.getsize(T.rt)-1,res=0,mid;
    if (!check(x,y,1)) return 0; while (l<=r)
    if (check(x,y,mid=l+r>>1)) res=mid,l=mid+1;
    else r=mid-1; return res;
}
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    RI i; for (pw[0]=i=1;i<=400000;++i) pw[i]=pw[i-1]*seed;
    while (F.read(n))
    {
        for (T.clear(),F.read(m),i=1;i<=n;++i) F.gd(x),T.insert(i,x);
        for (i=1;i<=m;++i)
        {
            F.read(opt); F.read(x); switch (opt)
            {
                case 1:
                    F.read(y); T.insert(x+1,y); break;
                case 2:
                    T.remove(x); break;
                case 3:
                    F.read(y); T.reverse(x,y); break;
                case 4:
                    F.read(y); F.write(LCP(x,y)); break;
            }
        }
    }
    return F.Fend(),0;
}
```



---

## 作者：autoint (赞：2)

# 题意
给出一个长度为$n$的01串，有$m$个操作。操作有以下几种： 
1. p c在第p个字符后插入c

2. p    删除第p个字符

3. p1 p2 翻转p1到p2的字符串

4. p1 p2 求从p1开始和p2开始的两个后缀的LCP

# 分析
这是一个和lcp有关的问题。经过思考，我们发现后缀数组很难派上用场，因为修改操作太乱，很难维护后缀数组。但lcp可以用哈希法快速求出。具体如下：
1. 为每个后缀计算一个哈希值，满足递推式$H(i)=H(i+1)x+s[i]$(其中$0\leq i<n,H(n)=0$)
2. 一般的，$H(i)=s[n-1]x^{n-i-i}+s[n-2]x^{n-2-i}+\dots+s[i+1]x+s[i]$
3. 那么对于一段长度为$L$的字符串$s[i]\thicksim s[i+L-1]$，定义它的哈希值$Hash(i,L)=H(i)-H(i+L)x^L$，展开后$Hash(i,L)=s[i+L-1]x^{L-1}+s[i+L-2]x^{L-2}+\dots+s[i+1]x+s[i]$
4. 上式可作为这一子串的哈希值，对这题而言已经是很优的做法了，因为用 unsigned long long 来存，使其自然溢出，可保留有效位数$18$位，此题共$1e6 \times 1e6$个子串，重复的概率为$1e6 \times 1e6 \div 1e18=1e-6=0.0001\%$，而这题不是 Hash Killer 的数据，可以放心用
5. 当然在这题里面我们肯定不能这样算哈希值，不然每次操作就$O(n)$了。实际上我们只需对 Splay 的 pushup() 稍动手脚，就可以完成Hash值的统计。代码如下：
```cpp
void pushup()
{
	size=son[0]->size+1+son[1]->size;
	h1=son[0]->h1+(c-'0')*powX[son[0]->size]+son[1]->h1*powX[son[0]->size+1]; // 正向哈希值
	h2=son[1]->h2+(c-'0')*powX[son[1]->size]+son[0]->h2*powX[son[1]->size+1]; // 反向哈希值
}
```
这实际上就是把哈希值的统计化用了一下。对两个 string 类型的$S_1,S_2$，根据刚才定义的哈希式，他们的“和”$S_{sum}$的哈希值应该等于$Hash(S_1)+Hash(S_2)x^{S_1.size()}$。有了这个公式我们就可以自底向上统计答案。至于为什么要反向哈希值？因为要支持操作3。如果没有翻转操作要重新统计子树答案，变成了$O(n)$复杂度，这不是我们所期望的。

# 具体操作
1. 把p字符前一个旋至根，把p旋至根的右子树的根，然后把c加到p的左儿子，再向上统计。
2.  删除把p字符前一个旋至根，把p后一个字符旋至根的右子树的根，然后就可以删除p，再向上统计。
3. 翻转就跟普通的splay一样。
4. 二分lcp，judge就分别把p1和p2后len个数调至同一子树中统计答案。

# 代码
Splay的代码略。
```cpp
void rever(Splay_node*&r,int p1,int p2) // 操作3
{
	splay(r,p1);
	splay(r->son[1],p2-p1+2);
	r->son[1]->son[0]->rever();
	r->son[1]->pushup();
	r->pushup();
}

void insert(Splay_node*&r,int p,char c) // 操作1
{
	Splay_node*ad=new Splay_node();
	ad->son[0]=ad->son[1]=null;
	ad->c=c;
	ad->pushup();
	splay(r,p+1);
	splay(r->son[1],1);
	r->son[1]->son[0]=ad;
	r->son[1]->pushup();
	r->pushup();
}

void del(Splay_node*&r,int p) // 操作2
{
	splay(r,p);
	splay(r->son[1],2);
	delete(r->son[1]->son[0]);
	r->son[1]->son[0]=null;
	r->son[1]->pushup();
	r->pushup();
}

bool judge(Splay_node*&r,int p1,int p2,int len)
{
	if(len==0) return 1;
	int a1,a2;
	splay(r,p1);
	splay(r->son[1],len+1);
	a1=r->son[1]->son[0]->h1;
	splay(r,p2);
	splay(r->son[1],len+1);
	a2=r->son[1]->son[0]->h1;
	return a1==a2;
}

int query(Splay_node*&r,int p1,int p2) // 操作4
{
	int L=0,R=(n-p2+1); // 二分子串长度，注意长度限制为最短的那个
	while(R>L)
	{
		int M=(L+R)>>1;
		if(judge(r,p1,p2,M))
			L=M+1;
		else
			R=M;
	}
	if(!judge(r,p1,p2,L))
		--L;
	return L;
}

int main()
{
//  freopen("UVa11996.in","r",stdin);
//  freopen("UVa11996.out","w",stdout);
	powX[0]=1;
	for(int i=1;i<maxn;++i)
	{
		powX[i]=powX[i-1]*X;
	}
	while(~scanf("%d%d",&n,&m))
	{
		scanf("%s",str+1);
		str[0]=str[n+1]='0'; 
		removetree(root); 
		root=build(0,n+1); 
		for(int i=1;i<=m;++i)
		{
			int q;
			read(q);
			if(q==1)
			{
				int p,c;
				read(p);read(c);
				insert(root,p,c+'0');
				++n; ///edit 1
			}
			else if(q==2)
			{
				int p;
				read(p);
				del(root,p);
				--n; // edit 1
			}
			else if(q==3)
			{
				int p1,p2;
				read(p1);read(p2);
				rever(root,p1,p2);
			}
			else if(q==4)
			{
				int p1,p2;
				read(p1);read(p2);
				printf("%d\n",query(root,p1,p2));
			}
		}
	}
//  fclose(stdin);
//  fclose(stdout);
    return 0;
}
```
# Hint
$Maxnode=Maxn+Maxm$

这是对$powX[\dots]$(power of x)的大小要求，不仅要考虑初始就有的$n$个节点，还要考虑每次操作都可能插入的节点，最坏情况会插$m$个，而我们不能保证树是平衡的，所以$powX$套开这么大(400000)。

---

## 作者：JimmyLee (赞：1)

# 题意

给你一个 01 串，要求完成以下操作：

- 单点插入。

- 单点删除。

- 区间翻转。

- 查询两点开始的 LCP。

# 分析

先看查询操作，如何得到 LCP 的长度?

我们可以考虑二分长度 $l$，然后用哈希检验区间 $[p1, p1+l-1]$ 是否等于区间 $[p2, p2+l-1]$。

平衡树维护哈希即可。

---

发现还有一个翻转操作，这时又应当如何操作？

考虑多存一个哈希记录翻转后的哈希值。

翻转操作时交换正反哈希。

# Code

发一份指针版 FHQ Treap。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define lx 114
typedef uint64_t hash_t;
#define maxn 400005

hash_t lev[maxn];

struct Treap
{
    #define siz(x) (x?x->siz:0)
    #define hsh(x) (x?x->hsh:0)
    #define rhsh(x) (x?x->rhsh:0)

    mt19937 rnd;

    Treap(uint32_t s=114) { rnd.seed(s); }

    struct node
    {
        node *lc, *rc;
        uint32_t siz, id;
        uint8_t ch;
        hash_t hsh, rhsh;
        uint8_t rev;
        node(uint8_t c, uint32_t i)
        {
            id=i;
            lc=rc=nullptr;
            siz=1, hsh=rhsh=ch=c;
            rev=0;
        }

        node *push_up()
        {
            siz=siz(lc)+siz(rc)+1;
            hsh=lev[siz(rc)+1]*hsh(lc)+lev[siz(rc)]*ch+hsh(rc);
            rhsh=lev[siz(lc)+1]*rhsh(rc)+lev[siz(lc)]*ch+rhsh(lc);
            return this;
        }

        void reverse()
        {
            swap(hsh, rhsh);
            swap(lc, rc);
            rev^=1;
        }

        void push_down()
        {
            if(!rev) return;
            if(lc) lc->reverse();
            if(rc) rc->reverse();
            rev^=1;
        }
    };

    node *rt;

    node *new_node(uint8_t c) { return new node(c, rnd()); }

    void split(node *x, uint32_t k, node *&l, node *&r)
    {
        if(!x) return l=r=0, void();
        x->push_down();
        if(siz(x->lc)<k) l=x, split(x->rc, k-siz(x->lc)-1, x->rc, r);
        else             r=x, split(x->lc, k, l, x->lc);
        x->push_up();
    }

    node *merge(node *x, node *y)
    {
        if(!x||!y) return x?x:y;
        if(x->id<y->id)
        {
            x->push_down();
            x->rc=merge(x->rc, y);
            return x->push_up();
        }
        else
        {
            y->push_down();
            y->lc=merge(x, y->lc);
            return y->push_up();
        }
    }

    void push_back(uint8_t c) { rt=merge(rt, new_node(c)); }

    void insert(int p, uint8_t c)
    {
        node *a, *b;
        split(rt, p, a, b);
        rt=merge(a, merge(new_node(c), b));
    }

    void erase(int p)
    {
        node *a, *b, *c;
        split(rt, p-1, a, b);
        split(b, 1, b, c);
        rt=merge(a, c);
    }

    void reverse(int l, int r)
    {
        node *a, *b, *c;
        split(rt, l-1, a, b);
        split(b, r-l+1, b, c);
        b->reverse();
        rt=merge(merge(a, b), c);
    }

    hash_t query(int l, int r)
    {
        node *a, *b, *c;
        split(rt, l-1, a, b);
        split(b, r-l+1, b, c);
        hash_t ret=b->hsh;
        rt=merge(merge(a, b), c);
        return ret;
    }
}tr(114514);

string s;

bool chk(int p1, int p2, int l, int mxlen)
{
    if(p1+l-1>mxlen||p2+l-1>mxlen) return 0;
    hash_t h1=tr.query(p1, p1+l-1);
    hash_t h2=tr.query(p2, p2+l-1);
    return h1==h2;
}

int LCP(int p1, int p2)
{
    if(!tr.rt) return 0;
    int len=tr.rt->siz;
    int ret=0;
    for(int i=1<<20;i;i>>=1)
        if(chk(p1, p2, ret+i, len)) ret+=i;
    return ret;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    lev[0]=1;
    for(int i=1;i<maxn;i++) lev[i]=lev[i-1]*lx;
    int m;
    cin>>m>>m;
    cin>>s;
    for(auto c:s) tr.push_back(c);
    while(m--)
    {
        int op, p, x;
        cin>>op>>p;
        if(op==1) cin>>x, tr.insert(p, x^48);
        if(op==2) tr.erase(p);
        if(op==3) cin>>x, tr.reverse(p, x);
        if(op==4) cin>>x, cout<<LCP(p, x)<<'\n';
    }
}

```

---

## 作者：Y_QWQ_Y (赞：0)

显然的平衡树，但是我写了 2 天，终于过了，所以发篇题解纪念一下。

同时，三倍经验：[P4036](https://www.luogu.com.cn/problem/P4036)，[SP3109](https://www.luogu.com.cn/problem/SP3109)。

### 简要题意
对于一个 01 串，有 4 种操作。

- `1 p c`：在第 $p$ 个字符后面插入一个字符 $c$；

- `2 p`：删除第 $p$ 个字符；

- `3 l r`：把区间 $[l,r]$ 内的字符翻转；

- `4 l r`：查询从 $l$ 开始和从 $r$ 开始的字符串的最长公共后缀长度。

### 问题解析
一开始以为是字符算法题，但是有修改和翻转，很容易想到用平衡树维护。

因为有翻转操作，所以按照编号分裂。但是怎么做呢？字符串哈希可以解决。我们可以令 $w1$ 表示正着的哈希值，$w2$ 表示倒着的哈希值，当区间翻转时，交换两值。接下来，我们需要解决查询：我们可以二分的长度，用哈希值去检查是否相同即可。

剩下的都是平衡树板子了。

### 代码部分
```cpp
#include <bits/stdc++.h>
#define ull unsigned int
using namespace std;
const int N = 4e5 + 5, bas = 3;
int n, m, cnt, rt, l, r, a, b;
char op, c;
string s;
ull h[N];
struct FHQ_Treap{int l, r, siz, k, v, tag;ull w1, w2;}t[N << 1];
int New (int vv)
{
	t[++ cnt].siz = 1;
    t[cnt].v = t[cnt].w1 = t[cnt].w2 = vv;
	t[cnt].k = rand ();
	return cnt;
}
void push_up (int x)
{
    if (! x)return;
	t[x].siz = t[t[x].l].siz + t[t[x].r].siz + 1;
	t[x].w1 = t[t[x].l].w1 * h[t[t[x].r].siz + 1] + t[t[x].r].w1 + t[x].v * h[t[t[x].r].siz];
	t[x].w2 = t[t[x].r].w2 * h[t[t[x].l].siz + 1] + t[t[x].l].w2 + t[x].v * h[t[t[x].l].siz];
}
void Swap (int &a, int &b){a ^= b ^= a ^= b;}
void Swap (ull &a, ull &b){a ^= b ^= a ^= b;}
void rev (int x)
{
    Swap (t[x].l, t[x].r);
    Swap (t[x].w1, t[x].w2);
    t[x].tag ^= 1;
}
void push_down (int x)
{
	if (t[x].tag && x)
	{
		rev (t[x].l);
        rev (t[x].r);
        t[x].tag = 0;
	}
}
void split (int pos, int x, int &l, int &r)
{
	if (! pos)return l = r = 0, void ();
	int tt = t[t[pos].l].siz + 1;
	push_down (pos);
	if (tt <= x)
	{
		l = pos;
		split (t[l].r, x - tt, t[l].r, r);
        push_up (l);
	}
	else
	{
		r = pos;
		split (t[r].l, x, l, t[r].l);
        push_up (r);
	}
}
int merge (int l, int r)
{
	if (! l || ! r)return l | r;
	int pos;
	if (t[l].k < t[r].k)push_down (l), t[pos = l].r = merge (t[l].r, r);
	else push_down (r), t[pos = r].l = merge (l, t[r].l);
	push_up (pos);
	return pos;
}
ull query (int L, int R)
{
	int l1, r1;
	split (rt, R, l, r);
	split (l, L - 1, l1, r1);
	ull d = t[r1].w2;
	rt = merge (merge (l1, r1), r);
	return d;
}
signed main ()
{
	ios::sync_with_stdio (0), cin.tie (0), cout.tie (0);
	srand (time (0));
    h[0] = 1;
	for (int i = 1; i < N; ++ i)h[i] = h[i - 1] * bas;
	while (cin >> n)
	{
		cnt = rt = 0;
		memset (t, 0, sizeof (t));
		cin >> m >> s;
		s = " " + s;
		for (int i = 1; i <= n; ++ i)rt = merge (rt, New (s[i] - '0'));
		while (m --)
		{
			cin >> op >> a;
			if (op == '4')
			{
				cin >> b;
				if (a > b)Swap (a, b);
				int L = 0, R = n - b + 1;
				while (L < R)
				{
					int mid = L + R + 1 >> 1;
					if (query (a, a + mid - 1) == query (b, b + mid - 1))L = mid;
					else R = mid - 1;
				}
				cout << L << '\n';
			}
			if (op == '1')
			{
				cin >> c;
				split (rt, a, l, r);
				rt = merge (merge (l, New (c - '0')), r);
				++ n;
			}
			if (op == '2')
			{
				int l1, r1;
				split (rt, a - 1, l, r);
				split (r, 1, l1, r1);
				rt = merge (l, r1);
				-- n;
			}
			if (op == '3')
			{
				cin >> b;
				if (a > b)Swap (a, b);
				int l1, r1;
				split (rt, b, l, r);
				split (l, a - 1, l1, r1);
                if (r1)rev (r1);
				rt = merge (merge (l1, r1), r);
			}
		}
	}
	return 0;
}
```

完结撒花！

---

