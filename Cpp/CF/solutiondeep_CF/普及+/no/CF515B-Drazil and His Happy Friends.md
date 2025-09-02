# 题目信息

# Drazil and His Happy Friends

## 题目描述

Drazil has many friends. Some of them are happy and some of them are unhappy. Drazil wants to make all his friends become happy. So he invented the following plan.

There are $ n $ boys and $ m $ girls among his friends. Let's number them from $ 0 $ to $ n-1 $ and $ 0 $ to $ m-1 $ separately. In $ i $ -th day, Drazil invites ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515B/0da6b9a3d02abb66f05faf59011ade551446e858.png)-th boy and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515B/b11adea5506a14de900c875f929fb5324c4eb93f.png)-th girl to have dinner together (as Drazil is programmer, $ i $ starts from $ 0 $ ). If one of those two people is happy, the other one will also become happy. Otherwise, those two people remain in their states. Once a person becomes happy (or if he/she was happy originally), he stays happy forever.

Drazil wants to know whether he can use this plan to make all his friends become happy at some moment.

## 说明/提示

By ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF515B/bc360a33d2d53f2f08a31e2a137952fc77466359.png) we define the remainder of integer division of $ i $ by $ k $ .

In first sample case:

- On the 0-th day, Drazil invites 0-th boy and 0-th girl. Because 0-th girl is happy at the beginning, 0-th boy become happy at this day.
- On the 1-st day, Drazil invites 1-st boy and 1-st girl. They are both unhappy, so nothing changes at this day.
- On the 2-nd day, Drazil invites 0-th boy and 2-nd girl. Because 0-th boy is already happy he makes 2-nd girl become happy at this day.
- On the 3-rd day, Drazil invites 1-st boy and 0-th girl. 0-th girl is happy, so she makes 1-st boy happy.
- On the 4-th day, Drazil invites 0-th boy and 1-st girl. 0-th boy is happy, so he makes the 1-st girl happy. So, all friends become happy at this moment.

## 样例 #1

### 输入

```
2 3
0
1 0
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
2 4
1 0
1 2
```

### 输出

```
No
```

## 样例 #3

### 输入

```
2 3
1 0
1 1
```

### 输出

```
Yes
```

# AI分析结果

### 题目内容
# Drazil和他快乐的朋友们

## 题目描述
Drazil有许多朋友，其中一些人快乐，一些人不快乐。Drazil想让他所有的朋友都变得快乐，所以他想出了以下计划。

他的朋友中有n个男孩和m个女孩。我们分别将他们从0到n - 1和0到m - 1编号。在第i天，Drazil邀请编号为i % n的男孩和编号为i % m的女孩一起共进晚餐（因为Drazil是程序员，i从0开始）。如果这两个人中有一个是快乐的，另一个也会变得快乐。否则，这两个人保持他们原来的状态。一旦一个人变得快乐（或者如果他/她原本就是快乐的），他就会永远快乐。

Drazil想知道他是否可以通过这个计划在某个时刻让他所有的朋友都变得快乐。

## 说明/提示
通过a % b我们定义为整数a除以b的余数。

在第一个样例中：
- 在第0天，Drazil邀请0号男孩和0号女孩。因为0号女孩一开始就是快乐的，所以0号男孩在这一天变得快乐。
- 在第1天，Drazil邀请1号男孩和1号女孩。他们两个都不快乐，所以这一天没有变化。
- 在第2天，Drazil邀请0号男孩和2号女孩。因为0号男孩已经快乐了，所以他让2号女孩在这一天变得快乐。
- 在第3天，Drazil邀请1号男孩和0号女孩。0号女孩快乐，所以她让1号男孩快乐。
- 在第4天，Drazil邀请0号男孩和1号女孩。0号男孩快乐，所以他让1号女孩快乐。所以，在这个时刻所有朋友都变得快乐了。

## 样例 #1
### 输入
```
2 3
0
1 0
```
### 输出
```
Yes
```

