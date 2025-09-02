# 题目信息

# Different Divisors

## 题目描述

Positive integer $ x $ is called divisor of positive integer $ y $ , if $ y $ is divisible by $ x $ without remainder. For example, $ 1 $ is a divisor of $ 7 $ and $ 3 $ is not divisor of $ 8 $ .

We gave you an integer $ d $ and asked you to find the smallest positive integer $ a $ , such that

- $ a $ has at least $ 4 $ divisors;
- difference between any two divisors of $ a $ is at least $ d $ .

## 说明/提示

In the first test case, integer $ 6 $ have following divisors: $ [1, 2, 3, 6] $ . There are $ 4 $ of them and the difference between any two of them is at least $ 1 $ . There is no smaller integer with at least $ 4 $ divisors.

In the second test case, integer $ 15 $ have following divisors: $ [1, 3, 5, 15] $ . There are $ 4 $ of them and the difference between any two of them is at least $ 2 $ .

The answer $ 12 $ is INVALID because divisors are $ [1, 2, 3, 4, 6, 12] $ . And the difference between, for example, divisors $ 2 $ and $ 3 $ is less than $ d=2 $ .

## 样例 #1

### 输入

```
2
1
2```

### 输出

```
6
15```

# AI分析结果

### 题目内容翻译

正整数 $x$ 是正整数 $y$ 的因子，当且仅当 $y$ 能被 $x$ 整除。例如，$1$ 是 $7$ 的因子，而 $3$ 不是 $8$ 的因子。

给定一个整数 $d$，要求你找到最小的正整数 $a$，满足以下条件：

- $a$ 至少有 $4$ 个因子；
- $a$ 的任意两个因子之间的差至少为 $d$。

### 算法分类
**质数**

### 题解分析与结论

1. **核心思路**：所有题解都基于一个共同的核心思路，即最小的 $a$ 必须有且仅有四个因子，且这些因子之间的差至少为 $d$。由于 $a$ 本身和 $1$ 是必然的两个因子，因此剩下的两个因子必须是质数，且它们之间的差至少为 $d$。

2. **实现方法**：大多数题解都采用了筛法预处理质数，然后通过枚举找到满足条件的最小质数对，最后将这两个质数相乘得到 $a$。

3. **优化点**：部分题解使用了二分查找来加速质数的查找过程，进一步优化了时间复杂度。

4. **难点**：主要难点在于如何高效地找到满足条件的质数对，以及如何确保 $a$ 的因子数量恰好为四个。

### 评分较高的题解

#### 题解1：作者：fls233666 (4星)
**关键亮点**：
- 使用筛法预处理质数，确保质数查找的高效性。
- 通过暴力枚举找到满足条件的最小质数对，思路清晰且易于理解。

**核心代码**：
```cpp
inline void prepare(){  //用筛法暴力处理出质数
	for(rgt i=2;i<mxn;i++){
		if(!tag[i]){
			for(rgt j=i+i;j<mxn;j+=i)
				tag[j]=true;
		}
	}	
}

int main(){
	int test,d,div1,div2;
	prepare();
	scanf("%d",&test);
	while(test--){
		scanf("%d",&d);
		for(div1=1+d;tag[div1];div1++);  //找到第一个因子
		for(div2=div1+d;tag[div2];div2++);  //找到第二个因子
		printf("%d\n",div1*div2);  //输出答案
	}
	return 0;
}
```

#### 题解2：作者：hensier (4星)
**关键亮点**：
- 使用筛法预处理质数，并结合二分查找优化质数的查找过程。
- 代码结构清晰，逻辑严谨，适合有一定基础的读者。

**核心代码**：
```cpp
void init() // O(n) 筛素数
{
    for(int i=2;i<=maxn;++i)
    {
        if(!vis[i])prime[++prime[0]]=i;
        for(int j=1;i*prime[j]<=maxn&&j<=prime[0];++j)
        {
            vis[i*prime[j]]=true;
            if(i%prime[j]==0)break;
        }
    }
}

int find(int x) // 二分查找大于等于 d+1, x+d 的最小素数
{
    int l=1,r=prime[0],mid;
    while(l<=r)
    {
        mid=(l+r)>>1;
        if(prime[mid]>=x)r=mid-1;
        else l=mid+1;
    }
    return prime[l];
}
```

### 最优关键思路与技巧
- **筛法预处理质数**：通过筛法预处理质数，确保后续查找质数的高效性。
- **二分查找优化**：在查找满足条件的质数时，使用二分查找可以进一步优化时间复杂度。

### 可拓展之处
- **类似题目**：可以拓展到需要构造特定因子数量的数，或者要求因子之间满足特定关系的题目。
- **优化思路**：可以考虑使用更高效的质数生成算法，如线性筛法，或者结合其他数论知识进一步优化。

### 推荐题目
1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1217 [USACO1.5]回文质数 Prime Palindromes](https://www.luogu.com.cn/problem/P1217)
3. [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)

---
处理用时：30.29秒