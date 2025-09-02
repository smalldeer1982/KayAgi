# Need for Pink Slips

## 题目描述

After defeating a Blacklist Rival, you get a chance to draw $ 1 $ reward slip out of $ x $ hidden valid slips. Initially, $ x=3 $ and these hidden valid slips are Cash Slip, Impound Strike Release Marker and Pink Slip of Rival's Car. Initially, the probability of drawing these in a random guess are $ c $ , $ m $ , and $ p $ , respectively. There is also a volatility factor $ v $ . You can play any number of Rival Races as long as you don't draw a Pink Slip. Assume that you win each race and get a chance to draw a reward slip. In each draw, you draw one of the $ x $ valid items with their respective probabilities. Suppose you draw a particular item and its probability of drawing before the draw was $ a $ . Then,

- If the item was a Pink Slip, the quest is over, and you will not play any more races.
- Otherwise, 
  1. If $ a\leq v $ , the probability of the item drawn becomes $ 0 $ and the item is no longer a valid item for all the further draws, reducing $ x $ by $ 1 $ . Moreover, the reduced probability $ a $ is distributed equally among the other remaining valid items.
  2. If $ a > v $ , the probability of the item drawn reduces by $ v $ and the reduced probability is distributed equally among the other valid items.

For example,

- If $ (c,m,p)=(0.2,0.1,0.7) $ and $ v=0.1 $ , after drawing Cash, the new probabilities will be $ (0.1,0.15,0.75) $ .
- If $ (c,m,p)=(0.1,0.2,0.7) $ and $ v=0.2 $ , after drawing Cash, the new probabilities will be $ (Invalid,0.25,0.75) $ .
- If $ (c,m,p)=(0.2,Invalid,0.8) $ and $ v=0.1 $ , after drawing Cash, the new probabilities will be $ (0.1,Invalid,0.9) $ .
- If $ (c,m,p)=(0.1,Invalid,0.9) $ and $ v=0.2 $ , after drawing Cash, the new probabilities will be $ (Invalid,Invalid,1.0) $ .

You need the cars of Rivals. So, you need to find the expected number of races that you must play in order to draw a pink slip.

## 说明/提示

For the first test case, the possible drawing sequences are:

- P with a probability of $ 0.6 $ ;
- CP with a probability of $ 0.2\cdot 0.7 = 0.14 $ ;
- CMP with a probability of $ 0.2\cdot 0.3\cdot 0.9 = 0.054 $ ;
- CMMP with a probability of $ 0.2\cdot 0.3\cdot 0.1\cdot 1 = 0.006 $ ;
- MP with a probability of $ 0.2\cdot 0.7 = 0.14 $ ;
- MCP with a probability of $ 0.2\cdot 0.3\cdot 0.9 = 0.054 $ ;
- MCCP with a probability of $ 0.2\cdot 0.3\cdot 0.1\cdot 1 = 0.006 $ .

 So, the expected number of races is equal to $ 1\cdot 0.6 + 2\cdot 0.14 + 3\cdot 0.054 + 4\cdot 0.006 + 2\cdot 0.14 + 3\cdot 0.054 + 4\cdot 0.006 = 1.532 $ .For the second test case, the possible drawing sequences are:

- P with a probability of $ 0.4 $ ;
- CP with a probability of $ 0.4\cdot 0.6 = 0.24 $ ;
- CMP with a probability of $ 0.4\cdot 0.4\cdot 1 = 0.16 $ ;
- MP with a probability of $ 0.2\cdot 0.5 = 0.1 $ ;
- MCP with a probability of $ 0.2\cdot 0.5\cdot 1 = 0.1 $ .

So, the expected number of races is equal to $ 1\cdot 0.4 + 2\cdot 0.24 + 3\cdot 0.16 + 2\cdot 0.1 + 3\cdot 0.1 = 1.86 $ .

## 样例 #1

### 输入

```
4
0.2 0.2 0.6 0.2
0.4 0.2 0.4 0.8
0.4998 0.4998 0.0004 0.1666
0.3125 0.6561 0.0314 0.2048```

### 输出

```
1.532000000000
1.860000000000
5.005050776521
4.260163673896```

# 题解

## 作者：5ab_juruo (赞：4)

根据题意，我们要不停抽卡，直到抽到粉色卡~~金色传说~~才停。每次抽卡后概率都会减少 $v$（如果小于 $v$ 则减到 $0$），求抽到粉色卡的期望步数。

