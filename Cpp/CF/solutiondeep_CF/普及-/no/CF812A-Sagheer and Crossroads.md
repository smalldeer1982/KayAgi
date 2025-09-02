# 题目信息

# Sagheer and Crossroads

## 题目描述

Sagheer is walking in the street when he comes to an intersection of two roads. Each road can be represented as two parts where each part has $ 3 $ lanes getting into the intersection (one for each direction) and $ 3 $ lanes getting out of the intersection, so we have $ 4 $ parts in total. Each part has $ 4 $ lights, one for each lane getting into the intersection ( $ l $ — left, $ s $ — straight, $ r $ — right) and a light $ p $ for a pedestrian crossing.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF812A/a08cde5c54e404c978bae7b092917e8befa50c5b.png)An accident is possible if a car can hit a pedestrian. This can happen if the light of a pedestrian crossing of some part and the light of a lane that can get to or from that same part are green at the same time.

Now, Sagheer is monitoring the configuration of the traffic lights. Your task is to help him detect whether an accident is possible.

## 说明/提示

In the first example, some accidents are possible because cars of part $ 1 $ can hit pedestrians of parts $ 1 $ and $ 4 $ . Also, cars of parts $ 2 $ and $ 3 $ can hit pedestrians of part $ 4 $ .

In the second example, no car can pass the pedestrian crossing of part $ 4 $ which is the only green pedestrian light. So, no accident can occur.

## 样例 #1

### 输入

```
1 0 0 1
0 1 0 0
0 0 1 0
0 0 0 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
0 1 1 0
1 0 1 0
1 1 0 0
0 0 0 1
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
1 0 0 0
0 0 0 1
0 0 0 0
1 0 1 0
```

### 输出

```
NO
```

# AI分析结果

### 题目翻译
Sagheer 正在街上走着，这时他来到了两条路的交叉路口。每条路可以用两部分来表示，每部分有 3 条车道通向交叉路口（每个方向各一条），还有 3 条车道从交叉路口驶出，所以总共有 4 部分。每部分有 4 个信号灯，一个用于通向交叉路口的每条车道（l 表示左转，s 表示直行，r 表示右转），还有一个信号灯 p 用于人行横道。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF812A/a08cde5c54e404c978bae7b092917e8befa50c5b.png)

如果汽车可能撞到行人，就会发生事故。当某一部分的人行横道信号灯和可以到达或离开该同一部分的车道信号灯同时为绿灯时，就可能发生这种情况。

现在，Sagheer 正在监测交通信号灯的配置。你的任务是帮助他检测是否可能发生事故。

### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路都是枚举四个部分的信号灯情况，判断是否存在行人信号灯为绿灯时，有车辆信号灯也为绿灯从而可能导致事故的情况。各题解的算法要点都是判断当某部分的人行横道灯为绿灯时，该部分的左转、直行、右转灯以及对面部分的直行灯、左侧部分的右转灯、右侧部分的左转灯中是否有绿灯。

难点在于准确找出可能发生事故的所有情况，以及处理各部分之间的相对位置关系。不同题解在处理相对位置时采用了不同的方式，有的使用取模运算，有的使用三目运算符。

### 所选题解
- **_Execution_（4星）**
    - **关键亮点**：思路清晰，代码简洁，使用取模运算处理各部分之间的相对位置，提高了代码的可读性和简洁性。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
bool l[4], s[4], r[4], p[4];
int main() {
  for (int i = 0; i < 4; i++) {
    cin >> l[i] >> s[i] >> r[i] >> p[i];
  }
  for (int i = 0; i < 4; i++) {
    if (p[i]) {
      if ((l[i] || s[i] || r[i] || r[(i + 3) % 4] || s[(i + 2) % 4] || l[(i + 1) % 4])) {
        puts("YES");
        return 0;
      }
    }
  }
  cout << "NO";
  return 0;
}
```
核心实现思想：先输入四个部分的信号灯状态，然后枚举每个部分，当该部分的人行横道灯为绿灯时，检查该部分及相关部分的车辆信号灯是否有绿灯，若有则输出 `YES` 并结束程序，否则最后输出 `NO`。

- **huangjunhan（4星）**
    - **关键亮点**：思路明确，使用取模运算处理位置关系，代码简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110],b[110],c[110],d[110];
int main(){
	for(int i=0;i<4;i++)scanf("%d%d%d%d",a+i,b+i,c+i,d+i);
	for(int i=0;i<4;i++){
		if(d[i]&&(a[i]||b[i]||c[i]||c[(i+3)%4]||b[(i+2)%4]||a[(i+1)%4])){
			printf("YES\n");
			return 0;
		}
	}
	printf("NO\n");
}
```
核心实现思想：先输入信号灯状态，然后枚举每个部分，当人行横道灯为绿灯且相关车辆信号灯有绿灯时输出 `YES` 并结束程序，否则最后输出 `NO`。

- **jasonshen_（4星）**
    - **关键亮点**：代码简洁，逻辑清晰，使用取模运算处理位置关系。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int l[4],s[4],r[4],p[4];
	for (int i=0;i<4;i++)cin>>l[i]>>s[i]>>r[i]>>p[i];
	for (int i=0;i<4;i++)
	if (p[i]&&(l[i]||s[i]||r[i]||r[(i+3)%4]||s[(i+2)%4]||l[(i+1)%4]))
		return cout<<"YES",0;
	cout<<"NO";
}
```
核心实现思想：输入信号灯状态后，枚举每个部分，当满足事故条件时输出 `YES` 并结束程序，否则最后输出 `NO`。

### 最优关键思路或技巧
- 使用数组存储每个部分的信号灯状态，方便枚举和判断。
- 利用取模运算处理各部分之间的相对位置关系，避免了复杂的条件判断。

### 拓展思路
同类型题可能会有更复杂的交通场景，如多个交叉路口、不同的车道规则等，但解题思路仍然是枚举各种情况，判断是否满足事故条件。类似算法套路可以应用于其他需要判断条件组合的问题，如电路开关状态判断、游戏规则判断等。

### 推荐洛谷题目
- P1046 陶陶摘苹果
- P1420 最长连号
- P1055 ISBN 号码

---
处理用时：37.24秒