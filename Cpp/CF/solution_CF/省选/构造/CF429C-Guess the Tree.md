# Guess the Tree

## 题目描述

## 题面描述
你被要求构建这样一棵有根树：
- 此树除叶节点外的节点都至少有两个儿子。
- $i$ 号节点子树大小为 $c_i$ 。

## 样例 #1

### 输入

```
4
1 1 1 4
```

### 输出

```
YES```

## 样例 #2

### 输入

```
5
1 1 5 2 1
```

### 输出

```
NO```

# 题解

## 作者：George1123 (赞：6)


更木棒的阅读体验 $\to$ [`George1123`](https://www.cnblogs.com/George1123/p/13864073.html)

---

## 题面

> [CF429C Guess the Tree](https://www.luogu.com.cn/problem/CF429C)

> 给一个长度为 $n$ 的数组 $a_i$，问是否有一棵树，每个节点要么是叶子要么至少有两个儿子，而且 $i$ 号点的子树大小是 $a_i$。

> 数据范围：$1\le n\le 24$。

---

## 题解

发现 $n$ 很小，想到可以状压。

设叶子节点有 $ln$ 个，所以中间节点有 $mn=n-ln$ 个。

由于“每个节点要么是叶子要么至少有两个儿子”，所以 $ln\ge\lceil\frac n2\rceil$，$mn\le n-\lceil\frac n2\rceil \le 11$。

所以可以先特判 $2mn\ge n$ 的情况答案为 `NO`。

然后剩下的可以 `dp`，**设 $f_{t,s,i}$：**

$t$ 表示是一棵森林还是一个子树（为了对付“每个节点要么是叶子要么至少有两个儿子”，如果是子树 $t=0$，否则 $t=1$）。

$s$ 表示包含的中间节点集合，$s< 2^{mn}\le 2048$。

$i$ 表示包含的叶子节点个树，因为叶子节点都是一样的，所以这样可以优化状压。

值表示是否存在这样的森林，如果存在 $=1$，否则 $=0$。

**考虑怎么转移：**

1. 一棵森林（子树）和另一棵森林（子树）合并成新的森林。

2. 一棵森林上面加一个 $a=$ 森林大小 $+1$ 的节点成为一棵子树（怎么求一棵森林的大小？其实就是 ${\rm popcount}(s)+i$ 啦）。

然后就剩初始化的问题了，因为 $i$ 这维就像一个背包，而且因为 $s$ 这一维保证不会有重点，所以可以在 `dp` 中用无限背包的方式，这样就只需要初始化 $f_{0,0,1}=1$ 了。

**时间复杂度 $\Theta(ln^2 3^{mn})$**，细节看代码。

---

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

//Start
typedef long long ll;
typedef double db;
#define mp(a,b) make_pair((a),(b))
#define x first
#define y second
#define bg begin()
#define ed end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define R(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define L(i,a,b) for(int i=(b)-1,i##E=(a)-1;i>i##E;i--)
const int iinf=0x3f3f3f3f;
const ll linf=0x3f3f3f3f3f3f3f3f;

//Data
const int N=24,mN=11;
int n,sn,ln,mn,a[N],b[1<<mN];
int f[2][1<<mN][N+1]; // 森林还是子树，中间节点集，叶子节点数
bool get(int s,int i){ // 返回 f[1][s][i] 的值
    for(int su=s;su;su=s&(su-1))if(!(su&(s^su)))R(j,0,i+1)
        if((f[0][su][j]||f[1][su][j])&&(f[0][s^su][i-j]||f[1][s^su][i-j])) return true;
    R(j,0,i+1)if((f[0][0][j]||f[1][0][j])&&(f[0][s][i-j]||f[1][s][i-j])) return true; // 因为 su!=0，补上循环中缺少的 su=0
    return false;
}

//Main
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0),cout.tie(0);
    cin>>n; R(i,0,n) cin>>a[i]; sort(a,a+n,greater<int>());
    R(i,0,n)if(a[i]>1) mn++; ln=n-mn,sn=1<<mn,sort(a,a+mn); 
    if(mn*2>=n) cout<<"NO\n",exit(0);
    R(i,1,sn) b[i]=b[i>>1]+(i&1);
    f[0][0][1]=true;
    R(s,0,sn)R(i,0,ln+1)if(get(s,i)){
        f[1][s][i]=true;
        R(t,0,mn)if(!(s&(1<<t))&&a[t]==b[s]+i+1) // 加新的 a= 森林大小+1 的节点形成子树
            f[0][s^(1<<t)][i]=true;
    }
    if(f[0][sn-1][ln]) cout<<"YES\n";
    else cout<<"NO\n";
    return 0;
}
```

---

**祝大家学习愉快！**

---

## 作者：daniEl_lElE (赞：3)

不难发现 $c_i=1$ 一定是叶子，于是可以忽略。

由于要求的树每个非叶子结点必须至少有 $2$ 个儿子，故 $c_i=1$ 的位置至少占一半（可以树生长的角度思考，每次要么在一个叶子下面接 $2$ 个叶子，要么在任意一个其他节点下接 $1$ 个叶子，归纳可证至少有一半）。

于是 $c_i>1$ 只有 $\frac{n}{2}$ 个。考虑 $dp_{S}$ 表示 $S$ 集合是否可以组成一棵完整的树，$f_{S,i}$ 表示 $S$ 集合是否可以组成一个大小为 $i$ 的森林。转移可以选择集合中最大的 $c_t$，枚举其余组成的森林/单个子树大小即可。复杂度 $O(3^{\frac{n}{2}}n^2)$。


```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
int dp[4096][30],f[4096][30];
signed main(){
	int n; cin>>n;
	int a[n+1],b[n+1],m=0;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(a[i]!=1) b[++m]=a[i];
		if(a[i]==2){
			cout<<"NO";
			return 0;
		}
	}
	if(n==1&&m==0){
		cout<<"YES";
		return 0; 
	}
	if(m>n/2){
		cout<<"NO";
		return 0;
	}
	for(int i=1;i<=m;i++) dp[1<<(i-1)][b[i]]=1;
	int sta=(1<<m)-1;
	for(int i=1;i<(1<<m);i++){
		int maxv=0,maxp=0;
		for(int j=1;j<=m;j++){
			if((i>>(j-1))&1){
				if(b[j]>maxv) maxv=b[j],maxp=j;
			}
		}
		for(int p=0;p<=b[maxp]-1;p++){
			if(p+1<b[maxp]) f[i][b[maxp]]|=(f[i^(1<<(maxp-1))][p]);
			f[i][b[maxp]]|=(dp[i^(1<<(maxp-1))][p]);
		}
		for(int k=sta^i;k;k=(k-1)&(sta^i)){
			for(int j=0;j<=n;j++){
				for(int l=0;j+l<=n;l++){
					dp[i|k][j+l]|=(f[i][j]|dp[i][j])&(f[k][l]|dp[k][l]);
				}
			}
		}
	}
	if(f[sta][n]||dp[sta][n]) cout<<"YES";
	else cout<<"NO";
	return 0;
} 
```


---

## 作者：zhimao (赞：2)

## 翻译
### 题面描述
你被要求构建这样一棵有根树：
- 此树除叶节点外的节点都至少有两个儿子。
- $i$ 号节点子树大小为 $c_i$ 。
### 输入格式
第一行读入一个正整数 $n (1<=n<=24)$ ，表示树的大小 。

第二行读入 $n$ 个正整数 $c_i$ 表示 $i$ 号节点子树大小为 $c_i$  。

### 输出格式
如果能构建输出 YES ，否则输出 NO 。

## 题解
注意到 $n$ 特别小，考虑状压或暴搜 。

先把 $c$ 数组从大到小排序，则每个节点的父亲只可能排在它的前面。 暴搜每次搜父节点 ， 时间复杂度为 $O(n!)$ ，会 T ，考虑优化。首先注意到在非叶节点（即子树大小大于一的）的父亲确定下来后，叶节点无论是哪个节点的儿子都没关系 。 因此我们有个优化：搜到叶节点后直接设为子树未满的节点的儿子。设此树中叶节点有 $m$ 个 ， 则优化后时间复杂度为 $O((n-m)!)$ 。

接下来就是个神奇的结论了：合法构建出的树中 ， 叶节点的个数不小于一半！证明其实很简单：注意到条件一 ， 我们有：根节点的度数为 0 或大于 1 ， 其他节点的度数为 1 或大于 2  。 当树中除叶节点外的节点都只有两个儿子时 ， 叶节点的个数为 $x$ , 有 $n\times 2-2=a+(n-a)\times3-1$ , $a=\frac{n+3}{2}$ ，大于一半 。当一个节点度数加一 ， 则另一节点度数减一 ， 而叶节点度数不可再减 ， 因此叶节点的数目不减 ， 证毕。

**tip:** 读入时遇到子树大小为 2 的直接输出 NO ！！！

### 代码
由于我不知道输入给出的树是否存在（忽略第一个条件），因此我写了很多判断。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[1000000],bo,b[1000000],t,c[1000000];
bool cmp(int x,int y)
{
	return x>y;
}
void dfs(int x)
{
	if(x>n)
	{
		int bo=0;
		for(int i=1;i<=n;i++) bo+=a[i];
		if(bo) return;
		bo=1;
		for(int i=1;i<=n;i++) if(b[i]==1) bo=0;
		if(!bo) return;
		puts("YES");
		exit(0);
	}
	if(a[x]==1)
	{
		int bo=0;
		for(int i=1;i<x;i++) b[i]+=a[i],bo+=a[i];
		if(bo!=n-x+1) return;
		bo=1;
		for(int i=1;i<=n;i++) if(b[i]==1) bo=0;
		if(!bo) return;
		puts("YES");
		exit(0);
	}
	for(int i=t;i<=c[x];i++)
		if(a[i]>=a[x])
		{
			int tt=t;
			++b[i];
			a[i]-=a[x];
			--a[x];
			if(i==t&&a[i]==0) ++t;
			dfs(x+1);
			++a[x];
			a[i]+=a[x];
			--b[i];
			t=tt;
		}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),bo+=a[i]==2;
	if(bo)
	{
		puts("NO");
		return 0;
	}
	sort(a+1,a+n+1,cmp);
	if(n==1)
	{
		if(a[1]==1) puts("YES"); else puts("NO");
		return 0;
	}
	for(int i=2;i<=n;i++) if(a[i]==a[i-1]) c[i]=c[i-1]; else c[i]=i-1;
	--a[1];
	t=1;
	dfs(2);
	puts("NO");
}
```


