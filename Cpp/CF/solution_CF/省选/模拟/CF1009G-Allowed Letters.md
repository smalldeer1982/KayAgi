# Allowed Letters

## 题目描述

Polycarp 刚刚启动了他的新创业项目。这个领域相当空白，发展的关键方向也非常有前景，所以他很容易就找到了愿意投资公司的投资人。然而，他还没有给公司起名字！

实际上，Polycarp 已经想好了名字，但对它进行一些改进总是好的。所以现在他想通过交换名字中某些位置的字母来获得一个更好的名字。字母不一定要相邻才可以交换。

此外，每位投资人都选择了名字中的某个位置，并指定了一组可以放在该位置的字母。不同投资人选择的位置互不相同。如果某些位置没有被任何投资人选择，那么这些位置可以放任意字母。

最后，Polycarp 确信字典序最小的名字就是最好的名字。（比如你觉得 Google 为什么要改名叫 Alphabet？）

更正式地说，给定一个只包含小写拉丁字母 $a$ 到 $f$ 的字符串。你可以任意次数交换任意位置的字母（也可以不交换）。

每位投资人都指定了某个位置和该位置允许的字母集合。不同投资人指定的位置互不相同。如果某些位置没有被指定，则这些位置可以放任意字母。

请你求出通过交换字母后，满足每个位置的限制条件下，字典序最小的名字。如果无法得到合法的名字，输出 "Impossible"。

## 说明/提示



由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
bedefead
5
2 e
1 dc
5 b
7 ef
6 ef
```

### 输出

```
deadbeef
```

## 样例 #2

### 输入

```
abacaba
0
```

### 输出

```
aaaabbc
```

## 样例 #3

### 输入

```
fc
2
1 cfab
2 f
```

### 输出

```
cf
```

# 题解

## 作者：Asuka二号机 (赞：6)

看到题的天然想法是维护一下字符集每个子集覆盖到的A集合中的元素的数量，每次贪心放一下，然后什么容斥啊啥的判定是否可行。

想了半天没感觉，然后感觉这题可以网络流，就可以顺着做下去。

首先建立一个网络流模型，A集合是位置，B集合是字符集，B到超级汇连边size是字符数。天然的思路是不断地贪心放下去，每次最最大流查看剩余的位置是否还有完备匹配。这个复杂度显然不能接受，那么考虑其他的判定方法。

各种匹配在算法复杂度已经有一个n的情况下已经算是死了，不过我们知道有hall定理，它是这样说的：

>设二分图的两部分为X、Y，且|X|≤|Y|。则定理描述为：二分图存在完美匹配，等价于对于X的任意子集X′，与它们中任意点相连的Y的结点个数≥|X′|。

顺口胡一下证明

>**必要性：** 因为存在完备匹配，所以X中每个点的出边数大于等于1，必要性得证。

>**充分性：**

>假定当前不存在完备匹配，那么X中有元素$a_0$没有匹配。

>$a_0$必定有至少一条出边，如果这条出边不在匹配中，那就匹配上了，矛盾；因此a的出边全部在匹配中。

>假定$a_0$存在出边$b_1$，我们强制令两者匹配上，那么$b_1$原先的匹配$a_1$失去匹配，因为我们有$a_0$和$a_1$的相邻点集合大小≥2，所以$a_1$必定可以找到$b_1$之外新的匹配。

>我们把这个操作过程中X集合的元素加入$A$，Y的元素加入$B$，假定此时$|A|=|B|$。当前落单的元素$a_k$加入$A$，此时$A$集合的邻居集合$|S|≥|A|>|B|$，$S$中必定存在$B$中没有的点。这样一路操作下去，由于$|X|<|Y|$,于是最终停止在Y，完成匹配。

>这里还没解决$|X|=|Y|$的问题，既然集合大小相等，那么在最大匹配里，Y集合中必定也有个落单点。如果在操作中Y被连上就太好了，如果没有，那么X中所有元素都被遍历，都不和Y连边，那么X全集的邻居数就为$|Y-1|$，不符合条件。

>于是充分性得证。


看着一头雾水，因为A那个大小枚举子集没任何意义啊。

不过有B嘛。

B集合已经被压成6个了，信息有点乱。假设原来的多重集合是$B_0$,$B$实则是把$B_0$压缩起来，我们说$B$中元素$x$的$size$是$x$在$B_0$里出现的次数。

那么$B_0$的子集实际上等价于B的所有子集S，并且S的所有元素x的大小选择$[1,size_x]$的全部方案。这样算来，对于一个子集S而言，无论元素大小如何选择，与A集合中相连的边的数量是确定的，那么最坏的情况无非是大小取满。

所以还要每次都询问出一个集合覆盖到了A集合里的多少点。

ps:突然发觉自己绕回了自己最开始想到的那个结论

考虑贪心过程中要每次删一个点和它导出的所有边，在线改有点难受，那么预处理出每个后缀的这个东西就完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
int n,m,sz[maxn],link[maxn][1<<6],x,cover[maxn];
char s[maxn],ans[maxn];
vector<int>t[maxn];
bool check(int x)
{
    for(int i=0;i<1<<6;i++)
    {
        int a=link[x][i],b=0;
        for(int j=0;j<6;j++)
            if((i>>j)&1)b+=sz[j];
        if(a<b)return 0;
    }
    return 1;
}
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)sz[s[i]-'a']++;
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%s",&x,s+1);
        int len=strlen(s+1);
        for(int j=1;j<=len;j++)
            t[x].push_back(s[j]-'a'),cover[x]+=1<<(s[j]-'a');
    }
    for(int i=1;i<=n;i++)
        if(t[i].size()==0)
        {
            cover[i]=(1<<6)-1;
            for(int j='a';j<='f';j++)t[i].push_back(j-'a');
        }
            
    for(int i=n;i>=1;i--)
    {
        for(int j=0;j<1<<6;j++)
        if(j&cover[i])link[i][j]=link[i+1][j]+1;
        else link[i][j]=link[i+1][j];
    }
    for(int i=1;i<=n;i++)
    {
        sort(t[i].begin(),t[i].end());
        for(auto c:t[i])
        {
            sz[c]--;
            if(check(i+1)){ans[i]=c+'a';break;}
            sz[c]++;
        }
    }
    if(strlen(ans+1)<n)cout<<"Impossible";
    else printf("%s",ans+1);
}
```

