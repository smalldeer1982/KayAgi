# Tanya and Password

## 题目描述

While dad was at work, a little girl Tanya decided to play with dad's password to his secret database. Dad's password is a string consisting of $ n+2 $ characters. She has written all the possible $ n $ three-letter continuous substrings of the password on pieces of paper, one for each piece of paper, and threw the password out. Each three-letter substring was written the number of times it occurred in the password. Thus, Tanya ended up with $ n $ pieces of paper.

Then Tanya realized that dad will be upset to learn about her game and decided to restore the password or at least any string corresponding to the final set of three-letter strings. You have to help her in this difficult task. We know that dad's password consisted of lowercase and uppercase letters of the Latin alphabet and digits. Uppercase and lowercase letters of the Latin alphabet are considered distinct.

## 样例 #1

### 输入

```
5
aca
aba
aba
cab
bac
```

### 输出

```
YES
abacaba
```

## 样例 #2

### 输入

```
4
abc
bCb
cb1
b13
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
7
aaa
aaa
aaa
aaa
aaa
aaa
aaa
```

### 输出

```
YES
aaaaaaaaa
```

# 题解

## 作者：Yuno (赞：7)

### 题意：

给 $n$ 个长度为 $3$ 的字符串，问能否组成总长度为 $n+2$ 的字符串，如 $abcde=abc+bcd+cde$。

输出方案。$1\leq n\leq 2\times 10^5$

### 题解：

把每个字符串前两个和后两个通过字符串哈希看作一个点。

然后跑一遍欧拉路径即可。

至于欧拉路径，先判是否存在，即每个点出度和入度的差都为 $0$ ，或者有且只有两个点入度和出度的差为 $\pm 1$

对于第一种情况，任选一个点作为起点，第二种，选择入度比出度少一的点作为起点。

然后 $dfs$ 扫与当前点直接相连的边，删除这条边，并遍历下一个点。

遍历完了把当前点加入答案，注意最后倒序输出。

用链式前向星跑欧拉路径会 $T$，所以使用了 $vector$

复杂度：$O(n)$

$Code:$

```cpp
#include <bits/stdc++.h>
using std::cin;
using std::cout;

const int N = 300007;
int n, vis[N], in[N], out[N];
std::string ans;
std::vector <int> v[N];

void dfs(int u) {
//	std::cerr << u << '\n';
	while (!v[u].empty()) {
		int len = v[u].size();
		int _ = v[u][len - 1];
		v[u].pop_back();
		dfs(_);
	}
	ans += (char) (u % 256);
}

int main() {
	std::ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	char s[3];
	int S;
	for (int i = 1; i <= n; ++ i) {
		cin >> s;
		int x = s[0] * 256 + s[1], y = s[1] * 256 + s[2];
		v[x].push_back(y);
		++ out[x];
		++ in[y];
		S = x;
	}
	int _ = 0, __ = 0;
	for (int i = 0; i <= 200007; ++ i) {
		int delta = in[i] - out[i];
		if (delta == -1) ++_, S = i;
		else if (delta == 1) ++__;
		else if (delta != 0) {
			cout << "NO\n";
			return 0;
		}
	}
	if (_ > 1 || __ > 1 || _ + __ == 1) {
		cout << "NO\n";
		return 0;
	}
	dfs(S);
	ans += char(S / 256);
	if (ans.size() < n + 2) {
		cout << "NO\n";
		return 0;
	}
	cout << "YES\n";
	std::reverse(ans.begin(), ans.end());
	cout << ans << '\n';
	return 0;
} 
```

$date:2020.8.26$

---

## 作者：intel_core (赞：1)

如果有一个合法的串 $s_1s_2\cdots s_{n+2}$ ，那么 $s_1s_2s_3,s_2s_3s_4,\cdots,s_ns_{n+1}s_{n+2}$ 应该能和输入的串一一对应。

考虑两个纸条上的字符串，如果整个串拼起来之后这两个纸条上的字符串是相邻的，那么这两个纸条有长度为 $2$ 公共部分。

