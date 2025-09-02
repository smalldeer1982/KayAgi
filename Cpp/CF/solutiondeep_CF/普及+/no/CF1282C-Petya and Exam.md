# 题目信息

# Petya and Exam

## 题目描述

Petya has come to the math exam and wants to solve as many problems as possible. He prepared and carefully studied the rules by which the exam passes.

The exam consists of $ n $ problems that can be solved in $ T $ minutes. Thus, the exam begins at time $ 0 $ and ends at time $ T $ . Petya can leave the exam at any integer time from $ 0 $ to $ T $ , inclusive.

All problems are divided into two types:

- easy problems — Petya takes exactly $ a $ minutes to solve any easy problem;
- hard problems — Petya takes exactly $ b $ minutes ( $ b > a $ ) to solve any hard problem.

Thus, if Petya starts solving an easy problem at time $ x $ , then it will be solved at time $ x+a $ . Similarly, if at a time $ x $ Petya starts to solve a hard problem, then it will be solved at time $ x+b $ .

For every problem, Petya knows if it is easy or hard. Also, for each problem is determined time $ t_i $ ( $ 0 \le t_i \le T $ ) at which it will become mandatory (required). If Petya leaves the exam at time $ s $ and there is such a problem $ i $ that $ t_i \le s $ and he didn't solve it, then he will receive $ 0 $ points for the whole exam. Otherwise (i.e if he has solved all such problems for which $ t_i \le s $ ) he will receive a number of points equal to the number of solved problems. Note that leaving at time $ s $ Petya can have both "mandatory" and "non-mandatory" problems solved.

For example, if $ n=2 $ , $ T=5 $ , $ a=2 $ , $ b=3 $ , the first problem is hard and $ t_1=3 $ and the second problem is easy and $ t_2=2 $ . Then:

- if he leaves at time $ s=0 $ , then he will receive $ 0 $ points since he will not have time to solve any problems;
- if he leaves at time $ s=1 $ , he will receive $ 0 $ points since he will not have time to solve any problems;
- if he leaves at time $ s=2 $ , then he can get a $ 1 $ point by solving the problem with the number $ 2 $ (it must be solved in the range from $ 0 $ to $ 2 $ );
- if he leaves at time $ s=3 $ , then he will receive $ 0 $ points since at this moment both problems will be mandatory, but he will not be able to solve both of them;
- if he leaves at time $ s=4 $ , then he will receive $ 0 $ points since at this moment both problems will be mandatory, but he will not be able to solve both of them;
- if he leaves at time $ s=5 $ , then he can get $ 2 $ points by solving all problems.

Thus, the answer to this test is $ 2 $ .

Help Petya to determine the maximal number of points that he can receive, before leaving the exam.

## 样例 #1

### 输入

```
10
3 5 1 3
0 0 1
2 1 4
2 5 2 3
1 0
3 2
1 20 2 4
0
16
6 20 2 5
1 1 0 1 0 0
0 8 2 9 11 6
4 16 3 6
1 0 1 1
8 3 5 6
6 20 3 6
0 1 0 0 1 0
20 11 3 20 16 17
7 17 1 6
1 1 0 1 0 0 0
1 7 0 11 10 15 10
6 17 2 6
0 0 1 0 0 1
7 6 3 7 10 12
5 17 2 5
1 1 1 1 0
17 11 10 6 4
1 1 1 2
0
1
```

### 输出

```
3
2
1
0
1
4
0
1
2
1
```

# AI分析结果

### 题目翻译
# 彼佳和考试

## 题目描述
彼佳来参加数学考试，他想尽可能多地解决问题。他已经做好准备，并仔细研究了考试规则。

这场考试由 $n$ 道题目组成，考试时长为 $T$ 分钟。考试从时间 $0$ 开始，到时间 $T$ 结束。彼佳可以在从 $0$ 到 $T$（包含 $0$ 和 $T$）的任意整数时间点交卷。

所有题目分为两类：
- 简单题 —— 彼佳解决任何一道简单题恰好需要 $a$ 分钟；
- 难题 —— 彼佳解决任何一道难题恰好需要 $b$ 分钟（$b > a$）。

因此，如果彼佳在时间 $x$ 开始解决一道简单题，那么这道题将在时间 $x + a$ 被解决。同样，如果彼佳在时间 $x$ 开始解决一道难题，那么这道题将在时间 $x + b$ 被解决。

对于每一道题目，彼佳都知道它是简单题还是难题。此外，对于每一道题目，都确定了一个时间 $t_i$（$0 \leq t_i \leq T$），在这个时间点该题目将成为必答题。如果彼佳在时间 $s$ 交卷，并且存在这样一道题目 $i$，满足 $t_i \leq s$ 且他没有解决这道题，那么他将在整个考试中得到 $0$ 分。否则（即如果他已经解决了所有满足 $t_i \leq s$ 的题目），他将得到与他解决的题目数量相等的分数。注意，在时间 $s$ 交卷时，彼佳可能既解决了“必答题”，也解决了“非必答题”。

例如，如果 $n = 2$，$T = 5$，$a = 2$，$b = 3$，第一道题是难题且 $t_1 = 3$，第二道题是简单题且 $t_2 = 2$。那么：
- 如果他在时间 $s = 0$ 交卷，那么他将得到 $0$ 分，因为他没有时间解决任何题目；
- 如果他在时间 $s = 1$ 交卷，他将得到 $0$ 分，因为他没有时间解决任何题目；
- 如果他在时间 $s = 2$ 交卷，那么他可以通过解决编号为 $2$ 的题目得到 $1$ 分（这道题必须在从 $0$ 到 $2$ 的时间范围内解决）；
- 如果他在时间 $s = 3$ 交卷，那么他将得到 $0$ 分，因为在这个时刻两道题都将成为必答题，但他无法解决这两道题；
- 如果他在时间 $s = 4$ 交卷，那么他将得到 $0$ 分，因为在这个时刻两道题都将成为必答题，但他无法解决这两道题；
- 如果他在时间 $s = 5$ 交卷，那么他可以通过解决所有题目得到 $2$ 分。

