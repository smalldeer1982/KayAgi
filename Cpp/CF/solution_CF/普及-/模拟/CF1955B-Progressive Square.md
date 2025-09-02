# Progressive Square

## 题目描述

大小为 $n$ 的累进正方形是一个 $n\times n$ 的矩阵。选择三个整数 $a_{1,1},c,d$
 ，并根据以下规则构造一个累进正方形：

$a _ {i+1,j} = a _ {i,j} + c$

$a _ {i,j+1} = a _ {i,j} + d$

例如，如果 $n=3,a_{1,1}=1,c=2,d=3$，那么累进正方形如下：
 
$\begin{pmatrix} 1 & 4 & 7 \\ 3 & 6 & 9 \\ 5 & 8 & 11 \end{pmatrix}$

给定 $n,c,d$，有 $n^2$ 个整数，判断这些数是否能组成一个符合规则的累进正方形。

## 样例 #1

### 输入

```
5
3 2 3
3 9 6 5 7 1 10 4 8
3 2 3
3 9 6 5 7 1 11 4 8
2 100 100
400 300 400 500
3 2 3
3 9 6 6 5 1 11 4 8
4 4 4
15 27 7 19 23 23 11 15 7 3 19 23 11 15 11 15```

### 输出

```
NO
YES
YES
NO
NO```

# 题解

## 作者：ZnHF (赞：1)

# 题意简述

给定 $n,c,d$ 和 数组 $b$，并按照以下方式构造 $a$ 矩阵：

$$a_{i+1,j}=a_{i,j}+c$$
$$a_{i,j+1}=a_{i,j}+d$$

求问 $a$ 矩阵中的元素是否与 $b$ 数组中的元素完全一样。

# 题目分析

本题数据范围较小，模拟题意即可。

因为 $c,d$ 均是正整数，所以 $a_{1,1}$ 一定是 $b$ 数组中最小的元素，确定 $a_{1,1}$ 后就可以确定整个 $a$ 矩阵，然后再比较 $a$ 矩阵中的元素是否跟 $b$ 数组中的元素完全一样。

