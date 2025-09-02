# 题目信息

# Minimum Value Rectangle

## 题目描述

You have $ n $ sticks of the given lengths.

Your task is to choose exactly four of them in such a way that they can form a rectangle. No sticks can be cut to pieces, each side of the rectangle must be formed by a single stick. No stick can be chosen multiple times. It is guaranteed that it is always possible to choose such sticks.

Let $ S $ be the area of the rectangle and $ P $ be the perimeter of the rectangle.

The chosen rectangle should have the value $ \frac{P^2}{S} $ minimal possible. The value is taken without any rounding.

If there are multiple answers, print any of them.

Each testcase contains several lists of sticks, for each of them you are required to solve the problem separately.

## 说明/提示

There is only one way to choose four sticks in the first list, they form a rectangle with sides $ 2 $ and $ 7 $ , its area is $ 2 \cdot 7 = 14 $ , perimeter is $ 2(2 + 7) = 18 $ . $ \frac{18^2}{14} \approx 23.143 $ .

The second list contains subsets of four sticks that can form rectangles with sides $ (1, 2) $ , $ (2, 8) $ and $ (1, 8) $ . Their values are $ \frac{6^2}{2} = 18 $ , $ \frac{20^2}{16} = 25 $ and $ \frac{18^2}{8} = 40.5 $ , respectively. The minimal one of them is the rectangle $ (1, 2) $ .

You can choose any four of the $ 5 $ given sticks from the third list, they will form a square with side $ 5 $ , which is still a rectangle with sides $ (5, 5) $ .

## 样例 #1

### 输入

```
3
4
7 2 2 7
8
2 8 1 4 8 2 1 5
5
5 5 5 5 5
```

### 输出

```
2 7 7 2
2 2 1 1
5 5 5 5
```

# AI分析结果

### 题目翻译
#### 最小价值矩形

##### 题目描述
你有 $n$ 根给定长度的木棍。

你的任务是恰好选择其中的四根，使得它们能够组成一个矩形。不允许将木棍截断，矩形的每一条边都必须由一根完整的木棍构成，且每根木棍不能被重复选择。题目保证一定可以选出这样的四根木棍。

设 $S$ 为矩形的面积，$P$ 为矩形的周长。

所选的矩形应使得 $\frac{P^2}{S}$ 的值尽可能小，计算该值时不进行任何四舍五入。

如果有多个答案，输出其中任意一个即可。

每个测试用例包含多个木棍列表，对于每个列表，你都需要分别解决这个问题。

##### 说明/提示
在第一个列表中，只有一种选择四根木棍的方式，它们组成的矩形边长为 $2$ 和 $7$，面积为 $2 \cdot 7 = 14$，周长为 $2(2 + 7) = 18$，$\frac{18^2}{14} \approx 23.143$。

第二个列表中，能组成矩形的四根木棍子集对应的边长分别为 $(1, 2)$、$(2, 8)$ 和 $(1, 8)$，它们对应的 $\frac{P^2}{S}$ 值分别为 $\frac{6^2}{2} = 18$、$\frac{20^2}{16} = 25$ 和 $\frac{18^2}{8} = 40.5$，其中最小的是边长为 $(1, 2)$ 的矩形。

在第三个列表中，你可以从给定的 $5$ 根木棍中任选四根，它们将组成一个边长为 $5$ 的正方形，正方形也是一种特殊的矩形，其边长为 $(5, 5)$。

##### 样例 #1
###### 输入
```
3
4
7 2 2 7
8
2 8 1 4 8 2 1 5
5
5 5 5 5 5
```
###### 输出
```
2 7 7 2
2 2 1 1
5 5 5 5
```

### 综合分析与结论
本题要求从给定的 $n$ 根木棍中选择 $4$ 根组成矩形，使得矩形的 $\frac{P^2}{S}$ 值最小，其中 $P$ 为矩形周长，$S$ 为矩形面积。各题解的核心思路都是先通过数学推导得出使 $\frac{P^2}{S}$ 最小的条件，再根据该条件在给定木棍中筛选出合适的四根。

