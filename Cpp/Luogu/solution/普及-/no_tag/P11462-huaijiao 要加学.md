# huaijiao 要加学

## 题目背景

天天网瘾的 huaijiao 绩点已经大残了，为了稳住绩点，huaijiao 决定加学。

## 题目描述

期末考试一共有 $n$ 门课程，huaijiao 需要在有限时间内尽可能合理地安排速通计划，来让自己的绩点最大化。

已知第 $i$ 门课程的学分 $c_i$ 和难度系数 $k_i$，huaijiao 如果花费 $x$ 天来速通第 $i$ 门课程，那么他将取得的成绩 $w_i = \min(1, \displaystyle\frac{x}{k_i}) \times 100$。

huaijiao 最后的总成绩 $W = \sum_{i=1}^{n} (w_i \times c_i)$。

huaijiao 现在一点没学，距离期末考试只剩下 $M$ 天，每天 huaijiao 只能专心学一门，请你帮帮他最大化他的总成绩。

## 说明/提示

$1 \leq n \leq 1000$，$1 \leq M \leq 1000$，$1 \leq c_i \leq 10$，$1 \leq k_i \leq 10$。


## 样例 #1

### 输入

```
4 8
2 1 10 10
4 9 5 2
```

### 输出

```
2050.0000```

## 样例 #2

### 输入

```
10 19
1 10 3 3 1 10 2 7 8 6
3 2 1 2 7 9 7 6 4 7
```

### 输出

```
3544.4444
```

## 样例 #3

### 输入

```
8 18
4 6 4 1 3 8 9 3
6 9 6 7 5 9 8 3
```

### 输出

```
1822.2222
```

# 题解

## 作者：lailai0916 (赞：5)

## 原题链接

- [洛谷 P11462 huaijiao 要加学](https://www.luogu.com.cn/problem/P11462)

## 解题思路

$$
\begin{aligned}
  W &= \sum_{i=1}^n(w_i\times c_i) \\
  &= \sum_{i=1}^n\left(\min\left(1,\frac{x_i}{k_i}\right)\times 100\times c_i\right) \\
  &= 100\sum_{i=1}^n\left(\min(k_i,x_i )\times \frac{c_i}{k_i}\right)
\end{aligned}
$$

可以发现，第 $i$ 门课程每学一天的收益是 $\frac{c_i}{k_i}$，且最多可学 $k_i$ 天。为了最大化总收益，应优先选择收益较高的课程。

因此，可以按 $\frac{c_i}{k_i}$ 从大到小排序，然后贪心地选择每门课程最多学习 $x = \min(k_i, m)$ 天，并更新剩余天数 $m \gets m - x$。

## 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const int N=1005;
struct Node
{
	int c,k;
}a[N];
bool cmp(const Node &u,const Node &v)
{
	return u.c*v.k>v.c*u.k;
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i].c;
	for(int i=1;i<=n;i++)cin>>a[i].k;
	sort(a+1,a+n+1,cmp);
	double ans=0;
	for(int i=1;i<=n;i++)
	{
		int x=min(m,a[i].k);
		ans+=x*100.0/a[i].k*a[i].c;
		m-=x;
	}
	cout<<fixed<<setprecision(4)<<ans<<'\n';
	return 0;
}
```

---

## 作者：封禁用户 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/P11462)

我们可以建一个结构体数组 $p$，其中 $a$ 表示该课程每天学习所能增加的成绩与学分的乘积，也就是 $\frac{c_i}{k_i}$，$b$ 表示该课程的索引编号。$a$ 值越大，说明这门课的学习效率越高，即每花一天在这门课上所获得的成绩增长就会越多。所以我们按照 $a$ 降序排序，优先选择那些每天学习收益最高的课程。然后对于每一门课程，我们根据剩余天数 $m$ 和该课程的难度 $k_{id}$ 来决定应该分配多少天给这门课程学习，这里可以用 $\min(m,k_{id})$ 来确保不会超过总的剩余天数或课程本身需要的天数，其中 $id$ 指这门课程的索引编号。然后根据分配的时间再计算出该课程可以获得的成绩，并将其求和，最后保留 $4$ 位小数输出。

注意，我们在处理成绩时假设了只要花费时间学习就会有正向收益，也就是即使超过了 $k_i$ 天，因为成绩公式中有一个 $\min(1,\frac{x}{k_i})$ 的限制，意味着当 $x\ge k_i$ 时成绩就不会再增加。因此在实际分配学习时间时，我们只需要考虑不超过 $k_i$ 的情况即可。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1005;

int c[N], k[N];

struct Node
{
    double a;
    int b;
} p[N];

bool cmp(Node x, Node y)
{
    return x.a > y.a;
}

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n; i++)
        cin >> k[i];
    for (int i = 1; i <= n; i++)
        p[i] = {1.0 * c[i] / k[i], i};
    sort(p + 1, p + 1 + n, cmp);
    double ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (m <= 0) break;
        int id = p[i].b, ds = min(m, k[id]);
        ans += ds * c[id] * 100.0 / k[id];
        m -= ds;
    }
    printf("%.4lf\n", ans);
    return 0;
}
```

