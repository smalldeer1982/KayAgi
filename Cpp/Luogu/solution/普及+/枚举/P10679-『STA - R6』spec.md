# 『STA - R6』spec

## 题目描述

  定义一个实数 $\alpha$ 的谱 $\operatorname{Spec}(\alpha)$ 是整数组成的一个无限长的序列 $\lceil\alpha\rceil-1,\lceil2\alpha\rceil-1,\lceil3\alpha\rceil-1,\cdots$。例如，$\frac35$ 的谱的开头部分是 $0,1,1,2,2,3,4,\cdots$。

现在给定 $n$ 个整数 $x_1,\cdots,x_n$，你要找到最大的实数 $\alpha$，使得对于每个元素 $x_i$ 都有 $x_i$ 在 $\operatorname{Spec}(\alpha)$ 中出现过。


## 说明/提示

**本题采用捆绑测试。**

数据范围：
- Subtask 0 (10pts)：$n,x_i\le 100$。
- Subtask 1 (15pts)：合法答案构成一段连续区间。
- Subtask 2 (25pts)：每个 $x_i$ 都是 2 的非负整数次幂。
- Subtask 3 (50pts)：无特殊限制。

对于全部数据，$1\le n,x_i\le 1000$。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
1.3333333```

## 样例 #2

### 输入

```
3
2 4 7```

### 输出

```
2.5000000```

# 题解

## 作者：Kotobuki_Tsumugi (赞：21)

我们充分发挥人类智慧。猜测答案接近但不大于序列中的最小元素。

因此我们可以从最小元素开始，从大到小枚举答案。

这样速度快的飞起，最大的点都可以在 30ms 内完成。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e3+10;
const double eps = 6e-6;
int n,x[N];
int main(){
	scanf("%d",&n);
	for(int i = 1;i<=n;i++)
		scanf("%d",&x[i]),x[i]++;
	sort(x+1,x+n+1);
	for(double ans = x[1]+1;ans >= eps;ans -= eps){
		bool flag = true;
		for(int j = 1;j<=n;j++){
			int now = x[j]/ans;
			if(ans*now <= x[j]-1){
				flag = false;
				break;
			}
		}
		if(flag){
			printf("%.7lf\n",ans);
			return 0;
		}
	}
	return 0;
}
```
[record](https://www.luogu.com.cn/record/163547465)。总用时仅 52ms。

---

## 作者：jijidawang (赞：14)

对于每个 $x_i$ 来说，满足 $x_i\in\operatorname{Spec}(\alpha)$ 的 $\alpha$ 可以构成 $x_i$ 个不交区间之并，只需要找一个最大的位置使得上面恰好覆盖 $n$ 个区间。

考虑把所有区间的端点放到一起排序，每到达一个左端点计数器加一，每到达一个右端点计数器减一，计数器等于 $n$ 的时候统计答案即可。

时间复杂度 $O(nv\log nv)$ 其中 $v$ 是值域。

如果有人对更优的算法有想法欢迎与我交流。

---

## 作者：Laisira (赞：11)

### 题面
定义一个实数 $\alpha$ 的谱 $\operatorname{Spec}(\alpha)$ 是整数组成的一个无限长的序列 $\lceil\alpha\rceil-1,\lceil2\alpha\rceil-1,\lceil3\alpha\rceil-1,\cdots$。例如，$\frac35$ 的谱的开头部分是 $0,1,1,2,2,3,4,\cdots$。

现在给定 $n$ 个整数 $x_1,\cdots,x_n$，你要找到最大的实数 $\alpha$，使得对于每个元素 $x_i$ 都有 $x_i$ 在 $\operatorname{Spec}(\alpha)$ 中出现过。

### 思路
这题暴力啊！

我们设 $u$ 使得 $\alpha \times u-1\leq x_{Max}$。我们暴力枚举 $\alpha$ 的范围只是 $(0,(x_{Max}-1)/u]$，每次要枚举 $\max(u,n)$ 次，时间复杂度是 $x_{Max}-1$，也就是差不多 $10^3$。再算上精确到 $10^5$，即 $\alpha$ 总共最坏时间复杂度是 $10^9$。

这时我们发现我们并不知道 $(0,(x_{Max}-1)/u]$ 是啥，但我们可以估计到一点，即 $u>m$，$m$ 指种数。我们至少枚出 $m$ 种数，于是稳过。

（话说赛后我给一个同学讲我的解法，Ta 说 Ta 气炸了。）

update：发现可以小小的优化。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10000];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    sort(a+1,a+1+n);
    n=unique(a+1,a+1+n)-a-1;
    double opt=double(a[n]+1)/n;
    for(;opt>=0;opt-=0.00000100) {
        int r=1,l=1;
        while((int)(ceil(opt*r*1.0000000)-1)<=a[l]&&l<=n) {
            if((int)(ceil(opt*r*1.0000000)-1)==a[l])l++;
            r++;
        } if(l>n) {
            printf("%.7f",opt);
            return 0;
        }
    }
    return 0;
}
```

---

## 作者：zxh923 (赞：5)

# P10679 『STA - R6』spec 题解

[题目传送门](https://www.luogu.com.cn/problem/P10679)

### 思路

首先我们发现这个减 $1$ 非常不优美，所以我们把所有的 $x$ 加上 $1$。

接着发现重复的 $x$ 没有什么用，所以我们排序并去重。

这里需要注意到答案一定不小于 $1$，因为答案为 $1$ 可以覆盖所有的数。

接下来，我们假设每个数都是答案 $ans$ 的 $k_i$ 倍上取整，于是我们枚举 $ans\times k_1=x_1$ 的 $k_1$，根据上面的结论发现 $k_1$ 不大于 $x_1$。

然后我们对每个 $x_i$ 进行判断，看 $ans$ 的 $k_i$ 倍上取整能不能覆盖到它，如果不能，直接跳出。

当我们发现一个合法的答案时，它一定是最大的，因为我们的枚举顺序是从大到小的。

而且因为我们枚举了 $k_1$，所以再去重后的数组中枚举 $k_2$ 可以从 $k_1+1$ 开始枚举，这样可以少很多无用枚举。

### 代码

```cpp
#include<bits/stdc++.h>
#define N 1005
#define eps 2e-6
using namespace std;
int n,a[N];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a[i];
		a[i]++;
	}
	sort(a,a+n);
	n=unique(a,a+n)-a;//排序并去重
	double res=0;
	for(int i=1;i<a[0];i++){//枚举倍数
		double l=a[0]*1.0/i,r=a[0]*1.0/(i+1);
		for(double j=l;j>r;j-=eps){
			bool flag=1;
			int cnt=i;
			for(int k=0;k<n;k++){
				while(ceil(j*cnt)<a[k])cnt++;//如果仍然小于，就+1
				if(ceil(j*cnt)>a[k]){//cnt-1一定小于，而cnt又大于，所以覆盖不到它1，答案不合法
					flag=0;
					break;
				}
			}
			if(flag){
				res=j;//找到答案
				break;
			}
		}
		if(res)break;
	}
	cout<<setiosflags(ios::fixed)<<setprecision(6);
	cout<<res;
	return 0;
}
```

---

## 作者：Dream__Sky (赞：5)

提供一个正常的方法。


------------

对于每一个 $x_i$，我们先求出需要其在谱中出现时，答案 $a$ 可能的范围区间(已从大到小排序)：

- 当 $x_i=1$，$1<a\leq2,\dfrac{1}{2}<a\leq 1,\dfrac{1}{3}<a\leq\dfrac{2}{3} \cdots$。

- 当 $x_i=2$，$2<a\leq3,1<a\leq\dfrac{3}{2} ,\dfrac{2}{3}<a\leq1 \cdots$。

- 当 $x_i=k$，$k<a\leq k+1,\dfrac{k}{2}<a\leq\dfrac{k+1}{2} ,\dfrac{k}{3}<a\leq\dfrac{k+1}{3} \cdots$。

可以发现，我们要求的最终答案就是一个**最大**的位置，使得它在给定的 $n$ 个 $x_i$ 的所有可能区间内都出现过。


------------

具体实现方法为：

一开始，先将所有 $x_i$ 开始最大的 $n$ 个区间最大左端点插入大根堆，并根据上述规律维护当前堆内区间最小的右端点。

若最大左端点**大于或等于**最小右端点（上述区间都是左开右闭），那么说明此时堆内的各区间没有交集。我们继续将此时的堆顶区间弹出，更新为比它更小的下一个区间。

最后的答案即为维护的最小的右端点。

时间复杂度为 $O(nv\log nv)$。

------------
代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
struct info
{
	double l;
	int id,pos;
	
	bool operator <(const info&a)const{
		return l<a.l;
	}
};
const int N=1010;
int n,a[N];
double minn=1e9;
priority_queue<info> q;
int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		q.push(info{a[i]*1.0,i,1});//最大左端点 
		minn=min(minn,(a[i]+1)*1.0);//最小右端点 
	}
	
	while(!q.empty())
	{
		info now=q.top();
		q.pop();
		if(now.l>=minn)
		{
			q.push(info{a[now.id]*1.0/(now.pos+1)*1.0,now.id,now.pos+1});
			minn=min(minn,(a[now.id]+1)*1.0/(now.pos+1)*1.0);
		 } 
		 else break;
	}

	printf("%.5lf",minn);
	return 0;
}
```

