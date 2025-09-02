# Divan and a New Project

## 题目描述

有 $n + 1$ 座的建筑，编号从 $0\sim n$。

有一个人从编号为 $0$ 的建筑出发， 分别要去编号为 $i$ 的建筑 $a_i$ 次。

设编号为 $i$ 的建筑坐标为 $x_i$， 这个人往返编号为 $i$ 的建筑一趟花费的时间为 $2 \times|x_i - x_0|$ 。

求如何安排这 $n + 1$ 座建筑的坐标， 使这个人在路上花费的总时间最小。

## 说明/提示

对于 $100\%$ 的数据，$1 \le t \le 10^3$，$1 \le n \le 2 \cdot 10^5$，$\sum n \le 2 \cdot 10^5$，$0 \le a_i \le 10^6$，$-10^6 \le x_i \le 10^6$。

## 样例 #1

### 输入

```
4
3
1 2 3
5
3 8 10 6 1
5
1 1 1 1 1
1
0```

### 输出

```
14
2 4 1 3
78
1 -1 0 2 3 4
18
3 6 1 5 2 4
0
1 2```

# 题解

## 作者：Otue (赞：3)

## 具体思路
走完第 $i$ 个建筑的 $a_i$ 次花费 $2\times |x_i-x_0|\times a_i$ 时间。

每一个 $a_i$ 已经固定，想要时间最小，则必须让 $|x_i-x_0|$ 最小。

**对于比较大的 $a_i$ ，就给他分配一个比较小的 $|x_i-x_0|$ ，这就是此题的贪心策略。**

---

**不妨设 $x_0$ 为 $0$**，最大的 $a_i$ 对应的 $x_i$ 就应该为 $1$ ,次大的 $a_i$ 对应的 $x_i$ 就为 $-1$。（注意坐标可以为负数）

依次这样下去，$1,-1,2,-2,3,-3...$

---

模拟一下题目样例
```c++
5
1 2 3 4 5    (此处为编号）
3 8 10 6 1
```
从大到小排序之后：
```c++
3 2 4 1 5    (此处为编号）
10 8 6 3 1
```
$10$ 分配 $1$ ，$8$ 分配 $-1$ ......

则分配下来长这样：

```c++
3 2 4 1 5    (此处为编号）
10 8 6 3 1
1 -1 2 -2 3    (此处为分配的坐标）
```

编号为 $3$ 的分配为 $1$，编号为 $2$ 的分配为 $-1$ ......

当然还要加上编号为 $0$ 的坐标为 $0$！！

最终坐标变成这样：
```c++
0 1 2 3 4 5     (此处为编号）
0 -2 -1 1 2 3    (此处为分配的坐标）
```

知道了坐标，算答案就很简单了。

## 赛时代码
```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
int T;
int n;
struct stu{
	int x,id;     //id是编号
}ed[200005];
int a[200005],ans;
bool cmp(stu x,stu y){  //从大到小排序
	return x.x>y.x;
}
signed main(){
	cin>>T;
	while(T--){
		ans=0;
		memset(a,0,sizeof a);
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>ed[i].x;
			ed[i].id=i;
		}
		a[1]=0;     //不妨他总部为0，即x0
		sort(ed+1,ed+n+1,cmp);
		int tmp=1;
		for(int i=1;i<=n;i++){
			ans+=2*abs(tmp)*ed[i].x; //算答案
			a[ed[i].id]=tmp;
			if(tmp>0){//以下在模拟1,-1,2,-2,3....的过程
				if(i%2==1) tmp=-tmp;
				else if(i%2==0) tmp++;
			}
			else if(tmp<0){
				if(i%2==1) tmp=-tmp;
				else if(i%2==0) tmp--;
			}
			
		}
		cout<<ans<<endl;
		for(int i=0;i<=n;i++) cout<<a[i]<<' ';
		puts("");
	}
}
```

---

## 作者：MeowScore (赞：2)

我们把总部的坐标定为 $0$ 方便去做。

显然按照访问次数降序排序，次数越多的建筑应该越靠近总部。排序后枚举建筑，在总部两侧交替放置即可。

记得开 `long long`！！！

