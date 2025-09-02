# 题目信息

# Simple Molecules

## 题目描述

Mad scientist Mike is busy carrying out experiments in chemistry. Today he will attempt to join three atoms into one molecule.

A molecule consists of atoms, with some pairs of atoms connected by atomic bonds. Each atom has a valence number — the number of bonds the atom must form with other atoms. An atom can form one or multiple bonds with any other atom, but it cannot form a bond with itself. The number of bonds of an atom in the molecule must be equal to its valence number.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF344B/e6377325271b4515d315f9767d5c5b94bf56f174.png)Mike knows valence numbers of the three atoms. Find a molecule that can be built from these atoms according to the stated rules, or determine that it is impossible.

## 说明/提示

The first sample corresponds to the first figure. There are no bonds between atoms 1 and 2 in this case.

The second sample corresponds to the second figure. There is one or more bonds between each pair of atoms.

The third sample corresponds to the third figure. There is no solution, because an atom cannot form bonds with itself.

The configuration in the fourth figure is impossible as each atom must have at least one atomic bond.

## 样例 #1

### 输入

```
1 1 2
```

### 输出

```
0 1 1
```

## 样例 #2

### 输入

```
3 4 5
```

### 输出

```
1 3 2
```

## 样例 #3

### 输入

```
4 1 1
```

### 输出

```
Impossible
```

# AI分析结果

### 题目内容
# 简单分子

## 题目描述
疯狂科学家迈克正忙于进行化学实验。今天，他将尝试把三个原子连接成一个分子。

一个分子由原子组成，其中一些原子对通过原子键相连。每个原子都有一个化合价——该原子必须与其他原子形成的键的数量。一个原子可以与任何其他原子形成一个或多个键，但它不能与自身形成键。分子中一个原子的键的数量必须等于它的化合价。

迈克知道这三个原子的化合价。找出一种可以根据上述规则由这些原子构成的分子，或者确定这是不可能的。

## 说明/提示
第一个样例对应第一幅图。在这种情况下，原子1和2之间没有键。

第二个样例对应第二幅图。每对原子之间有一个或多个键。

第三个样例对应第三幅图。没有解决方案，因为一个原子不能与自身形成键。

第四幅图中的配置是不可能的，因为每个原子必须至少有一个原子键。

## 样例 #1
### 输入
```
1 1 2
```
### 输出
```
0 1 1
```

## 样例 #2
### 输入
```
3 4 5
```
### 输出
```
1 3 2
```

## 样例 #3
### 输入
```
4 1 1
```
### 输出
```
Impossible
```

### 算法分类
数学

### 题解综合分析与结论
这些题解主要围绕判断能否根据给定的三个原子化合价构建分子，并找出相应连接方案展开。思路上可分为两类，一类是通过数学推导得出边数计算公式，另一类是采用枚举的方式。各题解都考虑到了一些不可能的情况，如总度数为奇数、边数为负数等。在算法要点上，推导公式的方法利用了图中边与顶点度数的关系，通过解方程或直接推导得出边数；枚举法通过遍历可能的边数组合来寻找符合条件的方案。解决难点在于准确找出不可能的条件并合理推导或枚举。

### 所选的题解
- **作者：Dws_t7760 (5星)**
    - **关键亮点**：思路清晰，先总结出两个关键结论，一是图的边数等于所有顶点度之和除以二，二是任意两个顶点之间的边数为边总数与另一顶点度之差，据此直接计算边数，代码简洁高效。
    ```cpp
    #include<iostream>
    using namespace std;
    int a,b,c,s,s12,s23,s13;
    int main() {
        cin>>a>>b>>c;
        if((a+b+c)%2) {
            cout<<"Impossible";
            return 0;
        }
        s=(a+b+c)/2;
        s12=s-c,s23=s-a,s13=s-b;
        if(s12<0||s23<0||s13<0) cout<<"Impossible";
        else cout<<s12<<' '<<s23<<' '<<s13;
        return 0;
    }
    ```
    - **核心实现思想**：先判断总度数是否为奇数，若为奇数则输出“Impossible”。否则计算总边数，再根据结论计算各顶点间边数，若边数均非负则输出边数，否则输出“Impossible”。
- **作者：20111019Yu (4星)**
    - **关键亮点**：先排除两种不可能的情况，即总度数为奇数和两点度数之和小于另一点度数。然后通过设边数进行推导，得出各点间边数的计算公式，逻辑严谨。
    ```cpp
    #include <bits/stdc++.h>
    using namespace std;
    int a, b, c, x, y, z, d, e;

    int main(){
        cin >> a >> b >> c;
        if((a + b + c) % 2 || (a + b) < c || (b + c) < a || (a + c) < b){
            cout << "Impossible" << endl;
            return 0;
        }
        cout << b - (b + c - a) / 2 << " " << (b + c - a) / 2 << " " << c - (b + c - a) / 2 << endl;
        return 0;
    }
    ```
    - **核心实现思想**：先进行特判，不满足条件则输出“Impossible”。满足条件则根据推导公式计算并输出各顶点间边数。
- **作者：Jerrycyx (4星)**
    - **关键亮点**：通过建立三元一次方程组来求解各顶点间边数，思路直接，对不可能情况的判断全面，且时间复杂度为O(1)。
    ```cpp
    #include<cstdio>
    using namespace std;
    int a,b,c;
    int main()
    {
        scanf("%d%d%d",&a,&b,&c);
        int sum=(a+b+c)>>1;
        int x=sum-c,y=sum-a,z=sum-b;
        if((a+b+c)&1||x<0||y<0||z<0)
            printf("Impossible\n");
        else printf("%d %d %d\n",x,y,z);
        return 0;
    }
    ```
    - **核心实现思想**：解方程组得出各顶点间边数表达式，先判断总度数奇偶性和边数是否非负，满足条件则输出边数，否则输出“Impossible”。

### 最优关键思路或技巧
通过建立数学模型，利用图论中边与顶点度数的关系，如通过三元一次方程组或直接推导得出顶点间边数的计算方法，能高效解决问题。同时准确判断不可能的情况，如总度数的奇偶性、边数的正负性等，是解决此类问题的关键。

### 拓展思路
同类型题通常围绕图的顶点度数与边的关系展开，类似算法套路是根据题目条件建立合适的数学方程或等式来求解未知量，同时注意边界条件和不可能情况的判断。

### 洛谷相似题目推荐
- [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过简单数学计算解决实际问题，锻炼数学思维和条件判断能力。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：需要根据不同包装铅笔的价格和数量，通过数学计算选择最优购买方案。
- [P5723 【深基4.例13】质数口袋](https://www.luogu.com.cn/problem/P5723)：结合数学中的质数判断和简单计算，解决物品选取数量的问题。 

---
处理用时：65.38秒