---

## 作者：Vct14 (赞：4)

昨天题解写到一半电脑死机了文章没保存/kk

------------

易知 $x_i\geqslant \lceil\alpha\rceil-1$，则 $\alpha\leqslant \lceil\alpha\rceil\leqslant x_i+1$。则答案一定小于等于最小的 $x_i+1$。考虑从大到小枚举 $\alpha$，判断对于所有 $x_i$，是否存在正整数 $k$ 使得 $x_i=\lceil k\alpha\rceil-1$。当然，这里最好对 $x_i$ 进行去重，否则代码可能会超时。

若存在 $k$ 满足要求，则 $ka\leqslant x_i+1<ka+1$，可以得到 $\frac{x_i}{\alpha}< k\leqslant\frac{x_i+1}{\alpha}$ 即 $\frac{x_i}{\alpha}\leqslant k\leqslant\left\lfloor\frac{x_i+1}{\alpha}\right\rfloor$。那么当且仅当 $\left\lceil\frac{x_i}{\alpha}\right\rceil\geqslant\left\lfloor\frac{x_i+1}{\alpha}\right\rfloor$ 时不存在 $k$，我们将不等式两边同时乘 $\alpha$，得到 $a\left\lfloor\frac{x_i+1}{\alpha}\right\rfloor\leqslant x_i$ 时不存在 $k$。