---

## 作者：Kketchup (赞：0)

### [CF429C Guess the Tree](https://codeforces.com/problemset/problem/429/C)

- 搜索

- 状压 DP

**Sol:** 本题正解是状压 DP，这里提供一种好写的暴搜做法。首先关注到的是很小的数据范围，所以可以直接往状压或者搜索上面想。手动模拟样例发现，所有叶子节点是固定的，$c_i$ 为 $1$。进一步地，因为每个非叶子节点都要有至少两个儿子，所以合法序列的叶节点数大于等于 $\lfloor\frac{n+1}{2}\rfloor$。

证明：考虑归纳。$n=1$ 时显然成立。假设对于 $n\in[1,k)$ 都满足题设，那么对于 $n=k$，设当前点为 $x$，其中 $c_x=k$。设 $x$ 的儿子分别为 $s_1,s_2,\cdots,s_m$，他们的子树大小分别为 $c_1,c_2,\cdots,c_m$，那么根据题设，这些子树的叶子数量至少为 $\lfloor\frac{c_1+1}{2}\rfloor,\lfloor\frac{c_2+1}{2}\rfloor,\cdots,\lfloor\frac{c_m+1}{2}\rfloor$。则 $x$ 子树内叶子总数至少为 $\lfloor\frac{c_1+c_2+\cdots+c_m+m}{2}\rfloor=\lfloor\frac{n-1+m}{2}\rfloor$。又因为题目中儿子数量至少为 $2$ 的条件，$m\ge 2$，那么 $\lfloor\frac{n-1+m}{2}\rfloor\ge\lfloor\frac{n+1}{2}\rfloor$，所以假设成立。

