# Card Constructions

## 题目描述

A card pyramid of height $ 1 $ is constructed by resting two cards against each other. For $ h>1 $ , a card pyramid of height $ h $ is constructed by placing a card pyramid of height $ h-1 $ onto a base. A base consists of $ h $ pyramids of height $ 1 $ , and $ h-1 $ cards on top. For example, card pyramids of heights $ 1 $ , $ 2 $ , and $ 3 $ look as follows:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1345B/c8f889835ab0788603a3c97f750b5560a2dca9f4.png)You start with $ n $ cards and build the tallest pyramid that you can. If there are some cards remaining, you build the tallest pyramid possible with the remaining cards. You repeat this process until it is impossible to build another pyramid. In the end, how many pyramids will you have constructed?

## 说明/提示

In the first test, you construct a pyramid of height $ 1 $ with $ 2 $ cards. There is $ 1 $ card remaining, which is not enough to build a pyramid.

In the second test, you build two pyramids, each of height $ 2 $ , with no cards remaining.

In the third test, you build one pyramid of height $ 3 $ , with no cards remaining.

In the fourth test, you build one pyramid of height $ 3 $ with $ 9 $ cards remaining. Then you build a pyramid of height $ 2 $ with $ 2 $ cards remaining. Then you build a final pyramid of height $ 1 $ with no cards remaining.

In the fifth test, one card is not enough to build any pyramids.

## 样例 #1

### 输入

```
5
3
14
15
24
1```

### 输出

```
1
2
1
3
0```

# 题解

## 作者：bbbzzx (赞：4)

高度为 $n$ 的卡片堆一定用去 $\frac{n(3n+1)}{2}$ 的卡片。
### 代码如下
```cpp
#include<bits/stdc++.h>
using namespace std;
long long t,n,h,s,k;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		s=0,k=n;//初始化 
		while(k>1)
		{
			h=floor((sqrt(1+24*k)-1)/6);//不需要二分,直接更新高度 
			k-=(h*(3*h+1))/2;//递推式 
			s++;//统计 
		}
		cout<<s<<endl;
	}
	return 0;
}
```
加了防抄袭，勿抄谢谢。

---

## 作者：Isshiki_Hugh (赞：4)

做法：打表+贪心+二分查找

做法显然，找到需求量比当前牌数小的最大的塔，然后减去它，再继续找，直到找不到为止。

首先利用递推式打表得到高度为`h`的塔所需要的牌数`a[h]`

- `a[i] = a[i-1]  + 3 * i - 1`
- (在高度为i的塔的右侧增加`i`个三角形，减去最下面的那个三角形不用底边)

然后再不断用二分查找比当前小的最大的。


```cpp
int T,a[30000],ans,m;

inline ll find(ll x){
    int l = 1, r = 27000;
    while(l <= r){
        m = (l + r) / 2;
        if(a[m] == x) return m;
        else if(a[m] < x) l = m + 1;
        else r = m - 1;
    }
    if(a[m] == x) return m;
    else if(a[m] < x) return m;
    else return m = m-1;
}
int main(){
    //std::ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("in.in", "r", stdin);
    cin >> T;
    ll x;
    a[1] = 2;
    rep(i,1,27000) a[i] = a[i-1] + 3 * i -1;

    while(T--){
        ans = 0;
        cin >> x;
        while(find(x) > 0){
            x -= a[m];
            ++ans;
        }
        cout << ans << "\n";
    }

    return 0;
}

```

---

## 作者：andyli (赞：4)

