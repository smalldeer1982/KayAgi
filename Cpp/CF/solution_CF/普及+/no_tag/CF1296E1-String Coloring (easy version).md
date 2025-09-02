# String Coloring (easy version)

## 题目描述

This is an easy version of the problem. The actual problems are different, but the easy version is almost a subtask of the hard version. Note that the constraints and the output format are different.

You are given a string $ s $ consisting of $ n $ lowercase Latin letters.

You have to color all its characters one of the two colors (each character to exactly one color, the same letters can be colored the same or different colors, i.e. you can choose exactly one color for each index in $ s $ ).

After coloring, you can swap any two neighboring characters of the string that are colored different colors. You can perform such an operation arbitrary (possibly, zero) number of times.

The goal is to make the string sorted, i.e. all characters should be in alphabetical order.

Your task is to say if it is possible to color the given string so that after coloring it can become sorted by some sequence of swaps. Note that you have to restore only coloring, not the sequence of swaps.

## 样例 #1

### 输入

```
9
abacbecfd```

### 输出

```
YES
001010101```

## 样例 #2

### 输入

```
8
aaabbcbb```

### 输出

```
YES
01011011```

## 样例 #3

### 输入

```
7
abcdedc```

### 输出

```
NO```

## 样例 #4

### 输入

```
5
abcde```

### 输出

```
YES
00000```

# 题解

## 作者：流绪 (赞：3)

竟然没人发跟 hard 一样的解法！让我来水一发！

我们遍历整个字符串，对于每个位置，看看它前面有没出现比它大的字母，有的话取编号最大的那个加一作为自己的编号，然后记录下自己的编号，跑一遍就好啦，为什么呢？一开始大家都是编号都是 0，现在有一个位置比它前面的小！要交换位置，那么我们把这个位置编号取成前面那个位置加一不就好啦，其他的也是一样的道理。这是 hard 的解法，这里只有 01，那么我们记录所有编号最大值，如果大于 1，就判定为不合法就好啦。

我的代码里是一开始大家都为 1，所以最后输出的时候 -1 了。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define inf 1e9
#define maxn 1000010
#define ri register int
#define il inline
using namespace std;
int sum[maxn] = {0};
int ans[maxn];
int main()
{
	ios::sync_with_stdio(0);
	int n;
	cin >> n ;
	int tot = 0;
	for(int i=1;i<=n;i++)
	{
		char c;
		cin >> c;
		int maxx = 0;
		for(int j=c-'a'+1;j<26;j++)
			maxx = max(maxx,sum[j]);
		ans[i] = maxx+1;
		sum[c-'a'] = max(sum[c-'a'],maxx+1);
		tot = max(tot,maxx+1);
	} 
	if(tot > 2)
		cout << "NO";
	else
	{
		cout << "YES\n";
		for(int i=1;i<=n;i++)
			cout << ans [i]-1;
	}
	return 0;
}
```


---

## 作者：chinaxjh (赞：3)

# 前言
只有我一个人用二分图判定做吗？？怪不得$\text{hard version}$感觉思路不通了
# 分析
很容易想到，对于每一对需要交换的字母对，这两个字母的颜色必定是不同的，我们可以在这两个字母之间连线表示不同，最后如果所形成的图不是二分图，说明无法只用两种颜色染，输出$NO$，否则就把染的色输出

找需要交换的字母对（其实就是逆序对），因为数据较小，可以通过冒泡排序来找出来，详情见程序
# $\text{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef long double ld;
typedef unsigned long long ull;
const int N = 50000;
int len, a[N], nxt[N], las[N], color[N], num[N];
int n, i, j;
char s[N];
void add(int x, int y) {
    len++;
    a[len] = y;
    nxt[len] = las[x];
    las[x] = len;
}//链式前向星
bool dfs(int v, int c) {
    color[v] = c;

    for (int i = las[v]; i; i = nxt[i]) {
        if (color[a[i]] == c)
            return false;
        if (color[a[i]] == 0 && !dfs(a[i], -c))
            return false;
    }
    return true;
}//染色判断

void solve() {
    for (int i = 1; i <= n; ++i) {
        if (color[i] == 0) {
            if (!dfs(i, 1)) {//失败就不是二分图
                cout << "No" << endl;
                return;
            }
        }
    }//图可能不连通
    cout << "Yes" << endl;//是二分图
    for (i = 1; i <= n; i++)
        if (color[i] == 1)
            printf("%d", 0);
        else
            printf("%d", 1);
}

int main() {
    cin >> n;
    scanf("%s", s + 1);
    for (i = 1; i <= n; i++) num[i] = i;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n - 1; j++)
            if (s[j] > s[j + 1]) {
                swap(s[j], s[j + 1]);
                swap(num[j], num[j + 1]);
                add(num[j], num[j + 1]);
                add(num[j + 1], num[j]);
            }//冒泡排序寻找需要交换的字母对，建双向边
    solve();
}
```
# 后记
比赛完之后发现正解是类似导弹拦截？？？心态崩了

