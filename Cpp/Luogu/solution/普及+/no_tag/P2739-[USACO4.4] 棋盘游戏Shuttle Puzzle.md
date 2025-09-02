# [USACO4.4] 棋盘游戏Shuttle Puzzle

## 题目描述

大小为 $3$ 的棋盘游戏里有 $3$ 个白色棋子，$3$ 个黑色棋子，和一个有 $7$ 个格子一线排开的木盒子。$3$ 个白棋子被放在一头，$3$ 个黑棋子被放在另一头，中间的格子空着。

初始状态: `WWW_BBB`（`_` 代表空格）

目标状态: `BBB_WWW`

在这个游戏里有两种移动方法是允许的：

- 你可以把一个棋子移到与它相邻的空格；
- 你可以把一个棋子跳过一个(仅一个)与它不同色的棋子到达空格。

大小为 $N$ 的棋盘游戏包括 $N$ 个白棋子，$N$ 个黑棋子，还有有 $2N+1$ 个格子的木盒子。

这里是大小为 $3$ 的棋盘游戏的解，包括初始状态，中间状态和目标状态：

`WWW_BBB` → `WW_WBBB` → `WWBW_BB` → `WWBWB_B` → `WWB_BWB` → `W_BWBWB` → `_WBWBWB` → `BW_WBWB` → `BWBW_WB` → `BWBWBW_` → `BWBWB_W` → `BWB_BWW` → `B_BWBWW` → `BB_WBWW` → `BBBW_WW` → `BBB_WWW`

请编一个程序求解大小为 $N$ 的棋盘游戏（$1 \le N \le 12$）。要求用最少的移动步数实现。

## 说明/提示

题目翻译来自NOCOW。

USACO Training Section 4.3

## 样例 #1

### 输入

```
3```

### 输出

```
3 5 6 4 2 1 3 5 7 6 4 2 3 5 4```

# 题解

## 作者：珅肐 (赞：11)

不少题解都用了找规律的方法，其实我觉得这才是正解，

毕竟搜索比较麻烦，有人的减枝还是根据不知怎么推出的答案来限制最大值，如果是考试可以，但平常做题还是不要这样（那还不如打表）

虽然有不少找规律的题解，但都仅限于找规律，并没有说明为什么，这里详细解释一下。

我相信大家的找规律能力

应该都能发现

我们把还未移动时的个空位也算上的话

$4$ $3$ $5$ $6$ $4$ $2$ $1$ $3$ $5$ $7$ $6$ $4$ $2$ $3$ $5$ $4$ $(n=3)$

$5$ $4$ $6$ $7$ $5$ $3$ $2$ $4$ $6$ $8$ $9$ $7$ $5$ $3$ $1$ $2$ $4$ $6$ $8$ $7$ $5$ $3$ $4$ $6$ $5$$(n=4)$

排一下

$4$ $ $ $ $ $35$ $ $ $ $ $642$ $ $ $ $ $1357$ $ $ $ $ $642$ $ $ $ $ $35$ $ $ $ $ $4$

$5$ $ $ $ $ $4 6$ $ $ $ $ $7 5 3$ $ $ $ $ $2 4 6 8$ $ $ $ $ $9 7 5 3 1$ $ $ $ $ $2 4 6 8$ $ $ $ $ $7 5 3$ $ $ $ $ $4 6$ $ $ $ $ $5$

规律挺明显

共$2n+1$个等差序列，长度从$1$到$n$再到$1$，而且后面与前面是对称的

我们讨论第$1$~$n+1$组序列，这些序列满足


- 第奇数个序列公差为$-2$，第偶数个序列公差为$2$

- 对于第$i$个序列$(1<=i<=n+1)$,若为第奇数个序列则首项为$n+i$，第偶数个序列则首项为$n-i+2$

那为什么会这样呢

我们研究一下下它的规则

注：下文皆用"移"表示移到相邻空格，"跳"表示跳过一个棋子,且开始左白右黑

每次都是白色棋子移过去，黑色棋子跳过来，然后黑色棋子移过来，白色棋子跳过去，白色棋子跳过去，白色棋子移过去，黑色棋子跳过来，黑色棋子跳过来，黑色棋子跳过来，

就是说每次先移动一步，然后对应颜色的棋子一直跳，直到不能跳为止，接下来换另一种颜色棋子移一步，再继续跳啊跳

（建议画图，会非常清楚）

黑棋只往左走，白棋只向右走，容易发现，这样一定是最优的，

这样前半部分就说完了

至于后半部分为什么是对称的呢

我们进行完前$n$组后，棋盘会变成：

空 白 黑 白 黑 ... 白 黑

第$n+1$组后，棋盘就变成了：

黑 白 黑 白 ...黑 白 空

这两者是对称的，我们之前从开始局面到$n$局面做的

反过来做一遍就可以从$n+1$局面到第$2n+1$局面

就是说，第$n+1$遍的作用是使序列翻转，然后我们就可以倒过来再做

这就是对称的原因

以上

希望对你有所帮助
```cpp
#include<iostream>
#include<cstdio>
#include<ctype.h>
using namespace std;
inline int read(){
    int x=0,f=0;char ch=getchar();
    while(!isdigit(ch))f|=ch=='-',ch=getchar();
    while(isdigit(ch))x=x*10+(ch^48),ch=getchar();
    return f?-x:x;
}
int f[17][17];
inline void check(int x){
	if(x%20==0)puts("");
}
int main(){
	int n=read(),cnt=0;
	for(int i=1;i<=n+1;++i){
		if(i&1)for(int j=0;j<i;++j)f[i][j]=n+i-j-j;
		else for(int j=0;j<i;++j)f[i][j]=n-i+j+j+2;
	}
	for(int i=2;i<=n+1;++i)for(int j=0;j<i;++j)printf("%d ",f[i][j]),check(++cnt);
	for(int i=n;i>=1;--i)for(int j=0;j<i;++j)printf("%d ",f[i][j]),check(++cnt);
	return 0;
}

```


