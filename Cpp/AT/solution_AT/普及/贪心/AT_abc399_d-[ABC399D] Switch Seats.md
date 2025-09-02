# [ABC399D] Switch Seats

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc399/tasks/abc399_d

$N$ 组数字对（称为“情侣对”）排成一列。  
请统计满足以下所有条件的 **两对不同的情侣对** $(a, b)$ 的组数：

1. 在原序列中，$a$ 的两个出现位置不邻接。
2. 在原序列中，$b$ 的两个出现位置不邻接。
3. 通过执行以下操作（次数不限），可以使 $a$ 的两个出现位置邻接，同时 $b$ 的两个出现位置也邻接：
   - 选择两个位置 $(i, j)$ 满足 $A_i = a$ 且 $A_j = b$，并交换这两个位置的值。

给定一个长度为 $2N$ 的序列 $A = (A_1, A_2, \dots, A_{2N})$，其中每个 $1, 2, \dots, N$ 恰好出现两次。  
对于 $T$ 个测试用例，分别输出答案。

## 说明/提示

### 约束条件

- $1 \leq T \leq 2 \times 10^5$
- $1 \leq N \leq 2 \times 10^5$
- $1 \leq A_i \leq N$
- 每个 $1, 2, \dots, N$ 在 $A$ 中恰好出现两次
- 所有测试用例的 $N$ 总和不超过 $2 \times 10^5$
- 输入值均为整数

### 样例解释 1

考虑第一个测试用例 $(a, b) = (1, 2)$：
- 原序列中 $1$ 的两个出现位置不邻接。
- 原序列中 $2$ 的两个出现位置不邻接。
- 选择 $(i, j) = (1, 6)$ 交换 $A_1$ 和 $A_6$ 后，$1$ 的两个位置邻接，$2$ 的两个位置也邻接。  
因此满足条件的二元组 $(a, b)$ 仅有 $(1, 2)$ 这一组。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
3
3
1 2 3 3 1 2
4
1 1 2 2 3 3 4 4
5
1 2 3 4 5 1 2 3 4 5```

### 输出

```
1
0
4```

# 题解

## 作者：xiaoke2021 (赞：6)

不难。

---

很容易证明的是，若 $(a,b)$ 是一组可行解，我们用 $p_{x,0}$ 和 $p_{x,1}$ 分别表示 $x$ 靠前的一个位置和靠后的一个位置，那么 $\lvert p_{a,0}-p_{b,0} \rvert = 1$ 且 $\lvert p_{a,1}-p_{b,1} \rvert = 1$。当然，$\lvert p_{b,0}-p_{b,1} \rvert \ne 1$ 且 $\lvert p_{a,0}-p_{a,1} \rvert \ne 1$。

那么，将 $i$ 从 $1$ 循环到 $n-1$，对于每个 $A_i$，若 $i = p_{A_i,0}$ 且 $i+1 = p_{A_{i+1},0}$，用上述方法判断 $(A_i,A_{i+1})$ 是否为一组解。这样不会重复计算某一组解。

[Record here.](https://atcoder.jp/contests/abc399/submissions/64312085)

---

## 作者：2012_Zhang_ (赞：5)

做着题时其实认为比较水，但是不知道同机房的人为什么叫苦连天，废话少说，我们步入正题。

## 思路解析
首先我们浅浅的分析一下，注意到题目中有提到，答案里的任何一对情侣刚开始都不能坐在一起。  
那么两对位置能对答案产生贡献，当且仅当其中能凑出两对情侣，且初始都不坐在一起。  
我们要做的就是统计，我们不妨枚举左边的位置，很明显对于一个位置，只有一个对应的位置，我们可以存储第二个数下一次出现的位置。  
接下来进行判断贡献，首先判断是否不相邻，然后判断下次出现时是否与第一个数相邻，如果都满足，答案加一。  
题目分析完毕，接下来是代码实现。

代码奉上：
## AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
const double eps=1e-6;
int n,a[maxn],lst[maxn],t;
signed main(){
	cin>>t;
	while(t--){
		int sum=0;
		cin>>n;
		for(int i=1;i<=2*n;i++){
			cin>>a[i];
			lst[a[i]]=i;
		}
		a[2*n+1]=0;
		for(int i=1;i<2*n;i++){
			if(lst[a[i+1]]<=i+2) continue;
			if(a[lst[a[i+1]]-1]==a[i]||a[lst[a[i+1]]+1]==a[i]) sum++;
		}
		cout<<sum<<endl;
	}
	return 0;
}

---

## 作者：_qumingnan_ (赞：2)

[题目跳楼机](https://www.luogu.com.cn/problem/AT_abc399_d)

# 正文开始

## 阅读理解：

有 $2n$ 个数，其中 $1\sim n$ 搞好出现 $2$ 次。现在求有多少对数本不相邻，但一个数和另外一对数中一个交换后，两队数都相邻。

## 思路：

令一对数为 $x$，另一对为 $y$。

很显然，想要交换后都相邻，那就必须 $x$ 与 $y$ 分别相邻，于是就可以存下每个数第一次出现的位置，然后看 $l_{a_i}$ 与 $l_{a_{i-1}}$ 是否相邻即可。

注：如 $l_{a_i}$ 与 $i$ 相邻，或 $l_{a_{i-1}}$ 与 $i$ 相邻时也不合法。

## 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
int T;
int n;
int a[400005],t[400005],ans;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n;
		for(int i=1;i<=2*n;i++){
			cin>>a[i];
			if(!t[a[i]])t[a[i]]=i;//存第一次出现的位置。 
		}
		for(int i=2;i<=2*n;i++){
			int x=t[a[i]],y=t[a[i-1]];//a[i] 第一次出现的位置与 a[i-1] 第一次出现的位置。 
			if(abs(i-x)<=1||abs(i-1-y)<=1||abs(x-y)!=1)continue;//如果相邻，或者 x 与 y 不相邻，那就不合法。 
			ans++;
		}
		cout<<ans<<'\n';
		for(int i=1;i<=2*n;i++)t[a[i]]=0;
		ans=0;
		//多测不清空，爆 0 两行泪 
	}	
	return 0;
}
```

---

## 作者：Clover_Lin (赞：2)

