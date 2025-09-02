# Meta-set

## 题目描述

### 题目翻译
你有一副牌，每张牌包含$k$个特征，每个特征等于集合 $\{0，1，2\}$ 中的一个值。显然，共有$3^k$
不同的情况。
 
定义一个三张牌为好的，当且仅当：对于同一位上的特征，要么**相同**，要么**两两不同**。如果**三张牌**所有$k$对特征都是好的，则称为一个集合。

如果一组**五张牌**中有严格意义上的**一个以上**的集合，则称为元组。在给定的$n$个不同的牌中，有多少个元组？

## 样例 #1

### 输入

```
8 4
0 0 0 0
0 0 0 1
0 0 0 2
0 0 1 0
0 0 2 0
0 1 0 0
1 0 0 0
2 2 0 0```

### 输出

```
1```

## 样例 #2

### 输入

```
7 4
0 0 0 0
0 0 0 1
0 0 0 2
0 0 1 0
0 0 2 0
0 1 0 0
0 2 0 0```

### 输出

```
3```

## 样例 #3

### 输入

```
9 2
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2```

### 输出

```
54```

## 样例 #4

### 输入

```
20 4
0 2 0 0
0 2 2 2
0 2 2 1
0 2 0 1
1 2 2 0
1 2 1 0
1 2 2 1
1 2 0 1
1 1 2 2
1 1 0 2
1 1 2 1
1 1 1 1
2 1 2 0
2 1 1 2
2 1 2 1
2 1 1 1
0 1 1 2
0 0 1 0
2 2 0 0
2 0 0 2```

### 输出

```
0```

# 题解

## 作者：隐仞Mrsu (赞：4)

# 读一读题目
给出 $n$ 个 $k$ 长的三进制串，求出合法五元集的个数。

五元集合法的条件是，能从中提取出合法三元集，数量**超过** $1$。

而三元集合法的条件是：对于三个串的第 $i$ 位，其数字要么**都相等**，要么分别为 $0,1,2$ **不重复**的数。

## 举一点点例子

```
0 0 1 1
0 2 0 1
0 1 2 1
```
比如，对于这组由长度为 $4$ 的三进制串组成的三元集，从最左边那位看起，其数字为 $0,0,0$，皆相等，满足第一个条件，合法；对于从左数起的第二位，其数字为 $0,2,1$，三个数字不相等，不符合第一个条件，但是它们不重复，满足第二个条件，合法。后两位同理，亦满足条件。故该三元集合法。

而对于以下的五元集：
```
0 0 0 0 // a串
0 0 0 1 // b串
0 0 0 2 // c串
0 0 1 0 // d串
0 0 2 0 // e串
```
由上面的规则可知，$a,b,c$ 串组成的三元集合法，$a,d,e$ 串组成的三元集也合法。故该五元集能提取出两个合法三元集，所以整个五元集合法。

# 想一想思路

要求出合法五元集的个数，我们首先得求出合法三元集的个数。

## 求合法三元集

用一个两重循环进行遍历，循环变量 $i,j$ 表示当前想要求出的三元集中包含了第 $i$ 和第 $j$ 个三进制串。

为了保证三元集满足条件，可以通过已知的 $i,j$ 串得到第三个串，比如：

```
0 0 1 // 第i串
0 2 0 // 第j串
```
我们从左向右逐位求解，第一位为 $0,0$，则第三个串的第一位必须为 $0$；第二位为 $0,2$，则第三个串的第二位必须为 $1$；第三位为 $1,0$，则第三个串的第三位为 $2$。

故三元集里的第三个串为 $0 1 2$。

同时可以发现，已知两个串的前提下，三元集里的另一个串是唯一的。

于是，我们利用 $map$ 数组判断推导出的第三个串是否存在，即可进行统计，用 $sum$ 数组记录含有 $i$ 串的合法三元集的个数。

## 求合法五元集

用一个循环遍历每一个三进制串。循环变量 $i$ 表示当前所求的五元集中含有第 $i$ 串。

为了使该五元集合法，五元集中必须能提取出至少两个的合法三元集。我们之前已经求出 $sum$ 数组，记录含有 $i$ 串的合法三元集的个数。于是当前第 $i$ 串对结果的贡献就是 $C_{sum_i}^{2}$。