在比较时，我们可以开两个 `map` 分别为 $v,h$，$v_i$ 表示元素 $i$ 在矩阵 $a$ 中的出现次数，$h_i$ 表示元素 $i$ 在数组 $b$ 中的出现次数。在构造 $a$ 矩阵时，如果 $v_{a_{i,j}} > h_{a_{i,j}}$ 或者 $h_{a_{i,j}}=0$，则说明 $a$ 矩阵中的元素与 $b$ 数组中的元素并不完全一样。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){register int t1=0,t2=0;register char x=getchar();while(x<'0' ||x>'9'){if(x=='-') t2|=1;x=getchar();}while(x>='0' && x<='9'){t1=(t1<<1)+(t1<<3)+(x^48),x=getchar();}return t2?-t1:t1;}
inline void write(int x){register int sta[35],top=0;if(x<0) putchar('-'),x=-x;do{sta[top++]=x%10,x/=10;}while(x);while(top) putchar(sta[--top]+48);}
int T,n,c,d,b[250005],f[505][505];
bool flag;
unordered_map<int,int> v,h;
int main(){
	T=read();
	while(T--){
		flag=0;
		h.clear();
		v.clear();
		n=read();
		c=read();
		d=read();
		for(int i=1;i<=n*n;i++){
			b[i]=read();
			h[b[i]]++;
		}
		sort(b+1,b+1+n*n);
		f[1][1]=b[1];
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				f[i+1][j]=f[i][j]+c;
				f[i][j+1]=f[i][j]+d;
			}
		}//构造a矩阵
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(h[f[i][j]]!=0 && v[f[i][j]]!=h[f[i][j]]){
					v[f[i][j]]++;
				}
				else{
					flag=1;
				}
			}
		}//判断是否满足题意
		if(flag) puts("No");
		else puts("Yes");
	}
	return 0;
}
```

---

## 作者：Infinite_Loop (赞：1)

# CF1955B
## 题意
给定三个数 $n,c,d$ 和一个长度为 $n \times n$ 的数组 $b$，要求构造一个 $n \times n$ 的数组 $a$，满足以下条件：

$$
a_{i+1,j} = a_{i,j} + c
$$

$$
a_{i,j+1} = a_{i,j} + d
$$

而且数组 $a$ 中的元素与数组 $b$ 中的元素完全一样。

求是否能构造出数组 $a$ 满足以上条件，可以输出 ```YES```，否则输出 ```NO```。
## 思路
因为 $c$ 和 $d$ 都是正整数，所以 $a$ 数组中最小的数肯定是 $a_{1,1}$，即为 $b$ 数组中最小的数。求出 $a_{1,1}$ 后，我们就可以把整个 $a$ 数组求出来，然后把 $a$ 数组与 $b$ 数组进行比较是否有元素不同即可。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500+10;
int t,n,c,d,a[N*N],b[N*N]; 
int main(){
	cin>>t;
	while(t--){
		cin>>n>>c>>d;
		for(int i=1;i<=n*n;i++)cin>>a[i];
		sort(a+1,a+1+n*n);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int now=a[1]+(i-1)*d+(j-1)*c;
			b[(i-1)*n+j]=now;
		}
		sort(b+1,b+1+n*n);
		int flag=1;
		for(int i=1;i<=n*n;i++){
			if(a[i]!=b[i]){
				flag=0;
				break;
			}
		}
		if(flag)cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：littlebug (赞：1)

## 	Description

给定三个整数 $n,c,d$，可以构造矩阵 $a$ 满足：

$$a_{i+1,j}=a_{i,j}+c$$
$$a_{i,j+1}=a_{i,j}+d$$

其中，$a_{1,1}$ 是已知的。

设 $b$ 为 $a$ 中所有元素随机排列组成的数组。输入给定一个 $b$，求是否存在 $a$ 可以构成 $b$。

## Solution

因为 $n$ 的范围不大，所以可以想到直接进行模拟，我们对以上的递推公式进行一个变形：

$$a_{i,j}=a_{i-1,j}+c$$
$$a_{i,j}=a_{i,j-1}+d$$

酱紫我们就可以更好地进行递推了。

首先，要确定 $a_{1,1}$ 的值，因为 $c,d>0$，所以 $s_{1,1}$ 一定是矩阵 $a$ 中最小的元素，即 $a_{1,1}=\min(b)$。在我们知道 $a_{1,1}$ 的取值后，就可以推导出整个矩阵 $a$ 了，然后在推导矩阵 $a$ 的过程中对每个 $a_{i,j}$ 进行判断其知否存在于 $b$ 中即可。

具体地，我们可以开一个 `multiset` 来存 $b$ 中的所有元素（记为 $apr$），在对 $a_{i,j}$ 进行检查时，看看是否能在 $apr$ 中找到即可，如果不能找到直接判断无解，否则需要**将 $apr$ 中找到的元素删除**后再继续往后遍历。

时间复杂度 $O(n^2\log n^2)$，在 $n\le200$ 的范围时可以通过。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<set>
#define il inline
#define inf (int)(2e9)
#define fail {puts("NO");return;}
using namespace std;
const int MAXN=500+5;
int n,c,d;
int a[MAXN][MAXN],b[MAXN<<1];
multiset <int> apr;
il bool check(int i,int j)
{
	auto it=apr.find(a[i][j]);
	if(it==apr.end())
		return 0;
	apr.erase(it);
	return 1;
}
il void solve()
{
	apr.clear();
	cin>>n>>c>>d;
	a[1][1]=inf;
	for(int i=1;i<=n*n;++i)
	{
		cin>>b[i];
		a[1][1]=min(a[1][1],b[i]);
		apr.insert(b[i]);
	}
	for(int i=1;i<=n;++i)
	{
		if(i!=1)
			a[i][1]=a[i-1][1]+c;
		if(!check(i,1))
			fail;
		for(int j=2;j<=n;++j)
		{
			a[i][j]=a[i][j-1]+d;
			if(!check(i,j))
				fail;
		}
	}
	puts("YES");
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
```

