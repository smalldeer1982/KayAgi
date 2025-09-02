# DZY Loves Strings

## 题目描述

DZY loves strings, and he enjoys collecting them.

In China, many people like to use strings containing their names' initials, for example: xyz, jcvb, dzy, dyh.

Once DZY found a lucky string $ s $ . A lot of pairs of good friends came to DZY when they heard about the news. The first member of the $ i $ -th pair has name $ a_{i} $ , the second one has name $ b_{i} $ . Each pair wondered if there is a substring of the lucky string containing both of their names. If so, they want to find the one with minimum length, which can give them good luck and make their friendship last forever.

Please help DZY for each pair find the minimum length of the substring of $ s $ that contains both $ a_{i} $ and $ b_{i} $ , or point out that such substring doesn't exist.

A substring of $ s $ is a string $ s_{l}s_{l+1}...\ s_{r} $ for some integers $ l,r $ $ (1<=l<=r<=|s|) $ . The length of such the substring is $ (r-l+1) $ .

A string $ p $ contains some another string $ q $ if there is a substring of $ p $ equal to $ q $ .

## 说明/提示

The shortest substrings in the first sample are: xyz, dyhduxyz.

The shortest substrings in the second sample are: ca, abc and abd.

The shortest substrings in the third sample are: baabca and abaa.

## 样例 #1

### 输入

```
xudyhduxyz
3
xyz xyz
dyh xyz
dzy xyz
```

### 输出

```
3
8
-1
```

## 样例 #2

### 输入

```
abcabd
3
a c
ab abc
ab d
```

### 输出

```
2
3
3
```

## 样例 #3

### 输入

```
baabcabaaa
2
abca baa
aa aba
```

### 输出

```
6
4
```

# 题解

## 作者：panyf (赞：13)

根号分治。

令 $s$ 串长度为 $n$ ，在 $s$ 串中长度不超过 $4$ 的子串出现总次数不超过 $4n$ ，因此出现次数超过 $\sqrt{4n}$ 的子串不超过 $\sqrt{4n}$ 个。

先预处理每个长度不超过 $4$ 的子串在 $s$ 中出现的位置。

对于每个出现次数超过 $\sqrt{4n}$ 的子串，将 $s$ 串扫一遍，预处理这个子串和其他子串的答案。

如果询问中两个子串出现次数都不超过 $\sqrt{4n}$ ，那么可以将这两个串在 $s$ 中出现的位置扫一遍。

时间复杂度 $O(n\sqrt n)$ 。

