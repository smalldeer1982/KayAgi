# [USACO20JAN] Berry Picking S

## 题目描述

Bessie 和她的妹妹 Elsie 正在 Farmer John 的浆果园里采浆果。Farmer John 的浆果园里有 $N$ 棵浆果树（$1 \leq N \leq 1000$）；树 $i$ 上有 $B_i$ 个浆果（$1 \leq B_i \leq 1000$）。Bessie 有 $K$ 个篮子（$1 \leq K \leq 1000$，$K$ 为偶数）。每个篮子里可以装同一棵树上采下的任意多个浆果，但是不能装来自于不同的树上的浆果，因为它们的口味可能不同。篮子里也可以不装浆果。

Bessie 想要使得她得到的浆果数量最大。但是，Farmer John 希望 Bessie 与她的妹妹一同分享，所以 Bessie 必须将浆果数量较多的 $K/2$ 个篮子给 Elsie。这表示 Elsie 很有可能最后比 Bessie 得到更多的浆果，这十分不公平，然而姐妹之间往往就是这样。

帮助 Bessie 求出她最多可以得到的浆果数量。

## 说明/提示

### 样例解释

如果 Bessie 在

- 一个篮子里装树 2 的 6 个浆果
- 两个篮子里每个装树 3 的 4 个浆果
- 一个篮子里装树 4 的 4 个浆果

那么她能够得到两个各装有 4 个浆果的篮子，总共 8 个浆果。

### 子任务

- 测试点 $1 \sim 4$ 满足 $K \leq 10$。
- 测试点 $5 \sim 11$ 没有额外限制。

## 样例 #1

### 输入

```
5 4
3 6 8 4 2```

### 输出

```
8```

# 题解

## 作者：Zvelig1205 (赞：22)

## [题目传送门](https://www.luogu.com.cn/problem/P6002)

数据范围不大，可以直接暴力模拟。

## 思路

题目中已经明确指出， $K$ 为偶数，所以 $\frac{K}{2}$ 绝对是整数 ~~（当初因为这个专门问了同学）~~ 。

由于题目中没有说每个篮子的上限，那么我们可以枚举篮子装的果子的上限，通过一些奇奇怪怪的比较，来确定最优解。

核心 Code:

```cpp
for(int i=1;;i++)
{
	priority_queue<int>h;
	basket=0;
	for(int j=1;j<=n;j++)
	{
		basket+=a[j]/i;
		h.push(a[j]%i);
	}
	if(basket>k)continue;
	if(basket<(k>>1))break;
	mei=(k>>1)*i;
	jie=(basket-(k>>1))*i;
	for(int ii=basket-(k>>1)+1;ii<=(k>>1);ii++)
		jie+=h.top(),h.pop();
	ans=max(ans,jie);
}
```

分步看一下：

`basket` 代表了需要的篮子数。

很显然，需要的篮子数不能比实际的多，也就有了：

```
if(basket>k)continue;
```

当然，也不能太少，就有了：

```
if(basket<(k>>1))break;
```

当 `basket` 在 $\frac{K}{2}\sim K$ 时，也就是部分篮子能装满，部分篮子装不满的情况。

那么，妹妹能拿到其中的 $\frac{1}{2}$：

```
mei=(k>>1)*i;
```

剩下装满的给姐姐，姐姐再从未满的篮子里 **贪心的** 选取最多的，使自己的利益最大化（优先队列的作用）：

```cpp
jie=(basket-(k>>1))*i;
for(int ii=basket-(k>>1)+1;ii<=(k>>1);ii++)
	jie+=h.top(),h.pop();
```

最后，统计姐姐所能得到的最多的浆果数：

```cpp
ans=max(ans,jie);
```

## 优化

首先说明，上述暴力是能 $A$ 掉这个题的。而且这个优化只是我自己想（kouhu）的，并没有尝试，也不知道对不对。

在这里，我们是尝试 **枚举答案** ，时间复杂度是 $O(n\cdot\text{玄学})$。

那么优化就是 **二分答案** ，时间复杂度就应该为 $O(n\cdot\log\text{玄学})$。

可能是吧， ~~我太蒻了……~~

## 闲话