---

## 作者：1saunoya (赞：5)

贪心。

我们考虑一个地方能放的是啥，然后存在一个 vector 里面，并用二进制表示（因为 $2^8 = 64$）。

我们发现这个其实是一个完美匹配问题，根据 $Hall$ 定理然后直接贪心的从 $a \to f$ 枚举就可以了（根据字典序大小定义）。

~~这题写过代码~~

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x,I=y+1;i<I;++i)
#define per(i,x,y) for(int i=x,I=y-1;i>I;--i)
using namespace std;
using ll=long long;
void cmax(int&x,const int&y){x=x>y?x:y;}
void cmin(int&x,const int&y){x=x<y?x:y;}
template<class T>istream&operator>>(istream&in,vector<T>&V){for(auto&x:V)in>>x;return in;}
template<class T>ostream&operator<<(ostream&out,const vector<T>&V){for(auto x:V)out<<x<<' ';return out;}
template<class T>void sort(vector<T>&V){sort(V.begin(),V.end());}
template<class T>void reverse(vector<T>&V){reverse(V.begin(),V.end());}
template<class T>int SZ(const vector<T>&V){return (int)V.size();}
void debug(){cerr<<"whxorz"<<'\n';}

const int N = 1e5 + 5;
const int B = 64;
int n, m, sz[N];
int link[N][B];
int cov[N];
vector<int> t[N];
char s[N];
string ans;

