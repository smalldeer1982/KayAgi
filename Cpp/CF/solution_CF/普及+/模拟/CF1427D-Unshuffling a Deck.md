# Unshuffling a Deck

## 题目描述

给出一副 $n$ 张编号为 $1$ 到 $n$ 的卡牌，且不一定按照 $1$ 到 $n$ 的顺序给出，你需要按照以下步骤给卡牌排序：

* 任选 $2≤k≤n$ 并将这幅卡牌分为连续非空的 $k$ 个部分 $D_1,D_2,...,D_k$ ，其中 $D_1$ 包含了前 $|D_1|$ 张卡牌（译注： $|D_1|$ 表示 $D_1$ 中卡牌的数量，下同理）， $D_2$ 包含了紧接着的 $|D_2|$ 张卡牌，以此类推。然后将每部分的顺序翻转，将这幅卡牌变为 $D_k,D_{k-1},...,D_2,D_1$ ，操作后的这副卡牌前 $|D_k|$ 张卡牌是属于 $D_k$ 部分的，紧接着的 $|D_{k-1}|$ 张卡牌是属于 $D_{k-1}$ 部分的，以此类推。每部分卡牌内部的顺序不会因此操作而改变。

你需要用至多 $n$ 次操作将卡牌按 $1$ 到 $n$ 的顺序排列好，可以证明必然可以用至多 $n$ 次操作将卡牌排序。

对三副不同规模的卡牌的合法操作例子如下：

* 假设一副卡牌为[3 6 2 1 4 5 7]（3为第一张卡牌而7为最后一张卡牌），我们可以选择 $k=4$ ，将卡牌分为 $D_1$ =[3 6]，$D_2$ =[2 1 4]，$D_3$ =[5]，$D_4$ =[7]，进行操作。如果这样做，这副卡牌会变为 [7 5 2 1 4 3 6]。

* 假设一副卡牌为[3 1 2]，我们可以选择 $k=3$ ，将卡牌分为 $D_1$ =[3]，$D_2$ =[1]，$D_3$ =[2]，进行操作。如果这样做，这副卡牌会变为 [2 1 3]。

* 假设一副卡牌为[5 1 2 4 3 6]，我们可以选择 $k=2$ ，将卡牌分为$D_1$ =[5 1]，$D_2$ =[2 4 3 6]，进行操作。如果这么做，这副卡牌会变为 [2 4 3 6 5 1]。

## 样例 #1

### 输入

```
4
3 1 2 4```

### 输出

```
2
3 1 2 1
2 1 3```

## 样例 #2

### 输入

```
6
6 5 4 3 2 1```

### 输出

```
1
6 1 1 1 1 1 1```

## 样例 #3

### 输入

```
1
1```

### 输出

```
0```

# 题解

## 作者：7KByte (赞：2)

如果我们要排序，一个比较$\texttt{naive}$的想法是把$1$移动到最前面，把$2$移动到$1$后面，然后以此类推。

第一步很简单，我们只用在$1$前面划分一下，然后操作。

但是我们发现不能一次操作就将$2$移动到$1$后面，这也就意味着我们不能在$N$次操作内解决。

可是我们可以同时在$1$和$2$后面划分，操作之后序列的结尾是$21$，这时序列$……21$的。

我们发现刚好是倒序，也就是我们每进行一次操作会将序列反转一次。

这样就可以在$N$次操作内完成。


