# [USACO24JAN] Cannonball B

## 题目描述

Bessie 已经精通了变成炮弹并沿着长度为 $N$（$1\le N\le 10^5$）的数轴弹跳的艺术，数轴上的位置从左到右编号为 $1,2,\cdots,N$。她从某个整数位置 $S$（$1\le S\le N$）开始，以 $1$ 的起始能量向右弹跳。 如果 Bessie 的能量为 $k$，则她将弹跳至距当前位置向前距离 $k$ 处进行下一次弹跳。

从 $1$ 到 $N$ 的每个整数位置上均有炮击目标或跳板。每个炮击目标和跳板都有一个在 $0$ 到 $N$ 范围内的整数值。一个数值为 $v$ 的跳板会使 Bessie 的能量增加 $v$ 并反转她的方向。一个数值为 $v$ 的炮击目标会当着陆时能量不小于 $v$ 时被击破。着陆在炮击目标上不会改变 Bessie 的能量和方向。被击破的炮击目标将保持击破状态，Bessie 依然可以该炮击目标上弹跳，同样不会改变能量和方向。

如果 Bessie 弹跳无限长的时间或直到她离开数轴，她会击破多少个炮击目标？

如果 Bessie 开始时位于一个她可以击破的炮击目标，她会立刻这样做。类似地，如果 Bessie 开始时位于一个跳板，跳板的效果将在她第一次跳跃之前生效。 

## 说明/提示

### 样例解释 1

Bessie 从坐标 $2$ 开始，这是一个数值为 $1$ 的炮击目标，所以她立刻击破了它。然后她弹跳至坐标 $3$，这是一个数值为 $2$ 的炮击目标，所以她无法击破它。她继续弹跳至坐标 $4$，这改变了她的方向并将她的能量增加了 $1$，达到 $2$。她跳回至坐标 $2$，这是一个已经被击破的炮击目标，所以她继续弹跳。此时，她弹跳至了坐标 $0$，因此她停了下来。她击破了恰好一个炮击目标，位于坐标 $2$。

### 样例解释 2

Bessie 经过的路径为 $4\to 5\to 3\to 1\to 6$，下一次弹跳将会使她离开数轴（$11$）。她依次击破了炮击目标 $4,3,6$。

### 测试点性质

 - 测试点 $3-5$：$N\le 100$。
 - 测试点 $6-10$：$N\le 1000$。
 - 测试点 $11-20$：没有额外限制。

## 样例 #1

### 输入

```
5 2
0 1
1 1
1 2
0 1
1 1```

### 输出

```
1```

## 样例 #2

### 输入

```
6 4
0 3
1 1
1 2
1 1
0 1
1 1```

### 输出

```
3```

# 题解

## 作者：Genius_Star (赞：7)

### 思路：

考虑暴力模拟，判环的话就是记 $S_i$ 为第 $i$ 个位置下一步跳到的位置的集合，如果下一步要跳到的位置为 $x$，若 $x \in S_i$，则之前进行过这样的操作，就重复了，退出即可。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
const ll N=100100;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,s,p=1,t=1,ans;
struct Node{
	ll op;
	ll x,f;
}a[N];
set<ll> S[N];
int main(){
	n=read(),s=read();
	for(int i=1;i<=n;i++)
	  a[i]={read(),read(),0};
	while(s>=1&&s<=n){
//		cout<<a[s].f<<'\n';
		if(!a[s].op){
			t*=(-1);
			p+=a[s].x;
		}
		else{
			if(p>=a[s].x&&!a[s].f){
//				cout<<s<<'\n';
				ans++;
				a[s].f=1;
			}
		}
		if(S[s].count(s+p*t))
		  break;
		S[s].insert(s+p*t);
		s+=p*t;
	}
	write(ans);
	return 0;
}

