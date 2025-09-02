# 题目信息

# Great Sequence

## 题目描述

A sequence of positive integers is called great for a positive integer $ x $ , if we can split it into pairs in such a way that in each pair the first number multiplied by $ x $ is equal to the second number. More formally, a sequence $ a $ of size $ n $ is great for a positive integer $ x $ , if $ n $ is even and there exists a permutation $ p $ of size $ n $ , such that for each $ i $ ( $ 1 \le i \le \frac{n}{2} $ ) $ a_{p_{2i-1}} \cdot x = a_{p_{2i}} $ .

Sam has a sequence $ a $ and a positive integer $ x $ . Help him to make the sequence great: find the minimum possible number of positive integers that should be added to the sequence $ a $ to make it great for the number $ x $ .

## 说明/提示

In the first test case, Sam got lucky and the sequence is already great for the number $ 4 $ because you can divide it into such pairs: $ (1, 4) $ , $ (4, 16) $ . Thus we can add $ 0 $ numbers.

In the second test case, you can add numbers $ 1 $ and $ 14 $ to the sequence, then you can divide all $ 8 $ integers into such pairs: $ (1, 2) $ , $ (1, 2) $ , $ (2, 4) $ , $ (7, 14) $ . It is impossible to add less than $ 2 $ integers to fix the sequence.

## 样例 #1

### 输入

```
4
4 4
1 16 4 4
6 2
1 2 2 2 4 7
5 3
5 2 3 5 15
9 10
10 10 10 20 1 100 200 2000 3```

### 输出

```
0
2
3
3```

# AI分析结果

### 题目中文重写
# 优秀序列

## 题目描述
对于一个正整数 $x$，一个正整数序列被称为优秀序列，当且仅当我们可以将其拆分成若干对，使得每一对中的第一个数乘以 $x$ 等于第二个数。更正式地说，一个长度为 $n$ 的序列 $a$ 对于正整数 $x$ 是优秀序列，当且仅当 $n$ 是偶数，并且存在一个长度为 $n$ 的排列 $p$，使得对于每个 $i$（$1 \le i \le \frac{n}{2}$），都有 $a_{p_{2i - 1}} \cdot x = a_{p_{2i}}$。

山姆有一个序列 $a$ 和一个正整数 $x$。请帮助他将该序列变成优秀序列：找出最少需要添加到序列 $a$ 中的正整数个数，使得该序列对于数字 $x$ 成为优秀序列。

## 说明/提示
在第一个测试用例中，山姆很幸运，该序列已经是对于数字 $4$ 的优秀序列，因为你可以将其分成这样的对：$(1, 4)$，$(4, 16)$。因此，我们可以添加 $0$ 个数。

在第二个测试用例中，你可以向序列中添加数字 $1$ 和 $14$，然后你可以将所有 $8$ 个整数分成这样的对：$(1, 2)$，$(1, 2)$，$(2, 4)$，$(7, 14)$。不可能添加少于 $2$ 个整数来修正该序列。

## 样例 #1
### 输入
```
4
4 4
1 16 4 4
6 2
1 2 2 2 4 7
5 3
5 2 3 5 15
9 10
10 10 10 20 1 100 200 2000 3
```

### 输出
```
0
2
3
3
```

### 综合分析与结论
这些题解的核心思路都是贪心算法，即尽量让已有的数相互匹配，不能匹配的就添加新数。主要区别在于使用的数据结构不同，包括 `map`、`multiset`、`priority_queue` 等。

### 所选的题解
- **Yizhixiaoyun（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `unordered_map` 存储每个数的出现次数，排序后遍历数组进行匹配，时间复杂度较低。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=200010;
int T;
int n,a[maxn];
int x;
int ans;
unordered_map<int,int> mp;
inline void init(){
    mp.clear();ans=0;
    cin>>n>>x;
    for(register int i=1;i<=n;++i){
        cin>>a[i];
        mp[a[i]]++;
    }
    sort(a+1,a+n+1);
}
signed main(){
    cin>>T;
    while(T--){
        init();
        for(register int i=1;i<=n;++i){
            if(mp[a[i]]==0) continue;
            if(mp[a[i]*x]!=0){
                mp[a[i]]--;
                mp[a[i]*x]--;
            }
            else{
                mp[a[i]]--;
                ans++;
            }
        }
        cout<<ans<<endl;
    }
}
```
    - **核心实现思想**：先将所有数存入 `unordered_map` 中记录出现次数，对数组排序后遍历，若当前数 $a_i$ 还有剩余且 $a_i * x$ 也存在，则将它们的计数都减一；若 $a_i * x$ 不存在，则答案加一。

- **ExplodingKonjac（4星）**
    - **关键亮点**：使用 `multiset` 存储原序列，每次取出最小的数进行匹配，对贪心算法的正确性进行了证明。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL T,n,k,x,ans,a[200005];
multiset<LL> s;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>n>>k,ans=0;
        for(int i=1;i<=n;i++)    cin>>a[i],s.insert(a[i]);
        while(!s.empty())
        {
            auto it=s.begin();
            x=*it,s.erase(it);
            if(!s.empty() && (it=s.find(x*k))!=s.end())
                s.erase(it);
            else
                ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：将所有数存入 `multiset` 中，不断取出最小的数 $a$，若 $a * k$ 存在则删除，否则答案加一。

- **windflower（4星）**
    - **关键亮点**：使用优先队列和 `map` 结合，优先处理最小值，思路清晰，代码简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,x;
int main(){
    cin>>t;
    while(t--){
        cin>>n>>x;
        int ans=0,a;
        priority_queue<int,vector<int>,greater<int>>q;
        map<long long,int>m;
        for(int i=0;i<n;i++){
            scanf("%d",&a);
            q.push(a);
            m[a]++;
        }
        while(!q.empty()){
            int now=q.top();
            q.pop();
            if(!m[now])continue;
            m[now]--;
            if(m[1ll*now*x])m[now*x]--;
            else ans++;
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
    - **核心实现思想**：用优先队列存储所有数，按从小到大的顺序取出，用 `map` 记录每个数的出现次数，若当前数 $now$ 还有剩余且 $now * x$ 存在，则将它们的计数都减一；若 $now * x$ 不存在，则答案加一。

### 最优关键思路或技巧
- **贪心算法**：从小到大遍历序列，能匹配就匹配，不能匹配就添加新数，保证了结果的最优性。
- **数据结构的选择**：使用 `map`、`multiset` 或优先队列等数据结构来存储和处理数据，方便查找和删除操作。

### 可拓展之处
同类型题目可能会改变匹配规则，如匹配条件变为 $a_i + x = a_j$ 等，或者增加更多的限制条件。解题思路仍然可以是贪心算法，根据具体规则调整匹配逻辑。

### 推荐洛谷题目
- P1094 [NOIP2007 普及组] 纪念品分组
- P1223 排队接水
- P1803 凌乱的yyy / 线段覆盖

### 个人心得摘录与总结
- **jiangtaizhe001**：提到 $a_i\cdot x$ 会爆 `int`，一定要开 `long long`，很多人因为没开而 FST，提醒我们在处理数据时要注意数据范围。
- **Suzt_ilymtics**：指出用乘法时要开 `long long`，除法时不需要，让我们了解到不同实现方式对数据类型的要求。 

---
处理用时：48.61秒