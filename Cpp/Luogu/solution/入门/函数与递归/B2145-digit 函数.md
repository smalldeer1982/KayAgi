# digit 函数

## 题目描述

在程序中定义一函数 $digit(n,k)$，它能分离出整数 $n$ 从右边数第 $k$ 个数字。

## 说明/提示

$n \le 10^9$。

$k \le 10$。

## 样例 #1

### 输入

```
31859 3```

### 输出

```
8```

# 题解

## 作者：EthanC_ (赞：30)

### 思路：

用递归思想定义一个函数功能：返回数字 $ n $ 从左数起第 $ k $ 位。
### ACcode:

```cpp
#include<iostream> 
using namespace std;
long fh(int n,int k)//返回数字 n 从左数起第k位.
{
	k = k - 1;
	if(k == 0)//判断是否到达递归边界k=0
	return n % 10;
	else return fh(n / 10,k); //否则继续递归
}
int main(){
	int n,k;
	cin >> n >> k;
	cout << fh(n,k);
	return 0;
}

```


---

## 作者：vegetable_king (赞：13)

在[博客](https://yjh965.github.io/post/digit-han-shu-ti-jie/)食用更佳。

# 思路
这个题目很简单，函数内只需要这样一串代码：`return n / int(pow(10, k - 1)) % 10;`

为什么呢？

我们先看看，`n / int(pow(10, k - 1))` 是什么意思。

在 c++ 中，如果除号的两边都是整数，则这个除号就是整除。否则，就是正常的除法。例如，`3 / 4`、`3 / 4.0`、`3.0 / 4`、`3.0 / 4.0` 的结果分别是 `0`、`0.75`、`0.75`、`0.75`。

`pow(a, b)` 是一个求 $a^b$ 的函数。

在代码中，`n` 和 `int(pow(10, k - 1))` 的类型都是 `int`，所以这是一个整除运算。

$pow(10,k-1)$ 的值绝对是 $10$，$100$，$1000$ 这样的数。

你们不妨可以试验多几次，结果会发现，**`n / int(pow(10, k - 1))` 就是把 `n` 的后 `k - 1` 位砍掉！**

结果，`n` 的末位变成了原来的第 `k` 位！

`%` 这个符号，就是取一个数除以另外一个数的余数。例如，`233 % 2`、`234 % 5`、`235 % 3` 的结果分别是 `1`，`4`，`1`。

你又会发现，**取这个数除以 $10$ 的余数，不就是取这个数的末位吗？**

而在第一个环节里，末位就已经变成了第 `k` 位！

于是，我们成功的用 $O(1)$ 的时间复杂度在 `int` 的基础上求出了 `n` 的第 `k` 位！
# 代码
```cpp
#include <iostream>
#include <cmath>

using namespace std;

int digit(int n, int k){ // 其实，大可以不用写函数。
    return n / int(pow(10, k - 1)) % 10;
}
int n, k;
int main(){
    cin >> n >> k;
    cout << digit(n, k);
}
```


---

## 作者：Griseo_nya (赞：8)

在这里给出两种做法。主要区别为 $n$ 的类型。

## $n$ 作为字符串读入
### 思路
最简单的做法。将 $n$ 以字符串的形式读入，设其长度为 $len$，直接输出第 $len-k+1$ 位即可。但是默认情况下使用 STL string 和 char 数组读入字符串都会从 $0$ 开始标号，所以实际读取的是第 $len-k$ 位。

另外，代码中用到了 ```string::size()```，其返回值为该字符串的长度。
### 代码（使用 STL string 类实现）
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int k;
   string n;	
	cin>>n>>k;					//输入 n 和 k
	cout<<n[n.size()-k]<<endl;	//取出右数第 k 位
	return 0;
}
```
## $n$ 作为整数读入
### 思路
在 C++ 中，整数乘法是整除的，我们可以利用这个特性，使 $n=\dfrac{n}{10^{k-1}}$，达到舍弃最后 $k-1$ 位的效果。此时原来的右数第 $k$ 位即为现在的右数第 $1$ 位。因为取正整数 $n$ 最后一位的结果与 $n\mod 10$ 即可。结果相同，所以直接输出 $n\mod 10$ 即可。

下面是一些代码中用到的函数的介绍：

```pow(n,k)``` : 返回 $n^{k}$ 的值。返回值是 double 类型（浮点数）。在这里由于返回值是 double 类型（浮点数），所以要强制转换为 int 类型（整数）以达到整除的效果。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k;
	cin>>n>>k;				//输入 n,k
	n/=(int)(pow(10,k-1));	//舍弃最后 k-1 位
	cout<<(n%10)<<endl;		//输出最后一位
	return 0;
}
```

