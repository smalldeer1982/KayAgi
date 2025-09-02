# 题目信息

# Chess Cheater

## 题目描述

You like playing chess tournaments online.

In your last tournament you played $ n $ games. For the sake of this problem, each chess game is either won or lost (no draws). When you lose a game you get $ 0 $ points. When you win you get $ 1 $ or $ 2 $ points: if you have won also the previous game you get $ 2 $ points, otherwise you get $ 1 $ point. If you win the very first game of the tournament you get $ 1 $ point (since there is not a "previous game").

The outcomes of the $ n $ games are represented by a string $ s $ of length $ n $ : the $ i $ -th character of $ s $ is W if you have won the $ i $ -th game, while it is L if you have lost the $ i $ -th game.

After the tournament, you notice a bug on the website that allows you to change the outcome of at most $ k $ of your games (meaning that at most $ k $ times you can change some symbol L to W, or W to L). Since your only goal is to improve your chess rating, you decide to cheat and use the bug.

Compute the maximum score you can get by cheating in the optimal way.

## 说明/提示

Explanation of the first testcase. Before changing any outcome, the score is $ 2 $ . Indeed, you won the first game, so you got $ 1 $ point, and you won also the third, so you got another $ 1 $ point (and not $ 2 $ because you lost the second game).

An optimal way to cheat is to change the outcomes of the second and fourth game. Doing so, you end up winning the first four games (the string of the outcomes becomes WWWWL). Hence, the new score is $ 7=1+2+2+2 $ : $ 1 $ point for the first game and $ 2 $ points for the second, third and fourth game.

Explanation of the second testcase. Before changing any outcome, the score is $ 3 $ . Indeed, you won the fourth game, so you got $ 1 $ point, and you won also the fifth game, so you got $ 2 $ more points (since you won also the previous game).

An optimal way to cheat is to change the outcomes of the first, second, third and sixth game. Doing so, you end up winning all games (the string of the outcomes becomes WWWWWW). Hence, the new score is $ 11 = 1+2+2+2+2+2 $ : $ 1 $ point for the first game and $ 2 $ points for all the other games.

## 样例 #1

### 输入

```
8
5 2
WLWLL
6 5
LLLWWL
7 1
LWLWLWL
15 5
WWWLLLWWWLLLWWW
40 7
LLWLWLWWWLWLLWLWWWLWLLWLLWLLLLWLLWWWLWWL
1 0
L
1 1
L
6 1
WLLWLW```

### 输出

```
7
11
6
26
46
0
1
6```

# AI分析结果

### 题目内容重写
# 棋赛作弊者

## 题目描述

你喜欢在网上参加棋赛。

在你最近的一次比赛中，你进行了 $n$ 场对局。为了简化问题，每场棋赛要么赢，要么输（没有平局）。当你输掉一场比赛时，你得到 $0$ 分。当你赢得一场比赛时，你得到 $1$ 或 $2$ 分：如果你也赢得了上一场比赛，你得到 $2$ 分，否则你得到 $1$ 分。如果你赢得了比赛的第一场比赛，你得到 $1$ 分（因为没有“上一场比赛”）。

这 $n$ 场比赛的结果用一个长度为 $n$ 的字符串 $s$ 表示：$s$ 的第 $i$ 个字符是 W 表示你赢得了第 $i$ 场比赛，是 L 表示你输掉了第 $i$ 场比赛。

比赛结束后，你发现网站有一个漏洞，允许你改变最多 $k$ 场比赛的结果（意味着你最多可以 $k$ 次将某个字符 L 改为 W，或将 W 改为 L）。由于你的唯一目标是提高你的棋赛评分，你决定作弊并使用这个漏洞。

计算通过最优作弊方式可以获得的最大分数。

## 说明/提示

第一个测试用例的解释。在改变任何结果之前，分数是 $2$。确实，你赢得了第一场比赛，所以得到了 $1$ 分，你也赢得了第三场比赛，所以得到了另一个 $1$ 分（而不是 $2$ 分，因为你输掉了第二场比赛）。

一种最优的作弊方式是改变第二场和第四场比赛的结果。这样做后，你赢得了前四场比赛（结果字符串变为 WWWWL）。因此，新的分数是 $7=1+2+2+2$：第一场比赛得 $1$ 分，第二、第三和第四场比赛各得 $2$ 分。

第二个测试用例的解释。在改变任何结果之前，分数是 $3$。确实，你赢得了第四场比赛，所以得到了 $1$ 分，你也赢得了第五场比赛，所以得到了 $2$ 分（因为你也赢得了上一场比赛）。