---

## 作者：2c_s (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1955B)

## 思路

题目描述既然是每次加上一个正整数构造的矩阵，那么矩阵的第一个数一定是最小的。

我们读入数据后把它们全部放入一个 **``multiset``** 保存，并找到最小的一个数作为 $a_{1,1}$。

之后按照题意模拟构造一个矩阵，每遍历到一个数就在这个 ``multiset`` 中查询是否存在。如果存在就**删去**并继续遍历，如果不存在直接输出 ``NO`` 并跳出循环。

如果模拟完后没找到不存在的数，输出 ``YES``。

时间复杂度 $\mathcal{O}(Tn^2\log n^2)$。

- 有多组测试数据，记得**清空**变量和 ``multiset``。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
multiset<int>st;
int main(){
	int T;
    cin>>T;
	while(T--){
		int n,c,d,mi=1e9;
        cin>>n>>c>>d;
		st.clear();
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				int x;
                cin>>x;
				st.insert(x);
				mi=min(mi,x);
			}
		}
		for(int i=1;i<=n;++i){
			int x=mi;
			auto p=st.find(mi);
			if(p==st.end()){
				cout<<"NO\n";
				goto next;
			}
			st.erase(p);
			for(int j=2;j<=n;++j){
				auto p=st.find(x+d);
				if(p==st.end()){
					cout<<"NO\n";
					goto next;
				}
				st.erase(p);
				x+=d;//每次更改为这一项的值。
			}
			mi+=c;//别忘每次都得改首项。
		}
		cout<<"YES\n";
		next:;
	}
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/155211169)

---

## 作者：joe_zxq (赞：0)

# 思路

我们可以构造出正方形。然后将构造出的元素 $a$ 与给定的元素 $b$ 分别放到一个 multiset 里。将两者进行比较即可。

但是题目中只给定了 $c$ 和 $d$，没有给定 $a_{1,1}$。因为 $c$，$d$ 均为正数，$a_{1,1}$ 一定是正方形种最小值。我们找出给定元素 $b$ 中的最小值，即可确定 $a_{1,1}$。

关于 STL 容器 multiset 的用法：

multiset 与 set 的不同点在于是可重集合。

`multiset.insert(x)`：插入元素 $x$。

`multiset.erase(x)`：删除元素 $x$。如果有多个 $x$，会全部删除。

`multiset.find(x)`：查找元素 $x$。

`*multiset.begin()`：返回最小值。

`*multiset.rbegin()`：返回最大值。

`multiset1==multiset2`：返回两者中的元素是否相等。

时间复杂度：$O(n^2 \log n)$。

# 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define ll long long

ll a[505][505];
multiset<ll> s, t;

void solve() {
	ll n, c, d, mn = 1e18;
	s.clear();
	t.clear();
	cin >> n >> c >> d;
	for (ll i = 1; i <= n; i++) {
		for (ll j = 1; j <= n; j++) {
			ll x;
			cin >> x;
			s.insert(x);
			mn = min(mn, x);
		}
	}
	a[1][1] = mn;
	for (ll i = 1; i <= n; i++) {
		for (ll j = 1; j <= n; j++) {
			a[i + 1][j] = a[i][j] + c;
			a[i][j + 1] = a[i][j] + d;
			t.insert(a[i][j]);
		}
	}
	if (s == t) {
		puts("YES");
	} else {
		puts("NO");
	}
}

int main() {

	ll tc;
	cin >> tc;
	while (tc--) {
		solve();
	}

	return 0;
}

