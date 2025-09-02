# Faculty

## 题目描述

在 2077 年，世界被机器人奴役后，机器人决定实施教育改革，现在取模运算仅在"古代世界历史"学院中教授。以下是该学院的入学任务之一：

我们定义一个正整数数组 $b$ 的美观度为所有 $1 \leq i, j \leq n$ 数对中 $f(b_i, b_j)$ 的最大值，其中 $f(x, y) = (x \bmod y) + (y \bmod x)$。

给定一个长度为 $n$ 的正整数数组 $a$，输出 $n$ 个数字，其中第 $i$ 个数字（$1 \leq i \leq n$）是数组 $a_1, a_2, \ldots, a_i$ 的美观度。

$x \bmod y$ 表示 $x$ 除以 $y$ 的余数。

## 说明/提示

数组 $3$ 的美观度为 $0$。

数组 $3, 1$ 的美观度为 $f(3, 1) = 1$。

数组 $3, 1, 4$ 的美观度为 $f(3, 4) = 4$。

数组 $3, 1, 4, 1$ 的美观度为 $f(4, 3) = 4$。

数组 $3, 1, 4, 1, 5$ 的美观度为 $f(4, 5) = 5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2
5
3 1 4 1 5
7
5 11 11 4 2 1 10```

### 输出

```
0 1 4 4 5 
0 6 6 7 7 7 11```

# 题解

## 作者：lw393 (赞：13)

这道题算是本场除 AB 外，代码最为简单的了，但是思维难度大。

我们先证明命题 $1$：$f(x,y) \le \max(x,y)$

证明：

若 $x = y$ 则 $f(x,y) = 0$。

否则设 $x \le y$。

此时 $x \bmod y = x, y \bmod x = y -\lfloor\frac yx\rfloor x$。

$f(x,y) = x + y - \lfloor\frac yx\rfloor x$。

由于 $\lfloor\frac yx\rfloor \ge 1$，命题得证。

再证明命题 $2$：长度为 $k$ 的前缀中最大的 $f(a_i,a_j)$，$a_i \ge a_j$，在 $a_i = \max_{j=1}^k a_j$ 中取得。

证明：

设 $a_i$ 为长度为 $k$ 的前缀中的最大元素，$f(a_x, a_y)$ 大于找到的值，$a_x \le x_y$，由前命题，得 $f(a_x, a_y)\le a_y$。

我们再考虑 $f(a_i, a_y)$，由于 $a_y \le a_i$，得 $f(a_x,a_y)\le a_y \le f(a_i,a_y)$。

最后证明命题三：若 $x < y < 2x$，则 $f(x,y) = y$

证明：

$f(x,y) = f(x,y) = x + y - \lfloor\frac yx\rfloor x$，由 $x < y < 2x$，知 $\lfloor\frac yx\rfloor = 1$，从而 $f(x,y) = y$。

借助上述三个命题得正确性，我们可以枚举了。设在长度为 $k$ 的前缀中，最大值为 $x$，最大的 $f(x,y)$ 为 $ans$。

我们用以下步骤更新 $ans$：

1. 若 $a_{k+1} <x$，利用命题 $2$，更新 $ans$；
2. 若 $x < a_{k+1} < 2x$，利用命题 $3$，更新 $ans$；
3. 若 $a_{k+1} \ge 2x$，直接暴力遍历数组。

由于每次在前缀最大值达到前一个最大值的两倍才会枚举数组内的所有元素，所以时间复杂度可以证明是 $O(n\log A)$，其中 $A = \max_{i=1}^n a_i$。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int f(int x, int y) { return x % y + y % x; }

void solve(){
  int n; cin >> n;
  vector<int>a(n + 1);
  for(int i = 1; i <= n; i++) cin >> a[i];
  int ans = 0, maxn = a[1];
  for(int i = 1; i <= n; i++){
    ans = max(ans, f(maxn, a[i]));
    if(a[i] > maxn){
      if(a[i] >= maxn * 2){
        maxn = a[i];
        for(int j = 1; j <= i; j++) ans = max(ans, f(a[i], a[j]));
      } else { maxn = a[i]; ans = maxn; }
    }
    cout << ans << ' ';
  }
  cout << '\n';
}

int main(){
  int t = 1;
  cin >> t;
  while(t--){
    solve();
  }
  return 0;
}
```

---

## 作者：qqqaaazzz_qwq (赞：4)

比赛结束前 $8$ 分钟会了，$3$ 分钟写完代码，结束前 $5$ 分钟过了（

先来挖掘一下这个 $f(x,y)$ 的性质。（假设 $x > y$）。

