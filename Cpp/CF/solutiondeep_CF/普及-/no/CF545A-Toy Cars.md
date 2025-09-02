# 题目信息

# Toy Cars

## 题目描述

Little Susie, thanks to her older brother, likes to play with cars. Today she decided to set up a tournament between them. The process of a tournament is described in the next paragraph.

There are $ n $ toy cars. Each pair collides. The result of a collision can be one of the following: no car turned over, one car turned over, both cars turned over. A car is good if it turned over in no collision. The results of the collisions are determined by an $ n×n $ matrix $ А $ : there is a number on the intersection of the $ і $ -th row and $ j $ -th column that describes the result of the collision of the $ і $ -th and the $ j $ -th car:

- $ -1 $ : if this pair of cars never collided. $ -1 $ occurs only on the main diagonal of the matrix.
- $ 0 $ : if no car turned over during the collision.
- $ 1 $ : if only the $ i $ -th car turned over during the collision.
- $ 2 $ : if only the $ j $ -th car turned over during the collision.
- $ 3 $ : if both cars turned over during the collision.

Susie wants to find all the good cars. She quickly determined which cars are good. Can you cope with the task?

## 样例 #1

### 输入

```
3
-1 0 0
0 -1 1
0 2 -1
```

### 输出

```
2
1 3 ```

## 样例 #2

### 输入

```
4
-1 3 3 3
3 -1 3 3
3 3 -1 3
3 3 3 -1
```

### 输出

```
0
```

# AI分析结果

### 题目中文重写
# 玩具汽车

## 题目描述
小苏西因为她的哥哥而喜欢玩汽车。今天她决定在这些汽车之间举办一场锦标赛。锦标赛的流程将在接下来的段落中描述。

有 $n$ 辆玩具汽车。每两辆车都会发生碰撞。碰撞的结果可能是以下情况之一：没有车翻车、有一辆车翻车、两辆车都翻车。如果一辆车在任何碰撞中都没有翻车，那么它就是一辆好车。碰撞的结果由一个 $n×n$ 的矩阵 $A$ 决定：在第 $i$ 行和第 $j$ 列的交叉处有一个数字，描述了第 $i$ 辆车和第 $j$ 辆车的碰撞结果：
- $ -1 $：如果这两辆车从未发生碰撞。$ -1 $ 只出现在矩阵的主对角线上。
- $ 0 $：如果在碰撞过程中没有车翻车。
- $ 1 $：如果在碰撞过程中只有第 $i$ 辆车翻车。
- $ 2 $：如果在碰撞过程中只有第 $j$ 辆车翻车。
- $ 3 $：如果在碰撞过程中两辆车都翻车。

苏西想找出所有的好车。她很快就确定了哪些车是好车。你能完成这个任务吗？

## 样例 #1
### 输入
```
3
-1 0 0
0 -1 1
0 2 -1
```
### 输出
```
2
1 3 
```

## 样例 #2
### 输入
```
4
-1 3 3 3
3 -1 3 3
3 3 -1 3
3 3 3 -1
```
### 输出
```
0
```

### 算法分类
模拟

### 综合分析与结论
- **思路对比**：
    - 封禁用户、sel_fish、LYR_ 三位作者的思路类似，都是边输入矩阵元素边根据元素值标记翻车的车辆，最后统计未翻车的车辆数量及编号。
    - hgoicjl 的思路是按行处理矩阵，判断该行对应的车辆是否被撞毁，然后统计未撞毁的车辆。
- **算法要点对比**：
    - 封禁用户、sel_fish 用普通数组标记车辆状态。
    - LYR_ 使用 `set` 去重，同时用布尔数组标记车辆状态。
    - hgoicjl 按行判断车辆是否撞毁并记录未撞毁车辆编号。
- **解决难点对比**：
    - 主要难点在于根据矩阵元素准确标记翻车的车辆，各位作者都通过条件判断语句解决了该问题。

### 题解评分
- 封禁用户：4星。思路清晰，代码可读性高，实现简单直接。
- sel_fish：3星。思路较清晰，但代码注释可更详细，整体实现稍显简单。
- LYR_：3星。使用 `set` 去重有一定亮点，但对于该题而言，`set` 的使用并非必要，增加了代码复杂度。
- hgoicjl：2星。代码存在拼写错误（`mian` 应为 `main`），影响代码质量，思路实现较常规。

### 所选题解
- 封禁用户：4星。关键亮点在于思路清晰，代码结构简单，易于理解，直接通过数组标记车辆状态，边输入边处理。

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105][105],ans;//ans记录翻车的数量
bool b[105];//b数组记录每辆车的状态（false表示车没翻，true表示车翻了）
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
    	{
    		cin>>a[i][j];
    		if(a[i][j]==1 && !b[i])b[i]=true,ans++;//将编号i的车标记为true
    		else if(a[i][j]==2 && !b[j])b[j]=true,ans++;//将编号j的车标记为true
    		else if(a[i][j]==3)//将编号i、j的车标记为true
	    		{
	    			if(!b[i])b[i]=true,ans++;
	    			if(!b[j])b[j]=true,ans++;
	    		}
    	}
    }
    cout<<n-ans<<endl;//用车总数减去翻车的数量
    if(n-ans!=0)//假如有车没翻
    {
    	for(int i=1;i<=n;i++)//如果为false，输出
    		if(!b[i])cout<<i<<" ";
    }
    return 0;
}
```
**核心实现思想**：通过二维数组存储碰撞结果矩阵，用布尔数组 `b` 标记每辆车的状态。边输入矩阵元素边根据元素值判断车辆是否翻车，若翻车则标记为 `true` 并增加翻车数量 `ans`。最后输出未翻车的车辆数量和编号。

### 最优关键思路或技巧
使用布尔数组标记车辆状态，边输入边处理，简单高效地解决问题。

### 可拓展之处
同类型题可能会改变碰撞结果的表示方式或增加更多的条件，类似算法套路都是模拟整个过程，根据给定条件进行状态标记和统计。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)

### 个人心得
题解中未包含个人心得。 

---
处理用时：32.53秒