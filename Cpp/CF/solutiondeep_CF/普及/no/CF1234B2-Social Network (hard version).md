# 题目信息

# Social Network (hard version)

## 题目描述

The only difference between easy and hard versions are constraints on $ n $ and $ k $ .

You are messaging in one of the popular social networks via your smartphone. Your smartphone can show at most $ k $ most recent conversations with your friends. Initially, the screen is empty (i.e. the number of displayed conversations equals $ 0 $ ).

Each conversation is between you and some of your friends. There is at most one conversation with any of your friends. So each conversation is uniquely defined by your friend.

You (suddenly!) have the ability to see the future. You know that during the day you will receive $ n $ messages, the $ i $ -th message will be received from the friend with ID $ id_i $ ( $ 1 \le id_i \le 10^9 $ ).

If you receive a message from $ id_i $ in the conversation which is currently displayed on the smartphone then nothing happens: the conversations of the screen do not change and do not change their order, you read the message and continue waiting for new messages.

Otherwise (i.e. if there is no conversation with $ id_i $ on the screen):

- Firstly, if the number of conversations displayed on the screen is $ k $ , the last conversation (which has the position $ k $ ) is removed from the screen.
- Now the number of conversations on the screen is guaranteed to be less than $ k $ and the conversation with the friend $ id_i $ is not displayed on the screen.
- The conversation with the friend $ id_i $ appears on the first (the topmost) position on the screen and all the other displayed conversations are shifted one position down.

Your task is to find the list of conversations (in the order they are displayed on the screen) after processing all $ n $ messages.

## 说明/提示

In the first example the list of conversations will change in the following way (in order from the first to last message):

- $ [] $ ;
- $ [1] $ ;
- $ [2, 1] $ ;
- $ [3, 2] $ ;
- $ [3, 2] $ ;
- $ [1, 3] $ ;
- $ [1, 3] $ ;
- $ [2, 1] $ .

In the second example the list of conversations will change in the following way:

- $ [] $ ;
- $ [2] $ ;
- $ [3, 2] $ ;
- $ [3, 2] $ ;
- $ [1, 3, 2] $ ;
- and then the list will not change till the end.

## 样例 #1

### 输入

```
7 2
1 2 3 2 1 3 2
```

### 输出

```
2
2 1 
```

## 样例 #2

### 输入

```
10 4
2 3 3 1 1 2 1 2 3 3
```

### 输出

```
3
1 3 2 
```

# AI分析结果

### 题目内容重写（中文）

**社交网络（困难版）**

**题目描述**

简单版和困难版之间的唯一区别在于对 $n$ 和 $k$ 的约束条件。

你正在通过智能手机在一个流行的社交网络中发送消息。你的智能手机最多可以显示 $k$ 个最近的与朋友的对话。最初，屏幕是空的（即显示的对话数为 $0$）。

每个对话都是你与某个朋友之间的对话。与任何朋友的对话最多只有一个。因此，每个对话都由你的朋友唯一确定。

你（突然！）拥有了预知未来的能力。你知道在这一天中你将收到 $n$ 条消息，第 $i$ 条消息将来自 ID 为 $id_i$ 的朋友（$1 \le id_i \le 10^9$）。

如果你收到的消息来自当前在智能手机屏幕上显示的对话中的 $id_i$，那么什么都不会发生：屏幕上的对话不会改变，也不会改变它们的顺序，你读取消息并继续等待新消息。

否则（即如果屏幕上没有与 $id_i$ 的对话）：

- 首先，如果屏幕上显示的对话数为 $k$，则最后一个对话（位于第 $k$ 个位置）将从屏幕上移除。
- 现在，屏幕上的对话数保证小于 $k$，并且屏幕上没有与朋友 $id_i$ 的对话。
- 与朋友 $id_i$ 的对话将出现在屏幕的第一个（最顶部）位置，所有其他显示的对话将向下移动一个位置。

你的任务是在处理完所有 $n$ 条消息后，找到屏幕上显示的对话列表（按它们在屏幕上显示的顺序）。

**说明/提示**

在第一个示例中，对话列表将按以下方式变化（按从第一条到最后一条消息的顺序）：

- $[]$ ;
- $[1]$ ;
- $[2, 1]$ ;
- $[3, 2]$ ;
- $[3, 2]$ ;
- $[1, 3]$ ;
- $[1, 3]$ ;
- $[2, 1]$ .

