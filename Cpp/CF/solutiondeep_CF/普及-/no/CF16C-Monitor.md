# 题目信息

# Monitor

## 题目描述

Reca company makes monitors, the most popular of their models is AB999 with the screen size $ a×b $ centimeters. Because of some production peculiarities a screen parameters are integer numbers. Recently the screen sides ratio $ x:y $ became popular with users. That's why the company wants to reduce monitor AB999 size so that its screen sides ratio becomes $ x:y $ , at the same time they want its total area to be maximal of all possible variants. Your task is to find the screen parameters of the reduced size model, or find out that such a reduction can't be performed.

## 样例 #1

### 输入

```
800 600 4 3
```

### 输出

```
800 600
```

## 样例 #2

### 输入

```
1920 1200 16 9
```

### 输出

```
1920 1080
```

## 样例 #3

### 输入

```
1 1 1 2
```

### 输出

```
0 0
```

# AI分析结果

### 题目内容
# Monitor

## 题目描述
Reca公司生产显示器，其最受欢迎的型号是AB999，屏幕尺寸为a×b厘米。由于一些生产特点，屏幕参数为整数。最近，屏幕边长比例x:y受到用户欢迎。因此，该公司希望缩小AB999显示器的尺寸，使其屏幕边长比例变为x:y，同时希望其总面积在所有可能的变体中最大。你的任务是找出缩小尺寸后型号的屏幕参数，或者找出无法进行这种缩小的情况。

## 样例 #1
### 输入
```
800 600 4 3
```
### 输出
```
800 600
```

## 样例 #2
### 输入
```
1920 1200 16 9
```
### 输出
```
1920 1080
```

## 样例 #3
### 输入
```
1 1 1 2
```
### 输出
```
0 0
```

### 算法分类
数学

### 题解综合分析与结论
所有题解思路核心一致，均先对比例x, y进行化简（求最大公约数后约分），再判断a, b是否能满足比例要求（x <= a且y <= b ），若满足则通过不同方式确定缩放比例，进而得出满足条件的最大面积屏幕尺寸。不同点在于确定缩放比例的方式：
 - **RagnaLP和jijidawang以及Andysun06**：思路简洁直接，通过计算a/x和b/y的最小值作为缩放比例基数，认为此基数能保证结果在a, b范围内且满足比例要求。
 - **rayluo**：尝试分别以a、b为基准取满足x整除a和y整除b的最大值，再根据比例算出另一边长，对比两种情况取乘积更大者，过程稍复杂但同样能保证结果最优。
 - **Eraine**：思路与前三者类似，但化简部分出现错误，应该化简x, y而非a, b。

### 所选的题解
 - **作者：RagnaLP (5星)**
    - **关键亮点**：思路清晰简洁，代码实现直接明了，通过求最大公约数化简比例，再利用min函数确定缩放比例，高效解决问题。
    ```cpp
    int gcd(int n,int m){
        if(n<m) swap(n,m);
        return n==0?n:gcd(m,n%m);
    }
    int main() {
        cin>>a>>b>>x>>y;
        int k=gcd(x,y);
        x/=k,y/=k;
        if(a<x||b<y){
            printf("0 0");
            return 0;
        }
        int base=min(a/x,b/y);
        printf("%d %d",x*base,y*base);
        return 0;
    }
    ```
    - **核心实现思想**：首先用辗转相除法求x, y的最大公约数并化简比例，然后判断a, b能否满足比例要求，若能则通过a/x和b/y的最小值确定缩放基数，最后得出满足条件的屏幕尺寸。
 - **作者：jijidawang (4星)**
    - **关键亮点**：题面简述和算法分析简洁明了，准确抓住核心要点，即化简比例、判断可行性、确定缩放比并计算结果。
    ```cpp
    // 伪代码示意核心思路
    // 1. 化简x, y
    k = gcd(x, y);
    x /= k;
    y /= k;
    // 2. 判断可行性
    if (x > a || y > b) return "0 0";
    // 3. 确定缩放比并计算结果
    k = min(a / x, b / y);
    result_a = x * k;
    result_b = y * k;
    ```
    - **核心实现思想**：先对x, y进行约分，判断无解情况，再通过计算a/x和b/y的最小值作为缩放比，分别乘x, y得到结果。
 - **作者：rayluo (4星)**
    - **关键亮点**：深入分析使乘积最大的条件，通过分别以a、b为基准计算并对比，确保得到最优解，考虑全面。
    ```cpp
    in ll gcd(ll x0,ll y0)  {
        return y0?gcd(y0,x0%y0):x0;
    }
    int main()
    {
        a=read();
        a1=a;
        b=read();
        b1=b;
        x=read();
        y=read();
        ll k=gcd(x,y);
        x/=k;
        y/=k;
        if(x>a||y>b) {
            puts("0 0");
            return 0;
        }
        a=(a/x)*x;
        b=(a/x)*y;
        if(a<=a1&&b<=b1) {
            ansa=a;
            ansb=b;
        }
        a=a1;
        b=b1;
        b=(b/y)*y;
        a=(b/y)*x;
        if(a<=a1&&b<=b1) {
            if(ansa*ansb<a*b) {
                ansa=a;
                ansb=b;
            }
        }
        cout<<ansa<<" "<<ansb<<endl;
        return 0;
    } 
    ```
    - **核心实现思想**：先化简x, y并判断无解情况，接着分别假设a、b取满足整除条件的最大值，根据比例算出另一边长，判断是否符合条件并取乘积更大的结果。

### 最优关键思路或技巧
先将比例x, y化简为最简整数比，可避免后续计算出现偏差。通过求a/x和b/y的最小值来确定缩放比例，能直观且高效地找到在a, b范围内满足x:y比例且面积最大的解。若从更严谨角度，像rayluo的方法，分别以a、b为基准计算并对比取优，逻辑更加严密。

### 拓展
同类型题目通常围绕几何图形的边长比例、面积体积变化等结合数论知识考查。类似算法套路为遇到比例问题先化简，再根据给定条件判断可行性，最后通过合理的缩放计算得出结果。

### 洛谷相似题目推荐
 - [P1025 数的划分](https://www.luogu.com.cn/problem/P1025)：考查整数划分与数学规律应用。
 - [P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)：涉及数论中质因数分解相关知识。
 - [P1888 三角函数](https://www.luogu.com.cn/problem/P1888)：结合三角函数知识与数论进行求解。 

---
处理用时：47.87秒