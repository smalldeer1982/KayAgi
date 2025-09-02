# [语言月赛 202308] 小粉兔 Failed System Test

## 题目背景

小粉兔在某场 CF 中 -154，警示大家不能 FST。

这是一道 **hack 题**。在本题目中，你将得到两个问题和两个解决对应问题的代码，但是给出的代码不能对于某些输入给出正确的输出。不能给出正确的输出的情况包括：

1. 输出错误的结果。
2. 运行超时。
3. 产生一些运行时未定义行为。目前技术可检测的未定义行为仅包括数组越界。

对于这两个问题，你需要分别提交一份符合要求的输入数据，使得给定的代码不能给出正确的输出。你可以直接使用『提交答案』功能，也可以提交一份以任何语言写成的数据生成器。

---
**提示：如果你使用提交答案功能，请在提交其他题目时记得将语言改回你所使用的语言。**

## 题目描述

以下给出两个问题的题目描述：

#### 问题 1

给定 $n$ 个元素，标号为 $1, 2, \cdots, n$，你需要标记其中 $k$ 个元素。如果两个元素标号相差 $1$ 则称二者相邻。

请计算出「自身未被标记且有至少一个相邻元素被标记」的元素的**可能的最小数量**和**可能的最大数量**。

#### 问题 2

给定一个仅包含小写字母 `a`、`b`、`c` 的字符串，判断这个字符串是否符合以下所有特征：

1. 字符串中至少有一个 `a` 字母和一个 `b` 字母，且所有的 `a` 在 `b` 之前。
2. 如果字符串中有 `c`，所有的 `a` 在 `b`、`c` 之前，所有的 `b` 在 `c` 之前。
3. `c` 的数量等于 `a` 的数量或 `b` 的数量。


## 说明/提示

### 样例组与实际输入的说明

两个样例分别对应两个问题的样例输入输出。

如果你直接采用『提交答案』的方式，请分别将两个输入数据命名为 `1.in`、`2.in`，并打成 zip 压缩包进行提交；

如果你采用提交数据生成器的方式，你的生成器可以从标准输入读入一个整数 $x$，满足 $1 \leq x \leq 2$，表示该测试点对应的问题编号，然后**输出对应的输入数据**。

显然，你的程序不应该读入『输入格式』里提到的任何内容（而应该构造它们），也不应该输出『样例输出』里提到的任何内容（而是只输出你构造的输入数据）。你不应该使用样例测试你的程序，这只是对两个问题的样例说明。

### 数据规模要求

你给出的数据必须满足如下要求：

1. 完全符合『输入格式』的规定，不能有多余的输入，但是可以有文末回车。
2. 对于问题 $1$，$1 \leq n \leq 10 ^ 9$，$0 \leq k \leq n$。
3. 对于问题 $2$，$1 \leq \left | S \right | \leq 5000$（$\left | S \right |$ 代表字符串 $S$ 的长度），$S$ 中仅包含小写字母 `a, b, c`。

### 目标代码

你需要 hack 如下的代码：

#### 问题 1

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
	if (k == n || k == 0) {
		cout << "0 0" << endl;
		return 0;
	}
	cout << "1 ";
	if (k * 3 <= n)
        cout << 2 * k << endl;
	else
        cout << n - k << endl;
	return 0;
}
```

#### 问题 2

```cpp
#include <bits/stdc++.h>
using namespace std;

char str[5005];
int i, n, A, B, C;

int main() {
	cin >> str;
	n = strlen(str);
	if (str[0] != 'a') {
		cout << "NO" << endl;
		return 0;
	}
	for (i = 0; i < n; ++i) 
        if (str[i] != 'a') break;
	A = i;
	for (; i < n; ++i)
		if (str[i] != 'b') break;
	if (i == n || str[i] != 'c') {
		cout << "NO" << endl;
		return 0;
	}
	B = i - A;
	for (; i < n; ++i)
		if (str[i] != 'c') break;
	if (i != n) {
		cout << "NO" << endl;
		return 0;
	}
	C = n - B - A;
	if (C != A && C != B) 
        cout << "NO" << endl;
	else 
        cout << "YES" << endl;
	return 0;
}
```

目标代码的编译选项为 `-std=c++14 -fno-asm -O2`。编译器为洛谷提供的 g++。你可以在『在线 IDE』中选择 C++14 语言来获得完全相同的编译环境。

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
  } else { // 这个 else 不会被执行
    cout << "Stupid Fusu!" << endl;
  }
}
```

