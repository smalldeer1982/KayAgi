# [GCJ 2011 Finals] Program within a Program

## 题目背景

不保证本题的 Special Judge 一定正确。

## 题目描述

你有一个机器人，位于一条无限延伸的东西向公路上，并且它需要递送一个蛋糕。公路上每隔一英里（无论东西方向）就有一根路灯柱。你需要编程让机器人恰好向东移动 $N$ 根路灯柱，并在那里释放蛋糕。路线不必直线，只要最终机器人能在正确的位置释放蛋糕即可。

不幸的是，这个机器人只有极少的内存，并且无法进行复杂的逻辑运算。你只能在开始时给它一个非常简单的程序，这个程序必须能让它在正确的位置释放蛋糕。该程序由一条或多条语句组成，每条语句都指示机器人在特定条件下该做什么。语句格式如下：

```
<S> <M> -> <action>
```

这表示当且仅当以下所有条件满足时：

1. 机器人处于状态 $s$。
2. 机器人当前所在的路灯柱标记为 $M$。

它将执行以下动作之一：

1. 给当前路灯柱打上新标记，改变状态并移动。此时 `<action>` 格式为 "`<D> <NS> <NM>`"，其中 `D` 表示移动方向（'W' 表示向西，'E' 表示向东），`NS` 表示机器人的新状态，`NM` 表示当前路灯柱的新标记。
2. 在当前位置释放蛋糕并自毁。此时 `<action>` 只需写 `release`。

如果你输出了两条或更多具有相同 $s$ 和 $M$ 的语句，机器人会出错并摧毁蛋糕。

如果机器人在某时刻处于状态 $X$，且站在标记为 $Y$ 的路灯柱上，但没有语句满足 $s=X$ 且 $M=Y$，那么机器人会困惑并吃掉蛋糕。

所有状态和标记都必须是绝对值不超过一百万（$10^6$）的整数。假设机器人初始状态为 $0$，所有路灯柱初始标记为 $0$。

给定 $N$，请编写一个程序，使机器人能在正确的位置释放蛋糕。你的程序最多只能使用 $30$ 条语句，并且必须在 $X$ 步内终止。

## 说明/提示

**样例解释**

在第一个样例中，机器人初始状态为 $0$，路灯柱标记为 $0$。它执行唯一的语句，即释放蛋糕。

在第二个样例中，机器人有五种状态：$0$、$1$、$2$、$3$ 和 $-1$。机器人按如下方式行动：

- 将当前路灯柱标记为 $1$，向东移动，进入状态 $1$。
- 将当前路灯柱标记为 $1$，向东移动，进入状态 $2$。
- 将当前路灯柱标记为 $1$，向东移动，进入状态 $3$。
- 将当前路灯柱标记为 $1$，向东移动，进入状态 $-1$。
- 释放蛋糕。

在第三个样例中，机器人有两种状态，执行如下操作：

- 将当前路灯柱标记为 $1$，向东移动，进入状态 $1$。
- 将当前路灯柱标记为 $1$，向西移动，进入状态 $0$。
- 释放蛋糕。

注意，机器人两次处于状态 $0$ 时采取了不同的动作，因为它看到的标记不同。

**数据范围**

- $1 \leq T \leq 15$。

**小数据集（15 分，测试点 1 - 可见）**

- $0 \leq N \leq 500$。
- $X = 250,000$。
- 时间限制：30 秒。

**大数据集（23 分，测试点 2 - 隐藏）**

