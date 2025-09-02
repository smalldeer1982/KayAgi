# Korney Korneevich and XOR (easy version)

## 题目描述

给一个长度为 $n$ 的序列 $a_1,a_2,\dots,a_n$ ，寻找在 $a$ 的所有递增子序列（可以为空）的异或和中出现的数。

## 说明/提示

$1\le n\le10^5,0\le a_i\le500$ 。
### 样例解释
对于第一个样例：
- 子序列 $\{\}$ 的异或和为 $0$ 。
- 子序列 $\{2\}$ 的异或和为 $2$ 。
- 子序列 $\{4\}$ 的异或和为 $4$ 。
- 子序列 $\{2,4\}$ 的异或和为 $6$ 。

其他子序列的异或和与上述其中一个子序列的异或和相等。

## 样例 #1

### 输入

```
4
4 2 2 4```

### 输出

```
4
0 2 4 6```

## 样例 #2

### 输入

```
8
1 0 1 7 12 5 3 2```

### 输出

```
12
0 1 2 3 4 5 6 7 10 11 12 13```

# 题解

## 作者：Cht_master (赞：6)

- 题意简述：给定数列 $a$，求其所有上升子序列的异或和，升序输出。$1\le n\le 10^5$，$0\le a(i)\le 500$。

- 题目解析：

  - 容易得到最大的值域是 $512=2^{\lceil\log_2500\rceil}$。

  - 与上升子序列相关，考虑在这道题上用上升子序列的转移套路。定义 $f(i,S)$ 表示以第 $i$ 个元素结尾的上升子序列能否得到 $S$ 这个数。容易列出状态转移方程：
    $$
    f(i,S)=\bigvee_{j=1}^{i-1}f(j,S\oplus a(i))|(a(j)<a(i),j<i)
    $$

  - 由于有很明显的偏序性质，考虑用桶来统计答案。记 $pos(S)$  表示能达到 $S$ 的上升子序列的最末元素的最小值。因为下标是从小到大枚举，自然满足 $j<i$；又因为 $pos(S)$ 放的是最小的元素，所以只要满足 $pos(S\oplus a(i))<a(i)$ 就可以说明可以以 $a(i)$  为末尾得到 $S$ 了。

- ```cpp
  //f(i,S1)|=f(j,S1^a(i))|(i>j&&a(i)>a(j)).
  #pragma optimize(2,"Ofast","inline")
  #include<bits/stdc++.h>
  using namespace std;
  const int mxN(1e5),mxD(511);
  int n,a[mxN+5],pos[mxD+5],bk[mxD+5],cnt;
  int main(){
  	memset(pos,0x3f,sizeof(pos));
  	scanf("%d",&n);
  	for(int i(1);i<=n;++i)scanf("%d",&a[i]);
  	for(int i(1);i<=n;++i){
  		pos[a[i]]=min(pos[a[i]],a[i]),bk[a[i]]=1;
  		for(int S(0);S<=mxD;++S)if(pos[(S^a[i])]<a[i])bk[S]=1,pos[S]=min(pos[S],a[i]);
  	}
  	bk[0]=1;for(int S(0);S<=mxD;++S)cnt+=(bk[S]!=0);
  	printf("%d\n",cnt);
  	for(int S(0);S<=mxD;++S)if(bk[S])printf("%d ",S);
  	return 0;
  }
  ```

  

---

## 作者：123zbk (赞：3)

注意到 $a_{i}\le500$，所以最大的值域为 $512$，我们直接标记每一个数是否出现过即可。

创建一个数组 $pos$，$pos_i$ 代表所有异或和为 $i$ 的合法子序列中结尾数的最小值，以判断序列是否递增。

对于每个 $i$，如果存在 $j$，满足 $j$ 是此前可以得到的异或和，那么 $i\operatorname{xor} j$ 也是合法的，且 $pos_{i\operatorname{xor}j}= \min(pos_{i\operatorname{xor}j},i)$。

