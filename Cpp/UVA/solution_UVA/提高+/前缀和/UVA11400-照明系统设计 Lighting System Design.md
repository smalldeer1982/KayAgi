# 照明系统设计 Lighting System Design

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=26&page=show_problem&problem=2395

[PDF](https://uva.onlinejudge.org/external/114/p11400.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11400/c3748d15cb3e3882e349c0c2e200acb240ab8b00.png)

## 样例 #1

### 输入

```
3
100 500 10 20
120 600 8 16
220 400 7 18
0```

### 输出

```
778```

# 题解

## 作者：uhgariej (赞：15)

状态的定义：按额定电压排序后,dp[i]:表示前i个物品,以第i个物品结尾的最小费用

状态的转移：dp[i]这个状态由dp[j]转移而来，其中j+1到i的物品都被替换成第i个物品。

时间复杂度：O(N^2)

---

看了一些题解，好像都没说为什么"j+1到i的物品都被替换成第i个物品"这样做是合理的。

当然我也想了一个下午才明白了，下面大致说一下：

假设排序后物品序号如下：1，... ，i，i+1，i+2，...

假如我们在更新这个方程

dp[i+2] = std::min(dp[i+2], dp[i-1] + {i~i+2都被替换成第i+2个物品的花销})

此时一个直观的疑问是：问什么i,i+1,i+2都被替换成i+2这个物品，难道不可以只是第i个物品被替换成i+2这个物品，而第i+1个物品保持原样即不被i+2这个物品替换。

大家可以想象下，第i个物品和第i+2个物品很昂贵，而第i+1个物品很便宜。如下面这组数据：

//额定电压，电压源，每个灯泡的费用，数量

第i个物品：10,300,100,100

第i+1个物品：100,１,1,1

第i+2个物品：200,300,100,100

这样的话i,i+1,i+2都被替换成i+2,此时要：300+(100)*(100+1+100)

而i, i+2都被替换成i+2,而i+1保持不变，此时要：300+ 100*(100+100) + 1+1x1

此时发现后一种比前一种还要便宜，是不是我们将连续的一段如i,i+1,i+2都替换成i+2是错误的呢？

其实不是

大家接着思考一下，我们在更新dp[i+2]的时候，是不是dp[i+1]已经被更新过了，在更新dp[i+1]的时候已经把第i个物品替换成i+1这个物品了

此时虽然dp[i+2]从 {dp[i-1]这个状态 + 将i到i+2都替换成i+2这个物品}转移过来不是最优的，但是dp[i+2]也可以从dp[i+1]这个状态转移过来呀。

---

所以dp[i]在状态转移的时候，将连续的一段都替换成第i个物品是合理的，它不会丢失最优解。


```cpp
//
// created by **** on 2019-08-17
//

#include <bits/stdc++.h>

const int maxn = 1e3 + 10;
int n;
// 按额定电压排序后,dp[i]:表示前i个物品,以第i个物品结尾的最小费用
// 因为前i个物品中,排序后第i个物品的额定电压最大，所以它是不能被其他物品替换的，所以第i个物品
// 一定是结尾，这里只是显示的定义出来。
int dp[maxn],sum_[maxn];

struct node{
    // 额定电压,电压源,费用,数量
    int voltage_rating;
    int voltage_source;
    int cost;
    int number;
    // 额定电压从小到大排序
    const bool operator< (const node& rhs) const{
        return voltage_rating < rhs.voltage_rating;
    }
}A[maxn];

int main(){
    while(scanf("%d",&n) && n){
        memset(sum_, 0, sizeof sum_);
        memset(dp, 0x3f3f3f, sizeof dp);
        dp[0] = 0;
        for(int i=1;i<=n;++i){
            scanf("%d %d %d %d",&A[i].voltage_rating, &A[i].voltage_source, &A[i].cost, &A[i].number);
        }

        // 排序以及前缀和
        std::sort(A+1,A+1+n);
        for(int i=1;i<=n;++i){
            sum_[i] = sum_[i-1] + A[i].number;
        }
        // dp过程
        for(int i=1;i<=n;++i){
            for(int j=0;j<i;++j){
                dp[i] = std::min(dp[i], dp[j] + (sum_[i]-sum_[j])*A[i].cost + A[i].voltage_source);
            }
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}
```


---

## 作者：安静学习 (赞：9)

我看了一圈，似乎都只是说一下怎么做的，没有说为什么的，我觉得一个算法的正确性的证明还是很重要的，我来提一下吧。

首先一个灯泡要不然换，要不然不换，如果只换一部分，就会多处一个电源的费用。

将电压大到小排序，然后初步计算一下开销，然后d数组表示前i个灯泡的最少开销，因为一个灯泡要不然换，要不然就不换，所以每次考虑第j个灯泡换的时候，如果j换了可以减少开销，那么j+1，j+2等换了也可以减少开销。所以会用一个前缀和记录前i个灯泡总数量，这样就可以在O(n^2)中完成。

最佳的开销根据状态定义，自然就是d[n]

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
const int maxn = 1000 + 10;
int n;

int d[maxn], s[maxn];
struct Node{
    int v, k, c, l;
    bool operator < (const Node &a){
        return v < a.v;
    }
}elc[maxn];

int main(){
    while(cin >> n && n){
        for(int i = 1; i <= n; i++){
            scanf("%d%d%d%d", &elc[i].v, &elc[i].k, &elc[i].c, &elc[i].l);
        }
        sort(elc + 1, elc + n + 1);
        d[1] = elc[1].k + elc[1].c * elc[1].l;
        s[1] = elc[1].l;
        for(int i = 2; i <= n; i++){
            d[i] = d[i - 1] + (elc[i].k + elc[i].c * elc[i].l);
            s[i] = s[i - 1] + elc[i].l;
        }
        d[0] = 0;
        s[0] = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < i; j++){
                d[i] = min(d[i], d[j] + (s[i] - s[j]) * elc[i].c + elc[i].k);
            }
        }
        printf("%d\n", d[n]);
    }
    return 0;
}

