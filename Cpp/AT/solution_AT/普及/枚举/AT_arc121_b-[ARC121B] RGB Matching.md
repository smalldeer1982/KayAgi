# [ARC121B] RGB Matching

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc121/tasks/arc121_b

すぬけ君は $ 1 $ から $ 2N $ の番号がついた $ 2N $ 匹の犬を飼っています。

犬 $ i $ のかわいさは $ a_i $ です。 それぞれの犬の体色は赤、緑、青のいずれかで、犬 $ i $ の体色は $ c_i $ です。 $ c_i $ は `R`, `G`, `B` のいずれかであり、`R` ならばその犬の体色が赤であることを、`G` ならば緑であることを、`B` ならば青であることを表します。

すぬけ君は $ N $ 棟の犬小屋を持っており、それぞれの犬小屋に $ 2 $ 匹の犬を住まわせようとしています。 どの犬もちょうど一つの犬小屋に住んでいるように住まわせる必要があることに注意してください。

$ 2 $ 匹の犬を同じ犬小屋に住まわせるとその小屋には *不満* が生じます。 不満の度合いは整数で表され、犬 $ i,j $ が同じ小屋にいるとき生じる不満は $ c_i\ =\ c_j $ ならば $ 0 $、そうでなければ $ |a_i\ -\ a_j| $ です。

$ N $ 棟の犬小屋に犬を $ 2 $ 匹ずつ住まわせた結果生じる不満の総和としてありうる値の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 10^{5} $
- $ 1\ \leq\ a_i\ \leq\ 10^{15} $
- $ a_i $ は整数
- $ c_i $ は `R`, `G`, `B` のいずれか

### Sample Explanation 1

\- 犬 $ 1 $ のかわいさは $ 1 $、犬 $ 2 $ のかわいさは $ 2 $ です。 - $ c_1\ \neq\ c_2 $ より、不満は $ 1 $ となります。

### Sample Explanation 2

\- 犬 $ 1 $ のかわいさは $ 1 $、犬 $ 2 $ のかわいさは $ 2 $ です。 - $ c_1\ =\ c_2 $ より、不満は $ 0 $ となります。

## 样例 #1

### 输入

```
1
1 R
2 G```

### 输出

```
1```

## 样例 #2

### 输入

```
1
1 B
2 B```

### 输出

```
0```

## 样例 #3

### 输入

```
10
585 B
293 B
788 B
222 B
772 G
841 B
115 R
603 G
450 B
325 R
851 B
205 G
134 G
651 R
565 R
548 B
391 G
19 G
808 B
475 B```

### 输出

```
0```

# 题解

## 作者：zhaomumu1218 (赞：1)

### 题意
有 $2n$ 块巧克力，每个巧克力都有颜色和美味度。每次吃掉两个巧克力，如果他们颜色一样，不满意度为 $0$ 否则不满意度是他们美味度的差。求最小不满意度。
### 思路
把同一种颜色的巧克力放到同一个数组里，统计出长度后会出现这两种情况：
1. 两个数组长度是奇数，一个数组长度是偶数。
2. 三个数组长度都是偶数。
***
先看第一种情况。在两个长度为奇数的数组里找美味度相差最少的两块巧克力，把他们一起吃掉，剩下巧克力的跟同颜色一起吃掉。但是这样并不一定是最优的，比如 
```
2
100 R
100 G
0 G
0 B
```
可以把第 $1$ 和第 $2$ 块巧克力一起吃掉，再把后两块一起吃掉，不满意度为 $0$。按照上述的方法做，得到的结果是 $100$，错了！

观察数据可以发现，用那两个长度为奇数的数组分别在长度为偶数的数组里找差值最小的两个数，求那两个数的和就行了。这样也不一定是最优的，跟上面那种方法得到的答案取最小值就行了。

