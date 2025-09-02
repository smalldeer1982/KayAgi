# [ABC046B] AtCoDeerくんとボール色塗り

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc046/tasks/abc046_b

シカのAtCoDeerくんは一列に並んだ $ N $ 個のボールをそれぞれ $ K $ 色のペンキの色のうちのどれかで塗ろうとしています。見栄えが悪くならないように、隣り合ったボールは別の色で塗ることにします。ボールの塗り方としてあり得るものの個数を求めてください。

## 说明/提示

### 制約

- $ 1≦N≦1000 $
- $ 2≦K≦1000 $
- 答えは $ 2^{31}-1 $ 以下

### Sample Explanation 1

色を$ 0 $,$ 1 $で表すと、左のボールを$ 0 $で塗り、右のボールを$ 1 $で塗る という方法と、 左のボールを$ 1 $で塗り、右のボールを$ 0 $で塗る という方法の$ 2 $通りがあります。

### Sample Explanation 2

ボールは一つしか無いため,$ 10 $色のうちどれを使っても良いので答えは$ 10 $通りです。

## 样例 #1

### 输入

```
2 2```

### 输出

```
2```

## 样例 #2

### 输入

```
1 10```

### 输出

```
10```

## 样例 #3

### 输入

```
10 8```

### 输出

```
322828856```

# 题解

## 作者：Rulu (赞：15)

~~本文涉及小学乘法原理内容，初、高中生请在小学生的陪同下谨慎观看！~~
- - - - - 
乘法原理介绍
------------
做一件事，  

完成它需要分成n个步骤， 

做第1步有m1种不同的方法，

做第2步有m2不同的方法，

……

做第n步有mn不同的方法，

那么完成这件事共有：

#### N=m1×m2×m3×…×mn  

种不同的方法。


分析
------------
有1个球，有k种染法，   

有2个球，因为第2个球不能和第1个球颜色相同，所以有k*(k-1)种染法，也就是$\mathbf{k*(k-1)}^1$种染法，

有3个球，因为第3个球不能和第2个球颜色相同，所以有k*(k-1)* (k−1)种染法，也就是$\mathbf{k*(k-1)}^2$种染法，

有4个球，就有$\mathbf{k*(k-1)}^3$种染法,

……

以此类推，

 
有n个球，那么就有$\mathbf{k*(k-1)}^{n-1}$种染法。



代码
------------
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,k;//n个球，k种颜料
    cin>>n>>k;//输入n和k
	int ans;
	ans=k*pow(k-1,n-1);//求染法 
    cout<<ans<<endl;//输出 
    return 0;
}
```

#### 完结撒花~（疯狂暗示 QwQ



---

## 作者：Ender_NaCl (赞：4)

一道乘法原理的题目

首先科普一下什么是乘法原理：

- 做一件事，完成它需要分成 $n$ 个步骤。

- 做第一步有 $m_1$ 种不同的方法，做第二步有 $m_2$ 种不同的方法……

- 做第 $n$ 步有 $m_n$ 种不同的方法。

- 那么完成这件事共有 $N = \prod\limits_{i=1}^nm_i$ 种不同的方法。

回到题目

我们从左往右涂色（从第一个球涂到最后一个）

因为第一个球旁边的球都没有涂色，所以第一个球可以有 $k$ 种涂色方法

然而其他的球因为相邻的球都涂了色，所以其他的球的涂色方法都只有 $k - 1$ 种

根据乘法原理，把它们相乘，所以答案就是 $k \times (k - 1)^{n - 1}$

上代码

```cpp
#include <iostream>

#include <cmath>  

using namespace std;

int main()
{
	long long n,k,ans;
	cin>>n>>k;
	ans = k * pow(k - 1,n - 1); //记得把刚刚说的公式存进变量里，否则会输出科学计数法 
	cout<<ans;
	return 0; 
}
```


---

## 作者：RioBlu (赞：3)

本题明显是找规律

10 8 怎么算？

`8*7*7*7*7*7*7*7*7*7*7=322828856`

从此规律就简单多啦
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,c;
int main()
{
	cin>>a>>b;
	c=b*pow(b-1,a-1);
	cout<<c<<endl;
}
```

