# Platforms

## 题目描述

In one one-dimensional world there are $ n $ platforms. Platform with index $ k $ (platforms are numbered from 1) is a segment with coordinates $ [(k-1)m,(k-1)m+l] $ , and $ l<m $ . Grasshopper Bob starts to jump along the platforms from point $ 0 $ , with each jump he moves exactly $ d $ units right. Find out the coordinate of the point, where Bob will fall down. The grasshopper falls down, if he finds himself not on the platform, but if he finds himself on the edge of the platform, he doesn't fall down.

## 样例 #1

### 输入

```
2 2 5 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
5 4 11 8
```

### 输出

```
20
```

# 题解

## 作者：封禁用户 (赞：7)

发现此题仅有两篇题解，而且两人的基本一样，但此题可以使用贪心策略来解决，我的解法有所区别，所以企鹅写下了这篇题解。   
题目传送>>[CF18B](https://www.luogu.com.cn/problem/CF18B)  
### 题意简述：  
给定 $n$ 块一定已知长度相等的板子，一青蛙从原点 $0$ 开始跳，每次跨 $d$，求最终落在板外的位置。  
### 题目分析：  
使用贪心策略从小到大枚举板子长度，每次先判断，如果青蛙落在板子前，则停跳，反之则落在板后。  
#### 额外注意需要使用 long long!  

### Code：
```cpp
#include<iostream>
using namespace std;
typedef long long ll;   //类型定义long long为ll，避免频繁使用long long时累手 
int main()
{
	ios::sync_with_stdio(0);   //关同步流，加速cin输入和cout输出 
	ll n,d,m,l,ans=0;  
	cin>>n>>d>>m>>l; 
	for(ll i=1;i<=n;i++)
	{
		if(ans<((i-1)*m))
		{
			break;
		}
		while(ans<=(i-1)*m+l)
		{
			ans=(((i-1)*m+l)/d)*d+d;
		}
	}
	cout<<ans;
	return 0;
}
```
### 评测结果（未吸氧）：  
![JieGuo](https://cdn.luogu.com.cn/upload/image_hosting/28teph8m.png)  
企鹅的题解到此结束，祝各位 OIers 进步 ++~

---

## 作者：hry2009 (赞：4)

#### [题面](https://www.luogu.com.cn/problem/CF18B)
### 题意：
一只青蛙跳板子，有 $n$ 块板子，第 $k$ 块板子在 $[(k-1)m,(k-1)m+l]$ 之间，问它在哪掉下来。

$1$ $\leqslant$ $n$ $\leqslant$ $10^6$ 

### 这道模拟就两种情况：
1. 跳不到下一块板子了；

2. 跳得到下一块板子；

对于 $1$ 我们可以直接记录答案。
 
那问题来了，$2$ 怎么处理？

####  让青蛙一直蹦直到蹦出这块板子呗。

最后再进行下一轮判断

###  _AC代码如下_ ：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,d,m,l,ans = 0;// 切记开long long; 
	scanf("%lld %lld %lld %lld",&n,&d,&m,&l);
	for(long long i = 1;i <= n;i++){
		if(ans < ((i - 1) * m)) 
        		break;//跳不上停止循环；
		while(ans <= (i - 1) * m + l) 
        		ans = (((i - 1) * m + l) / d) * d + d; // 跳得上一直跳直至出了板子；
	}
	printf("%lld \n",ans);
	return 0;
}
```


---

## 作者：CLCK (赞：2)

## ~~先吐槽一下翻译，连k是啥都没说。~~

### 题目大意

给定一根坐标轴，现有 $n$ 条线段，每根线段从 $1$ 开始编号，设线段编号为 $k$，则该线段覆盖范围为：

$$[(k - 1) \times m, (k - 1) \times m + l]$$

有一个动点从原点开始移动，每次移动 $d$ 距离，问第一个**不被**线段覆盖的点的位置在哪里？

### 解法

看懂了题目，代码就很简单了，模拟一下，如果**上一线段**右端点和**该线段**左端点（之间就不是覆盖部分）不在一次移动范围内，那么这次移动的落点就是答案。

记得开 long long（~~不告诉你我这个卡了2次~~）

代码如下：

```cpp
#include <iostream>
using namespace std;
long long n, m, d, l;
int main() {
    cin >> n >> d >> m >> l;
    long long a = 0, b = 0;
    for (long long i = 1; i <= n; i++) {
        a = (i - 1) * m + l, b = i * m - 1;
        if (a / d != b / d) break;
    }
    cout << (a / d + 1) * d << endl;
    return 0;
}
```

#### 完结撒花～

---

## 作者：ImposterAnYu (赞：1)

# 0.自认为很简洁的题意
给你四个正整数 $n,d,m,l$，求最小的正整数 $x$，使得 $d\mid x$ 的同时，$x \mod m > l$ 或者 $x > (n - 1)m  + l$。

其中，$1 \leq n,d,m,l \leq 10^6$，且 $l < m$。

# 1.思路
因为我太菜了，第一个想到的思路就是枚举。：枚举每个满足 $d \mid x$ 的 $x$，同时判断 $x \mod m \leq l$ 和 $x > (n - 1)m + l$ 是否有一者成立。

但是，当 $l = m - 1$ 时，我们的代码就很有可能被卡到 $O(nm)$。不过这时，最后的答案显而易见，就是 $d(\left\lfloor\frac{(n - 1)m  + l}{d}\right\rfloor + 1)$。因为当 $l = m - 1$ 时，不可能存在 $x$ 使得 $x \mod m > l$ ，所以答案一定是使得 $d\mid x$ 和 $x > (n - 1)m  + l$ 同时成立的最小的 $x$。

加了这个特判之后，我们的代码就能跑得飞快的啦！

# 2.坑点
因为 $n,m,l \leq 10^6$，所以 $x$ 最大能到 $(10^6 - 1) \times 10^6 + (10^6 - 1) = 10^{12} - 1$，所以一定要开 `long long`！！！

# 3.AC code
```c++
#include<bits/stdc++.h>
#define int1 long long
using namespace std;
int1 i,d,m,l,maxn;
int1 read(){//快读。 
	int1 x = 0,f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-'){
			f = -1;
		}
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + ch - '0';
		ch = getchar();
	}
	return x * f;
}
void print(int1 x){//快写。 
  	if(x < 0){
    	putchar('-');
    	x = -x;
  	}
  	if(x > 9){
    	print(x / 10);
  	}
  	putchar(x % 10 + 48);
  	return ;
}
int main(){
  	maxn = read() - 1,d = read(),m = read(),l = read(),maxn *= m,maxn += l;//maxn = (n - 1) * m + l。 
  	if(l == m - 1){//特判。 
	  	print((maxn / d + 1) * d);
	  	return 0;
	}
  	for(i = d; i % m <= l && i <= maxn; i += d);//暴力枚举。 
  	print(i);
  	return 0;
}
```

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF18B)

# 分析

### 题目翻译：

在一坐标轴上给出 $n$ 块板子，第 $k$ 个板子所占的空间为$[(k-1)\times m,(k-1)\times m+l]$ $(l<m)$，一个青蛙从原点 $0$ 起跳，每次跳 $d$ 距离，问最后青蛙会落在哪里?（没落在板子上就结束跳跃）

### 数据范围:

$1\le n,d,m,l\le 10^6$

----

既然这道题的数据范围比较小，那么我们就可以用模拟来做呀。

假设目前青蛙在第 $x$ 个板子上，坐标为 $h$ 那么做以下操作：

$1.$ 若 $h$ 仍然在 $[(x-1)\times m,(x-1)\times m+l]$ 区间内，那么继续操作。

$2.$ 若 $(x-1)\times m+l<h$ 那么 $h+d$。

$3.$ 若 $x\times m>h>(x-1)\times m+l$ 也就是说青蛙此时处于两块板之间，输出即可。

**注意！！！**

由于 $1\le n,d,m,l\le 10^6$，$k\times m$ 有可能 $≥10^{12}$ 所以要用  long long 。

---

## 作者：mzyc_pzx (赞：1)

[CF18B Platforms](https://www.luogu.com.cn/problem/CF18B)
### 题意：
有 $n$ 条线段，每根从 1 开始编号，编号为 $k$，覆盖范围为  $[(k-1)\times m,(k-1)\times m+l]$  一只青蛙从原点开始，求每次移动 $d$ 求第一次不在线段上的位置。
### 分析：
模拟的思想，判断两条线段是否连接，若青蛙落点在空隙处，那么这输出这个点所在的位子即可。
### Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,d,m,l,ans1=0,ans2=0;
int main() 
{
	cin>>n>>d>>m>>l;
   for(int i=1;i<=n;i++)
	{
		ans1=(i-1)*m+l;
		ans2=i*m-1;
		if(ans1/d!=ans2/d)
		break;
   }
   cout<<(ans1/d+1)*d;
   return 0;
}
```
一句忠告：十年 OI 一场空，不开 long long 见祖宗。

---

