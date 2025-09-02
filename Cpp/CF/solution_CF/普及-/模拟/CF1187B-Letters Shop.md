# Letters Shop

## 题目描述

字母商店的橱窗其实是一个由 $n$ 个小写字母组成的字符串 $s$！店如其名，这家店就是卖字母的。

字母商店卖的东西很奇怪，卖的方式更奇怪，它只从左往右卖，意思是说，你只能买这个字符串 $s$ 的前缀。

你有 $m$ 个好基友，第 $i$ 个的名字叫做 $t_i$。他们听说了这家店，都打算来买点字母，来拼出自己的名字，当然买来的字母是可以被打乱顺序或者干脆不用的。他们都想知道至少要买下几个字母才能拼出自己的名字。

举几个例子

- $s="arrayhead" , t_i="arya"$时，必须买下$"\underline{array}head"$ $5$个字母

- $s="arrayhead" , t_i="harry"$时，必须买下$"\underline{arrayh}ead"$ $6$个字母

- $s="arrayhead" , t_i="ray"$时，必须买下$"\underline{array}head"$ $5$个字母

- $s="arrayhead" , t_i="r"$时，必须买下$"\underline{ar}rayhead"$ $2$个字母

- $s="arrayhead" , t_i="areahydra"$时，必须买下$"\underline{arrayhead}"$ $9$个字母

字母商店的字母很齐全，所有的朋友肯定都能拼出自己的名字。

