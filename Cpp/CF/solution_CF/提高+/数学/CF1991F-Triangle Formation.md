# Triangle Formation

## 题目描述

### 题面描述
你有 $n$ 根棍子，从 $1$ 到 $n$ 编号。第 $i$ 根棍子的长度是 $a_i$。

你需要回答 $q$ 个问题。在每个查询中，你会得到两个整数 $l$ 和 $r$（$1 \le l < r \le n，r − l + 1 \le 6$）。确定是否可以从编号为l到r的棒中选择6个不同的棒，形成2个非退化三角形。

边长为 $a$、$b$ 和 $c$ 的三角形称为非退化三角形，当且仅当：

$a<b+c\text{，}b<a+c，c<a+b$。

## 样例 #1

### 输入

```
10 5
5 2 2 10 4 10 6 1 5 3
1 6
2 7
2 8
5 10
4 10```

### 输出

```
YES
NO
YES
NO
YES```

# 题解

## 作者：Engulf (赞：13)

究极唐题，唐场，ConstructForces。

考虑最长的无法构成三角形的区间，构造 $a_1 = 1, a_2 = 1, a_3 = 2, a_i = a_{i - 1} + a_{i - 2} \cdots$，因为 $a_i \le 10^9$，发现 $a_{45} = 11,3490,3170 > 10^9$，断定长度 $\ge 45$ 的区间至少存在一组数可以构成三角形 $[1]$（以下简称为“存在三角形”）。

继续断言长度 $\ge 48$ 的区间存在两个三角形。证明 trivial，由 $[1]$ 可知这个区间存在一个三角形。去掉这三个数，剩下的区间 $\ge 45$，同样由 $[1]$ 得到剩余区间存在一个三角形，得证。

于是乎做法便得到了：
- $r-l+1 \ge 48$，输出 `YES`。
- $r - l + 1 < 48$，区间特别短小，考虑暴力寻找三角形。对区间排序不影响答案，如此做，考虑相邻的三个数 $(x, y, z), x \le y \le z$，若 $x + y > z$ 那么 $(x, y, z)$ 构成三角形，不会证翻八上数学书，发现数字离得越远，**构成三角形的可能性越渺茫** $[2]$，于是只考虑相邻的数，下面的三元组 $(x, y, z)$ 均隐含**相邻**和 $x < y < z$ 的限制条件，不再附上。
  - 若存在 $(x_1, y_1, z_1)$ 和 $(x_2, y_2, z_2)$ 且 $z_1$ 的**下标** $<$ $x_2$ 的**下标**，输出 `YES`。
  - 如果不存在这样的两组三角形，很有可能是它们混在了一起，比如这样 $[2, \color{red}2\color{black}, 4, 5, \color{red}10\color{black}, \color{red}10\color{black}]$，同样地，它们一定是**相邻的** $6$ 个数，原因同 $[2]$。记这 $6$ 个数为数组 $b$，暴力地枚举 $b$ 中的 $b_j, b_k (j < k)$，以及除去 $b_1, b_j, b_k$ 的另外三个数，下标记作 $b_{v_1}, b_{v_2}, b_{v_3}, v_1 < v_2 < v_3$，若 $b_1 + b_j > b_k$ 且 $b_{v_1} + b_{v_2} > b_{v_3}$ 则找到了两个三角形。否则就无解啦。

