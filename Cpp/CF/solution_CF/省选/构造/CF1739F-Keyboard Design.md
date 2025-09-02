# Keyboard Design

## 题目描述

Monocarp has a dictionary of $ n $ words, consisting of $ 12 $ first letters of the Latin alphabet. The words are numbered from $ 1 $ to $ n $ . In every pair of adjacent characters in each word, the characters are different. For every word $ i $ , Monocarp also has an integer $ c_i $ denoting how often he uses this word.

Monocarp wants to design a keyboard that would allow him to type some of the words easily. A keyboard can be denoted as a sequence of $ 12 $ first letters of the Latin alphabet, where each letter from a to l appears exactly once.

A word can be typed with the keyboard easily if, for every pair of adjacent characters in the word, these characters are adjacent in the keyboard as well. The optimality of the keyboard is the sum of $ c_i $ over all words $ i $ that can be typed easily with it.

Help Monocarp to design a keyboard with the maximum possible optimality.

## 样例 #1

### 输入

```
3
7 abacaba
10 cba
4 db```

### 输出

```
hjkildbacefg```

## 样例 #2

### 输入

```
1
100 abca```

### 输出

```
abcdefghijkl```

# 题解

## 作者：_SeeleVollerei_ (赞：3)

提前发放，总不可能有人 3min 看完我的 blog 然后写完吧。

调了大半年的 E 没调出来，然后没空写 F 了，这里先写个口胡做法，明天打完模拟赛再写。

首先显然每个串对应在键盘上一个固定的子串。相当于给了你若干个子串，然后每个有个贡献的值。要求构造一个排列，求贡献值最大。

这个问题可以放到 ACAM 上解决。具体地，把转换后的子串建成 ACAM，然后在对应的点上记录贡献。然后令 $f_{i,j}$ 表示当前最后一个字符走到点 $i$，且 12 个字符的出现情况状压成了 $j$ 的最大贡献，然后暴力枚举儿子转移即可。时间复杂度为 $O(12\times2^{12}\sum|s|)$，空间复杂度为 $O(2^{12}\sum|s|)$。空间特别小，时间有 4s 的时限。

明天下午回来写。

upd：写了一下，记得 ACAM 空间要开两倍。

https://codeforces.com/contest/1739/submission/174053369

---

## 作者：封禁用户 (赞：1)

思维题。码量题。

首先一个单次如果能被便捷的敲出来，当且仅当它的所有字母两边的字母都与它在键盘上相邻。这样我们可以对于每个单词整理出一个计入贡献时字母在键盘上的相邻关系。接下来我们针对 $12$ 个不同**字母**分析。

我们很容易注意到，如果一个单词要求一个字母周围有大于等于 $3$ 个邻近的不同字母，那么这个单词无论如何都无法计入贡献。否则必然至多存在 $2$ 个出现在此单词中的字母邻近于仅 $1$ 个不同字母。

数学归纳法。只有两个字母的字符串显然满足条件。假设 $S$ 为一个字符串且 $c$ 为一个字符，并且 $S$ 满足至多存在 $2$ 个出现在 $S$ 中的字母邻近于仅 $1$ 个不同字母，且不存在一个字母邻近于至少 $3$ 个不同字母，以及 $S+c$ 也不存在一个字母临近于至少 $3$ 个不同字母（$S+c$ 相邻字符不同）。

- 进行奇偶性分析可得，$S$ 必然存在恰好 $0$ 或 $2$ 个字母临近于仅 $1$ 个不同字母。

- 把字母作为点，$S$ 中相邻的字母之间连一条边。如果 $S$ 没有这样的字母，那么所有出现过的字母将会连成一个环（道理很简单：所有出现过字母连通），而如果 $S$ 有 $2$ 个这样的字母，所有出现过字母会形成一条链。

- 如果在 $S$ 后面增加一个字符 $c$，相当于如果 $S$ 的最后一个字符与 $c$ 没有连过边就连一条，此时最后一个字符的出度必然为 $1$，也即所有字母形成一条链，那么 $c$ 要么没有出现在 $S$ 中，要么是另一个链头，连完后形成一个环。如果 $S$ 最后一个字符与 $c$ 已经连过边了，那么原先是环现在还是环，原先是链现在还是链。

- 操作完之后最终肯定仍然是环或者链，那么 $S+c$ 也满足上述性质。

