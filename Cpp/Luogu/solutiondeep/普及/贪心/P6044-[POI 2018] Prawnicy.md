# 题目信息

# [POI 2018] Prawnicy

## 题目背景

**题目译自 [POI XXV - I etap](https://sio2.mimuw.edu.pl/c/oi25-1/dashboard/) 「[Prawnicy](https://sio2.mimuw.edu.pl/c/oi25-1/p/pra/)」**

## 题目描述

“Bajtazar 父子”律师事务所刚刚收到一位非常重要的客户的订单。案件严重、紧急，需要与律师事务所的律师举行会议。每个律师都有一段固定的空闲时间可以参加会议。你应该选择这样的 $k$ 位律师，以便召开会议的时间（即他们都空闲的时间）尽可能长。

[简要题意](https://www.luogu.com.cn/problem/U252799)

## 说明/提示

#### 样例解释

三位律师会议可能的最大时长是 $4$。编号为 $1$、$2$ 和 $4$ 的律师可以参加，持续时间从 $4$ 到 $8$。另一个同样好的方案是让编号为 $2$、$4$ 和 $5$ 的律师参加，持续时间从 $5$ 到 $9$。

![](https://cdn.luogu.com.cn/upload/image_hosting/187yuqy1.png)

#### 附加样例

参见 `pra/pra*.in` 和 `pra/pra*.out`：

- 附加样例 $1$：$1$ 组数据，$n=7$，$k=3$，且选择律师的方案有两种。

- 附加样例 $2$：$1$ 组数据，$n=k=1000$，$a_i=i$，$b_i=10^6+i$；

- 附加样例 $3$：$1$ 组数据，$n=1000$，$k=1$，$a_i=2i-1$，$b_i=2i$；

#### 数据范围与提示

测试集分为以下子任务。每个子任务的测试由一个或多个单独的测试组组成。

| Subtask # | 额外限制                         | 分值  |
|:---------:|:----------------------------:|:---:|
| $1$         | $n\le 20$       | $20$  |
| $2$         | $n\le 300$，$a_i,b_i\le 300$      | $15$  |
| $3$         | $n\le 5000$       | $15$  |
| $4$         | $n\le 10^6$，$k\in \{1,n\}$       | $15$  |
| $5$         | $n\le 10^6$       | $35$  |

如果你的程序在第一行输出了正确的时长，但其余的输出是错误的，那么你将获得 $40\%$ 的分数。

## 样例 #1

### 输入

```
6 3
3 8
4 12
2 6
1 10
5 9
11 12
```

### 输出

```
4
1 2 4
```

# AI分析结果

### 综合分析与结论

本题的核心问题是从给定的n条线段中选出k条，使得它们的交集长度最大。所有题解都采用了贪心算法结合优先队列（小根堆）的思路，通过排序和堆的维护来找到最优解。主要思路是：

1. **排序**：将线段按左端点从小到大排序，确保每次处理的线段左端点比之前的更大。
2. **优先队列**：使用小根堆维护当前选中的k条线段的右端点，确保每次都能快速找到最小的右端点。
3. **更新答案**：在堆中维护k个右端点时，计算当前线段的左端点与堆顶右端点的差值，更新最大交集长度。

### 所选高星题解

#### 1. **题解作者：longlinyu7 (5星)**
- **关键亮点**：思路清晰，代码简洁，详细解释了贪心和优先队列的结合使用，且代码可读性高。
- **个人心得**：通过维护合法右端点减去左端点的最大值，最后输出即可。代码中通过重新遍历找到符合条件的线段，确保了输出的正确性。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1000005;
int n,k,tail,head,tim;
struct node{int x,y,num;}a[N];
priority_queue<int,vector<int >,greater<int > >r;//小根堆
bool cmp(node a,node b){
    return a.x==b.x?(a.y<b.y):(a.x<b.x);
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i].x>>a[i].y;
        a[i].num=i;
    }
    sort(a+1,a+1+n,cmp);
    for(int i=1;i<=n;i++){
        r.push(a[i].y);
        while(r.size() >k){
            r.pop();
        }
        if(r.size()==k){ //如果合法
            if(tim<(r.top()-a[i].x)){//替换
                tail=r.top();head=a[i].x;
                tim=tail-head;
            }
        }
    }
    cout<<tim<<endl;
    for(int i=1;i<=n;i++){//重新遍历
        if(a[i].x<=head&&a[i].y>=tail&&k){
            k--;
            cout<<a[i].num<<" ";
        }
    }
    return 0;
}
```

#### 2. **题解作者：Je_son (4星)**
- **关键亮点**：详细解释了贪心算法的思路，并通过小根堆维护右端点，代码结构清晰。
- **个人心得**：通过小根堆维护当前k条线段的最小右端点，确保每次都能快速找到最优解。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n, k, l, r;
priority_queue <int, vector <int> , greater <int> > q;
struct Node { int l, r, num; }A[N];
bool cmp(Node x, Node y) { return x.l < y.l; }
signed main() {
    cin >> n >> k;
    for(int i = 1; i <= n; i ++ ) {
        cin >> A[i].l >> A[i].r;
        A[i].num = i;
    }
    sort(A + 1, A + n + 1, cmp);
    for(int i = 1; i <= n; i ++ ) {
        q.push(A[i].r);
        while(q.size() > k) q.pop();
        if(q.size() == k && q.top() - A[i].l > r - l) {
            l = A[i].l; r = q.top();
        }
    }
    cout << r - l << endl;
    for(int i = 1; i <= n && k; i ++ ) {
        if(A[i].l <= l && A[i].r >= r) {
            k -- ; cout << A[i].num << ' ';
        }
    }
    return 0;
}
```

#### 3. **题解作者：JackMerryYoung (4星)**
- **关键亮点**：代码简洁，思路清晰，通过优先队列维护右端点，确保每次都能找到最优解。
- **个人心得**：通过大根堆维护右端点，确保每次都能找到最优解。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
struct lawyer { ll a, b, num; } arr[1000005];
ll N, K, ansl, ansr;
priority_queue<ll, vector<ll>, greater<ll>> heap;
bool operator <(lawyer la, lawyer lb) { return (la.a == lb.a) ? (la.b < lb.b) : (la.a < lb.a); }
signed main() {
    cin >> N >> K;
    for(ll i = 1; i <= N; ++ i) { cin >> arr[i].a >> arr[i].b; arr[i].num = i; }
    sort(arr + 1, arr + N + 1);
    for(ll i = 1; i <= N; ++ i) {
        heap.push(arr[i].b);
        while(heap.size() > K) heap.pop();
        if(heap.size() == K && (heap.top() - arr[i].a) > (ansr - ansl)) {
            ansl = arr[i].a; ansr = heap.top();
        }
    }
    cout << ansr - ansl << endl;
    for(ll i = 1; i <= N; ++ i) {
        if(arr[i].a <= ansl && arr[i].b >= ansr && k) {
            k--; cout << arr[i].num << ' ';
        }
    }
    return 0;
}
```

### 最优关键思路与技巧

1. **贪心算法**：通过排序和优先队列的结合，确保每次都能找到最优解。
2. **优先队列（小根堆）**：维护当前选中的k条线段的右端点，确保每次都能快速找到最小的右端点。
3. **重新遍历**：在找到最大交集后，重新遍历所有线段，找到符合条件的线段输出。

### 可拓展之处

类似的问题可以扩展到其他需要选择子集并求最大交集的情境，如选择k个区间使得它们的并集最大，或者选择k个点使得它们覆盖的区间最多。

### 推荐题目

1. **P1230 智力大冲浪**：贪心算法的经典题目，考察如何选择任务以获得最大收益。
2. **P1803 线段覆盖**：考察如何选择不相交的线段使得覆盖的区间最大。
3. **P2887 选择不相交区间**：考察如何选择不相交的区间使得覆盖的区间最大。

### 个人心得总结

- **调试经历**：在维护优先队列时，确保堆的大小不超过k，否则需要弹出堆顶元素。
- **踩坑教训**：在重新遍历线段时，确保找到的线段符合条件，避免输出错误。
- **顿悟感想**：通过贪心算法和优先队列的结合，能够高效地解决这类选择子集并求最大交集的问题。

---
处理用时：59.50秒