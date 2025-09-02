# Automatic Door

## 题目描述

工厂里有一个自动门：

- 如果门关着，并来了一个或多个人，门立即打开，所有人立刻进去。

- 如果门开着，并来了一个或多个人，所有人立即进去。

- 门打开后$d$ 秒立刻关上。

- 门在关的瞬间，如果来了一个或多个人，这些人立刻进去，之后门关上。

例如，$d=3$ 时，有四个人分别在以下时刻到来：$\{4,7,9,13\}$ ，

那么门会开三次：$\{4,9,13\}$ ，

门会在以下时刻关闭：$\{7,12\}$ 。

你提前知道了公司有一批员工分别在$a,2a,3a,\cdots ,na(a\in \mathbf{Z^+})$ 时刻到来。另外有$m$ 位顾客分别在$t_{1},t_{2},\cdots,t_{m}$ 时刻到来。

最初门是关闭的。

试问门会开几次。

## 样例 #1

### 输入

```
1 1 3 4
7
```

### 输出

```
1
```

## 样例 #2

### 输入

```
4 3 4 2
7 9 11
```

### 输出

```
4
```

# 题解

## 作者：BADFIVE (赞：1)

**题意**：有一扇自动门, 若 $t$ 时有人来, 并且门是关的, 自动门会持续打开 $d$ 时间, $t$ 到 $t+d$ 时来的人都可以进入, 现在有 $n$ 个雇员, 分别在$a_1,a_2,...,a_n$ 时刻来, $m$ 个客户, 分别在 $t_1,t_2,...,t_m$ 时刻来, 求自动门打开的次数。   
**思路**：枚举 $m$ 个客户, 当一个客户 $i$ 来的时候, 先处理 $t_i$ 之前未处理的雇员即可。   
为了防止最后还有未处理的雇员, 可以添加一个客户, 让他时间等于 $n \ast a$ , 显然不影响答案。   

参考代码:   
```
#include <bits/stdc++.h>
using namespace std;
long long n, m, a, d, t[100001];
int main() {
	scanf("%lld%lld%lld%lld", &n, &m, &a, &d);
	for(int i=1;i<=m;i++) scanf("%lld", t+i);
	int now = 0, ans = 0, cur = 1;
	t[++m] = n*a;
	for(int i=m;i>=a;i--) if (t[i]<t[i-1]) swap(t[i],t[i-1]);
	for(int i=1;i<=m;i++) {
		if (cur<=n&&cur*a<t[i]) {
			now = cur*a;
			long long r = d/a+1, tot = (t[i]-now)/a+1;
			long long q = tot/r;
			if (q) {
				ans += q;
				now += (q-1)*r*a+d;
				tot -= q*r;
				cur = now/a+1;
			}
			if (tot) {
				++ans;
				now = cur*a+d;
				cur = now/a+1;
			}
		}
		if (now>=t[i]) continue;
		now = t[i]+d;
		cur = now/a+1;
		++ans;
	}
	printf("%lld\n", ans);
}
```

---

