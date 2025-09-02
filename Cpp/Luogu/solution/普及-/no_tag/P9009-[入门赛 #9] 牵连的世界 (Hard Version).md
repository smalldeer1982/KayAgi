# [入门赛 #9] 牵连的世界 (Hard Version)

## 题目背景


这是一道 **hack 题**。在此类型的题目中，你将得到若干个问题和若干个解决对应问题的代码，但是给出的代码不能对于某些输入给出正确的输出。不能给出正确的输出的情况包括：

1. 输出错误的结果。
2. 运行超时。
3. 产生一些运行时未定义行为。目前技术可检测的未定义行为仅包括数组越界。

对于每个问题，你需要提交一份符合要求的输入数据，使得给定的代码不能给出正确的输出。你可以直接使用『提交答案』功能，也可以提交一份以任何语言写成的数据生成器。

---
**提示：如果你使用提交答案功能，请在提交其他题目时记得将语言改回你所使用的语言**

## 题目描述

以下给出三个问题的题目描述：

#### 问题 1

给出 $n$ 个整数，求其中奇数的个数。

#### 问题 2

判定 $p$ 是否为质数。

#### 问题 3

给出 $n$ 个整数，第 $i$ 个为 $a_i$。找到最大的数 $p$，使得满足 $a_i \ge p$ 的 $i$ 个数不小于 $\lfloor \dfrac{n}{2} \rfloor$。

## 说明/提示

### 样例组与实际输入的说明

三个样例分别对应三个问题的样例输入输出。

如果你直接采用『提交答案』的方式，请分别将三个输入数据命名为 `1.in`、`2.in`、`3.in`，并打成 zip 压缩包进行提交；

如果你采用提交数据生成器的方式，你的生成器可以从标准输入读入一个整数 $x$，满足 $1 \leq x \leq 3$，表示该测试点对应的问题编号，然后**输出对应的输入数据**。

显然，你的程序不应该读入『输入格式』里提到的任何内容（而应该构造它们），也不应该输出『样例输出』里提到的任何内容（而是只输出你构造的输入数据）。你不应该使用样例测试你的程序，这只是对三个问题的样例说明。

### 数据规模要求

你给出的数据必须满足如下要求：

1. 完全符合『输入格式』的规定，不能有多余的输入，但是可以有行末空格和文末回车。
2. 数据中所有的数字都应为整数。
3. 对于问题 1，$1 \leq n \leq 1000, -2 \times 10^9 \le a_i \le 2 \times 10^9$。
4. 对于问题 2，$1 \le p \le 10^{12}$。
5. 对于问题 3，$2 \leq n \leq 100$，$1 \leq a_i \leq 2 \times 10^9$。

### 目标代码

你需要 hack 如下的代码：

#### 问题 1

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, ans = 0;
  cin >> n;
  for(int i = 1, x; i <= n; i++) {
    cin >> x;
    if(x % 2 == 1) ++ans;
  }
  cout << ans << endl;
}
```

#### 问题 2

```cpp
#include<bits/stdc++.h>
using namespace std;

bool isprime(long long x) {
    if(x == 1) return false;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) return false;
    }
    return true;
}

int main() {
    long long p;
    cin >> p;
    if(isprime(p)) cout << "Yes" << endl;
    else cout << "No";
    return 0;
}
```

#### 问题 3

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 7;

int n, a[MAXN];

bool check(int x) {
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] >= x) ++tot;
    }
    return (tot >= (n / 2));
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int L = 1, R = 2000000000, ans;
    while(L <= R) {
        int mid = (L + R) / 2;
        if(check(mid)) ans = mid, L = mid + 1;
        else R = mid - 1;
    }
    cout << ans << endl;
    return 0;
}
```

目标代码的编译选项为 `-std=c++14 -fno-asm -O2`。编译器为洛谷提供的 g++。你可以在『在线 IDE』中选择 C++14 语言来获得完全相同的编译环境。

### 判分说明

本题共三个测试点，分别对应三个问题，测试点分值依次为 $30$分、$30$ 分、$40$ 分。

#### 数据判定

你给出的数据必须完全符合『数据规模要求』，否则将得到 Unaccepted 的结果。

#### 超时判定

程序每执行若干条指令，我们会检测一遍程序的运行时间。我们保证两次检测之间的指令条数是一个输入规模无关的量，也即每执行 $O(1)$ 条指令会进行一次检测。且两次检测之间的指令条数不会太多，一般不超过 $100$ 条 C++ 语句。

