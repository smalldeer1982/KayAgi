# 题目信息

# Forgery

## 题目描述

Student Andrey has been skipping physical education lessons for the whole term, and now he must somehow get a passing grade on this subject. Obviously, it is impossible to do this by legal means, but Andrey doesn't give up. Having obtained an empty certificate from a local hospital, he is going to use his knowledge of local doctor's handwriting to make a counterfeit certificate of illness. However, after writing most of the certificate, Andrey suddenly discovered that doctor's signature is impossible to forge. Or is it?

For simplicity, the signature is represented as an $ n\times m $ grid, where every cell is either filled with ink or empty. Andrey's pen can fill a $ 3\times3 $ square without its central cell if it is completely contained inside the grid, as shown below.

 `<br></br>xxx<br></br>x.x<br></br>xxx<br></br>`Determine whether is it possible to forge the signature on an empty $ n\times m $ grid.

## 说明/提示

In the first sample Andrey can paint the border of the square with the center in $ (2, 2) $ .

In the second sample the signature is impossible to forge.

In the third sample Andrey can paint the borders of the squares with the centers in $ (2, 2) $ and $ (3, 2) $ :

1. we have a clear paper: `<br></br>...<br></br>...<br></br>...<br></br>...<br></br>`
2. use the pen with center at $ (2, 2) $ . `<br></br>###<br></br>#.#<br></br>###<br></br>...<br></br>`
3. use the pen with center at $ (3, 2) $ . `<br></br>###<br></br>###<br></br>###<br></br>###<br></br>`

In the fourth sample Andrey can paint the borders of the squares with the centers in $ (3, 3) $ and $ (3, 5) $ .

## 样例 #1

### 输入

```
3 3
###
#.#
###
```

### 输出

```
YES```

## 样例 #2

### 输入

```
3 3
###
###
###
```

### 输出

```
NO```

## 样例 #3

### 输入

```
4 3
###
###
###
###
```

### 输出

```
YES```

## 样例 #4

### 输入

```
5 7
.......
.#####.
.#.#.#.
.#####.
.......
```

### 输出

```
YES```

# AI分析结果

### 题目中文重写
## 伪造

### 题目描述
学生安德烈整个学期都在逃避体育课，现在他必须想办法在这门科目上取得及格成绩。显然，通过合法手段做到这一点是不可能的，但安德烈并没有放弃。他从当地一家医院拿到了一张空白证明，打算利用自己对当地医生笔迹的了解，伪造一张病假证明。然而，在写完大部分证明后，安德烈突然发现医生的签名无法伪造。真的是这样吗？

为了简单起见，签名用一个 $n\times m$ 的网格表示，其中每个单元格要么被墨水填充，要么为空。安德烈的笔可以填充一个 $3\times3$ 的正方形（不包括其中心单元格），前提是该正方形完全包含在网格内，如下所示。

```
xxx
x.x
xxx
```
确定是否可以在一个空白的 $n\times m$ 网格上伪造该签名。

### 说明/提示
在第一个样例中，安德烈可以以 $(2, 2)$ 为中心绘制正方形的边框。

在第二个样例中，无法伪造该签名。

在第三个样例中，安德烈可以以 $(2, 2)$ 和 $(3, 2)$ 为中心绘制正方形的边框：
1. 我们有一张白纸：
```
...
...
...
...
```
2. 以 $(2, 2)$ 为中心使用笔。
```
###
#.#
###
...
```
3. 以 $(3, 2)$ 为中心使用笔。
```
###
###
###
###
```

在第四个样例中，安德烈可以以 $(3, 3)$ 和 $(3, 5)$ 为中心绘制正方形的边框。

### 样例 #1
#### 输入
```
3 3
###
#.#
###
```
#### 输出
```
YES
```

### 样例 #2
#### 输入
```
3 3
###
###
###
```
#### 输出
```
NO
```

### 样例 #3
#### 输入
```
4 3
###
###
###
###
```
#### 输出
```
YES
```

### 样例 #4
#### 输入
```
5 7
.......
.#####.
.#.#.#.
.#####.
.......
```
#### 输出
```
YES
```

