# 题目信息

# Balanced Bitstring

## 题目描述

A bitstring is a string consisting only of the characters 0 and 1. A bitstring is called $ k $ -balanced if every substring of size $ k $ of this bitstring has an equal amount of 0 and 1 characters ( $ \frac{k}{2} $ of each).

You are given an integer $ k $ and a string $ s $ which is composed only of characters 0, 1, and ?. You need to determine whether you can make a $ k $ -balanced bitstring by replacing every ? characters in $ s $ with either 0 or 1.

A string $ a $ is a substring of a string $ b $ if $ a $ can be obtained from $ b $ by deletion of several (possibly, zero or all) characters from the beginning and several (possibly, zero or all) characters from the end.

## 说明/提示

For the first test case, the string is already a $ 4 $ -balanced bitstring.

For the second test case, the string can be transformed into 101.

For the fourth test case, the string can be transformed into 0110.

For the fifth test case, the string can be transformed into 1100110.

## 样例 #1

### 输入

```
9
6 4
100110
3 2
1?1
3 2
1?0
4 4
????
7 4
1?0??1?
10 10
11??11??11
4 2
1??1
4 4
?0?0
6 2
????00```

### 输出

```
YES
YES
NO
YES
YES
NO
NO
YES
NO```

# AI分析结果

### 题目内容重写
#### 平衡二进制串

**题目描述**

一个二进制串是一个仅由字符0和1组成的字符串。一个二进制串被称为$k$-平衡的，如果该字符串中每个长度为$k$的子串都包含相同数量的0和1字符（即每个子串中有$\frac{k}{2}$个0和$\frac{k}{2}$个1）。

给定一个整数$k$和一个由字符0、1和?组成的字符串$s$。你需要确定是否可以通过将$s$中的每个?替换为0或1，使得$s$成为一个$k$-平衡的二进制串。

字符串$a$是字符串$b$的子串，如果$a$可以通过从$b$的开头和结尾删除若干个（可能为零或全部）字符得到。

**说明/提示**

对于第一个测试用例，字符串已经是一个$4$-平衡的二进制串。

对于第二个测试用例，字符串可以转换为101。

对于第四个测试用例，字符串可以转换为0110。

对于第五个测试用例，字符串可以转换为1100110。

**样例 #1**

### 输入

```
9
6 4
100110
3 2
1?1
3 2
1?0
4 4
????
7 4
1?0??1?
10 10
11??11??11
4 2
1??1
4 4
?0?0
6 2
????00```

### 输出

```
YES
YES
NO
YES
YES
NO
NO
YES
NO```

### 算法分类
字符串、构造

### 题解分析与结论
各题解的核心思路都是通过分析字符串的性质，找出每个位置字符的约束条件，并判断是否能够满足这些条件。具体来说，题解们主要利用了以下性质：
1. 对于一个$k$-平衡的字符串，$s[i] = s[i+k]$，即每隔$k$个字符必须相同。
2. 通过模$k$的余数将字符串分为$k$个等价类，每个等价类中的字符必须相同。
3. 统计每个等价类中的0和1的数量，判断是否可以通过替换?来满足每个等价类中0和1的数量相等。

### 所选高星题解
#### 题解1：DPair (5星)
**关键亮点**：
- 清晰地分析了字符串的性质，提出了$s[i] = s[i+k]$的约束条件。
- 通过模$k$的余数将字符串分为$k$个等价类，并统计每个等价类中的0和1的数量。
- 判断是否可以通过替换?来满足每个等价类中0和1的数量相等。

**代码核心实现**：
```cpp
int n, k;
int c[300005];
char s[300005];
int main(){
    int t;scanf("%d", &t);
    while(t --){
        scanf("%d%d", &n, &k);
        for (register int i = 0;i < k;i ++) c[i] = -1;//-1表示不确定
        scanf("%s", s + 1);
        bool ck = 1;
        for (register int i = 1;i <= n;i ++){
            if(s[i] == '1'){
                if(c[i % k] == 0){
                    ck = 0;
                    break;
                }
                c[i % k] = 1;
            }
            if(s[i] == '0'){
                if(c[i % k] == 1){
                    ck = 0;
                    break;
                }
                c[i % k] = 0;
            }
        }
        int cnt = 0, num = 0;
        if(!ck) {printf("NO\n");continue;}
        for (register int i = 0;i < k;i ++){
            if(~c[i]) num += c[i];
            else cnt ++;
        }
        if(num > (k >> 1)){
            printf("NO\n");
            continue;
        }
        if(num + cnt >= (k >> 1)){
            printf("YES\n");
        }
        else printf("NO\n");
    }
}
```