```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 55
using namespace std;
int a[N],b[N],n;
vector<int>c[N];
int top=0;
void maintain(){
	int hav=0;
	for(int i=0;i<(int)c[top].size();i++){
		for(int j=1;j<=c[top][i];j++)b[n-hav-c[top][i]+j]=a[hav+j];
		hav+=c[top][i];
	}
	rep(i,1,n)a[i]=b[i];
}
void out(){
	printf("%d\n",top);
	rep(i,1,top){
		printf("%d ",(int)c[i].size());
		for(int j=0;j<(int)c[i].size();j++)printf("%d ",c[i][j]);
		putchar('\n');
	}
}
void debug(){
	puts(" ");
	rep(i,1,n)printf("%d ",a[i]);
	puts(" ");
}
int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d",&a[i]);
	bool flag=1;int cur=0;
	rep(i,1,n)if(a[i]==1)cur=i;
	if(cur!=n){
		++top;
		c[top].push_back(cur);c[top].push_back(n-cur);
		maintain();
	}
	//debug();
	rep(i,2,n-1){
		if(flag){
			if(a[n-i+1]==i)continue;
			rep(t,1,n-i)if(a[t]==i)cur=t;
			++top;
			if(cur^1)c[top].push_back(cur-1);
			c[top].push_back(n-i+1-cur+1);
			rep(t,n-i+2,n)c[top].push_back(1);
			flag^=1;maintain();
		}
		else{
			if(a[i]==i)continue;
			rep(t,i+1,n)if(a[t]==i)cur=t;
			++top;
			rep(t,1,i-1)c[top].push_back(1);
			c[top].push_back(cur-i+1);
			if(cur^n)c[top].push_back(n-cur);
			flag^=1;maintain();
		}
		//cout<<"ss "<<flag<<endl;debug();
	}
	if(flag&&n>1){
		++top;rep(i,1,n)c[top].push_back(1);
		maintain();
	}
	out();
	return 0;
}
/*
g++ D.cpp -o D -Wall -std=c++11
*/
```

---

## 作者：SSerxhs (赞：2)

没排好序的时候必定存在 $i,j(i<j)$ 满足 $a_i=a_j+1$

