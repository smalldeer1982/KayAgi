# Challenges in school №41

## 题目描述

There are $ n $ children, who study at the school №41. It is well-known that they are good mathematicians. Once at a break, they arranged a challenge for themselves. All children arranged in a row and turned heads either to the left or to the right.

Children can do the following: in one second several pairs of neighboring children who are looking at each other can simultaneously turn the head in the opposite direction. For instance, the one who was looking at the right neighbor turns left and vice versa for the second child. Moreover, every second at least one pair of neighboring children performs such action. They are going to finish when there is no pair of neighboring children who are looking at each other.

You are given the number $ n $ , the initial arrangement of children and the number $ k $ . You have to find a way for the children to act if they want to finish the process in exactly $ k $ seconds. More formally, for each of the $ k $ moves, you need to output the numbers of the children who turn left during this move.

For instance, for the configuration shown below and $ k = 2 $ children can do the following steps:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1333D/1c82f87a8bbc7db5946c92d119545cc62c807d4d.png) At the beginning, two pairs make move: $ (1, 2) $ and $ (3, 4) $ . After that, we receive the following configuration:  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1333D/e6b2846f00e19372028c7c25dec89f94953d95b5.png) At the second move pair $ (2, 3) $ makes the move. The final configuration is reached. Good job.  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1333D/52b4fbc28796b74c289106fad9a7da3188063226.png)It is guaranteed that if the solution exists, it takes not more than $ n^2 $ "headturns".

## 说明/提示

The first sample contains a pair of children who look at each other. After one move, they can finish the process.

In the second sample, children can't make any move. As a result, they can't end in $ k>0 $ moves.

The third configuration is described in the statement.

## 样例 #1

### 输入

```
2 1
RL```

### 输出

```
1 1```

## 样例 #2

### 输入

```
2 1
LR```

### 输出

```
-1```

## 样例 #3

### 输入

```
4 2
RLRL```

### 输出

```
2 1 3 
1 2```

# 题解

## 作者：奇米 (赞：7)

## 题解- CF1333D Challenges in school №41

