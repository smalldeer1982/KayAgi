# Kuroni and the Gifts

## 题目描述

Kuroni has $ n $ daughters. As gifts for them, he bought $ n $ necklaces and $ n $ bracelets:

- the $ i $ -th necklace has a brightness $ a_i $ , where all the $ a_i $ are pairwise distinct (i.e. all $ a_i $ are different),
- the $ i $ -th bracelet has a brightness $ b_i $ , where all the $ b_i $ are pairwise distinct (i.e. all $ b_i $ are different).

Kuroni wants to give exactly one necklace and exactly one bracelet to each of his daughters. To make sure that all of them look unique, the total brightnesses of the gifts given to each daughter should be pairwise distinct. Formally, if the $ i $ -th daughter receives a necklace with brightness $ x_i $ and a bracelet with brightness $ y_i $ , then the sums $ x_i + y_i $ should be pairwise distinct. Help Kuroni to distribute the gifts.

For example, if the brightnesses are $ a = [1, 7, 5] $ and $ b = [6, 1, 2] $ , then we may distribute the gifts as follows:

- Give the third necklace and the first bracelet to the first daughter, for a total brightness of $ a_3 + b_1 = 11 $ .
- Give the first necklace and the third bracelet to the second daughter, for a total brightness of $ a_1 + b_3 = 3 $ .
- Give the second necklace and the second bracelet to the third daughter, for a total brightness of $ a_2 + b_2 = 8 $ .

Here is an example of an invalid distribution:

- Give the first necklace and the first bracelet to the first daughter, for a total brightness of $ a_1 + b_1 = 7 $ .
- Give the second necklace and the second bracelet to the second daughter, for a total brightness of $ a_2 + b_2 = 8 $ .
- Give the third necklace and the third bracelet to the third daughter, for a total brightness of $ a_3 + b_3 = 7 $ .

This distribution is invalid, as the total brightnesses of the gifts received by the first and the third daughter are the same. Don't make them this upset!

## 说明/提示

In the first test case, it is enough to give the $ i $ -th necklace and the $ i $ -th bracelet to the $ i $ -th daughter. The corresponding sums are $ 1 + 8 = 9 $ , $ 8 + 4 = 12 $ , and $ 5 + 5 = 10 $ .

The second test case is described in the statement.

## 样例 #1

### 输入

```
2
3
1 8 5
8 4 5
3
1 7 5
6 1 2```

### 输出

```
1 8 5
8 4 5
5 1 7
6 2 1```

# 题解

## 作者：gyh20 (赞：2)

因为 $a_i,b_i$ 两两不同，所以排序后

$a_1 < a_2 <\dots < a_n$

$b_1 < b_2 <\dots < b_n$

加起来

$a_1+b_1 < a_2+b_2 <\dots < a_n+b_n$

满足题意两两不等。

综上，直接排序，然后输出和即可。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;
	re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0'){
		t=(t<<3)+(t<<1)+v-48;
		v=getchar();
	}
	return t;
}
int t,n,a[100002],b[100002];
int main(){
	t=read();
	while(t--){
		n=read();
		for(re int i=1;i<=n;++i)a[i]=read();
		for(re int i=1;i<=n;++i)b[i]=read();
		sort(a+1,a+n+1);
		sort(b+1,b+n+1);
		for(re int i=1;i<=n;++i)printf("%d ",a[i]);
		putchar('\n');
		for(re int i=1;i<=n;++i)printf("%d ",b[i]);
		putchar('\n');
	}
}
```


---

## 作者：xht (赞：2)

由于 $a,b$ 分别互不相同，因此想让 $a+b$ 互不相同，对 $a,b$ 分别排序即可。

```cpp
const int N = 107;
int n, a[N], b[N];

inline void solve() {
	rd(n), rda(a, n), rda(b, n);
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
		print(a[i], " \n"[i==n]);
	for (int i = 1; i <= n; i++)
		print(b[i], " \n"[i==n]);
}