那么考虑把原序列划分为 $[1,i-1],[i,k],[k+1,j],[j+1,n]$ 四段，可以把他们接上。 $k$ 的作用是防止已经被接上的断开，也就是每次操作原本连续段不能被分割，由于 $i,j$ 不属于同一连续段，必定存在合法分割点 $k$。反复操作即可。

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
pair<int,int> a[60],b[60];
int ans[60][60],ys[60];
int n,c,fh,i,j,k,pos,cnt,ct,tp;
inline void read(int &x)
{
	c=getchar();fh=1;
	while ((c<48)||(c>57))
	{
		if (c=='-') {c=getchar();fh=-1;break;}
		c=getchar();
	}
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
	x*=fh;
}
int main()
{
	read(n);
	for (i=1;i<=n;i++) {read(a[i].first);a[i].second=a[i].first;}
	while (1)
	{
		for (i=1;i<=n;i++) for (j=a[i].first;j<=a[i].second;j++) ys[j]=i;
		for (i=1;i<=n;i++) if ((a[i].first>1)&&(i<(j=ys[a[i].first-1])))
		{
			++cnt;tp=0;
			for (k=1;k<i;k++) tp+=a[k].second-a[k].first+1;
			if (tp) ans[cnt][++ans[cnt][0]]=tp;
			ans[cnt][++ans[cnt][0]]=a[i].second-a[i].first+1;tp=0;
			for (k=i+1;k<=j;k++) tp+=a[k].second-a[k].first+1;
			ans[cnt][++ans[cnt][0]]=tp;tp=0;
			for (k=j+1;k<=n;k++) tp+=a[k].second-a[k].first+1;
			if (tp) ans[cnt][++ans[cnt][0]]=tp;tp=0;
			for (k=j+1;k<=n;k++) b[++tp]=a[k];
			for (k=i+1;k<j;k++) b[++tp]=a[k];
			b[++tp]=a[j];b[tp].second=a[i].second;//printf("%d\n",a[i].first);
			for (k=1;k<i;k++) b[++tp]=a[k];n=tp;
			for (k=1;k<=n;k++) a[k]=b[k];
			break;
		}if (i>n) break;
		//for (i=1;i<=n;i++) printf("%d-%d ",a[i].first,a[i].second);puts("");
	}
	printf("%d\n",cnt);
	for (i=1;i<=cnt;i++)
	{
		printf("%d ",ans[i][0]);
		for (j=1;j<=ans[i][0];j++) printf("%d ",ans[i][j]);puts("");
	}
}
```

---

## 作者：Eznibuil (赞：0)

实际上，这道题是有更好的做法的，加强版名为 [	
Thanks to MikeMirzayanov](https://codeforces.com/gym/103260/problem/F)，限制 120 次操作次数。

考虑到操作的本质其实是 reverse 整个序列，然后 reverse 每个小块。如果每次都卡满 120 次操作，那么整个序列会被 reverse 120 次，等于没有。所以成功的将原问题转化为了每次操作 reverse 小块，构造一种方案。转化回去也很简单，隔一个就把整个操作块 reverse 一下，不再赘述。

那么考虑快速排序，假设当前分治的区间长度为 $x$，每次把小于等于中值和大于中值的分到两侧，然后递归。考虑把小于等于中值的记作 0，大于中值的记作 1，那么可以把整个分成若干个 01 连续段，比如：00011111010011101111...

这时候把第 2 段和第 3 段一起 reverse，第 6 段和第 7 段一起 reverse，就会变成：00001111110001111111...

所以就会让连续段数量减半。不停地做下去，在 $O(\log x)$ 次以内就可以把 0 和 1 完全分开。

最后递归处理分开的两侧即可。容易发现两侧互不影响，可以合在一起操作。因为递归 $O(\log n)$ 层，最后次数大概是 $O(\log^2n)$，分析一下大 O 里的常数大概是 $\frac12$，可以通过。

一些细节：特判 $n=1$，以及不要出现 $k=1$（在转化后的问题中 $k=1$ 是有意义的，但是原问题中是相当于没有操作）。
```cpp
#include<algorithm>
#include<iostream>
#include<vector>
int a[20001],lim;
std::vector<int>ans[121];
void solve(int d,int l,int r)
{
	bool f=1;
	for(int i=l+1;i<r;i++)
		f&=a[i-1]<a[i];
	if(f)
	{
		for(int i=d;i<lim;i++)
			for(int j=l;j<r;j++)
				ans[i].push_back(1);
		return;
	}
	const int m=l+r>>1;
	for(;;d++)
	{
		std::vector<int>c;
		for(int i=0,j=l;;i^=1)
		{
			int x=0;
			for(;j<r&&a[j]>m==i;j++)
				x++;
			c.push_back(x);
			if(j==r)
				break;
		}
		if(c.size()<3)
			break;
		for(int i=0,j=l;i<c.size();j+=c[i],i++)
			if((i&3)==1&&i<c.size()-1)
				continue;
			else if((i&3)==2)
				ans[d].push_back(c[i-1]+c[i]),std::reverse(a+j-c[i-1],a+j+c[i]);
			else if(c[i])
				ans[d].push_back(c[i]),std::reverse(a+j,a+j+c[i]);
	}
	return solve(d,l,l+r>>1),solve(d,l+r>>1,r);
}
int main()
{
	std::cin.tie(0)->sync_with_stdio(0);
	int n;
	std::cin>>n,lim=std::min(n&~1,120);
	for(int i=0;i<n;i++)
		std::cin>>a[i];
	if(n==1)
		return std::cout<<'0',0;
	solve(0,0,n),std::cout<<lim-(ans[0].size()==1);
	for(int i=ans[0].size()==1;i<lim;i++)
	{
		if(i&1)
			std::reverse(ans[i].begin(),ans[i].end());
		std::cout<<'\n'<<ans[i].size();
		for(int j:ans[i])
			std::cout<<' '<<j;
	}
	return 0;
}
```

---

## 作者：Acfboy (赞：0)

题目要求在 $n$ 次内完成排序，这引导着我们想到一次排上一个，要是能够第一次把 $1$ 放在最前面，第二次把 $2$ 放在第二个直到第 $n$ 次把 $n$ 放在最后一个就好了。

但试了试发现这没法做到，那就退而求其次，不要求顺序，只要把这几个数放在一起就可以了，即第一次其中有一块是 $1$，第二次有一块是 $12$ 或 $21$，第三次有一块是 $123$ 或 $321$，以此类推。

我一开始的想法是倒着来，因为要翻转嘛，那么从后往前排，但这样和直接从前往后没有什么区别。  
既然是翻转，那么就想个办法把连续的数放前面或反转后放后面，这样是可以做到的。举个例子，$3/15624 \to 1/562/43 \to 4/356/2/1 \to 1/2/3/564 \to 564321 \to \cdots$

容易发现，只要枚举当前新放进去的数，把小于它的数前面或后面划开，并把这个数前面或后面划开就可以了。

在实现上，我写了个结构体，维护了一个能自由切割和拼接的数组，使代码更清晰。

~~如果在 CF 赛场上遇到这题恐怕要写很久，因为开始想了个错误的 构造写了半天，代码细节也有些多。~~

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
struct twt {
    std::vector<int> a;
    twt() { a.clear(); }
    void push(int x) { a.push_back(x); }
    int find(int x) {
        int an = a.size() + 1;
        for (int i = 0; i < (int)a.size(); i++)
            if (a[i] == x) return i+1;
        return an;
    }
    twt sub(int l, int r) {
        twt an;
        for (int i = l; i <= r; i++) {
            if (i < 1 || i > (int)a.size()) return twt();
            an.push(a[i-1]);
        }
        return an;
    }
    twt operator + (twt y) {
        twt an = *this;
        an.a.insert(an.a.end(), y.a.begin(), y.a.end());
        return an;
    }
    bool fin() {
        for (int i = 0; i < (int)a.size(); i++)
            if (a[i] != i+1) return false;
        return true;
    }
    int size() { return a.size(); }
} now;
int n, x, ttt;
std::vector<int> pr, tmp;
std::vector<twt> dwd;
std::vector<std::vector<int> > ans;
std::ostream& operator << (std::ostream& out, twt x) {
    for (int i = 0; i < (int)x.a.size(); i++) out << x.a[i] << ' ';
    out << "#\n";
    return out;
}
int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> x, now.push(x);
    
    if (now.a[0] != 1) { 
        pr.clear(); pr.push_back(now.find(1)-1), pr.push_back(n-now.find(1)+1), ans.push_back(pr); 
        now = now.sub(now.find(1), n) + now.sub(1, now.find(1)-1);
    }
    
    for (int i = 2; !now.fin() && i <= n; i++) {
        pr.clear(), tmp.clear(), dwd.clear();
        for (int j = 1; j < i; j++) tmp.push_back(now.find(j));
        tmp.push_back(now.find(i));
        if (now.a[0] == 1) tmp.push_back(0); else tmp.push_back(1);
        if (now.a[0] == 1) tmp.push_back(n); else tmp.push_back(n+1);
        std::sort(tmp.begin(), tmp.end());
        for (int j = 1; j < (int)tmp.size(); j++)
            if (tmp[j] != tmp[j-1]) pr.push_back(tmp[j] - tmp[j-1]);
        ans.push_back(pr);
        for (int i = 0, l = 1; i < (int)pr.size(); l += pr[i], i++)
            dwd.push_back(now.sub(l, l+pr[i]-1)); 
        now = twt();
        for (int i = (int)dwd.size()-1; i >= 0; i--)
            now = now + dwd[i];
    }
   
    std::cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); i++, std::cout << '\n') {
        std::cout << ans[i].size() << ' ';
        for (int j = 0; j < (int)ans[i].size(); j++)
            std::cout << ans[i][j] << ' ';
    }
}
```

