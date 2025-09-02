# 题目信息

# [JRKSJ R7] Clock Paradox

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/47sjcgd5.png)

一分钟后的出题人阻止了这个时刻的出题人写一个有趣的题目背景。

（题目背景图片来自 Phigros 曲绘，如有侵权，请告知出题人。）

## 题目描述

给你一个字符串 $S$，设 $S=\overline{s_1s_2\dots s_n}$。

有一个字符串 $T$，初始时 $T=S$，你可以进行若干次操作，每次操作可以选取 $S$ 一个子串并插入到 $T$ 的任意位置。

你希望经过若干次操作后，$T=\overline{s_1s_1s_2s_2\dots s_ns_n}$，定义 $f(S)$ 为满足此条件所需的最少的操作次数。

此外，字符串 $S$ 还会发生一些改变。具体地，有 $q$ 次修改操作，每次修改操作会给出 $p$ 和 $\texttt{c}$，表示令 $s_p\gets \texttt{c}$。$\texttt{c}$ 表示任意一个小写字母，而并非 ASCII 为 $99$ 的字符。

你需要在最开始和每次修改后求出 $f(S)$ 的值。

## 说明/提示

Idea：cyffff，Solution：cyffff，Code：cyffff，Data：cyffff

**Clock Paradox - WyvernP (Insane12.6)**

**本题输入输出文件较大，请使用恰当的输入输出方式。**  

### 提示

称字符串 $A$ 是字符串 $S$ 的子串当且仅当存在 $1\le l\le r\le |S|$ 使得 $A=\overline{s_ls_{l+1}\dots s_{r}}$。

### 样例解释
所有修改前，$f(S)$ 的计算方法如下：

初始时，$S=T=\texttt{aabc}$。

第一次操作，选取 $S$ 的子串 $\texttt{aa}$，插入到 $T$ 的最前端，操作后 $T=\texttt{aaaabc}$。

第二次操作，选取 $S$ 的子串 $\texttt{bc}$，插入到 $T$ 的第 $5$ 个字符后，操作后 $T=\texttt{aaaabbcc}$，符合要求。

经过一次修改、两次修改后的 $S$ 分别等于 $\texttt{abbc}$ 和 $\texttt{abbb}$，这两次修改后 $f(S)$ 分别是 $2$ 和 $1$。
### 数据规模

本题采用捆绑测试。
| $\text{Subtask}$ | $\vert S\vert\le$ | $q\le$ | $\text{Score}$ |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $0$ | $10$ |
| $2$ | $10^4$ | $10^4$ | $20$ |
| $3$ | $5\times10^5$ | $0$ | $20$ |
| $4$ | $5\times10^5$ | $5\times 10^5$ | $20$ |
| $5$ | $3\times10^6$ | $3\times 10^6$ | $30$ |

对于 $100\%$ 的数据，$1\le|S|\le3\times10^6$，$0\le q\le 3\times10^6$，保证 $S$ 仅由小写字母构成，保证 $\texttt{c}$ 为单个小写字母。

## 样例 #1

### 输入

```
2
aabc
2 b
4 b```

### 输出

```
2
2
1```

# AI分析结果

### 综合分析与结论
这些题解核心思路一致：先将字符串 $S$ 按连续相同字符划分为若干“块”或“段”，最少操作次数为块数的一半向上取整，即 $\lceil \frac{\text{块数}}{2} \rceil$。初始时遍历字符串统计块数，每次修改时，通过判断修改位置字符与左右字符关系，以 $O(1)$ 复杂度更新块数，从而得出每次修改后的最少操作次数，整体时间复杂度为 $O(|S| + q)$。