借住这个发现，我们可以把所有可能的长度为 $2$ 的字符串都找出来，建出它们对应的点。

把输入的字符串 $s_1s_2s_3$ 看成是 $s_1s_2$ 和 $s_2s_3$ 之间的有向边，那么一个合法的串相当于图上的一条欧拉路径。

回顾一下存在欧拉路径的充要条件：

> 结论：若一张联通有向图中至多存在一个 入度比出度多 $1$ 和 出度比入度多 $1$ 的点，那么这张有向图存在欧拉路径。

详细证明参见 [【模板】欧拉路径](https://www.luogu.com.cn/problem/P7771) 。

找出一条欧拉路径也很简单：

* 如果图中所有顶点的入度与出度相同，那么随意挑一个点出发。

* 如果图中有出度比入度大 $1$ 的顶点，那么从这个点出发。

* 遍历到一个点的时候，先走一遍所有的自环，然后随便找一个邻接的节点，接着走就行。走完把边删掉。

只需要用并查集判联通然后随便找一条欧拉路径就可以了。

综上，复杂度 $O(n)$。

---

## 作者：Chillturtle (赞：0)

# 前置芝士

~~欧拉路径。~~

定义：

- 欧拉回路：通过图中每条边恰好一次的回路
- 欧拉通路：通过图中每条边恰好一次的通路
- 欧拉图：具有欧拉回路的图
- 半欧拉图：具有欧拉通路但不具有欧拉回路的图

摘自：[oi-wiki](https://oi-wiki.org/graph/euler/)。

首先，对于一个图，它要存在欧拉路径的必要条件很简单。就是奇点的个数要为 $0$ 或者 $2$。其他情况都是无解的。这两种情况对应的图的形态长这样捏：

![](https://cdn.luogu.com.cn/upload/image_hosting/w0cejboq.png)

当然这也不是唯一解。其中第一个图中没有奇点，而第二个图中奇点为 $1$ 和 $2$。

这里给出求解欧拉路径的伪代码：

```cpp
void dfs(int u){
    遍历u的所有出边
        如果该边还存在
        删掉这条边
        dfs(该边去往的点)
    u入栈
}
```

这里给出一点大部分题解都没有解释到的地方。为什么不能遍历到一个点就将该点入栈，非要循环结束后才可以？这里举出一个例子：如果有一个无向图长得像一个 $8$ 字，就像下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/9w13bho8.png)

当我们走到 $5$ 的时候会发生一个事情。就是说这个时候我们既可以选择往 $1$ 走也可以往 $4$ 走。我们希望的是向 $4$ 走。如果我们最后再入栈那么当它 dfs 到 $1$ 的时候就只会推掉 $5$ 和 $1$ 之间的部分，再从 $5$ 开始继续搜索。相当于我们最开始的 $[1,7,6,5]$ 加上 $[5,4,3,5]$ 以及 $[5,1]$ 就是我们最后的答案。这里需要倒序输出，这里借鉴了 Marsrayd 大佬的 [博客](https://www.luogu.com.cn/article/lvmezioa)。这里是这样说的：

> 感性理解倒序输出的原因：如果是欧拉回路，那么遍历到哪，输出到哪也是对的，因为不管怎么走都会绕某个环走回起点，所以不到最后不会出栈，然而欧拉路径会出现边都被走过了，走不回起点，最后会停留在终点，遇到这种情况这种路径会最先出栈，于是只要把这个路径先走了，前面就和欧拉回路一样随便走就行，不会出栈，于是倒序输出就是对的

膜拜大佬。这个说得非常清楚啊。

# 思路

此题很板啊。我们直接把这个字符串的前面的两个字符和后面的两个字符各看作一个点，连一条单向边。因为这题要求相同的字符串之间连线。那么我们把它转成 int 了之后就自然而然连上边了。

我们需要再记录一个每个点的出度和入度。来判断改图是否存在欧拉路径。

其实就是一个板题，这边给出可爱的代码：

# AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace CF508D{
	const int N=3e5+10;
	const int INF=2e5;
	vector<int> edge[N];
	vector<int> point;
	int n,outde[N],inde[N],Start;
	string ans;
	void dfs(int u){
		while(!edge[u].empty()){
			int to=edge[u][edge[u].size()-1];
			edge[u].pop_back();
			dfs(to);
		}
		ans+=(char)(u%256);
	}
	int main(){
		cin>>n;
		memset(outde,0,sizeof(outde));
		memset(inde,0,sizeof(inde));
		string s;
		for(int i=1;i<=n;i++){
			cin>>s;
			int u=s[0]*256+s[1],v=s[1]*256+s[2];
			edge[u].push_back(v);
			outde[u]++;
			inde[v]++;
			Start=u;
		}
		int k=3e5;
		for(int i=0;i<=k;i++){
			if(edge[i].size()!=0){
				point.push_back(i);
			}
		}
		if(n==1){
			cout<<"YES"<<endl;
			cout<<s<<endl;
			return 0;
		}
		int flag=0,cnt=0;
		for(int i=0;i<=INF;i++){
			if(outde[i]!=inde[i]){
				flag=1;
			}
			if(abs(outde[i]-inde[i])==1){
				cnt++;
			}
			if(abs(outde[i]-inde[i])>1&&outde[i]!=inde[i]){
				cout<<"NO"<<endl;
				return 0;
			}
			if(outde[i]-inde[i]==1){
				Start=i;
			}
		}
		if(flag==1&&cnt!=2){
			cout<<"NO"<<endl;
			return 0;
		}
		dfs(Start);
		ans+=Start/256;
		if(ans.size()<n+2){
			cout<<"NO"<<endl;
			return 0;
		}
		cout<<"YES"<<endl;
		reverse(ans.begin(),ans.end());
		cout<<ans<<endl;
		return 0;
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	CF508D::main();
	return 0;
}
```

---

## 作者：C_Pos_Princess (赞：0)

### Tanya and Password
#### 题意


给出长度为 $n+2$ 的字符串 $s$ 的全部 $n$ 个「长度为 $3$ 的子串」，求原串。若有解则输出 `YES` 与任意一个合法解，反之输出 `NO`。

字符集为大小写字母与数字，$1\le n\le2\times10^5$。


#### 题解

注意到给出的子串长度只有 3，那么事情变得简单。

这里，我们用一个哈希值，将一个子串的前两位看作一个点，后两位看作一个点，连一条路径，那么最终的字符串肯定是走过所有路径从头连到尾的，所以跑一遍欧拉路径，然后判断得到的字符串长度是否合法即可。

#### 代码
```cpp
const int N = 3e5+10;
const int INF = 0x3f3f3f3f;
using namespace std;
int n;
char s[10];

vector<int> e[N];
int in[N],out[N];
int st;
string ans;
void dfs(int u){
	
	while(!e[u].empty()){
		int len = e[u].size();
		int v = e[u][len-1];
		e[u].pop_back();
		dfs(v);
		
	}
	ans+=(char)(u%256);
}


int main(){
	read(n);
	for(int i = 1;i<=n;i++){
		scanf("%s",s);
		int x = (int)s[0]*256+s[1];
		int y = (int)s[1]*256+s[2];
		e[x].push_back(y);
		in[y]++;
		out[x]++;
		st = x;
	}
	
	int num1 = 0,num2 = 0;
	for(int i = 0;i<=200010;i++){
		int cha = in[i]-out[i];
		if(cha == -1) num1++,st = i;
		else if(cha == 1) num2++;
		else if(cha!=0){
			cout<<"NO";
			return 0;
		}
	}
	if(num1>1 || num2>1 || num1+num2 == 1) {
		cout<<"NO";
		return 0;
	}	
	
	dfs(st);
	
	ans+=(char)(st/256);
	
	if(ans.size()!=n+2) {
		cout<<"NO";
		return 0;
	} 	
	cout<<"YES"<<endl; 
	reverse(ans.begin(),ans.end());
	cout<<ans;


	return 0;
}

```

---

## 作者：qiliu (赞：0)

### 前置知识

[欧拉路径](https://www.luogu.com.cn/problem/P7771)，~~哈希~~。

## 思路

为了方便，下文中的子串都指长度为三的子串，合法的子串排序指以这个顺序能拼接所有子串从而得到一个合法的解。

容易发现两个子串能“拼”到一起当且仅当前一个子串的后两位等于后一个子串的前两位，所以我们可以把一个子串看成一条连接他前两位和后两位的一条边。

下一步考虑如何构造原来的串。不难发现从一个子串的后两位出发，遍历每一条边得到的路径即为一个合法的子串排序，即欧拉回路。

## code


```cpp
#include<bits/stdc++.h>
#define int long long
// #define DEBUG(x) cerr<<#x<<'='<<x<<endl
#define endl '\n'
using namespace std;
inline int rd()
{
    char t=getchar();
    int f=1,x=0;
    while(t<'0'||t>'9')
    {
        if(t=='-')f=-1;
            t=getchar();
    }
    while(t>='0'&&t<='9')
        x=x*10+t-'0',t=getchar();
    return x*f;
}
inline void wt(int t)
{
    if(t<0)
        putchar('-'),t=-t;
    if(t>9)
        wt(t/10);
    putchar(t%10+'0');
    return;
}
const int N=2e5+100;
string a[N];//所有的子串
int n;
vector<pair<int,int> >e[N];//边
int in[N],out[N];//一个点的出度和入度，欧拉路径要用到
stack<int>q;//统计答案
int beginn[N];//每条边只出现一次，所以对于出现过的边直接跳过，具体实现就在下面
void dfs(int now){//求欧拉路径
    for(int &i=beginn[now];i<e[now].size();){
        int id=e[now][i].first;
        dfs(e[now][i++].second);
        q.push(id);
    }
}
bool vis[1000000],vis1[1000000];
signed main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    // cout<<signed('a')<<endl;
    n=rd();
    for(int i=1;i<=n;i++){
        cin>>a[i];
        int num=signed(a[i][0])*1000+signed(a[i][1]);
        int num1=signed(a[i][1])*1000+signed(a[i][2]);//把string转化为int，写map<string,int>也可以，但是那样会多个log
        e[num].push_back(make_pair(i,num1));
        in[num1]++,out[num]++;//欧拉路径基本操作
    }
    int start=0,endd=0;int num;
    for(int i=1;i<=n;i++){
        num=signed(a[i][0])*1000+signed(a[i][1]);
        // int num1=signed(a[i][1])*100+signed(a[i][2]);
        if(abs(in[num]-out[num])>1){cout<<"NO";return 0;}
        if(in[num]>out[num]&&!vis1[num]){
            vis1[num]=1;
            if(endd){cout<<"NO";return 0;}
            else endd=num;
        }
        if(in[num]<out[num]&&!vis[num]){
            vis[num]=1;
            // cout<<start<<' '<<i<<' '<<in[num]<<' '<<out[num]<<endl;
            if(start){cout<<"NO";return 0;}
            else start=num;
        }
    }//欧拉路径基本操作
    // cerr<<start;
    if(start==0)start=num;
    dfs(start);
    if(q.size()!=n){cout<<"NO";return 0;}
    cout<<"YES\n";
    while(!q.empty()){
        if(q.size()==1){
            cout<<a[q.top()];
            q.pop();
        }else{
            cout<<a[q.top()][0];
            q.pop();
        }
    }//注意我们的答案路径里是每一个子串，是形如aba bab aba这样的
    //所以我们对于前n-1个子串只输出第一位，最后一个子串再全部输出
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}
```

希望有帮到你。

---

## 作者：Frictional (赞：0)

## 题意
题目翻译很清晰，不说了。
## 解法
显然，将两个字符串拼在一起当且仅当前一个字符串的后两位与下一个字符串的前两位相同。

我们设目前拼起来的原串是 $T$，我们来考虑后两个字符，可以注意到拼接上一个字符串 $S$ 后，原本 $T$ 的后两位字符的状态变成了拼接的字符串 $S$ 的后两位字符，即 $T$ 后两位字符的状态从 $S$ 的前两位字符变成了 $S$ 的后两位字符。

到这感觉就比较显然了，我们可以将每个字符串 $S$ 的前两位字符和后两位字符连边，跑欧拉路径即可。

## Code

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
#define db double
#define U unsigned
#define P pair<int,int>
#define int long long
#define pb push_back
#define MP make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define ROF(i,a,b) for(int i=a;i>=b;i--)
#define debug(x) cerr<<#x<<'='<<x<<endl
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define gc getchar()
#define pc putchar
using namespace std;
inline int rd(){
    int x=0,f=1;
    char ch=gc;
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1;ch=gc;}
    while(ch>='0' && ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=gc;
    return x*f;
}
inline void wr(int x){
    if(x<0) x=-x;
    if(x>9) wr(x/10);
    pc((x%10)^48);
}
const int N=2e5+5;
int n;
string s[N];
map<string,int>mp;
int cnt;
string tmp1,tmp2;
vector<P >ng[N*2];
int beginn[N*2];
stack<int>p;
int ind[N*2],outd[N*2];
void ol(int now,int id){
    for(int i=beginn[now];i<ng[now].size();){
        beginn[now]=i+1;
        // debug(ng[now][i].id);
        ol(ng[now][i].se,ng[now][i].fi);
        // p.push(ng[now][i].se);
        i=beginn[now];
    }
    p.push(id);
}
int star,endd;
bool flag;
int tmp;
signed main(){
    n=rd();
    FOR(i,1,n){
        cin>>s[i];
        tmp1=s[i][0];
        tmp1+=s[i][1];
        if(!mp[tmp1]) mp[tmp1]=++cnt;
        tmp2=s[i][1];
        tmp2+=s[i][2];
        if(!mp[tmp2]) mp[tmp2]=++cnt;
        ng[mp[tmp1]].pb(MP(i,mp[tmp2]));
        ind[mp[tmp2]]++;
        outd[mp[tmp1]]++;
        tmp++;
    }
    FOR(i,1,cnt){
        // for(auto x:ng[i]) cout<<x.fi<<' ';
        if(abs(ind[i]-outd[i])>=2){
            puts("NO");
            return 0;
        }
        if(ind[i]>outd[i]){
            if(endd!=0){
                puts("NO");
                return 0;
            }
            else endd=1;
        }
        if(outd[i]>ind[i]){
            if(star!=0){
                puts("NO");
                return 0;
            }
            else star=i;
        }
    }
    if(star==0) star=1;
    ol(star,-1);
    if(p.size()-1!=tmp){
        puts("NO");
        return 0;
    }
    puts("YES");
    while(!p.empty()){
        if(p.top()==-1){
            p.pop();
            continue;
        }
        if(!flag) cout<<s[p.top()];
        else cout<<s[p.top()][2];
        flag=1;
        p.pop();
    }
    return 0;
}
```

---

## 作者：xxseven (赞：0)

#### 题意：

乱序给定一个长为 $n+2$ 的字符串的所有长度为 $3$ 的子串，求原字符串。需要判无解。

#### 思路：
前置知识：[P7771 【模板】欧拉路径](https://www.luogu.com.cn/problem/P7771)

这种带限制的字符串拼接题目一般可以转化为图上的欧拉路问题。

在这道题中，我们发现如果两个子串 $A,B$ 要拼接，那么 $A$ 的后两个字符必须跟 $B$ 的前两个字符相等。  
我们记“当前拼接的下一个字符串的前缀必须是 `ab`”为状态 `ab`，那么考虑一个字符串 `abc`，拼接上该字符串后，我们的状态就由 `ab` 变为 `bc`。  
因此我们把一个状态设为点，题目给定的子串设为边，这个子串就是一条从它前缀到它后缀的有向边。拼接一个子串，就是沿着这条边前进改变了状态。

考虑有解的情况，每个字符串都要拼接上去，并且只能使用一次，这就是一个欧拉路板子。正常做即可。  
注意有可能图不连通的情况下，有一个连通块内存在欧拉路，可以记录下经过点的个数来判断是否连通。

对于将字符串转化为点的编号，可以使用字符串哈希或者直接 map 解决。

下面放代码：
```cpp
#include<bits/stdc++.h>
#define debug puts("NOIpRP++"); //调试用的 QAQ
using namespace std;
map<string,int> mp;
map<int,string> pm;
int n,cnt,in[80000],out[80000],now[80000];
vector<int> f[80000];
string S,x,y;
stack<int> s;
int siz;
void dfs(int x){//欧拉路板子
	for(int i=now[x];i<f[x].size();i=now[x]){
		now[x]++;
		dfs(f[x][i]);
	}
	s.push(x); siz++;//用siz记录路径长度，判连通性
}
int main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>S;
		x=S.substr(0,2); y=S.substr(1,2);//取出前缀后缀作为连边的节点
		if(!mp[x]) mp[x]=++cnt,pm[cnt]=x;
		if(!mp[y]) mp[y]=++cnt,pm[cnt]=y;
		f[mp[x]].push_back(mp[y]);
		out[mp[x]]++; in[mp[y]]++;
	}
	int pos=1,f1=0,f2=0;
	for(int i=1;i<=cnt;++i){
		if(in[i]==out[i]) continue;
		if(in[i]-out[i]==1) f1++;
		else if(out[i]-in[i]==1) f2++,pos=i;
		else {
			puts("NO"); return 0;
		}
	}
	if((f1==1&&f2==1)||(f1==0&&f2==0)) dfs(pos);
	else{
		puts("NO"); return 0;
	} 
	if(siz!=n+1){//如果siz不为n+1，说明求出的欧拉路没有遍历所有节点，图不连通，无解
		puts("NO"); return 0;
	} 
	string ans=pm[s.top()]; s.pop(); 
	while(!s.empty()){
		int t=s.top();
		ans+=pm[t][1];
		s.pop();
	}
	puts("YES"); cout<<ans;
	return 0;
}

```

希望这篇题解能帮到你！

---

## 作者：conprour (赞：0)

# 题解
考虑把每一个串的前两位和后两位分别看成一个点（字符串哈希），从前向后连边，问题转化成求所建图的欧拉路径。

对于有向图的欧拉路径，常规操作请移步[P7771 【模板】欧拉路径](https://www.luogu.com.cn/problem/P7771)。

对于本题而言，有一点易错的细节：
* 有自环，重边，所以点数我开到 $256\times 256$，但边数还是 $2\times 10^5$。
* 图可能不连通，所以加上一条判断，如果栈内元素是 $n+1$ 个才有解。

# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define FCC fclose(stdin),fclose(stdout)
const int INF = 0x3f3f3f3f,base=256,N = 257*257;
inline ll read()
{
	ll ret=0;char ch=' ',c=getchar();
	while(!(c>='0'&&c<='9')) ch=c,c=getchar();
	while(c>='0'&&c<='9') ret=(ret<<1)+(ret<<3)+c-'0',c=getchar();
	return ch=='-'?-ret:ret;
}
int n;
int head[N],ecnt=-1;
int ind[N],oud[N];
inline void init_edge(){memset(head,-1,sizeof(head)),ecnt=-1;}
struct edge
{
	int nxt,to;
}a[200005];
bool vis[N];
inline void add_edge(int x,int y)
{
	a[++ecnt]=(edge){head[x],y};
	head[x]=ecnt;
	ind[y]++,oud[x]++;
	vis[x]=1,vis[y]=1;
}

int S,T,stk[N],top;
char str[N][3];
void dfs(int u)
{
	for(int i=head[u];~i;i=head[u])
	{
		int v=a[i].to;
		head[u]=a[i].nxt;//链前的删边操作 
		dfs(v);
	}
	stk[++top]=u;
}
int main()
{
	init_edge();
	n=read();
	for(int i=1;i<=n;i++)	
	{
		char s[6];
		scanf("%s",s+1);
		int u=(s[1]-'0'+1)*base+s[2]-'0'+1;
		int v=(s[2]-'0'+1)*base+s[3]-'0'+1;
		add_edge(u,v);
		str[u][1]=s[1],str[u][2]=s[2];
		str[v][1]=s[2],str[v][2]=s[3];
		//cout<<str[u]<<'\n';
		//printf("%d->%d\n",u,v);
		S=u;
	}
	int cnt=0;
	for(int i=0;i<=256*256;i++)
	{
		if(!vis[i]) continue;
		if(oud[i]-ind[i]==1) S=i;
		if(oud[i]-ind[i]==-1) T=i;
		if(abs(oud[i]-ind[i])>1) return puts("NO"),0;
		cnt+=(oud[i]!=ind[i]);
	}
	if(cnt!=2&&cnt) return puts("NO"),0;
	
	dfs(S);
	//printf("S=%d,top=%d\n",S,top);
	if(top+1!=n+2) return puts("NO"),0;
	bool fir=0;
	puts("YES");
	while(top) 
	{
		if(!fir) printf("%c",str[stk[top]][1]),fir=1;
		printf("%c",str[stk[top]][2]),top--;
	}
	return 0;
}
```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2500}$
---
### 解题思路：

很容易发现一组答案合法也就是排列所有的字串，要求相邻两个字串中的前者的后两个字母和后者的前两个字母是相同的。

于是想到将每两个字符变成一个点，每一个字串的前两个字符和后两个字符之间连一条有向边。如果在转化后的图中找到一条欧拉路，就能说明原问题存在解，且具体解即为将路径上的所有点去掉中间的一个重复字母的简单拼接的结果。

需要注意，这个图可能存在重边，自环，但这两种较为特殊的情况并不会产生影响。

---
接下来是欧拉路的相关内容。

无向图的欧拉路是从任意一点出发，不重复地经过所有的边的一条路径。无向图存在欧拉路的条件为图中存在一个节点的出度比入度多一，另一个节点入度比出度多一，其余所有节点入度等于出度。或者是所有节点出度等于入度，这个条件满足时有更强的欧拉回路存在。

前一种条件满足时，直接选取出度比入度多
一的节点作为起点进行搜索。后一种则可以选取任意一个点开始搜索。

搜索欧拉路的时候有一个小优化，就是 $\text{vector}$ 存边然后记录下当期搜索到那一条边了，省去从头开始枚举边的过程。

最后需要注意一下是否存在多个连通块的情况，这种情况不满足条件。

---
无法理解为什么能够有 $2500$ 的难度。

---
### 代码：
```cpp
#include<cstdio>
#include<vector>
using namespace std;
const int MAXN=400005;
int NUM(char c1,char c2){
	return c1*256+c2;
}
int n,OUT[MAXN],IN[MAXN],vis[MAXN],c[MAXN],cnt,_cnt_;
vector <int> e[MAXN];
char c1,c2,c3,ans[MAXN];
void dfs(int now){
	vis[now]=1;
	for(int i=c[now];i<e[now].size();i=c[now]){
		c[now]++;
		dfs(e[now][i]);
	}
	ans[n-cnt+2]=now%256;
	cnt++;
	if(cnt==n+1)ans[1]=now/256,cnt++;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		c1=0;while(c1==' '||c1==0||c1=='\n'||c1=='\r')c1=getchar();
		c2=0;while(c2==' '||c2==0||c2=='\n'||c2=='\r')c2=getchar();
		c3=0;while(c3==' '||c3==0||c3=='\n'||c3=='\r')c3=getchar();
		e[NUM(c1,c2)].push_back(NUM(c2,c3));
		OUT[NUM(c1,c2)]++;IN[NUM(c2,c3)]++;
	}
	for(int i=1;i<=256*256;i++)
	if(OUT[i]>IN[i]){
		if(OUT[i]-IN[i]>=2){printf("NO\n");return 0;}
		if(_cnt_==0)_cnt_=i;
		else{
			printf("NO\n");
			return 0;
		}
	}
	if(_cnt_==0)dfs(NUM(c1,c2));
	else dfs(_cnt_);
	if(cnt!=n+2){
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	for(int i=1;i<=cnt;i++)putchar(ans[i]);
	putchar('\n');
	return 0;
}
```


---

