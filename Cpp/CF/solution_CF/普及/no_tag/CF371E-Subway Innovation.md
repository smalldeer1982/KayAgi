# Subway Innovation

## 题目描述

直线上 $n$ 个点，定义点 $i, j$之间的距离为 $|x_i-x_j|$。保留 $k$ 个点，使这些点**两两之间的距离和**最小。输出 $k$ 个点的下标。

## 样例 #1

### 输入

```
3
1 100 101
2
```

### 输出

```
2 3 ```

# 题解

## 作者：b6e0_ (赞：6)

[CF题面传送门](https://codeforces.com/contest/371/problem/E) [洛谷题面传送门](https://www.luogu.com.cn/problem/CF371E) [博客食用更佳](https://www.luogu.com.cn/blog/b6e0/tijie-CF371E)

下文中称一个区间每两个数之间的差的和为这个区间的值。

首先排序，然后贪心：取的数肯定是连续的。

然后因为长度已经确定了，所以只需要枚举左端点。考虑$a_i$~$a_{i+k-1}$（区间$1$）与$a_{i+1}$~$a_{i+k}$（区间$2$）两个区间的值怎么转移。$a_i$对区间$1$的值的贡献为：
$$\sum_{j=i+1}^{i+k-1}(a_j-a_i)$$
$$=\sum_{j=i+1}^{i+k-1}a_j-a_i\times(k-1)$$
$a_{i+k}$对区间$2$的贡献为：
$$\sum_{j=i+1}^{i+k-1}(a_{i+k}-a_j)$$
$$=a_{i+k}\times(k-1)-\sum_{j=i+1}^{i+k-1}a_j$$
设区间$1$的值为$x$，那么区间$2$的值为：
$$x-\left(\sum_{j=i+1}^{i+k-1}a_j-a_i\times(k-1)\right)+a_{i+k}\times(k-1)-\sum_{j=i+1}^{i+k-1}a_j$$
$$=x+(k-1)\times(a_i+a_{i+k})-2\times\sum_{j=i+1}^{i+k-1}a_j$$
其中：
$$\sum_{j=i+1}^{i+k-1}a_j$$
可以用前缀和优化。

代码：
```cpp
#include<bits/stdc++.h>
#define int long long//十年OI一场空，不开long long见祖宗！
using namespace std;
int s[300010];
pair<int,int>a[300010];//first存储值，second存储下标
signed main()
{
	int n,k,i,ans=0,minv,p=1;
	cin>>n;
	for(i=1;i<=n;i++)
	{
		cin>>a[i].first;
		a[i].second=i;
	}
	cin>>k;
	sort(a+1,a+n+1);
	for(i=1;i<=n;i++)
		s[i]=s[i-1]+a[i].first;//前缀和
	for(i=1;i<=k;i++)
		ans+=a[i].first*(i-1)-(s[i-1]-s[0]);//1开头的区间的值
	minv=ans;
	for(i=2;i<n-k+2;i++)
	{
		ans+=(k-1)*(a[i+k-1].first+a[i-1].first)-(s[i+k-2]-s[i-1])*2;//转移
		if(ans<minv)
		{
			minv=ans;
			p=i;
		}
	}
	for(i=p;i<p+k;i++)
		cout<<a[i].second<<' ';
	return 0;
}
```
时间复杂度为$O(n\log n)$（复杂度又到了sort上）

---

## 作者：sgl654321 (赞：0)

## 题目大意
直线上有 $n$ 个点，选出 $k$ 个点，使得这 $k$ 个点两两之间距离之和最小。输出这几个点的编号。

## 解题思路
首先，肯定是按这些点的坐标进行排序，然后你取出来的这 $k$ 个点，在坐标轴上肯定是连续的。为什么呢？比如说有四个点 $a,b,c,d(a<b<c<d)$，你选 $a,b,d$ 三个点，肯定不如 $a,b,c$ 或者 $b,c,d$ 来得优秀。

然后就变成了简单推式子的问题了。

假设你选的点，排序之后的编号是 $L\sim R$，其中 $R = L+k - 1$。

那么你要求的就是：

$$\sum_{i = L +1}^{R} \sum_{j = L}^{i - 1} (x_i- x_j)$$

考虑把被减数和减数分开考虑。

被减数之和：

$$S_1 = \sum_{i = L}^R (i - L + 1) \times a_i = \sum_{i = L}^R ia_i + (1-L)\sum_{i = L}^R a_i$$

减数之和：

$$S_2 = \sum_{i = L}^R (k + L - i)\times a_i =(k+L)\sum_{i = L}^R a_i -  \sum_{i = L}^R ia_i $$

两者相减就可以得到答案了。

$$S_1 - S_2 = 2\sum_{i = L}^R ia_i + (1 - k - 2L)\sum_{i = L}^R a_i$$

前缀和优化即可。没有 2000 的难度。

## 参考代码
注意点：初始答案开成 `LONG_LONG_MAX`，因为这个答案可以达到 $9\times 10^{18}$ 级别。

```cpp
#include<bits/stdc++.h>
#define maxn 300010
using namespace std;
typedef long long ll; 
struct node{
	ll id, val;
} c[maxn]; 
ll n, a[maxn], s[maxn], s2[maxn], ans, l, r, tmp, k;
bool cmp(node n1, node n2){
	return n1.val < n2.val;
}
int main(){
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> c[i].val, c[i].id = i;
	sort(c + 1, c + 1 + n, cmp);
	for(int i = 1; i <= n; i++) a[i] = c[i].val;
	cin >> k;
	
	
	for(int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
	for(int i = 1; i <= n; i++) s2[i] = s2[i - 1] + a[i] * i;
	
	ans = LONG_LONG_MAX;
	for(int i = 1; i <= n - k + 1; i ++){
		tmp = 2 * (s2[i + k - 1] - s2[i - 1]) + (1 - k - 2 * i)
		* (s[i + k - 1] - s[i - 1]);	
		
		if(tmp < ans){
			l = i; r = i + k - 1;
			ans = tmp;
		}
	}	
	for(int i = l; i <= r; i++) cout << c[i].id << ' ';
	cout << endl;
	return 0;
}
```

---

## 作者：skyskyCCC (赞：0)

## 前言。
题目内容：在直线上给定 $n$ 个点，定义其距离为横坐标的绝对值，请你保留 $k$ 个点，使这些点两两之间的距离和最小，输出这 $k$ 个点的坐标。

看到距离和这三个字我们不难发现这道题可能是前缀和有关题目，又是一道平面几何题，我们考虑从点的方向上下手。
## 分析。
我们可以发现，所有的点都在同一条直线上，所以我们不妨将这几个点按横坐标从小到大排列，此时我们易知如果要去的点的距离和尽可能小，则必定存在这 $k$ 个点是该直线上连续的 $k$ 个点。简单来说，就是现在我们取排好序的这几个点中的 $a_i$ 则如果我们取它后面紧挨着的 $a_j$ 之间的距离，必定比取它后面的后面的 $a_k$ 的距离要更优。所以我们只要找到一个区间，使得该区间内的 $k$ 个点的最小值在所有可能的区间内最小即可。

直接暴力枚举 $3\times10^5$ 个点显然是不太现实的。我们考虑能不能从一个区间推出下一个区间。我们去求区间内的距离和，我们也可以将两个区间作差，根据结果的正负性判断谁大。那么我们考虑两个相邻的区间 $\left[l,r\right]$ 和 $\left[l+1,r\right]$ 的距离和之差，则有取得差的公式：
$$\sum_{i=l+1}^{r+1}\sum_{j=i+1}^{r+1}\left(x_j-x_i\right)-\sum_{i=l}^r\sum_{j=i+1}^r\left(x_j-x_i\right)$$
可以发现能够化为以下公式：
$$\sum_{i=l+1}^r\left(x_{r+1}-x_i\right)-\sum_{i=l+1}^r\left(x_i-x_l\right)$$
此时就不是很难了，我们将上面的式子展开，在简单合并一下，就有：
$$\left(r-l\right)\left(x_{r+1}-x_l\right)-2\times\sum_{i=l+1}^rx_i$$
现在的算法就很显然了，先维护一个长度为 $k$ 的连续区间的最小和，然后记录一下相邻的两个区间内的差值存到前缀和中去，有了差值的前缀和，我们就可以轻松地求出两个区间 $\left[i,i+k-1\right]$ 和 $\left[1,k\right]$ 这段的区间差值，选一个差值尽可能小的即可。

代码如下，仅供参考：
```
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int n,k;
long long sum1,sum2,ans,id;
struct node{
	int x,y;
}a[300005];
bool cmp(node fir,node sed){
	//if(fir.x==sed.x){
	//	return fir.y<sed.y;
	//}
	return fir.x<sed.x;
}
int main(){
	cin>>n;
	for (int i=0;i<n;i++){
		cin>>a[i].x;
		a[i].y=i+1;
	}
	sort(a,a+n,cmp);
	cin>>k;
	for (int i=0;i<k;i++){
		sum1+=a[i].x;
	}
	for (int i=k;i<n;i++){
		sum2+=1ll*(k-1)*(a[i].x+a[i-k].x)-2ll*(sum1-a[i-k].x);
		sum1+=a[i].x-a[i-k].x;
		if(sum2<ans){
			ans=sum2;
			id=i-k+1;
		}
	}
	for (int i=0;i<k;i++){
		cout<<a[id+i].y<<" ";
	}
	return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：Infinity_G (赞：0)

首先我们将这 $n$ 个点按照坐标从小到大排序，那么一定是取连续的 $k$ 个点最优。

考虑维护每连续 $k$ 个点两两之间的距离之和，显然是每次在后面加入一个点，在前面删除一个点。由于删除和加入类似，我们只讨论加入的情况，那么加入一个点对答案的贡献为

$$\sum_{j=i-k+1}^{i-1}x_i-x_j=(k-1)\times x_i-\sum_{j=i-k+1}^{i-1}x_j$$

前半部分可以直接算，后半部分用前缀和维护即可，时间复杂度 $O(n\log n)$。

---

