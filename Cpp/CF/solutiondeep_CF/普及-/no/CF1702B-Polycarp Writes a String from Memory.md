# 题目信息

# Polycarp Writes a String from Memory

## 题目描述

Polycarp has a poor memory. Each day he can remember no more than $ 3 $ of different letters.

Polycarp wants to write a non-empty string of $ s $ consisting of lowercase Latin letters, taking minimum number of days. In how many days will he be able to do it?

Polycarp initially has an empty string and can only add characters to the end of that string.

For example, if Polycarp wants to write the string lollipops, he will do it in $ 2 $ days:

- on the first day Polycarp will memorize the letters l, o, i and write lolli;
- On the second day Polycarp will remember the letters p, o, s, add pops to the resulting line and get the line lollipops.

If Polycarp wants to write the string stringology, he will do it in $ 4 $ days:

- in the first day will be written part str;
- on day two will be written part ing;
- on the third day, part of olog will be written;
- on the fourth day, part of y will be written.

For a given string $ s $ , print the minimum number of days it will take Polycarp to write it.

## 样例 #1

### 输入

```
6
lollipops
stringology
abracadabra
codeforces
test
f```

### 输出

```
2
4
3
4
1
1```

# AI分析结果

### 题目内容
# Polycarp写字符串

## 题目描述
Polycarp记忆力很差。每天他最多只能记住3个不同的字母。
Polycarp想写一个由小写拉丁字母组成的非空字符串 $s$ ，求最少需要多少天能写完。
Polycarp最初有一个空字符串，并且只能在该字符串末尾添加字符。
例如，如果Polycarp想写字符串“lollipops”，他将在2天内完成：
 - 第一天，Polycarp将记住字母l, o, i 并写出“lolli”；
 - 第二天，Polycarp将记住字母p, o, s ，将“pops”添加到已有的字符串末尾，得到“lollipops”。
如果Polycarp想写字符串“stringology”，他将在4天内完成：
 - 第一天将写出“str”部分；
 - 第二天将写出“ing”部分；
 - 第三天将写出“olog”部分；
 - 第四天将写出“y”部分。
对于给定的字符串 $s$ ，输出Polycarp写完它所需的最少天数。

## 样例 #1
### 输入
```
6
lollipops
stringology
abracadabra
codeforces
test
f
```
### 输出
```
2
4
3
4
1
1
```

### 算法分类
模拟

### 综合分析与结论
所有题解均围绕模拟每天记忆字母的过程展开。核心思路都是从字符串开头遍历，每天尽量记忆不同字母，当一天内记忆的不同字母达到3个且下一个字母不同时，开启新的一天。不同题解在实现方式上存在差异，如使用不同的数据结构来记录已记忆字母，有的用指针、字符变量，有的用数组、集合、哈希表等。

### 所选的题解
- **作者：Jeremiahy (5星)**
    - **关键亮点**：思路清晰，代码简洁明了。使用指针和字符变量直接模拟记忆过程，逻辑直观。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, ans, l;
char a, b, c;
string s;
signed main() {
    cin >> t;
    while (t--) {
        cin >> s;
        ans = l = 0;
        while (l < s.length()) {
            a = b = c = '0';
            ans++;
            for (; ; l++) {
                if (a == '0')
                    a = s[l];
                else if (s[l] == a)
                    continue;
                else if (b == '0')
                    b = s[l];
                else if (s[l] == b)
                    continue;
                else if (c == '0')
                    c = s[l];
                else if (c == s[l])
                    continue;
                else
                    break;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
```
    - **核心实现思想**：初始化指针 $l$ 指向字符串开头，每天开始时初始化三个字符变量 $a,b,c$ 。遍历字符串，依次将未使用的字符存入 $a,b,c$ ，若遇到已使用的字符则跳过，当遇到第四个不同字符时，结束当天循环，开启新一天，直到遍历完整个字符串。
- **作者：yeshubo_qwq (4星)**
    - **关键亮点**：使用数组标记已记忆字母，代码结构清晰，逻辑明确。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
char s[200005];
int f[30],n,i,res,u,j;
void solve(){
    cin>>s+1,n=strlen(s+1);
    res=0;
    for (i=1;i<=n;){
        for (j=0;j<26;j++) f[j]=0;
        u=0;
        res++;
        while (i<=n){
            if (f[s[i]-'a']==1) i++;
            else if (u<3){
                u++;
                f[s[i]-'a']=1;
                i++;
            }
            else break;
        }
    }
    cout<<res<<'\n';
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tests=1;
    cin>>tests;
    while (tests--)
        solve();
    return 0;
}
```
    - **核心实现思想**：定义数组 $f$ 标记字母是否已记忆，每次从字符串开头遍历，若当前字母已记忆则跳过，未记忆且当天记忆字母数小于3时，标记该字母并计数，当记忆字母数达到3时，结束当天循环，开启新一天，直到遍历完字符串。
- **作者：Dream_weavers (4星)**
    - **关键亮点**：利用 `set` 容器自带的去重功能，简化代码实现，思路简洁。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
set <char> q;
string s;
int t,ans;
int main(){
    scanf("%d",&t);
    while(t--){
        cin>>s;
        q.clear(),ans=0;
        for(int i=0;i<s.size();i++){
            q.insert(s[i]);
            if(q.size()>3){
                q.clear();
                q.insert(s[i]);
                ans++;
            }
        }
        if(q.size())ans++;
        printf("%d\n",ans);
    }
    return 0;
}
```
    - **核心实现思想**：遍历字符串，将字符插入 `set` ，当 `set` 大小超过3时，清空 `set` 并重新插入当前字符，同时天数加一，遍历结束后若 `set` 不为空，天数再加一。

### 最优关键思路或技巧
可以利用数据结构的特性简化代码实现，如 `set` 的自动去重功能，能简洁地处理每天记忆不同字母的逻辑。同时，在遍历字符串时，合理使用循环和条件判断，准确模拟每天记忆字母的过程。

### 拓展思路
同类型题通常围绕资源限制下的任务分配展开，类似算法套路是模拟资源使用过程，根据资源限制条件进行相应操作。例如给定一定容量的背包，每次装入不同物品，计算装满背包或达到某种条件所需的次数等。

### 洛谷题目推荐
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：通过枚举组合来解决问题，与本题模拟过程中对不同元素的处理类似。
- [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)：在一定金额限制下选择菜品，与本题在资源限制下完成任务思路相似。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：根据不同包装铅笔的价格和数量，选择最优购买方案，同样涉及在限制条件下的模拟与选择。 

---
处理用时：49.72秒