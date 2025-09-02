# 题目信息

# Interactive LowerBound

## 题目描述

This is an interactive problem.

You are given a sorted in increasing order singly linked list. You should find the minimum integer in the list which is greater than or equal to $ x $ .

More formally, there is a singly liked list built on an array of $ n $ elements. Element with index $ i $ contains two integers: $ value_{i} $ is the integer value in this element, and $ next_{i} $ that is the index of the next element of the singly linked list (or -1, if the current element is the last). The list is sorted, i.e. if $ next_{i}≠-1 $ , then $ value_{nexti}&gt;value_{i} $ .

You are given the number of elements in the list $ n $ , the index of the first element $ start $ , and the integer $ x $ .

You can make up to $ 2000 $ queries of the following two types:

- ? i ( $ 1<=i<=n $ ) — ask the values $ value_{i} $ and $ next_{i} $ ,
- ! ans — give the answer for the problem: the minimum integer, greater than or equal to $ x $ , or ! -1, if there are no such integers. Your program should terminate after this query.

Write a program that solves this problem.

## 说明/提示

You can read more about singly linked list by the following link: [https://en.wikipedia.org/wiki/Linked\_list#Singly\_linked\_list](https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list)

The illustration for the first sample case. Start and finish elements are marked dark. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843B/71961769b81bfa3a3f8829eda26d6883c0c5db50.png)

## 样例 #1

### 输入

```
5 3 80
97 -1
58 5
16 2
81 1
79 4
```

### 输出

```
? 1
? 2
? 3
? 4
? 5
! 81```

# AI分析结果

### 题目内容
# 交互式下界

## 题目描述
这是一道交互式问题。

给定一个按升序排序的单链表。你需要找到链表中大于或等于 $x$ 的最小整数。

更正式地说，有一个基于包含 $n$ 个元素的数组构建的单链表。索引为 $i$ 的元素包含两个整数：$value_{i}$ 是该元素中的整数值，$next_{i}$ 是单链表中下一个元素的索引（如果当前元素是最后一个元素，则为 -1）。链表是有序的，即如果 $next_{i}≠ -1$，那么 $value_{next_{i}} > value_{i}$。

你会得到链表中的元素数量 $n$、第一个元素的索引 $start$ 以及整数 $x$。

你最多可以进行 2000 次以下两种类型的查询：
-? i （$1 <= i <= n$）——询问值 $value_{i}$ 和 $next_{i}$。
-! ans ——给出问题的答案：大于或等于 $x$ 的最小整数，如果不存在这样的整数，则为! -1。你的程序在进行此查询后应终止。

编写一个解决此问题的程序。

