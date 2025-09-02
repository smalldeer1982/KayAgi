# 【MX-S3-T3】「FeOI Round 1」再演

## 题目背景

原题链接：<https://oier.team/problems/S3C>。

---

![](bilibili:BV1rx411E7WH)

## 题目描述

**这是一道交互题。**

jt 有一个大小为 $n$ 的集合 $S$，集合中每个元素都是一个无序二元整数对 $(x, y)$，保证集合中 $1 \sim 2n$ 共 $2n$ 个整数每个恰好出现一次。

比如当 $n = 3$ 时，合法的集合 $S$ 可能是 $\{(1, 5), (2, 3), (4, 6)\}$。

开始时你只知道 $n$ 而不知道 $S$ 具体是什么。

现在支持一种操作：你可以给出 $i, j$（$1 \le i, j \le 2n$），然后 jt 会交换 $i, j$ 在 $S$ 中的位置（如 $i, j$ 在同一个二元组内，或 $i = j$，则什么也不会发生）。

比如，当 $S = \{(1, 5), (2, 3), (4, 6)\}$ 时，执行 $i = 2, j = 6$ 后 $S = \{(1, 5), (6, 3), (4, 2)\} = \{(1, 5), (2, 4), (3, 6)\}$。

在最开始时以及每次操作过后，对于当前的集合 $S$，jt 会告诉你 $res = \min\limits_{(x, y) \in S} \max(x, y)$。

比如，当 $S = \{(1, 5), (2, 3), (4, 6)\}$ 时，$res$ 为 $\min(\max(1, 5), \max(2, 3), \max(4, 6)) = \min(5, 3, 6) = 3$。

注意，每次 jt 告诉你 $res$ 之后**不会撤销**你做的操作，即你的操作是持续有效的。

你需要在 $lim$ 次操作内猜出**初始的**集合 $S$，即进行所有交换操作之前的版本。

保证初始的 $S$ 是提前确定的，即**交互库不自适应**。

### 交互方式

**本题单个测试点内包含多组数据。**

首先读入数据组数 $T$。

接下来有 $T$ 组数据，对于每组数据进行以下过程：

输入 $S$ 的大小 $n$ 以及 $lim$ 以开始交互。

每次操作，首先读入 $res$，接下来输出一行 `^ i j` 表示你要执行操作 $i, j$。

在你确定答案后，请先输出一行一个 `!`，然后接下来 $n$ 行每行输出两个整数 `x y` 代表 $S$ 中的一个二元组，然后准备读入下一组数据。你可以以任意顺序输出这些二元组，且二元组内元素顺序可以任意。

每次在你输出一行后，请清空缓冲区：

- 在 C++ 中，使用 `fflush(stdout)` 或 `cout.flush()`。
- 在 Pascal 中，使用 `flush(output)`。
- 在 Python 中，使用 `stdout.flush()`。
- 其它语言请自行查阅文档。

**当你在单个测试点所有测试数据的总操作次数不超过 $\boldsymbol{2.5 \times 10^5}$ 次时**，保证交互库占用时间不超过 $1\operatorname s$，空间不超过 $128\operatorname{MB}$，也就是你至少能使用 $1 \operatorname{s}$ 的时间以及 $384\operatorname{MB}$ 的空间。

## 说明/提示

**【样例解释】**

注意，样例只是描述了一个可能发生的交互过程，**并不一定存在逻辑**（就是说答案可能是乱猜猜对的）。

对于第一组测试数据，$S$ 最开始为 $\{(1, 5), (2, 3), (4, 6)\}$，jt 告诉你 $res = 3$。

接下来你交换 $1, 2$，$S$ 变为 $\{(2, 5), (1, 3), (4, 6)\}$，jt 告诉你 $res = 3$。

接下来你交换 $3, 6$，$S$ 变为 $\{(2, 5), (1, 6), (3, 4)\}$，jt 告诉你 $res = 4$。

接下来你交换 $6, 2$，$S$ 变为 $\{(5, 6), (1, 2), (3, 4)\}$，jt 告诉你 $res = 2$。

你输出 $\{(5, 1), (6, 4), (2, 3)\}$，用了 $3$ 次操作，不超过 $lim = 100$ 次，回答正确。

对于第二组测试数据，$S$ 初始为 $\{(1, 2)\}$，你直接输出 $\{(1, 2)\}$，用了 $0$ 次操作，不超过 $lim = 0$ 次，回答正确。

