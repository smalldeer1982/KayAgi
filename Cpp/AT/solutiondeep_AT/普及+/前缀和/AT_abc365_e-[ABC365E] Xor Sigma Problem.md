# 题目信息

# [ABC365E] Xor Sigma Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc365/tasks/abc365_e

長さ $ N $ の整数列 $ A=(A_1,\ldots,A_N) $ が与えられます。次の式の値を求めてください。

$ \displaystyle\ \sum_{i=1}^{N-1}\sum_{j=i+1}^N\ (A_i\ \oplus\ A_{i+1}\oplus\ \ldots\ \oplus\ A_j) $

 ビット単位 xor とは 非負整数 $ A,\ B $ のビット単位 xor 、$ A\ \oplus\ B $ は、以下のように定義されます。 - $ A\ \oplus\ B $ を二進表記した際の $ 2^k $ ($ k\ \geq\ 0 $) の位の数は、$ A,\ B $ を二進表記した際の $ 2^k $ の位の数のうち一方のみが $ 1 $ であれば $ 1 $、そうでなければ $ 0 $ である。

 例えば、$ 3\ \oplus\ 5\ =\ 6 $ となります (二進表記すると: $ 011\ \oplus\ 101\ =\ 110 $)。  
 一般に $ k $ 個の整数 $ p_1,\ \dots,\ p_k $ の排他的論理和は $ (\cdots\ ((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \cdots\ \oplus\ p_k) $ と定義され、これは $ p_1,\ \dots,\ p_k $ の順番によらないことが証明できます。

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 10^8 $
- 入力される数値は全て整数
 
### Sample Explanation 1

$ A_1\oplus\ A_2\ =\ 2,\ A_1\ \oplus\ A_2\oplus\ A_3\ =\ 0,\ A_2\oplus\ A_3\ =\ 1 $ なので答えは $ 2+0+1=3 $ です。

## 样例 #1

### 输入

```
3

1 3 2```

### 输出

```
3```

## 样例 #2

### 输入

```
7

2 5 6 5 2 1 7```

### 输出

```
83```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述
给定一个长度为 $N$ 的整数序列 $A=(A_1,\ldots,A_N)$，求以下表达式的值：

$$
\sum_{i=1}^{N-1}\sum_{j=i+1}^N (A_i \oplus A_{i+1} \oplus \ldots \oplus A_j)
$$

其中，$\oplus$ 表示按位异或运算。

#### 说明/提示
- **异或运算定义**：对于非负整数 $A$ 和 $B$，$A \oplus B$ 的二进制表示中，每一位的值为 $1$ 当且仅当 $A$ 和 $B$ 在该位的值不同。
- **样例解释**：
  - 样例1：$A_1 \oplus A_2 = 2$，$A_1 \oplus A_2 \oplus A_3 = 0$，$A_2 \oplus A_3 = 1$，因此答案为 $2 + 0 + 1 = 3$。

#### 输入输出样例
- 样例1：
  - 输入：
    ```
    3
    1 3 2
    ```
  - 输出：
    ```
    3
    ```
- 样例2：
  - 输入：
    ```
    7
    2 5 6 5 2 1 7
    ```
  - 输出：
    ```
    83
    ```

### 题解分析与结论

#### 综合分析与结论
本题的核心是计算所有长度大于等于2的子区间的异或和之和。由于直接暴力计算的时间复杂度为 $O(N^2)$，无法通过本题的限制，因此需要优化。

大多数题解采用了**前缀异或和**的思想，将问题转化为求前缀异或和数组的两两异或和。进一步地，题解通过**按位拆分**的方法，将问题转化为对每一位的贡献进行计算，从而将时间复杂度降低到 $O(N \log \max A_i)$。

#### 最优关键思路或技巧
1. **前缀异或和**：通过维护前缀异或和数组，将区间异或和转化为两个前缀异或和的异或。
2. **按位拆分**：将问题拆分为对每一位的贡献进行计算，利用异或运算的性质，统计每一位为1的区间数。
3. **乘法原理**：利用乘法原理计算每一位的贡献，避免重复计算。

#### 推荐题目
1. [P3917 异或序列](https://www.luogu.com.cn/problem/P3917)
2. [P9236 异或和之和](https://www.luogu.com.cn/problem/P9236)
3. [CF242E XOR on Segment](https://www.luogu.com.cn/problem/CF242E)

### 高星题解精选

#### 题解1：作者：xwh_hh (赞：6)
- **星级**：5星
- **关键亮点**：
  - 使用前缀异或和将问题转化为两两异或和的计算。
  - 按位拆分，利用数组统计每一位的0和1的个数，优化了时间复杂度。
  - 代码清晰，逻辑严谨，易于理解。
- **个人心得**：
  - 赛时误将 $A_i$ 的上限看成了 $10^{18}$，导致使用了 `__int128`，赛后发现 `long long` 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline long long read(){
	long long ans=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f=-f;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		ans=(ans<<3)+(ans<<1)+c-48;
		c=getchar();
	}
	return ans*f;
} 
void write(long long x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x<10) putchar(x+48);
	else{
		write(x/10);
		putchar(x%10+48);
	}
}
long long n;
long long a[200005],b[200005];
long long g[35][2];
long long ans;
signed main(){
	n=read();
	for(long long i=1;i<=n;i++){
		a[i]=read();
		b[i]=a[i]^b[i-1];
	}
	for(long long i=0;i<=28;i++) g[i][0]++;//将b[0]加进去 
	for(long long i=1;i<=n;i++){
		for(long long j=0;j<=28;j++){
			ans+=g[j][bool((b[i])&(1<<j))^1]*(1<<j);//按位统计答案 
		}
		for(long long j=0;j<=28;j++){
			g[j][bool((b[i])&(1<<j))]++;//按位更新g数组 
		}
	}
	for(long long i=1;i<=n;i++) ans-=a[i];//除去长度为1的区间 
	write(ans);
	return 0;
}
```

#### 题解2：作者：Sorato_ (赞：4)
- **星级**：4星
- **关键亮点**：
  - 倒序枚举，利用异或性质反转贡献。
  - 维护每一位的0和1的个数，统计贡献。
  - 代码简洁，逻辑清晰。
- **个人心得**：
  - 通过倒序枚举，简化了贡献的计算。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
	short f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')	{if(c=='-')	f=-1;c=getchar();}
	while(c>='0'&&c<='9')	x=(x<<1)+(x<<3)+(c^48),c=getchar();
	return x*f;
}
const int N=2e5+10;
int n,a[N],ans,cnt[35][2];
signed main()
{
	n=read();
	for(int i=1;i<=n;i=-~i)	a[i]=read();
	for(int i=n;i;i--)
	{
		for(int j=30;j>=0;j--)
			ans+=cnt[j][(a[i]>>j&1)^1]*(1<<j);
		for(int j=30;j>=0;j--)
		{
			if(a[i]>>j&1)	swap(cnt[j][1],cnt[j][0]);
			cnt[j][a[i]>>j&1]++;
		}
	}
	return printf("%lld",ans),0;
}
```

#### 题解3：作者：Special_Tony (赞：4)
- **星级**：4星
- **关键亮点**：
  - 按位拆解，利用异或性质反转贡献。
  - 代码简洁，逻辑清晰。
- **个人心得**：
  - 通过按位拆解，简化了贡献的计算。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int n, x, s[35];
ll sum;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		cin >> x, sum -= x;
		for (int j = 0; j < 30; ++ j) {
			if (x >> j & 1)
				s[j] = i - s[j];
			sum += ((ll) s[j]) << j;
		}
	}
	cout << sum;
	return 0;
}
```

---
处理用时：64.89秒