# Job Interview

## 题目描述

### 题意翻译
Monocarp 要开设一家 IT 公司。他想招聘 $n$ 名程序员和 $m$ 名测试员。

共有 $n+m+1$ 名候选人，第 $i$ 个人的到达时间为 $i$。

第 $i$ 名候选人的编程技能为 $a_i$ ，测试技能为 $b_i$ （保证 $a_i\not=b_i$）。

公司的能力定义为所有程序员的编程能力与所有测试员的测试能力之和。

形式化的讲，若招聘的程序员集合为 $s$，测试员集合为 $t$，则公司的能力为 $\sum\limits_{i\in s}a_i+\sum\limits_{j\in t}b_j$。

Monocarp 会按照候选人到达的时间顺序为他们分配工作。

对于第 $i$ 个人，招聘规则为：
1. 尝试将 $i$ 分配到最适合 $i$ 的职位，也就是若 $a_i>b_i$，则让他成为程序员，反之同理。
2. 如果该职位已经招满了，就把 $i$ 分配到另一职位上。

你的任务是，对于每个 $i$，输出若这个人不来的情况下，公司的能力值。

## 样例 #1

### 输入

```
4
1 0
2 1
1 2
0 2
4 5 5
5 4 1
1 2
2 1 5 4
5 2 3 1
3 1
4 3 3 4 1
5 5 4 5 2```

### 输出

```
1 2 
5 6 9 
8 11 11 12 
13 13 13 12 15```

# 题解

## 作者：Louis_lxy (赞：15)

## 前言

一个比较好想的 dp。

注：$id_i$ 表示第 $i$ 个人的岗位，$f_i$ 表示不选第 $i$ 个人可以多获得的价值，$ca$ 表示被迫选测试员的人，$cb$ 表示被迫选程序员的人。

## 思路

首先，我们可以先默认不选最后一个，求出一个答案 $res$，直接模拟即可。

然后，发现如果改为不选第 $i$ 个人，实际上就是让下一个原本要选 $id_i$ 但是没法选的人选 $id_i$ 然后还要有下一个人顶替他选的岗位，以此类推。

然后就考虑 dp，显然，如果不选第 $i$ 个人，那么原本被迫不选 $id_i$ 的人又可以选了，相当于不选那个人，然后他对价值的贡献就是 $f_{ca}+a_{ca}-b_{ca}$（默认原先被迫选测试员，被迫选程序员同理），解释一下 dp 方程：首先，改变了他的岗位，相当于不选他（不对后面造成影响），然后改变增加的价值为 $a_{ca}-b_{ca}$。

那么推出 $f$ 后答案是什么呢，首先，不选第 $i$ 个人，要减去他原先的贡献，再加上不选会多的贡献，最终答案就是 $res-a_i+f_i$（默认他原先选程序员）。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
int a[N], b[N];
long long f[N];
bitset<N> id;

