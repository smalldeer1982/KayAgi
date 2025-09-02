# [USACO24FEB] Maximizing Productivity B

## 题目描述

Farmer John 有 $N$（$1\le N\le 2\cdot 10^5$）个农场，编号为 $1$ 到 $N$。已知 FJ 会在时刻 $c_i$ 关闭农场 $i$。Bessie 在时刻 $S$ 起床，她希望在农场关闭前访问尽可能多的农场，从而最大限度地提高她这一天的生产力。她计划在时刻 $t_i+S$ 访问农场 $i$。Bessie 必须于严格早于 Farmer John 关闭农场的时刻抵达农场才能成功进行访问。

Bessie 有 $Q$（$1\le Q\le 2\cdot 10^5$）个询问。对于每个询问，她会给你两个整数 $S$ 和 $V$。对于每个询问，输出当 Bessie 在时刻 $S$ 起床是否可以访问至少 $V$ 个农场。

## 说明/提示

### 样例解释

对于第一个询问，Bessie 将在时间 $t=[9,7,8,8,13]$ 访问农场， 因此她在 FJ 关闭农场之前能准时访问到的只有农场 $4$。

对于第二个询问，Bessie 将无法准时访问到任何农场。

对于第三个询问，Bessie 将可以准时访问到农场 $3,4,5$。

对于第四个和第五个询问，Bessie 将能够准时访问除第一个农场之外的所有农场。

### 测试点性质

- 测试点 $2-4$：$N,Q\le 10^3$。
- 测试点 $5-9$：$c_i,t_i\le 20$。
- 测试点 $10-17$：没有额外限制。

## 样例 #1

### 输入

```
5 5
3 5 7 9 12
4 2 3 3 8
1 5
1 6
3 3
4 2
5 1```

### 输出

```
YES
NO
YES
YES
NO```

# 题解

## 作者：_Jocularly_ (赞：10)

## 题目分析
$c_{i}$ 表示关闭第 $i$ 个农场的时间，$t_{i}$ 表示到第 $i$ 个农场的初始时间，用 $late_{i}$ 要想在关闭前到达第 $i$ 个农场的最晚时间，此时我们只需要把 $late$ 数组从大到小排序即可，只要看第 $v$ 个是否能按时到达即可。因为数组有序，如果能到达，说明所有比他小的农场都可以到达。

## 注意
sort 函数实现的是数组从小到大排序，如果想要从大到小有两种实现方法，第一种是自己编写一个 cmp 函数；第二种方法，也是本篇用到的方法，利用 reverse 函数反转已经排完序，从小到大的数组，就可以实现从大到小，reverse 函数的使用方法和 sort 函数相同，具体请看代码。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std; 
int n,q;
int c[200005],t[200005];
int late[200005];
int main(){
	cin >> n >> q;
	for(int i=1;i<=n;i++){
		cin >> c[i];//关闭时间 
	}
	for(int i=1;i<=n;i++){
		cin >> t[i];//初始访问时间 
	}
	for(int i=1;i<=n;i++){
		late[i] = c[i] - t[i];//最晚到达时间 
	} 
	sort(late+1,late+1+n);//排序
	reverse(late+1,late+1+n);
	for(int i=1;i<=q;i++){
		int v,s;
		cin >> v >> s;
		if(s < late[v]) cout << "YES";//表示能够到达 
		else cout << "NO";
		cout << endl;
	} 
	return 0;
}
```

---

## 作者：OAer (赞：4)

### 思路
由题目可知，若 Bessie 可以访问农场 $i$，那么有 $t_i+S<c_i$。那么我们可以直接将最大的能满足的 $S$ 存在数组 $A$ 里，每次询问时，就找有多少个 $A_i\le S$。

看到数据规模时，果断二分。首先将 $A$ 从小到大排序（为了正常地二分），此时一个元素的位置表示 $S$ 小于等于这个元素时会错过的牧场数减 $1$。此时可以使用 `lower_bound`。若查找下来在数组 $A$ 的第 $p$ 个元素，最终就有 $N-(p-1)$ 个牧场 Bessie 可以拜访。

### 代码
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int c[200005],t[200005];
int TLE[200005],cnt[200005];	//此处使用TLE数组代替A数组
int n,q;
int main(){
	scanf("%d",&n);scanf("%d",&q);
	for(int i=1;i<=n;i++) scanf("%d",&c[i]);
	for(int i=1;i<=n;i++){
		scanf("%d",&t[i]);
		TLE[i]=c[i]-t[i]-1;	//最大限制的时间
	}
	sort(TLE+1,TLE+n+1);	//排序
	while(q--){
		int v;int s;
		scanf("%d %d",&v,&s);
		int l=0,r=n;
		int cnt=n-(lower_bound(TLE+1,TLE+n+1,s)-TLE-1);	//二分查找
		if(cnt>=v) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```
