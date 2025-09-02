# 题目信息

# Palindrome Degree

## 题目描述

String $ s $ of length $ n $ is called $ k $ -palindrome, if it is a palindrome itself, and its prefix and suffix of length ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF7D/f337f976991ac53405b164907ebe1f51ebb0830e.png) are $ (k-1) $ -palindromes. By definition, any string (even empty) is 0-palindrome.

Let's call the palindrome degree of string $ s $ such a maximum number $ k $ , for which $ s $ is $ k $ -palindrome. For example, "abaaba" has degree equals to $ 3 $ .

You are given a string. Your task is to find the sum of the palindrome degrees of all its prefixes.

## 样例 #1

### 输入

```
a2A
```

### 输出

```
1```

## 样例 #2

### 输入

```
abacaba
```

### 输出

```
6```

# AI分析结果

### 题目中文重写
# 回文度

## 题目描述
长度为 $n$ 的字符串 $s$ 被称为 $k$ - 回文串，如果它本身是一个回文串，并且它长度为 $\lfloor\frac{n}{2}\rfloor$ 的前缀和后缀都是 $(k - 1)$ - 回文串。根据定义，任何字符串（即使是空串）都是 0 - 回文串。

我们称字符串 $s$ 的回文度为最大的 $k$ 值，使得 $s$ 是 $k$ - 回文串。例如，"abaaba" 的回文度等于 $3$。

给定一个字符串，你的任务是计算它所有前缀的回文度之和。

## 样例 #1
### 输入
```
a2A
```
### 输出
```
1
```

## 样例 #2
### 输入
```
abacaba
```
### 输出
```
6
```

### 综合分析与结论
- **思路**：各题解核心思路一致，均使用动态规划，设 $dp_i$ 表示前缀 $i$ 的回文度。若前缀不是回文串，$dp_i = 0$；若是回文串，$dp_i = dp_{\lfloor\frac{i}{2}\rfloor} + 1$。最终结果为 $\sum_{i = 1}^{n}dp_i$。
- **算法要点**：关键在于判断前缀是否为回文串，大部分题解采用哈希算法，通过计算前缀的正向和反向哈希值来判断；也有题解使用 Manacher 算法预处理判断回文。
- **解决难点**：本题难点在于高效判断回文串，哈希算法通过预处理和公式计算子串哈希值，能快速判断；Manacher 算法则通过预处理得到每个位置的回文半径，进而判断。

### 所选题解
- **作者：唐一文 (赞：24)，5星**
    - **关键亮点**：思路清晰，代码简洁，直接推导出哈希值，未进行预处理，提高了代码的简洁性。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
char c[5000005];
int n,dp[5000005],ans,fac=1,fro,bac;
int main(){
    scanf("%s",c),n=strlen(c);
    for(register int i=0;i<n;++i){
        fro=fro*13+c[i],bac=bac+fac*c[i],fac=fac*13;
       !(fro^bac)?ans+=(dp[i]=dp[i-1>>1]+1):0;
    }
    printf("%d",ans);
}
```
核心思想：在遍历字符串过程中，动态计算正向和反向哈希值，若相等则更新 $dp$ 数组并累加结果。

- **作者：Gaode_Sean (赞：4)，4星**
    - **关键亮点**：思路简洁明了，代码实现简单易懂，同样采用动态计算哈希值的方式。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e6+1;
char ch[maxn];
int n,dp[maxn],t=1,a,b,ans;
int main()
{
    scanf("%s",ch+1);
    n=strlen(ch+1);
    for(int i=1;i<=n;i++){
        a=a*131+ch[i],b+=ch[i]*t;
        t*=131;
        if(a==b) dp[i]=dp[i>>1]+1,ans+=dp[i];
    }
    printf("%d",ans);
    return 0;
}
```
核心思想：遍历字符串，计算正向和反向哈希值，若相等则更新 $dp$ 数组并累加结果。

- **作者：2021hych (赞：1)，4星**
    - **关键亮点**：详细说明了动规思路，代码规范，注释清晰。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 5000001
using namespace std;
string s;
int len,f1[MAXN],f2[MAXN],p[MAXN],dp[MAXN],ans;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>s;
    len=s.size();
    s=" "+s;
    p[0]=1;
    for(int i=1;i<=len;i++) {
        f1[i]=f1[i-1]*131+s[i];
        f2[i]=f2[i-1]*131+s[len-i+1];
        p[i]=p[i-1]*131;
    }
    for(int i=1;i<=len;i++) {
        if(f1[i/2]-f1[0]*p[i/2]==f2[len-i+i/2]-f2[len-i]*p[i/2]) {
            dp[i]=dp[i/2]+1;
            ans+=dp[i];
        }
    }
    cout<<ans;
    return 0;
}
```
核心思想：预处理正向和反向哈希数组以及幂数组，通过比较子串哈希值判断回文，更新 $dp$ 数组并累加结果。

### 最优关键思路或技巧
- **动态规划**：利用子问题重叠特性，通过 $dp_{\lfloor\frac{i}{2}\rfloor}$ 计算 $dp_i$，减少重复计算。
- **哈希算法**：通过计算字符串的哈希值，快速判断子串是否为回文，提高效率。

### 可拓展之处
- **同类型题**：判断字符串中不同回文子串的数量、最长回文子串等。
- **类似算法套路**：在处理字符串匹配、子串判断等问题时，可使用哈希算法和动态规划结合的方法。

### 推荐题目
- [P3501 [POI2010]ANT-Antisymmetry](https://www.luogu.com.cn/problem/P3501)
- [P4555 [国家集训队]最长双回文串](https://www.luogu.com.cn/problem/P4555)
- [P1368 工艺](https://www.luogu.com.cn/problem/P1368)

### 个人心得
无。

---
处理用时：34.90秒