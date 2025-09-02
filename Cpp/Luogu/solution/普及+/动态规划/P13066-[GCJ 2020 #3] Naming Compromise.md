# [GCJ 2020 #3] Naming Compromise

## 题目描述

Cameron 和 Jamie 即将迎来他们的第二个孩子。他们在育儿方面已经配合得很好了，但此刻却在一个关键问题上产生了分歧！Cameron 想给孩子取名为 $\mathbf{C}$，而 Jamie 则想取名为 $\mathbf{J}$。

你希望帮助他们找到一个折中的名字，使其尽可能接近双方的想法。你认为可以通过**编辑距离**的概念来实现这一点。两个字符串 $S_1$ 和 $S_2$ 之间的编辑距离是指将 $S_1$ 转换为 $S_2$ 所需的最少操作次数，允许的操作包括：

* 在字符串任意位置插入一个字符。
* 删除字符串中的任意一个字符。
* 将字符串中的一个字符替换为其他任意字符。

例如，CAMERON 和 JAMIE 之间的编辑距离为 5。一种用 5 步完成转换的方式如下：CAMERON → JAMERON（替换）→ JAMIERON（插入）→ JAMIEON（删除）→ JAMIEN（删除）→ JAMIE（删除）。从 CAMERON 转换到 JAMIE 至少需要这么多操作。

为了使折中名字 $N$ 尽可能接近父母的原始意愿，你需要选择一个非空字符串 $N$，使得 $\mathbf{C}$ 与 $N$ 的编辑距离和 $\mathbf{J}$ 与 $N$ 的编辑距离之和最小。在所有满足这一条件的 $N$ 中，为了确保公平性，你还必须选择一个使得这两个编辑距离之差也尽可能小的 $N$。请为 Cameron 和 Jamie 找到一个折中名字。

## 说明/提示

**样例解释**

样例测试集 1 符合测试集 1 的限制。另一个不符合这些限制但可能出现在测试集 2 中的样例见下文。

在样例 #1 中，从 `XYZZY` 到 `ZZY` 的编辑距离为 2（删除前两个字母），从 `ZZYZX` 到 `ZZY` 的编辑距离为 2（删除最后两个字母）。`XZZX` 和 `ZYYZY` 也是可行的解。没有其他名字能使编辑距离之和小于 4。

例如，`ZY` 到 `C` 和 `J` 的编辑距离相同（均为 3），但编辑距离之和为 6，并非最小值，因此不是可接受的答案。

`XZZY` 也不符合要求。它到 `C` 和 `J` 的编辑距离分别为 1 和 3。虽然编辑距离之和是最小的，但两者之差（$|1-3| = 2$）并非最小，因为我们已经证明可以找到差值为 0 的解。

在样例 #2 中，`Y` 和 `Z` 是唯一可接受的答案。

在样例 #3 中，注意输入的长度限制不适用于输出，因此所示答案在任一测试集中均可接受。另一个可能的答案是 `YYXXY`。

在样例 #4 中，`XZXZXZ` 到 `ZYZX` 的编辑距离为 3，`YZ` 到 `ZYZX` 的编辑距离为 2。编辑距离之和为 5，差值为 1；这些值是该情况下的最优解。

**数据范围**

- $1 \leq T \leq 100$。
- $\mathbf{C} \neq \mathbf{J}$。

**测试集 1（4 分，可见判定）**

- $1 \leq \text{C 的长度} \leq 6$。
- $1 \leq \text{J 的长度} \leq 6$。
- $\mathbf{C}$ 的第 $i$ 个字母是大写 X、Y 或 Z。
- $\mathbf{J}$ 的第 $i$ 个字母是大写 X、Y 或 Z。

**测试集 2（8 分，隐藏判定）**

- $1 \leq \text{C 的长度} \leq 60$。
- $1 \leq \text{J 的长度} \leq 60$。
- $\mathbf{C}$ 的第 $i$ 个字母是大写英文字母。
- $\mathbf{J}$ 的第 $i$ 个字母是大写英文字母。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
XYZZY ZZYZX
Y Z
YYXXYZ ZYYXXY
XZXZXZ YZ```

### 输出

```
Case #1: ZZY
Case #2: Z
Case #3: ZYYXXYZ
Case #4: ZYZX```

## 样例 #2

### 输入

```
1
GCJ ABC```

### 输出

```
Case #1: GC```

# 题解

## 作者：RainySoul (赞：1)

记字符串 $A$ 到字符串 $B$ 的编辑距离为 $dis(A,B)$。

我们知道 $dis(A,B)+dis(B,C) \ge dis(A,C)$，当且仅当 $B$ 在 $A$ 到 $C$ 的编辑路径上时取等。

> 这非常显然，我用屁股都能想到。

那么回头看这个题，设答案串为 $S$，为了满足限制一：$dis(A,S)+dis(S,B)$ 最小。则 $S$ 在 $A$ 到 $B$ 的编辑路径上。

为了满足限制二：$\left | dis(A,S)-dis(S,B)\right |$ 最小。则 $S$ 是 $A$ 操作 $\frac{dis(A,B)}{2}$ 次得到的。

结合上面两个限制发现 $\text{dp}$ 出 $dis(A,B)$ 然后倒推方案就做完了。倒推方案就是记录转移路径，相信大家都会。

如果你不会求 $dis(A,B)$ 建议出门右转 [P2785](https://www.luogu.com.cn/problem/P2758)。

设计状态 $dp_{i,j}$ 表示串 $A$ 的前 $i$ 个字符转变成串 $B$ 的前 $j$ 个字符所需的最小花费。转移并不困难

$$dp_{i,j}=\min(dp_{i-1,j-1}+(a_i \ne b_j),dp_{i-1,j}+1,dp_{i,j-1}+1)$$

这里提一嘴几种转移对应的操作方式。

1. $dp_{i,j}=dp_{i-1,j}+1$ 是将串 $C$ 的第 $i$ 个删除。

2. $dp_{i,j}=dp_{i,j-1}+1$ 是将串 $J$ 的第 $j$ 个字符插入到串 $C$ 的第 $i$ 个字符前面。

3. $dp_{i,j}=dp_{i-1,j-1}+(a_i \ne b_j)$ 即当 $a_i \ne b_j$ 时将 $a_i$ 直接修改为 $b_j$；而 $a_i = b_j$ 时无需操作。

AC code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define inf 1e18
using namespace std;
string a,b;
int dp[1010][1010],path[1010][1010];
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int T,cnt=0;
    cin>>T;
    while(T--){
        cin>>a>>b;
        int lena=a.size(),lenb=b.size();
        for(int i=1;i<=lena;i++)
            for(int j=1;j<=lenb;j++)
                dp[i][j]=inf;
        for(int i=1;i<=lena;i++)dp[i][0]=i,path[i][0]=1;
        for(int i=1;i<=lenb;i++)dp[0][i]=i,path[0][i]=2;
        for(int i=1;i<=lena;i++){
            for(int j=1;j<=lenb;j++){
                int ta=dp[i-1][j-1]+(a[i-1]!=b[j-1]);
                int tb=dp[i-1][j]+1;
                int tc=dp[i][j-1]+1;
                int minn=min({ta,tb,tc});
                if(minn<dp[i][j]){
                    dp[i][j]=minn;
                    if(ta==minn){
                        if(a[i-1]!=b[j-1])path[i][j]=3;
                        else path[i][j]=4;
                    }
                    else if(tb==minn)path[i][j]=1;
                    else if(tc==minn)path[i][j]=2;
                }
            }
        }
        int ans=dp[lena][lenb];
        stack<int> v;
        while(!v.empty())v.pop();
        while(1){
            if(lena==0&&lenb==0)break;
            if(path[lena][lenb]==4){v.push(4),lena--,lenb--;}
            else if(path[lena][lenb]==3){v.push(3),lena--,lenb--;}
            else if(path[lena][lenb]==1){v.push(1),lena--;}
            else if(path[lena][lenb]==2){v.push(2),lenb--;}
        }
        int l=0,r=0;
        string s=a;
        for(int i=0;i<ans/2;i++){
            if(v.top()==1){
                string temp1="";
                for(int j=0;j<l;j++)temp1+=s[j];
                for(int j=l+1;j<(int)s.size();j++)temp1+=s[j];
                s=temp1;
            }
            else if(v.top()==2){
                string temp1="";
                for(int j=0;j<l;j++)temp1+=s[j];
                temp1+=b[r];
                for(int j=l;j<(int)s.size();j++)temp1+=s[j];
                s=temp1;
                r++;l++;
            }
            else if(v.top()==3)s[l]=b[r],l++,r++;
            else if(v.top()==4)i--,l++,r++;
            v.pop();
        }
        while(!v.empty())v.pop();
        cout<<"Case #"<<++cnt<<": "<<s<<'\n';
    }
    return 0;
}
```

---

