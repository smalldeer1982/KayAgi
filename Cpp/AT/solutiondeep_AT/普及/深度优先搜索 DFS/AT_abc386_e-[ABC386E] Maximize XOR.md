# 题目信息

# [ABC386E] Maximize XOR

## 题目描述

给定一个长度为 $N$ 的非负整数序列 $A$ 和一个整数 $K$。保证二项式系数 $\dbinom{N}{K} \leq 10^6$。

从序列 $A$ 中选择 $K$ 个不同的元素，求出这些元素的异或和的最大值。

简单来说，就是求 $\underset{1 \leq i_1 < i_2 < \ldots < i_K \leq N}{\max} A_{i_1} \oplus A_{i_2} \oplus \ldots \oplus A_{i_K}$。

在这里，异或运算（XOR）是这样定义的：对于两个非负整数 $A$ 和 $B$，其结果 $A \oplus B$ 是一个二进制数，对于每个 $2^k \ (k \geq 0)$ 位，如果 $A$ 和 $B$ 在这一位中恰好只有一个是 $1$，则结果在这一位是 $1$，否则为 $0$。

举个例子：$3 \oplus 5 = 6$，在二进制下：$011 \oplus 101 = 110$。通常来说，$k$ 个整数 $p_1, \dots, p_k$ 的异或值可以表示为 $(\cdots ((p_1 \oplus p_2) \oplus p_3) \oplus \cdots \oplus p_k)$，并且顺序不会影响结果。

## 说明/提示

- $1 \leq K \leq N \leq 2 \times 10^5$
- $0 \leq A_i < 2^{60}$
- $\dbinom{N}{K} \leq 10^6$
- 所有输入均为整数

### 示例解释 1

从 $(3, 2, 6, 4)$ 中选出任意两个不同的数，有以下六种组合方式：
- 选择 $(3, 2)$：异或值为 $3 \oplus 2 = 1$。
- 选择 $(3, 6)$：异或值为 $3 \oplus 6 = 5$。
- 选择 $(3, 4)$：异或值为 $3 \oplus 4 = 7$。
- 选择 $(2, 6)$：异或值为 $2 \oplus 6 = 4$。
- 选择 $(2, 4)$：异或值为 $2 \oplus 4 = 6$。
- 选择 $(6, 4)$：异或值为 $6 \oplus 4 = 2$。

因此，最大异或值为 $7$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 2
3 2 6 4```

### 输出

```
7```

## 样例 #2

### 输入

```
10 4
1516 1184 1361 2014 1013 1361 1624 1127 1117 1759```

### 输出

```
2024```

# AI分析结果

### 题目翻译

【题目内容】
# [ABC386E] Maximize XOR

## 题目描述

给定一个长度为 $N$ 的非负整数序列 $A$ 和一个整数 $K$。保证二项式系数 $\dbinom{N}{K} \leq 10^6$。

从序列 $A$ 中选择 $K$ 个不同的元素，求出这些元素的异或和的最大值。

简单来说，就是求 $\underset{1 \leq i_1 < i_2 < \ldots < i_K \leq N}{\max} A_{i_1} \oplus A_{i_2} \oplus \ldots \oplus A_{i_K}$。

在这里，异或运算（XOR）是这样定义的：对于两个非负整数 $A$ 和 $B$，其结果 $A \oplus B$ 是一个二进制数，对于每个 $2^k \ (k \geq 0)$ 位，如果 $A$ 和 $B$ 在这一位中恰好只有一个是 $1$，则结果在这一位是 $1$，否则为 $0$。

举个例子：$3 \oplus 5 = 6$，在二进制下：$011 \oplus 101 = 110$。通常来说，$k$ 个整数 $p_1, \dots, p_k$ 的异或值可以表示为 $(\cdots ((p_1 \oplus p_2) \oplus p_3) \oplus \cdots \oplus p_k)$，并且顺序不会影响结果。

## 说明/提示

- $1 \leq K \leq N \leq 2 \times 10^5$
- $0 \leq A_i < 2^{60}$
- $\dbinom{N}{K} \leq 10^6$
- 所有输入均为整数

### 示例解释 1

从 $(3, 2, 6, 4)$ 中选出任意两个不同的数，有以下六种组合方式：
- 选择 $(3, 2)$：异或值为 $3 \oplus 2 = 1$。
- 选择 $(3, 6)$：异或值为 $3 \oplus 6 = 5$。
- 选择 $(3, 4)$：异或值为 $3 \oplus 4 = 7$。
- 选择 $(2, 6)$：异或值为 $2 \oplus 6 = 4$。
- 选择 $(2, 4)$：异或值为 $2 \oplus 4 = 6$。
- 选择 $(6, 4)$：异或值为 $6 \oplus 4 = 2$。

因此，最大异或值为 $7$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
4 2
3 2 6 4```

### 输出

```
7```

## 样例 #2

### 输入

```
10 4
1516 1184 1361 2014 1013 1361 1624 1127 1117 1759```

### 输出

```
2024```

### 题解分析与结论

该题的核心在于从给定的序列中选择 $K$ 个元素，使得它们的异或和最大。由于 $\dbinom{N}{K} \leq 10^6$，直接暴力搜索是可行的，但需要优化以避免超时。大部分题解都采用了深度优先搜索（DFS）结合剪枝的策略，通过预处理后缀异或和来优化搜索过程。

### 所选高分题解

