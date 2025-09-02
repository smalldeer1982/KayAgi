# Antichain

## 题目描述

有一个$n$个点（$n<=10^6$）的$0…n-1$标号的$DAG$，有$n$条端点为$i$和$(i+1)\%n$的有向边（方向是给定的，保证一定会构成一个$DAG$），求最长反链。

一个“反链”定义为一个点的集合，使得这个集合内任意两个点互相不能到达。

## 样例 #1

### 输入

```
001
```

### 输出

```
1
```

## 样例 #2

### 输入

```
110010
```

### 输出

```
3
```

# 题解

## 作者：ywy_c_asm (赞：2)

首先有个比较显然的事实就是这个“环”一定被划分成类似这样的若干条极长的链：

![](https://cdn.luogu.com.cn/upload/pic/58906.png)

可以发现完全属于这些链上的点（入度和出度都是1），不同链上的点是独立的，并且，如果我们先选了一个链的端点，那么和他相邻的两条链上的点就都不能选，而先选一个完全在链上的点只会影响这条链，而一条链最多只能选一个点。那么我们先贪心的选完全在链上的点，再选链的端点即可。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
namespace ywy {
	char str[2000001];
	unsigned char bv[2000001], indeg[2000001], outdeg[2000001];
	int n;
	void dfs(int pt) {
	    if (bv[pt])
	        return;
	    bv[pt] = 1;
	    if (str[pt] == '0')
	        dfs((pt + 1) % n);
	    if (str[(pt - 1 + n) % n] == '1')
	        dfs((pt - 1 + n) % n);
	}
	void efs(int pt) {
	    if (bv[pt])
	        return;
	    bv[pt] = 1;
	    if (str[pt] == '1')
	        efs((pt + 1) % n);
	    if (str[(pt - 1 + n) % n] == '0')
	        efs((pt - 1 + n) % n);
	}
	void ywymain() {
	    scanf("%s", str);
	    n = strlen(str);
	    for (register int i = 0; i < n; i++) {
	        if (str[i] == '0')
	            indeg[(i + 1) % n]++, outdeg[i]++;
	        else
	            indeg[i]++, outdeg[(i + 1) % n]++;
	    }
	    int ans = 0;
	    for (register int i = 0; i < n; i++) {
	        if (bv[i])
	            continue;
	        if (indeg[i] && outdeg[i]) {
	            dfs(i);
	            bv[i] = 0;
	            efs(i);
	            ans++;
	        }
	    }
	    for (register int i = 0; i < n; i++) {
	        if (bv[i])
	            continue;
	        ans++;
	        dfs(i);
	        bv[i] = 0;
	        efs(i);
	    }
	    cout << ans << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：1234567890sjx (赞：0)

首先特判掉所有边都指向一个方向最后形成一个大环的情况。剩下的情况都可以被剖成若干个长度 $\ge 2$ 的链，其中链中的结点可以按照一个方向被到达。但是特殊的，链的顶端和底端的两个结点会被公用（被恰好两条链所包含）。于是考虑随便贪心，先贪心选不是顶端和底端的链的结点，再选是顶端和底端的链的结点，可以做到 $O(n)$ 通过该题。

还有就是“反链”的定义是任意两个点都没有边相连，而**不是**距离不为 $1$。有个人虚空调试了 $40$ min 才发现。

```cpp
char s[N];
int a[N], vis[N];
int Pre(int x, int mod) {
    if (x == 1) return mod;
    return x - 1;
}
int Nxt(int x, int mod) {
    if (x == mod) return 1;
    return x + 1;
}
int get(int x, int mod) {
    if (x > mod) return x - mod;
    return x;
}
void run() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    if (count(s + 1, s + n + 1, s[1]) == n) {
        cout << 1 << '\n'; 
        return;
    }
    for (int i = 1; i <= n; ++i) s[i + n] = s[i];
    vector<vector<int>> lnks;
    int spos = 2e18;
    for (int i = 2; i <= n + spos; ++i) if (s[i] != s[i - 1]) {
        if (spos > 1e18) spos = i - 1;
        vector<int> lnk = {get(i, n)}; int j;
        for (j = i + 1; s[j] == s[j - 1]; ++j) lnk.eb(get(j, n));
        lnk.eb(get(j, n)); lnks.eb(lnk); i = j - 1;
    }
    int cnt = 0;
    for (int i = 0; i < lnks.size(); ++i) {
        vector<int> &lnk = lnks[i];
        if (lnk.size() > 2) ++cnt, vis[i] = 1;
    }
    lnks.eb(lnks[0]);
    for (int i = 0; i < lnks.size() - 1; ++i) {
        if (lnks[i].size() == 2 && lnks[i + 1].size() == 2) ++cnt, ++i;
    }
    cout << cnt << '\n';
}
```

---

## 作者：Hoks (赞：0)

## 前言
duel 到的题，和傻逼一样挂挂挂，一眼胡的思路被细节硬控了 $50$ 分钟。

这个题细节挺多的，建议仔细手模。

摘自 [杂题选做](https://www.luogu.com.cn/training/499842)。
## 思路分析
首先题目给定的即为一个大环，长度为 $n$。

显然一个点只会有两条边包括这个点。

那么我们就可以把这个环剖开成为一条条链，而这些链中链顶和链底被公用了。

显然的是最优情况肯定是每条链中取出一个点。

但是因为公用的原因，导致如果取了链顶/底就会同时覆盖掉两条链。

贪心的选取，肯定先选非链顶/底的点，然后遍历链打标记。

接着再考虑选取链顶/底的点，遍历链打标记即可。

说起来是挺简单的，但是因为这个题的阴间连边方式，很容易写挂，只能说多手模吧。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,V=1e6,INF=0x3f3f3f3f3f3f3f3f,mod=998244353;
int n,ans,in[N],ut[N],l[N],r[N],mp[N];char s[N];queue<int>q;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf,out[10000000];int length=0;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void flush(){fwrite(out,1,length,stdout);length=0;}
    inline void put(char c){if(length==9999999) flush();out[length++]=c;}
    inline void put(string s) { for(char c:s) put(c); }
    inline void print(int x)
    {
        if(x<0) put('-'),x=-x;
        if(x>9) print(x/10);
        put(x%10+'0');
    }
    inline bool chk(char c) { return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'); }
    inline bool ck(char c) { return c!='\n'&&c!='\r'&&c!=-1&&c!=' '; }
    inline void rd(char s[],int&n)
    {
        s[++n]=getchar();
        while(chk(s[n])) s[n]=getchar();
        while(ck(s[n])) s[++n]=getchar();
        n--;
    }
}
using namespace Fast_IO;
inline void dfs1(int u)
{
    if(mp[u]) return;mp[u]=1;
    if(s[u]=='0') dfs1(r[u]);
    if(s[l[u]]=='1') dfs1(l[u]);
}
inline void dfs2(int u)
{
    if(mp[u]) return;mp[u]=1;
    if(s[u]=='1') dfs2(r[u]);
    if(s[l[u]]=='0') dfs2(l[u]);
}
signed main()
{
    rd(s,n);for(int i=1;i<=n;i++) l[i]=i-1,r[i]=i+1;l[1]=n;r[n]=1;//防写挂左右相邻
    for(int i=1;i<=n;i++) if(s[i]=='0') ut[r[i]]++,in[i]++;else ut[i]++,in[r[i]]++;
    for(int i=1;i<=n;i++)
    {
        if(mp[i]) continue;
        if(in[i]&&ut[i]) dfs1(i),mp[i]=0,dfs2(i),ans++;
    }
    for(int i=1;i<=n;i++)
    {
        if(mp[i]) continue;
        ans++,dfs1(i),mp[i]=0,dfs2(i);
    }
    print(ans);genshin:;flush();return 0;
}

```

---

