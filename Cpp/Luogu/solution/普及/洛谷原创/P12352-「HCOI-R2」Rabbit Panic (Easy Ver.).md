# 「HCOI-R2」Rabbit Panic (Easy Ver.)

## 题目背景

**注意在问题的这个版本中，你需要解决和 Hard Ver. 一样的问题，但是不需要最小化步数，而且数据范围不同。**

## 题目描述

你有一个长度为 $n$ 的排列 $\{p_n\}$，初始 $p_i = i$。每次你可以选择 $m$ 个**不同**位置的元素，并**同时**将它们改成它们的平均值（不取整）。

最后你需要使所有元素都相等。

请你构造一组操作方案，无解输出 $-1$。

**注意：你无需最小化操作数量。**

## 说明/提示

### 样例解释 1

- $[1,2,3,4,5,6]\to [3.5,3.5,3,4,3.5,3.5]\to [3.5,3.5,3.5,3.5,3.5,3.5]$。
- 注意：这不是唯一的答案。

### 数据范围

**本题采用捆绑测试。**

- Subtask 0 (20 pts)：$1\leq \sum n\leq 10$。
- Subtask 1 (30 pts)：$m\bmod 2=0$。
- Subtask 2 (10 pts)：$n\bmod 2=0$，且 $m\bmod 2=1$。
- Subtask 3 (40 pts)：无特殊限制。

保证 $1 \leq T \leq 10^3$，$1 \leq m \leq n \leq 2\times 10^3$，$1 \leq \sum n \leq 10^4$。


## 样例 #1

### 输入

```
1
6 4```

### 输出

```
2
1 2 5 6
2 3 4 5
```

# 题解

## 作者：fish_love_cat (赞：5)

Upd：改了一些胡言乱语的部分，比如倒闭了。

整场最简单的。

---

注意到最后剩下的一定是整个数列的平均值。

由于是一个排列，所以要得到这个值最简单的一个方法是让第 $i$ 大值和第 $i$ 小值取平均。


于是我们把第 $i$ 大值和第 $i$ 小值两两分组，在选中过程中整组整组的选即可。

但是当 $m$ 是奇数时注意到会多出一位，此时选择的只能是数列的平均值，否则值会取错。然而如果数列平均值为小数不在序列中，那就无解。

还有就是反复选中显然不会有什么影响，本题不需要最小化步数，所以怎么构造都是对的。

还有一种无解的情况是 $m=1$，判掉即可。

代码易于实现。

```cpp
#include<bits/stdc++.h>
using namespace std;
void solve(){
    int n,m;
    cin>>n>>m;
    if(n==1){
        puts("0");
        return;
    }
    if(m==1){
        puts("-1");
        return;
    }
    if(!(n&1)&&(m&1)){
        puts("-1");
        return;
    }
    int flc=(n-m)/2+1;
    cout<<flc<<'\n';
    for(int i=1;i<=flc;i++){
        if(m&1)cout<<n/2+1<<' ';
        for(int j=2;j<=m;j+=2)
            cout<<j/2+i-1<<' '<<n+1-(j/2+i-1)<<' ';
        puts("");
    }
}
signed main(){
    int t;
    cin>>t;
    while(t--)
        solve();
    return 0;
}
```

---

## 作者：zzx0102 (赞：4)

赛时拼尽全力终于战胜。

不难发现当 $n$ 是偶数且 $m$ 是奇数时无解，因为根本无法出现几个数相加和是平均数。

$n$ 是偶数 $m$ 是偶数时比较简单，前 $\dfrac{m}{2}$ 个数的和和后 $\dfrac{m}{2}$ 个数的和是平均数，随便找个顺序枚举前后序列即可。

$n$ 是奇数同理，此时平均数就是中位数。只不过如果 $m$ 是奇数时可以加个中位数进去，所以也是有解的。