bool check(int x) {
	for (int i = 0; i < B; i++) {
		int tmp = 0;
		for (int j = 0; j < 6; j++)
			if (i >> j & 1)
				tmp += sz[j];
		if (link[x][i] < tmp)
			return false;
	}
	return true;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> s + 1;
	n = strlen(s + 1);
	
	for (int i = 1; i <= n; i++)
		sz[s[i] - 'a']++;
		
	cin >> m;
	while (m--) {
		int x;
		string tmp;
		cin >> x >> tmp;
		for (auto y : tmp)
			t[x].push_back(y - 'a'), cov[x] |= 1 << y - 'a';
	}

	for (int i = 1; i <= n; i++) {
		if ((int)t[i].size() == 0) {
			cov[i] = B - 1;
			for (int j = 0; j < 6; j++)
				t[i].push_back(j);
		}
	}
	
	for (int i = n; i >= 1; i--) {
		for (int j = 0; j < B; j++)
			if (j & cov[i])
				link[i][j] = link[i + 1][j] + 1;
			else
				link[i][j] = link[i + 1][j];
	}
	
	for (int i = 1; i <= n; i++) {
		sort(t[i]);
		
		for (auto x : t[i]) {
			sz[x]--;
			if (check(i + 1)) {
				ans.push_back(x + 'a');
				break;
			}
			sz[x]++;
		}
	}
	if ((int)ans.size() < n)
		cout << "Impossible" << '\n';
	else
		cout << ans << '\n';
	return 0;
}
```

---

## 作者：ywy_c_asm (赞：4)

又是比较降智的一道题……

显然我们每次可以贪心的从前往后从小到大填字符，然而我们担心现在虽然可以填这个字符但是可能会导致后面的填不了就gg了，这个容易想到用最大流实现的二分图多重匹配判断是否为完美匹配，就是左部点是$n$个位置，右部点是6个字符，右部点向$t$连个数的边，每次尝试填一个字符，把流量修改一下，判断是否满流即可。

考虑优化，我们知道有个判断完美匹配的东西叫霍尔定理，就是任意右部点的$k$个点与之相邻的左部点不小于$k$个，那么我们干脆暴力建一个真正的左右部点都为$n$的二分图，右部点为所有可选的$n$个字符，这样的话左部点每个位置会向右部点每个可以匹配的字符连边，然后我们就发现**在右部点中相同的字符连的左部点边集是相等的**。所以**我们只需要考虑同种字符的所有点**，因为如果一个字符的所有点构成的点集满足霍尔定理的话，由于它以及它的子集相邻的左部点都是一样的，所以它的子集一定满足霍尔定理。那么我们就可以把同种字符的点看做一个整体点，就有6个整体点，于是我们就可以暴力$2^6$枚举这些点集了。令$f[S]$为后面可选集合与$S$有交的位置数，只要对任意$S$都有$f[S]>=S$的右部点数即可，$f[S]$可以暴力维护。$O(6*2^6n)$。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
namespace ywy {
	int f[64], s[100011], cnt[10], bits[64], df[64];
	char str[100011];
	void ywymain() {
	    cin >> str + 1;
	    int n = strlen(str + 1);
	    for (register int i = 1; i <= n; i++) cnt[str[i] - 'a']++, s[i] = 63;
	    int m;
	    cin >> m;
	    while (m) {
	        m--;
	        int pos;
	        cin >> pos;
	        cin >> str + 1;
	        int len = strlen(str + 1);
	        s[pos] = 0;
	        for (register int i = 1; i <= len; i++) s[pos] |= (1 << (str[i] - 'a'));
	    }
	    for (register int i = 1; i <= n; i++) {
	        for (register int j = 0; j < 64; j++)
	            if ((j & s[i]))
	                f[j]++;
	    }
	    for (register int i = 0; i < 6; i++) df[1 << i] = i;
	    for (register int i = 1; i < 64; i++) bits[i] = bits[i - (i & -i)] + cnt[df[i & -i]];
	    for (register int i = 0; i < 64; i++) {
	        if (f[i] < bits[i]) {
	            printf("Impossible\n");
	            return;
	        }
	    }
	    for (register int i = 1; i <= n; i++) {
	        for (register int k = 0; k < 64; k++)
	            if ((k & s[i]))
	                f[k]--;
	        for (register int j = 0; j < 6; j++) {
	            if (!(s[i] & (1 << j)) || !cnt[j])
	                continue;
	            cnt[j]--;
	            memset(bits, 0, sizeof(bits));
	            for (register int k = 1; k < 64; k++) bits[k] = bits[k - (k & -k)] + cnt[df[k & -k]];
	            for (register int k = 0; k < 64; k++) {
	                if (f[k] < bits[k]) {
	                    cnt[j]++;
	                    goto s;
	                }
	            }
	            printf("%c", j + 'a');
	            break;
	        s:;
	        }
	    }
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：Union_of_Britain (赞：3)

一个 $O(|\Sigma|^2n)$ 的做法。

字典序最小，则从前往后选能选的最小的。

现在压力给到如何判定。容易想到网络流判定，但是看上去每次判定一下复杂度有点爆炸。那么先尝试从后往前构造一组合法解。根据 [CF1168E](https://www.luogu.com.cn/problem/CF1168E) 的想法，考虑根据后面的解来调整。

具体来说，当前 $p_1$ 我想选 $s$，$s$ 却没有了，那么就找到后面的一个填 $a$ 的位置 $p_2$，让它滚（必要的牺牲）。

那么这个 $p_2$ 怎么办？我让另一个位置 $p_3$ 腾位置出来就可以了。如果有解，最后一定会在某个位置 $p_m$ 结束（历史的必然）。

注意到我只关心两个事情：这个路径上的位置可以做这样的替换，并且最后 $p_m$ 变成的字符 $t$ 必须是有余的。那么我把它看成在字符集大小的图上的路径 $P:s\to t$。同时也说明了这样的路径长度大小 $\le |\Sigma|$。

这样的图怎么构造呢？对于每个已经确定为 $c_i$ 的位置 $i$，从 $c_i$ 连向 $u$，并且标记为 $i$ 的转移，如果 $u\neq c_i$ 并且 $u$ 被允许放在 $i$ 位置。两个节点的连边集合，由于涉及插入、删除和找任意一个，可以选用 `unordered_set`。找到这样的路径之后，修改图即可。修改量是单次 $|\Sigma|^2$ 的。

最后构造答案时类似地动态判定即可。需要注意的是后面不能挪用前面的（时代的抉择）。

这样我们就使用更优的复杂度解决了这道题。

很史的考场代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int cur[maxn],sze[6],n,m,alo[maxn][7],vis[6],can[6];
char s[maxn];
unordered_set<int> d[6][6];
#define VI vector<int>
VI CUR;
bool dfs(int u,int t){
	if(u==t)return 1;
	vis[u]=1;
	for(int i=0;i<6;i++){
		if(vis[i])continue;
		if(d[u][i].size()){
			CUR.push_back(i);
			if(dfs(i,t))return 1;
			CUR.pop_back();
		}
	}
	return 0;
}
void DFS(int u){
	can[u]=1;
	for(int i=0;i<6;i++){
		if(can[i])continue;
		if(d[i][u].size())DFS(i);
	}
}
VI findpath(int u,int v){
	CUR={u};
	for(int i=0;i<6;i++)vis[i]=0;
	if(dfs(u,v))return CUR;
	return {};
} 
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>s+1;n=strlen(s+1);
	cin>>m;
	for(int i=1;i<=m;i++){
		int k;string s2;
		cin>>k>>s2;
		for(auto u:s2)alo[k][u-'a']=1;
		alo[k][6]=1;
	}
	for(int i=1;i<=n;i++){
		if(!alo[i][6])for(int j=0;j<6;j++)alo[i][j]=1;
	}
	for(int i=1;i<=n;i++)sze[s[i]-'a']++;
	for(int i=n;i>=1;i--){
		bool flg=0;
		for(int j=0;j<6;j++){
			if(!sze[j])continue;
			if(alo[i][j]){
				sze[j]--;cur[i]=j;
				for(int k=0;k<6;k++)if(alo[i][k]&&j!=k)d[j][k].insert(i);
				flg=1;break;
			}
			VI F;
			for(int k=0;k<6;k++)can[k]=0;
			DFS(j);
			for(int k=0;k<6;k++){
				if(j!=k&&can[k]&&alo[i][k]){
					F=findpath(k,j);
					int t[7];
					for(int i=0;i<F.size()-1;i++)t[i]=(*d[F[i]][F[i+1]].begin()),sze[F[i]]++,sze[F[i+1]]--;
					for(int i=0;i<F.size()-1;i++){
						cur[t[i]]=F[i+1];
						for(int l=0;l<6;l++)if(alo[t[i]][l]&&l!=F[i+1])d[F[i+1]][l].insert(t[i]);
						for(int l=0;l<6;l++)if(alo[t[i]][l]&&l!=F[i])d[F[i]][l].erase(t[i]);
					}
					sze[k]--;
					cur[i]=k;
					for(int l=0;l<6;l++)if(alo[i][l]&&l!=k)d[k][l].insert(i);
					flg=1;
					break;
				}
			}
			if(flg)break;
		}
		if(!flg)return cout<<"Impossible"<<endl,0;
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<6;j++)if(alo[i][j]&&j!=cur[i])d[cur[i]][j].erase(i);
		int res=-1;
		for(int k=0;k<6;k++)can[k]=0;
		DFS(cur[i]);
		for(int j=0;j<cur[i];j++){
			if(!alo[i][j]||!can[j])continue;
			VI F=findpath(j,cur[i]);
			int t[7];
			for(int i=0;i<F.size()-1;i++)t[i]=(*d[F[i]][F[i+1]].begin());
			for(int i=0;i<F.size()-1;i++){
				cur[t[i]]=F[i+1];
				for(int l=0;l<6;l++)if(alo[t[i]][l]&&l!=F[i+1])d[F[i+1]][l].insert(t[i]);
				for(int l=0;l<6;l++)if(alo[t[i]][l]&&l!=F[i])d[F[i]][l].erase(t[i]);
			}
			res=j;
			break;
		}
		if(res==-1)res=cur[i];
		cur[i]=res;
		cout<<(char)(res+'a');
	}
	return 0;
}
```