### 最后的忠告
`lower_bound` 的返回值是指针，记得减去 $A_0$ 的地址。

---

## 作者：卷王 (赞：4)

一道比较简单的二分题。

我们只需要求出 Bessie 想要到达农场 $i$ 最多能容忍的时间（即题目中的 $S$ 减去 $1$） $a_i$，然后把它从小到大排序，在每次询问里面二分即可。

考场代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
typedef long long ll;
typedef pair<int, int> pr;
#define up(l, r, i) for(int i = (l); i <= (r); i++)
#define down(r, l, i) for(int i = (r); i >= (l); i--)
const int mod = 1000000007;
const int base = 2333;
const double eps = 1e-6;

inline int read() {
	int x = 0, f = 1; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') f = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); }
	return x * f;
}

int n, m, k, Q, T, _, ans = 0;
int c[1000007];
int t[1000007];
int a[1000007];

signed main() {
	n = read(), Q = read();
	for(int i = 1; i <= n; i++) c[i] = read();
	for(int i = 1; i <= n; i++) t[i] = read(), a[i] = c[i] - t[i] - 1;
	sort(a + 1, a + n + 1);
//	for(int i = 1; i <= n; i++) cout << a[i] << " ";
//	cout << "\n";
	while(Q--) {
		int V = read(), S = read();
//		cout << "lower_bound:  " << (lower_bound(a + 1, a + n + 1, S) - a - 1) << "\n";
		int cnt = n - (lower_bound(a + 1, a + n + 1, S) - a - 1);
		if(cnt >= V) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：Liyunze123 (赞：3)

# 1.题目描述
农场 $i$ 会在 $c_i$ 时关闭。有人打算在 $S+t_i$ 时参观农场 $i$（$c_i$，$t_i$ 输入里会给），给出 $Q$ 个询问，每个询问把 $S$ 给你，问你能不能参观 $V$ 个农场。
# 2.题目思路
在 $c_i$ 时关闭农场 $i$，实际上最晚起床的时间就是 $c_i-t_i-1$。注意题目中说的必须严格早于关闭时间。

我们做个后缀和，$s_i$ 表示在 $i$ 起床能参观的农场数。那么：$s_i=s_{i+1}+g_i$，其中 $g_i$ 表示满足 $c_j-t_j-1=i$ 时的 $j$ 的个数。

判断在 $S$ 起床是否可以参观 $V$ 个农场的条件是 $V \ge s_S$。
# 3.代码加注释：
```
#include<bits/stdc++.h>
using namespace std;
int n,q,c[200010],t[200010],g[200010],o[1000010],k[1000010],p=1,s,v;//g数组是辅助数组，o数组才是题解中说的g数组，不要搞错了，c、t数组用来输入，k是计后缀和的
int main(){
    scanf("%d%d",&n,&q);
    for(int w=1;w<=n;w++)scanf("%d",&c[w]);
    for(int w=1;w<=n;w++)scanf("%d",&t[w]),g[w]=max(c[w]-t[w]-1,0),o[g[w]]++;//c[w]-t[w]-1<=0时无论如何都参观不了。
    for(int w=1000000;w;w--)k[w]=k[w+1]+o[w];//做后缀和
    for(int w=1;w<=q;w++){
        scanf("%d%d",&v,&s);
        if(k[s]>=v)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
```

---

## 作者：lun_hao (赞：3)

### 题目大意： 
[题目传送门](https://www.luogu.com.cn/problem/P10189)

给定 $N$ 个农场，编号为 $1$ 到 $N$，第 $i$ 农场会在时刻 $c_i$ 关闭，$Q$ 次询问，问在时刻 $t_i+S$ 访问的限制下能否访问**至少** $V$ 个农场。

数据范围：$1 \leq V \leq N \leq 2 \times 10^5$，$1 \leq Q \leq 2 \times 10^5$。
### 题目分析：  
每次要求的答案为：


$$ ans= \sum_{i}^{n} [S+t_i < c_i] $$


根据不等式的基本性质可将原式变形为：


$$ ans= \sum_{i}^{n} [c_i-t_i >S] $$


由于 $c_i$ 和 $t_i$ 的值在读入之后不会在变，故农场的前后顺序可以改变，可以考虑开一个结构体同时存 $c_i$ 和 $t_i$，按照 $c_i-t_i$ 的值从小到大排序，跑一次**二分**，$N-L$ 就是可以访问农场的个数，然后再跟 $V$ 比较即可。

时间复杂度：$O(Q \log N)$

### AC code：
稍微解释一下二分的差异：   
这里我选用了`L+1<R` 的二分循环条件，故左指针的初始值是 $0$，右指针的初始值为 $N+1$，当 $c_{mid}$ 的值不大于 $S$，就会让左指针 $L \gets mid$，反之就会让右指针 $R \gets mid$，最终结束时 $c_L$ 的值仍然不大于 $S$，故答案为 $L+1$ 到 $N$，答案为 $N-(L+1)+1=N-L$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int n,Q;
struct data
{
	int c,t;
}a[N];//结构体同时存c_i和t_i
bool cmp(data a,data b)
{
	return a.c<b.c;
}
signed main()
{
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++) scanf("%d",&a[i].c);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].t);
		a[i].c-=a[i].t;//预处理，提前处理好c_i-t_i的值
	}
	sort(a+1,a+1+n,cmp);//按c_i-t_i的值从小到大排序
	while(Q--)
	{
		int v,s;
		scanf("%d%d",&v,&s);
		int L=0,R=n+1;
		while(L+1<R)//二分
		{
			int mid=(L+R)>>1;
			if(a[mid].c<=s) L=mid;//如果访问第mid个农场的时间不比s大，就需要将左指针向右移
				else R=mid;//反之同理可得
		}
		if(v<=n-L) printf("YES\n");//答案放在左指针的右边一位，故答案为N-(L+1)+1=N-L
			else printf("NO\n");
	}
	return 0;
}
```

---

## 作者：xiaoshumiao (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/P10189)

如果我们直接预处理如果 Bessie 想去 $v$ 个农场需要多少时间，就可以在线 $\mathcal O(1)$ 回答了。

怎么预处理呢？

设 $b_i$ 代表 Bessie 要去第 $i$ 个农场最早什么时候起，则 $b_i=\max(0,a_i-t_i-1)$。

然后 $b_i$ 中的第 $v$ 大的数就是 Bessie 想去 $v$ 个农场最晚起床时间，排序后每次直接判断即可。
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=2e5+10;
int a[N],t[N],b[N];
bool cmp(int a,int b) {
  return a>b;
}
int main() {
  int n,q; scanf("%d %d",&n,&q);
  for(int i=1;i<=n;i++) scanf("%d",&a[i]);
  for(int i=1;i<=n;i++) scanf("%d",&t[i]);
  for(int i=1;i<=n;i++) b[i]=max(0,a[i]-t[i]-1);//计算 b
  sort(b+1,b+n+1,cmp);//排序，即预处理第 v 大
  for(int i=1;i<=q;i++) {
  	int v,s; scanf("%d %d",&v,&s);
  	puts(b[v]>=s?"YES":"NO");//如果 Bessie 在 <= bv 时刻起床就可以
  }
  return 0;
}
```

