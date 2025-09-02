# 题目信息

# Drinks

## 题目描述

Little Vasya loves orange juice very much. That's why any food and drink in his kitchen necessarily contains orange juice. There are $ n $ drinks in his fridge, the volume fraction of orange juice in the $ i $ -th drink equals $ p_{i} $ percent.

One day Vasya decided to make himself an orange cocktail. He took equal proportions of each of the $ n $ drinks and mixed them. Then he wondered, how much orange juice the cocktail has.

Find the volume fraction of orange juice in the final drink.

## 说明/提示

Note to the first sample: let's assume that Vasya takes $ x $ milliliters of each drink from the fridge. Then the volume of pure juice in the cocktail will equal ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF200B/7c2a6a8bbcdbfef1f9a32c2eb1f7549c3c17c619.png) milliliters. The total cocktail's volume equals $ 3·x $ milliliters, so the volume fraction of the juice in the cocktail equals ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF200B/cc3d21395b67607dff0b7baa3b0b870221e3352d.png), that is, $ 66.(6) $ percent.

## 样例 #1

### 输入

```
3
50 50 100
```

### 输出

```
66.666666666667
```

## 样例 #2

### 输入

```
4
0 25 50 75
```

### 输出

```
37.500000000000
```

# AI分析结果

### 题目内容
# 饮料

## 题目描述
小瓦夏非常喜欢橙汁。这就是为什么他厨房里的任何食物和饮料都必然含有橙汁。他的冰箱里有 $n$ 种饮料，第 $i$ 种饮料中橙汁的体积分数为 $p_{i}$%。

有一天，瓦夏决定给自己做一杯橙汁鸡尾酒。他从每种饮料中取出相同的比例，然后将它们混合在一起。然后他想知道，这杯鸡尾酒中含有多少橙汁。

求最终饮料中橙汁的体积分数。

## 说明/提示
第一个样例的说明：假设瓦夏从冰箱里每种饮料中取出 $x$ 毫升。那么鸡尾酒中纯橙汁的体积将等于 $\sum_{i = 1}^{3} \frac{p_{i}x}{100}$ 毫升。鸡尾酒的总体积等于 $3·x$ 毫升，所以鸡尾酒中橙汁的体积分数等于 $\frac{\sum_{i = 1}^{3} \frac{p_{i}x}{100}}{3x} \times 100\%$，即 $66.\dot{6}$%。

## 样例 #1
### 输入
```
3
50 50 100
```
### 输出
```
66.666666666667
```

## 样例 #2
### 输入
```
4
0 25 50 75
```
### 输出
```
37.500000000000
```

### 算法分类
数学

### 题解综合分析与结论
所有题解的核心思路都是通过计算所有饮料中橙汁体积分数的总和，再除以饮料的种类数 $n$，得到混合后饮料中橙汁的体积分数，即求平均数。各题解的不同之处主要在于输出格式控制和代码风格。有的题解使用 `cout` 配合 `fixed` 和 `setprecision` 控制小数位数，有的使用 `printf` 格式化输出；部分题解在代码中添加了注释，增强了可读性。

### 所选的题解
- **作者：RBI_GL（4星）**
    - **关键亮点**：思路清晰，代码简洁明了，直接通过循环读入数据并求和，最后计算平均数并输出，同时提到要使用 `double` 或 `float` 类型以及保留多位小数的注意点。
    - **重点代码核心实现思想**：通过两个 `for` 循环，一个读入数据，一个累加求和，最后输出平均数。
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[105];
int ans=0; 
int main()
{
    cin>>n; //输入n
    
    for(int i=1;i<=n;i++) {
    	cin>>a[i]; //输入数据
    }
    
    for (int i=1;i<=n;i++) {
    	ans+=a[i]; //计和 
    }
    
    cout<<fixed<<setprecision(10)<<(double)ans/n;  //输出,多保留几位小数，类型用double 
    return 0;
}
```
- **作者：codemap（4星）**
    - **关键亮点**：在实现求平均数的基础上，详细介绍了 `setprecision` 函数控制小数点后位数的用法，并给出了具体示例，对初学者友好。
    - **重点代码核心实现思想**：通过 `for` 循环读入数据并累加求和，最后使用 `cout` 配合 `fixed` 和 `setprecision` 输出指定小数位数的平均数。
```cpp
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
    int n,t,i,s=0;
    cin>>n;
    for(i=1;i<=n;i++)
    {
        cin>>t;
        s+=t;//计算和
    }
    cout<<fixed<<setprecision(12)<<1.0*s/n;//样例保存了12位小数
    return 0;
}
```
- **作者：TRZ_2007（4星）**
    - **关键亮点**：先通过公式推导证明了混合后饮料中橙汁体积分数的计算方法等同于求平均数，逻辑严谨，对原理阐述清晰。
    - **重点代码核心实现思想**：通过 `for` 循环读入数据并累加，最后使用 `printf` 输出指定小数位数的平均数。
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 109;

int n,x;
double cnt;

int main() {
	scanf("%d",&n);
	for(int i = 1;i <= n;i++) {
		scanf("%d",&x);
		cnt = cnt + x * 1.0;
	}
	printf("%.5lf",cnt / n);//这个你保留超过4位小数就可以了
	return 0;
}
```

### 最优关键思路或技巧
这些题解的最优关键思路在于理解混合饮料中橙汁体积分数的计算本质上就是求各饮料中橙汁体积分数的平均数。在代码实现上，使用合适的数据类型（如 `double`）来处理浮点数运算，并掌握控制输出小数位数的方法（如 `cout` 配合 `fixed` 和 `setprecision` 或 `printf` 的格式化输出）。

### 拓展
同类型题目通常围绕平均数的计算，可能会结合不同的实际场景，如计算班级学生的平均成绩、不同物品的平均价格等。类似算法套路就是根据题目场景，确定需要计算平均数的数据集，通过循环读入数据并累加求和，最后除以数据个数得到平均数。

### 洛谷相似题目推荐
- [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009)：涉及到循环计算阶乘并求和，最后输出结果，与本题通过循环累加数据有相似之处。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：需要根据不同包装铅笔的价格和数量，计算购买一定数量铅笔的最小花费，其中也包含数据的读取与计算，和本题有类似的数据处理过程。
- [P5718 三角形分类](https://www.luogu.com.cn/problem/P5718)：读入三角形三边长度，根据边长关系判断三角形类型，同样是读入数据并进行计算和判断，与本题在数据处理流程上相似。 

---
处理用时：49.20秒