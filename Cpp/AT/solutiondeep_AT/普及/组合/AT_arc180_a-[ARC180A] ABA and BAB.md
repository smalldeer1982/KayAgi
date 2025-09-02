# 题目信息

# [ARC180A] ABA and BAB

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc180/tasks/arc180_a

`A`, `B` からなる長さ $ N $ の文字列 $ S $ が与えられます．

あなたは以下の $ 2 $ 種類の操作を好きな順序で $ 0 $ 回以上繰り返すことができます．

- $ S $ の中で `ABA` となっている (連続した) 部分を選び，それを `A` で置き換える．
- $ S $ の中で `BAB` となっている (連続した) 部分を選び，それを `B` で置き換える．
 
操作後の $ S $ としてあり得る文字列の個数を $ 10^9+7 $ で割ったあまりを求めてください．

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 250000 $
- $ S $ は `A`, `B` からなる長さ $ N $ の文字列
 
### Sample Explanation 1

操作後の $ S $ としてあり得るのは以下の $ 2 $ 種類の文字列です． - `ABAB`: $ 0 $ 回の操作を行うことでこの文字列を得ることができます． - `AB`: $ S= $`ABAB` の $ 1 $ 文字目から $ 3 $ 文字目までが `ABA` となっています．これを `A` で置き換えると $ S= $`AB` となります． なお，$ S= $`ABAB` の $ 2 $ 文字目から $ 4 $ 文字目までが `BAB` となっているので，これを `B` に置き換える操作も可能です． ただし，その結果得られる `AB` は重複して数えないことに注意してください．

### Sample Explanation 2

操作を $ 1 $ 度も行うことができません．

### Sample Explanation 4

$ 10^9+7 $ で割ったあまりを求めるのを忘れないようにしてください．

## 样例 #1

### 输入

```
4

ABAB```

### 输出

```
2```

## 样例 #2

### 输入

```
1

A```

### 输出

```
1```

## 样例 #3

### 输入

```
17

BBABABAABABAAAABA```

### 输出

```
18```

## 样例 #4

### 输入

```
100

ABAABAABABBABAABAABAABABBABBABBABBABBABBABBABBABBABBABBABBABBABBABAABABAABABBABBABABBABAABAABAABAABA```

### 输出

```
415919090```

# AI分析结果

### 题目翻译
给定一个由 `A` 和 `B` 组成的长度为 $N$ 的字符串 $S$。

你可以按任意顺序重复以下两种操作 0 次或多次：
- 选择 $S$ 中连续的 `ABA` 部分，将其替换为 `A`。
- 选择 $S$ 中连续的 `BAB` 部分，将其替换为 `B`。

请求出操作后 $S$ 可能出现的字符串个数，将结果对 $10^9 + 7$ 取模。

### 综合分析与结论
这些题解的核心思路都是将原字符串拆分成多个由 `A` 和 `B` 交替出现的子串（可称为“交叉字符串”或“模板串”），因为相邻的子串之间不会相互干扰，所以可以根据乘法原理，将每个子串的可能变化数相乘得到最终结果。对于单个由 `A` 和 `B` 交替出现的子串，其可能变化数与子串长度有关，通常为 $\lceil \frac{n}{2} \rceil$ 或 $\lfloor \frac{n + 1}{2} \rfloor$。

### 所选题解
- **Ratio_Y（5星）**
    - **关键亮点**：思路清晰，先得出将字符串分成独立事件的结论，再通过打表找规律得到单个独立事件的样本点数，代码实现中对边界情况的处理很清晰，注释也较为详细。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=250005;
const int mod=1e9+7;
int len,n,tot,w[N];
char ch[N];
bool flag;
long long ans=1;
void Wsolve()
{
    if(n&1) n++;int res=n/2;
    w[++tot]=res; 
}
int main()
{
    scanf("%d",&len);cin>>ch;n=1;
    if(ch[0]=='A') flag=1;
    else flag=0;
    for(int i=1;i<len;i++)
        if((flag&&ch[i]=='B')||(!flag&&ch[i]=='A')) flag^=1,n++;
        else Wsolve(),n=1;
    Wsolve();
    for(int i=1;i<=tot;i++)
        ans=ans*w[i]%mod;
    printf("%lld\n",ans);
    return 0; 
}
```
    - **核心思想**：通过 `flag` 记录上一个字符，判断是否到达独立事件的边界。对于每个独立事件，调用 `Wsolve` 函数计算其样本点数，最后将所有独立事件的样本点数相乘并取模得到结果。

- **Binah_cyc（4星）**
    - **关键亮点**：对思路的阐述较为详细，有对规律的简单证明，代码简洁，使用了宏定义避免了 `long long` 溢出问题。
    - **核心代码**：
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
int n,ans=1;
char c[250005];
signed main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n;
    int sze=0;
    for(int i=1; i<=n; i++)
    {
        cin>>c[i];
        if(c[i]!=c[i-1]) sze++;
        else ans=(((sze/2)%mod+sze&1)%mod*ans)%mod,sze=1;
    }
    ans=(((sze/2)+sze&1)%mod*ans)%mod;
    cout<<ans;
    return 0;
}
```
    - **核心思想**：遍历字符串，统计每个模板串的长度，当遇到相邻字符相同时，计算该模板串的贡献并更新答案，最后处理最后一个模板串的贡献。

- **linjunye（4星）**
    - **关键亮点**：对将连续的 `AB` 串分为一个部分的证明较为详细，虽然不严谨但能帮助理解，代码实现简洁，使用函数封装计算单个子串的方案数。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int mod=1e9+7;
int n;
string s;
string t;
int ans=1;
int cal(string t){
    return (t.size()+1)/2;
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    cin>>s;
    for(int i=0;i<n;i++){
        if(t!=""&&t[t.size()-1]==s[i]){
            ans=(ans*cal(t))%mod;
            t="";
        }
        t+=s[i];
    }
    ans=(ans*cal(t))%mod;
    cout<<ans;
    return 0;
}
```
    - **核心思想**：遍历字符串，将连续的 `AB` 串存储在 `t` 中，当遇到相邻字符相同时，调用 `cal` 函数计算 `t` 的方案数并更新答案，最后处理最后一个子串的方案数。

### 最优关键思路或技巧
- **拆分字符串**：将原字符串拆分成多个由 `A` 和 `B` 交替出现的子串，利用乘法原理计算最终结果，降低问题复杂度。
- **找规律**：通过打表或简单推导，找出由 `A` 和 `B` 交替出现的子串的可能变化数与子串长度的关系。

### 可拓展之处
同类型题目可能会有不同的操作规则，例如可以替换的子串不同，或者操作次数有限制等。解题思路仍然可以考虑将字符串拆分成独立的部分，再根据具体规则计算每个部分的方案数，最后利用乘法原理得到最终结果。

### 推荐洛谷题目
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：涉及组合数学和乘法原理的应用。
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)：需要对字符串进行处理和模拟操作。
- [P1059 明明的随机数](https://www.luogu.com.cn/problem/P1059)：涉及对数据的处理和统计。

### 个人心得摘录与总结
部分题解提到要注意开 `long long` 防止爆 `int`，以及对 $10^9 + 7$ 取模，这是在处理大数运算时常见的注意事项。还有题解提到 AtCoder 不能使用 `cin>>s+1` 的操作，要从下标为 0 开始输入，这是在不同 OJ 平台上的实现细节差异。 

---
处理用时：41.57秒