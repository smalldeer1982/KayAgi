# Inversion Graph

## 题目描述

You are given a permutation $ p_1, p_2, \dots, p_n $ . Then, an undirected graph is constructed in the following way: add an edge between vertices $ i $ , $ j $ such that $ i < j $ if and only if $ p_i > p_j $ . Your task is to count the number of connected components in this graph.

Two vertices $ u $ and $ v $ belong to the same connected component if and only if there is at least one path along edges connecting $ u $ and $ v $ .

A permutation is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array) and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

Each separate test case is depicted in the image below. The colored squares represent the elements of the permutation. For one permutation, each color represents some connected component. The number of distinct colors is the answer.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1638C/555cddc5b98ba416425dd4322ce8f820d678b370.png)

## 样例 #1

### 输入

```
6
3
1 2 3
5
2 1 4 3 5
6
6 1 4 2 5 3
1
1
6
3 2 1 6 5 4
5
3 1 5 2 4```

### 输出

```
3
3
1
1
2
1```

# 题解

## 作者：lnwhl (赞：18)

## 题目大意
一共有 $T$ 组数据，每组数据给定一个 $1$ 到 $n$ 的排列， 在逆序对之间连边，构成一个无向图，求无向图连通块的数量。
## 思路
首先不可能暴力模拟，但我们可以想一想 **独立的联通块** 是如何构成的。

我们可以发现每个连通块在原序列中是连续的。如果 $p_{i}$ 后有小于 $p_{i}$ 的元素，那么两数之间一定会构成一个逆序对，那么一个连通块就不可能以 $p_{i}$ 结尾。

反之，如果所有比 $p_{i}$ 小的都在 $p_{i}$ 之前，也就是说 $1 \to p_{i}$ （含 $p_{i}$ ）**构成了 $i$ 的全排列**，那么一个连通块一定以 $p_{i}$ 结尾。

在题目中，只要预处理 $1$ 到当前位置的前缀和，如果这个前缀和等于 $\frac{(i+1)\times i}{2}$ ，那么答案就加 $1$。

这样就在 $O(\sum n)$ 的时间内解决了本题。

附上超短代码一份。
## 代码
```
#include <bits/stdc++.h>
using namespace std;
int T,n,a[100005],ans=0;
long long sum=0;
int main()
{
	cin>>T;
	for(int i=1;i<=T;i++)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];sum+=a[i];//sum前缀和 
			if(sum==1LL*(1+i)*i/2)ans++;
		}
		cout<<ans<<endl;sum=0;ans=0;
	}
	return 0;
} 
```


---

## 作者：hzy1 (赞：6)

## CF1638C Inversion Graph

### 题意
给定 $n$ 阶排列 $p_1,p_2,...,p_n$。当 $i<j$ 且 $p_i>p_j$ 时，$p_i$ 与 $p_j$ 之间有一条无向边。求所有 $n$ 个点构成的连通块总数。$t$ 组询问。

### 限制
$\sum n\le 2\times 10^5$。

### 题解一

考虑从后往前遍历整个排列，用 $\text{std::set}$ 维护之前所有 独立的连通块的块内最小值。

考虑当前的 $p_i$，将 $set$ 中可以与 $p_i$ 合并的连通块全部拿出来，将合并之后的块的最小值扔回去。（具体一点，就是将 $set$ 中 $<p_i$ 的元素全部拿出来，与 $p_i$ 取 $min$ 之后将这个 $min$ 扔到 $set$ 中）

正确性：对于任意 $p_i$，如果能与后面的块合并，那么 $p_i$ 一定 $>$ 块内最小值，归纳可知从后往前贪心合并是对的。

时间复杂度 $O(n\log{n})$。

但是我们发现好像没必要用 $\text{std::set}$，可以用单调栈就能做到 $O(n)$。

代码：

