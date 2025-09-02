# T-shirts Distribution

## 题目描述

The organizers of a programming contest have decided to present t-shirts to participants. There are six different t-shirts sizes in this problem: S, M, L, XL, XXL, XXXL (sizes are listed in increasing order). The t-shirts are already prepared. For each size from S to XXXL you are given the number of t-shirts of this size.

During the registration, the organizers asked each of the $ n $ participants about the t-shirt size he wants. If a participant hesitated between two sizes, he could specify two neighboring sizes — this means that any of these two sizes suits him.

Write a program that will determine whether it is possible to present a t-shirt to each participant of the competition, or not. Of course, each participant should get a t-shirt of proper size:

- the size he wanted, if he specified one size;
- any of the two neibouring sizes, if he specified two sizes.

If it is possible, the program should find any valid distribution of the t-shirts.

## 样例 #1

### 输入

```
0 1 0 1 1 0
3
XL
S,M
XL,XXL
```

### 输出

```
YES
XL
M
XXL
```

## 样例 #2

### 输入

```
1 1 2 0 1 1
5
S
M
S,M
XXL,XXXL
XL,XXL
```

### 输出

```
NO
```

# 题解

## 作者：xzggzh1 (赞：1)

题意：

有 $6$ 种尺码的衣服，有的人只适合 $1$ 种衣服，有的人适合相邻的 $2$ 种,问是否存在合法方案，并输出。

----

首先，如果一些人只适合一种衣服，那么根本不有抉择，直接减去即可。

然后我们考虑剩下的人。

每一个人都有两种选择，这是网络流的经典题，但这里并不用，直接贪心即可：

对于只适合第一种和第二种的，优先选择第一种，然后考虑只适合第二种和第三种的……显然，每次我们考虑的时候优先选的那一种在当时的情况下只能为一种人做出贡献，不然就直接浪费了，所以贪心的先选就好了。

核心代码:

```cpp
int main()
{
	for ( int i = 0; i < 6; i++ )
		cin >> a[i];
	cin >> n; for ( int i = 0; i < n; i++ )
	{
		cin >> s[i]; 
		for ( int j = 0; j < 6; j++ )
		if ( s[i] == as[j] ) a[j]--;
	}
	for ( int i = 0; i < 6; i++ )
	if ( a[i] < 0 ) return(cout << "NO\n", 0);
	for ( int t = 0; t < 5; t++ )
	for ( int i = 0; i < n; i++ )
	if ( s[i] == cmp[t] )if ( a[t] > 0 )
	a[t]--, s[i] = as[t];
	else if ( a[t + 1] > 0 ) a[t + 1]--, s[i] = as[t + 1];
	else return(cout << "NO\n", 0);
	cout << "YES\n"; 
	for ( int i = 0; i < n; i++ )
	cout << s[i] << '\n';
}
```

---

## 作者：wmrqwq (赞：0)

duel 到的。

# 题目链接