思路不难想，但代码细节较多。代码中用 $500$ 代替 $\sqrt{4n}$ 。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=70009;
char s[N],a[5],b[5];
int mp[500009],h[N],len[N],f[331][N],p[5][N];
//mp为所有出现过的串，h为出现次数超过500的串，len为每个串的长度，f为预处理的答案，p为s中每个长度不超过4的子串的序号
vector<int>v[N];//每个串出现的起始位置
inline int get(char*s,int l){
	int r=0,i=0;
	for(;i<l;++i)r=r*26+s[i]-96;
	return r;
}//将子串转成数字，便于存储
int main(){
	int n,q,id=0,ct=0,i,j,k,l,u,x,y,z,o;
	scanf("%s%d",s+1,&q),n=strlen(s+1);
	for(l=1;l<5;++l){
		for(i=1,j=n-l+2;i<j;++i){
			k=get(s+i,l);
			if(!mp[k])mp[k]=++id,len[id]=l;
			v[p[l][i]=mp[k]].push_back(i);
		}
	}//预处理每个串在s中出现位置
	for(i=1;i<=id;++i)if(j=v[i].size(),j>500){
		h[i]=++ct,u=len[i],memset(f[ct],9,id+2<<2);
		for(k=1;k<j;++k){
			x=v[i][k-1],y=v[i][k];
			for(z=x;z<y;++z)for(l=1;l<5;++l)f[ct][p[l][z]]=min(f[ct][p[l][z]],min(max(z+l-x,u),max(y+u-z,l)));
		}
		for(z=x=v[i][j-1];z<=n;++z)for(l=1;l<5;++l)f[ct][p[l][z]]=min(f[ct][p[l][z]],max(z+l-x,u));
		for(z=1,y=v[i][0];z<y;++z)for(l=1;l<5;++l)f[ct][p[l][z]]=min(f[ct][p[l][z]],max(y+u-z,l));
	}//预处理出现次数超过500的子串答案
	while(q--){
		scanf("%s%s",a,b),x=mp[get(a,strlen(a))],y=mp[get(b,strlen(b))];
		if(!x||!y)puts("-1");//不存在子串
		else if(h[x])printf("%d\n",f[h[x]][y]);
		else if(h[y])printf("%d\n",f[h[y]][x]);//存在一个串出现次数超过500，直接输出
		else{
			j=v[x].size(),k=v[y].size()-1,l=len[x],u=len[y],z=0,o=1e9;
			for(i=0;i<j;++i){
				while(z<k&&v[y][z]<v[x][i])++z;
				if(v[y][z]>=v[x][i]){
					o=min(o,v[y][z]+u-v[x][i]);
					if(z)o=min(o,v[x][i]+l-v[y][z-1]);
				}else o=min(o,v[x][i]+l-v[y][z]);
			}
			printf("%d\n",max(o,max(l,u)));
		}//两个串出现次数都不超过500
	}
	return 0;
}
```


---

## 作者：Purslane (赞：4)

# Solution

经营不善，搞出了 $O(n \sqrt n \log n)$ 的做法。

首先，很容易想到根号分治。我们假设查询的两个字符串出现次数分别是 $cnt_1$ 和 $cnt_2$。

我们考虑两种算法。第一个是 $cnt_1+cnt_2$ 比较小的时候，可以把所有出现归并一下，然后枚举一下就可以做到 $O(cnt_1+cnt_2)$。

第二个是在整个序列上扫描所有的子串。这样每个位置都要进行询问。那么我们在 $cnt_1+cnt_2$ 比较大的时候把 $cnt_1$ 和 $cnt_2$ 中较小者挂到主要询问位置。这样另一方是较大值，出现次数会比较小，也就是每个位置要进行询问的次数会比较少。

于是选取阈值 $B=\sqrt n$。

但是你发现，处理询问竟然是比较困难的。因为，我们无法存储答案（

于是我们先考虑直接字符串哈希。然后第一种情况直接输出，第二种情况放在较小处即可。

注意哈希要用 $27$ 进制来区分空字符和字符。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50000+10,MAXM=1e5+10,MAXK=6e5+10;
int n,q,ans[MAXM]; string S,a[MAXM],b[MAXM];
int check(string S) {
	int ans=0;
	for(auto ch:S) ans=ans*27+(ch-'a'+1);
	return ans;	
}
struct Query {int nxt,id,len;};
vector<int> pos[MAXK];
vector<Query> qr[MAXK];
void init(void) {
	ffor(i,1,n) {
		string tmp;
		ffor(j,i,min(n,i+3)) {
			tmp=tmp+S[j];
			pos[check(tmp)].push_back(i);	
		}
	}
	return ;
}
map<pair<int,int>,int> mp,qrrr;
int pos1[MAXN],pos2[MAXN],tot1,tot2,lst[MAXK],qrlst[MAXM];
int get_ans(int *pos1,int *pos2,int tot1,int tot2,int len1,int len2) {
	int ans=-1; if(tot1==0||tot2==0) return -1;
	int pos=1;
	while(pos<tot2&&pos2[pos]<pos1[1]) pos++;
	ffor(i,1,tot1) {
		while(pos<tot2&&pos2[pos]<pos1[i]) pos++;
		if(pos2[pos]<pos1[i]) break;
		if(ans==-1) ans=max(pos2[pos]+len2,pos1[i]+len1)-pos1[i];
		else ans=min(ans,max(pos2[pos]+len2,pos1[i]+len1)-pos1[i]);
	}
	return ans;
}
int solve(string A,string B) {
	int aid=check(A),bid=check(B);
	if(mp.count({min(aid,bid),max(aid,bid)})) return mp[{min(aid,bid),max(aid,bid)}];
	tot1=tot2=0;
	for(auto id:pos[aid]) pos1[++tot1]=id;
	for(auto id:pos[bid]) pos2[++tot2]=id;
	if(tot1==0||tot2==0) return -1;
	int ans1=get_ans(pos1,pos2,tot1,tot2,A.size(),B.size()),ans2=get_ans(pos2,pos1,tot2,tot1,B.size(),A.size());
	if(ans1==-1) return ans2;
	if(ans2==-1) return ans1;
	return mp[{min(aid,bid),max(aid,bid)}]=min(ans1,ans2);	
}
void SOLVE(void) {
	roff(i,n,1) {
		string tmp;
		ffor(j,i,min(n,i+3)) tmp+=S[j],lst[check(tmp)]=i;	
		tmp="";
		ffor(j,i,min(n,i+3)) {
			tmp+=S[j];
			for(auto pr:qr[check(tmp)]) {
				int nxt=pr.nxt,id=pr.id,len=pr.len;
				if(lst[nxt]) {
					int Len=max((int)tmp.size(),lst[nxt]+len-i);
					if(ans[id]==-1) ans[id]=Len;
					else ans[id]=min(ans[id],Len);
				}
			}
		}
	}
	memset(lst,0,sizeof(lst));
	ffor(i,1,n) {
		string tmp;
		roff(j,i,max(1,i-3)) tmp=S[j]+tmp,lst[check(tmp)]=i;	
		tmp="";
		roff(j,i,max(1,i-3)) {
			tmp=S[j]+tmp;
			for(auto pr:qr[check(tmp)]) {
				int nxt=pr.nxt,id=pr.id,len=pr.len;
				if(lst[nxt]) {
					int Len=max((int)tmp.size(),i-lst[nxt]+len);
					if(ans[id]==-1) ans[id]=Len;
					else ans[id]=min(ans[id],Len);
				}
			}
		}
	}
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>S,n=S.size(),S="&"+S; init();
	cin>>q; int bl=450; memset(ans,-1,sizeof(ans));
	ffor(i,1,q) {
		cin>>a[i]>>b[i];
		if(pos[check(a[i])].size()==0||pos[check(b[i])].size()==0) continue ;
		if(pos[check(a[i])].size()>pos[check(b[i])].size()) swap(a[i],b[i]);
		if(pos[check(b[i])].size()<=bl) ans[i]=solve(a[i],b[i]);
		else {
			if(qrrr.count({min(check(a[i]),check(b[i])),max(check(a[i]),check(b[i]))})) qrlst[i]=qrrr[{min(check(a[i]),check(b[i])),max(check(a[i]),check(b[i]))}];
			else {
				qrrr[{min(check(a[i]),check(b[i])),max(check(a[i]),check(b[i]))}]=i;
				qr[check(a[i])].push_back({check(b[i]),i,b[i].size()});
			}
		}
	}
	SOLVE();
	ffor(i,1,q) if(qrlst[i]) cout<<ans[qrlst[i]]<<'\n'; else cout<<ans[i]<<'\n';
	return 0;
}
```

