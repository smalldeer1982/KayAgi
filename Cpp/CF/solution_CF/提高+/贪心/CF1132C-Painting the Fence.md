# Painting the Fence

## 题目描述

你有一段很长的栅栏，共有 $n$ 段。遗憾的是，这段栅栏还没有被粉刷，于是你决定雇佣 $q$ 个油漆工来粉刷它。第 $i$ 个油漆工会粉刷所有满足 $l_i \le x \le r_i$ 的区段 $x$。

但由于预算有限，你最多只能雇佣 $q-2$ 个油漆工。显然，只有被雇佣的油漆工才会工作。

你希望通过最优地选择 $q-2$ 个油漆工，使得被粉刷的区段数最大。如果某个区段至少被一个油漆工粉刷过，则认为该区段被粉刷。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7 5
1 4
4 5
5 6
6 7
3 5
```

### 输出

```
7
```

## 样例 #2

### 输入

```
4 3
1 1
2 2
3 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 4
1 1
2 2
2 3
3 4
```

### 输出

```
3
```

# 题解

## 作者：Ynoi (赞：8)

q个人中选取q-2个人，因为q <= 5000，我们珂以暴力枚举不选哪两个人

然后我们就要计算一下

有哪些地方，因为失去了这两个人而没有被涂色

求出每个点被多少人染色即可

然后就是被这两个人涂色的区间

没有重合部分 统计染色1次的个数

重合部分 统计染色2次个数

这些部分在失去这两个人之后不会被涂色

前缀和维护一下就星了

```
#include<bits/stdc++.h>
using namespace std;

#define LL long long
#define INF 0x3f3f3f3f
#define MAXN 5005

LL n,m,rt;
struct aa
{
	LL l,r,x;
}a[MAXN];
 LL c[MAXN];
 LL d[MAXN];
LL e[MAXN],f[MAXN];
 
void rd()
{
	cin >> n >> m;
	for(int i = 1; i <= m; i ++)
	{
		cin >> a[i].l >> a[i].r;
	}
}

bool cmp(aa a,aa b) {
	return a.l < b.l;
}

LL q1(LL l,LL r) {
	return d[r] - d[l-1]; 
} 
LL q2(LL l,LL r) {
	return e[r] - e[l-1]; 
} 


int main()
{
	rd();
	for(int i = 1; i <= m; i ++)
		for(int j = a[i].l; j <= a[i].r; j ++)
			c[j] ++;
	for(int i = 1; i <= n; i ++) {
		if(c[i] == 0) rt ++;
		d[i] = d[i-1];e[i] = e[i-1];
		if(c[i] == 1) d[i] ++;
		if(c[i] == 2) e[i] ++;
	}
	sort(a+1,a+m+1,cmp);
	LL an = 0,fck = INF;
	for(int i = 1; i <= m; i ++)
		for(int j = i+1; j <= m; j ++)  {
			if(a[j].l > a[i].r) {
				an = q1(a[i].l,a[i].r) + q1(a[j].l,a[j].r);
			} else {
				if(a[j].r < a[i].r)
				{
					an = q1(a[i].l,a[j].l-1) + q2(a[j].l,a[j].r) + q1(a[j].r+1,a[i].r);
				}else 
				{
					an = q1(a[i].l,a[j].l-1) + q2(a[j].l,a[i].r) + q1(a[i].r+1,a[j].r);
				}
			}
			fck = min(fck,an);
		} 
	cout<<n - fck - rt;
	return 0;
 } 
```

---

## 作者：jianhe (赞：5)

[CF1132C Painting the Fence](https://www.luogu.com.cn/problem/CF1132C)
题解

### 分析：

这是一道暴力枚举题。

不难从题目中发现，因为输入的是区间，所以可以用前缀和来存放每堵墙有几个人来涂。

又因为要去掉两个人，我们可以先枚举第一个被去掉的人，再考虑第二个人的最优情况，得出最优解，即为答案。

### 代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

#define ll long long

const ll N=5010;

ll n,m,a[N],b[N],ans,p[N],p2[N],ct;

ll solve(ll x){

	memset(p,0,sizeof(p));

	memset(p2,0,sizeof(p2));

	ct=LONG_LONG_MIN;

	for(int i=0;i<m;i++)

		if(i!=x) p[a[i]-1]++,p[b[i]]--;
    //第x个人已经在循环中被删去

	for(int i=0;i<n;i++)

		p[i]+=p[i-1];

	for(int i=0;i<n;i++)

		p2[i+1]=p2[i]+(p[i]==1);
    //p2记录的是 一堵墙只有一个人涂的情况 的前缀和

	for(int i=0;i<m;i++)

		if(i!=x) ct=max(ct,-(p2[b[i]]-p2[a[i]-1]));
        //删去i，则他所涂区间内，只有一个人涂的墙就无人来涂了，因此要减去

	for(int i=0;i<n;i++) ct+=(p[i]>0);

	return ct;

}

int main(){

	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);

	cin>>n>>m;

	for(int i=0;i<m;i++) cin>>a[i]>>b[i];

    for(int i=0;i<m;i++) ans=max(ans,solve(i));

    cout<<ans;

	return 0;

}
```

