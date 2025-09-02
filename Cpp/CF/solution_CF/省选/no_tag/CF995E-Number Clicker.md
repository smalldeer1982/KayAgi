# Number Clicker

## 题目描述

Allen is playing Number Clicker on his phone.

He starts with an integer $ u $ on the screen. Every second, he can press one of 3 buttons.

1. Turn $ u \to u+1 \pmod{p} $ .
2. Turn $ u \to u+p-1 \pmod{p} $ .
3. Turn $ u \to u^{p-2} \pmod{p} $ .

Allen wants to press at most 200 buttons and end up with $ v $ on the screen. Help him!

## 说明/提示

In the first example the integer on the screen changes as $ 1 \to 2 \to 3 $ .

In the second example the integer on the screen changes as $ 3 \to 2 $ .

## 样例 #1

### 输入

```
1 3 5
```

### 输出

```
2
1 1
```

## 样例 #2

### 输入

```
3 2 5
```

### 输出

```
1
3
```

# 题解

## 作者：攀岩高手 (赞：8)

- upd 2022.6.19 修正了公式错误和 latex 语法错误

官方题解里提到验题人的一种期望更优的作法，感觉很有意思。

考虑从 $u$ 和 $v$ 分别找出一条到 0 的长度在 100 以内的路径。那么以 $u$ 为例，我们在区间 $[1, p-1]$ 内随机取一个整数 $x$ ，记 $a=ux\bmod p,b=x$。对 $(a,b)$ 使用更相减损术将 $b$ 迭代到 0 为止，具体过程如下：

- 若 $a<b$ ，交换 $a$ 和 $b$。
- 否则，将 $a$ 减去 $b$。

观察到初始时 $u\equiv\frac{a}{b}\pmod p$，那么操作 $u\to u-1\pmod p$ 就相当于 $\frac{a}{b}\to \frac{a-b}{b}\pmod p$，$u\to u^{p-2}\pmod p$ 就相当于 $\frac{a}{b}\to \frac{b}{a}\pmod p$。到 $b=0$ 时 $u$ 也就为 0 了。

但更相减损术不能保证复杂度。于是我们不断随机 $x$ 并用辗转相除法计算路径长度，直到它小于等于 100 为止。实际上这样跑的次数会很少，几乎是期望 $O(1)$ 的。所以我们可以在期望 $O(\log p)$ 左右的时间找到一条从任一点到 0 的长度在 100 以内的路径。

因为 2 操作与 3 操作互逆，那么显然 $v$ 到 0 的路径是可逆的。最终答案就是把两条路径拼起来。

下面是代码：
```cpp
#include <cstdio>
#include <algorithm>
#include <chrono>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int MAXL=220;
int get_len(int a, int b)
{
	if (b==0) return 0;
	return get_len(b, a%b)+a/b+1;
}
int get_path(int u, int p, bool* c)
{
	int a, b, l=0;
	do
	{
		b=rng()%(p-1)+1;
		a=1ll*u*b%p;
	} while (get_len(a, b)>100);
	while (b!=0)
		if (a<b) c[++l]=0, swap(a, b);
		else a-=b, c[++l]=1;
	return l;
}
bool c1[MAXL], c2[MAXL];
int main()
{
//	freopen("E.in", "r", stdin);
//	freopen("E.out", "w", stdout);
	int u, v, p;
	scanf("%d%d%d", &u, &v, &p);
	int l1=get_path(u, p, c1);
	int l2=get_path(v, p, c2);
	printf("%d\n", l1+l2);
	for (int i=1; i<=l1; i++) printf("%d ", c1[i]?2:3);
	for (int i=l2; i>=1; i--) printf("%d ", c2[i]?1:3);
	putchar('\n');
	return 0;
}
```

---

## 作者：Wuyanru (赞：6)

题目大意：

给你三个数 $ u $,$ v $,$ p $,将 $ u $ 进行若干次变化得到 $ v $,要求次数在 $ 200 $ 以内，然后输出一组合法的解，其中 $ p $ 保证为质数。

变化共有三种，分别是:
1.  $ u \to u+1\pmod{p} $；

2.  $ u \to u+p-1\pmod{p} $；

3.  $ u \to u^{p-2}\pmod{p} $；

我做这道题的时候第一个反应是广搜，用广搜做显然是可以做出这道题的，当然，普通的广搜也肯定是会超时的。

那么我们现在可以考虑双向广搜，这种做法要求其中所有的操作都是可逆的，其中前两种操作显然是可逆的，但是第三种操作是否是可逆的呢？

答案是肯定的，因为题目中保证了 $ p $ 是一个质数，那么 $ u^{p-2}\pmod{p} $ 与 $ u $ 互为逆元，那么就可以得到：

$ \left(u^{p-2}\right)^{p-2}\pmod{p} = u  $ 

所以第三种变换也是可逆的，那么这道题就可以使用双向bfs来求解了。

本人使用的是C++11的unordered_map，不使用C++11会造成CE。

因为他使用的是哈希，所以理论上会快一些，当然，使用map也不会超时。

