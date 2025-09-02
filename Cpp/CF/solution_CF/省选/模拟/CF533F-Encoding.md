# Encoding

## 题目描述

坡旅甲发明了一种新的字符串编码方法．  
具体来说，我们可以取若干对不相交的小写字母对(每个小写字母至多出现一次),然后对于一个由小写字母组成的字符串 $T$ ，我们将 $T$ 中出现在选中字母对中的字母替换为这个字母对中的另一个字母．

举个例子：我们选中了三对字母 $(l,r)$ , $(p,q)$ 和 $(a,o)$ ，那么，"parallelogram" 将会变为 "qolorreraglom"  

现在，坡旅甲已经有了两个字符串 $S$ 和 $T$ ．他惊讶地发现，$S$ 的许多子串竟然可以通过他所发明的新编码方法得到 $T$．于是坡旅甲想知道，$S$ 中有多少个子串可以用如上所描述的字符串编码方法编码得到 $T$

## 说明/提示

$n,m\le2\times10^5$

## 样例 #1

### 输入

```
11 5
abacabadaba
acaba
```

### 输出

```
3
1 3 7
```

## 样例 #2

### 输入

```
21 13
paraparallelogramgram
qolorreraglom
```

### 输出

```
1
5
```

# 题解

## 作者：ailanxier (赞：5)

## 提示1：

&emsp;&emsp;$\mathcal O(26^2*n)$ 的算法可通过。常用的几种字符串匹配算法kmp，AC自动机，哈希都可以解决该问题 （后两者可以优化到 $\mathcal O(26*n)$ ）。

## 提示2：

&emsp;&emsp;将文本串 $S$ 和模式串 $T$ 中的 $26$ 个字母分开考虑，各自匹配。

## $\mathcal O(26^2*n)$ 的kmp匹配

&emsp;&emsp;枚举每一种转换，记为 $(x,y),x,y\in\{'a','b',\cdots,'z'\}$，$x$ 可以等于 $y$ ，即不转换。如果该转换在某区间 $S[l,r]$ 是与 $T$ 匹配的，则说明在 $S[l,r]$ 中每个 $x$ 位置和 $T$ 中 $y$ 位置一一对应，每个 $y$ 位置和 $T$ 中 $x$ 位置一一对应，而且不会有另一个关于 $x$ 的转换使得该区间匹配。 若对于 $S[l,r]$ 段上 $x$ 的任何一种转换都不能与 $T$ 匹配，则说明该段无法匹配；否则在该区间起点打标记，表示该转换匹配成功。**对于 $T$ 任何一个字符 $x$ 都需要有转换在 $S[l,r]$ 中匹配，才说明 $S[l,r]$ 是与 $T$ 匹配的**。

&emsp;&emsp;具体实现时令 $T$ 中 $x,y$ 互换，其他位置替换为 $0$，$S$ 中除 $x,y$ 以外的位置置为 0，其它保持不变，这样可以用kmp判断转换 $(x,y)$ 是否与 $S$ 上某一段匹配。例如：

|      | 原字符串 | 转换 $(b,c)$ ,变成只含 $0,b,c$ 的序列（只在 $T$ 转换 $(b,c)$） |
| :--: | :------: | :----------------------------------------------------------: |
| $S$  | $abcab$  |                         $0~b~c~0~b$                          |
| $T$  | $acbac$  |                         $0~b~c~0~b$                          |

&emsp;&emsp;这里 $a,b,c$ 都能找到转换与 $S$ 匹配（$a$ 不转换就可以匹配），而对于 $S,T$ 都没出现的字母，任意转换都是匹配的，即会把两个序列都变成全 $0$ ，肯定是匹配的。

### $Code:$

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int sl,tl,nxt[N],ss[N],tt[N];
bool p[N][27];//p[i][j]标记S[i,i+tl-1]这段上是否有关于x的转换使得与T串匹配
char s[N],t[N];
vector<int>ans;

