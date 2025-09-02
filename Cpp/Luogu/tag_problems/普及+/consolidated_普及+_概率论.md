---
title: "考试"
layout: "post"
diff: 普及+/提高
pid: P10514
tag: ['洛谷原创', 'O2优化', '概率论', '洛谷月赛']
---
# 考试
## 题目背景

人生有梦，各自精彩。
## 题目描述

有 $n$ 名同学去参加考试，考试有 $m$ 道题。

每个学生的实力是相同的，但是每道题的难度可能不同。第 $i$ 道题会有随机的 $a_i$ 名同学做错。

考试结束后，随机选出 $k$ 名同学，求出这些同学全部做对的概率。答案对 $998244353$ 取模。
## 输入格式

第一行三个整数 $n,m,k$。

第二行 $m$ 个整数，第 $i$ 个数表示 $a_i$。
## 输出格式

一个整数，表示答案取模后的结果。
## 样例

### 样例输入 #1
```
5 5 2
1 2 1 2 2
```
### 样例输出 #1
```
793364682
```
## 提示

**【样例解释】**

随机选出 $2$ 名同学全部做对的概率为 $\frac{243}{25000}$，对 $998244353$ 取模后答案为 $793364682$。

可以证明答案一定为有理数。若不了解有理数取模，可以参照[【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)。

**【数据范围】**

- 对于 $30\%$ 的数据，$1\leq n,m \leq 10$；
- 另外有 $10\%$ 的数据，$k=0$；
- 另外有 $20\%$ 的数据，$1 \leq n \leq 1000$，$1\leq m \leq 10^5$；

对于所有数据，保证 $1\leq n,m\leq 10^5$，$0\leq k,a_i\leq n$。


---

---
title: "Hash Killer II"
layout: "post"
diff: 普及+/提高
pid: P12198
tag: ['Special Judge', '哈希 hashing', '概率论']
---
# Hash Killer II
## 题目描述

这天天气不错，hzhwcmhf 神犇给 VFleaKing 出了一道题：

给你一个长度为 $n$ 的字符串 $s$，求有多少个不同的长度为 $l$ 的连续子串。

两个字符串被认为是不同的当且仅当某个位置上的字符不同。

VFleaKing 一看觉得这不是 Hash 的裸题么！于是果断写了哈希 + 排序。

而 hzhwcmhf 神犇心里自然知道，这题就是后缀数组的 height 中 $< l$ 的个数 +1，就是后缀自动机上代表的长度区间包含 $l$ 的结点个数，就是后缀树深度为 $l$ 的结点的数量。

但是 hzhwcmhf 神犇看了看 VFleaKing 的做法表示非常汗。于是想卡掉他。

VFleaKing 使用的是字典序哈希，其代码大致如下：

```cpp
u64 val = 0;
for (int i = 0; i < l; i++)
    val = (val * base + s[i] - 'a') % MOD;
```

u64 是无符号 int64，范围是 $[0, 2^{64})$。VFleaKing 让 val 自然溢出。

base 是一个常量，VFleaKing 会根据心情决定其值。

$\text{MOD}=10^9+7$

VFleaKing 还求出来了 $base^l \bmod \text{MOD}$，即 base 的 $l$ 次方除以 $\text{MOD}$ 的余数，这样就能方便地求出所有长度为 $l$ 的子串的哈希值。

然后 VFleaKing 给哈希值排序，去重，求出有多少个不同的哈希值，把这个数作为结果。

其算法的 C++ 代码如下:

```cpp
typedef unsigned long long u64;
const int MaxN = 100000;
inline int hash_handle(const char *s, const int &n, const int &l, const int &base)
{
    const int Mod = 1000000007;
    u64 hash_pow_l = 1;
    for (int i = 1; i <= l; i++)
        hash_pow_l = (hash_pow_l * base) % Mod;
    int li_n = 0;
    static int li[MaxN];
    u64 val = 0;
    for (int i = 0; i < l; i++)
        val = (val * base + s[i] - 'a') % Mod;
    li[li_n++] = val;
    for (int i = l; i < n; i++)
    {
        val = (val * base + s[i] - 'a') % Mod;
        val = (val + Mod - ((s[i - l] - 'a') * hash_pow_l) % Mod) % Mod;
        li[li_n++] = val;
    }
    sort(li, li + li_n);
    li_n = unique(li, li + li_n) - li;
    return li_n;
}

```

hzhwcmhf 当然知道怎么卡啦！但是他想考考你。
## 输出格式

你需要输出一组数据使得 VFleaKing 的代码 WA 掉。我们会使用 Special Judge 检查你的结果的正确性。

输出文件共两行。

第一行两个用空格隔开的数 $n, l$。

第二行是一个长度为 $n$ 的字符串。只能包含小写字母。

需要保证 $1 \le n \le 10^5, 1 \le l \le n$，不符合以上格式会 WA。不要有多余字符，很可能导致你 WA。
## 提示

本题的评分为：在 SPJ 中预设了 10 个 base 用作测试，每让一个 base 出现哈希冲突记 10 分，满分为 100 分。


---

---
title: "[国家集训队] 单选错位"
layout: "post"
diff: 普及+/提高
pid: P1297
tag: ['数学', '集训队互测', '概率论', '期望']
---
# [国家集训队] 单选错位
## 题目描述

gx 和 lc 去参加 noip 初赛，其中有一种题型叫单项选择题，顾名思义，只有一个选项是正确答案。

