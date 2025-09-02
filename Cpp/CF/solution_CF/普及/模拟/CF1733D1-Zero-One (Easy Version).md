# Zero-One (Easy Version)

## 题目描述

两个长度为 $n$ 的二进制字符串 $a$ 和 $b$。你可以进行如下操作若干次（可以为0次）：

- 选两个数 $l$ 和 $r\ $ $(\ l\ <\ r\ )$，对 $a_l$、$a_r$ 取反
- 如果 $l+1=r$，代价为 $x$。否则，代价为 $y$。

## 样例 #1

### 输入

```
4
5 8 7
01001
00101
5 7 2
01000
11011
7 8 3
0111001
0100001
5 10 1
01100
01100```

### 输出

```
8
-1
6
0```

# 题解

## 作者：zhlzt (赞：2)

### 题解

Easy Version 保证了 $x\ge y$。

设满足 $a_i\oplus b_i=1$ 的 $i$ 有 $cnt$ 个。那么题目变为经过多次操作直到 $cnt=0$ 的最小代价。

易知 $cnt\equiv1\pmod 2$ 时无解（因为操作不会改变 $cnt$ 的奇偶性），输出 `-1`。

否则 $cnt\equiv0\pmod 2$，记 $dif_j$ 为第 $j$ 个满足 $a_i\oplus b_i=1$ 的 $i$，分类讨论：

- $cnt=0$，不需要任何操作。

- $cnt=2 \land |dif_1-dif_2|=1$，最小代价为 $\min\{x,2y\}$。由于 $n\ge 5$，所以总是可以通过 $2$ 次 $y$ 操作达到 $1$ 次 $x$ 操作的效果。

- $cnt=2 \land |dif_1-dif_2|>1$，最小代价为 $\min\{y,|dif_1-dif_2|\times x\}$。

- $cnt\ge 4$，总是存在一种组队方式使得只需要使用 $\dfrac{cnt}{2}$ 次 $y$ 操作，最小代价为 $\dfrac{cnt\times y}{2}$。

那么这题的 Easy Version 就搞定了，时间复杂度 $O(n)$。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5e5+10;
char str1[maxn],str2[maxn];
int val[maxn],dif[maxn];
//ll dp[maxn];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		ll wx,wy;cin>>wx>>wy;
		cin>>str1>>str2;
		int cnt=0; 
		for(int i=0;i<n;i++){
			val[i+1]=(str1[i]==str2[i])?0:1;
			if(val[i+1]) dif[++cnt]=i+1;
		}
		if(cnt&1){cout<<"-1\n"; continue;}
		if(wx>=wy){
			if(cnt==2){
				if(dif[1]==dif[2]-1) 
					cout<<min(wx,2*wy)<<'\n';
				else cout<<wy<<'\n';
			} 
			else cout<<wy*cnt/2<<'\n';
			continue;
		}
