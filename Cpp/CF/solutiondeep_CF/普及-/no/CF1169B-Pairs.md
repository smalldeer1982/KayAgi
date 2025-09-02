# 题目信息

# Pairs

## 题目描述

Toad Ivan has $ m $ pairs of integers, each integer is between $ 1 $ and $ n $ , inclusive. The pairs are $ (a_1, b_1), (a_2, b_2), \ldots, (a_m, b_m) $ .

He asks you to check if there exist two integers $ x $ and $ y $ ( $ 1 \leq x < y \leq n $ ) such that in each given pair at least one integer is equal to $ x $ or $ y $ .

## 说明/提示

In the first example, you can't choose any $ x $ , $ y $ because for each such pair you can find a given pair where both numbers are different from chosen integers.

In the second example, you can choose $ x=2 $ and $ y=4 $ .

In the third example, you can choose $ x=1 $ and $ y=2 $ .

## 样例 #1

### 输入

```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
5 4
1 2
2 3
3 4
4 5
```

### 输出

```
YES
```

## 样例 #3

### 输入

```
300000 5
1 2
1 2
1 2
1 2
1 2
```

### 输出

```
YES
```

# AI分析结果

### 题目内容
# Pairs
## 题目描述
蟾蜍伊万（Toad Ivan）有$m$对整数，每一个整数都在$1$到$n$之间（包含$1$和$n$）。这些数对为$(a_1, b_1), (a_2, b_2), \ldots, (a_m, b_m)$ 。
他让你检查是否存在两个整数$x$和$y$（$1 \leq x < y \leq n$），使得在每一个给定的数对中，至少有一个整数等于$x$或者$y$。
## 说明/提示
在第一个样例中，你无法选择任何$x$，$y$，因为对于每一对这样的数，你都可以找到一个给定的数对，其中两个数都与所选整数不同。
在第二个样例中，你可以选择$x = 2$和$y = 4$。
在第三个样例中，你可以选择$x = 1$和$y = 2$。
## 样例 #1
### 输入
```
4 6
1 2
1 3
1 4
2 3
2 4
3 4
```
### 输出
```
NO
```
## 样例 #2
### 输入
```
5 4
1 2
2 3
3 4
4 5
```
### 输出
```
YES
```
## 样例 #3
### 输入
```
300000 5
1 2
1 2
1 2
1 2
1 2
```
### 输出
```
YES
```
### 算法分类
枚举

### 综合分析与结论
这些题解的核心思路大多基于枚举思想。多数题解以第一对数$(a_1, b_1)$为基准，分别考虑$x$或$y$为$a_1$或$b_1$的情况，统计其余数对中不包含$x$或$y$时其他数出现的次数，判断是否能找到满足条件的$x$和$y$。少数题解采用暴力枚举所有可能的$x$和$y$组合。各题解的主要区别在于实现细节和代码的简洁性。

### 所选的题解
- **Trimsteanima（4星）**
  - **关键亮点**：思路清晰，代码简洁，利用数组统计非基准数出现的最大次数，通过一次遍历完成判断。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 10;
int n, m, a, b, x, y, sum, sum1, sum2, sum3, a1[N], a2[N];
int main() {
    scanf("%d%d%d%d", &n, &m, &x, &y);
    sum1 = sum = 1;
    for (int i = 1; i < m; i++) {
        scanf("%d%d", &a, &b);
        if (a == x || b == x) sum++; else sum2 = std::max(sum2, std::max(++a1[a], ++a1[b]));
        if (a == y || b == y) sum1++;else sum3 = std::max(sum3, std::max(++a2[a], ++a2[b]));
    }
    if (sum + sum2 == m || sum1 + sum3 == m) puts("YES"); else puts("NO");
    return 0;
}
```
  - **核心实现思想**：以输入的$x$，$y$为基准（实际应为第一对数），遍历其余数对，统计包含$x$或$y$的数对数量`sum`和`sum1`，同时统计不包含$x$或$y$时其余数在`a1`和`a2`数组中出现的最大次数`sum2`和`sum3`，最后判断是否满足条件。
- **YangXiaopei（4星）**
  - **关键亮点**：与Trimsteanima思路相似，代码逻辑清晰，采用`cin`和`cout`输入输出，更符合C++风格。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, x, y, sum, sum1, sum2, sum3, a1[3000005], a2[4000005];
int main() {
    cin >> n >> m >> x >> y;
    sum1 = sum = 1;
    for(int i = 1; i < m; i++){
        cin >> a >> b;
        if(a == x || b == x){
            sum++;
        }
        else{
            sum2 = max(sum2, max(++a1[a], ++a1[b]));
        }
        if(a == y || b == y){
            sum1++;
        }
        else{
            sum3 = max(sum3, max(++a2[a], ++a2[b]));
        }
    }
    if(sum + sum2 == m || sum1 + sum3 == m){
        cout << "YES";
        return 0;
    }
    cout << "NO";
    return 0;
}
```
  - **核心实现思想**：同Trimsteanima，以输入的$x$，$y$为基准（实际应为第一对数），遍历数对，统计相关数量并判断。
- **rainbow_cat（4星）**
  - **关键亮点**：思路清晰，代码简洁明了，使用`cin`、`cout`且利用`ios::sync_with_stdio(0)`等优化输入输出，逻辑与其他高星题解类似。
  - **重点代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,a,b,x,y,sumx,sumy,maxn,maxm,numx[3000010],numy[3000010];
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>x>>y;
    sumx=sumy=1;
    for(int i=1;i<m;i++)
    {
        cin>>a>>b;
        if(a==x||b==x)sumx++;//记录x的个数
        else maxn=max(maxn,max(++numx[a],++numx[b]));//记录可能的y的个数
        if(a==y||b==y)sumy++;//记录y的个数
        else maxm=max(maxm,max(++numy[a],++numy[b]));//记录可能x的个数
    }
    if(sumx+maxn==m||sumy+maxm==m)cout<<"YES";
    else cout<<"NO";
    return 0;
}
```
  - **核心实现思想**：以输入的$x$，$y$为基准（实际应为第一对数），遍历数对，分别统计包含$x$或$y$的数对个数`sumx`、`sumy`，以及不包含$x$或$y$时其余数在`numx`和`numy`数组中出现的最大次数`maxn`、`maxm`，最后判断是否满足条件。

### 最优关键思路或技巧
以第一对数为基准进行枚举，通过数组统计非基准数出现的情况，减少枚举量，优化算法时间复杂度。利用一次遍历完成所有统计工作，提高代码效率。

### 拓展
此类题目属于基于条件判断的枚举类型，类似套路为确定一个较小范围的枚举对象（如本题以第一对数为基准），通过统计相关数据来判断是否满足条件。同类型题可考虑增加数对的约束条件，或者改变判断满足条件的规则等。

### 洛谷相似题目
- [P1118 数字三角形](https://www.luogu.com.cn/problem/P1118)：通过枚举路径来寻找最优解，与本题枚举满足条件的数对思路类似。
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：需要枚举组合来判断是否满足质数条件，涉及枚举与条件判断。
- [P1423 小玉在游泳](https://www.luogu.com.cn/problem/P1423)：通过枚举天数来判断是否达到目标距离，也是枚举类型题目。 

---
处理用时：84.22秒