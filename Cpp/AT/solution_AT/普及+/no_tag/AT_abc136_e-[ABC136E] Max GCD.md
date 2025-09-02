# [ABC136E] Max GCD

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc136/tasks/abc136_e

長さ $ N $ の整数列 $ A_1,\ A_2,\ \cdots,\ A_N $ があります。

次の操作を $ 0 $ 回以上 $ K $ 回以下行うことができます。

- $ i\ \neq\ j $ なる $ 1 $ 以上 $ N $ 以下の $ 2 $ つの整数 $ i,\ j $ を選び、$ A_i $ に $ 1 $ を足し、$ A_j $ に $ -1 $ を足す。この操作の後いずれかの要素が負になってもよい。

操作後の $ A $ の全ての要素を割り切る正の整数として考えられる値の最大値を計算してください。ただし、正の整数 $ x $ が整数 $ y $ を割り切るとは、ある整数 $ z $ を用いて $ y\ =\ xz $ と表せる場合を表します。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 500 $
- $ 1\ \leq\ A_i\ \leq\ 10^6 $
- $ 0\ \leq\ K\ \leq\ 10^9 $
- 入力は全て整数である

### Sample Explanation 1

例えば以下の操作で、$ 7 $ が $ A $ の全ての要素を割り切るようにできます。 - $ i\ =\ 2,\ j\ =\ 1 $ とする。$ A $ は $ (7,\ 21) $ となる。 また、$ 8 $ 以上の整数が $ A $ の全ての要素を割り切るようにはできません。

### Sample Explanation 2

例えば、以下のように操作を $ 5 $ 回行います。 - $ i\ =\ 2,\ j\ =\ 1 $ とする。$ A $ は $ (2,\ 6) $ となる。 - $ i\ =\ 2,\ j\ =\ 1 $ とする。$ A $ は $ (1,\ 7) $ となる。 - $ i\ =\ 2,\ j\ =\ 1 $ とする。$ A $ は $ (0,\ 8) $ となる。 - $ i\ =\ 2,\ j\ =\ 1 $ とする。$ A $ は $ (-1,\ 9) $ となる。 - $ i\ =\ 1,\ j\ =\ 2 $ とする。$ A $ は $ (0,\ 8) $ となる。 このとき、$ 0\ =\ 8\ \times\ 0,\ 8\ =\ 8\ \times\ 1 $ と表せるので、$ 8 $ は $ A $ の全ての要素を割り切ります。また、$ 9 $ 以上の整数が $ A $ の全ての要素を割り切るようにはできません。

## 样例 #1

### 输入

```
2 3
8 20```

### 输出

```
7```

## 样例 #2

### 输入

```
2 10
3 5```

### 输出

```
8```

## 样例 #3

### 输入

```
4 5
10 1 2 22```

### 输出

```
7```

## 样例 #4

### 输入

```
8 7
1 7 5 6 8 2 6 5```

### 输出

```
5```

# 题解

## 作者：wuwendongxi (赞：12)



### 题意
给定一个长为 $N$ 的序列，允许进行不超过 $K$ 次操作,每一次操作选定两个不同的数 $A[i]$ 和 $A[j]$，使一个数 $+1$，一个数 $-1$，最后让序列中每一个数都能被 $P$ 整除，求 $P$ 的最大值。

------------
### 思路
- 找找题目性质，发现无论多少次操作，序列的和都不会变，所以 $P$ 一定是 $sum$ 的因数。
- 又因为 $sum<=1e9$，所以想到枚举 $sum$ 的所有因数，然后验证答案，题目变为使序列中每一个数变为 $P$ 的倍数的最小操作次数。
- 将每个数除以 $P$ 的余数进行排序，想到贪心，我们可以发现：余数较小的用减操作，余数大的用加操作，这样按照余数由小到大排序，首尾用一个操作。

---------------

