# 题目信息

# k-th equality

## 题目描述

Consider all equalities of form $ a + b = c $ , where $ a $ has $ A $ digits, $ b $ has $ B $ digits, and $ c $ has $ C $ digits. All the numbers are positive integers and are written without leading zeroes. Find the $ k $ -th lexicographically smallest equality when written as a string like above or determine that it does not exist.

For example, the first three equalities satisfying $ A = 1 $ , $ B = 1 $ , $ C = 2 $ are

- $ 1 + 9 = 10 $ ,
- $ 2 + 8 = 10 $ ,
- $ 2 + 9 = 11 $ .

An equality $ s $ is lexicographically smaller than an equality $ t $ with the same lengths of the numbers if and only if the following holds:

- in the first position where $ s $ and $ t $ differ, the equality $ s $ has a smaller digit than the corresponding digit in $ t $ .

## 说明/提示

In the first test case, the first $ 9 $ solutions are: $ \langle 1, 1, 2 \rangle, \langle 1, 2, 3 \rangle, \langle 1, 3, 4 \rangle, \langle 1, 4, 5 \rangle, \langle 1, 5, 6 \rangle, \langle 1, 6, 7 \rangle, \langle 1, 7, 8 \rangle, \langle 1, 8, 9 \rangle, \langle 2, 1, 3 \rangle $ .

Int the third test case, there are no solutions as the smallest possible values for $ a $ and $ b $ are larger than the maximal possible value of $ c $ — $ 10 + 10 = 20 > 9 $ .

Please note that whitespaces in the output matter.

## 样例 #1

### 输入

```
7
1 1 1 9
2 2 3 1
2 2 1 1
1 5 6 42
1 6 6 10000000
5 5 6 3031568815
6 6 6 1000000000000```

### 输出

```
2 + 1 = 3
10 + 90 = 100
-1
9 + 99996 = 100005
-1
78506 + 28543 = 107049
-1```

# AI分析结果

### 题目重写
考虑所有形式为 $a + b = c$ 的等式，其中 $a$ 有 $A$ 位，$b$ 有 $B$ 位，$c$ 有 $C$ 位。所有数字都是正整数且没有前导零。找到第 $k$ 个字典序最小的等式，或者确定它不存在。

例如，满足 $A = 1$，$B = 1$，$C = 2$ 的前三个等式是：
- $1 + 9 = 10$，
- $2 + 8 = 10$，
- $2 + 9 = 11$。

一个等式 $s$ 在字典序上小于等式 $t$，当且仅当在 $s$ 和 $t$ 第一个不同的位置上，$s$ 的字符小于 $t$ 的对应字符。

### 算法分类
枚举

### 题解分析与结论
所有题解的核心思路都是通过枚举 $a$ 的值，然后根据 $a$ 的值计算 $b$ 的可能范围，从而确定 $c$ 的值。由于题目中 $A, B, C$ 的最大值为 6，且大多数测试用例满足 $A, B, C \leq 3$，因此枚举的复杂度是可接受的。

### 精选题解
#### 题解1：XSean (5星)
**关键亮点**：
- 通过枚举 $a$ 的值，计算 $b$ 的范围，直接判断是否满足 $k$ 的要求。
- 代码简洁，逻辑清晰，时间复杂度为 $O(10^A)$，在题目限制下非常高效。

**核心代码**：
```cpp
int qmi(LL a, int k){
	int res = 1;
	for(; k; k >>= 1, a = a * a) if(k & 1) res = res * a;
	return res;
}
void ans(int a, int b){
	prf("%d + %d = %d\n", a, b, a + b);
}
int main(){
	int T; rd(T);
	while(T--){
		LL a, b, c, k; rd(a, b, c, k);
		bool f = true;
		int l = qmi(10, a - 1), r = qmi(10, a) - 1;
		rep(i, l, r){
			int L = max(qmi(10, b - 1), qmi(10, c - 1) - i);
			int R = min(qmi(10, b) - 1, qmi(10, c) - 1 - i);
			if(L > R) continue;
			int temp = R - L + 1;
			if(k <= temp){
				ans(i, L + k - 1);
				f = false;
				break;
			}
			k -= temp;
		}
		if(f) puts("-1");
	}	
	return 0;
}
```

