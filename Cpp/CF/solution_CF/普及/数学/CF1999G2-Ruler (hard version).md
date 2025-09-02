# Ruler (hard version)

## 题目描述

本题是问题的困难版本。该版本与简单版之间的唯一区别是在这个版本中，你最多可以进行 $7$ 次查询。

这是一道交互题。

有一把有 $1001$ 个刻度的尺子，刻度分别为 $1 \sim 1001$。不幸的是，尺子丢失了一个刻度 $x$（$2 \le x \le 999$）。当你用尺子量一个长度为 $y$ 的物体时，尺子量出的结果为：
- 若 $y < x$，尺子将会量出正确的结果 $y$。
- 否则，尺子将会量出错误的结果 $y + 1$。

你需要找出丢失的刻度 $x$。你可以每次提供两个 $1$ 至 $1000$ 内的整数 $a,b$，你将会收到尺子量出的 $a$ 的长度与尺子量出的 $b$ 的长度之积。

你可以进行最多 $7$ 次询问。

## 样例 #1

### 输入

```
2

18

25


9999```

### 输出

```
? 3 5

? 4 4

! 4
? 99 100

! 100```

# 题解

## 作者：cjh20090318 (赞：6)

很简单的交互题，不怎么需要动脑子。

## 题意

**这是一道交互题。**

和简单版本不同的是，你**最多**可以进行 $7$ 次查询。

有一个秘密的尺子，上面缺少一个数字 $x$。当你测量一个长度为 $y$ 的物体时，尺子会报告以下值：

- 如果 $y < x$，尺子（正确地）测量物体长度为 $y$。
- 如果 $y \ge x$，尺子错误地测量物体长度为 $y+1$。

你需要找出 $x$ 的值。为此，你可以进行以下形式的查询：

- $\texttt{? a b}$，作为响应，我们将用我们的尺子测量一个 $a \times b$ 的矩形的边长，并将结果相乘，向你报告测量出的矩形面积。

找出 $x$ 的值，回答格式为 $\texttt{! x}$。

## 分析

每次可以询问两个值，如果二分同一个值的话未免显得有点浪费。

答案具有单调性，且 $\log_3 999$ 略小于 $7$，考虑三分。

初始时 $l = 2, r = 999$，设 $m_1 = l + \left\lfloor \dfrac{r-l} 3 \right\rfloor, m_2 = r - \left\lfloor \dfrac{r-l} 3 \right\rfloor$。

查询 $m_1 \times m_2$ 组成矩形测出来的面积 $S$，有如下三种情况：

- $S = (m_1 + 1) (m_2 + 1)$，说明 $x \le m_1 \le m_2$，$r \gets m_1$。
- $S = m_1 (m_2 + 1)$，说明 $m_1 < x \le m_2$，$l \gets m_1 + 1, r \gets m_2$。
- $S = m_1 m_2$，说明 $m_1 \le m_2 < x$，$l \gets m_2 + 1$。

最后得到的 $l$ 即为缺失的数字 $x$，每次询问区间长度会缩小到原来的 $\dfrac 1 3$ 倍，询问次数可以保证。

## 代码

```cpp
//the code is from chenjh
#include<cstdio>
#define FLUSH fflush(stdout)
using namespace std;
int check(const int x,const int y){
	printf("? %d %d\n",x,y),FLUSH;
	int ret;scanf("%d",&ret);
	return ret;
}
void solve(){
	int l=2,r=999;
	for(int m1,m2,ret;l<r;){
		m1=l+(r-l)/3,m2=r-(r-l)/3;
		ret=check(m1,m2);
		if(ret==(m1+1)*(m2+1)) r=m1;
		else if(ret==m1*(m2+1)) l=m1+1,r=m2;
		else l=m2+1;
	}
	printf("! %d\n",l),FLUSH;
}
int main(){
	int T;scanf("%d",&T);
	while(T--) solve();
	return 0;
}
```

---

## 作者：aeiouaoeiu (赞：1)

令 $a\le b$，当我们查询 $a,b$ 时，结果必然是 $ab,a(b+1),(a+1)(b+1)$ 中的一种。

对三种情况讨论：

- 结果为 $ab$：我们有 $a\le b<x$。

- 结果为 $a(b+1)$：我们有 $a<x\le b$。

- 结果为 $(a+1)(b+1)$：我们有 $x\le a\le b$。

