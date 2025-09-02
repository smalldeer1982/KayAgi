# Quality vs Quantity

## 题目描述

$  \def\myred#1{\color{red}{\underline{\bf{#1}}}} \def\myblue#1{\color{blue}{\overline{\bf{#1}}}}  $ $ \def\RED{\myred{Red}} \def\BLUE{\myblue{Blue}} $

You are given a sequence of $ n $ non-negative integers $ a_1, a_2, \ldots, a_n $ . Initially, all the elements of the sequence are unpainted. You can paint each number $ \RED $ or $ \BLUE $ (but not both), or leave it unpainted.

For a color $ c $ , $ \text{Count}(c) $ is the number of elements in the sequence painted with that color and $ \text{Sum}(c) $ is the sum of the elements in the sequence painted with that color.

For example, if the given sequence is $ [2, 8, 6, 3, 1] $ and it is painted this way: $ [\myblue{2}, 8, \myred{6}, \myblue{3}, 1] $ (where $ 6 $ is painted red, $ 2 $ and $ 3 $ are painted blue, $ 1 $ and $ 8 $ are unpainted) then $ \text{Sum}(\RED)=6 $ , $ \text{Sum}(\BLUE)=2+3=5 $ , $ \text{Count}(\RED)=1 $ , and $ \text{Count}(\BLUE)=2 $ .

Determine if it is possible to paint the sequence so that $ \text{Sum}(\RED) > \text{Sum}(\BLUE) $ and $ \text{Count}(\RED) < \text{Count}(\BLUE) $ .

## 说明/提示

In the first test case, there is no possible way to paint the sequence. For example, if you paint the sequence this way: $ [\myblue{1},\myblue{2},\myred{3}] $ (where $ 3 $ is painted red, $ 1 $ and $ 2 $ are painted blue) then $ \text{Count}(\RED)=1 < \text{Count}(\BLUE)=2 $ , but $ \text{Sum}(\RED)=3 \ngtr \text{Sum}(\BLUE)=3 $ . So, this is not a possible way to paint the sequence.

In the second test case, a possible way to paint the sequence is described in the statement. We can see that $ \text{Sum}(\RED)=6 > \text{Sum}(\BLUE)=5 $ and $ \text{Count}(\RED)=1 < \text{Count}(\BLUE)=2 $ .

In the third test case, there is no possible way to paint the sequence. For example, if you paint the sequence this way: $ [\myred{3},\myred{5},\myblue{4}, \myblue{2}] $ (where $ 3 $ and $ 5 $ are painted red, $ 4 $ and $ 2 $ are painted blue) then $ \text{Sum}(\RED) = 8 > \text{Sum}(\BLUE) = 6 $ but $ \text{Count}(\RED) = 2 \nless \text{Count}(\BLUE) = 2 $ . So, this is not a possible way to paint the sequence.

In the fourth test case, it can be proven that there is no possible way to paint the sequence satisfying sum and count constraints.

## 样例 #1

### 输入

```
4
3
1 2 3
5
2 8 6 3 1
4
3 5 4 2
5
1000000000 1000000000 1000000000 1000000000 1000000000```

### 输出

```
NO
YES
NO
NO```

# 题解

## 作者：Night_sea_64 (赞：3)

很简单的一道题。本蒟蒻来水一发题解。

[题目](https://www.luogu.com.cn/problem/CF1646B)

知识点是贪心。

肯定得把大的给红色，小的给蓝色。这样我们把数组降序排个序，前面的给红色，后面的给蓝色。

可是这里有个坑，可以不涂色！！！

本蒟蒻在这里被坑了，一直不知道为啥。直到看了题解才恍然大悟……

我们只让红色个数比蓝色少一个就行。所以如果 $n$ 是偶数，那么在 $a_{n\div2}$ 的地方不涂色就行了。因为红色要涂 $n\div2-1$ 个，所以 $a_{n\div2}$ 前面都是涂红色。

$n$ 是奇数的话，红色要涂 $(n-1)\div2$ 个，也就是 $\left\lfloor{n\div2}\right\rfloor$ 个。为了和偶数统一，写成 $\left\lceil{n\div2}\right\rceil-1$ 个。

AC 代码如下：

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int a[200010];
bool cmp(int x,int y){return x>y;}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)cin>>a[i];
        sort(a+1,a+n+1,cmp);
        long long r=0,b=0;
        for(int i=1;i<=n;i++)
        {
            if(i<=ceil(n/2.0)-1)r+=a[i];
            else if(i*2==n)continue;
            else b+=a[i];
        }
        if(r>b)cout<<"yes"<<endl;
        else cout<<"no"<<endl;
    }
    return 0;
}
```


---

## 作者：0xFF (赞：2)

#### 题目大意


------------
给定一个长度为 $n$ 的序列 $a$，序列中的每一个数可以被染成红色或蓝色或者不染色，问能否构造出一种方案使得红色的数量小于蓝色的数量并且红色数之和大于蓝色数之和。

#### 思路分析


------------
最有可能构造出来的状态就是红色的数量只比蓝色的数量少一，也就是说一开始先将序列排好序，将最小的两个染成蓝色，最大的一个染成红色，然后判断是否满足题意，若不满足就将第三小的染成蓝色，第二大的染成红色，继续进行上述流程直到满足题设的要求，若找完了都不能构造出合法方案的话直接输出 ```NO``` 即可。

#### 代码实现


------------
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#define int long long
using namespace std;
const int N = 2e5 + 10;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}
int T,n;
int a[N],pre[N];
signed main(){
	T = read();
	while(T--){
		n = read();
		bool flag = 0;
		for(int i=1;i<=n;i++){
			a[i] = read();
		}
		sort(a+1,a+n+1);
		for(int i=1;i<=n;i++){
			pre[i] = pre[i-1] + a[i];
		}
		for(int j=2;j <= n;j ++){
			if(pre[j] < pre[n] - pre[n - j + 1]){
				printf("YES\n");
				flag = 1;
				break;
			}
		}
		if(flag == 0) printf("NO\n");
	}
	return 0;
}
```


