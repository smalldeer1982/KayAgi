# String Manipulation 1.0

## 题目描述

One popular website developed an unusual username editing procedure. One can change the username only by deleting some characters from it: to change the current name $ s $ , a user can pick number $ p $ and character $ c $ and delete the $ p $ -th occurrence of character $ c $ from the name. After the user changed his name, he can't undo the change.

For example, one can change name "arca" by removing the second occurrence of character "a" to get "arc".

Polycarpus learned that some user initially registered under nickname $ t $ , where $ t $ is a concatenation of $ k $ copies of string $ s $ . Also, Polycarpus knows the sequence of this user's name changes. Help Polycarpus figure out the user's final name.

## 说明/提示

Let's consider the first sample. Initially we have name "bacbac"; the first operation transforms it into "bacbc", the second one — to "acbc", and finally, the third one transforms it into "acb".

## 样例 #1

### 输入

```
2
bac
3
2 a
1 b
2 c
```

### 输出

```
acb
```

## 样例 #2

### 输入

```
1
abacaba
4
1 a
1 a
1 c
2 b
```

### 输出

```
baa
```

# 题解

## 作者：Soul_Love (赞：3)

看到还没有分块的代码，就想着来一发。

### 题意

给定一个正整数 $k$，和一个只含有小写字母的字符串 $S$，将 $k$ 个 $S$ 接在一起得到字符串 $G$，接下来有 $m$ 个操作，每次给定一个正整数 $p$ 和小写字母 $c$，表示将字符串 $G$ 从左往右第 $p$ 个 $c$ 删除。最后输出操作过后的字符串 $G$。

### 思路

考虑使用分块，对于每一个块开一个桶 $sum$，记录块内每个小写字母的个数。

每次询问时从第一个块开始，依次查看要删除的小写字母是否在这个块内，最后在块内暴力查找。

### code
```c
#include<bits/stdc++.h>
using namespace std;
int k,n,L[1000100],R[1000100],pos[1000100],l,m,sum[100000][200],x,t;
string g="6",s;//这里强制 g 从第一位开始存，所以先随便赋一个初值 
char o;
inline int read()
{
    int k=0,f=0;char c=getchar();
    for(;!isdigit(c);c=getchar()) f|=c=='-';
    for(;isdigit(c);c=getchar()) k=(k<<1)+(k<<3)+(c^48);
    return f?-k:k;
}
inline void build()//建块 
{
	l=g.size()-1;//得把那个随便赋的初值的长度减掉 
	int ql=sqrt(l);
	t=l/ql;
	for(int i=1;i<=t;i++)
	{
		L[i]=R[i-1]+1;
		R[i]=i*ql;
	}
	if(R[t]!=l)
	{
		t++;
		L[t]=R[t-1]+1;
		R[t]=l;
	}
	for(int i=1;i<=t;i++)
	{
		for(int j=L[i];j<=R[i];j++)
		{
			pos[j]=i;
			sum[i][g[j]]++;//统计每个块内各个小写字母的个数 
		}
	}
}
inline void update(int k,char o)
{
	int q=1;
	while(k>sum[q][o])//如果要删的小写字母 o 不在第 q 个块内 
	{
		k-=sum[q][o];//减去这个块内小写字母 o 的个数 
		q++;//下一个块 
	}
	sum[q][o]--;//删除 
	for(int i=L[q];i<=R[q];i++)//暴力查找 
	{
		if(g[i]==o)
		{
			k--;
			if(!k)
			{
				g[i]='0';//标记 
				break;
			}
		}
	}
}
int main()
{
	k=read();
	std::cin>>s;
	for(int i=1;i<=k;i++) g+=s;//把 k 个 S 接在一起 
	build();
	m=read();
	while(m--)
	{
		x=read();
		scanf("%c",&o);
		update(x,o);
	}
	for(int i=1;i<=l;i++) if(g[i]!='0') std::cout<<g[i];
	return 0;
}
```

---

## 作者：_Somutate_ (赞：1)

这只是模拟题吧，~~也许是因为不知道大佬们怎么想出这些写法才写暴力~~。

照题意模拟，$t=s+s+s+\cdots+s$（共计 $k$ 个 $s$），然后对于删除操作，我们可以用 vector 存下第 $p$ 次出现的 $c$ 在 $t$ 中的位置，然后每次删除时将这个位置上的字符变为 $0$，然后删除 vector 中这一存储位，根据 vector 的性质后面的储存会补上来。最后将字符串中不为 $0$ 的全输出就行了

