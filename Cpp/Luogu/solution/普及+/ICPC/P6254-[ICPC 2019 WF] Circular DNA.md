# [ICPC 2019 WF] Circular DNA

## 题目描述

你在一个研究 DNA 的生物信息学研究小组实习。单链 DNA 由许多基因组成，这些基因分为不同的类别，称为基因类型。基因类型由特定的核苷酸序列分隔，称为基因标记。每个基因类型 $i$ 有一个唯一的起始标记 $\texttt s_i$ 和一个唯一的结束标记 $\texttt e_i$。经过许多繁琐的工作（如细菌培养、细胞提取、蛋白质工程等），你的研究小组可以将 DNA 转换为仅由基因标记组成的形式，去除标记之间的所有遗传物质。

你的研究小组提出了一个有趣的假设，即基因的解释取决于某些基因类型的标记是否形成了正确的嵌套结构。要确定基因类型 $i$ 的标记在给定的标记序列 $w$ 中是否形成了正确的嵌套结构，需要考虑 $w$ 的子序列，其中只包含基因类型 $i$ 的标记（$\texttt s_i$ 和 $\texttt e_i$），不遗漏任何一个。以下（且仅以下）被认为是正确的嵌套结构：

- $\texttt s_i \texttt e_i$
- $\texttt s_i N \texttt e_i$，其中 $N$ 是一个正确的嵌套结构
- $AB$，其中 $A$ 和 $B$ 是正确的嵌套结构

鉴于你的计算背景，你被分配去研究这个性质，但还有一个进一步的复杂性。你的小组正在研究一种称为环状 DNA 的特定类型的 DNA，这种 DNA 形成一个闭合的环。为了研究环状 DNA 中的嵌套，有必要在某个位置切开环，这会产生一个唯一的标记序列（读取方向由分子性质固定）。基因类型 $i$ 是否形成正确的嵌套现在也取决于环状 DNA 的切割位置。你的任务是找到最大化形成正确嵌套结构的基因类型数量的切割位置。图 D.1 显示了对应于样例输入 1 的一个例子。所示的切割导致基因类型 1 的标记正确嵌套。

## 说明/提示

