# Let's Go Hiking

## 题目描述

On a weekend, Qingshan suggests that she and her friend Daniel go hiking. Unfortunately, they are busy high school students, so they can only go hiking on scratch paper.

A permutation $ p $ is written from left to right on the paper. First Qingshan chooses an integer index $ x $ ( $ 1\le x\le n $ ) and tells it to Daniel. After that, Daniel chooses another integer index $ y $ ( $ 1\le y\le n $ , $ y \ne x $ ).

The game progresses turn by turn and as usual, Qingshan moves first. The rules follow:

- If it is Qingshan's turn, Qingshan must change $ x $ to such an index $ x' $ that $ 1\le x'\le n $ , $ |x'-x|=1 $ , $ x'\ne y $ , and $ p_{x'}<p_x $ at the same time.
- If it is Daniel's turn, Daniel must change $ y $ to such an index $ y' $ that $ 1\le y'\le n $ , $ |y'-y|=1 $ , $ y'\ne x $ , and $ p_{y'}>p_y $ at the same time.

The person who can't make her or his move loses, and the other wins. You, as Qingshan's fan, are asked to calculate the number of possible $ x $ to make Qingshan win in the case both players play optimally.

## 说明/提示

In the first test case, Qingshan can only choose $ x=3 $ to win, so the answer is $ 1 $ .