int main() {
	int T;
	rd(T);
	while (T--) solve();
	return 0;
}
```

---

## 作者：_Harrisonwhl_ (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1305A)
由于 $a$ 数组中的数两两不同,$b$ 数组中的数也两两不同，所以将两数组排完序后满足条件：

$a_1<a_2<......<a_n$

$b_1<b_2<......<b_n$

将两式相加，得：

$a_1+b_1<a_2+b_2<......<a_n+b_n$

不会重复。

时间复杂度为 $O(nlogn\cdot t)$,不会超时。

完整代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105],b[105];
int main()
{
    int t,n;
    cin >> t;//多组数据
    while (t--)
    {
    	//输入
        cin >> n;
        for (int i = 1;i <= n;i++)
            cin >> a[i];
        for (int i = 1;i <= n;i++)
            cin >> b[i];
        sort(a + 1,a + n + 1);//排序
        sort(b + 1,b + n + 1);//排序
        //输出
        for (int i = 1;i <= n;i++)
            cout << a[i] << " ";
        cout << endl;
        for (int i = 1;i <= n;i++)
            cout << b[i] << " ";
        cout << endl;
    }
    return 0;
}
```


---

## 作者：JimmyF (赞：1)

### [CF1305A题目直通车](https://www.luogu.com.cn/problem/CF1305A)

由于这题说
$a_i$
和
$b_i$
各不相同。

那如果将它们排序后就变成：

$a_1<a_2<a_3<⋯<a_n$

$b_1<b_2<b_3<⋯<b_n$

加起来就变成
$a_1+b_1<a_2+b_2<a_3+b_3<a_n+b_n$

满足了题目说的“两两不相等”。

总结思路：

1. 输入$a$和$b$数组
2. 排序
3. 分别输出

~~貌似很水~~

### AC Code
```cpp
#define f(i,x,y) for(int i=x; i<=y; i++)
#define st(a) sort(a+1,a+1+n)
#define qr(x) scanf("%d",&x)
#define qw(x) printf("%d ",x)
#define qe printf("\n")
#include<bits/stdc++.h>
using namespace std;
int n,t,a[110],b[110];
int main()
{
	qr(t);
	while(t--)
	{
		qr(n);
		f(i,1,n)
			qr(a[i]);
		f(i,1,n)
			qr(b[i]);
		st(a);
		st(b);
		f(i,1,n)
			qw(a[i]);
		qe;
		f(i,1,n)
			qw(b[i]);
		qe;	
	}
	return 0;
}
```


---

## 作者：Smg18 (赞：0)

本题的目标是使 $a_{i}$ 和 $b_{i}$ 相加的和互不相同。

题目已经贴心的给了我们每个序列的数只出现一次，所以我们只需要从小到大排序后加在一起，必定不同。


代码如下：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define Test ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
using namespace std;
const int N=1e5+10,NN=1e4+10;
ll n,m,k,len,T;
ll minn=INT_MAX,maxn=0;
char c[NN][NN];
ll arr[N],brr[N];

int main(){
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
		}
		for (int i = 1; i <= n; i++) {
			cin >> b[i];	
		}
		sort(a+1,a+n + 1);//排序
		sort(b+1,b+n + 1);//排序
		for (int i = 1; i <= n; i++) cout<<a[i]<<" ";
		cout<<endl;
		for (int i = 1; i <= n; i++) cout<<b[i]<<" ";
		cout<<endl;
	}
	return 0;
	
}



