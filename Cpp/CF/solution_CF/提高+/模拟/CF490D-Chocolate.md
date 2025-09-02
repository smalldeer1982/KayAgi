# Chocolate

## 题目描述

Polycarpus likes giving presents to Paraskevi. He has bought two chocolate bars, each of them has the shape of a segmented rectangle. The first bar is $ a_{1}×b_{1} $ segments large and the second one is $ a_{2}×b_{2} $ segments large.

Polycarpus wants to give Paraskevi one of the bars at the lunch break and eat the other one himself. Besides, he wants to show that Polycarpus's mind and Paraskevi's beauty are equally matched, so the two bars must have the same number of squares.

To make the bars have the same number of squares, Polycarpus eats a little piece of chocolate each minute. Each minute he does the following:

- he either breaks one bar exactly in half (vertically or horizontally) and eats exactly a half of the bar,
- or he chips of exactly one third of a bar (vertically or horizontally) and eats exactly a third of the bar.

In the first case he is left with a half, of the bar and in the second case he is left with two thirds of the bar.

Both variants aren't always possible, and sometimes Polycarpus cannot chip off a half nor a third. For example, if the bar is $ 16×23 $ , then Polycarpus can chip off a half, but not a third. If the bar is $ 20×18 $ , then Polycarpus can chip off both a half and a third. If the bar is $ 5×7 $ , then Polycarpus cannot chip off a half nor a third.

What is the minimum number of minutes Polycarpus needs to make two bars consist of the same number of squares? Find not only the required minimum number of minutes, but also the possible sizes of the bars after the process.

## 样例 #1

### 输入

```
2 6
2 3
```

### 输出

```
1
1 6
2 3
```

## 样例 #2

### 输入

```
36 5
10 16
```

### 输出

```
3
16 5
5 16
```

## 样例 #3

### 输入

```
3 5
2 1
```

### 输出

```
-1
```

# 题解

## 作者：FFTotoro (赞：6)

看到楼上一堆大分讨，本人觉得完全没有必要。

本题可以使用一些数论的技巧。

记 $f(n,i)$（其中 $i\in\{2,3\}$）为正整数 $n$ 分解质因数的形式中包含 $i$ 的个数，那么需要满足最终条件，即为满足 $f(a,2)+f(b,2)=f(c,2)+f(d,2)$ 且 $f(a,3)+f(b,3)=f(c,3)+f(d,3)$。将此记为条件 $P$。

然后考虑每一轮操作，如果 $f(a,i)+f(b,i)>f(c,i)+f(d,i)$，那么，取 $a$ 和 $b$ 中分解质因数包含 $i$ 的一个（如果都包含就任取一个），不妨设为 $a$，然后 $a\leftarrow \frac{a(i-1)}{i}$；反之，类似地 $c$ 和 $d$ 也可以按上面的操作一步步完成。

最终，满足 $P$ 之后就可以判断，$ab$ 是否与 $cd$ 相等。如果相等就输出，不相等就判误解。可以证明，先处理 $i=3$，再处理 $i=2$，这种操作方式就不会有任何的冗余，所以它就是操作数最少的。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int f(int n,int i){
  return n%i?0:1+f(n/i,i);
}
int main(){
  int a,b,c,d,s=0; cin>>a>>b>>c>>d;
  for(int i=3;i>=2;i--)
    while(f(a,i)+f(b,i)-f(c,i)-f(d,i)&&++s){
      if(f(a,i)+f(b,i)>f(c,i)+f(d,i)){
        if(f(a,i))a=a/i*(i-1);
        else b=b/i*(i-1);
      }
      else{
        if(f(c,i))c=c/i*(i-1);
        else d=d/i*(i-1);
      }
    }
  if(1ll*a*b!=1ll*c*d)cout<<"-1\n";
  else cout<<s<<endl<<a<<' '<<b<<endl<<c<<' '<<d<<endl;
  return 0;
}

---

## 作者：Starrykiller (赞：5)

水题。注意到每个 $(a,b)$ 可以搜索到的状态最多只有 $\Theta(\log^2 V)$ 个，直接搜索即可，时间复杂度 $\Theta(\log^4 V)$（忽略数据结构）。

