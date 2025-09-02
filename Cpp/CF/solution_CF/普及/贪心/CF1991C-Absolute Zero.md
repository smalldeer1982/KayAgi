# Absolute Zero

## 题目描述

你会得到一个$n$整数的数组$a$。
在一个操作中，您将执行以下两步移动：
1.选择一个整数$x$（$0\le x\le 10^{9}$）。
2.将每个$a_i$替换为$|a_i-x|$，其中$|v|$表示[绝对值](https://en.wikipedia.org/wiki/Absolute_value)$v$。
例如，通过选择$x=8$，数组$[5,7,10]$将变为$[|5-8|，|7-8|，|10-8|]=[3,1,2]$。
构造一个操作序列，使$a$的所有元素在最多$40$的操作中等于$0$，或者确定这是不可能的。您不需要减少操作次数

## 说明/提示

在第一个测试用例中，我们只能通过选择$x=5$执行一个操作，将数组从$[5]$更改为$[0]$。
在第二个测试用例中，不需要任何操作，因为数组的所有元素都已经是$0$了。
在第三个测试用例中，我们可以选择$x=6$将数组从$[4,6,8]$更改为$[2,0,2]$，然后选择$x=1$将其更改为$[1,1,1]$，最后再次选择$x=1.$将数组更改为$[0,0,0]$。
在第四个测试用例中，我们可以按照操作序列$（60,40,20,10,30,25,5）$使所有元素都为$0$。
在第五个测试用例中，可以证明，在最多$40$的操作中，不可能使所有元素都为$0$。因此，输出为$-1$。

## 样例 #1

### 输入

```
5
1
5
2
0 0
3
4 6 8
4
80 40 20 10
5
1 2 3 4 5```

### 输出

```
1
5
0

3
6 1 1
7
60 40 20 10 30 25 5
-1```

# 题解

## 作者：_ZML_ (赞：4)

# 题意
你有一个整数序列 $a$。

你可以进行不超过 $40$ 次操作，每次选择一个数 $x$，将 $a_i$ 变成 $|a_i-x|$。

输出操作次数和每次操作选取的 $x$。
# 思路
构造题。
先说结论：每次选取 $a$ 中的最大值加上最小值的和的一半，也就是 $\frac{1}{2}\times(\max{a_i}+\min{a_i})$）作为 $x$。

至于正确性，可以这样想，每次进行操作之后，原数组的值域都会变成原来的**一半**，所以至多进行 $\log$ 次操作就会变成零。

时间复杂度：$N\times \log(S)$。其中，$S$ 是值域大小。

---

## 作者：白鲟 (赞：3)

操作次数疑似与 $\log$ 相关。于是考虑某种二分。易知若每次选择最大值与最小值的平均数，可以将数据的极差缩小一半。题目于是几乎已经完成了。最后，若某一步操作后同时只存在 $0$ 和 $1$，则显然无解。由于极差必然可以通过上述方法缩小至 $1$，对于任何的无解情形，均可以如此判定。
```cpp
#include <algorithm>
#include <cstdio>
const int maxn = 2e5;
int T, n, tot, a[maxn + 1], b[maxn + 1];
bool flag;
int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        flag = true;
        tot = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a[i]);
        }
        while(true) {
            int maxx = 0, minx = a[1], mid;
            for (int i = 1; i <= n; ++i) {
                maxx = std::max(maxx, a[i]);
                minx = std::min(minx, a[i]);
            }
            mid = (maxx + minx + 1) / 2;
            if (!mid || (maxx == 1 && minx == 0)) {
                break;
            }
            b[++tot] = mid;
            for (int i = 1; i <= n; ++i) {
                a[i] = std::abs(a[i] - mid);
            }
        }
        for (int i = 1; i <= n; ++i) {
            if(a[i]) {
                flag = false;
                break;
            }
        }
        if(!flag) {
            puts("-1");
        }
        else {
            printf("%d\n", tot);
            for (int i = 1; i <= tot; ++i) {
                printf("%d ", b[i]);
            }
            puts("");
        }
    }
    return 0;
}
```

---

## 作者：Dioretsa (赞：2)

记数组 $a$ 中最大值为 $maxa$，最小值为 $mina$。每次操作就是需要让 $maxa$ 不断减小，直至为 $0$。

为了每次让 $maxa$ 尽可能地减小，不妨设 $mid=\lfloor\frac{maxa+mina}{2}\rfloor$，操作为 $x$。
- 若 $x=x_1=mid$，则操作结束后 $maxa'=maxa_1=maxa-x_1=x1-mina$。
- 若 $x=x_2<mid$，则操作结束后 $maxa'=maxa_2=maxa-x_2$。
- 若 $x=x_3>mid$，则操作结束后 $maxa'=maxa_3=x_3-mina$。

不难得出，$maxa1<maxa2$ 且 $maxa1<maxa3$。因此，当 $x=mid=\lfloor\frac{maxa+mina}{2}\rfloor$ 时，可以尽可能地减小 $maxa$，直至为 $0$。

由于 $a_i\le10^9$，每次操作近似将 $maxa$ 减半，即近似地需要 $\log_2(10^9)=30 < 40$ 次操作。若有解，则一定可以在 $40$ 次操作内找到答案。若操作超过 $40$ 次，则一定无解。


```cpp
#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
inline long long read() {
	long long x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
long long T,n,a[MAXN],x[MAXN];
int main() {
	T=read();
	while(T--){
		n=read();
		for(long long i=1;i<=n;i++) a[i]=read();
		long long cnt=1;
		while(cnt<=40){
			long long maxa=0,mina=LONG_LONG_MAX;
			for(long long i=1;i<=n;i++){
				maxa=max(maxa,a[i]);
				mina=min(mina,a[i]);
			}
			long long tst=(maxa+mina)/2;
			x[cnt]=tst;
			bool check=true;
			for(long long i=1;i<=n;i++){
				a[i]=abs(a[i]-tst);
				if(a[i]!=0) check=false;
			}
			if(check) break;
			cnt++;
		}
		if(cnt>40) printf("-1\n");
		else{
			printf("%d\n",cnt);
			for(long long i=1;i<=cnt;i++) printf("%d ",x[i]);
			printf("\n");
		}
	}
	return 0;
}

```

---

## 作者：AKPC (赞：2)

考验情商的题。

我们可以考虑不断减小 $a$ 中元素的值域。我们知道，当现在元素值域为 $[l,r]$ 时，操作参数 $x$，那么值域就会被 $[0,\max\{x-l,r-x\}]$ 包含。事实上，可以假定操作后值域就是这个区间，那么也可以默认 $l=0$。

那么，因为我们假设 $l=0$，当我们取 $x=\frac{r}{2}$ 时，$\max\{x-l,r-x\}$ 是最小的。发现这就是类似二分的过程。

由于 $2^{29}\leq a_i\leq2^{30}$，那么假定初始值域是 $[0,2^{30}]$，完全可以在 $31$ 次操作以内完成。

对于无解，如果数列同时存在奇数和偶数，那么肯定无解，因为操作不可能把两种数同化。

---

## 作者：_ZHONGZIJIE0608_ (赞：1)

给你个长度为 $N$ 的整数序列 $A$，每次可以取一个整数 $P_i$，把所有 $A_i$ 修改为 $|A_i-P_i|$，构造出序列 $P$，如果 $P$ 的长度不能小于等于 $40$，输出 $-1$。多测。

$40$ 次操作，可能操作次数和 $\log$ 有关系，考虑某种二分。

对于每次操作，$P_i$ 设置为数组 $A$ 的**极差**。如果 $A_i$ 全部为 $0$ 或者最大是 $1$ 且最小是 $0$ 就显然可以直接 break 掉。

可以证明，这样操作后可以把所有数变成 $0$，且如果存在操作序列，其长度一定合法。

最后看是否全部变成 $0$ 即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
int a[N],b[N],cnt,n;
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	int T;cin>>T;while(T--){
		cin>>n;bool f=1;
		for(int i=1;i<=n;++i)cin>>a[i];cnt=0;
		while(1){
			int mx=0,mn=a[1];
			for(int i=1;i<=n;++i)mx=max(mx,a[i]),mn=min(mn,a[i]);
			int mid=(mx+mn+1)/2;
			if(!mid||(mx==1&&mn==0))break;
			b[++cnt]=mid;
			for(int i=1;i<=n;++i)a[i]=abs(a[i]-mid);
		}
		for(int i=1;i<=n;++i)if(a[i]){f=0;break;}
		if(!f){cout<<"-1\n";continue;}
		cout<<cnt<<'\n'; 
		for(int i=1;i<=cnt;++i)cout<<b[i]<<' ';
		cout<<'\n';
	}
	return 0;
}
```
[**Record**](https://codeforces.com/contest/1991/submission/273279014)

---

## 作者：Vct14 (赞：0)

duel 到这题了，写篇题解讲讲我的思路。

开题思路是取所有数平均值，但觉得不太能保证正确性，就没往后想。

因为要在 $40$ 次操作内将 $[0,10^9]$ 范围内的数变成 $0$，所以考虑怎样减小数的值域，即怎样减小最大的数又不使最小的数减后的绝对值过大。那么容易想到每次取最大数和最小数的平均数。这样每次可以将值域近似减半，如果有解那么 $40$ 次以内一定可以减完。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
const int N=2e5+2;
int a[N];
int k[N];
 
int main(){
	int t;cin>>t;
    while(t--){
        int n;cin>>n;
        for(int i=1; i<=n; i++) cin>>a[i];
        if(n==1){
            cout<<"1\n"<<a[1]<<"\n";
            continue;
        }
        int mx=40,s=0;
        bool ok=1;
        while(mx--){
            for(int i=1; i<=n; i++){
                if(a[i]) ok=0;
            } 
            if(ok) break;
            sort(a+1,a+1+n);
            int c=(a[n]+a[1])/2;
            if(a[1]==a[n]){
                k[++s]=a[1];
                ok=1;
                break;
            } 
            if(c==0){
                ok=false;
                break;
            }
            for(int i=1; i<=n; i++){
//                cout<<a[i]<<" ";
                a[i]=abs(c-a[i]);
            }// cout<<"\n";
            k[++s]=c;
//            cout<<c<<"\n";
        }
        if(!ok){
            cout<<"-1\n";
            continue;
        }
        cout<<s<<"\n";
        for(int i=1; i<=s; i++) cout<<k[i]<<" ";
        cout<<"\n";
    }
	return 0;
}
```

