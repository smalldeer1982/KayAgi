# Fight the Monster

## 题目描述

A monster is attacking the Cyberland!

Master Yang, a braver, is going to beat the monster. Yang and the monster each have 3 attributes: hitpoints ( $ HP $ ), offensive power ( $ ATK $ ) and defensive power ( $ DEF $ ).

During the battle, every second the monster's HP decrease by $ max(0,ATK_{Y}-DEF_{M}) $ , while Yang's HP decreases by $ max(0,ATK_{M}-DEF_{Y}) $ , where index $ Y $ denotes Master Yang and index $ M $ denotes monster. Both decreases happen simultaneously Once monster's $ HP<=0 $ and the same time Master Yang's $ HP>0 $ , Master Yang wins.

Master Yang can buy attributes from the magic shop of Cyberland: $ h $ bitcoins per $ HP $ , $ a $ bitcoins per $ ATK $ , and $ d $ bitcoins per $ DEF $ .

Now Master Yang wants to know the minimum number of bitcoins he can spend in order to win.

## 说明/提示

For the first sample, prices for $ ATK $ and $ DEF $ are extremely high. Master Yang can buy $ 99 $ HP, then he can beat the monster with $ 1 $ HP left.

For the second sample, Master Yang is strong enough to beat the monster, so he doesn't need to buy anything.

## 样例 #1

### 输入

```
1 2 1
1 100 1
1 100 100
```

### 输出

```
99
```

## 样例 #2

### 输入

```
100 100 100
1 1 1
1 1 1
```

### 输出

```
0
```

# 题解

## 作者：CountState (赞：1)

CF 决斗场，平局后才发现不寻常的数据范围。

首先，买完东西后，如果小 Y 的 ATK $\leq$ 小 M 的 DEF，那么小Y一定不能获胜，这种情况就不用讨论。

因为数据范围 $\leq 100$，所以有：

- 小 Y 最多买 $10000$ 点 HP，因为小 Y 的 ATK $>$ 小 M 的DEF，所以小 Y 最多 $100$ 回合即可胜利，在这 $100$ 回合内，小 Y 最多损失 $10000$ 点血量。

- 小 Y 最多买 $200$ 点 ATK，因为小 M 的 HP 最多为 $100$，DEF最多为 $100$，所以小 Y 的 ATK $=200$ 即可一击必杀，买更多的 ATK 没有用处。

- 小 Y 最多买 $100$ 点 ATK，因为小 M 的 ATK 最多为 $100$，DEF 最多为 $100$，所以小 Y 的 DEF $=100$ 即可防住全部攻击，买更多的 DEF 没有用处。

三层循环枚举每一种情况，循环 $2\times 10^8$ 次，加火车头可过。

```cpp
#include <bits/stdc++.h>
using namespace std;

int HPy,ATKy,DEFy,HPm,ATKm,DEFm,h,a,d,ans=INT_MAX;
int main(){
	cin>>HPy>>ATKy>>DEFy>>HPm>>ATKm>>DEFm>>h>>a>>d;
	for(int i=0;i<=10000;i++){
		for(int j=0;j<=200;j++){
			for(int k=0;k<=100;k++){
				//if(i!=0||j!=0||k!=0) continue;
				bool b1=true,b2=true;
				if(ATKm-(DEFy+k)<=0) b1=false;
				if((ATKy+j)-DEFm<=0) b2=false;
				if((!b1)&&b2)  ans=min(ans,i*h+a*j+d*k);
				else if(b1&&(!b2)) continue;
				else if((!b1)&&(!b2)) continue;
				else if(floor((double)(HPy+i)/(double)(ATKm-(DEFy+k))-0.000001)>=ceil((double)HPm/(double)((ATKy+j)-DEFm))) ans=min(ans,i*h+a*j+d*k);
				//cout<<floor((double)(HPy+i)/(double)(ATKm-(DEFy+k)))<<"\n";
			}
		}
	}
	cout<<ans<<"\n";
}


```

---