姐妹间的情感就是没有兄弟的好。

~~更没有情侣之间好。~~

---

## 作者：gznpp (赞：15)

假设 Elsie 拿的篮子里面果子数最小值为 $m$，那么最好情况是她拿的篮子里全都是 $m$ 个果子。

我们可以从 $1$ 到 $\max_{i = 1}^{N}{B_i}$枚举这个 $m$，令**能装满的**（也就是装了 $m$ 个果子的）篮子数为 $L$。

分类讨论：

- $L < \dfrac{K}{2}$：不能满足最小条件，停止枚举。

- $L \ge K$：此时 Bessie 能拿到的就是 $\dfrac{mK}{2}$ 个果子，更新答案即可。

- `default:` 这里的关键是每棵树上 在装满若干篮子之后 剩余的果子数，也就是 $B_i \bmod m$。我们以 $B_i \bmod m$ 为关键字从大到小对 $B$ 数组排序，排序结果为 $B'$。Bessie 拿的果子数就是
$$
m \cdot (L - \frac{K}{2}) + \sum_{i = 1}^{K - L}{({B'}_i \bmod m)}
$$

时间复杂度 $O(\max_{i = 1}^{N}{B_i} \cdot N \log N)$。

Code:
```cpp
// template <typename typ> 
// inline bool up(typ &x, const typ &y) {
// return x < y ? x = y, 1 : 0; }

const int maxn = 1005;
int n, k, a[maxn], mx, mod, ans;

inline bool cmp(int p, int q) {
	return p % mod > q % mod;
}

signed main() {
	orh::useios();
	
	cin >> n >> k;
	for (rg int i = 1; i <= n; ++i) {
		cin >> a[i];
		up(mx, a[i]);
	}
	
	for (rg int t = 1; t <= mx; ++t) {
		int full = 0;
		for (rg int i = 1; i <= n; ++i)
			full += a[i] / t;
		if (full < (k >> 1)) break;
		if (full >= k) {
			up(ans, t * k >> 1);
			continue;
		}
		
		mod = t;
		sort(a + 1, a + n + 1, cmp);
		int tmp = (full - (k >> 1)) * t;
		for (rg int i = 1; i <= n && i + full <= k; ++i)
			tmp += a[i] % t;
		up(ans, tmp); 
	}
	
	cout << ans << endl;
	
	return 0;
}
```

---

## 作者：zzw4257 (赞：10)

> **生动版**求$n$棵果数为$\{a_i\}$的树取$m$筐果子,要求每一筐都最多只从一棵树取
>
> **清晰版**求$\{A_i\}$一个长度为$K$(偶数)的子序列$\{B_i\}$的衍生序列$\{C_i\}$使得$\forall i,\sum\limits_{j=L_i}^{R_i}C_j\leqslant B_i(R_j<L_{j+1})$,求$\{C_i\}$的前$\frac k 2+1\rightarrow k$大元素之和最大

首先可以确定我们一定尽量想让前$k\over 2$号元素和尽量小时最小值(第$k\over 2$大)尽量大

所以有前$k\over 2$号元素都是一个相同值

枚举这个值$m$，有三种情况

- 往死里取能取出$k$个$m$，则前$\frac k 2+1\rightarrow k$大元素都是$m$
- 往死里取取不出$\frac k 2$个$m$，则更大的$m$不会有更优答案
- 否则，就在每棵树上尽量取后剩余结果(其实是取模结果)选出前$\frac{k}2$大元素作为前$\frac k 2+1\rightarrow k$大元素

```cpp
for(x=1;x<=mx;++x){
    for(sum=0,i=1;i<=n;++i)sum+=(b[i]/x);
    if(sum<k>>1)break;
    if(sum>=k){ans=max(ans,x*(k>>1));continue;}//直接对半 
    mod=x;sort(b+1,b+n+1,cmp);
    rest=(sum-(k>>1))*x;
    for(i=1;i<=n&&i+sum<=k;++i)rest+=b[i]%x;//每个都尽量选k后剩余的部分 
    ans=max(ans,rest);
}
```

---

## 作者：KaisuoShutong (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/P6002)

# 题目大意

给定 $n$ 颗树，分别有 $a_i$ 个果子，求选出 $m$ 篮果子使得最少的 $\frac{m}{2}$ 篮最多，要求每篮的果子都必须来自同一棵树。

# 题目分析

1. 首先，因为要使最少的 $\frac{m}{2}$ 篮果子更多，所以最多的 $\frac{m}{2}$ 篮果子应该尽量少。其次，为了让最少的 $\frac{m}{2}$ 篮果子取值更灵活（也就是能取到更大的值），第 $\frac{m}{2}$ 多的篮子中果子数应该尽量多。**由此可得最多的 $\frac{m}{2}$ 篮果子数目应该都相同。**

2. 那么我们枚举取的果子数 $w$ 。称取出 $w$ 个果子的篮子为整篮， $now$ 表示最多取出的整篮数（贪心），有以下情况：  
	1) $now\geq m$，答案为 $\frac{m}{2}\times w$。  
	2) $now\geq \frac{m}{2}$，答案为 $(now - \frac{m}{2})\times w + (m-now)\text{个无法凑成整篮的中的最大值}$。   
	3) $now\leq \frac{m}{2}$，不加入答案。

