# Table Decorations

## 题目描述

您正在为宴会装饰桌子，有 $r$ 个红色，$g$ 个绿色和 $b$ 蓝色的气球，一张桌子需要三个颜色不完全相同的气球来装饰。

您需要求出可以用所需方式进行装饰的桌子的最大数量 $t$。

## 样例 #1

### 输入

```
5 4 3
```

### 输出

```
4
```

## 样例 #2

### 输入

```
1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
2 3 3
```

### 输出

```
2
```

# 题解

## 作者：shiroi (赞：5)

一道贪心题。

观察题目可以发现，当数量最大的气球数量的一半小于另外两种颜色气球的数量之和，可以组成全部颜色数量之和的三分之一。否则全部组成都是 $2:1$ 的方案。

压行之后代码相当短。

```cpp
#include <bits/stdc++.h>
using namespace std;

inline long long read()
{
	long long x=0; long long f=1; char ch=getchar();
	while(!isdigit(ch)) {if(ch=='-')f=-1; ch=getchar();}
	while(isdigit(ch)) {x=x*10+ch-'0'; ch=getchar();}
	return x*f;
}

int main(int argc, char const *argv[])
{
	long long r=read(),g=read(),b=read();
	printf("%lld\n",min(min(min((r+g+b)/3,r+g),r+b),b+g));
	return 0;
}
```

---

## 作者：qzhwmjb (赞：4)

### 思路：
---
三种颜色不同的气球装饰桌子，每桌三个气球。  
那么气球总数除以3，就是可以满足的桌数了。  
但要注意：
当 r=7,g=1,b=1是只能有两桌。  
而不是三桌。  
因为每桌的气球的颜色不能完全相同。
也就是任意两个颜色的气球相加要大于气球总数除以3。
### 全代码
---
超短8行：
```cpp
#include<Bits/stdc++.h>//防伪标记
using namespace std;
int main(){
	long long r,g,b;
	cin>>r>>g>>b;
	cout<<min(min(min((r+g+b)/3,r+g),r+b),b+g);
	return 0;
} 
```
### 注意
---
十年OJ一场空，不开longlong见祖宗

---

