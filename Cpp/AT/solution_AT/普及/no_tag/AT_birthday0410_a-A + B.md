# A + B

## 题目描述

> ### A + B 问题
> 
> #### 题目描述
> 
> 编写一个程序来计算两个整数 $A, B$ 的和。
> 
> 保证 $A, B, A + B$ 都能用 $32$ 位有符号整数表示。
>
> #### 输入格式
> > $A _ 1$ $B _ 1$  
> > $A _ 2$ $B _ 2$  
> > $\dots$  
> > $0$ $0$  
>
> 输入包括最多 $100$ 个测试用例。每个测试用例在一行中给出两个整数 $A$ 和 $B$，用空格分隔。
> 
> 输入以一行 $A = B = 0$ 结束，这一行不需要处理。
>
> #### 输出格式
>
> 
> 对于每个测试用例，输出 $A + B$ 的值，每个结果占一行。



一场比赛的问题 A 已经完成，现在正进入测试阶段。然而，由于疲劳的原因，不幸的是 JAPLJ 在 A + B 问题中出现了 Bug。大学生丸桥，这个比赛的负责人，提出了解决条件……

丸桥说：“你要把错误的源代码改正确，快点！”

你需要为 JAPLJ 的三个错误程序各找出一个能够击败它们的测试用例，并输出这些测试用例。

### 课题

针对 A + B 问题（见上），下面有三个用 C++ 编写的错误程序。为每个错误程序找到一个可以击败它们的测试用例。

更准确地说，对于每个错误程序，请编写一个满足 A + B 问题的描述和输入部分约束的测试用例。当将这个测试用例输入到错误程序中时，该程序将输出错误的答案。编写一个程序来输出这样的测试用例。

回答 1 的源代码:

```cpp
#include <iostream>

using namespace std;

int main()
{
  int A, B;

  while(cin >> A >> B, A+B!=0) {
    cout << A+B << endl;
  }

  return 0;
}
```

回答 2 的源代码：

```cpp
#include <iostream>

using namespace std;

int myAbs(int n)
{
  if(n < 0) return -n;
  else return n;
}

int main()
{
  int A, B;

  while(cin >> A >> B, (A|B) != 0) {
    while(myAbs(A) >= 100000) {
      if(A > 0) {
        B += 100000;
        A -= 100000;
      } else {
        B -= 100000;
        A += 100000;
      }
    }

    if(A > 0) {
      for(int i=0; i<A; ++i) {
        B++;
      }
    } else {
      for(int i=0; i<-A; ++i) {
        B--;
      }
    }

    cout << B << endl;
  }

  return 0;
}
```

回答 3 的源代码：

```cpp
#include<iostream>

using namespace std;

int C[3][32];

int main()
{
  int A, B;

  while(cin >> A >> B, A!=0 || B!=0) {
    for(int i=0; i<32; ++i) {
      C[0][i] = (A >> i) & 1;
      C[1][i] = (B >> i) & 1;
    }

    for(int i=0; i<32; ++i) {
      if(C[0][i] + C[1][i] >= 2) {
        C[C[1][i-1] & 1][i+1]++;
        C[0][i]--;
        C[1][i]--;
      }
      C[2][i] = C[0][i] + C[1][i];
    }

    int R = 0;
    for(int i=0; i<32; ++i) {
      R |= C[2][i] << i;
    }

    cout << R << endl;
  }

  return 0;
}
```

## 说明/提示

### 限制

所有输入数据满足以下限制条件：

- $1 \le t \le 3$

### 评分标准

总共有 3 个测试用例：

- 如果 $t = 1$ 的测试用例正确，将获得 **33 分**。
- 如果 $t = 2$ 的测试用例正确，将获得 **33 分**。
- 如果 $t = 3$ 的测试用例正确，将获得 **34 分**。

---

Translated by User 735713.

# 题解

## 作者：lol_qwq (赞：9)

# AT_birthday0410_a A + B 题解

###### ~~什么牛马题目，狗都不做~~

$$\text{\color{red}1.题目翻译}$$

找出使下列程序输出错误的数据（A+B）。

1：

```cpp
#include <iostream>

using namespace std;

int main()
{
  int A, B;

  while(cin >> A >> B, A+B!=0) {
    cout << A+B << endl;
  }

  return 0;
}
```


2:

```cpp
#include <iostream>

using namespace std;

int myAbs(int n)
{
  if(n < 0) return -n;
  else return n;
}

int main()
{
  int A, B;

  while(cin >> A >> B, (A|B) != 0) {
    while(myAbs(A) >= 100000) {
      if(A > 0) {
        B += 100000;
        A -= 100000;
      } else {
        B -= 100000;
        A += 100000;
      }
    }

    if(A > 0) {
      for(int i=0; i<A; ++i) {
        B++;
      }
    } else {
      for(int i=0; i<-A; ++i) {
        B--;
      }
    }

    cout << B << endl;
  }

  return 0;
}
```


3:

