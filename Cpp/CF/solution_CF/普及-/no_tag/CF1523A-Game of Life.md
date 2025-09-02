# Game of Life

## 题目描述

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1523A/010268700b5eefe6d637a339a161b9e30121cb66.png)William really likes the cellular automaton called "Game of Life" so he decided to make his own version. For simplicity, William decided to define his cellular automaton on an array containing $ n $ cells, with each cell either being alive or dead.

Evolution of the array in William's cellular automaton occurs iteratively in the following way:

- If the element is dead and it has exactly $ 1 $ alive neighbor in the current state of the array, then on the next iteration it will become alive. For an element at index $ i $ the neighbors would be elements with indices $ i - 1 $ and $ i + 1 $ . If there is no element at that index, it is considered to be a dead neighbor.
- William is a humane person so all alive elements stay alive.

Check the note section for examples of the evolution.

You are given some initial state of all elements and you need to help William find the state of the array after $ m $ iterations of evolution.

## 说明/提示

Sequence of iterations of evolution for the first test case

- 01000000001 — initial state
- 11100000011 — first iteration of evolution
- 11110000111 — second iteration of evolution
- 11111001111 — third iteration of evolution

Sequence of iterations of evolution for the second test case

- 0110100101 — initial state
- 1110111101 — first iteration of evolution
- 1110111101 — second iteration of evolution

## 样例 #1

### 输入

```
4
11 3
01000000001
10 2
0110100101
5 2
10101
3 100
000```

### 输出

```
11111001111
1110111101
10101
000```

# 题解

## 作者：Hamer_sans (赞：6)

# CF1523A的题解

为什么这道题的题解只有一篇，那我来充个数。

### 题目简意：

就是给定一个长度为 $n$ 的 $01$ 串，要求进行 $m$ 次操作，将 $01$ 串中的 $0$ 在旁边只有一个 $1$ 的情况下变为 $1$ ，输出最后的 $01$ 串。

### 分析：

第一次看，这不就是一道模拟题吗？我于是就写了一篇时间复杂度为 $O(tnm)$ 的代码，具体思路是，每次操作跑一遍字符串，把能操作的 1 都给操作扩展一遍，然后自信往上一交，果然 TLE 了，为什么呢？我仔细一看数据：$1 \le t \le 10^{3}$，$2 \le n \le 10^{3}$，$1 \le m \le 10^{9}$，这数据，$O(tnm)$ 不 TLE 才怪，那就换一种思路再去做。

那么问题来了，怎么优化呢？没有关系，我们想吧，$m$ 的数据范围很大，我们可不可以把 $m$ 给优化掉呢？首先一个 $1$ 最多向一个方向拓展 $m$ 次，所以我们可以利用一个类似于前缀和的思路，把每一个 $0$ 距前一个 $1$ 的位置用一个数组 $b$ 记录下来，把距后面一个 $1$ 的位置用一个数组 $p$ 记录下来，然后再判断每一个位置的字符，分类讨论如下：

1.当字符串本位置本来就是 $1$ 时，它就是 $1$。

2.当字符串本位置是 $0$ ，但距两边 $1$ 的距离相等时，这个 $0$ 无论如何都变不成 $1$。

3.当字符串本位置是 $0$ ，且距左右两边 $1$ 的距离都小于我们的操作次数时,就输出 $1$ ，因为变 $m$ 轮，所以当小于操作次数时，就可以变为 $1$。

4.其余情况都为 $0$。