广搜函数：
```
long long a,b,p;
unordered_map<long long,int>ans1;
unordered_map<long long,int>ans2;
unordered_map<long long,long long>pre1;
unordered_map<long long,long long>pre2;
unordered_map<long long,int>num1;
unordered_map<long long,int>num2;
unordered_map<long long,bool>vis1;
unordered_map<long long,bool>vis2;
void bfs() {
	queue<long long>que1;
	queue<long long>que2;
	if(a==b) {//如果a与b相等，直接输出0，退出函数
		printf("0");
		return ;
	}
	que1.push(a);//第一个队列从a开始搜索
	pre1[a]=-1;
	vis1[a]=1;
	que2.push(b);//第二个队列从b开始搜索
	pre2[b]=-1;//将前缀标记为-1
	vis2[b]=1;//记得打上a与b的标记
	while(true) {
		long long ti=que1.front();//取出队列一的的队首
		que1.pop();
		long long tt=ti+1;//变换1
		if(tt>=0&&vis1[tt]==0) {
			tt%=p;
			vis1[tt]=1;
			ans1[tt]=ans1[ti]+1;
			pre1[tt]=ti;
			num1[tt]=1;
			que1.push(tt);
			if(vis2[tt]==1) {
				print(tt);
				return ;
			}
		}
		tt=ti-1;//变换2
		if(tt>=0&&vis1[tt]==0) {
			tt%=p;
			vis1[tt]=1;
			ans1[tt]=ans1[ti]+1;
			pre1[tt]=ti;
			num1[tt]=2;
			que1.push(tt);
			if(vis2[tt]==1) {
				print(tt);
				return ;
			}
		}
		tt=ny(ti);//变换3
		if(tt>=0&&vis1[tt]==0) {
			tt%=p;
			vis1[tt]=1;
			ans1[tt]=ans1[ti]+1;
			pre1[tt]=ti;
			num1[tt]=3;
			que1.push(tt);
			if(vis2[tt]==1) {
				print(tt);
				return ;
			}
		}
		ti=que2.front();//取出队列二的队首
		que2.pop();
		tt=ti-1;//因为是双向bfs，所以第二个队列里变化1和变化2是颠倒的
		if(tt>=0&&vis2[tt]==0) {//变化1
			tt%=p;
			vis2[tt]=1;
			ans2[tt]=ans2[ti]+1;
			pre2[tt]=ti;
			num2[tt]=1;
			que2.push(tt);
			if(vis1[tt]==1) {
				print(tt);
				return ;
			}
		}
		tt=ti+1;//变化2
		if(tt>=0&&vis2[tt]==0) {
			tt%=p;
			vis2[tt]=1;
			ans2[tt]=ans2[ti]+1;
			pre2[tt]=ti;
			num2[tt]=2;
			que2.push(tt);
			if(vis1[tt]==1) {
				print(tt);
				return ;
			}
		}
		tt=ny(ti)//变化3
		if(tt>=0&&vis2[tt]==0) {
			tt%=p;
			vis2[tt]=1;
			ans2[tt]=ans2[ti]+1;
			pre2[tt]=ti;
			num2[tt]=3;
			que2.push(tt);
			if(vis1[tt]==1) {
				print(tt);
				return ;
			}
		}
	}
}
```
快速幂求逆元：
```
long long ny(long long n) {//求n的逆元
	long long pi=p-2;//次数为p-2
	long long ans=1;
	while(pi) {
		if(pi&1)
			ans*=n,ans%=p;
		n=n*n,n%=p;
		pi>>=1;
	}
	return ans;
}
```
**快速幂一定要记得取模。**

我不可能告诉你们WA了两天没找到错哪里就是因为快速幂没有取模。

然后就是绕脑子的输出函数：
```
void print1(long long t) {
	if(pre1[t]==-1)//如果没有前缀（t=a）返回
		return ;
	print1(pre1[t]);
	printf("%d ",num1[t]);
}
void print2(long long t) {
	if(pre2[t]==-1)
		return ;
	printf("%d ",num2[t]);//注意这里和上面的print1里语句顺序不一样
	print2(pre2[t]);
}
void print(long long t) {//调用入口在bfs里
	printf("%d\n",ans1[t]+ans2[t]);//先输出变化操作数
	print1(t);//输出队列1中t如何变化
	print2(t);//输出队列2中t如何变化
}
```
那么我们就把这道题解决了。

