# 题目信息

# Mark and Lightbulbs

## 题目描述

Mark has just purchased a rack of $ n $ lightbulbs. The state of the lightbulbs can be described with binary string $ s = s_1s_2\dots s_n $ , where $ s_i=\texttt{1} $ means that the $ i $ -th lightbulb is turned on, while $ s_i=\texttt{0} $ means that the $ i $ -th lightbulb is turned off.

Unfortunately, the lightbulbs are broken, and the only operation he can perform to change the state of the lightbulbs is the following:

- Select an index $ i $ from $ 2,3,\dots,n-1 $ such that $ s_{i-1}\ne s_{i+1} $ .
- Toggle $ s_i $ . Namely, if $ s_i $ is $ \texttt{0} $ , set $ s_i $ to $ \texttt{1} $ or vice versa.

Mark wants the state of the lightbulbs to be another binary string $ t $ . Help Mark determine the minimum number of operations to do so.

## 说明/提示

In the first test case, one sequence of operations that achieves the minimum number of operations is the following.

- Select $ i=3 $ , changing $ \texttt{01}\color{red}{\texttt{0}}\texttt{0} $ to $ \texttt{01}\color{red}{\texttt{1}}\texttt{0} $ .
- Select $ i=2 $ , changing $ \texttt{0}\color{red}{\texttt{1}}\texttt{10} $ to $ \texttt{0}\color{red}{\texttt{0}}\texttt{10} $ .

 In the second test case, there is no sequence of operations because one cannot change the first digit or the last digit of $ s $ .In the third test case, even though the first digits of $ s $ and $ t $ are the same and the last digits of $ s $ and $ t $ are the same, it can be shown that there is no sequence of operations that satisfies the condition.

In the fourth test case, one sequence that achieves the minimum number of operations is the following:

- Select $ i=3 $ , changing $ \texttt{00}\color{red}{\texttt{0}}\texttt{101} $ to $ \texttt{00}\color{red}{\texttt{1}}\texttt{101} $ .
- Select $ i=2 $ , changing $ \texttt{0}\color{red}{\texttt{0}}\texttt{1101} $ to $ \texttt{0}\color{red}{\texttt{1}}\texttt{1101} $ .
- Select $ i=4 $ , changing $ \texttt{011}\color{red}{\texttt{1}}\texttt{01} $ to $ \texttt{011}\color{red}{\texttt{0}}\texttt{01} $ .
- Select $ i=5 $ , changing $ \texttt{0110}\color{red}{\texttt{0}}\texttt{1} $ to $ \texttt{0110}\color{red}{\texttt{1}}\texttt{1} $ .
- Select $ i=3 $ , changing $ \texttt{01}\color{red}{\texttt{1}}\texttt{011} $ to $ \texttt{01}\color{red}{\texttt{0}}\texttt{011} $ .

## 样例 #1

### 输入

```
4
4
0100
0010
4
1010
0100
5
01001
00011
6
000101
010011```

### 输出

```
2
-1
-1
5```

# AI分析结果



# Mark and Lightbulbs

## 题目描述

Mark购买了一个包含$n$个灯泡的灯架。灯泡的状态可以用二进制字符串$s = s_1s_2\dots s_n$表示，其中$s_i=\texttt{1}$表示第$i$个灯泡亮，$s_i=\texttt{0}$表示灭。

由于灯泡损坏，Mark只能进行如下操作：
- 选择索引$i \in \{2,3,\dots,n-1\}$，且满足$s_{i-1} \ne s_{i+1}$。
- 翻转$s_i$的值（0变1，1变0）。

Mark希望将灯泡状态变为另一个二进制字符串$t$。求实现目标的最小操作次数，若无法完成输出-1。

## 说明/提示
- 首尾字符不同则直接无解
- 操作无法改变连续1段的数量
- 样例验证需考虑分界线的移动距离

---

### 关键思路与算法分析

#### 核心结论
1. **首尾约束**：若$s$与$t$的首字符或末字符不同，直接无解。
2. **段数守恒**：连续的1段数量必须相同，否则无解。
3. **端点移动**：答案等于所有对应连续1段的左右端点移动距离之和。

#### 解决难点
- **操作性质分析**：每次操作只能改变连续段的端点位置，无法合并或分裂段。
- **等效转换**：将字符串转换为连续段结构，通过分界线位置差计算操作次数。

#### 最优思路
1. **预处理段信息**：提取$s$和$t$中所有连续1段的起始和结束位置。
2. **段数校验**：若段数不同则无解。
3. **距离求和**：对每对对应段的左右端点计算绝对值差之和。

---

### 精选题解

#### 题解1：jiangtaizhe001（★★★★★）
**亮点**：代码简洁，直接处理分界线位置差。
```cpp
int n; ll ans; char s1[maxn],s2[maxn];
int p1[maxn],p2[maxn],cnt1,cnt2;
void work(){
    n=read(); scanf("%s%s",s1+1,s2+1);
    if(s1[1]!=s2[1]||s1[n]!=s2[n]){ puts("-1"); return; }
    cnt1=cnt2=0; ans=0;
    // 提取s和t的分界线位置
    for(int i=2;i<=n;i++) if(s1[i]!=s1[i-1]) p1[++cnt1]=i;
    for(int i=2;i<=n;i++) if(s2[i]!=s2[i-1]) p2[++cnt2]=i;
    if(cnt1!=cnt2){ puts("-1"); return; }
    // 计算分界线位置差之和
    for(int i=1;i<=cnt1;i++) ans+=abs(p1[i]-p2[i]);
    print(ans),pc('\n');
}
```

#### 题解2：Anguei（★★★★☆）
**亮点**：详细分析操作性质，代码结构清晰。
```cpp
std::vector<pii> segS, segT;
// 提取连续1段的端点
for (int i=1; i<=n; ++i) {
    if (s[i] == '0') continue;
    int j = i;
    while (j+1 <=n && s[j+1]=='1') ++j;
    segS.emplace_back(i, j);
    i = j;
}
// 类似处理t的连续1段...
if (segT.size() != segS.size()) return print(-1);
// 计算端点差之和
ll ans = 0;
for (int i=0; i<m; ++i) 
    ans += abs(segS[i].first - segT[i].first) + abs(segS[i].second - segT[i].second);
```

#### 题解3：happy_dengziyue（★★★★☆）
**亮点**：完整处理连续段，变量命名清晰。
```cpp
// 提取s的连续1段
for(int l=1,r; l<=n; ++l){
    if(a[l]=='0') continue;
    for(r=l; r+1<=n &&a[r+1]=='1'; ++r);
    al[++ai]=l; ar[ai]=r; l=r;
}
// 类似处理t的段...
ans = 0;
for(int i=1; i<=ai; ++i) 
    ans += abs(al[i]-bl[i]) + abs(ar[i]-br[i]);
```

---

### 拓展与练习
- **类似问题**：涉及分段操作、端点移动的问题，如CF1695D（树的最小覆盖集）。
- **推荐题目**：
  1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090) - 分治与贪心
  2. [P1880 石子合并](https://www.luogu.com.cn/problem/P1880) - 区间DP与环形处理
  3. [P5019 铺设道路](https://www.luogu.com.cn/problem/P5019) - 差分数组应用

---
处理用时：59.42秒