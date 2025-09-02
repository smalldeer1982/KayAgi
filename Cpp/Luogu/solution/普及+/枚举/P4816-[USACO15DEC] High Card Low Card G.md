# [USACO15DEC] High Card Low Card G

## 题目描述

奶牛 Bessie 是卡牌游戏的狂热爱好者，尽管她没有对生拇指，但这并不影响她的热情。遗憾的是，她的同伴们在卡牌游戏方面水平堪忧，甚至出牌顺序都完全可预测！尽管如此，Bessie 仍需精心策划才能获胜。

Bessie 和她的朋友 Elsie 正在玩一个简单的卡牌游戏。她们使用一副包含 $2N$ 张卡牌的牌组（编号为 $1 \ldots 2N$），并将牌分成各 $N$ 张。随后进行 $N$ 轮比赛：每轮双方各打出一张牌。在前 $N/2$ 轮中，打出较大数字的玩家得 1 分；在后 $N/2$ 轮中，规则反转，打出较小数字的玩家得 1 分。

已知 Bessie 可以预知 Elsie 每轮出牌的顺序，请计算 Bessie 能够获得的最大分数。

## 说明/提示

在此样例中，Bessie 手中的卡牌为 $2$、$5$、$6$ 和 $7$。她可以通过在比赛后半段保留 $2$ 这张牌，从而最多获得 2 分。

题目提供者：Brian Dean

## 样例 #1

### 输入

```
4
1
8
4
3
```

### 输出

```
2```

# 题解

## 作者：liyilin2004 (赞：13)

