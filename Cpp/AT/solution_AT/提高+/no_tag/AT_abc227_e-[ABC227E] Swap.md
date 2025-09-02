# [ABC227E] Swap

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc227/tasks/abc227_e

`K`, `E`, `Y` のみからなる文字列 $ S $ が与えられます。

$ S $ の隣接する $ 2 $ 文字を入れ替える操作を $ K $ 回まで行えるとき、作ることができる文字列は何種類ありますか？

## 说明/提示

### 制約

- $ 2\ \leq\ |S|\ \leq\ 30 $
- $ 0\ \leq\ K\ \leq\ 10^9 $
- $ S $ は `K`, `E`, `Y` のみからなる

### Sample Explanation 1

`KEY` に対して $ 1 $ 回以下の操作を行うことで得られる文字列は `KEY`, `EKY`, `KYE` の $ 3 $ 種類です。

### Sample Explanation 2

`KKEE` に対して $ 2 $ 回以下の操作を行うことで得られる文字列は `KKEE`, `KEKE`, `EKKE`, `KEEK` の $ 4 $ 種類です。

## 样例 #1

### 输入

```
KEY
1```

### 输出

```
3```

## 样例 #2

### 输入

```
KKEE
2```

### 输出

```
4```

## 样例 #3

### 输入

```
KKEEYY
1000000000```

### 输出

```
90```

# 题解

## 作者：iqwl (赞：13)

### 题意

