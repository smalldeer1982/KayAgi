# 题目信息

# Reverse String

## 题目描述

You have a string $ s $ and a chip, which you can place onto any character of this string.

After placing the chip, you move it to the right several (maybe zero) times, i. e. you perform the following operation several times: if the current position of the chip is $ i $ , you move it to the position $ i + 1 $ . Of course, moving the chip to the right is impossible if it is already in the last position.

After moving the chip to the right, you move it to the left several (maybe zero) times, i. e. you perform the following operation several times: if the current position of the chip is $ i $ , you move it to the position $ i - 1 $ . Of course, moving the chip to the left is impossible if it is already in the first position.

When you place a chip or move it, you write down the character where the chip ends up after your action. For example, if $ s $ is abcdef, you place the chip onto the $ 3 $ -rd character, move it to the right $ 2 $ times and then move it to the left $ 3 $ times, you write down the string cdedcb.

You are given two strings $ s $ and $ t $ . Your task is to determine whether it's possible to perform the described operations with $ s $ so that you write down the string $ t $ as a result.

## 说明/提示

Consider the examples.

The first test case is described in the statement.

In the second test case, you can place the chip on the $ 1 $ -st position, move it twice to the right, and then move it twice to the left.

In the fourth test case, you can place the chip on the $ 2 $ -nd position, and then don't move it at all.

In the fifth test case, you can place the chip on the $ 1 $ -st position, move it $ 5 $ times to the right, and then finish the process.

## 样例 #1

### 输入

```
6
abcdef
cdedcb
aaa
aaaaa
aab
baaa
ab
b
abcdef
abcdef
ba
baa```

### 输出

```
YES
YES
NO
YES
YES
NO```

# AI分析结果

### 题目内容
# 反转字符串

## 题目描述
你有一个字符串 $s$ 和一个筹码，你可以将筹码放置在这个字符串的任意一个字符上。

放置筹码后，你将它向右移动若干次（也可能是零次），即你多次执行以下操作：如果筹码当前位置是 $i$ ，你将它移动到位置 $i + 1$ 。当然，如果筹码已经在最后一个位置，就无法再向右移动。

在向右移动筹码后，你再将它向左移动若干次（也可能是零次），即你多次执行以下操作：如果筹码当前位置是 $i$ ，你将它移动到位置 $i - 1$ 。当然，如果筹码已经在第一个位置，就无法再向左移动。

当你放置筹码或移动它时，你写下筹码在操作结束后所在位置的字符。例如，如果 $s$ 是 `abcdef` ，你将筹码放置在第 $3$ 个字符上，向右移动 $2$ 次，然后向左移动 $3$ 次，你写下的字符串就是 `cdedcb` 。

给定两个字符串 $s$ 和 $t$ 。你的任务是确定是否有可能对 $s$ 执行上述操作，使得最终写下的字符串为 $t$ 。

## 说明/提示
考虑以下示例。

第一个测试用例在题目描述中已说明。

在第二个测试用例中，你可以将筹码放置在第 $1$ 个位置，向右移动两次，然后向左移动两次。

在第四个测试用例中，你可以将筹码放置在第 $2$ 个位置，然后根本不移动它。

在第五个测试用例中，你可以将筹码放置在第 $1$ 个位置，向右移动 $5$ 次，然后结束这个过程。

## 样例 #1
### 输入
```
6
abcdef
cdedcb
aaa
aaaaa
aab
baaa
ab
b
abcdef
abcdef
ba
baa
```
### 输出
```
YES
YES
NO
YES
YES
NO
```

### 算法分类
字符串

### 综合分析与结论
这些题解主要分为暴力枚举和利用字符串算法优化两种思路。暴力枚举类题解通过枚举起始点、转折点等，模拟筹码移动过程并判断是否能得到目标字符串，时间复杂度较高但实现相对简单。利用字符串算法优化的题解则借助如KMP、manacher等算法，减少匹配时间，时间复杂度相对较低，但代码实现更复杂。

### 所选的题解
- **作者：cunzai_zsy0531 (赞：4)，星级：4星**
    - **关键亮点**：思路清晰，直接采用 $O(n^3)$ 的暴力枚举，枚举一个开头位置、一个转弯位置、一个结束位置，判断能否匹配上 $t$ 的整个字符串。
    - **核心代码片段**：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1000+13;