$\text{std::set}$ 做法：[CF 提交记录](https://codeforces.com/contest/1638/submission/146471661)

单调栈做法：[CF 提交记录](https://codeforces.com/contest/1638/submission/146719876)

### 题解二

考虑连通块长什么样子。

结论：任意块一定是连续的数构成的，并且任意两个编号为 $i,j~(i<j)$ 的连通块都有 $\max\limits_{x\in i}\{x\}<\min\limits_{y\in j}\{y\}$。

证明连续：如下图，假设第 $i$ 段不连续，红色部分是穿插于 $i$ 中的一些其他元素 $x$。那么如果 $x$ 不被它前面的 $i$ 合并，说明它比前面 $i$ 中的最大值还大，那就一定会与后面的 $i$ 合并。Q.E.D.

![](https://cdn.luogu.com.cn/upload/image_hosting/6jcfwmrl.png)

证明 $\max\limits_{x\in i}\{x\}<\min\limits_{y\in j}\{y\}~(i<j)$：因为已经证明了连续，块之间肯定无交集，所以不满足这个式子的一定会合并。Q.E.D.

有了这个结论，我们可以知道块的整体高度是严格递增的，也就大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/96n8w0sq.png)

所以预处理前缀最大值与后缀最小值，然后从左到右遍历 $n$ 个数，一旦出现 $x$ 满足 $\max\limits_{i=1}^x\{p_i\}<\min\limits_{j=x+1}^n\{p_j\}$，就说明新的块出现了，由于第一块未统计，所以最后答案要 $+1$。

时间复杂度 $O(n)$。

代码：[CF 提交记录](https://codeforces.com/contest/1638/submission/146617046)

### 题解三

结论一：当前 $i$ 个数恰好是 $1$ ~ $i$ 的排列时，就会产生一个新的块。

证明：前 $i$ 个数是 $1$ ~ $i$ 的排列，说明前 $i$ 个数无法与后面的块合并；也不与 上一次出现同样情况的下标 $j$ 合并，因为 $j+1$ ~ $i$ 的数全部大于 $j$ 之前的数。Q.E.D.（注：“上一次出现同样情况的下标 $j$”是指，前 $j$ 个数是 $1$ ~ $j$ 的排列，且 $j$ 是满足 $j<i$ 的最大 $j$）

可以权值树状数组 $O(n\log{n})$ 做。

结论二：结论一等价于 $\max\limits_{j=1}^i\{a_j\}=i$。（或 $\min\limits_{j=i+1}^{n}\{a_j\}=i+1$）

证明：如果前 $i$ 个数中有 $>i$ 的数，显然矛盾。后面那个形式同理。Q.E.D.

所以只需要边输入边记录最大值即可时间复杂度 $O(n)$，空间复杂度 $O(1)$ 做完。

代码：[CF 提交记录](https://codeforces.com/contest/1638/submission/146720087)


---

## 作者：lingfunny (赞：4)

### 前言

本场比赛(#771 div2) tourist 有在 [twitch](https://www.twitch.tv/the__tourist)（科学上网）直播切题 + 讲评（英语，真·俄罗斯口音 XD

回看应该在[油管](https://www.youtube.com/channel/UCkySD00cmDWYHXA31hqRYRw)会放。

### 题解

考虑有两个数字 $100,20$，中间夹了一个数 $x$：

![image-20220215133728280.png](https://s2.loli.net/2022/02/15/9AbwEL2yFPWRofJ.png)

$100\to20$ 显然有边，而满足下面两个条件中的任意一个，$x$ 都会被连到这个连通块里。

1. $x<100$
2. $x>20$

显然 $x$ 必被连到连通块里。

也就是说，对于某个数 $p_i$，对于任意在它右侧且比它小的 $p_j$，$[i,j]$ 中所有数都会是一个连通块。

对于连通块 $[l,r]$ 中最大的数 $p_i$，同理可以延申到 $p_{r'}$，则 $[l,r']$ 可以更新原来的连通块。

那么当 $r=r'$ 时就不再能更新了。

我们可以暴力模拟这个过程，首先定义 $l=r=1$，然后查询区间 $[l,r]$ 的最大值 $M$，并找到右边最后一个小于 $M$ 的位置 $r'$，令 $r\leftarrow r'$，然后不断重复，直到 $r=r'$。然后令 $l=r=r'+1,ans\leftarrow ans+1$。

此时有 $O(n\log n)$ 解法：

发现区间 $[l,r]$ 最大值 $M$ 其实就是前缀 $[1,r]$ 最大值，因为若存在某个数 $x\in[1,l-1]$ 且 $p_x>M$，那么显然会从 $[x,l-1]$ 更新到 $[x,r]$。

处理出后缀 $\min$，然后可以二分查找小于 $M$ 的位置。

可以优化。我们考虑什么时候不会更新：前缀 $\max$ 小于后缀 $\min$。

注意到给出的是一个排列，若前缀 $\max$ 小于后缀 $\min$，显然这个前缀应该是一个 $1\sim\max$ 的排列（反证法，如果不是显然可以往右拓展）。

此时可以做到 $O(n)$，处理前缀 $\max_i$，若发现其值恰好为 $i$，$ans\leftarrow ans+1$。

```cpp
for(int i = 1; i <= n; ++i) {
    mx = max(mx, a[i]);
    if(mx == i) ++ans;
}
```



~~测试时并没有想到 $O(n)$，看到 tourist 能在 5 min 内切掉并敲出这这么简洁的代码着实让我佩服~~



---

## 作者：XeniaF (赞：2)

## $\mathbf{Solution}$

不妨从 $a_1$ 入手：比 $a_1$ 小的元素一定都与 $a_1$ 连通。考虑 $a_2$ 有两种情况：

1. $a_1<a_2$ ，则范围变为了比 $a_2$ 小的元素一定连通。
2. $a_1>a_2$ ，则没有任何变化。

推广到后面的情况似乎也是可以的。一个很 naive 的做法是不断往后扫，记录每个递减子段的开头位置，类似 $a_1,a_2$ 的情况做即可。发现样例都过不去。因为可能在扫到某个开头的时候，虽然比上一个开头要大，但小于上一个开头的所有元素都已经遍历完了。比如 ```3 2 1 6 5 4``` ，在找到 $6$ 的时候 $1\to 3$ 均已遍历完，因此 $[1,3]$ 和 $[4,6]$ 并不连通。容易想到用一个树状数组记录所有数即可。对于 $3$ ，查询遍历到 $6$ 时小于等于它的元素有多少个：如果均已遍历完，则前后不连通， $ans$ 加一。

每找到一个开头，更新最大值即可。具体细节可以看代码。

**$\mathbf{Code}$**

```cpp
#include <bits/stdc++.h>
#define ll int 
#define maxn 200001
using namespace std;
 
ll n;
ll T;
ll a[maxn];
ll ans;
 
inline ll read(){
    ll x=0,f=0;char c=getchar();
    while(!isdigit(c))  f|=c=='-',c=getchar();
    while(isdigit(c))   x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return f?-x:x;
}
 
struct Tree{
    ll tr[maxn];
    inline ll lowbit(ll x) { return x&(-x); }
    inline void cl() {
        for(register int i=1;i<=2*n;++i)
            tr[i]=0;
    }
    inline void add(ll x,ll y){
        while(x<=n)
            tr[x]+=y,x+=lowbit(x);
    }
    inline ll query(ll x){
        ll rs=0;
        while(x){
            rs+=tr[x];
            x-=lowbit(x);
        }
        return rs;
    }
}tr;
 
inline void solve(){
    n=read();
    ll lt=0;
    ans=1;
    tr.cl();
    for(register int i=1;i<=n;++i){
        a[i]=read();
        if(a[i]>lt)
            if(!lt)     lt=a[i];
            else{
                ll p=tr.query(lt);
                if(p==lt)//判断是否连通
                    ++ans;
                lt=a[i];
            }
        tr.add(a[i],1);
    }
    printf("%d\n",ans);
}
 
int main(){
    T=read();
    while(T--)
        solve();
    return 0;
}
```



---

## 作者：Hywel (赞：1)

#### 思路
这里提供一种不同的思路。观察发现，当序列前 $k$ 项恰好为前 $k$ 大时，就会分裂产生新的连通块，所以只需顺序 $i=1-n$ 扫一遍看看前 $i$ 项是不是恰好前 $i$ 大即可。

判断方法为：如果前 $i$ 项的和恰好为 $\frac{i*(i-1)}{2}$，则会产生新的连通块，$ans+1$ 即可。时间复杂度 $O(n)$，空间复杂度优化单次可达 $O(1)$。
#### Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define forever return
using namespace std;

namespace IO
{
	template < typename T > inline void write( T x )
	{
	    if(x < 0)
	        putchar('-') , x = - x;
	    if(x == 0)
	    {
	        putchar('0') ;
	        return ;
	    }
	    if(x > 9)
	        write(x / 10) ;
	    putchar(x % 10 + '0') ;
	    return ;
	}
	template < typename T > inline void read( T &x )
	{
	    x = 0 ; int w = 1 ; char ch = getchar() ;
	    while( !isdigit( ch ) ) { if(ch == '-') w = -1 ; ch = getchar() ; }
	    while( isdigit( ch ) ) x = (x << 1) + (x << 3) + (ch ^ 48) , ch = getchar() ;
	    x *= w;
	}
}

#define writeln(x) write(x) , putchar('\n')
#define writesp(x) write(x) , putchar(' ')
using namespace IO ;

//#define writeln(x) write(x),pc('\n')
//#define writesp(x) write(x),pc(' ')
//using namespace FastIO ;
#define int long long
/* ------------------------------------------------------------------------------------------------------------------------ */
int a[100010] ,b[100010];
set < int > s ;
signed main()
{
	int T ;
	read( T ) ;
	while( T -- )
	{
		s.clear();
		int n ;
		ll res = 0 ;
		read( n ) ;
		for( int i = 1 ; i <= n ; ++ i )
			read( a[ i ] ) , b[ i ] = b[ i - 1 ] + a[ i ] ;
		for( int i = 1 ; i <= n ; ++ i )
		{
			if( b[ i ] == ( i * ( i + 1 ) / 2 ) ) 
				res ++ ;
		}
		writeln( res ) ;
	}
	forever 0 ;
}

```


---

## 作者：Eason_AC (赞：1)

## Content
给定一个 $1\sim n$ 的排列 $p$。我们新建一个包含 $n$ 个点的图，并按照如下方式连边：

- 如果对于两个不同的点 $i,j$，有 $i<j$ 且 $p_i>p_j$，则在这两个点之间连一条边。

求在连完边之后该图包含多少个连通块。

**数据范围：$t$ 组数据，$1\leqslant t\leqslant 10^5$，$1\leqslant n\leqslant 10^5$，$\sum n\leqslant 2\times 10^5$。**
## Solution
不难发现，如果存在一个位置 $x$，使得 $\max\limits_{1\leqslant i\leqslant x}p_i=x$，则节点编号 $>x$ 的所有点都不可能与编号 $\leqslant x$ 的点连边。证明很显然，既然是 $\max\limits_{1\leqslant i\leqslant x}p_i=x$，那么就说明所有 $1\sim x$ 的整数都在位置 $x$ 及以前就出现过了。由上述定义我们可以知道，$\forall j\in[x+1,n]$，必然有 $\max\limits_{1\leqslant i\leqslant x}p_i<p_j$。

因此，我们找出所有的使得 $\max\limits_{1\leqslant i\leqslant x}p_i=x$ 的位置 $x$，设满足该要求的位置有 $k$ 个且分别为 $a_1,a_2,\cdots,a_k$（不妨假定 $a_1<a_2<\cdots<a_k$），则所有编号在 $[1,a_1],[a_1+1,a_2],\cdots,[a_{k-1}+1,a_k]$ 内的点分别构成一个连通块，答案即为 $k$。注意特判 $k=0$ 的情况，此时整张图有 $1$ 个连通块。
## Code
```cpp
namespace Solution {
    const int N = 1e5 + 7;
    int Tnum;
    int n;
    int mx;
    int ans;
    int p[N];

	void Main() {
        read(Tnum);
        while(Tnum--) {
            read(n);
            ans = 0;
            mx = 0;
            for(int i = 1; i <= n; ++i) {
                read(p[i]);
                mx = max(mx, p[i]);
                if(mx == i)
                    ans++;
            }
            write(ans + (!ans));
            puts("");
        }
		return;
	}
}
```

---

## 作者：bmatrix (赞：1)

蒟蒻有一种用 `set` 的乱搞（？）做法。

将题目中的连边要求反着说一遍：$i>j$ 且 $a_i<a_j$。

考虑遍历 $a$ 时，遍历到的 $a_i$ 编号一定要比它前面的大，只需要将前面比它大的元素都和它连起来。

将每个连通块看作一个整体，只要 $a_i$ 比其中任意一个小，$a_i$ 就可以加入这个连通块。

因此可以用 `set` 维护每个连通块的最大值（因为只需要小于最大值即可），在其中 `lower_bound` 或 `upper_bound` 出第一个大于 $a_i$ 的位置。由于所有比 $a_i$ 大的连通块都要和 $a_i$ 相连成为同一个，因此将 `set` 中所有大于 $a_i$ 的元素都删除，只保留最大的一个代表这个连通块。

剩下的一些细节看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
set<int>st;
int main(){
    int t;cin>>t;
    while(t--){
        int n;scanf("%d",&n);
        for(int i=1;i<=n;i++){
            int x;scanf("%d",&x);//干脆在线搞，x即为上文a[i]
            auto it=st.upper_bound(x);
            if(it==st.end())st.insert(x);//it==st.end()说明没有比x大的，因此x独立成为一个连通块
            else while(++it!=st.end())//判断当前是否最大的元素
                it=st.erase(--it);//由于刚才++了，现在要--回来。erase的返回值为下一个元素的迭代器
        }
        printf("%d\n",st.size());
        st.clear();
    }
    return 0;
}
```
时间复杂度：

一次 `upper_bound` 的时间复杂度为 $O(\log n)$，共执行 $n$ 次，`bound` 总复杂度 $O(n\log n)$。

一次 `erase` 的时间复杂度为 $O(\log n)$，每个元素最多被删除 $1$ 次，一共最多删除 $n$ 次，`erase` 总复杂度 $O(n\log n)$。

总复杂度 $O(n\log n)$，可过。

---

## 作者：Cocoly1990 (赞：1)

好像和其他题解的理解方式不太一样。

考虑按编号从小往大添加点。

首先记录下当前的最大值 $x$，设当前添加的点为 $i$.

首先 $x\leftarrow\max\{p_i,x\}$，如果 $x=i$，说明 $1\sim i$ 在前面的 $p_1\sim p_i$ 中间都出现过，**那么之后的任何点都不会和前面的点连边**，则前面的点单独形成一个连通块，独立出来。此时在添加一个点连通块数量加 1.

小注意，至少有一个连通块。

$\mathcal{O}\left(n\right)$ 递推即可。



---

## 作者：lsr1409111459 (赞：1)

### 3.CF1638C Inversion Graph

#### 3.1 题目描述（[传送门](https://www.luogu.com.cn/problem/CF1638C)）

##### 3.1.1 题目大意

给定一个 $1$ 到 $n$ 的一个排列 $p_1,p_2,...,p_n$ 。

按照下列方式构建一个无向图：

- 对于所有的 $i<j$ ，如果满足 $p_i>p_j$ ，则连接一条由 $i$ 到 $j$ 的无向边。 （辅助理解：每对逆序对都连接一条无向边）

你的任务是求出该无向图有多少个连通块。

##### 3.1.2 输入格式

第一行一个整数 $t\ (\ 1\leq t\leq 10^5\ )$ ，表示测试组数。

每组第一行一个整数 $n\ (\ 1\leq n\leq 10^5)$ ，表示排列的长度。

每组第二行 $n$ 个整数 $p_1,p_2,...,p_n\ (\ 1\leq p_i\leq n\ )$ ，表示给定的一个长度为 $n$ 的排列。

可以保证 $t$ 组测试的 $n$ 的和不超过 $2·10^5$ 。

##### 3.1.3 输出格式

共 $t$ 行。

对于每组测试，输出一个整数 $k$ ，表示该排列构建的无向图的连通块数目。

##### 3.1.4 样例

###### 输入 #1

```cpp
6
3
1 2 3
5
2 1 4 3 5
6
6 1 4 2 5 3
1
1
6
3 2 1 6 5 4
5
3 1 5 2 4
```

###### 输出 #1

```cpp
3
3
1
1
2
1
```

##### 3.1.5 样例解释

每组测试的情况如下图所示。带颜色的方块表示排列中的每一项。对于一个排列，每种颜色代表一个连通块。颜色的数量就是答案。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1638C/555cddc5b98ba416425dd4322ce8f820d678b370.png)

#### 3.2 解题思路

我们考虑数列中最大的元素所在的连通块：

- 该连通块包含的元素应该为最大元素及其后面所有元素。

我们再考虑次大元素所在的连通块：

- 如果次大元素在最大元素后面，则其在最大元素所在连通块。
- 否则，次大元素在最大元素前，则排列为： $X,...,X,\text{次大},Y,...,Y,\text{最大}$ 。次大元素到最大元素之间的部分为一个连通块。

一般情况： $X,...,X,\text{小元素},Y,...,Y,\text{大元素},Z,...,Z$。此一般情况含义为： $\text{大元素}>\text{小元素}>Y,\text{大元素}>Z,\text{小元素}>X$ 。即 $\text{大元素}$ 和 $Z$ 在同一连通块内， $\text{小元素}$ 和 $Y$ 在同一连通块内。

- 如果 $Z$ 中有元素比 $\text{小元素}$ 小，则将其连边，说明 $\text{大元素}$ 和 $Z$ 和 $\text{小元素}$ 和 $Y$ 在同一连通块内。
- 否则，说明 $\text{大元素}$ 和 $Z$ ， $\text{小元素}$ 和 $Y$ 二者没有连边，分属两个不同的连通块。

因此我们的步骤如下：

1. 将原数列记录下标并排序。
2. 从最大数向最小数遍历。
3. 如果小数下标小于大数下标，则可能增加连通块。具体判断为大数后是否存在比小数小的数。

判断大数后是否存在比小数小的数，如果单纯遍历的话，复杂度为 $O(n)$ ，外面套上从最大数向最小数遍历，复杂度为 $O(n^2)$ ，显然不能过此题。

因此我们预处理出比小数小的数字中最大的那一个（的下标），即可 $O(n)$ 预处理， $O(n)$ 遍历即可。总时间复杂度为 $O(n)$ 。

#### 3.3 解题代码

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int T,n;
struct node
{
    int i,x;
}b[100010];
int d[100010];
bool cmp(node x,node y)
{
    if(x.x==y.x)return x.i<y.i;
    return x.x<y.x;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&b[i].x);
            b[i].i=i;
        }
        sort(b+1,b+1+n,cmp);
        for(int i=1;i<=n;i++)//d[i]表示 比下标为i的数字小的数字中 下标最大的下标
            d[i]=max(d[i-1],b[i-1].i);
        int t=n+1;//t表示大数的下标，初始时要大于n
        int cntt=0;//连通块数目
        for(int i=n;i>=1;i--)
        {
            if(b[i].i<t)//如果小数下标小于大数下标
            {
                if(d[i]<t)
                    cntt++;//如果比小数小的数字的下标小于大数的下标，说明小数连通块和大数连通块不连通，总连通块个数增一
                t=b[i].i;//更新大数的位置
            }
        }
        printf("%d\n",cntt);
    }
    return 0;
}
```

#### 3.4 解题心得

考场上碰到此题：“诶？这题不是我刚才想错那个想法嘛。”做 B 题时就想过将原数列记录下标然后排序。于是直接将没有过 B 题的代码复制粘贴，修修补补，过了此题。如果没有 B 题，本题可能也没有那么快能想到解法。阴差阳错了属于是。

不过这道题还是挺考思维的，如何在 $O(n)$ 的时间内完成建边和连通块的统计需要注意。

思维题，可能有思维的局限，如果有 hack 数据欢迎补充。

本场 CF 前三题都是考数列的问题，思维题。 D 题好像是搜索，但是考场没实现。之后实现也还没过，过了再补题解吧。

---

## 作者：CmsMartin (赞：1)

## 题面简述

现在有一个序列 $p_1,p_2,\dots,p_n$，你需要构建一个无向图，规则是：当 $i < j$ 且 $p_i > p_j$ 时在 $i$ 和 $j$ 之间连一条无向边。问最后图中会有几个连通块。

[题目传送门](https://codeforces.com/problemset/problem/1638/C)

## 思路

我们考虑什么时候会形成一块。

很显然，当 $\max\limits_{1\le j \le i}(p_j) = i$ 时前面的项就已经出现了 $p_1$ ~ $p_j$ ，对后面的块就没有影响了，这样答案就要加 $1$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e6 + 10;

int T , N;
int Ans;
int Num[MAXN];
int Max;

int main() {
    ios::sync_with_stdio(false);
    cin >> T;
    while(T--) {
        cin >> N;
        Ans = 0;
        Max = 0;
        for(int i = 1; i <= N; i++) cin >> Num[i];
        for(int i = 1; i <= N; i++) {
            Max = max(Max , Num[i]);
            if(Max == i) Ans++;
        }
        cout << Ans << endl;
    }
    return 0;
}
```

---

## 作者：清烛 (赞：0)

来一个和其他题解不太一样（主体代码不超过 7 行）的考场做法，时间复杂度 $O(n)$。

首先我们可以通过观察得到一个很重要的性质：所有的连通块都在原序列上都是连续的一段。

简要证明：考虑反证，假设存在 $k > i$ 且，$a_i$ 和 $a_k$ 有连边（显然 $a_i$ 和 $a_k$ 不相邻），则说明 $a_k < a_i$ 且 $\forall j \in (i, k)$，有 $a_i < a_j$。由不等式的传递性知 $a_j > a_k$，故 $\forall j\in(i, j)$，$a_j$ 和 $a_k$ 都有连边，与假设矛盾。

所以我们可以考虑从左到右扫，维护一下当前连续段的最右端，如果到头了就 `++ans`。

具体维护方式为：记录一下 $a_i$ 的位置 $\mathrm{pos}_{a_i}$，然后每扫一个 $i$ 就用 $\mathrm{pos}_{a_i - 1}$ 来尝试更新当前连续段的最右端。

至于这样为什么是对的，可以简要的说明一下：因为若 $a_i - 1$ 不是当前连续段的最右端，则在往右迭代的过程中总会用 $a_i - 2,\cdots$ 来进行更新，所以这样子做是正确的。

```cpp
const int maxn = 1e5 + 5;
int n, a[maxn], pos[maxn];

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]), pos[a[i]] = i;
        int rightmost = 0, ans = 0;
        FOR(i, 1, n) {
            if (i > rightmost) ++ans;
            chkmax(rightmost, pos[a[i] - 1]);
        }
        print(ans);
    }
    return output(), 0;
}
```

---

