# Game

## 题目描述

学生与教授在$n×n(1<=n<=10^{18})$的棋盘上做游戏，教授给定$n$的值，学生可以选择是先手还是后手。规则如下：

两人轮流给棋盘上的格子染色，不能将已染色的格子的周围格进行染色。这里的周围格指的是有公共边的格子，也就是说仅有公共点的格子是可以染色的。谁没有格子染谁就输。

问：若两人都以最好的方式染色（也就是尽可能使自己赢），学生应该选择先手还是后手？

## 样例 #1

### 输入

```
1
```

### 输出

```
1```

## 样例 #2

### 输入

```
2
```

### 输出

```
2```

# 题解

## 作者：ioker (赞：10)

## [题目传送门](https://www.luogu.com.cn/problem/CF630R)

## 题目大意：
两人轮流给棋盘上的格子染色，不能将已染色的格子的周围格进行染色。这里的周围格指的是有公共边的格子，也就是说仅有公共点的格子是可以染色的。谁没有格子染谁就输。

若两人都以最好的方式染色，选择先手还是后手必赢？

一行一个整数 $1$ 或 $2$，$1$ 表示学生应该选择先手，$2$ 反之。

## 分析:
分类讨论：

当 $n$ 是奇数时，先手取中点，剩下后手每取一个，就取与中点对称的点，如图($A$ 是先手，$B$ 是后手，$A$ 是中点)：

![](https://cdn.luogu.com.cn/upload/image_hosting/cjtexn7z.png)

最后后手必败。

当 $n$ 是偶数时，先手每取一点，后手选择对称的点，如图($A$ 是先手，$B$ 是后手)：

![](https://cdn.luogu.com.cn/upload/image_hosting/0r92g4z1.png)

先手必败。

所以当 $n$ 是奇数输出 $1$，$n$ 是偶数输出 $2$。

---

## 作者：Grisses (赞：7)

[题面](https://www.luogu.com.cn/problem/CF630R)

$n$ 的范围是 1 到 $10^{18}$，很明显就是思维题了。

- 对于 $n$ 是偶数的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/l6gdkjfp.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/eq0fzid2.png)

可能会是以上情况或其他的，但是 **红色圆圈的个数一定是偶数个**。即后手必胜。

- 对于 $n$ 是奇数的情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/959uffwx.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/6k2celrr.png)

可能会是以上情况或其他的，但是因为双方都是聪明的，所以 **红色圆圈的个数一定是奇数个**。即先手必胜。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  long long int n;
  int main()
  {
      cin>>n;
      cout<<(n%2==0?2:1);
      return 0;
  }
```

---

## 作者：sh7adow_ (赞：7)

### 闲话
~~这道题是可以打上骗分的tag的（雾~~

好久没写题解了，希望管理大大可以通过一下QAQ！

### 正题
这是CF中的水题了。翻了翻好像是几年前的。

用博弈论来做！

分析得到：

- 如果 $n$ 为奇数；

   - 先手第一步将棋子下在正中；
   
       - 先手都可以将棋下在与后手上一步棋关于棋盘**中心对称**的对称的位置 ~~（这里表达可能不清晰，有问题私信！（雾~~；
      
            - 最后一定是后手无棋可下，此时输出 $1$ ；

- 如果 $n$ 为偶数；

  - 那么无论先手下哪儿；
  
       - 后手都可以将棋下在与先手上一步棋关于棋盘中心对称的位置；
    
         - 最后一定是先手无棋可下，此时输出 $2$ 。
      
      
所以就这样解出来了。代码楼下都有，就不说了。

---

## 作者：Heliox (赞：4)

这道题我们第一眼看可能没有思路，对于这种题，我们可以自己列一个表格。

表格如下：

![](https://s4.ax1x.com/2022/01/26/7qxdLn.png)

由此表可得当 $n$ 为奇数时，答案是`1`，$n$ 为偶数时，答案是`2`，请注意 $10^{18}$ 数据范围。

代码如下：

```
#include <iostream>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    if (n % 2 == 1) cout << 1; // 为奇数
    else if (n % 2 == 0) cout << 2; // 为偶数
    return 0;
}
```

---

## 作者：Dream_weavers (赞：3)

## 大致题意

两人轮流对棋盘进行染色，每次染一格。若最后谁没有地方可以涂，谁败；反之，另一方胜。

题中给出棋盘的大小为 $\ n\times n\ $ 的，问是先手还是后手最后能获胜。

## 分析

首先我们知道 $\ n\ $ 和 $\ n\times n\ $ 奇偶性相同，最后染色的人获胜（~~这不废话吗~~）。

若 $\ n\ $ 为奇数，下的次数也为奇数，下第一次和最后一次的为同一人，即先手必胜。反之，若 $\ n\ $ 为偶数，则后手必胜。

分析了这么多，其实就是**判断 $\ n\ $奇偶性。** 奇数输出 1 ，偶数输出 2。

## AC代码

注意：$\ n\ $ 最多为 $\ 10^{18}\ $ ，不开 long long 见祖宗！

```cpp
#include<iostream>
using namespace std;
int main(){
    long long n;//不开longlong见祖宗
    cin>>n; //输入
    if(n%2==0)  cout<<2;//判断奇偶性，当n为偶数时
    else cout<<1;//当n为奇数时
    return 0;//完美结束
}
```

## 完


---

## 作者：DPseud (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF630R)

大家发的都是 C++，我来发一波 python 的题解。

# 思路

我们需要分类讨论：

如果 $n$ 是一个偶数，那么很显然，$n^2$ 也是偶数，因为染色格子上下左右不能染色，所以能染色的格子就是 $\frac{1}{2}n^2$，因为这也是个偶数，所以后手出必胜。

如果 $n$ 是奇数的话，那么 $n^2$ 也是奇数，而 $n^2/2$ 则是有余数的，那么先手出必然抢到余出来的格子，也就是最后一个格子，所以先手出必胜。

# 代码

```python
n=int(input())//直接input会输入字符串，你们懂的
if n%2==0:print(2)
if n%2==1:print(1)
```


---

## 作者：3a51_ (赞：1)

考虑将棋盘黑白染色。

黑白染色后我们可以得到，要么只能染完棋盘中所有白色，要么染完所有黑色。

当 $n \times n$ 为奇数时，黑格数量为奇数，白格数量为偶数。也就是说，学生只要选择先手，并染一个黑格，剩下的教授也只能染黑格，最终必为学生胜利。

同理，在 $n \times n$ 为偶数时，学生需要选择后手。

所以就判断一下 $n$ 的奇偶性即可。时间复杂度 $O(1)$。

### 代码1（仅适用于 $n \le 10^{20}$ 时）

用```long long```来存储即可，但有限制。

```cpp
#include<iostream>
using namespace std;
int main()
{
	long long x;
	cin>>x; 
	if(x%2==0)
		cout<<2;
	else
		cout<<1;
	return 0;
}
```

### 代码2（可以很大）

考虑字符串，并把最后一位提取出来单独判断。

```cpp
#include<iostream>
using namespace std;
int main()
{
	string s;
	cin>>s;
	int x=s[s.size()-1]-'0';
	if(x%2==0)
		cout<<2;
	else
		cout<<1;
	return 0;
}
```

---

## 作者：YUYGFGG (赞：1)

前面那个大佬讲得方法~~太显然~~了，蒟蒻提供一种简单一点的思路

首先我们可以发现

>不能将已染色的格子的周围格进行染色

这个限制可以忽视（手动模拟一下会发现总有替代办法）

于是可以变成一个数轴，两个人分别选数

再思考一下会发现其实就相当于挨个（1、2、3、4）选，谁选最后一个赢，另一个输

那就是判奇偶的大水题了

code:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n;
    cin>>n;
    if(n%2==0) cout<<2<<endl;
    else cout<<1<<endl;
    return 0;
}
```