部分代码如下：
```cpp
void solve()
{
	cin>>k>>t>>n;
	s=t;
	for(int i=2;i<=k;++i)t=t+s;//复制，使得 t=k个s
	for(int i=0;i<str.size();++i)v[str[i]].push_back(i);
	for(int i=1,p;i<=n;++i)
	{
		char c;
		cin>>p>>c;
		str[v[c][p-1]]=0;
		v[c].erase(v[c].begin()+p-1);
	}
	for(auto i:str)if(i)putchar(i); //输出
}
```
本蒟蒻第一篇题解，希望管理大大能给过审 qwq。

---

## 作者：huangzilang (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF159C)

**题目大意：**

先给出一个数 $k$ 和一个字符串 $s$，要复制 $k$ 次这个字符串 $s$，进行 $m$ 次操作，每次操作将字符串 $s$ 中第 $p$ 次出现的字符 $c$ 删去，问最后剩下的字符串是什么。

**思路：**

我是先把复制过后的字符串用一个 $t$ 数组存着，然后输入 $m$ 次，每次就查找第 $p$ 次出现的字符 $c$ 的位置，我们可以用一个函数 `find()` 来查找，这个函数返回的是一个位置，我用了一个 $q$ 来存，然后我们把 $t_q$ 标记为一个字符 ```-```，最后把这个 $t$ 数组里不是 ```-``` 的输出。

`find()`**函数详解：**

我们先定义一个计数器 $ans$，循环一遍整个字符串，如果第 $i$ 个字符为 $c$，那么计数器加 $1$，如果计数器等于 $p$，就立刻返回 $i$。

---

## 作者：helongyun (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF159C)
# 题目大意
给一个字符串，让你删除指定字母。
# 思路
这是一道模拟，顺便考字符串。
用按题意造出字符串（复制之后的），再按题意暴力找第若干个字母将其删除，最后输出就行。
# 核心代码
```cpp
for(int j=0;j<t.size();j++)
{//找第p个c
	if(v[j]==c)t++;
	if(t==p)//找到
  {
		v[j]='0';//标记'0' 
		break;//离开
	}
}
```

---

## 作者：beigongbaishan (赞：0)

# 题意
将 $k$ 个字符串 $s$ 接在一起，得到字符串 $t$，接下来进行 $q$ 次操作，每次把字符串 $t$ 中第 $p$ 个字符 $c$ 删除，最后输出操作后的字符串。
# 思路
按照题意模拟即可。可以用一个变量 $times$ 统计字符 $c$ 出现的次数，把第 $p$ 个 $c$ 标记为  `0`，最后把非 `0` 元素输出。有些讲解放在注释里啦。
# 核心代码：
```cpp
for(int j=0;j<t.size();j++){//找第p个c
	if(t[j]==c)times++;
	if(times==p){//找到了 
		t[j]='0';//标记为'0' 
		break;
	}
}
```

---

## 作者：zhoujunchen (赞：0)

楼上大佬在用分块，我只会用 vector，太强了%%%。

题目大意
--
字符串 $s$ 是给定 $c$ 重复 $k$ 次的字符串，依次删除第 $p$ 个 $ch$ 字母，输出最后得到的子串。

做题思路
--
因为用 vector 来进行删除操作太方便了，所以用 vector 循环模拟，先统计每个子串中每个字母出现的个数，再循环遍历字符串。

