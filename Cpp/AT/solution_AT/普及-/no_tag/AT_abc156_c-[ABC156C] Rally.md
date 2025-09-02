# [ABC156C] Rally

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc156/tasks/abc156_c

数直線上に $ N $ 人の人が住んでいます。

$ i $ 番目の人が住んでいるのは座標 $ X_i $ です。

あなたは $ N $ 人全員が参加する集会を開くことを考えています。

集会は数直線上の任意の **整数値の座標** で開くことができ、座標 $ P $ で集会を開くとき、$ i $ 番目の人は集会に参加するために $ (X_i\ -\ P)^2 $ の体力を消費します。

$ N $ 人が消費する体力の総和としてありえる値の最小値を求めてください。

## 说明/提示

### 制約

- 入力は全て整数である。
- $ 1\ \leq\ N\ \leq\ 100 $
- $ 1\ \leq\ X_i\ \leq\ 100 $

### Sample Explanation 1

座標 $ 2 $ で集会を開くとき、$ 1 $ 番目の人が消費する体力は $ (1\ -\ 2)^2\ =\ 1 $、 $ 2 $ 番目の人が消費する体力は $ (4\ -\ 2)^2\ =\ 4 $、よってその総和は $ 5 $ です。 これが $ 2 $ 人が消費する体力の総和としてありえる値の最小値です。 集会を開くことができるのは整数値の座標だけであることに注意してください。

## 样例 #1

### 输入

```
2
1 4```

### 输出

```
5```

## 样例 #2

### 输入

```
7
14 14 2 13 56 2 37```

### 输出

```
2354```

# 题解

## 作者：Ender_NaCl (赞：2)

这题因为 $n \le 100$ 可以直接枚举。

思路：先在输入的 $a_i$ 的范围内查找（枚举）点 $p$，再求出距离 $(a_i \times  p)^2$ 并相加，最后与之前的答案比较一下取最小值就行了。

上代码：

```cpp
#include <iostream>

using namespace std;

int a[110];

int dis(int x,int y) 
{
	return (x - y) * (x - y); //按照题意求距离 
}

int main()
{
	int n,i,j,ans = 1000000000,minn = 1000000000,maxn = -1000000000;
	cin>>n;
	for(i = 1;i <= n;i++)
	{
		cin>>a[i];
		maxn = max(maxn,a[i]); //a[i]中最大值 
		minn = min(minn,a[i]); //a[i]中最小值 
	}
	for(i = minn;i <= maxn;i++) //从最小值到最大值之间查找 
	{
		int sum = 0;
		for(j = 1;j <= n;j++) sum+=dis(a[j],i); //距离求和 
		ans = min(sum,ans); //比较大小 
	}
	cout<<ans; 
	return 0; //华丽结尾 
}
```


---

## 作者：MattL (赞：1)

