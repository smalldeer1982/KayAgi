# Secret Passwords

## 题目描述

One unknown hacker wants to get the admin's password of AtForces testing system, to get problems from the next contest. To achieve that, he sneaked into the administrator's office and stole a piece of paper with a list of $ n $ passwords — strings, consists of small Latin letters.

Hacker went home and started preparing to hack AtForces. He found that the system contains only passwords from the stolen list and that the system determines the equivalence of the passwords $ a $ and $ b $ as follows:

- two passwords $ a $ and $ b $ are equivalent if there is a letter, that exists in both $ a $ and $ b $ ;
- two passwords $ a $ and $ b $ are equivalent if there is a password $ c $ from the list, which is equivalent to both $ a $ and $ b $ .

If a password is set in the system and an equivalent one is applied to access the system, then the user is accessed into the system.

For example, if the list contain passwords "a", "b", "ab", "d", then passwords "a", "b", "ab" are equivalent to each other, but the password "d" is not equivalent to any other password from list. In other words, if:

- admin's password is "b", then you can access to system by using any of this passwords: "a", "b", "ab";
- admin's password is "d", then you can access to system by using only "d".

Only one password from the list is the admin's password from the testing system. Help hacker to calculate the minimal number of passwords, required to guaranteed access to the system. Keep in mind that the hacker does not know which password is set in the system.

## 说明/提示

In the second example hacker need to use any of the passwords to access the system.

## 样例 #1

### 输入

```
4
a
b
ab
d
```

### 输出

```
2```

## 样例 #2

### 输入

```
3
ab
bc
abc
```

### 输出

```
1```

## 样例 #3

### 输入

```
1
codeforces
```

### 输出

```
1```

# 题解

## 作者：Meatherm (赞：9)

根据题意，对于两个字符串，如果它们中有相同的字母，那么它们是等价的。等价的字符串具有传递性，即 $a$ 等价于 $b$，$b$ 等价于 $c$ 则 $a$ 等价于 $c$。

容易想到并查集。

使用数组存储每一个字母在哪些字符串中出现过。

对于每一个字母，将出现过的字符串的祖先全部合并。

最后输出不同的祖先数量即可。

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=200010;
std::vector <int> a[110];
int n;
char s[100];
int f[N];
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
inline void Union(int x,int y){
	int X=find(x),Y=find(y);
	if(X!=Y){
		f[X]=Y;
	}
	return;
}
int main(void){
	scanf("%d",&n);
	for(rr int i=1;i<=n;++i){
		f[i]=i;
		scanf("%s",s);
		int len=strlen(s);
		for(rr int j=0;j<len;++j){
			a[s[j]-'a'+1].push_back(i);
		}
	}
	for(rr int i=1;i<=26;++i){
		int siz=a[i].size();
		for(rr int j=0;j<siz;++j){
			Union(a[i][j],a[i][0]);
		}
	}
	int cnt=0;
	for(rr int i=1;i<=n;++i){
		if(f[i]==i)
			++cnt;
	}
	printf("%d",cnt);
	return 0;
}
```

---

## 作者：Froranzen (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/CF1263D)

# 思路

emm……

显然，这是一道并查集的题目，为什么呐？我们可以看这一句：

**如果$a$和$c$在同一组，$b$和$c$在同一组，则$a$和$b$也在同一组**

我们如果把$a,b,c$**抽象成一个个点**的话，它们是**构成一个联通块**的，而我们只需要求出**一共有几个联通块**，答案就有了。

所以用并查集可以很方便地求解。为了方便，我们可以把$a-z$这些小写字母分别转换为$0-25$这些数字，然后每输入一个字符串，我们就把**第$2-len$个字母的祖先更改为字符串的首字母，同时标记当前首字母已出现**。

因为在当前字符串时的首字母在另一个字符串不一定是首字母，所以我们**最后跑一遍循环**，统计各个首字母的祖先。

# 代码
```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
char name[2333];  //输入
bool qwq[233];  //判断当前字母是否出现过
bool waw[233];  //判断当前祖先是否出现过
int fath[233];  //祖先数组
int awa, wqw;