```


---

## 作者：xiaohuang (赞：5)

### 题意描述：

一共有n种灯泡可供选择，不同种类的灯泡必须用不同的电源，没每种灯泡的花费不相同，求最小花费。

### 分析：

先把灯泡按照电压从小到大排序。

设sum[i]为前i种灯泡的总数量（即L值之和），d[i]为灯泡1～i的最小花费，

动态转移方程就是d[i]=min(d[j]+(sum[i]-sum[j])*c[i]+k[i])；

答案就是d[n]。
### AC代码：
```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std;
int n,i,v[1005],k[1005],c[1005],l[1005],sum[1005],dp[1005];
void qsort(int left,int right)//排序 
{
	int i,j,mid,t;
	i=left;
	j=right;
	mid=v[(left+right)/2];
	while (i<=j)
	{
		while (v[i]<mid) i++;
		while (v[j]>mid) j--;
		if (i<=j)
		{
			t=v[i]; v[i]=v[j]; v[j]=t;//把所有值都交换 
			t=k[i]; k[i]=k[j]; k[j]=t;
			t=c[i]; c[i]=c[j]; c[j]=t;
			t=l[i]; l[i]=l[j]; l[j]=t;
			i++; j--;
		}
	}
	if (left<j) qsort(left,j);
	if (i<right) qsort(i,right);
}
int main()
{
	while (true)
	{
		scanf("%d",&n);
		if (n==0) return 0;
		for (int i=1; i<=n; i++)
			scanf("%d%d%d%d",&v[i],&k[i],&c[i],&l[i]);//读入数据 
		qsort(1,n);
		for (int i=1; i<=n; i++)
			sum[i]=sum[i-1]+l[i];//求前缀和
		memset(dp,0x3f3f3f,sizeof(dp));//初始化
		dp[0]=0; 
		for (int i=1; i<=n; i++)
			for (int j=0; j<=i-1; j++)
				dp[i]=min(dp[i],dp[j]+(sum[i]-sum[j])*c[i]+k[i]);//dp方程 
		printf("%d\n",dp[n]);//输出答案dp[n] 
	}
}
```

---

## 作者：metaphysis (赞：3)

本题是一道动态规划题目。

题目允许使用具有更高适配电压的灯泡来替换较低适配电压的灯泡，直觉就是先将灯泡按照适配电压的高低递增排列，然后进行选择。

显然，电压最高的灯泡必须选择，因为没有其他灯泡可以代替它们。那么对于不是最高电压的灯泡，可以选，也可以不选，如果不选，可以使用更高电压的灯泡来替换。

令（按照灯泡适配电压从低到高的顺序）排序后第 $i$ 类灯泡的适配电源的价格为 $K[i]$，单个灯泡的价格为 $C[i]$，所需要的数量为 $L[i]$，为了便于讨论和表示，令 $SL[i]$ 为排序后前 $i$ 类灯泡所需数量的总和。

由于第 $n$ 类灯泡必须选择，对于第 $1$、$2$、…、$n-1$ 类灯泡，可以选择或者不选，假定在第 $1$、$2$、…、$n-1$ 类灯泡中，最后一次选择的是第 $i$ 类灯泡，那么对于第 $i+1$、…、$n-1$ 类灯泡来说，只能使用第 $n$ 类灯泡进行代替，如果令 $dp[i]$ 表示前 $i$ 类灯泡中最后选择第 $i$ 类灯泡时的最小费用，那么前 $n$ 类灯泡的最小费用 $dp[n]$ 为：

$$dp[n] = \min \{dp[i]+K[n]+(L[i+1]+ \dots +L[n-1]+L[n]) \times C[n]\}$$

亦即：

$$dp[n]=\min \{dp[i]+K[n]+(SL[n]-SL[i]) \times C[n]\}$$

而 $dp[i]$ 的求解与 $dp[n]$ 是类似的，属于重复的子问题，因此可以使用动态规划中的备忘技巧（将递归中已解决子问题的结果使用表格予以记录，当再次遇到此子问题时，直接查表获得结果），使用递归予以解决。

---

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
struct lamp {
    int V, K, C, L;
    bool operator<(const lamp &l) const { return V < l.V; }
} lamps[1010];
int sum[1010], dp[1010];
int dfs(int n) {
    if (n == 0) return 0;
    if (~dp[n]) return dp[n];
    int r = sum[n] * lamps[n].C;
    for (int j = 1; j < n; j++) r = min(r, dfs(j) + (sum[n] - sum[j]) * lamps[n].C);
    return dp[n] = r + lamps[n].K;
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++)
            cin >> lamps[i].V >> lamps[i].K >> lamps[i].C >> lamps[i].L;
        sort(lamps + 1, lamps + n + 1);
        sum[0] = 0;
        for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + lamps[i].L;
        memset(dp, -1, sizeof dp);
        cout << dfs(n) << '\n';
    }
    return 0;
}
```