int main() {
    scanf("%d %d %s %s",&sl,&tl,s+1,t+1);
    for(int x = 'a'; x <= 'z'; x++){
        for(int y = x; y <= 'z'; y++){
            //t中x，y互换
            for(int i = 1;i <= tl;i++) {
                if(t[i] == x) tt[i] = y;
                else if(t[i] == y) tt[i] = x;
                else tt[i] = 0;
            }
            for(int i = 1; i <= sl; i++) ss[i] = ( (s[i] == y)||(s[i] == x) )? s[i] : 0;

            //kmp匹配
            for(int i = 2,j = 0; i <= tl; i++){
                while(j && tt[i] != tt[j + 1]) j = nxt[j];
                if(tt[i] == tt[j + 1]) nxt[i] = ++j;
                else nxt[i] = 0;
            }
            for(int i = 1,j = 0; i <= sl; i++){
                while(j && ss[i] != tt[j + 1]) j = nxt[j];
                if(ss[i] == tt[j + 1]) ++j;
                if(j == tl) {
                    p[i-tl+1][x-'a'] = 1;
                    p[i-tl+1][y-'a'] = 1;
                    j = nxt[j];
                }
            }
        }
    }
    //O(26*n) 的判断：S[i,i+tl-1]是否可以和转换后的T匹配,要满足t的每个字符j都有转换与S[i,i+tl-1]匹配
    for(int i = 1;i <= sl-tl+1;i++) {
        int flag = 1;
        for(int j = 0;j < 26;j++) if(!p[i][j]) { flag = 0;break;}
        if(flag) ans.push_back(i);
    }
    printf("%d\n",ans.size());
    for(auto it : ans) printf("%d ",it);
    return 0;
}
```

## $\mathcal O(26*n)$ 的哈希匹配

&emsp;&emsp;在kmp匹配结束后，有一个 $\mathcal O(26*n)$ 的判断循环，因为在kmp中已经求出 $p_{i,j}$ 的值了，所以对于每个 $i$ ,有 $26$ 次 $\mathcal O(1)$ 的判断 。我们考虑，哈希也可以 $\mathcal O(1)$ 的判断两个串是否匹配，这里只要将 $26$ 个字母分别求哈希值再求和匹配就可以了，所以哈希是可以将整体复杂度优化到 $\mathcal O(26*n)$ 的。

&emsp;&emsp;具体实现时需要求出一个特殊的数组，我们记为 $nxt_{i,j}$ ，表示 $S[i,|s|]$ 上第一次出现字符 $j$ 的下标。这样在我们判断 $S[i,i+|t|-1]$ 这段区间是否可以通过转换 $j$ 使得与 $T$ 匹配时，我们先通过 $nxt_{i,j}$ 获得 $j$ 下标，如果它在 $[i,i+|t|-1]$ 这个区间上，说明它在 $T$ 串对应位置有一个字符 $y$ 需要与它匹配，如果我们把 $[i,i+|t|-1]$ 上的 $j$ 全部替换为 $y$ ，其他字符置为 $0$ 。对所有的 $26$ 个字符都这样处理，他们分别计算的哈希值加起来与 $T$ 的哈希值比较，就可以知道 $S[i,i+|t|-1]$ 是否可以和 $T$ 匹配了。这样对于每个 $i$ 的 $26$ 次计算都是 $\mathcal O(1)$ 的。**注意对于同一区间上的字符转换不能有交集，即两个关于 $x$ 的转换 $(x,y),(x,z),y\not=z$ 不能同时存在，代码中用 $vis$ 记录每个字符的转换对象，每个字符的 $vis_j$ 只能被赋值一次**。~~因为比较懒没写双哈希~~。

### $Code:$

```c++
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
const int base = 131;
const int mod = 19260817;
int sl,tl,nxt[N][26];
ll T_hash,s_hash[N][26],fac[N];
int vis[27];
vector<int>ans;
char s[N],t[N];