---

## 作者：_Sunday_ (赞：2)

## 思路
一道贪心，根据每道题的价值分配学习天数。  
共有 $n$ 门课程，第 $i$ 门课程学分为 $c_i$，难度系数为 $k_i$。具体步骤如下：
1. 算出第 $i$ 门学科的价值 $t_i$；
2. 根据每门学科的价值分配对应的学习天数 $x$，价值越大分配的天数越多，由于他将取得的成绩 $w_i=\min(1,\frac{x }{k_i})\times 100$，所以他第 $i$ 门学科学习 $k_i$ 天就可以取得最大效果；
3. 算出所有学科取得的成绩之和。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct subjects{
	int c,k;
	double t;//第 i 门学科的价值 
}s[1005];
double w;
bool cmp(subjects x,subjects y){ 
	return x.t>y.t;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>s[i].c;
	for(int i=1;i<=n;i++){
		cin>>s[i].k;
		s[i].t=s[i].c*1.0/s[i].k;//算出第 i 门学科的价值 
	}
	sort(s+1,s+n+1,cmp);//根据价值由大到小排序 
	for(int i=1;i<=n;i++){
		int x;
		if(m>=s[i].k) x=s[i].k;
		else x=m;
		m-=x;//根据价值分配天数 
		w+=((x+0.0)/s[i].k)*100.0*s[i].c;//算出总和 
		if(m==0) break;
	}
	printf("%.4lf",w);
	return 0;
}
```

---

## 作者：mishitaotuoyyds (赞：2)

# 题目分析：
因为每一科将取得的成绩为 $w_i = \min(1, \displaystyle\frac{x}{k_i}) \times 100$。所以每科的成绩只需要 $k_i$ 天就可以最大化，再多也就只有这些分，然后就是贪心，贪一个最大值，这里我们只需要贪一个科目每天能获得的学分就行了。
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long a,b;
double ans=0;
struct jj{
	long long c,k,w;
	double xjb;
};
jj oo[1010];
bool cmp(jj d,jj f){
	return d.xjb>f.xjb;
}
int main()
{
	cin>>a>>b;
	for(int i=1;i<=a;i++){
		cin>>oo[i].c;
	}
	for(int i=1;i<=a;i++){
		cin>>oo[i].k;
		oo[i].xjb=(double)oo[i].c/(double)oo[i].k;
	}
	sort(oo+1,oo+a+1,cmp);
	for(int i=1;i<=a;i++){
		if(b>=oo[i].k){
			b-=oo[i].k;
			ans+=100*oo[i].c;
		}
		else{
			if(b!=0){
				ans+=100*((double)b/(double)oo[i].k)*oo[i].c;
				b=0;
			}
		}
		
	}
	cout << fixed << setprecision(4) << ans << endl;
    return 0;
} 
```
完结撒花。

求管理大大通过。

---

## 作者：Duanhen (赞：2)

### 题目大意

一共有 $n$ 门课程，每门课程的有学分 $c$ 和难度系数 $k$，如果花费 $x$ 天来速通第 $i$ 门课程，那么将取得的成绩 $w_i = \min(1, \displaystyle\frac{x}{k_i}) \times 100$。

而最后的总成绩 $W = \sum_{i=1}^{n} (w_i \times c_i)$。

现在距离期末考试只剩下 $M$ 天且每天只能专心学一门，需要最大化总成绩。

### 解题思路

从题目中我们可以知道，最后总成绩是由每门课程的成绩乘以学分累加得出。而对于第 $i$ 门课程，我们每天可以获得的课程成绩为 $\frac{1}{k_i}$ 且学满 $k_{i}$ 天就可以拿到满分，那就意味着我们每天可以拿到的总成绩为 $(\frac{1}{k_i}\times 100)\times c_i$，所以我们可以提前计算出每门课程的 $\frac{c_i}{k_i}$ 的值（简单来说就是该门课程的性价比），然后按性价比排序，优先学习性价比高的课程。

