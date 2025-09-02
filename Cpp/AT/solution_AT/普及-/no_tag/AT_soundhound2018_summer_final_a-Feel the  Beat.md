# Feel the  Beat

## 题目描述

[problemUrl]: https://atcoder.jp/contests/soundhound2018-summer-final/tasks/soundhound2018_summer_final_a

BPM (Beat Per Minute) とは、楽曲の速さを表す数値です。

Kenkoooo さんは、BPM が $ 140 $ 以上 $ 170 $ 未満の中速曲が好きです。 また、BPM を何回か $ 2 $ で割ると $ 140 $ 以上 $ 170 $ 未満となる曲も好きです。 このどちらにも当てはまらない曲は好きではありません。

例えば、Kenkoooo さんは BPM が $ 679 $ ($ 2 $ で $ 2 $ 回割ると $ 169.75 $) の曲は好きですが、 BPM が $ 680 $ ($ 2 $ で $ 2 $ 回割ると $ 170 $) の曲は好きではありません。

ここに $ 1 $ 枚の CD があり、$ D\ -\ C $ 曲の楽曲が収録されています。 これらの曲の BPM はそれぞれ $ C,\ C+1,\ C+2,\ ...,\ D-2,\ D-1 $ です。 このうち、Kenkoooo さんが好きな曲は何曲あるでしょうか？

## 说明/提示

### 制約

- $ 140\ <\ =\ C\ <\ D\ <\ =\ 10^{15} $
- $ C,\ D $ は整数である。

### Sample Explanation 1

この例では、CD には BPM $ 160,\ 161,\ 162,\ ...,\ 298,\ 299 $ の $ 140 $ 曲が収録されています。 このうち、Kenkoooo さんが好きな曲は BPM $ 160,\ 161,\ 162,\ ...,\ 168,\ 169 $ の $ 10 $ 曲と BPM $ 280,\ 281,\ 282,\ ...,\ 298,\ 299 $ の $ 20 $ 曲、合計 $ 30 $ 曲です。

### Sample Explanation 2

Kenkoooo さんの好みに合わないアルバムです。

### Sample Explanation 3

Kenkoooo さんの世界の CD の容量に上限はなく、収録曲数が $ 32 $ bit 整数型に収まらないこともあります。

## 样例 #1

### 输入

```
160 300```

### 输出

```
30```

## 样例 #2

### 输入

```
340 560```

### 输出

```
0```

## 样例 #3

### 输入

```
140 1000000000000000```

### 输出

```
263882790666210```

# 题解

## 作者：York佑佑 (赞：1)

## 题意

求出在 $c$ 到 $d$ 的数 $i$ 中有多少 $i$ 满足 $i$ 除以 $2$ 若干次之后范围在大于 $l$ 且小于 $r$。题目中给出 $l$ 为 $140$，$r$ 为 $170$。

## 分析

既然题目要求的是有多少 $i$ 满足 $i$ 除以 $2$ 若干次之后范围在大于 $l$ 且小于 $r$，那么我们就将 $l$ 和 $r$ 每次乘以 $2$，并增加在 $[l,r]$ 间的 $i$ 的个数，直到 $r$ 大于 $d$ 为止。**$r$ 大于 $d$ 时还要再做一遍，因为此时 $l$ 还可能小于等于 $d$。**

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int c, d, l = 140, r = 170, ans;
signed main()
{
	cin >> c >> d;
	while (r <= d)
	{
		ans += max(min(r, d) - max(c, l), 0ll);//增加在[l,r]间i的个数
		r *= 2, l *= 2;
	}
	ans += max(min(r, d) - max(c, l), 0ll);//再做一遍
	cout << ans << endl;
}
```


---

## 作者：danb123 (赞：0)

## 题目大意
给定一个区间范围，求这个区间内有多少个数除以若干次二以后在 $140$ 到 $170$ 之间。
## 题目分析
明显的一道数学题目，我们在思考的时候可以倒过来想，如果暴力是肯定没有分的。我们不能只想让这个数除以二来判断，而是想 $140$ 到 $170$ 范围之间的数的不断乘二，这样就把时间复杂度缩小到对数级。
## 完整代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,m,ans,x=140,y=170;
int main() {
	cin >>n>>m;
	while(x<m)ans+=max(0ll,min(m,y)-max(n,x)),x*=2,y*=2;
	cout<<ans;
	return 0 ;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_soundhound2018_summer_final_a)

## 思路

由于 $1\le C<D\le 10^{15}$，暴力枚举肯定行不通，所以我们考虑倒推。

让 $L$ 和 $R$ 分别从 $140$ 和 $170$ 开始直到 $R>D$ 为止。每次让结果增加区间 $[C,D]$ 和区间 $[L,R]$ 的**交集大小**即可。每次循环让 $L$ 和 $R$ 都增大一倍，实现倒推 $\div 2$ 的效果。记得 $R>D$ 时 $L$ 可能依旧小于 $D$，所以最后要再判断一遍。

- 上述交集的左端点是 $\max(L,C)$，右端点是 $\min(R,D)$，则交集大小是 $\min(R,D)-\max(L,C)$。当没有交集的时候记得**增加的值为 $0$ 而非负数**。

## 部分代码

```cpp
long long a,b,ans;
signed solution(){
	cin>>a>>b;
	long long l=140,r=170;
	while(r<=b){
		ans+=max(min(r,b)-max(l,a),0ll);
		l<<=1;
		r<<=1;
	}
	cout<<ans+max(min(r,b)-max(l,a),0ll);
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/157562164)

