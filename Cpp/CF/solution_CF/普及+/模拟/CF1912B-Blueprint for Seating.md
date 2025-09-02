# Blueprint for Seating

## 题目描述

一家飞机制造公司希望改进其乘客飞机的设计。研究显示，大多数延误是因为登机速度缓慢。

大多数中型客机采用3-3座位布局，也就是每排有6个座位：左边3个座位、一条过道，右边3个座位。两侧分别有窗户座位、靠过道座位和中间座位。在没有其他乘客的情况下，坐在靠过道座位的乘客登机速度明显快于靠窗座位的乘客。

该公司决定将一种座位布局的不便程度定义为一个排中每个座位到最近过道的距离总和。座位到过道的距离是指它们之间的座位数。例如，对于3-3布局，靠窗座位的距离为2，中间座位为1，靠过道座位为0。因此，3-3布局的不便程度为 $ (2+1+0)+(0+1+2)=6 $。而对于3-5-3布局，其不便程度为 $ (2+1+0)+(0+1+2+1+0)+(0+1+2)=10 $。

形式化地说，一种布局是一个正整数序列 $ a_1, a_2, \ldots, a_{k+1} $，其中第 $ i $ 组有 $ a_i $ 个座位，共有 $ k $ 条过道，每条过道位于相邻的两组之间。也就是说，过道必须夹在两个座位之间，无法紧挨窗户，也不能有两条相邻的过道。

公司希望设计一个单排有 $ n $ 个座位和 $ k $ 条过道的布局，以达到最小的不便程度。请帮助他们找出所有可能布局中不便程度最小的一种，并计算出所有达到最小不便程度的布局数量，并将其结果对 $ 998\,244\,353 $ 取模。

## 说明/提示

在测试用例 9 2 中，不便程度为6的布局有：3-4-2、2-4-3 和 2-5-2。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
8
4 1
3 2
4 2
5 2
6 1
6 2
1000000000 1
9 2```

### 输出

```
2 1
0 1
0 1
1 3
6 1
2 4
249999999500000000 1
6 3```

# 题解

## 作者：huangrenheluogu (赞：2)

位置坐标和对答案的贡献简图如下面所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/vhqjf811.png)

手摸一下样例，可以发现用 $k$ 条过道隔开位置的时候需要尽可能均匀。

简要~~伪证~~（~~感性理解~~）证明一下。

我们可以把一个过道左右两边看成两座山，如果出现下面这种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/m37gmugw.png)

那么，我们可以把过道往左移动，显然可以把左边更高的贡献“换成”右边更低的贡献，这样可以减小总贡献。

所以，我们可以感性理解为尽量平均。

我们把一个单调递增/递减的区域称为一个“凸起”，比如，样例中 `2 1 0 0 1 2 1 0 0 1 2` 就可以分成下面的“凸起”。`(2 1 0) (0 1) 2 (1 0) (0 1 2)`。其中没有包起来的 $2$ 可以属于左右两边任意一个“凸起”。

那么，剩下的问题就是先平均分，如何把剩下的位置放到“凸起”里。

第一个输出非常简单，我们考虑第二个输出的方案总数。

先把 $n$ 个物品平均分到 $2k$ 个地方（想想看，一共是 $2k$ 个“凸起”），剩下不能平均分的就是 $n'$。

接下来要把 $n'$ 个物品放到这被 $k$ 条过道分成的 $k+1$ 块，但是有下面的约束条件，求方案总数。

> 约束条件：发现有 $k-1$ 个地方可以放 $2$ 个剩余的位置，$2$ 个地方可以放 $1$ 个位置。

组合数学不会，怎么办？

发现 $\sum k\le10^6$，因此直接枚举 $i$ 个地方放了 $2$ 个剩余物，然后剩下 $k+1-i$ 个地方至多放 $1$ 个剩余的物品。这个组合数是很好计算的。

-------------------------

我在代码中特盘了第一个答案为 $0$ 的情况，当第一个答案为 $0$ 的时候，我们看下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/w3tv9sqe.png)

红线是必须隔断的，剩下 $n-2$ 个球，分成 $k-1$ 块。我们记数量为 $2$ 的堆为 $x$，数量为 $1$ 的堆为 $y$，列个方程可以解得 $x=n-k-1$，那么答案就是 $(_{n-k-1}^{n-1})$。

[code](https://codeforces.com/contest/1912/submission/238490933)

---

## 作者：madfallen (赞：1)

DoctorWang 模拟赛 T2。

把两边舷窗黏在一起，这样就变成 $k$ 个对称块，方便看。

注意到分成若干个 $\lfloor \frac{n}{k} \rfloor$ 和 $\lfloor \frac{n}{k} \rfloor +1$ 就是答案，调整法随便调都不会更优，于是第一问做完了。

第二问需要手玩一下，发现可以把两个奇数重组为两个偶数，比如 $5-5$ 和 $4-6$ 答案是一样的。

不妨设 $\lfloor \frac{n}{k} \rfloor$ 是奇数，否则跟 $\lfloor \frac{n}{k} \rfloor+1$ 对称地换一下。能不能继续重组呢？手玩一下一奇一偶重组和两个偶数重组会变劣，所以枚举一下把多少组 $2 \times \lfloor \frac{n}{k} \rfloor$ 拆成 $\lfloor \frac{n}{k} \rfloor-1$ 和 $\lfloor \frac{n}{k} \rfloor+1$，然后多重排列算一下就莫名其妙地对了。

```c++
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int N=2e5;
const int mod=998244353;
int n,k;
inline int ksm(int a,int b){
	int res=1;
	for(;b;b>>=1){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
	}
	return res;
}
inline int inv(int x){
	return ksm(x,mod-2);
}
int jc[N+5]={1},invjc[N+5];
inline void init(){
	for(int i=1;i<=N;i++)jc[i]=jc[i-1]*i%mod;
	for(int i=0;i<=N;i++)invjc[i]=inv(jc[i]);
}
inline int calc(int u){
	if(u<=1)return 0;
	return (u/2+u%2)*(u/2+1)-u;
}
inline int work1(int u,int kk){
	if(kk<=0||u<=0)return 0;
	int o=u/kk,h=u-o*kk;
	return (kk-h)*calc(o)+h*calc(o+1);
}
inline int work2(int u,int kk){
	if(kk<=0||u<=0)return 0;
	int o=u/kk,h=u-o*kk,g=kk-h;
	if(o==1)return jc[kk-1]*invjc[h-1]%mod*invjc[g]%mod;
	int ans=0;
	if(o%2==0)swap(h,g);
	for(int p=g;p>=0;p-=2){
		ans+=jc[kk]*invjc[p]%mod*invjc[(g-p)/2]%mod*invjc[h+(g-p)/2]%mod;
		if(p)ans+=jc[kk-1]*invjc[p-1]%mod*invjc[(g-p)/2]%mod*invjc[h+(g-p)/2]%mod;
		ans%=mod;
	}
	return ans;
}
signed main(){
	init();
	int T;
	cin>>T;
	while(T--){
		cin>>n>>k;
		cout<<work1(n,k)<<" "<<work2(n,k)<<endl;
	}
}
```

---

