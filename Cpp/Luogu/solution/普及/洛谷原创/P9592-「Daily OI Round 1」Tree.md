# 「Daily OI Round 1」Tree

## 题目描述

给定三个正整数参数 $n,d,k$，你需要构造出一棵根节点为 $1$ 的树，满足这棵树有 $n$ 个节点，每个节点到根节点的距离和为 $d$，除了叶节点以外每个节点的**直接**儿子数量**至少** $k$ 个，且所有节点的最大深度最小。

**注意事项：**

- 距离：两个点之间的简单路径上的边的条数。
- 叶子节点：没有儿子的非根节点。
- 根节点深度为 $0$。

## 说明/提示

### **样例解释**

对于第二组样例的第二组询问，$n=5,d=6,k=2$，即需要构造出含有 $5$ 个节点，各个节点到节点 $1$ 的距离和为 $6$ 且除叶节点外的节点至少有 $k$ 个儿子节点。

下面是样例构造的图：

![](https://cdn.luogu.com.cn/upload/image_hosting/wgir5yt5.png)

其中编号为 $1,2,3,4,5$ 的点到根节点 $1$ 的距离分别为 $0,1,1,2,2$，和为 $6$，满足条件。而且非叶子节点 $1,3$ 都含有至少 $2$ 个儿子节点，可以证明这是所有合法构造中节点的最大深度最小的解法，在此处为 $2$。

### **数据范围**
  
**本题开启捆绑测试。**

|$\text{Subtask}$|分值|$n \le$|特殊性质|
| :-----------: | :-------------:|:-----------: |:-----------: |
|$0$|$5$|$10$|无|
|$1$|$5$|$20$|无|
|$2$|$5$|$10^5$|$k= n-1$|
|$3$|$5$|$10^5$|$k= n-1$ 或 $n-2$|
|$4$|$10$|$10^5$|$T=1$|
|$5$|$70$|$10^5$|无|

对于全部数据，保证：$1 \le n \le 10^5$，$1 \le T \le 10^5$，$1 \le k \le 10^5$，$\sum n \le 10^6$，$1 \le d \le 10^{10}$。

## 样例 #1

### 输入

```
3
5 4 1
5 6 1
5 7 1```

### 输出

```
YES
1 1 1 1
YES
1 1 3 3
YES
1 2 2 2```

## 样例 #2

### 输入

```
3
5 4 2
5 6 2
5 7 2```

### 输出

```
YES
1 1 1 1
YES
1 1 3 3
NO```

# 题解

## 作者：Acoipp (赞：9)

下面是出题人题解：

因为是到根节点的距离，所以设根节点深度为 $0$，其余节点同理，题意转化为了所有节点深度和为 $d$。

## subtask0

暴力可做，枚举每个点的父亲节点，时间复杂度 $O(n!)$。

## subtask1

节点数量为 $n$ 的树的节点的深度之和的种类很少，所以对于每一种深度搜索一下再剪个枝就可以了。

## subtask2

很显然，构造菊花图，然后判断深度之和是否等于 $d$ 即可。

## subtask3

还是构造菊花图，但是当 $n$ 很小的时候也可以构造出非菊花图的解，特判一下就可以了。

## subtask4

给随机数算法的分。

## subtask5

很显然，对于深度相同的节点，把它们的儿子都移到这个深度的某个节点下面是可行的，那么这时题目变成了每一层至少 $k$ 个节点，除开第一层。

题目还要求最大深度最小，枚举最大深度，然后每个深度（除了根节点所在深度）都先安排 $k$ 个点上去，剩下的点就随便选择一个小于等于当前枚举的深度安排就可以了。

如果剩下 $i$ 个点，当前枚举深度为 $x$，每层安排 $k$ 个点后深度之和 $d$ 减去这些点的深度后为 $y$。

那么有解当且仅当 $i \le y \le i \times x$，然后构造就很简单了。

确定每个点的深度，然后深度 $x$ 的所有点的父亲设为深度 $x-1$ 的某个节点即可。

深度最大为 $n$，时间复杂度不计算排序的话是 $O(\sum n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 100005
using namespace std;
ll t,k,n,d,i,j,l,p,o,temp,dep[N],tot,ans[N];
int main(){
	ios::sync_with_stdio(false);
	cin>>t;
	while(t--){
		tot=0;
		cin>>n>>d>>k;
		if(n==1){
			if(d==0){
				cout<<"YES\n";
				continue;
			}
			else{
				cout<<"NO\n";
				continue;
			}
		}
		temp=0;
		for(i=1;i<=n;i++){
			if(i*(i+1)/2*k>d||i*k+1>n) break;
			j = d-i*(i+1)/2*k;
			l = (n-i*k-1);
			if(l*i>=j&&l<=j){
				j=i*l-j;
				temp=1;
				cout<<"YES\n";
				for(p=1;p<=i;p++){
					for(o=1;o<=k;o++) dep[++tot]=p;
				}
				for(p=1;p<=l;p++) dep[++tot]=i;
				for(p=tot-l+1;p<=tot;p++){
					if(dep[p]-1>=j){
						dep[p]-=j;
						break;
					}
					else j-=(dep[p]-1),dep[p]=1;
				}
				sort(dep+1,dep+tot+1);
				ans[0] = 1;
				for(p=1;p<=tot;p++) cout<<ans[dep[p]-1]<<" ",ans[dep[p]]=p+1;
				cout<<endl;
				break;
			}
		}
		if(!temp) cout<<"NO\n";
	}
	return 0;
}
```

---

## 作者：Nwayy (赞：9)

upd on $2023.9.7$：按出题人意旨修改了省略号写法。

不难想的构造题。

---

首先可以发现一些性质。

所有节点与根距离和可以转换为所有节点的深度和，那么一定是 $1+\dots+1+2+\dots+2+\dots+x+\dots+x=d$ 的形式。

非叶子节点的儿子数至少为 $k$，即若树最大深度为 $m$，则深度 $dep \in [1,m-1]$ 的节点的儿子数至少为 $k$。

至此本题就转换成一个经典问题了，例如 $n=6$，$d=5$，$k=2$，我们可以构造出深度为 ```0 1 1 1 1 2 ``` 的树。

复杂度线性，细节比较多。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 1000005
#define int long long
int n,m,i,j,ans,d,k,a[N],s,l[N],flg,dep,t,f;
signed main(){
	scanf("%lld",&t);
	while(t--){
		for(i=1;i<=n;i++) a[i]=l[i]=0;
		scanf("%lld%lld%lld",&n,&d,&k),f=2,l[1]=1,flg=0,dep=1;
		while(1){
			int nxt=f;
			if(d==0) break;
			for(i=1;i<=k;i++){
				if(f>n){flg=1;break;}
				a[f++]=l[dep];	
			}	
			d-=k*dep;
			if((n-f+1)*dep>=d) break;
			else l[++dep]=nxt;
		}
		if(flg==1 || d<n-f+1) printf("NO\n");
		else{
			printf("YES\n");
			for(i=f;i<=n;i++){
				while(1){
					if(d<dep || d-dep<n-i) dep--;
					else break;
				}
				a[i]=l[dep],d-=dep;
			}
			for(i=2;i<=n;i++) printf("%lld ",a[i]);
			printf("\n");
		}
	}
	return 0;
}
```


---

## 作者：ayun (赞：5)

我来分享一种**贪心**的解法，不一定最优，但一定容易理解。

## 思路

首先，题目限定**所有节点的最大深度最小**，可以考虑依次增加树的深度。

当树的最大深度为 $1$ 时，构造的树如下图所示：

![结构1](https://cdn.luogu.com.cn/upload/image_hosting/ngps58qm.png)

此时每个节点到根的距离和 $sum=n-1$，移动任何一个节点到下一层 $sum$ 都会增加 $1$，如果此时 $sum$ 小于 $d$，就需要增大层数从而增大 $sum$ 的值。此外，任何一个移动到下一层的节点挂靠到哪一个节点上没有区别，如果挂靠到多个节点还要考虑 $k$ 的限制，不如只挂靠到一个节点，所以最后我们构造的树一定长这样：

![结构2](https://cdn.luogu.com.cn/upload/image_hosting/zyi944y1.png)

那么我们只需要用一个数组 $cnt$ 记录下每一层的节点个数，就可以得出最后的答案。

我们规定深度为 $1$ 的这一层为第一层。第一层不能满足需求、构造第二层时，第一层最少留下 $k$ 个节点，将该层剩下的全部移动到第二层，$sum$ 会增加 $cnt[1]-k$，此时的 $sum$ 也就是限定层数为 $2$ 时能得到的最大路径和，如果还小于 $d$，就用同样的方法继续增加层数，直到最大路径和 $sum$ 大于等于 $d$。

如果此时最大路径和 $sum$ 大于 $d$，记 $x=sum-d$，当前所在层为第 $now$ 层。需要将第 $now$ 层的节点移动到其他层，从而减小 $x$。将第 $now$ 层的一个节点移动到第一层，$x$ 可以减小 $now-1$。

同理，移动到其他层还可以减小 $now-2$、$now-3$ $\cdots$ $1$，优先将节点移动到上层的位置，最后一定可以将 $x$ 减为 $0$。

如果这个时候第 $now$ 层的节点数量小于 $k$，一定无解。因为我们优先将节点移动到上层，如果要保持第 $now$ 层节点数量为 $k$，那么移动到上层的节点就还需要移动到更高层，会使 $sum$ 小于 $d$；同时，满足深度更高的合法的树最大路径和一定大于 $d$，所以此时一定无解。

有解的情况下，每一层的父亲编号等于它上一层之前所有节点之和加一，也容易通过 $cnt$ 数组求出，最后输出即可。

## 代码

```cpp
//丑陋的考场代码
#include<iostream>
#include<cstring>
using namespace std;
#define int long long

//由于当k==1时，会出现一层只有一个节点，数的深度很高的情况，数组开2e4才能ac所有点
int cnt[20000],fa[20000],prv[20000];

signed main(void)
{
    ios::sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--)
    {
        int n,d,k;
        cin>>n>>d>>k;
        memset(cnt,0,sizeof(cnt));
        cnt[0]=1;
        cnt[1]=n-1;
        int now=1,sum=cnt[1],flag=1,len=(n-1)/k;
        if(len*k+len*(len-1)*k/2+((n-1)%k)*len<d) flag=0;
        while(sum<d&&flag)
        {
            if(cnt[now]<k)
            {
                flag=0;
                break;
            }
            cnt[now+1]=cnt[now]-k;
            cnt[now]=k;
            sum+=cnt[now+1];
            now++;
        }
        int x=sum-d,temp=1;
        while(x&&flag&&temp<now)
        {
            if(now-temp<=x)
            {
                cnt[temp]++;
                cnt[now]--;
                x-=now-temp;
            }
            else temp++;
        }
        if((cnt[now]<k||x)&&flag) flag=0;
        if(!flag) {cout<<"NO"<<endl;continue;}
        else
        {
            cout<<"YES"<<endl;
            prv[0]=1;
            for(int i=1;i<=now;i++) prv[i]=prv[i-1]+cnt[i];
            fa[1]=1;
            for(int i=2;i<=now;i++) fa[i]=prv[i-2]+1;
            for(int i=1;i<=now;i++)
            {
                for(int j=1;j<=cnt[i];j++) cout<<fa[i]<<' ';
            }
            cout<<endl;
        }
    }
    return 0;
}
```

---

## 作者：一只绝帆 (赞：4)

构造的关键是不要急于开始打代码，先构造一个初始的有利的“基底”。

这种有利的基底通常是不会将东西移来移去的，仅仅将元素添加上去就很简单。

所以我们先确定最终层数，这就需要我们求出这个层数对应的最大深度，我们枚举层数每次加 $k$ 个节点即可，多余节点如果要最大深度可以直接挂在最下面一个非叶子节点。

然后我们考虑用 $n-c$ 个节点凑出剩余所需深度，平均分配即可。

实现上的小技巧可以先构造一条从 $1$ 到 $mxd$ 的编号递增的链，这样我们需要什么深度的节点就直接把该深度作为编号作为这个点的父亲。

Code：
```cpp
#include<bits/stdc++.h>
#define gc getchar
#define F(i,a,b) for(int i(a),i##end(b);i<=i##end;i++)
using namespace std;using ll=long long;
ll read() {
	ll s=0;char c=gc(),w=0;
	while(c<'0'||c>'9') w|=c=='-',c=gc();
	while(c>='0'&&c<='9') s=s*10+(c^48),c=gc();
	return w?-s:s;
} const int N=1e5+5;
int n,k,fa[N];ll d;
void add(int x,int y) {
	fa[y]=x;
}
void print() {
	puts("YES");
	F(i,2,n) printf("%d ",fa[i]);puts("");
}
int main() {
	F(T,1,read()) {
		n=read();d=read();k=read();
		if(n==1) {
			if(d==0) {puts("YES\n");}
			else {puts("NO");}
			continue;
		}
		ll now=1,mxd=0,sumd=0;
		while(now<=n&&sumd+(n-now)*mxd<d) {
			now+=k;
			sumd+=(++mxd)*k; 
		} 
		if(sumd+n-now>d||sumd+(n-now)*mxd<d) {puts("NO");continue;}
		ll yet=d-sumd,cnt=mxd;
		F(i,1,mxd) F(j,1,k-1) add(i,++cnt);
		F(i,1,mxd-1) add(i,i+1);add(mxd,++cnt);
		if(now==n&&sumd==d) {print();continue;}
		ll c=cnt,tmp=(yet)/(n-c);
		F(i,1,yet-tmp*(n-c)) add(tmp+1,++cnt);
		F(i,1,n-c-(yet-tmp*(n-c))) add(tmp,++cnt);
		if(cnt!=n) {puts("NO");continue;}print();
	}
	return 0;
}

```

---

## 作者：佬头 (赞：3)

## Description
给定三个正整数 $n,d,k$，请你构造出一棵以 $1$ 为根节点且节点数为 $n$ 的[**树**](https://www.luogu.com.cn/problem/P9592)，使每个节点到根节点的距离和为 $d$，除了叶节点以外每个节点的**直接**儿子数量**至少** $k$ 个，且所有节点的最大深度最小。根节点深度为 $0$。

对于每次询问，如果有解，第一行输出 `YES`，然后一行 $n-1$ 个正整数，第 $i$ 个正整数 $a_i$ 表示 $a_i$ 是 $i+1$ 的父亲节点，且 $a_i\leq i$；如果无解，输出 `NO`。

如果有多组合法的答案，任意输出其中一组。

## Solution
很显然，对于深度相同（不为 $0$）的所有节点，我们可以把它们都移到同一个父节点的下面，这样限制条件就变成了每个深度（不为 $0$）的节点**至少**有 $k$ 个。

因为要让节点的最大深度最小，则我们需要先找出一个最小的深度 $dep$ 满足
$$(dep\times(dep+1)\times k)\div2+n-dep*k-1\le d\le (dep\times(dep+1)\times k)\div2+dep*(n-dep*k-1)$$
其中 $(dep\times(dep+1)\times k)\div2$ 表示构造一棵深度为 $dep$ 且每个深度（不为 $0$）都只有 $k$ 个节点的树的节点深度之和；$n-dep*k-1$ 表示构造完这么一棵树后还剩下的节点数（$dep\times k+1\le n$），而将他们插入这棵树后对节点深度之和的贡献最小为 $n-dep*k-1$（全为根节点的儿子节点），最大为 $dep\times(n-dep*k-1)$（全为叶子节点）。

可以用**二分**解决（下面代码中 $n$ 的值为原值减一）：
```cpp
int lft = 1, rt = n / k, dep = 0;
while(lft <= rt){
	int mid = lft + rt >> 1;
	if(((long long)mid * (mid + 1) * k >> 1) + (long long)mid * (n - mid * k) < d) dep = mid, lft = mid + 1;
	else rt = mid - 1;
}
++ dep;
```
由于不影响总体的时间复杂度，也可以选择直接枚举 $dep$：
```cpp
for(dep = 1; dep * k <= n && ((long long)dep * (dep + 1) * k >> 1) + (long long)dep * (n - dep * k) < d; ++ dep) continue;
```
在找出这么一个 $dep$ 之后（若不存在就输出 ``NO``），可以借助**计数排序**的思想按照深度（不为 $0$）对节点进行排序。每个深度（不为 $0$）的节点数初始为 $k$，然后将剩下的节点数全设为根节点的儿子节点，再将其下放并使节点深度之和为 $d$。

时间复杂度 $\mathcal{O}(\sum n)$（由于输出就得达到这个复杂度，二分就显得没什么意义了）。

## Code
```cpp
#include <iostream>
using namespace std;
const int N = 100005;
int n, k, siz[N], dep;
long long d;
long long read(){
	long long x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(int x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	for(int _ = read(); _ >= 1; -- _){
		n = read() - 1, d = read(), k = read();
		//[找dep的代码]
		if(((long long)dep * (dep - 1) * k >> 1) + n > d || dep * k > n){
			puts("NO");
			continue;
		}
		puts("YES");
		d -= ((long long)dep * (dep - 1) * k >> 1) + n;
		for(int i = 1; i <= dep; ++ i) siz[i] = k;
		siz[1] += n - dep * k;
		if(d >= dep) siz[dep] += d / (dep - 1), siz[1] -= d / (dep - 1), d %= dep - 1; //直接下放为叶子节点
		if(d) ++ siz[1 + d], -- siz[1];
		for(int i = 1, pre = 1; i <= dep; ++ i){
			for(int j = 1; j <= siz[i]; ++ j) write(pre), putchar(' ');
			pre += siz[i];
		}
		puts("");
	}
	return 0;
}
```

---

## 作者：sbno333 (赞：3)

这是一道经典绿题。~~所以为啥比赛主页显示黄？~~

比较具有挑战性，~~适合中国OIer水掉。~~

本题按照小编的函数由简到难进行讲解

这道题大制作法如下：

首先，对于主函数，我们可以来进行多组测试用例操作。
```cpp
int main(){
	long long T;
	cin>>T;
	while(T--){
		_main();
	}
}
```

对于次主函数，即输出答案，我们可以作输入操作，不难发现根节点包含在 $n$ 个节点之内，很碍事，给它直接减掉。

```cpp
long long _main(){
	long long n,d,k;
	cin>>n>>d>>k;
	er(n-1,d,k);
	return 0;
} 
```

接下来是重点，即寻找答案。

我们可以找最小深度，这里采用二分查找，并进行判断，最后输出。

```cpp
void er(long long n,long long d,long long k){
	if(k>n){//由于根节点不算叶节点，所以至少要分出k个节点
		cout<<"NO"<<endl;
		return;	
	}
	if(n==0){//题目果然有骗人成分，输入的n为一就是无解，虽然这句话因为上头的那句话没有用，但这里特此提醒大家不要轻信题目
		cout<<"NO"<<endl;
		return;
	}
	if(n==d){//直接从根分叉
		cout<<"YES"<<endl;
		for(long long i=1;i<=n;i++){
			cout<<"1 ";
		}
		cout<<endl;
		return;
	}
	long long l,r;
	l=2;
	r=1000000;
	r*=10000;//将r复制成10的10次方，由于害怕出问题，就这么干了
	r+=9;//多点，以防万一
	while(l<r){
		long long mid;
		mid=(l+r)/2;
		if(dog(mid,n,d,k)){//dog函数会返回3种值：0,1,2，表示深度过低，深度合法，深度过高，时间复杂度O(1)
			r=mid-dog(mid,n,d,k)+1;//由于dog函数不慢，所以干脆再算一遍，懒得多写了，本种情况为合法或过高
		}else{
			l=mid+1;//过低
		}
	}
	if(dog(r,n,d,k)==1){//在判断一遍是否合法
		cout<<"YES"<<endl;
		pr(r,n,d,k);//输出，该函数类似dog函数
	}else{
		cout<<"NO"<<endl;//二分后都不合法，显然，无答案
	}
}
```

接下来就是疑点难点，判断函数，这个函数好像花了我一个半小时,思路就是先用最少的点搭到对应深度，即除了最后一层，每一层都选一个节点分支，$k$ 个叉，然后计算需要加的深度，剩的点，进行加点操作，判断是否能加即可。

```cpp
long long dog(long long s,long long n,long long d,long long k){
	long long u,v,w;
	u=s*k;//至少需要的总点数
	if(u>n){//点不够用
		return 2;//深度降低可能就好了
	}
	u=n-u;//计算剩的点
	v=s*s+s;
	v/=2;
	v*=k;//由于每层都有k个点，计算深度直接用等差数列公式，计算k+2k+3k+4k...+sk,此处换成(1+2+3+4...+s)*k
	if(v>d){//给的深度d不够
		return 2;
	}
	v=d-v;//计算剩的深度
	w=u*s;//假设剩的点都开得最大深度
	if(w<v){//开成最大都不够填，肯定填不了
		return 0;//深度应当提升，使得v变小
	}
	w-=v;//得到要在最大的基础上减去的深度
	if(u>v){//即使每个点都是1，都显得多，导致装不下那么多深度，至于为什么放最后面，纯属脑子刚转过弯
		return 2;
	}
	return 1;//剩下不难证明一定有办法使得成立，具体看下一个函数，pr。
}
```
接下来是最难得函数，前半部分是由上面的函数复制粘贴的，不讲了，主要看后半部分，该函数是构造数的场所。

```cpp
void pr(long long s,long long n,long long d,long long k){
	long long u,v,w,f3;
	f3=0;
	u=s*k;
	u=n-u;
	v=s*s+s;
	v/=2;
	v*=k;
	v=d-v;
	w=u*s;
	w-=v;//不用特判了，应为上面已经判了
   //先构建到深度为s
	for(long long i=0;i<s;i++){//深度-1
		for(long long j=0;j<k;j++){//该层深度第j+1个点
			cout<<i*k+1<<" ";//有上一深度的第一个点作父亲
			++f3;//计算输出了几个点
		}
	}
	long long f1,f2;
	f1=w/(s-1);//每个剩的点从最大深度s到最小1深度减少s-1的深度，把能减的减了
	f2=w%(s-1);//可能存在某点不用减到1
	f2=s-f2;//计算剩的点的层数
	f1=u-f1;//最大深度的数量，特别的，若最开始的余数f2不为0，就是最大深度数量+1（多了个f2）
	if(f2!=s){//最开始不为0，即f2!=0,s-f2!=s-0
		f1--;
	}
	while(f1--){//f1个
		cout<<(s-1)*k+1<<" ";//深度为s的点查到s-1中第一个点
		++f3;
	}
	if(f2!=s){//f2有存在就输出
		cout<<(f2-1)*k+1<<" ";
		++f3;
	}
	for(long long i=f3+1;i<=n;i++){//剩下的点深度为1，所以父亲为根
		cout<<1<<" ";
	}
	cout<<endl;	
}
```

~~好吧，这道题我调了约两个半小时，别的题都没时间了，欢迎大家喷~~。

---

## 作者：Nuyoah_awa (赞：3)

### 题目大意

构造一课树，使得这棵树共 $n$ 个节点，每个节点到根节点的距离之和为 $d$，除叶子节点外，每个节点的儿子个数不少于 $k$。

### 题目分析

首先，我们来观察这棵树的性质，如果我们把所有距根节点距离为 $x$ 的点全部连接到一个距根节点距离为 $x-1$ 的点上，这棵树所满足的所有条件不会变。

于是，我们可以把最终的树做些修改，使其变成下图的样子：

![P9592-1](https://s1.ax1x.com/2023/09/03/pPDUvWQ.png)

然后，我们的问题就变成了最大深度为多少的树可以满足所有条件。我们发现，对于任意深度，我们都可以 $\mathcal O(1)$ 判断是否可行，于是我们不妨暴力枚举最大深度。

对于判断，首先我们设深度为 $x$，其次我们知道除第一层外每层至少 $k$ 个节点，也就是说这棵树最少 $x \times k + 1$ 个节点，于是当 $x \times k + 1 > n$ 时，就没必要继续枚举了，直接输出 `NO`；然后，我们需要使这棵树深度和为 $d$，我们已知的这些点的深度也是固定的，已知点深度和为 $\dfrac{x \times (x + 1)}{2} \times k$，除去这些点，我们还有 $n - x \times k - 1$ 个点，剩余点的深度和最小为 $n - x \times k - 1$（即所有点连在 $1$ 下的情况），最大为 $x \times (n - x \times k - 1)$（即所有点在最后一层的情况）。我们需要满足 $n - x \times k - 1 \le d$ 且 $x \times (n - x \times k - 1) \ge d$，说明 $x$ 层是可以的。

接着，在知道了最大深度后，我们的任务就是构造了。

对于构造，我们先构造出一棵最基础的树来，如下图：

![P9592-2](https://s1.ax1x.com/2023/09/03/pPDa3FO.png)

我们知道已有深度和为 $\dfrac{x \times (x + 1)}{2} \times k$，我们需要将剩余的 $n - x \times k - 1$ 个点连入这棵树，并且深度和为 $d$，这里我们可以对于每个点，先连向 $1$，然后依次枚举每个点，若剩余 $d \ge x - 1$，我们将这个点放入最后一层，否则我们将其放入剩下的 $d + 1$ 层，直到 $d = 0$ 为止。

对于一些细节，我们可以快速求出深度为 $i$ 的点的父亲节点为 $(i - 2) \times k + 2$，特别的，深度为 $1$ 的父亲节点为 $1$。我们已知节点的数量为 $x \times k + 1$，（记得开 `long long`）。 

最后判断的时间复杂度为 $\mathcal O(n)$，构造（输出）的时间复杂度为 $\mathcal O(n)$ 的，所以总时间复杂度为 $\sum n$。

### code
```cpp
#include <iostream>
#include <cstdio>
#define int long long
using namespace std;
const int N = 1e6 + 5;
int T, n, d, k, fa[N], ans, deep[N], m;
void print()
{
	int tmp = ans * k + 1;
	d -= ((ans + 1) * ans / 2) * k;
	n -= tmp;
	for(int i = tmp + 1;i <= tmp + n;i++)
		deep[i] = 1, d--;
	for(int i = tmp + 1;i <= tmp + n && d > 0;i++)
	{
		if(d >= ans - 1)
			deep[i] = ans, d -= (ans - 1);
		else
			deep[i] = d + 1, d = 0;
	}
	for(int i = tmp + 1;i <= tmp + n;i++)
		fa[i] = deep[i] == 1 ? 1 : (deep[i] - 2) * k + 2;
	printf("YES\n");
	for(int i = 2;i <= m;i++)
		printf("%lld ", fa[i]);
	printf("\n");
	return ;
}
bool check()
{
	for(int i = 1;i <= n;i++)
	{
		if(((i+1)*i/2) * k > d || i * k + 1 > n)
			return false;
		for(int j = 1;j <= k;j++)
			fa[(i-1)*k+1+j] = i == 1 ? 1 : (i - 2) * k + 2;
		ans = i;
		if(((i+1)*i/2) * k + (n - 1 - i * k) <= d && ((i+1)*i/2) * k + i * (n - 1 - i * k) >= d)
			return true;
	}
	return false;
}
signed main()
{
	scanf("%lld", &T);
	while(T--)
	{
		scanf("%lld %lld %lld", &n, &d, &k);
		m = n;
		if(n == 1)				// n = 1 特判
		{
			if(d == 0)
				printf("YES\n");
			else
				printf("NO\n");
			continue;
		}
		if(check())
			print();
		else
			printf("NO\n");
	}
	return 0;
}
```

---

## 作者：Fislett (赞：2)

首先，我们知道，每一个节点的父亲是谁不重要，重要的只是每一层有多少个，既然如此，那我们把同一层的点挂在统一个父节点上就能让我们的之后的操作最简便。

进一步思考，对于一个固定的最大深度，他有一个连续的距离和可以拼凑出来，具体的，对于一个深度 $x$，他所对应区间是 $[k \times (1+2+…+x)+n-1-k \times x,k \times (1+2+…+x)+(n-1-k \times x) \times x]$。那么在节点足够的情况下，这个区间的右端点先然是随 $x$ 增大而增大的。

既然如此，我们二分最小的层数使得上界超过 $d$，然后把其他的点放到树上使其刚好等于 $d$ 即可。

注意判断下界大于 $d$ 无解的情况。

# $CODE$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
inline int read()
{
    int x = 0, flag = 1; char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-') flag = -1; else x = (c ^ 48); c = getchar();
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return flag * x;
}
inline void print(int x)
{
    if (x < 0) putchar('-'), x = ~(x - 1);
    if (x > 9) print(x / 10);
    putchar(x % 10 + 48);
}
int n, k, T, cnt[100005], cur, d;
inline int Calc(int x) {return (1 + x) * x >> 1;}
inline int calc(int x)
{
    x --;
    return k * Calc(x) + (n - k * x - 1) * x;
}
signed main()
{
    T = read();
    while (T --)
    {
        n = read(), d = read(), k = read();
        for (int i = 1; i <= n; ++ i) cnt[i] = 0;
        if (n == 1) {puts("NO"); continue;}
        int l = 2, r = (n - 1) / k + 1, res = -1;
        // cout << calc(2) << ' ';
        while (l <= r)
        {
            int mid = l + r >> 1;
            if (calc(mid) < d) l = mid + 1;
            else r = mid - 1, res = mid;
        }
        // cout << res << ' ';
        if (res == -1) {puts("NO"); continue;}
        if (k * Calc(res - 1) + n - 1 - k * (res - 1) > d) {puts("NO"); continue;}
        int tmp = n - k * (res - 1) - 1;
        d -= k * Calc(res - 1);
        if (tmp) cnt[d / tmp] = tmp - d % tmp, cnt[d / tmp + 1] = d % tmp;
        cur = 1;
        puts("YES");
        for (int i = 1; i < res; ++ i)
        {
            int x = cnt[i] + k, xx = x;
            while (x --) print(cur), putchar(' ');
            cur += xx;
        }
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：Aventurine_stone (赞：0)

## 1. 题目分析
读完题，很明显的一道构造题，~~不会有人认为是动态规划吧~~。出题人还设了一个坑，$n$ 为 $1$ 时必定无解，这一点稍微读下题便能想到。
## 2. 题目做法
本题构造分为三个部分。  
第一部分，特判。  
当 $k$ 大于等于 $n$ 时，此时必定无解，当 $d$ 大于其最大值一半时，也必定无解，此时我们只需要输出无解情况便可。  
第二部分，往下放点。  
我们先假设除根结点外的点父节点都是根节点，这样总距离就为 $n - 1$，如果 $d$ 小于 $n - 1$ 则无解，等于则直接输出。接下来如果此层节点数大于 $2 \times k$，就往下放点，记录两个值，一个是刚好放 $k$ 个点时的距离和，第二个是上一层刚好放到只剩 $k$ 个点时的距离和。若 $d$ 小于这两个值，则进入第三部分。若 $d$ 处于两值之间，计算需要放多少个点后便可输出。若大于两值，则继续往下放点，若不能继续放点则无解。  
第三部分，向上放点。  
与第二部分增加距离和差不多，只不过这部分是减少距离和，注意一下边界问题就行了。
## 3. 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
inline long long read()
{
	long long x=0;
	char c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
		x=(x<<1)+(x<<3)+c-'0',c=getchar();
	return x;
}
long long T,n,k;
long long d,s,minn,maxx,t,a[N];
void print()
{
	t=1;
	for(int i=1;a[i];i++)
	{
		for(int j=1;j<=a[i];j++)
		{
			printf("%lld ",t);
		}
		t+=a[i];
	}
	putchar(10);
}
bool p;
int main()
{
//	freopen("t.in","r",stdin);
//	freopen("t.out","w",stdout);
	T=read();
	while(T--)
	{
		n=read(),d=read(),k=read();
		if(k>=n||d>5e9)
		{
			printf("NO\n");
			continue;
		}
		for(int i=1;i<=n;i++)
			a[i]=0;
		a[1]=n-1;
		s=n-1;
		if(s>d)
		{
			printf("NO\n");
			continue;
		}
		if(s==d)
		{
			printf("YES\n");
			print();
			continue;
		}
		p=0;
		for(int i=2;i<n;i++)//往下放点 
		{
			if(a[i-1]<k*2)
				break;
			minn=s+k,maxx=s+a[i-1]-k;
			if(d>=minn&&d<=maxx)
			{
				p=1;
				printf("YES\n");
				t=d-s;
				a[i]=t;
				a[i-1]-=t;
				print();
				break;
			}
			else if(d<minn)//向上放点 
			{
				a[i]=k;
				a[i-1]-=k;
				s=minn;
				for(int j=i-1;j>1;j--)
				{
					minn=s-a[j]+k;
					if(minn<=d)
					{
						p=1;
						printf("YES\n");
						t=s-d;
						a[j]-=t,a[j-1]+=t;
						print();
						break;
					}
					s=minn;
					a[j-1]+=a[j]-k,a[j]=k;
				}
				break;
			}
			a[i]=a[i-1]-k,a[i-1]=k;
			s=maxx;
		}
		if(!p)
			printf("NO\n");
	}
	return 0; 
}
```

---

## 作者：Hyc_ (赞：0)

此题要让“所有节点的最大深度最小”，所以考虑二分答案。

二分初始 $l=1,r=(n-1)\div k$，因为每层至少放 $k$ 个节点还要去掉根节点。

对于每个深度，先把大于 $0$ 的每层放 $k$ 个节点，保障“除了叶节点以外每个节点的直接儿子数量至少 $k$ 个”，然后考虑多余的节点，全部与根节点相连时，深度和最小，全部放在最下面一层深度和最大，很容易发现最大值和最小值之间的每一个值都能被取到。

二分出最小深度后考虑构造方案：

从第一层往后，每层先放 $k$ 个节点，每个节点连接上层的第一个节点，这样操作完后还会剩 $n'$ 个点，$d'$ 条边。然后再从大到小枚举深度 如果 $n > 0$ 且 $d'-dep \ge n'-1$ 那么就在这层加点至不满足条件，这样也能保证 $a_i \le i$。

然后这题就做完了。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
template<typename T>inline void read(T &ret){
	ret=0;T fh=1;char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')fh=-1;ch=getchar();}
	while(isdigit(ch))ret=(ret<<1)+(ret<<3)+(ch^48),ch=getchar();
	ret*=fh;
}
template<typename T>inline void write(T ret,bool flag){
	if(ret<0)putchar('-'),ret*=-1;
	static char out[25];int top=0;
	do{out[++top]=(ret%10)^48,ret/=10;}while(ret);
	for(;top;--top)putchar(out[top]);
	putchar(flag?' ':'\n');
}
ll n,d,k;
inline int get(int x){//获取第x层最左侧的节点
	if(!x)return 1;
	return (x-1)*k+2;
}
inline void print(int dep){//构造，输出方案
	for(int i=1;i<=dep;++i)
		for(int j=1;j<=k;++j)
			write(get(i-1),1);
	d-=k*(dep+1)*dep/2,n-=dep*k+1;
	for(int i=dep-1;n&&~i;--i)
		while(n&&d-i-1>=n-1){
			write(get(i),1);
			d-=i+1,--n;
		}
	puts("");
}
inline void solve(){//二分答案
	int l=1,r=(n-1)/k,mid,ret=0;
	ll mn,mx,cnt;
	while(l<=r){
		mid=(l+r)>>1;
		cnt=n-1-mid*k;
		mn=k*(1+mid)*mid/2+cnt;
		mx=k*(1+mid)*mid/2+cnt*mid;
		if(mn<=d&&d<=mx)
			ret=mid,r=mid-1;
		else if(mx<=d)l=mid+1; 
		else if(mn>=d)r=mid-1;
	}
	if(ret){
		puts("YES");
		print(ret);
	}
	else puts("NO");
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	ll T;read(T);
	while(T--){
		read(n);read(d);read(k);
		solve();
	}
	return 0;
}
```

---