来源：ICPC 2019 世界总决赛。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
9
e1 e1 s1 e2 s1 s2 e42 e1 s1```

### 输出

```
3 1```

## 样例 #2

### 输入

```
8
s1 s1 e3 e1 s3 e1 e3 s3```

### 输出

```
8 2```

# 题解

## 作者：比利♂海灵顿 (赞：8)

校内 ICPC 模拟赛考到了此题，考完后发现考场代码喜提本体最优解 （虽然本来就没几个提交）。这道题很多人都是用 `<set>` 设计的 $O(nlogn)$ 的算法，这里就介绍**一个 $O(n)$ 的算法**。

## 题目分析

这个题面不是很好懂，校内赛中因为不明确 $s$，$e$ 后面数字的意思耽误了很长时间。字母后面跟的这个数字是基因的编号，编号相同的基因是同种基因，可以认为每种基因都是独立的，$s1$，$e1$ 之间就算有再多其它种类的基因也不影响 $s1$ 和 $e1$ 的匹配。

注意断开的位置 $p$ 的意思是在第 $p$ 个基因前面切割。

顺着当时做这道题的思路，我们来循序渐进地做这道题。

## 真核生物

众所周知，原核生物的 DNA 是环状的，但是显然环状 DNA 比真核生物的链状 DNA 复杂，所以先考虑链状 DNA 的完美匹配种数。

将 $s$ 看出上括号，权值为 $1$，$e$ 看成下括号，权值为 $-1$，这就是一个括号匹配问题。将同种基因求权值的前缀和。由于每个编号的基因互不影响，所以不同编号基因的前缀和分别记录。

对于权值总和不等于 $0$ 的编号，无论怎么切都切不出完美匹配的情况。对于总和等于 $0$ 的编号，至少有一种切法可以使它完美匹配。

一个编号的基因是完美匹配的条件有两个，一个是总和等于零，另一个是任何时候前缀和大于等于 $0$，只要维护这个编号的前缀和的最小值即可。

所以对于真核生物，只要扫一遍 DNA 链，过程中统计权值总和和前缀和最小值，最后枚举所有编号，统计满足上面两个条件的编号数量即可。时间复杂度 $O(n)$。

## $O(n^2)$

在考场上，有时需要先打复杂度高的算法然后再尝试优化，既减少了思考更优算法的难度，也能给这个题的得分兜底（当然 ACM 没有部分分）。

对于环形问题一般解法是断环为链，将环断成链后复制一份接在原来的链后面。

具体操作是在外层循环枚举断点，对于每个断点 $i$，都有 $[i, i + n - 1]$ 是以 $i$ 为断点切开的 DNA 链。每个断点跑一遍链式 DNA 的算法即可，复杂度 $O(n^2)$。

## 递推

先跑一遍真核生物的算法，考虑如何递推地求出每个断点的情况。

考虑断点向右移动，会有哪些影响？

显然是 DNA 左端基因接到右端去。假设这个基因编号是 $x$，则容易知道这次断点的移动只影响 $x$ 这一种编号的基因，因为其他编号的基因的相对位置不变。

前面已经说明，如果 $x$ 编号的所有基因权值总和不是 $0$，无论断点如何，永远不会完美匹配，所以只要这时左端基因的权值总和不是 $0$，直接跳到下一个断点即可。

规定编号 $x$ 的基因的权值总和为 $Sum_x$，本断点（端点不同前缀和最小值不同）的前缀和最小值为 $Low_x$，当前完美匹配数量为 $Tmp$。

如果 $Sum_x = 0$，那么这个编号的基因有可能是完美匹配（第一个条件符合）。一个基因的位置移动不影响这个编号的基因的权值总和。所以只要看移动这个基因后对 $Low_x$ 的影响如何即可。

对左端的基因分类讨论。

- 这个基因是 $sx$

  这是一个左括号，它在左端时给所有前缀和提供了一个加数 $1$，所以去掉它后，所有位置上，编号 $x$ 的基因权值前缀和都减少 $1$，$Low_x$ 也必然减少 $1$。

  因为 $Sum_x = 0$，所以前缀和最小值最大情况是 $0$，所以移动后的第 $x$ 种基因的前缀和最小值一定小于等于 $-1$，不可能完美匹配。

  修改 $Low_x$ 之前，对于原本 $Low_x = 0$ 的情况，失去了一个完美匹配，所以这一轮的最多匹配数量是 $Tmp - 1$。

- 这个基因是 $ex$

  这是一个右括号，它在左端时给所有前缀和提供了一个加数 $-1$，所以去掉它后，所有位置上，编号 $x$ 的基因权值前缀和都增加 $1$，$Low_x$ 也必然增加 $1$。

  给 $Low_x$ 加 $1$ 后，就有可能出现 $Low_x = 0$ 的情况，这时出现一个新的完美匹配 $x$（在此之前 $Low_x = -1$，不是完美匹配），及时更新 $Tmp$ 为 $Tmp + 1$。

枚举断点同时统计 $Tmp$，并且对于每个断点，尝试更新所有断点中最优的匹配数量 $Ans$ 和断点 $Pos$。因为在 $Tmp$ 相同时，优先输出小的断点，所以只有 $Tmp > Ans$ 时更新两个变量，最后直接输出 $Pos$ 和 $Ans$ 即可。

因为只是简单地扫上常数次序列，所以显然时间复杂度是 $O(n)$。

## 注意

- 在 $sx$ 情况，先判断 $Low_x = 0$，再修改 $Low_x$；在 $ex$ 的情况，先更新 $Low_x$，再判断 $Low_x = 0$。

- 枚举断点时只考虑左端点，所以这种算法不用复制一遍原序列接在后面，直接在原序列中找左端点即可。

- 代码中为了方便设计程序，枚举的断点 $i$ 的意义和 $p$ 不同。$i$ 的意义是在第 $i$ 个基因后面断，$p$ 的意义是在第 $p$ 个基因前面断。

## 代码

一些细节都在代码注释中，应该会很好懂吧。

```cpp
#include <cstdio>
#include <iostream>
#define Wild_Donkey 0
using namespace std;
unsigned n, Cnt(0), Ans(0), Tmp(0), List[1000005], Pos(0);
char Character;
int Sum[1000005], Low[1000005];
struct DNA {
  unsigned Number;  // 编号 
  int SE;           // s or e, 即权值 
}a[1000005];
int main() {
  scanf("%u", &n);
  for (register unsigned i(1); i <= n; ++i) { // 读入 
    Character = getchar();
    while (Character != 's' && Character != 'e') {
      Character = getchar();
    }
    if(Character == 's') {                    // 上括号 
      a[i].SE = 1;
    }
    else {                                    // 下括号 
      a[i].SE = -1;
    }
    scanf("%u", &a[i].Number);
    if(!Low[a[i].Number]) {                   // 这个编号的基因首次出现
      Low[a[i].Number] = 1;                   // 打标记表示这个编号的基因出现过 
      List[++Cnt] = a[i].Number;              // 记录在基因列表中 
    }
  }
  Pos = 1;
  for (register unsigned i(1); i <= n; ++i) {
    Sum[a[i].Number] += a[i].SE;              // 累计总和 
    Low[a[i].Number] = min(Low[a[i].Number], Sum[a[i].Number]); // 更新前缀和历史最小值 
  }
  for (register unsigned i(1); i <= Cnt; ++i) {// 真核生物  (枚举基因编号)
    if(Low[List[i]] == 0 && Sum[List[i]] == 0) {// 同时满足两个条件 
      ++Tmp;
    }
  }
  Pos = 1, Ans = Tmp;                         // 对于真核生物的运行结果
  for (register unsigned i(1); i < n; ++i) {  // 枚举断点, 这里是从 i 后面切断, 所以原左端基因是 a[i] 
    if(!(Sum[a[i].Number] ^ 0)) {             // 优化常数, 等价于 if(Sum[a[i].Number] == 0) 
      if(a[i].SE ^ (-1)) {                    // 优化同上, 这是 sx 的情况 
        if(!(Low[a[i].Number] ^ 0)) {         // 原本完美, 修改后不完美了 
          --Tmp;
        }
        --Low[a[i].Number];                   // 最后修改 Low[x] 
      }
      else {                                  // 这是 ex 的情况 
        ++Low[a[i].Number];                   // 先修改 Low[x] 
        if(!(Low[a[i].Number] ^ 0)) {         // 原本不是完美匹配, 但是现在完美了 
          ++Tmp;
        }
      }
    }
    if(Tmp > Ans) {                           // 新断点严格优于原先才更新 
      Pos = i + 1;
      Ans = Tmp;
    }
  }
  printf("%u %u", Pos, Ans);
  return Wild_Donkey;
}
```

## 鸣谢 & 后记

感谢 [@巴菲特](https://www.luogu.com.cn/user/171851) 踩了我的考场代码，但是幸好我用一发新的提交守住了最优解（当然这种题的最优解没什么用，是个人随便卡卡常就能比我快）。算法竞赛中人们以 A 题为目的，很少有人有能快则快能省则省的工程精神。但是追求完美的精神却让我受益匪浅，希望 OI 能给每个人留下受益终身的财富而不仅是名校的垫脚石。

---

## 作者：qwer6 (赞：1)

[你谷传送门](https://www.luogu.com.cn/problem/P6254)。

我们首先考虑拆环成链，然后考虑对于每一个长度为 $n$ 的子区间求解答案取最值即可。

但是，对于每一个子区间都模拟求解显然是一个无法承受的，极其夸张的时间复杂度，直接 Pass，而显然的，当区间左端点从 $l$ 转移到 $l+1$ 的时候，合法性可能变化的只有 $l$ 对应的类，因此我们考虑快速求解出 $l$ 对应的类在 $[l+1,l+n]$ 区间中的合法性。

对于类合法的条件，一眼直接打为括号序，考虑括号序的常见判断方式，任意前缀中左括号都不少于右括号，换到这道题中，也就是将 $s$ 视为 $1$，$e$ 视为 $-1$，对于每一类分别做前缀和，然后查询在 $[l+1,l+n+1]$ 中这一类的最小值，看一下是否大于 $l$ 这个位置的前缀和即可。

看上去不太好维护，实际上，如果你脑子确实因为学习 DS 严重受损的话，现在已经可以准备动态开点线段树之类清奇的操作了，或者，像我一样，给每一类在线段树中规定一段存储的区间，只要查询对应的一段即可保证类与类之间不相互干扰。

注意每一个数组都可能有开两倍，甚至四到八倍的需求，请留意分辨。

这里给出一个示例：

```c++
inline void input(){
	read(n);
	char c;
	for(int i=1;i<=n;i++){
		cin>>c;
		tmp[i]=read(id[i]);
		tp[i]=(c=='s'?1:-1);
	}
	sort(tmp+1,tmp+n+1);
	tot=unique(tmp+1,tmp+n+1)-tmp-1;
	for(int i=1;i<=n;i++)id[i]=lower_bound(tmp+1,tmp+tot+1,id[i])-tmp;
}
inline void init(){
	for(int i=1;i<=n;i++)id[i+n]=id[i],tp[i+n]=tp[i];
	for(int i=1;i<=2*n;i++){
		pre[i]=pre[las[id[i]]]+tp[i];
		las[id[i]]=i;
	}
	for(int i=1;i<=tot;i++)las[i]=0,place[i].push_back(0);
	for(int i=1;i<=2*n;i++){
		las[id[i]]++;
		place[id[i]].push_back(i);
		c[i]=las[id[i]];
	}
	for(int i=1;i<=tot;i++)L[i]=R[i-1]+1,R[i]=L[i]+las[i]-1;
	for(int i=1,p;i<=2*n;i++){
		p=L[id[i]]+c[i]-1;
		Set.change(1,1,2*n,p,p,pre[i]);
	}
}
inline void update(int _p,int _ans){
	if(ans<_ans){
		ans=_ans;
		p=_p;
	}
}
inline void First(){
	int res=0;
	for(int i=1,x,y;i<=tot;i++){
		x=Set.query(1,1,2*n,L[i],L[i]+las[i]/2-1);
		y=Set.query(1,1,2*n,L[i]+las[i]/2-1,L[i]+las[i]/2-1);
		if(x>=0&&y==0)res++;
	}
	p=1,ans=res;
}
inline int cal(int idx,int begin_time){
	int end_time=begin_time+las[idx]/2-1;
	int Pre=place[idx][begin_time-1];
	return Set.query(1,1,2*n,L[idx]+begin_time-1,L[idx]+end_time-1)-pre[Pre];
}
inline bool check(int idx,int begin_time){
	if(cal(idx,begin_time)<0)return false;
	if(begin_time==las[idx]+1)begin_time=1;
	int end_time=begin_time+las[idx]/2-1;
	int Pre=place[idx][begin_time-1];
	int y=Set.query(1,1,2*n,L[idx]+end_time-1,L[idx]+end_time-1)-pre[Pre];
	return y==0;
}
inline void solve(){
	int res=ans;
	for(int i=2,idx;i<=n;i++){
		idx=id[i-1];
		if(check(idx,c[i-1]))res--;
		if(check(idx,c[i-1]+1))res++;
		update(i,res);
	}
}
```

 可以发现代码长度十分逆天，加上线段树之后可以达到 $4.5K$ 的长度。

虽然这样就直接过了，[但是](https://www.luogu.com.cn/record/200432922)最慢的点拿到了 $1.84s$ 的骄人成绩，并且喜提洛谷最劣解……

好吧我承认这种做法时间复杂度确实是正确的 $O(n\log n)$，但是常数有一点大了。

但是这优秀的思维量，合理的码量，对于时空限制的充分利用，难道不是正解吗？

好吧确实不是，从上面的分析中，我们可以发现对于每一类之间，合法性完全是割裂的，也就说，我们可以把每一类分开处理，这样就避免了上面将线段树分成若干个小区间的窘境。

但是为什么要线段树？不是区间大小恒定的，左端点单向移动的 RMQ 问题吗？那为什么要线段树呢？为什么不选用优秀的单调队列呢？
具体的，对于每一类分开讨论，对于假定现在讨论到第 $x$ 类，且 $x$ 类在原序列中出现了 $cnt$ 次，当前是枚举到的区间是 $x$ 第 $begin$ 到 $end$ 次出现。

那么同样的，我们将 $s$ 视为 $1$，$e$ 视为 $-1$，跑一次前缀和，然后对于 $begin$ 到 $end$ 查询区间最小值，使用单调队列维护，如果不小于 $pre_{begin-1}$，那么在 $x$ 第 $begin$ 次出现的后一个位置到第 $begin$ 次出现的位置都是合法的，区间加一，可以直接差分。

注意一个特殊问题，就是如果 $begin$ 就是 $1$，也就是 $x$ 第一次出现的位置，并且确实合法，那么不仅 $1$ 到 $x$ 第一次出现的位置是合法的，并 $x$ 最后一次出现的后一个位置到 $n$ 也是合法的，需要特判。

最后的时间复杂度就是优秀的 $O(n)$，并且比上面那个代码快了几倍。

```c++
#include<bits/stdc++.h>
#define Nxt puts("")
#define Spa putchar(32)
#define Pline puts("------------------------------")
namespace FastIO{
	int write_top,read_f,read_x;
	char read_char;
	int write_st[20];
	inline int read(int &a){
		read_char=getchar();
		read_f=1;
		a=0;
		while(!isdigit(read_char)){
			if(read_char=='-')read_f=-1;
			read_char=getchar();
		}
		while(isdigit(read_char)){
			a=(a<<1)+(a<<3)+(read_char^48);
			read_char=getchar();
		}
		return a=a*read_f;
	}
	inline int read(){
		read_char=getchar();
		read_f=1;
		read_x=0;
		while(!isdigit(read_char)){
			if(read_char=='-')read_f=-1;
			read_char=getchar();
		}
		while(isdigit(read_char)){
			read_x=(read_x<<1)+(read_x<<3)+(read_char^48);
			read_char=getchar();
		}
		return read_x*read_f;
	}
	inline void write(int x){
		if(x<0)putchar('-'),x=-x;
		write_top=0;
		do{
		   write_st[++write_top]=x%10;
		   x/=10;
		}while(x);
		while(write_top)putchar(write_st[write_top--]+'0');
		return ;
	}
	inline void tomax(int &a,int b){
		if(a<b)a=b;
		return ;
	}
	inline void tomin(int &a,int b){
		if(a>b)a=b;
		return ;
	}
}
using namespace FastIO;
using namespace std;
const int N=1e6+5;
int n,p;
int id[N<<1],tp[N<<1],pre[N<<1],ans[N<<1];
vector<int>place[N];
struct deq{
	int head,tail;
	int q[N];
	void clear(){head=1,tail=0;}
	void pop_front(){head++;}
	void pop_back(){tail--;}
	void push_back(int v){q[++tail]=v;}
	int front(){return q[head];}
	int back(){return q[tail];}
	bool empty(){return head>tail;}
}q;
inline void input(){
	read(n);
	char c;
	for(int i=1;i<=n;i++){
		cin>>c;
		id[n+i]=read(id[i]);
		tp[n+i]=tp[i]=(c=='s'?1:-1);
	}
	n<<=1;
	for(int i=1;i<=n;i++)place[id[i]].push_back(i);
}
inline void solve(){
	for(int i=1,m;i<=1000000;i++){
		m=place[i].size();
		if(!m)continue;
		q.clear();
		for(int j=0;j<m;j++)pre[j+1]=pre[j]+tp[place[i][j]];
		if(pre[m])continue;
		m>>=1;
		for(int j=1;j<m;j++){
			while(!q.empty()&&pre[q.back()]>=pre[j])q.pop_back();
			q.push_back(j);
		}
		for(int r=m;r<m*2;r++){
			while(!q.empty()&&pre[q.back()]>=pre[r])q.pop_back();
			q.push_back(r);
			while(!q.empty()&&q.front()<=r-m)q.pop_front();
			if(pre[q.front()]<pre[r-m])continue;
			if(r==m){
				ans[1]++,ans[place[i][0]+1]--;
				ans[place[i][m-1]+1]++;
			}else ans[place[i][r-m-1]+1]++,ans[place[i][r-m]+1]--;
		}
	}
	for(int i=1;i<=n;i++)ans[i]+=ans[i-1];
	p=1;
	for(int i=2;i<=n;i++)
		if(ans[p]<ans[i])
			p=i;
}
signed main(){
	input();
	solve();
	write(p),Spa,write(ans[p]),Nxt;
}
```

---

## 作者：内拉组里 (赞：1)

模拟 $ \cdot $ 优化。

# Pts 20

将 $ s_i $ 视为左括号，$ e_i $ 视为右括号，不同的 $ i $ 对应不同的括号种类，

题意转化为在序列的循环排列中选择一种使得最多种类的括号全部匹配的方案。

暴力模拟先。

拆环成链，枚举起点。

然后用栈模拟匹配过程，判断合法性。

## Analyses：

> 总时间复杂度 $ \Theta (N^2) $。
>
> 总空间复杂度 $ \Theta (N) $。

***

# Pts 100

括号匹配基操。

在暴力的基础上，将左括号视为 $ 1 $，右括号视为 $ - 1 $，对每一种括号分别跑前缀和。

只要这一种括号的前缀和最小值 $ \ge 0 $，并且左右括号在数量上合法，那么这一种括号就合法。

考虑维护每种括号的最小值以及左右括号数量差，计算答案时只考虑数量上合法的括号种类。

实际上在枚举相邻起点时只有**被从队首拎到队尾的那一个括号所属的括号种类的最小值**会变。

所以在枚举起点是只需要实时维护每种括号的最小值即可。

对此会出现两种情况：

- 左括号，那么该种类的括号前缀和会整体 $ - 1 $，

  若最小值从 $ 0 $ 降到了 $ - 1 $，那么说明移动起点时把原本合法的括号序列非法化，

  故合法括号种类数应 $ - 1 $。

- 右括号，那么该种类括号的前缀和会整体 $ + 1 $，

  若最小值从 $ -1 $ 升到了 $ 0 $，那么说明原本非法的括号序列现在合法了，

  合法括号种类数应 $ + 1 $。

显然地，每种括号的前缀和的最小值 $ \le 0 $，否则这一种左右括号在数量上就不合法了，

故不可能出现左括号使最小值 $ 1 \rightarrow 0 $，或右括号使最小值 $ 0 \rightarrow 1 $。

最后对左右括号数量上合法的括号种类进行答案统计即可。

讲的有点抽象，自己对着样例模拟一下就明白了。

## Analyses：

> 总时间复杂度 $ \Theta (N) $。
>
> 总空间复杂度 $ \Theta (N) $。

# Code：

```cpp
/* reference : @Luogu.143771 */
#include	<iostream>
#include	<cstring>
#include	<vector>
#include	<set>
using namespace std;
using pii = pair<int,int>;				//operation type,gene type
constexpr int maxn = 2e6+4;

