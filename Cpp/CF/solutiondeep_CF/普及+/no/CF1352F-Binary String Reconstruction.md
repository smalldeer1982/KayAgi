# 题目信息

# Binary String Reconstruction

## 题目描述

For some binary string $ s $ (i.e. each character $ s_i $ is either '0' or '1'), all pairs of consecutive (adjacent) characters were written. In other words, all substrings of length $ 2 $ were written. For each pair (substring of length $ 2 $ ), the number of '1' (ones) in it was calculated.

You are given three numbers:

- $ n_0 $ — the number of such pairs of consecutive characters (substrings) where the number of ones equals $ 0 $ ;
- $ n_1 $ — the number of such pairs of consecutive characters (substrings) where the number of ones equals $ 1 $ ;
- $ n_2 $ — the number of such pairs of consecutive characters (substrings) where the number of ones equals $ 2 $ .

For example, for the string $ s= $ "1110011110", the following substrings would be written: "11", "11", "10", "00", "01", "11", "11", "11", "10". Thus, $ n_0=1 $ , $ n_1=3 $ , $ n_2=5 $ .

Your task is to restore any suitable binary string $ s $ from the given values $ n_0, n_1, n_2 $ . It is guaranteed that at least one of the numbers $ n_0, n_1, n_2 $ is greater than $ 0 $ . Also, it is guaranteed that a solution exists.

## 样例 #1

### 输入

```
7
1 3 5
1 1 1
3 9 3
0 1 0
3 1 2
0 0 3
2 0 0```

### 输出

```
1110011110
0011
0110001100101011
10
0000111
1111
000```

# AI分析结果

### 题目内容（中文重写）
# 二进制字符串重构

## 题目描述
对于某个二进制字符串 $s$（即每个字符 $s_i$ 要么是 '0' 要么是 '1'），会写出所有相邻（连续）字符对。换句话说，会写出所有长度为 $2$ 的子串。对于每一对（长度为 $2$ 的子串），计算其中 '1' 的数量。

给定三个数字：
- $n_0$ — 相邻字符对（子串）中 '1' 的数量等于 $0$ 的对数；
- $n_1$ — 相邻字符对（子串）中 '1' 的数量等于 $1$ 的对数；
- $n_2$ — 相邻字符对（子串）中 '1' 的数量等于 $2$ 的对数。

例如，对于字符串 $s =$ "1110011110"，会写出以下子串："11"、"11"、"10"、"00"、"01"、"11"、"11"、"11"、"10"。因此，$n_0 = 1$，$n_1 = 3$，$n_2 = 5$。

你的任务是根据给定的值 $n_0$、$n_1$、$n_2$ 还原出任意一个合适的二进制字符串 $s$。保证 $n_0$、$n_1$、$n_2$ 中至少有一个数字大于 $0$。同时，保证存在解。

## 样例 #1
### 输入
```
7
1 3 5
1 1 1
3 9 3
0 1 0
3 1 2
0 0 3
2 0 0
```

### 输出
```
1110011110
0011
0110001100101011
10
0000111
1111
000
```

### 算法分类
构造

### 综合分析与结论
这些题解主要围绕根据给定的 $n_0$、$n_1$、$n_2$ 构造出符合条件的二进制字符串展开。大部分题解采用分类讨论的方法，以 $n_1$ 是否为 $0$ 作为关键分类点。当 $n_1 = 0$ 时，$n_0$ 和 $n_2$ 必然有一个为 $0$，可直接构造全 $0$ 或全 $1$ 的字符串；当 $n_1 \neq 0$ 时，先构造 $n_0 + 1$ 个 $0$ 和 $n_2 + 1$ 个 $1$，此时已产生一组和为 $1$ 的相邻字符对，再对剩下的 $n_1 - 1$ 个和为 $1$ 的组按 $0 - 1$ 交替的顺序构造。部分题解使用搜索的方法，通过深度优先搜索（DFS）逐步构造字符串，在构造过程中进行剪枝以提高效率。

### 所选题解
- **作者：45dinо (赞：5)，4星**
    - **关键亮点**：思路简洁明了，代码实现简单，直接根据 $n_1$ 是否为 $0$ 进行分类构造，易于理解。
- **作者：registerGen (赞：2)，4星**
    - **关键亮点**：构造方法简洁，同样以 $n_1$ 是否为 $0$ 分类，代码逻辑清晰，可读性高。
- **作者：zxh923 (赞：0)，4星**
    - **关键亮点**：对 $1$ 是特殊情况的分析清晰，分类构造的思路明确，代码实现规范。

