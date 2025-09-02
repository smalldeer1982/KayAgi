# Level Statistics

## 题目描述

Polycarp has recently created a new level in this cool new game Berlio Maker 85 and uploaded it online. Now players from all over the world can try his level.

All levels in this game have two stats to them: the number of plays and the number of clears. So when a player attempts the level, the number of plays increases by $ 1 $ . If he manages to finish the level successfully then the number of clears increases by $ 1 $ as well. Note that both of the statistics update at the same time (so if the player finishes the level successfully then the number of plays will increase at the same time as the number of clears).

Polycarp is very excited about his level, so he keeps peeking at the stats to know how hard his level turns out to be.

So he peeked at the stats $ n $ times and wrote down $ n $ pairs of integers — $ (p_1, c_1), (p_2, c_2), \dots, (p_n, c_n) $ , where $ p_i $ is the number of plays at the $ i $ -th moment of time and $ c_i $ is the number of clears at the same moment of time. The stats are given in chronological order (i.e. the order of given pairs is exactly the same as Polycarp has written down).

Between two consecutive moments of time Polycarp peeked at the stats many players (but possibly zero) could attempt the level.

Finally, Polycarp wonders if he hasn't messed up any records and all the pairs are correct. If there could exist such a sequence of plays (and clears, respectively) that the stats were exactly as Polycarp has written down, then he considers his records correct.

Help him to check the correctness of his records.

For your convenience you have to answer multiple independent test cases.

## 说明/提示

In the first test case at the third moment of time the number of clears increased but the number of plays did not, that couldn't have happened.

The second test case is a nice example of a Super Expert level.

In the third test case the number of plays decreased, which is impossible.

The fourth test case is probably an auto level with a single jump over the spike.

In the fifth test case the number of clears decreased, which is also impossible.

Nobody wanted to play the sixth test case; Polycarp's mom attempted it to make him feel better, however, she couldn't clear it.

## 样例 #1

### 输入

```
6
3
0 0
1 1
1 2
2
1 0
1000 3
4
10 1
15 2
10 2
15 2
1
765 432
2
4 4
4 3
5
0 0
1 0
1 0
1 0
1 0```

### 输出

```
NO
YES
NO
YES
NO
YES```

# 题解

## 作者：lingfunny (赞：3)

# 题目翻译
统计一个游戏的数据，第$i$次有两个数$p_i$表示游玩次数，$c_i$表示通关次数。现在会统计$n$次（按时间顺序），问这个统计是不是错误的。
# 题目分析
简单模拟。
1. 通关次数不可能大于游玩次数；
2. 游玩次数和通关次数不可能减少（因为是按照时间顺序统计的）；
3. 未通关次数不可能变少（同理是因为时间顺序）。

三条规则，三个```if```解决。

有个需要注意的点就是，发现错误不能立刻输出```NO```，要等它输入完所有数据，否则输入数据就会交叉在一起。可以用打标记的方法。

具体怎么判断可以看代码。
# 实现代码
```cpp
#include <iostream>
using namespace std;
int t,n;
int lp,lw,np,nw;		//lp 上次游玩,lw 上次通关,np 这次游玩,nw 这次通关
int flag;
#define wa flag=0;		//宏定义，代码中出现wa即代表把标记置为假
int main(){
	cin>>t;
	while(t--){
		cin>>n;
		lp=lw=np=nw=0;	//初始化
		flag=1;			//先假设这个数据没问题
		cin>>lp>>lw;	//因为n>=1，所以可以先输入第一组
		if(lp<lw)wa		//详见分析第1条
		for(int i=1;i<n;++i){
			cin>>np>>nw;
			if(nw>np)wa	//分析第1条
			if(np<lp || nw<lw)wa	//分析第2条
			if(lp-lw > np-nw)wa		//分析第三条
			lp=np;
			lw=nw;					//不要忘记更新！
		}
		if(flag)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：___cjy__ (赞：2)

# CF1334A Level Statistics 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1334A)

[更好的阅读体验](https://www.luogu.com.cn/blog/chengjiayi666/solution-cf1334a)

### 题目大意：

按时间顺序统计 $n$ 次，每次统计两个数 $p_i$ 和 $c_i$，分别表示这个游戏的游玩次数和通关次数。问这个统计是否合法。

### 正文：

正难则反，我们可以判断这个统计是否是错误的。对于每一种统计，可以考虑如下三种性质：

1. 本次游玩次数小于上一次游玩次数或本次通关次数小于上一次通关次数。即 $p_i \lt p_{i-1}$ 或 $c_i \lt c_{i-1}$。

1. 游玩次数小于通关次数。即 $p_i \lt c_i$。

1. 本次增加的游玩次数小于本次增加的通关次数。即 $p_i-p_{i-1} \lt c_i-c_{i-1}$。

### AC Code：

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>
#include<cmath>
#define int long long
#define N 105
#define INF 0xffffffff
#define bug printf("..........bug!..........\n");
using namespace std;
int T, n, c[N], p[N];
signed main(){
	scanf("%lld", &T);
	while(T--){
		scanf("%lld", &n);
		bool f = 0;
		for(int i=1; i<=n; i++){
			scanf("%lld %lld", &p[i], &c[i]);//游玩和通关次数
			if(p[i] < p[i - 1] || c[i] < c[i - 1]) f = 1;
			if(p[i] < c[i]) f = 1;
			if(labs(p[i] - p[i - 1]) < labs(c[i] - c[i - 1])) f = 1;
		}
		if(f) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
```

