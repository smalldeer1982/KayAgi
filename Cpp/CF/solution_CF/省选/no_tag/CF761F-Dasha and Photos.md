# Dasha and Photos

## 题目描述

给你一个 $n \times m$ 的方格，每个格子里有一个小写英文字母。

现在你有 $k$ 个 $n \times m$ 的方格，这些方格都是在给出方格的基础上将一个矩形区域的方格中的字母全部变成一种得到的。

定义两个方格的距离为所有格子中字母在字母表中位置的差的和。你要找到 $k$ 个方格中的一个方格，满足它到其他 $k-1$ 个矩阵的距离之和最小，并输出这个最小值。

## 说明/提示

对于样例 1，仅有的两个版本分别为：

```text
bba | aaa
bba | acc
aaa | acc
```

他们的距离为 $10$。

## 样例 #1

### 输入

```
3 3 2
aaa
aaa
aaa
1 1 2 2 b
2 2 3 3 c
```

### 输出

```
10
```

## 样例 #2

### 输入

```
5 5 3
abcde
eabcd
deabc
cdeab
bcdea
1 1 3 4 f
1 2 3 3 e
1 3 3 4 i
```

### 输出

```
59
```

# 题解

## 作者：Fire_flame (赞：2)

模拟赛遇到的原题，场切了。

感觉没那么难的，评分有点虚高。

## $\mathtt{Solution}$

首先，我们发现每一个位置的值域很小，只有 $26$，所以可以尝试算出每一个位置有多少个相应的字符。

定义 $num_{i,j,t}$ 表示所有的副本里面，位置 $(i,j)$，字符 $t$ 出现了多少次。

可以发现，副本中的每一个位置的字符要么与原画相同，要么被修改的矩形覆盖。

所以我们可以使用二维差分来计算 $num_{i,j,t}$。

具体地，对于每一次修改 $(sx,sy,ex,ey,c)$，我们通过二位差分给位置 $(sx,sy)\sim(ex,ey)$ 打一个标记 $c$。然后，如果某个位置标记数量不足 $k$ 个，表示有些时候没有修改到它，那么 $num$ 就加上相应的值。

现在有了 $num_{i,j,t}$，后面就不难想了。

因为每个副本都是基于原来的方格修改而成的，所以如果以原来的方格作为基准，计算它与其他副本的距离之和，那么就可以实现动态的计算答案（好像和换根 dp 差不多）。

定义 $ans_{i,j,t}$ 表示如果位置 $(i,j)$ 的字符取 $t$，距离其他副本位置 $(i,j)$ 的答案之和是多少。

因为我们已经有了 $num_{i,j,t}$，所以 $ans_{i,j,t}$ 也不难计算。

还需要一个数组 $ans2_{i,j}$，表示位置 $(1,1)\sim(i,j)$ 的字符与原画相同的答案。

根据计算好的 $ans,ans2$ 数组，可以 $O(k)$ 计算答案。

时间复杂度 $O(Tnm+k)$，其中 $T$ 为字符集大小。