# 代码
```cpp
#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int N = 1e3+4;
LL n,k,a[N][25],w[N],res,sum[N];
map <LL,int> mp;
  
LL make(LL p,LL q){
	LL r=0;
	for(LL j=1,t=1;j<=k;j++,t*=3){
		if(a[p][j]==a[q][j]){
			r+=a[p][j]*t;
		}
		else{
			r+=(3-a[p][j]-a[q][j])*t;
		}
	}
	return r;
}
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(LL i=1;i<=n;i++){
		for(LL j=1,t=1;j<=k;j++,t*=3){
			cin>>a[i][j];
			w[i]+=a[i][j]*t; //记录每个三进制串对应的十进制数
		}
		mp[w[i]]=i; //记录该串对应的序号
	}
    
   //求合法三元集的个数
	for(LL i=1;i<=n-2;i++){
		for(LL j=i+1;j<n;j++){ //从i的下个串开始遍历，防止重复
			LL num=make(i,j); //求i串和j串对应的第三个串
			if(mp[num]>j){ 
            //该串的序号应该大于j，从而保证不重复判断
				sum[i]++;
				sum[j]++;
				sum[mp[num]]++;
			}
		}
	}
    //求合法五元集的个数，统计结果
	for(LL i=1;i<=n;i++){
		res+=sum[i]*(sum[i]-1)/2; 
	}
	cout<<res<<'\n';
}
```



---

## 作者：zuytong (赞：2)