一种最优的作弊方式是改变第一、第二、第三和第六场比赛的结果。这样做后，你赢得了所有比赛（结果字符串变为 WWWWWW）。因此，新的分数是 $11 = 1+2+2+2+2+2$：第一场比赛得 $1$ 分，其他比赛各得 $2$ 分。

## 样例 #1

### 输入

```
8
5 2
WLWLL
6 5
LLLWWL
7 1
LWLWLWL
15 5
WWWLLLWWWLLLWWW
40 7
LLWLWLWWWLWLLWLWWWLWLLWLLWLLLLWLLWWWLWWL
1 0
L
1 1
L
6 1
WLLWLW```

### 输出

```
7
11
6
26
46
0
1
6
```

### 算法分类
贪心

### 题解分析与结论
该问题的核心在于如何通过改变最多 $k$ 场比赛的结果来最大化得分。由于得分的计算规则与连胜有关，因此最优策略是将 $L$ 改为 $W$，并且尽量将 $W$ 连在一起，以减少得分段数。

各题解的思路基本一致，都是通过贪心策略，优先将 $W$ 之间的 $L$ 改为 $W$，以减少得分段数。具体实现上，有的题解通过记录 $W$ 之间的空隙长度，并排序后优先填补小的空隙；有的题解则通过遍历字符串，直接计算得分的变化。

### 所选高分题解
#### 题解1：houzhiyuan (5星)
**关键亮点**：
- 通过记录 $W$ 之间的空隙长度，并排序后优先填补小的空隙，以减少得分段数。
- 代码清晰，逻辑严谨，处理了所有边界情况。

**核心代码**：
```cpp
int tot=0;//tot表示原来连续W之间的空隙数
int n,k,cnt=0,x=0;
n=read();
k=read();
bool ff=0;//将最前面出现的L去掉
scanf("%s",ch+1);
for(int i=1,s=0;i<=n;i++){
    if(ch[i]=='W')ff=1,cnt++;
    if(ch[i]=='L'&&ff){
        s++;
    }
    else{
        if(s>0)a[++tot]=s,s=0;//将连续W的长度放入a中
    }
}
if(cnt+k>=n){//如果可以全部变W，直接输出
    cout<<2*n-1<<endl;
    continue;
}
sort(a+1,a+tot+1);//贪心，尽量将小的空隙填充
int t=0;
for(int i=1;i<=tot;i++){
    t+=a[i];
    if(t>k){//超过k，统计段数
        x=tot-i+2;//有i-1个空隙被填充，一共有tot+1段W，段数为tot+1-(i-1)=tot-i+2
        break;
    }
}
if(t<=k&&(cnt||k)){//如果可以填充所有空隙，且cnt与k至少有一个不是0，段数只有1
    x=1;
}
printf("%d\n",(cnt+k)*2-x);//用上面推出的式子
```

#### 题解2：7KByte (4星)
**关键亮点**：
- 通过遍历字符串，直接计算得分的变化，优先将 $W$ 之间的 $L$ 改为 $W$。
- 代码简洁，逻辑清晰，处理了特殊情况。

**核心代码**：
```cpp
int sum=0,ans=0;
rep(i,1,n){
    sum+=s[i]=='L';
    ans+=s[i]=='W';
    ans+=(s[i]=='W'&&s[i-1]=='W');
}
k=min(k,sum);
if(k==sum){printf("%d\n",n*2-1);return ;}
c.clear();int pre=0;
rep(i,2,n-1){
    if(s[i]=='L'&&s[i-1]=='W')pre=i;
    if(s[i]=='L'&&s[i+1]=='W'&&pre)c.push_back(i-pre+1);
}
sort(c.begin(),c.end());
for(int i=0;i<(int)c.size();i++){
    if(c[i]<=k){
        k-=c[i];ans+=c[i]*2+1;
    }
    else{
        ans+=k*2;k=0;
    }
}
if(sum==n&&k)printf("%d\n",ans+k*2-1);
else printf("%d\n",ans+k*2);
```

### 最优关键思路
最优策略是通过贪心算法，优先将 $W$ 之间的 $L$ 改为 $W$，以减少得分段数。具体实现上，可以通过记录 $W$ 之间的空隙长度，并排序后优先填补小的空隙，或者直接遍历字符串，计算得分的变化。

### 可拓展之处
类似的问题可以扩展到其他需要最大化得分的场景，如通过改变某些操作来最大化某种收益。贪心算法在这些问题中通常是一种有效的解决策略。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：55.58秒