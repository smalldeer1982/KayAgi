# [ABC230D] Destroyer Takahashi

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc230/tasks/abc230_d

$ N $ 行 $ 10^9 $ 列の格子状の区画に区切られた街に $ N $ 枚の壁があり、$ 1 $ から $ N $ までの番号が割り振られています。  
 壁 $ i $ は上から $ i $ 行目、左から $ L_i $ 列目から $ R_i $ 列目の範囲にあります。(入出力例 $ 1 $ の図も参考にしてください。)

高橋君は $ N $ 枚の壁をすべて破壊することにしました。  
 超人的な腕力を持つ高橋君は、$ 1 $ 回のパンチで連続する $ D $ 列にまとめてダメージを与えることができます。

- より厳密に言い換えると、$ 1 $ 以上 $ 10^9\ -\ D\ +\ 1 $ 以下の **整数** $ x $ を選んで、$ x $ 列目から $ x\ +\ D\ -\ 1 $ 列目に (一部でも) 存在するすべての破壊されていない壁にパンチによるダメージを与えることができます。

壁は一部分でもダメージを受けると、パンチの衝撃波により全体が木っ端みじんに破壊されてしまいます。  
 (入出力例 $ 1 $ の説明も参考にしてください。)

高橋君がすべての壁を破壊するには、少なくとも何回のパンチを放つ必要がありますか？

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ D\ \leq\ 10^9 $
- $ 1\ \leq\ L_i\ \leq\ R_i\ \leq\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

