# [USACO07FEB] The Cow Lexicon S

## 题目描述

很少有人知道，奶牛们有自己的字典，包含 W（1 ≤ W ≤ 600）个单词，每个单词最多包含 25 个字符，范围为 'a'..'z'。它们的“牛语”系统基于哞声，不是很准确；有时它们会听到一些没有意义的词。例如，Bessie 曾收到一条信息“browndcodw”。结果发现，原本的信息是“browncow”，其中两个字母“d”是来自其他地方的噪音。奶牛们希望你帮助它们解码收到的信息（也只包含字符 'a'..'z'），长度为 L（2 ≤ L ≤ 300），信息有些混乱。特别是，它们知道信息中有一些多余的字母，它们希望你确定必须删除的最少字母数量，以使信息成为字典中的单词序列。

## 说明/提示

感谢 @ws_fuweidong 提供完整题面。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6 10
browndcodw
cow
milk
white
black
brown
farmer```

### 输出

```
2```

# 题解

## 作者：xlxl (赞：12)

## 顶重要的东西：dp[i] 表示前i个字符去掉多少个为最优解

------------
### 初始值：dp[i]=i;(1~n)


------------
### 目标值：dp[len]


------------
扔代码（有注释）~~

------------
```
#include<bits/stdc++.h> 
using namespace std;
int n,len1,dp[310];
char s[310],c[610][310];
int main(){
    cin>>n>>len1>>s+1;
	//输入:字典词数n   交流长度len1   交流语言s+1 
    for(int i=1;i<=n;i++)
		cin>>c[i]+1;
	//输入字典内容
	//注意！！字符串从0开始 
    for(int i=1;i<=len1;i++){//遍历交流语言 
        dp[i]=i;//全去掉一定可以 
        for(int j=1;j<=n;j++){//遍历字典内容 
            int len2=strlen(c[j]+1);//取字典中每一个词的长度 
            int cnt=0,k;
            //cnt删去个数清零 
            for(k=i;k>=1;k--){//从后往前遍历字典是否相符 
                if(c[j][len2]==s[k])//判断 
					len2--;
                else 
					cnt++;//计数器 
                if(len2==0)//这个词结束 
					break;
            }
            if(k!=0)//这个词结束（以防止切一半） 
				dp[i]=min(dp[i],dp[k-1]+cnt);//更新dp值 
        }
    }
    cout<<dp[len1];
    return 0;
}
```
就这样。。没了（~~感觉很简单~~）

------------
真那样你就不会看到我的题解了^~^

---------
最后一句话————poj3267见.BYE

---

## 作者：Wider (赞：5)

看到这道题，首先想到的是乘积最大、添加号之类的动态规划，于是便有了一种思路。

设状态

F[i]为要使母串前i位匹配字典，所需删除的最少的字母数。

G[a,b]为母串中使从第a到第b位的子串包含字典中的词最长，所需删除的最少的字母数

状态转移方程

F[i]=Min { F[k] + G[k+1,i] } (0<=k<=i-1) 

求F[L]的时间复杂度为O(L^2)，关键在于求G[a,b]。

求G[a,b]只有O(L^2\*W)的算法，即枚举每种可能的(a,b)，并对字典中W个单词每个进行匹配，找出包含最长的单词长度为l，G[a,b]=b-a+1-l。

有两组数据会超时。

在上述算法的基础上，会发现大量的枚举是冗余的。我们不改变状态，改变状态转移策略即可，正向递推。

由当前状态F[i]向后可以直接推出，F[i+1]，如果F[i+1]<F[i]+1。另外从第i位开始向后找到序列，使该序列包含字典中的某个单词，序列长度-单词长度就是应当删除的字母数量，记为Space，序列的末尾记为Pos，则有F[Pos]=F[i]+Space，如果F[i]+Space<F[Pos]。

状态转移方程

F[Pos]=Min{ F[i]+Space , F[Pos] } 

F[i+1]=Min{ F[i+1] , F[i]+1 } 

时间复杂度为O(L^2\*W)



```cpp
 #include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