AC代码：
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,p;
unordered_map<long long,int>ans1;
unordered_map<long long,int>ans2;
unordered_map<long long,long long>pre1;
unordered_map<long long,long long>pre2;
unordered_map<long long,int>num1;
unordered_map<long long,int>num2;
unordered_map<long long,bool>vis1;
unordered_map<long long,bool>vis2;
long long ny(long long n) {//求n的逆元
	long long pi=p-2;//次数为p-2
	long long ans=1;
	while(pi) {
		if(pi&1)
			ans*=n,ans%=p;
		n=n*n,n%=p;
		pi>>=1;
	}
	return ans;
}
void print1(long long t) {
	if(pre1[t]==-1)//如果没有前缀（t=a）返回
		return ;
	print1(pre1[t]);
	printf("%d ",num1[t]);
}
void print2(long long t) {
	if(pre2[t]==-1)
		return ;
	printf("%d ",num2[t]);//注意这里和上面的print1里语句顺序不一样
	print2(pre2[t]);
}
void print(long long t) {//调用入口在bfs里
	printf("%d\n",ans1[t]+ans2[t]);//先输出变化操作数
	print1(t);//输出队列1中t如何变化
	print2(t);//输出队列2中t如何变化
}
void bfs() {
	queue<long long>que1;
	queue<long long>que2;
	if(a==b) {//如果a与b相等，直接输出0，退出函数
		printf("0");
		return ;
	}
	que1.push(a);//第一个队列从a开始搜索
	pre1[a]=-1;
	vis1[a]=1;
	que2.push(b);//第二个队列从b开始搜索
	pre2[b]=-1;//将前缀标记为-1
	vis2[b]=1;//记得打上a与b的标记
	while(true) {
		long long ti=que1.front();//取出队列一的的队首
		que1.pop();
		long long tt=ti+1;//变换1
		if(tt>=0&&vis1[tt]==0) {
			tt%=p;
			vis1[tt]=1;
			ans1[tt]=ans1[ti]+1;
			pre1[tt]=ti;
			num1[tt]=1;
			que1.push(tt);
			if(vis2[tt]==1) {
				print(tt);
				return ;
			}
		}
		tt=ti-1;//变换2
		if(tt>=0&&vis1[tt]==0) {
			tt%=p;
			vis1[tt]=1;
			ans1[tt]=ans1[ti]+1;
			pre1[tt]=ti;
			num1[tt]=2;
			que1.push(tt);
			if(vis2[tt]==1) {
				print(tt);
				return ;
			}
		}
		tt=ny(ti);//变换3
		if(tt>=0&&vis1[tt]==0) {
			tt%=p;
			vis1[tt]=1;
			ans1[tt]=ans1[ti]+1;
			pre1[tt]=ti;
			num1[tt]=3;
			que1.push(tt);
			if(vis2[tt]==1) {
				print(tt);
				return ;
			}
		}
		ti=que2.front();//取出队列二的队首
		que2.pop();
		tt=ti-1;//因为是双向bfs，所以第二个队列里变化1和变化2是颠倒的
		if(tt>=0&&vis2[tt]==0) {//变化1
			tt%=p;
			vis2[tt]=1;
			ans2[tt]=ans2[ti]+1;
			pre2[tt]=ti;
			num2[tt]=1;
			que2.push(tt);
			if(vis1[tt]==1) {
				print(tt);
				return ;
			}
		}
		tt=ti+1;//变化2
		if(tt>=0&&vis2[tt]==0) {
			tt%=p;
			vis2[tt]=1;
			ans2[tt]=ans2[ti]+1;
			pre2[tt]=ti;
			num2[tt]=2;
			que2.push(tt);
			if(vis1[tt]==1) {
				print(tt);
				return ;
			}
		}
		tt=ny(ti)//变化3
		if(tt>=0&&vis2[tt]==0) {
			tt%=p;
			vis2[tt]=1;
			ans2[tt]=ans2[ti]+1;
			pre2[tt]=ti;
			num2[tt]=3;
			que2.push(tt);
			if(vis1[tt]==1) {
				print(tt);
				return ;
			}
		}
	}
}
int main() {
	scanf("%lld%lld%lld",&a,&b,&p);
	bfs();
	return 0;
}
```
代码细节注意：

1.  快速幂中两个数相乘可能会爆int；

2.  如果变量是long long 类型，那么使用 printf函数时一定要用"%lld"（如果你使用cin和cout请忽略这句话）；

3. 一定要把变量类型搞清楚；

4.  记得取模（不要像我一样过了两天才发现）；

5.  操作 $ 2 $ 中如果对 $ 0 $ 进行结果会变成 $ p-1 $。

6.  求逆元时不用快速幂会超时。

7.  输出时要把语句顺序搞清楚，一定要有结束条件。

8.  bfs里面找到答案要记得立即退出。

感谢观看！

---

## 作者：swiftc (赞：3)

~~这道题我一开始看还以为是数学题~~

求逆元其实就可以看完随机跳到另一个位置，那么根据生日悖论，状态数不会太多，双向bfs即可
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int u,v,p;
map<int,int>vis1,vis2,nxt,pre;//记录每一个位置有么有被访问过和是哪跳过来的
queue<int> q1,q2;
int qpow(int a,int b){
	if(b==0)return 1;
	int tmp=qpow(a,b/2);
	return b%2?tmp*tmp%p*a%p:tmp*tmp%p;	
}
main(){
	scanf("%lld%lld%lld",&u,&v,&p);
	q1.push(u);
	q2.push(v);
	vis1[u]=1;
	pre[u]=-1;
	vis2[v]=1;
	nxt[v]=-1;
	while(!q1.empty()){
		int now=q1.front();
		q1.pop();
		if(vis2[now]){
			printf("%lld\n",vis1[now]+vis2[now]-2);
			stack<int>s;
			int tmp=now;
			while(tmp!=-1){
				s.push(tmp);
				tmp=pre[tmp];
			}
			while(s.size()!=1){
				int k=s.top();
				s.pop();
				if((k+1)%p==s.top()){
					printf("1 ");
				}
				else if((k+p-1)%p==s.top()){
					printf("2 ");
				}
				else{
					printf("3 ");
				}
			}
			tmp=now;
			while(nxt[tmp]!=-1){
				if((tmp+1)%p==nxt[tmp]){
					printf("1 ");
				}
				else if((tmp+p-1)%p==nxt[tmp]){
					printf("2 ");
				}
				else{
					printf("3 ");
				}
				tmp=nxt[tmp];
			}
			return 0;
	    }
		if(!vis1[(now+1)%p])q1.push((now+1)%p),vis1[(now+1)%p]=vis1[now]+1,pre[(now+1)%p]=now;
		if(!vis1[(now-1+p)%p])q1.push((now-1+p)%p),vis1[(now-1+p)%p]=vis1[now]+1,pre[(now-1+p)%p]=now;
		int power=qpow(now,p-2);
		if(!vis1[power])q1.push(power),vis1[power]=vis1[now]+1,pre[power]=now;
		now=q2.front();q2.pop();
		if(!vis2[(now+1)%p])q2.push((now+1)%p),vis2[(now+1)%p]=vis2[now]+1,nxt[(now+1)%p]=now;
		if(!vis2[(now-1+p)%p])q2.push((now-1+p)%p),vis2[(now-1+p)%p]=vis2[now]+1,nxt[(now-1+p)%p]=now;
		power=qpow(now,p-2);
		if(!vis2[power])q2.push(power),vis2[power]=vis2[now]+1,nxt[power]=now;
	}
}
```
还有...

据我们学校的学长说，双向广搜可能搜出来的不是最优解


---

## 作者：Super_Cube (赞：1)

# Solution

暴力 bfs，用双向搜索优化后即可通过。

证明是生日悖论，因为操作三可认为是随机变换，所以很大概率会重复。

在值域为 $V$ 的情况下，随机 $n$ 个数不重复的概率为 $\displaystyle\prod_{i=0}^{n-1}\dfrac{V-i}{V}$。

生日悖论：取 $V=365$，在 $n=61$ 时概率不到千分之五，这与直觉相违背。

此题 $V=10^9+9$，在 $n=120000$ 时概率不到万分之八。

于是可在不超过约 $40$ 步操作使得 $u$ 变为 $v$。

至于方案就记录上一步是从哪个数转移过来的，最后递归输出。

---

## 作者：沉石鱼惊旋 (赞：1)

# 前言

在『江莉XCPC民间算法交流枢纽』有群友扔了这题，还挺有趣的。（这里是专有名词中英文之间不加括号没事的吧？）

# 题目翻译

给定 $u,v,p$，保证 $p$ 是质数，有 $3$ 种操作：

1. $u\gets u+1$
2. $u\gets u-1$
3. $u\gets u^{p-2}$

以上操作过后均对 $p$ 取模。

求一种不超过 $200$ 次操作使得 $u=v$ 的操作方案。

$0\leq u,v\lt p,3\leq p\leq 10^9+9$。

# 题目思路

$200$ 直接搜就算有很多操作重复也是会炸的。考虑直接双向搜索，从 $u,v$ **同时**开搜。

~~你怎么知道我没睡醒两边各搜 100 个 TLE on 3。~~

为啥这样子时间复杂度是正确的？$u\gets u^{p-2}$ 其实就相当于随机选位置跳了，几乎一点关系没有。根据生日悖论，大概搜 $\mathcal O(\sqrt p)$ 次就能搜到，这样子跳到重复的概率其实是非常高的。

搜的时候记录一下前驱后驱，$v$ 搜碰到通过 $u$ 搜到的位置就可以停下输出了。我每个点都是不到 $40$ 次操作。

# 完整代码


