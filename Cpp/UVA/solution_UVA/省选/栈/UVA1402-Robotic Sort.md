# Robotic Sort

## 题目描述

通过一系列移动，将某些物品按顺序摆好。规定只能使用如下方式排序：
先找到编号最小的物品的位置P1，将区间[1,P1]反转，再找到编号第二小的物品的位置P2，将区间[2,P2]反转……

（如图）
上图是有6个物品的例子，编号最小的一个是在第4个位置。因此，最开始把前面4个物品反转，第二小的物品在最后一个位置，所以下一个操作是把2-6的物品反转，第三部操作则是把3-4的物品进行反转……
在数据中可能存在有相同的编号，如果有多个相同的编号，则按输入的原始次序操作。

# 题解

## 作者：宝硕 (赞：3)

更好的阅读体验：[https://oi.baoshuo.ren/cerc2007-sort/](https://oi.baoshuo.ren/cerc2007-sort/?utm_source=www.luogu.com.cn&utm_medium=uva1402_solution)

---

看到没有指针 FHQ Treap 的题解，于是来补一发留给后人参考。

其他题解都讲得挺清楚的，这里就不再细说思路了。考虑按照排名处理，每次找到最小值的排名 $k$，然后翻转区间 $[1, k]$，再删去这个最小值。对于每次操作 $k + i - 1$ 即为答案。

代码如下：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <limits>

using std::cin;
using std::cout;
const char endl = '\n';

const int N = 1e5 + 5;

struct node {
    node *lchild, *rchild;
    size_t size;
    unsigned key;
    int value, min;
    bool reversed;

    node()
        : lchild(nullptr),
          rchild(nullptr),
          size(0),
          key(rand()),
          value(0),
          min(std::numeric_limits<int>::max()),
          reversed(false) {}

    node(int _value)
        : lchild(nullptr),
          rchild(nullptr),
          size(1),
          key(rand()),
          value(_value),
          min(_value),
          reversed(false) {}

    ~node() {
        if (lchild != nullptr) delete lchild;
        if (rchild != nullptr) delete rchild;
    }

    inline size_t lsize() {
        return lchild == nullptr ? 0 : lchild->size;
    }

    inline size_t rsize() {
        return rchild == nullptr ? 0 : rchild->size;
    }

    inline void pushup() {
        size = lsize() + 1 + rsize();
        min = value;

        if (lchild != nullptr) {
            min = std::min(min, lchild->min);
        }

        if (rchild != nullptr) {
            min = std::min(min, rchild->min);
        }
    }

    inline void pushdown() {
        if (reversed) {
            std::swap(lchild, rchild);
            if (lchild != nullptr) lchild->reversed = !lchild->reversed;
            if (rchild != nullptr) rchild->reversed = !rchild->reversed;
            reversed = false;
        }
    }
};

int n, b[N];
std::pair<int, int> a[N];
node *root;

std::pair<node *, node *> split(node *u, int k) {
    if (u == nullptr) return std::make_pair(nullptr, nullptr);

    u->pushdown();

    if (k <= u->lsize()) {
        auto o = split(u->lchild, k);

        u->lchild = o.second;
        u->pushup();
        o.second = u;

        return o;
    }

    auto o = split(u->rchild, k - u->lsize() - 1);

    u->rchild = o.first;
    u->pushup();
    o.first = u;

    return o;
}

node *merge(node *x, node *y) {
    if (x == nullptr) return y;
    if (y == nullptr) return x;

    if (x->key < y->key) {
        x->pushdown();
        x->rchild = merge(x->rchild, y);
        x->pushup();

        return x;
    }

    y->pushdown();
    y->lchild = merge(x, y->lchild);
    y->pushup();

    return y;
}

void reverse(int k) {
    auto x = split(root, k);
    auto y = split(x.first, k - 1);
    if (y.first != nullptr) y.first->reversed = !y.first->reversed;
    delete y.second;
    root = merge(y.first, x.second);
}

int find(node *p) {
    int k = 1;

    while (p != nullptr) {
        p->pushdown();

        if (p->lchild != nullptr && p->min == p->lchild->min) {
            p = p->lchild;
        } else if (p->rchild != nullptr && p->min == p->rchild->min) {
            k += p->lsize() + 1;
            p = p->rchild;
        } else {
            return k + p->lsize();
        }
    }

    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n, n) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i].first;

            a[i].second = i;
        }

        std::sort(a + 1, a + 1 + n);

        for (int i = 1; i <= n; i++) {
            b[a[i].second] = i;
        }

        for (int i = 1; i <= n; i++) {
            root = merge(root, new node(b[i]));
        }

        for (int i = 1; i <= n; i++) {
            int k = find(root);

            reverse(k);

            cout << k + i - 1 << (i == n ? '\n' : ' ');
        }

        // Cleanup
        delete root;
        root = nullptr;
    }

    return 0;
}
```

---

## 作者：jerry119 (赞：3)

## 一道很好的Splay基础练习题

写第一份题解还是很兴奋的！

请大家不要复制我的代码提交，因为这份代码是在Bzoj上过了，但是洛谷上没过（可能是因为多组数据）……

本人一向很反感那种直接贴代码的博客，所以不想看文字的人，可以直接跳过，但是如果要看，请耐心：

其实一看就是Splay的区间翻转，但是如何找出这个区间成了一个难题！

我们希望快速找出这个区间[i,pi]，对吧？由于它需要找出第K小，但是Splay不能既按照序列下标建树，又按照序列中的值建成一个二叉排序树，所以我们考虑可能要预处理出所有Pi的位置！

但是Pi是随着区间翻转而移动的，这使得维护Pi的位置及其困难！这时候我上网看了很多份代码，但是没有看懂，我实在是太弱了，所以只能自己想……

这时候一个奇怪的念头蹦了出来，我们指针其实是可以进行映射的，所以我就考虑将原序列先建立一颗Splay，然后将其排序，得到新的结构体A，这个时候结构体A中保留了第K小的数在原序列中的位置（id），这个时候id就很有用了，我们可以用log的时间**将每一个排好序后的值与Splay上其对应的指针（或者数组编号）一一映射**，这样，不论Splay如何变化旋转，映射关系都不会改变，这样访问Pi在Splay上的节点就很容易找到了！

但是找到了Pi在Splay上的位置有什么用呢？考虑一下，**Splay的子树根节点的左子树是不是都是其子树代表的序列的根节点所在位置的左半边**（这句话一定要好好理解，不懂得可以查阅我的Csdn博客中Splay的详解，在文末有链接），这样我想我们只需要将查找到的Pi旋转到根，然后取其左子树的大小+1-1（因为左子树不包含Pi，所以要+1，但是Splay有一个前置虚拟节点，所以要-1）就是Pi现在在序列上的位置了！输出！

但是这样做是有问题的，我们进行区间翻转之后只是打了一个懒标记，但是并没有真正进行翻转，所以，在没有更新（pushdown）的情况下再次Splay旋转可能会导致标记下方错误或者无法下放标记：想一想，为什么？因为旋转会导致子树和父子关系的变化，这样就会导致原来的父亲无法进行正常的下放或者，根本下放到其他的节点上。这个问题我调试了一个晚上，最终在睡觉的时候想了出来，第二天一改，样例就过了！

那么想一想我们是如何解决这个问题的？第一种方法是利用find（）函数，在查找当前节点的时候在其路径上所有的节点全部pushdown！第二种是开一个栈空间，每一次都暴力跳到我们需要Splay旋转到的top节点，这不会超时，因为十分平衡的Splay树高期望是log的，我们只需要将跳上去的路径上的所有节点（所有即将被旋转影响的节点）全部压入栈中，一个一个pushdown之后再pop掉，一直到绽为空，这样就可以保证这一次Splay不会影响到任何没有下放翻转标记的节点！

这样题目就基本上完成了，但是交到洛谷上Wa了。中午想了一下有学长的Bzoj的号，可以看一下他是如何写的，于是我就考虑对拍一下大数据，这让我十分惊讶，居然全对。

交到Bzoj上直接A掉了。但是多组数据很是让人心烦，而且Uva的卡Presentation Error导致Wrong Answer让我十分失望。

希望管理员提供数据下载，毕竟这道题不过我的心里还是有一点余悸的，谢谢！

在讨论区中我会发大样例，随机数据，1e5范围。

代码风格迥异，望包含！

Bzoj AC 代码：

```cpp
#include <bits/stdc++.h>

const  int  N = 200000 + 5 ;

int  ch [ N ] [ 2 ] , siz [ N ] , rev [ N ] , fa [ N ] , val [ N ] , m [ N ] ;
int  ans [ N ] , a [ N ] , n , inf = 1e8 + 7 , root ;

struct  A {
	int  v , id ;
}
aa [ N ] ;

std :: stack < int >  s ;

