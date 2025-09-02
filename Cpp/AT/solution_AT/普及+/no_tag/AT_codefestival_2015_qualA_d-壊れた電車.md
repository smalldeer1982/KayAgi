# 壊れた電車

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-quala/tasks/codefestival_2015_qualA_d

高橋鉄道では、$ N $ 両編成の電車の一部が壊れてしまったため、$ M $ 人の整備士が点検をすることになりました。

$ i $ 人目の整備士ははじめ、$ X_i $ 両目の車両にいます。それぞれの整備士は、今いる車両を点検することと、隣の車両に移動することができます。車両の点検には時間はかかりませんが、隣の車両に移動するには $ 1 $ 分かかります。

全ての車両を少なくとも $ 1 $ 人の整備士が点検した状態になると点検作業は終了となります。点検作業は最短何分で終了させることができるでしょうか。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ N\ ≦\ 100 $ を満たすデータセットに正解した場合は、$ 20 $ 点が与えられる。
- $ N\ ≦\ 500,000 $ を満たすデータセットに正解した場合は、上記とは別に $ 60 $ 点が与えられる。
- 追加の制約のないデータセットに正解した場合は、上記とは別に $ 20 $ 点が与えられる。

### Sample Explanation 1

下の図のように整備士が移動すれば $ 3 $ 分で点検作業を終了させることができます。 !\[figure1\](https://code-festival-2015-quala.contest.atcoder.jp/img/other/code\_festival\_2015\_quala/BrokenDensya.png)

## 样例 #1

### 输入

```
17 5
1
5
10
15
16```

### 输出

```
3```

## 样例 #2

### 输入

```
66 10
8
9
16
23
37
47
51
52
53
64```

### 输出

```
8```

# 题解

## 作者：YujinSharp (赞：1)

~~水一篇题解。~~  




---


第一个样例在的 AtCoder 上解释如下图：
![](https://code-festival-2015-quala.contest.atcoder.jp/img/other/code_festival_2015_quala/BrokenDensya.png)
~~实则无用。~~  


---

由于 RMJ 不能正常使用，只能在 AtCoder 上提交。  
![](https://cdn.luogu.com.cn/upload/image_hosting/wmxlaelr.png)


---


### 解题方法：  
本题询问最小值，通过对题目的理解，可以分析出不同方式得到的总时间具有单调性，很容易想到使用二分答案。  

**注意：答案具有单调性是二分答案法可行的必要前提。**

对于整数类型的二分题，我们通常有以下模版：

```cpp
bool check(mid){
//......
}
//......
while(l<=r) {
		mid=(l+r)/2;
		if(check(mid)) {
			r=mid-1;
			ans=mid;
		} else {
			l=mid+1;
		}
	}
```
对于本题，我们定义答案变量为 $ans$，二分的中点为 $mid$。  


---


## 具体思路：  
`while(l<=r){ }`为模版语句部分，不作赘述。 

对于`check()`函数，我们定义一个变量`tans`用于统计在限定时间内 $x_i$ 所能修理的车厢数，此时，可能存在以下几种情况：  

1. 在 $mid$ 时间内 $x_i$ 根本无法到达 $mid$，显然不可取。
2. 在 $mid$ 时间内 $x_i$ 到达 $mid$ 位置后，$x_i$ 相较 $mid$ 更小，设 $x_i$ 与 $mid$ 相差的距离为 $l$，则此时的 $tans$ 应为 $\max(x_i+mid−2×l+1,x_i+\frac{mid-l}{2}+1)$，即抉择 $x_i$ 走到 $mid$ 再折返走与先向另一方向走再折返回到 $mid$ 两种情况哪一种价值更大。
3. 当 $mid$ 时间内 $x_i$ 到达 $mid$ 位置后，$x_i$ 相较 $mid$ 更大，直接将 $tans$ 设为 $x_i+mid+1$。

于是我们得到下面代码：

```cpp
bool check(ll mid) {
	ll tans=1;
	for(ll i=1; i<=m; i++) {
		if(tans>n) {//前后各一次，防止漏判
			return true;
		}
		if(x[i]-tans>mid) {//情况1
			return false;
		} else if(x[i]-tans>0) {//情况2
			tans=x[i]+max(mid-2*x[i]+2*tans,(mid-x[i]+tans)/2)+1;
		} else {//情况3
			tans=x[i]+mid+1;
		}
	}
	if(tans>n) {//前后各一次，防止漏判
		return true;
	}
}
```
## 几点重要提醒：
**一、注意速度问题。**   
使用`cin`、`cout`语句进行读入与输出的同学，应注意在主函数开头加入以下语句以关闭同步，提升速度。
```cpp
ios::sync_with_stdio(false);
cin.tie(0);
cout.tie(0);
```
否则如下图。  
![](https://cdn.luogu.com.cn/upload/image_hosting/gd609r1i.png)  


---

**二、注意数据大小。**  
不开`long long`见祖宗，使用`typedef long long ll`可使代码精简化。


---


**三、文末换行。**  
早期的 AtCoder 题目要求结尾必须输出回车空行，否则会 WA。


---

最后给出完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=100010;
ll n,m,ans,l,r,mid,x[N];
bool check(ll mid) {
	ll tans=1;
	for(ll i=1; i<=m; i++) {
		if(tans>n) {
			return true;
		}
		if(x[i]-tans>mid) {
			return false;
		} else if(x[i]-tans>0) {
			tans=x[i]+max(mid-2*x[i]+2*tans,(mid-x[i]+tans)/2)+1;
		} else {
			tans=x[i]+mid+1;
		}
	}
	if(tans>n) {
		return true;
	}
}
main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin>>n>>m;
	r=2*n;
	for(ll i=1; i<=m; i++) {
		cin>>x[i];
	}
	while(l<=r) {
		mid=(l+r)/2;
		if(check(mid)) {
			r=mid-1;
			ans=mid;
		} else {
			l=mid+1;
		}
	}
	cout<<ans<<"\n";
}
```

---

## 作者：nkrqzjc_zzz (赞：1)

### [题目链接](https://www.luogu.com.cn/problem/AT_codefestival_2015_qualA_d)
### 方法

这题数据够大，能用的方法十分有限，又要你求最小时间，所以可以自认而然的想到用二分答案解决此题。

------------


二分答案枚举总时间，check 函数如下：
```cpp
//a[i]为第i个人的位置
//cet代表二分答案枚举的时间
//dn代表在cet里前i个检修员最多能修到的地方
bool check(long long cet){
	long long dn=1;
	for(long long i=1;i<=m;i++){
		if(dn>n)return 1;//若dn>n那么表明已经可以修完全部了返回true
		if(a[i]-dn>cet)return 0;//若a[i]-dn>cet表明在规定时间内到达不了固定地点返回false
		else if(a[i]-dn>0){//若a[i]-dn>0，就相当于cet时间内检修员ai可以到达cet位置，且ai相较cet更为靠前。则此时的dn应该变为a[i]+1加上cet-2*a[i]+2*dn和(cet-a[i]+dn)/2的较大值。就是选择走到dn在向前走或先向前再往后回dn的两种情况哪种走的更远
			dn=a[i]+std::max(cet-2*a[i]+2*dn,(cet-a[i]+dn)/2)+1;
		}
		else dn=a[i]+cet+1;//剩下的情况只有cet时间里在ai可以到cet并且ai在后面cet时可直接将dn更新到ai+cet+1
	}
	return dn>n;
}
```


------------

另外，这到题有一个~~小~~问题。它的答案之后必须**换行**！不然呵呵呵……像我一样错两次，人很懵，看其他大佬的代码，大差不差都是二分答案，最后发现少了个空格，汗流浃背！

![](https://cdn.luogu.com.cn/upload/image_hosting/b4usofda.png)

 

------------


### AC code

```cpp
#include<ios>
long long n,m,a[100002];
bool check(long long cet){
	long long dn=1;
	for(long long i=1;i<=m;i++){
		if(dn>n)return 1;
		if(a[i]-dn>cet)return 0;
		else if(a[i]-dn>0){
			dn=a[i]+std::max(cet-2*a[i]+2*dn,(cet-a[i]+dn)/2)+1;
		}
		else dn=a[i]+cet+1;
	}
	return dn>n;
}
long long dn,le,ri,cet;
main(){
	scanf("%d%d",&n,&m);
	ri=2*n;
	for(long long i=1;i<=m;i++)scanf("%lld",&a[i]);
	while(le<=ri){
		cet=(le+ri)/2;
		if(check(cet))ri=cet-1,dn=cet;
		else le=cet+1;
	}
	printf("%lld\n",dn);
}
```


---

## 作者：_Flame_ (赞：1)

## 思路

想了挺久的题。

首先看到数据范围，可以想到是二分答案。

二分一个时间 $mid$，设一个 $cnt$ 为 $mid$ 时间下前 $i$ 个检修员最多能检修到的车厢，这时对于每个检修员 $a_i$，有以下几种情况。

- 在 $mid$ 时间内检修员 $a_i$ 无法到达 $mid$ 位置，这种情况肯定不成立。

- 当 $mid$ 时间内检修员 $a_i$ 可以到达 $mid$ 位置，且 $a_i$ 相较 $mid$ 更为靠前，设 $a_i$ 与 $mid$ 相差的距离为 $l$，则此时的 $cnt$ 应更新到 $a_i+mid-2\times l+1$ 与 $a_i+\frac{mid-l}{2}+1$ 中的更大值，即 $a_i$ 走到 $cnt$ 在向前走与先向前再折返回到 $cnt$ 两种情况下走的更远的那一种。

- 当 $mid$ 时间内检修员 $a_i$ 可以到达 $mid$ 位置，且 $a_i$ 相较 $mid$ 更为靠后时，直接将 $cnt$ 更新到 $a_i+mid+1$ 处即可。

最后判断 $cnt$ 是否大于 $n$ 即可。

注意时间最大值要开到 $2\times n$。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define _int __int128
#define y1 _
using namespace std;

static char buf[1000000],*p1=buf,*p2=buf;

inline int read(){
	char c=getchar();
	int res=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		res=res*10+c-'0';
		c=getchar();
	}
	return res*f;
}

inline void write(int x){
	static char buf[20];
	static int len=-1;
	if(x<0){
		putchar('-');
		x=-x;
	}
	do{
		buf[++len]=x%10;
		x/=10;
	}
	while(x);
	while(len>=0){
		putchar(buf[len--]+48);
	}
}

const int maxn=301000;
const int maxm=110;
const int mod=1e9+7;
const int inf=1e18;

int n,m;
int a[maxn];

bool check(int mid){
	int cnt=1;
	for(int i=1;i<=m;i++){
		if(cnt>n){
			return 1;
		}
		int l=a[i]-cnt;
		if(l>mid){
			return 0;
		}
		else if(l>0){
			cnt=a[i]+max(mid-2*l,(mid-l)/2)+1;
		}
		else{
			cnt=a[i]+mid+1;
		}
	}
	return cnt>n;
}

void solve(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		a[i]=read();
	}
	int l=0,r=2*n;
	int ans;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}
		else{
			l=mid+1;
		}
	}
	write(ans);
	puts("");
	return ;
}

signed main(){
	int T=1;
	while(T--){
		solve();
	}
	return 0;
}



```

---

## 作者：gdf_yhm (赞：1)

[AT_codefestival_2015_qualA_d](https://www.luogu.com.cn/problem/solution/AT_codefestival_2015_qualA_d)

### 思路

问最少，考虑二分答案。

$O(\log n)$ 枚举答案，需要 $O(n)$ 判断是否可行。

判断答案 $mid$ 是否可行。对 $a_i$ 从小到大排序。对于在 $a_i$ 位置上的第 $i$ 个工人，设前 $i-1$ 个工人能做完 $1$ 到 $lst-1$ 位置上的车厢。贪心可知，该工人需要处理从 $lst$ 到 $a_i$ 中的所有车厢，并尽可能向 $n$ 的方向（左边）推进。

有以下几种情况：

- 如果第 $i$ 个工人无法在 $mid$ 步内到达 $lst$，就无法修理 $lst$，而 $a_{i+1}$ 显然大于 $a_i$，所以第 $i+1$ 个工人也无法到 $lst$，则不成立。

- 第 $i$ 个工人可以到达 $lst$，则可以选择先向左到 $lst$ 载向右走完剩下的步数，也可以先向左做再折返到达 $lst$。显然我们想要第 $i$ 个工人做完的部分尽可能地大，减轻后面的工作量。

如果能使第 $m$ 个工人做完的 $lst$ 大于 $n$，则 $mid$ 步可行。

注意答案值域为 $0$ 到 $2\times n$。

### code

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=100010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,m,a[maxn];
int l,r,mid,ans;
bool check(int x){
	int lst=1;
	for(int i=1;i<=m;i++){
		if(lst==a[i]){
			lst=a[i]+x+1;
			lst=min(lst,a[i+1]);
		}
		else{
			if(a[i]-lst>x)return false;
			lst=max(a[i]+(x-(a[i]-lst))/2+1,a[i]+x-(a[i]-lst)*2+1);
			lst=min(lst,a[i+1]);
		}
	}
	if(lst<=n)return false;
	return true;
}

int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);

	n=read();m=read();
	for(int i=1;i<=m;i++)a[i]=read();
	sort(a+1,a+m+1);
	l=0,r=n*2;a[m+1]=n+1;
	while(l<=r){
		mid=l+r>>1;
		if(check(mid)){
			r=mid-1;
			ans=mid;
		}
		else l=mid+1;
	}
	printf("%lld\n",ans);
}

```


---

