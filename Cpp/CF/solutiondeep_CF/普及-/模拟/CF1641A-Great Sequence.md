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

### 题目内容翻译
#### 伟大的序列

### 题目描述
对于一个正整数 $x$，如果一个正整数序列可以被拆分成若干对，使得每一对中第一个数乘以 $x$ 等于第二个数，那么这个序列就被称为伟大的序列。更正式地说，对于一个正整数 $x$，如果一个长度为 $n$ 的序列 $a$ 满足 $n$ 是偶数，并且存在一个长度为 $n$ 的排列 $p$，使得对于每个 $i$（$1 \leq i \leq \frac{n}{2}$）都有 $a_{p_{2i - 1}} \cdot x = a_{p_{2i}}$，那么序列 $a$ 对于正整数 $x$ 就是伟大的。

山姆有一个序列 $a$ 和一个正整数 $x$。请帮助他让这个序列变得伟大：找出最少需要向序列 $a$ 中添加多少个正整数，才能使它对于数字 $x$ 成为伟大的序列。

### 说明/提示
在第一个测试用例中，山姆很幸运，这个序列已经对于数字 $4$ 是伟大的了，因为你可以将它分成这样的对：$(1, 4)$，$(4, 16)$。因此，我们可以添加 $0$ 个数。

在第二个测试用例中，你可以向序列中添加数字 $1$ 和 $14$，然后你可以将所有 $8$ 个整数分成这样的对：$(1, 2)$，$(1, 2)$，$(2, 4)$，$(7, 14)$。不可能添加少于 $2$ 个整数来修复这个序列。

### 样例 #1
#### 输入
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
#### 输出
```
0
2
3
3
```

### 综合分析与结论
这些题解的核心思路都是通过贪心算法来解决问题，即从小到大遍历序列中的数，尝试将每个数与其 $x$ 倍的数进行匹配，若无法匹配则需要添加一个数。主要区别在于使用的数据结构不同，部分题解使用 `map` 来记录每个数的出现次数，部分题解使用 `multiset` 来存储序列中的数。

### 所选题解
- **作者：Yizhixiaoyun（5星）**
    - **关键亮点**：思路清晰，代码简洁，使用 `unordered_map` 存储每个数的出现次数，时间复杂度较低。
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
核心实现思想：先将序列中的数存入 `unordered_map` 中记录出现次数，然后对序列进行排序，从小到大遍历序列，若当前数 $a_i$ 还有剩余且其 $x$ 倍的数也存在，则将它们的出现次数都减 $1$，否则答案加 $1$。

- **作者：heaksicn（4星）**
    - **关键亮点**：思路清晰，详细解释了代码的实现过程，使用 `map` 存储每个数的出现次数。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
    ll X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(ll x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
ll T; 
ll n,x;
ll a[200001];
map <ll,ll> mp; 
int main(){
    T=read();
    while(T--){
        n=read(),x=read();
        for(int i=1;i<=n;i++) a[i]=read(),mp[a[i]]++;//按入桶中
        sort(a+1,a+n+1);//排序
        int ans=0; 
        for(int i=1;i<=n;i++){
            if(mp[a[i]]==0){//被用过
                continue;
            }
            if(mp[a[i]*x]) mp[a[i]*x]--,mp[a[i]]--;//可以匹配
            else mp[a[i]]--,ans++;//不能匹配
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
核心实现思想：与 Yizhixiaoyun 的题解类似，使用 `map` 记录每个数的出现次数，排序后遍历序列，能匹配则减少出现次数，不能匹配则答案加 $1$。

- **作者：_Flame_（4星）**
    - **关键亮点**：思路清晰，代码简洁，同样使用 `map` 存储每个数的出现次数，提醒了多组数据要清空 `map`。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 200100
using namespace std;

int t;
int n;
int x;

int a[maxn];

map<int,int> p;

signed main(){
    cin>>t;
    while(t--){
        
        cin>>n>>x;
        p.clear();
        int ans=0;
        
        for(int i=1;i<=n;i++){
            cin>>a[i];
            p[a[i]]++;
        }
        sort(a+1,a+n+1);
        
        for(int i=1;i<=n;i++){
            if(p[a[i]]){
                if(p[a[i]*x]){
                    p[a[i]]--;
                    p[a[i]*x]--;
                }
                else{
                    p[a[i]]--;
                    ans++;
                }
            }
        }
        cout<<ans<<endl;
    }
}
```
核心实现思想：使用 `map` 记录数的出现次数，排序后遍历序列，能匹配则减少出现次数，不能匹配则答案加 $1$，每次处理新数据前清空 `map`。

### 最优关键思路或技巧
- 使用 `map` 或 `unordered_map` 来记录每个数的出现次数，避免了开数组可能导致的空间爆炸问题。
- 对序列进行排序后从小到大遍历，保证了贪心算法的正确性。

### 拓展思路
同类型题或类似算法套路：此类题目通常涉及贪心算法和数据结构的运用，例如在其他题目中可能会要求将序列拆分成若干组，满足一定的条件，同样可以使用贪心的思想，结合合适的数据结构来解决。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)：考察贪心算法和优先队列的使用。
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)：考察贪心算法的基本应用。
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)：考察贪心算法在背包问题中的应用。

### 个人心得摘录与总结
- **jiangtaizhe001**：提到 $x\leq 10^6$，$a_i\leq 10^9$，$a_i\cdot x\leq 10^{15}$ 会爆 `int`，一定要开 `long long`，很多人因为没开而 FST 了。总结：在处理涉及乘法运算且数据范围较大的题目时，要注意数据类型的选择，避免溢出问题。
- **Suzt_ilymtics**：指出用乘法（小数匹配大数）要开 `long long`，除法（大数匹配小数）则不需要。总结：根据具体的实现方式，合理选择数据类型，避免因数据溢出导致错误。 

---
处理用时：42.80秒