### 综合分析与结论
- **思路对比**：所有题解的核心思路一致，都是先存储目标矩阵，然后遍历矩阵中的每个点，判断以该点为中心的 $3\times3$ 正方形（不包含中心）是否都为 `#` ，若满足条件则在另一个矩阵中进行染色操作，最后比较染色后的矩阵与目标矩阵是否相同。
- **算法要点**：主要是枚举矩阵中的点，通过方向数组判断周围点的状态，以及染色和比对操作。
- **解决难点**：主要难点在于处理边界情况，避免越界访问矩阵元素，以及准确判断是否可以进行染色操作。

### 评分较高的题解
1. **作者：Abyss_Bright（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对每个步骤都有明确的解释，便于理解。
    - **核心代码**：
```cpp
bool bidui()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(mubiao[i][j]!=bian[i][j])
                return false;
        }
    }
    return true;
}
// 省略部分代码
if(bidui())
    cout<<"YES";
else
    cout<<"NO";
```
核心实现思想：通过 `bidui` 函数逐点比较目标矩阵和染色后的矩阵，若有不同则返回 `false` ，否则返回 `true` 。

2. **作者：Forever1507（4星）**
    - **关键亮点**：提供了枚举和深搜两种解法，并对两种解法进行了对比，适合学习不同的解题思路。
    - **核心代码（枚举）**：
```cpp
bool cmp(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(want[i][j]!=now[i][j])return 0;
        }
    }
    return 1;
}
void solve(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            bool flag=0;
            for(int k=0;k<=7;k++){
                int mx=i+dx[k];
                int my=j+dy[k];
                if(mx<=0||mx>n||my<=0||my>m||want[mx][my]=='.'){
                    flag=1;
                    break;
                }
            }
            if(flag)continue;
            for(int k=0;k<=7;k++){
                int mx=i+dx[k];
                int my=j+dy[k];
                now[mx][my]='#';
            }
        }
    }
}
```
核心实现思想：`cmp` 函数用于比较两个矩阵，`solve` 函数遍历矩阵中的点，判断是否可以染色，若可以则进行染色操作。

3. **作者：「已注销」（4星）**
    - **关键亮点**：代码简洁，逻辑清晰，直接枚举所有可能的 $3\times3$ 正方形进行染色和判断。
    - **核心代码**：
```cpp
for(int i=1;i<=n-2;++i)
    for(int j=0;j<m-2;++j){
        bool flag=true;
        for(int k=0;k<8;++k)
            if(a[i+dx[k]][j+dy[k]]!='#'){
                flag=false;
                break;
            }
        if(flag)
            for(int k=0;k<8;++k)
                s[i+dx[k]][j+dy[k]]='#';    
    }
for(int i=1;i<=n;++i)
    for(int j=0;j<m;++j)
        if(a[i][j]!=s[i][j]){
            cout<<"NO";
            return 0;
        }    
cout<<"YES";        
```
核心实现思想：枚举所有可能的 $3\times3$ 正方形，判断是否可以染色，若可以则在另一个矩阵中进行染色，最后比较两个矩阵是否相同。

### 最优关键思路或技巧
- **方向数组**：使用方向数组可以方便地遍历一个点的周围点，减少代码的重复度。
- **枚举法**：通过枚举矩阵中的每个点，判断是否可以进行染色操作，简单直接。

### 可拓展之处
同类型题或类似算法套路：
- 矩阵填充问题：如在矩阵中填充特定形状的图案，判断是否可以达到目标状态。
- 模拟染色问题：在二维平面上进行染色操作，根据染色规则判断最终结果。

### 推荐洛谷题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1540 机器翻译](https://www.luogu.com.cn/problem/P1540)
3. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)

### 个人心得摘录与总结
- **Forever1507**：提到深搜会多开一个 `bool vis[1005][1005]` 数组，空间消耗较大，虽然本题不会 `MLE` ，但养成省空间的习惯很有必要。总结：在选择算法时，要考虑空间复杂度，避免不必要的空间浪费。

---
处理用时：38.72秒