* $(x \bmod y) + (y \bmod x) = (x \bmod y) + y \geq y$
* $(x \bmod y) = x - \lfloor \dfrac{x}{y} \rfloor \times y$，由于 $x>y$，所以 $\lfloor \dfrac{x}{y} \rfloor \geq 1$，所以 $(x \bmod y) \leq x-y$。
* $(x \bmod y) + (y \bmod x) \leq x-y+y \leq x$

总结：$y \leq f(x,y) \leq x$。

设前缀最大值为 $x$，前缀**严格**次大值为 $y$，若不存在严格次大值，则前缀所有元素都相同，结论自然成立（答案为 $0$）。则我们可以证明答案 $\geq y$，因为 $f(x,y)\geq y$。如果我们不选 $x$，则结果必定 $\leq y$，是不优的。所以**前缀最大值必定被选上**（关键结论）。

然后这道题就基本做完了，下面是代码：

```cpp
#include <bits/stdc++.h>
#define FAST ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
int a[1000010];
int n;

int f(int x,int y){
	return x%y+y%x;
}

void solve(){
	cin >> n;
	for (int i=1;i<=n;i++) cin >> a[i];
	int mx = 0,ans = 0;
	for (int i=1;i<=n;i++){
		if(a[i]>=mx*2){
			mx = a[i];//暴力更新，做多发生 log V 次
			ans = 0;
			for (int j=1;j<=i;j++) ans = max(ans,f(a[i],a[j]));
		}
		else if(a[i]>mx){
			ans = a[i];//f(a[i],mx) = mx + a[i] - mx
			mx = a[i];
		}
		else ans = max(ans,f(a[i],mx));
		cout << ans << " ";
	}
	cout << "\n";
}

signed main()
{
	int t;
	cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：EricWan (赞：4)

随机区分的 trash round，但是来水题解

首先，重复的元素不考虑。

然后，观察 $f$，假设 $x\le y$ 得到 $f(x,y)=x+y\bmod x\in[x,y]$。

下面证明一下这个命题：取得答案的 $y$ 一定可以是 $\max\limits_{j=1}^ia_j$。

如果不可以是，那么 $f(x,y)\le f(y,\max\limits_{j=1}^ia_j)$，证明完了。

然后我们还可以发现答案理论最大值是 $\max\limits_{j=1}^ia_j$，这也是比较显然的。

考虑如何维护。

+ 遇到存在过的元素或者 $i=1$ 自然是要直接跳过的；
+ 如果 $a_i<\max\limits_{j=1}^{i-1}a_j$，说明 $a_i$ 只能被作为那个 $x$，然而上面的那个 $y$ 还是 $\max\limits_{j=1}^{i-1}a_j$ 不变，我们看一看能否更新答案即可；
+ 如果 $\max\limits_{j=1}^{i-1}a_j<a_i<2\times\max\limits_{j=1}^{i-1}a_j$，说明 $a_i$ 是新的 $y$，然后我们发现 $f(\max\limits_{j=1}^{i-1}a_j,a_i)=a_i$ 就是理论最大的答案，把答案进行更新即可。
+ 如果 $a_i\ge2\times\max\limits_{j=1}^{i-1}a_j$，说明我们不好计算答案，我们发现这样的情况最多只有 $1+\log_2\max a$ 次，我们遇到这种情况，将答案更新为 $\max\limits_{j=1}^{i-1}f(a_j,a_i)$ 即可。

代码大概是好懂好写的。

```cpp
int n, a[1000005], ans, maxa;
signed main() {
	ios::sync_with_stdio(0); // 我不会告诉你不开这两句话会 TLE on 4
	cin.tie(0);
	cout.tie(0);
	multiple_cases(T) {
		cin >> n;
		set<int> st; // 去重用
		ans = maxa = 0;
		#define OVER st.insert(a[i]);			\
					 cout << ans << " ";		\
					 maxa = max(maxa, a[i]);	\
					 continue // 因为需要用两次，偷懒写为宏
		#define f(a, b) ((a) % (b) + (b) % (a)) // 朴素计算 f
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			if (st.count(a[i]) || i == 1) { // 对应上文说的小分讨
				OVER;
			} else if (a[i] < maxa) {
				ans = max(ans, f(a[i], maxa));
			} else if (a[i] < maxa * 2) {
				ans = a[i];
			} else {
				ans = 0;
				for (int j = 1; j < i; j++) {
					ans = max(ans, f(a[i], a[j]));
				}
			}
			OVER;
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：NoirCube1 (赞：3)

## Preface

这是 Div. 2，不是 Div. 3？？

看到 rk1 八分钟秒了就感觉不对劲。

> \*1400 / 数学 / 暴力

## Solution

不妨记答案序列为 $\{b\}$。

我们对 $f(x,y)$ 进行一个大致的感知：

- **Observation 1**：不妨使 $x\le y$，函数取值一定落在 $[x,y]$ 之间。特别的，$y<2x$ 的时候我们可以取到上界。

下界显然，同时 $f(x,y)=x+y\bmod x \leq x+y-x=y$，于是上界显然。

由这个性质回到原问题。发现：

- **Observation 2**：$b_i\not= b_{i-1}$ 有个必要条件：**$\bm {a_i}$ 是前缀最大值**。

显然可以证明。因为对于 $b_{i-1}$ 一定不超过 $a_1,a_2,a_3,\dots.a_{i-1}$ 前缀最大值 $a_p$，然后 $a_i\ge a_p$，所以构造 $f(a_i,a_p)$ 就一定会产生一个大于 $b_{i-1}$ 的结果。

**请注意**：我们构造的 $f(a_i,a_p)$ 不一定是最大值，可能存在更大值，但显然必须使用 $a_i$。

但是 $a_i\leq 2a_p$ 的时候还有救，因为我们无需枚举 $b_i$ 直接就是 $a_i$。

于是就做完了。因为 $a_i> 2a_p$ 这件事情最多发生 $\log V$ 次（其中 $V$ 是值域），于是我们最多只会暴力枚举 $\log V$ 次，我们就在 $\mathcal O(n\log V)$ 时间解决该问题。

---

## 作者：ShanQing (赞：1)

CF 的套路是这样的，对于这种常规手段很难搞的题直接找性质，然后就变成了纸老虎。为啥我不在的场都是上分场。

写在前面，整道题其实就在围绕一个看似显然的关键结论，**对于任意的 $x,y$ 满足 $x<y$，我们有 $x\le f(x,y)\le y$，且 $f(x,y)=y$ 当且仅当 $2x>y$。**

我们考虑当前要插入 $a_i$，此时 $a_1$ 至 $a_{i-1}$ 的最大值为 $mx$，严格次大值（代码中无需实现，仅用于下文证明）为 $mx'$，当前答案为 $ans$。

首先如果 $a_i=mx$ 那么等于不存在，下文默认 $a_i\ne mx$。

当 $a_i>2mx$ 时，此时用不了“关键结论”，所以直接暴力枚举 $1$ 至 $i-1$ 更新答案。

否则，当 $2a_i>mx$ 且 $a_i\le 2mx$ 时，直接将 $ans$ 修改为 $\max(mx,a_i)$。这是因为根据结论，加入 $a_i$ 后 $\max(mx,a_i)$ 已经是整个序列可能达到的最大值，而又由结论可得 $f(mx,a_i)=\max(mx,a_i)$，不能再大了。

最后，如果 $2a_i\le mx$，那么我们令 $ans=\max(ans,f(a_i,mx))$。证明也很简单，考虑分讨：

（1）如果 $a_i\le mx'$，那么对于任意的 $v\le mx'$，我们有 $f(a_i,v)\le \max(a_i,v)\le mx' \le f(mx',mx)$。也就是说和任何一个不大于次大值的数计算出的 $f$ 值都不会超过原来的答案，那么只有 $f(a_i,mx)$ 存在大于原 $ans$ 的可能。

（2）如果 $a_i> mx'$，我们有 $f(a_i,v)\le a_i\le f(a_i,mx)$。这里 $f(a_i,mx)$ 直接地叉掉了所有的 $f(a_i,v)$，那么只要以它更新 $ans$ 即可。

综上，$2a_i\le mx$ 时只需要 $ans=\max(ans,f(a_i,mx))$。

最后别忘了更新 $mx=\max(mx,a_i)$。从这一步可以看出 $a_i>2mx$ 即暴力枚举更新最多只会存在 $\log V$ 次，所以总复杂度 $O(n \log V)$，可以接受。

## code


```cpp
#include <bits/stdc++.h>
//taskkill /f /im 未命名1.exe
#define ED cerr<<endl;
#define TS cerr<<"I AK IOI"<<endl;
#define cr(x) cerr<<x<<endl;
#define cr2(x,y) cerr<<x<<" "<<y<<endl;
#define cr3(x,y,z) cerr<<x<<" "<<y<<" "<<z<<endl;
#define cr4(x,y,z,w) cerr<<x<<" "<<y<<" "<<z<<" "<<w<<endl;
#define popcnt __builtin_popcount
#define all(s) s.begin(),s.end()
#define bstring basic_string
//#define add(x,y) (x+=y)%=mod
#define pii pair<int,int>
#define epb emplace_back
#define pb push_back
#define mk make_pair
#define ins insert
#define fi first
#define se second
#define ll long long
//#define ull unsigned long long
using namespace std;
const int N=1e6+5,INF=2e9,mod=1e9+7;
int t,n,m;
int a[N]; 

#define f(x,y) (x%y+y%x)

void sol() {
	scanf("%d",&n);int mx=0,mx2=0,ans=0;
	for(int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		if(a[i]>=mx+mx) {
			for(int j=1;j<i;++j) {
				ans=max(ans,f(a[j],a[i]));
			}
		}
		else if(a[i]+a[i]>mx&&a[i]!=mx) {
			ans=max(mx,a[i]);
		}
		else ans=max(ans,f(a[i],mx));
		mx=max(mx,a[i]);
		printf("%d ",ans);
	}
	puts("");
}

int main()
{
	scanf("%d",&t);
	while(t--) {
		sol();
	}
	return 0;
}
```

---

## 作者：jiazhichen844 (赞：1)

抽象题。

首先意识到 $f(x,y)=\max(x,y)\bmod\min(x,y)+\min(x,y)\le 2\min(x,y)$，且 $\min(x,y)\le f(x,y)$。  
还有 $f(x,y)=\max(x,y)\bmod\min(x,y)\le (\max(x,y)-\min(x,y))+\min(x,y)=\max(x,y)$。  
所以有 $\min(x,y)\le f(x,y)\le \min(\max(x,y),2\min(x,y))$。  
然后考虑长为 $i-1$ 的前缀的答案和长为 $i$ 的答案的区别。  
发现答案要对 $f(a_j,a_i)(j\le i)$ 取 $\max$。  
难以直接维护。  
分析性质。

先考虑 $a_i\le a_j$ 时的情况。  
若 $\exist 1\le x\le y< i,2a_i\le \min(a_x,a_y)$，则若 $a_i\le a_j,f(a_i,a_j)\le 2a_i\le \min(a_x,a_y)\le f(a_x,a_y)$，则这一部分一定没有贡献。  
所以若有贡献则前 $i-1$ 个数的次大值 $< 2a_i$。  
若 $a_i\le a_j<2a_i$，则 $f(a_i,a_j)=(a_j-a_i)+a_i=a_j$。  
此时只需求出最大的 $a_j$ 满足 $a_i\le a_j<2a_i$ 并更新即可。  
同时若存在一个 $a_j\ge 2a_i$，则也需要计算贡献。  
其实可以直接写成找到最大值和次大值并分别和 $a_i$ 计算贡献。  

然后是 $a_i>a_j$ 时的情况。  
若存在 $a_x\ge a_i(x<i)$，则 $f(a_i,a_j)\le a_i\le f(a_i,a_x)$，所以若这种情况有贡献，则 $a_i$ 是前缀最大值。  
若 $\exist x<i,\frac{a_i}{2}<a_x<a_i$，则 $f(a_x,a_i)=(a_i-a_x)+a_x=a_i$，且若 $a_y<a_i,f(a_y,a_i)\le a_i$，则若怎在这样的 $x$，其贡献是此种情况最大的。  
所以唯一问题是 $2\max(a_1,a_2,\cdots,a_{i-1})\le a_i$ 的情况，此时我们只会暴力，通过 $O(n)$ 的复杂度更新。  
令 $b_i=\max(a_1,a_2,\cdots,a_i)$，则若我们需要 $O(n)$ 复杂度暴力更新时，$b_i\ge2b_{i-1}$，但我们有 $b_n\le V$，则复杂度为 $O(n\log V)$。  
前面几种情况需要支持插入，lower_bound，使用 set 维护。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
int ans[1000005],a[1000005];
void test()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	set<int> st;
	for(int i=1;i<=n;i++)
	{
		ans[i]=ans[i-1];
		int x;
		if(!st.empty())
		{
			x=*st.rbegin();
			if(x>a[i])
				ans[i]=max(x%a[i]+a[i],ans[i]);
		}
		set<int>::iterator it=st.lower_bound(a[i]*2);
		if(it!=st.begin())
		{
			it--;
			x=*it;
			if(x>a[i])
				ans[i]=max(x%a[i]+a[i],ans[i]);
		}
		if(!st.empty())
			x=*st.rbegin();
		else
			x=0;
		if(a[i]>x)
		{
			if(x>a[i]/2)
				ans[i]=max(ans[i],a[i]);
			else
				for(int x:st)
					ans[i]=max(ans[i],a[i]%x+x%a[i]);
		}
		st.insert(a[i]);
	} 
	for(int i=1;i<=n;i++)
		cout<<ans[i]<<" ";
	cout<<"\n";
}
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	for(int i=1;i<=t;i++)
		test();
}
```

---

