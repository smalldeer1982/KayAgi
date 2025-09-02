# Inverse Genealogy

## 题目描述

Ivan is fond of genealogy. Currently he is studying a particular genealogical structure, which consists of some people. In this structure every person has either both parents specified, or none. Additionally, each person has exactly one child, except for one special person, who does not have any children. The people in this structure are conveniently numbered from $ 1 $ to $ n $ , and $ s_i $ denotes the child of the person $ i $ (and $ s_i =       0 $ for exactly one person who does not have any children).

We say that $ a $ is an ancestor of $ b $ if either $ a =       b $ , or $ a $ has a child, who is an ancestor of $ b $ . That is $ a $ is an ancestor for $ a $ , $ s_a $ , $ s_{s_a} $ , etc.

We say that person $ i $ is imbalanced in case this person has both parents specified, and the total number of ancestors of one of the parents is at least double the other.

Ivan counted the number of imbalanced people in the structure, and got $ k $ people in total. However, he is not sure whether he computed it correctly, and would like to check if there is at least one construction with $ n $ people that have $ k $ imbalanced people in total. Please help him to find one such construction, or determine if it does not exist.

## 说明/提示

In the first example case one can have a construction with 3 people, where 1 person has 2 parents.

In the second example case one can use the following construction:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1379E/56ef807b09159148574a73651e0ad3983f5cacfe.png)Only person 1 is imbalanced, because one of their parents has 1 ancestor in total, and the other parent has 3 ancestors.

## 样例 #1

### 输入

```
3 0```

### 输出

```
YES
0 1 1```

## 样例 #2

### 输入

```
5 1```

### 输出

```
YES
0 1 1 3 3```

## 样例 #3

### 输入

```
3 2```

### 输出

```
NO```

# 题解

## 作者：crashed (赞：16)