---

## 作者：yhk1001 (赞：10)

# P2739 [USACO4.4]棋盘游戏Shuttle Puzzle题解
这是一道可以练习搜索的好题，我采用的是dfs和剪枝优化。

观察样例，发现白子只往右走、黑子只往左走，那么搜索总共也就四种情况：白子挪一格、白子跳一格、黑子挪一格、黑子跳一格。（注意只能跳过一个**不同**颜色的棋子）

剪枝也很好想，记录最少所用的步数，如果当前步数已经比它大了，就直接返回，避免因多次递归而超时。

奉上AC代码$\;$[通过记录](https://www.luogu.com.cn/record/34800659)
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int n,a[10005],b[10005],sum = 2147483647;
string now = " ",tar = " ";//now是当前状态，tar是目标状态
void dfs(int step,int pos)//step是已用步数，pos是空格位置
{
	if (step >= sum)//剪枝
		return ;
	if (now == tar)//更新答案
	{
		sum = step;
		for (int i = 1;i <= step;i++)
		{
			a[i] = b[i];
		}
		return ;
	}
	if (pos - 2 > 0 && now[pos - 2] == 'W' && now[pos - 1] == 'B')//白子跳一格 
	{
		b[step + 1] = pos - 2;
		now[pos - 2] = ' ';
		now[pos] = 'W';
		dfs(step + 1,pos - 2);
		b[step + 1] = 0;//回溯
		now[pos - 2] = 'W';
		now[pos] = ' ';
	}
	if (pos - 1 > 0 && now[pos - 1] == 'W')//白子挪一格 
	{
		b[step + 1] = pos - 1;
		now[pos - 1] = ' ';
		now[pos] = 'W';
		dfs(step + 1,pos - 1);
		b[step + 1] = 0;
		now[pos - 1] = 'W';
		now[pos] = ' ';
	}
	if (pos + 1 <= n * 2 + 1 && now[pos + 1] == 'B')//黑子挪一格 
	{
		b[step + 1] = pos + 1;
		now[pos + 1] = ' ';
		now[pos] = 'B';
		dfs(step + 1,pos + 1);
		b[step + 1] = 0;
		now[pos + 1] = 'B';
		now[pos] = ' ';
	}
	if (pos + 2 <= n * 2 + 1 && now[pos + 2] == 'B' && now[pos + 1] == 'W')//黑子跳一格 
	{
		b[step + 1] = pos + 2;
		now[pos + 2] = ' ';
		now[pos] = 'B';
		dfs(step + 1,pos + 2);
		b[step + 1] = 0;
		now[pos + 2] = 'B';
		now[pos] = ' ';
	}
	return ;
}

int main()
{
	cin >> n;
	for (int i = 1;i <= n;i++)//产生初始状态与目标状态
	{
		now += 'W';
		tar += 'B';
	}
	now += ' ';
	tar += ' ';
	for (int i = 1;i <= n;i++)
	{
		now += 'B';
		tar += 'W';
	}
	dfs(0,n + 1);
	for (int i = 1;i <= sum;i++)
	{
		cout << a[i] << " ";
		if (i % 20 == 0)//每行20个数
			cout << endl;
	}
	cout << endl;
    return 0;
}
```
点个赞再走吧！

---

## 作者：Dadatu (赞：5)


//大家都是搜索的，我来发一篇规律的题解吧。[安利一下自己的blog](https://blog.csdn.net/Dadatu_Zhao)

我们先来手玩几组数据

n=1	1 3 2 1

n=2	2 4 5 3 1 2 4 3

n=3	3 5 6 4 2 1 3 5 7 6 4 2 3 5 4

我们来把中间空着那个格子放到第一位，再调整一下布局。

n=1	2 13 2

n=2	3 24 531 24 3

n=3	4 35 642 1357 642 35 4

总结一下规律

1 前n+1组数每组的大小等于组序数，并且后以n+1组数为与之前对称

2 每组数内公差为2

3 奇数组为降序且首项为n+i

4 偶数组为升序且首项为n-i+2

接下来就是写程序啦

```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
using namespace std;

int res[1010];
int n,tot,len;

int main()
{
	scanf("%d",&n);
	for (int i=1;i<=n+1;i++)//i表示组数
	{
		if (!(i%2))//奇数组
			for (int j=0;j<i;j++) res[++tot]=n-i+2+2*j;
		else//偶数组
			for (int j=0;j<i;j++) res[++tot]=n+i-2*j;
	}
	//输出
	for (int i=2;i<=tot;i++) 
	{
		//这里其实可以写个函数，懒得改了=。=
		len++;if (len%20==0) len=0;
		if (!len) printf("%d\n",res[i]);
		else printf("%d ",res[i]);
	}
	for (int i=n;i>=1;i--)
	{
		for (int j=(i*i-i)/2+1;j<=(i*i+i)/2;j++)//用的是等差数列的和，(首项+尾项)*项数/2，来输出对称的第i组数
		{
			len++;if (len%20==0) len=0;
			if (!len) printf("%d\n",res[j]);
			else printf("%d ",res[j]);
		}

	}

	return 0;
}

```



---

## 作者：Celebrate (赞：5)

这一道题我们采用深搜+剪枝，照样是0ms，运行内存

2175kb，还算不错了，这一道题的正解其实是贪心，但是我就

直接搜索了，宽搜其实可以更快

经过观察发现:白只往右，黑只往左

其实每次搜索也就只有4种情况

还有第二种跳法棋子只能跳过一个棋子（我被这里坑了好久）

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int bk=false,minn=168,a[51];//min为n=12的最小步数，单靠这一个，就可以大量的剪枝 
int k[210],d[210];
void dfs(int s,int p,int t)//s为当前步数，p为空格的位置，t为最左边的白子的位置 
{
	if(s-1>minn) return;//如果超过了最大值 
	if(s-1==minn && bk==true) return;//如果等于最大值而且已经被搜过了 
	if(p==n+1 && t==n+2)//如果排好了 
	{
		minn=s-1;bk=true;
		for(int i=1;i<=minn;i++) d[i]=k[i];//记录下来 
	}
	int tt;
	if(p-1>=1 && a[p-1]==1)//左边的白子跳到空格 
	{
		k[s]=p-1;
		if(t==p-1) tt=p;//判断最左边 
		else tt=t;
		swap(a[p-1],a[p]);
		dfs(s+1,p-1,tt);
		swap(a[p-1],a[p]);
	}
	if(p+1<=n*2+1 && a[p+1]==2)//右边的黑子跳到空格 
	{
		k[s]=p+1;
		swap(a[p],a[p+1]);
		dfs(s+1,p+1,t);
		swap(a[p],a[p+1]);
	}
	if(p-2>=1 && a[p-2]==1 && a[p-1]==2)//左边的白子跳过黑子到达空格 
	{
		k[s]=p-2;
		if(t==p-2) tt=p;
		else tt=t;
		swap(a[p-2],a[p]);
		dfs(s+1,p-2,tt);
		swap(a[p-2],a[p]);
	}
	if(p+2<=n*2+1 && a[p+2]==2 && a[p+1]==1)//右边的黑子进过白子跳到空格 
	{
		k[s]=p+2;
		swap(a[p],a[p+2]);
		dfs(s+1,p+2,t);
		swap(a[p],a[p+2]);
	}
}
int main()
{
	int i;
	scanf("%d",&n);
	memset(a,63,sizeof(a));
	a[n+1]=0;
	for(i=1;i<=n;i++) //初始化 
	{
		a[i]=1;
		a[n+1+i]=2;
	}
	dfs(1,n+1,1);
	for(i=1;i<=minn;i++) //输出 
	{
		printf("%d ",d[i]);
		if(i%20==0) printf("\n");
	}
	if(minn%20!=0) printf("\n");
	return 0;
}
```

---

## 作者：popcoount (赞：3)

这道题我用的是迭代加深+暴搜的写法（似乎题解里都没有迭代加深的写法，来补一下）。

首先我们构造出起点和终点：

```cpp
st = st + string(n, 'W') + ' ' + string(n, 'B');
ed = ed + string(n, 'B') + ' ' + string(n, 'W');
/*
当n = 3时
st = "WWW BBB"
ed = "BBB WWW"
*/
```

然后开始迭代加深搜索：

```cpp
int dep = 1; // dep表示每次迭代加深的最深深度
while (dep++) if (dfs(st, n, dep, 0)) break; // 成功了就跳出
```

搜索部分（注意交换完位置一定不要忘记恢复现场）：

```cpp
bool dfs(string &u, int k, int maxd, int dep) {
	// u是目前状态
   // k表示从0开始第几位是空格
   // maxd见上
   // dep为目前深度
	if (dep > maxd) return false; // 深度超过了最大深度
	ans[dep] = k; // 记录答案
	if (u == ed) return true; // 搜索成功
	int len = u.size();
	if (k - 1 >= 0 and u[k - 1] != 'B') { // 跳到前一个
		swap(u[k - 1], u[k]);
		if (dfs(u, k - 1, maxd, dep + 1)) return true;
		swap(u[k - 1], u[k]);
	}
	if (k + 1 < len and u[k + 1] != 'W') { // 跳到后一个
		swap(u[k], u[k + 1]);
		if (dfs(u, k + 1, maxd, dep + 1)) return true;
		swap(u[k], u[k + 1]);
	}
	if (k - 2 >= 0 and u[k - 2] != 'B' and u[k - 1] != 'W') { // 跳过前一个
		swap(u[k - 2], u[k]);
		if (dfs(u, k - 2, maxd, dep + 1)) return true;
		swap(u[k - 2], u[k]);
	}
	if (k + 2 < len and u[k + 2] != 'W' and u[k + 1] != 'B') { // 跳过后一个
		swap(u[k], u[k + 2]);
		if (dfs(u, k + 2, maxd, dep + 1)) return true;
		swap(u[k], u[k + 2]);
	}
	return false;
}
```

输出第 $i$ 步答案的时候只需要输出 $ans[i] + 1$ 就可以了（注意这道题有特殊的输出方式）。

# [完整代码](https://www.luogu.com.cn/paste/ypn6tp42)

---

## 作者：lxzy_ (赞：2)

//大佬们代码写辣么短，菜菜发抖中

做法：双向 bfs

最近学了这个知识点，于是考场上压根没往 DFS 或者找规律那一块想，最后打了个没有优化双向 bfs，并且没有输出换行，喜提 20pts.

由于题目中的起始状态都已确定，因此可以将起始两状态都放入队列，并打上是从起点开始还是从终点开始的标记 mp ，加入储存空格位置的 ans ，然后开始广搜。

由于考场上想打表，于是我直接暴力使用 string 存的状态，标记直接用 map ，储存答案用 vector

对于当前搜索到的状态 pre ，通过移动棋子得到下一个状态 f ，如果 $mp[pre] = mp[f]$ 说明它们都是从起点或终点搜过来的，不需要管；如果 $mp[f] = 0$ ，如果 $mp[pre] != mp[f]$ 说明它们分别从起点和终点都过来，双向搜索第一次相遇即是最优解，将答案输出，这里要注意从终点搜过来的点要倒叙输出。

光是这样还不够，由于有四种转移方式，而序列长度为 25 ，最坏要跑 $O(4^{24})$ ，考虑剪枝。

可以发现，在最优解的情况下白起必定往右走，黑棋必定往左走（否则就没有意义，多余了），因此可以在枚举状态的时候判断一下。

最后以 909ms 的优秀成绩跑过了，喜提最优解最后一名。


目前来说应该是最长（ 110 行）也是最复杂的代码， ~~别跟我说压行~~

```cpp
#include<cstdio>
#include<iomanip>
#include<queue>
#include<iostream>
#include<vector>
#include<map>
using namespace std;
const int N=1e6+50;
const int M=2e6+50;
map<string,string> ans;
map<string,int> mp;
string st,ed;
int n;
queue<string> que;
void Init()//起始状态预处理
{
	for(int i=1;i<=n;i++) st+='W',ed+='B';
	st+='_',ed+='_';
	for(int i=1;i<=n;i++) st+='B',ed+='W';
}
bool Check(string pre,string f,int pos,int opt)
{
	if(mp[f]==opt) return false;//f和pre都是从起点或终点过来的，不管
	if(mp[f]==0){//f还没有遍历到
		mp[f]=opt;
		ans[f]=ans[pre]+char(pos);//加上当前空格位置
		que.push(f);
		return false;
	}
	//若mp[f]!=mp[pre]，则输出
	int ed=ans[pre].size();
	int sss=0;
	for(int i=1;i<ed;i++){
		sss++;
		printf("%d",ans[pre][i]);
		if(sss%20==0) printf("\n");
		else printf(" ");
	}
	ed=ans[f].size();
	for(int i=ed-1;i>=0;i--){//从终点搜的那一段要倒叙
		sss++;
		printf("%d ",ans[f][i]);
		if(sss%20==0) printf("\n");
		else printf(" ");
	}
	return true;
}
int Get(string f)//获取空格位置，这里本来可以直接继承的，但是我懒得写了（bushi
{
	int ed=f.size();
	for(int i=0;i<ed;i++){
		if(f[i]=='_') return i;
	}
	return 0;
}
void BFS()
{
	que.push(st),que.push(ed);
	mp[st]=-1,mp[ed]=1;
	ans[st].push_back(char(n+1));
	ans[ed].push_back(char(n+1));
	
	while(!que.empty()){
		
		string f=que.front();
		string pre=f;
		que.pop();
		int pos=Get(f)+1;//这里的pos是题目中的空格位置，所以下面在字符串中查找都要-1
		
		/* 左->右 跳  */
		if(pos-3>=0&&f[pos-3]=='W'&&f[pos-2]!=f[pos-3]){
			swap(f[pos-3],f[pos-1]);
			if(Check(pre,f,pos-2,mp[pre])) break;
			swap(f[pos-1],f[pos-3]);
		}
		/* */
		
		/* 相邻 跳 */
		if(pos-2>=0&&f[pos-2]=='W'){
			swap(f[pos-1],f[pos-2]);
			if(Check(pre,f,pos-1,mp[pre])) break;
			swap(f[pos-2],f[pos-1]);
		}
	
	
		if(pos<2*n+1&&f[pos]=='B'){ 
			swap(f[pos],f[pos-1]);
			if(Check(pre,f,pos+1,mp[pre])) break;
			swap(f[pos-1],f[pos]);
		} 
		/* */
		
		
		/* 右->左 跳 */
		if(pos+1<2*n+1&&f[pos+1]=='B'&&f[pos]!=f[pos+1]){
			swap(f[pos-1],f[pos+1]);
			if(Check(pre,f,pos+2,mp[pre])) break;
			swap(f[pos+1],f[pos-1]);
		} 
		/*   */
		
	}
}
int main()
{
	scanf("%d",&n);
	Init();
	BFS();
	return 0;
}
```

---

## 作者：攀岩高手 (赞：2)

楼上的题解似乎没有用位运算的，我来写一个^\_^

- 思路


和楼上的题解相似，设白子只能像前（右）走，黑子只能向后（左）走，则状态数一定是有限的，也就不会发生无限递归这种情况。


因为白子和黑子可以分别用1和0表示，所以我们可以用一个二进制数表示dfs的状态。此外，棋盘中的空位也用0表示，并在dfs中记录一个p表示空格的位置。然后就可以愉快地搜索了^\_^

- 初始化


我们第一个状态是前n位都是白子（1），第n+1位是空位，n+2位到2n+1位都是黑子（0）。


比如当n=3时，第一个状态是111**0**000（加粗部分是空位）


这个状态可以用位运算的式子`(1<<(n<<1|1))-1^(1<<n+1)-1`表示（这里的n<<1|1可以代替2\*n+1，位运算的优先级请自行百度）。

- 搜索


搜索的边界是当前状态等于目标状态。目标状态就是`(1<<n)-1`，别忘了还需要判断空位位置`p==n+1`。


因为我们知道空位的位置，所以我们可以只枚举空格前后各两个位置了。


minn记录最少步数，d数组记录当前方案，ans数组记录答案方案


- 代码


0ms AC，自认为代码还是比较短的，细节请参见注释



```cpp
#include <cstdio>
#include <cstring>
const int MAXN=200; // 当n<=12时，答案最多168步
int n, minn=MAXN;
int d[MAXN], ans[MAXN];
void dfs(int x, int p, int step) // x记录当前状态，p记录空位位置，step记录当前步数
{
    if (step>=minn) return ; // 剪枝
    if (x==(1<<n)-1&&p==n+1) // 边界条件
    {
        minn=step; // 更新答案
        memcpy(ans, d, sizeof ans);
        return ;
    }
    for (int i=p-2>1?p-2:1; i<=p+2&&i<=(n<<1|1); i++) // 枚举下一个状态，注意棋子的边界位置
        if (i<p&&x&1<<(n<<1|1)-i||i>p&&!(x&1<<(n<<1|1)-i)) // 白子只能往右，黑子只能往左
            // 通过位运算处理下一步状态，i是下一个状态的空位的位置
            d[step]=i, dfs((x|((x&1<<(n<<1|1)-i)>>p-i))&~(1<<(n<<1|1)-i), i, step+1);
}
int main()
{
    scanf("%d", &n);
    dfs((1<<(n<<1|1))-1^(1<<n+1)-1, n+1, 0); // 处理第一个状态并搜索
    for (int i=0; i<minn; i++) // 输出答案
    {
        printf("%d ", ans[i]);
        if (i%20==19) printf("\n"); // 记得20个数换一次行
    }
    return 0;
}
```

---

## 作者：うっせぇわ (赞：1)

### 解法

这里提供一个特别暴力但是特别好想的做法……

首先，最暴力的思想是搜索，于是我们这里就可以想搜索做法。

本人不怎么喜欢写 `dfs`，所以这里用的是 `bfs` 的做法。

初始化不用多说，我们考虑 `while` 循环里面的内容；

这道题所描述的变量很多，我们考虑使用结构体。

题面中描述，一个棋子可以跳过不同颜色的棋子并且可以往旁边的空格移动，并且空格只有一个，所以可以往结构体存入空格的位置；

我们还要获取当前序列的字符串，将这个也存入结构体；

最终题目要求输出整数类型操作序列。这个有许多种存法，但是我们要追求 ~~无脑~~ 易懂的代码，所以，我们直接把这些整数类型的序列转化成字符串存入结构体，输出时直接用一个函数转化成整数输出。

接下来应该对状态进行操作了。如果直接按常规的方法进行处理，你的程序在 $n=12$ 时仅仅只跑了 $10000+$ 秒。这里介绍一个极其有效的剪枝。

既然最后白棋都得走向左边，黑棋都得走向右边，就没必要处理与其相反的状况了。所以在状态处理的时候，砍掉向右边走的白棋和向左边走的黑棋的情况，这样搜索树就小了很多。

最后还有一个问题：这个算法第一个搜到的合法状态不一定是字典序最小的状态。所以我们就搜到第二个符合要求并且字典序比最开始搜索到的解小的解时输出。为什么不用继续往下搜？因为 `BFS` 是按照搜索树一层一层搜的，这一层的最优解已经搜到了，再继续往下搜长度一定比之前的大了。

这里直接放代码，看注释看的可能更清楚。

```
#include <bits/stdc++.h>
using namespace std;
int n,cnt=0;
string ans="zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
//ans的初始状态要设大一点 
map<string,string> ma;
string goal="X",sta="X";//初始化字符串长度为1，在循环时就可以按普通数列操作了 
struct node{
	string str;//当前棋盘状态 
	int pos;//空的位置 
	string rec;//当前的操作序列 
};
queue<node> q;
bool check(string c,string d){
	if(c.length()<d.length()){
		return true;
	}else if(c.length()==d.length()){
		for(int i=1;i<=c.length();i++){
			if(c[i]>d[i]){
				return false;
			}
			else if(c[i]<d[i])return true;
		}
	}
	return false;
}//对比当前操作序列字典序是否更小 
string num(int x){
	string g="";
	if(x>=48&&x<=57){
		return g+char(x);
	}else if(x>=58&&x<=67){
		return g+"1"+char(x-10);
	}else{
		return g+"2"+char(x-20);
	}
}//将是字符串的操作序列转化成整数 
int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		goal+="B";//goal是目标状态 
		sta+="W";//sta是开始状态 
	}
	goal+=" ";
	sta+=" ";
	for(int i=0;i<n;i++){
		goal+="W";
		sta+="B";
	}
	q.push((node){sta,n+1,""});//刚开始的状态 
	while(!q.empty()){
		node tmp=q.front();
		q.pop();
		if(tmp.str==goal){//如果达到目标状态 
			if(tmp.rec.length()<ans.length()){
				ans=tmp.rec;
				cnt++;
			}else if(tmp.rec.length()==ans.length()){
				for(int i=0;i<tmp.rec.length();i++){
					if(ans[i]>tmp.rec[i]){
						ans=tmp.rec;
						cnt++;
						break;
					}
				}
			} 
			//比较 
			int l=0;
			if(cnt==2){//如果是第二个比原来小的序列了 
				for(int i=0;i<ans.length();i++){
					l++;
					cout<<num(ans[i])<<" ";
					if(l==20){
						l=0;
						cout<<endl;
					}
				}
			}//输出 
		}
		string sp=tmp.str;
		if(tmp.pos+1<=2*n+1){//处理向右移动 
			if(sp[tmp.pos+1]=='B'){
				swap(sp[tmp.pos+1],sp[tmp.pos]);		
		    	if(ma[sp]==""||check(ma[sp],tmp.rec+(char)(tmp.pos+1+48))){
					q.push((node){sp,tmp.pos+1,tmp.rec+(char)(tmp.pos+1+48)});
					ma[sp]=tmp.rec+(char)(tmp.pos+1+48);
				}
			}
		}
		//ma记忆化此状态是否搜索过，已经搜索过并且不比原来的解优就不搜（虽然好像没什么用，删了也行） 
		sp=tmp.str;//重置 
		if(tmp.pos-1>=1){//处理向左移动 
			if(sp[tmp.pos-1]=='W'){
				swap(sp[tmp.pos-1],sp[tmp.pos]);
				if(ma[sp]==""||check(ma[sp],tmp.rec+(char)(tmp.pos-1+48))){
		    		q.push((node){sp,tmp.pos-1,tmp.rec+(char)(tmp.pos-1+48)});
		    		ma[sp]=tmp.rec+(char)(tmp.pos-1+48);
				}
			}
		}
		sp=tmp.str;
		if(tmp.pos+2<=2*n+1){//处理向左跳 
			if(sp[tmp.pos+1]!=sp[tmp.pos+2]&&sp[tmp.pos+2]=='B'){
				swap(sp[tmp.pos],sp[tmp.pos+2]);
				if(ma[sp]==""||check(ma[sp],tmp.rec+(char)(tmp.pos+2+48))){
		    		q.push((node){sp,tmp.pos+2,tmp.rec+(char)(tmp.pos+2+48)});
		    		ma[sp]=tmp.rec+(char)(tmp.pos+2+48);
				}
			}
		}
		sp=tmp.str;
			if(sp[tmp.pos-1]!=sp[tmp.pos-2]&&sp[tmp.pos-2]=='W'){//处理向右跳 
				swap(sp[tmp.pos],sp[tmp.pos-2]);
				if(ma[sp]==""||check(ma[sp],tmp.rec+(char)(tmp.pos-2+48))){
		    		q.push((node){sp,tmp.pos-2,tmp.rec+(char)(tmp.pos-2+48)});
		    		ma[sp]=tmp.rec+(char)(tmp.pos-2+48);
		    	}
			}
		}
	}
	return 0;
}
```

这份代码是完全可以用更聪明的方法让它变得更好看，但是我们既然要 ~~无脑~~ 易懂，也就无伤大雅了。 

---

## 作者：zhangjianweivv (赞：1)

可能之前大佬们也用过我这种方法......不过我看到的基本上都是用贪心的（太强了）。我太菜了，不会推公式，于是就很暴力地用BFS做的。

还有就是顺序要考虑一下。如果有多组解的话就是按字典序排，所以下面的判断顺序是要严格讲究的。

好，直接上代码吧。

```cpp
/*
ID:zhangji78
LANG:C++
TASK:shuttle
*/
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
struct node
{
	int tx,fa;
	short int x[26];
    //这里卡内存，开到26就可以了（12*2+1）
    //tx存该状态中空格的位置
    //fa表示该状态是由哪个状态演变过来的
    //x数组表示该状态
}list[120000];
int n,m,a[26],b[26],head,tail,d[169],len;
bool pd(int x)
{
	for(int i=1;i<=m;i++)
	{
		if(list[x].x[i]!=list[0].x[i])return false;
	}
    //list[0]中存的是目标状态
	return true;
}
void pnt(int x)
{
	len=0;memset(d,0,sizeof(d));
	while(list[x].fa!=-1)
	{
		d[++len]=list[x].tx;
		x=list[x].fa;//fa的作用：寻找与记录
	}
	int t=0;
	for(int i=len;i>1;i--)
	{
		t++;
		if(t%20!=0)printf("%d ",d[i]);//注意每20个换一次行
		else printf("%d\n",d[i]);
	}
	printf("%d\n",d[1]);
	return ;
}
void bfs()
{
	while(head<tail)
	{
		int i;
        //顺序：left 2->left 1->right 1->right 2
		i=list[head].tx-2;
		if(i>=1&&list[head].x[i]==1&&list[head].x[i+1]==2)
		{
			for(int j=1;j<=m;j++)list[tail].x[j]=list[head].x[j];
			list[tail].x[i]=list[head].x[list[head].tx];
			list[tail].x[list[head].tx]=list[head].x[i];
			list[tail].tx=i;
			list[tail].fa=head;
			if(pd(tail)==true)break;
			tail++;
		}
		i=list[head].tx-1;
		if(i>=1&&list[head].x[i]==1)
		{
			for(int j=1;j<=m;j++)list[tail].x[j]=list[head].x[j];
			list[tail].x[i]=list[head].x[list[head].tx];
			list[tail].x[list[head].tx]=list[head].x[i];
			list[tail].tx=i;
			list[tail].fa=head;
			if(pd(tail)==true)break;
			tail++;
		}
		i=list[head].tx+1;
		if(i<=m&&list[head].x[i]==2)
		{
			for(int j=1;j<=m;j++)list[tail].x[j]=list[head].x[j];
			list[tail].x[i]=list[head].x[list[head].tx];
			list[tail].x[list[head].tx]=list[head].x[i];
			list[tail].tx=i;
			list[tail].fa=head;
			if(pd(tail)==true)break;
			tail++;
		}
		i=list[head].tx+2;
		if(i<=m&&list[head].x[i]==2&&list[head].x[i-1]==1)
		{
			for(int j=1;j<=m;j++)list[tail].x[j]=list[head].x[j];
			list[tail].x[i]=list[head].x[list[head].tx];
			list[tail].x[list[head].tx]=list[head].x[i];
			list[tail].tx=i;
			list[tail].fa=head;
			if(pd(tail)==true)break;
			tail++;
		}
		head++;
	}
	pnt(tail);
	return ;
}
int main()
{
//	freopen("shuttle.in","r",stdin);freopen("shuttle.out","w",stdout);
	scanf("%d",&n);
	m=n*2+1;
	for(int i=1;i<=n;i++)
	{
		list[1].x[i]=1;//初始状态
		list[1].x[i+n+1]=2;
		list[0].x[i]=2;//目标状态
		list[0].x[i+n+1]=1;
        //1表示W，2表示B，0表示空格
	}
	head=1;tail=2;list[1].tx=n+1;list[1].fa=-1;
    //简单的初始化（可以放在bfs中）
	bfs();
	return 0;
}
```

---

## 作者：TheSky233 (赞：0)

## Description

给你一个长度为 $2 \times n-1$ 的字符串，形如 $\overbrace{\texttt{WWW}\cdots \texttt{W}}^{n\text{个}\texttt{W}}\texttt{\_}\overbrace{\texttt{BBB}\cdots \texttt{B}}^{n\text{个}\texttt{B}}$，现在有两种操作：

1. 将一个字符移到和它相邻的空格中。
2. 把一个字符跳过一个（仅一个）与它不同色的棋子到达空格。

要求一个移动步数最少且字典序最小的操作序列，使得字符串变为 $\overbrace{\texttt{BBB}\cdots \texttt{B}}^{n\text{个}\texttt{B}}\texttt{\_}\overbrace{\texttt{WWW}\cdots \texttt{W}}^{n\text{个}\texttt{W}}$。

数据范围：$1\le n \le 12$。

## Solution

做法：迭代加深搜索。

注意到这题范围极小的 $n$，于是可以用搜索来做。

我们考虑每次设定一个搜索的最大深度 $dep$，每次搜索到达这个深度就返回，这样就可以控制步数最小。在这个前提下，我们每次保存一个空格的位置，与它相邻的 $4$ 个位置从左到右**依次**判断过去即可，这样保证了字典序最小。

同时，本题还需要加一个重要的剪枝优化：我们限制 $\tt W$ 只能向后跳，因为向前跳是毫无意义的，同理，$\tt B$ 只能向前跳。

## Code

```cpp
/*
  	Author: TheSky233
	Windows 11 Creation. All rights reserved.
*/
#include <bits/stdc++.h>
using namespace std;

#define Multicase() for(int T = read() ; T ; T--)
#define F(i,a,b) for(int i=(a) ;i<=(b);++i)
#define F2(i,a,b) for(int i=(a);i< (b);++i)
#define dF(i,a,b) for(int i=(a);i>=(b);--i)
#define endl '\n'
#define pb emplace_back
#define ENDL putchar('\n')

const int N=5e5+5;
const int M=1e6+5;
const int MN=1e3+5;

void Solve();

int n,m,q,k,p;
int a[N],b[N],f[N];
vector<int> step;
string chess,now,goal;

int main(){
	Solve();
}

int dep;

bool IDDFS(int space,int x,const int dep){
	if(x>dep)
		return now==goal;
	if(space>1 && now[space-1]!=now[space-2] && now[space-2]=='W'){
		swap(now[space],now[space-2]);
		step.pb(space-2);
		if(IDDFS(space-2,x+1,dep)) return true;
		step.pop_back();
		swap(now[space],now[space-2]);
	}
	if(space>0 && now[space-1]=='W'){
		swap(now[space],now[space-1]);
		step.pb(space-1);
		if(IDDFS(space-1,x+1,dep)) return true;
		step.pop_back();
		swap(now[space],now[space-1]);
	}
	if(space<=2*n && now[space+1]=='B'){
		swap(now[space],now[space+1]);
		step.pb(space+1);
		if(IDDFS(space+1,x+1,dep)) return true;
		step.pop_back();
		swap(now[space],now[space+1]);
	}
	if(space<2*n && now[space+1]!=now[space+2] && now[space+2]=='B'){
		swap(now[space],now[space+2]);
		step.pb(space+2);
		if(IDDFS(space+2,x+1,dep)) return true;
		step.pop_back();
		swap(now[space],now[space+2]);
	}
	return false;
}

void Solve(){
	cin>>n;
	F(i,1,n) chess+='W'; chess+=' ';
	F(i,1,n) chess+='B';
	F(i,1,n) goal+='B'; goal+=' ';
	F(i,1,n) goal+='W';
	now=chess;
	for(;!IDDFS(n,0,dep);dep++) now=chess;
	for(int i=0;i<step.size();i++){
		cout<<step[i]+1<<' ';
		if((i+1)%20==0) ENDL;
	}
	return;
}
```

---

## 作者：Drinkwater (赞：0)

感觉这道题难度是被低估了，考虑到深搜，如果不加以限制，就会一直卡下去，尝试加过一个羞耻性剪枝（++cnt > 100000；break；）发现毫无意义，然后就开始对这道题进行深入地分析，然后就有一种类似于贪心的思路，也不知道对不对，把样例过了，发现居然A了，好神奇，看了题解发现跟楼下诺诺的想法是一样的，就是1一直往后走，2一直往前走，然后就不会有无限递归的问题了，也没有判重的必要（开始用hash和map发现毫无意义），就这样就好了，挺快的，1ms，比楼下那位快了不少。（但是好像写法是一样的，估计是人长得太帅了没办法）

/*************************************************************************

    > Author: Drinkwater-cnyali
    > Created Time: 2017/5/5 21:57:06
************************************************************************/














```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
#define REP(i, a, b) for(register int i = (a), i##_end_ = (b); i <= i##_end_; ++ i)
#define DREP(i, a, b) for(register int i = (a), i##_end_ = (b); i >= i##_end_; -- i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mem(a, b) memset((a), b, sizeof(a))
template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }
int read()
{
    int sum = 0, fg = 1; char c = getchar();
    while(c < '0' || c > '9') { if (c == '-') fg = -1; c = getchar(); }
    while(c >= '0' && c <= '9') { sum = sum * 10 + c - '0'; c = getchar(); }
    return sum * fg;
}
const int maxn = 100000;
const int inf = 0x3f3f3f3f;
int n,a[20],pre[maxn],cnt;
bool check()
{
    REP(i,1,n/2)if(a[i] == 1)return 0;
    if(a[n/2+1]!=0)return 0;
    return 1;
}
int ans[maxn],ff = inf;
int ccc = 0;
void dfs(int x)
{
    if(cnt > ff)return ;
    if(check())
    {
        if(cnt < ff)
        {
            ff = cnt;
            REP(i,1,cnt)ans[i] = pre[i];
        }
        else
        {
            int flag = 0;
            REP(i,1,cnt)if(ans[i] < pre[i]){flag = 1;break;}
            if(!flag)REP(i,1,ff)ans[i] = pre[i];
        }
        return ;
    }
    if(x > 1 && a[x-1] == 1)
    {
        int tmp = a[x-1];
        a[x-1] = 0,a[x] = tmp,pre[++cnt] = x-1;
        dfs(x-1);
        a[x-1] = tmp,a[x] = 0,--cnt;
    }
    if(x < n && a[x+1] == 2)
    {
        int tmp = a[x+1];
        a[x+1] = 0,a[x] = tmp,pre[++cnt] = x+1;
        dfs(x+1);
        a[x+1] = tmp,a[x] = 0,--cnt;
    }
    if(x > 2 && a[x-2] == 1 && a[x-1] == 2)
    {
        int tmp = a[x-2];
        a[x-2] = 0,a[x] = tmp,pre[++cnt] = x-2;
        dfs(x-2);
        a[x-2] = tmp,a[x] = 0,--cnt;
    }
    if(x < n - 1 && a[x+2] == 2 && a[x+1] == 1)
    {
        int tmp = a[x+2];
        a[x+2] = 0,a[x] = tmp,pre[++cnt] = x+2;
        dfs(x+2);
        a[x+2] = tmp,a[x] = 0,--cnt;
    }
}
int main()
{
    n = read();
    n = n * 2 + 1;
    REP(i,1,n/2)a[i] = 1;
    REP(i,n/2+2,n)a[i] = 2;
    dfs(n/2+1);
    REP(i,1,ff)
    {
        cout<<ans[i]<<" ";
        if(i%20 == 0)cout<<endl;
    }
    return 0;
}

```

---

## 作者：Till_Gloam (赞：0)

关于这道题， 就是深搜

不过， 如果是每次枚举每一个位置， 就会T（30分）

如果每次移动是任意的， 就会无限递归

所以， 有以下两点：

1:    1（黑） 只能向后走， 2（白） 只能向前走

2:    我们dfs中记录每层0（空格）的位置， 就只需要判断它附近的4个位置就行了

细节：

1：棋子越界

2：输出没有分行







```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
int n, b[30];
int q[300000];
int Ans = 300000, a[300000];
bool P(){            //判断是否结束
    int i;
    if(b[n + 1]) return 0;
    for(i = 1; i <= n; ++i) if(b[i] == 1) return 0;
    return 1;
}
void get_ans(int cnt){          //更新答案
    int i;
    if(cnt < Ans){
        Ans = cnt;
        for(i = 1; i <= cnt; ++i) a[i] = q[i];
        return ;
    }
    bool flag = 1;
    for(i = 1; i <= cnt; ++i)
        if(a[i] < q[i]){
            flag = 0;
            break;
        }
    if(flag) for(i = 1; i <= cnt; ++i) a[i] = q[i];
}
void dfs(int x, int now){
    int i;
    if(now > Ans) return ;            //显然剪枝。。。
    if(P()){
        get_ans(now);
        return ;
    }
    if(b[x - 1] == 1){             //枚举4个方案
        b[x] = 1;
        b[x - 1] = 0;
        q[now + 1] = x - 1;
        dfs(x - 1, now + 1);
        b[x - 1] = 1;
        b[x] = 0;
    }
    if(b[x + 1] == 2){
        b[x] = 2;
        b[x + 1] = 0;
        q[now + 1] = x + 1;
        dfs(x + 1, now + 1);
        b[x + 1] = 2;
        b[x] = 0;
    }
    if(x > 1 && b[x - 1] == 2 && b[x - 2] == 1){
        b[x] = 1;
        b[x - 2] = 0;
        q[now + 1] = x - 2;
        dfs(x - 2, now + 1);
        b[x - 2] = 1;
        b[x] = 0;
    }
    if(x < (n << 1) + 1 && b[x + 1] == 1 && b[x + 2] == 2){
        b[x] = 2;
        b[x + 2] = 0;
        q[now + 1] = x + 2;
        dfs(x + 2, now + 1);
        b[x + 2] = 2;
        b[x] = 0;
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("Usa.in", "r", stdin);
    freopen("Usa.out","w",stdout);
#endif
    int i;
    scanf("%d", &n);
    for(i = 1; i <= n; ++i) b[i] = 1;
    for(i = n + 2; i <= (n << 1) + 1; ++i) b[i] = 2;
    dfs(n + 1, 0);
    for(i = 1; i <= Ans; ++i){
        printf("%d ", a[i]);
        if(!(i % 20)) printf("\n");                    //记得分行
    }
    return 0;
}
```

---

## 作者：Vin_1999 (赞：0)

这道题好像难度定低了吧，至少也有提高-啊。

如果没想到找规律的话大部分人都会dfs+剪枝吧。

那我们来分析一下这个操作图有什么特点。

1、若总行数为n,很容易发现以（n/2)（向上取整）的那一行呈中心对称。（对称性）

