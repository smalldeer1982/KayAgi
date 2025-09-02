# 题目信息

# 「Cfz Round 1」Permutation

## 题目背景

$1+2+3+\cdots+n=\dfrac {n\times (n+1)} 2$。

## 题目描述

给定一个正整数 $n$。

我们定义，对于一个 $1$ 到 $n$ 的排列 $\{x_n\}$， $f(\{x_n\})=\max\limits_{i=1}^{n}(x_i+x_{(i \bmod n)+1})-\min\limits_{i=1}^{n}(x_i+x_{(i \bmod n)+1})$。

你需要构造一个 $1$ 到 $n$ 的排列 $\{p_n\}$，使得对于任意一个 $1$ 到 $n$ 的排列 $\{q_n\}$，都有 $f(\{p_n\})\le f(\{q_n\})$，并输出你构造的排列 $\{p_n\}$。

## 说明/提示

#### 【样例解释 #1】

$f(\{1,4,2,3\})=2$，可以证明对于任意一个 $1$ 到 $n$ 的排列 $\{q_n\}$，都有 $f(\{1,4,2,3\})\le f(\{q_n\})$。

当然，$\{1,3,2,4\},\{3,1,4,2\},\{4,1,3,2\}$ 等也为合法的排列 $\{p_n\}$。

#### 【数据范围】

对于所有数据，$3 \le n \le 10^6$。

**本题采用捆绑测试。**

|子任务编号|分值|$n \le$|特殊性质|
|:---:|:---:|:---:|:---:|
|$1$|$20$|$8$|无|
|$2$|$25$|$10^6$|保证 $n \equiv 0 \pmod 2$|
|$3$|$25$|$10^6$|保证 $n \equiv 1 \pmod 2$|
|$4$|$30$|$10^6$|无|

## 样例 #1

### 输入

```
4```

### 输出

```
1 4 2 3```

# AI分析结果

• **综合分析与结论**：这些题解主要围绕构造一个1到n的排列，使相邻两项和的最大值与最小值之差最小展开。多数题解通过打表找规律，对n的奇偶性分类讨论。部分题解从理论分析入手，证明差值最小为2，并据此构造排列。思路和方法各有特点，质量参差不齐。
• **所选的题解**：
  - **作者：Defy_HeavenS (5星)**
    - **关键亮点**：思路清晰，对n的奇偶性分别详细分析并给出构造规律，代码简洁明了，可读性高。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000005];
int main(){
    cin>>n;
    if(n%2==0){
        for(int i=2,j=n-1;i<=n/2;i+=2,j-=2){
            a[i]=j;
            a[n-i+1]=n+1-j;
        }
        for(int i=1;i<=n;i++){
            if(!a[i]){
                cout<<i<<" ";
            }else{
                cout<<a[i]<<" ";
            }
        }
    }else{
        a[1]=1;
        for(int i=3,j=2;i<=n;i+=2,j+=2){
            a[i]=j;
        }
        for(int i=2,j=n;i<=n;i+=2,j-=2){
            a[i]=j;
        }
        for(int i=1;i<=n;i++){
            cout<<a[i]<<" ";
        }
    }
    return 0;
}
```
    - **核心思想**：偶数时，通过循环给数组特定下标赋值，构造出符合规律的排列；奇数时，同样利用循环分别给奇数、偶数下标赋值，最后输出排列。
  - **作者：wangif424 (4星)**
    - **关键亮点**：先深入分析最小极差不可能为0和1，只能为2，再基于此通过考虑相邻两数和的取值及合法性构造排列，分析过程有深度。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
#define R(x) x = read()
#define ENDL putchar('\n');
#define SPACE putchar(' ');
#define akioi register
#define int long long
using namespace std;
inline void P(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) {
        P(x / 10);
        x %= 10;
    }
    putchar(x ^ '0');
}
inline int read() {
    register int r=0,f=1;
    register char c=getchar();
    while(c>'9'||c<'0') {
        if(c=='-')f=0;
        c=getchar();
    }
    while(c>='0'&&c<='9') {
        r=(r<<3)+(r>>1)+(c^'0');
        c=getchar();
    }
    return f?(-r):r;
}
int n;
int vis[1000100];
signed main() {
    R(n);
    int p=1;
    P(p);
    SPACE
    vis[1]=1;
    for(int i=2; i<=n; i++) {
        p=n-p;
        if(vis[p]) {
            p+=2;
            if(vis[p]||p>n)p--;
        }
        vis[p]=1;
        P(p);
        SPACE
    }
    return 0;
}
```
    - **核心思想**：先确定第一个数，之后根据相邻两数和为n、n + 1、n + 2三种情况，结合数字是否已使用判断下一个数的取值并构造排列。
  - **作者：maomao233 (4星)**
    - **关键亮点**：从平均值角度出发，先尝试按和为n + 1构造发现会重复，进而调整为和在[n, n + 2]区间构造，详细阐述构造过程及遇到的问题和解决办法。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T>inline void rd(T &x){x=0;char c=getchar();bool f=0;while(!isdigit(c)){if(c=='-'){f=1;}c=getchar();}while(isdigit(c)){x=(x<<3)+(x<<1)+(c^'0');c=getchar();}if(f){x=~(x-1);}}