---

## 作者：JZH123 (赞：0)

# 解题思路
把数组从大到小排序，前面的给红色，后面的给蓝色。

红色数量比蓝色数量少一。

如果 n 是偶数 $\verb!(n % i == 0)!$，那么在 $a[n / 2]$ 的地方不涂色。因为红色要涂 $n / 2 - 1$ 个，所以 $a[n / 2]$ 前面都是涂红色。

$n$ 如果是奇数 $\verb!(n % i == 1)!$ 的话，红色要涂 $(n - 1) / 2$ 个。统写成 $⌈n / 2 ⌉−1$ 个。（用 $\verb!ceil!$ 函数实现）

# 上代码——
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define f(i, j, k) for (int i = j; i <= k; i ++)//宏定义
const int N = 2e5 + 5;
int a[N];
bool cmp(int x, int y)//自定义排序时要用的函数
{
	return x > y;
}
signed main()
{
    int t, n;
    scanf ("%d", &t);
    while (t --)
    {
        cin >> n;
        f (i, 1, n) 
			scanf ("%d", &a[i]);
        sort(a + 1, a + 1 + n, cmp);//数组a[]从大到小排序
        int sum, sum2;
        sum = sum2 = 0;
        f (i, 1, n)
        {
            if (i <= ceil(1.0 * n / 2) - 1)
				sum += a[i];
            else if(i * 2 == n)
				continue;
            else sum2 += a[i];
        }
        sum > sum2 ? printf ("YES\n") : printf("NO\n");
    }
    return 0;
}




```

---

## 作者：liangbowen (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1646B)

[$\color{red}{see}\space \color{green}{in}\space \color{blue}{my}\space \color{purple}{blog}$](https://www.luogu.com.cn/blog/liangbowen/solution-CF1646B)

看到题解里没有用双指针往中间靠的写法的，果断来一发。

思路上是**贪心**，贪心原则如下。

+ 任何时候保证蓝色元素比红色元素数量多。

+ 每次给剩余的最小元素涂蓝色，给最大元素涂红色。

+ 如果此时红元素的和大于蓝元素的和，说明可以成立。

+ 如果所有元素都被涂上色了，但还没有成立，说明无法构造。

有了这个思路就很容易了，我们先给数据**排序**。

```cpp
sort(a+1, a+n+1);
```

然后创建双指针，注意和需要使用 `long long`。

```cpp
int L = 1; long long sumL = a[1];    //左指针初始化，对应蓝色。 
int R = n+1; long long sumR = 0;     //右指针初始化，对应红色。
```

接下来两个指针不断朝中靠拢即可。

```cpp
while (L < R) //注意此处是小于不是小于等于。
{
	if (sumR > sumL) return true;
	sumL += a[++L];   //等价于 L++, sumL += a[L];
	sumR += a[--R];   //等价于 R++, sumR += a[R];
}
return false; 
```

把几段代码整理一下即可。

## 完整代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define LL long long
using namespace std;
int a[200005];
bool solve()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a+1, a+n+1);
	int L = 1; LL sumL = a[1];  //左指针初始化，对应蓝色。 
	int R = n+1; LL sumR = 0;     //右指针初始化，对应红色。
	while (L < R) //注意此处是小于不是小于等于。
	{
		if (sumR > sumL) return true;
		sumL += a[++L];
		sumR += a[--R];
	}
	return false; 
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		if (solve()) puts("YES");
		else puts("NO");
	}
	return 0;
}
```

---

## 作者：崔化博 (赞：0)