---

## 作者：xtx1092515503 (赞：3)

CF官方题解思路I：

凡是字典序最小的东西都可以贪心，因为只要保证当前位填出的东西尽量大，后面的位都只要保证有个解就行了。比如这道题，就是枚举每一位填什么，然后用网络流判断出后面有无合法解。

我们顺序枚举每一位填什么。我们建出$6$个点代表$'a'$到$'f'$字符，同时将每位可以填的字符种类状压一下，状压出$2^6$个点。每个字符向所有包含着它的状态连一条无穷大的边，源点向每个字符连“剩余部分该字符出现次数”边权的边，同时每个bitmask向汇点连“剩余部分该bitmask出现次数”边权的边。这就是相当于用$6$个字符与$2^6$个bitmask进行**二分图多重匹配**。

这样，如果跑出来的最大流等于“剩余部分长度”，则当前位填入该字符是合法的。

如果我们就这么直接每次都跑一遍网络流的话，复杂度最差为
$n*A*{(A+2^A)}^2*(2^{A-1}*A)$，假设网络流复杂度为常规的$n^2m$（$n^2\sqrt{m}$的HLPP不在讨论范围内），而$A$为字符集大小。
代入$n={3*10}^5,A=6$，得复杂度最劣为${3*10}^5*6*{70}^2*192\approx1.7*{10}^{12}$。因为网络流复杂度玄学，不妨乘上一个百分之一的常数，得复杂度约为$1.7*{10}^{10}$，不可能通过本题。

