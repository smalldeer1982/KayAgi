# [POI 2014] PRZ-Criminals

## 题目描述

两个罪犯 Bitie 和 Bytie 抢劫 $n$ 个房子，每个房子有一个颜色，Bitie 从低编号到高编号，Bytie 从高编号到低编号，直到相遇为止。已知罪犯开始时所在房子颜色相同（但不知道是什么颜色），并且知道罪犯依次抢劫的所有房子的颜色，且每个罪犯对每种颜色的房子分别最多抢劫一次，求所有可能的相遇点。

## 样例 #1

### 输入

```
15 7
2 5 6 2 4 7 3 3 2 3 7 5 3 6 2
3 2
4 7 3
5 3
```

### 输出

```
3
7 8 10
```

# 题解

## 作者：ZGS_WZY (赞：1)

**题意**

[额外提供一个LOJ的翻译](https://loj.ac/p/2465)

**题目分析**
	
我们考虑枚举每一个可能的相遇位置 $i$（即满足 $c[i]=x[m]=y[l]$ )，我们希望两个人所访问的第一个方格尽可能地靠近 $i$，分别记为 $x$,$y$，然后我们检查 $\left[1,x-1 \right]$ 和 $\left[y+1,n \right]$ 两个区间有没有相同的颜色即可。

因此题解分为以下两个部分：

### $Part 1:$

$L[i]:$ 相遇点为 $i$ 时，第一个人下标最大的出发点。

$R[i]:$ 相遇点为 $i$ 时，第二个人下标最小的出发点。

实际上将颜色数组 $c$ 倒叙后求 $R[i]$ 的过程与求 $L[i]$ 的基本一样，所以这里只讨论 $L[i]$ 的求法。

我们可以维护若干个序列，表示从不同的起始点 $i$（即满足 $c[i]=a[1]$）出发经过的最长的下标序列，使得这些下标上对应的颜色能匹配 $a$ 数组的前若干位。而我们想要知道的就是长度为 $m$ 的上述序列中第一个下标最大是多少。

例如对于以下情况：
```cpp
c:4 7 4 3 4 7 1 3 1
a:4 7 3 1
m=4
```
截止到第7个位置时，几个序列如下：
```cpp
1 2 4 7
3 6
5 6
```
所以 $L[7]=1$。

直接维护效率过低，我们考虑优化。

$Hint 1:$

如果有两个序列长度一样，那我们可以直接舍弃掉前一个序列，因为它的第一位下标比后一个小，且它们两在往后匹配的过程中遇到的情况始终是一样的。（上面例子的第2,3两个序列就是如此）

$Hint 2:$

我们只需要知道每个序列第一个下标是多少，以及目前需要匹配 $a$ 数组中的第几位即可。

有了这两个想法，我们可以记 $pos[i]$ 表示需要匹配第 $i$ 个位置的序列编号。假设当前的 $c[i]=a[x]$ ，那么第 $pos[x]$ 个序列已经可以匹配第 $x$ 个位置，所以我们可以令 $pos[x+1]=pos[x]$。

可是如果在这之前有序列要匹配第 $x+1$ 个位置被覆盖了怎么办？没关系，因为根据第一个想法就算有，它也可以被舍弃了，此外这个优化还保证了每一个序列想要匹配的位置一定不一样。

附上代码：
```cpp
for(int i=1;i<=m;i++)num[a[i]]=i;
pos[1]=1;//造一个空序列需要匹配第一位
int tot=1;
for(int i=1;i<=n;i++){
	if(pos[num[c[i]]]){//存在一个序列需要匹配这一位
		int x=num[c[i]];
		if(x==1)H[pos[1]]=i;//记下出发点
		pos[x+1]=pos[x];pos[x]=0;
		if(x==1)pos[1]=++tot;//跟前面同理
	}
	L[i]=(pos[m+1]!=0&&c[i]==a[m])?H[pos[m+1]]:0;//如果有序列已经匹配完m位，L[i]即为那个序列的出发点。
}
//以下是求R[i]
memset(num,0,sizeof(num));memset(pos,0,sizeof(pos));memset(H,0,sizeof(H));
for(int i=1;i<=l;i++)num[b[i]]=i;
pos[1]=1;tot=1;
for(int i=n;i>=1;i--){
	if(pos[num[c[i]]]){
		int x=num[c[i]];
		if(x==1)H[pos[1]]=i;
		pos[x+1]=pos[x];pos[x]=0;
		if(x==1)pos[1]=++tot;
	}
	R[i]=(pos[l+1]!=0&&c[i]==b[l])?H[pos[l+1]]:n+1;
}
```
时间复杂度: $O(n)$