namespace pts20
{
	int n, knd;
	int buc[maxn];
	int vis[maxn];
	pii a[maxn << 1];
	
	signed main (void)
	{
		cin >> n;
		for (int x, i = 1; i <= n; i++)
		{
			char ch = getchar ();
			while (!isalpha (ch)) ch = getchar ();
			cin >> x;
			if (ch == 's')
				a[i] = a[n + i] = {1, x};
			else
				a[i] = a[n + i] = {-1, x};
		}
		set<int> knd;
		for (int i = 1; i <= n; i++)
			knd.insert(a[i].second);
		int idx, ans = 0;
		for (int st = 1; st <= n; st++)
		{
			int res = knd.size();
			for (int i = st; i <= st + n - 1; i++) if (!vis[a[i].second])
			{
				if ((buc[a[i].second] += a[i].first) < 0)
				{
					vis[a[i].second] = 1;
					buc[a[i].second] = 0;
					res--;
				}
			}
			if (ans < res)
			{
				ans = res;
				idx = st;
			}
			for (auto i : knd) if (vis[i])
			{
				vis[i] = 0;
				buc[i] = 0;
			}
		}
		cout << idx << ' ' << ans << endl;
		return 0;
	}
}

namespace pts100
{
	int n;
	pii a[maxn];
	int mn[maxn];
	int sum[maxn];
	int vis[maxn];
	vector<int> gene;
	