参考代码（同时也是我的模拟赛代码）：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int read(){
	int s = 0, f = 1;char ch = getchar();
	while(!isdigit(ch)){if(ch == '-')f = -1;ch = getchar();}
	while(isdigit(ch)){s = s * 10 + ch - '0';ch = getchar();}
	return s * f;
}
void write(int x){
    if(x < 0){putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
const int MAXN = 1e3 + 5, MR = 3e5 + 5;
struct node{
	int sx, sy, ex, ey, p;
}a[MR];
int n, m, k, s, res = 1e18, nowans, mp[MAXN][MAXN], num[MAXN][MAXN][27], ans[MAXN][MAXN][27], ans2[MAXN][MAXN];
char ch[MAXN];
signed main(){
	n = read(), m = read(), k = read(), s = 26;
	for(int i = 1;i <= n;i ++){
		scanf("%s", ch + 1);
		for(int j = 1;j <= m;j ++)mp[i][j] = ch[j] - 'a' + 1;
	}
	for(int i = 1;i <= k;i ++){
		a[i] = {read(), read(), read(), read(), 0};
		char c;
		cin >> c;
		a[i].p = c - 'a' + 1;
	}
	for(int i = 1;i <= k;i ++){
		int h = a[i].p;
		num[a[i].sx][a[i].sy][h] ++;
		num[a[i].ex + 1][a[i].sy][h] --;
		num[a[i].sx][a[i].ey + 1][h] --;
		num[a[i].ex + 1][a[i].ey + 1][h] ++;
		//差分打标记 
	}
	for(int t = 1;t <= s;t ++){
		for(int i = 1;i <= n;i ++){
			for(int j = 1;j <= m;j ++)
				num[i][j][t] += num[i - 1][j][t] + num[i][j - 1][t] - num[i - 1][j - 1][t];
			//前缀和 
		}
	}
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			int tot = 0;
			for(int t = 1;t <= s;t ++)
				tot += num[i][j][t];
			num[i][j][mp[i][j]] += (k - tot);
			//把缺少的补上去
		}
	}
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			int tot = 0, tot2 = 0, tot3 = 0, tot4 = 0;
			for(int t = 1;t <= s;t ++)tot += num[i][j][t] * t, tot3 += num[i][j][t];
			for(int t = 1;t <= s;t ++){
				tot -= num[i][j][t] * t, tot3 -= num[i][j][t];
				tot2 += num[i][j][t] * t, tot4 += num[i][j][t];
				ans[i][j][t] = t * tot4 - tot2 + tot - t * tot3;
				//计算ans[i][j][t]，这里用到了求绝对值的一些技巧 
			}
			nowans += (ans[i][j][mp[i][j]]);
			ans2[i][j] = ans2[i][j - 1] + ans2[i - 1][j] - ans2[i - 1][j - 1] + ans[i][j][mp[i][j]];
			//计算ans2[i][j] 
		}
	}
	for(int i = 1;i <= n;i ++){
		for(int j = 1;j <= m;j ++){
			for(int t = 1;t <= s;t ++)
				ans[i][j][t] += ans[i - 1][j][t] + ans[i][j - 1][t] - ans[i - 1][j - 1][t];
			//对ans数组进行前缀和 
		}
	}
	for(int i = 1;i <= k;i ++){
		int g = a[i].p;
		int h = nowans - (ans2[a[i].ex][a[i].ey] - ans2[a[i].sx - 1][a[i].ey] - ans2[a[i].ex][a[i].sy - 1] + ans2[a[i].sx - 1][a[i].sy - 1]);
		h += (ans[a[i].ex][a[i].ey][g] - ans[a[i].sx - 1][a[i].ey][g] - ans[a[i].ex][a[i].sy - 1][g] + ans[a[i].sx - 1][a[i].sy - 1][g]);
		if(h < res)res = h;
		//动态的计算答案，就是以i方格为基准的答案nowans - ans2[sx,sy] ~ [ex,ey] + ans[sx,sy] ~ [ex,ey]
	}
	printf("%lld\n", res);
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

考虑计算出 $k$ 个方格每个方格的跟其他方格的距离之和。

