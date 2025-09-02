# 题目信息

# Compression and Expansion

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523C/da6104a926a977751ae03a3b556f0cead9b4ecdd.png)William is a huge fan of planning ahead. That is why he starts his morning routine by creating a nested list of upcoming errands.

A valid nested list is any list which can be created from a list with one item "1" by applying some operations. Each operation inserts a new item into the list, on a new line, just after one of existing items $ a_1 \,.\, a_2 \,.\, a_3 \,.\, \,\cdots\, \,.\,a_k $ and can be one of two types:

1. Add an item $ a_1 \,.\, a_2 \,.\, a_3 \,.\, \cdots \,.\, a_k \,.\, 1 $ (starting a list of a deeper level), or
2. Add an item $ a_1 \,.\, a_2 \,.\, a_3 \,.\, \cdots \,.\, (a_k + 1) $ (continuing the current level).

 Operation can only be applied if the list does not contain two identical items afterwards. And also, if we consider every item as a sequence of numbers, then the sequence of items should always remain increasing in lexicographical order. Examples of valid and invalid lists that are shown in the picture can found in the "Notes" section.When William decided to save a Word document with the list of his errands he accidentally hit a completely different keyboard shortcut from the "Ctrl-S" he wanted to hit. It's not known exactly what shortcut he pressed but after triggering it all items in the list were replaced by a single number: the last number originally written in the item number.

William wants you to help him restore a fitting original nested list.

## 说明/提示

In the second example test case one example of a fitting list is:

1

1.1

1.1.1

1.1.2

1.2

1.2.1

2

2.1

2.2

This list can be produced by using the sequence of operations shown below: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523C/53b6f0dc8acf3fde4c975f74ee95364a6e7138d2.png)

1. Original list with a single item $ 1 $ .
2. Insert item $ 2 $ by using the insertion operation of the second type after item $ 1 $ .
3. Insert item $ 1.1 $ by using the insertion operation of the first type after item $ 1 $ .
4. Insert item $ 1.2 $ by using the insertion operation of the second type after item $ 1.1 $ .
5. Insert item $ 1.1.1 $ by using the insertion operation of the first type after item $ 1.1 $ .
6. Insert item $ 1.1.2 $ by using the insertion operation of the second type after item $ 1.1.1 $ .
7. Insert item $ 1.2.1 $ by using the insertion operation of the first type after item $ 1.2 $ .
8. Insert item $ 2.1 $ by using the insertion operation of the first type after item $ 2 $ .
9. Insert item $ 2.2 $ by using the insertion operation of the second type after item $ 2.1 $ .

## 样例 #1

### 输入

```
2
4
1
1
2
3
9
1
1
1
2
2
1
2
1
2```

### 输出

```
1
1.1
1.2
1.3
1
1.1
1.1.1
1.1.2
1.2
1.2.1
2
2.1
2.2```

# AI分析结果

### 题目翻译
#### 题目描述
William 是一个喜欢提前计划的人。因此，他每天早上都会创建一个嵌套的待办事项列表。

一个有效的嵌套列表是可以通过从一个包含一个项目“1”的列表开始，应用一些操作来创建的任何列表。每个操作都会在现有项目 $a_1 \,.\, a_2 \,.\, a_3 \,.\, \,\cdots\, \,.\,a_k$ 之后插入一个新项目，新项目可以有两种类型：

1. 添加一个项目 $a_1 \,.\, a_2 \,.\, a_3 \,.\, \cdots \,.\, a_k \,.\, 1$（开始一个更深层次的列表），或
2. 添加一个项目 $a_1 \,.\, a_2 \,.\, a_3 \,.\, \cdots \,.\, (a_k + 1)$（继续当前层次）。

操作只能在应用后列表中不包含两个相同项目的情况下进行。并且，如果我们将每个项目视为一个数字序列，那么项目的序列应该始终保持字典序递增。图中展示了有效和无效的列表示例，可以在“说明/提示”部分找到。

当 William 决定保存一个包含他待办事项列表的 Word 文档时，他不小心按了一个完全不同的键盘快捷键，而不是他想要的“Ctrl-S”。不知道他按了什么快捷键，但触发后，列表中的所有项目都被替换为单个数字：原始项目编号中最后写入的数字。

William 希望你帮助他恢复一个合适的原始嵌套列表。

#### 说明/提示
在第二个示例测试用例中，一个合适的列表示例如下：

1  
1.1  
1.1.1  
1.1.2  
1.2  
1.2.1  
2  
2.1  
2.2  