	signed main (void)
	{
		cin >> n;
		for (int x, i = 1; i <= n; i++)
		{
			char ch = getchar ();
			while (!isalpha (ch)) ch = getchar ();
			cin >> x;
			if (ch == 's')
				a[i] = a[n + i] = {1, x};
			else
				a[i] = a[n + i] = {-1, x};
			if (!vis[x])
			{
				vis[x] = 1;
				gene.push_back(x);
			}
		}
		memset (mn, 0x3f, sizeof mn);
		for (int i = 1; i <= n; i++)
		{
			sum[a[i].second] += a[i].first;
			mn[a[i].second] = min (mn[a[i].second], sum[a[i].second]);
		}
		int cnt = 0;
		for (auto i : gene)
		{
			if (!mn[i] && !sum[i])
			{
				cnt++;
			}
		}
		int idx = 1;
		int ans = cnt;
		for (int i = 1; i < n; i++)
		/* cut off i from the head and append */
			if (!sum[a[i].second])
			/* complete type sequence */
		{
			if (a[i].first == 1)
			/* left bracket */
			{
				if (!mn[a[i].second]--)					/* complete -> incomplete */
					cnt--;
			}
			else
			/* right bracket */
			{
				if (!++mn[a[i].second])					/* incomplete -> complete */
					cnt++;
			}
			if (ans < cnt)
			{
				ans = cnt;
				idx = i + 1;
			}
		}
		cout << idx << ' ' << ans << endl;
		return 0;
	}
}

