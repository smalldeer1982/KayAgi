# [COCI 2011/2012 #5] POPLOČAVANJE

## 题目背景

注意：本题相对于原题缩小了空间限制，需要一些小技巧才能通过。

## 题目描述

有一条由 $N$ 个英文小写字母组成的街道，市政府偶尔会更换街道上的瓷砖。但是，字母瓷砖的需求量很大，所以政府只有 $M$ 种字母瓷砖可供选择。

第 $i$ 个瓦片图案由 $L_{i}$ 个字母组成。瓷砖不能旋转，也不能打碎，而且只能放置在瓷砖字母与街道上连续的字母子序列重合的地方。

瓷砖可以重叠，且可以使用相同图案的多块瓷砖。如果一个街道不能被任何瓷砖覆盖，那么他就是不好的。

求有多少个不好的街道。

## 说明/提示

$1\le N\le 3\times 10^{5}$，$1\le M\le 5\times 10^{3}$，$1\le L_{i}\le 5\times 10^{3}$。

题目译自 [COCI 2011/2012 #5 T6](https://hsin.hr/coci/archive/2011_2012/contest5_tasks.pdf)。

## 样例 #1

### 输入

```
6
abcbab
2
cb
cbab```

### 输出

```
2```

## 样例 #2

### 输入

```
4
abab
2
bac
baba```

### 输出

```
4```

## 样例 #3

### 输入

```
6
abcabc
2
abca
cab```

### 输出

```
1```

# 题解

## 作者：kkxacj (赞：8)

[题目传送门](https://www.luogu.com.cn/problem/P4595)

#### 前言
本蒟蒻当时只差一步之遥就 A 了，写篇题解纪念一下。
#### 思路
直接模拟肯定会超时，只有 $60$ 分（这个应该都会吧）。

于是我们可以用到查分和哈希优化。
用哈希最好定义一个质数，亲测 $233$ 可过，哈希如下。

```c
for(int i = 1;i <= n;i++)
{
	ha[i] = ha[i - 1] * bt + a[i];	//哈希
	dw[i] = dw[i - 1] * bt; //dw是本人朋友，这里最好用 pw
}
```
然后再在把暴力代码改一下，就 A 了。

```c
#include<bits/stdc++.h>
using namespace std;
char a[300010],b[5010];
int n,m,lb,bt = 233,v[300001];
long long ha[300010],dw[300010],h,ans;
int main()
{
//	freopen("block.in","r",stdin);
//	freopen("block.out","w",stdout);
	scanf("%d",&n);
	scanf("%s",a + 1);
	scanf("%d",&m);
	dw[0] = 1;
	for(int i = 1;i <= n;i++)//哈希
	{
		ha[i] = ha[i - 1] * bt + a[i];	
		dw[i] = dw[i - 1] * bt;
	}
	for(int i = 1;i <= m;i++)
	{
		scanf("%s",b + 1);
		lb = strlen(b + 1);
		h = 0;
		for(int k = 1;k <= lb;k++)
			h = h * bt + b[k]; //前缀
		for(int j = 1;j <= n - lb + 1;j++)
		{
			if(ha[j + lb - 1] - ha[j - 1] * dw[lb] == h) 
				v[j]++, v[j + lb]--; //差分
		}
	}
	int o;
	for(int i = 1;i <= n;i++)
	{
		o += v[i];
		if(!o) ans++;
	}
	printf("%lld\n",ans);
	return 0;
}


```




---

## 作者：夜临 (赞：6)

~~因为是最优解就来写题解了（滑稽）~~

------------
从数据大小上分析，这道题的 $n$ 的大小比较大，但是图案的大小和图案个数 $m$ 都比较小，较普遍的算法是使用AC自动机进行字符匹配，但是这里我们使用哈希，在加上优化后不仅空间比AC自动机小很多，而且在普遍的测试点中时间非常快，所有测试点时间之和只有$657ms$。

先考虑比较朴素的匹配，即将 $m$ 个小字符串进行哈希，再在大字符串上 $O(n)$ 进行匹配，然后通过差分来实现对能铺的位置的覆盖。

但是显然这样的时间复杂度是 $O(n\times m)$ ，所以我们要对算法进行优化。

------------
首先一个较明显的思路是对字符串的开头第一个字母进行分类，先将$m$个哈希值预处理出来，再按照首字母分别装到不同的数组中，在每次询问的时候只要询问需要的首字母的数组即可，那么这样的时间复杂度度就能减少26倍。

------------
这样就已经是第二优解了，但是这并不是最快的，我们还可以再每个大字符串的字符匹配时，从长度最大的字符串开始匹配，这样当我们匹配成功时，剩下的部分就没有必要在匹配了。

------------
于是一个简单的哈希加差分加剪枝就能飞快地A掉这道黑题。
~~٩(๑❛ᴗ❛๑)۶~~

下面是我自己的代码。

ps:我使用的是对最后一个字符进行分类，这样能防止被卡，使代码更快。

------------
```cpp
#include<bits/stdc++.h>
#define un unsigned long long
using namespace std;
const int N=3e5+5;
struct z{
	int Len;
	un Has;
} g[30][5005];//将哈希值与长度装在结构体中方便排序和调用
int n,m,Len,cnt[30],L[N];
un f[N],num[N],p;
char a[N],s[5005];
bool cmp(z a,z b){
	return a.Len>b.Len;
}
int main(){
	scanf("%d%s",&n,&a);
	num[0]=1;
	for(int i=0;i<n;i++)f[i]=f[i-1]*233+a[i],num[i+1]=num[i]*233;
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%s",&s);
		Len=strlen(s);
		int mb=s[Len-1]-'a';//按照尾字母分类
		p=0;
		for(int j=0;j<Len;j++)p=p*233+s[j];
		g[mb][++cnt[mb]]=(z){Len,p};
	}
	for(int i=0;i<26;i++)sort(g[i]+1,g[i]+cnt[i]+1,cmp);
	for(int i=0;i<n;i++){
		int mb=a[i]-'a';//按照尾字母进行查询
		for(int j=1;j<=cnt[mb];j++){
			Len=g[mb][j].Len;
			if(i<Len-1)continue;
			if(f[i]-f[i-Len]*num[Len]==g[mb][j].Has){
				L[i-Len+1]++,L[i+1]--;//对覆盖区域进行差分
				break;//剩下的都是比当前字符串短的，就算匹配成功对答案也没有贡献，可以直接break
			}
		}
	}
	int ans=0;
	for(int i=0;i<n;i++){
		if(i>0)L[i]+=L[i-1];
		if(L[i]==0)ans++;
	}
	cout<<ans;
}
```


---

## 作者：CuteMurasame (赞：5)

### 基本分析：

蒟蒻不会 KMP，只会哈希和差分qwq，让我们来看看怎么做吧！

1. 首先我们取一个质数，亲测 $353$ 可过；
2. 然后定义字符数组 $a$、$b$ 代表题目中的 $N$ 个小写字母和 $L_i$ 个小写字母。定义哈希数组 $hsh$ 和 $353$ 进制数 $pwr$；
3. 最后循环模拟即可。

---

- 哈希、求 $353$ 进制数的过程如下：
  
  
  ```cpp
    for(int i=1;i<=n;++i)
        hsh[i]=hsh[i-1]*bt+a[i],//哈希
        pwr[i]=pwr[i-1]*bt;  //353 进制数
  ```
  
  
  其中 $bt=353$。
  
---


- 循环过程如下：
  
  ```cpp
	for(int i=1;i<=m;++i)
	{
		scanf("%s",b+1);
		lb=strlen(b+1); //输入字符串 b，从下标 1 开始
        h=0;
        for(int j=1;j<=lb;++j)
            h=h*bt+b[j];  //前缀和模拟字符串转数字
		for(int j=1;j<=n-lb+1;++j)
		{
			if(hsh[j+lb-1]-hsh[j-1]*pwr[lb]==h)
                ++vis[j],--vis[j+lb]; //差分记录
		}
	}
  ```
  
  其中 $vis$ 数组用于差分。因为是差分所以最后输出时需要处理，代码如下：
  
  ```cpp
	int k=0;
	for(int i=1;i<=n;++i)
	    ans+=!(k+=vis[i]);
  ```
  
  其中 `ans+=!(k+=vis[i])` 语句可展开为：`k+=vis[i], ans+=!k`。
  
---
 
 - 最后输出即可。
 
---
 
### 完整代码：
```cpp
#include<bits/stdc++.h>
#define bt 353 //将 bt 定义为质数 353
using namespace std;
char a[300005],b[5005];
int n,m;
int lb,ans,hsh[300005],pwr[300005],h;
int vis[300005];
// 定义变量、数组
int main()
{
    pwr[0]=1;
	scanf("%d",&n);
	scanf("%s",a+1); //输入字符串 a，从下标 1 开始
	scanf("%d",&m);
    for(int i=1;i<=n;++i) 
        hsh[i]=hsh[i-1]*bt+a[i], //哈希
        pwr[i]=pwr[i-1]*bt;  //353 进制数
	for(int i=1;i<=m;++i)
	{
		scanf("%s",b+1);
		lb=strlen(b+1);
        h=0;
        for(int j=1;j<=lb;++j)
            h=h*bt+b[j]; //前缀和模拟字符串转数字
		for(int j=1;j<=n-lb+1;++j)
		{
			if(hsh[j+lb-1]-hsh[j-1]*pwr[lb]==h)
                ++vis[j],--vis[j+lb];//差分记录
		}
	}
	int k=0;
	for(int i=1;i<=n;++i) //处理差分
	    ans+=!(k+=vis[i]);// 可写成k+=vis[i], ans+=!k
	printf("%d\n",ans); //输出答案
	return 0;
}
```

是不是很简单呢qwq

---

## 作者：内拉组里 (赞：1)

这是一种 **Hash** 伪优化。

# Thoughts：

字符串匹配应该都能想到 **Hash**，

首先对街道序列作前缀 **Hash**，以便分段匹配。

然后对于每块瓷砖，只需记录模式串的长度以及 **Hash** 即可。

然后在母串中线性扫描，若模式串匹配，则将匹配的子串位置全部标记，然后跳到串尾。

显然，当模式串存在循环节时，这种算法可能会炸。

但是数据水，吸个氧就过了，顺便跻身最优解第一页。\^_\^ 

# Analyses：

> 总时间复杂度 $ \Theta (NM) $。
>
> 总空间复杂度 $ \Theta (N) $。

# Code：

```cpp
//#pragma		GCC		optimize(2)
#include	<iostream>
#include	<cstring>
using namespace std;
constexpr int maxn = 3e5+4;
constexpr int maxm = 5e3+4;
constexpr int P = 1331;

int n, m;
char s[maxn];
int vis[maxn];
int pwd[maxn];
unsigned int h[maxn];

inline int query (int l, int r)
{
	return h[r] - h[l - 1] * pwd[r - l + 1];
}

signed main (void)
{
	cin >> n >> s + 1;
	for (int i = 1; i <= n; i++) h[i] = h[i - 1] * P + s[i];
	pwd[0] = 1;
	for (int i = 1; i <= n; i++) pwd[i] = pwd[i - 1] * P;
	cin >> m;
	while (m--)
	{
		cin >> s + 1;
		int hsh = 0;
		int len = strlen (s + 1);
		for (int i = 1; i <= len; i++) hsh = hsh * P + s[i];
		for (int i = 1; i + len - 1 <= n; i++)
			if (query (i, i + len - 1) == hsh)
		{
			for (int j = i; j <= i + len - 1; j++) vis[j] = 1;
			i += len - 1;
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) if (!vis[i]) ans++;
	cout << ans << endl;
	return 0;
}
```

---

## 作者：yxy666 (赞：1)

本蒟蒻来交第一篇黑题题解。。。

由于本人太弱，不会 $KMP$ ,也不会 $AC$ 自动机，所以本人只能用傻傻的哈希啊！！！

想法：我们将每个字母都转成 $prime$（ $prime$ 是一个大于 $26$ 的质数）进制数，也就是类似于快读的原理， $x=x*10+ch-'0'$。 

如果 $int$ 类型存不下，变成乱码了，那又会怎么样呢，我把所有的字符串都转成乱码，反正规则都是一样的，又没关系。（谁让这道黑题那么坑！！！我只能无耻啊！！！）

然后我们先按照乱码构造一趟前缀和，枚举一个终点，然后看一下这一段的乱码是否与街道字符串的乱码相等，相等，就有差分标记一下。最后再找一趟没有大于 $0$ 的值有几个，就好了。

至于这个 $prime$ ，我试了好多次，发现一般来说是质数比较好一点，这样撞车的概率比较小。

本蒟蒻语文较差，所以代码中还会有有注释。

$code$ ：
```
#include<bits/stdc++.h>
using namespace std;
const int prime=37,maxn=300005;
int n,m,Ans,E[maxn],key[maxn],pw[maxn];
char s[maxn];
int main(){
    scanf("%d%s",&n,s+1);
    pw[0]=1;
    for (int i=1;i<=n;i++){
       key[i]=key[i-1]*prime+s[i];//制造prime进制数，就算是乱码也没关系，因为其他字符串也是这样处理的 
       pw [i]=pw [i-1]*prime;
    }
    scanf("%d",&m);
    for (int i=1;i<=m;i++){
      scanf("%s",s);
      int l=strlen(s),kp=0;
      for (int j=0;j<l;j++) kp=kp*prime+s[j];//制造prime进制数
      for (int j=l;j<=n;j++){
      	int w=key[j]-key[j-l]*pw[l];//构造枚举一个终点，那么起点就为j-l+1
        if (w==kp) E[j-l+1]++,E[j+1]--;//如果乱码一样，差分
	  }
    }
    int now=0;
    for (int i=1;i<=n;i++) now+=E[i],Ans+=!now;//差分，求换不了的瓷砖数
    printf("%d\n",Ans);
    return 0;
}
```


---

## 作者：Taduro (赞：1)

卡常+分块+奇技淫巧能使AC自动机通过SAM黑题

[传送门](https://www.luogu.org/problemnew/show/P4595)

首先不考虑空间的AC自动机的做法非常好想对吧，把每个单词都存好，匹配母串，打上标记即可。

但是AC自动机是存不了5000*5000的，但本题讨论中有大佬提供了一个做法，过10~30个字符串求一次答案并重建AC自动机。

但我觉得10~30个字符串非常草率，不如分个块，$\sqrt m$个串优美吧？

那就$\sqrt m$个串求一次答案，空间大概在6e5左右是比较稳的。但有一个坏消息，如果你AC自动机暴力跳fail+暴力打标记+没有优越的AC自动机模板的话，你就会T掉。

现在我来讲解一下一些优化技巧

#### 预处理fail树

首先暴力跳fail是对复杂度影响最大的，我们给每个点附一个值cnt表示如果这个点是单词的结尾的话那个单词的长度，如果是多个就是最长的那个的长度。

我们跳fail实际上是求这个点到fail树根中最大的那个cnt，这个东西可以O(树的大小)处理出来。

那么有一个问题，如果在某点到fail树根的路径上，最大的cnt和某个比他小cnt的区间不同怎么办？（就是选了最大的那个cnt会导致小的cnt的区间计算不到）

不会出现这个情况，因为fail是由长的串指向跟当前串后缀相同的串，一定由长指向短，由母串指向子串，而且在一个点到根的路径上，cnt的最大值是递增的，**比最大的cnt小的cnt代表的串一定作为当前串的子串出现过**，所以比**最大的cnt小的cnt一定曾被作为最大的cnt计算过**。

所以我们要把fail树建出来，对其dfs，匹配到一个点时O(1)得到他在到fail树根路径上最大的cnt。

#### 差分打标记

如果你只会fail树而像一个刚学OI的萌新一样暴力打标记的话，那么说明你跟我一样AC自动机学傻了，这个trick是我在只有前面那个优化而T到85分时在神仙@[ZUTTER_](https://www.luogu.org/space/show?uid=50562)的代码里找到的，她暴力跳fail但用了这个优化成功的水了过去。

首先我们发现一个被标记打多少次是玄学的，如果你运气不好很可能被卡死，所以打标记的时候要改成对差分数组操作，在区间开头+1，在区间结尾后一位-1。最后做一遍前缀和，如果一个点是0那他一定没有被覆盖。

```c++
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define re register
using namespace std;
struct node{
	int ch[26],cnt,fail;
}t[600000];
struct edge{
	int next,to;
}w[600001];
char ch[300001],s[5001]; int m;
int n,blo,heap,tail,team[600001];
int bl[5001],o[300001],num,cnt;
int maxn[600001],head[600001],ans;
inline void add(int x,int y){
	w[++cnt].next=head[x];
	w[cnt].to=y; head[x]=cnt;
}
inline void insert(char *s){
	int u=0,l=strlen(s);
	for (re int i=0; i<l; i++){
		int a=s[i]-'a';
		if (!t[u].ch[a]) t[u].ch[a]=++num;
		u=t[u].ch[a];
	}
	t[u].cnt=l;
}
void dfs(int x){
	maxn[x]=max(maxn[x],t[x].cnt);
	for (re int i=head[x]; i; i=w[i].next){
		maxn[w[i].to]=maxn[x]; dfs(w[i].to);
	}
}
inline void build(){
	heap=tail=1; team[heap]=0;
	while (heap<=tail){
		int x=team[heap];
		for (re int i=0; i<26; i++){
			if (t[x].ch[i]){
				team[++tail]=t[x].ch[i];
				if (!x) continue;
				t[t[x].ch[i]].fail=t[t[x].fail].ch[i];
			}
			else t[x].ch[i]=t[t[x].fail].ch[i];
		}
		heap++;
	}
	memset(head,0,sizeof(head)); cnt=0;
	for (re int i=1; i<=num; i++) add(t[i].fail,i);
	dfs(0);
}
inline void change(){
	int u=0;
	for (re int i=1; i<=n; i++){
		int a=ch[i]-'a'; u=t[u].ch[a];
		// for (re int j=u; j; j=t[j].fail)
		// 	if (t[j].cnt) o[i+1]-=1,o[i-t[j].cnt+1]+=1;
		o[i+1]-=1; o[i-maxn[u]+1]+=1;
		// for (re int j=0; j<maxn[u]; j++) o[i-j]=1;
	}
}
int main(){
	scanf("%d",&n);	scanf("%s",ch+1);
	scanf("%d",&m); blo=sqrt(m); bl[0]=1;
	for (re int i=1; i<=m; i++) bl[i]=(i-1)/blo+1;
	for (re int i=1; i<=m; i++){
		scanf("%s",s); insert(s);
		if (bl[i]!=bl[i-1]||i==m){
			build(); change();
			for (re int j=0; j<=num; j++){
				t[j].cnt=t[j].fail=maxn[j]=0;
				for (re int k=0; k<26; k++) t[j].ch[k]=0;
			}
			num=0;// puts("ok");
		}
	}
	// for (re int i=1; i<=n; i++) if (!o[i]) ans++;
	for (re int i=1; i<=n; i++){o[i]+=o[i-1]; if (!o[i]) ans++;}
	printf("%d\n",ans);
	return 0;
}
```

这份AC自动机代码大概只比正解慢1000ms，目前只有一个AC自动机跑的比我快。
~~听说调整块的大小能更快~~

---

## 作者：asuldb (赞：1)

据说这道题卡空间？

不存在的，拿$AC$自动机去存$5000\times5000$的串肯定是要M的

我们可以考虑对长度为$n$的串建一个$SAM$，这样空间就只需要两倍的$3e5$了

之后把每个输入的串放到$SAM$上匹配，匹配到了就打更新一下这个节点的最大匹配长度

之后在$parent$树上传一下这个最大匹配长度，一遍差分维护就好了

空间完全不卡，如果硬要继续卡，我们可以直接用$map$来存$SAM$那样空间就是线性的，不需要去乘上那个字符集的常数了

代码

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#define re register
#define maxn 600006
#define LL long long
#define inf 999999999
inline int max(int a,int b){return a>b?a:b;}
int tax[maxn],a[maxn];
int n,m,cnt=1,lst=1,num,ans;
int fa[maxn],len[maxn],endpos[maxn],son[maxn][26],mx[maxn];
int pre[maxn>>1];
char S[5005],T[maxn>>1];
inline void ins(int c,int o)
{
    int p=++cnt,f=lst; lst=p;
    len[p]=len[f]+1,endpos[p]=o;
    while(f&&!son[f][c]) son[f][c]=p,f=fa[f];
    if(!f) {fa[p]=1;return;}
    int x=son[f][c];
    if(len[f]+1==len[x]) {fa[p]=x;return;}
    int y=++cnt;
    len[y]=len[f]+1,fa[y]=fa[x],fa[x]=fa[p]=y;
    memcpy(son[y],son[x],sizeof(son[x]));
    while(f&&son[f][c]==x) son[f][c]=y,f=fa[f];
}
int main()
{
    scanf("%d",&n);
    scanf("%s",T+1);
    for(re int i=1;i<=n;i++) ins(T[i]-'a',i);
    scanf("%d",&m);
    while(m--)
    {
        scanf("%s",S+1);
        int len=strlen(S+1);
        int now=1;
        for(re int i=1;i<=len;i++) {now=son[now][S[i]-'a'];if(!now) break;}
        if(now)mx[now]=max(mx[now],len);
    }
    for(re int i=1;i<=cnt;i++) tax[len[i]]++;
    for(re int i=1;i<=n;i++) tax[i]+=tax[i-1];
    for(re int i=1;i<=cnt;i++) a[tax[len[i]]--]=i;
    for(re int i=1;i<=cnt;i++)
    {
        int k=a[i];
        mx[k]=max(mx[k],mx[fa[k]]);
        if(mx[k]&&endpos[k]) pre[endpos[k]-mx[k]+1]++,pre[endpos[k]+1]--;
    }
    for(re int i=1;i<=n;i++) pre[i]+=pre[i-1];
    for(re int i=1;i<=n;i++) if(!pre[i]) ++ans;
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：splendore (赞：0)

题目要求做一个模式串匹配，解决方案很多，但最好写的还得是 hash。

值得注意的是，求的是换不了的瓷砖数，直接求不好求，所以要套上一个差分。

由于本题不卡 hash，所以写最朴素的 hash 即可通过本题。

如果不会 hash 可以先去做一下板子。

预处理出文本串的 hash 值并存放在 $h$ 数组中，然后求出模式串的 hash 值，利用 $h$ 数组求出文本串与模式串等长的子串的 hash 值，分别与模式串的 hash 值比较，如果相同，这一段整体加 $1$（用差分维护），最后求前缀和，如果差分数组 $dif_i$ 为 $0$ 答案加 $1$ 即可。

```
#include<cstdio>
#include<cstring>
using namespace std;
typedef unsigned long long ULL;
const int N=3e5+5;
const ULL p=31;
char s[N];
int dif[N];
ULL h[N],pw[N];
int main(){
	int n,m;
	scanf("%d%s%d",&n,s+1,&m);
	pw[0]=1;
	for(int i=1;i<=n;++i){
		h[i]=h[i-1]*p+s[i];
		pw[i]=pw[i-1]*p;
	}
	for(int i=1;i<=m;++i){
		scanf("%s",s);
		int len=strlen(s);
		ULL t=0;
		for(int j=0;j<len;++j)t=t*p+s[j];
		for(int j=len;j<=n;++j){
			if(h[j]-h[j-len]*pw[len]==t){
				++dif[j-len+1];
				--dif[j+1];
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i){
		dif[i]+=dif[i-1];
		if(!dif[i])++ans;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Cells (赞：0)

## 题意

题意不是很清晰，其实是把那个街道上和瓷砖图案相等的字串全部认为是好的，不能被覆盖的叫做不好的。

## 思路

想不出正解先打暴力。

匹配问题最好写的无疑是哈希，不会取出一段字符串哈希值的同学可以看这篇 [文章](https://www.acwing.com/solution/content/205524/)。

我们每次匹配，若是成功则暴力打上标记，然后跳到成功的字符串的末尾，继续匹配。

时间复杂度 $\Theta(nm)$，对于四秒的时限还是比较卡的，我们尝试去优化常数。

考虑到在长度较小的时候匹配次数会较多，因为跳的不多，但是由于打标记的原因，有用的字符串会比较少，所以离线下来去重。

然后我们尝试优化打标记的过程，不使用 `bitset`，发现多次区间的修改，只有一次的查询，这时想到用树状数组，但实际上只需要使用它的内核差分数组。

对于每个文本串中的字符，只匹配开头是这个字符的模式串，也就是对模式串按照第开头字母进行分类。

最后，我们可以对每一类按长度从大到小排序，因为长度大的一定可以覆盖长度小的标记。

## Code

```c++
//# pragma GCC optimize("Ofast")
# include <bits/stdc++.h>
# define fr front
# define il inline
# define fir first
# define sec second
# define vec vector
# define it iterator
# define pb push_back
# define lb lower_bound
# define ub upper_bound
# define all(x) x.begin(), x.end()
# define mem(a, b) memset(a, b, sizeof(a))

# define lc (t[p].l)
# define rc (t[p].r)
# define ls(x) (x << 1)
# define rs(x) (x << 1 | 1)
# define lson ls(p), l, mid
# define rson rs(p), mid + 1, r

# define sqr(x) ((x) * (x))
# define bpc __builtin_popcount
# define lowbit(x) ((x) & (-(x)))
# define geti(x, i) (((x) >> (i)) & 1)
# define set1(x, i) ((x) | (1 << (i)))
# define set0(x, i) ((x) & (~(1 << (i))))

# define debug1(x) cerr << #x << " = " << x << " "
# define debug2(x) cerr << #x << " = " << x << "\n"
# define bug cerr << "--------------------------\n"

# define each1(i, x) for(auto (i) : (x))
# define each2(i, x) for(auto (&i) : (x))
# define rep(i, a, b) for(int i = (a); i <= (b); ++ i)
# define pre(i, a, b) for(int i = (a); i >= (b); -- i)
# define G(i, h, u, ne) for(int i = (h[(u)]); i; i = (ne[(i)]))
# define reps(i, a, b, c) for(int i = (a); i <= (b); i += (c))
# define pres(i, a, b, c) for(int i = (a); i >= (b); i -= (c))
using namespace std;

using DB = double;
using LL = long long;
using LDB = long double;
using PII = pair<int, int>;
using ULL = unsigned long long;

const int N = 3e5 + 10, M = 5e3 + 10, P = 131;
const int INF1 = 0x3f3f3f3f, INF2 = INT_MAX;
const LL INF3 = (LL)1e18, INF4 = 0x3f3f3f3f3f3f3f3f, INF5 = LLONG_MAX;

int n, m, len, sum, ans;
int cnt[N];
ULL val;
ULL h[N], p[N];

char s[N], str[M];

vec<pair<int, ULL>> a[30];

ULL query(int l, int r){
	return h[r] - h[l - 1] * p[r - l + 1];
}

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	cin >> n;
	
	cin >> s + 1;
	
	p[0] = 1;
	rep(i, 1, n){
		h[i] = h[i - 1] * P + s[i];
		p[i] = p[i - 1] * P;
	}
	
	cin >> m;
	
	while(m --){
		cin >> str + 1;
		val = 0;
		len = strlen(str + 1);
		rep(i, 1, len) val = val * P + str[i];
		a[str[1] - 'a' + 1].pb({len, val});
	}
	
	rep(i, 1, 26) sort(all(a[i]), greater<pair<int, ULL>>()), a[i].erase(unique(all(a[i])), a[i].end());//分类去重
	
	rep(i, 1, n){
		each2(tmp, a[s[i] - 'a' + 1]){//只枚举这一类
			len = tmp.fir, val = tmp.sec;
			int j = i + len - 1;
			if(j > n) continue;
			if(query(i, j) == val){
				cnt[i] ++;
				cnt[j + 1] --;
				break;//覆盖了
			}
		}
	}
	
	rep(i, 1, n) sum += cnt[i], ans += (!sum);
	
	cout << ans;
	
	return 0;
}
```

當月光灑在我的臉上，我想我就快變了模樣…………

---

## 作者：_ctz (赞：0)

[blog](https://ctz45562.github.io/2019/07/09/洛谷-P4595-【-COCI2011-2012-5-POPLOCAVANJE】/)

卡空间的$AC$自动机板子题。不会什么~~奇技淫巧~~于是选择了线性空间的$SAM$。

显然要对母串造$SAM$，把模式串在$SAM$跑一遍。如果一个模式串在节点$i$停下，它就能和所有属于$endpos_i$的位置匹配。

维护一个$ma_i$表示在节点$i$停下的最长的模式串长度。每个节点给区间$[\max\{pos-ma_i+1,1\},pos] (pos\in endpos_i)$加$1$。某个位置大于$0$说明可以修补，差分即可。

当然我们并不需要对每个节点都操作。一个点的$endpos$都来自于$parent\ tree$的子树，把$ma$推下去在叶子结点操作即可。

一开始开的$map$，不过额外空间开销不小还是$M$了，于是~~厚颜无耻地~~开数组靠动态内存$A$了。要没有动态内存的话。。。也许要手写平衡树？

代码：
``` cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <map>

#define maxn 600005
#define inf 0x3f3f3f3f

using namespace std;

inline int read(){
    int x=0,y=0;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')y=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return y?-x:x;
}
#define son(x,y) son[x][y]
int son[maxn][26],fa[maxn],len[maxn],ma[maxn],sum[maxn],pos[maxn],cur[maxn],tax[maxn],all,num,last=1,cnt=1;
char s[maxn];
inline void modify(int l,int r){
    ++sum[l],--sum[r+1];
}
void insert(int c){
    int p=last,ne=last=++cnt;
    pos[ne]=len[ne]=len[p]+1;
    while(p&&!son(p,c))son(p,c)=ne,p=fa[p];
    if(!p)fa[ne]=1;
    else {
        int q=son(p,c);
        if(len[q]==len[p]+1)fa[ne]=q;
        else {
            int sp=++cnt;
            memcpy(son[sp],son[q],sizeof son[q]);
            len[sp]=len[p]+1,fa[sp]=fa[q],fa[q]=fa[ne]=sp;
            while(p&&son(p,c)==q)son(p,c)=sp,p=fa[p];
        }
    }
}
int main(){
    int n=read(),m,t,node,ans=0;
    scanf("%s",s+1);
    for(register int i=1;i<=n;++i)insert(s[i]-'a');
    for(register int i=1;i<=cnt;++i)++tax[len[i]];
    for(register int i=1;i<=n;++i)tax[i]+=tax[i-1];
    for(register int i=1;i<=cnt;++i)cur[tax[len[i]]--]=i;
    t=read();
    while(t--){
        scanf("%s",s+1),m=strlen(s+1),node=1;
        for(register int i=1;i<=m&&node;++i)node=son(node,s[i]-'a');
        if(node)ma[node]=max(ma[node],m);
    }
    for(register int i=2;i<=cnt;++i){
        t=cur[i];
        ma[t]=max(ma[t],ma[fa[t]]);
        if(ma[t]&&pos[t])modify(max(pos[t]-ma[t]+1,1),pos[t]);
    }
    for(register int i=1;i<=n;++i){
        sum[i]+=sum[i-1];
        if(!sum[i])++ans;
    }
    printf("%d\n",ans);
}
```


---

## 作者：wheneveright (赞：0)

## Update: 2021/04/13

修改了一些难受的 $\operatorname{markdown}$ 语法，以及一些排版。


## 题目分析

[题面描述](https://www.luogu.com.cn/problem/P4595)

通过读题可以得知只要尽可能的把地砖铺上去然后再在统计没被铺盖的长度就是答案，所以只要把地砖可以铺的区间找出来，然后再用差分就可以做到，关于匹配字符串有几种算法： KMP 、 AC 自动机 Hash 还有几种其他的但是在这里就只放 Hash 了（~~因为数据范围~~）。

## 想法实现

可能很多人对哈希算法有奇怪的偏见。

但是这确实可以做到，首先来看看为什么这个方法可以做到匹配。

```plain
6
abcabc
2
abca
cab
```    
    
这是其中的一个样例。

首先原先的地面是 `abcabc`。
    
    
那么就可以把这个串转成数字串 `123123`。
    
   
它已经是个数字了，于是就可以把它当成 $prime$ 进制数（$prime$ 应该是一个大于 $26$ 的质数），然后就可以只用一个整形变量就可以把它的十进制数存下来了。

$$\sum_{i = 1}^n a_i \times prime ^ {n - i +1}$$

举个例子，在样例中，当 $prime$ 为 $31$ 时应该是：

$$1\times 31^6+2\times 31^5+3\times 31^4+1\times 31^3+2\times 31^2+3\times 31^1$$

这样就完成了字符串向数字的转换。

观察这个式子，你会发现它好像会超出普通整形的范围。

这个时候你应该打开一个 Cpp-IDE，然后输入几个数字试一下，之后可以得出结论：**同样的数字乘以同样的数字的结果，无论有没有超出整形上限都是一样的！**

如代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
	int x=rand()*100000+rand(), y; y=x;
	cout<<x<<' '<<y<<endl;
	x*=31;
	cout<<x<<' '<<y<<endl;
	y*=31;
	cout<<x<<' '<<y<<endl;
	return 0;
}

```

在第三次输出的数字还都是一样的。

所以可以证明 Hash 是可行的。


## 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
const int prime[2] = {37,31};
const int maxn=300005;
int N,M,Ans;
int E[maxn],key[3][maxn],pw[3][maxn];
char s[maxn];
int main(){
	scanf("%d%s",&N,s+1);
	for(int i=0;i<=1;i++)pw[i][0]=1;
	for(int i=1;i<=N;i++)
	for(int j=0;j<=1;j++){
		key[j][i]=key[j][i-1]*prime[j]+s[i];
		pw [j][i]=pw [j][i-1]*prime[j];
	}
	//构造初始的 Hash 数组，取双乘数不容易撞车
	scanf("%d",&M);
	for(int i=1;i<=M;i++){
		scanf("%s",s);
		int l=strlen(s),kp[2]={0,0};
		for(int j=0;j<l;j++)
		for(int k=0;k<=1;k++) kp[k]=kp[k]*prime[k]+s[j];
		for(int j=l;j<=N;j++){
			bool checker = true;
			for(int k=0;k<=1;k++){
				int w=key[k][j]-key[k][j-l]*pw[k][l];
				if (w!=kp[k]) checker=false;
			}
			if(checker)E[j-l+1]++,E[j+1]--;
		}
		//对于每一个字符串的计算
	}
	int now=0;
	for (int i=1;i<=N;i++) now+=E[i],Ans+=(not now);
	printf("%d\n",Ans);
	return 0;
}
```

至此，这道题解决完毕~~~

完结撒花

---

## 作者：GNAQ (赞：0)

考虑一个母串的 SAM

考虑覆盖一个子串实际上是覆盖母串一个前缀的后缀

如是我们考虑所有对应的“一个前缀的后缀”,在 SAM 上是对应着若干结点。并且这些节点通过**后缀链接**构成一颗（原后缀连接树的子）树，并且树根是 “（从前向后第一个匹配的子串的末尾）做结尾的前缀”代表的结点。

很啰嗦了。其实这个点就是把匹配串丢进去从根转移，转移到匹配串末尾时对应的结点。

给这个结点维护一个标记表示这个结点对应前缀最长被覆盖了多少

每次丢匹配串进去走到末尾，并更新标记。

最后建出后缀连接树，把标记下推到子树内的所有结点。

然后我们考虑把母串丢进去跑一遍，对于每个位置对应的结点，假设位置是 $i$ ，这个位置的标记值是 $v$ ，那么我们让答案数组的 `ans[i-v+1]` .. `ans[i]` 都置为 $1$ 即可。

最后扫一遍求得答案

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
#include<iterator>
#include<algorithm>
#include<cstdlib>
#include<map>
#include<set>
#include<vector>
#include<queue>
using namespace std;
typedef long long ll;
typedef ostream_iterator<int> os_iter_int;

int n,m;
short ans[300010];
char chr[300010],ch2[5010];

template<typename inp_t>
void readx(inp_t& x)
{
	x=0; int k=1; char ch=0;
	while (ch<'0' || ch>'9') { ch=getchar(); if (ch=='-') k=-1; }
	while (ch>='0' && ch<='9') { x=x*10+ch-'0'; ch=getchar(); }
	x*=k;
}

namespace SAM
{
	#define CH(a,b) node[a].ch[b]
	
	struct SAM_Node
	{
		int maxs,ch[27],suf;
		short maxm;
		SAM_Node(){}
	}node[600010];
	int samsiz=1,end=1;
	
	void Append(int c)
	{
		SAM_Node& now=node[++samsiz]; int pos=end;
		
		now.maxs=node[end].maxs+1; end=samsiz;
		for (;pos && !CH(pos,c);pos=node[pos].suf)
			CH(pos,c)=samsiz;
		
		if (!pos)
			now.suf=1;
		else if (node[pos].maxs+1==node[CH(pos,c)].maxs)
			now.suf=CH(pos,c);
		else
		{
			int pre=CH(pos,c);
			SAM_Node& N=node[++samsiz],& O=node[pre];
			
			copy(O.ch+1,O.ch+27,N.ch+1);
			N.suf=O.suf; N.maxs=node[pos].maxs+1;
			O.suf=now.suf=samsiz;
			
			for (int i=pos;CH(i,c)==pre;i=node[i].suf)
				CH(i,c)=samsiz;
		}
	}
	
	struct ed { int pre,to; } edge[600010];
	int at=1,ptr[600010];
	void Is(int fx,int tx)
	{
		at++;
		edge[at].pre=ptr[fx];
		edge[at].to=tx;
		ptr[fx]=at;
	}
	void BuildTree()
	{
		for (int i=2;i<=samsiz;i++)
			Is(node[i].suf,i);
	}
	
	void Match(char* str,short len)
	{
		int now=1;
		for (int i=1;i<=len;i++)
			now=node[now].ch[str[i]-'a'+1];
		node[now].maxm=max(node[now].maxm,len);
	}
	
	void DFS(int now,short maxv)
	{
		node[now].maxm=max(node[now].maxm,maxv);
		for (int v=ptr[now];v;v=edge[v].pre) 
			DFS(edge[v].to,node[now].maxm);
	}
	
	void Cover(char* str,int len)
	{
		int now=1;
		for (int i=1;i<=len;i++)
		{
			now=node[now].ch[str[i]-'a'+1];
			ans[i-node[now].maxm+1]+=1;
			ans[i+1]-=1;
		}
		for (int i=1;i<=len;i++) ans[i]+=ans[i-1];
	}
	
	#undef CH
};

int main()
{
	readx(n);
	scanf("%s",chr+1);
	for (int i=1;i<=n;i++) SAM::Append(chr[i]-'a'+1);
	SAM::BuildTree();
	
	readx(m);
	for (int i=1;i<=m;i++)
	{
		scanf("%s",ch2+1);
		int len=strlen(ch2+1);
		SAM::Match(ch2,len);
	}
	SAM::DFS(1,0);
	SAM::Cover(chr,n);
	
	int tans=0;
	for (int i=1;i<=n;i++) tans+=(!ans[i]);
	printf("%d\n",tans);
}
```

---

