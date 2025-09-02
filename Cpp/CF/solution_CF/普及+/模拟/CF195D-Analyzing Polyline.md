# Analyzing Polyline

## 题目描述

As Valeric and Valerko were watching one of the last Euro Championship games in a sports bar, they broke a mug. Of course, the guys paid for it but the barman said that he will let them watch football in his bar only if they help his son complete a programming task. The task goes like that.

Let's consider a set of functions of the following form:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF195D/bc3a6f827f49bee100d9da6adde48766963384ee.png) Let's define a sum of $ n $ functions $ y_{1}(x),...,y_{n}(x) $ of the given type as function $ s(x)=y_{1}(x)+...+y_{n}(x) $ for any $ x $ . It's easy to show that in this case the graph $ s(x) $ is a polyline. You are given $ n $ functions of the given type, your task is to find the number of angles that do not equal 180 degrees, in the graph $ s(x) $ , that is the sum of the given functions.Valeric and Valerko really want to watch the next Euro Championship game, so they asked you to help them.

## 样例 #1

### 输入

```
1
1 0
```

### 输出

```
1
```

## 样例 #2

### 输入

```
3
1 0
0 2
-1 1
```

### 输出

```
2
```

## 样例 #3

### 输入

```
3
-2 -4
1 7
-5 1
```

### 输出

```
3
```

# 题解

## 作者：renrua52 (赞：2)

### 前言
我又打破了一道0提交0通过

------------

### 题意
给定n个函数 y=max(0, kx+b)中的k和b的值，将所有这些（被截断的一次）函数相加得到一个新的函数，求这个新函数的图像中有多少个拐点

------------

### 思路
如果你只是不了解题意，请再思考一会！此题比较简单  
如果依然没有思路，请继续往下看：  