试卷上共有 $n$ 道单选题，第 $i$ 道单选题有 $a_i$ 个选项，这 $a_i$ 个选项编号是 $1,2,3,\ldots,a_i$，每个选项成为正确答案的概率都是相等的。

lc 采取的策略是每道题目随机写上 $1 \sim a_i$ 的某个数作为答案选项，他用不了多少时间就能期望做对 $\sum_{i=1}^n \frac{1}{a_i}$ 道题目。gx 则是认认真真地做完了这 $n$ 道题目，可是等他做完的时候时间也所剩无几了，于是他匆忙地把答案抄到答题纸上，没想到抄错位了：第 $i$ 道题目的答案抄到了答题纸上的第 $i+1$ 道题目的位置上，特别地，第 $n$ 道题目的答案抄到了第 $1$ 道题目的位置上。

现在 gx 已经走出考场没法改了，不过他还是想知道自己期望能做对几道题目，这样他就知道会不会被 lc 鄙视了。

我们假设 gx 没有做错任何题目，只是答案抄错位置了。

## 输入格式

$n$ 很大，为了避免读入耗时太多，输入文件只有 $5$ 个整数参数 $n, A, B, C, a_1$，由上交的程序产生数列 $a$。下面给出 pascal/C/C++ 的读入语句和产生序列的语句（默认从标准输入读入）：

```cpp
// for pascal
readln(n,A,B,C,q[1]);
for i:=2 to n do
q[i] := (int64(q[i-1]) * A + B) mod 100000001;
for i:=1 to n do
q[i] := q[i] mod C + 1;


// for C/C++
scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
for (int i = 2; i <= n; i++)
	a[i] = ((long long) a[i - 1] * A + B) % 100000001;
for (int i = 1; i <= n; i++)
	a[i] = a[i] % C + 1;
```

选手可以通过以上的程序语句得到 $n$ 和数列 $a$（$a$ 的元素类型是 $32$ 位整数），$n$ 和 $a$ 的含义见题目描述。

## 输出格式

输出一个实数，表示 gx 期望做对的题目个数，保留三位小数。

## 样例

### 样例输入 #1
```
3 2 0 4 1
```
### 样例输出 #1
```
1.167

```
## 提示

【样例说明】

| 正确答案   |   gx的答案    | 做对题目 | 出现概率 |
| :----------: | :----------: |:----------: | :----------: |
| $\{1,1,1\}$  |    $\{1,1,1\}$    |    $3$    |    $\frac16$ |
| $\{1,2,1\}$    |   $ \{1,1,2\}$   |    $1$    |    $\frac16$ |
|$\{1,3,1\}$    |   $ \{1,1,3\} $   |    $1$    |    $\frac16$ |
|$\{2,1,1\}$    |   $ \{1,2,1\} $   |    $1$    |    $\frac16$|
|$\{2,2,1\}$    |   $ \{1,2,2\}$    |    $1$    |    $\frac16$ |
|$\{2,3,1\}$    |    $\{1,2,3\} $   |    $0$    |    $\frac16$ |




$a = \{2,3,1\}$。

共有 $6$ 种情况，每种情况出现的概率是 $\frac{1}{6}$，gx 期望做对 $\frac{3+1+1+1+1+0}6 = \frac76$ 题。（相比之下，lc 随机就能期望做对 $\frac{11}6$ 题）



对于 $30\%$ 的数据，$n\leq 10, C\leq 10$。

对于 $80\%$ 的数据，$n\leq 10^4, C\leq 10$。

对于 $90\%$ 的数据，$n\leq 5\times 10^5, C\leq 10^8$。

对于 $100\%$ 的数据，$2\leq n\leq 10^7, 0\leq A,B,C \leq 10^8$，$1 \leq a_i \leq 10^8$。



---

---
title: "[GCJ 2020 #1C] Overrandomized"
layout: "post"
diff: 普及+/提高
pid: P13060
tag: ['数学', '2020', '概率论', 'Google Code Jam']
---
# [GCJ 2020 #1C] Overrandomized
## 题目描述

Note: Every time this statement says something is randomly chosen, it means "chosen uniformly at random across all valid possibilities, and independently from all other choices".

The company Banana Rocks Inc. just wrote a premium cloud-based random number generation service that is destined to be the new gold standard of randomness.

The original design was that a group of servers would receive a request in the form of a single positive integer M of up to $\mathbf{U}$ decimal digits and then respond with an integer from the range 1 through M, inclusive, chosen at random. However, instead of simply having the output written with digits 0 through 9 as usual, the servers were "overrandomized". Each server has a random subset of 10 distinct uppercase English letters to use as digits, and a random mapping from those letters to unique values between 0 and 9.

The formal description of the current situation is as follows: each server has a digit string D composed of exactly 10 different uppercase English letters. The digit string defines the mapping between letters and the base 10 digits: D's j-th character from the left (counting from 0) is the base 10 digit of value j. For example, if D were CODEJAMFUN then c would represent digit 0, o would represent digit 1 and n would represent digit 9. The number 379009 would be encoded as EFNCCN when using that digit string.

When receiving the i-th query with an integer parameter $M_i$, the server:

* chooses an integer $N_i$ at random from the inclusive range 1 through $M_i$,
* writes it as a base 10 string with no leading zeroes using the j-th character of D (counting starting from 0) as the digit of value j, and
* returns the resulting string as the response $R_i$.

We collected some data that we believe we can use to recover the secret digit string D from each server. We sent $10^4$ queries to each server. For each query, we chose a value $M_i$ at random from the range 1 through $10^{\mathbf{U}} - 1$, inclusive, and received the response $R_i$, a string of up to $\mathbf{U}$ uppercase English letters. We recorded the pairs $(M_i, R_i)$. As we were moving these records to a new data storage device, the values of all the integers $M_i$ within the records of some servers became corrupted and unreadable.