int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n, m, ca = 0, cb = 0;
		long long res = 0;
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n + m + 1; ++i) scanf("%d", &a[i]);
		for (int i = 1; i <= n + m + 1; ++i) scanf("%d", &b[i]);
		for (int i = 1; i <= n + m; ++i)
		{
			if (ca == n) res += b[i], id[i] = 0;
			else if (cb == m) res += a[i], id[i] = 1;
			else if (a[i] > b[i]) res += a[i], id[i] = 1, ++ca;
			else res += b[i], id[i] = 0, ++cb;
		}
		ca = n + m + 1, cb = n + m + 1;
		f[n + m + 1] = 0;
		for (int i = n + m; i; --i)
		{
			if (ca == n + m + 1 && id[i]) f[i] = f[ca] + a[ca];
			else if (cb == n + m + 1 && !id[i]) f[i] = f[cb] + b[cb];
			else if (id[i]) f[i] = f[ca] + a[ca] - b[ca];
			else f[i] = f[cb] + b[cb] - a[cb];
			if (id[i] && b[i] > a[i]) cb = i;
			else if (!id[i] && b[i] < a[i]) ca = i;
		}
		for (int i = 1; i <= n + m; ++i)
			printf("%lld ", res - (id[i] ? a[i] : b[i]) + f[i]);
		printf("%lld\n", res);
	}
	return 0;
}
```

---

## 作者：2huk (赞：8)

显然枚举 $i$ 表示这个人没了。

思考若没有

> 如果该岗位已经招满了，就把 $i$ 分配到另一岗位上。

的规则，显然我们会选择 $i$ 更适合的岗位。

有这个限制后，一定也存在一个最长前缀 $[1, j]$ 表示这些人是按照自己适合的选的。也就是说，**在这些人参与招聘时，两个岗位都未招满**。

我们可以二分这个前缀长度 $j$。显然 $[1, j]$ 结束后，**一定存在一个岗位招满了**。那么 $[j+1, n+m+1]$ 就只能在另一个没有招满的岗位上工作了。

具体实现上需要维护若干个前/后缀和。见代码。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

const int N = 400010;

int n, m, a[N], b[N], sum[N], pre[N], A[N], B[N];

void solve() {
	cin >> n >> m;
	
	for (int i = 1; i <= n + m + 1; ++ i ) cin >> a[i];
	for (int i = 1; i <= n + m + 1; ++ i ) cin >> b[i];
	
	for (int i = 1; i <= n + m + 1; ++ i ) sum[i] = sum[i - 1] + (a[i] > b[i]);
	for (int i = 1; i <= n + m + 1; ++ i ) pre[i] = pre[i - 1] + max(a[i], b[i]);
	
	A[n + m + 2] = B[n + m + 2] = 0;
	for (int i = n + m + 1; i; -- i ) A[i] = A[i + 1] + a[i], B[i] = B[i + 1] + b[i];
	
	for (int i = 1; i <= n + m + 1; ++ i ) {
		int l = 0, r = n + m + 1, pos = -1;
		int P, Q;
		
		while (l <= r) {
			int mid = l + r >> 1;
			
			int p = sum[mid], q = mid - p;
			if (mid >= i) (a[i] > b[i] ? p : q) -- ;
			
			if (p >= n || q >= m) {
				P = p, Q = q;
				r = mid - 1, pos = mid;
			}
			else {
				l = mid + 1;
			}
		}
		
		int res = pre[pos] - (pos >= i ? max(a[i], b[i]) : 0ll);
		res += Q == m ? A[pos + 1] - (pos + 1 <= i ? a[i] : 0) : B[pos + 1] - (pos + 1 <= i ? b[i] : 0);
		
		cout << res << ' ';
	}
	
	cout << '\n';
}

signed main() {
	int T;
	cin >> T;
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：紊莫 (赞：5)

标签：树状树组

比较无脑的 $O(n \log n)$ 做法。

对于每个人消失的情况，一定是一段前缀选 $\max(a, b)$，一段后缀全选 $a$ 或 $b$，可以二分出这个位置，然后利用树状树组维护。

树状树组上二分的话即可做到 $O(n \log n)$。

---

## 作者：yangshengyu0719 (赞：4)

此题鉴定为**模拟**（但也算是和 DP 挂钩）。

## 思路
思路很简单，就是模拟！

$l_{0/1}$：原本**该成为**程序员或测试员，实际上也**成为了**程序员或测试员的**最后一个人**。

$f_{0/1}$：原本**该成为**程序员或测试员，实际上**没能成为**程序员或测试员的**第一个人**。

$cnt_{0/1,i}$：前 $i$ 个人中，程序员或测试员分别的个数。

只要求得这些信息，我们就可以“愉快”的开始模拟了（细节请看代码）！

最后讲个笑话，我这个菜鸡只打了 39 行代码，却调了足足一下午。

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long//不开long long见祖宗
using namespace std;
const int N=2e5+5;
int test,n,m,ans,End;
int a[2][N],l[2],f[2],cnt[2][N];
int job(int x){return cnt[0][x]==cnt[0][x-1];}
int val(int x){return a[job(x)][x];}
void add(int x,int i){
	cnt[x][i]=cnt[x][i-1]+1;
	cnt[x^1][i]=cnt[x^1][i-1];
	ans+=a[x][i];
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>test;
	while(test--){
		cin>>n>>m,End=n+m+1,ans=0;
		for(int i=1;i<=End;i++) cin>>a[0][i];
		for(int i=1;i<=End;i++) cin>>a[1][i];
		for(int i=1;i<End;i++) add(a[0][i]>a[1][i]?cnt[0][i-1]>=n:cnt[1][i-1]<m,i);
		l[0]=l[1]=f[0]=f[1]=End;
		for(int i=0;i<End;i++){
			if(l[0]==End&&cnt[0][i]==n) l[0]=i;
			if(l[1]==End&&cnt[1][i]==m) l[1]=i;
		}
		for(int i=0;i<End;i++){
			if(a[0][i]>a[1][i]&&job(i)){f[0]=i;break;}
			if(a[0][i]<a[1][i]&&!job(i)){f[1]=i;break;}
		}
		for(int i=1;i<End;i++){
			if(a[0][i]<a[1][i]) cout<<ans+(i<=l[1]?a[1][f[1]]-a[0][f[1]]:0)-val(i)+a[0][End]<<' ';
			else cout<<ans+(i<=l[0]?a[0][f[0]]-a[1][f[0]]:0)-val(i)+a[1][End]<<' ';
		}
     	cout<<ans<<'\n';
	}
	return 0;
}
```

时间复杂度：$O(n)$。

---

## 作者：yshpdyt (赞：3)

## 题意
有 $n+m+1$ 个人依次来面试，第 $i$ 个人的编程能力是 $a_i$，测试能力是 $b_i$。公司需要 $n$ 名程序员和 $m$ 名测试员。招聘规则为，编程能力强于测试能力的去当程序员，否则去当测试员，保证不存在两项能力相同的员工，如果岗位已满，则调剂到另一个岗位。公司的能力是所有程序员的编程能力与所有测试员的测试能力之和。

求出对于每个人，如果其不参加面试，公司的能力。

## Sol
考虑钦定最后一个人不参加面试，可以模拟求出公司的能力为 $res$。

然后考虑每次让第 $i$ 人不参加面试，减去他的贡献，加上最后一个人的贡献。

但是这样不够完善，如果撤去的人是个程序员，在此之前程序员满了，后面有人被迫调剂，那么应该让第一个调剂的人去当程序员，让最后一个人去当测试员，答案变化比较大。

注意到在某一职位招满后，剩下的所有人不管能力都只能去另一个职业，不妨假设程序员先招满，另一种情况同理。

那么显然可以根据招满的时刻分成两部分。

后半部分答案比较简单，因为只是换掉测试员，所以答案是 $res-b_i+b_{n+m+1}$。

