# A Tale of Two Lands

## 题目描述

The legend of the foundation of Vectorland talks of two integers $ x $ and $ y $ . Centuries ago, the array king placed two markers at points $ |x| $ and $ |y| $ on the number line and conquered all the land in between (including the endpoints), which he declared to be Arrayland. Many years later, the vector king placed markers at points $ |x - y| $ and $ |x + y| $ and conquered all the land in between (including the endpoints), which he declared to be Vectorland. He did so in such a way that the land of Arrayland was completely inside (including the endpoints) the land of Vectorland.

Here $ |z| $ denotes the absolute value of $ z $ .

Now, Jose is stuck on a question of his history exam: "What are the values of $ x $ and $ y $ ?" Jose doesn't know the answer, but he believes he has narrowed the possible answers down to $ n $ integers $ a_1, a_2, \dots, a_n $ . Now, he wants to know the number of unordered pairs formed by two different elements from these $ n $ integers such that the legend could be true if $ x $ and $ y $ were equal to these two values. Note that it is possible that Jose is wrong, and that no pairs could possibly make the legend true.

## 说明/提示

Consider the first sample. For the pair $ \{2, 5\} $ , the situation looks as follows, with the Arrayland markers at $ |2| = 2 $ and $ |5| = 5 $ , while the Vectorland markers are located at $ |2 - 5| = 3 $ and $ |2 + 5| = 7 $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/49a110f22f2f955554c4787453bc1d910bd25e72.png)The legend is not true in this case, because the interval $ [2, 3] $ is not conquered by Vectorland. For the pair $ \{5, -3\} $ the situation looks as follows, with Arrayland consisting of the interval $ [3, 5] $ and Vectorland consisting of the interval $ [2, 8] $ :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/764d6883589527503a65e13f965f521d456c3d05.png)As Vectorland completely contains Arrayland, the legend is true. It can also be shown that the legend is true for the pair $ \{2, -3\} $ , for a total of two pairs.

In the second sample, the only pair is $ \{3, 6\} $ , and the situation looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1166C/18e49be72c9003e62671bf9e2781a2db66c67ab9.png)Note that even though Arrayland and Vectorland share $ 3 $ as endpoint, we still consider Arrayland to be completely inside of Vectorland.

## 样例 #1

### 输入

```
3
2 5 -3
```

### 输出

```
2
```

## 样例 #2

### 输入

```
2
3 6
```

### 输出

```
1
```

# 题解

## 作者：maomao (赞：4)

首先你需要明白一个问题:

 $\left|X-Y\right| = \left|X+(-Y)\right|$

 $\left|X+Y\right| = \left|X-(-Y)\right|$

看出来了吗?**每个无序对中的元素的正负不影响它的前后两个区间**

所以:**对每个元素先取个绝对值**.

再观察:每个元素可以造成多大贡献?分类讨论一下.

我们显然可以知道:

$max(\left|X\right|, \left|Y\right|)\leqslant max(\left|X+Y\right|, \left|X-Y\right|)$

所以我们只需要满足

$min(\left|X\right|, \left|Y\right|) \geqslant min(\left|X+Y\right|, \left|X-Y\right|)$

设当前元素为$x$,对于比它小的,最小不能小于$x/2$.对于比它大的,最大不能超过$x\times2$.

所以,我们只要计算一下$[X/2,X\times2]$这个区间中的元素数即可.

但是,对于$[X/2,X]$这一部分,$X$和$X/2$都会计算到,所以,我们对每一个元素,只计算$[X,X\times2]$中的元素数即可.


## $\text{\color{red}{高能预警:}}$
考虑优化.

对于每一个元素$X$,我们关注的是$[X,X\times2]$中的元素数.

那么,直接将所有元素都排个序,我们就可以找出$X$在整个序列中的位置与$(X\times2)+1$的位置差,统计入答案.

排序过的序列满足单调性,所以我们可以通过二分来找到$(X\times2)+1$的位置.

二分的时间复杂度为:$O(nlogn)$,**已经是正解了.**
```cpp
sort(a+1,a+n+1,cmp);
int l,r,mid;
F(i,1,n){
    l=i,r=n+1;
    while(l<r){
        mid=(l+r)>>1;
        if(a[mid]-a[i]<=a[i])l=mid+1;
        else r=mid;
    }
    ans+=l-i-1;
}
```
**但是**,还能更快!!
# $\text{\color{red}{核能预警:}}$
我们发现,你在已排序的序列上找$(X\times2)+1$的位置,**找到的位置仍然满足单调性!!!**

直接上两个指针,以左扫右.$O(n)$解决.

```cpp
sort(a+1,a+n+1,cmp);
int l=1,r=1;
while(l<=n){
    while(a[r]-a[l]>=a[l] && r<=n)r++;
    ans+=(r-l-1);l++;
}
```


---

## 作者：lukelin (赞：4)