如果程序的运行时间超过 $500 \text{ms}$，则判定为程序运行超时，返回 accepted 结果。

#### 结果错误判定

如果程序在规定的时间内结束且给出了一个输出，我们会比较这个输出和**完全正确的输出**，如果二者不同，则判定为 hack 成功，返回 accepted 结果。

#### 未定义行为判定

我们会在每次**显式**的调用数组元素前判断数组下标是否超过数组范围，如果超过，则判定为 hack 成功，返回 accepted 结果。

这就是说，如果你希望通过未定义行为进行 hack，只能对显式的调用数组元素的行为进行 hack。

### 样例程序

这是一份可以帮你理解你需要输出的内容的样例程序，**但它不能给出正确的 hack 数据**。直接提交此程序不会得分。

```cpp
#include <iostream>

using namespace std;

int main() {
  int taskId;
  cin >> taskId;
  if (taskId == 1) {
    cout << "" <<endl;
  } else if (taskId == 2) {
    cout << "" << endl;
  } else if (taskId == 3) {
    cout << "" << endl;
  } else { // 这个 else 不会被执行
    cout << "QiHai Nanami" << endl;
  }
}
```

如果你使用『提交答案』功能，请务必保证打开压缩包后能且仅能**直接**看到三个 `.in` 文件。这就是说，文件结构必须是：

```plain
ans.zip
 |---1.in
 |---2.in
 |---3.in
```

三个文件不应该被额外的文件夹包含，即文件结构不能是：

```plain
ans.zip
 |---ans(folder)
      |---1.in
      |---2.in
      |---3.in
```

### 关于评测信息的说明

如果 hack 成功，对应测试点的信息为 accepted。如果返回其他信息，说明程序本身有误。

例如，如果返回 TLE，不代表成功的将对应程序 hack 至超时，而是表示数据生成器本身运行超时，测试点不得分。

特别的，返回 UKE 结果可能是数据不合法（有多余内容、缺少内容或数据范围不符合要求）。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
2```

### 输出

```
Yes```

## 样例 #3

### 输入

```
4
1 2 3 4```

### 输出

```
3```

# 题解

## 作者：yszkddzyh (赞：7)

这是一道 **hack 题**。具体的规则不多说了，直接看解法。

首先是第一个问题，注意到给出的代码中有这样一句话：
```cpp
cin >> x;
if(x % 2 == 1) ++ans;
```
而题目中给出：$-2\times10^9\le a_i\le2\times10^9$，我们发现 $a_i$ 可能为负，而对负数取模是会出错的。比如我们计算 `(-3)%2`，程序得出的结果是 $-1$，而 $-1$ 肯定是不等于 $1$ 的，所以上面的程序判断负奇数时会出错，因此我们只需要构造一个包含负奇数的输入即可，我提交的是这样的：
```cpp
4
-1 -2 -3 -4
```

接下来看第二个问题：判断质数。发现程序中有这样一句代码：
```cpp
for(int i = 2; i * i <= x; i++) {
    if(x % i == 0) return false;
}
```
问题在哪呢？发现代码是用 `int` 来存 $i$ 的值的，而这样的话当 $i\times i$ 的值大于 $2^{31}-1$ 时就会溢出导致程序错误，而题目的数据范围是 $p\le10^{12}$，所以我们只需要构造出一个大质数使 $i$ 溢出即可。打表发现小于 $10^{12}$ 的最大质数是 $999999999989$，因此输出这个数即可 AC。

最后看第三个问题，发现给出的代码用了二分。一时看不懂？没关系，出错的地方很简单。我们发现题目给出的程序中有这样一段：
```cpp
int L = 1, R = 2000000000, ans;
while(L <= R) {
    int mid = (L + R) / 2;
    if(check(mid)) ans = mid, L = mid + 1;
    else R = mid - 1;
}
```
问题在哪呢？它用 `int` 存变量 $L,R$ 和 $mid$，发现数据范围是：$1\le a_i\le2\times10^9$，而计算 $mid$ 时程序将 $L$ 和 $R$ 直接相加，`int` 的上限是 $2147483647$，所以当 $L$ 和 $R$ 都很大时，计算 $mid$ 的过程就会溢出，所以我们需要构造一组能爆 `int` 的数据，我给出的是：
```cpp
2
1999999999 2000000000
```
这样就能全部 AC 了，下面给出完整代码：
```cpp
#include <iostream>