template<typename T,typename...Args>inline void rd(T &x,Args&...args){rd(x);rd(args...);}
inline void wt(int x){if(x<0){putchar('-'),x=-x;}if(x>9){wt(x/10);}putchar(x%10+'0');}
#define pc(x) putchar(x)
#define wtl(x) wt(x),pc('\n')
#define kg pc(' ')
#define hh pc('\n')
bool a[1000010];
int ans[1000010];
signed main()
{
    int n;
    rd(n);
    wt(1),kg,a[1]=ans[1]=1;
    for(int i=2;i<=n;i++)
    {
        int flag=0;
        if(!a[n-ans[i-1]]&&(i==2||(i>=3&&ans[i-1]+ans[i-2]==(n+2))))
        {
            int x=n-ans[i-1];
            a[x]=1,ans[i]=x,flag=1;
        }
        else if(!a[(n+1)-ans[i-1]]&&(i==2||(i>=3&&ans[i-1]+ans[i-2]==(n+1))))
        {
            int x=(n+1)-ans[i-1];
            a[x]=1,ans[i]=x,flag=1;
        }
        else if(!a[(n+2)-ans[i-1]]&&(i==2||(i>=3&&ans[i-1]+ans[i-2]==n)))
        {
            int x=(n+2)-ans[i-1];
            a[x]=1,ans[i]=x,flag=1;
        }
        else
        {
            if(!flag)
            {
                if(!a[n-ans[i-1]])
                {
                    int x=n-ans[i-1];
                    a[x]=1,ans[i]=x,flag=1;
                }
                else if(!a[(n+1)-ans[i-1]])
                {
                    int x=(n+1)-ans[i-1];
                    a[x]=1,ans[i]=x,flag=1;
                }
                else if(!a[(n+2)-ans[i-1]])
                {
                    int x=(n+2)-ans[i-1];
                    a[x]=1,ans[i]=x,flag=1;
                }
            }
            else
            {
                break;
            }
        }
    }
    for(int i=2;i<=n;i++)
    {
        wt(ans[i]),kg;
    }
    hh;
    return 0;
}
```
    - **核心思想**：先确定第一个数为1，之后根据上一次相邻两数和的情况，优先按“平均”原则选择下一个数，若不满足则按和为n、n + 1、n + 2的顺序选择未使用的数构造排列。
• **最优关键思路或技巧**：通过打表找规律，对n的奇偶性分类讨论来构造排列。从理论上分析出相邻两项和的极差最小为2，并围绕此构造满足条件的排列。在构造过程中，利用数字和的关系及已使用数字的标记来确定下一个数字。
• **可拓展之处**：此类构造题可拓展到其他类似的对序列元素关系有特定要求的题目，例如对相邻元素乘积、差值等进行最值限制的构造问题。解题套路通常是先通过小数据找规律，再从理论上分析可行性，最后根据规律和分析进行构造。
• **推荐题目**：
  - **P1149 火柴棒等式**：通过构造不同数字的火柴棒表示，找出满足等式的组合，与本题类似在构造中寻找满足特定条件的组合。
  - **P1433 吃奶酪**：需要构造遍历奶酪的顺序，使总路程最小，同样是构造满足最优条件的序列问题。
  - **P2678 [NOIP2015 提高组] 跳石头**：通过构造石头移除方案，满足跳跃距离的最小值最大，和本题构造排列满足特定差值最小思路类似。
• **个人心得摘录**：
  - **作者：include13_fAKe**：这是作者在赛事中独立完成的Div.2B题目，通过该题在洛谷月赛Div.2首次进全网前10%且得分超过230，特以此篇题解纪念。总结为通过本题提升了自身竞赛成绩，具有纪念意义。 

---
处理用时：53.75秒