```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;
int x, y, p;
int pos;
inline int qpow(ll x, int y)
{
    ll ret = 1;
    for (; y > 0; y >>= 1)
    {
        if (y & 1)
            (ret *= x) %= p;
        (x *= x) %= p;
    }
    return ret;
}
inline int inv(int x) { return qpow(x, p - 2); }
map<int, int> frt;
map<int, int> bck;
map<int, pii> pre;
map<int, pii> suf;
queue<pii> q1;
queue<pii> q2;
bool ok;
inline int F(int x, int op)
{
    if (op == 1)
        return (x + 1) % p;
    if (op == 2)
        return (x + p - 1) % p;
    return inv(x);
}
inline bool in(int x) { return 1 <= x && x < p; }
void out_pre(int x)
{
    if (!pre[x].first)
        return;
    out_pre(pre[x].second);
    cout << pre[x].first << " ";
}
void out_suf(int x)
{
    if (!suf[x].first)
        return;
    cout << (suf[x].first == 3 ? 3 : 3 - suf[x].first) << " ";
    out_suf(suf[x].second);
}
int main()
{
    cin >> x >> y >> p;
    pre[x] = {0, 0};
    suf[y] = {0, 0};
    q1.push({x, frt[x] = 0});
    q2.push({y, bck[y] = 0});
    while (!ok && !q1.empty() && !q2.empty())
    {
        int u = q1.front().first, v = q2.front().first;
        int du = q1.front().second, dv = q2.front().second;
        // cout << u << " " << v << endl;
        q1.pop(), q2.pop();
        for (int op = 1; op <= 3; op++)
        {
            int tx = F(u, op);
            if (frt.count(tx))
                continue;
            pre[tx] = {op, u};
            q1.push({tx, frt[tx] = du + 1});
        }
        for (int op = 1; op <= 3; op++)
        {
            int ty = F(v, op);
            if (bck.count(ty))
                continue;
            suf[ty] = {op, v};
            q2.push({ty, bck[ty] = dv + 1});
            if (frt.count(ty))
            {
                ok = 1, pos = ty;
                break;
            }
        }
    }
    cout << frt[pos] + bck[pos] << endl;
    out_pre(pos);
    out_suf(pos);
    return 0;
}
```

---

## 作者：wanggiaoxing (赞：1)