## 作者：ivyjiao (赞：1)

来源：CF 决斗场。

想了好几分钟没想出来平局了，然后到原站一看数据范围 $O(n^3)$ 能过……

我们能够发现，在小 Y 能够对 boss 造成伤害的情况下（即 $ATK_Y>DEF_M$）：

1. 当小 Y 有 $10000$ 点 HP 时，能稳赢 boss，因为 boss 每轮最多对小 Y 造成 $100$ 点伤害，而小 Y 每轮最少对 boss 造成 $1$ 点伤害，所以当小 Y 有 $10000$ 点 HP 时，能稳赢 boss。

1. 当小 Y 有 $200$ 点 ATK 时，能稳赢 boss，因为 boss 的 DEF 最多为 $100$，而小 Y 第一轮直接对 boss 造成 $200-100=100$ 点伤害秒杀 boss，所以当小 Y 有 $200$ 点 ATK 时，能稳赢 boss。

1. 当小 Y 有 $100$ 点 DEF 时，能稳赢 boss，因为 boss 的 ATK 最多为 $100$，而小 Y 能挡掉所有伤害，所以当小 Y 有 $100$ 点 DEF 时，能稳赢 boss。

所以运算次数为 $10^4\times (2\times 10^2)\times 10^2=2\times 10^8$，开个火车头就过了。

代码：

```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
using namespace std;
int ay,by,cy,am,bm,cm,a,b,c,ans=1e9;
int main(){
    cin>>ay>>by>>cy>>am>>bm>>cm>>a>>b>>c;
    for(int i=0;i<=10000;i++){
        for(int j=0;j<=200;j++){
            for(int k=0;k<=100;k++){
                int aa=ay+i,bb=by+j,cc=cy+k;
                if(bb-cm<=0) continue;
                if(bm-cc<=0) ans=min(ans,a*i+b*j+c*k);
                else if(ceil(1.0*am/(bb-cm))<ceil(1.0*aa/(bm-cc))) ans=min(ans,a*i+b*j+c*k);
            }
        }
    }
    cout<<ans;
}
```

---

## 作者：Tenshi (赞：0)

刷 codeforcesladders 的时候碰到的题目，感觉范围给得也太宽松了~~所以写个题解吐槽~~。

记我方的 HP，ATK，DEF 分别为 $hx, ax, dx$，敌方的类似地记为 $hy, ay, dy$。

首先手推一下柿子：

可以发现我方可以抵抗敌方 $\lceil \frac{hx}{ay-dx}\rceil$ 轮攻击，敌方可以抵抗我方 $\lceil \frac{hy}{ax-dy}\rceil$ 轮攻击。（当然，这里如果分母 $\leq 0$ 就意味着能抵抗无数轮攻击）。

然后题目的要求就是让 $\lceil \frac{hx}{ay-dx}\rceil > \lceil \frac{hy}{ax-dy}\rceil$。

根据题目范围，容易想到枚举。可以发现，将我方攻击至多加点至 $hy$ 就足以在一轮秒杀敌人；同时，将我方防御加点至 $dx$ 就能无限抵挡敌人攻击，所以考虑枚举我方攻击、防御的加点情况即可。

最后的任务是在枚举过程中我方还需要加点的最小 HP 值，现记我方攻击多点了 $i$，防御多加了 $j$，HP 多加了 $l$，那么此时敌方能够抵抗我方的轮数记为 $ycnt = \lceil \frac{hy}{ax-dy+i}\rceil$，我方能够抵抗的轮数为 $\lceil \frac{hx + l}{ay-dx-j}\rceil > ycnt$，简单推一下公式可知 $l>ycnt\times (ay-dx-j) - hx$，那我们取 $l = ycnt\times (ay-dx-j) - hx + 1$ 即为 $l$ 的最小值。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
#define debug(x) cerr << #x << ": " << (x) << endl
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)

int hx, ax, dx;
int hy, ay, dy;
int h, a, d;

int ceil(int a, int b){
	return (a+b-1)/b;
}