感觉次数不太好到 $2n^2$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define I inline
namespace SlowIO {
	const int SZ = (1 << 20) + 1;
	char buf[SZ], *p1 = buf, *p2 = buf;
	char buffer[SZ];
	int op1 = -1;
	const int op2 = SZ - 1;
	I char gc() {
		if(p1 != p2) return *p1++;
		return p1 == (p2 = (p1 = buf) + fread(buf, 1, SZ - 1, stdin)) ? EOF : *p1++;
	}
	I void flush() {
		fwrite(buffer, 1, op1 + 1, stdout);
		op1 = -1;
	}
	I void pc(const char &x) {
		if(op1 == op2) flush();
		buffer[++op1] = x;
	}
	I int read() {
		int x = 0, f = 1; char ch = gc();
		while(ch < '0' || ch > '9') {if(ch == '-') f = -f; ch = gc();}
		while(ch >= '0' && ch <= '9') x = x * 10 + (ch ^ 48), ch = gc();
		return x * f;
	}
	I void write(int x) {
		if(x < 0) pc('-'), x = -x;
		char s[25];
		int tot = 0;
		while(x || !tot) {
			s[tot++] = x % 10 + 48;
			x/=10;
		}
		while(tot--) pc(s[tot]);
	}
} using namespace SlowIO;
const int N = 2010;
signed main() {
	int T;
	cin >> T;
	while(T--) {
		int n, m; cin >> n >> m;
		if(n == 1 && m == 1) {
			cout << "0\n";
			continue;
		}
		if(n % 2 == 1) {
			int p = m / 2, l = 1, r = n, len = n / 2;
			int mid = n + 1 >> 1;
			int o = (len + p - 1) / p;
			cout << o << '\n';
			for(int i = 1; i < o; i++) {
				for(int j = l; j <= l + p - 1; j++) cout << j << ' ';
				for(int j = r - p + 1; j <= r; j++) cout << j << ' ';
				if(m % 2 == 1) cout << mid << '\n'; else cout << '\n'; 
				l += p, r -= p;
			}
			for(int i = mid - 1, cnt = 0; cnt < p; cnt++, i--) cout << i << ' ';
			for(int i = mid + 1, cnt = 0; cnt < p; cnt++, i++) cout << i << ' ';
			if(m % 2 == 1) cout << mid << '\n'; else cout << '\n';
			continue;
		}
		if(m % 2 == 1) {cout << "-1\n"; continue;}
		int l = 1, r = n, p = m / 2;
		int o = (n + m - 1) / m;
		cout << o << '\n';
		for(int i = 1; i < o; i++) {
			for(int j = l; j <= l + p - 1; j++) cout << j << ' ';
			for(int j = r - p + 1; j <= r; j++) cout << j << ' '; cout << '\n';
			l += p, r -= p;
		}
		int c = m - r + l - 1;
		for(int i = l; i <= r; i++) cout << i << ' ';
		for(int i = 1; i <= c / 2; i++) cout << i << ' ' << n - i + 1 << ' ';
		cout << '\n';
	}
	return 0;
}