三种情况下我们都能将 $x$ 的范围缩小。

为了让查询次数尽量少，这三类区间的长度要尽可能接近。若当前 $x$ 范围为 $[L,R]$，则这三类区间要么是 $\lfloor{\frac{R-L+1}{3}}\rfloor$，要么是 $\lceil{\frac{R-L+1}{3}}\rceil$。这样可以保证三类区间长度相差不超过 $1$。

具体地，我们只要钦定其中两个区间一定取向上取整即可。

计算可以发现，在最劣（全部取向上取整）的情况下，取区间的次数也不会超过 $7$ 次，恰好满足题目。

[code](https://codeforces.com/contest/1999/submission/274799889)，实现方式可能有些不同。

---

## 作者：PineappleSummer (赞：0)

Div4 放交互题，一点不会。

此题与简单版的区别在于这题至多可以询问 $7$ 次，而简单版至多可以询问 $10$ 次。

设 $n=10^3$，这题只能用 $\mathcal O(\log_3n)$ 的三分做法，而简单版可以通过 $\mathcal O(\log_2n)$ 的二分做法。

初始 $l=1,r=10^3$，设 $L=l+\left\lfloor\dfrac{r-l}{3}\right\rfloor,R=r-\left\lfloor\dfrac{r-l}{3}\right\rfloor$。

那么每次询问就是 $[L,R]$ 这个区间。

分类讨论一下返回的值 $x$。

- 如果 $x=L\times R$，说明目标位置大于 $R$，$l\gets R+1$。

- 如果 $x=L\times (R+1)$，说明目标位置在 $L+1$ 与 $R$ 之间，$r\gets R$，$l\gets L+1$。

- 如果 $x=(L+1)\times (R+1)$，说明目标位置小于等于 $L$，$r\gets L$。

$l$ 的值就是最后答案。时间复杂度 $\mathcal O(\log_3n)$。

```cpp
void solve () {
	int l = 1, r = 1e3;
	while (l < r) {
		int L = l + (r - l) / 3, R = r - (r - l) / 3;
		cout << "? " << L << ' ' << R << '\n';
		int init; cin >> init;
		if (init == -1) exit (0);
		else if (init == L * R) l = R + 1;
		else if (init == L * (R + 1)) r = R, l = L + 1;
		else if (init == (L + 1) * (R + 1)) r = L;
	}
	cout << "! " << l << endl;
}
```

---

## 作者：Halberd_Cease (赞：0)

简单观察，容易发现，我们会把长度大于等于 $x$ 的线段长度测量错误，使结果 $+1$，后续我们称这个值为测量值。

对于朴素的二分，需要 $\log_2 n$ 次以求出正确答案，能通过简单版，但是无法通过此题。

考虑继续发掘性质，对于一次查询，我们可以询问两个数，得到两个数测量值的乘积。

分类讨论一下，设查询的两个数为 $l,r$ 且 $l\le r$，则有：

- 如果 $x<l$，两者测量值之积即为 $l\times r$，因为没有数被测量错误；

- 如果 $l\le x<r$，两者测量值之积为 $(l+1)\times r$，只有 $l$ 被测量错误导致测量值 $+1$。

- 如果 $x\ge r$，测量值之积为 $(l+1)\times (r+1)$，两者都被测量错误。

因此，我们询问一次 $(l,r)$，都可以得到 $x$ 与 $l,r$ 的相对大小关系。

因此，我们设已经得到答案的区间在 $[l,r]$ 内，此时令 $ll,rr$ 为该区间的左、右三等分点，询问一次 $(ll,rr)$，根据返回的乘积按上述方式判断，即可知道 $x$ 在两个三等分点划分出的三个区间中的哪一个。

因为三个子区间的大小最多为 $\lceil \frac{len}{3}\rceil$，其中 $len$ 为大区间长度，因此只需要 $\log_3 n$ 次询问就能知道 $x$ 的大小。

[submission](https://codeforces.com/contest/1999/submission/275001948)

---

## 作者：nightwatch.ryan (赞：0)

### 思路
首先，答案是具有单调性的，因为尺子的刻度是升序的。

其次，题目生怕你看不见最多询问 $7$ 次，$\lceil \log_3 1000 \rceil = 7$，所以我们考虑三分求解。

初始时设 $l$ 为 $2$，$r$ 为 $1000$。设当前查询的矩形的长和宽分别为 $l_{mid}$ 和 $r_{mid}$。$l_{mid} = l+ \lfloor \dfrac{r-l}{3} \rfloor$，$r_{mid} = r- \lfloor \dfrac{r-l}{3} \rfloor$。显然 $l_{mid} \leq r_{mid}$，

设询问得到的结果为 $ans$，那么：
- 如果 $ans=l_{mid} \times r_{mid}$，那么说明 $x$ 有可能大于等于 $r_{mid}$，缩小左边界，让 $l = r_{mid} + 1$。
- 如果 $ans=l_{mid+1} \times r_{mid+1}$，说明 $l_{mid}$ 和 $r_{mid}$ 都大于等于 $x$，缩小右边界，让 $r=l_{mid}$。
- 如果 $ans=l_{mid} \times r_{mid+1}$，那么说明 $l_{mid}$ 小于等于 $x$，$r_{mid}$ 大于等于 $x$，那么缩小左右边界，让 $l=l_{mid+1}$，并且 $r=r_{mid}$。

最后输出 $l$。

本题是交互题。记得刷新缓冲区。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(int T){
    if(!T)return;
    int l=2,r=1000;
    while(l<r){
        int L_mid=l+(r-l)/3;
        int R_mid=r-(r-l)/3;
        cout<<"? "<<L_mid<<" "<<R_mid<<endl;
        int ans;
        cin>>ans;
        if(ans==L_mid*R_mid){
            l=R_mid+1;
        }else if(ans==(L_mid+1)*(R_mid+1)){
            r=L_mid;
        }else{
            l=L_mid+1;
        r=R_mid;
        }
    }
    cout<<"! "<<l<<endl;
    solve(T-1);
}
int main(){
    int T;
    cin>>T;
    solve(T);
}
```

---

## 作者：block_in_mc (赞：0)

## 题目大意

**本题为交互题**。有一个尺子，但是上面缺失了数 $x$，你需要找出 $x$ 的值（$2\le x\le999$）。使用这个尺子测量长度为 $n$ 的线段时，若 $n<x$，则测量结果时正确的；否则测量结果为 $n+1$。你每次可以询问用这把尺子测量实际宽度为 $a$，长度为 $b$ 的矩形的面积值（即用这把尺子分别测量长和宽的结果的乘积）。

你有 $10$ 次（Easy Version）或 $7$ 次（Hard Version）询问机会。

## 解题思路

首先考虑 Easy Version 如何解决。按照题意，如果我们询问 $1$ 和 $n$，若返回值为 $n$，则有 $x>n$；若返回值为 $n+1$，则有 $x\le n$。显然可以进行二分，由于 $2^{10}>999$，能够通过 Easy Version。

但是这个解决方案中没有利用矩形的第二条边，考虑如何利用——三分。但是这个三分是与二分类似的，而不是寻找单峰函数的峰值。具体地，在二分的基础上，令 $p=\lfloor\dfrac{l+r}{3}\rfloor$，$mid_1=l+p$，$mid_2=r-p$，我们将区间 $l\sim r$ 分为了三部分。我们询问 $mid_1$ 和 $mid_2$：

- 若返回值为 $mid_1mid_2$，则 $mid_2< x\le r$；
- 若返回值为 $mid_1(mid_2+1)$，则 $mid_1<x\le mid_2+1$；
- 若返回值为 $(mid_1+1)(mid_2+1)$，则 $l\le x\le mid_1$.

需要注意的是上面的不等号是否能够取等。

由于 $3^7>999$，三分可以通过 Hard Version。

那为什么我们正常不使用三分呢？因为正常情况下，我们对 $mid$ 进行两次合法性检查能够用二分缩小 $\dfrac{3}{4}$ 的范围，但是要求知道第一次合法性检查的结果再进行第二次，而这里只能同时进行，但也因此两次合法性检查只能缩小 $\dfrac{2}{3}$ 的范围。

## AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, l, r, mid1, mid2, ans;
int main() {
    cin >> t;
    while (t--) {
        l = 2, r = 999;
        while (l < r) {
            mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3;
            cout << "? " << mid1 << " " << mid2 << endl;
            cin >> ans;
            if (ans == mid1 * mid2) l = mid2+1;
            else if (ans == mid1 * (mid2 + 1)) l = mid1 + 1, r = mid2;
            else r = mid1;
        }
        cout << "! " << l << endl;
    }
    return 0;
}
```

---

## 作者：_O_v_O_ (赞：0)

[点此查看这个蒟蒻写的该场比赛所有题目的题解](https://www.luogu.com.cn/article/opat7vrj)

我们注意到 $\log_3(1000)$ 接近 $7$，于是考虑三分。

具体来说，我们假设三分到了 $mid1,mid2$，每次输出 $\tt ?\ mid1\ mid2$，如果输入的数 $x=mid\times mid2$，那么 $l=mid2$，如果 $x=mid\times (mid+1)$，$l=mid1,r=mid2$，否则 $r=mid1$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+5;
int T;
int x;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>T;
	while(T--){
		int r=1000,l=0;
		while(l+1<r){
			int mid=(r-l)/3+l,mmid=(r-l)/3*2+l+1;
			cout<<'?'<<' '<<mid<<' '<<mmid<<endl;
			cin>>x;
			if(x==mid*mmid) l=mmid;
			else if(x==mid*(mmid+1)) l=mid,r=mmid;
			else r=mid;
		}
		cout<<'!'<<' '<<r<<endl;
	}
	return 0;
}
```

---

## 作者：doby (赞：0)

三分。  

根据题意，每次询问可以同时检查两个位置上的刻度是不是对的。为了尽快减小答案的范围，可以每次将当前区间三等分，询问两个三等分点，根据给出的查询结果可以判断答案在哪个部分，这样每次答案的范围变为原来的 $\frac{1}{3}$，$3^7=2187$ 正好满足题目需求。  

注意最后还需要对 $r-l$ 分类讨论一下，赛时我以为只有 $r-l=1$ 导致 TLE 不止最后还没过掉，令人感叹。  
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,l,r,lmid,rmid,now;
void Solve()
{
	l=2,r=999;
	while(l+2<r)
	{
		lmid=l+(r-l)/3,rmid=r-(r-l)/3;
		cout<<"? "<<lmid<<" "<<rmid<<endl;
		cin>>now;
		if(now==lmid*rmid){l=rmid+1;}
		if(now==lmid*(rmid+1)){l=lmid+1,r=rmid;}
		if(now==(lmid+1)*(rmid+1)){r=lmid;}
	}
	if(l+1==r)
	{
		cout<<"? "<<l<<" "<<l<<endl;
		cin>>now;
		if(now==l*l){cout<<"! "<<r<<endl;}
		else{cout<<"! "<<l<<endl;}
		return;
	}
	cout<<"? "<<l<<" "<<l+1<<endl;
	cin>>now;
	if(now==l*(l+1)){cout<<"! "<<r<<endl;}
	if(now==l*(l+2)){cout<<"! "<<l+1<<endl;}
	if(now==(l+1)*(l+2)){cout<<"! "<<l<<endl;}
}
int main()
{
	cin>>T;
	while(T--){Solve();cout.flush();} 
	return 0;
}
```

---

## 作者：incra (赞：0)

赛后 VP，光速 AK，爽爽爽！

### Sol

考虑到只能询问 $7$ 次，但是问的两条边，所以实际上我们可以问 $14$ 次。

考虑三分，设当前三分区间 $[l,r]$，三分的节点分别为 $m1,m2$，不妨设 $m1<m2$，设询问 $m1,m2$ 的结果为 $x$，接下来分情况讨论：

1. 当 $x=m1\times m2$，此时 $m1,m2$ 均小于 $x$，那么 $r\gets m1-1$。
2. 当 $x=(m1+1)\times m2$，此时 $m1\le x < m2$ 那么 $l\gets m1,r\gets m2-1$。
3. 当 $x=(m1+1)\times (m2+1)$，此时 $x\ge m2$ 那么 $l\gets m2$。

建议读者自行思考二分的开闭区间，对于理解有帮助。

操作次数为 $\log_3 999\le 7$，足以通过 G1 和 G2。
### Code
```
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#include <chrono>
#include <random>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
#define puts(s) cout << (s) << endl
int T;
int main () {
	cin >> T;
	while (T--) {
		int l = 1,r = 999;
		while (l < r) {
			int mid1 = l + (r - l + 1) / 3,mid2 = r - (r - l + 1) / 3;
			cout << "? " << mid1 << ' ' << mid2 << endl;
			int x;
			cin >> x;
			if (x == mid1 * mid2) l = mid2 + 1;
			else if (x == mid1 * (mid2 + 1)) l = mid1 + 1,r = mid2;
			else if (x == (mid1 + 1) * (mid2 + 1)) r = mid1;
			else exit (-1);
		}
		cout << "! " << l << endl;
	}
	return 0;
}
```

---

## 作者：GenesisCrystal (赞：0)

## Solution

考虑到只有 $7$ 次询问，注意到 $[\log_3 1000] = 7$，使用近似三分的一种算法。

令 $a = l + \dfrac{l + r}{3}, b = r - \dfrac{l + r}{3}$，求 $a \times b$ 的面积。设结果为 $x$，如果 $x = a \times b$，那么答案一定在 $b$ 之上，则令 $l = r + 1$；如果 $x = a \times (b + 1)$，那么没有的一定在 $(a, b]$ 这个区间内，则令 $l = a + 1, r = b$；如果 $x = (a + 1) \times (b + 1)$，则没有的一定小于等于 $a$，则令 $r = a$。

代码很好写，上一题稍微改一下就行了。

###### ~~我才不会告诉你我是不想写呢~~

---

## 作者：__O_v_O__ (赞：0)

这题只有 $7$ 次机会，按照上一题的做法，最多需要 $10$ 次，显然过不了。

观察到：$6<\log_3(999)<7$，我们猜想这题会用三分。

如何三分呢？我们取当前 $l$ 和 $r$ 的三等分点 $m1$ 和 $m2$，再询问 $m1\times m2$ 的矩形，有三种情况：

- 如果结果是 $m1\times m2$，则两个都正确，把 $l$ 置为 $m2$。

- 如果结果是 $m1\times(m2+1)$，则 $m1$ 正确，$m2$ 错误，把 $l$ 置为 $m1$，$r$ 置为 $m2$。

- 如果结果是 $(m1+1)\times(m2+1)$，则两个都错误，把 $r$ 置为 $m1$。

这样，我们每次都能把范围缩小到原来的三分之一，询问次数是满足要求的。

**AC code:**

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
signed main(){
	ios::sync_with_stdio(0),cin>>t;
	while(t--){
		int l=1,r=1000;
		while(l+1<r){
			int mi1=(r-l)/3+l,mi2=(r-l)/3*2+l+1;
			cout<<'?'<<' '<<mi1<<' '<<mi2<<'\n';
			cout.flush();
			int x;
			cin>>x;
			if(x==mi1*mi2)l=mi2;
			else if(x==mi1*(mi2+1))l=mi1,r=mi2;
			else r=mi1;
		}
		cout<<'!'<<' '<<r<<'\n';
		cout.flush();
	}return 0;
}
```

---

## 作者：xxxaIq (赞：0)

# 思路

由于询问次数被限制到了 $7$ 次，那么采用三分法，每次询问 $lmid$ 和 $rmid$，如果返回值等于 $lmid\times rmid$，那么证明这两个值都小了，于是答案就在 $[lmid,r]$。如果返回的值是 $lmid\times(rmid+1)$，那么答案就在 $[lmid+1,rmid]$。如果返回的值是 $(lmid+1)\times (rmid+1)$，那么答案就在 $[l,lmid-1]$。

这样每次就能把答案缩小到原来的 $\frac{1}{3}$ 范围。

# 代码


```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int T;
int main(){
	cin>>T;
	while(T--){
		int l=2,r=999,lmid,rmid;
		while(l<=r){
			lmid=l+(r-l)/3,rmid=r-(r-l)/3;
			cout<<"? "<<lmid<<" "<<rmid<<endl;
			int x;
			cin>>x;
			if(x==(rmid+1)*(lmid+1)){
				r=lmid-1;
			}else if(x==lmid*(rmid+1)){
				l=lmid+1,r=rmid-1;
			}else{
				l=rmid+1;
			}
		}
		cout<<"! "<<l<<endl;
	}
	return 0;
}
```

---

## 作者：zxh923 (赞：0)

# CF1999G2 Ruler (hard version) 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1999G2)

### 思路

发现 $3^7>1000$，于是考虑能不能每次缩小到原来可能答案区间的 $\dfrac13$。

分类讨论一下，如果我们询问 $(x,y)$ 会发生什么，注意这里 $x\le y$。

+ 返回 $(x+1)\times(y+1)$，此时答案不超过 $x$。

+ 返回 $x\times(y+1)$，此时答案大于 $x$，不超过 $y$。

+ 返回 $x\times y$，此时答案大于 $y$。

于是我们使用三分来找出我们这次询问的 $(x,y)$ 即可。

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define N 200005
using namespace std;
int T;
void solve(){
	int l=1,r=999,res=1;
	while(l<r){
		int mid1=l+(r-l)/3;
		int mid2=r-(r-l)/3;
		cout<<"? "<<mid1<<' '<<mid2<<'\n';
		int x;
		cin>>x;
		if(x==(mid2+1)*mid1){
			l=mid1+1;r=mid2;
		}
		else if(x==(mid1+1)*(mid2+1)){
			r=mid1;
		}
		else l=mid2+1;
	}
	cout<<"! "<<l<<'\n';
} 
signed main(){
	cin>>T;
	while(T--){
		solve();
	}
	return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：0)

实际上简单版的二分想出来之后，再看到生怕你看不出来做法的询问次数限制，这题的做法也不难想了。

三分。

猜数字的另一种形式，假设当前知道答案在 $[l,r]$ 当中：

找到将区间“三等分”的两个点 $l_1$ 和 $l_2$（假设 $l_1\le l_2$），并向程序询问：

如果返回 $(l_1+1)\times(l_2+1)$，答案必然在 $[l,l_1]$ 中。

如果返回 $l_1\times(l_2+1)$，答案必然在 $[l_1+1,l_2]$ 中。

如果返回 $l_1\times l_2$，答案必然在 $[l_2+1,r]$ 中。

一次可以将区间的长度变为原来的 $\dfrac{1}{3}$，可以通过本题。

另外注意，询问的时候数字不能大于 $1000$（赛时因为这个挂了）。

代码：


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	int t;
	scanf("%lld",&t);
	while(t--){
		int l=2,r=999,l1,l2,ans;
		while(l<=r){
			l1=l+(r-l)/3;
			l2=r-(r-l)/3;
			printf("? %lld %lld",l1,l2);
			cout<<endl;
			int s;
			scanf("%lld",&s);
			if(s==(l1+1)*(l2+1)){
				r=l1-1;
				ans=l1;
			}
			else if(s==l1*(l2+1)){
				l=l1+1;
				ans=l1+1;
				r=l2-1;
			}
			else{
				ans=l2+1;
				l=l2+1;
			}
		}
		printf("! %lld",ans);
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：wmrqwq (赞：0)

需要我教你怎么 AK div.4 吗？

# 题目链接

[CF1999G1](https://www.luogu.com.cn/problem/CF1999G1)

[CF1999G2](https://www.luogu.com.cn/problem/CF1999G2)

# 解题思路

考虑三分。

我们发现，我们每次可以给出两个数字来作为限制。

因此我们可以将这两个数字设为断开区间的点，由于尺子上缺少的数字只有一个，因此我们可以通过每一次询问来减少 $\dfrac{2}{3}$ 的剩余区间长度。

询问次数 $\log_3 V$ 次，可以通过 G1 和 G2，其中 $V$ 为值域。

# 参考代码

```cpp
/*
Tips:

你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
//#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define x first
#define y second
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
ll pw(ll x,ll y,ll mod){if(x==0)return 0;ll an=1,tmp=x;while(y){if(y&1)an=(an*tmp)%mod;tmp=(tmp*tmp)%mod;y>>=1;}return an;}
void Max(ll&x,ll y){x=max(x,y);}
void Min(ll&x,ll y){x=min(x,y);}
ll _t_;
void _clear(){}
ll n,m;
ll ans,An;
ll ask(ll x,ll y){
	cout<<"? "<<x<<' '<<y<<endl;
	ll z;
//	An++;
	cin>>z;
//	z=(x+(x>=ans))*(y+(y>=ans));
	return z;
}
/*
8
*/
ll L,R;
void solve()
{
	_clear();
	L=2,R=999;
	while(L<R)
	{
		ll Mid1=L+(R-L)/3,
		   Mid2=R-(R-L)/3;
		ll now=ask(Mid1,Mid2);
		if(now==Mid1*Mid2)
			L=Mid2+1;
		else if(now==Mid1*(Mid2+1))
			L=Mid1+1,R=Mid2;
		else
			R=Mid1;
	}
	cout<<"! "<<L<<endl;//<<" queries = "<<An<<endl;
	An=0;
}
int main()
{
//	IOS;
	_t_=1;
 	cin>>_t_;
	while(_t_--)
		solve();
// 	forl(i,2,_t_)
//		ans=i,solve();
	QwQ;
}
```

---

## 作者：Heldivis (赞：0)

## CF1999G Ruler

每次询问，可以获得两个信息，如果使用二分，一定有一个信息是没用的。考虑三分。

令 $lmid = l + \lfloor\dfrac{r-l}3\rfloor, rmid = r -  \lfloor\dfrac{r-l}3\rfloor$。询问 $(lmid,rmid)$，得到结果 $res$。

- $res = lmid \times rmid$，说明缺失的数一定大于 $rmid$，那么令 $l \gets rmid + 1$。
- $res = lmid \times (rmid + 1)$，说明缺失的数一定在区间 $(lmid, rmid]$ 内，那么令 $l \gets lmid + 1,r\gets rmid$。
- $res = (lmid+1) \times (rmid+1)$，说明缺失的数一定小于等于 $lmid$，那么令 $r \gets lmid$。

只要 $l<r$ 便一直操作，每次让区间缩小到原来的三分之一，询问次数约为 $\log_31000\approx6.29$，可以通过。

代码：

```cpp
void Main() {
  int l = 1, r = 1000;
  while (l < r) {
    int lmid = l + (r - l) / 3, rmid = r - (r - l) / 3;
    cout << "? " << lmid << " " << rmid << endl;
    int res;
    cin >> res;
    if (res == -1) exit(0);
    if (res == (lmid) * (rmid)) l = rmid + 1;
    if (res == (lmid) * (rmid + 1)) l = lmid + 1, r = rmid;
    if (res == (lmid + 1) * (rmid + 1)) r = lmid;
  }
  cout << "! " << l << endl;
}
```

---

## 作者：Wei_Han (赞：0)

在 G1 中，我们的策略是二分，每次选择一个点和 $1$ 求一下面积，因为 $1$ 永远不会变，而另一个点也具有单调性，所以比较次数是 $O(\log_2 n)$ 的，大约有 $10$ 次，无法通过本题，考虑进一步优化。其实能够发现，我们没有必要每次与 $1$ 做比较，可以再选一个点，虽然是面积，但是增加的值只有 $1$，我们可以直接判断。假如将一个点匹配或者不匹配看做 $1$ 和 $0$，那么在答案 $x$ 左右两段的值是具有单调性的，或者说全部相同，那我们就可以考虑三分了，每次可以选定两个点查询，如果左右两点都是 $1$，那么左端点扩展到更靠右的点，反之都是 $0$ 同理，假如一个 $0$ 一个 $1$，那么答案就在这两个点之间，拿这两个点更新左右端点即可。这样的比较次数是 $\log_3 10^3 \approx 6$ 次左右，可以通过。

注意特判最后的小区间。

```cpp
// LUOGU_RID: 171079790
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define pr putchar('\n')
#define pp putchar(' ')
#define pii pair<ll,ll>
#define mem(aa,bb) memset(aa,bb,sizeof(aa))
#define fo(a,i,b) for(ll i = a ; i <= b ; ++ i )
#define Fo(a,i,b) for(ll i = a ; i >= b ; -- i )
//#pragma GCC optimize(2)
using namespace std;
typedef long long ll;
typedef __uint128_t ui128;
typedef __int128 i128;
typedef unsigned long long ull;
const int N=2e5+10,M=2e5;
inline void read(ll &opp){ll x=0,t=1;char ch;ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-'){t=-1;}ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}opp=x*t;return; }
inline void wr(ll x){if(x<0){putchar('-');x=-x;}if(x>9){wr(x/10);}putchar(x%10+'0');}

ll t;

signed main(){
	cin>>t;
	while(t--){
		ll l=1,r=999;
		while(l+1<r){
			if(l+2<r){
				ll L=(l*2+r)/3,R=(l+r*2)/3,sum;
				cout<<"? "<<L<<" "<<R<<endl;
				cin>>sum;
				if(sum==L*R) l=R;
				else if(sum==L*(R+1)) l=L,r=R; 
				else r=L;
			}
			else{
				ll mid=l+r>>1;
				cout<<"? "<<1<<" "<<mid<<endl;
				ll sum;cin>>sum;
				if(sum==1*mid) l=mid;
				else r=mid;
			}
		}
		cout<<"! "<<r<<endl;
	}
	return 0;
}	
``````

---