FILE *in = fopen("lexicon.in", "r"), *out = fopen("lexicon.out", "w");
char data[2000];
char words[2000][100];
int w,n;
int best[2001];
void tryword(int pos, int wnum)
 {
    int i,p=pos,t=0;
    for (i=0;i<strlen(words[wnum]);i++)
    {
        while (data[p]!=words[wnum][i])
        {
            p++;t++;
            if (p>=n) return;
        } p++;
    }
    if (best[pos]+t<best[p]) best[p]=best[pos]+t;
}
int main(void)
 {
    int i,j;
    fscanf(in,"%i %i",&w,&n);
    i=0; char c;
    for (i=0;i<n;i++)
    {
        fscanf(in,"%c",&c);
        while (!isalpha(c)) fscanf(in,"%c",&c);
        data[i]=c;
    } data[i]='\0';
    fscanf(in,"%c",&c);
    for (i=0;i<w;i++) fscanf(in,"%s",&words[i][0]);
    for (i=0;i<=n;i++) best[i]=i;
    for (i=0;i<n;i++)
    {
        for (j=0;j<w;j++)
            if (i+strlen(words[j])<=n)
                if (data[i]==words[j][0])
                    tryword(i,j);
        if (best[i]+1<best[i+1]) best[i+1]=best[i]+1;
    }
    fprintf(out,"%i\n",best[n]);
    fclose(in); fclose(out); return 0;
}
```

---

## 作者：crashed (赞：4)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[点这里](https://www.luogu.org/blogAdmin/article/new)看题目。
# 分析
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;暴力$DP$题。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;很容易想到如下的状态：  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$DP(i)$：前$i$个字母需要删除的最少的字母数量。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;转移就是枚举哪个单词最后被匹配。然后我们一直在字符串中从后往前枚举字母，在原串中从$i$往前找字母，并且在这个过程中统计出需要删除的字母数量。如果我们发现当前单词可以被匹配到，那么就进行转移。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;理论时间复杂度是$O(WL^2)$，但实际运行速度比较快（$76ms$）。  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;另外，可以用一个$pre[i][ch]$记录在第$i$个字母之前的第一个$ch$的位置，这样可以在找字符的时候做到$O(len)$的时间，总时间就是$O(L\times \sum_{i=1}^nlen(word_i))$。
# 代码
```cpp
#include <cstdio>
#include <cstring>

const int MAXW = 605, MAXL = 305, MAXLEN = 30;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

char dict[MAXW][MAXLEN];
char str[MAXL];
int l[MAXW];
int DP[MAXL];
int W, L;

int id( const char s )
{
	return s - 'a' + 1;
}

int main()
{
	read( W ), read( L );
	scanf( "%s", str + 1 );
	for( int i = 1 ; i <= W ; i ++ ) scanf( "%s", dict[i] + 1 ), l[i] = strlen( dict[i] + 1 );
	for( int i = 0 ; i <= L ; i ++ ) DP[i] = i;
	//最开始，每个位置最多需要i次操作，将整个串删成空串。
	for( int i = 1 ; i <= L ; i ++ )
		for( int j = 1 ; j <= W ; j ++ )
		{
			int cur = i, k = l[j], cnt = 0;
			for( ; cur > 0 && k ; cur --, k -- )
				while( str[cur] ^ dict[j][k] && cur > 0 ) 
					cur --, cnt ++;
            //依次找字符并且算出需要删除的数量
			if( ! k ) DP[i] = MIN( DP[i], DP[cur] + cnt );
            //如果可以找到才能转移
		}
	write( DP[L] ), putchar( '\n' );
	return 0;
}
```

---

## 作者：The_Dark_Knight (赞：4)

确实，这道题改了我不少的时间，主要是数组的一些小问题，但所幸最后还是AC，并且代码不长，也许这是pascal为数不多的一个优势吧。这道题果然还是想到用动规来做，f[i]记录i之后一共要删除多少个数。我们从后往前做，转移状态。找到要删除多少个数也不难。对于当前i来说，如果给出的字典里面有某一个单词的开头与i位置的字符相同，则往后找，找出包含了这个单词的最短长度，用这个长度减去单词长度则可得到要删除的数目。转移方程则为f[i]:=min(f[i],f[k+1]+k-i-length(s[j]));k-i即是前面提到的最短长度。

```cpp
uses math;
var f:array[0..1000] of longint;
    s:array[1..1000] of ansistring;
    i,j,k,w,l,m,n,p,t,kk:longint;ss:ansistring;
begin
    //assign(input,'P2875.in');reset(input);
    readln(w,l);
    readln(ss);
    for i:=1 to w do
      readln(s[i]);
    for i:=l-1 downto 0 do
    begin
        f[i]:=f[i+1]+1;
        for j:=1 to w do
        begin
          if (length(s[j])<=l-i)and(ss[i+1]=s[j][1]) then
          begin
                p:=1;
                for k:=i+1 to l do
                begin
                    if ss[k]=s[j][p] then inc(p);
                    if p=length(s[j])+1 then begin
                    f[i]:=min(f[i],f[k]+(k-i-length(s[j])));
                    break;
                    end;
                end;
          end;
        end;
    end;
    writeln(f[0]);
