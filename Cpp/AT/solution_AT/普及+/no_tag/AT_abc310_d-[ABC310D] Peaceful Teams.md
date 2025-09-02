# [ABC310D] Peaceful Teams

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc310/tasks/abc310_d

$ N $ 人のスポーツ選手がいます。

$ N $ 人の選手たちには互いに相性の悪い選手のペアが $ M $ 組あり、相性の悪い組のうち $ i\ (1\leq\ i\leq\ M) $ 組目は $ A\ _\ i $ 番目の選手と $ B\ _\ i $ 番目の選手です。

あなたは、選手を $ T $ チームに分けます。 どの選手もちょうど一つのチームに属さなければならず、どのチームにも少なくとも一人の選手が属さなければなりません。 さらに、どの $ i=1,2,\ldots,M $ についても、 $ A\ _\ i $ 番目の選手と $ B\ _\ i $ 番目の選手が同じチームに属していてはいけません。

この条件を満たすチーム分けの方法は何通りあるか求めてください。 ただし、チーム分けの方法が異なるとは、ある二人が存在して、彼らが一方のチーム分けでは同じチームに所属し、もう一方では異なるチームに所属することをいいます。

## 说明/提示

### 制約

- $ 1\leq\ T\leq\ N\leq10 $
- $ 0\leq\ M\leq\dfrac{N(N-1)}2 $
- $ 1\leq\ A\ _\ i\lt\ B\ _\ i\leq\ N\ (1\leq\ i\leq\ M) $
- $ (A\ _\ i,B\ _\ i)\neq\ (A\ _\ j,B\ _\ j)\ (1\leq\ i\lt\ j\leq\ M) $
- 入力はすべて整数
 
### Sample Explanation 1