---

## 作者：lihongqian__int128 (赞：0)

# 题解：AT_soundhound2018_summer_final_a Feel the  Beat
首先，考虑暴力，发现会超时。

考虑这样一件事，若区间 $[L,R]$ 内的元素经过若干次除 $2$ 操作后全都在 $[140,170]$ 的范围内，则区间 $[L\times 2,R\times 2]$ 内的元素也都可以经过若干次除 $2$ 操作后全都在 $[140,170]$ 的范围内。

初始范围是 $[140,170]$。

时间复杂度：$O(\log D)$。

代码：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std ;
int c , d , ans , i , j ;
signed main()
{
    cin >> c >> d ;
    i = 140 , j = 170 ;
    while(i < d)
    {
        ans += max(0ll , min(d , j) - max(c , i)) ;
        i <<= 1 , j <<= 1 ;
    }
    cout << ans ;
    return 0 ;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/AT_soundhound2018_summer_final_a)

## 思路

- 由于本题 $ 140 \leq C < D \leq 10^{15}$，因此如果我们用暴力肯定是会超时的。

- 所以我们需要换一种思路，我们可以用题目要求的范围，即从 $140$ 到 $170$，将这个范围不断地乘 $2$，看有多少数在区间内，最终输出答案即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
    ll L, R;
    cin >> L >> R;
    ll l = 140, r = 170;//题目中规定的范围。
    ll ans = 0;
    while(l <= R){
        ans += max(min(R, r) - max(L, l), 1LL * 0);//增加个数。
        l *= 2; r *= 2;//逆推，
    }
    cout << ans << endl;
}
```

---

## 作者：huangjunhan (赞：0)

# 题目大意
本题是让我们求在 $C$ 到 $D$ 的区间内有多少个数是由若干个 $2$ 和一个在 $140 - 170$ 之间的数相乘而成。
## 分析
首先想到枚举 $C$ 到 $D$ 之间的所有数。再每次除以 $2$。判断得数是否在 $140$ 到 $170$ 之间。

但是题目数据有 $10^{15}$，枚举会超时。

于是，我们要换位思考：先设定一个区间，每次将区间乘以 $2$，判断 $C$ 和 $D$ 是否在区间之内，如果是，就累加。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,x=140,y=170,sum;
int main(){
    cin>>n>>m;
    while (x<=m){
	if (min(y,m)>=max(x,n)sum+=min(y,m)-max(x,n);
	x*=2,y*=2;
    }
    cout<<sum;
}
```

---

## 作者：zhouzihang1 (赞：0)

# Feel the Beat 题解

[洛谷传送门](https://www.luogu.com.cn/problem/AT_soundhound2018_summer_final_a)

[AT 传送门](https://atcoder.jp/contests/soundhound2018-summer-final/tasks/soundhound2018_summer_final_a)

[文章区链接](https://www.luogu.com.cn/article/ahjddb8f/edit)

## 做法

显然对于 $140 \le C < D \le 10^{15}$ 的数据，枚举无法通过。

我们可以换个方式，或许**找**满足条件的数不如**生成**满足条件的数。

所以可以定义两个变量分别为 $L = 140, R = 170$，并一直循环，每次循环计算在 $L,R$ 区间内，同时也在 $C,D$ 区间内的数的个数，并让 $L,R$ 每次乘 $2$。

---

## 作者：chl090410 (赞：0)

## The Solution to AT_soundhound2018_summer_final_a Feel the Beat

### Description

求出在 $C$ 到 $D$ 的数 $i(C≤i≤D)$ 中有多少 $i$ 满足 $i$ 除以 $2$ 若干次之后范围在大于 $140$ 且小于 $170$。

### Solution

由于 $140\le C<D\le10^{15}$，所以遍历 $C$ 与 $D$ 间的数是会超时的。所以我们转而枚举满足除以 $2$ 若干次之后在大于 $140$ 且小于 $170$ 的数，看有多少数在区间内即可。这样就能把时间复杂度降到 $O(\log D)$。

### Accode 如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int l,r,ans,ll=140,rr=170;
signed main(){
 	cin>>l>>r;
 	while(ll<r){
    	     ans+=max(min(r,rr)-max(l,ll),0ll);
    	     ll*=2;rr*=2;
	}
	cout<<ans;
	return 0;
}

---

## 作者：jhdrgfj (赞：0)

## 解法

我们可以通过暴力枚举每个符合要求的数区间的端点进行求解。

我们设左端点为 $l$，右端点为 $r$。则在每一次端点变化中，我们需要统计给定的 $A$ 与 $B$ 有多少数处在该区间内。

然后再考虑将左右端点如何变化。由于每个数每次变换应该 $\div 2$，所以可推出每次变化应该将左右端点同时 $\times 2$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,c=140,d=170,ans;
//读入的两个数，左端点，右端点，答案数。
int main()
{
	cin>>a>>b;
	while (c<=b){    //只要左端点比输入的 b 要大，就不可能还有数处在区间里
		ans+=max(min(d,b)-max(a,c),0ll);
      //统计有多少数处在答案区间里
		d*=2,c*=2;
     //扩大左右端点
	}
	cout<<ans<<endl;
}
```


---

