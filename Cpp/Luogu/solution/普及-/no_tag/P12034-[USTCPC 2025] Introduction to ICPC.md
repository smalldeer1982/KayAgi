# [USTCPC 2025] Introduction to ICPC

## 题目背景

USTCPC 设置 2s 时限为了使得 python 通过。洛谷改为 1s 时限。

## 题目描述

克露丝卡尔酱正在参加 ICPC！这个题目是和 ICPC 基本规则相关的一道题。

以下关于 ICPC 的内容与该题目无关：

1. 一场 ICPC 一般有 $10\sim 15$ 道题。题目排布顺序与题目难度无关。不过为了提升大家的参赛体验，克露丝卡尔酱温馨地提醒大家，ABCD 是本场比赛的简单题哦～

2. 提交代码的正确性会即时返回给选手，选手也可以看到其他选手提交代码的正确性和即时排名。因此，当你在某一道题卡住时，不妨看看排行榜上其他队伍在做什么题，一般来说**通过**选手数较多的题目会更简单哦~

3. 比赛最后一小时内，选手将不再能够看到其他选手提交代码的正确性，称为**封榜**（可以看到自己提交代码的正确性）。在颁奖过程中，会将排名从低到高逐渐公开是否通过，称为**滚榜**。

-------

以下关于 ICPC 的内容与该题目有关：

1. 在 ICPC 中，提交代码的正确性为即时返回给选手，包括：（不同平台上这些名词会略有不同，以实际为准）
   
   + Accepted（正确）
   
   + Wrong Answer（答案错误）
   
   + Time Exceeded（程序运行时间超出时间限制）
   
   + Runtime Error（程序运行时发生错误，可能原因有：数组越界、除以0等）
   
   + Memory Exceeded（程序运行内存空间超过了题目限制）
   
   + Compile Error（编译错误）
   
   如果一位选手在一道题目中获得 Accepted 的结果，则选手在该题获得**通过**。

2. 选手的成绩可以用 $2$ 个参数表示，**通过的题数**和**总罚时**。通过的题数即为选手获得通过题目的数量，而**罚时**的计算参照下表：
   
   - 对于未通过的题目，该题目的罚时为 $0$。
   
   - 对于通过的题目：该题目基础罚时为在该题获得 Accepted 的结果的时间（从比赛开始的分钟数）；特别地，在 Accepted 结果前，**每一个**非 Accepted 且非 Compile Error 在该题的提交会对于该题增加 $20$ 分钟罚时。
   
   - 每道题目的基础罚时的范围为 $[0,300)$，即在第 $300$ 分钟开始后不能够再提交代码。（这里认为存在第 $0$ 分钟）
   
   - 一场比赛的总罚时即为所有题目的罚时之和。
   
	定义偏序关系：对于 2 位选手，如果他们通过的题数不相等，则通过的题数更多的选手胜出；若通过的题数相等，则总罚时更小的选手胜出。

特别地，对于该题，规定一位选手只能在一分钟内提交 $30$ 次代码（所有题目共用提交次数）

---

一场一般的 ICPC 可以决出金奖、银奖、铜奖和荣誉奖。按照定义的偏序关系可以获得一个排行榜，而排行榜的前若干名可以获得金奖/银奖/铜奖。每种奖牌存在一种分数线（显然也有 $2$ 个参数）：成绩优于或等于该分数线的获得该种奖牌，而成绩劣于该分数线不能获得该种奖牌。分数线必须是一个可能达成的成绩。

显然，能将不同奖牌区分开的分数线并不唯一。因此，克露丝卡尔酱想知道：对于每种奖牌，奖牌线的**上确界**和**下确界**为多少？

## 样例 #1

### 输入

```
4 4 4 2
9 935
9 1212
9 1218
9 1322
8 868
8 934
8 960
8 1031
8 1112
8 1166
8 1324
7 605
7 898
7 954```

### 输出

```
9 1322 8 867
8 1031 8 1111
7 605 7 897```

## 样例 #2

### 输入

```
1 1 1 1
3 0
1 0
1 1
0 0```

### 输出

```
3 0 2 180558
1 0 1 0
1 1 1 180279```

