# [ABC116C] Grand Garden

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc116/tasks/abc116_c

花壇に $ N $ 本の花が咲いており、それぞれ $ 1,2,......,N $ と番号が振られています。最初、全ての花の高さは $ 0 $ です。 数列 $ h=\{h_1,h_2,h_3,......\} $ が入力として与えられます。以下の「水やり」操作を繰り返すことで、すべての $ k(1\ \leqq\ k\ \leqq\ N) $ に対して花 $ k $ の高さを $ h_k $ にしたいです。

- 整数 $ l,r $ を指定する。$ l\ \leqq\ x\ \leqq\ r $ を満たすすべての $ x $ に対して、花 $ x $ の高さを $ 1 $ 高くする。

条件を満たすための最小の「水やり」操作の回数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leqq\ N\ \leqq\ 100 $
- $ 0\ \leqq\ h_i\ \leqq\ 100 $
- 入力はすべて整数である。

### Sample Explanation 1

「水やり」操作の回数は $ 2 $ 回が最小です。 以下が一つの例です。 - $ (l,r)=(1,3) $ の「水やり」操作を行う。 - $ (l,r)=(2,4) $ の「水やり」操作を行う。

## 样例 #1

### 输入

```
4
1 2 2 1```

### 输出

```
2```

## 样例 #2

### 输入

```
5
3 1 2 3 1```

### 输出

```
5```

## 样例 #3

### 输入

```
8
4 23 75 0 23 96 50 100```

### 输出

```
221```

# 题解

## 作者：_easy_ (赞：4)

# 思路
直接贪心，每次把答案加上两个数值的差就行了。
### 贪心证明

假设现在你在的位置有一个坑，但旁边又有一个坑，你肯定会选择把两个同时减 $1$。
那么小的坑肯定会和大的坑一起填掉，大的坑也会减少 $abs(a_i-a_{i-1})$ 的深度，所以这样贪心是对的。
# 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,a[N],ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>a[i-1]){
			ans+=a[i]-a[i-1];
		}
	}
	cout<<ans;
}
```
[AC记录](https://www.luogu.com.cn/record/58690925)

---

## 作者：Tipsy_bamboo (赞：0)

## 思路
这一题主要可以用递推的思想，下面我们来分类讨论。  
我们用 $ ans $ 数组来记录答案，$ ans_n $ 来表示让 $ h_1 $ 到 $ h_n $ 的花朵长到指定高度的浇水次数。

- 如果 $ h_n $ 小于等于 $ h_{n-1} $，则在浇 $ h_{n-1} $ 时便可以一并浇了，不需要做改变。
- 如果 $ h_n $ 大于 $ h_{n-1} $，则还需要 $ h_n - h_{n-1} $ 次才能浇完。

## 代码奉上（千万不要抄袭）
```cpp
#include<bits/stdc++.h>
using namespace std;
int h[105], ns[105];
bool pd(int n)
{
	for(int i = 1; i <= n; ++i) if(!h[i]) return true;
	return false;
}
int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", &h[i]);
	for(int i = 1; i <= n; ++i)
	{
		if(h[i] <= h[i - 1]) ns[i] = ns[i - 1];
		else ns[i] = ns[i - 1] + h[i] - h[i - 1];
	}
	printf("%d", ns[n]);
	return 0;
 } 
