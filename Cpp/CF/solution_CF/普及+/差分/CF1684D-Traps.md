# Traps

## 题目描述

There are $ n $ traps numbered from $ 1 $ to $ n $ . You will go through them one by one in order. The $ i $ -th trap deals $ a_i $ base damage to you.

Instead of going through a trap, you can jump it over. You can jump over no more than $ k $ traps. If you jump over a trap, it does not deal any damage to you. But there is an additional rule: if you jump over a trap, all next traps damages increase by $ 1 $ (this is a bonus damage).

Note that if you jump over a trap, you don't get any damage (neither base damage nor bonus damage). Also, the bonus damage stacks so, for example, if you go through a trap $ i $ with base damage $ a_i $ , and you have already jumped over $ 3 $ traps, you get $ (a_i + 3) $ damage.

You have to find the minimal damage that it is possible to get if you are allowed to jump over no more than $ k $ traps.

## 说明/提示

In the first test case it is allowed to jump over all traps and take $ 0 $ damage.

In the second test case there are $ 5 $ ways to jump over some traps:

1. Do not jump over any trap.Total damage: $ 5 + 10 + 11 + 5 = 31 $ .
2. Jump over the $ 1 $ -st trap.Total damage: $ \underline{0} + (10 + 1) + (11 + 1) + (5 + 1) = 29 $ .
3. Jump over the $ 2 $ -nd trap.Total damage: $ 5 + \underline{0} + (11 + 1) + (5 + 1) = 23 $ .
4. Jump over the $ 3 $ -rd trap.Total damage: $ 5 + 10 + \underline{0} + (5 + 1) = 21 $ .
5. Jump over the $ 4 $ -th trap.Total damage: $ 5 + 10 + 11 + \underline{0} = 26 $ .

To get minimal damage it is needed to jump over the $ 3 $ -rd trap, so the answer is $ 21 $ .

In the third test case it is optimal to jump over the traps $ 1 $ , $ 3 $ , $ 4 $ , $ 5 $ , $ 7 $ :

Total damage: $ 0 + (2 + 1) + 0 + 0 + 0 + (2 + 4) + 0 = 9 $ .

## 样例 #1

### 输入

```
5
4 4
8 7 1 4
4 1
5 10 11 5
7 5
8 2 5 15 11 2 8
6 3
1 2 3 4 5 6
1 1
7```

### 输出

```
0
21
9
6
0```

# 题解

## 作者：Eric998 (赞：17)

## 1.对本题的看法
这是一道难度虚高的贪心题，实际上只有1400左右

## 2.题意
你的面前有 $n$ 个陷阱，第 $i(i \leq n)$ 会对你造成 $a_i$ 点伤害。你可以选择跳过 $k$ 个陷阱来避免伤害，但代价是此后的每一个陷阱的伤害都加 $1$。

## 3.分析

跳过第 $i$ 个陷阱会减免 $a_i$ 的伤害，但会让后面的 $n-i-1$ 个陷阱
都增加 $1$ 的伤害(注意**此处 $i$ 从 $0$ 开始**)，因此跳过第 $i$ 个陷阱实际上减免的伤害为 $a_i-(n-i-1)=a_i-n+i+1$。将每个陷阱的实际减免伤害排序，选取最大的 $k$ 个，将 $a$ 数组的和减去这 $k$ 个数的和即可。

于是，我们抓了一只~~鲜活的~~样例，把它塞给程序，**结果 $\color{red}WA$ 了！**

emm,我们的程序给出的数好像都比标准答案大，差好像一定是 $\frac {k(k-1)}{2}$。

于是就可以证明了。

## 4.证明

假设我们选的 $k$ 个陷阱为第 $d_1,d_2,d_3,……d_k$ 个。

第 $m$ 个陷阱增加的 $1$ 伤害对 $d_{m+1},d_{m+2},d_{m+3}……d_k$ 这 $k-m$ 个陷阱不起作用。

因此，多算的伤害为$\sum_{m=1}^k k-m = \frac {k(k-1)}{2}$。

Q.E.D

## 5.code

