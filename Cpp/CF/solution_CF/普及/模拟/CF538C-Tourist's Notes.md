# Tourist's Notes

## 题目描述

一位旅行者沿着山脉远足，一共 $n$ 天，每天他都记下来这一天他所在的海拔高度。任意两天所在的海拔高度之差不会超过 $1$。形式化来说，令第 $i$ 天的海拔高度为 $h_i$,则 $h_i-h_{i-1}| \leq 1 $。

几十年后，旅行者回忆这段时光时发现他丢失了一些当时的日记，他现在只有 $m$ 天高度的记录。

现在这位旅行者想知道，根据残存的 $m$ 天海拔记录，他当年最高可能达到过多高的海拔。

## 样例 #1

### 输入

```
8 2
2 0
7 0
```

### 输出

```
2
```

## 样例 #2

### 输入

```
8 3
2 0
7 0
8 3
```

### 输出

```
IMPOSSIBLE
```

# 题解

## 作者：wanggk (赞：5)

### 一些废话
下午学校停课打膜你赛的一道题，然而还调了好久才过大样例……

难度不高，主要考查思维上和细节上的实现，建议评黄或者评绿。

由于语文不好，表述不清楚的地方可以评论留言。

### 题意
有一个长度为 $n$ 的数列 $a$ 满足对于 $\forall 1 \leq i \leq n-1$，$\left\vert h_i - h_{i+1} \right\vert \leq 1$。

现已知数列中的 $m$ 个数。输入 $m$ 行，每行两个数，分别是在 $a$ 序列中的下标和数值。保证给出的 $m$ 个下标严格单调递增。

构造序列中剩余的数，最大化序列中的最大值。输出这个最大值。

### 题解
我们关注到题目条件中，相邻两数之差的绝对值不能超过 $1$，而且一些位置上的数是固定的。

现在有 $m$ 个固定位置，将整个序列分为 $m+1$ 段。

对于第 $1$ 段和最后一段，需要特判。显然，最优策略就是使 $a[1]$ 到 $a[d_1]$ 单调下降，使 $a[d_m]$ 到 $a[n]$ 单调递增。第一段和第二段最大值分别为 $a[1]$ 和 $a[n]$ ，更新答案。

另外对于中间段，相邻的两个固定位置 $i$ 和 $j$，考虑一个位置 $k$，使得：

- $i \leq k \leq j$
- 从 $a[i]$ 到 $a[k]$ 单调不下降
- 从 $a[k]$ 到 $a[j]$ 单调不上升
- 相邻两数之差的绝对值不超过 $1$

即，在 $i$ 和 $j$ 之中找一个峰顶 $k$，$a[k]$ 为已固定位置 $i$ 和 $j$ 中可以达到的最大值，更新答案。

最终的答案就是每一段答案的最大值。

一些细节：如果相邻两个固定位置相差值过大，构造序列时无法达到某一个 $k$，则判定为“不可能”。

### 代码
学校膜你赛的考场代码，含注释，码风丑陋：
```cpp
int n,m;
int res=0;
struct node{
	int h,hd;
}a[maxm];
signed main()
{
    scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&a[i].h,&a[i].hd);
	res=a[1].hd+(a[1].h-1);//特判第一段
	for(int i=2;i<=m;i++)
	{
		int dd=a[i].h-a[i-1].h-1;//日期差
		//1.先把矮的高度变为高的那个，花费的日期差为del
		int tmp=max(a[i].hd,a[i-1].hd);
		int del=tmp-a[i].hd+tmp-a[i-1].hd;
		//2.如果del不够变成相同的，则说明高度差过大（因为构造时相邻只能差1）
		if(a[i].h-a[i-1].h<abs(a[i].hd-a[i-1].hd)){ printf("IMPOSSIBLE\n"); return 0; }
		//3.多出来的向内扩展，形成"峰顶"
		dd-=del; res=max(res,tmp+(dd+1)/2);
	}
	res=max(res,a[m].hd+(n-a[m].h));//特判最后一段
	printf("%d\n",res); return 0;
}
```

---

## 作者：OIerJiang_1017 (赞：2)

## [CF528C 题目传送门](https://www.luogu.com.cn/problem/CF538C)

## 题目大意
一个人出去爬山 $n$ 天，第 $i$ 天所在地方的高度为 $h$，相邻两天的高度之差不超过 $1$。给出部分天数的高度，问这个人在这 $n$ 天中，所到地方的最高高度是多少？如果根据给出的数据不符合题意描述，即出现相邻两天的高度之差超过 $1$，输出 `IMPOSSIBLE`。