```


---

## 作者：lilong (赞：4)

直接暴力模拟跳的过程，并且判断是否符合条件以及是否出界。不难写出以下程序，可以通过大部分测试点。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long

using namespace std;

int n,nw,p = 1,ti = 1,a[1000001],b[1000001],pd[1000001],ans;

//ti 控制跳跃方向，1 为向右，-1 为向左

signed main()
{
	cin >> n >> nw;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i] >> b[i];
	while( nw >= 1 && nw <= n )
	{
		if( a[nw] )
		{
			if( !pd[nw] && p >= b[nw] ) pd[nw] = 1,ans ++;
		}
		else
		{
			p += b[nw];
			ti *= -1;
		}
		nw += p * ti;
	}
	cout << ans;
	return 0;
}

```
注意到还有一种情况没有考虑，即在区间里无限跳跃。检查方法也十分简单：在目标处检查劲度系数和方向是否改变，若无改变则说明已陷入无限循环，退出即可。加上这部分代码即可 AC。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long

using namespace std;

int n,nw,p = 1,ti = 1,a[1000001],b[1000001],pd[1000001],pp[1000001],tt[1000001],ans;

signed main()
{
	cin >> n >> nw;
	for( int i = 1 ; i <= n ; i ++ )
		cin >> a[i] >> b[i];
	while( nw >= 1 && nw <= n )
	{
		if( a[nw] )
		{
			if( !pd[nw] && p >= b[nw] ) pd[nw] = 1,pp[nw] = p,tt[nw] = ti,ans ++;
			else if( pp[nw] == p && tt[nw] == ti ) break;
		}
		else
		{
			p += b[nw];
			ti *= -1;
		}
		nw += p * ti;
	}
	cout << ans;
	return 0;
}

```


---

## 作者：shaozhehan (赞：3)

[原题链接](https://www.luogu.com.cn/problem/P10132)

建议难度：普及-。

我们直接按照题目暴力模拟 Bessie 每一次的跳动，如果 Bessie 出界就结束跳动。不过，我们发现还有一种特殊的情况没有考虑，例如：Bessie 跳到了一个数值为 $0$ 的垫子上，又反弹到了另一个数值为 $0$ 的垫子上，如此循环往复，永远不能出界。此时，我们可以开两个标记数组 ```vis_power``` 和 ```vis_dir```，第 $i$ 个元素分别表示 Bessie 最后一次弹到此位置时的能量和方向。特殊地，如果 Bessie 没有到过第 $i$ 个位置，则 ```vis_power``` 和 ```vis_dir``` 的第 $i$ 个位置为 $0$。显而易见，如果 Bessie 跳到了位置 $i$ 且 ```vis_power``` 和 ```vis_dir``` 的第 $i$ 个元素分别和 Bessie 的能量和方向相等，则 Bessie 陷入了一个循环，可以停止弹跳。

上代码：
```cpp
#include <iostream>
using namespace std;

bool vis[100001];
int q[100001], v[100001], vis_power[100001], vis_dir[100001];

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);// cin、cout 加速
    int n, s;
    cin >> n >> s;
    for (int i = 1; i <= n; i++){
        cin >> q[i] >> v[i];
    }
    int cur = s, power = 1, direction = 1, cnt = 0;
    while (true){
        if (q[cur] == 0){
            power += v[cur];
            direction = -1 / direction;
        } else {
            if (!vis[cur] && power >= v[cur]){
                cnt++;
                vis[cur] = true;
            }
        }
        if (vis_power[cur] == power && vis_dir[cur] == direction){ // 如果 Bessie 的能量和方向和标记数组中的相同则停止弹跳，退出循环
            break;
        }
        vis_power[cur] = power;
        vis_dir[cur] = direction;
        cur += power * direction;
        if (cur < 1 || cur > n){// 如果越界则停止弹跳
            break;
        }
    }
    cout << cnt << "\n";
    return 0;
}

