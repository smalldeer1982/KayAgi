# 题目信息

# [ARC185B] +1 and -1

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc185/tasks/arc185_b

長さ $ N $ の整数列 $ A\ =\ (A_1,\ A_2,\ \dots,\ A_N) $ があります。  
 あなたは次の操作を $ 0 $ 回以上好きな回数行うことが出来ます。

- $ 1\ \leq\ i\ \lt\ j\ \leq\ N $ を満たす整数対 $ (i,\ j) $ を選び、$ A_i $ を $ A_i\ +\ 1 $ に、$ A_j $ を $ A_j\ -\ 1 $ に置き換える。
 
操作によって $ A $ を広義単調増加な数列にすることが可能かどうか判定してください。

$ T $ 個のテストケースが与えられるので、それぞれに対して答えを求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ T\ \leq\ 2\ \times\ 10^5 $
- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 0\ \leq\ A_i\ \leq\ 10^9 $
- 全てのテストケースに対する $ N $ の総和は $ 2\ \times\ 10^5 $ 以下
- 入力される値は全て整数
 
### Sample Explanation 1

$ 1 $ 番目のテストケースでは、次のように操作を行うことで $ A $ を広義単調増加な数列にすることが出来ます。 - $ (i,\ j) $ として $ (1,\ 2) $ を選ぶ。操作後の $ A $ は $ (2,\ 6,\ 5) $ になる。 - $ (i,\ j) $ として $ (1,\ 2) $ を選ぶ。操作後の $ A $ は $ (3,\ 5,\ 5) $ になる。 $ 2 $ 番目のテストケースでは、どのように操作しても $ A $ を広義単調増加な数列にすることは出来ません。

## 样例 #1

### 输入

```
3

3

1 7 5

2

9 0

10

607 495 419 894 610 636 465 331 925 724```

### 输出

```
Yes

No

Yes```

# AI分析结果

### 题目内容重写

#### 题目描述

有一个长度为 $N$ 的整数序列 $A = (A_1, A_2, \dots, A_N)$。你可以进行以下操作任意次：

- 选择满足 $1 \leq i < j \leq N$ 的整数对 $(i, j)$，将 $A_i$ 替换为 $A_i + 1$，并将 $A_j$ 替换为 $A_j - 1$。

问是否可以通过这些操作将 $A$ 变成一个**广义单调递增**的序列（即非严格递增序列）。

给定 $T$ 个测试用例，每个测试用例需要输出 `Yes` 或 `No`。

#### 说明/提示

##### 约束

- $1 \leq T \leq 2 \times 10^5$
- $2 \leq N \leq 2 \times 10^5$
- $0 \leq A_i \leq 10^9$
- 所有测试用例的 $N$ 总和不超过 $2 \times 10^5$
- 输入值均为整数

##### 样例解释

第一个测试用例中，可以通过以下操作将 $A$ 变成广义单调递增序列：
1. 选择 $(1, 2)$，$A$ 变为 $(2, 6, 5)$
2. 选择 $(1, 2)$，$A$ 变为 $(3, 5, 5)$

第二个测试用例中，无论如何操作都无法将 $A$ 变成广义单调递增序列。

#### 样例输入

```
3

3

1 7 5

2

9 0

10

607 495 419 894 610 636 465 331 925 724
```

#### 样例输出

```
Yes

No

Yes
```

---

### 题解综合分析与结论

本题的核心在于判断是否可以通过一系列操作将序列变为广义单调递增。所有题解的共同思路是：通过操作调整序列，使其尽可能平均，然后判断是否满足单调递增的条件。具体来说，大多数题解都利用了序列的总和不变这一性质，构造一个目标序列，并通过前缀和或贪心策略来判断是否可行。

#### 最优关键思路

1. **总和不变**：操作不会改变序列的总和，因此可以利用总和来构造目标序列。
2. **目标序列构造**：将序列构造为尽可能平均的形式，即前 $n - s \bmod n$ 个元素为 $\lfloor \frac{s}{n} \rfloor$，后 $s \bmod n$ 个元素为 $\lceil \frac{s}{n} \rceil$。
3. **前缀和判断**：通过比较原序列和目标序列的前缀和，判断是否可以通过操作将原序列变为目标序列。

#### 可拓展之处

类似的问题可以通过构造目标序列并利用前缀和或贪心策略来解决。例如，判断是否可以通过某些操作将序列变为特定形式的问题，都可以考虑类似的思路。