## 解决思路
用一个**结构体**记录天当天高度 $h$ 和当天天数 $d$。设 $dd$ 为相隔的天数，$hh$ 为 $dd$ 天相隔的高度差
- 若 $hh>dd$，即相隔的高度比天数大（相邻两天的高度差不超过 $1$），则不符合题意，直接输出 `IMPOSSIBLE`；
- 否则就符合要求，求出相隔天数中的最大海拔高度就为 `ans = max(ans, a[i].h + (hh + dd) / 2)`。

最终 $ans$ 即为答案。

## 代码展示
```cpp
#include <iostream>
using namespace std;

const int N = 1e5 + 10;
int n, m, ans;
struct node
{
	int d, h;
	//d记录天数
	//h记录高度 
}a[N];

int main()
{
	scanf("%d%d", &n, &m);//建议scanf,更快
    for(int i = 1; i <= m; i++)
		scanf("%d%d", &a[i].d, &a[i].h);
    ans = a[1].h + a[1].d - 1;
    for(int i = 1; i < m; i++)
    {
    	int dd = a[i + 1].d - a[i].d;//相隔天数
        int hh = a[i + 1].h - a[i].h;//dd天相隔的高度 
        if(abs(hh) > dd) 
        {//相隔的高度比天数大
    	    printf("IMPOSSIBLE\n");
            return 0;//建议printf,更快
        }
        else ans = max(ans, a[i].h + (hh + dd) / 2);
    }
    ans = max(ans, a[m].h + n - a[m].d);
    printf("%d\n", ans);
	return 0;//换行是个好习惯 
}
```

---

## 作者：_Deer_Peach_ (赞：2)

题意：

一个旅行者去远足，一共 $n$ 天，每一天都会记录当天的日期 $d_i$ 和到达的海拔高度 $h_i$，相邻两天的到达的海拔高度相差不超过 $1$。几十年后，旅行者只有 $m$ 天的记录。求当年最高可能达到过多高的海拔。

思路：

先将所有的日期从小到大排序，然后先求出第一天可能到达的最高高度和最后一天可能到达的最高高度。接着遍历这 $m$ 天的记录，计算每两天之间最高可能达到的最高高度，并判断相差是否不超过 $1$，如果是，则记录下最大的高度。否则直接输出 `IMPOSSIBLE`。

那怎么判断记录是否冲突呢？因为过了一天只能向上或向下走一海拔的高度，所以如果两次记录之间的日期间隔小于了高度差，那么记录是不存在冲突的。否则就是存在冲突的。

那怎么计算两次记录间可能到达的最高的高度呢？如果先不管后一天的记录，那么从前一天开始后面每一天都可以比前一天的高度高 $1$，但是有了后一天的记录，所以到最高的高度后要往低处走。$d_i-d_{i-1}-1$ 是从第 $d_{i-1}$ 天到第 $d_i$ 天中间的日期也是走的距离，$\max(h_i,h_{i-1})-\min(h_i,h_{i-1})$ 是记录的两天的高度差，先让一共走的减去高度差（可以理解成使两天的高度走成一致），这样中间几天就先向上走再向下走，且向上走的距离与向下走的距离相同，除以 $2$ 加上 $\max(h_i,h_{i-1})$，再减去 $1$ 就可以算出可能到达的最高高度。计算公式： $\frac{(d_i-d_{i-1}-1)-[\max(h_i,h_{i-1})-\min(h_i,h_{i-1})+1]}{2} + \max(h_i,h_{i-1})$。