最后统计答案时不要忘记 $0$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1e4+5;
bool ans[maxn];
int n,x,res,pos[maxn];
int main()
{
	scanf("%d",&n);
	memset(pos,0x3f,sizeof(pos));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		for(int j=1;j<=512;j++)
		{
			if(ans[j]&&pos[j]<x)
			{
				int s=j^x;
				ans[s]=true;
				pos[s]=min(pos[s],x);
			}
		}
		ans[x]=true;
		pos[x]=min(pos[x],x);
	} 
	for(int i=1;i<=512;i++)
	{
		if(ans[i])
		{
			res++;	
		}	
	} 
	printf("%d\n",res+1);
	printf("0 ");
	for(int i=1;i<=512;i++)
	{
		if(ans[i])
		{
			printf("%d ",i);
		}
	}
	return 0;
} 
```

---

## 作者：Fireworks_Rise (赞：3)

# 闲话

- 当你亲身去感受程序运行的过程后，你会感觉很神奇！！！

# 解析思路

[CF1582F1 Korney Korneevich and XOR (easy version) ](https://www.luogu.com.cn/problem/CF1582F1)

声明：本题是 [CF1582F2 Korney Korneevich and XOR (hard version) ](https://www.luogu.com.cn/problem/CF1582F2) 的削弱版，此处是直接使用 hard 的做法...

往值域上想，可以先定义集合 $f_i$ 为所有以 $j \in [1,i-1]$ 结尾的子序列的异或值。

再考虑转移，一开始肯定想暴力枚举，对于每个 $a_i$，将 $a_i \oplus k$ 加入 $f_j$ 中，$k \in f_{a_i}$，由于要求序列是按数值递增排列的，所以还需满足 $a_i < j \le V$。

~~这里需说明，若用 vector 来存集合 $f_i$ 可能会导致超时，所以我们选用数组进行操作...~~

~~我们发现这样去做时间复杂度为 $O(n + V^3)$，明显会超时~~，再考虑优化，可以发现每个 $a_i$ 所加入的集合是个后缀，这样不仅浪费时间而且还对答案没有任何多的贡献，所以可以再此处进行优化。

设定 $last_i$	表示异或和为 $i$ 所覆盖后缀的左端点，加入 $i$ 后更新 $last_i$ 即可。

贴上蒟蒻的 code，细节看程序...

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
const int V=8210;
int n,a[N],last[V];
int f[V][V],g[V];
bool vis[V],isIn[V][V];
inline void init_() {
	for(int i=1;i<=8200;i++) {
		f[i][++g[i]]=0;
		last[i]=8200; 
	}
}
signed main() {
	init_();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	vis[0]=1;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=g[a[i]];j++) {
			int x=a[i]^f[a[i]][j];
			vis[x]=1;
			for(int k=a[i]+1;k<=last[x];k++) {
				if(!isIn[k][x]) {
					isIn[k][x]=1;
					f[k][++g[k]]=x;
				}
			}
			last[x]=min(a[i],last[x]);
		}
		g[a[i]]=0;
	}
	int ans=0;
	for(int i=0;i<=8200;i++)
		ans+=vis[i];
	printf("%d\n",ans);
	for(int i=0;i<=8200;i++)
		if(vis[i]) printf("%d ",i);
	printf("\n"); 
	return 0;
} 
```

---

## 作者：_AyachiNene (赞：2)

# 思路：
数据结构优化 dp 做法。容易发现异或出来的数值域很小，且最后要输出那些数，很自然就能想到 bitset 记个 $0/1$，很自然就能得到状态 $f_{i,j}$ 表示前 $i$ 个数，能凑出的集合为 $j$ 的方案数。考虑转移，状态只能从前面小于等于这个数的位置转移，直接用数据结构维护，把这一段的状态的 bitset 合并起来，在直接枚举每个数能否凑出来直接转移就行了。设数的值域 $s$，复杂度 $O(n\cdot s+n\log n\cdot \frac{s}{\omega})$。

# Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
	int res=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') f=-1;c=getchar();}
	while(c>='0'&&c<='9'){res=(res<<1)+(res<<3)+(c^48);c=getchar();}
	return res*f;
}
void write(int x)
{
	if(x<0){putchar('-');x=-x;}
	if(x>9) write(x/10);
	putchar(x%10+'0');
}
namespace Elaina
{
	bitset<8205>t[8205];
	inline int lowbit(int x){return x&-x;}
	inline void add(int x,bitset<8205>v){for(;x<=8200;x+=lowbit(x))t[x]|=v;}
	inline bitset<8205>query(int x){bitset<8205>res;for(;x;x-=lowbit(x))res|=t[x];return res;}
}
using namespace Elaina;
int n;
int a[1145141];
bitset<8205>ans,tmp,f[100005];
int main()
{
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	f[0][0]=1;
	add(1,f[0]);
	ans|=f[0];
	for(int i=1;i<=n;i++)
	{
		if(ans.count()==8192) break;
		tmp=query(a[i]+1);
		for(int j=0;j<=8200;j++) if(tmp[j]) f[i][j^a[i]]=1;
		add(a[i]+1,f[i]);
		ans|=f[i];
	}
	int cnt=0;
	for(int i=0;i<=8200;i++) if(ans[i]) ++cnt;
	write(cnt),puts("");
	for(int i=0;i<=8200;i++) if(ans[i]) write(i),putchar(' '); 
	return 0;
}

```

---

## 作者：Mason123456 (赞：2)

# CF1582F1

### 思路

先看数据。

$1 \le n \le 10^5,0 \le a_i \le 500$，可以发现，$n\times a_i$ 的时间复杂度刚好是够用的，所以从这个方面入手思考。

关于**上升子序列**的问题，可以参考在[基础题：导弹拦截](https://www.luogu.com.cn/problem/P1020)中我们设 $dp_i$ 表示长度为 $i$ 的上升子序列结尾**最小值**。

结合本题，把 $dp_i$ 设为**异或和**为 $i$ 时末尾的**最小值**。

于是有：
$$
dp_{j \space \oplus \space a_i} = \min(dp_{j \space \oplus \space a_i},a_i)[dp_j < a_i]
$$
其中 $dp_0 = 0, dp_i = \infin(i \ne0)$。

解释一下：

当 $dp_j < a_i$ 时，说明异或和为 $j$ 的序列是可以插入 $a_i$ 这个元素，但是不会产生更新，此时会诞生一个新的序列的异或和为 $j \oplus a_i$，再作比较即可。

### CODE

```cpp
// 详细注释版
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int a[N], f[N], d[N], n;// a是输入元素，f是dp数组，d是答案桶，记录可以做到的异或和
int main(){
	cin>>n;
	for(int i = 1;i <= n;i++){
		cin>>a[i];
	}
	memset(f, 0x3f, sizeof f);// 其中，为了取min，其他元素初始化为最大
	f[0] = 0, d[0] = 1;
	for(int i = 1;i <= n;i++){
		for(int j = 0;j <= 512;j++){// 关于512的分析，可以参考其他题解。
			if(f[j] < a[i]){// 当f[j]>a[i]时，不存在满足条件的异或，舍去
				f[j xor a[i]] = min(f[j xor a[i]], a[i]);// 这里取异或和最小值自然是min，由于我们初始化的是inf，所以成立
				d[j xor a[i]] = 1;
			}
		}
	}
	int num = 0;
	for(int j = 0;j <= 512;j++){
		if(d[j])	num++;// 单纯的统计数量
	}
	cout<<num<<"\n";
	for(int j = 0;j <= 512;j++){
		if(d[j])
			cout<<j<<" ";
	}
	return 0;
}
```

---

## 作者：Inui_Sana (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1582F1)

解题思路：dp+贪心

先看到这题的数据范围，$1\le n\le 10^5$，$0\le a_i\le 500$。$n^2$ 肯定是过不了的，但是 $a_i$ 很小，所以我们可以直接标记每个数是否满足题目条件。

创建一个数组 $e$，$e_i$ 表示所有异或和为 $i$ 的递增子序列中的最小的结尾数。对于每个 $i$，除 $a_i$ 本身为一个递增子序列外，如果有 $j$ 满足 $j$ 是此前可以得到的异或和且 $e_j<i$，则 $i\otimes j$ 也是满足条件的，$e_{i\otimes j}=\min (e_{i\otimes j},i)$。

code：

```cpp
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<queue>
#define lb lower_bound
using namespace std;
typedef long long ll;
const int maxn=-1,inf=2147483647;
const int mod=1;
int n,ans,e[607];
bool bk[607];
void solve(){
	scanf("%d",&n);
	memset(e,0x7f,sizeof e);//初始化为一个很大的数，方便后面处理
	for(int i=1,x;i<=n;i++){
		scanf("%d",&x);
		for(int j=1;j<=512;j++){
			if(bk[j]&&x>e[j]){
				e[j^x]=min(e[j^x],x);
				bk[j^x]=true;
			}
		}
		e[x]=min(e[x],x);
		bk[x]=true;
	}
	for(int i=1;i<=512;i++)ans+=bk[i];
	printf("%d\n0",ans+1);
	for(int i=1;i<=512;i++){
		if(bk[i])printf(" %d",i);
	}
}
signed main(){
	int t=1;
//	scanf("%d",&t);
	while(t--)solve();
}
```
ps：别忘了0

---

## 作者：wizardMarshall (赞：0)

## 题意

求所有上升子序列的异或值。

## 思路

这题是简单版，值域为 $n \le 10 ^ 5$，$a_i \le 500$。如果暴力枚举前面每一个元素，复杂度为 $O(n^2)$，无法通过此题。

但是 $a$ 的值域非常小，所以我们考虑建一个桶，桶的下标对应得到的异或值。遍历每个元素时，只要枚举桶的范围 $2^{\lceil \log_2 500 \rceil}=512$ 即可。

但是题面中还有一个要求，是上升子序列。因此，桶数组不仅仅是 $01$ 数组，还要存储值。这个值就是上一个元素的值。如果上一个值小于当前值，则可以接上。

总结：桶数组的定义就是，当前异或和为 $i$ 时，结尾元素的最小值。

初始桶数组全为无穷大，只有空子序列为 $0$。

## 代码

为防止越界，枚举范围开到了 $1000$。


```c++