### 代码
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int n,k,a[503],sum,ans=1,det[503];
bool check(int x)
{
    for(int i=1;i<=n;i++) det[i]=a[i]%x;
    sort(det+1,det+n+1);
    int l=1,r=n; long long opc=0;
    while(l<=r)
	{
        while(det[l]%x==0&&l<=r) ++l;
        while(det[r]%x==0&&l<=r) --r;
        int tmp=min(det[l]%x,x-det[r]%x);
        det[l]-=tmp,det[r]+=tmp; opc+=tmp;
    }
    return (opc<=k);
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum+=a[i];
    for(int k=sqrt(sum);k;--k)
	{
		if(sum%k) continue;
        if(check(k)) ans=max(ans,k);
        if(check(sum/k)) ans=max(ans,sum/k);
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：dd_d (赞：4)

## Sol 
记这个数列的和为 $sum$。  
那么显然，对于每一次操作，$sum$ 的值都不会改变。  
最后的答案，也一定是 $sum$ 的因数。  
那么我们枚举一下 $sum$ 的因数，然后判断一下这个值是否可行。  
考虑怎么判断。  
考虑贪心。  
我们对余数较小的数进行减操作，然后对于余数较大的数进行加操作即可。  
最后验证一下，取个 $max$ 就行。  
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
int n,k,sum,Max;
int a[10001],f[10001];
bool cmp(int x,int y)
{
	return x<y;	
}
int check(int x)
{
	int ans=0;
	for (int i=1;i<=n;i++)
		f[i]=a[i]%x;
	sort(f+1,f+n+1,cmp);
	int l=1,r=n;
	while (l<=r)
	{
		int x1=f[l],x2=x-f[r];
		if (x1<x2) ans=ans+x1,f[r]=f[r]+x1,l++;
		if (x1>x2) ans=ans+x2,f[l]=f[l]-x2,r--;
		if (x1==x2) ans=ans+x1,l++,r--;
//		writesp(x1),writeln(x2);
	}
	return ans;
} 
signed main()
{
	n=read(),k=read();
	for (int i=1;i<=n;i++)
	{
		a[i]=read();
		sum+=a[i];
	}
	for (int i=1;i<=sqrt(sum);i++)
		if (sum%i==0)
		{
			if (check(i)<=k) Max=max(Max,i);
//			writesp(i);writeln(check(i));
			if (check(sum/i)<=k) Max=max(Max,sum/i);
//			writesp(sum/i);writeln(check(sum/i));
		}
	writeln(Max);
	return 0;
}

```


---

## 作者：Wf_yjqd (赞：2)

又是好水的一道绿题。。

------------

显然，$\sum^{n}_{i=1}A_i$ 的值不变。

考虑若一个数能整除所有的 $A_i$，则一定能整除 $\sum^{n}_{i=1}A_i$。

那么可以找出 $\sum^{n}_{i=1}A_i$ 的所有因数，挨个进行 `check` 即可。

如何 `check` 呢？考虑贪心按 $A_i\mod x$ 来排序，每次用最大的和最小的进行操作，双指针 $\operatorname{O}(n)$ 求解。

总体复杂度 $\operatorname{O}(n\times\operatorname{d}(n))$，其中 $\operatorname{d}(n)$ 表示 $n$ 的因数个数。还是过的去的吧。

------------

代码很好理解吧。。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5;
int unprime[maxn],prime[maxn],pcnt;
void get_prime(int mx){
    for(int i=2;i<=mx;i++){
        if(!unprime[i]){
            prime[++pcnt]=i;
            for(int j=i*2;j<=mx;j+=i)
                unprime[j]=1;
        }
    }
    return ;
}
int n,k,a[1680],b[1680],sum,ans;
bool check(int x){
    for(int i=1;i<=n;i++)
        b[i]=a[i]%x;
    sort(b+1,b+n+1);
    int l=1,r=n,cnt=0;
    while(!b[l])
        l++;
    while(l<=r){
        if(cnt>k)
            break;
        if(b[l]==x-b[r]){
            cnt+=b[l];
            l++;
            r--;
        }
        else if(b[l]<x-b[r]){
            cnt+=b[l];
            b[r]+=b[l];
            l++;
        }
        else{
            cnt+=x-b[r];
            b[l]-=(x-b[r]);
            r--;
        }
    }
    return cnt<=k;
}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        sum+=a[i];
    }
    get_prime(sqrt(sum+168)+168);
    for(int i=1;i<=sqrt(sum)+1;i++)
        if(sum%i==0){
            if(i>ans&&check(i))
                ans=i;
            if(sum/i>ans&&check(sum/i))
                ans=sum/i;
        }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：TLEWA (赞：1)

## 简要题意

题目所给的翻译部分地方表述不清晰，在这里给出一个清楚的版本

给定一个长为 $N$ 的正整数序列 $A$，你可以进行最多不超过 $K$ 次操作，每次操作选择不同的两个 $i,j$，使 $A_i$ 加上 $1$，$A_j$ 减去 $1$（注意可能产生负数）。最终使序列中的每一个数都可以被整数 $P$ 整除，求最大的 $P$。

## 思路

首先我们可以发现每次操作不改变序列的和，即 $\sum_{i=1}^{n} A_i$ 不变。所以我们要找的 $P$ 必定是初始时的 $\sum_{i=1}^{n} A_i$ 的因子（最大的 $P$ 不可能为负。因为 $P=1$ 时必定符合条件），发现别的题解并没有关于这个步骤的证明，我们来简单证明一下（第一次写这种证明，如果有错误请及时指正）：

一个整数 $P$ 是整数 $x$ 的因子，当且仅当可以找到一个整数 $n$，使得 $nP=x$，也就是说，如果整数 $P$ 是整数 $x,y$ 的因子时，我们必定可以找到两个整数 $n_1,n_2$，使得 $n_1 P = x,n_2 P = y$，与此同时，这两个数的和 $z$ 就可以被表示成 $(n_1 + n_2)P$ 了，而 $n_1+n_2$ 显然还是一个整数，所以当整数 $P$ 是整数 $x,y$ 的因子时，其必定为 $x+y$ 的因子。

如果序列 $A$ 中的每一个数都是整数 $P$ 的因子，$A_1$ 必定是 $P$ 的因子，$A_1=\sum_{i=1}^{1} A_i$，根据我们上面的结论，如果 $\sum_{i=1}^{j} A_i$ 是 $P$ 的因子，$A_{j+1}$ 也是 $P$ 的因子，则 $\sum_{i=1}^{j} A_i + a_{j+1}=\sum_{i=1}^{j+1} A_i$ 是 $P$ 的因子，运用数学归纳法可以证得，$P$ 必定也是 $\sum_{i=1}^{n} A_i$ 的因子，证毕。

所以我们枚举每个 $\sum_{i=1}^{n} A_i$ 的因数作为 $P$，每次判断是否能在 $K$ 次内构造出符合要求的序列，最后把所有符合要求的 $P$ 取最大值即可。下面我们重点讲解一下怎么判断能否构造出符合要求的序列：

贪心地想，对于每一次的 $P$，我们将序列中每一个数除以 $P$ 的余数排序，余数较小的我们用减操作，余数较多的我们用加操作，这样操作次数一定是最少的，双指针 $O(n)$ 求解单次 `check`，总的时间复杂度为 $O(n \sqrt{\sum_{i=1}^{n} A_i })$。

## AC 代码

上面的讲解有不懂可以看注释

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k;
int arr[505];

int summ,ans=1;

int cost_arr[505];

bool check(int num) {
	//计算余数 
	for(int i=1;i<=n;++i) cost_arr[i]=arr[i]%num; //如果做减法，花费就是 cost_arr[i]。如果做加法，花费是 num-cost_arr[i] 
	sort(cost_arr+1,cost_arr+1+n);
	
	int cost=0,l=1,r=n;
	while(l<=r && cost<=k) { //l>r，说明操作完成了，cost>k，说明无解 
		if(!cost_arr[l]) {l++;continue;}
		else if(cost_arr[r]==num) {r--;continue;}
		
		while(cost_arr[l] && l<=r) {
			int cnt=min(cost_arr[l],num-cost_arr[r]); //将操作合并，一次进行多个目标相同的操作 
			cost_arr[l]-=cnt,cost_arr[r]+=cnt,cost+=cnt;
			if(cost_arr[r]==num) r--;
		}
		if(!cost_arr[l]) l++;
	} 
	if(cost>k) return 0;
	return 1;
}

int main() {
	cin >> n >> k;
	for(int i=1;i<=n;++i){
		cin >> arr[i];
		summ+=arr[i]; //summ 变量即为所有数的总和 
	}
	
	for(int i=1;i*i<=summ;++i) {
		if(summ%i) continue; //不是因子直接跳出 
		if(check(i)) ans=max(ans,i);
		if(check(summ/i)) ans=max(ans,summ/i);
	}
	
	cout << ans;
	
	return 0;
}

```


---

## 作者：liuziqin (赞：0)

## 题目简述

给你一个序列 $A$ 和一个整数 $K$ ，你可以对这个序列操作不超过 $K$ 次，使得存在一个整数 $P$ 可以整除 $A$ 中每个元素，求出最大的 $P$ 。

## 思路

从题意来看，无论怎么进行操作，元素的总量不变。

我们设 $sum=\sum_{i=1}^nA_i$ ，易证 $P$ 一定能被 $sum$ 整除。

考虑暴力枚举答案。每当枚举到一个符合条件的 $P$ 时，判断是否合法。至于如何判断，我们可以将每一个 $A_i$ 对 $P$ 的余数从小到大进行排序，然后小的和大的进行匹配，最后判断是否 $\le K$ 即可。

## Code

```c++
#include<bits/stdc++.h>
using namespace std;
int a[505],now[505];
int n,k;
bool check(int u){
	for(int i=1;i<=n;i++)now[i]=a[i]%u;
	sort(now+1,now+n+1);//按照余数进行排序 
	int tot=0;
	for(int i=1,j=n;i<j;i++){
		while(i<j){
			if(u-now[j]>now[i]){
				now[j]+=now[i];
				tot+=now[i];//计算贡献 
				now[i]=0;
				break;
			}
			now[i]-=u-now[j];
			tot+=u-now[j];//计算贡献 
			j--;
		}
	}//小的和大的进行匹配 
	return tot<=k;
}//检查目前的P是否合法。 
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	int sum=0,ans;
	for(int i=1;i<=n;i++)sum+=a[i];//求和 
	for(int i=1;i<=sum;i++){
		if(sum%i==0){
			if(check(i))ans=i;//合法更新答案 
		}
	}
	cout<<ans<<"\n";//输出 
	return 0;
}
```

---

## 作者：Redamancy_Lydic (赞：0)

太唐了，打个模拟赛把人打傻了。

首先设 $sum$ 表示所有元素和，易得 $sum$ 整除是所有元素都能整除的必要条件。

然后想找到充要条件的话显然可以枚举所有 $sum$ 然后一个一个检验，由于枚举的量级在 $\sqrt{sum}$，所以检验时我们拥有富裕的时间。

具体的，假设当前需要验证的模数为 $x$，根据题目要求，我们容易得到一个贪心策略：按照数组取模后的值排序，用一个双指针维护非 $0$ 的最大最小元素，每次最大配最小修改，最后看看修改次数是否合法即可。

[提交记录](https://atcoder.jp/contests/abc136/submissions/58133118)

---

## 作者：chrispang (赞：0)

这道题作为一道绿题，肯定还是有一定的难度的（大佬除外）。那么，本蒟蒻给大家浅浅的分析一下吧！

- 由于不管进行多少次操作，总和一定不会变，所以，我们的答案 $p$ 一定是 $sum$ 的因数。
- 然后呢，从 $1$ 到 $\sqrt{sum}$ 枚举 $sum$ 的因数，之后判断是否可以。
- 将每个数除以 $p$ 的余数进行排序，我们可以发现：余数较小的用减去一些，余数大的用加操作，进行记录。
- 最后判断一下操作次数是否小于 $k$ 就行了。

上代码：

```c++
#include <bits/stdc++.h>
using namespace std;

int n, k, sum, ans = 1, a[510], mod[510];
bool check(int x) {
	for (int i = 1; i <= n; i++)
		mod[i] = a[i] % x; //把余数都记下来 
	sort(mod + 1, mod + n + 1);
	int l = 1, r = n;
	long long pts = 0;
	while(l <= r) {
		while(mod[l] % x == 0 && l <= r) l++; //%x的原因是怕mod[i]超过x 
		while(mod[r] % x == 0 && l <= r) r--; //同上 
		long long t = min(mod[l] % x, x - (mod[r] % x)); //找出哪个才能加上去 
		mod[l] -= t, mod[r] += t, pts += t; //进行记录 
	}
	return pts <= k;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
    	cin >> a[i];
		sum += a[i]; //算出总和 
    }
    for (int i = sqrt(sum); i; i--) {
    	if(sum % i) continue; //如果i不能整除sum，则下一个 
    	if(check(i)) ans = max(ans, i); //找出最大值 
    	if(check(sum / i)) ans = max(ans, sum / i); //同理 
    }
    cout << ans << endl;
    return 0;
}
```

这是蒟蒻的第一篇题解，如果你觉得可以的话，请动动你的小手点个赞吧！谢谢啦！

---

## 作者：XYQ_102 (赞：0)

很显然的是，这样操作总和不会变，然后所有 $\gcd$ 的可能的取值都是会是 $sum$ 的因子，所以可以 $\Theta(\sqrt {sum})$ 的时间复杂度来枚举 $\gcd$，然后 $\Theta(n)$ 遍历用最小操作来看是否是小于 $k$，最后取最大即可。
## Code
```cpp
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const ll N = 1e6 + 9, mod = 1e9 + 7;

ll a[N];
ll b[N];
ll sum = 0;
ll n, k;
ll ans;
void check(ll p) {
    ll ssum = 0;
    for (ll i = 1; i <= n; i++) {
        b[i] = a[i] % p;
    }
    sort(b + 1, b + 1 + n);
    ll sub = 0;
    ll add = 0;
    int l = 1, r = n;
    while (l <= r) {
        while (l <= r && b[l] == 0) {
            l++;
        }
        while (l <= r && b[r] == p) {
            r--;
        }
        if (r == l) {
            ssum += min(b[l], p - b[l]);
            break;
        }
        if (l > r) break;
        ssum += b[l];
        ll t = b[l];
        
        b[l] = 0;
        while (l <= r && t > 0) {
            if ( b[r] + t >= p ) {
                t -= (p - b[r]);
                b[r] = p;
                r--;
            } else {
                b[r] += t;
                t = 0;
                break;
            }
        }
    }
    if (ssum <= k) {
        ans = max(ans, p);
    }
}
signed main() {
    cin >> n >> k;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    ans = -1;
    check(sum);
    for (ll i = 1; i * i <= sum; i++) {
        if (sum % i == 0) {
            check(i);
            check(sum / i);
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

## 作者：大眼仔Happy (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc136_e)

题目翻译很屎怎么办。

考虑到一个性质，我们发现每次操作 $\sum a_i$ 并不会改变，所以答案 $\rm ans$ 必须满足 ${\rm ans}\mid\sum a_i$，所以我们枚举这玩意的因数。

假设枚举的是 $x$，我们显然有贪心策略让余数更小的减，更大的加，最后判断操作次数是否合法即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
int inline read()
{
	int num=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}
	return num*f;
}
int n,k,a[N],sum,ans;
int s[N],tot;
void solve(int x)
{
	int res=0;tot=0;
	for(int i=1;i<=n;i++)if(a[i]%x)s[++tot]=a[i]%x;
	sort(s+1,s+1+tot);
	int L=1,R=tot;
	while(L<R)
	{
		int cnt=min(s[L],x-s[R]);
		s[L]-=cnt;s[R]+=cnt;res+=cnt;
		if(s[L]==0)L++;else R--;
	}
	if(res<=k)ans=max(ans,x);
}
// 将 n 个数调成 x 的倍数所需要的最小价值
int main(){
	n=read();k=read();
	for(int i=1;i<=n;i++)a[i]=read(),sum+=a[i];
	for(int i=1;i*i<=sum;i++)
	{
		if(sum%i)continue;
		if(i*i==sum)solve(i);
		else solve(i),solve(sum/i);
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：maple_trees_112 (赞：0)

很好，又找到了一道可以安慰我的绿题。

## 思路

最后输出的答案一定是这个序列之和的因子，那么我们可以枚举这个序列之和的因子，然后考虑贪心。先将所有数模当前因子后排序，前面的数减，后面的数加，再和前面的对比谁大即可。

代码

```cpp
#include <iostream>
#include <bits/stdc++.h>
#include <cstdio>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <queue>
#include <math.h>
#include <stack>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string.h>
#include <algorithm>
#define int long long
const int N = 1e5 + 10;
const int M = 1e3 + 10;
const int INF = 0x3f3f3f3f;
using namespace std;
int n,k,a[510],sum,f[510],ans = 1;
bool check(int x)
{
    for(int i = 1;i <= n;i++) 
    {
    	f[i] = a[i] % x;
	}
    sort(f + 1,f + n + 1);
    int l = 0,r = n; 
	int opc = 1;
    while(l <= r)
	{
        while(f[l] % x == 0 && l <= r)
        {
        	l++;
		}
        while(f[r] % x == 0 && l <= r) 
		{
			r--;
		}
        int tmp = min(f[l] % x,x - f[r] % x);
        f[l] -= tmp,f[r] += tmp; 
		opc += tmp;
    }
    return (opc <= k);
}
signed main()
{
    std::cin>>n>>k;
    for(int i = 1;i <= n;i++) 
    {
    	std::cin>>a[i];
		sum += a[i];
	}
    for(int i = sqrt(sum);i >= 1;--i)
	{
		if(sum % i) 
		{
			continue;
		}
        if(check(i)) 
    	{
    		ans = max(ans,i);
		}
        if(check(sum / i)) 
        {
        	ans = max(ans,sum / i);
		}
    }
    std::cout<<ans<<'\n';
    return 0;
}
```


---

## 作者：SuperCowHorse (赞：0)

观察题目，不难发现一个性质：所有数的和在加减过程中是不变的。

那么就说明：答案在所有数和 $sum$ 的因数中。

根据数据范围，又不难发现，$sum\le500\times10^6=5\times10^8$。

所以枚举 $sum$ 的因数，时间复杂度 $O(\sqrt{sum})$。

那有如何判断此时枚举到的因数 $x$ 能否成为答案呢？

可以采用贪心的策略，先将所有数模 $x$ 后排序，使用双指针，前面的数减，后面的数加，再统计总步数有没有超过 $k$ 即可。

代码：[Code](https://atcoder.jp/contests/abc136/submissions/43067449)。

---

## 作者：Dreamerly (赞：0)

## 题目：[AT_abc136_e](https://www.luogu.com.cn/problem/AT_abc136_e)
## 思路：
**首先**，不论做多少次操作 ，序列的总和 $sum$ 永远不变。而题意中让我们求最大的最小值 $x$ ，既然它是序列中所有数的因子，那么它肯定也是 $sum$ 的因子。

**然后**，看数据发现 $sum$ 的规模也不大， $O\left(\sqrt{sum}\right)$ 的枚举肯定能过，因此我们可以从 $1-\sqrt{sum}$ 中枚举 $sum$ 的因数，然后判断是否可行，取最大值。

**如何判断**：

先计算出所有数对于当前 $x$ 的余数。由于一个数要成为 $x$ 的倍数，只能往下**减掉它的余数**，或加上**它的余数与 $x$ 的差值**，因此从小到大排列。

然后用双指针去遍历余数，贪心地将余数小的数补给余数较大的数即可。最后检验，可行就取最大值。

## 代码：
```
#include<bits/stdc++.h>
using namespace std;
int read(){ 
	int num=0,sign=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){
		if(ch=='-') sign=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		num=(num<<3)+(num<<1)+(ch^48);
		ch=getchar(); 
	}
	return num*sign;
} 
void write(int x){ 
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
	return;
}
int n,k,ans=-1;
int a[510];
bool check(int x){
	vector<int> ve;
	int res=0;
	for(int i=1;i<=n;i++){
		if(a[i]%x) ve.push_back(a[i]%x);
	}
	sort(ve.begin(),ve.end());
	int l=0,r=ve.size()-1;
	while(l<r){
		int tmp=min(ve[l],x-ve[r]);
		res+=tmp;
		ve[l]-=tmp;
		if(!ve[l]) l++;
		ve[r]+=tmp;
		if(ve[r]==x) r--;
	}
	return res<=k;
}
int sum;
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;i++) sum+=(a[i]=read());
	for(int i=1;i<=sqrt(sum);i++){
		if(sum%i==0){
			if(check(i)) ans=max(ans,i); 
		    if(check(sum/i)) ans=max(ans,sum/i);//两个因数两两匹配，加快枚举 
		}
	}
	write(ans);
	return 0;
} 
```


---

