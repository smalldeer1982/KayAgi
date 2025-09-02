# 题目信息

# Friends and Gifts

## 题目描述

There are $ n $ friends who want to give gifts for the New Year to each other. Each friend should give exactly one gift and receive exactly one gift. The friend cannot give the gift to himself.

For each friend the value $ f_i $ is known: it is either $ f_i = 0 $ if the $ i $ -th friend doesn't know whom he wants to give the gift to or $ 1 \le f_i \le n $ if the $ i $ -th friend wants to give the gift to the friend $ f_i $ .

You want to fill in the unknown values ( $ f_i = 0 $ ) in such a way that each friend gives exactly one gift and receives exactly one gift and there is no friend who gives the gift to himself. It is guaranteed that the initial information isn't contradictory.

If there are several answers, you can print any.

## 样例 #1

### 输入

```
5
5 0 0 2 4
```

### 输出

```
5 3 1 2 4 
```

## 样例 #2

### 输入

```
7
7 0 0 1 4 0 6
```

### 输出

```
7 3 2 1 4 5 6 
```

## 样例 #3

### 输入

```
7
7 4 0 3 0 5 1
```

### 输出

```
7 4 2 3 6 5 1 
```

## 样例 #4

### 输入

```
5
2 1 0 0 0
```

### 输出

```
2 1 4 5 3 
```

# AI分析结果

### 题目重写
**Friends and Gifts**

**题目描述**

有 $n$ 个朋友想要在新年时互相赠送礼物。每个朋友应该恰好送出一份礼物，并且恰好收到一份礼物。朋友不能给自己送礼物。

对于每个朋友，已知一个值 $f_i$：如果 $f_i = 0$，表示第 $i$ 个朋友不知道他想把礼物送给谁；如果 $1 \le f_i \le n$，表示第 $i$ 个朋友想把礼物送给朋友 $f_i$。

你需要填补未知的值（$f_i = 0$），使得每个朋友恰好送出一份礼物，并且恰好收到一份礼物，且没有朋友给自己送礼物。题目保证初始信息不矛盾。

如果有多个答案，可以输出任意一个。

**样例 #1**

**输入**

```
5
5 0 0 2 4
```

**输出**

```
5 3 1 2 4 
```

**样例 #2**

**输入**

```
7
7 0 0 1 4 0 6
```

**输出**

```
7 3 2 1 4 5 6 
```

**样例 #3**

**输入**

```
7
7 4 0 3 0 5 1
```

**输出**

```
7 4 2 3 6 5 1 
```

**样例 #4**

**输入**

```
5
2 1 0 0 0
```

**输出**

```
2 1 4 5 3 
```

### 算法分类
**构造**

### 题解分析与结论
本题的核心是通过构造一个排列，使得每个元素都不等于其下标，并且填补所有未知的值。题解中主要采用了以下几种思路：

1. **环图构造**：将问题转化为环图的构造，通过填补缺口来形成完整的环。
2. **贪心匹配**：将未送出礼物的人和未收到礼物的人进行匹配，避免自己送给自己。
3. **模拟与交换**：通过模拟过程，交换元素以避免冲突。

### 高星题解推荐

#### 1. 作者：OnlyJerry (赞：8)
**星级：5星**
**关键亮点：**
- 通过环图构造的思路，将问题转化为图论问题，思路清晰。
- 代码实现详细，逻辑严密，能够处理多种情况。
**核心代码：**
```cpp
for(int i=1;i<=n;i++)
{
    if(st[i] || !q[i]) continue;
    st[i]=true;
    int x=i,y=i;
    while(p[x] && !st[p[x]])
    {
        x=p[x];
        st[x]=true;
    }
    while(q[y] && !st[q[y]])
    {
        y=q[y];
        st[y]=true;
    }
    if(p[x]==y) continue;
    if(!flag)
    {
        flag=true;
        for(int j=1;j<=n;j++)
        {
            if(!q[j] && !p[j])
            {
                st[j]=true;
                p[x]=j;
                x=j;
            }
        }
    }
    p[x]=y;
}
```

#### 2. 作者：brimosta (赞：6)
**星级：4星**
**关键亮点：**
- 通过贪心匹配的思路，避免了复杂的图论构造，代码简洁。
- 处理了特殊情况，如最后一个元素需要与第一个元素交换。
**核心代码：**
```cpp
for(int i=1;i<=A[0];i++)
{
    if(A[i]==B[i])
    {
        if(i!=A[0]) swap(B[i],B[i+1]);
        else
        {
            swap(B[1],B[i]);
            a[A[1]]=B[1];
        }
    }
    a[A[i]]=B[i];
}
```

#### 3. 作者：HoshizoraZ (赞：6)
**星级：4星**
**关键亮点：**
- 通过入度和出度的分析，将问题转化为图的匹配问题，思路新颖。
- 代码实现简洁，逻辑清晰。
**核心代码：**
```cpp
for(int i=1;i<=n;i++)
{
    if(in[i] && !out[i]) aa[++s1]=i;
    if(!in[i] && out[i]) bb[++s2]=i;
}
for(int i=1;i<=s1;i++)
{
    out[aa[i]]=1, in[bb[i]]=1, ans[aa[i]]=bb[i];
}
```

### 最优关键思路或技巧
- **环图构造**：将问题转化为环图的构造，通过填补缺口来形成完整的环，适用于需要构造排列且避免冲突的问题。
- **贪心匹配**：通过将未送出礼物的人和未收到礼物的人进行匹配，避免自己送给自己，适用于需要快速匹配且避免冲突的场景。

### 可拓展之处
- 类似的问题可以扩展到图论中的环构造、匹配问题等。
- 可以进一步优化贪心匹配的算法，处理更复杂的情况。

### 推荐题目
1. [P1283 礼物](https://www.luogu.com.cn/problem/P1283)
2. [P1284 礼物](https://www.luogu.com.cn/problem/P1284)
3. [P1285 礼物](https://www.luogu.com.cn/problem/P1285)

### 个人心得摘录
- **OnlyJerry**：通过环图构造的思路，将问题转化为图论问题，思路清晰，代码实现详细，逻辑严密，能够处理多种情况。
- **brimosta**：通过贪心匹配的思路，避免了复杂的图论构造，代码简洁，处理了特殊情况，如最后一个元素需要与第一个元素交换。
- **HoshizoraZ**：通过入度和出度的分析，将问题转化为图的匹配问题，思路新颖，代码实现简洁，逻辑清晰。

---
处理用时：44.95秒