//		dp[1]=wy;
//		for(int i=2;i<=cnt;i++){
//			ll val1=dp[i-2]+2*wx*(dif[i]-dif[i-1]);
//			ll val2=dp[i-1]+wy;
//			dp[i]=min(val1,val2);
//		}
//		cout<<dp[cnt]/2<<'\n';
	}
	return 0;
}
```

---

## 作者：SMall_X_ (赞：2)

[原题传送门](https://www.luogu.com.cn/problem/CF1733D1)

---
## 题目大意

给定两个长度为 $n$ 的二进制字符串 $a$ 和 $b$，你可以进行若干次操作，对于每次操作：

- 选两个数 $l$ 和 $r$，且 $l<r$，将 $a_l$ 和 $a_r$ 交换。
- 如果选取的 $l$ 和 $r$ 相邻，代价为 $x$，否则为 $y$。

保证 $y≤x$，求出最小代价使得 $a=b$，若不能使 $a=b$，输出 `-1`。

## 思路分析

贪心，很简单的一个分类讨论。

首先，根据 $y≤x$，要使得代价最小，尽量不交换相邻的。

记 $a$ 和 $b$ 不相同字符个数为 $cnt$，分为以下几种情况：

- 当 $cnt$ 是奇数，无论怎么交换，都不能使 $a=b$，输出 `-1`。

- 否则，继续判断，特判若 $cnt=0$，即一开始 $a=b$，输出 `0`。

- 尽量让交换的两个数不相邻，所以若 $cnt>2$，则选择都不相邻的两个进行交换，进行 $\frac{cnt}{2}$ 次不相邻交换，代价即为 $\frac{cnt \cdot y}{2}$。

- 还有一种，当 $cnt=2$，就需要判断是否相邻了：不相邻则输出 $y$；相邻，则考虑进行一次代价为 $x$ 的交换，或两次代价为 $y$ 的交换（另外找一个字符进行交换），求两种哪种最优，即 $\min(x,2y)$。

因为 $y≤x≤10^9$，交换次数越多，可能会爆 `int`，要开 `long long`。

最后记得加上换行。

代码：
```cpp
/*Written by smx*/
#include<bits/stdc++.h>
using namespace std;
int num[3005];
int main() 
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin>>t;
	while(t--)
	{
		long long len,x,y,cnt=0;
		string a,b;
		cin>>len>>x>>y>>a>>b;
		for(int i=0;i<len;i++)
		{
			if(a[i]!=b[i])
			{
				num[++cnt]=i;
			}
		}
		if(cnt%2==1)
		{
			cout<<"-1\n";
		}
		else 
		{
			if(cnt==0)
			{
				cout<<"0\n";
			}
			else if(cnt==2)
			{
				if(num[1]+1!=num[2])
				{
					cout<<y<<"\n";
				}
				else
				{
					cout<<min(x,2*y)<<"\n";
				}
			}
			else
			{
				cout<<cnt/2*y<<"\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：Wi_Fi (赞：2)

很简单的贪心分类讨论。

题目已经说了 $y \le x$，所以尽量选择不相邻的。  
下文令不相同的数量为 $sum$。

1. $sum$ 为奇数时

很显然我们无论如何只能改变偶数个数，所以无解。

2. $sum$ 偶数时

- 如果 $sum$ 为 $0$，则输出 $0$。
- 如果 $sum$ 为 $2$，那么判断两个数位置情况：如果不相邻直接输出 $y$；如果相邻可以直接输出 $x$，也可以将第三个数反转两次，即 $2y$，所以输出 $\min(x,2y)$。
- 不然的话，剩下的数两两匹配，必然有让它们每组全部不相邻的方法，输出 $sum \div 2 \times y$。

```
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
long long T,i,n,x,y,sum,q[N];
string a,b;
int main()
{
	cin>>T;
	while(T--)
	{
		sum=0;
		cin>>n>>x>>y>>a>>b;
		for(i=0;i<n;i++)if(a[i]!=b[i])q[++sum]=i;
		if(sum%2)cout<<"-1\n";
		else if(!sum)cout<<"0\n";
		else if(sum==2)
		{
			if(q[1]+1!=q[2])cout<<y<<"\n";
			else cout<<min(x,2*y)<<"\n";
		}
		else cout<<sum/2*y<<"\n";
	}
	return 0;
}
```


---

## 作者：atomic_int (赞：1)

## 题意：
题目翻译中已有。

## 分析：
- $a=b$ 代价为 $0$。
- 设 $a$ 与 $b$ 不同的个数为 $k$。$k$ 为奇数无法将 $a$ 变成 $b$。
- 对于 $k > 2$，每隔一个进行取反，代价为 $\frac{k}{2} \cdot y$。
- 对于 $k \leq 2$：
	- 如果两个不同的数是相连的，要么互相取反要么选择另一个位置进行取反，也就是说代价为 $\min \{ x,2y \}$。
    - 代价为 $x$。
    
## 代码：
```cpp
inline void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    string a, b;
    cin >> a >> b;
    if (a == b) {
        cout << 0 << '\n';
        return ;
    }
    vector<int> d;
    for (int i = 0; i < n; i ++) {
        if (a[i] != b[i])   d.push_back(i);
    }
    if (d.size() & 1) {
        cout << "-1\n";
        return ;
    }
    if (d.size() > 2) {
        cout << d.size() / 2 * y << '\n';
    }
    else {
        if (d[0] + 1 == d[1]) {
            cout << min(x, y * 2) << '\n';
        }
        else {
            cout << y << '\n';
        }
    }
}
```

---

## 作者：Iamzzr (赞：1)

简单贪心 + 分类讨论。

首先要找出有多少个不同的数字。显然如果有奇数个，那么肯定无解。

一旦不同的个数超过 $2$ 个，那么我们肯定有一种这样的方案：$1$ 跟 $3$，$2$ 跟 $4$，依次类推。

而这样做的花费，每次是 $y$，题目已经保证 $y \le x$，所以这样操作一定是最优的。

如果不同的个数正好是 $2$ 个，则需要进行特判。

如果这两个不同的数连在一块，答案为 $\min(x, 2 \times y)$，否则答案为 $y$。当然了，如果总长度只有 $2$，那么答案就只能为 $x$。

AC 代码：

```cpp
#include <iostream>

using namespace std;

const int N = 3010;
#define int long long

int T;
int a[N];

signed main() {
    cin >> T;
    while (T--) {
        int n, x, y; cin >> n >> x >> y;
        string a, b; getline(cin, a);
        getline(cin, a), getline(cin, b);
        int cnt = 0;
        for (int i = 0; i < n; i++)
            if (a[i] != b[i]) cnt++;
        //cout << cnt << endl;
        if (cnt % 2) {
            cout << -1 << endl;
            continue;
        }
        if (cnt == 2) {
            bool flag = false;
            for (int i = 0; i < n - 1; i++)
                if (a[i] != b[i] && a[i + 1] != b[i + 1]) {
                    flag = true;
                    break;
                }
            if (flag) {
                if (n == 2) cout << x << endl;
                else cout << min(x, 2 * y) << endl;
                continue;
            }
            cout << y << endl;
            continue;
        }
        cout << (cnt / 2) * y << endl;
    }
    return 0;
}

```

---

## 作者：我梦见一片焦土 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1733D1)

---

# 思路：
因为每次操作都是两个位置同时取反，所以我们先统计满足 $s1_i$ 不等于 $s2_i$ 的 $i$ 的数量 $cnt$，如果为奇数，则无法使两个字符串相同,然后只要 $cnt$ 不等于 $2$，那么我们一定可以对每个不匹配的位置都找到一个不相邻的不匹配的位置，两个位置同时取反，消耗为 $y$，最小的花费为$cnt \div2\times y$，当 $cnt=2$ 时，且如果两个不匹配的位置相邻，那么我们可以将这两个位置取反，或者找到另一个位置，使这两个不匹配的位置分别与这个位置取反，最小费用为 $2y$ 和 $x$ 的最小值，如果两个不匹配的位置不相邻，最小费用为 $y$。

代码如下：
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e6+10;
const int INF=0x3f3f3f3f;
int read(){
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
void write(int x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9){
        write(x/10);
    }
    putchar(x%10+'0');
    return;
}
int t,n,x,y;
string s1,s2;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>x>>y>>s1>>s2;
		int cnt=0,cnt2=0,ans=0;
		for(int i=0;i<n;i++){
			if(s1[i]!=s2[i]){
				cnt++;
			}			
		}
		for(int i=0;i<n;i++){
			if(i!=0&&s1[i]!=s2[i]&&s1[i-1]!=s2[i-1]){
				cnt2++;
				i++;
			}
		}
		if(cnt&1){
			cout<<-1<<endl;
			continue;
		}
		if(cnt==2&&cnt2==1){
			ans=min(x,2*y);
		}else{
			ans=cnt/2*y;
		}
		cout<<ans<<endl;
	}
	return 0;
}
```
完结撒花~

---

## 作者：xiazha (赞：0)

好题！

让我们思考以下 ```easy ver``` 的作用，然后想到了分讨。

首先将所有 $s_i\ne t_i$ 的下标 $i$ 组成长为 $c$ 的序列 $a$。

特别的，若 $c$ 为奇数，输出 ```-1```。

- $y\le x$

贪心的，当 $c\le 2$ 且 $a_1+1=a_2$ 时，我们想不用相邻交换就必须用另一个点作为中转点，将中转点翻两次，注意到 $n\ge 5$，所以我们一定能找到一个不相邻的中转点，答案为 $\min(x,2y)$。否则一定可以将所有下标两两配对且不相邻，答案为 $c/2\times y$。

- $y > x$

考虑 dp。

设 $dp_i$ 为将前 $i$ 个下标都修改为与 $t$ 相等最小花费。

那么若选相邻的，则将 $a_i$ 与 $a_{i-1}$ 一组，需要交换 $a_i-a_{i-1}$ 次，方程为 $dp_i=dp_{i-2}+(a_i-a_{i-1})\times x$。

若不选相邻的，则我们将 $y$ 的贡献均匀拆成两个 $y/2$，$dp_i=dp_{i-1}+y/2$。

将上述两个取最小值即可。

还有两个提示：

第一，将 dp 过程中的值全部乘 $2$，最终再除 $2$ 防止小数出现。

第二，你可能会不理解 $y/2$ 会不会没有与他匹配的另一半，根据转移方程，你会发现选择 $y/2$ 一定是偶数次，因为另一种操作每次都会加上两个数，而 $c$ 也是偶数，故方程是正确的。

时间复杂度 $O(n)。$

---

## 作者：caotianhao (赞：0)

# 题外话
1. 好久没上谷了，赶紧水两篇题解加下社贡（逃；
2. 怎么又是 $01$ 串啊（恼。
# 题目大意
两个长度为 $n$ 的二进制字符串 $a$ 和 $b$。你可以进行如下操作若干次：
- 选两个数 $l$ 和 $r\ $ $(\ l\ <\ r\ )$，对 $a_l$、$a_r$ 取反
- 如果 $l+1=r$，代价为 $x$。否则，代价为 $y$。  
求把 $a$ 变成 $b$ 的最小代价。
# 解题思路
**注：以下简称 `a 和 b 不同的字符` 为 `不同的字符`**
## I 无解：
由于我们每次只能改变 $2$ 个数，所以我们统计不同的字符的个数，若为奇数，那么必然无解，打个比方：我们有 $3$ 个不同的字符，那么我们进行一次操作后，不同的字符的个数必然为 $1$，$3$ 或 $5$，那么可得：如果原来有奇数个不同的字符，不论进行多少次操作，最后不同的字符个数都是奇数，不可能为 $0$，因此无解。
## II $0$ 或 $2$ 个不同字符：
$0$ 个不同的字符自然没有代价，如果是 $2$ 个不同的字符，就要分类讨论。
### $2$ 个字符不相邻：
这种情况很简单，代价就是 $y$。
### $2$ 个字符相邻：
如果你认为这种情况输出 $x$，那就错了，因为我们可以拉一个与这 $2$ 个字符都不相邻的“垫背字符”，然后用 $2y$ 的代价解决，所以这种情况的答案应该是 $\min(x,2y)$。
## III $2$ 个以上不同字符：
这种情况，由于我们一定能找到一种方法，让每次操作的 $2$ 个数不相邻，所以直接输出操作次数 $\times y$。
# ACcode
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开longlong见祖宗
int t;
signed main(){
	cin>>t;
	while(t--){
		int n,x,y;
		string a,b;
		cin>>n>>x>>y;
		cin>>a>>b;
		int num=0;
		for(int i=0;i<n;i++){
			if(a[i]!=b[i]){
				num++;
			}
		}
		if(num%2==1){
			cout<<-1<<"\n";
			continue;
		}
		x=min(x,2*y);
		if(num==0){
			cout<<0<<"\n";
		}else if(num==2){
			for(int i=0;i<n;i++){
				if(a[i]!=b[i]){
					if(a[i+1]!=b[i+1]){
						cout<<x<<"\n";
					}else{
						cout<<y<<"\n";
					}
					break;
				}	
			}
		}else{
			cout<<(num/2)*y<<"\n";
		}
	}
	return 0;
}
```

---

## 作者：Chenyichen0420 (赞：0)

# 简要题意

每次改变两个比特位的值，使得原比特串 $a$ 变为新比特串 $b$。其中，每次变换需要耗费一定的代价。其具体的代价为：若两位相邻，则代价为 $x$，否则代价为 $y$，且保证 $y\leq x$。

# 思路分析

首先判断无解。因为每次一定会变换两个，所以如果比特位不同的位有奇数个，那么一定无解，否则一定有解。

对于有解的，如果不同位的个数为 $0$，那么直接输出 $0$。如果不同位的个数为 $2$ 且这两位是相邻的，那么在 $x$ 和 $2\times y$ 之间取最小值（毕竟可以找一个中介分别变换吗）输出。其余情况则输出不同位个数 $\div2\times y$，毕竟题目保证了 $y\leq x$，即不相邻的情况下直接交换一定比挨个交换更优。

按照上述思路模拟一遍就可以通过这道题了。代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,x,y,pos[5001],cnt; char a[5001],b[5001];
inline int read(){
    register int r=0; register char c=getchar();
    while(c<'0' || c>'9') c=getchar();
    while(c>='0' && c<='9') r=(r<<3)+(r<<1)+(c^48),c=getchar();
    return r;
}
signed main(){
    t=read();
    while(t--){
        n=read(); x=read(); y=read();
        for(int i=1;i<=n;++i) a[i]=getchar();
        getchar(); cnt=0;
        for(register int i=1;i<=n;++i) b[i]=getchar();
        for(register int i=1;i<=n;++i)
            if(a[i]^b[i]) pos[++cnt]=i;
        if(cnt&1){
            putchar('-');
            putchar('1');
            putchar('\n');
            continue;
        }
        if(!cnt){
            putchar('0');
            putchar('\n');
            continue;
        }
        if(cnt!=2||pos[1]+1!=pos[2]) cout<<cnt/2*y,putchar('\n');
        else cout<<min(2*y,x),putchar('\n');
    }
}
```

---

## 作者：Hisaishi_Kanade (赞：0)

首先考虑直接找到所有 $a_i\not = b_i$ 的 $i$ 的点集，按照升序排序得到 $p_1,\cdots,p_k$。

容易证明无论如何操作 $k$ 的奇偶性不变，则可以使得 $k\to0$ 的充要条件是 $k\equiv 0\ (\bmod\ 2)$。

然后考虑如何处理。因为 $y\le x$，所以能一次 $y$ 绝不使用 $x$。

那么如果 $k>2$ 则可以两两配对使得价值为 $\dfrac {ky} 2$。

当 $k=2$ 且这两个点相邻时，这时候挑一个已经匹配的操作两次 $y$，或者使用 $x$。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for(i=l; i<=r; ++i)
#define req(i, r, l) for(i=r; i>=l; --i)
using namespace std;
const int N=5005;
char u[N], v[N]; int t, i, n, x, y, tot;
int p[N];
inline void solveez()//y<=x
{
	tot=0;
	rep(i, 1, n) if(u[i]!=v[i]) p[++tot]=i;
	if(tot&1) puts("-1");
	else if(tot==2 && p[1]==p[2]-1) printf("%d\n", min(x, y<<1));
	else printf("%lld\n", 1ll*(tot>>1)*y);
	return ;
}
inline void solvehd(){}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %d %d %s %s", &n, &x, &y, u+1, v+1);
		if(y<=x) solveez();
		else solvehd();
	}
	return 0;
}
```

---

## 作者：aimcf (赞：0)

设不同的位置数量为 $w$。

如果 $w\bmod 2 = 1$，由于一次更新会同时更新两个位置，所以无解。

否则必然有解。

由于 $x>y$，那么可以贪心的选择不相邻的两个位置进行操作。

如果 $w=0$，那么不需要进行任何操作。

如果 $w>2$，那么全部使用不相邻的两个位置进行操作即可。

否则，如果两个不同的位置相邻，可以选择一次相邻操作完成，由于 $n\le 5$，所以也必然可以选择两次不相邻操作完成；否则只需要花费一次不相邻的操作即可。

时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

int compare(string codingfun, string codeforces)
{
  int AC = 0;
  for (int i = 0; i < codingfun.size(); i ++)
    if (codingfun[i] != codeforces[i])
      AC ++;
  return AC;
}

bool close(string s1, string s2)
{
  for (int i = 1; i < s1.size(); i ++)
    if (s1[i] != s2[i] && s1[i - 1] != s2[i - 1])
      return true;
  return false;
}

signed main()
{
  int T;
  cin >> T;
  while (T --)
  {
    int n, x, y;
    cin >> n >> x >> y;
    int npy = 0;
    string s1, s2;
    cin >> s1 >> s2;
    npy = compare(s1, s2);
    if (npy == 0)
      cout << "0\n";
    else if (npy & 1)
      cout << "-1\n";
    else if (npy > 2)
      cout << y * (npy / 2) << '\n';
    else if (close(s1, s2))
      cout << min(2 * y, x) << '\n';
    else
      cout << y << '\n';
  }
  return 0;
}

```

[AC](https://www.luogu.com.cn/record/89677230)

---

## 作者：linjinkun (赞：0)

~~连我这种贪心弱智之人都过了，还有谁过不了？~~

简单贪心，貌似这数据范围……有点小了。

分类讨论，由于题目保证 $y \le x$，那么我们要尽量使每一次操作都不要相邻，那么我们记 $ans = \sum_{i = 1}^n[a_i \not = b_i]$。如果 $ans$ 是奇数，那么一定无解，因为每次操作都会将两个交换，奇数个无法交换，当 $ans = 2$ 时，又分两种情况，如果这两个位置不相邻，那么直接输出 $y$，如果这两个位置相邻，那么答案为 $\min(y \times 2,x)$，因为可以拿另外一个位置当中转站，连续交换两次，那个当中转站的位置不会受到影响，而原本的两个位置又会变成 $b_i$，也满足了题目将 $a$ 变成 $b$ 的要求。接着，当 $ans \not = 2$ 时，那么就只能老老实实得做 $ans \div 2$，次操作了，由于我们可以通过安排顺序使得每一次操作都不相邻，所以说得分就是 $ans \div 2 \times y$。

**注意：要开 ```long long```，当 $a = b$ 时直接输出 $0$。**

代码（比题解还短）：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int s[3005];
signed main()
{
	int t;
	scanf("%lld",&t);
	while(t--)
	{
		string a,b;
		int n,x,y;
		scanf("%lld %lld %lld",&n,&x,&y);
		cin >> a >> b;
		if(a == b)
		{
			printf("0\n");
			continue;
		}
		int k = 0;
		for(int i = 0;i<n;i++)
		{
			if(a[i]!=b[i])
			{
				s[++k] = i;
			}
		}
		if(k%2 == 1)
		{
			printf("-1\n");
			continue;
		}
		if(k == 2)
		{
			if(s[1]+1 == s[2])
			{
				printf("%lld\n",min(y*2,x));
			}
			else
			{
				printf("%lld\n",y);
			}
		}
		else
		{
			printf("%lld\n",k/2*y);
		}
	}
	return 0;
}
```

---

## 作者：wth2026 (赞：0)

# 题目大意
有两个长度为 $n$ 的 $01$ 串，每次选取第一个串的两个位置取反，如果选取的两个位置相邻，则代价为 $x$，否则代价为 $y$。求将第一个串变成第二个的最小代价。
# 题目思路
读入的时候记录一下一共有几个不一样。

如果有奇数个，那么就无解，直接输出无解搞定。

否则，如果有偶数个：

如果只有两个，且两个相邻，那么就输出最小的交换两个的代价（及如果 $n \ge 5$，那么要判断一下是两倍的 $y$ 大，还是 $x$ 大）。

如果有大于两个不同，就直接输出个数 $\times \, y$ 的一半。
# AC Code
```cpp
#include <bits/stdc++.h>

#define endl '\n'
#define int long long
#define inf 0x3f3f3f3f

#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Os")
#pragma GCC optimize("Ofast")

using namespace std;

const int N = 3000;
int n, x, y, T, sum = 0;
char c;
bool _[N + 5], a[N + 5], q;

void init() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
}

signed main() {
	init();
	cin >> T;
	
	while (T --) {
		sum = 0;
		q = false;
		cin >> n >> x >> y;
		
		for (int i = 1; i <= n; ++ i) {
			a[i] = _[i] = 0;
		}
		
		if (x > (2 * y) && n > 4) {
			x = 2 * y;
		}
		
		for (int i = 1; i <= n; ++ i) {
			cin >> c;
			_[i] = (c ^ 48);
		}
		
		for (int i = 1; i <= n; ++ i) {
			cin >> c;
			a[i] = (c ^ 48) ^ _[i];
			
			if (a[i]) {
				++ sum;
				
				if (a[i - 1]) {
					q = true;
				}
			}
		}
		
		if (sum % 2 != 0) {
			cout << "-1\n";
			continue;
		}
		
		if (sum == 2 && q) {
			cout << x << endl;
		} else {
			cout << (sum * y / 2) << endl;
		}
	}
	
	return 0;
}
```

---

## 作者：xzz_0611 (赞：0)

[题目传送门](/problem/CF1733D1)
# 分析
明显的贪心题。

这道题我们只要知道 $a$、$b$ 两个字符串不同的字符的个数（后面用 $cnt$ 代替）就可以解题了。

对于 $cnt$ 的不同的值，会有以下 $4$ 种情况：
- $cnt=0$
- $cnt$ 是奇数
- $cnt=2$
- $cnt\ge3$

这 $4$ 种情况又分别对应着以下 $4$ 种答案：
- $0$，应为此时 $a$ 与 $b$ 初始就相等了
- $-1$，应为当 $cnt$ 为奇数时，无论操作多少次，$a$ 与 $b$ 都不可能相等
- $x$、$y$ 或 $2\times y$，此时有两种情况：
	- 两个不同的字符不相邻：直接交换，代价为 $y$
   - 两个不同的字符相邻：有两种情况：
	   - 直接交换：代价为 $x$
	   - 分别与一个相同的字符进行交换：代价为 $2\times y$
- $\displaystyle\frac{cnt\times y}{2}$，应为根据题目可知 $x\ge y$，所以要尽量选择不相邻的两个字符取反；由于每次取反是取反两个字符，所以要去反 $\displaystyle\frac{cnt}{2}$ 次，而每次要消耗的代价为 $y$，故总代价为 $\displaystyle\frac{cnt\times y}{2}$

所以只需要判断 $cnt$ 属于以上那种情况再进行对应的操作即可。

**注意：要开 `long long`！**
# code
```cpp
#include<iostream>
#define ll long long
using namespace std;
int loction[3005],t;
int main() {
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--) {
		ll len,x,y,cnt=0;
		string a,b;
		cin>>len>>x>>y>>a>>b;
		for(int i=0;i<len;i++) if(a[i]!=b[i]) loction[++cnt]=i;//统计不同字符的位置
		if(cnt==0) cout<<"0\n";//第一种情况
		else {
			if(cnt%2==1) cout<<"-1\n";//第二种情况
			else if(cnt==2) {//第三种情况
				if(loction[1]+1!=loction[2]) cout<<y<<"\n";
				else cout<<min(x,2*y)<<"\n";
			}else cout<<cnt/2*y<<"\n";//第四种情况
		}
	}
	return 0;
}
```

---