前半部分需要一些讨论，如果换掉的人原来是测试员，和刚才一样处理即可。如果换掉的人是程序员，会让后半部分的第一个编程能力大于测试能力的人替补，设这个人为 $j$，然后再让最后一人成为测试员，答案为 $res-a_i+a_j-b_j+b_{n+m+1}$。

对于测试员先满，同理即可。

时间复杂度 $O(n)$，听说有比较容易想到的 $O(n\log n)$ 做法。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 300005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const ll mod=1e9+7;
const ll inf=1e18;
const double eps=1e-6;
ll n,m,a[N],b[N],bel[N];
stack<ll>x,y;
ll resa,resb,ans[N];
void sol(){
    cin>>n>>m;
    resa=0,resb=0;
    while (!x.empty())x.pop();
    while (!y.empty())y.pop(); 
    for(int i=1;i<=n+m+1;i++){
        cin>>a[i];
        bel[i]=0;
    }
    int pos=n+m+1+1,p=0;
    for(int i=1;i<=n+m+1;i++)cin>>b[i];
    if(x.size()==n&&0<n+m+1)pos=0,p=1;
    if(y.size()==m&&0<n+m+1)pos=0,p=0;
    for(int i=1;i<=n+m;i++){
        if(a[i]>b[i]){
            if(x.size()<n){
                resa+=a[i];
                x.push(i);
                bel[i]=1;
            }else{
                resb+=b[i];
                y.push(i);
                bel[i]=0;
            }
        }else{
            if(y.size()<m){
                resb+=b[i];
                y.push(i);
                bel[i]=0;
            }else{
                resa+=a[i];
                x.push(i);
                bel[i]=1;
            }
        }
        if(x.size()==n&&pos==n+m+2)pos=i,p=1;
        if(y.size()==m&&pos==n+m+2)pos=i,p=0;
    }
    ll last=n+m+1;
    ans[n+m+1]=resa+resb;
    for(int i=n+m;i>pos;i--){
        ans[i]=resa+resb;
        if(p)ans[i]=ans[i]-b[i]+b[n+m+1];
        if(!p)ans[i]=ans[i]-a[i]+a[n+m+1];
        if(p&&a[i]>b[i])last=i;
        if(!p&&a[i]<b[i])last=i;
    }
    for(int i=pos;i>=1;i--){
        ans[i]=resa+resb;
        if(p&&a[i]>b[i])ans[i]=ans[i]-a[i]+b[n+m+1]-b[last]+a[last];
        if(p&&a[i]<b[i])ans[i]=ans[i]-b[i]+b[n+m+1];
        if(!p&&a[i]<b[i])ans[i]=ans[i]-b[i]+a[n+m+1]-a[last]+b[last];
        if(!p&&a[i]>b[i])ans[i]=ans[i]-a[i]+a[n+m+1]; 
    }
    for(int i=1;i<=n+m+1;i++)cout<<ans[i]<<" ";
    cout<<endl;
}
int main(){
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    ll ttt;
    cin>>ttt;
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：MoonCake2011 (赞：2)

首先，如果不删人，答案很好求。

但是删一个人就不好 $O(1)$ 求得。

所以一定要预处理。

我将 $a_i>b_i$ 与 $a_i<b_i$ 的人装进了俩 `vector`。

为了快速求和，我求出俩 `vector` 的 $a_i$ 与 $b_i$ 的和。

删去第 $i$ 个人，我们直接暴力分讨。

两种情况 $i\le n$，$i>n$。

去求就是了。

看代码。

分讨了 70 多行。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int a[300010],b[300010];
vector<int>p,q,sap,saq,sbp,sbq;
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n+m+1;i++) cin>>a[i];
	for(int i=1;i<=n+m+1;i++) cin>>b[i];
	p.clear(),q.clear(),sap.clear(),saq.clear(),sbp.clear(),sbq.clear();
	p.push_back(0),q.push_back(0);
	sap.push_back(0),sbp.push_back(0);
	saq.push_back(0),sbq.push_back(0);
	for(int i=1;i<=n+m+1;i++){
		if(a[i]>b[i]){
			p.push_back(i);
			sap.push_back(0);
			sap[sap.size()-1]=sap[sap.size()-2]+a[i];
			sbp.push_back(0);
			sbp[sbp.size()-1]=sbp[sbp.size()-2]+b[i];
		}
		else{
			q.push_back(i);
			saq.push_back(0);
			saq[saq.size()-1]=saq[saq.size()-2]+a[i];
			sbq.push_back(0);
			sbq[sbq.size()-1]=sbq[sbq.size()-2]+b[i];
		}
	}
	for(int i=1;i<=n+m+1;i++){
		if(a[i]>b[i]){//程序 
			int pos=lower_bound(p.begin(),p.end(),i)-p.begin(),ans=0;//二分
			if(pos<=n){
				if(p.size()-2>=n) ans+=sap[n+1]+sbp[sbp.size()-1]-sbp[n+1];//n 个人装得下
				else ans+=sap[sap.size()-1];//装不下
				if(q.size()-1>=m) ans+=sbq[m]+saq[sbq.size()-1]-saq[m];//同理
				else ans+=sbq[sbq.size()-1];
				ans-=a[i];
			}
			else{
				if(p.size()-1>=n) ans+=sap[n]+sbp[sbp.size()-1]-sbp[n];
				else ans+=sap[sap.size()-1];
				if(q.size()-1>=m) ans+=sbq[m]+saq[sbq.size()-1]-saq[m];
				else ans+=sbq[sbq.size()-1];
				ans-=b[i];
			}
			cout<<ans<<' ';
		}
		else{//测试 
			int pos=lower_bound(q.begin(),q.end(),i)-q.begin(),ans=0;
			if(pos<=m){
				if(q.size()-2>=m) ans+=sbq[m+1]+saq[saq.size()-1]-saq[m+1];
				else ans+=sbq[sbq.size()-1];
				if(p.size()-1>=n) ans+=sap[n]+sbp[sbp.size()-1]-sbp[n];
				else ans+=sap[sap.size()-1];
				ans-=b[i];
			}
			else{
				if(q.size()-1>=m) ans+=sbq[m]+saq[saq.size()-1]-saq[m];
				else ans+=sbq[sbq.size()-1];
				if(p.size()-1>=n) ans+=sap[n]+sbp[sbp.size()-1]-sbp[n];
				else ans+=sap[sap.size()-1];
				ans-=a[i];
			}
			cout<<ans<<" ";
		}
	}
	cout<<"\n";
}
signed main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：Jerrycyx (赞：1)