struct  Splay {
    void  update ( int  pos ) {
        siz [ pos ] = siz [ ch [ pos ] [ 0 ] ] + siz [ ch [ pos ] [ 1 ] ] + 1 ;
    }
    void  init ( ) {
        siz [ 0 ] = 0 ;
        root = build ( 0 , a , 1 , n + 2 ) ;
    }
    void  pushdown ( int  nd ) {
        if ( rev [ nd ] ) {//翻转标记 
            ch [ nd ] [ 0 ] ^= ch [ nd ] [ 1 ] ^= ch [ nd ] [ 0 ] ^= ch [ nd ] [ 1 ] ;
            if ( ch [ nd ] [ 0 ] )  rev [ ch [ nd ] [ 0 ] ] ^= 1 ;
            if ( ch [ nd ] [ 1 ] )  rev [ ch [ nd ] [ 1 ] ] ^= 1 ;
            rev [ nd ] = 0 ;
        }
    }
    int  build ( int  p , int  * a , int  l , int  r ) {
        if ( l > r )  return  0 ;
        int  mid = l + r >> 1 ;
        fa [ mid ] = p ;
        ch [ mid ] [ 0 ] = build ( mid , a , l , mid - 1 ) ;
        ch [ mid ] [ 1 ] = build ( mid , a , mid + 1 , r ) ; 
        val [ mid ] = a [ mid ] ;
        update ( mid ) ;
        return  mid ; 
    }
    void  rotate ( int  nd , int  pd ) {
        int  s = ch [ nd ] [ ! pd ] ;
        int  ss = ch [ s ] [ pd ] ;
        int  p = fa [ nd ] ;
        fa [ nd ] = s ;
        if ( p )  ch [ p ] [ nd == ch [ p ] [ 1 ] ] = s ;
        else  root = s ;
        ch [ s ] [ pd ] = nd ;
        ch [ nd ] [ ! pd ] = ss ;
        if ( ss )  fa [ ss ] = nd ;
        fa [ s ] = p ;
        update ( nd ) ;
        update ( s ) ; 
    }
    void  splay ( int  nd , int  top = 0 ) {
    	for ( int  x = nd ; x != top ; x = fa [ x ] )
    		s . push ( x ) ;
    	while ( ! s . empty ( ) )  pushdown ( s . top ( ) ) , s . pop ( ) ;
        while ( fa [ nd ] != top ) {
            int  p = fa [ nd ] ;
            int  pp = fa [ p ] ;
            int  nl = nd == ch [ p ] [ 0 ] ;
            if ( pp == top )
                rotate ( p , nl ) ;
            else {
                int  pl = p == ch [ pp ] [ 0 ] ;
                if ( pl == nl ) {
                    rotate ( pp , pl ) ;
                    rotate ( p , nl ) ;
                }
                else {
                    rotate ( p , nl ) ;
                    rotate ( pp , pl ) ;
                }
            }
        }
    }
    int  find ( int  pos ) {
        int  nd = root ;
        while ( 1 ) { 
            pushdown ( nd ) ;
            if ( pos <= siz [ ch [ nd ] [ 0 ] ] )
                nd = ch [ nd ] [ 0 ] ;
            else  if ( pos >= siz [ ch [ nd ] [ 0 ] ] + 2 ) {
                pos -= siz [ ch [ nd ] [ 0 ] ] + 1 ;
                nd = ch [ nd ] [ 1 ] ;
            }
            else {
                splay ( nd ) ;
                return  nd ;
            }
        }
    }
    void  erase ( int  pos ) {
        int lnd = find ( pos - 1 ) , rnd = find ( pos + 1 ) ;
        splay ( lnd ) ;
        splay ( rnd , lnd ) ;
        ch [ rnd ] [ 0 ] = 0 ;
        update ( rnd ) ;
        update ( lnd ) ;
    }
    void reverse ( int  l , int  r ) {
    	if ( l > r )  return  ;
        int  lnd = find ( l ) ;
        int  rnd = find ( r + 1 ) ;
        splay ( lnd ) ;
        splay ( rnd , lnd ) ;
        rev [ ch [ rnd ] [ 0 ] ] ^= 1 ;  //打上翻转标记，并且" ^ "保证了原本需要翻转的点现在不需要翻转了 
        pushdown ( ch [ rnd ] [ 0 ] ) ;
        splay ( ch [ rnd ] [ 0 ] ) ;
    }
}
work ;

bool  cmp ( const  A  & a , const  A  & b ) {
	if ( a . v == b . v )  return  a . id < b . id ;
	return  a . v < b . v ;
}

int  main ( ) {
	freopen ( "xx.in" , "r" , stdin ) ;
	freopen ( "xx.out" , "w" , stdout ) ;
	int  gd = 0 ;
	while ( 1 ) {
		gd ++ ;
		scanf ( "%d" , & n ) ;
		if ( n == 0 )  return  0 ;
		memset ( val , 0 , sizeof ( val ) ) ;
		memset ( fa , 0 , sizeof ( fa ) ) ;
		memset ( ch , 0 , sizeof ( ch ) ) ;
		memset ( siz , 0 , sizeof ( siz ) ) ;
		memset ( rev , 0 , sizeof ( rev ) ) ;
		memset ( m , 0 , sizeof ( m ) ) ;
		a [ 1 ] = -inf; a [ n + 2 ] = inf ;
		for ( int  i = 2 ; i <= n + 1 ; i ++ ) {
			scanf ( "%d" , & a [ i ] ) ;
			aa [ i - 1 ] . v = a [ i ] ;
			aa [ i - 1 ] . id = i - 1 ;
		}
		work . init ( ) ;
		std :: sort ( aa + 1 , aa + n + 1 , cmp ) ;
		for ( int  i = 1 ; i <= n ; i ++ ) {
			int  nd = work . find ( aa [ i ] . id + 1 ) ;
			int  deb1 = val [ nd ] ;
			m [ i ] = nd ;
		}
		//int  debug_GYX = work . find ( 5 ) ;
		//printf ( "%d\n" , val [ debug_GYX ] ) ;
		for ( int  i = 1 ; i <= n ; i ++ ) {
			int  tmp = m [ i ] ;
			work . splay ( tmp ) ;
			//print ( root ) ;
			int  deb = val [ tmp ] ;
			int  lzl = siz [ ch [ tmp ] [ 0 ] ] + 1 ;
			ans [ i ] = siz [ ch [ tmp ] [ 0 ] ] ;
			work . reverse ( i , lzl ) ;
		}
		for ( int  i = 1 ; i < n ; i ++ )
			printf ( "%d" , ans [ i ] ) ;
		printf ( "%d" , ans [ n ] ) ;
		printf ( "\n" ) ;
	}
	return  0 ;
}
```

---

## 作者：xixike (赞：2)

[更好的阅读体验](https://www.cnblogs.com/xixike/p/15728014.html)

## Description

[Luogu传送门](https://www.luogu.com.cn/problem/UVA1402)

## Solution

题目要求我们找到第 $i$ 的数，其实就维护一下剩下的数中最小值在哪里即可。

我们考虑使用 $fhq-treap$。

说一下具体实现过程：

- 找到剩下的点中的最小值（其实就是根）。
- 输出答案，删去它，合并它的两个儿子。
- 维护区间翻转标记并下传。

然后就没了。。甚至连 split 都不需要（

并且维护的这个最小值正好满足小根堆的性质，为了方便，我们可以拿输入的数代替 rand 的值。

（但是会被卡）

我们考虑优化建树，使用建**笛卡尔树**的思想来建树。

关于笛卡尔树，戳[这里](https://www.cnblogs.com/xixike/p/15544463.html)。

我们把权值小于当前权值的点挂到当前点的左子树上，再把当前点挂到第一个大于它的点的右子树上，即可构建出一棵相对平衡的平衡树（事实上跑的飞快）。

这个过程就用单调栈维护一下即可。

（这样一来反而不如普通的 $fhq-treap$ 好写了 QwQ）

还有无关紧要的一点，**题目中可能会输入相同的数，如有相同先输出最靠左的**，所以稍微处理一下即可，具体见代码。

## Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ls(x) t[x].l
#define rs(x) t[x].r

using namespace std;

namespace IO{
    inline int read(){
        int x = 0;
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        while(isdigit(ch)) x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
        return x;
    }

    template <typename T> inline void write(T x){
        if(x > 9) write(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace IO;

const int N = 1e5 + 10;
int n;
struct fhq_treap{
    int siz, val, l, r;
    ll wei;
    bool rev;
}t[N];
int rt, tot;

inline void pushup(int x){
    t[x].siz = t[ls(x)].siz + t[rs(x)].siz + 1;
}

inline void pushdown(int x){
    if(t[x].rev){
        swap(ls(x), rs(x));
        if(ls(x)) t[ls(x)].rev ^= 1;
        if(rs(x)) t[rs(x)].rev ^= 1;
        t[x].rev = 0;
    }
}

inline int merge(int x, int y){
    if(!x || !y) return x | y;
    if(t[x].wei <= t[y].wei){
        pushdown(x);
        rs(x) = merge(rs(x), y);
        return pushup(x), x;
    }else{
        pushdown(y);
        ls(y) = merge(x, ls(y));
        return pushup(y), y;
    }
}

int stk[N], top;

inline void build(int x){
    while(top && t[x].wei < t[stk[top]].wei) ls(x) = stk[top--], pushup(ls(x));
    if(top) rs(stk[top]) = x;
    stk[++top] = x;
}

inline void update(int x){
    int l = ls(x), r = rs(x);
    ls(x) = rs(x) = 0;
    t[l].rev ^= 1;
    rt = merge(l, r);
}

signed main(){
    while(1){
        n = read();
        if(!n) break;
        for(int i = 1; i <= n; ++i){
            t[i].wei = 1ll * read() * n + i, t[i].val = i, t[i].siz = 1;
            build(i);
        }
        while(top) pushup(rt = stk[top--]);
        for(int i = 1; i < n; ++i){
            pushdown(rt);
            write(t[ls(rt)].siz + i), putchar(' ');
            update(rt);
        }
        pushdown(rt);
        write(t[ls(rt)].siz + n), puts("");
    }
    return 0;
}
```