[传送门](https://www.luogu.com.cn/problem/CF1735D)


------------
## 题意：

你有 $n$ 个长度为 $k$ 的序列，仅由 $0,1,2$ 组成。

我们定义一个三元组序列为“好”的，当且仅当：

- 对于同一位上的元素，要么相同，要么两两不同。

例如 $(0,0,2)(0,1,2)(0,2,2)$ 是“好”的，而 $(0,0,2)(0,1,2)(1,2,2)$ 不是“好”的，因为第一位上既有相同元素（$0,0$），也有不同元素 $(0,1)$。

现在要选出一个五元组，要求其中包含**大于**一个“好”的三元组。

问这样的五元组有多少个。$n \le 1000,~k \le 20$


------------
## 思路：

首先，符合要求的五元组，都是恰好包含 $2$ 个“好”的三元组；而且**有且仅有**一个序列同时出现在这两个三元组中。

- 至少有一个：显然，如果没有，那么至少需要 $6$ 个序列。

- 恰好有一个：显然，如果我们选出了两个序列，根据它们每一位上的相等关系，我们能够**确定**第三个序列；因此不存在任何两个“好”的三元组，有两个或以上的序列相同。

- 恰好有两个“好”的三元组：根据上面的证明，因为只有一个**共用序列**，那么五元组就只能是有两个“好”的三元组。

问题就转化为统计“好”的三元组的数量（设为 $tot$），最终答案就是 $\begin{pmatrix} tot \\ 2 \end{pmatrix}$.

根据两个序列能够确定第三个序列，而且 $k\le 20$，我们考虑将每个序列转化为三进制数，用一个 map 存起来。

然后枚举任意两个序列，在 map 中查询是否有第三个序列即可。

时间复杂度为 $O(kn^2\log n)$ （放心，$4s$ 能过）。


------------
## 代码

```cpp
#include<bits/stdc++.h>
#define LL long long
#define FOR(i, x, y) for(int i = (x); i <= (y); i++)
#define ROF(i, x, y) for(int i = (x); i >= (y); i--)
#define PFOR(i, x) for(int i = he[x]; i; i = r[i].nxt)
using namespace std;
inline int rd()
{
    int sign = 1, re = 0; char c = getchar();
    while(!isdigit(c)){if(c == '-') sign = -1; c = getchar();}
    while(isdigit(c)){re = re * 10 + (c - '0'); c = getchar();}
    return sign * re;
}
int n, m;
struct Node
{
	int a[25]; LL sum;
}p[1005];
LL ans, cnt[1005];
map<LL, int> f;
signed main()
{
    n = rd(), m = rd();
    FOR(i, 1, n)
    {
    	LL h = 1;
    	FOR(j, 1, m)
	    {
	    	p[i].a[j] = rd(), p[i].sum += h * p[i].a[j];
	    	h *= 3;
		}
		f[p[i].sum] = i;
	}
    FOR(i, 1, n) FOR(j, i + 1, n)
    {
    	LL t = 0, h = 1;
    	FOR(k, 1, m)
    	{
    		if(p[i].a[k] == p[j].a[k]) t += h * p[i].a[k];
    		else t += h * (3 - p[i].a[k] - p[j].a[k]);
    		h *= 3;
		}
		int id = f[t];
		if(id > j) cnt[i]++, cnt[j]++, cnt[id]++;
	}
	FOR(i, 1, n)
		ans += cnt[i] * (cnt[i] - 1) / 2ll;
	printf("%lld", ans);
    return 0;
}
```


---

## 作者：luo_shen (赞：1)

### 题意描述
给定 $n$ 个长度为 $m$ 的且两两不同的序列 $a_i$。 

定义一个三元集 $(i,j,k)$ 为合法三元集当且仅当对于任何一个位置 $p$，要么 $a_{i,p}=a_{j,p}=a_{k,p}$，要么 $a_{i,p}\not= a_{j,p}\ \operatorname{and}\ a_{j,p}\not= a_{k,p}\ \operatorname{and}\ a_{i,p}\not= a_{k,p}$。

定义一个五元集为合法五元集当且仅当其中存在至少两个不同的合法三元集。

问有多少个合法五元集。

### 题目分析
证明：一个合法五元集必然是由两个只有一个元素重复的合法三元集组成
>若两个合法三元集没有重复元素：总元素数量为 $6$，不为五元集。  
>若两个合法三元集有两个或三个重复元素：根据合法三元集的定义可知，若已知两个元素，可以通过这两个元素的每一位的同或异推得第三个元素每一位的值，此时两个合法三元集为同一三元集，不符合题目  

因此可以通过控制一个元素相同来寻找这两个合法三元集。

因为 $m$ 很小，用一个二元组 $(i,j)$，记录一个元素 $y$ 与被控制的这个元素 $x$ 的每一位同异情况。$i$ 的第 $p$ 位为 $1$ 表示两个元素第 $p$ 位相同，反之不同；$j$ 的第 $p$ 位为 $1$ 表示 $y_p\equiv x_p+1 \pmod 3$，反之表示 $y_p\equiv x_p+2 \pmod 3$。所以如果存在二元组 $(i,i\oplus j \oplus (2^m-1))$，则为匹配。

### Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
    int s=0,f=1;
    char ch=getchar();
    while(ch>'9'||ch<'0'){
        if(ch=='-'){
            f=-1;
        }
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        s=s*10+(ch-'0');
        ch=getchar();
    }
    return s*f;
}
struct node{
    int x,y;
    node(int _x=0,int _y=0){
        x=_x,y=_y;
    }
    bool operator <(const node &rhs)const{
        return x==rhs.x?y<rhs.y:x<rhs.x;
    }
}ans[2000];
int n,m,a[2000][100],_ans;
signed main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            a[i][j]=read();
        }
    }
    for(int i=1;i<=n;i++){
        set<node>s;
        for(int j=1;j<=n;j++){
            ans[j].x=0,ans[j].y=0;
            if(i==j)continue;
            for(int k=1;k<=m;k++){
                if(a[i][k]==a[j][k]){//统计a[i][k]=a[j][k]
                    ans[j].x|=(1<<(k-1));
                }
                if(a[i][k]==0&&a[j][k]==1){
                    ans[j].y|=(1<<(k-1));
                }
                if(a[i][k]==1&&a[j][k]==2){
                    ans[j].y|=(1<<(k-1));
                }
                if(a[i][k]==2&&a[j][k]==0){
                    ans[j].y|=(1<<(k-1));
                }//统计(a[i][k]+1==a[j][k])
            }
            s.insert(ans[j]);//放入s中统计
        }
        int cnt=0;
        for(int j=1;j<=n;j++){
            if(i==j)continue;
            cnt+=s.count(node(ans[j].x,ans[j].x^ans[j].y^((1<<m)-1)));//寻找匹配组
        }
        _ans+=(cnt/2)*(cnt/2-1)/2;//因为有重复统计，所以要cnt除以2后再统计答案
    }
    printf("%d\n",_ans);
    return 0;
}
```

---

## 作者：whhsteven (赞：1)

赛时缺个脑子痛失 D 题，赛后看了一会儿莉可丽丝等 System Test 完了之后补了这道题。

&nbsp;

下面称题中的 set 为「合法三元集」，meta-set 为「合法五元集」。

易见，一个合法三元集可以被其中任意两个元素唯一确定。由此我们可以得到以下三点：

1. 枚举第一个和第二个元素，找第三个元素，就可以遍历所有的合法三元集，从而统计每一个元素在多少个合法三元集里；

2. 对于一个元素所在的所有不同合法三元集，其两两交集均只含这一个元素；

3. 一个合法五元集的任意两个不同合法三元子集，其交集大小必然不超过 $1$。

由上面第 3 条，又显然一个五元集的任意两个不同三元子集必然有交，我们可以知道每一个合法五元集里的任意两个不同合法三元子集交集大小为 $1$。

进一步地，在一个合法五元集里划出两个交集大小为 $1$ 的合法三元子集，易见再在这个五元集里任意划出一个三元子集，其与现有这两个合法三元子集的交集大小不可能都为 $1$，从而可知一个合法五元集有且只有两个合法三元子集。

这样，我们枚举作为交集元素的那个元素，统计以其作为交集元素的所有合法五元集数量，即可得到答案。

时间复杂度 $O(kn^2)$ 或 $O(kn^2\log n)$，取决于枚举前两个元素找第三个元素时使用的数据结构带不带 $\log$。

&nbsp;

参考实现：

```cpp
#include<bits/stdc++.h>

