# 题目信息

# Beppa and SwerChat

## 题目描述

Beppa and her circle of geek friends keep up to date on a group chat in the instant messaging app SwerChat $ ^{\text{TM}} $ .

The group has $ n $ members, excluding Beppa. Each of those members has a unique ID between $ 1 $ and $ n $ . When a user opens a group chat, SwerChat $ ^{\text{TM}} $ displays the list of other members of that group, sorted by decreasing times of last seen online (so the member who opened the chat most recently is the first of the list). However, the times of last seen are not displayed.

Today, Beppa has been busy all day: she has only opened the group chat twice, once at 9:00 and once at 22:00. Both times, she wrote down the list of members in the order they appeared at that time. Now she wonders: what is the minimum number of other members that must have been online at least once between 9:00 and 22:00?

Beppa is sure that no two members are ever online at the same time and no members are online when Beppa opens the group chat at 9:00 and 22:00.

## 说明/提示

In the first test case, members $ 4, 5 $ must have been online between 9:00 and 22:00.

In the second test case, it is possible that nobody has been online between 9:00 and 22:00.

## 样例 #1

### 输入

```
4
5
1 4 2 5 3
4 5 1 2 3
6
1 2 3 4 5 6
1 2 3 4 5 6
8
8 2 4 7 1 6 5 3
5 6 1 4 8 2 7 3
1
1
1```

### 输出

```
2
0
4
0```

# AI分析结果

### 中文题目重写

#### 题目描述

Beppa 和她的极客朋友们在一个即时通讯应用 SwerChat™ 的群聊中保持联系。这个群有 $n$ 个成员，不包括 Beppa。每个成员都有一个唯一的 ID，范围在 $1$ 到 $n$ 之间。当用户打开群聊时，SwerChat™ 会显示其他成员的列表，按照最近在线时间的降序排列（最近打开群聊的成员排在列表的最前面）。然而，最近在线的时间并不显示。

今天，Beppa 整天都很忙：她只打开了群聊两次，一次在 9:00，一次在 22:00。每次打开时，她都记下了当时显示的成员列表顺序。现在她想知道：在 9:00 到 22:00 之间，至少有多少其他成员必须在线过至少一次？

Beppa 确信没有两个成员同时在线，也没有成员在 Beppa 打开群聊的 9:00 和 22:00 时在线。

#### 说明/提示

在第一个测试用例中，成员 $4, 5$ 必须在 9:00 到 22:00 之间在线过。

在第二个测试用例中，可能没有人在 9:00 到 22:00 之间在线过。

#### 样例 #1

##### 输入

```
4
5
1 4 2 5 3
4 5 1 2 3
6
1 2 3 4 5 6
1 2 3 4 5 6
8
8 2 4 7 1 6 5 3
5 6 1 4 8 2 7 3
1
1
1
```

##### 输出

```
2
0
4
0
```

### 算法分类
模拟

### 题解分析与结论

#### 题解对比

1. **ダ月 (赞：4)**
   - **思路**：通过寻找早上和晚上列表的最长公共后缀，确定未登录的成员数量，然后用总人数减去未登录的成员数量得到至少登录的成员数量。
   - **亮点**：通过倒序双指针优化，时间复杂度为 $O(n)$，思路清晰且高效。
   - **评分**：5星

2. **封禁用户 (赞：1)**
   - **思路**：通过双指针从后向前遍历，统计未登录的成员数量，然后用总人数减去未登录的成员数量。
   - **亮点**：使用双指针优化，时间复杂度为 $O(n)$，代码简洁。
   - **评分**：4星

3. **little_stickman (赞：0)**
   - **思路**：通过从后向前遍历，统计未登录的成员数量，然后用总人数减去未登录的成员数量。
   - **亮点**：思路与封禁用户类似，但代码实现稍显冗长。
   - **评分**：3星

#### 最优关键思路

- **倒序双指针**：通过从后向前遍历早上和晚上的列表，寻找最长公共后缀，从而确定未登录的成员数量。这种方法避免了 $O(n^2)$ 的复杂度，优化为 $O(n)$。

#### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
int main(){
    cin>>T;
    while(T--){
        cin>>n;
        vector<int> a(n),b(n);
        for(int i=0;i<n;i++) cin>>a[i];
        for(int i=0;i<n;i++) cin>>b[i];
        int pos=n-1,wh=-1;
        for(int i=n-1;~i;i--){
            while(~pos&&b[i]!=a[pos]) pos--;
            if(pos<0){wh=i;break;}
        }printf("%d\n",wh+1);
    }return 0;
}
```

#### 可拓展之处

- **类似问题**：可以扩展到其他需要比较两个序列并寻找最长公共子序列或后缀的问题，如字符串匹配、序列对齐等。

#### 推荐题目

1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P1144 最长公共子序列](https://www.luogu.com.cn/problem/P1144)
3. [P3376 【模板】最长公共前缀](https://www.luogu.com.cn/problem/P3376)

#### 个人心得

- **调试经历**：在实现双指针时，需要注意指针的边界条件，避免越界或死循环。通过调试，确保指针在遍历过程中正确移动。
- **顿悟感想**：通过倒序遍历和双指针的结合，可以高效地解决序列比较问题，这种思路在其他类似问题中也有广泛应用。

---
处理用时：32.34秒