#include <bits/stdc++.h>
using namespace std;
int a[100005];
int ans[1005];//表示当前子序列的异或和为i时，结尾元素最小（这样才方便接上）
signed main() {
	memset(ans, 127, sizeof(ans));//初始全无穷大
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	ans[0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= 1000; j++) {
			if (ans[j] < a[i]) {
				ans[j ^ a[i]] = min(ans[j ^ a[i]], a[i]);//更新桶数组
			}
		}
	}
	set <int> sum;
	for (int i = 0; i <= 1000; i++) {
		if (ans[i] < 1e9) {//即存在子序列异或和为i（不为无穷大）
			sum.insert(i);
		}
	}cout << sum.size() << endl;
	for (auto i : sum) {
		cout << i << ' ';
	}
	return 0;
}

```

---

## 作者：songzhihan2010 (赞：0)

观察数据很难不发现 $a_i$ 的范围非常小，异或和不会超过 512,于是可以想到直接枚举可能的异或和，通过公式 $x \oplus y \oplus y=x$，所以我们可以记录下当前所有可能得到的异或和，但现在又面临一个问题——怎样保证得到的序列是递增的？$\\$ 我这里直接用 $vis_i$ 表示异或和为 $i$ 的递增序列且这个序列的结尾为数字 $vis_i$，其中 $vis_i$ 的初值直接赋值成无穷大，这样就不会将不满足的条件来更新 $vis$ 数组，具体细节见代码。

[AC record](https://codeforces.com/contest/1582/submission/286515293)
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll read() {
	ll x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
const ll N=1e5+10;
ll vis[550];
ll x,n,ans=0;
signed main(){
	n=read();
	for (int i=1;i<=512;i++){
		vis[i]=1e9;
	}
	for (int i=1;i<=n;i++){
		x=read();
		vis[x]=min(x,vis[x]);
		for (int j=0;j<=512;j++){
			if(vis[(j^x)]!=1e9&&vis[(j^x)]<=x&&(j^x)<=512){//如果当先的j^x的值比x小，并且(j^x)比512小，那么就更新
				vis[j]=min(vis[j],x);
			}
		}
	}
	for (int i=0;i<=512;i++){
		if(vis[i]!=1e9){
			ans++;
		}
	}
	cout<<ans<<endl;
	for (int i=0;i<=512;i++){
		if(vis[i]!=1e9){
			printf("%d ",i);
		}
	}
}
```

---

## 作者：xzy090626 (赞：0)

分享一个暴力做法。

以下设值域为 $V=512$，位宽为 $w=32$。

我们直接开 $V$ 个 bitset 来记录每个值为结尾的子序列可能得到异或值。对于每个 $a_i$，暴力枚举 $V$ 个前驱的状态，以及每次 $V$ 的值域进行转移。这样的话复杂度是 $O(nV^2)$，bitset 只能起到优化空间作用，所以不太能过。