此题解决。

短到哭泣的代码：

```cpp
signed main()
{
	n=read(),k=read();
	for(int i=1;i<=n;i++) MAX=max(MAX,b[i]=read());
	std::sort(b+1,b+1+n);
	for(int i=1;i<=MAX;i++)
	{
		std::priority_queue<int> q;int ans=0;
		for(int j=1;j<=n;j++) ans+=b[j]/i,q.push(b[j]%i);
		if(ans<k>>1) continue;
		else if(ans<k)
		{
			int t=ans-(k>>1),cr=t*i;t=(k>>1)-t;
			while(t--) cr+=q.top(),q.pop();
			res=max(res,cr);
		}
		else res=max(res,(k>>1)*i);
	}
	printf("%d\n",res);
	return 0;
}
```

---

## 作者：似镜流年 (赞：6)

## 思路
$\qquad$由于这题每棵树上的果子的数据较小，我们可以考虑贝茜的妹妹所拿的框中都是$w$个苹果，那么只要一一枚举$w$就再求贝茜在这种情况下可以拿到的最多的苹果然后取最大就好了。    
$\qquad$详情见代码。
## 代码
```
#include<bits/stdc++.h>//万能头 
#define ll long long
using namespace std;
int n,k,a[5001],l,ans;//ans表示答案 
priority_queue<int>q,kong;//利用优先队列取最优，kong用来快速清空。 
void doit(int x){//x表示一个篮子最多的果子数 
	q=kong;
	l=0;
	for(int i=1;i<=n;i++){
		l+=a[i]/x;//按这种装法可以装满多少篮子 
		q.push(a[i]%x);//余下来的直接加入优先队列 
	}
}
void kk(int x){
	int w;//w记录在一个篮子最多装x个的情况下贝茜可以得多少个 
	w=(l-(k/2))*x;//剩下来的篮子给bessie 
	for(int i=1;i<=k-l;i++){
		w+=q.top();//取剩下最多的补完k个篮. 
		q.pop();
	}//也可以直接存到数组里然后sort排序后再取. 
	if(ans<w)ans=w;
}
int main () {
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
	}
	sort(a+1,a+1+n);
	for(int i=a[n];i>=a[1];i--){
		doit(i);
		if(l>=k){//如果有一个可以取到，那么低的必然能取到，答案也不会更优，所以直接退出。 
			if(ans<k*i/2)ans=k*i/2;		
			break;
		}else if(l<k/2)continue;//取不到直接跳过(也就是说bessie的妹妹不可能最小的一个篮子是i个) 
		else kk(i);
	}
	printf("%d",ans);//输出 
	return 0;
}

```



---

## 作者：FutaRimeWoawaSete (赞：4)

不知道有没有人用三分过掉，不过应该是对的，希望没有萎掉。           

不过此题直接 $O(n ^ 2 \log n)$ 就可以过了。        

考虑前 $\frac{k}{2}$ 个篮子必须装成一个值，我们直接枚举这个值然后就可以算当前的最大贡献了。         