```

---

## 作者：gaozitao1 (赞：0)

# AT4284 [ABC116C] Grand Garden 题解
题目大意：有一个初始值为 $0$ 的序列，求最少经过多少次“区间加一”操作可以使序列变为目标序列。

首先，需要经过 $h_1$ 次操作，将第一个数变为 $h_1$。

如果 $h_2\le h_1$，那么在改变第一个数时，只要同时改变第二个数，就可以做到，不需要多余操作。

举例：$h_1=5,h_2=3$，将第一个数变为 $5$ 需要 次操作，而因为 $h_2\le h_1$，所以只需要在这五次操作中其中三次修改第一个数和第二个数，剩下两次只修改第一个数即可，一共只需要五次操作。

如果 $h_2>h_1$，那么在经过 $h_1$ 次操作之后，需要在经过至少 $h_2-h_1$ 次操作，才能满足第二个数的要求。

举例：$h_1=3,h_2=5$,将第一个数变为 $3$ 需要三次操作，而因为 $h_2>h_1$，所以这三次修改必须同时修改第一个数和第二个数，第二个数序号额外两次修改，一共需要五次操作。

综上所述，每到一个位置 $i$ 时，如果 $h_i\le h_{i-1}$，那么不需要额外操作；如果 $h_i>h_{i-1}$，那么需要增加 $h_i-h_{i-1}$ 次操作。

代码：
```cpp
#include<cstdio>
#include<iostream>
int d[100001];
int main()
{
	int a=0,i,n;
	scanf("%d",&n);
	for(i=1; i<=n; ++i)
	{
		scanf("%d",&d[i]);
		if(d[i]>d[i-1])//如果当前数比前一个数大，那么需要操作
			a+=d[i]-d[i-1];
	}
	printf("%d",a);
	return 0;
}
```

---

## 作者：Maxmilite (赞：0)

### 题意描述：

花床上有 $N$ 枝花，每次可以选定一个连续区间让这个区间里的花高度 $+1$，求至少需要多少次操作才可以让花的高度长到给定序列那样

### 4.5 倍经验：
[P3078](https://www.luogu.com.cn/problem/P3078) 完全一致

[P1969](https://www.luogu.com.cn/problem/P1969) 完全一致

[P5019](https://www.luogu.com.cn/problem/P5019) 完全一致

[AT4284(本题)](https://www.luogu.com.cn/problem/AT4284) 完全一致

[CF448C](https://www.luogu.com.cn/problem/CF448C) 极其相似

### 解法

核心要点：**贪，都可以贪**

贪心做法，从前往后遍历，每当找到一个 $h_{i} > h_{i - 1}$ 操作次数就加上 $h_{i} -  h_{i - 1}$

### 为什么这样解

可以理解为当找到一个高点 （即 $h_{i} > h_{i - 1}$），那就可以顺便把他后面递减的区间一起干掉。由于区间保证递减  （即 $h_{i} \leq h_{i - 1}$），所以可以保证像金字塔那样，每次操作的区间都是连续的。

![](https://cdn.luogu.com.cn/upload/image_hosting/mrao9sgg.png)

（黑色框表示每个点需求的高度，红色框表示操作顺序）

如果遇到操作区间内（即 $h_{i} > h_{i - 1}$），那么就会出现这种状况

![](https://cdn.luogu.com.cn/upload/image_hosting/lduf0pdh.png)

（断档了）

### AC Code:

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    long long n, a, last(0), ans(0);
    cin >> n;
    for (long long i = 1; i <= n; ++i)
    {
        cin >> a;
        ans += a > last ? (a - last) : 0;
        last = a;
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：PushyTao (赞：0)

这道题是个思维题，看了一些大佬的题解，方法有很多，我感觉我采用的方法是比较容易理解的，当后面的那个数，小于前面的那个数的时候，就将这个差值记录在ans中，最后将答案输出
代码也很简单
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+7;
const ll inf=1e15;
const int mod=1e9+7;
ll num[maxn];
ll ans;
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>num[i];
    for(int i=1;i<=n;i++)
        if(num[i-1]<num[i])
            ans+=num[i]-num[i-1];
    cout<<ans<<endl;
    return 0;
}

```


---

## 作者：wmy_goes_to_thu (赞：0)

话说这是 NOIP2018T1……

这道题肯定是贪心呀，每次选择最小点，都减一下这个值，分成若干个子区间进行处理。

代码：
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int a[100005];
int go(int l,int r)
{
	if(l<1||r<1)return 0;
	if(l>r)return 0;
	if(l==r)return a[l];
	int m=1111111111,w=0;
	for(int i=l;i<=r;i++)
		if(a[i]<m)
		{
			m=a[i];
			w=i;
		}
	int j=a[w];
	for(int i=l;i<=r;i++)
		a[i]-=j;
	int lf=go(l,w-1);
	int rg=go(w+1,r);
	return j+lf+rg;
}
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	int ans=go(1,n);
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：leoair (赞：0)

# Grand Garden

题目大意:有$n$朵花，第$i$朵花最后的高度必须为$h_i$。每一次操作能让$1$个连续的区间的花的高度增加$1$。

这道题其实就只要求$\sum\limits_{i=1}^{n}if(h_i>h_{i-1}) h_i-h_{i-1}$(等同于``` for (long long i = 1; i <= n; ++i) if(h[i] > h[i - 1]) ans += h[i] - h[i - 1]``` )。

接下来看看实现:

### Code:

```cpp
#include <bits/stdc++.h>
#define REP(i, a, b) for (long long i = a; i <= b; ++i)
#define ll long long
#define N 110
using namespace std;

ll n, ans, a[N];

inline ll read(){										//快读 
	ll s = 0, w = 1;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		if (ch == '-') w *= -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}

int main(){
	n = read();											//有n朵花 
	REP(i, 1, n) a[i] = read();							//最后要求第i朵花的高度 
	REP(i, 1, n)
		if (a[i - 1] < a[i]) ans += a[i] - a[i - 1];	//如果这朵花比前1朵花的矮那就加上这2朵的高度之差 
	printf("%lld\n", ans);
	return 0;
}
```





---

