# [HBCPC2024] LCMs

## 题目描述

Walk Alone 有一个数轴，上面只有正整数。从整数 $a$ 走到整数 $b$ 的代价是 ${\rm lcm}(a, b)$，其中 ${\rm lcm}(a, b)$ 表示整数 $a$ 和 $b$ 的最小公倍数。由于对整数 $1$ 的厌恶，Walk Alone 禁止任何人移动到小于或等于 $1$ 的整数点上。

给定两个整数 $a$ 和 $b$，你需要计算从整数 $a$ 到 $b$ 的最小行走代价。

## 说明/提示

在第一个测试用例中，你可以选择这样的路径：$3 \to 2 \to 4$，总代价为 ${\rm lcm}(3, 2) + {\rm lcm}(2, 4) = 6 + 4 = 10$，这可以被证明是最小的。（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3
3 4
10 15
2 4```

### 输出

```
10
25
4```

# 题解

## 作者：luogu_gza (赞：4)

不妨设 $a<b$。

若 $a=b$，答案为 $0$。

否则，若 $a\mid b$，答案为 $b$，直接走过去即可。

否则，若 $\gcd(a,b)>1$，答案为 $a+b$，$a \to \gcd(a,b) \to b$ 即可。

否则，$\gcd(a,b)=1$，则挑选出 $a,\operatorname{minp}(a),2,\operatorname{minp}(b),b$ 五个数跑一下最短路即可。实际实现的时候采用了直接分类讨论。

[code](https://www.luogu.com.cn/record/171971036)。

要代码可以找我。

---

## 作者：Vct14 (赞：3)

题解代码没有分讨？我来交一发！

本场比赛最难的签到题。

题意：将整数 $x$ 变为整数 $y$ 代价为 $\operatorname{lcm}(x,y)$，求将 $a$ 变为 $b$ 的最小代价。注意：只能变为大于 $1$ 的整数。

---

先讨论两种简单的情况。

如果 $a=b$，则最小代价为 $0$。不动即可。

否则如果 $a\mid b$，则一次变化最优，最小代价为 $b$，否则若变化多次，最后一步的代价一定大于或等于 $b$。


---


否则如果 $\gcd(a,b)\ne1$。

若走一步，代价 $\operatorname{lcm}(a,b)$。

否则因为 $\operatorname{lcm}(x,y)\geqslant x$，第一步的代价一定大于或等于 $a$，最后一步的代价一定大于或等于 $b$，理论最小代价 $a+b$，要实现这个代价只能走两步。设途经的数为 $z$，第一步走需使得 $\operatorname{lcm}(a,z)=a$，第二步走需使得 $\operatorname{lcm}(z,b)=b$。即 $z$ 是 $a,b$ 的公因数，可以走 $a\to \gcd(a,b)\to b$ 实现。

设 $\gcd(a,b)=d,a=dx,b=dy,(x,y)=1$。则 $a+b=d(x+y)$，$\operatorname{lcm}(a,b)=dxy$。由于 $a<b$ 且 $a\nmid b$，有 $1<x<y,(x,y)=1$，因此 $(x-1)(y-1)>1$，即 $xy>x+y$。所以 $\operatorname{lcm}(a,b)>a+b$。最小代价为 $a+b$。

---

只剩下 $\gcd(a,b)=1$ 的情况。这种情况我们是走不到 $\gcd(a,b)$ 的。

如果走一步，代价 $\operatorname{lcm}(a,b)=ab$。

如果走多步，因为互质的两数的最小公倍数是它们的乘积，为了使代价尽量小，我们可以选择途经 $a$ 和 $b$ 的最小质因子 $\operatorname{minp}(a)$ 和 $\operatorname{minp}(b)$ 使乘积尽量小。

若途经的数 $z$ 与起点 $a'$ 和终点 $b'$ 都互质，代价为 $a'z+b'z$，我们可以选择途经 $2$ 使得代价最小。

整理一下最终情况。设 $p=\operatorname{minp}(a),q=\operatorname{minp}(b)$。

1. $a\to b$，代价 $ab$。
2. $a\to2\to b$，代价 $\operatorname{lcm}(a,2)+\operatorname{lcm}(b,2)$。
3. $a\to p\to b$，代价 $\operatorname{lcm}(a,p)+\operatorname{lcm}(p,b)=a+pb$。
4. $a\to q\to b$，代价 $\operatorname{lcm}(a,q)+\operatorname{lcm}(q,b)=aq+b$。
5. $a\to p\to 2\to b$，代价 $\operatorname{lcm}(a,p)+\operatorname{lcm}(p,2)+\operatorname{lcm}(b,2)=a+\operatorname{lcm}(p,2)+\operatorname{lcm}(b,2)$。
6. $a\to 2\to q\to b$，代价 $\operatorname{lcm}(a,2)+\operatorname{lcm}(q,2)+\operatorname{lcm}(q,b)=\operatorname{lcm}(a,2)+\operatorname{lcm}(q,2)+b$。
7. $a\to p\to q\to b$，代价 $\operatorname{lcm}(a,p)+\operatorname{lcm}(p,q)+\operatorname{lcm}(q,b)=a+pq+b$。
8. $a\to p\to2\to q\to b$，代价 $\operatorname{lcm}(a,p)+\operatorname{lcm}(p,2)+\operatorname{lcm}(q,2)+\operatorname{lcm}(q,b)=a+\operatorname{lcm}(p,2)+\operatorname{lcm}(q,2)+b$。

以上代价取最小值即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int lcm(int a,int b){
	return a/__gcd(a,b)*b;
}

int mnp(int a){
	for(int i=2; i*i<=a; i++) if(!(a%i)) return i;
	return a;
}

signed main(){
	int t;cin>>t;
	while(t--){
		int a,b;cin>>a>>b;
		if(a==b){
			cout<<0<<"\n";
			continue;
		}
		if(!(b%a)){
			cout<<b<<"\n";
			continue;
		} 
		if(__gcd(a,b)!=1){
			cout<<a+b<<"\n";
			continue;
		}
		int p=mnp(a),q=mnp(b);
		int a2=lcm(a,2),b2=lcm(2,b),p2=lcm(2,p),q2=lcm(2,q);
		cout<<min({a*b,a+p*b,a*q+b,a2+b2,a+p2+b2,a2+q2+b,a+p*q+qb,a+p2+q2+b})<<"\n";
	}
	return 0;
}
```