次の $ 4 $ 通りのチーム分けが条件を満たします。 !\[\](https://img.atcoder.jp/abc310/b92c2629f68d56350fe18e6d0a8fa060.png) 他に条件を満たすチーム分けは存在しないので、$ 4 $ を出力してください。

### Sample Explanation 2

条件を満たすチーム分けがひとつも存在しないこともあります。

### Sample Explanation 3

相性の悪いペアがひとつも存在しないこともあります。

## 样例 #1

### 输入

```
5 2 2
1 3
3 4```

### 输出

```
4```

## 样例 #2

### 输入

```
5 1 2
1 3
3 4```

### 输出

```
0```

## 样例 #3

### 输入

```
6 4 0```

### 输出

```
65```

## 样例 #4

### 输入

```
10 6 8
5 9
1 4
3 8
1 6
4 10
5 7
5 6
3 7```

### 输出

```
8001```

# 题解

## 作者：Coffee_zzz (赞：11)

### 分析

看到 $1 \le T \le N \le 10$，考虑搜索。

我们可以枚举每个选手放在 $T$ 个队伍中的每个队，然后判断是否满足题中所说的 $M$ 组选手之间的限制和每个队伍至少有 $1$ 个选手的限制，如果满足就给答案变量增加 $1$。因为这 $T$ 个队伍是没有顺序关系的，所以我们要给答案变量除以 $T$ 的阶乘。

上述做法的复杂度为 $O(N^T \times (T+M))$，无法接受，考虑剪枝。

我们记录当前枚举到的选手 $pos$ 和存在选手的队伍数 $now$，同时开一个数组 $cnt_i$ 表示第 $i$ 个队伍的选手数用于更新 $now$。

搜索时，如果 $n-pos+1<t-now$，即还没有枚举到的选手数小于还不存在选手的队伍数，我们就不需要往下枚举了，因为无论之后怎么安排，总会有队伍没有选手。

增加这个剪枝后，我们就可以通过此题了。记得要给答案变量除以 $T$ 的阶乘。

### 代码

```c++
#include <bits/stdc++.h>

using namespace std;
const int N=105;
int n,t,m,a[N],b[N],num[N],cnt[N],ans;
void dfs(int pos,int now){
	if(n-pos+1<t-now) return;
	if(pos==n+1){
		for(int i=1;i<=m;i++) if(num[a[i]]==num[b[i]]) return;
		ans++;
		return;
	}
	for(int i=1;i<=t;i++){
		if(cnt[i]){
			cnt[i]++;
			num[pos]=i;
			dfs(pos+1,now);
			cnt[i]--;
		}
		else{
			cnt[i]++;
			num[pos]=i;
			dfs(pos+1,now+1);
			cnt[i]--;
		}
	}
}
signed main(){
	cin>>n>>t>>m;
	for(int i=1;i<=m;i++) cin>>a[i]>>b[i];
	dfs(1,0);
	for(int i=1;i<=t;i++) ans=ans/i;
	cout<<ans<<endl; 
	return 0;
}
```

---

## 作者：Lucky_Cloud (赞：8)

一道比较简单的爆搜题。~~虽然在考场上没写出来。~~
## 分析
我们可以直接枚举每个人加入哪个团队（如果团队中没有与他相斥的人）。然后答案加一就可以了。

为了是答案更优，我们可以小小地剪一剪枝。

1. 如果剩下的不能满足每一组都有人，就新建一个组，不考虑加入新组。
1. 如果当前组数与要求组数相同就不新建小组了。

但其实，这题的难点是在判重，我们可以用状压~~应该是吧~~去做。也就是每一个人加入的小组转为一个整数。但是，一定要注意，要边建小组边考虑加入目前建了那些组。

因为状态会爆数组所以用 ```map``` 标记即可。



## Code
马蜂不好，不喜勿喷。
```cpp
#include <bits/stdc++.h>
#define ll long long
#define vint vector<int>
#define ull unsigned ll
using namespace std;

int n, t, m, ans, mp[20][20];
vint v[20];
map<ll, int> mps;

void dfs(int x, int tm, ll num) {//x 传的是当前第几个人，tm 是目前有几个队伍，因为与队伍号无关，所以有多少组建多少组，num 是状态。
	if (x == n + 1 && tm == t && !mps[num]) {//处理边界，团队数要符合条件。
		ans++;
		mps[num] = 1;//标记状态。
//		cout << num << "\n";
		return;
	}
	else if(x == n + 1) {
		return;
	}
	if (t - tm < n - x + 1 && tm != 0) {//小剪枝
		for (int i = 1; i <= tm; i++) {
			if (!mp[i][x]) {//如果里面没有与他相斥的人
				for (int j = 0; j < v[x].size(); j++) mp[i][v[x][j]]++;//标记其他人不能进。注意：一定是++，不能是等于一，否则，可能其他标记了同样的人后面删除标记，就可能会使相斥的人在一个组。
				num = num * 10 + i - 1;//状压
				dfs(x + 1, tm, num);
				for (int j = 0; j < v[x].size(); j++) mp[i][v[x][j]]--;//删除标记。
				num /= 10;
			}
		}
	}
	if (tm == t) return;//如果队够了就不新建了
	++tm;
	for (int i = 0; i < v[x].size(); i++)
		mp[tm][v[x][i]]++;
	num = num * 10 + tm - 1;//状压
	dfs(x + 1, tm, num);
	for (int i = 0; i < v[x].size(); i++)
		mp[tm][v[x][i]]--;
	num /= 10;
}

int main() {
	cin >> n >> t >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		cin >> x >> y;
		v[x].push_back(y);//标记相斥的人。
		v[y].push_back(x);//同上
	}
	dfs(1, 0, 0);
	cout << ans << endl;
	return 0;
}
```


---

## 作者：良心WA题人 (赞：4)

## 题意

$n$ 个人，某些人不能放到同一组里，问分成 $t$ 组的方案数。

## 思路

~~鉴定为学状压学的。~~

看到 $n,t\le 10$，显然状压。先预处理出一组的形态是否可行，然后定义 $f_{i,j}$ 表示前 $i$ 组选了的所有人状态为 $j$ 的方案数。显然枚举子集转移即可。

注意到本题的队伍无区别，所以要求枚举的子集的 `lowbit` 必须等于全部的 `lowbit` 才允许转移，否则会算重。

然后你就 $O((m+2^n\times n^2)\times\log m +t\times 3^n)$ 过掉了这个题。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NN=14;
long long f[NN][1<<NN];
bool flag[1<<NN];
int lowbit(int x)
{
	return x&-x;
}
int main()
{
	int n,t,m;
	scanf("%d%d%d",&n,&t,&m);
	set<pair<int,int> >st;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		u--,v--;
		if(u>v)
			swap(u,v);
		st.insert({u,v});
	}
	for(int i=0;i<1<<n;i++)
	{
		flag[i]=true;
		for(int j=0;j<n;j++)
			for(int k=j+1;k<n;k++)
				if((i>>j&1)&&(i>>k&1)&&st.count({j,k}))
					flag[i]=false;
	}
	f[0][0]=1;
	for(int i=1;i<=t;i++)
		for(int j=0;j<1<<n;j++)
			for(int k=j;;k=k-1&j)
			{
				if(lowbit(k&j)!=lowbit(j))
					f[i][j]+=f[i-1][k]*flag[j^k];
				if(!k)
					break;
			}
	printf("%lld",f[t][(1<<n)-1]);
	return 0;
}
```

---

## 作者：DengDuck (赞：2)

我考场上没做出来！

我们先考虑每个队是不同的，求出一个答案，再除去 $t!$ 即可。

那这个答案怎么求呢？由于本身有一些限制，而且数据较小，所以暴力是一个不错的选择。

这样的时间复杂度是 $O(t^n)$ 的，有一点点困难，所以我们加一两个小剪枝即可。

比如，空队数量比人还多，那肯定填不完，所以不继续搜索。

```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL N=15;
LL n,t,m,ans,x,y,vis[N],c[N],sz[N];
vector<LL>v[N];
void dfs(LL x,LL tot)
{
	if(x>n)
	{
		ans+=(tot==t);
		return;
	}
	if(t-tot>n-x+1)return;
	LL b[N],cnt=0;
	memset(b,0,sizeof(b));
	for(LL i:v[x])
	{
		if(x<i)continue;
		cnt++;
		b[c[i]]=1;
	}
	for(int i=1;i<=t;i++)
	{
		if(b[i]==0)
		{
			c[x]=i;
			sz[i]++;
			dfs(x+1,tot+(sz[i]==1));
			c[x]=0;
			sz[i]--;
		}
	}	
}
int main()
{
	cin>>n>>t>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	for(int i=1;i<=t;i++)ans/=i;
	cout<<ans<<endl;
}
```

---

## 作者：Yashajin_Ai (赞：2)

### 思路
定义深搜去寻找所有可能的组队方案，每次调用 $x$ 表示当前处理的运动员编号，$y$ 表示剩余可用团队的数量，尝试给每个运动员染色，并检查染色方案是否符合要求，全部都有归属后，即可停止深搜，然后，遍历团队编号，对于每个团队，检查当前运动员与其不兼容的运动员是否属于同一个团队，如果属于同一个团队，则跳过该团队，否则，将当前运动员分配到该团队，并深搜处理下一个运动员，调用完后需要将当前运动员从团队中移除，以便进行下一次尝试。

再计算一下输出即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int Maxn=1<<12;
int n,m,t,a[301],b[301],f[11],vis[11],ans=0;
void dfs(int x,int y){
    if(x==n){
        if(y!=0){
        	return;
		}
        for(int i=1;i<=m;i++){
            if(f[a[i]]==f[b[i]]){
            	return;
			}
        }
        ans++;
        return;
    }
    if(n-x<y){
    	return;
	}
    for(int i=1;i<=t;i++){
        if(!vis[i]){
            vis[i]=1;
            f[x+1]=i;
            dfs(x+1,y-1);
            vis[i]=0;
        }
        else{
            f[x+1]=i;
            dfs(x+1,y);
        }
    }
}
int main(){
    cin>>n>>t>>m; 
    for(int i=1;i<=m;i++){
    	cin>>a[i]>>b[i];
	}
    int mod=1;
    for(int i=1;i<=t;i++){
    	mod*=i;
	}
    dfs(0,t);
    cout<<ans/mod;
}
```

