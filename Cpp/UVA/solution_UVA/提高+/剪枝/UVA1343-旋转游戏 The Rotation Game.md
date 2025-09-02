# 旋转游戏 The Rotation Game

## 题目描述

　　如图 $1$ 所示，有一个 “#” 形的棋盘，上面有 $1,2,3$ 三种数字各 $8$ 个。给定 $8$ 种操作，分别为图中的 $\text{A}\sim \text{H}$。这些操作会按照图中字母与箭头所指明的方向，把一条长度为 $8$ 的序列循环移动 $1$ 个单位。例如下图最左边的 “#” 形棋盘执行操作 $\text{A}$ 时，会变为图中间的 “#” 形棋盘，再执行操作 $\text{C}$ 后会变为图中最右边的 “#” 形棋盘。
![](https://cdn.luogu.org/upload/pic/40731.png)
$$\text{图 1}$$
　　现给定一个初始状态，请使用最少的操作次数，使 “#” 形棋盘最中间的 $8$ 个格子里的数字相同。

# 题解

## 作者：米奇 (赞：13)

## 算法:IDA*

这是道IDA*的模板题
```cpp
#include<bits/stdc++.h>
using namespace std;
bool flag=false;
char c[20];
int a[9]={5,4,7,6,1,0,3,2,-1};//先把A-H看成1-8,A对应F,B对应E...
//这里的a[8]=-1其实是一个是否为深搜第一层的特判 
int mp[24];
int pos[8][7]=
{
  {0,2,6,11,15,20,22},    //A
  {1,3,8,12,17,21,23},    //B
  {10,9,8,7,6,5,4},       //C
  {19,18,17,16,15,14,13}, //D
  {23,21,17,12,8,3,1},    //E
  {22,20,15,11,6,2,0},    //F
  {13,14,15,16,17,18,19}, //G
  {4,5,6,7,8,9,10}      //H
};
int center[8]={6,7,8,11,12,15,16,17};
//看英文就知道这是中间8块的编号
void change(int x)//x表示那一条(A-H)
{
    int k=mp[pos[x][0]];
    for(int i=0;i<6;i++)
    	mp[pos[x][i]]=mp[pos[x][i + 1]];
    mp[pos[x][6]]=k;
}
bool cmp(int a,int b)
{
    return a>b;
}
int luck()//乐观估计函数
{
    int cnt[3]={0,0,0};
    for(int i=0;i<8;i++)
        cnt[mp[center[i]]-1]++;
    sort(cnt,cnt+3,cmp);
    return 8-cnt[0];
}
void dfs(int dep,int lastx,int maxdep)
//dep是当前深度,lastx是上一次选的操作,maxdep是边界
{
    if(flag)return;
    if(dep>maxdep||dep+luck()>maxdep)return;
    if(luck()==0)
    {
    	flag=true;
        c[dep]='\0';
        cout<<c<<endl;
        cout<<mp[center[0]]<<endl;
        return;
    }
    for(int i=0;i<8;i++)//i枚举变那一条(A-H) 
    {
        if(i!=a[lastx])
        {
            change(i);
            c[dep]=i+'A';//存下来 
            dfs(dep+1,i,maxdep);
            change(a[i]);
        }
    }
}
int main()
{
    while(true)
    {
        for(int i=0;i<24;i++)
        {
            cin>>mp[i];
            if(i==0 && mp[i]==0) return 0;
        }
        if(!luck())
        {
            cout<<"No moves needed"<<endl;
            cout<<mp[center[0]]<<endl;
            continue;
        }
        else
        {
            flag=false;
            for(int maxdep=1;!flag;maxdep++)
            dfs(0,8,maxdep);
        }
    }
    return 0;
}
```

---

## 作者：chlchl (赞：7)

## 题意简述
给定一个 $8$ 个 $1$、$8$ 个 $2$、$8$ 个 $3$ 组成的井字形矩阵，有八中操作，分别可以将每一行、列向两边循环移一位。问至少要多少步，使得中间八个格子相等，在此基础上，输出字典序最小的方案和中间八个数的值。

## 做法
使用 IDA* 解决本题。

### IDA* 算法
IDA* （启发式迭代加深搜索），是一种常用的高效搜索。它有一个估价函数 $h()$，估算当前大概还有多少步才能到达目标状态，根据这个进行剪枝。

同时，其“迭代加深”的意义是，搜索时规定一个步数 $step$，返回的是能否用 $step$ 步得出答案，如果不能，就让 $step\leftarrow step+1$。

正因如此，当我们看到数据范围较小、最大步数已知且同样较小时，可以考虑使用 IDA* ，会有不错的效果。

由上面可知，IDA* 的效率取决于估价函数的效率。$h()$ 精度越高，复杂度越低。

如果你的估价函数每次都能精准地判断接下来还有多少步，~~那你还写 IDA* 干嘛~~，这就是个 DP。

最后还有一点要注意，无论什么时候，你的 $h()$ **不能把步数更小的方案剪掉**，宁可松，不可太紧。

------------
回归本题，注意到最多只有 $48$ 次操作（~~同一个位置循环移位 $7$ 次以上没啥意义~~），故考虑使用 IDA* 算法。

本题的估价函数是唯一一个难点（虽然没多难），就是中间那八个格子至少改变几个数才能变成一样。因为我们粗略地估计，每次操作都能减少一个。

这题是一个很裸的 IDA* ，跟走迷宫差不多，但是代码的细节和实现的技巧非常多。我会重点讲讲。

- 读入不要构造矩阵，用一维数组存，每个位置就是其读入顺序的编号；
- 写一个矩阵，意思是每次循环移位会涉及到哪几个位置，注意按一定顺序写；
- 记录 $A-H$ 操作的逆操作，方便回溯时回复矩阵；
- 多用函数，善用函数。

给份代码参考，还没压行，略显冗长。

```cpp
#include<iostream>
#include<cstdio>
#include<math.h>
using namespace std;

const int N = 8 + 5;
const int oppo[] = {5, 4, 7, 6, 1, 0, 3, 2};//逆操作
const int idx[] = {0, 7, 8, 9, 12, 13, 16, 17, 18};//中间几个格子
const int mve[9][9] = {
	{1, 3, 7, 12, 16, 21, 23}, 
	{2, 4, 9, 13, 18, 22, 24}, 
	{11, 10, 9, 8, 7, 6, 5}, 
	{20, 19, 18, 17, 16, 15, 14}, 
	{24, 22, 18, 13, 9, 4, 2}, 
	{23, 21, 16, 12, 7, 3, 1}, 
	{14, 15, 16, 17, 18, 19, 20}, 
	{5, 6, 7, 8, 9, 10, 11}
};//每种操作涉及到哪几个位置
int step, g[30], ans[N];

int h(){
	int mp[4] = {0};
	for(int i=1;i<=8;i++)
		mp[g[idx[i]]]++;
	int cnt = 10;
	for(int i=1;i<=3;i++)
		cnt = min(cnt, 8 - mp[i]);
	return cnt;
}//估价函数

void calc(int op){
	int x = g[mve[op][0]];
	for(int i=0;i<6;i++)
		g[mve[op][i]] = g[mve[op][i + 1]];
	g[mve[op][6]] = x;
}//模拟循环移位操作

bool dfs(int now, int lst){
	if(h() + now > step)
		return 0;//预估的步数加上当前步数大于限制步数，不能再走了
	if(!h())
		return 1;//中间全部一致了
	for(int i=0;i<8;i++){
		if(lst == oppo[i])
			continue;//不要做上一个步骤的逆操作，这样会回到两步前
		calc(i);
		ans[now] = i;
		if(dfs(now + 1, i))
			return 1;
		calc(oppo[i]);//回溯，恢复矩阵
	}
	return 0;
}

int main(){
	while(true){
		for(int i=1;i<=24;i++){
			scanf("%d", &g[i]);
			if(!g[i])
				return 0;
		}
		if(!h()){
			printf("No moves needed\n%d\n", g[7]);
			continue;
		}
		step = 1;//初始化！初始化！初始化!
		while(!dfs(0, -1))
			step++;//IDA* 精华
		for(int i=0;i<step;i++)
			putchar('A' + ans[i]);
		printf("\n%d\n", g[7]);
	}
	return 0;
}
```

~~愣是用这几个技巧从 138 行缩到 74 行。马蜂应该海星吧。~~



---

## 作者：Lagerent (赞：5)

[题目链接](https://www.luogu.com.cn/problem/UVA1343)

参考文献：李煜东 《算法竞赛进阶指南》

## $\text{Solution}$

可以使用 IDA* 算法求解。

首先我们来确定 dfs 的框架——在每个状态下枚举执行哪种操作，然后沿着该分支深入即可。有一个很明显的剪枝是记录上一次的操作，不执行上次操作的逆操作，避免来回操作。

接下来我们设计估价函数。通过仔细观察可以发现，在每个状态下，如果中间 $8$ 个格子里出现次数最多的数字是 $k$，而中间八个格子里剩下的数字有 $m$ 个与 $k$ 不同，那么把中间 $8$ 个格子里的数字都变成 $k$ 至少需要 $m$ 次操作。因此，我们就以这个 $m$ 估价即可。

总而言之，我们采用迭代加深，由 1 开始从小到大依次限制操作次数（搜索深度），在 dfs 的每个状态下，若“ $\text{当前操作次数 + 估价} > \text{深度限制}$ ”，则从当前分支回溯。

（感觉我的代码写的还是比大部分题解清晰可读的。）

```
/*
          A       B
          0       1
          2       3
H 4   5   6   7   8   9   10 C
          11      12
G 13  14  15  16  17  18  19 D
          20      21
          22      23
          F       E
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define rep(a, b, c) for(int (a) = (b); (a) <= (c); ++ (a))
#define per(a, b, c) for(int (a) = (b); (a) >= (c); -- (a))
#define Rep(a, b, c) for(int (a) = (b); (a) < (c); ++ (a))
#define Per(a, b, c) for(int (a) = (b); (a) > (c); -- (a))
#define il inline
#define inf 0x3f3f3f3f
using namespace std;

const int N = 24;

int op[8][7] = {
    {0, 2, 6, 11, 15, 20, 22}, // A
    {1, 3, 8, 12, 17, 21, 23}, // B
    {10, 9, 8, 7, 6, 5, 4}, // C
    {19, 18, 17, 16, 15, 14, 13}, // D
    {23, 21, 17, 12, 8, 3, 1}, // E
    {22, 20, 15, 11, 6, 2, 0}, // F
    {13, 14, 15, 16, 17, 18, 19}, // G
    {4, 5, 6, 7, 8, 9, 10} // H
};

int opposite[] = {5, 4, 7, 6, 1, 0, 3, 2};
int center[] = {6, 7, 8, 11, 12, 15, 16, 17};
int q[N], path[100];
int sum[4];

int f() {
    memset(sum, 0, sizeof sum);
    rep(i, 0, 7) sum[q[center[i]]] ++ ;
    
    int s = 0;
    rep(i, 1, 3) s = max(s, sum[i]);
    return 8 - s;
}

void doit(int x) {
    int t = q[op[x][0]];
    rep(i, 0, 5) q[op[x][i]] = q[op[x][i + 1]];
    q[op[x][6]] = t;
}

bool dfs(int u, int dep, int last) {
    if(u + f() > dep) return false;
    if(!f()) return true;
    
    rep(i, 0, 7) {
        if(opposite[i] != last) {
            doit(i);
            path[u] = i;
            if(dfs(u + 1, dep, i)) return true;
            doit(opposite[i]);
        }
    }
    return false;
}

int main() {
    while(~scanf("%d", &q[0]) && q[0]) {
        rep(i, 1, N - 1) scanf("%d", &q[i]);
        
        int dep = 0;
        while(!dfs(0, dep, -1)) ++ dep;
        if(!dep) printf("No moves needed");
        else {
            Rep(i, 0, dep) printf("%c", path[i] + 'A');
        }
        printf("\n%d\n", q[6]);
    }

    return 0;
}
```

---

## 作者：ADay (赞：4)

[更逊的阅读体验](https://www.cnblogs.com/aday526/p/solution-uva1343.html)  
题解区都是 $\text{IDA*}$，实际上这题 $\text{A*}$ 也可以，代码也很简单。

## Solution

首先由于整个棋盘的形状是已知的，所以我们可以先处理出 $\text A\sim \text H$ 操作对应行列的格子编号及中间 $8$ 个格子的编号，使代码实现简单化。

而对于 $\text{A*}$，最重要的就是估价函数 $f(x)=g(x)+h(x)$，那么我们可以把每一个棋盘状态 $x$ 的操作次数当作 $g(x)$，然后把中间 $8$ 个格子中还需要修改的格子数当作估计的 $h(x)$，最后以 $f(x)$ 为序来进行广搜即可。

因为棋盘上只有 $24$ 个格子，目标状态也是一定能达到的，且时限放到了 $3s$，$\text{A*}$ 算法足以通过此题。

## Code

实现非常清晰，加上提前处理的编号也只有 $50$ 多行

```cpp
#include<bits/stdc++.h>
using namespace std;
const int p[]={7,8,9,12,13,16,17,18},//中心格子
li[][8]={{1,3,7,12,16,21,23},//A~H操作
		{2,4,9,13,18,22,24},
		{11,10,9,8,7,6,5},
		{20,19,18,17,16,15,14},
		{24,22,18,13,9,4,2},
		{23,21,16,12,7,3,1},
		{14,15,16,17,18,19,20},
		{5,6,7,8,9,10,11}};
struct node{
	int step,f,a[25];
	vector<int>op;//记录每次操作
	inline void init(){step=0;op.clear();}
	inline int h(){//计算需修改的格子数
		int c[4]={0,0,0,0};
		for(int x:p)c[a[x]]++;
		return 8-*max_element(c+1,c+4);
	}inline void calcf(){f=step+h();}
	bool operator<(node x)const{return f==x.f?op>x.op:f>x.f;}
	inline void move(int x){//进行修改操作
		int tmp=a[li[x][0]];
		for(int i=0;i<6;i++)a[li[x][i]]=a[li[x][i+1]];
		a[li[x][6]]=tmp;
	}
}st;
void Astar(){
	st.init();
	st.calcf();
	if(!st.h()){
		printf("No moves needed\n%d\n",st.a[p[0]]);
		return;
	}
	priority_queue<node>q;
	q.push(st);
	while(!q.empty()){
		node u=q.top();q.pop();
		for(int i=0;i<8;i++){
			node v=u;
			v.move(i);v.calcf();
			v.op.push_back(i);
			v.step++;
			if(!v.h()){//v为目标状态，直接输出
				for(int x:v.op)putchar('A'+x);
				printf("\n%d\n",v.a[p[0]]);
				return;
			}q.push(v);
		}
	}
}
int main(){
	while(~scanf("%d",&st.a[1])){
		if(!st.a[1])break;
		for(int i=2;i<=24;i++)scanf("%d",&st.a[i]);
		Astar();
	}
	return 0;
}
```



---

## 作者：liumuxin (赞：4)

这道题可以说是ida*的“模板"题

ida*就是迭代加深搜索+估价，枚举层数，开始dfs，到枚举的层数就停止，这样的好处是有bfs的顺序（速度），剩下了bfs的空间。

什么是估价呢，估价就是计算一个当前方案的价值，找一个比较理想的先搜索，这样理论上可以加速搜索的过程，一个好的估价函数可以让你的搜索直接找到正解（虽然不大可能）

这道题就是将上下左右的移动当成一种状态，每次搜索动哪一根，估价函数为中间的八个格子有几个相等的（原因是题目求最少几次可以让中间的变成一样的数），每次迭代加深就可以了。

这题有很多细节，比如说题目中的读入非常玄学，按照1~24的顺序从上往下，从左往右读，这就需要一些处理来计算出每一根上面的数存在哪里。其他细节详见代码注释。

```cpp
#include<iostream>
using namespace std;
//            1     2 
//            3     4
//      5  6  7  8  9 10 11
//			  12    13			
//      14 15 16 17 18 19 20
//            21    22
//            23    24   随手打下的草稿，用来对照题目中的输入，处理细节
int zhong[8]={7,8,9,12,13,16,17,18};//记录中心块读入的下标
int a[100];
int b[8][7]={{1,3,7,12,16,21,23},{2,4,9,13,18,22,24},{11,10,9,8,7,6,5},{20,19,18,17,16,15,14},
{24,22,18,13,9,4,2},{23,21,16,12,7,3,1},{14,15,16,17,18,19,20},{5,6,7,8,9,10,11}};//记录8种操作挪动的下标
int back[8]={5,4,7,6,1,0,3,2};
int count(int x){//数在8个中心块种有多少个x
	int cnt=0;
	for(int i=0;i<=7;i++)if(a[zhong[i]]==x)cnt++;
	return cnt;
}
int calc(){//算出中心块中有多少个1,2,3，求出价值（估价部分）
	return 8-max(max(count(1),count(2)),count(3));
}
void move(int n){//使用第n种操作移动，这里用到了之前处理的每一根上面的下标
	int q=a[b[n][0]];
	for(int i=1;i<=6;i++){//去掉最后一个，共6个
		a[b[n][i-1]]=a[b[n][i]];
	}
	a[b[n][6]]=q;//注意细节，最后一个需要单独赋值
}
char c[100000];
void output(){//这个是调试用的输出函数，挺复杂的，挑不出来的同学们可以用他输出调试
	cout<<"      "<<a[1]<<"     "<<a[2]<<endl;
	cout<<"      "<<a[3]<<"     "<<a[4]<<endl;
	cout<<a[5]<<"  "<<a[6]<<"  "<<a[7]<<"  "<<a[8]<<"  "<<a[9]<<"  "<<a[10]<<"  "<<a[11]<<endl;
	cout<<"      "<<a[12]<<"     "<<a[13]<<endl;
	cout<<a[14]<<"  "<<a[15]<<"  "<<a[16]<<"  "<<a[17]<<"  "<<a[18]<<"  "<<a[19]<<"  "<<a[20]<<endl;
	cout<<"      "<<a[21]<<"     "<<a[22]<<endl;
	cout<<"      "<<a[23]<<"     "<<a[24]; 
}
bool dfs(int now,int last,int limit){//搜索函数，返回值是搜没搜到解，如果搜到了解，答案就是迭代加深的层数
	//output();
	//cout<<endl<<"-------------------------------"<<endl;
	if(calc()==0){//如果全部一样，就有解
		return 1;
	}
	if(calc()+now>limit)return 0;//剪枝，如果最少步数还超过了层数限制，就没有解了
	for(int i=0;i<=7;i++){//枚举是哪一种移动
	//	cout<<(char)(i+'A')<<endl;
		//if(i==last)continue;
		move(i);
		c[now+1]=i+'A';//记录移动方案，准备输出
		if(dfs(now+1,i,limit))return 1;//如果搜到了解，返回true
		move(back[i]); //这里要回溯，很重要的细节，back[i]表示i的逆操作
	}
	return 0;
}
int main(){
	//freopen("out.txt","w",stdout);
    while(1){
		cin>>a[1];
		if(a[1]==0)return 0;
		for(int i=2;i<=24;i++)cin>>a[i];
		if(calc()==0)cout<<"No moves needed"<<endl<<a[zhong[1]]<<endl;//细节，如果不需要移动，直接输出
		else{
			int ans=1;
			while(1){//迭代加深，枚举层数
				if(dfs(0,-1,ans)){//如果在ans层内有解，答案为ans
					break;
				}
				ans++;
			}
			for(int i=1;i<=ans;i++)cout<<c[i];//输出移动的方案
			cout<<endl<<a[zhong[1]]<<endl;//输出中心块颜色
		}	
    }
}
```




---

## 作者：H_Bryan (赞：4)

这是一道经典的IDA*算法的题目，不知道该算法的小伙伴请移步至百度。


------------

首先，我们可以对1、2、3分三次求解，同时更新答案，提高效率；

其次，一个明显的剪枝是不执行上一层操作的反操作；

最后，本题的重点在于构造估价函数：
我们考虑每次移动的影响，因为每次移动最多可以增加一个相同数字的格子，
所以我们可以这样构造估价函数：

f(state[i])=该状态下中间八个格子中非所求数字格子的个数；

不难证明，f(state[i])一定小于等于实际步数，该估价函数合理。

下面上代码：

------------


```cpp
#include<bits/stdc++.h>
using namespace std;
bool state[50][24];
int table[24],ans[50],res[50],maxd;
int moven[8][7]={
{0,2,6,11,15,20,22},
{1,3,8,12,17,21,23},
{10,9,8,7,6,5,4},
{19,18,17,16,15,14,13},
{23,21,17,12,8,3,1},
{22,20,15,11,6,2,0},
{13,14,15,16,17,18,19},
{4,5,6,7,8,9,10}
};//手动打移动规则
int mid[8]={6,7,8,11,12,15,16,17};//中间八个格子
int oppo[8]={5,4,7,6,1,0,3,2};//剪枝一
int f(int now)//估价函数
{
    int ans=0;
    for(int i=0;i<8;i++)if(!state[now][mid[i]])ans++;
    return ans;
}
bool dfs(int deep)//IDA*
{
    if(deep==maxd)
    {
        if(f(deep)==0)return 1;
        else return 0;
    }
    if(deep+f(deep)>maxd)return 0;
    for(int i=0;i<8;i++)
    if(deep==0||oppo[ans[deep-1]]!=i)
    {
        ans[deep]=i;
        for(int j=0;j<24;j++)state[deep+1][j]=state[deep][j];
        for(int j=0;j<7;j++)state[deep+1][moven[i][j]]=state[deep][moven[i][(j+1)%7]];
        if(dfs(deep+1))return 1;
    }
    return 0;
}
bool judge()//更新答案
{
    if(res[0]!=-1)
    for(int i=0;i<maxd;i++)
        if(res[i]<ans[i])return 0;
        else if(res[i]>ans[i])break;
    for(int i=0;i<maxd;i++)res[i]=ans[i];
    return 1;
}
int main()
{
    while(1)
    {
        memset(res,-1,sizeof(res));
        scanf("%d",&table[0]);
        if(!table[0])break;
        for(int i=1;i<=23;i++)scanf("%d",&table[i]);
        int p=0;
        for(maxd=0;;maxd++)
        {
            for(int k=1;k<=3;k++)//分三次求解
            {
                for(int j=0;j<24;j++)
                state[0][j]=table[j]==k;
                if(dfs(0)&&judge())p=k;//更新答案
            }
            if(p)break;
        }
        if(maxd)
        {
        	for(int i=0;i<maxd;i++)putchar(res[i]+'A');
        	putchar('\n');
        }
        else printf("No moves needed\n");
        printf("%d\n",p);
    }
    return 0;
}
```

---

## 作者：John_yangliwu (赞：3)

# 思路
思路来自蓝书。

使用 IDA* 算法求解。
## 一、 估价函数
既然是 IDA* 算法，就先考虑估价函数怎么设计。

仔细观察发现，每一次操作，只能将 $1$ 个数字移出中心的 $8$ 个格子，并将另外 $1$ 个数字移入。

设在每个状态下，中心 $8$ 个格子内出现次数最多的数字为 $k$，而剩下的数字有 $m$ 个与 $k$ 不同。那么把这 $8$ 个格子里的数都变成 $k$，至少要操作 $m$ 次，于是得到了估价函数 $\operatorname{f}(state)=m$。

## 二、剪枝
有一个很明显的剪枝，记录上一次的操作，不执行该操作的逆操作，避免来回搜索。

## 三、状态的存储
发现状态的存储是一个棘手的问题，于是我们定义几个数组：

首先，我们把这个 `#` 字按从上到下，从左到右的顺便编号为 $0,1,\dots,23$：
```
         0       1
         2       3
 4   5   6   7   8   9  10
        11      12
13  14  15  16  17  18  19
        20      21
        22      23
```
然后把 $A$ 到 $H$ 所代表的一行或一列按顺序存在二维数组 $op$ 中：
```cpp
int op[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},// A
    {1, 3, 8, 12, 17, 21, 23},// B
    {10, 9, 8, 7, 6, 5, 4},// C
    {19, 18, 17, 16, 15, 14, 13},// D
    {23, 21, 17, 12, 8, 3, 1},// E
    {22, 20, 15, 11, 6, 2, 0},// F
    {13, 14, 15, 16, 17, 18, 19},// G
    {4, 5, 6, 7, 8, 9, 10}// H
};
```

进一步，用 $0,1,\dots,7$ 代替 $A,B,\dots,H$，把它们所代表的操作的逆操作存在数组 $opposite$ 中。中心的 $8$ 个位置也存在数组 $center$ 中：
```cpp
int opposite[8] = {5, 4, 7, 6, 1, 0, 3, 2};// 5是0的逆操作，4是2的逆操作……
int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};
```

最后用一个数组 $q$ 存储 $0$ 到 $23$ 这些位置上的数字就好了。

有了这几个数组，就可以解决令人头大的问题了。

# 代码
```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 24;
int op[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13},
    {23, 21, 17, 12, 8, 3, 1},
    {22, 20, 15, 11, 6, 2, 0},
    {13, 14, 15, 16, 17, 18, 19},
    {4, 5, 6, 7, 8, 9, 10}
};

int opposite[8] = {5, 4, 7, 6, 1, 0, 3, 2};
int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

int q[N];
int path[100]; // 答案，操作序列

int f() { // 估价函数
    static int sum[4];
    memset(sum, 0, sizeof(sum));
    for(int i = 0; i < 8; i++) sum[q[center[i]]]++;
    int s = 0;
    for(int i = 1; i <= 3; i++) s = max(s, sum[i]);
    return 8 - s;
}

bool chk() { // 是否满足要求，即中心8个数相同
    for(int i = 1; i < 8; i++) 
        if(q[center[i]] != q[center[0]])
            return false;
    return true;
}

void operate(int x) { // 进行操作x
    int t = q[op[x][0]];
    for(int i = 0; i < 6; i++) 
        q[op[x][i]] = q[op[x][i + 1]]; // 将这一行或一列上的数顺序移动
    q[op[x][6]] = t; // 第一个数移动到最后
}

bool dfs(int depth, int max_depth, int last) {
    if(depth + f() > max_depth) return false;
    if(chk()) return true;

    for(int i = 0; i < 8; i++) {
        if(opposite[i] == last) continue; // 剪枝，不进行上次操作的逆操作
        operate(i);
        path[depth] = i;
        if(dfs(depth + 1, max_depth, i))
            return true;
        operate(opposite[i]); // 回溯，逆操作一次
    }
    return false;
}

int main() {
    while(cin >> q[0], q[0]) {
        for(int i = 1; i < N; i++) 
            cin >> q[i];
        int depth = 0;
        while(!dfs(0, depth, -1)) depth++; // IDA*

        if(!depth) cout << "No moves needed" << endl;
        else {
            for(int i = 0; i < depth; i++) 
                cout << (char)(path[i] + 'A');
            cout << endl;
        }
        cout << q[6] << endl; // 按题目要求，随便输出一个中心的数
    }
    return 0;
}
```

[AC记录](https://www.luogu.com.cn/record/52320030)

---
$\large\text{THE\ \ \ END}$

---

## 作者：dingshengyang (赞：2)

这题用 IDA* 来写。

估价函数：题目要求最中间 $8$ 个数一模一样，那么设其最多一样的数有 $n$ 个，则至少需要 $8-n$ 次。

IDA* 本体：如果估价函数 $f()$ 加上现有步数 $step$ 大于 $max-step$，则 `return false;`

如果 $f()=0$，说明已经到达，返回 `true`。

$ways$：中间 $8$ 个的坐标。

$op_{x,y}$：第 $x$ 列第 $y$ 个数的坐标。

剪枝：记录逆操作 $abop$ （即）$a$ 通过 $abop_a$ 到达 $b$ 然后从 $abop_b$ 回到 $a$。不难发现这种操作是不必要的，于是记录上一次操作 $last$，如果 $abop_i = last$，剪枝。

```pp

#include<bits/stdc++.h>
using namespace std;
int depth;
int op[10][10]= {
    {0,2,6,11,15,20,22},
    {1,3,8,12,17,21,23},
    {10,9,8,7,6,5,4},
    {19,18,17,16,15,14,13},
    {23,21,17,12,8,3,1},
    {22,20,15,11,6,2,0},
    {13,14,15,16,17,18,19},
    {4,5,6,7,8,9,10}
};
int w[100];
int ways[10]= {6,7,8,11,12,15,16,17};
int f() {
    int st[5]= {};
    for(int i = 0; i<8; i++) {
        st[w[ways[i]]]++;
    }
    int maxn = 0;
    for(int i = 1; i<=3; i++) {
        if(st[i]>maxn) {
            maxn = st[i];
        }
    }
    return 8-maxn;
}
int abop[10]= {5,4,7,6,1,0,3,2};
int path[100]= {};
void operate(int x) {
    int t = w[op[x][0]];
    for(int i = 0; i<6; i++) {
        w[op[x][i]] = w[op[x][i+1]];
    }
    w[op[x][6]] = t;
}
int dfs(int step,int last) {
    if(step+f()>depth) return 0;
    if(f() == 0) return 1;
    for(int i = 0; i<8; i++) {
        if(abop[i]!=last) {
            operate(i);
            path[step] = i;
            if(dfs(step+1,i)) return 1;
            operate(abop[i]);
        }
    }
    return 0;
}
int main() {
    while(cin>>w[0],w[0]) {
        for(int i = 1; i<=23; i++)
            cin>>w[i];
        depth = 0;
        while(!dfs(0,-1)) depth++;
        if(!depth) cout<<"No moves needed"<<endl<<w[6]<<endl;
        else {
            for(int i = 0; i<depth; i++)
                cout<<char(path[i]+'A');
            cout<<endl<<w[6]<<endl;
        }

    }
    return 0;
}

```

---

## 作者：Grisses (赞：2)

[题面](https://www.luogu.com.cn/problem/UVA1343)

本题的方法是使用 IDA* 算法，我们设 $h(s)$ 表示矩阵 $s$ 中间 8 个数中，以最多的数作为最终的中间数字，还差多少；$g(s)$ 表示从起始状态到目前状态进行了多少步。

代码：
```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int ans,s[10][10];//ans是限制的搜索深度
  char last[105];//存储方案
  void A(){int m=s[1][3];for(int i=1;i<7;i++)s[i][3]=s[i+1][3];s[7][3]=m;}
  void B(){int m=s[1][5];for(int i=1;i<7;i++)s[i][5]=s[i+1][5];s[7][5]=m;}
  void C(){int m=s[3][7];for(int i=7;i>1;i--)s[3][i]=s[3][i-1];s[3][1]=m;}
  void D(){int m=s[5][7];for(int i=7;i>1;i--)s[5][i]=s[5][i-1];s[5][1]=m;}
  void E(){int m=s[7][5];for(int i=7;i>1;i--)s[i][5]=s[i-1][5];s[1][5]=m;}
  void F(){int m=s[7][3];for(int i=7;i>1;i--)s[i][3]=s[i-1][3];s[1][3]=m;}
  void G(){int m=s[5][1];for(int i=1;i<7;i++)s[5][i]=s[5][i+1];s[5][7]=m;}
  void H(){int m=s[3][1];for(int i=1;i<7;i++)s[3][i]=s[3][i+1];s[3][7]=m;}//8种操作
  int h(int a[10][10]){
      int f[5]={0};
      f[a[3][3]]++;f[a[3][4]]++;f[a[3][5]]++;f[a[4][3]]++;f[a[4][5]]++;f[a[5][3]]++;f[a[5][4]]++;f[a[5][5]]++;
      return 8-max(max(f[1],f[2]),f[3]);//以8减去最多的，就是上文对h(s)的定义
  }
  bool dfs(int cnt){
      if(cnt+h(s)-1>ans)return 0;//目前+估计大于了限制值就退出
      if(h(s)==0){//完成
          for(int i=1;i<cnt;i++)printf("%c",last[i]);
          printf("\n%d\n",s[3][3]);//输出答案
          return 1;//告诉dfs，已完成
      }
      last[cnt]='A';
      A();
      if(dfs(cnt+1))return 1;
      F();
      last[cnt]='B';
      B();
      if(dfs(cnt+1))return 1;
      E();
      last[cnt]='C';
      C();
      if(dfs(cnt+1))return 1;
      H();
      last[cnt]='D';
      D();
      if(dfs(cnt+1))return 1;
      G();
      last[cnt]='E';
      E();
      if(dfs(cnt+1))return 1;
      B();
      last[cnt]='F';
      F();
      if(dfs(cnt+1))return 1;
      A();
      last[cnt]='G';
      G();
      if(dfs(cnt+1))return 1;
      D();
      last[cnt]='H';
      H();
      if(dfs(cnt+1))return 1;
      C();//A到H依次执行（字典序）
      return 0;//无解
  }
  int main()
  {
      while(1){
          scanf("%d",&s[1][3]);
          if(!s[1][3])break;
          scanf("%d",&s[1][5]);
          scanf("%d%d",&s[2][3],&s[2][5]);
          for(int i=1;i<=7;i++)scanf("%d",&s[3][i]);
          scanf("%d%d",&s[4][3],&s[4][5]);
          for(int i=1;i<=7;i++)scanf("%d",&s[5][i]);
          scanf("%d%d",&s[6][3],&s[6][5]);
          scanf("%d%d",&s[7][3],&s[7][5]);//读入
          if(h(s)==0)printf("No moves needed\n%d\n",s[3][3]);//判断是否需要操作
          else{
              ans=1;
              while(!dfs(1))ans++;//迭代加深
          }
      }
      return 0;
  }
```

---

## 作者：封禁用户 (赞：1)

#### 思路

使用 $ IDA* $ 算法。

估价函数 $ h $ ：中间八块中哪个数字最多

简化 ：可以写一个上下左右的函数，这样会简单一些

#### 代码

```
#include<bits/stdc++.h>
using namespace std;
#define ojs_is_sb 1
int T,n;
int a[8][8],vis[4],k[25],deep;
string sb;
int H(){
    vis[1]=vis[2]=vis[3]=0;
    for(int i=3;i<=5;++i){
        for(int j=3;j<=5;++j){
            if(i==4&&j==4)continue;
            ++vis[a[i][j]];
        }
    }return 8-max(max(vis[1],vis[2]),vis[3]);
}
//估价函数
void left(int x){
    int m=a[x][1];
    a[x][1]=a[x][2];
    a[x][2]=a[x][3];
    a[x][3]=a[x][4];
    a[x][4]=a[x][5];
    a[x][5]=a[x][6];
    a[x][6]=a[x][7];
    a[x][7]=m;
}
void right(int x){
    int m=a[x][1];
    a[x][1]=a[x][7];
    a[x][7]=a[x][6];
    a[x][6]=a[x][5];
    a[x][5]=a[x][4];
    a[x][4]=a[x][3];
    a[x][3]=a[x][2];
    a[x][2]=m;
}
void up(int x){
    int m=a[1][x];
    a[1][x]=a[2][x];
    a[2][x]=a[3][x];
    a[3][x]=a[4][x];
    a[4][x]=a[5][x];
    a[5][x]=a[6][x];
    a[6][x]=a[7][x];
    a[7][x]=m;
}
void down(int x){
    int m=a[1][x];
    a[1][x]=a[7][x];
    a[7][x]=a[6][x];
    a[6][x]=a[5][x];
    a[5][x]=a[4][x];
    a[4][x]=a[3][x];
    a[3][x]=a[2][x];
    a[2][x]=m;
}
//操作
bool dfs(int x){
    int dis=H();
    if(!dis){
        cout<<sb<<endl<<a[3][3]<<endl;
        return 1;
    }
    if(dis+x>deep)return 0;
    string lzm=sb;
    if(sb[x-1]!='F'){
        sb+='A',up(3);
        if(dfs(x+1))return 1;
        sb=lzm,down(3);
    }
    if(sb[x-1]!='E'){
        sb+='B',up(5);
        if(dfs(x+1))return 1;
        sb=lzm,down(5);
    }
    if(sb[x-1]!='H'){
        sb+='C',right(3);
        if(dfs(x+1))return 1;
        sb=lzm,left(3);
    }
    if(sb[x-1]!='G'){
        sb+='D',right(5);
        if(dfs(x+1))return 1;
        sb=lzm,left(5);
    }
    if(sb[x-1]!='B'){
        sb+='E',down(5);
        if(dfs(x+1))return 1;
        sb=lzm,up(5);
    }
    if(sb[x-1]!='A'){
        sb+='F',down(3);
        if(dfs(x+1))return 1;
        sb=lzm,up(3);
    }
    if(sb[x-1]!='D'){
        sb+='G',left(5);
        if(dfs(x+1))return 1;
        sb=lzm,right(5);
    }
    if(sb[x-1]!='C'){
        sb+='H',left(3);
        if(dfs(x+1))return 1;
        sb=lzm,right(3);
    }return 0;
}
//搜索
int main(){
    while(ojs_is_sb){
        sb="";
        deep=0;
        cin>>k[1];
        if(!k[1])break;
        for(int i=2;i<=24;++i)cin>>k[i];
        a[1][3]=k[1];
        a[1][5]=k[2];
        a[2][3]=k[3];
        a[2][5]=k[4];
        for(int i=1;i<=7;++i)a[3][i]=k[i+4];
        a[4][3]=k[12];
        a[4][5]=k[13];
        for(int i=1;i<=7;++i)a[5][i]=k[i+13];
        a[6][3]=k[21];
        a[6][5]=k[22];
        a[7][3]=k[23];
        a[7][5]=k[24];
        if(!H()){
            cout<<"No moves needed"<<endl<<a[3][3]<<endl;
            continue;
        }
        while(!dfs(1))++deep;
    }
    return 0;
}


---

## 作者：zythonc (赞：1)

### 前言

这道题就是读入和处理比较麻烦，其他的就是的IDA\*板子

### 正文

那这个原理是什么？

通俗的讲就是在某一步发现不管怎么样，**都不可能达到目标情况或不是最优解**，此时直接回溯，效率提高不少

**用一个式子来表示就是：**

$s+h(s)>dep$

- $s$是当前的步数（花费）

- $dep$是目标

- $h(s)$就是对当前的一个最好估计，称为估价函数

当前步数 + 最好估计还达不到目标，你还会搜索下去吗？

当然不会，所以直接回溯

之后通过慢慢增加限制深度一步一步找到最优解

\[瞎bb\]30ms位居rank.1（希望不是评测姬波动或做题的dalao太少？

### 代码选注

```
char Map[8]={'A','B','C','D','E','F','G','H'};
```
考虑到字典序的问题，我们枚举的时候1-8，最后来个对应

至于为啥不是i+'A'这种类型，为了保险（懒

----------------------
```
int shrc[8]={1,2,3,4,2,1,4,3},dep;
int shru[8]={0,0,1,1,1,1,0,0},ans;
```
1-8所**对应的状态**，为了好处理所以打乱顺序，这相当于对应数组

-----------------------
```
inline int GetSituation()
```
获得情况，看看**最少**还有几个数没有回到位置上

--------------------------
```
inline void Change(char a[8],int rc,bool rule)
```
**改动某一行**

**rule取值意义**

- 0是左移（上移）

- 1是右移（下移）

**rc取值意义：**

- 1是竖着的左边的

- 2是竖着的右边的

- 3是横着的上边的

- 4是横着的下边的

----------------
```
if(!st){
	ans=f[1][3]-'0';
	return 1;
}
```
存在不需要搜索或搜索完毕的情况，此时记录，退出

----------------
```
if(shrc[i]==prc&&shru[i]!=pru) continue;
```
防止出现两次移动相当于没移的情况

--------------

```
Change(f[shrc[i]],shrc[i],!shru[i]);
```
相反方向回溯

----------------

### 完整代码

```
#include<iostream>
using std::cin;
using std::cout;
char f[5][8],lu[100],Map[8]={'A','B','C','D','E','F','G','H'};
int shrc[8]={1,2,3,4,2,1,4,3},dep;
int shru[8]={0,0,1,1,1,1,0,0},ans;
inline int Tmax(int a,int b,int c){return a>b?(a>c?a:c):(b>c?b:c);}
inline int GetSituation(){
	int a[4]={0,0,0,0};
	a[f[1][3]-'0']+=1;a[f[1][4]-'0']+=1;a[f[1][5]-'0']+=1;
	a[f[2][3]-'0']+=1;a[f[2][4]-'0']+=1;a[f[2][5]-'0']+=1;
	a[f[3][4]-'0']+=1;a[f[4][4]-'0']+=1;
	return 8-Tmax(a[1],a[2],a[3]);
}
inline void Change(char a[8],int rc,bool rule){
	char head;
	if(rule){
		head=a[7];
		for(int i=6;i>0;i--) a[i+1]=a[i];
		a[1]=head; 
	}
	else{
		head=a[1];
		for(int i=1;i<7;i++) a[i]=a[i+1];
		a[7]=head;
	}
	switch(rc){
		case 1: f[3][3]=f[1][3],f[4][3]=f[1][5];break;
		case 2: f[3][5]=f[2][3],f[4][5]=f[2][5];break;
		case 3: f[1][3]=f[3][3],f[2][3]=f[3][5];break;
		case 4: f[1][5]=f[4][3],f[2][5]=f[4][5];break;
	}
}
inline bool A_star(int s,int prc,int pru){
	int st=GetSituation();
	if(!st){
		ans=f[1][3]-'0';
		return 1;
	}
	if(s+st>dep) return 0;
	for(int i=0;i<8;i++){
		if(shrc[i]==prc&&shru[i]!=pru) continue;
		Change(f[shrc[i]],shrc[i],shru[i]);
		lu[s]=Map[i];
		if(A_star(s+1,shrc[i],shru[i])) return 1;
		Change(f[shrc[i]],shrc[i],!shru[i]);
	}
	return 0;
}
int main(){
	while(1){
		cin>>f[1][1];if(f[1][1]=='0') break;
		cin>>f[2][1]>>f[1][2]>>f[2][2];
		for(int i=1;i<8;i++) cin>>f[3][i];
		f[1][3]=f[3][3],f[2][3]=f[3][5];
		cin>>f[1][4]>>f[2][4];
		for(int i=1;i<8;i++) cin>>f[4][i];
		f[1][5]=f[4][3],f[2][5]=f[4][5];
		cin>>f[1][6]>>f[2][6]>>f[1][7]>>f[2][7];
		dep=GetSituation();ans=f[1][3]-'0';
		while(!A_star(0,-1,-1)){
			dep+=1;
		}
		if(!dep) cout<<"No moves needed";
		else for(int i=0;i<dep;i++) cout<<lu[i];
		cout<<"\n"<<ans<<"\n";
	}
}
```
代码未作任何处理，~~欢迎抄袭~~

---

## 作者：SimonSu (赞：1)

从题意我们可以看到下图 建立map数组 把对应点的数组位置存下来

![题目](https://cdn.luogu.com.cn/upload/pic/54239.png)

那么用IDA* 算法层次递进

不断的选择对象 然后用函数进行更改 赋予参数

具体见代码

```
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#define LL long long
#define ULL unsigned long long
#define debug cout<<"bug"<<endl;
using namespace std;
inline void read(int &x){
	x=0;int f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1; c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	x=x*f; 
}
int map[25],depth,aim,CCC[4];
char ans[110];
inline int okk(int map[])//判断是否已经成功 
{
	int tmp=map[7];
	if(map[8]!=tmp||map[9]!=tmp||map[12]!=tmp||map[13]!=tmp||map[16]!=tmp||map[17]!=tmp||map[18]!=tmp)
	   return 0;
	return 1;
}
inline int cc(int *g)//估价函数女 
{
	memset(CCC,0,sizeof CCC);
	CCC[g[7]]++,CCC[g[8]]++,CCC[g[9]]++,CCC[g[12]]++,CCC[g[13]]++,CCC[g[16]]++,CCC[g[17]]++,CCC[g[18]]++;
    return max(max(CCC[1],CCC[2]),CCC[3]);
}
void change(int *g,int a1,int a2,int a3,int a4,int a5,int a6,int a7)//移动函数 
{
	int tmp=g[a1];
	g[a1]=g[a2],g[a2]=g[a3],g[a3]=g[a4],g[a4]=g[a5],g[a5]=g[a6],g[a6]=g[a7],g[a7]=tmp;
}
inline int dfs(int g[],int dep,int before)
{
	if(depth-dep<8-cc(g)) return 0;//估价函数 
	if(dep>=depth) return 0;
	int tmp[25];
	for(int i=1;i<=8;i++)
	{   //剪枝 移过去的不移回来 
		if((i==1&&before==6)||(i==6&&before==1)) continue;
		if((i==2&&before==5)||(i==5&&before==2)) continue;
		if((i==3&&before==8)||(i==8&&before==3)) continue;
		if((i==4&&before==7)||(i==7&&before==4)) continue;
		
		for(int k=1;k<=24;k++) tmp[k]=g[k];
		switch(i)
		{
			case 1:ans[dep]='A';change(tmp,1,3,7,12,16,21,23);break;
			case 2:ans[dep]='B';change(tmp,2,4,9,13,18,22,24);break;
			case 3:ans[dep]='C';change(tmp,11,10,9,8,7,6,5);break;
			case 4:ans[dep]='D';change(tmp,20,19,18,17,16,15,14);break;
			case 5:ans[dep]='E';change(tmp,24,22,18,13,9,4,2);break;
			case 6:ans[dep]='F';change(tmp,23,21,16,12,7,3,1);break;
			case 7:ans[dep]='G';change(tmp,14,15,16,17,18,19,20);break;
			case 8:ans[dep]='H';change(tmp,5,6,7,8,9,10,11);break;
			default :cout<<"ERROR!"<<endl;
		}
		if(okk(tmp))
		{
			aim=tmp[7];
			ans[dep+1]='\0';
			return 1;
		}
		if(dfs(tmp,dep+1,i)) return 1;
	}
	return 0;
}
int main()
{
	while(1)
	{
		depth=0;
		read(map[1]); if(map[1]==0) break;
		for(int i=2;i<=24;i++) read(map[i]);
		if(okk(map))
		{
			printf("No moves needed\n");
            printf("%d\n",map[7]);
		}
		else
		{
			depth++;
			while(1)
			{
				if(dfs(map,0,-1))
				   break;
				depth++;
			}
			printf("%s\n",ans);
            printf("%d\n",aim);
		}
	}
	return 0;
}
```


---

## 作者：cqbzhyf (赞：0)

[题面](https://www.luogu.com.cn/problem/UVA1343)

首先我不会告诉你~~这道题我调了一个小时~~

模拟+ `IDA*`

思维难度：橙

实现难度：绿、蓝

首先估价函数即为中间八个中不同数字 $+$ 搜索层数 $=$ 迭代加深枚举层数。（一个小剪枝）

剩下的就是八个方向的函数实现（回溯可以用反方向操作）。

这就是 `IDA*`（迭代加深搜索+ `A*`）。

**本题输入以及操作繁琐，注意检查数组数字！！！**

## 代码在这里

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int ch=0,num=0;
	char c=getchar();
	while(!isdigit(c))ch|=(c=='-'),c=getchar();
	while(isdigit(c))num=(num<<1)+(num<<3)+(c^48),c=getchar();
	return ch?-num:num;
}
inline void write(int x){
	if(x>=10)write(x/10);
	putchar(x%10+'0');
}
int a[15][15],ans;
char Ans[100005]; 
inline void init(){
	a[1][5]=read();
	a[2][3]=read(),a[2][5]=read();
	a[3][1]=read(),a[3][2]=read(),a[3][3]=read(),a[3][4]=read(),a[3][5]=read(),a[3][6]=read(),a[3][7]=read();
	a[4][3]=read(),a[4][5]=read();
	a[5][1]=read(),a[5][2]=read(),a[5][3]=read(),a[5][4]=read(),a[5][5]=read(),a[5][6]=read(),a[5][7]=read();
	a[6][3]=read(),a[6][5]=read();
	a[7][3]=read(),a[7][5]=read();
	return;
}
inline int find(){
	int vis[5];
	memset(vis,0,sizeof vis);
	++vis[a[3][3]],++vis[a[3][4]],++vis[a[3][5]];
	++vis[a[4][3]],++vis[a[4][5]];
	++vis[a[5][3]],++vis[a[5][4]],++vis[a[5][5]];
    return 8-max(max(vis[1],vis[2]),vis[3]);
}
inline void get_A(){int tmp=a[1][3];for(int i=1;i<7;++i)a[i][3]=a[i+1][3];a[7][3]=tmp;}
inline void get_B(){int tmp=a[1][5];for(int i=1;i<7;++i)a[i][5]=a[i+1][5];a[7][5]=tmp;}
inline void get_C(){int tmp=a[3][7];for(int i=7;i>1;--i)a[3][i]=a[3][i-1];a[3][1]=tmp;}
inline void get_D(){int tmp=a[5][7];for(int i=7;i>1;--i)a[5][i]=a[5][i-1];a[5][1]=tmp;}
inline void get_E(){int tmp=a[7][5];for(int i=7;i>1;--i)a[i][5]=a[i-1][5];a[1][5]=tmp;}
inline void get_F(){int tmp=a[7][3];for(int i=7;i>1;--i)a[i][3]=a[i-1][3];a[1][3]=tmp;}
inline void get_G(){int tmp=a[5][1];for(int i=1;i<7;++i)a[5][i]=a[5][i+1];a[5][7]=tmp;}
inline void get_H(){int tmp=a[3][1];for(int i=1;i<7;++i)a[3][i]=a[3][i+1];a[3][7]=tmp;}
inline bool dfs(int x){
	int ret=find();
	if(!ret)return 1;
	if(x+ret-1>ans)return 0;
	get_A(),Ans[x]='A';
	if(dfs(x+1))return 1;
	get_F(),get_B(),Ans[x]='B';
	if(dfs(x+1))return 1;
	get_E(),get_C(),Ans[x]='C';
	if(dfs(x+1))return 1;
	get_H(),get_D(),Ans[x]='D';
	if(dfs(x+1))return 1;
	get_G(),get_E(),Ans[x]='E';
	if(dfs(x+1))return 1;
	get_B(),get_F(),Ans[x]='F';
	if(dfs(x+1))return 1;
	get_A(),get_G(),Ans[x]='G';
	if(dfs(x+1))return 1;
	get_D(),get_H(),Ans[x]='H';
	if(dfs(x+1))return 1;
	get_C();
	return 0;
}
signed main(){
	while(a[1][3]=read()){
		if(!a[1][3])break;
		init();
		if(!find())puts("No moves needed"),write(a[3][3]),puts("");
		else{
			for(ans=1;;++ans){
				if(dfs(1)){
					for(int i=1;i<=ans;++i)printf("%c",Ans[i]);
					puts(""),write(a[3][3]),puts("");
					break;
				} 
			}
		}
	}
	return 0;
} 
```

---

## 作者：BotYoung (赞：0)

**前置知识：IDA\* 字符串**

不得不说，本题是一道 IDA\* 的经典题，但是也确实是一道考验耐心与信心的好题。本题的难点在于 IDA\* 的估价函数和模拟过程的处理，所以题解分以下两个问题讲解。

- **1、IDA\* 的估价函数处理**

本题的最终目的是使中间 8 个格子中的数字相同，而我们已经知道整个结构中有 3 个不同的数字，这就不好处理。运用一些贪心的策略（通过样例也可以看出来），我们最终选择了 2 作为目标数，原因是因为它是所有在中间的数字中，出现次数最多的。因此我们可以利用这一特点（估计猜也能猜出来吧），可以构造估价函数--将图案中间出现次数最多的数字假定为目标数字，中间除了这个数字的数的出现次数就是我们的估价函数 $h(x)$。

IDA\* 的剪枝：当已经走过的步数 $g(x)$ 加上估计步数 $h(x)$ 大于我们的深度限制，则直接返回（可行性剪枝）。

- **2、模拟过程的处理**

本题的操作类型多，不易处理，我也没啥好说的。在这里提醒一下各位：注意输入和模拟过程的细节即可 ~~（本人第一遍打的时候把 5 打成了 35 导致RE）~~。

至于过程的存储，首先在结构体中存入一个 string 类变量，这种变量可以快速进行加入、删除以及比较操作，所以用它保存已经操作的过程。最后找到答案时，将它与已经搜到的答案字符串进行比较即可。

**Code**
```cpp
#include<cstdio>
#include<queue>
#include<cstring>
#include<iostream>
#define For(i, l, r) for(int i = l; i <= r; ++i)
#define Rof(i, r, l) for(int i = r; i >= l; --i)
using namespace std;
//快读快写有需要可嫖
inline int read(){
	int s = 0, f = 1;
	char c = getchar();
	while(c < '0' || c > '9'){
		if (c == '-') f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9'){
		s = s * 10 + c - '0';
		c = getchar();
	}
	return s * f;
}
inline void write(int x){
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
int a[10][10], p;
string ans;
struct node{
	int a[10][10], cnt[5];
    //a数组是指当前状态，cnt是指中间部分每种数字的出现次数
	int h;
    //估价值保存在h中
	string step;
    //step是指各种操作
    //以下部分是各种操作
	inline void A(){
		int t = a[1][3];
		For(i, 1, 6) a[i][3] = a[i + 1][3];
		a[7][3] = t;
	}
	inline void F(){
		int t = a[7][3];
		Rof(i, 7, 2) a[i][3] = a[i - 1][3];
		a[1][3] = t;
	}
	inline void B(){
		int t = a[1][5];
		For(i, 1, 6) a[i][5] = a[i + 1][5];
		a[7][5] = t;
	}
	inline void E(){
		int t = a[7][5];
		Rof(i, 7, 2) a[i][5] = a[i - 1][5];
		a[1][5] = t;
	}
	inline void H(){
		int t = a[3][1];
		For(j, 1, 6) a[3][j] = a[3][j + 1];
		a[3][7] = t;
	}
	inline void C(){
		int t = a[3][7];
		Rof(j, 7, 2) a[3][j] = a[3][j - 1];
		a[3][1] = t;
	}
	inline void G(){
		int t = a[5][1];
		For(j, 1, 6) a[5][j] = a[5][j + 1];
		a[5][7] = t;
	}
	inline void D(){
		int t = a[5][7];
		Rof(j, 7, 2) a[5][j] = a[5][j - 1];
		a[5][1] = t;
	}
    //update函数用来计算估价，同时用来判断是否已经满足条件
	inline bool update(){
		cnt[1] = cnt[2] = cnt[3] = 0;
		int maxn = 0, p;
		For(i, 3, 5){
			if (i == 3 || i == 5) For(j, 3, 5){
				cnt[a[i][j]]++;
				if (cnt[a[i][j]] > maxn) maxn = cnt[a[i][j]], p = a[i][j];
			}
			else{
				cnt[a[i][3]]++;
				if (cnt[a[i][3]] > maxn) maxn = cnt[a[i][3]], p = a[i][3];
				cnt[a[i][5]]++;
				if (cnt[a[i][5]] > maxn) maxn = cnt[a[i][5]], p = a[i][5];
			}
		}
		h = 8 - maxn;
		if (!h) return 1;
		return 0;
	}
};
inline bool init(){
	a[1][3] = read();
	if (!a[1][3]) return 0;
	For(i, 1, 7){
		if (i == 3 || i == 5) For(j, 1, 7) a[i][j] = read();
		else if (i != 1) a[i][3] = read(), a[i][5] = read();
		else a[1][5] = read();
	}
	return 1;
}
//dfs部分
inline void dfs(node now, int k, int d){
	//更新估价函数
	now.update();
    //我们要求字典序最小的操作方案，所以可以剪枝
	if (now.step > ans) return;
    //IDA*默认剪枝
	if (k + now.h > d) return;
	if (k == d){
		ans = now.step, p = now.a[3][3];
		return;
	}
    //枚举各种操作
    //我打了一个没啥用的剪枝--不进行与上次操作相反的操作
	if (now.step.back() != 'F'){
		now.A(), now.step += 'A';
		dfs(now, k + 1, d); now.F(), now.step.pop_back();
	}
	if (now.step.back() != 'E'){
		now.B(), now.step += 'B';
		dfs(now, k + 1, d); now.E(), now.step.pop_back();
	}
	if (now.step.back() != 'H'){
		now.C(), now.step += 'C';
		dfs(now, k + 1, d); now.H(), now.step.pop_back();
	}
	if (now.step.back() != 'G'){
		now.D(), now.step += 'D';
		dfs(now, k + 1, d); now.G(), now.step.pop_back();
	}
	if (now.step.back() != 'B'){
		now.E(), now.step += 'E';
		dfs(now, k + 1, d); now.B(), now.step.pop_back();
	}
	if (now.step.back() != 'A'){
		now.F(), now.step += 'F';
		dfs(now, k + 1, d); now.A(), now.step.pop_back();
	}
	if (now.step.back() != 'D'){
		now.G(), now.step += 'G';
		dfs(now, k + 1, d); now.D(), now.step.pop_back();
	}
	if (now.step.back() != 'C'){
		now.H(), now.step += 'H';
		dfs(now, k + 1, d); now.C(), now.step.pop_back();
	}
	return;
}
int main(){
	while(init()){
		int i = 0;
		node s;
		p = 0;
		For(i, 1, 7) For(j, 1, 7) s.a[i][j] = a[i][j];
		while(1){
        	//初始化“极大值”
			ans = "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ";
			dfs(s, 0, i);
			if (p){
				if (i == 0) printf("No moves needed\n");
				else cout << ans << endl;
				write(p), putchar('\n');
				break;
			}
			++i;
		}
	}
	return 0;
}
```


---

## 作者：cqbzjyh (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/UVA1343)

### Solution.

IDA* $+$ 模拟

对于这道题，我们的估价函数为中间 $8$ 个数数值数量最多的数字个数与 $8$ 的差值。然后再加上每种移动的模拟即可。没什么思维难度，纯靠模拟能力。

### Code.

有点长，将就看吧。

```cpp
#include <bits/stdc++.h>
//#define int long long
using namespace std;
template <typename T>
void read (T &x) {
    x = 0; T f = 1;
    char ch = getchar ();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar ();
    }
    x *= f;
}
char For_Print[25];
template <typename T>
void write (T x) {
    if (x == 0) { putchar ('0'); return; }
    if (x < 0) { putchar ('-'); x = -x; }
    int poi = 0;
    while (x) {
        For_Print[++poi] = x % 10 + '0';
        x /= 10;
    }
    while (poi) putchar (For_Print[poi--]);
}
template <typename T>
void print (T x, char ch) {
    write (x); putchar (ch);
}

int a[11][11];
int now[11][11];
//以下为四种操作的函数
void A() {
	int t = a[1][3];
	for (int i = 1; i < 7; i++) {
		a[i][3] = a[i + 1][3];
	}
	a[7][3] = t;
}
void B() {
	int t = a[1][5];
	for (int i = 1; i < 7; i++) {
		a[i][5] = a[i + 1][5];
	}
	a[7][5] = t;
}
void C() {
	int t = a[3][7];
	for (int i = 7; i >= 2; i--) {
		a[3][i] = a[3][i - 1];
	}
	a[3][1] = t;
}
void D() {
	int t = a[5][7];
	for (int i = 7; i >= 2; i--) {
		a[5][i] = a[5][i - 1];
	}
	a[5][1] = t;
}
void E() {
	int t = a[7][5];
	for (int i = 7; i >= 2; i--) {
		a[i][5] = a[i - 1][5];
	}
	a[1][5] = t;
}
void F() {
	int t = a[7][3];
	for (int i = 7; i >= 2; i--) {
		a[i][3] = a[i - 1][3];
	}
	a[1][3] = t;
}
void G() {
	int t = a[5][1];
	for (int i = 1; i < 7; i++) {
		a[5][i] = a[5][i + 1];
	}
	a[5][7] = t;
}
void H() {
	int t = a[3][1];
	for (int i = 1; i < 7; i++) {
		a[3][i] = a[3][i + 1];
	}
	a[3][7] = t;
}
int dep;
int A_star() {
	int t = 0;
	int b[4] = {};
	b[a[3][3]]++, b[a[3][4]]++, b[a[3][5]]++;
	b[a[4][3]]++, b[a[4][5]]++;
	b[a[5][3]]++, b[a[5][4]]++, b[a[5][5]]++;
	return 8 - max(max(b[1], b[2]), b[3]);
}
char ans[10005];
bool IDA_DFS(int t) {
	int dif = A_star();
	if (dif == 0) {
		return true;	
	}
	if (dif + t - 1 > dep) return false;//A*优化
	A();
	ans[t] = 'A';
	if (IDA_DFS(t + 1)) return true;
	F();
	B();
	ans[t] = 'B';
	if (IDA_DFS(t + 1)) return true;
	E();
	C();
	ans[t] = 'C';
	if (IDA_DFS(t + 1)) return true;
	H();
	D();
	ans[t] = 'D';
	if (IDA_DFS(t + 1)) return true;
	G();
	E();
	ans[t] = 'E';
	if (IDA_DFS(t + 1)) return true;
	B();
	F();
	ans[t] = 'F';
	if (IDA_DFS(t + 1)) return true;
	A();
	G();
	ans[t] = 'G';
	if (IDA_DFS(t + 1)) return true;
	D();
	H();
	ans[t] = 'H';
	if (IDA_DFS(t + 1)) return true;
	C();
	return false;
}
signed main() {
	while (scanf("%d", &a[1][3]) != EOF) {
		if (a[1][3] == 0) return 0;
		read(a[1][5]);
		read(a[2][3]), read(a[2][5]);
		for (int i = 1; i <= 7; i++) read(a[3][i]);
		read(a[4][3]), read(a[4][5]);
		for (int i = 1; i <= 7; i++) read(a[5][i]);
		read(a[6][3]), read(a[6][5]);
		read(a[7][3]), read(a[7][5]);
		for (int i = 1; i <= 7; i++) {
			for (int j = 1; j <= 7; j++) {
				now[i][j] = a[i][j];
			}
		}
		if (A_star() == 0) {
			puts("No moves needed");
			print(a[3][3], '\n');
		} else {
			for (dep = 1; ; dep++) {//枚举深度
				for (int i = 1; i <= 7; i++) {
					for (int j = 1; j <= 7; j++) {
						a[i][j] = now[i][j];
					}
				}
				if (IDA_DFS(1)) {
					for (int i = 1; i <= dep; i++) {
						putchar(ans[i]);
					}
					putchar('\n');
					print(a[3][3], '\n');
					break;
				}
			}	
		}
		
	}
    return 0;
}
```

---

## 作者：Unnamed114514 (赞：0)

### Update
2022.6.27 因为删掉剪切板重新补上代码。
***
算法： IDA*

对于 IDA\*，其实就是迭代加深启发式搜索。

从某种意义上来说，这道题的关键点在于两个：

1. 模拟

注意细节，不用多讲。

2. 回溯
注意实现一次操作后要还原原数组。
***
接下来是 IDA\* 部分。

首先是 $g(x)$，这也是最好想的，就是它所走的步数。 

接下来我们分析一下估价函数 $h(x)$：对于每次移动，我们可以发现在中间有两个数会不变，有一个数会被删除，有一个数会被加上，也就是说满足题意的数最多会加一。

那么 $F(x)=g(x)+h(x)$，如果这个深度大于要搜索的深度，就 `return;`，这就是 A\* 最关键的一步。

然后就是实现问题了，见代码注释。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int n=24,ee[]={7,8,9,12,13,16,17,18};
int a[25],t[3];
string s;
namespace Move{
	/*
		   A     B
		   |     |
		   1     2
		   3     4
H--  5  6  7  8  9 10 11--C
          12    13
G-- 14 15 16 17 18 19 20--D
 		  21    22
		  23    24
		  |      |
		  F      E
	*/
	inline void A(){
		//1 3 7 12 16 21 23
		a[0]=a[1];
		a[1]=a[3];
		a[3]=a[7];
		a[7]=a[12];
		a[12]=a[16];
		a[16]=a[21];
		a[21]=a[23];
		a[23]=a[0];
	}
	inline void B(){
		//2 4 9 13 18 22 24
		a[0]=a[2];
		a[2]=a[4];
		a[4]=a[9];
		a[9]=a[13];
		a[13]=a[18];
		a[18]=a[22];
		a[22]=a[24];
		a[24]=a[0];
	}
	inline void C(){
		//11 10 9 8 7 6 5
		a[0]=a[11];
		a[11]=a[10];
		a[10]=a[9];
		a[9]=a[8];
		a[8]=a[7];
		a[7]=a[6];
		a[6]=a[5];
		a[5]=a[0];
	}
	inline void D(){
		//20 19 18 17 16 15 14
		a[0]=a[20];
		a[20]=a[19];
		a[19]=a[18];
		a[18]=a[17];
		a[17]=a[16];
		a[16]=a[15];
		a[15]=a[14];
		a[14]=a[0];
	}
	inline void E(){
		//24 22 18 13 9 4 2
		a[0]=a[24];
		a[24]=a[22];
		a[22]=a[18];
		a[18]=a[13];
		a[13]=a[9];
		a[9]=a[4];
		a[4]=a[2];
		a[2]=a[0];
	}
	inline void F(){
		//23 21 16 12 7 3 1
		a[0]=a[23];
		a[23]=a[21];
		a[21]=a[16];
		a[16]=a[12];
		a[12]=a[7];
		a[7]=a[3];
		a[3]=a[1];
		a[1]=a[0];
	}
	inline void G(){
		//14 15 16 17 18 19 20
		a[0]=a[14];
		a[14]=a[15];
		a[15]=a[16];
		a[16]=a[17];
		a[17]=a[18];
		a[18]=a[19];
		a[19]=a[20];
		a[20]=a[0];
	}
	inline void H(){
		//5 6 7 8 9 10 11
		a[0]=a[5];
		a[5]=a[6];
		a[6]=a[7];
		a[7]=a[8];
		a[8]=a[9];
		a[9]=a[10];
		a[10]=a[11];
		a[11]=a[0];
	}
}
using namespace Move;
inline int f(){
	t[0]=t[1]=t[2]=0;
	for(int i=0;i<8;++i)
		++t[a[ee[i]]-1];
	return 8-max(t[0],max(t[1],t[2]));
}
bool dfs(int a,int b){
	int WSH=f();
	if(!WSH)
		return 1;
	if(b+WSH>a)
		return 0;
	A();
	if(dfs(a,b+1)){
		s+='A';
		return 1;
	}
	F();
	B();
	if(dfs(a,b+1)){
		s+='B';
		return 1;
	}
	E();
	C();
	if(dfs(a,b+1)){
		s+='C';
		return 1;
	}
	H();
	D();
	if(dfs(a,b+1)){
		s+='D';
		return 1;
	}
	G();
	E();
	if(dfs(a,b+1)){
		s+='E';
		return 1;
	}
	B();
	F();
	if(dfs(a,b+1)){
		s+='F';
		return 1;
	}
	A();
	G();
	if(dfs(a,b+1)){
		s+='G';
		return 1;
	}
	D();
	H();
	if(dfs(a,b+1)){
		s+='H';
		return 1;
	}
	C();
	return 0;
}
int main(){
	while(~scanf("%d",&a[1])&&a[1]){
		for(int i=2;i<=n;++i)
			scanf("%d",&a[i]);
		bool p=1;
		for(int i=1;i<8;++i)
			if(a[ee[i]]!=a[ee[i-1]]){
				p=0;
				break;
			}
		if(p)
			puts("No moves needed");
		else{
			s.clear();
			for(int i=1;;++i){
				if(dfs(i,0)){
					reverse(s.begin(),s.end());
					cout<<s<<endl;
					break;
				}
			}
		}
		cout<<a[ee[0]]<<endl; 
	}
	return 0;
}
```

---

## 作者：BigJoker (赞：0)

# 前言

这题很板，但是很码。

本人没有打多久，一遍过的样子，但是代码是真的长。

# Solution

由于不明确步数，BFS 可能会炸空间。考虑使用迭代加深搜索，但是由于搜索状态过于庞大，考虑使用 A* 对其优化。

那么启发函数如何写呢，其实不用太精确只要看八个格子上还有那些不合法就行了，这样肯定是比真正的步数小的。

然后搜索就行了，这个启发函数主要是用来剪枝，这样跑得就更快了。

当然对于这个特殊的迷宫，使用一个数组进行模拟就行。对于还原使用其跟他方向相反的就可以了。

注意要求字典序最小，所以要么改一下顺序，或者遍历完再求最小都是可以的。

# Code

```cpp
#include<bits/stdc++.h>
#define _min(a,b,c) min(a,min(b,c))
#define _max(a,b,c) max(a,max(b,c))
using namespace std;
int a[25],a1[25];
int ans,all;
string anss;
int StarX(int x){
	int res=0;
	if(a1[7]==x) res++;
	if(a1[8]==x) res++;
	if(a1[9]==x) res++;
	if(a1[12]==x) res++;
	if(a1[13]==x) res++;
	if(a1[16]==x) res++;
	if(a1[17]==x) res++;
	if(a1[18]==x) res++;
	return res;
}
void init(){
	for(int i=1;i<=24;i++) a1[i]=a[i];
}
void ChangeA(){
	int x1=a1[1],x2=a1[3],x3=a1[7],x4=a1[12],x5=a1[16],x6=a1[21],x7=a1[23];
	a1[1]=x2,a1[3]=x3,a1[7]=x4,a1[12]=x5,a1[16]=x6,a1[21]=x7,a1[23]=x1;
}
void ChangeF(){
	int x1=a1[1],x2=a1[3],x3=a1[7],x4=a1[12],x5=a1[16],x6=a1[21],x7=a1[23];
	a1[1]=x7,a1[3]=x1,a1[7]=x2,a1[12]=x3,a1[16]=x4,a1[21]=x5,a1[23]=x6;
}
void ChangeB(){
	int x1=a1[2],x2=a1[4],x3=a1[9],x4=a1[13],x5=a1[18],x6=a1[22],x7=a1[24];
	a1[2]=x2,a1[4]=x3,a1[9]=x4,a1[13]=x5,a1[18]=x6,a1[22]=x7,a1[24]=x1;
}
void ChangeE(){
	int x1=a1[2],x2=a1[4],x3=a1[9],x4=a1[13],x5=a1[18],x6=a1[22],x7=a1[24];
	a1[2]=x7,a1[4]=x1,a1[9]=x2,a1[13]=x3,a1[18]=x4,a1[22]=x5,a1[24]=x6;
}
void ChangeC(){
	int x1=a1[5],x2=a1[6],x3=a1[7],x4=a1[8],x5=a1[9],x6=a1[10],x7=a1[11];
	a1[5]=x7,a1[6]=x1,a1[7]=x2,a1[8]=x3,a1[9]=x4,a1[10]=x5,a1[11]=x6;
}
void ChangeH(){
	int x1=a1[5],x2=a1[6],x3=a1[7],x4=a1[8],x5=a1[9],x6=a1[10],x7=a1[11];
	a1[5]=x2,a1[6]=x3,a1[7]=x4,a1[8]=x5,a1[9]=x6,a1[10]=x7,a1[11]=x1;
}
void ChangeD(){
	int x1=a1[14],x2=a1[15],x3=a1[16],x4=a1[17],x5=a1[18],x6=a1[19],x7=a1[20];
	a1[14]=x7,a1[15]=x1,a1[16]=x2,a1[17]=x3,a1[18]=x4,a1[19]=x5,a1[20]=x6;
}
void ChangeG(){
	int x1=a1[14],x2=a1[15],x3=a1[16],x4=a1[17],x5=a1[18],x6=a1[19],x7=a1[20];
	a1[14]=x2,a1[15]=x3,a1[16]=x4,a1[17]=x5,a1[18]=x6,a1[19]=x7,a1[20]=x1;
}
bool Astar(int step,string now){
	if(step==ans){
		if(_max(StarX(1),StarX(2),StarX(3))==8){
			if(anss>now){
				if(StarX(1)==8) all=1;
				if(StarX(2)==8) all=2;
				if(StarX(3)==8) all=3;
				anss=now;
			}
			return 1;
		}
		return 0;
	}
	if(step+8-_max(StarX(1),StarX(2),StarX(3))>ans) return 0;
	bool f=0;
	ChangeA();
	f|=Astar(step+1,now+"A");
	ChangeF();
	ChangeF();
	f|=Astar(step+1,now+"F");
	ChangeA();
	ChangeB();
	f|=Astar(step+1,now+"B");
	ChangeE();
	ChangeE();
	f|=Astar(step+1,now+"E");
	ChangeB();
	ChangeC();
	f|=Astar(step+1,now+"C");
	ChangeH();
	ChangeH();
	f|=Astar(step+1,now+"H");
	ChangeC();
	ChangeD();
	f|=Astar(step+1,now+"D");
	ChangeG();
	ChangeG();
	f|=Astar(step+1,now+"G");
	ChangeD();
	return f;
}
int main(){
	while(cin>>a[1] && a[1]){
		for(int i=2;i<=24;i++) scanf("%d",&a[i]);
		init();
		ans=0;
		while(!Astar(0,"")){
			init();
			ans++;
			anss="";
			for(int i=0;i<=ans;i++) anss+="Z";
		}
		if(ans==0) printf("No moves needed\n");
		else cout<<anss<<endl;
		printf("%d\n",all);
	}
	return 0;
}
```

---

## 作者：风羽跃 (赞：0)

### IDA* 算法

IDA*（带有估价函数的迭代加深） = ID(迭代加深dfs）+ A*(估价函数）

听起来很高大上是吗?

其实很简单，咱们一个一个说。

所谓**迭代加深**，顾名思义，就是不断加深搜索深度。

在 dfs 的过程中会形成一颗搜索树，dfs 的特点就是找到一个子树就硬着头皮往下拱，不管拱到多深，这样的时间复杂度很容易炸。

有些题目中，我们能看出答案在搜索树中非常浅的位置，这样的话就可以从小到大限制搜索深度。

什么意思？

就是先假设最大深度为1，如果没搜到再设为2重新搜……以此类推

显然，会有一部分被重复遍历，但这点重复遍历与任凭其深度增大相比还是微不足道滴~

**估价函数**就是在迭代加深的基础上，我们估算一下**最好情况下还需要走几步**，如果当前步数+最好情况步数还超过限制，那就提前回溯。

对应到这道题，我们不断限制操作的步数进行迭代加深，并加入一个剪枝：减掉互逆操作（显然互逆操作没有意义……）

估价函数：最好情况下，每操作一次中间就能多一个我们想要的数，因此估价函数 = 8 - 中间最多的数的个数

注意实现的细节，具体看代码吧。

### Code：

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}

//输入的时候给每个位置都标上号 

const int opt[8][7]=//每一步操作拉动了那些点
{
	{22,20,15,11,6,2,0},
	{23,21,17,12,8,3,1},
	{4,5,6,7,8,9,10},
	{13,14,15,16,17,18,19},
	{1,3,8,12,17,21,23},
	{0,2,6,11,15,20,22},
	{19,18,17,16,15,14,13},
	{10,9,8,7,6,5,4}
};
const int oppo[8]={5,4,7,6,1,0,3,2};//逆操作（剪枝用） 
const int cen[8]={6,7,8,11,12,15,16,17};//中间的点 

int mp[24],ans[10005];//ans记录答案 
bool flag;//游戏结束标记 

inline int f()//估价函数 
{
	int tot[4]={0},res=8;
	for(int i=0;i<8;i++) tot[mp[cen[i]]]++;
	for(int i=1;i<=3;i++){
		res=min(res,8-tot[i]);
	}
	return res;
}

inline void dfs(int x,int dep,int last)
{
	if(flag) return ;
	if(x-1+f()>dep) return ;
	if(x>dep){
		if(!f()){
			flag=true;
			for(int i=1;i<=dep;i++){
				cout<<(char)(ans[i]+'A');
			}
			cout<<endl;
			cout<<mp[6]<<endl;
		}
		return ;
	}
	for(int i=0;i<8;i++){
		if(last!=-1&&i==oppo[last]) continue;//互逆操作 
		int raw=mp[opt[i][6]];
		for(int j=6;j>=1;j--){
			mp[opt[i][j]]=mp[opt[i][j-1]]; 
		}
		mp[opt[i][0]]=raw;//旋转
		ans[x]=i;
		dfs(x+1,dep,i);
		raw=mp[opt[i][0]];
		for(int j=0;j<6;j++){
			mp[opt[i][j]]=mp[opt[i][j+1]];
		}
		mp[opt[i][6]]=raw;//回溯，再倒着转回去 
	}
}

int main()
{
	while(cin>>mp[0]){
		if(!mp[0]) return 0;
		flag=false;
		for(int i=1;i<=23;i++){
			cin>>mp[i];
		}
		if(!f()){
			puts("No moves needed");
			cout<<mp[6]<<endl;
			continue;
		}
		for(int i=1;i<=100000;i++){
			dfs(1,i,-1);
			if(flag) break;
		}
	}
	return 0;
}


```


---

## 作者：luckydrawbox (赞：0)

## 分析

显然，这题需要**深搜**。

我们先记 ``A`` 到 ``H`` 的操作分别为 $1$ 到 $8$，深搜的同时，全局建一个 ``vector`` 型变量 $ans$ 记录答案，对于当前的状态，我们有 $8$ 种移动方式，不断往下搜即可。

#### 一个剪枝

我们的 $ans$ 种存储了上一次的操作，显然，如果执行上一次的逆操作，那么状态就会回到上一次移动前的状态，造成等效冗余，不能满足最小次数的要求，所以每次不应执行上一次的逆操作。

每个操作的逆操作对应如下：

```
1-6 2-5 3-8 4-7
5-2 6-1 7-4 8-3
```

#### 一个优化

显然，~~如果这题仅仅是这样就不是蓝题了，~~ 我们还需要更多的优化。

可以发现，在每个状态下，如果中间的 $8$ 个格子出现次数最多的数字出现了 $x$次，而每次修改只能增加或减少不超过 $1$ 个出现次数最多的数字，那么想要凑满 $8$ 个至少要 $8-x$ 次，我们可以使用启发式搜索**IDA\*** ，设估价函数 $g()$ 表示当前状态下最少需要的操作次数，从 $1$ 开始从小到大限制搜索的次数，设当前操作次数为 $now$，限制步数为 $step$，若 $now+g()>step$，则返回不可行。

## 代码

```cpp
#include<bits/stdc++.h>
#define mec(a,b) memcpy(a,b,sizeof(a));
using namespace std;
const int N=15;
int a[N][N],step,num[4],dui[9]={0,6,5,8,7,2,1,4,3};
vector<int>ans;
int g()//估价函数
{
	num[1]=num[2]=num[3]=0;
	for(int i=3;i<6;i++)
		for(int j=3;j<6;j++) 
		{
			if(i!=4||j!=4)
				num[a[i][j]]++;//统计出现最多的数的次数
		}
	return 8-max(num[1],max(num[2],num[3]));
}
void move(int op)//移动
{
	switch(op)
	{
		case 1:for(int i=1;i<8;i++)a[i-1][3]=a[i][3];a[7][3]=a[0][3];break;
		case 2:for(int i=1;i<8;i++)a[i-1][5]=a[i][5];a[7][5]=a[0][5];break;
		case 3:for(int i=7;i;i--)a[3][i+1]=a[3][i];a[3][1]=a[3][8];break;
		case 4:for(int i=7;i;i--)a[5][i+1]=a[5][i];a[5][1]=a[5][8];break;
		case 5:for(int i=7;i;i--)a[i+1][5]=a[i][5];a[1][5]=a[8][5];break;
		case 6:for(int i=7;i;i--)a[i+1][3]=a[i][3];a[1][3]=a[8][3];break;
		case 7:for(int i=1;i<8;i++)a[5][i-1]=a[5][i];a[5][7]=a[5][0];break;
		case 8:for(int i=1;i<8;i++)a[3][i-1]=a[3][i];a[3][7]=a[3][0];break;
	}
}
bool dfs(int now)
{
	int gu=g();
	if(!gu)//以成功就返回1
		return 1;
	if(now+gu>step)//超过限制返回0
		return 0;
	int b[N][N];
	mec(b,a);//复制状态
	for(int i=1;i<9;i++)
	{
		if(ans.size()&&ans.back()==dui[i])//不是第一次操作且是逆操作就不执行这个操作
				continue;
		move(i);
		ans.push_back(i);
		if(dfs(now+1))
			return 1;
		ans.pop_back();
		mec(a,b);//改变状态
	}
	return 0;
}
int main()
{
    while(cin>>a[1][3]&&a[1][3])
    {
    	ans.clear();
    	step=0;
    	cin>>a[1][5]>>a[2][3]>>a[2][5];
    	for(int i=1;i<=7;i++)
    		cin>>a[3][i];
    	cin>>a[4][3]>>a[4][5];
    	for(int i=1;i<=7;i++)
    		cin>>a[5][i];
    	cin>>a[6][3]>>a[6][5]>>a[7][3]>>a[7][5];
    	while(!dfs(0))
			step++;
    	if(step)
    	{
    		for(int i=0;i<ans.size();i++)
    			putchar(ans[i]+'A'-1);
    		printf("\n");
		}
		else printf("No moves needed\n");
		printf("%d\n",a[3][3]);
	}
	return 0;
}
```


---

## 作者：wzkdh (赞：0)

这是道IDA* 的模板题，但是数据的读入和处理有些复杂，在操作是略有难度，个人感觉本人的读入还是比较好理解的（~~过于蒟蒻写不出其他读入~~）


------------

IDA* 就是增加了估价函数的深度优先搜索，估价函数一般是理想情况下最少还要执行的步数，如果当前所进行的步数加上估价函数的步数已经超过了限制，则直接返回。所以要求估价函数所估计出的步数要比实际还要进行的步数少。

至于这道题，因为每次操作只能将一个数字移出中心区域并把一个数字加进来，所以估价函数为统计中间部分有多少个空格和中间数量最多的数字不同。

具体内容请查看代码注释
```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

int a[9][9],co[4],maxn,ans;//a:存图 co:计数 maxn:中间部分数量最多的数字 ans:迭代计数 
char bz[1000000];//记录移动步骤 
const int back[]={0,6,5,8,7,2,1,4,3};//操作的逆操作，既用于还原，也用于剪枝（防止搜索时搜索逆操作） 
const int x[]={3,5,3,5,1,2,3,4,5,6,7,3,5,1,2,3,4,5,6,7,3,5,3,5};//读图时的x坐标 
const int y[]={1,1,2,2,3,3,3,3,3,3,3,4,4,5,5,5,5,5,5,5,6,6,7,7};//读图时的y坐标 
const int centenx[]={3,4,5,3,5,3,4,5};//中间部分的x坐标 
const int centeny[]={3,3,3,4,4,5,5,5};//中间部分的y坐标 
struct f{
	int s;
	char hs,fx;
}b[9];//记录每个操作的轴坐标，方向，横竖 

int init()
{
	for(int i=0;i<24;i++)
	{
		int b;
		scanf("%d",&b);
		if(b==0)
			return 0;
		a[y[i]][x[i]]=b;
	}
	return 1;
}//读入 

int gj()
{
	memset(co,0,sizeof(co));
	int maxx=-1;
	for(int i=0;i<8;i++)
	{
		co[a[centeny[i]][centenx[i]]]++;
	}
	for(int i=1;i<4;i++)
	{
		if(co[i]>maxx)
		{
			maxn=i;
			maxx=co[i];
		}
	}
	return 8-maxx;
}//估价函数，最理想情况为每一步增加中间部分一个正确的数字 

void move(int ff)
{
	int fx=b[ff].fx,hs=b[ff].hs,s=b[ff].s;
	if(fx=='s'&&hs=='s')
	{
		for(int i=0;i<7;i++)
		{
			a[i][s]=a[i+1][s];
		}
		a[7][s]=a[0][s];a[0][s]=0;
		return;
	}
	if(fx=='s'&&hs=='h')
	{
		for(int i=0;i<7;i++)
		{
			a[s][i]=a[s][i+1];
		}
		a[s][7]=a[s][0];a[s][0]=0;
		return;
	}
	if(fx=='x'&&hs=='s')
	{
		for(int i=8;i>1;i--)
		{
			a[i][s]=a[i-1][s];
		}
		a[1][s]=a[8][s];a[8][s]=0;
		return;
	}
	if(fx=='x'&&hs=='h')
	{
		for(int i=8;i>1;i--)
		{
			a[s][i]=a[s][i-1];
		}
		a[s][1]=a[s][8];a[s][8]=0;
		return;
	}
}//移动函数 

bool dfs(int now,int last,int limit)
{
	if(!gj())
	{
		return 1;
	}//估价为0，直接返回1 
	if(gj()+now>limit)
	{
		return 0;
	}//估价与实际的和超出限制，直接返回0 
	for(int i=1;i<=8;i++)
	{
		if(i==back[last])
			continue;//防止逆操作 
		move(i);
		bz[now+1]=i+'A'-1;//记录步骤 
		if(dfs(now+1,i,limit))//如果深搜返回1，证明找到答案，继续向上返回1 
			return 1;
		move(back[i]);//还原图 
	}
	return 0;
}

int main()
{
	b[1].fx='s';b[1].hs='s';b[1].s=3;
	b[2].fx='s';b[2].hs='s';b[2].s=5;
	b[3].fx='x';b[3].hs='h';b[3].s=3;
	b[4].fx='x';b[4].hs='h';b[4].s=5;
	b[5].fx='x';b[5].hs='s';b[5].s=5;
	b[6].fx='x';b[6].hs='s';b[6].s=3;
	b[7].fx='s';b[7].hs='h';b[7].s=5;
	b[8].fx='s';b[8].hs='h';b[8].s=3;//初始化b结构体数组 
	while(init())
	{
		if(!gj())
		{
			printf("No moves needed\n%d\n",maxn);
			continue;
		}//开始正确直接输出 
		for(ans=1;;ans++)
		{
			if(dfs(0,0,ans))
			{
				break;
			}
		}//迭代深搜 
		for(int i=1;i<=ans;i++)
			printf("%c",bz[i]);
		printf("\n%d\n",maxn);//输出 
	}
	return 0;
} 

---

