# 题目信息

# Inventory

## 题目描述

Companies always have a lot of equipment, furniture and other things. All of them should be tracked. To do this, there is an inventory number assigned with each item. It is much easier to create a database by using those numbers and keep the track of everything.

During an audit, you were surprised to find out that the items are not numbered sequentially, and some items even share the same inventory number! There is an urgent need to fix it. You have chosen to make the numbers of the items sequential, starting with $ 1 $ . Changing a number is quite a time-consuming process, and you would like to make maximum use of the current numbering.

You have been given information on current inventory numbers for $ n $ items in the company. Renumber items so that their inventory numbers form a permutation of numbers from $ 1 $ to $ n $ by changing the number of as few items as possible. Let us remind you that a set of $ n $ numbers forms a permutation if all the numbers are in the range from $ 1 $ to $ n $ , and no two numbers are equal.

## 说明/提示

In the first test the numeration is already a permutation, so there is no need to change anything.

In the second test there are two pairs of equal numbers, in each pair you need to replace one number.

In the third test you need to replace $ 2 $ by $ 1 $ , as the numbering should start from one.

## 样例 #1

### 输入

```
3
1 3 2
```

### 输出

```
1 3 2 
```

## 样例 #2

### 输入

```
4
2 2 3 3
```

### 输出

```
2 1 3 4 
```

## 样例 #3

### 输入

```
1
2
```

### 输出

```
1 
```

# AI分析结果

### 题目内容（中文重写）
# 库存管理

## 题目描述
公司通常有大量的设备、家具和其他物品。所有这些物品都需要进行跟踪管理。为了实现这一点，会为每件物品分配一个库存编号。通过使用这些编号创建数据库来跟踪所有物品会容易得多。

在一次审计中，你惊讶地发现物品的编号并不是连续的，甚至有些物品使用了相同的库存编号！现在急需解决这个问题。你决定将物品的编号改为从 1 开始的连续编号。更改编号是一个相当耗时的过程，因此你希望最大程度地利用现有的编号。

已知公司中 n 件物品的当前库存编号信息。请重新编号这些物品，使它们的库存编号构成一个从 1 到 n 的排列，同时尽可能少地更改物品的编号。需要注意的是，如果一组 n 个数字都在 1 到 n 的范围内，并且没有两个数字相等，那么这组数字就构成一个排列。

## 说明/提示
在第一个测试用例中，编号已经构成一个排列，因此无需进行任何更改。

在第二个测试用例中，有两对相同的数字，在每对中都需要替换一个数字。

在第三个测试用例中，需要将 2 替换为 1，因为编号应该从 1 开始。

## 样例 #1
### 输入
```
3
1 3 2
```
### 输出
```
1 3 2 
```

## 样例 #2
### 输入
```
4
2 2 3 3
```
### 输出
```
2 1 3 4 
```

## 样例 #3
### 输入
```
1
2
```
### 输出
```
1 
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心策略，即尽可能保留原数组中已经符合要求（在 1 到 n 范围内且不重复）的数字，将重复出现或超出范围的数字修改为排列中未出现的数字。
- **思路对比**：大部分题解都是先统计每个数字的出现次数，找出重复和未出现的数字，再进行替换。部分题解使用队列存储未出现的数字，方便按顺序替换；还有题解使用 set 来优化查找未出现数字的过程。
- **算法要点**：使用桶数组（如哈希数组）统计数字出现次数，标记重复和未出现的数字；利用队列、数组或 set 存储未出现的数字，方便后续替换。
- **解决难点**：关键在于如何高效地找出重复和未出现的数字，并合理地进行替换，以保证修改次数最少。

### 高评分题解
- **zajasi（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，使用哈希数组标记数字出现次数，通过向量存储重复和未出现的数字，实现了高效的替换操作。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int a[100010],h[100010];//h 记录哈希
vector<int> d,v;
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        h[a[i]]++;//统计出现的次数
        if(h[a[i]]>1||a[i]>n)d.push_back(i);//d 记录在原数组中重复出现或出界了的数的位置
    }
    for(int i=1;i<=n;i++){
        if(h[i]==0)v.push_back(i);//v 记录在排列中没有出现过的数
    }
    for(int i=0;i<d.size();i++){
        a[d[i]]=v[i];//将重复的数换成没有出现的数
    }
    for(int i=1;i<=n;i++){
        cout<<a[i]<<" ";//直接输出结束
    }
    return 0;
}
```
- **Ninelife_Cat（4星）**
    - **关键亮点**：使用队列存储未出现的数字，代码简洁，实现了贪心策略。
    - **核心代码**：
```cpp
const int N=1e5+10;
int n,a[N],cnt[N];
queue<int> q;//用队列存放排列中未出现过的数
signed main()
{
    n=read();
    for(ri int i=1;i<=n;++i)
        ++cnt[a[i]=read()];//cnt记录每个数字的出现次数
    for(ri int i=1;i<=n;++i)
        if(!cnt[i]) q.push(i);
    for(ri int i=1;i<=n;++i)
        if(cnt[a[i]]==1&&a[i]<=n) cout<<a[i]<<" ";//如果符合条件,直接输出
        else --cnt[a[i]],cout<<q.front()<<" ",q.pop();//修改
    return 0;
}
```
- **Zq_water（4星）**
    - **关键亮点**：思路清晰，使用桶数组标记数字出现情况，通过数组存储未出现的数字，实现了高效的替换。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a[100005],ans[100005],len;
bool t[100005];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i],t[a[i]]=true;
    
    for(int i=1;i<=n;i++)
        if(!t[i]) ans[++len]=i;
 
    memset(t,false,sizeof t);
    len=0;
    for(int i=1;i<=n;i++){
        if(t[a[i]]||a[i]>n) cout<<ans[++len]<<" ";
        else cout<<a[i]<<" ";
        t[a[i]]=true;
    }
    return 0;
}
```

### 最优关键思路或技巧
- 使用桶数组（哈希数组）统计数字出现次数，方便标记重复和未出现的数字。
- 利用队列、数组或 set 存储未出现的数字，按顺序进行替换，保证修改次数最少。

### 拓展思路
同类型题目通常会涉及数组元素的调整和优化，以满足特定的条件。可以采用类似的贪心策略，优先保留符合条件的元素，对不符合条件的元素进行修改。

### 推荐洛谷题目
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录与总结
部分题解提到了在使用队列、set 等数据结构时的注意事项，如访问 set 中的元素需要加星号，否则会访问到地址导致程序错误。在处理数据时，要注意边界条件的判断，避免出现错误。同时，使用快读函数可以优化程序的运行效率。

---
处理用时：42.14秒