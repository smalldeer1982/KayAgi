# Remove Adjacent

## 题目描述

You are given a string $ s $ consisting of lowercase Latin letters. Let the length of $ s $ be $ |s| $ . You may perform several operations on this string.

In one operation, you can choose some index $ i $ and remove the $ i $ -th character of $ s $ ( $ s_i $ ) if at least one of its adjacent characters is the previous letter in the Latin alphabet for $ s_i $ . For example, the previous letter for b is a, the previous letter for s is r, the letter a has no previous letters. Note that after each removal the length of the string decreases by one. So, the index $ i $ should satisfy the condition $ 1 \le i \le |s| $ during each operation.

For the character $ s_i $ adjacent characters are $ s_{i-1} $ and $ s_{i+1} $ . The first and the last characters of $ s $ both have only one adjacent character (unless $ |s| = 1 $ ).

Consider the following example. Let $ s= $ bacabcab.

1. During the first move, you can remove the first character $ s_1= $ b because $ s_2= $ a. Then the string becomes $ s= $ acabcab.
2. During the second move, you can remove the fifth character $ s_5= $ c because $ s_4= $ b. Then the string becomes $ s= $ acabab.
3. During the third move, you can remove the sixth character $ s_6= $ 'b' because $ s_5= $ a. Then the string becomes $ s= $ acaba.
4. During the fourth move, the only character you can remove is $ s_4= $ b, because $ s_3= $ a (or $ s_5= $ a). The string becomes $ s= $ acaa and you cannot do anything with it.

Your task is to find the maximum possible number of characters you can remove if you choose the sequence of operations optimally.

## 说明/提示

The first example is described in the problem statement. Note that the sequence of moves provided in the statement is not the only, but it can be shown that the maximum possible answer to this test is $ 4 $ .

In the second example, you can remove all but one character of $ s $ . The only possible answer follows.

1. During the first move, remove the third character $ s_3= $ d, $ s $ becomes bca.
2. During the second move, remove the second character $ s_2= $ c, $ s $ becomes ba.
3. And during the third move, remove the first character $ s_1= $ b, $ s $ becomes a.

## 样例 #1

### 输入

```
8
bacabcab```

### 输出

```
4```

## 样例 #2

### 输入

```
4
bcda```

### 输出

```
3```

## 样例 #3

### 输入

```
6
abbbbb```

### 输出

```
5```

# 题解

## 作者：Blunt_Feeling (赞：7)

# CF1321C Remove Adjacent 题解
这是一道普通的字符串贪心题。~~本蒟蒻是这么认为的，至于其他dalao们写的DP和链表，本蒟蒻只能疯狂%%%了。~~

思路是遍历26个英文字母，对于遍历到的每个字母 $c_{i}$ ，把字符串 $s$ 中的每个元素遍历，一旦遇到一个等于 $c_{i}$ 的字符 $s_{j}$ ，满足 $s_{j-1}$ 或 $s_{j+1}$ 中有一个是 $s_{j}$ 的前驱，就用C++ _string_ 中的 _erase()_ 函数把这个字符删掉，接着把字符串再次从头遍历。当字符串 $s$ 中没有一个字符 $s_{j}$ 满足 $s_{j-1}$ 或 $s_{j+1}$ 中有一个是 $s_{j}$ 的前驱时，就把 $c_{i}$ 换成下一个字母。

在遍历26个英文字母时，要注意是从'z'到'b'遍历，因为我们要算它的前驱。

把推导的思路加上一些简单的调(ya)整(hang)，就得到了如下13行代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n; string s;
	cin>>n>>s;
	for(int i='z';i>'a';i--) //这里i的类型也可以是char
		for(int j=0;j<s.length();j++)
			if(s[j]==i&&(j>0&&s[j-1]==i-1 || j<s.length()-1&&s[j+1]==i-1))//要注意不能越界
				s.erase(j,1),j=-1;//删除s[j]，别忘了把j设成-1
	cout<<n-s.length()<<endl;//输出删去字符的总数
	return 0;
}
```
由于题目中说 $1≤∣s∣≤100$ ，所以大家可以轻松~~水~~过此题。

---

## 作者：dblark (赞：4)

贪心。发现从大到小删除无后效性（从 `z` 到 `b`），也就是说这样删除是最优的。

观察到数据范围非常小，每次删除暴力枚举即可，同时可以保证正确。

这里使用链表删除。

```cpp
#include <cstdio>

