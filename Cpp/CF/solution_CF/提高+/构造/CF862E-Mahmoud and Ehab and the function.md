# Mahmoud and Ehab and the function

## 题目描述

给出长度为 $n$ 的数组 $a$ 和长度为 $m$ 的数组 $b$，定义函数 $f(j)$ ($0$ $≤$ $j$ $≤$ $m$ −$n$) 如图所示（未翻译的题面中的图），共有 $q$ 次更新，每次更新将 $a$ 数组中下标为 $l $\~$ r$ 中的每个数加上 $x$，对于原数组和每次更新后的数组，求 $f(j)$ 的最小值

## 样例 #1

### 输入

```
5 6 3
1 2 3 4 5
1 2 3 4 5 6
1 1 10
1 1 -9
1 5 -1
```

### 输出

```
0
9
0
0
```

# 题解

## 作者：xxgirlxx (赞：3)

## 题外话
模拟赛 T1，结果 Lemonlime 发癫了，把我的 100 分测成了 50 分，我当场红温。
## 题目大意
给你一个长度为 $n$ 的 $a$ 序列和一个长度为 $m$ 的 $b$ 序列，然后让你求下面的这个式子的值：

$$\min_{j=0}^{m-n}f(j)=| \sum_{i=1}^{n}(-1)^{i-1}\times (a_i-b_{i+j})|$$

但是出题人觉得这样太简单了，所以会对 $a$ 序列进行 $q$ 次更改，每次更改会将 $l$ 到 $r$ 的 $a_i$ 改成 $a_i+x$。

求所有更改前和每次更改后式子对应的值。
## 题目思路
首先将式子转化一下：

$$\min_{j=0}^{m-n}f(j)=| \sum_{i=1}^{n}((-1)^{i-1}\times a_i+(-1)^i\times b_{i+j})|$$

注意到所有的 $f(j)$ 都加上了 $\sum_{i=1}^{n}(-1)^{i-1}\times a_i$，也就是说，假如 $a$ 序列发生了改变，那么所有的 $f(j)$ 都会改变，而且改变的过后与原值相差的值是一样的。而 $b$ 序列又不会发生改变。也就是说，$a$ 序列和 $b$ 序列只是给所有的 $f(j)$ 赋初值而已。

然后对所有的 $f(j)$ 的初值进行计算。$a$ 序列的贡献值因为是固定的，所以可以直接用一个数记录下来。$b$ 序列的贡献值是连续的一串数，所以可以用前缀和来计算。但是注意到 $b$ 序列还要乘上 $(-1)^i$，在开头奇偶性不同的情况下，一个数的贡献值也是不同的。比如说以 $1$ 开头，$b_2$ 的贡献值就是 $b_2$。但是以 $2$ 开头，$b_2$ 的贡献值就是 $-b_2$ 了。所以要将所有的贡献值分成两类，一类是奇数开头的，另一类是偶数开头的，两类贡献值需要分别计算。

再考虑改变的情况，注意到 $a$ 序列的贡献值是一减一加一减一加的，所以如果 $l$ 和 $r$ 是一奇一偶，那么加的数量和减的数量就是一样的，更改的值为 $0$。如果都是奇数，那么更改的值为 $-x$。如果都是偶数，更改的值就为 $x$。