---

## 作者：liability (赞：2)

开始刷紫书的题；

首先题意，参见紫书，{

  你的任务是设计一个照明系统，一共有n（n<=1000)种灯泡可供选择,不同种类的灯泡必须用不同的电源，同一种灯泡则可以用一个，输入为一个n，以下n行，每行四个数值，代表电压V，电源费用K，每个灯泡费用C，所需灯泡数量L。n=0为结束标志。
  
  为了省钱，你可以把一些灯泡换成电压更高的以节省电源的钱，但不能换成更低的，请你计算出最优方案的费用。
  
  }
  
  题意应该很清晰了吧，就是将一些灯泡换成电压更高的灯泡并且灯泡总数量不变，注意哪个L是指需要多少灯泡而不是只有多少灯泡。
  
  首先明确一个结论，一种灯泡要么全换要么全不换，因为如果只换部分的话会多花一个电源的钱。
  
  由此，**d[i]=min(d[i],d[j]+(s[i]-s[j])*c[i]+k[i])**
  s代表前i个灯泡所需总数。
    
```
#include<bits/stdc++.h>
using namespace std;
struct lamp {
    int v,k,c,l;
    bool operator < (const lamp & a) const {
        return v<a.v;
    }
} a[1005];
int n,s[1005],dp[1005];
int main() {
    while(cin>>n,n) {
        for(int i=1;i<=n;i++) cin>>a[i].v>>a[i].k>>a[i].c>>a[i].l;
        sort(a+1,a+1+n);//一定要先排序再求和，这个我调了好久才发现
        for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i].l;
        memset(dp,0x3f,sizeof(dp));
        dp[0]=0;
        for(int i=1;i<=n;i++) {
            for(int j=0;j<i;j++) {
                dp[i]=min(dp[i],dp[j]+(s[i]-s[j])*a[i].c+a[i].k);
            }
        }
        cout<<dp[n]<<endl;
    }
    return 0;
}
    
```