signed main (void)
{
	return pts100::main ();
}
```

---

## 作者：lzx1999 (赞：1)

### 题目:

一个长度为 n 的环形 DNA 序列，以顺时针顺序给出，其中每个基因有类型和编号两个属性，类型是 s（头）或 e（尾）中的一种，而编号是 1 到 106​ 中的整数。 你需要在某个地方切断，按照顺时针顺序拉成链后，最大化能够完美匹配的基因编号个数。

一个基因编号 i 是能够完美匹配的，当且仅当它在链中对应的所有基因，将 s 看作左括号，e 看作右括号，可以匹配成非空的合法括号序列。

如果有多个位置满足最大化的条件，输出最小的位置。

输入第一行一个整数 n (1≤n≤106)，表示DNA序列的长度，第二行是DNA序列，包含 nn 个元素，每个元素有一个字符 c∈\{s,e\}（s 表示切割时以这个元素为开始还是结束，s 表示开始,e 表示结束）和一个整数 i (1 \le i \le 10^6) 表示基因类型。可以通过在任意位置切割，从环状DNA获得给定的DNA序列。

输出一行包含两个整数 p 和 m , p是切割位置，可最大化能够完美匹配的基因编号个数，m 是能够完美匹配基因类型的最大数量如果多个切割位置产生相同的最大值 m，输出最小的 p。

### 题目大意:  
将环状序列抽出一条长度为n的链,使其完美匹配的个数尽可能多

首先对有环状的问题一般来说就是将长度为n的环变成一个长度为2n,3n的一条链,然后求解

或者向类似于这道题的

首先算出来1~n这条链的符合题意的答案,这个是可以O(n)求解的,然后每次O(1)转移算出来对于每个i~(i+n)%n的结果

首先我们可以计算出每一个e和s之间的绑定关系,0表示没有绑定,非0表示绑定的那个位置坐标,

对于一个s我们可以将其放到对应的set中,遇到一个对应的e我们可以取出对应的set中的最后一个元素相互绑定

当然我是提前判断了一下对于某些元素是有可能匹配成功的和没有可能匹配成功的,

考虑对于每一个s,要放到最后肯定只有两种情况,一种是本身绑定了一个e,一种是没有绑定e,

然后如果绑定的那个放到最后一定是成为一个未绑定e的存在,因此如果之前绑定的那个e寻找一些对应的set中的首元素是否满足情况如果有的话,这部对答案的操作是没有任何影响的

对应e的话,本身一定不是一个绑定的存在,因此向后方一定会遇到和在set里面未绑定对应e的s绑定,或者不影响任何存在
```cpp
//下列代码若为声明的话出现s和e表示的是对应值相同改的s和e

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

