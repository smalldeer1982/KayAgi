# 『MGOI』Simple Round I | A. 魔法数字

## 题目背景

> 目标越坚定的魔法士，越幸运。——殿堂魔法士 S

## 题目描述

初级魔法士小 M 的魔法数字是 $2$。

给定一个正整数 $n$，小 M 需要找到最大的 **偶数** $m$，使得 $2^m<n$。

请你帮帮他。

## 说明/提示

**【数据范围】**

对于前 $20\%$ 的数据，$n = 2$。

对于前 $60\%$ 的数据，$n$ 为 $2$ 的幂次。

对于 $100\%$ 的数据，$2 \le n \le 10^9$。

## 样例 #1

### 输入

```
7```

### 输出

```
2```

## 样例 #2

### 输入

```
8```

### 输出

```
2```

## 样例 #3

### 输入

```
1024```

### 输出

```
8```

# 题解

## 作者：残阳如血 (赞：12)

普通模拟的别的题解应该都有了，现在我来介绍一种不同寻常的~~偷懒~~方法！
# 思路分析
## 确定最大值
题目要我们求 $2^m$ 次方，常规的方法是对于 $m$ 一个一个试过去，最终找到答案。

但是，我们可以发现，$m$ 不就是 $\log_2 n$ 嘛！（不考虑偶数和小于的条件下）

所以我们可以使用 C++ 中的 `log2()` 函数，快速求出 $\log_2 n$ 的值。

不过，可不能这样结束。
## 进行微调
题目中提到了，要使 $2^m<n$，所以如果 $n$ 是 $2$ 的幂次，那么 $2^m$ 就会与 $n$ 相等这不符合题意。所以，我们需要特判 $2^m$ 是否与 $n$ 相等，如果相等就将 $m$ 减少 $1$。

另外，题目强烈提醒我们 $m$ 一定为**偶数**，所以，在执行上一个调整后，我们还要判断 $m$ 是否为奇数。如果是，那么我们还要将 $m$ 减少 $1$。
# 程序实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n;
int main() {
	cin >> n;
	int m = floor(log2(n)); // 将log2(n)的值向下取整
	if ((1 << m) == n) m--; // 第一类微调
	if (m & 1) m--; // 第二类微调
	cout << m;
	return 0;
}
```

---

## 作者：qwerty_____ (赞：8)

直接用 `pow()` 函数暴力判断即可，一旦不符合条件就立即跳出循环，要注意开 `long long` 或 `unsigned long long` 。

```cpp
#include <iostream>
#include <cmath>
using namespace std;
unsigned long long n, num;
int main(){
    cin >> n;
    for(unsigned long long i = 2; i <= n; i += 2){
        unsigned long long ans = pow(2, i);
        if(ans < n) num = i;
        if(ans >= n) break;
    }
    cout << num;
    return 0;
}
```

---

## 作者：zsh_haha (赞：5)

### 思路讲解

我们可以暴力枚举偶数 $i$，当第一次 $2^i>n$ 时，$i-2$ 就是最后一个偶数解，输出即可。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	int pro=1;
	for(int i=0;;i+=2){
		if(pro>=n){
			cout<<i-2;
			return 0;
		}else{
			pro*=4;
		}
	}
    return 0;
}
```

---

## 作者：封禁用户 (赞：3)

毫无压力！

看到 $2^n$，自然想到 $\log n$。

观察数据范围，当 $2 \le n \le 4$ 时，结果为 $0$。

所以只要循环所有非负偶数就可以啦~
```c
main(n) {
    scanf("%d", &n);
    int i;
    for (i = 0; i < log2(n) - 2; i += 2);
    printf("%d", i);
}
```

---

## 作者：MoGuYun_12 (赞：2)

按题意模拟即可。

```cpp
#include <bits/stdc++.h>

using namespace std;
long long n,m;
int main()
{
	cin>>n;
	while((1<<m)<n)
	{
		m+=2;
	}
	cout<<m-2;//最后多循环了一次，减2
	return 0;
}

```


---

## 作者：FurippuWRY (赞：1)

循环找到第一个使 $2^{m}\ge n$ 的偶数 $m$，因为要求的是偶数，再输出 $m-2$ 即可。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, p = 1;
int main() {
	cin >> n;
	for (int i = 2; ; i += 2) {
		if ((1 << i) >= n) {
			cout << i - 2;
			return 0;
		}
	}
	return 0;
}
```

---