## 样例 #2
### 输入
```
2 4
1 0
1 2
```
### 输出
```
No
```

## 样例 #3
### 输入
```
2 3
1 0
1 1
```
### 输出
```
Yes
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要分为两种思路。一种是纯模拟思路，利用题目数据范围小的特点，通过模拟 $2\times lcm(n,m)$（或 $2\times n\times m$ ，因为 $lcm(n,m)\leq n\times m$）次邀请过程，每次更新男孩和女孩的快乐状态，最后扫描判断是否所有朋友都快乐。另一种是结合数论的思路，通过分析发现 $(i - j)\bmod \gcd(n,m) = 0$ 的位置的人能够相遇，基于此将所有可能碰到一起的人分组，组内只要有一个乐观的人就能传染给组内所有人，通过判断所有组是否都有乐观的人来得出结论。

### 所选的题解
- **作者：Dry_ice（4星）**
  - **关键亮点**：结合暴力模拟和数论知识（GCD），通过求最大公约数简化判断过程，时间复杂度低。
  - **重点代码**：
```cpp
int G=std::__gcd(n,m); 
if(G==1) {
    if(b+g>=1)printf("Yes\n");
    else printf("No\n");
    return 0;
}
for(int i=0; i<n; ++i)if(x[i])tmp[i%G]=1;
for(int i=0; i<m; ++i)if(y[i])tmp[i%G]=1;
s=0;
for(int i=0; i<G; ++i)
    s+=tmp[i];
if(s==G) printf("Yes\n");
else printf("No\n");
```
  - **核心实现思想**：先求 $n$ 和 $m$ 的最大公约数 $G$ ，若 $G = 1$ ，只要有一个人快乐就能让所有人快乐；否则，将男孩和女孩按对 $G$ 取模分组，判断每组是否都有快乐的人。
- **作者：XL4453（4星）**
  - **关键亮点**：给出 $O(n + m)$ 的数论解法，思路清晰，复杂度低。通过证明将所有可能碰到一起的人按 $\gcd(n,m)$ 分组的合理性，然后基于分组判断能否让所有人快乐。
  - **重点代码**：
```cpp
int gcd(int a,int b){
    if(b==0)return a;
    return gcd(b,a%b);
}
//...
GCD=gcd(n,m);
//...
for(int u=0;u<GCD;u++){
    for(int i=u;i<=n;i+=GCD)cur[u]|=a[i];
    for(int i=u;i<=m;i+=GCD)cur[u]|=b[i];
}
int flag=1;
for(int i=0;i<GCD;i++)
    flag&=cur[i];
if(flag)printf("Yes\n");
else printf("No\n");
```
  - **核心实现思想**：先求最大公约数 $GCD$ ，然后遍历所有分组，判断每组内是否有快乐的人，若所有组都有则输出Yes，否则输出No。

### 最优关键思路或技巧
结合数论知识（如最大公约数）对问题进行分析和简化。通过证明得出按 $\gcd(n,m)$ 对人员分组的结论，利用组内快乐状态的传递性，降低时间复杂度，提高解题效率。

### 同类型题或类似算法套路拓展
此类题目通常涉及状态的传递和循环规律，关键在于发现其中隐藏的数学规律（如周期、余数关系等），利用数论知识简化问题。在遇到类似有循环操作且状态相互影响的题目时，可以尝试寻找操作序列中的数学规律，通过分组、取模等方式简化模拟过程。

### 洛谷相似题目推荐
- [P1082 同余方程](https://www.luogu.com.cn/problem/P1082)：考察数论中的同余方程和扩展欧几里得算法，与本题结合数论知识解题思路类似。
- [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)：同样涉及数论中的取模运算及相关性质的应用，和本题利用数论简化问题的思路相符。
- [P1572 计算分数的精确值](https://www.luogu.com.cn/problem/P1572)：通过模拟除法运算过程，结合余数规律解决问题，与本题模拟过程中结合数论规律有相似之处。 

---
处理用时：62.85秒