[$$\huge\color{blue}\boxed{\color{Violet}\mathfrak{There\ is \ my \ blog}}$$](https://www.luogu.com.cn/blog/wyy2020/)

### **题目意思**

* [D](https://www.luogu.com.cn/problem/CF1333D)
* 给你一个含$R,L$序列就是称一次操作可以将若干$RL$对翻转，问能否在$k$次使得序列无法翻转。
* $n\leq 3e3,k\leq 3e6$

### $\mathrm{Sol}$

* 一道比较$** $的构造题目

* 我们首先考虑如何使得答案最优，我们是不是只要每次能翻就翻。我们记录这个最少翻转次数为$mi$

* 同理，我们再考虑如何使得答案最差，我们是不是只要每次能翻只翻转一个。我们记录这个最大翻转次数为$mx$

* 对于无解的情况即：$k<mi$或者$k>mx$，这个很好理解

* 那么这样就简单了，我们只要去凑数字。即如果$mi<k$，那么我们就选择最差的方式去反转直到$mi=k$。对于剩下的我们选择用最优秀的方法翻转即可。这样就可以构造一个合法的答案了。

### $\mathrm{Code}$

```cpp
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

inline int read()
{
	int sum=0,ff=1; char ch=getchar();
	while(!isdigit(ch))
	{
		if(ch=='-') ff=-1;
		ch=getchar();
	}
	while(isdigit(ch))
		sum=sum*10+(ch^48),ch=getchar();
	return sum*ff;
}

const int N=3005;

int n,m,ans,a[N],b[N],tmp[N],mi,mx;
char ch[N];

int main()
{
	n=read();
	m=read();
	scanf("%s",ch+1);
	for ( int i=1;i<=n;i++ ) 
	{
		a[i]=(ch[i]=='R')?1:-1;
		b[i]=a[i];
	}
	while(1)
	{
		int flg=0;
		for ( int i=1;i<n;i++ ) 
			if(a[i]==1&&a[i+1]==-1) 
			{
				flg=1;
				swap(a[i],a[i+1]);
                i++;
				mx++;
			}
		if(!flg) break;
		mi++;
	}
	if(m<mi||m>mx) return printf("-1\n"),0;
	for ( int i=1;i<=n;i++ ) a[i]=b[i];
	while(1)
	{
		int i=1;
		for(;i<n;++i)
		{
			if(m==mi) break;
			if(a[i]==1&&a[i+1]==-1) 
			{
				swap(a[i],a[i+1]);
				m--;
				printf("%d %d",1,i);
				puts("");
				i++;
			}
		}
		int gs=0;
		for(;i<n;++i)
		{
			if(a[i]==1&&a[i+1]==-1)
			{
				swap(a[i],a[i+1]);
				tmp[++gs]=i;
				i++; 
			}
		}
		if(gs)
		{
			printf("%d ",gs);
			for ( int j=1;j<=gs;j++ ) printf("%d ",tmp[j]);
			m--;
			puts("");
		}
		mi--;
		if(!m) break;
	}
	return 0;
}
		
```


---

## 作者：AutumnKite (赞：4)

[宣传 blog](https://autumnkite.github.io/)（Github Pages 上不去可以用 [Gitee 上的镜像](https://autumnkite.gitee.io/)）

### 题解

考场上的我不知道在干什么...

首先我们把 $\mathtt{R}$ 看成 $1$，$\mathtt{L}$ 看成 $0$，那么交换轮数的上界为逆序对数。如果 $k$ 大于逆序对数，那一定无解。

然后我们考虑求出交换轮数的下界并求出一组解。

由于总交换次数固定，为逆序对数，那么我们只要每一轮贪心地将可以交换的相邻的数对交换即可。

考场上并没有过多的时间证明交换轮数下界的级别，所以代码中我直接使用了 $\mathtt{set}$ 来快速找到所有需要交换的数对。

在求出达到下界的这一组解后，若 $k$ 大于这个下界，我们只需要将同一轮中的若干次交换拆成若干轮，直到轮数搞好为 $k$ 即可。

由于我使用了 $\mathtt{set}$，所以复杂度是 $O(n^2\log n)$ 的，可以通过此题。

### 代码

```cpp
const int N = 3005;

int n, k, a[N];
char s[N];
std::set<int> S;
std::vector<std::pair<int, int>> move;

void solve() {
	read(n), read(k), readStr(s + 1);
	for (int i = 1; i <= n; ++i) {
		a[i] = (s[i] == 'R');
		if (i == 1 || a[i] != a[i - 1]) S.insert(i);
	}
	S.insert(n + 1);
	int cnt = 0;
	while (1) {
		std::vector<int> p;
		int x = 1;
		while (x <= n) {
			if (a[x] || x == 1) {
				x = *S.upper_bound(x);
				continue;
			}
			p.push_back(x - 1);
			std::swap(a[x], a[x - 1]);
			int tmp = *S.upper_bound(x);
			if (x > 2 && !a[x - 2]) {
				S.erase(x - 1);
			} else {
				S.insert(x - 1);
			}
			if (!a[x + 1]) {
				S.insert(x + 1);
			}
			x = tmp;
		}
		if (p.empty()) {
			break;
		}
		++cnt;
		for (int v : p) {
			move.push_back({v, cnt});
		}
	}
	if (k < cnt || k > (int)move.size()) {
		print(-1);
		return;
	}
	for (int i = (int)move.size() - 1; i >= 1; --i) {
		move[i].second -= move[i - 1].second;
	}
	for (int i = 0; i < (int)move.size(); ++i) {
		if (move[i].second) {
			continue;
		}
		if (cnt == k) {
			break;
		}
		move[i].second = 1;
		++cnt;
	}
	std::vector<std::vector<int>> ans(k);
	int now = 0;
	for (auto p : move) {
		now += p.second;
		// debug("%d %d\n", p.first, p.second);
		ans[now - 1].push_back(p.first);
	}
	for (auto p : ans) {
		print((int)p.size(), ' ');
		for (int v : p) {
			print(v, ' ');
		}
		putchar('\n');
	}
}
```

---

## 作者：gyh20 (赞：3)

首先，我们可以发现，最终的结果一定是一串 L 加上一串 R。（知道这个这道题就简单了）

反证法，如果一个 L 左边不是 L,那么可以交换。

所以，我们将每一个 L 的位置和之前的 L 的个数存为一个结构体。

首先，最大的答案一定是所有 L 移动的次数之和。最小答案可以一次搜索 $+$ 贪心得出，每次对于每一个 L ，如果和上一个不相邻就 $-1$，这样可以保证每一次操作的影响最大。然后如果次数大于 $>k$ 可以直接判无解。

这样是 $O(n\times minans)$ 的，跑得过。

之后根据 $k$ 的大小和最大答案的大小依次摆放答案即可，方法同之前找最小答案。

代码有点丑。。。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define int long long
inline int read(){
	re int t=0,f=0;re char v=getchar();
	while(v<'0')f|=(v=='-'),v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return f?-t:t;
}
int n,a[3002],ans[3002],k,sum,ans1,ans2,p[3002],tot;
char s[3002];
struct node{
	int x,y;
}q[3002];
signed main(){
	n=read();k=read();
	scanf("%s",s+1);sum=1;
	for(re int i=1;i<=n;++i){
			
		if(s[i]=='L'){
			ans[i]=sum;
			ans1=max(ans1,i-ans[i]);ans2+=i-ans[i];
			++sum;//printf("%lld %lld\n",i,ans[i]);
			if(i!=ans[i])q[++tot]=(node){ans[i],i};
		}
	}//return 0;
	if(ans2<k){
		puts("-1");
		return 0;
	}ans1=0;
	while(tot){
		re int num=0,lst=0,sss=0;
		for(re int i=1;i<=tot;++i){
			node z=q[i];
			if(z.y==lst+1){
				lst=z.y;
				q[++sss]=z;
				continue;
			}lst=z.y;
			--z.y;
			if(z.x!=z.y)q[++sss]=z;
		}++ans1;tot=sss;
	if(ans1>k){
		puts("-1");
		return 0;
	}
	}
	sum=1;ans2=0;
	for(re int i=1;i<=n;++i){
		if(s[i]=='L'){
			ans[i]=sum;
			ans2+=i-ans[i];
			++sum;//printf("%lld %lld\n",i,ans[i]);
			if(i!=ans[i])q[++tot]=(node){ans[i],i};
		}
	}
	while(tot){
		re int sss=0,y=min(ans2-k+1,tot),num=0,lst=0;
		if(y==1){
			for(re int i=1;i<=tot;++i){
				node z=q[i];
				while(z.y!=z.x){
					--z.y;
					printf("%d %d\n",1,z.y);
				}
			}
			return 0;
		}
		for(re int i=1;i<=tot;++i){
			node z=q[i];
			if(z.y==lst+1||num>=y){lst=z.y;
				q[++sss]=z;
				continue;
			}lst=z.y;
			p[++num]=(--z.y);--ans2;if(z.x!=z.y)q[++sss]=z;
		}--k;tot=sss;
		printf("%lld ",num);
		for(re int i=1;i<=num;++i)printf("%lld ",p[i]);
		putchar('\n');
	}
}
```


---

## 作者：ix35 (赞：2)

题目说的这个过程很显然就是冒泡排序。

既然 $n\leq 3000$，那么就暴力模拟冒泡排序，看看至少要多少轮（设为 $mn$，注意这个轮是指同一轮中不能交换同一个元素多次），以及逆序对数（设为 $mx$）。

那么如果 $k<mn$ 或 $k>mx$，无解。

否则我们记录每一轮冒泡排序消除了哪些逆序对，然后根据 $k$ 和 $mn$ 的差来分配一下每次做多少次冒泡即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN=3010;
int n,k,mx,mn,a[MAXN],b[MAXN],sum[MAXN];
char c[MAXN];
vector <int> v[MAXN];
int main () {
	scanf("%d%d%s",&n,&k,c+1);
	for (int i=1;i<=n;i++) {
		a[i]=b[i]=(c[i]=='R'?1:0);
	}
	for (int i=1;i<=n;i++) {
		int cnt=0;
		for (int j=1;j<n;j++) {
			if (b[j]>b[j+1]) {
				cnt++;
				v[i].push_back(j);
			}
		}
		for (int j=0;j<cnt;j++) {
			swap(b[v[i][j]],b[v[i][j]+1]);
		}
		if (!cnt) {mn=i-1;break;}
		mx+=cnt;
		sum[i]=sum[i-1]+cnt;
	}
	if (k<mn||k>mx) {printf("-1\n");return 0;}
	if (k==mn) {
		for (int i=1;i<=mn;i++) {
			printf("%d ",v[i].size());
			int len=v[i].size();
			for (int j=0;j<len;j++) {printf("%d ",v[i][j]);}
			printf("\n");
		}
		return 0;
	}
	int cur=0;
	while (cur<mn&&mx-sum[cur+1]+cur+1>=k) {cur++;}
	for (int i=1;i<=cur;i++) {
		int len=v[i].size();
		printf("%d ",len);
		for (int j=0;j<len;j++) {printf("%d ",v[i][j]);}
		printf("\n");
	}
	if (mx-sum[cur]+cur-k+1) {
		printf("%d ",mx-sum[cur]+cur-k+1);
		for (int i=0;i<mx-sum[cur]+cur-k+1;i++) {
			printf("%d ",v[cur+1][i]);
		}
		printf("\n");
	}
	int len=v[cur+1].size();
	for (int i=mx-sum[cur]+cur-k+1;i<len;i++) {
		printf("%d %d\n",1,v[cur+1][i]);
	}
	for (int i=cur+2;i<=mn;i++) {
		int len=v[i].size();
		for (int j=0;j<len;j++) {printf("%d %d\n",1,v[i][j]);}
	}
	return 0;
}
```


---

## 作者：Day_Tao (赞：1)

首先不难发现，最终这个字符串会变成形如 $\texttt{LLL}\cdots \texttt{RRR}$ 的样子。而对于每个字符串都存在一个操作的上限 $mx$ 和下限 $mn$。上限不难发现就是对于每个 $\texttt{R}$ 右边的 $\texttt{L}$ 的数量，即操作的总次数。考虑下限及对于下限的证明。

不难发现在 $\texttt{L}$ 和 $\texttt{R}$ 的数量相同时，形如 $\texttt{RRR}\cdots \texttt{LLL}$ 一定是最劣的，这样的字符串操作若干次之后将会变成给定的字符串。考虑对于这样最劣的字符串的操作下限。发现在最优移动下，倒数第 $i$ 个 $R$ 将在第 $i$ 轮开始移动，并且能够一直移动，一共会移动 $cntL$ 次。所以对于这种最劣情况移动的下限就是 $n$。

知道了上限下限就好做了。对于 $k<mn\vee k>mx$ 一定无解，若有解则尝试将最优移动进行若干次拆分即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define pii pair<int,int>
#define mid ((l+r)>>1)
#define fi first
#define se second
#define SZ(a) ((int)(a).size())
#define END(a) (prev((a).end()))
#define pc(a) putchar(a)
#define mp(a,b) make_pair(a,b)
#define pb(a) push_back(a)
#define no return puts("NO"),void()
#define yes return puts("YES"),void()
typedef long long ll;
const int N = 3e3+5;
const int mod = 998244353;
const ll INFLL = LONG_LONG_MAX;
const int INF = INT_MAX;
inline void cmax(int&a,int b){a=max(a,b);}
inline void cmin(int&a,int b){a=min(a,b);}
inline void add(int&a,int b){a+=b;if(a>=mod)a-=mod;}
inline int read()
{
	int x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
int n,k,mx,mn;
vector<int>ans[N*N];
char s[N];
bool fl=1;
inline void SOLVE()
{
	n=read(),k=read();cin>>(s+1);
	for(int i=1;i<=n;i++)if(s[i]=='R')for(int j=i;j<=n;j++)if(s[j]=='L')++mx;
	while(fl)
	{
		fl=0,++mn;
		for(int i=1;i<=n;i++)if(s[i]=='R'&&s[i+1]=='L')
			ans[mn].push_back(i),swap(s[i],s[i+1]),++i,fl=1;
	}fl=0;--mn;
	if(k<mn||k>mx)return puts("-1"),void();
	int sum=k-mn;
	for(int i=1;i<=mn;i++)
	{
		vector<int>res;
		for(int j:ans[i])if(sum)printf("1 %lld\n",j),sum--;else res.push_back(j);
		if(SZ(res)){printf("%lld ",SZ(res));for(int j:res)printf("%lld ",j);puts("");}else ++sum;
	}
	return ;
}
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	int T=1;while(T--) SOLVE();return 0;
}
```

---

