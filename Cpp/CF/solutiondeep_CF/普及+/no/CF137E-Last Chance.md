# 题目信息

# Last Chance

## 题目描述

Having read half of the book called "Storm and Calm" on the IT lesson, Innocentius was absolutely determined to finish the book on the maths lessons. All was fine until the math teacher Ms. Watkins saw Innocentius reading fiction books instead of solving equations of the fifth degree. As during the last maths class Innocentius suggested the algorithm of solving equations of the fifth degree in the general case, Ms. Watkins had no other choice but to give him a new task.

The teacher asked to write consecutively (without spaces) all words from the "Storm and Calm" in one long string $ s $ . She thought that a string is good if the number of vowels in the string is no more than twice more than the number of consonants. That is, the string with $ v $ vowels and $ c $ consonants is good if and only if $ v<=2c $ .

The task Innocentius had to solve turned out to be rather simple: he should find the number of the longest good substrings of the string $ s $ .

## 说明/提示

In the first sample there is only one longest good substring: "Abo" itself. The other good substrings are "b", "Ab", "bo", but these substrings have shorter length.

In the second sample there is only one longest good substring: "EIS". The other good substrings are: "S", "IS".

## 样例 #1

### 输入

```
Abo
```

### 输出

```
3 1
```

## 样例 #2

### 输入

```
OEIS
```

### 输出

```
3 1
```

## 样例 #3

### 输入

```
auBAAbeelii
```

### 输出

```
9 3
```

## 样例 #4

### 输入

```
AaaBRAaaCAaaDAaaBRAaa
```

### 输出

```
18 4
```

## 样例 #5

### 输入

```
EA
```

### 输出

```
No solution
```

# AI分析结果

### 题目内容
# 最后机会

## 题目描述
在信息技术课上读了一半名为《风暴与平静》的书后，伊诺森修斯下定决心要在数学课上读完这本书。一切都很顺利，直到数学老师沃特金斯女士看到伊诺森修斯在读小说而不是解五次方程。由于在上一节数学课上，伊诺森修斯提出了一般情况下解五次方程的算法，沃特金斯女士别无选择，只能给他布置一个新任务。

老师要求将《风暴与平静》中的所有单词连续（无空格）写成一个长字符串 $s$ 。她认为一个字符串是好的，如果该字符串中元音字母的数量不超过辅音字母数量的两倍。也就是说，对于有 $v$ 个元音字母和 $c$ 个辅音字母的字符串，当且仅当 $v \leq 2c$ 时，该字符串是好的。

伊诺森修斯要解决的任务其实相当简单：他需要找出字符串 $s$ 中最长的好子串的数量。

## 说明/提示
在第一个样例中，只有一个最长的好子串：“Abo” 本身。其他好子串有 “b”、“Ab”、“bo”，但这些子串长度较短。

在第二个样例中，只有一个最长的好子串：“EIS”。其他好子串有：“S”、“IS”。

## 样例 #1
### 输入
```
Abo
```
### 输出
```
3 1
```

## 样例 #2
### 输入
```
OEIS
```
### 输出
```
3 1
```

## 样例 #3
### 输入
```
auBAAbeelii
```
### 输出
```
9 3
```

## 样例 #4
### 输入
```
AaaBRAaaCAaaDAaaBRAaa
```
### 输出
```
18 4
```

## 样例 #5
### 输入
```
EA
```
### 输出
```
No solution
```

### 算法分类
前缀和

### 综合分析与结论
这几道题解的核心思路都是将元音和辅音赋予不同数值，通过前缀和数组来判断子串是否满足条件。不同题解在后续寻找最长子串及其数量的方法上有所差异。有的利用二分查找、尺取法，有的通过记录数值出现位置来计算长度，还有的使用树状数组等数据结构解决二维偏序问题。整体来看，各题解在思路清晰度、代码可读性和优化程度上存在一定差距。

