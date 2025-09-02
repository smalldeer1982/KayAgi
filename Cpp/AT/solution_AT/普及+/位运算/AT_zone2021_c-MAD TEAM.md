# MAD TEAM

## 题目描述

[problemUrl]: https://atcoder.jp/contests/zone2021/tasks/zone2021_c

$ N $ 人のメンバー候補がおり、それぞれの人は、パワー・スピード・テクニック・知識・発想力の $ 5 $ 種類の能力値を持っています。  
 $ i $ 番目の人のパワーは $ A_i $ 、スピードは $ B_i $ 、テクニックは $ C_i $ 、知識は $ D_i $ 、発想力は $ E_i $ です。  
 あなたは、$ N $ 人のメンバー候補から $ 3 $ 人を選び、$ 1 $ つのチームを作ります。  
 チーム全体のパワーをチームメンバーのパワーの最大値で定義します。スピード・テクニック・知識・発想力についても同様に定義します。  
 チームの総合力を、チーム全体のパワー・スピード・テクニック・知識・発想力の最小値で定義します。  
 チームの総合力としてありえる最大値を求めてください。

## 说明/提示

### ストーリー

さて、本格的に UFO と対峙する仲間を集めることにしよう。それも、とびきり MAD で優秀な。  
 俺は数多の天才たちと競い合ってきた「AtCoder」上でメンバーを集めることにした。  
 名の知れたプログラマに片っ端から声をかけてもいいが、どうせなら得意分野のバランスが良い少数精鋭で最高なチームを作るとしよう。

### 制約

- 入力は全て整数
- $ 3\ <\ =\ N\ <\ =\ 3000 $
- $ 1\ <\ =\ A_i,\ B_i,\ C_i,\ D_i,\ E_i\ <\ =\ 10^9 $

### Sample Explanation 1

$ 3 $ 人全員をチームに入れるほかありません。 この時、チーム全体の各能力値は以下のようになります。 - チーム全体のパワー : $ \max(3,\ 6,\ 8)\ =\ 8 $ - チーム全体のスピード : $ \max(9,\ 9,\ 8)\ =\ 9 $ - チーム全体のテクニック : $ \max(6,\ 3,\ 9)\ =\ 9 $ - チーム全体の知識 : $ \max(4,\ 1,\ 3)\ =\ 4 $ - チーム全体の発想力 : $ \max(6,\ 1,\ 7)\ =\ 7 $ したがって、チームの総合力は $ \min(8,\ 9,\ 9,\ 4,\ 7)\ =\ 4 $ となります。

### Sample Explanation 2

$ 1,\ 2,\ 3 $ 番目の人を採用すると、チームの総合力は $ \min(20,\ 13,\ 19,\ 19,\ 18)\ =\ 13 $ です。

## 样例 #1

### 输入

```
3
3 9 6 4 6
6 9 3 1 1
8 8 9 3 7```

### 输出

```
4```

## 样例 #2

### 输入

```
5
6 13 6 19 11
4 4 12 11 18
20 7 19 2 5
15 5 12 20 7
8 7 6 18 5```

### 输出

```
13```

## 样例 #3

### 输入

```
10
6 7 5 18 2
3 8 1 6 3
7 2 8 7 7
6 3 3 4 7
12 8 9 15 9
9 8 6 1 10
12 9 7 8 2
10 3 17 4 10
3 1 3 19 3
3 14 7 13 1```

### 输出

```
10```

# 题解

## 作者：Binary_Lee (赞：4)

## [题面传送门](https://www.luogu.com.cn/problem/AT_zone2021_c)

### 解决思路

求最小值的最大值，考虑二分答案。

二分团队综合能力的最大值，我们需要实现的是一个判断该最大值是否合法的 check 函数。

考虑状压。对于每个人，记一个长度为 $5$ 的二进制串，对应 $5$ 项参数，其中一位是 $1$ 表示这项参数 $\ge$ 当前给定的团队综合能力的最大值，即满足要求。记录 $mark_i$ 表示是否存在二进制状态为 $i$ 的人。然后只要三重循环 $i,j,k$ 分别枚举状态（三个人），若满足：

$$(i\mid j\mid k=31)\ \text{and}\ mark_i\ \text{and}\ mark_j\ \text{and}\ mark_k$$

则该最大值合法。

### AC Code

