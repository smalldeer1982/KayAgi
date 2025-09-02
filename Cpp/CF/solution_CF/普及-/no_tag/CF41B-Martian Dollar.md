# Martian Dollar

## 题目描述

一天Vasya得到了接下来n天，在bourles 有火星元的交易的信息。 第i天每一火星元的市价（不管是买入还是卖出都一样）是a[i]. Vasya有b 火星元。 他可以执行至多一次买入一定数量的火星元并卖出的操作。 根据火星法律，对火星元的买卖必须以整数为单位。试问Vasya在过了n天后最多能得到多少火星元？

## 样例 #1

### 输入

```
2 4
3 7
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4 10
4 3 2 1
```

### 输出

```
10
```

## 样例 #3

### 输入

```
4 10
4 2 3 1
```

### 输出

```
15
```

# 题解

## 作者：fzj2007 (赞：8)

**吐槽**

看这个题提交率较少，于是写`AC`后看了眼题解，发现题解的 @[柳逸君](https://www.luogu.com.cn/user/105124) 的代码是一个 $O\left(n^2\right)$，但是明显可以优化。

好了，下面步入正轨。

--------

## 第一步 读题

简化一下，就是：

> 给定 $n$ 天火星元的市值（可以认为是买股票），然后你有 $b$ 元的火星元，你可以在某一天买进（股票）并在某一天卖出，此操作只能进行一次，请问你最后最多有多少火星元。

## 第二步，思路

思路一：即@[柳逸君](https://www.luogu.com.cn/user/105124)的思路，直接简单地枚举购进时间和卖出时间。时间复杂度 $O(n^2)$。

思路二：即本蒟蒻的思路。我们发现要使得最后收益最大就是使得卖出与买进的价钱差距尽可能大，但是如果差距相等的时候就需要特判。**所以我们可以考虑前后缀和的思路。用一个数组的第 $i$ 个位置来保存 $1-i$ 的最小值，即期望的卖出最小值。用另一个数组的第 $i$ 个位置保存 $i-n$ 的最大值。**最后来一个一个地判断。如果没看明白请看代码。

## 第三步 代码

思路一的代码我就不贴了，请直接参考@[柳逸君](https://www.luogu.com.cn/user/105124)的代码。

思路二的代码（加注释）在这里：
```
#include<bits/stdc++.h>//万能头文件，洛谷不让加太多预编译指令
using namespace std;
inline int read(){//读入优化，初级快速读入
	int ans=0,flag=1;//ans保存最后的结果，flag保存正负，1为正，0为负。由于此题没有负数，所以可以省略此步骤。
	char ch=getchar();
	while((ch>'9'||ch<'0')&&ch!='-') ch=getchar();
	if(ch=='-') flag=-1,ch=getchar();
	while(ch>='0'&&ch<='9'){
		ans=(ans<<1)+(ans<<3)+(ch^'0');//ans<<1=ans*2，ans<<3=ans*8，ans<<k=ans*2^k，即增加这一位。ch^'0'可以理解为ch-'0'。
		ch=getchar();
	}
	return ans*flag;//负号特判
}
int n,b,q[2005],h[2005],p[2005],maxn,ans;//n,b，p为读入数据，q存储前缀最小值（即购买时间），h存储后缀最大值（即卖出时间）
int main(){
	n=read(),b=read();//读入不解释
	for(int i=1;i<=n;i++) p[i]=read();
	for(int i=0;i<=n;i++) q[i]=2005;//只要初始一个比2000大的数就可以了，因为加钱上线是2000。注意：要从0开始，否则你要特判
	for(int i=1;i<=n;i++) q[i]=min(p[i],q[i-1]);//前缀最小值，不会的同学可以去百度前缀和
	for(int i=n;i>=1;i--) h[i]=max(p[i],h[i+1]);//后缀最大值，会了前缀和应该就会后缀和吧......
	for(int i=1;i<=n;i++) ans=max((b/q[i])*h[i]+b%q[i],ans);//int类型自动取整， (b/q[i])*h[i]+b%q[i]的意思是：可以买b/p[i]次，然后乘上卖出时间，最后加上剩余的钱
	printf("%d\n",ans);//输出23333
	return 0;//Good Bye!
}

```

## 第四步 宣传

如果有帮助，请点个赞，谢谢！（撰文不易，dalao勿喷！）如果发现我的讲解有bug，请及时指出！

[我的主页](https://www.luogu.com.cn/user/172370)和[博客](https://www.luogu.com.cn/blog/fzj2007/)，欢迎关注！

---

## 作者：柳逸君 (赞：6)


## 题意翻译
```cpp
      一天Vasya得到了接下来n天，在bourles 有火星元的交易的信息。 
 第i天每一火星元的市价（不管是买入还是卖出都一样）是a[i]. Vasya有b 火星元。 
他可以执行至多一次买入一定数量的火星元并卖出的操作。 根据火星法律，
对火星元的买卖必须以整数为单位;试问Vasya在过了n天后最多能得到多少火星元？
输入格式：
    第一行两个数n,b(1<=n,b<=2000) ， 第二行，n个数a[i] 1 <= a_i<= 2000，含义如题 
输出格式： 
     一行一个数，表示答案。

Translated by @Maniac丶坚果
```
```cpp
输入样例#1： 
2 4
3 7
输出样例#1： 
8
输入样例#2： 
4 10
4 3 2 1
输出样例#2： 
10
输入样例#3： 
4 10
4 2 3 1
输出样例#3： 
15
```

 本题还是很简单的；题目中要求在n天中卖出一次B币（？？）再用卖出B币的Dollar买一些B币；  
数据范围也不太大（$n<=2\times10^3$）所以我们可以简单地枚举一遍买币的日期和卖币的日期，就可以优雅~~暴力~~地完成这道题了

代码如下：
```cpp
#include <cstdio>
#include <iostream>
#include <queue>
#include <algorithm>
#define ll long long
using namespace std;
ll n,b,ans;
ll a[2010];
ll mer(int in,int out)
{
	ll bb,d;
	d=b/a[in];  bb=b%a[in];
	bb+=d*a[out]; 
	return bb;
}
int main()
{
  scanf("%lld%dll",&n,&b);
  for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
  for(int i=1;i<=n;i++)
   for(int j=i;j<=n;j++)
    ans=max(ans,mer(i,j)) ;
  cout<<ans<<endl;
return 0;
}

```


---

## 作者：Luo_gu_ykc (赞：1)

## 题目大意
你知道 $n$ 天火星市场的买卖价格，第 $i$ 天的买卖价格为 $a_i$，你有 $b$ 元钱，你可以在某天买入，再在某天卖出，求最大的收益。

## 思路

枚举买入与卖出时间，模拟买卖操作即可；

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 2005;
int n, b, a[N], ans = 0;
int main(){
	cin >> n >> b;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
	}
	for(int i = 1; i <= n; i++){ // 枚举买入日期
		int maxi = INT_MIN;
		for(int j = i; j <= n; j++){ // 枚举卖出日期
			maxi = max(maxi, a[j]); // 找最佳卖出日期
		}
		int sum = b / a[i]; // 可以买入的数量 
		int cha = maxi - a[i]; // 买入与卖出的差距 
		ans = max(ans, b + sum * cha); // 最后记得加上开始的钱数 
	}
	cout << ans; 
	return 0;
}

---

## 作者：Allanljx (赞：1)

[洛谷传送门](https://www.luogu.com.cn/problem/CF41B)

[CF传送门](http://codeforces.com/problemset/problem/41/B)
## 题意
你有 $b$ 元钱，在第 $i$ 天买入卖出需要 $a[i]$ 元钱，最多能买入或卖出各一次，问你最后最多能剩多少钱。
## 思路
暴力枚举，数据最大只有$2000$，暴力不会 $T$ 。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a[2001],ans;
signed main()
{
	int n,b;
	cin>>n>>b;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	for(int i=1;i<=n;i++)//枚举买入日期 
	{
		for(int j=i;j<=n;j++)//枚举卖出日期 
		{
			int c,d;
			d=b/a[i];//最多可以买入多少 
			c=b%a[i];//剩的钱 
			c+=d*a[j];//卖出后的钱 
			ans=max(ans,c);//取最大 
		}
	}
	cout<<ans<<endl; 
    return 0;
}
```


---

## 作者：Node_Edge (赞：0)

这题数据很小，可以直接枚举买入时间与卖出时间。

```
#include<bits/stdc++.h>
using namespace std;
int n,b,a[2005],cnt;
int main(){
	cin >> n >> b;
	for(int i=0;i<n;i++){
		cin >> a[i];
	}
	for(int i = 0; i < n; i++){ // 遍历买入时间
		int maxn=0xffffff;
		for(int j=i+1;j<n;j++){ // 遍历卖出时间
			maxn=max(maxn,a[j]); // 求最佳卖出时间
		}
		int sum = b / a[i]; // 可以买入的数量(c++自动取下整)
		int x= maxn - a[i]; // 买入-卖出
		cnt = max(ans, b+cnt* x); //更新
	}
	cout << cnt; 
	return 0;
}
```


配合 [P5662](https://www.luogu.com.cn/problem/P5662) 食用更佳，可以当个这题进阶版做。

---

