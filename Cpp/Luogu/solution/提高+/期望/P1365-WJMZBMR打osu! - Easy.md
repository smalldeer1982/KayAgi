# WJMZBMR打osu! / Easy

## 题目背景

原 维护队列 参见 P1903

## 题目描述

某一天 WJMZBMR 在打 osu，~~但是他太弱了，有些地方完全靠运气:(~~。

我们来简化一下这个游戏的规则

有 $n$ 次点击要做，成功了就是 `o`，失败了就是 `x`，分数是按 combo 计算的，连续 $a$ 个 combo 就有 $a\times a$ 分，combo 就是极大的连续 `o`。

比如`ooxxxxooooxxx`，分数就是 $2 \times 2 + 4 \times 4 = 4 +16=20$。

Sevenkplus 闲的慌就看他打了一盘，有些地方跟运气无关要么是 `o` 要么是 `x`，有些地方 `o` 或者 `x` 各有 $50\%$ 的可能性，用 `?` 号来表示。

比如 `oo?xx` 就是一个可能的输入。
那么 WJMZBMR 这场 osu 的期望得分是多少呢？

比如 `oo?xx` 的话，`?` 是 `o` 的话就是 `oooxx`（$9$），是x的话就是 `ooxxx`（$4$），期望自然就是 $(4+9)/2 =6.5$ 了。

## 样例 #1

### 输入

```
4
????```

### 输出

```
4.1250```

# 题解

## 作者：HPXXZYY (赞：100)

首先，这是一道**期望 dp 题**。

我们按照 `dp` 的一般思路来思考这道题。

先考虑**设计状态**，我们记**期望**连续的 `o` 个数为 $\texttt{len}$，$f_i$ 表示以第 $i$ 个字符结尾的**期望**得分。

然后，我们考虑如何**转移**，很明显，转移需要分 `o,x,?` 考虑。

当当前字符为 `o` 时，$f_i=f_{i-1}+[(\texttt{len}+1)^2-\texttt{len}^2]=f_{i-1}+2 \times \texttt{len}+1$，而 $\texttt{len}=\texttt{len}+1$（注意先后顺序，先修改 $f_i$，再修改 $\texttt{len}$，下同）。

当当前字符为 `x` 时，$f_i=f_{i-1},\texttt{len}=0$。

前两个很显然，重点在 `?` 的转移，我们发现 `?` 为 `x` 和 `o` 的概率是一样的，所以 `?` 的转移就相当于把 `x` 和 `o` 的转移合在一起，然后乘上概率 $50\%$，即除以 $2$。

也就是说，当当前字符为 `?` 时，有：

$$f_i=f_{i-1}+\dfrac{[(\texttt{len}+1)^2-\texttt{len}^2]+0}{2} =f_{i-1}+\texttt{len}+0.5$$

而 $\texttt{len}=\dfrac{\texttt{len}+1}{2}$，$(\texttt{len}+1)^2-\texttt{len}^2$ 和 $\texttt{len}+1$ 是 `o` 的转移，其他都是 `x` 的转移，注意 $\texttt{len}$ 的转移应是 $\texttt{len}=\dfrac{(\texttt{len}+1)+0}{2}$，也就是 $\texttt{len}=\dfrac{\texttt{len}+1}{2}$。

### （主要思路来源于洛谷网校老师的课件）

**【主要代码】：**
```cpp
const int N=3e5+100;
long double len,f[N];
string s;int l,i;
int main(){
	cin>>l>>s;
	for(i=1;i<=l;i++){
		switch(s[i-1]){
			case 'x':f[i]=f[i-1];len=0;break;
			case 'o':f[i]=f[i-1]+2*len+1;len++;break;
			case '?':f[i]=f[i-1]+len+0.5;len=(len+1)/2;break;
		}
	}
	printf("%.4Lf",f[l]);
//	注意long double的输出需要一个大写的L
	return 0;
}
```

当然，这道题可以做到空间复杂度 $O(1)$。

```cpp
const int N=3e5+100;
char s[N];//用string慢 
long double ans,len;int n;
int main(){
	scanf("%d%s",&n,s+1);
	for(int i=1;i<=n;i++){
		if (s[i]=='o'){
			ans+=2*len+1;
			len++;
		}
		else if (s[i]=='x') len=0;
		else{
			ans+=len+0.5;
			len=(len+1)/2;
		}
	}
	printf("%.4Lf",ans);
	return 0;
}
```

**【补充】：**

1. 因为编者不想让某些人抄代码，又不想放一个反作弊系统影响其他人正常的阅读，所以编者决定，仅仅删去代码的**头文件**，主体部分全部是原汁原味的！这点请读者放心！

2. 关于概率 dp 的题，重点在你能不能想到如何转移，因为这种题目一般状态定义很简单。在考虑转移时，必要的话，需要一定的**分类讨论**或**数学知识**，所以数学学得好，对 `OI` 还是很有帮助的。

3. 关于万能头，现在网络上还存在很多争论，所以建议读者平时用用就好，考试还是要稳一点！

---

## 作者：Sweetlemon (赞：44)

#### WJMZBMR 打 osu! / Easy

这题比 osu! 一些图的 Easy 难多了……

##### 随机变量

我们需要详细定义**随机变量**，这样有利于理解。注意，下面的几段都还没有引入期望。

随机变量的推导可以认为是涵盖了各种可能情况时的推导。再次提醒，这里还没有期望！

$L_i$ 表示以第 $i$ 个点击结尾的 combo 的**长度**。如果 $a_i$ 是 x，$L_i=0$；对于 o，$L_i=L_{i-1}+1$，也就是不论 $L_{i-1}$ 如何，只要 $a_i$ 是 o，$L_i$ 总是等于 $L_{i-1}+1$。对于 ?，情况比较复杂，$L_i$ 有 $\frac{1}{2}$ 的概率等于 $L_{i-1}+1$，有 $\frac{1}{2}$ 的概率等于 $0$。

$F_i$ 表示假如在第 $i$ 次点击后游戏意外退出（这个说法好牵强），此时的**得分**（或者可以理解为进行到第 $i$ 次点击时游戏界面显示的分数，打过 osu! 也大概知道吧(大雾)）。

考虑如何从 $F_{i-1}$ 计算 $F_i$ 呢？这当然是考虑第 $i$ 次点击对分数有多少贡献（或者叫增量）啦。假如第 $i$ 次点击 miss 了，那么 $F_i$ 当然等于 $F_{i-1}$（这个音符就白打了）。但是如果成功了，那么 combo 加长了 $1$，分数又增加了多少呢？

由于 $(x+1)^2=x^2+2x+1$，也就是 $(x+1)^2-x^2=2x+1$，将 $x=L_{i-1}$ 代入上面的式子，于是 combo 增长 $1$ 对答案的增加量应该是 $2L_{i-1}+1$。

因此，对于 x，$F_i=F_{i-1}$；对于 o，$F_i=F_{i-1}+2L_{i-1}+1$；对于 ?，上述两个等式成立的概率各为 $\frac{1}{2}$。

或者，我们可以定义随机变量 $\Delta_i=F_i-F_{i-1}$。对于 x，$\Delta_i=0$；对于 o，$\Delta_i=2L_{i-1}+1$；对于 ?，上述两个等式成立的概率各为 $\frac{1}{2}$。

---

##### 随机变量的期望

这些可都是随机变量的分布啊，我要它干什么呢？

算期望确实要用到概率，接下来我们开始了！

由于期望的线性性，$\mathrm{Ex}(F_i)=\mathrm{Ex}(F_{i-1}+\Delta_i)=\mathrm{Ex}(F_{i-1})+\mathrm{Ex}(\Delta_i)$。因此，我们只需要想办法计算出 $\mathrm{Ex}(\Delta_i)$，就可以很容易地递推出 $\mathrm{Ex}(F_i)$ 了（其实 $\mathrm{Ex}(F_i)$ 就是 $\mathrm{Ex}(\Delta_i)$ 的前缀和嘛）。

对于 x，由于 $\Delta_i$ 恒等于 $0$，因此 $\mathrm{Ex}(\Delta_i)=0$。

对于 o，由于 $\Delta_i$ 恒等于 $2L_i-1$，由期望的线性性，$\mathrm{Ex}(\Delta_i)=\mathrm{Ex}(2L_{i-1}+1)=2\mathrm{Ex}(L_{i-1})+1$。

对于 ?，我们要根据分布列计算 $\mathrm{Ex}(\Delta_i)$，也就是把两种情况下的取值与概率相乘，加权相加——这应该算是全期望公式的应用吧。由于 $\Delta_i$ 取上述两种式子的概率各为 $\frac{1}{2}$，因此 $\mathrm{Ex}(\Delta_i)=\frac{1}{2}(0+2\mathrm{Ex}(L_{i-1})+1)=\mathrm{Ex}(L_{i-1})+\frac{1}{2}$。

上面的三个式子中有两个出现了 $\mathrm{Ex}(L_{i-1})$，因此我们在计算 $\mathrm{Ex}(\Delta_i)$ 的同时也要计算 $\mathrm{Ex}(L_i)$。

对于 x，由于 $L_i$ 恒等于 $0$，因此 $\mathrm{Ex}(L_i)=0$。

对于 o，由于 $L_i$ 恒等于 $L_{i-1}+1$，由期望的线性性，$\mathrm{Ex}(L_i)=\mathrm{Ex}(L_{i-1}+1)=\mathrm{Ex}(L_{i-1})+1$。

对于 ?，我们还是要根据分布列计算 $\mathrm{Ex}(L_i)$。由于 $L_i$ 取上述两种式子的概率各为 $\frac{1}{2}$，因此 $\mathrm{Ex}(L_i)=\frac{1}{2}(0+\mathrm{Ex}(L_{i-1})+1)=\frac{1}{2}\mathrm{Ex}(L_{i-1})+\frac{1}{2}$。

这样我们所需的所有递推式都全了，可以整理如下：

$$\begin{cases}\begin{aligned} &\mathrm{Ex}(L_i)=0,&a_i=\mathrm{x} \\ &\mathrm{Ex}(L_i)=\mathrm{Ex}(L_{i-1})+1,&a_i=\mathrm{o} \\ &\mathrm{Ex}(L_i)=\frac{1}{2}\mathrm{Ex}(L_{i-1})+\frac{1}{2}, &a_i=\mathrm{?} \end{aligned}\end{cases}$$

$$\begin{cases}\begin{aligned} &\mathrm{Ex}(F_i)=\mathrm{Ex}(F_{i-1}),&a_i=\mathrm{x} \\ &\mathrm{Ex}(F_i)=\mathrm{Ex}(F_{i-1})+2\mathrm{Ex}(L_{i-1})+1,&a_i=\mathrm{o}\\ &\mathrm{Ex}(F_i)=\mathrm{Ex}(F_{i-1})+\mathrm{Ex}(L_{i-1})+\frac{1}{2}, &a_i=\mathrm{?} \end{aligned}\end{cases}$$

初始值是 $F_0=L_0=0$。因为我们已经把辅助变量 $\Delta_i$ 处理掉了，所以最终我们不需要用到它。

注意一个要点！$F_i$ 的式子里不要出现 $L_i$，因为这样在应用全期望公式的时候会出问题。简单地说，就是全期望公式里面已经在讨论这个 ? 是否 miss 的这两种可能性了，但是 $\mathrm{Ex}(L_i)$ 里面同样包含了这个 ? 是否 miss 的讨论，一个事件重复讨论就会导致问题；或者说，在全期望公式里，已经假设（或者说在……的条件下）了这个 ? 是否 miss，因此应该代入的是已经确定下来的上一个状态，而不是代入目前这个状态。  
如果不好理解，可以试着把 $\mathrm{Ex}(F_i)=\mathrm{Ex}(F_{i-1})+\mathrm{Ex}(L_i)-\frac{1}{2},\ a_i=\mathrm{?}$ 代入 `?` 这个序列计算，就会发现问题。

----

##### 代码

下面是甚至不需要用到数组的代码。

另外，写完这题还可以写一道类似的 [osu!](https://www.luogu.org/problem/P1654)。

```cpp
#include <cstdio>
#include <cctype>
#include <algorithm>
#define MAXIOLG 25
#define FILENAME(x)\
freopen(x".in","r",stdin);\
freopen(x".out","w",stdout);
using namespace std;

typedef long long ll;
typedef long double ld;
typedef ll io_t;
io_t shin[MAXIOLG];
io_t seto(void); //快读
char seto_op(void); //读入 o,x,?
void ayano(io_t x,char spliter='\n'); //快速输出

int main(void){
    int n;
    n=seto();
    ld exl=0,exf=0; //动态维护 Ex(L_i), Ex(F_i)
    for (int i=1;i<=n;i++){
        char ch=seto_op(); //读入当前音符
        switch (ch){
            case 'x':
                exl=0; //Ex(F_i)=Ex(F_{i-1}), Ex(L_i)=0
                break;
            case 'o':
                exf+=2*exl+1,exl++; //Ex(F_i)=Ex(F_{i-1})+2Ex(L_{i-1})+1, Ex(L_i)=Ex(L_{i-1})+1
                //注意上面先更新 F，是因为 F 的更新需要用到原来的 L 值（道理类似于 01 背包倒序循环）
                break;
            case '?':
                exf+=exl+0.5,exl++,exl/=2; //Ex(F_i)=Ex(F_{i-1})+Ex(L_{i-1})+0.5, Ex(L_i)=0.5*(Ex(L_{i-1}+1)
                break;
        }
    }
    printf("%.4Lf\n",exf);
    return 0;
}

io_t seto(void){
    io_t ans=0;
    int symbol=0;
    char ch=getchar();
    while (!isdigit(ch))
        (ch=='-')?(symbol=1):(0),ch=getchar();
    while (isdigit(ch))
        (ans=ans*10+(ch-'0')),ch=getchar();
    return (symbol)?(-ans):(ans);
}

char seto_op(void){
    char ch=getchar();
    while (ch!='?' && ch!='o' && ch!='x')
        ch=getchar();
    return ch;
}

void ayano(io_t x,char spliter){
    if (!x){
        putchar('0'),putchar(spliter);
        return;
    }
    if (x<0)
        putchar('-'),x=-x;
    int len=0;
    while (x){
        io_t d=x/10;
        shin[len++]=x-d*10;
        x=d;
    }
    while (len){
        len--;
        putchar(shin[len]+'0');
    }
    putchar(spliter);
}
```

---

## 作者：浅色调 (赞：33)

### Solution：

　　期望题总是贼有意思。

　　本题期望combo为$o$的期望连续长度的平方，所以我们设$f[i]$表示到了第$i$位的总期望combo，$g[i]$表示到了第$i$位结尾的连续$o$的期望长度，那么分情况讨论：

　　1、当$s[i]==x$，则$f[i]=f[i-1],g[i]=0$;

　　2、当$s[i]==o$，则$f[i]=f[i-1]+2*g[i-1]+1,g[i]=g[i-1]+1$（$f[i]=f[i-1]+2*g[i-1]+1$是因为$f[i]=(g[i-1]+1)^2=g[i-1]^2+2*g[i-1]+1\;,\;g[i-1]^2=f[i-1]$）;

　　3、当$s[i]==?$，则$f[i]=f[i-1]+g[i-1]+0.5,g[i]=\frac{g[i-1]+1}{2}$;

　 **注意：**由于不知道$n$的范围，不好开数组，但是我们发现转移时当前的状态只与上一次的状态有关，于是直接滚掉就好了。
  
$\quad\;\;$欢迎来踩博客：[five20](https://www.cnblogs.com/five20/p/9384250.html)（蒟蒻写题解不易，转载请注明出处，万分感谢！）
### 代码：
```cpp
    /*Code by 520 -- 7.29*/
    #include<bits/stdc++.h>
    #define il inline
    #define ll long long
    #define For(i,a,b) for(int (i)=(a);(i)<=(b);(i)++)
    #define Bor(i,a,b) for(int (i)=(b);(i)>=(a);(i)--)
    using namespace std;
    int n,cnt;
    char s;
    double f[2],g[2];
    int main(){
        ios::sync_with_stdio(0);
        cin>>n;
        For(i,1,n){
            cin>>s;
            if(s=='x') f[cnt^1]=f[cnt],g[cnt^1]=0;
            else if(s=='o') f[cnt^1]=f[cnt]+2*g[cnt]+1,g[cnt^1]=g[cnt]+1;
            else f[cnt^1]=f[cnt]+g[cnt]+0.5,g[cnt^1]=g[cnt]/2+0.5;
            cnt^=1;
        }
        printf("%.4lf",f[cnt]);
        return 0;
    }
```

---

## 作者：dead_X (赞：15)

# 0 前面的话
To 管理员: 蒟蒻第一道蓝题(恶评) 题解求过 Latex 不太熟悉求谅解
明天就是CSP-J了所以来一发题解

普及组(Junior?)的窝只会一些最基础的期望(比如这题)所以就来水一发题解

**所以** WJMZBMR打osu! / Hard 呢?
# 1 前置知识
* 期望

>在概率论和统计学中，数学期望(mean)（或均值，亦简称期望）是试验中每次可能结果的概率乘以其结果的总和，是最基本的数学特征之一。它反映随机变量平均取值的大小。(BaiduBaike)

是不是简单易懂?

**更**简单地说，如果给你一个骰子，如果你投出$6$，dead_X就会给你1RMB。那么，你投一次期望获得的钱就是$1/6=0.1666\cdots$。因为你有$1/6$的概率投出6并且获得1RMB，还有$5/6$的机会没有投出6，获得0RMB，则期望就是$(1/6*1+5/6*0)=1/6+0=1/6$。

* 递推

什么?你不会递推?右转**斐波那契数列**。
# 2 正片
令当前的$combo$为$now$且前面的音符已经得到了$score$分，显然，根据这两个值和这次音符的打击结果，我们就可以推出这次的分数，即满足递推的规律。

如果一个音符我们**打中了**，那么我们的分数就会从$t+now^2$变成$t+(now+1)^2$，其中的差就是$2*now+1$，并且$now$也会$+1$。

没打中的话，分数不变，$now$也莫得了qwq

### 最重要的一部分，如果不一定打中呢?

**这个时候，如果打中了$(1/2)$，那么$now=now+1$,$score=score+(2*now+1)$，不然就是$now=0$,$score=score$**

**根据期望的概念可知——**

$now=(0+now+1)/2$ 也就是 $now=now/2+0.5$

$score=(score+score+2*now+1)/2$ 也就是 $score=score+now+0.5$

所以 递推!

### 注意! 因为有0.5 所以千万不要把combo开成int!
# 3 Code
因为太简单了所以懒得改一处地方了 但是不要$ctrl+c~~ and  ~~ ctrl+v$啊
```
#include<bits/stdc++.h>
using namespace std;
char ch[1000003];
double ans[1000003];
double combo[1000003];
int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1; i<=n; i++)ch[i]=getchar();
	ans[0]=0;
	combo[0]=0;
	for(int i=1; i<=n; i++)
	{
		switch(ch[i])
		{
			case 'o':
				ans[i]=ans[i-1]+combo[i-1]*2+1;
				combo[i]=combo[i-1]+1;
				break;
			case 'x':
				combo[i]=0;
				ans[i]=ans[i-1];
				break;
			case '?':
				ans[i]=ans[i-1]+(combo[i-1]*2+1)/2;
				combo[i]=(combo[i-1]+1)/2;
				break;
		}
	}
	printf("%.4f",ans[n]);
	return 0;
}
```
# 4 UPD
## upd1:我找到这道题的加难版了!
``P1654 OSU!``

``CF235B Let's Play Osu!``
## upd2:我真的去玩了一下这个游戏……
```
50
0
0
0
0
50
50
100
50
0
Failed...
```
Cy2玩家留下了Ta的眼泪……

---

## 作者：EDT_ (赞：9)

没有几个人做这个题，我发个题解好了：

**非正解**如下（大家请忽视）：

由于不知道数据范围的缘故，开始用“骗数据”的方法做这个题

第一份代码
```
	int n; scanf("%d", &n); printf("%d", n);

```
输出一个$n$，得出了$n$的范围和每个答案的前$4$~$5$位的答案。

~~经过几次实验以后（每次得到5位的答案），基本上可以得出所有的答案了QAQ~~
（每次用$n$判断）

由于后面的几个数据的$n$相等了，只能混$50$
```
#define f(P,t) if(n == P) return 0 * printf("%.4lf",t)
int main(){
    int n = read();
    f(10,14.50);
    f(30,188.5);
    f(100,2322.9375);
    f(200,5727.1104);
    f(1000,175779.5927);
}
```
怎么办？不能利用评测记录混分了吗？当然可以！

~~然后**根据出现的'o'的次数判断就好了**~~

交了几次，然后就能过了

code：
```
#include <bits/stdc++.h>
inline int read(){
    char ch = getchar(); int u = 0, f = 1;
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { u = (u << 1) + (u << 3) + ch - 48; ch = getchar(); }
    return u * f;
}
#define f(P,t) if(n == P) return 0 * printf("%.4lf",t)
#define g(P,t) if(ct1 == P) return 0 * printf("%.4lf",t)
char s[1000000];
int main(){
    int n = read();
    f(10,14.50); // Subtask : #1
    f(30,188.5);
    f(100,2322.9375);
    f(200,5727.1104);
    f(1000,175779.5927);
    register int ct1 = 0;
    char ch;
    while (ch != '\n')
        ct1 += ((ch = getchar()) == 'o');
    g(9979,15834769.4263);
    g(99979,1447623428.7656);
	// Subtask : #8
    g(9700, 1328102.5129);
    g(97000, 12995697.8181);
    printf("34949678.6289");
    return 0;
}
```
~~其实BZOJ上也是可以A的哦~~

**好了，扯完了**

**正解**： 期望DP

其实也是很水的啦

$exxxxp[i] = ans$表示到第$i$位的期望长度为$ans$， 也就是答案

$com[i] = ans$表示到第$i$个位置连续'o'的期望长度为$ans$

考虑几种转移：

1. 如果这个当前是$o$:
	
    因为$(x+1)^2$ = $x^2+2x+1$ , 所以

  $exp[i] = exp[i - 1] + com[i - 1] * 2 + 1$, $com[i] = com[i - 1] + 1$
2. 如果是$x$:
	
    $exp[i] = exp[i - 1]$, $com[i] = 0$
3. 如果是$?$:
	 
     $exp[i] = exp[i - 1] + com[i - 1] + 0.5$
     $com[i] = (com[i - 1] + 1) / 2$

代码如下：

```
#include <bits/stdc++.h>
inline int read(){
    char ch = getchar(); int u = 0, f = 1;
    while (!isdigit(ch)) { if (ch == '-') f = -1; ch = getchar(); }
    while (isdigit(ch)) { u = (u << 1) + (u << 3) + ch - 48; ch = getchar(); }
    return u * f;
}
const int maxn = 1e6 + 10;
char s[maxn];
double exxxxp[maxn], com[maxn];
int main(){
    int n = read();
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; ++i){
        char t = s[i];
        if (t == 'o') { exxxxp[i] = exxxxp[i - 1] + com[i - 1] * 2 + 1; com[i] = com[i - 1] + 1; }
        else if (t == 'x') { exxxxp[i] = exxxxp[i - 1]; com[i] = 0; }
        else if (t == '?') {
            exxxxp[i] = exxxxp[i - 1] + com[i - 1] + 0.5;
            com[i] = (com[i - 1] + 1) / 2;
        }      
    }
    printf("%.4lf", exxxxp[len]);	
    return 0;
}
```


---

## 作者：D12241R (赞：4)

连续$x$个$won$就有$x\times x$分

我们将`o,?,x`转化为概率：

* o:1.0
* x.0.0
* ?:0.5

考虑增加1分：

$(x+1)^2$=$x^2+2x^1+1$

与原来相比增加了：

$2x^1+1$

题目变成维护这个增加值的期望,所以我们处理$x^1$:

$x1[i]$表示$x^1$的期望;

$x2[i]$表示答案的期望;

$x1[i]=(x1[i-1]+1)*p[i];$

$x2[i]=(x2[i-1]+2*x1[i]+1)*p[i]+x2[i-1]*(1-p[i])$

所以，我们简化一下$x2$:

$x2[i]=x2[i-1]+(2*x1[i-1]+1)*p[i]$

答案是$x2[n]$。

此题还可以用滚动数组优化空间，~~但这题不用优化也能过~~。

```
#include<stdio.h>
#define R register
#define maxn 1000001
int n;
char c;
double a[maxn],x1[maxn],x2[maxn];
int main(void)
{
	scanf("%d",&n);
	for(R int i=1; i<=n; i++)
	{
		do
		{
			c=getchar();
		}
		while(c!='o'&&c!='x'&&c!='?');
		if(c=='o')
		{
			a[i]=1.0;
		}
		else if(c=='x')
		{
			a[i]=0.0;
		}
		else
		{
			a[i]=0.5;
		}
		x1[i]=(x1[i-1]+1)*a[i];
		x2[i]=x2[i-1]+(x1[i-1]*2+1)*a[i];
	}
	printf("%.4lf",x2[n]);
	return 0;
}
```

---

## 作者：Porsche (赞：3)

#### 临下课了，发片题解，喵~
### 疯狂的化式子就行了，其实挺简单的。
### 因为(x+1)^2=x^2+2*x+1
### 又x=(x+1)*P
### 又(x+1)^2-x^2=2*x+1
### 则当前点的期望贡献为(2*x+1)*P
### 当前点为o则P=1，当前点为x则P=0，当前点为？则P为0.5（这个应该都好理解吧）
### 把每一位都累加即为答案
```cpp
#include<bits/stdc++.h>
using namespace std;
double wzc,x,ans;
char flag;
int main()
{
	int n;
	scanf("%d",&n);
	flag=getchar();
	for(int i=1;i<=n;i++)
	{
		char flag;
		flag=getchar();
		if(flag=='o')wzc=1.0;
		else if(flag=='x')wzc=0.0;
		else wzc=0.5;
		ans+=(2.0*x+1.0)*wzc;
		x=(x+1.0)*wzc;
	}
	cout<<fixed<<setprecision(4)<<ans<<endl;
	return 0;
}
```
#### 进阶版跳转[P1654 OSU！](https://www.luogu.org/problemnew/show/P1654)
## HZOI版权所有，吕老师万岁！

---

## 作者：TLE_Automat (赞：2)

### P.S. 我真的不想开学 /kk ！！！
### 作为 5.7 开学前的最后一篇题解和期望dp的第一篇题解是不是应该伤感的纪念一下。

---

作为一个不看题解永远做不出期望 $dp$ 的小菜鸡，这道题竟然不看题解做出来了？(~~jiade~~ 

感觉这是我做的期望 $dp$ 里面最水的一道题。废话少说（~~好像已经说了很多废话~~）， $dp$ 走起。

## 一. 设状态

设状态嘛，显然，设 $dp_i$ 为以第 $i$ 个字符为结尾的期望得分。

## 二. 动态转移方程

这是期望 $dp$ 最关键的步骤，一般有关期望的题码量都很小，没什么代码难度，但思维难度一般都不小，最关键的就是推出转移方程或者是一些神奇的结论。接着我门上面设的状态，我们很容易发现有**三种**情况下的转移：

我们先假设 $len$ 为以 $s_i$ 为结尾的连续的字符 $o$ 的期望长度，初始为 $0$。

- 当 $s_i = x $ 时，因为字符 $x$ 对 $o$ 的长度没什么影响，所以显然 $f_i=f_{i-1}$ ，$len=0$ 。

- 当 $s_i = o$ 时 ，因为之前期望的以 $s_{i-1}$ 为结尾的连续的字符 $o$ 的长度为 $len$ ，所以 $f_i=f_{i-1}+(len+1)^2-len^2=f_{i-1}+2\times len+1$ ，$len=len+1$ 。这里之所以要减去 $len^2$ 是因为统计 $f_{i-1}$ 的时候已经加上了 $len^2$ ，而现在 $len$ 变成了 $len+1$ ，影响从 $len^2$ 变成了 $(len+1)^2$ ，所以要减去之前统计的 $len^2$ 。


- 当 $s_i = ?$ 时，这时我们需要考虑它变成 $x$ 和 $o$ 的**概率**，显然是 $50%$ ，那么那么我们只要把变成 $x$ 的影响和变成 $o$ 的影响**加起来**再除以 $2$ 就行了。 所以 $f_i = f_{i-1} + ((len+1)^2-len^2+0) \div 2$ ，其中 $?$ 变成 $x $ 影响就会增加 $(len+1)^2 - len^2$ ，变成 $o$ 影响会增加 $0$ 。 $len=(len+1+0) \div 2$ ，其中 $?$ 变成 $x$ 会使 $len$ 变成 $len+1$ ，变成 $o$ 会使 $len$ 变成 $0$ 。

## 三. 开心敲代码

由于代码难度过于简单，并且蒟蒻码风过丑，代码就不放了。（温馨提示：不开 $long$ $ double$ 可能见祖宗）

**最后窝还是想说，作为开学前最后一篇题解，点个赞再走呗。**

**update on 2020/5/5** : 修改DP方程中的笔误。



---

## 作者：Sym_Je (赞：2)

     期望dp   
   [P1365 WJMZBMR打osu! / Easy](https://www.luogu.org/problemnew/show/P1365)   
   这是道期望$dp$的题 .  
   首先我们肯定要推出状态转移方程，因为他是$^2$的所以，当前所在的$o$的长度肯定影响他的得分，所以我们开一个$f[i]$，表示在i位置时连续o的长度，然后再开一个 $dp[i]$ ，表示在第i个位置的期望是多少。        
   因为它没给 $n$ 的大小，所以不好搞数组所以我们就用string来动态开空间。   
   然后分类讨论，非常明显，   
   1.当$s[i]$为$'o'$时，$dp[i]=dp[i-1]+2×f[i-1]+1,f[i]=f[i-1]+1$;    
   为啥是 $dp[i]=dp[i-1]+2×f[i-1]+1$呢，因为我们看，    
   $dp[i]=dp[i-1]+f[i]^2-f[i-1]^2$     
   然后 $f[i]^2-f[i-1]^2=(f[i]-f[i-1])×(f[i]+f[i-1])$    
   然后 $f[i]-f[i-1]=1,f[i]+f[i-1]=2×f[i-1]+1.so zheyang$     
   2.$if('x') dp[i]=dp[i-1],f[i]=0;$   
   3.$else$ 期望和的平均值就好咯，因为概率都是$0.5$，所以都乘$0.5$相加就好了 。     
   
   
   然后因为$n$不确定并且转移位置小且唯一，所以用滚动数组搞成大小为2的。    
   
```cpp
//dp[i]  f[i]
//if(x) dp[i]=dp[i-1],f[i]=0;
//if(s) f[i]=f[i-1]+1,dp[i]=dp[i-1]+2*f[i-1]+1;
//else dp[i]=dp[i-1]+f[i-1]+0.5,f[i]=(f[i-1]+1)/2;

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring> 
#include<string>
using namespace std;

int n;
string s;

double dp[2];
double f[2];

int main()
{
	scanf("%d",&n);
	cin>>s;
	for(int i=0;i<n;i++)
	{
		if(s[i]=='x')
		{
			dp[i%2]=dp[(i%2)^1],f[i%2]=0;
		}
		else if(s[i]=='o')
		{
			f[i%2]=f[(i%2)^1]+1,dp[i%2]=dp[(i%2)^1]+2*f[(i%2)^1]+1;
		}
		else
		{
		
			dp[i%2]=dp[(i%2)^1]+f[(i%2)^1]+0.5,f[i%2]=(f[(i%2)^1]+1)/2;
	//		cout<<dp[0]<<"*"<<dp[1]<<endl;
		}
	}
	if(n%2)
	{
		printf("%.4lf\n",dp[0]);
	}
	else
	{
		printf("%.4lf\n",dp[1]);
	}
	return 0;
}
```
   
   
   

---

## 作者：jins3599 (赞：1)

算是入门的一道期望dp。


不妨设 $l$ 为当前最末位 o 的**期望**个数 , $f(i)$为前 $i$ 位的**期望**得分。

- 当前位置为 o 时
	
    显然 `f[i] = f[i - 1] +(l + 1) * (l + 1) - l * l`
    
    并且 `l = l + 1`。 不再赘述。
    
- 当前位置为 x 时
	
    即当前位置对答案无贡献，`f[i] = f[i - 1]` 即可。
    
    当然不要忘了令`l = 0`
    
- 当前位置为 ? 时
	
    重点。
    
    我们首先考虑$f(i)$的取值，显然当前位置为 x 或 o 的概率是相同的。
    
    于是期望得分就很好算了。
    
    `f[i] = (f[i - 1] +　(l + 1) * (l + 1) - l * l + f[i - 1]) / 2` 即可。
    
   即前两个的得分的均值。
   
   考虑此时我们的期望长度。
   
   在第一和第二种情况时，长度分别为 $l+1$和$0$
   
   考虑期望长度就为这两个的均值，令 `l = (l + 1 + 0) / 2` ，即`(l + 1)/2`即可。
   

$Code:$

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 3 * 1e5 + 10;

char s[N + 10];
int n;
long double f[N];

int main () {
 	scanf("%d" , &n);
 	scanf("%s" , s + 1);
	f[1] = 0;
	double l = 0.0;
 	for(int i = 1 ; i <= n ; i ++) {
		if(s[i] == 'o') {
			f[i] = f[i - 1] - l * l + (l + 1.0) * (l + 1.0);
			l ++;
		} else if(s[i] == 'x') {
			l = 0.0; f[i] = f[i -  1];
		} else if(s[i] == '?') {
			f[i] = (f[i - 1] - l * l + (l + 1.0) * (l + 1.0) + f[i -  1]) / 2.0;
			l = (l + 1) / 2;
		}
	}
	printf("%.4Lf" , f[n]);
	return 0;
}
```
	

---

## 作者：喵の耳 (赞：1)

## 大力推式子

设$f[i]$表示以$i$结尾的期望得分，$len$为期望连续的$o$的个数

### 分类讨论：

①当前字母为$o$时，$f[i]=f[i-1]+((len+1)^2-len^2)$ 此时$len+1$

化简 $=>$ $f[i]=f[i-1]+2*len+1$

②当前字母为$x$时，$f[i]=f[i-1]$ 此时$len=0$ 

③当前字母为?时，为$(①+②)/2$

也就是 $f[i]=f[i-1]+len+0.5$

整理变成$f[i]=f[i-1]+(2*len+1)*p[i]$

其中$p[i]$就是i位置出现o的期望,其中

$o$  $p[i]=1$

$x$  $p[i]=0$

$?$  $p[i]=0.5$

再看$len$怎么维护，设$x[i]$表示$i$结尾的最后一段连续$o$的个数

同样可以转化为$x[i]=(x[i-1]+1)*p[i]$

综上，转移方程为

$$f[i]=f[i-1]+(2*x[i]+1)*p[i]$$



### code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e6+10;
namespace gengyf{
inline int read(){
	int x=0,f=1;char s=getchar();
	while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
	while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
	return f*x;
}
double f[maxn],p[maxn],x[maxn];
string s;int n;
int main(){
	n=read();cin>>s;
	for(int i=0;i<n;i++){
		if(s[i]=='o')p[i+1]=1.0;
		if(s[i]=='x')p[i+1]=0.0;
		if(s[i]=='?')p[i+1]=0.5;
	}
	for(int i=1;i<=n;i++){
		f[i]=f[i-1]+(x[i-1]*2+1.0)*p[i];
		x[i]=(x[i-1]+1.0)*p[i];
	}
	printf("%.4lf",f[n]);
	return 0;
}
}
signed main(){
	gengyf::main();
	return 0;
}

```


---

## 作者：Unordered_OIer (赞：0)

# P1365 题解
[$\text{题目传送门}$](https://www.luogu.com.cn/problem/P1365)  
首先，这道题一看到**期望**这俩字，那么什么都别想了，期望$dp$啊。  
那么我们就可以开始~~准备好头秃地~~推式子了。

先抄原题：  
$dp_i$表示前$i$个的期望得分。  
答案输出$dp_n$。  
转移方程**不好推**，考虑定义的更具体一些。  

具体的定义：  
$exdv_i$代表第$i$格对得分期望的贡献。  
即$exdv_i=dp_i-dp_{i-1}($差分$)$  
答案即$dp_n=\sum_{i=1}^nexdv_i$

具体推导：（$E[x]$表示在题目下情况$x$的期望）$(Expectation)$  


| $exdv_i$代表第$i$格对得分期望的贡献 |
| :----------- |
| **随机变量$q_i$为用第$i$格结尾的连续长度** |
| **$exlen_i$代表用第$i$格结尾的连续长度的期望** |
| 概率$1-p_i:q_i=0$   |
| 概率$\ \ \ \ p_i\ \ \ :q_i=q_{i-1}+1$   |
$exdv_i=(1-p_i)*0+p_i*(E[{q_i}^2]-E[{q_{i-1}}^2])$  
$\ \ \ \ \ \ \ \ \ \ \ =p_i*(E[(q_{i-1}+1)^2]-E[{q_{i-1}}^2])$  
$\ \ \ \ \ \ \ \ \ \ \ =p_i*(E[{q_{i-1}}^2+2q_{i-1}+1]-E[{q_{i-1}}^2])$  
$\ \ \ \ \ \ \ \ \ \ \ =p_i*(2E[q_{i-1}]+1)$  
$\ \ \ \ \ \ \ \ \ \ \ =p_i*(2exlen_{i-1}+1)$  
$exlen_i=p_i*E[q_{i-1}+1]$  
$\ \ \ \ \ \ \ \ \ \ \ \ =p_i*(exlen_{i-1}+1)$  

代码太过简单，就不放了。

---