我们发现 $v$ 不小，减少 10 次就会变成 $0$，所以我们可以爆搜，每次枚举抽到的卡及其概率，然后模拟概率变化就可以了。

需要注意一下精度问题，其他就是大分类了。

```cpp
#include <iostream>
using namespace std;
 
typedef long long ll;
typedef double db;
 
db v;
const db eps = 1e-10;
 
db dfs(db c, db m, db p)
{
	db ret = 0;
	
	if (c > v)
	{
		if (m > eps)
			ret += c * dfs(c - v, m + v / 2, p + v / 2);
		else
			ret += c * dfs(c - v, 0, p + v);
	}
	else if (c > eps)
	{
		if (m > eps)
			ret += c * dfs(0, m + c / 2, p + c / 2);
		else
			ret += c;
	}
	
	if (m > v)
	{
		if (c > eps)
			ret += m * dfs(c + v / 2, m - v, p + v / 2);
		else
			ret += m * dfs(0, m - v, p + v);
	}
	else if (m > eps)
	{
		if (c > eps)
			ret += m * dfs(c + m / 2, 0, p + m / 2);
		else
			ret += m;
	}
	
	return ret + 1;
}
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int cas;
	db c, m, p;
	
	cin >> cas;
	while (cas--)
	{
		cin >> c >> m >> p >> v;
		cout.precision(9);
		cout << dfs(c, m, p) << endl;
	}
	
	return 0;
}
```

---

## 作者：言琢დ (赞：1)

### Need for Pink Slips

这道题其实就是根据题意模拟即可，唯一造成困扰的可能就是题面是英文的。当然，如果你的数学期望学的不是很好，可能也会遇到一些棘手的问题。

---

### 题意

首先我们需要彻底搞清楚题意，因此我在这里为题意中的例子添加了说明，如果已经看懂题意的小伙伴，可以直接去看分析。

- 如果 $(c,m,p)=(\red{0.2},0.1,0.7),v=0.1$，且你抽到了 $\tt C$，抽奖后 $(c,m,p)=(\red{0.1},0.15,0.75)$。

	说明：由于 $c>v$，因此 $c\leftarrow c-v$，因此 $c=0.2-0.1=0.1$，其余两个 $m\leftarrow m+\dfrac{v}{2}$，$p\leftarrow p+\dfrac{v}{2}$，因此 $m=0.1+\dfrac{0.1}{2}=0.15$，$p=0.7+\dfrac{0.1}{2}=0.75$。

- 如果 $(c,m,p)=(\red{0.1},0.2,0.7),v=0.2$，且你抽到了 $\tt C$，抽奖后 $(c,m,p)=(\red{0},0.25,0.75)$，$\tt C$ 将失效。

	说明：由于 $c<v$，因此 $c\leftarrow 0$，其余两个 $m\leftarrow m+\dfrac{c}{2}$，$p\leftarrow p+\dfrac{c}{2}$，因此 $m=0.2+\dfrac{0.1}{2}=0.25$，$p=0.7+\dfrac{0.1}{2}=0.75$。

- 如果 $(c,m,p)=(\red{0.2},0,0.8),v=0.1$，且你抽到了 $\tt C$，抽奖后 $(c,m,p)=(\red{0.1},0,0.9)$。

	说明：由于 $c>v$，因此 $c\leftarrow c-v$，而 $m=0$ 因此 $p\leftarrow p+v$，最终 $c=0.2-0.1=0.1$，$p=0.8+0.1=0.9$。

- 如果 $(c,m,p)=(\red{0.1},0,0.9),v=0.2$，且你抽到了 $\tt C$，抽奖后 $(c,m,p)=(\red{0},0,1)$，$\tt C$ 将失效。

	说明：由于 $c<v$，因此 $c\leftarrow 0$，而 $m=0$ 因此 $p\leftarrow p+c$，最终 $c=0$，$p=0.9+0.1=1$。
    
### 分析

首先需要注意浮点数判断相等，需要用到 `fabs` 绝对值函数，格式形如：`fabs(x - y) < eps` 判断 `x == y`。

其次，我们设 `go(c, m, p, t)` 表示状态为 $c$，$m$，$p$ 时抽奖次数的期望，其中 $t$ 表示已经走过的抽奖次数。

接着按次序，首先判断 $c$ 和 $m$ 是否为零，然后按照题意模拟进行分配即可。