using namespace std;

int n, k, a[1007][22], cnt[1007];
long long s, ans;
map<long long, int> ap;

inline long long dmn(int x, int y)
{
	long long s = 0;
	for(int i = 1; i <= k; i++)
		s = s * 3 + ((a[x][i] == a[y][i]) ? a[x][i] : (3 - a[x][i] - a[y][i]));
	return s;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(nullptr);
	
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= k; j++) cin >> a[i][j], s = s * 3 + a[i][j];
		ap[s] = i, s = 0;
	}
	
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) if(i != j)
		cnt[i] += (ap.find(s = dmn(i, j)) != ap.end() && ap[s] != i && ap[s] > j);
	for(int i = 1; i <= n; i++) if(cnt[i]) ans += 1ll * cnt[i] * (cnt[i] - 1) / 2;
	
	cout << ans;
	
	return 0;
}
```

---

## 作者：Hisaishi_Kanade (赞：1)

首先给出一个显然成立的命题：

+ 对于一个合法三元组，我们显然可以由其中两个推出唯一对应的第三个。

 
简单证明：

设已经知道了 $x,y$，求第三个值 $z$。

假设 $z$ 不唯一，即 $z_1,z_2$ 都满足条件。

而对于每一位，$x,y$ 的这一位如果相同，$z$ 这一位也就有且仅有和 $x,y$ 这一位相同的值满足条件；如果 $x,y$ 的这一位不同，$z$ 在这一位也有且仅有一个数满足条件。

显然 $z_1=z_2$，即 $z$ 存在且唯一。
- - -

为了统计的方便，我们钦定 $x,y,z$ 的编号上升。

那么，我们枚举原序列中两个值 $x,y$，求出需要配对的第三个值 $z$。

如果存在，求出 $z$ 在原序列的编号，$x,y,z$ 的编号的计数器加一。

我们发现，合法五元组可以理解为两个只有一个值相同的合法三元组构成的（如果两个值相同那这两个合法三元组就可能是同一个）。

对于一个下标 $p$，它的计数器 $c_p$ 就表示有多少个合法三元组包含 $p$。

由于上面的理解，我们可以得到，包含 $p$ 的合法五元组个数就相当于 $c_p$ 个球里选两个，即 $\dfrac {c_p\times (c_p-1)} 2$ 个。

至此，做法就讲完了。

- - -

最后指正一下，有一些题解认为这种做法是 $kn^2\log n$ 的，但是注意到的是，`std::map` 使用 `.operator []` 时，即使没有找到也会创建空节点。这样，红黑树中的节点数就是 $n^2$ 量级的。

也就是这些老哥的做法退化到 $k n^2\log n^2$ 了，虽然也能过，但是测试结果表明慢很多。

遗憾的是，题解区给出代码的题解中只有 [whhsteven 的题解](https://www.luogu.com.cn/blog/118109/cf1735d-solution)注意到了这个问题。

最上方是笔者的代码，下面五次提交依次是 `隐仞Mrsu, zuytong, whhsteven, luo_shen, OccDreamer` 五篇题解的代码。

![](https://cdn.luogu.com.cn/upload/image_hosting/pmz1lzwj.png)

即使知道评测姬有波动，但是明显复杂度是有差异的。

```cpp 
#include <map>
#define rep(i,l,r) for(i=l;i<=r;++i)
#include <stdio.h>
const int N=100005;
long long pre[N];
long long ret;
int x,k;
int n,i,j;
std::map<long long,int> rid;
int cnt[N];
inline int find(long long x,long long y)
{
	long long p=0,base=1;
	int t=k;
	while(t--)
	{
		if(x%3==y%3)
			p+=base*(x%3);
		else
			p+=base*(3-x%3-y%3);
		base*=3;
		x/=3;y/=3;
	}
//	printf("%d\n",p);
	if(rid.count(p) && rid[p]>j)
	{
		++cnt[i];
		++cnt[j];
		++cnt[rid[p]];
	}
	return p;
}
int main()
{
	long long mid;
	scanf("%d %d",&n,&k);
	rep(i,1,n)
	{
		mid=0;
		rep(j,1,k)
		{
			scanf("%d",&x);
			mid=mid*3+x;
		}
		pre[i]=mid;
		rid[mid]=i;
	}
	rep(i,1,n)
		rep(j,i+1,n)
			find(pre[i],pre[j]);
	rep(i,1,n)
	{
		ret+=cnt[i]*(cnt[i]-1)/2;
	}
	printf("%lld",ret);
	return 0;
}
```

当然哈希表能 $O(kn^2)$，这里不多赘述。


- - -

不过，这个题暴力跑不满而且常数小，和笔者的做法甚至在效率上并无很大差异（

---

## 作者：Jorisy (赞：0)

首先对于三元组 $(i,j,k)$，如果确定了 $i,j$，$k$ 是被唯一确定的。

又考虑到五元组内必然有至少一个数贡献到了五元组内的两个三元组。

于是我们可以枚举所有存在的合法三元组 $(i,j,k)$，记 $c_i$ 表示 $i$ 所在合法三元组数量，则 $i$ 对答案的贡献为 $C_{c_i}^2$。
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

map<ll,int>mp;
int n,k;
ll a[1005][25],h[1005],c[1005];

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
    cin>>n>>k;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=k;j++)
        {
            cin>>a[i][j];
            h[i]=h[i]*3+a[i][j];
        }
        mp[h[i]]=i;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
            ll t=0;
            for(int l=1;l<=k;l++) t=t*3+(a[i][l]==a[j][l]?a[i][l]:3-a[i][l]-a[j][l]);
            if(mp[t]<j) continue;
            c[mp[h[i]]]++;
            c[mp[h[j]]]++;
            c[mp[t]]++;
        }
    }
    ll ans=0;
    for(int i=1;i<=n;i++) ans+=c[i]*(c[i]-1)/2;
    cout<<ans;
	return 0;
}
```

