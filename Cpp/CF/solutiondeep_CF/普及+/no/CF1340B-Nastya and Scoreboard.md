# 题目信息

# Nastya and Scoreboard

## 题目描述

Denis, after buying flowers and sweets (you will learn about this story in the next task), went to a date with Nastya to ask her to become a couple. Now, they are sitting in the cafe and finally... Denis asks her to be together, but ... Nastya doesn't give any answer.

The poor boy was very upset because of that. He was so sad that he punched some kind of scoreboard with numbers. The numbers are displayed in the same way as on an electronic clock: each digit position consists of $ 7 $ segments, which can be turned on or off to display different numbers. The picture shows how all $ 10 $ decimal digits are displayed:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1340B/f1bf3e3ee1e01404b7c2f218b7a8b65c071d6967.png)After the punch, some segments stopped working, that is, some segments might stop glowing if they glowed earlier. But Denis remembered how many sticks were glowing and how many are glowing now. Denis broke exactly $ k $ segments and he knows which sticks are working now. Denis came up with the question: what is the maximum possible number that can appear on the board if you turn on exactly $ k $ sticks (which are off now)?

It is allowed that the number includes leading zeros.

## 说明/提示

In the first test, we are obliged to include all $ 7 $ sticks and get one $ 8 $ digit on the scoreboard.

In the second test, we have sticks turned on so that units are formed. For $ 5 $ of additionally included sticks, you can get the numbers $ 07 $ , $ 18 $ , $ 34 $ , $ 43 $ , $ 70 $ , $ 79 $ , $ 81 $ and $ 97 $ , of which we choose the maximum — $ 97 $ .

In the third test, it is impossible to turn on exactly $ 5 $ sticks so that a sequence of numbers appears on the scoreboard.

## 样例 #1

### 输入

```
1 7
0000000```

### 输出

```
8```

## 样例 #2

### 输入

```
2 5
0010010
0010010```

### 输出

```
97```

## 样例 #3

### 输入

```
3 5
0100001
1001001
1010011```

### 输出

```
-1```

# AI分析结果

### 题目中文重写
# Nastya和计分板

## 题目描述
Denis买了花和糖果（你将在下一个任务中了解这个故事）后，和Nastya约会，想请求她成为自己的恋人。现在，他们坐在咖啡馆里，最后……Denis向她表白，但Nastya没有给出任何回应。

可怜的男孩为此非常沮丧。他伤心到一拳打在了某个数字计分板上。这些数字的显示方式和电子时钟一样：每个数字位置由7个线段组成，这些线段可以打开或关闭以显示不同的数字。下图展示了所有10个十进制数字的显示方式：

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1340B/f1bf3e3ee1e01404b7c2f218b7a8b65c071d6967.png)
一拳打下去后，一些线段不工作了，也就是说，一些原本发光的线段可能不再发光。但Denis记得之前有多少根线段在发光，以及现在有多少根在发光。Denis正好弄坏了k个线段，并且他知道现在哪些线段还在工作。Denis想到了一个问题：如果正好打开k个现在不亮的线段，计分板上可能出现的最大数字是多少？

允许数字包含前导零。

## 说明/提示
在第一个测试中，我们必须打开所有7个线段，在计分板上得到一个数字8。

在第二个测试中，我们已经有一些线段亮着，形成了个位数字。再额外打开5个线段，可以得到数字07、18、34、43、70、79、81和97，我们选择其中最大的——97。

在第三个测试中，不可能正好打开5个线段，使计分板上出现一个数字序列。

## 样例 #1
### 输入
```
1 7
0000000
```
### 输出
```
8
```

## 样例 #2
### 输入
```
2 5
0010010
0010010
```
### 输出
```
97
```

## 样例 #3
### 输入
```
3 5
0100001
1001001
1010011
```
### 输出
```
-1
```

### 算法分类
贪心、动态规划

### 综合分析与结论
这些题解的核心思路都是结合贪心和动态规划来解决问题。先通过动态规划判断从第 $i$ 个数字到第 $n$ 个数字，点亮 $j$ 个荧光棒是否能构成合法数字，再利用贪心从高位到低位选择最大的可行数字。

- **思路对比**：
    - juicyyou 的题解直接定义 $dp_{i, j}$ 为从第 $i$ 个数到第 $n$ 个数，仅打开 $j$ 个荧光棒所能在第 $i$ 上得到的合法数字。
    - ZigZagKmp 的题解用 $dp(i,j)$ 表示 $i$ 到 $n$ 的灯组再点亮 $j$ 个是否能构成数字，然后在贪心过程中保证有解并让数字尽可能大。
    - Fairicle 的题解对每个位置预处理能转化的数字及需要点亮的数目，用 $f_{i,j}$ 表示在目前处理到第 $i$ 位，总共点亮了 $j$ 次的可行性。
    - YNH_QAQ 的题解用二维布尔动态规划 $dp_{i,j}$ 表示从 $i$ 到 $n$，只打开 $j$ 个位置的灯能否构成数字。

- **算法要点**：
    - 预处理每个数字需要点亮的线段数。
    - 利用动态规划判断可行性。
    - 从高位到低位贪心选择最大的可行数字。

- **解决难点**：
    - 直接贪心可能导致无解，通过动态规划判断可行性来避免。
    - 处理无解的情况，当 $dp_{1,k}$ 为 -1 或 0 时，输出 -1。

### 所选题解
- **juicyyou（5星）**：
    - **关键亮点**：思路清晰，代码实现规范，详细定义了动态规划的状态和转移方程。
- **ZigZagKmp（4星）**：
    - **关键亮点**：将输入转化为二进制处理，方便计算，对算法分析较为详细。