入力例 $ 1 $ に対応する壁の配置を図示したものが下図です。 !\[image\](https://img.atcoder.jp/ghi/b7b9e6741514f51c6c0aac924589c9d2.png) たとえば次のようにパンチを放つことで、 $ 2 $ 回のパンチですべての壁を破壊することができます。(以下の説明では、$ a $ 列目から $ b $ 列目までの範囲を $ \lbrack\ a,\ b\ \rbrack $ と表記します。) - まず、 $ \lbrack\ 2,\ 4\ \rbrack $ にパンチを放つ。 $ \lbrack\ 2,\ 4\ \rbrack $ に存在する壁である壁 $ 1 $ と壁 $ 2 $ はダメージを受け、破壊される。 - 次に $ \lbrack\ 5,\ 7\rbrack $ にパンチを放つ。$ \lbrack\ 5,\ 7\rbrack $ に存在する壁 $ 3 $ はダメージを受け、破壊される。 また、次の方法でもすべての壁を $ 2 $ 回のパンチで破壊することができます。 - まず、$ \lbrack\ 7,\ 9\ \rbrack $ にパンチを放ち、壁 $ 2 $ と壁 $ 3 $ を破壊する。 - 次に、$ \lbrack\ 1,\ 3\ \rbrack $ にパンチを放ち、壁 $ 1 $ を破壊する。

### Sample Explanation 2

入出力例 $ 1 $ と比べると、壁 $ 3 $ の範囲が $ \lbrack\ 5,\ 9\ \rbrack $ から $ \lbrack\ 4,\ 9\ \rbrack $ に変わりました。 この場合は $ \lbrack\ 2,\ 4\ \rbrack $ にパンチを放つことで $ 1 $ 回ですべての壁を破壊できます。

## 样例 #1

### 输入

```
3 3
1 2
4 7
5 9```

### 输出

```
2```

## 样例 #2

### 输入

```
3 3
1 2
4 7
4 9```

### 输出

```
1```

## 样例 #3

### 输入

```
5 2
1 100
1 1000000000
101 1000
9982 44353
1000000000 1000000000```

### 输出

```
3```

# 题解

## 作者：Wi_Fi (赞：4)

非常经典的一类区间贪心问题。

形式化题意：给定 $n$ 个闭区间 $[a_i,b_i]$，请你在数轴上选择尽量少的点，使得每个区间内至少包含一个选出的点。

然后解法就很清晰了。贪心需要排序，这里很明显不是根据左端点就是右端点排序，不难证明，打破一堵墙的右端点会打破更多的墙，所以我们根据右端点排序即可。

代码：
```cpp
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
struct wa
{
	int l,r;
}a[N];
bool cmp(wa a,wa b)
{
	if(a.r!=b.r)return a.r<b.r;
	return a.l<b.l;
}
int i,n,d,now,ans;
int main()
{
	cin>>n>>d;
	for(i=1;i<=n;i++)cin>>a[i].l>>a[i].r;
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=n;i++)if(a[i].l>now)ans++,now=a[i].r+d-1;
	cout<<ans;
	return 0;
}
```


---

## 作者：ICE__LX (赞：2)

### 题意
你处于位置 $0$，你面前有 $n$ 堵 $l_i$ 起到 $r_i$ 的墙，你的拳头命中位置 $k$ 的墙，那么所有 $l_i\le k$ 的墙都会被破坏，问至少打出几拳才能将所有墙破坏掉。  
### 具体思路
先对所有的墙进行排序，以 $r_i$ 大小为基准从升序排列，然后用一个变量 $rs$ 记录破坏的范围。如果 $l_i\le rs$，代表第 $i$ 堵墙已经被破坏，反之没有，这就需要再打出一拳，答案数加一。直接线性枚举的时间复杂度为 $O(n)$，可以通过此题，但仍可以继续优化，排序后的数据是有序的，不难想到用二分直接找到 $l_i> rs$ 的墙，更新答案后继续查找，直到所有的墙都被破坏，算法结束。虽然时间复杂度仍为 $O(n)$，但效率相对线性枚举更好。[线性](https://www.luogu.com.cn/record/180940360) VS [二分](https://www.luogu.com.cn/record/181108638)，效果十分明显。  
时间主要花在排序上，总时间复杂度为 $O(n\log n)$。
### 代码实现
我们需要以 $r_i$ 大小为基准对数据排序，但有一种偷懒的方法，用 pair 来储存数据，pair 在比较时会先比较第一个数据，因此我们让 $r_i$ 为 pair 的第一个数据，这样就不用写比较函数啦。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int maxn=200005;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
pair<int,int>a[maxn];
int n,d,rs,h;
int main() {
    n=read(),d=read();
    rep(i,1,n){
    	int l=read(),r=read();
    	a[i]=make_pair(r,l);
	}
	sort(a+1,a+n+1);
	rep(i,1,n){
		if(rs<=a[i].second){
			h++;
			rs=a[i].first+d;
			int l=i+1,r=n;
			while(l<=r){
				int mid=(l+r)>>1;
				if(rs>a[i].second)l=mid+1;
				else r=mid-1;
			}
			if(r<n){
			i=l-1;	
			}
		}
	}
	cout<<h;
}
```

---

## 作者：qhr2023 (赞：1)

## 思路

显然的贪心问题。

实质是给定 $n$ 个区间，在数轴上选择尽量少的点，使得每个区间内至少包含一个选出的点。

不难证明，打破墙的右端会更优，所以根据右端点排序，然后每次找到一个没有被打破的墙，就将这堵墙的右端点打破并往后找，摧毁所有在当前可以一起打破的墙，同时答案加一。最后输出答案即可。

## code

```cpp
#include<bits/stdc++.h> 
using namespace std;
struct node{
	int l, r;
} a[200005];
int n, d, l, r, ans, x=-0x3f3f3f3f;
bool cmp(node a, node b){
	if(a.r!=b.r)
		return a.r<b.r;
	return a.l<b.l;
}
int main(){
	cin >> n >> d;
	for(int i=1; i<=n; i++)
		cin >> a[i].l >> a[i].r;
	sort(a+1, a+n+1, cmp);
	for(int i=1; i<=n; i++)
		if(x+d-1<a[i].l)
			ans++, x=a[i].r;
	cout << ans;
	return 0;
}
```

---

## 作者：hhztl (赞：1)

## 题意简述
有 $n$ 个区间，我们每次可以标记一段长为 $d$ 的区间，求最少操作几次才能保证每个区间都有点被标记。
## 算法分析
考虑使用贪心算法。先排序，接着枚举每一个区间。为保证每个区间都有点被标记，所以我们标记的左端点应放在当前区间的最右端。而后**所有被这次操作标记过的区间**都可以直接跳过。

就这样讲讲估计还是听不懂。所以——
## 上代码！
```
#include<bits/stdc++.h>//万能头yyds
using namespace std;
struct node{int l,r;}a[200010];//结构体方便排序
int n,d,sum,k;
bool cmp(node x,node y){return x.r<y.r||x.r==y.r&&x.l<y.l;}
int main(){
    cin>>n>>d;
    for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r;
    sort(a+1,a+n+1,cmp);//快排
    for(int i=1;i<=n;){
        k=i+1;//当前区间的下一区间
        while(k<=n&&a[k].l<a[i].r+d)k++;//如果第k个区间被标记，跳过
        sum++;//操作数++
        i=k;//更新i
    }cout<<sum;
}
```
**请勿抄袭，后果自负！**

管理员辛苦啦！

---

## 作者：Symbolize (赞：1)

# $\tt{Solution}$
贪心应该是非常容易看出来的，由于每次都能摧毁整列，所以说不需要在二维的平面上思考，换句话说，也就是墙的先后顺序是完全没有关系的，那么就可以排序了。如何排序？对于一堵墙，显然是在破坏它之前的墙的时候就已经将其破坏掉最好，如果发现它还没被便利过，毫无疑问的，肯定是在它的右端点打一拳，因为这样不仅能破坏当前这堵墙，还可以尽可能的破坏他之后的墙，所以说，以右端点为第一关键字排序，每次记录当前破坏到的位置，如果当前枚举的墙的左坐标在其之前，则说明其被破坏过，跳过即可，否则则需要将当前破坏的位置，更新成当前枚举的位置的右坐标加 $D$。

```cpp
/*
	Luogu name: Symbolize
	Luogu uid: 672793
*/
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(register int i=l;i<=r;++i)
#define rep2(i,l,r) for(register int i=l;i>=r;--i)
#define rep3(i,x,y,z) for(register int i=x[y];~i;i=z[i])
#define rep4(i,x) for(auto i:x)
#define debug() puts("----------")
const int N=2e5+10;
const int inf=0x3f3f3f3f3f3f3f3f;
using namespace std;
int n,d,ans;
pii a[N];
int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
bool cmp(pii x,pii y)
{
	if(x.y==y.y) return x.x<y.x;
	return x.y<y.y;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	d=read();
	rep1(i,1,n) a[i].x=read(),a[i].y=read();
	sort(a+1,a+n+1,cmp);
	int last=0;
	rep1(i,1,n)
	{
		if(last>=a[i].x) continue;
		++ans;
		last=a[i].y+d-1;
	}
	cout<<ans<<endl;
	return 0;
}

```

---

## 作者：xiaomuyun (赞：1)

- [Luogu 传送门](https://www.luogu.com.cn/problem/AT_abc230_d)
- [Atcoder 传送门](https://atcoder.jp/contests/abc230/tasks/abc230_d)

## 思路分析

考虑贪心。

对于每堵墙，将它的右端点从小到大排序。然后每次找到一个没有被打破的墙，就将这堵墙的右端点打破并往后找，摧毁所有一部分在当前右端点 $x$ 到 $x+D-1$ 这个区间范围内（也就是刚刚那一击可以同时打破）的墙，同时计数器加一。最后输出答案即可。

## 代码实现

```cpp
#include<algorithm>
#include<cstdio>
using namespace std;
typedef long long ll;
ll n,d,res=0;
struct Walls{
	ll l,r;
	bool operator <(const Walls &w) const{//定义排序的规则
		return r<w.r;
	}
}a[200001];
int main(){
	scanf("%lld%lld",&n,&d);
	for(ll i=1;i<=n;++i) scanf("%lld%lld",&a[i].l,&a[i].r);
	sort(a+1,a+1+n);
	for(ll i=1;i<=n;){
		ll cur=i+1;
		while(a[cur].l<=a[i].r+d-1&&cur<=n) ++cur;//打破所有可以打破的墙
		i=cur,++res;
	}
	printf("%lld\n",res);
	return 0;
}
```

---

## 作者：guer_loser_lcz (赞：0)

# 题解
## 思路
考虑贪心，因为要求最小值。

因为一拳打的是若干列，所以这题跟二维没关系，只用考虑一维。

按右端点排序，每次打一堵墙的右端点，看打到哪堵墙，再下一拳打下一堵没碎的墙的右端点，重复以上操作，直到打完墙。
## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,d;
struct le{
	int l,r;
}a[200100];
bool cmp(le a,le b){
	return a.r<b.r;
}//右端点排序
int main(){
	cin>>n>>d;
	for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r;
	sort(a+1,a+n+1,cmp);//排序
	int ans=0,len=0;
	for(int i=1;i<=n;i++){
		if(len<a[i].l){
			len=a[i].r+d-1;
			ans++;
		}//如果距离超了，就再打一拳。
	}
	cout<<ans;//一共要几拳
	return 0;
} 
```

---

## 作者：Liuhy2996 (赞：0)

## 思路
按右端点从小到大排序，遍历所有墙，若一堵墙没有被打碎，则打碎第 $r_i$ 到第 $r_i+d-1$ 列里的墙。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,d,cnt,pos;
struct A{
	int l,r;
}a[200005];
bool cmp(A x,A y){
	return x.r<y.r;
}
signed main(){
	cin>>n>>d;
	for(int i=1;i<=n;++i) cin>>a[i].l>>a[i].r;
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;++i)
		if(pos<a[i].l) ++cnt,pos=a[i].r+d-1;
	cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：YFF1 (赞：0)

## 思路：
在该题中，我们需要通过最少次数来击碎所有的墙。使用贪心的做法，我们会发现每次击打时仅需在两堵墙中间打一拳就可以同时打到两堵墙。如果有一堵墙无法通过这种方式击碎，则需要再补上一拳。这道题的做法类似于贪心问题中经典的“求最大不相交区间”。
## 代码：
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,d;
struct node{
	int l,r;
}a[200005];
bool cmp(node a,node b){
	if(a.r==b.r)return a.l<b.l;
	return a.r<b.r;//按照墙的左端点排序
}
signed main () {
	cin>>n>>d;
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&a[i].l,&a[i].r);
		a[i].r+=d-1;
	}
	sort(a+1,a+1+n,cmp);//该做法是建立在每一堵墙都是有序的基础上的
	int pos=1;
	long long cnt=1;
	for(int i=2;i<=n;i++){
		if(a[i].l>a[pos].r){
			pos=i;
			cnt++;
		}
	}//参考了求最大不相交区间的代码
	cout<<cnt;
	return 0;
}
```

---

## 作者：__hjwucj__ (赞：0)

# 题解：AT_abc230_d [ABC230D] Destroyer Takahashi

[题目传送门](/problen/AT_abc230_d)

## 思路

考虑 $\color {red}贪心$。

题意：给定 $n$ 个闭区间 $[a_i,b_i]$，请你在数轴上选择尽量少的点，使得每个区间内至少包含一个选出的点。

那么思路就很清晰了。

我们先按右端点排序，因为，如果打破左端点，那还需要右边打破更多的墙。所以，我们打破右端点，价值更高。

然后，我们可以使用一个变量 $p$ 来存储当前打到了第几座墙。当 $a_i$（左端点）没有被打破时，次数加 $1$，更新 $p$。

## 代码参考

```cpp
#include <bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define fin(x) freopen (x,"r",stdin)
#define fout(x) freopen (x,"w",stdout)
using namespace std;
typedef pair<int,int> dt;
int n,d,s=0,p=0;
inline bool cmp (dt x,dt y) {return x.se<y.se||(x.se==y.se&&x.fi<y.fi);}
signed main ()
{
	cin>>n>>d;
	vector<dt> a (n+1);
	for (int i=1;i<=n;i++) cin>>a[i].fi>>a[i].se;
	sort (a.begin ()+1,a.end (),cmp);
	for (int i=1;i<=n;i++)
		if (p<a[i].fi) s++,p=a[i].se+d-1;
	cout<<s;
	return 0;
}
```

---

## 作者：xvl_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc230_d)

一道贪心题。

我们可以将每一堵墙的右端点从小到大进行排序，然后我们从第 $1$ 堵墙开始看，将在第 $1$ 堵墙的右端点打破后会倒塌的墙全部跳过，去看下一堵还没被打破的墙。可以证明这是最优解。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n, d, ans;
struct xvl_ {
    int l, r;
    bool operator < (const xvl_& s) const {
        return r < s.r;
    }
}a[200005];
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> d;
    for (int i = 1; i <= n; i++) cin >> a[i].l >> a[i].r;
    sort(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ans++) {
        int bk = i + 1; 
        while (a[bk].l <= a[i].r + d - 1 and bk <= n) bk++;
        i = bk; // 前面的墙被打破了
    }
    cout << ans;
    return 0;
}

/*
0 1 2 3 4 5 7 8 9 …
1 ---
2       -----
3         -------

0 1 2 3 4 5 7 8 9 …
1 ---
2       -----
3       ---------
*/
```