[翻译的很清楚了。](https://www.luogu.com.cn/problem/AT_abc227_e)
### 解法说明
记搜，正确的！

考虑将每一种字符提到开头，显然可以**暴力找出所有排列情况**。

因为越靠前花费越少，所以每次找到第一个要找的字符就跳出循环，将其放到开头固定，同时减去这步操作的花费。

其实也就是相当于对于字符串的每一种排列，我们都用最优的解法，即用最近的字符转移，然后看看能不能转移到这个排列，正确性显然。


记搜优化则为：遇到之前已考虑过所有排列情况的字符串（搜过的串）时直接返回之前记录的值。

### 举个例子
设有原字符串 `ABC`，且转移后的大写字母写为小写字母。

第一次转移后得到：`aBC`，`bAC`，`cAB`

第二次转移后得到：`abC`，`acB`，`baC`，`bcA`，`caB`，`cbA`

第三次，最后只剩一个字母就不用转移啦。

体现在代码中，每次我们保存的为大写字母（待排列）部分。

代码 AT 上跑了 106 ms，也没有很慢吧。TvT

#### codetime

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

string S;
int K;
map<pair<string,int>,ll>mp;

ll solve(string s,int k)
{
	int n=s.size();
	if(k<0)return 0;//剩下的步数
	if(n<=1)return 1;
	auto p=make_pair(s,k);
	if(mp[p]!=0)return mp[p];

	ll res=0;
	for(auto t:"KEY")
		for(int i=0;i<n;++i)
		{
			if(t==s[i])
			{
				res+=solve(s.substr(0,i)+s.substr(i+1),k-i);
				break;
			}
		}
	return mp[p]=res;
}

int main()
{
	cin>>S>>K;

	solve(S,K);

	cout<<mp[{S,K}]<<'\n';
	return 0;
}
```


---

## 作者：_ZSR_ (赞：9)

### [[ABC227E] Swap](https://www.luogu.com.cn/problem/AT_abc227_e)

事实上，$k$ 只能到达 $n^2$ 这个级别，再大就没有任何区别了。因为当 $k$ 达到 $n^2$ 这个级别的时候，我们已经可以让整个字符串以任意形式排列。那么考虑把 $k$ 设计进 $dp$ 的状态中。

令 $dp_{i,j,k,t}$ 表示当前排好了 $i$ 个 $K$，$j$ 个 $E$，以及 $k$ 个 $Y$，使用了 $t$ 次交换的方案数。考虑下一个字符排什么。我们先预处理出每一个字母第几次出现的位置，以及每一个字母数量的前缀和。假设下一个排 $K$，那么 $dp_{i+1,j,k,t+cost}=dp_{i+1,j,,k,t+cost}+dp_{i,j,,k,t}$。其中 $cost$ 等于原序列中第 $i$ 个 $K$ 和第 $i+1$ 个 $K$ 之间的 $E,Y$ 的数量。如果 $i,j,k$ 分别等于 $K,E,Y$ 的总数量并且 $t \leq k$，那么将这个状态加入答案。

code
```
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=40,M=910;
int n,k,ans;
char str[N];
int sum[3][N],pos[3][N];
int num[3];
int dp[N][N][N][M];
inline int get(char c)
{
	if (c=='K') return 0;
	else if (c=='E') return 1;
	else return 2;
}
signed main()
{
	cin>>str+1>>k;
	n=strlen(str+1);
	for (int i=1;i<=n;++i)
	{
		int x=get(str[i]);
		for (int j=0;j<3;++j) sum[j][i]+=sum[j][i-1];
		sum[x][i]++;
		num[x]++;
		pos[x][num[x]]=i;
	}
	dp[0][0][0][0]=1;
	for (int a=0;a<=num[0];++a)
	{
		for (int b=0;b<=num[1];++b)
		{
			for (int c=0;c<=num[2];++c)
			{
				for (int d=0;d<=900;++d)
				{
					if (a<num[0])
					{
						int p=pos[0][a+1];
						int cnt=max(0ll,sum[1][p]-b)+max(0ll,sum[2][p]-c);
						dp[a+1][b][c][d+cnt]+=dp[a][b][c][d];
					}
					if (b<num[1])
					{
						int p=pos[1][b+1];
						int cnt=max(0ll,sum[0][p]-a)+max(0ll,sum[2][p]-c);
						dp[a][b+1][c][d+cnt]+=dp[a][b][c][d];
					}
					if (c<num[2])
					{
						int p=pos[2][c+1];
						int cnt=max(0ll,sum[0][p]-a)+max(0ll,sum[1][p]-b);
						dp[a][b][c+1][d+cnt]+=dp[a][b][c][d];
					}
					if (a==num[0]&&b==num[1]&&c==num[2]&&d<=k) ans+=dp[a][b][c][d]; 
				}	
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```


---

## 作者：EuphoricStar (赞：5)

感觉是很裸的题。

考虑一个串 $T$，它要交换多少次相邻字符才能等于 $S$。这是一个经典问题，设 $p_i$ 为 $T_i$ 在 $T$ 的前缀 $[1, i]$ 中的出现次数，$q_i$ 为 $T_i$ 在 $S$ 中第 $p_i$ 次出现的位置，那么答案就是排列 $q$ 的逆序对数。证明平凡故略。

由此也容易发现当 $k > \frac{n(n - 1)}{2}$ 时能排列出所有能够排列出来的字符串。设字符 $c$ 的出现次数为 $cnt_c$，那么此时答案即为 $\frac{(|S|!)}{cnt_{\text{A}}! cnt_{\text{B}}! cnt_{\text{C}!}}$。

对于 $k \le \frac{n(n - 1)}{2}$ 的情况，考虑 dp，$f_{i, j, k, p}$ 表示当前填了 $i$ 个 $\text{A}$，$j$ 个 $\text{B}$，$k$ 个 $\text{C}$，用了 $p$ 次交换的方案数。转移就考虑 $T_{i + j + k}$ 填哪个字符即可，因为 $i, j, k$ 都知道，所以此时 $q_{1 \sim i + j + k}$ 能被算出来，所以 $q_{i + j + k}$ 贡献的逆序对数也可以算出来。

时间复杂度 $O(|S|^6)$，但是因为常数小所以跑得很快。

[code](https://atcoder.jp/contests/abc227/submissions/42269686)

---

## 作者：xiaosi4081 (赞：4)

由于我看不懂题解……所以我就来写了一篇题解。

小插曲：我们机房电脑十分 nb，我稍微按了一下 win 键，然后我写题解写到一半那个界面直接给我退了，直接破防。

* 如何想到 dp？
	首先，我们把问题反过来，变成了询问有多少个字符串 $T$ 可以在 $K$ 次操作内变成 $S$。
	
	为了让这个操作数尽可能小（这样才能找到尽可能多的 $T$），我们不会交换相邻的相同字符，因为这对 $T$ 没有任何影响。
	 
	所以我们可以让 $T$ 串第 $i$ 个 `K` 对齐 $S$ 串第 $i$ 个 `K`，`E` 和 `Y` 同理。
	
	由于 $T$ 串也是可以一位一位地决定的，所以我们每决定 $T$ 的一位，就让它马上对齐 $S$ 串中的对应位。这样就可以 DP 了。

那么我们设 $f_{i,j,k,x}$ 为已经决定了 $T$ 串的前 $i+j+k$ 位，有 $i$ 位是 `K`，$j$ 位是 `E`，$k$ 位是 `Y`，用了 $x$ 步让这些字符与 $S$ 串的对应位置对齐。放张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/5hpyzg4e.png)

发现 $x$ 很大，存不下，但是 $k$ 的大小只要大于 $\dfrac {n(n-1)} 2$ 就无意义了。

具体计算步数最大值的方法就是考虑最坏情况，最坏情况下就是 $T$ 最后一个字符移动到第一个字符的位置，操作完之后再把现在 $T$ 的最后一个字符移动到第二个字符的位置，以此类推。

每次转移考虑在 $T$ 串后面加一位，例如说加一位 `K`。

当前状态是 $f_{i,j,k,x}$，接下来计算递推代价。

发现这个对齐比较麻烦，我们不妨只考虑相对与 $T$ 自己的位置而不是相对于 $S$ 的位置。

第 $i+1$ 个 `K` 与前面的字符的相对位置在 $S$ 与 $T$ 中应该是一致的，所以我们只需要使 $T$ 中第 $i+1$ 个 `K` 前面的 `E` 和  `Y` 的数量与 $S$ 相同即可。如果当前的 `E` 数量还不够，就不考虑 `E` 了（因为后面插入 `E` 的时候仍然要交换过来），`Y` 同理。简单做个前缀和维护下。

我们把 `K` 前移到对应位置，然后计算步数即可。具体见代码。

初始时 $f_{0,0,0,0}=1$，转移 $O(1)$，复杂度 $O(n^5)$。

注意一下转移的顺序，$i+j+k$ 从小到大转移。


```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
string s;
int n,m,sums[35][3]; 
int f[35][35][35][505];
int vl[3][35];
signed main(){
	cin>>s>>m;
	n=s.size(); 
	m=min(m,n*(n-1)/2);
	s=" "+s; 
	for(int i=1;i<=n;i++){
		sums[i][0]=sums[i-1][0];
		sums[i][1]=sums[i-1][1];
		sums[i][2]=sums[i-1][2];
		if(s[i]=='K')sums[i][0]++,vl[0][++vl[0][0]]=i;
		if(s[i]=='E')sums[i][1]++,vl[1][++vl[1][0]]=i;
		if(s[i]=='Y')sums[i][2]++,vl[2][++vl[2][0]]=i;
	}
	f[0][0][0][0]=1;
	for(int l=0;l<n;l++){
		for(int i=0;i<=sums[n][0]&&i<=l;i++){
			for(int j=0;i+j<=l&&j<=sums[n][1];j++){
				int k=l-i-j;
				if(k>sums[n][2])continue;
				for(int x=0;x<=min(m,l*(l-1)/2);x++){
					int pa=vl[0][i+1],pb=vl[1][j+1],pc=vl[2][k+1];
					int vla=max(j-sums[pa][1],0ll)+max(k-sums[pa][2],0ll);
					int vlb=max(i-sums[pb][0],0ll)+max(k-sums[pb][2],0ll);
					int vlc=max(i-sums[pc][0],0ll)+max(j-sums[pc][1],0ll);
					if(i+1<=sums[n][0]&&x+vla<=m)f[i+1][j][k][x+vla]+=f[i][j][k][x];
					if(j+1<=sums[n][1]&&x+vlb<=m)f[i][j+1][k][x+vlb]+=f[i][j][k][x];
					if(k+1<=sums[n][2]&&x+vlc<=m)f[i][j][k+1][x+vlc]+=f[i][j][k][x];
				}
			}
		}
	}
	int res=0;
	for(int i=0;i<=m;i++)res+=f[sums[n][0]][sums[n][1]][sums[n][2]][i];
	cout<<res<<endl;
	return 0;
}
```

---

## 作者：xujingyu (赞：4)

## 题意

可以交换 $k$ 次 $s$ 的相邻字符，求可以得到多少个字符串。

## 解法

设 $n=|s|$，$cnt1$ 为 $s$ 中 `K` 的个数，$cnt2$ 为 $s$ 中 `E` 的个数，$cnt3$ 为 $s$ 中 `Y` 的个数，$dp_{a,b,c,x}$ 为长度为 $a$，包含 $b$ 个 `K`，$c$ 个 `E`（和 $a-b-c$ 个 `Y`），需要至少在字符串 $s$ 中执
行 $x$ 次操作才能与字符串 $s$ 的前 $i$ 位相等的字符串 $t$ 个数。

所以答案为 $\sum\limits_{i=0}^kdp_{n,cnt1,cnt2,i}$。

首先将 $k$ 与 $\dfrac{n\times(n-1)}{2}$ 取最小值，因为最多只能对 $s$ 交换 $\dfrac{n\times(n-1)}{2}$ 次，否则会有重复。

每次转移考虑在后面增加一个字符，把它一直往前换，直到当前字符串可以和原串的前 $b$ 个 `K`，$c$ 个 `E` 和 $a-b-c$ 个 `Y` 匹配，并增加操作次数。

时间复杂度为 $\mathcal{O(n^4)}$。


```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

int n,k,t[3][31],pos[3][31],cnt1,cnt2,cnt3,dp[31][31][31][436],ans;
string s;

signed main()
{
	cin >> s;
	scanf("%lld",&k);
	n = s.size();
	k = min(k,n * (n - 1) / 2);
	for(int i = 1;i <= n;i++)
	{
		t[0][i] = t[0][i - 1];
		t[1][i] = t[1][i - 1];
		t[2][i] = t[2][i - 1];
		if(s[i - 1] == 'K') pos[0][++cnt1] = i,t[0][i]++;
		if(s[i - 1] == 'E') pos[1][++cnt2] = i,t[1][i]++;
		if(s[i - 1] == 'Y') pos[2][++cnt3] = i,t[2][i]++;//前缀和累加
	}
	dp[0][0][0][0] = 1;//初始化
	for(int a = 1;a <= n;a++)
	{
		for(int b = 0;b <= a && b <= cnt1;b++)
		{
			for(int c = 0;c + b <= a && c <= cnt2;c++)
			{
				int l = a - b - c;
				if(l > cnt3) continue;
				for(int x = 0;x <= a * (a - 1) / 2 && x <= k;x++)
				{
					int p1 = x - max(c - t[1][pos[0][b]],0ll) - max(l - t[2][pos[0][b]],0ll);
					int p2 = x - max(b - t[0][pos[1][c]],0ll) - max(l - t[2][pos[1][c]],0ll);
					int p3 = x - max(b - t[0][pos[2][l]],0ll) - max(c - t[1][pos[2][l]],0ll);
					if(b > 0 && p1 >= 0) dp[a][b][c][x] += dp[a - 1][b - 1][c][p1];
					if(c > 0 && p2 >= 0) dp[a][b][c][x] += dp[a - 1][b][c - 1][p2];
					if(l > 0 && p3 >= 0) dp[a][b][c][x] += dp[a - 1][b][c][p3];//转移
				}
			}
		}
	}
	for(int i = 0;i <= k;i ++) ans += dp[n][cnt1][cnt2][i];//累加答案
	printf("%lld", ans);
	return 0;
}
```

---

## 作者：txrw (赞：2)

## AT_abc227_e [ABC227E] Swap 题解
### [原题](https://www.luogu.com.cn/problem/AT_abc227_e)

首先，容易得出，当 $k \ge n(n-1)$ 时，可以排列出所有形式。

此时，设 $a$ 为 K 出现的个数，$b$ 为 E 出现的个数，$c$ 为 Y 出现的个数。

答案为 $ \dfrac{len!}{a!b!c!}$。

接着考虑 $k < n(n-1)$，我们对它进行 DP 。

设 $f_{i,j,k,w}$，用了 $i$ 个 K，$j$ 个 E，$k$ 个 Y，交换了 w 次。

转移考虑填当前第 $i + j + k$ 位填哪个字符。

假设下一位填 K，

则  $f_{i+1,j,k,w+cnt} = f_{i+1,j,k,w+cnt} + f_{i,j,k,w}$  
( $cnt$ 为当前 K 和下一个 K 之间有多少 E,Y )， 
其余两个字符同理。

最后计算 $i , j , k$ 与 K,E,Y 个数相等，且交换次数 $\le k$ 的答案即可。

---

## 作者：_edge_ (赞：2)

比较神奇的 DP 题。

首先要稍微收缩一下题面的 $k$ 的范围。

如果 $k>n^2$ 那么必然他可以随便换成全排列的形式，这时候我们用一点小的组合数学就知道答案。

设 $k1$ 为 $s$ 里 $k$ 的个数，$e1$ 为 $s$ 里 $e$ 的个数，$y1$ 为 $s$ 里 $y$ 的个数，$len$ 为 $s$ 的长度。 

必然是 $\dfrac{len!}{k1!e1!y1!}$。

否则的话我们可以对他进行 DP。

我们设 $f_{i,j,k,l,u}$ 放到第 $i$ 个，已经用了 $j$ 个 `K`，用了 $k$ 个 `E`，用了 $l$ 个 `Y`，交换次数剩 $u$ 次。

那么我们如何来描述交换次数呢？一种简单的想法是求逆序对，逆序对即为交换次数。

然后我们枚举当前状态选哪一个，利用存下来的序列来计算逆序对个数。

这里，我们强行把最前的，没有匹配的，作为这个点，因为对于其他的作为这个点的贡献显然没有最前的作为贡献优秀。

然后这里需要用 vector 嵌套的方法来避免内存爆炸，同时由于 $k1+y1+e1=len$ 所以三维状态较小，是可以通过这个题的。

```cpp
#include <bits/stdc++.h> 
#define int long long 
#define pb push_back
using namespace std;
const int INF=1e5+5;
const int INFN=35;
const int INFK=905;
const int INFF=35;
string s1;
int k,lenk,lene,leny;
vector <int> vk,ve,vy;
vector <vector <vector <vector <vector <int> > > > > f;
int check(int lk,int ly,int le,int z) {
    if (z==1) {
        int it1=lower_bound(ve.begin(),ve.end(),lk)-ve.begin()-1;
        int it2=lower_bound(vy.begin(),vy.end(),lk)-vy.begin()-1;
        // cout<<it1<<" "<<it2<<" "<<le<<" "<<ly<<" ?\n";
        return max(0ll,it1-le)+max(0ll,it2-ly);
    }
    else if (z==2) {
        int it1=lower_bound(vk.begin(),vk.end(),ly)-vk.begin()-1;
        int it2=lower_bound(ve.begin(),ve.end(),ly)-ve.begin()-1;
        // cout<<it1<<" "<<it2<<" "<<lk<<" "<<ly<<" "<<le<<" fad? this 2?\n";
        return max(0ll,it1-lk)+max(0ll,it2-le);
    }
    else {
		int it1=lower_bound(vk.begin(),vk.end(),le)-vk.begin()-1;
        int it2=lower_bound(vy.begin(),vy.end(),le)-vy.begin()-1;
		// cout<<it1<<" "<<it2<<" "<<lk<<" "<<le<<" "<<ly<<" fad?\n";
        return max(0ll,it1-lk)+max(0ll,it2-ly);
    }
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>s1;
	cin>>k;
	if (k>900) {
		int kk=0,ee=0,yy=0;
		for (char x:s1)
			if (x=='K') kk++;
			else if (x=='E') ee++;
			else yy++;
		__int128 res=1;
		for (int i=1;i<=kk+yy+ee;i++) res*=i;
		for (int i=1;i<=kk;i++) res/=i;
		for (int i=1;i<=yy;i++) res/=i;
		for (int i=1;i<=ee;i++) res/=i;
		long long res1=res;
		cout<<res1<<"\n";
	}
	else {
		int kk=0,ee=0,yy=0;
		for (char x:s1)
			if (x=='K') kk++;
			else if (x=='E') ee++;
			else yy++;
		int K=k;
		int len=s1.size();
		for (int i=1;i<=len+2;i++) {
			vector <vector <vector <vector <int> > > > v1;
			for (int j=1;j<=kk+2;j++) {
				vector <vector <vector <int> > > v2;
				for (int k=1;k<=yy+2;k++) {
					vector <vector <int> > v3;
					for (int l=1;l<=ee+2;l++) {
						vector <int> v4;
						for (int p=1;p<=K+2;p++)
							v4.pb(0);
						v3.pb(v4);
					}
					v2.pb(v3);
				}
				v1.pb(v2);
			}
			f.pb(v1);
		}
		// f[i][j][l][p][u] 第几位，当前第 j 个 K ，第 k 个 Y ，第 l 个 E，p 次交换。
		s1=" "+s1;vk.pb(0);ve.pb(0);vy.pb(0);
		for (int i=1;i<=len;i++)
			if (s1[i]=='K') vk.pb(i);
			else if (s1[i]=='E') ve.pb(i);
			else vy.pb(i);
		lenk=vk.size();lene=ve.size();leny=vy.size();
//		cout<<f[0][0][0][0][1]<<" ?\n";
		
		f[0][0][0][0][0]=1;
		for (int i=1;i<=len;i++) {
			for (int j=0;j<=kk;j++) {
				for (int l=0;l<=yy;l++) {
					for (int p=0;p<=ee;p++) {
						for (int u=0;u<=k;u++) {
                            int X=check(vk[j],l,p,1),Y=check(j,vy[l],p,2),Z=check(j,l,ve[p],3);
                            // cout<<X<<" "<<Y<<" "<<Z<<" "<<i<<" "<<j<<" "<<l<<" "<<p<<" ?\n";
							if (j && u-X>=0) 
                                f[i][j][l][p][u]+=f[i-1][j-1][l][p][u-X];
							if (l && u-Y>=0)
								f[i][j][l][p][u]+=f[i-1][j][l-1][p][u-Y];
							if (p && u-Z>=0)
								f[i][j][l][p][u]+=f[i-1][j][l][p-1][u-Z];
                            // if (f[i][j][l][p][u])
                            //     cout<<f[i][j][l][p][u]<<" "<<i<<" "<<j<<" "<<l<<" "<<p<<" "<<u<<" ?\n";
						}
					}
				}
			}
		}
		
//		cout<<f[1][0][1][0][1]<<" ?\n";
		int ans=0;
		for (int u=0;u<=k;u++) {
			ans+=f[len][kk][yy][ee][u];
		}
		cout<<ans<<"\n";
	}
	return 0;
}
```


---

## 作者：AC_love (赞：0)

设 $f(i, j, k, s)$ 表示前面有 $i$ 个 $K$，$j$ 个 $E$ 和 $k$ 个 $Y$，且交换了 $s$ 次的方案数。

填表法有点难转移，考虑刷表。

$f(i, j, k, s)$ 可以向某个 $f(i + 1, j, k, s + c)$ 转移，其中 $c$ 是把第 $i + 1$ 个 $K$ 挪到当前位置的代价。

考虑怎么计算 $c$ 即可。

我们先在原字符串中找到第 $i + 1$ 个 $K$ 的位置。

设在原字符串中，第 $i + 1$ 个 $K$ 前面有 $j'$ 个 $E$ 和 $k'$ 个 $Y$。而新字符串里，第 $i + 1$ 个 $K$ 前面有 $j$ 个 $E$ 和 $k$ 个 $Y$。

不难发现，我们只要把在原字符串中多出来的 $E$ 和 $Y$ 挪到这个 $K$ 后面就行了，这一部分代价为 $\max(0, j' - j) + \max(0, k' - k)$。

$E$ 和 $Y$ 的转移同理。

[code](https://atcoder.jp/contests/abc227/submissions/59263928)

---

## 作者：ZDQ2011 (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/AT_abc227_e)
### 题意
给定一个字符串 $S$ 和一个非负整数 $K$，求从 $S$ 开始至多进行 $K$ 次相邻字符的交换，可以生成多少种不同的字符串。

----
### 思路
- 设 $n = |S|$，$cnt1$ 为 $S$ 中 $K$ 的个数，$cnt2$ 为 $S$ 中 $E$ 的个数，$cnt3$ 为 $S$ 中 $Y$ 的个数，$dp _ {a, b, c, x}$ 表示长度为 $a$，包含 $b$ 个 $K$，$c$ 个 $E$ 和 $a - b - c$ 个 $Y$，需要至少在字符串 $S$ 中执行 $x$ 次操作才能与字符串 $s$ 的前 $i$ 位相等的字符串 $T$ 的个数。
- 显然答案应该是 $\sum_{i = 0}^{k} dp _ {n, cnt1, cnt2, i}$。
- 首先将 $k$ 与 $\frac{n \times (n - 1)}{2}$ 取最小值，因为最多只能交换 $\frac{n \times (n - 1)}{2}$ 次，再大一定会重复。同时预处理出每种字母在字符串中出现的位置以及数量的前缀和。
- 但显然第 $i$ 位有三种情况，假设目前最后一位是 $K$，那很显然需要的交换次数 $p1$ 为原串 $i$ 之前最后一个 $K$ 到 $i$ 之间的 $E, Y$ 个数，此时有 $dp _ {a, b, c, x} += dp _ {a - 1, b - 1, c - 1, p1}$，另外两种情况也是类似。
- 每次转移考虑在后面增加一个字符，把它一直往前换，知道当前字符串可以和原串的前 $b$ 个 $k$，$c$ 个 $E$，和 $a - b - c$ 个 $Y$ 匹配，并增加操作次数。
- 时间复杂度为 $O(n ^ 4)$。

---

