# Cleaning the Phone

## 题目描述

Polycarp often uses his smartphone. He has already installed $ n $ applications on it. Application with number $ i $ takes up $ a_i $ units of memory.

Polycarp wants to free at least $ m $ units of memory (by removing some applications).

Of course, some applications are more important to Polycarp than others. He came up with the following scoring system — he assigned an integer $ b_i $ to each application:

- $ b_i = 1 $ — regular application;
- $ b_i = 2 $ — important application.

According to this rating system, his phone has $ b_1 + b_2 + \ldots + b_n $ convenience points.

Polycarp believes that if he removes applications with numbers $ i_1, i_2, \ldots, i_k $ , then he will free $ a_{i_1} + a_{i_2} + \ldots + a_{i_k} $ units of memory and lose $ b_{i_1} + b_{i_2} + \ldots + b_{i_k} $ convenience points.

For example, if $ n=5 $ , $ m=7 $ , $ a=[5, 3, 2, 1, 4] $ , $ b=[2, 1, 1, 2, 1] $ , then Polycarp can uninstall the following application sets (not all options are listed below):

- applications with numbers $ 1, 4 $ and $ 5 $ . In this case, it will free $ a_1+a_4+a_5=10 $ units of memory and lose $ b_1+b_4+b_5=5 $ convenience points;
- applications with numbers $ 1 $ and $ 3 $ . In this case, it will free $ a_1+a_3=7 $ units of memory and lose $ b_1+b_3=3 $ convenience points.
- applications with numbers $ 2 $ and $ 5 $ . In this case, it will free $ a_2+a_5=7 $ memory units and lose $ b_2+b_5=2 $ convenience points.

Help Polycarp, choose a set of applications, such that if removing them will free at least $ m $ units of memory and lose the minimum number of convenience points, or indicate that such a set does not exist.

## 说明/提示

In the first test case, it is optimal to remove applications with numbers $ 2 $ and $ 5 $ , freeing $ 7 $ units of memory. $ b_2+b_5=2 $ .

In the second test case, by removing the only application, Polycarp will be able to clear only $ 2 $ of memory units out of the $ 3 $ needed.

In the third test case, it is optimal to remove applications with numbers $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , freeing $ 10 $ units of memory. $ b_1+b_2+b_3+b_4=6 $ .

In the fourth test case, it is optimal to remove applications with numbers $ 1 $ , $ 3 $ and $ 4 $ , freeing $ 12 $ units of memory. $ b_1+b_3+b_4=4 $ .

In the fifth test case, it is optimal to remove applications with numbers $ 1 $ and $ 2 $ , freeing $ 5 $ units of memory. $ b_1+b_2=3 $ .

## 样例 #1

### 输入

```
5
5 7
5 3 2 1 4
2 1 1 2 1
1 3
2
1
5 10
2 3 2 3 2
1 2 1 2 1
4 10
5 1 3 4
1 2 1 2
4 5
3 2 1 2
2 1 2 1```

### 输出

```
2
-1
6
4
3```

# 题解

## 作者：jianhe (赞：3)