总体思路：二分+前缀和

-----

因为在本题中，满员与否具有二段性，即在某个人以前一定没有满员，在这个人之后一定满员，所以可以二分查找**满员的位置**。

这里，记程序员能力值更高的候选人为预备程序员，测试员能力值更高的人为预备测试员。

满员很好判断，对于每个位置记录它及以前预备程序员/预备测试员的人数，直接判断是否多于需求量 $n$ 或 $m$，注意如果包含删去的这候选人，需要减去他的贡献。

找出程序员和测试员满员的位置以后，有以下三种情况：
+ 程序员先满员，在满员的位置以前，正常累加能力值；在满员的位置之后，只累加测试员能力值。
+ 测试员先满员，在满员的位置以前，正常累加能力值；在满员的位置之后，只累加程序员能力值。
+ 程序员和测试员同时满员（我代码里二分得到的其实是刚超员的前一个位置，所以这种情况可能发生，**当且仅当预备程序员和预备测试员的人数都刚好等于所需程序员和测试员的人数**），这时直接正常累计所有人的能力值即可。

枚举删去的候选人，然后根据上述过程即可求出最后团队的总能力值，注意在计算的时候需要时刻排除删去的候选人的影响。

-----

要实现上述操作，需要记录以下参数：
+ 仅程序员能力值的前缀和 `sum_prog`，仅测试员能力值的前缀和 `sum_test`；
+ 所有候选人都选择自己的强项（即预备程序员全部成为正式程序员，预备测试员全部成为正式测试员）的总能力值前缀和 `sum_ok`；
+ 某个位置以前预备程序员的数量 `cnt_prog` 和预备测试员的数量 `cnt_test`。

注意开 `long long`。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;

const int N=2e5+5;
int T,n,m;
int prog[N],test[N];
long long sum_prog[N],sum_test[N],sum_ok[N]; 
int cnt_prog[N],cnt_test[N];
//以上变量含义见题解内容 
//prog(rammer)程序员；test(er)测试员 

long long getsum(long long sum[],int l,int r)
{
	return sum[r]-sum[l-1];
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n+m+1;i++)
		{
			scanf("%d",&prog[i]);
			sum_prog[i]=sum_prog[i-1]+prog[i];
		}
		for(int i=1;i<=n+m+1;i++)
		{
			scanf("%d",&test[i]);
			sum_test[i]=sum_test[i-1]+test[i];
		}
		for(int i=1;i<=n+m+1;i++)
		{
			cnt_prog[i]=cnt_prog[i-1];
			cnt_test[i]=cnt_test[i-1];
			if(prog[i]>test[i]) //这个候选人是预备程序员 
			{
				cnt_prog[i]++;
				sum_ok[i]=sum_ok[i-1]+prog[i];
			}
			if(prog[i]<test[i]) //这个候选人是预备测试员 
			{
				cnt_test[i]++;
				sum_ok[i]=sum_ok[i-1]+test[i];
			}
		}
		
		for(int pos=1;pos<=n+m+1;pos++)
		{
			int l=0,r=n+m+1+1;
			while(l+1<r) //[1,l] ok; [r,n+m+1] exceeded
			{
				int mid=l+r>>1,prog_now=cnt_prog[mid]; //当前位置以前的预备程序员人数 
				if(prog[pos]>test[pos] && pos<=mid) prog_now--; //排除当前候选人
				if(prog_now<=n) l=mid;
				else r=mid;
			}
			int pos_prog=l;
			
			l=0,r=n+m+1+1;
			while(l+1<r) //[1,l] ok; [r,n+m+1] exceeded
			{
				int mid=l+r>>1,test_now=cnt_test[mid]; //当前位置以前的预备测试员人数 
				if(prog[pos]<test[pos] && pos<=mid) test_now--; //排除当前候选人
				if(test_now<=m) l=mid;
				else r=mid;
			}
			int pos_test=l;
			
			long long ans=0;
			if(pos_prog<pos_test) //程序员先满员，以后所有人只能当测试员 
			{
				ans=getsum(sum_ok,1,pos_prog)+getsum(sum_test,pos_prog+1,n+m+1);
				if(pos<=pos_prog) ans-=max(prog[pos],test[pos]); //排除当前候选人 
				else ans-=test[pos];
			}
			else if(pos_prog>pos_test) //测试员先满员，以后所有人只能当程序员 
			{
				ans=getsum(sum_ok,1,pos_test)+getsum(sum_prog,pos_test+1,n+m+1);
				if(pos<=pos_test) ans-=max(prog[pos],test[pos]); //排除当前候选人
				else ans-=prog[pos];
			}
			else
			{
				if(pos_prog==n+m+1) //程序员和测试员数量刚好够 
				{
					ans=getsum(sum_ok,1,n+m+1);
					ans-=max(prog[pos],test[pos]);
				}
				else return -1; //为了防止出现意想不到的情况
				//上面的 if/else 语句可以删去，只保留中间的处理部分 
			}
			printf("%lld ",ans);
		}
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：TTpandaS (赞：1)