------------
若两函数在x轴上方没有交点，如下图：  
![](https://i.loli.net/2020/03/10/oHt54izmvJ3LXsS.png)  
显然它们的和的图像几乎与原图像相同，拐点全部出现在x轴上，数目为2

------------
若两函数在x轴上恰有一个交点，如下图：  
![](https://i.loli.net/2020/03/10/5FxigH2YSnKNekU.png)  
它们的和的图像仍几乎与原图像相同，拐点出现在x轴上，数目为1

------------
若两函数在x轴上方恰有一个交点，如下图：  
![](https://i.loli.net/2020/03/10/up4FhWYiBXocgO6.png)  
不难证明，加和后，在D左侧和A右侧的图像仍不变，AD之间的图像在加和后仍为一次函数图像的一部分，解析为(k1+k2)x+(b1+b2)   
故在A和D正上方各存在一个拐点，数目为2

------------
至此不难发现，拐点数目=所有函数与x轴的不同的交点数  
我们知道，一次函数与x轴的交点横坐标为 -b/k  
用map或set维护之即可  
注意k, b数据范围正负1e9，相除后为确保不错误重复，要使用long double存储

------------

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n; long double k, b;
map<long double, bool> mp;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	while(n --){
		cin >> k >> b;
		if(k) mp[-b/k] = 1;
	}
	cout << mp.size() << "\n";

	return 0;
}

```

------------

### 后记
希望此次疫情早日结束，让大家拥抱心仪的女孩纸 qwq

---

## 作者：Special_Tony (赞：0)

# 思路
这题的每个算式的折点就在 $x=-\frac dk$ 的位置，然后这题其实就是求不同的 $\frac dk$ 的个数，这一点可以把这个分数约分然后把分子分母组成 pair 扔到 map 里去（当然也可以用 set 自动去重，也可以用高精度的浮点数代替 pair）。约分操作其实就是把 $d,k$ 都除以 $\gcd(d,k)$ 而已。$k=0$ 的情况要无视，因为它就是一条直线。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef pair <int, int> pii;
int n, sum, k, b, g;
map <pii, bool> vis;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	while (n --) {
		cin >> k >> b;
		if (k) {
			g = __gcd (k, b);
			k /= g, b /= g;
			if (k < 0)
				k *= -1, b *= -1;
			if (! vis[{k, b}])
				vis[{k, b}] = 1, ++ sum;
		}
	}
	cout << sum;
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
非常有意思的一道题目。

题意：给定 $n$ 个函数，第 $i$ 个函数 $y_i\left(x\right)$ 取 $k_i\times x+b_i$ 和 $0$ 中的较大值。定义函数 $s\left(x\right)=y_1\left(x\right)+y_2\left(x\right)+\dots+y_n\left(x\right)$，显然这个图像是一个折线，请你求出这个折线上有多少个拐点。
## 分析。
我们不妨从特殊值入手。对于每一个函数 $y_i\left(x\right)$ 的图像，如果 $k_i=0$ 那么就只剩下 $\left(b_i,0\right)$ 则没有拐点，否则必定存在至少一个拐点。那么这个拐点因为是一次函数，所以我们要使得函数值为 $0$ 则代入到 $y_i$ 中即可得到拐点在 $\left(-\frac{b_i}{k_i},0\right)$ 处。如果函数 $y_i$ 和 $y_j$ 存在两个不同的拐点，那么它们相截后形成的函数的图像的拐点也会有两个。同理，如果它们存在两个相同的拐点，那么它们和的函数的图像也只会有一个。这样我们不妨将 $s\left(x\right)$ 看做两两相加，这样问题就转换成了：求在 $y_1$ 到 $y_n$ 中不同的 $-\frac{b_i}{k_i}$ 的个数，每个不同的都代表一个拐点。

代码如下，仅供参考：
```
#include<iostream>
#include<set>
using namespace std;
set<long double> s;
int n,k,b;
int main(){
	cin>>n;
    for(int i=1;i<=n;i++){
        cin>>k>>b;
        if(k!=0){
		    s.insert((-(long double)b)/k);
		}
    }
	cout<<s.size()<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Yuby (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF195D)

#### 题意：

给定函数 $s(x)=y_1(x)+y_2(x)+....+y_n(x)$，其中 $y_i(x)=\max\left(0,k_i\times x+b_i\right)$，求 $s(x)$ 的函数图像中有多少个位置夹⻆不等于 $180^\circ$。

#### 分析：

注意到题目中的 $y_i(x)=\max\left(0,k_i\times x+b_i\right)$，发现每个函数对总体的贡献大于等于 0，只要找到函数

与 $x$ 轴的交点就行，因为从这个点往后函数对函数的贡献和之前不再是一条直线。这里也可以这样理解，每个函数都是一个分段函数，分两段，在 $k_i\times x+b_i \leq 0$ 和 $k_i\times x+b_i >0$ 时分别对 $s(x)$ 做出线性的贡献。

这个时候我们要注意若两个函数与 $x$ 轴的交点相同，其实对答案的贡献只有一个，问题转化为求 $n$ 个函数和 $x$ 轴的不同的交点。

为防止小数出现精度问题，我选择了模拟分数。（做完打开题解发现不需要

注意 0 要特殊处理，因为正常 gcd 算出来 都会是 $\frac{0}{x}$ 的形式但此处 $x$ 的值不重要，这东西一定为 0。

核心代码如下：

```cpp
ll n,k[MAXN],b[MAXN];
map<pair<ll,ll>,bool>mp;
vector<ll>use;
int main()
{
 	//freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
	n=read();
	ll ans=0;
	bool flag=0;
	for(ll i=1;i<=n;i++)
	{
		k[i]=read(),b[i]=read();
		if(!k[i])continue;
		ll up=-b[i],dow=k[i];
		if(!b[i])//0的情况
		{
			if(!flag)ans++;
			flag=1;
			continue;
		}
		if(dow<0)dow*=-1,up*=-1;
		bool flag1=0;
		if(up<0)flag1=1;//防止gcd出现奇怪的问题
		up=abs(up);
		ll gc=gcd(up,dow);
		dow/=gc,up/=gc;
		if(flag1)up*=-1;
		if(!mp[make_pair(up,dow)])ans++;
		mp[make_pair(up,dow)]=1;
	}
	write(ans);
	return 0;
}
```



---