---

## 作者：yhylivedream (赞：1)

## 分析

发现对于 $c_i \le t_i$ 的农场一定是不行的，可以忽略不记。

我们把剩下的农场的 $c_i - t_i$ 用 $d$ 数组记录下来，如果 $S > d_i$ 那么这个农场就可以去到，所以我们将 $d$ 数组排序，发现答案具有单调性：如果当前农场可以去到，那么后面时间更充足的肯定能去到，所以每次询问二分第一个满足 $S > d_i$ 的位置，再判断即可。

## 代码


```
#include <bits/stdc++.h>
#define debug puts("Y")
#define int long long

using namespace std;
using PII = pair <int, int>;

const int N = 2 * 1e5 + 5;
int n, q, cnt, c[N], t[N], d[N];

signed main(){
	cin >> n >> q;
	for (int i = 1; i <= n; i ++) {
		cin >> c[i];
	} for (int i = 1; i <= n; i ++) {
		cin >> t[i];
		if (t[i] < c[i]) {
			d[++ cnt] = c[i] - t[i];
		}
	}
	sort (d + 1, d + cnt + 1);
	for (; q; q --) {
		int v, s;
		cin >> v >> s;
		int pos = upper_bound(d + 1, d + cnt + 1, s) - d;//二分
		cout << (cnt - pos + 1 >= v ? "YES" : "NO") << "\n";//判断能去到的农场是否大于等于v
	}
	return 0;
}

```