---

## 作者：MattL (赞：2)

[洛谷链接](https://www.luogu.com.cn/problem/AT2139) & [原题链接](https://www.luogu.com.cn/problem/AT2139)

~~这题不值橙题~~

---

**解题：**

直接用数学方法推。

首先，我们用小学就学过的乘法原理来按数据3来列式：

$$8\times 7\times 7\times 7\times 7\times 7\times 7\times 7\times 7\times 7=322828856$$

整理一下，就是：

$$8\times 7^9=答案$$

原理：

选第一个的时候：有 $k$ 种情况。

选第二个的时候：有 $k-1$ 种情况，是因为要减去前面选过的 $1$ 种情况。

以此类推，接下来的都只有 $k-1$ 种情况，直到最后一个。

所以，最终推出的数学公式就是 Ta 啦：

$$k\times (k-1)^{n-1}$$

而算次方不用手写，有函数 ```pow``` 来计算。用法：

```cpp
pow(n,k)// n 的 k 次方
```

接下来就可以写代码啦。

---

**代码：**


```cpp
#include <bits/stdc++.h>
using namespace std;
long long n,k;
int main() {
    cin>>n>>k;
    k=k*pow(k-1,n-1);
    cout<<k;
    return 0;
}

```


---

## 作者：Otue (赞：1)

### 题意
你要把 $N$ 个球涂上颜料（你有 $K$ 种颜料），但是两个球不能是一样颜色的。问有多少种涂色方法？
### 思路

首先来考虑第一个球，因为有 $K$ 种颜料，所以第一个球有 $K$ 种涂法。

再来考虑第二个球，因为不能和第一个球颜色一样，所以有 $K-1$ 种涂法。

再来考虑第三个球，因为不能和第二个球颜色一样，所以有 $K-1$ 种涂法。

以此类推，第 $N$ 个球也有 $K-1$ 种涂法。

由乘法原理，有 $K*(m-1)^{n-1}$ 种涂法。
### 错误点
pow 是 double 类型，所以要取整。
###  附文
送上一篇文章：[排列组合](https://baike.baidu.com/item/%E6%8E%92%E5%88%97%E7%BB%84%E5%90%88/706498)。

已修正。

---

## 作者：gi_A (赞：0)

考虑从左到右依次进行涂色，每个球只需保证与前一个球颜色不同即可做到不重不漏。

对于第一个球，它比较特殊——没有前一个球。因此第一个球可以取到所有 $k$ 种颜色。

后面的每一个球，原本应有 $k$ 种颜色取值，但是为了与前一个的颜色不同，因此它只能选取 $k-1$ 种颜色。（不需要在意前一个球的颜色到底是什么，因为不论前一个涂什么，当前的球都可以选另外的 $k-1$ 种）。

因此答案就为：$k\times (k-1)^{n-1}$。

再看数据范围，发现答案不会超过 $2^{31}-1$，不会爆 `int` ，$n$ 的范围也很小，可以多次运用乘法来实现乘方运算。

核心代码：

```cpp
int main()
{
	int n=read(),k=read();
	int s=k;
	for(int i=2;i<=n;i++)s=s*(k-1);
	cout<<s;
	return 0;
}
```


---

## 作者：Cambridge (赞：0)


蒟蒻又来发题解了！

~~这道题我们采用小学二年级就学过的办法~~我们先来回忆回忆：

> * 第1步假设有a1种不同方法。
> * 第2步假设有a2种不同方法。
> * 第3步假设有a3种不同方法。
> * ······
> * 第n步假设有an种不同方法。

### 则完成这件事一共有a1×a2×a3×······×an种方法。

上面就是所谓的乘法原理，那我们再来分析分析这道题目：

> * 第1步有k种染法，毋庸置疑。
> * 因为相邻的不能相同，第2步有k×(k-1)种染法。
> * 因为相邻的不能相同，第3步有k×(k-1)×(k-1)种染法。
> * ······

### 类推，则第n步有k乘(k-1)的n-1次方的染法。

知道思路，代码就很简单了。具体代码如下：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>//文件头不解释
using namespace std;
long long n,k,a;
int main()
{
	cin>>n>>k;
	a=k*pow(k-1,n-1);//具体为什么看上方解释部分
	cout<<a<<endl;//记得换行
	return 0;
}
```
好了，本蒟蒻就讲到这里，希望对读者有所帮助。

---

## 作者：梦游的小雪球 (赞：0)

### 梦雪的思路：
- 首先题目要求每相邻的2个球不能一样，那么我们只需要把后一个球的可能性-1（前一个球的颜色）即可。

- 设有n种颜色，那么第一个球的颜色就有n种可能（因为他的前面没有球），第2个有n-1种可能性，第3个有n-1种可能性，以此类推。

### AC代码：

```
#include<bits/stdc++.h>
using namespace std;
long long a,b,s;
int main(){
	cin>>a>>b;
	s=b;//第一个球的颜色就有b种可能
	a--;//还剩下a-1个球
	while(a--)
		s=s*(b-1);//累乘
	cout<<s<<endl;//毕竟是AT，换行还是要的
	return 0;
}
```


---

## 作者：happybob (赞：0)

# 前埔芝士

本题要涉及到乘法原理

对于n个球，k种颜色，可以得出第一个球可以是k种，其余每个k - 1种

![https://cdn.luogu.com.cn/upload/image_hosting/0p7vso7g.png?x-oss-process=image/resize,m_lfit,h_170,w_225](https://cdn.luogu.com.cn/upload/image_hosting/0p7vso7g.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

因此可得

 _ans = $k$ * $k - 1 ^ {n - 1}$_ 
 
 代码：
 
 ```cpp
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    long long n, k;
    cin >> n >> k;
    long long ans = k * pow(k - 1, n - 1);//注意转为long long
    cout << ans << endl;
    return 0;
}
```


---

## 作者：LiveZoom (赞：0)

# 题解 AT2139 【[ABC046B] AtCoDeerくんとボール色塗り / Painting Balls with AtCoDeer】

本题一看求种数就像是乘法原理。

## 前铺知识—乘法原理
有一件事，有$n$个分支，第$i$个分支有$a_{i}$种决策，那么有：
$$\prod_{i=1}^{n}{a_{i}}$$
种安排方式。

## Solution
那么第$1$个球，有$k$种决策。  
第$2$个球因为不能喝第$1$个球相同，所以有$k-1$种决策。  
第$3$球也有$k-1$种。  
以此类推，再将所有乘起来，共有：$k(k-1)^{n-1}$种可能

## Code
没什么说的，套公式就行了：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, m;
int main() {
	cin >> n >> m;
	int ans = m * pow(m - 1, n - 1);
	cout << ans << endl;
    return 0;
}
```

# The end
代码这么短，就不用Ctrl+C了吧......

求通过

---

## 作者：Egg_eating_master (赞：0)

## 数学严谨推导~

首先，第一个球肯定是什么颜色都能涂的，因为我们涂第一个球是，它并没有受到任何的限制。$k$种方法。

第二个球本来是一样有$k$种方法的，可由于它不能和第一个球涂同样的颜色，所以就有$k-1$种方法。

第三个球不能和第二个球涂相同的颜色，所以也有$k-1$种方法。

$\cdots\cdots$

因此，除了第一个球之外，剩下$n-1$个球都有$k-1$种方法。

所以，根据乘法原理，共有 $k\times (k-1)^{n-1}$ 种方法（别告诉我你不会乘法原理）。

代码就直接上啦~
```
#include<bits/stdc++.h>
#define ll long long//宏定义
using namespace std;
ll n,k;
ll ans;
int main(){
    cin>>n>>k;
    ans=k*pow(k-1,n-1);//按照推出的公式直接得出答案
    cout<<ans<<endl;//AT不换行，爆零两行泪！
    return 0;//happy ending~
}

---