以下是这个TLE的暴力网络流代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int lim=1<<6;
int n,mask[100100],m,tot[lim],cmp[6];
char s[100100],ss[6],ans[100100];
namespace MaxFlow{
	const int N=10000,M=200000;
	int head[N],cur[N],dep[N],cnt,S,T,res;
	struct node{
		int to,next,val;
	}edge[M];
	void ae(int u,int v,int w){
		edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=w,head[u]=cnt++;
		edge[cnt].next=head[v],edge[cnt].to=u,edge[cnt].val=0,head[v]=cnt++;
	}
	queue<int>q;
	inline bool bfs(){
		memset(dep,0,sizeof(dep)),q.push(S),dep[S]=1;
		while(!q.empty()){
			register int x=q.front();q.pop();
			for(register int i=cur[x]=head[x];i!=-1;i=edge[i].next)if(edge[i].val&&!dep[edge[i].to])dep[edge[i].to]=dep[x]+1,q.push(edge[i].to);
		}
		return dep[T]>0;
	}
	bool reach;
	inline int dfs(int x,int flow){
		if(x==T){
			res+=flow;
			reach=true;
			return flow;
		}
		int used=0;
		for(register int &i=cur[x];i!=-1;i=edge[i].next){
			if(!edge[i].val||dep[edge[i].to]!=dep[x]+1)continue;
			register int ff=dfs(edge[i].to,min(edge[i].val,flow-used));
			if(ff){
				edge[i].val-=ff;
				edge[i^1].val+=ff;
				used+=ff;
				if(used==flow)break;
			}
		}
		return used;
	}
	inline void Dinic(){
		while(bfs()){
			reach=true;
			while(reach)reach=false,dfs(S,0x3f3f3f3f);
		}
	}
}
using namespace MaxFlow;
int che(){
	for(register int i=head[S];i!=-1;i=edge[i].next)edge[i].val=cmp[edge[i].to],edge[i^1].val=0;
	for(register int i=head[T];i!=-1;i=edge[i].next)edge[i^1].val=tot[edge[i].to-6],edge[i].val=0;
	res=0;
	Dinic();
	return res;
}
inline void read(int &x){
	x=0;
	register char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
}
inline void print(int x){
	if(x<=9)putchar('0'+x);
	else print(x/10),putchar('0'+x%10);
}
int main(){
	scanf("%s",s+1),n=strlen(s+1),S=6+lim,T=6+lim+1;
	for(register int i=1;i<=n;i++)cmp[s[i]-'a']++;
	read(m);
	for(register int i=1,x,y;i<=m;i++){
		read(x),scanf("%s",ss),y=strlen(ss);
		for(register int j=0;j<y;j++)mask[x]|=1<<(ss[j]-'a'); 
	}
	for(register int i=1;i<=n;i++)if(!mask[i])mask[i]=lim-1;
	for(register int i=1;i<=n;i++)tot[mask[i]]++;
	memset(head,-1,sizeof(head));
	for(register int i=0;i<6;i++)ae(S,i,cmp[i]);
	for(register int i=0;i<lim;i++)for(register int j=0;j<6;j++)if(i&(1<<j))ae(j,i+6,0x3f3f3f3f);
	for(register int i=0;i<lim;i++)ae(i+6,T,tot[i]);
	Dinic();
	if(res!=n){puts("Impossible");return 0;}
	for(register int i=1;i<=n;i++)for(register int j=0;j<6;j++){
		if(!(mask[i]&(1<<j)))continue;
		if(!cmp[j])continue;
		tot[mask[i]]--,cmp[j]--;
		if(che()!=n-i)tot[mask[i]]++,cmp[j]++;
		else{ans[i]='a'+j;break;}
	}
	ans[n+1]='\0';
	printf("%s",ans+1);
	return 0;
}
```
网络流题最有效的优化是什么？**残量网络优化**。在重跑网络流时，不再全体清空边权，而是只清空少量边权，其它部分仍沿用之前结果。

我们考虑当尝试在一个bitmask为$msk$的位置上填入字符$chr$的变化：

首先，我们找出边$(S,chr)$和$(msk,T)$。显然，这两条边必须是满流量的（不然最大流肯定不为$n$）。

我习惯**只记录边的残量**。因此，我们可以观察它们的反边，则反边上的残量即为当前正边上的流量，也就是正边上的流量上限（最大流必定满流）。如果反边残量为0，就意味着正边流量为$0$，就意味着正边流量上限为$0$，就意味着$chr$或$msk$已经一个不剩了，因此肯定是不合法的，直接跳掉。

如果边$(chr,msk)$上流量不为零（即反边有残量），则我们完全可以直接使这条边上流量减一，直接判为合法并退出。

否则，我们找到一条新的增广路$(S\rightarrow 1\rightarrow x\rightarrow T)$，其中这个$x$可以是任何节点。当然，这里面任何一条边，都必须有流量（而不是常规增广路的定义 **“未满流的路径”** ，因为这条增广路是为退流而用）。

当我们找到这样一条增广路后（必然存在，因为边$(S,chr)$出来的流量最终肯定流向汇点），就把增广路上每一条边的流量全都减少一（即反边残量减一，正边残量加一）。

同时，我们从$msk$出发，找一条反向的增广路，道理还是退流，只不过这里找的就是常规增广路（未满流的路径），因为这回的退流就是反边残量加一，正边残量减一。

全都做完以后，删去边$(S,chr)$与$(msk,T)$的各一点流量，因为这次匹配后，$chr$和$msk$的出现次数将会各减少1，固然是需要删去的。

这么一番操作后，我们成功拆掉了两点流量（正增广路的一点，反增广路的一点）。然后，我们再要跑最大流验证不小心多拆的那一点（即边$(chr,msk)$上原应有的那一点）能不能补回来。如果可以，那这次匹配就算成功了，直接退出。否则，匹配失败，去掉两条增广路的所有影响，返回匹配失败。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int lim=1<<6;
int n,mask[100100],m,tot[lim],cmp[6],enm[80][80];
char s[100100],ss[6];
namespace MaxFlow{
	const int N=10000,M=200000;
	int head[N],cur[N],dep[N],cnt,S,T,res;
	struct node{
		int to,next,val;
	}edge[M];
	void ae(int u,int v,int w){
		enm[u][v]=cnt,edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=w,head[u]=cnt++;
		enm[v][u]=cnt,edge[cnt].next=head[v],edge[cnt].to=u,edge[cnt].val=0,head[v]=cnt++;
	}
	queue<int>q;
	inline bool bfs(){
		memset(dep,0,sizeof(dep)),q.push(S),dep[S]=1;
		while(!q.empty()){
			register int x=q.front();q.pop();
			for(register int i=cur[x]=head[x];i!=-1;i=edge[i].next)if(edge[i].val&&!dep[edge[i].to])dep[edge[i].to]=dep[x]+1,q.push(edge[i].to);
		}
		return dep[T]>0;
	}
	bool reach;
	inline int dfs(int x,int flow){
		if(x==T){
			res+=flow;
			reach=true;
			return flow;
		}
		int used=0;
		for(register int &i=cur[x];i!=-1;i=edge[i].next){
			if(!edge[i].val||dep[edge[i].to]!=dep[x]+1)continue;
			register int ff=dfs(edge[i].to,min(edge[i].val,flow-used));
			if(ff){
				edge[i].val-=ff;
				edge[i^1].val+=ff;
				used+=ff;
				if(used==flow)break;
			}
		}
		return used;
	}
	inline void Dinic(){
		while(bfs()){
			reach=true;
			while(reach)reach=false,dfs(S,0x3f3f3f3f);
		}
	}
}
using namespace MaxFlow;
inline void read(int &x){
	x=0;
	register char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
}
inline void print(int x){
	if(x<=9)putchar('0'+x);
	else print(x/10),putchar('0'+x%10);
}
bool fillin(int msk,int cha){
	if(!(msk&(1<<cha)))return false;
	int p1=cha,p2=msk+6;
	int e1=enm[S][p1],e2=enm[p2][T];
	if(!edge[e1^1].val||!edge[e2^1].val)return false;
	edge[e1^1].val--;
	edge[e1].val++;
	vector<int>afe;
	afe.push_back(e1);
	for(int i=head[p1],x;i!=-1;i=edge[i].next){
		if((i&1)||!edge[i^1].val)continue;
		afe.push_back(i);
		edge[i^1].val--;
		edge[i].val++;
		x=edge[i].to;
		for(int j=head[x];j!=-1;j=edge[j].next){
			if(j&1)continue;
			afe.push_back(j);
			edge[j^1].val--;
			edge[j].val++;
			break;
		}
		break;
	}
	if(edge[e2].val){edge[e2].val--,edge[e1].val--;return true;}
	afe.push_back(e2);
	edge[e2^1].val--;
	edge[e2].val++;
	for(int i=head[p2],x;i!=-1;i=edge[i].next){
		if(!(i&1)||!edge[i].val)continue;
		afe.push_back(i^1);
		edge[i^1].val++;
		edge[i].val--;
		x=edge[i].to;
		for(int j=head[x];j!=-1;j=edge[j].next){
			if(!(j&1))continue;
			afe.push_back(j^1);
			edge[j^1].val++;
			edge[j].val--;
			break;
		}
		break;
	}
	edge[e1].val--;
	edge[e2].val--;
	res=0;
	Dinic();
	if(res)return true;
	edge[e1].val++;
	edge[e2].val++;
	for(int i=0;i<afe.size();i++)edge[afe[i]].val--,edge[afe[i]^1].val++;
	return false;
} 
int main(){
	scanf("%s",s+1),n=strlen(s+1),S=6+lim,T=6+lim+1;
	for(register int i=1;i<=n;i++)cmp[s[i]-'a']++;
	read(m);
	for(register int i=1,x,y;i<=m;i++){
		read(x),scanf("%s",ss),y=strlen(ss);
		for(register int j=0;j<y;j++)mask[x]|=1<<(ss[j]-'a'); 
	}
	for(register int i=1;i<=n;i++)if(!mask[i])mask[i]=lim-1;
	for(register int i=1;i<=n;i++)tot[mask[i]]++;
	memset(head,-1,sizeof(head));
	for(register int i=0;i<6;i++)ae(S,i,cmp[i]);
	for(register int i=0;i<lim;i++)for(register int j=0;j<6;j++)if(i&(1<<j))ae(j,i+6,0x3f3f3f3f);
	for(register int i=0;i<lim;i++)ae(i+6,T,tot[i]);
	Dinic();
	if(res!=n){puts("Impossible");return 0;}
	for(register int i=1;i<=n;i++)for(register int j=0;j<6;j++)if(fillin(mask[i],j)){putchar('a'+j);break;}
	return 0;
}
```
CF官方题解思路II：有个叫做Hall's theorem的奇怪玩意，我也不会用……