---

## 作者：__AFO__ (赞：1)

## 题解
[题目传送门](https://www.luogu.com.cn/problem/P10189)

这道题把每一个农场至少要在几点起床才能拜访记录下来，再排序，用二分找到第一个大于等于要求的数值，从这个数起在排序中往后数个数，只要大于等于要求数即可。


代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,T,w,h,f,v,s,l,aa[200005];
struct nn{
	int c,t;//结构体定义 
}a[200005];
int main(){
	cin>>n>>m;//输入 
	for(int i=1;i<=n;i++) cin>>a[i].c;
	for(int i=1;i<=n;i++){
		cin>>a[i].t;
		aa[i]=a[i].c-1-a[i].t;//算出第i个农场至少要在几点起床才行 
	}
	aa[n+1]=0x3f3f3f3f;
	sort(aa+1,aa+1+n);//将至少起床时间排序 
    while(m--){
    	cin>>v>>s;
        l=lower_bound(aa+1,aa+1+n,s)-aa;//找到第一个大于等于接近他的 
        if(n-l+1>=v){//拜访的农场是否大于要求 
        	cout<<"YES"<<endl;
		}else{
			cout<<"NO"<<endl;
		}
	}
    return 0;
}
```

### END


---

## 作者：wht_1218 (赞：1)



对于此题，我们可以求出每个农场**最小**的 $S$，假设是 $a$，得 $a_i=c_i-t_i$，**不要求绝对值**！

由于题目没让求出每个农场的编号，我们可以提前**从大到小**排好序，想让 Bessie 至少去 $V$ 个农场，就一定要去第 $V$ 个农场，只要判断 `s>=a[i]` 即可。

坑点：

注意 $ans$ 开 `long long`。~~题面也提醒了~~

```cpp
#include<bits/stdc++.h> 
using namespace std;  
int a[200007],b[200007],c[200007];
long long sum[200005];
int main() {  
    int n,q;
    cin>>n>>q;
    int cnt=n;
    for(int i=1;i<=n;++i){
    	scanf("%d",&a[i]);
	}for(int i=1;i<=n;++i){
    	scanf("%d",&b[i]);
    	c[i]=a[i]-b[i];
	}sort(c+1,c+n+1,greater<int>());
	while(q--){
		int v;
		long long s;
		scanf("%d%lld",&v,&s);
		if(v>cnt)printf("NO\n");//以防万一
		else{
			if(s>=c[v])printf("NO\n");
			else printf("YES\n");
		}
	}
    return 0;  
}
```


---

## 作者：yuyc (赞：1)

## 题意
给定两个长度为 $N$ 的数列 $s,t$。$Q$ 次询问，每次给出两个正整数  $V,S$，令 $res = \sum\limits_{i=1}^{n} [t_i+S < s_i]$，试判断 $res$ 与 $V$ 的大小关系

## 解析


注意到 $S$ 越大，$res$ 越小，故考虑离线做法，将询问按 $S$ 从小到大排序

可以发现，由于是判断大小关系，所以我们只关心 $t_i$ 与 $s_i$ 的差值，不妨将其求出然后排序，以从小到大排序 $s_i - t_i$ 为例，可以让一个指针 $p$ 指向从左到右第一个满足 $s_i-t_i-S > 0$ 的 $i$，$n-p+1$ 即为答案。

由于 $S$ 越来越大，$s_i-t_i$ 越来越大，故可以保证 $p$ 只会往右移，移指针的时间复杂度为 $O(n)$，总时间复杂度为 $O(n\log n)$

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int c[N],t[N],dif[N],ans[N];
struct Q{
	int pos,v,s;
}qry[N];
bool cmp(Q a,Q b){
	return a.s < b.s;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
	int n,q;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	for(int i=1;i<=n;i++){
		cin>>t[i];
		dif[i] = c[i] - t[i];
	}
	for(int i=1;i<=q;i++){
		cin>>qry[i].v>>qry[i].s;
		qry[i].pos = i;
	}
	sort(dif + 1,dif + 1 + n);
	sort(qry + 1,qry + 1 + q,cmp);
	int p = 1;
	for(int i=1;i<=q;i++){
		int v = qry[i].v,s = qry[i].s;
		while(p <= n && dif[p] - s <= 0) p++;
		ans[qry[i].pos] = q - p + 1 >= v;
	}
	for(int i=1;i<=q;i++) cout<<(ans[i] ? "YES" : "NO")<<'\n';
    return 0;
}
```



---

## 作者：Ivan422 (赞：0)

# USACO 2月 铜组 T3

题目大意：每个农场可以在 $t_i+S$ 到 $c_i$ 时刻访问，求可访问数是否不小于 $V$ 。

思路：我们可以计算出每个农场可用时间长度 $c_i-t_i$ ，记做 $d_i$。而每次起床相当于使用了 $S$ 的时间，一旦 $d_i>S$ ，即满足 $c_i$ 时刻前访问，就满足条件了。这时我们对 $d_i$ 进行排序，一旦找到第一个 $d_i>S$ 的值，就会有 $n-i+1$ 个可以访问的农场，而找到这个值可以使用二分。在这里我使用的是 `upper_bound`，可以找到第一个大于 $S$ 的值。

代码：
```cpp
#include<bits/stdc++.h> 
using namespace std;
#define int long long
const int N=2e5+10;
int n,q,v,s,t[N],c[N],d[N],ans;
bool cmp(int x,int y){return x>y;}
signed main(){
	cin>>n>>q;
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++)cin>>t[i];
	for(int i=1;i<=n;i++)d[i]=c[i]-t[i]; // 计算 d[i]
	sort(d+1,d+n+1); // 从小到大排序
	while(q--){
		cin>>v>>s;
		ans=n-(upper_bound(d+1,d+n+1,s)-d)+1; // 求出可以访问的农场数
		if(ans>=v)printf("YES\n"); // 判断是否满足条件
		else printf("NO\n");
	}
	return 0;
}
```


---

## 作者：2021zjhs005 (赞：0)

[洛谷题目传送门](https://www.luogu.com.cn/problem/P10189)。

Despriction
------------

### 背景题意简述：

给定 $n$ 个农场关闭的时间 $c_i$，以及 Bessie 打算醒来后 $t_i$ 个时间单位参观第 $i$ 个农场，参观一个农场需要 $0$ 时间单位（设它参观农场的时间为 $T$，则参观时间为 $T\sim T$，也就是用在时间 $T$ 开始参观，并参观完毕）。

每次给你 $Q$ 个 $v$ 和 $s$，分别表示 Bessie 想要参观的农场数以及它醒来的时间。如果能参观第 $i$ 个农场，那么 $s+t_i$ 必须**严格小于** $v$。如果**最多**能参观的农场数达到 $v$，输出一行 `YES`，否则输出一行 `NO`。


### 形式化题意简述：

给定 $2\cdot n$ 个数，前 $n$ 个第 $i$ 个为 $c_i$，后 $n$ 个第 $i$ 个为 $t_i$。

现给定 $Q$ 个询问，每个询问有整数 $v$ 和 $s$。

设满足 $s+t_i < c_i$ 的有 $sum$ 个。

- 如果 $sum\ge v$，输出一行 `YES`。

- 如果 $sum<v$，输出一行 `NO`。


注意：`YES` 和 `NO` 都是**大写**！


Solution
------------

### 解决 Subtask $1$：

将式子 $s+t_i < c_i$ 中的 $t_i$ 移到右边，可得 $s < c_i - t_i$。

- 读入 $c_i$，$t_i$ 后将 $c_i$ 改为 $c_i-t_i$。

- 随后，对于每个 $v$ 和 $s$，从 $n$ 个 $c_i$ 里找 $s<c_i$ 的数的个数。

- 最后分情况输出即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define sc scanf
#define pr printf
#define stg string
#define vct vector

inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

const int N=2e5+1;
int n,Q,v,s,c[N];

signed main(){
    n=read();Q=read();
    rep(i,1,n) c[i]=read();
    rep(i,1,n) c[i]-=read();//这里不读入 t[i]，直接减。
    while(Q--){
        v=read();s=read();
        int sum=0;
        rep(i,1,n)
            if(s<c[i]) sum++;//找满足条件的数的个数。
        if(sum>=v) pr("Yes\n");
        else pr("No\n");
    }
    return 0;
}
```

时间复杂度为 $\mathcal O(Qn)$，妥妥的 `T`。



------------

### 解决 Subtask $2$：

观察 $\texttt{Subtask}\ 2$ 的数据范围，$1\le c_i,t_i\le 20$，直接用一个桶即可（如果有 $c_i-t_i\leq 0$，那么这个 $c_i-t_i$ 就不用桶了），最坏时间复杂度为 $\mathcal O(Q)$。

代码实现很简单，就不展示了（~~是你懒得打~~）。





------------
### 解决 Subtask $1,2,3$：

首先还是式子 $s<c_i-t_i$，**处理好 $c$ 数组后**即为 $s<c_i$。

这就是从一个序列里找比 $s < c_i$ 的数的个数。

本蒟蒻第一思路是树状数组（做多了），但是一想，铜组不会考这么难。

于是，本蒟蒻又想到了——**二分**！

我们的目的是找到

- 首先将 $c$ 数组处理好，然后排序（**从大到小**更容易实现）。这是我们的目的是找到最后一个 $c_i > s$，那么对于醒来时间为 $s$ 的贡献为 $i$。


下面是对于每一组数据的步骤：
- 二分：

  - 初始化 $l\gets1$，$r\gets n$。
  
     - 当 $l\le r$，产生 $mid = \lfloor \frac{l+r}{2}\rfloor$。
     
     - 若 $c_{mid}\le s$，说明农场已经关闭了，向左查找，$r\gets mid-1$。
     
     - 若 $c_{mid}>s$，说明农场还开支，向右查找，$l\gets mid+1$，并且记录答案 $ans$ 为 $mid$。
     
- 最后分情况讨论即可。
     
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
#define rrep(i,x,y) for(int i=x;i>=y;i--)
#define sc scanf
#define pr printf
#define stg string
#define vct vector

inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

const int N=2e5+1;
int n,Q,v,s,l,r,ans,c[N];

inline bool cmp(int s1,int s2){
    return s1>s2;
}

signed main(){
    n=read();Q=read();
    rep(i,1,n) c[i]=read();
    rep(i,1,n) c[i]-=read();
    sort(c+1,c+1+n,cmp);//排序。
    while(Q--){
        v=read();s=read();
        l=1;r=n;ans=0;
        while(l<=r){//二分。
            int mid=(l+r) >> 1;
            if(c[mid]<=s) r=mid-1;
            else{
                ans=mid;
                l=mid+1;
            }
        }
        if(ans>=v) pr("YES\n");
        else pr("NO\n");
    }
    return 0;
}
```

---