### 参考代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1100;
struct cl {
  double c, k, t;
} g[N];
bool cmp(cl &a, cl &b) { return a.t > b.t; }

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> g[i].c;
  for (int i = 1; i <= n; i++) cin >> g[i].k;
  for (int i = 1; i <= n; i++) g[i].t = g[i].c / g[i].k; //t为性价比
  sort(g + 1, g + n + 1, cmp);
  double res = 0;
  for (int i = 1; i <= n; i++) {
    if (m >= g[i].k) {
      m -= g[i].k;
      res += g[i].c;
    } else {
      res += m * g[i].t;
      break;
    }
  }
  res *= 100;
  printf("%.4f", res);
  return 0;
}
```

---

## 作者：cy20110922 (赞：2)

# 分析
这道题叫我们计算最大值，且题目中有两个数据，那我们就可以用结构体排序来做。
# 方法
我们可以建立一个结构体，然后在结构体里面建立两个变量，一个为每天学习所能增加的成绩与学分的乘积，另一个为表示该课程的索引编号。然后在编一个  cmp 将结构体从大到小排序。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int dp[1200],c[1200],k[1200];
double sum=0;
struct study{
	double w;
	int v;
}s[1200];
bool cmp(study a,study b){
	return a.w>b.w;
}
int main(){
	int n,m;
	cin >> n >> m;
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&k[i]);
	}
	for(int i=1;i<=n;i++){
		s[i].w=1.0*c[i]/k[i];
		s[i].v=i;
	}
	sort(s+1,s+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(m<0)break;
		int id=s[i].v,dd=min(m,k[id]);
		sum+=dd*c[id]*100.0/k[id];
		m-=dd;
	}
	cout << fixed << setprecision(4) << sum;
	return 0;
}
```

---

## 作者：canwen (赞：2)

$f_{i,j}$ 表示对于前 $i$ 门学科，有 $j$ 天可以学习的的最大答案，显然 $f_{n,m}$ 即为所求。

尝试开始转移。

我们设此时对 $i$ 这一门学科进行补救的天数为 $kk$。

显然对于 $kk>k_i$，肯定是白学浪费时间，因为系数 $w_i$ 上限为 $1$。

对于这 $i$ 一门学科，假设不用时间学，初始答案即 $f_{i-1,j}$；否则转移方程，花 $kk$ 天数学 $i$ 学科总答案即为 $f_{i-1,j-kk} + \frac{kk}{k_i}\cdot100\cdot c_i$，取最大值即可。