# 题解

## 作者：chenyuan3 (赞：9)

[![](https://img.shields.io/badge/题目传送门-点我-f39c11)](https://www.luogu.com.cn/problem/P12034)

思路：设 $i$ 为获得当前奖项的最后一名。

- 上界：显然是获得该奖项的最低分；
- 下界：分情况讨论：
  - ~~观察样例发现~~当 $y_{i+1}>0$ 时答案为 $x_{i+1}$ 和 $y_{i+1}-1$；
  - 显然罚时不能是负数，所以当 $y_{i+1}=0$ 时通过数只能变高为 $x_{i+1}-1$，罚时取最大，考虑所有题都在 $299$ 分钟通过，且交满了 $300\times30$ 发提交，除了最后一发通过以外，其它都计算罚时。故最大的罚时为 $299(x_{i+1}+1)+[9000−(x_{i+1}+1)]×20=180000+279(x_{i+1}+1)$。

代码：（[AC 记录](https://www.luogu.com.cn/record/212940891)）

``` cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 1e5 + 10;
ll a, b, c, d, p[maxn], t[maxn];
void work(ll n) // 用于输出 n 为这一奖项的最后一名的上界与下界
{
    cout << p[n] << ' ' << t[n] << ' ';
    if (t[n + 1] > 0)
    {
        cout << p[n + 1] << ' ' << t[n + 1] - 1 << endl;
    }
    else
    {
        cout << p[n + 1] + 1 << ' ' << 180000 + (p[n + 1] + 1) * 279 << endl;
    }
}
void solve()
{
    cin >> a >> b >> c >> d;
    for (ll i = 1; i <= a + b + c + d; i++)
    {
        cin >> p[i] >> t[i];
    }
    work(a);
    work(a + b);
    work(a + b + c);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
 	// ll t; cin >> t; while (t--)
	solve();
	return 0;
}
```

---

## 作者：ShiYuXuan1234 (赞：5)

## 思路
很明显，这是一道模拟题。

本题的重点在于如何求**上下确界**。

根据输入输出样例，可以得出**上下确界**的求法如下：

>- **上确界**：取该奖项的最后一名选手的题目数和罚时。
>  
>- **下确界**：取下一奖项的第一名选手的前一合法成绩（当罚时 $\ne0$ 时，将罚时 $-1$，否则将题目数 $+1$，并取**最大可能罚时**）

而根据题意，**最大可能罚时**的求法如下（设题目数 $+1$ 的值为 $a$）：

$$a\times299+20\times(30\times300-a)$$

即在第 $299$ 分钟获得 Accepted 的结果，在这之前每分钟提交 $30$ 次，由于最后 $a$ 次将获得 Accepted 的结果，因此还要减去 $a$。

在这里，本人使用了结构体，其中 $x$ 代表题目数，$y$ 代表罚时。
## AC代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct node{
	int x,y;
};
node a[N];
int main(){
	int g,s,b,h;
	cin>>g>>s>>b>>h;
	int tmp=g+s+b+h;
	for(int i=1;i<=tmp;i++){
		cin>>a[i].x>>a[i].y;
	}
	node gu,gd,su,sd,bu,bd;//金、银、铜奖的上下确界
	gu.x=a[g].x;
	gu.y=a[g].y;
	if(a[g+1].y!=0){
		gd.x=a[g+1].x;
		gd.y=a[g+1].y-1;
	}else{
		gd.x=a[g+1].x+1;
		gd.y=gd.x*299+20*(30*300-gd.x);
	}
	su.x=a[g+s].x;
	su.y=a[g+s].y;
	if(a[g+s+1].y!=0){
		sd.x=a[g+s+1].x;
		sd.y=a[g+s+1].y-1;
	}else{
		sd.x=a[g+s+1].x+1;
		sd.y=sd.x*299+20*(30*300-sd.x);
	}
	bu.x=a[g+s+b].x;
	bu.y=a[g+s+b].y;
	if(a[g+s+b+1].y!=0){
		bd.x=a[g+s+b+1].x;
		bd.y=a[g+s+b+1].y-1;
	}else{
		bd.x=a[g+s+b+1].x+1;
		bd.y=bd.x*299+20*(30*300-bd.x);
	}
	cout<<gu.x<<" "<<gu.y<<" "<<gd.x<<" "<<gd.y<<endl;
	cout<<su.x<<" "<<su.y<<" "<<sd.x<<" "<<sd.y<<endl;
	cout<<bu.x<<" "<<bu.y<<" "<<bd.x<<" "<<bd.y<<endl;
	return 0;
}
```
[AC 记录](https://www.luogu.com.cn/record/212967006)。

---

## 作者：hgckythgcfhk (赞：1)

广告：[USTCPC2025 题解汇总（部分）](https://www.luogu.com.cn/article/xl8dsc9j)。

这题主要的难度在于读题和对题意建模，对于题意一句话总结就是对三个奖牌线的上下界，比如金牌线，定义一个金牌线 $a$ 合法当且仅当小于等于 $a$ 的元素的个数为 $g$，其他线以此类推，先考虑不按上述偏序排序，直接对于整数的情况，上下界分别是对应排名的数和对应排名的下一个数加 $1$，于是我们需要对这题的元素定义加 $1$ 操作，当罚时不为 $0$ 时对一个元素加 $1$ 等于罚时减 $1$，否则是多做一个题但罚时吃满，假设多做一题后做了 $x$ 题，相当于在 $300$ 分钟内每分钟都吃 $30$ 发然后乘 $20$ 分钟等于 $180000$ 分钟，然后加上 $299x$，注意第 $i$ 分钟表示时间轴上 $[i,i+1)$ 的区间，且有效的分钟是第 $0$ 到 $299$ 所以一共是 $300$ 分钟。

以下是线下选手 $42$ 队提供的赛时代码，非常感谢 $42$ 队。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MN = 4e5 + 7;
typedef pair<int, int> P;
int n, A, B, C, D;
P a[MN];
int calc(int x) {
	return 279 * x + 180000;
}
void pre(P a, P b) {
	if (b.second == 0) cout << b.first + 1 << " " << calc(b.first + 1) << endl;
	else cout << b.first << " " << b.second - 1 << endl;
}
bool cmp(P a, P b) {
	if (a.first != b.first) return a.first > b.first;
	return a.second < b.second;
}
int main() {
	cin >> A >> B >> C >> D, n = A + B + C + D;
	for (int i = 1; i <= n; i++) cin >> a[i].first >> a[i].second;
	sort(a + 1, a + n + 1, cmp);
	cout << a[A].first << " " << a[A].second << " ";
	pre(a[A], a[A + 1]);
	B = A + B;
	cout << a[B].first << " " << a[B].second << " ";
	pre(a[B], a[B + 1]);
	C = B + C;
	cout << a[C].first << " " << a[C].second << " ";
	pre(a[C], a[C + 1]);
}
```

---

## 作者：liuyuantao (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P12034)  
偶然看到这道题目，因为细节几次写挂，终于过了，来写篇题解。  
对于一个奖的**上确界**，令 $k$ 表示**获得此奖及更高奖**的总人数（如银奖的 $k=g+s$），则 $(x_k,y_k)$ 即为上确界（否则人数不足 $k$ 人）。

考虑下确界。保留上述定义 $k$，则下确界 $(x,y)$ 与 $(x_{k+1},y_{k+1})$ 偏序关系。当 $y_{k+1}>0$ 时，$(x_{k+1},y_{k+1}-1)$ 就是下确界。  
但是当 $y_{k+1}=0$ 时，$y_{k+1}-1=-1$ 不合法。于是我们只好增加通过数量，并且让罚时达到最大。即下确界为 $(x_{k+1}+1,tmax_{x_{k+1}+1})$。  
记 $X=x_{k+1}+1$，提交次数最大为 $30\times(299-0+1)=9000$，其中 $X$ 次是通过，于是最多有 $9000-X$ 次非通过，求得额外罚时为 $180000-20X$ 分钟。贪心地在第 $299$ 分钟通过，基础罚时即为 $299X$。综上，有 $tmax_{X}=279X+180000$。  
之后直接模拟计算即可。时间复杂度 $O(N)$（读入）。  
[AC code](https://www.luogu.com.cn/record/212095432)
```cpp
#include <bits/stdc++.h>

using namespace std;

#define LL long long


const int N=2e5+5;


LL A[N],B[N];
LL a,b,c,d,n;

int main(){
    ios::sync_with_stdio(false);
	cin>>a>>b>>c>>d;
	n=a+b+c+d;
	for(int i=1;i<=n;i++){
		cin>>A[i]>>B[i];
	}
    cout<<A[a]<<' '<<B[a]<<' ';
    if(B[a+1]>0)
    cout<<A[a+1]<<' '<<B[a+1]-1<<'\n';
    else
    cout<<A[a+1]+1<<' '<<180000+(A[a+1]+1)*279<<'\n';
    cout<<A[a+b]<<' '<<B[a+b]<<' ';
    if(B[a+b+1]>0)
    cout<<A[a+b+1]<<' '<<B[a+b+1]-1<<'\n';
    else
    cout<<A[a+b+1]+1<<' '<<180000+(A[a+b+1]+1)*279<<'\n';
    cout<<A[a+b+c]<<' '<<B[a+c+b]<<' ';
    if(B[a+b+c+1]>0)
    cout<<A[a+b+c+1]<<' '<<B[a+b+c+1]-1<<'\n';
    else
    cout<<A[a+b+c+1]+1<<' '<<180000+(A[a+b+c+1]+1)*279<<'\n';
    
    
    
    
    
    return 0;
}
```

---

## 作者：封禁用户 (赞：1)

一道模拟捏，需要求出每种奖牌，奖牌线的**上确界**和**下确界**为多少。

---

给定按成绩降序排列的选手列表，要求确定金奖、银奖、铜奖的分数线上下确界。
- 成绩的比较规则为：题数多的优先，题数相同时总罚时少的优先。

上下确界需满足：
1. 所有获奖选手的成绩 $\ge$ 上确界且 $\ge$ 下确界。
2. 未获奖选手的成绩 $<$ 上确界且 $<$ 下确界。

---

如何计算呢？
- **上确界**：取该奖项最后一名选手的成绩，即该奖项的最低成绩。
- **下确界**：取下一个奖项第一名选手的前一个合法成绩。
   - 若罚时 $>0$，则罚时 $-1$。
   - 若罚时为 $0$，则题数 $+1$，并取该题数的最大可能罚时。

## Code
```cpp
#include <iostream>
#include <vector>

using namespace std;

// 计算给定成绩的前一个更优成绩
pair<int, int> get(pair<int, int> score) {
    int x = score.first, y = score.second;
    if (y > 0) return {x, y - 1}; // 罚时减1
    // 罚时为0时，计算x+1题的最大可能罚时
    int new_x = x + 1;
    int new_y = new_x * 299 + 20 * (30 * 300 - new_x);
    return {new_x, new_y};
}

int main() {
    int g, s, b, h;
    cin >> g >> s >> b >> h;
    int total = g + s + b + h;
    vector<pair<int, int>> sc(total);
    for (int i = 0; i < total; ++i)
        cin >> sc[i].first >> sc[i].second;

    // 金奖上下界
    pair<int, int> gu = sc[g - 1]; // 上确界：金奖最后一名
    pair<int, int> gl = get(sc[g]); // 下确界：银奖第一名前一个成绩

    // 银奖上下界
    pair<int, int> su = sc[g + s - 1];
    pair<int, int> sl = get(sc[g + s]);

    // 铜奖上下界
    pair<int, int> bu = sc[g + s + b - 1];
    pair<int, int> bl = get(sc[g + s + b]);

    // 输出结果
    cout << gu.first << ' ' << gu.second << ' ' << gl.first << ' ' << gl.second << endl;
    cout << su.first << ' ' << su.second << ' ' << sl.first << ' ' << sl.second << endl;
    cout << bu.first << ' ' << bu.second << ' ' << bl.first << ' ' << bl.second << endl;

    return 0;
}
```

---

## 作者：jiangyunuo (赞：0)

### 思路：
通读全文，我们可以发现，本题主要从两个方面解决：

1. 确认每个分数线的上界，这个不难办到，我们只要根据名次，选择某个奖项最后一名的成绩作为这个奖项分数线上界（注：只要达到或超越某个奖项的分数线就算达到了某个奖项）。
2. 确认每个分数线的下界，这个就比前者难了，正常情况下，我们只要从某个奖项最后一名的后一名入手，以比他高一点的成绩为下界。

这说着很容易，但有一个重要的点，第一个方面没啥问题，第二个方面主要是从罚时下手，将某奖项的最后一名的后一名的罚时减一，但是，有一个值得注意的点，罚时不可能为负，如果某奖项的最后一名的后一名的罚时为 $0$，那么，我们就要将通过题加一，重新计算罚时。

如何计算罚时是一个大问题，很多人都看不懂样例二中的 $180558$ 和 $180279$ 是咋来的（其实我一开始也没看懂），接下来我会进行说明：
1. 罚时的第一种情况是根据提交时间，最晚是在 $299$ 分钟提交的，我们设提交数为 $n$，则算出这样的罚时为 $299 \times n$。
2. 每次提交非 AC 也非 CE 的代码就会增加 $20$ 的罚时，且每分钟能提交 $30$ 次代码且共有 $300$ 分钟时间，于是一场比赛共能提交 $30 \times 300 = 9 \times 10^3$ 次，最多会获得 $20 \times 9 \times 10^3 - 20 \times n = 1.8 \times 10^5 - 20 \times n$ 的罚时。
3. 最终整合得到 $1.8 \times 10^5 - 20 \times n + 299 \times n = 1.8 \times 10^5 + 299 \times n$。

接着我们就可以得到最终代码了。
### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
	int a,b;
}c[100005];
int main(){
	int g,s,b,h;
	cin>>g>>s>>b>>h;
	int n=g+s+b+h;
	for(int i=1;i<=n;i++){
		cin>>c[i].a>>c[i].b;
	}
	cout<<c[g].a<<" "<<c[g].b<<" ";
	if(c[g+1].b-1>=0)cout<<c[g+1].a<<" "<<c[g+1].b-1<<endl;
	else cout<<c[g+1].a+1<<" "<<180000+(c[g+1].a+1)*279<<endl;    //计算金奖上下界。
	cout<<c[g+s].a<<" "<<c[g+s].b<<" ";
	if(c[g+s+1].b-1>=0)cout<<c[g+s+1].a<<" "<<c[g+s+1].b-1<<endl;
	else cout<<c[g+s+1].a+1<<" "<<180000+(c[g+s+1].a+1)*279<<endl;    //计算银奖上下界。
	cout<<c[g+s+b].a<<" "<<c[g+s+b].b<<" ";
	if(c[g+s+b+1].b-1>=0)cout<<c[g+s+b+1].a<<" "<<c[g+s+b+1].b-1<<endl;
	else cout<<c[g+s+b+1].a+1<<" "<<180000+(c[g+s+b+1].a+1)*279<<endl;    //计算铜奖上下界。
	return 0; 
}
```

[AC 记录](https://www.luogu.com.cn/record/213343429)。

---

## 作者：b__b (赞：0)

# [P12034](https://www.luogu.com.cn/problem/P12034)
一道个人认为难度实际应为黄的模拟题，下文中 AC 为 Accepted 的缩写，CE 为 Compile Error 的缩写。
## 题目思路
下文将奖牌线表示为 $(p,t)$，其中 $p$ 为通过的题数，$t$ 为罚时，当前这个奖牌线需要通过的人数表示为 $g$。
> 数据保证对于 $\forall i$ 有 $(x_i,y_i)$ 和 $(x_{i+1},y_{i+1})$ 满足如题定义的偏序关系。

即输入数据已经是按照文中偏序关系排序的。

显然，奖牌线的上界为 $(x_g,y_g)$（因为再高的话第 $g$ 名就拿不了这个奖了）。

因为我们要使奖牌线分数尽可能低的话我们就需要让通过的题数尽可能少，所以我们优先通过减少罚时来提高奖牌线分数。

当 $y_{g+1}>0$ 时，奖牌线下界为 $(x_{g+1},y_{g+1}-1)$。

当 $y_{g+1}=0$ 时，因为罚时已经少不了了，所以只能增加题数。

因为已经增加了题数，所以我们可以将罚时设为最大。
#### 如何获得最大罚时？
下文设通过的题数为 $n$。
> 每道题目的基础罚时的范围为 $[0,300)$，即在第 $300$ 分钟开始后不能够再提交代码。（这里认为存在第 $0$ 分钟）

因此可以提交代码的时长为 $300$ 分钟。
> 特别地，对于该题，规定一位选手只能在一分钟内提交 $30$ 次代码（所有题目共用提交次数）

因此最多可以提交 $300 \times 30=9000$ 次，但是因为只有通过的题目会计算罚时，因此我们实际还要减掉 $n$，即实际可以计算为罚时的次数有 $9000-n$ 次。
> 特别地，在 Accepted 结果前，每一个非 Accepted 且非 Compile Error 在该题的提交会对于该题增加 20 分钟罚时。

因此如果每一次都非 AC 且非 CE 可以获得 $20(9000-n)$ 分钟的罚时。
> 对于通过的题目：该题目基础罚时为在该题获得 Accepted 的结果的时间（从比赛开始的分钟数）；

所以如果每一道题都是在第 $299$ 分钟通过的话那么可以获得 $299n$ 分钟的罚时（虽然有一分钟只能提交 $30$ 次的限制，但是由于题目最多只有 $15$ 道，因此不用考虑）。

综上所述，可以获得的最大罚时为 $20(9000-n)+299n=18000+279n$ 分钟。
## 代码

```cpp
#include <cstdio>
int g, s, b, h, sum;
struct per {
    int x, y;
} pers[100005];
int main() {
    scanf("%d%d%d%d", &g, &s, &b, &h), sum = g + s + b + h;
    for (int i = 0; i < sum; ++i)
        scanf("%d%d", &pers[i].x, &pers[i].y);
    //金奖
    printf("%d %d ", pers[g - 1].x, pers[g - 1].y);
    if (pers[g].y)
        printf("%d %d", pers[g].x, pers[g].y - 1);
    else
        printf("%d %d", pers[g].x + 1, 180000 + (pers[g].x + 1) * 279);
    //银奖
    printf("\n%d %d ", pers[g + s - 1].x, pers[g + s - 1].y);
    if (pers[g + s].y)
        printf("%d %d", pers[g + s].x, pers[g + s].y - 1);
    else
        printf("%d %d", pers[g + s].x + 1, 180000 + (pers[g + s].x + 1) * 279);
    //铜奖
    printf("\n%d %d ", pers[g + s + b - 1].x, pers[g + s + b - 1].y);
    if (pers[g + s + b].y)
        printf("%d %d", pers[g + s + b].x, pers[g + s + b].y - 1);
    else
        printf("%d %d", pers[g + s + b].x + 1, 180000 + (pers[g + s + b].x + 1) * 279);
}
```

---

## 作者：Grand_Dawn (赞：0)

本题的难点在于能够阅读并理解题意。

以下仅考虑金线（银线和铜线同理）：

显然金牌最后一名的成绩为金线的上确界。（上确界即为生活中关于分数线的常识）

对于下确界，仅需要考虑银牌第一的分数 $+1$ 即可（对于一般比赛）。对于 ICPC 比赛需要阅读题面中的偏序关系来明白定义。

一般情况下，若银牌第一名为 $x$ 题 $y$ 罚时，则金线的下确界即为 $x$ 题 $y-1$ 罚时。 

特殊情况：银牌第一名为 $x$ 题 $0$ 罚时，则金牌是 $x+1$ 题且罚时到达理论值最大。计算理论值最大，考虑所有题都在 $299$ 分钟通过，且交满了 $300\times 30$ 发提交，除了 $x+1$ 发通过以外，其它都计算罚时。

故 $x+1$ 题最大的罚时为 $299(x+1)+[9000-(x+1)]\times 20=180,279+279x$。

---

