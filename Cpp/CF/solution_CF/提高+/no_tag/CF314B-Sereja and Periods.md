# Sereja and Periods

## 题目描述

设$[s,t]$（$s$为一个字符串，$t$为正整数）为字符串$s$重复$t$次后的新字符串

再设当字符串$s$中删去部分字符后，得到字符串$t$，则称字符串$s$包含$t$

现在Sereja有两个字符串，可以表示为$w=[a,b]$和$q=[c,d]$，求使得$w$包含$[q,p]$的最大的正整数$p$

## 样例 #1

### 输入

```
10 3
abab
bab
```

### 输出

```
3
```

# 题解

## 作者：wsyhb (赞：5)

## 题意简述

记 $[x,n]$ 表示 $n$ 个字符串 $x$ 相接而得的字符串。

现有两个字符串 $w$ 和 $q$，满足 $w=[a,b]$ 和 $q=[c,d]$，求最大的整数 $p$ 使得 $[q,p]$ 是 $w$ 的子序列。

**数据范围**：$|a|,|c| \le 100$，$b,d \le 10^7$

## 分析 + 题解

由于 $[q,p]=[c,pd]$，问题转化为：求最大的 $k$ 使得 $[c,k]$ 是 $w$ 的子序列。（原答案即为 $\lfloor \dfrac{k}{d} \rfloor$）

一个显然的**贪心**策略：从左到右依次扫描 $w$ 并维护 $c$ 的下标 $i$，一旦遇到与 $c_i$ 相同的字符，就令 $i:=i+1$，若之后 $i$ 超出 $c$ 的字符串长度，答案增加 $1$，并令 $i$ 从头开始。

但这样是 $O(|a| \cdot b)$ 的，如何优化呢？

设第 $i$ 个 $c$ 的结束位置为第 $x_i$ 个 $a$ 的第 $y_i$ 个位置，那么必然存在 $i < j$ 且 $y_i=y_j$，此时每 $x_j-x_i$ 个 $a$ 就会出现 $j-i$ 个 $c$，即找到了循环节。

由于循环节长度 $\le |a|$，那么我们可以**暴力找循环节、暴力处理开头和结尾非循环节的部分**，时间复杂度为 $O(|a|^2 \cdot |c|)$。（常数还非常小，轻轻松松最优解）

## 代码

记得要先特判 $c$ 出现了 $a$ 中没有的字符的情况。

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int max_n=100+5;
const int max_m=100+5;
char s[max_n],t[max_m];
const int cnt_letters=26+5;
bool mark[cnt_letters];
typedef pair<int,int> P;
P pos[max_n];
int vis[max_n];
int main()
{
	int a,b;
	scanf("%d%d%s%s",&a,&b,s,t);
	int n=strlen(s),m=strlen(t);
	for(int i=0;i<n;++i)
		mark[s[i]-'a']=true;
	for(int i=0;i<m;++i)
	{
		if(!mark[t[i]-'a'])//特判
		{
			puts("0");
			return 0;
		}
	}
	int x=1,y=0,sz=0;//当前遍历到第 x 个串的第 y 个位置 
	while(1)
	{
		for(int i=0;i<m;++i)
		{
			while(s[y]!=t[i])
			{
				++y;
				if(y==n)
					++x,y=0;
			}
			++y;
			if(y==n)
				++x,y=0;
		}
		--y;
		if(y==-1)
			--x,y=n-1;
		pos[++sz]=P(x,y);
		if(vis[y])
			break;
		vis[y]=sz;
		++y;
		if(y==n)
			++x,y=0;
	}
	int end_pos=vis[y];//前 end_pos 个是开头的非循环节部分 
	for(int i=1;i<=end_pos;++i)
	{
		if(pos[i].first>a)//根本没有出现过完整的循环节 
		{
			printf("%d\n",(i-1)/b);
			return 0;
		}
	}
	int re=a-pos[end_pos].first;//还剩下几个完整的串 
	int cnt=end_pos+(sz-end_pos)*(re/(pos[sz].first-pos[end_pos].first));//开头部分 + 循环节长度 * 完整循环节个数 
	re%=pos[sz].first-pos[end_pos].first;//结尾非循环部分还剩下几个完整的串 
	x=a-re,y=pos[sz].second;
	++y;
	if(y==n)
		++x,y=0;
	while(x<=a)
	{
		bool flag=true;
		for(int i=0;i<m;++i)
		{
			while(s[y]!=t[i]&&x<=a)
			{
				++y;
				if(y==n)
					++x,y=0;
			}
			if(x>a)
			{
				flag=false;//此处要用 flag 标记记录最后一次是否完整出现 
				break;
			}
			++y;
			if(y==n)
				++x,y=0;
		}
		cnt+=flag;
	}
	printf("%d\n",cnt/b);
	return 0;
}
```

---

## 作者：是个汉子 (赞：3)

这里介绍两种做法，感觉都很巧妙。

### Solution 1

观察题面，发现 $|a|,|c|\leq 100$ ，所以可以像 $KMP$ 那样，造一个 $nxt$ 数组，然后再弄一个 $cnt$ 数组。

其中 $cnt_i$ 表示从 $c_i$ 开始匹配，把 $a$ 串扫一遍有几组匹配， $nxt_i$ 表示 $c_i$ 匹配完一个 $a$ 到了 $c$ 的哪一位。

然后从 $1$ 到 $b$ ，每次跳 $nxt$ ， $ans+=cnt$ 即可。

时间复杂度： $O(len_a\cdot len_b)+O(b)=O(b)$  

### 代码1

```c++
#include<bits/stdc++.h>
#define ll long long

