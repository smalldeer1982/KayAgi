# 题目信息

# [ARC140C] ABS Permutation (LIS ver.)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc140/tasks/arc140_c

$ (1,\dots,N) $ の順列 $ P=(P_1,P_2,\ldots,P_N) $ の**嬉しさ**を以下で定義します。

- 長さ $ N-1 $ の数列 $ A=(A_1,A_2,\ldots,A_{N-1}) $ を、$ A_i\ =\ |P_i-P_{i+1}|(1\leq\ i\ \leq\ N-1) $ で定める。 $ A $ の最長狭義単調増加部分列の長さを $ P $ の嬉しさとする。

$ P_1\ =\ X $ を満たす順列 $ P $ のうち、嬉しさが最大になるものを一つ出力してください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 1\ \leq\ X\ \leq\ N $
- 入力は全て整数

### Sample Explanation 1

$ A=(1,2) $ となるので、$ P $ の嬉しさは $ 2 $ です。これが達成可能な嬉しさの最大であるため、出力は条件を満たします。

### Sample Explanation 2

$ A=(1,1) $ となるので、$ P $ の嬉しさは $ 1 $ です。これが達成可能な嬉しさの最大であるため、出力は条件を満たします。

## 样例 #1

### 输入

```
3 2```

### 输出

```
2 1 3```

## 样例 #2

### 输入

```
3 1```

### 输出

```
1 2 3```

# AI分析结果

### 题目内容重写

**题目描述**

给定一个长度为 \( N \) 的排列 \( P = (P_1, P_2, \ldots, P_N) \)，定义其**嬉しさ**为：

- 构造一个长度为 \( N-1 \) 的数列 \( A = (A_1, A_2, \ldots, A_{N-1}) \)，其中 \( A_i = |P_i - P_{i+1}| \)（\( 1 \leq i \leq N-1 \)）。
- \( P \) 的嬉しさ为 \( A \) 的最长严格递增子序列的长度。

要求输出一个满足 \( P_1 = X \) 的排列 \( P \)，使得其嬉しさ最大。

**输入格式**

输入包含两个整数 \( N \) 和 \( X \)。

**输出格式**

输出一个满足条件的排列 \( P \)。

**样例 1**

输入：
```
3 2
```
输出：
```
2 1 3
```

**样例 2**

输入：
```
3 1
```
输出：
```
1 2 3
```

**说明/提示**

- \( 2 \leq N \leq 2 \times 10^5 \)
- \( 1 \leq X \leq N \)
- 输入均为整数

### 算法分类
构造

### 题解分析与结论

本题的核心在于如何构造一个排列 \( P \)，使得其对应的 \( A \) 数组的最长严格递增子序列长度最大。题解中多位作者提出了不同的构造方法，主要集中在如何通过交替排列元素来最大化 \( A \) 的 LIS 长度。

### 所选高星题解