int main() {
    scanf("%d %d %s %s",&sl,&tl,s+1,t+1);
    fac[0] = 1;
    for(int i = 1;i <= sl;i++) fac[i] = fac[i-1] * base % mod;

    //预处理出nxt数组，记录i后第一个字符j的下标
    for(int j = 0;j < 26;j++) nxt[sl+1][j] = sl+1;
    for(int i = sl;i >= 1;i--)
        for(int j = 0;j < 26;j++){
            if(s[i] == j+'a') nxt[i][j] = i;
            else nxt[i][j] = nxt[i+1][j];
        }

    //求出T串hash值
    for(int i = 1;i <= tl;i++) T_hash = (T_hash * base + (t[i]-'a') ) % mod;

    //求出S串26个字符分开计算的hash值，注意这里是将为j的字符置为1，其他置为0作哈希，之后有（j,y)的转换乘上y即可（哈希满足乘法分配律）
    for(int i = 1;i <= sl;i++)
        for(int j = 0;j < 26;j++){
            if(s[i] == j+'a') s_hash[i][j] = (s_hash[i-1][j] * base + 1) % mod;
            else s_hash[i][j] = s_hash[i-1][j] * base % mod;
        }

    for(int i = 1;i <= sl-tl+1;i++) {
        ll tot_hash = 0;
        memset(vis,-1,sizeof vis); //-1表示未被赋值过
        for(int j = 0;j < 26;j++){
            int p = nxt[i][j];
            if(p > i + tl - 1) continue;
            int y = t[p-i+1]-'a';     //找到在T串对应位置的字符

            //只有之前x,y都没有被转换过才能赋值
            if(vis[j] == -1 && vis[y] == -1) vis[y] = j,vis[j] = y;
            tot_hash = (tot_hash + vis[j] * ((s_hash[i+tl-1][j] - s_hash[i-1][j] * fac[tl]) % mod + mod) ) % mod;
        }
        if(tot_hash == T_hash) ans.push_back(i);
    }
    printf("%d\n",ans.size());
    for(auto it :ans) printf("%d ",it);
    return 0;
}
```

## $\mathcal O(26*n)$ 的AC自动机匹配

&emsp;&emsp;思路来自 [【题解】Codeforces533F. Encoding 按字符分解，AC自动机](https://blog.csdn.net/m0_37809890/article/details/103193420?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522161552983416780262513134%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=161552983416780262513134&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-1-103193420.pc_search_result_no_baidu_js&utm_term=+Encoding%E9%A2%98%E8%A7%A3) 。其实与哈希匹配思想是一致的，都是想要找到一种方式可以做到对于每个起点 $i$ ，进行 $26$ 次复杂度只有 $\mathcal O(1)$ 的判断。我们把 $T$ 串分成 $26$ 个 $01$ 串（不计入全 $0$ 串），构建AC自动机。再将 $S$ 串分成 $26$ 个 $01$ 串，在AC自动机上作匹配，每次匹配到一个 $T$ 串末尾，就在该位置标记匹配的字符，对于某个 $i$ ,要求 $T$ 中 $26$ 个字符 $j$ 都能被匹配到末尾（除 $j$ 全 $0$ 串外），才说明该段和 $T$ 匹配。例如：

|      | 原字符串 | $a$ 的 $01$ 串 | $b$ 的 $01$ 串 | $c$ 的 $01$ 串 |
| :--: | :------: | :------------: | :------------: | :------------: |
| $S$  | $abcab$  |  $1~0~0~1~0$   |  $0~1~0~0~1$   |  $0~0~1~0~0$   |
| $T$  | $acbac$  |  $1~0~0~1~0$   |  $0~0~1~0~0$   |  $0~1~0~0~1$   |

&emsp;&emsp;这里 $S$ 的 $a$ 串会匹配到AC自动机上对应 $T$ 的 $a$ 串末端， $S$ 的 $b$ 串会匹配到AC自动机上对应 $T$ 的 $c$ 串末端， $c$ 串会匹配到AC自动机上对应 $T$ 的 $b$ 串末端，其他全为 $0$ 的串不插入AC自动机，所以 $S$ 和 $T$ 是匹配的。

  AC自动机构建复杂度是 $\mathcal O (26*n)$ 的，匹配时无需暴力跳fail，对于 $26$ 个串的匹配也是 $\mathcal O (26*n)$ 。

### $Code:$

```c++
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int sl,tl,tt[N],en[N*26], match[27];
bool has[27];
char s[N],t[N];
vector<int>ans;
int trie[N*26][2],cnt,fail[N*26],now[26];