---

## 作者：·糯· (赞：6)

## 题目分析
此题我们只用分割数位，当计数器等于题目中要求分割的数位时，答案变量中存储的数位代表的数就是题目中要求的数位，那么答案就出来了。
## 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,ans,cnt=0;
int main(){
	cin>>n>>k;
	while(cnt!=k){
		cnt++;//当前数位下标
		ans=n%10;//记录数位
		n/=10;
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：墨忧 (赞：4)

## 题意
给定一个整数 $n$ , $k$ ,输出右边第 $k$ 位。
## 思路
将整数看做多个字符组成的字符串，用一个字符型数组存储这个字符串，使用输出右边 $k$ 位即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
char a[20];//以字符串的形式存储整数
int k,lena;//lena表示字符串的长度
int main()
{
    cin>>a>>k;
    lena=strlen(a);//strlen函数返回字符数组的长度
    cout<<a[lena-k];//输出右边第k位
    return 0;
}
```


---

## 作者：Dreamweaver (赞：4)

提供一种循环做法。

以样例为例：

```
31859 3
```
 
对于数 $n=31859$ 执行以下操作：

```
n/=10;

```
$n$ 变成了 $3185$。

再来一次。

$n$ 变成了 $318$。

此时 $n$ 的个位数即为答案。

所以,```n/=10;```这个操作相当于从右边起擦掉这个数的最后一位，我们只需要擦掉 $n$ 的后 $k-1$ 位，此时 $n$ 的个位数即为答案。

# 代码：
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
#define Orz cout<<"stO %王队% Orz"<<'\n';
int n,k;
int main()
{
	cin>>n>>k;
	for(int i=1;i<k;++i)	n/=10;
	cout<<n%10;  //输出个位数
	return 0; //好习惯
}

```


---

## 作者：Jorisy (赞：3)

~~不照顺序做题的 JY。~~

---

这是一道函数题，但我们可以把前面一个数看作一个字符串，$k$ 表示其下标。然后可以发现，$k$ 是从右往左数的下标，因此需要一个 STL 函数——`reverse()`。  
这个函数是用来翻转字符串的，通常是这么写的：
```cpp
reverse(s.begin(),s.end());
//表示翻转字符串 s
```
如果 $s$ 是 `Luogu`，那翻转后就是 `ugouL`。
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	string n;
	int k;
	cin>>n>>k;
   reverse(n.begin(),n.end());//翻转
	cout<<n[k-1];//千万要减一
	return 0;
}
```

---

这里在提供另一种方法，同样要用到一个 STL 函数（~~STL 大法好~~）——`size()`。这是求一个字符串的长度。示例：
```cpp
int l=s.size();
```
这是把变量 $l$ 设为字符串 $s$ 的长度，如果 $s$ 是 `Luogu`，那么 $l$ 就是 $5$。  
按照这个思路的代码：
```cpp
#include<bits/stdc++.h>
using namespace std;

int main()
{
	string n;
	int k;
	cin>>n>>k;
	cout<<n[n.size()-k];//如果看不懂算式可以自己算一下
	return 0;
}
```

---

