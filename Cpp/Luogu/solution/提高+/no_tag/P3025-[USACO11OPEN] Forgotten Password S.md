# [USACO11OPEN] Forgotten Password S

## 题目描述

就像在我们身上经常发生的那样，Bessie 又一次忘记了她的牛场管理员密码，她只能记得密码的一部分。

首先，她记得密码 $P$ 是长度为 $L$（$1 \le L \le 1000$）的字符串，并且她的密码中出现过的所有单词都记录在她的共有 $NW$ 个单词的字典中，每个字典中的单词 $W_i$ 都是由 $1$ 至 $20$ 个小写拉丁字母组成的。

她只记得密码中的一部分字母和它的位置。例如，Bessie 记得她的密码为 `a??l?ban???????`，其中，`?` 是她忘记的字母。她的字典中有这些单词：`apple cow farmer banana bananas pies`。所以，Bessie 的密码的两种可能是`applebananapies` 和 `applebananascow`.

现在，给你 Bessie 还记得的字母和她的字典，求可能的密码。如果有多个答案，则输出字典序最小的那一个。

## 样例 #1

### 输入

```
15 6 
a??l?ban??????? 
apple 
cow 
farmer 
banana 
bananas 
pies 
```

### 输出

```
applebananapies 
```

# 题解

## 作者：ycyaw (赞：6)

或许你们更愿意看短一点的代码。

每个密码单词长度小于等于$20$，那么我们在$dp$时直接暴力判断能不能匹配。

$ans[i]$表示长度为$i$时候的答案，为$""$时表示不存在。对于原密码的每一位，枚举所有单词，钦定这个单词的结尾为这一位，然后找到开头，看一下中间一段能不能匹配。如果能匹配，看一下答案是否更优。判断字典序以及字符串拼接利用强大的$string$即可。

代码很短很好懂：

复杂度$O(L\times NW\times 20)$。
```cpp
#include<bits/stdc++.h>
#define ts cout<<"ok"<<endl
#define ll long long
#define hh puts("")
using namespace std;
int len,n;
char p[1005];
string s[1005],ans[1005];
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-ff;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+(ch^48);ch=getchar();}
    return ret*ff;
}
inline bool check(int st,int id){
    for(int i=0;i<s[id].size();i++)
        if(p[st+i]!='?'&&p[st+i]!=s[id][i])
            return 0;
    return 1;
}
signed main(){
    len=read(),n=read();
    scanf("%s",p+1);
    for(int i=1;i<=n;i++) cin>>s[i];
    for(int i=1;i<=len;i++){
        for(int j=1;j<=n;j++){
            if(s[j].size()>i) continue;
            int st=i-s[j].size();
            if(st>0&&ans[st]=="") continue;
            if(check(st+1,j))
                if(ans[i]==""||ans[i]>ans[st]+s[j])
                    ans[i]=ans[st]+s[j];
        }
    }
    cout<<ans[len];
    return 0;
}
```


---

## 作者：姬小路秋子 (赞：3)

鉴于楼上那位的题解过于简略，其中的很多细节都没有提及，况且那个放代码的链接失效了（丧），所以就由我来给大家发一份福利吧。

**PS**：估计这题过的人那么少的原因就是网上根本找不到这题的代码吧。。

首先，我们可以......（巴拉巴拉巴拉，此处参照楼上前三行）

引用下他的第三行：**枚举每个单词j去和i每个位置匹配**

这边的**i**指密码串中的位置，意思是从密码串第i个位置开始匹配第j个单词，看是否能匹配，这可以通过预处理得出，时间复杂度**O(20L*NW)**

然后他后面两行是这样的：

**能够更新当前位置的情况当且仅当**

**dp[i]=="" 或者 dp[i]>dp[i-l[j]]+m[j]**

首先dp[i]==""意思就是这个位置还没有进行过匹配，即现在要对这个位置进行第一次匹配。

dp[i]>dp[i-l[j]]+m[j]的意思是第j个单词可以在当前匹配，l[j]指单词长度，m[j]指这个单词本身，简而言之，就是判断字典序大小辣，如果能更小那么就换掉

然后你发现，这不是要对密码串的每个位置都匹配一下每个单词吗，再加上比较字典序的话，时间复杂度不是**O(L^2*NW)**吗？这样显然不对

然后你发现时间复杂度的瓶颈在于字典序判断的次数过多

这是，我们不妨回顾下本题给出的条件：**单词长度不超过20**

！！！

问题的突破口！

然后你发现，对于每个位置，**相同长度的单词只要保留下能匹配当中的字典序最小的那个就行了**，因为字典序大的当然不如小的来的好了（注意，是相同长度的，不同长度的不一定）

然后枚举单词长度，对于每个长度进行判断

于是完了

时间复杂度：**O(20L*NW)**，再加上前面的预处理，就是这个的两倍。

代码细节真的很多，特别是判断字典序的时候我在两处犯下了致命的错误，导致一开始只有55分

**上代码**~~（欢呼吧）~~：