void insert(int o){
    int now = 0;
    for (int i = 1,c; i <= tl;i++){
        c = tt[i];
        if(trie[now][c] == 0) trie[now][c] = ++cnt;
        now = trie[now][c];
    }
    en[now] = o;
}

void build(){
    queue<int> q;
    for (int i = 0; i < 2;i++) if(trie[0][i]) q.push(trie[0][i]);
    while(!q.empty()){
        int now = q.front();q.pop();
        for (int i = 0; i < 2;i++){
            if(trie[now][i]){
                q.push(trie[now][i]);
                fail[trie[now][i]] = trie[fail[now]][i];
            }else
                trie[now][i] = trie[fail[now]][i];
        }
    }
}

int main() {
    scanf("%d %d %s %s",&sl,&tl,s+1,t+1);
    memset(en,-1,sizeof en);
    for(int j = 0;j < 26;j++){
        for(int i = 1; i <= tl; i++)
            has[j] |= tt[i] = (t[i] == j + 'a');
        if(has[j]) insert(j); //不是全0串才插入AC自动机
    }
    build();
    for(int i = 1;i <= sl;i++){
        int flag = 0;
        memset(match,-1,sizeof match);
        for(int j = 0;j < 26;j++){
            int c = s[i]-'a';
            now[j] = trie[now[j]][c == j];
            if(en[now[j]] != -1) match[en[now[j]]] = j;//记录T末端字符en[now[j]]匹配到S的字符j
        }
        for(int j = 0;j < 26;j++)
            if(has[j]){
                if(match[j] == -1) {flag = 1;break;}
                int y = match[j];
                //在T串同时含j,y的情况下，match[j]=y,match[y]=j才满足变换后匹配
                if(match[y] != j && has[y]) {flag = 1;break;}  
            }
        if(!flag) ans.push_back(i-tl+1);
    }
    printf("%d\n",ans.size());
    for(auto it : ans) printf("%d ",it);
    return 0;
}
```

&emsp;&emsp;这道题可以用多种算法尝试解决，是一道很全面的题目。各算法运行结果如下（空间换时间了）：

![](https://cdn.luogu.com.cn/upload/image_hosting/ioyj0ce4.png)



---

## 作者：冒泡ioa (赞：3)

> [博客链接](http://bubbleioa.top/archives/801)

## 题解
哈希真的是个好东西,在O(N)预处理之后,能在O(1)的时间内枚举任意子串.  
这道题我们可以考虑对每种字母进行哈希.  
具体来讲,hash1[i][c]存储的是字母c的哈希值(位置)

这样处理之后,就在S串里面枚举长度为T串的子串,再枚举两种字母,如果26个字母哈希值能够相等,那么这样的变化是没问题的

时间复杂度 $O(N\times 26\times 26)$

这里进制为131,模数为 $2^{64}$
## 代码
```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll p=131;
const int N=210000;
int n,m;
char sr1[N],sr2[N];
unsigned long long hash1[N][28],hash2[N][28],Q[N];
int Ans[N],ans;

int main(){
    int i,j,k,x,y;
    cin>>n>>m;
    scanf("%s%s",sr1+1,sr2+1);
    Q[0]=1;
    for(i=1;i<=n;++i)
        Q[i]=Q[i-1]*p;
    for(j=0;j<=25;++j)
        for(i=1;i<=n;++i){
            hash1[i][j]=hash1[i-1][j]*p;
            if(sr1[i]-'a'==j)hash1[i][j]+=1;
        }
    for(j=0;j<=25;++j)
        for(i=1;i<=m;++i){
            hash2[i][j]=hash2[i-1][j]*p;
            if(sr2[i]-'a'==j)hash2[i][j]+=1;
        }
    int cnt;
    for(i=1;i<=n-m+1;++i){
        cnt=0;
        for(x=0;x<26;++x){
            if(cnt!=x)break;
            for(y=0;y<26;++y)
                if(hash2[m][x]==hash1[i+m-1][y]-hash1[i-1][y]*Q[m])
                    if(hash2[m][y]==hash1[i+m-1][x]-hash1[i-1][x]*Q[m]){
                        cnt++;
                        break;
                    }
        }
        if(cnt==26) Ans[++ans]=i;
    }
    cout<<ans<<endl;
    for(i=1;i<ans;++i)printf("%d ",Ans[i]);
    if(ans!=0)printf("%d",Ans[ans]);
}