因此，这个测试的答案是 $2$。

帮助彼佳确定他在交卷前可以获得的最大分数。

## 样例 #1
### 输入
```
10
3 5 1 3
0 0 1
2 1 4
2 5 2 3
1 0
3 2
1 20 2 4
0
16
6 20 2 5
1 1 0 1 0 0
0 8 2 9 11 6
4 16 3 6
1 0 1 1
8 3 5 6
6 20 3 6
0 1 0 0 1 0
20 11 3 20 16 17
7 17 1 6
1 1 0 1 0 0 0
1 7 0 11 10 15 10
6 17 2 6
0 0 1 0 0 1
7 6 3 7 10 12
5 17 2 5
1 1 1 1 0
17 11 10 6 4
1 1 1 2
0
1
```
### 输出
```
3
2
1
0
1
4
0
1
2
1
```

### 算法分类
贪心

### 综合分析与结论
这些题解的核心思路都是贪心算法，关键在于发现最佳交卷时间是 $t_i - 1$ 或 $T$，然后通过排序题目按时间顺序处理，优先完成必答题，再用剩余时间优先做简单题。

不同题解的实现细节略有差异，但整体思路一致。部分题解用结构体存储题目信息，部分用 `pair` 存储；在计算剩余时间可做题目数量时，有的考虑了简单题和难题，有的只考虑简单题。

### 所选题解
- **Erica_N_Contina（5星）**
  - **关键亮点**：思路清晰，代码注释详细，逻辑完整，对贪心过程的处理简洁明了。
- **liuyz11（4星）**
  - **关键亮点**：代码规范，使用了常见的编程模板，对时间点的处理和分数的计算逻辑清晰。
- **lucifer1004（4星）**
  - **关键亮点**：提供了 Python 代码，方便不同语言使用者参考，对时间点进行离散化处理，思路独特。

### 重点代码
#### Erica_N_Contina 的代码核心片段
```C++
struct node{
    int t,p;
}e[N];
// ...
sort(e+1,e+n+1,cmp);
int bit=0;//必做题用时 
for(int i=1;i<=n+1;i++){
    int tm=e[i].t-1;
    if(i==n+1)tm=T;
    if(i-1)bit+=e[i-1].p?b:a;
    if(i-1)cnt[e[i-1].p]--;
    if(tm>=bit){
        tm-=bit;
        int tpa=tm/a;
        tpa=min(tpa,cnt[0]);
        int tpb=(tm-tpa*a)/b;
        ans=max(ans,i-1+min(cnt[1],tpb)+tpa);
    }
}
```
**核心实现思想**：先对题目按必做时间排序，然后遍历每个时间点，计算必做题用时，判断是否有剩余时间，若有则优先做简单题，再做难题，更新最大得分。

#### liuyz11 的代码核心片段
```cpp
pii pro[MAXN];
// ...
sort(pro + 1, pro + n + 1);
int ans = 0, sta0 = 0, sta1 = 0;
rep(i, 1, n){
    if(sta0 > T) break;
    if(pro[i - 1].fi != pro[i].fi){
        int tim = pro[i].fi - 1;
        tim -= sta0;
        int res = sta1;
        if(tim >= 0){
            res += min(tim / a, tot0);
            tim -= min(tim / a, tot0) * a;
            res += min(tim / b, tot1);
            ans = max(ans, res);
        }
    }
    if(pro[i].se){
        tot1--;
        sta0 += b;
    }
    else{
        tot0--;
        sta0 += a;
    }
    sta1++;
}
```
**核心实现思想**：对题目按必做时间排序，遍历每个时间点，计算剩余时间，优先做简单题，再做难题，更新最大得分。

#### lucifer1004 的代码核心片段
```python
critical = set()
for ti in t:
    critical.add(ti)
    if ti >= 1:
        critical.add(ti - 1)
critical.add(T)
critical = list(critical)
critical.sort()
# ...
for i in range(k):
    mandatory_easy += easy[i]
    mandatory_hard += hard[i]
    time = critical[i] - mandatory_easy * a - mandatory_hard * b
    if time < 0:
        continue
    rest_easy = total_easy - mandatory_easy
    extra_easy = min(time // a, rest_easy)
    time -= extra_easy * a
    rest_hard = total_hard - mandatory_hard
    extra_hard = min(time // b, rest_hard)
    score = mandatory_easy + mandatory_hard + extra_easy + extra_hard
    ans = max(ans, score)
```
**核心实现思想**：对时间点进行离散化处理，遍历每个时间点，计算必做题用时和剩余时间，优先做简单题，再做难题，更新最大得分。

### 最优关键思路或技巧
- 贪心策略：发现最佳交卷时间是 $t_i - 1$ 或 $T$，优先完成必答题，再用剩余时间优先做简单题。
- 排序：对题目按必做时间排序，方便按时间顺序处理。

### 可拓展之处
同类型题目可能会有更多类型的题目，或者题目用时不是固定值，可使用类似的贪心思路，先确定关键时间点，再按顺序处理题目，优先完成必做任务，再用剩余资源完成其他任务。

### 推荐洛谷题目
1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
2. [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)

### 个人心得
- **ivyjiao**：提到“被 1800 杀了，丢人”，反映出在做该题时可能遇到困难，有一定的挫败感。 

---
处理用时：65.13秒