```c
#include<bits/stdc++.h>
using namespace std;
struct aaa{
	int z;
	char x[1100];
}a[1100];
int n,m,hh[1100][1100],f[1100][1100],g[1100],c[1100];
bool cmp(aaa a,aaa b){
	int i,flag=0,t=strlen(a.x+1),k=strlen(b.x+1),now=min(t,k);
	for(i=1;i<=now;i++)
	 if(a.x[i]<b.x[i]){
	 flag=1;break;
}
	  else if(a.x[i]>b.x[i]){
	   flag=2;break;
}
	if(flag==1)return 1;
	if(flag==2)return 0;
	if(t<=k)return 1;
	return 0; 
}
int main(){
	int i,j,k,flag;
	char s[1100];
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	for(i=1;i<=m;i++){
		scanf("%s",a[i].x+1);
		a[i].z=strlen(a[i].x+1);
	}
	//puts("");
	//puts("");
	sort(a+1,a+m+1,cmp);
	//for(i=1;i<=m;i++)printf("%s\n",a[i].x+1);
	for(i=1;i<=m;i++)
	 for(j=1;j<=n;j++)
	  if(j+a[i].z-1<=n){
	  	flag=0;
	   for(k=j;k<=j+a[i].z-1;k++)
	    if(s[k]!='?'&&a[i].x[k-j+1]!=s[k]){
	     flag=1;break;
	 }
	   hh[j][i]=1-flag; 
}
g[0]=1;
    for(i=1;i<=n;i++){
    	memset(c,0,sizeof(c));
    	for(j=m;j;j--)
    	 if(a[j].z<=i&&hh[i-a[j].z+1][j])c[a[j].z]=j;
    	for(j=min(20,i);j;j--) 
		 if(c[j]&&g[i-j]){
		 	if(!g[i]){
		 		g[i]=1;
		 		for(k=1;k<=i-j;k++)f[i][k]=f[i-j][k];
		 		for(k=i-j+1;k<=i;k++)f[i][k]=a[c[j]].x[k-(i-j)];
		 	}
		 	 else{
		 	 	flag=0;
		 	 	for(k=1;k<=i-j;k++)
		 	 	 if(f[i-j][k]<f[i][k]){
		 	 	  flag=1;break;
		 	 }
		 	 	  else if(f[i-j][k]>f[i][k]){
		 	 	   flag=2;break;
		 	 }
		 	 	if(flag==1){
		 	 		for(k=1;k<=i-j;k++)f[i][k]=f[i-j][k];
		 		for(k=i-j+1;k<=i;k++)f[i][k]=a[c[j]].x[k-(i-j)];
		 	 	}
		 	 	 else if(flag==2)continue;  //这是第一处错误，之前我把continue写成了break。。。
		 	 	  else{
		 	 	  	for(k=i-j+1;k<=i;k++)
		 	 	  	 if(a[c[j]].x[k-(i-j)]<f[i][k]){
		 	 	  	  flag=1;break;
		 	 	  }
		 	 	   else if(a[c[j]].x[k-(i-j)]>f[i][k])break;//这是第二处，一开始我并没有这一行。。。
		 	 	  	if(flag==1)
		 	 	  	 for(k=i-j+1;k<=i;k++)f[i][k]=a[c[j]].x[k-(i-j)];
		 	 	  }
		 	 }
		 }
    }
    for(i=1;i<=n;i++)printf("%c",f[n][i]);
}
```

---

## 作者：_Deer_Peach_ (赞：2)

### 分析：
通过分析可以知道这是一道动态规划题。

首先：

状态定义：$dp[i]$ 表示为前i个字符满足要求的答案。

其次：

转移条件：

当前单词长度大于了 $i$，较 $i-l[j]$，$j$ 有不同的，或者是 $dp[i-l[j]]$ 是空串且剩余长度大于零则不满足转移条件；如果 $dp[i]$ 是空串或者答案比原答案更优则可以转移。

最后：