具体操作细节详见代码，有详细的注释。

### 参考代码

```cpp
const double eps = 1e-12;
bool equal(double x, double y){
  return fabs(x - y) < eps; // 浮点数比较大小，判断两个数是否相等
}
double v; // 不稳定性，由于 v >= 0.1 可以证明抽奖次数不会很大，也就是说暴力 dfs 的复杂度有保障
double go(double c, double m, double p, double t){
  if (equal(p, 1)) return t; // 中奖率 100 %
  double ans = 0;
  if (!equal(c, 0))
    if (c <= v)
      if (equal(m, 0)) ans += c * go(0, 0, 1, t+1); // c 给 t
  else ans += c * go(0, m + c / 2, p + c / 2, t+1); // c 均分给 m 和 t
  else
    if (equal(m, 0)) ans += c * go(c - v, 0, p + v, t+1); // c 按 v 给 p
  else ans += c * go(c - v, m + v / 2, p + v / 2, t+1); // c 按 v 均分
  if (!equal(m, 0))
    if (m <= v)
      if (equal(c, 0)) ans += m * go(0, 0, 1, t+1); // m 给 p
  else ans += m * go(c + m / 2, 0, p + m / 2, t+1); // m 均分给 c 和 t
  else
    if (equal(c, 0)) ans += m * go(0, m - v, p + v, t+1); // m 按 v 给 p
  else ans += m * go(c + v / 2, m - v, p + v / 2, t+1); // m 按 v 均分给 c 和 t
  ans += p * t; // 直接抽中 p
  return ans;
}
int main(){
  int T = init();
  while (T--) {
    double c, m, p;
    scanf("%lf%lf%lf%lf", &c, &m, &p, &v);
    printf("%.12lf\n", go(c, m, p, 1));
  }
}
```

---

## 作者：sto__Liyhzh__orz (赞：1)

#### [传送门：](https://www.luogu.com.cn/problem/CF1543C)

大致意思：你一直抽卡，直到抽到 `Pink Slips` 时停止抽卡。

抽完卡后，概率值（我用 $x$ 表示）会减少 $v$，若此时 $x\le0$，则 $x \gets 0$。

$v$ 并不大，减一二十次就为 $0$ 了，所以我们可以用爆搜。

注意精度问题！！

~~代码就不贴了，怕某些人抄。~~

---

## 作者：liuli688 (赞：0)

### 思路
看到样例解释，首先想到 DFS。一个是因为这里 $0.1 \le v \le 0.9$，因此概率下降的非常快，可以在最多 $10$ 次内变成 $0$；另一个是抽卡的过程本身就很像搜索，  一次没抽到就再来一次。

这题的细节还是比较多的，要注意以下几点：
- 一旦一个物品的概率被降为 $0$，那么它就不能再获得均摊到的概率了（也就是说这个物品就彻底抽不到了）。
- 如果一个物品的概率被降为 $0$，别的物品会把概率全部吸过去。

