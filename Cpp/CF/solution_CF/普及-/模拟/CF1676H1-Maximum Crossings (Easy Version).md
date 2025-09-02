# Maximum Crossings (Easy Version)

## 题目描述

The only difference between the two versions is that in this version $ n \leq 1000 $ and the sum of $ n $ over all test cases does not exceed $ 1000 $ .

A terminal is a row of $ n $ equal segments numbered $ 1 $ to $ n $ in order. There are two terminals, one above the other.

You are given an array $ a $ of length $ n $ . For all $ i = 1, 2, \dots, n $ , there should be a straight wire from some point on segment $ i $ of the top terminal to some point on segment $ a_i $ of the bottom terminal. For example, the following pictures show two possible wirings if $ n=7 $ and $ a=[4,1,4,6,7,7,5] $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676H1/71a1fe41f3cad0f3cbda88716457eefb4e46b4ca.png)A crossing occurs when two wires share a point in common. In the picture above, crossings are circled in red.

What is the maximum number of crossings there can be if you place the wires optimally?

## 说明/提示

The first test case is shown in the second picture in the statement.

In the second test case, the only wiring possible has the two wires cross, so the answer is $ 1 $ .

In the third test case, the only wiring possible has one wire, so the answer is $ 0 $ .

## 样例 #1

### 输入

```
4
7
4 1 4 6 7 7 5
2
2 1
1
1
3
2 2 2```

### 输出

```
6
1
0
3```

# 题解

## 作者：5k_sync_closer (赞：0)

# 题意
一个终端是一排 $n$ 个连接在一起的相等的线段，有两个终端，一上一下。

有一个数组 $a_i$，代表从上面的终端中第 $i$ 条线段，到下面的终端中第 $a_i$ 条线段，有一条连线。

问这些连线最多有几个交点。
# 思路
考虑何时两条连线会有交点。

观察样例不难得到，若 $i<j$ 且 $a_i≥a_j$，则两条连线有交点。

直接枚举每一对 $i,j$ 即可，复杂度 $O(n^2)$。

另外，这是一个二维偏序问题，[可以 $O(n\log n)$ 完成](https://www.luogu.com.cn/blog/388651/solution-cf1676h2)。
# 代码
```cpp
#include <cstdio>
int T, n, s, a[1050];
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		scanf("%d", &n);s = 0;
		for(int i = 1;i <= n;++i)
            scanf("%d", &a[i]);
		for(int i = 1;i <= n;++i)
            for(int j = i + 1;j <= n;++j)
                s += a[i] >= a[j];
        printf("%d\n", s);
	}
    return 0;
}
```


---

## 作者：include_BM (赞：0)

若 $i<j$ 且 $a_i\ge a_j$，那么这两条线就可能会产生一个交点。

故问题转化为对于每个 $j$，求 $i<j$ 且 $a_i\ge a_j$ 的数量。

由于 $n\le1000$ 直接枚举即可。 

```cpp
for(int j=1;j<=n;++j)
    for(int i=1;i<j;++i)
        if(a[i]>=a[j]) ++num;
printf("%d\n",num);
```

---

