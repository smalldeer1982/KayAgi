# 题目信息

# Maximum Cost Deletion

## 题目描述

You are given a string $ s $ of length $ n $ consisting only of the characters 0 and 1.

You perform the following operation until the string becomes empty: choose some consecutive substring of equal characters, erase it from the string and glue the remaining two parts together (any of them can be empty) in the same order. For example, if you erase the substring 111 from the string 111110, you will get the string 110. When you delete a substring of length $ l $ , you get $ a \cdot l + b $ points.

Your task is to calculate the maximum number of points that you can score in total, if you have to make the given string empty.

## 说明/提示

In the first example, it is enough to delete the entire string, then we will get $ 2 \cdot 3 + 0 = 6 $ points.

In the second example, if we delete characters one by one, then for each deleted character we will get $ (-2) \cdot 1 + 5 = 3 $ points, i. e. $ 15 $ points in total.

In the third example, we can delete the substring 00 from the string 100111, we get $ 1 \cdot 2 + (-4) = -2 $ points, and the string will be equal to 1111, removing it entirely we get $ 1 \cdot 4 + (-4) = 0 $ points. In total, we got $ -2 $ points for $ 2 $ operations.

## 样例 #1

### 输入

```
3
3 2 0
000
5 -2 5
11001
6 1 -4
100111```

### 输出

```
6
15
-2```

# AI分析结果

### 题目内容
# 最大花费删除

## 题目描述
给定一个长度为 $n$ 的字符串 $s$，该字符串仅由字符 0 和 1 组成。

你执行以下操作，直到字符串为空：选择一些连续的相同字符子串，将其从字符串中删除，并按相同顺序将剩余的两部分（其中任何一部分都可以为空）连接在一起。例如，如果你从字符串 111110 中删除子串 111，你将得到字符串 110。当你删除长度为 $l$ 的子串时，你将获得 $a \cdot l + b$ 分。

你的任务是计算在必须使给定字符串为空的情况下，你总共可以获得的最大分数。

## 说明/提示
在第一个示例中，删除整个字符串就足够了，然后我们将得到 $2 \cdot 3 + 0 = 6$ 分。

在第二个示例中，如果我们逐个删除字符，那么对于每个删除的字符，我们将得到 $(-2) \cdot 1 + 5 = 3$ 分，即总共 15 分。

在第三个示例中，我们可以从字符串 100111 中删除子串 00，我们得到 $1 \cdot 2 + (-4) = -2$ 分，并且字符串将变为 1111，完全删除它我们得到 $1 \cdot 4 + (-4) = 0$ 分。总共，我们通过 2 次操作得到了 -2 分。

## 样例 #1
### 输入
```
3
3 2 0
000
5 -2 5
11001
6 1 -4
100111
```
### 输出
```
6
15
-2
```

### 算法分类
贪心

### 综合分析与结论
所有题解的核心思路都是基于贪心策略。首先明确无论如何删除，$a$ 对总分数的贡献恒为 $a \times n$，因此影响总分数的关键在于 $b$。各题解针对 $b$ 的不同取值情况进行讨论：
 - 当 $b \geq 0$ 时，为使总分数最大，应尽可能增加删除次数，即每次删除单个字符，此时总分数为 $(a + b) \times n$。
 - 当 $b < 0$ 时，为使总分数最大，应尽可能减少删除次数。通过统计连续相同字符子串的数量，将其视为 01 交错的序列，取 0 串和 1 串数量中的较小值 $m$，再加上最后一次删除剩余字符的操作，总操作次数为 $m + 1$，此时总分数为 $a \times n + b \times (m + 1)$。

各题解在实现细节上略有差异，但整体思路一致，主要区别在于统计连续相同字符子串数量的方式不同。

### 所选的题解
#### 作者：tongzhenxuan (5星)
 - **关键亮点**：思路清晰，先从理论上推导总费用与 $a$、$b$ 的关系，再分情况详细讨论，代码简洁明了。
 - **核心代码**：