这道题乍一看像道迭代加深，但看同学都用广搜过的，我就开始用双向bfs做了。
## 干货补充
### 双向 bfs
通过同时从终点和起点广搜，找到第一个交点，此时两边步数相加即为所求（比单向快很多）。![](https://i.loli.net/2019/09/25/jevyd2TPC7FX6GA.png)
[图片来源](https://blog.csdn.net/weixin_43501684/article/details/90147421)
### 基本思路
同时从 $u$ 和 $v$ 广搜，设当前从 $u$ 广搜到 $i$ ，从 $v$ 广搜到 $j$ ，从 $i$ 的广搜大家应该都会，从 $j$ 的广搜则操作一为 $j-1$ ,因为 $j$ 为被加一后的结果，同理操作二也为 $j+1$ ,那操作三呢？见下方。
### 关于逆元

注意到逆元是在 $\bmod$ $p$ 的情况下，所以 $a$ 的逆元的逆元即为 $a$ 。所以操作三的逆操作即为求 $j$ 的 $p-2$ 次方。
## 两个小细节
开 long long。

因为我是手写队列，所以数组一定要开大些。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long int u,v,p;
map<long long int,bool>q;
map<long long int,bool>q1;//判重
map<long long int,long long int>p1;
map<long long int,long long int>p2;//记前缀
map<long long int,long long int>num;
map<long long int,long long int>num1;//记路径
map<long long int,long long int>ans;
map<long long int,long long int>ans1;//记步数
long long int qwq[1000001];
long long int qaq[1000001];
int mi(int x)
{
	long long int ans=1,base=x;
	long long int mod=p-2;
	while(mod)
	{
		if(mod&1)
			ans=(ans*base)%p;
		base=(base*base)%p;
		mod>>=1;
	}
	return ans;
}
void print1(int x)
{
	if(p1[x]==-1)
		return;
	print1(p1[x]);
	cout<<num[x]<<" ";
}
void print2(int x)
{
	if(p2[x]==-1)
		return;	
	cout<<num1[x]<<" ";
	print2(p2[x]);
}
void print(int x)
{
	print1(x);
	print2(x);
}
void bfs()
{
	long long int head=0,end=1,head1=0,end1=1;
	q[u]=1;
	q1[v]=1;
	p1[u]=-1;
	p2[v]=-1;
	qaq[1]=v;
	qwq[1]=u;
	long long int a,a1;
	while(1)//这里写while（1）是因为它保证有解
	{
		a=qwq[++head];	
		long long int b=a+1;
		if(b>=0&&q[b]==0)
		{
			b%=p;
			q[b]=1;
			qwq[++end]=b;
			ans[b]=ans[a]+1;
			p1[b]=a;
			num[b]=1;
			if(q1[b]==1)
			{
				cout<<ans[b]+ans1[b]<<endl;
				print(b);
				return;
			}
			
		}
		b=a-1;
		if(b>=0&&q[b]==0)
		{
			b%=p;
			q[b]=1;
			qwq[++end]=b;
			ans[b]=ans[a]+1;
			p1[b]=a;
			num[b]=2;
			if(q1[b]==1)
			{
				cout<<ans[b]+ans1[b]<<endl;
				print(b);
				return;
			}			
		}
		b=mi(a);
		if(b>=0&&q[b]==0)
		{
			b%=p;
			q[b]=1;
			qwq[++end]=b;
			ans[b]=ans[a]+1;
			p1[b]=a;
			num[b]=3;
			if(q1[b])
			{
				cout<<ans[b]+ans1[b]<<endl;
				print(b);
				return;
			}
			
		}
		
		a1=qaq[++head1];					
		b=a1+1;
		if(b>=0&&q1[b]==0)
		{
			b%=p;
			q1[b]=2;
			qaq[++end1]=b;
			ans1[b]=ans1[a1]+1;
			p2[b]=a1;
			num1[b]=2;
			if(q[b])
			{
				cout<<ans[b]+ans1[b]<<endl;
				print(b);
				return;
			}
			
		}
		b=a1-1;
		if(b>=0&&q1[b]==0)
		{
			b%=p;
			q1[b]=1;
			qaq[++end1]=b;
			ans1[b]=ans1[a1]+1;
			p2[b]=a1;
			num1[b]=1;
			if(q[b])
			{
				cout<<ans[b]+ans1[b]<<endl;
				print(b);
				return;
			}
			
		}
		b=mi(a1);
		if(b>=0&&q1[b]==0)
		{
			b%=p;
			q1[b]=1;
			qaq[++end1]=b;
			ans1[b]=ans1[a1]+1;
			p2[b]=a1;
			num1[b]=3;
			if(q[b]==1)
			{
				cout<<ans[b]+ans1[b]<<endl;
				print(b);
				return;
			}
			
		}		
	}
	
}
int main()
{
	cin>>u>>v>>p;
	if(u==v)
	{
		cout<<0;
		return 0;
	}
	bfs();
	return 0;
}
```


---

## 作者：qianfujia (赞：1)

这题看着挺吓人，实际上双向BFS即可，据CF题解说是不会搜超过$10^7$种状态的，于是跑了过去

Code
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll u, v, p;
inline ll pw(ll x, ll y){
	ll ans = 1;
	while(y){
		if(y & 1)(ans *= x) %= p;
		x = x * x % p;
		y >>= 1;
	}
	return ans;
}
map <ll, ll> M, pre, Vis, nxt;
queue <ll> q, q2;
int stk[1000], top = 0;
int main(){
	scanf("%lld%lld%lld", &u, &v, &p);
	q.push(u); M[u] = 1; pre[u] = -1; q2.push(v); Vis[v] = 1; nxt[v] = -1;
	while(! q.empty()){
		ll x = q.front(), f; q.pop();
		if(Vis[x]){
			printf("%lld\n", M[x] + Vis[x] - 2);
			int v = x;
			while(v != -1)stk[++ top] = v, v = pre[v];
			for(int i = top; i > 1; -- i){
				if((stk[i] + 1) % p == stk[i - 1])printf("1 ");
				else if((stk[i] + p - 1) % p == stk[i - 1])printf("2 ");
				else printf("3 ");
			}
			while(nxt[x] != -1){
				if((x + 1) % p == nxt[x])printf("1 ");
				else if((x + p - 1) % p == nxt[x])printf("2 ");
				else printf("3 ");
				x = nxt[x];
			}
			return 0;
		}
		if(!M[f = (x + 1) % p])q.push(f), M[f] = M[x] + 1, pre[f] = x;
		if(!M[f = (x + p - 1) % p])q.push(f), M[f] = M[x] + 1, pre[f] = x;
		if(!M[f = pw(x, p - 2)])q.push(f), M[f] = M[x] + 1, pre[f] = x;
		x = q2.front(); q2.pop();
		if(!Vis[f = (x + 1) % p])q2.push(f), Vis[f] = Vis[x] + 1, nxt[f] = x;
		if(!Vis[f = (x + p - 1) % p])q2.push(f), Vis[f] = Vis[x] + 1, nxt[f] = x;
		if(!Vis[f = pw(x, p - 2)])q2.push(f), Vis[f] = Vis[x] + 1, nxt[f] = x;
	}
	return 0;
}
```

---

## 作者：sp201613 (赞：1)

这道题其实难度并不大，是我一次模拟赛的题，~~尽管我在考试时没能A掉，而且还没得几分~~，我们看这道题，恐怕最暴力的思路就是bfs（~~甚至考场上我都没这么打，我太弱了~~）

在暴力的基础上，我们进行优化，其实不难发现，这道题仅需双向bfs即可,~~笑~~

这题走的时候有三种情况，+1，-1，求逆元，由于要输出过程，所以我们只需在双向bfs的过程中维护一下当前数的父亲，即当前数是由哪个数进行操作后得到的

//~~spyz201862提醒您，u==v时特判千万别忘QwQ~~

下面来看一下我的代码

```cpp
#pragma GCC optimize(2)
#include<cstdio>
#include<cctype>
#include<queue>
#include<map>
using namespace std;
#define rg register
typedef long long LL;
int u,v,mod,nw1,nw2,ans,anss[222],w;
map<int,int>vis1,vis2,fa,hw;
template<class T>inline void read(T &x)
{
    x=0;int f=0;char ch=getchar();
    while(!isdigit(ch)){f|=(ch=='-');ch=getchar();}
    while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=f?-x:x;
}
inline LL ksm(LL x,int y)
{
    LL res=1;
    while(y){
        if(y&1) res=(res*x)%mod;
        x=(x*x)%mod;
        y>>=1;
    }
    return (int)(res%mod);
}
inline void dl_bfs()
{
    queue<pair<int,int> >p,q;
    p.push(make_pair(u,0));q.push(make_pair(v,0));
    vis1[u]=vis2[v]=1;
    while(p.size()||q.size()){
        if(p.size()){
            int x=p.front().first,y=p.front().second,ii;
            p.pop();
            if(y>199) continue;
            ii=(x-1+mod)%mod;
            if(vis2[ii]){nw1=x;nw2=ii;w=2;break;}
            if(!vis1[ii]) vis1[ii]=1,fa[ii]=x,hw[ii]=2,p.push(make_pair(ii,y+1));
            ii=(x+1+mod)%mod;
            if(vis2[ii]){nw1=x;nw2=ii;w=1;break;}
            if(!vis1[ii]) vis1[ii]=1,fa[ii]=x,hw[ii]=1,p.push(make_pair(ii,y+1));
            ii=ksm((LL)x,mod-2);
            if(vis2[ii]){nw1=x;nw2=ii;w=3;break;}
            if(!vis1[ii]) vis1[ii]=1,fa[ii]=x,hw[ii]=3,p.push(make_pair(ii,y+1));
        }
        if(q.size()){
            int x=q.front().first,y=q.front().second,ii;
            q.pop();
            if(y>199) continue;
            ii=(x-1+mod)%mod;
            if(vis1[ii]){nw1=ii;nw2=x;w=1;break;}
            if(!vis2[ii]) vis2[ii]=1,fa[ii]=x,hw[ii]=1,q.push(make_pair(ii,y+1));
            ii=(x+1+mod)%mod;
            if(vis1[ii]){nw1=ii;nw2=x;w=2;break;}
            if(!vis2[ii]) vis2[ii]=1,fa[ii]=x,hw[ii]=2,q.push(make_pair(ii,y+1));
            ii=ksm((LL)x,mod-2);
            if(vis1[ii]){nw1=ii;nw2=x;w=3;break;}
            if(!vis2[ii]) vis2[ii]=1,fa[ii]=x,hw[ii]=3,q.push(make_pair(ii,y+1));
        }
    }
}
inline void search1(int x)
{
    if(x==u) return;
    search1(fa[x]);
    anss[++ans]=hw[x];
}
inline void search2(int x)
{
    if(x==v) return;
    anss[++ans]=hw[x];
    search2(fa[x]);
}
int main()
{
    read(u);read(v);read(mod);
    if(u==v){printf("0\n");return 0;}
    dl_bfs();
    search1(nw1);
    anss[++ans]=w;
    search2(nw2);
    printf("%d\n",ans);
    for(rg int i=1;i<=ans;++i) printf("%d ",anss[i]);
    printf("\n");
}
```


---

## 作者：maokaiyu (赞：0)

upd：有多余字符，希望通过。

[传送门](https://codeforces.com/problemset/problem/995/E)
## 思路
考虑直接建图，但由于点数过多所以使用折半搜索。
## 做法
从起点出发随机 $\sqrt{p}$ （取 $10000$）条长度为 $100$ 的路径，终点就是一直搜长度为 $100$ 的路径，我们所期望的是有两条路径的终点是一样的，然后拼起来。需要注意的是，在输出时有关终点的路径需要改为逆操作。
## AC Code
```cpp
#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)x.size()
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define be begin()
#define en end()
using namespace std;
typedef long long LL;
typedef int I;
I u,v,p;
unordered_map<I,vector<I>>r;
LL rp(LL a,LL b){
	LL res = 1;
	a %= p;
	for(;b;b >>= 1){
		if(b & 1) res *= a,res %= p;
		a *= a;
		a %= p;
	}
	return res;
}
//由于所建的图是随机的，所以根据生日悖论随机下去是可以搜到解的。 
I main(){
	scanf("%d%d%d",&u,&v,&p);
	if(u == v){//不用搜了 
		puts("0");
		return 0;
	}
	srand(time(0));
	vector<I>vec;
	for(I i = 1;i <= 10000;i++){//创建路径 
		I tmp = u;
		vec.clear();
		for(I j = 1;j <= 100;j++){
			I step = rand() % 3 + 1;//随机操作 
			if(step == 1) tmp = (tmp + 1) % p;
			else if(step == 2) tmp = (tmp + p - 1) % p;
			else tmp = rp(tmp,p - 2);
			vec.pb(step);//存下操作 
			if(!r[tmp].size()) r[tmp] = vec;
		}
	}
	for(;;){
		I tmp = v;//从终点开始搜索 
		vec.clear();
		for(I j = 1;j <= 100;j++){
			I step = rand() % 3 + 1;
			if(step == 1) tmp = (tmp + 1) % p;
			else if(step == 2) tmp = (tmp + p - 1) % p;
			else tmp = rp(tmp,p - 2);
			vec.pb(step);
			if(r[tmp].size()){//找到相遇点 
				printf("%d\n",SZ(r[tmp]) + SZ(vec));
				for(auto ans : r[tmp]){//输出路径 
					printf("%d ",ans);
				}
				reverse(all(vec));
				for(auto ans : vec){//对于从终点出发的路径需改为逆操作，即 1->2 2->1 3->3 
					printf("%d ",(ans == 3)? 3 : 3 - ans);
				}
				return 0;
			}			
		}
	}
	return 0;
} 
```

---

## 作者：Hanx16Kira (赞：0)

# Number Clicker

[Luogu CF995E](https://www.luogu.com.cn/problem/CF995E)

## Solution

尝试去找了一下三种操作之间有什么规律，然后发现确实没什么规律……

考虑构造一种操作，使它与题目要求的变化方式等价。由于存在逆元，所以我们将这个数表示成为 $\dfrac a b$。那么操作 $1$ 对应 $\dfrac {a+b}{b}$，操作 $2$ 对应 $\dfrac {a-b}{b}$，操作 $3$ 对应 $\dfrac b a$。发现这个操作很像辗转相除法，所以考虑使用更相减损法来做这道题。

因为操作 $1$ 和操作 $2$ 是可逆的，并且操作 $3$ 和操作 $3$ 也是可逆的，所以可以考虑将变换前的数 $u$ 和变换后的数 $v$ 都变换成为一个数字后然后将一个操作序列反过来。不妨将这个数字设成 $0$。那么就是运用更相减损法将 $u$ 和 $v$ 分别变成 $0$。

初始的 $a,b$ 并不好确认，所以可以直接随机 $a$ 的取值，然后计算 $b$。如果直接使用更相减损法可能会直接超时，所以可以先使用辗转相除法计算步数，如果总步数 $\le 200$ 就使用更相减损法构造答案。

复杂度 $\mathcal O(\text{松松松})$。

```cpp
// Cirno is not baka!
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (int)(b); ++i)
#define Rof(i, a, b) for (int i = (a); i >= (int)(b); --i)
#define All(x) x.begin(), x.end()
#define pii pair<int, int>
#define fi first
#define se second
#define i64 long long
#define mkp make_pair
// #define int long long
#define epb emplace_back
using namespace std;

const int _N = 1e6 + 5, inf = 1e9;
template<typename T> void Max(T &x, T y) {x = max(x, y);}
template<typename T> void Min(T &x, T y) {x = min(x, y);}
#ifdef CIRNO
template<typename T> void Debug(T x) {cerr << x << '\n';}
template<typename T, typename ...Args> void Debug(T x, Args ...args) {cerr << x << ' '; Debug(args...);}
template<typename T> void Debug(vector<T> v) {for (T x: v) cerr << x << ' '; cerr << '\n';}
#else
#define Debug(...)
#endif

namespace BakaCirno {
    mt19937 rnd(9);
    #define Rand(l, r) uniform_int_distribution<>(l, r)(rnd)
    int A, B, mod;
    int Calc(int a, int b) {
        if (b == 0) return 0;
        return Calc(b, a % b) + a / b + 1;
    }
    vector<int> GetPath(int a, int b) {
        vector<int> res;
        while (b) {
            if (a < b) res.epb(3), swap(a, b);
            else res.epb(2), a -= b;
        }
        return res;
    }
    void _() {
        cin >> A >> B >> mod;
        while (true) {
            int v1 = Rand(1, mod - 1), v2 = Rand(1, mod - 1);
            if (Calc(1ll * v1 * A % mod, v1) + Calc(1ll * v2 * B % mod, v2) <= 200) {
                vector<int> r1 = GetPath(1ll * v1 * A % mod, v1),
                            r2 = GetPath(1ll * v2 * B % mod, v2);
                reverse(All(r2));
                cout << r1.size() + r2.size() << '\n';
                for (int x: r1) cout << x << ' ';
                for (int x: r2) cout << (x < 3 ? 3 - x : 3) << ' ';
                cout << '\n';
                break;
            }
        }
    }
}

void File(const string file) {
    freopen((file + ".in").c_str(), "r", stdin);
    freopen((file + ".out").c_str(), "w", stdout);
}
signed main() {
    // File("");
    cin.tie(0)->sync_with_stdio(0); int T = 1;
    // cin >> T;
    while (T--) BakaCirno::_();
}
```

---

## 作者：Nuisdete (赞：0)

发现逆元这个操作也没有什么特别特殊的性质，求个逆元相当于随机整了个数了，因此 $3$ 操作相等于随机取个数。

按照操作建个图，在图上随机游走。

但是这个东西效率太低，发现 $1$ 操作和 $2$ 操作互为可逆操作，$3$ 操作自身可逆，因此可以直接 `meet-in-the-middle`，然后两边的长度限制都设为 $100$ 就行了。

根据生日悖论，期望约 $\sqrt p$ 次就会出现相等的情况，为了确保正确可以设为 $10^5 \sim 10^6$。

```cpp
# include <cstdio>
# include <vector>
# include <random>
# include <ctime>
# include <cstdlib>
# include <cassert>
# include <algorithm>
# include <unordered_map>

# define int long long

std::mt19937 Gen(time(nullptr) ^ std::random_device()());

int p;

int fpow(int x, int k) {
	int res = 1;
	for (; k; k >>= 1) {
		if (k & 1) res = res * x % p;
		x = x * x % p;
	}
	return res;
}

std::unordered_map<int, int> mp, mp2;

void solve(int v, int pre, int dis) {
	if (dis > 100 || mp2[v]) return;
	mp2[v] = pre;
	if (mp[v]) {
		std::vector<int> vec;
		for (int x = v; ~mp[x]; x = mp[x] == 1 ? (x + p - 1) % p : (mp[x] == 2 ? (x + 1) % p : fpow(x, p - 2))) vec.push_back(mp[x]);
		std::reverse(vec.begin(), vec.end());
		if (mp2[v]) for (int x = v; ~mp2[x]; x = mp2[x] == 1 ? (x + p - 1) % p : (mp2[x] == 2 ? (x + 1) % p : fpow(x, p - 2))) vec.push_back(mp2[x] == 3 ? 3 : (mp2[x] == 2 ? 1 : 2));
		printf("%zu\n", vec.size());
		for (int k : vec) printf("%lld ", k);
		exit(0);
	}
	std::vector<int> vec = { 1, 2, 3 };
	std::shuffle(vec.begin(), vec.end(), Gen);
	for (int k : vec) solve(k == 1 ? (v + 1) % p : (k == 2 ? (v + p - 1) % p : fpow(v, p - 2)), k, dis + 1);
}

int v;

void dfs(int u, int pre, int dis) {
	if (mp.size() > 3e5) solve(v, -1, 0), assert(false);
	if (dis > 100 || mp[u]) return;
	mp[u] = pre;
	std::vector<int> vec = { 1, 2, 3 };
	std::shuffle(vec.begin(), vec.end(), Gen);
	for (int k : vec) dfs(k == 1 ? (u + 1) % p : (k == 2 ? (u + p - 1) % p : fpow(u, p - 2)), k, dis + 1);
}

int u;

signed main() {
	
	scanf("%lld %lld %lld", &u, &v, &p);
	dfs(u, -1, 0), solve(v, -1, 0); assert(false);
	
	return 0;
}
```

---

## 作者：AlexandreLea (赞：0)

## 题目大意

给出三个数字 $u,v,p$，你可以对 $u$ 做如下三件事情之一：

+ $u\leftarrow (u+1)\bmod p$
+ $u\leftarrow (u-1+p)\bmod p$
+ $u\leftarrow (u)^{-1}\bmod p$（乘法逆元）

求 $u$ 用最小多少步可以变成 $v$。

## 题目思路

众所周知，一个数的倒数的倒数是其本身，那么对于乘法逆元，我们就有

$$x^{p-2}\equiv x^{-1}\pmod p$$

上面这是费马小定理。因而，我们就有

$$(x^{p-2})^{p-2}\equiv (x^{-1})^{-1}\equiv x\pmod p$$

这样我们就可以应用双向广搜，找到交点，即

![](https://cdn.luogu.com.cn/upload/image_hosting/md0gd916.png)

而代码的难处就在于节省代码，这里使用一个函数来计算下一个需要的数值。

我们可以记录所有数值中找到它的上一个数值，而后递归求出第一个数值而后动态判断变换方式。

在找出答案的操作方式后我们需要分开计算绿黄两条链。

代码如下。

```cpp
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#pragma GCC optimize(2)
using namespace std;
int mul(int a,int b,int p){
    int ans=0;
    for(;b;a=a*2%p,b>>=1) if(b&1) ans=(ans+a)%p;
    return ans;
}
int pow(int a,int b,int p){
    int ans=1;
    for(;b;a=mul(a,a,p),b>>=1) if(b&1) ans=mul(ans,a,p);
    return ans;
}
int fn(int x,int p,int ty){
    if(ty==0) return (x+1+p)%p;
    else if(ty==1) return (x-1+p)%p;
    else return pow(x,p-2,p);
}
int ces(int x,int y,int p){
    if(fn(x,p,0)==y) return 1;
    else if(fn(x,p,1)==y) return 2;
    else return 3;
}
int main(){
    int u,v,p,ni,co;
    map<int,int> from,fa,stp;
    queue<int> que;
    vector<int> ans;

    cin>>u>>v>>p;
    
    if(u==v){
        cout<<0<<endl;
        return 0;
    }
    from[u]=1,from[v]=2;
    fa[u]=u,fa[v]=v;
    stp[u]=0,stp[v]=1;
    que.push(u),que.push(v);
    while(!que.empty()){
        int nw=que.front();que.pop();
        bool got=false;
        for(int o=0;o<3;o++){
            int xt=fn(nw,p,o);
            if(from[xt]==from[nw]) continue;
            if(from[xt]+from[nw]==3){
                ni=xt,co=nw;
                got=true;
                break;
            }
            from[xt]=from[nw];
            stp[xt]=stp[nw]+1;
            fa[xt]=nw;
            que.push(xt);
        }
        if(got) break;
    }

    cout<<stp[ni]+stp[co]<<endl;
    if(from[ni]==1&&from[co]==2){
        // u---ni-co---v
        while(fa[ni]!=ni) ans.push_back(ni),ni=fa[ni];
        ans.push_back(ni);
        reverse(ans.begin(),ans.end());
        ans.push_back(co);
        while(fa[co]!=co) ans.push_back(fa[co]),co=fa[co];
    }else{
        // u---co-ni---v
        while(fa[co]!=co) ans.push_back(co),co=fa[co];
        ans.push_back(co);
        reverse(ans.begin(),ans.end());
        ans.push_back(ni);
        while(fa[ni]!=ni) ans.push_back(fa[ni]),ni=fa[ni];
    }
    for(int i=0;i<ans.size()-1;i++) cout<<ces(ans[i],ans[i+1],p)<<" ";
    return 0;
}
```

**EOF**

---

## 作者：Night_Bringer (赞：0)

[博客园体验更佳](https://www.cnblogs.com/C202202chenkelin/p/14507927.html)
# 题目大意
给定两个数 $u$ ， $v$ 。有三种操作：
1. $u=u+1(mod$ $p)$ 。
2. $u=u+p−1(mod$ $p)$ 。
3. $u=u^{p−2}(mod$ $p)$ 。

# 思路
## BFS
状态太多导致队列装不下。
## 迭代加深
$TLE$ ，浪费了太多时间在每一层上，没有记忆化且状态很多。
## IDA*
不行，无法得出乐观估价函数。
## 双向BFS
这样会将步数很为两半，状态相较于普通的 $BFS$ 会少很多。

先来看操作一和操作二，他们的关系是可以互逆的。一个对于原数 $+1$ ，另一个对于原数 $-1$ 。

操作三和操作三是互逆的，由费马小定理可知：若 $p$ 为质数，则 $a^{p-1}≡1(mod$ $p)$。

可得出：$(u^{p-2})^{p-2}≡u^{(p-2)(p-2)}≡u^{(p-1)(p-3)+1}≡(u^{p-1})^{p-3}u≡u(mod$ $p)$

那么就分别由开始状态与结束状态来向中间推进。
# Code
```cpp
#include <map>
#include <queue>
#include <cstdio>
#include <iostream>
using namespace std;
struct Status {//队列中保存的状态
	int step, number, flag;//分别是：步数，当前状态的数，正向或者反向
	Status() {}
	Status(int S, int N, int F) {
		step = S;
		number = N;
		flag = F;
	}
};
const int MAXN = 1e6 + 5;
queue<Status> q;
map<int, int> real;
bool vis[2][MAXN];//是否访问过
int dis[2][MAXN];//步数
pair<int, int> pre[2][MAXN];//first记录前一个数的哈希值，second记录操作的序号
int u, v, p;
int tot;
int Quick_Pow(int fpx, int fpy) {//快速幂
	long long res = 1;
	long long x = fpx;
	long long y = fpy;
	while(y) {
		if(y & 1)
			res = (res * x) % p;
		x = (x * x) % p; 
		y >>= 1;
	}
	int ans = res;
	return ans;
}
int Get_Hash(int x) {//map映射假哈希
	map<int, int>::iterator it = real.find(x);
	if(it != real.end())
		return (*it).second;
	real[x] = ++tot;
	return tot;
}
void Print(int x, int y) {//输出路径：记录每个前缀
	if(y == -1)
		return;
	if(!x) {//前半部分倒着输出
		if(pre[x][y].first != -1) {
			Print(x, pre[x][y].first);
			printf("%d ", pre[x][y].second);
		}
	}
	else {//后半部分正着输出
		if(pre[x][y].first != -1) {
			printf("%d ", pre[x][y].second);
			Print(x, pre[x][y].first);
		}
	}
}
void DoubleBfs() {
	int tmp;
	q.push(Status(0, u, 0));//初始化两个状态
	q.push(Status(0, v, 1));
	tmp = Get_Hash(u);
	vis[0][tmp] = 1;
	pre[0][tmp].first = -1;
	tmp = Get_Hash(v);
	vis[1][tmp] = 1;
	pre[1][tmp].first = -1;
	while(!q.empty()) {
		Status now = q.front();
		q.pop();
		int skt = Get_Hash(now.number);
		if(vis[!now.flag][skt]) {//碰头了输出并跳出
			printf("%d\n", dis[!now.flag][skt] + dis[now.flag][skt]);
			if(pre[0][skt].first != -1) {
				Print(0, pre[0][skt].first);
				printf("%d ", pre[0][skt].second);
			}
			if(pre[1][skt].first != -1) {
				printf("%d ", pre[1][skt].second);
				Print(1, pre[1][skt].first);
			}
			return;
		}
		Status next = now;
		next.step++;
		next.number = (next.number + 1) % p;
		tmp = Get_Hash(next.number);
		if(!vis[now.flag][tmp]) {//没有被访问则访问
			vis[now.flag][tmp] = 1;
			dis[now.flag][tmp] = next.step;
			pre[now.flag][tmp].first = skt;
			if(now.flag)
				pre[now.flag][tmp].second = 2;//若是倒着的，则该操作为1
			else
				pre[now.flag][tmp].second = 1;//若是正着的，则该操作为2
			q.push(next);
		}
		next = now;
		next.step++;
		next.number = (next.number + p - 1) % p;
		tmp = Get_Hash(next.number);
		if(!vis[now.flag][tmp]) {//同上
			vis[now.flag][tmp] = 1;
			dis[now.flag][tmp] = next.step;
			pre[now.flag][tmp].first = skt;
			if(now.flag)
				pre[now.flag][tmp].second = 1;
			else
				pre[now.flag][tmp].second = 2;
			q.push(next);
		}
		next = now;
		next.step++;
		next.number = Quick_Pow(next.number, p - 2) % p;
		tmp = Get_Hash(next.number);
		if(!vis[now.flag][tmp]) {//同上
			vis[now.flag][tmp] = 1;
			dis[now.flag][tmp] = next.step;
			pre[now.flag][tmp].first = skt;
			pre[now.flag][tmp].second = 3;//自己的逆操作就是自己
			q.push(next);
		}
	}
}
int main() {
	scanf("%d %d %d", &u, &v, &p);
	DoubleBfs();
	return 0;
}
```

---