实现上注意：`vector` 的长度 `vector::size()` 是**无符号整型**，原本减至负数的将会变成一个极大值（对 $2^w-1$ 取模了，$w = 32$ 或 $64$，取决于机器），要判掉。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    while (q--) {
        int l, r;
        cin >> l >> r;
        if (r - l + 1 >= 48) cout << "YES\n";
        else {
            vector<int> b(a.begin() + l - 1, a.begin() + r);
            sort(b.begin(), b.end());

            vector<int> validB;
            for (int i = 0; i < (b.size() > 2 ? b.size() - 2 : 0); i++) {
                if (b[i] + b[i + 1] > b[i + 2])
                    validB.emplace_back(i);
            }
            if (validB.size() && validB.back() - validB.front() > 2) {
                cout << "YES\n";
                goto qwq;
            }

            for (int i = 0; i < (b.size() > 5 ? b.size() - 5 : 0); i++) {
                vector<int> c(b.begin() + i, b.begin() + i + 6);

                for (int j = 1; j < 5; j++)
                    for (int k = j + 1; k < 6; k++)
                        if (c[0] + c[j] > c[k]) {
                            vector<int> v;
                            for (int l = 1; l < 6; l++)
                                if (l != j && l != k)
                                    v.emplace_back(c[l]);
                            if (v[0] + v[1] > v[2]) {
                                cout << "YES\n";
                                goto qwq;
                            }
                        }
            }
            cout << "NO\n";
            qwq:{}
        }
    }
    return 0;
}
```

---

## 作者：2huk (赞：2)

**题意**：有 $n$ 个长度 $a_i$。静态询问能否从区间 $[l, r]$ 中选出 $6$ 根凑成两个非退化三角形。

**做法**：若只要求凑出**一个**三角形，可以证明将 $[l, r]$ 排序后，原问题等价于是否存在 $i\in[l, r - 2]$ 满足 $a_i + a_{i + 1} > a_{i+2}$。证明如下：

> 充分性显然。
>
> 必要性。若不存在 $a_i + a_{i+1} > a_{i+2}$（即所有 $i$ 都满足 $a_i+a_{i+1} \le a_{i+2}$），那么一定凑不出三角形。反证法。若能凑出，不妨令这三条线段分别为 $i, i + x, i + x + y$（$x \ge 1, y \ge 1$）。因为排过序，所以 $a_i \le a_{i+x} \le a_{i+x+y}$。因为所有 $i$ 都满足 $a_i + a_{i+1} \le a_{i+2}$，所以 $a_i + a_{i+x} \le a_{i+x+y-2} + a_{i+x+y-1} \le a_{i+x+y}$。所以 $i,i+x,i+x+y$ 这三条线段也不能凑出。

可以证明，当区间长度 $\ge 45$ 时，一定有解。证明如下：

> 证逆否。
>
> 若无解，即对于所有 $i$ 都满足 $a_i + a_{i + 1} \le a_{i+2}$。因为 $a_l \ge 1, a_{l+1} \ge 1$，所以 $a_i \ge Fib_i$。其中 $Fib_i$ 表示斐波那契数列（$Fib_1 = Fib_2 = 1, Fib_i = Fib_{i-1} + Fib_{i-2}$）。因为 $Fib_{45} = 1134903170 \ge 10^9 \ge a_i$，所以区间长度必定 $< 45$。

考虑**两个**三角形。

可以证明，当区间长度 $\ge 48$ 时，一定有解。证明如下：

> 首先一定能凑出**一个**三角形，因为 $48 > 45$。
>
> 将这个三角形的三条边去掉后，剩下的数量 $\ge 48-3 = 45$。又可以凑出一个。

所以对于剩下的情况暴力即可。

但是暴力也不能六次方的复杂度。我们可以考虑：

- 若存在 $i, j$（$i + 2 < j$）满足 $a_i + a_{i + 1} > a_{i + 2}$ 且 $a_j + a_{j + 1} > a_{j+2}$，那么用 $i, i + 1, i + 2, j, j + 1, j + 2$ 这些木条即可。
- 否则，判断是否存在 $i$ 满足 $a_i, a_{i+1}, a_{i+2}, a_{i+3}, a_{i+4}, a_{i+5}$ 可以凑成两个三角形即可。

```cpp
// Problem: Triangle Formation
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1991F
// Memory Limit: 250 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

typedef long long ll;

int n, q, a[N], b[N];
vector<int> S;
int sum[2], mx[2];

