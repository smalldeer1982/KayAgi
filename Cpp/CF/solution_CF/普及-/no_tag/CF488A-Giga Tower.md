# Giga Tower

## 题目描述

Giga Tower is the tallest and deepest building in Cyberland. There are $ 17777777777 $ floors, numbered from $ -8888888888 $ to $ 8888888888 $ . In particular, there is floor $ 0 $ between floor $ -1 $ and floor $ 1 $ . Every day, thousands of tourists come to this place to enjoy the wonderful view.

In Cyberland, it is believed that the number "8" is a lucky number (that's why Giga Tower has $ 8888888888 $ floors above the ground), and, an integer is lucky, if and only if its decimal notation contains at least one digit "8". For example, $ 8,-180,808 $ are all lucky while $ 42,-10 $ are not. In the Giga Tower, if you write code at a floor with lucky floor number, good luck will always be with you (Well, this round is #278, also lucky, huh?).

Tourist Henry goes to the tower to seek good luck. Now he is at the floor numbered $ a $ . He wants to find the minimum positive integer $ b $ , such that, if he walks $ b $ floors higher, he will arrive at a floor with a lucky number.

## 说明/提示

For the first sample, he has to arrive at the floor numbered $ 180 $ .

For the second sample, he will arrive at $ 8 $ .

Note that $ b $ should be positive, so the answer for the third sample is $ 10 $ , not $ 0 $ .

## 样例 #1

### 输入

```
179
```

### 输出

```
1
```

## 样例 #2

### 输入

```
-1
```

### 输出

```
9
```

## 样例 #3

### 输入

```
18
```

### 输出

```
10
```

# 题解

## 作者：damage (赞：2)

# 题意

给定一个数字$a$（$-8888888888\leq{a}\leq{8888888888}$($10$个$8$)，就是输入），求最小的一个**正整数**$b$（就是输出）使得$a+b$为幸运数字。

当且仅当一个数字的各个数位中至少含有一个数字$8$时，定义它是[幸运数字]

---

# 题解

### 直接膜你

很容易发现答案只可能在$1$~$10$之间（只要个位数是$8$就可以了）。

所以只要不停```while(!check(a+b))```就行了，其中```check(a+b)```表示判断$a+b$是否为幸运数字。

时间复杂度渐进$O(1)$。

但是注意题目要求$b$是正数，所以$b\gt{0}$！也就是当原数本身就含有$8$时，答案就是$10$（只要把$b$的初始值设为$1$就行了）

### 注意$long\ long$！

---

# 代码

```cpp
#include<cstdio>
long long a,b=1; //long long，注意b的初始值为1
bool check(int x) //判断函数
{
	if(x<0) x=-x; //取绝对值，因为下面的判断x膜10时候会得到负数
	while(x)
	{
		if(x%10==8) return true; //如果上面不取绝对值就要写成(x%10==8||x%10==-8)
		x/=10; //逐位取
	}
	return false; //没有8就不是幸运数字
}
int main()
{
	scanf("%lld",&a);
	while(!check(a+b)) ++b; //不停地判断并且++b
	printf("%lld\n",b);
	return 0;
}
```

---

## 作者：伟大的王夫子 (赞：1)

根据题意，我们可以枚举$b$的大小，一个个判断$a+b$是否为幸运数。

对于判断幸运数，我们可以写一个check函数

```cpp
bool check(long long x) {
    if (x < 0) x = -x;
    while (x) {
        if (x % 10 == 8) return 1;//有一位为8
        x /= 10;//删去最后一位
    }
    return 0;
}
```

对于函数的第一行，做出解释如下：因为我们要用到取模运算，而C++无法正确对负数取模，所以便把$x$赋值为其相反数。这对该数数位上是否有8没有任何影响

观察样例，可知$b \in [1,10]$（只需加到各位为8即可）

所以时间复杂度为$O(1)$，完全不用担心超时

```cpp
#include <bits/stdc++.h>
using namespace std;
bool check(long long x) {
    if (x < 0) x = -x;
    while (x) {
        if (x % 10 == 8) return 1;
        x /= 10;
    }
    return 0;
}
int main() {
    long long a;
    cin >> a;
    int b = 1;
    while (!check(a + b)) ++b;
    cout << b;
}
```

---

## 作者：lxgw (赞：1)

### [传送门](https://www.luogu.com.cn/problem/CF488A)
## 题意
输入一个整数 a ,求出一个正整数 b 使 a+b 的各个数位中至少有一个 8.
## 思路
让 b 从1开始，每次都去判断 a+b 中是否含有 8 ，若果有就直接输出，没有就接着加1，直到找到为止。

需要注意的有以下三点：
1.  因为 a 的范围是 -8888888888 $\leq{a}\leq$ 8888888888 (10 个 8） ，所以要开 long long
2.  a+i（a+b） 要先取绝对值再判断
1.  b 是正整数，所以要从 1 开始枚举


------------

## 代码
```cpp
#include<iostream>
#include<cmath>// 包含 abs()（绝对值）函数
#define int long long
//记得开long long
using namespace std;
bool check_8(int x)//判断是否含有 8 的函数
{         
    while (x) 
    {
        if (x%10==8) //模10判断是否为8 
            return true;//如果是就返回真
        x/=10;//不断除以10判断每一位
    }
    return false;//返回假
}
signed main()
{
    int a,x;//x 用来存 a+i 的值
    cin>>a;
    for (int i=1;;i++) //从1开始枚举，判断 i(b)是否符合条件
	{
    	x=abs(a+i);//取绝对值（不然模10可能等于-8）
    	if(check_8(x))
    	{
    		cout<<i;//如果 a+i 含有8就直接输出
        	return 0;//找到了就结束程序
		}
	}
    return 0;
}

``` 
完结撒花~

拜拜 qwq

---

## 作者：tZEROちゃん (赞：1)

### Description

> 给你一个正整数 $n$，求出 $m$，要满足：$n + m$ 的各个数位至少有一个 $8$。                   
> $m$ 要尽量小。

### Solution

Python 是个好东西（

首先，输入 $n$。                  
将 $m$ 赋初值为 $1$，即从 $1$ 开始枚举。           

接着，使用 `while` 循环，将 $n + m$ 转换成字符串，即 `str(n + m)`。                      
判断在这个字符串内是否含有 $8$。

- 如果含有 $8$，退出循环，输出 $m$，结束程序。
- 如果不含有 $8$，让 $m + 1$，继续循环。


### Code

```python
n = int(input())
m = 1
while '8' not in str(n + m) :
 m += 1
print(m)
```

---

## 作者：Cult_style (赞：1)

这是一道水题，不算很难，我的做法和楼上大佬的思路不太一样，主要思路是枚举

看看我的思路吧

首先把正整数和负数分开

我们把那个数用a代替
- 如果是正整数，就从1到10(1)这十个数加上a枚举有没有数字是8，是8的话，因为要求最小，所以直接return

(1)为什么是一到十呢，让我们来模拟一下

假如那个数是15，加上3，就有数字是8

如果是11，加上7，就有数字是8

如果是28，就要加上10，变成38，就有数字是8（因为题目说要加上一个正整数，所以不能直接加零）

经过枚举，我们发现，加上的数最多是10

- 再来讲是负数的情况，虽然比正整数难，但也很简单（~~只让我郁闷了2个小时而已~~）

是负数的话，一开始我一点头绪也没有，后面想了想，唉，不管了，先把负数变成正整数再说

就比如a是 -14，看一眼就知道答案是6，如果没有-号还好办，有减号就麻烦点了

把它变成整数后（变成正整数的过程到时候再说）14要加4，就有数字是8，可是-14+4=-10，根本没有数字是8，可我突然发现，14只要-6就有数字是8，而-14+6也有数字是8，多试了几个样例后，发现都是这样，也是从1到10，只是变成减的了，但是如果是-1的话，就不是这样了1-比一大的数又变成了负数，那同理，-1~-9都是这样，我们发现-1~-8的有共同点，都是一个比一个大一，只要把9单独拿出来就行了。

下面献上代码

```
#include<bits/stdc++.h>
using namespace std;
long long a;
char s[20];
bool check(int x){
	while(x>0){
		int y=x%10;
		x/=10;
		if(y==8)return true;
	}
	return false;
}
//检查有没有数是8的
int main(){
	cin>>s;
    	//输入一串字符
	if(s[0]=='-'){
    	    //如果有减号，就不管减号
	    int cnt=1;
	    for(int i=strlen(s)-1;i>0;i--){
        	//i>0零减号就没有被计算了
	        int c=s[i]-'0';
		a+=c*cnt;
		cnt*=10;	
        	//把a变成整数
	    }
	    if(a<=8){
		int x=a;
		printf("%d",8+x);
        	//我们发现规律，x+8就是1到8的答案
		return 0;
        	//直接结束
	    }
	    if(x==9){
		printf("%d",1);
		return 0;
	    }
            //就拿出来独自判断
       	    for(int i=1;i<=10;i++){
		if(check(x-i)){
		    printf("%d",i);
		    return 0;
		}
        	//看看有没有符合条件的数
	    }
	}
    	//这里已经是判断正整数的了
	int cnt=1;
	for(int i=strlen(s)-1;i>=0;i--){
	    int c=s[i]-'0';
	    a+=c*cnt;
	    cnt*=10;	
	}
    	//把字符串变成一个数
	for(int i=1;i<=10;i++){
	    if(check(a+i)){
		printf("%d",i);
		return 0;
	    }
            //查找符合条件的数
	}
	
	return 0;
}
```
## ~~求过求赞~~



---

## 作者：Lish_Xizse (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF488A)


------------
### 分析与设计

这道题有一点复杂，我们通过两个部分来分析。

#### 设计函数部分：

我们需要设计一个函数来判断这个数字是不是幸运数字。

题目里说，**当且仅当一个数字的各个数位中至少含有一个数字八时，这样的数字叫做幸运数字。** 所以我们需要设计一个函数，判断这个数是不是幸运数字。

我们通过 ```while``` 语句来进行数位分离，判断是否有八的存在，从而实现判断幸运数字。

```
bool is_eight_x(int x){
    x=abs(x);
    while(x!=0){
        int sum=x%10;//取出最后一位；
        if(sum==8)return true;//判断最后一位是不是八；
        x/=10;删除最后一位。
    }
    return false;
}
```

#### 编写主函数部分

到了这里就比较简单了。我们已经得到了如何判断幸运数字的函数，我们可以再次使用 ```while``` 语句，不断寻找符合增加数字后幸运数字的数，然后输出这个数即可。

```
int main(){
    cin >> a;
    while(!(is_eight_x(a+b)))b++;//重复寻找加上数字后是幸运数字的数。
    cout << b << endl;
    return 0;
}
```


------------
### 完整 ```AC``` 代码:

```
#include<iostream>
#include<cmath>
using namespace std;
int a,b=1;//记得要把b的值设为1
bool is_eight_x(int x){
    x=abs(x);
    while(x!=0){
        int sum=x%10;
        if(sum==8)return true;
        x/=10;
    }
    return false;
}
int main(){
    cin >> a;
    while(!(is_eight_x(a+b)))b++;
    cout << b << endl;
    return 0;
}
```


---

## 作者：AllanPan (赞：0)

## 一、题意
题目（[传送门](https://www.luogu.com.cn/problem/CF488A)）给一个绝对值不超过十位的整数，想计算至多加几后会在和数中出现数字 $8$.
## 二、分析
看到这道题，我们最容易想到的当然是暴力枚举，但是首先需要明确这样做所需的执行工作量再开始写。注意到最坏的情况也可以在至多 $16$ 次内完成（我们看个位就会知道最坏的答案是 $16$，也即 $-8$ 到 $8$），并且输入的数据位数不超过 $10$ 位，因此暴力尝试是可行的。
## 三、代码
```cpp
#include <iostream>
using namespace std;

bool isLucky(long long n) // 判断是否“幸运”
{
	if (n < 0)
		n = -n;
	for (; n >= 1; n /= 10)
	{
		if (n % 10 == 8)
			return true;
	}
	return false;
}

int main()
{
	long long n;
	cin >> n;
	int i = 1;
	while (!isLucky(n + i))
	{
		i++;
	} // 尝试ing
	cout << i;

	return 0; // 完结撒花qwq
}
```

---