---

## 作者：Wf_yjqd (赞：2)

完全看不懂大佬们神奇的前缀和以及树状数组做法。

这不就是个暴力枚举题吗。

------------

假设两个个工人的离开有先后顺序。

显然如果一个位置有超过两个工人涂，那去掉两个工人后他一定还是被涂的。

预处理出涂的人数小于等于 $2$ 的位置被哪个（些）工人涂了。

考虑先枚举一个工人去掉，然后 $\operatorname{O}(n)$ 处理出剩下工人中去掉花费最少的。

问题变成了去掉一个工人，最大化粉刷的墙。

定义去掉某个工人的花费为只有他一个人涂的部分。

我们可以枚举一个位置，如果除了先走的工人涂的以外这个位置只有一个工人涂，将这个位置累计进这个工人的去掉花费。

再找出去掉花费最少的工人去掉即可。

对于先去掉某个工人后最大的被涂的墙取最大值即可。

复杂度 $\operatorname{O}(n^2)$。

------------

常数还是挺优秀的，不卡常第 $6$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+84;
int n,q,l[maxn],r[maxn],cnt[maxn],cntt[maxn],res,mn,ans;
pair<int,int> ad[maxn];
inline void Swap(int &x,int &y){
    x^=y^=x^=y;
    return ;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d",&l[i],&r[i]);
        cnt[r[i]+1]--;
        cnt[l[i]]++;
    }
    for(int i=1;i<=n;i++){
        cnt[i]+=cnt[i-1];
        if(cnt[i]&&cnt[i]<=2){
            for(int j=1;j<=q;j++)
                if(l[j]<=i&&i<=r[j]){
                    ad[i].first=j;
                    break;
                }
            if(cnt[i]==2){
                for(int j=q;j>=1;j--)
                    if(l[j]<=i&&i<=r[j]){
                        ad[i].second=j;
                        break;
                    }
            }
        }
    }
    for(int i=1;i<=q;i++){
        memset(cntt,0,4*q+84);
        for(int j=l[i];j<=r[i];j++){
            if(cnt[j]>1&&ad[j].first==i)
                Swap(ad[j].first,ad[j].second);
            cnt[j]--;
        }
        res=0;
        for(int j=1;j<=n;j++){
            if(cnt[j]){
                res++;
                if(cnt[j]==1)
                    cntt[ad[j].first]++;
            }
        }
        mn=0x3f3f3f3f;
        for(int j=1;j<=q;j++)
            if(i!=j)
                mn=min(mn,cntt[j]);
        ans=max(ans,res-mn);
        for(int j=l[i];j<=r[i];j++)
            cnt[j]++;
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：Larryyu (赞：2)

## _Description_
有一面长为 $n$ 的墙以及 $q$ 个工人，第 $i$ 个工人粉刷 $l_i$ 到 $r_i$ 的墙面，现在要去掉两个工人，问剩余 $q-2$ 个工人最多能粉刷多少墙面。
## _Solution_
注意数据，$n\le5\times10^3$，所以可以暴力枚举两个被去掉的工人。

对于被去掉的两个工人，他们的粉刷部分有三种情况：
- 没有相交
- 部分相交
- 完全相交（即小的区间在大的区间内）

可以先对每个工人的粉刷区间进行从左到右的排序，降低分类讨论复杂度。

如果一面墙被这两个人都刷了，那么它至少要刷 ```3``` 次，才不会被去到，如果只有一个人刷得到，只需刷到```2``` 次就不会被去掉。

所以我们记录每一个区间的 $ans_1,ans_2$，表示这个区间内刷过次数在一次及以下的墙数（一个人刷过就被去掉）和在两次及以下的墙数（两个人都刷过才会去掉）。

那么每一次用总墙数减去相交部分的 $ans_2$，再减去单独部分的 $ans_1$，就是剩余的墙数。

考虑如何维护 $ans_1,ans_2$。

本质上就是区间查询，用前缀和，树状数组都能做，线段树会因为常数大而被卡掉。

这里给出树状数组做法。
## _Code_
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,q;
int cnt[5050];
struct node{
	int l,r;
}a[5050];
struct tree{
	int ans1,ans2;
}tr[5050];
int lowbit(int x){
	return x&(-x);
}
void add(int x,int opt){
	for(int i=x;i<=n;i+=lowbit(i)){
		if(opt==1) tr[i].ans1++;
		else tr[i].ans2++;
	}
}
int query(int x,int opt){
	int ans=0;
	for(int i=x;i>=1;i-=lowbit(i)){
		if(opt==1) ans+=tr[i].ans1;
		else ans+=tr[i].ans2;
	}
	return ans;
}
void build(){
	for(int i=1;i<=n;i++){
		if(cnt[i]<=1) add(i,1),add(i,2);  //ans2也包括ans1
		else if(cnt[i]==2) add(i,2);
	}
}
bool cmp(node x,node y){  //对粉刷区间排序
	if(x.l==y.l) return x.r<y.r;
	return x.l<y.l;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>q;
	int tot=0;
	for(int i=1;i<=q;i++){
		cin>>a[i].l>>a[i].r;
		for(int j=a[i].l;j<=a[i].r;j++){
			if(!cnt[j]) tot++;  //求总墙数
			cnt[j]++;
		}
	}
	build();
	sort(a+1,a+1+q,cmp);
	int maxn=-10;
	for(int i=1;i<=q;i++){
		for(int j=i+1;j<=q;j++){
			int sum=0;
			if(a[i].l<=a[j].l&&a[j].r<=a[i].r){  //完全相交，由于已经排过序，所以只有可能是i包含j
				if(a[i].l<a[j].l){  //当两个重叠的时候是不计算的
					sum+=query(a[j].l-1,1)-query(a[i].l-1,1);
				}
				if(a[j].r<a[i].r){
					sum+=query(a[i].r,1)-query(a[j].r,1);
				}
				sum+=query(a[j].r,2)-query(a[j].l-1,2);
			}else if(a[i].r>=a[j].l){  //部分相交
				if(a[i].l<a[j].l){
					sum+=query(a[j].l-1,1)-query(a[i].l-1,1);
				}
				if(a[i].r<a[j].r){
					sum+=query(a[j].r,1)-query(a[i].r,1);
				}
				sum+=query(a[i].r,2)-query(a[j].l-1,2);
			}else{  //不相交
				sum+=query(a[i].r,1)-query(a[i].l-1,1);
				sum+=query(a[j].r,1)-query(a[j].l-1,1);
			}
			maxn=max(maxn,tot-sum);
		}
	}
	cout<<maxn<<endl;
	return 0;
}
```

---

## 作者：xvl_ (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1132C)

一道枚举题。

我们可以直接枚举那 $2$ 个去掉的粉刷匠。先统计一下每个栅栏会被多少个粉刷匠刷到，然后枚举第一个被去掉的粉刷匠，然后计算剩下的粉刷匠会将每个栅栏刷到多少次，我们只需要看只能被刷 $1$ 次的栅栏就行了。

接着处理一个前缀和数组，记录前 $i$ 个栅栏中有多少个只能被 $1$ 个粉刷匠刷到。然后枚举第二个被去掉的粉刷匠，然后通过前缀和用 $O(1)$ 的时间复杂度查询，别忘了加上前面第一个粉刷匠去掉后没有被刷的栅栏的数量。最后取最小值，与 $n$ 相减即是答案。

### Code

```cpp
#include <bits/stdc++.h>
#define ll long long
#define INF 1e9
using namespace std;
int n, q, minn = INF;
int l[5005], r[5005], cnt[5005], sum[5005];
signed main() {
    ios :: sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 1; i <= q; i++) {
        cin >> l[i] >> r[i];
        for (int j = l[i]; j <= r[i]; j++) cnt[j]++;
    }
    for (int i = 1; i <= q; i++) {
        int x = 0;
        for (int j = l[i]; j <= r[i]; j++) cnt[j]--;
        for (int j = 1; j <= n; j++) {
            sum[j] = sum[j - 1];
            if (cnt[j] == 1) sum[j]++;
            if (cnt[j] == 0) x++;
        }
        for (int j = 1; j <= q; j++) {  
            if (j == i) continue;
            minn = min(minn, sum[r[j]] - sum[l[j] - 1] + x);
        }
        for (int j = l[i]; j <= r[i]; j++) cnt[j]++; // 别忘了要加回去继续枚举
    }
    cout << n - minn;
    return 0;
}
```


---

## 作者：Arghariza (赞：2)

虽然但是，这题真的有 `*1700` 吗（

考虑到 $n\le 5000$，我们可以枚举去掉的两个区间，然后考虑 $O(1)$ 计算答案。

考虑去掉两个区间对答案的贡献，显然对于每一个位置，如果这个位置不被两个区间中任何一个覆盖，那么对答案的贡献是没有变化的。如果这个位置只被两个区间中的一个覆盖而不被其他所有区间覆盖，它对答案就会有 $-1$ 的贡献。如果这个位置被两个区间都覆盖并且没有被其他任何区间覆盖，它对答案也会有 $-1$ 的贡献。

那么我们只需要在 $O(1)$ 的时间内求出某个区间内被覆盖 $1$ 次或 $2$ 次的位置个数。于是我们对于 $q$ 个区间，每个区间中的位置全部 $+1$，最后做一个前缀和 $s_{i,0/1}$ 表示对序列从 $1$ 到 $i$ 的前缀位置，被覆盖的 $1/2$ 的个数即可。

复杂度大概是 $O(n^2)$ （这里认为 $n,q$ 同阶）。

[$\color{lightgreen}\mathtt{submission\ code}$](https://codeforces.com/contest/1132/submission/165661071)

---

## 作者：issue_is_fw (赞：1)

假设一开始把所有q条线段全选上去

用$in[x]$标记$x$点被覆盖了几次。很明显,此时答案就是$in[x]$不为0的点个数

$那么现在需要删去2条线段,我们直接暴力枚举,考虑如何求此时的答案$

因为只有两条线段,所有只有$in[x]<=2$的点可能变为$0$

所以开一棵树状数组$one$,标记$in[x]$为$1$的点为1

开一棵树状数组$two$,标记$in[x]$为2的点为$1$

那么对于枚举的两条线段,找出相交区间$[l,r]$

用$two$求出$[l,r]$中$in[x]=2$的点个数

$用one求出两条线段不相交的区间in[x]为1的点有几个$


$得到的这些点就是删去这两条线段会失去染色的点$


$最后答案取小即可$(~~我是不是很聪明会夸我~~)

```
#include <bits/stdc++.h>
using namespace std;
const int maxn=5009;
int n,ans,in[maxn],m;
class like_tree_array
{
	private:
		int sumn[maxn];
		int lowbit(int x){return x&(-x);}
	public:
		void add(int x){
			for(int i=x;i<=n;i+=lowbit(i))	sumn[i]++;
		}
		int ask(int l){
			int ans=0;
			for(int i=l;i;i-=lowbit(i))	ans+=sumn[i];
			return ans;
		}
		int query(int l,int r){
			return ask(r)-ask(l-1);
		}
}one,two;
struct p{
	int l,r;
}a[maxn];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i].l>>a[i].r;
		for(int j=a[i].l;j<=a[i].r;j++)	in[j]++;
	}
	int he=0;
	for(int i=1;i<=n;i++)
	{
		if(in[i])	he++;
		if(in[i]==1)	one.add(i);	
		else if(in[i]==2)	two.add(i);
	}
	for(int i=1;i<=m;i++)
	for(int j=i+1;j<=m;j++) 
	{
		int l=max(a[i].l,a[j].l),nl=min(a[i].l,a[j].l);
		int r=min(a[i].r,a[j].r),nr=max(a[i].r,a[j].r);
		int now=0;
		if(r>=l)//有相交的区间 
		{	
			now+=two.query(l,r);//相交区间
			if(l-1>=nl)	now+=one.query(nl,l-1);
			if(nr>=r+1) now+=one.query(r+1,nr);
		}
		else now+=one.query(a[i].l,a[i].r)+one.query(a[j].l,a[j].r);
		ans=max(ans,he-now); 
	}
	cout<<ans;
}
```

---

## 作者：Eazin_star (赞：0)

### 思路
看着可以直接暴枚，在看到 $n$ 和 $q$ 的范围后直接确定就是枚举。

记录下每面墙会有多少人刷，枚举那两个被去掉的粉刷匠。先枚举第一个去掉的粉刷匠，去掉后如果有墙只被一个人刷，那说明再去掉一个人时，那面墙可能不能被刷到。把所有这样的墙记录下来，在枚举第二位被去掉的粉刷匠时直接取最优就好。

记录下来最优数就是最少刷不到的墙的个数，所以用 $n$ 减去它就好。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int n, q, minn = 1e9; //minn表示最优解
int l[5005], r[5005], cnt[5005], sum[5005];

int main() {
	scanf("%d %d", &n, &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d %d", &l[i], &r[i]);
		for (int j = l[i]; j <= r[i]; j++) cnt[j]++; //记录每面墙有多少位粉刷匠刷
	}
	for (int i = 1; i <= q; i++) { //枚举第一位被去掉的粉刷匠
		int tot = 0;
		for (int j = l[i]; j <= r[i]; j++) cnt[j]--; 
		for (int j = 1; j <= n; j++) { //这里可以不用每次初始化，因为下标为0的永远不会被改变
			sum[j] = sum[j-1];
			if (cnt[j] == 1) sum[j]++; //如果只能被一位粉刷匠刷，记录下来
			if (cnt[j] == 0)tot++; //如果已经没有人刷了，也记录下来
		}
		for (int j = 1; j <= q; j++) { //枚举第二位被去掉的粉刷匠
			if (j == i) continue;
			minn = min(minn, sum[r[j]]-sum[l[j]-1]+tot); //取最优解
		}
		for (int j = l[i]; j <= r[i]; j++) cnt[j]++; //记得把减去的加回来
	}
	printf("%d\n", n-minn); //输出最终答案
	return 0;
}
```

