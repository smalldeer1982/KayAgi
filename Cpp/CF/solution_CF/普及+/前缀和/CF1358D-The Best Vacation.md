# The Best Vacation

## 题目描述

由于本场题面违反互联网相关法律，不予展示原题面。

## 说明/提示

In the first test case, the numbers of the days in a year are (indices of days in a corresponding month) $ \{1,1,2,3,1\} $ . Coronavirus-chan will hug you the most if you come on the third day of the year: $ 2+3=5 $ hugs.

In the second test case, the numbers of the days are $ \{1,2,3,1,2,3,1,2,3\} $ . You will get the most hugs if you arrive on the third day of the year: $ 3+1+2+3+1+2=12 $ hugs.

In the third test case, the numbers of the days are $ \{1,2,3,4,1,2, 1,2,3, 1, 1,2,3\} $ . You will get the most hugs if you come on the twelfth day of the year: your friend will hug you $ 2+3+1+2+3+4=15 $ times.

## 样例 #1

### 输入

```
3 2
1 3 1```

### 输出

```
5```

## 样例 #2

### 输入

```
3 6
3 3 3```

### 输出

```
12```

## 样例 #3

### 输入

```
5 6
4 2 3 1 3```

### 输出

```
15```

# 题解

## 作者：_xbn (赞：4)

考虑贪心，在同一个月内，月末的拥抱数肯定比月初多，所以取月末比取月初更优，所以**答案肯定是连续几个月加上某个月的月末的拥抱数**。

所以我们可以考虑枚举能取的最后一个月，根据上述性质，这个月肯定是取到月底的。

之后我们找到之前最多能取到那一天，这个可以用二分实现，在代码中用 lower_bound 实现二分。然后累加答案即可。

如果暴力实现累加会 TLE。我们可以用前缀和记录到这个月为止的拥抱数。这样就可以跑过了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 500002;
int s1[N], s2[N], a[N], b[N], n, m, c[N], p, k, t, l, r, ans = -1e18, sum, tot, cnt, x;
inline int rd()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
signed main()
{
    n = rd(), x = rd();
    for (int i = 1; i <= n; i++) a[i] = rd(), s1[i] = s1[i - 1] + a[i], s2[i] = s2[i - 1] + (a[i] + 1) * a[i] / 2;
    for (int i = n + 1; i <= 2 * n; i++) s1[i] = s1[i - 1] + a[i - n], s2[i] = s2[i - 1] + (a[i - n] + 1) * a[i - n] / 2;
    for (int i = 1; i <= 2 * n; i++)
    {
        if(s1[i] < x) continue;
        int pos = lower_bound(s1 + 1, s1 + 1 + 2 * n, s1[i] - x) - s1;
        int tmp = s2[i] - s2[pos];
        tot = x - s1[i] + s1[pos];
        tmp += (a[pos] - tot + 1 + a[pos]) * tot / 2;
        ans = max(tmp, ans);
    }
    cout << ans << endl;
    return 0;
}
```


---

## 作者：Fairicle (赞：3)

题解没有双指针的写法啊，那我就写一个（个人拙见认为此题双指针比二分好写，还更优）

由于这题的性质，去拜访最后一天必定是某个月的最后一天，就考虑枚举第 $i$ 个月，然后再开一个 $j$ 指针随着 $i$ 的移动而移动，保证他们之间的天数不超过题目给定的 $x$。

代码更便于理解：
```cpp
#define ll long long
#define ri register int
ll n,k;
#define N 200010
ll d[N*2],sd[N*2],sh[N*2],ans;//别忘了开两倍，类似于断环成链
int main()
{
	n=rd(),k=rd();
	for(ri i=1;i<=n;++i) d[i]=rd(),d[i+n]=d[i];
	for(ri i=1;i<=2*n;++i){
		sd[i]=d[i]+sd[i-1];//天数前缀和
		sh[i]=sh[i-1]+(d[i]*(d[i]+1)/2);//拥抱数前缀和
	}
	for(ri i=1,j=0;i<=2*n;++i){
		while(sd[i]-sd[j]>k) ++j;
		if(sd[i]>=k){//不加这一句会导致玄学错误，因为j的初值是0导致出现负数和奇奇怪怪的东西
			ll tmp=sh[i]-sh[j];
			ll res=k-sd[i]+sd[j];//多余的天数
			tmp+=(2*d[j]+1-res)*res/2;
			ans=max(ans,tmp);
		}
	}
	cout<<ans;
    return 0;
}
```
目前是提交记录的rank1

---

## 作者：KellyFrog (赞：3)

~~因为特判了但没写`else`所以`WA on test #23`的我，我好惨啊嘤嘤嘤。~~