统计每个位置每个颜色的数量，这样就可以算出这个位置填每个颜色在这个位置与其他方格的距离。求出原图距离其他方格的距离之和。然后相当于挖出一个子矩阵替换为某种颜色。前缀和统计即可。总复杂度 $O(nmW)$，其中 $W=26$。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
int val[1005][1005][26];
int a[300005],b[300005],c[300005],d[300005],e[300005];
int sta[1005][1005][26],rl[1005][1005];
char s[1005][1005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m,k; cin>>n>>m>>k;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>s[i][j];
		}
	}
	for(int i=1;i<=k;i++){
		cin>>a[i]>>b[i]>>c[i]>>d[i];
		char p; cin>>p; e[i]=p-'a';
		val[a[i]][b[i]][e[i]]++;
		val[a[i]][d[i]+1][e[i]]--;
		val[c[i]+1][b[i]][e[i]]--;
		val[c[i]+1][d[i]+1][e[i]]++;
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) for(int l=0;l<26;l++) val[i][j][l]+=val[i-1][j][l]+val[i][j-1][l]-val[i-1][j-1][l];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		int tot=k;
		for(int l=0;l<26;l++) tot-=val[i][j][l];
		val[i][j][s[i][j]-'a']+=tot;
		int mns=k,add=0,tmp=0;
		for(int l=0;l<26;l++) tmp+=val[i][j][l]*l;
		for(int l=0;l<26;l++){
			sta[i][j][l]=tmp;
			mns-=val[i][j][l];
			add+=val[i][j][l];
			tmp-=mns;
			tmp+=add;
		}
		rl[i][j]=sta[i][j][s[i][j]-'a'];
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){
		for(int l=0;l<26;l++) sta[i][j][l]+=sta[i-1][j][l]+sta[i][j-1][l]-sta[i-1][j-1][l];
		rl[i][j]+=rl[i-1][j]+rl[i][j-1]-rl[i-1][j-1]; 
	}
	int tot=rl[n][m],minv=1e18;
	for(int i=1;i<=k;i++){
		minv=min(minv,tot-(rl[c[i]][d[i]]-rl[c[i]][b[i]-1]-rl[a[i]-1][d[i]]+rl[a[i]-1][b[i]-1])+(sta[c[i]][d[i]][e[i]]-sta[c[i]][b[i]-1][e[i]]-sta[a[i]-1][d[i]][e[i]]+sta[a[i]-1][b[i]-1][e[i]]));
	}
	cout<<minv;
	return 0;
}
```

---

## 作者：Big_Dinosaur (赞：0)

模拟赛原题，居然 $30$ 分钟场切……

以下内容字母均被转换一个数字，具体为 ASCLL 码减去 $97$。

记原始方格为 $a$。

首先，用二维差分统计出将 $(i,j)$ 位置改成 $ch$ 的操作数。记为 $q_{i,j,ch}$。

接着，将 $q_{i,j,ch}$ 进一步完善，成为各方格中 $(i,j)$ 为 $ch$ 的操作数。只需将 $q_{i,j,a_{i,j}}$ 加上 $k-\sum_{x=0}^{25}q_{i,j,x}$。

接下来，计算将 $(i,j)$ 改成 $ch$ 造成的距离。具体做法：

- 维护 $s1=\sum_{x=0}^{ch-1} q_{i,j,x},s2=\sum_{x=0}^{ch-1} q_{i,j,x}\times (ch-i),s3=\sum_{x=ch}^{25} q_{i,j,x}\times (i-ch)$。
- 首先暴力算出当 $ch=0$ 时 $s1,s3$，此时 $s2=0$。
- 不断将 $ch$ 加一，接下来，$s3$ 减去 $k-s1$，$s2$ 加上 $s1$，$s1$ 加上 $q_{i,j,ch}$。
- 此时答案为 $s2+s3$。记为 $w_{i,j,ch}$。
- 若 $ch = a_{i,j}$，将 $w_{i,j,26}$ 设为 $w_{i,j,ch}$。

拆每种操作贡献。可以发现第 $x$ 中操作对应的 $ans$ 为：

$$ans=\sum_{i=a}^b\sum_{j=c}^d w_{i,j,ch_x} + \sum_{i=1}^n\sum_{j=1}^m w_{i,j,26}[i < a \operatorname{OR} i >c][j < b \operatorname{OR} j >d]$$

稍微转换一下变为：

$$ans=\sum_{i=a}^b\sum_{j=c}^d w_{i,j,ch_x} + \sum_{i=1}^n\sum_{j=1}^m w_{i,j,26}-\sum_{i=a}^b\sum_{j=c}^d w_{i,j,26}$$

这里只有区间查询，将 $w$ 做前缀和即可。

## 代码
为节约空间，$qz$ 在前面指 $q$，后为 $w$。否则可能 MLE。

另外也有一些变量意义与上述内容不符。部分将注释。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ri register int
#define pii pair<int,int>
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using namespace std;
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
	#if ONLINE_JUDGE
		#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
 	#else
		#define gh() getchar()
	#endif
	inline int r(){
		int o=1,p=0;
		char q=gh();
		while(q<'0'||q>'9'){if(q=='-')o=-1;q=gh();}
		while(q>='0'&&q<='9'){p=(p<<1)+(p<<3)+(q^48);q=gh();}
		return o*p;
	}
	inline char gc(){char q=gh();while(q<=' ')q=gh();return q;}
	inline string gs(){string s="";char g=gh();while(g<=' ')g=gh();while(g>' '){s+=g;g=gh();}return s;}
	inline void Wi(int _){
		if(_==0)return;if(_<0){_=-_;putchar('-');}
		Wi(_/10);putchar((_%10)^48);
	}
	inline void wln(int J){if(J==0)putchar('0');else Wi(J);putchar('\n');}
	inline void w(int J){if(J==0)putchar('0');else Wi(J);}
	inline void ww(int J){if(J==0)putchar('0');else Wi(J);putchar(' ');}
}
using namespace IO;
namespace D1n0{
	int qz[1002][1002][27],T[30];
	int a[1002][1002],n,m,k,x1[301155],y1[301155],x2[301155],y2[301155],ch[301155];
	inline int ask(int L,int id){
		return qz[x2[id]][y2[id]][L]-qz[x1[id]-1][y2[id]][L]-qz[x2[id]][y1[id]-1][L]+qz[x1[id]-1][y1[id]-1][L];
	}
	inline void _(){
		n=r(),m=r(),k=r();
		for(ri i=1;i<=n;++i){
			string s=gs();
			for(ri j=1;j<=m;++j)a[i][j]=s[j-1]-'a';
		}
		for(ri i=1;i<=k;++i){
			x1[i]=r(),y1[i]=r();//a,b
			x2[i]=r(),y2[i]=r();//c,d
			ch[i]=gc()-'a';
			++qz[x1[i]][y1[i]][ch[i]];
			--qz[x2[i]+1][y1[i]][ch[i]];
			--qz[x1[i]][y2[i]+1][ch[i]];
			++qz[x2[i]+1][y2[i]+1][ch[i]];
		}
		for(ri x=0;x<26;++x)for(ri i=1;i<=n;++i)for(ri j=1;j<=m;++j)
		qz[i][j][x]+=qz[i-1][j][x]+qz[i][j-1][x]-qz[i-1][j-1][x];
		for(ri i=1;i<=n;++i)for(ri j=1;j<=m;++j){
			int Su=0,Su3=0;
			for(ri x=0;x<26;++x)Su+=qz[i][j][x],Su3+=qz[i][j][x]*(x+1);
			qz[i][j][a[i][j]]+=k-Su;Su3+=(k-Su)*(a[i][j]+1);
			Su=0;//Su 为 s2，Su2 为 s1，Su3 为 s3。
			int Su2=0;
			for(ri x=0;x<26;++x){
				Su3-=k-Su2;Su+=Su2;Su2+=qz[i][j][x];
				qz[i][j][x]=Su+Su3;
			}
			qz[i][j][26]=qz[i][j][a[i][j]];
			Su=0;Su2=0;
		}
		for(ri i=1;i<=n;++i)for(ri j=1;j<=m;++j)for(ri x=0;x<=26;++x)
		qz[i][j][x]+=qz[i-1][j][x]+qz[i][j-1][x]-qz[i-1][j-1][x];
		int mi=1e18;
		for(ri i=1;i<=k;++i){
			mi=min(mi,qz[n][m][26]-ask(26,i)+ask(ch[i],i));
		}
		w(mi);
	}
}
signed main(){D1n0::_();}
```