## 思路：贪心
### ~~赤裸裸的贪心~~
把读入的数据分成1~n/2，n/2+1~n两份，排序，用剩下的数（也就是Bessie的牌）最大的对第一份最大的数，依次减小，最小的对第二份最小的，依次增大
##### **上代码咯**
```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int a[25001],c[25001],b[100001];||a存前半部分，c存后半部分，b记录是谁的牌
int ans;
int main()
{
	cin>>n;
	for(int i=1;i<=n/2;i++)
	{
		cin>>a[i];
		b[a[i]]=1;
	}
	for(int i=1;i<=n/2;i++)
	{
		cin>>c[i];
		b[c[i]]=1;
	}
	sort(a+1,a+1+n/2);
	sort(c+1,c+1+n/2);||排序，方便下面贪心
	int j=2*n;
	for(int i=n/2;i>=1;i--)||从大到小枚举前半部分
	{
		while(b[j]&&j>=1)||找到Bessie未用的最大的牌
			j--;
		if(j<a[i])||最大的也比这张牌小，无解
			continue;
		else
			b[j]=1,ans++;		
	}
	j=1;	
	for(int i=1;i<=n/2;i++)
	{	
		while(b[j]&&j<=2*n)||找到Bessie未用的最小的牌
			j++;
		if(j>c[i])||最小的也比这张牌大，无解
			continue;
		else
			b[j]=1,ans++;
	}
	cout<<ans;
	return 0;
}

```
安利一发博客[liyilin2004的博客](https://www.luogu.org/blog/liyilin2004/)
欢迎来拜访⁄(⁄ ⁄•⁄ω⁄•⁄ ⁄)⁄

---

## 作者：onepeople666 (赞：8)

[题面传送门](https://www.luogu.com.cn/problem/P4816)

这道题就是一道纯**贪心**，下面讲讲我的解题步骤。

## 1.读入、存储
我们可以先用一个 e 数组来存储 $Elsie$ 的牌，再定义一个 $bool$ 数组 a，假如是 $Elsie$ 的牌就标记为1。接着，我们可以把 1~2n 扫一遍，假如 a[i] 没有被标记过，那么就把它存入数组 b，作为 $Bessie$ 的牌。此时，$Bessie$ 的牌是已经排好序的，因为我们在扫的时候其实已经模拟了一遍桶排的过程。


------------

```cpp
  bool a[100010]= {0}; //定义bool数组a，并初始化为零
  int n,e[50010],b[50010],c=1;//e,b数组分别存Elsie和Bessie的牌
  cin>>n;//输入n
  for(int i=1; i<=n; i++)
  {
    cin>>e[i];//读入Elsie的牌
    a[e[i]]=1;//并进行标记
  }
  for(int i=1; i<=2*n; i++)//扫一遍
    if(a[i]==0)//如果没有标记过 
      b[c++]=i;//存入b数组，已经排好序 
```


------------
## 2.排序、贪心
读入完之后，我们要把 e 数组进行分两端的排序，原因是游戏的前半部分是谁的牌点数大谁就赢，而后半部分却是谁的牌点数小谁就赢。所以前半段我们要从大到小排序，而后半段要从小到大排序。因为 $sort$ 是默认从小到大排序的，所以要让它从大到小排序就要我们自己写比较函数。
```cpp
bool cmp(int a,int b)
{
  return a>b;//从大到小排序 
}
```
接着就可以进行排序啦！
```cpp
  sort(e+1,e+n/2+1,cmp);//前半段 
  sort(e+n/2+1,e+n+1);//后半段
```
排序完之后，就可以贪心了。~~说了那么久才开始贪心~~

这道题的贪心思路和[田忌赛马](https://www.luogu.com.cn/problem/P1650)差不多。~~暗示着双倍经验~~在前半段中，$Bessie$ 要用第一~第(n/2+1)大的牌和 $Elsie$ 进行游戏。然后因为我们已经把 $Elsie$ 前半段用的牌排好序，并且在同半段中，不管 $Elsie$ 怎么出牌，结果都是一样的，所以我们可以认为 $Elsie$ 是从大到小出牌的。然后我们可以用 c 和 v 两个数分别记录 $Bessie$ 最小和最大的牌。接着拿 $Bessie$ 目前最大的牌和 $Elsie$ 最大的牌进行比较，如果比 $Elsie$ 最大的牌大，就赢，不然就用最小的牌怼掉 $Elsie$ 最大的牌。
```cpp
c=n/2+1,v=n;//c和v分别是最小和最大 
  for(int i=1; i<=n/2; i++) 
  {
    if(b[v]>e[i])//如果大于Elsie出的牌 
      ans++,v--;//赢一局 
    else//否则 
      c++;//拿最小的怼掉 
  }
```
后半段同理，直接贴代码了，具体见注释：
```cpp
c=n/2,v=1;//c和v分别是最大和最小
  for(int i=n/2+1; i<=n; i++)
  {
    if(b[v]<e[i])//如果小于Elsie出的牌 
      ans++,v++;//赢一局 
    else
      c--;//拿最大的怼掉
  }
```
最后就直接输出 ans 就可以啦，祝大家AC愉快！

---

## 作者：cosf (赞：2)

# [P4816 [USACO15DEC]High Card Low Card G](https://www.luogu.com.cn/problem/P4816)


## 做题之前

这道题有**三倍经验**。

有能力的可以做一下 [P3129](https://www.luogu.com.cn/problem/P3129)。

做了这道或 P3129 后，稍微再改一下就是 [P6179](https://www.luogu.com.cn/problem/P6179)。~~准确来说这里我说反了。~~

---

## 正常做法

既然前面 $\frac{n}{2}$ 次要大，后面 $\frac{n}{2}$ 次要小，那么，把 Bessie 大的 $\frac{n}{2}$ 张用在前面，剩下的用在后面，岂不是两全其美？

那么，前面和后面的部分就不相关联了。那么，我们可以直接套 P6179 的代码来做了。

---

## 怎么套？

我们可以构造两个 `set`，分别存大的和小的。根据思路，我们可以发现前半部分和后半部分做法差不多，所以这里我只写一下前半部分的做法。

每一次枚举一个 Elsie 选的数，如果有比它大的，就取比它大的中最小的，否则就取一个小的数，取什么都行，所以可以先不取，反正最后把大的数取完后剩下的个数就会等于没取的数，并且标记一下（即这次赢不了）。

---

## [AC Code](https://www.luogu.com.cn/record/93136114)

```cpp
#include <iostream>
#include <set>
using namespace std;

int a[100005];
set<int> sets; // set 大法好！我从 P6179 复制改一下的，所以变量名问题请忽略。
set<int, greater<int> > set2; // sets 是前面的，set2 是后面的。
int e[100005]; // Elsie
int n;

int main()
{
	cin >> n;
	for (int i = 1; i <= 2 * n; i++)
	{
		sets.insert(i);
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> e[i];
		sets.erase(e[i]);
	}
	for (int i = 1; i <= n / 2; i++) // 把小的移到 set2。
	{
		set2.insert(*sets.begin());
		sets.erase(sets.begin());
	}
	int cnt = n; // 默认每次都能赢，赢不了再减。
	for (int i = 1; i <= n / 2; i++)
	{
		set<int>::iterator iter = sets.upper_bound(e[i]); // 尽量只大一点，这样才不会使大一点的数没得赢。这就是贪心的策略。
		if (iter == sets.end())
		{
			cnt--; // 这次赢不了。
		}
		else
		{
			sets.erase(iter); // 这个就必须得删。
		}
	}
	for (int i = n / 2 + 1; i <= n; i++) // 再枚一遍即可。注意i的范围。
	{
		set<int>::iterator iter = set2.upper_bound(e[i]);
		if (iter == set2.end())
		{
			cnt--;
		}
		else
		{
			set2.erase(iter);
		}
	}
	cout << cnt << endl;
	return 0;
}
```


---

## 作者：MC_Launcher (赞：2)

首先让我们读懂题意

>现在有$B$与$E$在玩牌，一共$2n$局，牌的点数是$1$~$2n$，互补重复，前$n$局点数大者胜，后$n$局相反，现在已知$E$先手出牌，试问如何能让$B$获得最高分

读入的话，我们用一个bool型数组记录，然后读入完后遍历一遍，顺便排序，代码如下

```cpp
for(int i=1;i<=n;i++)
{
	cin>>a;
	b[a]=false;//如果e出了这张牌，b不可能拥有
	e_[now2++]=a;//将这张牌记录进e所拥有的牌中，now2表示e数组中现在牌放到哪里了
}
```
转换为数字

```cpp

for(int i=n*2;i>=1;i--)
{
	if(b[i])b_[now++]=i;//如果b有这张牌，记录进去
}
    
```

接着该怎么办呢？

如果一个一个查找，每次最快(用二分)也要$O(\logn)$才能查找出来，我们需要更快怎么办？

类似于田忌赛马的思想，我们先把$B$,$E$数组前后段分别排好序然后逐一比较，拿前半部分举例，如果$B$目前的数小，那么用下一个，否则就用这个数得分。

正确性证明

假设有两个有序上升数列$B$，$E$，且这两个数列没有交集。

假设有情况刚好$B_i>E_j$，设此时不是最优，那么设$B_{i-n}$或$B_{i+n}$与$E_j$配对可以更优，如果用$B_{i-n}$，那么根据条件，比$E_j$小，比原有可获得分数少$1$分，与原有假设不符；若选用$B_{i+n}$，那么$E_{j+n}$中可能存在比$B_i$大而比$B_{i+n}$小的数，此时也会使可获得分数减少，与假设不符。

因此这种算法正确。在打代码时，不仅要知道这个算法是对的，更要知道为什么是对的，知其然，更要知其所以然。

正确代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
bool b[100010];
int main()
{
	int b_[100010],e_[100010];
	int n;
	cin>>n;
	int a;
	memset(b,1,sizeof(b));
	int now2=1;
	for(int i=1;i<=n;i++)//读入
	{
		cin>>a;
		b[a]=false;
		e_[now2++]=a;
	}
	int now=1;
	for(int i=n*2;i>=1;i--)//将其转换一下，之所以倒着排，因为前半部分用较大数一定比较小数好
	{
		if(b[i])b_[now++]=i;
	}
	int ans=0,bnow=1,enow=1;
	sort(b_+1,b_+n/2+1);
	sort(b_+n/2+1,b_+n+1);//前后段分别排序 
	sort(e_+1,e_+n/2+1);
	sort(e_+n/2+1,e_+n+1); 
	for(int i=1;i<=n/2;i++)//前半部分数的比较
	{
		if((bnow<=n/2)&&(enow<=n/2)&&(b_[bnow]>e_[enow]))//如果没有超过牌的一半并且点数大，就用这牌
		{
			ans++;
			bnow++;
			enow++;
		}
		else if((bnow<=n/2)&&(enow<=n/2))//否则用其他牌抵消，用下一张牌赢
		{
			bnow++;
		}
	}
	bnow=n,enow=n;
	for(int i=n;i>n/2;i--)//因为这里是小的赢，所以从大往小比
	{
		if((bnow>n/2)&&(enow>n/2)&&(b_[bnow]<e_[enow]))//同前
		{
			ans++;
			bnow--;
			enow--;
		}
		else if((bnow>n/2)&&(enow>n/2))
		{
			bnow--;
		}
	}
	cout<<ans;//输出
  	return 0;
}
```

### 代码仅供对拍，请勿直接复制

---

## 作者：__Hacheylight__ (赞：2)

T1 High Card Low Card (Gold)

很快能想到贪心。

类似于田忌赛马那样，如果我方当前最好的card无法赢敌方的，那么就用最差的card去怼掉对方最好的；否则赢就是了

首先能赢就赢很明显；因为如果你这句不应放到后面去明显不会更优

用差的抵掉也很显而易见； 最差的作用最低，那么既然没人能赢他，那你就当替罪羊吧。

于是随便枚举一下时间复杂度O(n)

```cpp
#include <bits/stdc++.h>
using namespace std ;
#define rep(i, a, b) for (int (i) = (a); (i) <= (b); (i)++)
#define per(i, a, b) for (int (i) = (a); (i) >= (b); (i)--)
#define clr(a) memset(a, 0, sizeof(a))
#define ass(a, sum) memset(a, sum, sizeof(a))
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define enter cout << endl
#define SZ(x) ((int)x.size())
typedef long long ll ;
typedef unsigned long long ull ;
typedef vector <int> vi ;
typedef pair <int, int> pii ;
typedef map <int, int> mii ;
typedef map <string, int> msi ;
const int N = 50010 ;
const int iinf = INT_MAX ;
const ll linf = 2e18 ;
const int MOD = 1000000007 ;
void print(int x) { cout << x << endl ; exit(0) ; }
void PRINT(string x) { cout << x << endl ; exit(0) ; }
void douout(double x){ printf("%lf\n", x + 0.0000000001) ; }

int n, ans, cnt ;
int a[N], b[N], app[N * 2] ;

bool cmp1(int a, int b) {return a > b ;}
bool cmp2(int a, int b) {return a < b ;}

signed main(){
	freopen("cardgame.in", "r", stdin) ;
	freopen("cardgame.out", "w", stdout) ;
	scanf("%d", &n) ;
	rep(i, 1, n) scanf("%d", &a[i]) ;
	sort(a + 1, a + n / 2 + 1, cmp1) ; sort(a + n / 2 + 1, a + n + 1, cmp2) ;
	rep(i, 1, n) app[a[i]] = 1 ;
	per(i, n * 2, 1) if (!app[i]) b[++cnt] = i ;
	sort(b + 1, b + n / 2 + 1, cmp1) ; sort(b + n / 2 + 1, b + n + 1, cmp2) ;
	int l = 1, r = n / 2, ll = 1, rr = n / 2 ; // 用B去匹配A， 对于每半片区间，越靠前越强
 	while (l <= r && ll <= rr) {
 		if (a[l] < b[ll]) { // 良马赢良马
 			l++, ll++, ans++ ;
		}
		else { // 用最劣马怼掉良马
			l++, rr-- ;
		}
	}
	l = n / 2 + 1, r = n, ll = n / 2 + 1, rr = n ;
	while (l <= r && ll <= rr) {
		if (a[l] > b[ll]) {
			l++, ll++, ans++ ;
		}
		else {
			l++, rr-- ;
		}
	}
	printf("%d\n", ans) ;
}
/*
10
10 5 8 1 2 3 11 4 16 19
*/
```

---

## 作者：Level_Down (赞：1)

一道很明显的贪心题，只要找到贪心策略就很简单了。

在前半部分中，由于要出的比对手大才能赢，所以在前半部分我们肯定要挑已有牌中最大的那些，但同时我们又要让利益最大化，如果一个更大的数抢了比自己小的数可以赢的牌导致那个更小的数找不到能赢的牌那就得不偿失了，所以我们很快能得出贪心策略：

> 在保证所出的牌都是已有牌中最大的牌时，用其中**偏小**的挑选可以赢的对方手牌，然后再用偏大的挑选，直到可用手牌都挑完。

以此，我们可以继续推断后半部分的贪心策略：

> 在保证所出的牌都是已有牌中最小的牌时，用其中**偏大**的挑选可以赢的对方手牌，然后再用偏小的挑选，直到可用手牌都挑完。

然后我们可以以此打出暴力判断代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[50005],b[50005],p[100005],cnt,ans; 
bool f[50005];
inline int read(){
   register int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read(),p[a[i]] = 1;
    for (int i = n * 2; i >= 1; i--) if (p[i] == 0) b[++cnt] = i;
    //填充我方手牌，顺便直接从大到小排序qwq。
    cnt = n / 2;
    for (int i = cnt; i >= 1; i--)//因为要从较大的牌中从小到大挑选，故倒序。
    	{
    		int t = b[i];
    		for (int j = 1; j <= cnt; j++)
    			{
    				if (f[j] == 1) continue;
    				if (a[j] < t) {f[j] = 1,ans++;break;}
				}
		}
	for (int i = cnt + 1; i <= n; i++)//同上。
		{
			int t = b[i];
			for (int j = cnt + 1; j <= n; j++)
				{
					if (f[j] == 1) continue;
					if (a[j] > t) {f[j] = 1,ans++;break;}
				}
		}	
	printf("%d",ans);
    return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/56177670)

然后我们会发现这样直接打爆力会有 $2$ 个点超时，于是我们思考优化方法。

我们发现根据贪心策略，在前半段时，都是由较小的数先挑选，若是能够挑到，那么挑到的牌绝对是前半部分中较小的牌，于是我们就可以在判断之前将对方手牌的前半部分**从小到大排序**，直接按照顺序一个一个判断过去，所得答案一定最优。

同理，要将对方手牌的后半部分**从大到小排序**。

于是我们打出优化代码：


```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a[50005],b[50005],p[100005],cnt,ans,q; 
inline int read(){
   register int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=getchar();
   return s*w;
}
bool cmp(int x,int y){
	return x > y;
}
int main()
{
    n = read();
    for (int i = 1; i <= n; i++) a[i] = read(),p[a[i]] = 1;
    for (int i = n * 2; i >= 1; i--) if (p[i] == 0) b[++cnt] = i;
    cnt = n / 2;
    sort(a + 1,a + 1 + cnt);
    sort(a + 1 + cnt,a + 1 + n,cmp);//注意这里开始的地方也是a + 1 + cnt，小心别被坑了qwq。 
    q = 1;
    for (int i = cnt; i >= 1; i--)
    	{
    		if (b[i] > a[q]) q++,ans++;
		}
	q = cnt + 1;//别忘了重新赋值。 
	for (int i = cnt + 1; i <= n; i++)
		{
			if (b[i] < a[q]) q++,ans++;
		}	
	printf("%d",ans);
    return 0;
}
```

若有问题或是题解中有笔误可在评论中提出或者私我。

---

## 作者：newbeeglass (赞：0)

翻译有点难看懂，输入的是 Elsie 的牌，输入顺序不是出牌顺序，输入的前半部分数据是 Elsie 第一轮出的牌，后半部分是 Elsie 第二轮出的牌，这两者的分界线在  输入中应该体现得明显一点。

输入了 Elise 的牌就可以推出 Bessie 的牌，预处理完了之后，就可以使用贪心思想解决这题了。

首先应该排序（为了实现贪心，保证枚举的顺序是从大到小或从小到大），把 Elise 第一轮的牌从大到小排序，第二轮的牌从小到大排序，Bessie的牌由于是从小到大枚举出来的，已经排好序了，不需要再排一次。

就拿第一轮来说，Bessie 应该选择当前最大的牌与 Elsie 当前最大的牌抗衡，因为这样一来，如果比得过，Bessie 较小的牌就有机会与 Elise 较小的牌抗衡，收益最大。当然如果比不过，就用当前最小的把 Elise 当前最大的牌搞掉，损失降到最少，但是这一点在代码中不需要直接体现出来，碰到比不过 Elise 当前最大的牌的情况时，可以直接跳过，因为跳过了多少张牌，这一轮中 Bessie 就会有多少张牌枚举不到，由于是从大到小枚举的，枚举不到的牌正好是最小的那几个，相当于用这些牌抵掉了 Elise 的牌。

第二轮与第一轮恰好相反，思路一样，Bessie 以当前最小的牌与 Elise 当前最小的牌抗衡，操作基本相同。

其它细节注释都在代码里。

### AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000001],b[1000001],c[1000001];
bool cmp(int x,int y){
	return x>y;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[a[i]]=1;
	}
	sort(a+1,a+n/2+1,cmp); // 两边分别排序 
	sort(a+n/2+1,a+n+1); //要注意 sort 的区间是左闭右开区间 
	int cnt=0;
	for(int i=1;i<=2*n;i++){ // 找出 Bessie 要出的牌 
		if(!b[i]){
			b[i]=1;
			cnt++;
			c[cnt]=i;
		}
	} // 从小到大枚举，不需要排序 
	int ans=0,h=n; // h 表示 Bessie 当前的牌的序号，从尾部开始枚举，即从大到小枚举  
	for(int i=1;i<=n/2;i++){
		if(a[i]<c[h]){
			h--; // 比得过就找下一个 
			ans++;
		}
	}
	int t=1; // t 同上面的 h，从头开始枚举，即从小到大枚举 
	for(int i=n/2+1;i<=n;i++){
		if(a[i]>c[t]){
			ans++;
			t++; // 比得过就找下一个 
		}
	}
	cout<<ans;
}

```


---

## 作者：_k_e_v_i_n_ (赞：0)

# 思路：贪心

**~~完全就是贪心~~**，让我们边说思路边写代码

首先需要把输入的数据用一个桶存起来，方便计算 Bessie 的牌。

```
for(int i=1;i<=n;i++){
	cin>>a[i];
	b[a[i]]=1;	//用桶存放 Elsie 的牌
}
for(int i=1;i<=100000;i++){
	if(!b[i]){	//如果不是 Elsie 的牌，那么肯定就是 Bessie 的牌了
		q[++t]=i;	//t 是一个临时变量
	}
}
```

然后把读入的数据分成两份（分别是 $1$ 到 $n/2$，$n/2+1$ 到 $n$ ）排序。

```
int cmp(int x,int y){
	return x>y;
}
```

以上是排序的方式，下面是排序。

```
sort(a+1,a+n/2+1,cmp);	//前半段从大到小
sort(a+n/2+1,a+n+1);	//后半段从小到大
sort(q+1,q+n+1,cmp);	//Bessie 的牌从大到小
```

分别枚举两段。

```
for(int i=1,j=1,k=1;i<=n/2;i++){	//前半段
	if(a[j]>q[k]){	//如果 Bessie 最大的牌也比不过 Elsie，那么 Bessie 出什么牌就无所谓了
		j++;
	}else{	//否则 Bessie 用这张牌把 Elsie 怼掉
		ans++,j++,k++;
	}
}

for(int i=n/2+1,j=i,k=n;i<=n;i++){	//后半段
	if(a[j]<q[k]){	//如果 Bessie 最小的牌也没 Elsie 小，那么 Bessie 出什么牌就无所谓了
		j++;
	}else{
		ans++,j++,k--;
	}
}
```

**以上需要注意的一点是，枚举时不需要将 Bessie 怎样也怼不过 Elsie 的时候 Bessie 该出什么牌记录下来，因为如果出牌的话就有可能会影响到后面的出牌（~~最好不出~~）！**

~~最后输出。~~

```
cout<<ans;
return 0;	//别忘了返回
```
# 完整 AC 代码

**勿直接复制，理解重要！**

```
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
long long n,a[100001],q[100001],b[100001],t,ans;
int cmp(int x,int y){
	return x>y;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		b[a[i]]=1;
	}
	for(int i=1;i<=100000;i++){
		if(!b[i]){
			q[++t]=i;
		}
	}
	sort(a+1,a+n/2+1,cmp);
	sort(a+n/2+1,a+n+1);
	sort(q+1,q+n+1,cmp);
	for(int i=1,j=1,k=1;i<=n/2;i++){
		if(a[j]>q[k]){
			j++;
		}else{
			ans++,j++,k++;
		}
	}
	for(int i=n/2+1,j=i,k=n;i<=n;i++){
		if(a[j]<q[k]){
			j++;
		}else{
			ans++,j++,k--;
		}
	}
	cout<<ans;
	return 0;
}

```

最后祝大家 AC 愉快！

---

## 作者：䒛夢 (赞：0)


# 题意
你有1到n中除了对手选的牌，怎样你能赢最多局？
# 思路
定义两个数组，一个存你的牌，一个存对手的牌，将你的和他的排一遍，比较一下判断最多能赢几局。
# 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,z=0;//记录赢几局
int a[100100],b[100100],top=0;
bool v[100100];
bool cmp(int a , int b)
{
    return a>b;
}
int main()
{
    cin>>n;
    for(int i=1 ; i<=n ; ++i)
    {
        cin>>a[i];
        v[a[i]]=1;
    }
    for(int i=1 ; i<=2*n ; ++i)
        if(v[i]==0)
            b[++top]=i;
    sort(b+1 , b+1+n, cmp);//将你自己有的牌
    sort(a+1 , a+1+n/2,cmp);//将他前面的牌从大到小排序
    sort(a+1+n/2 , a+1+n);//将他后面的牌从小到大排序
    int top1=1;//一个计量你现在这一半已经用到几个了
    for(int i=1 ; i<=n/2 ; ++i)
    {
        if(a[i]<b[top1])//比完就换下一个
        {
            z++;
            top1++;
        }
    }
    int top2=n;
    for(int i=n/2+1 ; i<=n ; ++i)
    {
        if(a[i]>b[top2])比完换下一个
        {
            z++;
            top2--;
        }
    }
    cout<<z;
    return 0;
}
```


---

## 作者：Yusani_huh (赞：0)

我其实对用田忌赛马的方法做这道题比较疑惑，不过能这么做的话，应该自有道理，我就不多说了。

我采用的是一种比较奇怪但也很容易理解的方法（以下把 Elsie 简称为 E，把 Bessie 简称为 B）：

前 $N/2$ 轮是谁的牌大谁赢，那就把 E 的牌从大到小排，而 B 的牌要尽可能大，所以从她的牌中选出最大的前 $N/2$ 张牌，然后从大到小排序。

对接下来 $N/2$ 轮也是同样的做法，把 E 的牌从小到大排，把 B 剩下的 $N/2$ 张牌也从小到大排。

排序完了，接下来就是比较。

以前 $N/2$ 轮为例，我的比较方法是：把 B 的第一张牌与 E 的第一张牌比，如果 B 的牌大，就怼掉 E 的牌，然后换下一张；如果怼不掉，就接着用这张牌和 E 的第二张牌比，能怼掉就怼掉，怼不掉再和第三张比……

正确性也是很明显的。当 B 的一张牌与 E 的一张牌比较能怼掉时，有两种情况：B 的下一张牌也能怼掉 E 的这张牌，或 B 的下一张牌怼不掉 E 的这张牌了。

对于第二种情况，很明显这局应该怼，机不可失时不再来，过了这个村就没这个店了，肯定得怼掉。而对于第一种情况，既然 B 的下一张牌能怼掉 E 的这张牌，那 B 的下一张牌肯定也能怼掉 E 的下一张牌，所以不如干脆按顺序来，一个一个怼，亏不了的。

而如果 B 的牌怼不掉 E 的牌，后面的任意一张牌肯定都怼不掉这张牌，所以不如放过它，而且因为 B 的这张牌是目前她有的牌中最大的（前面更大的都怼掉了），价值最高，不妨留到后面，说不定能发挥用处。

对于后 $N/2$ 轮也同理，如果 B 的牌小就怼掉 E 的牌，如果怼不掉就往后顺顺，找机会再怼。

接下来上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,l,ans,b[50003],e[50003];
bool f[100003];
bool cmp(int a,int b){
	return a>b;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&e[i]);
		f[e[i]]=true;
	}
	for(int i=n*2;i>=1;--i)
		if(!f[i]) b[++l]=i;
	sort(e+1,e+n/2+1,cmp);
	sort(e+n/2+1,e+n+1);
	reverse(b+n/2+1,b+n+1);
   //以上都是在给双方排序，sort和reverse的用法请自行搜索
	int bl=1,el=1;
	while(el<=n/2&&bl<=n/2){
		if(b[bl]>e[el]) ans++,bl++;
		el++;
	}
   //前N/2轮，能怼就怼，怼不掉就往后顺
	bl=n/2+1,el=n/2+1;
	while(el<=n&&bl<=n){
		if(b[bl]<e[el]) ans++,bl++;
		el++;
	}
   //后N/2轮，规则改变，思路同理
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：李若谷 (赞：0)

# 贪心
a数组是Elsie的牌，b数组是Bessie的牌。

a的顺序是已知的，我们需要排列b的顺序。

很明显，对于第一轮，我们尽量要用大的牌，而第二轮要尽量用小的牌。
所以我们可以把b数组分为两段。

~~（根据田径赛马）~~ 显然对于第一轮，b数组每一次用自己一张牌跟a数组一张比自己更小的牌中的最大的是最优的。最后,b再拿最小的牌跟之前比不过a的牌比。第二轮的方法也一样。


代码
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int n;
int a[50001];
int b[50001];
bool use[100001];
void copy()
{
	for(int i=1;i<=n/2;i++)
		swap(b[i],b[i+n/2]);
}
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		use[a[i]] = 1;
	}
	sort(a+1,a+n/2+1);
	sort(a+n/2+1,a+n+1);
	int pos = 0;
	for(int i=1;i<=2*n;i++)
	{
		if(!use[i])
			b[++pos] = i; //此时，b是排好序的。原理桶排序。
	}
	copy(); //我们要把b变成大的在左边。
	int apos = n/2,bpos = n/2;
	int win = 0;
	//第一局
	while(bpos>=1&&apos>=1)
	{
		if(b[bpos] > a[apos])
		{
			++win;
			--bpos,--apos;
		}
		else
		{
			--apos;
		}
	}
	//第二局
	apos = n/2+1,bpos = n/2+1;
	while(bpos<=n&&apos<=n)
	{
		if(b[bpos] < a[apos])
		{
			++win;
			++bpos,++apos;
		}
		else
		{
			++apos;
		}
	}
	cout<<win<<endl;


}
```

---