using namespace std;
const int N=110;
ll cnt[N],nxt[N],b,d,lena,lenc,ans;
char a[N],c[N];

int main(){
    scanf("%lld%lld%s%s",&b,&d,a,c);
    lena=strlen(a),lenc=strlen(c);
    for(int i=0,x;i<lenc;i++){
        x=i;
        for(int j=0;j<lena;j++)
            if(a[j]==c[x]){
                x++;
                if(x==lenc) cnt[i]++,x=0;
            }
        nxt[i]=x;
    }
    int pos=0;
    for(int i=1;i<=b;i++){
        ans+=cnt[pos];
        pos=nxt[pos];
    }
    printf("%lld\n",ans/d);
    return 0;
}
```

### Solution2

我们用倍增的思想来做题。

弄一个倍增数组 $go$ ，拿 $pair$ 储存。

设 $go_{k,idx(i,j)}$ 为从 $a$ 的第 $i$ 位， $c$ 的第 $j$ 位开始匹配，匹配 $c$ 的 $2^k$ 位之后， $first$ 表示此时两个串上的位置， $second$ 为过了几个 $a$ ，递推数组即可。

二分匹配长度，求得答案。

时间复杂度： $O(len_a\cdot len_b\log(len_a\cdot b))$ 

### 代码2

```c++
#include<bits/stdc++.h>
#define ll long long
#define PII pair<int,ll>

using namespace std;
const int N=110,INF=0x3f3f3f3f;
char a[N],c[N];
ll lena,lenc,b,d;
PII go[30][N*N];

inline int idx(int i,int j){
    return i*lenc+j;
}

ll solve(int dis){
    int tmp=idx(0,0);
    ll res=0;
    for(int i=0;i<30;i++){
        if(dis>>i&1){
            res+=go[i][tmp].second;
            tmp=go[i][tmp].first;
        }
    }
    return res;
}

int main(){
    scanf("%lld%lld%s%s",&b,&d,a,c);
    lena=strlen(a);lenc=strlen(c);
    for(int i=0;i<lena;i++)
        for(int j=0;j<lenc;j++){
            int id=idx(i,j);
            go[0][id]=make_pair(id,INF);
            for(int k=0;k<lena;k++)
                if(a[(i+k)%lena]==c[j]){
                    go[0][id]=make_pair(idx((i+k+1)%lena,(j+1)%lenc),(i==0)||((i+k)/lena));
                    break;
                }
        }
    for(int i=1;i<30;i++)
        for(int j=0;j<lena*lenc;j++){
            int nxt=go[i-1][j].first;
            go[i][j]=make_pair(go[i-1][nxt].first,go[i-1][j].second+go[i-1][nxt].second);
        }
    ll l=0,r=INF;
    while(l<r){
        ll mid=(l+r+1)>>1;
        if(solve(mid)<=b) l=mid;
        else r=mid-1;
    }
    printf("%lld\n",l/(lenc*d));
    return 0;
}
```



---

## 作者：NuoCarter (赞：1)

难度虚高了吧。。。。

其实需要求出最大的 $p$ ，使得 $[q,p]$ 是 $w$ 的子序列，很容易想到：

因为 $q=[c,d]$ 的，所以我们只需要求出 $w$ 最多包含多少个 $c$ ，用 $k$ 来表示这个答案，利用 $\frac{k}{d}$ 就可以得出答案了。

于是现在问题就是在 $w$ 中匹配 $c$ 。

首先因为求的是子序列，而不是子串，可以贪心的想：

如果当前匹配到了 $c$ 的 $j$ 位置与 $w$ 的 $i$ 位置，如果说$c[i]=w[i]$ 的话，一定是直接匹配，而不是暂时放弃 $w$ 的 $i$ 位置，转而匹配下一位。

所以我们可以用一个指针表示匹配到 $c$ 的位置 $i$，每次移动就可以了。

但是 $|w|=10^9$ 显然跑不过，但是我们利用上面这个贪心的性质：

因为相等就直接匹配，所以从 $c$ 的 $i$ 位置开始匹配，匹配完整个 $a$ 的结束匹配位置可以预处理出来，以及匹配了多少个 $c$。（因为此时在 $a$ 中的可能并不是完整的 $c$，这个 $c$ 可能有一部分是上一次匹配已经匹配了的）

预处理之后直接 $O(b)$ 处理即可。

Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=105;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=false;
    while(!isdigit(ch))  f|=ch=='-',ch=getchar();
    while(isdigit(ch))  x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    x=f?-x:x;
}
template <typename T>
inline void print(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) print(x/10);
    putchar(x%10^48);
}
char s[N],p[N];
int b,d,n,m,Next[N];
ll cnt[N];
int main(){
    read(b),read(d);
    scanf("%s",s);scanf("%s",p);
    n=strlen(s),m=strlen(p);
    for(register int i=0;i<m;++i){
        int now=i;
        for(register int j=0;j<n;++j)
            if(s[j]==p[now]){now++;if(now==m)  now=0,cnt[i]++;}

        Next[i]=now;
    }
    ll ans=0;int now=0;
    for(register int i=1;i<=b;++i)    ans+=cnt[now],now=Next[now];

    print(ans/d);
    return 0;
}

```