- **Fairicle（4星）**：
    - **关键亮点**：使用 vector 和 pair 存储能转化的数字及需要点亮的数目，代码结构清晰。

### 重点代码
#### juicyyou 的题解
```cpp
int cal(string s, int c){ // 计算需要打开的数量
    int cnt = 0;
    for(int i = 0;i < 7;i++){
        if(s[i] == '1' && num[c][i] == '0'){
            return -1;
        }
        if(s[i] != num[c][i]){
            cnt++;
        }
    }
    return cnt;
}
int main(){
    qread(n);
    qread(k);
    memset(dp, -1, sizeof(dp));
    for(int i = 1;i <= n;i++){
        cin >> s[i];
    }
    for(int i = n;i >= 1;i--){
        if(i == n){
            for(int j = 0;j < 10;j++){
                int op = cal(s[i], j);
                if(op == -1){
                    continue;
                }
                dp[n][op] = max(dp[n][op], j);
            }
        } else {
            for(int j = 0;j < 10;j++){
                int op = cal(s[i], j);
                if(op == -1){
                    continue;
                }
                for(int l = op;l <= k;l++){
                    if(dp[i + 1][l - op] != -1){
                        dp[i][l] = j;
                    }
                }
            }
        }
    }
    if(dp[1][k] == -1){
        puts("-1");
    } else {
        int now = k;
        bool f = 0;
        for(int i = 1;i <= n;i++){
            cout << dp[i][now];
            now -= cal(s[i], dp[i][now]);
        }
        puts("");
    }
    return 0;
}
```
**核心实现思想**：先定义 `cal` 函数计算将当前状态转化为数字 $c$ 需要打开的线段数。然后从后往前进行动态规划，更新 $dp$ 数组。最后根据 $dp$ 数组输出结果。

#### ZigZagKmp 的题解
```cpp
for(int i=1;i<=127;++i)siz[i]=siz[i-(i&(-i))]+1;
for(int i=1,x;i<=n;++i){
    for(int j=6;~j;--j){
        scanf("%1d",&x);
        if(x)a[i]|=(1<<j);
    }
    for(int j=0;j<10;++j){
        if((a[i]&nm[j])==a[i]){
            cst[i][j]=siz[nm[j]^a[i]];
        }
        else{
            cst[i][j]=-1;
        }
    }
}
//可行性dp
dp[n+1][0]=1;
for(int i=n;i;--i){
    for(int j=0;j<=m;++j){
        for(int k=0;k<10;++k){
            if(~cst[i][k]){
                if(j>=cst[i][k])dp[i][j]|=dp[i+1][j-cst[i][k]];
            }
        }
    }
}
//贪心
for(int i=1;i<=n;++i){
    int fl=-1;
    for(int k=9;~k;--k){
        if(cst[i][k]==-1)continue;
        if(dp[i+1][m-cst[i][k]]){
            fl=k;break;
        }
    }
    if(fl==-1){
        puts("-1");
        return 0;
    }
    printf("%d",fl);
    m-=cst[i][fl];
}
```
**核心实现思想**：先预处理每个数字的二进制表示和需要打开的线段数。然后进行可行性动态规划，判断从 $i$ 到 $n$ 的灯组再点亮 $j$ 个是否能构成数字。最后从高位到低位贪心选择最大的可行数字。

#### Fairicle 的题解
```cpp
for(ri i=1;i<=n;++i){
    scanf("%s",ch);
    for(ri j=9;j>=0;--j){
        int cnt=0,flg=0;
        for(ri k=0;k<7;++k){
            if(ch[k]==p[j][k]) continue;
            if(ch[k]=='1'){
                flg=1;
                break;
            }
            cnt++;
        }
        if(flg) continue;
        a[i].pb(make_pair(cnt,j));
    }
}//预处理
f[n+1][0]=1;
for(ri i=n;i>=1;--i){
    for(ri l=0;l<a[i].size();++l){
        for(int j=a[i][l].first;j<=k;j++){
            int w=a[i][l].first;
            f[i][j]|=f[i+1][j-w];
        }
    }
}//合法性判断
if(!f[1][k]){
    cout<<-1;
    return 0;
}
string ans="";
int cnt=k;
for(ri i=1;i<=n;++i){
    for(ri j=0;j<a[i].size();++j){
        int w=a[i][j].first;
        if(cnt<w) continue;
        if(f[i+1][cnt-w]){
            char ch=a[i][j].second+'0';
            ans=ans+ch;
            cnt-=w;
            break;
        }
    }
}//答案计算
cout<<ans;
```
**核心实现思想**：先预处理每个位置能转化的数字及需要点亮的数目，存储在 vector 中。然后进行合法性判断，利用动态规划更新 $f$ 数组。最后根据 $f$ 数组计算答案，从高位到低位贪心选择最大的可行数字。

### 最优关键思路或技巧
- 利用动态规划判断可行性，避免直接贪心导致无解。
- 从高位到低位贪心选择最大的可行数字，保证结果最大。
- 可以将输入转化为二进制处理，方便计算需要打开的线段数。

### 可拓展之处
同类型题或类似算法套路：
- 涉及到状态选择和可行性判断的问题，可以考虑使用动态规划和贪心结合的方法。
- 对于一些数字显示或状态变化的问题，可以将其转化为二进制或其他形式进行处理。

### 推荐题目
- [P1048 采药](https://www.luogu.com.cn/problem/P1048)：经典的 01 背包问题，与本题的动态规划思想类似。
- [P1216 [USACO1.5] 数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)：简单的动态规划题目，可练习动态规划的状态转移。
- [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)：完全背包问题，进一步巩固动态规划的应用。

### 个人心得
题解中未包含个人心得。

---
处理用时：77.31秒