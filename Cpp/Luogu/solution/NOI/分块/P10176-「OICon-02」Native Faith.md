# 「OICon-02」Native Faith

## 题目描述

本题字符串下标从 $1$ 开始。  

定义两个字符串相加的结果为将这两个字符串首尾拼接形成的新字符串。

令 $f(a,b,c)=\sum\limits_{i=1}^{|a|}\sum\limits_{j=i}^{|a|}\sum\limits_{k=1}^{|b|}\sum\limits_{l=k}^{|b|}[a_{i,i+1,\cdots,j}+b_{k,k+1,\cdots,l} = c]$（$a,b,c$ 均为字符串）。

即有多少种方式从 $a,b$ 中分别选出一个非空子串使两个子串的和为 $c$。

给定 $n$ 个字符串 $s_1,s_2,s_3,\cdots,s_n$。

有 $q$ 次询问，每次询问给出三个正整数 $l,r,k$，求 $\sum\limits_{i=l}^r\sum\limits_{j=l}^rf(s_i,s_j,s_k)$。

## 说明/提示

### 样例解释

对于样例 $1$，给出部分 $f$ 函数的值。
- $f(s_1,s_1,s_3)=0$，$f(s_1,s_2,s_3)=1$，$f(s_1,s_3,s_3)=2$，$f(s_2,s_1,s_3)=1$，$f(s_2,s_2,s_3)=4$，$f(s_2,s_3,s_3)=7$，$f(s_3,s_1,s_3)=2$，$f(s_3,s_2,s_3)=7$，$f(s_3,s_3,s_3)=12$。

### 数据范围

**本题采用捆绑测试。**

令 $m=\sum|s_i|$。

| $\text{Subtask}$ | 特殊性质 | $\text{Score}$ | 
| :-----------: | :-----------: | :-----------: |
| $1$ | $1\le n,m,q\le 3\times 10^3$ | $17$ |
| $2$ | 保证每次询问的 $k$ 各不相同 | $23$ | 
| $3$ | $1\le n,m,q\le 3\times 10^4$ | $27$ |
| $4$ | 字符串只包含小写字母 $\texttt{a}$ | $19$ |
| $5$ | 无特殊限制 | $14$ |

对于 $100\%$ 的数据：$1\le n,m,q\le 10^5$，$1\le l \le r\le n$，$1\le k\le n$，字符串仅包含小写字母。

## 样例 #1

### 输入

```
3 3
a
aa
aaa
1 2 3
2 3 3
1 3 3```

### 输出

```
6
30
36```

## 样例 #2

### 输入

```
10 10
aabb
aba
abbba
abaccaab
abbba
ababababab
aaaaa
bbbbbb
aaba
abbba
1 10 10
1 4 5
3 6 4
2 8 1
1 5 4
2 10 7
2 9 2
4 5 5
5 5 6
8 9 10```

### 输出

```
241
31
51
105
40
136
460
17
0
0```

## 样例 #3

### 输入

```
5 5
a
ba
aba
ababa
abab
1 3 3
1 2 3
2 3 3
4 4 5
3 4 4```

### 输出

```
12
2
9
11
28```

# 题解

## 作者：fjy666 (赞：5)

考虑根号分治，设阈值为 $B$。

### Case 1. $|s|\le B$

对于一个询问 $(l,r,k)$，记录 $f_i$ 为 $\operatorname{prefix}(s_k,i)$ 在 $a_l\sim a_r$ 中的出现次数，$g_i$ 为 $\operatorname{suffix}(s_k,i)$ 在 $a_l\sim a_r$ 的出现次数，则

$$ans=\sum\limits_{i=1}^{|s_k|-1}f_i g_{i+1}$$

差分一下，变成前缀对串的贡献。我们可以建立 AC 自动机，单点加子树求和。

可以用 $\mathcal{O}(\sqrt{m})-\mathcal{O}(1)$ 的分块根号平衡复杂度。

