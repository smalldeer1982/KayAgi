# Three Sevens

## 题目描述

Lottery "Three Sevens" was held for $ m $ days. On day $ i $ , $ n_i $ people with the numbers $ a_{i, 1}, \ldots, a_{i, n_i} $ participated in the lottery.

It is known that in each of the $ m $ days, only one winner was selected from the lottery participants. The lottery winner on day $ i $ was not allowed to participate in the lottery in the days from $ i+1 $ to $ m $ .

Unfortunately, the information about the lottery winners has been lost. You need to find any possible list of lottery winners on days from $ 1 $ to $ m $ or determine that no solution exists.

## 说明/提示

In the first test case, one of the answers is $ [8, 2, 1] $ since the participant with the number $ 8 $ participated on day $ 1 $ , but did not participate on days $ 2 $ and $ 3 $ ; the participant with the number $ 2 $ participated on day $ 2 $ , but did not participate on day $ 3 $ ; and the participant with the number $ 1 $ participated on day $ 3 $ . Note that this is not the only possible answer, for example, $ [8, 9, 4] $ is also a correct answer.

In the second test case, both lottery participants participated on both days, so any possible lottery winner on the day $ 1 $ must have participated on the day $ 2 $ , which is not allowed. Thus, there is no correct answer.

In the third test case, only one participant participated on days $ 2 $ , $ 3 $ , $ 4 $ , and on day $ 1 $ there is only one participant who did not participate in the lottery on days $ 2, 3, 4 $ — participant $ 2 $ , which means $ [2, 1, 4, 3] $ is the only correct answer to this test case.

## 样例 #1

### 输入

```
3
3
4
1 2 4 8
3
2 9 1
2
1 4
2
2
1 2
2
2 1
4
4
1 2 3 4
1
1
1
4
1
3```

### 输出

```
8 2 1 
-1
2 1 4 3```

# 题解

## 作者：EdenSky (赞：9)