$\color{red}\text{提醒:}$像这类邻项交换的题目感觉在最近的比赛中出现不少，对冒泡排序（虽然平时基本不会用）这种类似的原理要有所了解，这样面对这种题目可以更加自信。

---

## 作者：Erica_N_Contina (赞：1)

## EV

给你一串字符串，你可以给字符串的每个位置染上 $0/1$，对于相邻的两个位置，如果他们的颜色不同则可以交换他们的位置。现在需要交换若干次后使得字符串按字典序排序。

如果存在，请输出 `YES` 并且输出一个可行的颜色序列，否则输出 `NO`。

---

我们以 $s_i$ 指代字符串中某个字符的字典序。

假定目前我们已经对字符串染好了色，那么在交换之前的字符串中，很显然颜色相同的两个字符的相对位置是固定的（即对于颜色相同的字符 $s_i,s_j,i<j$，无论怎么交换，$s_i$ 始终在 $s_j$ 的前面。因为如果 $s_j$ 要到 $s_i$ 前面，那么中途肯定会遇到他们俩相邻的情况。这时候我们无法交换他们两，于是就不能让 $s_j$ 到 $s_i$ 前面了）。

对于颜色不同的两个字符 $s_i,s_j$，经过若干次操作，一定可以改变他们的相对位置。这个很简单，仿照上面的证明即可。

所以最终，我们的字符串会被染色成 $0$ 和 $1$ 两个部分，部分内的相对位置不能改变，部分外的相对位置可以改变。所以我们就可以做到一点：我们可以让最终的字符串中被染色成 $0$ 的（我们叫 $0$ 串）都在前面，被染色成 $1$ 的（我们叫 $1$ 串）都在后面。于是我们就要求 $0$ 和 $1$ 的部分都是一个不降的序列，并且只有 $1$ 串的开头大于等于 $0$ 串的结尾时才能成立。

我们还知道，对于原字符串，第一个字符一定属于 $0$ 串或者 $1$ 串，但是由于我们不能保证第一个字符是所有字符中字典序最小的，于是我们就让它成为 $1$ 串的开头。然后我们以第一个字符为 $1$ 串的开头，尽可能选择字典序大的字符加入 $1$ 串中（这样才能保证在 $0$ 串合法的情况下，$1$ 串的开头小于等于 $0$ 串的结尾且 $1$ 串合法），同时保证 $1$ 串是不降的。

---

```C++
#include<bits/stdc++.h>
using namespace std;
#define int long long
 
 
#define rd read()
inline int read()
{
	int xx=0,ff=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') ff=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') xx=xx*10+(ch-'0'),ch=getchar();
	return xx*ff;
}
inline void write(int out)
{
	if(out<0) putchar('-'),out=-out;
	if(out>9) write(out/10);
	putchar(out%10+'0');
}
 
 
const int N=5e5+5;
const int M=5e5+5;
const int INF=1e9+5;
const int MOD=1e9+7;
bool f1;
int m,k,n,qzh;
 
int q;
int t,mn=INF,mx;
int cnt,r;
char s[N],c;
int ans[N],b;
 
bool f2;
 
signed main(){
	// freopen("1.in","r",stdin);
	// freopen("1.out","w",stdout);
	n=rd;
	scanf("%s",s+1);
	
	c=s[1];
	ans[1]=1;
	for(int i=2;i<=n;i++){
		if(s[i]>=c) {
			c=s[i];
			ans[i]=1;
			continue;
		}
		s[++cnt]=s[i];
		ans[i]=0;
	}
	
	for(int i=2;i<=cnt;i++){
		if(s[i]<s[i-1]){
			cout<<"No\n";
			return 0;
		}
	}
	
	cout<<"Yes\n";
	for(int i=1;i<=n;i++)cout<<ans[i];
	return 0;
}
/*
2
3 2 3 6
*/
```




---

## 作者：LZYAC (赞：0)

## 思路

跟 hard 的思路其实一样，只不过这里有无解的情况，那么就是超过两种颜色的情况了。

