# [ABC124D] Handstand

## 题目描述

有一个长为 $n$ 的字符串 $s$，只含 $0$ 和 $1$。  
你可以进行最多 $k$ 次如下操作（$0$ 次也可以）：

- 选择字符串 $s$ 的一个子串，将其中的字符反转（$0$ 变成 $1$，$1$ 变成 $0$）。

进行不超过 $k$ 次操作后，求最长的连续的 $1$ 的长度。

## 样例 #1

### 输入

```
5 1
00010```

### 输出

```
4```

## 样例 #2

### 输入

```
14 2
11101010110011```

### 输出

```
8```

## 样例 #3

### 输入

```
1 1
1```

### 输出

```
1```

# 题解

## 作者：_maojun_ (赞：4)

注：下文称连续的若干个 $1$ 为 $1$ 串，连续的若干个 $0$ 为 $0$ 串。

---

因为要求的是最长的连续 $1$，所以只用考虑反转至多 $k$ 个 $0$ 串的最大收益，其实和求固定长度的最大子串和也差不多。

一个滑动的窗口，一直加入元素。若需要加入一个 $0$ 串时，发现已经有了 $k$ 个 $0$ 串，就移除最后添加的 $0$ 串以及它再之前的 $1$ 串（已经连不上的）。

先预处理用成若干个 $0$ 串和 $1$ 串将原字符串表示出来，我用的是 $0$ 串记为正数，$1$ 串记为负数。比如样例的 `11101010110011` 就处理成 `-3 1 -1 1 -1 1 -2 2 -2`。然后用滑动窗口处理即可。

假设现在加入的 $i$ 号串为 $0$ 串，且现在（加入前）已有 $k$ 个 $0$ 串，则要删除 $0$ 串 $i-2k$ 和 $1$ 串 $i-2k-1$的贡献。

为什么是 $i-2k$ 呢？因为很显然，处理后的序列必然是 $01$ 相间的，那么 $i$ 前的第 $1$ 个 $0$ 串即是 $i-2$，第 $k$ 个即是 $i-2k$。而 $i-2k-1$ 是在删除 $i-2k$ 后已经无法联通的，所以也要去除。

复杂度 $O(n)$。

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;

const int MAXN=1e5+5;
int n,k,tot,a[MAXN],t[MAXN]; 