int n;
char s[105];
int a[105], pre[105], nxt[105], vis[105];

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    a[0] = a[n + 1] = -1;
    for (int i = 1; i <= n; ++i) a[i] = s[i - 1] - 'a', pre[i] = i - 1, nxt[i] = i + 1;
    int ans = 0;
    for (int i = 25; i; --i)
        for (int nfst = 1; nfst <= 100; ++nfst)
            for (int j = 1; j <= n; ++j)
                if (!vis[j] && a[j] == i && (a[pre[j]] == i - 1 || a[nxt[j]] == i - 1)) {
                    vis[j] = 1;
                    ++ans;
                    nxt[pre[j]] = nxt[j];
                    pre[nxt[j]] = pre[j];
                }
    printf("%d\n", ans);
    return 0;
}
```


---

## 作者：xiaomuyun (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1321C)

## 题目分析

考虑贪心。

因为每次删除一个字符只需要考虑前驱不用考虑后继，所以可以从 `z` 到 `b` 倒着删，这样能保证不会有字符因为相邻的前驱被删掉了而不能删掉。

## 代码实现
```cpp
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int n,cnt=0;
string s;
int main(){
	scanf("%d",&n);
	cin>>s;
	for(auto c:"zyxwvutsrqponmlkjihgfedcb"){//倒着遍历
		for(int i=0;i<s.length();++i){
			if(s[i]!=c) continue;
			if((i>0&&s[i]==s[i-1]+1)||(i<s.length()-1&&s[i]==s[i+1]+1)) s.erase(i,1),++cnt,i=-1;//找前驱，删除字符
		}
	}
	printf("%d\n",cnt);
	return 0;
}
```

---

## 作者：AlanSP (赞：1)

不会DP解决，考虑贪心qwq。

很容易看出，优先删排在后面的z，y，x……

由于n很小，所以我们可以直接扫26遍，依次删除。

但是不好维护相邻关系。

于是可以考虑双向链表，用数组模拟指针。

每次删除时都把指针换位。

----

存在Hack数据，比如多个z，y不相邻。

这样只扫26遍是远远不够的。

直接在此基础上扫多次（我取得109），保证能够全部把该删的删除即可。

（while写在里面，不然过不去test12。）

~~反正n<=100你咋搞都行。~~

```cpp
#include <bits/stdc++.h>
using namespace std;
 
int n,ans;
char s[109];
int pl[109],pp[109];
bool y[109];
 
