# [BalticOI 2015] Bowling

## 题目描述

Byteasar 是一个保龄球和统计学的爱好者。他记录了一些过去保龄球比赛的结果。不幸的是，笔记中的一些字符模糊不清，因此无法辨认。Byteasar 请你编写一个程序来计算与他的笔记一致的不同游戏的数量。

## 保龄球规则

一场保龄球比赛由 $n$ 局组成：$n-1$ 个简单局和一个最后局。在典型的比赛中 $n = 10$。在每局开始时，10 个瓶子被竖直放置在球道的末端，玩家最多有两次（最后一局有三次）机会（投球）将保龄球投向球道，尽可能多地击倒瓶子。每局用两个（对于简单局）或三个（对于最后局）字符表示。

对于每次投球，玩家获得的基本分数是该次投球击倒的瓶子总数。玩家在每局的基本分数是该局所有投球的基本分数之和。如果在一个简单局中击倒了所有 10 个瓶子（因此获得了 10 个基本分数），玩家会获得额外的奖励分数。

对于简单局，规则如下：

- 如果玩家在一局的第一次投球中击倒了所有 10 个瓶子，她获得一个全中，局结束。作为奖励分数，她获得下一次两次投球的基本分数之和。全中记为 “`x-`”。
- 如果玩家在一局的两次投球中击倒了所有 10 个瓶子，她获得一个补中。作为奖励分数，她获得下一次投球的基本分数。补中记为 “`A/`”，其中 $A$ 是描述该局第一次投球击倒瓶子数的数字。
- 如果在两次投球后击倒了 9 个或更少的瓶子，玩家只获得基本分数，这样的局记为 “`AB`”，其中 $A$ 是第一次投球击倒的瓶子数的一个数字，$B$ 是第二次投球击倒的瓶子数的一个数字 $(A + B < 10)$。

注意，奖励分数被计入获得全中或补中的局的分数中，尽管确切的奖励分数取决于下一局的投球。

对于最后局，规则如下：

- 玩家在此局最初有两次投球。如果在两次投球中击倒了 9 个或更少的瓶子，局结束。否则（如果前两次投球是补中或第一次投球是全中），玩家在此局获得第三次投球。每当玩家在三次投球中的任何一次击倒所有瓶子时，瓶子会为下一次投球恢复到初始状态。最后局的分数是击倒的瓶子总数（注意，由于全中和补中没有奖励分数）。
- 总共有七种可能的最后局配置，结果如下（$A$ 和 $B$ 代表一位数的数字）：

