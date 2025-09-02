# 题目信息

# [USACO2.1] 顺序的分数 Ordered Fractions

## 题目描述

输入一个自然数 $n$，对于一个最简分数 $a/b$（分子和分母互质的分数），满足 $1 \le b \le n,0 \le a/b \le 1$，请找出所有满足条件的分数。

这有一个例子，当 $n=5$ 时，所有解为：

$$\frac01,\frac15,\frac14,\frac13,\frac25,\frac12,\frac35,\frac23,\frac34 ,\frac45,\frac11$$

给定一个自然数 $n$，请编程按分数值递增的顺序输出所有解。
 
注：   
1、$0$ 和任意自然数的最大公约数就是那个自然数。    
2、互质指最大公约数等于1的两个自然数。


## 说明/提示

【数据范围】    
对于 $100\%$ 的数据，$1\le n \le 160$。

USACO 2.1

翻译来自NOCOW


## 样例 #1

### 输入

```
5
```

### 输出

```
0/1
1/5
1/4
1/3
2/5
1/2
3/5
2/3
3/4
4/5
1/1
```

# AI分析结果

### 综合分析与结论
这些题解主要分为枚举排序和分治两种思路。枚举排序思路是先枚举所有可能的分数，判断其是否为最简分数，再对符合条件的分数按值排序输出；分治思路则是利用数学性质，在两个分数间插入新分数并递归处理，以按顺序得到结果。

### 所选题解
- **作者：浮尘ii（5星）**
    - **关键亮点**：引入Stern - Brocot Tree的分治思想，从数学原理上进行深入分析，证明了算法的正确性，代码简洁高效。
    - **核心代码**：
```cpp
#include <iostream>
#include <cstdio>

using namespace std;

int    N;

void DFS(const int& l1, const int& l2, const int& r1, const int& r2)
{
    if(l2 > N || r2 > N)
        return;

    DFS(l1, l2, l1 + r1, l2 + r2);
    if(l2 + r2 <= N)
        printf("%d/%d\n", l1 + r1, l2 + r2);
    DFS(l1 + r1, l2 + r2, r1, r2);
}

int main()
{
    cin >> N;

    printf("0/1\n");
    DFS(0, 1, 1, 1);
    printf("1/1\n");

    return 0;
}
```
    - **核心思想**：从`0/1`和`1/1`开始，在两个分数`a/b`和`c/d`间插入`(a + c)/(b + d)`，并递归处理左右区间，保证输出分数按顺序排列。

- **作者：robin2333（4星）**
    - **关键亮点**：详细证明了分治方法中两个重要性质，理论基础扎实，代码简洁明了。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;

void dfs(int a1,int a2,int b1,int b2){
    if(b2>n||b1>n)return;
    dfs(a1,a1+a2,b1,b1+b2);
    if(b1+b2<=n)cout<<a1+a2<<"/"<<b1+b2<<endl;
    dfs(a1+a2,a2,b1+b2,b2);
}

int main(){
    cin>>n;
    cout<<0<<"/"<<1<<endl;
    dfs(0,1,1,1);
    cout<<1<<"/"<<1<<endl;
}
```
    - **核心思想**：与浮尘ii的思路类似，通过递归分治生成符合条件的最简分数并输出。

- **作者：tql_____（4星）**
    - **关键亮点**：思路清晰，详细阐述了枚举、判断互质和排序的步骤，使用交叉相乘比较分数大小，避免精度问题。
    - **核心代码**：
```c
#include<bits/stdc++.h>
using namespace std;
int n;
int cnt;
struct number
{
    int fenzi;
    int fenmu;
} a[1000001];
bool cmp(number a,number b)
{
    return (a.fenzi*b.fenmu)<(a.fenmu*b.fenzi);
}
bool huzhi(int x, int y)
{
    if(x <=0 || y<=0 || x==y)   
        return false;
    else if(x==1 || y==1)     
        return true;
    else
    {
        while(1)
        {
            int t = x%y;
            if(t == 0)
                break;
            else
            {
                x = y;
                y = t;
            }
        }
        if( y > 1)   
            return false;
        else    
            return true;
    }
}

int main()
{
    cin>>n;
    printf("0/1\n");

    for(int i=2; i<=n; i++)
    {
        for(int j=1; j<i; j++)
        {
            if(huzhi(i,j))
            {
                cnt++;
                a[cnt].fenmu=i;
                a[cnt].fenzi=j;
            }
        }
    }

    sort(a+1,a+cnt+1,cmp);

    for(int i=1; i<=cnt; i++)
        cout<<a[i].fenzi<<"/"<<a[i].fenmu<<endl;

    printf("1/1\n");
    
    return 0;
}
```
    - **核心思想**：枚举所有可能的分数，用辗转相除法判断互质，用交叉相乘比较大小进行排序后输出。

### 最优关键思路或技巧
- **分治思想**：利用Stern - Brocot Tree的分治方法，可直接按顺序生成最简分数，避免排序操作，提高效率。
- **交叉相乘比较分数大小**：避免将分数转化为小数比较，防止精度误差。
- **使用结构体存储分数**：方便记录分数的分子、分母和值，便于排序和处理。

### 可拓展之处
同类型题如求一定范围内的最简分数个数、求指定分数在最简分数序列中的位置等。类似算法套路可应用于其他需要生成有序序列的问题，通过分治或枚举排序的方法解决。

### 推荐题目
- P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题
- P1072 [NOIP2009 提高组] Hankson 的趣味题
- P1372 又是毕业季I

### 个人心得摘录与总结
- **御·Dragon**：提到数组不能开小，一开始把判断大小的大于号写成小于号，提醒我们在编码时要注意边界条件和逻辑判断。
- **袁宇轩**：指出用除法算商比较存在精度误差，建议用交叉相乘比较，强调了处理分数比较时要考虑精度问题。 

---
处理用时：38.19秒