#### 1. 作者：_anll_ (5星)
- **关键亮点**：通过预处理后缀异或和，优化了搜索过程，避免了不必要的递归。代码简洁，思路清晰。
- **个人心得**：通过观察数据范围，意识到直接搜索会超时，因此通过剪枝和预处理后缀异或和来优化搜索。

```cpp
#include<iostream>
#define int long long
using namespace std;
const int N=2e5+5;
int n,k,num[N],hzh[N],ans;
void dfs(int x,int c,int a){
	if(!c){ans=max(ans,a);return;}
	if(x>n||c+x-1>n) return;
	if(c+x-1==n)
		return void(ans=max(ans,a^hzh[x]));
	dfs(x+1,c-1,a^num[x]);
	dfs(x+1,c,a);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>num[i];
	for(int i=n;i>=1;i--) hzh[i]=(hzh[i+1]^num[i]);
	dfs(1,k,0);cout<<ans;
	return 0;
}
```

#### 2. 作者：sjh0626 (4星)
- **关键亮点**：通过预处理后缀异或和，优化了搜索过程，避免了不必要的递归。代码简洁，思路清晰。
- **个人心得**：通过观察数据范围，意识到直接搜索会超时，因此通过剪枝和预处理后缀异或和来优化搜索。

```cpp
#include<bits/stdc++.h>
#define sjh0626s return
#define code 0
#define ll long long
using namespace std;
class FastIO{
	public:
	inline ll read(){
		ll x=0,f=1;char ch=getchar();
		while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
		while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
		return x*f;
	}
	FastIO &operator>>(ll &x){
		x=read();
		return *this;
	}
};
FastIO qin;
ll n,k,a[300010],s[300010],ans;
void dfs(ll now,ll rest,ll sum){
	if(rest==0){ //搜完了 
		ans=max(ans,sum);
		return ;
	}
	if(now+rest-1==n){ //包括自己剩下 k 个数 
		ans=max(ans,sum^s[now]); //直接比较 
		return;
	}
	dfs(now+1,rest,sum); //选择 
	dfs(now+1,rest-1,sum^a[now]); //不选择 
}
int main(){
	qin>>n>>k;
	for(int i=1;i<=n;i++){
		qin>>a[i];
	}
	for(int i=n;i>=1;i--)s[i]=s[i+1]^a[i];
	dfs(1,k,0);
	cout<<ans; 
	sjh0626s code;
}
```

#### 3. 作者：wht_1218 (4星)
- **关键亮点**：通过预处理后缀异或和，优化了搜索过程，避免了不必要的递归。代码简洁，思路清晰。
- **个人心得**：通过观察数据范围，意识到直接搜索会超时，因此通过剪枝和预处理后缀异或和来优化搜索。

```cpp
#ifndef _CPP_FILE
#define _CPP_FILE
#include<bits/stdc++.h>
#define int long long 
#pragma GCC optimize("Ofast")
using namespace std;
const int N=1e6+7;
#define il inline
#define re register
#define rei register int
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
//#define abs(x) (x>0?x:-x)
inline int abs(auto x){
	return x>0?x:-x;
}
#define imx INT_MAX
#define imn INT_MIN
#define lmx LLONG_MAX
#define lmn LLONG_MIN
#define nmx (N)
#define nmn (-N)
#define umap unordered_map
#define pii pair<int,int>
#define mset multiset

/**/
int n,m,S;
long long a[N],p1[N],p2[N],ans=0;
inline void dfs(register int x,register long long ansn,register int cnt){
	if(cnt>m||cnt+n-x+1<m)return;
	if(x>n){
		cnt==m?ans=max(ans,ansn):0;
		return;
	}
	if(n-x+cnt+1==m)return dfs(n+1,ansn^p2[x],m);
	cnt==m?dfs(n+1,ansn,cnt):(cnt>0?dfs(x+1,ansn^a[x],cnt+1):dfs(x+1,a[x],cnt+1));
	cnt!=m?dfs(x+1,ansn,cnt):void();
	return;
} 
main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(register int i=1;i<=n;++i)cin>>a[i];
	p1[0]=0;
	p1[1]=a[1];
	p2[n]=a[n];
	p2[n+1]=0;
	for(int i=2;i<=n;++i)p1[i]=p1[i-1]^a[i];
	for(int i=n-1;i;--i)p2[i]=p2[i+1]^a[i];
	dfs(1,0,0);
	cout<<ans;
	return 0; 
}
#endif
```

### 最优关键思路或技巧

1. **预处理后缀异或和**：通过预处理后缀异或和，可以在搜索过程中快速计算剩余元素的异或和，避免了重复计算。
2. **剪枝优化**：在搜索过程中，通过判断剩余元素的数量是否足够选择 $K$ 个元素，提前终止不必要的递归，从而优化搜索效率。
3. **正难则反**：当 $K$ 较大时，选择不选 $N-K$ 个元素，利用异或的性质简化计算。

### 拓展思路

类似的问题可以通过预处理和剪枝来优化搜索过程，特别是在组合数较小的情况下。对于异或和最大化的问题，还可以考虑使用贪心算法或动态规划来进一步优化。

### 推荐题目

1. [P3811 【模板】乘法逆元](https://www.luogu.com.cn/problem/P3811)
2. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
3. [P3374 【模板】树状数组 1](https://www.luogu.com.cn/problem/P3374)

---
处理用时：80.52秒