using namespace std;

int main() {
  int taskId;
  cin >> taskId;
  if (taskId == 1) {
    cout << "4\n-1 -2 -3 -4" <<endl;
  } else if (taskId == 2) {
    cout << "999999999989" << endl;
  } else if (taskId == 3) {
    cout << "2\n1999999999 2000000000" << endl;
  } else { // 这个 else 不会被执行
    cout << "QiHai Nanami" << endl;
  }
}
```

2023.2.6 感谢 @Lyrically 指出一个重大错误。

---

## 作者：_GeorgeAAAADHD_ (赞：6)

题目大意:

给定三个问题及解决这三个问题的代码，你需要出一组数据，使得代码出错。

------------
这是一道 Hack 题，让我们一个一个问题来看吧！

------------

1.  求 $n$ 个数内的奇数个数。

数据范围：$1$ ${\le}$ $n$ ${\le}$ $1000$，对于第 $i$ 个数 $a_i$，$-2 \times 10^9$ ${\le}$ $a_i$ ${\le}$ $2 \times 10^9$。

分析:

乍一看代码好像没问题。

由于数据范围极小且没开数组，所以 TLE 和 RE 做法可以排除。

那就只剩 WA 做法了。

做过上次月赛第一题的人应该知道，**负数对正数取模会得到一个负数**，而判断条件是:
```cpp 
x % 2 == 1 
```
所以我们可以利用这一点来搞 WA。

Code:

```cpp
if(taskId==1)cout<<"1\n-1";
//简单粗暴
```
------------
2.  判断 $p$ 是否为质数。

数据范围：$1$ $\le$ $p$ $\le$ $10^{12}$。

分析:

看到代码感觉不太好入手。

但是只要观察函数内部，我们可以发现 $i$ 是 int 型的，这样我们就可以利用 $i \times i$ 来爆 int，从而使代码运行超时。

至于 $p$ 要开多大，只要使 $p \ge$ int 型的最大平方数，也就是 $p \ge 2147483647$ 且 $p$ 为质数就可以啦。

Code:

```cpp
if(taskId==2)cout<<"999999999989";
```
------------
3.   给出 $n$ 个整数，第 $i$ 个数为 $a_i$，找到最大的数 $p$，使得满足 $a_i$ $\ge$ $p$ 的 $i$ 个数不小于 ${\lfloor \frac{n}{2} \rfloor}$。

数据范围：$1 \le n \le 100$，$1 \le a_i \le 2 \times 10^9$。

分析:

这题出现了数组，但是数组的长度是 $n$ 最大时的十倍，所以 RE 做法泡汤了。

但是我们可以看到，求变量 mid 的值的时候出现了 $L + R$，这样我们就可以使 $L + R$ 的值爆 int，从而使计算机计算出错误的结果或超时！

Code:

```cpp
if(taskId==3)cout<<"2\n2000000000 2000000000";
```

最后附上完整代码:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int taskId;
    cin>>taskId;
    if(taskId==1)cout<<"1\n-1";
    if(taskId==2)cout<<"999999999989";
    if(taskId==3)cout<<"2\n2000000000 2000000000";
    return 0;
}
```


---

## 作者：yzm0325 (赞：3)

一道非常有趣的 hack 题。

首先第一题，给的程序是：

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, ans = 0;
  cin >> n;
  for(int i = 1, x; i <= n; i++) {
    cin >> x;
    if(x % 2 == 1) ++ans;
  }
  cout << ans << endl;
}
```

怎么做呢？我一看数据范围：

$-2 \times 10^9 \leq a_i \leq 2 \times 10^9$！可以负数！

拿 $-7$ 举例，它模 $2$ 的结果是 $-1$，程序只判断是否等于 $1$ ，所以这时条件不符合，$ans$ 不会 $+ 1$！所以让输入有负数就行了。

像这样：

```
3
-1 -2 -3
```

再看第二题。

给出的程序：

```cpp
#include<bits/stdc++.h>
using namespace std;

bool isprime(long long x) {
    if(x == 1) return false;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) return false;
    }
    return true;
}

int main() {
    long long p;
    cin >> p;
    if(isprime(p)) cout << "Yes" << endl;
    else cout << "No";
    return 0;
}
```

~~读了三遍~~才发现一个问题：

```cpp
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) return false;
    }