```c++
#include<bits/stdc++.h>
using namespace std;

int x[1002];

int main(){
	int n;cin>>n;
	for(int i=1; i<=n; i++) cin>>x[i];
	sort(x+1,x+1+n);n=unique(x+1,x+n+1)-x-1;
	for(double a=x[1]+1; a; a-=0.000001){
		bool f=1;
		for(int i=1; i<=n; i++) if(a*(int)((x[i]+1)/a)<=x[i]){f=0;break;}
		if(f){printf("%.6lf",a);break;}
	}
	return 0;
}
```

---

## 作者：Dws_t7760 (赞：4)

萌新刚学 $\LaTeX$，大佬见谅。

## Statement

定义一个实数 $\alpha$ 的谱 $\operatorname{Spec}(\alpha)$ 是整数组成的一个无限长的序列 $\lceil\alpha\rceil-1,\lceil2\alpha\rceil-1,\lceil3\alpha\rceil-1,\cdots$。

现在给定 $n$ 个整数 $x_1,\cdots,x_n$，你要找到最大的实数 $\alpha$，使得对于每个元素 $x_i$ 都有 $x_i$ 在 $\operatorname{Spec}(\alpha)$ 中出现过。

## Solution

首先考虑子问题，给定一个正整数 $x$，若 $x\in \operatorname{Spec}(\alpha)$，求 $\alpha$ 的取值范围。