我写的代码可能有点繁杂，应该是可以简化的，但是 duel 的时候抢时间就懒得改了。

---

## 作者：ELECTRODE_kaf (赞：0)

既然替换后的数是与所选的数的差，那最佳选择肯定是最大值和最小值的平均值。时间复杂度 $O(Qn\log n)$。

```cpp
const ll N = 2e5 + 10, MAX = 40, inf = 3e9;
ll Q, n, a[N];
vector<ll> ans;

int main() {
	sync_off;
	cin >> Q;

	count(Q) {
		ans.clear();
		cin >> n;
		ll min1 = inf, max1 = -inf, cnt = 0;

		rep(i, 1, n) {
			cin >> a[i];
			update(min1, a[i], min);
			update(max1, a[i], max);
		}

		while (1) {
			if (max1 == 0) {
				cout << ans.size() << '\n';

				if (ans.empty() == 0) {
					for (ll i : ans)
						cout << i << ' ';
				}

				endl;
				break;
			} else if (cnt == MAX) {
				cout << "-1\n";
				break;
			} else {
				ll x = (min1 + max1) / 2;
				ans.pb(x);
				min1 = inf;
				max1 = -inf;
				cnt++;

				rep(i, 1, n) {
					a[i] = abs(a[i] - x);
					update(min1, a[i], min);
					update(max1, a[i], max);
				}
			}
		}
	}
}
```