不妨设先招满的职业为 $A$，另一个职业为 $B$。

一定可以找到一个人满足在选他之后使得 $A$ 职业招满，那么剩下的一定会选择 $B$ 职业。

令找到的这个人位置为 $end$，先算出假设的总贡献，在 $end$ 前的人都贡献其能力最大值，之后的人贡献 $B$ 职业的能力值。

在 $end$ 之后的人如果被删去，那么只会让答案减去他在 $B$ 职业上的能力值。

在 $end$ 之前的人如果被删去，如果他本来就是贡献的就是 $B$ 职业能力值，那么只会让答案减去他在 $B$ 职业上的能力值。而如果他贡献的是 $A$ 职业能力值，答案先会减去他在 $A$ 职业上的能力值，然后会让在 $end$ 之后的人选一个来填补他的空缺。所以可以先找到 $end$ 之后第一个满足在 $A$ 职业上的能力值大于 $B$ 职业上的能力值的人，然后答案减去这个人在 $B$ 职业上的能力值，加上其在 $A$ 职业上的能力值即可。

```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  const int N=2e5+5;
  int T;
  int n,m,a[N],b[N];
  int ans[N];
  signed main(){
      scanf("%lld",&T);
      while(T--){
          scanf("%lld %lld",&n,&m);
          for(int i=1;i<=n+m+1;i++){
              scanf("%lld",&a[i]);
          }
          for(int i=1;i<=n+m+1;i++){
              scanf("%lld",&b[i]);
          }
          int tot1=0,tot2=0,end;
          for(int i=1;i<=n+m+1;i++){
              if(!n){
                  end=0;
                  break;
              }
              if(!m){
                  end=0;
                  break;
              }
              if(a[i]>b[i]){
                  tot1++;
                  if(tot1==n){
                      end=i;
                      break;
                  }
              }
              else{
                  tot2++;
                  if(tot2==m){
                      end=i;
                      break;
                  }
              }
          }
          if(tot2==m){
              for(int i=1;i<=n+m+1;i++){
                  swap(a[i],b[i]);
              }
              swap(n,m);
              swap(tot1,tot2);
          }
          int sum=0;
          for(int i=1;i<=end;i++){
              sum+=max(a[i],b[i]);
          }
          for(int i=end+1;i<=n+m+1;i++){
              sum+=b[i];
          }
          for(int i=end+1;i<=n+m+1;i++){
              ans[i]=sum-b[i];
          }
          int fi=n+m+1;
          for(int i=end+1;i<=n+m+1;i++){
              if(a[i]>b[i]){
                  fi=i;
                  break;
              }
          }
          for(int i=1;i<=end;i++){
              if(a[i]>b[i]){
                  ans[i]=sum-a[i]-b[fi]+a[fi];
              }
              else{
                  ans[i]=sum-b[i];
              }
          }
          for(int i=1;i<=n+m+1;i++){
              printf("%lld ",ans[i]);
          }
          printf("\n");
      }
      return 0;
  }
```

---

## 作者：ttq012 (赞：1)

注：题解格式已经修改。

给大家介绍一种又难写又难调的答辩做法。

首先考虑暴力怎么做。对于每一个人 $i$，从前往后枚举每一个人 $j$，如果 $j\neq i$ 那么就把它给放入更合适的集合里。但是这样的时间复杂度为 $O(n^2)$，会超时。

考虑优化。容易发现上述的暴力有着大量的冗余运算。因此开设两个集合 $S_1$ 和 $S_2$ 分别表示编程技能更加优秀的人集合和测试技能更加优秀的人集合。然后开四个数组 $A_{1,1},A_{1,2},A_{2,1},A_{2,2}$ 分别表示编程技能优秀的人去干编程对技能的贡献，编程技能优秀的人去干测试对技能的贡献，测试技能优秀的人去干测试对技能的贡献，测试技能优秀的人去干编程对技能的贡献。容易发现答案必然是：

+ 一段连续的编程去干编程和一段连续的编程去干测试。
+ 一段连续的测试去干测试和一段连续的测试去干编程。

两者都出现的。所以对上述的四个 $A_{1/2,1/2}$ 数组去开 $4$ 个前缀和统计答案，然后一步一步贪心的模拟答案即可。注意细节十分的多。时间复杂度为 $O(n)$。

代码写了 $170$ 行。