不妨设 $x$ 为 $\operatorname{Spec}(\alpha)$ 的第 $i$ 项，可知 $\lceil i \times \alpha \rceil - 1 = x$，即 $ x < i \times \alpha \leq x + 1$，解得 $\dfrac{x}{i} < \alpha \leq \dfrac{x + 1}{i}$。


由此可知 $\alpha$ 的取值范围集合为 $\bigcup _{i = 1 }^{\infty }\{ t \mid \dfrac{x}{i} < t \leq \dfrac{x + 1}{i}\}$，由于本题要求误差低于 $10^{-5}$ 即可，所以原式化为 $\bigcup _{i = 1 }^{\infty }\{ t \mid \dfrac{x}{i} + 10 ^ {-6} \leq t \leq \dfrac{x + 1}{i}\}$ 后不影响答案。

 回归原题，令 $A_i$ 为 $\bigcup _{i = 1 }^{\infty }\{ t \mid \dfrac{x_i}{i} + 10 ^ {-6} \leq t \leq \dfrac{x_i + 1}{i}\}$，易知 $1$ 一定属于所有集合，故答案最小为 $1$，不需要考虑小于 $1$ 的元素，可将 $A_i$ 进一步简化为 $\bigcup _{i = 1 }^{x_i }\{ t \mid \dfrac{x_i}{i} + 10 ^ {-6} \leq t \leq \dfrac{x_i + 1}{i}\}$。
 
 我们将所有 $A_i$ 内部的边界离散化，这样可以用一个 bitset 来表示一个 $A_i$，逐个进行按位与运算即可。
 
 ## Code
 
 ```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define len 1010
int n, v[len], a, tre[2 * len * len], l[len * len], r[len * len], cnt, tot;
double t[2 * len * len], tl[len * len], tr[len * len], x, y;
map <double, int> mp;
bitset <2 * len * len> bt[len], btt;
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a, v[a] = 1;
	for (int i = 1; i <= 1000; i++) {
		if (v[i]) {
			for (int j = 1; j <= i; j++) {
				x = 1.0 * i / j + 0.000001, y = 1.0 * (i + 1) / j;
				t[++cnt] = x, t[++cnt] = y;
				tl[++tot] = x, tr[tot] = y;
			}
		}
	}
	sort(t + 1, t + cnt + 1);
	cnt = unique(t + 1, t + cnt + 1) - t - 1;
	for (int i = 1; i <= cnt; i++) mp[t[i]] = i;
	int tmp = 1;
	for (int i = 1; i <= 1000; i++) {
		bt[i].reset();
		if (v[i]) {
			for (int j = tmp; j <= tmp + i - 1; j++) {
				tl[j] = mp[tl[j]], tr[j] = mp[tr[j]];
				for (int k = tl[j]; k <= tr[j]; k++) bt[i][k] = 1;
			}
			tmp += i;
		}
	}
	int ans = 0;
	btt.set();
	for (int i = 1; i <= 1000; i++) if (v[i]) btt &= bt[i];
	for (int i = cnt; i; i--) {
		if (btt[i]) {
			ans = i;
			break;
		}
	}
	if (!ans) cout << "1.00000";
	else cout << fixed << setprecision(6) << t[ans];
	return 0;
}
```

---

## 作者：hensier (赞：3)

当 $x_i$ 在 $\text{Spec}(\alpha)$ 中出现时，有

$$\exists j \in \N^*, \lceil j \alpha \rceil - 1 = x_i$$

即

$$x_i \lt j \alpha \le x_i + 1$$

$$\dfrac{x_i}{\alpha} \lt j \le \dfrac{x_i + 1}{\alpha}$$

