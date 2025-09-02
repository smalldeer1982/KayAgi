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

### 题目中文重写
# 学校食堂的排队问题

## 题目描述
课间休息时，小学生们（包括男孩和女孩）在食堂里排成了一列长度为 $n$ 的队伍。最初，孩子们按照进入食堂的顺序排队。然而，过了一会儿，男孩们因为站在女孩前面而感到尴尬，于是他们开始让女孩每秒向前移动一次。

让我们更精确地描述这个过程。假设队伍中的位置从 $1$ 到 $n$ 依次编号，位置 $1$ 的人最先接受服务。如果在第 $x$ 秒时，第 $i$ 个位置站着一个男孩，第 $i + 1$ 个位置站着一个女孩，那么在第 $x + 1$ 秒时，第 $i$ 个位置将变成女孩，第 $i + 1$ 个位置将变成男孩。时间以秒为单位。

已知孩子们在初始时刻的排队情况，请确定经过 $t$ 秒后队伍的排列方式。

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

### 综合分析与结论
这些题解的核心思路都是模拟男孩和女孩位置交换的过程，在每一秒内遍历队列，若相邻位置是“男孩-女孩”组合，则交换二者位置。

|作者|思路|算法要点|解决难点|评分|
| ---- | ---- | ---- | ---- | ---- |
|6954717a|使用递归搜索，每次搜索检查相邻位置是否为“男孩-女孩”组合，若是则交换，达到规定时间后输出|字符数组存储队列，递归函数进行搜索|递归的使用和边界条件判断|3星|
|HNYLMS_MuQiuFeng|使用两层循环，外层控制时间，内层遍历队列，若相邻位置为“男孩-女孩”组合则交换|字符串存储队列，交换后跳过下一个位置|避免重复交换|4星|
|Dancing_Wave|按题意模拟，从队头到队尾遍历，若相邻位置为“男孩-女孩”组合则交换|字符串存储队列，交换后直接到下一位学生|避免一个男生在一个时间点交换多次|4星|
|liuzitong|标记每个位置是否交换过，避免同一轮内重复交换|字符数组存储队列，标记数组记录交换状态|标记数组的清空和使用|3星|
|xxxjz|两层循环模拟时间和队列遍历，若相邻位置为“男孩-女孩”组合则交换|字符串存储队列，交换后位置加1|避免重复交换|4星|
|Kirito_1205|记录每一秒需要交换的位置，统一处理|字符串存储队列，数组记录交换位置|处理交换位置的重叠情况|3星|
|fls233666|先记录男孩位置，再检查每个男孩后面是否为女孩，若是则交换|字符串存储队列，动态数组记录男孩位置|避免重复交换|3星|

### 所选题解
- **HNYLMS_MuQiuFeng（4星）**
    - 关键亮点：思路清晰，使用字符串存储队列，代码简洁易懂，通过交换后跳过下一个位置避免了重复交换。
    - 核心代码：
```cpp
for(int i=1;i<=n;i++)
{
    for(int j=0;j<len;j++)
    {
        if(s[j]=='B'&&s[j+1]=='G')
        {
            swap(s[j],s[j+1]);
            j++;
        }
    }
}
```
- **Dancing_Wave（4星）**
    - 关键亮点：按照题意直接模拟，代码简洁，通过交换后直接到下一位学生避免了一个男生在一个时间点交换多次。
    - 核心代码：
```cpp
for(int i=1;i<=t;i++){
    for(int i=0;i<n-1;i++){
        if(s[i]=='B'&&s[i+1]=='G'){
            swap(s[i],s[i+1]);
            i++;
        }
    }
}
```
- **xxxjz（4星）**
    - 关键亮点：思路直接，代码简洁，通过交换后位置加1避免了重复交换。
    - 核心代码：
```cpp
for(int q=1; q<=t; q++)
    for(int i=0; i<st.size()-1; i++)
        if(st[i]=='B'&&st[i+1]=='G')  {swap(st[i],st[i+1]);i++;}
```

### 最优关键思路或技巧
- 使用字符串存储队列，方便处理和交换元素。
- 交换相邻元素后，跳过下一个位置，避免重复交换。

### 拓展思路
同类型题目可能会改变交换规则或增加其他条件，如交换的条件更复杂、增加不同类型的人等。解题时仍可采用模拟的方法，根据具体规则进行相应的处理。

### 洛谷相似题目推荐
- P1047 [NOIP2005 普及组] 校门外的树
- P1094 [NOIP2007 普及组] 纪念品分组
- P1208 [USACO1.3] 混合牛奶 Mixing Milk

### 个人心得摘录与总结
- **fls233666**：一开始直接模拟交换未考虑重复交换问题，导致样例不通过。总结出要避免重复交换，可先记录男孩位置，再统一处理交换。
- **Kirito_1205**：提醒要考虑变换位置时的重叠情况，可通过记录交换位置统一处理来避免。 

---
处理用时：30.95秒