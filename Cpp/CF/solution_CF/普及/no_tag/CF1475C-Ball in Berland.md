# Ball in Berland

## 题目描述

### 题意
在毕业典礼上，有 $a$ 个男孩和 $b$ 个女孩准备跳舞，不是所有的男孩和女孩都准备结伴跳舞。


现在你知道 $k$ 个可能的舞伴，你需要选择其中的两对，以便使没有人重复地出现在舞伴里，求可能的数量。

## 说明/提示

$1 \leq t \leq 10^4$

$1\leq a,b,k \leq 2\cdot 10^5$

## 样例 #1

### 输入

```
3
3 4 4
1 1 2 3
2 3 2 4
1 1 1
1
1
2 2 4
1 1 2 2
1 2 1 2```

### 输出

```
4
0
2```

# 题解

## 作者：_lxy_ (赞：5)

### 题意
有 $a$ 个男孩，$b$ 个女孩，组成了 $k$ 对舞伴，问选出这 $k$ 对舞伴中的两对且两对舞伴中的 $4$ 个人互不相同的方法数。
### 分析
假设第 $i$ 对舞伴由男孩 $a[i]$ 和女孩 $b[i]$ 组成，用 $cnta[a[i]]$ 和 $cntb[b[i]]$ 分别记录 $a[i]$ 号男生出现的次数和 $b[i]$ 号女生出现的次数。

![](https://cdn.luogu.com.cn/upload/image_hosting/1ibcm30v.png?x-oss-process=image/resize,m_lfit,h_425,w_562)

根据上图，不难发现，与第 $i$ 对舞伴能组成符合要求的两对舞伴的个数就是总舞伴数减去和 $a[i]$ 重复的、和 $b[i]$ 重复的，再加上 $a[i]$ , $b[i]$ 都重复的一对 $($ 因为重复减了 $)$，即 $k-cnta[a[i]]-cntb[b[i]]+1$，最后因为每对舞伴都重复计算了一遍，所以答案要除以 $2$。

### 代码
```cpp
#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int inf=1e9+7;
const int MAXN=2e5+7;
ll T,n,m,k,a[MAXN],b[MAXN],cnta[MAXN],cntb[MAXN],ans;
int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%lld",&T);
	while(T--)
	{
		mem(cnta,0);
		mem(cntb,0);
		ans=0;
		scanf("%lld%lld%lld",&n,&m,&k);
		ll i;
		for(i=0;i<k;i++)
		{
			scanf("%lld",&a[i]);
			cnta[a[i]]++; //cnta[i]表示i号男生在舞伴中出现的次数
		}
		for(i=0;i<k;i++)
		{
			scanf("%lld",&b[i]);
			cntb[b[i]]++; //cntb[i]表示i号女生在舞伴中出现的次数
		}
		for(i=0;i<k;i++)
		{
			ans+=k-cnta[a[i]]-cntb[b[i]]+1; //计算和每一对舞伴能组成2对舞伴的舞伴数
		}
		ans/=2; //因为有重复
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：Cult_style (赞：1)

~~看了大概5遍才看懂题意。~~

第$i$个男生用$a[i].x$表示，第$i$个女生用$a[i].y$表示。

用$vis$_$a[i]$表示$i$前面出现过多少次$a[i].x$
  
用$vis$_$b[i]$表示$i$前面出现过多少次$a[i].y$

我们能选的就是不重复的，即$vis[a[i].x]$和$vis[a[i].y]$为$0$的。

再用容斥原理。
```
int p=vis_a[a[i].x];
int q=vis_b[a[i].y];
if(p+q==0) ans+=(i-1);		
else ans=ans+(i-1)-(p+q)+tot;
```

$i-1$是因为前面的数都能选，$p$和$q$是不能选的

$tot$表示的是重复计算的，即$p$和$q$的可能表示了同样的需要去掉的数，那样会算两遍，所以要加上一个值，处理方式可见代码。



```
#include<bits/stdc++.h>
#define MN 1000005
#define ll long long
using namespace std;
struct node{
	int x,y;
}a[MN];
int vis_a[MN],vis_b[MN];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int x,y,n;
		scanf("%d%d%d",&x,&y,&n);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i].x);
		for(int i=1;i<=n;++i)
			scanf("%d",&a[i].y);
		for(int i=1;i<=max(x,y);++i)
			vis_a[i]=vis_b[i]=0;
		ll ans=0;
		int tot=0;
		for(ll i=1;i<=n;++i){
			if(!(a[i].x==a[i-1].x&&a[i].y==a[i-1].y))
				tot=0;
			int p=vis_a[a[i].x];
			int q=vis_b[a[i].y];
			if(p+q==0) ans+=(i-1);		
			else ans=ans+(i-1)-(p+q)+tot;
			vis_a[a[i].x]++;
			vis_b[a[i].y]++;
			tot++;
		}
		printf("%lld\n",ans);
	}
	
	return 0;
}   
```


---

## 作者：Cutest_Junior (赞：1)

## 题解 CF1475C 【Ball in Berland】

### 题意

+ $k$ 对舞伴，每对有一个男孩和一个女孩，给出双方的编号；
+ 选出两对舞伴，要求任何人不能同时出现在两对舞伴中；
+ 求有多少种选法；
+ 多组数据，$k,\text{男女编号}\le2\times10^5$。

### 做法

容易想到对于每对舞伴，判断有多少对舞伴和这一对没有重复的人，统计答案，最后除以 $2$。

这个操作不难，可以用 $k$ 减去这个男孩的舞伴个数和这个女孩的舞伴个数，可以桶排维护，根据容斥定理，当前这个舞伴会被减去两次，需要加上 $1$。 

然后注意最多的情况是任意两对都没有重复，答案是 $k^2$ 级别的，会爆 long long，我 Virtual participation 的时候就这样没调出来。

### 代码

```cpp
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int N = 2e5 + 5;