end.

```

---

## 作者：quarmer (赞：3)

### 简化题意
给出一个长度为 $L$ 的字符串， 再给出 $W$ 个单词，问至少从 $L$ 中去掉多少字符才能由若干个单词拼成，单词使用可以重复。

### 思路

这种题一看就是 DP，考虑 $f_{i}$ 为在 $L$ 中前 $i$ 个字符最少需要删除多少个字符。显然的， $f_{i}$ 可以由 $f_{i - 1} + 1$ 得到。假设删除后拼成这句话的所有单词中最后一个单词为 $W_{j}$，那么方程显然 

$f_{i} = \min(f_{i - 1} +1, f_{i - len} + (len - |W_{j}|)$

其中，$len$ 表示 $L$ 中从第 $i$ 个字符往前数 $len$ 个字符，使子串 $L_{i - len +1} - L_{i}$ 可以通过删除单词拼成 $W_{j}$ 的 $len$ 的最小值。此时的 $f_{j}$ 就可以等于前 $i - len$ 个字符要删除字符的最小值与 $i + len - 1 $ 之后要拼成 $W_{j}$ 要删除字符的最小值之和。

至于求 $len$ 可以从 $L$ 的第 $i$ 个字符与 $W_{j}$ 的最后一个字符向前一一匹配，具体实现见代码。

### 代码：

```cpp
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <set>
using namespace std;
#define int long long
int f[305] ;
int n, m ;
string s ;
string d[605] ;
signed main() {
	cin >> n >> m ;
	cin >> s ;
	for(int i = 1 ; i <= n ; i++) cin >> d[i] ;
	memset(f, 0x3f, sizeof(f)) ; //要求最小值，初始化成INF
	f[0] = 0 ; //边界 f[0] = 0 
	for(int i = 1 ; i <= m ; i++) {
		f[i] = f[i - 1] + 1 ;
		for(int j = 1 ; j <= n ; j++) {
			int r1 = i, r2 = d[j].size() ;//指针的思想
			int flag = 1 ;//记录是否可以匹配成功
			while(r1 && r2) {
				if(d[j][r2 - 1] == s[r1 - 1]) r1--, r2-- ; //若匹配成功，各向前移一位
				else r1-- ; // 不然 把母串指针前移一位
				if(!r2) flag = 0 ; //匹配成功
			}
			if(!flag) f[i] = min(f[r1] + i - r1 - (int)d[j].size(), f[i]) ; // 若匹配成功，转移
		}
	}
	cout << f[m] ;
	return 0 ;
}

```

---

## 作者：Wsy_flying_forever (赞：3)

# 题目大意： 
给你一个主串以及若干个子串，求最少需要删除几个字母，使得主串能由一些子串组成。

# 思路： 
求最值问题，我们可以联想到用dp求解，最直接的状态就是，设 $dp_i$ 表示主串的前i位最少需要删除几个字母。

方程显然：$dp_i$=$\min(dp_{i-1}+1,dp_k+(i-k-len_j))$

（其中，$k$ 表示从主串 $[k+1...i]$ 的区间中删掉一些字符能得到子串j的最大左端点 -1，此时(显然此时的代价就为 区间长度-子串 $j$ 的长度 )）

代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=1010;
char ch[maxn];
int n,len;
string s[maxn];
int dp[maxn];
int main(){
	scanf("%d%d",&n,&len);
	for (int i=1;i<=len;i++)
	  cin>>ch[i];
	for (int i=1;i<=n;i++) 
	  cin>>s[i];
	for (int i=1;i<=len;i++){
		dp[i]=dp[i-1]+1;
	    for (int j=1;j<=n;j++)
	  	{
	  		int l=s[j].length()-1,l1=i;
	  		while (l>=0 && l1>=1){
	  		    if (s[j][l]==ch[l1]) l--,l1--;
				  else l1--;	
			}
			if (l==-1) dp[i]=min(dp[i],dp[l1]+i-l1-int(s[j].length()));
		}
	}
	cout<<dp[len];
	return 0;
}
```



---

## 作者：majt (赞：3)

发一发三维dp：

dp[i][j][k] ，表示： 匹配第i个，凑好第j个词的第k位；