## CF 1358D The Best Vacation
数据表明这将是一个$O(n)$或者$O(n\log n)$的算法。

从$i$个月开始，一直待着，待完$i+j$个月（若超过一年就是下一年）剩$k$天，那么明显有$d_{i+j+1}>k$，我们第$i$个月的前$d_{i+j+1}-k$天移到第$i+j+1$个月去，把第$i+j+1$个月填满，明显应该更优（因为换之前是1开始，后面的开始点是$\ge1$的）。

那么我们枚举起点，找到$i+j$，就就能够根据上面的结论找出当前的结果，更新答案即可。

用一个变量维护上一次$i+j$的结果可以做到$O(n)$，当然考试的时候写了个二分，复杂度$O(n\log n)$，同样可以通过此题，下面是二分的解法。

注意：

- 破环成链
- 别忘了判$x<d_i$的情况
- 开`long long`

code：
```cpp
#include <iostream>

using namespace std;

#define int long long

const int MAXN = 2e5 + 5;

int sum[MAXN << 1], a[MAXN << 1], suma[MAXN << 1];
int n, d;

int bs(int p) {
	int left = p, right = n << 1;
	int res = 0;
	while(left <= right) {
		int mid = (left + right) >> 1;
		if(sum[mid] - sum[p - 1] <= d) {
			res = mid;
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return res;
}

signed main() {
	cin >> n >> d;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		a[i + n] = a[i]; //破环成链
	}
	for(int i = 1; i <= n << 1; i++) {
		sum[i] = sum[i - 1] + a[i];
		suma[i] = suma[i - 1] + a[i] * (a[i] + 1) / 2;  //前缀和，suma是拥抱数
	}
	int ans = -1;
	for(int i = 1; i <= n; i++) {
		int b = bs(i); 
		if(b == 0) {
			int l = a[i] - d;
			ans = max(ans, a[i] * (a[i] + 1) / 2 - l * (l + 1) / 2);
		} else if(sum[b] - sum[i - 1] == d) { //考试的时候这行少写一个else，rating就莫得了
			ans = max(ans, suma[b] - suma[i - 1]);
		} else {
			int l = d - (sum[b] - sum[i - 1]); //还剩几天（在b+1）个月
			int l2 = a[b + 1] - l; //填满b+1月还要几天
			ans = max(ans, suma[b + 1] - suma[i - 1] - l2 * (l2 + 1) / 2);
		}
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：juicyyou (赞：2)

# CF1358D The Best Vacation
~~因为少判了一种情况FST，我太难了。。。~~

题目大意有点长就不放了。

## 解法
考虑一段合法的区间，那么，如果这个区间的两个端点都不在一个月的月末，那么我们考虑把这个区间向后移动一格：

设这个区间的第一天为 $k$，最后一天为 $k + x$，第 $i$ 天的拥抱数为 $h_i$，则有：

原来的区间和为：
$$\sum\limits_{i = k}^{k+x}h_i$$

那向前移动一天呢？
$$\sum\limits_{i = k}^{k + x}h_i - h_k + h_{k + x} + 1$$

于是就增加了 $ h_{k + x}- h_k + 1$ 个拥抱。

而第一天和最后一天的差，只要这两天不进入新的月份，那就一直不变。由此看来，这个区间只要第一天和最后一天不进入新的月份，那么向前滑动的时候要不然就是递增，要不然就是递减。所以我们只要看第一天在月初，第一天在月末，最后一天在月初，最后一天在月末这四种情况，然后进行二分 + 前缀和就行了。

最后，注意要断环为链并且一定要注意**一个月的天数比 $x$ 还大**的情况！！( 因为这个FST了。。。。

下面是我的Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll maxn = 4e5 + 5;
const ll maxm = 1e3 + 5;
inline void qread(){}
template<class T1, class ...T2>
inline void qread(T1 &IEE, T2&... ls){
	register T1 __ = 0, ___ = 1;
	register char ch;
	while(!isdigit(ch = getchar())) ___ = (ch == '-') ? -___ : ___;
	do{
		__ = (__ << 1) + (__ << 3) + (ch ^ 48);
	}while(isdigit(ch = getchar()));
	__ *= ___;
	IEE = __;
	qread(ls...);
	return ;
}
ll n, x, ans;
ll a[maxn], f[maxn], v[maxn];
ll count(ll x){
	return x * (x + 1) / 2;
}
int main(){
	qread(n, x);
	for(int i = 1;i <= n;i++){
		qread(a[i]);
		a[i + n] = a[i];
	}
	for(int i = 1;i <= 2 * n;i++){
		f[i] = f[i - 1] + a[i];
		v[i] = v[i - 1] + a[i] * (a[i] + 1) / 2;
	}
	for(int i = 1;i <= n;i++){
		if(a[i] >= x){
			ans = max(ans, count(a[i]) - count(a[i] - x));
			continue;
		}
		int l = 1, r = 2 * n, cur = i;
		while(l <= r){
			ll mid = (l + r) >> 1;
			if(f[mid] - f[i - 1] <= x){
				l = mid + 1;
				cur = mid;
			} else {
				r = mid - 1;
			}
		}
		ans = max(ans, v[cur] - v[i - 1] + count((x - (f[cur] - f[i - 1]))));
	}
	for(int i = 1;i <= n;i++){
		if(a[i] >= x) continue;
		int l = 1, r = 2 * n, cur = i;
		while(l <= r){
			ll mid = (l + r) >> 1;
			if(f[mid] - f[i] + 1 <= x){
				l = mid + 1;
				cur = mid;
			} else {
				r = mid - 1;
			}
		}
		ans = max(ans, v[cur] - v[i] + a[i] + count(x - (f[cur] - f[i] + 1)));
	}
	for(int i = n + 1;i <= 2 *n;i++){
		if(a[i] >= x) continue;
		int l = 1, r = 2 * n, cur = i;
		while(l <= r){
			ll mid = (l + r) >> 1;
			if(f[i - 1] - f[mid - 1] + 1 <= x){
				r = mid - 1;
				cur = mid;
			} else {
				l = mid + 1;
			}
		}
		ans = max(ans, v[i - 1] - v[cur - 1] + 1 + 
		count(a[cur - 1]) - count(a[cur - 1] - (x - 1 - f[i - 1] + f[cur - 1])));
	}
	for(int i = n + 1;i <= 2 * n;i++){
		if(a[i] >= x) continue;
		int l = 1, r = 2 * n, cur = i;
		while(l <= r){
			ll mid = (l + r) >> 1;
			if(f[i] - f[mid - 1] <= x){
				r = mid - 1;
				cur = mid;
			} else {
				l = mid + 1;
			}
		}
		ll res = x - f[i] + f[cur - 1];
		ans = max(ans, v[i] - v[cur - 1] + count(a[cur - 1]) - count(a[cur - 1] - res));
	}
	cout << ans << endl;
	return 0;
}
```