代码：
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m;struct node{
	int date,height;//日期，海拔高度
}a[100001];int ans;bool cmp(node x,node y){return x.date<y.date;}//按时间排序
signed main(){
	cin>>n>>m;for(int i=1;i<=m;i++){//输入
		cin>>a[i].date>>a[i].height;
	}sort(a+1,a+m+1,cmp);ans=max(a[1].date-1+a[1].height,n-a[m].date+a[m].height);for(int i=2;i<=m;i++){//先求出第一天和最后一天可能到达的最高高度，然后遍历记录的m天
		if(a[i].height-a[i-1].height>a[i].date-a[i-1].date){//记录存在冲突
			cout<<"IMPOSSIBLE";return 0;//输出完直接结束
		}else{//不存在冲突
			ans=max(ans,((a[i].date-a[i-1].date-1)-abs(a[i].height-a[i-1].height)+1)/2+max(a[i].height,a[i-1].height));//比较大小
		}
	}cout<<ans;return 0;
}
```

---

## 作者：BYWYR (赞：2)

## $\texttt{Solution}$

用一个结构体数组记录天数和当天的海拔高度。

设 $\text{d}$ 为相隔的天数，$\text{h}$ 为相隔的海拔差。

- 若 $\text{h} > \text{d}$，则就是矛盾，输出 ```IMPOSSIBLE```；

- 如果不矛盾，相隔天数中的最大海拔高度就为

$$ ans=\max(ans,\max(a_i.h,a_{i-1}.h)+(a_i.day-a_{i-1}.day-h)/2)$$

最后 $\text{ans}$ 即为答案。

## $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct Day{
	ll day,h;
};
Day a[100005];
int n,m;
ll ans;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%lld%lld",&a[i].day,&a[i].h);
	}
	ans=a[1].h+a[1].day-1;//初始化为第1个知道的
	for(int i=2;i<=m;i++){
		int _d=a[i].day-a[i-1].day;//相隔天数
		int _h=abs(a[i].h-a[i-1].h);//相隔海拔差
		if(_h>_d){//矛盾
			printf("IMPOSSIBLE");
			return 0;
		}
		int sh=max(a[i].h,a[i-1].h);//原基础的最大高度
		ans=max(ans,sh+(a[i].day-a[i-1].day-_h)/2);
	}
	ans=max(ans,n-a[m].day+a[m].h);
	printf("%lld",ans);
	return 0;
}
```



---

## 作者：xyzqwq (赞：2)

# 一些胡言乱语

校模拟赛出了这道题，考场上推出来式子但是没有特判首尾，于是挂了 30。

另外，这仿佛是我在洛谷的第一篇题解。

# 题意

简化一下题意，实际上就是给定 $n$ 个点，由这 $n$ 个点引出斜率为 $\pm 1$ 的直线，求所有交点的最大值。

以样例 1 为例：

```
8 2
2 0
7 0
```

如果按照刚刚写的理解方式，画成一个平面就是：

