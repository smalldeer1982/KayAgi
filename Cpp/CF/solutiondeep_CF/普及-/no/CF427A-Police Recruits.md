# 题目信息

# Police Recruits

## 题目描述

The police department of your city has just started its journey. Initially, they don’t have any manpower. So, they started hiring new recruits in groups.

Meanwhile, crimes keeps occurring within the city. One member of the police force can investigate only one crime during his/her lifetime.

If there is no police officer free (isn't busy with crime) during the occurrence of a crime, it will go untreated.

Given the chronological order of crime occurrences and recruit hirings, find the number of crimes which will go untreated.

## 说明/提示

Lets consider the second example:

1. Firstly one person is hired.
2. Then crime appears, the last hired person will investigate this crime.
3. One more person is hired.
4. One more crime appears, the last hired person will investigate this crime.
5. Crime appears. There is no free policeman at the time, so this crime will go untreated.
6. One more person is hired.
7. One more person is hired.
8. One more person is hired.

The answer is one, as one crime (on step 5) will go untreated.

## 样例 #1

### 输入

```
3
-1 -1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8
1 -1 1 -1 -1 1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
11
-1 -1 2 -1 -1 -1 -1 -1 -1 -1 -1
```

### 输出

```
8
```

# AI分析结果

### 题目翻译
# 警察招募

## 题目描述
你们城市的警察局刚刚成立。起初，他们没有任何警力。于是，他们开始分组招募新警员。

与此同时，城市里不断有犯罪事件发生。一名警察一生中只能调查一起犯罪案件。

如果在犯罪发生时没有空闲的警察（即所有警察都在处理案件），那么这起犯罪案件将得不到处理。

给定犯罪发生和警员招募的时间顺序，找出将得不到处理的犯罪案件数量。

## 说明/提示
让我们考虑第二个示例：
1. 首先招募了一名警员。
2. 然后发生了一起犯罪案件，最后招募的警员将调查这起案件。
3. 又招募了一名警员。
4. 又发生了一起犯罪案件，最后招募的警员将调查这起案件。
5. 发生了一起犯罪案件。此时没有空闲的警察，所以这起案件将得不到处理。
6. 又招募了一名警员。
7. 又招募了一名警员。
8. 又招募了一名警员。

答案是 1，因为有一起犯罪案件（在第 5 步）将得不到处理。

## 样例 #1
### 输入
```
3
-1 -1 1
```
### 输出
```
2
```

## 样例 #2
### 输入
```
8
1 -1 1 -1 -1 1 1 1
```
### 输出
```
1
```

## 样例 #3
### 输入
```
11
-1 -1 2 -1 -1 -1 -1 -1 -1 -1 -1
```
### 输出
```
8
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟警察招募和犯罪处理的过程。对于输入的数，若为正数则表示招募相应数量的警察，若为 -1 则表示发生一起犯罪案件，需要判断是否有空闲警察来处理。
- **思路对比**：大部分题解都是按照输入顺序依次处理每个事件，根据输入的数值进行不同操作，只是在变量命名和细节处理上略有差异。
- **算法要点**：使用变量记录当前空闲警察的数量和未处理案件的数量，根据输入更新这两个变量。
- **解决难点**：主要难点在于正确判断在犯罪发生时是否有空闲警察，避免出现逻辑错误。

### 题解评分
| 作者 | 评分 | 思路清晰度 | 代码可读性 | 优化程度 |
| --- | --- | --- | --- | --- |
| Yaixy | 4星 | 清晰，分类讨论明确 | 较高，代码结构简单 | 一般 |
| infinities | 4星 | 清晰，结合题目背景解释 | 较高，代码规范 | 一般 |
| TRZ_2007 | 3星 | 较清晰，思路简洁 | 一般，变量命名不够直观 | 一般 |
| dk——又哇红题 | 3星 | 较清晰，思路常规 | 一般，代码有冗余 | 一般 |
| Autism_ever | 3星 | 较清晰，思路简单 | 一般，代码结构普通 | 一般 |
| _Luminous | 3星 | 较清晰，结合银行背景解释 | 一般，代码注释较少 | 一般 |
| FJ·不觉·莫笑 | 3星 | 较清晰，思路明确 | 一般，数组使用无必要 | 一般 |
| 2132B | 3星 | 较清晰，思路完整 | 一般，代码风格普通 | 一般 |
| KazamiHina | 3星 | 较清晰，结合题目背景解释 | 一般，头文件过多 | 一般 |
| Fatelism | 2星 | 思路错误，理解偏差 | 一般，代码有错误 | 差 |
| Cult_style | 3星 | 较清晰，有调试过程 | 一般，代码有修改痕迹 | 一般 |

### 高评分题解
- **Yaixy（4星）**
    - **关键亮点**：思路清晰，分类讨论明确，代码结构简单易懂。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int ans=0,sum=0,x,n;
int main()
{
    cin>>n;
    while(n--)
     {
        cin>>x;
        if(x<0&&sum<1) ans++;
        if(x<0&&sum) sum--;
        if(x>0) sum+=x; 
	 }
    cout<<ans;
    return 0;
}
```
核心实现思想：使用 `sum` 记录当前空闲警察的数量，`ans` 记录未处理案件的数量。根据输入的 `x` 进行不同操作，若 `x` 为 -1 且 `sum` 小于 1 则 `ans` 加 1，若 `x` 为 -1 且 `sum` 大于 0 则 `sum` 减 1，若 `x` 大于 0 则 `sum` 加上 `x`。

- **infinities（4星）**
    - **关键亮点**：结合题目背景解释思路，代码规范。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>

int num,n,get,ans;
signed main(){
    std::cin>>n;
    
    for(int i=1;i<=n;i++){
        std::cin>>get;
        
        if(get>0)ans+=get;
        else if(get==-1){
            if(ans>0)ans--;else num++;
        }
    }
    
    std::cout<<num;
}
```
核心实现思想：使用 `ans` 记录当前空闲警察的数量，`num` 记录未处理案件的数量。根据输入的 `get` 进行不同操作，若 `get` 大于 0 则 `ans` 加上 `get`，若 `get` 为 -1 且 `ans` 大于 0 则 `ans` 减 1，若 `get` 为 -1 且 `ans` 小于等于 0 则 `num` 加 1。

### 最优关键思路或技巧
使用两个变量分别记录当前空闲警察的数量和未处理案件的数量，按照输入顺序依次处理每个事件，根据输入的数值更新这两个变量。

### 拓展思路
同类型题可能会增加更多的条件，如警察有不同的能力等级，不同等级的警察能处理不同类型的案件等。类似算法套路就是按照事件发生的顺序进行模拟，根据不同的条件更新相应的状态变量。

### 推荐洛谷题目
1. P1047 [NOIP2005 普及组] 校门外的树
2. P1098 [NOIP2007 提高组] 字符串的展开
3. P1548 [NOIP1997 普及组] 棋盘问题

### 个人心得摘录与总结
- **Cult_style**：在编写代码时直接按照思路实现会 WA，通过模拟样例发现问题，即当空闲警察数量小于 1 时需要将其置为 0，避免未判的案子被错误计算。总结就是在编写代码后要仔细检查，通过模拟样例来发现潜在的逻辑错误。 

---
处理用时：38.94秒