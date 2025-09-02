# 题目信息

# Shurikens

## 题目描述

Tenten runs a weapon shop for ninjas. Today she is willing to sell $ n $ shurikens which cost $ 1 $ , $ 2 $ , ..., $ n $ ryo (local currency). During a day, Tenten will place the shurikens onto the showcase, which is empty at the beginning of the day. Her job is fairly simple: sometimes Tenten places another shuriken (from the available shurikens) on the showcase, and sometimes a ninja comes in and buys a shuriken from the showcase. Since ninjas are thrifty, they always buy the cheapest shuriken from the showcase.

Tenten keeps a record for all events, and she ends up with a list of the following types of records:

- + means that she placed another shuriken on the showcase;
- - x means that the shuriken of price $ x $ was bought.

Today was a lucky day, and all shurikens were bought. Now Tenten wonders if her list is consistent, and what could be a possible order of placing the shurikens on the showcase. Help her to find this out!

## 说明/提示

In the first example Tenten first placed shurikens with prices $ 4 $ and $ 2 $ . After this a customer came in and bought the cheapest shuriken which costed $ 2 $ . Next, Tenten added a shuriken with price $ 3 $ on the showcase to the already placed $ 4 $ -ryo. Then a new customer bought this $ 3 $ -ryo shuriken. After this she added a $ 1 $ -ryo shuriken. Finally, the last two customers bought shurikens $ 1 $ and $ 4 $ , respectively. Note that the order $ [2, 4, 3, 1] $ is also valid.

In the second example the first customer bought a shuriken before anything was placed, which is clearly impossible.

In the third example Tenten put all her shurikens onto the showcase, after which a customer came in and bought a shuriken with price $ 2 $ . This is impossible since the shuriken was not the cheapest, we know that the $ 1 $ -ryo shuriken was also there.

## 样例 #1

### 输入

```
4
+
+
- 2
+
- 3
+
- 1
- 4```

### 输出

```
YES
4 2 3 1```

## 样例 #2

### 输入

```
1
- 1
+```

### 输出

```
NO```

## 样例 #3

### 输入

```
3
+
+
+
- 2
- 1
- 3```

### 输出

```
NO```

# AI分析结果

### 题目翻译
### 手里剑

#### 题目描述
天天经营着一家忍者武器店。今天，她打算出售 $n$ 个手里剑，这些手里剑的价格分别为 $1$、$2$、……、$n$ 两（当地货币）。在一天中，天天会将手里剑摆放到展示台上，展示台在一天开始时是空的。她的工作相当简单：有时，天天会把另一个手里剑（从可用的手里剑中）放到展示台上；有时，会有一个忍者进来，从展示台上购买一个手里剑。由于忍者们都很节俭，他们总是购买展示台上最便宜的手里剑。

天天会记录所有事件，最终会得到一份包含以下类型记录的列表：
- `+` 表示她在展示台上放置了另一个手里剑；
- `- x` 表示价格为 $x$ 的手里剑被买走。

今天是幸运的一天，所有手里剑都被卖出去了。现在，天天想知道她的记录列表是否一致，以及可能的手里剑摆放顺序。请帮助她找出答案！

#### 说明/提示
在第一个样例中，天天首先摆放了价格为 $4$ 和 $2$ 的手里剑。之后，一位顾客进来买走了最便宜的、价格为 $2$ 的手里剑。接着，天天在已经摆放的价格为 $4$ 的手里剑旁边，又在展示台上添加了一个价格为 $3$ 的手里剑。然后，一位新顾客买走了这个价格为 $3$ 的手里剑。之后，她添加了一个价格为 $1$ 的手里剑。最后，最后两位顾客分别买走了价格为 $1$ 和 $4$ 的手里剑。注意，顺序 $[2, 4, 3, 1]$ 也是有效的。

在第二个样例中，第一位顾客在任何东西都还没摆放之前就买走了一个手里剑，这显然是不可能的。

在第三个样例中，天天把所有手里剑都放到了展示台上，之后一位顾客进来买走了价格为 $2$ 的手里剑。这是不可能的，因为这个手里剑不是最便宜的，我们知道价格为 $1$ 的手里剑也在那里。

#### 样例 #1
##### 输入
```
4
+
+
- 2
+
- 3
+
- 1
- 4
```
##### 输出
```
YES
4 2 3 1
```

#### 样例 #2
##### 输入
```
1
- 1
+
```
##### 输出
```
NO
```

#### 样例 #3
##### 输入
```
3
+
+
+
- 2
- 1
- 3
```
##### 输出
```
NO
```

### 算法分类
模拟

### 综合分析与结论
这些题解主要围绕判断记录列表是否合法以及找出可能的手里剑摆放顺序展开。大部分题解采用倒序操作的思路，通过维护栈、堆、单调栈等数据结构来模拟手里剑的放置和购买过程，判断是否满足“每次购买最便宜的手里剑”这一条件。各题解的主要区别在于使用的数据结构和具体的实现细节不同，但核心都是模拟操作并检查合法性。