```

---

## 作者：周小涵 (赞：3)

一个不同于其他题解的做法。

首先设 $pre_i$ 表示 $i$ 这个位置上一个和它相等字符的位置与它的相隔距离，特别的，如果前面没有相同的字符，把 $0$ 位置看成上一个字符，对于两个长度相等的字符串 $S$ 和 $T$，如果它们的 $pre$ 数组完全一致，那么至少 $S$ 中出现的每个字母对应到 $T$ 中也是完全相等的，但满足这个条并不代表合法，可此时我们可以 $O(|\Sigma|)$ 暴力枚举每个小写字母匹配即可。

但由于我们要对于 $S$ 中每个长度为 $|T|$ 的子串判断，所以不能直接暴力，我们考虑将 $pre$ 数组哈希，即可做到 $O(1)$ 判断，我们考虑一个长度为 $|T|$ 的窗口从 $S$ 开头向后移动，我们要做的就是删除开头的 $pre_l$ 和加上结尾的 $pre_{r+1}$ ，并且对于某个字符在这个区间出现的第一个位置 $p$，我们要把所有的 $pre_p$ 减 $1$ ，我们可以通过记一个指针，或者直接二分去找到每个 $p$。我们通过上述方法更新哈希值，如果 $S[l,l+|T|-1]$ 的哈希值和 $T$ 的哈希值相等，再暴力进行匹配检查可行性即可。

时间复杂度 $O(|\Sigma| n\log n)$。

顺便一提，程序里的常数 $inv=2263404180823257867$ 表示的是 $B=163$ 在模 $2^{64}$ 意义下的逆元，删最前面的 $pre_l$ 时要用到。

代码：
```cpp
#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int N=2e5+5;
const ull B=163,inv=2263404180823257867;
int n,m,prs[N],prt[N],mp[30];
char s[N],t[N];
ull sums,sumt,pw[N];
vector<int>ans,G[30];
bool check(int x){
    if(sums!=sumt)return 0;
    memset(mp,-1,sizeof(mp));
    for(int i=0;i<26;i++){
        int pos=*lower_bound(G[i].begin(),G[i].end(),x);
        if(pos>x+m-1)continue;
        if(mp[t[pos-x+1]-'a']!=-1&&mp[t[pos-x+1]-'a']!=i)return 0;
        if(mp[i]!=-1&&mp[i]!=t[pos-x+1]-'a')return 0;
        mp[i]=t[pos-x+1]-'a';
        if(mp[mp[i]]==-1)mp[mp[i]]=i;
        else if(mp[mp[i]]!=i)return 0;
    }
    return 1;
}
int main(){
    scanf("%d%d%s%s",&n,&m,s+1,t+1);
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*B;
    for(int i=1;i<=n;i++){
        G[s[i]-'a'].push_back(i);
        prs[i]=i-mp[s[i]-'a'];
        mp[s[i]-'a']=i;
    }
    for(int i=0;i<26;i++)G[i].push_back(n+1);
    memset(mp,0,sizeof(mp));
    for(int i=1;i<=m;i++){
        prt[i]=i-mp[t[i]-'a'];
        mp[t[i]-'a']=i;
    }
    for(int i=m;i>=1;i--){
        sums=sums*B+(ull)prs[i];
        sumt=sumt*B+(ull)prt[i];
    }
    for(int i=1;i<=n-m+1;i++){
        if(check(i))ans.push_back(i);
        for(int j=0;j<26;j++){
            int pos=*lower_bound(G[j].begin(),G[j].end(),i);
            if(pos<i+m)sums-=pw[pos-i];
        }
        sums*=inv;
        sums+=pw[m-1]*(ull)(i+m-prs[i+m]>i?prs[i+m]:m);
    }
    cout<<ans.size()<<endl;
    for(auto v:ans)cout<<v<<' ';
    cout<<endl;
    return 0;
}
```

---