int boy[N], girl[N];
int cnta[N], cntb[N];

void run() {
	memset(cnta, 0, sizeof cnta);
	memset(cntb, 0, sizeof cntb);
	int a, b, k;
	scanf("%d%d%d", &a, &b, &k);
	for (int i = 1; i <= k; ++i) {
		scanf("%d", &boy[i]);
		++cnta[boy[i]];
	}
	for (int i = 1; i <= k; ++i) {
		scanf("%d", &girl[i]);
		++cntb[girl[i]];
	}
	ll ans = 0;
	for (int i = 1; i <= k; ++i) {
		ans += k - cnta[boy[i]] - cntb[girl[i]] + 1;
	}
	printf("%lld\n", ans / 2);
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

## 作者：WsW_ (赞：1)

# 1.暴力枚举 $O(t \times n^2)$ 。
双重循环枚举判断即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,ans,x,boy[200005],girl[200005];
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&x);
		scanf("%lld%lld",&x,&n);
		for(int i=1;i<=n;i++)scanf("%lld",&boy[i]);
		for(int i=1;i<=n;i++)scanf("%lld",&girl[i]);
		ans=0;
		for(int i=1;i<=n;i++){
			for(int j=i+1;j<=n;j++){
				if(boy[i]!=boy[j]&&girl[i]!=girl[j])ans++;//枚举每一对
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
# 2.排列组合+容斥原理 $O(t \times n)$。
先求出每个人重复了几次，然后用小奥排列组合，最后减去重复的组合。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,ans,a,b,x,boy[200005],girl[200005];
int c(int x){               //排列组合函数
	return x*(x-1)/2;
}
signed main(){
	scanf("%lld",&t);
	while(t--){
		memset(boy,0,sizeof(boy));
		memset(girl,0,sizeof(girl));
		scanf("%lld",&a);
		scanf("%lld%lld",&b,&n);
		for(int i=1;i<=n;i++){
			scanf("%lld",&x);
			boy[x]++;
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&x);
			girl[x]++;
		}
		ans=c(n);            //如果没重复的
		for(int i=1;i<=max(a,b);i++){
			if(boy[i]>=2)ans-=c(boy[i]);//减去重复的
			if(girl[i]>=2)ans-=c(girl[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：bmyjacks (赞：0)

### 宣传一下某蒟蒻的blog
[更好的阅读体验](https://www.bmyjacks.cn/2021/cf1475c/)

# 题意理解

* 数据组数 $ T $
* 男孩 $ a $ 个，女孩 $ b $ 个，舞伴 $ k $ 对

# 思路

## 存储数据

```cpp
vector<pair<int, int>> dancePair;
```

### 计算答案

#### 方法一

期望得分：20

暴力枚举每一对舞伴 $ (boy_{i} - girl_{i}) $ 

```cpp
 register unsigned long long ans = 0;
  for (register int i = 0; i < k - 1; ++i) {
    for (register int j = i + 1; j < k; ++j) {
      if ((dancePair[i].first != dancePair[j].first) and (dancePair[i].second != dancePair[j].second)) {
        ++ans;
      }
    }
  }
  cout << ans << endl;
```

结果第四个点 **TLE** 了，一看时间复杂度 $ O(k^{2} \times T) $，难道 $ n^{2} $ 过百万已经不灵验了？（好吧题目中的是两百万）

#### 方法二

期望得分：100

仔细研究发现，我们可以枚举每一对舞伴，并将所有 $ k $ 对舞伴中除了与他们有相同的组成以外的加入答案中即可。

详细版： 共 $ k $ 对舞伴，除去本身后有 $ k - 1 $ 对舞伴，在剩下的 $ k - 1 $ 对舞伴中，与选择的舞伴中男生相同的有 $ aryBoy[boy_{choose}]  - 1 $ 对，与女生相同的有 $ aryGirl[girl_{choose}] - 1 $ 对，则每次枚举需要增加的数量为
$$
(k - 1) - (aryBoy[boy_{choose}] - 1) - (aryGirl[girl_{choose}] - 1) \\
= k - aryBoy[boy_{choose}] - aryGirl[girl_{choose}] + 1
$$

此时我们对每一对男生女生都重复计算了两次，则最后答案需要除以 $ 2 $。

时间复杂度 $ O(k \times T) $

```cpp
int aryBoy[MAX_K], aryGirl[MAX_K];
for (register int i = 0, tmp; i < k; ++i) {
    cin >> tmp;
    ++aryBoy[tmp];
  }
  for (register int i = 0, tmp; i < k; ++i) {
    cin >> tmp;
    ++aryGirl[tmp];
  }

register unsigned long long ans = 0;
  for (register int i = 0; i < k; ++i) {
    ans += k - aryBoy[dancePair[i].first] - aryGirl[dancePair[i].second] + 1;
  }
  ans /= 2;
  cout << ans << endl;
```



---

## 作者：qhy_ (赞：0)

### 题目地址

#### [CF原题](https://codeforces.com/contest/1475/problem/C)
#### [洛谷题目](https://www.luogu.com.cn/problem/CF1475C)


------------

### 思路
~~$a$ 和 $b$ 都是废的~~

1. 首先判重，把重复的部分找出来
1. 然后利用容斥原理，得到

$
sum=\sum_{i=1}^n (k-(cnta_{ai}+cntb_{bi}-1))
$



------------

### $Code$
```cpp
#include <cstring>
#include <iostream>

using namespace std;
using ll = long long;

const int N = 2e5 + 5;

int a, b, k, t;
int a[N], b[N];
int cnta[N], cntb[N];
ll sum;

void in(int a[], int cnt[]) {
  for (int i = 0; i < k; i++) {
    cin >> a[i];
    ++cnt[a[i]];
  }
}

int main() {
  cin.tie(NULL);
  cout.tie(NULL);
  ios_base::sync_with_stdio(NULL);
  cin >> t;
  while (t--) {
    memset(cnta, 0, sizeof cnta);
    memset(cntb, 0, sizeof cntb);
    cin >> a >> b >> k;
    sum = k;
    in(a, cnta);
    in(b, cntb);
    for (int i = 0; i < k; i++) {
      sum += k - cnta[a[i]] - cntb[b[i]];
    }
    cout << sum / 2 << endl;
  }
  return 0;
}
```


---

## 作者：do_while_true (赞：0)

# [C](https://codeforces.com/contest/1475/problem/C)

### $\mathcal{Translate}$

共有 $a$ 个男生，$b$ 个女生，其中有 $k$ 组男女愿意组成一对。现在要从中挑选出两对男女（不能重复），求一共有多少种挑选方法。

$a,b,k\leq 2\times 10^5$

### $\mathcal{Solution}$

首先先去重。枚举每一对作为第一对，然后就是剩下的 $(k-1)$ 组中有多少组不包含枚举到的那一组的男女。提前记录每个男生和每个女生匹配了多少组，即可快速求出这个答案。

最后把算出来的答案除以 $2$ 即为答案（因为每种合法的匹配被两组男女分别计算了一次。）

### [$\mathcal{Code}$](https://codeforces.com/contest/1475/submission/105834047)


---

## 作者：Ryo_Yamada (赞：0)

> 给出男生、女生的总个数 $a,\,b$ 和可能配对的组数 $k$。其中 $(x,\,y)$ 为一对，$x$ 即左边的数永远表示男生编号，$y$ 永远表示女生编号。询问找出 $2$ 个组且其中的男生女生不重复的挑选方法数。

容斥。记录组中男生是 $x$ 的个数 $cnta_x$，女生是 $y$ 的个数 $cntb_y$，以及组是 $(x,\,y)$ 的个数 $cntt_{(x,\,y)}$。每次计算的时候需要减去的值则为 $cnta_{a_i} + cntb_{b_i} - cntt_{(a_i,\,b_i)}$
。别忘了最后的答案需要除以 $2$。

而且我没搞懂这个 $a,\,b$ 有什么用。

upd：没看到每组最多出现一次。。。所以 $cntt_{(a_i,\,b_i)}$ 一定为 $1$。。。

$\text{Code}$：

```cpp
#define pii pair<int, int>
#define W(M) while(M--)

const int N = 2e5 + 5;

int x, y, k;
int a[N], b[N], cnta[N], cntb[N];
map<pii, int> cntt;
ll sum;
 
int main() {
	int T; cin >> T;
	W(T) {
		sum = 0;
		memset(cnta, 0, sizeof cnta);
		memset(cntb, 0, sizeof cntb);
		cntt.clear();
		qread(x, y, k);
		rep(i, 1, k) {
			qread(a[i]);
			++cnta[a[i]];
		} 
		rep(i, 1, k) {
			qread(b[i]);
			++cntb[b[i]];
			++cntt[mp(a[i], b[i])];
		}
		rep(i, 1, k) sum += k - 1 - (cnta[a[i]] + cntb[b[i]] - cntt[mp(a[i], b[i])] - 1);
		printf("%lld\n", sum / 2);
	}
 	return 0;
}
```


---