扯那么多是干嘛呢？如果一个单词（没有出现邻近于 $3$ 个不同字母的字母）所有字母按照上述连边方式连出来一个环，那无论如何都无法便捷的被敲出来，而如果连出来的是条链，那么只要这条链从链头到链尾正着或者反着出现在键盘中，该单词就可以贡献频率权值。

由于不同字母数量非常少，时间限制又很大，一条链又无法正着反着**同时**出现在键盘里，我们可以将所有合法单词的链正反一起建一个 $\text{AC}$ 自动机并且将频率权值下传到可以通过失配指针（也即 $\text{border}$ 指针）跳到当且点的所有点。然后利用状态压缩计算答案即可（方程式设 $f_{i,j}$ 表示当前没定过的字母状态为 $i$，目前跳到 $\text{AC}$ 自动机的 $j$ 号点）。

代码实现非常长，相当适合锻炼码力：

```cpp
#include<bits/stdc++.h>
using namespace std;

struct node{
	int son[13],fail,val;
}vert[18005];

int n,c[2005],len[2005],ths[2005][13],pt,clnk[12],ctow[12][12],pt2,rot,dp[4096][18005],H[4096][18005][2],ans,hs1,hs2;

int nw(){
	return++pt2;
}

int nwvert(int now,int num){
	if(vert[now].son[num]==0){
		return vert[now].son[num]=nw();
	}
	return vert[now].son[num];
}

int Link(int now,int num){
	if(vert[now].son[num]==0){
		if(vert[now].fail==0)return rot;
		return Link(vert[now].fail,num);
	}
	return vert[now].son[num];
}

void bfs(){
	queue<int>q;q.push(rot);
	while(!q.empty()){
		int now=q.front();q.pop();
		for(int o=1;o<=12;o++){
			if(vert[now].son[o]!=0){
				vert[vert[now].son[o]].fail=now==0?1:Link(vert[now].fail,o);
				vert[vert[now].son[o]].val+=vert[vert[vert[now].son[o]].fail].val;
				q.push(vert[now].son[o]);
			}
		}
	}
}

int main(){
	memset(dp,0xb0,sizeof(dp));
	cin>>n;
	for(int i=1;i<=n;i++){
		int val;string s;bool satis1=0,satis2=1;cin>>val>>s;
		for(int o=0;o<12;o++){
			clnk[o]=0;
			for(int oo=0;oo<12;oo++)ctow[o][oo]=0;
		}
		for(int o=0;o<s.size()-1;o++){
			if(!ctow[s[o]-'a'][s[o+1]-'a'])clnk[s[o]-'a']++;
			ctow[s[o]-'a'][s[o+1]-'a']=1;
			if(!ctow[s[o+1]-'a'][s[o]-'a'])clnk[s[o+1]-'a']++;
			ctow[s[o+1]-'a'][s[o]-'a']=1;
		}
		for(int o=0;o<12;o++){
			if(clnk[o]==1)satis1=1;
			if(clnk[o]>2)satis2=0;
		}
		if(!(satis1&satis2))continue;
		pt++;c[pt]=val;
		for(int o=0;o<12;o++){
			if(clnk[o]!=1)continue;
			for(int oo=o,Lst=-1;;){
				ths[pt][++len[pt]]=oo+1;
				int Nxt=-1;
				for(int ooo=0;ooo<12;ooo++){
					if(ooo==Lst)continue;
					if(ctow[oo][ooo]){
						Nxt=ooo;break;
					}
				}
				if(Nxt==-1)break;
				Lst=oo;oo=Nxt;
			}
			break;
		}
	}
	for(int i=1;i<=pt;i++){
		len[i+pt]=len[i];c[i+pt]=c[i];
		for(int j=1;j<=len[i];j++){
			ths[i+pt][j]=ths[i][len[i]+1-j];
		}
	}
	pt*=2;rot=nw();
	for(int i=1;i<=pt;i++){
		int cur=rot;
		for(int j=1;j<=len[i];j++){
			cur=nwvert(cur,ths[i][j]);
		}
		vert[cur].val+=c[i];
	}
	bfs();dp[0][1]=0;
	for(int zt=0;zt<4096;zt++){
		for(int o=1;o<=12;o++){
			if((zt&(1<<o-1))!=0)continue;
			for(int i=1;i<=pt2;i++){
				int Nxt=Link(i,o);
				dp[zt^(1<<o-1)][Nxt]=max(dp[zt^(1<<o-1)][Nxt],dp[zt][i]+vert[Nxt].val);
				if(H[zt^(1<<o-1)][Nxt][1]==0||dp[zt][i]+vert[Nxt].val==dp[zt^(1<<o-1)][Nxt]){
					H[zt^(1<<o-1)][Nxt][0]=zt;H[zt^(1<<o-1)][Nxt][1]=i;
				}
			}
		}
	}
	hs1=4095;
	for(int i=1;i<=pt2;i++){
		ans=max(ans,dp[4095][i]);
		if(dp[4095][i]==ans)hs2=i;
	}
	while(hs1!=0){
		int xornum=hs1^H[hs1][hs2][0];
		for(int o=1;o<=12;o++){
			if(xornum==(1<<o-1)){
				cout<<char('a'+o-1);break;
			}
		}
		hs2=H[hs1][hs2][1];hs1^=xornum;
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：1)

对于每个输入的串，我们可以将其整理为另一个等价的每个元素互不相同的串 $s'$，其中如果要满足这个串（即获得 $c_i$ 贡献），所有 $s'_i$ 和 $s'_{i+1}$ 键必须相邻。

将所有 $s'$ 塞到 ACAM 中。考虑 $dp_{S,i}$，表示目前已经用了 $S$ 集合内的所有键，目前在 ACAM 中 $i$ 节点的最高价值。转移时枚举下一个键是啥即可。总复杂度 $O(2^VV\sum|s_i|)$，其中 $V$ 为字符集大小，此处为 $12$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
int trie[4005][26],cnt,fail[4005],val[4005],g[26][26];
int dp[4096][4005],frma[4096][4005],frmb[4096][4005];
char pr[4096];
vector<int> vc[26];
void add(string s,int num){
	int now=0;
	for(int i=0;i<s.size();i++){
		if(!trie[now][s[i]-'a']) trie[now][s[i]-'a']=++cnt;
		now=trie[now][s[i]-'a'];
	}
	val[now]+=num;
}
string dfs(int now,int fa){
	for(auto v:vc[now]){
		if(v==fa) continue;
		return (char)(now+'a')+dfs(v,now);
	}
	string s="";
	s+=(char)(now+'a');
	return s;
}
string getstring(string s){
	memset(g,0,sizeof(g));
	for(int i=0;i<26;i++) vc[i].clear();
	for(int i=1;i<s.size();i++){
		if(!g[s[i]-'a'][s[i-1]-'a']) vc[s[i]-'a'].push_back(s[i-1]-'a');
		if(!g[s[i-1]-'a'][s[i]-'a']) vc[s[i-1]-'a'].push_back(s[i]-'a');
		g[s[i]-'a'][s[i-1]-'a']=g[s[i-1]-'a'][s[i]-'a']=1;
	}
	int cnt0=0,cnt1=0,cnt2=0;
	for(int i=0;i<26;i++) cnt0+=(vc[i].size()==0),cnt1+=(vc[i].size()==1),cnt2+=(vc[i].size()==2);
	string ans="";
	if(cnt0+cnt1+cnt2==26&&cnt1){
		int st=0;
		for(int i=0;i<26;i++){
			if(vc[i].size()==1){
				st=i;
				break;
			}
		}
		return dfs(st,-1);
	}
	return ans;
}
void getacam(){
	queue<int> q; for(int i=0;i<26;i++) if(trie[0][i]!=0) q.push(trie[0][i]);
	while(!q.empty()){
		int f=q.front(); q.pop();
		val[f]+=val[fail[f]];
		for(int i=0;i<26;i++){
			if(trie[f][i]) fail[trie[f][i]]=trie[fail[f]][i],q.push(trie[f][i]);
			else trie[f][i]=trie[fail[f]][i];
		}
	}
}
signed main(){
	for(int i=0;i<12;i++) pr[1<<i]=i+'a';
	int n,tag=0; cin>>n;
	for(int i=1;i<=n;i++){
		int num; cin>>num;
		string s; cin>>s;
		s=getstring(s);
		if(s=="") continue;
		add(s,num);
		reverse(s.begin(),s.end());
		add(s,num);
	}
	getacam();
	memset(dp,-1,sizeof(dp));
	dp[0][0]=0;
	for(int i=0;i<(1<<12);i++){
		for(int j=0;j<=cnt;j++){
			if(dp[i][j]==-1) continue; 
			for(int k=0;k<12;k++){
				if(!((i>>k)&1)){
					if(dp[i|(1<<k)][trie[j][k]]<dp[i][j]+val[trie[j][k]]){
						dp[i|(1<<k)][trie[j][k]]=dp[i][j]+val[trie[j][k]];
						frma[i|(1<<k)][trie[j][k]]=i;
						frmb[i|(1<<k)][trie[j][k]]=j;
					}
				}
			}
		}
	}
	int maxv=-1,maxpos;
	for(int j=0;j<=cnt;j++) if(dp[(1<<12)-1][j]>maxv) maxv=dp[(1<<12)-1][j],maxpos=j;
	int nowi=(1<<12)-1,nowj=maxpos;
	for(int i=1;i<=12;i++){
		int lsti=frma[nowi][nowj],lstj=frmb[nowi][nowj];
		cout<<pr[lsti^nowi];
		nowi=lsti,nowj=lstj;
	}
	return 0;
}
```