```cpp
#include<iostream>

using namespace std;

int C[3][32];

int main()
{
  int A, B;

  while(cin >> A >> B, A!=0 || B!=0) {
    for(int i=0; i<32; ++i) {
      C[0][i] = (A >> i) & 1;
      C[1][i] = (B >> i) & 1;
    }

    for(int i=0; i<32; ++i) {
      if(C[0][i] + C[1][i] >= 2) {
        C[C[1][i-1] & 1][i+1]++;
        C[0][i]--;
        C[1][i]--;
      }
      C[2][i] = C[0][i] + C[1][i];
    }

    int R = 0;
    for(int i=0; i<32; ++i) {
      R |= C[2][i] << i;
    }

    cout << R << endl;
  }

  return 0;
}
```

$$\text{\color{orange}2.题目分析}$$

第一条 hack:

```latex
正确：a + (-a) = 0
输出：
```

第二条 hack:

```latex
正确：-2147483648 + b = -2147483648 + b
输出：b
```

第三条 hack:

```latex
正确：a + (-a) = 0
测试：1 -1
输出：1
```

1. 第一个相反数相加和为 $0$，代码不输出。

2. 第二个代码是个反绝对值函数，当 $A$ $=$ $-2147483648$ 且 $B$ $=$ $0$ 时，因为 $A$ 的相反数爆 ```int``` 了，所以输出时是 $B$。

3. 第三个同第一个一样，也是相反数的问题。

$$\text{\color{green}3.题目代码}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
int main(){
   int a;
   cin >> a;
   if(a == 2){
     cout << "-2147483648 0\n 0 0" << endl;
   }else{
     cout << "-1 1\n 0 0" << end;
   }
}
```


---

## 作者：Lizj (赞：2)

updated on 2024/11/2 修改了第二组问题中语言描述不严谨的情况

## 题意分析

给定三组完成 $A+B$ 的源代码，输出会导致它输出错误答案的数据。

对于第一组源代码，当 $A,B$ 为相反数时，将没有输出（如 $A=-1,B=1$ 时）。

对于第二组源代码，当 $A,B$ 的绝对值不在 int 范围内时，将输出错误。

对于第三组代码，与第一组相同。

由此，我们可以写出代码。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int x;
    cin>>x;
    if(x==2) cout<<"-2147483648 0"<<endl<<"0 0"<<endl;
    else cout<<"-1 1"<<endl<<"0 0"<<endl;
    return 0;
}
```

---

## 作者：_ChongYun_ (赞：2)

~~这什么聪明题目啊~~

# 解析

对于第一段代码，当 $A$ 和 $B$ 互为相反数时，不会输出。

对于第二段代码，当 $A=$ $-$ $2147483648$ 时，它不在 int 类型范围内。

对于第三段代码，和第一段一样，当 $A=-1$，$B=1$ 时，就会输出`1`。

所以这样，就迎刃而解了。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int main(){
    cin>>n;
    if(n==2){
  	   cout<<"-2147483648 0"<<endl<<"0 0"<<endl;
    }else{
  	   cout<<"-1 1"<<endl<<"0 0"<<endl;
    }	
    return 0;
}
```


---

## 作者：InversionShadow (赞：1)

## AT_birthday0410_a A + B 题解

### 思路： 

题目给定三个源码，让你找出 $hack$ 数据，并输出 $hack$ 数据。

### 源码：

$1.$ 

```cpp
#include <iostream>

using namespace std;

int main()
{
  int A, B;

  while(cin >> A >> B, A+B!=0) {
    cout << A+B << endl;
  }

  return 0;
}
```
$2.$

```cpp
#include <iostream>

using namespace std;

int myAbs(int n)
{
  if(n < 0) return -n;
  else return n;
}

int main()
{
  int A, B;

  while(cin >> A >> B, (A|B) != 0) {
    while(myAbs(A) >= 100000) {
      if(A > 0) {
        B += 100000;
        A -= 100000;
      } else {
        B -= 100000;
        A += 100000;
      }
    }

    if(A > 0) {
      for(int i=0; i<A; ++i) {
        B++;
      }
    } else {
      for(int i=0; i<-A; ++i) {
        B--;
      }
    }

    cout << B << endl;
  }

  return 0;
}
```
$3.$

```cpp
#include<iostream>

using namespace std;

int C[3][32];