在第二个示例中，对话列表将按以下方式变化：

- $[]$ ;
- $[2]$ ;
- $[3, 2]$ ;
- $[3, 2]$ ;
- $[1, 3, 2]$ ;
- 然后列表将保持不变，直到结束。

**样例 #1**

### 输入

```
7 2
1 2 3 2 1 3 2
```

### 输出

```
2
2 1 
```

**样例 #2**

### 输入

```
10 4
2 3 3 1 1 2 1 2 3 3
```

### 输出

```
3
1 3 2 
```

### 算法分类
模拟、队列

### 题解分析与结论

本题的核心逻辑是模拟一个消息处理系统，使用队列或双端队列（deque）来维护当前显示的对话列表。难点在于如何高效地处理大量消息（$n$ 和 $k$ 的约束较大），并且需要快速判断某个对话是否已经在屏幕上显示。

大部分题解都采用了 `deque` 和 `map` 或 `set` 的组合来实现这一功能。`deque` 用于维护对话的顺序，`map` 或 `set` 用于快速判断某个对话是否已经在屏幕上。部分题解还提到了离散化处理，以应对 $id_i$ 范围较大的问题。

### 精选题解

#### 题解1：作者：jiangXxin (赞：3)
**星级：4.5**
**关键亮点：**
- 使用 `deque` 和 `map` 的组合，简洁高效。
- 代码清晰，逻辑明确，直接模拟题目要求。

**核心代码：**
```cpp
deque<int> que;
map<int,bool> mp;
int n,k,m;
int main(){
    cin>>n>>k;
    REP(1,n,i){
        int x;
        cin>>x;
        if(mp[x]==true)continue;
        mp[x]=true;
        que.push_front(x);
        if(que.size()>=k+1){
            m=que.back();
            mp[m]=false;
            que.pop_back();
        }
    }
    cout<<que.size()<<endl;
    while(!que.empty()){
        int x=que.front();
        que.pop_front();
        cout<<x<<" ";
    }
    return 0;
}
```

#### 题解2：作者：Meatherm (赞：2)
**星级：4**
**关键亮点：**
- 手动记录 `deque` 的元素个数，优化了 `q.size()` 的复杂度。
- 使用了离散化处理，适合 $id_i$ 范围较大的情况。

**核心代码：**
```cpp
std::deque <int> q;
int main(void){
    cin>>n>>k;
    for(rr int i=1;i<=n;++i){
        if(!use[std::lower_bound(b+1,b+1+n,a[i])-b]){
            q.push_front(a[i]),use[std::lower_bound(b+1,b+1+n,a[i])-b]=true;
            ++asa;            
        }
        if(asa>k){
            use[std::lower_bound(b+1,b+1+n,q.back())-b]=false,q.pop_back();
            --asa;
        }    
    }
    int tmp=asa;
    cout<<tmp<<endl;
    for(rr int i=1;i<=tmp;++i)
        cout<<q.front()<<" ",q.pop_front();
    return 0;
}
```

#### 题解3：作者：FiraCode (赞：0)
**星级：4**
**关键亮点：**
- 使用 `deque` 和 `map` 的组合，代码简洁，逻辑清晰。
- 直接模拟题目要求，易于理解。

**核心代码：**
```cpp
deque <int> q;
map <int , int> ma;
int main(){
    scanf ("%d%d" , &n , &k);
    for (int i = 1; i <= n; ++ i) {
        if (ma[a[i]]) continue;
        if (q.size () == k) ma[q.back()] = false , q.pop_back();
        if (!ma[a[i]])q.push_front (a[i]) , ma[a[i]] = true;
    }
    cout << q.size() << endl;
    for (int i = 0; i < q.size(); ++ i)
        cout << q[i] << ' ';
    return 0;
}
```

### 最优关键思路
使用 `deque` 维护对话顺序，`map` 或 `set` 快速判断对话是否已存在，直接模拟题目要求。对于 $id_i$ 范围较大的情况，可以使用离散化处理。

### 拓展思路
类似的问题可以出现在缓存替换算法（如 LRU 缓存）中，使用类似的数据结构（如 `deque` 和 `map`）可以高效实现。

### 推荐题目
1. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)
2. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
3. [P1540 机器翻译](https://www.luogu.com.cn/problem/P1540)

---
处理用时：45.86秒