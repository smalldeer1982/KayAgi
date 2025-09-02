# 枕決め

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2014-morning-easy/tasks/code_festival_morning_easy_d

`CODE FESTIVAL 2014` の参加者のうち、$ n $ 人の人がホテルに宿泊しようとしています。

ホテルには $ m $ 個の部屋があり、部屋 $ i $ には高さが $ a_i $ の枕が置いてあります。 ホテルの部屋はあまり広くないため、$ 1 $ つの部屋には高々 $ 1 $ 人しか宿泊することができません。 参加者はそれぞれ枕の高さに対して好みがあり、$ i $ 番目の参加者は $ x_i $ 以上 $ y_i $ 以下の高さの枕を好んでいます。

できるだけ多くの参加者が好みの枕を使うことができるようにホテルの部屋を割り当てたときに、好みの枕を使うことができる人数を求めてください。

## 样例 #1

### 输入

```
3 3
1 2
2 3
3 4
1
2
3```

### 输出

```
3```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 4
2
4
5```

### 输出

```
2```

## 样例 #3

### 输入

```
3 4
1 4
2 3
5 5
2
4
5
6```

### 输出

```
3```

# 题解

## 作者：qianxinyu (赞：1)

# [枕決め](https://www.luogu.com.cn/problem/AT_code_festival_morning_easy_d)
## 本题解解题要用的知识点：
### 优先队列~~没找到板子，不知道的自己上网搜吧。~~
## 题目大意:
有 $n$ 个范围和 $m$ 个数，一个范围可以对应一个数，要求这个数在这个范围内且每个数只能用一次。求最多可以匹配多少对。
## 思路：
首先，可以想到[二分图最大匹配](https://www.luogu.com.cn/problem/P3386)。建出所有符合要求的边然后匹配。复杂度 $O((n+m)^2)$。但是，这不是我们想要的复杂度。

可以发现，这题的匹配是有限制的。于是，我们可以进行**贪心**。

如果对于最小的数 $a_1$，能匹配肯定是最优的。而匹配时，匹配 $r_i$ 最小的肯定最优。因为对于 $a_2$，可以匹配 $a_1$ 的里 $r_i \ge a_2$ 的，而如果优先匹配大的 $r_i$ 可能会导致 $a_2$ 没法匹配。所以尽量匹配 $r_i$ 小的。
## 处理：
### 令 $a \to $ 数字，$b \to l,r$ 结构体
可以先对 $a$ 排序，对 $b$ 以 $l$ 为第一关键字排序。
然后顺序处理 $a_i$。对于每个 $a_i$，把 $l\ge a_i$ 的都放入优先队列里，优先队列以 $r$ 为第一关键字。然后把 $r\le a_i$ 的全部弹出。如果还存在数，就再弹出一个，答案加一。
## 代码：
```cpp
#include"algorithm"
#include"cstdio"
#include"queue"
const int N=100010;
struct Z{
	int l,r;
	bool operator <(const Z&a)const{
		return r>a.r;
	}
};
struct Zz{
	int l,r;
	bool operator <(const Zz&a)const{
		return l<a.l;
	}
};
int n,m,a[N],ans;
Zz b[N];
std::priority_queue<Z>q;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d%d",&b[i].l,&b[i].r);
	for(int i=1;i<=m;i++)scanf("%d",&a[i]);
	std::sort(b+1,b+n+1);
	std::sort(a+1,a+m+1);
	int now=1;
	for(int i=1;i<=m;i++){
		while(a[i]>=b[now].l&&now<=n)q.push({b[now].l,b[now].r}),now++;//放入
		while((!q.empty())&&a[i]>q.top().r)q.pop();//弹出
		if(!q.empty())ans++,q.pop();//如果还存在数，就再弹出一个，答案加一。
	}
	printf("%d\n",ans);
	return 0;
}
```
## 警示后人
这题一定要在答案后换行，不然过不了。

---

## 作者：AC_love (赞：0)

忽略数据范围的限制，我们可以直接二分图匹配，然而光是边数就达到了 $O(n ^ 2)$ 级别，只好放弃。

把所有住宿者按照喜欢的枕头的高度排序，我们发现每个枕头对应的合适的住宿者一定是一个连续的区间 $[l, r]$。

我们把所有区间 $[l, r]$ 按照左端点排序，然后从左到右依次遍历每个人。如果这个人在某个区间中，就把区间右端点压入一个优先队列，每次选一个最靠左的右端点弹出优先队列即可。

[code](https://atcoder.jp/contests/code-festival-2014-morning-easy/submissions/59506695)

---

## 作者：Yc_cY (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_code_festival_morning_easy_d)

题目大意：给一些区间，给一些点，每个点去匹配区间，问最多能匹配多少点，每个点只能匹配一个区间，每个区间也只能匹配一个点

显而易见的贪心，先把点小到大排序，再把区间按 $L$ 小到大排序。顺序枚举点，并把每个 $L$ 小于等于当前点的区间的 $R$ 都压进一个 multiset 里面，对于每个点，最优匹配显然是大于等于该点值的最小的 $R$ ，直接 lower_bound 找，找不到说明匹配不上，找到了就统计进答案

code：
```cpp
#include<bits/stdc++.h>
#define For( i , a , b ) for( register ll i = ( a ) ; i <= ( b ) ; ++i )
#define Rep( i , a , b ) for( register ll i = ( a ) ; i >= ( b ) ; --i )
#define ll long long
using namespace std ;
inline ll read() {
    ll s = 0 ; char ch = getchar() ; bool f = 0 ;
    for( ; !isdigit( ch ) ; ch = getchar() )  f ^= !( 45 ^ ch ) ;
    for( ; isdigit( ch ) ; ch = getchar() ) s  = (  s <<  3 ) +(  s << 1 ) + (  ch ^ 48 ) ;
    if( f ) return -s; return s ;
}
const int N = 100005 ;
int n , m , b[ N ] , ans , p0 ;
pair < int , int > t[ N ] ;
multiset < int > r ;
int main() {
    n = read() ;
    m = read() ;
    //cout << n << " " << m << '\n' ;
    For( i , 1 , n ) t[ i ].first = read() , t[ i ].second = read() ;
    For( i , 1 , m ) b[ i ] = read() ;
    sort( t + 1 , t + 1 + n ) ;
    sort( b + 1 , b + 1 + m ) ;
    p0 = 1 ;
    For( i , 1 , m ) {
        while( p0 <= n && t[ p0 ].first <= b[ i ] ) r.insert( t[ p0 ].second ) , p0 ++ ;
        multiset < int > ::iterator it = r.lower_bound( b[ i ] ) ;
        if( *it >= b[ i ] ) ++ans , r.erase( it ) ;
    }
    printf("%lld\n" , ans ) ;
    return 0 ;
}

```

---