由 $j \in \N^*$，只需满足

$$\lfloor \dfrac{x_i}{\alpha} \rfloor + 1 \le \lfloor \dfrac{x_i+1}{\alpha} \rfloor$$

又 $\lfloor \dfrac{x_i}{\alpha} \rfloor \le \lfloor \dfrac{x_i+1}{\alpha} \rfloor$，因而只需考虑

$$\lfloor \dfrac{x_i}{\alpha} \rfloor \neq \lfloor \dfrac{x_i+1}{\alpha} \rfloor (*)$$

不难发现，当 $\alpha \le 1$ 时

$$\dfrac{1}{\alpha} \ge 1$$

$$\dfrac{x_i+1}{\alpha}-\dfrac{x_i}{\alpha} \ge 1$$

进而 $\alpha \le 1$ 时 $(*)$ 成立。由于要求最大值，因此可只考虑 $a \gt 1$。

当 $\alpha \gt 1$ 时则有 $\dfrac{x_i+1}{\alpha}-\dfrac{x_i}{\alpha} \lt 1$。再结合 $(*)$，就只能有 $\lfloor \dfrac{x_i+1}{\alpha} \rfloor = \lfloor \dfrac{x_i}{\alpha} \rfloor + 1$ 了。

进一步地，$\dfrac{x_i+1}{\alpha} \ge \lfloor \dfrac{x_i}{\alpha} \rfloor + 1 = \lfloor \dfrac{x_i}{\alpha} \rfloor + 1 \ge 1$，即 $\alpha \le x_i+1$。

因此 $\lfloor \dfrac{x_i+1}{\alpha} \rfloor \in \{1, 2, \cdots, x_i\}$。

对每个 $k \in \{1, 2, \cdots, x_i\}$，考虑 $\lfloor \dfrac{x_i+1}{\alpha} \rfloor = k$ （同时 $\lfloor \dfrac{x_i}{\alpha} \rfloor=k-1$）时 $\alpha$ 的范围。

1. $\dfrac{x_i}{k} \lt \alpha \le \dfrac{x_i+1}{k}$ 时：$\dfrac{kx_i}{x_i+1} \le \dfrac{x_i}{\alpha} \lt k \le \dfrac{x_i+1}{\alpha} \lt \dfrac{k(x_i+1)}{x_i}$。

	- $\dfrac{kx_i}{x_i+1}=k-\dfrac{k}{x_i+1} \in (k -1,k)$。则 $\lfloor \dfrac{x_i}{\alpha} \rfloor=k-1$。
    
	- $\dfrac{k(x_i+1)}{x_i}=k+\dfrac{k}{x_i} \in (k,k+1)$。则 $\lfloor \dfrac{x_i+1}{\alpha} \rfloor=k$。
    
2. $\alpha \le \dfrac{x_i}{k}$ 时 $\dfrac{x_i}{\alpha} \ge k$，$\lfloor \dfrac{x_i}{\alpha} \rfloor$ 不可能为 $k-1$。

3. $\alpha \gt \dfrac{x_i+1}{k}$ 时 $\dfrac{x_i+1}{\alpha} \lt k$，$\lfloor \dfrac{x_i+1}{\alpha} \rfloor$ 不可能为 $k$。

故 $\dfrac{x_i}{k} \lt \alpha \le \dfrac{x_i+1}{k}$（当然，也可通过在数轴上平移区间的方式获得此结论）。又因为 $\dfrac{x_i+1}{k} \lt \dfrac{x_i}{k-1}$，因而对每个 $x_i$，$\alpha$ 的范围可表示为**一段段互斥区间的并集**。

由于每个 $x_i$ 下的各个区间互斥，因而 $\alpha$ 必然**恰好被包含在 $\mathbf n$ 个区间内**。我们只需要将所有的区间端点位置排序，然后从大到小，遇到右端点时计数器 $+1$，遇到左端点时计数器 $-1$。当计数器值第一次达到 $n$ 时即可得所求的最大 $\alpha$，时间复杂度为：$\mathcal O(n \max\{x_i\} \log (n \max\{x_i\})) \approx \mathcal O(n^2 \log n^2) = \mathcal O(n^2 \log n)$。