```

---

## 作者：Iniaugoty (赞：3)

感觉 USACO 经常出这种题，正解就是一个看似不可能过的暴力，但是加了一个决定复杂度的剪枝，简单但很有趣。

暴力跳的做法是平凡的，但是过不去。

我们考虑最坏的情况来分析暴力的复杂度。

想尽可能多的让跳的次数更多，只可能是左右来回反复横跳，即在左右两边放置两个跳板，其余地方是炮击目标。能量越大，跳过一遍的次数就越少，所以我们要让能量增长的幅度尽可能地减小。

当两边的跳板 $v = 0$ 时，这样是会死循环的！所以，我们要加一个剪枝，以所在位置 $ i $，来到这个位置时的方向 $ d $，来到这个位置时的能量 $k$ 作为一个状态三元组 $ (i, d, k) $，丢进一个 `map` 里面打标记。如果当前状态以前已经经过了，就退出。不难证明这个三元组定了接下来发生的事情就都定了，[有一道好题](/problem/P4621)也用了这个思路。

考虑当 $ v = 1 $ 时，要跳的次数大致为 $ \dfrac {n} {1} + \dfrac {n} {2} + \dots + \dfrac {n} {n} $。有一个调和级数的重要结论：不严谨地，$ \dfrac {1} {1} + \dfrac {1} {2} + \dots + \dfrac {1} {n} = O (\log n) $。这意味着暴力跳的次数大致是 $ O (n \log n) $ 级别的。同时，因为有上面的那个剪枝，还要算上 `map` 的 $ \log $，则时间复杂度为 $ O (n \log ^ 2 n) $。

当 $ v > 1$ 时，显然不超过 $ v = 1 $ 的情况。

加了剪枝的暴力做法时间复杂度为 $ O (n \log ^ 2 n) $，空间复杂度 $ O (n \log n) $，可以通过。

实现是简单的。

---

## 作者：_sh1kong_ (赞：2)

[In Luogu](https://www.luogu.com.cn/problem/P10132)

### $\texttt{Solution}$
首先依据题意模拟，很容易可以写出一份暴力。

```cpp
int n, s;

int Ans;

struct node
{
	int q, v;
	//q = 1 jump
	//q = 2 flag
}p[N];

signed main()
{
	I;
	
	cin >> n >> s;
	for (int i = 1; i <= n; i ++ ) cin >> p[i].q >> p[i].v;
	int ener = 1, Dir = 1;
	while (s >= 1 && s <= n)
	{
		if (p[s].q == 1 && ener >= p[s].v)
		{
			++ Ans;
			p[s].q = 2;
		}
		else if (p[s].q == 0)
		{
			ener += p[s].v;
			Dir = -Dir;
		}
		s += (ener * Dir);
	}
	cout << Ans;
}
```

实测会 [TLE](https://www.luogu.com.cn/record/146524073) $5$ 个点。

我们来分析一下原因。

当 Bessie 跳到一个能量为 $0$ 的跳板上，改变方向后又跳到一个能量为 $0$ 的跳板上时，她会无限地跳下去。


容易发现如果出现上述情况，答案不会继续增加。

因为点最多只会有 $10^5$ 个，粗略估计一下，$1s$ 肯定是跳的完的。

所以我们用 $clock$ 判断时间，超过 $1s$ 那就不再操作即可。

是能过的，因为时限给了 $2s$。

放一下优化后的代码。

```cpp
int n, s;

int Ans;

struct node
{
	int q, v;
	//q = 1 jump
	//q = 2 flag
}p[N];