---

## 作者：copper_ingot (赞：0)

[Luogu](https://www.luogu.com.cn/problem/CF1991C)

[Codeforces](https://codeforces.com/problemset/problem/1991/C)

显然如果两个数的奇偶性不同，那么对于任意的操作都无法让这两个数同时为 $0$，所以先判断奇偶。

然后对于每次操作，设 $maxn$ 为 $x$ 中的最大值，$minn$ 为最小值，则让每个 $x_i$ 都变为 $|x_i-(maxn+minn)/2|$ 可以使极差缩小一半以上。

在最坏情况下需要操作 $\log(\max x_i-\min x_i)$ 次，因为 $x_i \le 10^9$，所以操作次数小于 $40$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[200001], cnt, ans[50], maxn, minn;
void solve(){
	scanf("%d", &n); cnt = maxn = 0, minn = 2e9;
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 2; i <= n; i++) if (a[i] % 2 != a[i - 1] % 2){puts("-1"); return;}
	for (int i = 1; i <= n; i++) maxn = max(maxn, a[i]), minn = min(minn, a[i]);
	while (maxn != 0 || minn != 0){
		ans[++cnt] = (maxn + minn) >> 1;
		maxn = 0, minn = 2e9;
		for (int i = 1; i <= n; i++) a[i] = abs(a[i] - ans[cnt]), maxn = max(maxn, a[i]), minn = min(minn, a[i]);
	}
	printf("%d\n", cnt);
	for (int i = 1; i <= cnt; i++) printf("%d ", ans[i]);
	puts("");
}
int main(){scanf("%d", &t); while (t--) solve(); return 0;}
```

---

## 作者：Lame_Joke (赞：0)

- ### 大体思路

  看到此题，首先想到二分，当然，二分可以过，但是这题用贪心就行，毕竟题目没要求操作次数最小。接下来说贪心操作，每次选择数列中最大和最小的两个数，取 $x$ 为这两个数的平均值，这样能让这两个数相等，其他数也减去这个数，这样就做到了不断缩小值域，一般情况下可以在最少次数内减为 $0$。

- ### 具体实现

  ```cpp
  #include<bits/stdc++.h>
  using namespace std;
  int T,n,a[200005],ans[45];
  void qsort(int l,int r)
  {
  	int i=l,j=r,mid=a[(l+r)/2+1];
  	while(i<=j)
  	{
  		while(a[i]<mid) i++;
  		while(a[j]>mid) j--;
  		if(i<=j)
  		{
  			swap(a[i],a[j]);
  			i++;
  			j--;
  		}
  	}
  	if(l<j) qsort(l,j);
  	if(i<r) qsort(i,r);
  }
  int main()
  {
  	scanf("%d",&T);
  	int mid,ans1;
  	bool s;
  	while(T--)
  	{
  		scanf("%d",&n);
  		for(int i=1;i<=n;i++)
  		{
  			scanf("%d",&a[i]);
  		}
  		s=0;
  		if(n==1)
  		{
  			printf("1\n%d\n",a[1]);
  			continue;
  		}
  		for(int j=1;j<=n;j++)
  		{
  			if(a[j]!=0) s=1;
  		}
  		if(s==0)
  		{
  			printf("0\n\n");
  			continue;
  		}
  		for(int i=1;i<=40;i++)
  		{
  			ans1=i;
  			s=0;
  			sort(a+1,a+1+n);
  			mid=(a[1]+a[n])/2;
  			
  			ans[i]=mid;
  			for(int j=1;j<=n;j++)
  			{
  				a[j]=abs(a[j]-mid);
  				if(a[j]!=0) s=1;
  			}
  			
  			if(s==0) break;
  			else ans1=0;
  		}
  		if(ans1==0)
  		{
  			printf("-1\n");
  			continue;
  		}
  		printf("%d\n",ans1);
  		for(int i=1;i<=ans1;i++)
  		{
  			printf("%d ",ans[i]);
  		}
  		printf("\n");
  	}
  }
  ```

---

## 作者：JXR_Kalcium (赞：0)

## 题目大意

给定一个长度为 $n$ 的数组 $a$，每次可以选定任意一个自然数 $x$，然后对于每个 $1\le i\le n$ 都使 $a_i\leftarrow|a_i-x|$，要求最少的操作次数使 $a$ 数组全部变成 $0$，并且求每次的 $x$，如果不行就输出 $-1$。

## 解题思路

非常简单，第一次先将 $x$ 设为 $\max(a_i)$，然后在之后每次操作将 $x$ 变成原来的一半，这样的话 $a$ 数组的总区间就从 $[0,x]$ 变成了 $\left[0,\large\frac{x}{2}\right]$，缩小了一半（对我们非常有利），一直到这个数组全部变成 $0$，或者操作次数比 $40$ 大就可以停止了。

## AC 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define endl putchar(10)
#define spc putchar(32)
using namespace std;

inline ll read()
{
    ll x=0,f=1; char c=getchar();

    while(c<48 || c>57)
    {
        if(c=='-') f=-1;
        c=getchar();
    }

    while(c>47 && c<58)
    x=(x<<1)+(x<<3)+c-48, c=getchar();
    return x*f;
}

inline void write(ll x)
{
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48); return;
}

ll t,n,a[200001],mx[41],cnt,bz;

int main()
{
    t=read();

    while(t--)
    {
        n=read(); mx[1]=0;
		bz=0; cnt=0;

        for(int i=1; i<=n; ++i)
        {
            a[i]=read(); mx[1]=max(mx[1],a[i]);
            if(a[i]) bz=1;
        }

        if(bz) ++cnt; bz=1;
        
        while(true)
        {
            bz=0;

            for(int i=1; i<=n; ++i)
            {
                a[i]=abs(a[i]-mx[cnt]);
                if(a[i]) bz=1;
            }
            
            if(bz && cnt<40)
            mx[cnt+1]=ceil(mx[cnt]/2.0), ++cnt;
            else break;
        }
		
        if(bz) write(-1), endl;
        
        else
        {
            write(cnt); endl;
            for(int i=1; i<=cnt; ++i) write(mx[i]), spc;
            endl;
        }
    }

    return 0;
}

```

---

## 作者：Jairon314 (赞：0)

> [更好的体验](https://www.cnblogs.com/Jair314/p/18330313)

$$ \large\textbf{Solution} $$

----------

$$ \text{Absolute Zero} $$

> C
> 
> [题目链接](https://www.luogu.com.cn/problem/CF1991C)
> 
> [提交记录](https://www.luogu.com.cn/record/169267362)

题意：给定长度为 $n$ 的序列 $\{a_n\}$. 操作为每次选定一个值 $x$，然后对 $a_i \rightarrow |a_i-x|$. 最多不能超过 $40$ 次操作，问能否构造一种方案，使序列中所有的元素都变成 $0$？

分析：

首先考虑无法构造方案的情况，容易发现当序列中出现奇偶性不同的数时永远也不可能得到全零序列，而其他情况均可行。特判即可。

对于剩下的情况：

- 观察数据猜测时间复杂度大概是线性带 ``log`` 级别的，容易想到取最大值和最小值的平均值作为 $x$，这样使得每一次值域范围都会折半。复杂度合理。

模拟过程即可。

----------

---

## 作者：Trubiacy_ (赞：0)

### 赛时思路

这个题，~~我也不知道我是怎么过的~~，可以想到的是，**我们需要找到一个方法在每次循环之后缩小元素的范围**，所以我选择每次进行排序，选择 $x=\lceil\frac{a_{max}}{2}\rceil$ 进行操作。

另外在想到上面的思路之前我就想到过，若序列中各元素奇偶性不一致，则无解，但我最终没有运用上，因为我担心可能会有奇偶性一致的情况超出 $40$ 步（官方题解说明了不存在这种情况）所以选择手动进行了 $40$ 次操作。

### 赛时 AC 代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define x first
#define y second
#define MAXN 0x3f3f3f3f3f3f3f3f
#define MINN -0x3f3f3f3f3f3f3f3f
#define Trubiacy ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
using namespace std;

const int N=2e5+29;
int n,a[N];

signed main(){
    Trubiacy;
    // int Tracy=1;
    int Tracy; cin>>Tracy;
    while(Tracy--){
        cin>>n;
        for(int i=1;i<=n;i++){
            cin>>a[i];
        }
        sort(a+1,a+1+n);
        int t=0;
        vector<int> ans;
        bool f=false;
        while(t<40){
            if(a[n]==0){
                f=true;
                break;
            }
            t++;
            int op=a[n]/2+(a[n]%2==1);//取x的值为最大值/2上取整
            ans.push_back(op);//将答案暂存因为后面还要判断是否有解
            for(int i=1;i<=n;i++){
                a[i]=abs(a[i]-op);
            }
            sort(a+1,a+1+n);
        }
        // cout<<t<<endl;
        // if(a[n]==0) f=true;
        if(f){
            cout<<t<<endl;
            for(auto i:ans) cout<<i<<" ";
        }
        else cout<<-1;
        cout<<endl;
    }
    return 0;
}
```

---

## 作者：yyz1005 (赞：0)

首先注意到对于 $x,y$，如果 $x,y$ 奇偶性不同，不妨设 $x$ 为奇数，$y$ 为偶数，那么由于 $|x-a|+|y-a|$ 的奇偶性与 $(x-a)+(y-a)$ 相同（$x-a \equiv a-x\pmod 2$），于是 $|x-a|+|y-a| \equiv (x+y)-2a \equiv x+y \equiv 1 \pmod 2$。

也就是说 $|x-a|,|y-a|$ 仍然为一个奇数一个偶数，显然，在同时存在奇数与偶数的情况下无论如何，无法完成题目要求。

下考虑所有 $a_i$ 奇偶性相同的情况。

不妨令当前最大值为 $f > 0$，最小值为 $g \ge 0$，不妨取 $x = \frac{f+g}{2}$。

那么注意到操作后的最大值 $f' = \max(f-x,x-g) = \frac{f-g}{2} \le \frac{f}{2}$。

也就是说最大值至少减半且更小，也就是说 $\log_2f+1$ 次操作后一定满足 $f=0,g = 0$，显然在 $40$ 次以内。

[Code](https://codeforces.com/contest/1991/submission/273166556)

---

## 作者：Link_Cut_Y (赞：0)

动态维护序列，每次找到当前序列的最大值和最小值。设 $l = \max a_i - \min a_i$。题目操作相当于整体平移。将所有值都减去 $d = \max a_i - \dfrac{d}{2}$ 之后值域最劣缩小为原来的一半，只需要做 $\log V$ 次即可。只有 $0, 1$ 两个数时显然无解。[submission](https://www.luogu.com.cn/problem/U457854)。

---

## 作者：_O_v_O_ (赞：0)

首先，我们发现如果 $a$ 中奇偶性不同，那么一定不行，因为假设 $x,y$ 是两个奇偶性不同的数，一定无法找到一个整数 $z$ 满足 $|x-z|$ 与 $|y-z|$ 奇偶性不同。

我们又发现我们每次选的数如果为 $(\max_i a_i-\min_i a_i)\div 2$，那么整个 $a$ 的极差一定会至少折半。

那么我们发现一开始的极差最多就是 $a$ 的值域，即 $10^9$，这启示着我们我们每次就直接选择 $(\max_i a_i-\min_i a_i)\div 2$ 就行了。

时间复杂度 $O(\sum n\log V)$，其中 $V$ 是值域，最多 $40$。

---