signed main() {
	for (int i = 0; i < 1 << 6; ++ i )
		if (__builtin_popcount(i) == 3 && i != 1 + 2 + 4 && i != 8 + 16 + 32) {
			S.push_back(i);
		}
	
	cin >> n >> q;
	
	for (int i = 1; i <= n; ++ i ) cin >> a[i];
	
	while (q -- ) {
		int l, r;
		cin >> l >> r;
		if (r - l + 1 >= 48) puts("YES");
		else {
			int m = 0;
			for (int i = l; i <= r; ++ i ) b[ ++ m] = a[i];
			
			sort(b + 1, b + m + 1);
			
			int L = 1e9, R = -1e9;
			for (int i = 1; i + 2 <= m; ++ i )
				if (b[i] + b[i + 1] > b[i + 2]) {
					L = min(L, i);
					R = i;
				}
			
			if (L + 2 < R) puts("YES");
			else {
				bool flg = false;
				
				for (int i = 1; i + 5 <= m && !flg; ++ i )
					for (int s : S) {
						sum[0] = sum[1] = mx[0] = mx[1] = 0;
						
						for (int j = 0; j < 6; ++ j ) {
							int w = s >> j & 1;
							sum[w] += b[i + j];
							mx[w] = max(mx[w], b[i + j]);
						}
						
						if (mx[0] < sum[0] - mx[0] && mx[1] < sum[1] - mx[1]) {
							flg = true;
							break;
						}
					}
				
				puts(flg ? "YES" : "NO");
			}
		}
	}
	
	return 0;
}
```

---

## 作者：MarSer020 (赞：1)

赛时 +10，什么实力？

$\Large\text{Solution}$

显然先将区间排序一遍不改变答案，以下默认查询的区间是不增的。

考虑存在解的充要条件是存在两个不交三元组 $(x,y,z),x<y<z$ 使得 $a_x<a_y+a_z$。

注意到若每次取出最大的三个数 $x,y,z$，当 $x\ge y+z$ 时，即不能构成三元组时，则有 $x\ge 2z$，此时最大值减半。又当最大值为 $1$ 时若数有至少 $6$ 个，显然必能构成至少两个三元组。考虑若无法找到满足条件的三元组，最大值会在 $\log n$ 次后递减至 $1$。所以当查询的区间长度大于 $k$ 时，必然有解。其中 $k$ 是 $O(\log n)$ 的。

考虑当 $len<k$ 时如何求解。设当前第 $i$ 大为 $c_i$，注意到当 $c_1\ge c_2+c_3$ 时 $c_1$ 是无用的，直接删去即可。

否则考虑前 $6$ 大值，枚举每种情况看能否组成两个三元组。若不能，则让 $c_1,c_2,c_3$ 直接组成一个三元组并删去即可。考虑该贪心为什么正确：若两个三元组的最大值均在前 $6$ 大中，则将后面的数替换成前 $6$ 大是不劣的。否则利用前 $3$ 大构成一个三元组也是不劣的。贪心成立。

$\Large\text{Code}$

代码上可以直接使用 $80$ 代替 $k$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],p,l,r,c[15];
priority_queue<int>s;
bool check(int x,int y,int z){
	int xx=0,yy=0,zz=0;
	for(int i=2;i<=6;i++)
		if(i!=x&&i!=y&&i!=z){
			if(!xx)
				xx=i;
			else if(!yy)
				yy=i;
			else
				zz=i;
		}
	return (c[x]<c[y]+c[z]&&c[xx]<c[yy]+c[zz]);
}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0),cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>a[i];
	while(m--){
		while(!s.empty())
			s.pop();
		cin>>l>>r;
		if(r-l+1>80){
			cout<<"YES\n";
			continue;
		}
		for(int i=l;i<=r;i++)
			s.emplace(a[i]);
		p=2;
		while(p&&(int)s.size()>=p*3){
			if(p==1){
				for(int i=1;i<=3;i++)
					c[i]=s.top(),s.pop();
				if(c[1]<c[2]+c[3]){
					p=0;
					break;
				}
				s.emplace(c[2]),s.emplace(c[3]);
				continue;
			}
			for(int i=1;i<=6;i++)
				c[i]=s.top(),s.pop();
			for(int i=2;i<=6;i++)
				for(int j=i+1;j<=6;j++)
					if(check(1,i,j)){
						p=0;
						break;
					}
			if(!p)
				break;
			else if(c[1]<c[2]+c[3]){
				p--;
				for(int i=4;i<=6;i++)
					s.emplace(c[i]);
			}
			else
				for(int i=2;i<=6;i++)
					s.emplace(c[i]);
		}
		cout<<(p?"NO\n":"YES\n"); 
	}
	return 0;
}
```