signed main(){
	cin>>hx>>ax>>dx;
	cin>>hy>>ay>>dy;
	cin>>h>>a>>d;
	
	int res=1e9+10;
	rep(i, max(0, (dy-ax)+1), max(hy-(ax-dy), 0)){
		rep(j, 0, max(ay-dx, 0)){
			int ycnt=ceil(hy, ax-dy+i);
			if(ay-dx-j<=0){
				res=min(res, i*a+j*d);
				continue;
			}
			int l=max(0, (ay-dx-j)*ycnt+1-hx);
			res=min(res, i*a+j*d+l*h);
		}
	}
	cout<<res<<endl;
	return 0;
}

```

---

## 作者：_Ink (赞：0)

duel 1800 的时候 duel 到这题了...

## 题解：

对取胜条件进行分析：

当 $atk_y \le def_m$，Y 每秒造成的伤害为 0，显然这种情况下不可能取胜。

当 $atk_y > def_m$，这个时候能够造成伤害。不考虑 $hp_y$ 的情况下，我们需要 $round$ 次才能击败 M，其中，$round$ 为：

$$round = \bigg\lceil \frac{hp_m}{atk_y - def_m} \bigg\rceil.$$

那么考虑 $hp_y$，取胜条件便为 $round \times (atk_m - def_y) < hp_y$。

---

观察到数据范围很小，所有数的区间仅为 $[0, 100]$，显然能考虑枚举。

我们观察最坏的情况：

- 对于 hp，若 M 每次能对 Y 造成 100 伤害，而 Y 仅能对 M 造成 1 伤害，且 $hp_m=100, hp_y=1$，那么 Y 至少要买 10000 点 hp 才能胜利。

- 对于 atk，由于 $hp_m$ 和 $def_m$ 最大可能都为 100，所以 Y 在最坏情况下至少要买 200 点 atk 才能一轮结束。

- 对于 def，由于 $atk_m$ 最大可能为 100，所以 Y 在最坏情况下至少要买 100 点 def 才不会被击败。

所以套个三重循环枚举购买的个数就行了

...嗯，对，像这样暴力枚举就行了。像上述所说的“最坏情况”其实就是计算了循环的上界，这样算即是循环了 $2\cdot10^8$ 次，在 cf 神机上能跑过。所以直接这么交上去就行了。

说实话...这种暴力方法都卡不掉，简直有损 CF*1800 风范（

## $\text{Code:}$

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define maxn 500050
#define maxm 500050 
#define vi vector <int>
#define vvi vector <vi>
#define endl '\n'
#define ll long long
using namespace std;

void solve()
{
	int hpy, atky, defy; cin >> hpy >> atky >> defy;
	int hpm, atkm, defm; cin >> hpm >> atkm >> defm;
	int h, a, d; cin >> h >> a >> d;
	
	int ans = inf;
	for(int hi = 0; hi <= 10000; hi ++){
		for(int ai = 0; ai <= 200; ai ++){
			for(int di = 0; di <= 100; di ++){
				if(atky + ai - defm <= 0) continue;
				int thpy = hpy + hi, tatky = atky + ai, tdefy = defy + di;
				int rnd = (hpm + (tatky - defm - 1)) / (tatky - defm);
				if(rnd * (max(0, atkm - tdefy)) < thpy) ans = min(ans, hi * h + ai * a + di * d);
			}
		}
	}
	cout << ans;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); //cout.tie(0);
	
	int t = 1;
	//cin >> t; 
	while(t --) solve();
	
	return 0;
}
```

## $\text{Extra:}$

当然，我们也可以考虑优化。

我们发现，如果我们已经知道了 Y 三个数据中的两个，那么所需的剩下的一个数据实际上是可以计算出来的。

直接计算，这样就优化掉了一维的枚举。鉴于我们枚举 hp 的次数是最大的，所以我们可以不枚举 hp，只枚举 atk 和 def，然后通过计算求出所需购买的 hp 数量即可。这样就快多了。

代码就不贴了。

---

