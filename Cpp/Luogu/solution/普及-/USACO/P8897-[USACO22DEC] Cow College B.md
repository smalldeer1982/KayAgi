# [USACO22DEC] Cow College B

## 题目描述

Farmer John 计划为奶牛们新开办一所大学！ 

![](https://cdn.luogu.com.cn/upload/image_hosting/wiy5l6d6.png)

有 $N(1 \le N \le 10^5)$ 头奶牛可能会入学。每头奶牛最多愿意支付 $c_i$ 的学费 $(1 \le c_i \le 10^6)$。 Farmer John 可以设定所有奶牛入学需要支付的学费。如果这笔学费大于一头奶牛愿意支付的最高金额，那么这头奶牛就不会入学。Farmer John 想赚尽可能多的钱，从而可以给他的讲师提供一笔可观的工资。请求出他能赚到的钱的数量，以及此时应当收取多少学费。 

## 说明/提示

### 样例 1 解释

如果 Farmer John 收费 $4$，那么 $3$ 头奶牛将会入学，从而使他赚取 $3 \times 4=12$ 的金额。

### 测试点性质

- 测试点 $2-4$ 满足 $c_i \le 1000$。
- 测试点 $5-8$ 满足 $N \le 5000$。
- 测试点 $9-12$ 没有额外限制。 

## 样例 #1

### 输入

```
4
1 6 4 6```

### 输出

```
12 4```

# 题解

## 作者：NightStriker (赞：13)

（1.16：本题解进行了一些修改，希望管理能给通过 /kel）

题意：

> 有 $N$（$1 \le N \le 10^5$）头奶牛可能会入学。每头奶牛最多愿意支付  $c_i$ 的学费（$1 \le c_i\le 10^6$）。 Farmer John 可以设定所有奶牛入学需要支付的学费。如果这笔学费大于一头奶牛愿意支付的最高金额，那么这头奶牛就不会入学。Farmer John 想赚尽可能多的钱，从而可以给他的讲师提供一笔可观的工资。请求出他能赚到的钱的数量，以及此时应当收取多少学费。



## $33$ 分做法

虽然是 T1，但是纯暴力是过不去的哦。

枚举答案，然后再遍历一遍数组判断当前奶牛能否支付起现在的学费，不断取 $\operatorname{max}$ 就行了。

设 $k$ 是 $c_i$ 中最大的数字，这种暴力的做法时间复杂度即 $\mathcal{O}(nk)$，因为 $k \le 10^6$，所以明显会 TLE。

放一下代码吧。

```cpp
#include<iostream>
#define int long long//不开ll见祖宗（
using namespace std;
int n,a[100001],ans,k,cnt,mx;
signed main(){
	cin>>n;
	for(int i = 1;i<=n;i++) {
		cin>>a[i];
		k = max(k,a[i]);
	}
	for(int i = 1;i<=k;i++){//枚举答案
		ans = 0;
		for(int j = 1;j<=n;j++){
			if(a[j]>=i) ans+=i;//判断第 j 头奶牛能否支付起当前的学费 i
		}
		if(ans>mx){//打擂台取最大
			mx = ans;
			cnt = i;
		}
		if(ans==mx){//如果答案相同取学费小的
			cnt = min(cnt,i);
		}
	}
	cout<<ans<<' '<<cnt<<endl;
	return 0;
} 

```

---

## $100$ 分做法（满分）

可以证明，取的最佳学费永远是 $c_i$ 的其中之一（因为如果不是，可以稍微增加学费而不改变付钱的牛）。

因此，我们所要做的就是维护这些值，看看每个值能赚多少钱。

我们先排一下序，确定有多少奶牛可以支付当前的学费，然后从最低到最高进行更新，维护愿意支付的奶牛数量的计数。（在一个 $c_i$ 值被遍历到后，这些奶牛就不再能够支付学费，所以计数是递减）

这些操作在 $\mathcal{O}(n \log n)$ 的时间复杂度就可以解决力（喜


还有最重要的一件事，就是 **不开 $\textbf{long long}$ 见祖宗**，因为答案可能高达 $10^5 \times 10^6 = 10^{11}$。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1000001],ans,cnt;
signed main() {
	cin>>n;
	int cow = n;
	for (int i = 1; i<=n; i++) cin>>a[i];
	sort(a+1,a+n+1);
	for (int i = 1; i<=n; i++) {
		if (a[i]*cow>ans) {//最优答案更新 
			ans = a[i]*cow;
			cnt = a[i];
		}
		cow--;//第i-1头牛不交学费了。 
	}
	cout<<ans<<' '<<cnt<<endl;
	return 0;
}

```

---

###### 一些魔怔的废话：作者因为评测机原因这道题抱灵力！谢谢你，USACO。

---

## 作者：快斗游鹿 (赞：5)

可以证明，收取的学费一定是某只奶牛最多愿意支付的学费。假设当前收取的学费为 $x$，这时可以入学的奶牛是 $a$ 只，而某只奶牛最多愿意支付 $y(x<y)$ 的学费，当收取学费为 $y$ 时，仍有 $a$ 只奶牛可以入学。则显然，有 $x\times a <y\times a$，也就是取后者一定比取前者更优。

所以我们可以先将 $c_i$ 去重后从小到大排序，对于每个 $c_i$，维护当前可以入学的奶牛只数即可。时间复杂度 $O(n \log n)$，瓶颈在于排序。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
long long n,m,a[N],t[N],cnt;
long long ans,q; 
long long read(){
	//快读
}
int main(){
	n=read();m=n;
	for(int i=1;i<=n;i++){
		int A;A=read();if(!t[A])a[++cnt]=A;
		t[A]++;
	}
	sort(a+1,a+1+cnt);
	for(int i=1;i<=cnt;i++){ 
		long long mx=a[i]*m;
		if(ans<mx){
			ans=mx;q=a[i];
		}
		m-=t[a[i]];
	}
	cout<<ans<<" "<<q;
	return 0;
}


```



