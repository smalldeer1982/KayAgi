# 题目信息

# Yet Another Array Queries Problem

## 题目描述

You are given an array $ a $ of size $ n $ , and $ q $ queries to it. There are queries of two types:

- $ 1 $ $ l_{i} $ $ r_{i} $ — perform a cyclic shift of the segment $ [l_{i},r_{i}] $ to the right. That is, for every $ x $ such that $ l_{i}<=x<r_{i} $ new value of $ a_{x+1} $ becomes equal to old value of $ a_{x} $ , and new value of $ a_{li} $ becomes equal to old value of $ a_{ri} $ ;
- $ 2 $ $ l_{i} $ $ r_{i} $ — reverse the segment $ [l_{i},r_{i}] $ .

There are $ m $ important indices in the array $ b_{1} $ , $ b_{2} $ , ..., $ b_{m} $ . For each $ i $ such that $ 1<=i<=m $ you have to output the number that will have index $ b_{i} $ in the array after all queries are performed.

## 样例 #1

### 输入

```
6 3 5
1 2 3 4 5 6
2 1 3
2 3 6
1 1 6
2 2 1 5 3
```

### 输出

```
3 3 1 5 2 
```

# AI分析结果

### 题目内容
# 又一个数组查询问题

## 题目描述
给定一个大小为 $n$ 的数组 $a$ ，以及对它的 $q$ 次查询。查询有两种类型：
- $1$ $l_{i}$ $r_{i}$ — 对区间 $[l_{i},r_{i}]$ 执行一次向右循环移位。即，对于每个满足 $l_{i}<=x<r_{i}$ 的 $x$ ，$a_{x + 1}$ 的新值变为 $a_{x}$ 的旧值，并且 $a_{l_{i}}$ 的新值变为 $a_{r_{i}}$ 的旧值；
- $2$ $l_{i}$ $r_{i}$ — 反转区间 $[l_{i},r_{i}]$ 。

数组中有 $m$ 个重要索引 $b_{1}$ ，$b_{2}$ ，...，$b_{m}$ 。对于每个满足 $1<=i<=m$ 的 $i$ ，你必须输出在执行完所有查询后，数组中索引为 $b_{i}$ 的数字。

## 样例 #1
### 输入
```
6 3 5
1 2 3 4 5 6
2 1 3
2 3 6
1 1 6
2 2 1 5 3
```
### 输出
```
3 3 1 5 2 
```

### 算法分类
模拟

### 综合分析与结论
本题主要考查对数组操作的模拟。多数题解采用倒推思路，利用操作可逆性，对每次询问从后往前模拟操作，根据操作类型分类讨论位置变化，时间复杂度 $O(mq)$ 可通过本题。少数题解使用fhq文艺平衡树，虽代码复杂，但适合解决复杂区间操作问题。

### 所选的题解
- **作者：yuzhechuan（5星）**
    - **关键亮点**：使用fhq文艺平衡树，能高效处理复杂区间操作，代码基于平衡树模板，结构清晰。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
void doit(){
    int op,l,r;
    read(op);read(l);read(r);
    if(op==1){
        int a,b,c,d;
        split(rt,l - 1,a,b); //拆成四段
        split(b,r - l,b,c);
        split(c,1,c,d);
        rt = merge(a,merge(c,merge(b,d)));
    }
    else{
        int x,y,z;
        split(rt,l - 1,x,y);
        split(y,r - l + 1,y,z);
        tag[y]^=1; //中间打上翻转标记
        rt = merge(x,merge(y,z));
    }
}
```
核心思想：操作1将序列拆成四段再重新合并实现循环移位；操作2拆分区间后在中间段打翻转标记，利用平衡树特性实现区间操作。

- **作者：yuheng_wang080904（4星）**
    - **关键亮点**：思路清晰，采用倒推法，详细阐述每种操作下位置倒推的逻辑，代码简洁明了。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
while(m--){
    int x;
    cin>>x;
    for(int i = q;i >= 1;i--){
        if(x < c[i][2]||x > c[i][3])continue;
        if(c[i][1]==1){
            if(x==c[i][2])x = c[i][3];
            else x--;
        }
        else x = c[i][2]+c[i][3]-x;
    }
    cout<<a[x]<<" ";
}
```
核心思想：对每次询问，从后往前遍历操作，根据操作类型和位置关系更新位置，最后输出原数组对应位置的值。

- **作者：kevin1616（4星）**
    - **关键亮点**：先分析暴力解法会超时，引出倒推思路，对倒推过程中操作的逆过程分类讨论详细。
    - **个人心得**：无
    - **核心代码片段**：
```cpp
for(int i = 1;i <= m;i++){
    int x;
    cin>>x;
    for(int j = q;j >= 1;j--){ //逆推
        if(t[j] == 1 && x <= r[j] && x >= l[j] + 1) x--; //如果是操作1而且l<x<=r,那么x'=x-1
        else if(t[j] == 1 && x == l[j]) x = r[j]; //如果是操作1而且x=l,那么x'=r
        else if(t[j] == 2 && x <= r[j] && x >= l[j]) x = l[j] + r[j] - x; //如果是操作2而且l<=x<=r,那么x'=l+r-x
    }
    cout<<a[x]<<" "; //输出当前位对应的初始位的值即操作后当前位的值
}
```
核心思想：与上一个题解类似，对每个询问倒推操作，按操作类型和位置判断更新位置，输出最终位置对应原数组的值。

### 最优关键思路或技巧
倒推思路是解决本题的高效方法，利用操作可逆性，避免正向模拟的高复杂度。对于区间操作问题，若数据范围允许，倒推可简化问题。此外，平衡树能高效处理复杂区间操作，但代码实现复杂，需掌握平衡树模板。

### 可拓展之处
此类题目属于数组区间操作模拟类型，类似算法套路有正向模拟结合优化（如标记优化）、使用更高级数据结构（线段树等）处理区间问题。可拓展到更多不同类型区间操作的题目，如区间加、区间求和等操作混合的问题。

### 洛谷相似题目推荐
- [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996)：通过模拟解决约瑟夫环问题，与本题倒推思路类似，都需按特定规则模拟元素位置变化。
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)：涉及对二维数组区域的模拟操作，与本题对一维数组区间操作类似，需按给定规则处理数组元素。
- [P2671 求和](https://www.luogu.com.cn/problem/P2671)：结合区间操作和前缀和思想，与本题处理区间操作有相似之处，可加深对区间操作的理解。 

---
处理用时：50.86秒