---

## 作者：loser_seele (赞：0)

题意：给定若干个闭区间，每次选定一条长度为 $ N $ 的线段，把与这条线段有交集的所有区间删除，问最少操作次数。

考虑贪心。首先把区间按右端点递增的顺序排序，然后遍历所有区间，记录一个变量 $ last $，每遇到一个新的区间的左端点的时候如果还在 $ last+N-1 $ 的范围内则忽略，否则更新 $ last $ 为当前左端点，答案增加即可。

可以证明这样一定是最优的，因为无论怎么选择区间左端点都应该被优先考虑，因为选择左端点与上一次选择的答案重叠部分总是更多，所以每次都优先选取。

时间复杂度 $ \mathcal{O}(n\log{n}) $，可以通过。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge
{
int b,e;
}datai[200020];
bool cmp(edge a,edge b)
{
return a.e<b.e;
}
int d,n;
int main()
{
ios::sync_with_stdio(0);
cin>>n>>d;
for(int i=1;i<=n;i++)
cin>>datai[i].b>>datai[i].e;
sort(datai+1,datai+n+1,cmp);
int last=-1e9;
int ans=0;
for(int i=1;i<=n;i++)
if(datai[i].b>last)
last=datai[i].e+d-1,ans++;
cout<<ans;
}
```


---