```

它全篇都是 `long long` 偏偏这里用 `int`，而题目的数据最大是 $10^{12}$，算 $i \times i$ 时会溢出！

所以就很简单了，只要输入一个大质数，$i \times i$ 就会完美地溢出，目的就达到了。

但注意必须是质数，不然枚举到一半就返回了，溢出不了。

拿程序试一下就知道小于 $10^{12}$ 的最大质数是 $999999999989$。

当然，稍微再小一点也没问题。（如 $999999999961$，也已经远超 `int` 极限。）

下面是第三题。

给出的程序：

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000 + 7;

int n, a[MAXN];

bool check(int x) {
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] >= x) ++tot;
    }
    return (tot >= (n / 2));
}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int L = 1, R = 2000000000, ans;
    while(L <= R) {
        int mid = (L + R) / 2;
        if(check(mid)) ans = mid, L = mid + 1;
        else R = mid - 1;
    }
    cout << ans << endl;
    return 0;
}
```

二分看不懂没关系（~~我也是~~），只要看见数据范围只有 `int` 就够了。也是一样的思路，用极端数据，虽然一个数溢出不了，但是 $L$ 和 $R$ 最大都是 $2 \times 10^{9}$，它们的和 $4 \times 10^{9}$ 已经超出 `int` 极限了。（`int` 的极限是 $2147483647$）


于是这样就可以：

```
2
2000000000 2000000000
```

再给全部代码（**禁止抄袭！！**）：

```cpp
#include <iostream>
using namespace std;
int main() {
  int taskId;
  cin >> taskId;
  if (taskId == 1) {
    cout << "3\n-1 -2 -3" <<endl;
  } else if (taskId == 2) {
    cout << "999999999961" << endl;//999999999989
  } else if (taskId == 3) {
    cout << "2\n2000000000 2000000000" << endl;
  } else { // 这个 else 不会被执行
    cout << "QiHai Nanami" << endl;
  }
  //完结撒花！！！
}
```

---

## 作者：ice_fish01 (赞：1)

## $\text{P9009}$ [入门赛 #9] 牵连的世界 ($\text{Hard Version}$)

### 题目大意

你将得到 $3$ 个问题和若干个解决对应问题的代码，但是给出的代码不能对于某些输入给出正确的输出。不能给出正确的输出的情况包括：

1. 输出错误的结果。
2. 运行超时。
3. 产生一些运行时未定义行为。目前技术可检测的未定义行为仅包括数组越界。

### $\text{Subtask 1}$

**本题多倍经验：[$\text{B3714}$ [语言月赛 $202302$] 牵连的世界 ($\text{Easy Version}$)](https://www.luogu.com.cn/problem/B3714)**

容易发现，代码中使用了 `if(x % 2 == 1) ++ans;` 来判断当前的数 $a_i$ 是否为奇数。当 $a_i \le 0$ 且 $a_i \bmod 2 = 1$ 时，C++ 语言中的模运算（`x % 2`）返回的结果是 $-1$ 而不是 $1$，导致奇数个数统计错误，符合「输出错误的结果」这一条要求。

因此我们使任何一个 $a_i \le 0$ 即可，其余部分可以自由构造。

### $\text{Subtask 2}$

注意到代码中使用了 `int` 类型的变量来存储 $i$ 的值，并将 $i\times i$ 与函数中的 $x$ 变量比较。

`int` 类型变量仅能够储存 $-2^{31} \sim 2^{31}-1$ 之间的整数值。当 $p$ 是一个大于 $\sqrt{2^{31}-1}$ 的质数时，就会发生数据溢出。

因此，我们给出一个大于 $\sqrt{2^{31}-1}$ 的质数即可。

### $\text{Subtask 3}$

注意到代码中使用了 `int mid = (L + R) / 2;` 来进行二分。当 $L+R\ge2^{31}-1$ 时，就会造成溢出。

因此我们给出 `2000000000 2000000000` 即可。

### 参考代码

```cpp
//P9009 [入门赛 #9] 牵连的世界 (Hard Version)
#include<bits/stdc++.h>
using namespace std;

signed main()
{
	int i;
	scanf("%d",&i);
	if(i == 1)
		printf("1\n-1");
	else if(i == 2)
		printf("999999999989");
	else if(i == 3)
		printf("2\n2000000000 2000000000");
	return 0;
}

```

---