题目的意思其实就是**对于每一个数列，每一个数可以是蓝的也可以是红的，也可以不选，然后规定红的数量必须小于蓝的数量，且把红的所有数字和加起来要大于蓝的数字加起来。然后问有没有这种方案。**

### 思路
贪心。我们先试试蓝的选 2 个最小的，红的选 1 个最大的。然后依次加，变成
3 4 5 6 ....个最小的，以及红的 2 3 4 5 .....个最大的，然后看和能否超过就好了。

### 代码
```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define int long long 
using namespace std;
int t,n,a[2*1000000+2];
signed main(){
	std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(register int i=1;i<=n;++i){
			cin>>a[i];
		}
		unsigned long long sum1=0,sum2;
		sort(a+1,a+n+1);
		sum2=a[1];
		for(int i=2,j=n;i<=n/2+1;++i,--j){
			sum2+=a[i];
			sum1+=a[j];
			if(sum1>sum2)
				break;
		}
		if(sum1>sum2)
			cout<<"YES";
		else
			cout<<"NO";
		cout<<endl;
	}
	return 0;
} 

---

## 作者：沉石鱼惊旋 (赞：0)

### 题目翻译

我们对于 $n$ 个数 $a_1,a_2,...,a_n$，每个数可以选择标记为 `Red` 或 `Blue`。

对于颜色 $c$，`Count(c)` 表示颜色 $c$ 出现几次。

对于颜色 $c$，`Sum(c)` 表示标记为颜色 $c$ 的数字总和。
 
问是否存在 `Sum(Red)` $>$ `Sum(Blue)` 且  `Count(Red)` $<$  `Count(Blue)`

### 题目思路

个人认为像贪心。

我们尽量让多的个数和少的个数差距缩小，最好为 $1$，再让多的个数全选小的，少的个数全选大的，最大程度缩小差距。

### 题目代码

```cpp
void solve()
{
	int n;
	cin>>n;
	ll a[n+5];
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+n+1);//排序，更好区分大小
	ll l=2,r=n,sl=a[1]+a[2],sr=a[n];//默认多的有两个，少的有一个，小的和默认为两个最小的，大的和默认两个最大的
	bool f=0;//记录是否实现
	if(sr>sl)//默认状态就实现，去输出
	{
		f=1;
		goto check;
	}
	while(l+2<r)//每次左右都移一次，所以这里是+2
	{
		l++;
		r--;
		sl+=a[l];
		sr+=a[r];
		if(sr>sl)//判断
		{
			f=1;
			break;
		}
	}
	check:;
	if(f==1)cout<<"YES"<<endl;
	else cout<<"NO"<<endl;
}
```



---

## 作者：_Fatalis_ (赞：0)

### Solution

贪心。想要 $R$ 和大于 $B$ 和，而且 $R$ 数量还得更少，那么只能让 $R$ 中的元素远远大于 $B$ 中元素。

那么排一遍升序，从左到右选，左边选 $x$ 个数当做 $B$，右边选择 $(x+1)$ 个数当做 $R$，如果扫完全序列都不能满足，那必然是 `nO` 了。

单次 $O(n\log n)$，均摊总时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[1000001];

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++) cin>>a[i];
        sort(a+1,a+n+1);
        long long s1=a[1]+a[2],s2=a[n];
        int i=2,j=n;
        bool flag=0;
        while(i+1<j)
        {
            if(s1<s2) {flag=1;break;}
            i++;j--;
            s1+=a[i];s2+=a[j];
        }
        if(s1<s2) flag=1;
        if(flag) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}
```

---

## 作者：ryanright (赞：0)

### Description

有一个长为 $n$ 的非负整数数列 $a$，将里面的数涂成红色 **或者** 蓝色。问是否有可能红色数的数量小于蓝色数的数量且红色数的总和大于蓝色数的总和。

### Solution

必须的，我们要把 $a$ 从小到大排序。每次我们枚举蓝色数的数量 $i$，为了使红色数的总和尽可能的大，我们令红色数的数量为 $(i-1)$，且取的就是最大的 $(i-1)$ 个数，而蓝色数取的就是最小的 $i$ 个数，一直枚举到两种颜色有交集，只要出现红色数的总和大于蓝色数的总和即 $\sum_{j=n-i+2}^na_j>\sum_{j=1}^ia_j$，输出 `YES`，若一直没有，则输出 `NO`。

单次询问时间复杂度 $O(n\log n)$。

### Code