```

样例好像仅供参考。

---

## 作者：TheShuMo (赞：0)

## 思路
首先看到这道题有可能会想到是用暴力枚举一下所有数的排列，但由于其过高的复杂度在这道题显然是不可取的。

所以这道题肯定就有更加巧妙的做法。

通过观察样例我们可以发现：只要把输出稍稍改一下改成从大到小的，同样符合题意。思路就出来了。

即排序数组 $a,b$ 使 $a_0 > a_1>a_2>\cdots>a_{n-1}>a_n$

$b_0 > b_1>b_2>\cdots>b_{n-1}>b_n$

那么上下两个不等式相加得

$a_0+b_0 > a_1+b_1 >a_2+b_2 >\cdots>a_{n-1}+b_{n-1}>a_n+b_n$ 

满足题目需求（其实此处还因为 $a,b$ 数组中任意两数都不相等，不然有可能出现相等的情况。）

---

## 作者：JustinXiaoJunyang (赞：0)

 思路分析：

本题思路易得：把 $a$ 和 $b$ 从小到大排序，保证 $a_i \neq b_i$。

根据题意：可能有多解，任意输出一种解即可。如果较真，把 $a$ 和 $b$ 从大到小排序也行，同样符合“单调性”。

推倒如下：

考虑小的和小的加，大的和大的加。对于相邻位置，设 $a$ 相邻位置元素为 $x$ 与 $x+m$，设 $b$ 相邻位置元素为 $y$ 与 $y+n$。

由于已经进行从小到大排序而且序列元素不同，那么一定满足 $m>0$ 且 $n>0$。

根据上述，$s_1=x+y<x+m+y+n=s_{i+1}$。那么这种方法可行。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[105], b[105];

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		for (int i = 1; i <= n; i++)
			cin >> b[i];
		sort(a + 1, a + n + 1);
		sort(b + 1, b + n + 1);
		for (int i = 1; i <= n; i++)
			cout << a[i] << " ";
		cout << endl;
		for (int i = 1; i <= n; i++)
			cout << b[i] << " ";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Xdl_rp (赞：0)

~~这道题挺水的~~

进入正题
------------
$\because$ 当两个数组都排完序之后：

$a_i < a_{i+1} < a_{i+2} < …… < a_n$

$b_i < b_{i+1} < b_{i+2} < …… < b_n$

$\therefore a_i+b_i<a_{i+1}+b_{i+1}<……<a_n+b_n$

所以直接输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[1005], b[1005];
int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) cin >> b[i];
		sort(a + 1, a + n + 1);
		sort(b + 1, b + n + 1);
		for (int i = 1; i <= n; i++) cout << a[i] << " ";
		puts("");
		for (int i = 1; i <= n; i++) cout << b[i] << " ";
		puts("");
	}
	return 0;
}
```


---

## 作者：WsW_ (赞：0)

题目要求：  
对序列 $a$ 和序列 $b$ 进行某种排列，使得所有 $a'_i+b'_i$ 互不相同。  
因为题目中保证同一序列中没有重复元素，也就是说 $a_i\neq a_j$ ， $b_i\neq b_j$ 。  
之后再给大家普及一下初一不等式性质： 
$$\because a<b \&c<d$$
$$\therefore a+c<b+d$$  
再变成题目的要求就是  
$$\because a'_i<a'_j \&b'_k<b'_x$$
$$\therefore a'_i+a'_j<b'_k+b'_x$$  

因为题目中保证同一序列中没有重复元素，所以是取不到等号的。而要保证$a'_i<a'_j \&b'_k<b'_x$ ，排序即可，最后按顺序输出排好序的数列。  
代码：  
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[105],b[105];
int q,n;
int main(){
    scanf("%d",&q);
    while(q--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&b[i]);
        }
        sort(a+1,a+1+n);
        sort(b+1,b+1+n);
        for(int i=1;i<=n;i++){
            printf("%d ",a[i]);
        }
        puts("");
        for(int i=1;i<=n;i++){
            printf("%d ",b[i]);
        }
        puts("");
    }
    return 0;
}
```

---

## 作者：cyh_toby (赞：0)

# 题意
原题链接：[CF 1305A【Kuroni and the Gifts】](https://www.luogu.com.cn/problem/CF1305A)

给定序列 $a$ , $b$ ，保证同一序列中**没有重复元素**。求对两个序列分别进行排列变成 $a',\,b'$ 使得所有 $a'_i\,+\,b'_i$ **互不相同**。

任意输出一种解即可。

多组输入。
# 分析
原题有个提示语句：

> 可以证明一定有解

这让我们联想到，一定可以构造一组解。

考虑小的和小的加，大的和大的加。

要实现这个，我们先将两个序列排序。

随后对于相邻两位置，记 $a$ 这两个位置元素为 $x$ ， $x+c$， 记 $b$ 这两个位置元素为 $y$ , $y+d$。

由于已经进行排序，并且原序列元素互不相同，可以得到

$$c > 0 \;,\; d > 0 $$

所以

$$s_i = x+y < x+c+y+d=s_{i+1}$$

即
$$s_i≠s_{i+1}$$

即满足**和不同**的条件。

所以一种可行的解是把两个序列排序后输出。

# 源码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int n;
int a[N],b[N];
int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++)
			scanf("%d", &b[i]);
		sort(a+1, a+1+n);
		sort(b+1, b+1+n);
		for (int i = 1; i <= n; i++)
			printf("%d ", a[i]);
		printf("\n");
		for (int i = 1; i <= n; i++)
			printf("%d ", b[i]);
		printf("\n");
	}
	return 0;
}

```

---