提交，可恶，还没通过。那么问题又来了，哪里出问题呢？还是没有关系，仔细一看，大概是每一个的首尾没有处理好，那我们可以把字符串的头加上一个，这样下标就没有问题了，但是数组 $b$ 和数组 $p$ 怎么处理呢？我们把 $b_{0}=-\infty$，$p_{n+1}=+\infty$，那么就有人要问了，你为啥不把 $b_{0}=+\infty$，$p_{n+1}=-\infty$ 呢？ 首先如果将 $b_{0}=+\infty$，那么求位置 $1$ 距前面的 $1$ 的距离时，也就是 $b_{1}-b_{0}$，就是一个正整数减去一个正无穷，所以是一个负无穷，也就会出错，同样 $p_{n}-p_{n+1}$ 也是同样的道理。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int t,n,m;
int b[N],p[N];
int inf=0x3f3f3f3f;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		string a;
		cin>>a;
		b[0]=-inf;
		p[n+1]=inf;
		string x="0";
		x+=a;
		for(register int i=1;i<=n;++i){
			if(x[i]=='1') b[i]=i;
			else b[i]=b[i-1];
		}
		for(register int i=n;i>=1;--i){
			if(x[i]=='1') p[i]=i;
			else p[i]=p[i+1];
		}
		for(register int i=1;i<=n;++i){
			if(x[i]=='1') cout<<x[i];
			else{
				int l=i-b[i],r=p[i]-i;
				if(l==r) printf("%d",0);
				else if(l<=m or r<=m) printf("%d",1);
				else printf("%d",0);
			}
		}
		printf("\n");
	}
	return 0;
}
```
#### 蒟蒻第一篇题解，求大佬轻喷。

---

## 作者：Chenyichen0420 (赞：2)

# 题目大意

给你一个 $01$ 串，让你进行 $m$ 次变换，请问你变换完毕后的 $01$ 串是什么样的。

其中，一次变换是指将要变换的串将每个有且仅有一个 $1$ 与之相邻的 $0$ 变为 $1$。

# 解题思路

这道题理论上暴力可以过。下面证明：

对于每一次变换，有如下两种情况：

有变换的数，此时至少有 $1$ 个数出现了改变。

无变换的数，此时以后一定不会再发生任何变化，即这时的串就是最终的串。

这样的话，每个串变换的次数一定是小于其长度 $n$ 的。

这样的话时间复杂度为 $O(t\times n^2)$，总体即为 $10^9$ 次的量级，卡一下常，吸一下氧气差不多就过了。

下面附上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m; char s[1005],s2[1005]; 
int main(){
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--){
		cin>>n>>m>>(s+1); s[0]=s[n+1]='0';
		for(int i=1;i<=m;++i){
			memcpy(s2,s,sizeof s);
			for(register int j=1;j<=n;++j){
				if(s2[j]^48) s[j]='1';
				else s[j]=((s2[j+1]^48)+(s2[j-1]^48)==1)|48;
			}
			if(!strcmp(s,s2)) break;
		}
		for(register int i=1;i<=n;++i)putchar(s[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：cmll02 (赞：2)

提供 $O(n)$ 的做法。

记录每个点最近的两个 $1$（前面和后面）。

判断：如果到两边距离相等那么还是 $0$。

否则如果距离够就是 $1$。

代码：

```cpp
// Problem: A. Game of Life
// Contest: Codeforces - Deltix Round, Spring 2021 (open for everyone, rated, Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/1523/problem/A
// Memory Limit: 256 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <stdio.h>
#include <string.h> 
#include <algorithm>
#include <queue>
#define od(x) printf("%d",x)
#define odb(x) printf("%d ",x)
#define odl(x) printf("%d\n",x)
#define odp(x,y) printf("%d %d\n",x,y)
#define ol(x) puts("")
#define old(x) printf("%lld",x)
#define oldb(x) printf("%lld ",x)
#define oldl(x) printf("%lld\n",x)
#define oldp(x,y) printf("%lld %lld\n",x,y)
//#define int long long
inline int read()
{
	int num=0,f=1;char c=getchar();
	while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
	while(c>47&&c<58)num=num*10+(c^48),c=getchar();
	return num*f;
}
inline int re1d()
{
	char c=getchar();
	while(c<48||c>49)c=getchar();
	return c&1;
}
inline int min(int a,int b){return a>b?b:a;}
inline int max(int a,int b){return a<b?b:a;}
int a[10005],pre[10005],suf[10005];
signed main()
{
	int T=read();
	pre[0]=-2000000000;
	while(T--)
	{
		int n=read(),m=read();
		for(int i=1;i<=n;i++)a[i]=re1d();
		for(int i=1;i<=n;i++)
		{
			if(a[i])
			{
				pre[i]=i;
			}
			else pre[i]=pre[i-1];
		}
		suf[n+1]=2000000000;
		for(int i=n;i>=1;i--)
		{
			if(a[i])suf[i]=i;else suf[i]=suf[i+1];
		}
		for(int i=1;i<=n;i++)if(a[i])putchar(49);
		else
		{
			int x=i-pre[i],y=suf[i]-i;
			if(x==y)putchar(48);
			else if(x<=m||y<=m)putchar(49);
			else putchar(48);
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：SH___int (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/CF1523A)

## 一、思路
读了一遍题，没怎么读懂，但观察样例后可以发现，要把 ‘0’ 变成 ‘1’ ，只需要满足两种情况里的任意一种就可以了：

	1. '0'的左边是'1',右边不是'1'的情况。
    2. '0'的右边是'1',左边不是'1'的情况。
## 二、优化
但光这样还不行，代码实现后会超时，所以要稍微优化。我们可以看到 $n$ 的大小，也就是字符串的长度不超过 $1000$ ,而 $m$ ，也就是轮数的大小有 $10$ 的 $9$ 次方这么大，肯定用不了这么多轮，所以只需要判断一下还能否继续变成 ‘1’ ，如果不能就直接输出结果，可以节省很多时间，通过此题就很轻松啦。
## 三、代码

具体怎么用代码实现呢？让我们一起来看一看吧！
```
#include<bits/stdc++.h>
using namespace std;
string s;
int main()
{
	int t;//一共测试的组数
	int n,m;//字符串的长度和变'1'的轮数
	scanf("%d",&t);
	bool js;//优化，下面细讲
	for(int i=0;i<t;i++)
	{
		cin>>n>>m>>s;
		for(int j=0;j<m;j++)//循环轮数
		{
			js=true;//赋初值，设为最初应该结束
			for(int p=0;p<s.size();p++)
			{
				if(s[p]=='0')
				{
					if(s[p-1]!='1'&&s[p+1]=='1')//两种情况，上面讲过
					{
						js=false;//运行了，说明还可以变'1'，所以还不能结束（下同）
						s[p]='2';//先把应该变成'1'的'0'变为'2'，防止它们在同一轮继续扩散
					}
					else if(s[p-1]=='1'&&s[p+1]!='1')
					{
						js=false;
						s[p]='2';
					}
				}
			}
			if(js==true)//如果不能继续变'1'了
			{
				break;//直接跳出轮数的循环
			}
			for(int p=0;p<s.size();p++)
			{
				if(s[p]=='2')//把应该变为'1'的'0'变为'1'
				{
					s[p]='1';
				}
			}
		}
		cout<<s<<endl;//输出变完后的答案
	}
	return 0;
}
```
~~码风很丑，不喜勿喷~~
## 四、总结
我再细讲一下为什么要把 ‘1’ 先变成 ‘2’ ，由于某一轮变 ‘1’ 过程还没有结束，所以为了防止将 ‘0’ 变为 ‘1’ 以后影响后面的变化，可以先把 ‘0’ 变为其他的东西储存起来，最后再统一变。

最后如果有什么意见或建议，欢迎在下方评论出来，我会努力改进的。

感谢阅读QWQ！

---

## 作者：dks0311 (赞：1)

### 题意
- 给定 $t$ 个长度为 $n$ 的 $01$ 序列。
- 进行 $m$ 次操作，每次将所有只有一个 $1$ 与之相邻的 $0$ 变成 $1$。

### 思路
如果要对于每组数据枚举 $m$ 次，时间复杂度为 $O(tnm)$，显然要 TLE 掉。所以我们想到了预处理。

首先我们要输入，所以 $O(tn)$ 的复杂度是少不了的，所以我们只有想办法将 $m$ 去掉。

于是我们可以将每一个 $0$ 和前面一个 $1$ 的距离与和后面一个 $1$ 的距离预处理出来，用两个数组存储。

对于每一个位置，分以下 $4$ 种情况讨论：

- 本来就为 $1$，不变。
- 否则，和前后的 $1$ 距离相等，不变。
- 否则，和前后任意一个 $1$ 距离小于 $m$，变为 $1$。
- 其它情况为 $0$。

具体分析过程这里就不再赘述，直接上代码。

### 代码
```
#include <bits/stdc++.h>
using namespace std;
const int N = 1e3 + 5;
const int INF = 0x3f3f3f3f;
int t;
int d1[N], d2[N], a[N];
inline int read(){
	int s = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)){if(ch == '-') f = -1; ch = getchar();}
	while(isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
	return s * f;
}	//快读 
int main(){
	t = read();
	while(t--){
		int n = read(), m = read();
		for(register int i = 1; i <= n; ++i)
			a[i] = getchar() - '0';	//输入 
		int pos = 0;
		for(register int i = 1; i <= n; ++i){
			if(a[i] == 1) pos = i;
			else{
				if(pos == 0) d1[i] = INF;
				else d1[i] = i - pos;
			}
		}	//和前一个1的距离 
		pos = 0;
		for(register int i = n; i >= 1; --i){
			if(a[i] == 1) pos = i;
			else{
				if(pos == 0) d2[i] = INF;
				else d2[i] = pos - i;
			}
		}	//和后一个1的距离 
		for(register int i = 1; i <= n; ++i){
			if(a[i] == 0 && d1[i] != d2[i] && (d1[i] <= m || d2[i] <= m)) a[i] = 1;
		}
		for(register int i = 1; i <= n; ++i)
			printf("%d", a[i]);
		puts("");
	}
	return 0;
}
```
蒟蒻的第 $2$ 篇题解，大佬们多多指教。

---

## 作者：xwh_hh (赞：0)

一道水题。

我们需要弄懂一件事情：怎样的 $0$ 会变成 $1$？  
这里我给出答案：  
首先，$m$ 次操作要波及到这个位置，离它最近的 $1$ 的位置与它的位置距离应不超过 $m$。  
其次，在它左边的离它最近的 $1$ 的位置与它的位置距离不能等于在它右边的离它最近的 $1$ 的位置与它的位置距离。  
举个例子：  
```
1000001
1100011
1110111
```
这个例子中最中间的 $0$ 永远不会变成 $1$。  
搞懂了以上这些，就基本成功了。  
至于它左边的离它最近的 $1$ 的位置怎么求，只需要开一个数组，递推一下即可，它右边的离它最近的 $1$ 的位置也是一个道理。  
时间复杂度 $O(\sum n)$。  
代码实现：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m; 
string s;
int a[1005],b[1005];//递推数组 
int main(){
	cin>>t;
	while(t--){
		cin>>n>>m>>s;
		s=" "+s;
		a[0]=-0x3f3f3f3f;
		b[n+1]=0x3f3f3f3f;
		//递推过程 
		for(int i=1;i<=n;i++){
			if(s[i]=='1') a[i]=i;
			else a[i]=a[i-1];
		}
		for(int i=n;i>=1;i--){
			if(s[i]=='1') b[i]=i;
			else b[i]=b[i+1];
		}
		//判断过程 
		for(int i=1;i<=n;i++){
			if(s[i]=='1') cout<<1;
			else if((i-a[i]<=m||b[i]-i<=m)&&i-a[i]!=b[i]-i) cout<<1;
			else cout<<0;
		}
		cout<<endl;
	}
	return 0;//再见 
}

```

---

## 作者：a1a2a3a4a5 (赞：0)

#### [题目：](https://www.luogu.com.cn/problem/CF1523A)
- 题意：
1. 给你一个初始字符串，它会按照一定规律变化：当一个 $ 0 $ 旁边只有一个$1$时，那么这个$0$在**下一轮**变成 $ 1 $。求 ` m ` 轮之后的字符串。
- 思路
1. 直接模拟，开始先把要变化的 $ 0 $ 先设为 $ 2 $，在所有遍历完一次后再将 $ 2 $ 转为 $ 1 $。
- 问题
1. 我开始就直接将 $ 0 $ 先转为 $ 1 $，那么会错，比如 ` 1 0 0 0 0 0 `，仅仅在一轮之后就变成了 ` 1 1 1  1 1 1 `，非常的不合理，所以我们要先给将变化的 $ 0 $ 转换一个其他字符，然后再在事后转为 $ 1 $。
2. 如果你没读清题，你会把只有一个 $ 1 $ 写成有 $ 1 $ ，导致一个样例没过。
- 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
string s;
int main()
{
		cin>>t;
		while(t--)
		{
			cin>>n>>m>>s;
			while(m--)
			{
				for(int i=0;i<n;i++) if((s[i+1]=='1'&&s[i-1]!='1')||(s[i+1]!='1'&&s[i-1]=='1')) s[i]='2';
				//将即将变化的0先转为2，避免后面的0被这个零变化
				for(int i=0;i<n;i++) if(s[i]=='2') s[i]='1';
				//转化回来
			}
			cout<<s<<"\n";
		}
		return 0;
}
```
- 题目名字来源：
1. 这个题目翻译过来就是：生命游戏。这个游戏是有的，和这个题有一点相似，可以体验一下这个模拟器：[Game of Life](https://playgameoflife.com/)

---

## 作者：_Evergarden_ (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/CF1523A)


## 题目大意

给出一个长度为 $n$ 的 01 串，当一个 0 旁边只有一个 1 时，这个 0 就变为 1。输出最后的 01 串。

## 思路

看上去就是一道模拟，可以写出一个 $O(tnm)$ 的程序，但是，下方的数据已给出：$1 \le t \le 10^3$，$ 2 \le n \le 10^3$，$1 \le m \le 10^9$，肯定会 TLE 的，我们考虑更好方法。

通过观察题目，我们可以知道，当一个 0 两边只有一个 1 时，它就会变为 1，这样下去，只有旁边有两个一且距离这个 0 相等时，它才不会变为 1。

接下来就是代码了。

## 代码

```cpp
#include <bits/stdc++.h>

using  namespace std;

int a[1001], dist[1001], vis[1001];//a数组是存01串的，dist数组是存距离的，vis数组是判断的
int T, n, m;
char s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);//输入优化

	cin >> T;
	while(T --) {
		cin >> n >> m;
		for(int i = 1; i <= n; ++ i) {
			cin >> s;
			a[i] = s - '0';
			dist[i] = 1e9 + 9;
			vis[i] = 1;
		}
		for(int i = 1; i <= n; ++ i) {
			if(a[i] == 1) {
				for(int j = 1; j <= n; ++ j) {
					if(a[j] == 0) {
						if(abs(j - i) == dist[j]) vis[j] = 1;
						if(abs(j - i) < dist[j]) {
							dist[j] = abs(j - i);
							vis[j] = 0;
						}
					}
				}
			}
		}
		for(int i = 1; i <= n; ++ i) {
			if(a[i] == 0 && (dist[i] > m || vis[i] == 1)) cout << '0';
			else cout << '1';
		}
		cout << "\n";
	}
	return 0;
}
```


---

## 作者：齐心协力 (赞：0)

# CF1523A Game of Life 题解

### 题意
t 组测试数据，每组给定 01 串的长度 n 和轮数 m 。

对于每一轮，每个有且仅有一个 1 与之相邻的 0 会变成 1 。例 101 中的 0 不会变成 1，但 1000001 经过 2 轮后变成 1110111 。

每组测试数据输出经过 m 轮后的 01 串并换行。

### 思路1：模拟
我们可以根据题目所给的模拟过程写出代码。

时间复杂度 $O(tnm)$，如果加一个小小的优化，那么时间复杂度为 $O(tn^2)$。

#### [代码](https://www.luogu.com.cn/paste/gjzdlq6s)


### 思路2：优化
由于我门要读入，思来想去只能把 $m$ 次循环去掉。

我们不难发现：每次变化可以看做是以 $“1”$ 为中心向外扩散，无法变化的情况是两边同时扩散到同一个点。

然而向外扩散的过程太麻烦了，我们可以将其再次转换：我们不从 $“1”$ 扩散，而是从 $“0”$ 接收。什么意思呢？

不妨举个例子：
![](https://cdn.luogu.com.cn/upload/image_hosting/aey033ta.png)
这样一来，循环次数减少，就可以通过这道题。

[代码](https://www.luogu.com.cn/paste/dpzv2ntb)

---

## 作者：Noby_Glds (赞：0)

看这数据范围就知道，暴力是不可能暴力的，得想简单亿点的方法。

### 思路：
我们用 $dis$ 数组记录当前位置的 $0$ 与最近的 $1$ 的距离。

如果 $m$ 小于 $dis(i)$，那么这个 $0$ 就不会变成 $1$。

**但是**：$\texttt{101}$ 中的 $0$ 是安全的！

所以，需要 $sav$ 数组来记录该位置的 $0$ 会不会在某一轮中被两个 $1$ 夹击。

如果离 $0$ 最近的 $1$ 有两个，那么它就是安全的。

如果 $dis(i)$ 的值更新了，那这个零就不安全了，因为离它最近的 $1$ 只有一个了。
### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[1010],dis[1010],sav[1010];
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		char b;
		cin>>n>>m;
		for(int j=1;j<=n;j++){
			cin>>b;
			a[j]=b-'0';
			dis[j]=99999999,sav[j]=1;
		}
		for(int j=1;j<=n;j++){
			if(a[j]==1){
				for(int k=1;k<=n;k++){
					if(a[k]==0){
						if(abs(j-k)==dis[k]) sav[k]=1;
						if(abs(j-k)<dis[k]){
							dis[k]=abs(j-k);
							sav[k]=0;
						}
					}
				}
			}
		}
		for(int j=1;j<=n;j++){
			if(a[j]==0&&(dis[j]>m||sav[j]==1)) cout<<"0";
			else cout<<"1";
		}
		cout<<endl;
	}
	return 0;
}
```


---