---

## 作者：__Aaaaaaaa (赞：1)

题目大意：$n$ 个不同的球放进 $t$ 个相同的盒子，现在要求有 $m$ 对矛盾关系，矛盾关系的两个球不能放进同一个盒子里，盒子非空，求方案数。

首先拿到这道题是一眼容斥加第二类斯特林数。

容斥了 $m$ 条关系后，相当于要把当前容斥的关系的两个球绑在一起（用并查集），然后把处理后的球放在盒子中的方案数嘛……  
球异？盒同？非空？第二类斯特林！  
方案数就是 $S2(n')(t)$。

但是可以立马发现一个问题：$m$ 最坏是 $10\times 9 \times \frac12=45$。   
$O(2^m)$ 的算法立马就炸了。

作者是没想到可以直接优雅地搜索剪枝的。

就针对 $m > 20$ 的情况，可以发现制约数量比较多，对于 $n=10$ 的图而言也足够稠密了。  
于是就写了一个比较暴力的方式，将这张矛盾关系的图建出来后，搜索优先考虑度数比较多的，然后几乎没有任何优化就将这类数据点跑过去了，虽然时间复杂度是正解的 $t!$ 倍……

就这样，数据点分治加两个错解就水过了这道题……

这个时候管理大大把题解打回了。emmm……还是证明一下原因吧，因为 $n$ 和 $t$ 的范围都只有 $10$，而针对第二类数据点而言，边足够多($m > 20$)，所以在先选度数多再选度数少的节点后，可以将 $10^{10}$ 的爆搜大大降低，完全跑不满，搜索次数在作者亲自手玩数据验证后最坏大概在 $[10^8,5\times 10^8]$，而时限是 $2s$，可以轻松跑过去。

### Code:
```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
const int N=210;
int h[N],e[N],ne[N],ct=1;
void add(int x,int y){
	e[ct]=y,ne[ct]=h[x],h[x]=ct++;//建出矛盾关系的图
}
ll s2[N][N];
void init(int n){//预处理第二类斯特林数
	s2[0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=i;++j){
			s2[i][j]=s2[i-1][j-1]+s2[i-1][j]*j;
		}
	}
}
int n,t,m;
ll ans;
int A[N],B[N];
int p[N],d[N];
int find(int x){
	return p[x]==x?x:p[x]=find(p[x]);
}
bool cmp(int x,int y){
	return d[x]>d[y];
}
bool vis[N];
int cho[N];
int cnt[N];
void dfs(int x,int k){
	if(n-x+1<t-k)return;
	if(x>n){
		++ans;
		return;
	}
	int u=p[x];
	bool vis[11];
	for(int i=1;i<=t;++i)vis[i]=false;
	for(int i=h[u];i;i=ne[i]){
		vis[cho[e[i]]]=true;
	}
	for(int i=1;i<=t;++i){
		if(!vis[i]){
			cho[u]=i;
			++cnt[i];
			dfs(x+1,k+(cnt[i]==1));
			--cnt[i];
			cho[u]=0;
		}
	}
}
int main(){;
	scanf("%d%d%d",&n,&t,&m);
	for(int i=0;i<m;++i){
		scanf("%d%d",A+i,B+i);
		add(A[i],B[i]),add(B[i],A[i]);
	}
	init(N-10);
	if(m<=20){//针对此类，直接容斥
		for(int s=0;s<1<<m;++s){
			int sign=1;
			for(int i=1;i<=n;++i)p[i]=i;
			for(int i=0;i<m;++i){
				if(s>>i&1){
					p[find(A[i])]=find(B[i]);
					sign*=-1;
				}
			}
			int cnt=n;
			for(int i=1;i<=n;++i)
				if(find(i)!=i)
					--cnt;
			ans+=s2[cnt][t]*sign;
		}
		printf("%lld\n",ans);
	}
	else{//玄学暴搜
		for(int i=1;i<=n;++i)p[i]=i;
		sort(p+1,p+1+n);
		dfs(1,0);
		for(int i=1;i<=t;++i)//真的是t!倍，没骗人
			ans/=i;
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：TKXZ133 (赞：1)

[Peaceful Teams](https://www.luogu.com.cn/problem/AT_abc310_d)

### 题目大意

将 $n$ 个人分成 $T$ 组，要求每组不能包含敌对的人，问有多少种分法。

### 思路分析

注意到 $n,T$ 均很小，考虑爆搜。

注意到直接枚举会枚举到分组顺序的全排列，所以可以强行嵌定大小关系去重。

```cpp
void dfs(int s){
    if(s==n+1){
        for(int i=1;i<=t;i++) if(!tt[i]) return ;
        for(int i=2;i<=t;i++) if(sk[i-1][1]>sk[i][1]) return ;//去重
        ans++;
        return ;
    }
    for(int i=1;i<=t;i++){
        int flag=0;
        for(int j=1;j<=tt[i];j++) if(bad[sk[i][j]][s]){flag=1;break;}//判断敌对
        if(flag) continue;
        sk[i][++tt[i]]=s;
        dfs(s+1);
        tt[i]--; 
    }
}
```

正常搜索的时间复杂度为 $O(T^n)$，无法通过，于是加一点点剪枝：

- 如果当前人数小于当前的空组数，那么填到最后一定存在空组，直接返回。

- 每次搜索都优先判定是否合法。

然后就飞过去了。

### 代码

```cpp
#include <iostream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <cstdio>
 
using namespace std;
const int N=110;
 
int ans,n,t,m,in1,in2;
int bad[N][N],sk[N][N],tt[N];
 
void dfs(int s){
    for(int i=2;i<=t;i++) 
        if(tt[i-1]&&tt[i]&&sk[i-1][1]>sk[i][1]) return ; 
    int cnt=0;
    for(int i=1;i<=t;i++) 
        if(!tt[i]) cnt++;
    if(n-s+1<cnt) return ;
    if(s==n+1){
        for(int i=1;i<=t;i++) if(!tt[i]) return ;
        ans++;
        return ;
    }
    for(int i=1;i<=t;i++){
        int flag=0;
        for(int j=1;j<=tt[i];j++) if(bad[sk[i][j]][s]){flag=1;break;}
        if(flag) continue;
        sk[i][++tt[i]]=s;
        dfs(s+1);
        tt[i]--; 
    }
}
 
int main(){
    scanf("%d%d%d",&n,&t,&m);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&in1,&in2);
        bad[in1][in2]=bad[in2][in1]=1;
    }
    dfs(1);
    cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：Genius_Star (赞：1)