下面是代码：

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
struct Building{
	int id;
	int vis;
}a[200010];
int ans[200010];
int cmp(Building aa,Building bb){
	return aa.vis>bb.vis;
}
signed main(){
	int T;
	cin>>T;
	while(T--){
		int n;
		cin>>n;
		for(int i=1;i<=n;i++){
			a[i].id=i;
			cin>>a[i].vis;
		}
		sort(a+1,a+n+1,cmp);
		int tot=0;
		int nw=1;
		for(int i=1;i<=n;i++){
			ans[a[i].id]=nw;
			tot+=(abs(nw)*2*a[i].vis);
			if(nw>0)
				nw=-nw;
			else
				nw=-nw+1;
		}
		cout<<tot<<endl;
		cout<<0<<' ';
		for(int i=1;i<=n;i++)
			cout<<ans[i]<<' ';
		cout<<endl;
	}
	return 0;
}









	









```

---

## 作者：xiaomuyun (赞：2)

# CF1614B Divan and a New Project 题解
[题目传送门](https://www.luogu.com.cn/problem/CF1614B)

昨晚的第一题是贪心，没想到第二题也是贪心……
## 题意分析
你需要给 $n+1$ 个建筑定位置，已知第 $i$ 个建筑需要访问 $a_i$ 次，然后你就需要从第 $0$ 个建筑访问第 $i$ 个建筑 $a_i$ 次。每次访问需要花费 $2\times|x_0-x_i|$ 的时间来走路，其中 $x_i$ 表示第 $i$ 个建筑的位置。现在请你求出最少需要走多远以及一个满足答案的 $x$ 数组。
## 题目分析
这题的解法我已经说了：贪心！

首先我们可以尝试~~感性~~理解一下，如果一个建筑要访问很多次，那么它的位置应该离 $0$ 号建筑更近。而且我们完全可以将 $x_0$ 设为 $0$，毕竟 $x_0$ 的位置并不影响最少要走的距离。

所以我们可以将输入的 $a$ 数组从大到小排序，然后左右左右（~~反复横跳~~）地放建筑，这样可以保证要访问最多次的建筑里 $0$ 号建筑最近。
## 代码实现
```cpp
#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
struct node{
	long long val,id;
}a[200010];
long long t,n,ans[200010];
bool cmp(const node &a,const node &b){
	return a.val>b.val;
}
int main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n);
		for(long long i=1;i<=n;++i){
			scanf("%lld",&a[i].val);
			a[i].id=i;
		}
		memset(ans,0,sizeof ans);
		sort(a+1,a+1+n,cmp);//从大到小排序
		long long lcnt=0,rcnt=0,res=0;
		for(long long i=1;i<=n;++i){
			if(lcnt==rcnt){//往右放建筑
				res+=2*(rcnt+1)*a[i].val;//求出访问第i个建筑需要的时间
				ans[a[i].id]=++rcnt;
			} else {//往左放建筑
				res+=2*(lcnt+1)*a[i].val,ans[a[i].id]=0-lcnt-1,++lcnt;//和上面一样
			}//存答案
		}
		printf("%lld\n",res);
		for(long long i=0;i<=n;++i) printf("%lld ",ans[i]);
		putchar('\n');
	}
	return 0;
}
```
## 总结
昨晚原本是能把这一题过了的，但是没开 `long long`，然后就……

所以希望大家要吸取我这个教训，管理员求过！谢谢！

---

## 作者：wangyibo201026 (赞：0)

## 感言

自己五分钟水完了（真的哦）。

## 思路

由于说输出任意一种方案都行，以不妨设 $0$ 号建筑在位置 $X$。

此时，我们可以发现，当一栋建筑物来回访问的次数越多，这栋建筑物就要离 $X$ 越近，才能使得时间越小。

那么，怎么确定 $n + 1$ 栋楼的位置呢？

我们可以发现，离 $X$ 最近的位置有两个（仅指整数位置），分别是 $X - 1$ 和 $X + 1$，同理，第二近的位置也有两个，分别是 $X - 2$ 和 $X + 2$。

此时，我们按照这 $n + 1$ 栋楼的访问次数排序，再依次对应 $X - 1, X + 1, X - 2, X + 2...$，最终再还原输出就可以了。

注意，$X$ 可以为任意值，但由于数据卡得很紧，这里还是设为 $0$ 比较保险。还有，一定要**开 long long**，其次，时间乘 $2$，可以自己想想为什么。

## 代码

思路有了，代码就到手了（不是 ctj）:

```
#include<bits/stdc++.h>