[洛谷链接](https://www.luogu.com.cn/problem/AT4807) & [原题链接](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/4807)

---
题意：

有 $n$ 个人， $X_i$ 表示第 $i$ 的位置。现在假设有一个点 $P$ ，第 $i$ 个人前往点 $P$ 的费用为 $(X_i-P)^{2}$  ，总费用为所有人的费用和。现在请确定 $P$ ，使得所有人到达这个点的总费用最小。

---
做法：暴力枚举

为什么可以暴力枚举？

$\because 1 \leqslant X_i \leqslant 100$

$\therefore 1\leqslant P \leqslant 100$

---
然而暴力我们只需要两重循环：

第一重循环：枚举每一个 $P$ 的位置。

第二重循环：累加每个人到 $P$ 点的费用和。

---

时间复杂度： $O(\max X_i n)$ ，又因 $1 \leqslant n \leqslant 100$ ，所以不会超时。

---
另外介绍一个很好用的宏： ```INT_MAX```

这类宏有：

```INT_MAX``` 表示 ```int``` 类型的最大值。

```LONG_LONG_MAX``` 表示 ```long long``` 类型的最大值。

```INT_MIN``` 表示 ```int``` 类型的最小值。

```LONG_LONG_MIN``` 表示 ```long long``` 类型的最小值。

---

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[111],cnt,ans=INT_MAX;//INT_MAX 见上解释
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<102;i++)//枚举 P
	{
		cnt=0;
		for(int o=0;o<n;o++)//枚举每个人走到 P 的费用和
			cnt+=(a[o]-i)*(a[o]-i);
		ans=min(ans,cnt);//取最小值
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Keep_RAD (赞：1)

~~暴力出奇迹，枚举拿省一~~

一开始看到这一题，你一定会想：有套路！鼠标滚动......

$N$才`100`??

~~floyd都能过~~

看到大佬用的都是DP，排序，蒟蒻十分不解，叹道：

## 枚举大法好！

对于这一题，由于出题者十分良心，所以可以直接枚举点的位置，利用题目中给的公式就可以过了。

公式：`(a[i]-p)*(a[i]-p)`，次方可以直接进行成自己。

具体看代码：

代码：

```cpp
#include <bits/stdc++.h> //万能头CSP允许用！！
using namespace std;
int n,a[105],sum;
int ans=1e9; 
int main() 
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<102;i++) //枚举P的位置
	{ 
		sum=0; //sum清零重算
		for(int j=0;j<n;j++) //加上每个数的费用
		{
			sum=sum+(a[j]-i)*(a[j]-i); //计算费用和
		}
		ans=min(ans,sum); //费用是否变小
	}
	cout<<ans; 
	return 0;
}
```


---

## 作者：fanersaiwenxue (赞：0)

## Describe

有 $ N $ 个人，第 $ i $ 个人处在 $ X_i $ 的位置上。现在假设有一个点 $ P $，第 $ i $ 个人前往点 P 的费用为 $ (X_i-P)^2 $，总费用为所有人的费用和。现在请确定一个点，使得所有人到达这个点的总费用最小，输出这个最小需要的总费用。

## Idea

因为 $ 1 ≤ N ≤ 100 $，因此我们可以直接暴力枚举。

注：$ ans $ 值记得赋极大值保证输出的数为最小值。

## Working

只需要两重循环：第一层循环 $ P $ 值，第二层循环 $ X $ 值，用公式 $ (x-y)* (x-y) $ 求出两点之间距离加入 $ sum $ 中，等到 $ X $ 值枚举完后将 $ sum $ 值与 $ ans $ 值作比较得出最小值输出即可。
## Code

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;
int a[10010];
int n,ans=1e9,sum; // ans 赋极大值保证输出的数为最小值
int len(int x,int y)
{
	return (x-y)*(x-y); // 两点之间距离公式
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=101;i++) //因为 n 最大只有 100 直接循环即可
	{
		sum=0; // 每次算完 sum 值记得清零
		for(int j=1;j<=n;j++)
		{
			sum=sum+len(a[j],i); // 求出两点距离
		}
		ans=min(ans,sum); // 取最小值
	}
	cout<<ans;
	return 0;
}
```
✿✿ヽ(°▽°)ノ✿

---

## 作者：RBI_GL (赞：0)

## 题意

有 $n$ 个人，第 $i$ 个人处在 $x_i$ 的位置上。现在假设有一个点  $P$，现已知一个人到 $p$ 点的费用计算公式，确定点 $p$，使得费用最小，输出最小费用。

## 思路

由于数据范围很小，可以枚举 $p$ 点的位置，枚举范围是 $0$ 到 $102$。对于每一个 $p$，计算出总费用，每次计算最小值即可。

时间复杂度为 $O(n^2)$。

当然有比这个时间复杂度更优的做法，但对于这道题的数据范围，这个时间复杂度是可以接受的。


## $Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int a[105];
int cnt = 0;
int ans = 1e9 + 5;
int main() {
	cin >> n;
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for(int i = 0; i <= 102; i++) { //点p的位置 
		cnt = 0; 
		for(int j = 1; j <= n; j++) cnt += (a[j] - i) * (a[j] - i); //计算距离和 
		ans = min(ans, cnt);
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：thhxxx (赞：0)

# **分析**




由题意知位置的范围为 $1\leq P \leq100$，推断出最低可能的位置为1，最高可能的位置为 100，所以说只需暴力枚举可能的位置即可过。



枚举所有可能的位置，每次计算公式为 ```pow(X-P,2)```，等价于 ```(X-P)^2```。

注意：```pow``` 函数的返回值为  double 类型，因此需要强制转换为 int 类型。

# $AC$代码
```
#include <iostream>
#include <cmath>
#define INF 0x3f3f3f3f//无限大

using namespace std;

int a[110],sum,minn=INF;//因为要比小，所以先把minn设成无限大

int main()
{
    int n;
    cin>>n;
    for (int i=0;i<n;i++) cin>>a[i];
    for (int i=0;i<=100;i++)
    {
        sum=0;
        for (int j=0;j<n;j++) sum=sum+(int)pow(a[j]-i,2);//强制转换类型(int)pow(a[j]-i,2)
        minn=min(sum,minn);
    }
    cout<<minn;
    return 0;
}
```


---

## 作者：naroanah (赞：0)

不知道为什么其他人都要排序，直接暴力枚举点 $P$ 就可以啊。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
typedef long long ll;
typedef unsigned long long ull;
#define si(x) scanf("%d",&x)
int n, x[1000];
int ans = INF; //初值设大一些

int main() {
	si(n);
	for (int i = 1; i <= n; i++)
		si(x[i]);
	for (int i = 0; i <= 1000; i++) { //枚举点P位置
		int sum = 0;
		for (int j = 1; j <= n; j++) {
			sum += (x[j] - i) * (x[j] - i); //模拟
		}
		ans = min(ans, sum); //比较
	}
	cout << ans << endl; 
	return 0;
}

```