![](https://cdn.luogu.com.cn/upload/image_hosting/muuv6yzd.png)


# 推式子

肯定是要循环写的。

设一个 $A(d_i,h_i),B(d_{i+1},h_{i+1})$。

待定系数法，先设穿过 A 的直线为 $y_1=x_1+b_1$，求出来 $b_1=h_i-d_i$。

再设穿过 $B$ 的直线为 $y_2=-x_2+b_2$，求出来 $b_2=d_{i+1}+h_{i+1}$。

然后计算两直线交点，即 $-x+d_{i+1}+h_{i+1}=x+h_i-d_i$。

求出来 $x=\frac{d_{i+1}+h_{i+1}+d_i-h_i}{2}$。

所以此时得到的最大值就是 $\frac{d_{i+1}+h_{i+1}+d_i-h_i}{2}+h_i-d_i$。

循环的时候去 $\max$ 即可。

本题还要求判断无解，那么什么时候无解呢？就是两个点连成一条直线的斜率大于 1 的时候，即 $|\frac{h_{i+1}-h_i}{d_{i+1}-d_i}|>1$ 的情况。

另外首尾还需要特判一下。

# AC 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m;
struct node{
	int d,h;
}a[N];
int ans=-1;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d%d",&a[i].d,&a[i].h);
	ans=a[1].d+a[1].h-1;//首特判
	for(int i=1;i<m;i++){
		if(abs(a[i].h-a[i+1].h)>a[i+1].d-a[i].d){//判断无解
			printf("IMPOSSIBLE");
			return 0;
		}
		ans=max(ans,max(a[i].h,a[i+1].h)+((a[i+1].d-a[i].d)-abs(a[i].h-a[i+1].h))/2);
	}
	ans=max(ans,a[m].h+n-a[m].d);//尾特判
	printf("%d",ans);
}
```

---

## 作者：pyz51 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF538C)

[CF传送门](https://codeforces.com/problemset/problem/538/C)

[AC记录](https://codeforces.com/contest/538/submission/292769248)
# 题意简述
有 $n$ 个数，现给定其中的 $m$ 个数的位置与数值，规定后一个数与前一个数之差小于等于 $1$，求这 $n$ 个数中最大的数最大可能为多少。
# 题解
根据题目，我们每次处理相邻两个给定的数，如下表：
![](https://cdn.luogu.com.cn/upload/image_hosting/xkyq3vt1.png)

1. 将较少的一端向另一端移并不断 $+1$，直至与另一端数量相等。
![](https://cdn.luogu.com.cn/upload/image_hosting/su0xrmqo.png)  
**此时可能会出现一端移到另一端仍少的情况，直接输出 IMPOSSIBLE。**

2. 两边同时向中间靠拢，不断 $+1$，直至两端相遇。
   ![](https://cdn.luogu.com.cn/upload/image_hosting/rp16bmqm.png)  
   **此时，这一段的答案即为中间的最大值。**

3. 最后处理完每一段，再考虑两端的 $1$ 和 $n$ 位置，显然往两侧不断 $+1$。
   ![](https://cdn.luogu.com.cn/upload/image_hosting/xctj5shd.png)
   最后就可以得到答案是 $5$。

其中，第一步和第二步可以用 $O(1)$ 的复杂度计算出来，所以最终仅需 $O(m)$。
# AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int M=2e5+5;
const int inf=2147483647;
const long long lof=9223372036854775807;
#define ll long long
#define bug cout<<"...here...\n"
#define mem(a,b) memset(a,b,sizeof a)
#define CLOSE ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define F first
#define S second
inline ll read(){
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
int Stack[105];
inline void print(ll x){
    int cnt=0;
    if(x<0) putchar('-'),x=-x;
    while(x){
    	Stack[++cnt]=x%10;
    	x/=10;
    }
    while(cnt--) putchar((char)Stack[cnt+1]+'0');
    return;
}
int n,m;
pair<int,int> a[N]; 
int main(){
    CLOSE
    cin>>m>>n;
    for(int i=1;i<=n;i++) cin>>a[i].F>>a[i].S;
    sort(a+1,a+1+n);
    int maxx=-inf;
    for(int i=1;i<=n+1;i++){
    	if(i==1) maxx=max(maxx,a[i].S+a[i].F-1);
    	else if(i==n+1) maxx=max(maxx,a[i-1].S+m-a[i-1].F);
        //分别处理第一天和最后一天
    	else{
    		if(a[i].F-a[i-1].F<abs(a[i].S-a[i-1].S)){//若不合理，输出IMPOSSIBLE
    			cout<<"IMPOSSIBLE";
    			return 0;
			}
			int l=a[i].F-a[i-1].F,num=abs(a[i].S-a[i-1].S);
			l-=num;
			maxx=max(maxx,max(a[i].S+l/2,a[i-1].S+l/2));//算出这一段的最大值，与答案取最大
		}
	}
	cout<<maxx;
    return 0;
}
```

---

## 作者：Undefined_Shawn (赞：1)

这道题思路很明确，就是用结构体（pair 也行）存储天和海拔高度，根据两天的信息确定这两天之间最高可以到多高，然后取最大值即可。

注意！本题有个坑点，就是要计算头和尾，即从第 $1$ 天到第一次输入的天，和从第最后一次输入的天到第 $n$ 天，这两段时间可千万不要忘记！