如果你使用『提交答案』功能，请务必保证打开压缩包后能且仅能**直接**看到两个 `.in` 文件。这就是说，文件结构必须是：

```plain
ans.zip
 |---1.in
 |---2.in
```

两个文件不应该被额外的文件夹包含，即文件结构不能是：

```plain
ans.zip
 |---ans(folder)
      |---1.in
      |---2.in
```

### 关于评测信息的说明

如果 hack 成功，对应测试点的信息为 accepted。如果返回其他信息，说明程序本身有误。

例如，如果返回 TLE，不代表成功的将对应程序 hack 至超时，而是表示数据生成器本身运行超时，测试点不得分。

特别的，返回 UKE 结果可能是数据不合法（有多余内容、缺少内容或数据范围不符合要求）。

## 样例 #1

### 输入

```
6 3```

### 输出

```
1 3```

## 样例 #2

### 输入

```
aaabccc
```

### 输出

```
YES
```

# 题解

## 作者：dthythxth_Huge_Brain (赞：5)

这是一道 Hack 题，我们先来看看第一问：

>给定 $n$ 个元素，标号为 $1, 2, \cdots, n$，你需要标记其中 $k$ 个元素。如果两个元素标号相差 $1$ 则称二者相邻。

>请计算出「自身未被标记且有至少一个相邻元素被标记」的元素的**可能的最小数量**和**可能的最大数量**。

> $1\le n\le 10^{9},0\le k\le n$

Hack 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
	if (k == n || k == 0) {
		cout << "0 0" << endl;
		return 0;
	}
	cout << "1 ";
	if (k * 3 <= n)
        cout << 2 * k << endl;
	else
        cout << n - k << endl;
	return 0;
}

```

不难发现，$k$ 和 $n$ 都是用 int 存储的，但是```if (k * 3 <= n)```这里将 $k$ 乘上了 $3$，会爆 int，所以我们把 $n$ 取最大值，$k$ 取比 $n$ 小的最大值（注意这里 $k$ 不能取最大值，要不然 $n$ 就和 $k$ 相等了，第一个 if 判断就会判掉，不会爆 int）。

-----

接着来看第二问：

>给定一个仅包含小写字母 `a`、`b`、`c` 的字符串，判断这个字符串是否符合以下所有特征：

>1. 字符串中至少有一个 `a` 字母和一个 `b` 字母，且所有的 `a` 在 `b` 之前。

>2. 如果字符串中有 `c`，所有的 `a` 在 `b`、`c` 之前，所有的 `b` 在 `c` 之前。

>3. `c` 的数量等于 `a` 的数量或 `b` 的数量。


>$1 \leq \left | S \right | \leq 5000$（$\left | S \right |$ 代表字符串 $S$ 的长度），$S$ 中仅包含小写字母 `a, b, c`。

>如果 $S$ 符合要求，则输出 `YES`，否则输出 `NO`。

Hack 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

char str[5005];
int i, n, A, B, C;

int main() {
	cin >> str;
	n = strlen(str);
	if (str[0] != 'a') {
		cout << "NO" << endl;
		return 0;
	}
	for (i = 0; i < n; ++i) 
        if (str[i] != 'a') break;
	A = i;
	for (; i < n; ++i)
		if (str[i] != 'b') break;
	if (i == n || str[i] != 'c') {
		cout << "NO" << endl;
		return 0;
	}
	B = i - A;
	for (; i < n; ++i)
		if (str[i] != 'c') break;
	if (i != n) {
		cout << "NO" << endl;
		return 0;
	}
	C = n - B - A;
	if (C != A && C != B) 
        cout << "NO" << endl;
	else 
        cout << "YES" << endl;
	return 0;
}
```
很好发现，这个代码并没有判断字符串特征的这个条件：

>至少有一个 `a` 字母和一个 `b` 字母。

我们只需满足字符串的其他特征，并且没有 `b` 字母，即可使代码输出错误。

---

## 作者：A_grasser (赞：5)

## 题意简化

干掉两份目标代码。

## 解法分析

### 程序一

输入数据为 `1000000000 999999999` 会导致 `k*3` 爆 `int`。

### 程序二