hard 的思路（**请对照 hard 题面理解**）：寻找前面出现过的字母的最大涂色值，注意一定要与当前字母构成逆序对，那么此字母的涂色值即为上述操作加一。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt,a[200010],maxn[30],n,tmp;
char s[200010];
int main(){
	scanf("%d%s",&n,s+1);
	cnt=1;
	a[1]=1;
	maxn[s[1]-'a']=1;
	for(int i=2;i<=n;i++){
		tmp=0;
		for(int j=s[i]-'a'+1;j<='z'-'a';j++){
			tmp=max(tmp,maxn[j]);
		}
		maxn[s[i]-'a']=tmp+1;
		a[i]=tmp+1;
		cnt=max(cnt,tmp+1);
	}
	if(cnt>2){
		printf("NO");
		return 0;
	}
	printf("YES\n");
	for(int i=1;i<=n;i++) printf("%d",a[i]-1);
	return 0;
}
```

---

## 作者：_masppy_ (赞：0)

### 题目链接：[Link](https://www.luogu.com.cn/problem/CF1296E1)

&nbsp;

### 题目大意：
给定一个长为 $n$ 的字符串，你可以用 $0$ 和 $1$ 两种颜色给字符串中的每个字符依次上色，染色后你可以对相邻的不同颜色的字符进行交换，交换可以进行若干次。求一种合法的染色方案，使得进行若干次这样的交换后字符串中的字符按照字典序从小到大排列。

&nbsp;

### 解题思路：
不难发现，对于颜色相同的数，若 $i<j$，则 $a_i<a_j$，$a_i$ 指字符 $i$ 的字典序。而对于不同颜色的则没有这个要求，因为不论处于何种状况，两个字符显然都能够在一定次数的交换后对调位置。

于是我们只需要保证能够将序列划分为两个不下降子序列即可。显然的，其中一个不下降子序列的开头为编号为 $1$ 的字符，于是乎我们便可以遍历一遍字符串，找出以第一个字符为左端点的不下降子序列，而这个子序列显然需要保证尽可能地选大数，而不是求最长不下降子序列。因为第一个被该子序列排除在外的元素显然会成为另一个不下降子序列的左端点，而对于该点，我们显然希望它越小越好。

可以这样想，对于第一个不属于上述方案的字符的字典序 $i$，假设整个字符串合法，则后续字符的字典序显然不会比 $i$ 更小，因为此时他显然也无法在 $1$ 所属的不下降子序列中取得位置，由此可证这种构造方案是合法的。

代码如下：
```cpp
int main(){
	//freopen("test.in","r",stdin);
	scanf("%d",&n);
	scanf("%s",c+1);
	
	int tot=0;
	char p;
	p=c[1];
	a[1]=1;
	for(int i=2;i<=n;i++){
		if(c[i]>=p) p=c[i],a[i]=1;//寻找最长不下降子序列，同序列的染色为1
		else s[++tot]=c[i],a[i]=0;
		
	}
	
	for(int i=2;i<=tot;i++){
		if(s[i]<s[i-1]){//判断是否构成不下降子序列
			printf("No");
			return 0;
		}
	}
	
	printf("Yes\n");
	for(int i=1;i<=n;i++) printf("%d",a[i]);
	return 0;
}
```
完结撒花 OvO！！！

---

## 作者：Xdl_rp (赞：0)

我是 `A` 了 `hard` 再做这一道题的……

solution
------------

这一题我们看到题目，如果可以交换（$b,a$），定义 $a$ 的染色一定是小于 $b$ 的，故我们可以将本体转化为一个最长下降子序列的问题，相信这种小问题大家都能够解决，所以这里就不多说了（代码上也是有注释的）。

```cpp
#include <bits/stdc++.h>

using namespace std;
int n, m;
string s;
int dp[200005], maxn[205];
/*
dp[i] [i,n]区间内，以S[i]字符为起点的最长下降子序列的长度 
maxn[i] [i+1,n]区间内，以字符S[i]为起点的最长下降子序列的长度 
*/
int main() {
	int n, cnt = 0;
	cin >> n >> s;
	s = " " + s;
	for (int i = n; i >= 1; i--) {//倒序
		int x = s[i] - 'a';//可以看成一个映射
		dp[i] = maxn[x] + 1;//先附成一个初始值
	    for (int j = x + 1; j <= 25; j++) maxn[j] = max(maxn[j], dp[i]);
		cnt = max(dp[i], cnt);//最长下降子序列
	}
	if (cnt > 2) {
		puts("NO");
		return 0;
	}
	puts("YES");
	for (int i = 1; i <= n; i++) {
		printf("%d", dp[i] - 1);
	}
	return 0;
}
```


---