```cpp
#include<bits/stdc++.h>
using namespace std;
char ch[10000];
int n,m;
int a,b;
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n>>a>>b;
        cin>>ch;
        if(b>=0) cout<<a*n+b*n<<"\n";
        else if(b<0)
        {
            int l=1;
            for(int i=1;i<n;i++) if(ch[i]!=ch[i-1]) l++;
            cout<<a*n+b*(l/2+1)<<"\n";
        }
    }
    return 0; 
} 
```
 - **核心实现思想**：输入数据后，根据 $b$ 的值分情况计算最大得分。$b \geq 0$ 时，直接输出 $a \times n + b \times n$；$b < 0$ 时，通过遍历字符串统计连续字符变化次数得到 $l$，进而计算得分。

#### 作者：wheneveright (5星)
 - **关键亮点**：对题意理解准确，分析过程简洁易懂，代码实现逻辑清晰。
 - **核心代码**：
```cpp
# include <bits/stdc++.h>
using namespace std;

int T, N, A, B, res;
char s[105];

int main () {
    cin >> T;
    while (T--) {
        cin >> N >> A >> B >> s + 1;
        if (B < 0) {
            int cnt = 0; res = A * N;
            for (int i = 1; i <= N; i++) {
                cnt++;
                while (s[i + 1] == s[i] && i + 1 <= N) i++;
            }
            cout << A * N + (cnt / 2 + 1) * B << endl;
        }
        else cout << (A + B) * N << endl;
    }
    return 0;
}
```
 - **核心实现思想**：循环处理每组数据，根据 $B$ 的正负判断。$B < 0$ 时，遍历字符串统计连续相同字符子串数量 $cnt$，计算得分；$B \geq 0$ 时，直接输出 $(A + B) \times N$。

#### 作者：KSToki (5星)
 - **关键亮点**：分析过程详细，对 $b$ 不同取值下的操作策略阐述清晰，代码注释丰富。
 - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (1e9)
#define INF (1e18)
#define eps (1e-8)
I int read()
{
    char ch=getchar();
    int res=0,flag=1;
    while(ch<'0'||ch>'9')
    {
        if(ch=='-')
            flag=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
    {
        res=res*10+ch-'0';
        ch=getchar();
    }
    return res*flag;
}
int T,n,a,b,s[101],f[101][101]; 
int main()
{
    T=read();
    while(T--)
    {
        n=read();
        a=read();
        b=read();
        for(R int i=1;i<=n;++i)
            scanf("%1d",&s[i]);
        if(b>0)
            putint(n*(a+b));
        else
        {
            int lst=1,cnt=1;
            for(R int i=2;i<=n;++i)
                if(s[i]!=s[lst])
                {
                    lst=i;
                    ++cnt;
                }
            putint(n*a+(cnt/2+1)*b);
        }
    }
    return 0;
}
```
 - **核心实现思想**：通过自定义的 `read` 函数读取数据，根据 $b$ 的值分情况计算。$b > 0$ 时输出 $n \times (a + b)$；$b \leq 0$ 时，遍历数组统计连续字符变化次数得到 $cnt$ 以计算得分。

### 最优关键思路或技巧
 - **思维方式**：通过分析得分公式 $a \cdot l + b$，利用乘法分配律得出 $a$ 的贡献固定为 $a \times n$，从而将问题简化为根据 $b$ 的取值讨论操作次数的贪心策略。
 - **代码实现技巧**：在统计连续相同字符子串数量时，不同题解采用了不同的遍历方式，但都巧妙利用了相邻字符是否相同来计数，以确定最优的删除次数。

### 拓展思路
同类型题目通常围绕字符串操作和得分最大化/最小化展开，类似套路是分析操作对得分各部分的影响，通过固定某些部分，对可变部分进行分类讨论并采用贪心策略。例如，可能会改变操作规则或得分公式，但核心思路仍是寻找最优操作顺序以达到得分目标。

### 推荐题目
 - [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据进行排序实现贪心策略，与本题根据条件分类讨论贪心的思路类似。
 - [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要分析游戏规则找到贪心策略，确定最优选择，锻炼贪心思维。
 - [P2123 皇后游戏](https://www.luogu.com.cn/problem/P2123)：通过对数据排序和贪心策略来解决问题，与本题在寻找最优解的思维方式上有相似之处。 

---
处理用时：61.71秒