---

## 作者：Zechariah (赞：0)

$O(qlog_2q+n^2+C_{5000}^2)$暴搜即可  
排序是为了后面写方便  
暴力处理出选每一个人的情况，做两个前缀和$sum1,sum2$分别表示1的个数和2的个数  
然后dfs出去掉哪两个人，计算一下此时的答案  
最终答案取最大
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
#define jh(x, y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 3e5 + 5, mod = 1e9 + 7, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
struct Node {
    int l, r;
    bool operator <(const rg Node &s)const { return l < s.l || (l == s.l&&r < s.r); }
}a[N];
int q, n, ans, tot;
int b[3], tong[N], sum1[N], sum2[N];
void dfs(rg int step, rg int now)
{
    if (step > 2)
    {
        rg int del = 0;
        if (a[b[1]].r < a[b[2]].l)del = sum1[a[b[1]].r] - sum1[a[b[1]].l - 1]+ sum1[a[b[2]].r] - sum1[a[b[2]].l - 1];
        else del = sum1[a[b[1]].r] - sum1[a[b[1]].l - 1] + (a[b[1]].r >= a[b[2]].r ? 0 : sum1[a[b[2]].r] - sum1[a[b[1]].r]) + sum2[fast_IO::min(a[b[2]].r, a[b[1]].r)] - sum2[a[b[2]].l - 1];
        ans = fast_IO::max(ans, tot - del);
        return;
    }
    for (rg int i = now; i <= q; ++i)
    {
        b[step] = i;
        dfs(step + 1, i + 1);
    }
}

int main(void)
{
    n = fast_IO::read(); q = fast_IO::read();
    for (rg int i = 1; i <= q; ++i)
    {
        a[i].l = fast_IO::read(), a[i].r = fast_IO::read();
        for (rg int j = a[i].l; j <= a[i].r; ++j)++tong[j];
    }
    sort(a + 1, a + q + 1);
    for (rg int i = 1; i <= n; ++i)if (tong[i])++tot;
    for (rg int i = 1; i <= n; ++i)if (tong[i] == 1)sum1[i] = 1;
    for (rg int i = 1; i <= n; ++i)if (tong[i] == 2)sum2[i] = 1;
    for (rg int i = 1; i <= n; ++i)
        sum1[i] += sum1[i - 1], sum2[i] += sum2[i - 1];
    dfs(1, 1);
    fast_IO::write(ans);
    return 0;
}
```


---