一个小小的优化：$\alpha \le x_i+1$。因此要对 $x_1 \sim x_n$ 均满足，$\alpha \le \min\{x_i\}+1$。则只需考虑满足 $\dfrac{x_i+1}{k} \le \min\{x_i\}+1$ 的 $k$，即 $k \ge \lceil \dfrac{x_i+1}{\min\{x_i\}+1} \rceil$。但[可以证明](https://www.luogu.com.cn/paste/om7or5cm)，此优化对复杂度无影响。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, len, cnt, x[1001];
struct node {
    double val;
    int mul;
    bool operator < (const node &x) {
        return val > x.val;
    }
} a[600001];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &x[i]);
    sort(x + 1, x + n + 1);
    n = unique(x + 1, x + n + 1) - x - 1;
    for (int i = 1; i <= n; i++) {
        for (int k = ceil(1.0 * (x[i] + 1) / (x[1] + 1)); k <= x[i]; k++) {
            a[++len] = (node){1.0 * x[i] / k + 1E-6, -1}; // 加 1E-6 的原因是左端点是开区间
            a[++len] = (node){1.0 * (x[i] + 1) / k, 1};
        }
    }
    sort(a + 1, a + len + 1);
    for (int i = 1; i <= len; i++) {
        cnt += a[i].mul;
        if (cnt == n) {
            printf("%.6lf", a[i].val);
            break;
        }
    }
    return 0;
}
```

---

## 作者：gavinliu266 (赞：3)

fix：先去重。

fix：去重写错了。
# 思路
我们首先把 $x$ 数组排序。

可以发现 $0 < \alpha \le x_1$，否则序列里不会出现 $x_1$。

因为求最大值，$\alpha=1$ 时可遍历所有自然数，所以求出来，$\alpha \ge 1$。

然后枚举 $\alpha$，暴力判断即可。

注意到当 $x_i$ 不在序列中时，可以直接 break 掉，只需判断 $i$ 次即可。

## 运行效率
因为有一项常数较大，时间复杂度会产生较大偏差。

这里只分析 $x_1$。

若设有一整数 $k(1 \le k \le x_1+1)$，$\lceil k\alpha \rceil -1=x_1$，则 $\frac{x_1}{k} < \alpha \le \frac{x_1+1}{k}$。

此时，若数列接下来的值均满足题目要求，只有最后一项不符，则运算约 $n \cdot \frac{2 \times 10^5}{k}$。其它情况下，只需判断 $x_1$，计算一次。

最坏共运算约：$2 \times 10^5[n(\sum\frac{1}{k})+x_1-\sum\frac{1}{k}] \approx 2 \times 10^5(n \ln x_1 + x_1 - \ln x_1)$。

虽然看上去效率并不高，但实际上只分析了第一项，后面的项也有很大影响，我没有想到能 hack 该程序的数据。

时间复杂度：$O(n\log x_1 + x_1)$。

# 代码实现
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;
int n;
bool fl;
int a[1005];
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    n = unique(a + 1, a + n + 1) - a - 1;  // 去重
    for(double i = a[1] + 1.0; i >= 1; i -= 0.000005) {  // 避免精度问题
        fl = 1;                                         // 从大到小枚举，找到直接退出
        for(int j = 1; j <= n; ++j) {
            double c = floor(double(a[j] + 1) / i);
            if(ceil(c * i) - 1 != a[j] && ceil(c * i + i) - 1 != a[j]) {  // 两边都判断一下，避免问题
                fl = 0;
                break;
            }
        }
        if(fl) {
            printf("%.6lf\n", i);
            return 0;
        }
    }
}
```

暂时没想到 hack，想到了可以与我讨论一下。请先在在线 IDE 上测完，确定能够 hack。