[Code](https://www.luogu.com.cn/paste/wpg02yra)。

---

## 作者：Planet_Earth (赞：2)

## 题解：P11462 huaijiao 要加学
### [题目传送门](https://www.luogu.com.cn/problem/P11462)

在这道题中，我们需要帮助学生 huaijiao 在有限的时间内最大化他的总成绩。题目给定了 n 门课程，每门课程都有相应的学分和难度系数。

学生可以在 M 天内选择学习这些课程，每天只能专注于一门课程。

通过合理安排学习时间，学生的最终成绩将取决于他在每门课程上投入的时间和课程的难度。

#### 问题分析

每门课程的成绩计算公式为：
$$w_i = \min(1, \frac{k_i}{x}) \times 100$$
其中，$k_i$ 是课程的难度，$x$ 是学习这门课程所花费的天数。

我们可以看出，若学习天数 $x$ 大于等于难度 $k_i$，则成绩 $w_i$ 达到最大值 100；

若 $x$ 小于 $k_i$，则成绩会随着学习天数的增加而线性增长。
最终的总成绩 $W$ 为所有课程成绩与其学分的乘积之和：
$$W = \sum_{i=1}^{n} (w_i \times c_i)$$
#### 代码

```cpp
#include <bits/stdc++.h>
#define N 1010
#define int long long 
using namespace std;
int read(){
    int x=0,f=1;
  	char ch=getchar_unlocked();
	  while(!isdigit(ch)){
		    if(ch=='-') f=-1;
		    ch=getchar_unlocked();
	  }
	  while(isdigit(ch)){
		    x=(x<<1)+(x<<3)+(ch^48);
		    ch=getchar_unlocked();
  	}
	  return x*f;
}
void write(int x){
  	if(x<0){
	    	putchar('-');
		    x=-x;
	  }
  	if(x>9) write(x/10);
  	putchar(x%10+'0');
}
int n,m,c[N],k[N];
double dp[N];
signed main() {
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        c[i]=read();
    }
    for(int i=1;i<=n;i++){
        k[i]=read();
    }
    for(int i=1;i<=n;i++){
        for(int x=m;x>=1;x--){
            for(int d=1;d<=x;d++){
                double s=min(1.0,d/(double)k[i])*100*c[i];
                dp[x]=max(dp[x],dp[x-d]+s);
            }
        }
    }
	printf("%0.4lf",dp[m]);
    return 0;
}
//Planet_Earth
```

---

## 作者：Night_sea_64 (赞：0)

我场上降智写了个 $O(n^3)$。

可以观察到一定最多一个课程没有学完。理由是如果两个课程都没有学完的话，你可以把一天从价值更低的课程换成价值更高的课程。

于是我们直接枚举没有学完的那一门课，然后把剩下的课程做一遍 $O(n^2)$ 的背包，然后枚举用了的天数，拿这一门课补全剩下的天数即可。

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
int n,m,v[1010],w[1010],f[1010];
double ans;
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>v[i];
    for(int i=1;i<=n;i++)cin>>w[i];
    for(int i=1;i<=n;i++)
    {
        memset(f,0,sizeof(f));
        for(int j=1;j<=n;j++)
        {
            if(j==i)continue;
            for(int k=m;k>=w[j];k--)
                f[k]=max(f[k],f[k-w[j]]+v[j]);
        }
        for(int j=0;j<=m;j++)
            ans=max(ans,f[j]+min(1.0,(m-j)*1.0/w[i])*v[i]);
    }
    printf("%.4lf\n",ans*100);
    return 0;
}
```

---

## 作者：Kratos_Charger (赞：0)

## P11462 huaijiao 要加学 题解

### 题目大意

给定 $n$ 门课程，每门课程有对应的学分 $c$ 和难度系数 $k$，以及剩余的学习天数 $m$。需要根据这 $m$ 天合理分配给各门课程，以最大化总成绩。每门课程的最终得分取决于它的学分和分配给它的学习天数，具体如下：

1. 对于每门课程，若分配的学习天数 $x$ 大于或等于其难度系数 $k$，则该课程得满分，得分为 $c$。

2. 若分配的学习天数 $x$ 小于其难度系数 $k$，则该课程的得分为 $c \times \frac{x}{k}$。

### 思路

一道贪心题。

按照性价比从高到低进行排序。排序的目的是为了让首先分配学习时间给那些最值得学习的课程。排序之后，逐个遍历这些课程，根据剩余的学习天数来决定每门课程学习多少时间。

对于每门课程，首先检查剩余的学习天数是否足够学习该课程。如果剩余的天数 $m$ 大于或等于该课程的难度系数 $k$，那么就可以分配足够的天数，完全学习该课程，并且该课程得满分 $c$。如果剩余的学习天数不足以完成该课程的学习，那么只能按比例计算该课程的得分，得分为 $c \times \frac{m}{c}$，并且学习时间将用尽。

在遍历所有课程时，逐步减少剩余的学习天数，直到学习时间用完或所有课程都处理完为止。

最后，将所有课程的得分加起来，得到最大总成绩。


### Code


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
struct lesson{
    int c,k;
    double x;  // 性价比，表示每个学习天数带来的学分
}a[1005];

// 比较函数，用于根据性价比降序排序
bool cmp(lesson a,lesson b){
    return a.x>b.x;  // 性价比高的排在前面
}

signed main(){
    // 输入课程数和剩余天数
    cin>>n>>m;

    // 输入每门课程的学分
    for(int i=1;i<=n;i++){
        cin>>a[i].c;
    }

    // 输入每门课程的难度，并计算每门课程的性价比
    for(int i=1;i<=n;i++){
        cin>>a[i].k;
        a[i].x=(double)a[i].c/a[i].k;  // 性价比 = 学分 / 难度
    }

    // 按性价比从大到小排序
    sort(a+1,a+n+1,cmp);

    double ans=0;

    // 遍历所有课程
    for(int i=1;i<=n;i++){
        if(m>=a[i].k){
            // 如果剩余天数足够学习该课程，直接满分
            ans+=1.0*a[i].c;
            m-=a[i].k;  // 减去已使用的天数
        }else{
            // 如果剩余天数不够，只能部分学习，按比例计算得分
            ans+=(double)m/a[i].k*a[i].c;
            break;  // 一旦剩余天数用完，结束计算
        }
    }

    // 输出最终总成绩，保留四位小数
    printf("%.4lf",ans);
    
    return 0;
}

```

---

## 作者：Eason_cyx (赞：0)

显然一门课学到 $k_i$ 天之后就不优了。那么问题转换为：

有 $n$ 门课，第 $i$ 门课每学 $1$ 天可以获得 $\dfrac{c_i}{k_i}\times100$ 的收益，你最多可以学 $m$ 天，问最大收益。

那么我们就直接将每门课拆成 $k_i$ 个只用学 $1$ 天的小课，然后贪心排序，选出最大的 $m$ 个求和即可。时间复杂度 $O(\sum k_i \log \sum k_i)$。

代码很好写。 

```cpp
#include <bits/stdc++.h>
using namespace std;
int c[1005], k[1005]; double p[10005];
int main() {
	int n, m; cin >> n >> m; int cur = 0;
	for(int i = 1;i <= n;i++) cin >> c[i];
	for(int i = 1;i <= n;i++) cin >> k[i];
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= k[i];j++) {
			p[++cur] = 100.0 / k[i] * c[i]; 
		}
	} sort(p+1,p+cur+1,greater<double>());
	double ans = 0;
	for(int i = 1;i <= min(m,cur);i++) ans += p[i]; cout << fixed << setprecision(4) << ans << endl;
	return 0;
}
```

---

