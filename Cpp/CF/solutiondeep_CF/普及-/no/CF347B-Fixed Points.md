# 题目信息

# Fixed Points

## 题目描述

A permutation of length $ n $ is an integer sequence such that each integer from 0 to $ (n-1) $ appears exactly once in it. For example, sequence $ [0,2,1] $ is a permutation of length 3 while both $ [0,2,2] $ and $ [1,2,3] $ are not.

A fixed point of a function is a point that is mapped to itself by the function. A permutation can be regarded as a bijective function. We'll get a definition of a fixed point in a permutation. An integer $ i $ is a fixed point of permutation $ a_{0},a_{1},...,a_{n-1} $ if and only if $ a_{i}=i $ . For example, permutation $ [0,2,1] $ has $ 1 $ fixed point and permutation $ [0,1,2] $ has $ 3 $ fixed points.

You are given permutation $ a $ . You are allowed to swap two elements of the permutation at most once. Your task is to maximize the number of fixed points in the resulting permutation. Note that you are allowed to make at most one swap operation.

## 样例 #1

### 输入

```
5
0 1 3 4 2
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# 不动点

## 题目描述
长度为 $n$ 的排列是一个整数序列，使得从 $0$ 到 $(n - 1)$ 的每个整数在其中恰好出现一次。例如，序列 $[0, 2, 1]$ 是长度为 $3$ 的排列，而 $[0, 2, 2]$ 和 $[1, 2, 3]$ 都不是。

函数的不动点是指被该函数映射到自身的点。排列可以被视为一个双射函数。由此我们可以得到排列中不动点的定义。整数 $i$ 是排列 $a_{0}, a_{1},..., a_{n - 1}$ 的不动点，当且仅当 $a_{i} = i$ 。例如，排列 $[0, 2, 1]$ 有 $1$ 个不动点，排列 $[0, 1, 2]$ 有 $3$ 个不动点。

给定一个排列 $a$ 。你最多可以交换排列中的两个元素一次。你的任务是使得到的排列中不动点的数量最大化。注意，你最多只能进行一次交换操作。

## 样例 #1
### 输入
```
5
0 1 3 4 2
```
### 输出
```
3
```

### 算法分类
模拟

### 题解综合分析与结论
这些题解思路基本一致，都是先统计原排列中不动点的数量，再根据不同情况判断交换后不动点数量的变化。主要有三种情况：所有数字都在正确位置，直接输出 $n$；有两个数字互换了位置，交换后不动点数量增加 $2$；其他情况，交换后不动点数量增加 $1$。各题解在代码实现上略有差异，但核心逻辑相同。

### 所选的题解
- **作者：Yaixy (5星)**
    - **关键亮点**：思路清晰，先明确题意和注意点，通过画图总结出三种可能情况，代码简洁明了，可读性强。
    - **个人心得**：提到拿到题没思路时可画图整理思路。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000005],sum,n;
int main()
{
    cin>>n;
    for(int i=0;i<n;++i) cin>>a[i];//输入
    for(int i=0;i<n;++i) if(a[i]==i) sum++;//记录在正确位置上的数字个数
    if(sum==n)
     {
         cout<<n;
         return 0;//第一种情况
     }
    for(int i=0;i<n;i++)
     if(a[a[i]]==i&&i!=a[i])
      {
          cout<<sum+2;
          return 0;//第二种情况
      }
    cout<<sum+1;//第三种情况
    return 0;
}
```
核心实现思想：先统计原排列中不动点个数 `sum`，若 `sum` 等于 `n`，说明所有数字都在正确位置，直接输出 `n`；否则遍历数组，若存在 `a[a[i]] == i && i!= a[i]`，说明有两个数字互换位置，输出 `sum + 2`；若都不满足则输出 `sum + 1`。
- **作者：tryrtj (4星)**
    - **关键亮点**：代码简洁，逻辑清晰，通过一次枚举找出应在位置上的数且正好相反的情况。
    - **个人心得**：吐槽评测机显示登录错误。
    - **核心代码**：
```cpp
#include<iostream>
using namespace std;
int a[100005];
int main(){
	int n;
	cin>>n;
	int zong=0;
	for(int i=0;i<n;i++){
		cin>>a[i];//读入
		if(i==a[i])zong++;//找已经对应的个数
	}
	if(zong==n){
		cout<<n;//特判
		return 0;
	}
	for(int i=0;i<n;i++){
		if(i==a[a[i]]&&i!=a[i]){//找所对应的是否就是
			cout<<zong+2;//直接出来
			return 0;
		}
	}
	cout<<zong+1;//否则只能+1
	return 0;
}
```
核心实现思想：与 Yaixy 类似，先统计不动点个数 `zong`，若 `zong` 等于 `n` 直接输出 `n`；否则遍历数组，判断是否存在满足条件的两个数，若有则输出 `zong + 2`，否则输出 `zong + 1`。
- **作者：梦理乾坤 (4星)**
    - **关键亮点**：简洁明了地分析出两种需要处理的情况，代码实现清晰。
    - **核心代码**：
```cpp
#include <iostream>

using namespace std;

const int N = 100010;

int a[N], ans, n;

int main()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];// 输入
        if (a[i] == i)
            ans++;//看默认有几个是可以的
    }

    if (ans == n)
    {
        cout << ans << endl;
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (a[a[i]] == i && a[i]!= i)//若可以一下子换，就可以变两个岂不美哉，hh
        {
            cout << ans + 2 << endl;
            return 0;
        }
    }

    cout << ans + 1 << endl;//否则只能加一个
    return 0;
}
```
核心实现思想：统计不动点个数 `ans`，若 `ans` 等于 `n` 输出 `ans`；否则遍历数组，若找到满足条件的两个数则输出 `ans + 2`，否则输出 `ans + 1`。

### 最优关键思路或技巧
通过先统计原排列不动点数量，再根据特定条件判断能否通过一次交换增加两个不动点，若不能则只能增加一个不动点，从而避免暴力枚举交换的 $O(n^2)$ 复杂度。

### 拓展思路
此类题目主要考察对排列和不动点概念的理解以及逻辑分析能力。类似题目可能会改变限制条件，如允许交换多次，或者对排列的范围、性质有不同规定。解题时依旧要从分析不同情况对不动点数量的影响入手。

### 相似知识点洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合来解决问题，与本题通过分析不同情况解决问题思路类似。
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：涉及到组合的生成与输出，和本题分析不同情况有相似的逻辑分析过程。
- [P1219 八皇后](https://www.luogu.com.cn/problem/P1219)：通过模拟不同放置情况来求解，与本题分析不同排列情况的思路类似。 

---
处理用时：54.20秒