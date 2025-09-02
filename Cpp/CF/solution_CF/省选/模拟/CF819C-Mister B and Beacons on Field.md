# Mister B and Beacons on Field

## 题目描述

Mister B has a house in the middle of a giant plain field, which attracted aliens life. For convenience, aliens specified the Cartesian coordinate system on the field in such a way that Mister B's house has coordinates $ (0,0) $ . After that they sent three beacons to the field, but something went wrong. One beacon was completely destroyed, while the other two landed in positions with coordinates $ (m,0) $ and $ (0,n) $ , respectively, but shut down.

Mister B was interested in this devices, so he decided to take them home. He came to the first beacon, placed at $ (m,0) $ , lifted it up and carried the beacon home choosing the shortest path. After that he came to the other beacon, placed at $ (0,n) $ , and also carried it home choosing the shortest path. When first beacon was lifted up, the navigation system of the beacons was activated.

Partially destroyed navigation system started to work in following way.

At time moments when both survived beacons are at points with integer coordinates the system tries to find a location for the third beacon. It succeeds if and only if there is a point with integer coordinates such that the area of the triangle formed by the two survived beacons and this point is equal to $ s $ . In this case the system sends a packet of information with beacon positions to aliens, otherwise it doesn't.

Compute how many packets of information system sent while Mister B was moving the beacons.

## 说明/提示

First test case contains the following beacon positions: $ (2,0) $ and $ (0,2) $ , $ s=3 $ . The following packets could be sent: $ ((2,0),(0,2),(-1,0)) $ , $ ((1,0),(0,2),(4,0)) $ , $ ((0,0),(0,2),(3,1)) $ , $ ((0,0),(0,1),(-6,0)) $ , where $ (b_{1},b_{2},p) $ has next description: $ b_{1} $ — first beacon position, $ b_{2} $ — second beacon position, $ p $ — some generated point.

Second test case contains the following beacon initial positions: $ (4,0) $ and $ (0,5) $ , $ s=2 $ . The following packets could be sent: $ ((4,0),(0,5),(0,4)) $ , $ ((3,0),(0,5),(2,3)) $ , $ ((2,0),(0,5),(2,2)) $ , $ ((1,0),(0,5),(1,4)) $ , $ ((0,0),(0,4),(0,-1)) $ , $ ((0,0),(0,2),(2,0)) $ , $ ((0,0),(0,1),(4,0)) $ .

## 样例 #1

### 输入

```
3
2 1 1
2 1 1
1 1 3
1 5 1
2 2 1
1 1 2
10 6 18
2 103 2
13 1 13
```

### 输出

```
4
7
171
```

# 题解

## 作者：BqtMtsZDnlpsT (赞：3)

$\large\text{Solution}$

我们把整个行走过程分为 $2$ 段：

1. $(m,0)\to(0,0)$
2. $(0,n)\to(0,0)$

以下设坐标 $P(x,y)$ 为未知信标的位置。

先考虑第一段。

