# 题目信息

# Mishka and the Last Exam

## 题目描述

Mishka is trying really hard to avoid being kicked out of the university. In particular, he was doing absolutely nothing for the whole semester, miraculously passed some exams so that just one is left.

There were $ n $ classes of that subject during the semester and on $ i $ -th class professor mentioned some non-negative integer $ a_i $ to the students. It turned out, the exam was to tell the whole sequence back to the professor.

Sounds easy enough for those who attended every class, doesn't it?

Obviously Mishka didn't attend any classes. However, professor left some clues on the values of $ a $ to help out students like Mishka:

- $ a $ was sorted in non-decreasing order ( $ a_1 \le a_2 \le \dots \le a_n $ );
- $ n $ was even;
- the following sequence $ b $ , consisting of $ \frac n 2 $ elements, was formed and given out to students: $ b_i = a_i + a_{n - i + 1} $ .

Professor also mentioned that any sequence $ a $ , which produces sequence $ b $ with the presented technique, will be acceptable.

Help Mishka to pass that last exam. Restore any sorted sequence $ a $ of non-negative integers, which produces sequence $ b $ with the presented technique. It is guaranteed that there exists at least one correct sequence $ a $ , which produces the given sequence $ b $ .

## 样例 #1

### 输入

```
4
5 6
```

### 输出

```
2 3 3 3
```

## 样例 #2

### 输入

```
6
2 1 2
```

### 输出

```
0 0 1 1 1 2 
```

# AI分析结果

### 题目内容重写

**Mishka 和最后一门考试**

**题目描述**

Mishka 正在努力避免被大学开除。特别是，他整个学期什么都没做，却奇迹般地通过了一些考试，现在只剩下一门考试了。

这门课在学期中有 $n$ 节课，每节课教授都会向学生提到一个非负整数 $a_i$。结果发现，考试的内容就是向教授复述整个序列。

对于那些每节课都参加的学生来说，这听起来很简单，不是吗？

显然，Mishka 没有参加任何一节课。然而，教授留下了一些关于 $a$ 的线索，以帮助像 Mishka 这样的学生：

- $a$ 是非递减排序的（$a_1 \le a_2 \le \dots \le a_n$）；
- $n$ 是偶数；
- 教授给出了一个由 $\frac{n}{2}$ 个元素组成的序列 $b$，其中 $b_i = a_i + a_{n - i + 1}$。

教授还提到，任何通过上述方法生成序列 $b$ 的序列 $a$ 都是可以接受的。

帮助 Mishka 通过这最后一门考试。恢复任何一个非负整数的排序序列 $a$，使其通过上述方法生成序列 $b$。题目保证至少存在一个正确的序列 $a$，可以生成给定的序列 $b$。

**样例 #1**

**输入**

```
4
5 6
```

**输出**

```
2 3 3 3
```

**样例 #2**

**输入**

```
6
2 1 2
```

**输出**

```
0 0 1 1 1 2 
```

### 算法分类
贪心

### 题解分析与结论

这道题的核心是通过给定的序列 $b$ 构造一个非递减的序列 $a$，使得 $b_i = a_i + a_{n - i + 1}$。所有题解都采用了贪心策略，即让 $a_i$ 尽可能小，$a_{n - i + 1}$ 尽可能大，以确保序列 $a$ 的非递减性。

### 所选高星题解

#### 题解作者：Reywmp (赞：3)
**星级：4星**
**关键亮点：**
- 使用栈来存储数列，节省空间。
- 在线算法，避免了额外的数组存储，空间复杂度较低。
- 贪心策略清晰，代码简洁。

**核心代码：**
```cpp
stack <ll> s;
int main()
{
    ll n;
    read(n);
    ll x=0;
    putchar('0');putchar(' ');
    read(x);
    s.push(x);
    ll mina=0;
    for(int i=2;i<=n>>1;i++)
    {
        read(x);
        if(mina+s.top()<x)
        { 
            mina=x-s.top();
        }
        printf("%lld",mina);putchar(' ');
        s.push(x-mina);
    }
    while(s.empty()==0)
    {
        printf("%lld",s.top());putchar(' ');
        s.pop();
    }
    putchar('\n');
    return 0;
}
```
**核心思想：**
- 初始化 $a_1 = 0$，$a_n = b_1$。
- 对于每个 $b_i$，计算 $a_i$ 和 $a_{n - i + 1}$，确保 $a_i$ 尽可能小，$a_{n - i + 1}$ 尽可能大。

#### 题解作者：wuyixiang (赞：1)
**星级：4星**
**关键亮点：**
- 直接使用数组存储，代码简洁易懂。
- 贪心策略明确，通过取最小值来确保序列的非递减性。

**核心代码：**
```cpp
int main()
{
    cin >> n;
    for(int i = 1;i <= n / 2;i ++)cin >> b[i];
    a[n] = b[1];
    for(int i = 2;i <= n / 2;i ++)
    {
        a[n - i + 1] = min(a[n - i + 2],b[i] - a[i - 1]);
        a[i] = b[i] - a[n - i + 1];
    }
    for(int i = 1;i <= n;i ++)cout << a[i] << " ";
}
```
**核心思想：**
- 初始化 $a_1 = 0$，$a_n = b_1$。
- 对于每个 $b_i$，计算 $a_i$ 和 $a_{n - i + 1}$，确保 $a_i$ 尽可能小，$a_{n - i + 1}$ 尽可能大。

#### 题解作者：zsc2003 (赞：1)
**星级：4星**
**关键亮点：**
- 使用贪心策略，确保 $a_i$ 尽可能小，$a_{n - i + 1}$ 尽可能大。
- 代码结构清晰，易于理解。

**核心代码：**
```cpp
int main()
{
    n=read();
    x=n>>1;
    for(int i=1;i<=x;i++)
        b[i]=read();
    a[1]=0,a[n]=b[1];
    for(int i=2;i<=x;i++)
    {	
        a[n-i+1]=min(a[n-i+2],b[i]);
        a[i]=b[i]-a[n+1-i];
        if(a[i]<a[i-1])
        {
            a[i]=a[i-1];
            a[n-i+1]=b[i]-a[i];
        }
    }
    for(int i=1;i<=n;i++)
        printf("%I64d ",a[i]);
    return 0;
}
```
**核心思想：**
- 初始化 $a_1 = 0$，$a_n = b_1$。
- 对于每个 $b_i$，计算 $a_i$ 和 $a_{n - i + 1}$，确保 $a_i$ 尽可能小，$a_{n - i + 1}$ 尽可能大。

### 最优关键思路或技巧
- **贪心策略**：让 $a_i$ 尽可能小，$a_{n - i + 1}$ 尽可能大，以确保序列 $a$ 的非递减性。
- **数据结构**：使用栈或数组来存储和计算序列 $a$ 的元素。

### 可拓展之处
- 类似的问题可以通过贪心策略来解决，特别是在需要构造满足特定条件的序列时。
- 可以扩展到更复杂的序列构造问题，如构造满足多个条件的序列。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

---
处理用时：48.42秒