---

## 作者：tbdsh (赞：2)

# 题意
[题目传送门](/problem/P8897)

[更好的阅读体验](/blog/tianbiandeshenghuo11/solution-p8897)

~~[双倍经验](/problem/P2637)~~

给出 $N(1\le N\le10^5)$ 个数 $c_i(1\le c_i\le10^6)$，（以下令数组 $c$ 中 $\le c_i$ 的数有 $g$ 个）求 $c_i\times g$ 的最大值和 $g$。

如果有多个答案，则输出 $g$ 最小的一个。

# 分析
这里提供两种思路（都能 `AC`）。

## 暴力枚举
先对数组 $c$ 从大到小排序，挨个枚举。

此时 $g$ 就是枚举的次数 $i$。

求出 $c_i\times g$ 再判断是否 $\ge$ 当前最大值（因为从大到小枚举，要求输出 $g$ 最小，所以当答案相同时 $g$ 一定更小）。是就更新答案。

时间复杂度：$O(n)$。

## 后缀和
在读入时处理好每个数的出现次数，再用 $O(\max(c_i))$ 的时间处理后缀和。最后用与上面类似的方法判断并更新答案即可。

时间复杂度：$O(\max(c_i))$。

# Code

因为提供了两种解法，所以代码放在了[这里](/paste/x8eopw5n)。需要请自取。

---

## 作者：Ray1 (赞：2)

为了收取更多的学费，每头奶牛收取的学费应当刚好是某一头奶牛愿意支付的最高学费，于是就有了一个暴力写法：

先将 $c$ 数组从小到大排序，然后枚举若以第 $i$ 头奶牛愿意支付的最高学费 $c_i$ 为每头奶牛收取的学费，则这头奶牛和他后面的 $n-i$ 奶牛都愿意支付这笔学费，这个方案赚到的钱就为 $c_i\times(n-i+1)$。枚举所有的 $i$ 即可，时间复杂度 $O(n\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,c[100001],cnt,ans,bns;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>c[i];
	sort(c+1,c+1+n);
	for(int i=1;i<=n;i++){
		cnt=c[i]*(n-i+1);
		if(cnt>ans)ans=cnt,bns=c[i];
	}
	cout<<ans<<' '<<bns;
}
```


---

## 作者：what_can_I_do (赞：2)

[传送门](https://www.luogu.com.cn/problem/P8897)

水。

这道题我们可以先用一个桶来存储 $i$ 元学费是几头牛的最高学费，再对其进行后缀和的处理，就能求出第 $i$ 元学费会有几头牛能付得起，最后再正序处理能赚到的钱的最大值以及在能赚到最大钱的前提下最小的学费。

# CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a[100010],t[1000010]={0},maxd=-1,ans=-1,k=0;
int main()
{
	scanf("%lld",&n);
	for(register int i=1;i<=n;i++) scanf("%lld",&a[i]),maxd=max(maxd,a[i]),t[a[i]]++;
	for(register int i=maxd;i>=1;i--) t[i]+=t[i+1];           //后缀和
	for(register int i=1;i<=maxd;i++) if(t[i]*i>ans) ans=t[i]*i,k=i;      //t[i]*i为可赚学费，t[i]*i>ans才能保证k最小
	printf("%lld %lld",ans,k);
    return 0;
}
```

---

## 作者：Gaode_Sean (赞：0)

签到题。

首先对 $c$ 数组进行排序。

注意到 $1 \le c_i \le 10^6$，不妨考虑直接枚举收取的学费（单价）。设收取的学费为 $x$ 。则二分出有多少奶牛愿意支付的最高金额（即 $c_i$）大于等于 $x$，设为 $cnt$。最后一步，我们用 $x \times cnt$ 与答案进行比较，并更新答案。

时间复杂度为 $\mathcal{O}((\max{c_i}) \log n)$，空间复杂度为 $\mathcal{O}(n)$。

## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
typedef long long ll;
int n,p,x;
ll a[N],ans;
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	sort(a+1,a+1+n);
	for(ll i=1;i<=a[n];i++)
	{
		x=lower_bound(a+1,a+1+n,i)-a;
		if(ll(ll(n-x+1)*i)>ans) ans=ll(ll(n-x+1)*i),p=i;
	}
	printf("%lld %d",ans,p);
	return 0;
} 
```

---

## 作者：sunkuangzheng (赞：0)

**【题目大意】**

给定长度为 $n$ 的数组 $a$，第 $i$ 项为 $a_i$。选取一整数 $x$，定义 $f(x)$ 为不大于 $x$ 的数组 $a$ 的项数，求 $f(x) \cdot x$ 的最大值。

数据范围：$1 \le n \le 10^5,1 \le a_i \le 10^6$。

**【题目分析】**

由于 $a_i$ 很小，考虑枚举 $x$。我们用前缀和的方式处理不大于 $x$ 的项数，此部分代码如下：

```cpp
//a[i] 记录大于 i 的项数
for(int i = 1;i <= n;i ++) cin >> x,a[x+1]++;//由于是不大于，所以x要加一
for(int i = 1;i <= 1e6+5;i ++) a[i] += a[i-1];//前缀和
```

然后枚举 $x$，代码如下：

```cpp
    for(int i = 1;i <= 1e6+5;i ++){
    	long long temp = i*(n-a[i]);//此时 f(x)*x 的值
    	if(temp > mx){//比大小
    		mx = temp;
    		mi = i;
		}
	}
```

最后输出，时间复杂度 $\text O(n)$。

---