---

## 作者：Fracture_Dream (赞：0)

# 简述题意
给定一个 $n \times m$ 的方格，每个格子里有一个小写英文字母。

现在你有 $k$ 个 $n \times m$ 的方格，这些方格都是给定方格的基础上将左上角为 $(a_i,b_i)$，右下角为 $(c_i,d_i)$ 的矩形区域的方格中的字母替换成字符 $e_i$。

定义两个方格的距离为所有格子中字母在 $\text{Ascll}$ 码的差累和。你要找到 $k$ 个方格中的一个方格，满足它到其他 $k-1$ 个矩阵的距离之和最小，并输出这个最小值。

- $1 \le n,m \le 1000，1 \le k \le 3 \times 10^5$
- $1 \le a_i,b_i \le n,1 \le c_i,d_i\le m$

# 思路
以下简记：
- $X(a_i,b_i,c_i,d_i)$ 表示 $X$ 矩阵的左上角为 $(a_i,b_i)$，右下角为 $(c_i,d_i)$ 的子矩阵的**元素之和**。
- $A$ 表示原矩阵。

首先不难想到枚举每一个矩阵，求出其到其他 $k-1$ 个矩阵的距离和，取最小值即可，然而我们难以直接维护当前枚举到的矩阵与其他矩阵的距离和。

