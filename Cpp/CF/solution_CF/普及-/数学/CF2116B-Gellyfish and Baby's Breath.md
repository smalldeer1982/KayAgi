# Gellyfish and Baby's Breath

## 题目描述

Flower gives Gellyfish two permutations $ ^{\text{∗}} $ of $ [0, 1, \ldots, n-1] $ : $ p_0, p_1, \ldots, p_{n-1} $ and $ q_0, q_1, \ldots, q_{n-1} $ .

Now Gellyfish wants to calculate an array $ r_0,r_1,\ldots,r_{n-1} $ through the following method:

- For all $ i $ ( $ 0 \leq i \leq n-1 $ ), $ r_i = \max\limits_{j=0}^{i} \left(2^{p_j} + 2^{q_{i-j}} \right) $

But since Gellyfish is very lazy, you have to help her figure out the elements of $ r $ .

Since the elements of $ r $ are very large, you are only required to output the elements of $ r $ modulo $ 998\,244\,353 $ .

 $ ^{\text{∗}} $ An array $ b $ is a permutation of an array $ a $ if $ b $ consists of the elements of $ a $ in arbitrary order. For example, $ [4,2,3,4] $ is a permutation of $ [3,2,4,4] $ while $ [1,2,2] $ is not a permutation of $ [1,2,3] $ .

## 说明/提示

In the first test case:

- $ r_0 = 2^{p_0} + 2^{q_0} = 1+2=3 $
- $ r_1 = \max(2^{p_0} + 2^{q_1}, 2^{p_1} + 2^{q_0}) = \max(1+4, 4+2) = 6 $
- $ r_2 = \max(2^{p_0} + 2^{q_2}, 2^{p_1}+2^{q_1}, 2^{p_2}+2^{q_0}) = (1+1, 4+4, 2+2) = 8 $

## 样例 #1

### 输入

```
3
3
0 2 1
1 2 0
5
0 1 2 3 4
4 3 2 1 0
10
5 8 9 3 4 0 2 7 1 6
9 5 1 4 0 3 2 8 7 6```

### 输出

```
3 6 8 
17 18 20 24 32 
544 768 1024 544 528 528 516 640 516 768```

# 题解

## 作者：codingwen (赞：3)

可以发现 $2^{i-1}+2^{i-1}=2^i$，所以取最大的 $p_i$ 或 $q_i$ 一定不劣。   
所以将 $p$ 和 $q$ 扫一遍，统计最大的 $p_i,q_i$ 和它们的编号，记为 $maxp,maxq$。   
如果 $p_{maxp} \neq q_{maxq}$，那么取更大的一方统计答案。   
否则需要比较另外的一个（即题目中的 $i-j$），取更大的一方统计答案。   
可以预处理 $2$ 的次幂。   
时间复杂度 $O(\sum n)$。

---

## 作者：chenbs (赞：1)

## 题目大意

对于每个 $i$，求出 $\max_{j=0}^{i} (2^{p_j} + 2^{q_{i-j}})$。

要保证 $2^{p_j} + 2^{q_{i-j}}$ 最大，只需要最大化 $\max\{p_j, q_{i-j}\}$。对于一个 $i$，设 $p_x = \max_{j=0}^{i} p_j$，$q_y = \max_{j=0}^{i} q_j$，则：

$\max_{j=0}^{i} (2^{p_j} + 2^{q_{i-j}}) = \max\{2^{p_x} + 2^{q_{i-x}}, 2^{p_{i-y}} + 2^{q_y}\}$

## 代码实现