### 所选的题解
- **作者：Yuby (赞：3)  星级：5星**
    - **关键亮点**：思路清晰，先将问题拆解，通过巧妙的赋值构造前缀和数组。创新性地利用前缀和数组的性质，推导出更优答案的条件，进而提出二分查找和尺取法两种高效解法，代码简洁且运行速度快。
    - **个人心得**：无
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
#define pc putchar
using namespace std;
typedef long long ll;
const ll MAXN=2e5+7;
inline ll read(){ll read_result=0,is_below_0=0;char now_ch=0;while(!isdigit(now_ch)){is_below_0|=now_ch=='-';now_ch=getchar();}while(isdigit(now_ch)){read_result=(read_result<<3)+(read_result<<1)+(now_ch^48);now_ch=getchar();}return is_below_0?-read_result:read_result;}
inline void write(ll x){if(x<0){putchar('-');x=-x;}if(x>9){write(x/10);}putchar(x%10+'0');}
ll n,suf[MAXN],pre[MAXN];
char str[MAXN];
bool check(const char& x)
{
    return x=='a'||x=='e'||x=='i'||x=='o'||x=='u'||x=='A'||x=='E'||x=='I'||x=='O'||x=='U';
}
int main()
{
    scanf("%s",(str+1));
    n=strlen(str+1);
    for(ll i=1;i<=n;i++)
    {
        pre[i]=pre[i-1];
        if(check(str[i]))pre[i]--;
        else pre[i]+=2;
    }
    for(ll i=n;i>=1;i--)suf[i]=max(pre[i],suf[i+1]);
    ll i=1,j=1,minn=INF,ans=0,las=-1;
    while(i<=n)
    {
        while(pre[i-1]>=minn&&i<=n)i++;
        if(las==i)break;
        las=i;
        minn=pre[i-1];
        j=max(j,i);
        while(suf[j+1]>=pre[i-1]&&j<=n)j++;
        j--;
        if(pre[j]>=pre[i-1])ans=max(ans,j-i+1);
    }
    if(!ans)puts("No solution");
    else
    {
        ll cnt=0;
        for(ll i=1;i+ans-1<=n;i++)
            if(pre[i+ans-1]>=pre[i-1])cnt++;
        write(ans),pc(32),write(cnt),pc(10);
    }
    return 0;
}
```
    - **核心实现思想**：先将辅音字母赋值为 $+2$，元音字母赋值为 $-1$ 构造前缀和数组 `pre`。再通过后缀最大值数组 `suf` 辅助，利用尺取法的思路，在 $O(n)$ 时间复杂度内找到最长好子串长度 `ans`，最后遍历前缀和数组统计长度为 `ans` 的好子串数量 `cnt`。

- **作者：ofsl (赞：2)  星级：4星**
    - **关键亮点**：通过设 $v_{i}$ 为前 $i$ 个字符的元音个数，$c_{i}$ 为前 $i$ 个字符的辅音个数的两倍，构造 $t_{i}=c_{i}-v_{i}$，将子串判断条件转化为 $t_{j}\geqslant t_{i - 1}$。通过记录 $t$ 值的首次和末次出现位置，巧妙计算合法子串长度，思路较为新颖。
    - **个人心得**：无
    - **重点代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int v,c,ans,n,cnt=1,l[200005],r[200005];
char s[200005];
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++){
        if(s[i]<97)s[i]+=32;
        if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u')v++;
        else c+=2;
        int t=c-v+n+1;
        if(t>n){
            ans=i;
            continue;
        }
        if(!l[t])l[t]=i;
        r[t]=i;
    }
    l[0]=0x3f3f3f3f;
    for(int i=1;i<=n;i++){
        if(l[i]){
            l[i]=min(l[i],l[i-1]);
            int len=r[i]-l[i];
            if(len==ans)cnt++;
            if(len>ans)ans=len,cnt=1;
        }else
            l[i]=l[i-1];
    }
    if(ans==0)puts("No solution");
    else printf("%d %d\n",ans,cnt);
    return 0;
}
```
    - **核心实现思想**：先将读入字符串统一小写，遍历字符串统计元音 `v` 和辅音 `c` 数量，计算 `t = c - v + n + 1` 防止负数。若 `t > n`，则当前子串长度为 `i`。否则记录 `t` 的首次出现位置 `l[t]` 和末次出现位置 `r[t]`。最后遍历 `l` 数组，更新最长子串长度 `ans` 和其数量 `cnt`。

### 最优关键思路或技巧
将元音和辅音赋予不同数值构造前缀和数组，通过分析前缀和数组元素之间的关系，利用尺取法、记录位置等技巧高效解决问题。这种将字符问题转化为数值问题，并借助前缀和性质的方法是解决本题的关键。

### 可拓展思路
同类型题通常围绕字符串子串条件判断与长度计算，类似算法套路为将字符串元素映射为数值，利用前缀和数组快速判断子串性质，再结合不同的数据结构或算法优化技巧，如二分、尺取、树状数组等，解决子串长度及数量的计算问题。

### 洛谷相似题目推荐
- [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)：同样是利用前缀和思想，求最大子段和，可锻炼对前缀和应用的理解。
- [P3166 [CQOI2014]数三角形](https://www.luogu.com.cn/problem/P3166)：通过坐标点构造三角形，利用前缀和优化计算三角形数量，与本题利用前缀和解决子串问题思路类似。
- [P1414 又是毕业季II](https://www.luogu.com.cn/problem/P1414)：利用前缀和统计满足条件的子序列数量，与本题统计满足条件子串数量思路有相通之处。 

---
处理用时：92.55秒