于是由定义很容易想到

if(ch[i]==dic[j][k]) dp[i][j][k]=dp[i-1][j][k-1];

else     dp[i][j][k]=dp[i-1][j][k]+1;

但要注意k=0时表示的情况——不选第i位

于是有朴素的处理方式

```cpp
   if(k==0){
        for(int o=1;o<=w;++o){
            dp[i][j][0]=min(dp[i][j][0],dp[i-1][o][len[o]]+1);
            dp[i][j][0]=min(dp[i][j][0],dp[i-1][o][0]+1);
        }
    }
```
但实际上这个for可以用数组存i-1的最小值（已经得出）来优化掉（见代码）
由于k=0的特殊性，k=1时也需要单独讨论（类似k=0，不再赘述）


代码（另附几组数据）：





        
    
```cpp
#include<cstdio>
#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;
#define ll long long
int getint() {
    int x=0,f=1;
    char ch=getchar();
    while(ch==' '||ch=='\n') {
        ch=getchar();
    }
    while(ch<'0'||ch>'9') {
        f=-f;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
const int inf=0x3fffffff;
const int MAXN=1000;
char dic[MAXN][30],len[MAXN],tmp[30];
char ch[310];
int dp[310][MAXN][30];//dp[i][j][k]  匹配第i个，凑好第j个词的第k位 
int w,l,ans=inf;
int min0[MAXN],minlen[MAXN];
int main(){
    w=getint(),l=getint();
    for(int i=1;i<=l;++i){
        ch[i]=getchar();
        while(ch[i]==' '||ch[i]=='\n'){
            ch[i]=getchar();
        }
    }
    for(int i=1;i<=w;++i){
        memset(tmp,0,sizeof(tmp));
        scanf("%s",tmp+1);
        len[i]=strlen(tmp+1);
        for(int j=1;j<=len[i];++j){
            dic[i][j]=tmp[j];
        }
    }
    memset(dp,0x3f,sizeof(dp));
    memset(min0,0x3f,sizeof(min0));
    memset(minlen,0x3f,sizeof(minlen));
    for(int j=1;j<=w;++j){
        if(ch[1]==dic[j][1]){
            dp[1][j][1]=0;
            if(len[j]==1){
                minlen[1]=0;
            }
        }
        dp[1][j][0]=1;
    }
    min0[1]=1;
    for(int i=2;i<=l;++i){
        for(int j=1;j<=w;++j){
            for(int k=0;k<=len[j];++k){
                if(k==0){
                    dp[i][j][0]=min(dp[i][j][k],min0[i-1]+1);
                    dp[i][j][0]=min(dp[i][j][k],minlen[i-1]+1);
                    min0[i]=min(min0[i],dp[i][j][0]);
                    continue;
                }
                if(k==1&&ch[i]==dic[j][1]){
                    dp[i][j][1]=min(dp[i][j][1],minlen[i-1]);
                    dp[i][j][1]=min(dp[i][j][1],min0[i-1]);
                    continue;
                }
                if(ch[i]==dic[j][k]){
                    dp[i][j][k]=dp[i-1][j][k-1];
                }else{
                    dp[i][j][k]=dp[i-1][j][k]+1;
                }
                if(k==len[j]){
                    minlen[i]=min(minlen[i],dp[i][j][k]);
                }
            }
        }
    }
    for(int j=1;j<=w;++j){
        ans=min(ans,dp[l][j][len[j]]);
        ans=min(ans,dp[l][j][0]);
    }
    cout<<ans<<endl;
}/*
```
3 10
vhiensjvbe

vis
jbe
hiensbe


3 6
ahskec
ask
ah
skec

3 6
ashgsd
agd
hds
as

6 10
browndcodw

cow
milk
white
black
brown
farmer

\*/

---

## 作者：heccc (赞：3)

	开始想的DP，但觉得状态太难设了。
	于是爆搜。用两个简单的最优性剪枝就可以了。
	额，也有可能是数据比较水的缘故，反正跑得不慢。