---

## 作者：大菜鸡fks (赞：3)

贪心是没问题的。 关键是如何判断后面方案能否成立

考虑这是一个完美匹配问题。而且二分图右侧的集合只有6种元素。

可以自然想到霍尔定理：二部图G中的两部分顶点组成的集合分别为X, Y; G中有一组无公共点的边，一端恰好为组成X的点的充分必要条件是：X中的任意k个点至少与Y中的k个点相邻。

也就是说可以枚举右边点的组成，来判断左边点是否合法。

右边点的组成只有1<<6种情况。 

每次选一个字符前判断一下能否选，能选就选。

```cpp
#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e5+5;
char s[N],ans[N];
int n,cnt[1<<6],f[N][1<<6],edge[N],m;
inline void init(){
	scanf("%s",s+1);
	n=strlen(s+1);
	for (int i=1;i<=n;i++){
		for (int j=0;j<(1<<6);j++){
			if (j&(1<<(s[i]-'a'))){
				cnt[j]++;
			}
		}
	}
	for (int i=1;i<=n;i++){
		edge[i]=(1<<6)-1;
	}
	scanf("%d",&m);
	for (int i=1;i<=m;i++){
		char S[10]; int x;
		scanf("%d %s",&x,S+1);
		int len=strlen(S+1);
		edge[x]=0;
		for (int j=1;j<=len;j++){
			edge[x]|=1<<(S[j]-'a'); 
		}
	}
}
inline void solve(){
	for (int i=n;i;i--){
		for (int j=0;j<(1<<6);j++){
			f[i][j]=f[i+1][j];
			if ((j&edge[i])==edge[i]) f[i][j]++;
		}
	}
	bool ok=0;
	for (int i=1;i<=n;i++){
		bool flag=false;
		for (int j=0;j<6&&!flag;j++){
			if (cnt[1<<j]&&(edge[i]&(1<<j))){
				ok=1;
				for (int k=0;k<(1<<6)&&ok;k++){
					if (f[i+1][k]>cnt[k]-((k>>j)&1)){
						ok=false;
					}
				}
				if (ok){
					flag=1;
					ans[i]='a'+j;
					for (int k=0;k<(1<<6);k++){
						if (k&(1<<j)) cnt[k]--;
					}
				}
			}
		}
		if (!flag){
			puts("Impossible");
			return;
		}
	}
	puts(ans+1);
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：bmatrix (赞：2)

[题面](https://www.luogu.com.cm/problem/CF1009G)。

本文节选自我的[二分图学习笔记](https://www.cnblogs.com/untitled0/p/bipartite-graph.html)，欢迎来玩！

> 有一个长为 $n$ 的字符串 $s$，只包含 $\texttt a\dots\texttt f$ 共 $6$ 种字符。你知道每种字符的出现次数，和每个位置可能出现哪些字符，你需要构造出满足条件且字典序最小的 $s$。

不难发现这是一个位置和字符之间的匹配问题，考虑建图网络流。

设字符 $c$ 的出现次数为 $\mathrm{cnt}_c$。从源点 $S$ 向每个位置 $i$ 连容量为 $1$ 的边，每个位置向这个位置可能出现的字符连容量为 $1$ 的边，每个字符 $c$ 向汇点 $T$ 连容量为 $\mathrm{cnt}_c$ 的边，跑最大流，如果能流满就有解，否则无解。

然而直接网络流难以找到字典序最小的匹配。网络流算法的流程很复杂，我们把握不住，所以尽量不要尝试改动网络流的板子，而是考虑其他方法。

最大 / 最小化字典序的问题都可以贪心。从前往后枚举位置 $i$，尽量让 $i$ 放更小的字符。因此我们需要解决的问题转化为：当位置 $i$ 流向字符 $c$ 时，剩下的点还能否流满。

注意到如果不算源点和汇点，这就判断二分图是否有完美多重匹配（多重匹配：每个点 $u$ 最多被 $l_u$ 条边覆盖，而非一般匹配的 $1$ 条边）。我们可以通过把每个点拆成 $l_u$ 个点转化成一般匹配。我们称位置对应的点集为“位置部”，字符对应的点集为“字符部”。

此时我们需要引入 Hall 定理：

>对于二分图 $G=(A,B,E),|A|\le|B|$，定义函数 $f(S)$ $(S\subseteq A)$ 表示与 $S$ 中的点有连边的点的数量，则 $G$ 存在完美匹配的充要条件是 $\forall S\subseteq A,f(S)\ge|S|$。

我们显然不能枚举位置部的所有子集，但是字符部只有 $6$ 个本质不同的点，相同的点无论放多少个，对 $f$ 值都只会产生一个点的影响，所以只需要枚举 $6$ 种字符的所有子集，只有 $2^6=64$ 种情况。

对于每个 $i$，预处理出每个子集的后缀 $f$ 值，即只考虑 $i$ 到 $n$ 这些位置时，每个子集的 $f$ 值，然后贪心枚举即可。

设字符集为 $\Sigma$，则时间复杂度为 $O(n|\Sigma|2^{|\Sigma|})$。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
#define rep(i, s, e) for(int i = s, i##E = e; i <= i##E; ++i)
#define per(i, s, e) for(int i = s, i##E = e; i >= i##E; --i)
#define F first
#define S second
// #define int ll
#define gmin(x, y) (x = min(x, y))
#define gmax(x, y) (x = max(x, y))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double f128;
typedef pair<int, int> pii;
constexpr int N = 1e5 + 5;
int n, t, cnt[6], sum[64], f[N][64];
bool ava[N][6];
string s;
signed main() {
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
#endif
    cin >> s; n = s.size();
    for(auto c : s) cnt[c - 'a']++;
    rep(i, 0, 63) rep(j, 0, 5) if(i >> j & 1) sum[i] += cnt[j];
    cin >> t;
    memset(ava, 1, sizeof ava);
    rep(i, 1, t) {
        int p; cin >> p >> s;
        memset(ava[p], 0, sizeof ava[p]);
        for(auto c : s) ava[p][c - 'a'] = 1;
    }
    per(i, n, 1) {
        memcpy(f[i], f[i + 1], sizeof f[i]);
        rep(j, 0, 63) rep(k, 0, 5)
            if((j >> k & 1) && ava[i][k]) 
                { ++f[i][j]; break; }
    }
    s.clear();
    rep(i, 1, n) {
        bool flg = 0;
        rep(j, 0, 5) if(ava[i][j]) {
            bool fl = 1;
            rep(k, 0, 63) 
                if(k >> j & 1) {
                    if(f[i + 1][k] < sum[k] - 1) { fl = 0; break; }
                }
                else if(f[i + 1][k] < sum[k]) { fl = 0; break; }
            if(fl) {
                flg = 1; s.push_back(j + 'a');
                rep(k, 0, 63) if(k >> j & 1) --sum[k];
                break;
            }
        }
        if(!flg) cout << "Impossible\n", exit(0);
    }
    cout << s << endl;
    return 0;
}
```