依然要开 `long long`。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[200005];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        long long x=a[1]+a[2],y=a[n];
        bool flag=x<y;
        for(int i=3;i<n-i+2;i++)
        {
            x+=a[i];
            y+=a[n-i+2];
            if(x<y) flag=1;
            if(flag) break;
        }
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}
```

---

## 作者：Rad_Forever (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1646B)

## 题目大意

你有一个长度为 $n$ 的序列 $a$，你可以将每一个数字染成红色或者蓝色，也可以选择不染色，问是否存在至少一种方案使得染成红色的数字数量大于染成蓝色的数字数量，且染成红色的数字和小于染成蓝色的数字和。

## 思路

考虑贪心。我们先将序列 $a$ 排序。

如果我们选择将 $a_{p_1},a_{p_2},a_{p_3}\dots a_{p_k}$ 染成蓝色或者红色，其中 $1 \leq p_1 < p_2 < p_3 < \dots < p_k$。

我们假定其中有 $r$ 个被染成红色，$b=k-r$ 个被染成蓝色，$r > b$。

我们为了使得红色数字总和小于蓝色数字总和，必然要选择尽可能小的数字染成红色，那么贪心的策略就出来了，我们将 $a_{p_1},a_{p_2}\dots a_{p_r}$ 染成红色。

现在解决第二个问题，怎么确定 $r,b$，仍然是贪心。

在确定了贪心策略的情况下，要使得红色数字总和尽可能小，我们需要使得红色数字取得尽可能少，解下不等式 $r > k-r$ 变形为 $2r > k$，讨论一下奇偶性便可以得到下界。

考虑在序列 $p$ 序列中加入 $2$ 个数 $x,y$，不妨设 $x<y$。在原本染色的基础上将 $x$ 染成红色，$y$ 染成蓝色只会扩大蓝色与红色数字总和的差值，由此可以推广到整个序列。

梳理一下整个代码大致过程。

1. 将 $a$ 排序。
2. $r>n-r$，解出 $r$ 取值范围并取下界。
3. 判定是否可行。

[评测记录](https://codeforces.live/problemset/submission/1646/148309521)

---

## 作者：Toorean (赞：0)

## 题意
定义 $\operatorname{Count}(colour)$ 代表 $colour$ 的元素个数，$\operatorname{Sum}(colour)$ 代表 $colour$ 的元素和。让一个长度为 $n$ 的序列 $arr$ 中的元素染 $\text{\color{red}Red}$ 或者 $\text{\color{blue}Blue}$，当然也可以不染色。问是否存在 $\operatorname{Sum}(\text{\color{red}Red})>\operatorname{Sum}(\text{\color{blue}Blue})$ 且 $\operatorname{Count}(\text{\color{red}Red})<\operatorname{Count}(\text{\color{blue}Blue})$ 的情况？

## 思路
首先，实际上 $\text{\color{blue}Blue}$ 和 $\text{\color{red}Red}$ 是可以互换的，这一点不难发现。其次，这个问题就是在问我们是否可以使得一个子序列的和大于另外一个**不交于此子序列**的子序列的和且元素个数小于另外一个子序列。因此，我们只要提取原序列最大的几个元素的和与最小的和逐次进行比较，即可求出答案。

## AC Code
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

#define LL long long
#define MAXN int (2e5 + 10) // Datas MAX
#define INF 0x3f3f3f3f
#define max(x,y) (x > y ? x : y)
#define min(x,y) (x < y ? x : y)
#define ffor(_INDEX,l,r) for (int _INDEX = (l); _INDEX <= (r); _INDEX++)
#define _for(_INDEX,l,r,_Value) for (int _INDEX = (l); _INDEX <= (r); _INDEX += _Value)
#define rfor(_INDEX,l,r) for (int _INDEX = (l); _INDEX >= (r); _INDEX --)
#define _rfor(_INDEX,l,r, _Value) for (int _INDEX = (l); _INDEX >= (r); _INDEX -= _Value)

int t, n;
LL arr[MAXN], f[MAXN];

template <typename T> inline void read (T &x) {
    T f = 1; x = 0;
    char ch = getchar ();
    while (ch < '0' || ch > '9') {
        if (ch == '-') { f = -1; };
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar ();
    }
    x *= f;
}

template <typename T, typename ... Args> inline void read (T &t, Args&... args) {
    read(t), read(args...);
}

void solve () {
    LL sum = 0, sourcesum = 0;
    bool flag = false;
    memset (f, 0, sizeof (f));

    std::sort (arr + 1, arr + n + 1);

    ffor (i, 1, n) {   
        f[i] = f[i - 1] + arr[i];
    }
    rfor (i, n, 1) {
        sum += arr[i];
        if (n - i + 2 > n) {
            continue ;
        }
        if (sum > f[n - i + 2]) {
            flag = true;
            break ;
        }
    }

    if (flag) {
        printf ("YES\n");
    } else {
        printf ("NO\n");
    }
}

int main (void) {

    read (t);
    while (t--) {
        read (n);
        ffor (i, 1, n) {
            read (arr[i]);
        }

        solve ();
    }
    
    return 0;
}
```

---

