# Nuclear Fusion

## 题目描述

一道化学题。
你有n个原子，每个原子都有它的“原子序数”（即排在元素周期表中的第几个）。
你可以将任意两个原子合成为一个新的原子（新原子原子序数=两个融合的原子的原子序数之和）。新的原子也可以继续合成。
这个问题的困难在于，它只能将两个原子合成一个新原子，而不允许将一个原子分裂成几个原子。
你的任务是：将已有的n个原子合成为k个希望得到的新原子
新原子将给出

## 说明/提示

原子序数和元素周期表请自行百度（原子序数<=100）
注意：原子的合成不是化学方程式，而只是原子序数相加

第一个例子的反应如下：
![样例说明](C:\Users\a\Desktop\捕获.PNG)

## 样例 #1

### 输入

```
10 3
Mn Co Li Mg C P F Zn Sc K
Sn Pt Y
```

### 输出

```
YES
Mn+C+K-&gt;Sn
Co+Zn+Sc-&gt;Pt
Li+Mg+P+F-&gt;Y
```

## 样例 #2

### 输入

```
2 1
H H
He
```

### 输出

```
YES
H+H-&gt;He
```

## 样例 #3

### 输入

```
2 2
Bk Fm
Cf Es
```

### 输出

```
NO
```

# 题解

## 作者：lx_zjk (赞：3)

~~我好像是$luogu$第一个$A$掉的人 不过 我还是那么菜~~

首先$(1<=k <= n <= 17)$ 想到状态压缩 

首先是预处理吧

通过计算预处理出来$sum$数组 表示当前$state$下选择元素的原子序数之和

如果$sum[state] == b[i]$那么说明当前选的元素可以凑成新的元素 那么如果要转移 那么就枚举 他前面那一位 选过的数肯定不能选 所以我们要枚举$state$的子集

子集枚举
```cpp
for (int t = s; t; t = s & (t - 1)) do something
```

## $code$
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <set>
#include <map>
#include <queue>

using namespace std;

typedef long long ll;

const int INF = 2139062143;

#define DEBUG(x) std::cerr << #x << " = " << x << std::endl

inline ll read() {
    ll f = 1, x = 0;char ch;
    do {ch = getchar();if (ch == '-')f = -1;} while (ch > '9' || ch < '0');
    do {x = x * 10 + ch - '0';ch = getchar();} while (ch >= '0' && ch <= '9');
    return f * x;
} 

const int MAX_S = (1 << 18) + 5;
const int MAX_N = 20 + 5;

string element[110] = {"","H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc","Ti","V","Cr","Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag","Cd","In","Sn","Sb","Te","I","Xe","Cs","Ba","La","Ce","Pr","Nd","Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb","Lu","Hf","Ta","W","Re","Os","Ir","Pt","Au","Hg","Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac","Th","Pa","U","Np","Pu","Am","Cm","Bk","Cf","Es","Fm"};
map < string, int > mp;
string s1[MAX_N], s2[MAX_N]; 
int n, k, a[MAX_N], b[MAX_N], sum[MAX_S], f[MAX_N][MAX_S], pre[MAX_N][MAX_S];