---

## 作者：Pink_Dove (赞：0)

[AC 记录](https://codeforces.com/contest/311/submission/310519486)

[更 pass 的食用体验](https://yumomeow.github.io/2025/03/24/solution-CF1009G/)
### 题意
给定一个长为 $n$ 的串，字符集 `a` 到 `f`。你可以重排这个串，满足指定 $m$ 个位置上只能放特定的字符，求字典序最小的串。无解输出 `Impossible`。

### 题解
考虑网络流，每个位置向可能出现的字符连边，跑最大流看能否流满即可，但这样很难找到字典序最小的匹配。

显然字典序问题都可以贪心考虑，对每一位尽量放更小的字符，**判断剩下的位置能否满足条件**，考虑解决这个问题。以位置为左部，原串的字符为右部建立二分图，实际上是在求一个二分图完美匹配，对于这个问题我们有 Hall 定理：
> 对于二分图 $G=(A,B,E),|A|\le |B|$，定义 $f(S)$ 表示与点集 $S(S\subseteq A)$ 中的点有连边的点的数量，则 $G$ 存在完美匹配的充要条件是 $\forall S\subseteq A,f(S)\ge |S|$。

因为字符集只有 `a...f`，枚举所有子集只有 $2^6$ 种情况，对于每个 $i$ 枚举并判断即可。关于 $f$ 值，从后往前枚举则考虑后 $i$ 个字符的 $f$ 值可以从考虑后 $i+1$ 个字符的 $f$ 值转移而来。

复杂度 $O(6\times 2^6n)$。

### 代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
constexpr int N=1e5+10;
int n,m,cnt[6],sum[64],f[N][64];
bool lim[N][6];
string s,ans;
signed main(){
    cin>>s; 
    n=s.size();
    for(auto c:s) cnt[c-'a']++;
    for(int i=0;i<64;i++){
        for(int j=0;j<=5;j++){
            if(i>>j&1) sum[i]+=cnt[j];
        } 
    }
    cin>>m;
    memset(lim,1,sizeof(lim));
    for(int i=1;i<=m;i++){
        int p; 
        cin>>p>>s;
        for(int j=0;j<=5;j++) lim[p][j]=0;
        for(auto c:s) lim[p][c-'a']=1;//每个位置能放的字符
    }
    for(int i=n;i>=1;i--){
        for(int j=0;j<64;j++){
            f[i][j]=f[i+1][j];
            for(int k=0;k<=5;k++){
                if((j>>k&1)&&lim[i][k]){
                    f[i][j]++;
                    break;//预处理 f 值
                }          
           }
        } 
    }
    for(int i=1;i<=n;i++){
        bool fll=0;
        for(int j=0;j<=5;j++){
            if(!lim[i][j]) continue;
            bool fl=1;
            for(int k=0;k<64;k++){
                if(k>>j&1){
                    if(f[i+1][k]<sum[k]-1){ 
                        fl=0; 
                        break; //hall 定理判断
                    }
                }
                else if(f[i+1][k]<sum[k]){ 
                    fl=0; 
                    break; 
                }                
            }
            if(fl) {
                fll=1; ans.push_back(j+'a');
                for(int k=0;k<64;k++) if(k>>j&1) sum[k]--;
                break;
            }
        }
        if(!fll) cout<<"Impossible\n",exit(0);
    }
    cout<<ans;
    return 0;
}
```

---

