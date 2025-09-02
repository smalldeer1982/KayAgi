# [蓝桥杯 2023 国 Python A/Java A] 整数变换

## 题目背景

Python 选手建议使用 PyPy3 提交本题。

## 题目描述

小蓝有一个整数 $n$。每分钟，小蓝的数都会发生变化，变为上一分钟的数减去上一分钟的数的各个数位和。

例如，如果小蓝开始时的数为 $23$，则下一分钟变为 $23 - (2 + 3) = 18$，再下一分钟变为 $18 - (1 + 8) = 9$，再下一分钟变为 $9 - 9 = 0$，共经过了 $3$ 分钟变为 $0$。

给定一个正整数，请问这个数多少分钟后变为 $0$。


## 说明/提示

对于 $30\%$ 的评测用例，$1 \le n \le 1000$；

对于 $60\%$ 的评测用例，$1 \le n \le 10^6$；

对于所有评测用例，$1 \le n \le 10^9$。

## 样例 #1

### 输入

```
23```

### 输出

```
3```

# 题解

## 作者：Oracynx (赞：46)

## P10985 [蓝桥杯 2023 国 Python A] 整数变换 题解

**本题是 Python 题**

### 思路分析

显然的，这道题目只考察选手对 Python 的运用，我们可以顺理成章的写出下面的代码。

```python
s = input()
# 输入 s，此时的 s 是字符串
answer = 0
# 初始化答案变量
while s != '0':
    answer += 1
    # 更新答案
    remove = 0
    # 统计每一位的和
    for x in s:
        # 枚举每一个字符
        remove += int(x)
        # 更新每一位的和（必须用 int 将字符串类型转为数字类型）
    s = str(int(s) - remove)
    # 更新字符串，使用 str 将数字类型转为字符串类型
print(answer)
# 输出答案
```

（你知道为什么这个代码不在代码实现板块中吗？）

得益于 Python 的巨大常数，同时根据常识，字符串运算的常数是数字的数倍，这段代码 TLE 了……

而 PyPy3 对整数的运算有过优化（好像是不超过存储范围就先用类似于 C++ 的 `long long` 存，放不下了再用高精度，具体忘了），所以我们可以将其全程更改为使用整数计算即可通过。

### 代码实现

代码细节针对语言语法薄弱的同学已经写在了注释里。

```python
s = int(input())
# 输入 s，并把 s 从字符串转为数字
answer = 0
# 初始化答案变量
while s != 0:
    answer += 1
    # 更新答案
    remove = 0
    # 统计每一位的和
    n = s
    # 使用 int 将 s 转为数字类型
    while n != 0:
        # 枚举 n 的每一位
        remove += n % 10
        # 更新和
        n //= 10
        # 重点：Python 中的除法符号 / 是浮点数（小数）的除法，整除符号是 //
    s -= remove
    # 将原数减去每一位的和
print(answer)
# 输出答案
```

---

## 作者：离散小波变换° (赞：21)

轻松拿下最优解。

## 题意

设 $S(x)$ 表示 $x$ 在十进制下数位之和。给定正整数 $n$，每次令 $n\gets n-S(n)$，问多少步之后 $n$ 变成 $0$。

数据范围：$1\le n\le 10^9$。

## 题解

存在复杂度 $\mathcal O(\sqrt n\log n)$ 的做法。

考虑将 $n$ 分成两个部分，$n=h\times 10^B + l$，下面代码里取了 $B=4$。注意到因为每次减去的 $S(n)$ 是一个很小的值，所以大多数时候 $h$ 保持不变，$l$ 减小，只有当 $l< S(n)$ 时才会引起 $h$ 减一。

于是我们预处理 $S(h)=i,l=j$ 时，需要多少步才能把 $n$ 减到 $l$ 从 $h$ 借位，记为 $f_{i,j}$。容易得到递推方程：

$$
f_{i,j} = \begin{cases}
f_{i,j-S(n)}+1 & j\ge S(n) \\
1 & j< S(n) \\
\end{cases}
$$

同样地，我们还要记录最后一步减法之后，$l$ 从 $h$ 借位，留下的数字是多少。设为 $g_{i, j}$。因为转移方程和 $f$ 基本一样，这里就不放了，留作读者思考。

接着只要从大到小枚举 $h$，然后利用 $g$ 数组维护 $l$，利用 $f$ 数组统计答案，就做完了。

因为 $S(n)=\mathcal O(\log n)$，所以 $i$ 只用开到 $\mathcal O(\log n)$ 级别。于是总复杂度为 $\mathcal O(\sqrt n \log n)$。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e4 + 3;
const int MAXW = 1e5 + 3;
const int MAXM = 100 + 3;

int H[MAXM][MAXN][2];
int W[MAXW];

