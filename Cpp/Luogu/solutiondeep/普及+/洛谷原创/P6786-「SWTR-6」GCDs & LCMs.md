# 题目信息

# 「SWTR-6」GCDs & LCMs

## 题目描述

小 A 有一个长度为 $n$ 的序列 $a_1,a_2,\cdots,a_n$。

他想从这些数中选出一些数 $b_1,b_2,\cdots,b_k$ 满足：对于所有 $i\ (1\leq i\leq k)$，$b_i$ 要么是序列 $b$ 中的最大值，要么存在一个位置 $j$ 使得 $b_j>b_i$ 且 $b_i+b_j+\gcd(b_i,b_j)=\mathrm{lcm}(b_i,b_j)$。

- 如果你不知道 $\gcd$ 和 $\mathrm{lcm}$ 是什么，可以点击最底部的「帮助/提示」部分的链接。

小 A 想让选出的数之和尽量大。请求出这个最大值。

## 说明/提示

**「样例 1 说明」**

可以选择 $b=\{2,3\}$，因为 $2+3+\gcd(2,3)=\mathrm{lcm}(2,3)$。

**「数据范围与约定」**

**本题采用捆绑测试。**

- Subtask 1（5 points）：$n\leq2$；
- Subtask 2（20 points）：$n\leq 17$；
- Subtask 3（15 points）：$a_i\leq 2\times 10^3$；
- Subtask 4（15 points）：$n\leq 2\times 10^3$；
- Subtask 5（10 points）：$n\leq 5\times 10^4$；
- Subtask 6（10 points）：$a_i\leq 10^7$；
- Subtask 7（25 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n\leq 3\times 10^5$，$1\leq a_i\leq 10^9$。

**「帮助/提示」**

$\gcd$ 表示[最大公约数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308?fr=aladdin)，$\mathrm{lcm}$ 表示[最小公倍数](https://baike.baidu.com/item/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B0/6192375?fr=aladdin)。

**「来源」**

[【LGR-075】洛谷 8 月月赛 II Div.2 & SWTR-06 & EZEC Round 3](https://www.luogu.com.cn/contest/33190)。

idea & solution & data by [Alex_Wei](https://www.luogu.com.cn/user/123294)。

## 样例 #1

### 输入

```
4
4 3 2 1```

### 输出

```
5```

## 样例 #2

### 输入

```
10
6 7 18 4 17 10 9 1 3 8```

### 输出

```
19```

## 样例 #3

### 输入

```
3
123456789 234567890 123456789```

### 输出

```
246913578```

# AI分析结果

• 综合分析与结论：这些题解主要围绕从给定序列中选出满足特定条件的子序列并求其最大和的问题。大部分题解先对条件\(b_i + b_j + \gcd(b_i,b_j)=\mathrm{lcm}(b_i,b_j)\)进行推导，得出若\(b_i < b_j\)，则\(b_i:b_j = 2:3\)的关键结论。基于此，常见思路是对原序列排序后，通过枚举最小值确定整个子序列，利用二分查找或map等方式查找序列中的数，计算满足条件子序列的和并取最大值。不同题解在实现细节和复杂度优化上有所差异。
• 所选的题解：
  - **作者：Alex_Wei (5星)**
    - **关键亮点**：作为官方题解，思路清晰全面，对各子任务分别阐述解法，从暴力到优化逐步深入，先证明关键结论，再针对不同数据范围给出相应算法，时间复杂度分析准确。
    - **重点代码核心思想**：利用map记录每个数出现的次数，排序后枚举每个数作为子序列起始，根据结论判断并累加满足条件的数的和，同时记录已计算的数防止重复计算。
```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int N=3e5+5;

map <int,int> mp;
int n,a[N]; ll ans;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i],mp[a[i]]++;
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        ll tmp=a[i],cnt=0;
        while(mp[tmp]){
            cnt+=tmp*mp[tmp],mp[tmp]=0;
            if(tmp%2==0)tmp=tmp/2*3;
            else break;
        }
        ans=max(ans,cnt);
    } cout<<ans<<endl;
    return 0;
}
```
  - **作者：Alarm5854 (4星)**
    - **关键亮点**：详细讲述比赛时的思考过程和各部分分的做法，从暴力枚举到图论方法，再到利用结论优化为\(O(n \log n)\)的算法，思路具有启发性，对不同解法的时间复杂度分析清晰。
    - **重点代码核心思想**：先对数组去重离散化并统计次数，利用`lower_bound`查找满足\(1.5\)倍关系的数并连边，通过拓扑排序计算以每个数结尾的最大数列之和。
  - **作者：Konnyaku_LXZ (4星)**
    - **关键亮点**：从数学推导入手得出关键结论，表述清晰，代码实现简洁明了，先排序合并相同元素并记录次数，通过二分查找满足\(2/3\)关系的元素更新答案。
    - **重点代码核心思想**：排序后处理相同元素，初始化\(f\)数组，遍历数组，对能整除3的元素二分查找其\(2/3\)的元素并更新\(f\)值和答案。
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cmath>
#include<stack>
using namespace std;

const int MAXN=5e5+50;
typedef long long LL;

LL N,a[MAXN],x[MAXN],t[MAXN],f[MAXN],cnt=0,Ans=0;

void Init(){
    scanf("%lld",&N);
    for(int i=1;i<=N;++i) scanf("%lld",&a[i]);
    sort(a+1,a+1+N);
    for(int i=1;i<=N;++i){
        if(a[i]==a[i-1]) ++t[cnt];
        else x[++cnt]=a[i],t[cnt]=1;
    }
    for(int i=1;i<=cnt;++i) f[i]=x[i]*t[i],Ans=max(Ans,f[i]);
}

void Solve(){
    for(int i=2;i<=cnt;++i){
        if(x[i]%3!=0) continue;
        LL val=x[i]/3*2;
        LL pos=lower_bound(x+1,x+i,val)-x;
        if(pos>=i||pos<1||val!=x[pos]) continue;
        f[i]+=f[pos];
        Ans=max(Ans,f[i]);
    }
}

void Print(){
    cout<<Ans<<endl;
}

int main()
{
    Init();
    Solve();
    Print(); 
    return 0;
}
```
• 最优关键思路或技巧：通过对给定条件进行数学推导得出关键结论，利用排序、二分查找或map等数据结构和算法优化，高效地解决问题。同时，在实现过程中注意避免重复计算以降低时间复杂度。
• 可拓展之处：同类型题常涉及数论知识与序列选择优化问题，类似套路是对给定条件进行数学化简，找到元素间的关系，再结合合适的数据结构和算法进行求解。
• 相似知识点洛谷题目：
  - [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)
  - [P2568 GCD](https://www.luogu.com.cn/problem/P2568)
  - [P1890  gcd区间查询](https://www.luogu.com.cn/problem/P1890)
• 个人心得摘录：部分作者提到通过打表找规律（如lndjy通过输出暴力结果观察规律），还有作者分享比赛时从部分分入手逐步思考优化的过程（如Alarm5854），这些方法在面对难题时有助于打开思路。 

---
处理用时：61.25秒