---

## 作者：St_john (赞：4)

发现 $|a|,|b|$ 很小，可以暴力处理出 $O(4|S|)$ 个可能的串。  

根号分治。

对于出现次数大等于 $\sqrt{4|S|}$ 的串，暴力预处理和其他串的答案，复杂度 $O(|S|\sqrt{|S|})$ 。  

对于出现次数小于 $\sqrt{4|S|}$ 的串，暴力计算答案，复杂度为 $O(\sqrt{4|S|})$ 。  

总复杂度为 $O((q+|S|)\sqrt{|S|})$ 。  

注意一些实现**细节**。  

**注意事项：**
1. 字符串哈希，27进制，`a-z` 对应 `1-26` 。  
1. 内存问题
	1. 字符串库的内存为 $27^4$ ，不是 $26^4$ ！！！
    1. 预处理的数组大小不是 $4|S| \times \sqrt{4|S|}$，这样会 **MLE** 的，观察发现，肯定会有重复出现的字符串，可以证明不同的字符串数 $\leqslant 3|S|$。
 
1. 块长我用的是 $450$ ，本题不卡常。

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#define _for(i,a,b) for(register int i=(a);i<=(b);++i)
#define __for(i,a,b) for(register int i=(a);i>=(b);--i)
#define Re register int
#define il inline
#define pc putchar
using namespace std;
typedef long long ll;
const int N=50000+10,M=531441+10,inf=2147483647;
il int re(){
	int x=0;
	bool f=0;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		f|=ch=='-',ch=getchar();
	while(ch>='0'&&ch<='9')
		x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return f?-x:x;
}
void pr(int x){
	if(x<0) x=-x,pc('-');
	if(x>9) pr(x/10);
	pc(x%10|48);
}

char s[N];int n;
il int calc(int l,int r){
	int num=0;
	_for(i,l,r)
		num=num*27+s[i]-'a'+1;
	return num;
}
const int B=450,B1=B+10,B2=3*N/B+10;
int all[M],L[N*3],cnt;
int p[5][N];
vector<int> v[N*3];
int num,all2[N*3],f[B2][N*3];
il int min(int a,int b){
	return a<b?a:b;
}
il int max(int a,int b){
	return a>b?a:b;
}
void init(){
	_for(len,1,4){//预处理 O(4|S|) 个字符串
		for(Re l=1,r;(r=l+len-1)<=n;++l){
			int slr=calc(l,r);
			if(!all[slr]){
				all[slr]=++cnt;//对应id
				L[cnt]=len;//长度
			}
			p[len][l]=all[slr];//起始位置和长度对应串的id
			v[all[slr]].push_back(l);//存放出现位置
		}
	}
	memset(f,0x3f,sizeof(f));
	_for(i,1,cnt)
		if(v[i].size()>=B){//处理出现次数>=sqrt(4|S|) 的部分
			all2[i]=++num;
			for(Re j=1;j<v[i].size();++j){
				//通过枚举当前串的出现位置来找中间的串
				int x=v[i][j-1],y=v[i][j],xx=x+L[i]-1,yy=y+L[i]-1;
				_for(len,1,4)
					for(Re l=x,r;l<y&&(r=l+len-1)<=n;++l)
						f[num][p[len][l]]=min(f[num][p[len][l]],
						min(max(r,xx)-x+1,max(r,yy)-l+1));
			}
			int x=v[i][0],y=x+L[i]-1;
			_for(len,1,4)//开头的
				for(Re l=1;l<x;++l)
					f[num][p[len][l]]=min(f[num][p[len][l]],
					max(y,l+len-1)-l+1);
			x=v[i][v[i].size()-1],y=x+L[i]-1;
			_for(len,1,4)//结尾的
				for(Re l=x,r;(r=l+len-1)<=n;++l)
					f[num][p[len][l]]=min(f[num][p[len][l]]
					,max(y,r)-x+1);
		}
	
}