using namespace std;

long long t, n, b[200005], len, f, sum;

struct node{
  long long zhi, wei, shu;    //shu 为位置，wei 为记录是第几栋楼，zhi为访问次数
}a[200005];

bool cmp(node x, node y){
  return x.zhi > y.zhi;    //排序
}

bool cmp2(node x, node y){
  return x.wei < y.wei;    //还原
}

void Solve(){
  cin >> t;
  while(t--){
    len = f = sum = 0;    //sum 来统计时间，f 来记录位置。
    cin >> n;
    for(int i = 1; i <= n; i++){
      cin >> a[i].zhi;
      a[i].wei = i;
    }
    sort(a + 1, a + 1 + n, cmp);   //按照访问次数排序
    a[0].shu = 0;
    for(int i = 1; i <= n; i++){    //分配位置
      if(i & 1){   //别吓傻了，i & 1 是判断 i 是否为奇数
        f++;
        a[++len].shu = f;
      }
      else{
        a[++len].shu = -f;
      }
    }
    sort(a + 1, a + 1 + n, cmp2);
    for(int i = 1; i <= n; i++){
      sum += (abs(a[i].shu - 0) * a[i].zhi);    //求时间
    }
    cout << sum * 2 << endl;   //由于要来回都走，所以要乘 2
    for(int i = 0; i <= n; i++){
      cout << a[i].shu << " ";   //输出位置
    }
    cout << endl;
  }
}

int main(){
  Solve();
  return 0;
}
```

---

## 作者：_Diu_ (赞：0)

要使路程最短，那我们可以让每一个房子靠近 $0$ 号建筑建。

这样最短占用一段连续 $n+1$ 个位置的坐标，远小于 $1e6$ 的限制。

我们把 $0$ 号建筑放在 $[-900000,900000]$ 都可以，$114514$ 也行.

这里我们为了方便，把它放在 $0$ 处。

这样 $n$ 个建筑距离 $0$ 号建筑的距离应该分别为 $1,1,2,2,3,3,\dots,\lceil\frac n2\rceil$。

然后我们很贪心的想到：

**把 $n$ 个建筑从大到小排序，让它们左右左右的放，也就是与上述距离一个一个对应即可**。

怎么证明呢，这里提供一种反证法：

假设上述结论不成立，也就是最优解中存在一对点对 $(x,y)$ 使得 $a_x>a_y\&\&d_x>d_y$（这里假设 $d_i$ 表示建筑 $i$ 距离 $0$ 号建筑的距离）。

那么这两个点的时间为：

$2a_xd_x+2a_yd_y=2a_x(d_x+d_y)-2(a_x-a_y)d_y$。

如果交换一下 $(x,y)$ 的距离，那么这两个点的贡献为：

$2a_yd_x+a_xd_y=2a_x(d_x+d_y)-2(a_x-a_y)d_x$。

明显比上面的小。

与条件**最优解**不符。

所以命题成立。

然后我们贪心处理就好了。

~~当时没看到要输出这个时间调了好久~~

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int t,n,x[N];
struct nb{
	int id,a;
}a[N];
bool cmp(nb a,nb b){
	return a.a>b.a;
}
signed main(){
	scanf("%lld",&t);
	for(;t--;){
		scanf("%lld",&n);
		for(int i=1;i<=n;i++)scanf("%lld",&a[i].a),a[i].id=i;
		sort(a+1,a+n+1,cmp);
		int ans=0;
		for(int i=1;i<=n;i++){
			if(i&1)x[a[i].id]=i/2+1,ans+=(i/2+1)*a[i].a;
			else x[a[i].id]=-i/2,ans+=(i/2)*a[i].a;
		}
		printf("%lld\n114514 ",ans*2);
		for(int i=1;i<=n;i++)printf("%lld ",114514+x[i]);
		puts("");
	}
}
```

---

