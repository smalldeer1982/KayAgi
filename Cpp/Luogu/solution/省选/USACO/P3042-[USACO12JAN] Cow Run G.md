# [USACO12JAN] Cow Run G

## 题目描述

农夫 John 和 Bessie 为奶牛们设计了一种新的运动游戏。奶牛们从同一位置开始，在一个长度为 $M$ 的圆形跑道上奔跑，其中 $2 \leq M \leq 1,000,000,000$。游戏进行 $N$ 轮（$1 \leq N \leq 14$），使用一副 $8N$ 张的牌，每张牌上写有一个数字 $X_i$，其中 $0 \leq X_i < M$。

每一轮，FJ 将顶部的 8 张牌移到一个单独的牌堆中，并选择顶部 4 张或底部 4 张牌供 Bessie 使用。然后 Bessie 从 FJ 选择的 4 张牌中选择顶部 2 张或底部 2 张牌。之后，FJ 报出顶部牌上的数字 $X_{\text{top}}$，奶牛们跑 $R \times X_{\text{top}}$ 的距离，其中 $R$ 是奶牛们到目前为止跑过的总距离。接着 Bessie 报出底部牌上的数字 $X_{\text{bottom}}$，奶牛们再跑 $X_{\text{bottom}}$ 的距离。

FJ 担心在运动后，奶牛们会太累而无法回到跑道的起点，如果它们离起点的距离超过 $K$，它们就无法回家，其中 $0 \leq K \leq \lfloor \frac{M}{2} \rfloor$。

可以保证，如果 FJ 正确地进行游戏，他总能确保奶牛们能够回家，无论 Bessie 做出什么选择！对于每一轮，你的任务是确定 FJ 应该选择哪一半的牌，以便无论 Bessie 从那时起做出什么选择，FJ 总能让奶牛们回家。Bessie 将根据输入提供的选择进行移动，然后你可以继续进行下一轮。注意，尽管 Bessie 的选择在输入中提供给你，但你需要为 FJ 指定无论 Bessie 选择什么都能奏效的策略（因此实际上 FJ 并不知道 Bessie 在她的回合中会做什么）。


## 说明/提示

奶牛们必须准确地回到起点才能回家。注意，FJ 事先不知道 Bessie 会做出什么选择。如果 FJ 知道，他每次都可以选择底部一半。
（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
2 2 0 
TT 
1 0 0 0 0 0 0 1 
0 1 1 1 0 0 1 0 
```

### 输出

```
TB 
```

# 题解

## 作者：星爵 (赞：7)

好像没什么人做这道题。。。

首先肯定是想4^n暴枚，可惜会超时。

考虑到某一轮作出某个选择的条件是：无论以后牛怎么选，农夫都有合法的选择方案。

如果枚举两个选择的话肯定不行，但是两种选择的结果逻辑运算有神奇的短路性质，所以在某一种满足条件的情况下另一种无需计算，这样会减小计算量。

那么数据故意卡怎么办呢？神奇的随机选择解决它。

附上真\*题解：http://txhwind.blog.163.com/blog/static/203524179201211109155143/

```cpp
#include<cstdio>
#include<iostream>
#include<cstdlib>
const int MAXN=14;
int m,x[MAXN<<3];
inline int calc(long long run,int n,bool a,bool b){
        int t=n*8+a*4+b*2;
        return (run*(x[t]+1)+x[t+1])%m;
}
int n,k;
bool check2(int,int);
bool check1(int now,int run,bool a){
        bool b=rand()&1;
        return check2(now+1,calc(run,now,a,b)) && check2(now+1,calc(run,now,a,!b));
}
bool check2(int now,int run){
        if(now==n)
                return run<=k || run+k>=m;
        bool a=rand()&1;
        return check1(now,run,a) || check1(now,run,!a);
}
int main(){
    int i,run=0;
    char c[MAXN];
    scanf("%d%d%d%s",&n,&m,&k,c);
    for(i=0;i<n<<3;++i)
        scanf("%d",x+i);
    for(i=0;i<n;++i)
        if(check1(i,run,1)){
            putchar('B');
            run=calc(run,i,1,c[i]=='B');
        }
        else{
            putchar('T');
            run=calc(run,i,0,c[i]=='B');
        }
    return 0;
}

```

---

## 作者：DeepSeaSpray (赞：5)

官方题解：[Link](https://usaco.org/current/data/sol_cowrun.html)

首先考虑暴力，具体来说可以从 SG 函数的角度思考。

如果一个位置可行那么设为 $1$，不可行则设为 $0$。

那么贝茜的操作即取 AND，FJ 的操作即取 OR。

见官方题解图：

![](https://cdn.luogu.com.cn/upload/image_hosting/s6eytjuy.png)

我们可以逐步确定取牌的策略，即先尝试取 `B`，检验是否可行，若不可行，取 `T`，（这样做是因为还有字典序最小的要求）。

暴力检验是 $O(2^{2n})$ 的。

接着我们发现 OR 和 AND 都有**短路**的性质，即 OR 中出现了一个 $1$ 之后就会停止运算，AND 类似。

我们可以随机的选择先计算哪一颗子树，再运用短路的性质剪枝。我们可以考虑证明这样做的时间复杂度。

设 $f(d)$ 为一颗深度为 $d$ 的子树结果为 $0$ 的计算次数，$t(d)$ 为结果为 $1$ 的计算次数。

注意到德·摩根定律：

$$
P \land Q = \lnot (\lnot P \lor \lnot Q)
$$

所以 AND 与 OR 本质相同，故不妨假设所有操作都在 OR 上。

对于 $f(d)$，根据德·摩根（注意取反）有：

$$
f(d) = 2 t(d-1)
$$

对于 $t(d)$，当我们只有一个 $1$ 子树的时候最劣：

$$
t(d) = f(d-1) + \frac{1}{2} t(d-1)
$$

故：

$$
t(d) = \frac{1}{2} t(d-1) + 2 t(d-2)
$$

所以：

$$
t(d) = (\frac{1+\sqrt{33}}{4})^d
$$

所以检验的时间复杂度是：$O((\frac{1+\sqrt{33}}{4})^{2n})$ 的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=15;
mt19937 rnd(time(0));
int n,m,K;
int a[maxn+5][10];
char s[maxn+5];
inline int Calc(int st,int x,int c,int t){
	return ((a[st][(c<<2)|(t<<1)]+1ll)*x
		+a[st][(c<<2)|(t<<1)|1])%m;
}
bool Check(int st,int x,int c){
	int t=rnd()&1;
	if(st>(n-1)<<1) return (x<=K)||(-x+m<=K);
	if(st&1) return Check(st+1,x,t)||Check(st+1,x,!t);
	else{
		return Check(st+1,Calc(st>>1,x,c,t),t)
			&&Check(st+1,Calc(st>>1,x,c,!t),!t);
	}
}
signed main(){
	scanf("%d%d%d",&n,&m,&K);
	scanf("%s",s);
	for(int i=0;i<n;i++)
		for(int j=0;j<8;j++)
			scanf("%d",&a[i][j]);
	int x=0;
	for(int i=0;i<n;i++){
		if(Check(i<<1,x,1)){
			putchar('B');
			x=Calc(i,x,1,s[i]=='B');
		}
		else{
			putchar('T');
			x=Calc(i,x,0,s[i]=='B');
		}
	}
	return 0;
}
```

---