```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#include<set>
#include<map>
#include<vector>
#define ll long long
#define N 605

using namespace std;
inline int Get() {int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}while('0'<=ch&&ch<='9') {x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}return x*f;}

int w,len;
char s[N],t[N];
int cnt=1,rt=1;
struct trie {
	int ch[30];
	bool f;
}tr[N*50];
void Insert() {
	int v=rt,l=strlen(t+1);
	for(int i=1;i<=l;i++) {
		int j=t[i]-'a';
		if(!tr[v].ch[j]) tr[v].ch[j]=++cnt;
		v=tr[v].ch[j];
	}
	tr[v].f=1;
}
int ans=1e9;
int dis[N][N*30];
int flag=0;
void dfs(int v,int f,int tot) {
	if(f>len) {
		if(tr[v].f) ans=min(ans,tot);
		return ;
	}
	if(ans<=tot) return ;
	if(dis[f][v]<=tot) return ;
	dis[f][v]=tot;
	if(tr[v].ch[s[f]-'a']) dfs(tr[v].ch[s[f]-'a'],f+1,tot);
	if(tr[v].f) dfs(1,f,tot);
	dfs(v,f+1,tot+1);
}
int main() {
	memset(dis,0x3f,sizeof(dis));
	w=Get(),len=Get();
	scanf("%s",s+1);
	for(int i=1;i<=w;i++) {
		scanf("%s",t+1);
		Insert();
	}
	dfs(1,1,0);
	cout<<ans;
	return 0;
}

```

---

## 作者：GUO120822 (赞：2)

这真是道~~大水题~~。

- 思路

拿道题之后，觉得这题肯定是动态规划。于是，就开始想状态。

$dp_i$ 表示前 $i$ 个字符，把它变成牛语的最少删除数。

想一想怎么转移。前面的变成牛语的字符串加上一个单词一定是一个合法牛语。所以我们只要看看结尾是哪个单词，然后配对。

```cpp
for (k=i;k>=1;k--)
{
	if (a[k]==b[j][len]) len--;
	else sum++;
	if (!len) break;
}
```

$sum$ 表示配对失败的个数，

如果配对成功，那么就有 $dp_i=\max(dp_i,dp_{k-1}+sum)$。

$k-1$ 就是配对成功的开头的前一个。最后的结果就是 $dp_n$。

上代码！！

- 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=310,M=610;
int m,n,i,j,k,dp[N],len,sum;
char a[N],b[M][N];
int main()
{
	scanf("%d%d%s",&m,&n,a+1);
	for (i=1;i<=m;i++) scanf("%s",b[i]+1);
	for (i=1;i<=n;i++)
	{
		dp[i]=i;
		for (j=1;j<=m;j++)
		{
			sum=0;
			len=strlen(b[j]+1);
			for (k=i;k>=1;k--)
			{
				if (a[k]==b[j][len]) len--;
				else sum++;
				if (!len) break;
			}
			if (k) dp[i]=min(dp[i],dp[k-1]+sum);
		}
	}
	printf("%d",dp[n]);
	return 0;
}
```

---

## 作者：_ANIG_ (赞：2)

## 题意简述

在一个字符串中删掉最少的字母使这个字符串能由词典里若干个字符串拼接而成。

## 确定状态

$f_i$ 表示母串的前 $i$ 个字符能由字典的单词拼成所要删除的最少字母数。

## 转移方程

分两种情况讨论。

1. 删掉当前的字符。
2. 删掉若干个字母，使其中一个字典中的字符串是当前的后缀。

第一种情况很好想，直接 $f_i=f_{i-1}+1$。

第二种情况要枚举每个单词，即 $f_i=\min(f_p+i-p+1-lth)$。

其中，$lth$ 表示当前枚举的字符串的长度，$p$ 指的是如果当前枚举到的单词要成为母串前 $i$ 项的后缀，当前枚举的单词的第一个字母可以在的最靠右的位置。

## 怎样求 $p$

设 $dp_{i,j,k}$ 是第 $j$ 个字符的后 $k$ 项成为母串的前 $i$ 项的后缀时，当前枚举到的单词的第 $k$ 个字母可以在的最靠右的位置。

求 $dp_{i,j,k}$ 时，可以用一个游标 $w$，初始值是 $dp_{i,j,k+1}-1$ 。游标往前走，直到字符匹配成功，即母串的第 $w$ 项等于子串的第 $k$ 项时，游标停止，将 $dp_{i,j,k}$ 更新为 $w$。

当 $w$ 为负数时，即无论如何都无法使第 $j$ 个单词是母串前 $i$ 项的后缀。

## 总代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int w,l;
int f[305],dp[305][605][30];
string s,c[605];
int main(){
	cin>>w>>l;
    cin>>s;
    for(int i=1;i<=w;i++)cin>>c[i];
    for(int i=0;i<l;i++){
    	for(int j=1;j<=w;j++){
    		dp[i][j][c[j].size()+1]=i+1;
    		for(int k=c[j].size();k>=1;k--){
    			int nw=dp[i][j][k+1];
    			nw--;
    			while(s[nw]!=c[j][k-1]&&nw>=0)nw--;
    			dp[i][j][k]=nw;
			}
		}
	}
	for(int i=0;i<l;i++){
		f[i]=f[i-1]+1;
		for(int j=1;j<=w;j++){
			if(dp[i][j][1]>=0)f[i]=min(f[i],f[dp[i][j][1]-1]+(i-dp[i][j][1]-(int)c[j].size()+1));
		}
	}
	cout<<f[l-1];
}
```