signed main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	init();
	int m=re();
	while(m--){
		scanf("%s",s+1);
		int a=all[calc(1,strlen(s+1))];
		scanf("%s",s+1);
		int b=all[calc(1,strlen(s+1))];
		//分别将字符串读入，对应到数值上
		if(!a||!b)
			pr(-1),pc('\n');
		else if(all2[a])//特判预处理的部分
			pr(f[all2[a]][b]),pc('\n');
		else if(all2[b])
			pr(f[all2[b]][a]),pc('\n');
		else{//暴力
			int now=0,ans=inf;
			for(Re i=0;i<v[a].size();++i){
				int la=v[a][i],ra=la+L[a]-1;
				while(now+2<=v[b].size()&&v[b][now]<la)
					++now;//使lb尽可能地接近la
				int lb=v[b][now],rb=lb+L[b]-1;
				if(lb>=la){
					ans=min(ans,max(ra,rb)-la+1);//lb在la前
					if(now){
						lb=v[b][now-1],rb=lb+L[b]-1;
						ans=min(ans,max(ra,rb)-lb+1);
						//la在lb前
					}
				}
				else{
					ans=min(ans,max(ra,rb)-lb+1);
					//la在lb前
				}
			}
			pr(ans),pc('\n');
		}
	}
	return 0;
}
```


---

## 作者：5k_sync_closer (赞：2)

字符串？哈希！

考虑暴力，对每次询问 $a,b$ 找到其在 $S$ 中的所有出现，

对 $a$ 的所有出现，找到与其最近的 $b$ 的出现，

不难发现若 $a$ 的枚举是单调的，则 $b$ 的枚举也是单调的。

对 $a,b$ 的出现次数根号分治，注意到 $1\le|a|,|b|\le4$，则出现次数 $\Omega(\sqrt n)$ 的串有 $O(\sqrt n)$ 个。

对所有出现次数 $\Omega(\sqrt n)$ 的串，处理其与其他所有串（$O(n)$ 个）的答案。

询问 $a,b$ 时，若其一出现次数 $\Omega(\sqrt n)$，查表即可。

若 $a,b$ 出现次数均为 $O(\sqrt n)$，则可以保证暴力复杂度为 $O(\sqrt n)$。
```cpp
#include <vector>
#include <cstdio>
#include <cstring>
#define B 27ll
using namespace std;
vector<int> v[150050];
char s[50050];
int n, m, c1, c2, p1[600050], L[150050], p[5][50050], p2[150050], f[350][150050];
int H(int l, int r)
{
    int q = 0;
    for (int i = l; i <= r; ++i)
        q = q * B + s[i] - 'a' + 1;
    return q;
}
int main()
{
    memset(f, 0x3f, sizeof f);
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int z = 1; z <= 4; ++z)
        for (int l = 1, k; l + z - 1 <= n; ++l)
        {
            if (!p1[k = H(l, l + z - 1)])
                L[p1[k] = ++c1] = z;
            v[p[z][l] = p1[k]].push_back(l);
        }
    for (int i = 1; i <= c1; ++i)
        if (v[i].size() >= 450)
        {
            p2[i] = ++c2;
            for (int j = 1, x1, x2, y1, y2; j < v[i].size(); ++j)
            {
                x1 = v[i][j - 1];
                x2 = x1 + L[i] - 1;
                y1 = v[i][j];
                y2 = y1 + L[i] - 1;
                for (int z = 1; z <= 4; ++z)
                    for (int l = x1, r; l < y1 && l + z - 1 <= n; ++l)
                        r = l + z - 1, f[c2][p[z][l]] = min(f[c2][p[z][l]], min(max(r, x2) - x1 + 1, max(r, y2) - l + 1));
            }
            int x1 = v[i][0], x2 = x1 + L[i] - 1;
            for (int z = 1; z <= 4; ++z)
                for (int l = 1; l < x1; ++l)
                    f[c2][p[z][l]] = min(f[c2][p[z][l]], max(x2, l + z - 1) - l + 1);
            x1 = v[i][v[i].size() - 1], x2 = x1 + L[i] - 1;
            for (int z = 1; z <= 4; ++z)
                for (int l = x1; l + z - 1 <= n; ++l)
                    f[c2][p[z][l]] = min(f[c2][p[z][l]], max(x2, l + z - 1) - x1 + 1);
        }
    scanf("%d", &m);
    while (m--)
    {
        scanf("%s", s + 1);
        int a = p1[H(1, strlen(s + 1))];
        scanf("%s", s + 1);
        int b = p1[H(1, strlen(s + 1))];
        if (!a || !b)
            puts("-1");
        else if (p2[a])
            printf("%d\n", f[p2[a]][b]);
        else if (p2[b])
            printf("%d\n", f[p2[b]][a]);
        else
        {
            int u = 0, q = 1e9;
            for (int i = 0, l1, r1, l2, r2; i < v[a].size(); ++i)
            {
                l1 = v[a][i];
                r1 = l1 + L[a] - 1;
                while (u + 1 < v[b].size() && v[b][u] < l1)
                    ++u;
                l2 = v[b][u];
                r2 = l2 + L[b] - 1;
                if (l2 >= l1)
                {
                    q = min(q, max(r1, r2) - l1 + 1);
                    if (u)
                    {
                        l2 = v[b][u - 1];
                        r2 = l2 + L[b] - 1;
                        q = min(q, max(r1, r2) - l2 + 1);
                    }
                }
                else
                    q = min(q, max(r1, r2) - l2 + 1);
            }
            printf("%d\n", q);
        }
    }
    return 0;
}
```


---

## 作者：xuyuansu (赞：1)

## 题意
给你一个字符串，每次询问包含给出的两个字符串的最短子串。
## 题解
对于答案的计算，只要找到两个字符串在模板串中的出现位置，就可以很容易处理了。

但是可以发现在线处理是几乎不可能的，哪怕是最高效的匹配算法也无法胜任，但是如果把询问串拿出来直接处理很可能会出现一些极端情况把人卡掉，所以需要考虑均衡一下复杂度。

首先可以预处理所有询问串在模板串的出现位置，由于询问串非常短，所以可以直接暴力匹配。然后可以发现，出现了超过 $ \sqrt{n} $ 级别阀值的串个数不超过 $ \sqrt{n} $ 级别，可以通过向前和向后扫整个序列预处理出这些串和其他所有串组合起来的答案，而出现次数小于阀值的数可以两者间使用类似归并的方式求值，单次复杂度是 $ \sqrt{n} $ 级别。总复杂度 $ O(n\sqrt{n}) $ 。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,cnt,sum[N],block=500;
int last[N],siz[N];
vector<int> v[N],res[N],id[N];
map<string,int> m;
pair<int,int> q[N];
string s,c;
void solve(int x)
{
    for(int i=1;i<=cnt;i++) last[i]=0;
    res[x].resize(cnt+5,2e9);
    for(int i=1;i<=(int)s.size();i++)
    {
        for(int j : id[i])
        {
            last[j]=i;
            if(last[x])
            {
                res[x][j]=min(res[x][j],max(siz[x]+i-last[x],siz[j]));
            }
        }
    }
    for(int i=1;i<=cnt;i++) last[i]=0;
    for(int i=(int)s.size();i>=1;i--)
    {
        for(int j : id[i])
        {
            last[j]=i;
            if(last[x])
                res[x][j]=min(res[x][j],max(siz[j]+last[x]-i,siz[x]));
        }
    }
}
int query(int x,int y)
{
    if(!sum[x] || !sum[y]) return -1;
    int res=2e9;
    int i=0,j=0;
    while(i<v[x].size() && j<v[y].size())
    {
        if(v[x][i]<v[y][j])
        {
            res=min(res,max(siz[x]+v[y][j]-v[x][i],siz[y]));i++;
        }
        else{
            res=min(res,max(siz[y]+v[x][i]-v[y][j],siz[x]));j++;
        }
    }
    while(i<v[x].size())
    {
        res=min(res,max(siz[y]-v[y][j-1]+v[x][i],siz[x]));i++;
    }
    while(j<v[y].size())
    {
        res=min(res,max(siz[x]-v[x][i-1]+v[y][j],siz[y]));j++;
    }
    return res;
}
int main()
{
    cin>>s;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        cin>>c;
        if(!m[c]) m[c]=++cnt,siz[cnt]=c.size();
        q[i].first=m[c];
        cin>>c;
        if(!m[c]) m[c]=++cnt,siz[cnt]=c.size();
        q[i].second=m[c];
    }
    for(int i=1;i<=(int)s.size();i++)
    {
        string now="";
        for(int j=i;j>=max(i-5,1);j--)
        {
            now=s[j-1]+now;
            if(m[now])
            {
                int x=m[now];
                sum[x]++;v[x].push_back(i);
                id[i].push_back(x);
            }
        }
    }
    for(int i=1;i<=cnt;i++)
    {
        if(sum[i]<block) continue;
        solve(i);
    }
    for(int i=1;i<=n;i++)
    {
        if(sum[q[i].first]<sum[q[i].second]) swap(q[i].first,q[i].second);
        if(sum[q[i].first]>=block)
        {
            if(res[q[i].first][q[i].second]==2e9) printf("-1\n");
            else printf("%d\n",res[q[i].first][q[i].second]);
        }
        else{
            printf("%d\n",query(q[i].first,q[i].second));
        }
    }
    return 0;
}
```


