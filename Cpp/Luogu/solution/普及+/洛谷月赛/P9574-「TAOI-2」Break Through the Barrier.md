# 「TAOI-2」Break Through the Barrier

## 题目描述

有一个由 $\tt B$ 和 $\tt T$ 组成的字符串。

你可以进行如下操作：选择一个长度为 $4$ 的子串，其恰好等于 $\texttt{BTTB}$，并将其修改为 $\texttt{TBBT}$。你可以进行这种操作任意多次（也可以不操作）。

定义一个字符串的权值为最长的 $\texttt{T}$ 连续段长度。你需要通过如上操作使得字符串的权值尽可能大。输出这个最大值。

+ 子串的定义：一个字符串 $b$ 被称为字符串 $a$ 的子串，当且仅当可以通过删除 $a$ 开头若干个（可以是 $0$ 个，下同）字符和结尾若干个字符得到 $b$。
+ $\texttt{T}$ 连续段的定义：一个原字符串的仅由 $\texttt{T}$ 构成的子串。

## 说明/提示

**本题采用捆绑测试。**

记 $\sum n$ 为所有数据中的 $n$ 的和。

+ Subtask 0（5 pts）：$n \leq 7$。
+ Subtask 1（20 pts）：$T \leq 10$，$n \leq 10$。
+ Subtask 2（25 pts）：$\sum n \leq 5000$。
+ Subtask 3（5 pts）：保证给定的字符串无法进行任何操作。
+ Subtask 4（45 pts）：无特殊限制。

对于所有数据，$1 \leq T \leq 10^3$，$1 \leq n \leq 10^5$，$1 \leq \sum n \leq 5\times 10^5$，字符串只包含字符 `B` 和 `T`。

## 样例 #1

### 输入

```
6
3
TTT
4
BTTB
5
TBBTT
6
BTBTBB
7
BTTBTTB
17
TTBTBTTBTBTTTBTTB
```

### 输出

```
3
2
2
1
3
5
```

# 题解

## 作者：EdenSky (赞：11)