---

## 作者：ZHRRRRRR (赞：2)

这道题题目翻译有点问题...(或者是我理解能力比较弱）

**大概意思就是说可以把低伏的灯泡换成高伏的，但最后的方案中所有的灯泡种类都要买其对应的电源。
数据中就是把120的16个和100的20个全部换成220的还要再买18个220的和一个220的电源得到最少花费（不信的话可以自己算算）**

然后就是一个弱鸡dp。
先将灯泡从小到大或从大到小排序（节约时间复杂度）
对于任何一种灯泡k，需在枚举电压比他大的灯泡p比较两个量的大小：k的数量*k的价值和p的价值*k的数量（p的价值*k的数量+p的电源价格，视是否购买过电源而定）

具体dp方程见代码：

```cpp
//GSY Please don't copy my code.
//  Created by Henry Zhang on 2018/5/30
//  Copyright © 2018年 Henry Zhang. All rights reserved.
#include <bits/stdc++.h>
using namespace std;

int res=0,temp,use;
struct Light{
    int v,k,c,l,s;
}l[1001];

bool cmp(Light a,Light b){
    return a.v>b.v;
}

int main()
{
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)
        cin >> l[i].v >> l[i].k >> l[i].c >> l[i].l;
    sort(l+1,l+1+n,cmp);
    res+=l[1].l*l[1].c+l[1].k;
    l[1].s=1;
    for(int i=2;i<=n;i++){
        temp=l[i].c*l[i].l+l[i].k,use=i;
        for(int j=1;j<=i;j++){//dp方程
            if(l[j].s==1) temp=min(temp,l[j].c*l[i].l),use=0;
            if(l[j].s==0&&temp>l[j].c*l[i].l+l[j].k) temp=l[j].c*l[i].l+l[j].k,use=j;
        }
        res+=temp;l[use].s=1;
    }
    cout << res << endl;
}
//  Created by Henry Zhang on 2018/5/30
//  Copyright © 2018年 Henry Zhang. All rights 
```

---

## 作者：CRTL_xzh2009 (赞：1)

~~这有蓝吗~~

显然的线性 DP。

1. 先把所有数据按照电压值进行排序。

2. 设置数组 $dp$，令 $dp[i]$ 表示 $1 \sim i$ 的最小总价。

3. 转移方程：`dp[i]=min(dp[i], dp[j]+(sum[i]-sum[j])*p[i].c+p[i].k);`

其中，$sum[i]-sum[j]$ 表示从 $j+1$ 到 $i$ 的总数，$c_{i}$ 表示 $i$ 的单价，$k_{i}$ 表示电源 $i$ 的价格。

表示前 $j$ 个用 $dp[j]$，从 $j+1$ 到 $i$ 换成 $i$ 号电源。


```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=132005;
struct Lamps{
	int v, k, c, l;
}p[N];
bool cmp(Lamps a, Lamps b){
	return a.v < b.v;
}
int main(){
	int n;
    while(1)
    {
		scanf("%d", &n);
		if(n==0) exit(0);//遇到0退出 
		for (int i=1; i<=n; i++)//读入 
			scanf("%d %d %d %d", &p[i].v, &p[i].k, &p[i].c, &p[i].l);
		sort(p+1, p+1+n, cmp);
		int sum[N]={0}, dp[N]={0};//不怕空间的我！ 
		for (int i=1; i<=n; i++)
			sum[i]=sum[i-1]+p[i].l;
		for (int i=1; i<=n; i++){
			dp[i]=1<<30;
			for (int j=0; j<=i; j++)
				dp[i]=min(dp[i], dp[j]+(sum[i]-sum[j])*p[i].c+p[i].k);
		}
		printf("%d\n", dp[n]);
    }
	return 0;
}
```


---

## 作者：Jeremiahy (赞：1)

## 分析

首先可以得到一个结论：每种电压的灯泡要么全换，要么全不换。因为如果只换部分灯泡，如 $v=100$ 有两个灯泡，把其中一个换成 $v=200$ 的，另一个不变，则 $v=100$ 和 $v=200$ 两种电源都需要，不划算（若一个都不换则只需要 $v=100$ 一种电源）。

先把灯泡按照电压从小到大排序。设 $s_i$ 为前 $i$ 种灯泡的总数量（即 $l$ 值之和），$d_i$ 为灯泡 $1$ 到 $i$ 的最小开销，则状态转移方程如下：

$$d_i=\min \{d_j+(s_i-s_j)\times c_i+k_i\}$$

表示前 $j$ 个先用最优方案买，然后第 $j+1$ 到 $i$ 个都用第 $i$ 号的电源。

最终答案为 $d_n$。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, dp[1005], s[1005];
struct node{
    int v, k, c, l;//电压，电源花费，每个灯的费用，所需数量
    const bool operator< (const node& rhs) const{
        return v < rhs.v;//按电压排序
    }
}a[1005];
signed main(){
    while(cin >> n && n){
        memset(s, 0, sizeof(s));//初始化
        memset(dp, 0x3f3f3f3f, sizeof(dp));
        dp[0] = 0;
        for (register int i = 1; i <= n; i++)
            cin >> a[i].v >> a[i].k >> a[i].c >> a[i].l;
        sort(a + 1, a + 1 + n);//排序
        for (register int i = 1; i <= n; i++)//计算s[i](L值前缀和)
            s[i] = s[i - 1] + a[i].l;
        for (register int i = 1; i <= n; i++)
            for (register int j = 0; j < i; j++)
                dp[i] = min(dp[i], dp[j] + (s[i] - s[j]) * a[i].c + a[i].k);//状态转移
       	cout << dp[n] << '\n';
    }
    return 0;
}
```




---

## 作者：Weakest_Konjac (赞：1)

题目简述：
 给定n种灯泡的电压，电源费，每个灯泡的花费和需求量，用电压大的灯泡换小的灯泡，求最小花费

思路：首先排序，然后计算前i个灯泡总需求值，最后递推
```pascal
var a,b,c,d,f:array[0..1000] of longint;
       n,i,j:longint;
procedure sort(l,r:longint);//电压升序排列
var i,j,x,y:longint;
begin
 i:=l;j:=r;
 x:=a[(l+r) div 2];
 repeat
  while a[i]<x do inc(i);
  while x<a[j] do dec(j);
  if not(i>j) then
    begin
     y:=a[i];a[i]:=a[j];a[j]:=y;
     y:=b[i];b[i]:=b[j];b[j]:=y;
     y:=c[i];c[i]:=c[j];c[j]:=y;
     y:=d[i];d[i]:=d[j];d[j]:=y;
     inc(i);j:=j-1;
    end;
 until i>j;
if l<j then sort(l,j);
if i<r then sort(i,r);
end;
function min(x,y:longint):longint;
begin
if x<y then exit(x); exit(y);
end;
begin
 read(n);
 while n<>0 do//判断是否输入零
  begin
   for i:=1 to n do readln(a[i],b[i],c[i],d[i]);
    sort(1,n);
   for i:=1 to n do d[i]:=d[i-1]+d[i];//计算前缀和
   f[0]:=0;
    for i:=1 to n do
    begin
     f[i]:=maxlongint;//定义初始值
     for j:=0 to i do
      f[i]:=min(f[i],f[j]+(d[i]-d[j])*c[i]+b[i]);//递推
    end;
    writeln(f[n]);//输出
     readln(n);
  end;
end.
```

---