要注意的是，你的朋友们都只是在Doing [window shopping](https://baike.baidu.com/item/%E6%A9%B1%E7%AA%97%E8%B4%AD%E7%89%A9/9473660?fr=aladdin&fromid=8209896&fromtitle=Window+shopping)。他们只要你帮他们算出答案，并不会真正买下这些字母。

## 样例 #1

### 输入

```
9
arrayhead
5
arya
harry
ray
r
areahydra
```

### 输出

```
5
6
5
2
9
```

# 题解

## 作者：Eismcs (赞：4)

# 字符串的模拟题

因为时间上很紧，所以主串要通过桶来预处理，让每次询问只用遍历一遍匹配串

主要思路都是用 **桶**来做，比较匹配串的每个字母是否比主串的多，多则说明匹配失败；如果最终匹配成功，要输出每个字母在主串对应字母的最大位置（一开始用桶记录主串每个字母对应在主串的位置），且尽量最小
```cpp
#include<cstdio>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<map> 
using namespace std;
#define re register int
inline int read(){
    int x=0,ff=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')ff=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    return x*ff;
}
char s[500005],ss[500005];
int a[125],b[125],c[28][400005];
int main(){
	int n=read(),m,l,ans;
	scanf("%s",ss+1);
	for(int i=1;i<=n;i++){
		b[ss[i]-'a']++;//记录每个字母主串所有的个数
		c[ss[i]-'a'][b[ss[i]-'a']]=i;
     //记录每个字母出现在主串的位置（升序，以便最大位置最小）
	}
	m=read();bool pk;
	while(m--){
		scanf("%s",s+1);l=strlen(s+1);
		memset(a,0,sizeof(a));ans=-1;pk=0;
		if(l>n){//剪枝，以为如果匹配串字母个数比主串多，主串肯定无法包含每个匹配串的字母
			printf("%d\n",n);continue;
		}
		for(re i=1;i<=l;i++){
			a[s[i]-'a']++;//记录匹配串出现的字母
			if(b[s[i]-'a']<a[s[i]-'a']){
           //判断是否都包含
				printf("%d\n",n);pk=1;break;
			}
			ans=max(ans,c[s[i]-'a'][a[s[i]-'a']]);
        //ans取最大位置
		}
		if(pk)continue;
		printf("%d\n",ans);
	}
    return 0;
}
```


---

## 作者：AC_Dolphin (赞：2)

终于见到一个不恶意评分的cf题了。。

记$a_{i,j}$为$s$中字母$i$出现第$j$次的**下标**，先预处理$a$，时间复杂度$O(n)$，然后对于每一次查询字符串$t$，先统计字母$i$在$t$中出现的次数$m_i$，为了让所有字母都能出现足够次数，$ans$即为$max(ans,a[i][m[i]])$

总时间复杂度为$O(\Sigma |t|)$

注意：因为字符串下标从$0$开始，所以输出$ans$时要$+1$.

$Code:$
```cpp
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for((i)=0;(i)<(n);(i)++)
int n,m,a[30][1000000],t[30];
string s;
typedef long long ll;
int read(){
	char ch=getchar();
	int f=1,x=0;
	while(ch<'0'||ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
	return x*f;
}
int lowbit(int x){
	return x&(-x);
}
int main(){
	n=read();
	cin>>s;
	for(int i=1;i<=26;i++) for(int j=1;j<=10;j++) a[i][j]=-1;//因为下标可能是0，所以处理成-1
	for(int i=0;i<s.length();i++) a[s[i]-'a'+1][++t[s[i]-'a'+1]]=i;
	//for(int i=1;i<=26;i++) {for(int j=1;j<=10;j++) cout<<a[i][j]<<" ";cout<<endl;}
	m=read();
	while(m--){
		string t;
		cin>>t;
		int m[30]={0},ans=0;
		for(int i=0;i<t.length();i++) m[t[i]-'a'+1]++;
		//for(int i=1;i<=26;i++) cout<<m[i]<<" ";
		//cout<<endl;
		for(int i=1;i<=26;i++) ans=max(ans,a[i][m[i]]);
		printf("%d\n",ans+1);//注意+1
	}
	return 0;
}
```

---

## 作者：Meatherm (赞：1)

这里提供$O(n*log(n))$的做法，常数不算特别优秀。

## 思路
我们可以对主串$s$搞一个类似于前缀和的东西——$a[][]$。$a[i][j]$表示主串的第$1$位到第$i$位一共有多少个字符$j$。再对每一个子串进行统计，得到数组$b[]$。$b[i]$表示子串中含有多少个字符$i$。

容易发现，对于题目要求的$ans$，有$a[ans][i]≥b[i]$，且具有单调性。使用二分答案即可。


## 代码

```
# include <bits/stdc++.h>
# define rr register
int n,m;
std::string s;
int a[200010][30];
std::string tmp;
int b[40];
int main(void){
	scanf("%d",&n);//读入字符串的长度（感觉没啥用）
	std::cin>>s;
	s=" "+s;//为了使下标从1开始
	int slen=s.size();
	for(rr int i=1;i<slen;++i){//注意是< 防止越界
		for(rr int j=1;j<=26;++j)
			a[i][j]=a[i-1][j];
		++a[i][s[i]-'a'+1];//给当前位置的字符+1 其它不变
	}
	scanf("%d",&m);
	while(m--){
		std::cin>>tmp;
		tmp=" "+tmp;//读入子串
		int len=tmp.length();
		memset(b,0,sizeof(b));
		for(rr int i=1;i<len;++i)
			++b[tmp[i]-'a'+1];//计算出子串需要的每一个字符数量
		int l=1,r=slen-1,ans;//二分判断
		while(l<=r){
			int mid=(l+r)>>1;
			bool flag=true;
			for(rr int i=1;i<=26;++i){
				if(a[mid][i]<b[i]){
					flag=false;
					break;//只要有一个不够 那么就是不成功的
				}
			}
			if(!flag)
				l=mid+1;//如果不行 那么把位数往右移
			else ans=mid,r=mid-1;//否则记录答案
		}
		printf("%d\n",ans);
	}
	return 0;
}
```

---

## 作者：L2_sheep (赞：1)

这道题可以用一个链表来做，用next数组作为和当前字母相同的下一个位置，head数组记录字母当前的开头位置。只要从后向前做，就可以符合题目的要求了。
具体代码如下：
```cpp
#include <stdio.h>
#define N 200002

char s[N], t[N], x;
int next[N] = {0}, head[128] = {0};

int main()
{	
	int n, i, j, k, m, y;
	
	scanf("%d%s", &n, s + 1);
	for(i = n; i; i--){
		x = s[i];
		next[i] = head[x];
		head[x] = i;
	}
	
	scanf("%d", &m);
	while(m--){
		int p[128] = {0}, ans = 0;
		scanf("%s", t);
		for(i = 0; t[i]; i++){
			x = t[i];
			if(!p[x]) y = p[x] = head[x];
			else y = p[x] = next[p[x]];
			if(y > ans) ans = y; 
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
```


---

## 作者：CodingOIer (赞：0)

## CF1187B Letters Shop 题解

### 思路分析

本题的主要问题在如何快速求出最先满足条件的位置。

然后我们就有了一个「二分答案」的方法

对于我们取到的 $mid$，通过「前缀和」来判断是否满足条件。

复杂度 $O(N + 26 \times M \times \log_N)$。

而我们可以通过分别计算满足每个字母的最短位置并对其取 $\max$ 来简化。

而每个字母的第 $i$ 个的位置我们可以通过「预处理」得出。

预处理代码：

```cpp
for (int i = 0; i < 26; i++)
{
    meet[i].push_back(0);
}
for (int i = 1; i <= n; i++)
{
    int c = s[i] - 'a';
    meet[c].push_back(i);
}
```

这时我们便可以 $O(1)$ 得知单个字符的最短位置。

复杂度 $O(N + 26 \times |T|)$。

### 代码实现

仅给出复杂度更优的预处理做法的代码。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
constexpr int MaxN = 2e5 + 5;
int n, m;
int p[26];
char s[MaxN];
char t[MaxN];
std::vector<int> meet[26];
int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    for (int i = 0; i < 26; i++)
    {
        meet[i].push_back(0);
    }
    for (int i = 1; i <= n; i++)
    {
        int c = s[i] - 'a';
        meet[c].push_back(i);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", t + 1);
        int k = strlen(t + 1);
        int max = 0;
        memset(p, 0, sizeof(p));
        for (int j = 1; j <= k; j++)
        {
            p[t[j] - 'a']++;
        }
        for (int j = 0; j < 26; j++)
        {
            max = std::max(max, meet[j][p[j]]);
        }
        printf("%d\n", max);
    }
    return 0;
}
```

---

## 作者：lostxxx (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1187B)

# 题目大意

有 $m$ 次询问，在每次询问给出的字符串 $t$ 中的所有字符在已给定字符串 $s$ 中前多少个字符能够集齐。

# 题目分析

我们可以定义一个前缀和数组 $S_{i,j}$，其中 $i$ 代表字母 $a$ 到字母 $z$，$j$ 代表出现第 $j$ 次的位置，其中第 $j$ 次可以用一个数组 $pos$ 来维护。

随后再在每次询问中利用一个数组 $sum$ 来求得每个字母出现的次数，最后在遍历一次求得最大的位置。

$code$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll s[30][200100];
ll pos[30];
string a;
ll n,m;
string t;
int main(){
    //cout<<int('a');
    cin>>n;
    cin>>a;
    for (int i=0;i<a.size();i++){
        pos[a[i]-96]++;
        s[a[i]-96][pos[a[i]-96]]=i+1;
    }
    cin>>m;
    while(m--){
        cin>>t;
        ll ans=0;
        ll sum[30];
        memset(sum,0,sizeof(sum));
        for (int i=0;i<t.size();i++)
            sum[t[i]-96]++;
        for (int i=1;i<=26;i++){
            ans=max(ans,s[i][sum[i]]);
        }
        cout<<ans<<endl;
    }
}
```