DFS 的状态设计也比较麻烦，我为了方便用了五维，分别是三个物品的概率、走到这个状态的概率和抽奖轮数。其实三个物品的概率只需要两个变量即可。
### 代码
```cpp
#include <algorithm>
#include <iostream>
#include <iomanip>
using std::cin;
using std::cout;

int T;
double c, m, p, v, ans;

void dfs(double c, double m, double p, double P, int step)
{
    if (c > 1e-6)
    	dfs(std::max(c - v, 0.0), m + (m < 1e-6 ? 0 : std::min(c, v) / 2), p + std::min(c, v) / 2 * ((m < 1e-6) + 1), P * c, step + 1);
    if (m > 1e-6)
    	dfs(c + (c < 1e-6 ? 0 : std::min(m, v) / 2), std::max(m - v, 0.0), p + std::min(m, v) / 2 * ((c < 1e-6) + 1), P * m, step + 1);
    ans += P * p * step;
}

signed main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
    for (cin >> T; T--; )
    {
		cin >> c >> m >> p >> v;
        ans = 0;
        dfs(c, m, p, 1, 1);
        cout << std::fixed << std::setprecision(12) << ans << '\n';
    }
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF1543C Need for Pink Slips
## 题意
给定 $c,m,p,v$ 四个实数 $(c+m+p=1)$，代表选择 $C,M,P$ 三个奖品分别被选择的概率和选择系数。每次选择如果选择 $P$ 则游戏结束，否则把对应的概率减去 $\min(v,c/m)$ 并把概率平均分给另外不为 $0$ 的奖品中。问期望多少次能够游戏结束。
## 颇具细节的模拟
根据题目要求，如果没有被选完，每次 $p$ 都会增加 $\frac{v}{2}$，而如果被选完，则每次会增加 $v$。所以直接根据题目模拟爆搜是肯定在时间允许范围内的。\
至于这道题的细节方面，由于 `c++` 存在严重的精度问题，所以判断的时候需要加入一个极小误差量进行比较。
## code
```cpp
#include<bits/stdc++.h>
using namespace std;
using ld=long double;
const ld two=2.0;
const ld eps=1e-9;
ld c,m,p,v;
bool vis[3];
ld E(ld C,ld M,ld P){
    ld res=0;
    if(C>eps){
        ld del=min(C,v);
        if(del>=C-eps)vis[0]=0;
        if(!vis[1])res+=C*(E(C-del,M,P+del))+C;
        else res+=C*(E(C-del,M+del/two,P+del/two))+C;
        vis[0]=1;
    }
    if(M>eps){
        ld del=min(M,v);
        if(del>=M-eps)vis[1]=0;
        if(!vis[0])res+=M*(E(C,M-del,P+del))+M;
        else res+=M*(E(C+del/two,M-del,P+del/two))+M;
        vis[1]=1;
    }
    if(P>eps){
        res+=P;
    }
    return res;
}
void solve(){
    vis[0]=vis[1]=vis[2]=1;
    cin>>c>>m>>p>>v;
    printf("%.10Lf\n",E(c,m,p));
}
signed main(){
    int T;cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：a_blue_cell (赞：0)

这道题就是要求你一直抽卡，直到抽到粉卡（~~然后歪了~~）。再抽卡的过程中，每一种卡被抽到的概率还会有所变化，具体变化[见原题](https://www.luogu.com.cn/problem/CF1543C)。

我们发现，$v$ 的最小值为 $0.1$，说明整个抽卡的流程中，抽卡次数最多也只有 $15$ 次左右，完全可以爆搜。

我们可以在将以下五个参数传入搜索中：三种卡被抽中的概率 $a,b,c$，抽到这一步时一共抽了几次卡 $step$ 以及抽到这一步时的概率 $sum$，每一次将 $c\times step\times sum$ 累加给答案，然后按照题意更新每一个参数即可。**注意精度**。

代码：

```cpp
#include<cmath>
#include<cstdio>
#define int long long
using namespace std;
double a,b,c,v,ans;
const double lep=1e-10;
int T;
void dfs(double x,double y,double z,int s,double sum){
	ans+=sum*z*s;
	double xx=x,yy=y,zz=z,tot=sum;
	sum*=x;//假设抽到了第一种卡
	if(x>=v){//按照题意更新概率即可
		if(y>=lep){
			y+=v/2;
		}
		if(y>=lep){
			z+=v/2;
		}else{
			z+=v;
		}
		x-=v;
	}else if(x>=lep){
		if(y>=lep){
			y+=x/2;
		}
		if(y>=lep){
			z+=x/2;
		}else{
			z+=x;
		}
		x=0;
	}
	/*
	判断：如果“抽到第一张卡”这个操作不合法，也就是抽到第一张卡的概率降为了0，那么，抽到第三张卡的概率是绝对不会变的。
	而如果抽到第三张卡的概率变了，说明抽到第一张卡的概率不为0，也就是这个说：这个操作是合法的，可以进行下一步搜索。
	*/
	if(zz!=z){
		dfs(x,y,z,s+1,sum); 
	}
	x=xx,y=yy,z=zz,sum=tot;
	//同理，假设抽到了第二种卡
	sum*=y;
	if(y>=v){
		if(x>=lep){
			x+=v/2;
		}
		if(x>=lep){
			z+=v/2;
		}else{
			z+=v;
		}
		y-=v;
	}else if(y>=lep){
		if(x>=lep){
			x+=y/2;
		}
		if(x>=lep){
			z+=y/2;
		}else{
			z+=y;
		}
		y=0;
	}
	if(zz!=z){
		dfs(x,y,z,s+1,sum);
	}
}
signed main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lf%lf%lf%lf",&a,&b,&c,&v);
		dfs(a,b,c,1,1);
		printf("%.12lf\n",ans);
		ans=0;
	}
	return 0;
}
```

---

