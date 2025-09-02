# Sakurako's Box

## 题目描述

Sakurako 有一个装满 $n$ 个球的盒子。每个球都有自己的数值。她想和朋友打个赌，朋友如果从盒子中随机选出两个球（可以是不同的两球，即使它们有相同的数值），这两个球数值的乘积能够等于 Sakurako 事先猜测到的一个数。

因为 Sakurako 是概率学方面的专家，她知道最明智的猜测应该是[期望值](http://tiny.cc/matozh_en)，但她忘了如何去计算。请帮助她计算出这个数组中任意两个元素乘积的期望值。

可以证明，该期望值的形式为 $\frac{P}{Q}$，其中 $P$ 和 $Q$ 是非负整数，且 $Q \ne 0$。你需要计算并输出 $P \cdot Q^{-1} \bmod (10^9+7)$ 的结果。

## 说明/提示

举个例子：
- 在第一个测试用例中，Sakurako 的朋友可以选择这些球对：$(a_1, a_2)$、$(a_1, a_3)$ 和 $(a_2, a_3)$。它们的乘积分别是 $3 \times 2 = 6$、$3 \times 3 = 9$ 和 $3 \times 2 = 6$，所以期望值计算结果为 $\frac{6 + 9 + 6}{3} = 7$。

- 在第二个测试用例中，朋友可以选择的球对有：$(a_1, a_2)$、$(a_1, a_3)$、$(a_1, a_4)$、$(a_2, a_3)$、$(a_2, a_4)$ 和 $(a_3, a_4)$。它们的乘积分别为 $2 \times 2 = 4$、$2 \times 2 = 4$、$2 \times 4 = 8$、$2 \times 2 = 4$、$2 \times 4 = 8$ 和 $2 \times 4 = 8$，所以期望值为 $\frac{4 + 4 + 8 + 4 + 8 + 8}{6} = \frac{36}{6} = 6$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
3
3 2 3
4
2 2 2 4
5
1 2 3 4 5```

### 输出

```
7
6
500000012```

# 题解

## 作者：Super_Cube (赞：4)

# Solution

题目也就是求 $\dfrac{2\sum\limits_{i=1}^n\sum\limits_{j=i+1}^n a_ia_j}{n(n-1)}$。

分母是定值先不管。对于 $j$ 造成的贡献为 $a_j\displaystyle\sum_{i=1}^{j-1}a_i$，于是枚举 $j$ 并对 $a$ 做前缀和就能快速计算分子。最后求个分母的逆元就结束了。

# Code

```cpp
#include<bits/stdc++.h>
const int mod=1e9+7;
inline int qpow(int x,int y){
	static int res;res=1;
	while(y){
		if(y&1)res=1ll*res*x%mod;
		y>>=1;
		x=1ll*x*x%mod;
	}
	return res;
}
int T,n,s,ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&s);
		ans=0;
		for(int i=1,x;i<n;++i)
			scanf("%d",&x),ans=(ans+1ll*x*s)%mod,(s+=x)<mod?0:s-=mod;
		printf("%d\n",1ll*ans*qpow((n*(n-1ll)>>1)%mod,mod-2)%mod);
	}
	return 0;
}
```

---

## 作者：Drifty (赞：1)

### Preface

感觉这题[官解](https://codeforces.com/blog/entry/133509)想麻烦了。

### Solution

我们注意到分母即为 $\frac{n(n - 1)}{2}$，直接费马小定理算[逆元](https://oi-wiki.org/math/number-theory/inverse/)最后再乘上即可。

难点在于处理分子。但实际上这并不困难。

我们考虑对于每一个 $a_i$ 产生的贡献为 $a_i\sum_{j = 1}^{i - 1} a_j$。那么总贡献（分子）即为：

$$
\sum_{i = 1}^n\sum_{j = i + 1}^n a_i a_j=\sum_{i=1}^{n} \left (a_i \sum_{j = 1}^{i - 1} a_j \right )
$$

那么前缀和维护即可。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr i64 P = 1e9 + 7;
int T, n;
auto inv = [](i64 a, i64 x = P - 2) {
	i64 ans = 1;
	for (; x; x >>= 1, a = 1ll * a * a % P)
		if (x & 1) ans = 1ll * ans * a % P;
	return ans;
};
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL), cout.tie(NULL);
	cin >> T;
	for (; T--; ) {
		i64 ret = 0, s = 0;
		cin >> n >> s;
		for (int i = 1, x; i < n; i ++) 
			cin >> x, ret = (ret + s * x) % P, s = (s + x) % P;
		cout << ret * inv(1ll * n * (n - 1) / 2 % P) % P << '\n';
	}
	return 0;
}
```

---