### 题意：
有 $N$ 个人，需要将其分配到 $T$ 个小组里面，这 $N$ 个中有 $M$ 对仇家，对于每对仇家 $a_i$ 和 $b_i$ 不能在一个小组里面。

求分配的方案数是多少？

### 思路：
考虑到 $N$ 和 $T$ 都很小，可以直接暴力每一个选择的小组，时间复杂度为 $O(T^N)$，这样肯定得 TLE，所以考虑优化。

因为这最后 $T$ 个小组每一个小组至少都要有一个人，所以我们可以记录一下哪些小组没有人（爆搜的时候标记一下即可）。

假设当前暴力搜索到了第 $pos$ 个人，还有 $sum$ 个小组一个人都没有，如果剩余的人填不满剩下的小组，那么这个方案失效，则是 $N-pos+1<sum$ 的话，就退出。

然后，我们要找出重复的方案，发现对于每一个小组成员的情况不变的话，对于这种情况的全排列就都是重复的，所以对于最后的答案我们要除以一个 $T$ 的阶乘（也就是小组的全排列方式）。
### 完整代码：
```cpp
#include<bits/stdc++.h>
#define INF INT_MAX
using namespace std;
typedef long long ll;
const int N=105;
inline ll read(){ //快读 
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
            f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){ //快输 
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll a[N],b[N],c[N],s[N];
ll ans=0,n,t,m;
void dfs(ll x){
	int sum=0;
	for(int i=1;i<=t;i++)
	  if(!s[i]) 
		sum++;
	if(sum>n-x+1) 
	  return;
	if(x==n+1){
		for(int i=1;i<=m;i++)
		  if(c[a[i]]==c[b[i]]) 
			return;
		for(int i=1;i<=t;i++)
		  if(!s[i]) 
			return ;
		ans++;
		return;
	}
	for(int i=1;i<=t;i++){
		c[x]=i,s[i]++;
		dfs(x+1);
		s[i]--;
	}
}
int main(){
	n=read(),t=read(),m=read();
	for(int i=1;i<=m;i++)
	  a[i]=read(),b[i]=read();
	c[1]=1,s[1]=1;
	dfs(2);
	for(int i=t-1;i>=2;i--)
	  ans/=i;
	write(ans);
	return 0;
}
```