In the second test case, if Qingshan will choose $ x=4 $ , Daniel can choose $ y=1 $ . In the first turn (Qingshan's) Qingshan chooses $ x'=3 $ and changes $ x $ to $ 3 $ . In the second turn (Daniel's) Daniel chooses $ y'=2 $ and changes $ y $ to $ 2 $ . Qingshan can't choose $ x'=2 $ because $ y=2 $ at this time. Then Qingshan loses.

## 样例 #1

### 输入

```
5
1 2 5 4 3```

### 输出

```
1```

## 样例 #2

### 输入

```
7
1 2 4 6 5 3 7```

### 输出

```
0```

# 题解

## 作者：miao5 (赞：10)

**题目大意：**

有两个人，他们在一张高度不一的图像吗行走， Q 只能向下走， D 只能向上走，不能走到别的人身上,求 Q 有多少中可以赢的位置。

**大体思路：**

这道题目就是分情况讨论，
我们先考虑 Q 怎么会输：

一种是这样：D 把 Q 的路堵住了

![](https://cdn.luogu.com.cn/upload/image_hosting/otl2fc1e.png)

这时该 Q 走，我们可以发现他无路可走了，因为再下一格就是    D。 
我们可以发现这种情况只会发生在这个坡是偶数长度的情况下。

一种是这样：Q 走到尽头了，但是 D 还能走：

![](https://cdn.luogu.com.cn/upload/image_hosting/wa80cbsg.png)

这样 Q 就走不了了，
这种情况只会发生在两边边长不一的情况下。

我们再考虑 Q 会赢的情况：

一种是 Q 把 D 堵住了：
![](https://cdn.luogu.com.cn/upload/image_hosting/b0elc0za.png)

这时是 D 走，但他走不了了，所以他输了。
这时坡长是奇数。

那么这时 D 有办法吗？ 当然有！



![](https://cdn.luogu.com.cn/upload/image_hosting/ftxvzm7c.png)

D 往上选一格，照样能堵住 Q。

那怎么办呢？
我们考虑其他的情况。


![](https://cdn.luogu.com.cn/upload/image_hosting/r5j14br9.png)

如果两边是一样长的，那么 Q 就往另一边走，D 走到顶上，Q 还没到底。

这貌似是一组正解，但考虑如果旁边有更长的坡：

![](https://cdn.luogu.com.cn/upload/image_hosting/5ls8dspe.png)

这样 Q 到头了 D 还没有，如果 Q 选在红线上，D 照样堵他，妥妥的。

那怎么办呢？

考虑这种情况，两条最长的坡连在一起了：

![](https://cdn.luogu.com.cn/upload/image_hosting/5rby27ri.png)


这样也有两种情况：

首先考虑坡是偶数，这样 Q 不能往 D 的方向走，否则 D 会把他堵住。如果 Q 往另一边走，他会比 D 先到，所以这样也是输。

如果坡是奇数呢？

这样 Q 也不能往没有 D 的方向走，要不然他又会输。

如果 Q 往 D 的方向走呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/y7z93spd.png)

那么这样 Q 把 D 堵住了，Q 就赢了。

那么 D 有办法吗？
D 可不可以在往上一格？

尝试一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/jbauw1b9.png)

这样 D 到头了 Q 还没有。
还是 Q 赢。

这时他能赢的唯一情况，总结一下：有且只有两条最长的边，刚好连在一起，长度又恰好是奇数。

这题就做完了。

**code：**

```cpp
#include<iostream>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=100010;
int n,a[maxn],len_up,len_down;
int dp1[maxn],dp2[maxn],len_max;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]>a[i-1]) dp1[i]=dp1[i-1]+1;
		else dp1[i]=1;
		if(a[i]<a[i-1]) dp2[i]=dp2[i-1]+1;
		else dp2[i]=1;//记录坡的连续长度 
		len_up=max(len_up,dp1[i]);
		len_down=max(len_up,dp2[i]);//记录最长的坡 
	}
	len_max=max(len_up,len_down);//最最长的坡 
	bool f_up=false,f_down=false;
	int p_up,p_down;
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(dp1[i]==len_max){
			f_up=true;
			cnt++;
			p_up=i;
		}
		if(dp2[i]==len_max){
			f_down=true;
			cnt++;
			p_down=i;
		} //记录最长的上坡和最长的下坡的位置 
	}
	if(f_up&&f_down&&cnt==2&&p_up==p_down-len_max+1&&len_max%2) cout<<1<<endl; 
	else cout<<0<<endl;	
	//判断，输出答案。 
	return 0;
}

```


---

## 作者：oisdoaiu (赞：5)

一个简单粗暴的思路，枚举每一个初始位置，然后判断可行性。

首先如果先手只能往一个方向走，那么后手直接堵旁边就赢了，所以只考虑先手两边都可以走的情况。

那么对于后手来说，他有两种选择：

- 和先手比长度

- 堵路

设先手能走到的范围为 $[l,r]$。

对于第一种情况，相当于二者互不干扰，则初始位置 $i\in[1,l)$ 或 $(r,n]$，或者从 $l$ 往左走，从 $r$ 往右走。

而堵路就两种情况，$l$ 往右走和 $r$ 往左走，显然后手会走长的那一条。

至于先手/后手往左/右能走多远，可以先扫一遍预处理 $O(n)$。

```cpp
for(register int i=1, lst=1; i<=n; i++)    
    if(a[i]>a[i+1] or i==n){
        for(register int j=lst; j<=i; j++) up[1][j] = i, down[0][j] = lst;
        lst = i+1;
    }
for(register int i=n, lst=n; i; i--)
    if(a[i]>a[i-1] or i==1){
        for(register int j=lst; j>=i; j--) up[0][j] = i, down[1][j] = lst;
        lst = i-1;
    }
```

后手在前缀/后缀中能走的最远长度也可以扫一遍预处理 $O(n)$。

```cpp
for(register int i=1; i<=n; i++) pre[i] = max(pre[i-1],max(i-up[0][i]+1,up[1][i]-i+1));
for(register int i=n; i>=1; i--) suf[i] = max(suf[i+1],max(i-up[0][i]+1,up[1][i]-i+1));
```

然后枚举一下先手的初始位置 $O(1)$判断，也是 $O(n)$。

```cpp
for(register int i=1; i<=n; i++) if(down[0][i]!=i and down[1][i]!=i){
    int len1 = i-down[0][i]+1, len2 = down[1][i]-i+1;
    int l = down[0][i], r = down[1][i];
    if(max(max(pre[l-1],l-up[0][l]+1),max(suf[r+1],up[1][r]-r+1))>=max(len1,len2)) continue;
    if(((len1>>1)<<1)>=len2) continue;
    if(((len2>>1)<<1)>=len1) continue;
    ans++;
}
```

**注意**一个小细节，如果要堵路，那么要保证两者间的距离为偶数，如果为奇数的话先手就能反杀。(模拟一下不难发现)

---

## 作者：fuxuantong123 (赞：3)

# CF1495B Let's Go Hiking 题解
## 题意
这还用说？
## 思路
首先，答案一定是 $0$ 或 $1$，假设有两个必胜的位置，则先手选择一个时，后手可选择另一个对应的最低点，就没有必胜位置了。

然后分类讨论。

显然，先手一定会在一个“山峰”上（两个单调子序列的最高点拼在一起）。

如果两“山坡”的长度不同，那么后手可以在长边上堵住先手，强迫他走短边，先手最后因为先手（第一个先手是名词，第二个是形容词）而无路可走，失败。

如果两“山坡”长度相同且都是奇数，那么后手可以选在一边坡底，先手只能走另一边，最后仍然无路可走，失败。

如果两“山坡”长度相同且都是偶数，那么后手无论选在哪一边坡底，都会被先手堵死，如果往上一格再堵，先手就可以走另一边，后手最后无路可走，先手胜。
## 总结
如果有两个最长单调子序列，有一个公共点且为坡顶（数值最大点）， 且最长单调子序列长度为偶数，则公共点为唯一先手必胜的位置。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[100010];
int s[100010];
int j[100010];
int main(){
	int n;
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=2;i<=n;i++){
		if(a[i]>a[i-1]){
			s[i]=s[i-1]+1;
		}
	}
	for(int i=n-1;i>=1;i--){
		if(a[i]>a[i+1]){
			j[i]=j[i+1]+1;
		}
	}
	int mxs=0;
	int mxj=0;
	for(int i=1;i<=n;i++){
		mxs=max(mxs,s[i]);
		mxj=max(mxj,j[i]);
	}
	int cnt=0;
	for(int i=1;i<=n;i++){
		if(mxs==mxj && s[i]==mxs){
			cnt++;
		}
		if(mxs==mxj && j[i]==mxs){
			cnt++;
		}
	}
	if(cnt>=3){
		printf("0");
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(s[i]==j[i] && s[i]%2==0 && s[i]==mxs && j[i]==mxj && s[i]!=0){
			printf("1");
			return 0;
		}
	}
	printf("0");
return 0;
}
```

---

## 作者：Schwarzkopf_Henkal (赞：3)

这题细节巨多无比……

首先稍微思考一下，显然放的位置一定是峰顶，考虑如果放在坡上，`D` 一定有办法堵，或者甚至都不用堵 `Q` 就会输。

再考虑，如果峰顶两边坡的长度是不相等的，那么 `D` 放在更长的坡上总是能胜利。

再再考虑，如果坡的长度（峰谷坐标差）不是偶数，那么 `D` 总是能堵死，或者一直向上爬直到 `Q` 挂掉。

再再再考虑，如果这些条件都满足但是这个峰的峰坡长度不是严格最长的，那么 `D` 能够比长度比过 `Q` 。也就是说答案要么是 $1$，要么是 $0$。

再再再再考虑，如果这些条件再都满足，考虑 `Q` 一定往 `D` 所在的谷走，但 `D` 却不一定要往 `Q` 所在的峰走，如果另一边的坡长不能保证小于这边的坡长，会挂。（理论上这个永远不会成立？但是我去掉就 WA 了，不知道为什么）

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100005],ans,mx,mxc,pre[100005],suf[100005];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    for(int i=n-1;i>=1;i--){
        if(a[i]<a[i+1])
            suf[i]=suf[i+1]+1;
        else suf[i]=0;
    }
    for(int i=2;i<=n;i++){
        if(a[i]<a[i-1])
            pre[i]=pre[i-1]+1;
        else pre[i]=0;
    }
    for(int i=2;i<n;i++)
        if(a[i]>a[i-1]&&a[i]>a[i+1]){
            int u=i,v=i;
            while(u-1>=1&&a[u-1]<a[u])
                u--;
            while(v+1<=n&&a[v+1]<a[v])
                v++;
            if(max(i-u,v-i)>mx){
                mx=max(i-u,v-i);
                mxc=1;
            }else if(max(i-u,v-i)==mx)
                mxc++;
        }
    for(int i=2;i<n;i++)
        if(a[i]>a[i-1]&&a[i]>a[i+1]){
            int u=i,v=i;
            while(u-1>=1&&a[u-1]<a[u])
                u--;
            while(v+1<=n&&a[v+1]<a[v])
                v++;
            if(i-u==v-i&&(i-u)%2==0&&mxc==1&&i-u>=mx)
                ans=1;
        }
    cout<<ans;
}/*
首先明确，x0必定是在峰顶上的，
并且两边到谷底的距离要一样长，并且长度必须是偶数（峰谷坐标差）
并且，这段长度还必须是最长的……
也就是说，答案只有可能是0或1.
细节巨多……
*/
```



---

## 作者：vеctorwyx (赞：3)

### 题目大意：

给你一个序列，先手可以向相邻的比自己小的数移动，后手可以向相邻的比自己大的数移动，初始位置自由选择，先手先选。

求先手必胜的初始位置有几个。

### sol：

比较好得到一个结论：先手必胜的位置只能有一个或没有。

证明：

假设有两个必胜的位置，则先手选择其中一个时，后手可选择另一个对应的最低点，则没有必胜位置， 证必。

所以可以首先找到全部最长单调子序列：

- 如果出现三个及更多最长单调子序列，则先手必败；

- 如果有两个最长单调子序列，有一个公共点且为数值最大点， 且最长单调子序列长度为奇数， 则公共点为唯一先手必胜的位置；

- 其他情况先手均必败。

然后即可得出答案。

code：
```
#include "iostream"
#include "cstdio"
#include "cstring"
#include "cstdlib"
#include "algorithm"
#include "queue"
#include "cmath"
#include "vector"
#include "map"
#include "time.h"
#define int long long
using namespace std;
int read()
{
	int xsef = 0,yagx = 1;char cejt = getchar();
	while(cejt < '0'||cejt > '9'){if(cejt == '-')yagx = -1;cejt = getchar();}
	while(cejt >= '0'&&cejt <= '9'){xsef = (xsef << 1) + (xsef << 3) + cejt - '0';cejt = getchar();}
	return xsef * yagx;
}
void write(int x){
	if(x > 9)
		write(x / 10);
	putchar(x % 10 + '0');
}
int n;
int a[200010], st[200010], top, fr, dis[200010][2], st2[200010], top2;
signed main(){
	n = read();
	if(n == 2){
		puts("0");
		return 0 ;
	}
	for(int i = 1; i <= n; i++)
		a[i] = read();
	st[++top] = 1;
	for(int i = 2; i < n; i++){//寻找山峰（山谷）
		if(a[i] > a[i - 1] && a[i] > a[i + 1])
			st[++top] = i;
		if(a[i] < a[i - 1] && a[i] < a[i + 1])
			st[++top] = i;
	}
	st[++top] = n;
	int maxx = 0;
	if(a[st[2]] > a[st[2] - 1] && a[st[2]] > a[st[2] + 1])//第一个山峰的位置
		fr = 2;
	else
		fr = 1;
	for(int i = fr; i <= top; i += 2){
		int x = 0, y = 0;
		if(st[i - 1] == 0)
			x = 0;
		else
			x = st[i] - st[i - 1];
		if(i + 1 > top)
			y = 0;
		else
			y = st[i + 1] - st[i];
            	//记录每个单调子序列的长度
		dis[i][0] = min(x, y);
		dis[i][1] = max(x, y);
        	//记录最长单调子序列的个数
		if(maxx < max(x, y)){
			top2 = 1;
			st2[top2] = i;
			maxx = max(x, y);
		}
		else if(maxx == max(x, y))
			st2[++top2] = i;
	}
	int ans = 0;
	if(top2 == 1){
		if(dis[st2[top2]][1] % 2 == 0 && dis[st2[top2]][0] == dis[st2[top2]][1])
			ans = 1;
	}
	write(ans), putchar('\n');
	return 0;
}
```

~~赛时因为读错题而调了一个小时的屑~~

---

## 作者：Cry_For_theMoon (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1495B)

赛场被2c卡了1h然后没时间想这题，结果本以为直接CM却再次掉出1800（悲）

给一个比较容易想到的思路（我现在不知道直接上全局最大段的神仙思路是怎么找到的）

$p$ 是排列在这题的唯一用处就是告诉我们没有相同元素

首先，$x=1$ 或 $n$ 时，必败，所以以下只考虑 $x=[2,n-1]$ 的情况。

如果 $x$ 位于一个递增/递减子段的中部，即满足 $p[x-1]<p[x]<p[x+1]$ 或 $p[x-1]>p[x]>p[x+1]$，这两种情况下，令 $y$ 取 $x-1$ 或 $x+1$，即 $x$ 唯一能走的那个方向，就堵住了 $x$，必败。

所以我们得到结论：$x$ 的可取值一定是在山峰/山谷上（即一个递增/递减子序列的开头/结尾的）

那么分两种情况讨论：

- $x$ 的两边全部都是上升子段，即 $p[x-1]>p[x]$ 且 $p[x+1]>p[x]$

此时不管 $y$ 怎么选，$x$ 本身都没有可走的下一个位置，必败

- $x$ 的两边全部都是下降子段，即 $p[x-1]<p[x]$ 且 $p[x+1]<p[x]$

参考下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/b4w3o1o3.png)

然后我们讨论 $y$ 的取值：

1.$y$ 所在的链不是与 $x$ 相交的这两条链（链指一个极大的上升/下降子段）

此时 $y$ 与 $x$ 不会冲突，会各自走完所选择的那条链。所以我们找到 $[1,L]+[R,n]$ 中的最长链作为 $y$ 选择的链，这个东西可以用前缀和/后缀和预处理出来。然后 $x$ 选择 $\max\{len1,len2\}$ 作为所选择的链。因为 $x$ 要多走一步，所以当 $x$ 所选的链长**严格大于**$y$ 所选的链长时，$x$ 不会输。

2.$y$ 就在 $[L,R]$ 之间取的时候

注意到这个时候 $x$ 有两个方向可以走。先考虑两条链相等，即 $len1=len2$.此时 $y$ 若不取 $L$ 或 $R$，则 $x$ 不往 $y$ 所在链走，$y$ 一定会负。而当 $y$ 取 $L$ 或 $R$ 时，$x$ 一定会往 $y$ 所在链走（否则因为$x,y$ 所选链登场 $x$ 会负），此时讨论 $L$ 的奇偶性就可以知道谁会赢。

若两条链不等，不妨设 $len1>len2$，那么 $y$ 一定会选在左边这条链上。此时 $x$ 也一定会往 $y$ 所在链走，$y$ 要么选 $L$，要么选 $L+1$，总有一种情况下，$y$ 拼奇偶是赢的（能选 $L+1$ 是因为 $len1>len2$，选 $L+1$ 的话两条链就是大于等于，变成上面那种情况），所以此时 $x$ 必败。

此时我们已经可以做了，预处理出四个（向前向后的上升/下降）子段，统计前缀/后缀和，枚举 $x=[2,n]$ 再 $O(1)$ 判断即可。

但是别忘了官方题解的那个找全局最大的 nb 做法，我们能否通过这个做法推导出那个。

根据第一部分“$y$ 所在链不是与 $x$ 相交的这两条链”部分，我们可以推出，若 $x$ 像不败，它所在两条链必须有至少一条是全局最大的。

此时根据第二部分中“若两条链不等”我们可以推出 $x$ 的这两条链都是全局最大的。

所以当且仅当有两条相交的全局最大链时可能有 $1$ 个解，此时讨论最大链长度即可，即官方题解的思路。

（官方题解做法我就不放了，放一下本篇思路的做法）

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(ll i=(a);i<=(b);i++)
#define per(i,a,b) for(ll i=(a);i>=(b);i--)
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=1e5+10;
int n,p[MAXN],f[4][MAXN],ans;
int pre[MAXN],suf[MAXN];
int main(){
	scanf("%d",&n);
	rep(i,1,n){
		scanf("%d",&p[i]);
		if(p[i-1]<p[i]){
			f[0][i]=f[0][i-1]+1;
			f[1][i]=1;
		}else{
			f[0][i]=1;
			f[1][i]=f[1][i-1]+1;
		}
		pre[i]=pre[i-1];
		pre[i]=Max(pre[i],f[0][i]);
		pre[i]=Max(pre[i],f[1][i]);
	}
	per(i,n,1){
		if(p[i+1]<p[i]){
			f[2][i]=f[2][i+1]+1;
			f[3][i]=1;
		}else{
			f[2][i]=1;
			f[3][i]=f[3][i+1]+1;
		}
		suf[i]=suf[i+1];
		suf[i]=Max(suf[i],f[2][i]);
		suf[i]=Max(suf[i],f[3][i]);
	}
	rep(i,2,n-1){
		if(p[i-1]<p[i] && p[i+1]<p[i]){
			//f[0]和f[2]两边延伸 
			int L=i-f[0][i]+1,R=i+f[2][i]-1;
			int Maxn=Max(pre[L],suf[R]);
			if(Maxn>=Max(f[0][i],f[2][i]))continue; 
			if(f[0][i]==f[2][i] && f[0][i]&1)ans++;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：_Anchor (赞：1)

## Problem

[CF1495B Let's Go Hiking（博弈+DP）](https://www.luogu.com.cn/problem/CF1495B)

## Solution

第一步，我们分析得出每个人不能走回头路，证明显然。

首先，我们发现一个人可以走的更远，当且仅当这是一个连续单调 上升/下降 的序列。

我们可以用 dp 来求出以每个点结尾的最长连续 上升/下降 的序列。

那么其实在我们选定最初 $x$ 的位置时，他能走的路线就已经确定了，也就是只能朝着单调下降的一段不停地往前走，直到单调区间的尽头。


而这个时候 $y$ 的应对也很容易。

首先我们发现，既然答案跟单调区间长度有关，那么我们就直接求出最长的单调 上升/下降 区间即可。

顺便记一下最大值的个数，因为如果有超过 2 个这样的区间，那么对于 $x$ 而言是必败。

（至于为什么是 2 个不是 1 个：因为如果超过 1 个，但是两个区间首尾相接并且正好相反，也就是呈现 '^' 形状，这个需要单独讨论，x 并不是必败。）

为什么呢？因为 $x$ 无论选择哪个最长单调区间，$y$ 都可以选择另外一个区间，其长度和 $x$ 的长度一样，并且这样的话 $x$ 接下来只能走 $len-1$ 步，而 $y$ 相对于 $x$ 要多一步。（因为 $x$ 先手）

那么现在再讨论刚好有一个的情况：

这样的情况其实很简单，$x$ 随便选哪个点， $y$ 直接选 $x$ 下端的那一个点，此时该 $x$ 走，但他被 $y$ 挡住了，直接就输了。

最后是刚好两个这样的区间，且首尾相接，且呈现 '^' 状的情况。

$x$ 此时选择 '^' 的顶点， $y$ 堵哪一边都不行,因为 $x$ 直接反方向走即可，但是我们考虑 $x$ 反方向走行吗？

比如此时我的 $y$ 放在左下角，$x$ 如果走另一边，显然这是和之前那个 “两个以上区间” 的情况一样，$x$ 因为先手会死掉。

（但是，这也是 $y$ 最大的限制，那就是此时 $y$ 只能放在两端的末尾，不能放在山坡上的任何中间一个位置，因为这样的话 $x$ 走另一边就比 $y$ 长了。）

那么此时 $x$ 只能走 $y$ 的同侧，且 $y$ 只能放在一段末尾，那在这个时候，$x,y$ 的行动轨迹完全确定了，我们只需要考虑最后模拟出来的胜者是谁即可。

模拟几下会知道：$x$ 会胜当且仅当这个山坡长度是奇数时。（此时 $x$ 在最后会走到中点 mid ，而 $y$ 会走到 mid-1 ，此时该 $y$ 走，但是他被 $x$ 挡住了，$y$ 动不了了，所以 $x$ 胜。）

## Code

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
template <typename T>
inline void read(T &x){
	x=0;char ch=getchar();bool f=false;
	while(!isdigit(ch)){if(ch=='-'){f=true;}ch=getchar();}
	while(isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	x=f?-x:x;
	return ;
}
template <typename T>
inline void write(T x){
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10^48);
	return ;
}
const int N=1e5+5;
int T,n,m,tot;
int a[N],dp[N],Maxn,Maxn1,Max,dp1[N];
int main(){
	T=1;
	while(T--){
		read(n);tot=Max=Maxn=Maxn1=0;
		for(int i=1;i<=n;i++){
			read(a[i]);
			if(a[i]>a[i-1]) dp[i]=dp[i-1]+1;
			else dp[i]=1;
			if(a[i]<a[i-1]) dp1[i]=dp1[i-1]+1;
			else dp1[i]=1;
			Maxn=max(Maxn,dp[i]);
			Maxn1=max(Maxn1,dp1[i]);
		}
		Max=max(Maxn,Maxn1);
		bool flag=false,flag1=false;
		int pos1,pos;
		for(int i=1;i<=n;i++){
			if(dp[i]==Max) tot++,flag=true,pos=i;
			if(dp1[i]==Max) tot++,flag1=true,pos1=i;
		}
		if(tot==2&&flag&&flag1&&pos==pos1-Max+1&&(Max&1)) puts("1");
		else puts("0");
	}
	return 0;
}
```

---

## 作者：vectorwyx (赞：1)

我们把整个序列 $p$ 看做山地，$p_{i}$ 为第 $i$ 个位置的高度。定义山峰、山谷、山坡、坡长如下：

* 山峰：高度比相邻两个位置都高的位置($p_{i}>\max(p_{i-1},p_{i+1})$)
* 山谷：高度比相邻两个位置都低的位置($p_{i}<\min(p_{i-1},p_{i+1})$)
* 山坡：既不是山峰也不是山谷的位置
* 坡长：一个山峰到左面最近的山谷之间的山坡的数量称为这个山峰的左坡长，到右面最近的山谷之间的山坡的数量称为右坡长。一个山峰的坡长为其左坡长和右坡长的最大值。

那么题目中的游戏就是 A 先选一个位置，B 再选一个位置，A 只能向低处走，B 只能向高处走。规定不能和别人待在同一个位置，当一个人无路可走时另一个人就输了。A 先走，问 A 有多少个可选的位置是必胜的。

首先，A 要想获胜只能选在山峰处。因为如果他选在了山坡处，那么他的第一步就只能走向唯一确定的一个位置：左面，或右面，这种情况下 B 只需要把位置选在 A 第一步将要去的位置，就可以把 A 堵死。如果他选在山谷处，那么第一步他就已经无路可走了。

其次，A 所选的山峰的坡长必须是所有山峰的坡长中**严格最大**的那个。如果其坡长不是最大的，那么 B 只需要把位置选在坡长最大的那个山峰对应的山谷处，A 一定比 B 先走完他的路程；如果其坡长是最大的但不严格，也就是说有多个山峰的坡长是最大值，那么 B 也只需要把位置选在另一个坡长为最大值的山峰对应的山谷处，由于 A 先走，A 必定先于 B 走投无路。

同时，A 所选的山峰的左坡长和右坡长必须相等且均为奇数。如果左右坡长不相等，那么 B 只需要选在坡长较长的那一边的山谷或山谷向上一步处就可以逼迫 A 往坡长较短的那一边走（如果 A 向 B 这边走来，B 总能把 A 的出路堵死），由于 A 先走，又转化成了上一种情况。而如果左右坡长相等但均为偶数，那么 B 只需要选在任意一边的山谷处，A 只能往另一边走。由于 A 先走，所以 A 先无路可走。

综上，只有当序列 $p$ 中存在坡长为严格最大的山峰且这个山峰的左右坡长为相同的奇数时答案为 $1$，其余情况答案为 $0$。

代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=1e5+5;
int a[N],b[N],top=1,c[N],d[N];

int main(){
	int n=read();
	fo(i,1,n) a[i]=read();
	b[1]=1;
	if(a[1]>a[2]||a[1]<a[2]) b[++top]=1,c[top]=(a[1]>a[2]);
	fo(i,2,n-1)
		if((a[i-1]<a[i]&&a[i+1]<a[i])||(a[i-1]>a[i]&&a[i+1]>a[i])) 
			b[++top]=i,c[top]=(a[i-1]<a[i]&&a[i+1]<a[i]);
	if(a[n]>a[n-1]||a[n]<a[n-1]) b[++top]=n,c[top]=(a[n-1]<a[n]);
	b[++top]=n;
	int mx=0,rp=0,pos=-1;
	fo(i,2,top-1) d[i]=max(b[i]-b[i-1],b[i+1]-b[i]);
	fo(i,2,top-1) if(c[i]) mx=max(mx,d[i]);
	fo(i,2,top-1) if(c[i]&&mx==d[i]) rp++,pos=i;
	//fo(i,1,top) printf("%d ",b[i]);puts("");
//	fo(i,1,top) printf("%d ",c[i]);puts(""); 
	//fo(i,1,top) printf("%d ",d[i]);puts("");
	if(rp>1){
		cout<<0;
		return 0;
	}
	if(b[pos]-b[pos-1]!=b[pos+1]-b[pos]){
		cout<<0;
		return 0; 
	}
	if(d[pos]&1) cout<<0;
	else cout<<1;
	return 0;
}
```


---

## 作者：_Only_this (赞：0)

### CF1495B Let's Go Hiking 题解

------------

emm，没什么好说的，一眼分讨。

------------

考虑几种情况。

对于每个坡，Q 必然不能位于坡中央任意一点，因为 D 必然会在下一个位置堵掉。

而且显然，Q 也不可能在坡底，因为下一步就没位置走了。

那么 Q 只能在坡顶了。

容易发现，位于坡顶，会有两个向下的选择。

如果两个向下的选择的长度不同，下一步 D 必然会堵掉那个长的，这样 Q 就会被耗死。

所以只有在两个长度相同时，才有可能 Q 赢。

但当坡长都为奇数时，D 会选择任意一边的坡底。Q 往 D 的方向走会被堵死，往另一个方向走会被耗死，因此在这种情况下 Q 必输。

最后只剩下一种可能了，那就是坡长均为偶数。这种情况下，如果 D 想堵 Q，会被耗死，如果 D 想拼长度，会被 Q 堵死，因此这种情况下 Q 必胜。

但在上述讨论中是默认了相邻两个坡都是最长的坡，如果还有更长的坡，还要讨论。

但容易发现，如果相邻两个坡不是最长的，那么 Q 也不可能赢，人家 D 会选择一条更长的坡，把 Q 耗死。

因此总结一下：如果相邻两个坡长均为偶数，且均为最大值，且最大值有且仅有两个，那么 Q 才能赢。

贴个代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int inf = 0x3f3f3f3f;
int n,ans;
int a[maxn];
inline void Solve(){
	int tot=0,maxx=-inf,cnt=0;
	
	for(int i=1;i<=n;i++){
		if(a[i]>a[i-1]){
			tot++;
		}
		else{
			tot=1;
		}
		if(tot>maxx){
			cnt=1,maxx=tot;
		}
		else{
			if(tot==maxx){
				cnt++;
			}
		}
	}
	
	tot=0,a[0]=inf;
	
	for(int i=1;i<=n;i++){
		if(a[i]<a[i-1]){
			tot++;
		}
		else{
			tot=1;
		}
		if(tot>maxx){
			cnt=1,maxx=tot;
		}
		else{
			if(tot==maxx){
				cnt++;
			}
		}
	}
	
	a[0]=0;
	
	int now=2,lst,len1,len2;
	
	for(;now<n;){
		lst=now-1;
		for(;a[now]>a[now-1] &&  now<=n;now++);
		len1=now-lst;
		lst=now;
		for(;a[now]<a[now-1] && now<=n;now++);
		len2=now-lst+1;
		if(cnt==2 && len1==maxx && len2==maxx && (len1&1)){
			printf("%d\n",1);
			return ;
		}
	}
	
	printf("%d\n",0);
	
	return ;
}
int main(){
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	
	Solve();
	return 0;
}
```

完结散花。

---

## 作者：Hooch (赞：0)

这道题我们读了题之后发现想要 `Q` 获胜，有且仅有以下这种情况：

+ `Q` 选择的山一定两边都能走。

如果只能走一边，那么 `D` 只要在 `Q` 旁边就必输。

+ `Q` 最长的那边能走的长度一定为偶数。

如果是奇数，若他们相向而行，则他们两人走在中间时必定 `Q` 输； 若逆向而行，则另一边比这边短，依然是 `Q` 输。

+ 此时 `Q` 选择的路一定是所有山当中最长的下降子序列。

不然，`D` 就直接选择最长的那一条，`Q` 必输。

+ 两边长度一定相等。

若不等，则 `D` 选择较长的一条，无论长度奇或偶，`Q` 一定输。

***

知道了这些，便可以想怎么实现了。

我们可以预处理出每个山两边能走的长度。

代码：
```cpp
	pre[1] = 1;
	for (int i(2); i <= n; ++i) {
		if (a[i] > a[i - 1]) pre[i] = pre[i - 1];
		else pre[i] = i;
	} //处理往前能走到的最小下标。
	nxt[n] = n;
	for (int i(n - 1); i; --i) {
		if (a[i] > a[i + 1]) nxt[i] = nxt[i + 1];
		else nxt[i] = i;
	} //处理往后能走到的最大下标。
    int ma = 0, cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (i - pre[i] == ma) ++cnt;
		else if (i - pre[i] > ma) cnt = 1, ma = i - pre[i];	
		if (nxt[i] - i == ma) ++cnt;
		else if (nxt[i] - i > ma) cnt = 1, ma = nxt[i] - i;	
	} //求一共有多少条长度最大的下降子序列。
```

***

然后按照上述的条件判断这个下标是否可取。

代码：

```cpp
    int ans = 0;
	for (int i(1); i <= n; ++i) {
		int len1 = nxt[i] - i, len2 = i - pre[i];
		if (!len1 || !len2) continue;
		ans += (max(len1, len2) % 2 == 0 && len1 == len2 && max(len2, len1) == ma && cnt <= 2);
	}
```

时间复杂度 $\operatorname{O}(n)$，稳过。

---

## 作者：FutaRimeWoawaSete (赞：0)

TM真的是难受，考场上前面预处理打了个分块还打爆了……         

个人认为这道题的解法有两种，一种 $O(n)$ 一种 $O(n \sqrt n)$ ，这里着重讲解 $O(n)$ 解法，会将 $O(n \sqrt n)$ 附在最后（不过没去实现）。           

首先这道题有个很明显的结论：答案只会为 $0 , 1$ 。      

其实很好理解，我们发现其实 A , B 的操作是等价的，只不过是起点和终点不同罢了，并且我们很明显可以感觉到，一个点像左右两边延伸的最长长度 L 与 R 其实是一堆单调递减的数组叠加在一起形成的（而且每一段单调递减的数组有一个最优点），这也就说明我们应该选的点的 L , R 是不会交的。这时这个结论就很显了，如果 A 选择一个不是最优的点，如果这个点本就不属于全局最优点 PPos 所管辖的单调递减数组的话，我们 B 就选 PPos 就行了。否则的话我们现在就直接在 PPos 所在的单调递减数组里面操作，你 A 选的这个点肯定在 B 选完之后分不到更多的路径，结论得证。       

接着我们只要考虑最优点可不可以取即可（其实有了这个结论后我们可以直接先找到最优点，然后用每一个点尝试去叉他即可，不过这里也可以直接判，着重介绍一下直接判的情况）。          

剔除掉一些冗杂点，这些点都是左右两边有一端走不通的点，这个我们必须要把它的 L 和 R 清空，不然我们就会爆掉 。（应该是赛时没想到的地方）            

接着我们把最优点找出来，看有没有其他点可以有一样长的方案（因为经过上述证明后我们选出来的这个点肯定和他不是在一个单调递减数组里面），如果没有的话我们还要去判断 L 和 R是不是等长，如果不等长的话那么 B就可以长的那一边立马去堵他，最优情况都是两者获得的路径一样长，所以必须要等长，接着还要判断 L 和 R 是不是偶数，不然的话 B 还是可以堵。                 

对于 1 和 n ， 这里需要注意一下，我们不能直接扔掉，因为他们也可以在找有没有与最优点一样长的方案时影响答案。           

其实个人认为还是一道比较毒瘤的分类讨论问题，反正我分类讨论能力一直都很差（~~这可能是因为初一初二的时候真的学的很差~~），没做出来也肯定是能力缺失，至少对于此题而言没有什么机遇不机遇运气不运气可言。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int Len = 1e5 + 5;
int n,m,a[Len],posA,Lmax[Len],Rmax[Len];
int main()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++) scanf("%d",&a[i]);
	posA = 1;
	for(int i = 1 ; i < n ; i ++)
	{
		Lmax[i] = i - posA;
		if(a[i + 1] < a[i]) posA = i + 1;
	}
	Lmax[n] = n - posA;
	posA = n;
	for(int i = n ; i >= 2 ; i --)
	{
		Rmax[i] = posA - i;
		if(a[i - 1] < a[i]) posA = i - 1;
	}
	Rmax[1] = posA - 1;
	for(int i = 1 ; i <= n ; i ++) 
	{
		if(a[i - 1] > a[i] || a[i + 1] > a[i]) Lmax[i] = Rmax[i] = 0;
	}
//	for(int i = 1 ; i <= n ; i ++) printf("%d %d\n",Lmax[i], Rmax[i]);
	int pos = -1;
	for(int i = 2 ; i <= n - 1 ; i ++)
		if(pos == -1 || max(Lmax[i] , Rmax[i]) > max(Lmax[pos] , Rmax[pos])) pos = i;
	if(pos == -1) return puts("0") & 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		if(pos == i) continue;
		if(max(Lmax[i] , Rmax[i]) == max(Lmax[pos] , Rmax[pos])) return puts("0") & 0;
	}
	if(Lmax[pos] != Rmax[pos] || Rmax[pos] % 2 == 1) return puts("0") & 0;
	return puts("1") & 0;
}
```

PS： $O(n\sqrt n)$ 应该就是我们先暴力 $O(n ^ 2)$ 出来，然后有一个这么玩意儿，这里以向左找为例：          

```cpp
int optl = 0 , optr = 0;
if(((i - j + 1) % 2 == 0) && (Rmax[j][1] + j >= i - Lmax[i][0])) optl = 1;//条件1
if(Lmax[j][1] >= Lmax[i][0]) optl = 1;//条件2
if(max(Rmax[j][1] , Lmax[j][1]) >= Rmax[i][0]) optr = 1;//条件3
if(optl & optr){ans -- ; flag = false ; break;} 
```

这个解法不用上述推得的答案只为 $0 , 1$ 的情况，~~非常裸~~。     

我们考虑这个玩意儿，诶我们发现只有条件3影响 optr ，所以我们直接把 ```max(Rmax[j][1] , Lmax[j][1])``` 丢进去我们的阈值里面，然后开两个分块数组一个维护条件1一个维护条件2，对于条件1里面的区间长为偶数我们记录一下下标的奇偶，再来个分块数组即可。             



---

## 作者：清烛 (赞：0)

upd：更新了一处笔误，即答案存在的条件。

### 题意
给定一个 $1-n$ 的排列 $p$，Qingshan 和 Daniel 在草稿纸上按照如下规则进行远足游戏。

首先 Qingshan 选定一个数 $x$ **并告诉 Daniel**，接下来 Daniel 选定另一个数 $y$，$1\le x, y\le n$ 且 $x\not=y$。然后他们轮流进行游戏，Qingshan 为先手：

- 如果轮到 Qingshan，则 Qingshan 只能把 $x$ 移动到 $x'$，其中 $|x' - x| = 1$，且 $x' \neq y$，$p_x\gt p_{x'}$。
- 如果轮到 Daniel，则 Daniel 只能把 $y$ 移动到 $y'$，其中 $|y' - y| = 1$，且 $y'\neq x$，$p_y\lt p_{y'}$。

如果轮到某一方时无路可走了，则另一方胜利。

假设双方都足够聪明，那么判断有多少个初始的 $x$ 可以让 Qingshan 一定取胜。

### 题解
首先发掘这个游戏的性质：每个人只能往一个方向走，不能回头。注意到这个性质之后不难发现如果 Qingshan 要赢，那么 Daniel 必须被 Qingshan 卡死或者自己被卡死。

因为两方都足够聪明，所以我们把问题范围缩小到最长单调序列上面来，因为这样可以最大化双方的移动步数。

可以证明的是，**Qingshan 一开始选的点在最长单调序列的顶端是他能赢的必要条件**。至于为什么呢？如果 Qingshan 选的不是最长单调序列的顶端，那么 Daniel 就可以选最长单调序列的底端进行游戏，那么 Qingshan 肯定先被卡死。

并且如果有多条不相交的最长单调序列，**Qingshan 必输**。因为这样 Daniel 可以选择另外一条序列的底端，而 Qingshan 是先手，所以 Qingshan **肯定先被卡死**。

如果只有一条最长单调序列，还是 **Qingshan 必输**，因为 Qingshan 是先手，Daniel 选择的位置但凡与 Qingshan 的初始位置成的链长为**偶数**，**那么 Daniel 肯定可以卡死 Qingshan**。

剩下的两种情况就是同时有两条最长单调序列，要么成“V”形要么成山峰形。对于“V”形的情况**还是 Qingshan 必输**，因为 Daniel 可以往与 Qingshan 相反的方向跑走，那么当 Qingshan 最后到达谷底的时候就 GG 了。对于山峰形的情况，Qingshan 肯定是选峰顶，接下来分最长单调序列长度的奇偶性讨论：

奇数：如果 Daniel 选了坡底，**那么 Qingshan 只要往 Daniel 的方向走那么就必然可以卡死 Daniel**；如果不选坡底，**那么 Qingshan 只要往另一个方向走就可以让 Daniel 先无路可走**，所以此时答案为 $1$，Qingshan 唯一的必胜策略就是选择山顶。

偶数：类似上面的分析方法，不难发现**要么 Daniel 卡死 Qingshan，要么 Qingshan 先无路可走**，所以 Qingshan **必败**。

分分析到这里我们就发现了**答案为 $1$ 当且仅当有两条长度为奇数的最长单调序列并且他们共享一个最高点，否则答案为 $0$**。$O(n)$ 直接扫就可以过了。

```cpp
#include <cstdio>
#include <cctype>
#include <set>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 1e5 + 5;
int n, a[maxn], pre[maxn], suf[maxn], pos[maxn];

int main()
{
    n = read();
    FOR(i, 1, n)
        a[i] = read();
    FOR(i, 1, n)
        if (a[i] > a[i - 1])
            pre[i] = pre[i - 1] + 1;
        else pre[i] = 1;
    DEC(i, n, 1)
        if (a[i] > a[i + 1])
            suf[i] = suf[i + 1] + 1;
        else suf[i] = 1;
    int maxlen = 0, cnt = 0;
    bool flag = 0;
    FOR(i, 1, n)
        maxlen = max(max(maxlen, pre[i]), suf[i]);
    FOR(i, 1, n)
    {
        if (pre[i] == maxlen)
            ++cnt;
        if (suf[i] == maxlen)
            ++cnt;
        if (i + maxlen - 1 <= n && i - maxlen + 1 >= 1 && suf[i] == maxlen && pre[i] == maxlen)
            flag = 1;
    }
    if (cnt == 2 && flag)
    {
        printf("%d\n", maxlen & 1);
        return 0;
    }
    else puts("0");
    return 0;
}
```

---

## 作者：little_sun (赞：0)

### 题目描述

有一个长度为 $n$ 的排列，有两个人 $A,B$ 要在这个排列上移动。

$A$ 只能往相邻的且满足数值小于当前位置的位置移动， $B$反之。

$A$ 先走，不能移动的人算输，询问有多少位置满足 $A$ 从这里开始一定赢。

### 题目分析

首先一个点要满足条件一定要是一个极大值点，所以我们可以把范围缩小到这些点上。

我们设该点为 $x$， $x$ 往左右能延伸的最大长度为 $max$，例如下图 $11$ 号点的 $max=2$

![](https://cdn.luogu.com.cn/upload/image_hosting/owk7d273.png)

如果在整个排列去掉以 $x$ 为山顶的山峰能找到一个连续递增/递减的子串满足长度 $ \leq max$，那么 $x$ 肯定不满足条件。

接下来我们看下下面这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/9g7cwirb.png)

显然，$B$只要在最左边的位置就能保证无论 $A$ 怎么走都是必输，所以 $max \equiv 1 \pmod 2$ 的情况不行。

于是我们保证了$max \equiv 0 \pmod 2$，在这个限制下我们发现两边延伸的长度不一样的情况也是不行的。如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/0268urib.png)

$B$只要在左数第二个的位置就能保证无论 $A$ 怎么走都是必输，于是我们又有了两边延伸的长度相等的限制，现在我们就可以愉快的解决这个题了。

### 代码

``` cpp
#include <bits/stdc++.h>

#define R register
#define ll long long
#define sum(a, b, mod) (((a) + (b)) % mod)
#define meow(cat...) fprintf(stderr, cat)

const int MaxN = 1e5 + 10;

int n, ans, a[MaxN], l[MaxN], r[MaxN], ls[MaxN], rs[MaxN];
int lp[MaxN], rp[MaxN], linc[MaxN], rinc[MaxN];

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch > '9' || ch < '0')
        ch = getchar();
    while (ch <= '9' && ch >= '0')
        x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
    return x;
}

signed main()
{
    n = read(), ans = 0, a[0] = a[n + 1] = n + 1;
    for (int i = 1; i <= n; i++)
        a[i] = read(), lp[i] = rp[i] = i;
    for (int i = 2; i <= n; i++)
        if (a[i] < a[i - 1])
            linc[i] = linc[i - 1] + 1;
    for (int i = n - 1; i; i--)
        if (a[i] < a[i + 1])
            rinc[i] = rinc[i + 1] + 1;
    for (int i = 2; i <= n; i++)
        linc[i] = std::max(linc[i], linc[i - 1]);
    for (int i = n - 1; i; i--)
        rinc[i] = std::max(rinc[i], rinc[i + 1]);
    for (int i = 2; i <= n; i++)
        if (a[i] > a[i - 1])
            l[i] = l[i - 1] + 1, lp[i] = lp[i - 1];
    for (int i = n - 1; i; i--)
        if (a[i] > a[i + 1])
            r[i] = r[i + 1] + 1, rp[i] = rp[i + 1];
    for (int i = 1; i <= n; i++)
        ls[i] = std::max(l[i], ls[i - 1]);
    for (int i = n; i; i--)
        rs[i] = std::max(r[i], rs[i + 1]);
    for (int i = 1; i <= n; i++)
        if (l[i] && r[i])
        {
            int max = std::max(l[i], r[i]);
            if (ls[i - 1] >= max || rs[i + 1] >= max)
                continue;
            if (linc[i - 1] >= max || rinc[i + 1] >= max)
                continue;
            int min = std::min(l[i], r[i]);
            if (max & 1) continue;
            if (min & 1) continue;
            if (max > min) continue;
            ++ans; 
        }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：Fairicle (赞：0)

看完题目尝试化简一下题意并寻找性质。（称 Qingshan 为 Q，Daniel 为 D）

首先容易发现他们的移动都是选定方向不能回头的。其次发现，Q 是往小走，D 是往大走。

如果一个点左右两边**没有都小于它**，这个点是不可以选的，因为 D 可以堵在小于它的那一边，Q 一开始就走不了。

所以要左右两边都小于它。考虑一个点能向左右走多远，这个可以预处理前缀后缀搞出来。

如果左右两边距离相等（**这个距离定义为经过的点数，起点终点也包含**），分奇偶考虑。如果距离是偶数，D 随便堵在一个终点位置，Q 都输了。如果是奇数，Q 就得到外面去找一个最长上升（或者说下降，一样的）段看是否有大于等于这个距离，没有的话这个点就是一个答案。

如果向左走的距离不等于向右走的距离，那么这也是不行的，D 可以堵在更长的一边的最后一个格子（长度为偶数）或者更长一边的倒数第二个格子（长度为奇数）。

所以只有向左右走长度相等且为奇数的情况才有可能有答案。

这时候可以写出代码：

```cpp
#include"bits/stdc++.h"
using namespace std;
#define ll long long
#define ul unsigned long long
#define ui unsigned int
#define ri register int
#define pb push_back
#define mp make_pair
inline ll rd(){
	ll x=0,flag=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') flag=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+(ch^48);ch=getchar();}
	return x*flag;
}
#define N 300010
int t,n,m,pre[N],suf[N],tree[N<<1],p[N];
inline void build(int id,int l,int r){
    if(l==r){tree[id]=max(pre[l],suf[l]);return;}
    int mid=(l+r)>>1;
    build(id<<1,l,mid),build(id<<1|1,mid+1,r);
    tree[id]=max(tree[id<<1],tree[id<<1|1]);
}
inline int query(int id,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr) return tree[id];
    int mid=(l+r)>>1,mx=0;
    if(ql<=mid) mx=max(mx,query(id<<1,l,mid,ql,qr));
    if(qr>mid) mx=max(mx,query(id<<1|1,mid+1,r,ql,qr));
    return mx;
}
int main()
{
	n=rd();
	for(ri i=1;i<=n;++i) p[i]=rd();
	for(ri i=1;i<=n;++i) if(p[i]>p[i-1]) pre[i]=pre[i-1]+1;else pre[i]=1;
	for(ri i=n;i>=1;--i) if(p[i]>p[i+1]) suf[i]=suf[i+1]+1;else suf[i]=1;
	build(1,1,n);
	int ans=0;
	for(ri i=2;i<=n;++i){
        if(pre[i]==1||suf[i]==1) continue;
        if(pre[i]!=suf[i]) continue;
        if(pre[i]%2==0) continue;
        if(max(query(1,1,n,1,i-pre[i]+1),query(1,1,n,i+suf[i]-1,n))>=pre[i]);
        else ans++;
    }
    cout<<ans;
    return 0;
}

```
这里多此一举使用了线段树，可以直接预处理前缀最大值和后缀最大值来做。

这道题就解决了，但是有更进一步的结论：答案只可能是 0 或 1。这个也是比较好理解的，考虑统计答案的时候，只有外面最长段小于它的长度才可以，也就是说它一定是全局最长段，并且这个最长段唯一。所以答案至多为 1 了。

---