Can you help us find each server's digit string D?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow. Each test case contains the records for one server and starts with a line containing a single integer $\mathbf{U}$, representing that $10^{\mathbf{U}} - 1$ is the inclusive upper bound for the range in which we chose the integers $M_i$ to query that server. Then, exactly $10^4$ lines follow. Each of these lines contains an integer $\mathbf{Q}_i$ (in base 10 using digits 0 through 9, as usual) and a string $\mathbf{R}_i$, representing the i-th query and response, respectively. If $\mathbf{Q}_i = -1$, then the integer $M_i$ used for the i-th query is unknown. Otherwise, $\mathbf{Q}_i = M_i$.

## 输出格式

For each test case, output one line containing `Case #x: y`, where x is the test case number (starting from 1) and y is the digit string D for the server examined in test case x.
## 样例

### 样例输入 #1
```

```
### 样例输出 #1
```

```
## 提示

**Limits**

- $1 \leqslant \mathbf{T} \leqslant 10$.
- $\mathbf{D}$ is a string of exactly 10 different uppercase English letters, chosen independently and uniformly at random from the set of all such strings.
- $\mathbf{M}_i$ is chosen independently and uniformly at random from the range 1 through $10^{\mathbf{U}} - 1$, inclusive, for all i.
- $\mathbf{N}_i$ is chosen independently and uniformly at random from the range 1 through $\mathbf{M}_i$, inclusive, for all i.
- $\mathbf{R}_i$ is the base 10 representation of $\mathbf{N}_i$, using the j-th digit from the left of $\mathbf{D}$ (counting starting from 0) as the digit of value j, for all i.

**Test Set 1 (9 Pts, Visible Verdict)**

- $\mathbf{Q}_i = \mathbf{M}_i$, for all i.
- $\mathbf{U} = 2$.

**Test Set 2 (10 Pts, Visible Verdict)**

- $\mathbf{Q}_i = \mathbf{M}_i$, for all i.
- $\mathbf{U} = 16$.

**Test Set 3 (17 Pts, Visible Verdict)**

- $\mathbf{Q}_i = -1$, for all i.
- $\mathbf{U} = 16$.


---