输入 `ac` 时，按道理来说应该输出 `NO`，但是程序识别不出没有 `b`。因为程序的思维是找 `a` 后面的字符，并求出 `b` 的数目和 `c` 的数目，没有判断 `B==0` 的情况。

## 完整代码

```cpp
//已通过 
#include<bits/stdc++.h>
using namespace std;
int main(){
  	int taskId;
  	cin>>taskId;
  	if(taskId==1){
    	cout<<"1000000000 999999999"<<endl;
  	}
	else{
		cout<<"ac"<<endl;
	}
	return 0;
}
```

---

## 作者：zhanghaosong (赞：3)

# B3821 [语言月赛 202308] 小粉兔 Failed System Test 题解

### 解析

#### 代码 $1$

本题使用了 `int` 类型，又数据范围是 $10^9$ 量级的，一看就是输入超大数据炸 `int`。

观察代码中的破绽，注意到 `if (k * 3 <= n)` 这句话，直接将 $k$ 赋值为 `1e9-1` 即可（将 $n$ 赋值为 `1e9`）。

#### 代码 $2$

题目中规定必须有 `a` 字符和 `b` 字符才能输出 `Yes`，但是在被 Hack 的代码中，竟然没有对 `b` 是否存在进行判断！抓住破绽，输出一个没有 `b` 的代码即可，比如 `ac`，就能 AC 本测试点。

### 总代码

由于是 B 题库的题目，贴一个代码。

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n;
int main(){
	cin>>n;
	if(n==1){
		cout<<"1000000000 999999999"; //大数 Hack 是一种常见的 Hack 方式哦 
	}
	else if(n==2){ //也可以写为 else 
		cout<<"ac"; //祝大家AC呀 
	}
return 0;
}
```


---

## 作者：Pink_Cut_Tree (赞：3)

# B3821 [语言月赛 202308] 小粉兔 Failed System Test 题解

又到了一月一度的 Hack 题时间，作为蒟蒻的我肯定要来~~氵一发~~题解呀。

赛时没有 Hack 出来第二题，痛失 $750$ 分。

此外，Hack 题的基础知识已经在题目中说的很清楚了，此处不再赘述。

### 解析

#### 问题 $1$

对于数据范围 $1\leq n \leq 10^9$，一看就是让我们制造超大数据爆 `int`，于是观察代码。

在第 $11$ 行，有 `k*3` 运算，而对于 `int` 的范围是 $-2147483648\sim 2147483647$，远远小于 $3\times 10^9$，所以对于 $k$，我们只需输入 `1e9-1`，即可完美 Hack（当然，$n$ 需要赋值为 `1e9`，题中说明了 $k\leq n$）。

#### 问题 $2$

题目要求必须含有 `a` 和 `b` 才算一个“合格”的字符串，但是观察代码，只有 $18\sim 19$ 行与 `b` 有关，而且压根没判断 `b` 是否存在！所以我们只需输入一个没有 `b`，且 `a` 和 `c` 的数量相等的字符串即可，错误程序会输出 `Yes`，而应该输出 `No`。

### 完整代码

```cpp
#include<bits/stdc++.h> 
using namespace std;
int n;
int main(){
	cin>>n;
	if(n==1){
		cout<<int(1e9)<<" "<<int(1e9);
	}
	else if(n==2){
		cout<<"aaaaaccccc";
	}
	else{ //这个else不会被执行 
		cout<<"Stupid Xiaofentu";
	}
return 0;
}
```


---

## 作者：szh_AK_all (赞：2)

本道题分为两问，我们逐一分析。

## 第一题
#### 伪代码
```c
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
	if (k == n || k == 0) {
		cout << "0 0" << endl;
		return 0;
	}
	cout << "1 ";
	if (k * 3 <= n)
        cout << 2 * k << endl;
	else
        cout << n - k << endl;
	return 0;
}
```
数据：$1\le n \le 10^9,0\le k \le n$。

对于这一小问，我们其实不需要明白怎么做，仔细观察代码便会发现，在第 $11$ 行，变量 $k$ 乘了 $3$。先看看 $k$ 的类型，再看看 $k$ 的范围，不难发现，当 $k$ 为最大值时，$k\times3$ 会达到惊人的 $3\times10^9$，这已经超出了 `int` 的范围。

然后，我们冲动地写下第一题的答案：$n=10^9,k=10^9$。本已自信满满，然鹅，发现错了。我们再看看程序第 $6$ 行，如果 $k=n$，当输出 $0  0$ 后，程序就终止了。所以，我们只要稍稍修改一下 $k$ 的值即可。

## 第二题
#### 伪代码
```c
#include <bits/stdc++.h>
using namespace std;

