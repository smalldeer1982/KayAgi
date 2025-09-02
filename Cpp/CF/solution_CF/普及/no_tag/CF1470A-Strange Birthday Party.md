# Strange Birthday Party

## 题目描述

Petya 举办了一场奇怪的生日聚会。 他邀请了 $n$ 个朋友并分配一个整数 $k_i$ 给第 $i$ 
个朋友。现在 Petya 想要给每个朋友送一个礼物，而附近的商店有 $m$ 种不同的礼物，其中第  $j$ 种的价格为 $c_j$ 美元 $( 1 \le c_1 \le c_2 \le \ldots \le c_m )$。每种礼物最多买一件。

对于第 $i$ 个朋友，Petya 可以选择给他买第 $j$ 种礼物 $( j \le k_i )$ , 花费 $c_j$ 美元；或者选择直接给他 $c_{k_i}$ 美元。

请你帮助 Petya 计算举办生日聚会需要的最小花费。

## 说明/提示

在第一个示例中，有两个测试用例。在第一个测试用例中，Petya 有个 5 朋友和 4 种可选的礼物。Petya 只用花费 30 美元，如果他给
- 第一个朋友 5 美元。
- 第二个朋友价格为 12 美元的礼物。
- 第三个朋友价格为 5 美元的礼物。
- 第四个朋友价格为 3 美元的礼物。
- 第五个朋友 5 美元。

在第二个测试用例中，Petya 有个 5 朋友和 5 种可选的礼物。Petya 只要消费 190 美元，如果他给
- 第一个朋友价格为 10 美元的礼物。
- 第二个朋友价格为 40 美元的礼物。
- 第三个朋友 90 美元。
- 第四个朋友 40 美元。
- 第五个朋友 10 美元。

## 样例 #1

### 输入

```
2
5 4
2 3 4 3 2
3 5 12 20
5 5
5 4 3 2 1
10 40 90 160 250```

### 输出

```
30
190```

## 样例 #2

### 输入

```
1
1 1
1
1```

### 输出

```
1```

# 题解

## 作者：Symbolize (赞：5)

# 思路
不难发现，价值小的礼物一定要留给号码大的人，因为如果号码大的人拿钱拿得肯定比号码小的人拿钱拿得多。所以我们可以先将 $k$ 数组从大到小排序。我们选取礼物的条件是当前礼物未被选择且小于等于 $k_i$。所以我们选取礼物的判断语句就是：
```cpp
int id=1/*从最便宜的礼物选起，选完这个礼物id的值就加1，跳到下一个礼物*/,ans=0/*记录答案*/;
for(int i=1;i<=n;i++)
{
	if(c[id]<c[k[i]]) ans+=c[id++];//拿礼物
	else ans+=c[k[i]];//拿钱
}
```
最后输出答案就结束了！

# Code
下面附上 AC 代码！！！
```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=3e5+10;
using namespace std;
int t,n,m,k[N],c[N];
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
bool cmp(int a,int b){return a>b;}
void getans()
{
	n=read();
	m=read();
	rep1(i,1,n) k[i]=read();
	rep1(i,1,m) c[i]=read();
	sort(k+1,k+n+1,cmp);//从大到小排序
	int id=1,ans=0;
	rep1(i,1,n)//循环，里面判断每个人选择拿钱还是拿礼物
	{
		if(c[id]<c[k[i]]) ans+=c[id++];//拿礼物
		else ans+=c[k[i]];//拿钱
	}
	cout<<ans<<endl;//输出
	return;
}
signed main()
{
	t=read();
	while(t--) getans();//t次询问
	return 0;//收场
}
```

---

## 作者：_lxy_ (赞：3)