int find (int q) {
    if (fath[q] == q) return q;
    return fath[q] = find(fath[q]);  //路径压缩
}  //寻找祖先

int main () {
    scanf ("%d", &n);
    if (n == 1) {  //一个小特判
        printf ("1");
        exit(0);
    }
    for (register int i(0); i < 53; ++i) fath[i] = i;  //初始化，每个字母的祖先都是它自己
    for (register int i(0); i < n; ++i) {
        scanf ("%s", name);
        int len = strlen(name);
        if (name[0] >= 'a' && name[0] <= 'z') {  //如果是小写字母
            wqw = name[0] - 'a';  //转成int类型，这样方便一点
        }
        else {
            wqw = name[0] - 'A' + 26;
        }  
        waw[wqw] = true;  //标记当前祖先出现过
        for (register int j(1); j < len; ++j) {
            if (name[j] >= 'a' && name[j] <= 'z') {
                fath[find (name[j] - 'a')] = find (fath[wqw]);  //合并
            }
            else {
                fath[find (name[j] - 'A' + 26)] = find (fath[wqw]);
            } 
        }
    }
    for (register int i(0); i < 53; ++i) {
        if (waw[i]) {  //是一个祖先
            if (!qwq[find(fath[i])]) {  //她的祖先没有在qwq数组中标记
                qwq[find(fath[i])] = true;
                awa++;  //答案加1
            }
        }
    }
    printf ("%d", awa);
    return 0;
}
```

---

## 作者：Zvelig1205 (赞：4)

# 并查集判连通块

[题目传送门](https://www.luogu.com.cn/problem/CF1263D)

[双倍经验](https://www.luogu.com.cn/problem/CF277A)

思路和双倍经验差不多，将每个字符串当成人，其中的字母当做语言。

虽然字符串有 $2\times10^5$ 个，但是字母最多 $26$ 个，所以数组并不需要开太大。

具体思路我在[这篇博客](https://413020.blog.luogu.org/solution-cf277a)已经讲过了，此处不再赘述。

值得注意的是数组大小，不能只开到 $2\times10^5$，因为还有 $+26$。

不得不说，Codeforces 还是很[良心](https://codeforces.com/contest/1263/submission/172813872)的，不然还得调一阵子。

代码：

```cpp
const int inf=2e5+107;
int n,ans,fa[inf];
bool v[inf];
int find(int x){return (fa[x]^x)?(fa[x]=find(fa[x])):(x);}
int main()
{
	n=re();
	for(int i=1;i<=n+26;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
	{
		char s[57]="";scanf("%s",s);
		bool vis[27]={};
		int len=strlen(s);
		for(int j=0;j<len;j++)
			vis[s[j]-'a'+1]=1;
		for(int j=1;j<=26;j++)
			if(vis[j])fa[find(i)]=find(n+j);
	}
	for(int i=1;i<=n;i++)
	{
		int ls=find(i);
		if(v[ls])continue;
		v[ls]=1;ans++;
	}
	wr(ans);
	return 0;
}
```

---

## 作者：Priori_Incantatem (赞：3)

把每一个字母当成一个点，对于每一个给出的字符串，把字符串中的所有字母之间都连上边。这样，若两个字符串有公共的字母，他们就一定在一个连通块内，最后求出连通块个数就可以了  

我们可以用并查集来简化上面的操作，对于一次加边操作，我们可以用并查集的合并来代替，最后求连通块也是同理

```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
const int Maxn=30,inf=0x3f3f3f3f;
int f[Maxn];
bool c[Maxn];
int n,ans;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
int find(int x)
{
	if(f[x]==x)return x;
	return f[x]=find(f[x]);
}
inline void uni(int x,int y)
{
	f[find(x)]=find(y);
}
int main()
{
//	freopen("in.txt","r",stdin);
	n=read();
	for(int i=1;i<=26;++i)
	f[i]=i;
	for(int i=1;i<=n;++i)
	{
		char s[60];
		scanf("%s",s+1);
		int len=strlen(s+1);
		c[s[1]-'a'+1]=1;
		for(int j=1;j<len;++j)
		{
			int x=s[j]-'a'+1,y=s[j+1]-'a'+1;
			uni(x,y);
			c[x]=c[y]=1;
		}
	}
	for(int i=1;i<=26;++i)
	if(f[i]==i && c[i])ans++;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：OldVagrant (赞：2)

## 题意
给定 $n$ 个由小写字母组成的字符串，定义两个字符串 $a,b$ 在同一组当且仅当存在至少一个字符同时在 $a,b$ 中出现。如果 $a,b$ 在同一组， $b,c$ 在同一组，那么 $a,c$ 也在同一组。求最后一共有多少组字符串。    
$1\le n\le 2\times 10^5$,每个字符串的长度不超过 50，总长度不超过 $10^6$。
## Solution
题目告诉我们字符串之间的关系是可传递的，所以我们可以使用并查集来维护哪些字符串被分到了一组，但是直接维护整个字符串会有些麻烦。      
题上说了这些字符串都是由小写字母组成的，那么不如去维护每个小写字母之间的关系，哪些小写字母被分到了一个集合就代表含有这些小写字母的字符串被分到了一个集合。如果同一个字符串里出现了多个不同的小写字母，那么就把这些小写字母所在的集合合并。 
因为每个字符串的长度都很短，所以可以考虑直接读入每个字符串，然后统计出哪几个不同的小写字母在这个字符串里出现了，把这些字母所在的集合合并。小写字母的范围很小，只有 26 个，每次合并要么是已经在同一集合内了不需要合并，要么就是把两个集合合并到一起，所以合并操作次数虽然很多,但是均摊复杂度很小，接近于带一个小常数的 $O(1)$ ，可以通过此题。
最后读入完直接遍历每个小写字母所在的集合，如果该集合的代表没有出现过那么这就是一个新的集合，统计到答案里，并且标记这个代表出现过。因为一共只有 26 个小写字母，所以这个遍历的复杂度可以忽略不计。
## Code
注释掉的代码为卡常用的快读快写，可以自行去掉。
```c
#include <bits/stdc++.h>
using namespace std;
#define gc getchar
#define pc(x) putchar(x)
int fa[27],n,size[27],col[27],ans;//size为每个集合的大小，col为每个集合里字符串的数量
string s[200001];
bool t[200001][27];//t为统计每个字符串里每个小写字母是否出现过的数组
/*const int LEN=114514;
char BUF[LEN],*Pin,*Pin_last,PUF[LEN],*Pout=PUF,*Pout_last=PUF+LEN-1;
char gc(){
	return Pin==Pin_last&&(Pin_last=(Pin=BUF)+fread(BUF,1,LEN,stdin),Pin==Pin_last)?EOF:*Pin++;
}
void pc(char x){
	if(Pout==Pout_last) fwrite(PUF,1,Pout-PUF,stdout),Pout=PUF;
	*Pout++=x;
}*/
void write(int x){
    if(x>9) write(x/10);
    pc(x%10+48);
}
int find(int x){
	if(fa[x]==x) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return;
	if(size[x]<size[y]) swap(x,y);//这里用了启发式合并的优化，优先把小的集合往大的集合里并。
	fa[y]=x,size[x]+=size[y],col[x]+=col[y],col[y]=0; //注意合并两个集合之后小的集合的元素数量就为0了，原有的元素现在都属于新的大集合。
}
void read(int cnt){
	char ch=gc();
	int la=0;
	while(ch>122||ch<97) ch=gc();
	while(ch<123&&ch>96) t[cnt][ch-96]=1,ch=gc();//直接暴力统计每个字母是否出现过
	for(int i=1;i<27;i++){
		if(t[cnt][i]){//如果该字母出现过并且不是第一个就把它和上一个出现的字母合并
			if(la) merge(i,la);
			la=i;
		}
	}col[find(la)]++;//该字符串所属的集合的计数器记得加上1，把这个字符串的贡献也算上。
	return;
}
signed main(){
	scanf("%d",&n);
	for(int i=1;i<27;i++) fa[i]=i,size[i]=1;
	for(int i=1;i<=n;i++) read(i); 
	for(int i=1;i<27;i++) if(col[i]) ans++;//如果该字母的集合内有元素则更新答案。
	printf("%d",ans);
	//fwrite(PUF,1,Pout-PUF,stdout);
	return 0;
}
```

---

## 作者：Karry5307 (赞：2)

### 题意

我们定义两个串$s$和$t$是等价的当且仅当有一个字母在$s$和$t$中都出现或者存在一个串$u$使得$s=u$且$u=t$。

给定$n$个串，你需要判断至少在这些串里选多少个串才可以使得剩下的任意一个串都与某一个选中的串是等价的。

$\texttt{Data Range:}n\leq 2\times 10^5,\sum len\leq 10^6$

### 题解

哎，rating+1，无缘 Expert，果然这东西还是需要慢慢熬qwq

并查集好题。

一看到这种具有传递性的关系很明显的用并查集来维护。

我们记$t_i$表示上一次出现字母$i$的串是哪一个。

对于每一个串都扫一遍，如果发现这一个串的某一个字母$s$的$t_s$存在，就把这个串与那个串所在的集合合并，表明他们是等价的。

然后不同集合的个数就是答案。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef int ll;
const ll MAXN=2e5+51;
set<ll>st;
ll cnt,fx,fy;
ll ffa[MAXN],t[128];
string str[MAXN];
inline ll read()
{
    register ll num=0,neg=1;
    register char ch=getchar();
    while(!isdigit(ch)&&ch!='-')
    {
        ch=getchar();
    }
    if(ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
} 
inline ll find(ll x)
{
	return ffa[x]==x?x:ffa[x]=find(ffa[x]);
}
int main()
{
	cnt=read();
	for(register int i=1;i<=cnt;i++)
	{
		cin>>str[i];
		ffa[i]=i;
	}
	for(register int i=0;i<str[1].length();i++)
	{
		t[str[1][i]]=1;
	}
	for(register int i=2;i<=cnt;i++)
	{
		for(register int j=0;j<str[i].length();j++)
		{
			if(t[str[i][j]])
			{
				fx=find(i),fy=find(t[str[i][j]]);
				if(fx!=fy)
				{
					ffa[fy]=fx;
				}
			} 
			else
			{
				t[str[i][j]]=i;
			}
		}
	}
	for(register int i=1;i<=cnt;i++)
	{
		st.insert(find(i)); 
	}
	printf("%d\n",st.size());
}
```


---

## 作者：_GW_ (赞：2)

## 思路

一眼并查集。

先用一个数组，存储每个字母第一次出现时是在第几个字符串里。

然后每输入一个字符串 $s$，就遍历 $s$ 中的每一个字母。

如果 $s_i$ 在之前出现过，就让这个字符串与之前那个字符串合并。

否则就把 $s_i$ 这个字母第一次出现的位置指向 $s$。

最后答案就是联通块的个数。

## 复杂度
时间 $O(n)$，空间 $O(n)$。

## code
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int vis[N],fa[N],num,val,sum[N],n,m,k,T,res;
int mp[N];
int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
    int fax=find(x),fay=find(y);
    if(fax!=fay)
    {
        res++;
        fa[fax]=fay;
    }
}
int main()
{
    cin>>n;
    for(int i=0;i<N;i++)
    {
        fa[i]=i;
    }
    string s;
    for(int i=1;i<=n;i++)
    {
        cin>>s;
        for(int j=0;j<s.size();j++)
        {
            if(mp[s[j]])
            {
                merge(mp[s[j]],i);
            }
            if(!mp[s[j]])
            {
                mp[s[j]]=i;
            }
        }
    }
    int res=0;
    for(int i=1;i<=n;i++)
    {
        if(fa[i]==i)
        {
            res++;
        }
    }
    cout<<res<<endl;
    return 0;
}
```


---

## 作者：xujunlang2011 (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1263D)

## 思路

发现题目中提到了**分组**，所以我们可以用并查集维护。

先将在同一个字符串的字母分在同一组，再找出现过的字母一共分成了几组，最后输出组数就行了。

这里我用了一个标记数组来记录有几个不同的祖先。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n, a[30], t[30], f[30];
string s;
int find(int k)
{
    if (a[k] == k)
    {
        return k;
    }
    return a[k] = find(a[k]);
}
int main()
{
    cin >> n;
    for (int i = 1;i <= 26;i++)
    {
        t[i] = 0;
        a[i] = i;
    }
    for (int i = 1;i <= n;i++)
    {
        cin >> s;
        int l = s.length();
        s = " " + s;
        t[s[1] - 'a' + 1] = 1;
        for (int j = 2;j <= l;j++)
        {
            if (find(s[1] - 'a' + 1) != find(s[j] - 'a' + 1))
            {
                a[find(s[j] - 'a' + 1)] = find(s[1] - 'a' + 1);
            }
            t[s[j] - 'a' + 1] = 1;
        }
    }
    for (int i = 1;i <= 26;i++)
    {
        f[i] = 0;
    }
    for (int i = 1;i <= 26;i++)
    {
        if (t[i])
        {
            f[find(i)] = 1;
        }
    }
    int cnt = 0;
    for (int i = 1;i <= 26;i++)
    {
        if (f[i])
        {
            cnt++;
        }
    }
    cout << cnt;
    return 0;
}
```


---

## 作者：Yun_Mengxi (赞：1)

[题目传送门](/problem/CF1263D)

## 题意

给定 $n$ 个字符串，一个字符串里的字符在同一组，问最终有多少组。

## 分析

根据“同一组”“如果 $a$ 和 $b$ 在同一组，$b$ 和 $c$ 在同一组，$a$ 和 $c$ 在同一组”这些关键词语，不难发现这题是并查集，这里提供一种其他题解没有的做法，每次将当前字符串除了第一个字符之外的所有字符都与第一个字符合并，然后求最后的出现过的字符的集合数就行了。

时间复杂度为 $O(n\times |s|\times \alpha(n\times |s|))$，$|s|$ 为字符串 $s$ 的长度。

## 代码

```cpp
#include <bits/stdc++.h>
#include <limits.h>

#include <algorithm>
#include <cmath>

#define IOS                \
  ios::sync_with_stdio(0); \
  cin.tie(0);              \
  cout.tie(0)

using namespace std;

const int kInf = 0x3f3f3f3f, kMaxN = 200005;

int n;
int ans = 0;
string s[kMaxN];
int fa[kMaxN];
int sz[kMaxN];
int vis[kMaxN];

int FF(int x) {                               // 路径压缩优化
  return x == fa[x] ? x : fa[x] = FF(fa[x]);
}

void add(int u, int v) {                      // 按秩合并优化
  u = FF(u), v = FF(v);
  if (u == v) return;
  if (sz[u] < sz[v]) swap(u, v);
  fa[v] = u;
  sz[u] += sz[v];
}

int main() {
  IOS;
  for (int i = 'a'; i <= 'z'; i++) {          // 初始化
    fa[i] = i;
  }
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> s[i];
    vis[s[i][0]] = 1;                         // 别忘了还有第一个字符
    for (int j = 1; j < s[i].size(); j++) {
      add(s[i][0], s[i][j]);                  // 合并当前字符和第一个字符
      vis[s[i][j]] = 1;                       // 记录当前字符出现过没有
    }
  }
  for (int i = 'a'; i <= 'z'; i++) {
    ans += fa[i] == i && vis[i];              //  如果这个字符出现过
  }
  cout << ans << '\n';
  return 0;
}
```

---

## 作者：Buried_Dream (赞：1)

## Solution



我们考虑通过将每个字母有哪些串出现过，是可以用 $26$ 个 set 来存储位置的。 

因为题目中 $a$ 和 $b$ 同组，$b$ 与 $c$ 同组，则 $a$ 与 $c$ 同组。

我们考虑用并查集来维护。

然后我们枚举第一个集合，枚举第二个集合，如果这个两个集合中有相同的元素，则将这两个合并起来。

注意要先去重。

```cpp
/**
 *	author: TLE_Automation
 *	creater: 2022.9.28
 **/
#include<map>
#include<set>
#include<cmath>
#include<queue>
#include<cstdio>
#include<random>
#include<bitset>
#include<cstring>
#include<iostream>
#include<algorithm>
#define gc getchar 
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const int mod = 998244353;
const ll inf = 0x3f3f3f3f3f3f3f3f;
#define debug cout << "i ak ioi" << "\n"
inline void print(int x) {if (x < 0) putchar('-'), x = -x; if(x > 9) print(x / 10); putchar(x % 10 + '0');}
inline char readchar() {static char buf[100000], *p1 = buf, *p2 = buf; return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;}
inline int read() { int res = 0, f = 0; char ch = gc();for (; !isdigit(ch); ch = gc()) f |= (ch == '-'); for (; isdigit(ch); ch = gc()) res = (res << 1) + (res << 3) + (ch ^ '0'); return f ? -res : res;}

set <int> s[30];
string a[N];
int fa[N];

inline int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

map <string, int> mp;

signed main() 	
{
	int n = read();
	for(register int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= n; i++) sort(a[i].begin(), a[i].end());
	sort(a + 1, a + n + 1);
	n = unique(a + 1, a + n + 1) - a - 1;
	for(register int i = 1; i <= n; i++) {
		for(register int j = 0; j < (int)a[i].size(); j++) {
			int num = a[i][j] - 'a' + 1;
			s[num].insert(i);
		}	
		mp[a[i]]++;
	}
	for(register int i = 1; i <= 26; i++) fa[i] = i;
	for(register int j = 1; j <= 26; j++) {
		for(register int k = 1; k <= 26; k++) {
			if(find(j) == find(k)) continue;
			for(set <int>::iterator it = s[j].begin(); it != s[j].end(); ++it) {
				if(s[k].find(*it) != s[k].end()) {
					int fx = find(j), fk = find(k);
					fa[fx] = fk; break;
				}
			}
		}
	}
	ll ans = 0;
	for(register int i = 1; i <= 26; i++) {
		if(s[i].size()) ans += (fa[i] == i);
	}
	std::cout << ans;
	return (0 - 0);
}
```

---

## 作者：Mcggvc (赞：1)

## **联通块**

把字符串连起来，最后用一遍dfs算出联通块数量，即为答案。

具体怎么操作呢

把每个子串看成一个结点，在这些子串数量基础上，再开26个结点，编号分别为$0,1,2...25$，代表$a,b,c...z$，输入每个字符串时遍历一遍字符串，有什么字母就把这个字符串和这个字母相应的结点连上边。记录一下字母结点的连边数量。

最后跑一边dfs，统计答案。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int N = 200100;
const int M = 65;
const int EDGE = 2000005;
int nextt[EDGE], head[N], to[EDGE];
int n, cnt, ans, in[M];
char s[M];
bool vis[N + M];
void add(int x, int y) {
	nextt[++cnt] = head[x];
	to[cnt] = y; head[x] = cnt;
}
void dfs(int u) {
	vis[u] = true;
	for(int i = head[u]; i; i = nextt[i]) {
		int v = to[i]; if(vis[v]) continue;
		dfs(v);
	}
}
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) {
		cin >> s; int len = strlen(s);
		bool v[M]; memset(v, false, sizeof(v));
		for(int j = 0; j < len; j++) {
			if(v[s[j] - 'a']) continue;
			in[s[j] - 'a']++; v[s[j] - 'a'] = true;
			add(s[j] - 'a', i + 25); add(i + 25, s[j] - 'a');
		}
	}
	for(int i = 0; i <= 25; i++) { 
		if(!vis[i] && in[i]) ans++, dfs(i);
	}
	printf("%d", ans);
	return 0;
}

```


---

## 作者：One_JuRuo (赞：0)

## 思路

题目告诉我们有相同字母的密码就是等效的，等效性可以传递，所以我们可以考虑把所有等效的密码放在一起。

自然而然地想到了并查集，统计每个出现过某个字母的密码，然后一个字母一个字母的去合并等效密码。

接下来思考如何统计答案，如果合并完了再去统计，自然就很麻烦，但是我们可以边合并边统计，发现如果有两个等效密码合并，则会减少一个答案，所以可以在合并时统计。

## AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,fa[200005],ans;
char ch[55];
bool vis[26];
vector<int>v[26];
int find(int x){return (fa[x]==x)?x:fa[x]=find(fa[x]);}
int main()
{
	scanf("%d",&n),ans=n;
	for(int i=1;i<=n;++i) fa[i]=i;
	for(int i=1;i<=n;++i)
	{
		scanf("%s",ch),memset(vis,0,sizeof(vis));
		int m=strlen(ch);
		for(int j=0;j<m;++j)
		{
			if(vis[ch[j]-'a']) continue;//避免重复统计
			vis[ch[j]-'a']=1,v[ch[j]-'a'].push_back(i);
		}
	}
	for(int i=0;i<26;++i)
		if(v[i].size()>1)
			for(int j=1;j<v[i].size();++j)
				if(find(v[i][0])!=find(v[i][j])) fa[find(v[i][j])]=find(v[i][0]),ans--;
	printf("%d",ans);
	return 0;
}
```

---

## 作者：快斗游鹿 (赞：0)

很容易想到可以使用并查集。

只要枚举 $26$ 个字母，判断它们在哪些字符串中出现过，再将那些字符串的祖先合并即可。最后只需要输出有多少个不同的祖先就行了。因为所有字符串总长度不超过 $10^6$，所以这种做法可行。

代码：

```
#include<bits/stdc++.h> 
using namespace std;
const int N=2e5+5;
int n,fa[N],t[N],ans;
string s[N];
int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++)cin>>s[i],fa[i]=i;
	for(int i=1;i<=26;i++){//枚举字母
		int now=0;
		for(int j=1;j<=n;j++){
			bool flag=0;
			for(int k=0;k<s[j].length();k++){
				if(int(s[j][k])==i+96){
					if(!now)now=j;
					flag=1;break;
				} 
			}
			if(flag){
				int e=find(now);
				int f=find(j);
				//cout<<now<<" "<<j<<endl;
				fa[e]=f;
			}
		}
	}
	for(int i=1;i<=n;i++){
		int x=find(i);
		if(!t[x]){
			ans++;t[x]=1;
		}
	}
	cout<<ans;
	return 0;
}