用 `pw` 预处理出 $2$ 的幂，然后扫一遍求上面那个式子就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t, n;
long long p[100005], q[100005], pw[100005];
int main() {
	cin>>t;
	pw[0]=1;
	for(int i=1; i<=100000; i++) pw[i]=(pw[i-1]<<1)%998244353;
	while(t--) {
		cin>>n;
		for(int i=0; i<n; i++) cin>>p[i];
		for(int i=0; i<n; i++) cin>>q[i];
		int mxp=-1e9, mxpi, mxq=-1e9, mxqi;
		for(int i=0; i<n; i++) {
			if(p[i]>mxp) mxp=p[i], mxpi=i;
			if(q[i]>mxq) mxq=q[i], mxqi=i;
			if(mxp>mxq || mxp==mxq && q[i-mxpi] > p[i-mxqi])
				cout<<(pw[mxp]+pw[q[i-mxpi]])%998244353<<' ';
			else
				cout<<(pw[mxq]+pw[p[i-mxqi]])%998244353<<' ';
		}
		cout<<'\n';
	}


	return 0;
}
```

---

## 作者：fanjiayu666 (赞：0)

### 评价

挺坑的题。

### 思路

不难想到贪心做法：设到第 $i$ 个位置时 $\displaystyle
\max_{j=0}^i q_i$ 的下标为 $maxq$，$\displaystyle\max_{j=0}^i p_i$ 的下标为 $maxp$，则答案如下：


$$r_i=\begin{cases}
  q_{maxq} = p_{maxp} \ 2^{p_{maxp}}+2^{max(p_{i-maxp},q_{i-maxq})}\\
  q_{maxq} > p_{maxp} \ 2^{q_{maxq}}+2^{q_{i-maxq}}\\
  q_{maxq} < p_{maxp} \ 2^{p_{maxp}}+2^{p_{i-maxp}}\\
\end{cases}$$

但是，我们会有个疑问：有没有可能说虽然 $p_{maxp}$ 很大，但是 $p_{i-maxp}$ 很小，$maxp$ 和 $maxq$ 很接近，然后导致 $$2^{q_{maxq}}+2^{q_{i-maxq}}>2^{p_{maxp}}+2^{p_{i-maxp}}$$ 呢？

答案是不可能的：因为 $2^i+2^i=2^{i+1}$，所以必须要有两个相同的次幂 $i$ 加起来才可能等于次幂 $i+1$，要大于的话是不可能的，且题目有说 $p,q$ 都是排列，最多只有两个相同的数，所以无法出现上述情况。（我因为没想通这一点废了）

所以按着上面的些就好了，代码不给了。

---

## 作者：Aurelia_Veil (赞：0)

# 题解：CF2116B Gellyfish and Baby's Breath

这道题让我们最大化 $2^{p_j}+2^{q_{i-j}}$，因为是指数函数而且底数不变，因此只需要找出 $p_j$ 和 $q_{i-j}$ 的最大值让它最大即可。

我们可以遍历每一个 $i$，然后分别找出 $q_j$ 和 $p_j$ 的最大值，然后我们把下标记为 $mxq$ 和 $mxp$。

因此，我们只需要在 $(p_{mxp},q_{i-mxp})$ 和 $(p_{i- mxq},q_{mxq})$ 取其中一对取最大值即可。

最终答案 $\max \{2^{p_{mxp}}+2^{q_{i-mxp}},2^{p_{i- mxq}}+2^{q_{mxq}}\}$。

完结撒花！

---

## 作者：wuyouawa (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF2116B)

### 思路

首先，题目让我们最大化 $2^{p_j}+2^{q_{i-j}}$，那么最大化 $p_j$ 或 $q_{i-j}$ 一定是最好的。

那么我们首先预处理 $2$ 的幂次与最大的 $p$ 和最大的 $q$，接着枚举 $i$，再用预处理的结果进行计算即可。

### 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,q[100005],p[100005],f[100005],mxp[100005],mxq[100005],ans,x[100005],d[100005];
const long long mod=998244353;
int main(){
	scanf("%lld",&t);
	f[0]=1;
	for(int i=1;i<=100000;i++)
	{
		f[i]=f[i-1]*2%mod;
	}
	while(t--)
	{
		scanf("%lld",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%lld",&p[i]);
			if(i>0)  mxp[i]=max(mxp[i-1],p[i]);
			else  mxp[i]=p[i];
			x[p[i]]=i;
		}  
		for(int i=0;i<n;i++)
		{
			scanf("%lld",&q[i]);
			if(i>0)  mxq[i]=max(mxq[i-1],q[i]);
			else  mxq[i]=q[i];
			d[q[i]]=i;
		}  
		for(int i=0;i<n;i++)
		{
			ans=max((f[mxp[i]]+f[q[i-x[mxp[i]]]])%mod,(f[mxq[i]]+f[p[i-d[mxq[i]]]])%mod);
			printf("%lld ",ans);
		}
		printf("\n");
	}
	return 0;
} 
```

---