代码已经呼之欲出了！
```cpp

#include<iostream>
#include<vector>
#include<map>
#include<math.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<time.h>
using namespace std;
#define inf 0x3f3f3f3f
#define minf 0x3f
#define inp(x) cin>>x
#define otp(x) cout<<x
#define otp_nl(x) cout<<x<<"\n"
#define otp_sp(x) cout<<x<<" "
#define int long long
#define veci vector<int>
#define str string
#define pb(x) push_back(x)
#define fr(k,len) for(k=0;k<len;k++)
#define nfr(k,len) for(int k=0;k<len;k++)
#define ret return
#define db long double
namespace my_stl{

}

void solve(){
	int n,k;
	cin>>n>>k;
	vector<int> a(n);
	int sum=0;
	for(int i=0;i<n;i++){
		cin>>a[i];sum+=a[i];
		a[i]-=n;
		a[i]+=i;
		a[i]++;
	}
	sort(a.rbegin(),a.rend());
	for(int i=0;i<k;i++)sum-=a[i];
	cout<<sum-(k-1)*k/2<<"\n";
	ret;
}
signed main(){
    int t;
    cin>>t;
	nfr(i,t){
		solve();
	}
	ret 0;
}


```

---

## 作者：happy_dengziyue (赞：10)

### 1 视频题解

$7$ 分 $27$ 秒开始。

![](bilibili:BV15U4y127QD)

### 2 思路

首先，我们可以确定，用完这 $k$ 次机会是最优的。如果机会没被用完，再跳过最右一个没被跳过的陷阱总是更优的。

然后我们考虑跳过陷阱能够带来多少收益。

设第 $i$ 个被跳过的陷阱的坐标为 $x[i]$。可得：

+ 基础伤害减少为 $\sum_{i=1}^ka[x[i]]$；

+ 额外伤害增加（暂不考虑跳过） $\sum_{i=1}^k(n-x[i])$；

+ 被跳过的额外伤害为 $\sum_{i=0}^{k-1}i$。

那么，总的收益就是：

$$\sum_{i=1}^ka[x[i]]-\sum_{i=1}^k(n-x[i])+\sum_{i=0}^{k-1}i$$

化简得：

$$\sum_{i=1}^k(a[x[i]]+x[i])-n\times k+\dfrac{k\times(k-1)}{2}$$

那么，我们对于 $i(1\le i\le n)$，按照 $a[i]+i$ 的大小降序排序，选择前 $k$ 个，然后按照题意模拟计算即可。