#define eps 1e-9
#define endl '\n'
#define gcd __gcd
#define pi acos(-1)
#define ll long long
#define LL long long
#define IDX(x) x - 'A'
#define idx(x) x - 'a'
#define idz(x) x - '0'
#define ld long double
#define lowebit(x) x&(-x)
#define rint register int
#define Len(x) (int)(x).size()
#define all(s) (s).begin(), (s).end()
using namespace std;
inline int read()
{
	register int x = 0, f = 1, ch = getchar();
	while( !isdigit(ch) ){if(ch == '-') f = -1; ch = getchar();}
	while( isdigit(ch) ){x = x * 10 + ch - '0'; ch = getchar();}
	return x * f;
}
set <int> a[3000005]; // a[i]表示编号i中未能完成配对的s(左括号)的存在
int p[3000005]; // p中记录任意一个数对应被绑定的另一个数的位置,未被绑定值未0
pair<int, bool> //c[3000005]; c[i]中记录第i个读取值的信息
bool kt[3000005]; //记录i是否可能存在完美匹配的情况
set<int> k[3000005]; // 计算最开始的序列答案
int ff[3000005]; // 记录e和s是否相等
int32_t main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    clock_t c1ockck = clock();
    int n; cin >> n;
    int ans = 0, res = 1;// 记录最后答案
    int mmm = -1;
    for(int i = 1 ; i <= n ; i ++)
    {
        string s; cin >> s;
        rint t = 0;
        for(int j = 1 ; j < Len(s) ; j ++) t = t * 10 + idz(s[j]); // 读入信息
        kt[t] = true; // 在这个时候表示t是出现过的值
        mmm = max(t, mmm); // 求一下给出的最大值
        if(s[0] == 'e')
        {   
            ff[t] --; // 会抵消一个s,可以是未出现的s,值可以为负
            if(Len(a[t])) // 如果集合a[t]中有元素(表明有之前配对的s出现)
            {
                auto x = *(--a[t].end()); // 提取最后一个未出现的信息
                p[i] = x;
                p[x] = i; // 记录对应的绑定信息
                a[t].erase(x); // 删除未绑定的s的信息
                
            }
            else
            {
                k[t].insert(i); /
            }
        }
        else
        {
            ff[t] ++; // 会抵消一个e,可以是未出现的e,这个数组有用的信息只有0的值
            a[t].insert(i); //新加入的s一定是未配对的s
        }
        c[i] = make_pair(t, s[0] != 'e'); // 记录值的信息
    }
    for(int i = 1 ; i <= mmm ; i ++)
    {
        if(kt[i] && !Len(a[i]) && !Len(k[i])) ans ++; // 记录1~n存在的答案
        if(!ff[i] && kt[i]) kt[i] = false; // 将可以达成的信息标记未false,不能达成的标记为true
        else kt[i] = true;
    }
    int t_ans = ans; //转移最多只会从ans改变一个
    for(int i = 1 ; i <= n ; i ++) // i表示第i个是链的末尾,i+1为链首 
    {
        if(c[i].second == 0)  // 如果当前是e
        {
            if(Len(a[c[i].first])) // 并且存在未匹配的s, 因为当前的e是最后一个元素,因此对于存在的s一定会匹配上
            {
                auto x = *(--a[c[i].first].end()); // 为了方便取出来的是最后一个放进去的s
                 p[x] = i + n; 
                p[i + n] = x; //此时的s对应的恰好是相当于多了一圈的i,因此对应方式未i+n
                a[c[i].first].erase(x); // 匹配成功的删除
                if(!Len(a[c[i].first]) && !kt[c[i].first])t_ans ++; // 凑成新的完美匹配答案+1
            }
        }
        else
        {
            if(p[i]) // 如果被配对的是
            {
                p[p[i]] = 0; // 对应的e会被解除配对关系
                a[c[i].first].insert(i + n); // 一定是未被配对的存在
                auto x = *a[c[i].first].begin();
                if(p[i] > x && Len(a[c[i].first])) // 为了方便取出来对应的最小的值判断就ok
                {
                    p[p[i]] = x;
                    p[x] = p[i];
                    a[c[i].first].erase(x); // 成立新的绑定关系,
                }else
                {
                    if(!kt[c[i].first] && Len(a[c[i].first]) == 1) t_ans --; // 上面的情况一定不会达成一个新的完美匹配和接触完美匹配的状态,只有这种情况才能解除完美匹配的状况
                }
            }
        }
        if(t_ans > ans) // 更新答案
        {
            res = i + 1;
            ans = t_ans;
        }
       //cout << i + 1<< " : T_ans = " << t_ans << " ans = " << ans << " res = " << res << endl;
    }
    cout << res << " " << ans << endl;
    cerr << endl << "Time:" << clock() - c1ockck << "ms" <<endl;
    /**srO**/return 0;/**Orz**/
}
```

---

## 作者：YingLi (赞：1)

ps：做法可能有点复杂并且细节比较多，但是思路总归是正确的【

因为每个i之间相互独立，所以肯定是分别提出来做。

并且可以发现这跟括号匹配是一样的，只是多了一个环形。

一个断开后的链合法，当且仅当**每个括号的存在都合法**，所以开头一定是一个si，结尾一定是ei，期间不会出现cnt[si]<cnt[ei]的情况。

这里我们复制一遍序列来断环。以前括号匹配的时候用到的是栈，这里因为复制了一遍所以有长度限制，所以用双端队列来维护。如果开头的超出了当前结尾对应的区间长就head++，如果当前是e并且队列里有数就tail--。如果当前是e而且当前长度有一个周期并且操作过后队列空了，则以当前e结尾的就是一个合法的序列。回到环上的话，在当前e到下一个s/e之间断环都是合法的。

用树状数组标记对于每个i的合法区间，最后查询前缀和看哪个点被覆盖的次数最多并且最靠前即可。因为倍长了序列所以总长要开到3e6【开6e6是因为怕炸……】。详细解释看代码。



```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cmath>
#include<queue>
#include<map>
#define maxn 6000006
using namespace std;
typedef long long ll;
const int mx = 3e6;
int read() {
	int x = 0, f = 1, ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
	return x * f;
}