---

### 推荐题目

1. [P2367 差分基础题](https://www.luogu.com.cn/problem/P2367)
2. [P3372 线段树模板题](https://www.luogu.com.cn/problem/P3372)
3. [P3383 线性筛素数](https://www.luogu.com.cn/problem/P3383)

---

### 精选题解

#### 题解1：作者：Locix_Elaina_Celome (评分：4星)

**关键亮点**：
- 通过构造目标序列并利用前缀和判断是否可行，思路清晰。
- 代码简洁，逻辑明确。

**核心代码**：
```cpp
int n;
int a[N];
int g[N];
int main(){
	int T;
	read(T);
	while(T--){
		read(n);
		int sm=0;
		for(int i=1;i<=n;i++){
			read(a[i]);
			sm+=a[i];
		}
		for(int i=1;i<=n;i++){
			if(i<=(n-sm%n))g[i]=sm/n;
			else g[i]=sm/n+1;
		}
		sm=0;
		for(int i=n;i;i--){
			sm+=a[i]-g[i];
			if(sm<0){
				puts("No");
				break;
			}
		}
		if(sm>=0)puts("Yes");
	}
	return 0;
}
```

**实现思想**：
- 构造目标序列 $g$，使得前 $n - s \bmod n$ 个元素为 $\lfloor \frac{s}{n} \rfloor$，后 $s \bmod n$ 个元素为 $\lceil \frac{s}{n} \rceil$。
- 通过倒序遍历序列，计算前缀和，判断是否满足条件。

---

#### 题解2：作者：Super_Cube (评分：4星)

**关键亮点**：
- 直接利用总和不变的性质，构造目标序列并判断是否可行。
- 思路简洁，代码实现高效。

**核心代码**：
```cpp
int n;
int a[N];
int g[N];
int main(){
	int T;
	read(T);
	while(T--){
		read(n);
		int sm=0;
		for(int i=1;i<=n;i++){
			read(a[i]);
			sm+=a[i];
		}
		for(int i=1;i<=n;i++){
			if(i<=(n-sm%n))g[i]=sm/n;
			else g[i]=sm/n+1;
		}
		sm=0;
		for(int i=n;i;i--){
			sm+=a[i]-g[i];
			if(sm<0){
				puts("No");
				break;
			}
		}
		if(sm>=0)puts("Yes");
	}
	return 0;
}
```

**实现思想**：
- 构造目标序列 $g$，使得前 $n - s \bmod n$ 个元素为 $\lfloor \frac{s}{n} \rfloor$，后 $s \bmod n$ 个元素为 $\lceil \frac{s}{n} \rceil$。
- 通过倒序遍历序列，计算前缀和，判断是否满足条件。

---

#### 题解3：作者：Nuclear_Fish_cyq (评分：4星)

**关键亮点**：
- 通过贪心策略，构造目标序列并判断是否可行。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
#include <bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define inf INT_MAX
#define linf LLONG_MAX
#define ninf INT_MIN
#define nlinf LLONG_MIN
#define mod 998244353
#define lwbd lower_bound
#define upbd upper_bound
//#define range
using namespace std;
void read(int &x){
	cin >> x;
	return;
}
void readll(ll &x){
	cin >> x;
	return;
}void readdb(db &x){
	cin >> x;
	return;
}
ll t, n, a[200000], sum, now;

//如果再忘记把题目给的1~n变为0~n-1自罚20仰卧起坐
int main(){
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while(t--){
		cin >> n;
		sum = 0;
		now = 0;
		for(int i = 0; i < n; i++){
			cin >> a[i];
			sum += a[i];
		}
		for(int i = 0; i < n; i++){
			ll t = sum / n + (n - i <= sum % n);//t代表终点值
			now += t - a[i];
			if(now < 0){
				cout << "No" << endl;
				break;
			} 
		}
		if(now >= 0){//防止同时输出No和Yes 
			cout << "Yes" << endl;
		} 
	}
	return 0;
}
```

**实现思想**：
- 构造目标序列，使得前 $n - s \bmod n$ 个元素为 $\lfloor \frac{s}{n} \rfloor$，后 $s \bmod n$ 个元素为 $\lceil \frac{s}{n} \rceil$。
- 通过正序遍历序列，计算前缀和，判断是否满足条件。

---
处理用时：70.08秒