void read(){
    for(int i=1;i<=n;i++) scanf("%1d",&t[i]);
    if(t[1]==0) a[tot=1]=1;     // 预处理 0/1 串 
    else a[tot=1]=-1;
    for(int i=2;i<=n;i++)
        if(t[i]==t[i-1]){
            if(t[i]==0) a[tot]++;
            else a[tot]--;
        }
        else{
            if(t[i]==0) a[++tot]=1;
            else a[++tot]=-1;
        }
    n=tot;
} 
int main(){
    scanf("%d%d",&n,&k);
    read();
    int maxn=0,now=0,val=0;     // now 表示当前 0 串的个数，val 是当前的子串和。 
    for(int i=1;i<=n;i++){ 
        if(a[i]>0){				// 如果当前加入的是 0 串 
            if(now==k) val-=a[i-2*k]-a[i-2*k-1];    // 去除过期元素，注意因为 a[i-2*k-1] 是 1 串，用的是负数记录，要用减法，等价于 +(-a[i-2*k-1]) 
            else now++;
        }
        val+=abs(a[i]);         // 加入当前元素（注意是绝对值） 
        maxn=max(maxn,val);     // 在所以状态中取最大 
    }
    printf("%d\n",maxn);
    return 0;
}
```

Q：你这样写不就没法计算到后缀的贡献了吗？

A：因为每个元素的贡献都是正的，所以后缀中最优的就是在合法情况下的极长后缀，而这个在加入最后一个元素的时候是计算了的，故后面的算不算都无所谓。

同样的道理其实前缀也是没有必要的，但这样写可以规避掉 $k$ 大到能让整个序列全部变成 $1$ 的情况。还是同样的道理选取非前缀非后缀的中间子串也是选极长子串。

---

## 作者：wjr_jok (赞：3)

求最长连续子序列，很明显可以用双指针。

挨个遍历 $01$ 块，当前块为 $0$ 时，如果当前还能修改，那肯定就改，更新最大值。否则就将最前面的一次修改取消（因为只有这样才能保证字串的连续性），用来修改这一段。

统计时，块为 $1$ 时直接加入答案即可。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l,r,cnt,ans;
char s;
int xl[100001];
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){//转为int
		cin>>s;
		xl[i]=s-'0';
	}
	while(l<=r&&r<n){
		if(!xl[r+1]){//为0块
			if(k){//能改
				k--;
				while(!xl[r+1]&&r<n){//将这个块改完
					r++;
					cnt++;
				}
				while(xl[r+1]&&r<n){//顺便把下一个1块也算上
					r++;
					cnt++;
				}
				ans=max(ans,cnt);
			}
			else{//不能改
				k++;
				while(xl[l+1]&&l<=r){//把前面的删了
					l++;
					cnt--;
				}
				while(!xl[l+1]&&l<=r){//最前面的1块因为断开了也要删去
					l++;
					cnt--;
				}
			}
		}
		else{//为1块
			r++;
			cnt++;
			ans=max(ans,cnt);
		}
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：CYZZ (赞：2)

# [Handstand](https://www.luogu.com.cn/problem/AT_abc124_d)
发现校内练习题也~~水~~一发题解。
# 思路分析
对于一段连续的 0 或 1，我们总是一次把它取完。所以原来的 01 串就可以压缩一下，相邻 $n$ 个 1 表示为 $n$，相邻 $n$ 个 0 表示为 $-n$。

如何遍历所有含 $k$ 段 0 的序列呢？我们可以用类似滑动窗口的思路。每次入队一个元素，若是正数（1 序列）就直接入队。若是负数（0 序列）就判断：如果已有 $k$ 个 0 序列就将最后一个 0 序列和前面的多余 1 序列弹出，再把新的 0 序列加入；如果还没满就直接加入。两种情况都要更新答案。代码挺好理解的。
# 代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,k,a[100005],last=-1,x,cnt,cnt0,ans,sum;
queue<int>q;
int main()
{
	scanf("%d%d",&n,&k);
	getchar();
	for(int i=1;i<=n;i++)
	{
		x=getchar()-'0';
		if(x==last) a[cnt]+=x?1:-1;
		else a[++cnt]+=x?1:-1,last=x;
	}
	n=cnt;//新的长度 
	for(int i=1;i<=n;i++)
	{
		if(a[i]>0)//1序列 
		{
			q.push(a[i]);
			sum+=a[i];
		}
		else
		{
			if(cnt0<k)//还没满 
			{
				q.push(a[i]);
				cnt0++;
				sum+=-a[i];
			}
			else//满了k个 
			{
				while(q.front()>0)
					sum-=q.front(),q.pop();//前面多余的1序列也要弹出 
				sum-=-q.front();
				q.pop();//队头出队 
				q.push(a[i]);
				sum+=-a[i];
			}
		}
		ans=max(ans,sum);//更新答案 
	}
	printf("%d",ans);
	return 0;
}
```
希望本篇题解可以帮到大家！！！

---

## 作者：dd_d (赞：2)