---

## 作者：AirQwQ (赞：1)

~~被同学骗过来做的。~~

## 分析

看到 $1 \le T \le N \le 10$ 这个范围就知道肯定是爆搜，只需要分别把每个人放到每个队里面再判断合不合法就可以了，一种情况讨论完还要判断每个队有没有人，最后因为每组无顺序，所以要除序。

信心满满的交一发结果 [T 飞了](https://www.luogu.com.cn/record/115790311)，（AT 的题返回 $ \operatorname{UKE}$ 就是超时，爆空间，显然这里是超时）考虑优化。

- 我们发现，因为顺序我们会枚举很多次，所以开始时就固定 $1$ 的位置可以让后面枚举情况为原来的 $\frac{1}{n}$ 但依旧超时 $2$ 个点。

- 再看，每个队没有人的情况很多，费时间，所以进行可行性剪枝，如果当前剩下没判断的人数小于空着的队伍数，那它一定不符合情况，直接 ```return```。

这时就能跑过所有数据啦。~~（还喜提最劣解）~~

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool v[15][15],f;
int a[15][15];
int cnt[15];//记录每个队的人数
int n,t,m,ans;
inline void dfs(int s,int num){
	if(n-s+1+num<t) return;//可行性剪枝
	if(s>n){
		f=1;
		ans+=f;
		return;
	}
	for(int i=1;i<=t;i++){
		f=1;
		for(int j=1;j<=cnt[i];j++)
			if(v[a[i][j]][s]){
				f=0;
				break;
			}
		if(!f) continue;
		a[i][++cnt[i]]=s;
		if(cnt[i]==1)  dfs(s+1,num+1);//判断是否为新队列
		else dfs(s+1,num);
		cnt[i]--;//回溯
	}
}
int val(int n){//除序
	int num=1;
	for(int i=1;i<t;i++)
		num*=i;
	return num;
}
int main(){
	a[1][1]=1;
	cnt[1]=1;//减少顺序
	int a,b;
	cin>>n>>t>>m;
	for(int i=1;i<=m;i++){
		cin>>a>>b;
		v[a][b]=v[b][a]=1;//记录是否合法
	}
	dfs(2,1);
	cout<<ans/val(n);
	return 0;
} 

```

---

## 作者：small_john (赞：0)

## 思路

没见过如此简单的 D 题。

看见 $n$ 的范围这么小，你不觉得可以用 DFS 吗？

我们在 DFS 时，用 $vis_{i,j}$ 表示第 $i$ 个人的敌人有多少个加入了第 $j$ 队。

用两个参数 $x,sum$，表示正在处理第 $x$ 个人，目前有 $sum$ 个队伍。

如果 $sum>t$，说明队伍太多，退出。

如果 $x>n$，则找到一组解，答案加 $1$，退出。

先让第 $x$ 个人加入前面的队伍，但必须满足 $t-sum\le n-x$，则加入前面的队伍可以让 $sum=t$。在让 $x$ 加入新的队伍。每加入一个队伍 $q$，就把每个敌人 $p$ 的 $vis_{p,q}$ 加一。

最后输出答案即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e2+5;
int n,t,m,ans;
int vis[N][N];
vector<int> v[N];
void dfs(int x,int sum)
{
	if(sum>t) return;
	if(x>n)
	{
		ans++;
		return;
	}
	for(int i = 1;i<=sum;i++)
		if(t-sum<=n-x&&vis[x][i]==0)
		{
			for(int j = 0;j<v[x].size();j++)
				vis[v[x][j]][i]++;
			dfs(x+1,sum);
			for(int j = 0;j<v[x].size();j++)
				vis[v[x][j]][i]--;
		}
	for(int i = 0;i<v[x].size();i++)
		vis[v[x][i]][sum+1]++;
	dfs(x+1,sum+1);
	for(int i = 0;i<v[x].size();i++)
		vis[v[x][i]][sum+1]--;
}
signed main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>t>>m;
	for(int i = 1,x,y;i<=m;i++)
		cin>>x>>y,v[x].push_back(y),v[y].push_back(x);
	dfs(1,0);
	cout<<ans;
 	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

**【题目分析】**

看到数据范围较小，考虑爆搜。注意本题对两种方案不同的定义是**当且仅当一种方案两名运动员在同一组而另一种方案不在同一组**，所以可以发现搜索的最劣时间复杂度是 $\Theta(n \times n!)$，可以通过。

我们发现搜索到当前的队员时，所有空的组是本质相同的。所以用一个变量记录当前用到了几个组，每次在这几个组里搜即可。

**【代码】**

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,t,m,u,v,g[15][15],s[15][15],ans;
void dfs(int x,int tot){
    if(x == n+1) return ans += (tot == t+1),void();//注意要求恰好分 T 组而不是小于等于 T 组
    int ss[15];
    for(int i = 1;i <= min(tot,t);i ++){
        if(!s[i][x]){
            for(int j = 1;j <= n;j ++) ss[j] = s[i][j];
            for(int j = 1;j <= n;j ++) s[i][j] = max(s[i][j],g[x][j]);
            dfs(x+1,(i == tot ? tot+1 : tot));
            for(int j = 1;j <= n;j ++) s[i][j] = ss[j];
        }   
    }
}
int main(){
    cin >> n >> t >> m;
    for(int i = 1;i <= m;i ++) cin >> u >> v,g[u][v] = g[v][u] = 1;
    dfs(1,1);
    cout << ans;
    return 0;
}
```

---

## 作者：D2T1 (赞：0)

数据范围很小，直接暴搜！

注意两种方案不同当且仅当一种方案两个数在同一组而另一种方案这两个数不在同一组，所以我们并不在乎组的编号。

所以在暴搜的时候不应该枚举 $[1,T]$，而应该先枚举选过的组，然后再枚举选择没选过的组中编号最小的那个组，可以保证不重不漏。

方案可行当且仅当每组都有人，且满足 $A_i,B_i$ 不在同一组。

```cpp
//AT_abc310_d
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 200;
int n, t, m, a[N], b[N];
int c[N], s[N];
ll ans = 0, cnt = 0;

void dfs(int x){
	if(x == n+1){
		for(int i = 1; i <= t; ++ i){
			if(!s[i]){
				return;
			}
		}
		for(int i = 1; i <= m; ++ i){
			if(c[a[i]] == c[b[i]]){
				return;
			}
		}
		++ ans;
	} else {
		for(int i = 1; i <= cnt; ++ i){
			c[x] = i;
			++ s[i];
			dfs(x+1);
			-- s[i];
			c[x] = 0;
		}
		if(cnt == t) return;
		c[x] = ++cnt;
		++ s[cnt];
		dfs(x+1);
		-- s[cnt];
		c[x] = 0;
		-- cnt;
	}
}

void solve(){
	scanf("%d%d%d", &n, &t, &m);
	for(int i = 1; i <= m; ++ i){
		scanf("%d", &a[i]);
		scanf("%d", &b[i]);
	}
	dfs(1);
	printf("%lld\n", ans);
}

int main(){
	solve();
	return 0;
}
```

---