写晕了/yun，如果哪里有问题欢迎在评论区指出。

---

## 作者：是青白呀 (赞：2)

可以直接讨论，不用跑最短路。

不妨设 $a\leq b$。
- $a=b$ 时，答案为 $0$。
- $b\bmod a=0$ 时，答案为 $b$。
- 否则，至少要有两次转化，答案下界是 $a+b$。
    - 若 $\gcd(a,b)\neq 1$，可以取得下界 $a+b$，跳到 $\gcd$ 的位置即可。
	- 否则，一定会有一次贡献为两个互质的数的转化的操作，这个的代价是 $v_{xy}=\min(xy,2(x+y))$（要么直接转，要么选最小的数作为桥梁来转）。我们希望最小化这两个东西的乘积和加和，即在 $a$ 和 $b$ 的最小非 $1$ 因数（下简称“最小因数”）处取得。设 $a,b$ 的最小因数分别为 $x,y$，答案为 $a\times[a\neq x]+b\times [b\neq y]+v_{xy}$。

最后一部分的正确性证明：考虑分类讨论。首先我们选的一定是 $a$ 或 $b$ 的质因数，否则会带来无意义的因子。其次，对于不同的质数 $x,y$，$xy<2(x+y)$ 成立当且仅当 $x=3$，$y=5$。