由 [OEIS A005449](https://oeis.org/A005449) 得高度为 $n$ 用去 $\dfrac{n(3n + 1)}{2}$ 个卡片。因此，每次二分最大可能的卡片数即可。  

代码如下（[模板](https://www.luogu.com.cn/blog/andyli/read-template)）：  
```cpp
int main() {
    int q;
    io.read(q);
    while (q--) {
        int n;
        io.read(n);
        int cnt = 0;
        while (n > 1) {
            int l = 1, r = n;
            while (l < r) {
                int m = (l + r + 1) >> 1;
                if (LL(m) * (3LL * m + 1) / 2 <= n)
                    l = m;
                else
                    r = m - 1;
            }
            cnt++;
            n -= LL(l) * (3LL * l + 1) / 2;
        }
        writeln(cnt);
    }
    return 0;
}
```

---

## 作者：yu__xuan (赞：1)

### 题目
[CF1345B Card Constructions](https://www.luogu.com.cn/problem/CF1345B)

### 思路
暴力。
根据下面的代码可以得到高度为 $30000$ 的金字塔就已经超过了 $1000000000$。
```cpp
h[1]=2;
for(int i=2;i<=30000;++i) {
	h[i]=h[i-1]+(i-1)+2*(i);
}
```
然后测试点最多 $1000$ 个，复杂度可以。

### Code
```cpp
#include<cstdio>
#include<cstring>
#include<string>
#include<iostream>
#include<algorithm>

inline void read(int &T) {
	int x=0;bool f=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=!f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	T=f?-x:x;
}

int t,h[30001];

int main() {
	h[1]=2;
	for(int i=2;i<=30000;++i) {
		h[i]=h[i-1]+(i-1)+2*(i);
	}
	read(t);
	while(t--) {
		int ans=0,x;read(x);
		for(int i=30000;i>=1;--i) {
			if(x>=h[i]) {
				ans+=x/h[i];
				x-=x/h[i]*h[i];
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：felixshu (赞：0)

[我是传送门](https://www.luogu.com.cn/problem/CF1345B)

##  题目大意

你在玩一种扑克搭建金字塔的游戏，其中高度为 $1、2、3$ 的金字塔是这个样子：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1345B/c8f889835ab0788603a3c97f750b5560a2dca9f4.png)

现在你有 $n$ 张扑克牌，你有一种搭建策略：每次你会用你手中牌搭建可以搭建高度最大的金字塔，重复这个过程，直至手中的牌无法搭建任何一个金字塔。

问：你最多可以搭建几个金字塔？

## 分析

这题可以打表找规律。可以发现：

- 如果高度为 $i$，那么要用 $h[i]=h[i-1]+(i-1)+2*i$ 张卡片。

- 要开 ```long long```。

那么这个递推公式是怎么来的呢？

可以发现，每一个三角形都会有一个顶点是空的。补上这个空的地方需要  $i-1$ 张扑克。

然后下方，还有加上 $i$ 个最小的三角形要 $2\times i$ 张扑克。然后就可以得出这个递推公式了。

用这个代码来获取高度并存在数组 $h$ 中。
```
	for(int i=2;i<=30000;++i) 
	{
	h[i]=h[i-1]+(i-1)+2*(i);
	}
```

------------

那么，就先试试直接打暴力搜索。


然后从 $2$ 开始枚举。然后发现不行。



------------

就只能去试试二分了。这里可以直接用函数 ```upper_bound``` 搜索第一个要用的扑克大于 $n$ 的高度，然后 $n$ 减去这个高度的扑克数就好了。

## 下面是 AC 代码
```
#include<bits/stdc++.h>
using namespace std;
int main()
{
long long t,n,s,k,h[30000];
	cin>>t;
	h[1]=2;
	for(int i=2;i<=30000;++i) 
	{
	h[i]=h[i-1]+(i-1)+2*(i);
	}
	while(t--)
	{
		cin>>n;
		s=0;
		int i=1;
		while(n>=2)
		{
			int pos1=upper_bound(h,h+30000,n)-h; 
		//	cout<<h[pos1-1]<<" ";
			n-=h[pos1-1];
			s++;
		}
				
			
		cout<<s<<endl;
	}
	return 0;
}
```





  

---

## 作者：xxxalq (赞：0)

[洛谷链接](https://www.luogu.com.cn/problem/CF1345B) & [CF链接](http://codeforces.com/problemset/problem/1345/B)

## 思路分析：
首先搭每个金字塔所需的扑克牌数并不会由 $n$ 决定，所以我首先想到打表。抱着信心尝试一番之后

![](https://discourse.xinyoudui.com/uploads/default/original/2X/f/fc21ad631fef34735e63cd2fe74f93c2ef738de4.png)

![](https://discourse.xinyoudui.com/uploads/default/original/2X/b/b0313f4f48cd5728d71f22ae5ee60d89562a0e5b.png)

既然文件太大提交不了，那我们就放弃，怎么可能，下面我们来简单的计算一波，打表时间复杂度 $O(n)$，二分时间复杂度 $O(\log n)$，所以打表和二分结合。

所以这一题的思路就是：把打表程序放在主程序里，用二分查找搭成最大金字塔所需扑克牌数量，再通过递归解决。

既然要预处理，那就先分析一下金字塔的规律：

![](https://discourse.xinyoudui.com/uploads/default/optimized/2X/2/2b0d28bb5ba445c55bb32d025ccdbbb6648dd32b_2_690x323.jpeg)

总结规律：每两个相邻的金字塔所需纸牌数差依次增加 $3$。

接着用二分查找出离 $n$ 最近的金字塔，然后减去那个数在递归查找剩下的，知道小于 $2$ 为止，因为最小的金字塔要 $2$ 张扑克牌。

## 代码：

```cpp
#include<iostream>
using namespace std;
int a[25850];//预处理数组 
int t,n;//由题意 
int ans=0;//记录答案 
void dg(int x){
	if(x<2){
		return;
	}//递归终止条件 
	int l=0,r=25850,mid;//r=25850是打表测出来的，在1e9内有25820种不同的金字塔结果，开大一点到25850 
	while(l<r){//二分 
		mid=(l+r+1)/2;
		if(a[mid]>x){
			r=mid-1;
		}else{
			l=mid;
		}
	}//找不大于x的最大值下标 
	ans+=1;//答案加一 
	dg(x-a[l]);//剩下的继续找 
	return;
}
int main(){
	int cnt=0/*所需扑克牌张数*/,tmp=2/*差值*/,idx=-1;//a数组下标 
	while(cnt<=1000000000){ 
		cnt+=tmp;
		tmp+=3;//差值加3 
		idx+=1;//下标加一 
		a[idx]=cnt;
	}//在输入前预处理(打表) 
	cin>>t;
	while(t--){//t次询问 
		ans=0;//答案初始化 
		cin>>n;
		dg(n);//递归调用 
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：FiraCode (赞：0)

## 题解思路：
我们发现：

当搭高度为 $1$ 时，那么他就只用两个牌。

当塔高度为 $i$ 时，那么他就是把第 $i - 1$ 个封口在加上 $i$ 个尖，如图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5uyrqi3g.png)

就的到了一下公式：（$f_{i}$ 代表高为 $i$ 的金字塔的牌的数量）

$\left\{\begin{matrix}
f_{1} = 2\\
f_{i} = f_{i - 1} + i - 1 + 2 \times i
\end{matrix}\right.$

然后根据题意二分求出第一个 $\le$ 牌数的 $f$ 值，然后减去就可以了！
 
## AC CODE:
```cpp
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
int T;
int cnt;
int f[100010];
void init () {
	f[1] = 2;
	for (cnt = 2; f[cnt - 1] <= 1000000000; ++ cnt)
		f[cnt] = f[cnt - 1] + cnt - 1 + 2 * cnt;//预处理搭建i高的金字塔的纸牌数 
}
int main() {
	init ();
	-- cnt;//因为是第一个>1000000000的才会跳出，所以，cnt要-- 
	scanf ("%d" , &T);
	while (T --) {
		int n;
		scanf ("%d" , &n);
		int ans = 0;
		int mid = 0;
		do {
			int l = 1 , r = cnt;
			while (l <= r) {//二分
				mid = (l + r) >> 1;
				if (f[mid] == n) break;//找到了直接退出 
				else if(f[mid] < n) l = mid + 1;
				else r = mid - 1;
			}
			if (f[mid] > n) mid --;//若比他大了就-- 
			if (mid <= 0) break; //若mid小于等于0就是没有小于等于n的了 
			n -= f[mid];//减去用的纸牌数 
			ans ++;//搭了一个 
		}while (true);
		printf ("%d\n" , ans);
	}
	return 0;
}
```
码字不易，求赞！

---

## 作者：换个思路 (赞：0)

先暴力求出给定的a数组(叠i高的三角形要的个数)。让后对给定的n一顿乱求解就ok~~ 代码很丑 请见谅~~
```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int t, n, a[10000010], z;
int getnum(int n) {
	for (int i = 1; ; i++) {
		if (a[i] > z) {
			z -= a[i - 1]; break;
		}
	}
	return z;
}
int main(void) {
	cin >> t;
	int count = 5;
	a[1] = 2;
	for (int i = 2; a[i - 1] <= 1000000001; i++) {
		a[i] += a[i - 1] + count; count += 3;
	}
	while (t--) {
		cin >> z; int time = 0;
		while (z >= 2) {
			z = getnum(z);
			time++;
		}
		cout << time << endl;
	}
	return 0;
}
```

---

## 作者：shengyeqi (赞：0)

## 题面

[题目传送门](https://www.luogu.com.cn/problem/CF1345B)

## 思路

根据样例，可以推出公式：高度为 $n$ 的金字塔一定用去 $n\times(n\times 3 +1)\div 2$。

代码套用公式即可。

## 代码

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	long long t;
	cin>>t;
	while(t--)
	{
		long long n;
		cin>>n;
		long long sum=0,ti=n,gao;//ti为n的替身，gao为高度
		while(ti>1)
		{
			gao=(sqrt(1+24*ti)-1)/6;
			ti-=(gao*(3*gao+1))/2; 
			sum++;
		}
		cout<<sum<<"\n";//别忘了换行
	}
	return 0;
}
```


---

