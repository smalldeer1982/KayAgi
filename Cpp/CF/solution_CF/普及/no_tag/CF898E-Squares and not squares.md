# Squares and not squares

## 题目描述

Ann and Borya have $ n $ piles with candies and $ n $ is even number. There are $ a_{i} $ candies in pile with number $ i $ .

Ann likes numbers which are square of some integer and Borya doesn't like numbers which are square of any integer. During one move guys can select some pile with candies and add one candy to it (this candy is new and doesn't belong to any other pile) or remove one candy (if there is at least one candy in this pile).

Find out minimal number of moves that is required to make exactly $ n/2 $ piles contain number of candies that is a square of some integer and exactly $ n/2 $ piles contain number of candies that is not a square of any integer.

## 说明/提示

In first example you can satisfy condition in two moves. During each move you should add one candy to second pile. After it size of second pile becomes $ 16 $ . After that Borya and Ann will have two piles with number of candies which is a square of integer (second and fourth pile) and two piles with number of candies which is not a square of any integer (first and third pile).

In second example you should add two candies to any three piles.

## 样例 #1

### 输入

```
4
12 14 30 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
0 0 0 0 0 0
```

### 输出

```
6
```

## 样例 #3

### 输入

```
6
120 110 23 34 25 45
```

### 输出

```
3
```

## 样例 #4

### 输入

```
10
121 56 78 81 45 100 1 0 54 78
```

### 输出

```
0
```

# 题解

## 作者：shiziyu111 (赞：1)

## 题目大意
给定一个长度为 $n$ 的数列 $a$，求将此数列更改成 $\frac{n}{2}$ 个平方数和 $\frac{n}{2}$ 个非平方数的最小次数。

## 分析
首先，我们需要统计出平方数和非平方数的个数。

然后，我们要求出两者中个数较高的一方，设为 $maxx$。