第二种情况答案就是 $0$。
### 代码
前三个部分基本一样，因为我很懒，所以只批注第 $1$ 个部分了。
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
pair<int,char>a[200010];
int lenr,leng,lenb,ans=2000000000000010,r[200010],g[200010],b[200010],n;
signed main(){
    scanf("%lld",&n);
    n*=2;
    for(int i=1;i<=n;i++) scanf("%lld",&a[i].first),cin>>a[i].second;
    for(int i=1;i<=n;i++){
        if(a[i].second=='R') r[++lenr]=a[i].first;
        if(a[i].second=='G') g[++leng]=a[i].first;
        if(a[i].second=='B') b[++lenb]=a[i].first;
    }
    int rr=(lenr%2),gg=(leng%2),bb=(lenb%2);
    sort(r+1,r+1+lenr);
    sort(g+1,g+1+leng);
    sort(b+1,b+1+lenb);
    if(rr&&gg){
        for(int i=1;i<=lenr;i++){
            int z=*lower_bound(g+1,g+1+leng,r[i]),y=z++;
            ans=min(ans,min(abs(r[i]-z),abs(y-r[i])));
        }
        for(int i=1;i<=leng;i++){
            int z=*lower_bound(r+1,r+1+lenr,g[i]),y=z++;
            ans=min(ans,min(abs(g[i]-z),abs(y-g[i])));
        }//在长度为奇数的两个数组中找最接近的两个数
        int ls=2000000000000010,yl=0,lsl=2000000000000010;
        for(int i=1;i<=lenr;i++){
            auto zz=lower_bound(b+1,b+1+lenb,r[i]),yy=g,xx=g;
            yy=zz++;
            zz--,zz--,xx=zz,zz++,zz++;
            int z=*zz,y=*yy,x=*xx;
            int lls=abs(r[i]-z),yls=zz-b;
            if(lls>abs(y-r[i])) lls=abs(y-r[i]),yls=yy-b;
            if(lls>abs(x-r[i])) lls=abs(x-r[i]),yls=xx-b;
            if(ls>lls) ls=lls,yl=yls;
        }
        for(int i=1;i<=leng;i++){
            auto zz=lower_bound(b+1,b+1+lenb,g[i]),xx=g,yy=g;
            zz--,xx=zz,zz++,zz++,yy=zz,zz--;
            int z=*zz,y=*yy,x=*xx;
            if(zz-b!=yl) lsl=min(lsl,abs(z-g[i]));
            if(yy-b!=yl) lsl=min(lsl,abs(y-g[i]));
            if(xx-b!=yl) lsl=min(lsl,abs(x-g[i]));
        }
        ans=min(ans,ls+lsl);//用两个长度为奇数的数组在长度为偶数的数组里找差值最小的两个数，求那两个数的和。
        ls=2000000000000010,yl=0,lsl=2000000000000010;
        for(int i=1;i<=leng;i++){
            auto zz=lower_bound(b+1,b+1+lenb,g[i]),yy=zz++,xx=g;
            zz--,zz--,xx=zz,zz++,zz++;
            int z=*zz,y=*yy,x=*xx;
            int lls=abs(g[i]-z),yls=zz-b;
            if(lls>abs(y-g[i])) lls=abs(y-g[i]),yls=yy-b;
            if(lls>abs(x-g[i])) lls=abs(x-g[i]),yls=xx-b;
            if(ls>lls) ls=lls,yl=yls;
        }
        for(int i=1;i<=lenr;i++){
            auto zz=lower_bound(b+1,b+1+lenb,r[i]),yy=g,xx=g;
            zz--,xx=zz,zz++,zz++,yy=zz,zz--;
            int z=*zz,y=*yy,x=*xx;
            if(zz-b!=yl) lsl=min(lsl,abs(z-r[i]));
            if(yy-b!=yl) lsl=min(lsl,abs(y-r[i]));
            if(xx-b!=yl) lsl=min(lsl,abs(x-r[i]));
        }
        ans=min(ans,ls+lsl);// 不要忘记把顺序倒过来再做一次
    }
    else if(rr&&bb){
        for(int i=1;i<=lenr;i++){
            auto zz=lower_bound(b+1,b+1+lenb,r[i]),yy=zz++;
            int z=*zz,y=*yy;
            ans=min(ans,min(abs(r[i]-z),abs(y-r[i])));
        }
        for(int i=1;i<=lenb;i++){
            auto zz=lower_bound(r+1,r+1+lenr,b[i]),yy=zz++;
            int z=*zz,y=*yy;
            ans=min(ans,min(abs(b[i]-z),abs(y-b[i])));
        }
        int ls=2000000000000010,yl=0,lsl=2000000000000010;
        for(int i=1;i<=lenr;i++){
            auto zz=lower_bound(g+1,g+1+leng,r[i]),yy=zz++,xx=g;
            zz--,zz--,xx=zz,zz++,zz++;
            int z=*zz,y=*yy,x=*xx;
            int lls=abs(r[i]-z),yls=zz-g;
            if(lls>abs(y-r[i])) lls=abs(y-r[i]),yls=yy-g;
            if(lls>abs(x-r[i])) lls=abs(x-r[i]),yls=xx-g;
            if(ls>lls) ls=lls,yl=yls;
        }
        for(int i=1;i<=lenb;i++){
            auto zz=lower_bound(g+1,g+1+leng,b[i]),yy=g,xx=g;
            zz--,xx=zz,zz++,zz++,yy=zz,zz--;
            int z=*zz,y=*yy,x=*xx;
            if(zz-g!=yl) lsl=min(lsl,abs(z-b[i]));
            if(yy-g!=yl) lsl=min(lsl,abs(y-b[i]));
            if(xx-g!=yl) lsl=min(lsl,abs(x-b[i]));
        }
        ans=min(ans,ls+lsl);
        ls=2000000000000010,yl=0,lsl=2000000000000010;
        for(int i=1;i<=lenb;i++){
            auto zz=lower_bound(g+1,g+1+leng,b[i]),yy=zz++,xx=g;
            zz--,zz--,xx=zz,zz++,zz++;
            int z=*zz,y=*yy,x=*xx;
            int lls=abs(b[i]-z),yls=zz-g;
            if(lls>abs(y-b[i])) lls=abs(y-b[i]),yls=yy-g;
            if(lls>abs(x-b[i])) lls=abs(x-b[i]),yls=xx-g;
            if(ls>lls) ls=lls,yl=yls;
        }
        for(int i=1;i<=lenr;i++){
            auto zz=lower_bound(g+1,g+1+leng,r[i]),yy=g,xx=g;
            zz--,xx=zz,zz++,zz++,yy=zz,zz--;
            int z=*zz,y=*yy,x=*xx;
            if(zz-g!=yl) lsl=min(lsl,abs(z-r[i]));
            if(yy-g!=yl) lsl=min(lsl,abs(y-r[i]));
            if(xx-g!=yl) lsl=min(lsl,abs(x-r[i]));
        }
        ans=min(ans,ls+lsl);
    }
    else if(gg&&bb){
        for(int i=1;i<=leng;i++){
            int z=*lower_bound(b+1,b+1+lenb,g[i]),y=z++;
            ans=min(ans,min(abs(g[i]-z),abs(y-g[i])));
        }
        for(int i=1;i<=lenb;i++){
            int z=*lower_bound(g+1,g+1+leng,b[i]),y=z++;
            ans=min(ans,min(abs(b[i]-z),abs(y-b[i])));
        }
        int ls=2000000000000010,yl=0,lsl=2000000000000010;
        for(int i=1;i<=leng;i++){
            auto zz=lower_bound(r+1,r+1+lenr,g[i]),yy=zz++,xx=g;
            zz--,zz--,xx=zz,zz++,zz++;
            int z=*zz,y=*yy,x=*xx;
            int lls=abs(g[i]-z),yls=zz-r;
            if(lls>abs(y-g[i])) lls=abs(y-g[i]),yls=yy-r;
            if(ls>lls) ls=lls,yl=yls;
        }
        for(int i=1;i<=lenb;i++){
            auto zz=lower_bound(r+1,r+1+lenr,b[i]),yy=g,xx=g;
            zz--,xx=zz,zz++,zz++,yy=zz,zz--;
            int z=*zz,y=*yy,x=*xx;
            if(zz-r!=yl) lsl=min(lsl,abs(z-b[i]));
            if(yy-r!=yl) lsl=min(lsl,abs(y-b[i]));
            if(xx-r!=yl) lsl=min(lsl,abs(x-b[i]));
        }
        ans=min(ans,ls+lsl);
        ls=2000000000000010,yl=0,lsl=2000000000000010;
        for(int i=1;i<=lenb;i++){
            auto zz=lower_bound(r+1,r+1+lenr,b[i]),yy=zz++,xx=g;
            zz--,zz--,xx=zz,zz++,zz++;
            int z=*zz,y=*yy,x=*xx;
            int lls=abs(b[i]-z),yls=zz-r;
            if(lls>abs(y-b[i])) lls=abs(y-b[i]),yls=yy-r;
            if(lls>abs(x-b[i])) lls=abs(x-b[i]),yls=xx-r;
            if(ls>lls) ls=lls,yl=yls;
        }
        for(int i=1;i<=leng;i++){
            auto zz=lower_bound(r+1,r+1+lenr,g[i]),yy=g,xx=g;
            zz--,xx=zz,zz++,zz++,yy=zz,zz--;
            int z=*zz,y=*yy,x=*xx;
            if(zz-b!=yl) lsl=min(lsl,abs(z-g[i]));
            if(yy-b!=yl) lsl=min(lsl,abs(y-g[i]));
            if(xx-b!=yl) lsl=min(lsl,abs(x-g[i]));
        }
        ans=min(ans,ls+lsl);
    }
    else ans=0;
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：DengDuck (赞：1)

性质 $1$：最优方案每两种颜色之间不会有两对元素配对。

证明：选择两对异色配对，让其与另外一个同色的配对，代价为 $0$，只会更优。

性质 $2$：最优方案异色元素配对不超过两对。

证明：满足性质 $1$ 下，显然不可能是三对以上，三对也不行，三对就是每两种颜色都都要配对，这样这三对每种颜色都出现了两次，不如改成同色的配对。

所以只有三种情况：

- 每种颜色数量都为偶数，都同色配对，代价为 $0$。
- 有两种颜色数量为奇数，让这两种颜色配对一组。
- 有两种颜色数量为奇数，让数量为偶数的颜色与这两种颜色分别配对一组。

容易用 `set` 维护前驱后继，然后就可以求其他数组里与某个值相差最小的值，然后后两种情况维护就比较简单。

时间复杂度为 $\mathcal O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define LF long double
#define pLL pair<LL,LL>
#define pb push_back
//#define fir first
//#define sec second
using namespace std;
const LL inf=1e15;
const LL N=2e5+5;
//const LL M;
//const LL mod;
//const LF eps;
//const LL P;
LL n,cnt[3],x,ans=inf,pre[N],suf[N];
vector<LL>v[3];
char c[5];
set<LL>s,s1;
int main()
{
	scanf("%lld",&n);
	for(int i=1;i<=2*n;i++)
	{
		scanf("%lld",&x);
		scanf("%s",c);
		LL t;
		if(c[0]=='R')t=0;
		if(c[0]=='G')t=1;
		if(c[0]=='B')t=2;
		v[t].pb(x),cnt[t]++;
	}
	if(cnt[0]%2==0&&cnt[1]%2==0&&cnt[2]%2==0)
	{
		puts("0");
		return 0;
	}
	if(cnt[1]%2==0)swap(cnt[1],cnt[0]),swap(v[1],v[0]);
	if(cnt[2]%2==0)swap(cnt[2],cnt[0]),swap(v[2],v[0]);
	for(LL i:v[2])s.insert(i);
	for(LL i:v[1])s1.insert(i);
	for(LL i:v[1])
	{
		auto t1=s.lower_bound(i);
		LL t=inf;
		if(t1!=s.end())t=min(t,*t1-i);
		if(t1!=s.begin())t=min(t,i-*(--t1));
		
		ans=min(ans,t);
	}
	pre[0]=inf,suf[cnt[0]+1]=inf;
	for(int i=1;i<=cnt[0];i++)
	{
		auto t1=s1.lower_bound(v[0][i-1]);
		LL t=inf;
		if(t1!=s1.end())t=min(t,*t1-v[0][i-1]);
		if(t1!=s1.begin())t=min(t,v[0][i-1]-*(--t1));
		
		pre[i]=suf[i]=t;
	}
	for(int i=1;i<=cnt[0];i++)pre[i]=min(pre[i],pre[i-1]);
	for(int i=cnt[0];i>=1;i--)suf[i]=min(suf[i],suf[i+1]);
	for(int i=1;i<=cnt[0];i++)
	{
		auto t1=s.lower_bound(v[0][i-1]);
		LL t=inf;
		if(t1!=s.end())t=min(t,*t1-v[0][i-1]);
		if(t1!=s.begin())t=min(t,v[0][i-1]-*(--t1));
		
		ans=min(ans,t+min(pre[i-1],suf[i+1]));	
	}	
	printf("%lld",ans);
	return 0;
}
//RP++
```

---

## 作者：Felix72 (赞：0)

一个 DP 解法：排完序后如果有要产生不满意度的两块巧克力，这两块一定是相邻的，否则可以通过调整到相邻的位置使得答案不劣于原来的情况。

基于这个结论，设状态 $f_{p, 0/1, 0/1, 0/1}$ 表示考虑到第 $p$ 块巧克力，不产生不满意度的三种巧克力的个数分别是奇数还是偶数时，答案的最小值。每次转移有两种情况：

- 后面的一块巧克力不产生不满意度；
- 后面的两块巧克力配对，产生不满意度。

按照这个转移写，感觉代码比贪心简单。

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & (-x))
using namespace std;

const int N = 200010;
int n, m; long long f[N][2][2][2];
struct node {long long p; char c;} a[N];
inline bool cmp(node u, node v) {return u.p < v.p;}
inline void check(long long &now, long long comp) {now = min(now, comp);}

int main()
{
//	freopen("text.in", "r", stdin);
//	freopen("prog.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n; n *= 2;
	for(int i = 1; i <= n; ++i) cin >> a[i].p >> a[i].c;
	sort(a + 1, a + n + 1, cmp);
	memset(f, 0x3f, sizeof(f));
	f[0][0][0][0] = 0;
	for(int p = 0; p < n; ++p)
	{
		for(int i = 0; i <= 1; ++i)
		{
			for(int j = 0; j <= 1; ++j)
			{
				for(int k = 0; k <= 1; ++k)
				{
					check(f[p + 1][i ^ (a[p + 1].c == 'R')][j ^ (a[p + 1].c == 'G')][k ^ (a[p + 1].c == 'B')], f[p][i][j][k]);
					if(p + 2 <= n) check(f[p + 2][i][j][k], f[p][i][j][k] + (a[p + 2].p - a[p + 1].p));
				}
			}
		}
	}
	cout << f[n][0][0][0] << '\n';
	return 0;
}
/*

*/
```

---

## 作者：huangzhixia (赞：0)

**[题目传送门](https://www.luogu.com.cn/problem/AT_arc121_b)**

## 题意

有 $2N$ 个巧克力，每个巧克力都有一个满意值和一个颜色。现在我们要把 $2N$ 个巧克力分成 $N$ 组，每组 $2$ 个，每组两个颜色不一样的话，我们的不满意值就要加上这两个巧克力满意度相减的绝对值，求怎么分组能让不满意度最小。

## 思路

首先，暴力配对，需要 $O(n^2)$ 的复杂度，肯定不能过的，这时候就要开始优化啦！

看到最小的字眼，第一反应想到的肯定是**贪心**。

贪心的策略是什么？详见以下几点：

- 我们注意到，必须是要两个巧克力的颜色不一样才能让我们的不满意度增加的，也就是说我们要尽量地让每组巧克力的颜色不一样，这是第一要考虑的策略。

- 考虑完上面的策略以后，现在我们可以统计一下每个颜色的巧克力。这就不容易想到，如果每种颜色的巧克力他的个数都是**偶数**，那肯定是都能分完的。那么我们就直接输出 $0$，因为根本不会有颜色不同的一组。

- 否则的话，我们思考随便两种颜色为奇数（其他的也是一样的），比如颜色 A 和 B 都为奇数，我们要选出 A 和 B 颜色中相差最小的那一组，拿出来，然后拿满意值得绝对值加入答案。

因为可能需要排序，所以时间复杂度降为 $O(n \log n)$。

---

## 作者：HappyJaPhy (赞：0)

# 题意
- 有 $2N$ 个物品，每个物品有可爱度 $a_i$ 和颜色 $c_i$，将其两两配对。假设物体 $i$ 和 $j$ 配对，则 $c_i\neq c_j$，则会增加 $|a_i-a_j|$ 的不满意度，求最小的不满意度。

# 分析
- 这道题可以贪心解决。我们尽量让每一对物品颜色相同，令每种颜色的总个数为 $cnt_c$，则：
1. 若 $cnt_R$、$cnt_G$、$cnt_B$ 均为偶数，则答案为 $0$。
2. 若 $cnt_R$ 和 $cnt_G$ 为奇数（其余情况同理），那么我们将颜色为 R 和 G 的物品个留出一个配对，剩余的物品以相同颜色两两配对；也可以将一个 R 和一个 B 配对，再把一个 G 和一个 B 配对。取这两种情况的最小值即可。
- 时间复杂度 $O(n\log n)$。

# AC 代码
```cpp
#include <bits/stdc++.h>
#define int long long
#define inf 1e18
#define N 200005
using namespace std;
int n;
vector<int> a[4];

inline int read(int &x) {
	char ch = x = 0;
	while (ch < '0' || ch > '9')
		ch = getchar();
	while (ch >= '0' && ch <= '9') {
		x = (x << 1) + (x << 3) + ch - 48;
		ch = getchar();
	}
	return x;
}

inline int calc(int u, int v) {
	int ans = inf;
	if (a[v].empty()) {
		return ans;
	}
	int lu = a[u].size(), lv = a[v].size(), j = 0;
	for (int i = 0; i < lu; i++) { //求取差值最小的那一对
		while (j + 1 < lv && a[v][j + 1] <= a[u][i]) { //尺取法
			j++;
		}
		ans = min(ans, abs(a[u][i] - a[v][j]));
		if (j + 1 < lv) {
			ans = min(ans, abs(a[u][i] - a[v][j + 1]));
		}
	}
	return ans;
}

signed main() {
	read(n);
	n <<= 1;
	char ch = 0;
	int x;
	for (int i = 1; i <= n; i++) {
		read(x);
		ch = getchar();
		while (ch < 'A' || ch > 'Z') ch = getchar();
		if (ch == 'R') a[1].push_back(x);
		else if (ch == 'G') a[2].push_back(x);
		else a[3].push_back(x);
	}
	vector<int> res;
	for (int i = 1; i <= 3; i++) {
		sort(a[i].begin(), a[i].end());
		if (a[i].size() % 2 == 1) {
			res.push_back(i);
		}
	}
	if (res.empty()) {
		printf("0");
		return 0;
	}
	int u = res[0], v = res[1], w = 6 - u - v;
	int uv = calc(u, v);
	int uw = calc(u, w);
	int vw = calc(v, w);
	printf("%lld", min(uv, uw + vw));
	return 0;
}
```
- 感谢观看！留个赞吧~

---