![](https://cdn.luogu.com.cn/upload/image_hosting/vz466ecx.png)

每场比赛被描述为一个 $2n + 1$ 个字符的序列。在比赛结束时，可以计算每局后的总分数。例如，对于一个由 “`08x-7/2/x-x-23441/0/x`” 描述的 $n = 10$ 局的比赛，玩家在各局后的分数如下：

![](https://cdn.luogu.com.cn/upload/image_hosting/6arspls8.png)

## 说明/提示

**示例解释：** 在第一个例子中，在第 5 局中，在字符 “`x`” 之后，唯一可能的字符是 “`-`”。在第 8 局中，玩家总共获得了 8 分。因此，有 9 种可能的方式获得这个总和：$0 + 8, 1 + 7, ..., 8 + 0$。在第 9 局中没有奖励分数。因此，在最后一局的第一次投球中没有分数。为了在最后两次投球中获得 20 分，唯一的可能性是补中，接着在该局的最后一次投球中全中。因此，有 9 个不同的有效比赛与此输入数据相符。

在第二个例子中，任何从 $0$ 到 $9$ 的字符都与输入数据一致。

以下子任务和评测无关，仅供参考。

![](https://cdn.luogu.com.cn/upload/image_hosting/v8uz3sto.png)

（但是我开不了 5 个 Subtask，所以就放在一起测了）

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2
10
08x-7/2/x?x-23??1/???
8 -1 40 60 82 97 102 110 120 140
5
x-x-23?/00-
22 37 42 52 52```

### 输出

```
9
10```

# 题解

## 作者：qiuzx (赞：2)

## 题意

对于一个 $n$ 局的保龄球的分数记录，其中有一些位置是未知的，求有多少种将未知的位置填上值的方式使得存在一个局面得到这个分数记录。$n\le 10$。

## 思路

一个自然的想法就是记 $dp_{i,j}$ 表示考虑了前 $i$ 局，前面累计分数 $j$ 分的方案数。然而这么记录的问题在于一局的分数不仅仅由它自己决定，还和后面的分数有关。但由于数据范围特别小，所以不妨暴力一些，由于至多后面两次投掷的分数会影响前面的得分，所以记 $dp_{i,j,x,y}$ 表示前 $i$ 局累计分数为 $j$，下一局的分数需要为 $x$，下两局分数之和需要为 $y$ 的方案数。这里 $x\in[0,10],y\in[0,20]$，如果没有 $x$ 或 $y$ 的限制则记为 $11$ 和 $21$ 即可。

考虑这个 dp 如何转移。首先最后一局很特殊，所以最后算答案的时候单独考虑即可。对于前面的局，枚举这一局的得分（包含奖励分），以及两次投掷的分数分别是什么。设这局的得分为 $d$，则这里分为三种情况转移：

1. 这一局是一个 strike：必须满足 $x=10/11$，且 $y\ge 10$。此时转移过后 $x$ 的限制没了，$y$ 被减去了一个 $10$ 变成了 $x$ 的限制，又增加了一个 $y$ 的限制，所以 $dp_{i,j,x,y}\to dp_{i+1,j+d,y-10,d-10}$。
2. 这一局是一个 spare：枚举第一局的得分 $a$，则必须满足 $x=a/11$，且 $y=10/21$。这次转移由于有两次投掷，所以 $x,y$ 的限制都没了。又增加了一个 $x$ 的限制，所以 $dp_{i,j,x,y}\to dp_{i+1,j+d,d-10,21}$。
3. 其它情形：枚举两局的得分 $a,b$，则必须满足 $x=a/11$，且 $y=a+b/21$。由于没有奖励分了，所以必须有 $d=a+b$。此时 $dp_{i,j,x,y}\to dp_{i+1,j+d,11,21}$。

然后处理最后一局的情形，这里和前面转移的方式是类似的，直接按照题面里给出的最后一局的 $7$ 种情况分别枚举一下，根据前两次投掷的结果判定一下前面状态中 $x,y$ 的合法性，然后计入答案即可，不再赘述。考虑一下这么做的复杂度。一局的得分显然至多是 $30$，所以总得分至多是 $300$，记 $k=30,d=10$，则复杂度 $O(n^2k^2d^4)$，虽然常数很小，但不能通过。

注意到瓶颈在于普通转移的第三种情形需要枚举两个得分，但由于此时 $d=a+b$，所以确定了 $a$ 就确定了 $b$。这样复杂度优化至 $O(n^2k^2d^3)$，且常数很小。其实还可以根据合法条件省去一些枚举量，但是这样已经足够通过，且实现起来比较清楚。

[代码](https://www.luogu.com.cn/paste/x89ttz70)

---

## 作者：TruchyR (赞：1)

由于神奇的转移式子喜提最长解。

设 $f_{id,i,s,ax}$ 表示打完第 $id$ 轮，总分数是 $i$，需要补奖励分的状态是 $s$，下一个必须得 $ax$ 分。

- 总分数不包括这一轮的奖励分。
- $s$ 有如下四种状态。
  - $s=0$ 时不需要补奖励分。
  - $s=1$ 时需要补下一次的分数。
  - $s=2$ 时需要补下两次的分数。
  - $s=3$ 时需要补下一次的分数加下两次的分数。
- $ax$ 在没有要求的时候等于 $11$。

转移的时候用当前状态 $f_{id,i,s,ax}$ 更新其他状态。
## 普通轮
考虑对三种情况进行分类讨论。  

对于有变量的直接枚举，然后计算要补的奖励分和增加的总分，判合法后更新。

全中的情况比较特殊，注意当 $s\geq 2$ 时说明上一个也是全中，奖励分没有补全，此时对下一次的得分有要求。

## 最终轮
最终轮不会增加新的奖励分，比较好做。

按照给定的 $7$ 种形式分类讨论就可以了，记得判合法。

## 细节
判断合法有两个基本条件。

1. 设补上了 $w$ 的奖励分且补全了，那么第 $id$ 轮的得分会固定为 $i+w$，要与给定分数比较。

2. 如果 $s=3$ 且这个状态有要求，那么第一次的分数要等于 $ax$。

具体的更新过程即枚举所有变量，对于可能的情况都做一遍，可以见代码。

```cpp
#include<bits/stdc++.h>
#define CKE if(CHECK)
#define FRE if(FIL)
#define int long long
#define MX 505
using namespace std;
const int CHECK=0,FIL=0;
int T,n,a[MX],f[15][MX][4][12];string str,p[MX];
bool dgt(char c){return (c>='0' && c<='9');}
int check(int id,int i,int op=0){
	if(op==0) return (a[id]<0 || a[id]==i);
	else{
		if(a[id]<0) return -1;
		if(i<=a[id] && i+10>=a[id]) return 1;
		return 0;
	}
}
/*
0 没有需奖励的 
1 第一球需奖励1次 
2 前两球需奖励1次 
3 第一球需奖励2次+第二球需奖励1次
   0~10 下一个要求为 x
   11 下一个没啥要求 
   
分讨中add代表这轮加的分数，bns代表这轮补上的奖励分。
check()表示判断补上奖励分后分数是否和题目给定的一样。
solveA()~solveC()是普通轮，由solve1()调用。 
solveI()~solveVII()是最终轮，由solve2()调用。 
实际实现时是用f[id-1][i][s][ax]更新f[i][][][]的。 
*/
void solveA(int id,string w,int i,int s,int lst,int xa){//全中 
	int add=0,bns=0;w="x-";
	add=10;
	if(s>=1) bns+=10;
	if(s<=1){
		if(!check(id-1,i+bns)){return;}
		f[id][i+add+bns][2][11]+=lst;
	}
	if(s==2 || (s==3 && xa>=10)){ 
		if(s>=3) bns+=10;
		//要计算下一球需要的分数
		int ck=check(id-1,i+bns,1);
		if(ck<0) f[id][i+add+bns][3][11]+=lst; 
		if(ck>0) f[id][i+add+bns][3][a[id-1]-(i+bns)]+=lst;
	}
}
void solveB(int id,string w,int i,int s,int lst,int xa){//补中 
	int add=0,bns=0;
	add=10;
	if(s==0){
		if(!check(id-1,i)) return;
		f[id][i+add][1][11]+=lst*(dgt(w[0])?1:10);
	}else if(s==2){
		bns=10;
		if(!check(id-1,i+bns)) return;
		f[id][i+add+bns][1][11]+=lst*(dgt(w[0])?1:10);
	}else{
		int AL=0,AH=9;
		if(dgt(w[0])) AL=AH=w[0]-'0';
		for(int A=AL;A<=AH;A++){
			bns=A;
			if(s==1){
				if(!check(id-1,i+bns)) continue;
				f[id][i+add+bns][1][11]+=lst;
			}else if(xa==11 || xa==A){
				bns+=10;
				if(!check(id-1,i+bns)) continue;
				f[id][i+add+bns][1][11]+=lst;
			}
		}
	}
}
void solveC(int id,string w,int i,int s,int lst,int xa){//没中 
	int add=0,bns=0;
	int AL=0,AH=9;if(dgt(w[0])){AL=AH=w[0]-'0';}
	int BL=0,BH=9;if(dgt(w[1])){BL=BH=w[1]-'0';}
	for(int A=AL;A<=AH;A++) for(int B=BL;B<=BH;B++){
		if(A+B>9) break;
		add=A+B;bns=0;
		if(s>=1) bns+=A;
		if(s>=2) bns+=B;
		if(s>=3) bns+=A;
		if(s==3 && xa!=A && xa!=11) continue; 
		if(!check(id-1,i+bns)) continue;
		f[id][i+add+bns][0][11]+=lst;
	}
}
void Solve1(int id,string w){
	for(int i=0;i<=MX-5;i++){
		for(int s=0;s<=3;s++){
			int LL=(s<3)?11:0;int RR=11;
			for(int xa=LL;xa<=RR;xa++){
				int lst=f[id-1][i][s][xa];
				if(!lst) continue;
				if(!dgt(w[0]) && !dgt(w[1]) && w[1]!='/'){//可能是全中 
					solveA(id,w,i,s,lst,xa);
				}
				if(w[0]!='x' && !dgt(w[1]) && w[1]!='-'){//可能是补中 
					solveB(id,w,i,s,lst,xa);
				}
				if(w[0]!='x' && w[1]!='/' && w[1]!='-'){//可能是没中 
					solveC(id,w,i,s,lst,xa);
				}
			}
		}
	}
}

void solveI(int id,string w,int i,int s,int lst,int xa){// xxx
	int add=0,bns=0;w="xxx";
	add=30;bns=s*10;
	if(!check(id-1,i+bns)){return;}
	if(s==3 && (xa!=11 && xa!=10)){return;}
	f[id][i+add+bns][0][11]+=lst;
}
void solveII(int id,string w,int i,int s,int lst,int xa){// xxA
	int add=0,bns=0;
	int Lo=0,Hi=9;if(dgt(w[2])){Lo=Hi=w[2]-'0';}
	for(int A=Lo;A<=Hi;A++){
		add=20+A;bns=s*10;
		if(!check(id-1,i+bns)){continue;}
		if(s==3 && (xa!=11 && xa!=10)){continue;}
		f[id][i+add+bns][0][11]+=lst;
	}
}
void solveIII(int id,string w,int i,int s,int lst,int xa){// xA/
	int add=20,bns=0;
	int Lo=0,Hi=9;if(dgt(w[1])){Lo=Hi=w[1]-'0';}
	for(int A=Lo;A<=Hi;A++){
		bns=0;
		if(s>=1) bns+=10;
		if(s>=2) bns+=A;
		if(s>=3) bns+=10;
		if(!check(id-1,i+bns)){continue;}
		if(s==3 && (xa!=11 && xa!=10)){continue;}
		f[id][i+add+bns][0][11]+=lst;
	}
}
void solveIV(int id,string w,int i,int s,int lst,int xa){// xAB
	int add=0,bns=0;
	int AL=0,AH=9;if(dgt(w[1])){AL=AH=w[1]-'0';}
	int BL=0,BH=9;if(dgt(w[2])){BL=BH=w[2]-'0';}
	for(int A=AL;A<=AH;A++) for(int B=BL;B<=BH;B++){
		if(A+B>9) continue;
		add=10+A+B;
		bns=0;
		if(s>=1) bns+=10;
		if(s>=2) bns+=A;
		if(s>=3) bns+=10;
		if(!check(id-1,i+bns)){continue;}
		if(s==3 && (xa!=11 && xa!=10)){continue;}
		f[id][i+add+bns][0][11]+=lst;
	}
}
void solveV(int id,string w,int i,int s,int lst,int xa){// A/x
	int add=20,bns=0;
	int AL=0,AH=9;if(dgt(w[0])){AL=AH=w[0]-'0';}
	for(int A=AL;A<=AH;A++){
		bns=0;
		if(s==1) bns=A;
		if(s==2) bns=10;
		if(s==3) bns=10+A;
		if(!check(id-1,i+bns)){continue;}
		if(s==3 && (xa!=11 && xa!=A)){continue;}
		f[id][i+add+bns][0][11]+=lst;
	}
}
void solveVI(int id,string w,int i,int s,int lst,int xa){// A/B
	int add=0,bns=0;
	int AL=0,AH=9;if(dgt(w[0])){AL=AH=w[0]-'0';}
	int BL=0,BH=9;if(dgt(w[2])){BL=BH=w[2]-'0';}
	for(int A=AL;A<=AH;A++) for(int B=BL;B<=BH;B++){
		add=10+B;
		bns=0;
		if(s==1) bns=A;
		if(s==2) bns=10;
		if(s==3) bns=10+A;
		if(!check(id-1,i+bns)){continue;}
		if(s==3 && (xa!=11 && xa!=A)){continue;}
		f[id][i+add+bns][0][11]+=lst;
	}
}
void solveVII(int id,string w,int i,int s,int lst,int xa){// AB-
	int add=0,bns=0;
	int AL=0,AH=9;if(dgt(w[0])){AL=AH=w[0]-'0';}
	int BL=0,BH=9;if(dgt(w[1])){BL=BH=w[1]-'0';}
	for(int A=AL;A<=AH;A++) for(int B=BL;B<=BH;B++){
		if(A+B>9) continue;
		add=A+B;
		bns=0;
		if(s==1) bns=A;
		if(s==2) bns=A+B;
		if(s==3) bns=A+A+B;
		if(!check(id-1,i+bns)){continue;}
		if(s==3 && (xa!=11 && xa!=A)){continue;}
		f[id][i+add+bns][0][11]+=lst;
	}
}
void Solve2(int id,string w){
	for(int i=0;i<=MX-5;i++){
		for(int s=0;s<=3;s++){
			int LL=(s<3)?11:0;int RR=11;
			for(int xa=LL;xa<=RR;xa++){
				int lst=f[id-1][i][s][xa];
				if(!lst) continue;
		if(!dgt(w[0]) && (w[1]=='x' || w[1]=='?') && (w[2]=='x' || w[2]=='?')){// xxx
			solveI(id,w,i,s,lst,xa);
		}
		if(!dgt(w[0]) && (w[1]=='x' || w[1]=='?') && (dgt(w[2]) || w[2]=='?')){// xxA
			solveII(id,w,i,s,lst,xa);
		}
		if(!dgt(w[0]) && (dgt(w[1]) || w[1]=='?') && (w[2]=='/' || w[2]=='?')){// xA/
			solveIII(id,w,i,s,lst,xa);
		}
		if(!dgt(w[0]) && (dgt(w[1]) || w[1]=='?') && (dgt(w[2]) || w[2]=='?')){// xAB
			solveIV(id,w,i,s,lst,xa);
		}
		if(w[0]!='x' && (w[1]=='/' || w[1]=='?') && (w[2]=='x' || w[2]=='?')){// A/x
			solveV(id,w,i,s,lst,xa);
		}
		if(w[0]!='x' && (w[1]=='/' || w[1]=='?') && (dgt(w[2]) || w[2]=='?')){// A/B
			solveVI(id,w,i,s,lst,xa);
		}
		if(w[0]!='x' && (dgt(w[1]) || w[1]=='?') && (w[2]=='-' || w[2]=='?')){// AB-
			solveVII(id,w,i,s,lst,xa);
		}
			}
		}
	}
}

signed main(){
	FRE freopen("bow.in","r",stdin);
	FRE freopen("bow.out","w",stdout);
	cin>>T;while(T--){
		//初始化 
		cin>>n>>str;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=0;i<=n;i++) for(int j=0;j<=MX-5;j++){
			f[i][j][0][11]=f[i][j][1][11]=f[i][j][2][11]=0;
			for(int ww=0;ww<=11;ww++) f[i][j][3][ww]=0;
		}
		f[0][0][0][11]=1;
		//预处理每一轮对应的条件 
		for(int i=1;i<=n;i++){
			p[i]="";for(int j=i*2-2;j<i*2;j++) p[i]+=str[j];}
		p[n]+=str[n*2];
		//分别处理普通轮和最终轮 
		for(int i=1;i<n;i++){Solve1(i,p[i]);}
		Solve2(n,p[n]);
		//统计答案 
		int res=0;
		if(a[n]<0){for(int j=0;j<=MX-5;j++) res+=f[n][j][0][11];}
		else{res=f[n][a[n]][0][11];}
		cout<<res<<'\n';
	}
	return 0;
}
```

---