---

## 作者：M1saka16I72 (赞：3)

## 前言

[更可爱的阅读体验](https://misaka16172.github.io/solution-p10679.html)

怎么题解区全是假做法，这里提供一个和标解思路略微不同的方法。

## 思路

对于每个 $x_i$，设 $x_i=\lceil k\alpha\rceil-1$，解不等式可得 $x_i<k\alpha \leq x_i+1$，考虑枚举 $k$ 把不等式解集转化成一堆区间（即 $[\frac{x_i}{k}+eps,\frac{x_i+1}{k}]$），同时注意到答案保底为 $1$，于是可以忽略右端点在 $1$ 左边的区间，这样枚举到 $k$ 的上界就不会超过 $x_i$。

于是问题就变成了找到最大的、被每个 $x_i$ 形成的区间都覆盖过的数，而这个过程可以离散化后用差分解决；具体地，枚举每个 $x_i$，将其形成的所有区间都推平为 $1$，处理完之后将每个当前为 $1$ 的下标的 $sum$ 值都加上 $1$，最后 $sum=n$ 的下标就是合法的。

容易发现答案一定是某个区间的右端点，所以直接简单从右往左遍历找答案就做完了，如果没有找到就输出 $1$。

时间复杂度 $\mathcal{O}(\sum x\log \sum x)$，$\log$ 来自离散化。

## 代码

```cpp
constexpr int N = 2e6+5;
constexpr db eps = 1e-6;

db raw[N];
int num = 0,c;
inline void add_num(db x){++num,raw[num] = x;}
inline int id(db x){return lower_bound(raw+1,raw+1+c,x)-raw;}
inline void discrete(){
	sort(raw+1,raw+1+num);
	c = unique(raw+1,raw+1+num)-raw-1;
}

int n,x[N],cf[N],sum[N];

inline void add(int l,int r,int v){cf[l]+=v,cf[r+1]-=v;}

void solve(){
    read(n);
    cout<<fixed<<setprecision(7);
    for(int i=1;i<=n;i++){
    	read(x[i]);
    	db l,r;
    	for(int j=1;j<=x[i];j++){
    		l = (db)x[i]/j,r = (db)(x[i]+1)/j;
    		add_num(l+eps),add_num(r);
    	}
    }
    discrete();
    for(int i=1;i<=n;i++){
    	int l,r;
    	for(int j=1;j<=x[i];j++){
    		l = id(((db)x[i]/j)+eps),r = id((db)(x[i]+1)/j);
    		add(l,r,1);
    	}
    	for(int j=1;j<=c;j++)	cf[j]+=cf[j-1];
    	cf[0] = 0;
    	for(int j=1;j<=c;j++){
    		sum[j]+=(bool)cf[j];
    		cf[j] = 0;
    	}
    }
    for(int j=c;j>=1;j--){
    	if(sum[j]==n){cout<<raw[j];return;}
    }
    cout<<1.000000;
}
```

---

## 作者：水星湖 (赞：3)

给出一个正确性有保证但是不太靠谱的做法。

首先对给出的 $n$ 个数去重，设剩下 $n'$ 个数，那么容易发现，$\alpha$ 的最大值不会超过 $\left\lceil \frac{1000}{n'}\right\rceil$，如果更大，那么 $\alpha_{max}\times n'$ 必然大于 $1000$，即 $a_i$ 的值域。

考虑从大到小枚举 $\alpha$，第一个合法的即为答案。

如何判断一个 $\alpha$ 是否合法？可以判断 $n'$ 个数是否分别出现在了 $\alpha$ 形成的序列中，可以使用二分的方法，如果依次尝试 $\operatorname{Spec}(\alpha)$ 感觉会超时。

精度取 $5\times 10^{-6}$，$10^{-5}$ 会寄，~~但我不知道为什么会寄~~。

然后就做完了，时间复杂度理论上不可过。

---

## 作者：TemplateClass (赞：2)

