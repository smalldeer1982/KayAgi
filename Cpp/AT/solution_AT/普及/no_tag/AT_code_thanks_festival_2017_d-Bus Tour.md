# Bus Tour

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-thanks-festival-2017/tasks/code_thanks_festival_2017_d

あなたはバスツアーを計画しています。

バスツアーの参加者は必ず $ 1 $ グループ $ N $ 人で申し込みます。運転手を除いた各バスの定員は必ず $ M $ 人です。  
 このバスツアーは、全ての参加者がバスに乗り切れるようなバスの最小台数で行います。   
 同じグループに属する人が必ずしも同じバスに乗り込む必要はありません。

このバスツアーに参加するグループ数には上限がないため、申し込みを締め切るまでバスツアーに参加するグループ数は分かりません。   
 したがって、参加者の申し込み具合によってはバスに空席が生じてしまいます。   
 最大で何席の空席ができるでしょうか?

## 说明/提示

### 制約

- $ 1≦N≦10^9 $
- $ 1≦M≦10^9 $
- $ N $ と $ M $ は整数である。

### Sample Explanation 1

申し込みが $ 1 $ グループだった場合、参加者 $ 5 $ 人に対して定員 $ 4 $ 名のバス $ 2 $ 台で バスツアーを行うため、$ 3 $ 席の空席が生じます。

### Sample Explanation 2

申し込みグループ数に関わらず、常にバスが満員である場合もあります。

## 样例 #1

### 输入

```
5 4```

### 输出

```
3```

## 样例 #2

### 输入

```
1000000 10```

### 输出

```
0```

## 样例 #3

### 输入

```
500000000 1000000000```

### 输出

```
500000000```

# 题解

## 作者：Yizhixiaoyun (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/AT3639)

## 写在前面

本题需要提前掌握（链接指向 $\textit{oi-wiki}$ ）：[裴蜀定理](https://oi-wiki.org/math/number-theory/bezouts/)

## 题目分析

由裴蜀定理，轻松简化本题：

$Na + Mb = K$ 

那么我们只需要求出 $\gcd(n,m)$ ，然后找到满足是其倍数的最大的 $K(0 \leq K \leq m-1)$ 即可。

## 贴上代码

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	int gcd=__gcd(n,m);
	gcd=(m-1)/gcd*gcd;
	printf("%d",gcd);
}
```

---

## 作者：wuwendongxi (赞：2)

### 题意：

$Na≡K(mod M)$ 求 $K$ 的最大值。

### 题解：

- 题目等价于 $Na+Mb=K$，由裴蜀定理可知：$K$ 为 $gcd(N,M)$ 的倍数。同时，$K∈[0,M-1]$，求出最大的 $K$ 即可。

### 代码：
```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n,m,gcd;
int main()
{
	return scanf("%d%d",&n,&m),gcd=__gcd(n,m),cout<<((m-1)/gcd)*gcd,0;
}
```

---

## 作者：_acat_ (赞：1)

### 题目大意

给定 $N,M$，求 $N \times a≡k(\mod M)$ 的 $K$ 的最大值。

### 思路

对任意两个整数 $a,b$ 设 $d$ 是它们的最大公约数。那么关于未知数 $x$ 和 $y$ 的线性丢番图方程（称为裴蜀等式）：

$$ax + by = m$$

根据著名的裴蜀定理，我们可以轻松简化本题：$Na+Mb=K$。

得知 $K$ 为 $\gcd(N,M)$ 的倍数。

而 $K \in [0,M-1]$，所以只要求出最大的 $K$ 即可。



## AC Code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;

int n,m,gcd;

int main()
{
	cin>>n>>m;

	gcd=__gcd(n,m);
	cout<<((m-1)/gcd)*gcd;
   
   return 0;
}
```

---

## 作者：ttq012 (赞：0)

本题建议评黄。

**Solution**

feature：样例 $2$ 的输出 $0$ 不见了。

题目要求求 $N\times a\equiv k(\bmod M)$ 中 $k$ 的最大值。

可以用裴蜀定理将式子化简成 $Na + Mb = k$。

于是只需要求出 $\gcd(n, m)$，然后找到 $< m$ 的且是 $\gcd(n, m)$ 的倍数的数即可。

**Code**

```cpp
// Think twice, code once.

#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    cout << ((m - 1) / gcd(n, m)) * gcd(n, m) << '\n';
    return 0;
}

```



---

## 作者：EthanC_ (赞：0)

### 思路：
通过裴蜀定理我们可以分析出以下内容：
$ Na+Mb=K $，$ K $ 为 $ gcd(N,M) $ 的倍数。并且 $ K $ 在 $ [0,M-1] $ 中，我们要求的就是最大的 $ K $。
### 代码：
```cpp
#include<iostream>
#include<algorithm>//gcd头文件
using namespace std;
int main(){
    long long n,m;
    cin>>n>>m;
    long long g=__gcd(n,m);//将g设为n和m的最大公约数
    cout<<((m-1)/g)*g;//最大的肯定是m-1，我们将其除以最大的公约数在乘其就可以得到最大的K了。
    return 0;//完结撒花✿✿ヽ(°▽°)ノ✿
}
```


---

