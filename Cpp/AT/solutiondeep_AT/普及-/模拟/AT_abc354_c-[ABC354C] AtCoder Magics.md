# 题目信息

# [ABC354C] AtCoder Magics

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc354/tasks/abc354_c

高橋くんは、カードゲーム「AtCoder Magics」のカードを $ N $ 枚持っています。$ i $ 番目のカードをカード $ i $ と呼ぶことにします。各カードには強さとコストのパラメーターがあり、カード $ i $ の強さは $ A_i $ で、コストは $ C_i $ です。

高橋くんは、弱いカードは要らないので捨てることにしました。具体的には、以下の操作をできなくなるまで繰り返します。

- $ 2 $ つのカード $ x,\ y $ であって、 $ A_x\ >\ A_y $ かつ $ C_x\ <\ C_y $ であるようなものを選ぶ。カード $ y $ を捨てる。

操作ができなくなったとき、捨てられなかったカードの集合は一意に定まることが証明できます。これを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ A_i,\ C_i\ \leq\ 10^9 $
- $ A_1,\ A_2,\ \dots\ ,A_N $ は全て異なる
- $ C_1,\ C_2,\ \dots\ ,C_N $ は全て異なる
- 入力はすべて整数

### Sample Explanation 1

カード $ 1,\ 3 $ に注目すると、 $ A_1\ <\ A_3 $ かつ $ C_1\ >\ C_3 $ なのでカード $ 1 $ を捨てることができます。 それ以上操作をすることはできません。このときカード $ 2,\ 3 $ が残っているので、これらを出力します。

### Sample Explanation 2

この場合、どのカードも捨てることができません。

## 样例 #1

### 输入

```
3
2 4
1 1
3 2```

### 输出

```
2
2 3```

## 样例 #2

### 输入

```
5
1 1
10 2
100 3
1000 4
10000 5```

### 输出

```
5
1 2 3 4 5```

## 样例 #3

### 输入

```
6
32 101
65 78
2 29
46 55
103 130
52 40```

### 输出

```
4
2 3 5 6```

# AI分析结果

### 题目翻译
高桥有 $N$ 张“AtCoder Magics”卡牌游戏的卡片。我们将第 $i$ 张卡片称为卡片 $i$。每张卡片都有强度和成本这两个参数，卡片 $i$ 的强度是 $A_i$，成本是 $C_i$。

高桥认为弱的卡片不需要，所以决定将其丢弃。具体来说，他会重复以下操作，直到无法再进行为止：
- 选择两张卡片 $x$ 和 $y$，满足 $A_x > A_y$ 且 $C_x < C_y$，然后丢弃卡片 $y$。

可以证明，当操作无法再进行时，未被丢弃的卡片集合是唯一确定的。请找出这个集合。

### 综合分析与结论
这些题解的核心思路都是通过排序将无序的卡牌信息变得有序，从而降低判断卡牌是否需要丢弃的复杂度。大部分题解先对卡牌按强度或成本排序，再遍历卡牌，根据已遍历卡牌的信息（如最大强度、最小成本等）判断当前卡牌是否需要丢弃。

### 所选题解
- **hjyowl（4星）**
    - **关键亮点**：思路清晰，对可行性分析详细，代码注释完善，易于理解。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
const long long N = 100010;
long long n;
struct owl{
    long long x,y,id;
}a[N];
bool cmp(owl a,owl b){
    return a.y < b.y;
}
int main(){
    cin >> n;
    set<int>st;
    for (long long i = 1; i <= n; i ++ ){
        cin >> a[i].x >> a[i].y;
        st.insert(i);
        a[i].id = i;
    }
    sort(a + 1,a + 1 + n,cmp);
    long long mx = -1e9;
    for (long long i = 1; i <= n; i ++ ){
        mx = max(mx,a[i].x);
        if (a[i].x != mx){
            st.erase(a[i].id);
        }
    }
    cout << st.size() << endl;
    set<int>::iterator it;
    for (it = st.begin(); it != st.end(); it ++ ){
        cout << *it << " ";
    }
    return 0;
}
```
    - **核心实现思想**：先按成本从小到大排序，然后遍历卡牌，维护一个最大强度值 `mx`。如果当前卡牌的强度不是最大的，说明存在比它强且成本低的卡牌，将其从集合中删除。

- **forever_nope（4星）**
    - **关键亮点**：对题目的性质进行了详细证明，逻辑严谨，代码简洁。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
template<typename tp>
istream& operator >>(istream &in, vector<tp> &a) {
    for (tp &t : a) in >> t;
    return in;
}
template<typename tp>
ostream& operator <<(ostream &out, vector<tp> &a) {
    for (auto i : a) out << i << " ";
    return out;
}
constexpr int N = 2e5 + 10;
int a[N], c[N];
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n; vector<int> id(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> c[i], id[i] = i;
    sort(id.begin(), id.end(), [] (int i, int j) { return a[i] > a[j]; });
    int mx = 2e9; vector<int> ans;
    for (int i : id) if (c[i] < mx) mx = c[i], ans.push_back(i + 1);
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl << ans << endl;
    return 0;
}
```
    - **核心实现思想**：先按强度从大到小排序，然后遍历卡牌，维护一个最小成本值 `mx`。如果当前卡牌的成本小于 `mx`，则将其加入结果集合，并更新 `mx`。

### 最优关键思路或技巧
- **排序优化**：通过排序将无序的卡牌信息变得有序，从而降低判断卡牌是否需要丢弃的复杂度。
- **维护最值**：在遍历卡牌的过程中，维护最大强度、最小成本等信息，方便判断当前卡牌是否需要丢弃。

### 可拓展之处
同类型题可能会有更多的属性或更复杂的规则，但核心思路仍然是通过排序和维护最值来解决问题。例如，可能会增加卡牌的其他属性，或者改变丢弃卡牌的规则。

### 推荐洛谷题目
- P1093 [NOIP2007 普及组] 奖学金
- P1104 生日
- P1271 [深基9.例1] 选举学生会

### 个人心得摘录与总结
- **Ryzen_9_7950X**：赛时脑抽，赛后1分钟才调出来。总结是在比赛时要保持冷静，避免出现低级错误。 

---
处理用时：34.52秒