### 所选题解
- **AFOier（5星）**
    - **关键亮点**：思路清晰，代码简洁，直接通过倒序操作维护栈，利用栈的特性判断合法性并找出摆放顺序，时间复杂度为 $O(n)$。
    - **个人心得**：无
- **NightmareAlita（4星）**
    - **关键亮点**：详细分析了不合法情况，通过栈实现倒序操作，逻辑清晰，代码可读性高。
    - **个人心得**：无
- **lyhqwq（4星）**
    - **关键亮点**：采用倒序操作，利用优先队列维护最小值，判断合法性并记录答案，代码实现简洁。
    - **个人心得**：无

### 重点代码
#### AFOier
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, sta[200011], cnt;
int s[200011], ans[200011];
char opt[200011];
int main() {
    scanf("%d", &n); n *= 2;
    for(int i = 1; i <= n; i++) {
        cin >> opt[i];
        if(opt[i] == '-') scanf("%d", &s[i]);
    }
    for(int i = n; i >= 1; i--) {
        if(opt[i] == '-') {
            if(cnt && s[i] > sta[cnt]) {
                cout << "NO" << endl;
                return 0;
            }
            sta[++cnt] = s[i];
        }
        else {
            if(!cnt) {
                cout << "NO" << endl;
                return 0;
            }
            ans[i] = sta[cnt--];
        }
    }
    cout << "YES" << endl;
    for(int i = 1; i <= n; i++) 
        if(opt[i] == '+') cout << ans[i] << " ";
    return 0;
}
```
**核心实现思想**：倒序遍历操作记录，遇到购买操作将价格压入栈，遇到放置操作弹出栈顶元素。若压入元素大于栈顶元素或弹栈时栈为空则无解。

#### NightmareAlita
```cpp
#include <iostream>
#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

namespace SHAWN {
    stack<int> s;
    stack<int> ans;
    vector<int> opt;
    int n;
    int work()
    {
        cin >> n;
        for (int i = 1; i <= 2 * n; ++i) {
            char op; int x;
            cin >> op;
            if (op == '+') { opt.emplace_back(0); }
            else if(op == '-') { cin >> x; opt.emplace_back(x); }
        }
        for (int i = opt.size() - 1; i >= 0; --i) {
            if (!opt[i]) {
                if (s.empty()) { cout << "NO\n"; return 0; }
                else { ans.push(s.top()); s.pop(); }
            }
            else {
                if (s.size() && opt[i] > s.top()) { cout << "NO\n"; return 0; }
                else { s.push(opt[i]); }
            }
        }
        cout << "YES\n"; 
        while (!ans.empty()) { cout << ans.top() << ' '; ans.pop(); }
        return 0;
    }
}

signed int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    return SHAWN :: work();
}
```
**核心实现思想**：倒序遍历操作记录，遇到取数操作将数压入栈，遇到插入操作弹出栈顶元素到另一个栈。若栈为空或入栈元素大于栈顶元素则无解。

#### lyhqwq
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
struct node{
    char op;
    int x;
}a[N];
int n,x;
int ans[N];
priority_queue<int,vector<int>,greater<int> > q;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++){
        scanf(" %c",&a[i].op);
        if(a[i].op=='-') scanf("%d",&a[i].x);
    }
    x=n;
    for(int i=2*n;i>=1;i--){
        if(a[i].op=='+'){
            if(q.empty()) return puts("NO"),0;
            ans[x--]=q.top();
            q.pop();
        }
        else{
            if(!q.empty()&&q.top()<a[i].x) return puts("NO"),0;
            q.push(a[i].x);
        }
    }
    puts("YES");
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}
```
**核心实现思想**：倒序遍历操作记录，遇到放置操作从优先队列中取出最小值，遇到购买操作将价格加入优先队列。若优先队列空或加入元素大于队列最小值则无解。

### 关键思路或技巧
- **倒序操作**：将问题反转，把购买操作变为放入操作，放置操作变为取出操作，简化了问题的处理。
- **栈和优先队列的使用**：利用栈和优先队列的特性，方便地维护手里剑的顺序和最小值，判断合法性。

### 拓展思路
同类型题可能会有不同的操作规则和限制条件，但核心思路都是模拟操作过程并检查合法性。类似算法套路包括使用栈、队列、优先队列等数据结构来模拟操作，通过倒序或正序遍历操作记录来解决问题。

### 推荐题目
- [P1047 [NOIP2005 普及组] 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1098 [NOIP2007 提高组] 字符串的展开](https://www.luogu.com.cn/problem/P1098)
- [P1160 队列安排](https://www.luogu.com.cn/problem/P1160)

---
处理用时：61.35秒