#### 题解2：tommymio (4星)
**关键亮点**：
- 通过移动区间的性质，推导出$s_i = s_{i \bmod k}$的约束条件。
- 将字符串分为$k$个等价类，并判断每个等价类中的字符是否一致。
- 统计每个等价类中的0和1的数量，判断是否满足条件。

**代码核心实现**：
```cpp
#include<cstdio>
char s[300005];
int t[300005];
int main() {
    int T;
    scanf("%d",&T);
    while(T--) {
        int n,k,flag=1;
        scanf("%d%d%s",&n,&k,s+1);
        for(register int i=1;i<=k;++i) t[i]=-1;
        for(register int i=1;i<=n;++i) {
            int x=(i-1)%k+1;
            if(s[i]=='?') {continue;}
            if(t[x]!=-1&&s[i]-'0'!=t[x]) {flag=0;break;}
            if(t[x]==-1) {t[x]=s[i]-'0';}
        }
        int cnt0=0,cnt1=0;
        for(register int i=1;i<=k;++i) {if(t[i]!=-1) s[i]=t[i]+'0'; cnt0+=(s[i]-'0'==0);cnt1+=(s[i]-'0'==1);}
        if(cnt0<=k/2&&cnt1<=k/2&&flag) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```

#### 题解3：引领天下 (4星)
**关键亮点**：
- 通过分析子串的性质，推导出$s_i = s_{i+k}$的约束条件。
- 将字符串分为$k$个等价类，并判断每个等价类中的字符是否一致。
- 统计每个等价类中的0和1的数量，判断是否满足条件。

**代码核心实现**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k;
string s,s1;
int main(){
    ios::sync_with_stdio(false);
    cin>>t;
    while(t--){
        bool ok=1;
        cin>>n>>k>>s1;s=" "+s1;
        for(register int i=1;i<=k&&ok;i++){
            int z=s[i]=='?'?-1:s[i]-'0';
            for(register int j=1;j*k+i<=n&&ok;j++)if(z==-1)z=s[j*k+i]=='?'?-1:s[j*k+i]-'0';
            else if(s[j*k+i]!='?'&&s[j*k+i]-'0'!=z)ok=0;//出现矛盾
            s[i]=z==-1?'?':z+'0';//记下可能的取值
        }
        if(!ok){puts("NO");continue;}
        register int cnt1=0,cnt2=0;
        for(register int i=1;i<=k;i++)if(s[i]=='0')cnt1++;else if(s[i]=='1') cnt2++;
        if(cnt1>(k>>1)||cnt2>(k>>1))ok=0;//合理
        puts(ok?"YES":"NO");
    }
    return 0;
}
```

### 最优关键思路或技巧
1. **等价类划分**：通过模$k$的余数将字符串分为$k$个等价类，每个等价类中的字符必须相同。
2. **约束条件**：利用$s[i] = s[i+k]$的性质，确保每个等价类中的字符一致。
3. **统计与判断**：统计每个等价类中的0和1的数量，判断是否可以通过替换?来满足条件。

### 可拓展之处
类似的问题可以通过分析字符串的周期性或等价类划分来解决。例如，判断字符串是否满足某种周期性条件，或者通过划分等价类来简化问题。

### 推荐题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)

### 个人心得摘录
- **DPair**：通过分析字符串的性质，发现$s[i] = s[i+k]$的约束条件，并通过等价类划分和统计0和1的数量来解决问题。
- **tommymio**：通过移动区间的性质，推导出$s_i = s_{i \bmod k}$的约束条件，并通过等价类划分和统计0和1的数量来解决问题。
- **引领天下**：通过分析子串的性质，推导出$s_i = s_{i+k}$的约束条件，并通过等价类划分和统计0和1的数量来解决问题。

---
处理用时：57.54秒