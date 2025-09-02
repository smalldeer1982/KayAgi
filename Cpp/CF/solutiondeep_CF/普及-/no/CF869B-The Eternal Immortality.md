# 题目信息

# The Eternal Immortality

## 题目描述

Even if the world is full of counterfeits, I still regard it as wonderful.

Pile up herbs and incense, and arise again from the flames and ashes of its predecessor — as is known to many, the phoenix does it like this.

The phoenix has a rather long lifespan, and reincarnates itself once every $ a! $ years. Here $ a! $ denotes the factorial of integer $ a $ , that is, $ a!=1×2×...×a $ . Specifically, $ 0!=1 $ .

Koyomi doesn't care much about this, but before he gets into another mess with oddities, he is interested in the number of times the phoenix will reincarnate in a timespan of $ b! $ years, that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/e1b2fb98f4ea484515a807ebc0e143dd3b54b9f1.png). Note that when $ b>=a $ this value is always integer.

As the answer can be quite large, it would be enough for Koyomi just to know the last digit of the answer in decimal representation. And you're here to provide Koyomi with this knowledge.

## 说明/提示

In the first example, the last digit of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/710c390d7d95fd1e439facb57a8db32614f140ba.png) is $ 2 $ ;

In the second example, the last digit of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/9a0a3742a40de8b41b9545899252cb65c16a80ca.png) is $ 0 $ ;

In the third example, the last digit of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF869B/ba5fe125aa2ce1485bb9c22050da0a9acf975415.png) is $ 2 $ .

## 样例 #1

### 输入

```
2 4
```

### 输出

```
2
```

## 样例 #2

### 输入

```
0 10
```

### 输出

```
0
```

## 样例 #3

### 输入

```
107 109
```

### 输出

```
2
```

# AI分析结果

### 题目中文重写
# 永恒的不朽

## 题目描述
即使世界充满了假冒伪劣，我仍然认为它很美好。

堆积香草和香料，然后从它前身的火焰和灰烬中重生 —— 众所周知，凤凰就是这样做的。

凤凰的寿命相当长，每 $a!$ 年转世一次。这里 $a!$ 表示整数 $a$ 的阶乘，即 $a!=1×2×...×a$ 。特别地，$0!=1$ 。

小忍对此并不太在意，但在他再次陷入与怪异的麻烦之前，他对凤凰在 $b!$ 年的时间跨度内转世的次数感兴趣，即 $\frac{b!}{a!}$ 。注意，当 $b \geq a$ 时，这个值总是整数。

由于答案可能非常大，对小忍来说，只知道答案的十进制表示的最后一位就足够了。而你要在这里为小忍提供这些信息。

## 说明/提示
在第一个示例中，$\frac{4!}{2!}$ 的最后一位是 $2$ ；

在第二个示例中，$\frac{10!}{0!}$ 的最后一位是 $0$ ；

在第三个示例中，$\frac{109!}{107!}$ 的最后一位是 $2$ 。

## 样例 #1
### 输入
```
2 4
```
### 输出
```
2
```

## 样例 #2
### 输入
```
0 10
```
### 输出
```
0
```

## 样例 #3
### 输入
```
107 109
```
### 输出
```
2
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是先对 $\frac{b!}{a!}$ 进行化简，得到 $(a + 1) * (a + 2) * \cdots * b$ ，然后通过取模运算只关注个位数来避免数据溢出。同时，利用数学性质，当 $b - a \geq 5$ 时，结果的个位数一定为 $0$ ，以此来优化算法。

### 所选的题解
- 作者：李至擎 (赞：7)，4星
  - 关键亮点：思路清晰，对每一步优化都有详细的解释，代码可读性高。
  - 个人心得：无

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,ans=1;
int main()
{
    cin>>a>>b;
    if(b-a>=5)
    {
        cout<<0;
        return 0;
    }
    for(long long i=a+1;i<=b;i++)
    {
        ans=(ans*(i%10))%10;
    }
    cout<<ans;
    return 0;
}
```
**核心实现思想**：首先判断 $b - a$ 是否大于等于 $5$ ，如果是则直接输出 $0$ 。否则，从 $a + 1$ 到 $b$ 进行遍历，每次将当前数的个位数与之前的结果相乘并取个位数，最终得到结果的个位数。

### 关键思路或技巧
- **化简公式**：将 $\frac{b!}{a!}$ 化简为 $(a + 1) * (a + 2) * \cdots * b$ ，减少计算量。
- **取模运算**：只关注个位数，通过取模运算避免数据溢出。
- **数学性质优化**：利用当 $b - a \geq 5$ 时，结果的个位数一定为 $0$ 的性质，提前终止计算。

### 拓展思路
同类型题目可能会涉及到其他数学运算的个位数求解，或者在不同的数学场景下利用类似的取模和数学性质优化的方法。例如，计算多个数的乘积、幂运算等结果的个位数。

### 推荐题目
- [P1045 麦森数](https://www.luogu.com.cn/problem/P1045)：涉及到大数的幂运算，可能需要用到取模等技巧来处理结果。
- [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)：与阶乘相关，可能需要处理大数的加法和乘法。
- [P1306 斐波那契公约数](https://www.luogu.com.cn/problem/P1306)：涉及到斐波那契数列和公约数的计算，可能需要运用数学性质进行优化。

### 个人心得总结
题解中未包含个人心得。

---
处理用时：28.69秒