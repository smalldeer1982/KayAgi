# Splitting money

## 题目描述

爱丽丝有 $n$ 个账户，为了使自己的财产更分散些，她决定拆分自己的账户，把一些账户中的钱转入新账户，使每个账户中的钱数都不超过 $x$ 个单位货币。每一次转账都需要花费 $f$ 个单位货币的手续费。现在她想知道为了实现她的目标，她至少需要支付多少手续费。

## 说明/提示

爱丽丝转账的最优转账过程：

0. 13 7 6 （开始状态）  
1. 6 7 6 5 （将 $5$ 个单位货币从第一个账户转向新账户，并且花费 $2$ 个单位货币的手续费）
2. 6 4 6 5 1 （将 $1$ 个单位货币从第二个账户转向新账户，也花费两个单位货币的手续费）

两次转账，总手续费为 $4$ 个单位货币。

## 样例 #1

### 输入

```
3
13 7 6
6 2
```

### 输出

```
4
```

# 题解

## 作者：huwenbo (赞：7)

这题我们很容易想到$(mid+1)*x+mid*k$为移动$mid$次的最大值，而且满足单调性，那么我们就可以二分啦！！！！！！！！

话不多说，上代码了。。。。。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[200010],x,k;
long long ans=0,ll;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	scanf("%d %d",&x,&k);
	for(int i=1;i<=n;i++){
		if(a[i]<=x) continue;
		int l=1,r=1000000000,mid,ai=1000000000;
		while(l<=r){
			mid=(l+r)/2;
			ll=(long long)(mid+1)*x+mid*k;
			if(ll>=a[i]){
				r=mid-1;
				ai=min(ai,mid);
			}
			else{
				l=mid+1;
			}
		}
		ans+=(long long)k*ai;
	}
	cout<<ans<<endl;
	
	return 0;
}
```

好简单啊！！

---

## 作者：_Spectator_ (赞：1)

[可能更好的食用体验](/article/65izo64p) $|$ 
[题目传送门](/problem/CF1046F) $|$ 
[我的其他题解](/user/523641#article.2)

------------

### ${\color{#00CD00}\text{思路}}$

对于原本就小于等于 $x$ 的 $a_i$，显然不需要转移，直接跳过。

对于大于 $x$ 的 $a_i$，开一些新账户进行转移，每个新账户最多能转移 $x$ 单位的钱，同时消耗 $f$ 单位的手续费。容易得到至少需要 $\lceil\frac{a_i-x}{x+f}\rceil$ 个新账户并转移，同时消耗 $\lceil\frac{a_i-x}{x+f}\rceil\times f$ 单位的手续费。将所有的手续费求和即可。

这里提一下向上取整：$\lceil\frac{a}{b}\rceil=\lfloor\frac{a-1}{b}\rfloor+1$。

需要开 `long long`。

------------

### ${\color{#00CD00}\text{代码}}$

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 5;
int n, x, f, ans, a[N];
signed main(){
	ios::sync_with_stdio(false), cin.tie(nullptr);
	cin >> n;
	for(int i=1; i<=n; i++) cin >> a[i];
	cin >> x >> f;
	for(int i=1; i<=n; i++){
		if(a[i] <= x) continue;
		ans += (a[i] - x - 1) / (x + f) + 1;
	}
	cout << ans * f;
	return 0;
}
```

---

## 作者：LOVE_Ynoi (赞：1)

# CF1064F 题解
### 题目大意： 
给定一个数列 $A$ 和常数 $x$ , $f$ ，可以进行操作：将选定 $A_i = A_i - k$ ( $k$ 为任意正整数)，并将 $k-f$ 添加到 $A$ 末尾,每次操作的花费为 $f$ ,可以做任意次操作，求使 $\forall{i}$ 都满足 $A_i<x$ 的最小花费。  
### 思路：
对于每一个元素 $A_i > x$ ，都必须减去 $A_i-x$ 使其满足条件  
对于每一次操作，必须也使 $k-f \le x$  
所以每一次操作的 $k$ 的最大值就是 $x+f$  
所以单一元素的花费就是 $f\times\left\lceil\dfrac{A_i-x}  {x+f}\right\rceil$  
循环把每一个元素的花费加起来即可 (注意 ``long long`` )  
时间复杂度 $O(n)$ ,可以通过

### 代码：
```c++
#include<bits/stdc++.h>
using namespace std;
long long n;
long long a[200010];
long long x,f;
long long ans;
int main(){
    cin>>n;
    for(int i = 1;i<=n;i++) cin>>a[i];
    cin>>x>>f;
    for(int i = 1;i<=n;i++){
        if(a[i]>x)
            /*
            注意这里的(double) 如果是不加的话,提前自动向下取整   
            ceil无效果
            */
            ans += k*ceil((double)(a[i]-x)/(x+f));
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：albertting (赞：0)

本蒟蒻写的最快的黄题，没有之一。

### 思路

首先，我们需要推导每次分裂的代价。

为了使次数最少，我们尽量要使每次分裂分出来的比特币最多，也就是 $x$。

而每次分裂要花 $f$ 个比特币，所以每次分裂相当于从原来的比特币中拿走 $x + f$ 个。

对于每个 $a_i$ 我们需要分割的部分是 $a_i - x$ 个币，所以每组比特币我们需要拿的次数可以这样表示：

$$
\left \lceil \frac{a_i - x}{x  + f} \right \rceil 
$$

那么每次分裂要花的比特币数量就是：

$$
f \times \left \lceil \frac{a_i - x}{x  + f} \right \rceil 
$$

[AC 撒花！](https://www.luogu.com.cn/record/161207514)

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

long long n, a[200005], x, f;
long long ans;

int main()
{
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    scanf("%lld %lld", &x, &f);
    for(int i = 1; i <= n; i++)
        if(a[i] > x)
            ans += f * ceil((double)(1.0) * (a[i] - x) / (x + f));
    printf("%lld", ans);
	return 0;
}
```

在此提醒各位谷民：十年 OI 一场空，不开 ```long long``` 见祖宗！

---

## 作者：xuhanxi_dada117 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1046F)

# 题目大意

给定数组 $a$ 以及 $x,f$，每一次操作可以使 $a$ 中某个元素减 $k$，并在数组最后添加数 $k-f$。

求使 $\forall i:a[i]< x$ 的最小操作次数。

# 解法

考虑每个 $a[i]>x$:

为保证添加的数不超过 $x$，可以得出：
$$k-f\le x$$

也就是：

$$k\le x+f$$

所以对每个 $a[i]>x$，最小删除次数为：
$$\left\lceil\dfrac{a[i]-x}{x+f}\right\rceil$$

所以最终花费为：

$$f\times \left\lceil\dfrac{a[i]-x}{x+f}\right\rceil$$

对数组扫一遍计算答案即可。

时间复杂度 $\Theta(n)$。

# 代码

```cpp
#include<bits/stdc++.h>
#define N 200010
#define int long long //数据范围较大，开 long long
using namespace std;
int n,x,f,a[N],ans=0;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	scanf("%lld%lld",&x,&f);
	for(int i=1;i<=n;++i)
		if(a[i]>x) ans+=f*ceil((double)(a[i]-x)/(x+f));//扫一遍计算答案
	printf("%lld",ans);
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/list?pid=CF1046F)

---

