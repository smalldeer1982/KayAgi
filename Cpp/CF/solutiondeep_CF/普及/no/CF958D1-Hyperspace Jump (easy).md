# 题目信息

# Hyperspace Jump (easy)

## 题目描述

The Rebel fleet is on the run. It consists of $ m $ ships currently gathered around a single planet. Just a few seconds ago, the vastly more powerful Empire fleet has appeared in the same solar system, and the Rebels will need to escape into hyperspace. In order to spread the fleet, the captain of each ship has independently come up with the coordinate to which that ship will jump. In the obsolete navigation system used by the Rebels, this coordinate is given as the value of an arithmetic expression of the form ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF958D1/d69a7d7c3c678bb5c53aa5b1c81de4c6ffbba379.png).

To plan the future of the resistance movement, Princess Heidi needs to know, for each ship, how many ships are going to end up at the same coordinate after the jump. You are her only hope!

## 说明/提示

In the sample testcase, the second and the third ship will both end up at the coordinate $ 3 $ .

Note that this problem has only two versions – easy and hard.

## 样例 #1

### 输入

```
4
(99+98)/97
(26+4)/10
(12+33)/15
(5+1)/7
```

### 输出

```
1 2 2 1 ```

# AI分析结果

### 题目内容重写

**题目描述**

反抗军舰队正在逃亡。它由 $m$ 艘飞船组成，目前聚集在一颗行星周围。几秒钟前，更强大的帝国舰队出现在同一个太阳系中，反抗军需要逃入超空间。为了分散舰队，每艘飞船的船长独立地确定了飞船将跳跃到的坐标。在反抗军使用的过时导航系统中，这个坐标由一个算术表达式的值给出，表达式的形式为 $\frac{a+b}{c}$。

为了规划抵抗运动的未来，Heidi公主需要知道每艘飞船跳跃后有多少艘飞船将到达相同的坐标。你是她唯一的希望！

**说明/提示**

在样例中，第二艘和第三艘飞船都将到达坐标 $3$。

注意，这个问题只有两个版本——简单版和困难版。

**样例 #1**

**输入**

```
4
(99+98)/97
(26+4)/10
(12+33)/15
(5+1)/7
```

**输出**

```
1 2 2 1
```

### 算法分类

模拟、数学

### 题解分析与结论

题目要求计算每个表达式的值，并统计有多少个表达式的值相同。由于表达式的形式固定为 $\frac{a+b}{c}$，可以直接计算其值，并使用 `map` 来统计相同值的个数。

**关键思路与技巧：**

1. **表达式解析与计算**：由于表达式的格式固定，可以直接解析字符串中的 $a$、$b$、$c$，并计算 $\frac{a+b}{c}$ 的值。
2. **统计相同值的个数**：使用 `map` 来记录每个值的出现次数，最后输出每个表达式对应的值的出现次数。
3. **精度问题处理**：部分题解提到直接计算浮点数可能带来精度问题，因此建议将表达式化为最简分数形式，使用 `pair<int, int>` 来存储分子和分母，避免精度误差。

**评分较高的题解：**

1. **作者：Chenyichen0420 (4星)**
   - **关键亮点**：将表达式化为最简分数形式，避免了浮点数精度问题，使用 `pair<int, int>` 存储分子和分母，代码简洁且高效。
   - **核心代码：**
     ```cpp
     for(int i=1;i<=n;++i)
         cin>>ccp>>a[i]>>ccp>>b[i]>>ccp>>ccp>>c[i],l=a[i]+b[i],r=c[i],
         cnt[make_pair(l/__gcd(l,r),r/__gcd(l,r))]++;
     for(int i=1;i<=n;++i)
         l=a[i]+b[i],r=c[i],cout<<cnt[make_pair(l/__gcd(l,r),r/__gcd(l,r))]<<" ";
     ```

2. **作者：Harrylzh (4星)**
   - **关键亮点**：同样使用 `pair<int, int>` 存储最简分数形式，代码逻辑清晰，处理了输入中的无关字符，代码可读性高。
   - **核心代码：**
     ```cpp
     for(int i=1;i<=t;i++)
     {
         int a,b,c;
         cin>>ch>>a>>ch>>b>>ch>>ch>>c;
         int gcdabc=gcd(a+b,c);
         mp[make_pair((a+b)/gcdabc,c/gcdabc)]++;
         p[i]=make_pair((a+b)/gcdabc,c/gcdabc);
     }
     for(int i=1;i<=t;i++) cout<<mp[p[i]]<<' ';
     ```

3. **作者：智子 (4星)**
   - **关键亮点**：使用 `gcd` 函数将分数化为最简形式，代码简洁且高效，处理了输入中的无关字符，代码可读性高。
   - **核心代码：**
     ```cpp
     for(int i = 1; i <= m; i++) {
         int a, b, c;
         a = read(); b = read(); c = read();
         int x = a + b, y = c, g = gcd(x, y);
         x = x / g; y = y / g;
         cnt[make_pair(x, y)]++;
         tmp[i] = make_pair(x, y);
     }
     for(int i = 1; i <= m; i++) {
         printf("%d ", cnt[tmp[i]]);
     }
     ```

**最优关键思路或技巧：**

- **分数最简形式**：将表达式化为最简分数形式，避免浮点数精度问题，使用 `pair<int, int>` 存储分子和分母。
- **输入处理**：直接解析字符串中的 $a$、$b$、$c$，跳过无关字符，简化输入处理。

**可拓展之处：**

- 类似题目可以考察表达式的解析与计算，或者统计相同值的个数。
- 可以扩展到更复杂的表达式形式，如包含多个运算符或括号的表达式。

**推荐题目：**

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)

**个人心得：**

- **调试经历**：部分题解提到在处理输入时，直接跳过无关字符可以简化代码逻辑，避免不必要的错误。
- **踩坑教训**：直接计算浮点数可能带来精度问题，因此建议将表达式化为最简分数形式，避免精度误差。

---
处理用时：32.83秒