好了，思路就这么多，简单明了，下面是代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> PII;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<PII> a(m);
  for (int i = 0; i < m; i++) cin >> a[i].first >> a[i].second;
  sort(a.begin(), a.end());
  int mx = max(a[0].second + a[0].first - 1, a.back().second + (n - a.back().first));
  for (int i = 1; i < m; i++) {
    int h = abs(a[i].second - a[i - 1].second), d = a[i].first - a[i - 1].first;
    if (h > d) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
    mx = max(mx, max(a[i].second, a[i - 1].second) + (d - h) / 2);
  }
  cout << mx;
  return 0;
}
```

---

## 作者：ChrisWangZi (赞：1)

# CF538C Tourist's Notes 题解

## [题目传送门](https://www.luogu.com.cn/problem/CF538C)

## 题意简述

给定 $n$ 个数，但只知道 $m$ 个数及其下标。已知相邻两个数的差不大于 $1$，求出数组的最大值最大为多少。

## 思路

结构体存储，求出两个已知数之间的最大值的最大值。

有一些特判：

- 已知数也要求一遍最大值；

- 两端的最大值。

我们用两张图来说明如何求出两个已知数之间的最大值。

（样例 1）
![](https://cdn.luogu.com.cn/upload/image_hosting/y2n3jqvu.png)
（样例 2）
![](https://cdn.luogu.com.cn/upload/image_hosting/vm24tb3f.png)

## 代码

```cpp
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
struct er{
	int d,h;
}a[100005];
operator <(const er& _X,const er& _Y){
	return _X.d<_Y.d;
}
int main(){
	int n,m;
	cin>>m>>n;
	int maxn=0;
	for(int i=1;i<=n;i++){
		cin>>a[i].d>>a[i].h;
		maxn=max(maxn,a[i].h);
	}
	maxn=max(maxn,max(a[1].h+a[1].d-1,a[n].h+m-a[n].d));
	sort(a+1,a+1+n);
	for(int i=1;i<=n-1;i++){
		int c=abs(a[i].h-a[i+1].h);
		int e=a[i+1].d-a[i].d;
		if(c>e){
			cout<<"IMPOSSIBLE";
			return 0;
		}
		e-=c;
		maxn=max(maxn,max(a[i].h,a[i+1].h)+e/2);
	}
	cout<<maxn;
	return 0;
}
```

---

## 作者：zby0501_ (赞：0)

## 思路：
这道题题意很明确，用 pair 把天数与海拔存下来，判断两个记录之间能达到的最大海拔是多少最后输出答案即可。

要注意一下，第 $1$ 天到第一次输入的那一天和最后一次输入到结束的那些天也要计入答案。
## 代码
```
#include <bits/stdc++.h>
using namespace std;
int n,m;
int main() {
	cin>>n>>m;
	vector<pair<int,int> >a(m);
	for(int i=0;i<m;++i) cin>>a[i].first>>a[i].second;
	sort(a.begin(),a.end());
	int mx=max(a[0].second+a[0].first-1,a.back().second+(n-a.back().first));
	for(int i=1;i<m;++i){
		int h=abs(a[i].second-a[i-1].second),d=a[i].first-a[i-1].first;
		if(h>d){
			cout<<"IMPOSSIBLE\n";
			return 0;
		} 
		mx=max(mx,max(a[i].second,a[i-1].second)+(d-h)/2);
	}
	cout<<mx<<endl;
	return 0;
}

```

---

## 作者：lin_A_chu_K_fan (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF538C)
# 题意
给定一个 $n$ 个元素的序列 $a$，满足对于 $2 \le i \le n$，$|a_i -a_{i-1}| \le 1$。

现在给你 $a$ 中的 $m$ 个数。求 $a$ 中最大值的最大值是多少。
# 思路
首先明确，要分别处理相邻两个已知数之间的最大值。

 1. 然后对于每两个相邻的数，从较小的一段向另一端移动并每次加 $1$，两个数相等为止（**如果区间所有点都被填充还没有任何相等，直接输出 `IMPOSSIBLE` 结束**）。
 2. 两边一起向中间靠拢，相遇为止。
 3. 然后第一个点往前扩展，最后一个点往后扩展，直至填满。
 4. 最后遍历求最大值即为答案。

思路很简单，代码就不放了，求关~

---

## 作者：Lovely_Elaina (赞：0)

很一眼，但是很容易出错。

[更好的翻译。](https://www.luogu.com.cn/discuss/1008945)

## $\texttt{Solution}$

先判断合法问题，通过模拟易得如果 $|h_i-h_{i-1}|>d_i-d_{i-1}$ 则一定不存在合法方案，否则有至少一种合法的方案。

然后就开始贪心，因为前后不能相差一，所以优先将小的数递增到和大的数一样大，然后一同往中间递增。

```data
7 2
1 3
7 4 
```

例如对于上面这组数据，不妨先令 $h_2=h_7=4$，然后往中间递增赋值：

1. $h_3=h_6=5$；
2. $h_4=h_5=6$。

此时得到一个合法的构造方案使得 $\max h_i$ 最大，易证没有更优的构造方案。

然后通过模拟得到规律推出式子。

## $\texttt{Code}$

```cpp
#include <bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

int n,m,ans;
int ld,lh,d,h;

inline int _abs(int x){
    return (x>=0?x:-x);
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m >> ld >> lh;
    
    ans = lh+ld-1;
    d = ld,h = lh;
    
    for(int i = 1; i < m; i++){
        cin >> d >> h;
        
        if(_abs(h-lh) > d-ld){
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
        
        int p = d-ld-1-_abs(h-lh);
        ans = max(ans,max(h,lh)+((p+1)>>1));
        
        ld = d,lh = h;
    }
    
    ans = max(ans,h+n-d);
    cout << ans << endl;
    return 0;
}
```

## $\texttt{Warning}$

- 请注意最左侧和最右侧空域；
- 请注意 $m=1$ 的数据。

---