### 题意
有 $n$ 个人，第 $i$ 个人有一个编号 $k_i$ ,还有 $m$ 个按价格升序排列的礼物，第 $i$ 个礼物价格为 $c_i$ ,对于第 $i$ 个人，可以给他送前 $k_i$ 个礼物中的一个，也可以给他送 $c_{k_i}$ 美元，问最少花费是多少。
### 分析
根据题意我们不难看出，因为礼物是按价格升序排列的，所以送礼物的花费一定不超过送钱的花费，但是礼物不能重复送，因此我们可以想出贪心策略：**尽量先给编号大的人选**。我们可以用一个变量来存目前没取过的礼物中编号最靠前的一个，如果最便宜的礼物比送钱的花费更大，就送钱，否则就送礼物。
### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll T,n,m,ans;
vector<ll>k;
vector<ll>c;
int main()
{
    scanf("%lld",&T);
    while(T--)
    {
        k.clear();
        c.clear();
        ans=0;
        scanf("%lld%lld",&n,&m);
        ll i,j;
        for(i=0;i<n;i++)
        {
            ll x;
            scanf("%lld",&x);
            x--; //因为是从0存的，所以编号要-1
            k.push_back(x);
        }
        for(i=0;i<m;i++)
        {
            ll x;
            scanf("%lld",&x);
            c.push_back(x);
        }
        sort(k.begin(),k.end(),greater<ll>()); //把k数组按编号降序排列，目的是确保编号大的人能够先选礼物
        j=0; //目前最便宜的礼物的位置
        for(i=0;i<n;i++)
        {
            if(c[j]<c[k[i]]) //送礼物划算
            {
                ans+=c[j++];
            }
            else ans+=c[k[i]]; //送钱划算
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```


---

## 作者：vectorwyx (赞：3)

（本篇博客同步于[CSDN](https://blog.csdn.net/vectorwyx/article/details/112260203)）

假设有 $x$ 人直接拿钱，我们选择让 $k$ 最小的那 $x$ 个人来拿钱肯定是最优的，因为这样能使得剩下的 $n-x$ 个人选择的余地最大，并且代价最小。把 $k$ 排序后对 $c_{k_{i}}$ 做前缀和。这就转化为了在两个递增数组上依次取一段长为 $x$ 的前缀和一段长为 $m-x$ 的后缀使得和最小，这显然是一个关于 $x$ 的单谷函数，直接无脑三分就能解决。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define ll long long
#define fo(i,x,y) for(register int i=x;i<=y;++i)
#define go(i,x,y) for(register int i=x;i>=y;--i)
using namespace std;

inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*fh;
}

const int N=3e5+5;
int k[N],c[N];
ll S1[N],S2[N];

void work(){
	int n=read(),m=read();
	ll ans=1e18;
	fo(i,1,n) k[i]=read();//n个顾客 
	fo(i,1,m) c[i]=read(),S2[i]=S2[i-1]+c[i];//m件礼品
	sort(k+1,k+1+n);
	fo(i,1,n) S1[i]=S1[i-1]+c[k[i]];
	int L=max(0,n-m),R=n,mid1,mid2;
	while(R-L>5){
		mid1=L+(R-L)/3,mid2=R-(R-L)/3;
		ll v1=S1[mid1]+S2[n-mid1],v2=S1[mid2]+S2[n-mid2];
		if(v1<=v2) R=mid2;
		else L=mid1;
	}
	fo(i,L,R) ans=min(ans,S1[i]+S2[n-i]);
	printf("%lld\n",ans);
	//puts("");
}
int main(){
	int T=read();
	while(T--){
		work();
	}
	return 0;
}
```

---

## 作者：fanfansann (赞：3)

小鹿马上就要生日了！让我们祝她生日快乐！因为马上就要生日了，小鹿准备开一个生日派对，邀请了 $n$ 位朋友，并且给第 $i$ 位朋友分配了一个编号 $k_i$，现在小鹿要给她们**每人一个礼物**， 商店里有价格 **从小到大** 的 $m$ 件各不相同的商品，每一件商品都只有一件，每件商品只能买一次，其中第 $j$ 个商品需要花费小鹿 $c_j$ 元（$1\le c_1\le c_2\le \cdots \le c_m$），对于第 $i$ 个朋友，小鹿**要么**给这个朋友从商店里买一个编号为$j$ 的商品， 其中$1\le j\le k_i$，花费 $c_j$ 元，**要么**直接给这位朋友 $c_{k_i}$ 元，而不需要购买礼物。小鹿是一个很节省的好孩子，她想知道最少需要花费多少钱？

$1 \leq t \leq 10^3,1 \leq n, m \leq 3 \cdot 10^5,1 \leq k_i \leq m,1 \le c_1 \le c_2 \le \ldots \le c_m \le 10^9$

其中保证所有的测试数据中，每次的测试数据的所有 $case$ 的 $n$ 之和以及 $m$ 之和都不超过 $3\times10^5$。

**Solution** 

我们发现本题的解题关键在于，所有的商品的价格是从小到大递增的，读懂题意以后，我们就可以自然地发现当无法购买商品，也就是就那么几个，卖完了之后， $k_i$ 小的，选择第二种方法，花费 $c_{k_i}$ ，不占用宝贵的商品资源，是一定比 $k_i$ 大的选择方法二总花费更少，所以 $k_i$ 小的就放到后面最后选，因为他有保底。让 $k_i$ 大的先选，先买前面便宜的商品，不得已的时候才直接送钱。这样花费最小。所以就是按照每个人的编号 $k_i$ 从大到小排序，然后贪心模拟即可。
```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 5e5 + 7, mod = 1e9 + 7;
typedef long long ll;
int n, m, t, x;
int k[N], c[N];

int main()
{
    scanf("%d", &t);
    while(t -- ) {
        ll ans = 0;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++ i) {
            scanf("%d", &k[i]);
        }
        for(int i = 1; i <= m; ++ i) {
            scanf("%d", &c[i]);
        }
        sort(k + 1, k + 1 + n);
        reverse(k + 1, k + 1 + n);
        int now = 1;
        for(int i = 1; i <= n; ++ i) {
            if(c[k[i]] <= c[now]) {
                ans += c[k[i]];
            }
            else ans += c[now], now ++ ;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：CQ_Bab (赞：2)

# 思路
这道题我们通过题目和样例一得出结论：因为 $c$ 是单调递增的所以我们先将 $k$ 大的给他弄掉，再弄小的。那么怎么改呢？我们发现在排完序之后，我们对于每一个 $k_i$ 只需要判断当时对应的那个取到的 $id$（因为 $c$ 是递增的所以我们取了 $1$ 就去取 $2$ 而不用继续往后找最小值）与他的 $c_{k_i}$ 进行比较如果 $id$ 的那个大就将 $id$ 加一并统计及答案即可，否则将答案加上 $c_{k_i}$。最后输出答案就行了。
# AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std ;
#define int long long
int n,m,t,res;
int k[1001000],c[1001000];
bool f[1001000];
bool cmp(int a,int b) {
	return a>b;
}
signed main() {
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>t;
	while(t--) {
		memset(f,0,sizeof f); //初始化
		res=0; //初始化
		cin>>n>>m;
		for(int i=1; i<=n; i++) cin>>k[i];
		sort(k+1,k+1+n,cmp); //先弄大的
		for(int i=1; i<=m; i++) cin>>c[i];
		int num=1;
		for(int i=1; i<=n; i++) {
			if(c[num]<c[k[i]]) res+=c[num],num++; //找后一位
			else res+=c[k[i]];
		}
		cout<<res<<endl;
	}
	return false;
}
```


---

## 作者：suyue1098765432 (赞：2)

题目大意：

你有 $n$ 个朋友， $m$ 种礼物 ，第 $i$ 种礼物花费 $c_i$ ,对于每个人，你都要选$[1,k_i]$中的一个礼物送给他，或是给他 $c_{k_i}$的钱，每个礼物只能被送一次，问最小花费。


思路 ：

这个题是一个带反悔的贪心，都先将 $k_i$ 有从小到大排序，然后枚举 $k$ ，将所有的小于 $k_i$ 的礼物加到一个堆中，然后此时若最小元素比 $c_{k_i}$ 大，那么直接给他钱，否则把这个礼物给$i$，并把这个元素从堆中删除。

考虑反悔，已将价值$c_i$的礼物送给了$a$，如果要把它给$b$，那么就要给$a$,$c_{k_i}$的钱，这等价于给$b$送了个价值$c_{k_i}$的礼物的礼物，所以可以直接在礼物送给$i$后，在堆中加入一个价值$c_{k_i}$的礼物，这样就能得到正确答案。

code:

C:

```c
#include<stdio.h>
struct node{
	int s,id;
}a[300010],pxr[300010];
int sl[300010];
int n,m;
int q[300010],lenq;
void px(int l,int r){
	if(l==r)return ;
	int mid=(l+r)>>1;
	int k=l,s=mid+1,p=l;
	px(l,mid);px(mid+1,r);
	while(k<=mid&&s<=r)
		if(a[k].s<=a[s].s)pxr[p++]=a[k++];
		else pxr[p++]=a[s++];
	while(k<=mid)pxr[p++]=a[k++];
	while(s<=r)pxr[p++]=a[s++];
	for(p=l;p<=r;p++)a[p]=pxr[p];
	return ;
}
int getq(){
	int res,p;int now,next;
	res=q[1];
	q[1]=q[lenq--];
	now=1;
	while((next=now<<1)<=lenq){
		if(next<lenq&&q[next+1]<q[next])next++;
		if(q[now]<=q[next])break;
		p=q[now];q[now]=q[next];q[next]=p;
		now=next;
	}
	return res;
}
void putq(int res){
	int p;int now,next;
	q[++lenq]=res;
	now=lenq;
	while((next=now>>1)>0){
		if(q[now]>=q[next])break;
		p=q[now];q[now]=q[next];q[next]=p;
		now=next;
	}
	return;
}
int read(){
	int res=0,zf=1;char ch;
	while((ch=getchar())<48||ch>57)if(ch=='-')zf=!zf;res=(ch^48);
	while((ch=getchar())>=48&&ch<=57)res=(res<<3)+(res<<1)+(ch^48);
	return zf?res:(-res);
}
int main(){
	int T=read();
	while(T--){
		long long add=0;
		lenq=0;
		n=read();m=read();
		for(int i=1;i<=n;i++){
			a[i].s=read();
			a[i].id=i;
		}
		px(1,n);
		for(int i=1;i<=m;i++)
			sl[i]=read();
		int cnt=1;
		for(int i=1;i<=n;i++){
			while(cnt<=a[i].s){
				putq(sl[cnt]);
				cnt++;
			}
			if(lenq>0&&q[1]>=sl[a[i].s])add+=sl[a[i].s];
			else {
				add+=getq();
				putq(sl[a[i].s]);
			}
		}
		printf("%lld\n",add);
	}
	return 0;
}
```

pascal:

```pascal
type node=record
	s,id:longint;
end;
var
	a,pxr:array[0..300000]of node;
	sl,q:array[0..300000]of longint;
	n,m,lenq:longint;
procedure px(l,r:longint);
var mid,k,s,p:longint;
begin
	if l=r then exit();
	mid:=(l+r)div 2;
	k:=l;s:=mid+1;p:=l;
	px(l,mid);px(mid+1,r);
	while(k<=mid)and(s<=r)do
		if a[k].s<=a[s].s then begin
			pxr[p]:=a[k];
			p:=p+1;k:=k+1;
		end else begin
			pxr[p]:=a[s];
			p:=p+1;s:=s+1;
		end;
	while k<=mid do begin
		pxr[p]:=a[k];
		p:=p+1;k:=k+1;
	end;
	while s<=r do begin
		pxr[p]:=a[s];
		p:=p+1;s:=s+1;
	end;
	for p:=l to r do a[p]:=pxr[p];
	exit();
end;
function getq():longint;
var res,p,now,next:longint;
begin
	res:=q[1];
	q[1]:=q[lenq];
	lenq:=lenq-1;
	now:=1;
	while(now*2)<=lenq do begin
		next:=now*2;
		if(next<lenq)and(q[next+1]<q[next])then next:=next+1;
		if q[now]<=q[next] then break;
		p:=q[now];q[now]:=q[next];q[next]:=p;
		now:=next;
	end;
	exit(res);
end;
procedure putq(res:longint);
var p,now,next:longint;
begin
	lenq:=lenq+1;
	q[lenq]:=res;
	now:=lenq;
	while now>1 do begin
		next:=now div 2;
		if q[now]>=q[next] then break;
		p:=q[now];q[now]:=q[next];q[next]:=p;
		now:=next;
	end;
	exit();
end;
var 
	T,i,h,cnt:longint;
	add:int64;
begin
	read(T);
	for h:=1 to T do begin
		add:=0;
		lenq:=0;
		read(n,m);
		for i:=1 to n do begin
			read(a[i].s);
			a[i].id:=i;
		end;
		px(1,n);
		for i:=1 to m do read(sl[i]);
		cnt:=1;
		for i:=1 to n do begin
			while cnt<=a[i].s do begin
				putq(sl[cnt]);
				cnt:=cnt+1;
			end;
			if(lenq>0)and(q[1]>=sl[a[i].s])then add:=add+sl[a[i].s]
			else begin
				add:=add+getq();
				putq(sl[a[i].s]);
			end;
		end;
		writeln(add);
	end;
	exit();
end.
```

---

## 作者：Need_No_Name (赞：0)

# Solution For CF1470A
## Step1:题意
有 $n$ 个人，$m$ 种价值的礼物。现给定每个人一个编号 $k_i$ ,可以在 $m$ 种礼物中任意选一个礼物或者是选 $k_i$ 的价值。
## Step2:分析
看样子，这道题第一眼像是一个暴力完事儿，也差不多对得起这个道题的“普及/普及-”的黄色小标签（实际上我在比赛中也是这么想的，死的很惨QAQ）,再看看数据范围， $1≤n,m≤3·10^5$ , $O(n^2)$ ，绝对会炸，于是我们就考虑考虑更clever的做法，贪心。

## Step3:思路
那么，贪心策略是甚么呢？

首先，由题意可知,价值是升序排序的，那就意味编号最大的人要给现金的时候花费最多，所以，我们可以试试将存储编号的 $k$ 数组从大到小排序，然后先从编号最大的人进行处理,不断比较给现金还是给礼物便宜还是给现金便宜，给礼物时就每次无脑选最便宜即可。

## Step4:Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=500005;
bool cmp(int x,int y)
{
	return x>y;
}
int c2[N];
int k[N];
int c[N];
int T;
int n,m;
int ans=0;
int cnt=1;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	while(T--)
	{
		cnt=1;
		ans=0;
		memset(c2,0,sizeof(c2));//注意初始化 
		cin>>n>>m;
		for(int i=1;i<=n;i++)
		{
			cin>>k[i];
		}
		for(int i=1;i<=m;i++)
		{
			cin>>c[i];
		}
		sort(k+1,k+n+1,cmp);
		for(int i=1;i<=n;i++)
		{
			c2[i]=c[k[i]];
		}
		for(int i=1;i<=n;i++)
		{
			if(c[cnt]<c2[i])
			{
				ans+=c[cnt];
				cnt++;
			}
			else
			{
				ans+=c2[i]; 
			} 
		}
		cout<<ans<<endl;
	}
	return 0;
} 
//谢绝抄袭
```
#### 注意几点:
1.不开ll见祖宗


2.初始化


---

