# [NEERC 2013] Interactive Interception

## 题目描述

这是一个交互式问题。

东北紧急火箭控制局（NEERC）开发了一种新的雷达控制系统，旨在更好地控制弹道火箭拦截。为了测试新系统，NEERC 机构开发了一个数学模型，旨在展示该系统的能力。

让我们将火箭表示为一条线上的一个点。最初，该点位于 $0$ 到 $p$ 之间的某个未知整数位置（包括 $0$ 和 $p$）。它具有某个未知速度 $q$，这是一个介于 $0$ 和 $v$ 之间的整数（包括 $0$ 和 $v$）。

每秒会发生以下情况。首先，控制系统向雷达发出一个形式为“`check L R`”的查询，并得到一个答案，指出该点当前是否在 $L$ 和 $R$ 之间（包括 $L$ 和 $R$）。之后，该点的坐标增加 $q$。

雷达控制系统的目标是在某一秒开始时准确地确定该点的位置。当它确实知道该点的位置时，不再向雷达发出查询，而是发出命令在该位置拦截该点。

你必须实现控制系统，在最多进行 100 次雷达查询的情况下定位并拦截该点。

### 交互协议
交互从你的程序读取两个整数——$p$ 和 $v$ 的值开始（$1 \leq p \leq 10^5$，$1 \leq v \leq 10^5$）。

之后，你的程序必须向标准输出打印命令。每个命令必须是以下两种之一。

- “`check L R`”——向雷达发出查询以获得答案，指出该点当前是否在 $L$ 和 $R$ 之间（包括 $L$ 和 $R$）。答案必须从标准输入读取，答案是“`Yes`”或“`No`”。之后，该点的坐标增加 $q$。$L$ 和 $R$ 必须是整数。
- “`answer x`”——已知该点的确切坐标 $x$，并命令拦截该点。在打印此命令后，你的程序必须退出。

你的程序必须在每个命令后，包括最后一个命令“`answer x`”后写入行结束符并刷新标准输出（在退出之前必须写入并刷新行结束符）。

## 说明/提示

在给定的例子中，该点最初位于位置 $1$，并以速度 $q = 1$ 移动。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
2 2
Yes
No
Yes
Yes```

### 输出

```
check 1 3
check 3 5
check 2 4
check 4 5
answer 5```

# 题解

## 作者：CuFeO4 (赞：1)

非常有意思的一道题。注意 $q$ 是不变的。

允许的查询次数比较小，考虑二分。由于知道了速度 $q$ 也无法知道位置，但知道了位置可以反推出速度 $q$ 的范围，而且可以证明 $q$ 可能的取值范围一直在缩小，从而考虑二分询问位置 $x$。

具体的，假如当前询问为 $[l_{k},r_{k}]$，那么最快的速度 $v_{max}$ 就是 $\max\limits_{1\le i<k}(r_k-l_i)/(k-i)$，最慢的速度 $v_{min}$ 就是 $\min\limits_{1\le i<k}(l_k-r_i)/(k-i)$，然后左右端点 $l=l_{k}+v_{min}$，$r=r_{k+1}+v_{max}$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,s,t,p) for(int i = s;i <= t;i += p)
#define drep(i,s,t,p) for(int i = s;i >= t;i -= p)
#ifdef LOCAL
  //auto I = freopen("in.in","r",stdin),O = freopen("out.out","w",stdout);
  auto I = stdin,O = stdout;
#else
  auto I = stdin,O = stdout;
#endif
using ll = long long;using ull = unsigned long long;
using db = double;using ldb = long double;
int p,v,L[101],R[101],t;
auto Q = [](int l,int r){cout<<"check "<<l<<' '<<r<<endl;string s;cin>>s;return (s[0] == 'Y');};
signed main(){
  cin.tie(nullptr)->sync_with_stdio(false);
  cin>>p>>v;
  int l = 0,r = p,lv = 0,rv = v;
  while(l < r){
    int mid = (l + r) >> 1;
    if(Q(l,mid)) r = mid;
    else l = mid + 1;
    for(int i = 0;i < t; ++i) 
      lv = max(lv,(l-R[i])/(t-i)),
      rv = min(rv,(r-L[i])/(t-i));
    L[t] = l,R[t] = r;
    l += lv,r += rv;
    t++;
  }
  cout<<"answer "<<l<<endl;
}
```

---

## 作者：luxiaomao (赞：1)

## [P7004](https://www.luogu.com.cn/problem/P7004) 二分交互题

这是笔者的第一道交互题，代码难度不大，但从思维上来说还是挺有意思的，所以写篇题解祭一祭。

## Solution

题意：

> 平面上有一个点，初始位置 $x\in[0,p]$，速度 $q\in[0,v]$，其中 $p,v$ 是给定的。
\
你可以进行不超过 $100$ 次询问，形如 ``check L R``，满足 $0\le L\le R\le 10^9$，交互库会告诉你是否有 $x\in[L,R]$，每次询问之后，交互库会令 $x\gets x+q$。你需要在某个询问后确定此时的 $x$，并告诉交互库，格式形如 ``answer x``。
\
$1\le p,v\le 10^5$。