## Sol  
首先，想要连续的 $1$ 长度最大，那么一定是将全 $0$ 串翻转。  
并且，翻转的，一定是相邻的全 $0$ 串，否则可能对答案无贡献。  
我们考虑用类似前缀和的方式来计算答案。  
用两个数组，分别存储，每一个连续的全 $0$ 串和全 $1$ 串的末尾字符的位置。  
然后就可以以类似前缀和的方式来计算答案了。  
注意特判全 $0$ 串数量小于等于 $k$ 的情况。  
## Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
using namespace std;
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
string st;
int n,k,ans,a[100001],b[100001],c[100001],k1,k2;
signed main()
{
	n=read(); k=read();
	cin>>st;
	st=' '+st;
	for (int i=1;i<=n;i++)
		a[i]=(int)(st[i]-'0');
	if (a[1]==0) k2++;
	for (int i=1;i<=n;i++)
	{
		if (a[i]==0&&a[i+1]==1) b[++k1]=i;
		if (a[i]==1&&a[i+1]==0) c[++k2]=i;
	}
	if (a[n]==0) b[++k1]=n,c[++k2]=n;
	if (k1<=k)
	{
		writeln(n);
		return 0;
	}
	for (int i=1;i<=k1-k+1;i++)
		ans=max(ans,c[i+k]-b[i-1]);
	writeln(ans);
}



```


---

## 作者：chinazhanghaoxun (赞：1)

## 分析

这道题又是一道选择子串修改的问题，很明显可以使用双指针来做，具体操作也跟模板非常相似，基本不用改动。

首先，我们循环遍历这个字符串，使用一个变量 $res$ 记录每一次连续子串的长度。

如果当前字符为 `0` 而且还有修改的机会，那一定就要进行修改，正确性也是显然的，毕竟我们已经记录了 $res$。如果没有机会了，那我们就取消上一次修改，仍然修改这一位。

如果当前字符为 `1` 那就更简单了，直接把这一位加入当前的最长子串中，然后记录 $res$。
## 代码

这道题就是个双指针的模板题，代码中的注释也很详细，相信大家都是看得懂的。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,chance,l,r;
char s;
int a[100010];
int main(){
	cin>>n>>chance;
	for(int i=1;i<=n;i++){
		cin>>s;
		a[i]=s-'0';
	}
	int cnt=0,ans=0;
	while(l<=r && r<n){//双指针循环的基本条件 
		if(a[r+1]==0){//这一个字符是0 
			if(chance>0){//还有机会 
				chance--;//一定要改 
				while(a[r+1]==0 && r<n){//接着改 
					r++;
					cnt++;
				}
				while(a[r+1]!=0 && r<n){//如果是1就不用改 
					r++;
					cnt++;
				}
				ans=max(ans,cnt);//更新答案 
			}else{//没有机会了 
				chance++;
				while(a[l+1]!=0 && l<=r){//取消前面的操作来满足这次操作 
					l++;
					cnt--;
				}
				while(a[l+1]==0 && l<=r){//之前的1删去
					l++;
					cnt--;
				}
			}
		}else{//是1就直接加 
			r++;
			cnt++;
			ans=max(ans,cnt);
		}
	}
	cout<<ans;//输出 
	return 0;
}
```

---

## 作者：__little__Cabbage__ (赞：1)

## Solution

因为要使得连续的 $1$ 最长，所以考虑选择尽量多的 $0$ 串，这里的正确性是显然的，因为如果将 $1$ 变成了 $0$，那么就还需要一次操作把它变回 $1$（不然第一次操作就失去意义了）。