不难发现如果每个 $x_i$ 均在 $\operatorname{Spec}(\alpha)$ 中，那么 $\min\{x_i\}$ 必 $\ge \lceil\alpha\rceil - 1$，即 $\lceil \alpha\rceil \le \min\{x_i\}+1$。

由于是对 $\alpha$ 进行向上取整，所以必然有 $\alpha \le \lceil\alpha\rceil \le \min\{x_i\}+1$。

所以我们先对 $x$ 进行排序、去重，然后从 $x _ 1 + 1$ 开始从大到小枚举 $\alpha$，由于精度的限制，加上我自己的测试，每次减少 $5 \times 10 ^ {-6}$ 即可。

```cpp
#include<iostream>
#include<algorithm>
#include<iomanip>

const int N = 1e3 + 5;
const double eps = 5e-6;
int n, x[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0), std::cout.tie(0);
	
	std::cin >> n;
	for(int i = 1; i <= n; ++i) {
		std::cin >> x[i];
	}
	
	std::sort(x + 1, x + n + 1);
	int n2 = std::unique(x + 1, x + n + 1) - x - 1;
	
    std::cout << std::fixed << std::setprecision(7);
	for(double a = x[1] + 1; a >= 0; a -= eps) {
		bool flag = true;
		for(int j = 1; j <= n2; ++j) {
			int p = (x[j] + 1) / a;
			if(a * p <= x[j]) {
				flag = false;
				break;
			}
		}
		if(flag) {
			std::cout << a;
			break;
		}
	}
	
	return 0;
}
```

---

## 作者：small_john (赞：2)

## 思路

提供一种比较复杂但是无脑的方法。

首先，答案至少为一。不难发现，对于每个 $x$，枚举其在谱中的位置 $k$，那么 $\alpha$ 一定在区间 $(\frac{x}{k},\frac{x+1}{k}]$ 中。去掉重复部分，满足条件的实数 $\alpha$ 就能表示成一些不相交的区间。

最终的答案一定是是某个区间的端点，所以可以离散化，而对于实数 $\alpha$，如果它的谱能让所有的数都出现，那么就相当于有 $n$ 个区间覆盖这个点。

其实现在这个问题已经很板了，其实就是区间加，单点求值。直接差分，然后从大到小枚举出最大的答案即可。

时间复杂度 $O(nv\log nv)$，瓶颈在于离散化，但是足以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
#define double long double 
using namespace std;
const int N = 1e3+5;
const double eps = 1e-6;
int n,x,b[N*N*2],cnt,lt[N*N],rt[N*N],tt,c[N*N*2];
vector<int> v[N*N];
signed main()
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cout<<fixed<<setprecision(6); 
	cin>>n;
	for(int i = 1;i<=n;i++)
	{
		cin>>x;++x;
		int pl = (x-1)*1000000+1,pr = x*1000000;
		for(int i = 2;i<=x;i++)
		{
			int l = ((double)x-1)/i*1000000+1,r = (double)x/i*1000000;
			if(l>r) continue;
			if(r>pl) pl = l;
			else
			{
				lt[++tt] = pl,rt[tt] = pr,b[++cnt] = pl,b[++cnt] = pr;
				pl = l,pr = r;
			}
		}
		lt[++tt] = pl,rt[tt] = pr,b[++cnt] = pl,b[++cnt] = pr;
	}
	sort(b+1,b+cnt+1),cnt = unique(b+1,b+cnt+1)-b-1;
	for(int i = 1;i<=tt;i++)
		lt[i] = lower_bound(b+1,b+cnt+1,lt[i])-b,rt[i] = lower_bound(b+1,b+cnt+1,rt[i])-b,c[lt[i]]++,c[rt[i]+1]--;
	for(int i = 1;i<=cnt;i++)
		c[i]+=c[i-1];
	for(int i = cnt;i;i--)
		if(c[i]>=n) return cout<<(double)b[i]/1000000,0;
	return 0;
}
```

---

