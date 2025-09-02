# [POI 2007] TET-Tetris Attack

## 题目描述

一种名为 *Tetris Attack* 的猜谜游戏风靡 Byteotia。游戏本身非常复杂，因此我们只介绍它的简化规则：

玩家拥有一个有 $2n$ 个元素的栈，一个元素放置在另一个元素上，这样一个组合有 $n$ 个不同的符号标记。对于每个符号，栈中恰好有两个元素用一个符号标记。

玩家可以交换两个相邻元素，即互换他们的位置。交换后，如果有两个相邻的元素标有相同的符号，则将他们都从栈中删除。然后，位于其上方的所有元素都会掉落下来，并且可以造成再次删除。

玩家的目标是以最少的移动次数清空堆栈。请你编写一个程序，找出最少的移动次数及方案。

## 说明/提示

$1 \le n \le 50000$

## 样例 #1

### 输入

```
5
5
2
3
1
4
1
4
3
5
2```

### 输出

```
2
5
2```

# 题解

## 作者：fletmer (赞：24)

## 友情提醒，不要试图看楼上的题解的代码，否则你会弃题而走的，不是很明白为什么他能写这么多

#### 关键思想就是通过使用树状数组来维护数列，达到消除后效性的效果。具体看代码注释，这里说一下对方案的记录：
##### 1.第一次记录很简单，关键在于后面的几次，因为有一个问题就是中间被消掉了很多块，所以某个数字的序号可能会改变。所以定义了一个hsb去记录已消的元素个数。由于 | 已经被消的元素 | 一定是 | 当前计算的元素 | 前的元素，所以直接减去就好了。
##### 2.由于两个相同元素之间可能不止隔了一个元素，所以循环去填方案：
dis相同元素的距离，t为当前计算的元素，hsb为当前元素前已被消除的元素

---

```cpp
int t=i,dis=Query(i-1)-Query(v[s[i]]);
while(dis) stp[++cnt]=t-1-hsb,t--,dis--;
```

---

##### 3.算了多一句嘴，使用树状数组为啥会使后效被消除？
---

有几种情况

第一种： 1.....1 2.....2这样先消1和先消2一样

第二种：1212  同上，并且只用消一个

第三种： 1 2 ....2 1 显然先消2更优

---
其中第三种情况，每次交换为了缩短相同元素的距离，都会把无关的后调，树状数组是直接把相同的元素给消除了，对其它元素的影响就是：

1. 没影响

2. 相同元素距离缩短

自行理解吧，还是好懂的


```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define SIZE 50010
#define lowbit(x) x&(-x)
#define LL long long
using namespace std;

LL n,ans,cnt,hsb;
LL tr[2*SIZE],v[2*SIZE],s[2*SIZE],stp[1000005];

//树状数组不解释
inline void Add(int x,int y){
	//注意这里是2*n不是n
	for( ;x<=2*n;x+=lowbit(x)) tr[x]+=y;
}
inline LL Query(int x){
	LL sum=0;
	for( ;x;x-=lowbit(x)) sum+=tr[x];
	return sum;
}

int main(){
	cin>>n;
    
    //初始化
	for(int i=1;i<=2*n;i++) cin>>s[i],Add(i,1);
	for(int i=1;i<=2*n;i++){
    	//如果遇的元素为第一次遇到，记录其位置
		if(!v[s[i]]) v[s[i]]=i;
        //如果不是第一次遇到
		else{
        	//统计步数，中间有几个，就要交换几回
			ans+=Query(i)-Query(v[s[i]])-1;
			int t=i,dis=Query(i-1)-Query(v[s[i]]);
			while(dis) stp[++cnt]=t-1-hsb,t--,dis--;
            //消除影响
			Add(v[s[i]],-1); Add(i,-1); 
            hsb+=2; //一次合并消两个元素
		}
	}
    
    //输出方案不解释
	printf("%lld\n",ans);
	for(int i=1;i<=cnt;i++) printf("%lld\n",stp[i]);
	
	return 0;
}
```

---

## 作者：asuldb (赞：15)