## 博客
[在博客内阅读效果更佳，欢迎查看！](https://blog.csdn.net/ArmeriaLeap/article/details/146715138)

## 题目大意
请点击 [这里](https://atcoder.jp/contests/abc399/tasks/abc399_d) 查看原题面。

有一个长度为 $2\cdot N$ 的序列 $A$，其中 $1,2,\dots,N$ 各出现了两次。现在要找满足如下条件的数对 $(a,b)$ 的个数：
- $a$ 的两次出现不相邻。
- $b$ 的两次出现不相邻。
- 交换一个 $a$ 和一个 $b$ 的位置任意多次之后，可以使两个 $a$ 和 两个 $b$ 相邻。

有多测，且 $1\le N\le 2\cdot 10^5$。
## 思路
$N$ 的值很大，对于每组数据，我们需要一个时间复杂度为 $O(N)$，总时间复杂度 $O(\sum_1^T N)$。考虑只枚举二元组中的一个数，通过计算得到第二个数并验证。为了更高效、更方便，我们不妨记录一下 $1$ 到 $N$ 在数组中两次出现的位置。实际上，直接开两个数组就可以维护，我使用了 `vector`，一个动态数组，虽然浪费空间，但是代码难度不高。

我们可以发现，如果想要满足第三条要求，那么 $a$ 和 $b$ 需要满足以下条件：
- $a$ 的第一次出现位置和 $b$ 的第一次出现位置相邻。
- $a$ 的第二次出现位置和 $b$ 的第二次出现位置相邻。

我们需要规定一个“限制”或者“顺序”来避免重复统计。每次只统计第一次出现在 $a$ 后面且相邻的 $b$，然后判断第二次是否相邻。但是还有一个小细节：当数据中出现形容 `1 2 1 2` 的时候，程序遍历到 $1$，统计了一次，然后遍历到 $2$，又会统计一次。但这是错误的，因为这相当于是调用了两次 $1$ 的第二个位置。所以我们要小心这个问题。
## 代码
```cpp
// 评测记录：https://atcoder.jp/contests/abc399/submissions/64303061
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int t, n, a[400010]; // 注意数组大小
vector<int> p[200010]; // p 记录位置

bool check(int x, int y) // 判断两个位置是否相邻
{
	return abs(x - y) == 1;
}

int main()
{
	cin >> t;
	while (t--)
	{
		cin >> n;
		for (int i = 1; i <= n; i++)
			p[i].clear(); // 多测初始化
		for (int i = 1; i <= n * 2; i++)
		{
			cin >> a[i];
			p[a[i]].push_back(i);
		}
		long long ans = 0;
		for (int i = 1; i <= n; i++)
		{
			if (check(p[i][0], p[i][1]))
				continue; // 两个 a 相邻
			int j = a[p[i][0] + 1];
			if (p[j][0] != p[i][0] + 1)
				continue; // 细节处理
			if (check(p[j][0], p[j][1]))
				continue; // 两个 b 相邻
			if (check(p[i][1], p[j][1]))
				ans++; // 第二次出现的位置相邻就统计答案
		}
		cout << ans << endl;
	}
	return 0;
}
```
## 总结
这道题难度不大，个人感觉是 $\color{gold}普及/提高-$ 左右。最后，希望这篇题解对你有帮助，如有想法欢迎评论或私信提出！

---

## 作者：_Weslie_ (赞：1)

笑点解析：$413$ 机房生物还是太超前了，一对情侣有四个人。

## Solution AT_abc399_d

### Idea

考虑两个相邻的整数对：$(a_{i-1},a_i)$。原因是假如我们考虑不相邻的两对，根据题目的交换规则也没用。

然后我们要把另一个 $a_{i-1}$ 换到 $i$ 的位置。那么我们需要预处理出上一个 $a_{i-1}$ 的位置。有人或许会问：假如这是第一个 $a_{i-1}$ 怎么办？第一个 $a_{i-1}$ 我们把上一个的位置设为 $0$，直接判掉。

我们设上一个 $a_{i-1}$ 位置为 $x$。那么假如 $x$ 的相邻两个位置有 $a_{i}$，把 $a_{i}$ 换到位置 $x$ 之后就可以满足条件，反之不能。

注意：假如 $x=i-2$，那么要排除，因为 $a_{i-1}$ 的一对已经相邻。

### Code

```
#include<bits/stdc++.h>
using namespace std;
const int N=400005;
int lst[N],a[N],pre[N];
int n;
void soilve(){
    scanf("%d",&n);n<<=1;
    memset(pre,0,sizeof pre);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        lst[i]=pre[a[i]];pre[a[i]]=i;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        int x=lst[i-1];
        if(x==0)continue;
        if(x==i-2)continue;
        if(a[x+1]==a[i]||a[x-1]==a[i])ans++;
    }
    printf("%d\n",ans);
}
int main(){
    int T;scanf("%d",&T);while(T--)soilve();
}
```

---

## 作者：coding_goat (赞：1)

[可能更好的阅读体验](https://www.cnblogs.com/CodingGoat/p/18800213)

一个二元组 $(a,b)$ 满足条件，当且仅当序列中没有相邻的 $a$ 或 $b$ 元素时，有两对相邻的不重复的无序对 $(a,b)$ 。

所以我们只需要检查该元素两边的元素是否能构成一个二元组就好了。

我们记录序列中 $(a_i,a_{i-1})$ 出现的次数。对于答案统计，我们分类讨论：

- 当 $a_{i-1}=a_{i+1}$ 时，至少有 $(a_{i-1},a_{i})>1$ 或者是 $(a_i,a_{i-1})>1$ 才满足要求。

- 其他情况只需要加起来大于等于 $2$ 即可。

时间复杂度 $O(n\log n)$，用 `map<pair<int,int>,int>` 常数较大，但是 AtCoder 机子快，能过。

```cpp
#include<bits/stdc++.h>

#define pii pair<int,int> 
#define pll pair<long long,long long> 
#define ll long long
#define i128 __int128

#define mem(a,b) memset((a),(b),sizeof(a))
#define m0(a) memset((a),0,sizeof(a))
#define m1(a) memset(a,-1,sizeof(a))
#define lb(x) ((x)&-(x))
#define lc(x) ((x)<<1)
#define rc(x) (((x)<<1)|1)
#define pb(G,x) (G).push_back((x))
#define For(a,b,c) for(int a=(b);a<=(c);a++)
#define Rep(a,b,c) for(int a=(b);a>=(c);a--)
#define in1(a) a=read()
#define in2(a,b) a=read(), b=read()
#define in3(a,b,c) a=read(), b=read(), c=read()
#define in4(a,b,c,d) a=read(), b=read(), c=read(), d=read()
#define fst first 
#define scd second 
#define dbg puts("IAKIOI")

using namespace std;

int read() {
	int x=0,f=1; char c=getchar();
	for(;c<'0'||c>'9';c=getchar()) f=(c=='-'?-1:1); 
	for(;c<='9'&&c>='0';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x*f;
}
void write(int x) { if(x>=10) write(x/10); putchar('0'+x%10); }

const int mod = 998244353;
int qpo(int a,int b) {int res=1; for(;b;b>>=1,a=(a*a)%mod) if(b&1) res=res*a%mod; return res; }
int inv(int a) {return qpo(a,mod-2); }

#define maxn 400050

int n,a[maxn];
bool vis[maxn];
int t_cnt[maxn];
ll ans=0;

void work() {
	ans=0;
	map<pii,int> mp,flg; mp.clear(),flg.clear();
	in1(n);
	For(i,1,n+n) {
		in1(a[i]);
		if(a[i-1]==a[i]) vis[a[i]]=1;
	}
	For(i,2,n+n) if(!vis[a[i-1]]&&!vis[a[i]]) mp[{a[i],a[i-1]}]++;
	For(i,2,n+n-1) if(a[i-1]==a[i+1]) flg[{a[i-1],a[i]}]=1;
	For(i,2,n+n) if(!vis[a[i]]&&!vis[a[i-1]]) {
		if(flg[{a[i-1],a[i]}]||flg[{a[i],a[i-1]}]) {
			if(mp[{a[i],a[i-1]}]>1||mp[{a[i-1],a[i]}]>1) {
				ans++,mp[{a[i],a[i-1]}]=0,mp[{a[i-1],a[i]}]=0;
	//			dbg;
//				cout<<a[i]<<' '<<a[i-1]<<'\n';
			}		
		} else {
			if(mp[{a[i],a[i-1]}]+mp[{a[i-1],a[i]}]>=2) {
				ans++,mp[{a[i],a[i-1]}]=0,mp[{a[i-1],a[i]}]=0;
			//	cout<<a[i]<<' '<<a[i-1]<<'\n';
			}		
		}		
	}
	cout<<ans<<'\n';
	For(i,1,n+n) vis[i]=0;
}

signed main() {
//	freopen("data.in","r",stdin);
//	freopen("myans.out","w",stdout);
//	ios::sync_with_stdio(false); 
//	cin.tie(0); cout.tie(0);
	double stt=clock();
	int _=1;
	_=read();
//	cin>>_;
	For(i,1,_) {
		work();
	}
	cerr<<"\nTotal Time is:"<<(clock()-stt)*1.0/1000<<" second(s)."<<'\n';
	return 0;
}
/*
1
4
1 2 3 2 4 3 4 1

*/
```

---

## 作者：daitangchen2008 (赞：1)

## 解法
显然的，本题中每个数出现且仅出现两次，于是在排除了同一个数字相邻情况之后，只需统计满足两次出现且都相邻的数对 $(i,j)$ 的个数。  
所以此题我们只需要从后往前扫，判断出现次数大于等于二的 $(i,j)$ 即可。  
但特别的，会有 1221 和 121……2 两种特殊情况，需要注意。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=4e5+10;
int a[N];
map<pair<int,int>,int>mp;
signed main()
{
	int T,n;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n;
		int ans=0;
		n=n*2;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		int lx,ly;
		lx=ly=0;
		for(int i=2;i<=n;i++)
		{
			if(a[i]==a[i-1])
				continue;
			int x=a[i];
			int y=a[i-1];
			if(x<y)
			 swap(x,y);
			if(x==lx&&y==ly)
			{
				lx=ly=0;
				continue;
			}
			lx=x;
			ly=y;
			mp[make_pair(x,y)]++;
			if(mp[make_pair(x,y)]==2)
				ans++;
		}
		cout<<ans<<endl;
		for(int i=2;i<=n;i++)
		{
			int x=a[i];
			int y=a[i-1];
			if(x<y)
			swap(x,y);
			mp[make_pair(x,y)]=0;
		}
	}
	return 0;
}
```

---

## 作者：Yannik (赞：1)

## 题目大意：
有一个长度为 $2n$ 的序列 $A$，其中每个数字 $1$ 到 $n$ 恰好出现两次。我们需要统计满足以下条件的数字对 $a,b$ 的数量。

- 初始不相邻：数字 $a$ 的两个位置不相邻，数字 $b$ 的两个位置也不相邻。

- 交换后都相邻：通过交换 $1$ 对 $a$ 和 $b$，可以使得 $a$ 的两个位置相邻，且 $b$ 的两个位置也相邻。这种操作可以进行任意次。

## 分析：
模拟可得交换 $1$ 对 $a$ 和 $b$ 这个操作最多进行 $1$ 次。所以要满足数字对可以是以下情况：
- $[a...b...a...b]$
- $[a...b...b...a]$ 且两个 $b$ 不能相邻。

可以用一个数组 $p$ 记录第一次第二次出现位置。再用一个数组记录可能通过交换的 $a$ 的位置。最后用一个 ```set``` 查看能不能变换。

## 赛时代码：
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<numeric>
#include<vector>
#include<queue>
#include<map>
#include<set>
#include<stack>
#include<random>
#define int long long 
#define PII pair<int,int>
using namespace std;
const int N = 1e6 + 10,inf= 2e18,mod = 1e9 + 7;
int T,n,m,a[N];
signed main(){
    cin.tie(0)->ios::sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=2*n;i++){
            cin>>a[i];
        }
        int p[n+1][2]={0};
        for(int i=1;i<=2*n;i++){
            if(!p[a[i]][0]){
                p[a[i]][0]=i;
            } else {
                p[a[i]][1]=i;
            }
        }
        int cnt=0;
        vector<int> v1,v2;
        for(int i=1;i<=n;i++){
            int x=p[i][0],y=p[i][1];
            if(y-x>1){
                v1.push_back(x);
                v2.push_back(y);
            }
        }
        set<PII> s;
        for(int i=0;i<v1.size();i++){
            s.insert(make_pair(v1[i],v2[i]));
        }
        int ans=0;
        for(int i=0;i<v1.size();i++){
            int x=v1[i],y=v2[i];
            int nx=x+1,ny=y+1,px=x+1,py=y-1;
             if(s.count(make_pair(nx,ny))){
                ans++;
            }
             if(s.count(make_pair(px,py))&&py-px>1){
                ans++;
            }
        }
        cout<<ans<<"\n";
    }
}
```

---

## 作者：zyn0309 (赞：1)

# [ABC399D] Switch Seats
[题目传送门](https://atcoder.jp/contests/abc399/tasks/abc399_d)
## 思路
判断每一个数 $x$ 和它右边的数 $y$ 能否配对，用数组存储每一个位置对应的另一个相等的数字位置，称作 $nxt_x$。如果 $x$ 与 $nxt_x$ 不相邻，$y$ 与 $nxt_y$ 不相邻且 $nxt_x$ 与 $nxt_y$ 相邻就将答案加一。因为每一对会被统计两次所以要将答案除以二。
## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii  pair<int,int> 
#define mk make_pair
using namespace std;
const int N=5e5+10;
int n,cnt,a[N],pos[N][2];
inline int nxt(int x){
	if(pos[a[x]][0]==x)return pos[a[x]][1];
	else return pos[a[x]][0];
}
inline bool ok(int x){
	return abs(nxt(x)-x)==1;
}
inline void solve(){
	cin>>n;
	cnt=0;
	for(int i=1;i<=n;++i)pos[i][0]=-1;
	for(int i=0;i<2*n;++i){
	  cin>>a[i];
	  if(pos[a[i]][0]==-1)pos[a[i]][0]=i;
	  else pos[a[i]][1]=i;
	}
	for(int i=0;i<2*n-1;++i)if(!ok(i)&&!ok(i+1)&&abs(nxt(i)-nxt(i+1))==1)++cnt;
	cout<<cnt/2<<"\n";
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	int T;
	cin>>T;
	while(T--)solve();
	return 0;
}
```

---

## 作者：Gilbert1206 (赞：1)

## AT_abc399_d [ABC399D] Switch Seats题解
[洛谷传送门](https://www.luogu.com.cn/problem/AT_abc399_d)

## 思路 and 方法
这道题其实输入 $2 \times n$ 个数字，每个数字在 $2 \times n$ 必定出现 $2$ 次。现在我们只能交换 $1$ 次，使出现 $2$ 对相同的数字紧挨在一起（本就挨在一起的不能算入）。

做法其实类似于贪心，我们只需要每次找到一个与之前所有都不相同的就记录一下它当前所属的下标，当再次遇到它的时候就开始作比较，看两个的旁边是否是相同且注意交换的两个数字挨在一起没有。

## AC CODE


```cpp
#include <bits/stdc++.h>
using namespace std;
int a[450000],t[450000],vis[450000];
int main(){
	int u;
	cin>>u;
	for(int i=0;i<u;i++){
		int n;
		cin>>n;
		a[n*2]=-1e8;//因为后面的要使用a[i+1],所以在此先做标记成-1e8
        //标准输入
		for(int i=0;i<n*2;i++){
			cin>>a[i];
			t[a[i]]=0;//用memset(t,0,sizeof(t))会TLE
		}
		int ans=0;
		for(int i=0;i<n*2;i++){
			if(t[a[i]]==0){
				t[a[i]]=i;
			}//记录之前都没有出现过的数字的下标
			else{
				if((a[t[a[i]]-1]==a[i+1]&&i-t[a[i]]!=1&&i+1-(t[a[i]]-1)!=1)||(a[t[a[i]]-1]==a[i-1]&&i-t[a[i]]!=1&&i-1-(t[a[i]]-1)!=1)){
					ans++;
				}//之前出现过的开始查找是否交换后可以组成2对紧挨在一起的。（同时看是否本就挨在一起）
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}

```

---

## 作者：xy_mc (赞：0)

### 正解：

首先我们要明白一点，既然 $A_i=a$，$A_j=b$，那么移动一次和移动多次实际上是一样的，只要移动一次，就可以使两个 $a$ 相邻，两个 $b$ 相邻，也就只有以下这两种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/snokudpz.png)

明白了这一点，其他的就很简单了。记录每个数出现的位置。令 $a=A_i$，$b=A_{i+1}$，题里要求两个 $a$ 和 $b$ 原来不相邻，所以判断一下，也就是若相邻就不用管了。否则把四个位置放进一个数组里，对其进行排序，判断是否符合上面的两种情况，是的话就把 $(a,b)$ 塞进一个 set 里面。最后输出大小就行了。总之后面就是按照题意模拟。

注意数组要开两倍大小，每次都要清空！！！

### code:

```cpp
#include<bits/stdc++.h>
#define inl inline
#define pii pair<int,int>
#define rep(i,x,y) for(int i=x;i<=(y);++i)
#define per(i,x,y) for(int i=x;i>=(y);--i)
#define fst ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
typedef long long ll;
using namespace std;
const int INF=INT_MAX;
const int N=2e5+10;
inl int sf(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
int t,n,a[N*2];
vector<int> pos[N];
int main(){
	fst;
	t=sf();
	while(t--){
		n=sf();
		rep(i,1,n) vector<int>().swap(pos[i]);
		rep(i,1,2*n){
			a[i]=sf();
			pos[a[i]].push_back(i);
		}
		set<pii> s;
		rep(i,1,2*n-1){
			int x=a[i],y=a[i+1];
			if(pos[x][0]+1==pos[x][1]||pos[y][0]+1==pos[y][1]) continue;
			int v[4]={pos[x][0],pos[x][1],pos[y][0],pos[y][1]};
			sort(v,v+4);
			if(v[0]+1==v[1]&&v[2]+1==v[3]) s.insert({min(x,y),max(x,y)});
		}
		cout<<s.size()<<"\n";
	}
	return 0;
}
```

---

## 作者：haokee (赞：0)

访问 [Haokee Note](https://haokee-note.org/%E9%A2%98%E8%A7%A3/AtCoder/ABC399D+Switch+Seats) 以获得更好的体验。

## 思路

首先，由于 $N$ 最大有 $2\times 10^5$，很显然我们不能通过枚举 $(a,b)$ 的方式进行处理，因为这种方式的时间复杂度至少为 $\mathcal O(n^2)$，因此我们需要更换枚举的方式。

对样例进行观察，很显然可以发现满足的数对 $(a,b)$ 当中，$a$ 和 $b$ 在原数组当中对应的位置都是相邻的。例如 $a=1,b=2$ 且满足条件，则可能是这样：

```cpp
…… 1 2 …… 1 2 ……
```

或者

```cpp
…… 2 1 …… 2 1 ……
```

还可以

```cpp
…… 2 1 …… 1 2 ……
```

即 $1$ 和 $2$ 都是相邻的。需要注意的是这种不行

```cpp
…… 1 2 2 1 ……
```

因为不能有相同的元素相邻。

结合上面的结论，我们就可以很简单地优化枚举方式了。由于有两对 $(a,b)$ 在原数组的位置是相邻的，因此我们只需要枚举相邻的元素，然后看一看是否符合条件就行了。我这里使用 vector 存储每个元素的两个位置。时间复杂度 $\mathcal O(n)$。

## 代码

```cpp
#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 1e6 + 5;

int a[kMaxN], t, n, ans;
vector<int> v[kMaxN];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  for (cin >> t; t; t--) {
    // 读入和初始化
    cin >> n;
    fill(v + 1, v + n + 1, vector<int>());
    ans = 0;
    for (int i = 1; i <= 2 * n; i++) {
      cin >> a[i];
      v[a[i]].push_back(i);
    }

    // 处理
    for (int i = 1; i < 2 * n; i++) {
      if (a[i] != a[i + 1] && 
          abs(v[a[i]][0] - v[a[i]][1]) != 1 && 
          abs(v[a[i + 1]][0] - v[a[i + 1]][1]) != 1) {  // 要求相同的数不相邻，不相同的数相邻
        int x, y;  // 另外两个 (a,b) 的位置
        if (i == v[a[i]][0])  {
          x = v[a[i]][1];
        } else {
          x = v[a[i]][0];
        }
        if (i + 1 == v[a[i + 1]][0]) {
          y = v[a[i + 1]][1];
        } else {
          y = v[a[i + 1]][0];
        }
        if (abs(x - y) == 1) {  // 另外的也要相邻
          ans++;
        }
      }
    }
    cout << ans / 2 << '\n';  // 注意除以 2，因为这里一个 (a,b) 会枚举两次
  }
  return 0;
}
```

---

## 作者：include13_fAKe (赞：0)

昨晚发现咋我们班没人切这题，还被学弟薄纱了，想在 vp 的时候做出来，结果被特殊情况卡了。

## 题意

题面已经很清晰了，略。

## 思路

~~咋算法标签标的贪心~~，看到这题就可以往用 struct 维护上去想了。

具体来讲，对 $i\in[1,n)$ 的每一个 $i$ 维护 $\min(a_i,a_{i+1})$ 和 $\max(a_i,a_{i+1})$ 的值。然后以 $\min(a_i,a_{i+1})$ 为第一关键字，$\max(a_i,a_{i+1})$ 为第二关键字排序。

提交，发现不对，考虑以下情况：


```cpp
3
2 1 3 2 3 1
```

此时 $i=3$ 时维护的值为 $(2,3)$，$i=4$ 时维护的值也是 $(2,3)$，但是，不能把两个为 $2$ 的数 $a_1$ 和 $a_3$ 在仅使用数 $2$ 和数 $3$ 的情况下凑在一起。

考虑在排序前加入第三关键字：**排序前** 的位置 $i$，若两个二元组相等，还必须满足位置 $i$ 的间距 $\ge 1$ 才能累计答案。

这仍然是错的，考虑以下特殊情况：


```cpp
2
1 2 1 2
```

此时三个位置维护的值分别为 $\left \{ 1,2,1 \right \} $、$\left \{ 1,2,2 \right \} $ 和 $\left \{ 1,2,3 \right \} $。

考虑在 check 到 $\left \{ 1,2,2 \right \} $ 时将 $\left \{ 1,2,2 \right \} $ 也改成 $\left \{ 1,2,1 \right \} $。**不重新排序**，继续 check $\left \{ 1,2,3 \right \} $。容易证明，维护的前两关键字相同的值 **最多出现三次**。

然后就 AC 了，时间复杂度 $O(\sum n)$。

感觉自己的处理方式没有任何优点。

## 代码


```cpp
#include<bits/stdc++.h>
using namespace std;

int n;
struct node{
	int x,y,z;
}pair1[5*114514];
bool cmp(node a,node b){
	if(a.x!=b.x)	return a.x<b.x;
	if(a.y!=b.y)	return a.y<b.y;
	return a.z<b.z;
}
int a[5*114514];
int b[5*114514];
int ptr=0;
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
		b[i]=0;
	}
	ptr=0;
	for(int i=1;i<=2*n;i++){
		cin>>a[i];
		if(i!=1&&a[i]!=a[i-1]){
			pair1[++ptr].x=min(a[i],a[i-1]),pair1[ptr].y=max(a[i],a[i-1]),pair1[ptr].z=i;
			if(a[i]==a[i-1])	b[a[i]]=1;
		}
		if(a[i]==a[i-1])	b[a[i]]=1;
	}
	sort(pair1+1,pair1+ptr+1,cmp);
	int include13=0;
	for(int i=1;i<ptr;i++){
		if(pair1[i].x==pair1[i+1].x&&pair1[i].y==pair1[i+1].y&&abs(pair1[i].z-pair1[i+1].z)!=1&&(!b[pair1[i].x])&&(!b[pair1[i].y])&&(!b[pair1[i+1].x])&&(!b[pair1[i+1].y])){
			include13++;
		}
		else if(pair1[i].x==pair1[i+1].x&&pair1[i].y==pair1[i+1].y&&abs(pair1[i].z-pair1[i+1].z)==1&&(!b[pair1[i].x])&&(!b[pair1[i].y])&&(!b[pair1[i+1].x])&&(!b[pair1[i+1].y])){
			pair1[i+1].z--;
		}
	}
	for(int i=1;i<=ptr;i++){
//		cout<<pair1[i].x<<' '<<pair1[i].y<<' '<<pair1[i].z<<endl;
	}
	cout<<include13<<endl;
	return;
}
int T;
signed main(){
	cin>>T;
	while(T--)	solve();
	return 0;
}//ABC399D 
```

不知道为什么这码量能够有 1.2KB。

---

## 作者：I_Like_Play_Genshin (赞：0)

## Solution

我们首先可以记录 $f_i$ 为值为 $i$ 的数是否相邻。

然后用一个 map 套 pair 来记录 $mp_{(i, j)}$ 为值为 $i, j$ 的数是否已经相邻。

只要发现两次 $(i, j)$ 相邻，就可以算作答案加一。

注意，如果发现两次相邻有共点，那么则不算相邻。

在这里给一个 Hack。

```
2
3
1 2 1 3 3 2
2
1 2 1 2
```

```
0
1
```

## Code

[Code](https://atcoder.jp/contests/abc399/submissions/64317688)

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定长为 $2N$ 的序列 $A$，其中 $1\sim N$ 每个数都出现两次，问整数对 $(a,b)$ 的数量，满足 $1\le a<b\le N$，同时 $a$ 和 $b$ 出现两次的位置分别不相邻，并且任意交换这四个数后，可满足 $a,b$ 出现两次的位置分别相邻，数据范围 $N\le 2\times 10^5$，数据组数为 $T$。

## 解题思路

下面用 $x_1,x_2$ 表示出现两次的 $x$，其中 $x_1$ 下标小于 $x_2$ 的下标。不难想到，最终要满足 $a,b$ 出现两次的位置分别相邻，也就是让交换后的状态为 $\cdots,a_1,a_2,\cdots,b_1,b_2,\cdots$。那么就可以通过这个状态来任意交换，从而得到交换前的原始状态，同时还要满足 $a_1,a_2$ 和 $b_1,b_2$ 分别不相邻，那么只有两种可能：$\cdots,a_1,b_1,\cdots,a_2,b_2,\cdots$ 或 $\cdots,a_1,b_1,\cdots,b_2,a_2,\cdots$（这里要注意，我一开始打的时候没读题，只考虑了第一种情况，于是就有了

![](https://cdn.luogu.com.cn/upload/image_hosting/x6gh0woq.png)，

应该不会有人跟我一样没读题吧）。

于是就可以先记录一下每个数字 $1\sim N$ 两次出现的位置，然后按上面两种情况讨论即可。需要注意的是，第二种情况需要满足 $b_1,b_2$ 不相邻，不然就会 $\textcolor{#E74C3C}{\text{WA}\times 8}$，时间复杂度 $O(TN)$。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
#define R register
using namespace std;
#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x << " = " << x, endl
#endif

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    static ll sta[41]; ll top=0;
    if(x<0) putchar('-'), x=-x;
    do sta[top++]=x%10, x/=10; while(x);
    while(top) putchar(sta[--top]+48);
}

ll t,n,a[400001],p[200001][2],x,ans;

int main()
{
	t=read();
	
	while(t--)
	{
		n=read(); ans=0;
		
		for(R int i=1; i<=n<<1; ++i)
		{
			a[i]=read();
			if(p[a[i]][0]) p[a[i]][1]=i;
			else p[a[i]][0]=i;
		}
		
		for(R int i=1; i<n-1<<1; ++i)
		{
			if(p[a[i]][0]==i && p[a[i+1]][0]==i+1 &&
			p[a[i]][0]+1<p[a[i]][1] && p[a[i+1]][0]+1<p[a[i+1]][1] && 
			abs(p[a[i]][1]-p[a[i+1]][1])<2) ++ans;
		}
		
		for(R int i=1; i<=n; ++i)
		p[i][0]=0, p[i][1]=0;
		write(ans); endl;
	}
	
    return 0;
}
```

---

## 作者：Tairitempest (赞：0)

## [ABC399D] Switch Seats

关键点在于：
- $a$ 的位置在 $i$ 和 $j$，$b$ 在 $i+1$（或 $i-1$）和 $j+1$（或 $j-1$）。
- $a$ 的两个位置不相邻，$b$ 同理。
- 这时候交换，就能让这两对小情侣贴贴！

考虑记录每个数字的两个先后出现的位置，然后遍历数组，找相邻元素可能的候选对，将相邻的元素对存入集合去重，并保证 $x>y$。不过要跳过连续相同的情况！找到候选对以后检查候选对的四个位置是否满足：两个数靠前的位置相邻，且两个数靠后的位置也相邻。如果满足条件就计数。

本题多测记得清空。时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,a[400010],p1[200010],p2[200010],ans;
set< array<ll,2> > cp;
int main(){
	ll t;
	cin>>t;
	while(t--){
		cp.clear();
		ans=0;
		cin>>n;
		for(int i=1;i<=2*n;i++) cin>>a[i];
		for(int i=1;i<=2*n;i++){
			if(p1[a[i]]==0) p1[a[i]]=i;
			else p2[a[i]]=i;
		}
		for(int i=1;i<2*n;i++){
			if(i>1&&a[i]==a[i-1]) continue;
			if(a[i]==a[i+1]) continue;
			if(i+1<2*n&&a[i+1]==a[i+2]) continue;
			ll x=a[i],y=a[i+1];
			if(x<y) swap(x,y);
			cp.insert({x,y});
		}
		for(auto i=cp.begin();i!=cp.end();i++){
			ll x=(*i)[0],y=(*i)[1];
			if(abs(p1[x]-p1[y])==1&&abs(p2[x]-p2[y])==1) ans++;
		}
		cout<<ans<<endl;
		for(int i=1;i<=n;i++) p1[i]=p2[i]=0;
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：0)

突破口在于看出答案是 $O(n)$ 的。

枚举夫妇 $a$，假设夫妇 $a$ 的位置是 $x,y$。夫妇 $b$ 位置只有可能是 $(x-1,y-1),(x-1,y+1),(x+1,y-1),(x+1,y+1)$ 这四种，判一下无解。

注意去重的细节。

```cpp
#define il inline
int n,a[N],p[N][2]; set<tuple<int,int,int,int>> st;
il void chk(int x,int y,int s,int t) {
	if(!s||t==n*2+1) return; if(s>t) swap(s,t);
	if(abs(s-t)>1&&a[s]==a[t]&&a[s]>a[x]) st.insert({x,y,s,t});
}
void QwQ() {
	n=rd(),st.clear();
	for(int i=1;i<=n;i++) p[i][0]=p[i][1]=0;
	for(int i=1;i<=n*2;i++) a[i]=rd(),p[a[i]][!!p[a[i]][0]]=i;
	for(int i=1,x,y;i<=n;i++) {
		x=p[i][0],y=p[i][1];
		if(y-x==1) continue;
		chk(x,y,x-1,y-1),chk(x,y,x-1,y+1),chk(x,y,x+1,y-1),chk(x,y,x+1,y+1);
	}
	wr(st.size(),"\n");
}
```

---

## 作者：Emplace (赞：0)

## 思路
### 性质
我们可以发现，只有相邻两个数满足条件，且不能相等，并且两个数都不能与旁边的数相等。它们对应的数也是这样。
### 做法
记录每个数出现的两次位置。然后对于每个数，只需要求它的另外一个数与它下一个数的另外一个数即可，然后按照性质判断即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[500000],cnt,t1[500000],t2[500000];
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=2*n;i++) t1[i]=0,t2[i]=0;
		for(int i=1;i<=2*n;i++){
			cin>>a[i];
			if(!t1[a[i]]) t1[a[i]]=i;
			else t2[a[i]]=i;
		}
		cnt=0;
		for(int i=1;i<=2*n-1;i++){
			int j,k;
			if(t1[a[i]]==i) j=t2[a[i]];
			else j=t1[a[i]];
			if(t1[a[i+1]]==i+1) k=t2[a[i+1]];
			else k=t1[a[i+1]];
			if(abs(k-j)==1&&abs(j-i)>1&&abs(k-i-1)>1){
				cnt++;
			}
		}
		cout<<cnt/2<<endl;
	}
	return 0;
}

```

---

## 作者：SuyctidohanQ (赞：0)

### 思路分析

UPD：添加了代码。

这是一道有点复杂的题。思路会了，代码写寄了。

我们可以用一个数组来存储每个位置的值。

```cpp
rep(i, 1, n) pos[i].x = i, pos[i].y = j;
```

在确认数字的两个出现位置后，我们必须检查这两个位置**是否相邻**。

接下来我们要判断是否可以通过**交换**使得 $a$ 和 $b$ 的两个数都可以相邻。

对于数字 $a$，它的两个位置 $x_1$ 和 $y_1$，对于数字 $b$，它的两个位置 $x_2$ 和 $y_2$，如果出现了**相邻的**，那么满足条件。

### 代码实现

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = a; i <= b; i ++)
using namespace std;
int T, n;
signed main () {
    cin >> T;
    
    while (T --) {
    	cin >> n;
    	vector <int> v (2 * n + 1);
    	vector <pair <int,int> > vp (n + 1);
    	rep(j, 1, 2 * n) {
    		cin >> v[j];
    		if (vp[v[j]].first != 0) vp[v[j]].second =j;
    		else vp[v[j]].first = j;
		}
		int sum = 0;
		rep(j, 1, 2 * n - 1) {
			int a = v[j], b = v[j + 1];
			if (vp[a].first + 1 == vp[a].second || vp[b].first + 1 == vp[b].second) continue;
			if (vp[b].first != j + 1) continue;
			if (a != b) {
				if (vp[a].first == j) {
					bool flag = false, flag2 = false;
					if (vp[b].second < 2 * n) 
						if (vp[b].second + 1 == vp[a].second) flag = true;
					
					if (vp[b].second - 1 == vp[a].second) flag = true;
					if (vp[a].second < 2 * n) 
						if (vp[a].second + 1 == vp[b].second) flag2 = true;
					if (vp[a].second - 1 == vp[b].second) flag2 = true;
					if (flag2 == true && flag == true) sum ++;
				}
			}
		}
		cout << sum << endl;
		
	}
	return 0;
}

```

---

## 作者：FXLIR (赞：0)

### 思路
为方便叙述，分别称两个满足条件的 $a$ 为 $a_1,a_2$，两个满足条件的 $b$ 为 $b_1,b_2$，且 $a_1$ 在 $a_2$ 之前，$b_1$ 在 $b_2$ 之前。

我们发现，若一次交换之后 $a_1$ 与 $a_2$ 相邻，$b_1$ 与 $b_2$ 相邻，则交换前 $a_1$ 必定与 $b_1$ 相邻，$a_2$ 必定与 $b_2$ 相邻。

即，四个数可能的排列情况有如下四种（忽略其它的数字）：

- $a_1,b_1,a_2,b_2$
- $b_1,a_1,a_2,b_2$
- $a_1,b_1,b_2,a_2$
- $b_1,a_1,b_2,a_2$

其中第 $1$ 种与第 $4$ 种，第 $2$ 种与第 $3$ 种本质上是相同的，也就是说实质上只有 $a_1,b_1,a_2,b_2$ 和 $b_1,a_1,a_2,b_2$ 两种。

那么，是不是将所有以上这两种可能的情况都找出来就好了呢？

并不是。题目中还给出了一个限制条件——交换以前，$a_1$ 和 $a_2$ 不相邻，$b_1$ 和 $b_2$ 不相邻。

对于 $a_1,b_1,a_2,b_2$ 这种情况来说，这个条件无关紧要，因为 $a \ne b$；但对于 $b_1,a_1,a_2,b_2$ 这种情况来说，如果 $a_1$ 和 $a_2$ 之间没有其它的数，那这一组就不能算了——因为违反了交换前不相邻的条件。

所以，在找第二种可能的时候，还需要判断一下 $a_1$ 和 $a_2$ 之间有没有其它的数。

可以通过用数组记录每个数每一次出现的位置，来在线性时间内找出所有的 $(a,b)$。具体实现参见代码，我在代码中给出了相关的注释。
### 代码
```
#include<map>
#include<iostream>
#define int long long
using namespace std;
const int N=4e5+5,INF=1e9;
int t,n,a[N],ans,s[3][N];
/*
s[1][i] 表示数 i 第一次出现的位置
s[2][i] 表示数 i 第二次出现的位置
*/
signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--){
		ans=0;
		cin>>n;
		for(int i=1;i<=2*n;i++){
			cin>>a[i];
			s[1][a[i]]=s[2][a[i]]=0;
			//清空
		}
		for(int i=1;i<=2*n;i++){
			s[(s[1][a[i]]!=0?2:1)][a[i]]=i;//标记
		}
		for(int i=1;i<2*n;i++){
			if(s[1][a[i]]==i){//如果 a[i] 是第一次出现，则判断，这么写是为了防止重复
				ans+=(s[2][a[i]]+1==s[2][a[i+1]]&&s[2][a[i]]>i||s[2][a[i+1]]+1==s[2][a[i]]&&s[2][a[i+1]]>i+2);
				/*
				设 a[i] 为 a，a[i+1] 为 b，则 a[i],a[i+1] 为 a1,b1
				若 a2 和 b2 的排列顺序是 a2,b2（第一种情况）
				或者排列顺序是 b2,a2 且 b1 和 b2 之间有别的数（即 b2 和 a1 之间有至少两个数），则答案+1
				*/
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Terminal_P (赞：0)

# D. Switch Seats
## 【题意简述】
给定一个长度为 $2N$ 的正整数序列 $A$。其中 $[1, N]$ 的每个整数都出现了 $2$ 次。    
对于一个整数对 $(x, y)$，其满足条件当且仅当：
 - 在 $A$ 中 $x, y$ 的 $2$ 次出现不相邻。
 - 可以执行下列操作任意次，使在 $A$ 中 $x, y$ 的 $2$ 次出现均相邻：
   - 挑选两个正整数 $i, j(1 \le i \le 2N, j \le j \le 2N)$，使得 $A_i = x$ 且 $A_j = y$，并交换 $A_i$ 和 $A_j$ 的位置。

求满足上述条件的整数对的个数。    
本题单个测试点内有 $T$ 组测试样例。    
$1 \le T \le 2 \times 10^5, 1 \le N \le 2 \times 10^5, 1 \le A_i \le N, 1 \le \sum N \le 2 \times 10^5$。
## 【思路分析】
显然对于每个整数对，执行操作仅需 $1$ 次，多次操作是无意义的。    
令 $pos_{i, 0 \sim 1}$ 为值为 $i$ 的元素在序列 $A$ 中两次出现的位置。    
注意到满足条件的整数对 $(x, y)$ 都有以下性质：    
 - $pos_{x, 0} + 1 \not = pos_{x, 1}$。（$x$ 的两次出现不相邻）
 - $pos_{y, 0} + 1 \not = pos_{y, 1}$。（$y$ 的两次出现不相邻）
 - 令序列 $V \gets \{pos_{x, 0}, pos_{x, 1}, pos_{y, 0}, pos_{y, 1}\}$。给 $V$ 升序排序后有 $V_1 + 1 = V_2, V_3 + 1 = V_4$。

 答案可使用`std::set<pair<int, int>>`存储、去重。    
需要注意的是，此处的数列 $A$ 需要开两倍空间（$4 \times 10 ^ 5$）。
## 【AC Code】
```C++
/*
书本试卷堆积的角落里
找到没贴邮票泛黄的信
不禁幻想回到那个雨季
说出 反复练习 却没说的话语
—— 鸽稀拉 《回信》

In the corner where books and test papers are piled up
Found a yellowed letter without a stamp
I can't help but fantasize about returning to that rainy season
"Saying words that have been repeatedly practiced but not spoken"
- Reply (by Gexila)
*/
#include <bits/stdc++.h>
#define endl "\n"
#define int long long
using namespace std;
const int N = 2e5 + 5;
vector<int> pos[N];
int T;
int n;
int a[N << 1];

void init() {
  for (int i = 1; i <= n; i++) {
    pos[i].clear();
  }
}
void func() {
  cin >> n;
  init();
  set<pair<int, int>> ans;
  for (int i = 1; i <= 2 * n; i++) {
    cin >> a[i];
    pos[a[i]].push_back(i);
  }
  for (int i = 1; i < 2 * n; i++) {
    int &x = a[i], &y = a[i + 1];
    if (pos[x][0] + 1 == pos[x][1] || pos[y][0] + 1 == pos[y][1]) {
      continue;
    }
    vector<int> tmp = {pos[x][0], pos[x][1], pos[y][0], pos[y][1]};
    sort(tmp.begin(), tmp.end());
    if (tmp[0] + 1 == tmp[1] && tmp[2] + 1 == tmp[3]) {
      ans.insert({min(x, y), max(x, y)});
    }
  }
  cout << ans.size() << endl;
}
signed main() {
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> T;
  while (T--) {
    func();
  }
  return 0;
}
/*
By Terminal_P  >_P
Copyright 2025. All Rights Reserved.
Luogu: Terminal_P
Bilibili: Terminal_P
Netease Music: Terminal_P
QQ ID: 2705680938
QQ Group ID: 945817959
Nice to meet you.
*/
```
[AC记录 Submission #64364959](https://atcoder.jp/contests/abc399/submissions/64364959)

---

## 作者：Tjaweiof (赞：0)

# AT_abc399_d 题解
[题目传送门](https://www.luogu.com.cn/problem/AT_abc399_d)

对于每一个数，记录与其对应的两个位置，那么 `ans++` 当且仅当这两个位置的旁边都有一个相同的数。为了防止重复计算，只考虑第一个位置后的那个数，判断第二个位置旁边是否有这个数。

然后注意一些小细节即可。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define FILE(x) freopen(x".in", "r", stdin);freopen(x".out", "w", stdout);
int t, n, a[400005], p1[200005], p2[200005], ans;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> t;
	while (t--){
		ans = 0;
		cin >> n;
		for (int i = 1; i <= n; i++){
			p1[i] = 0;
			p2[i] = 0;
		}
		a[n << 1 | 1] = 0;
		for (int i = 1; i <= (n << 1); i++){
			cin >> a[i];
			if (p1[a[i]]){
				p2[a[i]] = i;
			} else {
				p1[a[i]] = i;
			}
		}
		for (int i = 1; i <= n; i++){
			if (p1[i] + 1 != p2[i] && p2[i] != (n << 1)){
				ans += a[p1[i] + 1] == a[p2[i] + 1];
			}
			if (p1[i] + 1 != p2[i] && p1[i] + 2 != p2[i] && p1[i] + 3 != p2[i]){
				ans += a[p1[i] + 1] == a[p2[i] - 1];
			}
		}
		cout << ans << "\n";
	}
	return 0;
}

```

---

## 作者：I_am_kunzi (赞：0)

# AT_abc399_d 题解

### 题目翻译

给定 $ t $ 组数据，每组数据有以下格式：

> 给定 $ n $ 和 $ 2n $ 个数，记为 $ A_1 \sim A_{2n}$，其中 $ A $ 数组满足 $ 1 \sim n $ 每个数各出现两次。你需要找到满足以下条件的数对 $ (a , b) $ 的个数：
>
> 1. $ 1 \le a < b \le n$；
> 2. 在 $ A $ 数组中，值为 $ a $ 的两位置不相邻；
> 3. 在 $ A $ 数组中，值为 $ b $ 的两位置不相邻；
> 4. 只交换值为 $ a $ 或 $ b $ 的这四个位置的值，可以使得值为 $ a $ 的两位置相邻，且值为 $ b $ 的两位置相邻。
>
> 输出满足条件的 $ (a , b) $ 数对的个数。

### 题目思路

容易发现，每个数都只会出现两次，所以我们可以将每个数出现的两个位置存下来，这里记 $ i $ 出现的两个位置分别为 $ p_{i , 1} $ 和 $ p_{i , 2}$，在代码中表述为 ``` p[i].first ``` 和 ```p[i].second```。

还容易发现，要求交换完的两对数两两相邻，且只能交换这两对数的四个位置，则必须在交换之前这四个位置就需要两两相邻，且相邻两位置的数字不相同。

所以，我们可以枚举一个 $ i$，然后判断 $ a_i $ 和 $ a_{i + 1} $ 这两个数是否满足题意。而判断过程可以分为以下几个步骤：

1. 找出 $ p_{a_i , 1} , p_{a_i , 2} , p_{a_{i + 1} , 1} , p_{a_{i + 1} , 2} $ 这四个位置，也就是 $ a_i $ 和 $ a_{i + 1} $ 这两个数出现的位置；

2. 判断 $ p_{a_i , 1} , p_{a_i , 2} $ 之间是否相邻，即 $ p_{a_i , 1} + 1 = p_{a_i , 2} $ 是否成立（当然移项可得多种判断方法）；

3. 同理判断 $ p_{a_{i + 1} , 1} , p_{a_{i + 1} , 2} $ 是否相邻；

4. 把四个位置排序，判断是否两两相邻（排序后第一、二个位置和第三、四个位置）；

5. 如果排序后两两相邻，即 $ (a_i , a_{i + 1}) $ 这一对数对合法（当然可以通过取最小值和最大值满足题目中第一条要求），就放到一个 ``` map < pair < int , int > , bool > ``` 中统计答案。

容易发现，这样统计一定不会漏掉任何一组相邻的位置，也不用担心 $ a_i = a_{i + 1}$，因为这时候 $ p_{a_i , 1} + 1 = p_{a_i , 2} $ 一定成立。

这样就有了一份正确解法。

### 代码

[因为洛谷 RMJ 可能坏了，所以这里只有 AtCoder 的提交记录。](https://atcoder.jp/contests/abc399/submissions/64354715)

这里也放一份代码（去缺省源）。

```cpp
pair < int , int > p[200005]; // p[i] 表示 a[x] = i 的 x 的值
int a[400005];
map < pair < int , int > , bool > m; // map 防止重复统计答案
bool check(int A , int B , int C , int D) // 判断 A , B , C , D 四个位置是否满足题意
{
	int b[6] = {0 , A , B , C , D};
	sort(b + 1 , b + 5);
	return (b[2] - b[1] == 1 && b[4] - b[3] == 1); 
}
void solve()
{
	int n;
	read(n);
	m.clear();
	for(int i = 1 ; i <= n * 2 ; i++)
	{
		read(a[i]);
		if(!p[a[i]].first)
		{
			p[a[i]].first = i;
		}
		else
		{
			p[a[i]].second = i;
		}
	}
	int cnt = 0;
	for(int i = 1 ; i < n * 2 ; i++) // 因为交换后要求相邻，所以只需要统计交换前相邻两位置的答案
	{
		int x = a[i] , y = a[i + 1];
		if(p[x].second == p[x].first + 1)
		{
			continue;
		}
		if(p[y].second == p[y].first + 1)
		{
			continue;
		}
		if(check(p[x].first , p[x].second , p[y].first , p[y].second))
		{
			cnt += !m[make_pair(min(x , y) , max(x , y))];
			m[make_pair(min(x , y) , max(x , y))] = 1;
		}
	}
	for(int i = 1 ; i <= n ; i++) // 注意清空
	{
		p[i].first = p[i].second = 0;
	}
	printnl(cnt);
}
signed main()
{
	int t;
	read(t);
	while(t--)
	{
		solve();
	}
	return 0;
}
```

---