所以我们可以把连续的长度为 $k$ 的 $1$ 串记为 $+k$，$0$ 串记为 $-k$，然后用一个类似滑动窗口的方法，每次遇到 $+k$ 的时候直接将 $k$ 加入答案，遇到 $-k$ 的时候先判断是否有已经在答案之外的 $0$ 串和 $1$ 串，然后再将 $k$ 加入答案。记录最大值即可。

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
//#define int long long
#define pb emplace_back
using namespace std;
const int MAXN=1e5+5;
int n,k;
string s;
vector <int> v;
signed main()
{
    ios::sync_with_stdio(0);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>k>>s;
    s="$"+s;
    char _now=s[1];int len=1;
    for(int i=2;i<=n;++i)
    {
        if(s[i]==_now) ++len;
        else
        {
            v.pb(_now=='0' ? -len : len);
            _now=s[i],len=1;
        }
    }
    v.pb(_now=='0' ? -len : len);
    int ans=0,now=0,cnt=0;
    for(int i=0;i<v.size();++i)
    {
        if(v[i]<0)
        {
        	if(cnt==k) now=now+v[i-2*k]-v[i-2*k-1];
        	else ++cnt;
        }
        now+=abs(v[i]);
        ans=max(ans,now);
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：Lame_Joke (赞：1)

- ### 大体思路
	不难想到，尽量进行多次操作一定是最优的。还可以想到，每次操作都对于一个连续的相同的区间进行，也一定是最优解之一，所以我们为了方便，先将相同的串压缩，记录它们的长度和它们的数字。然后我们再考虑有多少个区间供进行操作。若当前枚举的区间为 $0$，则有 $2\times k$ 段可进行操作，因为每一段的数字是互不相同的；若为 $1$，则有 $2\times k+1$ 段，因为当前段可以不进行操作。知道这些以后，二重循环暴力即可。

- ### 具体实现

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,t[200005];
bool b[200005];
char s[200005];
int main()
{
	scanf("%d%d",&n,&k);
	scanf("%s",s+1);
	int cnt=0,n1=0;
	for(int i=1;i<=n;i++)
	{
		n1++;
		if(s[i]!=s[i+1])
		{
			t[++cnt]=n1;
			n1=0;
			b[cnt]=s[i]-'0';
		}
	}
	int cntt=max(1,cnt-2*k+1),jj,ans1=0,ans=-1e9;
	for(int i=1;i<=cntt;i++)
	{
		jj=i+2*k;
		ans1=0;
		if(b[i]==0)
		{
			for(int j=i;j<jj;j++) ans1+=t[j];
			ans=max(ans,ans1);
		}
		else
		{
			for(int j=i;j<=jj;j++) ans1+=t[j];
			ans=max(ans,ans1);
		}
	}
	printf("%d",ans);
}

---

## 作者：hxhhxh (赞：1)

### 大意

给定一个长度为 $ n $ 的二进制序列 $ a $ ，每次可以选择连续的一段并取反，求在最多 $ K $ 次操作后连续的 $ 1 $ 的个数的最大值。

### 思路

把连续的 $ 0 $ 称为零块，将连续的 $ 1 $ 成为一块。可以发现，最优决策中，一定有一种方法，每一次操作都一定是**对于一个零块进行的**。

依次计算出一块右端点是从 $ 1 $ 到 $ n $ 的最大长度，可以从上一个答案中推导出来当前答案。

先记录每一个块的长度，从第一个零块开始，“0”、“1”相间，保证最后一个块是一块（如果不是，补一个长度为 $ 0 $ 的一块）。

用两个队列分别储存存入的零块和一块，一开始插入第 $ 1 $ 个零块，之后每一次插入一个一块和一个零块，表示对当前零块进行操作，并将当前答案增加这**两个**块的长度。如果零块的数量大于 $ K $ ，弹出**两个队列**的队首。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,k,t,ans,nans;
queue<int>st,q1,q2;
char ch[101010];
signed main(){
    scanf("%lld %lld %s",&n,&k,ch);
    ch[n]='0';
    for(int i=0;i<n||ch[n]=='1';){
        t=0;
        while(i<n&&ch[i]==ch[n]){
            t++;
            i++;
        }
        ch[n]=(ch[n]=='0')?'1':'0';
        st.push(t);
    }
    q1.push(0);
    while(!st.empty()){
        int x=st.front();
        st.pop();
        int y=st.front();
        st.pop();
        nans+=x+y;
        q1.push(y);
        q2.push(x);
        if(q2.size()>k){
            nans-=q1.front()+q2.front();
            q1.pop();
            q2.pop();
        }
        ans=max(nans,ans);
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Nightingale_OI (赞：1)

### 大意

给你一个长度为 $ n $ 的二进制串，每次操作可以让一段取反。

问你至多 $ k $ 次操作后全是 $ 1 $ 的连续段的最大长度。

### 思路

可以发现如果一个位置取反了，将它相连相同位置也取反是不劣的，并且取反的一定是 $ 0 $ 。

那么可以把每个同种类连续段缩在一起，如 $ 11001110 $ 变成 $ (1:2)  (0:2) (1:3) (0:1) $ 。

只可能翻转 $ k $ 次，可以看成只可能让相邻的 $ k + 1 $ 个为 $ 1 $ 的段合并，合并过程中贡献记得加上中间夹着的 $ 0 $ 的个数。

用队列扫一遍即可，若元素个数多了则让队头出队并减去贡献即可。

时间复杂度 $ O(n) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
queue<int>a,b,c;
char st[101010];
int main(){
    cin>>n>>m;
    scanf("%s",st);
    l=0;
    st[n]='0';
    while(l<n || st[n]=='1'){
        s=0;
        while(l<n && st[l]==st[n]){
            ++s,++l;
        }
        st[n]='a'-st[n];
        a.push(s);
    }
    s=l=0;
    b.push(0);
    while(a.size()){
        s+=a.front();
        c.push(a.front());a.pop();
        s+=a.front();
        b.push(a.front());a.pop();
        if(b.size()>m+1){
            s-=b.front()+c.front();
            b.pop();c.pop();
        }
        l=max(s,l);
    }
    printf("%d\n",l);
    return 0;
}
```

---

## 作者：run_away (赞：1)

## 题意

给一个长度为 $n$ 的 01 串 $s$，可以至多进行 $k$ 次操作，每次操作可以把任意子串取反，求操作后最长的连续 1 串长度。

## 分析

$n$ 的范围“友好” 地告诉我们最大 $O(n\log n)$。

最开始想的是把每一块分出来跑 dp，然后发现写不出来 $O(n)$ 的式子。（去世）

想了一会后注意到题目中 `任意一个子串`，突然想到双指针。

设 $l,r$ 分别表示左端点和右端点，$f_i$ 表示第 $i$ 位前全 0 的块数。所以使 $[l,r]$ 区间内全为 1 所需要的操作次数为 $f_r-f_{l-1}$。若 $s_l$ 是两块的交界，那么答案还要加一。

总时间复杂度 $O(n)$。

## Code

```cpp
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
inline ll read(){ll x=0,f=1;char c=getchar();while(c<48||c>57){if(c==45)f=0;c=getchar();}while(c>47&&c<58)x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?x:-x;}
const ll maxn=1e5+5;
ll n,k,f[maxn],ans;
char s[maxn];
signed main(){
    n=read(),k=read();
    s[0]='1';
    for(ll i=1;i<=n;++i)cin>>s[i];
    for(ll i=1;i<=n;++i)f[i]=f[i-1]+(s[i-1]=='1'&&s[i]=='0');
    ll l=1,r=1;
    while(r<=n){
        if(l==r||f[r]-f[l-1]+(s[l-1]=='0'&&s[l]=='0')<=k){
            ++r,ans=max(ans,r-l);
        }
        else ++l;
    }
    printf("%lld",ans);
}
```

---

## 作者：OIerYang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc124_d)

此题明显是双指针。

我们可以把 $01$ 串给分割，就像这样：
![](https://cdn.luogu.com.cn/upload/image_hosting/tjd51omx.png)

把他分割成元素相同的子序列。

用两个数组，$a_i$ 表示第 $i$ 个子序列的元素个数，$vis_i$ 表示第 $i$ 个子序列的元素是什么。

此时我们应该用双指针求最大包含 $m$ 个的区间的最大长度是多少。

CODE：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[100001],cnt;
bool vis[100001];
signed main(){
	int n,m;cin>>n>>m;
	string s;cin>>s;
	s=' '+s;
	int now=1;
	while(now<=n){
		int ans=1;
		while(s[now]==s[now+1])now++,ans++;
		now++;
		a[++cnt]=ans;
		if(s[now-1]=='0')vis[cnt]=1;
	}//O(n)分割
	int res=0,k=0;//k用于记录区间内0块的个数
	int ans=0;
	for(int l=1,r=1;r<=cnt;r++){
		res+=a[r];
		if(vis[r])k++;
		while(k>m&&l<=r)res-=a[l++],k-=vis[l-1];//双指针模版，记得要把0块剪掉
		ans=max(ans,res);//求最大值
	}cout<<ans;
	return 0;
}
```

---

## 作者：Dream_Stars (赞：0)

## 题目说明：
你有 $k$ 次操作的机会，每次可以选取字符串中的一部分，将其翻转，如：

$\texttt{1100110}$ 选择其中的 $\texttt{1100}$，反转，成为 $\texttt{0011}$。

但是，题目要求我们给出一种最优的策略，使最后字符串出现一个最长的**连续** $1$ 串，就是**最长连续子序列**。

但是，不能反转 $1$ 成为 $0$ 的，那样会断除整个子序列，所以，最优策略是不可以反转 $1$ 成为 $0$ 的，反证，最优的反转策略是一定不会将 $1$ 反转为 $0$ 的，所以，我们便可以用贪心的思想去解题。

## 算法解释：

知道了最优的策略不能把 $1$ 反转为 $0$，于是，我们便可以抽象一下整个序列，就比如：$\texttt{11001110000}$ 我们可以抽象为 $2$，$-2$，$3$，$-4$。

**解释**：

- $2$ 个连续的 $1$，我们抽象为 $+2$；

- $2$ 个连续的 $0$，我们抽象为 $-2$；

- $3$ 个连续的 $1$，我们抽象为 $+3$；

- $4$ 个连续的 $0$，我们抽象为 $-4$。

- 结论： $1$ 抽象为正数，$0$ 抽象为负数。

做好了这步预处理，题目就会简单很多。

接下来，我们用一个循环遍历整个数组，再找出数组中的 $0$ 串，也就是负数串，再用贪心的思想来解决题目即可。

**贪心方法：**
遍历整个数组，如果是 $0$ 串，则判断次数是否足够放入新的 $0$ 串，足够则直接放入，不足够则删除第一个 $0$ 串和 $1$ 串即可。每次循环再判断最大值，最后输出即可。

## 代码展示：

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long N = 100005 , MIN = LONG_LONG_MIN;
long long x,n,k,ans,cnt;
long long a[N],v[N];
long long mx = MIN,l = 1;
string p;
int main(){
	cin>>n>>k>>p;
	for(int i=0;i<n;i++) v[i+1] = p[i] - '0';
//将字符串转换为一个long long的整型数组，下标从1~n。
	//这里循环为什么可以从1开始呢，因为v[0]默认为0，如果v[1] = 1，那么a[1]的值就是1，反之，a[1]的值就是-1，所以不用从2开始。
	for(int i=1;i<=n;i++){
		if(v[i] != v[i-1]){
//如果后项不等于前项，说明后项与前项一定属于两个连续的子串。
			l++;//新开辟一个子串
	    if(v[i-1] == 0) a[l] = 1;//如果前面的是0，那么这项一定是1。
	    else a[l] = -1;//反之。
		}
		else//如果相等。
			if(v[i] == 1) a[l] = a[l] + 1;//是1串，等于前项加1。
			else a[l] = a[l] - 1;//是0串，等于前项减1。
	}
	l++;//这里一定要加1，不然会少一项。
	for(int i=1;i<=l;i++){
//如果这是0串，并且次数足够，那么就直接放入，并累加。
		else if(a[i] < 0 && x >= k) cnt = cnt + a[i-2*k] - a[i-2*k-1] - a[i] , x = x + 1;
//如果这个是0串，并且次数不够，那么就删除最先放置的0串和1串各一个，再加入新的串。
//a[i-2*k]是一个0串，0串存的是负数，那么+负数 = -负数的绝对值，所以我们可以直接写加号。
		else if(a[i] > 0) cnt = cnt + a[i];
//如果这个是1串，那么直接加入即可。
		mx = max(mx,cnt);
	}
//for(int i=1;i<=l;i++) cout<<a[i]<<" ";cout<<endl;
	cout<<mx;
  return 0;//return 养成好习惯。
}
```

---

## 作者：HNOIRPplusplus (赞：0)

观察容易发现，如果把 $1$ 反转成 $0$ 没有任何有益作用。而把连续的一串 $0$ 分成两部分反转也只是浪费了一次机会。而且，如果反转的串最后无法拼接到一起，也是浪费机会。

因此认为，$k$ 次反转进行操作的部分一定是 $k$ 个相邻的连续最大 $0$ 串。

我们将每一个连续最大 $0$ 串和最大 $1$ 串的长度抽象出来。比如串 `1011110000010000`，我们抽象出 $\{1,1,4,5,1,4\}$。假设我们 $k=2$，那么我们就可以反转 $2$ 个连续的最大 $0$ 串，然后再算上夹着两个最大 $0$ 串的三个最大 $1$ 串。  
为了方便计算，我们假设序列最后面有零个 $1$，扩展成 $\{1,1,4,5,1,4,0\}$。（当第一个是 $0$ 个时候也可以这么扩展）于是，我们可以计算从每个奇数位置开始的长为 $(2k+1)$ 的段中，最长的一段有多少。  
上述例子中一共有两段：$\{1,1,4,5,1\}$ 和 $\{4,5,1,4,0\}$，长度和分别为 $12$ 和 $14$。显然答案是 $14$。

---

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
  int n, k;
  string s;
  cin >> n >> k >> s;
  vector<int> len;
  if(s[0] == '0') {
    len.push_back(0);
  }
  for(int i = 0, j = 0; i < n; i = j) {
    for(j = i; j < n && s[i] == s[j]; j++);
    len.push_back(j - i);
  }
  if(s[n - 1] == '0') {
    len.push_back(0);
  }
  int ans = 0, sum = 0;
  for(int i = 0; i < len.size() && i < 2 * k + 1; i++) {
    sum += len[i];
    ans += len[i];
  }
  for(int i = 2 * k + 2; i < len.size(); i += 2) {
    sum += len[i] + len[i - 1] - len[i - 2 * k - 1] - len[i - 2 * k - 2];
    ans = max(ans, sum);
  }
  cout << ans;
}
```

---

## 作者：YFF1 (赞：0)

## 思路
注意到这道题每次可以更改很多个 $0$，所以一长段 $0$ 只需要更改一次即可，所以使用前缀和与双指针，每次计算更改这一段 $0$ 对整个序列的影响以及所需代价。
## 代码
```
#include<bits/stdc++.h>
using namespace std;
int n,k,a[100005],t=0,cnt=0,cnt2=0,sum[100005],tot[100005],ans=0;
char c[100005];
int main () {
	cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>c[i];
	for(int i=1;i<=n;i++){
		if(c[i]=='1'){
			if(cnt2!=0){
				t++;
				a[t]=-cnt2;
				cnt2=0;
			}
			cnt++;
		}
		else {
			if(cnt!=0){
				t++;
				a[t]=cnt;
				cnt=0;
			}
			cnt2++;
		}
	}
	if(cnt2!=0){
		t++;
		a[t]=-cnt2;
		cnt2=0;
	}
	else if(cnt!=0){
		t++;
		a[t]=cnt;
		cnt=0;
	}
	for(int i=1;i<=t;i++){
		sum[i]=sum[i-1];
		if(a[i]<0)sum[i]++;
	}
	for(int i=1;i<=t;i++){
		tot[i]=tot[i-1];
		tot[i]+=abs(a[i]);	
	}
	int head=1,tail=1;
	while(head<=tail&&tail<=t){
		if(sum[tail]-sum[head-1]<=k){
			ans=max(ans,tot[tail]-tot[head-1]);
			tail++;
		}
		else head++; 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：lostxxx (赞：0)

[题目传送门](https://atcoder.jp/contests/abc124/tasks/abc124_d)

# 题目大意

每次节选一段连续的 $0$ 使其转换为 $1$ 。共进行 $k$ 次操作，求最后操作完后最多有多少个连续的 $1$ 。

# 题目分析

首先，如果想要连续的 $1$ 尽可能多的话，那么操作满 $k$ 次肯定是最优选择，所以我们可以把连续相同的数字看做一段，统计出每一段相同数字的个数。

```cpp
for (int i=0;i<s.size();i++){
   cnt++;
   if (s[i]!=s[i+1]){
     a[kk].key=cnt;
     a[kk].c=s[i]-'0'+1;//分成1或者0一组，便于分类讨论
     kk++;
     cnt=0;
   }
}
```

随后就可以遍历每一段了。每一种颜色的情况不一，要分类讨论。如果是以 $0$ 为开头的话，那么总共只有 $2 \times k-1$ 段。如果是以 $1$ 为开头的话，那么总共就有 $2 \times k+1$ 段。然后再将每种情况所求的的每一段的和加起来求最大值即可。

$code$

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct node{
    ll key,c;
}a[200100];
string s;
ll cnt=0,kk=1;
ll n,k,ans=0,maxn=-1;
int main(){
    cin>>n>>k;
    cin>>s;
    for (int i=0;i<s.size();i++){
        cnt++;
        if (s[i]!=s[i+1]){
            a[kk].key=cnt;
            a[kk].c=s[i]-'0'+1;
            kk++;
            cnt=0;
        }
    }
    for (int i=1;i<=max(kk-2*k+1,1ll);i++){
        if (a[i].c==2){
            ans=0;
            for (int j=i;j<=i+2*k;j++){
                ans+=a[j].key;
            }
            maxn=max(maxn,ans);
        }else{
            ans=0;
            for (int j=i;j<=i+2*k-1;j++)
                ans+=a[j].key;
            maxn=max(maxn,ans);
        }
    }
    cout<<maxn;
}
```


---

## 作者：OranJun (赞：0)

显然具有单调性，所以二分答案即可，转换为判定性问题暴力枚举一下就可以了

还需发现一个关键性质：你全部反转再把区间中的1翻转回来与把这个区间中的0段翻转是等价的，所以就之间翻转0段就可以了。

具体实现中可以把每段0缩成一个比较好写，注意判断边界问题

时间复杂度$O(n \log n)$


```cpp
/*Code by Codercjh*/
#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a);i<=(b);++i)
#define rf(i,a,b) for(int i=(a);i>=(b);--i)
#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)
using namespace std;
typedef long long ll;
template<typename T>
inline void read(T &x){
	char c=getchar();T fh=0;bool f=false;
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))fh=(fh<<1)+(fh<<3)+(c^48),c=getchar();
	x=f?-fh:fh;
	return;
}
int n,k,cnt;
const int N=1e5+5;
char a[N];
struct node{int l,r;}pos[N];
bool check(int cd){
	fr(i,1,cnt){
		int r=min(i+k-1,cnt),l=i;
		int cd1=r+1>cnt?n:pos[r+1].l-1,cd2=l==1?1:pos[l-1].r+1;//判断如果超出边界就可以直接赋值端点
		if(cd1-cd2+1>=cd)return 1;//存在就可以返回
	}
	return 0;
}
int main(){
	read(n),read(k);
	cin>>a+1; 
	int l=1;
	while(a[l]=='1')++l;
	fr(i,l,n){
		if(a[i]=='1'&&a[i-1]=='0')pos[++cnt]=(node){l,i-1};
		if(a[i]=='0'&&a[i-1]=='1')l=i;
	}
	if(a[n]=='0')pos[++cnt]=(node){l,n};//注意最后一段也要
	if(cnt==0)return printf("%d\n",n),0;//注意特判
	l=1;
	int r=n,ans=0;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid))l=mid+1,ans=mid;//二分答案
		else r=mid-1;
	}
	cout<<ans;
	return 0;
}


---

