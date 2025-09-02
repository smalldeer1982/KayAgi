# Required Length

## 题目描述

You are given two integer numbers, $ n $ and $ x $ . You may perform several operations with the integer $ x $ .

Each operation you perform is the following one: choose any digit $ y $ that occurs in the decimal representation of $ x $ at least once, and replace $ x $ by $ x \cdot y $ .

You want to make the length of decimal representation of $ x $ (without leading zeroes) equal to $ n $ . What is the minimum number of operations required to do that?

## 说明/提示

In the second example, the following sequence of operations achieves the goal:

1. multiply $ x $ by $ 2 $ , so $ x = 2 \cdot 2 = 4 $ ;
2. multiply $ x $ by $ 4 $ , so $ x = 4 \cdot 4 = 16 $ ;
3. multiply $ x $ by $ 6 $ , so $ x = 16 \cdot 6 = 96 $ ;
4. multiply $ x $ by $ 9 $ , so $ x = 96 \cdot 9 = 864 $ .

## 样例 #1

### 输入

```
2 1```

### 输出

```
-1```

## 样例 #2

### 输入

```
3 2```

### 输出

```
4```

## 样例 #3

### 输入

```
13 42```

### 输出

```
12```

# 题解

## 作者：litachloveyou (赞：21)

一开始很容易想到用深搜去写这个题，但是没有优化的深搜连第三个样例都过不去。**这个时候我们可以考虑一下剪枝策略。**

------------
##### 贪心
首先我们考虑试一下贪心，从第一个样例不难得出，能影响数位的只有2~9，0和1是没有办法影响数位的，所以我们从9开始往下去乘，把每一次更新的答案记录，如果当前次数超过答案了就返回。**这样仍然还是超时。**
##### 贪心+最优情况剪枝
仔细思考一下，其实每一次最多就能够使得数位+1，**那么如果题目要求的数位减去当前数位加上已用的次数大于等于当前答案**，就可以返回了。**因为你现在的数位在每一次都+1位的情况下都没有现在的答案更优，就不用继续了。**
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
ll n,y;
ll ans=1e18+10;
bool que=false;
ll leg(ll x)//计算数位
{
	ll cnt=0;
	while(x)
	{
		cnt++;
		x=x/10;
	}
	return cnt;
}
void bfs(ll x,ll c)
{
	if(n+c-leg(x)>=ans)return;//最优情况剪枝
	if(leg(x)==n)
	{
		ans=c;//更新答案
		que=true;
		return;
	}
	vector<int>a(10);
	ll k=x;
	while(k)
	{
		a[k%10]++;
		k=k/10;
	}
	for(int i=9;i>1;i--)//从9开始
	{
		if(a[i]>=1)
		{
			bfs(x*i,c+1);
		}
	}
}
int main()
{
	scanf("%lld%lld",&n,&y);
	bfs(y,0);
	if(!que)printf("-1");
	else
	{
		printf("%lld",ans);
	}
	return 0;
}
```


---

## 作者：dbxxx (赞：4)

[您可在我的博客中查看，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/cf1681d.html)

注意到，选用 $0$ 或 $1$ 这两种数位相乘的操作是没有任何用处的，所以下面的操作直接过滤掉这两种情况。

设 $N = 10^n$。每次操作后的结果一定可以分解为 $x \times 2^\alpha \times 3^\beta \times 5^\gamma \times 7^\delta$。而 $2^\alpha, 3^\beta, 5^\gamma, 7^\delta < N$，因此操作结果最多有 $\log_2N \times \log_3 N \times \log_5N \times \log_7N$ 种， 算一算是 $63 \times 39 \times 27 \times 22 \approx 1.5 \times 10^6$。因此，直接 bfs 即可。

怎么记忆化判重？传统 vis 数组就不太行了，因为值域有 $10^{19}$，那么这里有两种写法：

- 四维：$vis(\alpha,\beta,\gamma,\delta)$ 表示 $x \times 2^\alpha \times 3^\beta \times 5^\gamma \times 7^\delta$ 是否访问过。这样所需空间也是 $1.5 \times 10^6$；
- 把访问过的数丢 set 里面。

我采用了第二种，这样代码更好写。不过这样会自动带一个 $\log$。

时间复杂度 $\mathcal{O}(w(\log w + n))$，其中 $w = \log_2N \times \log_3 N \times \log_5N \times \log_7N$，$N = 10^n$。

小细节：

- long long 取值范围是 $9.2 \times 10^{18}$，装不下最大的 $19$ 位数 $10^{19} - 1$。因此应选用 unsigned long long。
- 一次操作位数最多增加 $1$。因此当 bfs 到当前状态的 $num$ 大于等于 $10^{n-1}$ 直接输出 $num$ 即可，不用判断会不会超出去。

目前最优解 46 ms，在我之上的两位评测时只有三个数据点（样例）所以不算。但事实上这份代码还有挺多常数优化空间的（不过没必要）。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-10-17 00:50:58 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-10-17 01:04:49
 */
#include <bits/stdc++.h>
#define int unsigned long long

inline int read() {
    int x = 0;
    bool flag = true;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            flag = false;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    if(flag)
        return x;
    return ~(x - 1);
}

typedef std :: pair <int, int> pii;

bool hav[11];

std :: set <int> vis;

signed main() {
    int n = read(), x = read();
    int l = 1;
    for (int i = 1; i < n; ++i)
        l *= 10;

    std :: queue <pii> q;
    q.emplace(x, 0);

    while (!q.empty()) {
        int x = q.front().first, step = q.front().second;
        q.pop();
        
        if (x >= l) {
            printf("%llu\n", step);
            return 0;
        }
        
        std :: memset(hav, false, sizeof(hav));

        int t = x;
        while (t) {
            hav[t % 10] = true;
            t /= 10;
        }

        for (int i = 2; i <= 9; ++i) if (hav[i]) {
            if (vis.count(x * i))
                continue;
            q.emplace(x * i, step + 1);
            vis.insert(x * i);
        }
    }

    puts("-1");
    return 0;
}
```