## 作者：orz_z (赞：0)

## 题目大意

在一条街上，盖 $n+1$ 栋楼，每栋楼坐标为 $x_i$，满足 $\forall j \ne i,x_i \ne x_j$ 且 $x_i$ 是一个整数。

将所有楼从 $0$ 到 $n$ 标号。

有一人在编号为 $0$ 的楼，分别要去编号为 $i$ 的建筑 $a_i$ 次，这个人往返编号为 $i$ 的建筑一趟花费的时间为 $2 \times(|x_i - x_0|)$。

请安排每一栋楼的坐标，使得这个人花费的时间最短。

共 $T$ 组数据。

对于 $100\%$ 的数据，保证 $1\leq T \leq 10^3,1 \leq n \leq 2*10^5,0 \leq a_i \leq 10^6$。

## 解题思路

首先，我们把编号为 $0$ 的楼的坐标定为 $0$ 方便去做。

记答案为 $ans$，则 $ans=\sum\limits_{i=1}^{n}{2*a_i*|x_0-x_i|}$。

要使得 $ans$ 最少，就要让 $a_i$ 大的楼放到距离 $x_0$ 近的地方。

那么按照 $a_i$ 从大到小排序，在 $x_0$ 按照左右左右左右…的顺序放楼即可。

具体实现见代码。

时间复杂度 $\mathcal O(Tn)$。

## CODE

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int _ = 2e5 + 7;

int t;

int n;

struct abc
{
    int v, id;
} a[_];

int b[_];

int ans;

bool cmp(abc a, abc b)
{
    return a.v > b.v;
}

signed main()
{
    scanf("%lld", &t);
    while (t--)
    {
        ans = 0;
        scanf("%lld", &n);
        for (int i = 1; i <= n; ++i)
            scanf("%lld", &a[i].v), a[i].id = i;
        sort(a + 1, a + n + 1, cmp);
        int k = 0;
        for (int i = 1; i <= n; i += 2)
        {
            b[a[i].id] = ++k;
        }
        k = 0;
        for (int i = 2; i <= n; i += 2)
        {
            b[a[i].id] = --k;
        }
        for (int i = 1; i <= n; ++i)
        {
            ans += 2 * a[i].v * abs(b[a[i].id]);
        }
        cout << ans << "\n";
        cout << "0 ";
        for (int i = 1; i <= n; ++i)
            cout << b[i] << " ";
        cout << "\n";
    }
    return 0;
}
```

---

## 作者：tongziyu (赞：0)

### Update on 2021/11/28： 翻译锅了，感谢 Eason_AC 大佬指出。


------------



# 题面翻译


### 题目描述

有 $n + 1$ 座的建筑，编号从 $0$ ~ $n$。

有一个人从编号为 $0$ 的建筑出发，分别要去编号为 $i$ 的建筑 $a_i$ 次。

设编号为 $i$ 的建筑坐标为 $x_i$，这个人往返编号为 $i$ 的建筑一趟花费的时间为 $2 \times(|x_i - x_0|)$。

求如何安排这 $n + 1$ 座建筑的坐标，使这个人在路上花费的总时间最小。

### 输入格式

输入第一行一个整数 $t$，表示有 $t$ 组数据。

每组数据第一行一个整数 $n$，第二行 $n$ 个数，分别表示 $a_1$ …… $a_n$。

### 输出格式

每组数据输出共两行，第一行一个整数，表示最小要花费的总时间。第二行 $n + 1$ 个整数，表示使总时间花费最小的 $x_0$ …… $x_n$。如果有多组符合条件的解，输出任意一组即可。

### 数据范围与约定

对于 $100\%$ 的数据，$1 \le t \le 10^3$；$1 \le n \le 2 \cdot 10^5$；$0 \le a_i \le 10^6$；$-10^6 \le x_i \le 10^6$。

对于每个测试点，$\Sigma n \le 2 \times 10^5$。

# Solution
首先考虑如何使时间之和最小。

既然要总时间最小，那么要去更多次（即 $a_i$ 越大）的建筑肯定是距离出发点 $x_0$ 越近越好，这样多次去的总时间开销最小。

那么我们把每个建筑按 $a_i$ 从大到小排序，把坐标按距离 $x_0$ 的远近分配给每一座建筑即可。

因为本题有 Special Judge，我们不妨直接假设 $x_0 = 0$。 

之后只需按排序后的顺序，依次将 $1$，$-1$，$2$，$-2$…… 分配下去，一边分配一边统计答案，注意要开 long long。

# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct node
{
	int vis, id;
}a[N];
int ans[N];
inline int read()
{
	int r = 0, c = getchar();
	while (c < '0' || c > '9') c = getchar(); 
	while (c >= '0' && c <= '9') r = (r << 3) + (r << 1) + (c ^ 48), c = getchar();
	return r; 
}
inline bool cmp(node a, node b)
{
	return a.vis > b.vis; 
} 
int main()
{
	int t = read();
	while (t--)
	{
		int n = read();
		long long sum = 0;
		for (int i = 1; i <= n; ++i) a[i].vis = read(), a[i].id = i;
		sort(a + 1, a + n + 1, cmp);
		for (int i = 1; i <= n; ++i) ans[a[i].id] = (i & 1) ? ((i + 1) >> 1) : (- (i >> 1)), sum += ((long long)a[i].vis * abs(ans[a[i].id]) << 1); 
		printf("%lld\n0 ", sum);
		for (int i = 1; i <= n; ++i) printf("%d ", ans[i]);
		puts("");
	}
}
```