int main() {
	for (int i = 1; i <= 100; i ++ ) mp[element[i]] = i;
	n = read (); k = read ();
	for (int i = 0; i < n; i ++ ) {
		cin >> s1[i];
		a[i] = mp[s1[i]];
	}
	for (int i = 0; i < k; i ++ ) {
		cin >> s2[i];
		b[i] = mp[s2[i]];
	}
//	for (int i = 0; i < n; i ++ ) DEBUG (a[i]);
//	for (int i = 0; i < k; i ++ ) DEBUG (b[i]);
	for (int s = 0; s < (1 << n); s ++ )
		for (int i = 0; i < n; i ++ )
			if (s & (1 << i)) sum[s] += a[i];
//	for (int s = 0; s < (1 << n); s ++ ) DEBUG (sum[s]);
    reverse (s2, s2 + k);
    reverse (b, b + k);
	memset(f, 0, sizeof (f));
    f[0][0] = 1;
    int full = (1 << n) - 1;
	for (int i = 0; i < k; i ++ ) {
		for (int mask = 0; mask < (1 << n); mask ++ ) {
			if (sum[mask] != b[i]) continue;
			int s = full ^ mask;
			for (int t = s; t; t = s & (t - 1)) {
				if (f[i][t]) {
					f[i + 1][mask | t] = 1;
					pre[i + 1][mask | t] = t;
				}

			}		
			if (f[i][0]) {
				f[i + 1][mask] = 1;
				pre[i + 1][mask] = 0;
			}
		}
	}
	if (!f[k][(1 << n) - 1]) {
		puts ("NO");
		return 0;
	}
	puts ("YES");
	int left = (1 << n) - 1;
    for (int i = k; i > 0; --i) {
        int mask = (left ^ pre[i][left]);
        int out = 0;
        for (int j = 0; j < n; ++j) {
            if (mask & 1 << j) {
                if (out ++ > 0) cout << "+";
                cout << s1[j];
            }
        }
        cout << "->" << s2[i - 1] << endl;
        left = pre[i][left];
    }
	return 0;
}
```

---

## 作者：zpyyy (赞：1)

本题题意为:
求一组数能不能其中几个相加得出另一组数。


发现数据很小，于是想到状压。

然后dfs枚举状态。
一开始用打表的方法把原子符号变为数字。dfs(tot,sum,q)表示目前完成了tot个原子，目前原子序数累加的和，用q来表示a数组各元素取或不取。枚举原子a[i]。如果没有取过，就dfs取这个原子。

加个记忆化，比dp跑得快多了
code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=25;
string names[] = {" ","H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu","Zn" ,"Ga", "Ge", "As" ,"Se" ,"Br" ,"Kr" ,"Rb" ,"Sr" ,"Y" ,"Zr" ,"Nb", "Mo" ,"Tc" ,"Ru" ,"Rh" ,"Pd" ,"Ag" ,"Cd" ,"In" ,"Sn" ,"Sb" ,"Te" ,"I" ,"Xe" ,"Cs", "Ba" ,"La", "Ce" ,"Pr" ,"Nd" ,"Pm" ,"Sm", "Eu" ,"Gd", "Tb" ,"Dy" ,"Ho" ,"Er" ,"Tm" ,"Yb" ,"Lu", "Hf" ,"Ta", "W", "Re", "Os" ,"Ir" ,"Pt" ,"Au", "Hg", "Tl", "Pb", "Bi" ,"Po" ,"At", "Rn" ,"Fr", "Ra" ,"Ac" ,"Th" ,"Pa", "U" ,"Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es" ,"Fm"};
int n,k,flag;
int a[N],b[N];
bool f[105][140000];
vector<int> ans; 
int getid(string x) {
	for(int i=1;i<=100;i++)
	if(names[i]== x) return i;
}
string getst(int i) {
	return names[i];
}
void mprint(){
	int sum=0,j=0;
	for(int i=0;i<ans.size();i++){
		sum+=ans[i];
		cout<<getst(ans[i]);
		if(sum==b[j]){
			printf("->");
			cout<<getst(b[j++]);
			printf("\n");
			sum=0;
		}
		else printf("+");
	}
}
void dfs(int tot,int sum,int q){
	if(sum==b[tot]){
		if(tot==k) {
			flag=1;
			printf("YES\n");	
			mprint();
		}
		else dfs(tot+1,0,q);//下一个
	}
	if(sum>b[tot]) return;//减枝
	if(f[tot][q]) return;//记忆化
	for(int i=0;i<n&&(!flag);i++){
		if(q&(1<<i)) continue;
		else {
			ans.push_back(a[i]);
			dfs(tot,sum+a[i],q|(1<<i));
			ans.pop_back();//回溯
		}
	}
	f[tot][q]=1；
}
int main(){
	scanf("%d%d",&n,&k);
	for(int i=0;i<n;i++){
		string s;cin>>s;
		a[i]=getid(s);
	}
	for(int i=0;i<k;i++){
		string s;cin>>s;
		b[i]=getid(s);
	}
	dfs(0,0,0);
	if(!flag) printf("NO");
	return 0;
}
```


---

## 作者：ZBH_123 (赞：0)

## 题目分析
首先，因为字符串不方便进行运算，所以我们要利用元素周期表将其换成它的原子序数。下图是元素周期表：