总时间复杂度为 $\mathcal{O}(qB+m\sqrt{m})$。

### Case 2. $|s|>B$

这个长度不允许我们对于单组询问解决时间复杂度带 $|s|$。   

#### Solution 1

设 $s_k=a+b$，当 $|a|\le B$ 或 $|b|\le B$ 的时候可以像 Case 1 一样做。

当 $|a|>B$ 且 $|b|>B$ 时，它们所对应的字符串只有 $\mathcal{O}(\frac{m}{B})$ 种。

那么本质不同询问左端点 $l$ 也只有 $\mathcal{O}(\frac{m}{B})$。

直接暴力计算每种本质不同询问的答案，复杂度是 $\mathcal{O}(\frac{m^3}{B^2})$。

取 $B=n^{2/3}$ 得到最优复杂度 $\mathcal{O}(n^{5/3})$。

#### Solution 2

长度 $>B$ 的字符串共 $\mathcal{O}(\frac{m}{B})$ 个。对于一个 $k$，我们预处理出 $cnt_{i,j}$ 表示 $\operatorname{prefix}(s_k,j)$ 在 $s_i$ 中的出现次数。（后缀同理）

这一部分可以提前给每个串建立后缀自动机做到。

$cnt_i$ 的长度为 $\min(|s_i|,|s_k|)$，所以 $cnt$ 的总长是 $\mathcal{O}(n)$ 级别的。

对于询问，使用**莫队**来解决。正确排序的莫队复杂度为 $\mathcal{O}(n\sqrt{q})$。

总复杂度相当于

$A_1+A_2+\cdots A_{\frac{m}{B}}=q,\max\{\sum \sqrt{A_i}\}$。

视 $q,m$ 同阶，可以证明 $A_i$ 取 $B$ 时最优，复杂度为 $\mathcal{O}(\frac{mn}{B}\sqrt{B})$。

取 $B=n^{2/3}$ 得到最优复杂度 $\mathcal{O}(n^{5/3})$。

---

## 作者：Nt_Tsumiki (赞：3)

实至名归的重工业。

以下对于贡献只讨论正串（即前缀）后缀是同理的。

首先答案是每一位的前缀在 $[l,r]$ 内的匹配数与后缀的匹配数的乘积。

然后朴素的阈值分治一下，设阈值为 $B$。

对于 $|s_i|\le B$ 的是简单的，我们对所有 $s$ 建 ACAM，那么贡献就是一个单点加子树求和的形式，转化为 dfn 序列后使用 $O(\sqrt{m})-O(1)$ 分块可以做到 $O(nB+n\sqrt{m})$。

然后对于 $|s_i|>B$ 的部分，我们不希望复杂度与 $|s_i|$ 相关，我这里采用的官解的第二种做法，对于每个 $|s_i|>B$ 的 $i$ 求出 $cnt_{j,k}$ 表示 $\text{prefix}(s_i,j)$ 在 $s_k$ 中的匹配次数，可以通过对每个串建 SAM 求得，因为 $O(\sum \min\{|s_i|,|s_k|\})=O(m)$，这部分的复杂度是可以接受的，然后对于询问我们使用莫队去做就行，正确的莫队复杂度 $O(m\sqrt{q})$，默认 $m,q$ 同阶的话这部分的总复杂度为 $O(\sum _{i=1}^{\frac{m}{B}}m\sqrt{q_i}+q\log q)=O(\frac{m^2}{B}\sqrt{B}+m\log m)$。

默认 $n,m$ 同阶时在 $B=n^{\frac{2}{3}}$ 时最优为 $O(n^{\frac{5}{3}})$。

关于 正确的莫队 的写法，因为本题你加一个点的复杂度是 $O(\min\{|s_i|,|s_k|\})$ 的，所以你进行分块排序的时候应该带上这个权去分，这样就是对的。