---

## 作者：gyh20 (赞：2)

嘤语太差 WA 了两次。/dk

简要题意：

有一个游戏，在某一个时刻总共有 $p_i$ 次尝试和 $c_i$ 次成功，问是否合法。输入按时间顺序给出。

其实是一个小小的判断。

首先，如果 $p_i<p_{i-1}$ 或 $c_i<c_{i-1}$ 就一定是 NO，因为无论怎样都不能变少。

如果 $p_i-p_{i-1}<c_i-c_{i-1}$，那么说明通关的人比玩的人还多，肯定不合法。

```cpp
#include<bits/stdc++.h>
#define re register
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
int t,n,m,a[100002],b[100002];
signed main(){
	t=read();
	while(t--){
		n=read();re long long suma=0,sumb=0;
		bool ia=1;
		for(re int i=1;i<=n;++i){
			a[i]=read();b[i]=read();
			if(a[i]<a[i-1]||b[i]<b[i-1])ia=0;
			if(b[i]-b[i-1]>a[i]-a[i-1])ia=0;
		}
		if(ia)puts("YES");
		else puts("NO");
	}
}
```


---

## 作者：Warriors_Cat (赞：2)

### $Description:$

给你 $n$ 个时间点，每个时间点的 $p_i$ 和 $c_i$ 分别表示参加的比赛数和通过的比赛数，保证**按时间升序**输入，问这种排列合不合法。

### $Solution:$

首先，$p_i$ 一定要 $\ge c_i$，因为参加数肯定要超过通过数嘛！

其次，对于两个相邻的时间间隔，它的参加数和通过数肯定不能小于 $0$，也就是：$p_i \ge p_{i-1}$ 且 $c_i \ge c_{i-1}$。

最后，$p_i - p_{i-1}$ 一定要 $\ge c_i - c_{i-1}$，原理同第一种情况。

综合以上情况，这道题就被我们做出来啦-v-。

下面放代码：

### $Code:$

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int t, n, p[10010], c[10010];
int main(){
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) scanf("%d%d", p + i, c + i);
		bool flag = 1;
		if(p[1] < c[1]) flag = 0;
		for(int i = 2; i <= n; ++i){
			int x = p[i] - p[i - 1], y = c[i] - c[i - 1];//先算出来
			if(x < 0 || y < 0 || x < y || p[i] < c[i]){
				flag = 0;
				break;
			}//如上所述
		}
		if(flag) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
} 

