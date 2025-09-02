# 题目信息

# Inna and Alarm Clock

## 题目描述

Inna loves sleeping very much, so she needs $ n $ alarm clocks in total to wake up. Let's suppose that Inna's room is a $ 100×100 $ square with the lower left corner at point $ (0,0) $ and with the upper right corner at point $ (100,100) $ . Then the alarm clocks are points with integer coordinates in this square.

The morning has come. All $ n $ alarm clocks in Inna's room are ringing, so Inna wants to turn them off. For that Inna has come up with an amusing game:

- First Inna chooses a type of segments that she will use throughout the game. The segments can be either vertical or horizontal.
- Then Inna makes multiple moves. In a single move, Inna can paint a segment of any length on the plane, she chooses its type at the beginning of the game (either vertical or horizontal), then all alarm clocks that are on this segment switch off. The game ends when all the alarm clocks are switched off.

Inna is very sleepy, so she wants to get through the alarm clocks as soon as possible. Help her, find the minimum number of moves in the game that she needs to turn off all the alarm clocks!

## 说明/提示

In the first sample, Inna first chooses type "vertical segments", and then she makes segments with ends at : $ (0,0) $ , $ (0,2) $ ; and, for example, $ (1,0) $ , $ (1,1) $ . If she paints horizontal segments, she will need at least 3 segments.

In the third sample it is important to note that Inna doesn't have the right to change the type of the segments during the game. That's why she will need 3 horizontal or 3 vertical segments to end the game.

## 样例 #1

### 输入

```
4
0 0
0 1
0 2
1 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
4
0 0
0 1
1 0
1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4
1 1
1 2
2 3
3 3
```

### 输出

```
3
```

# AI分析结果

### 题目内容
# Inna和闹钟

## 题目描述
Inna非常喜欢睡觉，所以她总共需要n个闹钟才能醒来。假设Inna的房间是一个100×100的正方形，左下角坐标为(0, 0)，右上角坐标为(100, 100)。那么闹钟就是这个正方形内具有整数坐标的点。

早晨来临了。Inna房间里的n个闹钟都在响，所以Inna想把它们关掉。为此，Inna想出了一个有趣的游戏：
- 首先，Inna选择一种她将在整个游戏中使用的线段类型。线段可以是垂直的或水平的。
- 然后，Inna进行多次移动。在一次移动中，Inna可以在平面上绘制任意长度的线段，她在游戏开始时选择线段的类型（垂直或水平），然后所有位于这条线段上的闹钟都会关闭。当所有闹钟都关闭时，游戏结束。

Inna非常困，所以她想尽快解决闹钟问题。帮助她找到在游戏中关闭所有闹钟所需的最少移动次数！

## 说明/提示
在第一个示例中，Inna首先选择“垂直线段”类型，然后她绘制端点为(0, 0)，(0, 2)的线段；例如，还可以绘制端点为(1, 0)，(1, 1)的线段。如果她绘制水平线段，那么她至少需要3条线段。

在第三个示例中，需要注意的是Inna在游戏中无权改变线段的类型。这就是为什么她需要3条水平或3条垂直线段才能结束游戏。

## 样例 #1
### 输入
```
4
0 0
0 1
0 2
1 0
```
### 输出
```
2
```

## 样例 #2
### 输入
```
4
0 0
0 1
1 0
1 1
```
### 输出
```
2
```

## 样例 #3
### 输入
```
4
1 1
1 2
2 3
3 3
```
### 输出
```
3
```

### 算法分类
贪心

### 综合分析与结论
所有题解思路基本一致，均基于贪心策略。由于只能选择横向或纵向一种方式关闭闹钟，所以分别统计出现闹钟的行数和列数，取二者最小值即为关闭所有闹钟所需最少移动次数。各题解在代码实现上略有差异，主要体现在变量命名、数组定义范围以及代码风格等方面，但核心算法相同。

### 所选的题解
- **作者：幻之陨梦 (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，变量命名直观，直接用`f1`、`f2`数组记录行和列的闹钟出现情况，`s1`、`s2`统计出现闹钟的行、列数。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,y,s1,s2;
bool f1[101],f2[101];
int main(void)
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        if(!f1[x])
        {
        	f1[x]=1;
        	s1++;
        }
        if(!f2[y])
        {
        	f2[y]=1;
        	s2++;
        }
    }
    printf("%d",min(s1,s2));
}
```
    - **核心实现思想**：遍历输入的每个闹钟坐标，若某行或某列首次出现闹钟，则标记并对相应计数器加1，最后输出行、列计数器的最小值。

- **作者：pyyyyyy (5星)**
    - **关键亮点**：语言风趣，在阐述题意时结合图片，使读者更易理解。代码逻辑清晰，通过`sum_x`和`sum_y`分别统计出现闹钟的行、列数。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int x,y,n,i,x_state[2019],y_state[2019],ans,sum_x,sum_y;
int main() {
	cin>>n;
	for(i=1; i<=n; i++) {
		cin>>x>>y;
		if(!x_state[x]) sum_x++;
		if(!y_state[y]) sum_y++;
		x_state[x]=1,y_state[y]=1;
	}
	if(sum_x>sum_y)
	{
		ans=sum_y;
	}
	else 
		ans=sum_x;
	cout<<ans;
	return 0;
}
```
    - **核心实现思想**：循环读入闹钟坐标，若某行或某列未被标记过（即首次出现闹钟），则对应计数器加1并标记，最后比较行、列计数器大小，输出较小值。

- **作者：无意识躺枪人 (4星)**
    - **关键亮点**：代码简洁高效，通过`xvis`和`yvis`数组标记行和列是否出现闹钟，`xcnt`和`ycnt`统计出现闹钟的行、列数。
    - **重点代码**：
```c
#include<bits/stdc++.h>
using namespace std;
int n,x,y,xcnt,ycnt;
bool xvis[105],yvis[105];
int main()
{
	cin>>n;
	while (n--)
	{
		cin>>x>>y;
		if (!xvis[x]) {xvis[x]=1;xcnt++;}
		if (!yvis[y]) {yvis[y]=1;ycnt++;} 
	}
	printf("%d",min(xcnt,ycnt));
	return 0;
}
```
    - **核心实现思想**：边读入闹钟坐标边判断某行或某列是否已出现过闹钟，若未出现则标记并使对应计数器加1，最后输出行、列计数器的最小值。

### 最优关键思路或技巧
利用贪心策略，分别统计出现闹钟的行数和列数，取最小值。实现时使用布尔数组标记行和列是否出现闹钟，用计数器记录出现闹钟的行、列数，这样可以高效地解决问题。

### 拓展
此类题目属于简单的贪心策略应用，类似套路可用于解决一些需要在两种固定操作方式中选择较优解的问题，例如在给定矩阵中，只能按行或按列进行操作来完成某个任务，求最少操作次数等。

### 推荐题目
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1090 [NOIP2004 提高组] 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录与总结
部分作者提到题目翻译存在问题，导致理解困难，建议在遇到类似情况时，结合英文原题面理解题意。这提醒我们在做题时，若对翻译后的题目有疑惑，应尝试从原始题目获取更准确信息。 

---
处理用时：54.99秒