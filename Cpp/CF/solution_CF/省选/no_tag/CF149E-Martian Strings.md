# Martian Strings

## 题目描述

During the study of the Martians Petya clearly understood that the Martians are absolutely lazy. They like to sleep and don't like to wake up.

Imagine a Martian who has exactly $ n $ eyes located in a row and numbered from the left to the right from $ 1 $ to $ n $ . When a Martian sleeps, he puts a patch on each eye (so that the Martian morning doesn't wake him up). The inner side of each patch has an uppercase Latin letter. So, when a Martian wakes up and opens all his eyes he sees a string $ s $ consisting of uppercase Latin letters. The string's length is $ n $ .

"Ding dong!" — the alarm goes off. A Martian has already woken up but he hasn't opened any of his eyes. He feels that today is going to be a hard day, so he wants to open his eyes and see something good. The Martian considers only $ m $ Martian words beautiful. Besides, it is hard for him to open all eyes at once so early in the morning. So he opens two non-overlapping segments of consecutive eyes. More formally, the Martian chooses four numbers $ a $ , $ b $ , $ c $ , $ d $ , ( $ 1<=a<=b&lt;c<=d<=n $ ) and opens all eyes with numbers $ i $ such that $ a<=i<=b $ or $ c<=i<=d $ . After the Martian opens the eyes he needs, he reads all the visible characters from the left to the right and thus, he sees some word.

Let's consider all different words the Martian can see in the morning. Your task is to find out how many beautiful words are among them.

## 说明/提示

Let's consider the sample test. There the Martian can get only the second beautiful string if he opens segments of eyes $ a=1,b=2 $ and $ c=4,d=5 $ or of he opens segments of eyes $ a=1,b=2 $ and $ c=6,d=7 $ .

## 样例 #1

### 输入

```
ABCBABA
2
BAAB
ABBA
```

### 输出

```
1
```

# 题解

## 作者：chaynflow (赞：8)

~~为什么没有正经的 SA 题解啊！~~

首先，我们如果要找两个子串给他拼起来，就对原串正反做两遍 SA（后面都只考虑第一次正着做）

然后建一个 ST 表，维护在一个区间 $[l,r]$ 内最小的 $sa_i$，也就是后缀名次在 $[l,r]$ 内最靠前的后缀，待会儿会用到。

我们发现，当长度 $len$ 增加时，满足后缀的 $len$ 长度的前缀与 $p_i$ 的等长前缀相同时，这样的后缀总是越来越少的，并且排名范围一定是一个区间。

所以每读入一个 $p_i$，就枚举 $len$ 从 $1$ 到 $\operatorname{len}(p_i)$ 从 $l=1,r=n$ 开始缩小区间，每次检查后缀 $sa_l,sa_r$ ，不符合就缩小区间，然后再刚刚求的 ST 表上找这个区间内最靠前的后缀，把它记录在 $ans_{len}$ 中，表示 $p_i$ 的 前 $len$ 个字符最早可以在原串的 $ans_{len}$ 位置找到，如果找不到，则 $ans_{len} = -1$。

接着要判断答案，我们要拿出正串答案 $ans$ 与反串答案 $ans'$。如果存在一个 $q$ 满足以下**所有**条件，则有解：

+ $ans_q \ne -1$。

+ $ans'_{\operatorname{len}(p_i) - q} \ne -1$。

+ $n - ans_q - ans'_{\operatorname{len}(p_i) - q} + 2 \ge \operatorname{len}(p_i)$。

解释一下三个条件：可以找到 $p_i$ 的前 $q$ 个字符，可以找到 $p_i$ 的剩余字符，两个区间无交。

然后就做完了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
string s, pp, ppp;
typedef long long ll;
#define si sizeof(int)
const int N = 1e5 + 5;
int n, m, q, p, i, cnt[N], sa[N], rk[N << 1], sap[N], rkp[N << 1];
int sa1[N], sa2[N];
void Shuffix(string s, int _sa[]) // sa 板子
{
    n = s.size();
    m = 127;
    memset(cnt, 0, sizeof(cnt));
    memset(sa, 0, sizeof(sa));
    memset(rk, 0, sizeof(rk));
    for (i = 1; i <= n; i++) ++cnt[rk[i] = s[i - 1]];
    for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; i--) sa[cnt[rk[i]]--] = i;
    memcpy(rkp + 1, rk + 1, si * n);
    for (p = 0, i = 1; i <= n; i++) 
        if (rkp[sa[i]] == rkp[sa[i - 1]]) rk[sa[i]] = p;
        else rk[sa[i]] = ++p;
    for (int w = 1; w < n; w <<= 1, m = n)
    {   
        memset(cnt, 0, sizeof(cnt));
	    memcpy(sap + 1, sa + 1, si * n); 
	    for (i = 1; i <= n; ++i) ++cnt[rk[sap[i] + w]];
	    for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
	    for (i = n; i >= 1; --i) sa[cnt[rk[sap[i] + w]]--] = sap[i];
        memset(cnt, 0, sizeof(cnt));
        memcpy(sap + 1, sa + 1, si * n);
        for (i = 1; i <= n; i++) ++cnt[rk[sap[i]]];
        for (i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
        for (i = n; i >= 1; i--) sa[cnt[rk[sap[i]]]--] = sap[i];
        memcpy(rkp + 1, rk + 1, si * n);
        for (p = 0, i = 1; i <= n; i++) 
            if (rkp[sa[i]] == rkp[sa[i - 1]] && rkp[sa[i] + w] == rkp[sa[i - 1] + w]) rk[sa[i]] = p;
            else rk[sa[i]] = ++p;
    }
    for (i = 1; i <= n; i++) 
        _sa[i] = sa[i];
}
void Reverse(string& s) // 翻转字符串
{
    int len = s.size();
    for (int i = 0; i < (len + 1) / 2; i++)
        swap(s[i], s[len - i - 1]);
}
int ans[N], _ans[N], anscnt;
bool check(int _p, int _i, int _sa[]) // 求一个后缀是否匹配
{
    return (_sa[_p] + _i - 1 <= n && s[_sa[_p] + _i - 2] == pp[_i - 1]);
} 
int st1[N][22], st2[N][22];
int base2[N];
void calc(int st[][22], int a[]) // 建 st 表
{
    for (int len = 0; len <= 22; len++)
        for (int i = 1; i <= n - (1 << len) + 1; i++)
            st[i][len] = (len == 0 ? a[i] : min(st[i][len - 1], st[i + (1 << len - 1)][len - 1])); // , printf("%d %d: %d\n", i, len, st[i][len]);
}
int query(int st[][22], int l, int r) // 查询
{
    int len = r - l + 1;
    return min(st[l][base2[len]], st[r - (1 << base2[len]) + 1][base2[len]]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> s >> q;
    Shuffix(s, sa1); // 正串 sa
    Reverse(s);
    Shuffix(s, sa2); // 反串 sa
    for (i = 2; i <= n; i++)
        base2[i] = base2[i / 2] + 1;
    calc(st1, sa1);
    calc(st2, sa2);
    while (q--)
    {   
        cin >> pp;
        int len, l1, l2, r1, r2;
        len = pp.size();
        if (len == 1) continue;
        l1 = l2 = 1;
        r1 = r2 = n;
        Reverse(s);
        for (i = 1; i < len; i++)
        {   
            while (l1 <= n && !check(l1, i, sa1)) l1++;
            while (r1 >= 1 && !check(r1, i, sa1)) r1--;
            ans[i] = (l1 > r1 ? -1 : query(st1, l1, r1)); // 正串 ans
        } 
        Reverse(s);
        Reverse(pp); 
        for (i = 1; i < len; i++)
        {   
            while (l2 <= n && !check(l2, i, sa2)) l2++;
            while (r2 >= 1 && !check(r2, i, sa2)) r2--;
            _ans[i] = (l2 > r2 ? -1 : query(st2, l2, r2)); // 反串 ans
        }
        for (int i = 1; i < len; i++)
            if (ans[i] != -1 && _ans[len - i] != -1 && n - ans[i] - _ans[len - i] + 2 >= len) {anscnt++; break;} // 是否合法
    }
    cout << anscnt;
    return 0;
}
```

---

## 作者：MspAInt (赞：7)

[CF149E](https://www.luogu.com.cn/problem/CF149E)

因为我不会用 SA，所以写的是 kmp 题解/oh

显然提取的两个串只有分别是模式串的前缀和后缀才能拼，把存在于文本串中的模式串前后缀都给求出来不就可以了！

前缀的话，kmp 一遍存下来就好了。

后缀需要稍微想想，其实就是把模式串和文本串都倒过来求前缀。

现在考虑拼接操作，可以在求后缀时顺便做一下。首先要保证前后缀长度之和为模式串长度，为了快速取出所需长度的前缀，可以开一个桶存长度为 $x$ 的起始位置最左侧的前缀（显然这样可以尽量保证前缀区间位置合法）。每拿到一个后缀判断一下即可。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,M=1e3+10;
char S[N],SS[N],s[M],ss[M];
int n,m,q,j,ans,k1[M],k2[M],t[M];
signed main(){
    scanf("%s",S+1);n=strlen(S+1);
    for(int i=1;i<=n;i++)SS[i]=S[n-i+1];
    scanf("%d",&q);
    while(q--){
        scanf("%s",s+1);m=strlen(s+1);
        if(m>n||m==1)continue;
        memset(k1,0,sizeof(k1));memset(k2,0,sizeof(k2));memset(t,0,sizeof(t));
        for(int i=2;i<=m;i++)
            {while(j&&s[j+1]!=s[i])j=k1[j];if(s[j+1]==s[i])j++;k1[i]=j;}j=0;
        for(int i=1;i<=n;i++){
            while(j&&s[j+1]!=S[i])j=k1[j];if(s[j+1]==S[i])j++;
            if(!t[j])t[j]=i;
        }j=0;
        for(int i=1;i<=m;i++)ss[i]=s[m-i+1];
        // for(int i=1;i<=m;i++)printf("%d ",t[i]);puts("");
        for(int i=2;i<=m;i++)
            {while(j&&ss[j+1]!=ss[i])j=k2[j];if(ss[j+1]==ss[i])j++;k2[i]=j;}j=0;
        for(int i=1;i<=n;i++){
            while(j&&ss[j+1]!=SS[i])j=k2[j];if(ss[j+1]==SS[i])j++;
            if(t[m-j]&&t[m-j]<n-i+1){ans++;break;}
        }j=0;
    }
    printf("%d\n",ans);
    return 0;
}
```

[record](https://www.luogu.com.cn/record/113054675)

---

## 作者：EM_LGH (赞：5)

这里给出来一个后缀自动机的题解. 

考虑对 $s$ 的正串和反串分别建后缀自动机.

对于正串的每个节点维护 $endpos$ 的最小值.

对于反串的每个节点维护 $endpos$ 的最大值. 

这两个东西通过一个简单的基数排序就可以实现. 

将 $p$ 的正串在正串的 SAM 上去匹配，一直
匹配到匹配不了为止，并记录 $p[i]$ 在正串中自动机节点上 $endpos$ 的最小值 $a[i]$. 

对 $p$ 的反串也进行相同的处理，记录 $endpos$ 的最大值 $b[i]$.

正串中的 $endpos$ 就是 $p[1...i]$ 中 $i$ 的最小结束位置，那么反串中的 $endpos$ 就是 $p[i...length(p)]$ 中 $i$ 的最大开始位置. 

所以，我们只需枚举 $1$~length(p) 并判断 $a[i]&&b[i]&&a[i]<b[i+1]$ 即可. 

如果满足这个条件，就说明这个询问是有解的. 

当然，要注意判断一下长度为 $1$ 的情况，这显然是无解的. 

```cpp
#include <cstdio> 
#include <cstring> 
#include <algorithm> 
#define N 200004 
#define setIO(s) freopen(s".in","r",stdin) 
using namespace std;    
inline void getmin(int &a,int b) { if(b<a)a=b; } 
inline void getmax(int &a,int b) { if(b>a)a=b; } 
int a[1002],b[1002],n; 
char str[N],P[N];   
struct SAM 
{ 
    int c[N],rk[N],tot,last; 
    struct Node { int len,ch[27],f,minv,maxv; }t[N]; 
    void init() { last=tot=1; } 
    inline void extend(int c,int lst) 
    {
        int np=++tot,p=last; 
        last=np, t[np].len=t[p].len+1; 
        while(p&&!t[p].ch[c]) t[p].ch[c]=np,p=t[p].f;  
        if(!p) t[np].f=1;
        else 
        {
            int q=t[p].ch[c]; 
            if(t[q].len==t[p].len+1) t[np].f=q; 
            else 
            {
                int nq=++tot;
                t[nq].len=t[p].len+1,t[nq].minv=t[nq].maxv=t[q].maxv;   
                memcpy(t[nq].ch,t[q].ch,sizeof(t[q].ch)); 
                t[nq].f=t[q].f,t[q].f=t[np].f=nq;   
                while(p&&t[p].ch[c]==q) t[p].ch[c]=nq,p=t[p].f;   
            }
        }   
        t[np].minv=t[np].maxv=lst; 
    }       
    inline void prepare() 
    { 
        int i,u; 
        for(i=1;i<=tot;++i) c[i]=0;  
        for(i=1;i<=tot;++i) ++c[t[i].len];   
        for(i=1;i<=tot;++i) rk[c[t[i].len]--]=i;  
        for(i=tot;i>=1;--i) 
            u=rk[i],getmin(t[t[u].f].minv,t[u].minv),getmax(t[t[u].f].maxv,t[u].maxv);      
    }
}t1,t2;  
int main() 
{
    int i,j,m,re=0,ans=0; 
    // setIO("input"); 
    t1.init(),t2.init();    
    scanf("%s",str+1),n=strlen(str+1); 
    for(i=1;i<=n;++i) t1.extend(str[i]-'A',i); 
    for(i=n;i>=1;--i) t2.extend(str[i]-'A',i); 
    t1.prepare(),t2.prepare(),scanf("%d",&m); 
    for(i=1;i<=m;++i) 
    {
        int len,p; 
        scanf("%s",P+1),len=strlen(P+1),memset(a,0,sizeof(a)),memset(b,0,sizeof(b));       
        for(p=j=1;j<=len;++j) 
        {
            int c=P[j]-'A';      
            if(t1.t[p].ch[c]) a[j]=t1.t[t1.t[p].ch[c]].minv,p=t1.t[p].ch[c]; else break; 
        } 
        for(p=1,j=len;j>=1;--j) 
        {
            int c=P[j]-'A'; 
            if(t2.t[p].ch[c]) b[j]=t2.t[t2.t[p].ch[c]].maxv,p=t2.t[p].ch[c]; else break;  
        } 
        re=0;   
        for(j=1;j<len;++j) {
            if(a[j]&&b[j+1]&&a[j]<b[j+1]) re=1;     
        }
        if(a[len]) re=1; 
        if(len==1) re=0;   
        ans+=re;  
    }
    printf("%d\n",ans); 
    return 0; 
}
```


---

## 作者：优秀的渣渣禹 (赞：5)

是在做有关后缀数组的题中发现这个题，然而题解中的大佬们用的后缀自动机，蒟蒻表示不会啊QwQ，但是发现这道题用kmp就可以做w。
下面给出kmp的做法。

#### 题目大意：

给出字符串$S$,再给$m$个字符串$T$，判断有几个$T$是可以在$S$中找到坐标$a,b,c,d$ 满足$1 \leq a \leq b < c \leq d \leq n$使得$S[a...b] + S[c...d] = T$.

先正向kmp，记录$T$的前缀的每一个长度，在$S$能匹配的最左边，也就是首次匹配的位置。

然后就是把寻找后缀，把$S$和$T$都逆序存好，再kmp一次。

看是否可以找到一个长度为$x$的后缀的位置在一个长度为$len-x$的前缀的位置之后，如果可以找到该$T$就是合法的

```cpp
#define B cout << "BreakPoint" << endl;
#define O(x) cout << #x << " " << x << endl;
#define O_(x) cout << #x << " " << x << " ";
#define Msz(x) cout << "Sizeof " << #x << " " << sizeof(x)/1024/1024 << " MB" << endl;
#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<set>
#define LL long long
const int inf = 1e9 + 9;
const int N = 2e5 + 5;
using namespace std;
inline int read() {
	int s = 0,w = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		if(ch == '-')
			w = -1;
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		s = s * 10 + ch - '0';
		ch = getchar();
	}
	return s * w;
}
char s[N],t[N],c[N];
int a[N],nxt[N]; 
void next(char x[],int f[]){
    int m = strlen(x);
    f[0] = f[1] = 0;
    for(int i = 1 ; i < m; i++){
        int j = f[i];
        while(j && x[i] != x[j]) j = f[j];
        f[i + 1] = x[i] == x[j] ? 1 + j : 0;
    }
}
bool find(char s[],char t[],int f[],int v){
    next(t,f);
    int n = strlen(s),m = strlen(t),j = 0;
    for(int i = 0; i < n; i++){
        while(j && s[i] != t[j]) j = f[j];
        if(s[i] == t[j]) ++j;
        if(v == 1 && j && a[j] == -1) a[j] = i;
        if(v == 2 && j && a[m - j] != -1 && a[m - j] < n - i - 1) return 1;
    }
    return 0;
}
void back(char s[],int n){
    char ch;
    for(int i = 0,k = n - 1; i < n / 2; i++,k--){
        ch = s[i]; 
		s[i] = s[k]; 
		s[k] = ch;
	}
}
int main(){
    scanf("%s",s);
    int m = read(),cnt = 0;
    while(m--){
        scanf("%s",t);
        memset(a,-1,sizeof(a));
        find(s,t,nxt,1);
        int n = strlen(s);
        for(int i = n - 1,k = 0;i >= 0;i--) c[k++] = s[i];
        back(t,strlen(t));
        if(find(c,t,nxt,2)) cnt++;
    }
    printf("%d\n",cnt);
    return 0;
}
```

---

## 作者：shuangmu (赞：3)

#### 题意

给定一个主串 $s$ 和一些模式串 $p_i$，问主串中是否存在两个不相交的非空字串，拼起来和模式串相同。

考虑如何拼接 $p_i$。我们可以从前向后匹配一遍主串，找到 $p_i$ 的所有长度的前缀在主串中最先出现的位置，并记录下来；然后再从后向前跑匹配，每次匹配上一个后缀，就判断该后缀在主串中的起始位置是否大于这一后缀对应前缀的结束位置，如果是则答案加一。注意判断边界条件。匹配这里用的是 KMP 算法。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+100;

char b[N], s[N];
int n, m, lth;
int fnxt[N], bnxt[N], posl[1005], posr[1005];
bool KMP(){
    int j = 0;
    for(int i = 2; i<=lth; i++){
        while(j && b[j+1]!=b[i]){
            j = fnxt[j];
        }
        if(b[j+1]==b[i]){
            j++;
        }
        fnxt[i] = j;
    }
    j = lth+1;bnxt[lth] = lth+1;
    for(int i = lth-1; i>=1; i--){
        while(j<=lth&&b[j-1]!=b[i]){
            j = bnxt[j];
        }
        if(b[j-1]==b[i]){//只记录第一次出现的结束位置
            j--;
        }
        bnxt[i] = j;
    }
    memset(posl, 0, sizeof(posl));
    j = 0;
    for(int i = 1; i<=n; i++){
        while(j && s[i]!=b[j+1]){
            j = fnxt[j];
        }
        if(s[i]==b[j+1]){
            j++;
        }
        if(!posl[j]&&j){
            posl[j] = i;
        }
    }
    j = lth+1;
    
    for(int i = n; i>=1; i--){
        while(j<=lth&&b[j-1]!=s[i]){
            j = bnxt[j];
        }
        if(s[i]==b[j-1]){
            j--;
        }
        if((j-1)&&posl[j-1]&&posl[j-1]<i&&(j<=lth)){//注意前后缀都要非空
            return true;
        }
    }
    return false;
}
int ans;
int main(){
    scanf("%s", s+1);
    n = strlen(s+1);
    scanf("%d", &m);
    while(m--){
        scanf("%s", b+1);
        lth = strlen(b+1);
        if(KMP()){
            ans++;
        }
    }
    printf("%d\n", ans);
    system("pause");
    return 0;
}
```









---

## 作者：hsfzLZH1 (赞：3)

## 题目大意

给定一个长度为 $n$ 的字符串 $s$ 和 $m$ 个询问，每次询问给出一个字符串 $p$ ，问你是否可能找到四个正整数 $a,b,c,d$ ，满足 $a\le b<c\le d$ ，且 $s_{[a,b]}+s_{[c,d]}=p$ 。统计满足条件的字符串 $p$ 的个数。

（ $s_{[l,r]}$ 代表 $s$ 的下标范围在区间 $[l,r]$ 中的子串， $+$ 是字符串拼接运算）

$2\le |n|\le 10^5,1\le m\le 100,1\le |p|\le 1000$

## 解题思路

我们定义 $pre_i$ 为字符串 $p$ 长度为 $i$ 的前缀在字符串中出现的最靠左的位置， $suf_i$ 为该字符串长度为 $i$ 的后缀在字符串中出现的最靠右的位置。在本题的代码实现中，我们分别定义位置为字符串第一个字符的下标和最后一个字符的下标。观察发现，如果 $suf_i-pre_{|p|-i}+1\ge |p|$ ，那么就保证存在这样的 $a,b,c,d$ 。如果我们能求出 $pre$ 和 $suf$ 这两个数组的值，那么我们就可以解决这个问题。

考虑单独求解 $pre$ 数组。我们对 $s$ 进行后缀排序，在后缀排序中，前缀中含有任意字符串的位置一定是连续的，这些前缀中含有 $p$ 的指定长度的前缀的位置一定是连续的。对于 $p$ 的长度为 $i$ 的前缀，我们在上一个长度为 $i-1$ 的区间的基础上进行 ** 两次 ** 二分，确定区间的左右端点，进而确定其范围，最后的 $pre_i$ 的值就是这个区间对应的下标的最小值。由于每次二分都是在上一次的基础上进行的，可以认为区间每次长度便除以 $2$ ，这样单次计算 $pre$ 数组的时间复杂度就是 $O(|p|+\log_2 n)$ 的。

我们反转字符串 $s$ 和 $p$ ，就可以求解 $suf$ 数组。

总的时间复杂度为 $O((n+m)\log_2 n+\sum |p|)$ ，可以通过此题。

此题还有一种使用 $Z$ 函数求解的方法，在此不加赘述。

## 代码展示

~~代码真的很丑。。。变量名什么的长短不一太难看了~~

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n,m,sa[maxn],sa2[maxn],x[maxn],y[maxn],c[maxn],cur;
int q,le,lg[maxn],st1[maxn][30],st2[maxn][30],ans,pre[1010],suf[1010];
int L,R,l,r,mid;
char s[maxn],revs[maxn],que[1010],rev[1010];
int rmq1(int l,int r)
{
    int k=lg[r-l+1];
    return min(st1[l][k],st1[r-(1<<k)+1][k]);
}
int rmq2(int l,int r)
{
	int k=lg[r-l+1];
	return max(st2[l][k],st2[r-(1<<k)+1][k]);
} 
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);m=128;
	for(int i=1;i<=n;i++)revs[i]=s[n-i+1];
	for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
	for(int i=1;i<=n;i++)x[i]=s[i];
	for(int i=1;i<=m;i++)c[i]=0;
	for(int i=1;i<=n;i++)c[x[i]]++;
	for(int i=1;i<=m;i++)c[i]+=c[i-1];
	for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
	for(int k=1,cur;k<=n;k<<=1)
	{
		cur=0;
		for(int i=n;i>n-k;i--)y[++cur]=i;
		for(int i=1;i<=n;i++)if(sa[i]>k)y[++cur]=sa[i]-k;
		for(int i=0;i<=m;i++)c[i]=0;
		for(int i=1;i<=n;i++)c[x[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i];
		cur=y[sa[1]]=1;
		int a,b;
		for(int i=2;i<=n;i++)
		{
			a=(sa[i]+k>n)?-1:x[sa[i]+k];
			b=(sa[i-1]+k>n)?-1:x[sa[i-1]+k];
			y[sa[i]]=((x[sa[i]]==x[sa[i-1]])&&(a==b))?cur:(++cur);
		}
		swap(x,y);
		if(cur>=n)break;
		m=cur; 
	}
	//for(int i=1;i<=n;i++)printf("%d ",sa[i]);printf("\n");
	for(int i=1;i<=n;i++)st1[i][0]=sa[i];
	for(int i=1;i<=lg[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)
	st1[j][i]=min(st1[j][i-1],st1[j+(1<<(i-1))][i-1]);
	for(int i=1;i<=n;i++)x[i]=revs[i];
	for(int i=1;i<=m;i++)c[i]=0;
	for(int i=1;i<=n;i++)c[x[i]]++;
	for(int i=1;i<=m;i++)c[i]+=c[i-1];
	for(int i=n;i>=1;i--)sa2[c[x[i]]--]=i;
	for(int k=1,cur;k<=n;k<<=1)
	{
		cur=0;
		for(int i=n;i>n-k;i--)y[++cur]=i;
		for(int i=1;i<=n;i++)if(sa2[i]>k)y[++cur]=sa2[i]-k;
		for(int i=0;i<=m;i++)c[i]=0;
		for(int i=1;i<=n;i++)c[x[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i>=1;i--)sa2[c[x[y[i]]]--]=y[i];
		cur=y[sa2[1]]=1;
		int a,b;
		for(int i=2;i<=n;i++)
		{
			a=(sa2[i]+k>n)?-1:x[sa2[i]+k];
			b=(sa2[i-1]+k>n)?-1:x[sa2[i-1]+k];
			y[sa2[i]]=((x[sa2[i]]==x[sa2[i-1]])&&(a==b))?cur:(++cur);
		}
		swap(x,y);
		if(cur>=n)break;
		m=cur; 
	}
	for(int i=1;i<=n;i++)st2[i][0]=n-sa2[i]+1;
	for(int i=1;i<=lg[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)
	st2[j][i]=max(st2[j][i-1],st2[j+(1<<(i-1))][i-1]);
	scanf("%d",&q);
	while(q--)
	{
		memset(pre,-1,sizeof pre);
		memset(suf,-1,sizeof suf); 
		scanf("%s",que+1);
		le=strlen(que+1);rev[le+1]=0;
		for(int i=1;i<=le;i++)rev[i]=que[le-i+1];
		L=1;R=n; 
		for(int i=1;i<=le;i++)
		{
			l=L;r=R+1;
			while(l+1<r)
			{
				mid=(l+r)>>1;
				if(sa[mid]+i-1>n||s[sa[mid]+i-1]>=que[i])r=mid;
				else l=mid;
			}
			if(sa[l]+i-1<=n&&s[sa[l]+i-1]==que[i])L=l;
			else if(r!=R+1&&sa[r]+i-1<=n&&s[sa[r]+i-1]==que[i])L=r;
			else L=-1;
			l=L;r=R+1;
			while(l+1<r)
			{
				mid=(l+r)>>1;
				if(s[sa[mid]+i-1]>que[i])r=mid;
				else l=mid;
			}
			R=l;
			if(L==-1||L>R)break;
			pre[i]=rmq1(L,R);
		}
		//for(int i=1;i<=le;i++)printf("%d ",pre[i]);printf("\n");
		L=1;R=n; 
		for(int i=1;i<=le;i++)
		{
			l=L;r=R+1;
			while(l+1<r)
			{
				mid=(l+r)>>1;
				if(sa2[mid]+i-1>n||revs[sa2[mid]+i-1]>=rev[i])r=mid;
				else l=mid;
			}
			if(sa2[l]+i-1<=n&&revs[sa2[l]+i-1]==rev[i])L=l;
			else if(r!=R+1&&sa2[r]+i-1<=n&&revs[sa2[r]+i-1]==rev[i])L=r;
			else L=-1;
			l=L;r=R+1;
			while(l+1<r)
			{
				mid=(l+r)>>1;
				if(revs[sa2[mid]+i-1]>rev[i])r=mid;
				else l=mid;
			}
			R=l;
			if(L==-1||L>R)break;
			suf[i]=rmq2(L,R);
		}
		//for(int i=1;i<=le;i++)printf("%d ",suf[i]);printf("\n");
		for(int i=1;i<=le;i++)if(suf[le-i]!=-1&&pre[i]!=-1)
		if(suf[le-i]-pre[i]+1>=le){ans++;break;}
	} 
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：lzyqwq (赞：2)

**[cnblogs](https://www.cnblogs.com/MnZnOIerLzy/p/17812885.html)**

感觉这题 SA 做法绝对不止 $\color{orange} *2300$。

**[洛谷](https://www.luogu.com.cn/problem/CF149E) [CF](https://codeforces.com/problemset/problem/149/E)**

> - 给出字符串 $s$，以及 $m$ 个询问串 $p_i$，每次询问是否能找到两个不交的区间 $[a,b],[c,d]$ 使得 $\overline{s_as_{a+1}\dots s_bs_cs_{c+1}\dots s_d} = p_i$。
>
> - $m\le 10^2$，$|p_i|\le10^3$，$|s|\le 10^5$。

考虑将所有串拼成一个大串 $S$，做一遍后缀排序，求出 $sa,rk,\text{height}$ 数组。

对于每一组询问，考虑枚举 $j$ 表示找到 $[a,b],[c,d]$ 使得 $\overline{s_as_{a+1}\dots  s_b}=\overline{p_{i_1}p_{i_2}\dots p_{i_{j}}},\overline{s_bs_{c+1}\dots  s_d}=\overline{p_{i_{j+1}}p_{i_{j+2}}\dots p_{i_{|p_i|}}}$。可以通过二分 + ST 表求出满足条件的后缀的排名区间。

我们考虑选择最左边的 $[a,b]$ 以及最右边的 $[c,d]$，这样一定不劣。因此考虑以排名为下标建立 ST 表维护某个排名区间内，$\boldsymbol{\le |s|}$ **的**最左、左右后缀的位置。然后判断这两个位置截取出来的子串是否相交即可。

时间、空间复杂度均为 $\mathcal{O}(|S|\log |S|)$。

**[提交记录（含代码）](https://codeforces.com/contest/149/submission/231550749)**

---

## 作者：jun头吉吉 (赞：1)

## 题意
给定一个长度为 $n(1\leq n \leq 10^5)$的仅由大写字母组成字符串 $s$ 。

有 $m(1\leq m\leq 100)$ 个字符串 $p_1,p_2,\ldots,p_m$，$|p_i|\le 1000$，对于每个字符串，问能否找到 $1\leq a\leq b \lt c \leq d \leq n$ 使得：
$$s[a\ldots b]+s[c\ldots d]=p_i$$
( $+$ 表示拼接)

问能找到的字符串的个数。
## 题解
这里给出一种比较 $\rm Naive$ 的 $\rm Hash+SA$ 的 $\mathcal{O}(n\log n+nm)$ 算法

首先我们对于 $p$ 的一个前缀 $p[1\ldots i]$，考虑找到等于它的最左位置 $pre_i$。

发现，对于一个串后缀排序之后，可以变成 $p[1\ldots i]$ 与一个后缀的前缀相等。然后因为后缀排过序，前缀等于 $p[1\ldots i]$ 的一定是一个连续区间。这个可以用反证法证明，假设不连续，随便推一推就知道不对劲。

还容易发现 $p[1\ldots i]\to p[1\ldots i+1]$ ，区间必然缩小，脑补一下即可。于是我们开两个指针 $l,r$ 分别指向当前区间，每次 $i+1$ 时暴力缩小区间，最后一定是 $\mathcal{O}(n)$ 的。

那么 $pre_i$ 就是所有符合条件的后缀中最早出现的位置，写个 $\rm ST$ 表就可以 $\mathcal{O}(1)$ 得出了。

反转 $S$ 与 $P$ ，我们可以得到一个类似的数组 $suf$。

那么一个字符串可行，需要什么条件呢？

其实画一下就一目了然了：

![sjyakioi](https://cdn.luogu.com.cn/upload/image_hosting/1cf4ntiw.png)

于是只要有 $i\in(0,|p|)$ 满足 $|S|+2-pre_i-suf_{|P|-i}≥ |p|$ 即可
## 代码
封装了一波结构还是很清晰的。
```cpp
#include<bits/stdc++.h>
#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
template<const int N>
struct String{
	//系统string buxing
	int n;
	/*后缀数组*/
	char s[N];int x[N],y[N],c[N],sa[N];
	bool cmp(int a,int b,int c){return y[a]==y[b]&&y[a+c]==y[b+c];}
	void SA(int m='Z'){
		for(int i=0;i<=m;i++)c[i]=0;
		for(int i=1;i<=n;i++)c[x[i]=s[i]]++;
		for(int i=1;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i>=1;i--)sa[c[x[i]]--]=i;
		for(int k=1;k<=n;k<<=1){
			int num=0;
			for(int i=0;i<=m;i++)c[i]=0;
			for(int i=n-k+1;i<=n;i++)y[++num]=i;
			for(int i=1;i<=n;i++)if(sa[i]>k)y[++num]=sa[i]-k;
			for(int i=1;i<=n;i++)c[x[i]]++;
			for(int i=1;i<=m;i++)c[i]+=c[i-1];
			for(int i=n;i>=1;i--)sa[c[x[y[i]]]--]=y[i],y[i]=0;
			swap(x,y);num=1;x[sa[1]]=1;
			for(int i=2;i<=n;i++){
				if(cmp(sa[i],sa[i-1],k))x[sa[i]]=num;
				else x[sa[i]]=++num;
			}
			if(num==n)break;m=num;
		}
	}
	/*HASH*/
	const int mod=998244353,base=107;
	int power[100100],val[N];
	void HASH(){
		power[0]=1;for(int i=1;i<=n;i++)power[i]=1ll*power[i-1]*base%mod;
		val[0]=0;for(int i=1;i<=n;i++)val[i]=(1ll*val[i-1]*base+s[i])%mod;
	}
	int get(int l,int r){
		long long V=val[r]-1ll*val[l-1]*power[r-l+1];
		return (V%mod+mod)%mod;
	}
	/*读入*/
	void read(){scanf("%s",s+1);n=strlen(s+1);}
	void print(){printf("%s\n",s+1);}
	/*翻转*/
	void reverse(String<N> &b){
		b.n=n;
		for(int i=1;i<=n;i++)
			b.s[i]=s[n-i+1];
	}
};
template<const int N,const int M>
struct ST{
	int cmp(int a,int b){return a>b?b:a;}
	int dp[M][N];
	int &operator[](int x){return dp[0][x];}
    void init(int n){
        for(int j=1;(1<<j)<=n;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                dp[j][i]=cmp(dp[j-1][i],dp[j-1][i+(1<<j-1)]);
    }
    int query(int st,int ed){
        int j=log(ed-st+1)/log(2);
        return cmp(dp[j][st],dp[j][ed-(1<<j)+1]);
    }
};
template<class A,class B>
bool Strcmp(A &S1,int st1,B &S2,int st2,int len,int get2=-1){
	if(len==0)return true;
	if(S1.n<st1+len-1)return false;
	if(S2.n<st2+len-1)return false;
	if(get2==-1)
		return S1.get(st1,st1+len-1)==S2.get(st2,st2+len-1);
	else return S1.get(st1,st1+len-1)==get2;
}
ST<100100,18>ST1,ST2;
String<100100>S1,S2;
String<1005>P1,P2;
int m,ans=0;
int pre[1005],suf[1005];
signed main(){
	//freopen("aaa","r",stdin);
	S1.read();S1.SA();S1.HASH();
	S1.reverse(S2);S2.SA();S2.HASH();
	for(int i=1;i<=S1.n;i++)ST1[i]=S1.sa[i];
	for(int i=1;i<=S2.n;i++)ST2[i]=S2.sa[i];
	ST1.init(S1.n);ST2.init(S2.n);
	scanf("%d",&m);
	while(m--){
		P1.read();P1.HASH();
		P1.reverse(P2);P2.HASH();
		auto f=[&](int *arr,String<100100>&S,ST<100100,18>&RMQ,String<1005>&P){
			memset(arr,255,sizeof pre);
			int l=1,r=S.n;
			for(int i=0;i<=P.n;i++){
				int now=P.get(1,i);
				while(l<=r&&!Strcmp(S,S.sa[l],P,1,i,now))l++;
				while(r>=l&&!Strcmp(S,S.sa[r],P,1,i,now))r--;
				if(l>r)break;
				arr[i]=RMQ.query(l,r);
			}
		};
		f(pre,S1,ST1,P1);f(suf,S2,ST2,P2);
		//for(int i=0;i<=P1.n;i++)printf("%d ",pre[i]);puts("");
		//for(int i=0;i<=P1.n;i++)printf("%d ",suf[i]);puts("");
		for(int i=1;i<P1.n;i++)
			if(pre[i]!=-1&&suf[P1.n-i]!=-1)
				if(S1.n+2-pre[i]-suf[P1.n-i]>=P1.n){
					ans++;break;
				}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：SFlyer (赞：0)

另一种（维护方式）的 SAM 题解？

首先，这个数据范围就是要一个 $\mathcal{O}(\sum |p_i|)$ 的做法，容易想到，如果我们能对于正串和反串求：

- $p_{i_{1\sim j}}$ 在 $s$ 中最少匹配到哪，即最小位置。

我们就可以维护答案了。也就是说，要求 SAM 中 endpos 的最小值。这个的话，设为 $lst(x)$，我们插入字符的时候，$lst(np)=len(np),lst(nq)=lst(q)$ 就可以了。$nq$ 是 clone 的节点。

感觉比另一篇 SAM 好写（？）

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N = 3e5+5;

struct sam {
	int tot=1,lst=1;
	struct node {
		int len,ch[26],fa,fst;
	} t[N];
	int pos[N];
	void ins(int c){
		int p=lst,np=++tot;
		t[np].len=t[p].len+1;
		t[np].fst=t[np].len;
		lst=np;
		while (p && !t[p].ch[c]){
			t[p].ch[c]=np;
			p=t[p].fa;
		}
		if (!p){
			t[np].fa=1;
			return;
		}
		int q=t[p].ch[c];
		if (t[q].len==t[p].len+1){
			t[np].fa=q;
			return;
		}
		int nq=++tot;
		t[nq]=t[q];
		t[nq].len=t[p].len+1;
		t[q].fa=t[np].fa=nq;
		while (p && t[p].ch[c]==q){
			t[p].ch[c]=nq;
			p=t[p].fa;
		}
	}
	void sol(string x){
		int cur=1;
		memset(pos,-1,sizeof pos);
		for (int i=0; i<x.size(); i++){
			cur=t[cur].ch[x[i]-'A'];
			if (cur==0){
				break;
			}
			pos[i]=t[cur].fst-i;
		}
	}
} it,rev;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s;
	cin>>s;
	string t=s;
	reverse(t.begin(),t.end());
	for (auto u : s){
		it.ins(u-'A');
	}
	for (auto u : t){
		rev.ins(u-'A');
	}
	int q;
	cin>>q;
	int cnt=0;
	while (q--){
		string x;
		cin>>x;
		string y=x;
		reverse(y.begin(),y.end());
		it.sol(x),rev.sol(y);
		int sz=x.size(),f=0;
		for (int i=0; i+1<x.size(); i++){
			int ls=i,rs=x.size()-i-2;
			int itf=it.pos[ls],rvf=rev.pos[rs];
			if (itf!=-1 && rvf!=-1){
				int r=itf+ls,l=s.size()-rvf+1-rs;
				if (r<l){
					f=1;
					cnt++;
					break;
				}
			}
		}
	}
	cout<<cnt<<endl;
	return 0;
}
```

---

## 作者：Lyccrius (赞：0)

枚举询问串的断点 $i$。

要让 $p[1, i]$ 在 $s$ 中出现，$p[1, i]$ 应为 $s$ 某后缀的前缀，不难证明这样的后缀为 $sa$ 中的一段区间。

随着 $i$ 的增大，区间不断变小，使用双指针维护。

为了尽可能存在解，$a, b$ 应尽量靠前，因此 $a$ 选择 $sa[l, r]$ 中的最小值，预处理 ST 表以实现 $\mathcal O(1)$ 查询。

对于一个断点 $i$ 选定了 $[a, b]$，现在需要选定 $[c, d]$。

为了尽可能存在解，$c, d$ 应尽量靠后，将串翻转转化为上面的问题。

对于每一个端点做完决策后检查合法性，即是否有 $b \lt c$。

时间复杂度 $\mathcal O(nm)$。

---