首先要注意 $q$ 是一个恒定的值（刚开始我还以为每次询问完随机跳一段距离呢）。

既然不能超过一百次询问，不难想到二分。但本题难点在于，二分的范围如何求出？

脑补一下解题过程：设变量 $l$ 和 $r$ 为该点坐标的范围，当这个范围越缩越小直至成为一个点，我们就求出了此时坐标的具体值。

如果不存在每次查询往前跳一段的设定，那么现在这道题就成为了一个二分板子。但是我们不清楚 $q$ 的具体值，每次查询后的 $l$ 和 $r$ 该如何处理？

请看下面这张图（真的是图吗）。

```
[        ]    [               ]
l        r    l'              r'
[           max_v             ]
        [min_v]
```

这表示的是一次查询后可以根据上次查询推算出可能最大和最小的 $v$，以此类推，我们还可以根据之前的每一次查询推算，只是记得除去操作次数差就行，具体见代码。

## Code

普及组代码难度，但是要想出思路并不容易。

```cpp
#include<bits/stdc++.h>
#define N 200
using namespace std;

int p,v;
int l,r,lv,rv;
int L[N],R[N],t;

bool ask(int l,int r)
{
	cout<<"check "<<l<<' '<<r<<endl;
	string s;
	cin>>s;
	return s[0] == 'Y';
}

int main()
{
	cin>>p>>v;
	l = 0,r = p,lv = 0,rv = v;
	while(l < r)
	{
		int mid = (l+r)>>1;
		if(ask(l,mid))r = mid;
		else l = mid+1;
		L[t] = l,R[t];
		for(int i = 0;i < t;i++)
		{
			lv = max(lv,(l-R[i])/(t-i));
			rv = min(rv,(r-L[i])/(t-i));
		}
		L[t] = l,R[t] = r;
		l += lv,r += rv;
		++t;
	}
	cout<<"answer "<<l;
}
```

---

## 作者：CmsMartin (赞：1)

[更好的阅读体验](http://cmsblog.top/archives/neerc2013interactiveinterception)

## 题目描述

[题目传送门](https://www.luogu.com.cn/problem/P7004)

## 思路

很好玩的交互题。

首先不难想到二分，可以二分位置。

因为询问比较的少，我们可以将每次二分后可能的位置记录下来，然后计算可能的速度。

不断逼近就可以得到答案。

询问次数是 $\log p$ 级别的。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

string S;
bool Ask(int l, int r) {
	cout << "check " << l << " " << r << endl;
	cin >> S;
	return S[0] == 'Y'; 
}

int lp, rp, lv, rv, mid, t, L[100010], R[100010];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> rp >> rv;
	while (lp < rp) {
		mid = lp + rp >> 1;
		if (Ask(lp, mid))
			rp = mid;
		else
			lp = mid + 1;
		for (int i = 0; i < t; i++) {
			rv = min(rv, (rp - L[i]) / (t - i));
			lv = max(lv, (lp - R[i]) / (t - i));
		}
		L[t] = lp;
		R[t] = rp;
		lp += lv;
		rp += rv;
		t++;
	}
	cout << "answer " << lp << endl;
	return 0;	
}
```

---

## 作者：Day_Dreamer_H (赞：0)

# P7004 题解

一道比较有意思的二分交互题。

题目给了你速度范围和位置范围，那我们显然应该二分位置，因为即使知道速度了也无法确定位置。

那我们怎么处理速度，显然在我们不断提问的时候，速度的可能取值范围会越来越小，那我们不如把之前的所有提问都记录下来，每次提问之后和之前的所有提问比较，假设我们当前提问是第 $cur$ 次，区间是 $[l,r]$，正在和 $[l_i,r_i]$ 比较。

其中最慢的速度就是 $(l-r_i)/(cur-i)$，最快的速度就是 $(r-l_i)/(cur-i)$，这样我们的左区间加上最慢速度，右区间加上最快速度即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int p,v;
int lv,rv;
int lp,rp;
int lp1[105],rp1[105],pos;
int main(){
	cin>>p>>v;
	rv = v;
	rp = p;
	while(lp<rp){
		int mid = (lp+rp)>>1;
		cout<<"check "<<lp<<" "<<mid<<endl;
		string op;
		cin>>op;
		if(op[0] == 'Y'){
			rp = mid;
		}else{
			lp = mid+1;
		}
		for(int i = 0;i<pos;i++){
			lv = max(lv,(lp-rp1[i])/(pos-i));
			rv = min(rv,(rp-lp1[i])/(pos-i));
		}
		lp1[pos] = lp;
		rp1[pos] = rp;
		pos++;
		lp+=lv;
		rp+=rv;
	}
	cout<<"answer "<<lp;
}
```

---