## 说明/提示
你可以通过以下链接了解更多关于单链表的信息：[https://en.wikipedia.org/wiki/Linked\_list#Singly\_linked\_list](https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list)

第一个样例的图示。起始和结束元素用深色标记。![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF843B/71961769b81bfa3a3f8829eda26d6883c0c5db50.png)

## 样例 #1
### 输入
```
5 3 80
97 -1
58 5
16 2
81 1
79 4
```
### 输出
```
? 1
? 2
? 3
? 4
? 5
! 81```

### 算法分类
搜索

### 综合分析与结论
这几道题解思路相近，均利用链表递增特性，通过随机询问减少询问次数。难点在于如何在有限询问次数内高效找到目标值，各题解通过随机询问并后续局部暴力搜索解决。题解在随机数生成、代码实现细节上有差异。

### 所选的题解
- **作者：rui_er (5星)**
    - **关键亮点**：思路清晰，对询问策略解释详细，考虑到题目隐藏的询问次数限制，还针对随机数函数被卡的情况，手写随机函数。
    - **个人心得**：发现翻译误导，实际只能进行1999次询问；C++ 的 `rand()` 函数被出题人卡掉，尝试多种方式后手写随机函数。
    - **重点代码**：
```cpp
int seed, seed2;
void srand(int x, int y) {seed = x; seed2 = y;}
int frand() {return (seed *= 19260817) += ((seed2 += 114514) ^= 1919810);}
int rand() {int res = frand(); while(res <= 0) res += n; return res;}

int main() {
    srand(998244353, 1000000007);
    scanf("%d%d%d", &n, &front, &x);
    nxt = front;
    rep(i, 1, min(n, 1000)-1) {
        int pos = rand() % n + 1;
        vector<int> res = interact(pos);
        if(res[0] <= x && res[0] > ans) nxt = res[1], ans = res[0];
    }
    if(ans == x) return give(x), 0;
    rep(i, 1, 1000) {
        if(nxt == -1) break;
        vector<int> res = interact(nxt);
        if(res[0] >= x) return give(res[0]), 0;
        ans = res[0]; nxt = res[1];
    }
    give(ans>=x?ans:-1);
    return 0;
}
```
核心实现思想：先随机询问 `min(n, 1000)-1` 次找到 $\le x$ 的最大元素及其下一项地址，若该元素为 $x$ 直接输出；否则从下一项开始再询问最多1000次找 $\ge x$ 的数或判断无此数输出 -1 。

- **作者：BADFIVE (4星)**
    - **关键亮点**：思路简洁明了，直接阐述随机询问找最大小于 $x$ 的数，再向后搜索的策略。
    - **重点代码**：
```cpp
int main(){
    srand(time(0));
    cin>>n>>a>>x;
    ans=a;
    for(int i=1;i<=1000;i++){
        int res=1ll*rand()*rand()%n+1;
        cout<<"? "<<res<<endl;
        cin>>arr[res]>>brr[res];
        if(arr[ans]<arr[res]&&arr[res]<=x){
            ans=res;
        }
    }
    for(int i=ans;i!=-1;i=brr[i]){
        cout<<"? "<<i<<endl;
        cin>>arr[i]>>brr[i];
        if(arr[i]>=x){
            cout<<"! "<<arr[i]<<endl;
            return 0;
        }
    }
    cout<<"! -1"<<endl;
}
```
核心实现思想：先随机询问1000次找到最大小于等于 $x$ 的数的索引，再从此索引开始向后遍历链表找 $\ge x$ 的数，若无则输出 -1 。

- **作者：lytqwq (4星)**
    - **关键亮点**：从概率角度解释随机询问将链表分块，期望确定 $x$ 所在部分再暴力搜索的合理性。
    - **重点代码**：
```cpp
int main(){
    srand(time(NULL));
    cin>>n>>startt>>x;
    dowz=startt;
    for(int i=1;i<=1000;i++){
        int nam=1ll*rand()*rand()%n+1;
        cout<<"? "<<nam<<endl;
        cin>>val[nam]>>nex[nam];
        if(val[dowz]<val[nam]&&val[nam]<=x){
            dowz=nam;
        }
    }
    for(int i=dowz;i!=-1;i=nex[i]){
        cout<<"? "<<i<<endl;
        cin>>val[i]>>nex[i];
        if(val[i]>=x){
            cout<<"! "<<val[i]<<endl;
            return 0;
        }
    }
    cout<<"! -1"<<endl;
}
```
核心实现思想：随机询问1000次找到最大小于等于 $x$ 的数的索引，从该索引开始向后遍历链表找 $\ge x$ 的数，若无则输出 -1 。

### 最优关键思路或技巧
利用链表递增性质，通过随机询问减少询问范围，再局部暴力搜索。随机询问时要考虑随机数函数可能被卡的情况，可手写随机函数。

### 拓展
此类交互式问题常见套路为利用数据已有特性（如单调性），通过部分随机采样缩小搜索范围，再进行精确查找。类似题目通常会在数据规模和询问限制上做文章，考察对算法复杂度和随机策略的理解。

### 洛谷相似题目推荐
- P1118 数字三角形：通过递推求解路径最大和，考察对数据规律的把握和简单搜索思想。
- P1242 新汉诺塔：涉及递归和搜索，对问题进行逐步分解求解。
- P1434 滑雪：结合深度优先搜索和记忆化，与本题类似在有限操作内找最优解。 

---
处理用时：56.82秒