# The Corridor or There and Back Again

## 题目描述

You are in a corridor that extends infinitely to the right, divided into square rooms. You start in room $ 1 $ , proceed to room $ k $ , and then return to room $ 1 $ . You can choose the value of $ k $ . Moving to an adjacent room takes $ 1 $ second.

Additionally, there are $ n $ traps in the corridor: the $ i $ -th trap is located in room $ d_i $ and will be activated $ s_i $ seconds after you enter the room $ \boldsymbol{d_i} $ . Once a trap is activated, you cannot enter or exit a room with that trap.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1872B/4c6bb8cafdaa97d3491d04295a1aa2f558037158.png) A schematic representation of a possible corridor and your path to room $ k $ and back.Determine the maximum value of $ k $ that allows you to travel from room $ 1 $ to room $ k $ and then return to room $ 1 $ safely.

For instance, if $ n=1 $ and $ d_1=2, s_1=2 $ , you can proceed to room $ k=2 $ and return safely (the trap will activate at the moment $ 1+s_1=1+2=3 $ , it can't prevent you to return back). But if you attempt to reach room $ k=3 $ , the trap will activate at the moment $ 1+s_1=1+2=3 $ , preventing your return (you would attempt to enter room $ 2 $ on your way back at second $ 3 $ , but the activated trap would block you). Any larger value for $ k $ is also not feasible. Thus, the answer is $ k=2 $ .

## 说明/提示

The first test case is explained in the problem statement above.

In the second test case, the second trap prevents you from achieving $ k\ge6 $ . If $ k\ge6 $ , the second trap will activate at the moment $ 3+s_2=3+3=6 $ (the time you enter room $ 4 $ plus $ s_2 $ ). In the case of $ k\ge6 $ , you will return to room $ 4 $ at time $ 7 $ or later. The trap will be active at that time. It can be shown that room $ k=5 $ can be reached without encountering an active trap.

In the third test case, you can make it to room $ 299 $ and then immediately return to room $ 1 $ .

## 样例 #1

### 输入

```
7
1
2 2
3
2 8
4 3
5 2
1
200 200
4
1 20
5 9
3 179
100 1
2
10 1
1 18
2
1 1
1 2
3
1 3
1 1
1 3```

### 输出

```
2
5
299
9
9
1
1```

# 题解

## 作者：guozhe6241 (赞：5)

# 题目传送门

https://www.luogu.com.cn/problem/CF1872B

# 题意

有一个数轴,一个人现在在 $0$ 的位置，有 $n$ 个陷阱

，第 $i$ 个陷阱在 $d_i$ 的位置。过了 $s_i$ 秒后， 

这个点无法再次通行。从第 $k$ 秒开始返回，必须要回

到原点。问 $k$ 的最大值是多少。

# 思路

因为走到最大点时需要折返，而且题面要求时间严格小于 

$s_i$，所以直接向下取整是不行的，需要自增 $1$ 再除

以　$2$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int t,n;
int d[maxn],s[maxn];
int main(){
	cin>>t;
	for(int i=t;i>0;i--){
		int minn=0x3f3f3f3f;
		cin>>n;
		for(int j=1;j<=n;j++){
			cin>>d[i]>>s[i];
			minn=min(d[i]+(s[i]+1)/2,minn);
		}
		cout<<minn-1<<endl;
	}
	return 0;
}
```



---

## 作者：minVan (赞：4)

**题目大意**

一个人从原点 $0$ 向右出发，有 $n$ 个陷阱，第 $i$ 个陷阱在 $d_i$ 处，从 走出 $d_i$ 开始计时，如果过了 $s_i$ 个单位时间还没在 $d_i$ 左侧，则他将不能返回原点。

问最大的 $k$，使得他从 $0$ 到 $k$ 后能再回到 $0$。

**解题思路**

由于 $1\le d_i,s_i\le 200$，所以 $d_{i_{\max}} = 200,\{\dfrac{s_i}{2}\}_{\max}=100$，所以 $k_{\max}\le 300$。

所以 $k$ 从 $300$ 开始往下枚举，对于 $1\le i\le n$：如果 $2\times(k-d_i)$ 也就是离开 $d_i$ 到 $k$ 再回到 $d_i$ 所需要的时间大于等于 $s_i$，则不满足条件。

而第一个满足条件的 $k$ 就是 $k_{\max}$ 了。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int n, d[N], s[N];
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while(t--) {
    cin >> n;
    for(int i = 1; i <= n; i++) {
      cin >> d[i] >> s[i];
    }
    for(int k = 300; k >= 1; k--) {
      bool flag = 0;
      for(int i = 1; i <= n; i++) {
        if(2 * (k - d[i]) >= s[i]) {
          flag = 1;
          break;
        }
      }
      if(!flag) {
        cout << k << '\n';
        break;
      }
    }
  }
  return 0;
}

```

---

## 作者：wanghaoran00 (赞：4)

### 翻译

从原点由零时刻出发，有 $n$ 个陷阱，第 $i$ 个陷阱在        $d[i]$ 处，$s[i]$ 时出现，阻断回去的路，求最远距离。

### 思路

为保证有去有回，需满足在每一个陷阱落下之前已返回至陷阱前，即保留一半时间返回。在奇数情况下向下取整可满足留有剩余时间，偶数时则 $ans-1$ 即可。~~某蒟蒻在输出一堆奇奇怪怪的情况作出的奇怪方法。~~

AC code

```
#include <bits/stdc++.h>
using namespace std;
int t,n,d[105],s[105],ans;
signed main(){  
    scanf("%d",&t);   
    while(t--){
        ans=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d",&d[i],&s[i]);
        }
        for(int i=1;i<=n;i++){
            if(ans!=0){
                if(s[i]%2==0){//
                    ans=min(ans,d[i]+(s[i]/2)-1);
                }
                else{
                    ans=min(ans,d[i]+(s[i]/2));
                }
            }
            else{
                if(s[i]%2==0){
                    ans=d[i]+s[i]/2-1;  
                }
                else{
                    ans=d[i]+s[i]/2;
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：QCurium (赞：2)

[洛谷原题链接](https://www.luogu.com.cn/problem/CF1872B)

[视频讲解（顺便点个赞吧](https://www.bilibili.com/video/BV1W8411i7Ro/?vd_source=a8f2ca9bd086cb49d933fb93cb7409c0)

## 题意

你在第 $1$ 号房间，前往房间 $k$，在 $d_i$ 号房间有一个 $s_i$ 后会触发的陷阱，询问 $k$ 的最大值。

## 题目分析

我们可以把数组 $d$ 和 $s$ 存在结构体里，按 $d$ 的大小为第一关键字从小到大排序，$s$ 为第二关键字从小到大排序，每次计算到达 $d_i$ 号房间后能在走多少个房间，并更新 $k$，直到 $k$ 小于等于 $d_i$，$k$ 就是最终答案了。

有一个细节需要处理：因为必须在 $s_i$ 秒之后离开 $d_i$ 号房间，所以在计算是要用到 $s_i-1$。

## Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define base 200807
#define mod 212370440130137903
using namespace std;
const int N=105;
int t,n;
struct node{//存陷阱的结构体
	int d,s;
}a[N];
bool cmp(node x,node y){
	if(x.d!=y.d)
		return x.d<y.d;
	else
		return x.s<y.s;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		int ans=100000;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i].d>>a[i].s;
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++){
			if(a[i].d>=ans)
				break;
			if(a[i].d+(a[i].s-1)/2<=ans)
				ans=a[i].d+(a[i].s-1)/2;
		}
		if(ans==100000)
			cout<<1<<'\n';
		else
			cout<<ans<<'\n';
	}
	return 0;
}
```

[AC记录（洛谷老是UKE](https://codeforces.com/contest/1872/submission/222839373)

---

## 作者：IOI_AK_TLR (赞：1)

# 题意

有一排无限长的房间，其中部分房间有陷阱，从第一个房间开始走，走到陷阱房间后隔一段时间陷阱就会触发，触发陷阱的房间不能走，试求从一号房间最多能走多远再返回一号房间。

# 分析

此题数据量不大，可以暴力枚举通过每个陷阱房间后最多能走多远，再取最小值。由于陷阱触发的那一秒也无法通过，所以 $s_i$ 在除以二之前需要减去 $1$，最后的答案就是 $\min(d_i+(s_i-1)/{2})$。

# 实现

```cpp
#include <iostream>
#include <cstdio>
#include <climits>
using namespace std;
int t,n,d,s,ans;
int main()
{
	scanf("%d",&t);
	for(int i=1;i<=t;i++)
	{
		ans=INT_MAX;	 
		scanf("%d",&n);
		for(int j=1;j<=n;j++)
		{
			scanf("%d%d",&d,&s);
			ans=min(d+(s-1)/2,ans);	//取最小值 
		}
		printf("%d\n",ans);
	}
	return 0;
}
```


---

## 作者：Dream_poetry (赞：1)

### 题目简述：
一个人从原点 $0$ 向右行走，有 $n$ 个坑，其中第 $i$ 个坑在 $d_i$ 处，从你经过 $d_i$ 之后，如果过了 $s_i$ 之后没有回到 $d_i$ 的左侧，你将永远无法回去。

请求出最大的 $k$，使得从原点到 $k$ 还能回到原点。

### 解题思路：
我们发现：哇，数据好水，$1 \le s_i,d_i,\le 200$，那直接从一个数开始枚举一下不就行了吗？

欸，从谁开始呢？由于 $\max(d_i)=200$，$\max(\frac{s_i}{2})=100$，所以，直接从 $300$ 开始枚举即可。

从 $300$ 向下枚举，如果 $ s_i \le 2 \times (k-d_i) $，则表明无法满足条件。

第一个满足条件的即为 $\max(k)$。

#### 注意多测换行和清空！！


#### [AC记录](https://www.luogu.com.cn/record/125590659)

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
bool flag;
int d[500],s[500];
void solve(){
    cin>>n;
    for (int i=1;i<=n;i++){
    	cin>>d[i]>>s[i];
	}
    for (int k=300;k>=1;k--){
    	flag=0;
    	for(int i=1;i<=n;i++) {
        	if(2*(k - d[i]) >= s[i]) {
        		flag = 1;
        		break;
        	}
    	}
    	if(!flag){
    		cout<<k<<'\n';
			break;
    	}
    }
}



signed main(){
	int T;
	cin>>T;
	while (T--){
		solve();
	}
	return 0;
}
```


---

## 作者：tang_mx (赞：1)

很简单的一道题啊，赛时想出了最优解。看到题解区里的写法都稍微复杂一点点，我就打算来把我的想法写一下。

先分析题目，因为输入的有陷阱的房间都需要一定的触发时间，并且每一秒可以走一个房间。

由于我们需要走一个来回，因此我们在走到陷阱触发时间 $t_i$ 的一半时必须返回，否则无法回到起点。而需要返回房间中编号最小的房间号 $d_i+\left\lceil\dfrac{t_i}{2}\right\rceil$ 就是所求的 $k$ 的最大值。

代码如下
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long

using namespace std;

inline int read(){
	int x=0,y=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') y=-y;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+(c^'0');c=getchar();}
	return x*y;
}

const int N=2e5+10;

int t,n;
bool flag[N]; 

void solve(){
	n=read();
	int d,s;
	memset(flag,0,sizeof(flag));
	for(int i=1;i<=n;i++){
		d=read(),s=read();
		flag[d+(s+1)/2]=1;
	}
	for(int i=1;;i++){
		if(flag[i]){
			printf("%d\n",i-1);return;
		}
	}
}

int main(){
	t=read();
	while(t--){
		solve();
	}
	return 0;
}
```


---

## 作者：Natori (赞：1)

>[CF1872B The Corridor or There and Back Again](https://www.luogu.com.cn/problem/CF1872B)

观察第二组样例的解释，注意这句话：“第二个陷阱限制了你”。这启发我们计算经过每个陷阱之后最多还能向前走到哪里，然后取 $\min$ 得到答案。

现在的问题是如何求出每个陷阱限制的最远可到达点。

由于要求折返，因此对于第 $i$ 个陷阱，它限制的最远可到达点为 $d_i+\lfloor\dfrac{s_i}{2}\rfloor$。同时注意到要求“返回时间严格小于 $s_i$”，所以对于偶数，直接除以 $2$ 并向下取整是不行的，要先让 $s_i$ 自减 $1$。

时间复杂度 $\mathcal{O}(n)$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool Mbegin;
void File_Work(){
	freopen("test.in","r",stdin);
	freopen("test.out","w",stdout);
}
namespace Fast_In_Out{
	char buf[1<<21],*P1=buf,*P2=buf;
	#define gc (P1==P2&&(P2=(P1=buf)+fread(buf,1,1<<21,stdin),P1==P2)?EOF:*P1++)
	int read(){
		int f=1,x=0;
		char c=gc;
		while(c<'0'||c>'9'){
			if(c=='-')
			    f=-1;
			c=gc;
		}
		while(c>='0'&&c<='9'){
			x=x*10+c-'0';
			c=gc;
		}
		return f*x;
	}
	void write(int x){
		if(x<0)
			x=-x,putchar('-');
		if(x>9)
			write(x/10);
		putchar(x%10+'0');
	}
	#undef gc
}
using namespace Fast_In_Out;
const int N=108,oo=1e9+8;
int n,a[N];
void solve(){
	n=read();
	int ans=oo;
	for(int i=1;i<=n;i++){
		int d=read(),s=read();
		if(s%2==0)
			s--;
		ans=min(ans,d+s/2);
	}
	write(ans),putchar('\n'); 
}
bool Mend;
int main(){
	fprintf(stderr,"%.3lf MB\n\n\n",(&Mbegin-&Mend)/1048576.0);
	int testnum=read();
	while(testnum--)
		solve();	
	fprintf(stderr,"\n\n\n%.0lf ms",1e3*clock()/CLOCKS_PER_SEC);
	return 0;
}
```

---

## 作者：Larryyu (赞：1)

## _Description_
有若干个房间排成一行，其中有 $n$ 个房间有陷阱，对于这 $n$ 个房间，它们有两个属性：$d_i$ 和 $s_i$，分别代表标号和陷阱形成的时间，即若你第 $t$ 秒第一次到达 $i$ 号房间，$t+s_i$ 秒时陷阱就会在此房间形成，此后你无法通过此房间。每秒你可以走到与当前房间标号相邻的房间。

你需要从 1 号房间走到 $k$ 号房间，并且再从 $k$ 号房间走回 1 号房间。求 $k$ 最大是多少。
## _Solution_
对于一个有陷阱的 $i$ 号房间，我们最远可以走到 $limit_i=d_i+\lfloor(s_i)\div2\rfloor$ 号房间（减一是因为 $d_i+s_i$ 时是不能走的，要提前一秒）。

如果 $d_{i+1}>limit_i$，那就无法走到第 $d_{i+1}$ 号房间，最多只能走到 $limit_i$ 号房间。

遍历 $n$ 个有陷阱的房间，将 $d_i$ 与 $limit_1,limit_2\dots limit_{i-1}$ 比较一下就行了，对于没有陷阱的房间，它要么包含在 $limit_j$ 中，要么就走不到，所以不用考虑。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
struct node{
	int d,s;
}a[110];
int limit[110];
bool cmp(node x,node y){
	if(x.d==y.d) return x.s<y.s;
	return x.d<y.d;
}
void  solve(){
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].d>>a[i].s;
	}
	sort(a+1,a+1+n,cmp);  //需要先排序
	limit[1]=a[1].d+(a[1].s-1)/2;
	int now=limit[1];
	for(int i=2;i<=n;i++){
		bool f=0;
		for(int j=1;j<i;j++){
			if(a[i].d>limit[j]) { 
				f=1;break;
			}
		}
		if(f) break;
		limit[i]=a[i].d+(a[i].s-1)/2;
		now=min(now,limit[i]);  //可能之前的limit比当前还大，需要取最小值保证正确性
	}
	cout<<now<<endl;
}
int main(){
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：abensyl (赞：0)

原题：[CF1872B The Corridor or There and Back Again](https://www.luogu.com.cn/problem/CF1872B)。

一道贪心好题。

## 思路

当一个人到达一个含有陷阱的房间时，他就必须在一定的时间内回来，因为假如他走了太远，那么当他回来的时候，这个房间的陷阱就已经形成了，于是他便无法返回初始房间了。

那么，当一个人到达了一个房间后，他能够继续往下走多远就成了这个题主要需要攻克的问题。

显然，他继续往下走和回到这个房间来回的过程时间是一样的，由于它必须在陷阱形成前回来，所以他最多继续往下走 $\lfloor {s_i-1\over 2}\rfloor$。

那么，他到达所有房间都有一个可以到达的最远距离，最远距离中的最小值就是能够到达的最远房间距离，答案即 $\min\limits_{i=1}^n d_i+\lfloor {s_i-1\over 2}\rfloor$。

时间复杂度为 $O(n)$，可过！

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
void solve() {
	int n;
	cin>>n;
	int res=0x3fffffff;
	for(int i=1;i<=n;++i) {
		int d,s;
		cin>>d>>s;
		int tp=d+(s-1)/2;
		res=min(res,tp);
	} cout<<res<<'\n';
}
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--) {
		solve();
	}
	return 0;
}
```

[我的代码和 AC 记录。](https://codeforces.com/contest/1872/submission/225247999)

---

## 作者：FeiDing (赞：0)

## 题目大意

你在一条无限长的路上，初始坐标是 $1$。对于每一个陷阱 $i$，会在走到坐标 $d_{i}$ 后第 $s_{i}$ 秒无法进入或离开坐标 $d_{i}$。求你最远能去到并回到 $1$ 的坐标。

## 思路

（我）看到这种题一下就想到二分答案。

## 实现

我们先定义一个结构体 $trap$ 来存储所有陷阱，按他们的坐标升序排序：

```cpp
struct trap{
	int d,s;
	bool operator <(trap b) const{
		return d<b.d;
	}
}a[102];
```

对于二分中 $l$ 和 $r$ 的设置，有以下两点：

- 题目中 $1 \le d_{i},s_{i} \le 200$，那么很明显我们不可能走到坐标 $1000$ 还安全回来。
- 初始坐标是 $1$，那我们即使不动答案也是 $1$ 。

所以设置 $l \gets 1,r \gets 1000$。

对于 $check$ 函数，很明显我们可以越过陷阱 $i$ 最多 $(s_{i}-1)\div2$ 格（除以二是因为要留一半时间回来），所以 $check$ 函数是这样的：


```cpp
bool check(int k){
	for(int i=1;i<=n&&a[i].d<=k;++i){
		if(a[i].d+(a[i].s-1)/2<k)
			return 0;
	}
	return 1;
}
```

完整代码：

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
struct trap{
	int d,s;
	bool operator <(trap b) const{
		return d<b.d;
	}
}a[102];
int t,n,l,r;
bool check(int);
int main(){
	scanf("%d",&t);
	while(t--){
		for(int i=0;i<102;++i){
			a[i]={0,0};
		}//多组数据初始化
		r=1000,l=1;
		scanf("%d",&n);
		for(int i=1;i<=n;++i){
			scanf("%d%d",&a[i].d,&a[i].s);
		}
		sort(a+1,a+n+1);
		while(r-l>1){//标准二分
			int mid=(l+r)/2;
			if(check(mid)){
				l=mid;
			}else{
				r=mid;
			}
		}
		printf("%d\n",l);
	}
}
bool check(int k){
	for(int i=1;i<=n&&a[i].d<=k;++i){
		if(a[i].d+(a[i].s-1)/2<k)
			return 0;
	}
	return 1;
}
```


---

## 作者：Daniel_yao (赞：0)

## Problem
有无限个房间，并且向右延伸。你现在需要从 $1$ 号房间走到 $k$ 号房间，并从 $k$ 号房间回来。每向右走 $1$ 单位需要耗费 $1$ 单位的时间。这些房间里有些会有陷阱。共 $n$ 个陷阱，每一个陷阱都有一个所在位置 $d_i$ 和激活时间 $s_i$，当你进入有陷阱的房间时，会激活陷阱，陷阱将在 $s_i$ 秒后触发。陷阱触发后，你不能再次进入此房间或者从此房间出去。

求最远能到达的 $k$ 号房间。
## Solve
此题花费了我一点点的时间。

首先必须有去有回。当一个陷阱被出发后，你必须在某个点折返回来，并且要保证不能受陷阱影响。对于所有的陷阱，都是如此。每个陷阱都会有一个最大的，能到达并且能返回的点，将其记为 $g_i$，答案为 $\min\limits_{1\le i\le n} g_i$。

考虑如何计算 $g_i$，我们将去的路和回的路拉成一条直线，这条直线的中点即为 $g_i=\frac{(d_i+(s_i-1))}{2}$。
## Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define H 19260817
#define rint register int
#define For(i,l,r) for(rint i=l;i<=r;++i)
#define FOR(i,r,l) for(rint i=r;i>=l;--i)
#define MOD 1000003
#define mod 1000000007
#define inf 1e9

using namespace std;

namespace Read {
  template <typename T>
  inline void read(T &x) {
    x=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x*=f;
  }
  template <typename T, typename... Args>
  inline void read(T &t, Args&... args) {
    read(t), read(args...);
  }
}

using namespace Read;

void print(int x){
  if(x<0){putchar('-');x=-x;}
  if(x>9){print(x/10);putchar(x%10+'0');}
  else putchar(x+'0');
  return;
}

int T, n, d, s, k; 

void solve() {
  read(n);
  k = inf;
  For(i,1,n) {
  read(d, s);
    k = min(k, d + (s - 1) / 2);
  }
  cout << k << '\n';
}

signed main() {
  read(T);
  while(T--) {
    solve();
  }
  return 0;
}
```

---

## 作者：One_JuRuo (赞：0)

## 思路

假设第 $0$ 时刻走进有陷阱的房间，那么必须在第 $t_i$ 时刻前返回到这个房间之前，因为出去还需要回来，假设到达这个房间后的第 $k$ 个房间，那么到达需要 $k$ 的时间，回来需要 $k+1$ 的时间，因为陷阱会困住当前在房间里的人，所以我们需要提前回去。

那么如果走到一个有陷阱的房间，假设房间在 $a$，陷阱时间是 $t$，那么这个陷阱就会把答案缩减到 $a+\lfloor \frac {k-1} 2 \rfloor$。

那么我们就直接遍历一遍，不断更新最远的答案，直到遍历到最远的答案为止。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,t[1005],a,b,maxn;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n),memset(t,0,sizeof(t)),maxn=1000;
		for(int i=1;i<=n;++i) scanf("%d%d",&a,&b),t[a]=(!t[a])?b:min(t[a],b);
		for(int i=1;i<=1000;++i)
		{
			if(i>=maxn) break;
			if(t[i]) maxn=min(maxn,i+(t[i]-1)/2);
		}
		printf("%d\n",maxn);
	}
} 
```

---