/*
9 4
0101010101
*/
```

---

## 作者：Clare613 (赞：3)

## 思路
类似于构造题，可以分讨：
- $n$ 为奇数，$m$ 为奇数\
每一次取中间与两端各取 $m$ 除 $2$ 个，输出即可。
- $n$ 为偶数，$m$ 为奇数\
无解，输出 $-1$。
- $n$ 为奇数，$m$ 为偶数\
两端各取 $m$ 除 $2$ 个，输出即可。
- $n$ 为偶数，$m$ 为偶数\
两端各取 $m$ 除 $2$ 个，输出即可。\
值得注意的是，如果 $n$ 的值为 $1$，输出 $0$。如果 $m$ 的值为 $1$，输出 $-1$。每次有多的可以重复输出一部分。
## code:

```cpp
#include<iostream>
#include<queue>
#define MOD 1000000007
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--){
		int n,m;
		cin>>n>>m;
		if(n%2==0&&m%2==1){
			cout<<-1<<"\n";
			continue;
		}
		if(m==1){
			if(n==1) cout<<0<<"\n";
			else cout<<-1<<"\n";
			continue;
		}
		if(n%2==1){
			if(m%2==1){
				m--;
				cout<<(n-1+m-1)/m<<"\n";
				for(int i=n/2;i>=m/2;i-=m/2){
					for(int j=i-m/2+1;j<=i;j++){
						cout<<j<<" ";
					}
					cout<<n/2+1<<" ";
					for(int j=n-i+1;j<=n-i+m/2;j++){
						cout<<j<<" ";
					}
					cout<<"\n";
				}
				if((n-1)%m!=0){
					for(int i=1;i<=m/2;i++){
						cout<<i<<" ";
					}
					cout<<n/2+1<<" ";
					for(int i=n-m/2+1;i<=n;i++){
						cout<<i<<" ";
					}
				}
			}
			else{
				cout<<(n-1+m-1)/m<<"\n";
				for(int i=n/2;i>=m/2;i-=m/2){
					for(int j=i-m/2+1;j<=i;j++){
						cout<<j<<" ";
					}
					for(int j=n-i+1;j<=n-i+m/2;j++){
						cout<<j<<" ";
					}
					cout<<"\n";
				}
				if((n-1)%m!=0){
					for(int i=1;i<=m/2;i++){
						cout<<i<<" ";
					}
					for(int i=n-m/2+1;i<=n;i++){
						cout<<i<<" ";
					}
				}
			}
		}
		else{
			cout<<(n+m-1)/m<<"\n";
			for(int i=n/2;i>=m/2;i-=m/2){
				for(int j=i-m/2+1;j<=i;j++){
					cout<<j<<" ";
				}
				for(int j=n-i+1;j<=n-i+1+m/2-1;j++){
					cout<<j<<" ";
				}
				cout<<"\n";
			}
			if(n%m!=0){
				for(int i=1;i<=m/2;i++){
					cout<<i<<" ";
				}
				for(int i=n-m/2+1;i<=n;i++){
					cout<<i<<" ";
				}
				cout<<"\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：Colinxu2020 (赞：2)

构造题。

首先，我们可以注意到取一段区间变为平均值的操作不影响这段区间的数的和，因而在整个操作过程中序列的和永远为 $\frac{n \times (n-1)}2$ 不变，又因为最终序列中所有元素的值一样，因此每个元素的值都是 $\frac{n-1}2$，也就是这个排列中位数的值，分类讨论这个元素是否在排列中，即 $n$ 的奇偶性。

## 情况一

$n$ 是奇数，此时我们可以发现只要以中位数为对称中心对称，继续分讨 $m$ 的奇偶性，如果 $m$ 是偶数则每一次对称的选择左右的元素，否则在 $m$ 是偶数的基础上加选中位数即可。

## 情况二

$n$ 是偶数，此时中位数是一个实际上不存在的元素，类似于情况一，我们对称的选择左右的元素，但是，当 $m$ 是奇数时，我们不再能找到一个元素来补充上去，所以无解。

## 细节

如果按上面的方法操作完发现没有满 $m$ 个，则需要在已经操作完成的元素中选择来补齐。为此我们还需要记录一下哪些元素已经处理完成。

如果 $m=1$ 特判下 $n=1$ 无需操作，否则输出 $-1$。

## 代码

```cpp
#include<iostream>
#include<sstream>
using namespace std;

const int maxn=2000+10;
int T,n,m,vis[maxn];

int main(){
    cin>>T;
    while(T--){
        cin>>n>>m;
        if(m==1){
            if(n!=1)cout<<-1<<endl;
            else cout<<0<<endl;
            continue;
        }
        for(int i=1;i<=n;i++)vis[i]=0;
        stringstream cache; int left=m;
        if(n%2){
            int cnt=(n+m-m%2-2)/(m-m%2);
            cache<<cnt<<endl;
            for(int i=1;i<=n/2;i++){
                cache<<i<<' '<<n-i+1<<' '; left-=2; vis[i]=vis[n-i+1]=true;
                if(left<=1){
                    for(int j=1;j<=n;j++)vis[j]=0;
                    if(left==1)cache<<(n+1)/2<<endl,vis[(n+1)/2]=true;
                    else cache<<endl;
                    left=m;
                }
            }
            if(left!=m){
                for(int i=1;i<=n&&left;i++)if(!vis[i])cache<<i<<' ',left--;
                cache<<'\n';
            }
        }else{
            if(m%2){
                cout<<-1<<endl;
                continue;
            }
            int cnt=(n+m-2)/m;
            cache<<cnt<<endl;
            for(int i=1;i<=n/2;i++){
                cache<<i<<' '<<n-i+1<<' '; left-=2; vis[i]=vis[n-i+1]=true;
                if(!left){
                    for(int j=1;j<=n;j++)vis[j]=0;
                    cache<<endl; left=m;
                }
            }
            if(left!=m){
                for(int i=1;i<=n&&left;i++)if(!vis[i])cache<<i<<' ',left--;
                cache<<'\n';
            }
        }
        if(left==m||left==0)cout<<cache.str();
        else cout<<-1<<endl;
    }
}
```

---

## 作者：Milthm (赞：2)

没 T2 一半难。

首先最容易想到的就是 $m$ 为偶数的情况，可以每次取两边的 $\frac{m}2$ 个，往中间取，中间不够 $m$ 个就随便选一个包含中间这部分的长度为 $m$ 的区间（因为平均值已经在两边归好了，多取一些和平均值相等的数计算平均值没有影响）。

然后 $m$ 是奇数的情况也很简单了，因为刚才偶数的情况所有数到最后都变为了 $\frac{n+1}2$，所以如果 $n$ 是奇数，那么 $\frac{n+1}2$ 就是排列的中间一项，我们每次在两边各选 $\frac{m-1}2$ 个，再选中间的一项就好了。如果 $n$ 是偶数，可以手玩几种情况，发现是无解的。

这样我们就分讨完了，注意我们的 $n>1$ 且 $m=1$ 是无解的，$n=m=1$ 时输出 $0$，没了。


```cpp
#include<bits/stdc++.h>
#define N 4005
using namespace std;
int T,n,m;
vector<int>ans[N];
int main(){
	//ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--){
		cin>>n>>m;
		if(n>1&&m==1||n%2==0&&m%2==1)cout<<"-1\n";
		else if(n==1)cout<<"0\n";
		else{
			int l=1,r=n,cnt=0;
			while(1){
				++cnt;
				if(l+m/2-1>=r-m/2+1){
					if(l+m-1<=n)for(int i=l;i<=l+m-1;++i)ans[cnt].push_back(i);
					else if(r-m+1>=1)for(int i=r-m+1;i<=r;++i)ans[cnt].push_back(i);
					else for(int i=1;i<=m;++i)ans[cnt].push_back(i);
					break;
				}
				for(int i=l;i<=l+m/2-1;++i)ans[cnt].push_back(i);
				for(int i=r;i>=r-m/2+1;--i)ans[cnt].push_back(i);
				if(m%2)ans[cnt].push_back(n/2+1);
				l+=m/2;r-=m/2;
			}
			cout<<cnt<<'\n';
			for(int i=1;i<=cnt;++i){
				for(int v:ans[i])cout<<v<<" ";cout<<'\n';
				ans[i].clear();
			}
		}
	}
	return 0;
}

```

---

## 作者：StormWhip (赞：2)

## 思路  
整体的思路是从数列中间开始依次向左右两边修改，这样可以保证每次修改之后修改的元素都会变为整个数列的平均数。注意要分类讨论 $n$ 和 $m$ 的奇偶性来确定修改的起点和重点等一些细节。  
另外要特判以下几点：  
- $n$ 是偶数，$m$ 是奇数时无解，输出 `-1`。
- $m=1$ 时，除非 $n=1$，否则无解，输出 `-1`。
- $m=1$ 且 $n=1$ 时，可以输出 `0`，也可以作出一次修改。

## 代码  

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int T,n,m;
void Solve1()
{
	int mid=(n+1)/2,s=m/2,now=mid+1;
	cout<<ceil(1.0*(n/2)/s)<<"\n";
	while(now+s-1<=n)
	{
		cout<<mid<<" ";
		for(int i=0;i<s;i++) cout<<now+i<<" "<<2*mid-now-i<<" ";
		cout<<"\n";
		now+=s;
	}
	if(now>n) return;
	int lasts=0,p=1;
	for(int i=now;i<=n;i++) cout<<i<<" ",lasts++;
	for(int i=n-now+1;i>=1;i--) cout<<i<<" ",lasts++;
	cout<<mid<<" ";lasts++;
	while(lasts<m)
	{
		cout<<mid-p<<" "<<mid+p<<" ";
		lasts+=2;
		p++;
	}
	cout<<"\n";
}
void Solve2()
{
	int mid=(n+1)/2,s=m/2,now=mid+1;
	cout<<ceil(1.0*(n/2)/s)<<"\n";
	while(now+s-1<=n)
	{
		for(int i=0;i<s;i++) cout<<now+i<<" "<<2*mid-now-i<<" ";
		cout<<"\n";
		now+=s;
	}
	if(now>n) return;
	int lasts=0,p=1;
	for(int i=now;i<=n;i++) cout<<i<<" ",lasts++;
	for(int i=n-now+1;i>=1;i--) cout<<i<<" ",lasts++;
	while(lasts<m)
	{
		cout<<mid-p<<" "<<mid+p<<" ";
		lasts+=2;
		p++;
	}
	cout<<"\n";
}
void Solve3()
{
	int mid=n/2,s=m/2,now=mid+1;
	cout<<ceil(1.0*(n/2)/s)<<"\n";
	while(now+s-1<=n)
	{
		for(int i=0;i<s;i++) cout<<now+i<<" "<<2*mid-now-i+1<<" ";
		cout<<"\n";
		now+=s;
	}
	if(now>n) return;
	int lasts=0,p=1;
	for(int i=now;i<=n;i++) cout<<i<<" ",lasts++;
	for(int i=n-now+1;i>=1;i--) cout<<i<<" ",lasts++;
	while(lasts<m)
	{
		cout<<mid-p+1<<" "<<mid+p<<" ";
		lasts+=2;
		p++;
	}
	cout<<"\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		if(n==1&&m==1) {cout<<"1\n1\n";continue;}
        if(m==1) {cout<<"-1\n";continue;}
		if(n%2==1&&m%2==1) Solve1();
		if(n%2==0&&m%2==1) cout<<"-1\n";
		if(n%2==1&&m%2==0) Solve2();
		if(n%2==0&&m%2==0) Solve3();
	}
	return 0;
}
```

---

## 作者：Vct14 (赞：2)

每次操作总和不变，因此最终序列一定为 $n$ 个原序列的平均数 $\dfrac{n+1}{2}$。那么每次操作选中的数的和一定为 $\dfrac{m(n+1)}{2}$。

若 $n$ 为偶数且 $m$ 为奇数，那么每次操作选中的数的和一定是小数。这显然无法做到，输出 $-1$。

我们知道 $i$ 和 $n-i+1$ 的平均数就是 $\dfrac{n+1}{2}$，所以考虑每次选出一头一尾配对。

若 $n$ 为奇数且 $m$ 为偶数，考虑每次分别从头尾拿出 $\dfrac{m}{2}$ 个进行操作，即每次选出 $i,i+1,\cdots,i+\dfrac{m}{2}-1,n-i+1,n-i,\cdots,n-i-\dfrac{m}{2}+2$ 进行操作。因为正中间的数就是平均数，所以无需操作。

若 $n,m$ 均为偶数同理。

若 $n,m$ 均为奇数，考虑每次操作分别从头尾拿出 $\dfrac{m-1}{2}$ 个进行操作，再带上正中间的平均数。

注意特判 $m=1$ 的情况。此时若 $n=1$ 则无需操作输出 $0$，否则无解。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		if(n%2==0 && m%2==1){
			cout<<"-1\n";
			continue;
		}
		else if(n%2==1 && m%2==0){
			cout<<n/2-m/2+2<<"\n";
			for(int i=1; i<=n/2-m/2+1; i++){
				for(int j=i; j<=i+m/2-1; j++) cout<<j<<" "<<n-j+1<<" ";
				cout<<"\n";
			}
			for(int i=1; i<=(m-1)/2; i++) cout<<i<<" "<<n-i+1<<" ";cout<<(m-1)/2+1<<" "<<n/2+1<<"\n";
		}
		else if(n%2){
			cout<<n/2-m/2+1<<"\n";
			for(int i=1; i<=n/2-m/2+1; i++){
				for(int j=i; j<=i+m/2-1; j++) cout<<j<<" "<<n-j+1<<" ";
				cout<<n/2+1<<"\n";
			}
		}
		else{
			cout<<n/2-m/2+1<<"\n";
			for(int i=1; i<=n/2-m/2+1; i++){
				for(int j=i; j<=i+m/2-1; j++) cout<<j<<" "<<n-j+1<<" ";
				cout<<"\n";
			}
		}
	}
	return 0;
}
```

这份代码可以进行优化。即，尽量不重复操作，每次选择 $i,i+1,\cdots,i+\dfrac{m}{2}-1,n-i+1,n-i,\cdots,n-i-\dfrac{m}{2}+2$ 操作后 $i$ 加上 $\left\lfloor\dfrac{m}{2}\right\rfloor$ 再操作。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;cin>>t;
	while(t--){
		int n,m;cin>>n>>m;
		if(n%2==0 && m%2==1){
			cout<<"-1\n";
			continue;
		}
		else if(m==1){
			if(n==1) cout<<"0\n";
			else cout<<"-1\n";
			continue;
		}
		else if(n%2==1 && m%2==0){
			int ans=(n/2-m/2+1)/(m/2);
			if((n/2-m/2+1)%(m/2)) ans++;
			if((n-1)%m) cout<<ans+1<<"\n";
			else cout<<ans<<"\n";
			int k=1;
			for(int i=1; i<=n/2-m/2+1; i+=m/2){
				for(int j=i; j<=i+m/2-1; j++) cout<<j<<" "<<n-j+1<<" ";
				cout<<"\n";
				k=i+m/2;
			}
			if((n-1)%m){
				for(int i=k; i<=n-k+1; i++) cout<<i<<" ";
				for(int i=1; i<=(m-(n-2*k+2))/2; i++) cout<<i<<" "<<n-i+1<<" ";cout<<(m-(n-2*k+2))/2+1<<"\n";
			}
		}
		else if(n%2){
			int ans=(n/2-m/2+1)/(m/2);
			if((n/2-m/2+1)%(m/2)) ans++;
			if((n-1)%(m-1)) cout<<ans+1<<"\n";
			else cout<<ans<<"\n";
			int k=1;
			for(int i=1; i<=n/2-m/2+1; i+=m/2){
				for(int j=i; j<=i+m/2-1; j++) cout<<j<<" "<<n-j+1<<" ";
				cout<<n/2+1<<"\n";
				k=i+m/2;
			}
			if((n-1)%(m-1)){
				for(int i=k; i<=n-k+1; i++) cout<<i<<" ";
				for(int i=1; i<=(m-(n-2*k+2))/2; i++) cout<<i<<" "<<n-i+1<<" ";cout<<"\n";
			}
		}
		else{
			int ans=(n/2-m/2+1)/(m/2);
			if((n/2-m/2+1)%(m/2)) ans++;
			if(n%m) cout<<ans+1<<"\n";
			else cout<<ans<<"\n";
			int k=1;
			for(int i=1; i<=n/2-m/2+1; i+=m/2){
				for(int j=i; j<=i+m/2-1; j++) cout<<j<<" "<<n-j+1<<" ";
				cout<<"\n";
				k=i+m/2;
			}
			if(n%m){
				for(int i=k; i<=n-k+1; i++) cout<<i<<" ";
				for(int i=1; i<=(m-(n-2*k+2))/2; i++) cout<<i<<" "<<n-i+1<<" ";cout<<"\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：ran_qwq (赞：1)

$n\ne1$ 且 $m=1$ 时操作不了，无解。

$n\bmod2=0$ 且 $m\bmod2=1$ 时加不出平均数，最后一次操作不是平均数，无解。

其他情况如果每次操作的位置都是对称的，那么把所有位置都操作一遍就能使所有数相等，这是容易归纳证明的。

接着乱构造都行，$m\bmod2=0$ 可以直接对称构造。如果 $m\bmod2=1$ 则取中间的数，剩下对称构造。

```cpp
void QwQ() {
	int n=rd(),m=rd();
	if(n==1&&m==1) return puts("0"),void();
	if(m==1||!(n&1)&&(m&1)) return puts("-1"),void();
	vector<vi> as;
	if(m&1) {
		int x=m/2,y=n/2/x;
		for(int i=1,l=x,r=n-x+1;i<=y;i++,l+=x,r-=x) {
			vi v={n/2+1};
			for(int j=l-x+1;j<=l;j++) v.pb(j);
			for(int j=r;j<=r+x-1;j++) v.pb(j);
			as.pb(v);
		}
		vi v;
		for(int i=n/2+1-x;i<=n/2+1+x;i++) v.pb(i);
		as.pb(v);
	} else if(!(n&1)) {
		int x=m/2,y=n/2/x;
		for(int i=1,l=x,r=n-x+1;i<=y;i++,l+=x,r-=x) {
			vi v;
			for(int j=l-x+1;j<=l;j++) v.pb(j);
			for(int j=r;j<=r+x-1;j++) v.pb(j);
			as.pb(v);
		}
		vi v;
		for(int i=n/2-x+1;i<=n/2+x;i++) v.pb(i);
		as.pb(v);
	} else {
		int x=m/2,y=n/2/x;
		for(int i=1,l=x,r=n-x+1;i<=y;i++,l+=x,r-=x) {
			vi v;
			for(int j=l-x+1;j<=l;j++) v.pb(j);
			for(int j=r;j<=r+x-1;j++) v.pb(j);
			as.pb(v);
		}
		vi v;
		for(int i=n/2-x+1;i<=n/2+1+x;i++) if(i!=n/2+1) v.pb(i);
		as.pb(v);
	}
	wr(as.size(),"\n");
	for(vi v:as) {
		for(int x:v) wr(x," ");
		puts("");
	}
}
```

---

## 作者：the_Short_Path (赞：0)

对于 $n$ 和 $m$ 的奇偶性分类讨论：
+ $n=1$，输出 $0$；
+ $m=1$ 且 $n\neq1$，输出 $-1$；
+ $m$ 为偶数时，每次操作取左右两端各 $\frac{m}{2}$ 个；
+ $n$ 和 $m$ 都为奇数时，每次操作取中间和左右两端各 $\frac{m}{2}$ 个；
+ $n$ 为偶数且 $m$ 为奇数是，无解。

具体操作看代码的实现。
# Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        if (n == 1) puts("0");
        else if (m == 1) puts("-1");
        else if (n % 2 == 0 && m % 2) puts("-1");
        // 以上均为特判
        else if (n % 2 && m % 2) {
            m--;// 记得 -1
            cout << (n - 1 + m - 1) / m << "\n";
            for (int i = n / 2; i >= m / 2; i -= m / 2) {
                for (int j = i - m / 2 + 1; j <= i; j++) cout << j << " ";
                cout << n / 2 + 1 << " ";
                for (int j = n - i + 1; j <= n - i + m / 2; j++) cout << j << " ";
                puts("");
            }
            if ((n - 1) % m) {
                for (int i = 1; i <= m / 2; i++) cout << i << " ";
                cout << n / 2 + 1 << " ";
                for (int i = n - m / 2 + 1; i <= n; i++) cout << i << " ";
            }
        } else if (n % 2 && !(m % 2)) {
            cout << (n - 1 + m - 1) / m << "\n";
            for (int i = n / 2; i >= m / 2; i -= m / 2) {
                for (int j = i - m / 2 + 1; j <= i; j++) cout << j << " ";
                for (int j = n - i + 1; j <= n - i + m / 2; j++) cout << j << " ";
                puts("");
            }
            if ((n - 1) % m) {
                for (int i = 1; i <= m / 2; i++) cout << i << " ";
                for (int i = n - m / 2 + 1; i <= n; i++) cout << i << " ";
            }
        } else {
            cout << (n + m - 1) / m << "\n";
            for (int i = n / 2; i >= m / 2; i -= m / 2) {
                for (int j = i - m / 2 + 1; j <= i; j++) cout << j << " ";
                for (int j = n - i + 1; j <= n - i + 1 + m / 2 - 1; j++) cout << j << " ";
                puts("");
            }
            if (n % m) {
                for (int i = 1; i <= m / 2; i++) cout << i << " ";
                for (int i = n - m / 2 + 1; i <= n; i++) cout << i << " ";
                puts("");
            }
        }
    }
    return 0;
}
```

---

## 作者：LittleAcbg (赞：0)

## 初步分析

这题不需要最小化操作次数，就比较简单了。

容易发现操作不会改变所有数的和，所以最后所有数都是初始平均数，也就是 $\dfrac{1+n}2$。

Subtask 里面有关于 $n,m$ 奇偶性的特殊性质，所以我们能够想到对 $n,m$ 奇偶性分类讨论。

## $m$ 为偶数

对 $1\sim n$ 两两分组，$(1,n)$ 一组，$(2,n-1)$ 一组……最后一组是 $\left(\left\lfloor\dfrac n2\right\rfloor,n-\left\lfloor\dfrac n2\right\rfloor\right)$。这些组依次编号 $1,2,\dots,\left\lfloor\dfrac n2\right\rfloor$。

我们发现取 $m$ 个元素就可以取其中 $\dfrac m2$ 组。由于不需要最小化操作次数，我们直接依次取：

- 组 $1,2,\dots,\frac m2$
- 组 $1,2,\dots,\frac m2-1,\frac m2+1$
- 组 $1,2,\dots,\frac m2-1,\frac m2+2$
- $\dots$
- 组 $1,2,\dots,\frac m2-1,\left\lfloor\frac n2\right\rfloor$

共取 $\left\lfloor\dfrac{n-m}2\right\rfloor+1$ 次。

实现：

```cpp
cout << (n - m) / 2 + 1 << endl; // 取的次数
for (int k = 1; k <= (n - m) / 2 + 1; ++k) // 循环，每次取一组
{
    for (int i = 1; i < m / 2; ++i) cout << i << ' '; // 组 1,2,...,m/2-1 的前一项
    cout << m / 2 - 1 + k << ' ' << n - m / 2 + 2 - k; // 中间一组
    for (int i = n - m / 2 + 2; i <= n; ++i) cout << ' ' << i; // 组 1,2,...,m/2-1 的后一项
    cout << endl; // 记得换行
}
```

## $m$ 为奇数

### $m=1$ 的特殊情况

这个比较好解决。$n=1$ 时不用操作（输出一个 $0$），$n\ne1$ 时无解。

```cpp
if (m == 1) puts(n == 1 ? "0" : "-1");
```

### $m\ge3$ 的一般情况

先考虑 $n$ 为奇数的情况。此时类似于输入 $(n,m-1)$ 的情况，只不过我们每次多选一个正中间的数。

```cpp
/* 代码和 m 为偶数基本一样
由于 n 为奇数，(n - m) / 2 + 1 和 m / 2 值也都不变
所以只需要多加一个 n / 2 + 1（1~n 中位数）即可
*/
cout << (n - m) / 2 + 1 << endl;
for (int k = 1; k <= (n - m) / 2 + 1; ++k)
{
    for (int i = 1; i < m / 2; ++i) cout << i << ' ';
    cout << m / 2 - 1 + k << ' ' << n / 2 + 1 << ' ' << n - m / 2 + 2 - k; // 多一个 n / 2 + 1（正中间）
    for (int i = n - m / 2 + 2; i <= n; ++i) cout << ' ' << i;
    cout << endl;
}
```

再看 $n$ 为偶数的情况，没办法选一个正中间的数，可以发现这种情况无解。

题目比较简单，上面也提供了许多局部代码，整个代码就不放了。

---