所以我们可以直接判断，当叶子节点数量不够时无解。又能观察到，叶子节点是没有区别的，因为他们的子树大小都是 $1$，而题目只要求判断有无解。所以我们只需要搜索非叶子节点的父子关系，剩余一定可以满足。

所以直接在搜索过程中用一个栈维护当前搜到的所有点中每个点下面还能挂多少点，再注意一下至少 $2$ 个儿子的限制即可，实测跑得很快。

**Trick:** 发现有解情况叶子数量至少一半的性质，缩小搜索上界，故可以通过。

除了对叶子数量的判断，代码中还加入了几个特判优化，作用可能微乎其微。

- 若出现 $c_i=2$，一定无解，因为这个非叶子节点只有一个儿子。

- 若 $c_i$ 最大值不是 $n$，显然无解。

```cpp
const int N=30;
int n,cnt,a[N];
int s[N],top;
void dfs(int x){
	if(x>cnt){
		cout<<"YES";
		exit(0);
	}
	for(int i=1;i<=top;++i){
		if(s[i]>=a[x]&&(s[i]>a[x]||s[i]!=a[i]-1)){
        //解释下这里，判断 i 下面能不能挂 x，要么 i 已经有儿子，要么挂了 x 以后还能继续挂。
			s[i]-=a[x];
			s[++top]=a[x]-1;
			dfs(x+1);
			s[i]+=a[x];
			top--;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
		if(a[i]==2){
			cout<<"NO";
			return 0;
		}
		cnt+=(a[i]!=1);
	}
	sort(a+1,a+1+n,greater<int>());
	if(a[1]!=n||cnt*2>=n){
		cout<<"NO";
		return 0;
	}
	s[++top]=a[1]-1;
	dfs(2);
	cout<<"NO";
	return 0;
}
```

---