### 重点代码
#### 作者：45dinо
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n1,n2,n3;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d %d",&n1,&n2,&n3);
        if(n2==0)
        {
            if(n1)
                for(int i=1;i<=n1+1;i++)
                    cout<<0;
            else
                for(int i=1;i<=n3+1;i++)
                    cout<<1;
            cout<<endl;
            continue;
        }
        for(int i=1;i<=n1+1;i++)
            cout<<0;
        for(int i=1;i<=n3+1;i++)
            cout<<1;
        n2--;
        for(int i=1;i<=n2;i++)
            if(i&1)
                cout<<0;
            else
                cout<<1;
        cout<<endl;
    }
    return 0;
}
```
**核心实现思想**：先判断 $n_1$ 是否为 $0$，若为 $0$ 则根据 $n_0$ 和 $n_2$ 的情况直接输出全 $0$ 或全 $1$ 的字符串；若不为 $0$，先输出 $n_0 + 1$ 个 $0$ 和 $n_2 + 1$ 个 $1$，再对剩下的 $n_1 - 1$ 个和为 $1$ 的组按 $0 - 1$ 交替输出。

#### 作者：registerGen
```cpp
#include<bits/stdc++.h>

int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n0,n1,n2;
        scanf("%d%d%d",&n0,&n1,&n2);
        std::string ans="";
        if(n0==0&&n1==0)
        {
            for(int i=1;i<=n2+1;i++)ans+="1";
            goto OUTPUT;
        }
        if(n1==0&&n2==0)
        {
            for(int i=1;i<=n0+1;i++)ans+="0";
            goto OUTPUT;
        }
        if(n1>=1)
        {
            for(int i=1;i<=n0+1;i++)ans+="0";
            for(int i=1;i<=n2+1;i++)ans+="1";
            for(int i=1;i<=n1-1;i++)
            {
                if(i%2==1)ans+="0";
                else ans+="1";
            }
        }
OUTPUT:
        puts(ans.c_str());
    }
    return 0;
}
```
**核心实现思想**：同样先判断 $n_0$、$n_1$、$n_2$ 的情况，若 $n_0$ 和 $n_1$ 都为 $0$ 则输出 $n_2 + 1$ 个 $1$，若 $n_1$ 和 $n_2$ 都为 $0$ 则输出 $n_0 + 1$ 个 $0$，若 $n_1 \geq 1$ 则按顺序构造字符串。

#### 作者：zxh923
```cpp
#include<bits/stdc++.h> 
#define int long long
#define N 8005
using namespace std;
int t,n3,n1,n2;
signed main(){
    cin>>t;
    while(t--){
        cin>>n1>>n2>>n3;
        if(!n2){
            if(n1)for(int i=1;i<=n1+1;i++)cout<<"0";
            else for(int i=1;i<=n3+1;i++)cout<<"1";
            cout<<'\n';
        }
        else{
            for(int i=1;i<=n1+1;i++)cout<<"0";
            for(int i=1;i<=n3+1;i++)cout<<"1";
            for(int i=1;i<n2;i++){
                if(i&1)cout<<"0";
                else cout<<"1";
            }
            cout<<'\n';
        }
    }
    return 0;
}
```
**核心实现思想**：以 $n_1$ 是否为 $0$ 分类，$n_1 = 0$ 时根据 $n_0$ 和 $n_2$ 输出全 $0$ 或全 $1$ 字符串，$n_1 \neq 0$ 时按规则构造字符串。

### 最优关键思路或技巧
- **分类讨论**：以 $n_1$ 是否为 $0$ 作为分类依据，简化了构造过程。
- **特殊情况处理**：先处理 $n_1 = 0$ 的特殊情况，再处理一般情况，使逻辑更清晰。
- **顺序构造**：按 $0$、$1$ 的顺序依次构造，保证满足 $n_0$ 和 $n_2$ 的要求，再处理 $n_1$ 的情况。

### 可拓展之处
同类型题可能会改变字符串的字符集，或者改变相邻字符对的统计规则。类似算法套路主要是根据给定的条件进行分类讨论，逐步构造出满足条件的结果。

### 推荐洛谷题目
- P1098 字符串的展开
- P1217 [USACO1.5] 回文质数 Prime Palindromes
- P1308 统计单词数

### 个人心得
部分作者提到搜索构造虽然复杂度没有其他方法好，但更好理解，这提示我们在解题时可以根据自己的情况选择合适的方法，先以理解为首要目标，再考虑优化。 

---
处理用时：62.61秒