场上由于太傻逼了，没有注意到 $r-l+1>80$ 必然有解，使用了主席树找出前 $80$ 大判断。我是什么傻逼。

---

## 作者：wangyishan (赞：0)

## 题解：CF1991F Triangle Formation

似乎是典题捏。类似题目：P10799。

考虑什么时候构不成 1 个三角形：首先把询问区间排序，构不成 1 个三角形当且仅当对于任意 $i\in[l,r-2],a_{i}+a_{i+1}\le a_{i+2}$。这东西增长速度很快，大于等于我们熟知的斐波那契数列：$f_1=f_2=1,f_n=f_{n-1}+f_{n-2}$。斐波那契数列在 $n\ge 45$ 时大于 $a_i$ 的最大值 $1\times 10^9$，所以当 $n\ge 45$ 时，一定存在一个三角形。

题目要求 2 个三角形，那么当 $n\ge 45+3$ 时，一定可以找到 2 个三角形。证明显然，你从 $n\ge 48$ 的区间中取出 3 个数，之后的区间 $n\ge 45$，仍然能找到能构成三角形的三个数。

当 $n < 48$ 时直接暴力就好了。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int n,q;
ll a[500050],t[110],r[7],c[4];
bool check(int x){// 暴力枚举 6 个连续的数能否构成
    for(int j=2;j<=6;j++){
        for(int k=j+1;k<=6;k++){
            for(int l=1,ct=0;l<=6;l++){
                if(l!=1&&l!=j&&l!=k)c[++ct]=l;
            }
            if(t[x+k]<t[x+1]+t[x+j]&&t[x+c[3]]<t[x+c[2]]+t[x+c[1]])return true;
        }
    }
    return false;
}
void solve(){
    cin>>n>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    while(q--){
        int l,r;
        cin>>l>>r;
        if(r-l+1>=50){
            cout<<"YES"<<endl;
            continue;
        }
        int cnt=0;
        for(int i=l;i<=r;i++)t[++cnt]=a[i];
        sort(t+1,t+cnt+1);
        int L=1e9,R=-1e9;
        for(int i=1;i<=cnt-2;i++){
            if(t[i]+t[i+1]>t[i+2])L=min(L,i),R=i;// 存在 1 组 
        }
        if(L+2<R){//存在的能否不交
            cout<<"YES"<<endl;
            continue;
        }
        int flg=1;
        for(int i=1;i<=cnt-5;i++){
            if(check(i-1)){
                cout<<"YES"<<endl;
                flg=0;
                break;
            }
        }
        if(flg==1)cout<<"NO"<<endl;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    //cin>>T;
    while(T--)solve();
    return 0;
}
```

---

## 作者：dutianchen1 (赞：0)

# F  Triangle Formation

### 思路简析

（英文）题面中告诉我们每次询问的长度 $ r - l + 1 \ge 6$，于是我们考虑如何缩减每次询问的长度。

考虑最劣情况下询问长度为多少才满足性质。显然，在木棍长度为斐波那契数列时，满足性质的序列才会最长。

回题面看数据范围，$a_{i} \in [1,10_{9}] $，再手动写个递推可以发现，序列**最长**不会超过 $45$ 就会满足**至少有一个**三元组 $(x,y,z)$ 满足题意。

而题目要求序列里面有两组满足性质的三元组，那么同理，也只需要再加三项即可。也就是说，只要询问序列长度**大于等于** $48$ 就一定满足题目要求。

接下来分析长度小于 $48$ 的情况。因为范围较小，我们考虑暴力查找是否符合条件。

首先，贪心考虑，先尝试找到一组**权值最大**的三个元素 $x,y,z$ 来构成第一个三元组 $(x,y,z)$。

接下来，我们考虑在不与第一个三元组重复的情况下，再找到剩余元素中，**权值最大**的一组来构成第二个三元组。

为什么再找一个权值最大的？我们考虑模拟一下，假设我们第二组找到的不是剩余元素中**权值最大**的一组，显然，我们令三元组中最小的元素换成剩余元素中更大的一个，这个三元组**仍然满足**三角形**性质**。然而，我们**不可以**随便将第二个权值最大的三元组中的元素**替换**成一个较小的元素。因此我们考虑找剩余元素中**权值最大**的一组。

其余的解释代码有注释，代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6+5;
inline ll read()
{
	ll x=0,f=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
ll n,q; 
ll num[N];//所有棍子 
ll use[N];//区间内的棍子 
ll ans[N];
ll id[N];//记录使用的棍子的编号 
ll check[N];//记录两组混在长度为6的区间内的棍子 
ll len,cnt;
bool cmp(ll a,ll b){return a>b;} 
bool f(ll x){
	return ((check[x]+check[x+1]>check[x+2])&&(check[x]+check[x+2]>check[x+1])&&(check[x+1]+check[x+2]>check[x]));
}
int main()
{
    n=read();q=read();
    for(int i=1;i<=n;i++)num[i]=read();
    while(q--)
	{
        ll l=read(),r=read();
        cnt=0;
        len=r-l+1;
        if(len>=48){
        	cout<<"Yes"<<'\n';
       		continue;
		}
		for(int i=1;i<=len;i++)use[i]=num[i+l-1];
		sort(use+1,use+1+len,cmp);
		for(int i=1;i<=len-2;i++)
		{
			if(use[i+2]+use[i+1]>use[i])//降序取元素。 
			{
				id[++cnt]=i;
			}
		}
		ll fpos=0;//第一个三角形
		for(int i=1;i<=cnt;i++){
			if(id[i]-id[1]>=3)
			{
				fpos=id[i];
				break;
			}
		} 
		ll flag=0;
		if(fpos){//如果找到了第一个 (不与第二组的三个元素混杂) 
			for(int i=0;i<=2;i++){
				flag+=(use[id[1]+i]+use[fpos+i]);
			}
		}
		if(id[1]+5<=len){//拿出最大的六个元素，看能不能分成符合题意的两组。 
			for(int i=0;i<=5;i++)check[i]=use[id[1]+i];
			sort(check,check+6);
			do{
				if(f(0)&&f(3)){
					flag=1;
					break;
				}
			}while(next_permutation(check,check+6));
		}
		cout<<(flag?"Yes":"No")<<'\n';
//		end:{}
    }
    return 0;
}
/*
10 5
5 2 2 10 4 10 6 1 5 3
1 6
2 7
2 8
5 10
4 10
*/

```

---

## 作者：1234567890sjx (赞：0)

哇，我十五分钟切了一道紫！！！

（其实是因为做过 AT 的弱化版，可以翻我一年前的题解）

### F

定义 $F_i$ 为第 $i$ 个斐波那契数，则容易证明 $F_{50}>10^9$，也就是说 $2\times 50=100$ 条边就一定可以组成三角形。

现在只需要讨论区间长度 $\le 100$ 的情况。

将所有在区间范围内的线段从大到小排序，然后第一个三角形一定可以贪心的选权值最大的那一个。第二个三角形贪心的选择和第一个三角形没有重复的边的三角形中，权值最大的那一个即可。时间复杂度为 $O(qW\log W)$。其中 $W$ 为区间长度。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5 + 10;
int a[N], b[N], id[N];
signed main() {
    int m, q;
    cin >> m >> q;
    for (int i = 1; i <= m; ++i)
        cin >> b[i];
    while (q--) {
        int l, r;
        cin >> l >> r;
        if (r - l + 1 >= 200)
            puts("YES");
        else {
            int n = r - l + 1;
            for (int i = 1; i <= n; ++i)
                a[i] = b[i + l - 1];
            sort(a + 1, a + n + 1, greater<>());
            int cnt = 0;
            for (int i = 1; i <= n - 2; ++i)
                if (a[i + 1] + a[i + 2] > a[i])
                    id[++cnt] = i;
            int gmid = -1;
            for (int i = 1; i <= cnt; ++i)
                if (id[i] - id[1] >= 3) {
                    gmid = id[i];
                    break;
                }
            int mx = -1;
            if (~gmid)
                mx = a[id[1]] + a[id[1] + 1] + a[id[1] + 2] + a[gmid] + a[gmid + 1] + a[gmid + 2];
            if (id[1] + 5 <= n) {
                int p[6] = {a[id[1]], a[id[1] + 1], a[id[1] + 2], a[id[1] + 3], a[id[1] + 4], a[id[1] + 5]};
                sort(p, p + 6);
                int cost = accumulate(p, p + 6, 0ll);
                do {
                    if (p[0] + p[1] > p[2] && p[3] + p[4] > p[5] && p[1] + p[2] > p[0] && p[0] + p[2] > p[1] && p[3] + p[5] > p[4] && p[4] + p[5] > p[3]) {
                        mx = max(mx, cost);
                        break;
                    }
                } while (next_permutation(p, p + 6));
            }
            if (~mx)
                puts("YES");
            else
                puts("NO");
        }
    }
}
```

---

## 作者：lfxxx (赞：0)

首先 **假若** 将一个区间内的数排序，显然若存在一个三角形一定就是在相邻 $3$ 个数之间，那么假若不存在三个数则对于每个 $i$ 都有 $a_{i+1} \geq a_i + a_{i-1}$，注意到 $a_i$ 一定大于斐波那契数列的对应项，而这个数量是指数增长的，也就是当区间长度大于 $2 \log V$ 时一定会存在两对解，接下来考虑对于区间长度小于等于 $2 \log V$ 的情况，显然两对三角形应该是两组不相交的相邻 $3$ 个数或者相邻 $6$ 个数经行某种分配，前者是好算的，后者枚举相邻 $6$ 个数然后 $2^6$ 枚举每个数放入哪个三角形即可。注意需要一定的剪枝与常数优化。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+114;
int n,q,a[maxn],c[maxn];
int popcount[1<<6];
int A[3],B[5],ta,tb;
vector<int> S;
bool check(int l,int r){
    for(int i=l;i<=r;i++) c[i]=a[i];
    sort(c+l,c+r+1);
    for(int i=l;i+5<=r;i++){
        for(int k:S){
            ta=0,tb=0;
            for(int p=0;p<6;p++){
                if((1<<p)&k) A[ta++]=c[i+p];
                else B[tb++]=c[i+p];
            }
            if(A[0]+A[1]>A[2]&&B[0]+B[1]>B[2]) return true;
        }
    }
    int f=r+1,b=l-1;
    for(int i=l+1;i+1<=r;i++)
        if(c[i-1]+c[i]>c[i+1]) f=min(f,i),b=max(b,i);
    if(b-f>=3) return true;
    return false;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    for(int i=1;i<(1<<6);i++) popcount[i]=popcount[i/2]+i%2;
    for(int i=0;i<(1<<6);i++)
        if(popcount[i]==3) S.push_back(i);
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>a[i];
    while(q--){
        int l,r;
        cin>>l>>r;
        if(r-l>=70) cout<<"YES\n";
        else cout<<(check(l,r)==true?"YES\n":"NO\n");
    }
}
/*
10 1
5 2 2 10 4 10 6 1 5 3
2 8
*/

```

---

## 作者：六楼溜刘 (赞：0)

## 题意

- 给定一长度为 $n$ 的序列 $a_n$，其中 $a_i$ 代表一根木棍的长度，木棍是两两不同的，尽管长度可能一样。
- 有 $q$ 次询问，每次询问某区间 $[l,r]$ 中能否取出 $6$ 根不同的木棍组成两个三角形，保证 $r-l+1\ge 6$
- $6\le n\le 10^5,1\le q\le 10^5,1\le a_i\le 10^9$。

## 题解

哎哟赛时想出做法结果糖丸了吃了一堆罚时。

~~省流：暴力可过。~~

首先只考虑组一个三角形怎么做：

> 引理：只要 $r-l+1\ge 45$ 就必定有解。

这个可以打点暴力瞪出来。

为什么呢？首先对于组一个三角形，显然只要给木根按长度排序每次考虑相邻的三个是否满足 $a_i+a_{i+1}> a_{i+2}$ 即可。

那么一个单调不下降的序列何时满足 $a_i+a_{i+1}\le a_{i+2}$ 呢？显然最好情况就是它恰好取等，那么是一个斐波那契数列，容易发现 $f_{45}=1134903170>10^9$（此处 $f_i$ 表示斐波那契数列第 $i$ 项），那么超过 $45$ 根木棍无论怎么构造都必定会出现一个三角形的情况。

所以只需要对 $r-l+1< 45$ 的情况暴力将区间取出来排序后遍历即可。

---

那么两个三角形呢？

其实也非常简单，相当于去掉三根木棍再做一遍，那么 $45$ 换成 $48$ 即可。

但是怎么暴力呢？

仍然考虑**删掉某个三角形后再搞**，于是又两种情况：两个三角形在排序后的序列上根本不相邻（这个是简单的）。或者两个三角形缠在一起（例子：$1,1,2,2,2,2$，两个三角形均为 $[1,2,2]$）。

因为将第一个三角形删掉后第二个三角形也必然能是一段连续的区间，所以两个三角形必然能占用连续的六个位置，所以枚举这个长度为 $6$ 的连续段再随便搞一下即可。

复杂度 $O(q\times 48\times 6^2)$，这个写法不是很严谨，但是能传达我的意思。总之 $10^5$ 的五秒还是随便过的。

代码没取 $48$，随便取了个 $60$。

## code

```cpp
#include<bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
#define forup(i,s,e) for(i64 i=(s),E123123=(e);i<=E123123;i++)
#define fordown(i,s,e) for(i64 i=(s),E123123=(e);i>=E123123;i--)
using namespace std;
#ifdef DEBUG
#define msg(args...) fpri64f(stderr,args)
#else
#define msg(...) void()
#endif
using i64=long long;
using pii=pair<i64,i64>;
#define fi first
#define se second
#define mkp make_pair
#define gc getchar()
inline i64 read(){
    i64 x=0,f=1;char c;
    while(!isdigit(c=gc)) if(c=='-') f=-1;
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=gc;}
    return x*f;
}
#undef gc
const i64 N=1e5+5;
i64 n,m,a[N],len;
vector<i64> vec;
bool chk(i64 x){
    forup(i,1,4){
        forup(j,i+1,5){
            if(vec[x]+vec[x+i]>vec[x+j]){
                vector<int> v1;
                forup(p,1,5){
                    if(p!=i&&p!=j) v1.push_back(vec[x+p]);
                }
                if(v1[0]+v1[1]>v1[2]){
                    return true;
                }
            }
        }
    }
    return false;
}
signed main(){
    n=read();m=read();
    forup(i,1,n){
        a[i]=read();
    }
    forup(i,1,m){
        i64 l=read(),r=read();
        if(r-l+1>60){
            puts("YES");
            continue;
        }
        vec.clear();
        forup(i,l,r){
            vec.push_back(a[i]);
        }
        sort(vec.begin(),vec.end());
        len=vec.size();
        bool flag=false;
        int mn=-1;
        forup(i,0,len-3){
            if(vec[i]+vec[i+1]>vec[i+2]){
                if(mn==-1) mn=i;
                if(i>=mn+3){
                    flag=true;
                    break;
                }
            }
        }
        if(!flag){
            forup(i,0,len-6){
                if(chk(i)){
                    flag=true;
                    break;
                }
            }
        }
        puts(flag?"YES":"NO");
    }
}
```

---

## 作者：_lmh_ (赞：0)

一个很重要的观察是如果区间长度足够大的话一定有解。

具体地，考虑一个三角形的情况，最好的构造是斐波那契数列，大概会在 50 项左右的地方超出 $10^9$ 的范围，也就是说大约五十个数就肯定能找到一个三角形。

所以如果询问序列长度超过了 100 就可以直接输出 `YES`。这个上界非常松。

否则我们把序列提取出来排序，分几种情况讨论。

将六个选出来的数所属的三角形编号，如 111222 代表选出来的数中小的那三个属于三角形 1，大的三个属于三角形 2。

我们从后往前枚举六个数中最大的，设目前枚举到第 i 个数，属于三角形 2。

1. 111222

显然选择连续三个是最优的，记录一下每个前缀是否能选出三角形即可。

2. 112122

显然让所有数占据 $i-5 \sim i$ 最优，直接判断。

3. 121122/211122

如果最后一个 1 占据了 $i-2$ 的位置可以把左边的数尽可能往右移然后特判，否则注意到 111222 的一种情况一定不劣。

4. 211212/121212/112212

右侧出现单独一个 1，把它和左边的那个 2 交换一定不劣。

5. 212112/122112/221112

同理如果所有数不占据 $i-5\sim i$ 一定可以调整到更优的位置，依然特判即可。

至此所有情况考虑完毕，我们在 $O(mV\log V)$（其中 $V$ 为输出 NO 的可能最大值，程序里可以预设为 100）的复杂度内解决了问题。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll N=100007;
ll T,n,m,a[N],b[N],k,l,r,ok[N];
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m;
	for (int i=1;i<=n;++i) cin>>a[i];
	while(m--){
		cin>>l>>r;
		if (r-l>=100){
			cout<<"YES\n";continue;
		}
		ll fl=k=0;
		for (ll i=l;i<=r;++i) b[++k]=a[i];
		sort(b+1,b+1+k);
		ok[2]=0;
		for (ll i=3;i<=k;++i) ok[i]=ok[i-1]||(b[i-2]+b[i-1]>b[i]);
		for (ll i=k;i>=6;--i){
			if (b[i-5]+b[i-4]>b[i]) fl|=(b[i-3]+b[i-2]>b[i-1]);
			if (b[i-4]+b[i-3]>b[i]) fl|=(b[i-5]+b[i-2]>b[i-1]);
			if (b[i-5]+b[i-3]>b[i]) fl|=(b[i-4]+b[i-2]>b[i-1]);
			if (b[i-5]+b[i-1]>b[i]) fl|=(b[i-4]+b[i-3]>b[i-2]);
			if (b[i-4]+b[i-1]>b[i]) fl|=(b[i-5]+b[i-3]>b[i-2]);
			if (b[i-2]+b[i-1]>b[i]) fl|=ok[i-3];
			if (fl) break;
		}
		cout<<(fl?"YES\n":"NO\n");
	}
	return 0;
}
```

---