~~经过一波数学推算~~，我们发现，设序列为$a$，对于$a_i$它不管是正的还是负的答案都是一样的，所以上来我们就珂以给这个数列ABS一下，然后我们拿到了一个正数数列，那么应该怎么求呢？  
设有两个序列中的数$a_x$,$a_y$。且我们定义$a_y<a_x$。我们发现Arrayland的领土边界为$[a_y,a_x]$，而Vectorland的领土范围为$[a_x-a_y,a_x+a_y]$，注意到因为经过ABS处理的a序列大于等于零，显然$a_x+a_y \geq a_x$，所以是一定满足的，那么我们只需要考虑左端的情况，为了使$a_x - a_y \leq a_y$，变形一下显然需要满足$a_x \leq a_y \times 2$，显然原序列的顺序对答案无影响，所以我们将原序列排序，从头开始枚举每个$a_y$，显而易见，我们的$a_x$只需要在a数组的$[i+1,n]$范围内二分找出最大的$k$，使得$a_k \leq a_i \times 2$，因为原数组排序后的有序性，显而易见a数组中下标小于等于k，大于i的元素都珂以作为$a_x$，那么当前$a_y$对于答案的贡献就是$k - i$。  
完结撒花。

贴个代码：
```cpp
#include <cstdio>
#include <cmath>
#include <algorithm>
#define ll long long

using namespace std;

inline ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

ll a[200005];

int main(){
	int n = read();
	for (int i = 1; i <= n; ++i)
		a[i] = abs(read());
	sort(a + 1, a + n + 1);
	ll ans = 0;
	for (int i = 1; i <= n; ++i){
		int l = i + 1, r = n, k = -1, val = a[i] << 1;
		while (l <= r){
			int mid = (l + r) >> 1;
			if (a[mid] <= val){
				l = mid + 1;
				k = mid;
			}
			else
				r = mid - 1;
		}
		if (k != -1)
			ans += k - i;
	}
	printf("%I64d", ans);
	return 0;
}
```

---

## 作者：XY_cpp (赞：2)

显然右边的$|x+y|$显然是大于$x$，$y$的，我们不需要考虑

考虑每具右边的端点$y$，显然对于某个$x_0$，当$x_0>=y-x_0$时，
$|x_0-y|$在$x_0$左侧，考虑单调队列，瞎搞一下就可以了，复杂度$O(n)$



```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int a[maxn];
long long ans;
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),a[i]=abs(a[i]);
    sort(a+1,a+1+n);
    int l=1,r=2;
    while(l<=n&&r<=n)
    {
        while(a[l]<a[r]-a[l]) l++;
        if(l>n) break;
        ans+=(long long)r-l;r++;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：wangyibo201026 (赞：0)

## 题目思路

首先我们发现 $|x| = |-x|, |x + y| = |x - ( - y )|, |x-y| = |x + ( - y )|$，实际上数的正负对我们是没有影响的。

然后考虑两个条件，首先可以确定的一点就是 $\max(x, y)/\min(x, y) < x + y$，所以第一点的第二个条件和第二点都没用。

然后排个序，发现 $\min(x, y)$ 就是下标小的数，然后双指针就做完了。

## 题目代码

Code：

```cpp
#include <bits/stdc++.h>
 
using namespace std;
 
// #define int long long
#define fir first
#define sec second
#define mkp make_pair //
#define pb push_back
#define lep( i, l, r ) for ( int i = ( l ); i <= ( r ); ++ i )
#define rep( i, r, l ) for ( int i = ( r ); i >= ( l ); -- i )
 
typedef long long ll;
typedef long double ld;
typedef pair < int, int > pii;
 
char _c; bool _f; template < class type > inline void read ( type &x ) {
	_f = 0, x = 0;
	while ( _c = getchar (), !isdigit ( _c ) ) if ( _c == '-' ) _f = 1;
	while ( isdigit ( _c ) ) x = x * 10 + _c - '0', _c = getchar (); if ( _f ) { x = -x; }
}
 
template < class type > inline void chkmin ( type &x, type y ) { x = ( x <= y ? x : y ); }
template < class type > inline void chkmax ( type &x, type y ) { x = ( x >= y ? x : y ); }

const int N = 2e5 + 5;

int n, l = 1, r = 0, ans;
int a[N];

void Solve () {
	cin >> n;
	for ( int i = 1; i <= n; i ++ ) {
		cin >> a[i];
		a[i] = abs ( a[i] );
	}
	sort ( a + 1, a + 1 + n );
	while ( l <= n ) {
		if ( a[r] - a[l] <= a[l] && r <= n ) {
			r ++;
		}
		else {
			ans += r - l - 1;
			l ++;
		}
	}
	cout << ans;
}
 
signed main () {
#ifdef judge
  freopen ( "Code.in", "r", stdin );
  freopen ( "Code.out", "w", stdout );
  freopen ( "Code.err", "w", stderr );
#endif
	Solve ();
	return 0;
}
```

wt 帮忙审一下谢谢。

---

