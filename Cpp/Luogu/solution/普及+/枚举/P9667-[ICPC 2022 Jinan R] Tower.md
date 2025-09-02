# [ICPC 2022 Jinan R] Tower

## 题目描述

庞教授搭了 $n$ 座不同高度的塔。第 $i$ 座塔的高度是 $a _ {i}$。

寿教授不喜欢这些参差不齐的塔。他决定**先去掉它们中的 $m$ 座**，然后执行以下操作中的一些（或不执行）：
- 选择一座塔并增加它 $1$ 个单位高度。
- 选择一座塔并减少它 $1$ 个单位高度。
- 选择一座塔并把它的高度 $a _ {i}$ 除以 $2$，如果它不是整数的话，向下取整。

寿教授永远不会选择被拆除的塔。如果操作后，塔的高度变为 $0$，则不允许操作。在这些约束条件下，寿教授可以按任意顺序执行任意数量的运算。

寿教授希望所有没有被拆除的塔都有相同的高度 $a _ {i}$。请计算实现此目标的最小操作次数。

## 样例 #1

### 输入

```
3
2 0
2 6
5 0
1 2 3 4 5
5 3
1 2 3 4 5```

### 输出

```
2
4
1```

# 题解

## 作者：Nwayy (赞：9)

和 lyt 组队随便打了打。

---

翻译：给定 $n$ 个数，现在你需要从中**任意**删除 $m$ 个数，然后对剩余 $n-m$ 个数进行以下操作：

- 将 $a_{i}$ 加上 $1$。

- 将 $a_{i}$ 减去 $1$。

- 将 $a_{i}$ 除以 $2$。

每次操作代价为 $1$，而且在操作过程中你不能把 $a_{i}$ 变为 $0$。问把剩余的数变成相同的数的最小代价是多少。

- 数据范围：多测 $1 \le T \le 10$，$1 \le m < n \le 500$，$1 \le a_{i} \le 10^9$。

---

首先发现 $n \le 500$ 与 $6$ 秒的实现，考虑三次方做法。

但按照题目的意思枚举删哪些点肯定行不通。于是我们考虑枚举最终变成的那个值，然后计算所有点变成那个值的代价，删掉最大的 $m$ 个点，剩余点代价之和取最小值。

但是值域有 $10^9$，因此我们考虑答案可能在哪些点。

容易猜答案存在于某个数不断除以 $2$ 的某个结果中，因此存下每个数不断除以 $2$ 直到 $1$ 的所有结果，枚举它，再按上面的方法统计最小值即可。

于是我们惊人的发现 AC 了。复杂度是 $O(Tn^2 \log^2 V)$ 的。第一只 $\log$ 是枚举答案的，第二只 $\log$ 是对于 $i \in [1,n]$ 计算 $a_{i}$ 的代价的，$V$ 是值域。 

---

- 现在我们考虑证明。

我们只需证明答案不在除以 $k$ 后存在加 $1$ 减 $1$ 之类的答案即可。那么这个证明类似一个经典问题：给定 $n$ 个坐标，要求你再另外选出一个坐标，要求所有点到此坐标距离最短。

显然，在这个问题中，若 $n$ 为奇数，答案为排序后的中间点；若 $n$ 为偶数，答案为排序后两个中间点其中一个。

为什么不会是中间点加减 $1$ 呢？对于奇数显然会有一半加 $1$ 个点贡献多 $1$，显然更劣；对于偶数，答案不变。

因此原问题类比这个问题可得答案一定在除以 $k$ 的某个关键点上。

