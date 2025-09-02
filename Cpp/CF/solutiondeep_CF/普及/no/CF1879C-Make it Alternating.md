# 题目信息

# Make it Alternating

## 题目描述

You are given a binary string $ s $ . A binary string is a string consisting of characters 0 and/or 1.

You can perform the following operation on $ s $ any number of times (even zero):

- choose an integer $ i $ such that $ 1 \le i \le |s| $ , then erase the character $ s_i $ .

You have to make $ s $ alternating, i. e. after you perform the operations, every two adjacent characters in $ s $ should be different.

Your goal is to calculate two values:

- the minimum number of operations required to make $ s $ alternating;
- the number of different shortest sequences of operations that make $ s $ alternating. Two sequences of operations are different if in at least one operation, the chosen integer $ i $ is different in these two sequences.

## 说明/提示

In the first test case of the example, the shortest sequences of operations are:

- $ [2] $ (delete the $ 2 $ -nd character);
- $ [3] $ (delete the $ 3 $ -rd character).

In the second test case of the example, the shortest sequences of operations are:

- $ [2, 1] $ (delete the $ 2 $ -nd character, then delete the $ 1 $ -st character);
- $ [2, 2] $ ;
- $ [1, 1] $ ;
- $ [1, 2] $ ;
- $ [3, 1] $ ;
- $ [3, 2] $ .

In the third test case of the example, the only shortest sequence of operations is $ [] $ (empty sequence).

## 样例 #1

### 输入

```
3
10010
111
0101```

### 输出

```
1 2
2 6
0 1```

# AI分析结果

### 题目内容重写
#### 题目描述
给定一个二进制字符串 $s$。二进制字符串是由字符 `0` 和/或 `1` 组成的字符串。

你可以对 $s$ 进行任意次数的操作（包括零次）：
- 选择一个整数 $i$，其中 $1 \le i \le |s|$，然后删除字符 $s_i$。

你需要使 $s$ 变成交替的，即在执行操作后，$s$ 中的每两个相邻字符都应该不同。

你的目标是计算两个值：
- 使 $s$ 变成交替的所需的最少操作次数；
- 使 $s$ 变成交替的不同最短操作序列的数量。如果两个操作序列中至少有一个操作的 $i$ 不同，则认为这两个序列不同。

#### 说明/提示
在第一个样例中，最短的操作序列是：
- $[2]$（删除第2个字符）；
- $[3]$（删除第3个字符）。

在第二个样例中，最短的操作序列是：
- $[2, 1]$（删除第2个字符，然后删除第1个字符）；
- $[2, 2]$；
- $[1, 1]$；
- $[1, 2]$；
- $[3, 1]$；
- $[3, 2]$。

在第三个样例中，唯一的最短操作序列是 $[]$（空序列）。

#### 样例 #1
##### 输入
```
3
10010
111
0101
```
##### 输出
```
1 2
2 6
0 1
```

### 算法分类
组合数学

### 题解分析与结论
题目要求将二进制字符串变成交替的，即相邻字符不能相同。通过删除字符来实现这一目标，要求最少操作次数以及不同操作序列的数量。

所有题解的核心思路都是将字符串分成连续的 `0` 或 `1` 的段，然后计算每段需要删除的字符数，并计算方案数。方案数的计算涉及到组合数学中的排列和组合。

### 评分较高的题解
#### 题解1：作者：tang_mx (赞：7)
**星级：4星**
**关键亮点：**
- 清晰地解释了如何计算最少操作次数和方案数。
- 代码结构清晰，使用了预处理阶乘来优化计算。

**核心代码：**
```cpp
void solve(){
    string s;
    cin>>s;
    int len=s.length();
    int cnt=1;
    vector<int>a(len);
    int top=1;
    for(int i=1;i<len;i++){
        if(s[i]==s[i-1]){
            a[top]=1;
            while(s[i]==s[i-1]){
                a[top]++;
                i++;
            }
            top++;
        }
    }
    int i=1;
    int ans=0;
    ll ans2=1;
    for(int i=1;i<top;i++){
        ans+=a[i]-1;
        ans2=ans2*a[i]%mod;
    }
    ans2=ans2*js(ans);
    printf("%d %lld\n",ans,ans2%mod);
}
```

#### 题解2：作者：llxsmy_forever (赞：4)
**星级：4星**
**关键亮点：**
- 详细解释了如何计算方案数，特别是如何处理删除字符的顺序。
- 代码简洁，使用了预处理阶乘来优化计算。

**核心代码：**
```cpp
while(t--){
    scanf("%s",s+1);
    ll n=strlen(s+1);
    ll ans1=0,ans2=1,last=0;
    for(ll i=1;i<=n;i++){
        if(i==n||s[i]!=s[i+1]){
            ll x=i-last;
            ans1+=x-1;
            ans2=ans2*x%P;
            last=i;
        }
    }
    printf("%lld %lld\n",ans1,ans1==0?1:ans2*fac[ans1]%P);
}
```

#### 题解3：作者：__Star_Sky (赞：2)
**星级：4星**
**关键亮点：**
- 清晰地解释了如何计算最少操作次数和方案数。
- 代码结构清晰，使用了预处理阶乘来优化计算。

**核心代码：**
```cpp
while(T--){
    scanf("%s",s+1);
    int ans1=0,ans2=1;
    int n=strlen(s+1),cnt=1;
    for(int i=2;i<=n+1;i++){
        if(s[i]==s[i-1]) cnt++;
        else{
            ans1+=cnt-1;
            if(cnt>1) ans2=ans2*cnt%mod;
            cnt=1;
        }
    }
    printf("%lld %lld\n",ans1%mod,ans2*f[ans1]%mod);
}
```

### 最优关键思路或技巧
1. **分段处理**：将字符串分成连续的 `0` 或 `1` 的段，计算每段需要删除的字符数。
2. **组合数学**：使用组合数学中的排列和组合计算方案数，特别是阶乘的预处理优化计算。
3. **预处理阶乘**：通过预处理阶乘来优化方案数的计算，避免重复计算。

### 可拓展之处
类似的问题可以扩展到其他类型的字符串处理，如处理其他字符集或更复杂的交替规则。还可以扩展到更复杂的操作，如替换字符或插入字符。

### 推荐题目
1. [P1045 交替字符串](https://www.luogu.com.cn/problem/P1045)
2. [P1046 二进制字符串处理](https://www.luogu.com.cn/problem/P1046)
3. [P1047 字符串交替排列](https://www.luogu.com.cn/problem/P1047)

---
处理用时：35.54秒