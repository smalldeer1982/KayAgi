# City Day

## 题目描述

很多年了，N市的节日是在下雨天最严重的那一天举行。新的领导者打算去打破这个传统，并准备选择一个下雨天不是那么严重的一天进行活动。领导者知道$n$天的天气预报。在第$i$天上，下$a_i$毫米的雨。

领导者知道市民们关注$x$天前以及$y$天后的天气。因此，他说假定第$d$天下雨不是那么严重在满足以下情况  
1. 满足$a_d<a_j$  
2. $j$满足$d-x \leq j<d$或者$d<j \leq d+y$ 

由于市民们只看n天，所以j同时还要满足$1 \leq j \leq n$  
请帮助领导者找到下雨不是那么严重的一天

## 说明/提示

#### 第一个样例
第3天和第8天都满足这个条件，第三天更早，所以答案是第三个。

#### 第二个样例
第三天不满足这个条件，因为$3+y=6$ 且 $a_3>a_6$。第8天是答案。请注意：$8+y=11$，然而我们没有第11天，所以无需考虑第11天。

## 样例 #1

### 输入

```
10 2 2
10 9 6 7 8 3 2 1 4 5
```

### 输出

```
3
```

## 样例 #2

### 输入

```
10 2 3
10 9 6 7 8 3 2 1 4 5
```

### 输出

```
8
```

## 样例 #3

### 输入

```
5 5 5
100000 10000 1000 100 10
```

### 输出

```
5
```

# 题解

## 作者：智子 (赞：5)

作为 Codeforces Round #576 Div.2 的A题，这道题其实并不困难。

读入之后直接枚举每一天，看这一天是否“降雨量较少”即可，找到之后直接输出。这道题需要注意的地方是，枚举时注意边界，不能超过$1$到$n$的范围

代码如下：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 1000000 + 5;

int a[MAXN];

int main() {
	int n, x, y;
	
	cin >> n >> x >> y;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	
	for(int i = 1; i <= n; i++) {
		bool flag = true;
		for(int j = max(i - x, 1); j < i; j++) {
			if(a[i] >= a[j]) {
				flag = false;
				break;
			}
		}
		
		for(int j = i + 1; j <= min(i + y, n); j++) {
			if(a[i] >= a[j]) {
				flag = false;
				break;
			}
		}
		
		if(flag) {
			cout << i << endl;
			break;
		}
	}
	
	return 0;
}
```

---

## 作者：Retired_lvmao (赞：3)

本题的题意是:给你一个长度为 $N$ 的数列,两个参数 $X$ 和 $Y$ 求第一个满足:这个数本身小于这个数前$X$个数和这个数后$Y$个数的数,数据保证了有解而且只有一个解.

思路很简单 一波暴力枚举就能过了

直接上代码:
    
    
    #include<iostream>//头文件
    using namespace std;
    int main()
    {
	 int a[100001],n,x,y;
	 cin>>n>>x>>y;//读入
	 for(int i=1;i<=n;i++)
	 cin>>a[i];
	 for(int i=1;i<=n;i++)//枚举每一个数
	 {
		bool flag=false;
		for(int j=max(1,i-x);j<=min(n,i+y);j++)//判断枚举到的数字是否符合条件
		if(a[j]<a[i]&&i!=j)flag=true;//如果不符合条件则标记flag
		if(!flag)//如果符合条件则跳出
		{
			cout<<i<<endl;
			break;
		}
    }
    return 0;
    }
```


---

## 作者：Node_Edge (赞：0)

题目大致可简化成：维护一个有 $n$ 个元素的序列，找到第一个 $a_i$ 满足:它前面 $x$ 个元素和后面 $y$ 个元素都不小于它。

思路：遍历每一个元素，找到第一个解