---

## 作者：wmrqwq (赞：0)

# 题目链接

[CF444D DZY Loves Strings](https://www.luogu.com.cn/problem/CF444D)

# 解题思路

发现我们只需要预处理每个长度不大于 $4$ 的字符串所在的区间即可，那么我们实际上需要的字符串是只有 $4n$ 级别的，下文设 $4n$ 为 $m$。

我们容易发现出现次数 $> \sqrt{m}$ 的字符串数量是 $\sqrt{m}$ 级别的，于是我们可以直接预处理出对于每个出现次数 $> \sqrt{m}$ 的字符串对于其余子串的答案，此处时间复杂度为 $O(m \sqrt{m})$。

那么对于每一个询问，如果两个字符串有至少一个字符串出现次数是 $> \sqrt{m}$ 的，那么此时我们已经预处理过了，直接输出答案即可，时间复杂度 $O(1)$。否则，如果两个字符串出现次数都是 $\le \sqrt{m}$ 的，那么此处我们直接枚举第一个字符串所在的位置，对于第二个字符串直接双指针维护即可，此处时间复杂度 $\sqrt{m}$，此处最劣时间复杂度为 $O(q \sqrt{m})$。

总时间复杂度为 $O((m+q) \sqrt{m})$。

# 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define re register
#define ll long long
#define cll const ll
#define forl(i,a,b) for(re ll (i)=(a);i<=(b);(i)++)
#define forr(i,a,b) for(re ll (i)=(a);i>=(b);(i)--
#define pii pair<ll,ll>
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
#define pb push_back
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#define endl '\n'
#define QwQ return 0;
#define x first
#define y second
template<typename T1,typename T2>bool Max(T1&x,T2 y){if(y>x)return x=y,1;return 0;}template<typename T1,typename T2>bool Min(T1&x,T2 y){if(y<x)return x=y,1;return 0;}ll Ss=chrono::steady_clock::now().time_since_epoch().count();mt19937_64 Apple(Ss);ll rand_lr(ll l,ll r){return Apple()%(r-l+1)+l;}
ll _t_;
string s;
ll n,q;
string s1,s2;
map<string,ll>mp;
string mp2[200010];
ll a[200010],k;
vector<pii>G[200010];
ll sz[200010];
ll sq=500;
string x,y;
vector<ll>big;
int ans[300][100005];
ll bigmp[200010];
ll visbig[200010];
ll ID;
void Init()
{
    forl(i,0,(ll)big.size()-1)
    {
        ll id=big[i];
        forl(j,1,4)
        {
            ll L=-1,szm=(ll)G[id].size()-1;
            forl(l,1,n-j+1)
            {
                ll len=1e9;
                ll r=l+j-1;
                string S="";
                forl(_,l,r)
                    S+=s[_];
                while(L<szm && G[id][L+1].y<=r)
                    L++;
                if(L!=-1)
                    Min(len,max(G[id][L].y,r)-min(l,G[id][L].x)+1);
                if(L<szm)
                    Min(len,max(G[id][L+1].y,r)-min(l,G[id][L+1].x)+1);
                Min(ans[i+1][mp[S]],len);
            }
        }
    }
}
void _clear(){}
void solve()
{
    _clear();
    cin>>s>>q;
    n=s.size();
    s=' '+s;
    forl(i,1,n)
    {
        string S="";
        forl(j,i,min(i+3,n))
        {
            S+=s[j];
            if(!mp[S])
                mp[S]=++k;
            mp2[mp[S]]=S;
            G[mp[S]].pb({i,j});
            sz[mp[S]]++;
        }
    }
    forl(i,1,k)
        if(sz[i]>=sq)
            big.pb(i),
            visbig[i]=1,
            bigmp[i]=++ID;
    forl(i,1,(ll)big.size())
        forl(j,1,k)
            ans[i][j]=1e9;
    Init();
    forl(_,1,q)
    {
        cin>>x>>y;
        ll id1=mp[x],id2=mp[y];
        if(!id1 || !id2)
        {
            cout<<-1<<endl;
            continue;
        }
        if(visbig[id1]+visbig[id2]==0)
        {
            ll L=-1,szm=(ll)G[id2].size()-1;
            ll len=1e18;
            for(auto i:G[id1])
            {
                while(L<szm && G[id2][L+1].y<=i.y)
                    L++;
                if(L!=-1)
                    Min(len,max(G[id2][L].y,i.y)-min(i.x,G[id2][L].x)+1);
                if(L<szm)
                    Min(len,max(G[id2][L+1].y,i.y)-min(i.x,G[id2][L+1].x)+1);
            }
            if(len==1e18)
                len=-1;
            cout<<len<<endl;
        }
        else
        {
            ll A=1e9;
            if(visbig[id1]+visbig[id2]==2)
                A=min(ans[bigmp[id1]][id2],ans[bigmp[id2]][id1]);
            else if(visbig[id1])
                A=ans[bigmp[id1]][id2];
            else
                A=ans[bigmp[id2]][id1];
            if(A>=1e9)
                A=-1;
            cout<<A<<endl;
        }
    }
}
int main()
{
	Init();
//    freopen("tst.txt","r",stdin);
//    freopen("sans.txt","w",stdout);
    IOS;
    _t_=1;
   // cin>>_t_;
    while(_t_--)
        solve();
    QwQ;
}
```

---

## 作者：lfxxx (赞：0)

来个不动脑子的写法。下文记 $n = |s|$。

首先有意义的 $a,b$ 显然只有 $O(n)$ 个，暴力找出来，把下标放到 vector 里面排序。

不妨记 $cnt_{t}$ 为 $t$ 的出现次数，每次询问串 $a,b$ 时，显然可以枚举 $cnt$ 小的串的所有出现位置，然后在另一个串对应的 vector 中二分一个前驱后继贡献到答案上，复杂度为 $O(\min(cnt_a,cnt_b) \log n)$。

于是记忆化所有询问，由于 $\sum cnt_{t} = O(n)$，所以可以做到 $O(n \sqrt n \log n)$，常数很小直接通过了。


```cpp
#include<bits/stdc++.h>
using namespace std;
vector< pair<int,int> > S[531441+114];
int _pow[4]={1,27,729,19683};
map<int,int> ans[531441+114],vis[531441+114];
int trans(string s){
	int res=0;
	for(int i=0;i<(int)s.size();i++) res+=(s[i]-'a'+1)*_pow[i];
	return res;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	string T;
	cin>>T;
	for(int i=1;i<=4;i++){
		for(int j=0;j+i-1<(int)T.size();j++){
			string s;
			for(int k=j;k<j+i;k++) s+=T[k];
			S[trans(s)].push_back(make_pair(j,j+i-1));
		}
	}
	for(int i=0;i<=531441;i++) sort(S[i].begin(),S[i].end());
	int q;
	cin>>q;
	while(q--){
		string a,b;
		cin>>a>>b;
		int A=trans(a),B=trans(b);
		if(make_pair(S[A].size(),A)>make_pair(S[B].size(),B)) swap(A,B);
		if(vis[A][B]!=0){
			cout<<ans[A][B]<<'\n';
		}else{
			vis[A][B]=1;
			ans[A][B]=1e9;
			if(S[A].size()==0||S[B].size()==0){
				ans[A][B]=-1;
				cout<<ans[A][B]<<'\n';
				continue;
			}
			for(pair<int,int> now:S[A]){
				int l=-1,r=S[B].size()-1;
				if(S[B].back()>=now){
					while(l+1<r){
						int mid=(l+r)>>1;
						if(S[B][mid]>=now) r=mid;
						else l=mid;
					}
					pair<int,int> chi=S[B][r];
					ans[A][B]=min(max(chi.second,now.second)-min(chi.first,now.first)+1,ans[A][B]);
				}
				l=0,r=S[B].size();
				if(S[B][0]<=now){
					while(l+1<r){
						int mid=(l+r)>>1;
						if(S[B][mid]<=now) l=mid;
						else r=mid;
					}
					pair<int,int> fan=S[B][l];
					ans[A][B]=min(max(fan.second,now.second)-min(fan.first,now.first)+1,ans[A][B]);
				}
			}
			if(ans[A][B]>=1e9) ans[A][B]=-1;
			cout<<ans[A][B]<<'\n';
		}
	}
	return 0;
}
```

---

## 作者：wwwwwza (赞：0)

发现询问串的长度非常小，这样的话只用处理最多 $2\times 10^5$ 个串就可以了。

考虑根号分治。

设 $M=4\times N$，即一共有多少个串。

对于出现次数大于 $\sqrt{M}$ 次的串，最多只会出现 $\sqrt{M}$ 次，直接预处理这 $\sqrt{M}$ 个串与其他串的最短距离。

若询问串的长度都小于等于 $\sqrt{M}$，直接双指针枚举两个串的位置。

这里的块长即 $\sqrt{M}$ 我取了 $400$。

这题不卡时间卡空间，需要注意数组的大小。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1.5e5+5;
const int M=400;
char ch[N],a[7],b[7];
int q,cnt=1,tot=0,f[M+5][N],vis[N];
vector<int>lst[N];
map<int,int>id;
struct line{
	int len,ht;
}pos[M];
int hs(int l,int r){
	int res=0;
	for(int i=l;i<=r;i++){
		res=res*27+(ch[i]-'a'+1);
	}
	return res;
}
int calc(int x1,int y1,int x2,int y2){
	return max(y1,y2)-min(x1,x2)+1;
}
int main(){
	scanf("%s",ch+1);
	int n=strlen(ch+1);
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++){
		for(int len=1;len<=4;len++){
			int j=i+len-1;
			if(j>n)break;
			int res=hs(i,j);
			if(!id[res])id[res]=cnt,cnt++;
			lst[id[res]].push_back(i);
			if(lst[id[res]].size()==M+1){
				pos[++tot]={len,res};
				vis[id[res]]=tot;
			}
		}
	}
	for(int i=1;i<=tot;i++){
		int h=id[pos[i].ht];
		for(int j=0;j<lst[h].size();j++){
			int l=(j==0?1:lst[h][j-1]);
			int r=(j==lst[h].size()-1?n:lst[h][j+1]);
			for(int k=l;k<=r;k++){
				for(int len=1;len<=4;len++){
					int p=k+len-1;
					if(p>n)break;
					f[i][id[hs(k,p)]]=min(f[i][id[hs(k,p)]],calc(lst[h][j],lst[h][j]+pos[i].len-1,k,p));
				}
			}
		}
	}
	scanf("%d",&q);
	while(q--){
		scanf("%s%s",a+1,b+1);
		int lena=strlen(a+1),lenb=strlen(b+1),suma=0,sumb=0;
		for(int i=1;i<=lena;i++){
			suma=suma*27+(a[i]-'a'+1);
		}
		for(int i=1;i<=lenb;i++){
			sumb=sumb*27+(b[i]-'a'+1);
		}
		if(!id[suma]||!id[sumb]){
			printf("-1\n");
			continue;
		}
		bool flag=0;
		if(vis[id[suma]])printf("%d\n",f[vis[id[suma]]][id[sumb]]),flag=1;
		if(flag)continue;
		if(vis[id[sumb]])printf("%d\n",f[vis[id[sumb]]][id[suma]]),flag=1;
		if(flag)continue;
		suma=id[suma],sumb=id[sumb];
		int ans=1e9;
		for(int i=0,j=0;i<lst[suma].size();i++){
			while(j+1<lst[sumb].size()&&lst[sumb][j+1]<lst[suma][i])j++;
			ans=min(ans,calc(lst[suma][i],lst[suma][i]+lena-1,lst[sumb][j],lst[sumb][j]+lenb-1));
			if(j!=lst[sumb].size()-1){
				j++;
				ans=min(ans,calc(lst[suma][i],lst[suma][i]+lena-1,lst[sumb][j],lst[sumb][j]+lenb-1));
				j--;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

```

---

## 作者：qiyue7 (赞：0)

由于query串的最大长度只有4 ，显然长度为4的不同子串最多4 * n个 ，所以写个超级大暴力 ，然后分类讨论加花式剪枝压常数 ，就A了（居然1A了  我自己都不信） 
AC代码：
```cpp
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
#include <ext/rope>
using namespace __gnu_cxx;
#include<string>
#include<vector>
#include<regex>
#include<algorithm>
#include<random>
#include<map>
#include<set>
#include<deque>
#include<iomanip>
#include<sstream>
#include<stack>
#include<iostream>
#include<limits>
#include<bitset>
#include<list>
#include<queue>
#include<memory>
#include<functional>
#include<unordered_map>
#define EPS 1e-8
const int sigma = 26;
using namespace std;
struct Trie_node
{
	Trie_node *next[sigma];
	Trie_node *fail;
	int end, end2, ans, depth;
	string ends;
 	Trie_node(Trie_node*a = NULL, bool b = 0)
	{
		memset(next, 0, sizeof(next));
		fail = a;
		end2 = 0;
		end = b;
		ans = 0;
		depth = 0;
	}
};

struct Trie
{
	Trie_node *root;
	Trie()
	{
		root = new Trie_node(NULL, 0);
	}
	void insert(string &l)
	{
		Trie_node *found = root;
		for (auto &s : l)
		{
			if (found->next[s - 'a'] != NULL)
				found = found->next[s - 'a'];
			else
			{
				found->next[s - 'a'] = new Trie_node(NULL, 0);
				found = found->next[s - 'a'];
			}
		}
		found->end++;
		found->depth = l.size();
		found->ends = l;
	}

	void compute_fail()
	{
		queue<Trie_node *> part;
		part.push(root);
		while (!part.empty())
		{
			Trie_node *part2 = NULL;
			Trie_node *father = part.front();
			part.pop();
			for (int s = 0; s < sigma; ++s)
			{
				if (father->next[s] != NULL)
				{
					if (father == root)
						father->next[s]->fail = root;
					else
					{
						part2 = father->fail;
						while (part2 != NULL)
						{
							if (part2->next[s] != NULL)
							{
								father->next[s]->fail = part2->next[s];
								father->next[s]->end2 += part2->next[s]->end2;
								break;
							}
							part2 = part2->fail;
						}
						if (part2 == NULL)
							father->next[s]->fail = root;
					}
					part.push(father->next[s]);
				}
			}
		}
	}
	void clear()
	{
		root = new Trie_node(NULL, 0);
	}
}trie1;
list<pair<string,string> > query;
gp_hash_table<string, set<int> > trans;
map<pair<string, string>, int> trans2;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	string s,qs1,qs2;
	int n;
	cin >> s;
	cin >> n;
	while (n--)
	{
		cin >> qs1 >> qs2;
		trie1.insert(qs1);
		trie1.insert(qs2);
		query.push_back({ qs1,qs2 });
	}
	trie1.compute_fail();
	Trie_node *p=trie1.root;
	for (int i = 0; i < s.size(); ++i)
	{
		if (p->next[s[i] - 'a'] != NULL)
		{
			p = p->next[s[i] - 'a'];
			Trie_node *p2 = p;
			while (p2!= trie1.root)
			{
				trans[p2->ends].insert(i+1);
				p2 = p2->fail;
			}
		}
		else
		{
			while (p != trie1.root && p->next[s[i] - 'a'] == NULL)
				p = p->fail;
			if (p->next[s[i] - 'a'] != NULL)
			{
				p = p->next[s[i] - 'a'];
				Trie_node *p2 = p;
				while (p2 != trie1.root)
				{
					trans[p2->ends].insert(i + 1);
					p2 = p2->fail;
				}
			}
		}
	}
	while (!query.empty())
	{
		auto k = query.front(),k2=query.front();
		query.pop_front();
		swap(k2.first, k2.second);
		if (trans2.find(k) == trans2.end() && trans2.find(k2) == trans2.end())
		{
			int Min = 10000000;
			if (k.first == k.second)
			{
				if (!trans[k.first].empty())
					trans2[k] = k.first.size();
				else
					trans2[k] = -1;
			}
			else
			{
				if (trans[k.first].size() > trans[k.second].size())
				{
					for (auto &it1 : trans[k.second])
					{
						auto it2=trans[k.first].lower_bound(it1);
						int calc ;
						if (it2 != trans[k.first].end())
						{
							calc = min(it1 - k.second.size(), *it2 - k.first.size());
							Min = min(int(*it2 - calc), Min);
						}
						if (it2 != trans[k.first].begin())
						{
							it2--;
							calc = min(it1 - k.second.size(), *it2 - k.first.size());
							Min = min(int(it1-calc), Min);
						}
					}
				}
				else
				{
					for (auto &it1 : trans[k.first])
					{
						auto it2 = trans[k.second].lower_bound(it1);
						int calc;
						if (it2 != trans[k.second].end())
						{
							calc = min(*it2 - k.second.size(), it1 - k.first.size());
							Min = min(int(*it2 - calc), Min);
						}
						if (it2 != trans[k.second].begin())
						{
							it2--;
							calc = min(*it2 - k.second.size(), it1 - k.first.size());
							Min = min(int(it1 - calc), Min);
						}
					}
				}
				if (Min != 10000000)
					trans2[k] = trans2[k2] = Min;
				else
					trans2[k] = trans2[k2] = -1;
			}
		}
		if (trans2.find(k) != trans2.end())
			cout << trans2[k] << '\n';
		else
			cout << trans2[k2] << '\n';
	}
	return 0;
}
```


---

