# 题目信息

# Sum on Subarrays

## 题目描述

For an array $ a = [a_1, a_2, \dots, a_n] $ , let's denote its subarray $ a[l, r] $ as the array $ [a_l, a_{l+1}, \dots, a_r] $ .

For example, the array $ a = [1, -3, 1] $ has $ 6 $ non-empty subarrays:

- $ a[1,1] = [1] $ ;
- $ a[1,2] = [1,-3] $ ;
- $ a[1,3] = [1,-3,1] $ ;
- $ a[2,2] = [-3] $ ;
- $ a[2,3] = [-3,1] $ ;
- $ a[3,3] = [1] $ .

You are given two integers $ n $ and $ k $ . Construct an array $ a $ consisting of $ n $ integers such that:

- all elements of $ a $ are from $ -1000 $ to $ 1000 $ ;
- $ a $ has exactly $ k $ subarrays with positive sums;
- the rest $ \dfrac{(n+1) \cdot n}{2}-k $ subarrays of $ a $ have negative sums.

## 样例 #1

### 输入

```
4
3 2
2 0
2 2
4 6```

### 输出

```
1 -3 1
-13 -42
-13 42
-3 -4 10 -2```

# AI分析结果

### 题目内容重写
# 子数组和

## 题目描述

对于一个数组 $ a = [a_1, a_2, \dots, a_n] $，我们定义其子数组 $ a[l, r] $ 为数组 $ [a_l, a_{l+1}, \dots, a_r] $。

例如，数组 $ a = [1, -3, 1] $ 有 $ 6 $ 个非空子数组：

- $ a[1,1] = [1] $ ;
- $ a[1,2] = [1,-3] $ ;
- $ a[1,3] = [1,-3,1] $ ;
- $ a[2,2] = [-3] $ ;
- $ a[2,3] = [-3,1] $ ;
- $ a[3,3] = [1] $ 。

给定两个整数 $ n $ 和 $ k $，构造一个由 $ n $ 个整数组成的数组 $ a $，满足以下条件：

- 数组 $ a $ 中的所有元素都在 $ -1000 $ 到 $ 1000 $ 之间；
- 数组 $ a $ 恰好有 $ k $ 个子数组的和为正数；
- 其余的 $ \dfrac{(n+1) \cdot n}{2}-k $ 个子数组的和为负数。

## 样例 #1

### 输入

```
4
3 2
2 0
2 2
4 6```

### 输出

```
1 -3 1
-13 -42
-13 42
-3 -4 10 -2```

### 算法分类
构造

### 题解分析与结论
本题的核心在于如何构造一个满足特定子数组和条件的数组。各题解主要通过以下思路解决问题：

1. **前缀和与差分**：通过构造前缀和序列，利用差分得到原数组，确保子数组和的正负性。
2. **贪心策略**：通过逐步增加正数或负数的个数，确保最终满足条件。
3. **递归与子问题**：将问题分解为子问题，逐步构造满足条件的数组。

### 所选高星题解

#### 题解1：作者：hy233 (赞：17)
**星级：5星**
**关键亮点**：
- 利用前缀和序列的排列性质，通过交换操作构造满足条件的数组。
- 代码简洁，思路清晰，通过冒泡排序的思想逐步增加正序对。

**核心代码**：
```cpp
int a[N];
int main()
{
	int t=rd();
	while(t--)
	{
		int n=rd(),k=rd();
		for(int i=0;i<=n;i++)
			a[i]=n-i+1;
		for(int i=0;i<=n;i++)
			for(int j=i+1;j<=n;j++)
			{
				if(k>0)
				{
					k--;
					swap(a[i],a[j]);
				}
			}
		for(int i=1;i<=n;i++)
			cout<<a[i]-a[i-1]<<' ';
		cout<<endl;
	}
	return 0;
}
```

#### 题解2：作者：igAC (赞：9)
**星级：4星**
**关键亮点**：
- 通过贪心策略，逐步增加正数个数，确保最终满足条件。
- 详细证明了构造方法的正确性，思路清晰。

**核心代码**：
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 35
using namespace std;
int read(){
	int x=0,f=1,ch=getchar();
	for(;!isdigit(ch);ch=getchar()) f=(ch=='-')?-1:1;
	for(;isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
	return x*f;
}
int n,k;
int a[N];
void solve(){
	n=read(),k=read();
	if(!k) for(int i=1;i<=n;++i) printf("%d ",-1000);
	else{
		int cnt=0;
		for(int i=1;i<=n;++i){
			int d=i*(i+1)/2;
			if(d>=k){
				cnt=i;
				break;
			}
		}
		for(int i=1;i<cnt;++i) a[i]=30;
		if(cnt*(cnt+1)/2==k) a[cnt]=30;
		else a[cnt]=-1-30*(cnt*(cnt+1)/2-k-1);
		for(int i=cnt+1;i<=n;++i) a[i]=-1000;
		for(int i=1;i<=n;++i) printf("%d ",a[i]);
	}
	puts("");
}
int main(){
	int T=read();
	while(T--) solve();
	return 0;
}
```

#### 题解3：作者：听取MLE声一片 (赞：8)
**星级：4星**
**关键亮点**：
- 通过逐步增加正数个数，确保最终满足条件。
- 代码简洁，思路清晰，通过递归与子问题逐步构造满足条件的数组。

**核心代码**：
```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<queue>
#include<stack>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=40;
int n,k,a[N];
signed main()
{
	int T=read();
	while(T--){
		n=read(),k=read();
		memset(a,0,sizeof(a));
		for(int i=1;i<=n;i++){
			if(k>=i){
				k-=i;
				a[i]=2;
				continue;
			}
			a[i]=-2*(i-k-1)-1;
			for(int j=i+1;j<=n;j++)
				a[j]=-1000;
			break;
		}
		for(int i=1;i<=n;i++)
			cout<<a[i]<<' ';
		cout<<'\n';
	}
	return 0;
}
```

### 最优关键思路
- **前缀和与差分**：通过构造前缀和序列，利用差分得到原数组，确保子数组和的正负性。
- **贪心策略**：通过逐步增加正数或负数的个数，确保最终满足条件。
- **递归与子问题**：将问题分解为子问题，逐步构造满足条件的数组。

### 可拓展之处
- 类似构造题可以通过前缀和、差分、贪心等策略解决。
- 递归与子问题的思想可以应用于其他构造类题目。

### 推荐题目
1. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1057 传球游戏](https://www.luogu.com.cn/problem/P1057)

---
处理用时：46.46秒