```


---

## 作者：_Dreamer_ (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1263D)

题解里貌似没有我这种做法

由 题目 

- 如果**存在**一个或多个字母同时在字符串 $a$ 和 $b$ 中出现 这 $a$ 和 $b$ 就被分在同一组

意思就是

对于字符串 $s$  假若其中出现了字符 $c_1\,,c_2\,,\cdots\,\ ,c_n$ 那么 $s$ 可以被归结到以 字符 $c_1$ 为代表的类 也可以被归结到以 $ c_2 $ 为代表的类

- 如果 $b$ 和 $c$ 在同一组 $b$ 和 $c$ 在同一组 则 $ a $ 和 $b$ 也在同一组

 即这种关系具有传递性 故可以把 $c_1\, ,c_2\,,\cdots,c_n $ 合并为同一类  利用并查集维护这种关系即可

注意到没有出现的字母是不能拥有一个类别的  计算答案时跳过即可

```cpp

#include<bits/stdc++.h>
using namespace std;
int n;
int f[27];
string s;
int find(int x)
{
	if(f[x]==x)return x;
	return f[x]=find(f[x]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		cin>>s;int le=s.size();
		for(int i=0;i<le;i++)
		{
			if(f[s[i]-'a'+1]==0)f[s[i]-'a'+1]=s[i]-'a'+1;
			if(i)f[find(s[i]-'a'+1)]=find(s[i-1]-'a'+1);
		}
	}
	int ans=0;
	for(int i=1;i<=26;i++)
	{
		if(f[i]==i)ans++;
	}
	printf("%d",ans);
	return 0;
}