- $a,b$ 均为质数时，答案显然最小。
- 下面设 $a,b$ 选取的因数（不要求最小）为 $x,y$。当 $a,b$ 中恰有一个质数时，不妨设为 $a$。若选 $y$，显然是选最小的因数，答案为 $2(a+y)+b$；若不选，则答案为 $2(a+b)$。显然有 $2y\leq b$，答案取得最小。对于 $v$ 取乘积值的情况，仅有选最小因数时，可能使答案进一步减小。因此答案为 $a\times[a\neq x]+b\times [b\neq y]+v_{xy}$ 时最小。
- 两者都不为质数时，若两者有至少一个不选因数，则根据上面的讨论可知答案最小为 $2(a+y)+b$（此时 $a$ 不选因数，$b$ 选因数）。若两边都选因数，则答案为 $a+b+2(x+y)$。根据上面的讨论可知 $2(x+y)+a\leq 2(a+y)$，特殊取值的情况同样只会使两边都取因数时的答案进一步减小。因此答案为 $a\times[a\neq x]+b\times [b\neq y]+v_{xy}$ 时最小。
```cpp
void solve(){
    read(a),read(b);
    if(a>b)swap(a,b);
    if(a==b)puts("0");
    else if(b%a==0)printf("%lld\n",b);
    else if(__gcd(a,b)!=1)printf("%lld\n",a+b);
    else{
        int res=0,x=a,y=b;
        rep(i,2,sqrt(a))
            if(a%i==0)x=min(x,i);
        rep(i,2,sqrt(b))
            if(b%i==0)y=min(y,i);
        if(x!=a)res+=a;
        if(y!=b)res+=b;
        res+=min(x*y,2*(x+y));
        printf("%lld\n",res);
    }
}

---

## 作者：Cary1075 (赞：1)

## 洛谷 P10869 LCMs
### 分析:
设两个整数分别为 $a$，$b$，且 $a \leq b$。
 
- 若 $a$，$b$ 两数相等，则从 $a$ 到 $b$ 无需移动，花费代价为 $0$。
 
- 若 $b$ 为 $a$ 的倍数，则花费代价为两数最大公倍数，即 $\operatorname{lcm}(a,b) = b$。

引理：存在一条最优路径 $P$ 使得路径上没有重复顶点。

证明：若某最优路径存在重复顶点，把回路剪掉，所得新路径仍连通 $a$ 与 $b$。回路内每条边的 $\operatorname{lcm}$ 都是正整数，因此删去回路后总代价严格减小，这与原路径最优矛盾；所以最优路径必为简单路径。

令最优简单路径上所有顶点都属于集合
$D = \{d \in \Z_{\ge 2} : d \mid \operatorname{lcm}(a,b) \}$。

设 $M = \operatorname{lcm}(a,b)$，它包含了路径可能出现的所有质因子。沿着从 $a$ 到 $b$ 的路径，每个质因子的指数变化模式只能是：
- 保持不变

- 先升后降（或先降后升）

如果所有质因子的变化都能在同一个中转点完成，就只需要一个中转点。

如果有些质因子的变化必须在另一个地方完成，那就需要两个中转点。

$2$ 是最小的允许整数，它的质因子集合是 $\{2\}$，所以：

- 经过 $2$，可以同时把所有其他质因子的指数降到 $0$。

- 从 $2$ 出发，再可以方便地引入需要的质因子。

令
$$S_1 = \min_{{v_1 \in D}} (\operatorname{lcm}(a, v_1) + \operatorname{lcm}(v_1, b))$$

$$S_2 = \min_{v_1, v_2 \in D} (\operatorname{lcm}(a, v_1) + \operatorname{lcm}(v_1, v_2) + \operatorname{lcm}(v_2, b))$$

$$S_3 = \min_{v_1, v_2 \in D} (\operatorname{lcm}(a, v_1) + \operatorname{lcm}(v_1, 2) + \operatorname{lcm}(2, v_2) + \operatorname{lcm}(v_2, b))$$

则题目要求的最小代价为：

$$ans = \min \{0 \; \text{if } a = b，b \; \text{if } a \mid b，S_1， S_2， S_3\}$$

 
::::info[建议]
- 使用 long long 存储数据，因为在 $\operatorname{lcm}(a,b)$ 的运算过程当中 $a \times b$ 可能会超过 int 的最大值 $2^{31} -1$。

- 使用 vector 数组更加灵活地存储 $a$，$b$ 可到达的点。

- 使用 algorithm 库自带的 $\gcd(a,b)$ 函数。
::::
::::warning[警告]
- 注意题目输入为多组测试样例。

- 特判输出 $0$ 的时候不要写 `break;` 或 `return 0;`，而要写 `continue;` 继续读取下一轮测试样例。

- 多组测试样例每轮记得要清空 vector 数组。
::::

### 代码:
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
long long a,b,x,y,ans,min1,min2,min3;//min1,min2,min3分别记录三种路径情况的最小值，ans记录最终答案
vector<int> a_point,b_point;//记录a与b的可选到达点
long long gcd(long long a,long long b){
	return (!b)?a:gcd(b,a%b);//最大公约数函数:使用辗转相除法+递归
}
long long lcm(long long a,long long b){
	return a*b/gcd(a,b);//最小公倍数函数
}
int main(){
	int T=1;//好习惯
	cin>>T;
	while(T--){
	    cin>>a>>b;
	    if(a==b){
	    	cout<<0<<endl;
	    	continue;
	    }
	    if(a>b) swap(a,b);
	    a_point.clear(),b_point.clear();
	    a_point.push_back(a);
	    a_point.push_back(2);
	    b_point.push_back(b);
	    b_point.push_back(2);
	    min1=min2=min3=ans=0;
	    for(int i=2;i*i<=a;i++){//从2到sqrt(a)枚举与a有公因数的点
	    	if(a%i==0){
	    		x=i,y=a/i;
	    		if(x!=1){//如果不为1就将这个点存入备选点数组
					a_point.push_back(x);	    			
				}
	    		if(y!=1){
	    			a_point.push_back(y);	
				}
	    	}
	    }
	    for(int i=2;i*i<=b;i++){//同理，从2到sqrt(b)枚举与b有公因数的点
	    	if(b%i==0){
	    		x=i,y=b/i;
	    		if(x!=1){
	    			b_point.push_back(x);	
				}
	    		if(y!=1){
	    			b_point.push_back(y);	
				}
	    	}
	    }
	    ans=lcm(a,b);//若两数呈倍数关系，最小花费为两数最大公倍数
	    for(auto v1:a_point){
	    	min1=lcm(a,v1)+lcm(v1,b);//a->v1->b
	    	ans=min(ans,min1);
	    	for(auto v2:b_point){
	    		min2=lcm(a,v1)+lcm(v1,v2)+lcm(v2,b);//a->v1->v2->b
	    		min3=lcm(a,v1)+lcm(v1,2)+lcm(2,v2)+lcm(v2,b);//a->v1->2->v2->b
	    		ans=min(ans,min(min2,min3));
	    	}
		} 
	    for(auto v1:b_point){//枚举b可到达的数,再从该数到达a
	    	min1=lcm(a,v1)+lcm(v1,b);
	    	ans=min(ans,min1);
	    	for(auto v2:a_point){
	    		min2=lcm(a,v1)+lcm(v1,v2)+lcm(v2,b);
	    		min3=lcm(a,v1)+lcm(v1,2)+lcm(2,v2)+lcm(v2,b);
	    		ans=min(ans,min(min2,min3));
	    	}
	    }
	    cout<<ans<<endl;
	}
    return 0;
}
```