---

## 作者：徐晨轩✅ (赞：0)

# 题目大意

> 给你 $n$ 个数，分别为 $a_1,a_2,\dots,a_n$，请输出一个长度为 $n+1$ 的序列 $x=x_0,x_1,x_2,\dots,x_n$，使得：
>
> $$\sum_{i=1}^{n}2 \times |x_0-x_i| \times a_i$$
>
> 最小。打印这个最小值及 $x$。

# 题解

很明显，一道贪心题。

既然 $a$ 数组已经是固定下来的了，那么想要使得上式最小，则 $a_i$ 越大，$|x_0-x_i|$ 就得越小，$a_i$ 越小，$|x_0-x_i|$ 就得越大。

我们先把 $a$ 排一个递减序，这样越往后，$|x_0-x_i|$ 就越大。为了方便计算，我们把 $x_0$ 设为 $0$。这样，我们就可以按下图所示依次分配 $x$ 数组：

![](https://cdn.luogu.com.cn/upload/image_hosting/lyduwjg3.png)

e.g. `x[a[11].dex]=-5`，`x[a[9].dex]=-4`（其中 `a[i].dex` 为排过序后的 $a_i$ 所在未排序的 $a$ 中的位置）

现在我们要做的是对应每个 $i$，求出 `x[a[i].dex]`。我们可以用指针的思想做，就是定义 $p$（代码中是 `dex`**（不是上面说的 `x[a[i].dex]` 的 `dex`！**），在每做一轮之后，计算出下一个 $p$ 就行了，即代码中的：

```cpp
for(int i=1;i<=n;i++)
{
	x[a[i].second]=dex;
	if(dex>0)dex=-dex;
	else dex=-dex,dex++;
}
```

最后，再求出 $\sum_{i=1}^{n}2 \times |x_0-x_i| \times a_i$ 即可。

# 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=200001;
bool cmp(pair<int,int>aa,pair<int,int>bb){return aa>bb;}
pair<int,int>a[N],tmpa[N];
int t,n,sum,dex,x[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin >> t;
	while(t--)
	{
		memset(a,0,sizeof a);
		memset(x,0,sizeof x);
		sum=0,dex=1;
		cin >> n;
		for(int i=1;i<=n;i++)
			cin >> a[i].first,a[i].second=i;
		memcpy(tmpa,a,sizeof a);
		sort(a+1,a+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			x[a[i].second]=dex;
			if(dex>0)dex=-dex;
			else dex=-dex,dex++;
		}
		for(int i=1;i<=n;i++)
			sum+=2*abs(x[i])*tmpa[i].first;
		cout << sum << endl;
		cout << 0 << " ";
		for(int i=1;i<=n;i++)
			cout << x[i] << " ";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：qwcdim (赞：0)

## CF1614B Divan and a New Project 题解

[题目传送门](https://www.luogu.com.cn/problem/CF1614B)

[安利blog](https://www.luogu.com.cn/blog/I-like-10/)

### 题目大意

~~为了锻炼你的阅读能力~~，就不放大意了。

### 题目思路

看完题目你就知道，这是一道**贪心**。首先可以发现建筑最好一个贴一个。然后运用一点小小的贪心，就是把要多次走的建筑建到**离原点最近**的点，然后统计一下总时间就可以了。

### 高清可直接食用代码（要用C++17）

```cpp
#include<iostream>
#include<cstdio>
#include<stdio.h>
#include<algorithm>
using namespace std;
const long long N=2*1e5+10;
long long t,n,sum=1,ans;
bool flagkkk,flagQQ;
struct node{
	long long id,cnt,x;
}a[N];
inline long long read(){//快读
	char ch;
	ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	long long f=0;
	while(ch>='0'&&ch<='9'){
		f=(f<<3)+(f<<1)+ch-48;
		ch=getchar();
	}
	return f;
}
inline bool cmp(node a,node b){
	return a.cnt>b.cnt;
}
inline bool cmp_2(node a,node b){
	return a.id<b.id;
}
int main(){
	t=read();
	while(t--){
		n=read();
		for(long long i=1;i<=n;i++){
			a[i].cnt=read();
			a[i].id=i;
		}
		sort(a+1,a+n+1,cmp);//按到达次数排
		for(long long i=1;i<=n;i++){
			if(flagkkk==true&&flagQQ==true){//0+sum||0-sum的两个点都满了
				sum++;//绝对值加一
				flagkkk=flagQQ=false;//重置
			}
			if(flagkkk==true&&flagQQ==false){
				ans+=2*sum*a[i].cnt;//统计
				a[i].x=0+sum;//右点
				flagQQ=true;
			}else if(flagkkk==false&&flagQQ==false){
				ans+=2*sum*a[i].cnt;//统计
				a[i].x=0-sum;//左点
				flagkkk=true;
			}
		}
		printf("%lld\n",ans);//输出统计
		printf("%lld ",0);//不想找原点，直接设0
		sort(a+1,a+n+1,cmp_2);//按下标排
		for(long long i=1;i<=n;i++){
			printf("%lld ",a[i].x);//输出
		}
		printf("\n");
		ans=0;//初始化
		sum=1;
		flagkkk=flagQQ=false;
	}
	return 0;
}
```


---

## 作者：Dragonbell_exp (赞：0)

### 思路：
由于所有建筑在一条链上，且它们的坐标各不相同。

也就是说，要从主建筑到达别的建筑的方法一定是向左或向右直行。

以贪心的思想来看，我们应该把去的次数尽量多的建筑放得离主建筑最近，次数少的放在远处。这一步可以用排序实现。

我们不妨把主建筑的坐标设为 $0$，向左走到达的建筑就是 $-1$、$-2$……向右走到达的建筑就是 $1$、$2$……他们的绝对值也就是从主建筑到达那些地方的距离。如下所示：

$$...-4,-3,-2,-1,0,1,2,3,4...$$

然后根据这个思路模拟即可。
### 代码：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n;
struct pi{
	int name;
	int v;
	int ovo;
}mus[1919810];
int z,u,ans;
int out[1919810];
bool cmp(pi a,pi b){
	return a.name>b.name;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%d",&n);
		z=0;
		u=0;
		ans=0;
		for(int i=1;i<=n;i++){
			scanf("%lld",&mus[i].name);
			mus[i].v=i;
		}
		sort(mus+1,mus+n+1,cmp);
		for(int i=1;i<=n;i++){
			if(i%2==1){
				ans+=(i/2+1)*mus[i].name*2;
				mus[i].ovo=i/2+1;
			}
			else{
				ans+=(i/2)*mus[i].name*2;
				mus[i].ovo=-i/2;
			}
		}
		cout<<ans<<endl;
		cout<<0<<" ";
		for(int i=1;i<=n;i++){
			out[mus[i].v]=mus[i].ovo;
		}
		for(int i=1;i<=n;i++){
			cout<<out[i]<<" ";
		}
		cout<<endl;
	}
}
```





---