```cpp
#include <bits/stdc++.h>
#define int long long
#define pb push_back
#define em emplace_back
#define F(i,x,y) for(int i=x;i<=y;i++)
#define G(i,x,y) for(int i=x;i>=y;i--)
#define W(G,i,x) for(auto&i:G[x])
#define W_(G,i,j,x) for(auto&[i,j]:G[x])
#define add(x,y) z[x].em(y)
#define add_(x,y) add(x,y),add(y,x)
#define Add(x,y,d) z[x].em(y,d)
#define Add_(x,y,z) Add(x,y,z),Add(y,x,z);
#define inf (7611257611378358090ll/2)
using namespace std;
const int N = 550100, mod = 1e9 + 7;
int a[N], b[N], to[N], prs[N], tos[N], prt[N], tot[N];
// 算 prog 的 a 贡献
int q1(int l, int r) {
    if (l > r) return 0;
    if (l) return prs[r] - prs[l - 1];
    return prs[r];
}
// 算 test 的 b 贡献
int q2(int l, int r) {
    if (l > r) return 0;
    if (l) return tos[r] - tos[l - 1];
    return tos[r];
}
int q3(int l, int r) {
    if (l > r) return 0;
    if (l) return prt[r] - prt[l - 1];
    return prt[r];
}
int q4(int l, int r) {
    if (l > r) return 0;
    if (l) return tot[r] - tot[l - 1];
    return tot[r];
}
auto main() [[O3]] -> signed {
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        F(i, 1, n + m + 1) {
            cin >> a[i];
        }
        F(i, 1, n + m + 1) {
            cin >> b[i];
        }
        vector<int> prog, test;
        F(i, 1, n + m + 1) {
            if (a[i] > b[i]) prog.pb(i), to[i] = prog.size();
            else test.pb(i), to[i] = test.size();
        }
        if (prog.size())
        prs[0] = a[prog[0]], prt[0] = b[prog[0]];
        if (test.size())
        tos[0] = b[test[0]], tot[0] = a[test[0]];
        F(i, 1, (int)prog.size() - 1)
        prs[i] = prs[i - 1] + a[prog[i]], 
        prt[i] = prt[i - 1] + b[prog[i]];
        F(i, 1, (int)test.size() - 1)
        tos[i] = tos[i - 1] + b[test[i]], 
        tot[i] = tot[i - 1] + a[test[i]];
        F(i, prog.size(), n + m + 33)
        prs[i] = prs[i - 1], prt[i] = prt[i - 1];
        F(i, test.size(), n + m + 33)
        tos[i] = tos[i - 1], tot[i] = tot[i - 1];
        F(i, 1, n + m + 1) {
            if (a[i] > b[i]) {
                // 本身最应该被任命为 prog
                if (to[i] > n) {
                    // 本身也任命不到了
                    // 后面的全都鉴定为 test
                    int s = 0;
                    s += q1(0, n - 1);
                    // F(j, 0, n - 1) {
                    //     s += a[prog[j]];
                    // }
                    s += q3(n, to[i] - 2);
                    s += q3(to[i], (int)prog.size() - 1);
                    // F(j, n, (int)prog.size() - 1) {
                    //     if (prog[j] != i)
                    //     s += b[prog[j]];
                    // }
                    s += q2(0, (int)test.size() - 1);
                    // for (auto &x : test) {
                    //     s += b[x];
                    // }
                    cout << s << ' ';
                } else {
                    // 本身任命的到
                    int s = 0;
                    s += q1(0, to[i] - 2);
                    s += q1(to[i], n);
                    s += q3(n + 1, (int)prog.size() - 1);
                    // F(j, 0, (int)prog.size() - 1) {
                    //     if (prog[j] == i) {
                    //         // j < n FOR ALL
                    //         cout << "result " << j << '\n';
                    //         continue;
                    //     }
                    //     if (j <= n) {
                    //         s += a[prog[j]];
                    //     } else {
                    //         s += b[prog[j]];
                    //     }
                    // }
                    s += q2(0, m - 1);
                    s += q4(m, (int)test.size() - 1);
                    // F(j, 0, (int)test.size() - 1) {
                    //     if (j < m) {
                    //         s += b[test[j]];
                    //     } else {
                    //         s += a[test[j]];
                    //     }
                    // }
                    cout << s << ' ';
                }
            } else {
                // 本身最应该被任命为 test
                if (to[i] > m) {
                    int s = 0;
                    s += q2(0, m - 1);
                    // F(j, 0, m - 1) {
                    //     s += b[test[j]];
                    // }
                    s += q4(m, to[i] - 2);
                    s += q4(to[i], (int)test.size() - 1);
                    // F(j, m, (int)test.size() - 1) {
                    //     if (test[j] != i)
                    //     s += a[test[j]];
                    // }
                    s += q1(0, (int)prog.size() - 1);
                    // for (auto &x : prog) {
                    //     s += a[x];
                    // }
                    cout << s << ' ';
                } else {
                    int s = 0;
                    s += q2(0, to[i] - 2);
                    s += q2(to[i], m);
                    s += q4(m + 1, (int)test.size() - 1);
                    // F(j, 0, (int)test.size() - 1) {
                    //     if (test[j] == i) {
                    //         continue;
                    //     }
                    //     if (j <= m) {
                    //         s += b[test[j]];
                    //     } else {
                    //         s += a[test[j]];
                    //     }
                    // }
                    s += q1(0, n - 1);
                    s += q3(n, (int)prog.size() - 1);
                    // F(j, 0, (int)prog.size() - 1) {
                    //     if (j < n) {
                    //         s += a[prog[j]];
                    //     } else {
                    //         s += b[prog[j]];
                    //     }
                    // }
                    cout << s << ' ';
                }
            }
        }
        cout << '\n';
    }
}
```

---

## 作者：Hoks (赞：1)

## 前言
上分场，但是马上就被家长会折磨到掉的更多了。

最后一题写的 C，感觉其实不难想。
## 思路分析
首先对于给我们的 $n+m+1$ 个人，我们先按照正常的顺序决策一遍，得到初始答案 $res$。