signed main()
{
	clock_t start, end;
	start = clock();
	
	I;
	
	cin >> n >> s;
	for (int i = 1; i <= n; i ++ ) cin >> p[i].q >> p[i].v;
	int ener = 1, Dir = 1;
	while (s >= 1 && s <= n)
	{
		if (p[s].q == 1 && ener >= p[s].v)
		{
			++ Ans;
			p[s].q = 2;
		}
		else if (p[s].q == 0)
		{
			ener += p[s].v;
			Dir = -Dir;
		}
		s += (ener * Dir);
		
		end = clock();
		double n = (double)(end - start) / CLOCKS_PER_SEC;
		if (n > 1) break;
	}
	cout << Ans;
}
```

---

## 作者：newbieTroll (赞：1)

本题只需按题意模拟即可获得 75pts：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct Node{
	bool q;
	int v;
}a[N];
bool h[N];
int main(){
	bool fx=0;
	int n,s,e=1,cnt=0;
	cin>>n>>s;
	for(int i=1;i<=n;++i){
		cin>>a[i].q>>a[i].v;
	}while(1<=s&&s<=n){
		if(a[s].q==0){
			fx=!fx;
			e+=a[s].v;
			if(fx==0){
				s+=e;
			}else{
				s-=e;
			}
		}else{
			if(a[s].v<=e&&!h[s]){
				++cnt;
				h[s]=1;
			}if(fx==0){
				s+=e;
			}else{
				s-=e;
			}
		}
	}cout<<cnt<<endl;
	return 0;
}
```