# [P9574 Break Through the Barrier](https://www.luogu.com.cn/problem/P9574)
- [或许更好的阅读体验](https://www.cnblogs.com/wanguan/p/18343918)

## 思路分析

分析样例：

```txt
== TTBT BTTBTB TTT BTTB
-> TTBT TBBTTB TTT BTTB
-> TTBT TBTBBT TTT BTTB
-> TTBT TBTBBT TTT TBBT
----1-----2-----3---4--
```

观察区块 2，发现 `BTTB` 进行操作后与右边的 `TB` 再次构成 `BTTB`，我们发现在这个区块内，可以从左向右不断操作，我们称这种特性为传递性，可以发现其具有方向。

假设区块 2 右边有更多的 `TB`，例如 `BTTBTBTBTBTB`，是否仍然存在传递性呢？没错，你可以在纸上试一下，答案肯定。

推论 1：具有 `BTTB TBTB...` 特征的区块中，可以向右不断操作，操作具有传递性，方向向右。

那我们再反过来看呢？难道就不能向左不断操作吗？

我们在区块 2 的左边加上一些 `BT`，可以发现可以不断向左传递。

推论 1.1：`BTTB TBTB...` 具有向右的传递性；`...BTBT BTTB` 具有向左的传递性。

综合一下：

推论 1.2：`...BTBT BTTB TBTB...` 具有双向的传递性，在它的右方传递性向右，左方则向左。

考虑极限思维，`...BTBT BTTB TBTB...` 舍去了它的尾巴，变成 `BTTB`。思考发现这也是具有双向传递性的，只不过只能连续操作 1 次。

推论 1.3：`BTTB` 也具有双向传递性。

那么，这有什么用呢？

再次观察样例（如上），可以发现通过传递性进行操作，区块 3 左边多加了一个 `T`，右边也多加了一个 `T`。是的，我们可以通过区块的传递性对某个连续 `T` 区间增加 `T`。

我们对推论 1.1 再次分析，对于区间 `BTTB TBTB...`，可以发现右边的 `B` 变成了 `T`；而对于区间 `...BTBT BTTB`，左边的 `B` 变成了 `T`。

由于区块 3 在区块 2 右边，区块 2 表现出向右的传递性，通过操作区块 2 右边的 `B` 变成 `T`，由于两个区块相邻，区块 3 连续 `T` 的长度增加 1。同理区块 4 表现出向左的传递性，邻接于区块 3，使得区块 3 连续 `T` 在右边又增加了 1。

推论 2：对于一个具有传递性的区块，它可以使它表现出的传递性方向上的邻接连续 `T` 区块长度增加 1。

可以发现，当某个具有传递性的区块进行操作后，它将损失其传递性，不再可操作，不再能给邻接 `T` 区块提供新的 `T`。也就是说：

推论 3：一个具有传递性的区块只能对其表现出的传递性方向上的邻接连续 `T` 区块贡献一次。

综合推论 2 和推论 3，我们可以得出推论 4：一个连续 `T` 区块只能收到两次贡献，来自左和右的两个方向，也就是说，每个连续 `T` 区间长度最多增加 2，其增加的 `T` 分别来源于左边和右边两个方向的与其方向**相反**的连续性区块。

从推论 4 的视角，我们再来看一次样例，我们把表现出向右连续性的区块视为 `->`，向左的视为 `<-`。

```txt
TTBT -> TTT <-
```

可以看出连续性的方向对答案是存在影响的。

如此，我们找到每个具有连续性的区块，区块左边表现出向左的连续性，并打上标记，向右也是如此，但注意要区分方向。

然后枚举一遍连续 `T` 区块，如果其某个边界处存在标记且该标记方向正确，则该方向使长度加 1，最后取所有区块这样执行后的长度的最大值即可。

蒟蒻已经尽力说清楚了 QAQ。

## 代码实现

```cpp
#define by_wanguan
#include<iostream>
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
const int N=5e5+7;
int t,n,le[N],ri[N],ans; char c[N];
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>t; while(t--){
  cin>>n; for(int i=2;i<=n+1;i++) cin>>c[i],le[i]=ri[i]=0;
  int l=1,r=l+3; ans=0; c[0]=c[1]=c[n+2]=c[n+3]='#';
  le[0]=le[1]=le[n+2]=le[n+3]=ri[0]=ri[1]=ri[n+2]=ri[n+3]=0;//初始化
  while(r<=n){//通过双指针查找有连续性的区间
    l++,r++;
    if(c[l]=='B'&&c[l+1]=='T'&&c[l+2]=='T'&&c[l+3]=='B'){
	  ri[r]++,le[l]++;//发现存在，则在两端打上标记，le的标记方向向左，ri向右
      while(c[r+1]=='T'&&c[r+2]=='B') r+=2,ri[r]++;//向左右扩展区块并打上标记（找尾巴）
      while(c[l-1]=='T'&&c[l-2]=='B') l-=2,le[l]++;
      l=r-1,r=l+3;//l跳到r的位置，在本次操作后l和r都会++，提前减1
    }
  }
  l=1,r=l;
  while(r<=n){
    l=r,l++,r++;
    if(c[l]!='T') continue;//查询连续T区间
    while(c[r+1]=='T') r++;//扩展连续T区间
    ans=max(r-l+1+ri[l-1]+le[r+1],ans);//查询是否存在标记，注意方向
  }
  cout<<ans<<'\n';
}
}
```

有点 DP 的味道，看不懂请狠狠踢我！蒟蒻会尽量解答的。

[喵。](https://www.luogu.com.cn/record/170533425)

---

## 作者：light_searcher (赞：8)

# 贪心+模拟

## $50pts$

对于每一串 `T`，两侧都可能会通过转化使得这个串变长，但是需要满足一定的条件：

- 如果有和该串的左侧紧贴的子串长这样：`BTTBTBTB···TB`，（其中 `TB` 的个数 $\ge1$），则可以使该串变长。

- 如果有和该串的右侧紧贴的子串长这样：`BTBTBT···BTTB`，（其中 `BT` 的个数 $\ge1$），则可以使该串变长。

不难发现，在一侧**最多只能使长度增加 $1$**，所以**一个串在最优情况下长度可以增加 $2$**。设变化前最长的一串 `T` 的长度为 $maxlen$，则有可能成为最长的一个串的串（好拗口）的长度必须 $\ge maxlen-1$。

基本思路就出来了，我们只要筛选长度 $\ge maxlen-1$ 的串，再分别去判断左右两边是否可以变长即可。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,maxlen,ans;
char s[N];
vector<pair<int,int> >g;
void find_out_T(){
	int bgin=0,len=0,tmp=0;
	for(int i=1;i<=n;i++)
		if(s[i]=='T'){
			tmp++;
			maxlen=max(maxlen,tmp);
		}
		else tmp=0;
	ans=maxlen;
	for(int i=1;i<=n;i++)
		if(s[i]=='T'){
			if(s[i-1]!='T') bgin=i;
			len++;
		}
		else{
			if(s[i-1]=='T'&&len>=maxlen-1)	
				g.push_back({bgin,bgin+len-1});
			len=0;
		}
	if(len>=maxlen-1) g.push_back({bgin,bgin+len-1});
}
bool search_l(int pos){
	for(int i=pos;i>=1;i-=2)
		if(s[i]=='T'&&s[i-1]=='B') return i!=pos;
		else if(s[i]!='B'||s[i-1]!='T') return 0;
	return 0;
}
bool search_r(int pos){
	for(int i=pos;i<=n;i+=2)
		if(s[i]=='T'&&s[i+1]=='B') return i!=pos;
		else if(s[i]!='B'||s[i+1]!='T') return 0;
	return 0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		maxlen=0;
		g.clear();
		scanf("%d%s",&n,s+1);
		find_out_T();
		for(int i=0;i<g.size();i++){
			int l=g[i].first,r=g[i].second;
			ans=max(ans,r-l+1+search_l(l-1)+search_r(r+1));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```
超时 $3$ 个点。

## $100pts$

发现长度为 $1$ 的串是不需要考虑的，理由如下：

分类讨论：如果长度为 $1$ 的串被选进来了，则说明变化前 $maxlen=1$ 或 $2$。 

- 当 $maxlen=1$ 时，根本无法变化，所以 $1$ 就是答案，不需要考虑。

- 当 $maxlen=2$ 时，长度为 $1$ 的串可能经过变化后成为最长的串。若只有一段可以变长，则长度变为 $2$，和 $maxlen$ 相等，则不会影响答案；若两边都可以变长，则长度变为 $3$，可能是最长的，但一定不是唯一的，举个例子：`BTTBTBTTB`，你会发现，右边的 `BTTB` 变化后，可以再变化一次，能使左边长度为 $2$ 的串长度变为 $3$，所以这种情况长度为 $1$ 的串也不会对答案造成影响。

综上，长度为 $1$ 的 `T` 的串不会对答案造成任何影响，这个剪枝加上后就过了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int T,n,maxlen,ans;
char s[N];
vector<pair<int,int> >g;
void find_out_T(){
	int bgin=0,len=0,tmp=0;
	for(int i=1;i<=n;i++)
		if(s[i]=='T'){
			tmp++;
			maxlen=max(maxlen,tmp);
		}
		else tmp=0;
	ans=maxlen;
	for(int i=1;i<=n;i++)
		if(s[i]=='T'){
			if(s[i-1]!='T') bgin=i;
			len++;
		}
		else{
			if(s[i-1]=='T'&&len>=maxlen-1)	
				g.push_back({bgin,bgin+len-1});
			len=0;
		}
	if(len>=maxlen-1) g.push_back({bgin,bgin+len-1});
}
bool search_l(int pos){
	for(int i=pos;i>=1;i-=2)
		if(s[i]=='T'&&s[i-1]=='B') return i!=pos;
		else if(s[i]!='B'||s[i-1]!='T') return 0;
	return 0;
}
bool search_r(int pos){
	for(int i=pos;i<=n;i+=2)
		if(s[i]=='T'&&s[i+1]=='B') return i!=pos;
		else if(s[i]!='B'||s[i+1]!='T') return 0;
	return 0;
}
int main(){
	scanf("%d",&T);
	while(T--){
		maxlen=0;
		g.clear();
		scanf("%d%s",&n,s+1);
		find_out_T();
		for(int i=0;i<g.size();i++){
			int l=g[i].first,r=g[i].second;
			if(l==r) continue;
			ans=max(ans,r-l+1+search_l(l-1)+search_r(r+1));
		}
		printf("%d\n",ans);
	}
	return 0;
}
```
喜提 $100pts$。



------------

好了，本题就到这里了，如果有哪里讲得不好的，欢迎指出。

---

## 作者：dino (赞：8)

###  写在前面
这题思维难度有点，个人认为绿左右(虽然可以模拟）。主要把握问题关键是两个字符串的特殊性
### 思路
赛时 T1 调太久了，这题也就少了点时间了，但还是做出来了。题目中说 $ \texttt{TBBT}$ 与 $\texttt{BTTB}$ 可互换，这个特殊在前者只能将左右两边各多出一个 $\texttt{T}$，后者直接只有两个在中间了。  
而我们就想到找出一段 $\texttt{T}$ 连续段，然后判断左边和右边是否能多一个。然后 $n^2$ 算法就出来了。即利用双指针来查找连续段，然后向左向右查找是否可以增加一个。  
### 优化
上面算法明显过不了，考虑优化。寻找优化有一个方法：处理冗余操作。每次从前往后做一遍再从后往前做一遍，实际上**每个位置是否能是增加是固定的**。
显然两边是 $\texttt{B}$ 的话（要么没了）增加一个，只有可能是 $\texttt{TB}$ 的情况，那么再前面两位应该要能**变成** $\texttt{BT}$ ，再往前的话要能变成 $\texttt{BT}$ 通过上面推导可以看出应该可以用我们的 DP 啊（抓狂）。
状态就是以 $i$ 结尾（或者开头因为后面还要再做一遍）是否能变成  $\texttt{BT}$ 和 $\texttt{TB}$。因为上面已经大致推过了就留给读者自己推。(当然代码里也有）
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int const N = 1e5 + 5;
bool ltb[N], lbt[N], rtb[N], rbt[N];//ltb和lbt是从左往右是否能变成tb或bt，rtb，rbt则反之
int main(){
	int t, n;
	cin >> t;
	while(t--){
		string s;
		cin >> n;
		cin >> s;
		s = ' ' + s;
		for(int i = 0; i <= n + 5; i++) ltb[i] = rbt[i] = lbt[i] = rtb[i] = 0;//清空记得多清几个，因为n+1要判断的（我就是这卡了半天）
		for(int i = 2; i <= n; i++){
			if(s[i] != s[i - 1]){//为bt或tb
				if(s[i] == 'T') ltb[i] = ltb[i - 2], lbt[i] = 1;
				else lbt[i] = lbt[i - 2], ltb[i] = 1;
			}
		}
		for(int i = n - 1; i >= 1; i--){
			if(s[i] != s[i + 1]){
				if(s[i] == 'T') rbt[i] = rbt[i + 2], rtb[i] = 1;
				else rtb[i] = rtb[i + 2], rbt[i] = 1;
			}
		}//上面两个循环是做dp的，方程推不出来的可以看看
		int l = 0, r = 0, mx = 0;//双指针，l是第一个t的前面一个，r是最后一个t的后面一个，mx是最长的t连续段长度
		while(r <= n){//双指针写的不太好，轻喷
			if(s[r] == 'T') r++;
			else{
				int cnt = r - l - 1;//计算长度
				if(lbt[l]) cnt++;//左边能增加一个
				if(rtb[r]) cnt++;//右边能增加一个
				mx = max(mx, cnt);
				l = r;
				r++;
			}
		}
		int cnt = r - l - 1;//最后如果是t处理一下
		if(lbt[l]) cnt++;
		if(rtb[r]) cnt++;
		mx = max(mx, cnt);
		cout << mx << endl;
	}
    return 0;
} 
```



---

## 作者：int08 (赞：4)

## 前言
众所周知，一篇题解需要一张头图：
![](https://cdn.luogu.com.cn/upload/image_hosting/5jgvc9au.png)
# Solution
美丽的 Ad-hoc，思路很杂，但是只要一点点探索，总有新发现。

## 第一阶段：找规律

1.超过三个的连续 $\tt{T}$ 串不可拆分！

原因显然，带给我们的启示是：以长 $\tt{T}$ 串把原字符串拆为几个部分。

2.最重要的：形如 $\tt{BBTTT……}$ 的形状，永远无法把第二个 $\tt{B}$ 改掉！

理由：
要改第二个得先改第一个，然而改第一个的时候就会在更左边的位置产生连续的两个 $\tt{B}$。

为什么说它很重要？它带来了新发现。

3.由上可得：对于一个长（长度大于 $2$）的 $\tt{T}$ 串，最多只能从左右各自多一个 $\tt{T}$。

理由：$\tt{BTTBTTTTT……}$ 变成了 $\tt{TBBTTTTTT……}$，出现无解双 $\tt{B}$ 串。

规律已经找到得差不多了，可以开始正式做题了。

## 第二阶段：解题

相信大家也发现了方法：

在本身没有 $\tt{T}$ 串的位置生造一个是很困难的，我们应该**在长 $\tt{T}$ 串的基础上**试着从左右运送一个 $\tt{T}$ 过来。

有一个问题：什么叫做可以运输？

首先只是交替的 $\tt{TB}$ 绝对不行，因为没有连续的两个 $\tt{T}$。

只有正好两个才可以。

即形如：$\tt{BTTBTBT……BTBTTTTTTT}$ 时候，可以从左边的长度为 $2$ 的 $\tt{T}$ 串运输一个到右边。

如果中间有连续 $\tt{B}$，哪怕是两个也会打断运输。

则做法出现：

找到原串里所有的长度大于等于 $2$ 的 $\tt{T}$ 串，检测某个串是否可以从左右传输，如可以则该 $\tt{T}$ 串统计答案时一边加一，最后找到最大值即可。

**注意贴到两边的 $\tt{T}$ 串不能往中间传！**

实现细节还是很多，上面是卡了我很久的一个。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long i,j,t,n,cb[500000],ca[500000],l[500000],p,k,ans=1;string s;
int main()
{
	cin>>t;
	for(int ac=1;ac<=t;ac++)
	{
		cin>>n>>s;
		for(i=1;i<=p+10;i++) ca[i]=cb[i]=l[i]=0;p=0;k=0;
		if(n==1&&s[0]=='T')
		{
			cout<<1<<endl;continue;
		}
		for(i=1;i<n;i++)
		{
			if(s[i]=='T'||s[i-1]=='T') k=1;
			if(s[i]=='T'&&s[i-1]=='T')
			{
				if(i==1||s[i-2]!='T')
				{
					p++;l[p]=2;
					if(i==1) ca[1]=1;
				}
				else l[p]++;
				if(i==n-1) cb[p]=1;
			}
			if(s[i]=='B'&&s[i-1]=='B') cb[p+1]=ca[p]=1;
		}
		if(p==0)
		{
			cout<<k<<endl;continue;
		}
		ans=l[1];
		for(i=1;i<=p;i++)
		{
			long long q=l[i];
			if(l[i-1]==2&&!ca[i-1]) q++;
			if(l[i+1]==2&&!cb[i+1]) q++;
			ans=max(ans,q);
		}
		cout<<ans<<endl;
	}
	return 0;
 } 
```
# The End.

---

## 作者：Neuron (赞：4)

本题是一道找规律题目。

基本的思路是：
如果出现序列 `BTTB...` 或者 `BTTBTBTB...TB`，就可以通过连续的向右操作将这两种序列之后连续的 `T` 序列 `TTT...` 的开头延长一个 `T`。

例如：
```
[BTTB]TBTBTTTTTT...
=>
TB[BTTB]TBTTTTTT...
=>
TBTB[BTTB]TTTTTT...
=>
TBTBTBBTTTTTTT...
```
*(中括号代表每一次操作选定的序列)*

同时，如果在一串 `T` 序列 `...TTT` 的结尾出现上面序列的对称形式，即 `...TTTBTTB` 或者 `...TTTBT...BTBTBTTB` 就可以将前面T的序列向后扩展一个 `T`。操作顺序与向前扩展序列的操作顺序正好相反。

思路是用一个有限状态机来维护上面的状态，识别出在连续的 `T` 串头部和尾部的拓展序列。
## Release 1.0：初步的思路
初步构建的有限状态机的状态转移图：
![](https://cdn.luogu.com.cn/upload/image_hosting/izds4mia.png)
> 这个状态机共有十一个内部状态，其中 `START` 为初始状态，是所有状态机开始运行的状态，相应的， `END` 是终结状态，状态机将在这里结束运行。状态机有一个内部变量 `tot`，该变量被用于计算 `T` 串中 `T` 的数目并最终形成输出。在每一条路径上的第一个单词表示该路径的转移条件。转移条件一共有三种：接收到 `T`，接收到 `B`，接收到 `\n` *(图中为 `EOF`)*。一些路径在转移的同时会修改内部变量。 `tot x` 意味着将内部变量 `tot` 赋值为 `x`，  `out x` 是状态机的输出， `out max x,y` 意味着输出 `x` 和 `y` 中较大的值，最终的输出为状态机在运行过程中的所有输出的最大值。

### issue:
很可惜，hack掉这个状态机十分简单。
```
BTTBTTBTTTTT
```
该序列可以通过如下修改:
```
BTT[BTTB]TTTTT
=>
BTTTBBTTTTTT
```
得到六个 `T` 连续的序列，同时也是该样例的正解，但是我们构造的状态机会输出 $5$，因为状态机仅仅会将第二个 `BTTB` 中间的 `T` 序列识别为连续的 `T`，并不会将其识别为可以被修改的序列。当运行至状态 `..TBTT` 时，再输入一个 `T` 仅仅会使得状态机重新开始计算 `T` 的数量，而忽略了该连续的 `T` 串头部同样可以扩张的可能。

## Release 2.0

重新考量状态 `..TBTT` 之后的构造。不难发现，如果状态机处于该状态并且 `tot == 3` 时， `T` 串的前方应当有一串 `BTTB` ，此时 `T` 串头部可扩展。**故该状态的转移应当由外部条件和内部变量共同决定。** 解决方案是仍不调整该点所转移到的状态，但是当 `tot == 3` 时，将 `tot` 的值赋为 $4$。

同时，在所有转移到状态 `tot++` 的路径中，有且仅有从状态 `BTTBT..` 和从前端可扩展的状态 `...TBTT` 中转移过来的路径可以构造出 `BTTB`，故设一个新的内部变量 `flag`，在通过上述两条路径转入状态 `tot++` 时将 `flag` 设为 `1`，自己转入自己的时候该变量的值不变，其他的转入路径则将该变量设为 $0$。同时，如果状态处于 `..TBTT`，当且仅当 `tot == 3` 同时 `flag == 1` 的时候可以将 `tot` 设为 $4$ 并转入状态 `tot++`。

最终的状态转移图：
![](https://cdn.luogu.com.cn/upload/image_hosting/n4khdpra.png)
> 请注意 `..TBTT` 返回 `tot++` 的节点，仅当 `tot == 3` 并且 `flag == 1` 的时候将 `tot` 修改为 $4$，这意味着序列前方存在一串 `BTTB`。

Accepted 代码：
```cpp
#include "bits/stdc++.h"
#define int long long

// 定义有限状态机的状态节点
#define START 	0
#define B_ 		1
#define BT 		2
#define BTT 	3
#define BTTB 	4
#define BTTBT 	5
#define TOT 	6
#define TB 		7
#define TBT 	8
#define TBTT 	9
#define END 	10

using namespace std;

int max(int x, int y) { return x > y ? x : y; }

// 有限状态机的实现
class solve {
public:
  int now;
  int tot;
  int Max;
  int flag;

  solve() {
    this->now = START;
    this->tot = 0;
    this->Max = 0;
    this->flag = 0;
  }

  void out(int x) { this->Max = max(Max, x); }

  void fun(char ch) {
    if (now == START) {
      if (ch == 'B') {
        now = B_;
        return;
      } else if (ch == 'T') {
        flag = 0;
        now = TOT;
        tot = 1;
        return;
      } else {
        now = END;
        out(0);
        return;
      }
    } else if (now == B_) {
      if (ch == 'B') {
        now = B_;
        return;
      } else if (ch == 'T') {
        now = BT;
        return;
      } else {
        now = END;
        out(0);
        return;
      }
    } else if (now == BT) {
      if (ch == 'B') {
        out(1);
        now = B_;
        return;
      } else if (ch == 'T') {
        now = BTT;
        return;
      } else {
        now = END;
        out(1);
        return;
      }

    } else if (now == BTT) {
      if (ch == 'B') {
        now = BTTB;
        return;
      } else if (ch == 'T') {
        tot = 3;
        flag = 0;
        now = TOT;
        return;
      } else {
        now = END;
        out(2);
        return;
      }
    } else if (now == BTTB) {
      if (ch == 'B') {
        now = B_;
        out(2);
        return;
      } else if (ch == 'T') {
        now = BTTBT;
        return;
      } else {
        now = END;
        out(2);
        return;
      }
    } else if (now == BTTBT) {
      if (ch == 'B') {
        now = BTTB;
        return;
      } else if (ch == 'T') {
        flag = 1;
        tot = 3;
        now = TOT;
        return;
      } else {
        out(2);
        now = END;
        return;
      }
    } else if (now == TOT) {
      if (ch == 'B') {
        now = TB;
        return;
      } else if (ch == 'T') {
        now = TOT;
        tot++;
        return;
      } else {
        out(tot);
        now = END;
        return;
      }
    } else if (now == TB) {
      if (ch == 'B') {
        out(tot);
        now = B_;
        return;
      } else if (ch == 'T') {
        now = TBT;
        return;
      } else {
        out(tot);
        now = END;
        return;
      }
    } else if (now == TBT) {
      if (ch == 'B') {
        now = TB;
        return;
      } else if (ch == 'T') {
        now = TBTT;
        return;
      } else {
        out(tot);
        return;
      }
    } else if (now == TBTT) {
      if (ch == 'B') {
        out(tot + 1);
        tot = 0;
        now = BTTB;
        return;
      } else if (ch == 'T') {
        out(max(tot, 2));
        if (tot == 3 && flag == 1) {
          flag = 1;
          tot = 4;
        } else {
          flag = 0;
          tot = 3;
        }
        now = TOT;
        return;
      } else {
        out(max(tot, 2));
        tot = 0;
        now = END;
        return;
      }
    } else {
    }
  }
};

int read() {
  int x = 0, f = 1;
  int c = getchar();
  while (c > '9' || c < '0') {
    if (c == '-') {
      f = -1;
    }
    c = getchar();
  }
  while (c >= '0' && c <= '9') {
    x = x * 10 + c - '0';
    c = getchar();
  }
  return x * f;
}

signed main() {
  int _ = read();

  while (_--) {
    int n = read();
    char *chlist = new char[n + 1];
    for (int i = 0; i < n; i++) {
      scanf("%c", &(chlist[i]));
    }

    // 向字符串的结尾添加结束状态机的标识符
    chlist[n] = '\n';
    
    // 新建一个状态机
    solve *S = new solve;

    for (int i = 0; i <= n; i++) {
	  // 遍历整个字符串并转移状态机的状态。
	  // 当然，也可以一边读入一边遍历，这样会节省一些空间。
      S->fun(chlist[i]);
    }
    cout << S->Max << endl;
  }
  return 0;
}
```
算法复杂度：$O(n)$。

---

## 作者：Petit_Souris (赞：2)

出题人是大笨蛋，现在突然发现官方题解不在题解区。

- Subtask 0：$n \leq 7$。
		
可以手动模拟所有情况，或者爆搜。
		
- Subtask 1：$T \leq 10$，$n \leq 10$。
		
复杂度较好的爆搜。
		
- Subtask 3：保证给定的字符串无法进行任何操作。
	
输出最长 $\texttt{T}$ 连续段。

- Subtask 2：$\sum n \leq 5000$。
		
如果进行了操作，我们考虑选择一个极长 $\texttt{T}$ 连续段，并尝试扩展它。
		
观察到一段 $\texttt{T}$ 左右分别最多扩展 $1$ 的长度，因为不可能通过操作得到两个 $\texttt{T}$ 和原来的 $\texttt{T}$ 连着。
		
如何判断能否扩展一个 $\texttt{T}$？假设要在左边扩展一个 $1$，那么必定是从左边一个 $\texttt{BTTB}$ 开始操作，不断往后。那么可行的串一定长成一个 $\texttt{BT}$ 再加上若干个 $\texttt{TB}$ 拼起来（形如 $\texttt{BTTBTBTBTBTTT...}$）。右边同理。
		
暴力模拟这个过程，复杂度 $\mathcal O(n^2)$。

- 正解:
	
优化上面这个过程。
	
- 正解 1：前缀和 + 二分。
	
预处理出不同奇偶位置是否为 $\texttt{TB}$ 和 $\texttt{BT}$ 的前缀和。
	
对于每个 $\texttt{T}$ 连续段，二分出左边第一个 $\texttt{BT}$，判断从这个 $\texttt{BT}$ 到这个 $\texttt{T}$ 连续段是否全是 $\texttt{TB}$，右边同理。
	
时间复杂度 $\mathcal O(n\log n)$。
	
- 正解 2：用指针预处理每个位置是否能扩展。
	
枚举一个子串 $\texttt{BTTB}$，向左右不断扩展 $\texttt{TB}$ 和 $\texttt{BT}$，并将经过的位置标记为可以被左边/右边扩展。
	
统计答案时，枚举极长 $\texttt{T}$ 连续段，判断左右两个位置是否可以扩展。
	
时间复杂度 $\mathcal O(n)$。 

- 正解 3：状压 dp，记录前三个字符。

时间复杂度 $\mathcal O(n)$。

- 彩蛋：参与讨论本题的团队成员想出的各种错解。
	
错解 1：对于 Subtask 2 的做法，只考虑 $\texttt{T}$ 的最长连续段，并将其扩展。
	
hack：一个长度为 $x$ 的 $\texttt{T}$ 连续段不能扩展，但是一个长度为 $x-1$ 的 $\texttt{T}$ 连续段两端都能扩展的情况。
	
错解 2：对于正解 2，记录是否能被扩展时，用 $-1$ 和 $1$ 标记。
	
不同的标记会被覆盖掉（两个同时有的情况会出错）。
	
hack：$\texttt{BTTBTTBTTB}$，正确答案 4，错误输出 3。（原本 std 的出错处）
	
std 的解决方案是：用 $00,01,10,11$ 四个二进制数表示，每次用二进制或来更新状态。
	
感谢数据负责人 irris 卡掉了这些错误情况。

哎，有几个平方做法最后没卡满过了。感觉大家都是乱搞大师。

正解 1（by wsc）：

```cpp
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
#define pii pair<ll,ll>
#define rep(i,a,b) for(ll i=(a);i<=(b);++i)
#define per(i,a,b) for(ll i=(a);i>=(b);--i)
using namespace std;
ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
void write(ll x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
const ll N=1e6+5;
ll T,n,sum1[2][N],sum2[2][N];
char ch[N];
ll chk1(ll x){
	if(x>=n)return 0;
	return ch[x]=='B'&&ch[x+1]=='T';
}
ll chk2(ll x){
	if(x>=n)return 0;
	return ch[x]=='T'&&ch[x+1]=='B';
}
ll calc1(ll id,ll l,ll r){
	if(l>r)return 0;
	return sum1[id][r]-sum1[id][max(0ll,l-2)];
}
ll calc2(ll id,ll l,ll r){
	if(l>r)return 0;
	return sum2[id][r]-sum2[id][max(0ll,l-2)];
}
ll getmid(ll l,ll r){
	ll mid=(l+r)>>1;
	if(mid%2!=l%2){
		if(l==mid)mid++;
		else mid--;
	}
	return mid;
}
void solve(){
	n=read();
	scanf("%s",ch+1);
	rep(i,0,1){
		rep(j,0,n+1)sum1[i][j]=sum2[i][j]=0;
	}
	sum1[1][1]=chk1(1);
	sum1[0][2]=chk1(2);
	sum2[1][1]=chk2(1);
	sum2[0][2]=chk2(2);
	rep(i,3,n-1){
		sum1[1][i]=sum1[1][i-2]+chk1(i);
		sum2[1][i]=sum2[1][i-2]+chk2(i);
		i++;
	}
	rep(i,4,n-1){
		sum1[0][i]=sum1[0][i-2]+chk1(i);
		sum2[0][i]=sum2[0][i-2]+chk2(i);
		i++;
	}
	ll ans=0;
	rep(i,1,n){
		if(ch[i]=='B')continue;
		ll j=i;
		while(j<n&&ch[j+1]=='T')j++;
		ll len=j-i+1;
		ll l=(i%2==1?1:2),r=i-2,pos=-1;
		while(l<=r){
			ll mid=getmid(l,r);
			if(calc1(i%2,mid,i-2)>0)pos=mid,l=mid+2;
			else r=mid-2;
		}
		if(pos!=-1){
			if(calc2(i%2,pos+2,i-2)==(i-1-pos)/2)len++;
		}
		l=j+1,r=((n-j)%2==0?n-1:n-2),pos=-1;
		while(l<=r){
			ll mid=getmid(l,r);
			ll tmp=calc2(1-j%2,j+1,mid);
			if(tmp>0)pos=mid,r=mid-2;
			else l=mid+2;
		}
		if(pos!=-1){
			if(calc1(1-j%2,j+1,pos-2)==(pos-j-1)/2)len++;
		}
		ans=max(ans,len);
		i=j;
	}
	write(ans),putchar('\n');
}
int main(){
	T=read();
	while(T--)solve();
	return 0;
}
```

正解 2（by irris）：

```cpp
#include <bits/stdc++.h>

#define MAXN 500005
int u[MAXN];
int sumN = 0;
void solve() {
	int N; std::string S; std::cin >> N >> S;
	int ans = 0, n = S.size();
	for (int i = 0; i <= n; ++i) u[i] = 0;
	for (int i = 0, p, q; i + 3 < n; ++i) if (S[i] == 'B' && S[i + 1] == 'T' && S[i + 2] == 'T' && S[i + 3] == 'B') {
		u[i] |= 2, u[i + 3] |= 1, p = i, q = i + 3;
		while (p - 1 > 0 && S[p - 2] == 'B' && S[p - 1] == 'T') u[p -= 2] |= 2;
		while (q + 2 < n && S[q + 1] == 'T' && S[q + 2] == 'B') u[q += 2] |= 1;
	}
	for (int i = 0, j; i < n; ++i) if (S[i] == 'T') {
		j = i; while (j + 1 < n && S[j + 1] == 'T') ++j;
		ans = std::max(ans, (int)(i > 0 && (u[i - 1] & 1) > 0) + j - i + 1 + (int)((u[j + 1] & 2) > 0)), i = j;
	}
	std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
    int T; std::cin >> T;
    while (T--) solve();
    return 0;
}
```

---

## 作者：Defy_HeavenS (赞：2)

## 题意
你可以把字符串 `BTTB` 修改为 `TBBT`，求最长 `T` 连续段的长度。

## 思路
我们可以发现，对于一串连续的 `T` 通过修改最多只能将长度增加 $2$。

比如 `BTTBTTTTTBTTB` 这个字符串，对于中间 `T` 的连续段想让它长度增加，最多变成 `TBBTTTTTTTBBT`，长度增加 $2$。由于修改后 `T` 连续段旁边都变成了 `BB`，而 `BB` 不会再修改，也不会给 `T` 的连续段做贡献了。

但是要注意！对于 `BTTBTBTBTBTTTTTTTBTBTBTBTTB` 这种情况， `T` 的连续段和 `BTTB` 中间隔了好多 `BT` 或 `TB`（左为 `TB` ，右为 `BT`），也是可以的。

### 于是就有了一个被数据卡的想法

对于每个 `T` 的连续段，如果左边有 $0$ 或多个 `TB` 然后出现一个 `BT` 就说明左端可以增加一个 `T`。

相反，如果右边有 $0$ 或多个 `BT` 然后出现一个 `TB` 就说明右端可以增加一个 `T`，最后 $\max$ 一下更新答案。

可是遇到 `BTBTBTBTBTBT...BTBT` 这种情况时间复杂度就从 $\mathcal{O}(n)$ 变成了近似 $\mathcal{O}(n^2)$ 的 $\mathcal{O}(n\times\frac{n}{2})$。

### 那么怎么优化呢？

预处理！

从前往后枚举，当遇到 `BT`，那么接下来遇到的 `TB` 就都会变成 `BT` 给答案加一。

相反，从后往前枚举，当遇到 `TB`，那么接下来遇到的 `BT` 就都会变成 `TB` 给答案加一。

用两个不同的数组存储，当遇到 `T` 的连续段时，只需要判断一下这两个数组在相应位置有没有被标记，最后 $\max$ 一下更新答案即可。

## 代码
### TLE 50分代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,ma,l,r,ans;
bool v[100005];
char s[100005];
int main(){
	scanf("%d",T);
	while(T--){
		scanf("%d%s",n,s);
		memset(v,0,sizeof v);
		ma=0;
		for(int i=0;i<n;i++){
			if(s[i]=='T'&&!v[i]){
				l=i,r=l,ans;
				for(int j=i+1;j<n;j++){
					if(s[j]!='T'){
						break;
					}else{
						r++;
						v[j]=1;
					}
				} 
				ans=r-l+1;
				for(int j=l-1;j>=0;j-=2){
					if(s[j]!='B'||s[j-1]!='T'){
						if(s[j]=='T'&&s[j-1]=='B'){
							ans++;
						}
						break;
					}
				}
				for(int j=r+1;j<n;j+=2){
					if(s[j]!='B'||s[j+1]!='T'){
						if(s[j]=='T'&&s[j+1]=='B'){
							ans++;
						}
						break;
					}
				}
				ma=max(ans,ma);
			}
		}
		printf("%d\n",ma);
	}
    return 0;
}

```

### AC 100代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,ma,sum,l,k;
bool TB[100005],BT[100005];
char s[100005];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%s",&n,s);
		l=-1;
		ma=sum=0;
        for(int i=0;i<n;++i){
            if(s[i+1]=='T'&&s[i]=='B'){
			    k=i+2;
                while(s[k]=='T'&&s[k+1]=='B'&&k<n-1){
					i=k;
                	TB[k+1]=1;
					k+=2;
				}
            }
        }
        for(int i=n-1;i>=0;--i){
            if(s[i-1]=='T'&&s[i]=='B'){
			    k=i-2;
                while(s[k]=='T'&&s[k-1]=='B'&&k>0){
					i=k;
                	BT[k-1]=1;
					k-=2;
				}
            }
        }
        for(int i=0;i<n;++i){
            if(s[i]=='T'){
                ++sum;
                if(l==-1){
                	l=i;
				}
            }else{
                ma=max(sum+TB[l-1]+BT[i],ma);
                sum=0;
				l=-1; 
            }
        }
		printf("%d\n",max(TB[l-1]+BT[n-1]+sum,ma));
        memset(TB,0,sizeof(TB));
		memset(BT,0,sizeof(BT));
    }
    return 0;
}
```

## 修改

2023/8/26 错别字 吧 修改成 把

---

## 作者：QianRan_GG (赞：2)

# 考场没思路？暴力出奇迹！

没错，我赛时就是用 $\mathcal O(n^2)$ 的暴力卡时通过了本题！

[AC记录](https://www.luogu.com.cn/record/121924224)，最高 $998 ms$。

## 解题思路

首先对于一个字符串 $s$，我们用 $b$ 数组记录 $\texttt{B}$ 在 $s$ 中每次出现的位置，则每段 $\texttt{T}$ 的数量可以用 $b_{i + 1} - b_i$ 表示。

所以，我们可以用 $b$ 数组表示整个 $s$。 

但是会出现这种情况：$\texttt{TTTBBTTBT}$。像这种两边是 $\texttt{T}$ 的字符串，我们会漏数两边的 $\texttt{T}$。  
怎么办呢？**在字符串两边各插入一个 $\texttt{B}$！**  

当然，既然我们用 $b$ 数组能表示整个 $s$，那么我们只用在 $b$ 中*插入*，即在 $b$ 的最左边加一个 $-1$，在最右边加一个 $n$（$s$ 下标为 $0 \sim n - 1$）这样就不用动原字符串啦。  

这样，我们的 $b$ 数组就构造好啦！

然后我们遍历整个 $b$，找出所有的 $\texttt{T}$，对于一整段 $\texttt{T}$，我们在它的左右两边找能不能进行操作使更多的 $\texttt{T}$ 进入当前这段。  

因为我们只能将 $\texttt{BTTB}$ 变成 $\texttt{TBBT}$，在变完后两个 $\texttt{B}$ 会把两个 $\texttt{T}$ 隔开，所以对于每一边，$\texttt{T}$ 的个数最多加 $1$，所以对于每一段 $\texttt{T}$，进行操作最多能使 $\texttt{T}$ 的个数加 $2$。  

所以我们要在左右两边找 $\texttt{BTTB}$ 类型的子串，找到一处就可以返回了。 

怎么找呢？ 我们发现对于一下字符串：$\texttt{BTTBTB}$，其中有 $\texttt{BTTB}$，当我们进行操作后会变成 $\texttt{TBBTTB}$ 这时又会出现一个 $\texttt{BTTB}$，所以若在 $\texttt{BTTB}$ 右边有 $\texttt{TB}$（左边是 $\texttt{BT}$），就能使其中一个 $\texttt{T}$ 往两边转移。  

所以对于一段 $\texttt{T}$ 串，我们看其左边是不是 $\texttt{TB}$，右边是不是 $\texttt{BT}$，若是，则可以继续往两边转移，直到不是，此时我们再判断当前遍历到的是不是 $\texttt{BTTB}$，若是，则可以使我们的 $\texttt{T}$ 的数量加 $1$。 

然后。。。就做完了！

## 代码

```cpp
#include <iostream>

using namespace std;

const int N = 1e5 + 5;

int lb, maxm;
int b[N];

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);  //关闭同步。
	int T; cin >> T;
	while(T -- )
	{
		maxm = lb = 0;
		int n;
		string s;
		cin >> n >> s;
		b[ ++ lb] = -1;
		for(int i = 0; i < n; ++ i)
			if(s[i] == 'B') b[ ++ lb] = i;
		b[ ++ lb] = n;          //记录 B 出现的位置。
		for(int i = 1; i < lb; ++ i)
		{
			int j = i + 1;
			int t = b[j] - b[i] - 1;  //算出 T 的数量。
			if(t + 2 <= maxm) continue;  //优化，若当前串 + 2 都比当前最大值小直接跳过。
			if(i - 1 > 1)
			{
				int ld = i;
				while(ld > 2 && b[ld] - b[ld - 1] == 2) ld -- ;
				if(ld > 2 && b[ld] - b[ld - 1] == 3) t ++ ;
			} //往左遍历。
			if(j + 1 < lb)
			{
				int rd = j;
				while(rd < lb - 1 && b[rd + 1] - b[rd] == 2) rd ++ ;
				if(rd < lb - 1 && b[rd + 1] - b[rd] == 3) t ++ ;
			} //往右遍历。
			maxm = max(maxm, t);
		}
		cout << maxm << '\n';
	}
}
```

---

## 作者：hank_wenstion (赞：1)

## 题意
给你一个有一个由 B 和 T 组成的字符串
你可以将 BTTB 修改为 TBBT 来改变这个字符串
一个字符串的权值为最长的 T
连续段长度。你需要使得字符串的权值尽可能大并输出最大权值。

## 思路
通过观察不难发现，无论是那种串，只要数量大于等于三，就无法被改变，因此衍生出的结论就是字符串权值最大只能加上二，即在连续 T 串左右各加一个字符 T 来增加权值。

因此，我们可以得出解法，造一个串是不现实的，需要我们在原有的基础上看看能否将其他的串通过操作左右转移过来，并在输出时加上权值。

一定要注意，贴边的 T
不能往中间传，别问我怎么知道的。

## 代码
```cpp
#include<iostream>
using namespace std;
const int N=5e5+10;
int T,n;
int a[N],b[N],cod[N];
int p,d;
string s;
int main(){
	cin>>T;
	int ans=1;
	for(int i=1;i<=T;i++){
		cin>>n>>s;
		for(int j=1;j<=p+10;j++){
            a[j]=0;
			b[j]=0;
			cod[j]=0;
        }
        p=0;
        d=0;
		if(n==1 && s[0]=='T'){
			cout<<1<<endl;
            continue;
		}
		for(int k=1;k<n;k++){
			if(s[k]=='T' || s[k-1]=='T') d=1;
			if(s[k]=='T' && s[k-1]=='T'){
				if(k==1 || s[k-2]!='T'){
					p++;
                    cod[p]=2;
					if(k==1) a[1]=1;
				}
				else cod[p]++;
				if(k==n-1) b[p]=1;
			}
			if(s[k]=='B' && s[k-1]=='B') {
                b[p+1]=1;a[p]=1;
            }
		}
		if(p==0){
			cout<<d<<endl;
            continue;
		}
		ans=cod[1];
		for(int x=1;x<=p;x++){
			int q=cod[x];
			if(cod[x-1]==2 && !a[x-1]) q++;
			if(cod[x+1]==2 && !b[x+1]) q++;
			ans=max(ans,q);
		}
		cout<<ans<<endl;
	}
	return 0;
 } 
```







---

## 作者：Register_int (赞：1)

由于一次变换最多只能为答案提供 $1$ 的贡献，我们可以找出原串内所有极长连续 $\verb!T!$ 子串，并判断两端是否能变成 $\verb!T!$。

考虑 $dp_i$ 表示只操作 $i$ 之前的位置，能不能在 $i-3\sim i$ 进行一次变换。显然有转移式：

$$dp_i=[dp_{i-2}\lor(s_{i-3}=\verb!B!\land s_{i-2}=\verb!T!)][s_{i-1}=\verb!T!][s_i=\verb!B!]$$

因为在 $i-2$ 处变换也能补全 $\verb!BTTB!$ 的前缀。后缀部分同理。极长连续串用双指针查找即可。

# AC 代码

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

int t, n, ans; char s[MAXN];

bool f[MAXN], g[MAXN];

int main() {
	for (scanf("%d", &t); t--;) {
		scanf("%d%s", &n, s + 1), ans = 0;
		for (int i = 0; i <= n; i++) f[i] = 0;
		for (int i = 4; i <= n; i++) {
			f[i] |= (f[i - 2] || s[i - 3] == 'B' && s[i - 2] == 'T') && s[i - 1] == 'T' && s[i] == 'B';
		}
		for (int i = 1; i <= n + 1; i++) g[i] = 0;
		for (int i = n - 3; i > 0; i--) {
			g[i] |= s[i] == 'B' && s[i + 1] == 'T' && (s[i + 2] == 'T' && s[i + 3] == 'B' || g[i + 2]);
		}
		for (int i = 1, j; i <= n; i++) {
			if (s[i] != 'T') continue;
			for (j = i + 1; j <= n && s[j] == 'T'; j++);
			ans = max(ans, j - i + f[i - 1] + g[j]), i = j;
		}
		printf("%d\n", ans);
	}
}
```

---

## 作者：_3Zinc_ (赞：1)

前言：比赛前去做牙齿矫正，回来晚了 10 分钟……做比赛的运气全用在了一路绿灯上了（无语）。第二题切了两个半小时。决定写篇题解来抒发一下再记得~~愤怒~~愉悦之情。

AC 的想法很简单，就是表示出每一串连续的 $\texttt{T}$，其长度分别为 $l_1 \sim l_m$。明显的，对于任何一个 $l_i$，在一系列操作后，它的长度顶多加 $2$，也就是左边多一个，右边多一个。明显的贪心，将 $\texttt{T}$ 子串按长度从大到小排，然后只要枚举到 $l_i < ans-1$，就可以结束了。因为它既是加两个，也只能等于 $ans$。然后每次更新 $ans$。

对于判断左右是否能增加一个，不是只判断有没有 $\texttt{BTTB}$ 那么简单。拿左边来说，他可能长这样：

$$\texttt{(BTTBTBTBTB)TTTTTTT}$$

他可以一路猛操作变成：

$$\texttt{(TBBTBTBTBT)TTTTTTT}$$

我吗，蠢蠢地使用了暴力，然后喜提 $2\mathcal{WA}+4\mathcal{TLE}$。加个记忆化，喜提 $2\mathcal{WA}$。

两次的翻车记录在这里：[4TLE+2WA](https://www.luogu.com.cn/record/121942410)，[2WA](https://www.luogu.com.cn/record/121944357)。

为什么呢？因为这个样例：$1 \texttt{B}$，要特判一下。（大概也只有我会漏掉这个样例的情况吧，悲。）

$\mathcal{AC} \texttt{CODE}$：

```cpp
#include <bits/stdc++.h>
using namespace std;

int T,n,cnt;
struct Node {
	int l,r,mm;
	Node(int L=0,int R=0,int m=0) {
		l=L,r=R,mm=m;
		return ;
	}
	friend bool operator <(const Node a,const Node b) {
		return a.mm>b.mm;
	}
};
const int MS=100005;
Node node[MS];
char s[MS];
int pr[MS][2];
bool GO(int p,int drct) {
	if(p<1||p>n-1) return 0;
	if(pr[p][drct-1]!=-1) return pr[p][drct-1];
	if(drct&1) {
		if(p>2&&s[p]=='B'&&s[p-1]=='T'&&s[p-2]=='T'&&s[p-3]=='B') return pr[p][drct-1]=true;
		if(s[p]=='B'&&s[p-1]=='T') return pr[p][drct-1]=GO(p-2,drct);
	}
	else {
		if(p<n-3&&s[p]=='B'&&s[p+1]=='T'&&s[p+2]=='T'&&s[p+3]=='B') return pr[p][drct-1]=true;
		if(s[p]=='B'&&s[p+1]=='T') return pr[p][drct-1]=GO(p+2,drct);
	}
	return pr[p][drct-1]=false;
}

int main() {
	scanf("%d",&T);
	while(T--) {
		memset(pr,-1,sizeof(pr));
		scanf("%d%s",&n,s);
		int l=-1;
		cnt=0;
		for(int i=0;i<n;i++) {
			if(s[i]=='B'&&l>=0) node[++cnt]=Node(l,i-1,i-l),l=-1;
			if(s[i]=='T'&&l<0) l=i;
		}
		if(l>=0) node[++cnt]=Node(l,n-1,n-l);
		if(cnt==0) {
			printf("0\n");
			continue;
		}
		sort(node+1,node+1+cnt);
		int ans=node[1].mm;
		for(int i=1;i<=cnt&&node[i].mm>=ans-1;i++) {
			if(GO(node[i].l-1,1)) node[i].mm++;
			if(GO(node[i].r+1,2)) node[i].mm++;
			ans=max(ans,node[i].mm);
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

为什么辣么简单的暴力题要切两个半小时呢？因为我一直往 DP 和暴搜上考虑，浪费了两个小时。警钟长鸣。

---

## 作者：xixihaha2021 (赞：0)

# [「TAOI-2」Break Through the Barrier 题解](https://www.luogu.com.cn/problem/P9574)
## 题意简述
给定一个 `01` 串，每次操作可以将形如 `0110` 的子串改为 `1001`，求进行任意次操作后最长的全为 `1` 的子串长度的最大值。

以下思路均采用此题意简述的模式。具体地，题中的 `T` 为此题解中的 `1`；题中的 `B` 为此题解中的 `0`。由此将输入的字符串改为 `01` 串。
## 思路简述
定义全为 `1` 的子串为合法子串。注意到每个初始的合法子串经过若干次操作至多只能使长度增加 `2`，即左右两边分别增加一个 `1`。因此考虑针对每个初始的合法子串依次判断其可能增加的长度，再取总长度的最大值。考虑什么样的以 `0` 结尾的子串可以将最后一位变成 `1`。发现此类子串形如 `0110` 的后面补充任意个 `10`。同理形如 `0110` 的前面补充任意个 `01` 的子串可以将首位变成 `1`。我们定义前者为 `10` 型子串，后者为 `01` 型子串。现在针对每一个初始的合法子串，判断其前面如果是 `10` 型子串，那么合法子串左侧可以补充一个 `1`；如果是 `01` 型子串，那么合法子串右侧可以补充一个 `1`。

为此，考虑预处理出每个 `10` 型子串和 `01` 型子串的右端点和左端点。即记录两个表，称为 `10` 表和 `01` 表。记录每个位置是否为某个 `10` 型子串的右端点和是否为某个 `01` 型子串的左端点。具体做法为，先正着扫一遍，如果遇到 `0110`，那么就在后面所接的最后一个 `10` 的 `0` 处标记为 $1$ 并从这里继续扫。然后反着扫一遍，如果遇到 `0110`，那么就在前面所接的最后一个 `01` 的 `0` 处标 `1` 并继续扫。下面枚举每个合法子串 $[l,r]$，若 `10` 表显示第 $l-1$ 位为某个 `10` 型子串的右端点，那么合法子串的长度增加 $1$；若 `01` 表显示第 $r+1$ 位为某个 `01` 型子串的左端点，那么合法子串的长度增加 $1$。最后以最终长度动态更新答案即可。

另外，对于字符串、`10` 表和 `01` 表，都可以使用 bitset 维护。

---

以下是本题的第二种方法。

~~source：校内训练中搬运此题，以下做法来自一位学长，笔者本人。~~

考虑记 $f_i$ 表示 $2$ 个 `0` 之间 `1` 的个数。例如：将 `11010110101110110` 记为 $\{2,1,2,1,3,2,0\}$。

接着观察操作的本质，与上文从传递的结果考虑不同，本方法中从传递的源头考虑。执行依次操作其实就是将 $2$ 个 `1` 拆开。具体在 $f_i$ 数组中就是将一个形如 $\{x,2,y\}$ 的子串改为 $\{x+1,0,y+1\}$，此时如果需要继续向左传递，那么必须有 $x+1=2$，即 $x=1$。同理若要继续向右传递则必有 $y=1$。

因此考虑对于每个 $f_i=2(i \in [2,tot-1])$，其中 $tot$ 为序列 $f$ 的长度，分别向左、向右枚举，计算其可以传递到的位置。具体地，形如 $\{2,1,1,...\}$ 或 $\{1,1,...,2\}$ 的子串可以传递。记 $g_i$ 表示某点得到的传递贡献，每次传递结束后（即遇到首个$f_i$ 满足 $f_i \not = 1$）将其传递的终点所对应的 $g_i$ 增加 $1$ 即可。

答案即 $\max_{i=1}^n f_i+g_i$。

---

易发现上述两种方法本质相同，只是枚举的角度不同。但是后者更为常见。
## 复杂度分析
### 时间复杂度分析
对于每组数据，无论是预处理还是更新答案，其时间复杂度都是线性的。因此总时间复杂度为 $O(\sum N)$。

---

对于每组数据，不难证明其最劣时间复杂度为 $O(N)$。因此总时间复杂度为 $O(\sum N)$。
### 空间复杂度分析
空间复杂度仅与 bitset 的大小相关，即空间复杂度为 $O(\dfrac{N}{\omega})$。

---

显然，序列 $f,g$ 的空间复杂度均为 $O(N)$，也即总空间复杂度。
### 数据范围
$1 \le n \le 10^5,1 \le \sum n \le 5 \times 10^5$。

对于时间复杂度，$\sum N \le 5 \times 10^5 \le 4 \times 10^8$，故不会超时。

对于空间复杂度，设 $\omega$ 为 $64$，$\dfrac{N}{\omega} \le \dfrac{10^5}{64}=1562.5 \le 3 \times 10^7$，故不会超空间。

---

对于时间复杂度，$\sum N \le 5 \times 10^5 \le 4 \times 10^8$，故不会超时。

对于空间复杂度，$N \le 10^5 \le 3 \times 10^7$，故不会超空间。
## 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,ans,tmp;
bitset<100005> a,vis1,vis2;
char ch;
ll read(){
	ll x = 0;
	bool f = true;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-')f = !f;
		ch = getchar();
	}
	while(isdigit(ch))x = x * 10 + ch - '0',ch = getchar();
	return x * f * 2 - x;
}
ll write(ll x,string ch){
	ll f = 1,L = ch.size(),tmp = x;
	if(tmp < 0){
		putchar('-');
		tmp *= -1;
	}
	while(f <= tmp)f *= 10;
	if(tmp)f /= 10;
	while(f){
		putchar(tmp / f + '0');
		tmp -= (tmp / f * f),f /= 10;
	}
	for(ll i = 0;i <= L - 1;i++)putchar(ch[i]);
	return x;
}
int main(){
	t = read();
	for(ll i = 1;i <= t;i++){
		n = read(),ans = 0;
		a.reset(),vis1.reset(),vis2.reset();
		for(ll j = 1;j <= n;j++){
			if(j == 1)scanf(" %c",&ch);
			else ch = getchar();
			a[j] = (ch == 'T');
		}
		for(ll j = 1;j <= n - 3;j++){
			if(!(a[j] == 0 && a[j + 1] == 1 && a[j + 2] == 1 && a[j + 3] == 0))continue;
			for(ll k = j + 3;k <= n && a[k - 1] == 1 && a[k] == 0;k += 2)vis1[k] = 1,j = k - 1;
		}
		for(ll j = n;j >= 4;j--){
			if(!(a[j] == 0 && a[j - 1] == 1 && a[j - 2] == 1 && a[j - 3] == 0))continue;
			for(ll k = j - 3;k && a[k + 1] == 1 && a[k] == 0;k -= 2)vis2[k] = 1,j = k + 1;
		}
		for(ll j = 1;j <= n;j++){
			if(a[j] == 0)continue;
			for(ll k = j + 1;k <= n + 1;k++){
				if(a[k] == 0){
					tmp = k;
					if(j >= 2 && vis1[j - 1] == 1)j--;
					if(k <= n && vis2[k] == 1)k++;
					if(k - j > ans)ans = k - j;
					j = tmp;
					break;
				}
			}
		}
		write(ans,"\n");
	}
	return 0;
}
```

---

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll t,n,ans,cnt,a[100005],p[100005];
char ch;
ll read(){
	ll x = 0;
	bool f = true;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-')f = !f;
		ch = getchar();
	}
	while(isdigit(ch))x = x * 10 + ch - '0',ch = getchar();
	return x * f * 2 - x;
}
ll write(ll x,string ch){
	ll f = 1,L = ch.size(),tmp = x;
	if(tmp < 0){
		putchar('-');
		tmp *= -1;
	}
	while(f <= tmp)f *= 10;
	if(tmp)f /= 10;
	while(f){
		putchar(tmp / f + '0');
		tmp -= (tmp / f * f),f /= 10;
	}
	for(ll i = 0;i <= L - 1;i++)putchar(ch[i]);
	return x;
}
int main(){
	t = read();
	for(ll i = 1;i <= t;i++){
		memset(p,0,sizeof(p));
		n = read(),cnt = 1,ans = a[1] = 0;
		for(ll j = 1;j <= n;j++){
			if(j == 1)scanf(" %c",&ch);
			else ch = getchar();
			if(ch == 'T')a[cnt]++;
			else a[++cnt] = 0;
		}
		for(ll j = 1;j <= cnt;j++)if(a[j] > ans)ans = a[j];
		for(ll j = 2;j <= cnt - 1;j++){
			if(a[j] == 2){
				for(ll k = 1;j + k <= n && a[j + k] == 1;k++)if(a[j + k + 1] != 1 && j + k <= n - 1)p[j + k + 1]++;
				for(ll k = 1;j - k >= 1 && a[j - k] == 1;k++)if(a[j - k - 1] != 1 && j - k >= 2)p[j - k - 1]++;
				if(a[j + 1] != 1 && j <= n - 1)p[j + 1]++;
				if(a[j - 1] != 1 && j >= 2)p[j - 1]++;
			}
		}
		for(ll j = 1;j <= cnt;j++)if(a[j] + p[j] > ans)ans = a[j] + p[j];
		write(ans,"\n");
	}
	return 0;
}
```

---

## 作者：mc123456 (赞：0)

## 分析

考虑答案里的最长 $\tt T$ 连续段是有什么变来的，只可能是由一段初始时连续的 $\tt T$ 拓展而来的或是无中生有而来的。

考虑一次操作的本质是什么。可以发现一次操作会把 $\tt BTTB$ 变成 $\tt TBBT$，也就是把 $\tt T$ 从中间转移到了两边，并把操作前本来连续的 $\tt T$ 断开了。那么想让一个初始时连续的 $\tt T$ 串变长，只能将其两侧的 $\tt T$ 通过不断操作转移到其旁边；而想无中生有一个连续的 $\tt T$ 串，其长度至多只会为 $2$，不优于不操作，所以忽略无中生有的部分。

那么我们就可以设计两个 $dp$ 状态，$f_i = 0/1$ 表示以 $i$ 结尾的字符串能否在 $i$ 处从 $\tt B$ 变为 $\tt T$，$g_i = 0/1$ 表示以 $i$ 开头的字符串能否在 $i$ 处从 $\tt B$ 变为 $\tt T$。设原字符串为 $s$，那么我们可以得到转移方程：

$$
\begin{aligned}
f_i &= ([s_{i - 1} = \texttt{T}] \wedge [s_i = \texttt{T}]) \wedge (f_{i - 2} \vee ([s_{i - 3} = \texttt{B}] \wedge [s_{i - 2} = \texttt{T}])) \quad (4 \leq i \leq n) \\
g_i &= ([s_{i + 1} = \texttt{T}] \wedge [s_i = \texttt{T}]) \wedge (g_{i + 2} \vee ([s_{i + 3} = \texttt{B}] \wedge [s_{i + 2} = \texttt{T}])) \quad (1 \leq i \leq n - 3)
\end{aligned}
$$

设 $s$ 中 $\tt B$ 将 $\tt T$ 划分为了 $m$ 段，每一段的端点分别为 $l_p, r_p$，那么答案即为：

$$
\max\limits_{p = 1}^{m}\{r_p - l_p + 1 + f_{l_p - 1} + g_{r_p + 1}\}
$$

时间复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define int long long
const int N = 1e5 + 10;

int n;
string s;
bool bt[N], tb[N];

void solve()
{
    cin >> n >> s;
    s = ' ' + s + ' ';
    for (int i = 0; i <= n + 1; i++)
        bt[i] = tb[i] = 0;
    for (int i = 4; i <= n; i++)
        bt[i] = (s[i - 1] == 'T' && s[i] == 'B') && (bt[i - 2] || (s[i - 3] == 'B' && s[i - 2] == 'T'));
    for (int i = n - 3; i >= 1; i--)
        tb[i] = (s[i + 1] == 'T' && s[i] == 'B') && (tb[i + 2] || (s[i + 3] == 'B' && s[i + 2] == 'T'));
    int ans = 0;
    for (int i = 1, l = 1, r = 0, flg = 0; i <= n + 1; i++)
        if (s[i] == 'T')
            r = i, flg = 1;
        else
        {
            if (flg)
                ans = max(ans, r - l + 1 + bt[l - 1] + tb[r + 1]);
            l = i + 1, flg = 0;
        }
    cout << ans << endl;
}

signed main()
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--)
        solve();
}
```

---

## 作者：int_R (赞：0)

[P9574 「TAOI-2」Break Through the Barrier](https://www.luogu.com.cn/problem/P9574)

做法多少麻烦了点。

手模一下发现，如果你进行了变化，你变化的位置上最多只会有一个连续的 $\text{T}$。

所以我们可以选出一个 $\text{T}$ 的连续段 $S[l,r]$，判断操作 $S[1,l-1]$ 能否使得 $S_{l-1}=\text{T}$，操作 $S[r+1,n]$ 能否使得 $S_{r+1}=\text{T}$，每有一边可以就将这个连续段的长度加 $1$，最后和答案取 $\max$。

问题变成了求操作前缀/后缀能否使一个位置变成 $\text{T}$，考虑 DP。

两个问题是一样的，这里说前缀。用 $0/1$ 表示为 $\text{T}/\text{B}$。

定义 $f_{i,a,b,c,d}$ 表示能否将 $S[i-3,i]$ 变成 $d,c,b,a$。初始状态 $f_{3,s_3,s_2,s_1,s_0}=true$。当然这里你可以状压一下。

转移时枚举 $x,y,z,j\in[0,1]$，即枚举前第一、二、三、四位，$f_{i,s_i,x,y,z}=\bigvee\limits_{x,y,z,j\in[0,1]} f_{i-1,x,y,z,j}$。同时对于 $S_i=1(\text{B})$，枚举一个 $j\in[0,1]$，即前第四位，$f_{i,0,1,1,0}=\bigvee\limits_{j\in[0,1]} f_{i-1,0,0,1,j}$。

前者表示不做操作正常转移，后者表示进行一次操作。

$S_i$ 能否变成 $\text{T}$ 等价于 $\bigvee\limits_{x,y,z\in[0,1]} f_{i,0,x,y,z}$。

后缀也是同理的。

```cpp
inline bool Check_f(int i)//能否变成 T
{
    if(i<0||i>=n) return 0;
    for(register int x=0;x<=1;++x)
        for(register int y=0;y<=1;++y)
            for(register int z=0;z<=1;++z)
                if(f[i][0][x][y][z]) return true;
    return false;
}
int main()
{
		f[3][s[3]=='B'][s[2]=='B'][s[1]=='B'][s[0]=='B']=true;
        if(f[3][1][0][0][1]) f[3][0][1][1][0]=true;//不要忘了这里
        for(register int i=4;i<n;++i)
        {
            if(s[i]=='B') f[i][0][1][1][0]|=f[i-1][0][0][1][0]|f[i-1][0][0][1][1];
            for(register int x=0;x<=1;++x)
                for(register int y=0;y<=1;++y)
                    for(register int z=0;z<=1;++z)
                        for(register int j=0;j<=1;++j)
                            f[i][s[i]=='B'][x][y][z]|=f[i-1][x][y][z][j];
        }
}
```

然后扫描一遍 $S$，求解答案即可。

```cpp
		for(register int i=0;i<s.size();++i)
        {
            if(s[i]=='T')
            {
                int j=i;
                while(j<s.size()&&s[j]=='T') ++j;
                --j;int len=(j-i+1);
                if(Check_f(i-1)) ++len;//前缀
                if(Check_g(j+1)) ++len;//后缀
                i=j;ans=max(ans,len);
            }
        }
```

---