```

---

## 作者：Troubadour (赞：0)

### 题意简述
给定 $n$ 个字符串

- 如果存在一个或多个字母同时在字符串 $a$ 和 $b$ 中出现，这 $a$ 和 $b$ 就被分在同一组。
- 如果 $a$ 和 $c$ 在同一组，$b$ 和 $c$ 在同一组，则 $a$ 和 $b$ 也在同一组。

问所有的字符串最后被分成几组。
### 分析
根据题意，我们可以得到分组间的传递关系和并查集如出一辙，所以我们可以考虑用并查集来维护。

初始时有 $n$ 个组，每个串都是独立的，接下来我们可以把有相同字符的串不断合并，最后合并得到的组数即为所求。

但是我们看到，$1≤n≤2·10^5$，$O(n^2)$ 刚好被卡得死死的。如果不断遍历字符串来判断的话，肯定妥妥的TLE。

我们换一种思路：遍历 $26$ 个字母，看每个串是否出现过这个字母。我们可以另外给每个字母建一个点，然后把出现过它的字符串全部和它合并，表明他们是等价的。$26$ 个字母，这样稳稳的就过了。

(在下面的代码里，我为了省事直接把 $26$ 个点接在了 $n$ 个字符串后面。)

因为我们只需要考虑每一个字符有没有在原串里出现过，可以把 $26$ 个字母的信息压缩成一个二进制串，$1$ 表示出现过，$0$ 表示没有出现，这样更易于计算。

最后遍历一遍并查集，统计答案即可。

### Code
```
#include<bits/stdc++.h>
#pragma warning(disable:4996)
namespace CCCP
{
	const int N = 2e5 + 30;
	char s[50];
	int a[N], fa[N], n, ans, vis[N];
	int find(int x)
	{
		if (fa[x] == 0)return fa[x] = x;
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	void work()
	{
		scanf("%d", &n);
		for (int i = 1;i <= n;i++)
		{
			scanf("%s", s);
			for (int j = 0;s[j];j++)
			{
				a[i] |= 1 << (s[j] - 'a');
			}
		}
		for (int i = 0;i < 26;i++)
		{
			for (int j = 1;j <= n;j++)
			{
				if (a[j] & (1 << i))
				{
					int fx = find(j), fy = find(n + i + 1);
					if (fx == fy)continue;
					fa[fx] = fy;
				}
			}
		}
		for (int i = 1;i <= n;i++)
		{
			int x = find(i);
			if (!vis[x])
			{
				vis[x] = 1,ans++;
			}
		}
		printf("%d", ans);
	}
}
int main()
{
	return CCCP::work(), 0;
}
```

---