### $Part 2:$

对于每一种颜色 $x$，我们可以求出它出现的最靠后的位置在哪儿，记为 $pos[x]$ (为了省空间用了同一个数组)。

然后对于位置 $i$，我们可以预处理一个前缀最大值 $pre[i]=\max \limits_{1\leq j \leq i}pos[c[j]]$。于是 $pre[i]$ 就可以表示区间 $\left [1,i\right]$中的颜色出现的最靠后的位置，如果 $pre[i] \geq r$，那么我们就可以认为区间 $\left [1,i\right]$ 和区间 $\left [r,n\right]$ 中有一样的颜色。

附上代码：

```cpp
for(int i=1;i<=n;i++)pos[c[i]]=i;
for(int i=1;i<=n;i++)pre[i]=max(pre[i-1],pos[c[i]]);
for(int i=1;i<=n;i++){
	if(c[i]!=a[m])continue;
	if(pre[L[i]-1]>R[i])ans.push_back(i);
}
```
时间复杂度：$O(n)$


---

## 作者：123zbk (赞：0)

**主题思路**：

因为两个人最开始所在的房子颜色相同，所以我们枚举每一个颜色，预处理出每一个颜色第一次和最后一次出现的位置。

找到每一个颜色后面第一个为抢劫序列第一个元素的位置（不能算自己），从它开始一直跳到最后一个颜色，反过来同理。这里可以类似路径压缩一下。

对于每一种颜色，如果得到对应的一个区间，那么区间内所有与最后一个颜色相同的房子都是答案。