```cpp
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(false)
#define TIE cin.tie(0),cout.tie(0)
#define int long long
using namespace std;
int n,a[3005][6];
bool mark[32];
bool check(int x){
	memset(mark,0,sizeof(mark));
	for(int i=1;i<=n;i++){
		int s=0;
		for(int j=0;j<5;j++){
			if(a[i][j+1]>=x) s|=(1<<j);
		}
		mark[s]=1;
	}
	for(int i=0;i<32;i++)
	for(int j=0;j<32;j++)
	for(int k=0;k<32;k++){
		if((i|j|k)==31&&mark[i]&&mark[j]&&mark[k]) return 1;
	}
	return 0;
}
signed main(){
	IOS;TIE;
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=5;j++) cin>>a[i][j];
	}
	int l=1,r=1e9;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	cout<<l-1<<endl;
	return 0;
}
```

---

## 作者：Wf_yjqd (赞：2)

最优解不是我，但跟我思路一样（我第二）。

------------

显然可以考虑二分答案。

如何快速选出三个，并判断是否可行呢？

我们可以转换问题，假设二分出答案为 $x$。

要求选出的三组数（每组 $5$ 位数）中，对于每位数，都存在至少一组中这位数 $\ge x$。

可以考虑状态压缩，若一位数 $\ge x$，用 $1$ 表示，否则为 $0$。

预处理时枚举三个状态 $a$，$b$ 和 $c$（五位二进制数），若 $a\mid b\mid c=2^5-1$，状态合法，即可以满足答案。

二分 check 时枚举每种预处理出来的合法状态，看是否都出现个即可。

复杂度为 $\operatorname{O}((n+k)\times\log m)$，$m$ 为值域大小，$k$ 为总状态个数（即 $2^{15}$）。

------------