---

## 作者：Alex_Wei (赞：1)

对于一个单词，我们在相邻字符之间连边，去掉重边之后图的形态只能为一条链，因为键盘上每个字符至多和两个字符相邻。

如果不是一条链，则忽略该单词。否则，从链的一端走到另一端，得到如果可以敲出该单词，则键盘必须包含的子串。注意有两种走法，正反作为子串均可，且因为 $|s_i| > 1$ 所以不会重复统计。

然后就可以 DP 了。对所有这样的子串，我们建出 AC 自动机，然后设 $f_{S, p}$ 表示用掉了集合 $S$ 的字符，当前匹配到 AC 自动机的状态 $p$ 的最大收益。因为字符互不相同所以不会重复经过表示某个单词的点。转移即枚举下一个字符。

时间复杂度 $\mathcal{O}(|\Sigma| 2 ^ {|\Sigma|} \sum |s_i|)$。注意记录决策点以输出方案。[代码](https://codeforces.com/contest/1739/submission/184452426)。

---

## 作者：water_tomato (赞：0)

Good problem.

## 题意

[题目链接](https://codeforces.com/problemset/problem/1739/F)

Monocarp 词典包含 $n$ 个单词，由 $12$ 个拉丁字母组成。单词编号从 $1$ 到 $n$ 。每个单词中的每一对相邻字符都是不同的。对于每个单词 $i$ ，Monocarp 也有一个整数 $c_i$ ，表示他使用这个单词的频率。

Monocarp 想要设计一个键盘，让他可以轻松地输入其中的一些单词。键盘可以表示为一串由 $12$ 个拉丁字母首字母组成的序列，其中从 a 到 l 每个字母正好出现一次。

如果单词中每一对相邻的字符在键盘中也是相邻的，那么就可以用键盘轻松输入单词。键盘的最优性是 $c_i$ 与所有可以用它轻松输入的单词 $i$ 之和。

请帮助 Monocarp 设计出具有最大优化性的键盘。

$1\le n \le 1000, |s_i| \ge 2, \sum |s_i| \le 2000$.

> Translated by DeepL.

## 题解

把 12 种字符看成 12 个点，对于给出的一个字符串，如果 $u$ 和 $v$ 相邻的，我们就把他们之间连一条边。这样操作后，如果连成的不是一条链，这个字符串的价值就是一定无法获得的。否则，我们把这个链由头到尾连成一个新字符串，我们发现这个字符串或其首尾翻转后的字符串如果是最终键盘的子串，那么我们就可以获得这个价值。容易知道这样的一个字符串不可能和其翻转串存在于同一个排列中，因此我们可以放心地将他们看作两个价值相同的串进行计算。

现在问题转化为，我们有若干个串，每个串有一个价值，我们需要给出一个 $12$ 个字符的，若这个串是这个排列的子串，则我们就能获得价值，求最大价值。

我们把所有字符串塞进 AC 自动机中，然后在 AC 自动机上跑状压 dp。记一个十二位的 $state$ 表示十二种字符是否被使用过，则 $f[state][u]$ 表示当前状态为 $state$，在 AC 自动机上的 $u$ 点的最大价值。

转移是容易的，同时记录以下到达这个答案的 pre 即可完成输出。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int f[5005][5005];
int pre[5005][5005];
int prechar[5005][5005];
struct ACAM{
    struct Trie_Tree{
        int fail,to[26],val;
    }tr[N];
    int tot=0;
    void insert(string s,int k){
        int l=s.length();
        int u=0;
        for(int i=0;i<l;i++){
            if(!tr[u].to[s[i]-'a']){
                tr[u].to[s[i]-'a']=++tot;
            }
            u=tr[u].to[s[i]-'a'];
        }
        tr[u].val+=k;
    }
    void Get_Fail(){
        queue<int> q;
        for(int i=0;i<26;i++)
            if(tr[0].to[i]) q.push(tr[0].to[i]);
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int i=0;i<26;i++){
                if(tr[u].to[i]){
                    tr[tr[u].to[i]].fail=tr[tr[u].fail].to[i];
                    tr[tr[u].to[i]].val+=tr[tr[tr[u].to[i]].fail].val;
                    q.push(tr[u].to[i]);
                }
                else tr[u].to[i]=tr[tr[u].fail].to[i];
            }
        }
    }
    void solve(){
        for(int i=0;i<=tot;i++){
            for(int j=0;j<(1<<12);j++){
                f[i][j]=-1e9;
                pre[i][j]=-1;
            }
        }
        f[0][0]=0;
        for(int state=0;state<(1<<12);state++){
            for(int i=0;i<=tot;i++){
                if(f[i][state]==-1e9) continue;
                for(int j=0;j<12;j++){
                    if(state&(1<<j)) continue;
                    if(f[tr[i].to[j]][state|(1<<j)]<f[i][state]+tr[tr[i].to[j]].val){
                        f[tr[i].to[j]][state|(1<<j)]=f[i][state]+tr[tr[i].to[j]].val;
                        pre[tr[i].to[j]][state|(1<<j)]=i;
                        prechar[tr[i].to[j]][state|(1<<j)]=j;
                    }
                }
            }
        }
    }
}AC;
int n;
string tmp;
bool ok,vis[N];
int path[15][15],du[15];
void dfs(int u,int fa){
    vis[u]=1;tmp+='a'+u-1;
    for(int v=1;v<=12;v++){
        if(path[u][v]==0) continue;
        if(v==fa) continue;
        if(vis[v]){
            ok=0;
            return;
        }
        else dfs(v,u);
    }
}
void output(int x){
    if(x==0) return;
    output(x>>1);
    putchar('0'+x%2);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    scanf("%d",&n);
    for(int i=1,val;i<=n;i++){
        char s[2005];
        scanf("%d %s",&val,s);
        
        for(int i=1;i<=12;i++){
            du[i]=vis[i]=0;
            for(int j=1;j<=12;j++){
                path[i][j]=0;
            }
        }
        tmp="";
        for(int j=0;j<strlen(s)-1;j++){
            path[s[j]-'a'+1][s[j+1]-'a'+1]=1;
            path[s[j+1]-'a'+1][s[j]-'a'+1]=1;
        }
        for(int i=1;i<=12;i++){
            for(int j=1;j<=12;j++){
                if(path[i][j]) du[i]++;
            }
        }
        ok=1;
        for(int j=1;j<=12;j++){
            if(du[j]>=3){
                ok=0;
                break;
            }
        }
        if(!ok) continue;

        for(int j=1;j<=12;j++){
            if(du[j]==1){
                dfs(j,j);break;
            }
        }
        for(int j=1;j<=12;j++){
            if(du[j]!=0 && !vis[j]) ok=0;
        }
        if(!ok) continue;
        AC.insert(tmp,val);
        reverse(tmp.begin(),tmp.end());
        AC.insert(tmp,val);
    }
    AC.Get_Fail();
    AC.solve();
    int ans=0,ansid=0;
    for(int i=0;i<=AC.tot;i++){
        if(f[i][(1<<12)-1]>ans){
            ans=f[i][(1<<12)-1];
            ansid=i;
        }
    }
    string ansString;
    int nowstate=(1<<12)-1;
    while(nowstate){
        if(pre[ansid][nowstate]==-1) break;
        char ch=prechar[ansid][nowstate]+'a';
        ansString+=ch;
        ansid=pre[ansid][nowstate];
        nowstate^=(1<<(ch-'a'));
    }
    cout<<ansString<<endl;
    return 0;
}
```

---