#### 题解2：qwq___qaq (4星)
**关键亮点**：
- 通过枚举 $a$ 的值，计算 $b$ 的范围，判断是否满足 $k$ 的要求。
- 代码结构清晰，使用了预处理数组来快速计算 $10^n$ 的值。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,a,b,c,k,cnt,p[15];
inline void solve(){
	cnt=0;
	for(int A=p[a-1];A<p[a];++A){
		int l=max(p[b-1]+A,p[c-1]),r=min(p[b]-1+A,p[c]-1);
		if(l>r)
			continue;
		if(cnt+(r-l+1)>=k){
			cout<<A<<" + "<<l+(k-cnt-1)-A<<" = "<<l+(k-cnt-1)<<endl;
			return;
		}
		cnt+=(r-l+1);
	}
	cout<<"-1"<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    p[0]=1;
    for(int i=1;i<=10;++i)
    	p[i]=p[i-1]*10;
    cin>>T;
	while(T--){
		cin>>a>>b>>c>>k;
		solve();
	}
	return 0;
}
```

#### 题解3：rainygame (4星)
**关键亮点**：
- 通过枚举 $a$ 的值，计算 $b$ 的范围，判断是否满足 $k$ 的要求。
- 代码中特别处理了 $b$ 的范围可能为负数的情况，避免了潜在的错误。

**核心代码**：
```cpp
#include <iostream>
using namespace std;
#define ll long long
#define int long long
#define for1(i, s, t) for (ll i(s); i<=t; ++i)
#define for2(i, t, s) for (int i(t); i>=s; --i)
#define for3(i, vec) for (auto i: vec)
#define INF 0x3f3f3f3f
#define opb pop_back
#define pb push_back
#define pf push_front
#define opf pop_front
#define fi first
#define se second

ll read(){
	ll x(0), f(1);
	char ch;
	while ((ch = getchar()) < 48) f = ch == '-' ? -1 : 1;
	do{
		x = (x << 1) + (x << 3) + (ch ^ 48);
	}while ((ch = getchar()) > 47);
	return x * f;
}

void uwrite(ll x){
	ll tmp(x/10);
	if (tmp) uwrite(tmp);
	putchar(x-(tmp<<1)-(tmp<<3)^48);
}

void write(ll x){
	if (x < 0){
		putchar('-');
		x = -x;
	}
	uwrite(x);
}

ll pow(int a, int b){
	int res(1);
	while (b--) res *= a;
	return res;
}

int A, B, C;
ll k, sum;

void solve(){
	A = read();
	B = read();
	C = read();
	k = read();
	for1(i, pow(10, A-1), pow(10, A)-1){
		sum = max(min(i+pow(10, B)-1, pow(10, C)-1)-max(i+pow(10, B-1), pow(10, C-1))+1, 0ll);
		if (k > sum) k -= sum;
		else{
			write(i);
			printf(" + ");
			write(max(i+pow(10, B-1), pow(10, C-1))+k-1-i);
			printf(" = ");
			write(max(i+pow(10, B-1), pow(10, C-1))+k-1);
			return;
		}
	}
	write(-1);
}

signed main(){
	int t(1);
	t = read();
	while (t--){
		solve();
		putchar('\n');
	}
	return 0;
}
```

### 最优关键思路
通过枚举 $a$ 的值，计算 $b$ 的范围，判断是否满足 $k$ 的要求。由于 $A, B, C$ 的最大值为 6，且大多数测试用例满足 $A, B, C \leq 3$，因此枚举的复杂度是可接受的。

### 拓展思路
类似的问题可以通过枚举一个变量，然后根据条件计算另一个变量的范围来解决。例如，在某些组合数学问题中，可以通过枚举一个参数，然后计算另一个参数的合法范围来求解。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)

---
处理用时：63.12秒