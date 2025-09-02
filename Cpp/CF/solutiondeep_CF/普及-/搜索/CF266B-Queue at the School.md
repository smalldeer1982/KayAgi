# 题目信息

# Queue at the School

## 题目描述

During the break the schoolchildren, boys and girls, formed a queue of $ n $ people in the canteen. Initially the children stood in the order they entered the canteen. However, after a while the boys started feeling awkward for standing in front of the girls in the queue and they started letting the girls move forward each second.

Let's describe the process more precisely. Let's say that the positions in the queue are sequentially numbered by integers from $ 1 $ to $ n $ , at that the person in the position number $ 1 $ is served first. Then, if at time $ x $ a boy stands on the $ i $ -th position and a girl stands on the $ (i+1) $ -th position, then at time $ x+1 $ the $ i $ -th position will have a girl and the $ (i+1) $ -th position will have a boy. The time is given in seconds.

You've got the initial position of the children, at the initial moment of time. Determine the way the queue is going to look after $ t $ seconds.

## 样例 #1

### 输入

```
5 1
BGGBG
```

### 输出

```
GBGGB
```

## 样例 #2

### 输入

```
5 2
BGGBG
```

### 输出

```
GGBGB
```

## 样例 #3

### 输入

```
4 1
GGGB
```

### 输出

```
GGGB
```

# AI分析结果

### 题目内容重写

**题目描述**

在课间休息时，学校的男孩和女孩们在食堂排成了一队，共有 $n$ 个人。最初，孩子们按照进入食堂的顺序站队。然而，过了一段时间后，男孩们开始感到尴尬，因为他们站在女孩们的前面，于是他们开始让女孩们每秒向前移动。

让我们更精确地描述这个过程。假设队列中的位置从 $1$ 到 $n$ 依次编号，位置 $1$ 的人最先被服务。如果在时间 $x$，男孩站在第 $i$ 个位置，女孩站在第 $i+1$ 个位置，那么在时间 $x+1$，第 $i$ 个位置将变成女孩，第 $i+1$ 个位置将变成男孩。时间以秒为单位给出。

你得到了孩子们在初始时刻的位置。请确定队列在 $t$ 秒后的样子。

**样例 #1**

### 输入

```
5 1
BGGBG
```

### 输出

```
GBGGB
```

**样例 #2**

### 输入

```
5 2
BGGBG
```

### 输出

```
GGBGB
```

**样例 #3**

### 输入

```
4 1
GGGB
```

### 输出

```
GGGB
```

### 题解分析与结论

通过对多条题解的分析，可以发现大多数题解都采用了模拟的思路，即按照题目描述逐秒模拟男孩和女孩的交换过程。以下是各题解的要点和难点对比：

1. **递归与循环的对比**：第一篇题解使用了递归进行搜索，虽然思路清晰，但递归的深度可能会影响性能，尤其是在 $t$ 较大的情况下。其他题解大多采用循环结构，避免了递归的潜在问题。

2. **交换后的位置处理**：大多数题解在交换后都会将索引 $i$ 加一，以避免重复交换。这是解决该问题的关键技巧之一。

3. **标记数组的使用**：部分题解使用了标记数组来记录每轮交换中已经交换过的位置，避免重复交换。这种方法虽然增加了空间复杂度，但确保了每轮交换的正确性。

4. **字符串与字符数组的选择**：部分题解使用字符数组来处理队列，而其他题解则直接使用字符串。字符串操作更为简洁，但字符数组在某些情况下可能更直观。

### 精选题解

#### 题解1：作者：HNYLMS_MuQiuFeng (赞：5)
**星级：4.5**
**关键亮点**：
- 使用字符串直接处理队列，代码简洁。
- 在交换后立即将索引加一，避免重复交换。
- 时间复杂度为 $O(n \times t)$，符合题目要求。

**核心代码**：
```cpp
for(int i=1;i<=n;i++)
{
    for(int j=0;j<len;j++)
    {
        if(s[j]=='B'&&s[j+1]=='G')
        {
            swap(s[j],s[j+1]);j++;
        }
    }
}
```

#### 题解2：作者：Dancing_Wave (赞：2)
**星级：4**
**关键亮点**：
- 使用字符串处理队列，代码简洁。
- 在交换后立即将索引加一，避免重复交换。
- 时间复杂度为 $O(n \times t)$，符合题目要求。

**核心代码**：
```cpp
for(int i=1;i<=t;i++){
    for(int i=0;i<n-1;i++){
        if(s[i]=='B'&&s[i+1]=='G'){
            swap(s[i],s[i+1]);i++;
        }
    }
}
```

#### 题解3：作者：fls233666 (赞：0)
**星级：4**
**关键亮点**：
- 使用动态数组记录男孩的位置，避免重复交换。
- 每轮交换前清空动态数组，确保每轮交换的正确性。
- 时间复杂度为 $O(n \times t)$，符合题目要求。

**核心代码**：
```cpp
for(int ti=1;ti<=t;ti++){
    boy.clear();
    for(int i=0;i<n-1;i++){
        if(queue[i]=='B')
            boy.push_back(i);
    }
    for(int i=0;i<boy.size();i++){
        if(queue[boy[i]+1]=='G'){
            queue[boy[i]]='G';
            queue[boy[i]+1]='B';
        }
    }
}
```

### 最优关键思路或技巧

1. **交换后的索引处理**：在交换后立即将索引加一，避免重复交换，这是解决该问题的关键技巧之一。
2. **标记数组的使用**：使用标记数组记录每轮交换中已经交换过的位置，确保每轮交换的正确性。
3. **字符串与字符数组的选择**：根据具体需求选择合适的数据结构，字符串操作更为简洁，字符数组在某些情况下可能更直观。

### 可拓展之处

该问题可以拓展到更复杂的队列操作，例如多个人同时交换、不同优先级的人交换等。类似的问题可以考察学生对模拟和字符串操作的理解。

### 推荐题目

1. **P1047 校门外的树**：考察模拟和区间处理。
2. **P1056 排座椅**：考察模拟和排序。
3. **P1067 多项式输出**：考察字符串处理和格式化输出。

---
处理用时：36.94秒