int main(){
    int n;
    cin >> n;
    int h = n / 10000;
    int l = n % 10000;

    for(int i = 1;i <= 100000;++ i){
        W[i] = W[i / 10] + i % 10;
    }

    for(int i = 0;i <= 100;++ i){
        for(int j = 0;j <= 9999;++ j){
            int t = i + W[j];

            if(t > j){
                H[i][j][0] = 1;
                H[i][j][1] = j - t + 10000;
            } else {
                H[i][j][0] = H[i][j - t][0] + 1;
                H[i][j][1] = H[i][j - t][1];
            }
        }
    }

    int ans = 0;
    for(int i = h;i >= 0;-- i){
        ans += H[W[i]][l][0];
        l    = H[W[i]][l][1];
    }
    cout << ans - 1 << endl;
    
    return 0;
}
```

---

## 作者：Ja50nY0un9 (赞：2)

该题考查的是依照题意模拟的能力，以及实现基本的 Python 语法的能力。

首先观察数据范围，发现数据范围为 $n \leq 10^9$，结合模拟做法时间复杂度约为 $\Omicron (\dfrac{n}{\log n})$，直接模拟足以通过。~~然而其实这是针对 PyPy 3 而言，使用 Python 3 提交会超时。~~

于是我们依照题意模拟：

首先输入 $n$ 并存入 `int` 格式中。
```python
n = int(input())
```
接着按照题意，每一轮需要将 $n$ 减去其各位数字之和，直到 $n = 0$。

这个过程中需要记录进行了第几轮减法，我们将这个信息存储在变量 $ans$ 中。代码实现上使用 `while` 语句，每一次循环将 $ans$ 加上 $1$ 来模拟这个过程。

```python
ans = 0
while n != 0 :
    ans += 1
    ...
```
由于我每一轮都需要 $n$ 的值，而取末位数字直到 $n = 0$ 的操作会破坏掉 $n$ 中的数据，我们不能在 $n$ 这个变量上直接修改。所以我们选择使用变量 $tmp$ 代替 $n$，用于记录 $n$ 在操作之前的值。

在每一轮循环中，每一次取出 $tmp$ 的最后一位，用 $n$ 减去该值，直到 $tmp$ 为 $0$。
```python
while n != 0 :
    ans += 1
    tmp = n
    while tmp != 0 :
        n -= tmp % 10
        tmp //= 10
```
最后输出 $ans$。
```python
print(ans)
```

---

我们合并以上各个片段得到完整代码：
```
n = int(input())
ans = 0
while n != 0 :
    ans += 1
    tmp = n
    while tmp != 0 :
        n -= tmp % 10
        tmp //= 10
print(ans)
```

---

## 作者：LG086 (赞：2)

根据题意模拟就行了。

先输入一个正整数 $n$，使用变量 $ans$ 来记录时间。  
外部循环使用 `while n>0` 进行循环，内部循环中计算 $n$ 的数位和。  
使用变量 $x$ 用来存储 $n$ 的当前值，$cnt$ 初始化为 $0$ 来计算各位数字之和。  
使用 `cnt+=x%10` 加上当前的末尾的数字，并通过整除操作 `x//=10` 去掉这一位数字，直到 $x=0$ 结束。  
更新 $n$ 为 $n-cnt$，$ans$ 加一。当 $n=0$ 时，输出 $ans$ 即可。

----

### 代码


```python
n=int(input())
ans=0
while n>0:
    x=n
    cnt=0
    while x>0:
        cnt+=x%10
        x//=10
    n-=cnt
    ans+=1
print(ans)
```

---

## 作者：joe_zxq (赞：2)

按照题目意思模拟即可。

看似数据范围是过不了的，其实是完全可以的。

首先是计算数字和，就是不断将结果累加上数的个位，然后将数除以 $10$ 向下取整。

其次是模拟，当 $n$ 不为 $0$ 时就不断减去数字和，将答案加一。

```cpp
// Problem: 
//     P10985 [蓝桥杯 2023 国 Python A] 整数变换
//   
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P10985
// Memory Limit: 512 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
using namespace std;

#define ll long long

void ts() {
	puts("The code is running!");
}

int read() {
    char c;
    bool isf = 0;
    while (!isdigit(c = getchar())) isf = (c == '-');
    int res = (c ^ 48);
    while (isdigit(c = getchar())) res = (res << 3) + (res << 1) + (c ^ 48);
    return isf ? -res : res;
}

void write(int x) {
    if (x < 0)
        putchar('-'), x = -x;
    if (x >= 10)
        write(x / 10);
    putchar('0' + x % 10);
}

void updmin(int& x, int y) {
	x = min(x, y);
}

void updmax(int& x, int y) {
	x = max(x, y);
}

void openf(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

int tc = 1;

void init() {
	;
}

int sum(int x) {
	int res = 0;
	while (x) {
		res += x % 10;
		x /= 10;
	}
	return res;
}

void solve() {
	init();
	int n, ans = 0;
	cin >> n;
	while (n) {
		n -= sum(n);
		ans++;
	}
	cout << ans;
}

int main() {
	
    // openf("data");

    // tc = read();
    
    while (tc--) {
    	solve();
    }
    
    // printf("Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);

    return 0;
}

/*
Things to check:

1. When testing multiple sets of data, remember to clear the array.

2. When clearing, pay attention to clearing the area, starting from 0 or 1. If time permits, use memset.

3. Delete the debugged code.

4. Do you need to enable file input/output.

5. Use faster input and output methods.

6. Pay attention to time complexity and space complexity, and control constants.

7. Think twice before acting.

8. Talk is cheap, show me the code.

9. The most important one, zxq's brain.
*/

/*
                                                                                              
_|_|_|_|_|  _|      _|    _|_|          _|      _|        _|_|      _|      _|_|    _|  _|    
      _|      _|  _|    _|    _|          _|  _|        _|    _|  _|  _|  _|    _|  _|  _|    
    _|          _|      _|  _|_|            _|              _|    _|  _|      _|    _|_|_|_|  
  _|          _|  _|    _|    _|          _|  _|          _|      _|  _|    _|          _|    
_|_|_|_|_|  _|      _|    _|_|  _|      _|      _|      _|_|_|_|    _|    _|_|_|_|      _|    
                                                                                              
                                                                 
*/
```

---