[代码](https://codeforces.com/contest/490/submission/272643792)。

---

## 作者：Light_Pursuer (赞：3)

**提供一种没有思考难度，没有码量的优质题解**

这种思路洛谷题解里我没找到。

还是首先考虑是否能够有解。
考虑对 $a \times b,c\times d$  进行 $2,3$ 的提取。提取剩下的数如果不相等的话那么一定无解，否则必有解。

接着思考一个问题：**切巧克力后面积发生的变化是相对的。这样对于 $s1$ 切剩下二分之一就相当于给 $s2$ 乘上二。同理，对于 $s1$ 切剩下三分之二就相当于给 $s2$ 乘上二分之三。**

这样的话就转变为给一个数进行若干次操作是否能变为另一个数的问题了。由于一共有四种操作，也就是 $\times 2,\times \dfrac12,\times \dfrac23,\dfrac32$，发现**其中只有 $\times \dfrac23$ 的操作能使得这个数 $3$ 的指数 $+1$。**

因此，考虑从 $3$ 的指数小的入手，对另一个数一直执行 $\times \dfrac23$ 的操作，直到两个数的 $3$ 的指数相同。最后看谁的 $2$ 的指数大再修改即可。

话说为什么题解区这么多搜索的？没看懂

代码参考
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int a, b, c, d;
int a2, a3, b2, b3;
int a21, a32, b21, b32;
signed main() {
	cin >> a >> b >> c >> d;
	int i, j, k, l;
	i = a, j = b, k = c, l = d;
	while (a % 2 == 0) {a /= 2; a2 ++;}
	while (b % 2 == 0) {b /= 2; a2 ++;}
	while (a % 3 == 0) {a /= 3; a3 ++;}
	while (b % 3 == 0) {b /= 3;	a3 ++;}
	while (c % 2 == 0) {c /= 2; b2 ++;}
	while (d % 2 == 0) {d /= 2; b2 ++;}
	while (c % 3 == 0) {c /= 3;	b3 ++;}
	while (d % 3 == 0) {d /= 3;	b3 ++;}
	if (a * b != c * d) {cout << -1; return 0;}
	while (a3 < b3) { b32++; b3--; b2++;}
	while (a3 > b3) { a32++; a3--; a2++;}
	while (a2 < b2) { b21++; b2--;}
	while (a2 > b2) { a21++; a2--;}
	cout << a21 + a32 + b21 + b32 << endl;
	while (a32) {
		if (i % 3 == 0) i = i / 3 * 2;
		else j = j / 3 * 2;
		a32--;
	}
	while (a21) {
		if (i % 2 == 0) i /= 2;
		else j = j / 2;
		a21--;
	}
	while (b32) {
		if (k % 3 == 0) k = k / 3 * 2;
		else l = l / 3 * 2;
		b32--;
	}
	while (b21) {
		if (k % 2 == 0) k /= 2;
		else l /= 2;
		b21--;
	}
	cout << i << ' ' << j << endl;
	cout << k << ' ' << l << endl;
	return 0;
}
```
完结！

---

## 作者：WorldMachine (赞：1)

搜索题。

发现一个巧克力的状态数不会很多，可以先搜索一次把第一块巧克力的所有状态存下来，第二次搜索找到面积相等的状态中步数最小的统计答案。

在 CF 上过的很轻松，因为搜索的复杂度只会与质因子 $2,3$ 的个数有关，操作 $2$ 只会使得一个 $3$ 变成一个 $2$，因此状态数为 $\mathcal O(\log^2 V)$ 的。因为存了个 map 所以复杂度多一个 $\log$。

代码写得很抽象，谨慎食用。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int a, b, c, d, ans = INT_MAX;
pair<int, int> x, y;
map<pair<int, int>, int> vis, vis1;
map<ll, int> mnt;
map<pair<ll, int>, pair<int, int> > qry;
void dfs1(int a, int b, int t) {
	if (vis.count({a, b}) && vis[{a, b}] <= t) return;
	vis[{a, b}] = t;
	if (mnt.count((ll)a * b)) mnt[(ll)a * b] = min(mnt[(ll)a * b], t);
	else mnt[(ll)a * b] = t;
	qry[{(ll)a * b, t}] = {a, b};
	if (!(a & 1)) dfs1(a >> 1, b, t + 1);
	if (!(b & 1)) dfs1(a, b >> 1, t + 1);
	if (!(a % 3)) dfs1(a / 3 * 2, b, t + 1);
	if (!(b % 3)) dfs1(a, b / 3 * 2, t + 1);
}
void dfs2(int a, int b, int t) {
	if (vis1.count({a, b}) && vis1[{a, b}] <= t) return;
	vis1[{a, b}] = t;
	if (mnt.count((ll)a * b)) {
		int tt = mnt[(ll)a * b];
		if (t + tt < ans) {
			ans = t + tt;
			y = {a, b}, x = qry[{(ll)a * b, tt}];
		}
	}
	if (!(a & 1)) dfs2(a >> 1, b, t + 1);
	if (!(b & 1)) dfs2(a, b >> 1, t + 1);
	if (!(a % 3)) dfs2(a / 3 * 2, b, t + 1);
	if (!(b % 3)) dfs2(a, b / 3 * 2, t + 1);
}
int main() {
	scanf("%d%d%d%d", &a, &b, &c, &d);
	dfs1(a, b, 0), dfs2(c, d, 0);
	if (ans == INT_MAX) return puts("-1"), 0;
	printf("%d\n%d %d\n%d %d", ans, x.first, x.second, y.first, y.second);
}
```

---

## 作者：FutaRimeWoawaSete (赞：1)

大分讨。              

考虑操作 $1$ 就是将一个数分解质因数后，$2$ 的个数 $+1$ ，$3$ 的个数 $-1$ ；         

操作 $2$ 就是将一个数分解质因数后，$2$ 的个数 $-1$ ；           

首先分解完质因数后看看除了 $2,3$ 的部分是不是一样的就可以判 $-1$ 了。         

接着我们考虑 $3$ 只能减少所以先把 $3$ 的个数都置为一样，然后 $2$ 现在也只能减少了，所以把 $2$ 的个数再置为一样就好了，大分讨有点难打。    

```cpp
#include "bits/stdc++.h"
using namespace std;
#define int long long
const int Len = 1e5 + 5;
long long a,b,x,y,mula,mulb;
int num[2][2];
long long qpow(long long a,long long b)
{
	long long res = 1;
	while(b)
	{
		res = res * a;
		b = b >> 1;
		a = a * a;
	}
	return res;
}
void Print(int numa,int numb,long long A,long long B)
{
	int twoA = 0,twoB = 0,threeA = 0,threeB = 0;long long usea = A , useb = B;
	while(usea % 3 == 0) usea = usea / 3 , threeA ++;
	while(useb % 3 == 0) useb = useb / 3 , threeB ++;
	while(numb && usea * 3 <= A && threeA){numb -- ; usea *= 3;threeA --;}
	while(numb && useb * 3 <= B && threeB){numb -- ; useb *= 3;threeB --;}
	while(usea % 2 == 0) usea = usea / 2 , twoA ++;
	while(useb % 2 == 0) useb = useb / 2 , twoB ++;
	int add = 0;
	while(numa && usea * 2 <= A && add < twoA + threeA){add ++;numa -- ; usea *= 2;}
	add = 0;
	while(numa && useb * 2 <= B && add < twoB + threeB){add ++;numa -- ; useb *= 2;}
	printf("%lld %lld\n",usea,useb);
}
signed main()
{
	scanf("%lld %lld %lld %lld",&a,&b,&x,&y);
	mula = a * b;mulb = x * y;long long pre,A,B;
	pre = mula;
	while(pre % 2 == 0) num[0][0] ++ , pre /= 2;
	pre = mula;
	while(pre % 3 == 0) num[0][1] ++ , pre /= 3;
	pre = mulb;
	while(pre % 2 == 0) num[1][0] ++ , pre /= 2;
	pre = mulb;
	while(pre % 3 == 0) num[1][1] ++ , pre /= 3;
	A = mula , B = mulb;
	while(A % 2 == 0) A = A >> 1;
	while(A % 3 == 0) A = A / 3;
	while(B % 2 == 0) B = B >> 1;
	while(B % 3 == 0) B = B / 3;
	if(A != B) 
	{
		puts("-1");
		return 0;
	}
	int ans = 0;
	if(num[0][1] > num[1][1]) 
	{
		num[0][0] += num[0][1] - num[1][1];
		ans += num[0][1] - num[1][1];
		num[0][1] = num[1][1];
		if(num[0][0] > num[1][0]) 
		{
			printf("%lld\n",ans + num[0][0] - num[1][0]);
			num[0][0] = num[1][0];
			Print(num[0][0] , num[0][1] , a , b);
			Print(num[1][0] , num[1][1] , x , y);
		}
		else 
		{
			printf("%lld\n",ans + num[1][0] - num[0][0]);
			num[1][0] = num[0][0];
			Print(num[0][0] , num[0][1] , a , b);
			Print(num[1][0] , num[1][1] , x , y);
		}
	}
	else
	{
		num[1][0] += num[1][1] - num[0][1];
		ans += num[1][1] - num[0][1];
		num[1][1] = num[0][1];
		if(num[0][0] > num[1][0]) 
		{
			printf("%lld\n",ans + num[0][0] - num[1][0]);
			num[0][0] = num[1][0];
			Print(num[0][0] , num[0][1] , a , b);
			Print(num[1][0] , num[1][1] , x , y);
		}
		else 
		{
			printf("%lld\n",ans + num[1][0] - num[0][0]);
			num[1][0] = num[0][0];
			Print(num[0][0] , num[0][1] , a , b);
			Print(num[1][0] , num[1][1] , x , y);
		}
	}
	return 0;
}
```

---

## 作者：E1_de5truct0r (赞：0)

数学题。

## 思路

首先考虑对 $a \times b$ 和 $c \times d$ 进行 $2$ 和 $3$ 的质因数分解。分解之后，如果 $a \times b$ 和 $c \times d$ 有独立的不属于 $2,3$ 的质因子，那么输出 `-1`。这个判断方法很简单，假设 $a \times b$ 有 $s_1$ 个 $2$ 和 $s_2$ 个 $3$，$c \times d$ 有 $s_3$ 个 $2$ 和 $s_4$ 个 $3$。我们只需要判断 $a \times b \times \dfrac{2^{s_3} \times 3^{s_4}}{2^{s_1} \times 3^{s_2}} = c \times d$ 是否成立即可。如果不成立说明无论如何也不能达到目标。

然后考虑如何进行操作。一个显然的贪心就是先考虑对 $3$ 进行处理，因为 $3$ 的最优处理方式是唯一的，并不会被 $2$ 影响，但是 $2$ 会被 $3$ 影响。具体方法就是看 $a \times b$ 和 $c \times d$ 哪一个 $3$ 数量多，就对它操作。在除以 $3$ 的同时，因为还乘了 $2$，所以相当于 $3$ 的数量减掉而 $2$ 的数量加上相应的数。

接下来考虑 $2$ 的情况。和 $3$ 同理，只不过这次只需要给 $2$ 减掉应该减的，不需要处理其他的。

这样我们就得到了 $a \times b$ 和 $c \times d$ 应该分别除以 $2^{d_1}$、$3^{d_2}$ 和 $2^{d_3}$、$3^{d_4}$。现在考虑怎么分配回去。显然，我们直接把能除掉的在 $a$ 和 $c$ 除掉，剩下的留给 $b$ 和 $d$ 处理即可，这样一定能够除完。主要就是注意 $a$ 和 $c$ 除以 $3$ 的时候还会乘以 $2$，这个时候相当于能够除 $2$ 的数量变多了，要记得加上。

## 代码

这道题思维难度也就 `*1400`，主要难度在代码上。（其实目测这道题远远没有 `*1900` 那么难）

```cpp
#include <bits/stdc++.h>
#define inl inline
#define cst const
#define reg register
#define lob lower_bound
#define uob upper_bound
#define sct struct
#define ll long long
const int MAXN=100005;
using namespace std;
inline ll gcd(const ll &a,const ll &b){return !b?a:gcd(b,a%b);} // 求 gcd(a,b)
inline ll ksm(ll a,ll b){ // 快速幂，求 a 的 b 次方
	ll base=a,ans=1;
	while(b){
		if(b&1) ans*=base;
		base*=base;
		b>>=1;
	}return ans;
}int main(){
	ll a,b,c,d; cin>>a>>b>>c>>d;
	ll P=a*b,Q=c*d,p=P,q=Q;
	int cnt1=0,cnt2=0,cnt3=0,cnt4=0;
	while(P && P%2==0) P/=2,cnt1++;
	while(P && P%3==0) P/=3,cnt2++;
	while(Q && Q%2==0) Q/=2,cnt3++;
	while(Q && Q%3==0) Q/=3,cnt4++;
	if(p/ksm(2,cnt1)/ksm(3,cnt2)*ksm(2,cnt3)*ksm(3,cnt4)!=q){ // 判断能不能乘回来
		cout<<-1;
		return 0;
	}int div1=0,div2=0,div3=0,div4=0;
	if(cnt2<cnt4){ // 先处理 3
		div4+=cnt4-cnt2;
		cnt3+=cnt4-cnt2;
	}else{
		div2+=cnt2-cnt4;
		cnt1+=cnt2-cnt4;
	}if(cnt1<cnt3){ // 再处理 2
		div3+=cnt3-cnt1;
	}else{
		div1+=cnt1-cnt3;
	}cout<<div1+div2+div3+div4<<endl;
//	cout<<div1<<" "<<div2<<" "<<div3<<" "<<div4<<endl;
	int x1,x2,x3,x4,x5,x6,x7,x8;
	ll aa=a,bb=b,cc=c,dd=d;
	x1=x2=x3=x4=x5=x6=x7=x8=0; // 算出来 a,b,c,d 各有多少个 2 和 3
	while(aa && aa%2==0) aa/=2,x1++;
	while(aa && aa%3==0) aa/=3,x2++;
	while(bb && bb%2==0) bb/=2,x3++;
	while(bb && bb%3==0) bb/=3,x4++;
	while(cc && cc%2==0) cc/=2,x5++;
	while(cc && cc%3==0) cc/=3,x6++;
	while(dd && dd%2==0) dd/=2,x7++;
	while(dd && dd%3==0) dd/=3,x8++;
	cout<<a/ksm(3,min(x2,div2))*ksm(2,min(x2,div2))/ksm(2,min(x1+min(x2,div2),div1))<<" "; // 先分配给 a
	div1=div1-min(x1+min(x2,div2),div1); // 对应的 2 和 3 的数量减掉
	div2=div2-min(x2,div2);
	cout<<b/ksm(3,min(x4,div2))*ksm(2,min(x4,div2))/ksm(2,min(x3+min(x4,div2),div1))<<endl; // 再分给 b
	
	cout<<c/ksm(3,min(x6,div4))*ksm(2,min(x6,div4))/ksm(2,min(x5+min(x6,div4),div3))<<" "; // 先分给 c
	div3=div3-min(x5+min(x6,div4),div3); // 对应的 2 和 3 的数量减掉
	div4=div4-min(x6,div4);
	cout<<d/ksm(3,min(x8,div4))*ksm(2,min(x8,div4))/ksm(2,min(x7+min(x8,div4),div3))<<" "; // 再分给 d
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

## 思路

一看感觉及其朴素，但是细节还是有的，算是个分讨，难怪是蓝。

容易发现题面的意思就是让 $a_1\times a_2$ 和 $b_1\times b_2$ 经过操作后相等。

可以先质因数分解，这个好处在于可以直接 $\sqrt{a_1}$ 计算并存入，剩余部分比一下和 $b$ 是否相等，不等直接 $-1$。

若存在 $>3$ 的质因子满足 $a,b$ 包含数量不同也可以直接输出 $-1$。

然后我们考虑操作，将 $a,b$ 中 $3$ 多的变成一样多，然后 $2$ 多的同样操作。

注意最后他要我们输出这两个，那么在我们操作 $3$ 的时候优先应该减去 $a_1,b_1$ 的 $3$ 并增加 $a_1,b_1$ 的 $2$，才能保证最后输出结果可达。

## 代码

~~不要在意无关变量，因为三目运算这个东西很玄学。~~

大致不解释了，挂了可以对比一下细节，写的思路不一定十分清晰。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mp make_pair
#define s(i,j) (i-1)*n+j
using namespace std;
int cnt1[100005],cnt2[100005],cnt3[100005],cnt4[100005],cjldakioi;
signed main(){
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	for(int i=2;i<=100000;i++){
		while(a%i==0){
			a/=i;
			cnt1[i]++;
			cnt3[i]++;
		}
	}
	for(int i=2;i<=100000;i++){
		while(b%i==0){
			b/=i;
			cnt1[i]++;
		}
	}
	for(int i=2;i<=100000;i++){
		while(c%i==0){
			c/=i;
			cnt2[i]++;
			cnt4[i]++;
		}
	}
	for(int i=2;i<=100000;i++){
		while(d%i==0){
			d/=i;
			cnt2[i]++;
		}
	}
	if(a*b!=c*d){
		cout<<-1;
		return 0;
	}
	int ok=1;
	for(int i=4;i<=100000;i++) if(cnt1[i]!=cnt2[i]) ok=0;
	if(!ok){
		cout<<-1;
		return 0;
	}
	int ans=0;
	while(cnt1[3]!=cnt2[3]){
		ans++;
		(cnt1[3]>cnt2[3])?(cnt1[3]--,cnt1[2]++,(cnt3[3]>0)?(cnt3[3]--,cnt3[2]++):(cjldakioi++)):(cnt2[3]--,cnt2[2]++,(cnt4[3]>0)?(cnt4[3]--,cnt4[2]++):(cjldakioi++));
	}
	while(cnt1[2]!=cnt2[2]){
		ans++;
		(cnt1[2]>cnt2[2])?(cnt1[2]--):(cnt2[2]--);
	}
	cout<<ans<<endl;
	int ansa=1;
	for(int i=2;i<=100000;i++){
		for(int j=1;j<=min(cnt1[i],cnt3[i]);j++) ansa*=i;
		cnt1[i]-=min(cnt1[i],cnt3[i]);
	}
	int ansb=1;
	for(int i=2;i<=100000;i++){
		for(int j=1;j<=cnt1[i];j++) ansb*=i;
	}
	int ansc=1;
	for(int i=2;i<=100000;i++){
		for(int j=1;j<=min(cnt2[i],cnt4[i]);j++) ansc*=i;
		cnt2[i]-=min(cnt2[i],cnt4[i]);
	}
	int ansd=1;
	for(int i=2;i<=100000;i++){
		for(int j=1;j<=cnt2[i];j++) ansd*=i;
	}
	cout<<ansa*a<<" "<<ansb*b<<endl;
	cout<<ansc*c<<" "<<ansd*d;
	return 0;
}
```

---

## 作者：Xdl_rp (赞：0)

solution
------------
- 求 $a1 \times b1$ 和 $a2 \times b2$ 的最大公约数 $d$。设 $x = a1 \times b1 \div d$，$y = a2 \times b2 \div d$。那么如果可以的话，$x$ 和 $y$ 中应该只剩下质因数 $2$ 和 $3$。

## 分类讨论

- $x = 3^t,y = 2^k$
- $x = 2^t,y = 3^k$
- $x = 1,y = 2^k$
- $x = 1,y = 3^k$
- $x = 2^t,y = 1$
- $x = 3^t,y = 1$

方法是：一步可以去掉一个 $2$ 或者去掉一个 $3$，加上一个 $2$。两步可以去掉一个 $3$，这样一直做下去，直到 $k = t$，就可以了。

---

