# 题目信息

# Guess The String

## 题目描述

This is an interactive problem. Remember to flush your output while communicating with the testing program. You may use fflush(stdout) in C++, system.out.flush() in Java, stdout.flush() in Python or flush(output) in Pascal to flush the output. If you use some other programming language, consult its documentation. You may also refer to the guide on interactive problems: <https://codeforces.com/blog/entry/45307>.

The jury has chosen a string $ s $ consisting of $ n $ characters; each character of $ s $ is a lowercase Latin letter. Your task is to guess this string; initially, you know only its length.

You may ask queries of two types:

- $ 1 $ $ i $ — the query of the first type, where $ i $ is an integer from $ 1 $ to $ n $ . In response to this query, the jury will tell you the character $ s_i $ ;
- $ 2 $ $ l $ $ r $ — the query of the second type, where $ l $ and $ r $ are integers such that $ 1 \le l \le r \le n $ . In response to this query, the jury will tell you the number of different characters among $ s_l, s_{l+1}, \dots, s_r $ .

You are allowed to ask no more than $ 26 $ queries of the first type, and no more than $ 6000 $ queries of the second type. Your task is to restore the string $ s $ .

For each test in this problem, the string $ s $ is fixed beforehand, and will be the same for every submission.

## 说明/提示

Let's analyze the example of interaction.

The string chosen by the jury is guess, so initially the jury sends one integer $ 5 $ .

1. the first query is ? 2 1 5, which means "count the number of different characters among $ s_1, s_2, \dots, s_5 $ ". The answer to it is $ 4 $ .
2. the second query is ? 1 2, which means "tell which character is $ s_2 $ ". The answer to it is u.
3. the third query is ? 2 1 2, which means "count the number of different characters among $ s_1 $ and $ s_2 $ ". The answer to it is $ 2 $ .
4. the fourth query is ? 1 1, which means "tell which character is $ s_1 $ ". The answer to it is g.
5. the fifth query is ? 1 3, which means "tell which character is $ s_3 $ ". The answer to it is e.
6. the sixth query is ? 1 4, which means "tell which character is $ s_4 $ ". The answer to it is s.
7. the seventh query is ? 2 4 5, which means "count the number of different characters among $ s_4 $ and $ s_5 $ ". The answer to it is $ 1 $ , so it's possible to deduce that $ s_4 $ is the same as $ s_5 $ .

In the end, the answer is submitted as ! guess, and it is deduced correctly.

## 样例 #1

### 输入

```
5
4
u
2
g
e
s
1```

### 输出

```
? 2 1 5
? 1 2
? 2 1 2
? 1 1
? 1 3
? 1 4
? 2 4 5
! guess```

# AI分析结果

### 题目翻译
这是一个交互式问题。在与测试程序通信时，请记得刷新输出。你可以在 C++ 中使用 `fflush(stdout)`，在 Java 中使用 `system.out.flush()`，在 Python 中使用 `stdout.flush()`，或者在 Pascal 中使用 `flush(output)` 来刷新输出。如果你使用其他编程语言，请查阅其文档。你也可以参考交互式问题的指南：<https://codeforces.com/blog/entry/45307>。

评委选择了一个由 $n$ 个字符组成的字符串 $s$；$s$ 的每个字符都是小写拉丁字母。你的任务是猜出这个字符串；最初，你只知道它的长度。

你可以提出两种类型的查询：
- $1$ $i$ —— 第一种类型的查询，其中 $i$ 是一个从 $1$ 到 $n$ 的整数。作为对这个查询的响应，评委会告诉你字符 $s_i$。
- $2$ $l$ $r$ —— 第二种类型的查询，其中 $l$ 和 $r$ 是整数，且满足 $1 \le l \le r \le n$。作为对这个查询的响应，评委会告诉你 $s_l, s_{l+1}, \dots, s_r$ 中不同字符的数量。

你最多可以提出 $26$ 次第一种类型的查询，最多可以提出 $6000$ 次第二种类型的查询。你的任务是还原字符串 $s$。

对于这个问题中的每个测试用例，字符串 $s$ 是预先确定的，并且对于每次提交都是相同的。

### 样例说明
让我们分析一下交互的示例。

评委选择的字符串是 `guess`，所以最初评委会发送一个整数 $5$。
1. 第一个查询是 `? 2 1 5`，这意味着“计算 $s_1, s_2, \dots, s_5$ 中不同字符的数量”。答案是 $4$。
2. 第二个查询是 `? 1 2`，这意味着“告诉我 $s_2$ 是什么字符”。答案是 `u`。
3. 第三个查询是 `? 2 1 2`，这意味着“计算 $s_1$ 和 $s_2$ 中不同字符的数量”。答案是 $2$。
4. 第四个查询是 `? 1 1`，这意味着“告诉我 $s_1$ 是什么字符”。答案是 `g`。
5. 第五个查询是 `? 1 3`，这意味着“告诉我 $s_3$ 是什么字符”。答案是 `e`。
6. 第六个查询是 `? 1 4`，这意味着“告诉我 $s_4$ 是什么字符”。答案是 `s`。
7. 第七个查询是 `? 2 4 5`，这意味着“计算 $s_4$ 和 $s_5$ 中不同字符的数量”。答案是 $1$，所以可以推断出 $s_4$ 和 $s_5$ 是相同的。

最后，答案以 `! guess` 的形式提交，并且被正确推断出来。