```


---

## 作者：CodingOIer (赞：1)

## CF1334A Level Statistics 题解

### 思路分析

有 $4$ 种情况会导致记录有问题。

- $c_i < c_{i - 1}$，即本次记录的游戏次数比上一次少。
- $p_i < p_{i - 1}$，即本次记录的胜利次数比上一次少。
- $c_i < p_{i - 1}$，即本次记录的游戏次数比本次记录的胜利次数少。
- $c_i - c_{i-1} < p_i - p_{i-1}$，即本次记录比上一次增加的游戏次数比增加的胜利次数少。

这些情况便输出 `NO`。

### 代码实现

注：在输入的时候不能直接处理，因为输出 `NO` 结束循环后会有剩余的数据没有输入，导致和后面的数据混在一起。

```cpp
#include <bits/stdc++.h>
const int MaxN = 1e2 + 5;
int t;
int n;
int c[MaxN], p[MaxN];
void solve()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d", &c[i], &p[i]);
    }
    for (int i = 1; i <= n; i++)
    {
        if (c[i] < c[i - 1] || p[i] < p[i - 1] || c[i] < p[i] || c[i] - c[i - 1] < p[i] - p[i - 1])
        {
            printf("NO\n");
            return;
        }
    }
    printf("YES\n");
}
int main()
{
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        solve();
    }
    return 0;
}
```

---

## 作者：PersistentLife (赞：1)

### 题意简述

第一行输入一个整数 $T$，表示有多少个游戏记录。

对于每个游戏记录，先给定一行一个整数 $n$，表示玩了几局。

对于每一局，输入一行两个整数，用空格隔开，表示当前**累计**玩的局数和赢的局数，**不是新增**。

如果记录无误输出 `YES`，否则输出 `NO`。

### 题目分析

~~大家都玩过游戏吧？~~

玩过游戏的人都知道，以下几种情况不会出现。

- 赢的局数不会比总共玩的局数多；

- 赢的局数和总共玩的局数不会减少；

- 失败的局数也不会减少。

那么三个 `if` 就搞定了。

### 代码实现

```
#include<bits/stdc++.h>
using namespace std;
int T,N,lstc,lstp,tisc,tisp;
//分别表示：多少个游戏记录 玩了多少局 上一次玩的局数 上一次赢的局数 这一次玩的局数 这一次赢的局数
bool flag;
void ChuShiHua()//初始化
{
	lstc=lstp=tisc=tisp=0;
	flag=1;
}
void GengXin()//更新局数
{
	lstc=tisc;
	lstp=tisp;
}
int main()
{
	cin>>T;
	while(T--)
	{
		cin>>N;
		ChuShiHua();
		while(N--)//这里发现不符合要求不能直接退出，因为这样会打乱输入，所以采用打标记法
		{
			cin>>tisc>>tisp;
			if(tisp>tisc) flag=0;//第一条
			if(tisc<lstc||tisp<lstp) flag=0;//第二条
			if(lstc-lstp>tisc-tisp) flag=0;//第三条
			GengXin();
		}
		if(flag) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	}
	return 0;
}
```


---

## 作者：TainityAnle (赞：0)

[CF1334A](https://www.luogu.com.cn/problem/CF1334A)

[在我的洛谷博客中查看](https://www.luogu.com.cn/blog/550317/solution-cf1334a)

橙题，但是是红题难度。模拟。

- $t$ 个玩家，就是很普通的多组输入，注意清空数组和变量。

- 考虑有多少种的可能是可以的，但是要看每一次都正常，所以直接考虑不可能的即可。

1. 正常人的逻辑来讲，游玩次数一定不大于通关次数。也就是说，对于所有的错误情况，存在某一 $i$，满足 $c_i>p_i$

2. 由于游戏记录是按照时间顺序给出的，所以通关次数或游戏次数不可能比上一次小。也就是说，对于所有的错误情况，存在某一 $i$，满足 $p_{i-1}>p_i$ 或 $c_{i-1}>c_i$ 其中任意一条。

3. 这是最容易忽略的一点，即本次增加的通关次数不可能大于增加的总次数。对于所有的错误情况，存在某一 $i$，满足 $c_i-c_{i-1}>p_i-p_{i-1}$

- 一个变量标记，如果不合规就设为 $1$，否则就是 $0$，**注意清空**。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long T,n,c[105],p[105],flag;
int main() {
	cin>>T;
	while(T--) {
		cin>>n;
		flag=0;
		for(int i=1; i<=n; i++) {
			cin>>p[i]>>c[i];
			if(p[i]<p[i-1]||c[i]<c[i-1]) flag=1;
			if(p[i]<c[i]) flag=1;
			if(labs(p[i]-p[i-1])<labs(c[i]-c[i-1])) flag=1;
		}
		if(flag) cout<<"NO\n";
		else cout<<"YES\n";
	}
	return 0;
}

```

---

## 作者：AutumnKite (赞：0)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

初始状态为 $p_0=0,c_0=0$。

由于每进行一次游戏，$p$ 一定会加 $1$，而 $c$ 可能加 $1$ 也有可能不变，所以 $p$ 增加的值一定大于等于 $c$ 增加的值，并且他们增加的值必须非负。

所以只要判断是否所有 $i$ 都满足 $p_{i-1} \le p_i,c_{i-1} \le c_i,p_i-p_{i-1}\ge c_{i}-c_{i-1}$ 即可。

### 代码

```cpp
int n;

void solve() {
	read(n);
	int x = 0, y = 0;
	bool flag = true;
	for (int i = 1; i <= n; ++i) {
		int nx, ny;
		read(nx), read(ny);
		if (nx < x || ny < y) {
			flag = false;
		}
		if (nx - x < ny - y) {
			flag = false;
		}
		x = nx, y = ny;
	}
	if (flag) {
		printStr("YES");
	} else {
		printStr("NO");
	}
}
```

---

## 作者：寒鸽儿 (赞：0)

判定状态是否合法 ,  首先初始状态中 $p_0 \geqslant c_0$ ，然后在增量中 , $p$ 的增量大于 $c$ 的增量 , 即 $p_i - p_{i-1} \geqslant c_i - c_{i-1} , i \in [1, n-1]$ 。  

```cpp
#include <bits/stdc++.h>
#define endl '\n'
#define rep(i,a,b) for(int i=a;i<=(b);++i)
#define per(i,a,b) for(int i=a;i>=(b);--i)
#define repp(i,a,b) for(int i=a;i<(b);++i)
#define perr(i,a,b) for(int i=a;i>(b);--i)
#define pb push_back
#define rz resize
#define VI vector<int>
#define VL vector<long long>
#define VD vector<double>

using namespace std;

typedef long long ll;

const int inf = 0x3f3f3f3f;
const ll linf = 0x3f3f3f3f3f3f3f3f;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tests;
	cin>>tests;
	while(tests--) {
		int n, p, c, pi, ci;
		bool flg = true;
		cin>>n;
		--n;
		cin >> p >> c;
		if(p < c) flg = false;
		while(n--) {
			cin >> pi >> ci;
			if(pi < p || ci < c || pi - p < ci - c || pi < ci) flg = false;
			p = pi; c = ci;
		}
		if(flg) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}

```

---