[CF727D (luogu)](https://www.luogu.com.cn/problem/CF727D)

[CF727D (codeforces)](https://codeforces.com/problemset/problem/727/D)

# 解题思路

首先只能选一个尺码的人直接给就是了，这样我们就只用考虑选两个尺码的人了。

因为适合穿两个尺码衣服的人的适合穿的两个尺码是相邻的，因此我们直接从小到大按照有两个尺码的人排序，再将剩下的衣服大小从小到大排序，然后依次将衣服给这些人就可以了。

这里我用了桶排，时间复杂度 $O(n)$。

# 参考代码

```cpp
/*
Tips:
你数组开小了吗？
你MLE了吗？
你觉得是贪心，是不是该想想dp？
一个小时没调出来，是不是该考虑换题？
打 cf 不要用 umap！！！

记住，rating 是身外之物。

该冲正解时冲正解！

Problem:

算法：

思路：

*/
#include<bits/stdc++.h>
using namespace std;
//#define map unordered_map
#define re register
#define ll long long
#define forl(i,a,b) for(re ll i=a;i<=b;i++)
#define forr(i,a,b) for(re ll i=a;i>=b;i--)
#define forll(i,a,b,c) for(re ll i=a;i<=b;i+=c)
#define forrr(i,a,b,c) for(re ll i=a;i>=b;i-=c)
#define lc(x) x<<1
#define rc(x) x<<1|1
#define mid ((l+r)>>1)
#define cin(x) scanf("%lld",&x)
#define cout(x) printf("%lld",x)
#define lowbit(x) (x&-x)
#define pb push_back
#define pf push_front
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define db long double
#define ull unsigned long long
#define lcm(x,y) x/__gcd(x,y)*y
#define Sum(x,y) 1ll*(x+y)*(y-x+1)/2
#define aty cout<<"Yes\n";
#define atn cout<<"No\n";
#define cfy cout<<"YES\n";
#define cfn cout<<"NO\n";
#define xxy cout<<"yes\n";
#define xxn cout<<"no\n";
#define printcf(x) x?cout<<"YES\n":cout<<"NO\n";
#define printat(x) x?cout<<"Yes\n":cout<<"No\n";
#define printxx(x) x?cout<<"yes\n":cout<<"no\n";
#define maxqueue priority_queue<ll>
#define minqueue priority_queue<ll,vector<ll>,greater<ll>>
ll t;
ll a[10];
ll pw(ll x){
	return 1ll<<x;
}
string s;
ll n,b[100010];
ll ans[100010];
void print(ll x)
{
	if(!x)
		cout<<"Failed.\n";
	else if(x==1)
		cout<<"S\n";
	else if(x==2)
		cout<<"M\n";
	else if(x==3)
		cout<<"L\n";
	else
	{
		forl(i,1,x-3)
			cout<<"X";
		cout<<"L\n";
	}
}
/*
1 2 4 4 1 1
10
XL
XL
S,M
L
M,L
L
S,M
M
XL,XXL
XL
*/
void solve()
{
	forl(i,0,5)
		cin>>a[i];
	cin>>n;
	forl(i,1,n)
	{
		cin>>s;
		ll pd=0;
		forl(j,0,(ll)s.size()-1)
			if(s[j]==',')
				pd=1;
		if(!pd)
		{
			if(s=="S")
				b[i]|=pw(0);
			else if(s=="M")
				b[i]|=pw(1);
			else if(s=="L")
				b[i]|=pw(2);
			else if(s=="XL")
				b[i]|=pw(3);
			else if(s=="XXL")
				b[i]|=pw(4);
			else
				b[i]|=pw(5);
		}
		else
		{
			string S="";
			ll wz=0;
			forl(j,0,(ll)s.size()-1)
			{
				if(s[j]!=',')
					S+=s[j];
				else
				{
					wz=j;
					break;
				}
			}
			if(S=="S")
				b[i]|=pw(0);
			else if(S=="M")
				b[i]|=pw(1);
			else if(S=="L")
				b[i]|=pw(2);
			else if(S=="XL")
				b[i]|=pw(3);
			else if(S=="XXL")
				b[i]|=pw(4);
			else
				b[i]|=pw(5);
			S="";		
			forl(j,wz+1,(ll)s.size()-1)
			{
				if(s[j]!=',')
					S+=s[j];
				else
				{
					wz=j;
					break;
				}
			}
			if(S=="S")
				b[i]|=pw(0);
			else if(S=="M")
				b[i]|=pw(1);
			else if(S=="L")
				b[i]|=pw(2);
			else if(S=="XL")
				b[i]|=pw(3);
			else if(S=="XXL")
				b[i]|=pw(4);
			else
				b[i]|=pw(5);	
		}
	}
	forl(i,0,5)
		forl(j,1,n)
			if(b[j]==pw(i))
			{
				if(!a[i])
				{
					cfn;
					return ;
				}
				a[i]--;
				ans[j]=i+1;
			}
	forl(i,0,5)
	{
		forl(j,1,n)
			if(!ans[j])
				if((b[j]&pw(i))==pw(i) && b[j]<pw(i)*2)
					if(a[i])
						a[i]--,ans[j]=i+1;
		forl(j,1,n)
			if(!ans[j])
				if((b[j]&pw(i))==pw(i))
					if(a[i])
						a[i]--,ans[j]=i+1;		
	}
//	cout<<b[7]<<endl;
	forl(i,1,n)
		if(ans[i]==0)
		{
			cfn;
			return ;
		}
	cfy;
	forl(i,1,n)
		print(ans[i]);
}
int main()
{
	IOS;
	t=1;
 //	cin>>t;
	while(t--)
		solve();
    /******************/
	/*while(L<q[i].l) */
	/*    del(a[L++]);*/
	/*while(L>q[i].l) */
	/*    add(a[--L]);*/
	/*while(R<q[i].r) */
	/*	  add(a[++R]);*/
	/*while(R>q[i].r) */
	/*    del(a[R--]);*/
    /******************/
	QwQ;
}
```

---

## 作者：Erica_N_Contina (赞：0)

## 思路

先把一定要分配的分配了，剩下的就是一个 ~~2-SAT 问题~~。

或者我们可以不用考虑那么复杂——也许就是个贪心。

注：下面的“人”指的是可以有两种选择的人。

因为每个人都只有可能选择两款相邻的尺码，我们按每个人第一款尺码从小到大排序后从小到大贪心地分配各个款式的衣服即可，即优先分配尺码小的衣服，不够了再分配尺码大的。

其它真的就没了。

---

**一些字符串操作**

`t.find(",",0)` 返回字符串 $t$ 中第一个 `,` 的下标。

`t.substr(0, pos)` 取出下标范围内的子串，返回值为 `string`。

---

```C++
/*
CB Ntsc
*/

#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int, int>
#define pf first
#define ps second

#define err cerr<<"Error"
#define rd read()
// #define nl putc('\n')
#define ot write
#define nl putchar('\n')
inline int rd
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}

const int INF = 1e9;
const int N = 2e6+5;
const int M = 1e6+5;
const int S=1e6+5;
const int maxlog = 10;
string ds[10]={"S","M","L","XL","XXL","XXXL"};
struct node{
	int a,b,id;
}p[N];
int tot;
int ans[N];
int c[N],n;
void cal(string s,int id,int f,int idx){
	for(int i=0;i<6;i++){
		if(ds[i]==s){
			if(f==1)p[id].a=i,p[id].id=idx;
			if(f==2)p[id].b=i,p[id].id=idx;
			if(!f){
				ans[idx]=i;
				c[i]--;
				if(c[i]<0){
					cout<<"NO"<<endl;
					exit(0);
				}
				return ;
			}
			
		}
	}
}
bool cmp(node a,node b){
	return a.a<b.a;
}

signed main(){
	for(int i=0;i<6;i++)c[i]=rd;
	n=rd;
	for(int i=1;i<=n;i++){
		string s;
		cin>>s;
		int pos=s.find(",",0);
		if(pos==EOF){
			cal(s,0,0,i);
		}else{
			cal(s.substr(0,pos),++tot,1,i);
			cal(s.substr(pos+1,s.size()-1),tot,2,i);
		}

	}

	// for(int i=1;i<=tot;i++){
	// 	cerr<<p[i].a<<' '<<p[i].b<<endl;
	// }

	sort(p+1,p+tot+1,cmp);
	for(int i=1;i<=tot;i++){
		int a=p[i].a,b=p[i].b,id=p[i].id;
		if(c[a])c[a]--,ans[id]=a;
		else c[b]--,ans[id]=b;
		if(c[b]<0){
			cout<<"NO"<<endl;
			return 0;
		}
	}
	cout<<"YES\n";
	for(int i=1;i<=n;i++){
		cout<<ds[ans[i]]<<endl;
	}
}
/*
2 5
0 1 1 1 1
0 1 1 2 4
0 2 1 2 1
0 2 1 1 4
*/
```




---