这个列表可以通过以下操作序列生成：  
1. 原始列表包含一个项目 $1$。  
2. 在项目 $1$ 之后插入项目 $2$，使用第二种插入操作。  
3. 在项目 $1$ 之后插入项目 $1.1$，使用第一种插入操作。  
4. 在项目 $1.1$ 之后插入项目 $1.2$，使用第二种插入操作。  
5. 在项目 $1.1$ 之后插入项目 $1.1.1$，使用第一种插入操作。  
6. 在项目 $1.1.1$ 之后插入项目 $1.1.2$，使用第二种插入操作。  
7. 在项目 $1.2$ 之后插入项目 $1.2.1$，使用第一种插入操作。  
8. 在项目 $2$ 之后插入项目 $2.1$，使用第一种插入操作。  
9. 在项目 $2.1$ 之后插入项目 $2.2$，使用第二种插入操作。

#### 样例 #1
##### 输入
```
2
4
1
1
2
3
9
1
1
1
2
2
1
2
1
2
```

##### 输出
```
1
1.1
1.2
1.3
1
1.1
1.1.1
1.1.2
1.2
1.2.1
2
2.1
2.2
```

### 算法分类
模拟

### 题解分析与结论
该题的核心是通过模拟操作来恢复嵌套列表。所有题解都采用了模拟的思路，通过栈或数组来维护当前的列表状态，并根据输入的数字进行相应的操作。主要思路如下：

1. **操作类型判断**：如果输入的数字为1，则直接在列表末尾添加1；否则，从列表末尾开始查找第一个等于输入数字减1的元素，并将其加1。
2. **输出格式**：每次操作后，输出当前列表，元素之间用“.”分隔。

### 高星题解推荐
#### 1. 作者：Macesuted (4星)
**关键亮点**：
- 使用栈来模拟操作，代码简洁高效。
- 通过从栈顶开始查找，确保操作的最优性。

**核心代码**：
```cpp
void work(void) {
    cin >> n;
    for (register int i = 1; i <= n; i++) cin >> a[i];
    for (register int i = 1; i <= n; i++) {
        if (a[i] == 1)
            li.push_back(1);
        else {
            while (!li.empty() && li.back() != a[i] - 1) li.pop_back();
            if (!li.empty()) li.pop_back();
            li.push_back(a[i]);
        }
        for (list<int>::iterator j = li.begin(); j != li.end(); j++) {
            if (j != li.begin()) cout << '.';
            cout << *j;
        }
        cout << endl;
    }
    li.clear();
    return;
}
```

#### 2. 作者：xiaoyuchenp (4星)
**关键亮点**：
- 使用数组模拟栈，代码清晰易读。
- 详细解释了从后往前查找的原因，确保操作的合法性。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){
    if(s[i]==1)num[++pos]=1;
    else if(s[i]==num[pos]+1)num[pos]++;
    else{
        for(;num[pos]!=s[i]-1;pos--);
        num[pos]++;
    }
    for(int i=1;i<pos;i++)cout<<num[i]<<'.';
    cout<<num[pos]<<'\n';
}
```

#### 3. 作者：ylch (4星)
**关键亮点**：
- 使用vector来维护列表，代码简洁且易于理解。
- 详细解释了操作的处理逻辑，确保每一步的合法性。

**核心代码**：
```cpp
void solve()
{
    int n,x;
    cin >> n;
    for (int i=1; i<=n; i++)
    {
        cin >> x;
        if (x == 1) v.push_back(1);
        else
        {
            while (v.size() && v.back() != x-1) v.pop_back();
            if (v.empty()) v.push_back(x);
            else v.back() = x;
        }
        for (unsigned i=0; i<v.size(); i++)
        {
            if (i > 0) putchar('.');
            cout << v[i];
        }
        cout << endl;
    }
    v.clear();
}
```

### 最优关键思路
1. **栈的使用**：通过栈来维护当前列表状态，能够高效地进行插入和删除操作。
2. **从后往前查找**：确保在删除最少元素的情况下找到合适的操作位置，保证后续操作的合法性。

### 可拓展之处
该题的模拟思路可以应用于类似的序列操作问题，如括号匹配、表达式求值等。通过栈或数组来维护状态，能够有效地解决这类问题。

### 推荐题目
1. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)
2. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
3. [P1981 表达式求值](https://www.luogu.com.cn/problem/P1981)

---
处理用时：41.99秒