# 题目信息

# Fox Dividing Cheese

## 题目描述

两头贪心的小熊有 a，b 两块蛋糕，他们都想要大的那一块的那一块。于是狡猾的狐狸提出一个方案：让狐狸吃掉一些蛋糕，最后使得两块蛋糕大小一样。假如这块蛋糕的重量是 2 的倍数，那么狐狸可以吃掉二分之一；假如蛋糕的重量是 3 的倍数，那么狐狸可以吃掉三分之二；假如蛋糕的重量是 5 的倍数，狐狸可以吃掉五分之四。为了不让狐狸吃掉太多，熊要求以最少的次数将两块蛋糕吃的大小一样，求最小次数。

## 样例 #1

### 输入

```
15 20
```

### 输出

```
3
```

## 样例 #2

### 输入

```
14 8
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
6 6
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# Fox Dividing Cheese

## 题目描述
两头贪心的小熊有 a，b 两块蛋糕，他们都想要大的那一块。于是狡猾的狐狸提出一个方案：让狐狸吃掉一些蛋糕，最后使得两块蛋糕大小一样。假如这块蛋糕的重量是 2 的倍数，那么狐狸可以吃掉二分之一；假如蛋糕的重量是 3 的倍数，那么狐狸可以吃掉三分之二；假如蛋糕的重量是 5 的倍数，狐狸可以吃掉五分之四。为了不让狐狸吃掉太多，熊要求以最少的次数将两块蛋糕吃的大小一样，求最小次数。

## 样例 #1
### 输入
```
15 20
```
### 输出
```
3
```

## 样例 #2
### 输入
```
14 8
```
### 输出
```
-1
```

## 样例 #3
### 输入
```
6 6
```
### 输出
```
0
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路核心一致，均基于以下要点：
 - **思路**：要使两块蛋糕最终重量一样且操作次数最少，最终的重量应为两数的最大公因数（gcd）。所以先求出a、b的最大公因数c，再分别判断a/c和b/c能否仅通过除以2、3、5变为1，若能则统计操作次数，若不能则无解输出 -1。
 - **算法要点**：利用辗转相除法求最大公因数；通过循环不断判断a/c和b/c能否被2、3、5整除，能则整除并累加操作次数。
 - **解决难点**：理解通过求最大公因数确定最终目标值，并判断能否仅通过给定的除数（2、3、5）将两数变为最大公因数对应的倍数。

### 所选的题解
 - **作者：Plus_Ultra (赞：6)  星级：5星  关键亮点**：思路清晰，代码简洁明了，直接通过gcd函数求出最大公因数，然后分别对a/c和b/c进行判断和操作，逻辑连贯。
```cpp
#include <iostream>

#define LL long long

using namespace std;

LL a, b, c, k2, k3, k5, ac, bc, ans;

LL gcd(LL a, LL b)
{
	if(! b)  return a;
	return gcd(b, a % b);
}

int main()
{
	cin >> a >> b;
    
	c = gcd(a, b);
    
	ac = a / c;  bc = b / c;
    
	while(ac % 2 == 0)  k2++, ac /= 2;
	while(ac % 3 == 0)  k3++, ac /= 3;
	while(ac % 5 == 0)  k5++, ac /= 5;
    
	while(bc % 2 == 0)  k2++,bc /= 2;
	while(bc % 3 == 0)  k3++,bc /= 3;
	while(bc % 5 == 0)  k5++,bc /= 5;
    
	ans = k2 + k3 + k5;
    
	if(bc!= ac)  cout << "-1" << endl;
	else  cout << ans << endl;
    
	return 0;
}
```
 - **作者：HeCao2008 (赞：3)  星级：4星  关键亮点**：对题意理解清晰，代码简洁，利用c++自带的求gcd功能简化代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,ans;
int main(){
	cin>>a>>b;c=__gcd(a,b);
	a/=c,b/=c; 
	while(a%2==0)a/=2,ans++;
	while(a%3==0)a/=3,ans++;
	while(a%5==0)a/=5,ans++;
	if(a!=1){cout<<-1;return 0;} 
	while(b%2==0)b/=2,ans++;
	while(b%3==0)b/=3,ans++;
	while(b%5==0)b/=5,ans++;
	if(b!=1){cout<<-1;return 0;} 
	cout<<ans<<endl;  
	return 0;
}
```
 - **作者：liangbowen (赞：3)  星级：4星  关键亮点**：对思路讲解细致，通过自定义函数play来约掉因数，使代码结构更清晰，并且讲解了在主函数外结束程序的方法。
```cpp
#include <cstdio>
#include <iostream>
using namespace std;
int gcd(int x, int y)
{
	if (y == 0) return x;
	return gcd(y, x%y);
}
int cnt;
void play(int &x, int k)
{
	while (x!= 0 && x % k == 0) x /= k, cnt++;
}
void X()
{
	printf("-1");
	exit(0);
}
int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	int GCD = gcd(a, b);
	a /= GCD, b /= GCD;
	
	play(a, 2), play(a, 3), play(a, 5);
	if (a!= 1) X();
	
	play(b, 2), play(b, 3), play(b, 5);
	if (b!= 1) X();
	
	printf("%d", cnt);
	return 0;
}
```

### 最优关键思路或技巧
 - **数学思维**：通过分析得出最终目标值为两数的最大公因数，这是解决本题的关键思维。
 - **代码实现**：利用循环对数字进行整除操作并计数，简洁地实现操作次数的统计。

### 可拓展思路
此类题目属于数论相关的数学问题，类似套路是先分析出最终状态与初始状态的数学关系（如本题通过最大公因数确定最终蛋糕重量），再根据给定的操作规则判断能否达到最终状态并计算操作次数。

### 洛谷相似题目
 - [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
 - [P1072 Hankson 的趣味题](https://www.luogu.com.cn/problem/P1072)
 - [P2152 [SDOI2009]SuperGCD](https://www.luogu.com.cn/problem/P2152)

### 个人心得摘录
无

---
处理用时：63.71秒