---

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 505
#define int long long
int n,m,i,j,ans,a[N],t,s[N];
vector<int>G;
signed main(){
	scanf("%lld",&t);
	while(t--){
		G.clear();
		scanf("%lld%lld",&n,&m),ans=1e9;
		for(i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(i=1;i<=n;i++){
			int k=a[i];
			while(k){
				G.push_back(k);
				k>>=1;
			}
		}
		for(int y:G){
			for(i=1;i<=n;i++) s[i]=1e9;
			for(i=1;i<=n;i++){
				int k=a[i],cnt=0;
				while(k>=1){
					s[i]=min(s[i],cnt+abs(k-y));
					k>>=1,cnt++;
				}
			}
			sort(s+1,s+1+n);
			int sum=0;
			for(i=1;i<=n-m;i++) sum+=s[i];
			ans=min(ans,sum);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：int_stl (赞：2)

这道题思路如下：
- 有 $n$ 座塔，可以进行以下操作：
	- 选择一座塔并且增加 $a_i$ 高度 $1$。
	- 选择一座塔并且减小 $a_i$ 高度 $1$。
	- 选择一座塔并且将高度 $a_i$ 除以 $2$。

那么我们可以先对每座塔进行这 $3$ 个操作，得出每座塔所需的次数，然后进行排序，移除 $m$ 座塔，剩下 $n - m$ 座塔操作次数总和即是最小操作次数。  
由这个思路可以得到以下代码：
```cpp
#include <bits/stdc++.h>

using namespace std;
#define LL long long

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        set<int> s;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            int x = a[i];
            while (x) {
                s.insert(x);
                x >>= 1;
            }
        }
        LL ans = 9E18;
        for (int i : s) {
            auto get = [&](int x) {
                if (x - i <= 0) {
                    return i - x;
                }
                int res = 0;
                while (x / 2 >= i) {
                    x /= 2;
                    res++;
                }
                int tmp = res + x - i;
                if (x / 2 > 0) {
                    x /= 2;
                    return min(tmp, res + 1 + i - x);
                }
                else {
                    return tmp;
                }
            };
            vector<int> tmp;
            for (int i = 0; i < n; i++) {
                tmp.push_back(get(a[i]));
            }
            sort(tmp.begin(), tmp.end());
            LL res = 0;
            for (int i = 0; i < n - m; i++) {
                res += tmp[i];
            }
            ans = min(ans, res);
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Auto_Accepted (赞：1)

Rank 1 来随便写写。
## 题意
给你 $n$ 个塔，要求你先删除 $m$ 个塔，再通过以下 $3$ 种操作使得剩下的塔高度相同：

1. 将一个塔的高度增加 $1$。
1. 将一个塔的高度减少 $1$。
1. 将一个塔的高度除以 $2$ （向下取整）。
## 题解
考虑到操作 $1$、$2$ 和操作 $3$ 之间的顺序是可以随意调换的，也就是先进行操作 $1$、$2$ 后进行操作 $3$ 和先进行操作 $3$ 后进行操作 $1$、$2$ 是等价的。

然后通过模拟样例可知最后达到的相同高度一定是某个塔不停的进行操作 $3$ 的结果。

于是枚举最后高度，计算最小次数即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline void solve(){
	int n , m;
	cin >> n >> m;
	vector <int> a(n) , ans , c(n);
	for_each(a.begin() , a.end() , [&](int &i){
		cin >> i;
		int tmp = i;
		while(tmp){
			ans.push_back(tmp);
			tmp >>= 1;
		}
	});
	int minn = 9e18;
	for(auto x : ans){
		for(int j = 0;j < n;j++){
			c[j] = 9e18;
			a[j] <= x ? 
			a[j] < x ? 
			c[j] = x - a[j] : 
			c[j] = 0 : 0;
			if(a[j] > x){
				int tmp = a[j] , cnt = 0;
				while(tmp > x){
					if(tmp > x && (tmp >> 1) <= x){
						c[j] = min(cnt + tmp - x , cnt + (x - (tmp >> 1)) + 1);
						break;
					}
					tmp >>= 1;
					cnt++;
				}
			}
		}
		sort(c.begin() , c.end());
		partial_sum(c.begin() , c.end() , c.begin());
		minn = min(minn , c[n - m - 1]);
	}
	cout << minn << endl;
}
signed main(){
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}
```

---

## 作者：tiger2008 (赞：1)

### 题解

这题相对来说不算难。

结论题，最后所有塔楼的高度肯定是其中一个塔楼高度不断除 $2$ 得来的。

这时就枚举所有最后可能的取值，然后计算每个塔楼高度变成这个取值的最⼩次数，接着去掉 $m$ 个最大的数，取所有 $ans$ 的最小值即可。
 
### code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define int long long
using namespace std;
int T;
int arr[505];
int brr[100005];
int crr[505];
bool cmp(int a,int b){
	return a>b;
}
signed main(){
	cin>>T;
	while(T--){
		memset(brr,0,sizeof(brr));
		int n,m;
		cin>>n>>m;
		int cnt=0;
		for(int i=1;i<=n;i++){
			cin>>arr[i];
			int tmp=arr[i];
			while(tmp){
				cnt++;
				brr[cnt]=tmp;
				tmp/=2;
			}
		}
		int ans=1145141919810;
		for(int i=1;i<=cnt;i++){
			int answ=0;
			for(int j=1;j<=n;j++){
				if(arr[j]<=brr[i]){
					crr[j]=brr[i]-arr[j];
					answ+=crr[j];
					continue;
				}
				int num=arr[j];
				int tmp=0;
				while(num>=brr[i]*2){
					tmp++;
					num/=2;
				}
				if(num!=0)crr[j]=min(num+tmp-brr[i],tmp+brr[i]-num/2+1);
				else crr[j]=num+tmp-brr[i];
				answ+=crr[j];
			}
			sort(crr+1,crr+n+1,cmp);
			for(int j=1;j<=m;j++)answ-=crr[j];
			ans=min(ans,answ);
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：ccg12345 (赞：0)

场切了本题，赛后来写篇题解。

## 题意简化 

先给你 $n$ 座塔，删除掉 $m$ 座塔，并通过一定的操作使得剩下塔的高度相等。

1. 选择一个塔，增加一个单位高度。

2. 选择一个塔，减少一个单位高度。

3. 选择一个塔，使高度除以 $2$（向下取整）。

## 思路

其实想到本题的思路并不困难，但我太菜了刚开始还以为是 dp 把这题撂在一边。

实在没题可做的时候才来看本题，没思路，开始模拟样例，发现了一些东西：最后的相对高度一定是某个塔不断进行操作 $3$ 的结果，又显然有对一个塔先进行操作 $1$、$2$ 再操作 $3$ 所需要的操作次数等于先进行操作 $3$ 再操作 $1$、$2$，那么正解就出来了，即：通过枚举最后高度，来计算塔到这个高度的最小操作次数。

这里是 [代码](https://www.luogu.com.cn/paste/3p9nyv5i) and [评测记录](https://www.luogu.com.cn/record/126616598)。

---

## 作者：zxh_qwq (赞：0)

很容易看出，先进行`1,2`再进行`3`和进行`3`再进行`1,2`是等价的。而且一个塔的高度肯定是通过`3`操作得来的，那么正解就出来了:

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, m, a[100005], b[100005], t[100005],cnt=0,k,ans = 5e17, x, s, p;
void solve()
{
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(t,0,sizeof(t));
	cin>>n>>m;
    cnt=0,ans=5e17;
	for(int i = 1; i <= n; i++)
	{
		cin >> a[i];
		k = a[i];
		while(k > 0)
			t[++cnt] = k, k /= 2;
	}
	for(int i = 1; i <= cnt; i++)
	{
		x = 0;
		for(int j = 1; j <= n; j++)
		{
			b[j] = 5e17;
			if(a[j] < t[i])
				b[j] = t[i] - a[j];
			else if(a[j] == t[i])
				b[j] = 0;
			else
			{
				s = a[j], p = 0;
				while(s > t[i])
				{
					if(s / 2 <= t[i])
					{
						b[j] = min(s + p - t[i], p + t[i] - s / 2 + 1);
						break;
					}
					s /= 2, p++;
				}
			}
		}
		sort(b + 1, b + n + 1);
		for(int j = 1; j <= n - m; j++)
			x += b[j];
		ans = min(x, ans);
	}
	cout << ans << endl;
	return ;
}
main()
{
	int t;
	cin >> t;
	while(t--)
		solve();
}
```

---