```

---

## 作者：_ayaka_ (赞：0)

### 思路
可以发现在题目中的 $n$ 比较小，所以可以尝试直接暴力求解。
我们先将 $a$ 数组排序，由于 $c,d\ge1$，所以题目中的 $a_{1,1}$ 就是此处的 $a_1$。

然后我们可以通过 $c,d$ 来求解出一个正确的数组 $b$，经分析，求解式是这样的：
$$ b_{(i-1)\times c+j\times d}=a_1+(i-1)\times c+(j-1) \times d$$
最后将两数组进行比较，检查是否相等就行了。

### 代码
```
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,c,d,a[250005],b[250005],bj;
signed main() {
	cin>>t;
	while(t--){
		cin>>n>>c>>d;
		bj=0;
		for(int i=1;i<=n*n;i++) cin>>a[i];
		sort(a+1,a+n*n+1);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				b[(i-1)*n+j]=a[1]+c*(i-1)+d*(j-1);
		sort(b+1,b+n*n+1);
		for(int i=1;i<=n*n;i++){
			if(a[i]!=b[i]) {
				cout<<"NO\n";
				bj=1;
				break;
			}
		}
		if(bj) continue;
		cout<<"YES\n";
	}
	return 0;
}
```

---

## 作者：Silver_Wolf (赞：0)

## 思路
这个题很明显，就是简单的暴力，非常水。

我们把 $a$ 数组排序，而且 $c,d\ge1$，所以 $a$ 数组第一个就是正方形的第一个了！

再根据 $c,d$ 生成一个 $b$ 数组，也进行排序，两个数组一比较，这个题我们就做完了。

## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,t,c,d,bj;
int a[300010],b[300010];
int main() {
	cin>>t;
	while(t--){
		cin>>n>>c>>d;
		bj=0;//记得清零！ 
		for(int i=1;i<=n*n;i++) cin>>a[i];
		sort(a+1,a+n*n+1);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				b[i*n+j-n]=a[1]+c*(i-1)+d*(j-1);//这个公式通过推理就能得到了 
		sort(b+1,b+n*n+1);
		for(int i=1;i<=n*n;i++){
			if(a[i]!=b[i]) {
				bj=1;
				break;
			}
		}
		if(bj==1) cout<<"no\n";
		else cout<<"yes\n";
	}
}
```

---

## 作者：ttq012 (赞：0)

大水题。因为 $c\ge1$ 且 $d\ge1$，所以 $a_{1,1}$ 肯定为矩阵中最小的元素。有了 $a_{1,1}$ 就可以直接 $O(n^2)$ 构造出唯一一个矩阵，然后分别对矩阵和原数列排序，若两个数列相同则肯定可以，否则肯定不可以。