[submission](https://www.luogu.com.cn/record/198585441)

---

## 作者：Zaunese (赞：2)

有代码的题解。

主要说明 fjy666 的第一种做法。省选场上能写出第二种做法（代码 7KB 以上）的都是这个👍👍👍。

由 $n,m,q\le10^5$，时限 3s，数据范围里有 $\sum|s_i|$，鉴定为：根号分治。

那么，依据串长度和 $B$ 的大小关系，分为大串和小串。

***

考虑一个暴力。记询问为 $(l,r,k)$，枚举 $s_k$ 被分割出的前缀长度 $i$，此时的方案数是：$s_k$ 的长为 $i$ 的前缀在 $s_l,s_{l+1},\dots,s_r$ 中的**出现次数和** $f_i$，与 $s_k$ 的长为 $|s_k|-i$ 的后缀在 $s_l,s_{l+1},\dots,s_r$ 中的**出现次数和** $g_i$ 的积，即此询问答案为

$$\sum_{i=1}^{|s_k|-1}f_ig_i$$

求这个出现次数显然使用 AC 自动机。

但是这里，模板串是 $s_k$ 的所有前缀、后缀，故想到先对所有 $s_k$ 的所有**前缀**构建 AC 自动机，对所有 $s_k$ 的所有**后缀**再构建一个 AC 自动机。

然后扫描线，询问差分一下，拆成 $(l-1,k)$ 和 $(r,k)$，变成前缀 $s_1,s_2,\dots,s_i$ 查询某模板串的出现次数和。

依次加入字符串，即在两个自动机上分别跑一遍，然后查询出现次数和显然是 Fail 树的某棵子树的点权和。**即单点加子树求和。**

此时发现枚举分割的复杂度已经有 $O\left(\sum|s_k|\right)$ 了，能解决 $|s_k|\le B$ 的问题。子树求和有 $O(qB)$ 次，单点加有 $O(m)$ 次（即在自动机上跑一遍），用 $O\left(\sqrt m\right)$ 的单点加、$O(1)$ 的区间求和的分块来平衡，时间复杂度 $O\left(qB+m\sqrt m\right)$。

***

然后解决 $|s_k|> B$ 的问题。

考虑小串对大串的贡献。注意到能产生贡献当且仅当分割出的前缀长度 $i\le B$ 或 $i\ge|s_k|-B$。枚举这一范围的 $i$ 也只要 $O(B)$ 的时间复杂度，继续使用上面的暴力即可。

接下来只要关心 $i> B$ 且 $i<|s_k|-B$ 的情况，显然只有大串能贡献。

由于大串只有 $O\left(\frac mB\right)$ 个，枚举分割后只需回答 $O\left(\left(\frac mB\right)^2\right)$ 个本质不同的问题，时间复杂度是 $O\left(\frac{m^3}{B^2}\right)$。

具体地，沿用上述的扫描线，求每个大串 $s_i$ 的每个前缀、后缀在每个大串序列前缀 $s_1,s_2,\dots,s_j$ 的出现次数和。这个部分的时间复杂度是 $O\left(m\sqrt m+m\times\frac mB\right)$。

回答询问的时候直接对 $O\left(\left(\frac mB\right)^3\right)$ 个本质不同的询问记忆化即可。

***

两部分复杂度分别是 $O(qB)$ 和 $O\left(\frac{m^3}{B^2}\right)$，若 $n,m,q$ 同阶则平衡得到 $B=n^{2/3}$，总时间复杂度 $O(n^{5/3})$。

空间复杂度是 $O\left(qB+\frac{m^2}B+\left(\frac mB\right)^3\right)$。块长取到 $500$，大一点会 MLE。

***

代码参考了 <https://www.luogu.com.cn/record/187393706>，在此表示感谢！

```cpp
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<string>

#define fi first
#define se second
#define mkp std::make_pair
using llu=long long unsigned;
using ll=long long;
using std::max;
using std::min;
template<class T> void cmax(T&a,T b){a=max(a,b);}
template<class T> void cmin(T&a,T b){a=min(a,b);}

const int NV=1e5,B=500; //2100 -> 500

int M;

namespace bar{
    int bel[NV+5],L[NV+5],R[NV+5];
    void init(){
        for(int i=1;i<=M;++i){
            bel[i]=(i-1)/B+1;
            if(!L[bel[i]]) L[bel[i]]=i;
            R[bel[i]]=i;
        }
    }
}

struct ac{
    struct ACN{
        int g[26],f,p;
    } tr[NV+5];
    int cnt;
    void ins(const char*sz){
        int p=0;
        for(int i=0;sz[i];++i){
            const int c=sz[i]-'a';
            if(!tr[p].g[c]) tr[tr[p].g[c]=++cnt].p=p;
            p=tr[p].g[c];
        }
    }
    struct EDGE{
        int t,n;
    } G[NV+5];
    int ecnt=2,hd[NV+5],dfc,dfn[NV+5],dfr[NV+5];
    void ade(int s,int t){
        G[ecnt]={t,hd[s]};
        hd[s]=ecnt++;
    }
    void dfs(int x){
        dfn[x]=++dfc;
        for(int e=hd[x];e;e=G[e].n) dfs(G[e].t);
        dfr[x]=dfc;
    }void build(){
        std::queue<int> q;
        for(int i=0;i<26;++i) if(tr[0].g[i]) q.push(tr[0].g[i]);
        while(q.size()){
            int u=q.front();
            q.pop();
            for(int i=0;i<26;++i)
                if(tr[u].g[i]){
                    tr[tr[u].g[i]].f=tr[tr[u].f].g[i];
                    q.push(tr[u].g[i]);
                }else tr[u].g[i]=tr[tr[u].f].g[i];
        }
        for(int i=1;i<=cnt;++i) ade(tr[i].f,i);
        dfc=0;
        dfs(0);
    }
    int bis[NV+5],bgs[NV+5];
    void add(int p,int z){ // point add
        for(int i=p;i<=bar::R[bar::bel[p]];++i) bis[i]+=z;
        for(int i=bar::bel[p];i<=bar::bel[M];++i) bgs[i]+=z;
    }int que(int p){ // prefix sum
        return p?bis[p]+bgs[bar::bel[p]-1]:0;
    }int que(int l,int r){
        return que(r)-que(l-1);
    }void tour(const char*sz){
        int p=0;
        for(int i=0;sz[i];++i){
            p=tr[p].g[sz[i]-'a'];
            add(dfn[p],1);
        }
    }void clr(){
        memset(tr,0,sizeof*tr*(cnt+1));
        ecnt=2;
        memset(hd,0,sizeof*hd*(cnt+1));
        memset(bis,0,sizeof bis);
        memset(bgs,0,sizeof bgs);
        cnt=0;
    }auto que(const char*s,bool op=0){
        std::vector<int> ans;
		int mxn=!op?B-1:1<<30,p=0;
		for(int i=0;i<=mxn&&s[i];++i){
			p=tr[p].g[s[i]-'a'];
			ans.push_back(que(dfn[p],dfr[p]));
		}
        return ans;
	}
} pac,sac;

namespace xm{
    std::string s[NV+5],rs[NV+5];
    std::vector<int> swq[NV+5],pinfo[NV+5],sinfo[NV+5],npi[205][205],nsi[205][205];
    std::pair<int,int> quer[NV+5];
    ll mem[205][205][205];
    int quek[NV+5],bid[NV+5],bli[NV+5],nxt[205][205][205];
    char buf[NV+5];
    void _(){
        int N,Q;

        scanf("%d%d",&N,&Q);
        for(int i=1;i<=N;++i){
            scanf("%s",buf);
            rs[i]=s[i]=buf;
            std::reverse(rs[i].begin(),rs[i].end());
            M+=s[i].size();
        }
        bar::init();
        for(int i=1;i<=Q;++i){
            int l,r;
            scanf("%d%d%d",&l,&r,&quek[i]);
            quer[i]={l,r};
            swq[l-1].push_back(-i);
            swq[r].push_back(i);
        }

        for(int i=1;i<=N;++i){
            pac.ins(s[i].c_str());
            sac.ins(rs[i].c_str());
        }
        pac.build();
        sac.build();
        for(int i=0;i<=N;++i){
            if(i){
                pac.tour(s[i].c_str());
                sac.tour(rs[i].c_str());
            }
            for(int qi:swq[i]){
                const int sgn=qi>0?1:-1;
                qi=std::abs(qi);
                const int u=quek[qi];
                if(sgn<0){
                    pinfo[qi]=pac.que(s[u].c_str());
                    sinfo[qi]=sac.que(rs[u].c_str());
                }else{
                    auto ret=pac.que(s[u].c_str());
                    for(int i=0;i<ret.size();++i) pinfo[qi][i]=ret[i]-pinfo[qi][i];
                    ret=sac.que(rs[u].c_str());
                    for(int i=0;i<ret.size();++i) sinfo[qi][i]=ret[i]-sinfo[qi][i];
                }
            }
        }

        pac.clr();
        sac.clr();
        for(int i=1;i<=N;++i) if(s[i].size()>B){
            bli[bid[i]=++*bli]=i;
            pac.ins(s[i].c_str());
            sac.ins(rs[i].c_str());
        }
        pac.build();
        sac.build();
        for(int i=1;i<=*bli;++i){
            pac.tour(s[bli[i]].c_str());
            sac.tour(rs[bli[i]].c_str());
            for(int j=1;j<=*bli;++j){
                npi[i][j]=pac.que(s[bli[j]].c_str(),1);
                nsi[i][j]=sac.que(rs[bli[j]].c_str(),1);
            }
        }
        for(int j=1;j<=*bli;++j){
            npi[0][j].resize(M);
            nsi[0][j].resize(M);
        }

        for(int i=1;i<=Q;++i) if(s[quek[i]].size()>B){
            ll ans=0;
            int l=0,r=0,sle=s[quek[i]].size(),sid=bid[quek[i]];
			for(int j=1;j<=*bli;++j){
				if(bli[j]<quer[i].fi) l=j;
				if(bli[j]<=quer[i].se) r=j;
			}
            for(int j=0;j<sle-1;++j){
				if(j>=(int)pinfo[i].size()&&(int)sinfo[i].size()<=sle-j-2){
					if(mem[l][r][sid]){
						ans+=mem[l][r][sid];
						j=nxt[l][r][sid];
					}else{
						for(;j>=(int)pinfo[i].size()&&(int)sinfo[i].size()<=sle-j-2;++j){
							const int pv=npi[r][sid][j]-npi[l][sid][j];
							const int sv=nsi[r][sid][sle-j-2]-nsi[l][sid][sle-j-2];
							mem[l][r][sid]+=(ll)pv*sv;
						}
                        --j;
						nxt[l][r][sid]=j;
						ans+=mem[l][r][sid];
					}
					continue;
				}
                int pv,sv;
                if(j>=(int)pinfo[i].size()) pv=npi[r][sid][j]-npi[l][sid][j];
                else pv=pinfo[i][j];
                if((int)sinfo[i].size()<=sle-j-2)
                    sv=nsi[r][sid][sle-j-2]-nsi[l][sid][sle-j-2];
                else sv=sinfo[i][sle-j-2];
                ans+=(ll)pv*sv;
            }

            printf("%lld\n",ans);
        }else{
            int le=pinfo[i].size();
            ll ans=0;
            for(int j=0;j<le-1;++j)
                ans+=(ll)pinfo[i][j]*sinfo[i][le-j-2];
            printf("%lld\n",ans);
        }
    }
}

int main(){
    xm::_();
    return 0;
}
```

---