---

## 作者：liuyifan (赞：1)

## 类似于DP的模拟

用cnt[i]记录当前开始以c串的i位置找，经过一个a串后会过几个c串

next记录当前开始以c串的i位置开始找，经过一个a串后匹配的位置

code:(时间复杂度O(lena*lenc),CF机子不会炸,~~NOIP不保证~~
```cpp
#include<bits/stdc++.h>//万能头文件 
#define reg register
#define ll long long
#define inf 0x3f3f3f3f
ll b,d,lena,lenc,x,ans,cnt[10000005],next[10000005];//不开long long见祖宗 
char a[10000005],c[10000005];//空间不会炸，已亲身实验 
int main()
{ 
   	scanf("%lld%lld%s%s",&b,&d,a,c);//注意字符串不加&,数组名就是对应指针 
   	lena=strlen(a),lenc=strlen(c);//char字符串的长度 
   	for(reg int i=0;i<lenc;i++)//注意char字符串下标从0开始
  	{
       	x=i;//暴力匹配 
       	for(reg int j=0;j<lena;j++)
		if(a[j]==c[x])
		{
		    x++;//已匹配的位数++ 
		    if(x==lenc)cnt[i]++,x=0;//经过c串数量  
		}
       	next[i]=x;//匹配到的位置 
   	}
	x=ans=0;
	for(reg int i=1;i<=b;i++)
	{
	    ans+=cnt[x];
	    x=next[x];
	}//查找最大的p 
   	printf("%lld",ans/d);//输出 
   	return 0;
}
```


---

## 作者：shinkuu (赞：0)

很暴力的做法。

首先考虑暴力匹配每一个点。时间复杂度 $O(b\times|a|+d\times |c|)$。差一点。于是考虑优化，一次匹配一整个 $c$。预处理从 $a$ 的 $i$ 位置开始，要多长才能匹配到一个 $c$。乍一看好像是 $O(d)$ 的，但是匹配次数可能会很多。

于是再优化一下，处理出一个 $a$ 能匹配多少个 $c$。复杂度即为 $O(d)$。

code：

```cpp
int n,m,a,b,f[N],g[N],h[N];
char s[N],t[N];
inline int get_nxt(int x,char c){
	if(x==-1)
		return -1;
	rep(i,x,x+n-1){
		int j=i%n?i%n:n;
		if(s[j]==c)
			return i+1;
	}
	return -1;
}
void Yorushika(){
	scanf("%d%d%s%s",&a,&b,s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	rep(i,1,n){
		int p=i;
		rep(j,1,m){
			p=get_nxt(p,t[j]);
		}
		f[i]=~p?p-i-1:-1;
	}
	h[n+1]=n;
	drep(i,n,1){
		h[i]=i-1;
		if(i+f[i]<=n){
			g[i]=g[i+f[i]+1]+1;
			h[i]=h[i+f[i]+1];
		}
	}
	if(f[1]==-1){
		puts("0");
		return;
	}
	int cnt=0;
	rep(i,1,a*n){
		int j=i%n?i%n:n;
		if(i+f[j]>a*n)
			break;
		if(g[j]>0){
			cnt+=g[j];
			i+=h[j]-j;
		}else{
			i+=f[j];
			cnt++;
		}
	}
	printf("%d\n",cnt/b);
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

