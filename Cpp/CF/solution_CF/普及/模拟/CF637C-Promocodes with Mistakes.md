# Promocodes with Mistakes

## 题目描述

在一个新年特价销售期间，苏迪斯拉夫酒吧提供了 n 个促销代码。每个促销代码包括准确的六位数字，并且能在“蚊子庇护所”免费享用一杯鸡尾酒。当然，所有的促销代码都是不尽相同的。
  
  因为“蚊子庇护所”从九点才开始营业，而苏迪斯拉夫酒吧的派对最早往往六点就开始了，所以关于怎样输入准确无误的促销代码，就有可能会出现许多问题。那么就非常有必要确立一个最大值 k，使得如果促销代码的错误不超过 k 个，这个促销代码就是独一无二的。特别地，$k=0$ 表示所有的促销代码都必须准确无误地被输入。
  
  一个错误指输入了一个错误的号码。比如说，代码“123465”对于代码“123456”来说有两个错误。无论代码的错误共有多少个，代码都由六位数字组成。

## 样例 #1

### 输入

```
2
000000
999999
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
211111
212111
222111
111111
112111
121111
```

### 输出

```
0
```

# 题解

## 作者：xiaoxiaoxia (赞：0)

## 思路概述
这题其实难度不大，完全就是可以暴力水过，大致思路就是以 $dis(s_i,s_j)$ 表示 $s_i$ 和 $s_j$ 不同的数量，那么对于任意 $s_i$ 和 $s_j$，一个不合法的k会使得存在 $x$ 满足 $dis(s_i,x) \leq k,dis(s_j,x) \leq k$，进而 $dis(s_i,s_j) \leq dis(s_i,x)+dis(s_j,x) \leq 2 \times k$，故 $k \ge (dis(s_i,s_j)+1) \div 2$，那么合法的 $k$ 就是 $k \leq (dis(s_i,s_j)-1) \div 2$，故对每个 $i,j$，更新 $(dis(s_i,s_j)-1) \div 2$ 的最小值即为答案。
## 代码部分

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 0x3f3f3f3f
#define maxn 1005
int n;
string s[maxn];
int get(string a,string b)
{
	int ans=0;
	for(int i=0;i<6;i++)
		if(a[i]!=b[i])ans++;
	return ans;
}
int main()
{
	while(~scanf("%d",&n))
	{
		for(int i=1;i<=n;i++)
			cin>>s[i];
		int ans=6;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++)
				ans=min(ans,(get(s[i],s[j])-1)/2);
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：QWQ_123 (赞：0)

考虑找到每两组字符串最少不同使得他们匹配不上。

那么考虑按照样例一的方法，奇偶交替，如果有奇数个不同的，就再放一个和这一位上所有的数都不同即可。

比如这两个数字是：$\texttt{100100}$ 和 $\texttt{101010}$。

那么使得他们不匹配最小的 $k$ 是 $2$ 对应字符串：$\texttt{101020}$。

```cpp
#include <bits/stdc++.h>

using namespace std;

int n;
string s[1010];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> s[i];

	int ans = 6;

	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			int cnt = 0;
			for (int k = 0; k < 6; ++k) {
				if (s[i][k] != s[j][k]) ++cnt;
			}

			if (cnt & 1) ans = min(ans, (cnt - 1) / 2);//奇数，要额外放一个，所以不用 - 1
			else ans = min(ans, cnt / 2 - 1);//偶数
		}
	}

	printf("%d\n", ans);

	return 0;
}
```

---