---

## 作者：jhdonghj (赞：0)

## 题意

给出一个长度为$n$的排列，乱序，每次操作可以选择$2\le k\le n$个数字$D_1,D_2,\cdots,D_k$，表示将这$n$个数分为大小依次为$D_1,D_2,\cdots,D_k$的部分，然后将每一部分顺序翻转，使得该序列变为$D_k,D_{k-1},\cdots,D_1$，构造最多$n$次操作使得该序列顺序。

## 题解

考虑从$2$到$n$依次把它们和$1$并到一起，通过手玩发现，我们可以用$n-1$次操作得到$1,2,\cdots,n$或者$n,n-1,\cdots,1$，如果是后面一种情况，我们再用依次操作使得整个序列翻转，即可完成构造。

考虑把$i+1$并到$i$旁边并且不使$1,2,\cdots,i$断开，分为$4$种情况讨论，设$j$为$i+1$的位置，$l,r$为$1,2,\cdots,i$所在的区间，且序列下标从$0$开始。

$case\ j <l\ \&\ a_l = i:\{D_i\}=\{j,l-j,1,1,\cdots,1,n-1-r\}$

$case\ j >r\ \&\ a_l=i:\{D_i\}=\{l,r-l+1,j-r,n-1-j\}$

$case\ j <l\ \&\ a_r=i:\{D_i\}=\{j,l-j,r-l+1,n-1-r\}$