注意到，每一个新矩阵与原矩阵唯一的差别便是一个子矩阵不一样，套路地想到维护原矩阵。

不妨令 $w_{i,j,k}$ 为 $k$ 个新矩阵中，$(i,j)$ 这一位的字母为 $k$ 的数量，$cnt_{i,j}$ 表示 $k$ 个新矩阵中有多少个矩阵与原矩阵不同的位置包含了 $(i,j)$。

考虑如何求出 $w$ 数组。不妨先让 $\forall x \in [1,n],y \in [1,m]，w_{x,y,A_{x,y}}=k$，后面减去掉原矩阵贡献的这一部分即可。而后，每生成一个矩阵，就相当于把 $\forall x \in [a_i,b_i],y \in[c_i,d_i],w_{x,y,e_i} \leftarrow w_{x,y,e_i}+1,cnt_{x,y} \leftarrow cnt_{x,y}+1$，最后统一把 $x \in [1,n],y \in [1,m],w_{x,y,A_{x,y}} \leftarrow w_{x,y,A_{x,y}} - cnt_{x,y}$ 即可。

有了 $w$ 数组后，就可以求出原矩阵与 $k$ 个新矩阵的距离和。具体地，枚举 $(i,j)$，那么当前位置与 $k$ 个矩阵对应位置的差值和即为： $res_{i,j}=\sum_{o \in S}w_{i,j,o} \times |A_{i,j}-o|$，其中 $o$ 为字符，$S$ 为字符集。

有了 $res$ 数组之后就大功告成了！

而后，枚举每一个新矩阵，先继承一下原矩阵的贡献，就是 $res(1,1,n,m)-res(a_i,b_i,c_i,d_i)$，紧接着考虑 $(a_i,b_i,c_i,d_i)$ 这个子矩阵对答案的贡献，显然就是 $\sum_{o \in S}w_o(a_i,b_i,c_i,d_i) \times |e_i-o|$。（说人话 $w_o(a_i,b_i,c_i,d_i)$ 表示的就是 $k$ 个矩阵每一个 $(a_i,b_i,c_i,d_i)$ 子矩阵中有多少个字符 $o$）

总结一下，一个矩阵到其他 $k-1$ 个矩阵的距离和即为：

$$res(1,1,n,m)-res(a_i,b_i,c_i,d_i)+\sum_{o \in S}w_o(a_i,b_i,c_i,d_i) \times |e_i-o|$$

# 空间优化
如果你使用的是 区间修改，区间查询 的二维树状数组求解 $w,res$，那么恭喜你喜提 $\text{Memory limit exceeded on test 1}$，因为每一个树状数组需要 $4$ 个 $bit$ 数组，且需要 $26$ 个这样的树状数组，空间炸飞了。

再仔细思考，发现此题的 区间修改，区间查询 不是同时进行的，所以不妨先差分，再前缀和求出每一位，再前缀和维护子矩阵的和，这样普通数组就可以解决。