状态转移：
```
     if(l[j]>i or !check(i-l[j],j) or (dp[i-l[j]]=="" and (i-l[j])>0)) continue;
     if(dp[i]=="" or dp[i-l[j]]+w[j]<dp[i]) dp[i]=dp[i-l[j]]+w[j];
```
### 分析完毕，接下来就是代码实现：
```
#include<bits/stdc++.h>
using namespace std;
int l,n;
string w[1001],dp[1001],s;
int len[1001];
bool check(int x,int y){//判断是否符合条件
    for(int i=0;i<len[y];i++)
        if(s[x+i]!=w[y][i] and s[x+i]!='?')
            return false;
    return true;
}
inline void read(int &a){//快读快写（其实用不用无所谓可以跳过）
	a=0;
	char c;
	bool f=0;
	while((c<'0' or c>'9') and c!='-'){
		c=getchar();
	}
	c=='-' and (f=1,c=getchar());
	while(c>='0' and c<='9'){
		a=a*10+c-'0';
		c=getchar();
	}
	f and (a=-a);
}
inline void write(int a){
	if(a<'0'){
		a=-a;
		putchar('-');
	}
	if(a>'9'){
		write(a/10);
	}
	putchar(a%10+'0');
}
int main(){
    read(l);
    read(n);
    cin>>s;
    for(int i=1;i<=n;i++){
        cin>>w[i];
        len[i]=w[i].size();
    }
    for(int i=1;i<=l;i++)//核心代码
        for(int j=1;j<=n;j++){
            if(len[j]>i or !check(i-len[j],j) or (dp[i-len[j]]=="" and (i-len[j])>0))continue;
            if(dp[i]=="" or dp[i-len[j]]+w[j]<dp[i]) dp[i]=dp[i-len[j]]+w[j];
        }
    cout<<dp[l];
    return 0;
}

---

## 作者：hulean (赞：1)

动态规划题

令$dp[i]$表示字符串的前$i$个字符可以组成的字典序最小的字符，如果无法组成则为空串

那么就可以很好地写出状态转移方程：
```cpp
for(int i=1;i<=L;i++)
        for(int j=1;j<=N;j++)
        {
            if(l[j]>i||!check(i-l[j],j)||(dp[i-l[j]]==""&&(i-l[j])>0))continue;//不符合条件的剪去
            if(dp[i]==""||dp[i-l[j]]+w[j]<dp[i])
                dp[i]=dp[i-l[j]]+w[j];//取最优值
        }
```
### 主要看代码注释吧

代码
```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int L,N;
string w[1010],dp[1010];
//w[]表示单词，dp已经说过了
int l[1010];//表示每个单词的长度
inline bool check(int p,int t)
{
    for(int i=0;i<l[t];i++)
        if(s[p+i]!=w[t][i]&&s[p+i]!='?')//比较，如果有不同的，那么返回false
            return 0;
    return 1;
}
int main()
{
    scanf("%d %d",&L,&N);
    cin>>s;
    for(int i=1;i<=N;i++)
    {
        cin>>w[i];
        l[i]=w[i].size();
    }
    for(int i=1;i<=L;i++)
        for(int j=1;j<=N;j++)
        {
            if(l[j]>i||!check(i-l[j],j)||(dp[i-l[j]]==""&&(i-l[j])>0))continue;
            if(dp[i]==""||dp[i-l[j]]+w[j]<dp[i])
                dp[i]=dp[i-l[j]]+w[j];//记得特判空串，还有字符串是可以比较大小的
        }
    cout<<dp[L]<<endl;
    return 0;
}
```

---

## 作者：happybob (赞：0)

比较显然的 DP 是很好思考的。

令 $f_i$ 表示前 $i$ 个字符的答案，转移时枚举 $1 \leq j \leq i$，判断 $j \sim i$ 是否是一个单词，如果是，用 $f_{j-1}+s[j\cdots i]$ 转移。

然而我的实现并不太优美，复杂度甚至已经达到了 $O(n^3m)$。不过其实是跑不满的。因为当 $f_{j-1}$ 为空时，这个转移是不存在的。

这个复杂度其实并不很优，但是题目数据比较弱，所以就可以过了。不过优化也比较容易思考。发现单词长度不超过 $20$，所以第二层枚举 $j$ 只需要 $20$ 次，就可以达到正确的复杂度了。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

const int N = 1005;

string p[N], s;
string dp[N];
int n, m;

inline string check(string& g)
{
	string res = "-1";
	for (int i = 1; i <= m; i++)
	{
		if (p[i].size() != g.size()) continue;
		bool f = 1;
		for (int j = 0; j < g.size(); j++)
		{
			if (g[j] != '?' && p[i][j] != g[j])
			{
				f = 0;
				break;
			}
		}
		if (f)
		{
			if (res == "-1") res = p[i];
			else res = min(res, p[i]);
		}
	}
	return res;
}

auto main() -> int
{
	ios::sync_with_stdio(0), cin.tie(nullptr), cout.tie(nullptr);
	cin >> n >> m >> s;
	for (int i = 1; i <= m; i++) cin >> p[i];
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j >= 0; j--)
		{
			if (j != 0 && dp[j - 1].empty()) continue;
			string g = s.substr(j, i - j + 1);
			string l = check(g);
			if (l != "-1")
			{
				if (dp[i].empty()) dp[i] = (j == 0 ? "" : dp[j - 1]) + l;
				else dp[i] = min(dp[i], (j == 0 ? "" : dp[j - 1]) + l);
			}
		}
	}
	cout << dp[n - 1] << "\n";
	return 0;
}
```


---

## 作者：依依 (赞：0)

对于选哪一个单词去匹配，我们可以将单词排一下序，优先匹配前面的

用dp[i]表示1-i已经匹配好了的最佳结果

枚举每个单词j去和i每个位置匹配

能够更新当前位置的情况当且仅当

dp[i]==""   或者  dp[i]>dp[i-l[j]]+m[j]  

[代码](http://www.cnblogs.com/adelalove/p/8528466.html)

---

