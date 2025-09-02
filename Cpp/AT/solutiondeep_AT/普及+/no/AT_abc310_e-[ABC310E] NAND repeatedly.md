# 题目信息

# [ABC310E] NAND repeatedly

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc310/tasks/abc310_e

`0` と `1` からなる長さ $ N $ の文字列 $ S $ が与えられます。 $ S $ は長さ $ N $ の数列 $ A=(A\ _\ 1,A\ _\ 2,\ldots,A\ _\ N) $ の情報を表しており、$ S $ の $ i $ 文字目 $ (1\leq\ i\leq\ N) $ が `0` のとき $ A\ _\ i=0 $ 、`1` のとき $ A\ _\ i=1 $です。

\\\[\\sum \_ {1\\leq i\\leq j\\leq N}(\\cdots((A \_ i\\barwedge A \_ {i+1})\\barwedge A \_ {i+2})\\barwedge\\cdots\\barwedge A \_ j)\\\]

を求めてください。

より厳密には、次のように定められる $ f(i,j)\ (1\leq\ i\leq\ j\leq\ N) $ に対して $ \displaystyle\sum\ _\ {i=1}\ ^\ {N}\sum\ _\ {j=i}\ ^\ Nf(i,j) $ を求めてください。

\\\[f(i,j)=\\left\\{\\begin{matrix} A \_ i&amp;(i=j)\\\\ f(i,j-1)\\barwedge A \_ j\\quad&amp;(i\\lt j) \\end{matrix}\\right.\\\]

ただし、否定論理積 $ \barwedge $ は次を満たす二項演算子です。

\\\[0\\barwedge0=1,0\\barwedge1=1,1\\barwedge0=1,1\\barwedge1=0\\\]

## 说明/提示

### 制約

- $ 1\leq\ N\leq10^6 $
- $ S $ は `0` と `1` からなる長さ $ N $ の文字列
- 入力はすべて整数
 
### Sample Explanation 1

$ 1\leq\ i\leq\ j\leq\ N $ を満たすすべての組 $ (i,j) $ に対して、$ f(i,j) $ の値は以下のようになります。 - $ f(1,1)=0=0 $ - $ f(1,2)=0\barwedge0=1 $ - $ f(1,3)=(0\barwedge0)\barwedge1=0 $ - $ f(1,4)=((0\barwedge0)\barwedge1)\barwedge1=1 $ - $ f(1,5)=(((0\barwedge0)\barwedge1)\barwedge1)\barwedge0=1 $ - $ f(2,2)=0=0 $ - $ f(2,3)=0\barwedge1=1 $ - $ f(2,4)=(0\barwedge1)\barwedge1=0 $ - $ f(2,5)=((0\barwedge1)\barwedge1)\barwedge0=1 $ - $ f(3,3)=1=1 $ - $ f(3,4)=1\barwedge1=0 $ - $ f(3,5)=(1\barwedge1)\barwedge0=1 $ - $ f(4,4)=1=1 $ - $ f(4,5)=1\barwedge0=1 $ - $ f(5,5)=0=0 $ これらの総和は $ 0+1+0+1+1+0+1+0+1+1+0+1+1+1+0=9 $ なので、$ 9 $ を出力してください。 $ \barwedge $ は結合法則を満たさないことに注意してください。 例えば、$ (1\barwedge1)\barwedge0=0\barwedge0=1\neq0=1\barwedge1=1\barwedge(1\barwedge0) $ です。

## 样例 #1

### 输入

```
5

00110```

### 输出

```
9```

## 样例 #2

### 输入

```
30

101010000100101011010011000010```

### 输出

```
326```

# AI分析结果

### 题目内容重写
给定一个长度为 $N$ 的由 `0` 和 `1` 组成的字符串 $S$，$S$ 表示一个长度为 $N$ 的数列 $A=(A_1,A_2,\ldots,A_N)$，其中 $S$ 的第 $i$ 个字符为 `0` 时 $A_i=0$，为 `1` 时 $A_i=1$。

求：
\\\[\\sum \_ {1\\leq i\\leq j\\leq N}(\\cdots((A \_ i\\barwedge A \_ {i+1})\\barwedge A \_ {i+2})\\barwedge\\cdots\\barwedge A \_ j)\\\]

其中，$\barwedge$ 表示否定逻辑积（NAND），其定义如下：
\\\[0\\barwedge0=1,0\\barwedge1=1,1\\barwedge0=1,1\\barwedge1=0\\\]

### 算法分类
动态规划

### 题解分析与结论
本题的核心是通过动态规划来高效计算所有子区间的 NAND 结果。由于直接暴力计算的复杂度为 $O(N^2)$，无法通过 $N=10^6$ 的数据范围。因此，题解中普遍采用了动态规划的思路，通过维护当前子区间的 NAND 结果来优化计算。

### 精选题解
#### 1. 作者：Pt_crN (5星)
**关键亮点**：
- 通过维护当前子区间的 NAND 结果，简洁高效地计算了所有子区间的贡献。
- 代码简洁，逻辑清晰，适合初学者理解动态规划的基本思想。

**核心代码**：
```cpp
int n,m;
char s[N];
void solve(){
	scanf("%d%s",&n,s+1);
	ll ans=0;
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='1')
			cnt=i-cnt;
		else 
			cnt=i-1;
		ans+=cnt;
	}
	printf("%lld\n",ans);
}
```
**核心思想**：
- 通过 `cnt` 变量记录当前子区间的 NAND 结果，根据当前字符是 `0` 还是 `1` 更新 `cnt`，并累加到答案中。

#### 2. 作者：_Richardguo_ (4星)
**关键亮点**：
- 通过两个计数器 `cnt0` 和 `cnt1` 分别记录当前子区间的 NAND 结果为 `0` 和 `1` 的数量，进一步优化了计算。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	int n;
	cin>>n;
	ll cnt0=0,cnt1=0,ans=0;
	for(int i=1;i<=n;i++){
		char s;cin>>s;
		if(s=='0'){
			cnt1+=cnt0;
			cnt0=1;
		}
		else swap(cnt0,cnt1),cnt1++;
		ans+=cnt1;
	} 
	cout<<ans<<"\n";
	return 0;
}
```
**核心思想**：
- 使用 `cnt0` 和 `cnt1` 分别记录当前子区间的 NAND 结果为 `0` 和 `1` 的数量，根据当前字符更新这两个计数器，并累加到答案中。

#### 3. 作者：Coffee_zzz (4星)
**关键亮点**：
- 通过定义 `dp` 数组来记录以当前字符结尾的子区间的 NAND 结果，进一步优化了计算。
- 代码结构清晰，适合有一定动态规划基础的读者。

**核心代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],dp[N][2];
signed main(){
	int n,ans=0;
	string s;
	cin>>n>>s;
	for(int i=1;i<=n;i++) a[i]=s[i-1]-'0';
	if(a[1]==0) dp[1][0]=1;
	else dp[1][1]=1;
	for(int i=2;i<=n;i++){
		if(a[i]==0){
			dp[i][1]=dp[i-1][0]+dp[i-1][1];
			dp[i][0]=1;
		}
		else{
			dp[i][1]=dp[i-1][0]+1;
			dp[i][0]=dp[i-1][1];
		}
	}
	for(int i=1;i<=n;i++) ans=ans+dp[i][1];
	cout<<ans<<endl;
	return 0;
}
```
**核心思想**：
- 使用 `dp[i][0]` 和 `dp[i][1]` 分别记录以第 $i$ 个字符结尾的子区间的 NAND 结果为 `0` 和 `1` 的数量，根据当前字符更新 `dp` 数组，并累加到答案中。

### 最优关键思路
通过动态规划维护当前子区间的 NAND 结果，并根据当前字符更新状态，从而高效计算所有子区间的贡献。这种方法的时间复杂度为 $O(N)$，能够通过 $N=10^6$ 的数据范围。

### 可拓展之处
类似的问题可以通过动态规划来优化计算，尤其是在处理子区间问题时，动态规划是一种常用的高效方法。

### 推荐题目
1. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)

---
处理用时：40.49秒