---

## 作者：dark_moon (赞：2)

分析：

首先在读 [题](https://www.luogu.com.cn/problem/P2875) 完毕后，发现暴力的做法也不是很好做，再回想关于字符串的种种问题，发现没有什么字符串的模型可以使用，尽管模仿 [电子字典](https://www.luogu.com.cn/problem/P4407) 似乎可行，但仔细一想，对蓝题这么做是在没有必要，并且确实想不出一个可行的方案前进，所以向 dp 方面想。

具体方案：

既然有这个方向，就继续思考，设一个简单的状态，$f_i$ 就指话说到 $i$ 时，最少删去的字母个数，然后就可以想状态转移了。

显而易见的，如果枚举到 $i$ 时，我们不选这一个字母，即删掉这个字母，就简单的转移为 $f_i = f_{i-1} + 1$，难点在于如果考虑不删这个字母，应该怎么转移。

我们思考一下，如果不删这个字母，肯定是因为加上了它，可以与前面的某些字母组成一个单词，比如 $\texttt{abcd}$，我们加入一个 $e$，同时有一个单词 $\texttt{bde}$，那么转移时就是 $f_5 = f_{5 - 4} + 1$，其中 $5$ 代表枚举到第 $5$ 个；$4$ 表示我们选了一个长度为 $3$ 的单词，而且扔掉了 $1$ 个字母，所以是 $3 + 1$；$1$ 表示我们在选那个单词时扔掉了 $1$ 个字母。

所以策略就自然而然跳了出来，我们可以枚举每一个单词，看看以选的这个字母为结尾时，需要多少个字母才能组出来（比如上面的例子，字母是 $\texttt{e}$，单词是 $\texttt{bde}$，那么需要 $\texttt{bcde}$ 这 4 个字母才能组成，其中就包括一个被扔掉的），并在过程中判断这个单词是否可选。设 $le_j$ 为选了第 $j$ 个单词后需要把指针指在哪里（比如上面的例子，指针指在了 $a$ 后面的 $b$），$sum$ 表示中间扔掉了多少字母，状态转移为 

$f_i=\min\{f_i,f_{le-1}+sum\}$

接下来看如何求 $le$ 和 $sum$，可以同时设两个变量 $i$ 和 $j$，分别是母串中枚举到的地方和我们枚举尝试的单词的末尾，设母串是 $s$，单词是 $c$，每次比较 $s_i$ 和 $c_j$，若相等，就 $j$ $\leftarrow$ $j+1$，否则，$sum$ $\leftarrow$ $sum +1$，并且无论如何都使 $i$ $\leftarrow$ $ i+1$，这样，最后 $i$ 的位置就是 $le$。

代码如下，仅供参考（代码中单词是 $s$，母串是 $c$）：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, l, f[305], len[605];
char c[305];
string s[605];
int aaa(int x, int y, int &le){
	int j = len[y], sum = 0;
	le = -1;
	for(int i = x; i >= 1; i --){
		if(c[i] == s[y][j])
		j --;
		else
		sum ++;
		if(j == 0){
			le = i;
			break;
		}
	}
	return sum;
}
signed main(){
	scanf("%lld%lld%s", &n, &l, c + 1);
	for(int i = 1; i <= n; i ++){
		cin >> s[i];
		len[i] = s[i].size();
		s[i] = "0" + s[i];
	}
	f[0] = 0;
	for(int i = 1; i <= l; i ++){
		f[i] = f[i - 1] + 1;
		for(int j = 1; j <= n; j ++){
			int le;
			int sum = aaa(i, j, le);
			if(le != -1)
			f[i] = min(f[i], f[le - 1] + sum);
		}
	}
	printf("%lld", f[l]);
	return 0;
}
```
祝各位大佬刷题愉快。

---

## 作者：linyinuo2008 (赞：2)

[原题链接](https://www.luogu.com.cn/problem/P2875)

这题是一道经典的划分型 $\text{DP}$ 题，代码实现有一定难度。

# 1、题目理解

意思是给你一个长度为 $L$ 的字符串与一个字典（字典里的单词数为 $W$ ），问你最少从这个字符串中删几个字母才能使这个字符串完全由字典里的单词组成。

数据范围：

$1 \le W \le 600$ ， $1 \le L \le 300$

# 2、算法实现

状态设计是令 $f_i$ 表示前 $i$ 个字符组成的子串最少要删掉的字符数量。

而对于每一个 $f_i$ ，显然，初始化为 
$$f_i=f_{i-1}+1$$

也就是最坏情况就是直接把这个字符删掉。

然后我们开始遍历整个字典，搜寻哪一个单词能为当前的状态转移。

怎样转移呢？我们就拿`browndcodw`这个词来举个例子。

假设我们现在已经扫到了 $f_{10}$ ，也就是`w`的位置。此时我们开始在字典中搜寻，看有没有哪个字典中的单词是以`w`结尾的，结果发现有一个`cow`。

这里要用到一个 $calc(pos,k)$ 函数来找到这个单词初始位置，$pos$ 是当前的位置（也就是10），搜字典中第 $k$ 个单词（`cow`）。

开始向前搜，目标字符为`cow`的倒数第二个字符，也就是`o`，发现`d`与`o`不匹配，删去，再向前，`o`和`o`匹配上了！目标字符转为`c`，又匹配上了！返回大字符串中`c`所在的位置 $7$ 。

这就是大致上的划分匹配过程，转移方程为：
$$f_i= \min(f_i,f_{now-1}+i-now+1-len_j)$$ 

其中 $now$ 是 $calc(pos,k)$ 的返回值，$len_j$ 为当前匹配字符串的长度。

复杂度 $O(25 \times W \times L)$ 。

# 3、代码

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

const int NR=605;
const int MR=305;

int w,l;
char s[NR][30];
int len[NR];
char t[MR];
int f[MR];//f[j]表示到j位置最少去掉字母数（匹配到j）

int calc(int pos,int k)
{
	if(pos<len[k]) return 0;
	if(t[pos]!=s[k][len[k]]) return 0;
	int num=len[k];
	for(int i=pos;i>=1;i--)
	{
		if(t[i]==s[k][num]) num--;
		if(!num) return i;
	}
	return 0;
}


int main()
{
	cin>>w>>l;
	scanf("%s",t+1);
	for(int i=1;i<=w;i++)
	{
		scanf("%s",s[i]+1);
		len[i]=strlen(s[i]+1);
	}
	for(int i=1;i<=l;i++)
	{
		f[i]=f[i-1]+1;//最多就是直接把这个删掉
		for(int j=1;j<=w;j++)//枚举每一个单词
		{
			int now=calc(i,j);//得到比配到单词位置
			if(now<1) continue;
			f[i]=min(f[i],f[now-1]+i-now+1-len[j]);
		}
	}
	cout<<f[l];
	return 0;
}

```
**若有错误，欢迎指出！**

---

## 作者：Soul_Wanderer (赞：1)

# 题解

## [题目链接](https://www.luogu.com.cn/problem/P2875)

## 题目大意

给你一个主串，再给你一堆子串，问主串最少去掉几个字符可以使它由某几个（也可能是 $0$ 个）子串构成。

## 思路

因为是求最少，很容易联想到动态规划。

定义**状态**：$f_i$ 表示主串的前 $i$ 个字符最少去掉几个字符可以使它由某几个（也可能是 $0$ 个）子串构成。

**状态转移**：$f_i=\min\{f_{k-1}+num\}$。  

其中 $k$ 表示主串前 $i$ 个字符从前往后匹配完某个子串后扫到的左端点，$num$ 表示匹配的过程中由于不一样而删掉的字符个数，具体请见代码。

**初始化**：$f_i=i$，把所有字符都去掉肯定行。

## AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
char ch[310];
char a[610][30];
int f[310];//前i个字符至少去掉的字母数 
int w,l;
signed main()
{
	cin>>w>>l;
	cin>>ch+1;
	for(int i=1;i<=w;i++) cin>>a[i]+1;
	for(int i=1;i<=l;i++){
		f[i]=i;
		for(int j=1;j<=w;j++){
			int len=strlen(a[j]+1);
			int num=0;
			int cnt=0;
			for(int k=i;k>=1;k--){
				if(ch[k]==a[j][len]){
					len--;
				}
				else{
					num++;
				}
				if(len==0){
					cnt=k;
					break;
				}
			}
			if(cnt>0)
				f[i]=min(f[i],f[cnt-1]+num);
                //IAKIOI
		}
	}
	cout<<f[l];
	return 0;
}
```

---

## 作者：信息学carryHarry (赞：1)


### 题意
给定一个包含 $m$ 个单词的词典和一个长度为 $n$ 的字符串 $s$，求出字符串最少删除多少个字符使得剩下的字符串可以用词典中的单词拼接构成。
### 思路
划分DP。需要确定字符串中将哪些子串变为单词。

$dp_i$ 表示前 $i$ 个字符删除字符的最少个数使得剩下字符是一个单词序列。

$g_{i,j}$ 表示将子串 $s_i \ldots s_j$ 变成一个单词需要删除字符的最少个数。

转移时枚举上一个单词的结尾位置，$dp_i = \min_{0 \le j \le i}{dp_j+g_{j+1,i}}$。

预处理 $g_{i,j}$，如果子串里没有单词，$g_{i,j}$ 就为子串长度。可以先枚举每个单词，然后枚举子串区间 $\left [ i,j \right ] $，贪心地看子串中是否有子序列可以是单词，求出 $g_{i,j}$ 的最小值。


---

## 作者：SUNCHAOYI (赞：1)

这道题和 $\texttt{P2432}$ 的题目是一样的。考虑动态规划的作法，设 $dp[i]$ 表示原字符串的前 $i$ 位最少需要删除的字符的数量，显然最后的答案是 $dp[L]$。

对于初始值，因为求最小值，所以先把 $dp[i]$ 均设置为 $+\infty$，同时由转移方程的含义可知 $dp[0] = 0$。然后就是处理单词与文章是否能匹配的核心思路了，设 $dx$ 表示当前匹配到的位置 $i$，$dy$ 表示第 $j$ 个单词的长度 $len[j]$。从 $i$ 与单词的末尾开始，若成功匹配，则 $dx,dy$ 均减一，否则 $dx$ 减一。如果 $dy$ 的值先变为 $0$ 或者 $dx,dy$ 同时变为 $0$，这说明该单词能够在原字符串中匹配；但是如果不能匹配，显然原字符串的第 $i$ 个位置需要被删除。

所以有状态转移方程 $dp[i] = \min (dp[i - 1] + 1,dp[dx] + (i - dx - len[j])$，显然此时的 $dx$ 表示在匹配之后 $dx$ 的值，而不是初始的 $dx = i$。

讲了这么多，再看着代码理解一下叭！

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define init(x) memset (x,INF,sizeof (x))
#define ll long long
#define ull unsigned long long
#define INF 0x3f3f3f3f
using namespace std;
const int MAX = 605;
const int MOD = 1e9 + 7;
inline int read ();
int n,m,dlen[MAX],dp[MAX];
char str[MAX >> 1],cor[MAX][30];	
int main ()
{
	//freopen (".in","r",stdin);
	//freopen (".out","w",stdout);
	n = read ();m = read ();
	scanf ("%s",str + 1);
	for (int i = 1;i <= n;++i)
	{
		scanf ("%s",cor[i] + 1);
		dlen[i] = strlen (cor[i] + 1);//单词的长度
	}
	init (dp);//初始化
	dp[0] = 0;
	for (int i = 1;i <= m;++i)
	{
		dp[i] = dp[i - 1] + 1;
		for (int j = 1;j <= n;++j)//共有 n 个单词，一一匹配
		{
			int dx = i,dy = dlen[j];
			while (dx && dy)//边界条件
			{
				if (str[dx] == cor[j][dy]) --dx,--dy;
				else --dx;
			}
			if (!dy) dp[i] = min (dp[i],dp[dx] + (i - dx - dlen[j]));//成功匹配才能进行状态转移
		}
	}
	printf ("%d\n",dp[m]);//此处为 m 而不是 n 哦！
	return 0;
}
inline int read ()
{
    int s = 0;int f = 1;
    char ch = getchar ();
    while ((ch < '0' || ch > '9') && ch != EOF)
	{
        if (ch == '-') f = -1;
        ch = getchar ();
    }
    while (ch >= '0' && ch <= '9')
	{
        s = s * 10 + ch - '0';
        ch = getchar ();
    }
    return s * f;
}
```

---