char s[N],t[N];
int n,m;
inline void solve(){
    scanf("%s%s",s+1,t+1);n=strlen(s+1),m=strlen(t+1);
    for(int i=1;i<=n;++i){
        if(s[i]!=t[1]) continue;
        int r=1;
        while(r+1<=m&&i+r<=n&&s[i+r]==t[r+1]) ++r;
        if(r==m) return void(puts("YES"));
        for(int j=1;j<=r;++j){
            int l=0;
            while(l+1+j<=m&&i+j-l-2>=1&&s[i+j-l-2]==t[l+1+j]) ++l;
            if(l==m-j) return void(puts("YES"));
        }
    }
    puts("NO");
}
int main(){
    int T;scanf("%d",&T);
    while(T--) solve();
    return 0;
}
```
    - **核心实现思想**：先枚举 $s$ 中的起始位置 $i$，若 $s[i]$ 与 $t[1]$ 不相等则跳过。然后找到从 $i$ 开始能向右走到的最右边位置 $r$，若此时已能匹配整个 $t$ 则输出 “YES”。否则再枚举从哪里开始转弯向左走，判断能否匹配剩余部分。

- **作者：xuanxuan001 (赞：5)，星级：4星**
    - **关键亮点**：利用manacher算法处理回文判断，KMP算法处理子串匹配，将问题分解为回文判断和子串匹配两个子问题，时间复杂度优化到 $O(n)$。
    - **个人心得**：比赛时写的 $O(n)$ 做法调试很久，前后交了15发才通过，主要在KMP部分调试花费时间长。
    - **核心代码片段**：
```cpp
#include<cstdio>
#define MAXN 502
using namespace std;
int minn(int a,int b){return a<b?a:b;}
int qr(){
    char ch=getchar();int s=0;
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){
        s=s*10+ch-'0';ch=getchar();
    }return s;
}int T,sl,tl,man[MAXN<<1],r,kmps1[MAXN<<1],kmps2[MAXN<<1],kmp1[MAXN],kmp2[MAXN],tmp;
char s[MAXN],t[MAXN<<1];bool flag,can[MAXN<<1],can2[MAXN<<1];
int main(){
    T=qr();
    while(T--){
        for(int i=1;i<=tl;i++)man[i]=can[i]=can2[i]=0;
        scanf("%s%s",s+1,t+1);r=1;flag=false;
        for(sl=0;s[sl+1]!='\0';sl++);
        for(tl=0;t[tl+1]!='\0';tl++);kmps2[tl]=0;
        for(int i=2;i<=tl;i++){
            if(i<r+man[r])man[i]=minn(man[(r<<1)-i],r+man[r]-i);
            while(i-man[i]>1&&t[i-man[i]-1]==t[i+man[i]+1])man[i]++;
            if(i+man[i]>r+man[r])r=i;
        }for(int i=2;i<=tl;i++){
            tmp=kmps1[i-1];
            while(tmp&&t[tmp+1]!=t[i])tmp=kmps1[tmp];
            if(t[tmp+1]==t[i])tmp++;kmps1[i]=tmp;
        }for(int i=tl-1;i>0;i--){
            tmp=kmps2[i+1];
            while(tmp&&t[tl-tmp]!=t[i])tmp=kmps2[tl-tmp+1];
            if(t[tl-tmp]==t[i])tmp++;kmps2[i]=tmp;
        }for(int i=1;i<=sl;i++){
            tmp=kmp1[i-1];
            while(tmp&&t[tmp+1]!=s[i])tmp=kmps1[tmp];
            if(tmp<tl&&t[tmp+1]==s[i])tmp++;
            kmp1[i]=tmp;can[kmp1[i]]=true;
        }for(int i=1;i<=sl;i++){
            tmp=kmp2[i-1];
            while(tmp&&t[tl-tmp]!=s[i])tmp=kmps2[tl-tmp+1];
            if(tmp<tl&&t[tl-tmp]==s[i])tmp++;
            kmp2[i]=tmp;can2[kmp2[i]]=true;
        }for(int i=1;i<=tl;i++){
            if(man[i]==i-1)flag|=can2[tl-i+1];
            if(man[i]==tl-i)flag|=can[i];
        }if(flag)printf("YES\n");
        else printf("NO\n");
    }return 0;
}
```
    - **核心实现思想**：先通过manacher算法找出 $t$ 中以每个点为中心的最长回文子串。然后利用KMP算法分别预处理 $t$ 的前缀和翻转后的后缀与 $s$ 的匹配情况。最后根据回文子串的情况结合KMP匹配结果判断是否能得到 $t$。

### 最优关键思路或技巧
对于字符串匹配问题，若数据范围小，暴力枚举能快速解决问题且实现简单。当追求更低时间复杂度时，可利用如manacher、KMP等字符串算法优化。manacher算法可高效找出字符串中的回文子串，KMP算法能快速判断一个字符串是否为另一个字符串的子串，两者结合能有效解决本题这类复杂的字符串匹配问题。

### 可拓展之处
同类型题常涉及字符串的各种操作与匹配，类似算法套路如利用字符串匹配算法（如BM算法等）解决子串查找问题，或利用后缀数组、后缀自动机等数据结构处理更复杂的字符串问题。

### 洛谷相似题目推荐
- [P3375 【模板】KMP字符串匹配](https://www.luogu.com.cn/problem/P3375)
- [P1341 无序字母对](https://www.luogu.com.cn/problem/P1341)
- [P2408 不同子串个数](https://www.luogu.com.cn/problem/P2408)

---
处理用时：82.91秒