int main()
{
  int A, B;

  while(cin >> A >> B, A!=0 || B!=0) {
    for(int i=0; i<32; ++i) {
      C[0][i] = (A >> i) & 1;
      C[1][i] = (B >> i) & 1;
    }

    for(int i=0; i<32; ++i) {
      if(C[0][i] + C[1][i] >= 2) {
        C[C[1][i-1] & 1][i+1]++;
        C[0][i]--;
        C[1][i]--;
      }
      C[2][i] = C[0][i] + C[1][i];
    }

    int R = 0;
    for(int i=0; i<32; ++i) {
      R |= C[2][i] << i;
    }

    cout << R << endl;
  }

  return 0;
}
```

### 分析：

+ 第一个程序：运用 $while$ 循环输入。我们知道 $while$ 循环是每次做判断，然后再运行内部。我们发现循环条件是 $A\ +\ B\ !=\ 0$，在输入一对相反数时，他们的和为 $0$，做判断时直接 $out$ 掉了，根本无法做输出。

例：

输入： $-1$  $1$

输出：  （没有）

正确输出：0

+ 第二个程序，蒟蒻不知道是什么，看了楼下神犇的解释，才知道是 **绝对值函数**，当 $A\ =\ -2147483648$ 时，它的绝对值是 $2147483648$，超过 ```int``` 范围了，只要输入一个 ```int``` 范围以内的数 $B$，程序只会输出 $B$。

例：

输入： $-2147483648$  $0$

输出：$0$

正确输出：$-2147482647$

+ 第三个程序和第一个功能一样，也是相反数的问题，不过输入一个 $A$ 和 $B\ (A\ \leq\ 0\ \leq\ B)$，注意 $A$	是 $B$ 的相反数，输出的结果为 $1$，但是如果 $A$ 是 $B$ 的相反数，那答案为 $0$，是正确的。

例：

输入：$-1$ $1$

输出：$1$

正确输出：$0$

### Code：

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
    cin >> n;
    if (n == 2) {
      cout << "-214748364" << ' ' << "0" << endl << "0" << ' ' << "0" << endl;
    } else {
    	cout << "-1" << ' ' << "1" << endl << "0" << ' ' << "0" << endl;   // 发现程序 1 和程序 2 的反例可以一样，所以可以写在一起，或者分别写一组反例
    }
    return 0;
}

```


---

## 作者：The_End_of_GCC (赞：1)

[传送门](https://www.luogu.com.cn/problem/AT_birthday0410_a)

## 分析：

对于第一个程序， $A+B!=0$ 显然多余，故 hack 数据中的 $a$ 和 $b$ 为相反数。

对于第二个程序，其中的[反绝对值函数](https://jingyan.baidu.com/article/d3b74d64ae976e1f76e6096d.html)会爆``` int ```
，所以有 $a=-2147483648$，$b=0$。

对于第三个程序，还是一个相反数的问题，hack 与第一个程序的 hack 可以一样。

然后，我们就可以写出一个神奇的代码：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int s;
    cin>>s;
    if(s==2)
    	cout<<"-2147483648 0"<<endl<<"0 0"<<endl;
    else
    	cout<<"-1 1"<<endl<<"0 0"<<endl;
    return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/95092909)

希望大家采纳。

---

## 作者：yinpeichu2021 (赞：0)

# 翻译

找出使下列程序输出错误的数据（A+B）。

1：

```cpp
#include <iostream>

using namespace std;

int main()
{
  int A, B;

  while(cin >> A >> B, A+B!=0) {
    cout << A+B << endl;
  }

  return 0;
}
```

2:

```cpp
#include <iostream>

using namespace std;

int myAbs(int n)
{
  if(n < 0) return -n;
  else return n;
}

int main()
{
  int A, B;

  while(cin >> A >> B, (A|B) != 0) {
    while(myAbs(A) >= 100000) {
      if(A > 0) {
        B += 100000;
        A -= 100000;
      } else {
        B -= 100000;
        A += 100000;
      }
    }

    if(A > 0) {
      for(int i=0; i<A; ++i) {
        B++;
      }
    } else {
      for(int i=0; i<-A; ++i) {
        B--;
      }
    }

    cout << B << endl;
  }

  return 0;
}
```

3:

```cpp
#include<iostream>

using namespace std;

int C[3][32];

int main()
{
  int A, B;

  while(cin >> A >> B, A!=0 || B!=0) {
    for(int i=0; i<32; ++i) {
      C[0][i] = (A >> i) & 1;
      C[1][i] = (B >> i) & 1;
    }

    for(int i=0; i<32; ++i) {
      if(C[0][i] + C[1][i] >= 2) {
        C[C[1][i-1] & 1][i+1]++;
        C[0][i]--;
        C[1][i]--;
      }
      C[2][i] = C[0][i] + C[1][i];
    }

    int R = 0;
    for(int i=0; i<32; ++i) {
      R |= C[2][i] << i;
    }

    cout << R << endl;
  }

  return 0;
}
```

# 思路

对于第一个程序，易发现判断语句错误，当输入的两个数互为相反数时，其不对。可以出 `-1 1\n0 0` 这组数据。

对于第二个数据，可以看到其 `myAbs` 函数若为负数返回的是 `-n`，但是 `int` 类型的最小值 $-2147483648$ 的相反数超出了最大值 $2147483647$，所以会仍是 $-2147483648$。

这样会导致若 $A$ 为 $-2147483648$ 时第 $32$ 行的 `-A` 越界变成负数，即 $B$ 不会加上 $A$，所以输出为 $B$。

设 $B$ 为 $0$，数据为 `-2147483648 B\n0 0`。

最后一个看不懂。。。交一波[P1001](https://www.luogu.com.cn/problem/P1001)，发现错了下面这一个点：

```cpp
-123 123
```

似乎是互为相反数，试一试 `-1 1`，发现输出 $1$，可行！

终于，~~经历了九九八十一难，~~得出了以下代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	if(t==2)cout<<"-2147483648 0\n0 0\n";
	else cout<<"-1 1\n0 0\n";
	
	return 0;
}
```

---