---

## 作者：ZHR100102 (赞：1)

[Blog](https://www.cnblogs.com/zhr0102/p/18548924)

远古题解，格式可能有点丑/qd。

__________________

很好的数论和构造题。

显然我们不可以直接建图跑最短路。

于是考虑分讨。

# 倍数关系

答案显然为 $\max(a,b)$。

# 相等关系

答案显然为 $0$。

# $\gcd(a,b)>1$

我们可以先走到 $\gcd(a,b)$ 处，再到达 $b$，答案为 $a+b$。

# $\gcd(a,b)=1$

直接分讨不太好做，我们考虑用一点时间换取代码的简洁。

可以发现，我们中间会用到的点只有 $3$ 个：$minp_a,minp_b,2$，其中 $minp_x$ 表示数 $x$ 的最小质因数。

为什么要用最小的？因为既然 $a,b$ 已经互质，所以无论如何转化到哪一步它都是互质的，我们就要尽可能减小这一步中转的代价。这就是 $minp$ 的由来。

那么我们化为最小质因子后，就直接是两个数的积了吗？并不是，我们还可以发现这一个构造：$minp_a \to 2 \to minp_b$。可以让这一步的代价变为 $minp_a\times 2+minp_b \times 2$。并且其他数显然做这个中转点不优，因为 $a,b$ 已经是最小质因子了。

于是选这 $5$ 个点出来，跑 Floyd 即可。要是愿意写，写单源最短路也可以。

时间 $O(t \sqrt {n})$。

# 代码

```cpp
/*
1. 倍数关系，ans=max(a,b);
2. 相等关系，ans=0;
3. 互质关系，找出 a,b,minp_a,minp_b,2 这 5 个点跑最短路，因为要使分别的质因数最小（中转的代价最小），显然选其他质因数必定不优
4. 有公因数关系：走到 gcd 处，答案为 a+b;
时间 O(sqrt(n)t)
*/

#include <bits/stdc++.h>
#define fi first
#define se second
#define lc (p<<1)
#define rc ((p<<1)|1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pi;
int t;
ll d[10][10];
vector<int>g;
ll gcd(ll a,ll b)
{
    if(b==0)return a;
    return gcd(b,a%b);
}
ll lcm(ll a,ll b)
{
    return b/gcd(a,b)*a;
}
void floyd()
{
    for(int i=0;i<g.size();i++)
    {
        for(int j=0;j<g.size();j++)
        {
            d[i][j]=lcm(g[i],g[j]);
            if(i==j)d[i][j]=0;
        }
    }
    for(int k=0;k<g.size();k++)
    {
        for(int i=0;i<g.size();i++)
        {
            for(int j=0;j<g.size();j++)
            {
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
            }
        }
    }

}
void solve()
{
    ll a,b;
    cin>>a>>b;
    if(a>b)swap(a,b);
    if(a==b)cout<<0<<'\n';
    else if(b%a==0)cout<<b<<'\n';
    else if(gcd(a,b)>1)cout<<a+b<<'\n';
    else
    {
        int minp_a=1,na=a;
        for(int i=2;i<=a/i;i++)
        {
            if(na%i==0)
            {
                minp_a=i;
                break;
            }
        }
        if(minp_a==1)minp_a=a;
        int minp_b=1,nb=b;
        for(int i=2;i<=b/i;i++)
        {
            if(nb%i==0)
            {
                minp_b=i;
                break;
            }
        }
        if(minp_b==1)minp_b=b;
        g.clear();
        g.push_back(a);
        g.push_back(b);
        g.push_back(minp_a);
        g.push_back(minp_b);
        g.push_back(2);    
        floyd();
        cout<<d[0][1]<<'\n';    
    }
}

int main()
{
    //freopen("sample.in","r",stdin);
    //freopen("sample.out","w",stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--)solve();
    return 0;
}
```

---

## 作者：Your_Name (赞：1)

## 题意

从 $a$ 直接到 $b$ 要 ${\rm lcm}(a, b)$ 的花费，问从一点到另外一点的最小花费。

## 思路

可以发现：要使花费最小，我们能走的点只有四类，分别是：
* 2（即就算与当前点互质，代价也最小）
* $a$ 的最小因数（非 $1$）（即走后代价为 $a$）
* $b$ 的最小因数（非 $1$）（同理）
* $\gcd(a,b)$（即可以作为链接 $a$ 与 $b$ 的桥梁，代价为 $a$ 或 $b$ 或 $a + b$，但注意不能为 $1$）

这里解释一下为什么在 $a$ 与 $b$ 的因数中取最小的。

其实是因为 $a$ 或 $b$ 的因数一定是第一个被走的，那么他的代价就为起点本身，而且我们下一个要走的点就是另一个数的因数，或者 $\gcd(a,b)$。第一种情况中即便两数互质，代价也可以降到最低，第二种情况下 $a$ 的最小因数也必然小于等于 $\gcd(a,b)$，与第一种情况同理，且当他们不互质时代价就是 $\gcd(a,b)$。

剩下代码实现，只要把这几类点全部两两搭配，建图跑最短路就行，因为只需要单源，而且边数不多，跑什么都行，看自己。（当然也可以暴力手打每种情况取最小）

**记得每次建图之后要清空。**~~（多测不清空，亲人两行泪）~~

## AC Code

```cpp
#include <bits/stdc++.h>

using namespace std;
#define int long long
const int N = 1e4 + 10;//总共还没几个点，没必要开太大
int e[N], ne[N], w[N], h[N], dist[N], n, m, idx, a, b, t;//链式前向星存图
vector<int> x;//记录点
bool vis[N];
inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx++;
} 
inline int lcm(int a, int b){
    return (long long)a / __gcd(a, b) * b;
}
inline void build(){
    for(int i = 0; i < x.size(); i ++){
        for(int j = 0; j < x.size(); j ++){//正反都要
            if(i == j)continue;
            add(i, j, lcm(x[i], x[j]));//这里直接建i到j就可以，因为如果建x[i],x[j]的话，数组要开很大，每次清空会超时
        }
    }
}//建图
inline int spfa(int be, int ed)
{
    memset(dist, 0x3f, sizeof dist);
    dist[be] = 0;
    queue<int> q;
    q.push(be);
    vis[be] = 1;
    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        vis[t] = 0;
        for (int i = h[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!vis[j])
                {
                    vis[j] = 1;
                    q.push(j);
                }
            }
        }
    }
    return dist[ed];
}//板子
inline void work()
{
    x.clear();
    if (__gcd(a, b) != 1)
    {
        x.push_back(__gcd(a, b));//a，b最大公约数
    }
    memset(h, -1, sizeof h);
    memset(ne, 0, sizeof ne);
    memset(w, 0, sizeof w);
    memset(e, 0, sizeof e);
    memset(vis, 0, sizeof vis);
    idx = 0;//清空
    x.push_back(a), x.push_back(b), x.push_back(2);//a，b，2
    for (int i = 2; i * i <= a; i++)
    {
        if (a % i == 0)
        {
            x.push_back(i);//a最小因数
            break;
        }
    }
    for (int i = 2; i * i <= b; i++)
    {
        if (b % i == 0)
        {
            x.push_back(i);//b最小因数
            break;
        }
    }
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());//稍微处理一下
    build();//建图
    int posa;
    for(int i = 0; i < x.size(); i ++){
        if(x[i] == a){
            posa = i; //找到a在x数组里的位置
            break;
        }
    }
    cout << spfa(posa, x.size() - 1) << '\n';
    //这里的x.size() - 1其实就是b的位置，因为我们所有加的数都小于等于b，而且刚刚排了序
}
signed main()
{
    std::ios::sync_with_stdio(false);
    cin >> t;
    while (t--)
    {
        cin >> a >> b;
        work();
    }
    return 0;
}
```
 _完结撒花_

---

## 作者：Link_Cut_Y (赞：0)

赛时讨论了一堆东西，后来发现其实不用。

我们发现所有策略都只与下面有限个值有关：$p_a, p_b, a, b, 2$。其中 $p_i$ 表示 $i$ 的最小质因子。

在这些值之间建边，边权按照题目定义来。跑最短路即可。

注意如果这些值中有 $1$ 要提前排掉。

```cpp
int mn[N], p[N], cnt, g[6][6], n;
bool st[N];
#define pb push_back
int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
int lcm(int a, int b) { return a / gcd(a, b) * b; }
void init(int n) {
	rep(i, 2, n) {
		if (!st[i]) p[ ++ cnt] = i;
		for (int j = 1; j <= cnt and i * p[j] <= n; j ++ ) {
			st[i * p[j]] = 1; mn[i * p[j]] = p[j];
			if (i % p[j] == 0) break;
		}
	}
}
int minimum_path(int a, int b) {
	memset(g, 0x3f, sizeof g); vector<int> vec;
	vec.pb(a), vec.pb(b);
	if (mn[a] > 1) vec.pb(mn[a]);
	if (mn[b] > 1) vec.pb(mn[b]); vec.pb(2);
	rop(i, 0, vec.size()) rop(j, 0, vec.size())
		g[i][j] = g[j][i] = lcm(vec[i], vec[j]);
	int n = vec.size();
	rop(k, 0, n) rop(i, 0, n) rop(j, 0, n)
		if (i != j and i != k and j != k)
			g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	return g[0][1];
}
signed main() {
	init(N - 1);
	read(T); while (T -- ) {
		int a, b; read(a, b);
		if (a == b) { puts("0"); continue; }
		if (b % a == 0) { printf("%lld\n", b); continue; }
		if (gcd(a, b) != 1) { printf("%lld\n", a + b); continue; }
		printf("%lld\n", minimum_path(a, b));
	} return 0;
}
```

---