[CF1475D Cleaning the Phone](https://www.luogu.com.cn/problem/CF1475D)
题解

本文同步发表于 [`CSDN`](https://blog.csdn.net/weixin_38337678)~

### 前言：

一开始没看到 $m$ 的范围，往背包去想了。我在这里提醒大家：做题前要好好看数据范围，先判断自己的算法时间复杂度对不对，再写代码。否则又会重蹈覆辙了。

这道题其实不难，只是很容易想成动态规划。也许这道题为绿的原因就是数据范围（算法选择）上的困难了。

### 算法：贪心

注意：$1 \le m \le 10^9$。

动态规划肯定超时了，就往贪心方面去想。

又注意到 $b$ 的取值只能为 $1$ 或 $2$，比较特殊，就从中入手。

当总价值 $< m$ 时，肯定不成立，直接输出。

接下来贪心：

因为 $1+1=2$，所以我们可以通过两个体积为 $1$ 的物品与一个体积为 $2$ 的物品（总体积一样）比较价值大小来取。

因此输入时应该根据体积来分别保存到两个数组中，并且排序（从大到小）。之后就可以按照以上步骤来贪心啦~

### 代码：

代码并不难实现，只是要注意多测要清空！

多测不清空，爆零两行泪。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=2e5+10;
ll T,n,m,a[N],b,t1,t2,q1[N],q2[N],ct,ans,h1,h2;
bool cmp(ll l,ll r){
	return l>r;
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		t1=t2=ct=ans=0,h1=h2=1;
		for(int i=1;i<=n;i++){
			cin>>b;
			if(b==1) q1[++t1]=a[i];
			else q2[++t2]=a[i];
		}
		sort(q1+1,q1+t1+1,cmp);
		sort(q2+1,q2+t2+1,cmp);
		while(ct<m){//贪心取最大值
			if(!q1[h1]&&!q2[h2]){ans=-1;break;}//q1和q2都取完了,总价值还没达到m
			if(ct+q1[h1]>=m){ans++;break;}//取q1[h1]后达到
			if(q1[h1]+q1[h1+1]>=q2[h2]) ct+=q1[h1++],ans++;//取q1
			else ct+=q2[h2++],ans+=2;//取q2
		}
		cout<<ans<<"\n";
		for(int i=1;i<=n;i++) q1[i]=q2[i]=0;
	}
	return 0;
}

```

---

## 作者：Cutest_Junior (赞：3)

## 题解 CF1475D 【Cleaning the Phone】

### 题意

+ $n$ 个物品；
+ 每个物品有价值 $a$ 和体积 $b$；
+ 求价值和至少为 $m$ 时，体积和的最小值；
+ 多组数据，$n\le2\times10^5$，$a,m\le10^9$，$1\le b\le2$。

### 做法

Virtual participation 的时候就注意到了 $b$ 的大小的特殊性，但还是只想出朴素的 $O(N^2)$ 背包。

然后想了一晚上，想出了下面的做法，果然我是事后诸葛。

对于 $b$ 相同的物品，具有单调性，即若 $b_i=b_j$，且 $a_i>a_j$，则 $i$ 一定比 $j$ 先选（~~这个不用证了吧~~）。

按 $b$ 分为两类，分别排序。

根据单调性，我们每次只要考虑剩下的物品中最大的一个 $b=2$ 的物品和最大的两个 $b=1$ 的物品。

1. 若选了最大的 $b=1$ 的物品就达到 $m$ 了，就直接选（~~也不需要证明吧~~）；
1. 若最大的 $b=2$ 的物品价值大于等于最大的两个 $b=1$ 的物品的价值之和，那就选（反证法，因为选完一个 $b=1$ 的物品后一定要继续选，选完两个后替换成 $b=2$ 的那个物品显然更优）；
1. 同理，若最大的两个 $b=1$ 的物品价值之和大于最大的 $b=2$ 的物品价值，就选 $b=1$ 的那两个物品。

~~为什么这么显然的贪心我考场上每想出来啊/dk。~~

### 代码

```cpp
#include <cstdio>
#include <iterator>
#include <algorithm>
#include <cstring>
 
using namespace std;
 
const int N = 2e5 + 5;
 
int arr[N];
int que1[N], tot1;
int que2[N], tot2;
 
void run() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &arr[i]);
	}
	for (int i = 1; i <= n; ++i) {
		int x;
		scanf("%d", &x);
		if (x == 1) {
			que1[tot1] = arr[i];
			++tot1;
		}
		else {
			que2[tot2] = arr[i];
			++tot2;
		}
	}
	sort(que1, que1 + tot1, greater<int>());
	sort(que2, que2 + tot2, greater<int>());
	int cnt1 = 0, cnt2 = 0;
	int h1 = 0, h2 = 0;
	while (cnt1 < m) {
		if (que1[h1] == 0 && que2[h2] == 0) {
			cnt2 = -1;
			break;
		}
		if (cnt1 + que1[h1] >= m) {
			++cnt2;
			break;
		}
		if (que2[h2] >= que1[h1] + que1[h1 + 1]) {
			cnt1 += que2[h2];
			cnt2 += 2;
			++h2;
		}
		else {
			cnt1 += que1[h1];
			++cnt2;
			++h1;
		}
	}
	printf("%d\n", cnt2);
	tot1 = 0, tot2 = 0;
	memset(que1, 0, sizeof que1);
	memset(que2, 0, sizeof que2);
}
 