于是我们考虑到麻烦的地方在于 $V$ 个前驱啊。于是直接想到把 bitset 放到树状数组上面去，查询的时候就做 $\log V$ 次按位或，复杂度是 $O(\displaystyle {{V\log V}\over w})$；另外修改发现只是改一位，于是复杂度是 $O(\log V)$。$n$ 次的话就是 $O(\displaystyle {{nV\log V}\over w})$。

跑得非常快，差不多 500 ms。如果按位转移的时候利用 `_Find_next()` 函数一般会更快一些。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cmath>
#include<string>
#include<set>
#include<map>
#include<unordered_map>
#include<queue>
#include<assert.h>
#include<bitset>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
using namespace std;
const int N = 1e6 + 7;
bitset<512>f[512];
int s[N],n;
int lowbit(int x){return x&(-x);}
void add(int x,int y){
	for(;x<512;x+=lowbit(x)) f[x][y] = 1;
}
bitset<512>ask(int x){
	bitset<512>res;
	for(;x;x-=lowbit(x)) res |= f[x];
	return res;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	add(1,0);
	for(int i=1;i<=n;++i){
		cin>>s[i];
		bitset<512>tmp = ask(s[i]);
		for(int k=0;k<512;k=tmp._Find_next(k)){
			if(tmp[k]) add(s[i]+1,(k^s[i]));
		}
	}
	f[0] = ask(511);
	cout<<f[0].count()<<'\n';
	for(int i=0;i<512;++i){
		if(f[0][i]) cout<<i<<' ';
	}
	return 0;
}
```

---

## 作者：lfxxx (赞：0)

考虑在值域上 dp。

不妨记录 $dp_{i,j}$ 表示考虑值域 $[0,i]$ 内的数，想要凑出异或和为 $j$ 的子序列，子序列最后一个位置最靠前是哪个位置。

那么 $dp_{i,j}$ 由 $dp_{i-1,j \oplus a_i}$ 更新而来，具体来说记录 $S_v$ 表示所有值为 $v$ 的下标位置，那么就是在 $S_{a_i}$ 找到 $dp_{i-1,j \oplus a_i}$ 的后继更新状态，时间复杂度 $O(n + V^2 \log n)$。

[代码](https://codeforces.com/contest/1582/submission/280516760)

---

## 作者：QWQ_123 (赞：0)

发现 $a$ 的值域很小，那么考虑设 $f_i$ 表示上升子序列异或和为 $i$ 的最大值最小是多少。

那么对于 $f_i$，若 $f_i < a_i$，那么 $f_{i \oplus a_i} = \min\{f_{i \oplus a_i}, a_i\}$。

初始将 $f_0=0$，然后其他的数都设为 $+\infty$ 即可。

---

## 作者：kkxacj (赞：0)

#### 思路

很容易想到设状态为以第 $i$ 个数结尾的递增子序列异或和为 $j$ 是否可行，然后存一下异或和为 $j$ 以最小的数结尾是多少，然后暴力转移就可以了。

**Code**
```cpp
#include<bits/stdc++.h>
using namespace std;
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
const int N = 1e6+10,M = 8210,X = 2300;
int n,a[N],cnt,st[N],f[M+100],v[M+100],v1[M+100],mx;
signed main()
{
	read(n);
	for(int i = 1;i <= n;i++) read(a[i]),mx = max(mx,a[i]);
	f[0] = v[0] = 1;
	v1[0] = 0;
	for(int i = 1;i <= M;i++) v1[i] = 1e5;
	for(int i = 1;i <= n;i++)
	{
		for(int j = 1;j <= M;j++) 
		{
			if((j^a[i]) <= M && v1[j^a[i]] <= a[i]) f[j] = v[j] = 1;
			else f[j] = 0;
		}
		for(int j = 1;j <= M;j++) if(f[j]) v1[j] = min(v1[j],a[i]);
	}
	for(int i = 0;i <= M;i++) if(v[i]) st[++cnt] = i;
	print(cnt),pc('\n');
	for(int i = 1;i <= cnt;i++) print(st[i]),pc(' ');
	flush();
	return 0;
}

