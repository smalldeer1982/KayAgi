# 题目信息

# Subsegments

## 题目描述

Programmer Sasha has recently begun to study data structures. His coach Stas told him to solve the problem of finding a minimum on the segment of the array in ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF69E/8d33f6dbc21a91477b8c6a86185f0b1fd0e74ad4.png), which Sasha coped with. For Sasha not to think that he had learned all, Stas gave him a new task. For each segment of the fixed length Sasha must find the maximum element of those that occur on the given segment exactly once. Help Sasha solve this problem.

## 样例 #1

### 输入

```
5 3
1
2
2
3
3
```

### 输出

```
1
3
2
```

## 样例 #2

### 输入

```
6 4
3
3
3
4
4
2
```

### 输出

```
4
Nothing
3
```

# AI分析结果

### 题目内容
#### Subsegments
1. **题目描述**：程序员 Sasha 最近开始学习数据结构。他的教练 Stas 让他解决在数组区间上查找最小值的问题，Sasha 成功解决了。为了不让 Sasha 认为自己已经学完了所有内容，Stas 给了他一个新任务。对于每个固定长度的区间，Sasha 必须找到在给定区间上恰好出现一次的元素中的最大值。帮助 Sasha 解决这个问题。
2. **样例 #1**
    - **输入**：
```
5 3
1
2
2
3
3
```
    - **输出**：
```
1
3
2
```
3. **样例 #2**
    - **输入**：
```
6 4
3
3
3
4
4
2
```
    - **输出**：
```
4
Nothing
3
```
### 算法分类
离散化、模拟
### 题解综合分析与结论
这些题解主要分为两种思路，一种是使用权值线段树，另一种是使用 `set` 和 `map` 模拟滑动窗口。
- **权值线段树思路**：将每个叶子节点看作一个权值，存储数的出现次数等信息。由于数据值域较大（$-10^9\le a_i \le 10^9$），需要进行离散化处理。在叶子节点根据出现次数判断该数是否可成为答案，非叶子节点答案为两儿子节点最大值。通过类似滑动窗口方式，每次移动窗口时更新线段树，获取答案。
- **`set` 和 `map` 模拟滑动窗口思路**：用 `map` 记录每个数出现的次数，用 `set` 保存出现次数为1的数，通过滑动窗口每次更新 `map` 和 `set`，从而获取答案。

权值线段树方法代码相对复杂，但对于处理类似区间统计问题更具一般性和扩展性；`set` 和 `map` 模拟方法代码简洁直观，对于本题特定需求实现简单直接。

### 所选的题解
- **作者：BFSDFS123 (赞：3)  星级：4星**
    - **关键亮点**：详细解释权值线段树概念及本题具体应用，代码结构清晰，离散化处理使用 `unique` 和 `lower_bound` 标准库函数。
    - **重点代码 - 核心实现思想**：通过 `update` 函数更新权值线段树节点信息，在叶子节点根据数的出现次数更新答案，非叶子节点合并答案。滑动窗口移动时，先插入新值，获取答案后删除窗口外的值。
```cpp
void update(int node,int l,int r,int pos,int val)
{
    if(l==r)
    {
        t[node].sum+=val;
        if(t[node].sum==1)
        {
            t[node].ans=l;
        }else{
            t[node].ans=0;
        }
        return ;
    }
    int mid=(l+r)>>1;
    if(pos<=mid)
    {
        update(ls,l,mid,pos,val);
    }else{
        update(rs,mid+1,r,pos,val);
    }
    pushup(node); // 合并叶子节点答案
}
// 滑动窗口更新
for(int i=1;i<k;i++)
{
    update(1,1,newn,Ar[i],1); // 将前 k - 1 个值插入权值线段树
}
for(int i=k;i<=n;i++)
{
    update(1,1,newn,Ar[i],1); // 插入新一个值
    int ans=t[1].ans;
    if(ans==0)
    {
        puts("Nothing");
    }else{
        printf("%d\n",tmp[ans]);
    }
    update(1,1,newn,Ar[i-k+1],-1); // 删除现在序列的第一个值
}
```
- **作者：vandijk (赞：3)  星级：4星**
    - **关键亮点**：思路简单清晰，直接利用 `set` 和 `map` 模拟滑动窗口，代码简洁明了，通过插入负数到 `set` 巧妙获取最大值。
    - **重点代码 - 核心实现思想**：先初始化前 `k` 个数的 `map` 和 `set`，之后滑动窗口每次更新 `map` 中数的出现次数，并相应更新 `set`，最后根据 `set` 是否为空输出答案。
```cpp
for(int i=0;i<k;i++){
    mp[a[i]]++;
}
for(int i=0;i<k;i++){
    if(mp[a[i]]==1)st.insert(-a[i]);
}
if(st.empty()){
    cout<<"Nothing\n";
}
else cout<<-(*st.begin())<<"\n";
for(int i=k;i<n;i++){
    if(mp[a[i-k]]==1)st.erase(-a[i-k]);
    if(mp[a[i]]==1)st.erase(-a[i]);
    mp[a[i-k]]--;
    mp[a[i]]++;
    if(mp[a[i-k]]==1)st.insert(-a[i-k]);
    if(mp[a[i]]==1)st.insert(-a[i]);
    if(!st.empty())cout<<-(*st.begin())<<"\n";
    else cout<<"Nothing\n";
}
```
### 最优关键思路或技巧
- **离散化**：由于数据值域大但数据量相对小，通过离散化将大值域映射到小范围内，便于权值线段树存储和处理。
- **滑动窗口思想**：无论是权值线段树还是 `set` 和 `map` 的方法，都利用滑动窗口每次只更新少量数据的特点，避免重复计算，降低时间复杂度。
### 可拓展之处
同类型题常涉及在固定长度区间内进行特定条件的统计或最值查找。类似算法套路包括合理选择数据结构辅助统计，如本题权值线段树、`map` 和 `set`；利用滑动窗口减少重复计算。
### 推荐题目
- **P1440 [蓝桥杯2018初赛] 巧克力**：通过滑动窗口解决在区间内满足特定条件的统计问题。
- **P1886 滑动窗口**：同样利用滑动窗口求区间最值，可加深对滑动窗口应用理解。
- **P3806 【模板】点权线段树 1**：使用权值线段树解决相关问题，有助于进一步掌握权值线段树应用。 

---
处理用时：51.57秒