int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		run();
	}
}
```

---

## 作者：do_while_true (赞：2)

# [D](https://codeforces.com/contest/1475/problem/D)

### $\mathcal{Translate}$

现在有 $n$ 个物品，第 $i$ 个重量为 $a_i$，代价为 $b_i$。

现在要挑选出若干个物品，使其重量和 $\geq m$，并且代价最小，输出这个代价。

$1\leq n\leq 2\times 10^5,1\leq m\leq 10^9$

$1\leq a_i\leq 10^9,1\leq b_i\leq 2$

### $\mathcal{Solution}$

注意到 $b_i$ 只有 $1,2$ 是突破点，考虑类似于折半搜索的思想，把 $b_i=1,2$ 的分开来。

各自根据 $a$ 从大到小排序，这样各选一个前缀肯定是更优的，枚举选 $b_i=1$ 的个数，然后在 $b_i=2$ 的里面二分一个最小的前缀满足他们的和 $>m$ 即可。

所有可能取最小值即为答案。

### [$\mathcal{Code}$](https://codeforces.com/contest/1475/submission/105836312)

---

## 作者：Carotrl (赞：2)

### 简化题意：

有 $n$ 个物品和一个最低价值 $m$，每一个物品有一个价值 $a_i$ 和 体积 $b_i$，体积只有可能为 $1$ 或 $2$。你需要选出几个物品，使得它们的价值大于等于 $m$ 且使体积最小。

### 大致做法：

第一眼像个背包，但 $m$ 的范围 $\le10^9$ 将我们的空想打破。

我们尝试把体积为 $1$ 和为 $2$ 的物品分开。要使体积最小，则要使得体积相同的物品价值最大（贪心），我们把两个数组都从大到小排序，分别算出前缀和。

然后可以枚举用多少体积为 $1$ 的物品。这几个物品最大得到的价值可以由前缀和直接得到。算出至少还需要多少价值，对体积为 $2$ 的前缀和数组进行二分，找到第一个大于等于还需价值的位置，即可算出这次的体积，枚举找到最小值。

### code:

```cpp
#include<cstdio>
#include<algorithm>
#include<string>
using namespace std;
struct P{
    int x,v;
}q1[200005],q2[200005];
bool cmp(P p,P q){
	return p.v>q.v;
}
void in(int &x){
	int f=1;x=0;
	char c=getchar();
	while(!isdigit(c)&&c!='-')c=getchar();
	if(c=='-')f=-1,c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	x*=f;
}
void out(int x){
	if(x<0)putchar('-'),x=-x;
	if(x>9)out(x/10);
	putchar(x%10+'0');
}
long long sum1[200005],sum2[200005];
int t,n,m,x,v,n1,n2,a[200005],b[200005];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        n1=0;n2=0;
        for(int i=1;i<=n;i++)in(a[i]);
        for(int i=1;i<=n;i++)in(b[i]);
        for(int i=1;i<=n;i++){
            if(b[i]==1)q1[++n1].v=a[i],q1[n1].x=1;
            else q2[++n2].v=a[i],q2[n2].x=2;
        }
        sort(q1+1,q1+n1+1,cmp);
        sort(q2+1,q2+n2+1,cmp);
        sum1[0]=0;sum2[0]=0; 
        for(int i=1;i<=n1;i++)sum1[i]=sum1[i-1]+q1[i].v;
        for(int i=1;i<=n2;i++)sum2[i]=sum2[i-1]+q2[i].v;
        if(sum1[n1]+sum2[n2]<m){
        	puts("-1");continue;
		}
        long long ans=0x3f3f3f3f;
        for(int i=0;i<=n1;i++){
			long long sum=i; 
			long long now=m-sum1[i];
			int k=0;
			if(now>0){
			    k=lower_bound(sum2+1,sum2+1+n2,now)-sum2;
				if(k>n2)continue;
			}
			sum+=k*2;
			ans=min(ans,sum);
		}
		if(ans==0x3f3f3f3f)printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