---

## 作者：船酱魔王 (赞：0)

# CF1735D Meta-set 题解

## 题意回顾

有 $ n $ 个**两两不同**的长度为 $ k $ 的数组，元素值在 $ \{0,1,2\} $ 中。

定义三个数组的集合是“好”的，当且仅当每一位置上元素值均相等或均不同。

定义五个数组的集合是“非常好”的，当且仅当存在至少两个“好”的子集。

求有多少个“非常好”的由五个数组组成的集合。

$ 1 \le n \le 10^3 $，$ 1 \le k \le 20 $。

## 分析

因为数组两两不同，所以如果确定了两个数组是啥，剩下一个数组可以唯一确定以使得形成“好”的集合。

而如果两个“好”的集合不存在公共数组的话，不可能形成“非常好”的集合。

因此，“非常好”的集合中只能包含两个有一个公共数组的“好”集合。

枚举两个数组，判断出第三个数组是否存在，若存在则那个数组的计数器加一。

考虑哪个数组作为公共数组，设计数器值为 $ x $，答案增加 $ C^{2}_{x} $，代表选出任意两个可以与它组成“好”的集合的数组的方案数。

注意开 ```long long```。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
using namespace std;
const int N = 1005;
const int K = 23;
int n, k;
int a[N][K];
long long val[N];
set<long long> se;
map<long long, int> mp;
int b[N]; 
long long C2(int x) {
	return (long long)x * (x - 1) / 2;
}
int main() {
	cin >> n >> k;
	for(int i = 1; i <= n; i++) {
		val[i] = 0;
		for(int j = 1; j <= k; j++) {
			cin >> a[i][j];
			val[i] = val[i] * 3 + a[i][j];
		}
		se.insert(val[i]); 
	}
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			for(int l = 1; l <= k; l++) {
				if(a[i][l] != a[j][l]) {
					b[l] = 3 - a[i][l] - a[j][l];
				} else {
					b[l] = a[i][l];
				}
			}
			long long tmp = 0;
			for(int l = 1; l <= k; l++) {
				tmp *= 3;
				tmp += b[l];
			}
			mp[tmp]++;
		}
	}
	long long ans = 0;
	for(map<long long, int>::iterator it = mp.begin(); it != mp.end(); it++) {
		if(se.find(it -> first) != se.end() && it -> second >= 2) {
			ans += C2(it -> second);
		}
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：lyhqwq (赞：0)

# Solution
因为对于已经确定的两副牌，对应的第三副牌是已经确定的（请读者自己稍加思考）。

对于一个五元组，一定是由两个三元组组成，且这两个三元组有且仅有一副牌像相同，所以我们可以记 $sum_i$，为包含第 $i$ 副牌的三元组个数，只要从中选出两个，就可以组成一个合法的五元组，所以答案为 $\binom{sum_i}{2}$。

对于 $sum$ 的求法，我们可以枚举一个三元组中的其中两副牌，第三副牌可以用 $O(k)$ 的时间求出，这样就可以在 $O(n^2k)$ 的时间内求出 $sum$ 数组。

总的时间复杂度为 $O(n^2k+n)$，可以通过本题。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1005;
int n,k;
int a[N][25];
int w[N];
int sum[N];
map<int,int> mp;
int calc(int x,int y){
	int t=0;
	for(int i=1;i<=k;i++){
		t=t*3+(a[x][i]==a[y][i]?a[x][i]:3-a[x][i]-a[y][i]);
	}
	return t;
}
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	scanf("%lld%lld",&n,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=k;j++){
			scanf("%lld",&a[i][j]);
			w[i]=w[i]*3+a[i][j];
		}
		mp[w[i]]=i;
	}
	for(int i=1;i<=n-2;i++){
		for(int j=i+1;j<=n-1;j++){
			int x=calc(i,j);
			if(mp[x]>j){
				sum[i]++;
				sum[j]++;
				sum[mp[x]]++;
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans+=sum[i]*(sum[i]-1)/2;
	}
	printf("%lld\n",ans);
	return 0;
}

```


---

## 作者：封禁用户 (赞：0)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1735D)

[CF](https://codeforces.com/contest/1735/problem/D)

### 分析

这一题乍一看无从下手，我们先要推到一些结论：

+ 给出两个串，存在且仅存在一个串能和这两个串组成一个合法三元集。

证明：遍历串的每一位，当这两个串的这一位相等，构造第三个串的这一位也是这个数；否则，就是在集合 $\{0,1,2\}$ 中不与这两个数相等的另一个数。所以一定可以构造出一个串，而原题又说：所有的卡片都是不同的，故原命题得证。

+ 在一个合法五元集中，存在且仅存在两个合法三元集。

根据题意，我们先构造出两个合法三元集，令其为 $\{1,2,3\}$ 和 $\{1,4,5\}$，如果还有一个合法三元集，则三个串的来源一定来自一个合法三元集中的两个串和另一个合法三元集中的一个串，但根据前面的结论：
给出两个串，存在且仅存在一个串能和这两个串组成一个合法三元集。这两个串一定只能和原合法三元集中的串构成合法三元集，故原命题得证。

所以，我们发现，一个合法五元集中的两个合法三元集必定有一个重复数字，我们以这个数字来计算贡献，则方案数为：$\sum \frac{s_i \times (s_i-1)}{2}$，其中 $s_i$ 表示第 $i$ 个串可以形成的合法三元集的数量。

$s_i$ 的求法也不难，枚举两个串，根据第一个结论，可以得到唯一的第三个串，判断这个串是否在原数组中存在。如果存在，**并且三个下标满足一定相对顺序**，则更新 $s$ 数组。

已经讲得很详细了，代码就不附上了。


---

## 作者：Mashiroqwq (赞：0)

## 题目大意

给定 $n$ 张卡牌，每张卡牌有 $k$ 个属性，第 $i$ 张卡牌的第 $j$ 个属性为 $c_{i,j}$。

一个由 $3$ 张卡牌 $x,y,z$ 组成的集合被称作好的，当且仅当对于 $1 \leq i \leq k$ 均有 $c_{x,i}=c_{y,i}=c_{z,i}$ 或者 $c_{x,i},c_{y,i},c_{z,i}$ 两两不相等。

一个 meta-set 由五张卡牌组成，且其中至少存在两个大小为 $3$ 的子集是好的。求 meta-set 数量。

**给出的卡牌两两不同。**

数据范围为 $n \leq 1000$，$k \leq 20$，$0 \leq c_{i,j} \leq 2$。

## 观察

1. 注意到 $c$ 只有 $0,1,2$ 两个取值，所以一个好的集合要么对应位相等，要么分别为 $0,1,2$。
2. 一个 meta-set 应当恰好有 $2$ 个大小为 $3$ 的子集是好的，证明比较简单。
3. 必然有一张卡牌存在于两个好的集合当中。
4. 一个 meta-set 如果由 $(q,w,e,r,t)$ 组成，且 $q$ 包含于两个 meta-set，那么比如满足 $(q,w,e)$ 和 $(q,r,t)$ 是好的集合。
5. 一张卡牌可以用 $\sum _{i=1}^k c_{x,i} \times 3^{i-1}$ 表示。

## 求解

通过观察得到的 $3$ 性质，我们枚举这一张卡牌是 $x$，根据 $4$ 现在问题就变为统计有多少个好的集合包含了 $x$，记为 $f_x$。

因为 $n$ 很小，我们直接枚举一个好的集合当中的另一张卡牌，我们可以直接推出另一张卡牌是什么，对于每一张卡牌我们用一个数来表示丢进 `map` 中计数就行了，时间复杂度 $O(n^2 \log n)$。

```cpp
#include<bits/stdc++.h>

#define int long long

#define vc vector
#define db double
#define fi first
#define se second
#define ll long long
#define mk make_pair
#define pb push_back
#define RI register int
#define PI pair<int,int>
#define ull unsigned long long
#define err cerr << "   -_-   " << endl
#define debug cerr << " ------------------- " << endl

#define NO puts("No")
#define YES puts("Yes")

using namespace std;

namespace IO{
	inline int read(){
		RI X=0, W=0;register char ch=getchar();
		while(!isdigit(ch)) W|=ch=='-', ch=getchar();
		while(isdigit(ch)) X=(X<<1)+(X<<3)+(ch^48), ch=getchar();
		return W?-X:X;
	}
	inline void write(int x){
		if(x<0) x=-x, putchar('-');
		if(x>9) write(x/10);
		putchar(x%10+'0');
	}
	inline void sprint(int x){write(x), putchar(32);}
	inline void eprint(int x){write(x), putchar(10);}
}using namespace IO;

const int MAXN = 1e3+5;
const int mod1 = 998244353;
const int mod2 = 1e9+7;
const int inf = 1e12;

int n, k, m[MAXN][25], v[25];

map<int,int> T;

inline void solve(){
	cin >> n >> k;
	int c=0, powc;
	for(int i=1;i<=n;++i){
		powc=1;c=0;
		for(int j=1;j<=k;++j){
			m[i][j]=read();
			c=c+powc*m[i][j];
			powc=powc*3;
		}
		T[c]++;
	}
	ll ans=0;
	int tot=0;
	for(int i=1;i<=n;++i){
		tot=0;
		for(int j=1;j<=n;++j){
			if(i==j) continue;
			c=0, powc=1;
			for(int p=1;p<=k;++p){
				if(m[i][p]==m[j][p]) v[p]=m[i][p];
				else v[p]=3-m[i][p]-m[j][p];
				c+=powc*v[p], powc*=3;
			}
			tot+=T[c];
		}
		tot/=2;
		if(tot==1) continue;
		ans=ans+tot*(tot-1)/2;
	}
	cout << ans;
	return ;
}

signed main(){
	solve();
	return 0;
}
```

---