[题目](https://www.luogu.org/problem/P3460)

考虑贪心，显然的策略就是开一个栈，一旦遇到一个之前出现的数就交换过去消掉；否则就直接加入栈；答案就是暴力移动的次数

感性理解一下这样一定上最优的，对于数$i$第一次出现的位置$beg_i$和第二次出现的位置$end_i$，我们没有必要把$beg_i$往前换或是将$end_i$往后换；尽管这样可能会把一些东西换进来使得数$i$被连锁消掉，但是我们直接将$beg_i$往后换或$end_i$往前换显然有等价的效果

还有距离并不需要用树状数组维护，既然能输出方案答案显然不会很大，直接暴力弹栈就好

代码~~并不需要写得很长~~

```cpp
#include<bits/stdc++.h>
#define re register
inline int read() {
	char c=getchar();int x=0;while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+c-48,c=getchar();return x;
}
const int maxn=1e5+5;
int a[maxn],vis[maxn],tax[maxn],ans,top,st[maxn],n,Ans[1000005],np;
int main() {
	n=read();for(re int i=1;i<=n+n;++i) a[i]=read();
	for(re int i=1;i<=n+n;i++) 
	if(vis[a[i]]) {
		np=0;
		while(st[top]!=a[i]) Ans[++ans]=top,tax[++np]=st[top--];
		--top;while(np) st[++top]=tax[np--];  
	}
	else st[++top]=a[i],vis[a[i]]=1;
	printf("%d\n",ans);for(re int i=1;i<=ans;i++) printf("%d\n",Ans[i]);
	return 0;
}
```


---

## 作者：xiaoshumiao (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/solution/P3460)

对于每个数，如果栈中已经有这个数，那么肯定先把它消掉。

怎么理解？考虑这组数据：
```
2
2
1
1
2
```
如果你先消 $2$ 的话，那么需要 $2$ 次。但如果先消 $1$ 的话，一次操作也不用。

所以我们用 $place_i$ 记录 $i$ 出现的位置，$place_i=0$ 表示 $i$ 不在栈中。

然后直接模拟即可，为了提升效率可以用树状数组。

代码如下：（省略了树状数组实现和输出的部分，请读者自行补充。）
```cpp
int cnt=0,tot=0;
scanf("%d",&n);
n*=2;
for(int i=1;i<=n;i++) {
  int x;
  scanf("%d",&x);
  if(place[x]==0) {//第一次出现
	 add(i,1);
	 place[x]=i;
  }
  else {
	 int dis=sum(i-1)-sum(place[x]);//计算距离
	 for(int j=1;j<=dis;j++)//记录答案
	   ans[++tot]=i-cnt-j;
	 add(place[x],-1);
	 cnt+=2;
  }
}
```

---

## 作者：Fislett (赞：4)

# 题意
有一个栈，其中包含 $2n$ 个元素，有 $n$ 个标记，每种元素都有一个标记，对于每一种标记，栈中都有 $2$ 个。你可以交换相邻两个元素的位置。如果两个相邻元素相同，则将他们删除，删除后，他们上面的元素就会掉下来。问将栈清空使用的最少操作次数以及方案。

# 解题思路
开一个树状数组，用来维护元素间的距离，如果前面有和目前元素标记相同的元素，就移动两个元素直接的距离减一次，过程中顺便记录移动的位置，如果前面没有，就把当前元素的位置记录下来，以便后续处理，最后的答案就是移动的次数，而方案已经在移动的过程中记录下来了。

自行理解一下吧，还是很好懂的。对于一个标记第一次出现的位置和第二次出现的位置，我们没有必要把第一个往前换或把第二个往后换，尽管这样可能引来一连串的消消乐，但我们直接把第一个往后换或把第二个往前换其实也有同样的效果。

# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n, tr[N], ans[N], cnt, vis[N], tot; //cnt用来记录目前已经删除的元素个数，vis数组用来记录前一个与目前元素相同标记的元素的变号 
int lowbit(int x) {return x & -x;} 
void add(int x, int y) //树状数组模板 
{
	while (x <= n)
	{
		tr[x] += y;
		x += lowbit(x);
	}
}
int query(int x)
{
	int res = 0;
	while (x)
	{
		res += tr[x];
		x -= lowbit(x);
	}
	return res;
}
int main()
{
	scanf("%d", &n);
	n <<= 1;
	for (int i = 1; i <= n; i ++)
	{
		int x;
		scanf("%d", &x);
		add(i, 1); //i位置上加了1个元素 
		if (!vis[x]) vis[x] = i;
		else
		{
			int dis = query(i - 1) - query(vis[x]); //dis是元素当前元素与前一个元素之间的距离 
			for (int j = 1; j <= dis; j ++) ans[++ tot] = i - cnt - j; //路上需要交换的点直接计入答案，注意要减去已经删除的点的个数
			add(vis[x], -1), add(i, -1); //消除这两个点 
			cnt += 2; //删除点数加2 
		}
	}
	printf("%d\n", tot);
	for (int i = 1; i <= tot; i ++) printf("%d ", ans[i]); //输出 
	return 0; //完结撒花！ 
}
```

祝大家新年快乐！

---

## 作者：封禁用户 (赞：4)

首先这个题显然是贪心，然后一个~~瞎~~贪心的思路就是每次直接找距离最近的一对来强行合并到一块，但是这个是有后效性的，因为它能影响到别的数的合并。所以我们不能光按照距离大小来优先取，应该在优先级里加上对别的数的影响。

这个影响是啥呢？就比如下面这个：

$1\space2\space4\space3\space3\space2\space1\space4$

如果我们把3合并，那么合并1、2、4的代价就会相应的减少2（距离都拉近了2），所以我们要计算出合并一个数会使多少对数的距离减小多少。比如这个：

\____A______B_______________

AB分别为这个数前后的两个位置，然后合并后B后面只有第二个位置的数会前移1，A前面只有第一个位置的数会前移1。我们不妨设$f[i]$为i前面有多少个第一个位置的数，$g[i]$为i前面有多少个第二个位置的数，那么我们就可以稍微容斥一下，B后面有第二个位置的数为$n-g[B]$，但是B后面可能有凑对的，所以就要减去B后面有第一个位置的数$n-f[B-1]$，那么就会有$f[B-1]-g[B]$个贡献，同理A也会有$f[A]-g[A-1]$个贡献，再减去合并这个需要花费的代价$B-A-1$，那么我们每次就取贡献最大的数进行合并，而且这个合并后对别的数的贡献的影响都是相对一样的，所以不需要动态维护，直接按照贡献排个序即可。

然后方案也就好算了，我们每次直接把B移到A（这个题比较玄学的一点就是A移到B就会WA2个点，我也无法解释……），然后这之中直接计算答案并且记录方案，合并后这两个数会删掉，我们可以用并查集来提高效率，就相当于链表一样，就是指向这个位置右面离它最近的位置（可以是自己），这样在暴力记录方案时就会直接跳过已经删过的点。而且为了记录这个地方现在变成了位置几，我们用树状数组来维护这个位置前面有多少个未删除的数就行了。

然后这个题比较坑的一点是，相同的数碰到一块后必须得消掉不然会判为方案错误，所以每次移动的时候得特判这两个位置前后是不是有相同的，然后移完之后直接把它们删除。

上代码：

```cpp
// luogu-judger-enable-o2
// luogu-judger-enable-o2
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
inline int get(){
    int n;char c;while((c=getchar())||1)if(c>='0'&&c<='9')break;
    n=c-'0';while((c=getchar())||1){
        if(c>='0'&&c<='9')n=n*10+c-'0';
        else return(n);
    }
}
int bit1[200001],bit2[200001];
int ints[200001],pos[100001][2];
int c[200002];int n;
int bcj[200001];
int bcj1[200001];
int find(int n){
    if(bcj[n]==n)return(n);return(find(bcj[n]));
}
int find1(int n){
    if(bcj1[n]==n)return(n);return(find1(bcj1[n]));
}
inline int setpt(int pt,int num){
    for(register int i=pt;i<=n;i+=(i&-i))c[i]+=num;
}
inline int getpt(int pt){
    int ans=0;for(register int i=pt;i>0;i-=(i&-i))ans+=c[i];return(ans);
}
typedef struct _n{
    int pt;int data;
    friend bool operator <(const _n &a,const _n &b){
        return(a.data>b.data);
    }
}node;node memchi[100001];
int anss[1000001];
void print(int num){
    if(num>=10)print(num/10);putchar(num%10+'0');
}
unsigned char bv[100001];
inline void delpt(int pt){
	if(pt==0||pt>n/2)return;
	bv[pt]=1;
	bcj[pos[pt][1]]=find(pos[pt][1]+1);
    bcj[pos[pt][0]]=find(pos[pt][0]+1);
    bcj1[pos[pt][0]]=find1(pos[pt][0]-1);
    bcj1[pos[pt][1]]=find1(pos[pt][1]-1);
    setpt(pos[pt][0],-1);setpt(pos[pt][1],-1);
}
int main(){
    n=get()*2;for(register int i=1;i<=n;i++){
        ints[i]=get();if(!pos[ints[i]][0]){
            pos[ints[i]][0]=i;
            bit1[i]=bit1[i-1]+1;bit2[i]=bit2[i-1];
        }else{
            pos[ints[i]][1]=i;
            bit1[i]=bit1[i-1];bit2[i]=bit2[i-1]+1;
        }setpt(i,1);
    }
    int nn=n>>1;for(register int i=1;i<=nn;i++){
        memchi[i].pt=i;int a=pos[i][0],b=pos[i][1];
        memchi[i].data=bit1[a]-bit2[a-1]+bit1[b-1]-bit2[b]-(b-a-1);
    }
    for(register int i=1;i<=n;i++)bcj[i]=i,bcj1[i]=i;
    int ans=0;
    sort(memchi+1,memchi+1+nn);int pub=1;
    for(register int i=1;i<=nn;i++){
    	if(bv[memchi[i].pt])continue;
        //ans+=(getpt(pos[memchi[i].pt][1]-1)-getpt(pos[memchi[i].pt][0]));
        int ptr=getpt(pos[memchi[i].pt][1])-1;
        int last=find(pos[memchi[i].pt][0]+1);
        for(register int j=find1(pos[memchi[i].pt][1]);j>last;j=find1(j-1)){
            //printf("swap(%d)\n",j);
            anss[pub]=ptr;ptr--;pub++;ans++;
        }
        delpt(memchi[i].pt);
        //printf("delpt(%d)\n",memchi[i].pt);
        if(ints[find(pos[memchi[i].pt][0])]==ints[find1(pos[memchi[i].pt][0])]){
        	//printf("Extra del %d\n",find(pos[memchi[i].pt][0]));
        	delpt(ints[find(pos[memchi[i].pt][0])]);
		}
		if(ints[find(pos[memchi[i].pt][1])]==ints[find1(pos[memchi[i].pt][1])]){
			//printf("Extra del %d\n",find(pos[memchi[i].pt][1]));
        	delpt(ints[find(pos[memchi[i].pt][1])]);
		}
        //printf("del(%d)\n",memchi[i].pt);
    }cout<<ans<<endl;
    //cout<<endl;
    for(register int i=1;i<pub;i++){
        print(anss[i]);putchar('\n');
    }
    return(0);
}
```

---

## 作者：Dream__Sky (赞：1)

恶评题。

考虑贪心，每次输入一个数后，只要这个数在前面出现过，那么就立马删去，这样是最优的，也是最好操作的。

感性理解就是说，我们从中间开始消，能使上下两边的数对距离同时减小。即使有一种方案能使序列连环消，也要从从连环消的**中间**一层一层消下去，和之前的道理还是一样的。

前面为什么说是最好操作的，实际上我们满足的贪心条件是从中间删更优，题中需要我记录下每次交换的位置，如果我们无序交换，要记录一个区间内哪些数被删了，哪些数还留着，非常难搞。

可以用树状数组维护当前点之前有几个数还留着，因为我们要算出两个数间的距离，记录下交换的位置。

代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,len,sum,vis[N],ans[N],tr[N];
int lowbit(int x){return x&-x;}
void change(int x,int k){for(;x<=n;x+=lowbit(x)) tr[x]+=k;}
int query(int x)
{
	int cnt=0;
	for(;x;x-=lowbit(x)) cnt+=tr[x];
	return cnt;
}
signed main()
{
	cin>>n;
	n<<=1;
	for(int i=1,now;i<=n;i++)
	{
		cin>>now;
		change(i,1);
		if(!vis[now]) vis[now]=i;
		else
		{
			int dis=query(i-1)-query(vis[now]);
			for(int j=1;j<=dis;j++) ans[++len]=i-sum-j;
			change(i,-1),change(vis[now],-1);
			sum+=2;
		}
	}
	cout<<len<<"\n";
	for(int i=1;i<=len;i++) cout<<ans[i]<<"\n";
	return 0;
}

```


---

## 作者：hjqhs (赞：1)

考虑贪心，有一个显然的策略是，遇到出现的数直接消除，否则加入栈。然后在暴力移动的过程中把方案记一下即可。所以就是动态维护两个相同的数中数的数量，并且有单点删除，所以使用树状数组维护。
```cpp
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
#define per(i, a, b) for(int i = (a); i >= (b); -- i)
typedef long long ll;
typedef unsigned long long ull;
const int N = 1000005;
const int INF = 0x3f3f3f3f;
int n, a[N], c[N], stp[N], scnt, pos[N], cnt;
int lowbit(int x) {return x & -x; }
void upd(int p, int v) {for(int i = p; i <= n; i += lowbit(i) ) {c[i] += v; } }
int qry(int p) {int v = 0; for(int i = p; i; i -= lowbit(i) ) v += c[i]; return v; }
void solve() {
	cin >> n; n <<= 1;
	rep(i, 1, n) cin >> a[i], upd(i, 1);
	rep(i, 1, n) {
		if(!pos[a[i]]) pos[a[i]] = i;
		else {
			int dis = qry(i - 1) - qry(pos[a[i]]), tmp = i;
			while(dis) stp[++ scnt] = tmp - 1 - cnt, -- tmp, -- dis;
			upd(i, -1), upd(pos[a[i]], -1);
			cnt += 2;
		}
	}
	cout << scnt << '\n'; rep(i, 1, scnt) cout << stp[i] << '\n';
	return;
}
signed main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int T = 1;
	// cin >> T;
	while(T --) solve();
	return 0;
}
```

---

## 作者：Others (赞：1)

这题很简单，就是动态维护两个数之间有多少个数并且支持删除操作，很多数据结构都可以，这里我打的是树状数组。

最开始我的思路是有个贪心的思想：把两个相同的数之间的长度存下来，排序，然后从小到大处理，理论上说这种做法复杂了但应该没有问题，然后被 SPJ 驳回了······

后来想了一下，发现不用从小到大搞，只需要遇到一个出现两次的数就删，这样是常规思路，然后就过了······这题的 SPJ 真的有 BUG。

```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;
int qr(){
	int x=0,f=0;
	char c=getchar();
	while(!isdigit(c)) f|=(c=='-'),c=getchar();
	while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?~(x-1):x;
} 
struct node{
	int len,l,r;
	bool operator<(const node &p)const{
		return len<p.len;
	}
}b[50005];
int n,a[100005],ans,bit[100005],pos[50005];
void add(int x){
	while(x<=2*n){
		++bit[x];
		x+=lowbit(x);
	}
	return ;
}
void del(int x){
	while(x<=2*n){
		--bit[x];
		x+=lowbit(x);
	}
	return ;
}
int get(int x){
	int tot=0;
	while(x){
		tot+=bit[x];
		x-=lowbit(x);
	}
	return tot;
}
queue<int> qu;
int main() {
	n=qr();
	for(int i=1;i<=2*n;i++){
		a[i]=qr();
	}
	for(int i=1;i<=2*n;i++){
		bit[i]=lowbit(i);
	}
	for(int i=1;i<=2*n;i++){
		if(!pos[a[i]]){
			pos[a[i]]=i;
		}else{
			ans+=get(i-1)-get(pos[a[i]]);
			for(int j=get(i-1),k=1,tmp=get(i-1)-get(pos[a[i]]);k<=tmp;k++,j--) qu.push(j);
			del(i),del(pos[a[i]]);
		}
	}
	cout << ans << endl;
	while(!qu.empty()){
		cout << qu.front() << endl;
		qu.pop();
	}
	return 0;
}
```

---

## 作者：2021zjhs005 (赞：0)

~~本蒟蒻第一篇紫题题解。~~


solution
------------
考虑贪心，如果两个数相邻且相等，那么一定会先消除它们。

消除了它们，别的不能消除的数之间的距离会减少，因此得证。

用 $visit_i = 0$ 表示 $i$ 没有出现过；反之，$visit_i = x$ 表示 $i$ 出现在第 $x$ 个位置。

用一个树状数组维护元素之间的距离，若发现 $visit_{num} \ne 0$（$num$ 为读入的数），就计算它与它前面出现的 $num$ 元素之间的距离，即 $query(i-1) - query(num)$。

距离不用包括两个 $num$，因为只要相邻就可以消除，不是碰到。

然后记录答案，消除这 $2$ 个元素，并且增加消除数量即可。


code
------------
```cpp
#include <iostream>
using namespace std;
#define int long long
#define rep(i,x,y) for(int i=x;i<=y;i++)
const int N=1e6+10;

inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

int n,num,cnt,tot,dis,p[N],tree[N],visit[N];

//树状数组模板，没学过建议去【模板】树状数组1 和 2 看看。
inline int lowbit(int x){
    return x&-x;
}
inline int query(int k){
	int sum=0;
    for(;k;k-=lowbit(k)) sum+=tree[k];
	return sum;
}
inline void update(int k,int x){
    for(;k<=n;k+=lowbit(k)) tree[k]+=x;
}

signed main() {
    n=read();
    n<<=1;
    rep(i,1,n){
        num=read();
        update(i,1);
        if(!visit[num])
            visit[num]=i;
        else{
            dis=query(i-1)-query(visit[num]);//计算距离。
            rep(j,1,dis) p[++cnt]=i-tot-j;//加入答案。
            update(i,-1);update(visit[num],-1);//消除这 2 个元素。
            tot+=2;//消除数量加 2。
        }
    }
    printf("%lld\n",cnt);
    rep(i,1,cnt) printf("%lld\n",p[i]);
    return 0;
}
```

---

## 作者：_Revenge_ (赞：0)

分析题目这是一个消方块的游戏，并且会有连锁反应。       
但是我们发现每种元素的方块实际上**只有一对**。       
我们应以此为出发点，如果我们交换方块并删除它们，只会改变其余各队的距离对答案进行贡献。            
而贡献则是越大越好，也就是说我们先消除内部的方块会最大化减小距离，进而产生一系列连锁反应。      
所以一种较为简单的消除内部方块的方法就是**记录每种元素的开始点若遇到开始点已有，即不为空**。       
那么立即交换并删除它们，此时记录贡献，可以用树状数组进行维护单点修改，区间查询贡献，记录交换答案是**距离减去贡献**。     
对于构造输出，无需过多解释，详情见代码具体部分。

格式化代码，感谢食用。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N = 1e5 + 50;
const int M = 1e5 + 50;
const int Mod = 1e9 + 7;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}

int n;

int a[N];

int tree[N];

int lowbit(int x) { return x & (-x); }

void update(int x, int k)
{
    for (int i = x; i <= 2 * n; i += lowbit(i))
    {
        tree[i] += k;
    }
}

int query(int x)
{
    int res = 0;
    for (int i = x; i > 0; i -= lowbit(i))
    {
        res += tree[i];
    }
    return res;
}

int b[N];

queue<int>q;

int main()
{
    n = read();
    for (int i = 1; i <= 2 * n; ++i)
    {
        a[i] = read();
    }
    int ans = 0;
    for (int i = 1; i <= 2 * n; ++i)
    {
        if (!b[a[i]])
            b[a[i]] = i;
        else
        {
        	int k=i - b[a[i]] - 1 + query(i) - query(b[a[i]] - 1);
            ans+=k;
            int l=b[a[i]]+query(b[a[i]]);
            for(int i=l;i<=l+k-1;++i) q.push(i);
            update(i, -1);
            update(b[a[i]], -1);
        }
    }
    printf("%d\n", ans);
    while(!q.empty()){
    	printf("%d\n",q.front());
    	q.pop();
    }
    return 0;
}
```

---