$res$ 即为不要第 $n+m+1$ 个人时的答案。

接着考虑怎么得到去掉别的人的答案。

从本质入手，如果我们去掉一个人 $i$，他的工作类型为 $1$，那么会产生什么影响？

因为 $1$ 的空位多了一个，所以下一个应该选 $1$ 但是被强制选 $2$ 的人会变成 $1$。

设这个人为 $k$，则产生的贡献为 $a_k-b_k$。

那这样就结束了吗？

不，$k$ 他不选 $2$ 了，所以下一个应该选 $2$ 但是被强制选 $1$ 的人会变成 $2$。

直接递归显然是挂的，考虑直接使用递推。

设 $d_i$ 表示 $i$ 这个人不选会带来多少的收益。

则 $d_i=a_k-b_k+d_k$。

对于这里的这个 $k$，枚举的时候更新下即可。

最后的对于 $i$，若他选的是 $1$，则答案即为 $res+d_i-a_i$。

选的是 $2$ 的同理。

剩下的细节/没理解可以看下代码。
## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10,mod=1e9+7,V=1e9,INF=0x3f3f3f3f3f3f3f3f;
int T,n,m,a[N],b[N],c[N],d[N];
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s){for(char c:s) put(c);}
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c=='('||c==')'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
signed main()
{
    T=read();
    while(T--)
    {
        n=read(),m=read();int res=0,f1=0,f2=0;
        for(int i=1;i<=n+m+1;i++) a[i]=read();
        for(int i=1;i<=n+m+1;i++) b[i]=read();
        for(int i=1;i<=n+m;i++)
        {
            if(f1==n){c[i]=2,f2++;res+=b[i];continue;}
            if(f2==m){c[i]=1;f1++;res+=a[i];continue;}
            if(a[i]>b[i]) f1++,c[i]=1,res+=a[i];
            else f2++,c[i]=2,res+=b[i];
        }
        f1=n+m+1,f2=n+m+1;d[n+m+1]=0;
        for(int i=n+m;i>=1;i--)
        {
            if(c[i]==1) d[i]=d[f1]+max(a[f1]-b[f1],0ll),(f1==n+m+1)&&(d[i]=d[f1]+a[f1]);
            else d[i]=d[f2]+max(b[f2]-a[f2],0ll),(f2==n+m+1)&&(d[i]=d[f2]+b[f2]);
            if(c[i]==1&&b[i]>a[i]) f2=i;
            if(c[i]==2&&b[i]<a[i]) f1=i;
        }
        for(int i=1;i<=n+m;i++) print(res-((c[i]==1)?a[i]:b[i])+d[i]),put(' ');
        print(res);put('\n');
    }
    genshin:;flush();return 0;
}
```

---

## 作者：KarmaticEnding (赞：0)

我们首先一起来想一个暴力思路。

暴力怎么做？很简单，依次枚举每一个面试者 $i$，如果 $i$ 没有来面试，那么公司对于剩下的人一个一个按照规则聘用，公司的能力值是多少。时间复杂度 $O((n+m)^2)$。

在暴力的过程中可以观察到，总有那么一些面试者，无论谁不来面试，只要不来面试的不是这个人，这个人的职位就是固定的，一定是程序员和测试员中的一个。

所以，现在我们来考虑什么人的职位不是固定的。在考虑这个之前，我们先来考虑对于第 $i$ 个面试者，如果面试者 $j$ 来与不来能够影响面试者 $i$ 的职位，$j$ 与 $i$ 应该满足什么样的关系。

首先，我们要知道面试是按照面试者来的顺序的。如果 $j$ 在 $i$ 之后才来，也即 $j>i$，那么 $j$ 来与不来都是不会影响 $i$ 的职位的，毕竟 $i$ 之前的人是没有变的，面试到 $i$ 时的状态也是没有变的。

因此，我们得到了一个结论：如果一个面试者 $j$ 来与不来能够影响面试者 $i$ 所处职位，那么 $j$ 在 $i$ 之前，也就是 $j<i$。

这是一个必要条件，我们继续深挖，看看能不能把它变成一个充分必要条件。

我们假设 $a_i>b_i$。如果 $j<i$ 并且 $j$ 没来，然后 $i$ 的职位改变了，显而易见 $i$ 只能是从测试员变成程序员。很好理解，原来 $i$ 是可以被聘为程序员的，但是因为程序员人满了，只能屈才当一下测试员了。现在程序员走掉一个，空出来一个位置，那么 $i$ 肯定又能当回程序员了。

如果 $j$ 不来能够使 $i$ 从测试员变成程序员，我们得到了如下三重判断：

  - $a_j>b_j$。
  - $i$ 刚好是第 $n+1$ 个满足 $a_i>b_i$ 的。$j$ 走掉之后 $i$ 变成了第 $n$ 个，所以转职了。

反之亦然。

接下来的事情就很好办了。记录一下第 $n+1$ 个满足 $a_i>b_i$ 的 $i$ 和第 $m+1$ 个满足 $b_i>a_i$ 的 $i$，分别记为 $Ppc$ 和 $Tpc$（胡乱取的变量名），容易发现 $Ppc$ 和 $Tpc$ 只会有一个有值。很好理解，如果 $Ppc$ 和 $Tpc$ 都有值，那么至少有 $n+1$ 个满足 $a_x>b_x$ 的 $x$ 和 $m+1$ 个满足 $b_y>a_y$ 的 $y$，那么至少有 $n+m+2$ 个面试者，与题目条件“总共有 $n+m+1$ 个面试者”矛盾。

接下来就是对答案的处理。首先记录一个 $ans$ 表示如果录取了所有面试者，公司的能力值。其中，对于第 $n+m+1$ 个面试者，如果 $a_i>b_i$，其是测试员；反之则是程序员。这样设表示其被强制转职了。

从 $1$ 到 $n+m+1$ 枚举每一个面试者 $i$，如果 $a_i>b_i$，并且满足 $Ppc$ 有值且 $i<Ppc$，说明面试者 $Ppc$ 的职位改变了，输出 $ans-a_i+a_{Ppc}-b_{Ppc}$；反之，$i$ 一定是一个测试员，输出 $ans-b_i$。

如果 $b_i>a_i$ 也是同样的道理。

那么这道题就愉快的结束了。上面的性质以前的题解都提过，只是具体解法不大一样而已。

所以如果您看得懂我的题解点个赞吧~没看懂请在评论区回复一句

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
int a[MAXN],b[MAXN];
int n,m,Pcnt,Tcnt,Ppc,Tpc;
int T;
long long ans=0,res;
int main(){
//	freopen("C.in","r",stdin);
//	freopen("C.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n+m+1;++i){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n+m+1;++i){
			scanf("%d",&b[i]);
		}
		Pcnt=0,Tcnt=0;
		Ppc=0,Tpc=0;
		ans=0;
		for(int i=1;i<=n+m+1;++i){
			if(a[i]>b[i]){
				if(Pcnt<n){
					++Pcnt;
					ans+=a[i];
				}
				else{
					ans+=b[i];
					if(Pcnt==n){
						++Pcnt;
					}
				}
			}
			else{
				if(Tcnt<m){
					++Tcnt;
					ans+=b[i];
				}
				else{
					ans+=a[i];
					if(Tcnt==m){
						++Tcnt;
					}
				}
			}
			if(Pcnt==n+1&&Ppc==0){
				Ppc=i;
			}
			if(Tcnt==m+1&&Tpc==0){
				Tpc=i;
			}
		}
		if(Ppc==0){
			Ppc=2e5+9;
		}
		if(Tpc==0){
			Tpc=2e5+9;
		}
		for(int i=1;i<=n+m+1;++i){
			res=ans;
			if(a[i]>b[i]){
				if(i<Ppc){
					res-=a[i];
					res=res+a[Ppc]-b[Ppc];
				}
				else{
					res-=b[i];
				}
			}
			if(b[i]>a[i]){
				if(i<Tpc){
					res-=b[i];
					res=res+b[Tpc]-a[Tpc];
				}
				else{
					res-=a[i];
				}
			}
			printf("%lld ",res);
		}
		putchar('\n');
	}
}
```