注意：若 $a_i$ 前面没有 $x$ 个元素，则从第一个开始遍历，若后面没有 $y$ 个元素，则遍历到第 $n$ 个元素。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100050];
//这题读入的数据最多有十万个，可以采取快读
int read(){//快读模板
    int w=1;//判断正负
    char ch=getchar();
    while(ch>'9'|| ch<'0'){//判断正负
        if(ch=='-') w=-1;
        ch=getchar();
    }
    int num=ch-'0';
    while((ch=getchar())>='0'&&ch<='9'){//字符串转数字
        num=num*10+(ch-'0');
    }
    return num*w;//返回
}
int main(){
    int n,x,y;  
    n=read(); x=read(); y=read();//读入
    for(int i=0;i<n;i++){
        a[i]=read();//读入
    }
    for(int i=0;i<n;i++){
        bool flag=1;
        for(int j=max(i-x,0);j<=min(i+y,n-1);j++){//枚举
            if(i!=j&&a[j]<a[i]){//注意如果i==j,它们就是一个数了
                flag=0;//不符合规定
                break;
            }
        }
        if(flag){//符合规定
            cout<<i+1;//从0开始遍历i要加1
            break;//找出第一个就停止
        }
    }
    return 0;
}
```


---

## 作者：K_Madoka (赞：0)

**题目翻译**：在一个长度为$n$的数组中，找到数组中**第一个**左边$x$个数和右边$y$个数**严格**大于某一个数。

这道题做法很简单，只需要扫一遍即可，但是如果一个数的左$x$个数或者$y$个数越出这个数组的界限了，那么我们就算那些数比这个数大就行。只需要简单的枚举出来就行。

好了，上代码:
```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define fast ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
ll a[200010]={0};
using namespace std;
int main(){
	fast;
	int n,x,y,flag=0;
	cin>>n>>x>>y;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		flag=0;//用来判断这个数是否可行的flag
		int x1=max(1,i-x),x2=min(n,i+y);
        //和界限比较，x要比1大，y也要比n小。
		for(int j=x1;j<=x2;j++){//在这一段区间内
			if(i!=j){//特判不是它自己
				if(a[j]>a[i])continue;
				else{flag=1;break;}//旁边的数小于等于这个数，不满足条件。
			}
			else continue;
		}
		if(flag==0){//把满足条件的位置输出来
			cout<<i<<endl;
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：Zechariah (赞：0)

数据范围水，直接模拟  
枚举$d$，判断$d-x$到$d-1$天与$d+1$到$d+y$天的降雨量最小值$min$是否大于等于$d$天的降雨量，同时注意边界
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
#define jh(x, y) x ^= y ^= x ^= y
#define loc(x, y) (x - 1) * m + y
#define rg register
#define inl inline
#define PI 3.141592654
typedef long long ll;
const int N = 6e5 + 5, INF = 0x3f3f3f3f, mod = 998244353;
using namespace std;
namespace fast_IO {
	inl ll read() {
		rg char c;
		rg ll x = 0;
		rg bool flag = false;
		while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
		if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
		while ((c = getchar()) != ' ' && c != '\n' && c != '\r' && ~c)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if (flag)return -x; return x;
	}
	inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
	inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
	void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int a[N];

int main() {
	rg int n = fast_IO::read(), x = fast_IO::read(), y = fast_IO::read();
	for (rg int i = 1; i <= n; ++i)a[i] = fast_IO::read();
	for (rg int i = 1; i <= n; ++i) {
		rg int minn = INF;
		for (rg int j = i - 1; j > 0 && j >= i - x; --j)minn = fast_IO::min(minn, a[j]);
		for (rg int j = i + 1; j <= n && j <= i + y; ++j)minn = fast_IO::min(minn, a[j]);
		if (a[i] <= minn) {
			fast_IO::write(i);
			return 0;
		}
	}
	return 0;
}
```


---

## 作者：LJB00131 (赞：0)

**题面**：

找一个最靠前的$a[i]$,使$i$满足$a[j] < a[i](i - x \le j <i )$ 或 $(i < j \le i + y)$

考虑到$0 \le x, y \le 7$,暴力即可



```cpp
#include<bits/stdc++.h>
 
using namespace std;
 
#define N 100005
 
int n, a[N], x, y;
 
int main()
{
	scanf("%d%d%d", &n, &x, &y);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
	{
		bool flag = 1;
		for(int j = (i - 1); j >= max(1, (i - x)); j--)
			if(a[j] <= a[i]) {flag = 0; break;}
		for(int j = (i + 1); j <= min(n, (i + y)); j++)
			if(a[j] <= a[i]) {flag = 0; break;}
		if(flag)
		{
			cout << i << endl;
			return 0;
		}
	}
	return 0;
}
```

---

