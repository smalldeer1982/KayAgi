# 题目信息

# Message Transmission Error (hard version)

## 题目描述

这是一个难度较高的问题。它与简单版的区别仅在于约束条件不同。

在伯兰州立大学，服务器之间的本地网络并非总是运行无误。当连续传输两条相同的信息时，可能会发生错误，导致两条信息合并为一条。在这种合并中，第一条信息的结尾与第二条信息的开头重合。当然，合并只能发生在相同字符处。合并的长度必须是一个小于信息文本长度的正数。

例如，当连续传送两条信息```abrakadabra```时，可能会出现所述类型的错误、导致出现类似```abrakadabrakadabra```或```abrakadabrakadabra```的信息(前者在一个字符处发生合并，后者在四个字符处发生合并)。

给定接收到的报文 ```t``` ，判断这是否可能是本地网络运行中出现所述类型错误的结果，如果是，请确定可能的值 ```s``` 。

两个报文完全重叠的情况不应视为错误。例如，如果收到的报文是```abcd```，则应认为其中没有错误。同样，简单地在一条信息后附加另一条信息也不是错误的标志。例如，如果收到的信息是 ```abcabc```，也应认为其中没有错误。

## 样例 #1

### 输入

```
abrakadabrabrakadabra```

### 输出

```
YES
abrakadabra```

## 样例 #2

### 输入

```
acacacaca```

### 输出

```
YES
acacaca```

## 样例 #3

### 输入

```
abcabc```

### 输出

```
NO```

## 样例 #4

### 输入

```
abababab```

### 输出

```
YES
ababab```

## 样例 #5

### 输入

```
tatbt```

### 输出

```
NO```

# AI分析结果

### 题解综合分析与结论
这些题解主要围绕判断给定字符串是否是由两条相同信息合并产生的错误结果展开，若存在则找出原字符串。思路上主要分为两类：
1. **KMP 算法类**：利用 KMP 算法求出字符串的最长公共前后缀长度，若该长度的两倍大于字符串长度，则存在错误，原串就是最长公共前后缀。
2. **枚举类**：枚举重合长度，计算原串长度，通过比较字符串区间是否相等判断是否存在原串，可结合哈希优化判断字符串相等的效率。

各题解的算法要点和解决难点如下：
- **KMP 算法类**：要点是构建 `next` 数组求最长公共前后缀；难点在于理解 `next` 数组的构建过程和利用其判断条件。
- **枚举类**：要点是枚举重合长度和比较字符串区间；难点在于判断字符串相等的效率，普通比较是 $O(n)$ 复杂度，可使用哈希优化。

### 所选题解
- **作者：2023nsty04 (4星)**
    - **关键亮点**：思路清晰，详细解释了 KMP 算法的构建过程和判断依据，代码实现简洁明了。
- **作者：cly312 (4星)**
    - **关键亮点**：同样使用 KMP 算法，思路简洁，证明了判断条件的正确性，代码可读性高。
- **作者：SuyctidohanQ (4星)**
    - **关键亮点**：使用 KMP 算法，代码实现规范，对思路有简要说明。

### 重点代码
```cpp
// 作者：2023nsty04
#include<bits/stdc++.h>
using namespace std;
string a;
int n[400010]={0};
int main()
{
    cin>>a;
    int ak=a.size();
    for(int i=1,len=0;i<ak;i++)
    {
        while(len&&a[i]!=a[len])len=n[len-1];
        if(a[len]==a[i])len++;
        n[i]=len;
    }
    if(n[ak-1]>ak/2)
    {
        cout<<"YES"<<endl;
        string s(a,0,n[ak-1]);
        cout<<s;
    }
    else cout<<"NO";
    return 0;
 } 

// 作者：cly312
#include<bits/stdc++.h>
using namespace std;
string s;
int nxt[400000];
int main(){
    int n,i,j;
    cin>>s;
    n=s.length();
    nxt[0]=0;
    j=0;
    for(i=1;i<n;i++){
        while(j>0&&s[i]!=s[j])j=nxt[j-1];
        if(s[i]==s[j])j++;
        nxt[i]=j;
    }
    if(nxt[n-1]*2>n)
        cout<<"YES\n"<<s.substr(0,nxt[n-1])<<'\n';
    else cout<<"NO\n";
    return 0;
}

// 作者：SuyctidohanQ
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll MAXN = 4e5 + 10;
string s;
ll shu[MAXN] = {0}, len, cun = 0;
int main () {
    cin >> s;
    len = s.size ();
    for (ll i = 1; i <= len - 1; i ++) {
        while (cun > 0 && s[i] != s[cun]) cun = shu[cun - 1];
        if (s[i] == s[cun]) cun ++;
        shu[i] = cun;
    }
    if (shu[len - 1] * 2 > len) cout << "YES" << endl << s.substr (0, shu[len - 1]) << endl;
    else cout << "NO" << endl;
    return 0;
}
```
### 核心实现思想
这三个题解核心都是使用 KMP 算法构建 `next` 数组（不同题解中数组名不同），`next[i]` 表示字符串前 `i` 个字符的最长公共前后缀长度。构建过程中，若当前字符与之前匹配上的前缀下一位匹配，则 `next[i]` 加 1；若失配，则往前跳 `next[len - 1]` 步继续匹配。最后判断 `next[n - 1]`（`n` 为字符串长度）的两倍是否大于 `n`，若大于则存在错误，原串就是最长公共前后缀。

### 最优关键思路或技巧
使用 KMP 算法求最长公共前后缀，时间复杂度为 $O(n)$，能高效解决问题。同时，理解最长公共前后缀长度与原串合并的关系，通过比较长度判断是否存在错误。

### 拓展思路
同类型题可考察字符串的匹配、循环节等问题，类似算法套路有：
- 利用 KMP 算法解决字符串匹配问题，如求一个字符串在另一个字符串中出现的次数。
- 利用哈希算法优化字符串比较的效率，如判断多个字符串是否相等。

### 洛谷相似题目
1. [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
2. [P1368 【模板】最小表示法](https://www.luogu.com.cn/problem/P1368)
3. [P4391 [BOI2009]Radio Transmission 无线传输](https://www.luogu.com.cn/problem/P4391)

### 个人心得
题解中未包含个人心得。 

---
处理用时：41.34秒