# 题目
[点这里](https://www.luogu.com.cn/problem/CF1379E)看题目。   
# 分析
对于这种构造题目，我们首先考虑**边界情况**。比如，我们可以计算不平衡点的上界，并且找到对应的构造方案，然后构造出来。   
   
这个上界可以如下构造：   
   
```
          o
         / \
        o   o
       / \
      o   o
     /
   ...
   /
  o
 / \
o   o
```     

也就是，首先构造一条链，长度为 $\frac{n+1}{2}$（显然，有解的 $n$ 一定是**奇数**）。接着，我们给链上的除**任一端点**以外的所有点加上一个儿子。这样我们就可以得到一棵有 $\frac{n-3}{2}$ 个不平衡点的树。可以发现这就是构造的上界。    
    
现在，我们称 $T_k$ 为长成这个样子的树：   
   
```
          1
         / \
        2   o
       / \
      3   o
     / \
   ...  o
   /
  k
   \
    o
```    
   
此时只要节点 $k$ 的左儿子大小大于 1，我们就可以获得 $k$ 个不平衡点的贡献（否则也会有 $k-1$ 个的贡献）。可以发现我们刚刚构造的上界就是这样构造出来的。
   
接着考虑不平衡点的下界。显然，如果 $n=2^k-1(k>0)$，那么它就可以构造出没有不平衡点的树。否则，最少只能构造出有一个不平衡点的树。这两种情况的构造方法是一样的，都是构造成完全二叉树的样子。   

将两个极端结合起来——如果 $k<2$，我们可以判断并构造。否则，我们可以首先构造出 $T_{k-1}$ 。然后构造出带来 1 的贡献的树，并且接到 $T_{k-1}$ 下面去。   
   
如果 $n-2(k-1)$ 不能构成满二叉树，我们就可以直接构造成完全二叉树并且接到 $T_{k-1}$ 下面去。    
    
否则，考虑丢掉满二叉树的几个点，使得它不满，然后接到 $T_{k-1}$ 下面。接着，我们只需要给提出来的点找位置就好了。    
    
不难想到构造 $n-2$ 大小的树，接到 $T_{k-1}$ 下面，然后将 2 个点接到 1 的右儿子上。此时，只要 1 的左儿子足够大，1 还是可以成为不平衡点。   
   
这样的构造方法只会有一个反例：```n=9,k=2```。而经过枚举可以发现它是真的无解。     
   
于是问题就解决了，时间复杂度是 $O(n)$。

# 代码
```cpp
#include <cstdio>

const int MAXN = 1e5 + 5, MAXLOG = 50;

template<typename _T>
void read( _T &x )
{
    x = 0;char s = getchar();int f = 1;
    while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
    while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
    x *= f;
}

template<typename _T>
void write( _T x )
{
    if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
    if( 9 < x ){ write( x / 10 ); }
    putchar( x % 10 + '0' );
}

template<typename _T>
void swapp( _T &x, _T &y )
{
    _T t = x; x = y, y = t;
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
    return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
    return a > b ? a : b;
}

int ance[MAXN];
int N, M, K;

int Lowbit( const int x ) { return x & ( -x ); }
bool Chk( int x ) { return x - Lowbit( x ) == 0; }

int main()
{
    read( N ), read( K );
    int lim = MAX( ( N - 3 ) / 2, 0 );
    if( K > lim ) return puts( "NO" ), 0;
    if( N % 2 == 0 ) return puts( "NO" ), 0;
    if( N == 9 && K == 2 ) return puts( "NO" ), 0;
    if( Chk( N + 1 ) && K == 1 ) return puts( "NO" ), 0;
    if( ! Chk( N + 1 ) && K == 0 ) return puts( "NO" ), 0;
    
    puts( "YES" );
    int base = 2 * MAX( 0, K - 1 ); 
    for( int i = 1 ; i < base ; i += 2 )
        ance[i + 1] = i, ance[i] = MAX( 0, i - 2 );
    for( int i = 1 ; i <= N - base ; i ++ )
    {
        if( i == 1 ) ance[i + base] = MAX( 0, base - 1 );
        else ance[i + base] = ( i >> 1 ) + base;
    }   
    if( Chk( N - base + 1 ) && K ) ance[N - 1] = ance[N] = 2;
    for( int i = 1 ; i <= N ; i ++ ) write( ance[i] ), putchar( i == N ? '\n' : ' ' );
    return 0;
}
```

---

## 作者：lzqy_ (赞：7)

一道评分虚高的构造题。

首先考虑在总点数固定的情况下，如何构造出最多的非平衡点。容易发现构造方式如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/nd0omut1.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

也就是说，若 $n<2m+3$，那么一定无解。

考虑先按照如下方式构造出一棵二叉树，用去 $(2m+3)$ 个节点，然后再往树里面加上剩余的 $(n-(2m+3))$ 个节点。

那么问题就转化为了如何在总点数固定的情况下，构造出最少的平衡点，那么显然是构造出一棵完全二叉树。又为了不额外增加非平衡点，考虑往深度最深的非平衡点的右儿子下挂完全二叉树，大致是这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/wegfq2il.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

但是这个时候又会有新的问题出现，即如果挂的完全二叉树并不是满二叉树，那么仍然会多增加一个非平衡点。所以我们还需要把节点 $1,2$（上图的根节点与其左儿子）拆下来挂到其他的地方，并且保证新挂到的地方不能新增非平衡点。

观察此时的树，实际上只有两个位置可以挂，即所有非平衡点的左儿子底下以及完全二叉树下。只需要判断是否能挂在这两种位置上，如果能挂则可构造，不能挂则不可构造。

- 非平衡点的左儿子底下

  首先要满足 $m>1$，否则没地方挂。

  如果挂在这种位置下是合法的，那么必须保证该非平衡点的右子树 $>6$（否则会少一个非平衡点）。那么显然挂在深度最浅的非平衡点下最优。而该非平衡点的右子树有 $(n-4)$ 个点，所以只需要判断 $n-4>6$ 是否成立即可。

  综上，$m>1$ 且 $n>10$。

- 完全二叉树下

  上文说到，完全二叉树只有在满二叉树形态下才不会贡献非平衡点。如果新增两个节点后，完全二叉树变成了满二叉树，那么非平衡点总数就会减少 $1$。除此以外的情况都可以。

  综上，$(n-2m+3)+2$ 个节点不能构造出满二叉树。

总结一下，先构造出非平衡点最多的树的形态，然后把剩余的点以完全二叉树的形态挂到树的最深层。如果非平衡点多了 $1$，就把 $1,2$ 节点取下来，判断是否有地方挂，如果有，则可构造，没有则不可构造。

注意判断 $n$ 为奇数的情况。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int maxn=200010;
int n,m,N,cnt,fa[maxn];
void build1(int i,int beg=0){
	if(i>N) return ;
	fa[(i-beg<<1)+beg]=fa[(i-beg<<1|1)+beg]=i;
	build1((i-beg<<1)+beg,beg);
	build1((i-beg<<1|1)+beg,beg);
}//建以 (Beg+1) 为根的完全二叉树
void build2(int i){
	if(cnt==m) return ;
	fa[i+1]=fa[i+2]=i,cnt++;
	build2(i+2);
}//建非平衡点最多的二叉树
int Print(){
	printf("YES\n");
	for(int i=1;i<=N;i++)
		printf("%d ",fa[i]);
	return printf("\n"),0;
}
int main(){
	scanf("%d%d",&n,&m),N=n;
	if(n&1^1) return printf("NO\n"),0;
	if(m==0){
        //m=0直接看是不是满二叉树
		if((1<<((int)log2(n+1)))!=n+1)
			return printf("NO\n"),0;
		build1(1);return Print();
	}
	if(m*2+3>n) return printf("NO\n"),0;
    //判断m上界
	build2(1),n-=m*2+3;
	build1(2*m+1,2*m);
    //非平衡点最多的二叉树下挂完全二叉树
	if((1<<((int)log2(n+4)))==n+4) return Print();//如果恰好是满二叉树则输出
	if((N-4)>6&&m>1){
        //1,2挂非平衡点下
		fa[3]=0,fa[1]=fa[2]=4;
		return Print();
	}
	if((1<<(int)log2(n+6))!=n+6){
        //1,2挂完全二叉树下
		fa[3]=0,fa[1]=fa[2]=(N+1-2*m>>1)+2*m; 
		return Print();
	}printf("NO\n");
	return 0;
}
```

其他题解里提到的特判，其实就是 $1,2$ 节点无处可挂的情况。但其实不需要特判也是可以有完整的构造方式的。

---

## 作者：EuphoricStar (赞：3)

$n$ 为偶数显然无解。

否则我们可以构造一棵 $n$ 个点的完全二叉树，当 $n + 1$ 是 $2$ 的幂时满足 $m = 0$，否则 $m = 1$。

当 $n \ge 5$ 时可以递归至 $(n - 2, m - 1)$，再挂一个叶子即可。

但是可能会出现 $n + 1$ 是 $2$ 的幂，但 $n - 1$ 不是，可能会把有解判成无解。

打一个补丁，如果上面那种情况递归下去无解，当 $n \ge 11$ 时我们可以接一棵 $3$ 个点的满二叉树，然后再递归至 $(n - 4, m - 1)$。

时间复杂度 $O(n)$。

[code](https://codeforces.com/problemset/submission/1379/240998627)

---