上述算法的复杂度为 $O(n \log n)$，可以通过此题。

---

## 作者：xlqs23 (赞：2)

**题意：** 一年有$n$个月，第$i$月有$d[i]$天，而一个月的第$j$天可以拥抱$j$次。试问选择一年中的哪个连续$xt$天可以得到最多得拥抱$ans$？求出最大拥抱值$ans$.

**思路:**
显然若要在某个月中开始选择，那首当其冲得就是月末的那天(贡献值最大)。所有应该从某个月的月末那天开始向前选择连续$x$天。

首先得预处理$sum$函数来记录连续i天的拥抱值(题目给出可能达到$1e6$)

那么我们可以枚举第i月为选择的末月，计算出当前情况的时间拥抱值summ，再与答案$ans$取个$max$就行啦。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int  inf = 0x7fffffff;
const int  N = 2e5 + 5, M = 1e6 + 5;
int n, x, pos ,summ, ans;
int d[N], sum[M];

int main()
{
    //预处理sum数组
    for(int i = 1; i <= M; i ++)
        sum[i] = sum[i - 1] + i;
    
    cin >> n >> x;
    for(int i = 1; i <= n; i ++)
        cin >> d[i];

    pos = n;
    //以i为末月的选择向前枚举
    for(int i = n; i; i --){
        while(x > 0){ //只要还有剩余天数科选
            x -= d[pos]; //先选中第pos月
            summ += sum[d[pos]]; //把第pos月的贡献加入临时答案

            if(pos == 1) pos = n; // 若pos到1就首位循环
            else pos --;
        }
        //去掉多选的几天，计算出实际总和，再取个max
        ans = max(ans, summ - (1 - x) * (-x) / 2); 
        //去掉第i月的贡献，再进入下一个循环(以i - 1为末月的选择)
        summ -= sum[d[i]];
        x += d[i];
    }

    cout << ans << endl;

    return 0;
}