### 所选题解
- **作者：AKPC（5星）**
    - **关键亮点**：先给出暴力解法，便于理解，再优化为正解，思路清晰；代码注释详细，可读性强。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int query(int l,int r){
    int ans=0;
    for (int i=l;i<=r;i++) if (s[i]!=s[i-1]) ans++;
    return ans;
}
int n,x,ans;
char ch;
int main(){
    cin>>n>>s;
    ans=query(1,(int)s.length()-1);
    ans%2==1?cout<<(ans+1)/2<<endl:cout<<(ans+2)/2<<endl;
    while (n--){
        cin>>x>>ch;x--;
        ans-=query(x,x+1);
        s[x]=ch;
        ans+=query(x,x+1);
        ans%2==1?cout<<(ans+1)/2<<endl:cout<<(ans+2)/2<<endl;
    }
    return 0;
}
```
    - **核心思想**：`query` 函数用于统计指定区间内块的数量变化。初始时统计整个字符串的块数，每次修改时，先减去修改位置附近的块数变化，更新字符后再加上新的块数变化，最后输出最少操作次数。

- **作者：EdenSky（5星）**
    - **关键亮点**：通过多组数据找规律，详细阐述块的概念和操作方法，思路易懂；代码简洁，使用指针法统计块数，效率较高。
    - **核心代码**：
```cpp
#include<iostream>
#include<string>
using namespace std;
int q,a,cnt;
char c;
string s;
int main(){
    ios::sync_with_stdio(false),
    cin.tie(nullptr);
    cin>>q>>s;
    int k=0,d=s.size();
    s+="#";
    while(k<d){
        while(s[k+1]==s[k]) k++;
        k++,cnt++;
    }
    cout<<cnt/2+cnt%2<<'\n';
    s="#"+s;
    while(q--){
        cin>>a>>c;
        if(s[a]==s[a-1]) cnt++;
        if(s[a]==s[a+1]) cnt++;
        s[a]=c;
        if(s[a]==s[a-1]) cnt--;
        if(s[a]==s[a+1]) cnt--;
        cout<<cnt/2+cnt%2<<'\n';
    }
}
```
    - **核心思想**：使用指针法统计初始字符串的块数。每次修改时，根据修改位置字符与左右字符的关系更新块数，最后输出最少操作次数。

- **作者：cyffff（4星）**
    - **关键亮点**：使用数学归纳法证明结论，逻辑严谨；代码中使用快读快写，可应对大数据量输入。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=3e6+10;
int n,q,x;
char s[N];
int main(){
    q=read();
    n=readstr(s);
    for(int i=1,j=1;i<=n;i=j+1){
        while(j+1<=n&&s[j+1]==s[i]) j++;
        x++;
    }
    write(x+1>>1),putc('\n');
    while(q--){
        int a=read();
        char c=getc();
        if(s[a-1]==s[a]&&s[a-1]!=c)
            x++;
        if(s[a+1]==s[a]&&s[a+1]!=c)
            x++;
        if(s[a-1]!=s[a]&&s[a-1]==c)
            x--;
        if(s[a+1]!=s[a]&&s[a+1]==c)
            x--;
        s[a]=c;
        write(x+1>>1),putc('\n');
    }
    flush();
}
```
    - **核心思想**：先统计初始字符串的颜色段数（即块数），每次修改时，根据修改位置字符与左右字符的关系更新颜色段数，最后输出最少操作次数。

### 最优关键思路或技巧
- **分块思想**：将字符串按连续相同字符划分为块，每两个块可通过一次操作满足要求，简化问题。
- **动态维护**：每次修改时，只关注修改位置字符与左右字符关系，以 $O(1)$ 复杂度更新块数，避免重复计算。

### 可拓展之处
同类型题或类似算法套路：
- 字符串操作类问题，如字符串合并、分割、替换等，可考虑分块思想和动态维护。
- 涉及多次修改和查询的问题，可通过预处理和局部更新来优化时间复杂度。

### 推荐题目
- [P1116 车厢重组](https://www.luogu.com.cn/problem/P1116)：字符串操作与计数问题。
- [P1055 ISBN号码](https://www.luogu.com.cn/problem/P1055)：字符串处理与校验问题。
- [P1200 [USACO1.1]你的飞碟在这儿Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)：字符串转换与计算问题。

### 个人心得摘录与总结
- **作者：code_hyx**：交了7遍才过，说明本题虽思路简单，但细节处理容易出错，需仔细调试。
- **作者：JuRuoOIer**：赛时T2被取模骗了，本题是唯一做出来的题，提醒在比赛中要认真审题，避免掉入陷阱。 

---
处理用时：42.11秒