**【数据范围】**

**本题开启捆绑测试。**

记 $\sum n$ 为单个测试点内所有的 $n$ 之和。

对于 $100\%$ 的数据，$1 \le T \le 10^5$，$ 1 \le n \le 5 \times 10^4$，$ \sum n \le 10^5$。

| 子任务编号 | $T$ | $n$ | $lim$ | 分数 |
| :-: | :-: | :-: | :-: | :-: |
| $1$ | $=1$ | $=1$ | $=0$ | $1$ |
| $i$（$2 \le i \le 6$） | $=(2i-1)!!$ | $=i$ | $=10^9$ | $8$ |
| $7$ | $\le 5$ | $\le 100$ | $=5n^2$ | $14$ |
| $8$ | $\le 25$| $\le 10^3$ | $=10n$ | $15$ |
| $9$ | $\le 10^5$ | $\le 5 \times 10^4$ | $=\max(0, 2n - 3)$ | $30$ |

$!!$ 代表[双阶乘](https://baike.baidu.com/item/%E5%8F%8C%E9%98%B6%E4%B9%98/9500461)。

## 样例 #1

### 输入

```
2
3 100
3

3

4

2




1 0
2```

### 输出

```



^ 1 2

^ 3 6

^ 6 2

!
5 1
6 4
2 3


!
1 2```

# 题解

## 作者：vegetable_king (赞：8)

出题人题解。

首先有一个转化是我们可以求出最终的集合 $S$，再倒过来进行交换操作得到初始的 $S$。

然后考虑如果获得了一个数 $p$ 之后，你可以把它和 $1$ 交换。因为 $p$ 是所有 pair 中更大值最小的，所以一定有 $p \le o$，其中 $o$ 是与 $1$ 配对的数。

先不考虑 $p = o$ 即 $p$ 与 $1$ 配对的情况，此时有 $p < o$。

那么和 $1$ 交换之前，配对情况显然是 $(q, p), (1, o)$，交换之后配对情况变为 $(1, q), (p, o)$，且有 $q < p < o$，则操作后返回的 $res$ 一定为 $q$。于是我们知道了，在这次操作前 $p, q$ 是配对的，但是这并没有什么用，因为无法确保 $p, q$ 之前没有动过，也无法确保以后不会动。

我们还要找到一个更大的数与 $q$ 配对从而将它覆盖在底下来得到新的 $res$，选择 $2n$ 就可以了。于是交换 $1, 2n$，配对情况变为 $(q, 2n), (p, o)$（如果 $o = 2n$ 则变为 $(q, 2n), (1, p)$，但这并不重要），于是我们成功把 $q$ 覆盖在了底下。而且因为 $2n$ 是全局最大值，只要 $q, 2n$ 这两个数保持配对，那么它们就都不会成为 $res$，可以直接将这两个数删掉，变为一个 $n' = n - 1$ 的子问题。

现在考虑 $p = o$ 的情况。如果是这种情况，交换 $1, p$ 实际上不会产生任何效果，可以通过返回的 $res$ 是否变化来判断。然后我们只需要同样地交换 $1, 2n$ 来覆盖住 $p$ 即可。

最后 $n = 1$ 的时候一定会剩下一个 $1$，而另外一个数就是 $res$，共需要 $2(n - 1)$ 次询问。但是这个 $res$ 是我们能通过之前产生的 pair 推导得出的，所以就可以减少一次询问，做到 $\max(0, 2n - 3)$ 次询问。

[code](https://www.luogu.com.cn/paste/2kbydmb9)

---

## 作者：佬头 (赞：3)

## Description
一个大小为 $n$ 的集合 $S$，其中每个元素都是一个无序二元整数对且保证集合中整数 $1\sim 2n$ 恰好各出现一次。

现有一种操作：你可以给出 $i,j~(1\le i,j\le 2n)$ 并交换 $i,j$ 在 $S$ 中的位置。在最开始及每次操作后，对当前集合 $S$，你会得到 $res=\min\limits_{(x,y)\in S}\max(x,y)$。

请在 $lim$ 次操作内猜出**初始**集合 $S$。

## Solution
显然 $n=1$ 时，$S=\{(1,2)\}$。

初始集合 $S$ 内元素的有用信息只有 $res$，交换 $res$ 容易获得更明确的信息。而对于另一整数对 $(x,y)~(x\lt y)$，交换 $res,y$ 没有意义，则考虑交换 $res,x$。

然而 $(x,y)~(x\lt y)$ 并不好确定，但 $1$ 必然是 $x$。那么我们可以交换 $res,1$：
- 若 $(1,res)\in S$，则 $res'=res$；
- 若 $(1,res)\notin S$，对于 $(a,res),(1,y)$，显然有 $1\lt a\lt res\lt y$，那么交换后 $\min(\max(1,a),\max(res,y))=a$，则 $res'=a$。

因此第一步交换 $res,1$ 后可以确定 $(1,res')\in S'$。此时若 $n=2$，即可得出 $S$，操作次数恰好等于 $2n-3$。

然而 $(1,res')$ 极易影响我们对 $S'$ 信息的获取，因此考虑交换 $res',2n$，这样一个完美的整数对 $(1,2n)$ 就出现了，我们称 $1,2n$ 已配对。

然后依葫芦画瓢找思路：在所有未配对的整数中取最小值 $minn$ 和最大值 $maxx$，对于 $res_1$：
- 先交换 $res_1,minn$，得到 $(minn,res_2)\in S_1$；
  - 若此时有 $n-2$ 对整数已配对，即可确定 $S$，操作次数恰好为 $2n-3$。
- 再交换 $res_2,maxx$，得到 $(minn,maxx)\in S_2$，则 $minn,maxx$ 已配对。

最后将 $S_{2n-3}$ 通过交换操作倒推出 $S$ 即可，时间复杂度为 $\mathcal O(n)$。

## Code

```cpp
#include <iostream>
#define output(x,y) write(x),putchar(' '),write(y),putchar('\n'),fflush(stdout)
#define change(x,y) swap(par[x],par[y]),swap(x,y)
using namespace std;
const int N = 100005;
int n, par[N], minn, maxx, cnt, s1[N], s2[N], top;
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(int x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
void turn(int x, int y){
	s1[++ top] = x, s2[top] = y;
	fputs("^ ", stdout), output(x, y);
	change(par[x], par[y]);
}
int main(){
	for(int t = read(); t; -- t){
		n = read(), read();
		if(n == 1){
			read(), fputs("!\n1 2\n", stdout), fflush(stdout);
			continue;
		}
		minn = 1, maxx = n << 1, top = cnt = 0;
		for(int i = 1; i <= maxx; ++ i) par[i] = i;
		for(int res = read(); ; res = read()){
			if(res != minn + 1) turn(res, minn), res = read();
			if(par[res] == res) swap(par[res], par[minn]), ++ cnt;
			if(cnt + 1 == n) break;
			turn(res, maxx), ++ minn, -- maxx;
		}
		while(top) change(par[s1[top]], par[s2[top]]), -- top;
		fputs("!\n", stdout);
		for(int i = n << 1, t = 0; i >= 1; -- i)
			if(par[i] != -1)
				if(par[i] == i) t? output(i, t): t = i;
				else output(i, par[i]), par[par[i]] = -1, par[i] = -1;
		fflush(stdout);
	}
	return 0;
}
```

---

## 作者：JuRuoOIer (赞：2)

# 题解 P10887 【MX-S3-T3】「FeOI Round 1」再演

前排提示：本题为**结论题**。本篇题解**旨在阐述笔者是怎么想出来的**，希望能给大家以自然的思路。

题意略，[原题面](https://www.luogu.com.cn/problem/P10887)挺清楚的。

### 花絮

做本题时是把题印出来拿学校去做的。于是花了近三节自习课（约 $110\ \text{min}$）并通过包括但不限于
- 自制了 $1$ 到 $12$ 的数字卡片
- 与同位（没学过 OI）轮流当交互库
- 手玩数据玩了三页 A4 演算纸

等的方法，才发现这是大唐题。

### 思路

文中“$a$ 的另一边”指 $a$ 所在二元组中的另一个数。

开局的时候我们只有一个 $res_0$。所以我们需要搞到更多的数字。

因此我们希望先搞到 $res_0$ 的另一边是多少。容易想到有一个一定比 $res_0$ 小的东西是 $1$，于是猜想直接拿 $res_0$ 和 $1$ 换一手就可以把另一边换出来。证明：
- 当 $1$ 和 $res_0$ 在同一二元组中，即存在二元组 $(1,res_0)$ 时：
  - 换完后仍然是 $(1,res_0)$，返回值 $res=res_0$；
- 否则，即存在二元组 $(1,a)$ 和 $(b,res_0)$：
  - 操作完后变为 $(1,b)$ 和 $(res_0,a)$；
  - 根据返回值的意义我们知道 $b<res_0<a$，即 $(1,b)$ 中较大值为 $b$，$(res_0,a)$ 中较大值为 $a$，这两个取较小值后为 $b$；
  - 又因为其他二元组中的较大值均大于 $res_0$，因此返回 $res=b$。

综上，若使用 $1$ 和当前的 $res_0$ 进行交换后返回 $res$，则此时必存在一个二元组 $(1,res)$。

于是为了得到更多数字，我们希望 $b$ 不再贡献。因此给 $b$ 的另一边安排上 $2n$，即使用 $1$ 与 $2n$ 进行交换，这样以后该二元组就被固定了。

这个过程可以进行 $(n-2)$ 次，消耗 $(2n-4)$ 次操作。每次操作完第一步之后用于固定得到的数字的值依次减一即可。

现在还可以进行一次操作。我们仍然延续刚才的思路，通过一次操作来获取一个 $(1,res)$，这样最后剩下的两个数就是最后一个二元组了。操作的时候记录一下，并于输出时复原即可。

### 小细节

- 代码中的 `x` 和 `t` 两个数组需要操作的范围是到值域的，因此记得开二倍。
- $n=1$ 需要特判，而且记得 $n=1$ 时也要读入一个 $res$。

### 代码

```cpp
ll T,n,lim,res,l[50010],r[50010],x[100010],t[100010];
int main(){
	ios::sync_with_stdio(0);
	cin>>T;
	while(T--){
		cin>>n>>lim;
		if(n<=1){
			cin>>lim;//注意这里要读一下 
			cout<<'!'<<endl<<1<<' '<<2<<endl;
			continue;
		}
		ll p=n*2,res;
		for(int i=1;i<=n*2;i++)x[i]=i;//初始化 x 数组 
		for(int i=0;i<n-2;i++){
			//按思路部分的步骤操作即可 
			cin>>res;
			cout<<"^ 1 "<<res<<endl;
			swap(x[1],x[res]);//记录实时位置 方便输出时恢复 
			cin>>res;
			cout<<"^ 1 "<<p<<endl;
			swap(x[1],x[p]);
			l[i]=res;r[i]=p;
			p--;
		}
		cin>>res;
		cout<<"^ 1 "<<res<<endl;
		swap(x[1],x[res]);
		memset(t,0,sizeof(t));//多测不清空，爆零两行泪 
		cin>>res;
		l[n-2]=1;r[n-2]=res;
		cout<<'!'<<endl;
		for(int i=0;i<n-1;i++){
			cout<<x[l[i]]<<' '<<x[r[i]]<<endl;//记得恢复 
			t[l[i]]=1;t[r[i]]=1;
		} 
		for(int i=1;i<=2*n;i++){
			if(!t[i])cout<<x[i]<<' ';//最后剩的两个数在一个二元组中 
		} 
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Hoks (赞：2)

## 前言
难度不高的有趣交互题，但是我硬控我自己 $1.2$ 小时。
## 思路分析
交互题，啥思路也没有，怎么办。

那先开数据范围吧，一看 $n=1,lim=0$ 这个显然就是特判了，直接特判掉就行了。

然后观察发现给的 $lim=\max(0,2n-3)$，$0$ 显然是 $n=1$ 的时候了，所以 $n>1$ 时 $lim=2n-3$，考虑下这个 $2n-3$ 应该怎么来。

总共是 $n$ 组数，我们如果剥出来 $n-1$ 组，那么最后一组就直接确定了，所以我们是 $n-1$ 组使用 $2n-3$ 次询问。

又因为最开始就给了我们一个数，所以相当于是共有 $2n-2$ 次询问，平均下就是两组询问处理一组。

接着来考虑怎么做到两组询问一组数。

假设询问得到的第一个数为 $x$，那么 $x$ 这组内目前的情况肯定就是 $x,y$，其中 $y<x$。

我们考虑制作极端情况，交换 $1,x$，这个时候假设得到的数为 $z$，那么就有两种情况：
1. $z=x$，说明 $1,x$ 一组。
2. $z<x$，说明目前是 $1,z$ 一组，之前即是 $x,z$ 一组。

那这样我们一次询问就确定了一组，接下来第二次询问即是消去这组对答案的贡献，避免影响其他组。

考虑我们用目前还没用过的最大的数 $mx$ 来去掉这组的贡献，即为交换 $1,mx$，这时我们消去了 $z$ 的贡献，同时把 $1$ 换了出来。

但是，这里有个问题，就是 $1$ 这时候的位置其实是原本 $mx$ 的位置，而 $x$ 的位置其实是原本 $1$ 的位置。

所以这个时候我们要对每个 $i$ 记录一个 $mp_i$，代表 $i$ 这个数对应的位置**原本**是哪个数的。

最后找到还未出现过的两个数扔进一组即可。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,V=5e4,M=3,INF=0x3f3f3f3f,mod=1e9+7;
int n,lim,x,y,mp[N],a[N];set<int>s;vector<pair<int,int>>ans;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    // #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void ask(int x,int y){cout<<"^ "<<x<<" "<<y<<endl;lim--;}
inline void solve()
{
    n=read(),lim=read();if(n==1){read();return cout<<"!\n"<<1<<" "<<2<<endl,void();}s.clear();
    for(int i=1;i<=(n<<1);i++) s.insert(i),mp[i]=i,a[i]=0;ans.clear();assert(n>1);
    for(int i=1;i<n;i++)
    {
        x=read(),ask(1,x);y=read();
        if(y==x)
        {
            ans.emplace_back(mp[1],mp[x]);s.erase(mp[x]);a[mp[1]]=a[mp[x]]=1;
            if(i==n-1) break;int mx=*(--s.end());ask(1,mx);mp[1]=mp[mx];s.erase(mx);
        }
        else
        {
            ans.emplace_back(mp[x],mp[y]),s.erase(mp[x]),s.erase(mp[y]);a[mp[x]]=a[mp[y]]=1;mp[x]=mp[1];
            if(i==n-1) break;int mx=*(--s.end());ask(1,mx);mp[1]=mp[mx];s.erase(mx);
        }
    }cout<<"!\n";x=0;for(int i=1;i<=n<<1;i++) if(!a[i]&&x) ans.emplace_back(i,x);else if(!a[i]) x=i;
    for(auto [x,y]:ans) cout<<x<<" "<<y<<endl;
}
signed main()
{
    int T;T=read();while(T--) solve();
    genshin:;return 0;
}
```
彩蛋，赛时的我 solve 函数第一行的特判，return 前忘记读入了硬控 $1.2$ 小时不过。

---

## 作者：Muse_Dash (赞：1)

与官方题解思路一样。

记录一个二元组 $(a,b)$ 的**上数、下数**分别为 $\max\{a,b\},\min\{a,b\}$。那么，答案所求即为 $S$ 内所有二元组的上数最小值。

显然，$1$ 必定作为所有下数的 $\min$，而 $2n$ 为所有上数的 $\max$。在开始得到 $res$ 并将其与 $1$ 交换，可以得知原本与 $res$ 所在同一组内的另一个数 $res'$。再将 $res'$ 与 $2n$ 交换，使得 $1,2n$ 为同一组，可以考虑删掉 $(1,2n)$，由 $2,2n-1$ 分别取代下数 $\min$ 和上数 $\max$，以此往复。

在知道 $n-1$ 个组之后，最后一个也显而易见。通过 $2n-2$ 次操作达到理想的效果，并反推可以得到原来的 $S$。但实际上，在知道 $n-2$ 个组后，剩余两组只需要一次操作，这是很容易优化的，因为你完全可以只用一次操作来得到其中一组，而再用一次操作去拼凑 $(n-1,n+2)$ 实际上是无用的。

比较极端的情况就是给的 $res$ 对应组内另一元素为 $1$，那么交换 $1,res$ 之后返回值依然为 $res$，特判即可。

```cpp
cin>>n>>lim>>p;
l=1,r=2*n,tip=0;
while (r-l>1){
	cout<<"^ "<<l<<' '<<p<<endl;
	opt[++tip]={l,p},cin>>q;
	if (r-l==3) break;
	cout<<"^ "<<r<<' '<<q<<endl;
	opt[++tip]={r,q},l++,r--;
	cin>>p;
}
for (int i=1;i<=n-2;i++){
	e[i]={i,2*n-i+1};
	to[i]=i,to[2*n-i+1]=i;
}
if (p==q) e[n-1]={p,l},e[n]={(p==n+1?n:n+1),r},to[p]=n-1,to[l]=n-1,to[(p==n+1?n:n+1)]=n,to[r]=n;
else e[n-1]={p,q},e[n]={l,r},to[p]=n-1,to[q]=n-1,to[l]=n,to[r]=n;
for (int i=tip-1;i>=1;i--){
	int x=opt[i].fr,y=opt[i].sc;
	if (to[x]==to[y]) continue;
	e[to[x]].fr==x?e[to[x]].fr=y:e[to[x]].sc=y;
	e[to[y]].fr==y?e[to[y]].fr=x:e[to[y]].sc=x;
	swap(to[x],to[y]);
}
cout<<"!\n";
for (int i=1;i<=n;i++)
	cout<<e[i].fr<<' '<<e[i].sc<<'\n';
cout<<endl;
```

---

## 作者：Lu_xZ (赞：1)

### 再演

初始集合只要记录操作然后从当前集合回退即可。

定义**上数**为一对数中较大的，同理定义**下数**。

返回的 $p$ 是所有上数中最小的。

$p$ 与 $1$ 交换，$1$ 与原来 $p$ 的下数 $q$ 组成 $(1, q)$。

由于 $p$ 已经是上数中最小的了，$q$ 比 $p$ 还小，因此一定有 $res = q$，我们称该操作将 $q$ **暴露**出来。

$q$ 与 $2n$ 交换，得到 $(1, 2n)$。

无论如何 $2n$ 不会作为返回值，因此可以把 $(1, 2n)$ 删掉，递归到一个值域为 $[2, 2n - 1]$ 的子问题。

边界情况是只有一个数对 $(n, n + 1)$，不用询问，直接返回。

这样总询问数等于 $2n - 2$，比 $2n - 3$ 的限制多了一次。

考虑值域为 $[n - 1, n + 2]$ 的情况，res 一定是 $n$ 和 $n + 1$ 之一，我们的目的是将 $(n, n + 1)$ 凑对，因此无需 $2$ 次操作，只需一次交换。

具体分讨见代码。

```cpp
#include<bits/stdc++.h>
#define eb emplace_back
#define ep emplace
using namespace std;

using ll = long long;
constexpr int N = 1e5 + 5;

int n, lim, res, a[N], p[N];
stack<pair<int, int>> s; 

void ask(int i, int j) {
	s.ep(i, j);
	cout << "^ " << i << ' ' << j << endl;
	cin >> res;
}
void dfs(int l, int r) {
	if(l == n) return;
	if(l == n - 1) {
		if(res == n) ask(n, n + 2);
		else {
			/*
			(n + 1, n)  (n + 2, n - 1)
			(n + 1, n - 1)  (n + 2, n)
			*/
			ask(n + 1, n - 1);
			s.pop();
			if(res == n + 1) s.ep(n, n - 1);
		}
		return;
	}
	ask(res, l);
	ask(res, r);
	dfs(l + 1, r - 1);
}
void solve() {
	cin >> n >> lim >> res;
	dfs(1, 2 * n);
	for(int i = 1; i <= 2 * n; ++ i) {
		a[p[i] = i] = i;
	}
	while(!s.empty()) {
		auto [i, j] = s.top();
		s.pop();
		swap(a[p[i]], a[p[j]]);
		swap(p[i], p[j]);
	}
	cout << '!' << endl;
	for(int i = 1; i <= n; ++ i) {
		cout << a[i] << ' ' << a[2 * n - i + 1] << endl;
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	int T;
	cin >> T;
	
	while(T --) {
		solve();
	}
	return 0;
}
```

---

## 作者：_Ch1F4N_ (赞：0)

不妨令当前交互库给出的值为 $now$。

我们发现对于任意 $1 \leq i < now$ 其所在集合中另一个数一定大于 $now$，由此可得 $now \leq n+1$，那么 $now$ 所在集合中另一个数小于等于 $n$，我们考虑维护出所有还没有确定集合中另一个数的小于等于 $n$ 的数的集合，我们猜测 $now$ 所在集合中另一个数具有某种单调性，不妨令另一个数为 $p$，我们在 $[1,now)$ 中二分一个还没有确定另一个数的 $mid$，并尝试交换 $now$ 与 $mid$，我们发现由于 $now$ 被换到的集合另一个数大于 $now$ 所以不会对给出的数产生影响，因此给出的数应当是 $\min(mid,p)$，由于我们知道了 $p$，所以假若 $\min(mid,p) = now$ 说明 $mid = p$，假若 $\min(mid,p) < p$ 则 $\min(mid,p) = p$ 总之确定了 $p$ 和此时 $p$ 所在集合另一个数 $mid$ 后，我们把当前最大的还没有确定集合中另一个数与 $mid$ 交换，之后这个数与 $p$ 就不会产生贡献，我们把其丢掉，然后递归处理，否则就继续二分。

注意到我们令 $mid$ 等于当前最小没有确定集合中另一个数的数，那么就不会继续接着二分，而是会直接花费两次交换确定一个当前的集合，我们考虑对于集合中只剩下两个数的情况手动构造一种更优的方案即可在 $2 \times n - 3$ 次花费内确定当前的集合，一步步撤销即可还原原来的集合。


```cpp
#include<bits/stdc++.h>
using namespace std;
//#define int long long
//#define lowbit(x) (x&(-x))
//#define bp push_back
//#define sz size
//#define cl clear
const int maxn = 1e5+114;
int n,lim;
vector< pair<int,int> > opt;//进行过的操作
set<int> S;//小于等于 n 的数中还没有被删去的数 
int q[maxn<<1];//确定的当前匹配 
void solve(int now,int R){
	//cout<<now<<' '<<R<<'\n';
	if(S.size()==2){
		int a=(*S.begin());
		S.erase(a);
		int b=(*S.begin());
		S.erase(b);
		if(now==b){
			q[a]=b;
			q[b]=a;
			q[R]=R-1;
			q[R-1]=R;
		}else{
			cout<<"^"<<' '<<b<<' '<<R-1<<endl;
			opt.push_back(make_pair(b,R-1));
			int New;
			cin>>New;
			if(New==now){
				q[b]=R-1;
				q[R-1]=b;
				q[a]=R;
				q[R]=a;
			}else{
				q[a]=b;
				q[b]=a;
				q[R]=R-1;
				q[R-1]=R;
			}
		}
		return ;
	}
	if(S.size()==1){
		q[(*S.begin())]=R;
		q[R]=(*S.begin());
		S.clear();
		return ;
	}
	int p=(*S.begin());
	cout<<"^"<<' '<<p<<' '<<now<<endl;
	opt.push_back(make_pair(p,now));
	int res;
	cin>>res;
	if(res==now){
		//p就是与 now 匹配的点
		cout<<"^"<<' '<<now<<' '<<R<<endl;
		q[p]=R;
		q[R]=p;
		opt.push_back(make_pair(now,R));
		S.erase(p);
		int New;
		cin>>New;
		solve(New,R-1);
		return ;
	}else if(res>p){
		//此时 res 与 p 配对了
		cout<<"^"<<' '<<res<<' '<<R<<endl;
		q[p]=R;
		q[R]=p;
		opt.push_back(make_pair(res,R));
		S.erase(p);
		int New;
		cin>>New;
		//cout<<"F"<<'\n';
		solve(New,R-1);
		return ;	 
	}
}
void work(){
	cin>>n>>lim;
	opt.clear();
	for(int i=1;i<=n;i++) S.insert(i),q[i]=q[n+i]=0; 
	int now;
	cin>>now;
	if(n==1){
		cout<<"!"<<endl<<1<<' '<<2<<endl;
		return ;
	}
	solve(now,2*n);
	for(int i=opt.size()-1;i>=0;i--){
		int u=opt[i].first,v=opt[i].second;
		if(q[u]==v){
			continue;
		}else{
			int Qu=q[u];
			int Qv=q[v];
			//交换 u,v
			q[Qu]=v;
			q[v]=Qu;
			q[Qv]=u;
			q[u]=Qv;
		}
	}
	cout<<"!"<<endl;
	for(int i=1;i<=2*n;i++){
		if(q[i]>i) cout<<i<<' '<<q[i]<<endl;
	} 
}
int main(){
	int t;
	cin>>t;
	while(t--) work();
	return 0;
}
```

---