最后考虑怎么找到最小的值，因为加了绝对值，所以最开始就是要找到和 $0$ 最接近的 $f(j)$，因为不需要输出 $j$ 的值，所以我们可以直接把所有的 $f(j)$ 排一个序，然后就可以二分寻找最接近 $0$ 的值了（如果像我一样懒得手写二分的可以用 lower_bound）。可是后面的呢？注意到所有的 $f(j)$ 都会加上改变的值，所以我们可以找最接近**总的**改变的值的相反数的那一个 $f(j)$（因为醉最接近总的改变的值的相反数的那个加上总的改变的值才会最接近 $0$）。注意一下 lower_bound 是输出的**第一个大于等于值的数的位置**，所以前面的和后面的都要看一下，再特判一下边界的情况再输出就可以了。
## Code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,q,suma,sumb[500010],f[500010],a[500010],b[500010],sum,num,l,r,x;
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)cin>>a[i],suma+=(i%2==0?-1:1)*a[i];
	for(int i=1;i<=m;i++)cin>>b[i],sumb[i]=sumb[i-1]+(i%2==1?-1:1)*b[i];
	for(int i=0;i<=m-n;i+=2)f[i]=suma+sumb[i+n]-sumb[i];
	for(int i=1;i<=m;i++)sumb[i]=sumb[i-1]+(i%2==0?-1:1)*b[i];
	for(int i=1;i<=m-n;i+=2)f[i]=suma+sumb[i+n]-sumb[i];
	sort(f,f+m-n+1);
	for(int i=0;i<=q;i++){
		if(i!=0){cin>>l>>r>>x;if(l%2==r%2)num+=(l%2==1?x:-x);}
		sum=lower_bound(f,f+m-n+1,-num)-f-1;
		if(sum==m-n)cout<<abs(f[sum]+num)<<endl;
		else if(sum==-1)cout<<abs(f[sum+1]+num)<<endl;
		else cout<<min(abs(f[sum]+num),abs(f[sum+1]+num))<<endl;
	} 
	return 0;
}
```

---

## 作者：Nylch (赞：2)

首先 $f(j)=\displaystyle|\sum_{i=1}^{n}(-1)^{i-1}a_i+(-1)^ib_{i+j}|=|\sum_{i=1}^{n}(-1)^{i-1}a_i+\sum_{i=1}^{n}(-1)^{i}b_{i+j}|$

我们先处理出 ```suma```，表示 $\displaystyle\sum_{i=1}^{n}(-1)^{i-1}a_i$ 的值。

然后处理出 ```sumb[i]```，这个是等于 $-(sumb[i-1]+b_i)+b_{i+n}* n$ 是否为奇数，为奇数就乘 $-1$，否则乘 $1$。

然后我们发现对于每次的更新，只有 $r-l+1$ 为奇数时，且 $l$ 也为奇数时，```suma``` 才会发生变化，所以对于每次更新就判断一下就行了。

那么对于 $f(j)$ 的最小值，我们二分一下，在 ```sumb``` 中找最接近 ```suma``` 的就行了。

代码：

```cpp
#include <bits/stdc++.h>
#define reg register
#define ll long long
#define int long long
#define ull unsigned long long
#define db double
#define pi pair<int, int>
#define pl pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define vpi vector<pi>
#define vpl vector<pl>
#define pb push_back
#define er erase
#define SZ(x) (int) x.size()
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mkp make_pair
using namespace std;
char ch, B[1 << 20], *S = B, *T = B;
#define getc() (S == T && (T = (S = B) + fread(B, 1, 1 << 20, stdin), S == T) ? 0 : *S++)
#define isd(c) (c >= '0' && c <= '9')
int aa, bb;
int rd() {
  while(ch = getc(), !isd(ch) && ch != '-');
  ch == '-' ? aa = bb = 0 : (aa = ch - '0', bb = 1);
  while(ch = getc(), isd(ch))
    aa = aa * 10 + ch - '0';
  return bb ? aa : -aa;
}
const int MAXN = 1e5 + 10;
int n, m, q, a[MAXN], b[MAXN], suma, sumb[MAXN];
int ask(int l, int r, int x, int delta) {
  if((r - l) % 2 == 0) {
    if(l % 2 == 1)
      suma += x;
    else
      suma -= x;
  }
  int *pos = lb(sumb, sumb + delta, -suma);
  int ans = 1e18 + 10;
  if(pos != sumb + delta)
    ans = min(ans, abs(suma + *pos));
  if(pos != sumb) {
    --pos;
    ans = min(ans, abs(suma + *pos));
  }
  return ans;
}
inline void work() {
  scanf("%lld%lld%lld", &n, &m, &q);
  suma = 0;
  for(reg int i = 1, mul = 1; i <= n; ++i, mul *= -1) {
    scanf("%lld", &a[i]);
    suma += a[i] * mul;
    // printf("%d ", suma);
  }
  // puts("");
  int delta = m - n + 1;
  sumb[0] = 0;
  for(reg int i = 1, mul = -1; i <= m; ++i, mul *= -1) {
    scanf("%lld", &b[i]);
    if(i <= n)
      sumb[0] += b[i] * mul;
  }
  for(reg int i = 1; i + n <= m; ++i)
    sumb[i] = -(sumb[i - 1] + b[i]) + b[i + n] * ((n & 1) ? -1 : 1);
  // for(reg int i = 1; i <= m; ++i)
    // printf("%d ", &b[i]);
  // puts("");
  sort(sumb, sumb + delta);
  printf("%lld\n", ask(1, 1, 0, delta));
  for(reg int i = 1; i <= q; ++i) {
    int l, r, x;
    scanf("%lld%lld%lld", &l, &r, &x);
    printf("%lld\n", ask(l, r, x, delta));
  }
}
signed main() {
  // freopen("input.txt", "r", stdin);
  work();
  return 0;
}
```

---

## 作者：Sirkey (赞：1)

~~考试考到的签~~

[或许更好的阅读体验](https://cnblogs.com/sirkey2119/articles/18449781)

原式子：

$f_j  = |\sum_{i = 1} ^ n (-1) ^{i-1} \times (a_i - b_{i + j})|$

基本思路把 $a_i$ 和 $b_i$ 分开。

$f_j  = |\sum_{i = 1} ^ n (-1) ^{i-1} \times a_i - (-1) ^{i-1} \times b_{i+j}|$

发现 $(-1) ^{i-1} \times a_i$ 没有修改是个定值，直接计算。

考虑修改：

- 修改区间长度为 2 的倍数可以忽略，因为是一加一减。

- 修改区间长度不为 2 的倍数，判断右端点或左端点的奇偶性，偶数就减，奇数就加。

接下来考虑 $(-1) ^{i-1} \times b_{i+j}$ 我们可以将每个 $j$ 的该式子求出来。求的时候使用前缀和优化，就可以做到 $O(1)$。

求解答案时，将求出的 $(-1) ^{i-1} \times b_{i+j}$ 排序后二分出最接近 $(-1) ^{i-1} \times a_i$ 的。

```#include<bits/stdc++.h>
#define ll long long
#define int ll
#define debug(x) cout<<#x<<"[:]"<<x,puts("");
#define FOR(i,a,b) for(ll i=(a); i<=(b); ++i)
#define ROF(i,a,b) for(ll i=(a); i>=(b); --i)
//
//
//
using namespace std;
inline ll read() {
	ll f = 0, t = 0;
	char c = getchar();
	while (!isdigit(c)) t |= (c == '-'), c = getchar();
	while (isdigit(c)) f = (f << 3) + (f << 1) + c - 48, c = getchar();
	return t ? -f : f;
}
void write(int x) {
	if(x<0) putchar('-'),x=-x;
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
const int MX = 6e5 + 10;
int a[MX], b[MX][3];
int f[MX];
int n,m,Q;
const int inf = 1e18 + 10;
int check(int sum) {
	int l = 1, r = m - n + 1;
	int ans1 = inf;
	while(l <= r) {
		int mid = (l + r) / 2;
		if(f[mid] <= sum) ans1 = f[mid], l = mid + 1;
		else r = mid - 1;
	}
	int ans2 = inf;
	l = 1, r = m - n + 1;
	while(l <= r) {
		int mid = (l + r) / 2;
		if(f[mid] >= sum) ans2 = f[mid], r = mid - 1;
		else l = mid + 1;
	}
	return min(abs(sum - ans1), abs(sum - ans2));
}
signed main() {
	ios::sync_with_stdio(0), cout.tie(0);
	n = read(), m = read(), Q = read();
	FOR(i,1,n) a[i] = read();
	FOR(i,1,m) b[i][0] = read();
	int sum = 0;
	FOR(i,1,n) {
		if(i % 2 == 1) sum += a[i];
		else sum -= a[i];
	}
	FOR(i,1,m) {
		b[i][1] = b[i - 1][1];
		b[i][2] = b[i - 1][2];
		if(i % 2 == 0) b[i][2] += b[i][0];
		else b[i][1] += b[i][0];
	}
	FOR(i,1,m - n + 1) {
		if(i % 2 == 0) f[i] = b[n + i - 1][2] - b[i - 1][2] - b[n + i - 1][1] + b[i][1];
		else f[i] = b[n + i - 1][1] - b[i - 1][1] - b[n + i - 1][2] + b[i][2];
	}
	sort(f + 1,f + m - n + 2);
	cout<<check(sum)<<"\n";
	while(Q--) {
		int l = read(), r = read(), w = read();
		if(l > r) swap(l,r);
		if((r - l + 1) % 2 == 1) {
			if(r % 2 == 1) sum += w;
			else sum -= w;
		}
		cout<<check(sum)<<"\n";
	}
	return 0;
}
```

——end——

---

## 作者：Mu_leaf (赞：1)

挺巧的，和之前的大佬一样，这也是我们模拟赛 T1。

### [思路]

可以在式子上找到突破口。


$$
f_j=|\sum_{i=1}^n(-1)^{i-1}\times (a_i-b_{i+j})|
$$

$$
=|\sum_{i是奇数}^na_i-b_{i+j}-\sum_{i是偶数}^{n}a_i-b_{i+j}|
$$
先不考虑绝对值该怎么取。

对于这个式子，显然只有数组 $a$ 会改变，又因为我们求的是全局和，也就是说我们并不关心这个区间具体在哪，只关心左右端点和区间长度的奇偶性。

分类讨论一下：

- 区间长度为偶数时，式子前面的 $\sum_{i是奇数}^na_i-b_{i+j}$ 会加上 $\frac{(r-l+1)}{2} \times v$，后面同理。

-  区间长度为奇数，若左端点是奇数则前半部分会多一个 $v$，反之则后半部分多一个 $v$。

上面这个式子显然可以 $O(1)$ 求出每个 $f_j$。每次对 $a$ 的修改是对所有 $f_j$ 进行修改。

于是可以排序，维护每次操作造成的贡献，二分找到最接近 $0$ 的两个数比较大小即可。

时间复杂度：$O(n \log n)$。

## Code：

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
namespace IO{
	char buff[1<<21],*p1=buff,*p2=buff;
	char getch(){return p1==p2&&(p2=((p1=buff)+fread(buff,1,1<<21,stdin)),p1==p2)?EOF:*p1++;}
	template<typename T>void read(T &x){char ch=getch();int fl=1;x=0;while(ch>'9'||ch<'0'){if(ch=='-')fl=-1;ch=getch();}while(ch<='9'&&ch>='0'){x=x*10+ch-48;ch=getch();}x*=fl;}
	template<typename T>void read_s(T &x){char ch=getch();while(ch<'A'||ch>'Z')ch=getch();while(ch>='A'&&ch<='Z'){x+=ch;ch=getch();}}
	template<typename T,typename ...Args>void read(T &x,Args& ...args){read(x);read(args...);}
	char obuf[1<<21],*p3=obuf;
	void putch(char ch) {if(p3-obuf<(1<<21))*p3++=ch;else fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch;}
	char ch[100];
	void put(string s){for(int i=0;i<s.size();i++)putch(s[i]);}
	template<typename T>void write(T x) {if(!x)return putch('0');if(x<0)putch('-'),x*=-1;int top=0;while(x)ch[++top]=x%10+48,x/=10;while(top)putch(ch[top]),top--;}
	template<typename T,typename ...Args>void write(T x,Args ...args) {write(x);write(args...);}
	char readc(){char c;do{	c=getch();}while(c==' ' || c=='\r' || c=='\n');return c;}
	string reads(){string res="";char c;do{c=getch();}while(c==' ' || c=='\r' || c=='\n');do{res+=c;c=getch();}while(c!=' ' && c!='\r' && c!='\n' && c!=EOF);return res;}
	string getli(){string res="";char c;do{c=getch();}while(c==' '|| c=='\r' || c=='\n');do{res+=c;c=getch();}while(c!='\r' && c!='\n' && c!=EOF);return res;}
	void flush(){fwrite(obuf,p3-obuf,1,stdout);}
}
using namespace IO;
const int N=5e5+5;
int n,m,q,a[N],b[N],p[N],sum1,sum2,per1[N],per2[N];
signed main(){
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	read(n,m,q);
	for(int i=1;i<=n;i++){
		read(a[i]);
		if(i%2) sum1+=a[i];
		else sum2+=a[i];
	}
	for(int i=1;i<=m;i++){
		read(b[i]);
		if(i%2) per1[i]=per1[i-1]+b[i],per2[i]=per2[i-1];
		else per2[i]=per2[i-1]+b[i],per1[i]=per1[i-1];
	}
	for(int i=0;i<=m-n;i++){
		if(i%2) p[i+1]=sum1-(per2[n+i]-per2[i])-sum2+(per1[n+i]-per1[i]);
		else p[i+1]=sum1-(per1[n+i]-per1[i])-sum2+(per2[n+i]-per2[i]);
	}
	int tot=m-n+1;
	int ans=1e18;
	for(int i=1;i<=tot;i++) ans=min(ans,abs(p[i]));
	sort(p+1,p+tot+1);
	write(ans),putch('\n');
	int tmp=0;
	while(q--){
		int l,r,v;
		read(l,r,v);
		if(l>r) swap(l,r);
		if((r-l+1)%2==0) write(ans);
		else{
			if(l%2) tmp+=v;
			else tmp-=v;
			int res=lower_bound(p+1,p+tot+1,-tmp)-p;
			res=min(res,tot);
			res=max(res,2ll);
			if(tot==1) ans=abs(p[1]+tmp);
			else if(tot==2) ans=min(p[1]+tmp,p[2]+tmp);
			else ans=min(abs(p[res]+tmp),abs(p[res-1]+tmp));
			write(ans);
		}putch('\n');
	}
	flush();
	return 0;
}




```

---

## 作者：_Linver_ (赞：0)

我们有 $f(j)=\left|\sum_{i=1}^{n}(-1)^{i-1} a_{i}-(-1)^{i-1} b_{i+j}\right|=\left|\sum_{i=1}^{n}(-1)^{i-1} a_{i}+\sum_{i=1}^{n}(-1)^{i} b_{i+j}\right|$。

考虑到第一项和 $j$ 没有关系，可以用一个变量 $sum$ 存一下，第二项也可以用滑动窗口的方式求出。

设 $s_{j}$ 为第二项，那么 $s_{j}=\sum_{i=1}^{n}(-1)^{i} b_{i+j}=-b_{j+1}+b_{j+2}-\cdots \pm b_{j+n},\operatorname{s}_{j-1}=\sum_{i=1}^{n}(-1)^{i} b_{i+j-1}=-b_{j}+b_{j+1}-\cdots \pm b_{j+n-1}$。

那么可以写出式子 $s_{j}=-\left(s u m b_{j-1}+b_{j}\right) \pm b_{j+n}$。

其中最后一项的符号和 $n$ 的奇偶性有关，若 $n$ 是奇数，那么最后一项符号为负，否则为正。

那么我们要求 $f(j)$ 最小，只需要在 $s$ 中找到最接近 $-sum$ 的数即可。


```cpp
#include<cstdio>
#include<algorithm>
int n,m,q;
long long b[500005],f[500005],a[500005],p;
long long Min(long long x,long long y){return x<y?x:y;}
int read(){char c=getchar();int x=0,f=1;while(c<'0'||c>'9')c=='-'?f=-1:0,c=getchar();while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=getchar();return x*f;}
long long ef(){
	int l=-1,r=m+1;
	while(r-l>1){
		int mid=l+r>>1;
		if(f[mid]+p>=0)r=mid;
		else l=mid;
	}
	if(r==m+1)return -f[m]-p;
	if(r==0)return f[0]+p;
	return Min(f[r]+p,-f[r-1]-p);
}
int main(){
    freopen("trans.in","r",stdin);
    freopen("trans.out","w",stdout);
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;++i)a[i]=read(),a[i]=((i&1)?a[i]:-a[i])+a[i-1];
	for(int i=1;i<=m;++i)b[i]=read(),b[i]=((i&1)?b[i]:-b[i])+b[i-1];
	m-=n;
	for(int i=0;i<=m;++i)f[i]=a[n]+((i&1)?(b[i+n]-b[i]):(b[i]-b[i+n]));
	std::sort(f,f+m+1);
	printf("%lld\n",ef());
	for(int i=1,x,y,v;i<=q;++i){
		x=read(),y=read(),v=read(),x>y?x^=y^=x^=y:0;
		p+=(y&1)?(((y-x)&1)?0:v):(((y-x)&1)?0:-v);
		printf("%lld\n",ef());
	}
	return 0;
}
```

---

## 作者：可爱的小棉羊 (赞：0)

模拟赛 T1

不要被这个柿子吓倒了，拆开来看：

$$f(j)=\mid \sum_{i=1}^n(-1)^{i-1}a_i +\sum_{i=1}^n(-1)^ib_{i+j} \mid$$

后面那个显然不变，可以做前缀和之类的东西搞掉，设为 $B_j$。

而前面那个我们观察，与 $j$ 无关，设为 $A$。

那么我们修改后发现这个新贡献会抵消，可以分成三种情况讨论，可以动态维护 $A$，然后问题变成：

$$\min \mid A+B_j \mid$$

我们只需要按 $B_j$ 排序，然后二分 $-A$，取个 $\min$。

代码没找到，不贴了。

---

## 作者：huangrenheluogu (赞：0)

模拟赛 T1。

容易发现 $f(j)=|\sum\limits_{i=1}^n(-1)^{i-1}a_i-\sum\limits_{i=1}^n(-1)^{i-1}b_{i+j}|$。

发现 $b$ 的贡献是比较难处理的，但是 $b$ 序列是静态的。于是可以对于 $\forall j\in[0,m-n]$，预处理出 $c_j=\sum\limits_{i=1}^n(-1)^{i-1}b_{i+j}$。这个用前缀和是容易的。

$\sum\limits_{i=1}^n(-1)^{i-1}a_i$ 的维护是简单的，只需要分类讨论一下对总和的贡献是 $x/0/-x$ 即可。

考虑绝对值的意义，就是两个表达式之间的距离，lower_bound 出最近的即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 5e5 + 5;
int n, m, q, a[N], b[N], sum[N], tot, c[N], S;
int l, r, v, ans, inf, pos;
inline void chkmin(int &x, int y){
	if(x > y) x = y;
}
inline void calc(){
	ans = inf;
	pos = lower_bound(c + 1, c + tot + 1, S) - c;
	if(pos <= tot) chkmin(ans, abs(c[pos] - S));
	pos--;
	if(pos) chkmin(ans, abs(c[pos] - S));
	printf("%lld\n", ans);
}
signed main(){
	scanf("%lld%lld%lld", &n, &m, &q);
	for(int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for(int i = 1; i <= m; i++) scanf("%lld", &b[i]);
	tot = m - n + 1;
	for(int i = 0; i <= 62; i++) inf |= 1ll << i;
	for(int i = 1; i <= m; i++){
		if(i & 1) b[i] = -b[i];
		b[i] += b[i - 1];
	}
	for(int i = 1, j = n; j <= m; i++, j++){
		c[i] = b[j] - b[i - 1];
		if(i & 1) c[i] *= -1;
	}
	sort(c + 1, c + tot + 1);
	for(int i = 1; i <= n; i++){
		if(i & 1) S += a[i];
		else S -= a[i];
	}
	calc();
	while(q--){
		scanf("%lld%lld%lld", &l, &r, &v);
		if((l & 1) && (r & 1)){
			S += v;
		}
		if((l & 1) + (r & 1) == 0){
			S -= v;
		}
		calc();
	}
	return 0;
}

```

---

## 作者：zhangjiting (赞：0)

## 思路

简单题。

$f$ 函数长这样不怎么方便，考虑把式子拆开。

$\displaystyle\ f(j)= |\sum_{i=1}^{n} (-1)^{i-1} \times (a_i-b_{i+j})|=|\sum_{i=1}^{n} (-1)^{i-1} \times a_i+\sum_{i=1}^{n} (-1)^{i-1} \times (-b_{i+j})|$

发现 $b$ 数组没有修改，对于每个 $j$，算出 $ \displaystyle\ \sum_{i=1}^{n} (-1)^{i-1} \times (-b_{i+j})$，用前缀和就可以了

接下来要维护 $\displaystyle\ \sum_{i=1}^{n} (-1)^{i-1} \times a_i$，可以发现，修改操作对这个值的影响要么是加 $x$，要么是减 $x$，要么不变，也很好维护。

求最小的 $f(j)$，也就是找到最接近 $\displaystyle\ -\sum_{i=1}^{n} (-1)^{i-1} \times a_i$ 的 $ \displaystyle\ \sum_{i=1}^{n} (-1)^{i-1} \times (-b_{i+j})$，给所有 $ \displaystyle\ \sum_{i=1}^{n} (-1)^{i-1} \times (-b_{i+j})$ 排个序，二分查找就可以了。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
#define debug(x) cout<<#x<<':'<<x<<endl
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;
const int N=5e5+5;
int n,m,q;
int sb[N];
int a[N],sa,b[N],s[2][N];// 0:-+-+-+ 1:+-+-+-
int ask(){
	int s1,s2;
	int l=1,r=m-n+1,res=m-n+1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(sb[mid]>=-sa) r=mid-1,res=mid;
		else l=mid+1;
	}s1=sb[res]+sa;
	l=1,r=m-n+1,res=1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(sb[mid]<=-sa) l=mid+1,res=mid;
		else r=mid-1;
	}s2=sb[res]+sa;
	return min(abs(s1),abs(s2));
}
signed main(){
	IOS;
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>b[i];
	for(int i=1;i<=n;i++){
		if(i&1) sa+=a[i];
		else sa-=a[i];
	}
	for(int i=1;i<=m;i++){
		s[0][i]=s[0][i-1],s[1][i]=s[1][i-1];
		if(i&1) s[0][i]-=b[i],s[1][i]+=b[i];
		else s[0][i]+=b[i],s[1][i]-=b[i];
	}
	for(int i=1;i<=m-n+1;i++){
		if(i&1) sb[i]=s[0][n+i-1]-s[0][i-1];
		else sb[i]=s[1][n+i-1]-s[1][i-1];
	}
	sort(sb+1,sb+m-n+2);
	cout<<ask()<<endl;
	for(int i=1,l,r,k;i<=q;i++){
		cin>>l>>r>>k;
		if((r-l+1)%2==0) sa+=0;
		else if(l&1) sa+=k;
		else sa-=k;
		cout<<ask()<<endl;
	}
	return 0;
}
```

---

## 作者：xiao7_Mr_10_ (赞：0)

这玩意是蓝？

显然注意到实际上 $b$ 数组始终不变。

考虑拆开贡献，先预处理所有合理的 $b$ 值。

然后预处理 $a$ 的值，我们只关心 $a$ 数组的贡献而不是某个位置。

维护一下就行，找答案就二分一下，建议手写，不然判断挺麻烦的听说。

时间复杂度 $O(q \log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+5;
int n,m,q,a[N],b[N],ans[N],mul1,mul2,cnt,l,r,x;
int find(int x){
	int l = 1,ans1=0,r = cnt;
	while(l<=r){
		int mid=(l+r)>>1;
		if(ans[mid]>x){
			ans1=mid;
			r=mid-1;
		}else l=mid+1;
	}return ans1;
}
int find1(int x){
	int l = 1,ans1=0,r = cnt;
	while(l<=r){
		int mid=(l+r)>>1;
		if(ans[mid]<=x){
			ans1=mid;
			l=mid+1;
		}else r=mid-1;
	}return ans1;
}
int sum;
int calc(){
	int tmp=abs(sum-ans[1]);
	int id=find(sum);
	if(id)tmp=min(tmp,abs(sum-ans[id]));
	id=find1(sum);
	if(id)tmp=min(tmp,abs(ans[id]-sum));
	return tmp;
}
signed main(){
//	freopen("trans.in","r",stdin);
//	freopen("trans.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin >> n >> m >> q;
	for(int i = 1;i <= n;i++)cin >> a[i];
	for(int i = 1;i <= m;i++)cin >> b[i];
	for(int i = 1;i <= n;i++){
		if(i&1)mul1+=b[i];
		else mul2+=b[i];
	}
	ans[++cnt]=mul1-mul2;
	int l = 1,bj=-1;
	for(int i = n+1;i <= m;i++){
		if(i&1)mul1+=b[i];
		else mul2+=b[i];
		if(l&1)mul1-=b[l],l++;
		else mul2-=b[l],l++;
		ans[++cnt]=(mul1-mul2)*bj;
		bj*=-1;
	}
	sort(ans+1,ans+1+cnt);
	sum=0,bj=-1;
	for(int j = 1;j <= n;j++){
		sum-=a[j]*bj;
		bj*=-1;
	}
	cout << calc() << "\n";
	for(int i = 1;i <= q;i++){
		cin >> l >> r >> x;
		if(l>r)swap(l,r);
		int len=r-l+1;
		if(l&1)sum+=(len&1)*x;
		else sum-=(len&1)*x;
		cout << calc() << "\n" ;
	}
	return 0;
}
```

---

## 作者：incra (赞：0)

### Sol
另一篇题解有不少错的地方，所以就有这篇题解了。

显然 $\displaystyle f(j)=\left|\sum_{i=1}^n(-1)^{i-1}a_i-(-1)^{i-1}b_{i+j}\right|=\left|\sum_{i=1}^n(-1)^{i-1}a_i+\sum_{i=1}^n(-1)^{i}b_{i+j}\right|$。

考虑到第一项和 $j$ 没有关系，可以用一个变量 $suma$ 存一下，第二项也可以用滑动窗口的方式求出。

设 $sumb_j=第二项$，那么 $\displaystyle sumb_j=\sum_{i=1}^n(-1)^{i}b_{i+j}=-b_{j+1}+b_{j+2}-\cdots \pm b_{j+n}$，$\displaystyle sumb_{j-1}=\sum_{i=1}^n(-1)^{i}b_{i+j}=-b_{j}+b_{j+1}-\cdots \pm b_{j+n-1}$。

那么可以写出式子 $sumb_j=-(sumb_{j-1}+b_j)\pm b_{j+n}$。

其中最后一项的符号和 $n$ 的奇偶性有关，若 $n$ 是奇数，那么最后一项符号为负，否则为正。

那么我们要求 $f_{j}$ 最小，只需要在 $sumb$ 中找到最接近 $-suma$ 的数即可。
### Code
```cpp
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cassert>
#include <chrono>
#include <random>
#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define pf push_front
#define desktop "C:\\Users\\incra\\Desktop\\"
#define IOS ios :: sync_with_stdio (false),cin.tie (0),cout.tie (0)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair <int,int> PII;
const int dx[] = {1,0,-1,0},dy[] = {0,-1,0,1};
template <typename T1,typename T2> bool tomax (T1 &x,T2 y) {
	if (y > x) return x = y,true;
	return false;
}
template <typename T1,typename T2> bool tomin (T1 &x,T2 y) {
	if (y < x) return x = y,true;
	return false;
}
LL power (LL a,LL b,LL p) {
	LL ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
int fastio = (IOS,0);
#define endl '\n'
#define puts(s) cout << s << endl
const int N = 100010;
int n,m,q,k;
int a[N],b[N];
LL suma,sumb[N];
LL query () {
	int pos = lower_bound (sumb,sumb + k + 1,-suma) - sumb;
	LL ans = 1e18;
	if (pos <= k) tomin (ans,abs (sumb[pos] + suma));
	if (pos) pos--,tomin (ans,abs (sumb[pos] + suma));
	return ans;
}
int main () {
	cin >> n >> m >> q;
	k = m - n;
	for (int i = 1;i <= n;i++) cin >> a[i],suma += a[i] * (i % 2 ? 1 : -1);
	for (int i = 1;i <= m;i++) cin >> b[i],sumb[0] += i <= n ? b[i] * (i % 2 ? -1 : 1) : 0;
	for (int i = 1;i <= k;i++) sumb[i] = -(sumb[i - 1] + b[i]) + b[i + n] * (n % 2 ? -1 : 1);
	sort (sumb,sumb + k + 1);
	cout << query () << endl;
	while (q--) {
		int l,r,x;
		cin >> l >> r >> x;
		if (r - l + 1 & 1) {
			if (l & 1) suma += x;
			else suma -= x;
		}
		cout << query () << endl;
	}
	return 0;
}
```

---