```


---

## 作者：hytallenxu (赞：1)

## 前言
练习二分的好题，CF *1800。

## 正文
给定 $n \text{ }(1 \leq n \leq 10^5)$ 个东西，每个东西有能力值 $a_i$，以及一个损耗值 $b_i \in {1, 2}$，问在能力值大于 $m$ 的情况下损耗值最小是多少。

看“最小”，就应该有一个二分的思路。

我们可以先从损耗值下手。

因为损耗值只有 $2$ 个数，所以我们可以分别开两个数组 $x, y$，代表损耗值（$x$ 表示损耗值为 $1$，$y$ 表示损耗值为 $2$），存储每个能力值。

显然，我们要尽可能的多用 $x$ 数组里的值，这样才能让损耗值最小。

其实，我们要对 $x, y$ 里面的能力值**由大到小排序**，这样就能确保在损耗值最小的情况下尽可能的最大化总的能力值，使得它**大于等于**题目给定的限制 $m$。

于是，我们可以枚举使用 $x$ 数组中（损耗值为 $1$）的能力值的数量，并用二分一下 $y$ 数组中能否凑出来与这个能力值的差距即可。

每次枚举的答案即为 $i + 2 \times l$，其中 $i$ 是使用 $1$ 的数量，$l$ 是二分得出的使用 $2$ 的数量。

注意 corner case，包括凑不出来的情况，以及只使用 $1$ 或 $2$ 就可以满足 $m$ 的情况。 （笔者就是在这里被卡了一下。）

## Code
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define int long long

void solve(){
	int n,m;
	cin>>n>>m;
	vector<int> e(n);
	vector<int> a,b;
	for(int i=0;i<n;i++) cin>>e[i];
	for(int i=0;i<n;i++){
		int x;cin>>x;
		if(x==1) a.push_back(e[i]);
		else b.push_back(e[i]);
	}
	sort(a.rbegin(),a.rend());
	sort(b.rbegin(),b.rend());
	int ans=1e18,curSumA=0;
	vector<int> sum(b.size()+1);
	for(int i=0;i<b.size();i++){
		sum[i+1]=b[i]+sum[i];
	}
	auto check=[&](int x, int diff){
		return sum[x]>=diff;
	};
	
	for(int i=0;i<=n;i++){
		int diff=m-curSumA;
		if(diff<0){
			ans=min(ans,i);
			break;
		}
		int l=0,r=b.size();
		while(l<r){
			int mid=(l+r)>>1;
			if(check(mid,diff)) r=mid;
			else l=mid+1;
		}
		//cout<<i<<" "<<l<<"****\n";
		if(sum[l]>=diff) ans=min(ans,i+2*l);
		if(i<a.size()) curSumA+=a[i];
	}
	cout<<(ans==1e18?-1:ans)<<endl;
}

signed main(){
	cin.tie(nullptr)->sync_with_stdio(0);
	int t;cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：furina_1013 (赞：1)

### 题目大意
有 $n$ 个物品，每个物品分别有价值 $a_i$ 与重量 $b_i$（$b_i \in\{1，2\}$)。

问，最少用多少重量可以让价值大于 $m$。

### 思路

因为 $b \in \{1,2\}$ 我们考虑创建两个数组 $fu$ 与 $fu2$，加入数后从小到大排序，保证单调递增。

$fu_i$ 表示第 $i$ 珍贵的重量为 $1$ 的物品。

$fu2_i$ 表示第 $i$ 珍贵的重量为 $2$ 的物品。

因为要保证重量最小，我们考虑贪心思想，每一次选择性价比最高的物品，定义两个计数器 $i$、$j$，
加进选择总和 $zt$ 中，再累加答案 $zl$。

注意几个特殊情况：
1. 如果总和 $<m$ 输出 $-1$ 。
2. 如果 $zt\ge m$ 输出 $zl$。
3. 如果 $zt+fu_i \ge m$ 输出 $zl+1$。

### code：


```cpp
#include <bits/stdc++.h>
using namespace std;
int fu[200005],fu2[200005];//两个数组
int t, n, m, a[200005],zt, zl;//a数组
long long sum;//最好开long long
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//一个读写优化
	cin >> t;
	while (t--)//t次测试
	{
		zt=0;
		zl=0;
		sum=0;
		cin >> n >> m;
		for (int i = 1; i <= n; i++){
			cin >> a[i];
			sum += a[i];
		}
		int flag=1;//fu的指示器
		int flag2=1;//fu2的指示器
		for (int i=1;i<=n;i++){
			int t;
			cin>>t;
			if(t==1){
				fu[flag]=a[i];
				flag++;
			}
			if(t==2){
				fu2[flag2]=a[i];
				flag2++;
			}
		}//分重量存储
		if(sum<m){
			cout<<"-1"<<"\n";
			continue;
		}//不可能达成
		sort(fu+1,fu+flag);//排序
		sort(fu2+1,fu2+flag2);
		for (int i=flag-1,j=flag2-1;;)
		{
			if(zt>=m)
			{
				cout<<zl<<"\n";
				break;
			}//达到m
			if(zt+fu[i]>=m)
			{
				cout<<zl+1<<"\n";
				break;
			}//再加一个数就达到m，若不判断此条件，下一步时 fu2[j]>=fu[i]+fu[i-1]就会多加重量
			if(fu2[j]>=fu[i]+fu[i-1])//从后向前，因为后面的较大
			{
				zt+=fu2[j];
				zl+=2;
				j--;
			} 
			else if(fu[i]+fu[i-1]>fu2[j])
			{
				zt+=fu[i];
				zl++;
				i--;
			}
		}	
	}
	return 0;
}
```
完了

---

## 作者：__int127 (赞：0)

## CF1475D Cleaning the Phone 题解

[**题目传送门**](https://www.luogu.com.cn/problem/CF1475D)

### 题目大意

本题有多组数据。

有 $n$ 个物品和最低价值 $m$，对于第 $i$ 个物品，有它的价值 $a_i$ 和它的重量 $b_i$（$b_i$ 只可能是 $1$ 或 $2$，即 $b_i\in{\{1,2\}}$）。

你可以选取一些物品（可以全选），使得它们的价值之和 $\ge m$，且重量之和最小，输出重量，如无论如何选取也无法使价值之和 $\ge m$，输出 `-1`。

$1\le T\le10^4,1\le \sum n\le2\times10^5,1\le a_i\le10^9,b_i\in{\{1,2\}}$。

### 思路

可以发现，两个重量是 $1$ 的物品与一个重量是 $2$ 的物品的重量相等。~~（这不废话吗）~~

那么我们就可以先将 $b$ 数组分类，将重量是 $1$ 的存入 $b1$（程序里是 ```b_1```），将重量是 $2$ 的存入 $b2$（程序里是 ```b_2```），先将两个数组分别排序，由于两个重量是 $1$ 的物品与一个重量是 $2$ 的物品的重量相等，以可以将 $b1_i+b1_{i-1}$（$i$ 初始为重量为 $1$ 的物品数量）与 $b2_j$（$j$ 初始为重量为 $2$ 的物品数量）进行比较，如果 $b1_i+b1_{i-1}>b2_j$，就将价值变量 $sum$ 加 $b1_i$，使重量变量 $z$ 加 $1$，因为有可能加 $b1_i$ 就够了；否则 $sum$ 加 $b2_j$，$z$ 加 $2$，直到 $sum\ge m$，输出 $z$。

判断是否输出就更简单了，只要将 $a_i$ 全部加起来，如果全部加起来也 $<m$，就说明无论如何选取也无法使价值之和 $\ge m$，输出 `-1` 就可以了。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int b_1[200005], b_2[200005];
int t, n, m, a[200005], s, zl;
long long sum;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin >> t;
	while (t--){
		cin >> n >> m;
		for (int i = 1; i <= n; i++){
			cin >> a[i];
			sum += a[i];
		}
		int j = 1, k = 1;
		for (int i = 1; i <= n; i++){
			int t;
			cin >> t;
			if (t == 1){
				b_1[j] = a[i];
				j++;
			}
			if (t == 2){
				b_2[k] = a[i];
				k++;
			}
		}
		if (sum < m){
			cout << "-1\n";
			sum = 0;
			continue;
		}
		sort(b_1 + 1, b_1 + j);
		sort(b_2 + 1, b_2 + k);
		for (int i = j - 1, l = k - 1; ;){
			if (s >= m){
				cout << zl << "\n";
				break;
			}
			if (s + b_1[i] >= m){
				cout << zl + 1 << "\n";
				break;
			}
			if (b_2[l] >= b_1[i] + b_1[i - 1]){
				s += b_2[l];
				zl += 2;
				l--;
			} else if (b_1[i] + b_1[i - 1] > b_2[l]){
				s += b_1[i];
				zl++;
				i--;
			}
		}
		s = zl = sum = 0;
	}
	return 0;
}
```