---

## 作者：BlackPanda (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF630R)

------------
### 题意：
学生和教授两人轮流给 $n×n$ 棋盘上的格子染色，不能将已染色的格子的周围格进行染色。谁没有格子染谁就输。若两人都以最好的方式染色，学生应选择先手还是后手？

------------
### 思路：
我们可以将棋盘分为黑白两色，两人只能染完两种颜色其中一种。

可以分为两种情况：

- 当 $n×n$ 为奇数时（也可以说当 $n$ 为奇数时），白格数量为偶数，黑格数量为奇数，学生需要先手，染黑格，教授后面只能染黑格，学生胜。

![](https://cdn.luogu.com.cn/upload/image_hosting/abtgivq6.png)
- 当 $n×n$ 为偶数时（也可以说当 $n$ 为偶数时），白格数量和黑格数量都是偶数，学生后手赢。

![](https://cdn.luogu.com.cn/upload/image_hosting/mn4jiak5.png)

------------
### 注意：
千万不能输出多余的空格，我就被[卡](https://www.luogu.com.cn/record/67987328)了好几次。

------------
### code：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long n;
int main(){
	cin>>n;
	if(n%2==0)	cout<<2;
	else	cout<<1;
	return 0;
}


```



---

## 作者：rai1gun (赞：0)

### 一、题目思路

分两种情况讨论，第一种 $N$ 为奇数，那么它必含一个中间点，先手第一步下中心点，后边与对手下其对称的位置即可，先手升。若 $N$ 为偶数，那么找不出来中心位置，后手只需下先手的对称位置即可，后者声。

所以，只需要判断 $N$ 的奇偶性即可

### 二、题目代码

```c++
#include <iostream>
using namespace std;
typedef long long LL;
LL n;
int main(){
	cin>>n;
	if(n&1) cout<<1;
	else cout<<2;
    return 0;
}
```

---

## 作者：Pkixzx (赞：0)

这题比较简单啊。

看到这题后，我想到的第一个方法就是列个表格找规律。

可得以下数据：

1 1

2 2

3 1

4 2

5 1

6 2

………………

于是，我们得到：如果是棋盘边长为奇数个，先手；棋盘个数为偶数个，后手。

可得代码：
```
#include <bits/stdc++.h>
using namespace std; 
int main()
{
    long long n,i,j,k,m,x,y,t=0,t1=0;
    cin>>n;
    if(n%2==0)
    cout<<2;
    else
    cout<<1;
    return 0;
}
```


---

