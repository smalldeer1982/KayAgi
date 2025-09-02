# [语言月赛202212] 打 ACM 最快乐的就是滚榜读队名了(Easy Version)

## 题目背景

**本题与 [I2](https://www.luogu.com.cn/problem/P8890) 的题意完全一致，区别仅在 $m$ 和 $K$ 的范围**。

在刚刚结束的 ICPC 杭州赛站上，某 E 经历了刺激的滚榜。她发现打 ACM 最快乐的就是滚榜读队名了。

## 题目描述

一场 ICPC 正式赛共 $5$ 小时。

队伍的排名由通过题数与罚时决定。通过题数更多的队伍排名更靠前，若通过题数相同，则罚时更小的队伍排名更靠前。通过题数与罚时均相同的队伍排名相同。本题中可能出现队伍排名相同的情况，此时，认为先出现在提交记录中的队伍排名靠前。

罚时是由通过题目的时间和未通过提交的次数决定的。罚时为每一道题通过时比赛开始的分钟数之和，加上该题之前未通过提交的次数乘 $20$ 分钟得到的。例如，某队在比赛进行 $1:28:35$ 时通过了 G 题，在此之前共有 $3$ 次未通过的提交，则 G 题对罚时的总贡献为 $88+3 \times 20=148$ 分钟。

**需要注意的是，仅有通过的试题的未通过提交会被计算罚时**。例如，某队在 I 题共有 $14$ 次未通过的提交，但到比赛结束，该队都没有通过 I 题，则这 $14$ 次未通过的提交不会被计算罚时。**在某一题通过后，该队对这一题的任何提交（无论是否能够通过）都不会影响本题通过的结果和本题的罚时。**

选手在比赛过程中可以随时提交某一道试题的代码，代码将被立即评测并返回结果（$\texttt{Accepted}$，$\texttt{Time Limit Exceeded}$，$\texttt{Memory Limit Exceeded}$，$\texttt{Presentation Error}$，$\texttt{Wrong Answer}$，$\texttt{Runtime Error}$）。其中，评测结果 $\texttt{Accepted}$ 为通过，其他评测结果均为不通过。

在比赛进行的前四小时（$0:00:00 \sim 4:00:00$），每支队伍的提交均会在排行榜上反映出来。比赛的最后一小时（$4:00:01 \sim 5:00:00$），排行榜将被冻结（封榜），所有的提交在排行榜对应队伍对应试题上均显示为待判题（提交的队伍知道评测结果）。

在比赛结束后，会进行紧张刺激的滚榜环节。滚榜嘉宾将按照封榜时的排行榜，依照从最后一名到第一名，**先读出队伍队名**，再按照从 A 题依次到最后一题的顺序，公布排行榜上该队“待判题”状态试题最终是否通过。

如果通过，所有队伍的排名将立即重新计算，显然，已经滚榜完成（被滚榜嘉宾念过队名，且所有待判题状态的结果都已经揭晓）的队伍排名不会有影响。若该队伍排名上升，则滚榜嘉宾立即开始下一支队伍的滚榜。因此，一支队伍的队名可能被滚榜嘉宾多次读出。

例如，某队队名为“囤题”，在前四小时没有通过任何一题，封榜时排在最后一名。在封榜后，该队连续通过全部十三道题目。那么滚榜嘉宾有可能读到该队队名七八次。当然，当该队上升到第一名后，其排名不会再发生变化，即使揭晓的判题结果为通过，但其排名没有发生变化，滚榜嘉宾不会再次读出其队名。

现在给出某场 ICPC 完整的提交记录，请你依次输出滚榜嘉宾念出的队名。

**一次提交记录都没有的队伍不会在排行榜上出现，也不会在滚榜中被念到队名。**

## 说明/提示

### 样例解释

在封榜前，队伍 $\texttt{abc}$ 仅通过 $\texttt{A}$ 题，且在第二秒的第一次正确提交之前有一次错误提交，因此罚时为 $20$ 分钟；队伍 $\texttt{bcd}$ 同样仅通过 $\texttt{A}$ 题，且在 $0:19:38$ 的第一次正确提交之前没有错误提交，因此罚时为 $19$ 分钟。

在封榜后，队伍 $\texttt{abc}$ 通过了 $\texttt{B}$ 题。

在滚榜环节开始，由于封榜后的提交未被揭晓，因此暂时认为队伍 $\texttt{abc}$ 与 $\texttt{bcd}$ 均只通过一题，且前者罚时较大，排名靠后。

依照从最后一名到第一名的原则，队伍 $\texttt{abc}$ 的名字先被念到，并揭晓其在封榜后的提交的结果。其通过了 $\texttt{B}$ 题，因此其通过题数被更新为 $2$，罚时同样被更新。同时，所有队伍的排名立即被重新计算。由于此时 $\texttt{abc}$ 通过题目数量大于 $\texttt{bcd}$，因此其排名重新计算为第一名，而 $\texttt{bcd}$ 成为最后一名第二名。

这之后，队伍 $\texttt{bcd}$ 的名字被念到，由于其在封榜后没有提交，因此这时所有队伍的排名没有变化，滚榜嘉宾会进行其上一名队伍的滚榜。

最后，队伍 $\texttt{abc}$ 的名字被念到，滚榜结束。

需要注意的是，在滚榜过程中是逐题揭晓提交。也就是说，如果一支队伍封榜后通过了多道题，在其进行滚榜过程中，只要按照从 $\texttt{A}$ 题依次到最后一题的顺序，该队第一个“待判题”状态试题通过，后面的“待判题”同样暂时不会揭晓，而是立刻进行排名更新过程以及可能存在的更换另一支队伍进行滚榜的过程。

### 数据规模与约定

- 对于 $30\%$ 的数据，$n = 1$；
- 对于另外 $10\%$ 的数据，$m = 1$；
- 对于 $100\%$ 的数据，$1 \le n \le 20$，$1 \le m \le 1000$，$1 \le K \le 10^4$，$0 \leq x \leq 5$，$00 \leq yy < 60$，$00 \leq zz < 60$，且当 $x = 5$ 时保证 $yy = zz = 00$。

保证提交记录按照提交时间不降序给出，即先给出的提交记录提交时间不会晚于后给出的提交记录的提交时间，试题名称为大写字母 $\texttt{A} \sim \texttt{Z}$，队名均为长度不超过 $50$ 的由小写字母组成的字符串，评测状态为试题中所给的 $6$ 种之一。

## 样例 #1

### 输入

```
2 2 4
0:00:01 A abc Wrong Answer
0:00:02 A abc Accepted
0:19:38 A bcd Accepted
4:18:22 B abc Accepted```

### 输出

```
abc
bcd
abc
```

# 题解

## 作者：Milthm (赞：17)

## B3692 题解


### 前置知识

- 模拟

### 题目解法

这题是不算太难的模拟题目，但是为了方便一些（一次过两题多好啊），所以我这个代码同样可以通过加强版，但两题思路是一样的。

首先本题的题意有一点可能比较难懂，就是滚榜的过程。这里我说明一下，流程大概如下：

先找到排名最底下的没有完全更新完的人，从第一题扫描到最后一题，如果他比倒数第二名高了（即排名上升），我们直接停止更新，并重复此过程。直至这样的人只剩一个，输出这个人即可。

现在明白题目意思了，让我们来看看如何实现：

首先我们用结构体把每个队伍的通过题目数量、编号、罚时、名字、封榜前通过题目、封榜前未通过题目的次数、封榜后通过题目、封榜后未通过题目的次数和封榜后每题通过的时间存起来，如下（变量依次按照刚才说的顺序给出）：

```cpp
struct node{
	int sc,id,time;string name;
	bool ac[25]={0};int WA[25]={0};
	bool fbac[25]={0};int fbWA[25]={0};int fbti[25]={0};
}a[200005];
```

然后考虑如何记录，记录过程比较麻烦，结合代码中的注释理解：

```cpp
	for(int i=1;i<=K;++i){
		char c;
		int x,y,z;
		string d,rec;
		scanf("%d:%d:%d %c",&x,&y,&z,&c);
		cin>>d;
		getline(cin,rec);
		if(x*3600+y*60+z>4*3600){//如果超过 4 个小时
			fb=1;//设为封榜状态
		}
		if(b[d]==0){如果这个队伍之前没出现过
			b[d]=++qwq,a[qwq].id=qwq;a[qwq].name=d;//更新新队伍信息
		}
		if(rec[1]=='A'){如果这题通过了
			if(fb==0&&a[b[d]].ac[c-'A']==0){//如果是封榜前，且此题之前未通过
				a[b[d]].ac[c-'A']=1;//设为通过
				++a[b[d]].sc;//题目通过数+1
				a[b[d]].time+=x*60+y+a[b[d]].WA[c-'A']*20;//计算罚时
			}
			else if(fb&&a[b[d]].ac[c-'A']==0&&a[b[d]].fbac[c-'A']==0){//如果封榜了，且此题之前未通过
				a[b[d]].fbac[c-'A']=1;a[b[d]].fbti[c-'A']=x*60+y;//设为通过，记录通过时间
			}
		}
		else if(a[b[d]].ac[c-'A']==0&&a[b[d]].fbac[c-'A']==0){//如果没通过，且此题之前也没通过
			if(!fb)a[b[d]].WA[c-'A']++;//分别记录
			else a[b[d]].fbWA[c-'A']++;
		}
	}
```

最后就是滚榜过程了，容易发现这个过程很适合用优先队列维护，但是需要重载运算符：

```cpp
bool operator<(const node& b)const{
		if(sc!=b.sc)return sc>b.sc;
		if(time!=b.time)return time<b.time;
		return id<b.id;
	}
```
重载完了之后模拟即可：

```cpp
while(!q.empty()){
		if(q.size()==1){//记得特判只有一个人，不然全 RE
			cout<<q.top().name<<'\n';
			break;
		}
		node c1=q.top();q.pop();
		node c2=q.top();q.pop();//取出倒数第一和倒数第二
		cout<<c1.name<<'\n';
		for(int i=0;i<n;++i){
			if(c1.fbac[i]){//如果这题封榜之后 AC 了
				c1.time+=(c1.fbWA[i]+c1.WA[i])*20+c1.fbti[i];//计算罚时
				c1.fbac[i]=0;//清空，防止再次记录
				c1.ac[i]=1;
				c1.sc++;//通过题目数量 +1
				if(c1<c2){//如果比倒数第二还高了
					q.push(c1);q.push(c2);goto R;//就把两个都 push 回去榜单里
				}
			}
		}
		q.push(c2);//c1 被更新完了，只有 c2 回去
		R:;
	}
```

恭喜你通过了此题。

### 彩蛋



本题调试过程比较困难，我在这里给大家一个样例：

输入：

```
4 4 15
0:00:01 A dabc Wrong Answer
0:00:08 A dabc Wrong Answer
0:01:09 A qwq Accepted
1:19:08 B qwq Accepted
2:53:48 B dabc Wrong Answer
4:00:00 A dabc Accepted
4:00:03 A homo Accepted
4:00:04 B homo Accepted
4:00:05 C homo Accepted
4:00:06 D homo Runtime Error
4:50:08 A homo Runtime Error
4:59:13 C qwq Accepted
4:59:48 D qwq Accepted
5:00:00 D dabc Wrong Answer
5:00:00 C dabc Accepted
```

输出：

```
homo
dabc
homo
dabc
homo
qwq
homo
qwq
```





---

## 作者：T_TLucas_Yin (赞：6)

看题目一眼：这么简单？

写代码：哎？

此题是一道模拟。代码还是很有难度的。我们首先要知道题目要求我们干什么。

### 题意

实际上就是，将提交记录分为两个部分，分别进行处理。

对于封榜以前的提交记录，根据提交记录的信息将每个参加比赛的队伍的成绩进行排名（排序）。排序规则如下：

- 若两个队伍通过的题目数不同，通过题目多的队伍在前。
- 否则，若两个队伍的罚时不同，罚时少的队伍在前。
- 若罚时也相同，先提交的队伍在前。

封榜以后，首先从榜单的最后一名开始滚榜。滚到哪个排名，就读出哪个排名上的队伍名字，然后将这个队伍封榜以后通过的每道题以及其罚时依次计入成绩。若记录完一道题目后该队伍不再是最后一名，则停止读该队伍，重新计算排名后再读新的最后一名。若该队伍排名没有变化，则继续读下一个队伍。

### 解法

涉及到“重新计算”的排序问题很适合用**优先队列**。

我们定义一个结构体，存储每个队伍的队名、编号、通过的题数和罚时。编号是按照团队第一次提交的先后顺序排的。

然后在结构体中按照上述排序规则重载小于运算符。

本题的重点在于计算罚时。根据题目，罚时受两部分因素影响，一部分是 AC 的时间，另一部分是错误的提交次数。对于封榜前提交的题目，我们可以直接根据已有的信息计算罚时并计入成绩。对于封榜后提交的题目需要延时计算，第二部分的罚时仍可以直接得出，而第一部分只需要额外存储一下 AC 的时间即可。

所以为了计算罚时，我们需要另外两个数组，分别用于存储团队每道题目的通过情况（未通过的为 $0$，封榜前通过的为 $-1$，封榜后通过的存储 AC 时间，以分钟为单位）和团队每道未通过题目的提交次数。

按题意模拟即可。代码中给出解释。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,top;
int f1[1005][25];//每个队伍通过题目的情况
int f2[1005][25];//每个队伍未通过题目的提交次数
unordered_map<string,int> ma;//卡常神器
struct node{
	string name;
	int x,k,tim;
	bool operator <(const node &b) const{//排序规则
		if(x!=b.x) return x>b.x;
		else if(tim!=b.tim) return tim<b.tim;
		else return k<b.k;
	}
}a[1005];
priority_queue<node> q;
int fashi(int hour,int minute){//计算时间罚时
	return 60*hour+minute;
}
int main(){
	scanf("%d %d %d",&n,&m,&t);
	while(t--){
		char c;
		bool flag;
		int h,mi,s,q;
		string nam,st;
		scanf("%d:%d:%d %c",&h,&mi,&s,&c);
		q=c-'A'+1;
		cin>>nam;
		getline(cin,st);
		if(h>4||(h==4&&(mi||s))) flag=1;//表示这条记录是封榜后的提交
		else flag=0;
		if(!ma.count(nam)) ma[nam]=++top,a[top].name=nam,a[top].k=top;//新出现的队伍
		if(f1[ma[nam]][q]) continue;//很坑的一个点，已通过的题目又交了一遍是没有用的
		if(st==" Accepted"/*注意空格*/){//是AC记录
			if(!flag) f1[ma[nam]][q]=-1,a[ma[nam]].x++,a[ma[nam]].tim+=fashi(h,mi)+f2[ma[nam]][q]*20;
			//封榜前提交，存标记，更新团队和罚时通过数
			else f1[ma[nam]][q]=fashi(h,mi);
			//封榜后提交，只存标记
		}
		else f2[ma[nam]][q]++;//不是AC记录，只存标记
	}
	for(int i=1;i<=top;i++) q.push(a[i]);//存榜单
	while(q.size()>1){
		node t1=q.top();q.pop();
		cout<<t1.name<<"\n";//读一下最后一名
		node t2=q.top();q.pop();//把倒数第二名也取出来，方便比较
		for(int i=1;i<=n;i++){
			if(f1[t1.k][i]>0){//有封榜后提交的题目，就更新成绩
				t1.x++,t1.tim+=f1[t1.k][i]+f2[t1.k][i]*20,f1[t1.k][i]=-1;
				if(t1<t2){ q.push(t1);break; }//排名有变，停止读榜
			}
		}
		q.push(t2);//倒数第二名给他放回去
	}
	cout<<q.top().name;//输出榜单上的最后一个团队
	q.pop();//强迫症狂喜
	return 0;
}
```

---

## 作者：Zhou_yu (赞：4)

## 题目描述：
### [B3692 题目传送门](https://www.luogu.com.cn/problem/B3692)
第一眼：哇是模拟！只要细心能 AC！

上手后：啧，嘶……[是这样的吗](https://www.luogu.com.cn/record/list?pid=P8890&user=Zhou_yu&page=1)？
## 思路
本题码量其实不算多，主要是做题时的思路需要非常清晰，很考验逻辑功底。（~~像我这样底子差的就要十次才 AC~~）

大体分为：
1. 输入
2. 记录本次状态的影响（封榜前和封榜后）
3. 滚榜
4. 输出
5. 执行步骤 $3$ 和 $4$ 直到只剩一个人

熟悉流程后，考虑实现方法：
1. 输入时发现队伍名称与个数都不固定，使用 map 进行对队伍名称与出现顺序的配对，使便于在二维数组中进行本团队所有做题状态的记录。

2. 为记录一次状态的影响，使用两个二维数组，下文 `List[i][j]` 即表示第 $i$ 个队伍在第 $j$ 道题上的**所有的错误情况**与**封榜前**的正确情况。（特殊的，当 `List[i][j]` 值为 $-1$ 时表示此题在通过）

3. **封榜后的通过记录**需要在滚榜时特殊处理，需要再开一个二维数组 `List2[i][j]` 表示第 $i$ 个队伍在封榜后的第 $j$ 道题上通过的所用时间。

4. 滚榜时发现需要对目前的榜单不断进行排序，显然对于**动态排序**情况下，优先队列每次 $O(\log n)$ 的复杂度成为首选。使用优先队列进行滚榜，将最后一名与最后第二名的成绩重新比较，如果最后一名**反超**，再将其重新放进队列，否则将其移出队列。

现在做题的思路理清了，但本题难就难在其坑点很多，下面是本人整理的坑点清单（坑点不按题目流程排序）：
## 坑点清单
1. 一道已经通过的题目再提交这道题无论是什么结果都不需要加入计算。（本状态就是**完全无用**的数据）

2. 在排序时除了按队伍通过总题数与队伍总罚时为关键字，**队伍编号**也是需要的。（编号即队伍的出现顺序）

3. 当队列里只有一个人时，只需要输出他并且**立刻结束程序**。

4. 注意到一次状态只有通过与未通过之分，所以从状态首字母就能看出信息了。

5. 封榜后通过的某题只需要记录时间，**不需要**在该队伍的通过题数里记录加一，后面滚榜滚到才需要记录加一。

6. 最后一小时从 $4:00:01$ 开始，不是 $4:00:00$ 开始。

7. 无论最后一名反没反超都要把最后第二名重新放进队列。

8. map 要用 unordered_map 来卡常。

除了坑点，本题每个测试点 $5$ 秒的时限也使得本题难以调试，在放最终代码前，给各位再放一个本题的[随机数据生成程序](https://www.luogu.com.cn/paste/28au7add)，生成的数据名称为 `test.in`，希望能帮到大家！
## AC 代码
[AC 记录](https://www.luogu.com.cn/record/167587108)
```cpp
#include <bits/stdc++.h>
using namespace std;
struct node
{
	string name;//队伍名称
	int penalty;//队伍总罚时
	int ACpass;//队伍通过总题数
	int id;//编号
	bool operator <(const node &b) const
	{
		if(ACpass==b.ACpass)
		{
			if(penalty==b.penalty)
			return id<b.id;//坑，第三关键字
			return penalty<b.penalty;
		}
		return ACpass>b.ACpass;
	}
}team[1005];
unordered_map<string,int> book;//坑
int cnt;
int List[1005][25];
int List2[1005][25];
priority_queue<node> q;
int main()
{
	int n,m,k;
	cin>>n>>m>>k;
	while(k--)
	{
		int x,y,z;
		char ch;
		string name;
		char isAC;
		string rubbish;
		scanf("%d:%d:%d %c",&x,&y,&z,&ch);
		int Qi=ch-'A'+1;
		cin>>name;
		isAC=getchar();//把空格先去掉 
		isAC=getchar();//真正的状态首字母 
		getline(cin,rubbish);//废物…… 
		if(!book.count(name))//新的队伍出现了
		{
			book[name]=++cnt;
			team[cnt].name=name;
			team[cnt].id=cnt;
		}
		int id=book[name];
		if(!List2[id][Qi]&&List[id][Qi]!=-1)//坑
		{
			if(isAC=='A')
			{
				if(x>4||(x==4&&z+y>0))List2[id][Qi]=x*60+y;//坑，封榜后的AC
				else
				{
					team[id].ACpass++;//封榜前的AC
					team[id].penalty+=(x*60+y+List[id][Qi]*20);
					List[id][Qi]=-1;//设为通过
				}
			}
			else List[id][Qi]++;
		}
	}
	for(int i=1;i<=cnt;i++)q.push(team[i]);
	while(!q.empty())
	{
		node now=q.top();
		q.pop();//取出最后一名
		cout<<now.name<<'\n';
		if(q.empty())break;//坑，队列里仅有一人
		node nxt=q.top();
		q.pop();
		for(int i=1;i<=n;i++)//重新检查最后一名AC情况
		if(List2[now.id][i]&&List[now.id][i]!=-1)//坑，此题已通过
		{
			now.ACpass++;
			now.penalty+=List2[now.id][i]+List[now.id][i]*20;
			List[now.id][i]=-1;
			if(now<nxt)
			{q.push(now);break;}//反超了
		}
		q.push(nxt);//坑
	}
	return 0;
}
```
## 后记
笔者通过这道题后也尝试了使用快排取代优先队列，不仅慢，个人认为代码复杂度也比优先队列要高，所以说数据结构是个好东西。（~~期待有勇者撰写本版本的非优先队列题解~~）

---

## 作者：hjb13357896690 (赞：4)

### [题目传送门](https://www.luogu.com.cn/problem/B3692)

看一眼：一道绿题！一定很简单！

结果：呜呜呜， 怎么一直报错。。。

这道题只要用结构体打包好信息即可。

步骤：
1. 每支队伍封榜之前的数据
2. 每支队伍最终的数据
3. 将封榜之前的数据，做成排行榜
4. 滚榜
## 模拟 & 结构体

这题最麻烦的就是算罚时。AC 的时间、错误的提交次数都能导致被罚。我们可以用结构体 **Problem** 来计算并储存总罚时，**Team** 存团队的。

所以我们要按题意模拟。

下面就是你们最喜欢的 AC Code 了：
```cpp
#include <bits/stdc++.h> // 万能头
#define ll long long

using namespace std;

// 结构体

struct Problem
{
    Problem()
	{
        flag = 0,time = 0;
    }
    int flag; // 0 ：未通过，1 ：已通过
    int time; // 总罚时
};

struct Team
{
    Team()
	{
        solved = 0,total = 0;
    }
    string name;    // 队伍名称
    Problem a[26];  // 每一道题目的通过状态
    int solved;     // 总通过题目数量
    int total;      // 所有题目的总罚时
    int first_submit; // 首次提交记录
};

map<string, Team> ta; // 封榜之前每个队伍完成的题目情况
map<string, Team> tb; // tb 代表最终每个队伍完成题目的情况
Team bangdan[1005];
int n, m, k, copy_flag = 0;

// 两支队伍排序的比较规则
bool cmp(Team a, Team b)
{
    if (a.solved != b.solved) 
    {
    	return a.solved > b.solved;
	}
    if (a.total != b.total) 
    {
    	return a.total < b.total;
	}
    return a.first_submit < b.first_submit;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin >> n >> m >> k;
    for (int i = 0;i<k;i++)
	{
        char ch;
        int xx,yy,zz,ss;
        string name, result;
        cin >> xx >> ch >> yy >> ch >> zz; // 读入时间
        cin >> ch; // 读入题目编号
        cin >> name; // 读入队伍名称
        getline(cin, result); // 读入判题结果
        while (result[0] == ' ') 
        {
        	result = result.substr(1, result.size());
		}
        ss = xx * 3600 + yy * 60 + zz;
        if (ss <= 4*3600)
		{
            // 如果是第一次出现这个队伍，就记录这个队伍第一次提交的时间
            if (ta.find(name) == ta.end())
			{
                ta[name].first_submit = i;
                ta[name].name = name;
            }
            // 如果在4个小时以内，就把数据存储到 ta 中
            // 如果这道题目之前通过了，就跳过本次的提交记录
            if (ta[name].a[ch - 'A'].flag == 1)
			{
                continue;
            }
            // 如果之前没有通过，那就处理本条提交记录
            if (result == "Accepted")
			{
                ta[name].a[ch - 'A'].flag = 1;
                ta[name].a[ch - 'A'].time += xx * 60 + yy;
                ta[name].solved += 1;
                ta[name].total  += ta[name].a[ch - 'A'].time;
            }
			else
			{
                ta[name].a[ch - 'A'].time += 20;
            }
        }
		else
		{
            // 第一次封榜以后，先把数据拷贝给tb
            if (copy_flag == 0)
			{
                tb = ta;
                copy_flag = 1;
            }
            // 如果是第一次出现这个队伍，就记录这个队伍第一次提交的时间
            if (tb.find(name) == tb.end())
			{
                ta[name].first_submit = i;
                ta[name].name = name;
                tb[name].first_submit = i;
                tb[name].name = name;
            }
            // 之后的数据，就存储在 tb 当中
            if (tb[name].a[ch - 'A'].flag == 1)
			{
                continue;
            }
            // 如果之前没有通过，那就处理本条提交记录
            if (result == "Accepted")
			{
                tb[name].a[ch - 'A'].flag = 1;
                tb[name].a[ch - 'A'].time += xx * 60 + yy;
                tb[name].solved += 1;
                tb[name].total  += tb[name].a[ch - 'A'].time;
            }
			else
			{
                tb[name].a[ch - 'A'].time += 20;
            }
        }
    }
    // 将封榜之前的所有队伍的做题信息整理到榜单上
    int bangdan_cnt = 0;
    for (auto t:ta)
	{
        bangdan[bangdan_cnt++] = t.second;
    }
    // 对榜单排序
    sort(bangdan + 0, bangdan + ta.size(), cmp);
    /* 检验封榜之前的榜单正确性
     for (int i = 0; i < ta.size(); i++) {
         string name = bangdan[i].name;
         cout << name << " : ";
         for (int j = 0; j < n; j++) {
             if (ta[name].a[j].flag == 0) continue;
             cout << "(" << char(j + 'A') << ", " << ta[name].a[j].time << ") ";
         }
         cout << endl;
     }
     cout << endl;
     检验最终的榜单的正确性
     for (int i = 0; i < ta.size(); i++) {
         string name = bangdan[i].name;
         cout << name << " : ";
         for (int j = 0; j < n; j++) {
             if (tb[name].a[j].flag == 0) continue;
             cout << "(" << char(j + 'A') << ", " << tb[name].a[j].time << ") ";
         }
         cout << endl;
     }*/ 

    // 开始滚榜
    int ind = ta.size() - 1;
    string pre_name = "";
    while (ind != -1)
	{
        int flag = 0; // 当前队伍是否需要向上滚榜
        string name = bangdan[ind].name;
        if (name != pre_name)
		{
            cout << name << endl; // 输出当前被念到的榜单名字
            pre_name = name;
        }
        for (int i = 0; i < n; i++)
		{
            if (tb[name].a[i].flag != bangdan[ind].a[i].flag)
			{
                bangdan[ind].a[i] = tb[name].a[i];
                bangdan[ind].solved += 1;
                bangdan[ind].total  += bangdan[ind].a[i].time;
                flag = 1;
                break;
            }
        }
        if (flag)
		{
            int j = ind;
            while (j > 0 && cmp(bangdan[j], bangdan[j - 1]))
			{
                swap(bangdan[j], bangdan[j - 1]);
                j -= 1;
            }
        }
		else
		{
            ind -= 1;
        }
    return 0;//撒花 
}
```
既然已经看到这了，何不点个赞再走呢~

---

## 作者：szh_AK_all (赞：4)

## 分析
这题是一道模拟题，只需按照题意模拟并加上适当的算法即可。

首先，对于每支队伍，我们用一个结构体来存储信息。每支队伍的信息包括：这支队伍的名称，编号（有提交记录先后决定），罚时，通过题目数以及每道题的通过或不通过情况。

由于滚榜是不断更新的，滚榜内每支队伍的信息也是回不断改变的，所以，我们用堆来存储滚榜（也就是优先队列）。使用堆的好处是：每次在堆里添加一个队伍，那么堆内队伍的排列就会发生改变，符合滚榜的变化。

为了方便起见，我们重载小于号，根据题意，由通过题目数、罚时、编号来判断两支队伍的大小关系。那么在进行堆的插入操作时，也会按照这样的大小关系排序。

做完准备工作后，开始模拟过程。

首先对于每条提交记录，我们要判断提交队伍是否出现（用键值对存储）。如果没出现，那么添加这支队伍，并将队伍的信息初始化；如果出现过，则获取这支队伍的编号，以便得到这支队伍的信息。

如果该队伍通过了此题，则无需进行下面的操作；否则，继续进行判断。

如果该题的提交状态为不通过，则将改题目的提交数加一；否则，计算该队伍的罚时，并标记该题为通过。

需要注意的一点是，如果这条提交记录是在封榜后出现的，则进行特殊标记，并记录该题的罚时（不能更新该队伍的总罚时），在滚榜时再计算总罚时。

处理完所有提交记录后，将每支队伍加入堆中，并进行滚榜操作。

我们取出并弹出队首，并输出队首队伍的名称，计算每题在封榜后的罚时，若队首队伍的罚时加上该题的罚时后，滚榜会发生变化，那么重新加入堆中，并结束该操作。

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

struct dui {
	int fa;
	string name;
	int id;
	int guo;
	int to[40];
	int bu[40];
	bool operator <(const dui &l) const {
		if (guo != l.guo)
			return guo > l.guo;
		else if (fa != l.fa)
			return fa < l.fa;
		else
			return id < l.id;
	}
} s[1005];
int o;
map<string, int>q;
priority_queue<dui>pai;

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= k; i++) {
		string a, b, c, d;
		cin >> a >> b >> c;
		getline(cin, d);
		int x = 0, yy = 0, zz = 0;
		int p = 0;
		for (; p < a.size(); p++) {
			if (a[p] == ':')
				break;
			x = x * 10 + (a[p] - '0');
		}
		p++;
		for (; p < a.size(); p++) {
			if (a[p] == ':')
				break;
			yy = yy * 10 + (a[p] - '0');
		}
		p++;
		for (; p < a.size(); p++) {
			if (a[p] == ':')
				break;
			zz = zz * 10 + (a[p] - '0');
		}
		if (!q[c]) {
			q[c] = ++o;
			s[o].name = c;
			s[o].id = o;
			s[o].guo = 0;
			s[o].fa = 0;
			memset(s[o].to, 0, sizeof(s[o].to));
			memset(s[o].bu, 0, sizeof(s[o].bu));
		}
		int iid = q[c];
		int ti = b[0] - 'A' + 1;
		int shi = x * 60 + yy;//时间
		if (s[iid].to[ti])
			continue;
		if (d == " Accepted") {
			s[iid].to[ti] = 1;
			if (shi > 240 || (shi == 240 && zz)) {//特判
				s[iid].to[ti] = 2 + shi + 20 * s[iid].bu[ti];
			} else {
				s[iid].fa += shi + 20 * s[iid].bu[ti];
				s[iid].guo++;
			}
		} else
			s[iid].bu[ti]++;
	}
	for (int i = 1; i <= o; i++) {
		pai.push(s[i]);
	}
	while (pai.size() > 1) {
		dui x = pai.top();
		pai.pop();
		cout << x.name << endl;
		dui y = pai.top();
		pai.pop();
		for (int i = 1; i <= n; i++) {
			if (x.to[i] > 1) {
				x.fa += x.to[i] - 2;
				x.guo++;
				x.to[i] = 1;
				if (x < y) {
					pai.push(x);
					break;
				}
			}
		}
		pai.push(y);
	}
	cout << pai.top().name;
}
```


---

## 作者：zza_LG (赞：3)

### 纯模拟题解

#### 读题
题面有点长，耐心读完后总结出以下几点：
1. 此题模拟分为两部分：**评测情况**和**滚榜**。
2. 比赛的最后一小时（$4:00:01\sim5:00:00$）才封榜，也就是说，$4:00:00$ 是不封榜的。
3. 队伍排名的规则为先比**通过题数（更多更靠前）**，再比**罚时（更小更靠前）**，最后比**提交记录顺序（越早出现越靠前）**。

---

#### 需要注意的点
1. 会有队伍在封榜前从未提交（隐藏实力），封榜后却提交了，就要把队伍放在排名榜最后。
2. 当有队伍在某一题通过后，该队对这一题的任何提交都不会影响本题的做题情况（包括封榜后）。
3. 滚榜时，不会有队伍被连续两次念队名。
4. 如果有待判题通过了，则应停止处理该队伍后面其他的待判题，并将队伍排名未确定的队伍的排名重新计算，而不是简单地交换此队伍和上一个队伍的排名。

---

#### 评测情况模拟方法
若评测时间在封榜前，先判断该队伍此题是否已经 AC。如果是，就不要管了；如果不是，就将此次评测情况直接计入总数。

若评测时间在封榜后，仍先判断该队伍此题是否已经 AC。如果是，一样不要管了；如果不是，就将此次评测情况计入该队伍的此题情况。

---

#### 滚榜模拟方法

手动模拟样例可以发现，每次滚榜其实只有最后一名的队伍在往前移（或不移），所以可以用一个栈来记录目前排名榜中队伍排名未确定的队伍的队名，在根据题目描述来依次处理每个待判题，直到该滚榜的时候停止。在滚榜时，可以用另一个栈记录被该队伍反超的队伍，此次滚榜完后再接到该队伍的排名后面。

**具体模拟方法见代码及注释。（变量名的含义在定义时已给出）**

---

#### 代码
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,k,x,y,z,gb,fb;//n：试题数，m：队伍数(没什么用），k：提交记录数,x、y、z：提交时间、gb：滚榜，fb：封榜
char mh,th;//mh：冒号(占位)，th：题目遍号
string s,pc,a[200005],syc;//s：该队伍名称，pc：评测情况，syc：滚榜时上一次念的队伍名
struct dw{//dw：队伍
	int tg,cw,fs,dpt;//tg：通过，cw：错误次数，fs：封榜后通过此题的罚时,dpt：是否是待判题
};
map<string,int>p,zfs,ztgs,zdpts;//p[s]：队伍s的出现顺序，zfs[s]：队伍s的总罚时，stgs[s]：队伍s的通过题目总数，zdpts[s]：队伍s的总待判题
map<pair<string,char>,dw>l;//l[s][th]：队伍s的th题做题情况
vector<string>pmb;//pmb：排名榜
bool hl(string a,string b){//hl：合理的情况或排名的规则
	if(ztgs[a]!=ztgs[b])return ztgs[a]>ztgs[b];//通过题数更多的队伍排名更靠前
	if(zfs[a]!=zfs[b])return zfs[a]<zfs[b];//罚时更小的队伍排名更靠前
	return p[a]<p[b];//先出现在提交记录中的队伍排名靠前
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m>>k;
	m=0;
	for(int i=1;i<=k;i++){//评测
		cin>>x>>mh>>y>>mh>>z;
		cin>>th>>s;
		getline(cin,pc);
		pc=pc[1];//取出状态首字母。
		if(!p[s]){//记录队伍s的出现顺序
			p[s]=i,a[m+1]=s,m++;
			if(fb)pmb.push_back(s);//若队伍s封榜前从未提交，封榜后提交了，就要把队伍s放在排名榜最后
		}
		if(x*3600+y*60+z>4*3600&&!fb){
			sort(a+1,a+m+1,hl);
			for(int i=1;i<=m;i++)pmb.push_back(a[i]);
			fb=1;
		}//一到封榜时间就封榜，并建造排名榜
		if(!fb){
			if(!l[{s,th}].tg){
				if(pc=="A"){
					zfs[s]+=x*60+y+l[{s,th}].cw*20;
					l[{s,th}].tg=1;
					ztgs[s]++;
				}
				if(pc!="A")l[{s,th}].cw++;
			}
		}//未封榜时就将评测情况直接计入总数
		if(fb){
			if(!l[{s,th}].tg){
				if(pc=="A"){
					l[{s,th}].fs=x*60+y+l[{s,th}].cw*20;
					l[{s,th}].tg=1;
				}
				if(pc!="A")l[{s,th}].cw++;
				if(!l[{s,th}].dpt)zdpts[s]++;
				l[{s,th}].dpt=1;
			}
		}//封榜后就将评测情况计入队伍s的th题情况
	}
	while(!pmb.empty()){//滚榜
		gb=0;
		if(pmb.back()!=syc)cout<<pmb.back()<<"\n",syc=pmb.back();//念队伍名
		if(!zdpts[pmb.back()]){
			pmb.pop_back();
			continue;
		}//被念过队名，且所有待判题状态的结果都已经揭晓的队伍排名已确定，就再也不会被念队名了。
		string dqdw=pmb.back();//dqdw：当前正在滚榜的队伍队名
		pmb.pop_back();
		for(char i='A';i<='Z';i++){
			if(l[{dqdw,i}].dpt==1){
				if(l[{dqdw,i}].tg==1){
					zfs[dqdw]+=l[{dqdw,i}].fs;
					ztgs[dqdw]++;
				}
				l[{dqdw,i}].dpt=0;
				zdpts[dqdw]--;
			}//处理待判题
			if(!pmb.empty()&&!hl(pmb.back(),dqdw)){
				gb=1;
				break;
			}//需要滚榜
		}
		if(!gb)pmb.push_back(dqdw);//不需要滚榜
		if(gb){
			vector<string>t;
			while(!pmb.empty()&&!hl(pmb.back(),dqdw))t.push_back(pmb.back()),pmb.pop_back();
			pmb.push_back(dqdw);
			while(!t.empty())pmb.push_back(t.back()),t.pop_back();
		}//开始滚榜
	}
	return 0;
}
```
[AC](https://www.luogu.com.cn/record/184228894)

---

## 作者：GavinWu_qwq (赞：2)

这道题是一道模拟题，代码量较大，没有清晰的思路是无法在短时间内通过的。

### 题意简述

我们先梳理一下这道题的要求。

对于封榜前的提交记录，全部立即进行记录并实时更新排行榜。排名的规则如下：

1. 若两队通过数不同，通过数多的队伍排在前面。

2. 否则若两队罚时时长不同，罚时少的队伍排在前面。

3. 否则按首次出现提交记录中的时间排序，提交时间早的队伍排在前面。

对于封榜后的提交记录，暂时不计入排行榜，但依然计入最终成绩。

滚榜时，按排行从低到高依次念出队伍的名称，并处理该队在封榜后的提交记录。

- 若有提交记录的结果为通过，重新计算该队的总罚时和通过数。

- 若队伍的排名变化，更新排名，之后这支队伍可能还会再被念到。

### 代码思路

定义一个 ``Node`` 结构体来记录每支队伍的信息，注意还需要在结构体中重载运算符以方便使用优先队列。

```cpp
struct Node{
    string name; //记录队伍名称
    int qnum, ptime, ord; 
    //qnum记队伍在比赛时的通过数，ptime记队伍的总罚时，ord记队伍出现在提交记录中的顺序
    int pt[25], mcnt[25], act[25];
    //pt[i]记第i题为队伍带来的罚时，mcnt[i]记队伍在通过第i题前有多少次非AC提交，act[i]记队伍通过第i题的时间
    bool pf[25], lf[25];
    //pf[i]记队伍是否通过第i题，lf[i]记队伍是否是在封榜后通过的第i题
    //根据排序规则重载小于号
    bool operator < (const Node&x) const{
        if (qnum != x.qnum) return qnum > x.qnum;
        else if (ptime != x.ptime) return ptime < x.ptime;
        return ord < x.ord;
    }
}t[1010];
```

定义一个优先队列和一个 ``map`` 容器分别存排行榜和各支队伍在提交记录中出现的顺序。

```cpp
priority_queue <Node> q;
map <string, int> vis;
```

还可以再定义一个常量 ``TIME`` 来存以秒为单位的封榜时间。

```cpp
const int TIME = 14400;
```

读入和记录是本题细节较多的部分，这个部分的分支情况比较复杂，容易出错，写的时候要额外小心。

```cpp
int cur = 0; //记当前提交记录中有多少支队伍
while (k--){
    string tname, res; //tname存队名，res存评测结果
    char qnum; //qnum存题号
    int hr, min, sec; //hr,min,sec分别存时分秒
    scanf("%d:%d:%d %c", &hr, &min, &sec, &qnum);
    cin >> tname;
    getline(cin, res);
    int nt = hr * 3600 + min * 60 + sec; //计算提交时间（单位：秒）
    bool isp = (res == " Accepted"); //isp记是否通过
    //处理新出现在提交记录中的队伍
    if (vis.count(tname) == false){
        cur++; //队伍数+1
        vis[tname] = cur; //标记队伍在提交记录中的顺序
        t[cur].name = tname; //记录队名
        t[cur].ord = cur; //记录队伍在提交记录中的顺序
    }
    int qid = qnum - 'A' + 1, tid = vis[tname];
    //qid记1~26之间的题号，tid存队伍在提交记录中的顺序
    //只有当之前没有通过这道题才能继续计算罚时和通过数
    if (t[tid].pf[qid] == false){
         //如果评测结果为通过
         if (isp == true){
             t[tid].act[qid] = nt; //记录AC这道题的时间
             t[tid].pf[qid] = true; //标记为已通过
             if (nt > TIME) t[tid].lf[qid] = true; //如果已经封榜，标记为在封榜后通过
             else{
                 t[tid].pt[qid] = nt / 60 + t[tid].mcnt[qid] * 20; //否则计算本题罚时
                 t[tid].qnum++; //通过数+1
             }
         }
         else t[tid].mcnt[qid]++; //如果没有通过，累积未通过次数
    }
}
```

记录完了以后还要再计算一遍所有队伍的总罚时，并初始化排行榜（即优先队列）。

```cpp
for (int i = 1;i <= cur;i++)
    for (int j = 1;j <= n;j++)
        t[i].ptime += t[i].pt[j];
for (int i = 1;i <= cur;i++) q.push(t[i]);
```

滚榜的过程需要使用到优先队列数据结构，每次将当前的倒数第一名和倒数第二名出队，并处理倒数第一名在封榜后的提交。如果排行变化，重新入队倒数第一名。注意无论如何最后都要将倒数第二名重新入队。

```cpp
while (q.size() >= 2){ //只有当至少还剩两支队伍时才能继续，否则会RE
    Node last1 = q.top(); q.pop();
    Node last2 = q.top(); q.pop(); //出队倒数第一和第二
    cout << last1.name << endl; //点名
    for (int i = 1;i <= n;i++)
        if (last1.lf[i] == true){ //若该题是在封榜后AC
            last1.qnum++; //通过数+1
            last1.ptime += last1.act[i] / 60 + last1.mcnt[i] * 20; //重新计算总罚时
            last1.lf[i] = false; //标记为false避免重复处理
            if (last1 < last2){ //如果排行变动
                q.push(last1); //重新入队倒数第一
                break; //结束当前滚榜
            }
        }
        q.push(last2); //重新入队倒数第二
    }
cout << q.top().name << endl; //点最后一支队伍的名
```

### 完整代码

[戳这里](https://www.luogu.com.cn/paste/vm3s7cf3)

---

## 作者：pan_hometown (赞：1)

*本题解使用的是 Java 语言。*

该题需要准确理解题目描述的过程以及建立合适的数据结构，后者可用 Java 语言中的类与对象（或 C 语言中的结构体等）完成。本文处理如下：

---
**class：**`Answer`**（一支队伍的其中一题的解答情况）**
|成员名|成员类型|成员含义|
|-|-|-|
|`isAccepted1`|boolean|封榜前是否通过|
|`isAccepted2`|boolean|封榜后是否通过|
|`penaltyTime`|int|未通过记录积累的罚时|

---
**class：**`Team`**（一支队伍）**
|成员名|成员类型|成员含义|
|-|-|-|
|`name`|String|队伍名|
|`order`|int|第几先出现在提交记录中|
|`passProblem`|int|通过题数|
|`penaltyTime`|int|罚时|
|`temp`|int|滚榜到该队时从第几题开始判|
|`answer`|`Answer[]`|答题情况|
|`record`|方法|记录封榜前未通过记录和封榜后所有记录|
|`update`|方法|记录封榜前通过记录|

**方法说明：**
- `record`：若该题的 `isAccepted2` 为 `false`，则更新 `isAccepted2` 和**该题的** `penaltyTime`（罚时）。
- `update`：若该题的 `isAccepted1` 为 `false`，则更新 `isAccepted1=true`、`passProblem++` 和**该队的** `penaltyTime`（罚时）。
---
**class：**`TeamSet`**（队伍集合）**
|成员名|成员类型|成员含义|
|-|-|-|
|`team`|`Team[]`|至少提交一次记录的队伍集合|
|`count`|int|至少提交一次记录的队伍总数|
|`selectTeam`|方法|返回指定队伍名的 `Team` 对象|
|`ifSort`|方法|判断两个队伍是否需要交换排名|
|`sort`|方法|滚榜前排序|
|`update`|方法|滚榜时更新排名|

**方法说明：**
- `selectTeam`：根据队名顺序查找 `team`，若未找到（第一次提交），创建新的 `Team` 对象，更新 `count++`，返回新创建的 `Team` 对象。
- `ifSort`：输入两个排名，其对应的两个队伍中，若前者通过题数 `passProblem` 大于后者的或两者通过题数相等但前者罚时 `penaltyTime` 小于后者的或均相等但前者先出现在提交记录中（即 `order` 更小），返回 `true`，否则返回 `false`。
- `sort`：使用冒泡排序法在滚榜前对 `team` 进行排序。
- `update`：滚榜时的更新操作。从后向前查找最后一名的队伍更新后应插入的位置，将其余队伍依次后置。
---
**全过程描述如下：**
1. 遍历全部记录，若在封榜前提交且评测结果为 `Accepted`，调用**该队的** `update` 方法，否则调用 `record` 方法。
2. 调用 `sort` 方法排序。
3. 从最后一名的队伍开始。
4. **先输出队名**，然后若其不是第一名，则从该队第 `temp` 题开始判，若判到 AC 题，则先调用**该队的** `update` 方法，后调用 `ifSort` 方法，若 `ifSort` 返回 `true`，则先更新 `temp`，后调用 `TeamSet` 的 `update` 方法更新排名。
5. 若该队排名变化，则找到原排名对应的新队伍，执行步骤 $4$，若该队题目全部判完且排名不变且其不是第一名，则对其上一名队伍执行步骤 $4$。
---
相关 Java 代码如下：
```java
import java.util.Scanner;
public class Main{
	public static void main(String[]args){
		Scanner sc=new Scanner(System.in);
		int n=sc.nextInt();					//试题数
		TeamSet.team=new Team[sc.nextInt()];//队伍数
		int k=sc.nextInt();					//提交记录数
		for(int i=0;i<k;i++){
			String time=sc.next();
			int problem=sc.next().charAt(0)-'A';
			String name=sc.next();
			if(sc.nextLine().trim().equals("Accepted")){
				int hour=Integer.parseInt(time.substring(0,1));
				int minute=Integer.parseInt(time.substring(2,4));
				int second=Integer.parseInt(time.substring(5,7));
				if(hour<4||hour==4&&minute==0&&second==0){
					TeamSet.selectTeam(name,n).update(problem,60*hour+minute);
				}
				else{
					TeamSet.selectTeam(name,n).record(problem,true,60*hour+minute);
				}
			}
			else{
				TeamSet.selectTeam(name,n).record(problem,false,20);
			}
		}
		//至此，数据读取已全部完成
		//下面是滚榜
		TeamSet.sort();
		for(int i=TeamSet.count-1;i>=0;i--){
			if(i!=0){
				System.out.println(TeamSet.team[i].name);
				for(int j=TeamSet.team[i].temp;j<n;j++){
					if(TeamSet.team[i].answer[j].isAccepted2){
						TeamSet.team[i].update(j,0);
						if(TeamSet.ifSort(i,i-1)){
							TeamSet.team[i].temp=j+1;
							TeamSet.update(i);
							i++;
							break;
						}
					}
				}
			}
			else{
				System.out.print(TeamSet.team[i].name);
			}
		}
	}
}
class Answer{
	boolean isAccepted1;
	boolean isAccepted2;
	int penaltyTime;
}
class Team{
	String name;		//队伍名
	int order;			//序号
	int passProblem=0;	//通过题数
	int penaltyTime=0;	//罚时
	int temp=0;			//读取开始处
	Answer[]answer;		//答题情况
	Team(String name,int n){//构造方法
		this.name=name;
		order=TeamSet.count;
		answer=new Answer[n];
		for(int i=0;i<n;i++){
			answer[i]=new Answer();
		}
	}
	void record(int problem,boolean isAccepted,int penaltyTime){//用于记录
		if(!answer[problem].isAccepted2){
			answer[problem].isAccepted2=isAccepted;
			answer[problem].penaltyTime+=penaltyTime;
		}
	}
	void update(int problem,int penaltyTime){
		if(!answer[problem].isAccepted1){
			answer[problem].isAccepted1=true;
			passProblem++;
			this.penaltyTime=this.penaltyTime+answer[problem].penaltyTime+penaltyTime;
		}
	}
}
class TeamSet{
	static Team[]team;	//至少提交一次记录的队伍集合
	static int count=0;	//至少提交一次记录的队伍总数
	static Team selectTeam(String name,int n){
		for(int i=0;i<count;i++){
			if(team[i].name.equals(name)){
				return team[i];
			}
		}
		team[count]=new Team(name,n);
		count++;
		return team[count-1];
	}
	static boolean ifSort(int i,int j){
		boolean a=team[i].passProblem>team[j].passProblem||team[i].passProblem==team[j].passProblem&&team[i].penaltyTime<team[j].penaltyTime;
		boolean b=team[i].passProblem==team[j].passProblem&&team[i].penaltyTime==team[j].penaltyTime&&team[i].order<team[j].order;
		return a||b;
	}
	static void sort(){
		for(int i=0;i<count;i++){
			for(int j=count-1;j>i;j--){
				if(ifSort(j,j-1)){
					Team temp=team[j];
					team[j]=team[j-1];
					team[j-1]=temp;
				}
			}
		}
	}
	static void update(int i){
		int j=i-1;
		while(j>=0&&ifSort(i,j)){
			j--;
		}
		j++;
		Team temp=team[i];
		while(i>j){
			team[i]=team[i-1];
			i--;
		}
		team[j]=temp;
	}
}
```
**注意：**

本题解使用了如遍历查找队伍、冒泡排序等低效的算法，所以只能 AC 本题，~~因为这是我大半年前 AC 的题，当时还不会用复杂的数据结构，~~ 若想通过数据量更大的 [Hard Version](https://www.luogu.com.cn/problem/P8890)，需要在本题基础上进行优化，例如哈希查找、优先队列等。~~大半年对一个人的影响真的很大！~~ 优化的处理就交给大家自行思考吧❤️。

---

## 作者：liruizhou_lihui (赞：0)

打磨你。

## 思路分析

开一个结构体来表示一个团队，成员变量如下表



|名称|类型|含义|
|:-:|:-:|:-:|
|`name`|`string`|团队名称|
|`id`|`int`|有提交的团队里的编号|
|`time`|`int`|此团队的罚时|
|`problem`|`int`|通过题目数量|

再定义两个二维数组： $sum$ 和 $sum2$，$sum_{i,j}$ 表示第 $i$ 个队伍在**封榜前**有几次第 $j$ 题的**提交失败**。$sum2_{i,j}$ 表示 $i$ 个队伍在**封榜后** 解决第 $j$ 题的所用时间（封榜前就不用管了）。

有这些前置的定义就可以一步步按题意模拟即可

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k;
struct node
{
	string name;
	int time;
	int problem;
	int id;
	bool operator <(const node &b) const
	{
		if(problem==b.problem)
		{
			if(time==b.time)
			{
				return id<b.id;
			}
			return time<b.time;
		}
		return problem>b.problem;
	}
}team[200005];
unordered_map<string,int> ump;
int cnt;
int sum[200005][25];
int sum2[200005][25];
priority_queue<node> q;
int main()
{
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	cin>>n>>m>>k;
	while(k--)
	{
		int x,y,z;
		char p;
		string nam;
		string IAKIOI;//代替无用测评串 
		scanf("%d:%d:%d %c",&x,&y,&z,&p);
		cin>>nam; 
		char record;//测评记录首字母 
		int P=p-'A'+1;//第几题 
		cin>>IAKIOI;
		record=IAKIOI[0];
		if(record!='A')//并没有AC 
		{
			//其他测评状态都是由多个单词组成，要把剩下的输入完
			if(record=='T' || record=='M')//TLE,MLE三个字母
			{
				cin>>IAKIOI>>IAKIOI;
				//再输入两个 
			}
			else
			{
				//其他都是两个字母，只需再次输入一个 
				cin>>IAKIOI;
			}
		}
		//cout<<x<<' '<<y<<' '<<z<<' '<<p<<' '<<record<<'\n';
		if(!ump.count(nam))//新团队 
		{
			cnt++;
			ump[nam]=cnt;
			team[cnt].name=nam;
			team[cnt].id=cnt;
		}
		int id=ump[nam];
		if(!sum2[id][P]&&sum[id][P]!=-1)//如果此题还未通过 
		{
			if(record=='A')//如果测评记录为AC 
			{
				if(x>4||(x==4&&(y>0||z>0)))//封榜了 
				{
					sum2[id][P]=x*60+y;//记到封榜AC
				}
				else//还没封榜 
				{
					team[id].problem++;//又AC了一道题 
					team[id].time+=(x*60+y+sum[id][P]*20);
					sum[id][P]=-1;//设为通过
				}
			}
			else
			{
				sum[id][P]++;//吃罚时 
			}
		}
	}
	for(int i=1;i<=cnt;i++)//这里不能是m，因为有的团队一发也没交不会参与滚榜 
	{
		q.push(team[i]);//把所有有提交的团队压入队列 
	}
	while(!q.empty())
	{
		node now=q.top();
		q.pop();
		cout<<now.name<<'\n';//滚榜 
		if(q.empty())//滚完了 
		{
			break;
		}
		node nxt=q.top();
		q.pop();
		for(int i=1;i<=n;i++)
		{
			if(sum2[now.id][i]&&sum[now.id][i]!=-1)//看这题是不是在封榜的时候AC 
			{
				now.problem++;//又AC了一题
				now.time+=sum2[now.id][i]+sum[now.id][i]*20;//结算罚时 
				sum[now.id][i]=-1;//通过了 
				if(now<nxt)
				{
					q.push(now);
					break;
				}
			}
		}
		q.push(nxt);
	}
	return 0;
}
```

---

## 作者：OIratrace (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/B3692)

## 题意
这是一场 ICPC 比赛的滚榜过程。依照从最后一名到第一名的顺序，**先读出该队伍的队名**，然后再从 A 题到最后一题的顺序，公布排行榜上该队“待判题”状态试题最终是否通过。直到对排名**有影响**时，停止公布，对下一队进行以上操作。
## 思路
先给每个队伍编号，然后判断是否超过 4h。如果没有超过，就放入封榜前数组，否则就放入滚榜数组，在滚榜时按照题意操作。
### 注意
在计算时间时，不能算入秒数。\
[**AC**](https://www.luogu.com.cn/record/172047923)  
[**WA**](https://www.luogu.com.cn/record/172047981)
## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int tm;
	bool ACer;
}f[200005][30],st[200005][30];
struct O{
	int A,T,N;
	bool friend operator < (O x,O y){//堆排序的重载运算符
		if (x.A==y.A){
			if (x.T==y.T){
				return x.N<y.N;
			}
			return x.T<y.T;
		}
		return x.A>y.A;
	}
}o,oo;
bool check(O x,O y){//检查排名是否被影响
	if (x.A==y.A){
		if (x.T==y.T){
			return x.N<y.N;
		}
		return x.T<y.T;
	}
	return x.A>y.A;
}
priority_queue<O> s;
int n,m,k,cnt;
string NN[200005];
map<string,int> q;
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0);
	cin>>n>>m>>k;
	while (k--){
		string times,team,result;char name;
		cin>>times>>name>>team;
		if (q[team]==0){//用map给队伍编号，并通过号码存储队伍名字
			q[team]=++cnt;
			NN[cnt]=team;
		}
		getline(cin,result);
	    int	a=times[0]-'0';//计算时间
		int	b=(times[2]-'0')*10+(times[3]-'0');
		int	c=(times[5]-'0')*10+(times[6]-'0');
		int tm=a*60+b;
		if (tm*60+c<=3600*4){//判断是否封榜
			if (f[q[team]][name-'A'].ACer==0){//封榜前数组
				if (result[1]=='A'){	
					f[q[team]][name-'A'].ACer=1;
					f[q[team]][name-'A'].tm+=tm;
				}
				else f[q[team]][name-'A'].tm+=20;
			}
		}
		else{//滚榜数组
			if (st[q[team]][name-'A'].ACer==0&&f[q[team]][name-'A'].ACer==0){
				if (result[1]=='A'){
					st[q[team]][name-'A'].ACer=1;
					st[q[team]][name-'A'].tm+=tm;
				}
				else st[q[team]][name-'A'].tm+=20;
			}
		}
	}
	for (int i=1;i<=cnt;i++){//根据现有成绩入堆排名
		int AC=0,Time=0;
		for (int j=0;j<n;j++){
			if (f[i][j].ACer==1){
				AC++;
				Time+=f[i][j].tm;
			}
		}
		o.A=AC,o.T=Time,o.N=i;
		s.push(o);
	}
	while (!s.empty()){
		o=s.top(),s.pop();
		if (s.empty()==1){//判断是否为第一名
			cout<<NN[o.N]<<'\n';
			break;
		}
		oo=s.top();
		s.pop();
		cout<<NN[o.N]<<'\n';//先读出该队伍的队名
		for (int i=0;i<n;i++){
			if (st[o.N][i].ACer==1){
				st[o.N][i].ACer=0;
				o.A++,o.T+=st[o.N][i].tm+f[o.N][i].tm;
				if (check(o,oo)){//检查排名是否被影响
					s.push(o);
					break;
				}
			}
		}
		s.push(oo);
	}
	return 0;
}
```

---

