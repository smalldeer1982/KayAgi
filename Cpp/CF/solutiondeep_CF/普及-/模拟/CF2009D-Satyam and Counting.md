# 题目信息

# Satyam and Counting

## 题目描述

Satyam is given $ n $ distinct points on the 2D coordinate plane. It is guaranteed that $ 0 \leq y_i \leq 1 $ for all given points $ (x_i, y_i) $ . How many different nondegenerate right triangles $ ^{\text{∗}} $ can be formed from choosing three different points as its vertices?

Two triangles $ a $ and $ b $ are different if there is a point $ v $ such that $ v $ is a vertex of $ a $ but not a vertex of $ b $ .

 $ ^{\text{∗}} $ A nondegenerate right triangle has positive area and an interior $ 90^{\circ} $ angle.

## 说明/提示

The four triangles in question for the first test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2009D/34af5d1e01dabd5b071d413da74fdbeb85cca657.png)

## 样例 #1

### 输入

```
3
5
1 0
1 1
3 0
5 0
2 1
3
0 0
1 0
3 0
9
1 0
2 0
3 0
4 0
5 0
2 1
7 1
8 1
9 1```

### 输出

```
4
0
8```

# AI分析结果

### 题目中文重写
# Satyam与计数

## 题目描述
Satyam 得到了二维坐标平面上的 $n$ 个不同的点。保证对于所有给定的点 $(x_i, y_i)$ 都有 $0 \leq y_i \leq 1$。从这些点中选择三个不同的点作为顶点，可以形成多少个不同的非退化直角三角形 $^{\text{∗}}$ 呢？

如果存在一个点 $v$，使得 $v$ 是三角形 $a$ 的顶点但不是三角形 $b$ 的顶点，那么这两个三角形 $a$ 和 $b$ 就是不同的。

$^{\text{∗}}$ 非退化直角三角形的面积为正，并且有一个内角为 $90^{\circ}$。

## 说明/提示
第一个测试用例所涉及的四个三角形如下：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF2009D/34af5d1e01dabd5b071d413da74fdbeb85cca657.png)

## 样例 #1

### 输入
```
3
5
1 0
1 1
3 0
5 0
2 1
3
0 0
1 0
3 0
9
1 0
2 0
3 0
4 0
5 0
2 1
7 1
8 1
9 1
```

### 输出
```
4
0
8
```

### 题解综合分析与结论
- **思路对比**：各位作者都将可形成的直角三角形分为两类进行讨论。一类是有两条直角边垂直于坐标轴的情况，另一类是两条直角边不垂直于坐标轴的 45 度等腰直角三角形情况。
- **算法要点**：
    - 对于第一类三角形，若存在点 $(t,0)$ 和 $(t,1)$，则其余 $n - 2$ 个点都能与之构成直角三角形。
    - 对于第二类三角形，当直角顶点为 $(t,0)$ 时，另外两个顶点为 $(t - 1,1)$ 和 $(t + 1,1)$；当直角顶点为 $(t,1)$ 时，另外两个顶点为 $(t - 1,0)$ 和 $(t + 1,0)$。
- **解决难点**：关键在于准确分类并枚举所有可能的点组合，同时要注意数据的清空操作，避免因数据残留导致错误。

### 所选题解
- **作者：coderJerry（5星）**
    - **关键亮点**：思路清晰，代码简洁，详细说明了分类情况，并给出了动图辅助理解，同时提醒了清空数据的重要性。
    - **个人心得**：“清空不彻底，被 hack 两行泪！”，强调了在多组测试数据的情况下，清空数据的重要性，否则可能会导致错误。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int v[200010][2];//v[x][y] 表示 (x,y) 是否出现过
signed main(){
    int t,x,y,n,ans=0;
    cin>>t;
    while(t--){
        ans=0;
        cin>>n;
        for(int i=0;i<=200000;i++){v[i][0]=v[i][1]=0;}//清空不彻底，被hack两行泪！
        for(int i=1;i<=n;i++){
            cin>>x>>y;
            v[x][y]=1;
        }
        for(int i=0;i<=n;i++){
            if(v[i][0]==1&&v[i][1]==1)ans+=(n-2);//case1
            if(v[i][1]==1&&v[i-1][0]==1&&v[i+1][0]==1)ans++;//case2-1
            if(v[i][0]==1&&v[i-1][1]==1&&v[i+1][1]==1)ans++;//case2-2
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
核心实现思想：使用二维数组 `v` 记录每个点是否出现，然后遍历所有可能的点，根据两类三角形的条件进行计数。

### 最优关键思路或技巧
- 采用分类讨论的思维方式，将复杂的问题简单化。
- 使用数组或 `map` 来记录点的存在情况，方便后续的枚举和判断。

### 可拓展之处
同类型题目可能会改变点的坐标范围、三角形的类型（如钝角三角形、锐角三角形）等。解题的关键仍然是对不同类型的三角形进行分类讨论，并通过合适的数据结构记录点的信息。

### 推荐洛谷题目
- [P1313 计算系数](https://www.luogu.com.cn/problem/P1313)
- [P1044 栈](https://www.luogu.com.cn/problem/P1044)
- [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)

---
处理用时：28.65秒