---

## 作者：banned_gutongxing (赞：0)

## 思路
试想，在选拔规则里面，一定会在某一个不能将他安排到时候他的位置。然后，如果一个人没有来，且在前面。这个人是否能让原本不行的下一个人来替代他的位置。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5+10;
void read(int &x){
	x = 0;int p = 1;char ch;
	do{
		ch = getchar();
		if(ch=='-') p = -1;
	}while(!isdigit(ch));
	while(isdigit(ch)){
		x*=10;
		x+=ch-'0';
		ch = getchar();
	}
	x*=p;
}
void read(char &x){
    x = getchar();
    while(x==' '||x=='\n'||x=='\r') x = getchar();
}
void write(int k){
	if(k<0) putchar('-');
	k = abs(k);
	stack<int> num;
	do{
		num.push(k%10);
		k/=10;
	}while(k);
	while(!num.empty()){
		putchar(num.top()+48);
        num.pop();
	}
}
int T,n,m;
struct node{
	int t,id,a,b;
}a[MAXN],b[MAXN];
int pre[MAXN],suc[MAXN];
bool cmp(node a,node b){
	return a.t<b.t;
}
bitset<MAXN> p;
signed main(){
	read(T);
	while(T--){
		read(n);read(m);p.reset();
		int x = n,y = m;
		for(int i = 1;i<=n+m+1;i++){
			read(a[i].a);
		}
        for(int i = 1;i<=n+m+1;i++){
            read(a[i].b);
        }
		int ans = 0,ans1 = 0,now = 0;
		for(int i = 1;i<=n+m+1;i++){
			now = i;
			if(a[i].a>a[i].b){
				if(x--){
					ans += a[i].a;
				}else{
					break;
				}
			}else{
				if(y--){
					ans += a[i].b;
				}else break;
			}
		}
		if(x==-1){
			for(int i = now;i<=n+m+1;i++){
				ans1 += a[i].b;
			}
		}else if(y==-1){
			for(int i = now;i<=n+m+1;i++){
				ans1 += a[i].a;
			}
		}
        for(int i = 1;i<=n+m+1;i++){
			if(i>=now){
				write(ans+ans1-(x==-1?a[i].b:a[i].a));
			}else{
				if(x==-1){
					if(a[i].a>a[i].b){
						write(ans+ans1-a[i].a+a[now].a-a[now].b);
					}else write(ans+ans1-a[i].b);
				}else{
					if(a[i].a<a[i].b){
						write(ans+ans1-a[i].b+a[now].b-a[now].a);
					}else write(ans+ans1-a[i].a);
				}
			}
			putchar(' ');
        }
        putchar('\n');
	}
    return 0;
}
```

---