![](https://cdn.luogu.com.cn/upload/image_hosting/oxrcycsb.png)

接下来就可以开始做题了，以下设 $a_i$ 表示已有的原子的序数，$b_i$ 表示最终的原子的序数。看到数据范围 $1 \le N \le 17$，立刻就可以想到状压 DP。设 $sum_{\mathbb{S}}$ 表示用 $\mathbb{S}$ 中的原子能融合成的原子的序数，那么 $sum_{\mathbb{S}}=\sum{a_i}(i \in \mathbb{S})$。设 $dp_{i,\mathbb{S}}$ 表示用 $\mathbb{S}$ 中的元素能否凑出第 $i$ 个原子，用全集 $\mathbb{U}$ 中剩下的元素能否凑出前 $i-1$ 个原子。首先，如果 $sum_{\mathbb{S}} \ne b_i$，那么 $dp_{i,\mathbb{S}}$ 就等于 $0$。接着，我们就要把剩下的元素构成的集合 $\mathbb{D}$ 算出来，而 $\mathbb{D}$ 自然就等于 $\mathbb{U}-\mathbb{S}$。然后，因为用 $\mathbb{D}$ 中的元素不一定能凑出前 $i-1$ 个原子，但用 $\mathbb{D}$ 的子集中的元素却有可能凑出前 $i-1$ 个原子，所以我们要枚举 $\mathbb{D}$ 的子集 $\mathbb{T}$，如果 $dp_{i-1,\mathbb{T}}=1$，那么 $dp_{i,\mathbb{S}}$ 就等于 $1$（注意，$\mathbb{T}$ 也可以为空集）。注意到，这个题目还要求输出方案，所以我们要在转移时记录路径，最后沿着记录的路径输出就行了。
## AC code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1<<17;
map<string,int>id;
string elements[105]={"", "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne", "Na", "Mg", "Al","Si","P", "S", "Cl", "Ar", "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co","Ni", "Cu","Zn", "Ga", "Ge", "As", "Se", "Br", "Kr", "Rb", "Sr", "Y", "Zr", "Nb", "Mo","Tc","Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te", "I", "Xe", "Cs", "Ba","La","Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm","Yb", "Lu","Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po","At","Rn", "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf","Es", "Fm"};
int n,m,a[20],b[20],sum[maxn],pre[20][maxn];
bool dp[20][maxn];
string s1[20],s2[20];
int main(){
	for(int i=1;i<=100;i++){
		id[elements[i]]=i;
	}
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		cin>>s1[i];
		a[i]=id[s1[i]];
	}
	for(int i=1;i<=m;i++){
		cin>>s2[i];
		b[i]=id[s2[i]];
	}
	reverse(b+1,b+m+1);
	reverse(s2+1,s2+m+1);
	int N=(1<<n)-1;
	for(int i=0;i<=N;i++){
		for(int j=1;j<=n;j++){
			if(i&(1<<(j-1))){
				sum[i]+=a[j];
			}
		}
	}
	dp[0][0]=true;
	for(int i=0;i<m;i++){
		for(int j=0;j<=N;j++){
			if(sum[j]!=b[i+1]){
				continue;
			}
			int s=N^j;
			for(int k=s;k;k=s&(k-1)){
				if(dp[i][k]){
					dp[i+1][j|k]=true,pre[i+1][j|k]=k;
				}
			}
			if(dp[i][0]){
				dp[i+1][j]=true,pre[i+1][j]=0;
			}
		}
	}
	if(!dp[m][N]){
		puts("NO");
		return 0;
	}
	puts("YES");
	int tmp=N;
	for(int i=m;i>=1;i--){
		int s=tmp^pre[i][tmp],cnt=0;
		for(int j=1;j<=n;j++){
			if(s&(1<<(j-1))){
				if(cnt){
					cout<<'+';
				}
				cout<<s1[j];
				cnt++;
			}
		}
		cout<<"->"<<s2[i]<<endl;
		tmp=pre[i][tmp];
	}
	return 0;
}
```

---

## 作者：Mihari (赞：0)

# 题目

[传送门](https://www.luogu.com.cn/problem/CF71E)

# 题解

~~这个原子序数是真的狗~~

首先，看一下那可怜的数据范围：$1\le k\le n\le 17$，那么小？考虑直接暴力...

考虑定义暴力函数 `dfs(const int now,const int s)` 为我们已经处理到目标原子 $now$，而剩下的元素情况为 $s$ 的局面，显然 $s$ 是一个小雨等于 $2^{17}$ 的二进制串，显然，我们选择的组成 $now$ 的原子一定是 $s$ 的子集，可以这样枚举子集：

```cpp
for(int t=s;t;t=(t-1)&s)
```

在这些子集中，找一个子集使得他们的和刚好为 $b[now]$ 的值，最后如果 $now=k+1$ 并且 $s=0$ 时，找到合法解并直接输出。

为了降低复杂度，我们可以定义一个记忆化数组 `bool failed[]` 表示 `dfs(now,s)` 是否失败过，如果曾经失败过就不用再找了

状态有 $17\times 2^{17}$，子集的枚举是 $2^{17}$，极限复杂度似乎为 $\mathcal O(17\times 2^{17}\times 2^{17})$，但是由于我们每一次枚举子集，都只会把 $1$ 变成 $0$，而 $0$ 再也变不回 $1$，所以之多只有 $17$ 层，时间复杂度为 $\mathcal O(17\times 17\times 2^{17})=\mathcal O(37879808)$

# 代码

```cpp
https://www.cnblogs.com/Arextre/p/13442435.html
```



---