$case\ j>r\ \&\ a_r=i:\{D_i\}=\{l,1,1,\cdots,1,j-r,n-1-j\}$

不难发现，这样子我们就把$i+1​$并到了$i​$的旁边，然后每次操作过后暴力维护$l,r​$即可。

## Code

```c++
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define Mp make_pair
#define pb push_back

using ll = long long;
using db = double;
using pii = pair<int, int>;
using vi = vector<int>;
mt19937 mrand(time(0));
ll get(ll r) { return ((ll)mrand() * mrand() % r + r) % r; }
ll get(ll l, ll r) { return get(r - l + 1) + l; }

vi go(vi a, vi step) {
    vector<vi> tp; vi res;
    for(int i = 0, j = 0; i < a.size(); j++) {
        int sz = step[j]; vi nw;
        while(sz) sz--, nw.pb(a[i]), i++;
        tp.pb(nw);
    }
    reverse(tp.begin(), tp.end());
    for(vi i : tp) for(int j : i) res.pb(j);
    return res;
}
signed main() {
    int n, l, r; cin >> n; vi a(n); vector<vi> ans;
    for(int& i : a) cin >> i;
    for(int i = 0; i < n; i++) if(a[i] == 1) l = r = i;
    for(int i = 2; i <= n; i++) {
        for(int j = 0; j < n; j++) if(a[j] == i) {
            if(a[l] == i - 1) {
                if(j < l) {
                    vi step;
                    if(j) step.pb(j);
                    step.pb(l - j);
                    for(int k = l; k <= r; k++)
                        step.pb(1);
                    if(r != n - 1) step.pb(n - 1 - r);
                    a = go(a, step), ans.pb(step);
                } else {
                    vi step;
                    if(l) step.pb(l);
                    step.pb(r - l + 1);
                    step.pb(j - r);
                    if(j != n - 1) step.pb(n - 1 - j);
                    a = go(a, step), ans.pb(step);
                }
            } else {
                if(j < l) {
                    vi step;
                    if(j) step.pb(j);
                    step.pb(l - j);
                    step.pb(r - l + 1);
                    if(r != n - 1) step.pb(n - 1 - r);
                    a = go(a, step), ans.pb(step);
                } else {
                    vi step;
                    if(l) step.pb(l);
                    for(int k = l; k <= r; k++)
                        step.pb(1);
                    step.pb(j - r);
                    if(j != n - 1) step.pb(n - 1 - j);
                    a = go(a, step), ans.pb(step);
                }
            }
            break;
        }
        l = r = -1;
        for(int j = 0; j < n; j++)
            if(a[j] == i || a[j] == 1)
                ~l ? r = j : l = j;
    }
    if(a[l] != 1) {
        vi step;
        for(int i = l; i <= r; i++)
            step.pb(1);
        a = go(a, step), ans.pb(step);
    }
    for(int i = 0; i < a.size(); i++) assert(a[i] == i + 1);
    for(vi i : ans) assert(i.size() >= 2);
    printf("%d\n", ans.size());
    for(vi i : ans) {
        printf("%d", i.size());
        for(int j : i) printf(" %d", j);
        puts("");
    }
    fprintf(stderr, "time=%.4f\n", (db)clock()/CLOCKS_PER_SEC);
    return 0;
}
```

---