$$
\_EOF\_
$$


---

## 作者：TheLostWeak (赞：2)

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/BZOJ3506.html)

**大致题意：** 给你$n$个数。第一次找到最小值所在位置$P_1$，翻转$[1,P_1]$，第二次找到剩余数中最小值所在位置$P_2$，翻转$[2,P_2]$，以此类推。求$P_1,P_2,...,P_n$的值。

------

### 初始化

这题应该是一道比较裸的$Splay$题。

关于$Splay$可以查看这篇博客：[简析平衡树（三）——浅谈Splay](https://www.cnblogs.com/chenxiaoran666/p/Splay.html)。

首先，我们将原数组排序一遍，记下**每一次操作的位置**。

有一个细节，题目要求**相同值要先取位置靠前的**（没注意到这点结果狂$WA$不止）。

然后便是建树。

注意，$Splay$建树的过程中我们一般会在序列左右各加一个多余节点，方便后面取出一段区间进行操作。

------

### 操作

每一次操作，我们把要操作的位置先$Splay$到根，然后就可以得出答案即为此时**左子树的$Size$**，记其为$ans$。

注意是$Size$而不是$Size+1$，要考虑到我们在序列左边加的那个多余节点已经使$Size$比实际存在的节点个数多$1$了。

然后，按照题目要求，我们要翻转区间$[i,ans]$。（关于这一操作的具体过程可以看这道题：[【洛谷3391】【模板】文艺平衡树（Splay）](https://www.luogu.org/problemnew/show/P3391)）

直接将$i$号节点和$ans+2$号节点分别旋到根节点和根节点的右儿子，然后翻转根节点的右儿子的左儿子即可。

------

### 多组数据

由于是多组数据，所以我们要注意清空。

千万注意，清空的是编号为$1\sim n+2$的节点！（本蒟蒻为此调死... ...）

------

### 代码

```cpp
#include<bits/stdc++.h>
#define Type template<typename I>
#define N 100000
#define swap(x,y) (x^=y^=x^=y)
#define INF 1e9
using namespace std;
int n;
struct Data
{
    int pos,val;
    inline friend bool operator < (Data x,Data y) {return x.val^y.val?x.val<y.val:x.pos<y.pos;}
}a[N+5];
class Class_FIO
{
    private:
        #define Fsize 100000
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,Fsize,stdin),A==B)?EOF:*A++)
        #define pc(ch) (FoutSize^Fsize?Fout[FoutSize++]=ch:(fwrite(Fout,1,Fsize,stdout),Fout[(FoutSize=0)++]=ch))
        #define Isi(x) (typeid(x).name()==typeid(1).name())
        #define Isc(x) (typeid(x).name()==typeid('a').name())
        int Top,FoutSize;char ch,*A,*B,Fin[Fsize],Fout[Fsize],Stack[Fsize];
    public:
        Class_FIO() {A=B=Fin;}
        Type inline void read(I& x) {x=0;while(!isdigit(ch=tc()));while(x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));}
        Type inline void write(I x)
        {
            if(Isi(x)) {while(Stack[++Top]=x%10+48,x/=10);while(Top) pc(Stack[Top--]);}
            if(Isc(x)) pc(x);
        }
        template<typename I,typename... A> inline void read(I& x,A&... y) {read(x),read(y...);}
        template<typename I,typename... A> inline void write(I x,A... y) {write(x),write(y...);}
        inline void clear() {fwrite(Fout,1,FoutSize,stdout),FoutSize=0;}
}F;
class Class_Splay//Splay
{
    private:
        #define SIZE N
        #define PushUp(x) (node[x].Size=node[node[x].Son[0]].Size+node[node[x].Son[1]].Size+1)
        #define Rever(x) (swap(node[x].Son[0],node[x].Son[1]),node[x].Rev^=1)
        #define PushDown(x) (node[x].Rev&&(Rever(node[x].Son[0]),Rever(node[x].Son[1]),node[x].Rev=0))
        #define Which(x) (node[node[x].Father].Son[1]==x)
        #define Connect(x,y,d) (node[node[x].Father=y].Son[d]=x)
        #define Split(x,y) (Splay(get_pos(x),rt),Splay(get_pos((y)+2),node[rt].Son[1]),node[node[rt].Son[1]].Son[0])
        int rt;
        struct Tree
        {
            int Size,Rev,Father,Son[2];
        }node[SIZE+5];
        inline void Rotate(int x,int& k)
        {
            register int fa=node[x].Father,pa=node[fa].Father,d=Which(x);PushDown(fa),PushDown(x),
            (fa^k?node[pa].Son[Which(fa)]=x:k=x),node[x].Father=pa,Connect(node[x].Son[d^1],fa,d),Connect(fa,x,d^1),PushUp(fa),PushUp(x);
        }
        inline void Splay(int x,int& k) {register int fa;while(x^k) fa=node[x].Father,fa^k&&(Rotate(Which(x)^Which(fa)?x:fa,k),0),Rotate(x,k);}
        inline void Build(int l,int r,int& rt)
        {
            register int mid=l+r>>1;
            if(node[rt=mid].Size=1,!(l^r)) return;
            l<mid&&(Build(l,mid-1,node[rt].Son[0]),node[node[rt].Son[0]].Father=rt),
            r>mid&&(Build(mid+1,r,node[rt].Son[1]),node[node[rt].Son[1]].Father=rt),
            PushUp(rt);
        }
        inline int get_pos(int rk)
        {
            register int x=rt;
            while(x) 
            {
                if(PushDown(x),node[node[x].Son[0]].Size>=rk) x=node[x].Son[0];
                else if(!(rk-=node[node[x].Son[0]].Size+1)) return x;
                else x=node[x].Son[1];
            }
        }
    public:
        inline void Init(int len) {Build(1,len+2,rt);}
        inline int GetAns(int x) 
        {
            register int k,ans;
            Splay(a[x].pos+1,rt),ans=node[node[rt].Son[0]].Size,k=Split(x,ans),Rever(k);//找到ans，然后翻转
            return ans;//返回答案
        }
        #undef SIZE
}Splay;
int main()
{
    register int i,p;
    for(F.read(n),i=1;i<=n;++i) F.read(a[a[i].pos=i].val);//读入
    for(sort(a+1,a+n+1),Splay.Init(n),i=1;i<=n;++i) F.write(p=Splay.GetAns(i),' ');//初始化排序+依次操作
    return F.clear(),0;
}
```





---

## 作者：peterwuyihong (赞：1)

题意：给定一个序列，你要通过奥妙重重的手段把它排序，就是第 $i$ 次找到 $[i,n]$ 中最小的，把序列的第一位和这一位之间的序列翻转，操作 $n$ 次，但你还要保证这是一个稳定的排序，就是相同元素相对位置不变，然后你每次要输出最小值的位置。

首先这个稳定排序比较奥妙重重，我们使用[[Ynoi2016] 掉进兔子洞](https://www.luogu.com.cn/problem/P4688)的套路，把每个元素加入一个数组，然后排序，但不要去重，离散化时求出排名加上已经出现过的次数，这就是一个完美的映射。

然后硬上万能 fhq 即可，维护区间翻转与最小值，然后每次转完就把最小的点删掉即可，要注意每次输出排名要加上删掉的数的个数。

现在是 $10:53$，我看我什么时候写完。

现在是 $11:17$，我写完了。

```cpp
#define maxn 100010
int n;
struct prpr{
	int l,r,tag;
	int dat,val,siz;
	int mn;
}tree[maxn];
int tot,rt,x,y,z;
mt19937 rnd(time(NULL));
int Build(int val){
	tree[++tot].val=val;
	tree[tot].dat=rnd();
	tree[tot].siz=1;
	tree[tot].mn=val;
	return tot;
}
void Pushdown(int x){
	if(tree[x].tag){
		if(tree[x].l)tree[tree[x].l].tag^=1;
		if(tree[x].r)tree[tree[x].r].tag^=1;
		swap(tree[x].l,tree[x].r);
		tree[x].tag=0;
	}
}
void Pushup(int x){
	tree[x].siz=tree[tree[x].l].siz+1+tree[tree[x].r].siz;
	tree[x].mn=tree[x].val;
	if(tree[x].l){
		if(tree[x].mn>tree[tree[x].l].mn){
			tree[x].mn=tree[tree[x].l].mn;
		}
	}
	if(tree[x].r){
		if(tree[x].mn>tree[tree[x].r].mn){
			tree[x].mn=tree[tree[x].r].mn;
		}
	}
}
void Split(int rt,int k,int &x,int &y){
	if(!rt)x=y=0;
	else{
		Pushdown(rt);
		if(tree[tree[rt].l].siz+1<=k)x=rt,Split(tree[x].r,k-tree[tree[rt].l].siz-1,tree[x].r,y);
		else y=rt,Split(tree[y].l,k,x,tree[y].l);
		Pushup(rt);
	}
}
int Merge(int x,int y){
	if(!x||!y)return x+y;
	if(tree[x].dat<tree[y].dat){
		Pushdown(x);
		tree[x].r=Merge(tree[x].r,y);
		Pushup(x);return x;
	}else{
		Pushdown(y);
		tree[y].l=Merge(x,tree[y].l);
		Pushup(y);return y;
	}
}
int G(int x){
	int k=1;
	while(1){
		Pushdown(x);
		if(tree[x].l&&tree[tree[x].l].mn==tree[x].mn)x=tree[x].l;
		else if(tree[x].r&&tree[tree[x].r].mn==tree[x].mn)k+=tree[tree[x].l].siz+1,x=tree[x].r;
		else return k+tree[tree[x].l].siz;
	}
}
int a[maxn],b[maxn],cnt[maxn];
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
while(cin>>n,n){
	memset(tree,0,sizeof tree);
	memset(cnt,0,sizeof cnt);
	rt=tot=0;
	for(int i=1;i<=n;i++)cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+n+1,a[i])-b,a[i]+=cnt[a[i]]++;
	for(int i=1;i<=n;i++)rt=Merge(rt,Build(a[i]));
	for(int i=1;i<=n;i++){
		int rk=G(rt);
		Split(rt,rk,x,y);
		Split(x,rk-1,x,z);
		tree[x].tag^=1;
		rt=Merge(x,y);
		cout<<rk+i-1<<" \n"[i==n];
	}
}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
```
[一倍经验](https://www.luogu.com.cn/problem/P4402)[双倍经验](https://www.luogu.com.cn/problem/P3165)[三倍经验](https://www.luogu.com.cn/problem/UVA1402)[四倍经验](https://www.luogu.com.cn/problem/SP2059)

---

## 作者：PPL_ (赞：1)

# 前言

适合入门但其实不算很裸的题

# 题目

[洛谷](https://www.luogu.com.cn/problem/UVA1402)

[HDU](http://acm.hdu.edu.cn/showproblem.php?pid=1890)

# 讲解

在做这道题之前，最好先康康这道更板的题：

[P3391 【模板】文艺平衡树](https://www.luogu.com.cn/problem/P3391)

对于这道题，模拟就完事了

我使用平衡树是$Splay$

这道题的难点就在如何快速找到排名第$i$个数的位置

至于$reverse$操作，在板题中应该已经熟悉了

其实很简单，只需要将每个数与其对应在$Splay$上的点的编号记录下来，当你需要找到它的位置的时候，将它$splay$到根即可，它的位置就是左儿子大小+1

注意我们插入的$1$与$n+2$两个哨兵对各种造成的影响

同时注意输出格式，末尾不能有多余空格

# 代码
```cpp
int ID[MAXN];
struct number
{
	int x,pos;
}num[MAXN];

bool cmp1(number a,number b)
{
	if(a.x != b.x) return a.x < b.x;
	return a.pos < b.pos;
}
bool cmp2(number a,number b)
{
	return a.pos < b.pos;
}

#define lc t[x].ch[0]
#define rc t[x].ch[1]
struct Splay
{
	int tot,rt;//点，根
	
	struct node
	{
		int ch[2],val,f,siz,cnt;//儿子，value，父亲，size,count
		bool fz;//翻转标记 
	}t[MAXN];
	
	int newnode(int fa,int val)
	{
		++tot;
		t[tot].ch[0] = t[tot].ch[1] = 0;
		t[tot].siz = t[tot].cnt = 1;
		t[tot].val = val;
		t[tot].f = fa;
		t[tot].fz = 0;
		return tot;
	}
	bool chk(int x)//判断是左儿子还是右儿子 
	{
		return t[t[x].f].ch[1] == x;
	}
	void up(int x)
	{
		t[x].siz = t[lc].siz + t[rc].siz + t[x].cnt;
	}
	void down(int x)
	{
		if(!t[x].fz) return;
		t[x].fz = 0;
		t[lc].fz ^= 1;
		t[rc].fz ^= 1;
		swap(lc,rc);
	}
	int Build(int fa,int l,int r)
	{
		if(l > r) return 0;
		int mid = (l+r) >> 1;
		int x = newnode(fa,num[mid].x);
		ID[num[mid].x] = x;//记录对应在平衡树上点的编号
		lc = Build(x,l,mid-1);rc = Build(x,mid+1,r);
		up(x);
		return x;
	}
	void rotate(int x)
	{
		down(t[x].f);down(x);
		int y = t[x].f,z = t[t[x].f].f;
		bool cz = chk(y),cy = chk(x);
		t[x].f = z; t[z].ch[cz] = x;
		t[y].ch[cy] = t[x].ch[cy^1]; t[t[x].ch[cy^1]].f = y;
		t[x].ch[cy^1] = y; t[y].f = x;
		up(y);up(x);
	}
	void splay(int x,int to = 0)
	{
		while(t[x].f != to)
		{
			int y = t[x].f,z = t[t[x].f].f;
			if(z != to)//双旋 
			{
				if(chk(x) == chk(y)) rotate(y);
				else rotate(x);
			}
			rotate(x);
		}
		if(!to) rt = x;//记得改根 
	}
	int kth(int k)
	{
		int x = rt;
		while(1)
		{
			down(x);
			if(t[lc].siz >= k) x = lc;
			else if(t[lc].siz + t[x].cnt < k) k -= t[lc].siz + t[x].cnt,x = rc;
			else return x;
		}
	}
	void reverse(int l,int r)
	{
		if(l == r) return;
		l = kth(l-1);r = kth(r+1);
		splay(l);splay(r,l);
		t[t[r].ch[0]].fz ^= 1;
	}
	void print(int x)
	{
		if(!x) return;
		down(x);
		print(lc);
		Put(t[x].val,'\n');
		print(rc);
	}
}S;

int main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);	
	while(~scanf("%d",&n) && n)
	{
		S.tot = 0;
		for(int i = 2;i <= n+1;++ i)
			num[i].x = Read(),num[i].pos = i;
		sort(num+2,num+n+2,cmp1);
		num[1].pos = 1;num[n+2].pos = n+2;
		for(int i = 1;i <= n+2;++ i)
			num[i].x = i;
		sort(num+1,num+n+3,cmp2);
		S.rt = S.Build(0,1,n+2);
		for(int i = 2;i <= n+1;++ i)
		{
			S.splay(ID[i]);
			int pos = S.t[S.t[S.rt].ch[0]].siz;
			Put(pos);
			if(i == n+1) putchar('\n');
			else putchar(' ');
			S.reverse(i,pos+1);
		} 
	}
	return 0;
}
```

---

## 作者：Erotate (赞：0)

### 题目大意：

给定一个有 $n$ 个数的序列，然后进行 $n$ 次操作。对于第 $i$ 次操作，记第 $i$ 小值在序列中的位置为 $k$，先输出 $k$，再把 $[i,k]$ 的区间翻转一次。

---
看到区间翻转，区间第 $k$ 小这两个操作，自然而然地就想到了伸展树。

我们发现，在操作中，并不关心每个元素的具体值，而是关心每个元素的位置。那么我们记录两个值，一个是元素在数列中的下标，另一个是元素的值，然后按值从小到大排序，值相同的按下标排序即可。**注意，记得插入哨兵。**

排完序后，值就没用了（因为已经单调递增了），直接建树即可。然后，我们想一想，既然已经单调递增了，那查询第 $k$ 小的时候是不是把序列中对应的下标旋转到根之后，左子树的大小加一就是就是答案了（注意，是下标，不是元素值，所以可以这样做）。最后在找到之后把要反转的区间反转一下一下即可。

### 注意：尽可能的多下传懒惰标记，能下传就下传！

代码：
```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
#define inf 1000000007
using namespace std;
struct Splay{
    int f,s[2],sz,rev;
}tr[N];
struct num{
    int id,h;
}a[N];
int n,rt;
bool cmp(num x,num y){
    return x.h==y.h?x.id<y.id:x.h<y.h;
}
void push_up(int k){
    tr[k].sz=tr[tr[k].s[0]].sz+tr[tr[k].s[1]].sz+1;
}
void push_down(int k){
    if(!tr[k].rev) return;
    if(tr[k].s[0]) tr[tr[k].s[0]].rev^=1;
    if(tr[k].s[1]) tr[tr[k].s[1]].rev^=1;
    swap(tr[k].s[1],tr[k].s[0]);
    tr[k].rev=0;
}
void rotate(int x){
    int y=tr[x].f,z=tr[y].f,k=(tr[y].s[1]==x);
    push_down(y),push_down(x);
    tr[x].f=z,tr[z].s[tr[z].s[1]==y]=x;
    tr[y].s[k]=tr[x].s[k^1],tr[tr[x].s[k^1]].f=y;
    tr[x].s[k^1]=y,tr[y].f=x;
    push_up(y),push_up(x);
}
void splay(int x,int goal){
    while(tr[x].f!=goal){
        int y=tr[x].f,z=tr[y].f;
        if(z!=goal) push_down(z);
        push_down(y),push_down(x);
        if(z!=goal) rotate((tr[y].s[1]==x)^(tr[z].s[1]==y)?x:y);
        rotate(x);
    }
    if(!goal) rt=x;
}
void build(int l,int r,int fa){
    if(l>r) return;
    int mid=l+r>>1;
    if(mid<fa) tr[fa].s[0]=mid;
    else tr[fa].s[1]=mid;
    tr[mid].sz=1,tr[mid].f=fa;
    build(l,mid-1,mid);
    build(mid+1,r,mid);
    push_up(mid);
}
int find(int v){
    int x=rt;
    while(1){
        push_down(x);
        if(v<=tr[tr[x].s[0]].sz && tr[x].s[0]) x=tr[x].s[0];
        else{
            v-=tr[tr[x].s[0]].sz+1;
            if(v==0) return x;
            else x=tr[x].s[1];
        }
    }
}
void reverse(int l,int r){
    l=find(l-1),r=find(r+1);
    splay(l,0),splay(r,l);
    tr[tr[tr[rt].s[1]].s[0]].rev^=1;
}
signed main(){
    while(1){
        scanf("%lld",&n);
        if(!n) break;
        memset(tr,0,sizeof(tr));
        memset(a,0,sizeof(a));
        for(int i=2;i<=n+1;++i){
            scanf("%lld",&a[i].h);
            a[i].id=i;
        }
        a[1].h=-inf,a[n+2].h=inf,a[1].id=1,a[n+2].id=n+2;
        sort(a+1,a+n+3,cmp);
        build(1,n+2,0);
        rt=n+3>>1;
        for(int i=2;i<=n;++i){
            splay(a[i].id,0);
            int ans=tr[tr[rt].s[0]].sz+1;
            printf("%lld ",ans-1);
            reverse(i,ans);
        }
        printf("%lld\n",n);
    }
    return 0;
}
```


---

## 作者：MiniLong (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA1402)

## 题意

给定 $n$ 个整数 $p_1, p_2, p_3 \dots p_n $，$ n $ 次操作分别输出第 $i$ 小值在区间内的位置 $ k $，且翻转区间 $[i, k]$。

## 思路

从**区间翻转**能看出是用 splay 区间树，但 $k$ 小值无法在区间树中维护。

又因为题目只要求输出值的位置，所以考虑将原数组按高度为第一关键字，编号为第二关键字排序一遍，按照编号建树，然后把原数组中第 $k$ 个数值的编号旋转到根，它的左子树的 $ siz $（左子树的 $siz + 1$ 再减去哨兵的 $1$）就是它的位置了（因为排序后是单调递增的）。

接着是翻转操作，就是个 splay 的模板了，将排名为 $i$ 的值转到根，再把刚刚求出来的 $k+2$ 转到根的右子树（因为有哨兵，所以都要加一），这时根的右子树的左子树就是区间 $[i, k]$ 了，然后交换一下它的左右儿子，打个标记就好了。

**注意：标记一定要多 pushdown，在 rotate 和 getk 中都要下传！！！**

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace fastio{
    template<typename T> inline void read(T &t){
        int x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
};
using namespace fastio;
const int N = 100005, inf = 0x3f3f3f3f;
int n, id[10000005];
struct node{
    int x, id;
    bool operator<(const node b)const{
        if(x == b.x) return id < b.id;
        return x < b.x;
    }
}w[N];
int cnt, rt;
struct Tree{
    int fa, son[2], val, rev, siz;
    #define ls a[x].son[0]
    #define rs a[x].son[1]
}a[N];
int New(int fa, int val){
    a[++cnt] = Tree{fa, {0, 0}, val, 0, 1};
    return cnt;
}
void update(int x){
    a[x].siz = a[ls].siz + a[rs].siz + 1;
}
void pushr(int x){
    swap(ls, rs);
    a[x].rev ^= 1;
}
void pushdown(int x){
    if(a[x].rev){
        if(ls) pushr(ls);
        if(rs) pushr(rs);
        a[x].rev = 0;
    }
}
void rotate(int x){
    int y = a[x].fa, z = a[y].fa, k = a[y].son[1] == x;
    pushdown(y), pushdown(x);
    a[z].son[a[z].son[1] == y] = x, a[x].fa = z;
    a[y].son[k] = a[x].son[k ^ 1], a[a[x].son[k ^ 1]].fa = y;
    a[x].son[k ^ 1] = y, a[y].fa = x;
    update(y), update(x);
}
void splay(int x, int goal){
    while(a[x].fa != goal){
        int y = a[x].fa, z = a[y].fa;
        if(z != goal) rotate((a[z].son[1] == y) ^ (a[y].son[1] == x) ? x : y);
        rotate(x);
    }
    if(!goal) rt = x;
}
int getk(int k){
    int x = rt;
    while(1){
        pushdown(x);
        if(k <= a[ls].siz) x = ls;
        else if(k <= a[ls].siz + 1){
            splay(x, 0);
            return x;
        }
        else k -= a[ls].siz + 1, x = rs;
    }
}
void build(int &x, int l, int r, int fa){
    if(l > r) return;
    int mid = l + r >> 1;
    x = mid, a[x] = Tree{fa, {0, 0}, w[mid].id, 0, 1};
    build(ls, l, mid - 1, x);
    build(rs, mid + 1, r, x);
    update(x);
}
int Find(int val){
    int x = rt;
    while(1){
        if(val == a[x].val){
            splay(x, 0);
            return x;
        }
        if(val < a[x].val) x = ls;
        else x = rs;
    }
}
void Reverse(int l, int r){
    int x = getk(l), y = r;
    splay(x, 0), splay(y, x);
    // cout << x << ' ' << y << endl;
    pushr(a[y].son[0]);
}
void debug(int x, bool f = 1){
    pushdown(x);
    if(f) cout << "=================" << '\n';
    printf("num: %d, val: %d, ls: %d, rs: %d, fa: %d\n", x, a[x].val, a[ls].val, a[rs].val, a[a[x].fa].val);
    if(ls) debug(ls, 0);
    if(rs) debug(rs, 0);
}
void dfs(int x){
    pushdown(x);
    if(ls) dfs(ls);
    if(a[x].val != inf && a[x].val != -inf) putchar(' ');
    if(rs) dfs(rs);
}
int main(){
    while(1){
        read(n);
        if(!n) break;
        for(int i = 2; i <= n + 1; ++i){
            read(w[i].x), w[i].id = i;
        }
        w[1].x = -inf, w[n + 2].x = inf, w[1].id = 1, w[n + 2].id = n + 2;
        sort(w + 1, w + 3 + n);
        build(rt, 1, n + 2, 0);
        for(int i = 2; i <= n + 1; ++i){
            splay(w[i].id, 0);
            int k = a[a[rt].son[0]].siz + 1;
            write(k - 1);
            if(i != n + 1) putchar(' ');
            int x = getk(i - 1), y = getk(k + 1);
            splay(x, 0), splay(y, x);
            pushr(a[y].son[0]);
        }   
        puts("");
    }

    return 0;
}
```

---

## 作者：alvis (赞：0)

## $\texttt{Content}$

给定一个长度为 $n$ 的序列，第 $i$ 次操作找到 $[i,n]$ 中最小值 $p_j$，并将区间 $[i,j]$ 翻转，使得实现一种**稳定**排序的效果。输出每次查询出的 $j$。

## $\texttt{Solution}$

很显然的 splay 板子。~~但是很难调~~

因为要实现的是区间反转操作，那么建树的时候就不是以当前点的权值建了，而是以当前点的位置来建。

所以就可以把输进去的值，排一下序，然后就按照下标插入到树里。由于我们按照权值从小到大排的，所以我们也知道了每次操作的 $P_j$ 是多少。

获取结果的时候，就把目标位置转到树顶，然后输出一下左子树大小即可。（加上自己，再减去哨兵节点相当于没有加）

然后区间翻转就是很 naive 的文艺平衡树操作了。

不知道为啥我 cout 跑的超级慢，然后就挂了很多次。

## $\texttt{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;

void qread(int &x) {
	int sum = 0;char c = getchar();
	while(c >= '0' && c <= '9') sum = sum * 10 + c -'0', c = getchar();
	x = sum;
}

const int N = 1e6+5, MAXN = 1e8;
//输入的序列
struct node {
	int v, id;
	node(){}
	node(int _v, int _id){
		v = _v, id = _id;
	}
}num[N];
struct spl{
	node v;
	int s[2], p, minn;
	int size, cnt, fl;
}g[N];
int n ,rt, idx;

//向上合并
void pushup(int u) {
	g[u].size = g[g[u].s[0]].size + g[g[u].s[1]].size + 1; 
	g[u].minn = min(g[u].v.v, min(g[g[u].s[0]].minn, g[g[u].s[1]].minn));
}

//传下翻转标记
void pushdown(int u) {
	if(g[u].fl) {
		swap(g[u].s[0], g[u].s[1]);
		g[g[u].s[0]].fl ^= 1;
		g[g[u].s[1]].fl ^= 1;
		g[u].fl = 0;
	}
}

//splay 板子
void ro(int u) {
	int x = g[u].p, y = g[x].p;
	int k = g[x].s[1] == u;
	g[y].s[g[y].s[1] == x] = u, g[u].p = y;
	g[x].s[k] = g[u].s[k^1], g[g[u].s[k^1]].p = x;
	g[u].s[k^1] = x, g[x].p = u;
	pushup(x); pushup(u);
}

void splay(int u, int k) {
	while(g[u].p != k) {
		int x = g[u].p;
		int y = g[x].p;
		if(y != k) {
			if((g[x].s[1] == u) ^ (g[y].s[1] == x)) ro(u);
			else ro(x);
		}
		ro(u);
	}
	if(!k) rt = u;
}

//插入
void insert(node v) {
	int u = rt, p = 0;
	while(u) p = u, u = g[u].s[v.id > g[u].v.id];
	if(u) {
		g[u].cnt ++;
	}else {
		u = ++ idx;
		if(p) g[p].s[v.id > g[p].v.id] = u;
		g[u].p = p;
		g[u].minn = v.v;
		g[u].size = 1;
		g[u].v = v;
	}
	splay(u, 0);
}

int find_min(int u) {
	while(true) {
		pushdown(u);
		if(g[u].minn == g[u].v.v) return u;
		if(g[u].minn == g[g[u].s[0]].minn) u = g[u].s[0];
		else u = g[u].s[1];
	}
}

int get_k(int k) {
	int u = rt;
	while(true) {
		pushdown(u);
		if(k > g[g[u].s[0]].size + 1) k -= g[g[u].s[0]].size + 1, u = g[u].s[1];
		else if(k == g[g[u].s[0]].size + 1) return u;
		else u = g[u].s[0];
	} 
	return u;
}

bool cmp(node a, node b) {
	if(a.v == b.v) return a.id < b.id;
	return a.v < b.v; 
}

int main() {
	while(true) {
		qread(n);
		if(n == 0) {
			break;
		}
		idx = rt= 0;
		//建树
		//插入哨兵节点
		insert(node(MAXN, 1));
		insert(node(MAXN, n+2));
		g[0].minn = g[0].v.v = MAXN;
		for(int i = 1;i <= n;i ++) {
			qread(num[i].v);
			num[i].id = i;
		}
		
		sort(num+1, num+1+n, cmp);
		for(int i = 1;i <= n;i ++) insert(node(i, num[i].id+1)); 
		
		for(int i = 1;i <= n;i ++) {
			//找到目标节点
			int l = get_k(i), r = get_k(n+2);
			splay(l, 0); splay(r, l); 
			int x = find_min(g[r].s[0]);
			splay(x, 0);
			printf("%d ", g[g[rt].s[0]].size);
			l = get_k(i), r = get_k(g[g[rt].s[0]].size + 2);
			splay(l, 0);splay(r, l);
			g[g[r].s[0]].fl ^= 1; 
		}
		puts("");
		//清空数组
		for(int u = 0;u <= n+2;u ++) {
			num[u].id = 0, num[u].v = 0;
			g[u].size = g[u].fl = g[u].p = g[u].v.v = g[u].cnt = g[u].v.id = g[u].minn = g[u].s[0] = g[u].s[1] = 0;
		}
		
	}
	return 0;
}
```

---

## 作者：Mars_Dingdang (赞：0)

一道经典的区间平衡树题，用 fhq Treap 和 Splay 均可实现。下面提供两者的思路，详细解释前者并提供代码。

## 题目大意
有 $n$ 个数字，$1\le n\le 10^5$，用一个机械臂排序，方法如图所示，每次用机械臂夹住第 $i$ 个数和第 $i$ 小的数翻转，重复此过程直到结束，求第 $i$ 次翻转之前第 $i$ 大的数的位置。

## 大体思路
首先介绍 Splay 的思路。利用其能将结点旋转到根的功能，考虑区间翻转时找到最小的数，将其旋转到根，则其左子树大小就是数列中排在其左边的数的个数。

对于区间翻转，用类似线段树的懒标记记录反转情况，进行区间翻转时令标记 `rev ^= 1`，每次操作时标记下放即可。

注意，每次操作之后，得到的第 $i$ 小值将不参与后续的操作，因此将其直接从树中删除。计算第 $i$ 个排名时加上删去数的个数 $i-1$ 即可。
________

下面介绍 fhqTreap 的思路。由于其能够分裂合并，考虑按照排名进行分裂合并，每次操作时找到最小值的排名 $k$，并将区间 $[1, k]$ 翻转，随后删去该值。每次的答案即为 $k+i-1$。

主要操作涉及 `split`, `merge`, `insert`, `remove`, `pushdown` 等，对于其不熟悉请至模板题《普通平衡树》以及《文艺平衡树》。

## 代码 Code
**注意：本题有多组数据，直接抄袭代码显然无法通过！**
```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define rep(ii,aa,bb) for(re int ii = aa; ii <= bb; ii++)
#define Rep(ii,aa,bb) for(re int ii = aa; ii >= bb; ii--)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef pair<int, int> PII;
const int maxn = 1e5 + 5;
namespace IO_ReadWrite {
	#define re register
	#define gg (p1 == p2 && (p2 = (p1 = _buf) + fread(_buf, 1, 1<<21, stdin), p1 == p2) ? EOF :*p1++)
	char _buf[1<<21], *p1 = _buf, *p2 = _buf;
	template <typename T>
	inline void read(T &x){
		x = 0; re T f=1; re char c = gg;
		while(c > 57 || c < 48){if(c == '-') f = -1;c = gg;}
		while(c >= 48 &&c <= 57){x = (x<<1) + (x<<3) + (c^48);c = gg;}
		x *= f;return;
	}
	inline void ReadChar(char &c){
		c = gg;
		while(!isalpha(c)) c = gg;
	}
	template <typename T>
	inline void write(T x){
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar('0' + x % 10);
	}
	template <typename T>
	inline void writeln(T x){write(x); putchar('\n');}
}
using namespace IO_ReadWrite;
// <------------------ 快读 ----------------->
int n, root, seed = 1, tot; 
// root: 根, tot: 动态开点 
struct node{
	int l, r;
	int val, sz, wei, mi, rev;
    //wei: 随机权值，rev: 懒标记
} a[maxn];
// <--------------- 变量申明 ---------------->
inline int rand1() { return seed *= 19491001; } // 随机权值
template <typename T>
inline T Min(T x, T y) {
	return x < y ? x : y;
}
template <typename T>
inline void Swap(T &x, T &y) {
	T t = x; x = y; y = t;
}
inline void pushup(int p) { //向上更新
	a[p].sz = a[a[p].l].sz + a[a[p].r].sz + 1;
	a[p].mi = Min(a[p].val, Min(a[a[p].l].mi, a[a[p].r].mi));
}
inline void pushdown(int p) { //标记下放
	if (!a[p].rev) return;
	Swap(a[p].l, a[p].r);
	a[a[p].l].rev ^= 1;
	a[a[p].r].rev ^= 1;
	a[p].rev = 0;
}
inline PII split(int p, int k) { 
	//分裂， 返回 pair 表示两棵树的根
	if(!p) return {0, 0};
	pushdown(p);
	if(a[a[p].l].sz < k) {// 分裂右子树
		k -= (a[a[p].l].sz + 1);
		PII t = split(a[p].r, k);
		a[p].r = t.first;
		pushup(p);
		return {p, t.second};
	} else {//继续分裂左子树
		PII t = split(a[p].l, k);
		a[p].l = t.second;
		pushup(p);
		return {t.first, p};
	}
}
inline int merge(int u, int v) {//合并
	if(!u || !v) return u | v;
	if(a[u].wei < a[v].wei) {//u 优先级高，作为父节点
		pushdown(u);
		a[u].r = merge(a[u].r, v);
		pushup(u); return u;
	} else {
		pushdown(v);
		a[v].l = merge(u, a[v].l);
		pushup(v); return v;
	}
}
inline void insert(int k) {
	a[++tot].wei = rand1(); a[tot].sz = 1; a[tot].val = a[tot].mi = k;
    //动态开点
	root = merge(root, tot);//合并
    //由于主函数已经按值排序，此处直接合并至右子树即可
}
inline int find(int p) {//找最小值
	int k = 1;
	while(p) {
		pushdown(p);
		if(a[p].l && a[p].mi == a[a[p].l].mi) p = a[p].l;//左子树
		else if(a[p].r && a[p].mi == a[a[p].r].mi)//右子树
			k += a[a[p].l].sz + 1,
			p = a[p].r;
		else return k + a[a[p].l].sz;//当前节点 
	}
}
inline void reverse(int k) {
	PII x = split(root, k);
	PII y = split(x.first, k - 1);//分离出区间 [1,k]
	a[y.first].rev ^= 1;//标记
	root = merge(y.first, x.second);//删除并合并
}

struct Node {
	int num, pos;
	bool operator <(const Node &x)const {
		if(num != x.num) return num < x.num;
		return pos < x.pos;
	}
} p[maxn];
int v[maxn];

int main () {
	a[0].mi = (1 << 30);//边界
	read(n);
	rep(i, 1, n) 
		read(p[i].num), p[i].pos = i;
	sort(p + 1, p + n + 1);//按值排序
	rep(i, 1, n)
		v[p[i].pos] = i;
	rep(i, 1, n) insert(v[i]);//插入
	rep(i, 1, n) {		
		int k = find(root);//找到最小值的位置
		reverse(k);//区间翻转并删除
		write(k + i - 1), putchar(' ');//输出
	}
	
	return 0;
}
```
## 后记
本题有四倍经验：P3165，P4402，SP2059，UVA1402。

---

## 作者：Su_Zipei (赞：0)

### 不知道为啥难度是黑的。。。

一直对Splay维护区间操作不是很熟练，但是这道题让我学到了很多东西所以写篇题解来巩固一下。

首先模板题是比较好写的因为只有一个权值不需要转化，直接进行区间翻转即可，不过要注意区间反转之后元素的大小关系就发生了变化，即关键字大的就不一定在当前的平衡树中大，因为平衡树的大小关系实际上映射了整个序列。

那么考虑这道题，首先要知道需要干什么，区间翻转操作很好实现，打个标记就完了，但是找到翻转的区间就不那么容易了，可以发现第$i$小值是当前序列中从$i-n$的最小值，因为比它小的都去了前边，所以我们只需要知道最小值的位置就行了，但是如果按照题目中给的权值，最小值可能不唯一，于是先处理一下每个点的权值，因为可能会出现相等的情况，而题目中要求相等的按照下标排序，按照它的要求做就行了。

下面如何进行操作呢？

首先要把我当前处理的$i-n$区间转到右子树，然后找到其中的最小值，这时最小值一定是我要翻转的那个区间的右端点，所以直接对这个区间进行翻转，不过需要注意的是，Splay中第$k$大的元素就是序列中的第$k$个值，最开始这里没想明白然后就挂了。

Splay维护序列的本质就是用k$大的元素表示序列中的第$k$个值。

```
/*
6
3 4 5 1 6 2
4
3 3 2 1
0
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e6+10;
struct Node{
	int id,x;
	Node(){}
	Node(int a,int b){id=a;x=b;}
	bool operator < (const Node&A)const{
		if(x==A.x)return id<A.id;
		return x<A.x;
	}
}a[N];
struct Splay_Tree{
	Node v[N];
	int fa[N],siz[N],Min[N],tag[N],ch[N][2],cnt,rt;
	void clear(){
		memset(fa,0,sizeof(fa));
		memset(siz,0,sizeof(siz));
		memset(Min,0,sizeof(Min));
		memset(tag,0,sizeof(tag));
		memset(ch,0,sizeof(ch));
		cnt=rt=0;
	}
	void up(int x){
		siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
		Min[x]=min(v[x].x,min(Min[ch[x][0]],Min[ch[x][1]]));
	}
	void down(int x){
		if(tag[x]){
			tag[ch[x][0]]^=1;
			tag[ch[x][1]]^=1;
			swap(ch[x][0],ch[x][1]);
			tag[x]=0;
		}
	}
	void rotate(int x){
		int y=fa[x];int z=fa[y];
		int k=ch[y][1]==x;
		ch[z][ch[z][1]==y]=x;
		fa[x]=z;
		ch[y][k]=ch[x][k^1];
		fa[ch[x][k^1]]=y;
		ch[x][k^1]=y;
		fa[y]=x;
		up(y);up(x);
	}
	void splay(int x,int to){
		while(fa[x]!=to){
			int y=fa[x];int z=fa[y];
			if(z!=to)
				(ch[y][1]==x)==(ch[z][1]==y)?rotate(y):rotate(x);
			rotate(x);
		}
		if(!to)rt=x;
	}
	void insert(Node a){
		int u=rt,ff=0;
		while(u)ff=u,u=ch[u][a.id>v[u].id];
		u=++cnt;
		fa[u]=ff;v[u]=a;siz[u]=1;Min[u]=v[u].x;
		if(ff)ch[ff][v[u].id>v[ff].id]=u;
		splay(u,0);
	}
	int kth(int x){
		int u=rt;
		while(1){
			down(u);
			int y=ch[u][0];
			if(siz[y]+1<x)x-=siz[y]+1,u=ch[u][1];
			else if(x<=siz[y])u=y;
			else return u;
		}
	}
	int get(int u){
		while(1){
			down(u);
			if(Min[u]==v[u].x)return u;
			if(Min[u]==Min[ch[u][0]])u=ch[u][0];
			else u=ch[u][1];
		}
	}
	void solve(int x,int n){
		int l=kth(x),r=kth(n+2);
		splay(l,0);
		splay(r,l);
		int now=get(ch[r][0]);
		splay(now,0);
		printf("%d",siz[ch[rt][0]]);
		l=kth(x);r=kth(siz[ch[rt][0]]+2);
		splay(l,0);
		splay(r,l);
		tag[ch[r][0]]^=1;
	}
}s;
int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0)return 0;
		s.clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i].x);
			a[i].id=i;
		}
		sort(a+1,a+n+1);
		s.insert(Node(1,0x7f7f7f7f));
		s.insert(Node(n+2,0x7f7f7f7f));
		s.v[0].x=s.Min[0]=0x7f7f7f7f;
			for(int i=1;i<=n;i++)
			s.insert(Node(a[i].id+1,i));
		for(int i=1;i<=n;i++){
			s.solve(i,n);
			if(i==n)printf("\n");
			else printf(" ");
		}
	}
	return 0;
}

```


---

## 作者：南阳刘子骥 (赞：0)

题目要求我们对一个序列进行一系列反转操作，使得这个序列最终有序。

对于第 $i$ 次旋转，我们都需要找到第 $i$ 小的数，记其位置为 $p_i$，然后反转 $[i,p_i]$ 这段区间。

说到区间反转，我们就可以想到使用 Splay。  
这样就可以借鉴[文艺平衡树](https://www.luogu.com.cn/problem/P3391)的思路了。

我们每一次查询一个权值所对应的节点。找到我们需要反转的区间之后，将其左端点的前驱旋至根，然后将其右端点的后继旋至左端点前驱的下面，这样就拎出来了整个区间了。  
然后直接打反转标记即可。

但是我们还有一个问题。就是题目给出的序列是无序的，我们还需要自己排序。  
同时题目还要求我们做到稳定的排序。也就是两个物品如果高度相等，排序后它们的相对位置关系需要与初始时相同。  
那么我们拿一个结构体记录一下每一个物品的高度和一开始的位置，然后按照权值排序。

然后我们再建立一颗 Splay，像上面说的那样维护、反转区间就可以了。

同时题目要求输出第 $i$ 低的物品在操作之前的位置，我们就先将其代表的节点旋到根，其当前在序列内的位置就是其左子树的大小加上 1。  
这里我向序列中加入了两个哨兵节点，这样会使左子树的大小增加 1，直接输出左子树的大小就可以了。

代码如下：

``` cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100010;
const int INF = 1e8;
int n, m;
struct Node
{
	int s[2], fa;
	int v, sz;
	int flag;
};
Node tr[N];
int rt;
void maintain(int p)
{
	tr[p].sz = tr[tr[p].s[0]].sz + tr[tr[p].s[1]].sz + 1;
}
void pushdown(int p)
{
	if(tr[p].flag)
	{
		if(tr[p].s[0])tr[tr[p].s[0]].flag ^= 1;
		if(tr[p].s[1])tr[tr[p].s[1]].flag ^= 1;
		swap(tr[p].s[0], tr[p].s[1]);
		tr[p].flag = 0;
	}
}
void rotate(int x)
{
	int y = tr[x].fa, z = tr[y].fa;
	int k = (tr[y].s[1] == x) ? 1 : 0;
	tr[z].s[tr[z].s[1] == y] = x, tr[x].fa = z;
	tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].fa = y;
	tr[x].s[k ^ 1] = y, tr[y].fa = x;
	maintain(y); maintain(x);
}
void splay(int x, int k)
{
	while(tr[x].fa != k)
	{
		int y = tr[x].fa, z = tr[y].fa;
		pushdown(z), pushdown(y), pushdown(x);
		if(z != k)
		{
			if((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if(!k)rt = x;
}
void build(int &p, int l, int r)
{
	if(l > r)return;
	int mid = (l + r) >> 1;
	p = mid;
	if(l == r)
	{
		tr[p].sz = 1;
		return;
	}
	if(l < mid)
	{
		build(tr[p].s[0], l, mid - 1);
		tr[tr[p].s[0]].fa = p;
	}
	if(r > mid)
	{
		build(tr[p].s[1], mid + 1, r);
		tr[tr[p].s[1]].fa = p;
	}
	maintain(p);
}
int get_k(int k)
{
	int p = rt;
	while(true)
	{
		pushdown(p);
		if(tr[tr[p].s[0]].sz >= k && tr[p].s[0])p = tr[p].s[0];
		else
		{
			k -= tr[tr[p].s[0]].sz + 1;
			if(k == 0)return p;
			else p = tr[p].s[1];
		}
	}
}
struct TBS
{
	int x, pos;
	bool operator < (const TBS &a)const
	{
		return (x == a.x) ? pos < a.pos : x < a.x;
	}
}p[N];
int main()
{
	scanf("%d", &n);
	p[1] = { -INF,1 }, p[n + 2] = { INF,n + 2 };
	for(int i = 2; i <= n + 1; i++)
	{
		scanf("%d", &p[i].x);
		p[i].pos = i;
	}
	sort(p + 2, p + 2 + n);
	build(rt, 1, n + 2);
	for(int i = 2; i <= n; i++)
	{
		splay(p[i].pos, 0);
		int ans = tr[tr[rt].s[0]].sz;
		printf("%d ", ans);
		int L = get_k(i - 1);
		int R = get_k(ans + 2);
		splay(L, 0); splay(R, L);
		tr[tr[R].s[0]].flag ^= 1;
	}
	printf("%d\n", n);
	return 0;
}
```

[四](https://www.luogu.com.cn/problem/P4402) [倍](https://www.luogu.com.cn/problem/P3165) [经](https://www.luogu.com.cn/problem/SP2059) [验](https://www.luogu.com.cn/problem/UVA1402)


---

## 作者：RemiliaScar1et (赞：0)



观察题意，题目让我们依次输出第 $k$ 大所在位置 $p_k$ 并将 $[k,p_k]$ 翻转。并且我们自始至终只关心位置。所以我们可以按照高度排序，从最小的依次找起。我们将最初始的序列元素依次编号 $1,2,3 \cdots$，问题就落在了如何在序列中查找第 $k$ 号元素，带翻转操作。

我们利用 Splay 的中序遍历维护序列， Splay 的旋转操作不会改变其中序序列。然后当我们查询第 $i$ 号元素时，我们就将 $i$ 转到根，此时根据平衡树的性质，它的左子树大小 $+1$ 就是答案。翻转操作请参考~~照搬~~[P3391 【模板】文艺平衡树
](https://www.luogu.com.cn/problem/P3391)。

是一道不错的 Splay 练手题。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N=1e5+10,INF=1e8+10;

struct node
{
	int s[2],p,v;
	int size,flag;

	void init(int _v)
	{
		v=_v;
		size=1; flag=0;
	}
} tree[N];

int root,idx=0;

int n;
struct pak
{
	int x,no;
} poi[N];

bool cmp(pak a,pak b)
{
	if(a.x==b.x) return a.no<b.no;
	else return a.x<b.x;
}

inline int ls(int x){return tree[x].s[0];}
inline int rs(int x){return tree[x].s[1];}

void push_up(int x)
{
	if(!x) return;
	tree[x].size=tree[ls(x)].size+tree[rs(x)].size+1;
}

void push_down(int x)
{
	if(!tree[x].flag) return ;
	swap(tree[x].s[0],tree[x].s[1]);
	if(ls(x)) tree[ls(x)].flag^=1;
	if(rs(x)) tree[rs(x)].flag^=1;
	tree[x].flag=0;
}

int build(int l,int r)//严格对照中序遍历的方式建树
{
	int mid=l+r>>1;
	int la=0,ra=0;
	if(l<mid) la=build(l,mid-1);
	int u=++idx;
	tree[u].init(poi[mid].x);
	if(r>mid) ra=build(mid+1,r);
	tree[u].s[1]=ra; tree[u].s[0]=la;
	tree[ls(u)].p=tree[rs(u)].p=u;
	push_up(u);
	return u;
}

void rotate(int x)
{
	int y=tree[x].p, z=tree[y].p;
	int k=tree[y].s[1]==x;

	tree[z].s[tree[z].s[1]==y]=x;
	tree[x].p=z;

	tree[y].s[k]=tree[x].s[k^1];
	tree[tree[x].s[k^1]].p=y;

	tree[x].s[k^1]=y; tree[y].p=x;
	push_up(y), push_up(x);
}

void splay(int x,int k)
{
	while(tree[x].p!=k)
	{
		int y=tree[x].p,z=tree[y].p;
		push_down(z); push_down(y); push_down(x);
		if(z!=k)
		{
			if((tree[y].s[1]==x)^(tree[z].s[1]==y)) rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
	if(!k) root=x;
}

int get_k(int k)
{
	int u=root;
	while(1)
	{
		push_down(u);
		if(tree[tree[u].s[0]].size>=k) u=tree[u].s[0];
		else if(tree[tree[u].s[0]].size+1==k) return u;
		else k-=tree[tree[u].s[0]].size+1,u=tree[u].s[1];
	}
	return -1;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&poi[i].x);
		poi[i].no=i;
	}
	poi[0].x=-INF,poi[0].no=1;
	poi[n+1].x=INF,poi[n+1].no=n+1;
	sort(poi+1,poi+1+n,cmp);
	root=build(0,n+1);//建树无所谓在哪里，我们只关心某棵子树的左子树
	for(int i=1;i<n;i++)
	{
		splay(poi[i].no+1,0);//记得加上哨兵节点
		int s=tree[tree[root].s[0]].size;//答案也要减去哨兵
		printf("%d ",s);
		int l=get_k(i),r=get_k(s+2);
		splay(l,0); splay(r,l);
		tree[tree[r].s[0]].flag^=1;
	}
	printf("%d",n);
	return 0;
}

```


---

## 作者：hl666 (赞：0)

这题作为一道十分经典的**平衡树维护序列**的问题，自然是值得一做的了。

写完翻了下题解发现都是写**Splay**的dalao，少有的暴力**FHQ_Treap**党还是用**指针**实现的。

所以这里略微讲解下数组实现的FHQ_Treap好了，感觉写起来比Splay舒服些。

首先我们要抽象化一下题意：给你$n$个数，第$i$次操作在$[i,n]$中找到最小值的位置$p_i$，并**翻转**$[i,p_i]$。最后输出所有$p_i$的值。

然后我们考虑转化问题（因为貌似FHQ_Treap不能同时支持**基于权值**的```split```和**基于排名**的分裂）。

所以离散化是必须的，尤其注意这里不能直接对数组排序（因为会有**权值相等**的点）。

然后我们记一下每个值原来的位置，再考虑对一个**基本序列**（即初始时为$1,2,3,\dots,n$）进行翻转。

手动推导一下我们发现其实就是先找出每次操作位置的**排名**，然后再基本序列上不停翻转区间即可。

由于FHQ_Treap树高期望$\log$的特性，所以我们查询排名的时候可以直接暴力从一个点跳到根然后反着算回来。

最后提一下那种以权值为保证堆性质的值的做法是**错误**的！这样会导致树高不平衡，一旦遇到单调的数据就卡到$O(n^2)$了。

CODE

```cpp
#include<cstdio>
#include<cctype>
#include<algorithm>
#define RI register int
#define CI const int&
#define Tp template <typename T>
using namespace std;
const int N=100005;
struct data
{
    int val,id;
    inline friend bool operator <(const data& A,const data& B)
    {
        return A.val<B.val||(A.val==B.val&&A.id<B.id);
    }
}a[N]; int n,rk;
class FileInputOutput
{
    private:
        static const int S=1<<21;
        #define tc() (A==B&&(B=(A=Fin)+fread(Fin,1,S,stdin),A==B)?EOF:*A++)
        #define pc(ch) (Ftop<S?Fout[Ftop++]=ch:(fwrite(Fout,1,S,stdout),Fout[(Ftop=0)++]=ch))
        char Fin[S],Fout[S],*A,*B; int Ftop,pt[15];
    public:
        Tp inline void read(T& x)
        {
            x=0; char ch; while (!isdigit(ch=tc()));
            while (x=(x<<3)+(x<<1)+(ch&15),isdigit(ch=tc()));
        }
        Tp inline void write(T x,const char& ch)
        {
            if (!x) return (void)(pc('0'),pc(ch)); RI ptop=0;
            while (x) pt[++ptop]=x%10,x/=10; while (ptop) pc(pt[ptop--]+48); pc(ch);
        }
        inline void Fend(void)
        {
            fwrite(Fout,1,Ftop,stdout);
        }
        #undef tc
        #undef pc
}F;
class FHQ_Treap
{
    private:
        struct treap
        {
            int ch[2],size,dat,fa; bool rev;
            inline treap(CI Dat=0,CI Size=0)
            {
                ch[0]=ch[1]=rev=fa=0; dat=Dat; size=Size;
            }
        }node[N]; int tot,rt,seed,stack[N],top;
        #define lc(x) node[x].ch[0]
        #define rc(x) node[x].ch[1]
        #define fa(x) node[x].fa
        inline int rand(void)
        {
            return seed=(int)seed*482711LL%2147483647;
        }
        inline void swap(int& x,int& y)
        {
            int t=x; x=y; y=t;
        }
        inline void rever(CI x)
        {
            swap(lc(x),rc(x)); node[x].rev^=1;
        }
        inline void pushup(CI x)
        {
            node[x].size=node[lc(x)].size+node[rc(x)].size+1; fa(lc(x))=fa(rc(x))=x;
        }
        inline void pushdown(CI x)
        {
            if (node[x].rev) rever(lc(x)),rever(rc(x)),node[x].rev=0;
        }
        inline void merge(int& now,int x,int y)
        {
            if (!x||!y) return (void)(now=x|y); if (node[x].dat>node[y].dat)
            pushdown(x),now=x,merge(rc(now),rc(x),y),pushup(x); else
            pushdown(y),now=y,merge(lc(now),x,lc(y)),pushup(y);
        }
        inline void split(int now,int& x,int& y,int rk)
        {
            if (!now) return (void)(x=y=0); pushdown(now); if (node[lc(now)].size<rk)
            x=now,split(rc(now),rc(x),y,rk-node[lc(now)].size-1); else
            y=now,split(lc(now),x,lc(y),rk); pushup(now);
        }
    public:
        inline void clear(void)
        {
            seed=233; rt=tot=0;
        }
        inline void insert(CI val)
        {
            node[++tot]=treap(rand(),1); merge(rt,rt,tot);
        }
        inline void reverse(RI l,RI r)
        {
            int x,y,z; split(rt,x,y,l-1); split(y,y,z,r-l+1);
            rever(y); merge(y,y,z); merge(rt,x,y);
        }
        inline int get_rk(int now)
        {
            stack[top=1]=now; for (int t=now;fa(t);t=fa(t))	stack[++top]=fa(t);
            while (top) pushdown(stack[top--]); int ret=node[lc(now)].size;
            for (;now;now=fa(now)) if (now==rc(fa(now))) ret+=node[lc(fa(now))].size+1;
            return ret+1;
        }
        #undef lc
        #undef rc
}T;
int main()
{
    //freopen("CODE.in","r",stdin); freopen("CODE.out","w",stdout);
    while (F.read(n),n)
    {
        RI i; T.clear(); for (i=1;i<=n;++i) F.read(a[i].val),a[i].id=i;
        for (sort(a+1,a+n+1),i=1;i<=n;++i) T.insert(i); for (i=1;i<=n;++i)
        rk=T.get_rk(a[i].id),F.write(rk,i!=n?' ':'\n'),T.reverse(i,rk);
    }
    return F.Fend(),0;
}
```



---