2、空格的移动总是起始先向左移一格，再向右移动到行末，再向左......（特殊规律）

这两个规律就很有用了，但我们还需要做出进一步推论。

让我们观察一下操作的规律，记移动为1，跳为2，左l右r。

那么，当n=1时，操作情况为 1r 2l 1r.

n=2:1r,2l, 1l,2r,2r 1l,2l,  1r

n=3:1r,2l,1l,2r,2r,  1r,2l,2l,2l,  1r,2r,2r,1l,2l, 1r

n>3懒得列举。

你会发现移动规律总是1一步2好几步，而且2的步数还有一个先增后减的关系，而且方向上也存在一个特殊关系，（我就不说太明了自己思考吧）。说明这些单调性和对称性都是很重要的。如果这道题用dfs的话，最多有c(25,3)\*c(25,1)个状态，那就爆了啊。

然后就是很简单的模拟了（你要是打表也是可以的）。话说这是part4为数不多的我没看题解做出来的题。

然后献上本蒟蒻丑陋的代码。






```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<cstdio>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<climits>
#define rep(i,s,n) for(int (i)=(s);(i)<=(n);(i)++)
using namespace std;
int n,a[200],cur,cnt=1;
void work(int dep,int mv)
{
    if(dep==n)
    {
        a[cnt++]=cur;cur+=mv*2;
        rep(i,1,n-1) a[cnt++]=cur,cur+=mv*2;
        a[cnt++]=cur,cur-=mv;
    }
    else
    {
        a[cnt++]=cur;cur+=mv*2;
        rep(i,1,dep-1) a[cnt++]=cur,cur+=mv*2;
        a[cnt++]=cur,cur+=mv;
        work(dep+1,mv/-1);
        a[cnt++]=cur;cur+=mv*2;
        rep(i,1,dep-1) a[cnt++]=cur,cur+=mv*2;
        a[cnt++]=cur,cur-=mv;
    }
}
int main()
{
    freopen("e:/out.txt","w",stdout);
     scanf("%d",&n);
     cur=n;
     work(1,1);// 1 right,-1 left
     a[cnt++]=cur;
     for(int i=1;i<n*(n+2);)
     {
         for(int j=1;j<=20&&i<n*(n+2);i++,j++)
         {
             printf("%d ",a[i]);
      }
      if(i==n*(n+2)) printf("%d",a[i]);
      else printf("\n");
  }
    return 0;
}//by lyyz-ljy

```

---