int main()
{
	scanf("%d",&n);
	memset(y,true,sizeof y);
	for(int i=1;i<=n;i++) 
	{
		pl[i]=i-1;
		pp[i]=i+1;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>s[i];
	}
	for(char i='z';i>'a';i--)
	{
		int cnt=109;
		while(cnt)
		{
			for(int j=1;j<=n;j++)
			{
			if(!y[j]) continue;
			if(s[j]==i)
			{
				if(s[pl[j]]==i-1)
				{
					pl[pp[j]]=pl[j];
					pp[pl[j]]=pp[j];
					y[j]=false;
					ans++;
					continue;
				}
				if(s[pp[j]]==i-1)
				{
					pl[pp[j]]=pl[j];
					pp[pl[j]]=pp[j];
					y[j]=false;
					ans++;
				}
			}
			}
			cnt--;
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
给出字符串 $s$，$1\le|s|\le100$.

定义一次变换为，选中第 $i$ 个字符移除，字符串长度减少 $1$，选中字符需要满足  $s_{i-1},s_{i+1}$ 中至少有一个是 $s_i$ 的前驱.

求最多可进行几次操作.

## $\text{Solution}$
可以发现，在所有可以删除的字母中，每次贪心的删除最靠后的一定是不劣的.  
开一个堆来维护当前可以删除的所有字母，每次取出最大值删除并判断两侧的是否变得可以删除即可.  
删除可以使用链表 $O(1)$ 实现，总复杂度 $O(n\log n)$.  
细节上，注意要判断一下不要重复使同一个元素入堆.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=3e5+100;
const int mod=1e9+7;
const double eps=1e-9;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;
struct node{
  int val,pl;
  bool operator < (const node oth)const{return val<oth.val;}
};
priority_queue<node>q;
char s[105];
int l[105],r[105];
inline bool check(int x){
  return (l[x]&&s[x]-s[l[x]]==1)||(r[x]<=n&&s[x]-s[r[x]]==1);
}
bool vis[105];
int main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  scanf(" %s",s+1);
  for(int i=1;i<=n;i++){
    l[i]=i-1;r[i]=i+1;
  }
  r[0]=1;l[n+1]=n;
  for(int i=1;i<=n;i++){
    if(check(i)) q.push((node){s[i]-'a'+1,i}),vis[i]=1;
  }
  int ans(0);
  while(!q.empty()){
    int pl=q.top().pl;q.pop();
    //printf("pl=%d\n",pl);
    ++ans;
    l[r[pl]]=l[pl];r[l[pl]]=r[pl];
    if(!vis[l[pl]]&&check(l[pl])) q.push((node){s[l[pl]]-'a'+1,l[pl]}),vis[l[pl]]=1;
    if(!vis[r[pl]]&&check(r[pl])) q.push((node){s[r[pl]]-'a'+1,r[pl]}),vis[r[pl]]=1;
  }
  printf("%d\n",ans);
  return 0;
}

```



---

## 作者：Meatherm (赞：0)

考虑 DP。

设 $f_{i,j}$ 表示 $[i,j]$ 内的所有字符能不能被删除。对于 $i=j$，若 $s_{i-1},s_{i+1}$ 其中的任意一个是 $s_i$ 的前驱，则 $f_{i,j}=1$，否则 $f_{i,j}=0$。

而对于 $i< j$，若出现下列三种情况之一，则 $f_{i,j}=1$，否则 $f_{i,j}=0$：

- $[l+1,r]$ 的每个字符都可以被删除，$s_l$ 可以被 $s_{r+1}$  删除。
- $[l,r-1]$ 的每个字符都可以被删除，$s_r$ 可以被 $s_{l-1}$ 删除。
- 存在点 $k \in [l,r)$，使得 $f_{l,k}=f_{k+1,r}=1$。

在 DP 结束之后，找出所有不相交且满足 $f_{l,r}=1$ 的区间 $[l,r]$，它们的长度和即为答案。

```cpp
# include <bits/stdc++.h>
# define rr register
const int N=110,INF=0x3f3f3f3f;
bool f[N][N];
char s[N];
int n;
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
int main(void){
	n=read();
	scanf("%s",s+1);
	for(rr int i=1;i<=n;++i){
		if(s[i]-s[i-1]==1||s[i]-s[i+1]==1)
			f[i][i]=true;
	}
	for(rr int i=2;i<=n;++i){
		for(rr int l=1;l+i-1<=n;++l){
			int r=l+i-1;
			if(f[l+1][r]&&s[l]-s[r+1]==1){
				f[l][r]=true;
			}
			if(f[l][r-1]&&s[r]-s[l-1]==1){
				f[l][r]=true;
			}
			for(rr int k=l;k<r;++k){
				if(f[l][k]&&f[k+1][r]){
					f[l][r]=true;
					break;
				}
			}
		}
	}
	int ans=0,l=1;
	while(l<=n){
		for(rr int r=n;r>=l;--r){
			if(f[l][r]){
				ans+=(r-l+1);
				l=r+1;
				goto End;
			}
		}
		++l;
		End:;
	}
	printf("%d",ans);
	return 0;
}

```

---

## 作者：formkiller (赞：0)

### Problem :
给出字符串 $s$，$1\le|s|\le100 $。

定义一次变换为，选中第 $i$ 个字符移除，字符串长度减少 $1$，选中字符需要满足 $s_{i-1},s_{i+1}$ 中至少有一个是 $s_i$ 的前驱。

求最多可删除几个字符。



------------
### Solution :
考虑到每次删除操作都会把较大的字符删掉，也就是说，**先把大的字符删掉对小的字符不会破坏更优性**，如先考虑把字符 $z$ 删掉再删去字符 $y$ 不会破坏字符 $y$ 的选择，因为字符 $y$ 的删除操作与字符 $z$ 无关。

所以我们考虑从大到小枚举删除的字符种类，即做到先删除大的字符，再删去小的字符。由于删除一个字符以后可能会出现新的合法情况，所以可以考虑用双向链表的思想存储。每次删去一个节点之后，回跳到该字符的左边，同时跟右边进行比较。细节详见代码注释。



------------
### Code :
```cpp
//good luck
# include <iostream>
# include <cstdio>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <string>
# include <algorithm>

#define LL long long
#define maxn int(1e5+5)
#define is(a) (a>='0'&&a<='9')
#define iis(a) (a>='a'&&a<='z')

using namespace std;

int N,L[maxn],R[maxn],ans;

char st[maxn];

inline void read(int &x)
{
  x=0;bool f=0;char ch=getchar();
  for (;!is(ch);ch=getchar()) f|=ch=='-';
  for (;is(ch);ch=getchar()) x=(x<<3)+(x<<1)+(ch^48);
  x=f?-x:x;
}

inline void reads()
{
  int len=0;char ch=getchar();
  for (;!iis(ch);ch=getchar());
  for (;iis(ch);ch=getchar()) st[++len]=ch;
}

int main()
{
//	freopen("a.in","r",stdin);
	read(N); reads();
	R[0] =  1; L[N + 1] = N;
	for (int i = 1; i <= N; ++i)
	{
		L[i] = i - 1;
		R[i] = i + 1; 
	}
	for (int j = 26; j >= 1; --j)      //先删掉较大的字符
	for (int i = R[0]; i <= N; i = R[i])
	{
		if (st[i]==j + 'a' - 1)
		{
			int k=L[i];
			if (st[i]-st[L[i]]==1)
			{
				++ans;
				R[L[i]] = R[i];
				L[R[i]] = L[i];
				L[i]=R[i]=0; //这里是debug的时候加上去的，实际影响应该不大
				i = L[k]; //回跳(本来是要跳到L[i]的,但是循环结束后会执行i=R[i],所以这里实际上等价于i=L[L[i]])
			}
			else if (st[i]-st[R[i]]==1)
			{
				++ans;
				R[L[i]] = R[i];
				L[R[i]] = L[i];
				L[i]=R[i]=0;
				i = L[k];  //下面同理
			}
		}
	}
	cout << ans << endl;
    return 0;
}
```

---

## 作者：Reanap (赞：0)

这道题还是蛮有意思的。

当一个字母的前驱或者后继是它的字典序的后继的话就可以删除。

我们必须找到一种没有后效性的做法。

观察发现，$z$字母在字典序中是没有后继的，也就是没有一个字母能够因为它而删除，所以删除它是没有后效性的。

如果成功删除，那么又有可能出现新的$z$可以被删除，所以我们继续看$z$

否则，我们认为没有哪一个$z$可以被删除，于是我们考虑删除此时没有后效性的$y$，若成功删除，那么有可能会出现可以被删除的$z$，所以我们要再检查一遍。

以此类推，直到每一个字母都不再能被删除
~~好怂啊~~


```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
char s[105];
int n , la[105] , nxt[105] , beg;
int check(char x) {
	int now = nxt[0];
	int f = 0;
	while(now <= n) {
		if(s[now] == x) {
			if(s[now] - 1 == s[la[now]] || s[now] - 1 == s[nxt[now]]) {
				f ++;
				nxt[la[now]] = nxt[now];
				la[nxt[now]] = la[now];	
			}
		}
		now = nxt[now];
	}
	return f;
}
int main() {
	scanf("%d" , &n);
	scanf("%s" , s + 1);
	nxt[0] = 1;
	for (int i = 1; i <= n; ++i) {
		la[i] = i - 1;
		nxt[i] = i + 1;
	}
	int ans = 0;
	for (int i = 25; i >= 0; --i) {
		int cur = check('a' + i);
		if(cur > 0) {
			i = 26;
			ans += cur;
		}
	}
	printf("%d" , ans);
	return 0;
}
```

---

## 作者：流绪 (赞：0)

来一发 STL string 的题解！

为什么用 string ？因为他们 erase 函数，作用是删除字符串的某个位置。

他有很多种使用方法，具体可以百度，这里我们用单位置删除

定义 string s,s.erase(i,j)，从 string 的第 i 位开始，删除 j 个字符！

因为要删最多的字符且相邻位置有该字母的前驱才可以删，那么贪心的从 z 往前做，这样肯定是没有问题的，因为对于每个字母只对其后面的字母有影响，而这些字母都在之前做过了！

注意一个细节，如同楼上老哥说的回首掏。

abbbb 与 bbbba

如果只从一个方向做，那么必然对于上面有一个答案是错误的！

所以我们从后向前枚举每一个字母，然后两个方向遍历字符串，统计答案即可。

下面是 AC 代码。
```cpp
#include<bits/stdc++.h>
#define int long long
#define ld long double
#define inf 0x7f7f7f7f
#define maxn 1000010
#define ri register int
#define il inline
#define mod 1000000009
using namespace std;
string s;
signed main()
{
	ios::sync_with_stdio(0);
	int n;
	cin >> n >> s;
	int cnt = 0;
	s = " " +s;
	for(int i=25;~i;i--)
	{
		for(int j=1;j<s.length();j++)
			if(s[j]==i+'a')
			{
				if(s[j-1]==i+'a'-1)
					s.erase(j,1),cnt++,j--;
             //j--是因为每次循环结束有个j++
             //而我们删完后已经把下一个要判断的字母移到j位了
             //避免j++的影响 所以这里j--
				else if(s[j+1]==i+'a'-1)
					s.erase(j,1),cnt++,j--;
			}
		for(int j=s.length()-1;j;j--)
			if(s[j]==i+'a')
			{
				if(s[j-1]==i+'a'-1)
					s.erase(j,1),cnt++,j++;
				else if(s[j+1]==i+'a'-1)
					s.erase(j,1),cnt++,j++;
			}
	}
	cout << cnt ;
  	return 0;
}
```


---

## 作者：dead_X (赞：0)

## 1 题意简述
输入一个小写字母字符串 $S(|S|\leq 100)$ ， 对于所有的字符，如果左右有这个字符的前继则可以删除，删除后会形成新的序列，问最多能删除多少的字符。 
## 2 思路简述
贪心，最后的字符留着没有意义，能删则删

模拟链表

从后往前枚举即可
## 3 代码
```
#include<bits/stdc++.h>
using namespace std;
int a[1003],nxt[1003],pre[1003];
int main()
{
	int n,ans=0;
	scanf("%d",&n);
	char ch=getchar();
	for(int i=1; i<=n; i++) ch=getchar(),a[i]=(int)ch-(int)'a'+1,nxt[i]=i+1,pre[i]=i-1;
	int head=0,tail=n+1;
	nxt[0]=1,pre[n+1]=n;
	for(int i=26; i>1; i--) 
	{
		int now=nxt[head];
		while(now!=tail) 
		{
			if((a[pre[now]]==i-1 || a[nxt[now]]==i-1) && a[now]==i) 
			{
				pre[nxt[now]]=pre[now],nxt[pre[now]]=nxt[now],ans++;
				if(now==head) nxt[now]=head;
				if(now==tail) pre[now]=tail;
				if(now==head) now=nxt[now]; else now=pre[now];
			}
			else
			now=nxt[now]; 
		}
	}
	cout<<ans;
	return 0;
}
```
## 4 评价
赛时想出做法所用时间:9min

比赛A掉所用时间:35min

建议难度:橙/黄

链表好难调/kk

---