剩下的 25pts 呢？因为 Bessie 可能会在 2 个跳板内来回跳跃，所以我们可以开一个变量记录 Bessie 移动的次数。如果移动的次数超过一个很大的数（比如 $10^{7}$），就直接退出循环。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
struct Node{
	bool q;
	int v;
}a[N];
bool h[N];
int main(){
	bool fx=0;
	int n,s,e=1,cnt=0,tim=0;
	cin>>n>>s;
	for(int i=1;i<=n;++i){
		cin>>a[i].q>>a[i].v;
	}while(1<=s&&s<=n&&tim<=1e7){
	    ++tim;
		if(a[s].q==0){
			fx=!fx;
			e+=a[s].v;
			if(fx==0){
				s+=e;
			}else{
				s-=e;
			}
		}else{
			if(a[s].v<=e&&!h[s]){
				++cnt;
				h[s]=1;
			}if(fx==0){
				s+=e;
			}else{
				s-=e;
			}
		}
	}cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：_colin1112_ (赞：1)

## 思路

直接暴力地模拟，出界就终止循环即可。

然而，还有一种情况没考虑到：无限的跳，死循环。

这种情况也是十分好做的。这里介绍一种有趣的做法：卡时间。

计算循环所用的时间，当循环时间大于 $0.7$ 秒，直接跳出循环输出答案。于是我们就可以轻松地切掉这道题了。

## Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E = 1e6 + 5;
ll n, s, v, x = 1;
bool flag = 1;
bitset<E> flag1;
int main()
{
    cin >> n >> s;
    vector<pair<ll, ll>> a(n);
    for (auto &v : a)
        cin >> v.first >> v.second;
    ll ans = 0;
    double start = clock();
    while (1)
    {
        // cout << s << " " << x << endl;
        if (a[s - 1].first == 0)
        {
            x += a[s - 1].second;
            if (flag == 1)
                flag = 0;
            else
                flag = 1;
            if (flag == 0)
                s -= x;
            else
                s += x;
        }
        else
        {
            // cout << s << " " << x << endl;
            if (x >= a[s - 1].second && !flag1[s - 1])
                ans++, flag1[s - 1] = true;
            if (flag == 0)
                s -= x;
            else
                s += x;
        }

        double end = clock();
        double tim = (end - start) / CLOCKS_PER_SEC;//计算时间
        if (s < 1 || s > n || tim >= 0.7)//出界或时间来到0.7秒
            break;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：_ImposterX_ (赞：0)

~~非正解，看正解的同学可以跳过（）~~

我们按照题意模拟 Bessie 的所有操作，如果最终可以跳出 $[1,n]$ 这个区间，那么我们直接输出答案即可。但是可能会出现死循环，就是最终无法跳出这个区间，我用的方法是卡时。就是如果我们程序执行的时间即将超出时间限制了，就输出答案并直接结束程序。

具体模拟过程如下：

- 用一个 $fa$ 变量记录方向（向左跳还是向右跳），$fa = 1$ 表示往右跳，$fa = -1$ 表示往左跳。

- 用 $f_i$ 表示如果第 $i$ 个点是目标，那么 $i$ 有没有被击破过。

- 用 $speed$ 记录当前速度。

- 用 $s$ 表示当前坐标。

然后按题意模拟即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;

int n, s;
int q[MAXN], v[MAXN];
bool f[MAXN];
int fa = 1;
int ans = 0;
int speed = 1;

int main() {
	scanf("%d%d", &n, &s);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &q[i], &v[i]);
	}
	while(s <= n && s >= 1) {
//		printf("%d\n", s);
		if(q[s] == 0) {
			speed += v[s];
			if(fa == 1) fa = -1;
			else fa = 1;
			if(fa == 1) s += speed;
			else s -= speed;
		}
		else {
			if(speed >= v[s] && !f[s]) {
				++ans;
				f[s] = true;
			}
			if(fa == 1) s += speed;
			else s -= speed;
		}
		if(clock()*1000>=CLOCKS_PER_SEC*998) cout<<ans,exit(0);
	}
	printf("%d", ans);
	return 0;
}
```

---

## 作者：__Cby___ (赞：0)

作为铜组第二题，本人认为没有第一题难。   
## 解题思路
暴力模拟即可，再加上判环，以免 `Bessie` 反复横跳。   
但本文代码使用的是卡时，因为若你卡时的代码都会输出错误答案，正确的代码肯定会超时的。  
## 代码
```cpp
#include <iostream>
#include <ctime>
#include <set>
using namespace std;
bool q[100025];
long long int v[100025];
int main(){
	long long int n,s;
	cin>>n>>s;
	for(int i=1;i<=n;i++){
		cin>>q[i]>>v[i];
	} 
	long long int now=s;
	bool qh=0;
	long long int ne=1;
	long long int cnt=0;
	while((double)clock()/CLOCKS_PER_SEC<0.9){
		if(q[now]==0)ne+=v[now];
		else if(q[now]==1&&v[now]<=ne){
			cnt++;
			v[now]=212345678987654;
		}
		long long int ar=now;
		if(q[now]==0)qh=!qh;
		if(qh==1)ar-=ne;
		if(qh==0)ar+=ne;
		if(ar<1||ar>n)break;
		now=ar;
	}
	cout<<cnt<<endl;
	return 0;
}
```


---

## 作者：M1saka16I72 (赞：0)

# P10132 [USACO24JAN] Cannonball B 题解

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-usaco-2024-jan.html)

## 题意
给定一个长度为 $N$ 的序列和 Bessie 的起始位置 $S$，Bessie 在初始状态下在序列的 $S$ 处，能量为 $1$，方向向右。

Bessie 每次进行弹跳会向前跳 $k$ 个单位。如果 Bessie 跳到的位置 $i$ 是跳板，Bessie 的能量会增加 $v_i$；如果位置 $i$ 是目标，且 Bessie 的能量大于 $q_i$，则 Bessie 可以击破该目标，否则不能击破。目标不会改变她的方向或能量值。

输出在 Bessie 离开序列范围内或在序列内无限弹跳之前，她能击破多少个目标。
## 思路
按照题意模拟即可。

终止的条件有两种，第一种自然是 Bessie 跳到 $\leq 0$ 或 $\geq N$ 的位置上，第二种则是在跳到同一个目标上时，Bessie 面朝的方向、能量值均相同，会陷入死循环。
## 代码
```cpp
int n,s;
int t[100005],v[100005],tg[100005];
//tg[i]代表如果第i个位置是目标，能否在退出前被击破
map<int,bool> vis[100005];	//判断死循环
int ans = 0;
void search(int p,int x,int d){	//代表当前位置、能量值和方向，向右为1，向左为-1
	int fp = p;	//代表下一次跳到的位置
	if(t[p]){	//如果该点是目标
		if(x>=v[p])	tg[p] = 1;	//可以击破
		if(vis[p][x*d])	return;	//死循环
		vis[p][x*d] = 1;
	}
	else{	//如果该点是跳板
		x+=v[p];	//增加能量
		d = -d;		//改变方向
	}
	fp = p+d*x;
	if(fp<=0 || fp>n)	return;	//越界
	else	search(fp,x,d);	//继续模拟
}
void solve(){
	cin>>n>>s;
	reset(tg,0);
	for(int i=1;i<=n;i++){
		cin>>t[i]>>v[i];
	}
	search(s,1,1);
	for(int i=1;i<=n;i++)	ans+=tg[i];	//统计答案
	cout<<ans;
}
int main(){
	//int t = 1;
	//read(t);
	for(int tt=1;tt<=1;tt++){
		solve();
	}
}
```

---

## 作者：NATO (赞：0)

按题意模拟即可，复杂度 $O(n\log n)$，证明如下：

设当前一次跳 $k$ 个格子

记跳格子数相同的情况为一轮。

每一轮我们最多访问 $\frac{n}{k}$ 个格子后要么到一个跳板，要么就跳出去结束了。

如果跳板增加值不为 $0$，那么一次跳格子数最小增加一；

如果跳板增加值为 $0$，那么跳回去后如果遇到跳板为 $0$ 那么意味着陷入循环，直接结束，否则一次跳格子数最小增加一。

所以最多 $n$ 轮，每轮最多跳 $\frac{2n}{k}$ 次。

那么最坏复杂度即为 $O(\frac{n}{1}+\frac{n}{2}+...+\frac{n}{n})$。

由调和级数可知为 $O(n\log n)$ 的复杂度。

代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 214748364719260817ll
#define db double
using namespace std;
ll n,s;
ll add[100005],mb[100005];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);time(0);
	cin>>n>>s;
	ll opt,v;
	for(ll i=1;i<=n;++i)
	{
	cin>>opt>>v;
	if(opt==0)add[i]=v,mb[i]=-1;
	else mb[i]=v,add[i]=-1;
	}
	ll res=0;
	ll ls=s,f=1,p=1;ll bk=-1;
	if(add[s]!=-1)p+=add[s],bk=add[s],f=-f;
	if(mb[s]!=-1&&mb[s]<=1)++res,mb[s]=-1;
	while(1)
	{
		ll now=ls;now+=f*p;
		bool fp=0;
		for(;now>0&&now<=n;now+=f*p)
		{
			if(add[now]!=-1)
			{
				ls=now;p+=add[now];
				if(bk==0&&add[now]==0)fp=1;
				bk=add[now];
				f=-f;
				break;
			}
			else if(mb[now]<=p&&mb[now]!=-1)++res,mb[now]=-1;
		}
		if(now<=0||now>n||fp)break;
	}
	cout<<res;
}
```

---

## 作者：yyrwlj (赞：0)

## 思路

简单按照题意模拟，向左还是右走就记录偏移量为 $1$ 或 $-1$，移动时让当前坐标加上移动距离乘偏移量。

为了防止出现题目中的死循环，记录一下循环跑了几次，超过一定阈值就算它死循环。

## Code

```cpp
int main()
{
	int ans = 0, op = 1, power = 1, cnt = 0;
	while (1 <= s && s <= n)
	{
		if (++cnt == 10000000)
			break;
		if (q[s] == 0)
		{
			if (op == 1)
				op = -1;
			else
				op = 1;
			power += v[s];
		}
		else if (!st[s] && power >= v[s])
		{
			st[s] = true;
			ans ++;
		}
		s += power * op;
	}
	printf("%d", ans);
}
```

---

## 作者：_O_v_O_ (赞：0)

先考虑没有负数弹跳版的情况，很显然可以暴力，因为复杂度最多 $O(n\log n)$（因为级数求和）。

有负数时要加两个优化：

1. 当打击完所有目标时，直接退出循环；
2. 我们可以用一个数组 $vis_{pos,limit}$ 来记录第一次到达 $pos$，方向 $limit$ 时的速度，若第二次到达 $pos$，方向 $limit$ 时的速度 $=vis_{pos,limit}$ 则也退出循环，因为能打到的目标在之前打过了。

这样有负数弹板的情况复杂度也变成 $O(n\log n)$ 了。

---

## 作者：indream (赞：0)

## P10132 [USACO24JAN] Cannonball B 题解
[USACO](http://usaco.org/index.php?page=viewproblem2&cpid=1372) | [P10132](https://www.luogu.com.cn/problem/P10132)

### 思路
暴力模拟即可，没什么好说的。~~本来我还想优化，但想想上月的 A 我就决定继续打暴力。~~

记得特判死循环。如果上次到这里的能量和方向和这次完全一样，即表明死循环。
### 代码
```cpp
#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
int n,s,sgn=1,k=1,cnt;
//sgn:face(right:1/left:-1);k:energy
struct node{
    int q,v,la;//la:last k
}a[MAXN];
int main(){
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;++i)
        scanf("%d%d",&a[i].q,&a[i].v),a[i].la=-2000000000;
	//cerr<<"Work:\n"<<s<<" 1 1 0\n";
	while(1<=s&&s<=n){
        if(a[s].q==1){
            if(a[s].v<=k){
                ++cnt;
                a[s].q=2;
            }
        }
        else if(a[s].q==0){
            k+=a[s].v;
            sgn*=-1;
        }
        if(a[s].la==sgn*k) break;
        else a[s].la=sgn*k;
        s+=sgn*k;
        //cerr<<s<<' '<<sgn<<' '<<k<<' '<<cnt<<'\n';
    }
    printf("%d",cnt);
    return 0;
}

```


---

## 作者：Mortidesperatslav (赞：0)

中国选手的智慧。（当然没记错的话 USACO 以前也出过这种题。）

看到数据范围还行，很容易写出暴力模拟的代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,pw=1,ans,fx=1;
int op[100005],a[100005],kd[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>x;
	for(int i=1;i<=n;i++)cin>>op[i]>>a[i];
	while(1){
		if(op[x]==1){//目标
			if(!kd[x]&&pw>=a[x]){//摧毁目标
				ans++;
				kd[x]=1;
			}
			x+=pw*fx;
		}else{
			fx=-fx;//跳台
			pw+=a[x];
			x+=pw*fx;
		}
		if(x<1||x>n)break;
	}
	cout<<ans;
}
```

交上去，超时了。

这个时候就是奇技淫巧时间。

有一种做题技巧，叫做卡时，枚举 $70000000$ 次后，如果还在跳，就直接输出答案，退出。

然后就过了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,x,pw=1,ans,fx=1,cs;
int op[100005],a[100005],kd[100005];
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n>>x;
	for(int i=1;i<=n;i++)cin>>op[i]>>a[i];
	while(1){
		cs++;
		if(cs>=70000000)break;//跳太久了，直接输出
        //OI 赛制下用卡时最好估算一下多少次会超时
		if(op[x]==1){
			if(!kd[x]&&pw>=a[x]){
				ans++;
				kd[x]=1;
			}
			x+=pw*fx;
		}else{
			fx=-fx;
			pw+=a[x];
			x+=pw*fx;
		}
		if(x<1||x>n)break;
	}
	cout<<ans;
}
```

---

## 作者：Guizy (赞：0)

直接暴力模拟跳的过程，就是要判断是否死循环。

直接用一个 $cnt$ 记录跳的次数，当 $cnt>10^7$ 就退出。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int Max=100001;
int n,q[Max],v[Max],fx=1;
int now,cnt,ans,jump=1,flag[Max];

int main(){
	
	scanf("%d%d",&n,&now);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&q[i],&v[i]);
	
	while(now>=1&&now<=n){
		cnt++;
		if(cnt>10000000) break;
		if(q[now]==0){
			jump+=v[now];
			fx=(fx==1?-1:1);
		}
		else if(q[now]==1&&!flag[now]&&jump>=v[now]) 
			ans++,flag[now]=1;
		now+=jump*fx;
	}
	printf("%d\n",ans);
	
	return 0;
}
```

---