# 代码
请自行忽略树状数组，当成差分看就行。

~~主要是最开始超空间限制，改了半截发现空间开得下了就懒得改了。~~ 

 

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN = 1000 + 5 , MAXM = 3e5 + 5;
int n , m , k , a[MAXM] , b[MAXM] , c[MAXM] , d[MAXM];
ll Pre_T[MAXN][MAXN][26] , Pre_res[MAXN][MAXN] , res[MAXN][MAXN];
char mp[MAXN][MAXN] , opt[MAXM];
struct BIT{
	#define lowbit(x) (x & -x)
	int bit[MAXN][MAXN];
	void update(int k , int k2 , int x) {
		for (int i = k ; i <= n ; i += lowbit(i)) {
			for (int j = k2 ; j <= m ; j += lowbit(j)) {
				bit[i][j] += x;
			}
		}
	}
	ll Sum(int k , int k2) {
		ll sum = 0;
		for (int i = k ; i ; i -= lowbit(i)) {
			for (int j = k2 ; j ; j -= lowbit(j)) {
				sum += bit[i][j];
			}
		}
		return sum;
	} 
	void add(int a , int b , int c , int d , int x) {update(a , b , x) , update(a , d + 1 , -x) , update(c + 1 , b , -x) , update(c + 1 , d + 1 , x);}
}T[27];
ll query1(int a , int b , int c , int d , int opt) {return Pre_T[c][d][opt] - Pre_T[a - 1][d][opt] - Pre_T[c][b - 1][opt] + Pre_T[a - 1][b - 1][opt];}
ll query2(int a , int b , int c , int d) {return Pre_res[c][d] - Pre_res[a - 1][d] - Pre_res[c][b - 1] + Pre_res[a - 1][b - 1];}
signed main() { 
	ios::sync_with_stdio(false);
	cin.tie(nullptr) , cout.tie(nullptr);
	cin >> n >> m >> k;
	for (int i = 1 ; i <= n ; i ++) {
		for (int j = 1 ; j <= m ; j ++) {
			cin >> mp[i][j];
		}
	}
	for (int i = 1 ; i <= k ; i ++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i] >> opt[i];
		T[opt[i] - 'a'].add(a[i] , b[i] , c[i] , d[i] , 1);
		T[26].add(a[i] , b[i] , c[i] , d[i] , 1);
	}
	for (int i = 1 ; i <= n ; i ++) {
		for (int j = 1 ; j <= m ; j ++) {
			int sel = T[26].Sum(i , j);
			T[mp[i][j] - 'a'].add(i , j , i , j , k - sel); 
		}
	}
	for (int i = 1 ; i <= n ; i ++) {
		for (int j = 1 ; j <= m ; j ++) {
			int now = mp[i][j] - 'a';
			for (int o = 0 ; o < 26 ; o ++) res[i][j] += 1ll * abs(now - o) * T[o].Sum(i , j);
		}
	}
	for (int i = 1 ; i <= n ; i ++) {
		for (int j = 1 ; j <= m ; j ++) {
			Pre_res[i][j] = Pre_res[i - 1][j] + Pre_res[i][j - 1] - Pre_res[i - 1][j - 1] + res[i][j];
			for (int o = 0 ; o < 26 ; o ++) {
				Pre_T[i][j][o] = Pre_T[i - 1][j][o] + Pre_T[i][j - 1][o] - Pre_T[i - 1][j - 1][o] + T[o].Sum(i , j);
			} 
		}
	}
	ll ans = 1e16;
	for (int i = 1 ; i <= k ; i ++) {
		int now = opt[i] - 'a';
		ll w = query2(1 , 1 , n , m) - query2(a[i] , b[i] , c[i] , d[i]);
		for (int o = 0 ; o < 26 ; o ++) w += 1ll * abs(now - o) * query1(a[i] , b[i] , c[i] , d[i] , o);
		ans = min(ans , w);
	}
	cout << ans;
	return 0;
}
```

---