```

---

## 作者：__HHX__ (赞：0)

# 思路
容易观察得到，当一个已知序列异或和的结尾越小，可以在后面接的数越多。

所以我们设计状态：$(x, num)$ 表示序列异或和为 $x$，其中结尾最小为 $num$。

因为要选序列，所以选择 $a_i$ 中 $i$ 的拓扑序为 $1$ 到 $n$。

因为异或后有点难处理，我们先猜一个枚举异或和 $x$ 的拓扑序即 $0$ 到 $\max a_i$，大不了加个滚动数组优化。

那我们就可以知道转移为：$(x, num)\rightarrow(x \oplus a_i, a_i)$。

因为我们知道 $(x \oplus a_i) \oplus a_i = x$，所以我们仅需在此互相转移即可。

又因为我们是从 $0$ 到 $n$，在 $x$ 与 $x \oplus a_i$ 这一对中总是最小的先被转移，所以在 $x \oplus a_i < x$ 时无需转移。

时间复杂度为：$O(n \cdot \max a_i)$。

---

## 作者：Yh0326 (赞：0)

水绿。

设 $f_i$ 表示异或和为 $i$ 时，严格上升子序列末尾数的最小值。

我们初始先将 $f$ 赋值为较大数。

如样例1，求得 $f_0 = 0, f_2 = 2, f_4 = 4, f_6 = 4$。

如果 $f_i$ 在 $a$ 的值域中，则说明异或和可以为 $i$。

会发现 $a$ 的值域很小，所以暴力跑即可。

~~~cpp
#include <bits/stdc++.h>
using namespace std;
inline int read()
{
	int s = 0, w = 1;char ch = getchar();
	while(!isdigit(ch)){if(ch == '-'){w = -1;}ch = getchar();}
	while(isdigit(ch)) s = s * 10 + ch - 48, ch = getchar();
	return s * w;
}
int n;
int a[100003];
int f[542];
int main()
{
	n = read();
	for(int i = 1;i <= n;++ i) a[i] = read();
	f[0] = 0;
	for(int i = 1;i <= 512;++ i) f[i] = 513;
	for(int i = 1;i <= n;++ i)
	{
		f[a[i]] = min(f[a[i]], a[i]);
		for(int j = 0;j <= 512;++ j)
		{
			if(f[j] < a[i]) f[a[i] ^ j] = min(f[a[i] ^ j], a[i]);//更新，若可以从异或和为 j 的序列末尾加入 a[i] 并转移
		}
	}
	int ans = 0;
	for(int i = 0;i <= 512;++ i) if(f[i] != 513) ++ ans;
	cout << ans << '\n';
	for(int i = 0;i <= 512;++ i) if(f[i] != 513) cout << i << ' ';
	return 0;
}
~~~

~~刷个社贡~~

---

## 作者：wizardMarshall (赞：0)

## 题意

求所有上升子序列的异或值。

## 思路

这题是简单版，值域为 $n \le 10 ^ 5$，$a_i \le 500$。如果暴力枚举前面每一个元素，复杂度为 $O(n^2)$，无法通过此题。

但是 $a$ 的值域非常小，所以我们考虑建一个桶，桶的下标对应得到的异或值。遍历每个元素时，只要枚举桶的范围 $2^{\lceil \log_2 500 \rceil}=512$ 即可。

但是题面中还有一个要求，是**上升子序列**。因此，桶数组不仅仅是 $01$ 数组，还要存储值。这个值就是上一个元素的值。如果上一个值小于当前值，则可以接上。

总结：桶数组的定义就是，当前异或和为 $i$ 时，结尾元素的最小值。

初始桶数组全为无穷大，只有空子序列为 $0$。

## 代码

为防止越界，枚举范围开到了 $1000$。


```c++

#include <bits/stdc++.h>
using namespace std;
int a[100005];
int ans[1005];//表示当前子序列的异或和为i时，结尾元素最小（这样才方便接上）
signed main() {
	memset(ans, 127, sizeof(ans));//初始全无穷大
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	ans[0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= 1000; j++) {
			if (ans[j] < a[i]) {
				ans[j ^ a[i]] = min(ans[j ^ a[i]], a[i]);//更新桶数组
			}
		}
	}
	set <int> sum;
	for (int i = 0; i <= 1000; i++) {
		if (ans[i] < 1e9) {//即存在子序列异或和为i（不为无穷大）
			sum.insert(i);
		}
	}cout << sum.size() << endl;
	for (auto i : sum) {
		cout << i << ' ';
	}
	return 0;
}

```

---