# [CF1798B Three Sevens](https://www.luogu.com.cn/problem/CF1798B)
- [或许更好的阅读体验](https://www.cnblogs.com/wanguan/p/17629910.html)

## 正文

开个数组 $last_k$ 统计 $a_{i,j}$ 最后买彩票的时间，再开一排桶 $day_t$ 记录该天最后买彩票的有哪些人（即：有 $p$ 满足 $last_p=t$ 的集合）。

将 $last_k$ 放入 $day_t$ 中，判断 $day_t$ 中是否存在空桶，若有则无解（因为没有人在某一天是最后买彩票的）。

因为本题是 SPJ，对于每个桶 $day_t$，输出其中任意一个元素都是正确的，因此我们开桶的时候完全没必要用 `vector`，每个桶只需要存一个元素，用 C++ 内置数组完全够用。

~~因为懒~~，我将 $last_k$ 用 `unordered_map` 取代。

```cpp
#define by_wanguan
#include<iostream>
#include<cstring>
#include<unordered_map>
using namespace std;
const int N=5e4+7;
int t,m,n,a,day[N];
unordered_map<int,int> last;
int main(){
  ios::sync_with_stdio(false),cin.tie(0);
  cin>>t;
  while(t--){
    last.clear();
    memset(day,0,sizeof day);
    cin>>m;
    for(int i=1;i<=m;i++){
      cin>>n;
      for(int j=1;j<=n;j++)
        cin>>a,last[a]=i;
    }
    int M=m;//统计还有多少桶是空的
    for(auto &i: last){//将last放入桶中
      if(!day[i.second]) M--;
      day[i.second]=i.first;
    }
    if(M) cout<<-1;
    else for(int i=1;i<=m;i++) cout<<day[i]<<' ';
    cout<<'\n';
  }
}
```

[AC 记录](https://www.luogu.com.cn/record/120905058)。

---

## 作者：Larryyu (赞：2)

[题目链接](https://www.luogu.com.cn/problem/CF1798B)
## _Description_
一场彩票活动将持续 $m$ 天，每天有 $n$ 个编号分别为 $a_{i,1},a_{i,2}\dots a_{i,n}$ 的人在该天的参与名单里，你需要在这 $m$ 天的参与名单，每天的名单选出一个人，使得他不在后续任何一天的名单里。如果无法选出，输出 ```-1```，否则输出每天被选出的人的编号。
## _Solution_
设编号为 $i$ 的人最后一次出现在名单里是第 $last_i$ 天。

对于第 $j$ 天，若 $last_i(1\leq i\leq n)\ne j$，则无法选出一个人，因为这天都不是他们最后一次出现在名单上，否则就任选一个 $last=j$ 的人。

可以在输入时就更新当天每个人的 $last$ 值。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
int t;
int last[50050],ans[50050];
vector<int> a[500500]; //数组存不下，用 vector 储存
ll read(){
    ll x=0,f=1;
    char ch;
    ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void init(int m){ //记得初始化
	for(int i=1;i<=m;i++){
		a[i].clear();
	}
}
void solve(){
	memset(last,-1,sizeof(last));
	memset(ans,0,sizeof(ans));
	int m=read(),mm=m;
	init(m);
	for(int i=1;i<=m;i++){
		int n=read();
		for(int j=1;j<=n;j++){
			int x=read();
			a[i].emplace_back(x);
			last[x]=max(last[x],i); //更新 last
		}
	}
	for(int i=1;i<=m;i++){
		bool f=0;
		for(int j=0;j<a[i].size();j++){
			if(last[a[i][j]]==i){ //是最后一次出现在名单上
				f=1;
				ans[i]=a[i][j]; //因为无法确定后面能否选出人，所以要先存着
				break;
			}
		}
		if(f==0){
			cout<<-1<<endl;
			return;
		}
	}
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<" ";
	}
	cout<<endl;
	
}
int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：AzureHair (赞：1)

这道题算是一道比较简单的构造题，首先看一下题目:  
一共有 $m$ 天，每天有 $n_i$ 人买了彩票，分别为 $a_{i,1}\cdots a_{i,{n_i}}$。现在请你安排每天的一位中奖的人，满足他在之后的天里都没有买彩票。如果可以，给出方案，否则输出 $-1$ ;     
     
我们可以看出，对于一个人，除了最后一次买彩票外，他什么时候买彩票都对答案没有任何的影响，所以我们只需要知道一个人他最后一次买彩票是什么时候，其余的全部不记录，于是在一次询问输入结束后，我们就得到了每个人最后一次买彩票是哪一天，现在这个问题就变得非常简单了，因为你需要让每一天都有一个中奖的人，所以你只需要判断这 $m$ 天里是否每一天都有至少一个人最后一次买彩票，如果有那么就存在答案，如果没有就没有方案则输出 $-1$ 。    

这道题就这么结束了，等等。   

这道题还没结束，看到题目所给的数据范围，我们发现 $1\le t \le 50000$ ，$1\le m \le 50000$ ，以及 $n$ 的总和不超过 $50000$ 。时限给了两秒，我们发现像我这样从来懒得写快读的就 T 飞了，所以还要加上快读，于是这道题就过了   

放一下代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,a[50010],vis[50010];
//a 数组记录每个人最后一次买彩票的时间
//vis 数组记录每一天是否有人最后一次买彩票 
inline int read()//快读 (不加会 TLE 别问我怎么知道的 
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main()
{
	t=read();
	for(int k=1;k<=t;k++)
	{
		memset(a,0,sizeof(a));
		memset(vis,0,sizeof(vis));
		m=read();
		for(int i=1;i<=m;i++)
		{
			n=read();
			for(int j=1;j<=n;j++)
			{
				int x;
				x=read();
				a[x]=i;//记录买当前最后一次买彩票的时间 
			}
		}
		for(int j=1;j<=50000;j++)
		{
			if(a[j])
			{
				vis[a[j]]=j;//记录每一天是否有人最后一次买彩票 
			}
		}
		bool flag=0;
		for(int j=1;j<=m;j++)
		{
			if(!vis[j])
			{
				flag=1;
				break;
			}
		}
		if(flag)
		{
			cout<<-1<<endl;
		}
		else
		{
			for(int j=1;j<=m;j++)
			{
				printf("%d ",vis[j]);//输出一种可能的构造 
			}
			printf("\n");
		}
	}
	return 0;
}
```
**初次写题解，望多多包容，不喜勿喷**

---

## 作者：chlchl (赞：1)

~~话说这题我们老师困了一个小时做不出来，导致他愤怒无比~~。

## 题意简述
有 $m$ 天，每天出现 $n$ 个数。要求在每天都选一个数，使得这个数在后面都没出现过。

## Solution
暴力模拟就行。

注意到 $1\leq a_{i,j}\leq 50000$，所以考虑对于每个数，记录 $lst_i$ 为 $i$ 最后一次出现在第几天。这样，只要 $\forall i\in[1,m],\exists j\in[1, n_i]$ 满足 $lst_{a_{i,j}}=i$，就能选出方案，否则就不行。

那剩下的就是计算 $lst$ 了。因为读入的时候按天数顺序读入，所以每次读入一个 $a_{i,j}$，直接更新 $lst_{a_{i,j}}$ 就好了。

然后注意一个细节：它保证 $\sum{n\times m}\leq 50000$，但是因为 $n,m$ 具体大小未知，正常开二维数组的话要 $50000\times 50000$，空间吃不消。你可以化为 `vector` 或者一位数组存。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 50000 + 10;
int T, m, n, lst[N], ans[N];
vector<int> a[N];

int main(){
	scanf("%d", &T);
	while(T--){
		memset(ans, 0, sizeof(ans));
		memset(lst, 0, sizeof(lst));//多测不清空，爆零两行泪
		scanf("%d", &m);
		for(int i=1;i<=m;i++){
			scanf("%d", &n);
			for(int j=1,x;j<=n;j++){
				scanf("%d", &x);
				a[i].push_back(x);
				lst[x] = i;
			}
		}
		bool f = 1;
		for(int i=1;i<=m;i++){
			bool f1 = 0;
			for(int v: a[i]){
				if(lst[v] == i){
					ans[i] = v, f1 = 1;
					break;
				}
			}
			if(!f1){
				printf("-1\n"), f = 0;
				break;
			}
		}
		if(f){
			for(int i=1;i<=m;i++)
				printf("%d ", ans[i]);
			printf("\n");
		}
	}
	return 0;
}
```


---

## 作者：ncwzdlsd (赞：0)

设编号为 $i$ 的人最后买彩票在 $lst_i$ 天，容易想到，把中奖者的中奖日期安排在他买彩票的最后一天是一种合理的方案。

用 $day_i$ 表示每一天中奖者的编号，如果有一天找不到满足条件的中奖者，则不存在方案。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}

const int maxn=50005;
int lst[maxn],day[maxn];

void solve()
{
    int m=read();
    int mxid=1;
    memset(lst,0,sizeof lst),memset(day,0,sizeof day);
    for(int i=1;i<=m;i++)
    {
        int n=read();
        for(int j=1;j<=n;j++)
        {
            int a=read();lst[a]=i;
            mxid=max(mxid,a);
        }
    }
    for(int i=1;i<=mxid;i++) if(lst[i]) day[lst[i]]=i;
    bool flag=1;
    for(int i=1;i<=m;i++) if(!day[i]){flag=0;break;}
    if(flag) for(int i=1;i<=m;i++) cout<<day[i]<<' ';
    else cout<<"-1";
    cout<<'\n';
}

int main()
{
    int t=read();
    while(t--) solve();
    return 0;
}
```

---

## 作者：Dream_poetry (赞：0)

### 思路：
构造题。

首先，我们可以发现，除去最后一次出现外，前几次的出现都不会影响答案。所以，我们只需要针对一个人最后一次进行处理即可。

我们用数组 $vis$ 来存储每一天的人员。

如果有一天没有人是最后一次买彩票，输出 $-1$。

反之，我们按照日期，打印 $vis_i$ 即可。

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int flag;
int t,n,m,a[50010],vis[50010];
inline int read(){
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if (ch=='-') f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
int main(){
	t=read();
	while (t--){
		memset(a,0,sizeof(a));
		memset(vis,0,sizeof(vis));
		m=read();
		for(int i=1;i<=m;i++){
			n=read();
			for(int j=1;j<=n;j++){
				int x;
				x=read();
				a[x]=i;}
		}
		for(int j=1;j<=50000;j++)
			if(a[j])
				vis[a[j]]=j;
		flag=0;
		for(int j=1;j<=m;j++){
			if(!vis[j]){
				flag=1;
				break;
			}
		}
		if(flag)
			puts("-1");
		else{
			for(int j=1;j<=m;j++)
				cout<<vis[j]<<' ';
			puts("");
		}
	}
	return 0;
}
```


---

## 作者：封禁用户 (赞：0)

# CF1798B Three Sevens 题解

## 题目大意

[题面](https://www.luogu.com.cn/problem/CF1798B)。

一共有 $t$ 组数据 $(1 \le t \le 5 \times 10^4)$，每组数据有一个 $m$ 天 $(1 \le m \le 5 \times 10^4)$，每天有 $n$ 个人买彩票 $(1 \le n \le 5 \times 10^4)$。如果一个人中奖，那么他以后就不会再买彩票了。对于每组数据，给出每天中奖的人的编号的序列，如果没有合理的序列就输出 $-1$。

## 思路

可以用 last 存储一个人最后一次买彩票的时间。最后遍历 last 更新答案序列，用 $M$ 记录更新了对少天，如果 $M < m$ 那么久没有合理的答案，输出 $-1$。

## code:

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define il inline
#define re register
#define endl '\n'

const int maxn=50001;
int t,m,n;
int a;
int ans[maxn];
map<int,int>last;

signed main()
{
//	freopen(".in","r",stdin);
//	freopen("CF1798B.out","w",stdout);
	scanf("%lld",&t);
	while(t--)
	{
		memset(ans,0,sizeof ans);
		last.clear();
		int cnt=0;
		scanf("%lld",&m);
		bool flag2=false;
		for(int j=1;j<=m;j++)
		{
			scanf("%lld",&n);
			while(n--)
			{
				scanf("%lld",&a);
				last[a]=j;
			}
		}
		int M=m;
		for(auto i:last)
		{
			if(ans[i.second]==0)
			{
				ans[i.second]=i.first;
				M--;
			}
		}
		if(M>0)
		{
			printf("-1\n");
		}
		else
		{
			for(int i=1;i<=m;i++)
			{
				printf("%lld ",ans[i]);
			}
			printf("\n");
		}
	}
	return 0;
}
```

---

## 作者：UniGravity (赞：0)

## Solution CF1798B Three Sevens

[Luogu传送门](https://www.luogu.com.cn/problem/CF1798B)    
[CF传送门](https://codeforces.com/problemset/problem/1798/B) 

~~一开始看错题以为要每天有且仅有一个人中奖了。。。~~

### 题目分析
发现题目要求选中的人在之后的天里都没有买彩票，那么也就是在他**最后一次买彩票**的时候让他**中奖**。

我们可以用 $lst_i$ 表示编号为 $i$ 的人最后买彩票的时间，再开一个桶 $buy_i$ 记录第 $i$ 天需要买彩票的人。

题目要求每一天都有人中奖，那么我们用 $cnt$ 表示已经有人中奖的天数，当 $cnt<m$ 时就代表有某一天没人中奖，此时输出 $-1$。

由于`Special Judge`的原因，我们无需重复统计所有的 $buy_i$，随意输出一个即可。

发现题目所给的 $n_i,m\le50\space000$，如果直接开数组很可能会爆内存，在这里我们可以使用`unordered_map`替代数组 $lst_i$。（顺便一提，虽然`unordered_map`复杂度高但是好写）

由于时限 $2s$，时间复杂度虽然高一点还是能轻松通过。

### 完整代码

STL大法好！

```cpp
#include <bits/stdc++.h>
using namespace std;

int t, m, n;

unordered_map< int, int > lst; // i号最后买彩票的时间
int a;

int buy[50005]; // 第i天需要买彩票的人
int cnt;

int main() {
    scanf("%d", &t);
    while (t--) {
        lst.clear();
        memset(buy, -1, sizeof(buy));
        scanf("%d", &m);
        for (int i = 1; i <= m; i++) {
            scanf("%d", &n);
            for (int j = 1; j <= n; j++) {
                scanf("%d", &a);
                lst[a] = i;
            }
        }
        
        unordered_map< int, int >::iterator it;
        
        cnt = 0; // 多少天有人中奖
        
        for (it = lst.begin(); it != lst.end(); it++) {
            if (buy[it -> second] == -1) {
                cnt++;
            }
            buy[it -> second] = it -> first;
        }
        
        if (cnt != m) {
            printf("-1\n");
            continue;
        }
        for (int i = 1; i <= m; i++) {
            printf("%d ", buy[i]);
        }
        printf("\n");
    }
    return 0;
}
```

---

## 作者：2021sunzishan (赞：0)

一道简单的模拟题。
## 题目大意：
给定 $m$ 行数，每行数有 $n$ 个。现要从这 $m$ 行数中每一行选一个数，使得这个数在下面几行都没有出现过。

## 思路：

非常简单，模拟就好了。

每次记录每个数最后出现的行，再扫一遍每一行。当这个数是最后一次出现时，那么这一行就选这个数。

注意 $n$ 和 $m$ 取值范围都是 $50000$，开数组会爆，要开 vector。

以上就是本题的思路，如果还是看不懂，那就看代码吧！

**切勿抄袭！！！**

## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int m,s[50005],t,f[50005],ans[50005];
vector<int>a[50005];
inline int read() {//快读 
	int a=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9') {
		if  (c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		a=a*10+(c-'0');
		c=getchar();
	}
	return f*a;
}
int main() {
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	t=read();
	while(t--) {//多组数据
		m=read();
		memset(f,0,sizeof(f));//清空
		for(int i=1; i<=m; i++)a[i].clear();
		for(int i=1; i<=m; i++) {
			s[i]=read();
			for(int j=1; j<=s[i]; j++) {
				int x=read();
				a[i].push_back(x);
				f[x]=i;//记录最后一次出现的行号
			}
		}
		bool f1=0;
		for(int i=1; i<=m; i++) {//扫一遍
			bool k=0;
			for(int j=0; j<s[i]; j++)
				if(f[a[i][j]]==i) {
					k=1;
					ans[i]=a[i][j];//这里注意千万不能直接输出，可能后面找不到了(爆零的教训)
					break;
				}
			if(k==0) {
				f1=1;
				printf("-1");
				break;
			}
		}
		if(f1==0)
			for(int i=1;i<=m;i++)
				printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
```
完结~

---