---

## 作者：wyb0412 (赞：0)

看到各位大佬用的DP，本蒟蒻十分不解。

先开一个数组a[105]，用来存储每个人的位置，再用sort排序。现在我们动一动大脑：要想使总费用最小，那么这一个点只能在**最小坐标与最大坐标之间**，如果点P在最小坐标那个人的左边，或是在最大坐标那个人的右边，肯定会使总费用更大。

所以，我们只需要在最小的与最大的之间判断就可以了。



我们再看数据：1<=x[i]<=100，也就是说最坏情况需要判断100次，是100^2级别，远不会超时，这也是我认为不理解各位大佬使用DP的原因，暴力就可以了。

直接设一个**二维for循环**，两个数i，j。i表示排序后的a[i]~a[n]之间的每一个整数点，j表示第j个人到点i所需要的费用，计算后累加到ans中，最后再与表示最小费用的minv比小，循环结束后就可以打印啦！
```cpp
for(k=1;k<=n;k++){ 
	ans+=(a[k]-i)*(a[k]-i);
	minv=min(minv,ans);
	ans=0;
}    
```


接下来，我们来看代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=0x3f3f3f;  
int a[105];
int n,i,j,k,minv=MAXN,ans;  //将minv调大，使后来对比时降下来

int main(){
	cin>>n;
	
	for(i=1;i<=n;i++)
	cin>>a[i];
	sort(a+1,a+n+1);  //输入与排序
	
	for(i=a[1];i<=a[n];i++){  //暴力枚举
		for(k=1;k<=n;k++)  
		ans+=(a[k]-i)*(a[k]-i);  //按照题目的要求，计算本次情况的总费用
		minv=min(minv,ans);  //minv与ans比小，将更小的值赋给minv
		ans=0;  //记得ans要清0，否则就好玩儿了
	}
	
	cout<<minv;  //打印输出就行了
	return 0;
}
```
行了，本文到此结束，请各位大佬交流指正。

---

## 作者：L2_sheep (赞：0)

所求是一个关于p的二次函数，进一步化简式子可以得到结论:当p等于所有点的平均值的时候，S是最小的。
p要求一定是整数，应该选择最接近平均数的整数p来计算结果。

具体代码如下：

```cpp
#include <stdio.h>


int main() 
{
	int n, a[101], s = 0, x, y, p, ans = 0, i;
	
	scanf("%d", &n);
	for(i = 0; i < n; i++){
		scanf("%d", a + i);
		s += a[i];
	}
	p = x = s / n;
	if(s % n){
		y = x + 1;
		if(y * n - s < s - x * n) p = y;
	}
	for(i = 0; i < n; i++){
		x = a[i] - p;
		ans += x * x;
	}
	printf("%d\n", ans);	
			
	return 0;
}
```


---

## 作者：leoair (赞：0)

# Rally

题目大意：给定一个$n$和一个长度为$n$的数列$x$,是的找到一个点$i$的$\sum\limits_{j=1}^n(x_j-i)^2$**所得的值最小**

首先想到枚举每一个点，记录这个点所得的值然后再取最小值。看一眼数据范围:$1 \leq n \leq 100,1 \leq x_i \leq 100$。~~(这什么数据范围啊，怎么这么水……)~~看来复杂度是没问题了，接下来看看实现。

#### Code:

```cpp
#include <bits/stdc++.h>
#define REP(i, a, b) for (long long i = a; i <= b; ++i)
#define ll long long
#define N 110
using namespace std;

ll n, ans = INT_MAX, a[N];

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

inline void init(){										//输入 
	n = read();
	REP(i, 1, n) a[i] = read();
}

inline void work(){										//操作 
	init();
	sort(a + 1, a + n + 1);								//先从小到大排序一波 
	REP(i, 1, a[n]){									//从1循环到最大的那个数的值 
		ll sum = 0;										//初始为0 
		REP(j, 1, n) sum += pow(abs(a[j] - i), 2);		//逐个枚举，求值 
		ans = min(ans, sum);							//取最小值 
	}
	printf("%lld\n", ans);								//输出 
}

int main(){
	work();
	return 0;
}
```





---