char str[5005];
int i, n, A, B, C;

int main() {
	cin >> str;
	n = strlen(str);
	if (str[0] != 'a') {
		cout << "NO" << endl;
		return 0;
	}
	for (i = 0; i < n; ++i) 
        if (str[i] != 'a') break;
	A = i;
	for (; i < n; ++i)
		if (str[i] != 'b') break;
	if (i == n || str[i] != 'c') {
		cout << "NO" << endl;
		return 0;
	}
	B = i - A;
	for (; i < n; ++i)
		if (str[i] != 'c') break;
	if (i != n) {
		cout << "NO" << endl;
		return 0;
	}
	C = n - B - A;
	if (C != A && C != B) 
        cout << "NO" << endl;
	else 
        cout << "YES" << endl;
	return 0;
}
```
先抱着侥幸的心态看看这份代码会不会出现类似于第一问的情况，发现没有。于是细致的看看这份代码，可以手动模拟一下。

先看程序的第 $10$ 行（也就是这篇题解的第 $41$ 行），当字符串的首位不是 $a$ 时，那么不符合条件，输出后直接终止。那么这一段对不对呢？我们思考一下：题目中要求所有的 $a$ 是在 $b$ 和 $c$ 之前，并且整个字符串是由 $abc$ 组成的，也就是说，字符串肯定是以 $a$ 开头的，如果开头不为 $a$，那么肯定不符合。所以这一段是对的。

再看程序的第 $14$ 行（也就是这篇题解的第 $45$ 行），我们发现这一段其实是用来记录字符串中 $a$ 出现的次数的，用 $A$ 来记录。仿佛没什么问题。再看程序的第 $17$ 到 $23$ 行，其实 $B$ 与 $A$ 类似，是用来记录 $b$ 出现次数的。当最后一个字符不为 $b$ 时，则此时 $i$ 等于 $n$。如果 $i$ 等于 $n$，则代表字符串中没有 $c$，那么肯定不符合条件。或者当 $i$ 小与 $n$ 时，如果我们访问到的这一位不是 $c$，那么肯定也不符合。所以这一段也是对的。

剩下一些可以自己思考。

我们发现，在这份程序所涉及的情况中，基本上是正确的，但这份程序有没有漏掉什么情况呢？

答案是有的。

咱们看看要求的第一点：“字符串中至少有一个 $a$ 字母和一个 $b$ 字母”。再想想这份程序，是不是忽略了这个情况。

如果字符串中不包含字符 $b$，正确答案应该是错误，但这份程序得出的答案却可能是正确。也就是，当字符串中前面一段为字符 $a$，后面一段为字符 $c$，且 $a$ 的数量等于 $c$ 的数量时，可以 `hack` 本题。

最后随便给出一串答案：`aaaccc`（如果写 `ac` 好像真可以 `AC` 哟）。

---

## 作者：BLuemoon_ (赞：1)

[link](https://www.luogu.com.cn/problem/B3821)

## Q1：

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;
    if (k == n || k == 0) {
        cout << "0 0" << endl;
        return 0;
    }
    cout << "1 ";
    if (k * 3 <= n)
        cout << 2 * k << endl;
    else
        cout << n - k << endl;
    return 0;
}
```

数据范围：$1 \le n \le 10^9$，$1 \le k \le n$，而在代码中使用了 `k*3` ，而 $10^9 \times 3$ 爆 `int` 了，所以我们只需要输出一个 $10^9$ 和一个接近 $10^9$ 的数 就行了。

`final answer:1000000000 999999998`

## Q2：

```cpp
#include <bits/stdc++.h>
using namespace std;

char str[5005];
int i, n, A, B, C;

int main() {
    cin >> str;
    n = strlen(str);
    if (str[0] != 'a') {
        cout << "NO" << endl;
        return 0;
    }
    for (i = 0; i < n; ++i) 
        if (str[i] != 'a') break;
    A = i;
    for (; i < n; ++i)
        if (str[i] != 'b') break;
    if (i == n || str[i] != 'c') {
        cout << "NO" << endl;
        return 0;
    }
    B = i - A;
    for (; i < n; ++i)
        if (str[i] != 'c') break;
    if (i != n) {
        cout << "NO" << endl;
        return 0;
    }
    C = n - B - A;
    if (C != A && C != B) 
        cout << "NO" << endl;
    else 
        cout << "YES" << endl;
    return 0;
}
```