- $0 \leq N \leq 5000$。
- $X = 150,000$。
- 时间限制：60 秒。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
0
4
0```

### 输出

```
Case #1: 1
0 0 -> R
Case #2: 5
0 0 -> E 1 1
1 0 -> E 2 1
2 0 -> E 3 1
3 0 -> E -1 1
-1 0 -> R
Case #3: 3
0 0 -> E 1 1
0 1 -> R
1 0 -> W 0 1```

# 题解

## 作者：A6n6d6y6 (赞：3)

## 闲话

随机跳题刷到的，一看是黑题，AC率竟有 $0\%$，但是这个图灵机的形式让我觉得很有意思。

于是开始想，想到了正解大概思路，然后写出来，随便调了几下就过了。

其实这道题不算很难，但是好像 GCJ 赛时没有人通过？（雾

## 题意

为了方便，在此简化亿下题意，先解释什么是图灵机：

有一个无限长的纸带，初始上面都写着 $0$。

有一个机器，初始所在位置为 $0$，分为控制器和表头两个部分，表头有一个状态。

控制器接受一些规则，形如“若表头状态为 $a$ 且所在格子写着 $b$，则将格子中的数改为 $c$，状态改为 $d$，然后左/右（题目中为 `W` 和 `E`）移动一个单位长度”。

每一次根据所在位置和状态对应的规则执行一步操作，直到当表头状态为 Halt（题目中为 `R`）时停止运行图灵机。

题目要求的就是：构造不超过 $30$ 条规则，使得图灵机在 $X$ 步内恰好在 $N$ 这个位置停机。

**小数据集**：$0 \leq N \leq 500$，$X = 250,000$，时限 $30$ 秒。

**大数据集**：$0 \leq N \leq 5000$，$X = 150,000$，时限 $60$ 秒。

## 思路

### 分析

首先拿到这种构造题，先写一个可视化工具或 SPJ （代码在后面）方便观察调试。

考虑一个暴力：将状态设为已经走过的步数，每走一次加 $1$，当状态为 $n$ 时停机。

虽然它花费步数最少，从不回头，但这显然浪费了纸带的存储功能，需要用 $O(n)$ 条规则。

为了利用纸带，不妨将剩下的步数写在纸带上。每次遍历一遍存在纸带上的数，将纸带上数的减一。

当纸带上的数归零时，就完成了计数，直接停机即可。

但是 $X=150000=5000\times30$，也就是说平均每个规则只能被调用 $O(n)$ 次，卡得比较紧。

所以我们不能来回太多次，应该带着纸带一起走，边移动边把纸带往前面也移动一格。

考虑如何在纸带上存数字，不妨选定一个进制 $k$，因为这是 OI 题目，这里选定二进制（后面会解释原因）。

特别地，由于纸带上所有数默认为零，我们将二进制中每个数位上的数 $+1$ 以便和 $0$ 区分开：

例如：$5=(101)_2$，在这里记为 $(2,1,2)$。

综上，图灵机的运行大概分为四个阶段：

Step I. 初始化，将题目中的 $N$ 按位从高到低存在纸带上。（从左到右遍历）

Step II. 将纸带上的数减一，若数字已经为 $0$ 则跳转 Step III，否则跳转 Step IV。（从右到左遍历）

Step III. 复制纸带上的数到下一位，跳转 Step II。（从左到右遍历）

Step IV. 停机。

可以发现，这样的安排总是左右横跳，没有出现无意义的遍历，可以在 $O(n\log n)$ 步内停机。

然后按步构造规则就可以了。

Tips：

- 下文所说的“左边”“右边”，均指二进制位最左/右的**下一个**，即第一个 $0$ 的位置。
- 重要的事情说两遍：记录的二进制数位上的数会 $+1$。

### Step I 初始阶段

首先，Step I 的实现是 naive 的，状态为 $S_i$（初始 $i=0,S_0=0$）时就填充从高到低第 $i$ 位上的数，然后向右移动，状态切换为 $S_{i+1}$。于是表头从左边移动到了右边。

初始转移：

```
S0 0 -> E S1 t0
S1 0 -> E S2 t1
...  -> ...
Sn-1 0 -> E Sn tn-1
```

### Step II 减法阶段

现在我们在数字的右侧，此时从高到低存储的好处就体现出来了。

此时定义状态 $M_1$，表示未完成减法，需要借位（更高位继续 $-1$）。

此时定义状态 $M_2$，表示减法已经完成，不需要借位（更高位不变）。

当状态为 $S_n$ 时，往回走并改为 $M_1$ 状态。

过渡转移：

```
Sn 0 -> W M1 0
```

减法转移：

```
//重要的事情说三遍：记录的二进制数位上的数会 +1
M1 1 -> W M1 2 //这一位是 0，减了 1 之后为 1，后面仍需继续借位
M1 2 -> W M2 1 //这一位是 1，减了 1 之后为 0，后面不需要借位了    
M2 1 -> W M2 1 //不需要借位，保持原样
M2 2 -> W M2 2 //不需要借位，保持原样
```

完成后表头从右边移动到了左边。

### Step III 移动阶段

当表头在左侧时若状态为 $M_2$，则说明减法成功，需要将数字移动到下一位。

现在我们在数字的左侧，设 $C_i$ 表示上一位为 $i$，初始 $i=0$。

若这一位是 $j$，则将这一位改为 $i$，状态改为 $C_j$，向右移动进入下一位。

特别地，此时需要考虑 $0$，因为左边的位置需要归零保证复杂度，而且占用新的位置也需要考虑 $0$。

特别地，当状态为 $C_0$ 且纸带上的数为 $0$ 时，即到达最右边，需要结束移动阶段，进入新一轮减法阶段。

移动转移：

```
//Ci j -> E Cj i
C0 0 -> W M1 0 //完成循环
C0 1 -> E C1 0
C0 2 -> E C2 0
C1 0 -> E C0 1
C1 1 -> E C1 1
C1 2 -> E C2 1
C2 0 -> E C0 2
C2 1 -> E C1 2
C2 2 -> E C2 2
```

### Step IV 结束阶段

当表头在左侧时若状态为 $M_1$，则说明减法失败，即当前数字已经为 $0$。

显然，数字的二进制位最左边就是位置 $n$ ，但是我们在最左边的下一个，也就是位置 $n-1$。

很好，我们的图灵机输入 $n$ 能到达位置 $n-1$，不妨将输入的 $n$ 先 $+1$。

那么我们的图灵机输入 $n+1$ 能到达位置 $n$，直接停机，完成任务。

### 复盘

简单复盘一下，若用 $k$ 进制，不考虑状态数和纸带上的数的大小限制（$10^6$ 想必用不完）。

需要 $\log_kN+1+2k+1+(k+1)^2+1=k^2+4k+5+\log_kN$ 个转移。

丢进画图工具里你会发现只有 $k=2$ 这个整数始终在 $N\le5000$ 时满足条件，所以只能选二进制。

只要理解了思路，代码超级好写。实现时对于 $S,M,C$ 函数随便取不同的值就可以了（特别地，满足$S_0=0$）。

## 代码

哈哈哈，居然是首A。

不是一分钟的时间限制我就跑了 $4$ 毫秒？

建议降低时限以免被别有用心之人利用。

::::info[code.cpp]

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>b;
int S(int x){return x;}
int C(int x){return 100+x;}
const int M1=-1,M2=-2;
struct rules{
	int bs;int bm;
	char mv;
	int es;int em;
};vector<rules>r;
void solve(int c){
	int n;cin>>n;n++;//记得要先+1
	b.clear();r.clear();
	//初始阶段
	for(int i=n;i;i>>=1)
		b.push_back((i&1)+1);
	reverse(b.begin(),b.end());
	int m=b.size();
	for(int i=0;i<m;i++)
		r.push_back({S(i),0,'E',S(i+1),b[i]});
	//初始->减法
	r.push_back({S(m),0,'W',M1,0});
	//减法阶段
	r.push_back({M1,1,'W',M1,2});
	r.push_back({M1,2,'W',M2,1});       
	r.push_back({M2,1,'W',M2,1});
	r.push_back({M2,2,'W',M2,2});
	//减法成功，进入复制阶段
	r.push_back({M2,0,'E',C(0),0});
	//移动阶段
	for(int i=0;i<=2;i++){
		for(int j=0;j<=2;j++){
			if(!i&&!j)r.push_back({C(0),0,'W',M1,0});
			else r.push_back({C(i),j,'E',C(j),i});
		}
	}
	//减法失败，停机
	r.push_back({M1,0,'R',114514,1919810});
	//输出
	cout<<"Case #"<<c<<": "<<r.size()<<'\n';
	for(auto [bs,bm,mv,es,em]:r){
		if(mv=='R')cout<<bs<<' '<<bm<<" -> "<<mv<<'\n';
		else cout<<bs<<' '<<bm<<" -> "<<mv<<' '<<es<<' '<<em<<'\n';
	}
}
int main(){
	int t;cin>>t;
	for(int i=1;i<=t;i++)solve(i);
	return 0;
}
/*
当时的思路：
------------------
S0 0 -> E S1 t
S1 0 -> E S2 t    ->  logn<=13
...  -> ...
Sn-1 0 -> E Sn t
------------------
Sn 0 -> W M1 0
------------------
M1 1 -> W M1 2
M1 2 -> W M2 1        
M2 1 -> W M2 1
M2 2 -> W M2 2
------------------
M2 0 -> E C0 0  ||  M1 0 -> r
------------------
//Ci j -> E Cj i
C0 0 -> W M1 0
C0 1 -> E C1 0
C0 2 -> E C2 0
C1 0 -> E C0 1
C1 1 -> E C1 1
C1 2 -> E C2 1
C2 0 -> E C0 2
C2 1 -> E C1 2
C2 2 -> E C2 2
------------------
*/
```