**code**:


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e6+5;
int n,k,s,t,mn=0x3f3f3f3f,mx;
int col[N],a[N],b[N],f[N],g[N],nxt[N],pre[N],l[N],r[N],pos[N],vis[N];
stack <int> st;
vector <int> V;
int get_nxt(int x)
{
    while(x!=f[x]){
        st.push(x);
        x=f[x];
    }
    while(!st.empty()){
        f[st.top()]=x;
        st.pop();
    }
    return x;
}
int get_pre(int x)
{
    while(x!=g[x]){
        st.push(x);
        x=g[x];
    }
    while(!st.empty()){
        g[st.top()]=x;
        st.pop();
    }
    return x;
}
int main()
{
    //freopen("data.in","r",stdin);
    cin>>n>>k;
    for(int i=1;i<=n;i++) scanf("%d",&col[i]);
    cin>>s>>t;
    for(int i=1;i<=s;i++){
        scanf("%d",&a[i]);
        vis[a[i]]=i;
    } 
    for(int i=n;i>=1;i--){
        nxt[i]=pos[a[1]];
        pos[col[i]]=i;
    }
    for(int i=1;i<=k;i++) pos[i]=0;
    for(int i=n;i>=1;i--){  
        if(!vis[col[i]]) continue;
        if(col[i]==a[s]) f[i]=i;
        else f[i]=pos[a[vis[col[i]]+1]];
        pos[col[i]]=i;
    }
    for(int i=1;i<=k;i++) pos[i]=vis[i]=0;
    for(int i=1;i<=t;i++){
        scanf("%d",&b[i]);
        vis[b[i]]=i;
    } 
    for(int i=1;i<=n;i++){
        pre[i]=pos[b[1]];
        pos[col[i]]=i;
    }
    for(int i=1;i<=k;i++) pos[i]=0;
    for(int i=1;i<=n;i++){
        if(!vis[col[i]]) continue;
        if(col[i]==b[t]) g[i]=i;
        else g[i]=pos[b[vis[col[i]]+1]];
        pos[col[i]]=i;
    }
    for(int i=1;i<=n;i++) r[col[i]]=i;
    for(int i=n;i>=1;i--) l[col[i]]=i;
    for(int i=1;i<=k;i++){
        int L=l[i],R=r[i];
        L=get_nxt(nxt[L]);
        R=get_pre(pre[R]);
        if(!L or !R or L>R) continue;
        mn=min(mn,L);
        mx=max(mx,R);
    }
    for(int i=mn;i<=mx;i++){
        if(col[i]==b[t]) V.push_back(i);
    }
    cout<<V.size()<<"\n";
    for(auto it:V) printf("%d ",it);
    return 0;
}
```

---

## 作者：forgotmyhandle (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P3570)

## 分析
下文左边的指的就是 Bitie 的，右边的指的就是 Bytie 的。

首先不难想到枚举相遇点，然后看左边的出发位置左边和右边的出发位置右边有没有重复位置。

---

根据贪心的原则，我们希望求出最靠右的左出发位置和最靠左的右出发位置。左右是对称的，所以只考虑一边。有一个朴素的想法，就是对每个位置维护每种颜色在这个位置之前最后一次的出现位置，然后暴力跳。但是这样显然过不去，我们考虑优化。

注意到每种颜色在左边的抢劫序列中最多只会出现一次，也就是说每种颜色的前驱是一定的。所以我们就只需要对每个位置维护其颜色的前驱颜色在这个位置之前的最后一次出现是在哪里。然后每次就顺着记录的位置往前跳，直到跳到左边抢劫序列的开头颜色。此时的位置就是最靠右的左出发位置。容易发现暴力跳的过程可以用类似路径压缩的方法搞到 $\mathcal{O}(1)$，所以这部分就是 $\mathcal{O}(n)$ 的。

---

接下来的问题是给定 $x, y$，求 $[1, x]$ 和 $[y, n]$ 中是否有相同颜色。观察到当相遇点单增时，$x, y$ 都是单增的。所以可以使用双指针维护。这也是 $\mathcal{O}(n)$ 的。

## 代码
```cpp
#include <iostream>
using namespace std;
int n, k;
int pc[1000005], nc[1000005];
int cpc[1000005], cnc[1000005];
int clr[1000005];
int a, b;
int ca[1000005], cb[1000005];
int lst[1000005];
int L[1000005], R[1000005];
int cl[1000005], cr[1000005];
int ans[1000005], acnt;
int ocnt;
void Add(int x) { ocnt += (cl[clr[x]]++ == 0 && cr[clr[x]]); }
void Del(int x) { ocnt -= (--cr[clr[x]] == 0 && cl[clr[x]]); }
int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> clr[i];
    cin >> a >> b;
    for (int i = 1; i <= a; i++) cin >> ca[i];
    for (int i = 1; i <= b; i++) cin >> cb[i];
    for (int i = 1; i <= b / 2; i++) swap(cb[i], cb[b - i + 1]);
    for (int i = 1; i <= a; i++) cpc[ca[i]] = (i == 1 ? ca[i] : ca[i - 1]);
    for (int i = 1; i <= b; i++) cnc[cb[i]] = (i == b ? cb[i] : cb[i + 1]);
    for (int i = 1; i <= n; i++) {
        if (cpc[clr[i]]) 
            L[i] = (cpc[clr[i]] == clr[i] ? i : L[lst[cpc[clr[i]]]]);
        lst[clr[i]] = i;
    }
    for (int i = 1; i <= k; i++) lst[i] = n + 1;
    R[n + 1] = n;
    for (int i = n; i; i--) {
        if (cnc[clr[i]]) 
            R[i] = (cnc[clr[i]] == clr[i] ? i : R[lst[cnc[clr[i]]]]);
        lst[clr[i]] = i;
    }
    for (int i = 1; i <= n; i++) cr[clr[i]]++;
    for (int i = 1, l = 0, r = 1; i <= n; i++) {
        if (clr[i] != ca[a]) 
            continue;
        while (l < L[i]) Add(l++);
        while (r <= R[i]) Del(r++);
        ocnt ? (ans[++acnt] = i) : 0;
    }
    cout << acnt << "\n";
    for (int i = 1; i <= acnt; i++) cout << ans[i] << " ";
    cout << "\n";
    return 0;
}
```
### 注意

请注意输入的右序列的顺序。

---

