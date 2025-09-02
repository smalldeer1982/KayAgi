# 题目信息

# Roadside Trees (Simplified Edition)

## 题目描述

Squirrel Liss loves nuts. There are $ n $ trees (numbered $ 1 $ to $ n $ from west to east) along a street and there is a delicious nut on the top of each tree. The height of the tree $ i $ is $ h_{i} $ . Liss wants to eat all nuts.

Now Liss is on the root of the tree with the number $ 1 $ . In one second Liss can perform one of the following actions:

- Walk up or down one unit on a tree.
- Eat a nut on the top of the current tree.
- Jump to the next tree. In this action the height of Liss doesn't change. More formally, when Liss is at height $ h $ of the tree $ i $ ( $ 1<=i<=n-1 $ ), she jumps to height $ h $ of the tree $ i+1 $ . This action can't be performed if $ h&gt;h_{i+1} $ .

Compute the minimal time (in seconds) required to eat all nuts.

## 样例 #1

### 输入

```
2
1
2
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5
2
1
2
1
1
```

### 输出

```
14
```

# AI分析结果

### 题目内容
# 路边的树（简化版）

## 题目描述
松鼠 Liss 喜欢坚果。沿着一条街道有 $n$ 棵树（从西到东编号为 $1$ 到 $n$），每棵树的树顶都有一颗美味的坚果。第 $i$ 棵树的高度为 $h_{i}$ 。Liss 想要吃掉所有的坚果。

现在 Liss 在编号为 $1$ 的树的根部。在一秒内，Liss 可以执行以下操作之一：
- 在一棵树上向上或向下移动一个单位。
- 吃掉当前树树顶的坚果。
- 跳到下一棵树。在这个动作中，Liss 的高度不变。更正式地说，当 Liss 在第 $i$ 棵树的高度 $h$ 处（$1\leq i\leq n - 1$），她跳到第 $i + 1$ 棵树的高度 $h$ 处。如果 $h > h_{i + 1}$，则不能执行此动作。

计算吃掉所有坚果所需的最短时间（以秒为单位）。

## 样例 #1
### 输入
```
2
1
2
```
### 输出
```
5
```

## 样例 #2
### 输入
```
5
2
1
2
1
1
```
### 输出
```
14
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是基于题目给定的规则进行模拟。算法要点在于按照从第1棵树到第n棵树的顺序，依次计算爬上树顶吃坚果、根据下一棵树高度决定是否上下爬以及跳到下一棵树所需的时间。解决难点主要在于对各种情况的准确判断和时间计算，例如跳到下一棵树的条件限制，以及最后一棵树的特殊处理。

大部分题解思路较为清晰，代码实现也较为直接，但在细节处理上略有不同。部分题解通过提前初始化或特殊设置来简化计算，如将第n + 1棵树高度设为第n棵树高度，或者提前计算部分时间。

### 所选的题解
- **作者：_H17_ （5星）**
    - **关键亮点**：思路清晰，代码简洁明了。通过特殊设置第n + 1棵树的高度等于第n棵树，巧妙处理了最后一棵树跳到不存在树的情况，减少了额外判断。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100002],ans,now;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    a[n+1]=a[n];//特殊设置
    for(int i=1;i<=n;i++){
        ans+=a[i]-now+1,now=a[i];//爬上去+吃果子
        if(a[i]>a[i+1])
            now=a[i+1],ans+=a[i]-a[i+1];//趴下去
        ans++;//跳到下一棵树上
    }
    printf("%d",ans-1);
    return 0;
}
```
核心实现思想：遍历每棵树，先计算爬上当前树吃坚果的时间，再判断是否需要向下爬，最后加上跳到下一棵树的时间，最后减去多算的一次“跳”操作。
- **作者：Marshall001 （4星）**
    - **关键亮点**：提前初始化总时间，简化了计算过程，对从第i棵树跳到第i + 1棵树的时间计算有清晰的理解和处理。
    - **重点代码**：
```cpp
#include <iostream>
#include <cmath>
using namespace std;
long long n,last,h,ans;//last是上一棵树的高度。
int main(){
	cin>>n;
	ans=n-1;//初始化
	for(int i=1;i<=n;i++){
		cin>>h;
		ans+=labs(last-h)+1;
		last=h;
	}
	cout<<ans;
	return 0;
}
```
核心实现思想：初始化总时间为n - 1，遍历每棵树，计算与上一棵树高度差的绝对值并加上1，更新上一棵树的高度。
- **作者：123456zmy （4星）**
    - **关键亮点**：通过观察得出从第i棵树到第i + 1棵树树顶所需时间的通用公式，代码简洁高效。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,h,a;
int main()
{
	scanf("%d",&n);
	ans=(n<<1)-1;
	while(n--)
	{
		scanf("%d",&a);
		ans+=abs(a-h);
		h=a;
	}
	printf("%d",ans);
	return 0;
}
```
核心实现思想：初始化总时间为2n - 1，遍历每棵树，计算与上一棵树高度差的绝对值并更新当前高度。

### 最优关键思路或技巧
通过提前初始化部分时间，以及对从一棵树到下一棵树所需时间的总结归纳，简化了模拟过程中的计算。如提前算出跳到下一棵树的总次数对应的时间，以及总结出从第i棵树到第i + 1棵树树顶所需时间为$|{h_{i+1}-h_{i}}|+1$ 。

### 拓展
同类型题通常围绕特定规则下的操作模拟，可能会在操作种类、条件限制等方面进行变化。类似算法套路是仔细分析规则，明确每个操作的条件和代价，按顺序模拟整个过程。

### 推荐洛谷题目
- [P1046 陶陶摘苹果（升级版）](https://www.luogu.com.cn/problem/P1046)
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)
- [P5709 筛选号码](https://www.luogu.com.cn/problem/P5709)

### 个人心得摘录与总结
无。 

---
处理用时：54.61秒