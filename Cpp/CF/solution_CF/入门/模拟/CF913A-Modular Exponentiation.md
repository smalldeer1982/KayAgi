# Modular Exponentiation

## 题目描述

The following problem is well-known: given integers $ n $ and $ m $ , calculate

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/73fb55a49ff8c4211b34696969c8aef5090c1d6d.png), where $ 2^{n}=2·2·...·2 $ ( $ n $ factors), and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/b0d2851c9c5ab36f8f15a3eac416cac07be09dd3.png) denotes the remainder of division of $ x $ by $ y $ .

You are asked to solve the "reverse" problem. Given integers $ n $ and $ m $ , calculate

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF913A/d4dceae314a5c8428af0d75bf92415449f36c7d5.png).

## 说明/提示

In the first example, the remainder of division of 42 by $ 2^{4}=16 $ is equal to 10.

In the second example, 58 is divisible by $ 2^{1}=2 $ without remainder, and the answer is 0.

## 样例 #1

### 输入

```
4
42
```

### 输出

```
10
```

## 样例 #2

### 输入

```
1
58
```

### 输出

```
0
```

## 样例 #3

### 输入

```
98765432
23456789
```

### 输出

```
23456789
```

# 题解

## 作者：Playnext (赞：2)

这道绝对是入门题


看题目数据范围




2 ^30 = 1073741824

$ m < 10 ^ 8$ 

当$ n = 30 $时, $ m < $  2 ^ 30


所以当$ n >= 30 $ 时, 直接输出$ m $ 即可


代码：


```cpp
#include <bits/stdc++.h>
using namespace std;    //BY Playnext
#define REG register

int main () {
//    freopen ("Input.txt", "r", stdin);
//    freopen ("Output.txt", "w",stdout);
    REG int n, m;
    scanf (" %d %d", &n, &m);
    if (n >= 30)    printf ("%d\n", m);
    else    printf ("%d\n", m % (1<<n));    //1<<n 相当于 2^n
    return 0;
}
```

---

## 作者：wky32768 (赞：2)

既然没有python那就让蒟蒻我来水一发

当n太大的时候输出m，剩下的直接模拟（就是跑的比较慢，代码是短的）
```python
a=int(input())
b=int(input())
if a>30:
    print(b)
else:
    print(b%(2**a))

```

---

## 作者：return先生 (赞：0)

啊，这题没想到那么容易（居然不会超时啊）

那么，我就不客气了！

```cpp
#include<iostream>
#include<cmath>//pow要用到
using namespace std;
int main()
{
	int m,n;//定义
	cin>>n>>m;//输入
	int x=pow(2,n);//因为pow不能直接参与mod，所以把他赋值给x，再让x参与mod啦
	cout<<m%x;//直接输出
	return 0;//就这么结束了……
}
```

---

## 作者：Andysun06 (赞：0)

## 一道比较简单的题
### 很多人的3个点会RE,因为如果n>=30可以直接输出m
##### 代码奉上：
      VAR c,n,m:Qword;
    begin
      readln(n);//输入n
      read(m);//输入m
      if n<30 then//如果n>=30直接输出m
       begin
       c:=2;//c作为乘数不能是0
       n:=n-1;//要把n-1
       while n<>0 do//计算要除的数
       begin
       c:=c*2;
       n:=n-1;
       end;
       writeln(m mod c);//输出
       end
      else//否则
      writeln(m)；//如果n>=30输出m
    end.//结束  

---

## 作者：Aehnuwx (赞：0)

这道题我本来昨天晚上就写好了，提交后一直Judging。。

今天我登上来，终于好了。

看第一篇题解，感觉看不懂。。

所以，我准备写一篇简单易懂的题解（雾）。。


下面来介绍我的思路吧。


首先，我定义一个变量x为2的n次方。


再定义一个int类型的变量$ans$为$m/x$


然后，再定义一个int类型的变量$ans1$为$m - ans * x$


再输出 $ans1$即可。


$code$

```cpp
#include <cmath>
#include <cstdio>
using namespace std;
int main() {
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    long long x = pow(2, n);
    int ans = m / x;
    int ans1 = m -ans * x;
    printf("%d", ans1);
    return 0;
}
```

---