代码在判断完 `a` 之后直接开始找 `b` 的个数，没有判断 `b` 的存在性，所以我们只需要输出一个没有 `b` 的字符串就行了。当然 `a` 的数量要等于 `c` 的数量。

`final answer:aacc`

## Code：

```cpp
#include<iostream>
using namespace std;
int n;
int main() 
{
    cin>>n;
    if(n==1)
        cout<<"1000000000 999999998"<<endl;
    else
        cout<<"aacc"<<endl;
    return 0;
}
```

---

## 作者：LEle0309 (赞：1)

一道 hack 题。

hack 题，就是你去找给定代码的茬。

#### 第一题

看到`int`，且里面有乘法，第一反应就是数据溢出。注意这句话：`if (k * 3 <= n)`，而 $ k $ 的最大取值是 $ 10^9 $，而 $ 3 \times 10^9 $ 是超过了 `int` 的上线，因此输出 $ 1000000000 $ 和 $ 999999999 $ 即可 AC。

#### 第二题

代码中并没有判断字母 `b` 是否出现，而题目中有一行：“字符串中至少有一个 `a` 字母和一个 `b` 字母”，所以我们输出一个没有 `b` 的字符串即可通过。

~~代码就不用放了吧。~~

```cpp
#include<iostream>
using namespace std;
int taskId;
int main()
{
    cin>>taskId;
    if (taskId==1)cout<<"1000000000 999999999";//第一个，炸掉int即可
    else cout<<"ac";//第二个，没有b就行了
    return 0;
}
```

---

## 作者：Disjoint_cat (赞：1)

# [B3821 小粉兔 Failed System Test](https://www.luogu.com.cn/problem/B3821)

~~哇哈哈我来抢水题解了~~

题意自己看。

## Subtask 1

首先这个程序复杂度是 $\Theta(1)$ 的，且没有开任何数组，所以只能 WA hack。

注意到一句 `if (k * 3 <= n)`，再看看数据范围 $k\le n\le10^9$。

$k\times3$ 会爆 `int`，而程序中 `n`、`k` 都是 `int` 的。

所以只需让 $k\times3>2147483647$ 即可。

## Subtask 2

不难得出，合法的字符串长这个样子：

$$\texttt{aa\dots abb\dots bcc\dots c}$$

且 $\texttt{c}$ 的个数等于 $\texttt{a}$ 的个数或者 $\texttt{b}$ 的个数。

注意到题面中有一句：

> 字符串中至少有一个 $\texttt{a}$ 字母和一个 $\texttt{b}$ 字母。

再翻翻程序，发现程序特判了没有 $\texttt{a}$，却没有特判没有 $\texttt{b}$。

实际上，不特判确实是错的。只要让字符串不含 $\texttt{b}$，且符合其他所有条件即可。（程序会输出 $\texttt{YES}$，但答案是 $\texttt{NO}$）

例如，输出 $\texttt{ac}$ 就能 AC。

```cpp
#include <iostream>

using namespace std;

int main() {
  int taskId;
  cin >> taskId;
  if (taskId == 1) {
    cout << "1000000000 998244353" <<endl;
  } else if (taskId == 2) {
    cout << "ac" << endl;
  } else { // 这个 else 不会被执行
    cout << "Stupid Fusu!" << endl;
  }
}
```

最后给一句警示：

十年 OI 一场空，不开 `long long` 见祖宗。

---

## 作者：Xdwjs (赞：1)

# B3821 题解

## 代码1：

注意到这句话 ```if (k * 3 <= n)``` ，由于 $k$ 的上限为 $10^9$ 且使用 int 类型，所以乘 3 会导致溢出。输出 ```1000000000 999999999``` 即可通过。


------------
## 代码2：

题目规定字符串中至少有一个 ```a``` 字母和一个 ```b``` 字母，然而我们看到，这个代码在过完 ```b``` 字母这一段后，只判定了下一位是否是 ```c```。这说明程序没有判定是否存在 ```b``` 字母。

输出一个不包含 ```b``` 字母，且 ```a``` 字母的数量等于 ```c``` 字母的数量的字符串（例：```ac```）即可 AC。