三角形面积可以通过向量 $\overrightarrow {PN}\times\overrightarrow{PM}$ 的模除以 $2$ 得到（[如果你不知道叉积](https://baike.baidu.com/item/%E5%90%91%E9%87%8F%E7%A7%AF/4601007?fromtitle=%E5%8F%89%E4%B9%98&fromid=8251892&fr=aladdin)），当然你也可以通过暴力分类讨论。

根据面积 $=s$ 得到 $|nx+my-mn|=2s$，根据裴蜀定理，如果存在 $\gcd(n,m)\mid2s$ 则有整数解。

问题转化为求有多少 $k$ 满足 $k\in[1,m],\gcd(n,k)\mid 2s$。

考虑求有多少 $k$ 满足 $k\in[1,m],\gcd(n,k)\nmid 2s$。

我们发现：把 $n$ 分解质因数成 $\prod\limits_{i=1}^{cnt_n}pn_i^{kn_i}$，把 $s$ 分解质因数成 $\prod\limits_{i=1}^{cnt_s}ps_i^{ks_i}$（$cnt_x$ 表示 $x$ 的质因数种数，$ps_i,pn_i$ 是质数），

如果对于一个 $pn_i=ps_j$，有 $kn_i\le ks_j$，那么 $\gcd(n,k)$ 中 $pn_i(ps_j)$ 这个质因数的次数一定小于 $s$ 中的次数，不会因这个质因数不整除。

所以我们只要找出对于 $pn_i=ps_j$，有 $kn_i> ks_j$ 的数，把 $pn_i^{ks_j+1}$ 加入集合 $P$，求 $k\in[1,m]$，满足存在 $q\in P,q\mid k$ 的 $k$ 的数量（如果 $k$ 有因数 $pn_i^{ks_j+1}$，那么 $gcd(n,k)$ 中定有因数 $pn_i^{ks_j+1}$，定不整除）。

然后我们在 $[1,m]$ 范围中进行容斥即可，容斥的柿子：

$\frac{m}{q_1}+\frac{m}{q_2}+\dots+\frac{m}{q_{size}}-\frac{m}{q_1q_2}-\frac{m}{q_1q_3}-\dots-\frac{m}{q_{size-1}q_{size}}+\frac{m}{q_1q_2q_3}\dots\dots$。

$size$ 表示集合大小。

容斥本身难度不大，相信大家都能理解。

与代码里有区别的是：代码里直接用 $m$ 减去以上柿子。

------------

然后考虑第二段

第二段 $M$ 在 $(0,0)$ ，所以三角形面积为 $\frac{nx}{2}$.

所以就是要求出 $[1,n]$ 中 $2s$ 的约数个数。

这一部分可以分解质因数之后暴力枚举所有约数，判断是否小于 $n$，约数个数大约只有 $10^5$ 级别，具体的，你可以看代码。


```cpp

ll a[3],b[3],c[3],ans,n,m,s,GG;
vector<N>res,res1;
void dfs(int stp,ll u){//过程二，主要思路：枚举每一个质因数的次数，从而枚举约数。
	//u 表示当前值，stp 表示搜到哪个质数。
	if(u>GG)return;//如果大于根号 s，那么就返回。
	if(stp==-1){ans+=(u<=n)+(u!=s/u&&s/u<=n);return;}//判断一个小于根号 s 的约数，及 s 除以这个约数是否符合条件。
	for(int i=0;i<=res[stp].s;i++){
		dfs(stp-1,u);
		u*=res[stp].p;
		if(u>GG)break;
	}
}
int bit[150005];//bit是二进制下的位数，用于容斥。
void work(){
	for(int i=0;i<(1<<17);i++)bit[i]=bit[i>>1]+(i&1);
	for(int T=read();T;T--){
		ans=0;
		for(int i=0;i<3;i++)a[i]=read();
		for(int i=0;i<3;i++)b[i]=read();
		for(int i=0;i<3;i++)c[i]=read();
		n=a[0]*a[1]*a[2],m=b[0]*b[1]*b[2],s=c[0]*c[1]*(c[2]<<1);
		res1=Pollard_Rho::work(a[0],a[1],a[2]);//分解质因数，返回数组每个元素有两个参数，.p表示质数，.s表示次数。
		vector<ll>r;
		for(auto I:res1){//这是找集合 P 的过程
			ll cnt=I.p;
			for(int J=1;J<=I.s;J++){//如果一个 n 的质因数的 J 次不是 s 的约数，那么我们就找到一个目标元素
				if(s%cnt){r.push_back(cnt);break;}//这里及时 break 掉，导致不可能加入 p^{ks_j+2} 这种元素。
				cnt*=I.p;
			}
		}
		int gg=r.size(),ggg=(1<<r.size());
		for(int I=0;I<ggg;I++){//这是容斥的部分
			int t=(bit[I]&1?-1:1);ll cnt=1;
			for(int i=0;i<gg;i++)
				if((I>>i)&1)cnt*=r[i];
			ans+=t*m/cnt;
		}
		sort(c,c+3);
		res=Pollard_Rho::work(c[0]<<1,c[1],c[2]);
		GG=(int)sqrt((long long)s);dfs(res.size()-1,1);
		write(ans,'\n');
	}
}
```


---