int n;
char a[maxn][10];
int t[maxn], sum[maxn];
int q[maxn << 1], head, tail;//往死里开大了……
void add(int x, int d) {for(; x <= mx; x += (x & -x)) t[x] += d;}
int ask(int x) {int res = 0; for(; x; x -= (x & -x)) res += t[x]; return res;}

struct node {int num, p;};
vector<node> v[maxn];
signed main() {
	n = read();
	for(int i = 1; i <= n; i++) scanf("%s", a[i]);
	for(int i = 1; i <= n; i++) {
		register int x = 0;
		for(int j = 1; j < strlen(a[i]); j++) x = (x << 1) + (x << 3) + a[i][j] - '0';
		v[x].push_back({a[i][0] == 's'? 1 : -1, i});
	}//v[i]放的是si和ei。
	
	for(int i = 1; i <= mx; i++) {
		register int lim = v[i].size(), tmp = 0, len; len = lim;
		if(!lim) continue;//没有se，跳过
		for(int j = 0; j < lim; j++) tmp += v[i][j].num;
		if(tmp != 0) continue;//se数量不等，跳过
		for(int j = 0; j < lim; j++) v[i].push_back({v[i][j].num, v[i][j].p + n});//倍长
		v[i].push_back({v[i][0].num, v[i][0].num + n * 2});//加一个尾
		
		lim = v[i].size(); head = 1, tail = 0;
		for(int j = 0; j < lim - 1; j++) {
			while(head <= tail && q[head] < j - len + 1) head++;
			if(head > tail && v[i][j].num < 0) continue;//e比s多了
			if(v[i][j].num < 0) tail--; else q[++tail] = j;//正常操作
			
			if(head > tail && j >= len - 1 && v[i][j - len + 1].num > 0) 
				add(v[i][j].p, 1), add(v[i][j + 1].p, -1);//这个区间内断环对这个序列都是合法的
		}
	}
	
	register int ans_p = 0, ans_x = n * 2;
	for(int i = 1; i <= n * 2 + 1; i++) sum[i] = ask(i), ans_p = max(ans_p, sum[i]);
	for(int i = 1; i <= n * 2 + 1; i++) if(sum[i] == ans_p) ans_x = min(ans_x, (i % n) + 1);
	printf("%d %d\n", ans_x, ans_p);
	return 0;
}
```


---

## 作者：_JF_ (赞：0)

[P6254 [ICPC2019 WF] Circular DNA ](https://www.luogu.com.cn/problem/P6254)

很好，独立一遍切了这道有意思的模拟。

先把这个切割的过程看成从 $1$ 开始，每个点轮流做开头的过程，然后很容易考察到，不同种类是独立的。

比如说我在从 $2$ 当开头，到下一个 $3$ 当开头，其实对于 $1$ 左右括号的形态其实并不发生变化。

问题转化成了同种类内的一个问题，具体的就是一个括号序列，每次把开头扔到结尾，问你括号序列是否合法。

这东西应该可以上线段树做吧，但是我想了一会没想到。。。。

先判掉不可能造成贡献的情况，那就是左右括号不相同。

于是开始考察性质。我们不妨维护还没有匹配的左右括号数量为 $l,r$。

- 如果当前开头是 `(`，把他调整到末尾后，会是 `l++,r++`。

为什么呢？

我们思考为什么一个括号序列会不匹配，那显然是出现了 `)(` 这样的状物。但是当前在开头的是 `(`，所以当前 `(` 一定被匹配了。

- 如果在开头是 `)`，那么 `l--,r--`。

原因和上文类似。

然后对于当前的开头，如果 $l=r=0$，那么它在原序列能造成的贡献段就是，从当前种类的上一个括号的后一个位置，到当前位置为止。

当然因为这是个环，所以对于每个种类开始的那个括号我们特殊处理。

因为我们只最后查询一次，所以我们容易维护这个贡献，差分即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =3e6+10;
//#define int long long
struct node{
	int op,id;
};
vector<node> g[N];
stack<int> sta;
int n,t[N],pre[N],maxx,p;
void Slove(int u){
	while(!sta.empty())	sta.pop();
	int num=0,siz=(int)g[u].size(),lstLeft=0,lstRight=0;
	if(siz%2!=0)	return ;
	for(int i=0;i<siz;i++)	num+=g[u][i].op;
	if(num!=siz/2)	return ;
	for(int i=0;i<siz;i++){
		if(g[u][i].op==0)	sta.push(i);
		else{
			if(!sta.empty())	sta.pop();
			else	lstRight++;
		}
	} 
	lstLeft=(int)sta.size();
	for(int i=0;i<siz;i++){
		if(lstLeft==0&&lstRight==0){
			if(i!=0)	t[g[u][i-1].id+1]++,t[g[u][i].id+1]--;
			else t[g[u][siz-1].id+1]++,t[g[u][i].id+n+1]--;
			if(i==siz-1)	break;
		}
		if(g[u][i].op==0)	lstLeft++,lstRight++;
		else	lstRight--,lstLeft--;
	}
}
signed main(){
	cin>>n;
	for(int i=1,x;i<=n;i++){
		char c; cin>>c>>x,maxx=max(maxx,x);
		g[x].push_back({((c=='e')?1:0),i}); // 1 is right   
	}
	for(int i=1;i<=maxx;i++)	if((int)g[i].size())	Slove(i);
	for(int i=1;i<=2*n;i++)	t[i]+=t[i-1];
	for(int i=1;i<=n;i++)	pre[i]=t[i]+t[i+n],p=max(p,pre[i]);
	for(int i=1;i<=n;i++)	if(pre[i]==p)	cout<<i<<" "<<p<<endl,exit(0);
	return 0;
}

```

---

## 作者：mrclr (赞：0)


这道题挺有意思的，而且自己搞了一个和大多数题解不一样的解法，不用证明那个奇怪的结论。

首先我们枚举断环为链的地方$i$。对于从$i-1$到$i$，相当于只把元素$a_i$挪到了序列最后，因此最多只会影响一个基因编号所在的括号序列，那么我们可以把每一个基因编号单独考虑，分别求出把当前最前面的括号挪到了后面后，这个括号序列是否是合法的。最后扫一遍就能得出答案。

具体思路是这样的：
首先我们可以排除左右括号总数不相等的基因编号，因为这样的括号序列一定是不合法的。

对于剩下的序列，以其中基因编号为$x$的序列为例：

判断括号序列是否合法，就是要保证任何时刻左括号数目不少于右括号数目，这个把左括号看成1，右括号看成-1，求一遍前缀和$sum$就行。如果$min\{sum_i\} \geqslant 0$，那么括号序列就合法（经过第一步筛选已经保证了左右括号数目相等）

现在要将第一个括号挪到最后，我们考虑对他后面的$sum_i$的影响：如果第一个括号为左括号，那么后面的$sum_i$都要-1；如果第一个括号为右括号，那么后面的$sum_i$都要+1，这样操作完后就能用同样的方法判断括号序列是否合法了。

所以我们现在要用单次$O(1)$或者$O(logn)$的复杂度来实现一下操作：

1.删除队首元素

2.向队尾添加元素

3.队列中的所有元素+1/-1.

4.查找队列中的最小值。

操作1和2好办；先不考虑3操作，操作4可以用set维护，只不过取set首元素的时候要判断是否已经被当做队首删除，若删除了就不要，直到取到一个没被删除的或者当做队尾新添加的元素。

现在有了操作3，我们可以换一个思路：保持队列中的元素不变，单独开一个变量$A$记录队列所有元素变化了多少，那么最后判断是否小于0的时候只要跟$A$比较而不是0就好了。

这样我们就在单次$O(logn)$的时间复杂度内实现了上述操作：即动态判断一个序列是否合法。

最后我们对于每一个断点$x$，记$ans[x]$表示将$a_x$挪到后面后他所在的基因编号的括号序列的变化情况：是从合法变成不合法，还是从不合法变成了合法，还是没有改变。这样我们扫一遍就能统计每一个断点对应的合法的括号序列个数了。

```c++
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<cctype>
#include<vector>
#include<queue>
#include<set>
#include<assert.h>
#include<ctime>
using namespace std;
#define enter puts("") 
#define space putchar(' ')
#define Mem(a, x) memset(a, x, sizeof(a))
#define In inline
#define forE(i, x, y) for(int i = head[x], y; ~i && (y = e[i].to); i = e[i].nxt)
typedef long long ll;
typedef double db;
const int INF = 0x3f3f3f3f;
const db eps = 1e-8;
const int maxn = 1e6 + 5;
In ll read()
{
	ll ans = 0;
	char ch = getchar(), las = ' ';
	while(!isdigit(ch)) las = ch, ch = getchar();
	while(isdigit(ch)) ans = (ans << 1) + (ans << 3) + ch - '0', ch = getchar();
	if(las == '-') ans = -ans;
	return ans;
}
In void write(ll x)
{
	if(x < 0) x = -x, putchar('-');
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}

int n, N = 0, Max = 0, pos = 1;
bool vis[maxn];
struct Node
{
	int flg, id;	
}t[maxn];

char ss[20];
In void change(int x)
{
	t[x].flg = (ss[0] == 's') ? 1 : -1;
	int tp = 0, len = strlen(ss);
	for(int i = 1; i < len; ++i) tp = tp * 10 + ss[i] - '0';
	N = max(N, tp), vis[t[x].id = tp] = 1;
}

struct Set
{
	int val, p, New;		//val是对应的前缀和，p表示第几个元素，New表示是否是当做队尾新加入的 
	In bool operator < (const Set& oth)const
	{
		if(val ^ oth.val) return val < oth.val;
		if(New ^ oth.New) return New < oth.New;
		return p < oth.p;
	}
};
#define sSet set<Set>::iterator
vector<int> v[maxn];
set<Set> s;
int sum, las = 1;
In int init(int ID)
{
	s.clear();
	sum = 0, las = 1;
	for(int i = 0; i < (int)v[ID].size(); ++i) 
	{
		sum += t[v[ID][i]].flg;
		s.insert((Set){sum, v[ID][i], 0});
		if(sum < 0) las = 0;
	}
	if(sum) las = 0;
	return las;
}

int ans[maxn];
bool ha[maxn];                                                      	       //表示这个元素是否已经被当做队首删除
In void solve(int ID)
{
	int A = 0;
	for(int i = 0; i < (int)v[ID].size(); ++i)
	{
		int p = v[ID][i];
		A += t[p].flg, ha[p] = 1;
		s.insert((Set){A, p, 1});
		while(1)
		{
			sSet it = s.begin(); Set tp = *it;
			if(ha[tp.p] && !tp.New) s.erase(it);		      //当前set首元素无效 
			else 
			{
				bool flg = (tp.val - A) >= 0;
				if(las ^ flg)				      //判断括号序列的变化情况 
				{
					ans[p] = las ? -1 : 1;
					las ^= 1;
				}
				break;
			}
		}
	}
}

int main()
{
	n = read();
	for(int i = 1; i <= n; ++i)
	{
		scanf("%s", ss);
		change(i);
	}
	for(int i = 1; i <= n; ++i) v[t[i].id].push_back(i);	//存每一个基因编号对应的括号序列 
	for(int i = 1; i <= N; ++i) if(v[i].size())
	{
		Max += init(i);
		if(!sum) solve(i);
	}
	int Ans = Max, pos = 1;
	for(int i = 1; i <= n; ++i) 
	{
		Max += ans[i];
		if(Max > Ans) Ans = Max, pos = i + 1;
	}
	write(pos), space, write(Ans), enter;
	return 0;
}
```

---