这时候，我们就要求出将平方数 / 非平方数转化为非平方数 / 平方数的最少次数。再选择 $maxx$ 个次数较少的数。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long n,s[200005],ns[200005],snum=0,nsnum=0;
	cin>>n;
	for(long long i=1;i<=n;i++)
	{
		long long a;
		cin>>a;
		if((long long)sqrt(a)*(long long)sqrt(a)==a)
		{
			if(a==0)
			{
				s[++snum]=2;
			}
			else
			{
				s[++snum]=1;
			}
		}
		else
		{
			ns[++nsnum]=min(a-(long long)sqrt(a)*(long long)sqrt(a),((long long)sqrt(a)+1)*((long long)sqrt(a)+1)-a);
		}
	}
	long long ans=0;
	sort(s+1,s+1+snum);
	sort(ns+1,ns+1+nsnum);
	if(snum>=nsnum)
	{
		for(long long i=1;i<=snum-n/2;i++)
		{
			ans+=s[i];
		}
	}
	else
	{
		for(long long i=1;i<=nsnum-n/2;i++)
		{
			ans+=ns[i];
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：longStone (赞：0)

# CF898E Squares and not squares 题解
## 思路
我们如果要将序列分成两部分：

### 第一部分：是完全平方数
优先让已经是完全平方数的放上去，然后根据差放与完全平方数接近的。

记录每个数与最近的完全平方数的差。

### 第二部分：不是完全平方数
在选完是完全平方数的之后，如果还有剩下的完全平方数 $+1$ 就可以变成非平方数了，因为 $0$ 和 $1$ 都是完全平方数，$0$ 特别的需要 $+2$。

剩下的直接添加即可，不需要改动。
### 一些技巧
- 可以用数组记录数字与最近平方数的差然后进行排序，完全平方数最近的平方数是它本身。
- 特别关注 $0$ 这个数字。
## 代码
```c++
#include "bits/stdc++.h"
#define ll long long
using namespace std;
struct X
{
    ll a, b;//b代表与完全平方数的差
    bool operator <(X z)
    {
        if(b == z.b)	return a < z.a;//这样，数字0会排到前面，可以减少“不是完全平方数”组的修改
        return b < z.b;
    }
}a[200005];
ll n, ans;
int main()
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 1;i <= n;i++)
    {
        cin >> a[i].a;
        a[i].b = min(pow(ceil(sqrt(a[i].a)),2) - a[i].a,a[i].a - pow(floor(sqrt(a[i].a)),2));//增加或减少取最小值
    }
    sort(a + 1,a + n + 1);//a与b捆绑排序
    for(int i = 1;i <= n / 2;i++)	ans += a[i].b;//差小的放第一组
    for(int i = n / 2 + 1;i <= n;i++)
    {
        if(a[i].b == 0)
        {
            ans++;
            if(a[i].a == 0)	ans++;//0是完全回文数，需要+2才可以变成非完全平方
        }
    }
    cout << ans;
    return 0;
}
```

---

## 作者：CountState (赞：0)

ez problem，但是决斗场被绝杀。

我们可以求出原数组中完全平方数的个数$cnt$，然后分类讨论：

1.  $cnt\leq \dfrac n 2$：

我们求出每个数需要加或者减多少才能成为完全平方数，然后排序取前 $\dfrac n 2$ 小即可。

2. $cnt\geq \dfrac n 2$：

我们求出每个数需要加或者减多少才能成为非完全平方数。

显然对于一个非负整数：

-   若其为 $0$，那么 $c_i=2$。

-   若其是非零的完全平方数，那么 $c_i=0$。

-   否则 $c_i=1$。
  
然后排序取前 $\dfrac n 2$ 小即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10;
int n,a,b[N],c[N],ans,cnt;
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a;
		if(a-floor(sqrt(a))*floor(sqrt(a))==0){
			cnt++;
			if(a==0) c[i]=2;
			else c[i]=1;
		} 
		else c[i]=0;
		b[i]=min(a-floor(sqrt(a))*floor(sqrt(a)),ceil(sqrt(a))*ceil(sqrt(a))-a);
	}
	sort(b+1,b+1+n);
	sort(c+1,c+1+n);
	if(cnt<=n/2) for(int i=1;i<=n/2;i++) ans+=b[i];
	else for(int i=1;i<=n/2;i++) ans+=c[i];
	cout<<ans;
}


```

---

## 作者：ivyjiao (赞：0)

来源：CF 决斗场。

小清新构造题，$09:38$ 秒杀。

首先我们可以想到如果每个数要变成完全平方数，它只能变成上下离它最近的完全平方数，代价为变成两者中最小的那个，设 $b_i$ 为把 $a_i$ 变成完全平方数的代价（可以为 $0$），那么有式子：

$$b_i=\min(a_i-(\lfloor\sqrt{a_i}\rfloor)^2,(\lceil\sqrt{a_i}\rceil)^2-a_i)$$

然后我们只需要把 $b$ 排序后的前 $\dfrac n 2$ 位相加就是答案了。

然而仅仅是这样是过不去样例 $2$ 的，我们发现可能初始就有 $>\dfrac n 2$ 堆糖果是完全平方数了，而题目中要求恰好 $\dfrac n 2$ 堆的糖果数是完全平方数，所以我们就把对于的初始完全平方数花费 $1$ 的代价改成非完全平方数。

然而这样还是过不去样例 $2$ 的，我们发现由于糖果数不能是负数，所以对于多余的 $0$，我们要花费 $2$ 的代价将其改成 $2$。

然后就过了。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;
int n,a[N],b[N],cnt,ans;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        int l=a[i]-pow((int)sqrt(a[i]),2);
        int r=pow((int)sqrt(a[i])+1,2)-a[i];
        b[i]=min(l,r);
        if(a[i]==0) cnt++;
    }
    ans+=max(cnt-n/2,0ll);
    sort(b+1,b+1+n);
    for(int i=1;i<=n;i++){
        if(i<=n/2) ans+=b[i];
        else if(b[i]==0) ans++;
    }
    cout<<ans;
}
```

---