code:
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> v[207];
bool f[200005];
int k,n,m,x;
string c,s;
char ch;
int main(){
    cin>>k>>c;
    while(k--)s+=c;
    for(int i=0;i<s.size();i++)v[s[i]-'a'].push_back(i+1);
    cin>>m;
    while(m--){
        cin>>x>>ch;
        f[v[ch-'a'][x-1]]=1;
        v[ch-'a'].erase(v[ch-'a'].begin()+x-1);
    }
    for(int i=0;i<s.size();i++)if(!f[i+1])cout<<s[i];
    cout<<"\n";
    return 0;
}
```

---

## 作者：Wilderness_ (赞：0)

不理解其他大佬为何使用分块和树状数组这么高级的方法（doge
## 思路
这不是一道模拟题吗？

我们先用一个字符串 $t$ 存储下 $k$ 次复制后的 $s$，然后将每一个字符全部存到 vector 数组 $v$ 里（相当于一个桶），然后对于每个删除操作，将 $t_{v_{c,p}}$（因为 vector 从 0 开始存，$p$ 应先 -1）更改为 $0$，然后将 $v_{c,p}$ 用 v.erase() 函数删除。最后输出 $t$ 中每一个不为 0 的字符即可。

## Code：
```cpp
#include<bits/stdc++.h>
#define M 1145
using namespace std;
vector<int>v[M];
string t,s;
int k,n; 
int main()
{
	cin>>k>>t>>n;
	s=t;
	t.clear();
	for(int i=1;i<=k;++i)t=t+s;
	for(int i=0;i<t.size();++i)v[t[i]].push_back(i);
	for(int i=1;i<=n;++i)
	{
		int p;char c;
		cin>>p>>c;
		--p;
		t[v[c][p]]=0;
		v[c].erase(v[c].begin()+p);
	}
	for(int i=0;i<t.size();++i)
		if(t[i])
			printf("%c",t[i]);
    return 0;
}
```

---

## 作者：xu222ux (赞：0)

# [CF159C](https://www.luogu.com.cn/problem/CF159C)

## 题意：

有一个字符串 $t$ 是字符串 $s$ 复制 $k$ 次得到的，给定字符串 $s$ 和正整数 $k$ 有 $q$ 次操作，每次操作将字符串 $t$ 中第 $p$ 个出现的字符 $c$ 删去，问最后剩下的字符串是什么?

## 分块思路

这里讲一下分块，分块就是一个很长很长的字符串，有多次查询，每次查询要找一个数。

怎么做呢？分块登场。

分块算法会把这个字符串分成若干段段，当你要查询时，我就可以先确定查的点在那个块中，然后再在块中去搜。

## 本题思路

分块思想，对于每一个块一个桶来记录块内每个小写字母的个数。每次询问时暴力查找就行。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
bool flag[2000005];
int sum[20005][26];
int main(){
    int k;cin>>k>>s;
    string u="";
    for(int i=1;i<=k;i++)u+=s;
    int len=s.size();
    for(int i=0;i<len;i++)sum[1][s[i]-'a']++;
    for(int i=2;i<=k;i++){
        for(int j=0;j<26;j++)sum[i][j]=sum[i-1][j];
    }
    int q;cin>>q;
    while(q--){
        int t;char c;cin>>t>>c;
        int u=0,cnt=0,cur=0;
        for(int i=1;i<=k;i++){
            if(u+sum[i][c-'a']>=t){cur=i;break;}
            u+=sum[i][c-'a'];
            cnt+=len;
        }
        u=t-u;
        int yyy=-1,lll=0;
        while(true){
            cnt++,yyy++;
            if(!flag[cnt]&&s[yyy]==c)lll++;
            if(lll==u){
                sum[cur][s[yyy]-'a']--;
                flag[cnt]=true;
                break;
            }
        }
        //cout<<cnt;
    }
    for(int i=1;i<=len*k;i++){
        if(!flag[i])cout<<u[i-1];
    }
    return 0;
}
```

---

## 作者：nydzsf_qwq (赞：0)

## 题目大意：

给一个字符串，有 $n$ 次操作，每次操作将第 $p$ 个出现的字符 $c$ 删去，问最后剩下的字符串是什么。

## 解法：

考虑用树状数组维护字符 $c$ 在 $\left[1,m\right]$ 内被删除的个数，记为 $S(m)$，但问题是怎么求出第 $p$ 个究竟对应原来的第几个。

假设对应原来的第 $x$ 个，那么 $x-S(x)=p_{i}$。

$f(x)=x-S(x)$，那么当第 $x$ 个被删去时 $f(x)=f(x-1)$，否则 $f(x)=f(x-1)+1$，因此 $f(x)$ 单调**不降**。

然而问题并没有彻底解决，因为会有**多个** $x$ 满足 $f(x)=p_{i}$，要求的究竟是哪一个呢？

在这些 $x$ 中除了第一个都是满足 $f(x)=f(x-1)$ 的，因此都被删去了，所以第一个才是我们要求的。

那么答案就可以很容易地二分得到了。时间复杂度 $O(n\log^{2}n)$。

这题似乎也可以用分块来做。~~但是我写挂了。~~

### Code：

```
#include<bits/stdc++.h>
using namespace std;
const int N=2e5;
int k,n,del[N+5][26],cnt[26],c[N+5][26];
string s;
void add(int x,int t,int d=1) {
	while(x<=N) {
		c[x][t]+=d;
		x+=x&(-x);
	}
}
int S(int x,int t) {
	int res=0;
	while(x>0) {
		res+=c[x][t];
		x-=x&(-x);
	}
	return res;
}
int main() {
	cin>>k>>s>>n;
	for(int i=1;i<=n;++i) {
		int num;
		char ch;
		cin>>num>>ch;
		int l=1,r=N,mid;
		while(l<=r) {
			mid=(l+r)>>1;
			if(mid-S(mid,ch-'a')<num) l=mid+1;
			else r=mid-1;
		}
		add(l,ch-'a');
		del[l][ch-'a']=1;
	}
	for(int i=1;i<=k;++i)
		for(int j=0;j<s.size();++j) {
			++cnt[s[j]-'a'];
			if(!del[cnt[s[j]-'a']][s[j]-'a']) cout<<s[j];
		}
	return 0;
}
```

---