---

## 作者：Michael1234 (赞：1)

本题可以使用贪心和二分的思想：

首先我们可以确定，我们所选的这些天数一部分填满一整个月，一部分填充一个月中的几天。

那么我们通过贪心的思想可以得知，我们在将零散的几天放在某月月末几天时，所得到的拥抱数最多。

由此，我们可以先枚举每个月，假设从当前月末开始向前有连续几个被填满的月和一个没被填满的月，再使用二分枚举哪天开始访问，并计算总拥抱数，最后求最大即可。

二分、求答案时，注意还需维护一个天数前缀和及一个拥抱数前缀和，由于其还可以使用第二年的天数，所以数组、前缀和都要维护至 $2n$。

最终时间复杂度为 $O(n\log_2n)$。

---

## 作者：_JF_ (赞：0)

[Link](https://www.luogu.com.cn/problem/CF1358D)

补一下前几天看的题，***1900**，独立切了。

~~你说得对，但是我前年[期中考题解](https://www.luogu.com.cn/article/rqccjqea)然后爆炸，现在期末考前一天写题解，如何呢？~~

首先把 $d_i$ 展开成 $[1,d_i]$ 的一个序列，这样直接做是 $O((\sum d_i)^2)$ 的，无法接受。

但是我们可以在这个序列上观察思考。

我们注意到这个序列是分段单调的一个东西。且单调区间的公差是一。

所以我们考虑优化的方向，是对每段怎么去计算这个答案。

我们不妨以当前第 $i$ 段的 $1$ 作为开头，那么我们要计算 $[1,a_i]$ 为开头的答案。

注意到结尾构成的区间，也是若干段单调区间，且从第二段开始，每段的开头一定是 $1$。

不难注意到从第二段开始以后的都是不优的。假设在第二段开始，右端点是 $1$，这时候左端点一定 $\ge 1$，思考移动的过程，左边减掉的数一定不小于右边，所以不优。

所以我们只用专心考虑第一段单调区间，能发现我们都是能移动就移动，因为第一段单调区间的开始的数不小于 $1$。

然后根据我们的定义计算答案就行了，预处理每个位置结尾的第一段二分或者双指针都行，我用了二分。

时间复杂度 $O(n \log n)$，哦，还要断环成链。

~~由于本场题面违反互联网相关法律，不予展示原题面。~~


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N =1e6+10;
#define int long long 
int a[N],Day[N],s[N],n,x; 
int cal(int dus){
	return (1+dus)*dus/2;
}
int Find(int L){
	int l=L-1,r=n+1;
	while(l+1<r){
		int mid=(l+r)>>1;
		if(Day[mid]-Day[L-1]>=x)	r=mid;
		else l=mid;
	}
	return r;
}
signed main(){
	cin>>n>>x;
	for(int i=1;i<=n;i++)	cin>>a[i],a[i+n]=a[i];
	n*=2; int ans=0; 
	for(int i=1;i<=n;i++)	Day[i]=Day[i-1]+a[i],s[i]=s[i-1]+cal(a[i]);
	for(int i=1;i<=n;i++){
		if(Day[n]-Day[i-1]<x)	continue;
		int now=Find(i),lst=a[i];
		if(a[i]>=x){
			ans=max(ans,cal(a[i])-cal(a[i]-x));
			continue;
		} 
//		cout<<i<<' '<<now<<endl;
		int Lstday=(x-(Day[now-1]-Day[i-1])),lst2=a[now]-Lstday+1;
//		cout<<lst<<' '<<lst2<<endl;
		if(lst2>=lst)
			ans=max(ans,a[i]+(s[now-1]-s[i])+cal(Lstday+(a[i]-1)));
		else
			ans=max(ans,cal(a[i])-cal(1+lst2-2)+(s[now-1]-s[i])+cal(a[now]));
	} 
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ZLCT (赞：0)

# CF1358D The Best Vacation
## 题目翻译
一年有 $n$ 月，第 $i$ 月有 $a_i$ 天，在每个月第 $j$ 天你会得到 $j$ 的得分，求连续 $x$ 天最多得分多少（注意年可以循环）。
## 破环为链
由于 $x\le\sum\limits_{i=1}^{n}a_i$，所以它选择的区间一定不超过 $n$ 个月。\
我们考虑对于最后一个月的情况，一定是满月。\
证明：\
假设我们不选满月，那么我们把最后的那个月都往前移到第一个月前。由于等差数列的性质，我们可以得出这样一定不会比原来差。\
这样我们就可以枚举最后一个月，利用前缀和和二分找出第一个月的位置，这样只需要 $O(n\log n)$ 的复杂度。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+666;
int n,x,a[N],sum[N],ans,pre[N];
signed main(){
    cin>>n>>x;
    for(int i=1;i<=n;++i){
        cin>>a[i];
        a[i+n]=a[i];
    }
    for(int i=1;i<=n*2;++i){
        sum[i]=sum[i-1]+a[i];
        pre[i]=pre[i-1]+(a[i])*(a[i]+1)/2ll;
    }
    for(int i=n+1;i<=n*2;++i){
        int l=lower_bound(sum+1,sum+1+2*n,sum[i]-x)-sum;
        int s=pre[i]-pre[l];
        int rst=x-sum[i]+sum[l];
        if(rst){
            s+=(a[l]+a[l]-rst+1)*rst/2ll;
        }
        ans=max(s,ans);
    }
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Zinc_acetate (赞：0)

在同一个月里面，月末肯定比月初大，所以优先取月末，~~易得~~ 所以肯定是取某几个月的全部加上一个月的末尾几天（当然是连续的啦）。

~~然后就是喜闻乐见的暴力出奇迹啦~~

```cpp
#include <bits/stdc++.h>
#define int long long   //十年oi一场空,不开longlong见祖宗
#define endl '\n'       //endl:习惯了
using namespace std;    //懒得打std::是这样的
int aa[200010];
vector<int> a;          //代码用了vector,不流失,不蒸发,零浪费!
signed main()
{
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; i++)
    {
        cin >> aa[i];
        a.push_back(aa[i]);
    }
    for (int i = 0; i < n; i++) //好像是说不必是一年的来着,那就再来一轮(
    {
        a.push_back(aa[i]);
    }
    int l = n * 2 - 1, r = n * 2 - 1;   //双指针劳模:l&r
    int ans = 0;
    int b = x;
    int k = 0;
    while (r >= n)  //因为r是从n*2-1开始的,所以只需要跑到n就可以了,再下去就重复了
    {
        while (b - a[l] >= 0)   //l左移,同时更新剩余天数与拥抱次数
        {
            k += (1 + a[l]) * a[l] / 2;
            b -= a[l];
            l--;
        }

        ans = max(b * (a[l] + a[l] - b + 1) / 2 + k, ans);  //更新ans

        k -= (1 + a[r]) * a[r] / 2; //r左移,同时更新剩余天数与拥抱次数
        b += a[r];
        r--;
    }
    cout << ans;    //愉快ac
    return 0;
}
```


---

## 作者：Tx_Lcy (赞：0)

[更差的阅读体验](https://www.cnblogs.com/tx-lcy/p/16822070.html)

[题目传送门](https://www.luogu.com.cn/problem/CF1358D)

## 思路

做这道题主要是需要发现一个性质：选择的区间必定是从某一个月的最后一天开始往前连续的一段区间。

考虑如何证明这个结论，设这个月有 $x$ 天，假设有更优的方案满足到下一个月的第 $y$ 天，则我们发现下一个月中的拥抱数为 $\sum_{i=1}^{y} i$，而显然任意一个长度为 $y$ 的区间的最小拥抱数就是这个值，我们往前移动一定不劣于这个解。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=1e6+10;
int a[N],sum[N],qsum[N];
inline int check(int l,int r){return qsum[r]-qsum[l-1];}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,x;cin>>n>>x;int ans=0;
    for (int i=1;i<=n;++i) cin>>a[i],qsum[i]=qsum[i-1]+a[i],sum[i]=sum[i-1]+(1+a[i])*a[i]/2;
    for (int i=1;i<=n;++i) a[i+n]=a[i];
    n<<=1;
    for (int i=1;i<=n;++i) qsum[i]=qsum[i-1]+a[i],sum[i]=sum[i-1]+(1+a[i])*a[i]/2;
    for (int i=(n/2);i<=n;++i){
        int l=1,r=i;
        while (l<r){
            if (l+1==r){if (check(r,i)<=x);else l=r;break;}
            int mid=(l+r)>>1;
            if (check(mid,i)<=x) r=mid-1;
            else l=mid;
        }
        ++l;
        int q=x-(qsum[i]-qsum[l-1]);
        int summ;
        if (l>i+1) summ=0;
        else summ=sum[i]-sum[l-1]+(a[l-1]+(a[l-1]-q+1))*q/2;
        ans=max(ans,summ);
    }
    cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：E1_de5truct0r (赞：0)

## 思路

一个比较显然的贪心。

题目说不一定在一年里，所以我们破环为链，将 $a$ 数组复制一遍，对 $1$ 至 $2n$ 进行求解。

最终的答案中，假设包含 $A$ 个整年和 $B$ 天，那么这 $B$ 天最优情况下一定是在某一年的末尾出现。所以我们考虑找到最大的 $A$ 个整年（加起来天数 $\leq k$）和这 $A$ 年前面一年的末尾，对答案进行统计。

那么这变成了双指针的板子题。一个显然的单调性满足，如果 $\sum\limits_{j=l}^{r} a_j \geq k$，那么 $\sum\limits_{j=l}^{r+1} a_j > k$。因此我们可以对于每个 $l$ 双指针出所有的 $r$。题目要求求最大，那么我们尽量把 $r$ 往大取，即跑到一个位置 $d$ 使得 $\sum\limits_{j=l}^{d} a_j \leq k$ 并且 $\sum\limits_{j=l}^{d+1} a_j>k$。

首先，对于整年的情况，我们可以用前缀和的思想，记 $p_i$ 为前缀和数组，那么用 $p_r-p_{l-1}$ 可以快速求出 $\sum\limits_{j=l}^{r}a_j$。

然后要求拥抱数量，我们根据小学数学的等差数列求和公式得到，每一个 $a_i$ 的拥抱数应该是 $\sum\limits_{j=1}^{a_i} j$，即 $\dfrac{(a_i+1) \cdot i}{i}$。那么我们依然把这个东西用 $S$ 数组进行一个前缀和，得到 $[l,r]$ 这些整年的拥抱总和为 $S_r-S_{l-1}$。而 $[l,r]$ 这些整年之外的额外天数有 $k-(p_r-p_{l-1}) = k-p_r+p_{l-1}$ 天，我们要求的就是第 $l-1$ 个月，从 $a_{l-1}$ 向下加 $k-p_r+p_{l-1}$ 天的拥抱数量之和。

我们记 $k-p_r+p_{l-1} = t$。则我们要求的就是 $\sum\limits_{j=a_i-t+1}^{t}j$。根据~~小学数学的等差数列求和公式，我们再一次十分成功的~~得到了它的值为 $\dfrac{[a_i+(a_i-t+1)][a_i-(a_i-t+1)+1]}{2} = \dfrac{(2a_i-t+1)t}{2}$。

于是把这个和之前的那个整年的和加起来，每次的答案就是：

$$S_r-S_{l-1}+\dfrac{(2a_i-t+1)t}{2}$$

总体取 $\max$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=200005;
ll a[MAXN<<1],S[MAXN<<1],pre[MAXN<<1];
int main()
{
	int n; ll k; scanf("%d%lld",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&a[i]);
		a[n+i]=a[i];
	}
	for(int i=1;i<=n*2;i++) S[i]=S[i-1]+(a[i]+1)*a[i]/2,pre[i]=pre[i-1]+a[i];
	int l=0,r=1; ll ans=0;
	while(r<2*n)
	{
		while(pre[r]-pre[l]>k && l<=r) l++;
		if(pre[r]>=k) //要加一个特判不然会算出超级巨大的奇怪的数。
		{
			ll tmp=k-pre[r]+pre[l];
			ans=max(ans,S[r]-S[l]+(2*a[l]-tmp+1)*tmp/2);
		}
		r++;
	}
	printf("%lld",ans);
	return 0;
}
```

---