如果当前枚举到 $i$，记可以装的篮子数为 $res$ 那么如果 $k \leq res$ 答案就是 $\frac{k}{2} \times i$ ，否则我们就把剩下需要填的篮子装上还剩下的浆果数量即可。                

注意判断枚举的值是否合法。 

有空补一下三分做法吧。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 1e3 + 5;
int n,m,k,a[Len],sum[Len << 2],lsh[Len],cnt;
bool cmp(int x,int y){return x > y;}
int main()
{
	scanf("%d %d",&n,&k);int maxa = 0;
	for(int i = 1 ; i <= n ; i ++) 
	{
		scanf("%d",&a[i]);
		maxa = max(maxa , a[i]);
	}int Ans = 0;
	for(int i = 1 ; i <= maxa ; i ++) 
	{
		cnt = 0;int res = 0;
		for(int j = 1 ; j <= n ; j ++) res += a[j] / i , lsh[++ cnt] = a[j] % i;
		if(res < k / 2) continue;
		if(res >= k) Ans = max(Ans , k / 2 * i);
		else
		{
			int sim = (res - k / 2) * i;
			sort(lsh + 1 , lsh + 1 + cnt , cmp);
			for(int j = 1 ; j <= k - res ; j ++) sim += lsh[j];
			Ans = max(Ans , sim);
		}
	}
	printf("%d\n",Ans);
	return 0;
}
```

---

## 作者：haotian1234 (赞：3)

## 题意暗示
- 就是问你如何做到 Bessie 的篮子中所有的浆果数最接近于 Elsie 的篮子中所有的浆果数
## 题目分析
很显然，当 Elsie 的篮子中每一篮的篮子数与 Bessie 的篮子中每一篮的篮子数相等时，答案得到了最优化。

所以我们假设这个值为 $min$ ，既然这时 Elsie 的篮子中每一篮的篮子数与 Bessie 的篮子中每一篮的篮子数有可能不相等，但至少 Elsie 的篮子中每一篮的篮子数要相等，这时，就可以用这个值求出答案。

从数据来看，$min$ 最大也才 1000 ，那我们就枚举 $min$，不就好了吗。但在枚举时，要分以下几种情况讨论：

假设能装满 $min$ 个浆果的篮子数为 $lz$。
1. $lz$ < $\frac{K}{2}$，这时连 Elsie 的每个篮子都不能装满 $min$ 个，就别往下讨论了，直接 continue；
1. $lz$ > $K$，那么，Bessie 的篮子也都能装满 $min$ 个，所以，Bessie 所得到的浆果数为 $\frac{min \times K}{2}$ 个。
1. $\frac{K}{2}$ < $lz$ < $K$，此时将每棵浆果树摘完 $min$ 个后的浆果树放入一个优先队列 $q$ 中（大顶堆），每次从中取出最大的浆果数，放入篮子，总共取 $K - lz$ 次（有 $lz$ 个篮子已经装满了 $min$ 个浆果，还剩 $K - lz$ 个没装）

最后，将每次求出的 Bessie 可以拿到的浆果数进行取最大值，就是答案。
## 题目坑点
- 一颗浆果树上的浆果可以放入多个篮子
- 但一个篮子不可以放多个浆果树上的浆果

下面就上大家最最最关心的东西——代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,i,a[100100],b[100100],j,ans;
int main(){
    scanf("%d%d",&n,&k);
    for (i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+1+n);
    for (i=a[n];i>=a[1];i--){//枚举
        int lz=0;
        priority_queue<int> q;//优先队列
        for (j=1;j<=n;j++)
            lz+=a[j]/i,q.push(a[j]%i);
        if (lz>k) lz=k;
        if (lz<k/2) continue;
        else{
            int s=(lz-k/2)*i;
            for (j=1;j<=k-lz;j++)
                s+=q.top(),q.pop();
            ans=max(ans,s);//取剩下的
        }
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：信守天下 (赞：3)

## [洛谷传送门](https://www.luogu.com.cn/problem/P6002)
## 直接暴力就行了
分析题意，我们可以发现，这道题的难点在于你不知道每个篮子装几个果子。

题目要求的是求较小的 $K / 2 $ 的最大值。

那么我们可以设较小的 $K / 2 $ 中最大的篮子装了 $v$ 个。

则前 $K / 2$ 中，果子的数量就要尽可能地小，最小为 $v$。

后 $K / 2$ 中，果子的数量就要尽可能地大，最大也为 $v$。

那么就可以直接先分前 $K / 2$ ，每个篮子 $v$ 个。

如果分不了，就直接无解。

再去计算后 $K / 2$ ，每个篮子 $v$ 个，剩下的篮子继续装当前剩下的中最大的。

最后考虑 $v$ ，观察数据规模，可以发现直接枚举就行了。
## $code$
~~~cpp
#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
const int kMaxN = 1001;
int a[kMaxN];
int n, k, s;
int main() {
  cin >> n >> k;
  k /= 2;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1;; i++) {
    int t = 0;
    for (int j = 1; j <= n; j++) {  // 计算采满i的篮子数
      t += a[j] / i;
    }
    if (t < k) {  // 无法装满k个篮子
      break;
    }
    t = min(t - k, k);                                                    // 多出的篮子
    sort(a + 1, a + 1 + n, [i](int x, int y) { return x % i > y % i; });  // 按照剩下的数量排序
    int v = t * i;                                                        // 采满篮子的总量
    for (int j = 1; j <= min(n, k - t); j++) {                            // 采够k个篮子
      v += a[j] % i;
    }
    s = max(s, v);  // 更新最大值
  }
  cout << s;
  return 0;
}
~~~

---

## 作者：_szs9601 (赞：2)

#### 思路
假设 Elsie 拿的篮子里面果子数最小值为 $m$，那么最好情况是她拿的篮子里全都是 $m$ 个果子。所以我们直接暴力枚举这个 $m$，然后就能在剩下的果子中选择最多的那几组果子，就可以求出 Bessie 能得到的最多的果子数了。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,i,j,s,ans,k,a[100100];
int main(){
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(i=a[n];i>=a[1];i--){//枚举m
		s=0;
		priority_queue<int>q;//有限队列，大顶堆
		for(j=1;j<=n;j++) s+=a[j]/i,q.push(a[j]%i);//求出装满若干篮子之后剩余的果子数
		if(s>=m){ans=max(ans,i*m/2);continue;}//说明两人都能取到i*m/2的果子数
		if(s<m/2) continue;//不满足最小条件
		k=m-s;s=(s-m/2)*i;
		for(j=1;j<=k;j++) s+=q.top(),q.pop();
		ans=max(ans,s);//让Bessie得到最多的果子
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：nahidaa (赞：1)

## [传送门](https://www.luogu.com.cn/problem/P6002)

## 思路

1. 因为树上的浆果数 $\le1000$，所以我们可以枚举浆果数量（设为 $m$）。

1. 在每棵树上尽可能多地摘 $m$ 个浆果放在篮子中。

1. 将每棵树上剩下的浆果数量进行排序，从大到小放进还没有浆果的篮子内。

1. 枚举 $m$，记录 Bessie 最多可以收获得浆果的数量，最后取最大值作为结果。


------------
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,a[1005],big,ge,b[1005],e,geshu,shao,shu;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    shao=m/2;
    for(int g=1;g<=n;g++){
        cin>>a[g];
    }
    sort(a+1,a+n+1);
    for(int g=1;g<=1000;g++){
        ge=0;
        for(int h=n;h>=1;h--){
            if(a[h]>=g){
                ge+=a[h]/g;
                b[h]=a[h]%g;
            }
            else b[h]=a[h];
        }
        sort(b+1,b+n+1);
        e=0;
        shu=0;
        if(ge>shao){
            e=min(shao,ge-shao)*g;
            shu=ge-shao;
            if(shu>=shao){
                big=max(e,big);goto ew;
            }
        }
        for(int h=n;h>=1;h--){
            if(ge<shao){
                ge++;
            }
            else{
                shu++;
                e+=b[h];
                if(shu==shao)break;
            }
        }
        big=max(big,e);
        ew:
            big=big;
    }
    cout<<big<<"\n";
}
```

---

