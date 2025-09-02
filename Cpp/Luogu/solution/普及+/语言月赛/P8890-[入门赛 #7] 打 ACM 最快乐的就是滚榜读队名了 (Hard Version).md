# [入门赛 #7] 打 ACM 最快乐的就是滚榜读队名了 (Hard Version)

## 题目背景

**本题的题意与 [I1](https://www.luogu.com.cn/problem/B3692) 完全相同，区别仅在 $m$ 和 $K$ 的范围。**

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

对于 $100\%$ 的数据，$1 \le n \le 20$，$1 \le m \le 2 \times 10^5$，$1 \le K \le 2 \times 10^6$，$0 \leq x \leq 5$，$00 \leq yy < 60$，$00 \leq zz < 60$，且当 $x = 5$ 时保证 $yy = zz = 00$。

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

## 作者：chen_zhe (赞：17)

~~不会有人写大模拟题解吧，不会吧不会吧。~~

作为语言月赛的最后一题，这个题应当说是有一定难度的，考察了模拟的基本功，也考察了如何使用优先队列去优化模拟过程，代码中也有一定的细节，考察基本的码力。

首先不难想到的是，将队伍用一个结构体打包起来，存下这个队伍的 AC 题数，罚时，提交编号，队伍名。此外，我们还需要存储的是这个队伍每个题提交了多少次（数组 `f[i]`，特别的，代码中规定如果 `f[i]==K+1` 为过题），以及这个队伍有哪些提交需要被滚榜（`vector <Event> r`）。此外，由于最后肯定是要对队伍进行排序的，因此这里按照 AC 数、罚时和提交编号进行了重载运算符。

```cpp
struct team {
	int ac,ftime,id;
	int f[26];
	string tname;
	vector <Event> r;
	bool operator < (const team &rhs) const {
		if (ac!=rhs.ac)
			return ac<rhs.ac;
		else if (ftime!=rhs.ftime)
			return ftime>rhs.ftime;
		else
			return id>rhs.id;
	}
	bool operator > (const team &rhs) const {
		if (ac!=rhs.ac)
			return ac>rhs.ac;
		else if (ftime!=rhs.ftime)
			return ftime<rhs.ftime;
		else
			return id<rhs.id;
	}
};
```

由于队伍的名称是字符串，因此我们用一个 `unordered_map` 存储队名。接着要设计每一发提交的结构体 `Event`。这里存放的是提交时间，提交状态，提交编号，提交题号和队伍名称。

```cpp
struct Event {
	int time,status,id;
	char p;
	string name;
};
```

我们首先读入，将每一发提交存在一个结构体数组中。接着我们处理前四个小时的情况，方便我们到时候滚榜。这里需要介绍一个让代码写起来很方便的语法糖：结构化绑定。尽管这应该是 c++17 才引入的特性，由于 gcc 的支持，其可以在 NOI 等赛事下使用（gcc 9.3,-std=c++14）。

其使用方式中，有一种如下：

```cpp
struct Foo {
    int a,b;
}t;

auto [a,b]=t;
```

这样的代码等价于 `a=t.a,b=t.b;`。此外，还可以让 `a,b` 成为 `t.a` 和 `t.b` 的引用，只需写成形如 `auto &[a,b]=t` 即可。这样就可以写出计算前四个小时的成绩的代码：

```cpp
for (auto [time,ok,id,p,name] : e) {
	if (time<=240*60) {//前四个小时
		if (!t.count(name)) {//如果没有这个队伍再新建。
			t[name].tname=name;
			t[name].id=id;
		}
		if (ok==1) {//这是一条 AC 记录。
			auto &[ac,ftime,id,f,tname,r]=t[name];
			if (f[p]==K+1)//如果已经 AC 则不更新
				continue;
			ftime+=f[p]*20*60+time/60*60;
			ac++;
			f[p]=K+1;
		}
		else {
			auto &[ac,ftime,id,f,tname,r]=t[name];
			if (f[p]==K+1)
				continue;
			f[p]++;
		}
	} else {//最后一个小时
		if (t.count(name)==0) {//滚榜期间也可以有新队伍
			t[name].tname=name;
			t[name].id=id;
		}
		t[name].r.push_back({time,ok,id,p,name});
        //将其插入存放有哪些提交需要被滚榜的 vector
	}
}
```

这里需要指出的是，对于 `map` 和 `unordered_map`，直接使用下标去访问的话，哪怕如果没有对应的下标的元素，也会自动给你新建一个元素出来。比较好的方式是使用 `count()` 这个成员函数去看是否有对应元素。

接着由于滚榜的时候，是从 A 一直到 Z 题去滚榜的，因此需要对 `r` 这个 vector 中，根据 id 作为大小进行排序，接着将这些队伍统统塞入优先队列中。为了让代码好看，排序的 `cmp` 直接使用 lambda 表达式完成。此外，由于无法对 `unordered_map` 排序，这里将其插入一个 `vector` 中。

```cpp
for (auto [fir,sec]:t)
	t2.push_back(sec);
stable_sort(t2.begin(),t2.end());
for (auto &v:t2) {
	auto &t=v.r;
	sort(t.begin(),t.end(),[](auto a,auto b) {
		return a.p<b.p;
	});
	q.push(v);
}
```

接着就进入了滚榜的流程。滚榜过程中，有两个注意点：

1. 可以使用一个数组去存储当前这个队伍已经滚榜到哪一题了，这个可以轻松使用 `unordered_map` 完成。顺带一提，我之前开了个 `unordered_map <string,vector <Event> :: iterator> itmap;`，但是会 RE，改成寻常的下标访问即可，原因不明。

2. 滚榜阶段每次从优先队列中取出两个元素，一个是 `st1` 表示当前的队伍，一个是 `st2` 表示上一个队伍。在拿 `st2` 前如果优先队列已经空了其实就说明是排名第一。给 `st1` 滚了榜后要判断一下是否满足 `st1>st2`，如果成立就插入优先队列进行后续滚榜。参考代码：

```cpp
while (!q.empty()) {
	auto st1=q.top();
	auto &[ac,ftime,id,f,tname,r]=st1;
	q.pop();
	cout << tname << " ";
	cout << "\n";
	if (q.empty())
		break;
	if (r.empty())// 没有要滚榜的提交
		continue;
	auto st2=q.top();
	size_t it=(itmap.count(tname)?itmap.at(tname):0);
	for (;it<r.size() && st1<st2;it++) {
		auto [time,status,tid,p,name]=r[it];
		if (!t.count(name)) {
			t[name].tname=name;
			t[name].id=tid;
		}
		if (f[p]==K+1)
			continue;
		if (status==0)
			f[p]++;
		else {
			ac++;
			ftime+=f[p]*20*60+time/60*60;
			f[p]=K+1;
		}
	}
	itmap[tname]=--it;
	if (st1>st2)
		q.push(st1);
}
```

这样我们就完成了本题。实际上代码细想一下其实是不难的，但是我当时半小时写完后挂了一些细节，调了一段时间，然后因为 `f` 数组开了 `unordered_map` 造成了偏大的常数 TLE。写起来总的来说还是有点痛苦。

---

## 作者：_•́へ•́╬_ (赞：16)

~~这个家伙 `ao` 和 `o` 哈希冲突调了一周，警钟敲烂~~

cz 大佬的代码写了好多我看不懂的语法，我来弄一个比较友善的（除了 `unordered_map` 和 `emplace` 以外都是 C++98 语法）。

## 分析

没啥思维啊，照着模拟。

着重讲如何实现。

我们要维护两套系统，一套是对于某个队伍维护过题和罚时情况，另一套是维护队伍之间滚榜的动态排名变化过程。

进行如下的设计：

1. 搞一个数组 `qwq[i][0]` 表示第 $i$ 个队过题数量，`qwq[i][1]` 表示第 $i$ 个队罚时。
1. 搞两个数组 `sta1[i][j]` 和 `sta2[i][j]`：
	- 如果第 $i$ 队的第 $j$ 题还没过，那么 `sta1[i][j]` 保存其不通过提交的次数，`sta2[i][j]`=0；
	- 如果过了，那么 `sta1[i][j]`=-1，`sta2[i][j]`=1；
	- 如果过了但显示待判题，那么 `sta1[i][j]` 保存其罚时，`sta2[i][j]`=1。

关于队名到编号的映射，我感觉把 `string` 塞到 `unordered_map` 里肥肠卡评测，所以用了哈希。

滚榜的时候，要维护一个**大根堆**，就是榜上（排名还没有确定的）最后一名在堆顶。

每次过题要把当前队和堆顶比较，发现不对头就有排名变化，要入堆并开始下一队的滚榜。

## code

```cpp
#include<stdio.h>
#include<queue>
#include<unordered_map>
#define b 29
#define N 20
#define M 200000
#define ull unsigned long long
using namespace std;
inline char nc()
{
	static char buf[99999],*l,*r;
	return l==r&&(r=(l=buf)+fread(buf,1,99999,stdin),l==r)?EOF:*l++;
}
inline void read(int&x)
{
	char c=nc();for(;c<'0'||'9'<c;c=nc());
	for(x=0;'0'<=c&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=nc());
}
inline void pc(const char&x)
{
	static char buf[99999],*r=buf;
	(!x||(*r++=x,r==buf+99999))&&(fwrite(buf,1,r-buf,stdout),r=buf);
}
int n,nn,m,p,qwq[M][2],sta1[M][N],pos[M];bool sta2[M][N];
unordered_map<ull,int>mmp;ull hsh;char name[M][55],tmp[55];
struct cmp
{
	inline bool operator()(const int&x,const int&y)
	{
		if(qwq[x][0]^qwq[y][0])return qwq[x][0]>qwq[y][0];
		if(qwq[x][1]^qwq[y][1])return qwq[x][1]<qwq[y][1];
		return x<y;
	}
}pwp;
priority_queue<int,vector<int>,cmp>q;
main()
{
	read(n);read(m);read(p);
	for(int t1,t2,t3,i,j,k;p--;)
	{
		read(t1);read(t2);read(t3);j=nc()-'A';nc();hsh=0;k=0;
		for(char c;c=nc(),'a'<=c&&c<='z';hsh=hsh*b+c-'a'+1,tmp[k++]=c);
		if(!mmp.count(hsh))
			i=mmp[hsh]=nn++,tmp[k]=0,sprintf(name[i],"%s",tmp);
		else i=mmp[hsh];
		if(sta2[i][j])continue;//过了再交，忽略
		if(t1<4||(t1==4&&!t2&&!t3))
			if(nc()^'A')++sta1[i][j];//WA
			else
			{
				++qwq[i][0];qwq[i][1]+=t1*60+t2+sta1[i][j]*20;
				sta1[i][j]=-1;sta2[i][j]=1;//过了并立刻计入
			}
		else if(nc()^'A')++sta1[i][j];//WA
			else sta1[i][j]=t1*60+t2+sta1[i][j]*20,sta2[i][j]=1;//过了但封榜，不立刻计入
	}
	for(int i=0;i<nn;q.emplace(i++));//全部入堆
	for(int i;q.size();)
	{
		i=q.top();q.pop();
		for(char*j=name[i];*j;pc(*j++));pc('\n');//念队名
		if(q.empty())break;
		for(int&j=pos[i];j<n;++j)if(~sta1[i][j]&&sta2[i][j])//这一题过了但是显示待判题
		{
			++qwq[i][0];qwq[i][1]+=sta1[i][j];sta1[i][j]=-1;
			if(!pwp(q.top(),i)){q.emplace(i);break;}//排名应当有变化，入堆并停止当前队伍的滚榜
		}
	}
	pc(0);
}
```

---

## 作者：Zhou_yu (赞：4)

## 题目描述：
### [P8890 题目传送门](https://www.luogu.com.cn/problem/P8890)
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
[AC 记录](https://www.luogu.com.cn/record/167586885)
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
}team[200005];
unordered_map<string,int> book;//坑
int cnt;
int List[200005][25];
int List2[200005][25];
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
笔者通过这道题后也尝试了使用快排取代优先队列，不仅慢，个人认为代码复杂度也比优先队列要高，所以说数据结构是个好东西。（~~期待有勇者撰写简单版本的非优先队列题解~~）

---

## 作者：Milthm (赞：3)

## P8890 题解


### 前置知识

- 模拟

### 题目解法

这题是不简单的模拟题目，但是只要有好的思路就没有那么复杂。

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

~~代码虽然不算长，但是常数有点大，喜提最劣解。~~

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

## 作者：xiaoshumiao (赞：2)

有人说过，模拟题关键就就是**把程序的框架和结构搭建好，然后把题目的要求进行拆解。**

那么我们接下来就把这道题的思路理一遍：

## 1. 建立变量

对于每一只队伍，我们建一个结构体，里面记录名字、通过数、罚时、编号、每一道题目的罚时、每一道题目在第一次 AC 前的提交次数、每一道题目的 AC 时间、每一道题目是否 AC、每一道题目是否在封榜后 AC。
```cpp
const int N=30,M=2e5+10;
struct Team {
  string name;//名字
  int pas,tim,id;//通过数、罚时、编号
  int pt[N],st[N],t[N];//每一道题目的罚时、每一道题目在第一次 AC 前的提交次数、每一道题目的 AC 时间
  bool ac[N],fac[N];//每一道题目是否 AC、每一道题目是否在封榜后 AC
}a[M];
```

## 2. 读入&记录

开一个 map 记录每一只队伍的编号。

对于每一个提交记录，如果提交的队伍在 map 中没有出现过，就记录。

如果当前队伍已经通过了此题，那么可以忽视这条记录。

否则如果没有通过，则将此队伍这道题的 WA 次数加一。

否则记录这支队伍通过了这道题。
```cpp
int n,m,k,cnt=0; unordered_map<string,int>idx; scanf("%d %d %d",&n,&m,&k);
while(k--) {
  int h,m,s; char p; string nm,sta; scanf("%d:%d:%d %c",&h,&m,&s,&p),cin>>nm,getline(cin,sta);
  if(!idx[nm]) cnt++,idx[nm]=a[cnt].id=cnt,a[cnt].name=nm;//该队伍第一次出现
  int x=idx[nm],y=p-'A'+1;
  if(a[x].ac[y]) continue;//已经通过
  if(sta!=" Accepted") { a[x].st[y]++; continue; }//增加 WA 次数
  a[x].ac[y]=true,a[x].t[y]=h*60+m;
  if(h*3600+m*60+s>14400) a[x].fac[y]=true;//封榜后通过
  else a[x].pas++,a[x].pt[y]=a[x].t[y]+a[x].st[y]*20,a[x].tim+=a[x].pt[y];//记录
}
```

## 3. 输出

维护一个优先队列来记录所有队伍。

每次取出最后两名，将最后一名的名字输出。

然后对于每一道题，如果最后一名在封榜后过了这道题，则更新他的成绩。如果他的排名上升了，就把他重新塞到优先队列里并 `break`。
```cpp
bool operator <(const Team &b) const {//按题目要求重载运算符
  if(pas!=b.pas) return pas>b.pas;
  if(tim!=b.tim) return tim<b.tim;
  return id<b.id;
}

priority_queue<Team>q;
for(int i=1;i<=cnt;i++) q.push(a[i]);
while(q.size()>1) {
  Team x=q.top(); q.pop(),cout<<x.name<<'\n';
  Team y=q.top(); q.pop();
  for(int i=1;i<=n;i++)
    if(x.fac[i]) {//在封榜后有新通过
      x.pas++,x.tim+=x.t[i]+x.st[i]*20,x.fac[i]=false;
      if(x<y) { q.push(x); break; }//排名发生了变化
    }
    q.push(y);
}
cout<<q.top().name;
```
完结撒花！

---

## 作者：T_TLucas_Yin (赞：2)

更详细解释可以读：[Easy Version 题解](https://www.luogu.com.cn/blog/l-yhb/solution-b3692)。

此题直接模拟。用一个结构体存储每个团队的队名和所有与排序有关的信息（通过数、罚时、编号）。先按照封榜前的提交记录列出排行榜，再按照榜单顺序逐个更新封榜后的提交记录。

由于滚榜时榜单是动态的，因此要用优先队列存储。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,t,top;
int f1[200005][25];//每个队伍通过题目的情况
int f2[200005][25];//每个队伍未通过题目的提交次数
unordered_map<string,int> ma;
struct node{
	string name;
	int x,k,tim;
	bool operator <(const node &b) const{
		if(x!=b.x) return x>b.x;
		else if(tim!=b.tim) return tim<b.tim;
		else return k<b.k;
	}
}a[200005];
priority_queue<node> q;
int fashi(int hour,int minute){
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
		if(st==" Accepted"){
			if(!flag) f1[ma[nam]][q]=-1,a[ma[nam]].x++,a[ma[nam]].tim+=fashi(h,mi)+f2[ma[nam]][q]*20;
			//封榜前提交，存标记，更新团队和罚时通过数
			else f1[ma[nam]][q]=fashi(h,mi);
			//封榜后提交，只存标记
		}
		else f2[ma[nam]][q]++;
	}
	for(int i=1;i<=top;i++) q.push(a[i]);
	while(q.size()>1){
		node t1=q.top();q.pop();
		cout<<t1.name<<"\n";
		node t2=q.top();q.pop();
		for(int i=1;i<=n;i++){
			if(f1[t1.k][i]>0){//有封榜后提交的题目，就更新成绩
				t1.x++,t1.tim+=f1[t1.k][i]+f2[t1.k][i]*20,f1[t1.k][i]=-1;
				if(t1<t2){ q.push(t1);break; }//排名有变，停止读榜
			}
		}
		q.push(t2);
	}
	cout<<q.top().name;
	q.pop();
	return 0;
}
```

---

## 作者：szh_AK_all (赞：1)

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
	int to[30];
	int bu[30];
	bool operator <(const dui &l) const {
		if (guo != l.guo)
			return guo > l.guo;
		else if (fa != l.fa)
			return fa < l.fa;
		else
			return id < l.id;
	}
} s[2000005];
int o;
unordered_map<string, int>q;
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
		int shi = x * 60 + yy;
		if (s[iid].to[ti])
			continue;
		if (d == " Accepted") {
			s[iid].to[ti] = 1;
			if (shi > 240 || (shi == 240 && zz)) {
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

[题目传送门](https://www.luogu.com.cn/problem/P8890)
## 题意
这是一场 ICPC 比赛的滚榜过程。依照从最后一名到第一名的顺序，**先读出该队伍的队名**，然后再从 A 题到最后一题的顺序，公布排行榜上该队“待判题”状态试题最终是否通过。直到对排名**有影响**时，停止公布，对下一队进行以上操作。
## 思路
先给每个队伍编号，然后判断是否超过 4h。如果没有超过，就放入封榜前数组，否则就放入滚榜数组，在滚榜时按照题意操作。
### 注意
在计算时间时，不能算入秒数。\
[**AC**](https://www.luogu.com.cn/record/172057005)  
[**WA**](https://www.luogu.com.cn/record/172059258)
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