还是非常简单的。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3e3+84,maxs=2e4+84;
inline int Read(){
    int x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    return x*f;
}
struct State{
    int a,b,c;
}st[maxs];
struct Member{
    int a[5];
    inline void read(){
        for(int i=0;i<5;i++)
            a[i]=Read();
        return ;
    }
}p[maxn];
int n,l,r=1e9+7,mid,ans,cnt,s,top;
bitset<35> vis;
inline bool check(int x){
    vis.reset();
    for(int i=1;i<=n;i++){
        s=0;
        for(int j=0;j<5;j++)
            s=s*2+(p[i].a[j]>=x);
        vis[s]=1;
    }
    for(int i=1;i<=top;i++)
        if(vis[st[i].a]&&vis[st[i].b]&&vis[st[i].c])
            return 1;
    return 0;
}
int main(){
    for(int i=0;i<32;i++)
        for(int j=0;j<32;j++)
            for(int k=0;k<32;k++)
                if((i|j|k)==31)
                    st[++top]={i,j,k};
    n=Read();
    for(int i=1;i<=n;i++)
        p[i].read();
    while(l<=r){
        mid=l+r>>1;
        if(check(mid)){
            l=mid+1;
            ans=mid;
        }
        else
            r=mid-1;
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：Night_sea_64 (赞：2)

看见“最大的最小”和“最小的最大”这一类的字样，应该可以想到二分。

又看见 $n$ 的范围是 $3000$，所以想到大概二分的里面可以 $n^2$。

二分的时候已经知道答案，枚举两个人，看他们两个这五个属性的最大值是不是都满足条件。如果不满足条件，就找一个人加上使得能满足条件。怎么能快速找到有没有人的某些属性都大于等于答案呢？我们在知道答案后立刻预处理一个数组记录有没有人的某些属性都大于等于答案。可以使用状态压缩来表示每个属性选不选。

```cpp
#include<iostream>
#include<cstring>
using namespace std;
int n;
int a[3010][10],b[3010];
bool flag[32];
bool chk(int x)
{
    for(int i=0;i<32;i++)
    {
        flag[i]=0;
        for(int j=1;j<=n;j++)
        {
            int y=i;
            bool f=1;
            for(int k=5;k>=1;k--)
            {
                if(y%2&&a[j][k]<x)f=0;
                y/=2;
            }
            flag[i]|=f;
        }
    }
    bool fl=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
        {
            int y=0;
            for(int k=1;k<=5;k++)
                y=y*2+(max(a[i][k],a[j][k])<x);
            fl|=flag[y];
        }
    return fl;
}
int main()
{
    memset(b,999999,sizeof(b));
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=5;j++)
        {
            cin>>a[i][j];
            b[i]=min(b[i],a[i][j]);
        }
    int l=1,r=1e9,ans=0;
    while(l<=r)
    {
        int m=(l+r)/2;
        if(chk(m))l=m+1,ans=m;
        else r=m-1;
    }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Galois_Field_1048576 (赞：1)

考虑推广情况: $k$ 种属性, 选 $m$ 人.
($1 \le k \le 15; 1 \le m \le n$)

二分答案, 设 `mid` 值为 $x$. $O(kn)$ 地计算
$$
V_i = \sum_{j=0}^{k-1} [a_{i,j} \ge x] 2^j
$$
, 于是只需判断 是否存在一个 $k_1,k_2,\dots,k_m$ 满足 
$$
\bigvee_{i=1}^m k_i = 2^k-1
$$
. 使用桶数组 ${\rm Buc}$, 则只需判断
$$
\sum_{i_1 \vee i_2 \vee \dots \vee i_m = 2^k-1} \prod_{j=1}^m k_{i_j}
$$
是否为 $0$ 即可. FWT 即可.
时间复杂度: $O((k2^k + kn) \log X)$, 其中 $X = \max_{i,j} a_{i,j}$.

---

## 作者：technopolis_2085 (赞：0)

分析：

题目要求的是最小值的最大值，所以考虑二分答案。

假设当前二分到的答案是 $x$，那么，即要求团队的力量、速度、技巧、知识、想象力的最小值都大于等于 $x$。

由于 $N ≤ 3000$，所以可以枚举两个人 $i$ 和 $j$。

先计算出来 $i$ 和 $j$ 的力量、速度、技巧、知识、想象力，然后分类讨论：（以“力量”指标为例）

如果最大值大于等于 $x$，则不管第三个人的力量指标为多少，都可以使团队的力量值大于等于 $x$。

如果最大值小于 $x$，则第三个人的力量指标必须大于等于 $x$，否则团队的力量值小于 $x$，团队的综合力必然小于 $x$，答案不合法。

所以，应该对这五项指标中所有小于 $x$ 的指标中找一个同时满足指标都大于等于 $x$ 的一个人，找得到即答案合法，找不到即答案不合法。

由于有 $5$ 项指标，所以最多有 $2^5 = 32$ 种情况，对于这 $32$ 种情况，开 $32$ 个 set，每次查找这个 set 中有没有既不等于 $i$ 也不等于 $j$ 的数，如果有，则答案合法。

code：
```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn=3010;
struct node{
	int num[10];
};

node a[maxn];
int n;

bool check(int x){
	set<int> st[35];
	for (int i=0;i<32;i++) st[i].clear();
	
	for (int mask=0;mask<32;mask++){
		for (int i=1;i<=n;i++){
			int flag=0;
			for (int j=0;j<5;j++){
				if ((mask&(1<<j))){
					if (a[i].num[j]<x) flag=1;
				}
			}
			
			if (flag==0) st[mask].insert(i);
		}
	}
	
	for (int i=1;i<=n;i++){
		for (int j=i+1;j<=n;j++){
			int cnt[5];
			memset(cnt,0,sizeof(cnt));
			for (int k=0;k<5;k++) cnt[k]=max(a[i].num[k],a[j].num[k]);
			
			int mask=0;
			for (int k=0;k<5;k++){
				if (cnt[k]<x) mask+=(1<<k);
			}
			
			for (set<int>::iterator it=st[mask].begin();it!=st[mask].end();it++){
				if ((*it)==i) continue;
				if ((*it)==j) continue;
				else return true;
			}
		}
	}
	return false;
}

int main(){
	scanf("%d",&n);
	
	for (int i=1;i<=n;i++){
		for (int j=0;j<5;j++) scanf("%d",&a[i].num[j]);
	}
	
	int l=0,r=1e9+7;
	int ans=0;
	while (l<=r){
		int mid=(l+r)/2;
		
		if (check(mid)){
			ans=mid;
			l=mid+1;
		}else r=mid-1;
	}
	
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：cppcppcpp3 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_zone2021_c)。

## Solution

答案满足单调性，考虑二分。

对于待检验的 $x$，我们可以预处理出每个人的 $a,b,c,d,e$ 分别是否可以达到要求。发现只有 $5$ 位，所以还可以进行状态压缩，用一个小于 $32$ 的整数 $f_i$ 来表示。那么验证 $x$ 的过程就变成了从 $f$ 数组中选三个数 $f_x,f_y$ 和 $f_z$，使得这三个数按位或后的结果为 $31$（即 $2^5-1$）。

枚举 $x,y$，设 $res=(f_x | f_y) \oplus 31$，则 $res$ 在二进制下是 $f_z$ 的子集。在预处理时，对于每个 $f_i$ 枚举其子集（包括 $0$）并将其标记即可。

复杂度：$O(n^2 \log m)$，其中 $m=10^9$，所以 $\log m$ 约为 $30$。

## Code
```cpp
#include<bits/stdc++.h>
#define il inline
#define S (1<<5)
using namespace std;
const int N=3005;
const int inf=1e9+7;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=x*10+c-48;c=getchar();}
	return x*f;
}

int n,ans,w[N][5],f[N],mp[S];

bool check(int x){
	mp[0]=1;
	for(int i=1;i<S;++i) mp[i]=0;
	for(int i=1;i<=n;++i){ //将每个人能达到的方面用二进制表示。
		f[i]=0;
		for(int j=0;j<5;++j) f[i]|=((w[i][j]>=x)<<j);
		for(int j=f[i];j;j=(j-1)&f[i]) mp[j]=1; //枚举子集表示可以用一个人达到此状态。
	}
	for(int i=1;i<=n;++i){ //枚举前两个人，判断第三个人能否满足要求。
		for(int j=1;j<=n;++j){
			int res=(S-1)^(f[i]|f[j]);
			if(mp[res]) return 1;
		}
	}
	return 0;
}

main() {
	n=wrd();
	for(int i=1;i<=n;++i) for(int j=0;j<5;++j) w[i][j]=wrd();
	
	int l=1,r=1e9;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return printf("%d",ans),0;
}
```

---

## 作者：ktq_cpp (赞：0)

# [题面](https://www.luogu.com.cn/problem/AT_zone2021_c)

这道题第一眼看过去并没有找到头绪，但仔细想想会发现这道题满足单调性，因此我们可以考虑二分答案。

枚举前两个人，判断有哪些能力还没有达到目标，预处理满足缺陷的人是否存在，判断即可。

时间复杂度为 $O(n^2$ $\log_{2}10^9)$ ，足以通过本题。

```cpp
#include<bits/stdc++.h>
#define int long long
#define repe(i,l,r) for(int (i)=l;(i)<=r;(i)++)
#define rep(i,n) for(int (i)=1;(i)<=n;(i)++)
#define FOR(i,r,l) for(int (i)=r;(i)>=l;(i)--)
#define INF 0x3f3f3f
#define pii pair<int,int>
#define mpr make_pair
#define pb push_back
#define ALL(v) (v).begin(),(v).end()
#define rsort(v) sort(ALL(v),greater<int>())
#define lb(v,x) (int)(lower_bound(ALL(v),x)-v.begin())
#define ub(v,x) (int)(upper_bound(ALL(v),x)-v.begin())
#define uni(v) v.resize(unique(ALL(v))-v.begin())
using namespace std;
int read(){int sum=0,f=1;char c;c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){sum=(sum<<1)+(sum<<3)+(c-'0');c=getchar();}return sum*f;}
void out(int x){if(x<0){x=-x;putchar('-');}if(x>=10)out(x/10);putchar(x%10+'0');}
template <typename T>void die(T s){cout<<s<<endl;exit(0);}
int fast(int a,int b,int P){int res=1;if(P<=0){while(b){if(b&1)res=res*a;a=a*a;b>>=1;}}else{while(b){if(b&1)res=res*a%P;a=a*a%P;b>>=1;}}return res;}
template <typename T>void chkmax(T& a,T b){if(a<b)a=b;return;}
template <typename T>void chkmin(T& a,T b){if(a>b)a=b;return;}
int a[3005],b[3005],c[3005],d[3005],e[3005],n;
int cann[3005];
bool check(int x){
	memset(cann,0,sizeof(cann));
	for(int i=1;i<=n;i++){
		int s=0;
		if(a[i]>=x)s|=1;
		if(b[i]>=x)s|=2;
		if(c[i]>=x)s|=4;
		if(d[i]>=x)s|=8;
		if(e[i]>=x)s|=16;
		cann[s]=1;
		for(int j=s;j;j=(j-1)&s)cann[j]=1;
	}
	cann[0]=1;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			int s=0;
			if(a[i]>=x)s|=1;
			if(b[i]>=x)s|=2;
			if(c[i]>=x)s|=4;
			if(d[i]>=x)s|=8;
			if(e[i]>=x)s|=16;
			if(a[j]>=x)s|=1;
			if(b[j]>=x)s|=2;
			if(c[j]>=x)s|=4;
			if(d[j]>=x)s|=8;
			if(e[j]>=x)s|=16;
			s=s^31;
			if(cann[s])return 1;
		}
	}
	return 0;
}
signed main(){
	n=read();
	rep(i,n)a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read(),e[i]=read();
	int l=1,r=1000000000,ans;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	out(ans);
	return 0;
}
```


---

