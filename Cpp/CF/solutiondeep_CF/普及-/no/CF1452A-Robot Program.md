# 题目信息

# Robot Program

## 题目描述

There is an infinite 2-dimensional grid. The robot stands in cell $ (0, 0) $ and wants to reach cell $ (x, y) $ . Here is a list of possible commands the robot can execute:

- move north from cell $ (i, j) $ to $ (i, j + 1) $ ;
- move east from cell $ (i, j) $ to $ (i + 1, j) $ ;
- move south from cell $ (i, j) $ to $ (i, j - 1) $ ;
- move west from cell $ (i, j) $ to $ (i - 1, j) $ ;
- stay in cell $ (i, j) $ .

The robot wants to reach cell $ (x, y) $ in as few commands as possible. However, he can't execute the same command two or more times in a row.

What is the minimum number of commands required to reach $ (x, y) $ from $ (0, 0) $ ?

## 说明/提示

The explanations for the example test:

We use characters N, E, S, W and 0 to denote going north, going east, going south, going west and staying in the current cell, respectively.

In the first test case, the robot can use the following sequence: NENENENENE.

In the second test case, the robot can use the following sequence: NENENEN.

In the third test case, the robot can use the following sequence: ESENENE0ENESE.

In the fourth test case, the robot doesn't need to go anywhere at all.

In the fifth test case, the robot can use the following sequence: E0E.

## 样例 #1

### 输入

```
5
5 5
3 4
7 1
0 0
2 0```

### 输出

```
10
7
13
0
3```

# AI分析结果

### 题目内容
# Robot Program

## 题目描述
有一个无限的二维网格。机器人站在单元格 (0, 0) 处，想要到达单元格 (x, y) 。以下是机器人可以执行的可能命令列表：
- 从单元格 (i, j) 向北移动到 (i, j + 1) ；
- 从单元格 (i, j) 向东移动到 (i + 1, j) ；
- 从单元格 (i, j) 向南移动到 (i, j - 1) ；
- 从单元格 (i, j) 向西移动到 (i - 1, j) ；
- 停留在单元格 (i, j) 。

机器人希望以尽可能少的命令到达单元格 (x, y) 。然而，它不能连续执行两次或更多次相同的命令。

从 (0, 0) 到达 (x, y) 所需的最少命令数是多少？

## 说明/提示
示例测试的解释：
我们使用字符 N、E、S、W 和 0 分别表示向北走、向东走、向南走、向西走和停留在当前单元格。

在第一个测试用例中，机器人可以使用以下序列：NENENENENE。

在第二个测试用例中，机器人可以使用以下序列：NENENEN。

在第三个测试用例中，机器人可以使用以下序列：ESENENE0ENESE。

在第四个测试用例中，机器人根本不需要移动。

在第五个测试用例中，机器人可以使用以下序列：E0E。

## 样例 #1
### 输入
```
5
5 5
3 4
7 1
0 0
2 0
```
### 输出
```
10
7
13
0
3
```

### 算法分类
数学

### 题解综合分析与结论
这些题解的核心思路都是先将机器人移动到横纵坐标相等的位置，再处理剩余的距离。
 - **思路**：先以横纵交替的方式移动到(min(x, y), min(x, y)) 位置，之后在直线上采用走一步停一步的策略到达目标点。
 - **算法要点**：计算移动到(min(x, y), min(x, y)) 的步数为 2 * min(x, y)，后续走一步停一步的步数为 2 * (max(x, y) - min(x, y)) - 1 ，并对 x == y 的情况进行特判。
 - **解决难点**：如何规划路径使操作次数最少，避免重复操作且保证路径最短。通过分析可知向目标点的反方向移动会增加步数，不如停顿，所以采用横纵交替和走一步停一步的策略。

### 所选的题解
 - **作者：ql12345 (赞：6)  星级：5星 关键亮点：思路清晰简洁，代码高度优化**
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        cout << max(n, m) * 2 - (n == m? 0 : 1) << '\n';
    }
    return 0;
}
```
核心实现思想：直接根据 x 和 y 的关系计算结果，若 x == y ，结果为 2 * x ；否则为 2 * max(x, y) - 1 。

 - **作者：A_Konnyaku (赞：7) 星级：5星 关键亮点：思路阐述详细，代码注释丰富**
```cpp
#include<bits/stdc++.h>
using namespace std;
int  i,d,m,n,x,y,tot=0;
int main()
{
	ios::sync_with_stdio(false);
    cin>>d;
	for(i=0;i<d;i++)
    {
	cin>>x>>y;
		if(x==y)
        {
			cout<<2*x<<endl;
			continue;
		}
		int n=min(x,y),m=max(x,y);
		tot=2*n+(m-n)*2-1;
        cout<<tot<<endl;
		tot=0;
    }
	return 0;
}
```
核心实现思想：先特判 x == y 的情况，然后计算移动到横纵相等位置的步数与后续直线移动步数之和。

 - **作者：_ajthreac_ (赞：2) 星级：4星 关键亮点：表述简洁，代码清晰**
```cpp
int T,x,y;
int main(){
	Read(T);
	while(T--){
		Read(x),Read(y);
		x=abs(x),y=abs(y);
		if(x==y)cout<<min(x,y)*2<<endl;
		else cout<<min(x,y)*2+(max(x,y)-min(x,y))*2-1<<endl;
	}
	return 0;
}
```
核心实现思想：同样先对 x == y 进行特判，之后按照先横纵交替再走一步停一步的思路计算总步数。

### 最优关键思路或技巧
采用贪心策略，优先横纵交替移动，再走一步停一步，避免向远离目标点方向移动，通过数学方法直接计算出最少步数，避免复杂模拟。

### 同类型题或类似算法套路拓展
此类题目通常涉及在一定规则限制下求最优路径或最少操作次数。类似套路为先分析规则对路径的影响，找到一种局部最优的移动方式，再通过数学方法总结出通用的计算最少步数的公式，并注意对特殊情况进行特判。

### 洛谷相似题目推荐
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：需根据给定规则计算最优值，涉及简单的数学分析和条件判断。
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：通过枚举和数学计算找到满足等式的方案数，和本题一样需要分析规则并运用数学方法求解。
 - [P1228 地毯填补问题](https://www.luogu.com.cn/problem/P1228)：在一定限制条件下对图形进行填充，需分析规则并采用合适策略，和本题思路有相似之处。 

---
处理用时：61.41秒