------------
## Code:
```cpp
#include <iostream>

using namespace std;

int main() {
  int taskId;
  cin >> taskId;
  if (taskId == 1) {
    cout << "1000000000 999999999" <<endl;
  } else if (taskId == 2) {
    cout << "ac" << endl;
  } else { // 这个 else 不会被执行
    cout << "Stupid Fusu!" << endl;
  }
}
```

---

## 作者：zhang_Jimmy (赞：1)

### 赛时思路：

#### 问题 1：

我们可以注意到程序里有一句话：

```cpp
if (k * 3 <= n)
```
因为 $1 \le k \le 10^9$，所以我们可以构造一组让 $k \times 3$ 爆 `int` 且答案是 $n - k$ 的数据，就可以 hack 掉。

#### 问题 2：

我们注意到程序里有这样一段话：

```cpp
for (i = 0; i < n; ++i) 
        if (str[i] != 'a') break;
	A = i;
	for (; i < n; ++i)
		if (str[i] != 'b') break;
	if (i == n || str[i] != 'c') {
		cout << "NO" << endl;
		return 0;
	}
```
如果输入字符串是 `ac`，那么这段代码首先遍历到位置 $1$，发现不是 `a` 然后跳出循环，再从位置 $1$ 开始遍历，发现不是 `b`，跳出循环。虽然这个字符串不满足条件，但是此时 $i = n$ 且 $str_i$ 是 `c` 所以不会输出 `NO`。

所以输出一个满足字母 `a` 都在字母 `c` 前面，字母 `a` 和字母 `c` 的数量一样且没有字母 `b` 的字符串即可 hack 掉。