### 最后

本题题解到此结束，希望大家能看懂、有思路。

---

## 作者：wz20201136 (赞：0)

### 题意
有 $n$ 个物品和一个最低价值 $m$，每一个物品有一个价值 $a_i$ 
  和体积 $b_i$，$b_i$ 只可能为 $1$ 和 $2$，求得到价值 $m$ 的最小体积。
### 题解
不难发现，当体积相等时，优先选择价值更多的。于是我们预处理出 $b_i$ 为 $1$ 和 $2$ 的体积，按价值从大到小排序，暴力枚举选体积为 $1$ 的数量，然后二分出需要体积为 $2$ 的物品的最小数量。
### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int s1[200005],s2[200005],b1[200005],b2[200005],n1,n2,t,n,a[200005],y,m,ans;
bool cmp(const int &x,const int &y)
{
	return x>y;
}
signed main()
{
	ios::sync_with_stdio(0);
	cin>>t;
	while(t--)
	{
		n1=n2=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>a[i];
		for(int i=1;i<=n;i++)
		{
			cin>>y;
			if(y==1) b1[++n1]=a[i];
			else b2[++n2]=a[i];
		}
		ans=INT_MAX;
		sort(b1+1,b1+n1+1,cmp);
		sort(b2+1,b2+n2+1,cmp);
		for(int i=1;i<=n1;i++) s1[i]=s1[i-1]+b1[i];//前缀和以便二分时O(1)检查
		for(int i=1;i<=n2;i++) s2[i]=s2[i-1]+b2[i];
		if(s1[n1]+s2[n2]<m)
		{
			cout<<"-1\n";
			continue;
		}
		for(int i=0;i<=n1;i++)
		{
			int l=0,r=n2,find=INT_MAX;
			while(l<=r)
			{
				int mid=(l+r)/2;
				if(s1[i]+s2[mid]>=m) find=mid,r=mid-1;
				else l=mid+1;
			}
			ans=min(ans,i+find*2);
		}
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：_Dreamer_ (赞：0)


[传送门](https://www.luogu.com.cn/problem/CF1475D)


看第一眼  这不就是个背包么  看了看数据范围  ~~直接左转题解~~ 

显然背包的复杂度 并不能承受这个题的范围

注意到题目中的 $b_i\in\{1,2\}$ 考虑从这里入手

有一个比较显然的贪心策略

- 如果 体积相同的两个物品 优先考虑价值大的
- 对于两个体积为 $1 $ 的物品 如果相加没有某一个体积为 $2$ 的物品价值大  将两者替换策略不会更差

以这两点为基础  尝试贪心

- 对体积为 $ 1 $ , $2 $ 的物品分别降序排序
- 每次操作考虑 两个价值最大的 $1$ 体积物品 和 一个价值最大的 $2 $ 体积物品  如果 $1$ 体积物品的价值和较大  则选择其中较大的那个加入 答案  否则选择体积为二的那个

其他细节看代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int T;
int n,m;
int b1[N],b2[N];
int a[N];
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		memset(a,0,sizeof a);
		memset(b1,0,sizeof b1);
		memset(b2,0,sizeof b2);
		scanf("%d%d",&n,&m);
		long long sum=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a[i]);sum+=a[i];
		}
		for(int i=1;i<=n;i++)
		{
			int x;scanf("%d",&x);
			if(x==1)b1[++b1[0]]=a[i];
			else 	b2[++b2[0]]=a[i];
		}
		if(sum<m)
		{
			puts("-1");continue;
		}
		sort(b1+1,b1+1+b1[0]);reverse(b1+1,b1+1+b1[0]);
		sort(b2+1,b2+1+b2[0]);reverse(b2+1,b2+1+b2[0]);
		int ans=0;
		int h1=1,h2=1;
		while(m>0)
		{
			if(m-b1[h1]<=0)
			{
				ans++;
				m-=b1[h1++];
			}
			else if(b2[h2]>=b1[h1]+b1[h1+1])
			{
				ans+=2;m-=b2[h2++];
			}
			else
			{
				ans+=1;m-=b1[h1];
				h1+=1;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

## 作者：冰糖鸽子 (赞：0)

upd：LaTeX出锅

当成DP浪费了好多时间呜呜呜

----

肯定很多人都认为是 DP 吧，但其实不是的。因为 $convenience \  points $ （以下称为 $v$  或 $v_i$ ）只可能是 $1$ 或 $2$ ，所以本题其实是一个简单的贪心 + 二分。

首先，读入后把 $v$ 为 $1$ 和 $v$ 为 $2$ 的分开，再分别排序。这样，我们就得到了两个 **如果选择了其中的一些值，那一定是连续选择，且一定选择第一个** 的数组。

枚举 **卸载几个 $v$ 为 $1$ 的应用** ，前缀和记录这时释放的内存（$sum$）（不用单独一个循环求出，边枚举边计算就可以）。此时，$sum \ge m$ ，$ans$ 与 $i$（也就是卸载了几个 $v$ 为 $1$ 的应用）取 $\min$ ，并跳出循环（因为后面无论如何都找不到更优解了）。

否则，设 $x$ 为 $m - sum$ ，**在 $v$ 为 2 的数组的前缀和中二分出第一个大于等于 $x$ 的位置**，将 $ans$ 与答案 $\times 2$ 取 $\min$。（因为二分出的答案就是最少要卸载几个 $v$ 为 $2$ 的应用才能释放出 $\ge x$ 的内存，而因为 $v=2$ ，所以要 $\times  2$ ）。

最后输出 $ans$ 即可，还要判一下若 $ans$ 还是极大值的话就输出 $-1$ （无解）

记得开 `long long` ！

代码：

```cpp

// Problem: CF1475D Cleaning the Phone
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1475D
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <bits/stdc++.h>
using namespace std;
#define M 200005
#define int long long
int T,n,m,f[M],sum2,sum,V,STwo[M],ans,cnt1,cnt2,One[M],Two[M];
int done(int x)
{
	/*lower_bound解决一切(虽然好像并不用这么麻烦但是管他呢)*/
	int k=lower_bound(STwo+1,STwo+1+cnt2,x)-STwo;
	return k*2;
}
void Reset()
{
	cnt2=cnt1=sum2=sum=0;
	ans=1000000005;
}
bool cmp(int a,int b)
{
	return a>b;
}
signed main()
{
	cin>>T;
	while(T--)
	{
		Reset();//多组数据标配
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>f[i];
		}
		for(int i=1;i<=n;i++)
		{
			cin>>V;
			if(V==1)
			{
				cnt1++;
				One[cnt1]=f[i];
			}
			else
			{
				cnt2++;
				sum2+=f[i];
				Two[cnt2]=f[i];
			}
		}
		sort(One+1,One+1+cnt1,cmp);
		sort(Two+1,Two+1+cnt2,cmp);
		for(int i=1;i<=cnt2;i++)
		{
			STwo[i]=STwo[i-1]+Two[i];
		}
		for(int i=0;i<=cnt1;i++)/*枚举删多少个便利点为1的应用，注意是从0开始枚举*/
		{
			sum+=One[i];
			if(sum2<(m-sum))
			{
				continue;
			}
			if(sum>=m)
			{
				ans=min(ans,i);
				break;
			}
			ans=min(ans,i+done(m-sum));
		}
		cout<<(ans==1000000005?-1:ans)<<endl;
	}
	return 0;
}
```

---