---
title: "[GCJ 2018 #1C] Lollipop Shop"
layout: "post"
diff: 普及+/提高
pid: P13143
tag: ['数学', '2018', '交互题', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2018 #1C] Lollipop Shop
## 题目描述

You own a lollipop shop. At the start of the day, you make $N$ lollipops, each of a single unique flavor, like huckleberry, cherry or lime. $N$ customers come into the shop during the day, one at a time. Each customer gives you a list of which of your lollipop flavors they like. You can sell them one lollipop of any of those flavors, as long as you have not already sold someone else the same flavor earlier in the day (since there is only one lollipop of each flavor). If none of the flavors they like are still available, you cannot sell them a lollipop, and they leave your shop disappointed.

You do not know what each customer's flavor preferences are going to be until they arrive. Each customer decides if they like or dislike each flavor randomly, independently of whether they like any other flavor, or what flavors anyone else likes. However, your market studies have shown that some flavors may have a higher probability of being liked in general! For example, the lime flavor might have a $10\%$ chance of being liked by any particular customer, whereas that chance might be $1\%$ for the cherry flavor. These values are always chosen independently and uniformly at random from the interval $[0.005, 0.1]$.

Obviously, you want to sell lollipops to as many of the $N$ customers as possible! But, since you do not know what flavors your customers will ask for ahead of time, you cannot always make an optimal decision — sometimes you might sell a customer one flavor, and then later wish you had sold them another.

Suppose that you somehow knew all the customers' preferences in advance and could plan ahead; then there is some maximum number $M$ of lollipops that you could possibly sell. You do not know the customers' preferences in advance, but we require you to sell a number of lollipops that is at least $90\%$ of $M$ for each input case.

### Interactive Protocol

This problem is interactive, which means that the concepts of input and output are different than in standard Code Jam problems. You will interact with a separate process that both provides you with information and evaluates your responses. All information comes into your program via standard input; anything that you need to communicate should be sent via standard output. Remember that many programming languages buffer the output by default, so make sure your output actually goes out (for instance, by flushing the buffer) before blocking to wait for a response. See the FAQ for an explanation of what it means to flush the buffer. Anything your program sends through standard error is ignored, but it might consume some memory and be counted against your memory limit, so do not overflow it.

Initially, your program should read a single line containing a single integer $\mathbf{T}$ indicating the number of test cases. Then, you need to process $\mathbf{T}$ test cases.

For each test case, your program should read a single line with one integer $\mathbf{N}$, the number of lollipops (which is the same as the number of customers).

Then, for each of the customers, your program should read a single line, which will contain space-separated integers. The first integer is $\mathbf{D}$, the number of flavors that customer likes. Then, $\mathbf{D}$ integers follow, the ID numbers of those flavors, in strictly increasing order. Flavors have unique ID numbers in the range $[0, \mathbf{N} - 1]$. Note that $\mathbf{D}$ might be zero for some or all customers.

After each of these lines, your program must write a single line to standard output, containing the ID number of one of the $\mathbf{D}$ flavors to sell to the customer, or -1 if no lollipop is to be sold to the customer. After you have written the $\mathbf{N}$th line for the test case, your program should terminate if it was the last test case; otherwise, it should start reading data for the next test case.

If your program gets something wrong (e.g., tries to sell a customer a flavor that was already sold, or tries to sell a customer a flavor they don't like, or uses the wrong output format, or outputs an out-of-bounds value), the judge will send -1 to your input stream and it will not send any other output after that. If your program continues to wait for the judge after receiving -1, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive the appropriate verdict (Wrong Answer, Runtime Error, etc.) instead of a Time Limit Exceeded error. As usual, if the total time or memory is exceeded, or your program gets a runtime error, you will receive the appropriate verdict. Not selling enough lollipops for a test case will not cause you to get the -1 message.

You should not send additional information to the judge after processing all test cases. In other words, if your program keeps printing to standard output after the last test case, you will get a Wrong Answer judgment.
## 输入格式

See Interactive Protocol.
## 输出格式

See Interactive Protocol.
## 样例

### 样例输入 #1
```

```
### 样例输出 #1
```

```
## 提示

Note that this sample interaction has smaller values of $\mathbf T$ and $\mathbf N$ than the real data. The local testing tool also uses smaller cases.

```
  t = readline_int()           // reads 10 into t
  n = readline_int()           // reads 4 into n (four customers & flavors)
  prefs = readline_int_list()  // reads 1 2 (customer only likes flavor 2)
  printline 2 to stdout        // sells this customer flavor 2
  flush stdout
  prefs = readline_int_list()  // reads 0 (customer likes nothing)
  printline -1 to stdout       // no flavor to sell to the customer!
  flush stdout
  prefs = readline_int_list()  // reads 1 2 (customer only likes flavor 2)
  printline -1 to stdout       // already used flavor 2, so no flavor to sell
  flush stdout
  prefs = readline_int_list()  // reads 2 1 3 (customer likes 1 and 3)
  printline 3 to stdout        // note: we could have also sold flavor 1
  flush stdout
  n = readline_int()           // (start of case 2) reads 1
  prefs = readline_int_list()  // reads 1 0
  printline -1 to stdout       // non-optimal but legal choice
  flush stdout
  n = readline_int()           // (start of case 3) reads 5
  prefs = readline_int_list()  // reads 2 1 3
  printline 1 to stdout
  flush stdout
  prefs = readline_int_list()  // reads 2 1 2
  printline 1 to stdout        // error -- tried to give same flavor twice!
  flush stdout
  prefs = readline_int_list()  // reads -1 (judge has given up on us)
  exit                         // exits to avoid an ambiguous TLE error
```

The pseudocode above demonstrates the following scenario.

- In the first test case, the program sells a total of two lollipops. It would not have been possible to sell more than two, so the actual number sold is definitely at least 90% of the maximum possible number sold.
- In the second test case, the program chooses (for the sake of demonstration here) not to sell the customer a lollipop, although it could have. It sells a total of 0 when it could have sold a total of 1. So, the program will not pass this test set, but note that this does not cause the judge to stop sending input.
- In the third case, the program makes an error (again for the sake of demonstration) that causes the judge to stop sending input. The program recognizes this and terminates. The user will see a Wrong Answer judgment.

You can use this testing tool to test locally or on our platform. To test locally, you will need to run the tool in parallel with your code; you can use our [interactive runner](https://storage.googleapis.com/coding-competitions.appspot.com/interactive_runner.py) for that. For more information, read the instructions in comments in that file.

Instructions for the testing tool are included in comments within the tool. We encourage you to add your own test cases. Please be advised that although the testing tool is intended to simulate the judging system, it is **NOT** the real judging system and might behave differently.

**A note on judge behavior**

At the start of each test case, the judge will determine all customers' preferences. That is, it will use a (hidden) list of probabilities $P_i$ between 0.005 and 0.1, one for each flavor; each customer has a probability $P_i$ of liking the i-th flavor. That is, the random variables indicating whether customer j likes flavor i are independent and identically distributed. These preferences are constant throughout the test and will not be modified e.g. in response to your choices.

**Test set 1 (29 Pts, Visible)**

- $\mathbf{T} = 50.$
- $\mathbf{N} = 200.$
- $0 \leqslant \mathbf{D} \leqslant \mathbf{N}.$



---

---
title: "[GCJ 2016 #2] Red Tape Committee"
layout: "post"
diff: 普及+/提高
pid: P13199
tag: ['动态规划 DP', '2016', 'Special Judge', '概率论', 'Google Code Jam']
---
# [GCJ 2016 #2] Red Tape Committee
## 题目描述

You are the head of the Department of Redundancy Reduction and Superfluity Shrinkage. Currently, the department cannot agree on whether there is too much "red tape" (inefficiency) in the department itself. They have asked you to form a Red Tape Committee to vote on the issue.

The department has $\mathbf{N}$ members. For each member, you know the probability $\mathbf{P}_{\mathbf{i}}$ that that member will vote "Yes". If a member does not vote "Yes", they necessarily vote "No"; nobody abstains.

You must choose exactly $\mathbf{K}$ members to be on the committee. The department rules dictate that $\mathbf{K}$ must be an even number to allow for ties, which are seen as part of a healthy bureaucracy.

If you choose committee members to maximize the probability of a tie, what is that probability?
## 输入格式

The first line of the input gives the number of test cases, $\mathbf{T}$. $\mathbf{T}$ test cases follow; each consists of two lines. The first line of a test case consists of two integers $\mathbf{N}$ and $\mathbf{K}$, the sizes of the department and the committee. The second line of a test case consists of $\mathbf{N}$ decimal values $\mathbf{P}_{\mathbf{i}}$; each has exactly two decimal places of precision and represents the probability that the $i$-th department member will vote "Yes".

## 输出格式

For each test case, output one line containing `Case #x: y`, where $\mathrm{x}$ is the test case number (starting from 1) and $\mathrm{y}$ is a floating-point number: the maximum possible probability of a tie. $\mathrm{y}$ will be considered correct if it is within an absolute or relative error of $10^{-6}$ of the correct answer.
## 样例

### 样例输入 #1
```
3
2 2
0.50 0.50
4 2
0.00 0.00 1.00 1.00
3 2
0.75 1.00 0.50
```
### 样例输出 #1
```
Case #1: 0.5
Case #2: 1.0
Case #3: 0.5
```
## 提示

**Sample Explanation**

In sample case #1, you must use the only two available department members to form the committee. That committee will tie only if the two committee members vote differently, which will happen half the time. (Without loss of generality, choose the vote of the first. Then the probability that the second will vote the other way is $0.5$.)

In sample case #2, the best strategy is to pick one of the members with "Yes" probability $0.00$ and one of the members with "Yes" probability $1.00$. This guarantees a tie.

In sample case #3, suppose that we pick the two members with "Yes" probabilities of $0.50$ and $0.75$. A tie will happen if the first one votes "Yes" and the second one votes "No" (probability $0.5 \times 0.25 = 0.125$), or if the first one votes "No" and the second one votes "Yes" (probability $0.5 \times 0.75 = 0.375$). So the total probability of a tie is $0.125 + 0.375 = 0.5$. Choosing the two members with "Yes" probabilities of $0.50$ and $1.00$ would also make the tie probability $0.5$, since the $1.00$ member will vote "Yes" and the $0.50$ member must vote "No". Choosing the two members with "Yes" probabilities of $0.75$ and $1.00$ would make the tie probability only $0.25$, since the $1.00$ member will vote "Yes" and the $0.75$ member must vote "No". So $0.5$ is the best we can do.

**Sample Explanation**

- $1 \leqslant \mathbf{T} \leqslant 100$.
- $2 \leqslant \mathbf{K} \leqslant \mathbf{N}$.
- $\mathbf{K}$ is even.
- $0.00 \leqslant$ each $\mathbf{P}_{\mathbf{i}} \leqslant 1.00$.

**Small dataset (5 Pts, Test Set 1 - Visible)**

- Time limit: ~~60~~ 15 seconds.
- $2 \leqslant \mathbf{N} \leqslant 16$.

**Large dataset (Test Set 2 - Hidden)**

- Time limit: ~~120~~ 30 seconds.
- $2 \leqslant \mathbf{N} \leqslant 200$.


---

---
title: "赌神：决斗"
layout: "post"
diff: 普及+/提高
pid: P4978
tag: ['二分', '枚举', '前缀和', '概率论']
---
# 赌神：决斗
## 题目背景

**赌神 $\mathcal{CYJian}$，他回来了！**

## 题目描述

**$\mathcal{tomoo}$** 决定与 **$\mathcal{CYJian}$** 进行决斗！

已知 **$\mathcal{tomoo}$** 有 $\mathcal{N}$ 张扑克牌，每张扑克牌有一个$\mathcal{RP}$值$\mathcal{A_i}$， **$\mathcal{CYJian}$** 有$\mathcal{M}$张扑克牌，每张扑克牌有一个$\mathcal{RP}$值$\mathcal{B_i}$。

**$\mathcal{CYJian}$** 与 **$\mathcal{tomoo}$** 将会各自从他们的牌里任意取一段**连续区间**的牌决斗，谁的区间内的牌的$\mathcal{RP}$值的和更大，谁就赢了，请你帮忙求出 **$\mathcal{tomoo}$** 赢的概率。
## 输入格式

- 第一行 $2$ 个正整数 $\mathcal{N,M}$
- 第二行 $N$ 个正整数 $\mathcal{A_i}$
- 第三行 $M$ 个正整数 $\mathcal{B_i}$
## 输出格式

一个数表示 **$\mathcal{tomoo}$** 获胜的概率，如果答案可以表示成 $\frac{P}{Q}$ 的形式,则输出 $\frac{P}{Q}\%998244353$（不懂的左转[P3811](https://www.luogu.org/problemnew/show/P3811)）
## 样例

### 样例输入 #1
```
5 5
1 2 3 4 5
1 3 5 7 9
```
### 样例输出 #1
```
754229067
```
### 样例输入 #2
```
10 15
7 8 5 1 2 3 6 5 4 1 
52 10 5 6 3 2 1 4 5 8 7 4 5 6 3
```
### 样例输出 #2
```
181952721
```
### 样例输入 #3
```
1 1
5
5
```
### 样例输出 #3
```
0
```
### 样例输入 #4
```
5 5
1254125 36521421 25362142 12514221 25362142
857412252 36322411 2236232 1254112 36224125
```
### 样例输出 #4
```
261761853
```
### 样例输入 #5
```
2 2
2 4
2 5
```
### 样例输出 #5
```
332748118
```
## 提示

### 样例解释
- 样例 $3$：不管怎么抽都是平均，胜率为 $0$
- 样例 $5$：共有 $9$ 种方案，其中 $3$ 次 **tomoo** 会赢，胜率为 $1/3$

### 数据范围
- 对于 $20\%$ 的数据，$0<N,M\le50$
- 对于另外 $20\%$ 的数据，$\sum_{i=1}^NA_i\le10^6,\sum_{j=1}^MB_j\le10^6$
- 对于$100\%$的数据，$0<N,M\le2000,0<A_i,B_i\le10^9$


---

---
title: "「EZEC-2」机器"
layout: "post"
diff: 普及+/提高
pid: P6601
tag: ['递推', '二项式定理', '概率论', '矩阵乘法', '逆元']
---
# 「EZEC-2」机器
## 题目背景

tlx 喜欢科幻小说。   

>小宇宙中只剩下漂流瓶和生态球。漂流瓶隐没于黑暗里,在一千米见方的宇宙中,只有生态球里的小太阳发出一点光芒。在这个小小的生命世界中,几只清澈的水球在零重力环境中静静地飘浮着,有一条小鱼从一只水球中蹦出,跃入另一只水球,轻盈地穿游于绿藻之间。在一小块陆地上的草丛中,有一滴露珠从一片草叶上脱离,旋转着飘起,向太空中折射出一缕晶莹的阳光。    
>$\qquad \qquad \qquad \qquad \qquad \qquad \qquad\qquad\qquad\qquad\qquad\qquad\qquad --$《三体》    

在另一个宇宙，将是另一番奇景吧。    

在那里，重力似乎变得微不足道了，引力机器成了司空见惯的东西。

引力机器装置内并没有重力，即若有物体在机器上运动，运动过程中只受机器给予的引力，这个力有一定几率使物体向施力物体快速移动，达到一定动力时就可以实现瞬移。


## 题目描述

一个引力机器由一个光滑圆轨道和 $2n$ 个小孔组成（小孔按**逆时针**从 $1$ 到 $2n$ 编号，每两个相邻的小孔所夹的**劣弧**度数为 $\dfrac{\pi}{n}$ ），每个小孔与和其夹角为 $\pi$ 的另一个小孔有通道相连，比如当 $n=2$ 时，$1$ 号孔和 $3$ 号孔相连。

当 $n=2$ 时，这个装置的构造大概是这样的：
 
 ![](https://cdn.luogu.com.cn/upload/image_hosting/el8alxde.png) 
 
现在我们在 $1$ 号孔处放一个小球，使它一直**沿逆时针方向做匀速圆周运动**，在不瞬移的情况下，每一秒恰好能从一个小孔运动至下一个小孔。

由于未来实验室构造奇特（内部的引力提供装置太神了！），每经过一个小孔时，有 $p$ 的概率**立刻瞬移**（即不花费时间）到通道对面的小孔并继续沿逆时针方向做匀速圆周运动，也就是有 $1-p$ 的概率继续沿圆周向下一个小孔运动。

值得注意的是，**每一单位时刻，小球只能瞬移一次**。  

简单地说，若某一时刻小球在小孔 $i$，则下一时刻它可能运动到小孔 $i \bmod 2n + 1$ 或 $(i + n) \bmod 2n + 1$，概率分别为 $1-p$ 和 $p$。

现在 tlx 有两个一模一样的引力机器，两个小球同时从 $1$ 号孔开始运动。他会**随机**（所有可能选择的概率相同）选择一个二元组 $(i,j)( 1\leqslant i\leqslant 2n,0\leqslant j\leqslant t,i,j\in \mathbb Z$ ) 分别代表小孔编号和时间，你需要求出时间为 $j$ 时两个引力机器的小孔 $i$ **同时**有小球**停留（运动经过小孔但瞬移到对面了不算停留）** 的概率。

注意：**小球刚开始运动时也可能瞬移到对面的小孔。**   

为方便计算，我们规定：所有概率都是在模 $10^9+7$ 意义下的。      
## 输入格式

输入数据共一行，三个整数 $n,p,t$，分别代表引力装置的小孔数的一半，瞬移的概率对 $10^9+7$ 取模的结果，选择的时间的范围的上界。
## 输出格式

共一行，一个整数，代表两个小球同时经过所选位置的概率对 $10^9+7$ 取模的结果。
## 样例

### 样例输入 #1
```
2 500000004 1
```
### 样例输出 #1
```
125000001
```
### 样例输入 #2
```
6 114514 11
```
### 样例输出 #2
```
756497239
```
## 提示

**【数据范围与约定】** 

**本题采用捆绑测试。**    

具体计分方式如下：   

- Subtask $1$ ($7$ points)：满足 $p\in \{0,1\}$；  
- Subtask $2$ ($13$ points)：满足 $t\leqslant 20,n\leqslant50$；  
- Subtask $3$ ($20$ points)：满足 $t\leqslant 10^3,n\leqslant50$；  
- Subtask $4$ ($10$ points)：满足 $t\leqslant 10^3$；  
- Subtask $5$ ($10$ points)：满足 $t\leqslant 10^6$；
- Subtask $6$ ($15$ points)：满足 $n\leqslant50$；
- Subtask $7$ ($25$ points)：无特殊限制。


对于 $100\%$ 的数据，满足 $2\leqslant n\leqslant 500$，$0\leqslant p\leqslant 10^9+6$，$0\leqslant t \leqslant 10^9$。  

**注意：不做说明的数据范围即为极限数据范围。**

**【样例解释 #1】**  

$500000004$ 是模 $10^9+7$ 意义下的 $\dfrac{1}{2}$。 

下面为了方便，记 $P(i,j)$ 为选择的二元组为 $(i,j)$ 时的概率。    

所有概率不为 $0$ 的二元组有：   
$P(1,0)=\dfrac{1}{4},P(3,0)=\dfrac{1}{4},P(2,1)=\dfrac{1}{4},P(4,1)=\dfrac{1}{4}$。    

所有可以选择的二元组有：   
$(1,0),(1,1),(2,0),(2,1),(3,0),(3,1),(4,0),(4,1)$，共 $8$ 种。    

所以总的概率：  
$$P=\dfrac{1}{8}×\dfrac{1}{4}×4+\dfrac{1}{8}×0×4=\dfrac{1}{8}$$

在模 $10^9+7$ 意义下为 $125000001$，即为输出的答案。

------------

**【其他提示】**

1. 如果你不了解分数取模，可以查看[这里](https://www.luogu.com.cn/problem/P2613)。  

2. 如果你不明白题目中角度的表示方法，可以查看[弧度制](https://baike.baidu.com/item/弧度制/3315973?fr=aladdin)。




---

---
title: "「SWTR-7」IOI 2077"
layout: "post"
diff: 普及+/提高
pid: P7875
tag: ['数学', 'O2优化', '概率论', '期望', '洛谷月赛']
---
# 「SWTR-7」IOI 2077
## 题目背景

#### 友情提醒：本题输入输出量很大，请不要使用 cin 或 scanf。题目最下方附有快读及其使用方法。

#### 赛时提醒：若对于选出的 $m$ 无解，则期望值为 $0$。可以结合样例 2 的解释说明以更好理解。

#### 赛时提醒：你需要求的是能力值之和的期望而不是最大值。

---

小 A 被 FCC 钦定参加 IOI 2077！71 岁老将请求出战！
## 题目描述

IOI 2077 有 $n$ 位**候选**参赛者，他们分别编号为 $1\sim n$。每位候选参赛者都有一个能力值，且**能力值互不相等**，第 $i$ 位候选参赛者的能力值为 $a_i$。小 A 更喜欢有序的数字，所以他将这 $n$ 位候选参赛者按照能力值**从小到大**排好了序，即**满足 $a_i<a_{i+1}\ (1\leq i<n)$。**

正式参赛者将会从这 $n$ 位候选参赛者中产生。具体地，所有参赛者将是候选参赛者的一个子串 $[l,r]$，即编号为 $l,l+1,\cdots,r$ 的选手将参加 IOI 2077，其中，小 A 的编号为 $k$。因为他知道自己被钦定参加 IOI 2077，所以 $l\leq k\leq r$。可能的参赛者一共有 $q$ 种情况，每种情况用三个数 $l_i,r_i,k_i\ (l_i\leq k_i\leq r_i)$ 描述，即参赛者为编号在区间 $[l_i,r_i]$ 中的候选参赛者，而小 A 的编号为 $k_i$。

由于自己太菜，小 A 对即将到来的 IOI 感到力不从心。他决定选择一些参赛者作为队友，并与他们在赛场上相互帮（zuo）助（bi）。具体地，设正式参赛人数为 $s$，那么小 A 会在 $[0,\lfloor\frac{s-1}{2}\rfloor]$ 中**等概率随机**选择一个数 $m$，并从 $s$ 位参赛者中**随机**选出 $2m$ 个作为他的队友。不过，小 A 不希望自己显得太菜，所以**他的能力值 $a_k$ 必须是这 $2m+1$ 个人的能力值的中位数**。

俗话说，人多力量大，小 A 希望他与所有选出的队友的能力值之和尽量地大。**不过在此之前，他想知道这个值的期望值是多少**。请对 $998244353$ 取模，保证答案在该模数下有意义。**对于每一种可能的参赛者情况，你都需计算该情况下的答案。为了避免过大的输出，你只需要计算所有答案的异或和。**
## 输入格式

第一行一个整数 $t$，**表示该测试点 Subtask 编号。**  
第二行两个整数 $n,q$，分别表示候选参赛者个数和情况总数。  
第三行 $n$ 个整数 $a_1,a_2,\cdots,a_n$ 表示每个候选参赛者的能力值。**保证 $a_i$ 递增。**  
接下来 $q$ 行，每行三个整数 $l_i,r_i,k_i$ 描述一个可能的参赛者情况。
## 输出格式

输出一行一个整数，表示所有答案的异或和。
## 样例

### 样例输入 #1
```
0
5 2
2 3 5 7 8
1 5 3
2 4 2

```
### 样例输出 #1
```
499122189
```
## 提示

**「样例 1 说明」**

- 第 1 个询问：  
  因为 $s_1=r_1-l_1+1=5$，所以 $m$ 可以为 $0,1$ 或 $2$。  
  $m=0$ 时：小 A 没有队友，那么期望值就是他自身的能力值 $a_{k_1}=a_3=5$。    
  $m=1$ 时：小 A 可以选**编号** $(1, 4)$ 或 $(1, 5)$ 或 $(2, 4)$ 或 $(2, 5)$ 的参赛者作为他的队友，能力值之和分别为 $14,15,15,16$，期望值为 $\frac{14+15+15+16}{4}=15$。    
  $m=2$ 时：小 A 只能全选，期望值为 $2+3+5+7+8=25$。  
	综上，期望值为 $\frac{5+15+25}{3}=15$。

- 第 2 个询问：  
  因为 $s_2=r_2-l_2+1=3$，所以 $m$ 可以为 $0$ 或 $1$。  
  $m=0$ 时，小 A 没有队友，期望值为 $3$。    
  $m=1$ 时，小 A 无法选择，期望值为 $0$。  
  综上，期望值为 $\frac{3+0}{2}=\frac{3}{2}$，对 $998244353$ 取模后为 $499122178$。
  
$15\oplus499122178=499122189$。

**「数据范围与约定」**

**本题采用捆绑测试。**

记 $s_i=r_i-l_i+1$。

- Subtask #0（1 point）：是样例。
- Subtask #1（10 points）：$s_i\leq 2$。
- Subtask #2（20 points）：$s_i\leq 16$，$q\leq 40$，$n\leq 640$。
- Subtask #3（15 points）：$s_i,q\leq 500$，$n\leq 10^5$。
- Subtask #4（15 points）：$s_i,q\leq 3\times 10^3$，$n\leq 10^5$。
- Subtask #5（15 points）：$s_i,q\leq 2\times 10^5$，$n\leq 5\times 10^5$。
- Subtask #6（24 points）：无特殊限制。

对于 $100\%$ 的数据，$1\leq n,q\leq 2\times 10^6$，$1\leq l_i\leq k_i\leq r_i\leq n$，$1 \le a_i \le 998244352$，$a_i<a_{i+1}\ (1\leq i<n)$。

对于所有测试点，时间限制 1s，空间限制 512MB。

**「帮助/提示」**

关于 [有理数取余](https://www.luogu.com.cn/problem/P2613)，[中位数](https://baike.baidu.com/item/%E4%B8%AD%E4%BD%8D%E6%95%B0/3087401?fr=aladdin)。

本题输入输出量**极大**，**请注意 I/O 优化。**  
本题提供**有符号 32 位整数**快读模板，保证读入用时不超过 250ms：

```cpp
#define gc getchar()
inline int read(){
	int x=0; bool sgn=0; char s=gc;
	while(!isdigit(s))sgn|=s=='-',s=gc;
	while(isdigit(s))x=(x<<1)+(x<<3)+(s-'0'),s=gc;
	return sgn?-x:x;
}

// 如果需要读入直接调用 read() 即可。
// 一个例子（与正解无关，仅供参考）：

int t=read(),n=read(),q=read();
int a[2000005],l[2000005],r[2000005],k[2000005];
for(int i=1;i<=n;i++)a[i]=read();
for(int i=1;i<=q;i++)l[i]=read(),r[i]=read(),k[i]=read();

// 这样你就可以在 250ms 内读入全部数据了。
```

**「题目来源」**

[Sweet Round 07](https://www.luogu.com.cn/contest/51773) C。  
idea & solution：[SSerWarriors_Cat](https://www.luogu.com.cn/user/147999)；data：[Alex_Wei](https://www.luogu.com.cn/user/123294) ；验题：[chenxia25](https://www.luogu.com.cn/user/138400)。

---

IOI 2077 落下帷幕，小 A 凭借出（dui）色（you）的发（bang）挥（zhu）成功 AK 了 IOI，这不禁让他回想起曾经满腔热血的自己，以及和他共同奋斗在 OI 路上的战友们。如今他们虽已天各一方，说起来也有十几年没见过面了，但他们真挚的友谊未曾淡去，也将永远不会褪色。

>*“爷爷，您手机里有段录音，还写着 'ycx txdy!'。”*  
>*“哦，是嘛？放出来听听。”*  
>>*“I AK IOI. I AK ACM World Final. I AK Universe OI. I think all of you are vegetable chickens.”*  
>>*“I AK IOI. I AK ACM World Final. I AK Universe OI. I think all of you are vegetable chickens.”*  
>>*“I AK IOI. I AK ACM World Final. I AK Universe OI. I think all of you ............”*

2077.7.7


---

---
title: "〈 TREEのOI 2022 Spring 〉Absolutely Simple Game"
layout: "post"
diff: 普及+/提高
pid: P8307
tag: ['博弈论', 'O2优化', '概率论', '逆元']
---
# 〈 TREEのOI 2022 Spring 〉Absolutely Simple Game
## 题目背景

rin 和 len 在玩一个绝对简单的游戏，pcq 为裁判。
## 题目描述

初始时给定范围 $[l,r]=[1,n]$，pcq 从中均匀随机选出一个自然数 $t$，之后 rin 和 len 两人轮流进行操作，rin 先行。

每次操作方猜测一个整数 $x\in[l,r]$，若 $x=t$，则游戏结束，该方负；若 $x<t$，则调整范围 $[l,r]$ 为 $[x+1,r]$；若 $x>t$，则调整范围 $[l,r]$ 为 $[l,x-1]$。

rin 和 len 两人均充分了解规则且无比可爱聪明（都会最大化自己的胜率），过程中谁都知道场上除了 $t$ 以外的一切信息，求 rin 的胜率。
## 输入格式

一行一个整数 $n$。
## 输出格式

一行一个整数，表示 rin 的胜率，按分数 $\bmod~998244353$ 输出。
## 样例

### 样例输入 #1
```
3
```
### 样例输出 #1
```
665496236
```
## 提示

**样例解释1：**  

rin 的胜率为 $\dfrac 23$（一开始猜 $2$），$\bmod~998244353$ 后输出为 $665496236$。

***

**本题采用 SubTask 捆绑测试。**

| SubTask 编号 | 分值 | 特殊限制 |
| :-----------: | :-----------: | :-----------: |
| $0$ | $10$ | $n\equiv 0\ \pmod 2$ |
| $1$ | $20$ | $n\le 100$ |
| $2$ | $30$ | $n\le 10^9$ |
|$3$|$40$|$n\le 10^{18}$|

对于 $100\%$ 的数据，$1 \le n\le 10^{18}$。

---
**如何对有理数取模？**  

$\dfrac {x}{y} \bmod m$ 定义为 $xy^{m-2}\bmod~m$。

$m$ 必须为质数。  

保证答案约分后分母不为 $998244353$ 的倍数。


---