赛时代码和[提交记录](https://www.luogu.com.cn/record/120343451)：

```cpp
#include <iostream>

using namespace std;

int main() {
  int taskId;
  cin >> taskId;
  if (taskId == 1) {
    cout << "1000000000 900000000" <<endl;
  } else if (taskId == 2) {
    cout << "ac" << endl;
  } else { // 这个 else 不会被执行
    cout << "Stupid Fusu!" << endl;
  }
}
```


---

## 作者：hjsxhst2022 (赞：0)

#### 问题1：

注意到这句话 `if (k*3<=n)` ，由于 $k$ 的上限为 $10^9$ ，但 $k$ 使用 `int` 类型，所以乘 $3$ 会导致溢出。输出 `1000000000 999999999` 即可通过。

#### 问题2：
题目规定字符串中至少有一个 `a` 字母和一个 `b` 字母，然而这个代码在跑完 `b` 字母后只判定了下一位是否是 `c`。这说明程序没有判定是否存在 `b` 字母。

所以，输出不包含 `b` 字母，且 `a` 字母的数量等于 `c` 字母的数量的字符串即可通过。

code:
```
#include<bits/stdc++.h>
using namespace std;
int main(){
    int taskId;
    cin>>taskId;
    if(taskId==1)
        cout<<"1000000000 900000000";
    if(taskId==2)
        cout<<"ac";
}
```

---

## 作者：Bc2_ChickenDreamer (赞：0)

# B3821 [语言月赛 202308] 小粉兔 Failed System Test

## problem 1

我们注意到，$1 \le n \le 10^9$，而 $k$ 可能等于 $n$，所以 $k$ 也可能是 $10^9$，代码中有 $k \times 3$ 的运算，而 $10^9 \times 3 = 3 \times 10^9$，又 $3 \times 10^9 > 2^{31} - 1$，所以只要让 $k = 10^9$ 即可。

## problem 2

我们注意到，这个代码运行完 $18$ 和 $19$ 行后，只判断了 `c`，没有判断 `b` 存在，所以我们输出只满足 $2$ 和 $3$ 条件的字符串即可。（例：`aacc`）

## code

```cpp
#include <iostream>

using namespace std;

int main() {
  int taskId;
  cin >> taskId;
  if (taskId == 1) {
    cout << "1000000000 999999999" <<endl;
  } else if (taskId == 2) {
    cout << "aaaccc" << endl;
  } else { // 这个 else 不会被执行
    cout << "I AK IOI! You AK NOI!" << endl;
  }
}
// code by beautiful_chicken233 | uid = 814343 time:2023.8.14 Tips:do not copy!

```


---

## 作者：RyanLi (赞：0)

传送门：[B3821 [语言月赛 202308] 小粉兔 Failed System Test](https://www.luogu.com.cn/problem/B3821)

更佳的阅读体验：[洛谷 B3821 题解](https://blog.ryanli.top/index.php/archives/50/)

---

注意到，这是一道 hack 题，这意味着我们只需要输出对应的答案即可。

### 问题 1

来阅读程序！注意到，在程序的第 $11$ 行有 `k * 3`，然而 $k$ 是一个 `int` 类型的变量，因此我们只需要让 $k$ 足够大然后爆 `int` 即可。

另外在第 $6$ 行可以发现，程序对 `n == k` 的情况进行了特判，因此使 $n$ 和 $k$ 是两个不同的数字即可，如`1000000000 999999999`。

### 问题 2

继续阅读下一个程序！注意到第一条规则：

> 字符串中至少有一个 `a` 字母和一个 `b` 字母，且所有的 `a` 在 `b` 之前。

因此，任何不含字符 `b` 的输入一定不合法。然而可以发现的是，整个程序并没有任何判断 `b` 是否存在的语句。

可以发现，$A$、$B$、$C$ 三个变量分别存储了字符 `a`、`b`、`c` 的长度，但在最后判定的时候，只有 `C != A` **并且** `C != B` 时才会判定不合法。而当输入一个不含 `b` 但含 `a`、 `c` 两种字符，且`a`、 `c` 的长度相等字符串时，程序就会因为 `C == A` 而错判这个字符串为合法。

因此，我们只需要构造一个仅包含 `a`、`c` 两种字符，且 `a`、`c` 的长度相等的字符串即可，如 `ac`。

---

以下是示例代码，答案不唯一。

#### Python

``` python
x = input()
if x == '1': print('1000000000 999999999')
else: print('ac')
```

#### C++

``` cpp
#include <iostream>
int main() {
    int x;
    std::cin >> x;
    switch (x) {
        case 1 : std::cout << "1000000000 999999999\n"; break;
        default : std::cout << "ac\n";
    } return 0;
}
```



---

## 作者：__Dist__ (赞：0)

这道hack还比较简单。

### 问题1

注意问题 $1$ 中，$100\%$ 的数据 $k \leq n \leq 10^9$，而代码里处理 $k\times2$、$k\times3$ 时并没有开 `long long`，所以直接把 `int` 炸掉就可以过。

```cpp
cout<<(int)1e9<<' '<<(int)1e9-1<<endl;//注意n==k代码里特判了，所以k=n-1
```

### 问题2

忽略了细节。

- 字符串中至少有一个 ```a``` 字母和一个 ```b``` 字母，且所有的 ```a``` 在 ```b``` 之前。

代码里判断了 ```a``` 是否出现，却没有判断 ```b``` 是否出现。

所以我们只需要输出一个 ```a``` 和 ```c``` 数量相等、所有 ```a``` 在 ```c``` 之前且没有 ```b``` 的字符串就行了。

```cpp
puts("ac");
```

---

## 作者：In_Memory (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/B3821)

## 题目大意

你将得到两个问题和两个解决对应问题的代码，但是给出的代码不能对于某些输入给出正确的输出。不能给出正确的输出的情况包括：

1. 输出错误的结果。

2. 运行超时。

3. 产生一些运行时未定义行为。目前技术可检测的未定义行为仅包括数组越界。

问题一：

给定 $n$ 个元素，标号为 $1, 2, \cdots, n$，你需要标记其中 $k$ 个元素。如果两个元素标号相差 $1$ 则称二者相邻。

请计算出「自身未被标记且有至少一个相邻元素被标记」的元素的可能的最小数量和可能的最大数量。

问题二：

给定一个仅包含小写字母 `a`、`b`、`c` 的字符串，判断这个字符串是否符合以下所有特征：

1. 字符串中至少有一个 `a` 字母和一个 `b` 字母，且所有的 `a` 在 `b` 之前。

2. 如果字符串中有 `c`，所有的 `a` 在 `b`、`c` 之前，所有的 `b` 在 `c` 之前。

3. `c` 的数量等于 `a` 的数量或 `b` 的数量。

## 解法说明

观察问题一数据范围，$n$ 和 $k$ 的最大值都是 $10 ^ 9$，代码中使用了 `int` 变量储存。但在求解过程中，代码中有计算 $3 \times k$ 的值，当 $k$ 较大时这个值会超出 `int` 最大范围导致数据溢出而出错，于是使 $n \ne k$，$3 \times k > n$，$3 \times k > 2 ^ {31} - 1$ 即可。我在这里选择了令 $n = 10 ^ 9$，$k = 10 ^ 9 - 1$，其它符合要求的数据也可通过本题。

观察问题二的代码，发现其中判断了以下几种不合法情况：

- 在一段连续的 `a` 前面还有其它字符。依题意可得 `a` 字符应当先于其他所有字符，所以显然不合法。

- 一段连续的 `b` 字符后面紧跟的不是 `c`。由于 `c` 的数量要和 `a` 或 `b` 的数量相等，所以不能没有 `c`，而 `a` 不能在 `b` 后，所以无论如何不合法。

- 一段连续的 `c` 字符后面还有字符。依题意可得 `c` 字符应当后于其他所有字符，所以显然不合法。

- `c` 的数量不和 `a` 或 `b` 中任意一个的数量相等。依题意可得显然不合法。

发现代码没有判断字符串中无 `b` 字符的情况，所以使字符串 `a` 和 `c` 数量相等，`a` 全部在 `c` 前方，没有 `b` 字符即可。此时字符串不合法，但程序会输出 `YES`。

完整代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x;
int main()
{
	cin>>x;
	if(x==1)
		cout<<(int)1e9<<" "<<(int)1e9-1;
	if(x==2)
		cout<<"aacc";
	return 0;
}
```
[AC记录](https://www.luogu.com.cn/record/120750462)

---

## 作者：Zhu_Ziyu (赞：0)

## 题意

Hack 题，显然。

## 分析

### 问题 1

因为 $1 \le n \le 10^9,0 \le k \le n$，所以代码中的 `3*k` 可能会因为 `int` 溢出导致负数，错误判断。

所以数据这样构造就好了：

```plain
1000000000 999999999
```

### 问题 2

可以观察代码中并没有判断字符串至少要有 $1$ 个 `b`。

所以数据就这样构造：

```
ac
```

---

## 作者：2011FYCCCTA (赞：0)

[原题](https://www.luogu.com.cn/problem/B3821)

---

### 问题 1
   
注意到这么一句： `if (k * 3 <= n)`
    	
观察数据范围 $0 \le k \le n \le 10^9$，计算 $k \times 3$ 最大可以达到 $3 \times 10^9$，会爆 `int`，因此造一组数据是 $k$ 接近或等于 $10^9$ 就可以 hack 掉。

示例：`1000000000 999999999`

### 问题 2

程序先遍历了字符 `a` 和字符 `b` 以及 `a` 的数量，之后有一句特判 `if (i == n || str[i] != 'c')` 意思是如果遍历完字符 `b` 就完了或最后一个 `b` 的下一个字符不是 `c`，就不满足要求，但这句忘了判断 `b` 是否出现，因此若输入为若干个 `a` 加若干个 `c`（数量一样）程序就会输出错误，例如若输入为 `ac`，既满足遍历完后 $i < n$ 又满足下一个字符是 `c`，而且 `c` 的数量等于 `a`，因此程序会输出 `Yes`。其余代码没问题。

示例：`ac`

---
### 代码

```cpp
#include <iostream>

using namespace std;

int main() {
  int taskId;
  cin >> taskId;
  if (taskId == 1) {
    cout << "1000000000 999999999" <<endl;
  } else if (taskId == 2) {
    cout << "ac" << endl;
  } else { // 这个 else 不会被执行
    cout << "Stupid Fusu!" << endl;
  }
}
```

---

## 作者：Darkworldmystery (赞：0)

提醒：hack 题是让你造一组数据来使别人提供的代码出现错误。

# T1

首先我们看到数据 $1 \le n,k \le 10^9$，结合提供的语句 `if (k * 3 <= n)`，那么我们想到的肯定就是溢出了。正好，$10^9 \times 3$ 超过了题目的 int 类型的范围，结合题面，就可以得到 hack 数据了（$k$ 不要太小，不然溢出后会大于 $k$）。

Data：`1000000000 999999999`

# T2

被 hack 代码中判断 `a` 是否在前面之后就只在找 `a` 和 `b` 的个数了，完全没有看到底有没有 `b`。所以只需要在满足 `a` 的数量和 `c` 的数量一样的基础下，输出一个没有 `b` 的字符串就好了。

Data：`ac`

---

