# 题目信息

# Two Regular Polygons

## 题目描述

You are given two integers $ n $ and $ m $ ( $ m < n $ ). Consider a convex regular polygon of $ n $ vertices. Recall that a regular polygon is a polygon that is equiangular (all angles are equal in measure) and equilateral (all sides have the same length).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1312A/95b1bef3403a130cb1532da909306b47c3e9056c.png) Examples of convex regular polygons Your task is to say if it is possible to build another convex regular polygon with $ m $ vertices such that its center coincides with the center of the initial polygon and each of its vertices is some vertex of the initial polygon.

You have to answer $ t $ independent test cases.

## 说明/提示

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1312A/0982568e883452a4972ef18c303a083c1c1e1608.png) The first test case of the example It can be shown that the answer for the second test case of the example is "NO".

## 样例 #1

### 输入

```
2
6 3
7 3```

### 输出

```
YES
NO```

# AI分析结果

### 题目内容
# 两个正多边形

## 题目描述
给定两个整数 \(n\) 和 \(m\)（\(m < n\)）。考虑一个具有 \(n\) 个顶点的凸正多边形。回想一下，正多边形是指各角相等（所有角的度数都相等）且各边相等（所有边的长度都相同）的多边形。

![示例图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1312A/95b1bef3403a130cb1532da909306b47c3e9056c.png) 凸正多边形示例

你的任务是判断是否有可能构建另一个具有 \(m\) 个顶点的凸正多边形，使得它的中心与初始多边形的中心重合，并且它的每个顶点都是初始多边形的顶点。

你必须回答 \(t\) 个独立的测试用例。

## 说明/提示
![提示图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1312A/0982568e883452a4972ef18c303a083c1c1e1608.png) 示例中的第一个测试用例

可以证明示例中第二个测试用例的答案是 “NO”。

## 样例 #1
### 输入
```
2
6 3
7 3
```
### 输出
```
YES
NO
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路基本一致，均通过观察图形规律得出结论：当 \(n\bmod m = 0\) 时，可以构建满足条件的正 \(m\) 边形，输出“YES”；否则输出“NO”。各题解主要通过举例、画图等方式辅助理解该结论，部分题解给出了简单证明。在实现上，代码结构相似，都是读取 \(t\) 组数据，每组数据读取 \(n\) 和 \(m\) 后进行判断并输出结果。

### 所选的题解
- **作者：立风yu（5星）**
    - **关键亮点**：思路清晰简洁，直接点明通过画图发现规律，代码简洁明了，变量命名规范，注释详细。
    - **重点代码**：
```cpp
#include <iostream>
using namespace std;
int main(){
    int t,n,m;
    cin>>t;
    for (int i=1;i<=t;i++){
        cin>>n>>m;
        if (n%m==0)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：读取 \(t\) 组测试数据，对每组数据中的 \(n\) 和 \(m\) 进行取模判断，根据结果输出“YES”或“NO”。
- **作者：do_while_false（4星）**
    - **关键亮点**：通过两张具体图形举例说明规律，使结论更易理解，代码简洁，逻辑清晰。
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int main(void) {
	scanf("%d",&t);
	while(t--) {
		scanf("%d%d",&n,&m);
		if(n%m==0) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```
    - **核心实现思想**：与立风yu题解类似，通过 `scanf` 读取数据，利用 `while` 循环处理 \(t\) 组数据，根据取模结果输出相应答案。
- **作者：do_while_true（4星）**
    - **关键亮点**：不仅给出思路和代码，还对结论进行了详细证明，从正多边形外接圆及顶点分布角度分析，逻辑严谨。
    - **重点代码**：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int n,m,T;
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		if(n%m==0) puts("YES");
		else puts("NO");
	}
	return 0;
}
```
    - **核心实现思想**：通过 `cin` 读取数据，`while` 循环处理 \(T\) 组测试用例，依据 \(n\) 对 \(m\) 取模结果输出“YES”或“NO”。

### 最优关键思路或技巧
通过画图观察规律，将几何问题转化为简单的数论问题，利用正多边形顶点与边数的关系，通过判断 \(n\) 是否为 \(m\) 的倍数来解决问题，实现简洁高效。

### 可拓展之处
此类题目属于几何与数论结合的问题，类似套路是通过观察图形特征，找出几何关系与数论关系的联系。同类型题可考虑改变多边形条件，如变为凹多边形，或增加其他限制条件等。

### 洛谷相似题目推荐
- [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)：考察数论中质因数分解相关知识。
- [P1579 哥德巴赫猜想（升级版）](https://www.luogu.com.cn/problem/P1579)：涉及数论中质数与偶数的关系。
- [P2615 神奇的幻方](https://www.luogu.com.cn/problem/P2615)：与数学中的幻方构造有关，需要结合一定的数学规律和算法实现。

### 个人心得摘录与总结
无明显个人心得相关内容。 

---
处理用时：47.20秒