### 综合分析与结论
#### 思路对比
这些题解的核心思路都是利用操作一的 $26$ 次限制确定不同的字符，再通过操作二结合二分法确定每个位置的字符，以满足 $n\log26$ 的时间复杂度。
#### 算法要点
- **预处理**：通过操作二确定不同字符首次出现的位置，用操作一获取这些位置的字符。
- **二分查找**：维护每个字符最后出现的位置，对这些位置进行二分，利用操作二的结果缩小范围，确定当前位置的字符。
#### 解决难点
- **减少查询次数**：通过只关注每个字符最后出现的位置，将操作二的次数控制在 $n\log26$ 以内。
- **二分正确性**：维护位置的单调性，保证二分查找的正确性。

### 所选题解
- **作者：TH讠NK（5星）**
    - **关键亮点**：思路清晰，代码注释详细，对二分过程的处理逻辑明确，通过维护按位置排序的数组进行二分查找。
    - **核心代码**：
```cpp
struct node{
    int x,pos;
    bool operator < (const node a)const{
        return pos<a.pos;
    }
} a[27];
// 预处理部分
for(int i=1;i<=n;i++){
    t=ask2(1,i);
    if(t>mx){
        id[i]=mx=t;
        mp[id[i]]=ask1(i);
    }
}
// 核心处理部分
mx=0;
for(int i=1;i<=n;i++){
    if(!id[i]){
        l=1, r=mx;
        while(l<r){
            mid=l+r+1>>1;
            t=ask2(a[mid].pos,i);
            if(t==mx-mid+1) l=mid;
            else r=mid-1;
        }
        id[i]=a[l].x;
        for(int j=l;j<mx;j++) a[j]=a[j+1];
    }
    else mx++;
    a[mx]=(node) {id[i],i};
}
```
- **作者：lin_er（4星）**
    - **关键亮点**：详细解释了二分的原理，通过维护出现过的字符最后出现的位置进行二分，代码中对细节处理有注释。
    - **核心代码**：
```cpp
struct zz{
    int id,w;
};
vector<zz> v;
void che(int x){
    int l=0,r=v.size()-1;
    while(l<r){
        int mid=(l+r+1)>>1;
        cout<<"? 2 "<<v[mid].w<<' '<<x<<endl;
        cin>>ret;
        if(ret==(int)v.size()-mid) l=mid;
        else r=mid-1;
    }
    s[x]=s[v[l].w];
    v[l].w=x;
    sort(v.begin(),v.end(),cmp);
}
// 预处理部分
for(int i=1;i<=n;i++){
    cout<<"? 2 1 "<<i<<endl;
    cin>>ret;
    if(ret>sum){
        sum++;
        cout<<"? 1 "<<i<<endl;
        cin>>c[sum];
        s[i]=c[sum];
        ww[sum]=i;
    }
}
// 核心处理部分
for(int i=1;i<=n;i++){
    if(i<ww[now]){
        che(i);
    }
    else{
        v.push_back({now,i});
        now++;
    }
}
```
- **作者：Sellaris（4星）**
    - **关键亮点**：代码简洁，通过桶记录字符出现情况，对二分查找的实现较为清晰。
    - **核心代码**：
```cpp
int ask1(int u){
    cout<<"? "<<1<<" "<<u<<endl;
    fflush(stdout);
    cin>>c;
    return (int)(c-'a');
}
int ask2(int l,int r){
    cout<<"? "<<2<<" "<<l<<" "<<r<<endl;
    fflush(stdout);
    cin>>tmp;return tmp;
}
const int N=1050;
int n,tong[26],a[N];
struct node{
    int id,pos;
}st[50];
int top;
int cmp(node x,node y){
    return x.pos<y.pos;
}
// 核心处理部分
a[1]=ask1(1);
tong[a[1]]=1;
for(int i=2;i<=n;i++){
    top=0;
    for(int k=0;k<26;k++){
        if(tong[k])st[++top]={k,tong[k]};
    }
    sort(st+1,st+top+1,cmp);
    int l=1,r=top,jl=-1;
    while(l<=r){
        if(ask2(st[mid].pos,i)!=(top-mid+1)+1)jl=mid,l=mid+1;
        else r=mid-1;
    }
    if(jl==-1){
        a[i]=ask1(i);
        tong[a[i]]=i;
    }
    else{
        a[i]=st[jl].id;
        tong[a[i]]=i;
    }
}
```

### 最优关键思路或技巧
- **维护字符最后出现位置**：只关注每个字符最后出现的位置，减少不必要的查询，将时间复杂度控制在 $n\log26$。
- **二分查找**：对维护的位置数组进行二分，利用操作二的结果缩小范围，确定当前位置的字符。

### 可拓展之处
同类型的交互式问题通常会有不同的操作和限制条件，解题的关键在于根据操作次数的限制设计合适的算法。类似的算法套路包括利用二分查找、贪心算法等，通过有限的操作获取尽可能多的信息。

### 洛谷题目推荐
1. [P2615 [NOIP2015 提高组] 神奇的幻方](https://www.luogu.com.cn/problem/P2615)：考察对规则的理解和模拟能力，与本题处理交互规则有一定相似性。
2. [P1008 [NOIP1998 普及组] 三连击](https://www.luogu.com.cn/problem/P1008)：需要通过枚举和判断来满足一定条件，与本题通过有限操作确定答案的思路类似。
3. [P1046 [NOIP2005 普及组] 陶陶摘苹果](https://www.luogu.com.cn/problem/P1046)：简单的模拟问题，有助于熟悉基本的输入输出和条件判断，为解决交互式问题打下基础。

### 个人心得摘录与总结
- **作者：PosVII**：提到因为交互题不熟练没有刷新输出导致 TLE 了好几次，提醒我们在做交互题时要注意刷新输出。
- **作者：lin_er**：作为第一次顺利独立做出的交互题，强调了理解交互方式和限制条件的重要性，以及通过维护关键信息（如字符最后出现位置）来解决问题的思路。 

---
处理用时：50.60秒