### 题解分析
| 作者 | 思路 | 算法要点 | 解决难点 | 评分 |
| --- | --- | --- | --- | --- |
| Siyuan | 设矩形边长为 $a,a,b,b\ (a\leqslant b)$，推导出 $\frac{P^2}{S}=4(\frac{a}{b}+\frac{b}{a})+8$，只需最小化 $\frac{b}{a}$。分类讨论：若有 4 条相等线段则选这 4 条；否则将数量不小于 2 的线段排序，贪心选相邻线段。 | 数学推导、分类讨论、贪心 | 精度问题，将 $\frac{b'}{a'}<\frac{b}{a}$ 转化为 $ab'<a'b$ | 4 星 |
| HansLimon | 用 set 查重记录，将出现两次的木棍加入候选数组，排序后遍历数组，找到使 $\frac{b}{a}$ 最小的相邻两根木棍。 | set 查重、排序、遍历 | 数组无序问题，通过排序解决 | 3 星 |
| YellowBean_Elsa | 令矩形边长为 $a,b$，推导出 $\frac{P^2}{S}=4(\frac{a}{b}+\frac{b}{a}+2)$，根据对钩函数性质，$x=\frac{a}{b}$ 越接近 1 越佳。对成对边长排序，选相邻边长。 | 数学推导、对钩函数性质、排序 | 精度问题，比较解优劣时转化为乘法 | 4 星 |
| 轻绘 | 设长为 $a$，宽为 $b$，推导出 $\frac{P^2}{S}=\frac{4a}{b}+\frac{4b}{a}+4$，根据基本不等式，$a=b$ 时 $\frac{P^2}{S}$ 最小。用桶排序，对相邻边长求比值取最小。 | 数学推导、基本不等式、桶排序 | 边的条数判断、数组清零、精度问题 | 3 星 |
| Apocalypsis | 根据对勾函数性质，$\frac{a}{b}$ 越接近 1，$\frac{P^2}{S}$ 越小。若有某数值出现次数大于等于 4，直接输出。对成对边长排序，遍历找最小比值。 | 对勾函数性质、排序、遍历 | 精度问题 | 3 星 |
| LXH5514 | 设长方形长和宽为 $a,b(a>b)$，推导出 $\frac{S}{P^2}=\frac{1}{4}*(\frac{a}{b}+\frac{b}{a}+1/2)$，找最大的 $\frac{b}{a}$。先排序去重统计个数，再暴力枚举。 | 数学推导、排序、去重、枚举 | 数据范围处理 | 3 星 |
| PanH | 展开式子去掉常数项，转化为求最小的 $\frac{(a-b)^2}{ab}$。枚举合法的 $a$，找最大的小于 $a$ 的合法 $b$。 | 数学推导、枚举 | 时间复杂度优化 | 3 星 |
| Mickey_snow | 证明引理：同等宽的矩形，长越小，$\frac{P^2}{S}$ 越小。将木棍配对排序，扫一遍找最小 $\frac{P^2}{S}$。 | 引理证明、配对、排序、遍历 | 引理证明 | 3 星 |

### 高评分题解
- **Siyuan（4 星）**
    - **亮点**：思路清晰，对数学公式的推导和分类讨论详细，通过转化比较条件避免了精度问题。
    - **核心代码**：
```cpp
for(std::map<int,int>::iterator it=cnt.begin();it!=cnt.end();++it) {
    if((*it).second>=2) a[++m]=(*it).first;
    if((*it).second>=4) {
        flg=1;
        int ans=(*it).first;
        printf("%d %d %d %d\n",ans,ans,ans,ans);
        break;
    }
}
if(flg) continue;
int x=a[1],y=a[2];
FOR(i,3,m) if(x*a[i]<a[i-1]*y) x=a[i-1],y=a[i];
printf("%d %d %d %d\n",x,x,y,y);
```
- **YellowBean_Elsa（4 星）**
    - **亮点**：利用对钩函数性质分析问题，思路巧妙，对精度问题的处理合理，代码结构清晰。
    - **核心代码**：
```cpp
fu(i,1,n){
    if(vis[a[i]])continue;
    vis[a[i]]=1; 
    if(p[a[i]]>=4){
        flg=1;
        printf("%d %d %d %d\n",a[i],a[i],a[i],a[i]);
        break;
    }if(p[a[i]]>=2)b[++cnt]=a[i];
}if(flg)continue;
sort(b+1,b+cnt+1);
ans1=b[1],ans2=b[2];
fu(i,2,cnt-1)
    if(1LL*b[i]*ans2>1LL*b[i+1]*ans1)ans1=b[i],ans2=b[i+1];
printf("%d %d %d %d\n",ans1,ans1,ans2,ans2);
```

### 最优关键思路或技巧
- **数学推导**：通过对 $\frac{P^2}{S}$ 进行数学推导，将问题转化为最小化 $\frac{b}{a}$ 或其他等价形式，从而简化问题。
- **分类讨论**：考虑有 4 条相等线段的特殊情况，直接得出最优解，减少不必要的计算。
- **排序与贪心**：将满足条件的线段排序，贪心选择相邻线段，可快速找到使 $\frac{b}{a}$ 最小的组合。
- **精度处理**：将除法比较转化为乘法比较，避免了浮点数精度问题。

### 可拓展之处
同类型题目可能会改变条件，如增加木棍长度范围、限制选择木棍的规则等，但核心思路仍是通过数学推导找到最优解的条件，再结合排序、贪心等算法进行求解。类似算法套路还可应用于其他几何优化问题，如求最大面积、最小周长等。

### 推荐洛谷题目
- P1007 独木桥
- P1047 校门外的树
- P1223 排队接水

### 个人心得摘录与总结
部分题解提到了注意精度问题，如将除法比较转化为乘法比较，避免了浮点数运算带来的误差。还有题解强调了对特殊情况（如正方形）的处理，可优化算法，减少时间复杂度。这些心得提醒我们在解题时要注意细节，充分考虑各种情况，以提高算法的正确性和效率。

---
处理用时：57.52秒