---

## 作者：YangXiaopei (赞：0)

## Solution:

我们定义 $f_{i, j}$ 表示第 $i$ 种字母到第 $j$ 位的个数。

$k_i$ 表示当前字符串第 $i$ 种字母的个数。我们枚举每个字母 $i$，找 $f_i$ 中第一个大于等于 $k_i$ 的元素下标，全部取 $\max$ 即可。

[AC记录](https://www.luogu.com.cn/record/143541366)

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n, m, k[30], f[30][200005];
string s, t;
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> s >> m;
	for(int i = 0; i < s.size(); i++){
		for(int j = 0; j < 26; j++){
			if(i == 0){
				break;
			}
			f[j][i] = f[j][i - 1];
		}
		f[s[i] - 'a'][i]++;
	}
	while(m--){
		cin >> t;
		memset(k, 0, sizeof(k));
		for(int i = 0; i < t.size(); i++){
			k[t[i] - 'a']++;
		}
		int maxn = 0;
		for(int i = 0; i < 26; i++){
			int x = lower_bound(f[i], f[i] + s.size(), k[i]) - f[i];
			maxn = max(maxn, x + 1);
		}
		cout << maxn << "\n";
	}
	return 0;
}
```

---

## 作者：tder (赞：0)

[$\Large\color{black}\textbf{CF1187B Letters Shop}$](https://www.luogu.com.cn/problem/CF1187B) $\Large\textbf{题解}$

[$\textbf{题目传送门}$](https://www.luogu.com.cn/problem/CF1187B)

[$\textbf{更好的阅读体验}$](https://www.luogu.com.cn/blog/tder/solution-cf1187B)

~~前缀+字符串模拟~~

---

$$\large\textbf{思路}$$

用 $a_i$ 数组统计原字符串中第 $i$ 个字母出现的次数，$b_{i,j}$ 表示 第 $j$ 个字母首次出现 $i$ 次的下标。

用 $c_i$ 统计名字中第 $i$ 个字母出现的次数。

则 $b_{c_i,i}$ 即第 $i$ 个字母首次出现 $c_i$ 次的下标的最大值就是答案。

---

$$\large\textbf{代码}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[26], b[int(1e6 + 5)][26], c[26];
string s;
int main() {
	cin>>n>>s>>m;
	for(int i = 0; i < s.length(); i++) { // 遍历原串
		a[s[i] - 'a']++; // 统计原串中各字母出现的次数
        b[a[s[i] - 'a']][s[i] - 'a'] = i + 1; // 标记首次出现若干次的位置
	}
	while(m--) {
		string p;
		cin>>p;
		for(int i = 0; i < 26; i++) c[i] = 0; // 注意初始化
		for(int i = 0; i < p.length(); i++) 
			c[p[i] - 'a']++; // 统计名字中各字母出现的次数
		int ans = 0;
		for(int i = 0; i < 26; i++)
			ans = max(ans, b[c[i]][i]); // 打擂台取最大值
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：HEzzz (赞：0)

[题目跳转键](https://www.luogu.com.cn/problem/CF1187B)

## 题目大意：

给你一个长度为 $n$ 字符串 $s$，然后 $m$ 次询问，一次询问给出一个字符串 $t$，让你给出一个最小的答案 $ans$，表示 $s$ 的前 $ans$ 个字符匀包括 $t$ 的所有字符。

---

乍一看，显然要维护一下 $t$ 中每一个字符出现的数量。但是我们发现数据范围还是比较大的，$n$ 和 $t$ 的长度最大都到了 $2\times 10^5$，$m$ 最大到了 $5\times 10^4$，很容易发现 $O(n^2)$ 是过不去了的，所以我们可以用一个数组 $a_i,_j$ 表示字符串 $s$ 的前 $i$ 位有多少个字符 $j$。这样我们就可以节省大量的时间了。

但是想到这里还远远不够，我们可以想一下使用二分答案，首先我们知道使用二分这个算法的前提条件就是必须要有单调性。这道题显然可以使用二分答案，我们只需要二分最后的答案即可。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,p[N][30],cnt[30];
char a[N],s[N]; 
bool check(int Mid)//check函数看一下这个答案是否可行
{
	for(int i=1;i<=26;i++)
	{
		if(p[Mid][i]<cnt[i]) return false;
	}
	return true;
}
int main() 
{
	scanf("%d%s",&n,(s+1));
	int len=strlen(s+1);
	for(int i=1;i<=len;++i)//计算出前i位有多少个字符j
	{
		for(int j=1;j<=26;j++) p[i][j]=p[i-1][j];//记住必须把上一位的答案粘贴到下一位
		p[i][s[i]-'a'+1]++;
	}
	scanf("%d",&m);
	while(m--)
	{
		scanf("%s",(a+1));
		int sze=strlen(a+1);
		memset(cnt,0,sizeof(cnt)); 
		for(int i=1;i<=sze;i++) cnt[a[i]-'a'+1]++;//统计要询问的字符串每一个字符出现的次数
		int l=0,r=len+1;
		while(l+1<r)//一个二分的板子
		{
			int mid=(l+r)>>1;
			if(check(mid)) r=mid;
			else l=mid;
		}
		printf("%d\n",r);
	}
	return 0;
}
```
# 完结撒花

---