时间复杂度为 $O(n^2\log n^2)$，时间复杂度的瓶颈在于对数列排序。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 510;
int a[N * N], cc[N * N], b[N][N];
signed main() {
    int T;
    cin >> T;
    while (T--) {
        int n, c, d;
        cin >> n >> c >> d;
        for (int i = 1; i <= n * n; i++)
            cin >> a[i];
        sort(a + 1, a + n * n + 1);
        b[1][1] = a[1];
        for (int j = 1; j <= n; j++)
            for (int i = 1; i <= n; i++)
                if (i + j > 2) {
                    if (j == 1) b[i][j] = b[i - 1][j] + c;
                    else b[i][j] = b[i][j - 1] + d;
                }
        int idx = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cc[++idx] = b[i][j];
        sort(cc + 1, cc + n * n + 1);
        bool ok = true;
        for (int i = 1; i <= n * n; i++)
            if (a[i] != cc[i]) {
                ok = false;
                break;
            }
        if (ok)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
```

---

## 作者：qinmingze (赞：0)

### [题目传送门](https://www.luogu.com.cn/problem/CF1955B)

## 思路

题目询问我们可不可以根据题目给出的 $n^2$ 个数来构造出一个符合题意的矩阵。我们只需要用 set 进行处理即可，具体实现方法如下：

```cpp
for(int i = 1; i <= n; i++){
		ll x = minn;
		auto p = st.find(x);//找寻每一列的第一个数。
		if(p == st.end()){//如果找寻不到的话直接输出无解。
			flag = 1;
			puts("NO");
			break;
		}
		st.erase(p);//删除。
		for(int j = 2; j <= n; j++){
			if(flag) break;
			p = st.find(x + d);//找寻当前行的第 j 个元素。
			if(p == st.end()){//没有当前元素。
				flag = 1;
				puts("NO");
				break;
			}
			x += d;//下一个元素的值。
			st.erase(p);//删除当前数。
		}
		if(flag) break;
		minn += c;//下一行第一个元素的值
	}
```

- 我们分为两层循环，第一层循环遍历行，第二层循环遍历列。

- 第一层循环负责找第 $i$ 行的第 $1$ 个元素，第二层循环负责寻找第 $i$ 行的第 $j$ 个元素。

- **注意第二层循环必须要从第二个元素开始**，因为第一个元素已经在第一层循环遍历完了。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long

using namespace std;

const int N = 510;

multiset<ll> st;

int main(){
	int T;
	cin >> T;
	while(T--){
		ll n, c, d, minn = 1e9;
		cin >> n >> c >> d;
		st.clear();
		for(int i = 1; i <= n * n; i++) {
			ll x;
			cin >> x;
			st.insert(x);
			minn = min(minn, x);
		}
		bool flag = 0;
		for(int i = 1; i <= n; i++){
			ll x = minn;
			auto p = st.find(x);
			if(p == st.end()){
				flag = 1;
				puts("NO");
				break;
			}
			st.erase(p);
			for(int j = 2; j <= n; j++){
				if(flag) break;
				p = st.find(x + d);
				if(p == st.end()){
					flag = 1;
					puts("NO");
					break;
				}
				x += d; st.erase(p);
			}
			if(flag) break;
			minn += c;
		}
		if(!flag)puts("YES");
	}
}
```

---

## 作者：yshpdyt (赞：0)

## 题意
大小为 $n$ 的累进正方形是一个 $n \times n$ 矩阵，满足
$$
a _ {i+1,j} = a _ {i,j} + c
$$

$$
a _ {i,j+1} = a _ {i,j} + d
$$

给定 $n\times n$ 个数和 $c,d$，判断能否构成累进正方形。
## Sol
$c,d$ 为正数，左上角肯定是最小的，找到最小的元素后，先放第一排，找 $a_{1,i+1}=a_{1,i}+d$，找不到无解。

然后竖着放，和横着类似，$a_{i+1,j}=a_{i,j}+c$，找不到无解。

具体来说开个桶，桶为空就是找不到。

最后检查一下是否所有位置都满足即可。

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 2005
#define endl "\n" 
#define fi fisrt
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll a[N*N];
ll f[N][N];
map<ll,ll>mp;
ll n,c,d;
void sol(){
    cin>>n>>c>>d;
    mp.clear();
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)f[i][j]=0;
    for(int i=1;i<=n*n;i++){
        cin>>a[i];
        mp[a[i]]++;
    }
    sort(a+1,a+n*n+1);
    f[1][1]=a[1];
    for(int i=1;i<n;i++){
        if(mp[f[1][i]+d]){
            mp[f[1][i]+d]--;
            f[1][i+1]=f[1][i]+d;
        }else{
            cout<<"No\n";
            return ;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<n;j++){
            if(mp[f[j][i]+c]){
                mp[f[j][i]+c]--;
                f[j+1][i]=f[j][i]+c;
            }else{
                cout<<"No\n";
                return ;
            }
        }
    }
    for(int i=2;i<=n;i++){
        for(int j=2;j<=n;j++){
            if(f[i][j]!=f[i-1][j]+c){
                cout<<"No\n";
                return ;
            }
            if(f[i][j]!=f[i][j-1]+d){
                cout<<"No\n";
                return ;
            }
        }
    }
    cout<<"Yes\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();

    return 0;
}
```

---