::::

::::info[spj.cpp]

```cpp
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MAX_STATEMENTS = 30;
const int MAX_STEPS = 1e6;
const int MIN_VAL = -1000000;
const int MAX_VAL = 1000000;

struct Rule {
    int state, mark;
    string action;
    char dir;
    int next_state, new_mark;
    bool drop;
};

struct Transition {
    int state, mark;
    Rule rule;
};

map<pair<int, int>, Rule> rules;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt(1, 15, "T"), total = 0;
    for (int testCase = 1; testCase <= T; ++testCase) {
        int N = inf.readInt(0, 5000, "N");
        string caseHeader = ouf.readToken();
        ensuref(caseHeader == "Case", "Expected 'Case' at line start.");
        string caseNumStr = ouf.readToken();
        ensuref(caseNumStr == "#" + to_string(testCase) + ":", "Expected '#<testCase>:'.");
        int ruleCount = ouf.readInt(1, MAX_STATEMENTS, "number of rules.");

        rules.clear();

        for (int i = 0; i < ruleCount; ++i) {
            int S = ouf.readInt(MIN_VAL, MAX_VAL, "state");
            int M = ouf.readInt(MIN_VAL, MAX_VAL, "mark");
            string arrow = ouf.readToken();
            ensuref(arrow == "->", "Expected '->'");

            string token = ouf.readToken();

            Rule rule;
            rule.state = S;
            rule.mark = M;
            rule.drop = false;

            if (token == "R") {
                rule.drop = true;
            } else {
                ensuref(token == "E" || token == "W", "Invalid direction (must be E/W).");
                rule.dir = token[0];
                rule.next_state = ouf.readInt(MIN_VAL, MAX_VAL, "next state");
                rule.new_mark = ouf.readInt(MIN_VAL, MAX_VAL, "new mark");
            }

            pair<int, int> key = {S, M};
            ensuref(!rules.count(key), "Duplicate rule for (state=%d, mark=%d).", S, M);
            rules[key] = rule;
        }
        
        map<int, int> tape;
        int pos = 0;
        int state = 0;
        int steps = 0;

        while (true) {
            ++steps;
            if (steps > MAX_STEPS) {
                quitf(_wa, "Exceeded step limit (%d).", MAX_STEPS);
            }

            int mark = tape.count(pos) ? tape[pos] : 0;
            auto it = rules.find({state, mark});
            if (it == rules.end()) {
                quitf(_wa, "No rule for state=%d and mark=%d (robot got confused).", state, mark);
            }

            Rule r = it->second;

            if (r.drop) {
                if (pos == N) {
                    break;
                } else {
                    quitf(_wa, "Dropped cake at wrong position: %d (expected %d).", pos, N);
                }
            } else {
                tape[pos] = r.new_mark;
                state = r.next_state;
                pos += (r.dir == 'E') ? 1 : -1;
            }
        }
        total += steps;
    }
    quitf(_ok, "All cases passed in %d steps.",total);
}
```

::::

---