如果觉得这篇题解写得好，请不要忘记点赞，谢谢！

---

## 作者：qwq___qaq (赞：3)

算法：IDA*

首先，我们可以知道：单纯的 DFS，大概应该可能会 TLE（我没试过），所以我们可以采用迭代加深（我还是没试过），如果担心会 TLE，可以采用 IDA*。

首先，我们知道乘以 $1$ 和 $0$ 根本没有用，所以每次最少乘 $2$，那么迭代次数至多是 $\log{\dfrac{2\times 10^9}{x}}$。

然后我们考虑估价函数：

每次顶多增加一位（还有可能不增加），我们可以统计出它的位数 $k$，那么 F(x)=n-k。此时，我们可以统计出它包含了哪些位。

[Code](https://codeforces.com/contest/1681/submission/158343031)

---

## 作者：happy_dengziyue (赞：3)

### 1 视频题解

![](bilibili:BV1T541197NA)

### 2 思路

很明显的，$x$ 应该乘一个大于等于 $2$ 的数，不然没有意义。

那么，我们使用广度优先搜索，搭配 `map` 进行判重。

注意，不要让 $x$ 多次乘以一个相同的数字。

这个时间复杂度非常玄学，但是它可以通过所有 $209$ 个测试点，最慢 $31\operatorname{ms}$。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<queue>
#include<map>
using namespace std;
int n;
long long y;
__int128 p;
__int128 x;
struct W{
	__int128 x;
	int t;
}f;
queue<W>q;
map<__int128,bool>g;
bool vis[12];
__int128 u;
int ans=-1;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1681D_1.in","r",stdin);
	freopen("CF1681D_1.out","w",stdout);
	#endif
	scanf("%d%lld",&n,&y);
	x=y;
	p=1;
	for(int i=1;i<n;++i)p*=10;
	q.push((W){x,0});
	while(!q.empty()){
		f=q.front();
		q.pop();
		if(f.x>=(p*10))continue;
		//printf("%lld\n",(long long)f.x);fflush(stdout);
		if(f.x>=p){
			ans=f.t;
			break;
		}
		if(g[f.x])continue;
		g[f.x]=1;
		memset(vis,0,sizeof(vis));
		u=f.x;
		while(u){
			if((u%10)<2||vis[u%10]){
				u/=10;
				continue;
			}
			vis[u%10]=true;
			q.push((W){f.x*(u%10),f.t+1});
			u/=10;
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/76377484)

By **dengziyue**

---

## 作者：CWzwz (赞：2)

[CF1681D Required Length](https://www.luogu.com.cn/problem/CF1681D) 题解

[Codeforces](http://codeforces.com/problemset/problem/1681/D)

------------

写完一看，标签里不是有 dp 吗，居然没人写。来提供一个动规做法。

本文中的 $x$ 和 $n$ 都是指输入的 $x$ 和 $n$。$\operatorname{set}_i$ 表示 $i$ 的各位数字的集合，如 $\operatorname{set}_{998244353} = \{2,3,4,5,8,9\}$。

先考虑暴力 dp：

$f_i$ 表示得到数 $i$ 的最小操作次数，转移平凡，$f_{i\times k}\gets\min(f_{i\times k},f_i+1)$，其中 $k\in\operatorname{set}_i$。

最后答案就是所有 $n$ 位数的最小 $f$ 值。

------------

状态数过多，不能通过。

首先明确我们不会乘 $0$ 或 $1$，因为 $0$ 会把自己搞没，$1$ 浪费操作次数。

那么到**操作过程中的所有数**都可以表示为:
$$x\cdot2^a\cdot3^b\cdot4^c\cdot5^d\cdot6^e\cdot7^f\cdot8^g\cdot9^h$$
压缩一下：$num=x\cdot2^a\cdot3^b\cdot5^c\cdot7^d$（其他乘数均可用 $2,3,5,7$ 表示）。

所以只有可以被写成这个形式的数才可能得到。这样就压缩了状态量。

自然地，$f_{a,b,c,d}$ 表示得到 $x\cdot2^a\cdot3^b\cdot5^c\cdot7^d$ 的最小次数。范围是 $10^{19}$，所以 $a<64,b<40,c<28,d<23$。

$160$ 万左右的状态数，可过。转移几乎和暴力转移一样的，刷表即可。

设 $v$ 为 $10^n$，时间复杂度 $\Theta(\log_2v\cdot\log_3v\cdot\log_5v\cdot\log_7v\cdot n)$，约 $3\times10^7$ 次运算。

[Submission](https://codeforces.com/contest/1681/submission/237866213)

31ms 被 bfs 吊打（

```cpp
// Problem: CF1681D 
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
typedef __int128 ll;
const int N = 20;
ll read(){ll x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48);c=getchar();}return x*f;}
void print(ll x){if(x<0)putchar('-'),x=-x;if(x>9)print(x/10);putchar(x%10+48);}

int n, ans = inf;
ll x, max, min;
 
int f[65][45][30][25];
 
ll qpow(ll a, ll b) {
	if(b == 0) return 1;
	ll res = 1;
	for(; b; a *= a, b >>= 1) {
		if(b & 1) res *= a;
		if(res > 1e19 || a > 1e19) return -1; 
	}
	return res;
}
ll num(int a, int b, int c, int d) { // x ·2^a ·3^b ·5^c ·7^d
	ll res = x * qpow(2, a);
	if(res > max || res < 0) return -1;
	res *= qpow(3, b);
	if(res > max || res < 0) return -1;
	res *= qpow(5, c);
	if(res > max || res < 0) return -1;
	res *= qpow(7, d);
	if(res > max || res < 0) return -1; // 超过范围 
	return res;
}

int main() {
	n = read(), x = read();
	max = qpow(10, n) - 1;
	min = qpow(10, n - 1); // n 位数，即 [10^{n-1}, 10^n)。 
	memset(f, inf, sizeof f);
	f[0][0][0][0] = 0;
	for(int a = 0; a < 64; a++) {
		for(int b = 0; b < 40; b++) {
			for(int c = 0; c < 28; c++) {
				for(int d = 0; d < 23; d++) {
					ll now = num(a, b, c, d);
					if(now == -1) break;  // 超出范围不管
					ll set = 0, tmp = now; 
					while(tmp) set |= (1 << (tmp % 10)), tmp /= 10; // 压 set_now
					for(int k = __builtin_ctz(set); set; set -= set & -set, k = __builtin_ctz(set)) { // 枚二进制位
						if(k == 0 || k == 1) continue; 
						if(now * k > max) break;
						if(k == 2 || k == 3 || k == 5 || k == 7) {
							f[a + (k == 2)][b + (k == 3)][c + (k == 5)][d + (k == 7)] = std::min(f[a + (k == 2)][b + (k == 3)][c + (k == 5)][d + (k == 7)], f[a][b][c][d] + 1);
						} else if(k == 4) {
							f[a + 2][b][c][d] = std::min(f[a + 2][b][c][d], f[a][b][c][d] + 1);
						} else if(k == 6) {
							f[a + 1][b + 1][c][d] = std::min(f[a + 1][b + 1][c][d], f[a][b][c][d] + 1);
						} else if(k == 8) {
							f[a + 3][b][c][d] = std::min(f[a + 3][b][c][d], f[a][b][c][d] + 1);
						} else if(k == 9) {
							f[a][b + 2][c][d] = std::min(f[a][b + 2][c][d], f[a][b][c][d] + 1);
						} // 刷表 
					}
					if(now >= min) ans = std::min(ans, f[a][b][c][d]); 
				}
			}
		}
	}
	print(ans == inf ? -1 : ans);
    return 0;
}
```

---

## 作者：Light_az (赞：2)

### 剪枝深搜

说实话，这道题我看到的第一眼是贪心算法。就是将 $n$ 中最大的数位 $y$ 与 $n$ 相乘，以此类推，最后求出答案，开心把代码提交后成功零分。这让我开始反思，后来感觉可以用深搜去完成该题目，但是我们需要几个小小的剪枝方案。首先对于 $n$ 来说，真正影响它数位的数字其实是 $2$ 到 $9$ ,因为 $0$ 和 $1$ 与 $n$ 相乘数位其实是没有变化的，其次，我们好好想想，如果 $n$ 现在是 $y$ 位，那么距离它变成 $x$ 位数之前至少要进行 $x $ 减 $y$ 次操作，所以当现在的操作次数已经大于最优解时，我们就返回答案，下面是完整代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,x;
long long mini=50;
int Can=0;
long long f(long long n){//求数位 
	long long ans=0;
	while(n>0){
		ans++;
		n/=10;
	}
	return ans;
}
int least(long long n,long long num){//求最小次数 
	return x-f(n)+num;
}
void dfs(long long n,long long step){
	if(least(n,step)>=mini){//剪枝 
		/*
			>=非常重要，
			当答案可能为已经求出的最优解时 
			没有必要继续搜索
			因为最终答案仍为最优解
			因此不可以使用> 
		*/
		return ;
	}
	if(f(n)==x){//符合要求 
		Can=1;
		mini=min(mini,step);//更新答案 
		return ;
	}
	long long k=n;
	while(k>0){//枚举 
		if(k%10>1){//大于1的数位才能对n的数位个数造成影响 
			dfs(n*(k%10),step+1);
		}
		k/=10;
	}
	return ;
}
int main(){
	cin>>x>>n;
	dfs(n,0);
	if(!Can){//如果没有可行解，输出-1 
		cout<<-1;
	}
	else{//输出答案 
		cout<<mini;
	}
	return 0;
}
```


---

## 作者：Cocoly1990 (赞：2)

看到这题并没有什么好的思路，事实上对于 $x\times y$ 也并无好的性质。

我们可以尝试使用一个 BFS 或者 DFS 进行搜索，考虑到某一时刻的代价只和当前是什么数有关，这个部分显然可以记忆化来减少重复状态数。

一些经典传统剪枝：当前操作次数大于当前的答案就不需要管他了。

复杂度证明：

![XFH3Uf.png](https://s1.ax1x.com/2022/05/25/XFH3Uf.png)

让我们一起来膜拜 4b 吧/tyt.

---

## 作者：YCSluogu (赞：1)

# CF1681D 题解

## 题目分析

对于每一个状态 $(x, t)$，转移至 $(x', t + 1)$，其中的 $x'$ 就是 $x$ 与自己各位数的积。最终我们要找到一个状态使得 $x$ 的位数等于 $n$ 并且 $t$ 值最小

## 代码框架

这道题有很多有意思的做法，不过 `bfs` 可以更快地解决。（但是为什么 tag 里面有一个动态规划）

一个很容易想到的剪枝策略就是：当 $x$ 的位数大于 $n$ 时可以直接弃掉。

## 代码细节

估计很多人考虑完写后会纠结一下如何判断位数是否达标，比较暴力的做法就是写一个获取数字位数的函数:

``` cpp
int dig(int x) {
  int ans = 0;
  while (x) {
    x /= 10;
    ans++;
  }
  return ans;
}
```

用数学的方法就是：

``` cpp
log10(x) + 1 // 这个+1是必须得要的
```

但是这个方法会被 `99999999999999` 这样的数据卡掉。这是由于 `log10` 函数实现本身的精度问题（什么憨批函数）

或者在 `bfs` 开始前用 `pow` 将相应位数的区间求出来

``` cpp
upper = pow(10, n) - 1;
lower = pow(10, n - 1);
```

至于判重，可以利用 `set<int>``map<int, bool>` 这样可以用来判重的数据结构。 ~~（一开始脑袋没转过弯只想着用 `map` 去了，谢谢管理员提醒）~~

~~一定要开 `unsigned long long`!!!~~

## 完整代码:

``` cpp
#include <iostream>
#include <cmath>
#include <set>
#include <queue>
#define int unsigned long long

using namespace std;

set<int> vis;
queue<int> q1, q2;
int n, x, upper, lower;

void record(int x, int t) {
  if (x > upper || vis.find(x) != vis.end()) return;
  vis.insert(x);
  q1.push(x);
  q2.push(t);
}

signed bfs() {
  upper = pow(10, n) - 1;
  lower = pow(10, n - 1);
  record(x, 0);
  while (!q1.empty()) {
    int f = q1.front();
    int t = q2.front();
    if (f >= lower) {
      return t;
    }
    int u = f;
    while (u) {
      record(f * (u % 10), t + 1);
      u /= 10;
    }
    q1.pop();
    q2.pop();
  }
  return -1;
}

signed main() {
  cin >> n >> x;
  cout << bfs() << endl;
  return 0;
}
```


---

## 作者：SnowTrace (赞：1)

如题，宽搜乘亿乘就可以了。

对于每一个数，枚举它的数位，然后乘上去，如果结果已经被访问过，那么就不继续进行下一步的延申。

具体过程用宽搜即可。

判断答案只需要手动算出左边界和有边界，看当前的数是否符合在这个区间中就可以。

但是有几个小点需要注意：

1. 记得不要直接开桶记录是否访问过，用

```cpp
map<int,bool>vis
```
映射.

2. 本题数据范围大 开到 unsigned long long .

于是 水水的 1700 的题就被做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int unsigned long long
vector<int>p;
map<int,bool>vis;
int __pow(int n){
	int pro = 1;
	for(int i =0;i<n;i++)pro*=10;
	return pro;
}queue<pair<int,int> >q;
signed main(){
	int x,n;
	cin >> n >> x;
	int l = __pow(n-1),r = __pow(n);
	q.push({x,0});
	vis[x] = 1;
	while(!q.empty()){
		int e = q.front().first;
		if(e>=l){
			cout << q.front().second << endl;
			return 0;
		}
		p.clear();
		while(e>0){
			p.push_back(e%10);
			e/=10;
		}for(int i =0;i<p.size();i++)
			if(p[i]!=0 and !vis[q.front().first*p[i]] and q.front().first*p[i]>(int)0 and q.front().first*p[i]<r){
				q.push({q.front().first*p[i],q.front().second+1});
				vis[q.front().first*p[i]] = 1;
		}
	q.pop();
	}
	cout << -1 << endl;
}
```


---

## 作者：Ice_lift (赞：0)

> $\mathtt{TAGS}$：暴搜 + 剪枝

# 前置函数

下文中称：$len(x)$ 为 $x$ 十进制下的位数。

# First. 为什么是搜索

开始看到这道题想到了贪心：每次找出最大的一个数乘上去。

但是很显然：可以先乘一个小的数，使得其中某一位增大大，再乘上最大值是优于直接每次都乘最大值的。例如：$42 \to 84 \to 672$。

所以，贪心无法做。

再看一眼数据范围，发现 $n \le 19$，那么极端一点，对于 $2$
 每次都只 $\times 2$，最多也只需要 $\log_2 10^{19}$ 次。
 
所以可以尝试一下搜索和剪枝。

# Second.如何剪枝

1. 可行性剪枝：如果一个数中没有任何一个数字 $\ge1$，且位数 $<n$，那么该数一定不能再增加，所以可以剪掉。

2. 最优化剪枝：如果当前到达 $x$ 的次数再加上 $n - len(x)$（即要使 $x$ 的长度到达 $n$ 最少需要的步数）， $\ge ans$ 那么，一定不是最优解。

3. 最优化剪枝2：如果当前到达 $x$ 的步数 $\ge$ 之前到达 $x$ 的步数，那么此时也不可能是最优解。

# Third. 无解

如果 $len(x)$ 怎样都到不了 $n$ 那么无解。

# Code 

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
#define int long long
bool check (int x) {
	for (int p = x; p; p /= 10) {
		if(p % 10 > 1) return 1;
	}
	return 0;
}
int getlen (int x) {
	int len = 0;
	for (int p = x; p; p /= 10) len ++;
	return len;
}
int n, x;
int ans = 1e18;
map<int, int> res;
void dfs (int x, int cnt) {
	int len = getlen(x);
	if(!check(x) && len != n) return;
	if(!res[x]) res[x] = 1e18;
	if(cnt >= res[x] || cnt + (n - len) >= ans) return;
	res[x] = cnt;
	if(getlen(x) == n) {
		ans = min(ans, cnt);
		return;
	}
	for (int p = x; p; p /= 10) {
		int num = p % 10;
		if(num == 1 || num == 0) continue;
		dfs(x * num, cnt + 1);
	}
}

signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> x;
	dfs(x, 0);
	if(ans == 1e18) cout << -1;
	else cout << ans << endl;
	return 0;
}
```

---

## 作者：npqenqpve (赞：0)

### 思路：

考虑建边跑最短路，那么就是 $x$ 对每个能通过 $x$ 乘以某一位得到的点建边。

建边时如果有一个点已经是 $n$ 位数，那就不用继续从这个点建边了，直接输出即可。

所以连最短路都不用跑，每个数至多乘 $\log_2n$ 次任意数就可以变成一个 $n$ 位数。 

### 代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,x,d[(int)(1e6+10)];
struct node
{
    int id,val;
};
queue<node>q;
int get(int x)
{
    int cnt=0;
    while(x)
    {
        cnt++;
        x/=10;
    }
    return cnt;
}
int f[(int)(1e6+10)];
map<int,int>vis;
signed main()
{
    int tot=1,ff=0;
    cin>>n>>x;d[1]=x;
    q.push((node){1,d[1]});
    while(!q.empty())
    {
        node u=q.front();
        if(get(u.val)==n) 
        {
            cout<<f[u.id];ff=1;
            break;
        }
        q.pop();
        if(vis[u.val]) continue;
        vis[u.val]=1;
        for(int i=1;i<=get(u.val);i++)
        {
            node t=(node){++tot,u.val*(u.val/(int)(pow(10,i-1))%10)};
            d[t.id]=t.val;
            f[t.id]=f[u.id]+1;
            q.push(t);
        }
    }
    if(!ff) puts("-1");
	system("pause > null");
}
```



---

