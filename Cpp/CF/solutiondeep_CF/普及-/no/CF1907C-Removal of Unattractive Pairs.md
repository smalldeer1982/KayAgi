# 题目信息

# Removal of Unattractive Pairs

## 题目描述

Vlad found a string $ s $ consisting of $ n $ lowercase Latin letters, and he wants to make it as short as possible.

To do this, he can remove any pair of adjacent characters from $ s $ any number of times, provided they are different. For example, if $ s $ =racoon, then by removing one pair of characters he can obtain the strings coon, roon, raon, and raco, but he cannot obtain racn (because the removed letters were the same) or rcon (because the removed letters were not adjacent).

What is the minimum length Vlad can achieve by applying any number of deletions?

## 说明/提示

In the first test case of the example, you need to act as follows: "aabc" $ \rightarrow $ "ac" $ \rightarrow $ "". Note that with a different order of deletions, the string will not become empty.

## 样例 #1

### 输入

```
10
4
aabc
5
abaca
10
avbvvcvvvd
7
abcdefg
5
dabbb
8
aacebeaa
7
bbbbacc
6
dacfcc
6
fdfcdc
9
dbdcfbbdc```

### 输出

```
0
1
2
1
1
0
1
0
0
1```

# AI分析结果

### 题目内容中文重写
# 移除不吸引人的字符对

## 题目描述
弗拉德发现了一个由 $n$ 个小写拉丁字母组成的字符串 $s$，他想让这个字符串尽可能短。

为此，只要相邻的两个字符不同，他就可以任意次数地移除字符串 $s$ 中的任意一对相邻字符。例如，如果 $s$ = racoon，那么通过移除一对字符，他可以得到字符串 coon、roon、raon 和 raco，但不能得到 racn（因为移除的字母相同）或 rcon（因为移除的字母不相邻）。

通过进行任意次数的删除操作，弗拉德能得到的字符串的最小长度是多少？

## 说明/提示
在示例的第一个测试用例中，你需要按如下方式操作："aabc" $ \rightarrow $ "ac" $ \rightarrow $ ""。请注意，如果删除顺序不同，字符串不会变为空。

## 样例 #1

### 输入
```
10
4
aabc
5
abaca
10
avbvvcvvvd
7
abcdefg
5
dabbb
8
aacebeaa
7
bbbbacc
6
dacfcc
6
fdfcdc
9
dbdcfbbdc
```

### 输出
```
0
1
2
1
1
0
1
0
0
1
```

### 算法分类
数学

### 综合分析与结论
这些题解的核心思路都是通过统计字符串中出现次数最多的字符的个数，来判断最终字符串的最短长度。具体来说，设出现次数最多的字符个数为 $maxn$，字符串长度为 $n$，若 $maxn \leq \frac{n}{2}$，则最短长度为 $n \bmod 2$；若 $maxn > \frac{n}{2}$，则最短长度为 $2maxn - n$。

各题解的思路和算法要点基本一致，主要区别在于代码实现的细节和风格。解决的难点在于证明为什么只需要考虑出现次数最多的字符就能得到最短长度。

### 所选题解
- 作者：mywzj_mo (赞：13)，4星。关键亮点：思路清晰，代码简洁，对结论有详细的证明。
- 作者：zhouruoheng (赞：2)，4星。关键亮点：通过类比类似题目，帮助理解本题思路，代码规范。
- 作者：yuyc (赞：2)，4星。关键亮点：对最终可能出现的情况分析详细，代码逻辑清晰。

### 重点代码
#### mywzj_mo 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,ans,maxn;
int ch[30];
string s;
int main(){
    cin>>t;
    while(t--){
        memset(ch,0,sizeof(ch));
        cin>>n;
        cin>>s;
        for(int i=0;i<n;i++){
            ch[s[i]-'a']++;
        }
        ans=n%2;
        maxn=0;
        for(int i=0;i<26;i++){
            maxn=max(maxn,ch[i]);
        }
        ans=max(ans,maxn*2-n);
        cout<<ans<<"\n";
    }
}
```
核心实现思想：先统计每个字符的出现次数，找出出现次数最多的字符的个数 $maxn$，然后根据 $maxn$ 和 $n$ 的关系计算最短长度。

#### zhouruoheng 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,t,a[N];
string s;
void solve()
{
    cin>>n>>s;
    for(int i=0;i<n;i++) a[s[i]-'a']++;
    int ma=0;
    for(int i=0;i<26;i++) ma=max(ma,a[i]),a[i]=0;
    cout<<max(n&1,ma*2-n)<<"\n";
}
int main ()
{
    cin>>t;
    while(t--) solve();
    return 0;
}
```
核心实现思想：同样是先统计字符出现次数，找出最大值 $ma$，再根据 $ma$ 和 $n$ 的关系计算结果。

#### yuyc 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int cnt[30];
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin>>T;
    while(T--){
        memset(cnt,0,sizeof(cnt));
        int n,maxcnt = 0;
        string s;
        cin>>n>>s;
        for(int i=0;i<s.size();i++){
            cnt[s[i] - 'a']++;
            maxcnt = max(maxcnt,cnt[s[i] - 'a']);
        }
        if(maxcnt <= n / 2) cout<<n % 2;
        else cout<<maxcnt - (n - maxcnt);
        cout<<'\n';
    }
    return 0;
}
```
核心实现思想：统计字符出现次数，得到 $maxcnt$，根据 $maxcnt$ 和 $n$ 的大小关系输出结果。

### 最优关键思路或技巧
通过数学分析，发现只需要关注出现次数最多的字符的个数，就可以确定最终字符串的最短长度，避免了复杂的模拟删除过程。

### 可拓展之处
同类型题目可能会改变删除字符的规则，或者对字符串的处理有其他要求，但核心思路可能仍然是通过分析字符的出现次数来解决问题。类似的算法套路可以应用在一些需要对字符串进行操作并求最终状态的题目中。

### 推荐洛谷题目
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)
2. [P1071 潜伏者](https://www.luogu.com.cn/problem/P1071)
3. [P1125 笨小猴](https://www.luogu.com.cn/problem/P1125)

### 个人心得
题解中未包含个人心得。

---
处理用时：37.01秒