### 3 代码与记录

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define max_n 200000
int t;
int n;
int k;
long long a[max_n+2];
long long c[max_n+2];
int x[max_n+2];
bool ch[max_n+2];
long long ans;
bool cmp(long long a,long long b){
	return c[a]>c[b];
}
int main(){
	#ifndef ONLINE_JUDGE
	freopen("CF1684D_1.in","r",stdin);
	freopen("CF1684D_1.out","w",stdout);
	#endif
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;++i){
			scanf("%lld",a+i);
			c[i]=a[i]-(n-i);
			x[i]=i;
			ch[i]=false;
		}
		sort(x+1,x+n+1,cmp);
		for(int i=1;i<=k;++i)ch[x[i]]=true;
		ans=0;
		for(int i=1,cnt=0;i<=n;++i){
			if(ch[i])++cnt;
			else ans+=a[i]+cnt;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

[记录传送门](https://www.luogu.com.cn/record/76116175)

By **dengziyue**

---

## 作者：suyunqiaoKID (赞：6)

### 翻译

这里有 $ n $ 个陷阱，你需要按照给出的顺序穿过这些陷阱，每个陷阱将会对你造成 $ a_i $ 的伤害

你有至少k次机会跳过这些陷阱，可以避免你所跳过的陷阱给你造成的伤害，不过接下来的所有陷阱都会给你多造成 $ 1 $ 点伤害。

跳过陷阱所造成的额外伤害会叠加，如果你当前已经跳过了 $ 3 $ 个陷阱，接下来的陷阱给你造成的伤害将会是 $ a_i +3 $ 。

现在需要你求出受到的最小伤害。

### 思路

尽可能的通过k次跳过陷阱的机会减小受到的伤害，对于每个陷阱 $ x $，跳过它可以直接减小的伤害为 $ a_x $，不过以后的每个没有被跳过的陷阱（共 $ n-x $ 个）所造成的伤害都要增加 $ 1 $ 点，所以跳过陷阱 $ x $ 能减少的伤害为 $ a_x -n+x $ 。

### 注意

每个 $ a_i $ 最高可达 $ 10^9 $ ，所以需要开 `long long` 。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define int long long//要开long long
using namespace std;
const unsigned int N=2e5+15;
int damage[N],n,m,ans,jumped;
bool jump[N];
struct Trap{
    int val;
    int id;
}a[N];
inline void read(int &x){
    x=0;
    int y=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-')
        y=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();
    }
    x*=y;
}//快读
bool cmp(struct Trap x,struct Trap y){
    return x.val>y.val;
}//结构体排序
void init(){
    ans=0;
    jumped=0;
    for(register int i=1;i<=n;i++)
    jump[i]=false;
}
void solve(){
    read(n);
    read(m);
    init();//初始化
    for(register int i=1;i<=n;i++){
        read(damage[i]);
        a[i].val=damage[i]-(n-i);//跳过i所能减少的伤害
        a[i].id=i;//结构体排序后方便标记
    }
    sort(a+1,a+n+1,cmp);//排序求出减小的伤害前m大的陷阱
    for(register int i=1;i<=m;i++)
    jump[a[i].id]=true;//标记 后面模拟的的时候跳过
    for(register int i=1;i<=n;i++){
        if(jump[i]){
            jumped++;//jumped表示前面跳过陷阱的个数
            continue;
        }
        ans+=damage[i]+jumped;//当前陷阱的伤害加上跳过陷阱所带来的额外伤害
    }
    printf("%lld\n",ans);
}
signed main(){
    int T;
    read(T);
    while(T--)
    solve();
    return 0;
}
```


---

## 作者：alex_liu (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1684D)

## 思路：

由于要求受到陷阱的伤害要最小，所以我们可以把题意转化为跳过伤害值最大的 $k$ 个陷阱。

通过 [vector](https://blog.csdn.net/Sky_River_Z/article/details/113810638) 数组和 [pair](https://blog.csdn.net/sevenjoin/article/details/81937695?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1-81937695-blog-100588654.pc_relevant_default&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7Edefault-1-81937695-blog-100588654.pc_relevant_default&utm_relevant_index=2) 存储陷阱所带来的最大的伤害以及它的位置，排序过后找到跳过 $k$ 个陷阱的最优解（即跳过伤害值最大的 $k$ 个陷阱），统计总伤害后的结果即为受到伤害的最小值。

详细解析看代码注释。

## AC CODE：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
inline int read(){//快读优化 
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
	return x*f;
}
inline void solve(){
    int n,k,a[200005],sum=0,cnt=0;
    n=read(),k=read();//读入 
    vector<pair<int,int> >v;//用 vector 来存储 
    for(int i=0;i<n;i++)a[i]=read();//读入 
    for(int i=0;i<n;i++)v.push_back({a[i]+i,i});//插入 v （ first：当前陷阱可能造成伤害的最大值；second：当前陷阱是第几个（由于不能改变穿过陷阱的顺序） 
    sort(v.begin(),v.end());//从小到大排序（默认用第一关键字排序） 
    while(k--){a[v.back().second]=0;v.pop_back();}//跳过造成伤害最多的 k 个陷阱，赋值为 0 
    for(int i=0;i<n;i++){
        if(a[i])sum+=a[i],sum+=cnt;//不跳过当前陷阱 
        else cnt++;//跳过当前陷阱 
    }
    cout<<sum<<endl;//输出答案 
}
signed main(){
    t=read();//读入 
    while(t--)solve();//调用函数 
    return 0;
}
```


---

## 作者：GI录像机 (赞：3)

很好玩的一道贪心题。

## 思路简述：

首先我们需要知道跳陷阱的次数一定是用完才有最优解。

为什么呢？因为如果我们选择最后 $k$ 个陷阱跳，一定不会影响在其它陷阱中收到的伤害，伤害值会减小。

接着我们来计算每个点产生的贡献。如果选择跳第 $i$ 个陷阱，在此之前已经跳了 $s-1$ 次，则他会使答案增加 $-a_i+n-i-k+s$。其中 $-a_i$ 减少了当前点原来会受到的伤害，$n-i$ 是把后面的陷阱伤害增加造成的伤害，$-k+s$ 是在后面摆放陷阱后减少的由当前陷阱摆放而增加的伤害。

我们可以把 $-k+s$ 这一项提出来，因为我们要把所有跳陷阱的次数用完，所以 $-k+s$ 这一项产生的贡献为定值 $\frac{k(k-1)}{2}$。

现在每个点产生的贡献就为 $-a_i+n-i$，我们就可以用线段树维护区间最小值，让答案加上 $k$ 个最小值（可以用堆，但我喜欢用线段树）。

## 代码实现：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int read() {
	int f = 1, x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return f * x;
}
void write(int x) {
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	if (x > 9)write(x / 10);
	putchar(x % 10 + '0');
}
const int N = 2e5 + 10;
int t = read(), n, v[N], k;
struct Node {
	int maxn;
} a[N << 2];
void pushup(int pos) {
	a[pos].maxn = min(a[pos << 1].maxn, a[pos << 1 | 1].maxn);
}
void build(int pos, int l, int r) {
	if (l == r) {
		a[pos].maxn = v[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(pos << 1, l, mid);
	build(pos << 1 | 1, mid + 1, r);
	pushup(pos);
}
int del_query(int pos, int l, int r) {
	if (l == r) {
		int tmp = a[pos].maxn;
		a[pos].maxn = 0x3f3f3f3f;
		return tmp;
	}
	int mid = (l + r) >> 1, ans;
	if (a[pos << 1].maxn < a[pos << 1 | 1].maxn)ans = del_query(pos << 1, l, mid);
	else ans = del_query(pos << 1 | 1, mid + 1, r);
	pushup(pos);
	return ans;
}
signed main() {
	while (t--) {
		n = read();
		k = read();
		int ans = 114514-114514+1919810-1919810;
		ans -= k * (k - 1) / 2;
		for (int i = 1; i <= n; i++) {
			v[i] = read();
			ans += v[i];
			v[i] = -v[i] + n - i;
		}
		build(1, 1, n);
		while (k--)ans += del_query(1, 1, n);
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：qscisQJing (赞：2)

~~一看就是贪心~~


------------

# 解题思路
首先可以知道 $ k $ 次机会是一定要用完的，否则在最右端连续跳过去一定最优。

若在 $ x $ 的地方选择跳跃，总共跳过 $ l $ 次：

后面的伤害：$\sum\limits_{i=x+1}^n (a_i+l)$

若没有选择跳跃： $ \sum\limits_{i=x}^n(a_i+l-1)$

两者相差 $ n-x-a_i-l+1$

$n$ 和 $+1$ 肯定是不变的，$l$ 会取遍 $1$ 到 $k$ ,也是不变的。

也就是说我们只要按 $x+a_i$ 来排序就可以了，取最大的 $k$ 个。





------------
# AC代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int n,k,past[MAXN];
struct node
{
	int pos,val;
}a[MAXN];
bool cmp(node x,node y)
{
	return x.pos+x.val>y.pos+y.val;
}
bool ret(node x,node y)
{
	return x.pos<y.pos;
}
void solve()
{
	for(register int i=1;i<MAXN;++i)past[i]=false;
	long long ans=0,sum=0;
	scanf("%d%d",&n,&k);
	for(register int i=1;i<=n;++i)cin>>a[i].val,a[i].pos=i;
	sort(a+1,a+1+n,cmp);
	for(register int i=1;i<=k;++i)past[a[i].pos]=true;
	sort(a+1,a+1+n,ret);ans=0,sum=0;
	for(register int i=1;i<=n;++i)
	{
		if(past[i]){++sum;continue;}
		ans+=a[i].val+sum;
	}
	printf("%lld\n",ans);
}
int main()
{
	int t;
	cin>>t;
	while(t--)
		solve();
	return 0;
}
```


---

