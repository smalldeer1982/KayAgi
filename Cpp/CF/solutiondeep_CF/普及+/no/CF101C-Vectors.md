# 题目信息

# Vectors

## 题目描述

At a geometry lesson Gerald was given a task: to get vector $ B $ out of vector $ A $ . Besides, the teacher permitted him to perform the following operations with vector $ А $ :

- Turn the vector by $ 90 $ degrees clockwise.
- Add to the vector a certain vector $ C $ .

Operations could be performed in any order any number of times.

Can Gerald cope with the task?

## 样例 #1

### 输入

```
0 0
1 1
0 1
```

### 输出

```
YES
```

## 样例 #2

### 输入

```
0 0
1 1
1 1
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
0 0
1 1
2 2
```

### 输出

```
NO
```

# AI分析结果

### 题目内容
# 向量

## 题目描述
在一次几何课上，杰拉尔德接到一项任务：从向量A得到向量B。此外，老师允许他对向量A执行以下操作：
- 将向量顺时针旋转90度。
- 给向量加上某个向量C。
操作可以按任意顺序执行任意次数。
杰拉尔德能完成这项任务吗？

## 样例 #1
### 输入
```
0 0
1 1
0 1
```
### 输出
```
YES
```

## 样例 #2
### 输入
```
0 0
1 1
1 1
```
### 输出
```
YES
```

## 样例 #3
### 输入
```
0 0
1 1
2 2
```
### 输出
```
NO
```

### 算法分类
数学

### 综合分析与结论
三道题解思路本质相同，均基于向量旋转公式得出向量A旋转后的几种固定形式，通过建立向量方程转化为二元一次方程组，判断方程组是否有整数解来确定能否从向量A得到向量B，同时都注意到向量C为零向量的特殊情况。不同点在于方程推导过程和代码实现细节。

### 所选的题解
- **作者：Remake_ (5星)**
    - **关键亮点**：思路清晰，详细推导从向量方程到二元一次方程组的过程，代码实现完整且对多种情况考虑全面。
    - **个人心得**：提到初始时A有可能已旋转，有四种情况需考虑，较为细心。
```cpp
#include <bits/stdc++.h>
using namespace std;
long long ax, ay, bx, by, cx, cy;
void check(long long axx, long long ayy)
{
    if (cx * cx + cy * cy == 0)
    {
        if (axx == bx && ayy == by)
        {
            cout << "YES";
            exit(0);
        }
        else
            return;
    }
    if ((cx * (by - ayy) - cy * (bx - axx)) % (cx * cx + cy * cy)!= 0 || (cx * (bx - axx) + cy * (by - ayy)) % (cx * cx + cy * cy)!= 0)
        return;
    cout << "YES";
    exit(0);
}
int main()
{
    cin >> ax >> ay >> bx >> by >> cx >> cy;
    check(ax, ay);
    check(ay, -ax);
    check(-ax, -ay);
    check(-ay, ax);
    cout << "NO";
}
```
核心实现思想：`check`函数中先处理向量C为零向量时A与B是否相等，再判断方程组解是否为整数，`main`函数遍历A的四种初始旋转情况调用`check`函数。

- **作者：ncwzdlsd (4星)**
    - **关键亮点**：代码简洁明了，通过宏定义简化变量名，逻辑清晰。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define x1 x11
#define x2 x22
#define y1 y11
#define y2 y22

int a,b,x1,y1,x2,y2;

bool check(int x,int y)
{
	x-=x2,y-=y2;
	int tmp=a*a+b*b;
	if(!tmp) return x==0&&y==0;
	return (a*x+b*y)%tmp==0&&(a*y-b*x)%tmp==0;
}

signed main()
{
	cin>>x1>>y1>>x2>>y2>>a>>b;
	bool flag=0;
	if(check(x1,y1)||check(-x1,-y1)||check(y1,-x1)||check(-y1,x1)) flag=1;
	printf("%s",flag?"YES":"NO");
	return 0;
}
```
核心实现思想：`check`函数判断方程组解是否为整数，`main`函数遍历A的四种初始旋转情况调用`check`函数判断能否从A得到B。

### 最优关键思路或技巧
利用向量旋转公式确定向量A旋转后的有限种形式，将向量关系转化为二元一次方程组，通过判断方程组整数解来解决问题，同时注意零向量等特殊情况。

### 可拓展之处
此类题目可拓展到更复杂的向量变换和操作，或在更高维度空间下的向量问题。类似算法套路为将几何问题通过数学公式转化为代数方程求解。

### 洛谷题目推荐
- P1082 [NOIP2012 提高组] 同余方程，考察数论中求解同余方程，与本题判断方程整数解思路相关。
- P2613 【模板】有理数取余，涉及有理数运算和取余，与本题数学运算和特殊情况判断有关。
- P1516 青蛙的约会，同样是通过建立方程并求解整数解来解决问题，和本题思路类似。 

---
处理用时：42.43秒