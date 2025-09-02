# [CERC2018] Game of Stones

## 题目描述

**译自[ [CERC2018]](https://contest.felk.cvut.cz/18cerc/) [Game of Stones](https://contest.felk.cvut.cz/18cerc/solved/stones.pdf)**

Petyr 和 Varys 两个人在玩游戏。游戏中选手从 $N$ 堆石子中轮流取走一些石子。在自己的回合中，Petyr 可以从任意一堆中取走最多 $A$ 个石子，Varys 可以从任意一堆中取走最多 $B$ 个石子。每一轮选手至少要取走一个石子。取走最后一个石子的一方获胜。

游戏已经开始，并且现在 Petyr 要取石子。你的任务是判断在双方均采用最优策略的情况下 Petyr 是否能赢。

## 说明/提示

$1≤N,A,B,≤10^5,1≤X_i≤10^6$

## 样例 #1

### 输入

```
2 3 4
2 3```

### 输出

```
Petyr```

## 样例 #2

### 输入

```
7 8 9
1 2 3 4 5 6 7```

### 输出

```
Varys```

# 题解

## 作者：VinstaG173 (赞：7)

这道水题体现出我没有任何码力，整天写错各种细节。也许这就是为什么我 CF 也打得不好吧。

首先口胡是非常简单的。我们考虑分类。

$A=B$ 时即普通的 Bash 博弈，直接计算 SG 值异或和即可。SG 值就是 $x \bmod{(A+1)}$。

$A>B$ 时先按照两人都只能最多取 $B$ 计算，如果此时 Petyr 能赢则显然原游戏也能赢，如果此时 Petyr 不能赢，我们考虑能不能有使 SG 值仍为 $0$ 的操作。容易发现若有某一堆石子数 $>B$ 则可以从这一堆取 $B+1$ 颗，SG 值不变，Petyr 能获胜。若都 $\le B$ 则此游戏状态和 nim 没有区别，所以 Varys 必然获胜。

$A<B$ 时考虑 Petyr 的第一步操作。若 Petyr 能获胜，则他可以操作一步后到达 Varys 必败的情况，此与 $A>B$ 时 Petyr 必败的情况是一致的。于是我们枚举每堆使 SG 值变成 $0$ 的操作，如果操作完后还有一堆石子数 $>A$，则必然有 Petyr 落败。只有最初的 SG 值不为 $0$，至多只有一堆的石子数 $>A$，且操作后这一堆的石子数可以 $\le A$ 时 Petyr 能获胜。判断一下就行了。

时间复杂度 $O(n)$。

Code:
```cpp
#include<cstdio>
int n,t,f,v,a,b,r;
int x[100003];
int main()
{
	scanf(" %d %d %d",&n,&a,&b);
	for(int i=0;i<n;++i)scanf(" %d",&x[i]);
	if(a==b)
	{
		for(int i=0;i<n;++i)r^=x[i]%(a+1);
		puts((r)?"Petyr":"Varys");
		return 0;
	}
	if(a>b)
	{
		for(int i=0;i<n;++i)r^=x[i]%(b+1),(x[i]>b)&&(f=1);
		puts((r|f)?"Petyr":"Varys");
		return 0;
	}
	for(int i=0;i<n;++i)r^=x[i]%(a+1),(x[i]>a)&&(++v);
	for(int i=0;i<n;++i)t=x[i]%(a+1)^r,x[i]=(t>x[i]%(a+1))?(x[i]-x[i]%(a+1)+t-a-1):(x[i]-x[i]%(a+1)+t),(x[i]>a)&&(f=1);
	puts(((r)&&(!f)&&(v<2))?"Petyr":"Varys");
	return 0;
}
```

---

## 作者：QuQi_ZhouSi (赞：0)

###### [~~更不好的阅读体验~~](http://blog.godcraft.net:3000/post/P7467%5BCERC2018%5DGameofStones%C3%A9%C2%A2%C2%98%C3%A8%C2%A7%C2%A3)

### 解释

1. **当 $A = B$ 时：**  
   这种情况下是一个典型的 **Bash 博弈**，相当于两人均只能最多取 $A$ 个石子。直接通过 **Nim 博弈** 中的 **SG 值** 来判断胜负。每堆石子的 SG 值为 `石子数 % (A + 1)`，SG 值异或和不为 0 时，先手（Petyr）获胜，否则后手（Varys）获胜。

2. **当 $A > B$ 时：**  
   我们首先假设两人均只能取最多 $B$ 个石子，此时如果 Petyr 的 SG 值不为 0，则 Petyr 可以获胜。若 SG 值为 0，但有堆石子数大于 $B$，则 Petyr 可以取 $B + 1$ 个石子使得 SG 值不变，进而获胜。否则，若所有石子数均小于等于 $B$，游戏等价于普通 Nim 博弈，Varys 获胜。

3. **当 $A < B$ 时：**  
   Petyr 的第一步操作非常关键。如果 Petyr 先手能够改变局面，使得 Varys 在接下来的局面中必败，那么 Petyr 就会获胜。我们遍历每堆石子，尝试将其 SG 值变成 $0$，并且检查在此操作后是否还有一堆石子大于 $A$。如果此时的局面使得所有堆石子小于等于 $A$，则 Petyr 有获胜的机会，否则 Varys 获胜。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;

int n,a,b,x[N],r,v,f,t;
int main(){
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++) cin>>x[i];
    if(a==b){
        for(int i=1;i<=n;i++) r^=x[i]%(a+1);
        if(r) puts("Petyr");
        else puts("Varys");
        return 0;
    }
    if(a>b){
        for(int i=1;i<=n;i++){
            r^=x[i]%(b+1);
            f|=(x[i]>b);
        }
        if(r||f) puts("Petyr");
        else puts("Varys");
        return 0;
    }
    for(int i=1;i<=n;i++){
        r^=x[i]%(a+1);
        v+=(x[i]>a);
    }
    for(int i=1;i<=n;i++){
        t=x[i]%(a+1)^r;
        if(t>x[i]%(a+1)) x[i]=x[i]-x[i]%(a+1)+t-a-1;
        else x[i]=x[i]-x[i]%(a+1)+t;
        f|=(x[i]>a);
    }
    if(r&&!f&&v<2) puts("Petyr");
    else puts("Varys");
    return 0;
}
```

---