#### 题解作者：fengxiaoyi (4星)
**关键亮点**：
- 提出了一个简洁的构造思路，通过将 \( X \) 放在排列的开头，然后交替排列剩余元素，使得 \( A \) 的 LIS 长度最大化。
- 代码实现清晰，逻辑简单，易于理解。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
inline ll read(){
	ll res=0ll,f=1;
	char c;
	for(;(c=getchar())<'0'||c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9') res=(res<<1) + (res<<3) + c-'0',c=getchar();
	return res*f;
}
inline ll Max(re ll x,re ll y){return x>y?x:y;}
inline ll Min(re ll x,re ll y){return x<y?x:y;}
inline void cmax(re auto &x,re auto y){x=Max(x,y);}
inline void cmin(re auto &x,re auto y){x=Min(x,y);}
/*-----------------*/
const int N=2e5+10;
int n,x,a[N];
int main(){
	n=read();x=read();a[1]=x;
	if(n&1){
		if((n+1)/2==x){
			for(re int i=x-1,j=2;i;i--,j+=2) a[j]=i;
			for(re int i=x+1,j=3;i<=n;i++,j+=2) a[j]=i;
		}
		else if(x<(n+1)/2){
			a[2]=(n+1)/2;
			for(re int i=a[2]+1,j=3;i<=n;i++,j+=2) a[j]=i;
			for(re int i=a[2]-1,j=4;i;i--,j+=2){
				if(i==x) i--;
				if(i) a[j]=i;
				else break;
			}
		}
		else if(x>(n+1)/2){
			a[2]=(n+1)/2;
			for(re int i=a[2]-1,j=3;i;i--,j+=2) a[j]=i;
			for(re int i=a[2]+1,j=4;i<=n;i++,j+=2){
				if(i==x) i++;
				a[j]=i;
			}
		}
	}
	else{
		if(n/2==x){
			for(re int i=x+1,j=2;i<=n;i++,j+=2) a[j]=i;
			for(re int i=x-1,j=3;i;i--,j+=2) a[j]=i;
		}
		else if(n/2+1==x){
			for(re int i=x-1,j=2;i;i--,j+=2) a[j]=i;
			for(re int i=x+1,j=3;i<=n;i++,j+=2) a[j]=i;
		}
		else if(x<n/2){
			a[2]=n/2+1;
			for(re int i=a[2]-1,j=3;i;i--,j+=2){
				if(i==x) i--;
				if(i) a[j]=i;
				else break;
			}
			for(re int i=a[2]+1,j=4;i<=n;i++,j+=2) a[j]=i;
		}
		else{
			a[2]=n/2;
			for(re int i=a[2]+1,j=3;i<=n;i++,j+=2){
				if(i==x) i++;
				a[j]=i;
			}
			for(re int i=a[2]-1,j=4;i;i--,j+=2) a[j]=i;
		}
	}
	for(re int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
```

#### 题解作者：HasNoName (4星)
**关键亮点**：
- 通过对 \( N \) 的奇偶性进行分类讨论，提出了不同的构造方法。
- 代码结构清晰，逻辑严谨，适用于大规模数据。

**核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int a[N];
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,m;
	cin>>n>>m;
	if(n&1){
		int u=n/2+1;
		if(m==u){
			int t=u;
			for(int i=1;i<=n;i+=2)a[i]=t++;
			t=u-1;
			for(int i=2;i<=n;i+=2)a[i]=t--;
		}
		else{
			a[1]=m;
			if(m<u){
				int t=u+1;
				for(int i=3;i<=n;i+=2)a[i]=t++;
				t=u+1;
				for(int i=2;i<=n;i+=2){
					t--;
					if(t==m)t--;
					a[i]=t;
				}
			}
			else{
				int t=u-1;
				for(int i=2;i<=n;i+=2){
					t++;
					if(t==m)t++;
					a[i]=t;
				}
				t=u-1;
				for(int i=3;i<=n;i+=2)a[i]=t--;
			}
		}
	}
	else{
		int u=n/2;
		if(m==u){
			int t=u;
			for(int i=1;i<=n;i+=2)a[i]=t--;
			t=u+1;
			for(int i=2;i<=n;i+=2)a[i]=t++;
		}
		else if(m==u+1){
			int t=u+1;
			for(int i=1;i<=n;i+=2)a[i]=t++;
			t=u;
			for(int i=2;i<=n;i+=2)a[i]=t--;
		}
		else{
			a[1]=m;
			if(m<u){
				int t=u+1;
				for(int i=2;i<=n;i+=2)a[i]=t++;
				t=u+1;
				for(int i=3;i<=n;i+=2){
					t--;
					if(t==m)t--;
					a[i]=t;
				}
			}
			else{
				int t=u;
				for(int i=3;i<=n;i+=2){
					t++;
					if(t==m)t++;
					a[i]=t;
				}
				t=u;
				for(int i=2;i<=n;i+=2)a[i]=t--;
			}
		}
	}
	for(int i=1;i<=n;i++)cout<<a[i]<<' ';
	cout<<'\n';
	return 0;
}
```

### 最优关键思路或技巧
- **交替排列**：通过将剩余元素交替排列，可以最大化 \( A \) 的 LIS 长度。
- **分类讨论**：根据 \( N \) 的奇偶性和 \( X \) 的位置，采用不同的构造策略。

### 可拓展之处
- 类似题目可以通过交替排列元素来构造最优解，如最大化或最小化某些特定序列的性质。

### 推荐题目
1. [P1008 三连击](https://www.luogu.com.cn/problem/P1008)
2. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)
3. [P1028 数的计算](https://www.luogu.com.cn/problem/P1028)

### 个人心得摘录
- **fengxiaoyi**：通过将 \( X \) 放在开头，然后交替排列剩余元素，可以有效地构造出最优解。
- **HasNoName**：分类讨论 \( N \) 的奇偶性，能够更好地处理不同情况下的构造问题。

---
处理用时：62.82秒